/*******************************************************************************************/
/*  Module       :   Adaptive Cruise Control                                               */
/*  File Name    :   ACC_interface.h                                                       */
/*  Description  :   Interface file for the ACC Component                                  */
/*  Author       :   AHMED_REDA & AHMED KHALED                                             */
/*  Date         :   2/2/2024                                                              */
/*******************************************************************************************/

#ifndef SRC_ACC_INTERFACE_H_
#define SRC_ACC_INTERFACE_H_





#define CAR      FRONT           // FRONT or BACK


/********************************************************************************
 * Name : ACC_voidInit
 * Arguments : Void
 * Return : Void
 * Description :  The purpose of this function is to initialize various modules
 *   or components typically used in an Advanced Cruise Control (ACC) system.
 *   It initializes modules related to motor control (DCM_Init()),
 *   vehicle-to-vehicle communication (V2V_voidInit()),
 *   and ultrasonic sensors (UltraSonic_voidInit()).
 ********************************************************************************/



void ACC_voidInit(void);



/********************************************************************************
 * Name : ACC_voidRun
 * Arguments : Void
 * Return : Void
 * Description :  The purpose of the ACC_voidRun() function is to control the behavior
 *  of a vehicle in an Advanced Cruise Control (ACC) system based on its position
 *  within a convoy or similar setup. It includes logic for moving the vehicle
 *  forward, stopping it when necessary based on distance readings from ultrasonic
 *  sensors, and communicating with the preceding vehicle in the convoy using a
 *  vehicle-to-vehicle communication module.
 ********************************************************************************/


void ACC_voidRun(void);




#endif /* SRC_ACC_INTERFACE_H_ */
