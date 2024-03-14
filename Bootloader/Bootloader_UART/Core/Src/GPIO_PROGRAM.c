/*******************************************************************************
**  FILENAME     : GPIO_INTERFACE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : GPIO Driver INTERFACE file                                     **
**                                                                            **
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO_PRIVATE.h"
#include "GPIO_INTERFACE.h"
#include "GPIO_CONFIG.h"





/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
 *
 * @param copy_u8PinId
 * @param copy_u8Mode
 */
void MGPIO_voidSetPinMode( GPIO_PinId_t copy_u8PinId , GPIO_PIN_MODE copy_u8Mode)
{
	GPIO_PortId_t copy_u8PortId;
	    if(copy_u8PinId >= GPIO_PORTA_ENTRY && copy_u8PinId <= GPIO_PORTA_END)
	    {
	        copy_u8PortId = PORTA;
	    }
	    else if(copy_u8PinId >= GPIO_PORTB_ENTRY && copy_u8PinId <= GPIO_PORTB_END)
	    {
	        copy_u8PortId = PORTB;
	        copy_u8PinId -= GPIO_ADJUST_PORTB_PIN;
	    }
	    else if(copy_u8PinId >= GPIO_PORTC_ENTRY && copy_u8PinId <= GPIO_PORTC_END)
	    {
	        copy_u8PortId = PORTC;
	        copy_u8PinId -= GPIO_ADJUST_PORTC_PIN;
	    }
	    else
	    {
	        /*!<TODO: Error Codes*/
	    }

	    switch (copy_u8PortId)
	    {
	        case PORTA :
	           if(copy_u8PinId <= GPIO_PORT_MIDDLE)
	           {
	               GPIOA_CRL &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOA_CRL |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else if(copy_u8PinId <= GPIO_PORT_END)
	           {
	               copy_u8PinId -= GPIO_ADJUST_BIT;
	               GPIOA_CRH &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOA_CRH |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else
	           {
	               /*!<TODO: Error Codes*/
	           }
	        break;
	        case PORTB :
	           if(copy_u8PinId <= GPIO_PORT_MIDDLE)
	           {
	               GPIOB_CRL &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOB_CRL |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else if(copy_u8PinId <= GPIO_PORT_END)
	           {
	               copy_u8PinId -= GPIO_ADJUST_BIT;
	               GPIOB_CRH &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOB_CRH |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else
	           {
	               /*!<TODO: Error Codes*/
	           }
	        break;
	        case PORTC :
	           if(copy_u8PinId <= GPIO_PORT_MIDDLE)
	           {
	               GPIOC_CRL &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOC_CRL |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else if(copy_u8PinId <= GPIO_PORT_END)
	           {
	               copy_u8PinId -= GPIO_ADJUST_BIT;
	               GPIOC_CRH &= ~ ((GPIO_CLR_MODE) << (GPIO_SHIFT_BIT * copy_u8PinId));
	               GPIOC_CRH |=   ((copy_u8Mode)   << (GPIO_SHIFT_BIT * copy_u8PinId));
	           }
	           else
	           {
	               /*!<TODO: Error Codes*/
	           }
	        break;
	        default :
	            /*TODO: Error Codes*/
	        break;
	    }
}
/**
 *
 * @param copy_u8PinId
 * @param copy_u8Value
 */
void MGPIO_voidSetPinValue(GPIO_PinId_t copy_u8PinId , u8 copy_u8Value)
{
	GPIO_PortId_t copy_u8PortId;
	    if(copy_u8PinId >= GPIO_PORTA_ENTRY && copy_u8PinId <= GPIO_PORTA_END)
	    {
	        copy_u8PortId = PORTA;
	    }
	    else if(copy_u8PinId >= GPIO_PORTB_ENTRY && copy_u8PinId <= GPIO_PORTB_END)
	    {
	        copy_u8PortId = PORTB;
	        copy_u8PinId -= GPIO_ADJUST_PORTB_PIN;
	    }
	    else if(copy_u8PinId >= GPIO_PORTC_ENTRY && copy_u8PinId <= GPIO_PORTC_END)
	    {
	        copy_u8PortId = PORTC;
	        copy_u8PinId -= GPIO_ADJUST_PORTC_PIN;
	    }
	    else
	    {
	        /*!<TODO: Error Codes*/
	    }
	    if(copy_u8PinId <= GPIO_PORT_END)
	    {
	        switch(copy_u8PortId)
	        {
	            case PORTA :
	                switch(copy_u8Value)
	                {
	                    case LOW  : GPIOA_BRR = SET << copy_u8PinId;break;
	                    case HIGH : GPIOA_BSR = SET << copy_u8PinId;break;
	                }
	            break;
	            case PORTB :
	                switch(copy_u8Value)
	                {
	                    case LOW  : GPIOB_BRR = SET << copy_u8PinId;break;
	                    case HIGH : GPIOB_BSR = SET << copy_u8PinId;break;
	                }
	            break;
	            case PORTC :
	                switch(copy_u8Value)
	                {
	                    case LOW  : GPIOC_BRR = SET << copy_u8PinId;break;
	                    case HIGH : GPIOC_BSR = SET << copy_u8PinId;break;
	                }
	            break;
	            default :
	                /*TODO: Error Codes*/
	            break;
	        }
	    }
	    else
	    {
	        /*TODO: Error Codes*/
	    }
}
/**
 *
 * @param copy_u8PinId
 * @return
 */
u8   MGPIO_u8GetPinValue(GPIO_PinId_t copy_u8PinId)
{
	u8 u8_value = 0;
	    GPIO_PortId_t copy_u8PortId;
	    if(copy_u8PinId >= GPIO_PORTA_ENTRY && copy_u8PinId <= GPIO_PORTA_END)
	    {
	        copy_u8PortId = PORTA;
	    }
	    else if(copy_u8PinId >= GPIO_PORTB_ENTRY && copy_u8PinId <= GPIO_PORTB_END)
	    {
	        copy_u8PortId = PORTB;
	        copy_u8PinId -= GPIO_ADJUST_PORTB_PIN;
	    }
	    else if(copy_u8PinId >= GPIO_PORTC_ENTRY && copy_u8PinId <= GPIO_PORTC_END)
	    {
	        copy_u8PortId = PORTC;
	        copy_u8PinId -= GPIO_ADJUST_PORTC_PIN;
	    }
	    else
	    {
	        /*!<TODO: Error Codes*/
	    }
	    if(copy_u8PinId <= GPIO_PORT_END)
	    {
	        switch(copy_u8PortId)
	        {
	            case PORTA :
	                u8_value = GET_BIT(GPIOA_IDR, copy_u8PinId);
	            break;
	            case PORTB :
	                u8_value = GET_BIT(GPIOB_IDR, copy_u8PinId);
	            break;
	            case PORTC :
	                u8_value = GET_BIT(GPIOC_IDR, copy_u8PinId);
	            break;
	            default :
	                /*TODO: Error Codes*/
	            break;
	        }
	    }
	    else
	    {
	        /*TODO: Error Codes*/
	    }

	    return u8_value;
}
