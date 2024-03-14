/*
 *  Author      : Aya m.sayed
 *  Date        : march 3, 2024
 *  Version     : V 1.0
 *  Description : IR_program.h --> Functions Implementation
 *  Peri        : For the Developer only
 */


/**********************************************************
 *						 Includes
 **********************************************************/
#include "main.h"
#include "stdint.h"
#include "DCM_Interface.h"

#include "IR_Interface.h"

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

void IR_voidMakeDecision(GPIO_TypeDef * IR_PORT,uint16_t  RIR_PIN ,uint16_t  LIR_PIN)
{

	unsigned char IR1_Read =0, IR2_Read=0;
	IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
	IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);
	/*as we enable the internal pull up so the pins states would be reversed
	 * so 1 --> indicate to  obstacle &--->LED IN IR OFF
	 *    0 --> indicate to  no obstacle--->LED IN IR ON */
	while (1)
	{
		IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
		IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);

		if (( IR1_Read == GPIO_PIN_RESET) && ( IR2_Read == GPIO_PIN_RESET))
		{
			while(( IR1_Read == GPIO_PIN_RESET) && ( IR2_Read == GPIO_PIN_RESET))
			{
				IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
				IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);

				/*If no obstacle -> continue moving along the line*/
			   App_CarMoveForward(40); // Adjust the speed as needed
			}


		}

		else if (( IR1_Read == GPIO_PIN_SET) &&  (IR2_Read == GPIO_PIN_RESET))
		    {
		    	while(( IR1_Read == GPIO_PIN_SET) && (IR2_Read == GPIO_PIN_RESET))
					{
					IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
					IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);
						   //if Obstacle detected/
							App_CarMoveRight(40); // Adjust the speed and direction as needed
							HAL_Delay(700);
							App_CarMoveForward(40);
					}

		    }
		    else if ((IR1_Read == GPIO_PIN_RESET) && (IR2_Read  == GPIO_PIN_SET))
		    {
		    	while((IR1_Read == GPIO_PIN_RESET) && (IR2_Read  == GPIO_PIN_SET))
					{
					IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
					IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);
						//if for lane detection/
							App_CarMoveLeft(40); // Adjust the speed and direction as needed
							HAL_Delay(700);
							App_CarMoveForward(40);
					}
			}
			else
			{

				while((IR1_Read == GPIO_PIN_SET) && (IR2_Read  == GPIO_PIN_SET))
					{
					IR1_Read = HAL_GPIO_ReadPin(IR_PORT, RIR_PIN);
					IR2_Read = HAL_GPIO_ReadPin(IR_PORT, LIR_PIN);
						//if for lane detection/
						App_CarMoveReverse(40);
					}
			}
   }
}
