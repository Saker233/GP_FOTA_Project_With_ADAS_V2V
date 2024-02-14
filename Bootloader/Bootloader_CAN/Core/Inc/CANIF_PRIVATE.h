
/*******************************************************************************
**  FILENAME     : CANIF_PRIVATE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-26                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : CANIF Driver PRIVATE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_CANIF_PRIVATE_H_
#define INC_CANIF_PRIVATE_H_

/******************************************************************************************/
/*                                    Macro Definition                                    */
/*******************************************************************************************/

#define NODE_ONE_MESS_ID            0X02
#define NODE_TWO_MESS_ID            0X03
#define EIGTH_ROUNDS                 8
#define FRAME_DATA_BYTES             8
#define ONE_BTYE                     1
#define FOUR_BYTES                   4
#define BYTE_ZERO                    0
#define ZERO                         0

#define NODE_ONE_ID         		 0X00
#define NODE_TWO_ID        			 0X01
typedef u8 				Std_ReturnType;
#define E_OK         (Std_ReturnType)0x01
#define E_NOT_OK     (Std_ReturnType)0x00

#define CONFOIG_DLC        			 8
#define CONFOIG_RTR       			 0
#define CONFOIG_IDE       			 0

#endif /* INC_CANIF_PRIVATE_H_ */
