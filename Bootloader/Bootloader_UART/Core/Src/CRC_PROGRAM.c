
/*******************************************************************************
**  FILENAME     : CRC_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CRC Driver PROGRAM file                                     **
**                                                                            **
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "CRC_PRIVATE.h"
#include "CRC_INTERFACE.h"
#include "CRC_CONFIG.h"







/******************************************************************************
* Function Definitions
*******************************************************************************/
void MCRC_u32CalculateCrcHw(u32 * Copy_u32WordArray, u8 Copy_u8ByteArraySize, u32 * Copy_u32PtrCrc)
{
	   *Copy_u32PtrCrc = 0;


	   if(Copy_u32WordArray != NULL)
	   {
		   CRC_CR = CRC_RESET;
	      for(u32 Local_u32WordCounter = 0;Local_u32WordCounter < Copy_u8ByteArraySize;++Local_u32WordCounter)
	      {
	         CRC_DR = (u32)(Copy_u32WordArray[Local_u32WordCounter]);
	      }
	      *Copy_u32PtrCrc = CRC_DR;
	   }
	   else
	   {
	      /*!<TODO: Null pointer detected */
	   }
}
void MCRC_voidCalculateCrcDirect(u32 Copy_u32BaseAddress, u32 Copy_u32WordNumber, u32 * Copy_u32PtrCrc)
{
	   *Copy_u32PtrCrc = 0;
		u32 Local_u32Crc = 0;
		u16 Local_u16HalfWordH = 0 ;
		u16 Local_u16HalfWordL = 0 ;
	    u32 * Local_u32PtrToInteger = (u32 *)(Copy_u32BaseAddress);
	   if(Local_u32PtrToInteger != NULL)
	   {
	      CRC_CR = CRC_RESET;
	      for(u32 Local_u32WordCounter = 0;Local_u32WordCounter < Copy_u32WordNumber;Local_u32WordCounter++)
	      {
					Local_u16HalfWordL = (*((volatile u8*)(Copy_u32BaseAddress))<<8) | (*((volatile u8*)(Copy_u32BaseAddress+1)));
					Local_u16HalfWordH = (*((volatile u8*)(Copy_u32BaseAddress+2))<<8) | (*((volatile u8*)(Copy_u32BaseAddress+3)));
					CRC_DR = (Local_u16HalfWordL<<16)|Local_u16HalfWordH;
					Local_u32Crc = CRC_DR;
					Copy_u32BaseAddress+=WORD_SIZE_IN_BYTE;
	      }
		  *Copy_u32PtrCrc = CRC_DR;
	   }
	   else
	   {
		  /* Null pointer detected */
	   }
}
