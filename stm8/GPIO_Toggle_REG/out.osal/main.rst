                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _CAN_TPR_bit
                                     12 	.globl _CAN_TPR
                                     13 	.globl _ADC_DRL
                                     14 	.globl _ADC_DRH
                                     15 	.globl _I2C_SR3_bit
                                     16 	.globl _I2C_SR3
                                     17 	.globl _I2C_SR1_bit
                                     18 	.globl _I2C_SR1
                                     19 	.globl _SPI_TXCRCR
                                     20 	.globl _SPI_RXCRCR
                                     21 	.globl _CLK_CMSR
                                     22 	.globl _PI_IDR_bit
                                     23 	.globl _PI_IDR
                                     24 	.globl _PH_IDR_bit
                                     25 	.globl _PH_IDR
                                     26 	.globl _PG_IDR_bit
                                     27 	.globl _PG_IDR
                                     28 	.globl _PF_IDR_bit
                                     29 	.globl _PF_IDR
                                     30 	.globl _PE_IDR_bit
                                     31 	.globl _PE_IDR
                                     32 	.globl _PD_IDR_bit
                                     33 	.globl _PD_IDR
                                     34 	.globl _PC_IDR_bit
                                     35 	.globl _PC_IDR
                                     36 	.globl _PB_IDR_bit
                                     37 	.globl _PB_IDR
                                     38 	.globl _PA_IDR_bit
                                     39 	.globl _PA_IDR
                                     40 	.globl _main
                                     41 	.globl _gpio_init
                                     42 	.globl _DM_ENFCTR
                                     43 	.globl _DM_CSR2
                                     44 	.globl _DM_CSR1
                                     45 	.globl _DM_CR2
                                     46 	.globl _DM_CR1
                                     47 	.globl _DM_BK2RL
                                     48 	.globl _DM_BK2RH
                                     49 	.globl _DM_BK2RE
                                     50 	.globl _DM_BK1RL
                                     51 	.globl _DM_BK1RH
                                     52 	.globl _DM_BK1RE
                                     53 	.globl _SWIM_CSR
                                     54 	.globl _CPU_CFG_GCR_bit
                                     55 	.globl _CPU_CFG_GCR
                                     56 	.globl _CPU_CCR_bit
                                     57 	.globl _CPU_CCR
                                     58 	.globl _CPU_SPL
                                     59 	.globl _CPU_SPH
                                     60 	.globl _CPU_YL
                                     61 	.globl _CPU_YH
                                     62 	.globl _CPU_XL
                                     63 	.globl _CPU_XH
                                     64 	.globl _CPU_PCL
                                     65 	.globl _CPU_PCH
                                     66 	.globl _CPU_PCE
                                     67 	.globl _CPU_A
                                     68 	.globl _CAN_PF
                                     69 	.globl _CAN_PE
                                     70 	.globl _CAN_PD
                                     71 	.globl _CAN_PC
                                     72 	.globl _CAN_PB
                                     73 	.globl _CAN_PA
                                     74 	.globl _CAN_P9
                                     75 	.globl _CAN_P8
                                     76 	.globl _CAN_P7
                                     77 	.globl _CAN_P6
                                     78 	.globl _CAN_P5
                                     79 	.globl _CAN_P4
                                     80 	.globl _CAN_P3
                                     81 	.globl _CAN_P2
                                     82 	.globl _CAN_P1
                                     83 	.globl _CAN_P0
                                     84 	.globl _CAN_EIER_bit
                                     85 	.globl _CAN_EIER
                                     86 	.globl _CAN_ESR_bit
                                     87 	.globl _CAN_ESR
                                     88 	.globl _CAN_FPSR
                                     89 	.globl _CAN_DGR_bit
                                     90 	.globl _CAN_DGR
                                     91 	.globl _CAN_IER_bit
                                     92 	.globl _CAN_IER
                                     93 	.globl _CAN_RFR_bit
                                     94 	.globl _CAN_RFR
                                     95 	.globl _CAN_TSR_bit
                                     96 	.globl _CAN_TSR
                                     97 	.globl _CAN_MSR_bit
                                     98 	.globl _CAN_MSR
                                     99 	.globl _CAN_MCR_bit
                                    100 	.globl _CAN_MCR
                                    101 	.globl _ADC_TDRL
                                    102 	.globl _ADC_TDRH
                                    103 	.globl _ADC_CR3_bit
                                    104 	.globl _ADC_CR3
                                    105 	.globl _ADC_CR2_bit
                                    106 	.globl _ADC_CR2
                                    107 	.globl _ADC_CR1_bit
                                    108 	.globl _ADC_CR1
                                    109 	.globl _ADC_CSR_bit
                                    110 	.globl _ADC_CSR
                                    111 	.globl _TIM4_ARR
                                    112 	.globl _TIM4_PSCR_bit
                                    113 	.globl _TIM4_PSCR
                                    114 	.globl _TIM4_CNTR
                                    115 	.globl _TIM4_EGR_bit
                                    116 	.globl _TIM4_EGR
                                    117 	.globl _TIM4_SR_bit
                                    118 	.globl _TIM4_SR
                                    119 	.globl _TIM4_IER_bit
                                    120 	.globl _TIM4_IER
                                    121 	.globl _TIM4_CR1_bit
                                    122 	.globl _TIM4_CR1
                                    123 	.globl _TIM3_CCR2L
                                    124 	.globl _TIM3_CCR2H
                                    125 	.globl _TIM3_CCR1L
                                    126 	.globl _TIM3_CCR1H
                                    127 	.globl _TIM3_ARRL
                                    128 	.globl _TIM3_ARRH
                                    129 	.globl _TIM3_PSCR_bit
                                    130 	.globl _TIM3_PSCR
                                    131 	.globl _TIM3_CNTRL
                                    132 	.globl _TIM3_CNTRH
                                    133 	.globl _TIM3_CCER1_bit
                                    134 	.globl _TIM3_CCER1
                                    135 	.globl _TIM3_CCMR2_bit
                                    136 	.globl _TIM3_CCMR2
                                    137 	.globl _TIM3_CCMR1_bit
                                    138 	.globl _TIM3_CCMR1
                                    139 	.globl _TIM3_EGR_bit
                                    140 	.globl _TIM3_EGR
                                    141 	.globl _TIM3_SR2_bit
                                    142 	.globl _TIM3_SR2
                                    143 	.globl _TIM3_SR1_bit
                                    144 	.globl _TIM3_SR1
                                    145 	.globl _TIM3_IER_bit
                                    146 	.globl _TIM3_IER
                                    147 	.globl _TIM3_CR1_bit
                                    148 	.globl _TIM3_CR1
                                    149 	.globl _TIM2_CCR3L
                                    150 	.globl _TIM2_CCR3H
                                    151 	.globl _TIM2_CCR2L
                                    152 	.globl _TIM2_CCR2H
                                    153 	.globl _TIM2_CCR1L
                                    154 	.globl _TIM2_CCR1H
                                    155 	.globl _TIM2_ARRL
                                    156 	.globl _TIM2_ARRH
                                    157 	.globl _TIM2_PSCR_bit
                                    158 	.globl _TIM2_PSCR
                                    159 	.globl _TIM2_CNTRL
                                    160 	.globl _TIM2_CNTRH
                                    161 	.globl _TIM2_CCER2_bit
                                    162 	.globl _TIM2_CCER2
                                    163 	.globl _TIM2_CCER1_bit
                                    164 	.globl _TIM2_CCER1
                                    165 	.globl _TIM2_CCMR3_bit
                                    166 	.globl _TIM2_CCMR3
                                    167 	.globl _TIM2_CCMR2_bit
                                    168 	.globl _TIM2_CCMR2
                                    169 	.globl _TIM2_CCMR1_bit
                                    170 	.globl _TIM2_CCMR1
                                    171 	.globl _TIM2_EGR_bit
                                    172 	.globl _TIM2_EGR
                                    173 	.globl _TIM2_SR2_bit
                                    174 	.globl _TIM2_SR2
                                    175 	.globl _TIM2_SR1_bit
                                    176 	.globl _TIM2_SR1
                                    177 	.globl _TIM2_IER_bit
                                    178 	.globl _TIM2_IER
                                    179 	.globl _TIM2_CR1_bit
                                    180 	.globl _TIM2_CR1
                                    181 	.globl _TIM1_OISR_bit
                                    182 	.globl _TIM1_OISR
                                    183 	.globl _TIM1_DTR
                                    184 	.globl _TIM1_BKR_bit
                                    185 	.globl _TIM1_BKR
                                    186 	.globl _TIM1_CCR4L
                                    187 	.globl _TIM1_CCR4H
                                    188 	.globl _TIM1_CCR3L
                                    189 	.globl _TIM1_CCR3H
                                    190 	.globl _TIM1_CCR2L
                                    191 	.globl _TIM1_CCR2H
                                    192 	.globl _TIM1_CCR1L
                                    193 	.globl _TIM1_CCR1H
                                    194 	.globl _TIM1_RCR
                                    195 	.globl _TIM1_ARRL
                                    196 	.globl _TIM1_ARRH
                                    197 	.globl _TIM1_PSCRL
                                    198 	.globl _TIM1_PSCRH
                                    199 	.globl _TIM1_CNTRL
                                    200 	.globl _TIM1_CNTRH
                                    201 	.globl _TIM1_CCER2_bit
                                    202 	.globl _TIM1_CCER2
                                    203 	.globl _TIM1_CCER1_bit
                                    204 	.globl _TIM1_CCER1
                                    205 	.globl _TIM1_CCMR4_bit
                                    206 	.globl _TIM1_CCMR4
                                    207 	.globl _TIM1_CCMR3_bit
                                    208 	.globl _TIM1_CCMR3
                                    209 	.globl _TIM1_CCMR2_bit
                                    210 	.globl _TIM1_CCMR2
                                    211 	.globl _TIM1_CCMR1_bit
                                    212 	.globl _TIM1_CCMR1
                                    213 	.globl _TIM1_EGR_bit
                                    214 	.globl _TIM1_EGR
                                    215 	.globl _TIM1_SR2_bit
                                    216 	.globl _TIM1_SR2
                                    217 	.globl _TIM1_SR1_bit
                                    218 	.globl _TIM1_SR1
                                    219 	.globl _TIM1_IER_bit
                                    220 	.globl _TIM1_IER
                                    221 	.globl _TIM1_ETR_bit
                                    222 	.globl _TIM1_ETR
                                    223 	.globl _TIM1_SMCR_bit
                                    224 	.globl _TIM1_SMCR
                                    225 	.globl _TIM1_CR2_bit
                                    226 	.globl _TIM1_CR2
                                    227 	.globl _TIM1_CR1_bit
                                    228 	.globl _TIM1_CR1
                                    229 	.globl _UART3_CR6_bit
                                    230 	.globl _UART3_CR6
                                    231 	.globl _UART3_CR4_bit
                                    232 	.globl _UART3_CR4
                                    233 	.globl _UART3_CR3_bit
                                    234 	.globl _UART3_CR3
                                    235 	.globl _UART3_CR2_bit
                                    236 	.globl _UART3_CR2
                                    237 	.globl _UART3_CR1_bit
                                    238 	.globl _UART3_CR1
                                    239 	.globl _UART3_BRR2
                                    240 	.globl _UART3_BRR1
                                    241 	.globl _UART3_DR
                                    242 	.globl _UART3_SR_bit
                                    243 	.globl _UART3_SR
                                    244 	.globl _UART2_PSCR
                                    245 	.globl _UART2_GTR
                                    246 	.globl _UART2_CR6_bit
                                    247 	.globl _UART2_CR6
                                    248 	.globl _UART2_CR4_bit
                                    249 	.globl _UART2_CR4
                                    250 	.globl _UART2_CR3_bit
                                    251 	.globl _UART2_CR3
                                    252 	.globl _UART2_CR2_bit
                                    253 	.globl _UART2_CR2
                                    254 	.globl _UART2_CR1_bit
                                    255 	.globl _UART2_CR1
                                    256 	.globl _UART2_BRR2
                                    257 	.globl _UART2_BRR1
                                    258 	.globl _UART2_DR
                                    259 	.globl _UART2_SR_bit
                                    260 	.globl _UART2_SR
                                    261 	.globl _UART1_PSCR
                                    262 	.globl _UART1_GTR
                                    263 	.globl _UART1_CR5_bit
                                    264 	.globl _UART1_CR5
                                    265 	.globl _UART1_CR4_bit
                                    266 	.globl _UART1_CR4
                                    267 	.globl _UART1_CR3_bit
                                    268 	.globl _UART1_CR3
                                    269 	.globl _UART1_CR2_bit
                                    270 	.globl _UART1_CR2
                                    271 	.globl _UART1_CR1_bit
                                    272 	.globl _UART1_CR1
                                    273 	.globl _UART1_BRR2
                                    274 	.globl _UART1_BRR1
                                    275 	.globl _UART1_DR
                                    276 	.globl _UART1_SR_bit
                                    277 	.globl _UART1_SR
                                    278 	.globl _I2C_PECR
                                    279 	.globl _I2C_TRISER_bit
                                    280 	.globl _I2C_TRISER
                                    281 	.globl _I2C_CCRH_bit
                                    282 	.globl _I2C_CCRH
                                    283 	.globl _I2C_CCRL
                                    284 	.globl _I2C_ITR_bit
                                    285 	.globl _I2C_ITR
                                    286 	.globl _I2C_SR2_bit
                                    287 	.globl _I2C_SR2
                                    288 	.globl _I2C_DR
                                    289 	.globl _I2C_OARH_bit
                                    290 	.globl _I2C_OARH
                                    291 	.globl _I2C_OARL_bit
                                    292 	.globl _I2C_OARL
                                    293 	.globl _I2C_FREQR_bit
                                    294 	.globl _I2C_FREQR
                                    295 	.globl _I2C_CR2_bit
                                    296 	.globl _I2C_CR2
                                    297 	.globl _I2C_CR1_bit
                                    298 	.globl _I2C_CR1
                                    299 	.globl _SPI_CRCPR
                                    300 	.globl _SPI_DR
                                    301 	.globl _SPI_SR_bit
                                    302 	.globl _SPI_SR
                                    303 	.globl _SPI_ICR_bit
                                    304 	.globl _SPI_ICR
                                    305 	.globl _SPI_CR2_bit
                                    306 	.globl _SPI_CR2
                                    307 	.globl _SPI_CR1_bit
                                    308 	.globl _SPI_CR1
                                    309 	.globl _BEEP_CSR_bit
                                    310 	.globl _BEEP_CSR
                                    311 	.globl _AWU_TBR_bit
                                    312 	.globl _AWU_TBR
                                    313 	.globl _AWU_APR
                                    314 	.globl _AWU_CSR1_bit
                                    315 	.globl _AWU_CSR1
                                    316 	.globl _IWDG_RLR
                                    317 	.globl _IWDG_PR_bit
                                    318 	.globl _IWDG_PR
                                    319 	.globl _IWDG_KR
                                    320 	.globl _WWDG_WR_bit
                                    321 	.globl _WWDG_WR
                                    322 	.globl _WWDG_CR_bit
                                    323 	.globl _WWDG_CR
                                    324 	.globl _CLK_SWIMCCR_bit
                                    325 	.globl _CLK_SWIMCCR
                                    326 	.globl _CLK_HSITRIMR_bit
                                    327 	.globl _CLK_HSITRIMR
                                    328 	.globl _CLK_CANCCR_bit
                                    329 	.globl _CLK_CANCCR
                                    330 	.globl _CLK_PCKENR2
                                    331 	.globl _CLK_CCOR_bit
                                    332 	.globl _CLK_CCOR
                                    333 	.globl _CLK_CSSR_bit
                                    334 	.globl _CLK_CSSR
                                    335 	.globl _CLK_PCKENR1
                                    336 	.globl _CLK_CKDIVR_bit
                                    337 	.globl _CLK_CKDIVR
                                    338 	.globl _CLK_SWCR_bit
                                    339 	.globl _CLK_SWCR
                                    340 	.globl _CLK_SWR
                                    341 	.globl _CLK_ECKR_bit
                                    342 	.globl _CLK_ECKR
                                    343 	.globl _CLK_ICKR_bit
                                    344 	.globl _CLK_ICKR
                                    345 	.globl _RST_SR_bit
                                    346 	.globl _RST_SR
                                    347 	.globl _ITC_SPR8_bit
                                    348 	.globl _ITC_SPR8
                                    349 	.globl _ITC_SPR7_bit
                                    350 	.globl _ITC_SPR7
                                    351 	.globl _ITC_SPR6_bit
                                    352 	.globl _ITC_SPR6
                                    353 	.globl _ITC_SPR5_bit
                                    354 	.globl _ITC_SPR5
                                    355 	.globl _ITC_SPR4_bit
                                    356 	.globl _ITC_SPR4
                                    357 	.globl _ITC_SPR3_bit
                                    358 	.globl _ITC_SPR3
                                    359 	.globl _ITC_SPR2_bit
                                    360 	.globl _ITC_SPR2
                                    361 	.globl _ITC_SPR1_bit
                                    362 	.globl _ITC_SPR1
                                    363 	.globl _EXTI_CR2_bit
                                    364 	.globl _EXTI_CR2
                                    365 	.globl _EXTI_CR1_bit
                                    366 	.globl _EXTI_CR1
                                    367 	.globl _FLASH_DUKR
                                    368 	.globl _FLASH_PUKR
                                    369 	.globl _FLASH_IAPSR_bit
                                    370 	.globl _FLASH_IAPSR
                                    371 	.globl _FLASH_NFPR
                                    372 	.globl _FLASH_FPR
                                    373 	.globl _FLASH_NCR2_bit
                                    374 	.globl _FLASH_NCR2
                                    375 	.globl _FLASH_CR2_bit
                                    376 	.globl _FLASH_CR2
                                    377 	.globl _FLASH_CR1_bit
                                    378 	.globl _FLASH_CR1
                                    379 	.globl _PI_CR2_bit
                                    380 	.globl _PI_CR2
                                    381 	.globl _PI_CR1_bit
                                    382 	.globl _PI_CR1
                                    383 	.globl _PI_DDR_bit
                                    384 	.globl _PI_DDR
                                    385 	.globl _PI_ODR_bit
                                    386 	.globl _PI_ODR
                                    387 	.globl _PH_CR2_bit
                                    388 	.globl _PH_CR2
                                    389 	.globl _PH_CR1_bit
                                    390 	.globl _PH_CR1
                                    391 	.globl _PH_DDR_bit
                                    392 	.globl _PH_DDR
                                    393 	.globl _PH_ODR_bit
                                    394 	.globl _PH_ODR
                                    395 	.globl _PG_CR2_bit
                                    396 	.globl _PG_CR2
                                    397 	.globl _PG_CR1_bit
                                    398 	.globl _PG_CR1
                                    399 	.globl _PG_DDR_bit
                                    400 	.globl _PG_DDR
                                    401 	.globl _PG_ODR_bit
                                    402 	.globl _PG_ODR
                                    403 	.globl _PF_CR2_bit
                                    404 	.globl _PF_CR2
                                    405 	.globl _PF_CR1_bit
                                    406 	.globl _PF_CR1
                                    407 	.globl _PF_DDR_bit
                                    408 	.globl _PF_DDR
                                    409 	.globl _PF_ODR_bit
                                    410 	.globl _PF_ODR
                                    411 	.globl _PE_CR2_bit
                                    412 	.globl _PE_CR2
                                    413 	.globl _PE_CR1_bit
                                    414 	.globl _PE_CR1
                                    415 	.globl _PE_DDR_bit
                                    416 	.globl _PE_DDR
                                    417 	.globl _PE_ODR_bit
                                    418 	.globl _PE_ODR
                                    419 	.globl _PD_CR2_bit
                                    420 	.globl _PD_CR2
                                    421 	.globl _PD_CR1_bit
                                    422 	.globl _PD_CR1
                                    423 	.globl _PD_DDR_bit
                                    424 	.globl _PD_DDR
                                    425 	.globl _PD_ODR_bit
                                    426 	.globl _PD_ODR
                                    427 	.globl _PC_CR2_bit
                                    428 	.globl _PC_CR2
                                    429 	.globl _PC_CR1_bit
                                    430 	.globl _PC_CR1
                                    431 	.globl _PC_DDR_bit
                                    432 	.globl _PC_DDR
                                    433 	.globl _PC_ODR_bit
                                    434 	.globl _PC_ODR
                                    435 	.globl _PB_CR2_bit
                                    436 	.globl _PB_CR2
                                    437 	.globl _PB_CR1_bit
                                    438 	.globl _PB_CR1
                                    439 	.globl _PB_DDR_bit
                                    440 	.globl _PB_DDR
                                    441 	.globl _PB_ODR_bit
                                    442 	.globl _PB_ODR
                                    443 	.globl _PA_CR2_bit
                                    444 	.globl _PA_CR2
                                    445 	.globl _PA_CR1_bit
                                    446 	.globl _PA_CR1
                                    447 	.globl _PA_DDR_bit
                                    448 	.globl _PA_DDR
                                    449 	.globl _PA_ODR_bit
                                    450 	.globl _PA_ODR
                                    451 ;--------------------------------------------------------
                                    452 ; ram data
                                    453 ;--------------------------------------------------------
                                    454 	.area DATA
                           005000   455 _PA_ODR	=	0x5000
                           005000   456 _PA_ODR_bit	=	0x5000
                           005002   457 _PA_DDR	=	0x5002
                           005002   458 _PA_DDR_bit	=	0x5002
                           005003   459 _PA_CR1	=	0x5003
                           005003   460 _PA_CR1_bit	=	0x5003
                           005004   461 _PA_CR2	=	0x5004
                           005004   462 _PA_CR2_bit	=	0x5004
                           005005   463 _PB_ODR	=	0x5005
                           005005   464 _PB_ODR_bit	=	0x5005
                           005007   465 _PB_DDR	=	0x5007
                           005007   466 _PB_DDR_bit	=	0x5007
                           005008   467 _PB_CR1	=	0x5008
                           005008   468 _PB_CR1_bit	=	0x5008
                           005009   469 _PB_CR2	=	0x5009
                           005009   470 _PB_CR2_bit	=	0x5009
                           00500A   471 _PC_ODR	=	0x500a
                           00500A   472 _PC_ODR_bit	=	0x500a
                           00500C   473 _PC_DDR	=	0x500c
                           00500C   474 _PC_DDR_bit	=	0x500c
                           00500D   475 _PC_CR1	=	0x500d
                           00500D   476 _PC_CR1_bit	=	0x500d
                           00500E   477 _PC_CR2	=	0x500e
                           00500E   478 _PC_CR2_bit	=	0x500e
                           00500F   479 _PD_ODR	=	0x500f
                           00500F   480 _PD_ODR_bit	=	0x500f
                           005011   481 _PD_DDR	=	0x5011
                           005011   482 _PD_DDR_bit	=	0x5011
                           005012   483 _PD_CR1	=	0x5012
                           005012   484 _PD_CR1_bit	=	0x5012
                           005013   485 _PD_CR2	=	0x5013
                           005013   486 _PD_CR2_bit	=	0x5013
                           005014   487 _PE_ODR	=	0x5014
                           005014   488 _PE_ODR_bit	=	0x5014
                           005016   489 _PE_DDR	=	0x5016
                           005016   490 _PE_DDR_bit	=	0x5016
                           005017   491 _PE_CR1	=	0x5017
                           005017   492 _PE_CR1_bit	=	0x5017
                           005018   493 _PE_CR2	=	0x5018
                           005018   494 _PE_CR2_bit	=	0x5018
                           005019   495 _PF_ODR	=	0x5019
                           005019   496 _PF_ODR_bit	=	0x5019
                           00501B   497 _PF_DDR	=	0x501b
                           00501B   498 _PF_DDR_bit	=	0x501b
                           00501C   499 _PF_CR1	=	0x501c
                           00501C   500 _PF_CR1_bit	=	0x501c
                           00501D   501 _PF_CR2	=	0x501d
                           00501D   502 _PF_CR2_bit	=	0x501d
                           00501E   503 _PG_ODR	=	0x501e
                           00501E   504 _PG_ODR_bit	=	0x501e
                           005020   505 _PG_DDR	=	0x5020
                           005020   506 _PG_DDR_bit	=	0x5020
                           005021   507 _PG_CR1	=	0x5021
                           005021   508 _PG_CR1_bit	=	0x5021
                           005022   509 _PG_CR2	=	0x5022
                           005022   510 _PG_CR2_bit	=	0x5022
                           005023   511 _PH_ODR	=	0x5023
                           005023   512 _PH_ODR_bit	=	0x5023
                           005025   513 _PH_DDR	=	0x5025
                           005025   514 _PH_DDR_bit	=	0x5025
                           005026   515 _PH_CR1	=	0x5026
                           005026   516 _PH_CR1_bit	=	0x5026
                           005027   517 _PH_CR2	=	0x5027
                           005027   518 _PH_CR2_bit	=	0x5027
                           005028   519 _PI_ODR	=	0x5028
                           005028   520 _PI_ODR_bit	=	0x5028
                           00502A   521 _PI_DDR	=	0x502a
                           00502A   522 _PI_DDR_bit	=	0x502a
                           00502B   523 _PI_CR1	=	0x502b
                           00502B   524 _PI_CR1_bit	=	0x502b
                           00502C   525 _PI_CR2	=	0x502c
                           00502C   526 _PI_CR2_bit	=	0x502c
                           00505A   527 _FLASH_CR1	=	0x505a
                           00505A   528 _FLASH_CR1_bit	=	0x505a
                           00505B   529 _FLASH_CR2	=	0x505b
                           00505B   530 _FLASH_CR2_bit	=	0x505b
                           00505C   531 _FLASH_NCR2	=	0x505c
                           00505C   532 _FLASH_NCR2_bit	=	0x505c
                           00505D   533 _FLASH_FPR	=	0x505d
                           00505E   534 _FLASH_NFPR	=	0x505e
                           00505F   535 _FLASH_IAPSR	=	0x505f
                           00505F   536 _FLASH_IAPSR_bit	=	0x505f
                           005062   537 _FLASH_PUKR	=	0x5062
                           005064   538 _FLASH_DUKR	=	0x5064
                           0050A0   539 _EXTI_CR1	=	0x50a0
                           0050A0   540 _EXTI_CR1_bit	=	0x50a0
                           0050A1   541 _EXTI_CR2	=	0x50a1
                           0050A1   542 _EXTI_CR2_bit	=	0x50a1
                           007F70   543 _ITC_SPR1	=	0x7f70
                           007F70   544 _ITC_SPR1_bit	=	0x7f70
                           007F71   545 _ITC_SPR2	=	0x7f71
                           007F71   546 _ITC_SPR2_bit	=	0x7f71
                           007F72   547 _ITC_SPR3	=	0x7f72
                           007F72   548 _ITC_SPR3_bit	=	0x7f72
                           007F73   549 _ITC_SPR4	=	0x7f73
                           007F73   550 _ITC_SPR4_bit	=	0x7f73
                           007F74   551 _ITC_SPR5	=	0x7f74
                           007F74   552 _ITC_SPR5_bit	=	0x7f74
                           007F75   553 _ITC_SPR6	=	0x7f75
                           007F75   554 _ITC_SPR6_bit	=	0x7f75
                           007F76   555 _ITC_SPR7	=	0x7f76
                           007F76   556 _ITC_SPR7_bit	=	0x7f76
                           007F77   557 _ITC_SPR8	=	0x7f77
                           007F77   558 _ITC_SPR8_bit	=	0x7f77
                           0050B3   559 _RST_SR	=	0x50b3
                           0050B3   560 _RST_SR_bit	=	0x50b3
                           0050C0   561 _CLK_ICKR	=	0x50c0
                           0050C0   562 _CLK_ICKR_bit	=	0x50c0
                           0050C1   563 _CLK_ECKR	=	0x50c1
                           0050C1   564 _CLK_ECKR_bit	=	0x50c1
                           0050C4   565 _CLK_SWR	=	0x50c4
                           0050C5   566 _CLK_SWCR	=	0x50c5
                           0050C5   567 _CLK_SWCR_bit	=	0x50c5
                           0050C6   568 _CLK_CKDIVR	=	0x50c6
                           0050C6   569 _CLK_CKDIVR_bit	=	0x50c6
                           0050C7   570 _CLK_PCKENR1	=	0x50c7
                           0050C8   571 _CLK_CSSR	=	0x50c8
                           0050C8   572 _CLK_CSSR_bit	=	0x50c8
                           0050C9   573 _CLK_CCOR	=	0x50c9
                           0050C9   574 _CLK_CCOR_bit	=	0x50c9
                           0050CA   575 _CLK_PCKENR2	=	0x50ca
                           0050CB   576 _CLK_CANCCR	=	0x50cb
                           0050CB   577 _CLK_CANCCR_bit	=	0x50cb
                           0050CC   578 _CLK_HSITRIMR	=	0x50cc
                           0050CC   579 _CLK_HSITRIMR_bit	=	0x50cc
                           0050CD   580 _CLK_SWIMCCR	=	0x50cd
                           0050CD   581 _CLK_SWIMCCR_bit	=	0x50cd
                           0050D1   582 _WWDG_CR	=	0x50d1
                           0050D1   583 _WWDG_CR_bit	=	0x50d1
                           0050D2   584 _WWDG_WR	=	0x50d2
                           0050D2   585 _WWDG_WR_bit	=	0x50d2
                           0050E0   586 _IWDG_KR	=	0x50e0
                           0050E1   587 _IWDG_PR	=	0x50e1
                           0050E1   588 _IWDG_PR_bit	=	0x50e1
                           0050E2   589 _IWDG_RLR	=	0x50e2
                           0050F0   590 _AWU_CSR1	=	0x50f0
                           0050F0   591 _AWU_CSR1_bit	=	0x50f0
                           0050F1   592 _AWU_APR	=	0x50f1
                           0050F2   593 _AWU_TBR	=	0x50f2
                           0050F2   594 _AWU_TBR_bit	=	0x50f2
                           0050F3   595 _BEEP_CSR	=	0x50f3
                           0050F3   596 _BEEP_CSR_bit	=	0x50f3
                           005200   597 _SPI_CR1	=	0x5200
                           005200   598 _SPI_CR1_bit	=	0x5200
                           005201   599 _SPI_CR2	=	0x5201
                           005201   600 _SPI_CR2_bit	=	0x5201
                           005202   601 _SPI_ICR	=	0x5202
                           005202   602 _SPI_ICR_bit	=	0x5202
                           005203   603 _SPI_SR	=	0x5203
                           005203   604 _SPI_SR_bit	=	0x5203
                           005204   605 _SPI_DR	=	0x5204
                           005205   606 _SPI_CRCPR	=	0x5205
                           005210   607 _I2C_CR1	=	0x5210
                           005210   608 _I2C_CR1_bit	=	0x5210
                           005211   609 _I2C_CR2	=	0x5211
                           005211   610 _I2C_CR2_bit	=	0x5211
                           005212   611 _I2C_FREQR	=	0x5212
                           005212   612 _I2C_FREQR_bit	=	0x5212
                           005213   613 _I2C_OARL	=	0x5213
                           005213   614 _I2C_OARL_bit	=	0x5213
                           005214   615 _I2C_OARH	=	0x5214
                           005214   616 _I2C_OARH_bit	=	0x5214
                           005216   617 _I2C_DR	=	0x5216
                           005218   618 _I2C_SR2	=	0x5218
                           005218   619 _I2C_SR2_bit	=	0x5218
                           00521A   620 _I2C_ITR	=	0x521a
                           00521A   621 _I2C_ITR_bit	=	0x521a
                           00521B   622 _I2C_CCRL	=	0x521b
                           00521C   623 _I2C_CCRH	=	0x521c
                           00521C   624 _I2C_CCRH_bit	=	0x521c
                           00521D   625 _I2C_TRISER	=	0x521d
                           00521D   626 _I2C_TRISER_bit	=	0x521d
                           00521E   627 _I2C_PECR	=	0x521e
                           005230   628 _UART1_SR	=	0x5230
                           005230   629 _UART1_SR_bit	=	0x5230
                           005231   630 _UART1_DR	=	0x5231
                           005232   631 _UART1_BRR1	=	0x5232
                           005233   632 _UART1_BRR2	=	0x5233
                           005234   633 _UART1_CR1	=	0x5234
                           005234   634 _UART1_CR1_bit	=	0x5234
                           005235   635 _UART1_CR2	=	0x5235
                           005235   636 _UART1_CR2_bit	=	0x5235
                           005236   637 _UART1_CR3	=	0x5236
                           005236   638 _UART1_CR3_bit	=	0x5236
                           005237   639 _UART1_CR4	=	0x5237
                           005237   640 _UART1_CR4_bit	=	0x5237
                           005238   641 _UART1_CR5	=	0x5238
                           005238   642 _UART1_CR5_bit	=	0x5238
                           005239   643 _UART1_GTR	=	0x5239
                           00523A   644 _UART1_PSCR	=	0x523a
                           005240   645 _UART2_SR	=	0x5240
                           005240   646 _UART2_SR_bit	=	0x5240
                           005241   647 _UART2_DR	=	0x5241
                           005242   648 _UART2_BRR1	=	0x5242
                           005243   649 _UART2_BRR2	=	0x5243
                           005244   650 _UART2_CR1	=	0x5244
                           005244   651 _UART2_CR1_bit	=	0x5244
                           005245   652 _UART2_CR2	=	0x5245
                           005245   653 _UART2_CR2_bit	=	0x5245
                           005246   654 _UART2_CR3	=	0x5246
                           005246   655 _UART2_CR3_bit	=	0x5246
                           005247   656 _UART2_CR4	=	0x5247
                           005247   657 _UART2_CR4_bit	=	0x5247
                           005249   658 _UART2_CR6	=	0x5249
                           005249   659 _UART2_CR6_bit	=	0x5249
                           00524A   660 _UART2_GTR	=	0x524a
                           00524B   661 _UART2_PSCR	=	0x524b
                           005240   662 _UART3_SR	=	0x5240
                           005240   663 _UART3_SR_bit	=	0x5240
                           005241   664 _UART3_DR	=	0x5241
                           005242   665 _UART3_BRR1	=	0x5242
                           005243   666 _UART3_BRR2	=	0x5243
                           005244   667 _UART3_CR1	=	0x5244
                           005244   668 _UART3_CR1_bit	=	0x5244
                           005245   669 _UART3_CR2	=	0x5245
                           005245   670 _UART3_CR2_bit	=	0x5245
                           005246   671 _UART3_CR3	=	0x5246
                           005246   672 _UART3_CR3_bit	=	0x5246
                           005247   673 _UART3_CR4	=	0x5247
                           005247   674 _UART3_CR4_bit	=	0x5247
                           005249   675 _UART3_CR6	=	0x5249
                           005249   676 _UART3_CR6_bit	=	0x5249
                           005250   677 _TIM1_CR1	=	0x5250
                           005250   678 _TIM1_CR1_bit	=	0x5250
                           005251   679 _TIM1_CR2	=	0x5251
                           005251   680 _TIM1_CR2_bit	=	0x5251
                           005252   681 _TIM1_SMCR	=	0x5252
                           005252   682 _TIM1_SMCR_bit	=	0x5252
                           005253   683 _TIM1_ETR	=	0x5253
                           005253   684 _TIM1_ETR_bit	=	0x5253
                           005254   685 _TIM1_IER	=	0x5254
                           005254   686 _TIM1_IER_bit	=	0x5254
                           005255   687 _TIM1_SR1	=	0x5255
                           005255   688 _TIM1_SR1_bit	=	0x5255
                           005256   689 _TIM1_SR2	=	0x5256
                           005256   690 _TIM1_SR2_bit	=	0x5256
                           005257   691 _TIM1_EGR	=	0x5257
                           005257   692 _TIM1_EGR_bit	=	0x5257
                           005258   693 _TIM1_CCMR1	=	0x5258
                           005258   694 _TIM1_CCMR1_bit	=	0x5258
                           005259   695 _TIM1_CCMR2	=	0x5259
                           005259   696 _TIM1_CCMR2_bit	=	0x5259
                           00525A   697 _TIM1_CCMR3	=	0x525a
                           00525A   698 _TIM1_CCMR3_bit	=	0x525a
                           00525B   699 _TIM1_CCMR4	=	0x525b
                           00525B   700 _TIM1_CCMR4_bit	=	0x525b
                           00525C   701 _TIM1_CCER1	=	0x525c
                           00525C   702 _TIM1_CCER1_bit	=	0x525c
                           00525D   703 _TIM1_CCER2	=	0x525d
                           00525D   704 _TIM1_CCER2_bit	=	0x525d
                           00525E   705 _TIM1_CNTRH	=	0x525e
                           00525F   706 _TIM1_CNTRL	=	0x525f
                           005260   707 _TIM1_PSCRH	=	0x5260
                           005261   708 _TIM1_PSCRL	=	0x5261
                           005262   709 _TIM1_ARRH	=	0x5262
                           005263   710 _TIM1_ARRL	=	0x5263
                           005264   711 _TIM1_RCR	=	0x5264
                           005265   712 _TIM1_CCR1H	=	0x5265
                           005266   713 _TIM1_CCR1L	=	0x5266
                           005267   714 _TIM1_CCR2H	=	0x5267
                           005268   715 _TIM1_CCR2L	=	0x5268
                           005269   716 _TIM1_CCR3H	=	0x5269
                           00526A   717 _TIM1_CCR3L	=	0x526a
                           00526B   718 _TIM1_CCR4H	=	0x526b
                           00526C   719 _TIM1_CCR4L	=	0x526c
                           00526D   720 _TIM1_BKR	=	0x526d
                           00526D   721 _TIM1_BKR_bit	=	0x526d
                           00526E   722 _TIM1_DTR	=	0x526e
                           00526F   723 _TIM1_OISR	=	0x526f
                           00526F   724 _TIM1_OISR_bit	=	0x526f
                           005300   725 _TIM2_CR1	=	0x5300
                           005300   726 _TIM2_CR1_bit	=	0x5300
                           005301   727 _TIM2_IER	=	0x5301
                           005301   728 _TIM2_IER_bit	=	0x5301
                           005302   729 _TIM2_SR1	=	0x5302
                           005302   730 _TIM2_SR1_bit	=	0x5302
                           005303   731 _TIM2_SR2	=	0x5303
                           005303   732 _TIM2_SR2_bit	=	0x5303
                           005304   733 _TIM2_EGR	=	0x5304
                           005304   734 _TIM2_EGR_bit	=	0x5304
                           005305   735 _TIM2_CCMR1	=	0x5305
                           005305   736 _TIM2_CCMR1_bit	=	0x5305
                           005306   737 _TIM2_CCMR2	=	0x5306
                           005306   738 _TIM2_CCMR2_bit	=	0x5306
                           005307   739 _TIM2_CCMR3	=	0x5307
                           005307   740 _TIM2_CCMR3_bit	=	0x5307
                           005308   741 _TIM2_CCER1	=	0x5308
                           005308   742 _TIM2_CCER1_bit	=	0x5308
                           005309   743 _TIM2_CCER2	=	0x5309
                           005309   744 _TIM2_CCER2_bit	=	0x5309
                           00530A   745 _TIM2_CNTRH	=	0x530a
                           00530B   746 _TIM2_CNTRL	=	0x530b
                           00530C   747 _TIM2_PSCR	=	0x530c
                           00530C   748 _TIM2_PSCR_bit	=	0x530c
                           00530D   749 _TIM2_ARRH	=	0x530d
                           00530E   750 _TIM2_ARRL	=	0x530e
                           00530F   751 _TIM2_CCR1H	=	0x530f
                           005310   752 _TIM2_CCR1L	=	0x5310
                           005311   753 _TIM2_CCR2H	=	0x5311
                           005312   754 _TIM2_CCR2L	=	0x5312
                           005313   755 _TIM2_CCR3H	=	0x5313
                           005314   756 _TIM2_CCR3L	=	0x5314
                           005320   757 _TIM3_CR1	=	0x5320
                           005320   758 _TIM3_CR1_bit	=	0x5320
                           005321   759 _TIM3_IER	=	0x5321
                           005321   760 _TIM3_IER_bit	=	0x5321
                           005322   761 _TIM3_SR1	=	0x5322
                           005322   762 _TIM3_SR1_bit	=	0x5322
                           005323   763 _TIM3_SR2	=	0x5323
                           005323   764 _TIM3_SR2_bit	=	0x5323
                           005324   765 _TIM3_EGR	=	0x5324
                           005324   766 _TIM3_EGR_bit	=	0x5324
                           005325   767 _TIM3_CCMR1	=	0x5325
                           005325   768 _TIM3_CCMR1_bit	=	0x5325
                           005326   769 _TIM3_CCMR2	=	0x5326
                           005326   770 _TIM3_CCMR2_bit	=	0x5326
                           005327   771 _TIM3_CCER1	=	0x5327
                           005327   772 _TIM3_CCER1_bit	=	0x5327
                           005328   773 _TIM3_CNTRH	=	0x5328
                           005329   774 _TIM3_CNTRL	=	0x5329
                           00532A   775 _TIM3_PSCR	=	0x532a
                           00532A   776 _TIM3_PSCR_bit	=	0x532a
                           00532B   777 _TIM3_ARRH	=	0x532b
                           00532C   778 _TIM3_ARRL	=	0x532c
                           00532D   779 _TIM3_CCR1H	=	0x532d
                           00532E   780 _TIM3_CCR1L	=	0x532e
                           00532F   781 _TIM3_CCR2H	=	0x532f
                           005330   782 _TIM3_CCR2L	=	0x5330
                           005340   783 _TIM4_CR1	=	0x5340
                           005340   784 _TIM4_CR1_bit	=	0x5340
                           005341   785 _TIM4_IER	=	0x5341
                           005341   786 _TIM4_IER_bit	=	0x5341
                           005342   787 _TIM4_SR	=	0x5342
                           005342   788 _TIM4_SR_bit	=	0x5342
                           005343   789 _TIM4_EGR	=	0x5343
                           005343   790 _TIM4_EGR_bit	=	0x5343
                           005344   791 _TIM4_CNTR	=	0x5344
                           005345   792 _TIM4_PSCR	=	0x5345
                           005345   793 _TIM4_PSCR_bit	=	0x5345
                           005346   794 _TIM4_ARR	=	0x5346
                           005400   795 _ADC_CSR	=	0x5400
                           005400   796 _ADC_CSR_bit	=	0x5400
                           005401   797 _ADC_CR1	=	0x5401
                           005401   798 _ADC_CR1_bit	=	0x5401
                           005402   799 _ADC_CR2	=	0x5402
                           005402   800 _ADC_CR2_bit	=	0x5402
                           005403   801 _ADC_CR3	=	0x5403
                           005403   802 _ADC_CR3_bit	=	0x5403
                           005406   803 _ADC_TDRH	=	0x5406
                           005407   804 _ADC_TDRL	=	0x5407
                           005420   805 _CAN_MCR	=	0x5420
                           005420   806 _CAN_MCR_bit	=	0x5420
                           005421   807 _CAN_MSR	=	0x5421
                           005421   808 _CAN_MSR_bit	=	0x5421
                           005422   809 _CAN_TSR	=	0x5422
                           005422   810 _CAN_TSR_bit	=	0x5422
                           005424   811 _CAN_RFR	=	0x5424
                           005424   812 _CAN_RFR_bit	=	0x5424
                           005425   813 _CAN_IER	=	0x5425
                           005425   814 _CAN_IER_bit	=	0x5425
                           005426   815 _CAN_DGR	=	0x5426
                           005426   816 _CAN_DGR_bit	=	0x5426
                           005427   817 _CAN_FPSR	=	0x5427
                           005428   818 _CAN_ESR	=	0x5428
                           005428   819 _CAN_ESR_bit	=	0x5428
                           005429   820 _CAN_EIER	=	0x5429
                           005429   821 _CAN_EIER_bit	=	0x5429
                           005428   822 _CAN_P0	=	0x5428
                           005429   823 _CAN_P1	=	0x5429
                           00542A   824 _CAN_P2	=	0x542a
                           00542B   825 _CAN_P3	=	0x542b
                           00542C   826 _CAN_P4	=	0x542c
                           00542D   827 _CAN_P5	=	0x542d
                           00542E   828 _CAN_P6	=	0x542e
                           00542F   829 _CAN_P7	=	0x542f
                           005430   830 _CAN_P8	=	0x5430
                           005431   831 _CAN_P9	=	0x5431
                           005432   832 _CAN_PA	=	0x5432
                           005433   833 _CAN_PB	=	0x5433
                           005434   834 _CAN_PC	=	0x5434
                           005435   835 _CAN_PD	=	0x5435
                           005436   836 _CAN_PE	=	0x5436
                           005437   837 _CAN_PF	=	0x5437
                           007F00   838 _CPU_A	=	0x7f00
                           007F01   839 _CPU_PCE	=	0x7f01
                           007F02   840 _CPU_PCH	=	0x7f02
                           007F03   841 _CPU_PCL	=	0x7f03
                           007F04   842 _CPU_XH	=	0x7f04
                           007F05   843 _CPU_XL	=	0x7f05
                           007F06   844 _CPU_YH	=	0x7f06
                           007F07   845 _CPU_YL	=	0x7f07
                           007F08   846 _CPU_SPH	=	0x7f08
                           007F09   847 _CPU_SPL	=	0x7f09
                           007F0A   848 _CPU_CCR	=	0x7f0a
                           007F0A   849 _CPU_CCR_bit	=	0x7f0a
                           007F60   850 _CPU_CFG_GCR	=	0x7f60
                           007F60   851 _CPU_CFG_GCR_bit	=	0x7f60
                           007F80   852 _SWIM_CSR	=	0x7f80
                           007F90   853 _DM_BK1RE	=	0x7f90
                           007F91   854 _DM_BK1RH	=	0x7f91
                           007F92   855 _DM_BK1RL	=	0x7f92
                           007F93   856 _DM_BK2RE	=	0x7f93
                           007F94   857 _DM_BK2RH	=	0x7f94
                           007F95   858 _DM_BK2RL	=	0x7f95
                           007F96   859 _DM_CR1	=	0x7f96
                           007F97   860 _DM_CR2	=	0x7f97
                           007F98   861 _DM_CSR1	=	0x7f98
                           007F99   862 _DM_CSR2	=	0x7f99
                           007F9A   863 _DM_ENFCTR	=	0x7f9a
                                    864 ;--------------------------------------------------------
                                    865 ; ram data
                                    866 ;--------------------------------------------------------
                                    867 	.area INITIALIZED
                                    868 ;--------------------------------------------------------
                                    869 ; Stack segment in internal ram 
                                    870 ;--------------------------------------------------------
                                    871 	.area	SSEG
      FFFFFF                        872 __start__stack:
      FFFFFF                        873 	.ds	1
                                    874 
                                    875 ;--------------------------------------------------------
                                    876 ; absolute external ram data
                                    877 ;--------------------------------------------------------
                                    878 	.area DABS (ABS)
                                    879 
                                    880 ; default segment ordering for linker
                                    881 	.area HOME
                                    882 	.area GSINIT
                                    883 	.area GSFINAL
                                    884 	.area CONST
                                    885 	.area INITIALIZER
                                    886 	.area CODE
                                    887 
                                    888 ;--------------------------------------------------------
                                    889 ; interrupt vector 
                                    890 ;--------------------------------------------------------
                                    891 	.area HOME
      008000                        892 __interrupt_vect:
      008000 82 00 80 07            893 	int s_GSINIT ; reset
                                    894 ;--------------------------------------------------------
                                    895 ; global & static initialisations
                                    896 ;--------------------------------------------------------
                                    897 	.area HOME
                                    898 	.area GSINIT
                                    899 	.area GSFINAL
                                    900 	.area GSINIT
      008007                        901 __sdcc_gs_init_startup:
      008007                        902 __sdcc_init_data:
                                    903 ; stm8_genXINIT() start
      008007 AE 04 0D         [ 2]  904 	ldw x, #l_DATA
      00800A 27 07            [ 1]  905 	jreq	00002$
      00800C                        906 00001$:
      00800C 72 4F 00 00      [ 1]  907 	clr (s_DATA - 1, x)
      008010 5A               [ 2]  908 	decw x
      008011 26 F9            [ 1]  909 	jrne	00001$
      008013                        910 00002$:
      008013 AE 00 07         [ 2]  911 	ldw	x, #l_INITIALIZER
      008016 27 09            [ 1]  912 	jreq	00004$
      008018                        913 00003$:
      008018 D6 80 26         [ 1]  914 	ld	a, (s_INITIALIZER - 1, x)
      00801B D7 04 0D         [ 1]  915 	ld	(s_INITIALIZED - 1, x), a
      00801E 5A               [ 2]  916 	decw	x
      00801F 26 F7            [ 1]  917 	jrne	00003$
      008021                        918 00004$:
                                    919 ; stm8_genXINIT() end
                                    920 	.area GSFINAL
      008021 CC 80 04         [ 2]  921 	jp	__sdcc_program_startup
                                    922 ;--------------------------------------------------------
                                    923 ; Home
                                    924 ;--------------------------------------------------------
                                    925 	.area HOME
                                    926 	.area HOME
      008004                        927 __sdcc_program_startup:
      008004 CC 85 FA         [ 2]  928 	jp	_main
                                    929 ;	return from main will return to caller
                                    930 ;--------------------------------------------------------
                                    931 ; code
                                    932 ;--------------------------------------------------------
                                    933 	.area CODE
                                    934 ;	./src/main.c: 3: void gpio_init()
                                    935 ;	-----------------------------------------
                                    936 ;	 function gpio_init
                                    937 ;	-----------------------------------------
      0085CD                        938 _gpio_init:
                                    939 ;	./src/main.c: 5: PA_DDR |= 1 << 2; //输出
      0085CD 72 14 50 02      [ 1]  940 	bset	_PA_DDR+0, #2
                                    941 ;	./src/main.c: 6: PA_CR1 |= 1 << 2; //推挽输出
      0085D1 72 14 50 03      [ 1]  942 	bset	_PA_CR1+0, #2
                                    943 ;	./src/main.c: 7: PA_CR2 &= ~(1 << 2); //没有中断
      0085D5 72 15 50 04      [ 1]  944 	bres	_PA_CR2+0, #2
                                    945 ;	./src/main.c: 8: PA_ODR &= ~(1 << 2); //初始输出低电平
      0085D9 72 15 50 00      [ 1]  946 	bres	_PA_ODR+0, #2
                                    947 ;	./src/main.c: 10: PD_DDR |= MASK_PD_DDR_DDR4;
      0085DD C6 50 11         [ 1]  948 	ld	a, _PD_DDR+0
      0085E0 AA 10            [ 1]  949 	or	a, #0x10
      0085E2 C7 50 11         [ 1]  950 	ld	_PD_DDR+0, a
                                    951 ;	./src/main.c: 11: PD_CR1 |= MASK_PD_CR1_C14;
      0085E5 C6 50 12         [ 1]  952 	ld	a, _PD_CR1+0
      0085E8 AA 10            [ 1]  953 	or	a, #0x10
      0085EA C7 50 12         [ 1]  954 	ld	_PD_CR1+0, a
                                    955 ;	./src/main.c: 12: PD_CR2 &= ~MASK_PD_CR2_C24;
      0085ED 72 19 50 13      [ 1]  956 	bres	_PD_CR2+0, #4
                                    957 ;	./src/main.c: 13: PD_ODR |= MASK_PD_ODR_ODR4; //输出高电平
      0085F1 C6 50 0F         [ 1]  958 	ld	a, _PD_ODR+0
      0085F4 AA 10            [ 1]  959 	or	a, #0x10
      0085F6 C7 50 0F         [ 1]  960 	ld	_PD_ODR+0, a
                                    961 ;	./src/main.c: 14: }
      0085F9 81               [ 4]  962 	ret
                                    963 ;	./src/main.c: 17: void main()
                                    964 ;	-----------------------------------------
                                    965 ;	 function main
                                    966 ;	-----------------------------------------
      0085FA                        967 _main:
                                    968 ;	./src/main.c: 19: gpio_init();
      0085FA CD 85 CD         [ 4]  969 	call	_gpio_init
                                    970 ;	./src/main.c: 23: while (1);
      0085FD                        971 00102$:
      0085FD 20 FE            [ 2]  972 	jra	00102$
                                    973 ;	./src/main.c: 24: }
      0085FF 81               [ 4]  974 	ret
                                    975 	.area CODE
                                    976 	.area CONST
                           005001   977 _PA_IDR	=	0x5001
                           005001   978 _PA_IDR_bit	=	0x5001
                           005006   979 _PB_IDR	=	0x5006
                           005006   980 _PB_IDR_bit	=	0x5006
                           00500B   981 _PC_IDR	=	0x500b
                           00500B   982 _PC_IDR_bit	=	0x500b
                           005010   983 _PD_IDR	=	0x5010
                           005010   984 _PD_IDR_bit	=	0x5010
                           005015   985 _PE_IDR	=	0x5015
                           005015   986 _PE_IDR_bit	=	0x5015
                           00501A   987 _PF_IDR	=	0x501a
                           00501A   988 _PF_IDR_bit	=	0x501a
                           00501F   989 _PG_IDR	=	0x501f
                           00501F   990 _PG_IDR_bit	=	0x501f
                           005024   991 _PH_IDR	=	0x5024
                           005024   992 _PH_IDR_bit	=	0x5024
                           005029   993 _PI_IDR	=	0x5029
                           005029   994 _PI_IDR_bit	=	0x5029
                           0050C3   995 _CLK_CMSR	=	0x50c3
                           005206   996 _SPI_RXCRCR	=	0x5206
                           005207   997 _SPI_TXCRCR	=	0x5207
                           005217   998 _I2C_SR1	=	0x5217
                           005217   999 _I2C_SR1_bit	=	0x5217
                           005219  1000 _I2C_SR3	=	0x5219
                           005219  1001 _I2C_SR3_bit	=	0x5219
                           005404  1002 _ADC_DRH	=	0x5404
                           005405  1003 _ADC_DRL	=	0x5405
                           005423  1004 _CAN_TPR	=	0x5423
                           005423  1005 _CAN_TPR_bit	=	0x5423
                                   1006 	.area INITIALIZER
                                   1007 	.area CABS (ABS)
