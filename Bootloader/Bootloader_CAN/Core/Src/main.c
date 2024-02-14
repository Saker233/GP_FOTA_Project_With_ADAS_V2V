/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include <stdlib.h>
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "Bootloader_INTERFACE.h"
#include "CANIF_INTERFACE.h"
#include "CAN_INTERFACE.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
volatile extern CAN_InitTypeDef             CAN_InitStruct;
volatile extern CAN_FilterInitTypeDef       CAN_FilterInitStruct_0;
//volatile extern CAN_FilterInitTypeDef       CAN_FilterInitStruct_4;




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* Initialize all configured peripherals */
  MRCC_voidInitSysClock();
  MRCC_voidEnableClock(RCC_APB2, IOPA_PERIPHERAL); // port a
  MRCC_voidEnableClock(RCC_AHB, CRCE_PERIPHERAL); // crc clock
  MRCC_voidEnableClock(RCC_AHB, FLITF_PERIPHERAL); //flash clock
  MRCC_voidEnableClock(RCC_APB1, CAN_PERIPHERAL);

  MGPIO_voidSetPinMode( PINA12, AFIO_OUTPUT_2M_PULL_UP_DN);
  MGPIO_voidSetPinMode(PINA11, GPIO_INPUT_FLOATING);


  CAN_VoidInit(CAN1, &CAN_InitStruct);

  CAN_VoidFilterSet(&CAN_FilterInitStruct_0, CAN1);
  //CAN_VoidFilterSet(&CAN_FilterInitStruct_4, CAN1);

  BL_voidSpecify_Bank();

}

