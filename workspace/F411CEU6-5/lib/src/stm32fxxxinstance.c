/************************************************************************
	STM32FXXX INSTANCE
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32FXXX
Update: 07/01/2024
Comment:
	
************************************************************************/
#include "stm32fxxxinstance.h"

/*** HARDWARE HANDLER ***/
/*** ADC ***/
#if defined(STM32F411xE)
ADC_Common_TypeDef* adc_common_instance(void){return ADC1_COMMON;}
#endif
#ifdef STM32F446xx
ADC_Common_TypeDef* adc_common_instance(void){return ADC123_COMMON;}
#endif
ADC_TypeDef* adc1_instance(void){return ADC1;}
#ifdef STM32F446xx
ADC_TypeDef* adc2_instance(void){return ADC2;}
ADC_TypeDef* adc3_instance(void){return ADC3;}
#endif
/*** CAN ***/
#ifdef STM32F446xx
CAN_TypeDef* can1_instance(void){return CAN1;}
CAN_TypeDef* can2_instance(void){return CAN2;}
#endif
/*** CEC ***/
#ifdef STM32F446xx
CEC_TypeDef* cec_instance(void){return CEC;}
#endif
/*** CRC ***/
CRC_TypeDef* crc_instance(void){return CRC;}
/*** DAC ***/
#ifdef STM32F446xx
DAC_TypeDef* dac_instance(void){return DAC;}
#endif
/*** DBGMCU ***/
DBGMCU_TypeDef* dbgmcu_instance(void){return DBGMCU;}
/*** DCMI ***/
#ifdef STM32F446xx
DCMI_TypeDef* dcmi_instance(void){return DCMI;}
#endif
/*** DMA ***/
DMA_TypeDef* dma1_instance(void){return DMA1;}
DMA_Stream_TypeDef* dma1_stream0_instance(void){return DMA1_Stream0;}
DMA_Stream_TypeDef* dma1_stream1_instance(void){return DMA1_Stream1;}
DMA_Stream_TypeDef* dma1_stream2_instance(void){return DMA1_Stream2;}
DMA_Stream_TypeDef* dma1_stream3_instance(void){return DMA1_Stream3;}
DMA_Stream_TypeDef* dma1_stream4_instance(void){return DMA1_Stream4;}
DMA_Stream_TypeDef* dma1_stream5_instance(void){return DMA1_Stream5;}
DMA_Stream_TypeDef* dma1_stream6_instance(void){return DMA1_Stream6;}
DMA_Stream_TypeDef* dma1_stream7_instance(void){return DMA1_Stream7;}
DMA_TypeDef* dma2_instance(void){return DMA2;}
DMA_Stream_TypeDef* dma2_stream0_instance(void){return DMA2_Stream0;}
DMA_Stream_TypeDef* dma2_stream1_instance(void){return DMA2_Stream1;}
DMA_Stream_TypeDef* dma2_stream2_instance(void){return DMA2_Stream2;}
DMA_Stream_TypeDef* dma2_stream3_instance(void){return DMA2_Stream3;}
DMA_Stream_TypeDef* dma2_stream4_instance(void){return DMA2_Stream4;}
DMA_Stream_TypeDef* dma2_stream5_instance(void){return DMA2_Stream5;}
DMA_Stream_TypeDef* dma2_stream6_instance(void){return DMA2_Stream6;}
DMA_Stream_TypeDef* dma2_stream7_instance(void){return DMA2_Stream7;}
/*** EXTI ***/
EXTI_TypeDef* exti_instance(void){return EXTI;}
/*** FLASH ***/
FLASH_TypeDef* flash_instance(void){return FLASH;}
/*** FMC ***/
#ifdef STM32F446xx
FMC_Bank1_TypeDef* fmc_bank1_instance(void){return (FMC_Bank1_TypeDef*) FMC_Bank1_R_BASE;}
FMC_Bank1E_TypeDef* fmc_bank1e_instance(void){return (FMC_Bank1E_TypeDef*) FMC_Bank1E_R_BASE;}
FMC_Bank3_TypeDef* fmc_bank3_instance(void){return (FMC_Bank3_TypeDef*) FMC_Bank3_R_BASE;}
FMC_Bank5_6_TypeDef* fmc_bank5_6_instance(void){return (FMC_Bank5_6_TypeDef*) FMC_Bank5_6_R_BASE;}
#endif
/*** GPIO ***/
GPIO_TypeDef* gpioa_instance(void){return GPIOA;}
GPIO_TypeDef* gpiob_instance(void){return GPIOB;}
GPIO_TypeDef* gpioc_instance(void){return GPIOC;}
GPIO_TypeDef* gpiod_instance(void){return GPIOD;}
GPIO_TypeDef* gpioe_instance(void){return GPIOE;}
#ifdef STM32F446xx
GPIO_TypeDef* gpiof_instance(void){return GPIOF;}
GPIO_TypeDef* gpiog_instance(void){return GPIOG;}
#endif
GPIO_TypeDef* gpioh_instance(void){return GPIOH;}
/*** SYSCFG ***/
SYSCFG_TypeDef* syscfg_instance(void){return SYSCFG;}
/*** I2C ***/
I2C_TypeDef* i2c1_instance(void){return I2C1;}
I2C_TypeDef* i2c2_instance(void){return I2C2;}
I2C_TypeDef* i2c3_instance(void){return I2C3;}
/*** FMPI2C ***/
#ifdef STM32F446xx
FMPI2C_TypeDef* fmpi2c1_instance(void){return FMPI2C1;}
#endif
/*** IWDG ***/
IWDG_TypeDef* iwdg_instance(void){return IWDG;}
/*** PWR ***/
PWR_TypeDef* pwr_instance(void){return PWR;}
/*** RCC ***/
RCC_TypeDef* rcc_instance(void){return RCC;}
/*** RTC ***/
RTC_TypeDef* rtc_instance(void){return RTC;}
/*** SAI ***/
#ifdef STM32F446xx
SAI_TypeDef* sai1_instance(void){return SAI1;}
SAI_Block_TypeDef* sai1_block_a_instance(void){return SAI1_Block_A;}
SAI_Block_TypeDef* sai1_block_b_instance(void){return SAI1_Block_B;}
SAI_TypeDef* sai2_instance(void){return SAI2;}
SAI_Block_TypeDef* sai2_block_a_instance(void){return SAI2_Block_A;}
SAI_Block_TypeDef* sai2_block_b_instance(void){return SAI2_Block_B;}
#endif
/*** SDIO ***/
SDIO_TypeDef* sdio_instance(void){return SDIO;}
/*** SPI ***/
SPI_TypeDef* spi1_instance(void){return SPI1;}
SPI_TypeDef* spi2_instance(void){return SPI2;}
SPI_TypeDef* spi3_instance(void){return SPI3;}
SPI_TypeDef* spi4_instance(void){return SPI4;}
/*** QUADSPI ***/
#ifdef STM32F446xx
QUADSPI_TypeDef* quadspi_instance(void){return (QUADSPI_TypeDef*) QSPI_R_BASE;}
#endif
/*** SPDIFRX ***/
#ifdef STM32F446xx
SPDIFRX_TypeDef* spdifrx_instance(void){return SPDIFRX;}
#endif
/*** TIM ***/
TIM_TypeDef* tim1_instance(void){return TIM1;}
TIM_TypeDef* tim2_instance(void){return TIM2;}
TIM_TypeDef* tim3_instance(void){return TIM3;}
TIM_TypeDef* tim4_instance(void){return TIM4;}
TIM_TypeDef* tim5_instance(void){return TIM5;}
#ifdef STM32F446xx
TIM_TypeDef* tim6_instance(void){return TIM6;}
TIM_TypeDef* tim7_instance(void){return TIM7;}
#endif
#ifdef STM32F446xx
TIM_TypeDef* tim8_instance(void){return TIM8;}
#endif
TIM_TypeDef* tim9_instance(void){return TIM9;}
TIM_TypeDef* tim10_instance(void){return TIM10;}
TIM_TypeDef* tim11_instance(void){return TIM11;}
#ifdef STM32F446xx
TIM_TypeDef* tim12_instance(void){return TIM12;}
TIM_TypeDef* tim13_instance(void){return TIM13;}
TIM_TypeDef* tim14_instance(void){return TIM14;}
#endif
/*** USART ***/
USART_TypeDef* usart1_instance(void){return USART1;}
USART_TypeDef* usart2_instance(void){return USART2;}
#ifdef STM32F446xx
USART_TypeDef* usart3_instance(void){return USART3;}
USART_TypeDef* uart4_instance(void){return UART4;}
USART_TypeDef* uart5_instance(void){return UART5;}
#endif
USART_TypeDef* usart6_instance(void){return USART6;}
/*** WWDG ***/
WWDG_TypeDef* wwdg_instance(void){return WWDG;}
/*** USB ***/
USB_OTG_GlobalTypeDef* usb_otg_global_instance(void){return (USB_OTG_GlobalTypeDef*) USB_OTG_GLOBAL_BASE;}
USB_OTG_DeviceTypeDef* usb_otg_device_instance(void){return (USB_OTG_DeviceTypeDef*) USB_OTG_DEVICE_BASE;}
USB_OTG_INEndpointTypeDef* usb_otg_inendpoint_instance(void){return (USB_OTG_INEndpointTypeDef*) USB_OTG_IN_ENDPOINT_BASE;}
USB_OTG_OUTEndpointTypeDef* usb_otg_outendpoint_instance(void){return (USB_OTG_OUTEndpointTypeDef*) USB_OTG_OUT_ENDPOINT_BASE;}
USB_OTG_HostTypeDef* usb_otg_host_instance(void){return (USB_OTG_HostTypeDef*) USB_OTG_HOST_BASE;}
USB_OTG_HostChannelTypeDef* usb_otg_hostchannel_instance(void){return (USB_OTG_HostChannelTypeDef*) USB_OTG_HOST_CHANNEL_BASE;}

/***
TypeDef -> Instance -> Handler
***/

/*** EOF ***/

