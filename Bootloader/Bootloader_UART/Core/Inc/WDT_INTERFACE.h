/*******************************************************************************
**  FILENAME     : WDT_INTERFACE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : WDT Driver INTERFACE file                                     **
**                                                                            **
*******************************************************************************/

#ifndef INC_WDT_INTERFACE_H_
#define INC_WDT_INTERFACE_H_

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void IWDT_voidChangePrescaler(u8 Copy_u8Divisor);
void IWDT_voidEnableIwdtWithMaxValue(void);
void IWDT_voidEnableIwdtWithGivenValue(u16 Copy_u16ReloadValue);
void IWDT_voidRefreshIwdtWithValue(void);
void IWDT_voidMakeSoftWareReset(void);
void WWDT_voidMakeSoftWareReset(void);

#endif /* INC_WDT_INTERFACE_H_ */
