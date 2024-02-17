/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_Interface.h                                                       */
/*  Description  :   Interface File of the DCM  Driver                                     */
/*  Author       :   AYA_MOHAMED                                                           */
/*  Date         :   31/1/2024                                                             */
/*******************************************************************************************/

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/********************************************************************************************/
/************************************* Included Files ***************************************/
/********************************************************************************************/
#include "DCM_Config.h"

/*******************************************************************************************/
/************************************* Motor Macro *****************************************/
/*******************************************************************************************/
#define    DCM_RIGHT_SIDE                            1
#define    DCM_LEFT_SIDE                             2

/*******************************************************************************************/
/************************************* TypeDefs ********************************************/
/*******************************************************************************************/

typedef enum{
	DCM_FORWARD,DCM_REVERSE
}DCM_DirectionType;

/********************************************************************************************/
/************************************* Extern Configuration *********************************/
/********************************************************************************************/
extern TIM_HandleTypeDef htim2 ;

/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/
void DCM_Init(void);
void DCM_Move(uint8_t  DCM_Number,uint8_t Duty_Cycle, DCM_DirectionType Direction);
void DCM_Stop(uint8_t  DCM_Number);

void App_CarMoveForward(uint8_t Speed);
void App_CarMoveReverse(uint8_t Speed);
void App_CarMoveRight(uint8_t Speed);
void App_CarMoveLeft(uint8_t Speed);
void App_CarStop(void);
void Set_Speed(uint8_t Copy_U8Data);
uint8_t Send_Speed(void);

#endif /* DCM_INTERFACE_H_ */
