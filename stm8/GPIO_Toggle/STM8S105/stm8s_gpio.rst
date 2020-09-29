                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module stm8s_gpio
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _assert_failed
                                     12 	.globl _GPIO_DeInit
                                     13 	.globl _GPIO_Init
                                     14 	.globl _GPIO_Write
                                     15 	.globl _GPIO_WriteHigh
                                     16 	.globl _GPIO_WriteLow
                                     17 	.globl _GPIO_WriteReverse
                                     18 	.globl _GPIO_ReadOutputData
                                     19 	.globl _GPIO_ReadInputData
                                     20 	.globl _GPIO_ReadInputPin
                                     21 	.globl _GPIO_ExternalPullUpConfig
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area DATA
                                     26 ;--------------------------------------------------------
                                     27 ; ram data
                                     28 ;--------------------------------------------------------
                                     29 	.area INITIALIZED
                                     30 ;--------------------------------------------------------
                                     31 ; absolute external ram data
                                     32 ;--------------------------------------------------------
                                     33 	.area DABS (ABS)
                                     34 
                                     35 ; default segment ordering for linker
                                     36 	.area HOME
                                     37 	.area GSINIT
                                     38 	.area GSFINAL
                                     39 	.area CONST
                                     40 	.area INITIALIZER
                                     41 	.area CODE
                                     42 
                                     43 ;--------------------------------------------------------
                                     44 ; global & static initialisations
                                     45 ;--------------------------------------------------------
                                     46 	.area HOME
                                     47 	.area GSINIT
                                     48 	.area GSFINAL
                                     49 	.area GSINIT
                                     50 ;--------------------------------------------------------
                                     51 ; Home
                                     52 ;--------------------------------------------------------
                                     53 	.area HOME
                                     54 	.area HOME
                                     55 ;--------------------------------------------------------
                                     56 ; code
                                     57 ;--------------------------------------------------------
                                     58 	.area CODE
                                     59 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 53: void GPIO_DeInit(GPIO_TypeDef* GPIOx)
                                     60 ;	-----------------------------------------
                                     61 ;	 function GPIO_DeInit
                                     62 ;	-----------------------------------------
      00813C                         63 _GPIO_DeInit:
                                     64 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 55: GPIOx->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
      00813C 16 03            [ 2]   65 	ldw	y, (0x03, sp)
      00813E 90 7F            [ 1]   66 	clr	(y)
                                     67 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 56: GPIOx->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
      008140 93               [ 1]   68 	ldw	x, y
      008141 5C               [ 1]   69 	incw	x
      008142 5C               [ 1]   70 	incw	x
      008143 7F               [ 1]   71 	clr	(x)
                                     72 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 57: GPIOx->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
      008144 93               [ 1]   73 	ldw	x, y
      008145 6F 03            [ 1]   74 	clr	(0x0003, x)
                                     75 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 58: GPIOx->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
      008147 93               [ 1]   76 	ldw	x, y
      008148 6F 04            [ 1]   77 	clr	(0x0004, x)
                                     78 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 59: }
      00814A 81               [ 4]   79 	ret
                                     80 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 71: void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)
                                     81 ;	-----------------------------------------
                                     82 ;	 function GPIO_Init
                                     83 ;	-----------------------------------------
      00814B                         84 _GPIO_Init:
      00814B 52 05            [ 2]   85 	sub	sp, #5
                                     86 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 77: assert_param(IS_GPIO_MODE_OK(GPIO_Mode));
      00814D 0D 0B            [ 1]   87 	tnz	(0x0b, sp)
      00814F 27 51            [ 1]   88 	jreq	00116$
      008151 7B 0B            [ 1]   89 	ld	a, (0x0b, sp)
      008153 A1 40            [ 1]   90 	cp	a, #0x40
      008155 27 4B            [ 1]   91 	jreq	00116$
      008157 7B 0B            [ 1]   92 	ld	a, (0x0b, sp)
      008159 A1 20            [ 1]   93 	cp	a, #0x20
      00815B 27 45            [ 1]   94 	jreq	00116$
      00815D 7B 0B            [ 1]   95 	ld	a, (0x0b, sp)
      00815F A1 60            [ 1]   96 	cp	a, #0x60
      008161 27 3F            [ 1]   97 	jreq	00116$
      008163 7B 0B            [ 1]   98 	ld	a, (0x0b, sp)
      008165 A1 A0            [ 1]   99 	cp	a, #0xa0
      008167 27 39            [ 1]  100 	jreq	00116$
      008169 7B 0B            [ 1]  101 	ld	a, (0x0b, sp)
      00816B A1 E0            [ 1]  102 	cp	a, #0xe0
      00816D 27 33            [ 1]  103 	jreq	00116$
      00816F 7B 0B            [ 1]  104 	ld	a, (0x0b, sp)
      008171 A1 80            [ 1]  105 	cp	a, #0x80
      008173 27 2D            [ 1]  106 	jreq	00116$
      008175 7B 0B            [ 1]  107 	ld	a, (0x0b, sp)
      008177 A1 C0            [ 1]  108 	cp	a, #0xc0
      008179 27 27            [ 1]  109 	jreq	00116$
      00817B 7B 0B            [ 1]  110 	ld	a, (0x0b, sp)
      00817D A1 B0            [ 1]  111 	cp	a, #0xb0
      00817F 27 21            [ 1]  112 	jreq	00116$
      008181 7B 0B            [ 1]  113 	ld	a, (0x0b, sp)
      008183 A1 F0            [ 1]  114 	cp	a, #0xf0
      008185 27 1B            [ 1]  115 	jreq	00116$
      008187 7B 0B            [ 1]  116 	ld	a, (0x0b, sp)
      008189 A1 90            [ 1]  117 	cp	a, #0x90
      00818B 27 15            [ 1]  118 	jreq	00116$
      00818D 7B 0B            [ 1]  119 	ld	a, (0x0b, sp)
      00818F A1 D0            [ 1]  120 	cp	a, #0xd0
      008191 27 0F            [ 1]  121 	jreq	00116$
      008193 4B 4D            [ 1]  122 	push	#0x4d
      008195 5F               [ 1]  123 	clrw	x
      008196 89               [ 2]  124 	pushw	x
      008197 4B 00            [ 1]  125 	push	#0x00
      008199 4B 8C            [ 1]  126 	push	#<(___str_0 + 0)
      00819B 4B 80            [ 1]  127 	push	#((___str_0 + 0) >> 8)
      00819D CD 81 39         [ 4]  128 	call	_assert_failed
      0081A0 5B 06            [ 2]  129 	addw	sp, #6
      0081A2                        130 00116$:
                                    131 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 78: assert_param(IS_GPIO_PIN_OK(GPIO_Pin));
      0081A2 0D 0A            [ 1]  132 	tnz	(0x0a, sp)
      0081A4 26 0F            [ 1]  133 	jrne	00151$
      0081A6 4B 4E            [ 1]  134 	push	#0x4e
      0081A8 5F               [ 1]  135 	clrw	x
      0081A9 89               [ 2]  136 	pushw	x
      0081AA 4B 00            [ 1]  137 	push	#0x00
      0081AC 4B 8C            [ 1]  138 	push	#<(___str_0 + 0)
      0081AE 4B 80            [ 1]  139 	push	#((___str_0 + 0) >> 8)
      0081B0 CD 81 39         [ 4]  140 	call	_assert_failed
      0081B3 5B 06            [ 2]  141 	addw	sp, #6
      0081B5                        142 00151$:
                                    143 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 81: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      0081B5 16 08            [ 2]  144 	ldw	y, (0x08, sp)
      0081B7 93               [ 1]  145 	ldw	x, y
      0081B8 1C 00 04         [ 2]  146 	addw	x, #0x0004
      0081BB 1F 01            [ 2]  147 	ldw	(0x01, sp), x
      0081BD F6               [ 1]  148 	ld	a, (x)
      0081BE 88               [ 1]  149 	push	a
      0081BF 7B 0B            [ 1]  150 	ld	a, (0x0b, sp)
      0081C1 43               [ 1]  151 	cpl	a
      0081C2 6B 04            [ 1]  152 	ld	(0x04, sp), a
      0081C4 84               [ 1]  153 	pop	a
      0081C5 14 03            [ 1]  154 	and	a, (0x03, sp)
      0081C7 1E 01            [ 2]  155 	ldw	x, (0x01, sp)
      0081C9 F7               [ 1]  156 	ld	(x), a
                                    157 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      0081CA 93               [ 1]  158 	ldw	x, y
      0081CB 5C               [ 1]  159 	incw	x
      0081CC 5C               [ 1]  160 	incw	x
      0081CD 1F 04            [ 2]  161 	ldw	(0x04, sp), x
                                    162 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 87: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) != (uint8_t)0x00) /* Output mode */
      0081CF 0D 0B            [ 1]  163 	tnz	(0x0b, sp)
      0081D1 2A 1E            [ 1]  164 	jrpl	00105$
                                    165 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      0081D3 90 F6            [ 1]  166 	ld	a, (y)
                                    167 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 89: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) != (uint8_t)0x00) /* High level */
      0081D5 88               [ 1]  168 	push	a
      0081D6 7B 0C            [ 1]  169 	ld	a, (0x0c, sp)
      0081D8 A5 10            [ 1]  170 	bcp	a, #0x10
      0081DA 84               [ 1]  171 	pop	a
      0081DB 27 06            [ 1]  172 	jreq	00102$
                                    173 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      0081DD 1A 0A            [ 1]  174 	or	a, (0x0a, sp)
      0081DF 90 F7            [ 1]  175 	ld	(y), a
      0081E1 20 04            [ 2]  176 	jra	00103$
      0081E3                        177 00102$:
                                    178 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 95: GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
      0081E3 14 03            [ 1]  179 	and	a, (0x03, sp)
      0081E5 90 F7            [ 1]  180 	ld	(y), a
      0081E7                        181 00103$:
                                    182 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      0081E7 1E 04            [ 2]  183 	ldw	x, (0x04, sp)
      0081E9 F6               [ 1]  184 	ld	a, (x)
      0081EA 1A 0A            [ 1]  185 	or	a, (0x0a, sp)
      0081EC 1E 04            [ 2]  186 	ldw	x, (0x04, sp)
      0081EE F7               [ 1]  187 	ld	(x), a
      0081EF 20 08            [ 2]  188 	jra	00106$
      0081F1                        189 00105$:
                                    190 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 103: GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
      0081F1 1E 04            [ 2]  191 	ldw	x, (0x04, sp)
      0081F3 F6               [ 1]  192 	ld	a, (x)
      0081F4 14 03            [ 1]  193 	and	a, (0x03, sp)
      0081F6 1E 04            [ 2]  194 	ldw	x, (0x04, sp)
      0081F8 F7               [ 1]  195 	ld	(x), a
      0081F9                        196 00106$:
                                    197 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      0081F9 93               [ 1]  198 	ldw	x, y
      0081FA 1C 00 03         [ 2]  199 	addw	x, #0x0003
      0081FD F6               [ 1]  200 	ld	a, (x)
                                    201 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 110: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) != (uint8_t)0x00) /* Pull-Up or Push-Pull */
      0081FE 88               [ 1]  202 	push	a
      0081FF 7B 0C            [ 1]  203 	ld	a, (0x0c, sp)
      008201 A5 40            [ 1]  204 	bcp	a, #0x40
      008203 84               [ 1]  205 	pop	a
      008204 27 05            [ 1]  206 	jreq	00108$
                                    207 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008206 1A 0A            [ 1]  208 	or	a, (0x0a, sp)
      008208 F7               [ 1]  209 	ld	(x), a
      008209 20 03            [ 2]  210 	jra	00109$
      00820B                        211 00108$:
                                    212 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 116: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      00820B 14 03            [ 1]  213 	and	a, (0x03, sp)
      00820D F7               [ 1]  214 	ld	(x), a
      00820E                        215 00109$:
                                    216 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 81: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      00820E 1E 01            [ 2]  217 	ldw	x, (0x01, sp)
      008210 F6               [ 1]  218 	ld	a, (x)
                                    219 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 123: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) != (uint8_t)0x00) /* Interrupt or Slow slope */
      008211 88               [ 1]  220 	push	a
      008212 7B 0C            [ 1]  221 	ld	a, (0x0c, sp)
      008214 A5 20            [ 1]  222 	bcp	a, #0x20
      008216 84               [ 1]  223 	pop	a
      008217 27 07            [ 1]  224 	jreq	00111$
                                    225 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 125: GPIOx->CR2 |= (uint8_t)GPIO_Pin;
      008219 1A 0A            [ 1]  226 	or	a, (0x0a, sp)
      00821B 1E 01            [ 2]  227 	ldw	x, (0x01, sp)
      00821D F7               [ 1]  228 	ld	(x), a
      00821E 20 05            [ 2]  229 	jra	00113$
      008220                        230 00111$:
                                    231 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 129: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      008220 14 03            [ 1]  232 	and	a, (0x03, sp)
      008222 1E 01            [ 2]  233 	ldw	x, (0x01, sp)
      008224 F7               [ 1]  234 	ld	(x), a
      008225                        235 00113$:
                                    236 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 131: }
      008225 5B 05            [ 2]  237 	addw	sp, #5
      008227 81               [ 4]  238 	ret
                                    239 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 141: void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t PortVal)
                                    240 ;	-----------------------------------------
                                    241 ;	 function GPIO_Write
                                    242 ;	-----------------------------------------
      008228                        243 _GPIO_Write:
                                    244 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 143: GPIOx->ODR = PortVal;
      008228 1E 03            [ 2]  245 	ldw	x, (0x03, sp)
      00822A 7B 05            [ 1]  246 	ld	a, (0x05, sp)
      00822C F7               [ 1]  247 	ld	(x), a
                                    248 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 144: }
      00822D 81               [ 4]  249 	ret
                                    250 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 154: void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    251 ;	-----------------------------------------
                                    252 ;	 function GPIO_WriteHigh
                                    253 ;	-----------------------------------------
      00822E                        254 _GPIO_WriteHigh:
                                    255 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 156: GPIOx->ODR |= (uint8_t)PortPins;
      00822E 1E 03            [ 2]  256 	ldw	x, (0x03, sp)
      008230 F6               [ 1]  257 	ld	a, (x)
      008231 1A 05            [ 1]  258 	or	a, (0x05, sp)
      008233 F7               [ 1]  259 	ld	(x), a
                                    260 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 157: }
      008234 81               [ 4]  261 	ret
                                    262 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 167: void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    263 ;	-----------------------------------------
                                    264 ;	 function GPIO_WriteLow
                                    265 ;	-----------------------------------------
      008235                        266 _GPIO_WriteLow:
      008235 88               [ 1]  267 	push	a
                                    268 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 169: GPIOx->ODR &= (uint8_t)(~PortPins);
      008236 1E 04            [ 2]  269 	ldw	x, (0x04, sp)
      008238 F6               [ 1]  270 	ld	a, (x)
      008239 6B 01            [ 1]  271 	ld	(0x01, sp), a
      00823B 7B 06            [ 1]  272 	ld	a, (0x06, sp)
      00823D 43               [ 1]  273 	cpl	a
      00823E 14 01            [ 1]  274 	and	a, (0x01, sp)
      008240 F7               [ 1]  275 	ld	(x), a
                                    276 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 170: }
      008241 84               [ 1]  277 	pop	a
      008242 81               [ 4]  278 	ret
                                    279 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 180: void GPIO_WriteReverse(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    280 ;	-----------------------------------------
                                    281 ;	 function GPIO_WriteReverse
                                    282 ;	-----------------------------------------
      008243                        283 _GPIO_WriteReverse:
                                    284 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 182: GPIOx->ODR ^= (uint8_t)PortPins;
      008243 1E 03            [ 2]  285 	ldw	x, (0x03, sp)
      008245 F6               [ 1]  286 	ld	a, (x)
      008246 18 05            [ 1]  287 	xor	a, (0x05, sp)
      008248 F7               [ 1]  288 	ld	(x), a
                                    289 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 183: }
      008249 81               [ 4]  290 	ret
                                    291 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 191: uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
                                    292 ;	-----------------------------------------
                                    293 ;	 function GPIO_ReadOutputData
                                    294 ;	-----------------------------------------
      00824A                        295 _GPIO_ReadOutputData:
                                    296 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 193: return ((uint8_t)GPIOx->ODR);
      00824A 1E 03            [ 2]  297 	ldw	x, (0x03, sp)
      00824C F6               [ 1]  298 	ld	a, (x)
                                    299 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 194: }
      00824D 81               [ 4]  300 	ret
                                    301 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 202: uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
                                    302 ;	-----------------------------------------
                                    303 ;	 function GPIO_ReadInputData
                                    304 ;	-----------------------------------------
      00824E                        305 _GPIO_ReadInputData:
                                    306 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 204: return ((uint8_t)GPIOx->IDR);
      00824E 1E 03            [ 2]  307 	ldw	x, (0x03, sp)
      008250 E6 01            [ 1]  308 	ld	a, (0x1, x)
                                    309 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 205: }
      008252 81               [ 4]  310 	ret
                                    311 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 213: BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
                                    312 ;	-----------------------------------------
                                    313 ;	 function GPIO_ReadInputPin
                                    314 ;	-----------------------------------------
      008253                        315 _GPIO_ReadInputPin:
                                    316 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 215: return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
      008253 1E 03            [ 2]  317 	ldw	x, (0x03, sp)
      008255 E6 01            [ 1]  318 	ld	a, (0x1, x)
      008257 14 05            [ 1]  319 	and	a, (0x05, sp)
                                    320 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 216: }
      008259 81               [ 4]  321 	ret
                                    322 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 225: void GPIO_ExternalPullUpConfig(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState)
                                    323 ;	-----------------------------------------
                                    324 ;	 function GPIO_ExternalPullUpConfig
                                    325 ;	-----------------------------------------
      00825A                        326 _GPIO_ExternalPullUpConfig:
      00825A 88               [ 1]  327 	push	a
                                    328 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 228: assert_param(IS_GPIO_PIN_OK(GPIO_Pin));
      00825B 0D 06            [ 1]  329 	tnz	(0x06, sp)
      00825D 26 0F            [ 1]  330 	jrne	00107$
      00825F 4B E4            [ 1]  331 	push	#0xe4
      008261 5F               [ 1]  332 	clrw	x
      008262 89               [ 2]  333 	pushw	x
      008263 4B 00            [ 1]  334 	push	#0x00
      008265 4B 8C            [ 1]  335 	push	#<(___str_0 + 0)
      008267 4B 80            [ 1]  336 	push	#((___str_0 + 0) >> 8)
      008269 CD 81 39         [ 4]  337 	call	_assert_failed
      00826C 5B 06            [ 2]  338 	addw	sp, #6
      00826E                        339 00107$:
                                    340 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 229: assert_param(IS_FUNCTIONALSTATE_OK(NewState));
      00826E 0D 07            [ 1]  341 	tnz	(0x07, sp)
      008270 27 14            [ 1]  342 	jreq	00109$
      008272 7B 07            [ 1]  343 	ld	a, (0x07, sp)
      008274 4A               [ 1]  344 	dec	a
      008275 27 0F            [ 1]  345 	jreq	00109$
      008277 4B E5            [ 1]  346 	push	#0xe5
      008279 5F               [ 1]  347 	clrw	x
      00827A 89               [ 2]  348 	pushw	x
      00827B 4B 00            [ 1]  349 	push	#0x00
      00827D 4B 8C            [ 1]  350 	push	#<(___str_0 + 0)
      00827F 4B 80            [ 1]  351 	push	#((___str_0 + 0) >> 8)
      008281 CD 81 39         [ 4]  352 	call	_assert_failed
      008284 5B 06            [ 2]  353 	addw	sp, #6
      008286                        354 00109$:
                                    355 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008286 1E 04            [ 2]  356 	ldw	x, (0x04, sp)
      008288 1C 00 03         [ 2]  357 	addw	x, #0x0003
      00828B F6               [ 1]  358 	ld	a, (x)
                                    359 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 231: if (NewState != DISABLE) /* External Pull-Up Set*/
      00828C 0D 07            [ 1]  360 	tnz	(0x07, sp)
      00828E 27 05            [ 1]  361 	jreq	00102$
                                    362 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008290 1A 06            [ 1]  363 	or	a, (0x06, sp)
      008292 F7               [ 1]  364 	ld	(x), a
      008293 20 0A            [ 2]  365 	jra	00104$
      008295                        366 00102$:
                                    367 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 236: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      008295 88               [ 1]  368 	push	a
      008296 7B 07            [ 1]  369 	ld	a, (0x07, sp)
      008298 43               [ 1]  370 	cpl	a
      008299 6B 02            [ 1]  371 	ld	(0x02, sp), a
      00829B 84               [ 1]  372 	pop	a
      00829C 14 01            [ 1]  373 	and	a, (0x01, sp)
      00829E F7               [ 1]  374 	ld	(x), a
      00829F                        375 00104$:
                                    376 ;	/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 238: }
      00829F 84               [ 1]  377 	pop	a
      0082A0 81               [ 4]  378 	ret
                                    379 	.area CODE
                                    380 	.area CONST
                                    381 	.area CONST
      00808C                        382 ___str_0:
      00808C 2F 68 6F 6D 65 2F 66   383 	.ascii "/home/feng/mine/mcu/stm8/framework-ststm8spl-platformio/Libr"
             65 6E 67 2F 6D 69 6E
             65 2F 6D 63 75 2F 73
             74 6D 38 2F 66 72 61
             6D 65 77 6F 72 6B 2D
             73 74 73 74 6D 38 73
             70 6C 2D 70 6C 61 74
             66 6F 72 6D 69 6F 2F
             4C 69 62 72
      0080C8 61 72 69 65 73 2F 53   384 	.ascii "aries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c"
             54 4D 38 53 5F 53 74
             64 50 65 72 69 70 68
             5F 44 72 69 76 65 72
             2F 73 72 63 2F 73 74
             6D 38 73 5F 67 70 69
             6F 2E 63
      0080F5 00                     385 	.db 0x00
                                    386 	.area CODE
                                    387 	.area INITIALIZER
                                    388 	.area CABS (ABS)
