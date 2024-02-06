/*******************************************************************************************/
/*  Module       :   Ultrasonic                                                            */
/*  File Name    :   Ultrasonic.h                                                          */
/*  Description  :   Interface File of the Ultrasonic  Driver                              */
/*  Author       :   AHMED_REDA & AHMED_KHALED                                             */
/*  Date         :   3/2/2024                                                              */
/*******************************************************************************************/

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_


#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOA

/*  MX Configuration :
 *  Timer 1 Channel 1 --> choose input capture direct mode
 *	                  --> Parameter settings :
 *	                  - Prescaler = the clock source (16 MHz --> Prescaler 16)
 *	                  - Polarity Selection --> Rising Edge
 * 	                  --> Counter Period autoreload = 0xFFFF-1
 * 	                  --> NVIC Settings --> Enable Timer 1 Capture Compare Interrupt
 *
 * 	Set any Pin as Tigger pin output and change here
 *
 *
 *
 */






uint8_t HCSR04_Read (void);
void UltraSonic_voidInit (TIM_HandleTypeDef htim);

#endif /* SRC_ULTRASONIC_H_ */
