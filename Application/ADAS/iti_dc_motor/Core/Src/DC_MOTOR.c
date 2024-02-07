/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_Program.c                                                         */
/*  Description  :   Functions Implementation of the DCM  Driver                           */
/*  Author       :   AYA_MOHAMED                                                           */
/*  Date         :   31/1/2024                                                             */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/


#include "main.h"
#include "DCM_Config.h"
#include "DCM_Interface.h"

#define PIN_LEVEL_HIGH  1
#define PIN_LEVEL_LOW   0

uint8_t  flag=0;

/*@Name          DCM_Init
 *@Arguments     void
 *@Return        no return
 *@Description   this function is used to init the timers with specific channel
 *
 */

void DCM_Init(void){

	  HAL_TIM_PWM_Start(&htim2, DCM_1_SPEED_CHANNEL);
	  HAL_TIM_PWM_Start(&htim2, DCM_2_SPEED_CHANNEL);


}


/*@Name          DCM_Move
 *@Arguments     DCM_Number specifies the motor number of type @DCM_Index
				 Duty_Cycle specifies the motor duty cycle(speed from user) of type @u8
                 Direction  specifies the motor direction  of type @DCM_DirectionType
 *@Return        no return 
 *@Description   this function is used to Move the motor with specific speed and directionDuty_Cycle specifies the motor duty cycle of type @u8
 * 
 */

void DCM_Move(uint8_t  DCM_Number,uint8_t Duty_Cycle,DCM_DirectionType Direction){

	if(DCM_Number == DCM_RIGHT_SIDE){
		  __HAL_TIM_SET_COMPARE(&htim2,DCM_1_SPEED_CHANNEL,Duty_Cycle);//control speed
		if(Direction == DCM_FORWARD){
			HAL_GPIO_WritePin(DCM_1_IN1_PORT_ID,DCM_1_IN1_PIN_ID, PIN_LEVEL_HIGH);
			HAL_GPIO_WritePin(DCM_1_IN2_PORT_ID,DCM_1_IN2_PIN_ID,PIN_LEVEL_LOW);
		}
		else if(Direction == DCM_REVERSE){
			HAL_GPIO_WritePin(DCM_1_IN1_PORT_ID,DCM_1_IN1_PIN_ID, PIN_LEVEL_LOW);
			HAL_GPIO_WritePin(DCM_1_IN2_PORT_ID,DCM_1_IN2_PIN_ID,PIN_LEVEL_HIGH);
		}
	}
	else if(DCM_Number == DCM_LEFT_SIDE){

		  __HAL_TIM_SET_COMPARE(&htim2,DCM_2_SPEED_CHANNEL,Duty_Cycle);//control speed
		if(Direction == DCM_FORWARD){
			HAL_GPIO_WritePin(DCM_2_IN1_PORT_ID,DCM_2_IN1_PIN_ID,PIN_LEVEL_HIGH);
			HAL_GPIO_WritePin(DCM_2_IN1_PORT_ID,DCM_2_IN2_PIN_ID,PIN_LEVEL_LOW);
		}
		else if(Direction == DCM_REVERSE){
			HAL_GPIO_WritePin(DCM_2_IN1_PORT_ID,DCM_2_IN1_PIN_ID,PIN_LEVEL_LOW);
			HAL_GPIO_WritePin(DCM_2_IN1_PORT_ID,DCM_2_IN2_PIN_ID,PIN_LEVEL_HIGH);
		}
	}
}

/*
  @Name     	   DCM_Stop
  @Arguments       DCM_Number specifies the motor number of type @DCM_Index
  @Return          no return
  @Description     this function is used to stop the motor
 */
void DCM_Stop(uint8_t  DCM_Number){

	if(DCM_Number == DCM_RIGHT_SIDE){
		  HAL_TIM_PWM_Stop(&htim2, DCM_1_SPEED_CHANNEL);
	}
	else if(DCM_Number == DCM_LEFT_SIDE){
		  HAL_TIM_PWM_Stop(&htim2, DCM_2_SPEED_CHANNEL);

	}
}

/*@Name       	  App_CarMoveForward
 *@Arguments      Speed specifies the speed of the car and this variable of type @u8
 *@Return         no return
 *@Description    this function is used to move the car forward
 */
uint8_t App_CarMoveForward( uint8_t Speed){
	flag=1;
	DCM_Move(DCM_RIGHT_SIDE,Speed,DCM_FORWARD);
	DCM_Move(DCM_LEFT_SIDE,Speed,DCM_FORWARD);
	return Speed;
}


/*@Name          App_CarMoveReverse
 *@Arguments     Speed specifies the speed of the car and this variable of type @u8
 *@Return        no return
 *@Description   this function is used to move the car in reverse direction
 */
uint8_t  App_CarMoveReverse(uint8_t Speed){
	flag=2;

	DCM_Move(DCM_RIGHT_SIDE,Speed,DCM_REVERSE);
	DCM_Move(DCM_LEFT_SIDE,Speed,DCM_REVERSE);
	return Speed;

}

/*@Name       	 App_CarMoveRight
 *@Arguments     Speed specifies the speed of the car and this variable of type @u8
 *@Return        no return
 *@Description   this function is used to move the car right
 */
uint8_t App_CarMoveRight(uint8_t Speed){
	flag=3;

	DCM_Move(DCM_RIGHT_SIDE,Speed,DCM_REVERSE);
	DCM_Move(DCM_LEFT_SIDE,Speed,DCM_FORWARD);
	return Speed;


}

/*
 *@Name       	 App_CarMoveLeft
 *@Arguments     Speed specifies the speed of the car and this variable of type @u8
 *@Return        no return
 *@Description   this function is used to move the car left
 */
uint8_t  App_CarMoveLeft(uint8_t Speed){
	flag=4;
	DCM_Move(DCM_RIGHT_SIDE,Speed,DCM_FORWARD);
	DCM_Move(DCM_LEFT_SIDE,Speed,DCM_REVERSE);

	return Speed;
}

/*@Name       	 App_CarStop
 *@Arguments     Speed specifies the speed of the car and this variable of type @u8
 *@Return        no return
 *@Description   this function is used to stop the car
 */
void App_CarStop(){
	DCM_Stop(DCM_LEFT_SIDE);
	DCM_Stop(DCM_RIGHT_SIDE);
}



uint8_t App_SendDuty(void)
{
	uint8_t local_var;
   switch (flag)
   {

   case 1:
	   local_var= App_CarMoveForward(uint8_t Speed); break;
   case 2:
	    local_var=App_CarMoveReverse(uint8_t Speed); break;
   case 3:
	   local_var=App_CarMoveRight(uint8_t Speed);   break;
   case 4:
	   local_var=App_CarMoveLeft(uint8_t Speed);   break;
	  //default:
    // code block
   }
    return  local_var;

}


