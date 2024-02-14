/*******************************************************************************
**  FILENAME     : CAN_CONFIG.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CAN Driver config file                                     **
**                                                                            **
*******************************************************************************/

#ifndef INC_CAN_CONFIG_H_
#define INC_CAN_CONFIG_H_

#include "CAN_PRIVATE.h"
#include "CAN_INTERFACE.h"
#include "STD_TYPES.h"






typedef struct
{
  u16 CAN_Prescaler;  //describe time quantum length

  u8 CAN_MODE;     // describe the operation mode of can driver Loopback

  u8 CAN_SJW;  // describe max number of time quantum

  u8 CAN_BS1;   // describe time quantum in segment 1

  u8 CAN_BS2;   // describe time quantum in segment 2

  FunctionalState CAN_TTCM; //enable  or disable time trigger communication mode

  FunctionalState CAN_ABOM; //Enable or disable the automatic bus-off  management

  FunctionalState CAN_AWUM;  //Enable or disable the automatic wake-up mode

  FunctionalState CAN_NART; //Enable or disable the no-automatic retransmission mode

  FunctionalState CAN_RFLM;  // Enable or disable the Receive FIFO Locked mode

  FunctionalState CAN_TXFP;  // Enable or disable the transmit FIFO priority

} CAN_InitTypeDef;


typedef struct
{
  u32 FilterIdHigh;         /* Specifies the filter identification number (MSBs for a 32-bit
                                       configuration, first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  u32 FilterIdLow;     /* Specifies the filter identification number (LSBs for a 32-bit
                                       configuration, second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  u32 FilterMaskIdHigh;        /* Specifies the filter mask number or identification number,
                                       according to the mode (MSBs for a 32-bit configuration,
                                       first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  u32 FilterMaskIdLow;  /* Specifies the filter mask number or identification number,
                                       according to the mode (LSBs for a 32-bit configuration,
                                       second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  u32 FilterFIFOAssignment;   /* Specifies the FIFO (0 or 1U) which will be assigned to the filter.
                                       This parameter can be a value of @ref CAN_filter_FIFO */

  u32 FilterBank; /* Specifies the filter bank which will be initialized.
                                       For single CAN instance(14 dedicated filter banks),
                                       this parameter must be a number between Min_Data = 0 and Max_Data = 13. */

  u32 FilterMode;		/* Specifies the filter mode to be initialized.
                                       This parameter can be a value of @ref CAN_filter_mode */

  u32 FilterScale;		/* Specifies the filter scale.
                                       This parameter can be a value of @ref CAN_filter_scale */

  FunctionalState CAN_FilterActivation; // specify the state of the filter "ENABLE OR DISABLE"

} CAN_FilterInitTypeDef;








#endif /* INC_CAN_CONFIG_H_ */
