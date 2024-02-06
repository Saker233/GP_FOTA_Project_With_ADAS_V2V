/*******************************************************************************
**  FILENAME     : FEE_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : FEE Driver PROGRAM file                                     **
**                                                                            **
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"


#include "FLS_INTERFACE.h"



/**
 *
 * @param Copy_u16PageNumber
 */
void Fee_EraseImmediateBlock(u16 Copy_u16PageNumber)
{
	FLS_voidErasePage(Copy_u16PageNumber);
}
/**
 *
 * @param Copy_u32Address
 * @param Copy_u32Data
 */
void Fee_Write(u32 Copy_u32Address, u32 Copy_u32Data)
{
	FLS_u8ProgramOneWordFlash(Copy_u32Address, Copy_u32Data);
}



