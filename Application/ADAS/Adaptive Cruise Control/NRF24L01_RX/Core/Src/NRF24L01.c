#include "nrf24l01.h"

// Function to initialize the NRF24L01 module
void NRF_Init(SPI_HandleTypeDef *hspi) {
    // Reset the NRF24L01 module
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
    HAL_Delay(5);

    // Configure NRF24L01 registers
    uint8_t config = 0x00; // Set default configuration
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, &config, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    // Set RX and TX addresses
    uint8_t txAddr[5] = {0x12, 0x34, 0x56, 0x78, 0x90}; // Example TX address
    uint8_t rxAddr[5] = {0x12, 0x34, 0x56, 0x78, 0x90}; // Example RX address
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, NRF_TX_ADDR_REG, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(hspi, txAddr, 5, HAL_MAX_DELAY);
    HAL_SPI_Transmit(hspi, NRF_RX_ADDR_P0_REG, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(hspi, rxAddr, 5, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    // Power up the NRF24L01 module and set CE pin
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
}

void NRF_SendData(SPI_HandleTypeDef *hspi, uint8_t *data, uint8_t len) {
    // Write data to TX FIFO buffer
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, NRF_W_TX_PAYLOAD_CMD, 1, HAL_MAX_DELAY); // Write payload command
    HAL_SPI_Transmit(hspi, data, len, HAL_MAX_DELAY); // Write data to TX FIFO
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);

    // Start transmission
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
    HAL_Delay(1); // Ensure CE is set for at least 10 us (datasheet requirement)
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);
}

// Function to receive data via NRF24L01 module
void NRF_ReceiveData(SPI_HandleTypeDef *hspi, uint8_t *data) {
    // Check if there are any received payloads
    uint8_t status;
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(hspi, NRF_NOP_CMD, &status, 1, HAL_MAX_DELAY); // Send NOP command to read status
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);

    if (status & NRF_RX_DR_MASK) { // Data ready in RX FIFO
        // Read received data from RX FIFO buffer
        HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(hspi, NRF_R_RX_PAYLOAD_CMD, data, 1, HAL_MAX_DELAY); // Read payload command
        HAL_SPI_Receive(hspi, data, 32, HAL_MAX_DELAY); // Read data from RX FIFO
        HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);

        // Clear RX_DR bit in status register
        uint8_t config = NRF_STATUS_REG | (1 << NRF_RX_DR_BIT);
        HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
        HAL_SPI_Transmit(hspi, &config, 1, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
    }
}

