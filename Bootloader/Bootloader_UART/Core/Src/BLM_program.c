/*******************************************************************************
**  FILENAME     : BLM_PROGRAM.c         			                  		 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : BLM Driver PROGRAM file                            		 **

/******************************************************************************
************************************* Includes ********************************
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


/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
 * This function is used to check the bank flags and decide run bootloader or jump into applicatiopn
 */
void BL_voidSpecify_Bank()
{
	/* Reading the status address of Specifying flag */
	u32 Specifying_Flag = FLS_u32ReadWord(BL_SPECIFYING_BANK_FLAG);

	if(Specifying_Flag == RESET_SPECIFYING_FLAG)
	{
		/* if yes go check bank1 status and crc ......... */
		BL_Check_Active_Bank();
	}
	else if(Specifying_Flag == SET_SPECIFYING_FLAG)
	{
		/* if zero so there's no app then jump to bootloader and recive new code */
		BL_void_Jump_To_Bootloader();
	}
	else
	{
		/* NOTHING */
	}

}















