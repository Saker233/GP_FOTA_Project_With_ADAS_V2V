#ifndef NRF24L01_H
#define NRF24L01_H

#include "stm32f4xx_hal.h"
// Define the GPIO pins for CE and CSN
#define NRF_CE_PIN  GPIO_PIN_1
#define NRF_CE_PORT GPIOA
#define NRF_CSN_PIN GPIO_PIN_4
#define NRF_CSN_PORT GPIOA

// Function prototypes
void NRF24L01_Init(SPI_HandleTypeDef* hspi);
void NRF24L01_Config(uint8_t channel, uint8_t payloadSize);
void NRF24L01_SetTxAddress(uint8_t* address);
void NRF24L01_SetRxAddress(uint8_t* address);
void NRF24L01_SendData(uint8_t* data, uint8_t len);
void NRF24L01_ReceiveData(uint8_t* data);

#endif /* NRF24L01_H */
