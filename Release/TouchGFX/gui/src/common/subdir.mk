################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/common/CustomKeyboard.cpp \
../TouchGFX/gui/src/common/FrontendApplication.cpp 

OBJS += \
./TouchGFX/gui/src/common/CustomKeyboard.o \
./TouchGFX/gui/src/common/FrontendApplication.o 

CPP_DEPS += \
./TouchGFX/gui/src/common/CustomKeyboard.d \
./TouchGFX/gui/src/common/FrontendApplication.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/common/%.o: ../TouchGFX/gui/src/common/%.cpp TouchGFX/gui/src/common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../TouchGFX/target/generated -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../TouchGFX/App -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/gui/include -I../TouchGFX/generated/videos/include -I../USB_HOST/App -I../FATFS/App -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../FATFS/Target -I../USB_HOST/Target -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-common

clean-TouchGFX-2f-gui-2f-src-2f-common:
	-$(RM) ./TouchGFX/gui/src/common/CustomKeyboard.d ./TouchGFX/gui/src/common/CustomKeyboard.o ./TouchGFX/gui/src/common/FrontendApplication.d ./TouchGFX/gui/src/common/FrontendApplication.o

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-common

