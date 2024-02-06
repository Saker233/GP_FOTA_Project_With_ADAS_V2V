
/*******************************************************************************
**  FILENAME     : NVM_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : NVM Driver PROGRAM file                                     **
**                                                                            **
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "NVM_PRIVATE.h"
#include "NVM_INTERFACE.h"
#include "NVM_CONFIG.h"
#include "FEE_INTERFACE.h"



/******************************************************************************
* Function Definitions
*******************************************************************************/

void NVM_voidEraseRestoreHeaderPage(u32 Copy_u32Address, u32 Copy_u32NewData)
{
	u32 Local_u32AddressArray[NUMBER_OF_FLAGS];
	u32 Local_u32DataArray[NUMBER_OF_FLAGS];
	u16 Local_u16DataIndex        = 0;
	u16 Local_u16DataCounter      = 0;
	u32 Local_u32AddressCounter   = 0;
	for ( Local_u32AddressCounter = START_OF_AREA ;Local_u32AddressCounter < END_OF_AREA; Local_u32AddressCounter += WORD_SIZE_IN_BYTE)
	{
		if( (Local_u32AddressCounter != Copy_u32Address) & (*((u32*)(Local_u32AddressCounter)) != ERASED_VALUE))
		{
			Local_u32AddressArray[Local_u16DataIndex] = Local_u32AddressCounter;
			Local_u32DataArray[Local_u16DataIndex] = *((u32*)(Local_u32AddressCounter));
			Local_u16DataIndex++ ;
		}
	}

	Fee_EraseImmediateBlock(HEADER_PAGE_NUMBER); // erase after save

	for (Local_u16DataCounter = 0 ; Local_u16DataCounter < Local_u16DataIndex ;Local_u16DataCounter++ )
	{
		Fee_Write(Local_u32AddressArray[Local_u16DataCounter], Local_u32DataArray[Local_u16DataCounter] );
	}
	Fee_Write(Copy_u32Address, Copy_u32NewData);
}
