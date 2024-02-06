
/*******************************************************************************
**  FILENAME     : CRC_PRIVATE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CRC Driver PRIVATE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_CRC_PRIVATE_H_
#define INC_CRC_PRIVATE_H_

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// CRC base address.
#define CRC_BASE_ADDRESS     0x40023000

#define DR                   0X00
#define IDR                  0X04
#define CR                   0X08

#define CRC_DR           *((volatile u32 *)(CRC_BASE_ADDRESS + DR))
#define CRC_IDR          *((volatile u32 *)(CRC_BASE_ADDRESS + IDR))
#define CRC_CR           *((volatile u32 *)(CRC_BASE_ADDRESS + CR))


#define CRC_RESET       1
#define WORD_SIZE       4

#define RESET                    0
#define WORD_SIZE_IN_BYTE        4
#endif /* INC_CRC_PRIVATE_H_ */
