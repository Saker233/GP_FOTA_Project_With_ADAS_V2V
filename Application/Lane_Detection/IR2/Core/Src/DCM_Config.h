/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_CONFIG.h                                                       */
/*  Description  :   CONFIG File of the DCM  Driver                                     */
/*  Author       :   AYA_MOHAMED                                                           */
/*  Date         :   31/1/2024                                                             */
/*******************************************************************************************/

#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_


/*  TIM_CHANNEL_1
 *  TIM_CHANNEL_2
 *  TIM_CHANNEL_3
 *  TIM_CHANNEL_4
 *  TIM_CHANNEL_ALLt
 *
 * */

#define   NUMBER_OF_DC_MOTOR                                2

#define   DCM_1_SPEED_CHANNEL                          TIM_CHANNEL_1
#define   DCM_1_SPEED_PORT_ID                          GPIOA
#define   DCM_1_SPEED_PIN_ID                           GPIO_PIN_0

#define   DCM_1_IN1_PORT_ID                            GPIOA
#define   DCM_1_IN1_PIN_ID                             GPIO_PIN_4
#define   DCM_1_IN2_PORT_ID                            GPIOA
#define   DCM_1_IN2_PIN_ID                             GPIO_PIN_5


#define   DCM_2_SPEED_CHANNEL                          TIM_CHANNEL_2
#define   DCM_2_SPEED_PORT_ID                          GPIOA
#define   DCM_2_SPEED_PIN_ID                           GPIO_PIN_1

#define   DCM_2_IN1_PORT_ID                            GPIOA
#define   DCM_2_IN1_PIN_ID                             GPIO_PIN_6
#define   DCM_2_IN2_PORT_ID                            GPIOA
#define   DCM_2_IN2_PIN_ID                             GPIO_PIN_7

#endif /* DCM_CONFIG_H_ */

