/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     08102024
Comment:
	
*******************************************************************************/
#include "timer_irq.h"

/*** Library ***/
#include "stm32fxxxinstance.h"

/*** Default Callback Implementations ***/
void tim1_b_callback(void) {}
void tim1_u_callback(void) {}
void tim1_t_callback(void) {}
void tim1_cc1_callback(void) {}
void tim1_cc2_callback(void) {}
void tim1_cc3_callback(void) {}
void tim1_cc4_callback(void) {}

void tim2_b_callback(void) {}
void tim2_u_callback(void) {}
void tim2_t_callback(void) {}
void tim2_cc1_callback(void) {}
void tim2_cc2_callback(void) {}
void tim2_cc3_callback(void) {}
void tim2_cc4_callback(void) {}

void tim3_b_callback(void) {}
void tim3_u_callback(void) {}
void tim3_t_callback(void) {}
void tim3_cc1_callback(void) {}
void tim3_cc2_callback(void) {}
void tim3_cc3_callback(void) {}
void tim3_cc4_callback(void) {}

void tim4_b_callback(void) {}
void tim4_u_callback(void) {}
void tim4_t_callback(void) {}
void tim4_cc1_callback(void) {}
void tim4_cc2_callback(void) {}
void tim4_cc3_callback(void) {}
void tim4_cc4_callback(void) {}

void tim5_b_callback(void) {}
void tim5_u_callback(void) {}
void tim5_t_callback(void) {}
void tim5_cc1_callback(void) {}
void tim5_cc2_callback(void) {}
void tim5_cc3_callback(void) {}
void tim5_cc4_callback(void) {}

void tim6_u_callback(void) {}
void tim7_u_callback(void) {}

void tim8_b_callback(void) {}
void tim8_u_callback(void) {}
void tim8_t_callback(void) {}
void tim8_cc1_callback(void) {}
void tim8_cc2_callback(void) {}
void tim8_cc3_callback(void) {}
void tim8_cc4_callback(void) {}

void tim9_u_callback(void) {}
void tim9_t_callback(void) {}

void tim10_u_callback(void) {}

void tim11_u_callback(void) {}
void tim11_t_callback(void) {}

void tim12_u_callback(void) {}
void tim12_t_callback(void) {}
void tim12_cc1_callback(void) {}
void tim12_cc2_callback(void) {}

void tim13_u_callback(void) {}
void tim13_t_callback(void) {}

void tim14_u_callback(void) {}
void tim14_t_callback(void) {}

/*** Timer IRQ Handlers ***/
void TIM1_BRK_TIM9_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_BIF) {
        tim1_b_callback();
        TIM1->SR &= ~TIM_SR_BIF;
    }
    if (TIM9->SR & TIM_SR_UIF) {
        tim9_u_callback();
        TIM9->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        tim1_u_callback();
        TIM1->SR &= ~TIM_SR_UIF;
    }
    if (TIM10->SR & TIM_SR_UIF) {
        tim10_u_callback();
        TIM10->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_TIF) {
        tim1_t_callback();
        TIM1->SR &= ~TIM_SR_TIF;
    }
    if (TIM11->SR & TIM_SR_UIF) {
        tim11_u_callback();
        TIM11->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_CC1IF) {
        tim1_cc1_callback();
        TIM1->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM1->SR & TIM_SR_CC2IF) {
        tim1_cc2_callback();
        TIM1->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM1->SR & TIM_SR_CC3IF) {
        tim1_cc3_callback();
        TIM1->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM1->SR & TIM_SR_CC4IF) {
        tim1_cc4_callback();
        TIM1->SR &= ~TIM_SR_CC4IF;
    }
}

// Repeat similar structure for other timers
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        tim2_u_callback();
        TIM2->SR &= ~TIM_SR_UIF;
    }
    if (TIM2->SR & TIM_SR_TIF) {
        tim2_t_callback();
        TIM2->SR &= ~TIM_SR_TIF;
    }
    if (TIM2->SR & TIM_SR_CC1IF) {
        tim2_cc1_callback();
        TIM2->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM2->SR & TIM_SR_CC2IF) {
        tim2_cc2_callback();
        TIM2->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM2->SR & TIM_SR_CC3IF) {
        tim2_cc3_callback();
        TIM2->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM2->SR & TIM_SR_CC4IF) {
        tim2_cc4_callback();
        TIM2->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        tim3_u_callback();
        TIM3->SR &= ~TIM_SR_UIF;
    }
    if (TIM3->SR & TIM_SR_TIF) {
        tim3_t_callback();
        TIM3->SR &= ~TIM_SR_TIF;
    }
    if (TIM3->SR & TIM_SR_CC1IF) {
        tim3_cc1_callback();
        TIM3->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM3->SR & TIM_SR_CC2IF) {
        tim3_cc2_callback();
        TIM3->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM3->SR & TIM_SR_CC3IF) {
        tim3_cc3_callback();
        TIM3->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM3->SR & TIM_SR_CC4IF) {
        tim3_cc4_callback();
        TIM3->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM4_IRQHandler(void) {
    if (TIM4->SR & TIM_SR_UIF) {
        tim4_u_callback();
        TIM4->SR &= ~TIM_SR_UIF;
    }
    if (TIM4->SR & TIM_SR_TIF) {
        tim4_t_callback();
        TIM4->SR &= ~TIM_SR_TIF;
    }
    if (TIM4->SR & TIM_SR_CC1IF) {
        tim4_cc1_callback();
        TIM4->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM4->SR & TIM_SR_CC2IF) {
        tim4_cc2_callback();
        TIM4->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM4->SR & TIM_SR_CC3IF) {
        tim4_cc3_callback();
        TIM4->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM4->SR & TIM_SR_CC4IF) {
        tim4_cc4_callback();
        TIM4->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM5_IRQHandler(void) {
    if (TIM5->SR & TIM_SR_UIF) {
        tim5_u_callback();
        TIM5->SR &= ~TIM_SR_UIF;
    }
    if (TIM5->SR & TIM_SR_TIF) {
        tim5_t_callback();
        TIM5->SR &= ~TIM_SR_TIF;
    }
    if (TIM5->SR & TIM_SR_CC1IF) {
        tim5_cc1_callback();
        TIM5->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM5->SR & TIM_SR_CC2IF) {
        tim5_cc2_callback();
        TIM5->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM5->SR & TIM_SR_CC3IF) {
        tim5_cc3_callback();
        TIM5->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM5->SR & TIM_SR_CC4IF) {
        tim5_cc4_callback();
        TIM5->SR &= ~TIM_SR_CC4IF;
    }
}

#ifdef STM32F446xx
// TIM6 and TIM7 only have update interrupt
void TIM6_DAC_IRQHandler(void) {
    if (TIM6->SR & TIM_SR_UIF) {
        tim6_u_callback();
        TIM6->SR &= ~TIM_SR_UIF;
    }
}

void TIM7_IRQHandler(void) {
    if (TIM7->SR & TIM_SR_UIF) {
        tim7_u_callback();
        TIM7->SR &= ~TIM_SR_UIF;
    }
}

// TIM8 has similar structure
void TIM8_BRK_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_BIF) {
        tim8_b_callback();
        TIM8->SR &= ~TIM_SR_BIF;
    }
}

void TIM8_BRK_TIM12_IRQHandler(void) {}

void TIM8_UP_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_UIF) {
        tim8_u_callback();
        TIM8->SR &= ~TIM_SR_UIF;
    }
}

void TIM8_UP_TIM13_IRQHandler(void) {}

void TIM8_TRG_COM_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_TIF) {
        tim8_t_callback();
        TIM8->SR &= ~TIM_SR_TIF;
    }
}

void TIM8_TRG_COM_TIM14_IRQHandler(void);

void TIM8_CC_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_CC1IF) {
        tim8_cc1_callback();
        TIM8->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM8->SR & TIM_SR_CC2IF) {
        tim8_cc2_callback();
        TIM8->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM8->SR & TIM_SR_CC3IF) {
        tim8_cc3_callback();
        TIM8->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM8->SR & TIM_SR_CC4IF) {
        tim8_cc4_callback();
        TIM8->SR &= ~TIM_SR_CC4IF;
    }
}
#endif

void TIM9_IRQHandler(void) {
    if (TIM9->SR & TIM_SR_UIF) {
        tim9_u_callback();
        TIM9->SR &= ~TIM_SR_UIF;
    }
    if (TIM9->SR & TIM_SR_TIF) {
        tim9_t_callback();
        TIM9->SR &= ~TIM_SR_TIF;
    }
}

void TIM10_IRQHandler(void) {
    if (TIM10->SR & TIM_SR_UIF) {
        tim10_u_callback();
        TIM10->SR &= ~TIM_SR_UIF;
    }
}

void TIM11_IRQHandler(void) {
    if (TIM11->SR & TIM_SR_UIF) {
        tim11_u_callback();
        TIM11->SR &= ~TIM_SR_UIF;
    }
    if (TIM11->SR & TIM_SR_TIF) {
        tim11_t_callback();
        TIM11->SR &= ~TIM_SR_TIF;
    }
}

#ifdef STM32F446xx
void TIM12_IRQHandler(void) {
    if (TIM12->SR & TIM_SR_UIF) {
        tim12_u_callback();
        TIM12->SR &= ~TIM_SR_UIF;
    }
    if (TIM12->SR & TIM_SR_TIF) {
        tim12_t_callback();
        TIM12->SR &= ~TIM_SR_TIF;
    }
    if (TIM12->SR & TIM_SR_CC1IF) {
        tim12_cc1_callback();
        TIM12->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM12->SR & TIM_SR_CC2IF) {
        tim12_cc2_callback();
        TIM12->SR &= ~TIM_SR_CC2IF;
    }
}

void TIM13_IRQHandler(void) {
    if (TIM13->SR & TIM_SR_UIF) {
        tim13_u_callback();
        TIM13->SR &= ~TIM_SR_UIF;
    }
}

void TIM14_IRQHandler(void) {
    if (TIM14->SR & TIM_SR_UIF) {
        tim14_u_callback();
        TIM14->SR &= ~TIM_SR_UIF;
    }
}
#endif

/*** EOF ***/

