/*******************************************************************************
**  FILENAME     : CAN_INTERFACE.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CAN Driver interface file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_CAN_INTERFACE_H_
#define INC_CAN_INTERFACE_H_

/***************************************************** INCLUDES  **************************************************************************/
#include "CAN_PRIVATE.h"
#include "CAN_CONFIG.h"


/***************************************************** DEFINE MACROS  **************************************************************************/
#define CAN_FilterScale_16bit             ((u8)0x00) /* Two 16-bit filters */
#define CAN_FilterScale_32bit             ((u8)0x01) /* One 32-bit filter */


#define CAN_FilterMode_IdMask            ((u8)0x00)  /* identifier/mask mode */
#define CAN_FilterMode_IdList            ((u8)0x01)  /* identifier list mode */


#define CAN_Filter_FIFO0             ((u8)0x00)  /* Filter FIFO 0 */
#define CAN_Filter_FIFO1             ((u8)0x01)  /* Filter FIFO 1 */

#define CAN_FIFO0                   ((u8)0x00) /* CAN FIFO 0  */
#define CAN_FIFO1                   ((u8)0x01) /* CAN FIFO 1  */

/*****************************************************User-Defined Data Types **************************************************************************/

/* Transmit Data Struct */
typedef struct {

	u8 IDE;  /* 1 -> EXT , 0 -> STAND  */

	u8 RTR;  /* 1 -> Remote , 0 -> Data  */

	u32 ID;  /* MESSAGE IDENTIFIER */

	u8 DATA_LENGHT;  /* DATA LENGTH 0:8 */

	u8 DATA[8];  /* DATA */

}CanTxMsg ;

/* Receive Data Struct */
typedef struct {

	u8 IDE;  /* 1 -> EXT , 0 -> STAND  */

	u8 RTR;  /* 1 -> Remote , 0 -> Data  */

	u32 ID;  /* MESSAGE IDENTIFIER */

	u8 DATA_LENGHT;  /* DATA LENGTH  0:8*/

	u8 DATA[8];  /* DATA */

	u8 FMI;      /* Index of The Filter */

}CanRxMsg ;

volatile typedef struct
{
    /*Reference to CAN Controller */
    CAN_TypeDef*  CanControllerBaseAddress;
    /*This container contains the configuration  */
    CAN_InitTypeDef*  CanHwdefRef;

} Can_ConfigType;


/*****************************************************Funnctions Decalrations **************************************************************************/

/**
 * Initializes the CAN peripheral
 * @param CANx
 * @param CANInitStruct
 */
void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct);


/**
 * Initializes specific filter bank
 * @param CAN_FilterInitStruct
 */
void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct, CAN_TypeDef* CANx);



/**
 * INIT receive message struct to receive can frame
 * in specific FIFO
 * @param CANx
 * @param Copy_u8FifoNumber
 * @param RxMessage
 */
void CAN_VoidReceive(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg* RxMessage);


/**
 * INIT transmit can frame to send it through specific mail box
 * @param CANx
 * @param TxMessage
 * @return
 */
u8 CAN_VoidTransmit(CAN_TypeDef* CANx, CanTxMsg*  TxMessage);


/**
 * Get the last occurred error in "CANx->ESR"register
 * @param CANx
 * @return
 */
u8 CAN_u8GetLastErrorCodeType(CAN_TypeDef* CANx);



/**
 * Enables or disables the specified CANx interrupts.
 * @param CANx
 * @param Copy_u32CanInterruptType
 * @param Copy_u8InterruptNewState
 */
void CAN_VoidInterruptSet(CAN_TypeDef* CANx, u32 Copy_u32CanInterruptType, FunctionalState Copy_u8InterruptNewState);




/**
 * Activate or Deactivate Time trigger Communication mode of a specific mailbox
 * @param CANx
 * @param NewState
 * @param Copy_u8MailBoxNumber
 */
void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , u8 Copy_u8MailBoxNumber);



/**
 * Receive Array of Data
 * @param Copy_u8DataPtr
 * @param Copy_u8DataLenght
 */
void Can_voidSynRecieveArray( u8 *Copy_u8DataPtr ,  u8 Copy_u8DataLenght);



/**
 * Receive only one word in FIFO 0
 * @param CANx
 * @param Copy_u8FifoNumber
 * @return
 */
u32 Can_uint32SynRecieveWord(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber  );




/**
 * Receive only one byte in FIFO 0
 * @param CANx
 * @param Copy_u8FifoNumber
 * @return
 */
u8 Can_u8SynRecieveByte(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber);


























#endif /* INC_CAN_INTERFACE_H_ */
