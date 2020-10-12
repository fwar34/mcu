;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module OSAL_Timers
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _osal_set_event
	.globl _osal_mem_free
	.globl _osal_mem_alloc
	.globl _timerHead
	.globl _osalTimerInit
	.globl _osalAddTimer
	.globl _osalFindTimer
	.globl _osalDeleteTimer
	.globl _osal_start_timerEx
	.globl _osal_start_reload_timer
	.globl _osal_stop_timerEx
	.globl _osal_get_timeoutEx
	.globl _osal_timer_num_active
	.globl _osalTimerUpdate
	.globl _osal_GetSystemClock
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_timerHead::
	.ds 2
_osal_systemClock:
	.ds 4
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
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
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	./src/OSAL_Timers.c: 54: void osalTimerInit( void )
;	-----------------------------------------
;	 function osalTimerInit
;	-----------------------------------------
_osalTimerInit:
;	./src/OSAL_Timers.c: 56: osal_systemClock = 0;
	clrw	x
	ldw	_osal_systemClock+2, x
	ldw	_osal_systemClock+0, x
;	./src/OSAL_Timers.c: 57: }
	ret
;	./src/OSAL_Timers.c: 71: osalTimerRec_t * osalAddTimer( uint8 task_id, uint16 event_flag, uint32 timeout )
;	-----------------------------------------
;	 function osalAddTimer
;	-----------------------------------------
_osalAddTimer:
	pushw	x
;	./src/OSAL_Timers.c: 77: newTimer = osalFindTimer( task_id, event_flag );
	ldw	x, (0x06, sp)
	pushw	x
	ld	a, (0x07, sp)
	push	a
	call	_osalFindTimer
	addw	sp, #3
;	./src/OSAL_Timers.c: 78: if ( newTimer )
	ldw	(0x01, sp), x
	jreq	00111$
;	./src/OSAL_Timers.c: 81: newTimer->timeout.time32 = timeout;
	ldw	x, (0x01, sp)
	incw	x
	incw	x
	ldw	y, (0x0a, sp)
	ldw	(0x2, x), y
	ldw	y, (0x08, sp)
	ldw	(x), y
;	./src/OSAL_Timers.c: 83: return ( newTimer );
	ldw	x, (0x01, sp)
	jra	00113$
00111$:
;	./src/OSAL_Timers.c: 88: newTimer = osal_mem_alloc( sizeof( osalTimerRec_t ) );
	push	#0x0d
	push	#0x00
	call	_osal_mem_alloc
	addw	sp, #2
;	./src/OSAL_Timers.c: 90: if ( newTimer )
	ldw	(0x01, sp), x
	jreq	00108$
;	./src/OSAL_Timers.c: 93: newTimer->task_id = task_id;
	ldw	x, (0x01, sp)
	ld	a, (0x05, sp)
	ld	(0x0008, x), a
;	./src/OSAL_Timers.c: 94: newTimer->event_flag = event_flag;
	ldw	x, (0x01, sp)
	ldw	y, (0x06, sp)
	ldw	(0x0006, x), y
;	./src/OSAL_Timers.c: 95: newTimer->timeout.time32 = timeout;
	ldw	x, (0x01, sp)
	incw	x
	incw	x
	ldw	y, (0x0a, sp)
	ldw	(0x2, x), y
	ldw	y, (0x08, sp)
	ldw	(x), y
;	./src/OSAL_Timers.c: 96: newTimer->next = (void *)NULL;
	ldw	x, (0x01, sp)
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL_Timers.c: 97: newTimer->reloadTimeout = 0;
	ldw	x, (0x01, sp)
	addw	x, #0x0009
	clrw	y
	ldw	(0x2, x), y
	ldw	(x), y
;	./src/OSAL_Timers.c: 100: if ( timerHead == NULL )
	ldw	x, _timerHead+0
	jrne	00105$
;	./src/OSAL_Timers.c: 103: timerHead = newTimer;
	ldw	x, (0x01, sp)
	ldw	_timerHead+0, x
	jra	00106$
00105$:
;	./src/OSAL_Timers.c: 108: srchTimer = timerHead;
	ldw	y, _timerHead+0
;	./src/OSAL_Timers.c: 111: while ( srchTimer->next )
00101$:
	ldw	x, y
	ldw	x, (x)
	jreq	00103$
;	./src/OSAL_Timers.c: 112: srchTimer = srchTimer->next;
	exgw	x, y
	jra	00101$
00103$:
;	./src/OSAL_Timers.c: 115: srchTimer->next = newTimer;
	ldw	x, (0x01, sp)
	ldw	(y), x
00106$:
;	./src/OSAL_Timers.c: 118: return ( newTimer );
	ldw	x, (0x01, sp)
;	./src/OSAL_Timers.c: 122: return ( (osalTimerRec_t *)NULL );
	.byte 0x21
00108$:
	clrw	x
00113$:
;	./src/OSAL_Timers.c: 125: }
	addw	sp, #2
	ret
;	./src/OSAL_Timers.c: 138: osalTimerRec_t *osalFindTimer( uint8 task_id, uint16 event_flag )
;	-----------------------------------------
;	 function osalFindTimer
;	-----------------------------------------
_osalFindTimer:
;	./src/OSAL_Timers.c: 143: srchTimer = timerHead;
	ldw	y, _timerHead+0
;	./src/OSAL_Timers.c: 146: while ( srchTimer )
00104$:
	tnzw	y
	jreq	00106$
;	./src/OSAL_Timers.c: 148: if ( srchTimer->event_flag == event_flag &&
	ldw	x, y
	ldw	x, (0x6, x)
	cpw	x, (0x04, sp)
	jrne	00102$
;	./src/OSAL_Timers.c: 149: srchTimer->task_id == task_id )
	ldw	x, y
	ld	a, (0x8, x)
	cp	a, (0x03, sp)
	jreq	00106$
;	./src/OSAL_Timers.c: 151: break;
00102$:
;	./src/OSAL_Timers.c: 155: srchTimer = srchTimer->next;
	ldw	y, (y)
	jra	00104$
00106$:
;	./src/OSAL_Timers.c: 158: return ( srchTimer );
	ldw	x, y
;	./src/OSAL_Timers.c: 159: }
	ret
;	./src/OSAL_Timers.c: 171: void osalDeleteTimer( osalTimerRec_t *rmTimer )
;	-----------------------------------------
;	 function osalDeleteTimer
;	-----------------------------------------
_osalDeleteTimer:
;	./src/OSAL_Timers.c: 174: if ( rmTimer )
	ldw	x, (0x03, sp)
	jrne	00110$
	ret
00110$:
;	./src/OSAL_Timers.c: 178: rmTimer->event_flag = 0;
	ldw	x, (0x03, sp)
	addw	x, #0x0006
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL_Timers.c: 180: }
	ret
;	./src/OSAL_Timers.c: 196: uint8 osal_start_timerEx( uint8 taskID, uint16 event_id, uint32 timeout_value )
;	-----------------------------------------
;	 function osal_start_timerEx
;	-----------------------------------------
_osal_start_timerEx:
;	./src/OSAL_Timers.c: 201: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 204: newTimer = osalAddTimer( taskID, event_id, timeout_value );
	ldw	x, (0x08, sp)
	pushw	x
	ldw	x, (0x08, sp)
	pushw	x
	ldw	x, (0x08, sp)
	pushw	x
	ld	a, (0x09, sp)
	push	a
	call	_osalAddTimer
	addw	sp, #7
;	./src/OSAL_Timers.c: 208: return ( (newTimer != NULL) ? SUCCESS : NO_TIMER_AVAIL );
	tnzw	x
	jreq	00111$
	clr	a
	ret
00111$:
	ld	a, #0x08
;	./src/OSAL_Timers.c: 209: }
	ret
;	./src/OSAL_Timers.c: 226: uint8 osal_start_reload_timer( uint8 taskID, uint16 event_id, uint32 timeout_value )
;	-----------------------------------------
;	 function osal_start_reload_timer
;	-----------------------------------------
_osal_start_reload_timer:
	pushw	x
;	./src/OSAL_Timers.c: 231: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 234: newTimer = osalAddTimer( taskID, event_id, timeout_value );
	ldw	x, (0x0a, sp)
	pushw	x
	ldw	x, (0x0a, sp)
	pushw	x
	ldw	x, (0x0a, sp)
	pushw	x
	ld	a, (0x0b, sp)
	push	a
	call	_osalAddTimer
	addw	sp, #7
;	./src/OSAL_Timers.c: 235: if ( newTimer )
	ldw	(0x01, sp), x
	jreq	00109$
;	./src/OSAL_Timers.c: 238: newTimer->reloadTimeout = timeout_value;
	ldw	x, (0x01, sp)
	addw	x, #0x0009
	ldw	y, (0x0a, sp)
	ldw	(0x2, x), y
	ldw	y, (0x08, sp)
	ldw	(x), y
;	./src/OSAL_Timers.c: 241: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
00109$:
;	./src/OSAL_Timers.c: 243: return ( (newTimer != NULL) ? SUCCESS : NO_TIMER_AVAIL );
	ldw	x, (0x01, sp)
	jreq	00113$
	clr	a
	.byte 0xc5
00113$:
	ld	a, #0x08
00114$:
;	./src/OSAL_Timers.c: 244: }
	popw	x
	ret
;	./src/OSAL_Timers.c: 260: uint8 osal_stop_timerEx( uint8 task_id, uint16 event_id )
;	-----------------------------------------
;	 function osal_stop_timerEx
;	-----------------------------------------
_osal_stop_timerEx:
;	./src/OSAL_Timers.c: 265: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 268: foundTimer = osalFindTimer( task_id, event_id );
	ldw	x, (0x04, sp)
	pushw	x
	ld	a, (0x05, sp)
	push	a
	call	_osalFindTimer
	addw	sp, #3
;	./src/OSAL_Timers.c: 269: if ( foundTimer )
	tnzw	x
	jreq	00109$
;	./src/OSAL_Timers.c: 271: osalDeleteTimer( foundTimer );
	pushw	x
	pushw	x
	call	_osalDeleteTimer
	popw	x
	popw	x
;	./src/OSAL_Timers.c: 274: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
00109$:
;	./src/OSAL_Timers.c: 276: return ( (foundTimer != NULL) ? SUCCESS : INVALID_EVENT_ID );
	tnzw	x
	jreq	00113$
	clr	a
	ret
00113$:
	ld	a, #0x06
;	./src/OSAL_Timers.c: 277: }
	ret
;	./src/OSAL_Timers.c: 289: uint32 osal_get_timeoutEx( uint8 task_id, uint16 event_id )
;	-----------------------------------------
;	 function osal_get_timeoutEx
;	-----------------------------------------
_osal_get_timeoutEx:
	sub	sp, #4
;	./src/OSAL_Timers.c: 292: uint32 rtrn = 0;
	clrw	x
	ldw	(0x03, sp), x
	ldw	(0x01, sp), x
;	./src/OSAL_Timers.c: 295: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 297: tmr = osalFindTimer( task_id, event_id );
	ldw	x, (0x08, sp)
	pushw	x
	ld	a, (0x09, sp)
	push	a
	call	_osalFindTimer
	addw	sp, #3
	ldw	y, x
;	./src/OSAL_Timers.c: 299: if ( tmr )
	tnzw	x
	jreq	00109$
;	./src/OSAL_Timers.c: 301: rtrn = tmr->timeout.time32;
	ldw	x, y
	ldw	y, (0x4, y)
	ldw	x, (0x2, x)
	ldw	(0x03, sp), y
	ldw	(0x01, sp), x
;	./src/OSAL_Timers.c: 304: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
00109$:
;	./src/OSAL_Timers.c: 306: return rtrn;
	ldw	x, (0x03, sp)
	ldw	y, (0x01, sp)
;	./src/OSAL_Timers.c: 307: }
	addw	sp, #4
	ret
;	./src/OSAL_Timers.c: 318: uint8 osal_timer_num_active( void )
;	-----------------------------------------
;	 function osal_timer_num_active
;	-----------------------------------------
_osal_timer_num_active:
;	./src/OSAL_Timers.c: 324: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 327: srchTimer = timerHead;
	ldw	x, _timerHead+0
;	./src/OSAL_Timers.c: 330: while ( srchTimer != NULL )
	clr	a
00107$:
	tnzw	x
	jrne	00125$
	ret
00125$:
;	./src/OSAL_Timers.c: 332: num_timers++;
	inc	a
;	./src/OSAL_Timers.c: 333: srchTimer = srchTimer->next;
	ldw	x, (x)
	jra	00107$
;	./src/OSAL_Timers.c: 336: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
;	./src/OSAL_Timers.c: 338: return num_timers;
;	./src/OSAL_Timers.c: 339: }
	ret
;	./src/OSAL_Timers.c: 350: void osalTimerUpdate( uint32 updateTime )
;	-----------------------------------------
;	 function osalTimerUpdate
;	-----------------------------------------
_osalTimerUpdate:
	sub	sp, #26
;	./src/OSAL_Timers.c: 357: timeUnion.time32 = updateTime;
	ldw	y, (0x1f, sp)
	ldw	(0x07, sp), y
	ldw	y, (0x1d, sp)
	ldw	(0x05, sp), y
;	./src/OSAL_Timers.c: 359: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 361: osal_systemClock += updateTime;
	ldw	y, _osal_systemClock+2
	addw	y, (0x1f, sp)
	ldw	x, _osal_systemClock+0
	jrnc	00240$
	incw	x
00240$:
	addw	x, (0x1d, sp)
	ldw	_osal_systemClock+2, y
	ldw	_osal_systemClock+0, x
;	./src/OSAL_Timers.c: 365: if ( timerHead != NULL )
	ldw	x, _timerHead+0
	jrne	00241$
	jp	00153$
00241$:
;	./src/OSAL_Timers.c: 368: srchTimer = timerHead;
	ldw	x, _timerHead+0
	ldw	(0x09, sp), x
;	./src/OSAL_Timers.c: 369: prevTimer = (void *)NULL;
	clrw	x
	ldw	(0x0b, sp), x
;	./src/OSAL_Timers.c: 372: while ( srchTimer )
00148$:
	ldw	x, (0x09, sp)
	jrne	00242$
	jp	00153$
00242$:
;	./src/OSAL_Timers.c: 374: osalTimerRec_t *freeTimer = NULL;
	clrw	x
	ldw	(0x0d, sp), x
;	./src/OSAL_Timers.c: 376: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Timers.c: 379: if ((timeUnion.time16[1] == 0) && (timeUnion.time8[1] == 0))
	ldw	x, (0x07, sp)
;	./src/OSAL_Timers.c: 382: if (srchTimer->timeout.time8[0] >= timeUnion.time8[0])
	ldw	y, (0x09, sp)
	incw	y
	incw	y
	ldw	(0x0f, sp), y
;	./src/OSAL_Timers.c: 379: if ((timeUnion.time16[1] == 0) && (timeUnion.time8[1] == 0))
	tnzw	x
	jrne	00125$
	ld	a, (0x06, sp)
	jrne	00125$
;	./src/OSAL_Timers.c: 382: if (srchTimer->timeout.time8[0] >= timeUnion.time8[0])
	ldw	x, (0x0f, sp)
	ld	a, (x)
	ld	(0x1a, sp), a
	ld	a, (0x05, sp)
	cp	a, (0x1a, sp)
	jrugt	00119$
;	./src/OSAL_Timers.c: 385: srchTimer->timeout.time8[0] -= timeUnion.time8[0];
	ld	a, (0x05, sp)
	ld	(0x1a, sp), a
	ldw	x, (0x0f, sp)
	ld	a, (x)
	sub	a, (0x1a, sp)
	ldw	x, (0x0f, sp)
	ld	(x), a
	jp	00126$
00119$:
;	./src/OSAL_Timers.c: 390: if (srchTimer->timeout.time32 > timeUnion.time32)
	ldw	x, (0x0f, sp)
	ld	a, (0x3, x)
	ld	(0x1a, sp), a
	ld	a, (0x2, x)
	ldw	x, (x)
	ldw	(0x17, sp), x
	ldw	x, (0x07, sp)
	ldw	y, (0x05, sp)
	push	a
	ld	a, xl
	cp	a, (0x1b, sp)
	ld	a, xh
	sbc	a, (1, sp)
	ld	a, yl
	sbc	a, (0x19, sp)
	ld	a, yh
	sbc	a, (0x18, sp)
	addw	sp, #1
	jrnc	00116$
;	./src/OSAL_Timers.c: 392: srchTimer->timeout.time32 -= timeUnion.time32;
	ldw	x, (0x0f, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	ldw	(0x01, sp), x
	ldw	x, (0x07, sp)
	ldw	(0x15, sp), x
	ldw	x, (0x05, sp)
	subw	y, (0x15, sp)
	ld	a, (0x02, sp)
	pushw	x
	sbc	a, (2, sp)
	popw	x
	ld	(0x18, sp), a
	ld	a, (0x01, sp)
	pushw	x
	sbc	a, (1, sp)
	popw	x
	ld	(0x17, sp), a
	ldw	x, (0x0f, sp)
	ldw	(0x2, x), y
	ldw	y, (0x17, sp)
	ldw	(x), y
	jra	00126$
00116$:
;	./src/OSAL_Timers.c: 396: srchTimer->timeout.time32 = 0;
	ldw	x, (0x0f, sp)
	clrw	y
	ldw	(0x2, x), y
	ldw	(x), y
	jra	00126$
00125$:
;	./src/OSAL_Timers.c: 403: if (srchTimer->timeout.time32 > timeUnion.time32)
	ldw	x, (0x0f, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	(0x19, sp), y
	ldw	x, (x)
	ldw	(0x17, sp), x
	ldw	x, (0x07, sp)
	ldw	y, (0x05, sp)
	cpw	x, (0x19, sp)
	ld	a, yl
	sbc	a, (0x18, sp)
	ld	a, yh
	sbc	a, (0x17, sp)
	jrnc	00122$
;	./src/OSAL_Timers.c: 405: srchTimer->timeout.time32 -= timeUnion.time32;
	ldw	x, (0x0f, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	ldw	(0x01, sp), x
	ldw	x, (0x07, sp)
	ldw	(0x15, sp), x
	ldw	x, (0x05, sp)
	subw	y, (0x15, sp)
	ld	a, (0x02, sp)
	pushw	x
	sbc	a, (2, sp)
	popw	x
	ld	(0x18, sp), a
	ld	a, (0x01, sp)
	pushw	x
	sbc	a, (1, sp)
	popw	x
	ld	(0x17, sp), a
	ldw	x, (0x0f, sp)
	ldw	(0x2, x), y
	ldw	y, (0x17, sp)
	ldw	(x), y
	jra	00126$
00122$:
;	./src/OSAL_Timers.c: 409: srchTimer->timeout.time32 = 0;
	ldw	x, (0x0f, sp)
	clrw	y
	ldw	(0x2, x), y
	ldw	(x), y
00126$:
;	./src/OSAL_Timers.c: 414: if ( (srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0) &&
	ldw	x, (0x0f, sp)
	ldw	x, (x)
	ldw	(0x19, sp), x
	ldw	x, (0x09, sp)
	incw	x
	incw	x
;	./src/OSAL_Timers.c: 415: (srchTimer->reloadTimeout) && (srchTimer->event_flag) )
	ldw	y, (0x09, sp)
	addw	y, #0x0006
	ldw	(0x11, sp), y
;	./src/OSAL_Timers.c: 414: if ( (srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0) &&
	incw	x
	incw	x
	ldw	(0x13, sp), x
	ldw	x, (0x19, sp)
	jrne	00129$
	ldw	x, (0x13, sp)
	ldw	x, (x)
	jrne	00129$
;	./src/OSAL_Timers.c: 415: (srchTimer->reloadTimeout) && (srchTimer->event_flag) )
	ldw	x, (0x09, sp)
	addw	x, #0x0009
	ldw	(0x15, sp), x
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	tnzw	y
	jrne	00250$
	tnzw	x
	jreq	00129$
00250$:
	ldw	x, (0x11, sp)
	ldw	x, (x)
	jreq	00129$
;	./src/OSAL_Timers.c: 418: osal_set_event( srchTimer->task_id, srchTimer->event_flag );
	ldw	y, (0x09, sp)
	ld	a, (0x8, y)
	pushw	x
	push	a
	call	_osal_set_event
	addw	sp, #3
;	./src/OSAL_Timers.c: 421: srchTimer->timeout.time32 = srchTimer->reloadTimeout;
	ldw	x, (0x15, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	ldw	(0x17, sp), x
	ldw	x, (0x0f, sp)
	ldw	(0x2, x), y
	ldw	y, (0x17, sp)
	ldw	(x), y
00129$:
;	./src/OSAL_Timers.c: 425: if ( ((srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0)) ||
	ldw	x, (0x0f, sp)
	ldw	x, (x)
	ldw	(0x19, sp), x
;	./src/OSAL_Timers.c: 431: timerHead = srchTimer->next;
	ldw	x, (0x09, sp)
	ldw	x, (x)
	ldw	(0x17, sp), x
	ldw	y, x
;	./src/OSAL_Timers.c: 425: if ( ((srchTimer->timeout.time16[0] == 0) && (srchTimer->timeout.time16[1] == 0)) ||
	ldw	x, (0x19, sp)
	jrne	00140$
	ldw	x, (0x13, sp)
	ldw	x, (x)
	jreq	00136$
00140$:
;	./src/OSAL_Timers.c: 426: (srchTimer->event_flag == 0) )
	ldw	x, (0x11, sp)
	ldw	x, (x)
	jrne	00137$
00136$:
;	./src/OSAL_Timers.c: 429: if ( prevTimer == NULL )
	ldw	x, (0x0b, sp)
	jrne	00134$
;	./src/OSAL_Timers.c: 431: timerHead = srchTimer->next;
	ldw	_timerHead+0, y
	jra	00135$
00134$:
;	./src/OSAL_Timers.c: 435: prevTimer->next = srchTimer->next;
	ldw	x, (0x0b, sp)
	ldw	y, (0x17, sp)
	ldw	(x), y
00135$:
;	./src/OSAL_Timers.c: 439: freeTimer = srchTimer;
	ldw	y, (0x09, sp)
	ldw	(0x0d, sp), y
;	./src/OSAL_Timers.c: 442: srchTimer = srchTimer->next;
	ldw	x, (0x09, sp)
	ldw	x, (x)
	ldw	(0x09, sp), x
	jra	00141$
00137$:
;	./src/OSAL_Timers.c: 447: prevTimer = srchTimer;
	ldw	x, (0x09, sp)
	ldw	(0x0b, sp), x
;	./src/OSAL_Timers.c: 448: srchTimer = srchTimer->next;
	ldw	(0x09, sp), y
;	./src/OSAL_Timers.c: 451: HAL_EXIT_CRITICAL_SECTION( intState );   // Re-enable interrupts.
00141$:
;	./src/OSAL_Timers.c: 453: if ( freeTimer )
	ldw	x, (0x0d, sp)
	jrne	00256$
	jp	00148$
00256$:
;	./src/OSAL_Timers.c: 455: if ( (freeTimer->timeout.time16[0] == 0) && (freeTimer->timeout.time16[1] == 0) )
	ldw	x, (0x0d, sp)
	ldw	x, (0x2, x)
	jrne	00144$
	ldw	x, (0x0d, sp)
	incw	x
	incw	x
	ldw	x, (0x2, x)
	jrne	00144$
;	./src/OSAL_Timers.c: 457: osal_set_event( freeTimer->task_id, freeTimer->event_flag );
	ldw	x, (0x0d, sp)
	ldw	x, (0x6, x)
	ldw	y, (0x0d, sp)
	ld	a, (0x8, y)
	pushw	x
	push	a
	call	_osal_set_event
	addw	sp, #3
00144$:
;	./src/OSAL_Timers.c: 459: osal_mem_free( freeTimer );
	ldw	x, (0x0d, sp)
	pushw	x
	call	_osal_mem_free
	popw	x
	jp	00148$
00153$:
;	./src/OSAL_Timers.c: 463: }
	addw	sp, #26
	ret
;	./src/OSAL_Timers.c: 544: uint32 osal_GetSystemClock( void )
;	-----------------------------------------
;	 function osal_GetSystemClock
;	-----------------------------------------
_osal_GetSystemClock:
;	./src/OSAL_Timers.c: 546: return ( osal_systemClock );
	ldw	x, _osal_systemClock+2
	ldw	y, _osal_systemClock+0
;	./src/OSAL_Timers.c: 547: }
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
