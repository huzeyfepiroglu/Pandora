################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/bdma.c \
../Core/Src/can_messages.c \
../Core/Src/cocking_handle_maingun.c \
../Core/Src/dma.c \
../Core/Src/error.c \
../Core/Src/eth.c \
../Core/Src/fdcan.c \
../Core/Src/flash.c \
../Core/Src/functions.c \
../Core/Src/gpio.c \
../Core/Src/gun_control.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/peripherals.c \
../Core/Src/power_management.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c \
../Core/Src/timing.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/bdma.o \
./Core/Src/can_messages.o \
./Core/Src/cocking_handle_maingun.o \
./Core/Src/dma.o \
./Core/Src/error.o \
./Core/Src/eth.o \
./Core/Src/fdcan.o \
./Core/Src/flash.o \
./Core/Src/functions.o \
./Core/Src/gpio.o \
./Core/Src/gun_control.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/peripherals.o \
./Core/Src/power_management.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/timing.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/bdma.d \
./Core/Src/can_messages.d \
./Core/Src/cocking_handle_maingun.d \
./Core/Src/dma.d \
./Core/Src/error.d \
./Core/Src/eth.d \
./Core/Src/fdcan.d \
./Core/Src/flash.d \
./Core/Src/functions.d \
./Core/Src/gpio.d \
./Core/Src/gun_control.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/peripherals.d \
./Core/Src/power_management.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d \
./Core/Src/timing.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/bdma.cyclo ./Core/Src/bdma.d ./Core/Src/bdma.o ./Core/Src/bdma.su ./Core/Src/can_messages.cyclo ./Core/Src/can_messages.d ./Core/Src/can_messages.o ./Core/Src/can_messages.su ./Core/Src/cocking_handle_maingun.cyclo ./Core/Src/cocking_handle_maingun.d ./Core/Src/cocking_handle_maingun.o ./Core/Src/cocking_handle_maingun.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/error.cyclo ./Core/Src/error.d ./Core/Src/error.o ./Core/Src/error.su ./Core/Src/eth.cyclo ./Core/Src/eth.d ./Core/Src/eth.o ./Core/Src/eth.su ./Core/Src/fdcan.cyclo ./Core/Src/fdcan.d ./Core/Src/fdcan.o ./Core/Src/fdcan.su ./Core/Src/flash.cyclo ./Core/Src/flash.d ./Core/Src/flash.o ./Core/Src/flash.su ./Core/Src/functions.cyclo ./Core/Src/functions.d ./Core/Src/functions.o ./Core/Src/functions.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/gun_control.cyclo ./Core/Src/gun_control.d ./Core/Src/gun_control.o ./Core/Src/gun_control.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/peripherals.cyclo ./Core/Src/peripherals.d ./Core/Src/peripherals.o ./Core/Src/peripherals.su ./Core/Src/power_management.cyclo ./Core/Src/power_management.d ./Core/Src/power_management.o ./Core/Src/power_management.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/timing.cyclo ./Core/Src/timing.d ./Core/Src/timing.o ./Core/Src/timing.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

