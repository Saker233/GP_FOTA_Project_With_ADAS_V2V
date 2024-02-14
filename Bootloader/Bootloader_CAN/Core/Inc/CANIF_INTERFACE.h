
/*******************************************************************************
**  FILENAME     : CANIF_INTERFACE.h         			                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CANIF Driver INTERFACE file                                **
**                                                                            **
*******************************************************************************/
#ifndef INC_CANIF_INTERFACE_H_
#define INC_CANIF_INTERFACE_H_

/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/
#include "CAN_INTERFACE.h"
#include "CANIF_PRIVATE.h"
#include "CANIF_CONFIG.h"




/***********************************************************************************/
                      /***FUNCTIONS PROTOTYPES***/
/*********************************************************************************** */


/**
 * Transmit an array of Data
 * @param Copy_u8DataPtr
 * @param Copy_u8DataLenght
 */
Std_ReturnType CanIf_voidTransmitData(u8 *Copy_u8DataPtr , u8 Copy_u8DataLenght);


/**
 * Receive a complete frame
 * @param CANx
 * @param Copy_u8FifoNumber
 * @param RxMessage
 */
Std_ReturnType CanIf_voidReceive_Struct(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg RxMessage);

/**
 * Initialize transmission CAN frame to send it through specific mailbox
 * @param CANx
 * @param TxMessage
 */
Std_ReturnType CanIf_voidTransmit_Struct(CAN_TypeDef* CANx, CanTxMsg TxMessage );

/**
 * Block FIFO until receive only one word
 * @param Copy_u32Word
 */
Std_ReturnType CanIf_voidReceive_Word(u32 *Copy_u32Word);


/**
 * Block FIFO until receive only one byte
 * @param Copy_u8Byte
 */
Std_ReturnType CanIf_voidReceive_Byte(u8*Copy_u8Byte);


/**
 * Block FIFO until receiving is all complete
 * @param Copy_u8DataPtr
 * @param Copy_u8DataLenght
 */
Std_ReturnType CanIf_voidReceive_Block(u8 *Copy_u8DataPtr ,  u16 Copy_u8DataLenght);



/**
 * Transmit only one byte
 * @param Copy_u8Data
 */
Std_ReturnType CanIf_voidTransmit_Byte(u8 Copy_u8Data );


/**
 * Transmit only one word
 * @param Copy_u32Data
 */
Std_ReturnType CanIf_voidTransmit_Word(u32 Copy_u32Data);

#endif /* INC_CANIF_INTERFACE_H_ */
