/*******************************************************************************************/
/*  Module       :   Adaptive Cruise Control                                               */
/*  File Name    :   ACC_Program.c                                                         */
/*  Description  :   Functions Implementation of the ACC Component                         */
/*  Author       :   AHMED_REDA  & AHMED kHALED                                            */
/*  Date         :   2/2/2024                                                              */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/


/*HAL LAYER */
#include "main.h"
#include "V2V_interface.h"
#include "V2V_private.h"
#include "V2V_config.h"

volatile static uint8_t recieved_flag = 0;
static uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH] = {0};
static uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};
static V2VState_t g_state =RECIEVER ;
void V2V_voidInit(V2VState_t state)
{
	if (state == RECIEVER)
	{
		nrf24l01p_rx_init(2500, _1Mbps);
		g_state = RECIEVER;
	}
	else if (state == TRANSMITTER)
	{
		nrf24l01p_tx_init(2500, _1Mbps);
		g_state = TRANSMITTER;
	}
	else
	{

	}

}

void V2V_voidSendData(uint8_t* Copy_u8Data)
{
	nrf24l01p_tx_transmit(Copy_u8Data);
	 HAL_Delay(100);


}
uint8_t V2V_u8RecieveData(uint8_t * Copy_p8Buffer )
{
	if(recieved_flag == 1)
	{
		 for (uint8_t Local_u8Iterator = 0; Local_u8Iterator<NRF24L01P_PAYLOAD_LENGTH;Local_u8Iterator++)
		 {
			 Copy_p8Buffer[Local_u8Iterator]  = rx_data[Local_u8Iterator];
		 }
		 return 1;
	}
	else
	{
		return 0;
	}


}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
	{
		if (  g_state == RECIEVER )
		{
			nrf24l01p_rx_receive(rx_data);
			recieved_flag = 1;
		}

		else if (g_state == TRANSMITTER )
		{
			nrf24l01p_tx_irq();
		}

	}

}


