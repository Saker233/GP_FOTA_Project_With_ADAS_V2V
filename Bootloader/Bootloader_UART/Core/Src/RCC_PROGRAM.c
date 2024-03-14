/*******************************************************************************
**  FILENAME     : RCC_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : RCC Driver program file                                     **
**                                                                            **
*******************************************************************************/


/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_PRIVATE.h"
#include "RCC_INTERFACE.h"
#include "RCC_CONFIG.h"

/* This function is used to enable the clock for the chosen perpheral */
void MRCC_voidEnableClock(u8 Copy_u8BusId,  u8 Copy_u8BperId)
{
    if(Copy_u8BperId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : SET_BIT(RCC_AHBENR,  Copy_u8BperId); break;
			case RCC_APB1 : SET_BIT(RCC_APB1ENR, Copy_u8BperId); break;
			case RCC_APB2 : SET_BIT(RCC_APB2ENR, Copy_u8BperId); break;
			//default       : /*TODO: Return Error Code*/          break;

		}
	}
	else
	{
		//TODO: Return Error Code
	}
}
/* This function is used to disable the clock for the chosen perpheral */
void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8BperId)
{
    if(Copy_u8BperId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : CLR_BIT(RCC_AHBENR,  Copy_u8BperId); break;
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR, Copy_u8BperId); break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR, Copy_u8BperId); break;
			//default       : /*TODO: Return Error Code*/          break;
		}
	}
	else
	{
		//TODO: Return Error Code
	}
}
/* This function is used to select clock source for processor */
void MRCC_voidInitSysClock(void)
{
	RCC_CR   = 0X00000080;                    /*CLEAR REG + Triming = 0  */
	RCC_CFGR = 0X00000000;                    /*CLEAR REG */
	#if  RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	    SET_BIT(RCC_CR, RCC_CR_CSSON);
		SET_BIT(RCC_CR, RCC_CR_HSEON);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
		RCC_CFGR |= RCC_CFGR_SW_HSE;
	#elif  RCC_CLOCK_TYPE == RCC_HSE_RC
	    SET_BIT(RCC_CR, RCC_CR_CSSON);
	    SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		SET_BIT(RCC_CR, RCC_CR_HSEON);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
		RCC_CFGR |= RCC_CFGR_SW_HSE;
	#elif  RCC_CLOCK_TYPE == RCC_HSI
	    SET_BIT(RCC_CR, RCC_CR_HSION);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
        RCC_CFGR |= RCC_CFGR_SW_HSI;
	#elif  RCC_CLOCK_TYPE == RCC_PLL
        #if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
		    SET_BIT(RCC_CR, RCC_CR_HSION);
		    while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
            RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
	    #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
		    #if   RCC_PLL_HSE == RCC_PLL_HSE_CRYSTAL
               SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#elif RCC_PLL_HSE == RCC_PLL_HSE_RC
               SET_BIT(RCC_CR, RCC_CR_CSSON);
	           SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!GET_BIT(RCC_CR, RCC_CR_HSERDY));
            #else
			   #warning("Wrong PLL input from HSE...crystal is default")
			   SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#endif
            RCC_CFGR |= RCC_CFGR_PLLXTPRE_HSE_Div2;
	    #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
		    #if   RCC_PLL_HSE == RCC_PLL_HSE_CRYSTAL
               SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#elif RCC_PLL_HSE == RCC_PLL_HSE_RC
               SET_BIT(RCC_CR, RCC_CR_CSSON);
	           SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!GET_BIT(RCC_CR, RCC_CR_HSERDY)));
            #else
			   #warning("Wrong PLL input from HSE...crystal is default")
			   SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#endif
            RCC_CFGR |= RCC_CFGR_PLLSRC_HSE;
		#else
            #warning("Wrong PLL Input....HSI is dinput for PLL by default")
			RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
		#endif
		#if   RCC_PLL_MUL_VAL == RCC_PLLMULL2
            RCC_CFGR |= RCC_CFGR_PLLMULL2
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL3
            RCC_CFGR |= RCC_CFGR_PLLMULL3
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL4
            RCC_CFGR |= RCC_CFGR_PLLMULL4
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL5
            RCC_CFGR |= RCC_CFGR_PLLMULL5
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL6
            RCC_CFGR |= RCC_CFGR_PLLMULL6
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL7
            RCC_CFGR |= RCC_CFGR_PLLMULL7
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL8
            RCC_CFGR |= RCC_CFGR_PLLMULL8
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL9
            RCC_CFGR |= RCC_CFGR_PLLMULL9
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL10
            RCC_CFGR |= RCC_CFGR_PLLMULL10
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL11
            RCC_CFGR |= RCC_CFGR_PLLMULL11
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL12
            RCC_CFGR |= RCC_CFGR_PLLMULL12
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL13
            RCC_CFGR |= RCC_CFGR_PLLMULL13
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL14
            RCC_CFGR |= RCC_CFGR_PLLMULL14
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL15
            RCC_CFGR |= RCC_CFGR_PLLMULL15
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL16
            RCC_CFGR |= RCC_CFGR_PLLMULL16
		#else
            #warning("PLL input clock x 2 by default")
			RCC_CFGR |= RCC_CFGR_PLLMULL2
		#endif
		SET_BIT(RCC_AHBENR, RCC_CR_PLLON);
		while(!(GET_BIT(RCC_CR, RCC_CR_PLLRDY)));
		RCC_CFGR |= RCC_CFGR_SW_PLL;
	#else
	    #warning("Wrong Clock Type/HSI is default")
	    SET_BIT(RCC_CR, RCC_CR_HSION);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
        RCC_CFGR |= RCC_CFGR_SW_HSI;
	#endif
}

void MRCC_voidSetAHBPRE(void)
{
#if   RCC_HPRE_DIV_VAL == RCC_HPRE_DIV1
    RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV2
    RCC_CFGR |= RCC_CFGR_HPRE_DIV2;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV4
    RCC_CFGR |= RCC_CFGR_HPRE_DIV4;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV8
    RCC_CFGR |= RCC_CFGR_HPRE_DIV8;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV16
    RCC_CFGR |= RCC_CFGR_HPRE_DIV16;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV64
    RCC_CFGR |= RCC_CFGR_HPRE_DIV64;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV128
    RCC_CFGR |= RCC_CFGR_HPRE_DIV128;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV256
    RCC_CFGR |= RCC_CFGR_HPRE_DIV256;
#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV512
    RCC_CFGR |= RCC_CFGR_HPRE_DIV512;
#else
    RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
	#warning(Wrong HPRE....DIV1 is default)
#endif
}

void MRCC_voidSetAPB1Pre(void)
{
#if   RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV1
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV1;
#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV2
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV2;
#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV4
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV4;
#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV8
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV8;
#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV16
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV16;
#else
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV1;
	#warning(Wrong PPRE1....DIV1 is default)
#endif
}

void MRCC_voidSetAPB2Pre(void)
{
#if   RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV1
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV2
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV2;
#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV4
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV4;
#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV8
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV8;
#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV16
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV16;
#else
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
	#warning(Wrong PRE2....DIV1 is default)
#endif
}

void MRCC_voidSetADCPre(void)
{
#if   RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV2
    RCC_CFGR |= RCC_CFGR_ADCPRE_DIV2;
#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV4
    RCC_CFGR |= RCC_CFGR_ADCPRE_DIV4;
#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV6
    RCC_CFGR |= RCC_CFGR_ADCPRE_DIV6;
#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV8
    RCC_CFGR |= RCC_CFGR_ADCPRE_DIV8;
#else
    RCC_CFGR_ADCPRE_DIV2;
	#warning(Wrong ADCPRE....DIV2 is default)
#endif
}

void MRCC_voidMcoClk(void)
{
#if   RCC_MCO_CLK == RCC_MCO_NO_CLK
   RCC_CFGR |= RCC_CFGR_MCO_NOCLOCK;
#elif RCC_MCO_CLK == RCC_MCO_SYS_CLK
   RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;
#elif RCC_MCO_CLK == RCC_MCO_HSI_CLK
   RCC_CFGR |= RCC_CFGR_MCO_HSI;
#elif RCC_MCO_CLK == RCC_MCO_HSE_CLK
   RCC_CFGR |= RCC_CFGR_MCO_HSE;
#elif RCC_MCO_CLK == RCC_MCO_PLL_DVID2_CLK
   RCC_CFGR |= RCC_CFGR_MCO_PLL;
#endif //
}
