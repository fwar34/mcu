                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module stm8s_it
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _TRAP_IRQHandler
                                     12 	.globl _TLI_IRQHandler
                                     13 	.globl _AWU_IRQHandler
                                     14 	.globl _CLK_IRQHandler
                                     15 	.globl _EXTI_PORTA_IRQHandler
                                     16 	.globl _EXTI_PORTB_IRQHandler
                                     17 	.globl _EXTI_PORTC_IRQHandler
                                     18 	.globl _EXTI_PORTD_IRQHandler
                                     19 	.globl _EXTI_PORTE_IRQHandler
                                     20 	.globl _SPI_IRQHandler
                                     21 	.globl _TIM1_UPD_OVF_TRG_BRK_IRQHandler
                                     22 	.globl _TIM1_CAP_COM_IRQHandler
                                     23 	.globl _TIM2_UPD_OVF_BRK_IRQHandler
                                     24 	.globl _TIM2_CAP_COM_IRQHandler
                                     25 	.globl _TIM3_UPD_OVF_BRK_IRQHandler
                                     26 	.globl _TIM3_CAP_COM_IRQHandler
                                     27 	.globl _I2C_IRQHandler
                                     28 	.globl _UART2_TX_IRQHandler
                                     29 	.globl _UART2_RX_IRQHandler
                                     30 	.globl _ADC1_IRQHandler
                                     31 	.globl _TIM4_UPD_OVF_IRQHandler
                                     32 	.globl _EEPROM_EEC_IRQHandler
                                     33 ;--------------------------------------------------------
                                     34 ; ram data
                                     35 ;--------------------------------------------------------
                                     36 	.area DATA
                                     37 ;--------------------------------------------------------
                                     38 ; ram data
                                     39 ;--------------------------------------------------------
                                     40 	.area INITIALIZED
                                     41 ;--------------------------------------------------------
                                     42 ; absolute external ram data
                                     43 ;--------------------------------------------------------
                                     44 	.area DABS (ABS)
                                     45 
                                     46 ; default segment ordering for linker
                                     47 	.area HOME
                                     48 	.area GSINIT
                                     49 	.area GSFINAL
                                     50 	.area CONST
                                     51 	.area INITIALIZER
                                     52 	.area CODE
                                     53 
                                     54 ;--------------------------------------------------------
                                     55 ; global & static initialisations
                                     56 ;--------------------------------------------------------
                                     57 	.area HOME
                                     58 	.area GSINIT
                                     59 	.area GSFINAL
                                     60 	.area GSINIT
                                     61 ;--------------------------------------------------------
                                     62 ; Home
                                     63 ;--------------------------------------------------------
                                     64 	.area HOME
                                     65 	.area HOME
                                     66 ;--------------------------------------------------------
                                     67 ; code
                                     68 ;--------------------------------------------------------
                                     69 	.area CODE
                                     70 ;	./src/stm8s_it.c: 62: INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
                                     71 ;	-----------------------------------------
                                     72 ;	 function TRAP_IRQHandler
                                     73 ;	-----------------------------------------
      0080F6                         74 _TRAP_IRQHandler:
                                     75 ;	./src/stm8s_it.c: 67: }
      0080F6 80               [11]   76 	iret
                                     77 ;	./src/stm8s_it.c: 73: INTERRUPT_HANDLER(TLI_IRQHandler, 0)
                                     78 ;	-----------------------------------------
                                     79 ;	 function TLI_IRQHandler
                                     80 ;	-----------------------------------------
      0080F7                         81 _TLI_IRQHandler:
                                     82 ;	./src/stm8s_it.c: 78: }
      0080F7 80               [11]   83 	iret
                                     84 ;	./src/stm8s_it.c: 85: INTERRUPT_HANDLER(AWU_IRQHandler, 1)
                                     85 ;	-----------------------------------------
                                     86 ;	 function AWU_IRQHandler
                                     87 ;	-----------------------------------------
      0080F8                         88 _AWU_IRQHandler:
                                     89 ;	./src/stm8s_it.c: 90: }
      0080F8 80               [11]   90 	iret
                                     91 ;	./src/stm8s_it.c: 97: INTERRUPT_HANDLER(CLK_IRQHandler, 2)
                                     92 ;	-----------------------------------------
                                     93 ;	 function CLK_IRQHandler
                                     94 ;	-----------------------------------------
      0080F9                         95 _CLK_IRQHandler:
                                     96 ;	./src/stm8s_it.c: 102: }
      0080F9 80               [11]   97 	iret
                                     98 ;	./src/stm8s_it.c: 109: INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
                                     99 ;	-----------------------------------------
                                    100 ;	 function EXTI_PORTA_IRQHandler
                                    101 ;	-----------------------------------------
      0080FA                        102 _EXTI_PORTA_IRQHandler:
                                    103 ;	./src/stm8s_it.c: 114: }
      0080FA 80               [11]  104 	iret
                                    105 ;	./src/stm8s_it.c: 121: INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
                                    106 ;	-----------------------------------------
                                    107 ;	 function EXTI_PORTB_IRQHandler
                                    108 ;	-----------------------------------------
      0080FB                        109 _EXTI_PORTB_IRQHandler:
                                    110 ;	./src/stm8s_it.c: 126: }
      0080FB 80               [11]  111 	iret
                                    112 ;	./src/stm8s_it.c: 133: INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
                                    113 ;	-----------------------------------------
                                    114 ;	 function EXTI_PORTC_IRQHandler
                                    115 ;	-----------------------------------------
      0080FC                        116 _EXTI_PORTC_IRQHandler:
                                    117 ;	./src/stm8s_it.c: 138: }
      0080FC 80               [11]  118 	iret
                                    119 ;	./src/stm8s_it.c: 145: INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
                                    120 ;	-----------------------------------------
                                    121 ;	 function EXTI_PORTD_IRQHandler
                                    122 ;	-----------------------------------------
      0080FD                        123 _EXTI_PORTD_IRQHandler:
                                    124 ;	./src/stm8s_it.c: 150: }
      0080FD 80               [11]  125 	iret
                                    126 ;	./src/stm8s_it.c: 157: INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
                                    127 ;	-----------------------------------------
                                    128 ;	 function EXTI_PORTE_IRQHandler
                                    129 ;	-----------------------------------------
      0080FE                        130 _EXTI_PORTE_IRQHandler:
                                    131 ;	./src/stm8s_it.c: 162: }
      0080FE 80               [11]  132 	iret
                                    133 ;	./src/stm8s_it.c: 208: INTERRUPT_HANDLER(SPI_IRQHandler, 10)
                                    134 ;	-----------------------------------------
                                    135 ;	 function SPI_IRQHandler
                                    136 ;	-----------------------------------------
      0080FF                        137 _SPI_IRQHandler:
                                    138 ;	./src/stm8s_it.c: 213: }
      0080FF 80               [11]  139 	iret
                                    140 ;	./src/stm8s_it.c: 220: INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
                                    141 ;	-----------------------------------------
                                    142 ;	 function TIM1_UPD_OVF_TRG_BRK_IRQHandler
                                    143 ;	-----------------------------------------
      008100                        144 _TIM1_UPD_OVF_TRG_BRK_IRQHandler:
                                    145 ;	./src/stm8s_it.c: 225: }
      008100 80               [11]  146 	iret
                                    147 ;	./src/stm8s_it.c: 232: INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
                                    148 ;	-----------------------------------------
                                    149 ;	 function TIM1_CAP_COM_IRQHandler
                                    150 ;	-----------------------------------------
      008101                        151 _TIM1_CAP_COM_IRQHandler:
                                    152 ;	./src/stm8s_it.c: 237: }
      008101 80               [11]  153 	iret
                                    154 ;	./src/stm8s_it.c: 269: INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
                                    155 ;	-----------------------------------------
                                    156 ;	 function TIM2_UPD_OVF_BRK_IRQHandler
                                    157 ;	-----------------------------------------
      008102                        158 _TIM2_UPD_OVF_BRK_IRQHandler:
                                    159 ;	./src/stm8s_it.c: 274: }
      008102 80               [11]  160 	iret
                                    161 ;	./src/stm8s_it.c: 281: INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
                                    162 ;	-----------------------------------------
                                    163 ;	 function TIM2_CAP_COM_IRQHandler
                                    164 ;	-----------------------------------------
      008103                        165 _TIM2_CAP_COM_IRQHandler:
                                    166 ;	./src/stm8s_it.c: 286: }
      008103 80               [11]  167 	iret
                                    168 ;	./src/stm8s_it.c: 296: INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
                                    169 ;	-----------------------------------------
                                    170 ;	 function TIM3_UPD_OVF_BRK_IRQHandler
                                    171 ;	-----------------------------------------
      008104                        172 _TIM3_UPD_OVF_BRK_IRQHandler:
                                    173 ;	./src/stm8s_it.c: 301: }
      008104 80               [11]  174 	iret
                                    175 ;	./src/stm8s_it.c: 308: INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
                                    176 ;	-----------------------------------------
                                    177 ;	 function TIM3_CAP_COM_IRQHandler
                                    178 ;	-----------------------------------------
      008105                        179 _TIM3_CAP_COM_IRQHandler:
                                    180 ;	./src/stm8s_it.c: 313: }
      008105 80               [11]  181 	iret
                                    182 ;	./src/stm8s_it.c: 348: INTERRUPT_HANDLER(I2C_IRQHandler, 19)
                                    183 ;	-----------------------------------------
                                    184 ;	 function I2C_IRQHandler
                                    185 ;	-----------------------------------------
      008106                        186 _I2C_IRQHandler:
                                    187 ;	./src/stm8s_it.c: 353: }
      008106 80               [11]  188 	iret
                                    189 ;	./src/stm8s_it.c: 361: INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
                                    190 ;	-----------------------------------------
                                    191 ;	 function UART2_TX_IRQHandler
                                    192 ;	-----------------------------------------
      008107                        193 _UART2_TX_IRQHandler:
                                    194 ;	./src/stm8s_it.c: 366: }
      008107 80               [11]  195 	iret
                                    196 ;	./src/stm8s_it.c: 373: INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
                                    197 ;	-----------------------------------------
                                    198 ;	 function UART2_RX_IRQHandler
                                    199 ;	-----------------------------------------
      008108                        200 _UART2_RX_IRQHandler:
                                    201 ;	./src/stm8s_it.c: 378: }
      008108 80               [11]  202 	iret
                                    203 ;	./src/stm8s_it.c: 428: INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
                                    204 ;	-----------------------------------------
                                    205 ;	 function ADC1_IRQHandler
                                    206 ;	-----------------------------------------
      008109                        207 _ADC1_IRQHandler:
                                    208 ;	./src/stm8s_it.c: 434: return;
                                    209 ;	./src/stm8s_it.c: 436: }
      008109 80               [11]  210 	iret
                                    211 ;	./src/stm8s_it.c: 457: INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
                                    212 ;	-----------------------------------------
                                    213 ;	 function TIM4_UPD_OVF_IRQHandler
                                    214 ;	-----------------------------------------
      00810A                        215 _TIM4_UPD_OVF_IRQHandler:
                                    216 ;	./src/stm8s_it.c: 462: }
      00810A 80               [11]  217 	iret
                                    218 ;	./src/stm8s_it.c: 470: INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
                                    219 ;	-----------------------------------------
                                    220 ;	 function EEPROM_EEC_IRQHandler
                                    221 ;	-----------------------------------------
      00810B                        222 _EEPROM_EEC_IRQHandler:
                                    223 ;	./src/stm8s_it.c: 475: }
      00810B 80               [11]  224 	iret
                                    225 	.area CODE
                                    226 	.area CONST
                                    227 	.area INITIALIZER
                                    228 	.area CABS (ABS)
