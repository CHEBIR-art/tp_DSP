################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f746nghx.s 

OBJS += \
./Startup/startup_stm32f746nghx.o 

S_DEPS += \
./Startup/startup_stm32f746nghx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/CMSIS/Include" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/BSP/STM32746G-Discovery" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/BSP/Fonts" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Users/user/Desktop/Template_TP_DSP/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f746nghx.d ./Startup/startup_stm32f746nghx.o

.PHONY: clean-Startup

