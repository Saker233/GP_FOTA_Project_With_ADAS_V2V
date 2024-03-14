# FOTA with CAN Communication Protocol and Cryptography Implementation for Automotive Systems

This project aims to implement Firmware Over-The-Air (FOTA) capabilities, enhanced with CAN communication protocols and cryptography techniques, for automotive systems. Our focus is on establishing a secure and efficient method of updating firmware on microcontrollers found within automotive environments.

## Table of Contents

- [1. Project Overview](#1-project-overview)
- [2. Directory Structure](#2-directory-structure)
- [3. Getting Started](#3-getting-started)
  - [3.1. Prerequisites](#31-prerequisites)
  - [3.2. Installation](#32-installation)
- [4. Usage](#4-usage)
- [5. Contributing](#5-contributing)
- [6. Contact](#6-contact)
- [7. Acknowledgements](#7-acknowledgements)

## 1. Project Overview

Our solution extends beyond merely updating device firmware; it encapsulates the utilization of a Graphical User Interface (GUI) developed with PyQt5, RSA algorithm for encryption, HMAC for integrity check, and an in-depth exploration into adaptive cruise control using sensors like Ultrasonic and modules like NRF24L01 for communication.

## 2. Directory Structure

The project's directory is organized as follows:

```
├── Application
│   ├── ADAS
│   │   ├── Adaptive Cruise Control
│   │   └── iti_dc_motor
│   ├── a.txt
│   ├── Lane_Detection
│   │   └── IR2
│   └── Socket_V2I
│       ├── Core
│       ├── Debug
│       ├── Drivers
│       ├── python socket
│       ├── Socket_V2I Debug.launch
│       ├── Socket_V2I.ioc
│       └── STM32F401RCTX_FLASH.ld
├── Bootloader
│   ├── a.txt
│   ├── Bootloader_CAN
│   │   ├── Bootloader_CAN.ioc
│   │   ├── Core
│   │   ├── Debug
│   │   ├── Drivers
│   │   └── STM32F103C8TX_FLASH.ld
│   └── Bootloader_UART
│       ├── Bootloader_UART.ioc
│       ├── Core
│       ├── Drivers
│       └── STM32F103C8TX_FLASH.ld
├── Docs
│   ├── a.txt
│   ├── Autosar
│   │   ├── AUTOSAR_SWS_CANDriver.pdf
│   │   ├── AUTOSAR_SWS_CANInterface_2.pdf
│   │   ├── AUTOSAR_SWS_CANTransportLayer_2.pdf
│   │   ├── AUTOSAR_SWS_FlashEEPROMEmulation_2.pdf
│   │   └── AUTOSAR_SWS_NVRAMManager.pdf
│   ├── HC-SR04 Ultrasonic.pdf
│   ├── nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
│   ├── STM32f103
│   │   ├── 01- STM32F10x Register Description_2.pdf
│   │   ├── 02- STM32F103x Programming Manual.pdf
│   │   ├── 03- ARM ARM.pdf
│   │   └── 04- STM32F10xxx Flash memory microcontrollers.pdf
│   └── STM32F401
│       ├── 00- STM32f401CC Specifications.pdf
│       ├── 01- ST M4 Programming Manual.pdf
│       └── 02- Register Description.pdf
├── Gateway
│   ├── a.txt
│   ├── Cryptography
│   │   ├── App.hex
│   │   ├── concatenation_script.py
│   │   ├── OEM_encryption.py
│   │   ├── OEM_signature.py
│   │   ├── README.md
│   │   ├── RPI_scenario.py
│   │   └── secret_keys.env
│   └── GUI
│       ├── fota-ce4bf-firebase-adminsdk-q2xub-a851db9e97.json
│       ├── fota.py
│       ├── fota_ui.py
│       ├── icon.png
│       ├── metadata
│       ├── security.py
│       └── utils.py
└── README.md
```

### Key Components:

- **ADAS**: Involves implementations like Adaptive Cruise Control, featuring modules for NRF communication and Ultrasonic sensor handling.
- **iti_dc_motor**: Manages car movements using the L298N motor driver and STM32F401 microcontroller.
- **Lane_Detection**: Utilizes IR sensors for autonomous line-following capabilities.
- **Bootloader**: Ensures secure firmware updates over CAN protocol.
- **GUI**: A user-friendly interface for managing FOTA processes, developed with PyQt5.

## 3. Getting Started

Follow these steps to get a copy of the project up and running on your local machine for development and testing purposes.

### 3.1. Prerequisites

What things you need to install the software and how to install them:

```bash
python3 -m pip install -r firebase_admin pyserial
```

### 3.2. Installation

A step-by-step series of examples that tell you how to get a development environment running:

1. Clone the repository
```bash
git clone https://github.com/Saker233/GP_FOTA_Project_With_ADAS_V2V
```
2. Navigate to the project directory
```bash
cd GP_FOTA_Project_With_ADAS_V2V/Gateway/GUI
```

## 4. Usage

To start the application, run the following in the root directory:

```bash
python fota.py
```

This command initiates the GUI, allowing you to conduct various operations such as checking for updates, performing secure downloads, and decrypting received firmware.

## 5. Contributing

Please read [CONTRIBUTING.md](#) for details on our code of conduct, and the process for submitting pull requests to us.

## 6. Contact
- [Mohamed Ahmed Saker](https://www.linkedin.com/in/mohamed-saker-795123228/)
- [Ahmed Khaled Abbas](https://www.linkedin.com/in/eng-ahmedkhaled/)
- [Aya Mohamed Sayed](https://www.linkedin.com/in/aya-mohamed-8781281b6)
- [Nada Elsayed Hassan](https://www.linkedin.com/in/nada-elsayed%F0%9F%87%B5%F0%9F%87%B8-b06090297/)
- [Ahmed Reda Mohamed](https://www.linkedin.com/in/ahmed-r-b1891b80/)


## 7. Acknowledgements

- STM32f401CC microcontroller
- L298N Motor Driver
- Ultrasonic Sensor
- NRF24L01 Module
- PyQt5 for GUI Development
