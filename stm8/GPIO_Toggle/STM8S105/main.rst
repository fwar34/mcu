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
                                     11 	.globl _main
                                     12 	.globl _GPIO_WriteReverse
                                     13 	.globl _GPIO_Init
                                     14 	.globl _Delay
                                     15 	.globl _assert_failed
                                     16 ;--------------------------------------------------------
                                     17 ; ram data
                                     18 ;--------------------------------------------------------
                                     19 	.area DATA
                                     20 ;--------------------------------------------------------
                                     21 ; ram data
                                     22 ;--------------------------------------------------------
                                     23 	.area INITIALIZED
                                     24 ;--------------------------------------------------------
                                     25 ; Stack segment in internal ram 
                                     26 ;--------------------------------------------------------
                                     27 	.area	SSEG
      FFFFFF                         28 __start__stack:
      FFFFFF                         29 	.ds	1
                                     30 
                                     31 ;--------------------------------------------------------
                                     32 ; absolute external ram data
                                     33 ;--------------------------------------------------------
                                     34 	.area DABS (ABS)
                                     35 
                                     36 ; default segment ordering for linker
                                     37 	.area HOME
                                     38 	.area GSINIT
                                     39 	.area GSFINAL
                                     40 	.area CONST
                                     41 	.area INITIALIZER
                                     42 	.area CODE
                                     43 
                                     44 ;--------------------------------------------------------
                                     45 ; interrupt vector 
                                     46 ;--------------------------------------------------------
                                     47 	.area HOME
      008000                         48 __interrupt_vect:
      008000 82 00 80 6F             49 	int s_GSINIT ; reset
      008004 82 00 80 F6             50 	int _TRAP_IRQHandler ; trap
      008008 82 00 80 F7             51 	int _TLI_IRQHandler ; int0
      00800C 82 00 80 F8             52 	int _AWU_IRQHandler ; int1
      008010 82 00 80 F9             53 	int _CLK_IRQHandler ; int2
      008014 82 00 80 FA             54 	int _EXTI_PORTA_IRQHandler ; int3
      008018 82 00 80 FB             55 	int _EXTI_PORTB_IRQHandler ; int4
      00801C 82 00 80 FC             56 	int _EXTI_PORTC_IRQHandler ; int5
      008020 82 00 80 FD             57 	int _EXTI_PORTD_IRQHandler ; int6
      008024 82 00 80 FE             58 	int _EXTI_PORTE_IRQHandler ; int7
      008028 82 00 00 00             59 	int 0x000000 ; int8
      00802C 82 00 00 00             60 	int 0x000000 ; int9
      008030 82 00 80 FF             61 	int _SPI_IRQHandler ; int10
      008034 82 00 81 00             62 	int _TIM1_UPD_OVF_TRG_BRK_IRQHandler ; int11
      008038 82 00 81 01             63 	int _TIM1_CAP_COM_IRQHandler ; int12
      00803C 82 00 81 02             64 	int _TIM2_UPD_OVF_BRK_IRQHandler ; int13
      008040 82 00 81 03             65 	int _TIM2_CAP_COM_IRQHandler ; int14
      008044 82 00 81 04             66 	int _TIM3_UPD_OVF_BRK_IRQHandler ; int15
      008048 82 00 81 05             67 	int _TIM3_CAP_COM_IRQHandler ; int16
      00804C 82 00 00 00             68 	int 0x000000 ; int17
      008050 82 00 00 00             69 	int 0x000000 ; int18
      008054 82 00 81 06             70 	int _I2C_IRQHandler ; int19
      008058 82 00 81 07             71 	int _UART2_TX_IRQHandler ; int20
      00805C 82 00 81 08             72 	int _UART2_RX_IRQHandler ; int21
      008060 82 00 81 09             73 	int _ADC1_IRQHandler ; int22
      008064 82 00 81 0A             74 	int _TIM4_UPD_OVF_IRQHandler ; int23
      008068 82 00 81 0B             75 	int _EEPROM_EEC_IRQHandler ; int24
                                     76 ;--------------------------------------------------------
                                     77 ; global & static initialisations
                                     78 ;--------------------------------------------------------
                                     79 	.area HOME
                                     80 	.area GSINIT
                                     81 	.area GSFINAL
                                     82 	.area GSINIT
      00806F                         83 __sdcc_gs_init_startup:
      00806F                         84 __sdcc_init_data:
                                     85 ; stm8_genXINIT() start
      00806F AE 00 00         [ 2]   86 	ldw x, #l_DATA
      008072 27 07            [ 1]   87 	jreq	00002$
      008074                         88 00001$:
      008074 72 4F 00 00      [ 1]   89 	clr (s_DATA - 1, x)
      008078 5A               [ 2]   90 	decw x
      008079 26 F9            [ 1]   91 	jrne	00001$
      00807B                         92 00002$:
      00807B AE 00 00         [ 2]   93 	ldw	x, #l_INITIALIZER
      00807E 27 09            [ 1]   94 	jreq	00004$
      008080                         95 00003$:
      008080 D6 80 F5         [ 1]   96 	ld	a, (s_INITIALIZER - 1, x)
      008083 D7 00 00         [ 1]   97 	ld	(s_INITIALIZED - 1, x), a
      008086 5A               [ 2]   98 	decw	x
      008087 26 F7            [ 1]   99 	jrne	00003$
      008089                        100 00004$:
                                    101 ; stm8_genXINIT() end
                                    102 	.area GSFINAL
      008089 CC 80 6C         [ 2]  103 	jp	__sdcc_program_startup
                                    104 ;--------------------------------------------------------
                                    105 ; Home
                                    106 ;--------------------------------------------------------
                                    107 	.area HOME
                                    108 	.area HOME
      00806C                        109 __sdcc_program_startup:
      00806C CC 81 0C         [ 2]  110 	jp	_main
                                    111 ;	return from main will return to caller
                                    112 ;--------------------------------------------------------
                                    113 ; code
                                    114 ;--------------------------------------------------------
                                    115 	.area CODE
                                    116 ;	./src/main.c: 57: void main(void)
                                    117 ;	-----------------------------------------
                                    118 ;	 function main
                                    119 ;	-----------------------------------------
      00810C                        120 _main:
                                    121 ;	./src/main.c: 61: GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
      00810C 4B E0            [ 1]  122 	push	#0xe0
      00810E 4B 0F            [ 1]  123 	push	#0x0f
      008110 4B 00            [ 1]  124 	push	#0x00
      008112 4B 50            [ 1]  125 	push	#0x50
      008114 CD 81 4B         [ 4]  126 	call	_GPIO_Init
      008117 5B 04            [ 2]  127 	addw	sp, #4
                                    128 ;	./src/main.c: 63: while (1)
      008119                        129 00102$:
                                    130 ;	./src/main.c: 66: GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
      008119 4B 0F            [ 1]  131 	push	#0x0f
      00811B 4B 00            [ 1]  132 	push	#0x00
      00811D 4B 50            [ 1]  133 	push	#0x50
      00811F CD 82 43         [ 4]  134 	call	_GPIO_WriteReverse
      008122 5B 03            [ 2]  135 	addw	sp, #3
                                    136 ;	./src/main.c: 67: Delay(0xFFFF);
      008124 4B FF            [ 1]  137 	push	#0xff
      008126 4B FF            [ 1]  138 	push	#0xff
      008128 CD 81 2F         [ 4]  139 	call	_Delay
      00812B 85               [ 2]  140 	popw	x
      00812C 20 EB            [ 2]  141 	jra	00102$
                                    142 ;	./src/main.c: 70: }
      00812E 81               [ 4]  143 	ret
                                    144 ;	./src/main.c: 77: void Delay(uint16_t nCount)
                                    145 ;	-----------------------------------------
                                    146 ;	 function Delay
                                    147 ;	-----------------------------------------
      00812F                        148 _Delay:
                                    149 ;	./src/main.c: 80: while (nCount != 0)
      00812F 1E 03            [ 2]  150 	ldw	x, (0x03, sp)
      008131                        151 00101$:
      008131 5D               [ 2]  152 	tnzw	x
      008132 26 01            [ 1]  153 	jrne	00117$
      008134 81               [ 4]  154 	ret
      008135                        155 00117$:
                                    156 ;	./src/main.c: 82: nCount--;
      008135 5A               [ 2]  157 	decw	x
      008136 20 F9            [ 2]  158 	jra	00101$
                                    159 ;	./src/main.c: 84: }
      008138 81               [ 4]  160 	ret
                                    161 ;	./src/main.c: 95: void assert_failed(uint8_t* file, uint32_t line)
                                    162 ;	-----------------------------------------
                                    163 ;	 function assert_failed
                                    164 ;	-----------------------------------------
      008139                        165 _assert_failed:
                                    166 ;	./src/main.c: 102: while (1)
      008139                        167 00102$:
      008139 20 FE            [ 2]  168 	jra	00102$
                                    169 ;	./src/main.c: 105: }
      00813B 81               [ 4]  170 	ret
                                    171 	.area CODE
                                    172 	.area CONST
                                    173 	.area INITIALIZER
                                    174 	.area CABS (ABS)
