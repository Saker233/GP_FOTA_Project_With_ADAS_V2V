/*******************************************************************************
**  FILENAME     : Bootloader_INTERFACE.h         			                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : Bootloader Driver INTERFACE file                           **
*********************************************************************************/
#ifndef INC_BOOTLOADER_INTERFACE_H_
#define INC_BOOTLOADER_INTERFACE_H_

#include "STD_TYPES.h"

/******************************************************************************
*************************Function Prototypes**********************************
*******************************************************************************
*******************************************************************************/

typedef void (*Function_t)(void);


/**
 * This function is used to check the bank flags and decide run bootloader or jump into applicatiopn
 */
void BL_voidSpecify_Bank();


/**
 * This function is used to specify which bank will be excuted
 */
void BL_Check_Active_Bank();


/**
 * This function is used to check bank 2 application appropriate or not
 * @return u32
 */
u32 BL_u32Check_Bank2();


/**
 * This function is used to check the validity of crc and flag of a specific bank
 * @return u8
 */
u8 BL_u8Check_Bank_Validity();


/**
 * This function is used to Update the flags in the control paga
 */
void BL_voidUpdate_Control_Page();


/**
 * This function is used to make the processor jump to the bootloader appliaction
 */
void BL_void_Jump_To_Bootloader();


/**
 * This function is used to make the processir jump to specific bank
 */
void BL_voidJump_To_Bank();

/**
 * This function is used to calculate the crc value for bank1
 * @return u32
 */
u32 BL_u32Calculate_CRC_Bank1();

/**
 * This function is used to calculate the crc value for bank2
 * @return u32
 */
u32 BL_u32Calculate_CRC_Bank2();



/**
 *
 * This function is used to Move bank2 to bank1
 *
 */
void BL_voidCopy_Bank2_To_Bank1();




/**
 *
 * This function is used to Move bank1 to bank2
 *
 */
void BL_voidCopy_Bank1_To_Bank2();



/**
 * This function is used to update the bank specifier flag and make software reset and start from the begining
 */
void BL_voidSet_Specifying_Flag_Make_SW_Reset();


/**
 * This function is used to request the update from the server
 */
void BL_voidRecieve_APP();


/**
 * This function is used to set the offset SCB_VTOR of the vector table
 */
void BL_voidVector_Table_Offset();


/**
 * This function is used to end the process of the bootloader, update the control flags, copy bank1 to bank2 and make software reset
 */
void BL_void_Finish_Bootloader();





#endif /* INC_BOOTLOADER_INTERFACE_H_ */
