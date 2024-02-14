
/*******************************************************************************
**  FILENAME     : CANIF_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CANIF Driver PROGRAM file                                  **
**                                                                            **
*******************************************************************************/
/**********************************************include******************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "CANIF_PRIVATE.h"
#include "CANIF_INTERFACE.h"
#include "CANIF_CONFIG.h"
#include "CAN_INTERFACE.h"


/******************************************************************************
* Function Definitions
*******************************************************************************/



/**
 * Receive a complete frame
 * @param CANx
 * @param Copy_u8FifoNumber
 * @param RxMessage
 */
Std_ReturnType CanIf_voidReceive_Struct(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg RxMessage)
{
 	Std_ReturnType Local_ReturnError = E_OK;

	if (NULL == CANx)
	{
		Local_ReturnError = E_NOT_OK;

		return  Local_ReturnError;

	}
	CAN_VoidReceive(CANx, Copy_u8FifoNumber, &RxMessage);

	return Local_ReturnError;
}

/**
 * Initialize transmission CAN frame to send it through specific mailbox
 * @param CANx
 * @param TxMessage
 */
Std_ReturnType CanIf_voidTransmit_Struct(CAN_TypeDef* CANx, CanTxMsg TxMessage )
{
	Std_ReturnType Local_ReturnError = E_OK;


	if (NULL == CANx)
	{
		Local_ReturnError = E_NOT_OK;

		return  Local_ReturnError;

	}

	CAN_VoidTransmit( CANx , &TxMessage);

	return Local_ReturnError;
}

/**
 * Block FIFO until receive only one word
 * @param Copy_u32Word
 */
Std_ReturnType CanIf_voidReceive_Word(u32 *Copy_u32Word)
{
 	Std_ReturnType Local_ReturnError = E_OK;


	if ((NULL == Copy_u32Word))
	{
		Local_ReturnError = E_NOT_OK;

		return  Local_ReturnError;
	}
	u32 Local_u32Data ;

	Local_u32Data = Can_uint32SynRecieveWord(CAN1 , CAN_FIFO0);


	(*Copy_u32Word) = Local_u32Data ;

	return  Local_ReturnError;
}


/**
 * Block FIFO until receive only one byte
 * @param Copy_u8Byte
 */
Std_ReturnType CanIf_voidReceive_Byte(u8*Copy_u8Byte)
{
 	Std_ReturnType Local_ReturnError = E_OK;


	if (NULL == Copy_u8Byte)
	{
		Local_ReturnError = E_NOT_OK;

		return  Local_ReturnError;
	}


	u8 Local_u8Data ;

	Local_u8Data = Can_u8SynRecieveByte(CAN1 , CAN_FIFO0);

	(*Copy_u8Byte) = Local_u8Data;

	return  Local_ReturnError;
}


/**
 * Block FIFO until receiving is all complete
 * @param Copy_u8DataPtr
 * @param Copy_u8DataLenght
 */
Std_ReturnType CanIf_voidReceive_Block(u8 *Copy_u8DataPtr , u16 Copy_u8DataLenght)
{

	Std_ReturnType Local_ReturnError = E_OK;


	if (NULL == Copy_u8DataPtr)
	{
		Local_ReturnError = E_NOT_OK;

		return  Local_ReturnError;
	}



	Can_voidSynRecieveArray(Copy_u8DataPtr , Copy_u8DataLenght);

	return  Local_ReturnError;

}



/**
 * Transmit only one byte
 * @param Copy_u8Data
 */
Std_ReturnType CanIf_voidTransmit_Byte(u8 Copy_u8Data )
{

 	Std_ReturnType Local_ReturnError = E_OK;


	 CanTxMsg  TxMessage ;


	TxMessage.ID = NODE_ONE_MESS_ID ;


	TxMessage.DATA_LENGHT = ONE_BTYE;
	TxMessage.IDE = CONFOIG_IDE;
	TxMessage.RTR = CONFOIG_RTR;
	TxMessage.DATA[BYTE_ZERO] = Copy_u8Data;


	Local_ReturnError = CanIf_voidTransmit_Struct(CAN1, TxMessage);

	return Local_ReturnError ;
}


/**
 * Transmit only one word
 * @param Copy_u32Data
 */
Std_ReturnType CanIf_voidTransmit_Word(u32 Copy_u32Data)
{

 	Std_ReturnType Local_ReturnError = E_OK;


	 CanTxMsg TxMessage;

	u32 *Local_u8DataPtr = &Copy_u32Data;


	TxMessage.ID = NODE_ONE_MESS_ID;



	TxMessage.DATA_LENGHT = FOUR_BYTES;
	TxMessage.IDE = CONFOIG_IDE;
	TxMessage.RTR = CONFOIG_RTR;
	       /* save word byte by byte to first  4 elements in array*/
	for( u8 Data_Counter = ZERO ; Data_Counter < FOUR_BYTES ; Data_Counter++)
	    {
			TxMessage.DATA[Data_Counter] = Local_u8DataPtr[Data_Counter];
	    }
	                        /*send frame*/
	Local_ReturnError= CanIf_voidTransmit_Struct(CAN1, TxMessage);

	return Local_ReturnError ;
}

