/*******************************************************************************************/
/*  Module       :   Vehicle to Vehicle Communication (V2V)                                */
/*  File Name    :   V2V_Interface.h                                                       */
/*  Description  :   Interface File of the V2V  Driver                                     */
/*  Author       :   AHMED_REDA                                                            */
/*  Date         :   2/2/2024                                                             */
/*******************************************************************************************/

#ifndef SRC_V2V_INTERFACE_H_
#define SRC_V2V_INTERFACE_H_

/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/

#include "nrf24l01p.h"

typedef enum V2V_state
{
	RECIEVER = 0,TRANSMITTER

}V2VState_t;


void V2V_voidInit(V2VState_t state);
void V2V_voidSendData(uint8_t* Copy_u8Data);
uint8_t V2V_u8RecieveData(uint8_t * Copy_p8Buffer );











#endif /* SRC_V2V_INTERFACE_H_ */
