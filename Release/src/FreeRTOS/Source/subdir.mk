################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOS/Source/croutine.c \
../src/FreeRTOS/Source/event_groups.c \
../src/FreeRTOS/Source/list.c \
../src/FreeRTOS/Source/queue.c \
../src/FreeRTOS/Source/tasks.c \
../src/FreeRTOS/Source/timers.c 

O_SRCS += \
../src/FreeRTOS/Source/croutine.o \
../src/FreeRTOS/Source/event_groups.o \
../src/FreeRTOS/Source/list.o \
../src/FreeRTOS/Source/queue.o \
../src/FreeRTOS/Source/tasks.o \
../src/FreeRTOS/Source/timers.o 

OBJS += \
./src/FreeRTOS/Source/croutine.o \
./src/FreeRTOS/Source/event_groups.o \
./src/FreeRTOS/Source/list.o \
./src/FreeRTOS/Source/queue.o \
./src/FreeRTOS/Source/tasks.o \
./src/FreeRTOS/Source/timers.o 

C_DEPS += \
./src/FreeRTOS/Source/croutine.d \
./src/FreeRTOS/Source/event_groups.d \
./src/FreeRTOS/Source/list.d \
./src/FreeRTOS/Source/queue.d \
./src/FreeRTOS/Source/tasks.d \
./src/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/Source/%.o: ../src/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../include/FreeRTOS/Source/include" -I"../include/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


