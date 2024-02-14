/*******************************************************************************
**  FILENAME     : CAN_PRIVATE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CAN Driver private file                                     **
**                                                                            **
*******************************************************************************/

#ifndef INC_CAN_PRIVATE_H_
#define INC_CAN_PRIVATE_H_

#include "STD_TYPES.h"


/***************************************************** DEFINE MACROS FOR CAN INSTANCE **************************************************************************/
#define CAN1_BASE          0x40006400
#define CAN1               ((CAN_TypeDef*) CAN1_BASE)


/***************************************************** CAN REGISTERS BIT DECLRATION **************************************************************************/

/* CAN_MCR */
#define  CAN_MCR_INRQ                        0  /* Used in Intialization MODE  */
#define  CAN_MCR_SLEEP                       1  /* Sleep Mode */
#define  CAN_MCR_TXFP                        2  /* FIFO Priority */
#define  CAN_MCR_RFLM                        3  /* LOCK MODE */
#define  CAN_MCR_NART                        4  /* AUTOMATIC TRANSSMISSIN */
#define  CAN_MCR_AWUM                        5  /* WAKE UP */
#define  CAN_MCR_ABOM                        6  /*  */
#define  CAN_MCR_TTCM                        7  /* TIME TRIGGER */

/* CAN_MSR */
#define  CAN_MSR_INAK                        0            /* Initialization Acknowledge */
#define  CAN_MSR_SLAK                        1            /* Sleep Acknowledge */
#define  CAN_MSR_WKUI                        3            /* Wakeup Interrupt */


/* CAN_TSR */
#define  CAN_TSR_RQCP0                       0        /* Request Completed Mailbox0 */
#define  CAN_TSR_RQCP1                       8        /* Request Completed Mailbox1 */
#define  CAN_TSR_RQCP2                       16        /* Request Completed Mailbox2 */
#define  CAN_TSR_TME0                        26        /* Transmit Mailbox 0 Empty */
#define  CAN_TSR_TME1                        27        /* Transmit Mailbox 1 Empty */
#define  CAN_TSR_TME2                        28        /* Transmit Mailbox 2 Empty */

/* CAN_RF0R */
#define  CAN_RF0R_FMP0                       ((u8)0x03)               /* FIFO 0 Message Pending */
#define  CAN_RF0R_FULL0                      3              		 /* FIFO 0 Full */
#define  CAN_RF0R_FOVR0                      4               		/* FIFO 0 Overrun */
#define  CAN_RF0R_RFOM0                      5               /* Release FIFO 0 Output Mailbox */


/* CAN_RF1R */
#define  CAN_RF1R_FMP1                       ((u8)0x03)               /* FIFO 1 Message Pending */
#define  CAN_RF1R_FULL1                      3               /* FIFO 1 Full */
#define  CAN_RF1R_FOVR1                      4               /* FIFO 1 Overrun */
#define  CAN_RF1R_RFOM1                      5               /* Release FIFO 1 Output Mailbox */


/* CAN_IER */
#define  CAN_IER_TMEIE                       0        /* Transmit Mailbox Empty Interrupt Enable */
#define  CAN_IER_FMPIE0                      1        /* FIFO 0 Message Pending Interrupt Enable */
#define  CAN_IER_FMPIE1                      4        /* FIFO 1 Message Pending Interrupt Enable */



#define  CAN_ESR_LEC                         ((u32)0x00000070)        /* LEC[2:0] bits (Last Error Code) */



/***************************************************** CAN MAILBOXES REGISTERS **************************************************************************/

/* CAN_TI0R */
#define  CAN_TI0R_TXRQ                       0        /* Transmit Mailbox Request */
#define  CAN_TI0R_RTR                        1        /* Remote Transmission Request */
#define  CAN_TI0R_IDE                        2        /* Identifier Extension */
#define  CAN_TI0R_EXID                       ((u32)0x001FFFF8)        /* Extended Identifier */
#define  CAN_TI0R_STID                       ((u32)0xFFE00000)        /* Standard Identifier or Extended Identifier */


/* CAN_TI1R */
#define  CAN_TI1R_TXRQ                       ((u32)0x00000001)        /* Transmit Mailbox Request */
#define  CAN_TI1R_RTR                        ((u32)0x00000002)        /* Remote Transmission Request */
#define  CAN_TI1R_IDE                        ((u32)0x00000004)        /* Identifier Extension */
#define  CAN_TI1R_EXID                       ((u32)0x001FFFF8)        /* Extended Identifier */
#define  CAN_TI1R_STID                       ((u32)0xFFE00000)        /* Standard Identifier or Extended Identifier */



/* CAN_TI2R */
#define  CAN_TI2R_TXRQ                       ((u32)0x00000001)        /* Transmit Mailbox Request */
#define  CAN_TI2R_RTR                        ((u32)0x00000002)        /* Remote Transmission Request */
#define  CAN_TI2R_IDE                        ((u32)0x00000004)        /* Identifier Extension */
#define  CAN_TI2R_EXID                       ((u32)0x001FFFF8)        /* Extended identifier */
#define  CAN_TI2R_STID                       ((u32)0xFFE00000)        /* Standard Identifier or Extended Identifier */


/*  CAN_TDT0R  */
#define  CAN_TDT0R_DLC                       ((u32)0x0000000F)        /* Data Length Code */
#define  CAN_TDT0R_TGT                       8        /* Transmit Global Time */
#define  CAN_TDT0R_TIME                      ((u32)0xFFFF0000)        /* Message Time Stamp */



/*  CAN_TDT1R  */
#define  CAN_TDT1R_DLC                       ((u32)0x0000000F)        /* Data Length Code */
#define  CAN_TDT1R_TGT                       ((u32)0x00000100)        /* Transmit Global Time */
#define  CAN_TDT1R_TIME                      ((u32)0xFFFF0000)        /* Message Time Stamp */



/*  CAN_TDT2R  */
#define  CAN_TDT2R_DLC                       ((u32)0x0000000F)        /* Data Length Code */
#define  CAN_TDT2R_TGT                       ((u32)0x00000100)        /* Transmit Global Time */
#define  CAN_TDT2R_TIME                      ((u32)0xFFFF0000)        /* Message Time Stamp */



/*  CAN_TDL0R  */
#define  CAN_TDL0R_DATA0                     ((u32)0x000000FF)        /* Data byte 0 */
#define  CAN_TDL0R_DATA1                     ((u32)0x0000FF00)        /* Data byte 1 */
#define  CAN_TDL0R_DATA2                     ((u32)0x00FF0000)        /* Data byte 2 */
#define  CAN_TDL0R_DATA3                     ((u32)0xFF000000)        /* Data byte 3 */


/*  CAN_TDL1R  */
#define  CAN_TDL1R_DATA0                     ((u32)0x000000FF)        /* Data byte 0 */
#define  CAN_TDL1R_DATA1                     ((u32)0x0000FF00)        /* Data byte 1 */
#define  CAN_TDL1R_DATA2                     ((u32)0x00FF0000)        /* Data byte 2 */
#define  CAN_TDL1R_DATA3                     ((u32)0xFF000000)        /* Data byte 3 */


/*  CAN_TDL2R  */
#define  CAN_TDL2R_DATA0                     ((u32)0x000000FF)        /* Data byte 0 */
#define  CAN_TDL2R_DATA1                     ((u32)0x0000FF00)        /* Data byte 1 */
#define  CAN_TDL2R_DATA2                     ((u32)0x00FF0000)        /* Data byte 2 */
#define  CAN_TDL2R_DATA3                     ((u32)0xFF000000)        /* Data byte 3 */



/* CAN_TDH0R */
#define  CAN_TDH0R_DATA4                     ((u32)0x000000FF)        /* Data byte 4 */
#define  CAN_TDH0R_DATA5                     ((u32)0x0000FF00)        /* Data byte 5 */
#define  CAN_TDH0R_DATA6                     ((u32)0x00FF0000)        /* Data byte 6 */
#define  CAN_TDH0R_DATA7                     ((u32)0xFF000000)        /* Data byte 7 */



/* CAN_TDH1R */
#define  CAN_TDH1R_DATA4                     ((u32)0x000000FF)        /* Data byte 4 */
#define  CAN_TDH1R_DATA5                     ((u32)0x0000FF00)        /* Data byte 5 */
#define  CAN_TDH1R_DATA6                     ((u32)0x00FF0000)        /* Data byte 6 */
#define  CAN_TDH1R_DATA7                     ((u32)0xFF000000)        /* Data byte 7 */






/* CAN_TDH2R */
#define  CAN_TDH2R_DATA4                     ((u32)0x000000FF)        /* Data byte 4 */
#define  CAN_TDH2R_DATA5                     ((u32)0x0000FF00)        /* Data byte 5 */
#define  CAN_TDH2R_DATA6                     ((u32)0x00FF0000)        /* Data byte 6 */
#define  CAN_TDH2R_DATA7                     ((u32)0xFF000000)        /* Data byte 7 */


/* CAN_RI0R  */
#define  CAN_RI0R_RTR                        ((u32)0x00000002)        /* Remote Transmission Request */
#define  CAN_RI0R_IDE                        ((u32)0x00000004)        /* Identifier Extension */
#define  CAN_RI0R_EXID                       ((u32)0x001FFFF8)        /* Extended Identifier */
#define  CAN_RI0R_STID                       ((u32)0xFFE00000)        /* Standard Identifier or Extended Identifier */


/* CAN_RI1R  */
#define  CAN_RI1R_RTR                        ((u32)0x00000002)        /* Remote Transmission Request */
#define  CAN_RI1R_IDE                        ((u32)0x00000004)        /* Identifier Extension */
#define  CAN_RI1R_EXID                       ((u32)0x001FFFF8)        /* Extended Identifier */
#define  CAN_RI1R_STID                       ((u32)0xFFE00000)        /* Standard Identifier or Extended Identifier */


/* CAN_RDT0R */
#define  CAN_RDT0R_DLC                       ((u32)0x0000000F)        /* Data Length Code */
#define  CAN_RDT0R_FMI                       ((u32)0x0000FF00)        /* Filter Match Index */
#define  CAN_RDT0R_TIME                      ((u32)0xFFFF0000)        /* Message Time Stamp */


/* CAN_RDT1R */
#define  CAN_RDT1R_DLC                       ((u32)0x0000000F)        /* Data Length Code */
#define  CAN_RDT1R_FMI                       ((u32)0x0000FF00)        /* Filter Match Index */
#define  CAN_RDT1R_TIME                      ((u32)0xFFFF0000)        /* Message Time Stamp */



/* CAN_RDL0R */
#define  CAN_RDL0R_DATA0                     ((u32)0x000000FF)        /* Data byte 0 */
#define  CAN_RDL0R_DATA1                     ((u32)0x0000FF00)        /* Data byte 1 */
#define  CAN_RDL0R_DATA2                     ((u32)0x00FF0000)        /* Data byte 2 */
#define  CAN_RDL0R_DATA3                     ((u32)0xFF000000)        /* Data byte 3 */


/* CAN_RDL1R */
#define  CAN_RDL1R_DATA0                     ((u32)0x000000FF)        /* Data byte 0 */
#define  CAN_RDL1R_DATA1                     ((u32)0x0000FF00)        /* Data byte 1 */
#define  CAN_RDL1R_DATA2                     ((u32)0x00FF0000)        /* Data byte 2 */
#define  CAN_RDL1R_DATA3                     ((u32)0xFF000000)        /* Data byte 3 */



/* CAN_RDH0R */
#define  CAN_RDH0R_DATA4                     ((u32)0x000000FF)        /* Data byte 4 */
#define  CAN_RDH0R_DATA5                     ((u32)0x0000FF00)        /* Data byte 5 */
#define  CAN_RDH0R_DATA6                     ((u32)0x00FF0000)        /* Data byte 6 */
#define  CAN_RDH0R_DATA7                     ((u32)0xFF000000)        /* Data byte 7 */


/* CAN_RDH1R */
#define  CAN_RDH1R_DATA4                     ((u32)0x000000FF)        /* Data byte 4 */
#define  CAN_RDH1R_DATA5                     ((u32)0x0000FF00)        /* Data byte 5 */
#define  CAN_RDH1R_DATA6                     ((u32)0x00FF0000)        /* Data byte 6 */
#define  CAN_RDH1R_DATA7                     ((u32)0xFF000000)        /* Data byte 7 */

/** @defgroup CAN_receive_FIFO_number CAN Receive FIFO Number **/
#define CAN_RX_FIFO0                ((u32)(0x0))  /* CAN receive FIFO 0 */
#define CAN_RX_FIFO1                ((u32)(0x1))  /* CAN receive FIFO 1 */

/** @defgroup CAN_filter_FIFO CAN Filter FIFO **/
#define CAN_FILTER_FIFO0            ((u32)(0x0))  /* Filter FIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO1            ((u32)(0x1))  /* Filter FIFO 1 assignment for filter x */

/** @defgroup CAN_filter_mode CAN Filter Mode **/
#define CAN_FILTERMODE_IDMASK       ((u32)(0x0))  /* Identifier mask mode */
#define CAN_FILTERMODE_IDLIST       ((u32)(0x1))  /* Identifier list mode */

/** @defgroup CAN_filter_scale CAN Filter Scale */
#define CAN_FILTERSCALE_16BIT       ((u32)(0x0))  /* Two 16-bit filters */
#define CAN_FILTERSCALE_32BIT       ((u32)(0x1))  /* One 32-bit filter  */




#define FRAME_DATA             				    8
#define ZERO                				    0
#define BYTE_ZERO            				    0
#define BYTE_ONE               			     	1
#define BYTE_TWO              					2
#define BYTE_THREE            					3
#define  CAN_FMR_FINIT                          ((u8)0x01)               /* Filter Init Mode */


/*****************************************************User-Defined Data Types **************************************************************************/
/* CAN TxMailBox */
typedef struct
{
   u32 TIR;
   u32 TDTR;
   u32 TDLR;
   u32 TDHR;
} CAN_TxMailBoxType_Def;

/* CAN FIFOMailBox  */
typedef struct
{
  u32 RIR;
  u32 RDTR;
  u32 RDLR;
  u32 RDHR;
} CAN_FIFOMailBoxType_Def;


/* CAN TxMailBox FilterRegister  */
typedef struct
{
  u32 FR1;
  u32 FR2;
} CAN_FilterRegisterType_Def;

/* CAN Struct */
typedef struct
{
   u32 MCR;
   u32 MSR;
   u32 TSR;
   u32 RF0R;
   u32 RF1R;
   u32 IER;
   u32 ESR;
   u32 BTR;
   u32  RESERVED0[88];
  CAN_TxMailBoxType_Def sTxMailBox[3];
  CAN_FIFOMailBoxType_Def sFIFOMailBox[2];
  u32  RESERVED1[12];
  u32 FMR;
  u32 FM1R;
  u32  RESERVED2;
  u32 FS1R;
  u32  RESERVED3;
  u32 FFA1R;
  u32  RESERVED4;
  u32  FA1R;
  u32  RESERVED5[8];
  CAN_FilterRegisterType_Def sFilterRegister[14];
} CAN_TypeDef;



typedef enum
{
	DISABLE = 0,
	ENABLE
}FunctionalState;

typedef enum
{
	ERROR = 0,
	SUCCESS
}ErrorStatus;




#endif /* INC_CAN_PRIVATE_H_ */
