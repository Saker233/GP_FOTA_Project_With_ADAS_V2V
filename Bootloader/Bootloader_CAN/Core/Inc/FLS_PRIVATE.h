
/*******************************************************************************
**  FILENAME     : FLS_PRIVATE.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-01-24                                                 **
**                                                                            **
**                                                                            **
**  AUTHOR       : Mohamed Saker	                                          **
**                                                                            **
**  DESCRIPTION  : FLS Driver PRIVATE file                                     **
**                                                                            **
*******************************************************************************/
#ifndef INC_FLS_PRIVATE_H_
#define INC_FLS_PRIVATE_H_

/******************************************************************************
* User Defined Data Types
*******************************************************************************/
typedef struct
{
    volatile u32 ACR;
    volatile u32 KEYR;       /**<Key register */
    volatile u32 OPTKEYR;
    volatile u32 SR;         /**<Status register */
    volatile u32 CR;         /**<Control register */
    volatile u32 AR;         /**<Page address register */
    volatile u32 OBR;
    volatile u32 WRPR;
}FLS_t;

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define FLS_BASE_ADDRESS     0x40022000

#define SET                        1
#define CLEAR                      0
#define FLS_CATCH_LEAST_HALF_WORD 0x0000FFFF
#define FLS_CATCH_MOST_HALF_WORD  0xFFFF0000
#define CLR_REGISTER               0x00000080
#define FLASH_START_ADDRESS        0x08000000
#define FLS_RDPRT                 0x00A5
#define FLS_KEY_1                 0x45670123
#define FLS_KEY_2                 0xCDEF89AB
#define PAGE_SIZE                  1024
#define TWO_BYTE                   2
#define ONE_WORD_SIZE              4
#define TWO_BYTES_IN_BITS          16


#define FLS                  ((volatile FLS_t * const)(FLS_BASE_ADDRESS))
// Register bits definition.

// ACR register bits defniton.
#define LATENCY         0
#define HLFCYA          3
#define PRFTBE          4
#define PRFTBS          5
//SR register bits defniton.
#define BSY             0
#define PGERR           2
#define WRPRTERR        4
#define EOP             5
//CR register bits defniton.
#define PG              0
#define PER             1
#define MER             2
#define OPTPG           4
#define OPTER           5
#define STRT            6
#define LOCK            7
#define OPTWRE          9
#define ERRIE           10
#define EOPIE           12


#endif /* INC_FLS_PRIVATE_H_ */
