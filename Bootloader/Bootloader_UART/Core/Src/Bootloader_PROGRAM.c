/*******************************************************************************
**  FILENAME     : Bootloader_PROGRAM.c         			                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : Bootloader Driver PROGRAM file                             **
*********************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Bootloader_PRIVATE.h"
#include "Bootloader_INTERFACE.h"
#include "Bootloader_CONFIG.h"
#include "FLS_INTERFACE.h"
#include "NVM_INTERFACE.h"
#include "CRC_INTERFACE.h"
#include "WDT_INTERFACE.h"
#include "usart.h"



u32 Size_Of_Code;
u8 First_Flash = BOOTLOADER_NOT_FIRST_FLASH;
u8 Host_Buffer[1024];

/******************************************************************************
* Function Definitions
*******************************************************************************/



/**
 * This function is used to specify which bank will be excuted
 */
void BL_Check_Active_Bank()
{
	/* Intialize Banks Status and read every flag first */
	u32 Bank1_Status = FLS_u32ReadWord(BANK1_STATUS_ADDRESS);
	u32 Bank1_CRC    = FLS_u32ReadWord(BANK1_CRC_ADDRESS);
	u32 Bank2_Status = BOOTLOADER_INIT_NOT_APPROPRIATE;


	if(BOOTLOADER_APP_IS_IN_BANK1 == Bank1_Status)
	{
		/* Make sure that the value of the saved crc is the same calcuted new crc */
		u32 Bank1_New_CRC = BL_u32Calculate_CRC_Bank1();
		if(Bank1_New_CRC == Bank1_CRC)
		{
			/* If yes then jump to application*/
			BL_voidJump_To_Bank();
		}
		else
		{
			/* If no then update the validity flag as not appropriate then make softwarwe reset */
			NVM_voidUpdateControlPage(BANK1_STATUS_ADDRESS, BOOTLOADER_BANK_NOT_APPROPRIATE);
			WWDT_voidMakeSoftWareReset();
		}
	}
	else if((BOOTLOADER_BANK_NOT_APPROPRIATE == Bank1_Status) || (0xFFFFFFFF == Bank1_Status))
	{
		/* Check the application in bank 2  */
		Bank2_Status = BL_u32Check_Bank2();
		if(Bank2_Status == BOOTLOADER_BANK_APPROPRIATE)
		{
			/* if bank 2 is all good we will move the app to bank 1 and jump to bank 1 to excute the app */
			BL_voidCopy_Bank2_To_Bank1();
			BL_voidJump_To_Bank();
		}
		else if((Bank2_Status == BOOTLOADER_BANK_NOT_APPROPRIATE) || (Bank2_Status == 0xFFFFFFFF))
		{
			/* if bank 2 is NOT good also we update the flags and make software reset tp go to the bootloader */
			BL_voidSet_Specifying_Flag_Make_SW_Reset();
		}
		else
		{
			/* NOTHING */
		}
	}
	else
	{
		/* NOTHING */
	}



}


/**
 * This function is used to check bank 2 application appropriate or not
 * @return u32
 */
u32 BL_u32Check_Bank2()
{
	u32 Bank2_Status = FLS_u32ReadWord(BANK2_STATUS_ADDRESS);
	u32 Bank2_CRC    = FLS_u32ReadWord(BANK2_CRC_ADDRESS);
	u32 result = 0;
	if(Bank2_Status == BOOTLOADER_BACKUP_IS_IN_BANK2)
	{
		u32 Bank2_New_CRC = BL_u32Calculate_CRC_Bank2();
		if(Bank2_New_CRC == Bank2_CRC)
		{
			result = BOOTLOADER_BANK_APPROPRIATE;
		}
		else
		{
			/* if it's not the same CRC value then we will update the flag and return not appropeiate */
			NVM_voidUpdateControlPage(BANK2_STATUS_ADDRESS, BOOTLOADER_BANK_NOT_APPROPRIATE);
			result =  BOOTLOADER_BANK_NOT_APPROPRIATE;
		}
	}
	return result;
}


/**
 * This function is used to check the validity of crc and flag of a specific bank
 * @return u8
 */
u8 BL_u8Check_Bank_Validity()
{
	u8 Result = 0;

	/* Read both status flags for both banks */
	u32 Bank1_Status = FLS_u32ReadWord(BANK1_STATUS_ADDRESS);
	u32 Bank2_Status = FLS_u32ReadWord(BANK2_STATUS_ADDRESS);

	if((Bank1_Status == 0xFFFFFFFF) || (Bank1_Status == BOOTLOADER_BANK_NOT_APPROPRIATE))
	{
		if ((Bank2_Status == 0xFFFFFFFF) || (Bank2_Status == BOOTLOADER_BANK_NOT_APPROPRIATE))
		{
			Result = BOOTLOADER_APP_IS_NOT_APPROPRIATE_OR_NOT_EXISTING;
		}
		else
		{
			Result = BOOTLOADER_APP_IS_APPROPRIATE_OR_EXISTING;
		}
	}
	else
	{
		Result = BOOTLOADER_APP_IS_APPROPRIATE_OR_EXISTING;
	}
	return Result;
}


/**
 * This function is used to Update the flags in the control paga
 */
void BL_voidUpdate_Control_Page()
{
	u8  Bank_Status      =  BL_u8Check_Bank_Validity();
	u32 Bank1_Status     =  FLS_u32ReadWord(BANK1_STATUS_ADDRESS);
	u8 First_Request    =  0;
	u8  Control_Flag     =  0;
	u32 Bank_Size        =  0;
	u32 CRC_Value        =  0;
	u8 Data[8]           = {0};



	if(Bank_Status == BOOTLOADER_APP_IS_NOT_APPROPRIATE_OR_NOT_EXISTING)
	{
		/* First time to flash the bank */
		HAL_UART_Receive(&huart1, &First_Request, 1, 100);
		//CanIf_voidReceive_Word(&First_Request);
		First_Flash = 1;
	}
	else
	{
		/* NOTHING */
	}

	/* Send Request to the server that we need update */
	HAL_UART_Transmit(&huart1, UDS_MCU_ACKNOWLEDGE_UPGRADE_REQUEST, 1, 100);
	//CanIf_voidTransmit_Byte(UDS_MCU_ACKNOWLEDGE_UPGRADE_REQUEST);

	/* wait for the server to send the flag value which followed by array of 8 elemneets the first 4 is data represent the size and the last 4 are crc values */
	HAL_UART_Receive(&huart1, &Control_Flag, 1, 100);
	//CanIf_voidReceive_Byte(&Control_Flag);


	if(Control_Flag == UDS_GWY_PROVIDE_HEADER)
	{
		//CanIf_voidTransmit_Byte(UDS_MCU_ACCEPT_RECEIVING_HEADER);
		HAL_UART_Transmit(&huart1, UDS_MCU_ACCEPT_RECEIVING_HEADER, 1, 100);
		//CanIf_voidReceive_Block(Data, 8);
		HAL_UART_Receive(&huart1, Data, 8, 100);

		/* Here we received the array which contain the size and the crc values from the host or the server and we gonna parse this array to extarct the values */
		Bank_Size = ((Data[3] << 24) | (Data[2] << 16) | (Data[1] << 8) | (Data[0]));

		CRC_Value = ((Data[7] << 24) | (Data[6] << 16) | (Data[5] << 8) | (Data[4]));

		/* After Updateing the size of the bank and the new CRC values we will make bank 2 as a backup of bank 1 */
		if(Bank1_Status == BOOTLOADER_APP_IS_IN_BANK1)
		{
			BL_voidCopy_Bank1_To_Bank2();
		}

		NVM_voidUpdateControlPage(BANK1_SIZE_ADDRESS, Bank_Size);
		NVM_voidUpdateControlPage(BANK1_CRC_ADDRESS, CRC_Value);
	}

}


/**
 * This function is used to make the processor jump to the bootloader appliaction
 */
void BL_void_Jump_To_Bootloader()
{
	BL_voidUpdate_Control_Page();
	BL_voidRecieve_APP();
}


/**
 * This function is used to make the processir jump to specific bank
 */
void BL_voidJump_To_Bank()
{
	Function_t Address = 0;
	/* Assigning tha bank 1 address */
	Address = *(Function_t *)(ADDRESS_OF_BANK1);

	/* Make the vector table offset */
	BL_voidVector_Table_Offset();

	/* Jump to bank 1 address */
	Address();



}

/**
 * This function is used to calculate the crc value for bank1
 * @return u32
 */
u32 BL_u32Calculate_CRC_Bank1()
{
	u32 CRC_Value = 0;

	/* Reading the bank size   */
	u32 Size_Bank = FLS_u32ReadWord(BANK1_SIZE_ADDRESS);

	u32 NO_Words = Size_Bank / 4;

	/* CAlculate CRC */
	MCRC_voidCalculateCrcDirect(ADDRESS_OF_STARTUP_BANK1, NO_Words, &CRC_Value);

	return CRC_Value;

}

/**
 * This function is used to calculate the crc value for bank2
 * @return u32
 */
u32 BL_u32Calculate_CRC_Bank2()
{
	u32 CRC_Value = 0;

	/* Reading the bank size   */
	u32 Size_Bank = FLS_u32ReadWord(BANK2_SIZE_ADDRESS);

	u32 NO_Words = Size_Bank / 4;

	/* CAlculate CRC */
	MCRC_voidCalculateCrcDirect(ADDRESS_OF_STARTUP_BANK2, NO_Words, &CRC_Value);

	return CRC_Value;
}



/**
 *
 * This function is used to Move bank2 to bank1
 *
 */
void BL_voidCopy_Bank2_To_Bank1()
{
	u32 Bank2_Data    		  = 0;
	u32 Bank2_Address 		  = 0;
	u32 Bank1_Data_Address    = 0;

	/* Reading THe size of bank 2 */
	u32 Bank2_Size = FLS_u32ReadWord(BANK2_SIZE_ADDRESS);

	u32 Bank2_Size_Word = Bank2_Size / 4;

	/* Calcutling CRC value for bank 2 */
	u32 Bank2_CRC = FLS_u32ReadWord(BANK2_CRC_ADDRESS);

	/* Erase Bank 1  */
	FLS_voidEraseAppArea(NUMBER_OF_FIRST_PAGE_IN_BANK1, NUMBER_OF_LAST_PAGE_IN_BANK1);

	/* Copying the app in bank 2 to bank 1 */
	for(u32 Counter = 0; Counter < Bank2_Size_Word; Counter++)
	{
		/* Looping over bank 1 addresses  */
		Bank1_Data_Address = (ADDRESS_OF_STARTUP_BANK1 + (WORD_SIZE * Counter));

		/* Looping over bank 2 addreses */

		Bank2_Address      = (ADDRESS_OF_STARTUP_BANK2 + (WORD_SIZE * Counter));

		/* Referncing the addresses into the data */
		Bank2_Data = *((volatile u32 *) Bank2_Address);


		/* Looping over the whole bank addresses to flash it */
		FLS_u8ProgramOneWordFlash(Bank1_Data_Address, Bank2_Data);

	}

	/* Updating the control page with the new falsg values  */
	/* Updating bank 1 size */
	NVM_voidUpdateControlPage(BANK1_SIZE_ADDRESS, Bank2_Size);

	/* Updating CRC value */
	NVM_voidUpdateControlPage(BANK1_CRC_ADDRESS, Bank2_CRC);

	/* Making the bank 1 active */
	NVM_voidUpdateControlPage(BANK1_STATUS_ADDRESS, BOOTLOADER_APP_IS_IN_BANK1);


	/* making bank 2 back up */
	NVM_voidUpdateControlPage(BANK2_STATUS_ADDRESS, BOOTLOADER_BACKUP_IS_IN_BANK2);

}




/**
 *
 * This function is used to Move bank1 to bank2
 *
 */
void BL_voidCopy_Bank1_To_Bank2()
{
	u32 Bank1_Data    		  = 0;
	u32 Bank1_Address 		  = 0;
	u32 Bank2_Data_Address    = 0;

	/* Reading THe size of bank 2 */
	u32 Bank1_Size = FLS_u32ReadWord(BANK1_SIZE_ADDRESS);

	u32 Bank1_Size_Word = Bank1_Size / 4;

	/* Calcutling CRC value for bank 2 */
	u32 Bank1_CRC = FLS_u32ReadWord(BANK1_CRC_ADDRESS);

	/* Erase Bank 1  */
	FLS_voidEraseAppArea(NUMBER_OF_FIRST_PAGE_IN_BANK2, NUMBER_OF_LAST_PAGE_IN_BANK2);

	/* Copying the app in bank 2 to bank 1 */
	for(u32 Counter = 0; Counter < Bank1_Size_Word; Counter++)
	{
		/* Looping over bank 1 addresses  */
		Bank2_Data_Address = (ADDRESS_OF_STARTUP_BANK2 + (WORD_SIZE * Counter));

		/* Looping over bank 2 addreses */

		Bank1_Address      = (ADDRESS_OF_STARTUP_BANK1 + (WORD_SIZE * Counter));

		/* Referncing the addresses into the data */
		Bank1_Data = *((volatile u32 *) Bank1_Address);


		/* Looping over the whole bank addresses to flash it */
		FLS_u8ProgramOneWordFlash(Bank2_Data_Address, Bank1_Data);

	}

	/* Updating the control page with the new falsg values  */
	/* Updating bank 1 size */
	NVM_voidUpdateControlPage(BANK2_SIZE_ADDRESS, Bank1_Size);

	/* Updating CRC value */
	NVM_voidUpdateControlPage(BANK2_CRC_ADDRESS, Bank1_CRC);

	/* Making the bank 1 active */
	NVM_voidUpdateControlPage(BANK2_STATUS_ADDRESS, BOOTLOADER_BACKUP_IS_IN_BANK2);


	/* making bank 2 back up */
	NVM_voidUpdateControlPage(BANK2_STATUS_ADDRESS, BOOTLOADER_APP_IS_IN_BANK1);

}



/**
 * This function is used to update the bank specifier flag and make software reset and start from the begining
 */
void BL_voidSet_Specifying_Flag_Make_SW_Reset()
{

	/* Making Specifying flag with zero in order to be able to recive new code  */
	NVM_voidUpdateControlPage(BL_SPECIFYING_BANK_FLAG, SET_SPECIFYING_FLAG);

	/* SOftware Reset via watchdog timer */
	IWDT_voidMakeSoftWareReset();
}


/**
 * This function is used to request the update from the server
 */
void BL_voidRecieve_APP()
{
	u8 Gateway_Request = 0;

	u32 Bank1_Address  = ADDRESS_OF_STARTUP_BANK1;

	Size_Of_Code = FLS_u32ReadWord(BANK1_SIZE_ADDRESS);

	/* Erasing bank 1 */
	FLS_voidEraseAppArea(NUMBER_OF_FIRST_PAGE_IN_BANK1, NUMBER_OF_LAST_PAGE_IN_BANK1);

	/* Response to gateway that the headers is updated from the other function jump to bootloader*/
	//CanIf_voidTransmit_Byte(UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED);
	HAL_UART_Transmit(&huart1, UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED, 1, 100);



	while(Size_Of_Code)
	{

		//CanIf_voidReceive_Byte(&Gateway_Request);
		HAL_UART_Receive(&huart1, &Gateway_Request, 1, 100);


		if(Gateway_Request == UDS_GWY_REQUEST_SENDING_LINE_OF_CODE)
		{
			CanIf_voidTransmit_Byte(UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE);

			if(Size_Of_Code > 1024)
			{
				CanIf_voidReceive_Block(Host_Buffer, 1024);

				Size_Of_Code -= 1024;

				FLS_voidProgramFlashBuffer(Bank1_Address, Host_Buffer, 1024);

				Bank1_Address += 1024;

				//CanIf_voidTransmit_Byte(UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED);
				HAL_UART_Transmit(&huart1, UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED, 1, 100);
			}
			else
			{
				//CanIf_voidReceive_Block(Host_Buffer, Size_Of_Code);
				HAL_UART_Receive(&huart1, Host_Buffer, Size_Of_Code, 100)

				FLS_voidProgramFlashBuffer(Bank1_Address, Host_Buffer, Size_Of_Code);

				Size_Of_Code -= Size_Of_Code; //zero escape while

				//CanIf_voidTransmit_Byte(UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED);
				HAL_UART_Transmit(&huart1, UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED, 1, 100);
			}
		}

		//CanIf_voidReceive_Byte(&Gateway_Request);
		HAL_UART_Receive(&huart1, &Gateway_Request, 1, 100);

		if(Gateway_Request == UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE)
		{
			BL_void_Finish_Bootloader();
		}
		else
		{
			/* NOTHING */
		}
	}
}


/**
 * This function is used to set the offset SCB_VTOR of the vector table
 */
void BL_voidVector_Table_Offset()
{

	/* Making the offset of the vector table to the start of bank 1 */
	SCB_VTOR = ADDRESS_OF_STARTUP_BANK1;
}


/**
 * This function is used to end the process of the bootloader, update the control flags, copy bank1 to bank2 and make software reset
 */
void BL_void_Finish_Bootloader()
{
	/* Requesting a code from the gatewayy */
	//CanIf_voidTransmit_Byte(UDS_MCU_ACKNOWLEDGE_FINISHING);
	HAL_UART_Transmit(&huart1, UDS_MCU_ACKNOWLEDGE_FINISHING, 1, 100);

	NVM_voidUpdateControlPage(BANK1_STATUS_ADDRESS, BOOTLOADER_APP_IS_IN_BANK1);
	NVM_voidUpdateControlPage(BANK2_STATUS_ADDRESS, BOOTLOADER_BACKUP_IS_IN_BANK2);

	if(First_Flash == 1)
	{
		First_Flash = 0;

		BL_voidCopy_Bank1_To_Bank2();
	}

	NVM_voidUpdateControlPage(BL_SPECIFYING_BANK_FLAG, RESET_SPECIFYING_FLAG);

	IWDT_voidMakeSoftWareReset();
}















