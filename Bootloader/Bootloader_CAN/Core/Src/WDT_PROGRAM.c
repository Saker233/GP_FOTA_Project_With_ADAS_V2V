/*******************************************************************************
**  FILENAME     : WDT_PROGRAM.c        			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : WDT Driver PRORGAM file                                     **
**                                                                            **
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "WDT_PRIVATE.h"
#include "WDT_INTERFACE.h"
#include "WDT_CONFIG.h"


/******************************************************************************
* Function Definitions
*******************************************************************************/

void IWDT_voidChangePrescaler(u8 Copy_u8Divisor)
{
   CLR_BIT(IWDT_SR, PUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = Copy_u8Divisor;
}



void IWDT_voidEnableIwdtWithMaxValue(void)
{
   IWDT_KR = IWDT_ENABLE_IWDT;
}





void IWDT_voidEnableIwdtWithGivenValue(u16 Copy_u16ReloadValue)
{
   CLR_BIT(IWDT_SR, RUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = Copy_u16ReloadValue;
   IWDT_KR = IWDT_ENABLE_IWDT;
}



void IWDT_voidRefreshIwdtWithValue(void)
{
   IWDT_KR = IWDT_REFRESH_IWDT;
}



void IWDT_voidMakeSoftWareReset(void)
{
   CLR_BIT(IWDT_SR, RUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = 1;
   IWDT_KR = IWDT_ENABLE_IWDT;
}






void WWDT_voidMakeSoftWareReset(void)
{
   WWDT_CR = WWDT_REQUEST_SW_RESET;
}


