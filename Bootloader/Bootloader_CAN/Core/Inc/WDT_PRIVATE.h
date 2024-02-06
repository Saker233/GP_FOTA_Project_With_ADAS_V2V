/*******************************************************************************
**  FILENAME     : WDT_PRIVATE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : WDT Driver PRIVATE file                                     **
**                                                                            **
*******************************************************************************/

#ifndef INC_WDT_PRIVATE_H_
#define INC_WDT_PRIVATE_H_

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Important Constant
#define IWDT_ACCESS_PR_RLR_KEY  0x5555
#define IWDT_ENABLE_IWDT        0xCCCC
#define IWDT_REFRESH_IWDT       0xAAAA
#define WWDT_REQUEST_SW_RESET   0xBF
/*!<**************************PORTS Base Address*******************************/
#define IWDT_BASE_ADDRESS       0x40003000
#define WWDT_BASE_ADDRESS       0x40002C00
/*!<**************************Offset Definition********************************/
// IWDT
#define KR                      0X00
#define PR                      0X04
#define RLR                     0X08
#define SR                      0X0C
// WWDT
#define CR                      0X00
#define CFR                     0X04
#define WSR                     0X08
/*!<***************************Bite Definitions*********************************/
// IWDT
#define PUV                     0
#define RUV                     1
// WWDT
#define WDGA                    7
#define WDGTB0                  7
#define WDGTB1                  8
#define EVI                     9
#define EVIF                    0
#define T6                      6



/******************************************************************************
* Configuration Constants
*******************************************************************************/
/*!<***************************Register Address********************************/
// IWDT
#define IWDT_KR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + KR))
#define IWDT_PR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + PR))
#define IWDT_RLR                *((volatile u32 *)(IWDT_BASE_ADDRESS + RLR))
#define IWDT_SR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + SR))
// WWDT
#define WWDT_CR           		*((volatile u32 *)(WWDT_BASE_ADDRESS + CR))
#define WWDT_CFR          		*((volatile u32 *)(WWDT_BASE_ADDRESS + CFR))
#define WWDT_SR          		*((volatile u32 *)(WWDT_BASE_ADDRESS + WSR))




























#endif /* INC_WDT_PRIVATE_H_ */
