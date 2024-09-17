/******************************************************************************
	STM32 XXX GPIOBF
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 25032024
Comment:
	wrapper
*******************************************************************************/
#ifndef _STM32GPIOBF_H_
#define _STM32GPIOBF_H_

#include <stdint.h>

/* GPIO Registers Structure */
typedef volatile struct {
    /*** GPIO -> MODER ***/
    union {
        struct {
            uint32_t MODER0 : 2;  /* Mode for pin 0 */
            uint32_t MODER1 : 2;  /* Mode for pin 1 */
            uint32_t MODER2 : 2;  /* Mode for pin 2 */
            uint32_t MODER3 : 2;  /* Mode for pin 3 */
            uint32_t MODER4 : 2;  /* Mode for pin 4 */
            uint32_t MODER5 : 2;  /* Mode for pin 5 */
            uint32_t MODER6 : 2;  /* Mode for pin 6 */
            uint32_t MODER7 : 2;  /* Mode for pin 7 */
            uint32_t MODER8 : 2;  /* Mode for pin 8 */
            uint32_t MODER9 : 2;  /* Mode for pin 9 */
            uint32_t MODER10: 2;  /* Mode for pin 10 */
            uint32_t MODER11: 2;  /* Mode for pin 11 */
            uint32_t MODER12: 2;  /* Mode for pin 12 */
            uint32_t MODER13: 2;  /* Mode for pin 13 */
            uint32_t MODER14: 2;  /* Mode for pin 14 */
            uint32_t MODER15: 2;  /* Mode for pin 15 */
        } par;
        uint32_t reg;
    } MODER;  /* 0x00 */

    /*** GPIO -> OTYPER ***/
    union {
        struct {
            uint32_t OT0 : 1;    /* Output type for pin 0 */
            uint32_t OT1 : 1;    /* Output type for pin 1 */
            uint32_t OT2 : 1;    /* Output type for pin 2 */
            uint32_t OT3 : 1;    /* Output type for pin 3 */
            uint32_t OT4 : 1;    /* Output type for pin 4 */
            uint32_t OT5 : 1;    /* Output type for pin 5 */
            uint32_t OT6 : 1;    /* Output type for pin 6 */
            uint32_t OT7 : 1;    /* Output type for pin 7 */
            uint32_t OT8 : 1;    /* Output type for pin 8 */
            uint32_t OT9 : 1;    /* Output type for pin 9 */
            uint32_t OT10: 1;    /* Output type for pin 10 */
            uint32_t OT11: 1;    /* Output type for pin 11 */
            uint32_t OT12: 1;    /* Output type for pin 12 */
            uint32_t OT13: 1;    /* Output type for pin 13 */
            uint32_t OT14: 1;    /* Output type for pin 14 */
            uint32_t OT15: 1;    /* Output type for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        uint32_t reg;
    } OTYPER;  /* 0x04 */

    /*** GPIO -> OSPEEDR ***/
    union {
        struct {
            uint32_t OSPEEDR0 : 2; /* Output speed for pin 0 */
            uint32_t OSPEEDR1 : 2; /* Output speed for pin 1 */
            uint32_t OSPEEDR2 : 2; /* Output speed for pin 2 */
            uint32_t OSPEEDR3 : 2; /* Output speed for pin 3 */
            uint32_t OSPEEDR4 : 2; /* Output speed for pin 4 */
            uint32_t OSPEEDR5 : 2; /* Output speed for pin 5 */
            uint32_t OSPEEDR6 : 2; /* Output speed for pin 6 */
            uint32_t OSPEEDR7 : 2; /* Output speed for pin 7 */
            uint32_t OSPEEDR8 : 2; /* Output speed for pin 8 */
            uint32_t OSPEEDR9 : 2; /* Output speed for pin 9 */
            uint32_t OSPEEDR10: 2; /* Output speed for pin 10 */
            uint32_t OSPEEDR11: 2; /* Output speed for pin 11 */
            uint32_t OSPEEDR12: 2; /* Output speed for pin 12 */
            uint32_t OSPEEDR13: 2; /* Output speed for pin 13 */
            uint32_t OSPEEDR14: 2; /* Output speed for pin 14 */
            uint32_t OSPEEDR15: 2; /* Output speed for pin 15 */
        } par;
        uint32_t reg;
    } OSPEEDR;  /* 0x08 */

    /*** GPIO -> PUPDR ***/
    union {
        struct {
            uint32_t PUPDR0 : 2; /* Pull-up/Pull-down for pin 0 */
            uint32_t PUPDR1 : 2; /* Pull-up/Pull-down for pin 1 */
            uint32_t PUPDR2 : 2; /* Pull-up/Pull-down for pin 2 */
            uint32_t PUPDR3 : 2; /* Pull-up/Pull-down for pin 3 */
            uint32_t PUPDR4 : 2; /* Pull-up/Pull-down for pin 4 */
            uint32_t PUPDR5 : 2; /* Pull-up/Pull-down for pin 5 */
            uint32_t PUPDR6 : 2; /* Pull-up/Pull-down for pin 6 */
            uint32_t PUPDR7 : 2; /* Pull-up/Pull-down for pin 7 */
            uint32_t PUPDR8 : 2; /* Pull-up/Pull-down for pin 8 */
            uint32_t PUPDR9 : 2; /* Pull-up/Pull-down for pin 9 */
            uint32_t PUPDR10: 2; /* Pull-up/Pull-down for pin 10 */
            uint32_t PUPDR11: 2; /* Pull-up/Pull-down for pin 11 */
            uint32_t PUPDR12: 2; /* Pull-up/Pull-down for pin 12 */
            uint32_t PUPDR13: 2; /* Pull-up/Pull-down for pin 13 */
            uint32_t PUPDR14: 2; /* Pull-up/Pull-down for pin 14 */
            uint32_t PUPDR15: 2; /* Pull-up/Pull-down for pin 15 */
        } par;
        uint32_t reg;
    } PUPDR;  /* 0x0C */

    /*** GPIO -> IDR ***/
    union {
        struct {
            uint32_t ID0 : 1;    /* Input data for pin 0 */
            uint32_t ID1 : 1;    /* Input data for pin 1 */
            uint32_t ID2 : 1;    /* Input data for pin 2 */
            uint32_t ID3 : 1;    /* Input data for pin 3 */
            uint32_t ID4 : 1;    /* Input data for pin 4 */
            uint32_t ID5 : 1;    /* Input data for pin 5 */
            uint32_t ID6 : 1;    /* Input data for pin 6 */
            uint32_t ID7 : 1;    /* Input data for pin 7 */
            uint32_t ID8 : 1;    /* Input data for pin 8 */
            uint32_t ID9 : 1;    /* Input data for pin 9 */
            uint32_t ID10: 1;    /* Input data for pin 10 */
            uint32_t ID11: 1;    /* Input data for pin 11 */
            uint32_t ID12: 1;    /* Input data for pin 12 */
            uint32_t ID13: 1;    /* Input data for pin 13 */
            uint32_t ID14: 1;    /* Input data for pin 14 */
            uint32_t ID15: 1;    /* Input data for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        uint32_t reg;
    } IDR;  /* 0x10 */

    /*** GPIO -> ODR ***/
    union {
        struct {
            uint32_t ODR0 : 1;    /* Output data for pin 0 */
            uint32_t ODR1 : 1;    /* Output data for pin 1 */
            uint32_t ODR2 : 1;    /* Output data for pin 2 */
            uint32_t ODR3 : 1;    /* Output data for pin 3 */
            uint32_t ODR4 : 1;    /* Output data for pin 4 */
            uint32_t ODR5 : 1;    /* Output data for pin 5 */
            uint32_t ODR6 : 1;    /* Output data for pin 6 */
            uint32_t ODR7 : 1;    /* Output data for pin 7 */
            uint32_t ODR8 : 1;    /* Output data for pin 8 */
            uint32_t ODR9 : 1;    /* Output data for pin 9 */
            uint32_t ODR10: 1;    /* Output data for pin 10 */
            uint32_t ODR11: 1;    /* Output data for pin 11 */
            uint32_t ODR12: 1;    /* Output data for pin 12 */
            uint32_t ODR13: 1;    /* Output data for pin 13 */
            uint32_t ODR14: 1;    /* Output data for pin 14 */
            uint32_t ODR15: 1;    /* Output data for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        uint32_t reg;
    } ODR;  /* 0x14 */

    /*** GPIO -> BSRR ***/
    union {
        struct {
            uint32_t BS0 : 1;    /* Bit set for pin 0 */
            uint32_t BS1 : 1;    /* Bit set for pin 1 */
            uint32_t BS2 : 1;    /* Bit set for pin 2 */
            uint32_t BS3 : 1;    /* Bit set for pin 3 */
            uint32_t BS4 : 1;    /* Bit set for pin 4 */
            uint32_t BS5 : 1;    /* Bit set for pin 5 */
            uint32_t BS6 : 1;    /* Bit set for pin 6 */
            uint32_t BS7 : 1;    /* Bit set for pin 7 */
            uint32_t BS8 : 1;    /* Bit set for pin 8 */
            uint32_t BS9 : 1;    /* Bit set for pin 9 */
            uint32_t BS10: 1;    /* Bit set for pin 10 */
            uint32_t BS11: 1;    /* Bit set for pin 11 */
            uint32_t BS12: 1;    /* Bit set for pin 12 */
            uint32_t BS13: 1;    /* Bit set for pin 13 */
            uint32_t BS14: 1;    /* Bit set for pin 14 */
            uint32_t BS15: 1;    /* Bit set for pin 15 */
            uint32_t BR0 : 1;    /* Bit reset for pin 0 */
            uint32_t BR1 : 1;    /* Bit reset for pin 1 */
            uint32_t BR2 : 1;    /* Bit reset for pin 2 */
            uint32_t BR3 : 1;    /* Bit reset for pin 3 */
            uint32_t BR4 : 1;    /* Bit reset for pin 4 */
            uint32_t BR5 : 1;    /* Bit reset for pin 5 */
            uint32_t BR6 : 1;    /* Bit reset for pin 6 */
            uint32_t BR7 : 1;    /* Bit reset for pin 7 */
            uint32_t BR8 : 1;    /* Bit reset for pin 8 */
            uint32_t BR9 : 1;    /* Bit reset for pin 9 */
            uint32_t BR10: 1;    /* Bit reset for pin 10 */
            uint32_t BR11: 1;    /* Bit reset for pin 11 */
            uint32_t BR12: 1;    /* Bit reset for pin 12 */
            uint32_t BR13: 1;    /* Bit reset for pin 13 */
            uint32_t BR14: 1;    /* Bit reset for pin 14 */
            uint32_t BR15: 1;    /* Bit reset for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
            uint16_t BS;   /* Bit set register (low 16 pars) */
            uint16_t BR;   /* Bit reset register (high 16 pars) */
        } word;
        uint32_t reg;
    } BSRR;  /* 0x18 */

    /*** GPIO -> LCKR ***/
    union {
        struct {
            uint32_t LCK0 : 1;    /* Lock for pin 0 */
            uint32_t LCK1 : 1;    /* Lock for pin 1 */
            uint32_t LCK2 : 1;    /* Lock for pin 2 */
            uint32_t LCK3 : 1;    /* Lock for pin 3 */
            uint32_t LCK4 : 1;    /* Lock for pin 4 */
            uint32_t LCK5 : 1;    /* Lock for pin 5 */
            uint32_t LCK6 : 1;    /* Lock for pin 6 */
            uint32_t LCK7 : 1;    /* Lock for pin 7 */
            uint32_t LCK8 : 1;    /* Lock for pin 8 */
            uint32_t LCK9 : 1;    /* Lock for pin 9 */
            uint32_t LCK10: 1;    /* Lock for pin 10 */
            uint32_t LCK11: 1;    /* Lock for pin 11 */
            uint32_t LCK12: 1;    /* Lock for pin 12 */
            uint32_t LCK13: 1;    /* Lock for pin 13 */
            uint32_t LCK14: 1;    /* Lock for pin 14 */
            uint32_t LCK15: 1;    /* Lock for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
            uint16_t LCKR; /* Lock register (low 16 pars) */
            uint16_t reserved; /* Reserved for padding */
        } word;
        uint32_t reg;
    } LCKR;  /* 0x1C */

    /*** GPIO -> AFR ***/
    union {
        struct {
            uint32_t AFR0 : 4;    /* Alternate function for pin 0 */
            uint32_t AFR1 : 4;    /* Alternate function for pin 1 */
            uint32_t AFR2 : 4;    /* Alternate function for pin 2 */
            uint32_t AFR3 : 4;    /* Alternate function for pin 3 */
            uint32_t AFR4 : 4;    /* Alternate function for pin 4 */
            uint32_t AFR5 : 4;    /* Alternate function for pin 5 */
            uint32_t AFR6 : 4;    /* Alternate function for pin 6 */
            uint32_t AFR7 : 4;    /* Alternate function for pin 7 */
            uint32_t AFR8 : 4;    /* Alternate function for pin 8 */
            uint32_t AFR9 : 4;    /* Alternate function for pin 9 */
            uint32_t AFR10: 4;    /* Alternate function for pin 10 */
            uint32_t AFR11: 4;    /* Alternate function for pin 11 */
            uint32_t AFR12: 4;    /* Alternate function for pin 12 */
            uint32_t AFR13: 4;    /* Alternate function for pin 13 */
            uint32_t AFR14: 4;    /* Alternate function for pin 14 */
            uint32_t AFR15: 4;    /* Alternate function for pin 15 */
        } par;
        struct {
            uint32_t AFRL; /* Alternate function low register (0x20) */
            uint32_t AFRH; /* Alternate function high register (0x24) */
        } word;
        uint32_t reg[2]; /* AFRL and AFRH */
    } AFR;  /* 0x20 and 0x24 */

} STM32FXXXGPIOX_TypeDef;

#endif /* _STM32GPIOBF_H_ */

/*** EOF ***/

