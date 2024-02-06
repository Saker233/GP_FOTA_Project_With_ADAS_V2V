
/*******************************************************************************
**  FILENAME     : FLS_INTERFACE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : FLS Driver INTERFACE file                                  **
**                                                                            **
*******************************************************************************/
#ifndef INC_FLS_INTERFACE_H_
#define INC_FLS_INTERFACE_H_

/******************************************************************************
* Function Declarations
*******************************************************************************/

/**
 * This function is used to write code on the flash using flash driver peripheral
 * @param Copy_u32Address
 * @param Copy_u32Data
 * @return
 */
void   FLS_u8ProgramOneWordFlash(u32 Copy_u32Address, u32 Copy_u32Data);


/**
 * This function is used to write code on the flash using flash driver peripheral
 * @param Copy_u32Address
 * @param Copy_u16Code
 * @param Copy_u8Length
 */
void FLS_voidProgramFlash(u32 Copy_u32Address, u16 * Copy_u16Code, u8 Copy_u8Length);

/**
 * This function is used to ERASE code on the flash using flash driver peripheral
 * @param Copy_u16PageNumber
 */
void FLS_voidErasePage(u16 Copy_u16PageNumber);

/**
 * This function is used to ERASE Area on the flash using flash driver peripheral
 * @param Copy_u16FirstPageNumber
 * @param Copy_u16LastPageNumber
 */
void FLS_voidEraseAppArea(u16 Copy_u16FirstPageNumber, u16 Copy_u16LastPageNumber);


/**
 * This function is used to Read Word on the flash using flash driver peripheral
 * @param Copy_DataAddress
 * @return
 */
u32 FLS_u32ReadWord(u32 Copy_DataAddress);

void FLS_voidProgramFlashBuffer(u32 Copy_u32Address, u8* Copy_u16Code, u16 Copy_u16Length);

void FLS_voidProgramHalfWordFlash(u32 Copy_u32Address, u16 Copy_u16Data);
void FLS_voidProgramDoubleWord(u32 Copy_u32Address, u64 Copy_u32Data);

#endif /* INC_FLS_INTERFACE_H_ */
