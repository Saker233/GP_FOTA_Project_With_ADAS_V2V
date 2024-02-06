/*******************************************************************************
**  FILENAME     : FEE_INTERFACE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : FEE Driver INTERFACE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_FEE_INTERFACE_H_
#define INC_FEE_INTERFACE_H_


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define PAGE_DATA_OFFSET                                                8
#define PAGE_DATA_SIZE                                                  8




#define PAGE_0_ADDRESS                                                  0x0800FC00
#define PAGE_SIZE                                                       1024









/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 *
 * @param Copy_u16PageNumber
 */
void Fee_EraseImmediateBlock(u16 Copy_u16PageNumber);
/**
 *
 * @param Copy_u32Address
 * @param Copy_u32Data
 */
void Fee_Write(u32 Copy_u32Address, u32 Copy_u32Data);





#endif /* INC_FEE_INTERFACE_H_ */
