/*
 * NRF24L01.h
 *
 *  Created on: Feb 8, 2024
 *      Author: ahmed
 */

#ifndef SRC_NRF24L01_H_
#define SRC_NRF24L01_H_

#include "stm32f4xx_hal.h"

// Define nRF24L01 register addresses
#define NRF_CONFIG_REG      0x00
#define NRF_EN_AA_REG       0x01
#define NRF_SETUP_AW_REG    0x03
#define NRF_SETUP_RETR_REG  0x04
#define NRF_RF_CH_REG       0x05
#define NRF_RF_SETUP_REG    0x06
#define NRF_STATUS_REG      0x07
#define NRF_RX_ADDR_P0_REG  (uint8_t*) 0x0A
#define NRF_TX_ADDR_REG     (uint8_t*) 0x10
#define NRF_RX_PW_P0_REG    0x11
#define NRF_FIFO_STATUS_REG 0x17

// Define nRF24L01 commands
#define NRF_W_TX_PAYLOAD_CMD  (uint8_t*) 0xA0
#define NRF_R_RX_PAYLOAD_CMD  (uint8_t*) 0x61
#define NRF_NOP_CMD           (uint8_t*) 0xFF

// Define nRF24L01 status register bits
#define NRF_RX_DR_MASK  0x40
#define NRF_RX_DR_BIT   6


// Define the Ports and Pins for CE and CSN
#define NRF_CE_GPIO_Port           GPIOA
#define NRF_CE_Pin                 GPIO_PIN_1
#define NRF_CSN_GPIO_Port		   GPIOA
#define NRF_CSN_Pin                GPIO_PIN_4


// Function prototypes
void NRF_Init(SPI_HandleTypeDef *hspi);
void NRF_SendData(SPI_HandleTypeDef *hspi, uint8_t *data, uint8_t len);
void NRF_ReceiveData(SPI_HandleTypeDef *hspi, uint8_t *data);

#endif /* SRC_NRF24L01_H_ */
