#include "NRF24L01.h"

SPI_HandleTypeDef* nrf24l01_hspi;

void NRF24L01_Init(SPI_HandleTypeDef* hspi) {
    nrf24l01_hspi = hspi;

//    // Initialize CE and CSN pins as GPIO outputs
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    GPIO_InitStruct.Pin = NRF_CE_PIN | NRF_CSN_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(NRF_CE_PORT, &GPIO_InitStruct);

    // Disable CE and CSN initially
    HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}

void NRF24L01_Config(uint8_t channel, uint8_t payloadSize) {
    // Set channel
    uint8_t reg = 0x05;  // RF_CH register
    uint8_t value = channel;
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, &value, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);

    // Set payload size
    reg = 0x11;  // RX_PW_P0 register
    value = payloadSize;
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, &value, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}

void NRF24L01_SetTxAddress(uint8_t* address) {
    uint8_t reg = 0x10;  // TX_ADDR register
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, address, 5, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}

void NRF24L01_SetRxAddress(uint8_t* address) {
    uint8_t reg = 0x0A;  // RX_ADDR_P0 register
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, address, 5, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}

void NRF24L01_SendData(uint8_t* data, uint8_t len) {
    uint8_t reg = 0xA0;  // W_TX_PAYLOAD command
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, data, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);

    // Pulse CE pin to start transmission
    HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_SET);
    HAL_Delay(1);  // Pulse CE for at least 10 microseconds
    HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_RESET);
}

void NRF24L01_ReceiveData(uint8_t* data) {
    // Check if data is available
    uint8_t reg = 0x17;  // FIFO_STATUS register
    uint8_t status;
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(nrf24l01_hspi, &status, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);

    if ((status & 0x01) == 0) {
        // No data available
        return;
    }

    // Read received data
    reg = 0x61;  // R_RX_PAYLOAD command
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(nrf24l01_hspi, data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);

    // Clear RX_DR bit in STATUS register
    reg = 0x07;  // STATUS register
    status = 0x40;  // Clear RX_DR bit
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(nrf24l01_hspi, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(nrf24l01_hspi, &status, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}
