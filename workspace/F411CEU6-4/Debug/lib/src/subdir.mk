################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/74hc595.c \
../lib/src/armfunction.c \
../lib/src/armlcd.c \
../lib/src/armquery.c \
../lib/src/armsystick.c \
../lib/src/buffer.c \
../lib/src/circbuffer.c \
../lib/src/explode.c \
../lib/src/stm32fxxxadc.c \
../lib/src/stm32fxxxadc1.c \
../lib/src/stm32fxxxadc2.c \
../lib/src/stm32fxxxadc3.c \
../lib/src/stm32fxxxcrc.c \
../lib/src/stm32fxxxdma.c \
../lib/src/stm32fxxxflash.c \
../lib/src/stm32fxxxgpio.c \
../lib/src/stm32fxxxinstance.c \
../lib/src/stm32fxxxmapping.c \
../lib/src/stm32fxxxnvic.c \
../lib/src/stm32fxxxpwr.c \
../lib/src/stm32fxxxrcc.c \
../lib/src/stm32fxxxrtc.c \
../lib/src/stm32fxxxsram.c \
../lib/src/stm32fxxxsyscfg.c \
../lib/src/stm32fxxxtim1and8.c \
../lib/src/stm32fxxxtim2to5.c \
../lib/src/stm32fxxxtim6and7.c \
../lib/src/stm32fxxxtim9to14.c \
../lib/src/stm32fxxxusart.c \
../lib/src/znpid.c 

OBJS += \
./lib/src/74hc595.o \
./lib/src/armfunction.o \
./lib/src/armlcd.o \
./lib/src/armquery.o \
./lib/src/armsystick.o \
./lib/src/buffer.o \
./lib/src/circbuffer.o \
./lib/src/explode.o \
./lib/src/stm32fxxxadc.o \
./lib/src/stm32fxxxadc1.o \
./lib/src/stm32fxxxadc2.o \
./lib/src/stm32fxxxadc3.o \
./lib/src/stm32fxxxcrc.o \
./lib/src/stm32fxxxdma.o \
./lib/src/stm32fxxxflash.o \
./lib/src/stm32fxxxgpio.o \
./lib/src/stm32fxxxinstance.o \
./lib/src/stm32fxxxmapping.o \
./lib/src/stm32fxxxnvic.o \
./lib/src/stm32fxxxpwr.o \
./lib/src/stm32fxxxrcc.o \
./lib/src/stm32fxxxrtc.o \
./lib/src/stm32fxxxsram.o \
./lib/src/stm32fxxxsyscfg.o \
./lib/src/stm32fxxxtim1and8.o \
./lib/src/stm32fxxxtim2to5.o \
./lib/src/stm32fxxxtim6and7.o \
./lib/src/stm32fxxxtim9to14.o \
./lib/src/stm32fxxxusart.o \
./lib/src/znpid.o 

C_DEPS += \
./lib/src/74hc595.d \
./lib/src/armfunction.d \
./lib/src/armlcd.d \
./lib/src/armquery.d \
./lib/src/armsystick.d \
./lib/src/buffer.d \
./lib/src/circbuffer.d \
./lib/src/explode.d \
./lib/src/stm32fxxxadc.d \
./lib/src/stm32fxxxadc1.d \
./lib/src/stm32fxxxadc2.d \
./lib/src/stm32fxxxadc3.d \
./lib/src/stm32fxxxcrc.d \
./lib/src/stm32fxxxdma.d \
./lib/src/stm32fxxxflash.d \
./lib/src/stm32fxxxgpio.d \
./lib/src/stm32fxxxinstance.d \
./lib/src/stm32fxxxmapping.d \
./lib/src/stm32fxxxnvic.d \
./lib/src/stm32fxxxpwr.d \
./lib/src/stm32fxxxrcc.d \
./lib/src/stm32fxxxrtc.d \
./lib/src/stm32fxxxsram.d \
./lib/src/stm32fxxxsyscfg.d \
./lib/src/stm32fxxxtim1and8.d \
./lib/src/stm32fxxxtim2to5.d \
./lib/src/stm32fxxxtim6and7.d \
./lib/src/stm32fxxxtim9to14.d \
./lib/src/stm32fxxxusart.d \
./lib/src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o lib/src/%.su lib/src/%.cyclo: ../lib/src/%.c lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/Core/Inc" -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/lib/src" -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/Drivers/CMSIS/Include" -I"D:/GitHub_2024/STM32-F411CEU6/workspace/F411CEU6-4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-src

clean-lib-2f-src:
	-$(RM) ./lib/src/74hc595.cyclo ./lib/src/74hc595.d ./lib/src/74hc595.o ./lib/src/74hc595.su ./lib/src/armfunction.cyclo ./lib/src/armfunction.d ./lib/src/armfunction.o ./lib/src/armfunction.su ./lib/src/armlcd.cyclo ./lib/src/armlcd.d ./lib/src/armlcd.o ./lib/src/armlcd.su ./lib/src/armquery.cyclo ./lib/src/armquery.d ./lib/src/armquery.o ./lib/src/armquery.su ./lib/src/armsystick.cyclo ./lib/src/armsystick.d ./lib/src/armsystick.o ./lib/src/armsystick.su ./lib/src/buffer.cyclo ./lib/src/buffer.d ./lib/src/buffer.o ./lib/src/buffer.su ./lib/src/circbuffer.cyclo ./lib/src/circbuffer.d ./lib/src/circbuffer.o ./lib/src/circbuffer.su ./lib/src/explode.cyclo ./lib/src/explode.d ./lib/src/explode.o ./lib/src/explode.su ./lib/src/stm32fxxxadc.cyclo ./lib/src/stm32fxxxadc.d ./lib/src/stm32fxxxadc.o ./lib/src/stm32fxxxadc.su ./lib/src/stm32fxxxadc1.cyclo ./lib/src/stm32fxxxadc1.d ./lib/src/stm32fxxxadc1.o ./lib/src/stm32fxxxadc1.su ./lib/src/stm32fxxxadc2.cyclo ./lib/src/stm32fxxxadc2.d ./lib/src/stm32fxxxadc2.o ./lib/src/stm32fxxxadc2.su ./lib/src/stm32fxxxadc3.cyclo ./lib/src/stm32fxxxadc3.d ./lib/src/stm32fxxxadc3.o ./lib/src/stm32fxxxadc3.su ./lib/src/stm32fxxxcrc.cyclo ./lib/src/stm32fxxxcrc.d ./lib/src/stm32fxxxcrc.o ./lib/src/stm32fxxxcrc.su ./lib/src/stm32fxxxdma.cyclo ./lib/src/stm32fxxxdma.d ./lib/src/stm32fxxxdma.o ./lib/src/stm32fxxxdma.su ./lib/src/stm32fxxxflash.cyclo ./lib/src/stm32fxxxflash.d ./lib/src/stm32fxxxflash.o ./lib/src/stm32fxxxflash.su ./lib/src/stm32fxxxgpio.cyclo ./lib/src/stm32fxxxgpio.d ./lib/src/stm32fxxxgpio.o ./lib/src/stm32fxxxgpio.su ./lib/src/stm32fxxxinstance.cyclo ./lib/src/stm32fxxxinstance.d ./lib/src/stm32fxxxinstance.o ./lib/src/stm32fxxxinstance.su ./lib/src/stm32fxxxmapping.cyclo ./lib/src/stm32fxxxmapping.d ./lib/src/stm32fxxxmapping.o ./lib/src/stm32fxxxmapping.su ./lib/src/stm32fxxxnvic.cyclo ./lib/src/stm32fxxxnvic.d ./lib/src/stm32fxxxnvic.o ./lib/src/stm32fxxxnvic.su ./lib/src/stm32fxxxpwr.cyclo ./lib/src/stm32fxxxpwr.d ./lib/src/stm32fxxxpwr.o ./lib/src/stm32fxxxpwr.su ./lib/src/stm32fxxxrcc.cyclo ./lib/src/stm32fxxxrcc.d ./lib/src/stm32fxxxrcc.o ./lib/src/stm32fxxxrcc.su ./lib/src/stm32fxxxrtc.cyclo ./lib/src/stm32fxxxrtc.d ./lib/src/stm32fxxxrtc.o ./lib/src/stm32fxxxrtc.su ./lib/src/stm32fxxxsram.cyclo ./lib/src/stm32fxxxsram.d ./lib/src/stm32fxxxsram.o ./lib/src/stm32fxxxsram.su ./lib/src/stm32fxxxsyscfg.cyclo ./lib/src/stm32fxxxsyscfg.d ./lib/src/stm32fxxxsyscfg.o ./lib/src/stm32fxxxsyscfg.su ./lib/src/stm32fxxxtim1and8.cyclo ./lib/src/stm32fxxxtim1and8.d ./lib/src/stm32fxxxtim1and8.o ./lib/src/stm32fxxxtim1and8.su ./lib/src/stm32fxxxtim2to5.cyclo ./lib/src/stm32fxxxtim2to5.d ./lib/src/stm32fxxxtim2to5.o ./lib/src/stm32fxxxtim2to5.su ./lib/src/stm32fxxxtim6and7.cyclo ./lib/src/stm32fxxxtim6and7.d ./lib/src/stm32fxxxtim6and7.o ./lib/src/stm32fxxxtim6and7.su ./lib/src/stm32fxxxtim9to14.cyclo ./lib/src/stm32fxxxtim9to14.d ./lib/src/stm32fxxxtim9to14.o ./lib/src/stm32fxxxtim9to14.su ./lib/src/stm32fxxxusart.cyclo ./lib/src/stm32fxxxusart.d ./lib/src/stm32fxxxusart.o ./lib/src/stm32fxxxusart.su ./lib/src/znpid.cyclo ./lib/src/znpid.d ./lib/src/znpid.o ./lib/src/znpid.su

.PHONY: clean-lib-2f-src

