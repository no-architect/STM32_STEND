################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/image_icon_keyboard_even_row.cpp \
../TouchGFX/generated/images/src/image_icon_keyboard_highlighted.cpp \
../TouchGFX/generated/images/src/image_icon_keyboard_odd_row.cpp \
../TouchGFX/generated/images/src/image_keyboard_background.cpp \
../TouchGFX/generated/images/src/image_keyboard_key_delete_highlighted.cpp \
../TouchGFX/generated/images/src/image_keyboard_key_highlighted.cpp \
../TouchGFX/generated/images/src/image_keyboard_key_num_highlighted.cpp \
../TouchGFX/generated/images/src/image_keyboard_key_shift_highlighted.cpp \
../TouchGFX/generated/images/src/image_keyboard_space_highlighted.cpp \
../TouchGFX/generated/images/src/image_logomskrework_trick.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/image_icon_keyboard_even_row.o \
./TouchGFX/generated/images/src/image_icon_keyboard_highlighted.o \
./TouchGFX/generated/images/src/image_icon_keyboard_odd_row.o \
./TouchGFX/generated/images/src/image_keyboard_background.o \
./TouchGFX/generated/images/src/image_keyboard_key_delete_highlighted.o \
./TouchGFX/generated/images/src/image_keyboard_key_highlighted.o \
./TouchGFX/generated/images/src/image_keyboard_key_num_highlighted.o \
./TouchGFX/generated/images/src/image_keyboard_key_shift_highlighted.o \
./TouchGFX/generated/images/src/image_keyboard_space_highlighted.o \
./TouchGFX/generated/images/src/image_logomskrework_trick.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/image_icon_keyboard_even_row.d \
./TouchGFX/generated/images/src/image_icon_keyboard_highlighted.d \
./TouchGFX/generated/images/src/image_icon_keyboard_odd_row.d \
./TouchGFX/generated/images/src/image_keyboard_background.d \
./TouchGFX/generated/images/src/image_keyboard_key_delete_highlighted.d \
./TouchGFX/generated/images/src/image_keyboard_key_highlighted.d \
./TouchGFX/generated/images/src/image_keyboard_key_num_highlighted.d \
./TouchGFX/generated/images/src/image_keyboard_key_shift_highlighted.d \
./TouchGFX/generated/images/src/image_keyboard_space_highlighted.d \
./TouchGFX/generated/images/src/image_logomskrework_trick.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/%.o: ../TouchGFX/generated/images/src/%.cpp TouchGFX/generated/images/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../TouchGFX/target/generated -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../TouchGFX/App -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/gui/include -I../TouchGFX/generated/videos/include -I../USB_HOST/App -I../FATFS/App -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../FATFS/Target -I../USB_HOST/Target -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src

clean-TouchGFX-2f-generated-2f-images-2f-src:
	-$(RM) ./TouchGFX/generated/images/src/BitmapDatabase.d ./TouchGFX/generated/images/src/BitmapDatabase.o ./TouchGFX/generated/images/src/image_icon_keyboard_even_row.d ./TouchGFX/generated/images/src/image_icon_keyboard_even_row.o ./TouchGFX/generated/images/src/image_icon_keyboard_highlighted.d ./TouchGFX/generated/images/src/image_icon_keyboard_highlighted.o ./TouchGFX/generated/images/src/image_icon_keyboard_odd_row.d ./TouchGFX/generated/images/src/image_icon_keyboard_odd_row.o ./TouchGFX/generated/images/src/image_keyboard_background.d ./TouchGFX/generated/images/src/image_keyboard_background.o ./TouchGFX/generated/images/src/image_keyboard_key_delete_highlighted.d ./TouchGFX/generated/images/src/image_keyboard_key_delete_highlighted.o ./TouchGFX/generated/images/src/image_keyboard_key_highlighted.d ./TouchGFX/generated/images/src/image_keyboard_key_highlighted.o ./TouchGFX/generated/images/src/image_keyboard_key_num_highlighted.d ./TouchGFX/generated/images/src/image_keyboard_key_num_highlighted.o ./TouchGFX/generated/images/src/image_keyboard_key_shift_highlighted.d ./TouchGFX/generated/images/src/image_keyboard_key_shift_highlighted.o ./TouchGFX/generated/images/src/image_keyboard_space_highlighted.d ./TouchGFX/generated/images/src/image_keyboard_space_highlighted.o ./TouchGFX/generated/images/src/image_logomskrework_trick.d ./TouchGFX/generated/images/src/image_logomskrework_trick.o

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src

