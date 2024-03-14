
/*******************************************************************************
**  FILENAME     : FLS_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : FLS Driver PROGRAM file                                     **
**                                                                            **
*******************************************************************************/


/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "FLS_PRIVATE.h"
#include "FLS_INTERFACE.h"
#include "FLS_CONFIG.h"









/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
 * This function is used to write code on the flash using flash driver peripheral
 * @param Copy_u32Address
 * @param Copy_u32Data
 * @return
 */
void FLS_u8ProgramOneWordFlash(u32 Copy_u32Address, u32 Copy_u32Data)
{
	 u32  Local_u32StoredData = 0;
	 u32 Local_u32Address = Copy_u32Address;
	 u16 Local_u16LeastHalfWord = (u16)(FLS_CATCH_LEAST_HALF_WORD)  & (Copy_u32Data);
	 u16 Local_u16MostHalfWord  = (u16)((Copy_u32Data) >> TWO_BYTES_IN_BITS);
	 // Check that no main Flash memory operation is ongoing.
	 FLS_voidProgramHalfWordFlash(Copy_u32Address, Local_u16LeastHalfWord);
	 FLS_voidProgramHalfWordFlash(Copy_u32Address + TWO_BYTE, Local_u16MostHalfWord);
	 Local_u32StoredData = *((volatile u16*)(Local_u32Address));
}

void FLS_voidProgramDoubleWord(u32 Copy_u32Address, u64 Copy_u32Data)
{
	u32 Local_u32StoredData = 0;
	u32 Local_u32Address = Copy_u32Address;
	u32 Local_Counter = 0;
	 for (Local_Counter = 0U; Local_Counter < 4; Local_Counter++)
	    {
		 FLS_voidProgramHalfWordFlash((Copy_u32Address + (2U*Local_Counter)), (u16)(Copy_u32Data >> (16U*Local_Counter)));
	    }
	 Local_u32StoredData = *((volatile u16*)(Local_u32Address));
}


/**
 * This function is used to write code on the flash using flash driver peripheral
 * @param Copy_u32Address
 * @param Copy_u16Code
 * @param Copy_u8Length
 */
void FLS_voidProgramFlash(u32 Copy_u32Address, u16 * Copy_u16Code, u8 Copy_u8Length)
{
	   // Check that no main Flash memory operation is ongoing.
	   while(GET_BIT(FLS->SR, BSY) == SET);
	   // Check if the flash locked or not.
	   if(GET_BIT(FLS->CR, LOCK) == SET)
	   {
	     // Perform Unlock Sequence To Unlock FLS Peripheral.
	     FLS->KEYR = FLS_KEY_1;
	     FLS->KEYR = FLS_KEY_2;
	   }
	   for(u8 Local_u8Index = 0;Local_u8Index < Copy_u8Length;Local_u8Index++)
	   {
	     // Set the PG bit in the FLASH_CR register to write on the flash.
	     SET_BIT(FLS->CR, PG);
	     // Half word write operation.
	     *((volatile u16*)(Copy_u32Address)) = Copy_u16Code[Local_u8Index];
	     Copy_u32Address += TWO_BYTE;
	     // Wait for the BSY bit to be reset.
	     while(GET_BIT(FLS->SR, BSY) == SET)
	     {

	     }
	     // EOP
		   SET_BIT(FLS->SR, EOP);
	     CLR_BIT(FLS->CR, PG);
	   }
		 SET_BIT(FLS->CR, LOCK);
}

/**
 * This function is used to ERASE code on the flash using flash driver peripheral
 * @param Copy_u16PageNumber
 */
void FLS_voidErasePage(u16 Copy_u16PageNumber)
{
	 SET_BIT(FLS->CR,LOCK);
	  // Check that no main Flash memory operation is ongoing.
	  while(GET_BIT(FLS->SR, BSY) == SET);
	  // Check if the flash locked or not.
	  if(GET_BIT(FLS->CR, LOCK) == SET)
	  {
		 // Perform Unlock Sequence To Unlock FLS Peripheral.
		 FLS->KEYR = FLS_KEY_1;
		 FLS->KEYR = FLS_KEY_2;
	  }
	  // Set the PER bit in the FLASH_CR register to erase page.
	  SET_BIT(FLS->CR, PER);
	  // Program the FLASH_AR register to select a page to erase.
	  FLS->AR = FLASH_START_ADDRESS + (u32)(Copy_u16PageNumber * PAGE_SIZE);
	  // Set the STRT bit in the FLASH_CR register to start erase operation.
	  SET_BIT(FLS->CR, STRT);
	  /*Wait for the BSY bit to be reset*/
	  while(GET_BIT(FLS->SR, BSY) == SET);
	  // EOP
	  SET_BIT(FLS->SR, EOP);
	  CLR_BIT(FLS->CR, PER);
	  SET_BIT(FLS->CR, LOCK);
}

/**
 * This function is used to ERASE Area on the flash using flash driver peripheral
 * @param Copy_u16FirstPageNumber
 * @param Copy_u16LastPageNumber
 */
void FLS_voidEraseAppArea(u16 Copy_u16FirstPageNumber, u16 Copy_u16LastPageNumber)
{
	   for(u16 Local_u8Page = Copy_u16FirstPageNumber;Local_u8Page <= Copy_u16LastPageNumber;Local_u8Page++)
	   {
	      FLS_voidErasePage(Local_u8Page);
	   }
}


/**
 * This function is used to Read Word on the flash using flash driver peripheral
 * @param Copy_DataAddress
 * @return
 */
u32 FLS_u32ReadWord(u32 Copy_DataAddress)
{
	u32 Local_u32Data = 0;
	Local_u32Data = *((volatile u32*)(Copy_DataAddress));
	return Local_u32Data;
}

void FLS_voidProgramFlashBuffer(u32 Copy_u32Address, u8* Copy_u16Code, u16 Copy_u16Length)
{
	u16 Local_Word = 0 ;
	u16 Local_Counter = 0;

	/* Write to flash */
	for (Local_Counter = 0 ; Local_Counter < Copy_u16Length  ;  Local_Counter+= 2 )
	{
		Local_Word = Copy_u16Code[Local_Counter] | (Copy_u16Code[Local_Counter+1] << 8) ;
		FLS_voidProgramHalfWordFlash(Copy_u32Address , Local_Word);
		Copy_u32Address += 2 ;
	}

}

void FLS_voidProgramHalfWordFlash(u32 Copy_u32Address, u16 Copy_u16Data)
{
	// Check that no main Flash memory operation is ongoing.
		/* Reading the Busy Bit */
	   while(GET_BIT(FLS->SR, BSY) == SET);
	   // Check if the flash locked or not.
	   /* Reading the lock bit */
	   if(GET_BIT(FLS->CR, LOCK) == SET)
	   {
	      // Perform Unlock Sequence To Unlock FLS Peripheral.
	      FLS->KEYR = FLS_KEY_1;
	      FLS->KEYR = FLS_KEY_2;
	   }
	   // Set the PG bit in the FLASH_CR register.
	   SET_BIT(FLS->CR, PG);
	   // Perform the data write (half-word) at the desired address.
	   *((volatile u16*)(Copy_u32Address)) = Copy_u16Data;
	   // Wait for the BSY bit to be reset.
	   while(GET_BIT(FLS->SR, BSY) == SET)
	   {

	   }
	   // EOP
		 SET_BIT(FLS->SR, EOP);
		 CLR_BIT(FLS->CR, PG);
		 SET_BIT(FLS->CR, LOCK);
}























