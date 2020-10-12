                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module OSAL_ClockBLE
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _osalTimerUpdate
                                     12 	.globl _OSAL_timeSeconds
                                     13 	.globl _osalTimeUpdate
                                     14 	.globl _osal_setClock
                                     15 	.globl _osal_getClock
                                     16 	.globl _osal_ConvertUTCTime
                                     17 	.globl _osal_ConvertUTCSecs
                                     18 ;--------------------------------------------------------
                                     19 ; ram data
                                     20 ;--------------------------------------------------------
                                     21 	.area DATA
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area INITIALIZED
      00040F                         26 _timeMSec:
      00040F                         27 	.ds 2
      000411                         28 _OSAL_timeSeconds::
      000411                         29 	.ds 4
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
                                     59 ;	./src/OSAL_ClockBLE.c: 59: void osalTimeUpdate( void )
                                     60 ;	-----------------------------------------
                                     61 ;	 function osalTimeUpdate
                                     62 ;	-----------------------------------------
      008926                         63 _osalTimeUpdate:
                                     64 ;	./src/OSAL_ClockBLE.c: 61: osalTimerUpdate( 1 );
      008926 4B 01            [ 1]   65 	push	#0x01
      008928 5F               [ 1]   66 	clrw	x
      008929 89               [ 2]   67 	pushw	x
      00892A 4B 00            [ 1]   68 	push	#0x00
      00892C CD 87 4C         [ 4]   69 	call	_osalTimerUpdate
      00892F 5B 04            [ 2]   70 	addw	sp, #4
                                     71 ;	./src/OSAL_ClockBLE.c: 62: osalClockUpdate( 1 );
      008931 4B 01            [ 1]   72 	push	#0x01
      008933 4B 00            [ 1]   73 	push	#0x00
      008935 CD 89 3A         [ 4]   74 	call	_osalClockUpdate
      008938 85               [ 2]   75 	popw	x
                                     76 ;	./src/OSAL_ClockBLE.c: 63: }
      008939 81               [ 4]   77 	ret
                                     78 ;	./src/OSAL_ClockBLE.c: 74: static void osalClockUpdate( uint16 elapsedMSec )
                                     79 ;	-----------------------------------------
                                     80 ;	 function osalClockUpdate
                                     81 ;	-----------------------------------------
      00893A                         82 _osalClockUpdate:
      00893A 52 08            [ 2]   83 	sub	sp, #8
                                     84 ;	./src/OSAL_ClockBLE.c: 77: timeMSec += elapsedMSec;
      00893C CE 04 0F         [ 2]   85 	ldw	x, _timeMSec+0
      00893F 72 FB 0B         [ 2]   86 	addw	x, (0x0b, sp)
      008942 CF 04 0F         [ 2]   87 	ldw	_timeMSec+0, x
                                     88 ;	./src/OSAL_ClockBLE.c: 80: if ( timeMSec >= 1000 )
      008945 90 CE 04 0F      [ 2]   89 	ldw	y, _timeMSec+0
      008949 90 A3 03 E8      [ 2]   90 	cpw	y, #0x03e8
      00894D 25 2F            [ 1]   91 	jrc	00103$
                                     92 ;	./src/OSAL_ClockBLE.c: 82: OSAL_timeSeconds += timeMSec / 1000;
      00894F 90 89            [ 2]   93 	pushw	y
      008951 93               [ 1]   94 	ldw	x, y
      008952 90 AE 03 E8      [ 2]   95 	ldw	y, #0x03e8
      008956 65               [ 2]   96 	divw	x, y
      008957 90 85            [ 2]   97 	popw	y
      008959 4F               [ 1]   98 	clr	a
      00895A 0F 01            [ 1]   99 	clr	(0x01, sp)
      00895C 72 BB 04 13      [ 2]  100 	addw	x, _OSAL_timeSeconds+2
      008960 C9 04 12         [ 1]  101 	adc	a, _OSAL_timeSeconds+1
      008963 6B 06            [ 1]  102 	ld	(0x06, sp), a
      008965 7B 01            [ 1]  103 	ld	a, (0x01, sp)
      008967 C9 04 11         [ 1]  104 	adc	a, _OSAL_timeSeconds+0
      00896A 6B 05            [ 1]  105 	ld	(0x05, sp), a
      00896C CF 04 13         [ 2]  106 	ldw	_OSAL_timeSeconds+2, x
      00896F 1E 05            [ 2]  107 	ldw	x, (0x05, sp)
      008971 CF 04 11         [ 2]  108 	ldw	_OSAL_timeSeconds+0, x
                                    109 ;	./src/OSAL_ClockBLE.c: 83: timeMSec = timeMSec % 1000;
      008974 93               [ 1]  110 	ldw	x, y
      008975 90 AE 03 E8      [ 2]  111 	ldw	y, #0x03e8
      008979 65               [ 2]  112 	divw	x, y
      00897A 90 CF 04 0F      [ 2]  113 	ldw	_timeMSec+0, y
      00897E                        114 00103$:
                                    115 ;	./src/OSAL_ClockBLE.c: 85: }
      00897E 5B 08            [ 2]  116 	addw	sp, #8
      008980 81               [ 4]  117 	ret
                                    118 ;	./src/OSAL_ClockBLE.c: 98: void osal_setClock( UTCTime newTime )
                                    119 ;	-----------------------------------------
                                    120 ;	 function osal_setClock
                                    121 ;	-----------------------------------------
      008981                        122 _osal_setClock:
                                    123 ;	./src/OSAL_ClockBLE.c: 100: OSAL_timeSeconds = newTime;
      008981 1E 05            [ 2]  124 	ldw	x, (0x05, sp)
      008983 16 03            [ 2]  125 	ldw	y, (0x03, sp)
      008985 CF 04 13         [ 2]  126 	ldw	_OSAL_timeSeconds+2, x
      008988 90 CF 04 11      [ 2]  127 	ldw	_OSAL_timeSeconds+0, y
                                    128 ;	./src/OSAL_ClockBLE.c: 101: }
      00898C 81               [ 4]  129 	ret
                                    130 ;	./src/OSAL_ClockBLE.c: 115: UTCTime osal_getClock( void )
                                    131 ;	-----------------------------------------
                                    132 ;	 function osal_getClock
                                    133 ;	-----------------------------------------
      00898D                        134 _osal_getClock:
                                    135 ;	./src/OSAL_ClockBLE.c: 117: return ( OSAL_timeSeconds );
      00898D CE 04 13         [ 2]  136 	ldw	x, _OSAL_timeSeconds+2
      008990 90 CE 04 11      [ 2]  137 	ldw	y, _OSAL_timeSeconds+0
                                    138 ;	./src/OSAL_ClockBLE.c: 118: }
      008994 81               [ 4]  139 	ret
                                    140 ;	./src/OSAL_ClockBLE.c: 132: void osal_ConvertUTCTime( UTCTimeStruct *tm, UTCTime secTime )
                                    141 ;	-----------------------------------------
                                    142 ;	 function osal_ConvertUTCTime
                                    143 ;	-----------------------------------------
      008995                        144 _osal_ConvertUTCTime:
      008995 52 12            [ 2]  145 	sub	sp, #18
                                    146 ;	./src/OSAL_ClockBLE.c: 136: uint32 day = secTime % DAY;
      008997 4B 80            [ 1]  147 	push	#0x80
      008999 4B 51            [ 1]  148 	push	#0x51
      00899B 4B 01            [ 1]  149 	push	#0x01
      00899D 4B 00            [ 1]  150 	push	#0x00
      00899F 1E 1D            [ 2]  151 	ldw	x, (0x1d, sp)
      0089A1 89               [ 2]  152 	pushw	x
      0089A2 1E 1D            [ 2]  153 	ldw	x, (0x1d, sp)
      0089A4 89               [ 2]  154 	pushw	x
      0089A5 CD 8C 51         [ 4]  155 	call	__modulong
      0089A8 5B 08            [ 2]  156 	addw	sp, #8
      0089AA 1F 0F            [ 2]  157 	ldw	(0x0f, sp), x
      0089AC 17 0D            [ 2]  158 	ldw	(0x0d, sp), y
                                    159 ;	./src/OSAL_ClockBLE.c: 137: tm->seconds = day % 60UL;
      0089AE 16 15            [ 2]  160 	ldw	y, (0x15, sp)
      0089B0 17 01            [ 2]  161 	ldw	(0x01, sp), y
      0089B2 4B 3C            [ 1]  162 	push	#0x3c
      0089B4 5F               [ 1]  163 	clrw	x
      0089B5 89               [ 2]  164 	pushw	x
      0089B6 4B 00            [ 1]  165 	push	#0x00
      0089B8 1E 13            [ 2]  166 	ldw	x, (0x13, sp)
      0089BA 89               [ 2]  167 	pushw	x
      0089BB 1E 13            [ 2]  168 	ldw	x, (0x13, sp)
      0089BD 89               [ 2]  169 	pushw	x
      0089BE CD 8C 51         [ 4]  170 	call	__modulong
      0089C1 5B 08            [ 2]  171 	addw	sp, #8
      0089C3 9F               [ 1]  172 	ld	a, xl
      0089C4 1E 01            [ 2]  173 	ldw	x, (0x01, sp)
      0089C6 F7               [ 1]  174 	ld	(x), a
                                    175 ;	./src/OSAL_ClockBLE.c: 138: tm->minutes = (day % 3600UL) / 60UL;
      0089C7 1E 01            [ 2]  176 	ldw	x, (0x01, sp)
      0089C9 5C               [ 1]  177 	incw	x
      0089CA 1F 11            [ 2]  178 	ldw	(0x11, sp), x
      0089CC 4B 10            [ 1]  179 	push	#0x10
      0089CE 4B 0E            [ 1]  180 	push	#0x0e
      0089D0 5F               [ 1]  181 	clrw	x
      0089D1 89               [ 2]  182 	pushw	x
      0089D2 1E 13            [ 2]  183 	ldw	x, (0x13, sp)
      0089D4 89               [ 2]  184 	pushw	x
      0089D5 1E 13            [ 2]  185 	ldw	x, (0x13, sp)
      0089D7 89               [ 2]  186 	pushw	x
      0089D8 CD 8C 51         [ 4]  187 	call	__modulong
      0089DB 5B 08            [ 2]  188 	addw	sp, #8
      0089DD 4B 3C            [ 1]  189 	push	#0x3c
      0089DF 4B 00            [ 1]  190 	push	#0x00
      0089E1 4B 00            [ 1]  191 	push	#0x00
      0089E3 4B 00            [ 1]  192 	push	#0x00
      0089E5 89               [ 2]  193 	pushw	x
      0089E6 90 89            [ 2]  194 	pushw	y
      0089E8 CD 8C C1         [ 4]  195 	call	__divulong
      0089EB 5B 08            [ 2]  196 	addw	sp, #8
      0089ED 9F               [ 1]  197 	ld	a, xl
      0089EE 1E 11            [ 2]  198 	ldw	x, (0x11, sp)
      0089F0 F7               [ 1]  199 	ld	(x), a
                                    200 ;	./src/OSAL_ClockBLE.c: 139: tm->hour = day / 3600UL;
      0089F1 1E 01            [ 2]  201 	ldw	x, (0x01, sp)
      0089F3 5C               [ 1]  202 	incw	x
      0089F4 5C               [ 1]  203 	incw	x
      0089F5 1F 11            [ 2]  204 	ldw	(0x11, sp), x
      0089F7 4B 10            [ 1]  205 	push	#0x10
      0089F9 4B 0E            [ 1]  206 	push	#0x0e
      0089FB 5F               [ 1]  207 	clrw	x
      0089FC 89               [ 2]  208 	pushw	x
      0089FD 1E 13            [ 2]  209 	ldw	x, (0x13, sp)
      0089FF 89               [ 2]  210 	pushw	x
      008A00 1E 13            [ 2]  211 	ldw	x, (0x13, sp)
      008A02 89               [ 2]  212 	pushw	x
      008A03 CD 8C C1         [ 4]  213 	call	__divulong
      008A06 5B 08            [ 2]  214 	addw	sp, #8
      008A08 9F               [ 1]  215 	ld	a, xl
      008A09 1E 11            [ 2]  216 	ldw	x, (0x11, sp)
      008A0B F7               [ 1]  217 	ld	(x), a
                                    218 ;	./src/OSAL_ClockBLE.c: 144: uint16 numDays = secTime / DAY;
      008A0C 4B 80            [ 1]  219 	push	#0x80
      008A0E 4B 51            [ 1]  220 	push	#0x51
      008A10 4B 01            [ 1]  221 	push	#0x01
      008A12 4B 00            [ 1]  222 	push	#0x00
      008A14 1E 1D            [ 2]  223 	ldw	x, (0x1d, sp)
      008A16 89               [ 2]  224 	pushw	x
      008A17 1E 1D            [ 2]  225 	ldw	x, (0x1d, sp)
      008A19 89               [ 2]  226 	pushw	x
      008A1A CD 8C C1         [ 4]  227 	call	__divulong
      008A1D 5B 08            [ 2]  228 	addw	sp, #8
      008A1F 1F 03            [ 2]  229 	ldw	(0x03, sp), x
                                    230 ;	./src/OSAL_ClockBLE.c: 145: tm->year = BEGYEAR;
      008A21 1E 01            [ 2]  231 	ldw	x, (0x01, sp)
      008A23 1C 00 05         [ 2]  232 	addw	x, #0x0005
      008A26 1F 05            [ 2]  233 	ldw	(0x05, sp), x
      008A28 90 AE 07 D0      [ 2]  234 	ldw	y, #0x07d0
      008A2C FF               [ 2]  235 	ldw	(x), y
                                    236 ;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
      008A2D                        237 00101$:
      008A2D 1E 05            [ 2]  238 	ldw	x, (0x05, sp)
      008A2F FE               [ 2]  239 	ldw	x, (x)
      008A30 1F 07            [ 2]  240 	ldw	(0x07, sp), x
      008A32 89               [ 2]  241 	pushw	x
      008A33 90 AE 01 90      [ 2]  242 	ldw	y, #0x0190
      008A37 65               [ 2]  243 	divw	x, y
      008A38 17 0B            [ 2]  244 	ldw	(0x0b, sp), y
      008A3A 85               [ 2]  245 	popw	x
      008A3B 89               [ 2]  246 	pushw	x
      008A3C 90 AE 00 64      [ 2]  247 	ldw	y, #0x0064
      008A40 65               [ 2]  248 	divw	x, y
      008A41 17 0D            [ 2]  249 	ldw	(0x0d, sp), y
      008A43 85               [ 2]  250 	popw	x
      008A44 9F               [ 1]  251 	ld	a, xl
      008A45 A4 03            [ 1]  252 	and	a, #0x03
      008A47 6B 0E            [ 1]  253 	ld	(0x0e, sp), a
      008A49 0F 0D            [ 1]  254 	clr	(0x0d, sp)
      008A4B 1E 09            [ 2]  255 	ldw	x, (0x09, sp)
      008A4D 27 08            [ 1]  256 	jreq	00112$
      008A4F 1E 0B            [ 2]  257 	ldw	x, (0x0b, sp)
      008A51 27 08            [ 1]  258 	jreq	00109$
      008A53 1E 0D            [ 2]  259 	ldw	x, (0x0d, sp)
      008A55 26 04            [ 1]  260 	jrne	00109$
      008A57                        261 00112$:
      008A57 AE 01 6E         [ 2]  262 	ldw	x, #0x016e
      008A5A BC                     263 	.byte 0xbc
      008A5B                        264 00109$:
      008A5B AE 01 6D         [ 2]  265 	ldw	x, #0x016d
      008A5E                        266 00110$:
      008A5E 16 03            [ 2]  267 	ldw	y, (0x03, sp)
      008A60 17 0F            [ 2]  268 	ldw	(0x0f, sp), y
      008A62 1F 11            [ 2]  269 	ldw	(0x11, sp), x
      008A64 1E 0F            [ 2]  270 	ldw	x, (0x0f, sp)
      008A66 13 11            [ 2]  271 	cpw	x, (0x11, sp)
      008A68 25 22            [ 1]  272 	jrc	00103$
                                    273 ;	./src/OSAL_ClockBLE.c: 148: numDays -= YearLength( tm->year );
      008A6A 1E 09            [ 2]  274 	ldw	x, (0x09, sp)
      008A6C 27 08            [ 1]  275 	jreq	00120$
      008A6E 1E 0B            [ 2]  276 	ldw	x, (0x0b, sp)
      008A70 27 08            [ 1]  277 	jreq	00117$
      008A72 1E 0D            [ 2]  278 	ldw	x, (0x0d, sp)
      008A74 26 04            [ 1]  279 	jrne	00117$
      008A76                        280 00120$:
      008A76 AE 01 6E         [ 2]  281 	ldw	x, #0x016e
      008A79 BC                     282 	.byte 0xbc
      008A7A                        283 00117$:
      008A7A AE 01 6D         [ 2]  284 	ldw	x, #0x016d
      008A7D                        285 00118$:
      008A7D 50               [ 2]  286 	negw	x
      008A7E 72 FB 0F         [ 2]  287 	addw	x, (0x0f, sp)
      008A81 1F 03            [ 2]  288 	ldw	(0x03, sp), x
                                    289 ;	./src/OSAL_ClockBLE.c: 149: tm->year++;
      008A83 1E 07            [ 2]  290 	ldw	x, (0x07, sp)
      008A85 5C               [ 1]  291 	incw	x
      008A86 16 05            [ 2]  292 	ldw	y, (0x05, sp)
      008A88 90 FF            [ 2]  293 	ldw	(y), x
      008A8A 20 A1            [ 2]  294 	jra	00101$
      008A8C                        295 00103$:
                                    296 ;	./src/OSAL_ClockBLE.c: 152: tm->month = 0;
      008A8C 1E 01            [ 2]  297 	ldw	x, (0x01, sp)
      008A8E 1C 00 04         [ 2]  298 	addw	x, #0x0004
      008A91 1F 0E            [ 2]  299 	ldw	(0x0e, sp), x
      008A93 7F               [ 1]  300 	clr	(x)
                                    301 ;	./src/OSAL_ClockBLE.c: 153: while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
      008A94                        302 00104$:
      008A94 1E 0E            [ 2]  303 	ldw	x, (0x0e, sp)
      008A96 F6               [ 1]  304 	ld	a, (x)
                                    305 ;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
      008A97 1E 05            [ 2]  306 	ldw	x, (0x05, sp)
      008A99 FE               [ 2]  307 	ldw	x, (x)
                                    308 ;	./src/OSAL_ClockBLE.c: 153: while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
      008A9A 1F 11            [ 2]  309 	ldw	(0x11, sp), x
      008A9C 90 AE 01 90      [ 2]  310 	ldw	y, #0x0190
      008AA0 65               [ 2]  311 	divw	x, y
      008AA1 90 5D            [ 2]  312 	tnzw	y
      008AA3 27 16            [ 1]  313 	jreq	00126$
      008AA5 1E 11            [ 2]  314 	ldw	x, (0x11, sp)
      008AA7 90 AE 00 64      [ 2]  315 	ldw	y, #0x0064
      008AAB 65               [ 2]  316 	divw	x, y
      008AAC 90 5D            [ 2]  317 	tnzw	y
      008AAE 27 08            [ 1]  318 	jreq	00125$
      008AB0 88               [ 1]  319 	push	a
      008AB1 7B 13            [ 1]  320 	ld	a, (0x13, sp)
      008AB3 A5 03            [ 1]  321 	bcp	a, #0x03
      008AB5 84               [ 1]  322 	pop	a
      008AB6 27 03            [ 1]  323 	jreq	00126$
      008AB8                        324 00125$:
      008AB8 5F               [ 1]  325 	clrw	x
      008AB9 20 04            [ 2]  326 	jra	00127$
      008ABB                        327 00126$:
      008ABB 41               [ 1]  328 	exg	a, xl
      008ABC A6 01            [ 1]  329 	ld	a, #0x01
      008ABE 41               [ 1]  330 	exg	a, xl
      008ABF                        331 00127$:
      008ABF 88               [ 1]  332 	push	a
      008AC0 9F               [ 1]  333 	ld	a, xl
      008AC1 88               [ 1]  334 	push	a
      008AC2 CD 8B 20         [ 4]  335 	call	_monthLength
      008AC5 85               [ 2]  336 	popw	x
      008AC6 6B 12            [ 1]  337 	ld	(0x12, sp), a
      008AC8 0F 11            [ 1]  338 	clr	(0x11, sp)
      008ACA 1E 03            [ 2]  339 	ldw	x, (0x03, sp)
      008ACC 13 11            [ 2]  340 	cpw	x, (0x11, sp)
      008ACE 25 47            [ 1]  341 	jrc	00106$
                                    342 ;	./src/OSAL_ClockBLE.c: 155: numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
      008AD0 1E 0E            [ 2]  343 	ldw	x, (0x0e, sp)
      008AD2 F6               [ 1]  344 	ld	a, (x)
      008AD3 6B 10            [ 1]  345 	ld	(0x10, sp), a
                                    346 ;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
      008AD5 1E 05            [ 2]  347 	ldw	x, (0x05, sp)
      008AD7 FE               [ 2]  348 	ldw	x, (x)
      008AD8 9F               [ 1]  349 	ld	a, xl
                                    350 ;	./src/OSAL_ClockBLE.c: 155: numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
      008AD9 89               [ 2]  351 	pushw	x
      008ADA 97               [ 1]  352 	ld	xl, a
      008ADB 90 AE 01 90      [ 2]  353 	ldw	y, #0x0190
      008ADF 65               [ 2]  354 	divw	x, y
      008AE0 17 13            [ 2]  355 	ldw	(0x13, sp), y
      008AE2 85               [ 2]  356 	popw	x
      008AE3 16 11            [ 2]  357 	ldw	y, (0x11, sp)
      008AE5 27 13            [ 1]  358 	jreq	00132$
      008AE7 89               [ 2]  359 	pushw	x
      008AE8 97               [ 1]  360 	ld	xl, a
      008AE9 90 AE 00 64      [ 2]  361 	ldw	y, #0x0064
      008AED 65               [ 2]  362 	divw	x, y
      008AEE 85               [ 2]  363 	popw	x
      008AEF 90 5D            [ 2]  364 	tnzw	y
      008AF1 27 04            [ 1]  365 	jreq	00131$
      008AF3 A5 03            [ 1]  366 	bcp	a, #0x03
      008AF5 27 03            [ 1]  367 	jreq	00132$
      008AF7                        368 00131$:
      008AF7 5F               [ 1]  369 	clrw	x
      008AF8 20 03            [ 2]  370 	jra	00133$
      008AFA                        371 00132$:
      008AFA A6 01            [ 1]  372 	ld	a, #0x01
      008AFC 97               [ 1]  373 	ld	xl, a
      008AFD                        374 00133$:
      008AFD 7B 10            [ 1]  375 	ld	a, (0x10, sp)
      008AFF 88               [ 1]  376 	push	a
      008B00 9F               [ 1]  377 	ld	a, xl
      008B01 88               [ 1]  378 	push	a
      008B02 CD 8B 20         [ 4]  379 	call	_monthLength
      008B05 85               [ 2]  380 	popw	x
      008B06 5F               [ 1]  381 	clrw	x
      008B07 97               [ 1]  382 	ld	xl, a
      008B08 16 03            [ 2]  383 	ldw	y, (0x03, sp)
      008B0A 1F 11            [ 2]  384 	ldw	(0x11, sp), x
      008B0C 72 F2 11         [ 2]  385 	subw	y, (0x11, sp)
      008B0F 17 03            [ 2]  386 	ldw	(0x03, sp), y
                                    387 ;	./src/OSAL_ClockBLE.c: 156: tm->month++;
      008B11 1E 0E            [ 2]  388 	ldw	x, (0x0e, sp)
      008B13 7C               [ 1]  389 	inc	(x)
      008B14 CC 8A 94         [ 2]  390 	jp	00104$
      008B17                        391 00106$:
                                    392 ;	./src/OSAL_ClockBLE.c: 159: tm->day = numDays;
      008B17 1E 01            [ 2]  393 	ldw	x, (0x01, sp)
      008B19 7B 04            [ 1]  394 	ld	a, (0x04, sp)
      008B1B E7 03            [ 1]  395 	ld	(0x0003, x), a
                                    396 ;	./src/OSAL_ClockBLE.c: 161: }
      008B1D 5B 12            [ 2]  397 	addw	sp, #18
      008B1F 81               [ 4]  398 	ret
                                    399 ;	./src/OSAL_ClockBLE.c: 172: static uint8 monthLength( uint8 lpyr, uint8 mon )
                                    400 ;	-----------------------------------------
                                    401 ;	 function monthLength
                                    402 ;	-----------------------------------------
      008B20                        403 _monthLength:
                                    404 ;	./src/OSAL_ClockBLE.c: 174: uint8 days = 31;
      008B20 A6 1F            [ 1]  405 	ld	a, #0x1f
      008B22 97               [ 1]  406 	ld	xl, a
                                    407 ;	./src/OSAL_ClockBLE.c: 176: if ( mon == 1 ) // feb
      008B23 7B 04            [ 1]  408 	ld	a, (0x04, sp)
      008B25 4A               [ 1]  409 	dec	a
      008B26 26 07            [ 1]  410 	jrne	00106$
                                    411 ;	./src/OSAL_ClockBLE.c: 178: days = ( 28 + lpyr );
      008B28 7B 03            [ 1]  412 	ld	a, (0x03, sp)
      008B2A AB 1C            [ 1]  413 	add	a, #0x1c
      008B2C 97               [ 1]  414 	ld	xl, a
      008B2D 20 10            [ 2]  415 	jra	00107$
      008B2F                        416 00106$:
                                    417 ;	./src/OSAL_ClockBLE.c: 182: if ( mon > 6 ) // aug-dec
      008B2F 7B 04            [ 1]  418 	ld	a, (0x04, sp)
      008B31 A1 06            [ 1]  419 	cp	a, #0x06
      008B33 23 02            [ 2]  420 	jrule	00102$
                                    421 ;	./src/OSAL_ClockBLE.c: 184: mon--;
      008B35 0A 04            [ 1]  422 	dec	(0x04, sp)
      008B37                        423 00102$:
                                    424 ;	./src/OSAL_ClockBLE.c: 187: if ( mon & 1 )
      008B37 7B 04            [ 1]  425 	ld	a, (0x04, sp)
      008B39 44               [ 1]  426 	srl	a
      008B3A 24 03            [ 1]  427 	jrnc	00107$
                                    428 ;	./src/OSAL_ClockBLE.c: 189: days = 30;
      008B3C A6 1E            [ 1]  429 	ld	a, #0x1e
      008B3E 97               [ 1]  430 	ld	xl, a
      008B3F                        431 00107$:
                                    432 ;	./src/OSAL_ClockBLE.c: 193: return ( days );
      008B3F 9F               [ 1]  433 	ld	a, xl
                                    434 ;	./src/OSAL_ClockBLE.c: 194: }
      008B40 81               [ 4]  435 	ret
                                    436 ;	./src/OSAL_ClockBLE.c: 205: UTCTime osal_ConvertUTCSecs( UTCTimeStruct *tm )
                                    437 ;	-----------------------------------------
                                    438 ;	 function osal_ConvertUTCSecs
                                    439 ;	-----------------------------------------
      008B41                        440 _osal_ConvertUTCSecs:
      008B41 52 0C            [ 2]  441 	sub	sp, #12
                                    442 ;	./src/OSAL_ClockBLE.c: 210: seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;
      008B43 16 0F            [ 2]  443 	ldw	y, (0x0f, sp)
      008B45 17 0B            [ 2]  444 	ldw	(0x0b, sp), y
      008B47 93               [ 1]  445 	ldw	x, y
      008B48 E6 02            [ 1]  446 	ld	a, (0x2, x)
      008B4A 5F               [ 1]  447 	clrw	x
      008B4B 97               [ 1]  448 	ld	xl, a
      008B4C 90 5F            [ 1]  449 	clrw	y
      008B4E 89               [ 2]  450 	pushw	x
      008B4F 90 89            [ 2]  451 	pushw	y
      008B51 4B 3C            [ 1]  452 	push	#0x3c
      008B53 5F               [ 1]  453 	clrw	x
      008B54 89               [ 2]  454 	pushw	x
      008B55 4B 00            [ 1]  455 	push	#0x00
      008B57 CD 8D 3A         [ 4]  456 	call	__mullong
      008B5A 5B 08            [ 2]  457 	addw	sp, #8
      008B5C 1F 09            [ 2]  458 	ldw	(0x09, sp), x
      008B5E 17 07            [ 2]  459 	ldw	(0x07, sp), y
      008B60 1E 0B            [ 2]  460 	ldw	x, (0x0b, sp)
      008B62 E6 01            [ 1]  461 	ld	a, (0x1, x)
      008B64 90 5F            [ 1]  462 	clrw	y
      008B66 5F               [ 1]  463 	clrw	x
      008B67 90 97            [ 1]  464 	ld	yl, a
      008B69 72 F9 09         [ 2]  465 	addw	y, (0x09, sp)
      008B6C 9F               [ 1]  466 	ld	a, xl
      008B6D 19 08            [ 1]  467 	adc	a, (0x08, sp)
      008B6F 02               [ 1]  468 	rlwa	x
      008B70 19 07            [ 1]  469 	adc	a, (0x07, sp)
      008B72 95               [ 1]  470 	ld	xh, a
      008B73 90 89            [ 2]  471 	pushw	y
      008B75 89               [ 2]  472 	pushw	x
      008B76 4B 3C            [ 1]  473 	push	#0x3c
      008B78 5F               [ 1]  474 	clrw	x
      008B79 89               [ 2]  475 	pushw	x
      008B7A 4B 00            [ 1]  476 	push	#0x00
      008B7C CD 8D 3A         [ 4]  477 	call	__mullong
      008B7F 5B 08            [ 2]  478 	addw	sp, #8
      008B81 1F 09            [ 2]  479 	ldw	(0x09, sp), x
      008B83 17 07            [ 2]  480 	ldw	(0x07, sp), y
      008B85 1E 0B            [ 2]  481 	ldw	x, (0x0b, sp)
      008B87 F6               [ 1]  482 	ld	a, (x)
      008B88 90 5F            [ 1]  483 	clrw	y
      008B8A 5F               [ 1]  484 	clrw	x
      008B8B 90 97            [ 1]  485 	ld	yl, a
      008B8D 72 F9 09         [ 2]  486 	addw	y, (0x09, sp)
      008B90 9F               [ 1]  487 	ld	a, xl
      008B91 19 08            [ 1]  488 	adc	a, (0x08, sp)
      008B93 02               [ 1]  489 	rlwa	x
      008B94 19 07            [ 1]  490 	adc	a, (0x07, sp)
      008B96 95               [ 1]  491 	ld	xh, a
      008B97 17 03            [ 2]  492 	ldw	(0x03, sp), y
      008B99 1F 01            [ 2]  493 	ldw	(0x01, sp), x
                                    494 ;	./src/OSAL_ClockBLE.c: 215: uint16 days = tm->day;
      008B9B 1E 0B            [ 2]  495 	ldw	x, (0x0b, sp)
      008B9D E6 03            [ 1]  496 	ld	a, (0x3, x)
      008B9F 5F               [ 1]  497 	clrw	x
      008BA0 97               [ 1]  498 	ld	xl, a
      008BA1 1F 05            [ 2]  499 	ldw	(0x05, sp), x
                                    500 ;	./src/OSAL_ClockBLE.c: 219: int8 month = tm->month;
      008BA3 1E 0B            [ 2]  501 	ldw	x, (0x0b, sp)
      008BA5 E6 04            [ 1]  502 	ld	a, (0x4, x)
                                    503 ;	./src/OSAL_ClockBLE.c: 220: while ( --month >= 0 )
      008BA7 16 0B            [ 2]  504 	ldw	y, (0x0b, sp)
      008BA9 17 07            [ 2]  505 	ldw	(0x07, sp), y
      008BAB                        506 00101$:
      008BAB 4A               [ 1]  507 	dec	a
                                    508 ;	./src/OSAL_ClockBLE.c: 222: days += monthLength( IsLeapYear( tm->year ), month );
      008BAC 1E 07            [ 2]  509 	ldw	x, (0x07, sp)
      008BAE EE 05            [ 2]  510 	ldw	x, (0x5, x)
                                    511 ;	./src/OSAL_ClockBLE.c: 220: while ( --month >= 0 )
      008BB0 4D               [ 1]  512 	tnz	a
      008BB1 2B 3F            [ 1]  513 	jrmi	00103$
                                    514 ;	./src/OSAL_ClockBLE.c: 222: days += monthLength( IsLeapYear( tm->year ), month );
      008BB3 1F 09            [ 2]  515 	ldw	(0x09, sp), x
      008BB5 90 AE 01 90      [ 2]  516 	ldw	y, #0x0190
      008BB9 65               [ 2]  517 	divw	x, y
      008BBA 17 0B            [ 2]  518 	ldw	(0x0b, sp), y
      008BBC 93               [ 1]  519 	ldw	x, y
      008BBD 27 16            [ 1]  520 	jreq	00110$
      008BBF 1E 09            [ 2]  521 	ldw	x, (0x09, sp)
      008BC1 90 AE 00 64      [ 2]  522 	ldw	y, #0x0064
      008BC5 65               [ 2]  523 	divw	x, y
      008BC6 90 5D            [ 2]  524 	tnzw	y
      008BC8 27 08            [ 1]  525 	jreq	00109$
      008BCA 88               [ 1]  526 	push	a
      008BCB 7B 0B            [ 1]  527 	ld	a, (0x0b, sp)
      008BCD A5 03            [ 1]  528 	bcp	a, #0x03
      008BCF 84               [ 1]  529 	pop	a
      008BD0 27 03            [ 1]  530 	jreq	00110$
      008BD2                        531 00109$:
      008BD2 5F               [ 1]  532 	clrw	x
      008BD3 20 04            [ 2]  533 	jra	00111$
      008BD5                        534 00110$:
      008BD5 41               [ 1]  535 	exg	a, xl
      008BD6 A6 01            [ 1]  536 	ld	a, #0x01
      008BD8 41               [ 1]  537 	exg	a, xl
      008BD9                        538 00111$:
      008BD9 88               [ 1]  539 	push	a
      008BDA 88               [ 1]  540 	push	a
      008BDB 89               [ 2]  541 	pushw	x
      008BDC 5B 01            [ 2]  542 	addw	sp, #1
      008BDE CD 8B 20         [ 4]  543 	call	_monthLength
      008BE1 85               [ 2]  544 	popw	x
      008BE2 97               [ 1]  545 	ld	xl, a
      008BE3 84               [ 1]  546 	pop	a
      008BE4 02               [ 1]  547 	rlwa	x
      008BE5 4F               [ 1]  548 	clr	a
      008BE6 01               [ 1]  549 	rrwa	x
      008BE7 16 05            [ 2]  550 	ldw	y, (0x05, sp)
      008BE9 1F 0B            [ 2]  551 	ldw	(0x0b, sp), x
      008BEB 72 F9 0B         [ 2]  552 	addw	y, (0x0b, sp)
      008BEE 17 05            [ 2]  553 	ldw	(0x05, sp), y
      008BF0 20 B9            [ 2]  554 	jra	00101$
      008BF2                        555 00103$:
                                    556 ;	./src/OSAL_ClockBLE.c: 228: uint16 year = tm->year;
                                    557 ;	./src/OSAL_ClockBLE.c: 229: while ( --year >= BEGYEAR )
      008BF2 1F 0B            [ 2]  558 	ldw	(0x0b, sp), x
      008BF4                        559 00104$:
      008BF4 1E 0B            [ 2]  560 	ldw	x, (0x0b, sp)
      008BF6 5A               [ 2]  561 	decw	x
      008BF7 1F 0B            [ 2]  562 	ldw	(0x0b, sp), x
      008BF9 1F 07            [ 2]  563 	ldw	(0x07, sp), x
      008BFB A3 07 D0         [ 2]  564 	cpw	x, #0x07d0
      008BFE 25 2F            [ 1]  565 	jrc	00106$
                                    566 ;	./src/OSAL_ClockBLE.c: 231: days += YearLength( year );
      008C00 1E 07            [ 2]  567 	ldw	x, (0x07, sp)
      008C02 90 AE 01 90      [ 2]  568 	ldw	y, #0x0190
      008C06 65               [ 2]  569 	divw	x, y
      008C07 90 5D            [ 2]  570 	tnzw	y
      008C09 27 12            [ 1]  571 	jreq	00118$
      008C0B 1E 07            [ 2]  572 	ldw	x, (0x07, sp)
      008C0D 90 AE 00 64      [ 2]  573 	ldw	y, #0x0064
      008C11 65               [ 2]  574 	divw	x, y
      008C12 17 09            [ 2]  575 	ldw	(0x09, sp), y
      008C14 93               [ 1]  576 	ldw	x, y
      008C15 27 0A            [ 1]  577 	jreq	00115$
      008C17 7B 08            [ 1]  578 	ld	a, (0x08, sp)
      008C19 A5 03            [ 1]  579 	bcp	a, #0x03
      008C1B 26 04            [ 1]  580 	jrne	00115$
      008C1D                        581 00118$:
      008C1D AE 01 6E         [ 2]  582 	ldw	x, #0x016e
      008C20 BC                     583 	.byte 0xbc
      008C21                        584 00115$:
      008C21 AE 01 6D         [ 2]  585 	ldw	x, #0x016d
      008C24                        586 00116$:
      008C24 16 05            [ 2]  587 	ldw	y, (0x05, sp)
      008C26 17 09            [ 2]  588 	ldw	(0x09, sp), y
      008C28 72 FB 09         [ 2]  589 	addw	x, (0x09, sp)
      008C2B 1F 05            [ 2]  590 	ldw	(0x05, sp), x
      008C2D 20 C5            [ 2]  591 	jra	00104$
      008C2F                        592 00106$:
                                    593 ;	./src/OSAL_ClockBLE.c: 236: seconds += (days * DAY);
      008C2F 16 05            [ 2]  594 	ldw	y, (0x05, sp)
      008C31 5F               [ 1]  595 	clrw	x
      008C32 90 89            [ 2]  596 	pushw	y
      008C34 89               [ 2]  597 	pushw	x
      008C35 4B 80            [ 1]  598 	push	#0x80
      008C37 4B 51            [ 1]  599 	push	#0x51
      008C39 4B 01            [ 1]  600 	push	#0x01
      008C3B 4B 00            [ 1]  601 	push	#0x00
      008C3D CD 8D 3A         [ 4]  602 	call	__mullong
      008C40 5B 08            [ 2]  603 	addw	sp, #8
      008C42 51               [ 1]  604 	exgw	x, y
      008C43 72 F9 03         [ 2]  605 	addw	y, (0x03, sp)
      008C46 9F               [ 1]  606 	ld	a, xl
      008C47 19 02            [ 1]  607 	adc	a, (0x02, sp)
      008C49 02               [ 1]  608 	rlwa	x
      008C4A 19 01            [ 1]  609 	adc	a, (0x01, sp)
      008C4C 95               [ 1]  610 	ld	xh, a
      008C4D 51               [ 1]  611 	exgw	x, y
                                    612 ;	./src/OSAL_ClockBLE.c: 239: return ( seconds );
                                    613 ;	./src/OSAL_ClockBLE.c: 240: }
      008C4E 5B 0C            [ 2]  614 	addw	sp, #12
      008C50 81               [ 4]  615 	ret
                                    616 	.area CODE
                                    617 	.area CONST
                                    618 	.area INITIALIZER
      008028                        619 __xinit__timeMSec:
      008028 00 00                  620 	.dw #0x0000
      00802A                        621 __xinit__OSAL_timeSeconds:
      00802A 00 00 00 00            622 	.byte #0x00, #0x00, #0x00, #0x00	; 0
                                    623 	.area CABS (ABS)
