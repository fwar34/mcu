;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _CAN_TPR_bit
	.globl _CAN_TPR
	.globl _ADC_DRL
	.globl _ADC_DRH
	.globl _I2C_SR3_bit
	.globl _I2C_SR3
	.globl _I2C_SR1_bit
	.globl _I2C_SR1
	.globl _SPI_TXCRCR
	.globl _SPI_RXCRCR
	.globl _CLK_CMSR
	.globl _PI_IDR_bit
	.globl _PI_IDR
	.globl _PH_IDR_bit
	.globl _PH_IDR
	.globl _PG_IDR_bit
	.globl _PG_IDR
	.globl _PF_IDR_bit
	.globl _PF_IDR
	.globl _PE_IDR_bit
	.globl _PE_IDR
	.globl _PD_IDR_bit
	.globl _PD_IDR
	.globl _PC_IDR_bit
	.globl _PC_IDR
	.globl _PB_IDR_bit
	.globl _PB_IDR
	.globl _PA_IDR_bit
	.globl _PA_IDR
	.globl _main
	.globl _gpio_init
	.globl _DM_ENFCTR
	.globl _DM_CSR2
	.globl _DM_CSR1
	.globl _DM_CR2
	.globl _DM_CR1
	.globl _DM_BK2RL
	.globl _DM_BK2RH
	.globl _DM_BK2RE
	.globl _DM_BK1RL
	.globl _DM_BK1RH
	.globl _DM_BK1RE
	.globl _SWIM_CSR
	.globl _CPU_CFG_GCR_bit
	.globl _CPU_CFG_GCR
	.globl _CPU_CCR_bit
	.globl _CPU_CCR
	.globl _CPU_SPL
	.globl _CPU_SPH
	.globl _CPU_YL
	.globl _CPU_YH
	.globl _CPU_XL
	.globl _CPU_XH
	.globl _CPU_PCL
	.globl _CPU_PCH
	.globl _CPU_PCE
	.globl _CPU_A
	.globl _CAN_PF
	.globl _CAN_PE
	.globl _CAN_PD
	.globl _CAN_PC
	.globl _CAN_PB
	.globl _CAN_PA
	.globl _CAN_P9
	.globl _CAN_P8
	.globl _CAN_P7
	.globl _CAN_P6
	.globl _CAN_P5
	.globl _CAN_P4
	.globl _CAN_P3
	.globl _CAN_P2
	.globl _CAN_P1
	.globl _CAN_P0
	.globl _CAN_EIER_bit
	.globl _CAN_EIER
	.globl _CAN_ESR_bit
	.globl _CAN_ESR
	.globl _CAN_FPSR
	.globl _CAN_DGR_bit
	.globl _CAN_DGR
	.globl _CAN_IER_bit
	.globl _CAN_IER
	.globl _CAN_RFR_bit
	.globl _CAN_RFR
	.globl _CAN_TSR_bit
	.globl _CAN_TSR
	.globl _CAN_MSR_bit
	.globl _CAN_MSR
	.globl _CAN_MCR_bit
	.globl _CAN_MCR
	.globl _ADC_TDRL
	.globl _ADC_TDRH
	.globl _ADC_CR3_bit
	.globl _ADC_CR3
	.globl _ADC_CR2_bit
	.globl _ADC_CR2
	.globl _ADC_CR1_bit
	.globl _ADC_CR1
	.globl _ADC_CSR_bit
	.globl _ADC_CSR
	.globl _TIM4_ARR
	.globl _TIM4_PSCR_bit
	.globl _TIM4_PSCR
	.globl _TIM4_CNTR
	.globl _TIM4_EGR_bit
	.globl _TIM4_EGR
	.globl _TIM4_SR_bit
	.globl _TIM4_SR
	.globl _TIM4_IER_bit
	.globl _TIM4_IER
	.globl _TIM4_CR1_bit
	.globl _TIM4_CR1
	.globl _TIM3_CCR2L
	.globl _TIM3_CCR2H
	.globl _TIM3_CCR1L
	.globl _TIM3_CCR1H
	.globl _TIM3_ARRL
	.globl _TIM3_ARRH
	.globl _TIM3_PSCR_bit
	.globl _TIM3_PSCR
	.globl _TIM3_CNTRL
	.globl _TIM3_CNTRH
	.globl _TIM3_CCER1_bit
	.globl _TIM3_CCER1
	.globl _TIM3_CCMR2_bit
	.globl _TIM3_CCMR2
	.globl _TIM3_CCMR1_bit
	.globl _TIM3_CCMR1
	.globl _TIM3_EGR_bit
	.globl _TIM3_EGR
	.globl _TIM3_SR2_bit
	.globl _TIM3_SR2
	.globl _TIM3_SR1_bit
	.globl _TIM3_SR1
	.globl _TIM3_IER_bit
	.globl _TIM3_IER
	.globl _TIM3_CR1_bit
	.globl _TIM3_CR1
	.globl _TIM2_CCR3L
	.globl _TIM2_CCR3H
	.globl _TIM2_CCR2L
	.globl _TIM2_CCR2H
	.globl _TIM2_CCR1L
	.globl _TIM2_CCR1H
	.globl _TIM2_ARRL
	.globl _TIM2_ARRH
	.globl _TIM2_PSCR_bit
	.globl _TIM2_PSCR
	.globl _TIM2_CNTRL
	.globl _TIM2_CNTRH
	.globl _TIM2_CCER2_bit
	.globl _TIM2_CCER2
	.globl _TIM2_CCER1_bit
	.globl _TIM2_CCER1
	.globl _TIM2_CCMR3_bit
	.globl _TIM2_CCMR3
	.globl _TIM2_CCMR2_bit
	.globl _TIM2_CCMR2
	.globl _TIM2_CCMR1_bit
	.globl _TIM2_CCMR1
	.globl _TIM2_EGR_bit
	.globl _TIM2_EGR
	.globl _TIM2_SR2_bit
	.globl _TIM2_SR2
	.globl _TIM2_SR1_bit
	.globl _TIM2_SR1
	.globl _TIM2_IER_bit
	.globl _TIM2_IER
	.globl _TIM2_CR1_bit
	.globl _TIM2_CR1
	.globl _TIM1_OISR_bit
	.globl _TIM1_OISR
	.globl _TIM1_DTR
	.globl _TIM1_BKR_bit
	.globl _TIM1_BKR
	.globl _TIM1_CCR4L
	.globl _TIM1_CCR4H
	.globl _TIM1_CCR3L
	.globl _TIM1_CCR3H
	.globl _TIM1_CCR2L
	.globl _TIM1_CCR2H
	.globl _TIM1_CCR1L
	.globl _TIM1_CCR1H
	.globl _TIM1_RCR
	.globl _TIM1_ARRL
	.globl _TIM1_ARRH
	.globl _TIM1_PSCRL
	.globl _TIM1_PSCRH
	.globl _TIM1_CNTRL
	.globl _TIM1_CNTRH
	.globl _TIM1_CCER2_bit
	.globl _TIM1_CCER2
	.globl _TIM1_CCER1_bit
	.globl _TIM1_CCER1
	.globl _TIM1_CCMR4_bit
	.globl _TIM1_CCMR4
	.globl _TIM1_CCMR3_bit
	.globl _TIM1_CCMR3
	.globl _TIM1_CCMR2_bit
	.globl _TIM1_CCMR2
	.globl _TIM1_CCMR1_bit
	.globl _TIM1_CCMR1
	.globl _TIM1_EGR_bit
	.globl _TIM1_EGR
	.globl _TIM1_SR2_bit
	.globl _TIM1_SR2
	.globl _TIM1_SR1_bit
	.globl _TIM1_SR1
	.globl _TIM1_IER_bit
	.globl _TIM1_IER
	.globl _TIM1_ETR_bit
	.globl _TIM1_ETR
	.globl _TIM1_SMCR_bit
	.globl _TIM1_SMCR
	.globl _TIM1_CR2_bit
	.globl _TIM1_CR2
	.globl _TIM1_CR1_bit
	.globl _TIM1_CR1
	.globl _UART3_CR6_bit
	.globl _UART3_CR6
	.globl _UART3_CR4_bit
	.globl _UART3_CR4
	.globl _UART3_CR3_bit
	.globl _UART3_CR3
	.globl _UART3_CR2_bit
	.globl _UART3_CR2
	.globl _UART3_CR1_bit
	.globl _UART3_CR1
	.globl _UART3_BRR2
	.globl _UART3_BRR1
	.globl _UART3_DR
	.globl _UART3_SR_bit
	.globl _UART3_SR
	.globl _UART2_PSCR
	.globl _UART2_GTR
	.globl _UART2_CR6_bit
	.globl _UART2_CR6
	.globl _UART2_CR4_bit
	.globl _UART2_CR4
	.globl _UART2_CR3_bit
	.globl _UART2_CR3
	.globl _UART2_CR2_bit
	.globl _UART2_CR2
	.globl _UART2_CR1_bit
	.globl _UART2_CR1
	.globl _UART2_BRR2
	.globl _UART2_BRR1
	.globl _UART2_DR
	.globl _UART2_SR_bit
	.globl _UART2_SR
	.globl _UART1_PSCR
	.globl _UART1_GTR
	.globl _UART1_CR5_bit
	.globl _UART1_CR5
	.globl _UART1_CR4_bit
	.globl _UART1_CR4
	.globl _UART1_CR3_bit
	.globl _UART1_CR3
	.globl _UART1_CR2_bit
	.globl _UART1_CR2
	.globl _UART1_CR1_bit
	.globl _UART1_CR1
	.globl _UART1_BRR2
	.globl _UART1_BRR1
	.globl _UART1_DR
	.globl _UART1_SR_bit
	.globl _UART1_SR
	.globl _I2C_PECR
	.globl _I2C_TRISER_bit
	.globl _I2C_TRISER
	.globl _I2C_CCRH_bit
	.globl _I2C_CCRH
	.globl _I2C_CCRL
	.globl _I2C_ITR_bit
	.globl _I2C_ITR
	.globl _I2C_SR2_bit
	.globl _I2C_SR2
	.globl _I2C_DR
	.globl _I2C_OARH_bit
	.globl _I2C_OARH
	.globl _I2C_OARL_bit
	.globl _I2C_OARL
	.globl _I2C_FREQR_bit
	.globl _I2C_FREQR
	.globl _I2C_CR2_bit
	.globl _I2C_CR2
	.globl _I2C_CR1_bit
	.globl _I2C_CR1
	.globl _SPI_CRCPR
	.globl _SPI_DR
	.globl _SPI_SR_bit
	.globl _SPI_SR
	.globl _SPI_ICR_bit
	.globl _SPI_ICR
	.globl _SPI_CR2_bit
	.globl _SPI_CR2
	.globl _SPI_CR1_bit
	.globl _SPI_CR1
	.globl _BEEP_CSR_bit
	.globl _BEEP_CSR
	.globl _AWU_TBR_bit
	.globl _AWU_TBR
	.globl _AWU_APR
	.globl _AWU_CSR1_bit
	.globl _AWU_CSR1
	.globl _IWDG_RLR
	.globl _IWDG_PR_bit
	.globl _IWDG_PR
	.globl _IWDG_KR
	.globl _WWDG_WR_bit
	.globl _WWDG_WR
	.globl _WWDG_CR_bit
	.globl _WWDG_CR
	.globl _CLK_SWIMCCR_bit
	.globl _CLK_SWIMCCR
	.globl _CLK_HSITRIMR_bit
	.globl _CLK_HSITRIMR
	.globl _CLK_CANCCR_bit
	.globl _CLK_CANCCR
	.globl _CLK_PCKENR2
	.globl _CLK_CCOR_bit
	.globl _CLK_CCOR
	.globl _CLK_CSSR_bit
	.globl _CLK_CSSR
	.globl _CLK_PCKENR1
	.globl _CLK_CKDIVR_bit
	.globl _CLK_CKDIVR
	.globl _CLK_SWCR_bit
	.globl _CLK_SWCR
	.globl _CLK_SWR
	.globl _CLK_ECKR_bit
	.globl _CLK_ECKR
	.globl _CLK_ICKR_bit
	.globl _CLK_ICKR
	.globl _RST_SR_bit
	.globl _RST_SR
	.globl _ITC_SPR8_bit
	.globl _ITC_SPR8
	.globl _ITC_SPR7_bit
	.globl _ITC_SPR7
	.globl _ITC_SPR6_bit
	.globl _ITC_SPR6
	.globl _ITC_SPR5_bit
	.globl _ITC_SPR5
	.globl _ITC_SPR4_bit
	.globl _ITC_SPR4
	.globl _ITC_SPR3_bit
	.globl _ITC_SPR3
	.globl _ITC_SPR2_bit
	.globl _ITC_SPR2
	.globl _ITC_SPR1_bit
	.globl _ITC_SPR1
	.globl _EXTI_CR2_bit
	.globl _EXTI_CR2
	.globl _EXTI_CR1_bit
	.globl _EXTI_CR1
	.globl _FLASH_DUKR
	.globl _FLASH_PUKR
	.globl _FLASH_IAPSR_bit
	.globl _FLASH_IAPSR
	.globl _FLASH_NFPR
	.globl _FLASH_FPR
	.globl _FLASH_NCR2_bit
	.globl _FLASH_NCR2
	.globl _FLASH_CR2_bit
	.globl _FLASH_CR2
	.globl _FLASH_CR1_bit
	.globl _FLASH_CR1
	.globl _PI_CR2_bit
	.globl _PI_CR2
	.globl _PI_CR1_bit
	.globl _PI_CR1
	.globl _PI_DDR_bit
	.globl _PI_DDR
	.globl _PI_ODR_bit
	.globl _PI_ODR
	.globl _PH_CR2_bit
	.globl _PH_CR2
	.globl _PH_CR1_bit
	.globl _PH_CR1
	.globl _PH_DDR_bit
	.globl _PH_DDR
	.globl _PH_ODR_bit
	.globl _PH_ODR
	.globl _PG_CR2_bit
	.globl _PG_CR2
	.globl _PG_CR1_bit
	.globl _PG_CR1
	.globl _PG_DDR_bit
	.globl _PG_DDR
	.globl _PG_ODR_bit
	.globl _PG_ODR
	.globl _PF_CR2_bit
	.globl _PF_CR2
	.globl _PF_CR1_bit
	.globl _PF_CR1
	.globl _PF_DDR_bit
	.globl _PF_DDR
	.globl _PF_ODR_bit
	.globl _PF_ODR
	.globl _PE_CR2_bit
	.globl _PE_CR2
	.globl _PE_CR1_bit
	.globl _PE_CR1
	.globl _PE_DDR_bit
	.globl _PE_DDR
	.globl _PE_ODR_bit
	.globl _PE_ODR
	.globl _PD_CR2_bit
	.globl _PD_CR2
	.globl _PD_CR1_bit
	.globl _PD_CR1
	.globl _PD_DDR_bit
	.globl _PD_DDR
	.globl _PD_ODR_bit
	.globl _PD_ODR
	.globl _PC_CR2_bit
	.globl _PC_CR2
	.globl _PC_CR1_bit
	.globl _PC_CR1
	.globl _PC_DDR_bit
	.globl _PC_DDR
	.globl _PC_ODR_bit
	.globl _PC_ODR
	.globl _PB_CR2_bit
	.globl _PB_CR2
	.globl _PB_CR1_bit
	.globl _PB_CR1
	.globl _PB_DDR_bit
	.globl _PB_DDR
	.globl _PB_ODR_bit
	.globl _PB_ODR
	.globl _PA_CR2_bit
	.globl _PA_CR2
	.globl _PA_CR1_bit
	.globl _PA_CR1
	.globl _PA_DDR_bit
	.globl _PA_DDR
	.globl _PA_ODR_bit
	.globl _PA_ODR
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_PA_ODR	=	0x5000
_PA_ODR_bit	=	0x5000
_PA_DDR	=	0x5002
_PA_DDR_bit	=	0x5002
_PA_CR1	=	0x5003
_PA_CR1_bit	=	0x5003
_PA_CR2	=	0x5004
_PA_CR2_bit	=	0x5004
_PB_ODR	=	0x5005
_PB_ODR_bit	=	0x5005
_PB_DDR	=	0x5007
_PB_DDR_bit	=	0x5007
_PB_CR1	=	0x5008
_PB_CR1_bit	=	0x5008
_PB_CR2	=	0x5009
_PB_CR2_bit	=	0x5009
_PC_ODR	=	0x500a
_PC_ODR_bit	=	0x500a
_PC_DDR	=	0x500c
_PC_DDR_bit	=	0x500c
_PC_CR1	=	0x500d
_PC_CR1_bit	=	0x500d
_PC_CR2	=	0x500e
_PC_CR2_bit	=	0x500e
_PD_ODR	=	0x500f
_PD_ODR_bit	=	0x500f
_PD_DDR	=	0x5011
_PD_DDR_bit	=	0x5011
_PD_CR1	=	0x5012
_PD_CR1_bit	=	0x5012
_PD_CR2	=	0x5013
_PD_CR2_bit	=	0x5013
_PE_ODR	=	0x5014
_PE_ODR_bit	=	0x5014
_PE_DDR	=	0x5016
_PE_DDR_bit	=	0x5016
_PE_CR1	=	0x5017
_PE_CR1_bit	=	0x5017
_PE_CR2	=	0x5018
_PE_CR2_bit	=	0x5018
_PF_ODR	=	0x5019
_PF_ODR_bit	=	0x5019
_PF_DDR	=	0x501b
_PF_DDR_bit	=	0x501b
_PF_CR1	=	0x501c
_PF_CR1_bit	=	0x501c
_PF_CR2	=	0x501d
_PF_CR2_bit	=	0x501d
_PG_ODR	=	0x501e
_PG_ODR_bit	=	0x501e
_PG_DDR	=	0x5020
_PG_DDR_bit	=	0x5020
_PG_CR1	=	0x5021
_PG_CR1_bit	=	0x5021
_PG_CR2	=	0x5022
_PG_CR2_bit	=	0x5022
_PH_ODR	=	0x5023
_PH_ODR_bit	=	0x5023
_PH_DDR	=	0x5025
_PH_DDR_bit	=	0x5025
_PH_CR1	=	0x5026
_PH_CR1_bit	=	0x5026
_PH_CR2	=	0x5027
_PH_CR2_bit	=	0x5027
_PI_ODR	=	0x5028
_PI_ODR_bit	=	0x5028
_PI_DDR	=	0x502a
_PI_DDR_bit	=	0x502a
_PI_CR1	=	0x502b
_PI_CR1_bit	=	0x502b
_PI_CR2	=	0x502c
_PI_CR2_bit	=	0x502c
_FLASH_CR1	=	0x505a
_FLASH_CR1_bit	=	0x505a
_FLASH_CR2	=	0x505b
_FLASH_CR2_bit	=	0x505b
_FLASH_NCR2	=	0x505c
_FLASH_NCR2_bit	=	0x505c
_FLASH_FPR	=	0x505d
_FLASH_NFPR	=	0x505e
_FLASH_IAPSR	=	0x505f
_FLASH_IAPSR_bit	=	0x505f
_FLASH_PUKR	=	0x5062
_FLASH_DUKR	=	0x5064
_EXTI_CR1	=	0x50a0
_EXTI_CR1_bit	=	0x50a0
_EXTI_CR2	=	0x50a1
_EXTI_CR2_bit	=	0x50a1
_ITC_SPR1	=	0x7f70
_ITC_SPR1_bit	=	0x7f70
_ITC_SPR2	=	0x7f71
_ITC_SPR2_bit	=	0x7f71
_ITC_SPR3	=	0x7f72
_ITC_SPR3_bit	=	0x7f72
_ITC_SPR4	=	0x7f73
_ITC_SPR4_bit	=	0x7f73
_ITC_SPR5	=	0x7f74
_ITC_SPR5_bit	=	0x7f74
_ITC_SPR6	=	0x7f75
_ITC_SPR6_bit	=	0x7f75
_ITC_SPR7	=	0x7f76
_ITC_SPR7_bit	=	0x7f76
_ITC_SPR8	=	0x7f77
_ITC_SPR8_bit	=	0x7f77
_RST_SR	=	0x50b3
_RST_SR_bit	=	0x50b3
_CLK_ICKR	=	0x50c0
_CLK_ICKR_bit	=	0x50c0
_CLK_ECKR	=	0x50c1
_CLK_ECKR_bit	=	0x50c1
_CLK_SWR	=	0x50c4
_CLK_SWCR	=	0x50c5
_CLK_SWCR_bit	=	0x50c5
_CLK_CKDIVR	=	0x50c6
_CLK_CKDIVR_bit	=	0x50c6
_CLK_PCKENR1	=	0x50c7
_CLK_CSSR	=	0x50c8
_CLK_CSSR_bit	=	0x50c8
_CLK_CCOR	=	0x50c9
_CLK_CCOR_bit	=	0x50c9
_CLK_PCKENR2	=	0x50ca
_CLK_CANCCR	=	0x50cb
_CLK_CANCCR_bit	=	0x50cb
_CLK_HSITRIMR	=	0x50cc
_CLK_HSITRIMR_bit	=	0x50cc
_CLK_SWIMCCR	=	0x50cd
_CLK_SWIMCCR_bit	=	0x50cd
_WWDG_CR	=	0x50d1
_WWDG_CR_bit	=	0x50d1
_WWDG_WR	=	0x50d2
_WWDG_WR_bit	=	0x50d2
_IWDG_KR	=	0x50e0
_IWDG_PR	=	0x50e1
_IWDG_PR_bit	=	0x50e1
_IWDG_RLR	=	0x50e2
_AWU_CSR1	=	0x50f0
_AWU_CSR1_bit	=	0x50f0
_AWU_APR	=	0x50f1
_AWU_TBR	=	0x50f2
_AWU_TBR_bit	=	0x50f2
_BEEP_CSR	=	0x50f3
_BEEP_CSR_bit	=	0x50f3
_SPI_CR1	=	0x5200
_SPI_CR1_bit	=	0x5200
_SPI_CR2	=	0x5201
_SPI_CR2_bit	=	0x5201
_SPI_ICR	=	0x5202
_SPI_ICR_bit	=	0x5202
_SPI_SR	=	0x5203
_SPI_SR_bit	=	0x5203
_SPI_DR	=	0x5204
_SPI_CRCPR	=	0x5205
_I2C_CR1	=	0x5210
_I2C_CR1_bit	=	0x5210
_I2C_CR2	=	0x5211
_I2C_CR2_bit	=	0x5211
_I2C_FREQR	=	0x5212
_I2C_FREQR_bit	=	0x5212
_I2C_OARL	=	0x5213
_I2C_OARL_bit	=	0x5213
_I2C_OARH	=	0x5214
_I2C_OARH_bit	=	0x5214
_I2C_DR	=	0x5216
_I2C_SR2	=	0x5218
_I2C_SR2_bit	=	0x5218
_I2C_ITR	=	0x521a
_I2C_ITR_bit	=	0x521a
_I2C_CCRL	=	0x521b
_I2C_CCRH	=	0x521c
_I2C_CCRH_bit	=	0x521c
_I2C_TRISER	=	0x521d
_I2C_TRISER_bit	=	0x521d
_I2C_PECR	=	0x521e
_UART1_SR	=	0x5230
_UART1_SR_bit	=	0x5230
_UART1_DR	=	0x5231
_UART1_BRR1	=	0x5232
_UART1_BRR2	=	0x5233
_UART1_CR1	=	0x5234
_UART1_CR1_bit	=	0x5234
_UART1_CR2	=	0x5235
_UART1_CR2_bit	=	0x5235
_UART1_CR3	=	0x5236
_UART1_CR3_bit	=	0x5236
_UART1_CR4	=	0x5237
_UART1_CR4_bit	=	0x5237
_UART1_CR5	=	0x5238
_UART1_CR5_bit	=	0x5238
_UART1_GTR	=	0x5239
_UART1_PSCR	=	0x523a
_UART2_SR	=	0x5240
_UART2_SR_bit	=	0x5240
_UART2_DR	=	0x5241
_UART2_BRR1	=	0x5242
_UART2_BRR2	=	0x5243
_UART2_CR1	=	0x5244
_UART2_CR1_bit	=	0x5244
_UART2_CR2	=	0x5245
_UART2_CR2_bit	=	0x5245
_UART2_CR3	=	0x5246
_UART2_CR3_bit	=	0x5246
_UART2_CR4	=	0x5247
_UART2_CR4_bit	=	0x5247
_UART2_CR6	=	0x5249
_UART2_CR6_bit	=	0x5249
_UART2_GTR	=	0x524a
_UART2_PSCR	=	0x524b
_UART3_SR	=	0x5240
_UART3_SR_bit	=	0x5240
_UART3_DR	=	0x5241
_UART3_BRR1	=	0x5242
_UART3_BRR2	=	0x5243
_UART3_CR1	=	0x5244
_UART3_CR1_bit	=	0x5244
_UART3_CR2	=	0x5245
_UART3_CR2_bit	=	0x5245
_UART3_CR3	=	0x5246
_UART3_CR3_bit	=	0x5246
_UART3_CR4	=	0x5247
_UART3_CR4_bit	=	0x5247
_UART3_CR6	=	0x5249
_UART3_CR6_bit	=	0x5249
_TIM1_CR1	=	0x5250
_TIM1_CR1_bit	=	0x5250
_TIM1_CR2	=	0x5251
_TIM1_CR2_bit	=	0x5251
_TIM1_SMCR	=	0x5252
_TIM1_SMCR_bit	=	0x5252
_TIM1_ETR	=	0x5253
_TIM1_ETR_bit	=	0x5253
_TIM1_IER	=	0x5254
_TIM1_IER_bit	=	0x5254
_TIM1_SR1	=	0x5255
_TIM1_SR1_bit	=	0x5255
_TIM1_SR2	=	0x5256
_TIM1_SR2_bit	=	0x5256
_TIM1_EGR	=	0x5257
_TIM1_EGR_bit	=	0x5257
_TIM1_CCMR1	=	0x5258
_TIM1_CCMR1_bit	=	0x5258
_TIM1_CCMR2	=	0x5259
_TIM1_CCMR2_bit	=	0x5259
_TIM1_CCMR3	=	0x525a
_TIM1_CCMR3_bit	=	0x525a
_TIM1_CCMR4	=	0x525b
_TIM1_CCMR4_bit	=	0x525b
_TIM1_CCER1	=	0x525c
_TIM1_CCER1_bit	=	0x525c
_TIM1_CCER2	=	0x525d
_TIM1_CCER2_bit	=	0x525d
_TIM1_CNTRH	=	0x525e
_TIM1_CNTRL	=	0x525f
_TIM1_PSCRH	=	0x5260
_TIM1_PSCRL	=	0x5261
_TIM1_ARRH	=	0x5262
_TIM1_ARRL	=	0x5263
_TIM1_RCR	=	0x5264
_TIM1_CCR1H	=	0x5265
_TIM1_CCR1L	=	0x5266
_TIM1_CCR2H	=	0x5267
_TIM1_CCR2L	=	0x5268
_TIM1_CCR3H	=	0x5269
_TIM1_CCR3L	=	0x526a
_TIM1_CCR4H	=	0x526b
_TIM1_CCR4L	=	0x526c
_TIM1_BKR	=	0x526d
_TIM1_BKR_bit	=	0x526d
_TIM1_DTR	=	0x526e
_TIM1_OISR	=	0x526f
_TIM1_OISR_bit	=	0x526f
_TIM2_CR1	=	0x5300
_TIM2_CR1_bit	=	0x5300
_TIM2_IER	=	0x5301
_TIM2_IER_bit	=	0x5301
_TIM2_SR1	=	0x5302
_TIM2_SR1_bit	=	0x5302
_TIM2_SR2	=	0x5303
_TIM2_SR2_bit	=	0x5303
_TIM2_EGR	=	0x5304
_TIM2_EGR_bit	=	0x5304
_TIM2_CCMR1	=	0x5305
_TIM2_CCMR1_bit	=	0x5305
_TIM2_CCMR2	=	0x5306
_TIM2_CCMR2_bit	=	0x5306
_TIM2_CCMR3	=	0x5307
_TIM2_CCMR3_bit	=	0x5307
_TIM2_CCER1	=	0x5308
_TIM2_CCER1_bit	=	0x5308
_TIM2_CCER2	=	0x5309
_TIM2_CCER2_bit	=	0x5309
_TIM2_CNTRH	=	0x530a
_TIM2_CNTRL	=	0x530b
_TIM2_PSCR	=	0x530c
_TIM2_PSCR_bit	=	0x530c
_TIM2_ARRH	=	0x530d
_TIM2_ARRL	=	0x530e
_TIM2_CCR1H	=	0x530f
_TIM2_CCR1L	=	0x5310
_TIM2_CCR2H	=	0x5311
_TIM2_CCR2L	=	0x5312
_TIM2_CCR3H	=	0x5313
_TIM2_CCR3L	=	0x5314
_TIM3_CR1	=	0x5320
_TIM3_CR1_bit	=	0x5320
_TIM3_IER	=	0x5321
_TIM3_IER_bit	=	0x5321
_TIM3_SR1	=	0x5322
_TIM3_SR1_bit	=	0x5322
_TIM3_SR2	=	0x5323
_TIM3_SR2_bit	=	0x5323
_TIM3_EGR	=	0x5324
_TIM3_EGR_bit	=	0x5324
_TIM3_CCMR1	=	0x5325
_TIM3_CCMR1_bit	=	0x5325
_TIM3_CCMR2	=	0x5326
_TIM3_CCMR2_bit	=	0x5326
_TIM3_CCER1	=	0x5327
_TIM3_CCER1_bit	=	0x5327
_TIM3_CNTRH	=	0x5328
_TIM3_CNTRL	=	0x5329
_TIM3_PSCR	=	0x532a
_TIM3_PSCR_bit	=	0x532a
_TIM3_ARRH	=	0x532b
_TIM3_ARRL	=	0x532c
_TIM3_CCR1H	=	0x532d
_TIM3_CCR1L	=	0x532e
_TIM3_CCR2H	=	0x532f
_TIM3_CCR2L	=	0x5330
_TIM4_CR1	=	0x5340
_TIM4_CR1_bit	=	0x5340
_TIM4_IER	=	0x5341
_TIM4_IER_bit	=	0x5341
_TIM4_SR	=	0x5342
_TIM4_SR_bit	=	0x5342
_TIM4_EGR	=	0x5343
_TIM4_EGR_bit	=	0x5343
_TIM4_CNTR	=	0x5344
_TIM4_PSCR	=	0x5345
_TIM4_PSCR_bit	=	0x5345
_TIM4_ARR	=	0x5346
_ADC_CSR	=	0x5400
_ADC_CSR_bit	=	0x5400
_ADC_CR1	=	0x5401
_ADC_CR1_bit	=	0x5401
_ADC_CR2	=	0x5402
_ADC_CR2_bit	=	0x5402
_ADC_CR3	=	0x5403
_ADC_CR3_bit	=	0x5403
_ADC_TDRH	=	0x5406
_ADC_TDRL	=	0x5407
_CAN_MCR	=	0x5420
_CAN_MCR_bit	=	0x5420
_CAN_MSR	=	0x5421
_CAN_MSR_bit	=	0x5421
_CAN_TSR	=	0x5422
_CAN_TSR_bit	=	0x5422
_CAN_RFR	=	0x5424
_CAN_RFR_bit	=	0x5424
_CAN_IER	=	0x5425
_CAN_IER_bit	=	0x5425
_CAN_DGR	=	0x5426
_CAN_DGR_bit	=	0x5426
_CAN_FPSR	=	0x5427
_CAN_ESR	=	0x5428
_CAN_ESR_bit	=	0x5428
_CAN_EIER	=	0x5429
_CAN_EIER_bit	=	0x5429
_CAN_P0	=	0x5428
_CAN_P1	=	0x5429
_CAN_P2	=	0x542a
_CAN_P3	=	0x542b
_CAN_P4	=	0x542c
_CAN_P5	=	0x542d
_CAN_P6	=	0x542e
_CAN_P7	=	0x542f
_CAN_P8	=	0x5430
_CAN_P9	=	0x5431
_CAN_PA	=	0x5432
_CAN_PB	=	0x5433
_CAN_PC	=	0x5434
_CAN_PD	=	0x5435
_CAN_PE	=	0x5436
_CAN_PF	=	0x5437
_CPU_A	=	0x7f00
_CPU_PCE	=	0x7f01
_CPU_PCH	=	0x7f02
_CPU_PCL	=	0x7f03
_CPU_XH	=	0x7f04
_CPU_XL	=	0x7f05
_CPU_YH	=	0x7f06
_CPU_YL	=	0x7f07
_CPU_SPH	=	0x7f08
_CPU_SPL	=	0x7f09
_CPU_CCR	=	0x7f0a
_CPU_CCR_bit	=	0x7f0a
_CPU_CFG_GCR	=	0x7f60
_CPU_CFG_GCR_bit	=	0x7f60
_SWIM_CSR	=	0x7f80
_DM_BK1RE	=	0x7f90
_DM_BK1RH	=	0x7f91
_DM_BK1RL	=	0x7f92
_DM_BK2RE	=	0x7f93
_DM_BK2RH	=	0x7f94
_DM_BK2RL	=	0x7f95
_DM_CR1	=	0x7f96
_DM_CR2	=	0x7f97
_DM_CSR1	=	0x7f98
_DM_CSR2	=	0x7f99
_DM_ENFCTR	=	0x7f9a
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ; reset
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	./src/main.c: 3: void gpio_init()
;	-----------------------------------------
;	 function gpio_init
;	-----------------------------------------
_gpio_init:
;	./src/main.c: 5: PA_DDR |= 1 << 2; //输出
	bset	_PA_DDR+0, #2
;	./src/main.c: 6: PA_CR1 |= 1 << 2; //推挽输出
	bset	_PA_CR1+0, #2
;	./src/main.c: 7: PA_CR2 &= ~(1 << 2); //没有中断
	bres	_PA_CR2+0, #2
;	./src/main.c: 8: PA_ODR &= ~(1 << 2); //初始输出低电平
	bres	_PA_ODR+0, #2
;	./src/main.c: 10: PD_DDR |= MASK_PD_DDR_DDR4;
	ld	a, _PD_DDR+0
	or	a, #0x10
	ld	_PD_DDR+0, a
;	./src/main.c: 11: PD_CR1 |= MASK_PD_CR1_C14;
	ld	a, _PD_CR1+0
	or	a, #0x10
	ld	_PD_CR1+0, a
;	./src/main.c: 12: PD_CR2 &= ~MASK_PD_CR2_C24;
	bres	_PD_CR2+0, #4
;	./src/main.c: 13: PD_ODR |= MASK_PD_ODR_ODR4; //输出高电平
	ld	a, _PD_ODR+0
	or	a, #0x10
	ld	_PD_ODR+0, a
;	./src/main.c: 14: }
	ret
;	./src/main.c: 17: void main()
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	./src/main.c: 19: gpio_init();
	call	_gpio_init
;	./src/main.c: 23: while (1);
00102$:
	jra	00102$
;	./src/main.c: 24: }
	ret
	.area CODE
	.area CONST
_PA_IDR	=	0x5001
_PA_IDR_bit	=	0x5001
_PB_IDR	=	0x5006
_PB_IDR_bit	=	0x5006
_PC_IDR	=	0x500b
_PC_IDR_bit	=	0x500b
_PD_IDR	=	0x5010
_PD_IDR_bit	=	0x5010
_PE_IDR	=	0x5015
_PE_IDR_bit	=	0x5015
_PF_IDR	=	0x501a
_PF_IDR_bit	=	0x501a
_PG_IDR	=	0x501f
_PG_IDR_bit	=	0x501f
_PH_IDR	=	0x5024
_PH_IDR_bit	=	0x5024
_PI_IDR	=	0x5029
_PI_IDR_bit	=	0x5029
_CLK_CMSR	=	0x50c3
_SPI_RXCRCR	=	0x5206
_SPI_TXCRCR	=	0x5207
_I2C_SR1	=	0x5217
_I2C_SR1_bit	=	0x5217
_I2C_SR3	=	0x5219
_I2C_SR3_bit	=	0x5219
_ADC_DRH	=	0x5404
_ADC_DRL	=	0x5405
_CAN_TPR	=	0x5423
_CAN_TPR_bit	=	0x5423
	.area INITIALIZER
	.area CABS (ABS)
