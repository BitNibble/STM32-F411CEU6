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
#ifdef __STM32F411xE_H
//ADC_Common_TypeDef* adc_common_instance(void){return (ADC_Common_TypeDef*) ADC1_COMMON_BASE;}
STM32FXXXADC_COMMON_TypeDef* adc_common_instance(void){return (STM32FXXXADC_COMMON_TypeDef*) ADC1_COMMON_BASE;}
#endif
#ifdef __STM32F446xx_H
ADC_Common_TypeDef* adc_common_instance(void){return (ADC_Common_TypeDef*) ADC123_COMMON_BASE;}
#endif
//ADC_TypeDef* adc1_instance(void){return (ADC_TypeDef*) ADC1_BASE;}
STM32FXXXADC_TypeDef* adc1_instance(void){return (STM32FXXXADC_TypeDef*) ADC1_BASE;}
#ifdef __STM32F446xx_H
ADC_TypeDef* adc2_instance(void){return (ADC_TypeDef*) ADC2_BASE;}
ADC_TypeDef* adc3_instance(void){return (ADC_TypeDef*) ADC3_BASE;}
#endif
/*** CAN ***/
#ifdef __STM32F446xx_H
CAN_TypeDef* can1_instance(void){return (CAN_TypeDef*) CAN1_BASE;}
CAN_TypeDef* can2_instance(void){return (CAN_TypeDef*) CAN2_BASE;}
#endif
/*** CEC ***/
#ifdef __STM32F446xx_H
CEC_TypeDef* cec_instance(void){return (CEC_TypeDef*) CEC_BASE;}
#endif
/*** CRC ***/
CRC_TypeDef* crc_instance(void){return (CRC_TypeDef*) CRC_BASE;}
/*** DAC ***/
#ifdef __STM32F446xx_H
DAC_TypeDef* dac_instance(void){return (DAC_TypeDef*) DAC_BASE;}
#endif
/*** DBGMCU ***/
DBGMCU_TypeDef* dbgmcu_instance(void){return (DBGMCU_TypeDef*) DBGMCU_BASE;}
/*** DCMI ***/
#ifdef __STM32F446xx_H
DCMI_TypeDef* dcmi_instance(void){return (DCMI_TypeDef*) DCMI_BASE;}
#endif
/*** DMA ***/
DMA_TypeDef* dma1_instance(void){return (DMA_TypeDef*) DMA1_BASE;}
DMA_Stream_TypeDef* dma1_stream0_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream0_BASE;}
DMA_Stream_TypeDef* dma1_stream1_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream1_BASE;}
DMA_Stream_TypeDef* dma1_stream2_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream2_BASE;}
DMA_Stream_TypeDef* dma1_stream3_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream3_BASE;}
DMA_Stream_TypeDef* dma1_stream4_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream4_BASE;}
DMA_Stream_TypeDef* dma1_stream5_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream5_BASE;}
DMA_Stream_TypeDef* dma1_stream6_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream6_BASE;}
DMA_Stream_TypeDef* dma1_stream7_instance(void){return (DMA_Stream_TypeDef*) DMA1_Stream7_BASE;}
DMA_TypeDef* dma2_instance(void){return (DMA_TypeDef*) DMA2_BASE;}
DMA_Stream_TypeDef* dma2_stream0_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream0_BASE;}
DMA_Stream_TypeDef* dma2_stream1_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream1_BASE;}
DMA_Stream_TypeDef* dma2_stream2_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream2_BASE;}
DMA_Stream_TypeDef* dma2_stream3_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream3_BASE;}
DMA_Stream_TypeDef* dma2_stream4_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream4_BASE;}
DMA_Stream_TypeDef* dma2_stream5_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream5_BASE;}
DMA_Stream_TypeDef* dma2_stream6_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream6_BASE;}
DMA_Stream_TypeDef* dma2_stream7_instance(void){return (DMA_Stream_TypeDef*) DMA2_Stream7_BASE;}
/*** EXTI ***/
EXTI_TypeDef* exti_instance(void){return (EXTI_TypeDef*) EXTI_BASE;}
/*** FLASH ***/
FLASH_TypeDef* flash_instance(void){return (FLASH_TypeDef*) FLASH_R_BASE;}
/*** FMC ***/
#ifdef __STM32F446xx_H
FMC_Bank1_TypeDef* fmc_bank1_instance(void){return (FMC_Bank1_TypeDef*) FMC_Bank1_R_BASE;}
FMC_Bank1E_TypeDef* fmc_bank1e_instance(void){return (FMC_Bank1E_TypeDef*) FMC_Bank1E_R_BASE;}
FMC_Bank3_TypeDef* fmc_bank3_instance(void){return (FMC_Bank3_TypeDef*) FMC_Bank3_R_BASE;}
FMC_Bank5_6_TypeDef* fmc_bank5_6_instance(void){return (FMC_Bank5_6_TypeDef*) FMC_Bank5_6_R_BASE;}
#endif
/*** GPIO ***/
//GPIO_TypeDef* gpioa_instance(void){return (GPIO_TypeDef*) GPIOA_BASE;}
//GPIO_TypeDef* gpiob_instance(void){return (GPIO_TypeDef*) GPIOB_BASE;}
//GPIO_TypeDef* gpioc_instance(void){return (GPIO_TypeDef*) GPIOC_BASE;}
//GPIO_TypeDef* gpiod_instance(void){return (GPIO_TypeDef*) GPIOD_BASE;}
//GPIO_TypeDef* gpioe_instance(void){return (GPIO_TypeDef*) GPIOE_BASE;}
STM32FXXXGPIOX_TypeDef* gpioa_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOA_BASE;}
STM32FXXXGPIOX_TypeDef* gpiob_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOB_BASE;}
STM32FXXXGPIOX_TypeDef* gpioc_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOC_BASE;}
STM32FXXXGPIOX_TypeDef* gpiod_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOD_BASE;}
STM32FXXXGPIOX_TypeDef* gpioe_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOE_BASE;}
#ifdef __STM32F446xx_H
//GPIO_TypeDef* gpiof_instance(void){return (GPIO_TypeDef*) GPIOF_BASE;}
//GPIO_TypeDef* gpiog_instance(void){return (GPIO_TypeDef*) GPIOG_BASE;}
STM32FXXXGPIOX_TypeDef* gpiof_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOF_BASE;}
STM32FXXXGPIOX_TypeDef* gpiog_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOG_BASE;}
#endif
//GPIO_TypeDef* gpioh_instance(void){return (GPIO_TypeDef*) GPIOH_BASE;}
STM32FXXXGPIOX_TypeDef* gpioh_instance(void){return (STM32FXXXGPIOX_TypeDef*) GPIOH_BASE;}
/*** SYSCFG ***/
SYSCFG_TypeDef* syscfg_instance(void){return (SYSCFG_TypeDef*) SYSCFG_BASE;}
/*** I2C ***/
//I2C_TypeDef* i2c1_instance(void){return (I2C_TypeDef*) I2C1_BASE;}
//I2C_TypeDef* i2c2_instance(void){return (I2C_TypeDef*) I2C2_BASE;}
//I2C_TypeDef* i2c3_instance(void){return (I2C_TypeDef*) I2C3_BASE;}
STM32FXXXI2C_TypeDef* i2c1_instance(void){return (STM32FXXXI2C_TypeDef*) I2C1_BASE;}
STM32FXXXI2C_TypeDef* i2c2_instance(void){return (STM32FXXXI2C_TypeDef*) I2C2_BASE;}
STM32FXXXI2C_TypeDef* i2c3_instance(void){return (STM32FXXXI2C_TypeDef*) I2C3_BASE;}
/*** FMPI2C ***/
#ifdef __STM32F446xx_H
FMPI2C_TypeDef* fmpi2c1_instance(void){return (FMPI2C_TypeDef*) FMPI2C1_BASE;}
#endif
/*** IWDG ***/
IWDG_TypeDef* iwdg_instance(void){return (IWDG_TypeDef*) IWDG_BASE;}
/*** PWR ***/
PWR_TypeDef* pwr_instance(void){return (PWR_TypeDef*) PWR_BASE;}
/*** RCC ***/
//RCC_TypeDef* rcc_instance(void){return (RCC_TypeDef*) RCC_BASE;}
STM32FXXXRCC_TypeDef* rcc_instance(void){return (STM32FXXXRCC_TypeDef*) RCC_BASE;}
/*** RTC ***/
RTC_TypeDef* rtc_instance(void){return (RTC_TypeDef*) RTC_BASE;}
/*** SAI ***/
#ifdef __STM32F446xx_H
SAI_TypeDef* sai1_instance(void){return (SAI_TypeDef*) SAI1_BASE;}
SAI_Block_TypeDef* sai1_block_a_instance(void){return (SAI_Block_TypeDef*) SAI1_Block_A_BASE;}
SAI_Block_TypeDef* sai1_block_b_instance(void){return (SAI_Block_TypeDef*) SAI1_Block_B_BASE;}
SAI_TypeDef* sai2_instance(void){return (SAI_TypeDef*) SAI2_BASE;}
SAI_Block_TypeDef* sai2_block_a_instance(void){return (SAI_Block_TypeDef*) SAI2_Block_A_BASE;}
SAI_Block_TypeDef* sai2_block_b_instance(void){return (SAI_Block_TypeDef*) SAI2_Block_B_BASE;}
#endif
/*** SDIO ***/
SDIO_TypeDef* sdio_instance(void){return (SDIO_TypeDef*) SDIO_BASE;}
/*** SPI ***/
SPI_TypeDef* spi1_instance(void){return (SPI_TypeDef*) SPI1_BASE;}
SPI_TypeDef* spi2_instance(void){return (SPI_TypeDef*) SPI2_BASE;}
SPI_TypeDef* spi3_instance(void){return (SPI_TypeDef*) SPI3_BASE;}
SPI_TypeDef* spi4_instance(void){return (SPI_TypeDef*) SPI4_BASE;}
/*** QUADSPI ***/
#ifdef __STM32F446xx_H
QUADSPI_TypeDef* quadspi_instance(void){return (QUADSPI_TypeDef*) QSPI_R_BASE;}
#endif
/*** SPDIFRX ***/
#ifdef __STM32F446xx_H
SPDIFRX_TypeDef* spdifrx_instance(void){return (SPDIFRX_TypeDef*) SPDIFRX_BASE;}
#endif
/*** TIM ***/
//TIM_TypeDef* tim1_instance(void){return (TIM_TypeDef*) TIM1_BASE;}
//TIM_TypeDef* tim2_instance(void){return (TIM_TypeDef*) TIM2_BASE;}
//TIM_TypeDef* tim3_instance(void){return (TIM_TypeDef*) TIM3_BASE;}
//TIM_TypeDef* tim4_instance(void){return (TIM_TypeDef*) TIM4_BASE;}
//TIM_TypeDef* tim5_instance(void){return (TIM_TypeDef*) TIM5_BASE;}
STM32FXXXTIMXX_TypeDef* tim1_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM1_BASE;}
STM32FXXXTIMXX_TypeDef* tim2_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM2_BASE;}
STM32FXXXTIMXX_TypeDef* tim3_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM3_BASE;}
STM32FXXXTIMXX_TypeDef* tim4_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM4_BASE;}
STM32FXXXTIMXX_TypeDef* tim5_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM5_BASE;}
#ifdef __STM32F446xx_H
//TIM_TypeDef* tim6_instance(void){return (TIM_TypeDef*) TIM6_BASE;}
//TIM_TypeDef* tim7_instance(void){return (TIM_TypeDef*) TIM7_BASE;}
STM32FXXXTIMXX_TypeDef* tim6_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM6_BASE;}
STM32FXXXTIMXX_TypeDef* tim7_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM7_BASE;}
#endif
#ifdef __STM32F446xx_H
//TIM_TypeDef* tim8_instance(void){return (TIM_TypeDef*) TIM8_BASE;}
STM32FXXXTIMXX_TypeDef* tim8_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM8_BASE;}
#endif
//TIM_TypeDef* tim9_instance(void){return (TIM_TypeDef*) TIM9_BASE;}
//TIM_TypeDef* tim10_instance(void){return (TIM_TypeDef*) TIM10_BASE;}
//TIM_TypeDef* tim11_instance(void){return (TIM_TypeDef*) TIM11_BASE;}
STM32FXXXTIMXX_TypeDef* tim9_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM9_BASE;}
STM32FXXXTIMXX_TypeDef* tim10_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM10_BASE;}
STM32FXXXTIMXX_TypeDef* tim11_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM11_BASE;}
#ifdef __STM32F446xx_H
//TIM_TypeDef* tim12_instance(void){return (TIM_TypeDef*) TIM12_BASE;}
//TIM_TypeDef* tim13_instance(void){return (TIM_TypeDef*) TIM13_BASE;}
//TIM_TypeDef* tim14_instance(void){return (TIM_TypeDef*) TIM14_BASE;}
STM32FXXXTIMXX_TypeDef* tim12_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM12_BASE;}
STM32FXXXTIMXX_TypeDef* tim13_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM13_BASE;}
STM32FXXXTIMXX_TypeDef* tim14_instance(void){return (STM32FXXXTIMXX_TypeDef*) TIM14_BASE;}
#endif
/*** USART ***/
//USART_TypeDef* usart1_instance(void){return (USART_TypeDef*) USART1_BASE;}
//USART_TypeDef* usart2_instance(void){return (USART_TypeDef*) USART2_BASE;}
TM32FXXXUSARTX_TypeDef* usart1_instance(void){return (TM32FXXXUSARTX_TypeDef*) USART1_BASE;}
TM32FXXXUSARTX_TypeDef* usart2_instance(void){return (TM32FXXXUSARTX_TypeDef*) USART2_BASE;}
#ifdef __STM32F446xx_H
//USART_TypeDef* usart3_instance(void){return (USART_TypeDef*) USART3_BASE;}
//USART_TypeDef* uart4_instance(void){return (USART_TypeDef*) UART4_BASE;}
//USART_TypeDef* uart5_instance(void){return (USART_TypeDef*) UART5_BASE;}
TM32FXXXUSARTX_TypeDef* usart3_instance(void){return (TM32FXXXUSARTX_TypeDef*) USART3_BASE;}
TM32FXXXUSARTX_TypeDef* uart4_instance(void){return (TM32FXXXUSARTX_TypeDef*) UART4_BASE;}
TM32FXXXUSARTX_TypeDef* uart5_instance(void){return (TM32FXXXUSARTX_TypeDef*) UART5_BASE;}
#endif
//USART_TypeDef* usart6_instance(void){return (USART_TypeDef*) USART6_BASE;}
TM32FXXXUSARTX_TypeDef* usart6_instance(void){return (TM32FXXXUSARTX_TypeDef*) USART6_BASE;}
/*** WWDG ***/
WWDG_TypeDef* wwdg_instance(void){return (WWDG_TypeDef*) WWDG_BASE;}
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

