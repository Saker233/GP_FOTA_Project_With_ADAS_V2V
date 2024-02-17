
/*******************************************************************************
**  FILENAME     : NVM_INTERFACE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : NVM Driver INTERFACE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_NVM_INTERFACE_H_
#define INC_NVM_INTERFACE_H_

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define NUMBER_OF_FLAGS                       20
#define HEADER_PAGE_NUMBER                    63
#define WORD_SIZE_IN_BYTE                     4
#define START_OF_AREA                         0x0800FC00
#define END_OF_AREA                           0x0800FC50
#define ERASED_VALUE                          0xffffffff


/******************************************************************************
* Function Prototypes
*******************************************************************************/

void UDS_voidDetectNewCode(u8 Copy_u8ReceivedValue);

void NVM_voidUpdateControlPage(u32 Copy_u32Address, u32 Copy_u32NewData);

#endif /* INC_NVM_INTERFACE_H_ */
