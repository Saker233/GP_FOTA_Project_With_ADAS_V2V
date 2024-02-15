/*
 *  Author      : Nada Elsayed
 *  Date        : Feb 1, 2024
 *  Version     : V 1.0
 *  Description : IR_program.h --> Functions Implementation
 *  Peri        : For the Developer only
 */


/**********************************************************
 *						 Includes
 **********************************************************/
//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

#include "stdint.h"
#include "IR_Interface.h"
#include "IR_Config.h"

/**********************************************************
 *				  Functions Implementation
 **********************************************************/

/**********************************************************
 * Name : IR_voidInit
 * Arguments : u8 RIR_PORT, u8 RIR_PIN , u8 LIR_PORT, u8 LIR_PIN
 * Return : void
 * Description : Set the Right , Left IR sensor pin mode as Input
 * 				Enable the internal pull-up resistor for these pins
 * *********************************************************/
/*void IR_voidInit(u8 RIR_PORT, u8 RIR_PIN , u8 LIR_PORT, u8 LIR_PIN)
{
    GPIO_voidSetPinMode(RIR_PORT, RIR_PIN, GPIO_u8INPUT);
    GPIO_voidSetPullType(RIR_PORT, RIR_PIN, GPIO_u8PULLUP);

	GPIO_voidSetPinMode(LIR_PORT, LIR_PIN, GPIO_u8INPUT);
	GPIO_voidSetPullType(LIR_PORT, LIR_PIN, GPIO_u8PULLUP);
}*/

/**********************************************************
 * Name : IR_voidMakeDecision
 * Arguments : u8 RIR_PORT, u8 RIR_PIN , u8 LIR_PORT, u8 LIR_PIN
 * Return : void
 * Description : Make a decision based on the readings of the right
 *               and left IR sensors:
 *               If no obstacle is detected -> continue moving
 *               along the line with necessary speed. 
 *               If an obstacle is detected :
 *               on the right side -> move car left
 *             	 on the left side -> move car right
 * *********************************************************/
void IR_voidMakeDecision(uint8_t* IR_PORT,uint8_t  RIR_PIN ,uint8_t  LIR_PIN)
{
	uint8_t Local_u8RIR_Value = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
	uint8_t Local_u8LIR_Value = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);

	/*as we enable the internal pull up so the pins states would be reversed
	 * so 1 --> indicate to no obstacle &
	 *    0 --> indicate to an obstacle */
    if ((Local_u8RIR_Value == 1) || (Local_u8LIR_Value == 1)) 
	{
        /*If no obstacle -> continue moving along the line*/
       //App_CarMoveForward(50); // Adjust the speed as needed
    }
    else if (Local_u8RIR_Value == 0)
    {
        /*if Obstacle detected*/
        /*App_CarStop();*/
    	/*if for lane detection*/
         //App_CarMoveLeft(50); // Adjust the speed and direction as needed
    }
    else if (Local_u8LIR_Value == 0)
    {
		/*if Obstacle detected*/
		/*App_CarStop();*/
		/*if for lane detection*/
		//App_CarMoveRight(50); // Adjust the speed and direction as needed
	}
}

