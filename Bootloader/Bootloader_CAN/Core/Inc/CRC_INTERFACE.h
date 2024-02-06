
/*******************************************************************************
**  FILENAME     : CRC_INTERFACE.h        			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CRC Driver INTERFACE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_CRC_INTERFACE_H_
#define INC_CRC_INTERFACE_H_

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MCRC_u32CalculateCrcHw(u32 * Copy_u32WordArray, u8 Copy_u8ByteArraySize, u32 * Copy_u32PtrCrc);
void MCRC_voidCalculateCrcDirect(u32 Copy_u32BaseAddress, u32 Copy_u32WordNumber, u32 * Copy_u32PtrCrc);

#endif /* INC_CRC_INTERFACE_H_ */
