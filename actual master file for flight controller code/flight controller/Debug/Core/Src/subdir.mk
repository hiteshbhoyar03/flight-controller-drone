################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BMI088.c \
../Core/Src/BMM350.c \
../Core/Src/CRSF.c \
../Core/Src/DSHOT.c \
../Core/Src/EEPROM.c \
../Core/Src/IBUS.c \
../Core/Src/ICM42688P.c \
../Core/Src/ICM45686.c \
../Core/Src/ICP20100.c \
../Core/Src/M8N.c \
../Core/Src/MS5611.c \
../Core/Src/MYFUNCTIONS.c \
../Core/Src/SBUS.c \
../Core/Src/adc.c \
../Core/Src/dma.c \
../Core/Src/eth.c \
../Core/Src/fdcan.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/memorymap.c \
../Core/Src/sdmmc.c \
../Core/Src/spi.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/usb_otg.c 

OBJS += \
./Core/Src/BMI088.o \
./Core/Src/BMM350.o \
./Core/Src/CRSF.o \
./Core/Src/DSHOT.o \
./Core/Src/EEPROM.o \
./Core/Src/IBUS.o \
./Core/Src/ICM42688P.o \
./Core/Src/ICM45686.o \
./Core/Src/ICP20100.o \
./Core/Src/M8N.o \
./Core/Src/MS5611.o \
./Core/Src/MYFUNCTIONS.o \
./Core/Src/SBUS.o \
./Core/Src/adc.o \
./Core/Src/dma.o \
./Core/Src/eth.o \
./Core/Src/fdcan.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/memorymap.o \
./Core/Src/sdmmc.o \
./Core/Src/spi.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/usb_otg.o 

C_DEPS += \
./Core/Src/BMI088.d \
./Core/Src/BMM350.d \
./Core/Src/CRSF.d \
./Core/Src/DSHOT.d \
./Core/Src/EEPROM.d \
./Core/Src/IBUS.d \
./Core/Src/ICM42688P.d \
./Core/Src/ICM45686.d \
./Core/Src/ICP20100.d \
./Core/Src/M8N.d \
./Core/Src/MS5611.d \
./Core/Src/MYFUNCTIONS.d \
./Core/Src/SBUS.d \
./Core/Src/adc.d \
./Core/Src/dma.d \
./Core/Src/eth.d \
./Core/Src/fdcan.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/memorymap.d \
./Core/Src/sdmmc.d \
./Core/Src/spi.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DUSE_FULL_LL_DRIVER -DUSE_PWR_LDO_SUPPLY -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BMI088.cyclo ./Core/Src/BMI088.d ./Core/Src/BMI088.o ./Core/Src/BMI088.su ./Core/Src/BMM350.cyclo ./Core/Src/BMM350.d ./Core/Src/BMM350.o ./Core/Src/BMM350.su ./Core/Src/CRSF.cyclo ./Core/Src/CRSF.d ./Core/Src/CRSF.o ./Core/Src/CRSF.su ./Core/Src/DSHOT.cyclo ./Core/Src/DSHOT.d ./Core/Src/DSHOT.o ./Core/Src/DSHOT.su ./Core/Src/EEPROM.cyclo ./Core/Src/EEPROM.d ./Core/Src/EEPROM.o ./Core/Src/EEPROM.su ./Core/Src/IBUS.cyclo ./Core/Src/IBUS.d ./Core/Src/IBUS.o ./Core/Src/IBUS.su ./Core/Src/ICM42688P.cyclo ./Core/Src/ICM42688P.d ./Core/Src/ICM42688P.o ./Core/Src/ICM42688P.su ./Core/Src/ICM45686.cyclo ./Core/Src/ICM45686.d ./Core/Src/ICM45686.o ./Core/Src/ICM45686.su ./Core/Src/ICP20100.cyclo ./Core/Src/ICP20100.d ./Core/Src/ICP20100.o ./Core/Src/ICP20100.su ./Core/Src/M8N.cyclo ./Core/Src/M8N.d ./Core/Src/M8N.o ./Core/Src/M8N.su ./Core/Src/MS5611.cyclo ./Core/Src/MS5611.d ./Core/Src/MS5611.o ./Core/Src/MS5611.su ./Core/Src/MYFUNCTIONS.cyclo ./Core/Src/MYFUNCTIONS.d ./Core/Src/MYFUNCTIONS.o ./Core/Src/MYFUNCTIONS.su ./Core/Src/SBUS.cyclo ./Core/Src/SBUS.d ./Core/Src/SBUS.o ./Core/Src/SBUS.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/eth.cyclo ./Core/Src/eth.d ./Core/Src/eth.o ./Core/Src/eth.su ./Core/Src/fdcan.cyclo ./Core/Src/fdcan.d ./Core/Src/fdcan.o ./Core/Src/fdcan.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/memorymap.cyclo ./Core/Src/memorymap.d ./Core/Src/memorymap.o ./Core/Src/memorymap.su ./Core/Src/sdmmc.cyclo ./Core/Src/sdmmc.d ./Core/Src/sdmmc.o ./Core/Src/sdmmc.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/usb_otg.cyclo ./Core/Src/usb_otg.d ./Core/Src/usb_otg.o ./Core/Src/usb_otg.su

.PHONY: clean-Core-2f-Src

