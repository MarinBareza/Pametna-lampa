################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BSP/ble.c \
../Src/BSP/led.c \
../Src/BSP/max17048.c 

OBJS += \
./Src/BSP/ble.o \
./Src/BSP/led.o \
./Src/BSP/max17048.o 

C_DEPS += \
./Src/BSP/ble.d \
./Src/BSP/led.d \
./Src/BSP/max17048.d 


# Each subdirectory must supply rules for building sources it contributes
Src/BSP/%.o: ../Src/BSP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L073xx -I"C:/Users/Bareza/OneDrive - Visoko uciliste Algebra/Immersa/Pametna_Lampa/Inc" -I"C:/Users/Bareza/OneDrive - Visoko uciliste Algebra/Immersa/Pametna_Lampa/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Bareza/OneDrive - Visoko uciliste Algebra/Immersa/Pametna_Lampa/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Bareza/OneDrive - Visoko uciliste Algebra/Immersa/Pametna_Lampa/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Bareza/OneDrive - Visoko uciliste Algebra/Immersa/Pametna_Lampa/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


