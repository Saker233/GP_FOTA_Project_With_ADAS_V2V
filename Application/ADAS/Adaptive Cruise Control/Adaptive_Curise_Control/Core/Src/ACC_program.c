/*******************************************************************************************/
/*  Module       :   Adaptive Cruise Control                                               */
/*  File Name    :   ACC_Program.c                                                         */
/*  Description  :   Functions Implementation of the ACC Component                         */
/*  Author       :   AHMED_REDA & AHMED KHALED                                             */
/*  Date         :   2/2/2024                                                              */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/


/*HAL LAYER*/
#include "main.h"
#include "UltraSonic.h"
#include "DCM_Interface.h"
#include "V2V_interface.h"
#include "ACC_config.h"
#include "ACC_private.h"
#include "ACC_interface.h"
uint8_t static buffer [NRF24L01P_PAYLOAD_LENGTH] = {0};
void ACC_voidInit(void)
{
	DCM_Init();
#if (CAR == FRONT)
	V2V_voidInit(TRANSMITTER);

#elif (CAR == BACK)
	V2V_voidInit(RECIEVER);
#endif
	UltraSonic_voidInit();
}

void ACC_voidRun(void)
{

#if (CAR == FRONT)
	App_CarMoveForward(80);
	uint8_t Local_u8Dis_carf = HCSR04_Read();
	uint8_t Local_u8Speed_carf = Send_Speed();
	if (Local_u8Dis_carf <= 10 )
	{
		App_CarStop();
		HAL_Delay(1000);
	}
	buffer[0] = Local_u8Dis_carf;
	buffer[1] = Local_u8Speed_carf;
	V2V_voidSendData(buffer);
#elif (CAR == BACK)
	App_CarMoveForward(70);
	uint8_t Local_u8Dis_carb = HCSR04_Read();
	uint8_t Local_u8RecievedDis;
	uint8_t Local_u8RecievedSpeed;
	if (Local_u8Dis_carb <= 20 )
	{
		App_CarStop();
		HAL_Delay(2000);
	}
	if (V2V_u8RecieveData(buffer) == 1)
	{
		Local_u8RecievedDis = buffer[0];
		Local_u8RecievedSpeed = buffer[1];

		 if (Local_u8Dis_carb <=20)
		{

			if (Local_u8RecievedDis <=10)
			{
				App_CarMoveForward(0);
			}
			else
			{
				App_CarMoveForward(Local_u8RecievedSpeed);
			}

		}
		else
		{

		}


	}
	else
	{
		/* Like Front Car depending on Distance using Ultrasonic only*/
	}

#endif




}








