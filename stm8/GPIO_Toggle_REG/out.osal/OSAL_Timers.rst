                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module OSAL_Timers
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _osal_set_event
                                     12 	.globl _osal_mem_free
                                     13 	.globl _osal_mem_alloc
                                     14 	.globl _timerHead
                                     15 	.globl _osalTimerInit
                                     16 	.globl _osalAddTimer
                                     17 	.globl _osalFindTimer
                                     18 	.globl _osalDeleteTimer
                                     19 	.globl _osal_start_timerEx
                                     20 	.globl _osal_start_reload_timer
                                     21 	.globl _osal_stop_timerEx
                                     22 	.globl _osal_get_timeoutEx
                                     23 	.globl _osal_timer_num_active
                                     24 	.globl _osalTimerUpdate
                                     25 	.globl _osal_GetSystemClock
                                     26 ;--------------------------------------------------------
                                     27 ; ram data
                                     28 ;--------------------------------------------------------
                                     29 	.area DATA
      000408                         30 _timerHead::
      000408                         31 	.ds 2
      00040A                         32 _osal_systemClock:
      00040A                         33 	.ds 4
                                     34 ;--------------------------------------------------------
                                     35 ; ram data
                                     36 ;--------------------------------------------------------
                                     37 	.area INITIALIZED
                                     38 ;--------------------------------------------------------
                                     39 ; absolute external ram data
                                     40 ;--------------------------------------------------------
                                     41 	.area DABS (ABS)
                                     42 
                                     43 ; default segment ordering for linker
                                     44 	.area HOME
                                     45 	.area GSINIT
                                     46 	.area GSFINAL
                                     47 	.area CONST
                                     48 	.area INITIALIZER
                                     49 	.area CODE
                                     50 
                                     51 ;--------------------------------------------------------
                                     52 ; global & static initialisations
                                     53 ;--------------------------------------------------------
                                     54 	.area HOME
                                     55 	.area GSINIT
                                     56 	.area GSFINAL
                                     57 	.area GSINIT
                                     58 ;--------------------------------------------------------
                                     59 ; Home
                                     60 ;--------------------------------------------------------
                                     61 	.area HOME
                                     62 	.area HOME
                                     63 ;--------------------------------------------------------
                                     64 ; code
                                     65 ;--------------------------------------------------------
                                     66 	.area CODE
                                     67 ;	./src/OSAL_Timers.c: 54: void osalTimerInit( void )
                                     68 ;	-----------------------------------------
                                     69 ;	 function osalTimerInit
                                     70 ;	-----------------------------------------
      008600                         71 _osalTimerInit:
                                     72 ;	./src/OSAL_Timers.c: 56: osal_systemClock = 0;
      008600 5F               [ 1]   73 	clrw	x
      008601 CF 04 0C         [ 2]   74 	ldw	_osal_systemClock+2, x
      008604 CF 04 0A         [ 2]   75 	ldw	_osal_systemClock+0, x
                                     76 ;	./src/OSAL_Timers.c: 57: }
      008607 81               [ 4]   77 	ret
                                     78 ;	./src/OSAL_Timers.c: 71: osalTimerRec_t * osalAddTimer( uint8 task_id, uint16 event_flag, uint32 timeout )
                                     79 ;	-----------------------------------------
                                     80 ;	 function osalAddTimer
                                     81 ;	-----------------------------------------
      008608                         82 _osalAddTimer:
      008608 89               [ 2]   83 	pushw	x
                                     84 ;	./src/OSAL_Timers.c: 77: newTimer = osalFindTimer( task_id, event_flag );
      008609 1E 06            [ 2]   85 	ldw	x, (0x06, sp)
      00860B 89               [ 2]   86 	pushw	x
      00860C 7B 07            [ 1]   87 	ld	a, (0x07, sp)
      00860E 88               [ 1]   88 	push	a
      00860F CD 86 7C         [ 4]   89 	call	_osalFindTimer
      008612 5B 03            [ 2]   90 	addw	sp, #3
                                     91 ;	./src/OSAL_Timers.c: 78: if ( newTimer )
      008614 1F 01            [ 2]   92 	ldw	(0x01, sp), x
      008616 27 0F            [ 1]   93 	jreq	00111$
                                     94 ;	./src/OSAL_Timers.c: 81: newTimer->timeout.time32 = timeout;
      008618 1E 01            [ 2]   95 	ldw	x, (0x01, sp)
      00861A 5C               [ 1]   96 	incw	x
      00861B 5C               [ 1]   97 	incw	x
      00861C 16 0A            [ 2]   98 	ldw	y, (0x0a, sp)
      00861E EF 02            [ 2]   99 	ldw	(0x2, x), y
      008620 16 08            [ 2]  100 	ldw	y, (0x08, sp)
      008622 FF               [ 2]  101 	ldw	(x), y
                                    102 ;	./src/OSAL_Timers.c: 83: return ( newTimer );
      008623 1E 01            [ 2]  103 	ldw	x, (0x01, sp)
      008625 20 52            [ 2]  104 	jra	00113$
      008627                        105 00111$:
                                    106 ;	./src/OSAL_Timers.c: 88: newTimer = osal_mem_alloc( sizeof( osalTimerRec_t ) );
      008627 4B 0D            [ 1]  107 	push	#0x0d
      008629 4B 00            [ 1]  108 	push	#0x00
      00862B CD 84 71         [ 4]  109 	call	_osal_mem_alloc
      00862E 5B 02            [ 2]  110 	addw	sp, #2
                                    111 ;	./src/OSAL_Timers.c: 90: if ( newTimer )
      008630 1F 01            [ 2]  112 	ldw	(0x01, sp), x
      008632 27 44            [ 1]  113 	jreq	00108$
                                    114 ;	./src/OSAL_Timers.c: 93: newTimer->task_id = task_id;
      008634 1E 01            [ 2]  115 	ldw	x, (0x01, sp)
      008636 7B 05            [ 1]  116 	ld	a, (0x05, sp)
      008638 E7 08            [ 1]  117 	ld	(0x0008, x), a
                                    118 ;	./src/OSAL_Timers.c: 94: newTimer->event_flag = event_flag;
      00863A 1E 01            [ 2]  119 	ldw	x, (0x01, sp)
      00863C 16 06            [ 2]  120 	ldw	y, (0x06, sp)
      00863E EF 06            [ 2]  121 	ldw	(0x0006, x), y
                                    122 ;	./src/OSAL_Timers.c: 95: newTimer->timeout.time32 = timeout;
      008640 1E 01            [ 2]  123 	ldw	x, (0x01, sp)
      008642 5C               [ 1]  124 	incw	x
      008643 5C               [ 1]  125 	incw	x
      008644 16 0A            [ 2]  126 	ldw	y, (0x0a, sp)
      008646 EF 02            [ 2]  127 	ldw	(0x2, x), y
      008648 16 08            [ 2]  128 	ldw	y, (0x08, sp)
      00864A FF               [ 2]  129 	ldw	(x), y
                                    130 ;	./src/OSAL_Timers.c: 96: newTimer->next = (void *)NULL;
      00864B 1E 01            [ 2]  131 	ldw	x, (0x01, sp)
      00864D 6F 01            [ 1]  132 	clr	(0x1, x)
      00864F 7F               [ 1]  133 	clr	(x)
                                    134 ;	./src/OSAL_Timers.c: 97: newTimer->reloadTimeout = 0;
      008650 1E 01            [ 2]  135 	ldw	x, (0x01, sp)
      008652 1C 00 09         [ 2]  136 	addw	x, #0x0009
      008655 90 5F            [ 1]  137 	clrw	y
      008657 EF 02            [ 2]  138 	ldw	(0x2, x), y
      008659 FF               [ 2]  139 	ldw	(x), y
                                    140 ;	./src/OSAL_Timers.c: 100: if ( timerHead == NULL )
      00865A CE 04 08         [ 2]  141 	ldw	x, _timerHead+0
      00865D 26 07            [ 1]  142 	jrne	00105$
                                    143 ;	./src/OSAL_Timers.c: 103: timerHead = newTimer;
      00865F 1E 01            [ 2]  144 	ldw	x, (0x01, sp)
      008661 CF 04 08         [ 2]  145 	ldw	_timerHead+0, x
      008664 20 0F            [ 2]  146 	jra	00106$
      008666                        147 00105$:
                                    148 ;	./src/OSAL_Timers.c: 108: srchTimer = timerHead;
      008666 90 CE 04 08      [ 2]  149 	ldw	y, _timerHead+0
                                    150 ;	./src/OSAL_Timers.c: 111: while ( srchTimer->next )
      00866A                        151 00101$:
      00866A 93               [ 1]  152 	ldw	x, y
      00866B FE               [ 2]  153 	ldw	x, (x)
      00866C 27 03            [ 1]  154 	jreq	00103$
                                    155 ;	./src/OSAL_Timers.c: 112: srchTimer = srchTimer->next;
      00866E 51               [ 1]  156 	exgw	x, y
      00866F 20 F9            [ 2]  157 	jra	00101$
      008671                        158 00103$:
                                    159 ;	./src/OSAL_Timers.c: 115: srchTimer->next = newTimer;
      008671 1E 01            [ 2]  160 	ldw	x, (0x01, sp)
      008673 90 FF            [ 2]  161 	ldw	(y), x
      008675                        162 00106$:
                                    163 ;	./src/OSAL_Timers.c: 118: return ( newTimer );
      008675 1E 01            [ 2]  164 	ldw	x, (0x01, sp)
                                    165 ;	./src/OSAL_Timers.c: 122: return ( (osalTimerRec_t *)NULL );
      008677 21                     166 	.byte 0x21
      008678                        167 00108$:
      008678 5F               [ 1]  168 	clrw	x
      008679                        169 00113$:
                                    170 ;	./src/OSAL_Timers.c: 125: }
      008679 5B 02            [ 2]  171 	addw	sp, #2
      00867B 81               [ 4]  172 	ret
                                    173 ;	./src/OSAL_Timers.c: 138: osalTimerRec_t *osalFindTimer( uint8 task_id, uint16 event_flag )
                                    174 ;	-----------------------------------------
                                    175 ;	 function osalFindTimer
                                    176 ;	-----------------------------------------
      00867C                        177 _osalFindTimer:
                                    178 ;	./src/OSAL_Timers.c: 143: srchTimer = timerHead;
      00867C 90 CE 04 08      [ 2]  179 	ldw	y, _timerHead+0
                                    180 ;	./src/OSAL_Timers.c: 146: while ( srchTimer )
      008680                        181 00104$:
      008680 90 5D            [ 2]  182 	tnzw	y
      008682 27 12            [ 1]  183 	jreq	00106$
                                    184 ;	./src/OSAL_Timers.c: 148: if ( srchTimer->event_flag == event_flag &&
      008684 93               [ 1]  185 	ldw	x, y
      008685 EE 06            [ 2]  186 	ldw	x, (0x6, x)
      008687 13 04            [ 2]  187 	cpw	x, (0x04, sp)
      008689 26 07            [ 1]  188 	jrne	00102$
                                    189 ;	./src/OSAL_Timers.c: 149: srchTimer->task_id == task_id )
      00868B 93               [ 1]  190 	ldw	x, y
      00868C E6 08            [ 1]  191 	ld	a, (0x8, x)
      00868E 11 03            [ 1]  192 	cp	a, (0x03, sp)
      008690 27 04            [ 1]  193 	jreq	00106$
                                    194 ;	./src/OSAL_Timers.c: 151: break;
      008692                        195 00102$:
                                    196 ;	./src/OSAL_Timers.c: 155: srchTimer = srchTimer->next;
      008692 90 FE            [ 2]  197 	ldw	y, (y)
      008694 20 EA            [ 2]  198 	jra	00104$
      008696                        199 00106$:
                                    200 ;	./src/OSAL_Timers.c: 158: return ( srchTimer );
      008696 93               [ 1]  201 	ldw	x, y
                                    202 ;	./src/OSAL_Timers.c: 159: }
      008697 81               [ 4]  203 	ret
                                    204 ;	./src/OSAL_Timers.c: 171: void osalDeleteTimer( osalTimerRec_t *rmTimer )
                                    205 ;	-----------------------------------------
                                    206 ;	 function osalDeleteTimer
                                    207 ;	-----------------------------------------
      008698                        208 _osalDeleteTimer:
                                    209 ;	./src/OSAL_Timers.c: 174: if ( rmTimer )
      008698 1E 03            [ 2]  210 	ldw	x, (0x03, sp)
      00869A 26 01            [ 1]  211 	jrne	00110$
      00869C 81               [ 4]  212 	ret
      00869D                        213 00110$:
                                    214 ;	./src/OSAL_Timers.c: 178: rmTimer->event_flag = 0;
      00869D 1E 03            [ 2]  215 	ldw	x, (0x03, sp)
      00869F 1C 00 06         [ 2]  216 	addw	x, #0x0006
      0086A2 6F 01            [ 1]  217 	clr	(0x1, x)
      0086A4 7F               [ 1]  218 	clr	(x)
                                    219 ;	./src/OSAL_Timers.c: 180: }
      0086A5 81               [ 4]  220 	ret
                                    221 ;	./src/OSAL_Timers.c: 196: uint8 osal_start_timerEx( uint8 taskID, uint16 event_id, uint32 timeout_value )
                                    222 ;	-----------------------------------------
                                    223 ;	 function osal_start_timerEx
                                    224 ;	-----------------------------------------
      0086A6                        225 _osal_start_timerEx:
                                    226 ;	./src/OSAL_Timers.c: 201: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      0086A6 9B               [ 1]  227 	sim
      0086A7 9D               [ 1]  228 	nop
      0086A8 9D               [ 1]  229 	nop
                                    230 ;	./src/OSAL_Timers.c: 204: newTimer = osalAddTimer( taskID, event_id, timeout_value );
      0086A9 1E 08            [ 2]  231 	ldw	x, (0x08, sp)
      0086AB 89               [ 2]  232 	pushw	x
      0086AC 1E 08            [ 2]  233 	ldw	x, (0x08, sp)
      0086AE 89               [ 2]  234 	pushw	x
      0086AF 1E 08            [ 2]  235 	ldw	x, (0x08, sp)
      0086B1 89               [ 2]  236 	pushw	x
      0086B2 7B 09            [ 1]  237 	ld	a, (0x09, sp)
      0086B4 88               [ 1]  238 	push	a
      0086B5 CD 86 08         [ 4]  239 	call	_osalAddTimer
      0086B8 5B 07            [ 2]  240 	addw	sp, #7
                                    241 ;	./src/OSAL_Timers.c: 208: return ( (newTimer != NULL) ? SUCCESS : NO_TIMER_AVAIL );
      0086BA 5D               [ 2]  242 	tnzw	x
      0086BB 27 02            [ 1]  243 	jreq	00111$
      0086BD 4F               [ 1]  244 	clr	a
      0086BE 81               [ 4]  245 	ret
      0086BF                        246 00111$:
      0086BF A6 08            [ 1]  247 	ld	a, #0x08
                                    248 ;	./src/OSAL_Timers.c: 209: }
      0086C1 81               [ 4]  249 	ret
                                    250 ;	./src/OSAL_Timers.c: 226: uint8 osal_start_reload_timer( uint8 taskID, uint16 event_id, uint32 timeout_value )
                                    251 ;	-----------------------------------------
                                    252 ;	 function osal_start_reload_timer
                                    253 ;	-----------------------------------------
      0086C2                        254 _osal_start_reload_timer:
      0086C2 89               [ 2]  255 	pushw	x
                                    256 ;	./src/OSAL_Timers.c: 231: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      0086C3 9B               [ 1]  257 	sim
      0086C4 9D               [ 1]  258 	nop
      0086C5 9D               [ 1]  259 	nop
                                    260 ;	./src/OSAL_Timers.c: 234: newTimer = osalAddTimer( taskID, event_id, timeout_value );
      0086C6 1E 0A            [ 2]  261 	ldw	x, (0x0a, sp)
      0086C8 89               [ 2]  262 	pushw	x
      0086C9 1E 0A            [ 2]  263 	ldw	x, (0x0a, sp)
      0086CB 89               [ 2]  264 	pushw	x
      0086CC 1E 0A            [ 2]  265 	ldw	x, (0x0a, sp)
      0086CE 89               [ 2]  266 	pushw	x
      0086CF 7B 0B            [ 1]  267 	ld	a, (0x0b, sp)
      0086D1 88               [ 1]  268 	push	a
      0086D2 CD 86 08         [ 4]  269 	call	_osalAddTimer
      0086D5 5B 07            [ 2]  270 	addw	sp, #7
                                    271 ;	./src/OSAL_Timers.c: 235: if ( newTimer )
      0086D7 1F 01            [ 2]  272 	ldw	(0x01, sp), x
      0086D9 27 0C            [ 1]  273 	jreq	00109$
                                    274 ;	./src/OSAL_Timers.c: 238: newTimer->reloadTimeout = timeout_value;
      0086DB 1E 01            [ 2]  275 	ldw	x, (0x01, sp)
      0086DD 1C 00 09         [ 2]  276 	addw	x, #0x0009
      0086E0 16 0A            [ 2]  277 	ldw	y, (0x0a, sp)
      0086E2 EF 02            [ 2]  278 	ldw	(0x2, x), y
      0086E4 16 08            [ 2]  279 	ldw	y, (0x08, sp)
      0086E6 FF               [ 2]  280 	ldw	(x), y
                                    281 ;	./src/OSAL_Timers.c: 241: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
      0086E7                        282 00109$:
                                    283 ;	./src/OSAL_Timers.c: 243: return ( (newTimer != NULL) ? SUCCESS : NO_TIMER_AVAIL );
      0086E7 1E 01            [ 2]  284 	ldw	x, (0x01, sp)
      0086E9 27 02            [ 1]  285 	jreq	00113$
      0086EB 4F               [ 1]  286 	clr	a
      0086EC C5                     287 	.byte 0xc5
      0086ED                        288 00113$:
      0086ED A6 08            [ 1]  289 	ld	a, #0x08
      0086EF                        290 00114$:
                                    291 ;	./src/OSAL_Timers.c: 244: }
      0086EF 85               [ 2]  292 	popw	x
      0086F0 81               [ 4]  293 	ret
                                    294 ;	./src/OSAL_Timers.c: 260: uint8 osal_stop_timerEx( uint8 task_id, uint16 event_id )
                                    295 ;	-----------------------------------------
                                    296 ;	 function osal_stop_timerEx
                                    297 ;	-----------------------------------------
      0086F1                        298 _osal_stop_timerEx:
                                    299 ;	./src/OSAL_Timers.c: 265: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      0086F1 9B               [ 1]  300 	sim
      0086F2 9D               [ 1]  301 	nop
      0086F3 9D               [ 1]  302 	nop
                                    303 ;	./src/OSAL_Timers.c: 268: foundTimer = osalFindTimer( task_id, event_id );
      0086F4 1E 04            [ 2]  304 	ldw	x, (0x04, sp)
      0086F6 89               [ 2]  305 	pushw	x
      0086F7 7B 05            [ 1]  306 	ld	a, (0x05, sp)
      0086F9 88               [ 1]  307 	push	a
      0086FA CD 86 7C         [ 4]  308 	call	_osalFindTimer
      0086FD 5B 03            [ 2]  309 	addw	sp, #3
                                    310 ;	./src/OSAL_Timers.c: 269: if ( foundTimer )
      0086FF 5D               [ 2]  311 	tnzw	x
      008700 27 07            [ 1]  312 	jreq	00109$
                                    313 ;	./src/OSAL_Timers.c: 271: osalDeleteTimer( foundTimer );
      008702 89               [ 2]  314 	pushw	x
      008703 89               [ 2]  315 	pushw	x
      008704 CD 86 98         [ 4]  316 	call	_osalDeleteTimer
      008707 85               [ 2]  317 	popw	x
      008708 85               [ 2]  318 	popw	x
                                    319 ;	./src/OSAL_Timers.c: 274: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
      008709                        320 00109$:
                                    321 ;	./src/OSAL_Timers.c: 276: return ( (foundTimer != NULL) ? SUCCESS : INVALID_EVENT_ID );
      008709 5D               [ 2]  322 	tnzw	x
      00870A 27 02            [ 1]  323 	jreq	00113$
      00870C 4F               [ 1]  324 	clr	a
      00870D 81               [ 4]  325 	ret
      00870E                        326 00113$:
      00870E A6 06            [ 1]  327 	ld	a, #0x06
                                    328 ;	./src/OSAL_Timers.c: 277: }
      008710 81               [ 4]  329 	ret
                                    330 ;	./src/OSAL_Timers.c: 289: uint32 osal_get_timeoutEx( uint8 task_id, uint16 event_id )
                                    331 ;	-----------------------------------------
                                    332 ;	 function osal_get_timeoutEx
                                    333 ;	-----------------------------------------
      008711                        334 _osal_get_timeoutEx:
      008711 52 04            [ 2]  335 	sub	sp, #4
                                    336 ;	./src/OSAL_Timers.c: 292: uint32 rtrn = 0;
      008713 5F               [ 1]  337 	clrw	x
      008714 1F 03            [ 2]  338 	ldw	(0x03, sp), x
      008716 1F 01            [ 2]  339 	ldw	(0x01, sp), x
                                    340 ;	./src/OSAL_Timers.c: 295: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      008718 9B               [ 1]  341 	sim
      008719 9D               [ 1]  342 	nop
      00871A 9D               [ 1]  343 	nop
                                    344 ;	./src/OSAL_Timers.c: 297: tmr = osalFindTimer( task_id, event_id );
      00871B 1E 08            [ 2]  345 	ldw	x, (0x08, sp)
      00871D 89               [ 2]  346 	pushw	x
      00871E 7B 09            [ 1]  347 	ld	a, (0x09, sp)
      008720 88               [ 1]  348 	push	a
      008721 CD 86 7C         [ 4]  349 	call	_osalFindTimer
      008724 5B 03            [ 2]  350 	addw	sp, #3
      008726 90 93            [ 1]  351 	ldw	y, x
                                    352 ;	./src/OSAL_Timers.c: 299: if ( tmr )
      008728 5D               [ 2]  353 	tnzw	x
      008729 27 0A            [ 1]  354 	jreq	00109$
                                    355 ;	./src/OSAL_Timers.c: 301: rtrn = tmr->timeout.time32;
      00872B 93               [ 1]  356 	ldw	x, y
      00872C 90 EE 04         [ 2]  357 	ldw	y, (0x4, y)
      00872F EE 02            [ 2]  358 	ldw	x, (0x2, x)
      008731 17 03            [ 2]  359 	ldw	(0x03, sp), y
      008733 1F 01            [ 2]  360 	ldw	(0x01, sp), x
                                    361 ;	./src/OSAL_Timers.c: 304: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
      008735                        362 00109$:
                                    363 ;	./src/OSAL_Timers.c: 306: return rtrn;
      008735 1E 03            [ 2]  364 	ldw	x, (0x03, sp)
      008737 16 01            [ 2]  365 	ldw	y, (0x01, sp)
                                    366 ;	./src/OSAL_Timers.c: 307: }
      008739 5B 04            [ 2]  367 	addw	sp, #4
      00873B 81               [ 4]  368 	ret
                                    369 ;	./src/OSAL_Timers.c: 318: uint8 osal_timer_num_active( void )
                                    370 ;	-----------------------------------------
                                    371 ;	 function osal_timer_num_active
                                    372 ;	-----------------------------------------
      00873C                        373 _osal_timer_num_active:
                                    374 ;	./src/OSAL_Timers.c: 324: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      00873C 9B               [ 1]  375 	sim
      00873D 9D               [ 1]  376 	nop
      00873E 9D               [ 1]  377 	nop
                                    378 ;	./src/OSAL_Timers.c: 327: srchTimer = timerHead;
      00873F CE 04 08         [ 2]  379 	ldw	x, _timerHead+0
                                    380 ;	./src/OSAL_Timers.c: 330: while ( srchTimer != NULL )
      008742 4F               [ 1]  381 	clr	a
      008743                        382 00107$:
      008743 5D               [ 2]  383 	tnzw	x
      008744 26 01            [ 1]  384 	jrne	00125$
      008746 81               [ 4]  385 	ret
      008747                        386 00125$:
                                    387 ;	./src/OSAL_Timers.c: 332: num_timers++;
      008747 4C               [ 1]  388 	inc	a
                                    389 ;	./src/OSAL_Timers.c: 333: srchTimer = srchTimer->next;
      008748 FE               [ 2]  390 	ldw	x, (x)
      008749 20 F8            [ 2]  391 	jra	00107$
                                    392 ;	./src/OSAL_Timers.c: 336: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
                                    393 ;	./src/OSAL_Timers.c: 338: return num_timers;
                                    394 ;	./src/OSAL_Timers.c: 339: }
      00874B 81               [ 4]  395 	ret
                                    396 ;	./src/OSAL_Timers.c: 350: void osalTimerUpdate( uint32 updateTime )
                                    397 ;	-----------------------------------------
                                    398 ;	 function osalTimerUpdate
                                    399 ;	-----------------------------------------
      00874C                        400 _osalTimerUpdate:
      00874C 52 1A            [ 2]  401 	sub	sp, #26
                                    402 ;	./src/OSAL_Timers.c: 357: timeUnion.time32 = updateTime;
      00874E 16 1F            [ 2]  403 	ldw	y, (0x1f, sp)
      008750 17 07            [ 2]  404 	ldw	(0x07, sp), y
      008752 16 1D            [ 2]  405 	ldw	y, (0x1d, sp)
      008754 17 05            [ 2]  406 	ldw	(0x05, sp), y
                                    407 ;	./src/OSAL_Timers.c: 359: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      008756 9B               [ 1]  408 	sim
      008757 9D               [ 1]  409 	nop
      008758 9D               [ 1]  410 	nop
                                    411 ;	./src/OSAL_Timers.c: 361: osal_systemClock += updateTime;
      008759 90 CE 04 0C      [ 2]  412 	ldw	y, _osal_systemClock+2
      00875D 72 F9 1F         [ 2]  413 	addw	y, (0x1f, sp)
      008760 CE 04 0A         [ 2]  414 	ldw	x, _osal_systemClock+0
      008763 24 01            [ 1]  415 	jrnc	00240$
      008765 5C               [ 1]  416 	incw	x
      008766                        417 00240$:
      008766 72 FB 1D         [ 2]  418 	addw	x, (0x1d, sp)
      008769 90 CF 04 0C      [ 2]  419 	ldw	_osal_systemClock+2, y
      00876D CF 04 0A         [ 2]  420 	ldw	_osal_systemClock+0, x
                                    421 ;	./src/OSAL_Timers.c: 365: if ( timerHead != NULL )
      008770 CE 04 08         [ 2]  422 	ldw	x, _timerHead+0
      008773 26 03            [ 1]  423 	jrne	00241$
      008775 CC 89 1B         [ 2]  424 	jp	00153$
      008778                        425 00241$:
                                    426 ;	./src/OSAL_Timers.c: 368: srchTimer = timerHead;
      008778 CE 04 08         [ 2]  427 	ldw	x, _timerHead+0
      00877B 1F 09            [ 2]  428 	ldw	(0x09, sp), x
                                    429 ;	./src/OSAL_Timers.c: 369: prevTimer = (void *)NULL;
      00877D 5F               [ 1]  430 	clrw	x
      00877E 1F 0B            [ 2]  431 	ldw	(0x0b, sp), x
                                    432 ;	./src/OSAL_Timers.c: 372: while ( srchTimer )
      008780                        433 00148$:
      008780 1E 09            [ 2]  434 	ldw	x, (0x09, sp)
      008782 26 03            [ 1]  435 	jrne	00242$
      008784 CC 89 1B         [ 2]  436 	jp	00153$
      008787                        437 00242$:
                                    438 ;	./src/OSAL_Timers.c: 374: osalTimerRec_t *freeTimer = NULL;
      008787 5F               [ 1]  439 	clrw	x
      008788 1F 0D            [ 2]  440 	ldw	(0x0d, sp), x
                                    441 ;	./src/OSAL_Timers.c: 376: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      00878A 9B               [ 1]  442 	sim
      00878B 9D               [ 1]  443 	nop
      00878C 9D               [ 1]  444 	nop
                                    445 ;	./src/OSAL_Timers.c: 379: if ((timeUnion.time16[1] == 0) && (timeUnion.time8[1] == 0))
      00878D 1E 07            [ 2]  446 	ldw	x, (0x07, sp)
                                    447 ;	./src/OSAL_Timers.c: 382: if (srchTimer->timeout.time8[0] >= timeUnion.time8[0])
      00878F 16 09            [ 2]  448 	ldw	y, (0x09, sp)
      008791 90 5C            [ 1]  449 	incw	y
      008793 90 5C            [ 1]  450 	incw	y
      008795 17 0F            [ 2]  451 	ldw	(0x0f, sp), y
                                    452 ;	./src/OSAL_Timers.c: 379: if ((timeUnion.time16[1] == 0) && (timeUnion.time8[1] == 0))
      008797 5D               [ 2]  453 	tnzw	x
      008798 26 75            [ 1]  454 	jrne	00125$
      00879A 7B 06            [ 1]  455 	ld	a, (0x06, sp)
      00879C 26 71            [ 1]  456 	jrne	00125$
                                    457 ;	./src/OSAL_Timers.c: 382: if (srchTimer->timeout.time8[0] >= timeUnion.time8[0])
      00879E 1E 0F            [ 2]  458 	ldw	x, (0x0f, sp)
      0087A0 F6               [ 1]  459 	ld	a, (x)
      0087A1 6B 1A            [ 1]  460 	ld	(0x1a, sp), a
      0087A3 7B 05            [ 1]  461 	ld	a, (0x05, sp)
      0087A5 11 1A            [ 1]  462 	cp	a, (0x1a, sp)
      0087A7 22 0F            [ 1]  463 	jrugt	00119$
                                    464 ;	./src/OSAL_Timers.c: 385: srchTimer->timeout.time8[0] -= timeUnion.time8[0];
      0087A9 7B 05            [ 1]  465 	ld	a, (0x05, sp)
      0087AB 6B 1A            [ 1]  466 	ld	(0x1a, sp), a
      0087AD 1E 0F            [ 2]  467 	ldw	x, (0x0f, sp)
      0087AF F6               [ 1]  468 	ld	a, (x)
      0087B0 10 1A            [ 1]  469 	sub	a, (0x1a, sp)
      0087B2 1E 0F            [ 2]  470 	ldw	x, (0x0f, sp)
      0087B4 F7               [ 1]  471 	ld	(x), a
      0087B5 CC 88 5E         [ 2]  472 	jp	00126$
      0087B8                        473 00119$:
                                    474 ;	./src/OSAL_Timers.c: 390: if (srchTimer->timeout.time32 > timeUnion.time32)
      0087B8 1E 0F            [ 2]  475 	ldw	x, (0x0f, sp)
      0087BA E6 03            [ 1]  476 	ld	a, (0x3, x)
      0087BC 6B 1A            [ 1]  477 	ld	(0x1a, sp), a
      0087BE E6 02            [ 1]  478 	ld	a, (0x2, x)
      0087C0 FE               [ 2]  479 	ldw	x, (x)
      0087C1 1F 17            [ 2]  480 	ldw	(0x17, sp), x
      0087C3 1E 07            [ 2]  481 	ldw	x, (0x07, sp)
      0087C5 16 05            [ 2]  482 	ldw	y, (0x05, sp)
      0087C7 88               [ 1]  483 	push	a
      0087C8 9F               [ 1]  484 	ld	a, xl
      0087C9 11 1B            [ 1]  485 	cp	a, (0x1b, sp)
      0087CB 9E               [ 1]  486 	ld	a, xh
      0087CC 12 01            [ 1]  487 	sbc	a, (1, sp)
      0087CE 90 9F            [ 1]  488 	ld	a, yl
      0087D0 12 19            [ 1]  489 	sbc	a, (0x19, sp)
      0087D2 90 9E            [ 1]  490 	ld	a, yh
      0087D4 12 18            [ 1]  491 	sbc	a, (0x18, sp)
      0087D6 5B 01            [ 2]  492 	addw	sp, #1
      0087D8 24 2C            [ 1]  493 	jrnc	00116$
                                    494 ;	./src/OSAL_Timers.c: 392: srchTimer->timeout.time32 -= timeUnion.time32;
      0087DA 1E 0F            [ 2]  495 	ldw	x, (0x0f, sp)
      0087DC 90 93            [ 1]  496 	ldw	y, x
      0087DE 90 EE 02         [ 2]  497 	ldw	y, (0x2, y)
      0087E1 FE               [ 2]  498 	ldw	x, (x)
      0087E2 1F 01            [ 2]  499 	ldw	(0x01, sp), x
      0087E4 1E 07            [ 2]  500 	ldw	x, (0x07, sp)
      0087E6 1F 15            [ 2]  501 	ldw	(0x15, sp), x
      0087E8 1E 05            [ 2]  502 	ldw	x, (0x05, sp)
      0087EA 72 F2 15         [ 2]  503 	subw	y, (0x15, sp)
      0087ED 7B 02            [ 1]  504 	ld	a, (0x02, sp)
      0087EF 89               [ 2]  505 	pushw	x
      0087F0 12 02            [ 1]  506 	sbc	a, (2, sp)
      0087F2 85               [ 2]  507 	popw	x
      0087F3 6B 18            [ 1]  508 	ld	(0x18, sp), a
      0087F5 7B 01            [ 1]  509 	ld	a, (0x01, sp)
      0087F7 89               [ 2]  510 	pushw	x
      0087F8 12 01            [ 1]  511 	sbc	a, (1, sp)
      0087FA 85               [ 2]  512 	popw	x
      0087FB 6B 17            [ 1]  513 	ld	(0x17, sp), a
      0087FD 1E 0F            [ 2]  514 	ldw	x, (0x0f, sp)
      0087FF EF 02            [ 2]  515 	ldw	(0x2, x), y
      008801 16 17            [ 2]  516 	ldw	y, (0x17, sp)
      008803 FF               [ 2]  517 	ldw	(x), y
      008804 20 58            [ 2]  518 	jra	00126$
      008806                        519 00116$:
                                    520 ;	./src/OSAL_Timers.c: 396: srchTimer->timeout.time32 = 0;
      008806 1E 0F            [ 2]  521 	ldw	x, (0x0f, sp)
      008808 90 5F            [ 1]  522 	clrw	y
      00880A EF 02            [ 2]  523 	ldw	(0x2, x), y
      00880C FF               [ 2]  524 	ldw	(x), y
      00880D 20 4F            [ 2]  525 	jra	00126$
      00880F                        526 00125$:
                                    527 ;	./src/OSAL_Timers.c: 403: if (srchTimer->timeout.time32 > timeUnion.time32)
      00880F 1E 0F            [ 2]  528 	ldw	x, (0x0f, sp)
      008811 90 93            [ 1]  529 	ldw	y, x
      008813 90 EE 02         [ 2]  530 	ldw	y, (0x2, y)
      008816 17 19            [ 2]  531 	ldw	(0x19, sp), y
      008818 FE               [ 2]  532 	ldw	x, (x)
      008819 1F 17            [ 2]  533 	ldw	(0x17, sp), x
      00881B 1E 07            [ 2]  534 	ldw	x, (0x07, sp)
      00881D 16 05            [ 2]  535 	ldw	y, (0x05, sp)
      00881F 13 19            [ 2]  536 	cpw	x, (0x19, sp)
      008821 90 9F            [ 1]  537 	ld	a, yl
      008823 12 18            [ 1]  538 	sbc	a, (0x18, sp)
      008825 90 9E            [ 1]  539 	ld	a, yh
      008827 12 17            [ 1]  540 	sbc	a, (0x17, sp)
      008829 24 2C            [ 1]  541 	jrnc	00122$
                                    542 ;	./src/OSAL_Timers.c: 405: srchTimer->timeout.time32 -= timeUnion.time32;
      00882B 1E 0F            [ 2]  543 	ldw	x, (0x0f, sp)
      00882D 90 93            [ 1]  544 	ldw	y, x
      00882F 90 EE 02         [ 2]  545 	ldw	y, (0x2, y)
      008832 FE               [ 2]  546 	ldw	x, (x)
      008833 1F 01            [ 2]  547 	ldw	(0x01, sp), x
      008835 1E 07            [ 2]  548 	ldw	x, (0x07, sp)
      008837 1F 15            [ 2]  549 	ldw	(0x15, sp), x
      008839 1E 05            [ 2]  550 	ldw	x, (0x05, sp)
      00883B 72 F2 15         [ 2]  551 	subw	y, (0x15, sp)
      00883E 7B 02            [ 1]  552 	ld	a, (0x02, sp)
      008840 89               [ 2]  553 	pushw	x
      008841 12 02            [ 1]  554 	sbc	a, (2, sp)
      008843 85               [ 2]  555 	popw	x
      008844 6B 18            [ 1]  556 	ld	(0x18, sp), a
      008846 7B 01            [ 1]  557 	ld	a, (0x01, sp)
      008848 89               [ 2]  558 	pushw	x
      008849 12 01            [ 1]  559 	sbc	a, (1, sp)
      00884B 85               [ 2]  560 	popw	x
      00884C 6B 17            [ 1]  561 	ld	(0x17, sp), a
      00884E 1E 0F            [ 2]  562 	ldw	x, (0x0f, sp)
      008850 EF 02            [ 2]  563 	ldw	(0x2, x), y
      008852 16 17            [ 2]  564 	ldw	y, (0x17, sp)
      008854 FF               [ 2]  565 	ldw	(x), y
      008855 20 07            [ 2]  566 	jra	00126$
      008857                        567 00122$:
                                    568 ;	./src/OSAL_Timers.c: 409: srchTimer->timeout.time32 = 0;
      008857 1E 0F            [ 2]  569 	ldw	x, (0x0f, sp)
      008859 90 5F            [ 1]  570 	clrw	y
      00885B EF 02            [ 2]  571 	ldw	(0x2, x), y
      00885D FF               [ 2]  572 	ldw	(x), y
      00885E                        573 00126$:
                                    574 ;	./src/OSAL_Timers.c: 414: if ( (srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0) &&
      00885E 1E 0F            [ 2]  575 	ldw	x, (0x0f, sp)
      008860 FE               [ 2]  576 	ldw	x, (x)
      008861 1F 19            [ 2]  577 	ldw	(0x19, sp), x
      008863 1E 09            [ 2]  578 	ldw	x, (0x09, sp)
      008865 5C               [ 1]  579 	incw	x
      008866 5C               [ 1]  580 	incw	x
                                    581 ;	./src/OSAL_Timers.c: 415: (srchTimer->reloadTimeout) && (srchTimer->event_flag) )
      008867 16 09            [ 2]  582 	ldw	y, (0x09, sp)
      008869 72 A9 00 06      [ 2]  583 	addw	y, #0x0006
      00886D 17 11            [ 2]  584 	ldw	(0x11, sp), y
                                    585 ;	./src/OSAL_Timers.c: 414: if ( (srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0) &&
      00886F 5C               [ 1]  586 	incw	x
      008870 5C               [ 1]  587 	incw	x
      008871 1F 13            [ 2]  588 	ldw	(0x13, sp), x
      008873 1E 19            [ 2]  589 	ldw	x, (0x19, sp)
      008875 26 3B            [ 1]  590 	jrne	00129$
      008877 1E 13            [ 2]  591 	ldw	x, (0x13, sp)
      008879 FE               [ 2]  592 	ldw	x, (x)
      00887A 26 36            [ 1]  593 	jrne	00129$
                                    594 ;	./src/OSAL_Timers.c: 415: (srchTimer->reloadTimeout) && (srchTimer->event_flag) )
      00887C 1E 09            [ 2]  595 	ldw	x, (0x09, sp)
      00887E 1C 00 09         [ 2]  596 	addw	x, #0x0009
      008881 1F 15            [ 2]  597 	ldw	(0x15, sp), x
      008883 90 93            [ 1]  598 	ldw	y, x
      008885 90 EE 02         [ 2]  599 	ldw	y, (0x2, y)
      008888 FE               [ 2]  600 	ldw	x, (x)
      008889 90 5D            [ 2]  601 	tnzw	y
      00888B 26 03            [ 1]  602 	jrne	00250$
      00888D 5D               [ 2]  603 	tnzw	x
      00888E 27 22            [ 1]  604 	jreq	00129$
      008890                        605 00250$:
      008890 1E 11            [ 2]  606 	ldw	x, (0x11, sp)
      008892 FE               [ 2]  607 	ldw	x, (x)
      008893 27 1D            [ 1]  608 	jreq	00129$
                                    609 ;	./src/OSAL_Timers.c: 418: osal_set_event( srchTimer->task_id, srchTimer->event_flag );
      008895 16 09            [ 2]  610 	ldw	y, (0x09, sp)
      008897 90 E6 08         [ 1]  611 	ld	a, (0x8, y)
      00889A 89               [ 2]  612 	pushw	x
      00889B 88               [ 1]  613 	push	a
      00889C CD 83 3A         [ 4]  614 	call	_osal_set_event
      00889F 5B 03            [ 2]  615 	addw	sp, #3
                                    616 ;	./src/OSAL_Timers.c: 421: srchTimer->timeout.time32 = srchTimer->reloadTimeout;
      0088A1 1E 15            [ 2]  617 	ldw	x, (0x15, sp)
      0088A3 90 93            [ 1]  618 	ldw	y, x
      0088A5 90 EE 02         [ 2]  619 	ldw	y, (0x2, y)
      0088A8 FE               [ 2]  620 	ldw	x, (x)
      0088A9 1F 17            [ 2]  621 	ldw	(0x17, sp), x
      0088AB 1E 0F            [ 2]  622 	ldw	x, (0x0f, sp)
      0088AD EF 02            [ 2]  623 	ldw	(0x2, x), y
      0088AF 16 17            [ 2]  624 	ldw	y, (0x17, sp)
      0088B1 FF               [ 2]  625 	ldw	(x), y
      0088B2                        626 00129$:
                                    627 ;	./src/OSAL_Timers.c: 425: if ( ((srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0)) ||
      0088B2 1E 0F            [ 2]  628 	ldw	x, (0x0f, sp)
      0088B4 FE               [ 2]  629 	ldw	x, (x)
      0088B5 1F 19            [ 2]  630 	ldw	(0x19, sp), x
                                    631 ;	./src/OSAL_Timers.c: 431: timerHead = srchTimer->next;
      0088B7 1E 09            [ 2]  632 	ldw	x, (0x09, sp)
      0088B9 FE               [ 2]  633 	ldw	x, (x)
      0088BA 1F 17            [ 2]  634 	ldw	(0x17, sp), x
      0088BC 90 93            [ 1]  635 	ldw	y, x
                                    636 ;	./src/OSAL_Timers.c: 425: if ( ((srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0)) ||
      0088BE 1E 19            [ 2]  637 	ldw	x, (0x19, sp)
      0088C0 26 05            [ 1]  638 	jrne	00140$
      0088C2 1E 13            [ 2]  639 	ldw	x, (0x13, sp)
      0088C4 FE               [ 2]  640 	ldw	x, (x)
      0088C5 27 05            [ 1]  641 	jreq	00136$
      0088C7                        642 00140$:
                                    643 ;	./src/OSAL_Timers.c: 426: (srchTimer->event_flag == 0) )
      0088C7 1E 11            [ 2]  644 	ldw	x, (0x11, sp)
      0088C9 FE               [ 2]  645 	ldw	x, (x)
      0088CA 26 1A            [ 1]  646 	jrne	00137$
      0088CC                        647 00136$:
                                    648 ;	./src/OSAL_Timers.c: 429: if ( prevTimer == NULL )
      0088CC 1E 0B            [ 2]  649 	ldw	x, (0x0b, sp)
      0088CE 26 06            [ 1]  650 	jrne	00134$
                                    651 ;	./src/OSAL_Timers.c: 431: timerHead = srchTimer->next;
      0088D0 90 CF 04 08      [ 2]  652 	ldw	_timerHead+0, y
      0088D4 20 05            [ 2]  653 	jra	00135$
      0088D6                        654 00134$:
                                    655 ;	./src/OSAL_Timers.c: 435: prevTimer->next = srchTimer->next;
      0088D6 1E 0B            [ 2]  656 	ldw	x, (0x0b, sp)
      0088D8 16 17            [ 2]  657 	ldw	y, (0x17, sp)
      0088DA FF               [ 2]  658 	ldw	(x), y
      0088DB                        659 00135$:
                                    660 ;	./src/OSAL_Timers.c: 439: freeTimer = srchTimer;
      0088DB 16 09            [ 2]  661 	ldw	y, (0x09, sp)
      0088DD 17 0D            [ 2]  662 	ldw	(0x0d, sp), y
                                    663 ;	./src/OSAL_Timers.c: 442: srchTimer = srchTimer->next;
      0088DF 1E 09            [ 2]  664 	ldw	x, (0x09, sp)
      0088E1 FE               [ 2]  665 	ldw	x, (x)
      0088E2 1F 09            [ 2]  666 	ldw	(0x09, sp), x
      0088E4 20 06            [ 2]  667 	jra	00141$
      0088E6                        668 00137$:
                                    669 ;	./src/OSAL_Timers.c: 447: prevTimer = srchTimer;
      0088E6 1E 09            [ 2]  670 	ldw	x, (0x09, sp)
      0088E8 1F 0B            [ 2]  671 	ldw	(0x0b, sp), x
                                    672 ;	./src/OSAL_Timers.c: 448: srchTimer = srchTimer->next;
      0088EA 17 09            [ 2]  673 	ldw	(0x09, sp), y
                                    674 ;	./src/OSAL_Timers.c: 451: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
      0088EC                        675 00141$:
                                    676 ;	./src/OSAL_Timers.c: 453: if ( freeTimer )
      0088EC 1E 0D            [ 2]  677 	ldw	x, (0x0d, sp)
      0088EE 26 03            [ 1]  678 	jrne	00256$
      0088F0 CC 87 80         [ 2]  679 	jp	00148$
      0088F3                        680 00256$:
                                    681 ;	./src/OSAL_Timers.c: 455: if ( (freeTimer->timeout.time16[0] == 0) && (freeTimer->timeout.time16[1] == 0) )
      0088F3 1E 0D            [ 2]  682 	ldw	x, (0x0d, sp)
      0088F5 EE 02            [ 2]  683 	ldw	x, (0x2, x)
      0088F7 26 18            [ 1]  684 	jrne	00144$
      0088F9 1E 0D            [ 2]  685 	ldw	x, (0x0d, sp)
      0088FB 5C               [ 1]  686 	incw	x
      0088FC 5C               [ 1]  687 	incw	x
      0088FD EE 02            [ 2]  688 	ldw	x, (0x2, x)
      0088FF 26 10            [ 1]  689 	jrne	00144$
                                    690 ;	./src/OSAL_Timers.c: 457: osal_set_event( freeTimer->task_id, freeTimer->event_flag );
      008901 1E 0D            [ 2]  691 	ldw	x, (0x0d, sp)
      008903 EE 06            [ 2]  692 	ldw	x, (0x6, x)
      008905 16 0D            [ 2]  693 	ldw	y, (0x0d, sp)
      008907 90 E6 08         [ 1]  694 	ld	a, (0x8, y)
      00890A 89               [ 2]  695 	pushw	x
      00890B 88               [ 1]  696 	push	a
      00890C CD 83 3A         [ 4]  697 	call	_osal_set_event
      00890F 5B 03            [ 2]  698 	addw	sp, #3
      008911                        699 00144$:
                                    700 ;	./src/OSAL_Timers.c: 459: osal_mem_free( freeTimer );
      008911 1E 0D            [ 2]  701 	ldw	x, (0x0d, sp)
      008913 89               [ 2]  702 	pushw	x
      008914 CD 85 87         [ 4]  703 	call	_osal_mem_free
      008917 85               [ 2]  704 	popw	x
      008918 CC 87 80         [ 2]  705 	jp	00148$
      00891B                        706 00153$:
                                    707 ;	./src/OSAL_Timers.c: 463: }
      00891B 5B 1A            [ 2]  708 	addw	sp, #26
      00891D 81               [ 4]  709 	ret
                                    710 ;	./src/OSAL_Timers.c: 544: uint32 osal_GetSystemClock( void )
                                    711 ;	-----------------------------------------
                                    712 ;	 function osal_GetSystemClock
                                    713 ;	-----------------------------------------
      00891E                        714 _osal_GetSystemClock:
                                    715 ;	./src/OSAL_Timers.c: 546: return ( osal_systemClock );
      00891E CE 04 0C         [ 2]  716 	ldw	x, _osal_systemClock+2
      008921 90 CE 04 0A      [ 2]  717 	ldw	y, _osal_systemClock+0
                                    718 ;	./src/OSAL_Timers.c: 547: }
      008925 81               [ 4]  719 	ret
                                    720 	.area CODE
                                    721 	.area CONST
                                    722 	.area INITIALIZER
                                    723 	.area CABS (ABS)
