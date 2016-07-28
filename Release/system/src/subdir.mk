################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f429i_discovery.c \
../system/src/stm32f429i_discovery_lcd.c \
../system/src/stm32f429i_discovery_sdram.c 

OBJS += \
./system/src/stm32f429i_discovery.o \
./system/src/stm32f429i_discovery_lcd.o \
./system/src/stm32f429i_discovery_sdram.o 

C_DEPS += \
./system/src/stm32f429i_discovery.d \
./system/src/stm32f429i_discovery_lcd.d \
./system/src/stm32f429i_discovery_sdram.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/%.o: ../system/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../include/FreeRTOS/Source/include" -I"../include/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


