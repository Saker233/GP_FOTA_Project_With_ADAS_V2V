################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN_CONFIG.c \
../Core/Src/CAN_PROGRAM.c \
../Core/Src/CRC_PROGRAM.c \
../Core/Src/FEE_PROGRAM.c \
../Core/Src/FLS_PROGRAM.c \
../Core/Src/GPIO_PROGRAM.c \
../Core/Src/NVM_PROGRAM.c \
../Core/Src/RCC_PROGRAM.c \
../Core/Src/WDT_PROGRAM.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/CAN_CONFIG.o \
./Core/Src/CAN_PROGRAM.o \
./Core/Src/CRC_PROGRAM.o \
./Core/Src/FEE_PROGRAM.o \
./Core/Src/FLS_PROGRAM.o \
./Core/Src/GPIO_PROGRAM.o \
./Core/Src/NVM_PROGRAM.o \
./Core/Src/RCC_PROGRAM.o \
./Core/Src/WDT_PROGRAM.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/CAN_CONFIG.d \
./Core/Src/CAN_PROGRAM.d \
./Core/Src/CRC_PROGRAM.d \
./Core/Src/FEE_PROGRAM.d \
./Core/Src/FLS_PROGRAM.d \
./Core/Src/GPIO_PROGRAM.d \
./Core/Src/NVM_PROGRAM.d \
./Core/Src/RCC_PROGRAM.d \
./Core/Src/WDT_PROGRAM.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CAN_CONFIG.cyclo ./Core/Src/CAN_CONFIG.d ./Core/Src/CAN_CONFIG.o ./Core/Src/CAN_CONFIG.su ./Core/Src/CAN_PROGRAM.cyclo ./Core/Src/CAN_PROGRAM.d ./Core/Src/CAN_PROGRAM.o ./Core/Src/CAN_PROGRAM.su ./Core/Src/CRC_PROGRAM.cyclo ./Core/Src/CRC_PROGRAM.d ./Core/Src/CRC_PROGRAM.o ./Core/Src/CRC_PROGRAM.su ./Core/Src/FEE_PROGRAM.cyclo ./Core/Src/FEE_PROGRAM.d ./Core/Src/FEE_PROGRAM.o ./Core/Src/FEE_PROGRAM.su ./Core/Src/FLS_PROGRAM.cyclo ./Core/Src/FLS_PROGRAM.d ./Core/Src/FLS_PROGRAM.o ./Core/Src/FLS_PROGRAM.su ./Core/Src/GPIO_PROGRAM.cyclo ./Core/Src/GPIO_PROGRAM.d ./Core/Src/GPIO_PROGRAM.o ./Core/Src/GPIO_PROGRAM.su ./Core/Src/NVM_PROGRAM.cyclo ./Core/Src/NVM_PROGRAM.d ./Core/Src/NVM_PROGRAM.o ./Core/Src/NVM_PROGRAM.su ./Core/Src/RCC_PROGRAM.cyclo ./Core/Src/RCC_PROGRAM.d ./Core/Src/RCC_PROGRAM.o ./Core/Src/RCC_PROGRAM.su ./Core/Src/WDT_PROGRAM.cyclo ./Core/Src/WDT_PROGRAM.d ./Core/Src/WDT_PROGRAM.o ./Core/Src/WDT_PROGRAM.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

