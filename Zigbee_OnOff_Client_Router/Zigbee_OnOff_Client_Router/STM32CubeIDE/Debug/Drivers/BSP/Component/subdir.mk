################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/Components/ssd1315/ssd1315.c \
H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/Components/ssd1315/ssd1315_reg.c 

OBJS += \
./Drivers/BSP/Component/ssd1315.o \
./Drivers/BSP/Component/ssd1315_reg.o 

C_DEPS += \
./Drivers/BSP/Component/ssd1315.d \
./Drivers/BSP/Component/ssd1315_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Component/ssd1315.o: H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/Components/ssd1315/ssd1315.c Drivers/BSP/Component/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DZIGBEE_WB -DSTM32WB55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../Drivers/BSP/STM32WB5MM-DK -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_WPAN -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../Middlewares/ST/STM32_WPAN/utilities -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Middlewares/ST/STM32_WPAN/zigbee/core/inc -I../../Middlewares/ST/STM32_WPAN/zigbee/stack -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include/mac -I../../Drivers/CMSIS/Include -I../../Utilities/sequencer -I../../Utilities/lpm/tiny_lpm -I../../Utilities/LCD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/Component/ssd1315.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Component/ssd1315_reg.o: H:/STM32WB5MM-DK\ Project/Zigbee_OnOff_Client_Router/Zigbee_OnOff_Client_Router/Drivers/BSP/Components/ssd1315/ssd1315_reg.c Drivers/BSP/Component/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DZIGBEE_WB -DSTM32WB55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../Drivers/BSP/STM32WB5MM-DK -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_WPAN -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../Middlewares/ST/STM32_WPAN/utilities -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Middlewares/ST/STM32_WPAN/zigbee/core/inc -I../../Middlewares/ST/STM32_WPAN/zigbee/stack -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include -I../../Middlewares/ST/STM32_WPAN/zigbee/stack/include/mac -I../../Drivers/CMSIS/Include -I../../Utilities/sequencer -I../../Utilities/lpm/tiny_lpm -I../../Utilities/LCD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/Component/ssd1315_reg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Component

clean-Drivers-2f-BSP-2f-Component:
	-$(RM) ./Drivers/BSP/Component/ssd1315.cyclo ./Drivers/BSP/Component/ssd1315.d ./Drivers/BSP/Component/ssd1315.o ./Drivers/BSP/Component/ssd1315.su ./Drivers/BSP/Component/ssd1315_reg.cyclo ./Drivers/BSP/Component/ssd1315_reg.d ./Drivers/BSP/Component/ssd1315_reg.o ./Drivers/BSP/Component/ssd1315_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Component

