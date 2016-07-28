################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Fonts/font12.c \
../system/Fonts/font16.c \
../system/Fonts/font20.c \
../system/Fonts/font24.c \
../system/Fonts/font8.c 

OBJS += \
./system/Fonts/font12.o \
./system/Fonts/font16.o \
./system/Fonts/font20.o \
./system/Fonts/font24.o \
./system/Fonts/font8.o 

C_DEPS += \
./system/Fonts/font12.d \
./system/Fonts/font16.d \
./system/Fonts/font20.d \
./system/Fonts/font24.d \
./system/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
system/Fonts/%.o: ../system/Fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../include/FreeRTOS/Source/include" -I"../include/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


