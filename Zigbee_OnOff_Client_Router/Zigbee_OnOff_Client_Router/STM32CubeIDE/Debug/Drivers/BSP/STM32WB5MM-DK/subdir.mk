################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.c \
H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.c \
H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.c 

OBJS += \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.o \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.o \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.o 

C_DEPS += \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.d \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.d \
./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.o: H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.c Drivers/BSP/STM32WB5MM-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DZIGBEE_WB -DSTM32WB55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../Drivers/BSP/STM32WB5MM-DK -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_WPAN -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../Middlewares/ST/STM32_WPAN/utilities -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Middlewares/ST/STM32_WPAN/zigbee/core/inc -I../../Middlewares/ST/STM32_WPAN/zigbee/stack -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include/mac -I../../Drivers/CMSIS/Include -I../../Utilities/sequencer -I../../Utilities/lpm/tiny_lpm -I../../Utilities/LCD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.o: H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.c Drivers/BSP/STM32WB5MM-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DZIGBEE_WB -DSTM32WB55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../Drivers/BSP/STM32WB5MM-DK -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_WPAN -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../Middlewares/ST/STM32_WPAN/utilities -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Middlewares/ST/STM32_WPAN/zigbee/core/inc -I../../Middlewares/ST/STM32_WPAN/zigbee/stack -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include/mac -I../../Drivers/CMSIS/Include -I../../Utilities/sequencer -I../../Utilities/lpm/tiny_lpm -I../../Utilities/LCD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.o: H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.c Drivers/BSP/STM32WB5MM-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DZIGBEE_WB -DSTM32WB55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../Drivers/BSP/STM32WB5MM-DK -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_WPAN -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../Middlewares/ST/STM32_WPAN/utilities -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Middlewares/ST/STM32_WPAN/zigbee/core/inc -I../../Middlewares/ST/STM32_WPAN/zigbee/stack -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include/mac -I../../Drivers/CMSIS/Include -I../../Utilities/sequencer -I../../Utilities/lpm/tiny_lpm -I../../Utilities/LCD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32WB5MM-2d-DK

clean-Drivers-2f-BSP-2f-STM32WB5MM-2d-DK:
	-$(RM) ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.cyclo ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.d ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.o ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk.su ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.cyclo ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.d ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.o ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_bus.su ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.cyclo ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.d ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.o ./Drivers/BSP/STM32WB5MM-DK/stm32wb5mm_dk_lcd.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32WB5MM-2d-DK

