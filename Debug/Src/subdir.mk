################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lcd_start_page.c \
../Src/main.c \
../Src/mx_init.c \
../Src/peripheral.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/lcd_start_page.o \
./Src/main.o \
./Src/mx_init.o \
./Src/peripheral.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/lcd_start_page.d \
./Src/main.d \
./Src/mx_init.d \
./Src/peripheral.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -DSTM32 -DSTM32F746NGHx -DSTM32F746G_DISCO -DSTM32F7 -c -I../Inc -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/CMSIS/Include" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/BSP/STM32746G-Discovery" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/BSP/Fonts" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/lcd_start_page.cyclo ./Src/lcd_start_page.d ./Src/lcd_start_page.o ./Src/lcd_start_page.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/mx_init.cyclo ./Src/mx_init.d ./Src/mx_init.o ./Src/mx_init.su ./Src/peripheral.cyclo ./Src/peripheral.d ./Src/peripheral.o ./Src/peripheral.su ./Src/stm32f7xx_hal_msp.cyclo ./Src/stm32f7xx_hal_msp.d ./Src/stm32f7xx_hal_msp.o ./Src/stm32f7xx_hal_msp.su ./Src/stm32f7xx_it.cyclo ./Src/stm32f7xx_it.d ./Src/stm32f7xx_it.o ./Src/stm32f7xx_it.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f7xx.cyclo ./Src/system_stm32f7xx.d ./Src/system_stm32f7xx.o ./Src/system_stm32f7xx.su

.PHONY: clean-Src

