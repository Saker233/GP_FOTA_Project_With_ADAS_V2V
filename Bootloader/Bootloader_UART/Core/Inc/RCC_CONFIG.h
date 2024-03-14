/*******************************************************************************
**  FILENAME     : RCC_CONFIG.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : RCC Driver CONFIG file                                     **
**                                                                            **
*******************************************************************************/

#ifndef INC_RCC_CONFIG_H_
#define INC_RCC_CONFIG_H_

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define RCC_CLOCK_TYPE    RCC_HSI

#if RCC_CLOCK_TYPE == RCC_PLL
   #define RCC_PLL_INPUT     RCC_PLL_IN_HSI_DIV_2
   #if RCC_PLL_INPUT == RCC_PLL_IN_HSE
      #define RCC_PLL_HSE       RCC_PLL_HSE_CRYSTAL
   #endif
   #define RCC_PLL_MUL_VAL   RCC_PLLMULL2
#endif


#define RCC_HPRE_DIV_VAL   RCC_HPRE_DIV1

#define RCC_PPRE1_DIV_VAL   RCC_PPRE1_DIV1

#define RCC_PPRE2_DIV_VAL   RCC_PPRE2_DIV1


#define RCC_ADCPRE_DIV_VAL   RCC_ADCPRE_DIV2


#define RCC_MCO_CLK         RCC_MCO_NO_CLK


#endif /* INC_RCC_CONFIG_H_ */
