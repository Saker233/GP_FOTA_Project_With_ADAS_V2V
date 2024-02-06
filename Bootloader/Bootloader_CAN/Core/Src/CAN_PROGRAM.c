/*******************************************************************************
**  FILENAME     : CAN_PROGRAM.c         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **	                                                  **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **                                                                           **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
*******************************************************************************/

/**********************************************INCLUDES******************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "CAN_PRIVATE.h"
#include "CAN_INTERFACE.h"
#include "CAN_CONFIG.h"


/**********************************************Functions Definition******************************************/
/**
 * Initializes the CAN peripheral
 * @param CANx
 * @param CANInitStruct
 */
void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct)
{
	/* The CAN Module starts in sleep mode so we exit it */
	CLR_BIT(CANx->MCR, CAN_MCR_SLEEP);


	/* Enter Intialization Mode */
	SET_BIT(CANx->MCR, CAN_MCR_INRQ);


	/* Wait for the CAN to enter init by waiting on the flag of the sleep OR the flag of the init */
	while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CAN1->MSR)) || (CAN_MSR_INAK != (CAN_MSR_INAK & CAN1->MSR)))
	{
		asm("NOP");
	}


	/* Enable the Time Trigger COMM Mode if it's enable in the struct */
	if(CANInitStruct->CAN_TTCM == ENABLE)
	{
		SET_BIT(CANx->MCR, CAN_MCR_TTCM);

	}
	else
	{
		CLR_BIT(CANx->MCR, CAN_MCR_TTCM);

	}


	/* Setting the automatic bus off */
	if (CANInitStruct->CAN_ABOM == ENABLE)
	{
		SET_BIT(CANx->MCR, CAN_MCR_ABOM);
	}
	else
	{
		CLR_BIT(CANx->MCR, CAN_MCR_ABOM);
	}

	/* Setting the automatic wake up mode  */
	if (CANInitStruct->CAN_AWUM == ENABLE)
	{
		SET_BIT(CANx->MCR, CAN_MCR_AWUM);
	}
	else
	{
		CLR_BIT(CANx->MCR, CAN_MCR_AWUM);
	}

	/* Setting the automatic Retranssmission */
	if (CANInitStruct->CAN_NART == ENABLE)
	{
		SET_BIT(CANx->MCR, CAN_MCR_NART);
	}
	else
	{
		CLR_BIT(CANx->MCR, CAN_MCR_NART);
	}

	/* Setting the Transmission FIFO Priority  */
	if (CANInitStruct->CAN_TXFP == ENABLE)
	{
		SET_BIT(CANx->MCR, CAN_MCR_TXFP);
	}
	else
	{
		CLR_BIT(CANx->MCR, CAN_MCR_TXFP);
	}


	CANx->BTR = ((u32) CANInitStruct->CAN_MODE << 30) | ((u32) CANInitStruct->CAN_SJW << 24) | ((u32) CANInitStruct->CAN_BS1 << 16) | ((u32) CANInitStruct->CAN_BS2 << 20) | ((u32) CANInitStruct->CAN_Prescaler - 1);


	/* Leave Init Mode */
	CLR_BIT(CANx->MCR, CAN_MCR_INRQ);
}


/**
 * Initializes specific filter bank
 * @param CAN_FilterInitStruct
 */
void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{

}



/**
 * INIT receive message struct to receive can frame
 * in specific FIFO
 * @param CANx
 * @param Copy_u8FifoNumber
 * @param RxMessage
 */
void CAN_VoidReceive(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg* RxMessage)
{
	u8 Local_u8ReceivDataCounter;

	/* Getting the DLC (Data Length Code) from RDTR register the first 4 bits so we make halfword mask [0:3] */
	RxMessage->DATA_LENGHT = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDTR & (u8)0x0F);

	/* Getting the IDE Identfier to know I am working standard or Extended, it's the bit 2 */
	RxMessage->IDE = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR & (u8)0x04) ;

	/* Get the Remote Transsmosiion request, Data Frame or Remote Frame -> bit 1 */
	RxMessage->RTR = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR & (u8)0x02) ;

	/* Get the filter index, [0:7] in RDTR, contains the index of the filter message stored in the mailbox*/
	RxMessage->FMI =  ((CANx->sFIFOMailBox[Copy_u8FifoNumber].RDTR >> 8) & (u8)0xFF) ;


	if (RxMessage->IDE == 0X00) /* The message is standard 11bit identfier */
	{
		/* Storing the the 11 bits of the standard frame */
		RxMessage->ID = ( CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR >> 21) & ((u32)0x000007FF);


	}
	else /* Extended */
	{
		/* Storing the the 28 bits of the standard frame -> [0:17]  ,  [21:31] */
		RxMessage->ID = ( CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR >> 3 ) & ((u32)0x1FFFFFFF) ;
	}

	/* Looping over the data bytes */
	for (Local_u8ReceivDataCounter = 0;  Local_u8ReceivDataCounter< RxMessage->DATA_LENGHT; Local_u8ReceivDataCounter++)
	{
		if (Local_u8ReceivDataCounter < 4)
		{
			/* Get the LSB bytes in the low register as the counter is less than 4 */
			RxMessage->DATA[Local_u8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDLR >> (Local_u8ReceivDataCounter* 8))  & 0xFF;
		}
		else
		{
			/* Get the MSB bytes in the HIGH register as the counter is more than 4 */
			RxMessage->DATA[Local_u8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDHR >> ((Local_u8ReceivDataCounter - 4) * 8)) & 0xFF;
		}
	}

	if (Copy_u8FifoNumber == CAN_FIFO0)
	{
		/* Set bit 5 in RFxR to release FIFO */
		SET_BIT(CANx->RF0R, CAN_RF0R_RFOM0);
	}
	else if ( Copy_u8FifoNumber == CAN_FIFO1)
	{
		/* Set bit 5 in RFxR to release FIFO */
		SET_BIT(CANx->RF1R, CAN_RF1R_RFOM1);
	}
	else
	{
		/* Wrong FIFO */
	}
}


/**
 * INIT transmit can frame to send it through specific mail box
 * @param CANx
 * @param TxMessage
 * @return
 */
u8 CAN_VoidTransmit(CAN_TypeDef* CANx, CanTxMsg*  TxMessage)
{
	u8 Local_u8TransMailboxNumber = 0;
	u8 Local_u8TransDataCounter;

	/* Pooling on the Transmit mailbox 0 to be empty */
	while(!(CAN1->TSR & CAN_TSR_TME0));

	/* Reseting the TX mailbox register */
	CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR = 0;

	/* Setting the IDE and RTR of the frame to be transmitted */
	CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->IDE << 2) | (TxMessage->RTR << 1 ) ;


	if (TxMessage->IDE)
	{
		/* Standrad */
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->ID << 21);
	}
	else
	{
		/* Extended */
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->ID << 3);
	}

	/* Anding TDTR with halfword mask then oring with the data length  */
	CANx->sTxMailBox[Local_u8TransMailboxNumber].TDTR = (CANx->sTxMailBox[Local_u8TransMailboxNumber].TDTR & (~0x0f))
					                                               | TxMessage->DATA_LENGHT;


	/* Emptying the Data registers */
	CANx->sTxMailBox[Local_u8TransMailboxNumber].TDLR = 0;
	CANx->sTxMailBox[Local_u8TransMailboxNumber].TDHR = 0;

	for ( Local_u8TransDataCounter = 0; Local_u8TransDataCounter < TxMessage->DATA_LENGHT; Local_u8TransDataCounter++)
	{
		if (Local_u8TransDataCounter < 4)
		{
			/* Getting the lowest 16 bits 2 bytes  */
			CANx->sTxMailBox[Local_u8TransMailboxNumber].TDLR |= (TxMessage->DATA[Local_u8TransDataCounter] << (8 * Local_u8TransDataCounter));
		}
		else
		{
			/* Getting the highest 16 bits 2 bytes */
			CANx->sTxMailBox[Local_u8TransMailboxNumber].TDHR |= (TxMessage->DATA[Local_u8TransDataCounter] << (8 * (Local_u8TransDataCounter - 4)));
		}
	}

	/* Making a request to start transmit */
	SET_BIT(CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR, CAN_TI0R_TXRQ);


	 return Local_u8TransMailboxNumber;

}


/**
 * Get the last occurred error in "CANx->ESR"register
 * @param CANx
 * @return
 */
u8 CAN_u8GetLastErrorCodeType(CAN_TypeDef* CANx)
{
	u8 Local_u8ErrorcodeType=0;


	/* Getting the last error code bits 4,5,6 in ESR  */
	Local_u8ErrorcodeType = (((u8)CANx->ESR) & (u8)CAN_ESR_LEC);

	return Local_u8ErrorcodeType;
}



/**
 * Enables or disables the specified CANx interrupts.
 * @param CANx
 * @param Copy_u32CanInterruptType
 * @param Copy_u8InterruptNewState
 */
void CAN_VoidInterruptSet(CAN_TypeDef* CANx, u32 Copy_u32CanInterruptType, FunctionalState Copy_u8InterruptNewState)
{
	if (Copy_u8InterruptNewState == ENABLE)
	{
		SET_BIT(CANx->IER, Copy_u32CanInterruptType);
	}
	else if(Copy_u8InterruptNewState == DISABLE)
	{
		CLR_BIT(CANx->IER, Copy_u32CanInterruptType);
	}
	else
	{
		/* NOTHING */
	}
}




/**
 * Activate or Deactivate Time trigger Communication mode of a specific mailbox
 * @param CANx
 * @param NewState
 * @param Copy_u8MailBoxNumber
 */
void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , u8 Copy_u8MailBoxNumber)
{
	if ( Copy_u8MailBoxNumber > 2)
	{
		/* WRONG */
		return;
	}

	if (NewState == ENABLE)
	{
		/* ENABLE TTCM */
		SET_BIT(CANx->MCR, CAN_MCR_TTCM);

		SET_BIT(CANx->sTxMailBox[Copy_u8MailBoxNumber].TDTR, CAN_TDT0R_TGT);
	}
	else if (NewState == DISABLE)
	{
		/* DISABLE TTCM */
		CLR_BIT(CANx->MCR, CAN_MCR_TTCM);

		CLR_BIT(CANx->sTxMailBox[Copy_u8MailBoxNumber].TDTR, CAN_TDT0R_TGT);
	}
	else
	{

	}
}



/**
 * Receive Array of Data
 * @param Copy_u8DataPtr
 * @param Copy_u8DataLenght
 */
void Can_voidSynRecieveArray( u8 *Copy_u8DataPtr ,  u8 Copy_u8DataLenght)
{
	u8 counter1 = ZERO;
	u8 Frame_Number = (Copy_u8DataLenght / FRAME_DATA);


	for(u8 Data_Counter1 = ZERO ; Data_Counter1 < Frame_Number ; Data_Counter1++)
	{
		CanRxMsg   RxMessage;


		/* Pooling on FIFO 0 to be Pending */
		while (!(CAN1->RF0R & CAN_RF0R_FMP0));

		/* Receving the Data in the Can messagee struct */
		CAN_VoidReceive(CAN1 , CAN_FIFO0 ,&RxMessage);

		for( u8 Data_Counter = ZERO ; Data_Counter < FRAME_DATA ; Data_Counter++)
		{
			Copy_u8DataPtr[counter1]= RxMessage.DATA[Data_Counter];
		}

	}
}



/**
 * Receive only one word in FIFO 0
 * @param CANx
 * @param Copy_u8FifoNumber
 * @return
 */
u32 Can_uint32SynRecieveWord(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber)
{
	u32 Copy_u32Data = ZERO ;

    CanRxMsg   RxMessage;

    /* Pooling on FIFO 0 to be Pending */
    while (!(CAN1->RF0R & CAN_RF0R_FMP0));

    /* Receving the Data in the Can messagee struct */
    CAN_VoidReceive ( CANx , Copy_u8FifoNumber ,&RxMessage);

    /* Parsing the 4 bytes in a 32 bit var  */
    Copy_u32Data = (u32)((RxMessage.DATA[BYTE_THREE]<< 24) | (RxMessage.DATA[BYTE_TWO]<< 16) | (RxMessage.DATA[BYTE_ONE]<< 8) | (RxMessage.DATA[BYTE_ZERO]));

    return  Copy_u32Data;
}




/**
 * Receive only one byte in FIFO 0
 * @param CANx
 * @param Copy_u8FifoNumber
 * @return
 */
u8 Can_u8SynRecieveByte(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber)
{
	u8 Copy_u8Data = ZERO ;

	CanRxMsg   RxMessage;

	while (!(CAN1->RF0R & CAN_RF0R_FMP0));

	CAN_VoidReceive ( CANx , Copy_u8FifoNumber ,&RxMessage);


	Copy_u8Data = (u8)((RxMessage.DATA[BYTE_ZERO]));


	return  Copy_u8Data ;


}
