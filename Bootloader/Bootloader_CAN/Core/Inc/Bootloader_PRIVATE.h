/*******************************************************************************
**  FILENAME     : Bootloader_PRIVATE.h         			                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : Bootloader Driver PRIVATE file                              **
*********************************************************************************/
#ifndef INC_BOOTLOADER_PRIVATE_H_
#define INC_BOOTLOADER_PRIVATE_H_


/******************************************************************************
********************************  Preprocessor Constants **********************
*******************************************************************************/
#define SCB_VTOR                                   *((volatile u32 *)SCB_VTOR_ADDRESS)
#define SCB_VTOR_ADDRESS                        	0xE000ED08
#define PACKET_SIZE                            		64

#define ADDRESS_OF_STARTUP_BANK1		            0x08001400
#define ADDRESS_OF_BANK1	                        0x08001404
#define NUMBER_OF_FIRST_PAGE_IN_BANK1			    7
#define NUMBER_OF_LAST_PAGE_IN_BANK1		        33


#define BANK1_CONTROL_PAGE_ADDRESS                  0x0800FC10
#define BANK1_STATUS_ADDRESS          			    0x0800FC14
#define BANK1_SIZE_ADDRESS                   		0x0800FC18
#define BANK1_CRC_ADDRESS                    		0x0800FC1C


#define ADDRESS_OF_STARTUP_BANK2              		0x08008800
#define ADDRESS_OF_BANK2                      		0x08008804
#define NUMBER_OF_FIRST_PAGE_IN_BANK2		    	34
#define NUMBER_OF_LAST_PAGE_IN_BANK2		     	62
#define BANK2_CONTROL_PAGE_ADDRESS                 	0x0800FC30
#define BANK2_STATUS_ADDRESS                 		0x0800FC34
#define BANK2_SIZE_ADDRESS                   		0x0800FC38
#define BANK2_CRC_ADDRESS                    		0x0800FC3C


#define CONTROL_PAGE_NUMBER                         63


#define BL_SPECIFYING_BANK_FLAG                   	0x0800FC00





#define UDS_MCU_ACKNOWLEDGE_UPGRADE_REQUEST         0x50
#define UDS_GWY_PROVIDE_HEADER                      0x34
#define UDS_MCU_ACCEPT_RECEIVING_HEADER             0x73
#define UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED         0x74
#define UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE     0x75
#define UDS_GWY_REQUEST_SENDING_LINE_OF_CODE        0x36
#define UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED   0x76
#define UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE  0x37
#define UDS_GWY_ACKNOWLEDGE_FINISHING               0x04
#define UDS_MCU_ACKNOWLEDGE_FINISHING               0x77


#define SHIFT_LEFT_24_BIT                        	24
#define SHIFT_LEFT_16_BIT                        	16
#define SHIFT_LEFT_8_BIT                         	8



#define BOOTLOADER_APP_IS_IN_BANK1                  0xFFFFFFF1
#define BOOTLOADER_BANK_APPROPRIATE                 0xFFFFFFF2
#define BOOTLOADER_BACKUP_IS_IN_BANK2               0xFFFFFFF3
#define BOOTLOADER_BANK_NOT_APPROPRIATE             0xFFFFFFF4


#define BOOTLOADER_APP_IS_NOT_APPROPRIATE_OR_NOT_EXISTING        		   1
#define BOOTLOADER_APP_IS_APPROPRIATE_OR_EXISTING                          0


#define RESET_SPECIFYING_FLAG                     	0xFFFFFFFF
#define SET_SPECIFYING_FLAG                       	0x00000000


#define BOOTLOADER_IS_ZERO                     		0
#define BOOTLOADER_NOT_FIRST_FLASH                  1


#define BOOTLOADER_INIT_NOT_APPROPRIATE             0xFFFFFFF3
#define WORD_SIZE                           		4











#endif /* INC_BOOTLOADER_PRIVATE_H_ */
