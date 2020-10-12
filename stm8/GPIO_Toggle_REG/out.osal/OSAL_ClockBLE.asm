;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module OSAL_ClockBLE
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _osalTimerUpdate
	.globl _OSAL_timeSeconds
	.globl _osalTimeUpdate
	.globl _osal_setClock
	.globl _osal_getClock
	.globl _osal_ConvertUTCTime
	.globl _osal_ConvertUTCSecs
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
_timeMSec:
	.ds 2
_OSAL_timeSeconds::
	.ds 4
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
;	./src/OSAL_ClockBLE.c: 59: void osalTimeUpdate( void )
;	-----------------------------------------
;	 function osalTimeUpdate
;	-----------------------------------------
_osalTimeUpdate:
;	./src/OSAL_ClockBLE.c: 61: osalTimerUpdate( 1 );
	push	#0x01
	clrw	x
	pushw	x
	push	#0x00
	call	_osalTimerUpdate
	addw	sp, #4
;	./src/OSAL_ClockBLE.c: 62: osalClockUpdate( 1 );
	push	#0x01
	push	#0x00
	call	_osalClockUpdate
	popw	x
;	./src/OSAL_ClockBLE.c: 63: }
	ret
;	./src/OSAL_ClockBLE.c: 74: static void osalClockUpdate( uint16 elapsedMSec )
;	-----------------------------------------
;	 function osalClockUpdate
;	-----------------------------------------
_osalClockUpdate:
	sub	sp, #8
;	./src/OSAL_ClockBLE.c: 77: timeMSec += elapsedMSec;
	ldw	x, _timeMSec+0
	addw	x, (0x0b, sp)
	ldw	_timeMSec+0, x
;	./src/OSAL_ClockBLE.c: 80: if ( timeMSec >= 1000 )
	ldw	y, _timeMSec+0
	cpw	y, #0x03e8
	jrc	00103$
;	./src/OSAL_ClockBLE.c: 82: OSAL_timeSeconds += timeMSec / 1000;
	pushw	y
	ldw	x, y
	ldw	y, #0x03e8
	divw	x, y
	popw	y
	clr	a
	clr	(0x01, sp)
	addw	x, _OSAL_timeSeconds+2
	adc	a, _OSAL_timeSeconds+1
	ld	(0x06, sp), a
	ld	a, (0x01, sp)
	adc	a, _OSAL_timeSeconds+0
	ld	(0x05, sp), a
	ldw	_OSAL_timeSeconds+2, x
	ldw	x, (0x05, sp)
	ldw	_OSAL_timeSeconds+0, x
;	./src/OSAL_ClockBLE.c: 83: timeMSec = timeMSec % 1000;
	ldw	x, y
	ldw	y, #0x03e8
	divw	x, y
	ldw	_timeMSec+0, y
00103$:
;	./src/OSAL_ClockBLE.c: 85: }
	addw	sp, #8
	ret
;	./src/OSAL_ClockBLE.c: 98: void osal_setClock( UTCTime newTime )
;	-----------------------------------------
;	 function osal_setClock
;	-----------------------------------------
_osal_setClock:
;	./src/OSAL_ClockBLE.c: 100: OSAL_timeSeconds = newTime;
	ldw	x, (0x05, sp)
	ldw	y, (0x03, sp)
	ldw	_OSAL_timeSeconds+2, x
	ldw	_OSAL_timeSeconds+0, y
;	./src/OSAL_ClockBLE.c: 101: }
	ret
;	./src/OSAL_ClockBLE.c: 115: UTCTime osal_getClock( void )
;	-----------------------------------------
;	 function osal_getClock
;	-----------------------------------------
_osal_getClock:
;	./src/OSAL_ClockBLE.c: 117: return ( OSAL_timeSeconds );
	ldw	x, _OSAL_timeSeconds+2
	ldw	y, _OSAL_timeSeconds+0
;	./src/OSAL_ClockBLE.c: 118: }
	ret
;	./src/OSAL_ClockBLE.c: 132: void osal_ConvertUTCTime( UTCTimeStruct *tm, UTCTime secTime )
;	-----------------------------------------
;	 function osal_ConvertUTCTime
;	-----------------------------------------
_osal_ConvertUTCTime:
	sub	sp, #18
;	./src/OSAL_ClockBLE.c: 136: uint32 day = secTime % DAY;
	push	#0x80
	push	#0x51
	push	#0x01
	push	#0x00
	ldw	x, (0x1d, sp)
	pushw	x
	ldw	x, (0x1d, sp)
	pushw	x
	call	__modulong
	addw	sp, #8
	ldw	(0x0f, sp), x
	ldw	(0x0d, sp), y
;	./src/OSAL_ClockBLE.c: 137: tm->seconds = day % 60UL;
	ldw	y, (0x15, sp)
	ldw	(0x01, sp), y
	push	#0x3c
	clrw	x
	pushw	x
	push	#0x00
	ldw	x, (0x13, sp)
	pushw	x
	ldw	x, (0x13, sp)
	pushw	x
	call	__modulong
	addw	sp, #8
	ld	a, xl
	ldw	x, (0x01, sp)
	ld	(x), a
;	./src/OSAL_ClockBLE.c: 138: tm->minutes = (day % 3600UL) / 60UL;
	ldw	x, (0x01, sp)
	incw	x
	ldw	(0x11, sp), x
	push	#0x10
	push	#0x0e
	clrw	x
	pushw	x
	ldw	x, (0x13, sp)
	pushw	x
	ldw	x, (0x13, sp)
	pushw	x
	call	__modulong
	addw	sp, #8
	push	#0x3c
	push	#0x00
	push	#0x00
	push	#0x00
	pushw	x
	pushw	y
	call	__divulong
	addw	sp, #8
	ld	a, xl
	ldw	x, (0x11, sp)
	ld	(x), a
;	./src/OSAL_ClockBLE.c: 139: tm->hour = day / 3600UL;
	ldw	x, (0x01, sp)
	incw	x
	incw	x
	ldw	(0x11, sp), x
	push	#0x10
	push	#0x0e
	clrw	x
	pushw	x
	ldw	x, (0x13, sp)
	pushw	x
	ldw	x, (0x13, sp)
	pushw	x
	call	__divulong
	addw	sp, #8
	ld	a, xl
	ldw	x, (0x11, sp)
	ld	(x), a
;	./src/OSAL_ClockBLE.c: 144: uint16 numDays = secTime / DAY;
	push	#0x80
	push	#0x51
	push	#0x01
	push	#0x00
	ldw	x, (0x1d, sp)
	pushw	x
	ldw	x, (0x1d, sp)
	pushw	x
	call	__divulong
	addw	sp, #8
	ldw	(0x03, sp), x
;	./src/OSAL_ClockBLE.c: 145: tm->year = BEGYEAR;
	ldw	x, (0x01, sp)
	addw	x, #0x0005
	ldw	(0x05, sp), x
	ldw	y, #0x07d0
	ldw	(x), y
;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
00101$:
	ldw	x, (0x05, sp)
	ldw	x, (x)
	ldw	(0x07, sp), x
	pushw	x
	ldw	y, #0x0190
	divw	x, y
	ldw	(0x0b, sp), y
	popw	x
	pushw	x
	ldw	y, #0x0064
	divw	x, y
	ldw	(0x0d, sp), y
	popw	x
	ld	a, xl
	and	a, #0x03
	ld	(0x0e, sp), a
	clr	(0x0d, sp)
	ldw	x, (0x09, sp)
	jreq	00112$
	ldw	x, (0x0b, sp)
	jreq	00109$
	ldw	x, (0x0d, sp)
	jrne	00109$
00112$:
	ldw	x, #0x016e
	.byte 0xbc
00109$:
	ldw	x, #0x016d
00110$:
	ldw	y, (0x03, sp)
	ldw	(0x0f, sp), y
	ldw	(0x11, sp), x
	ldw	x, (0x0f, sp)
	cpw	x, (0x11, sp)
	jrc	00103$
;	./src/OSAL_ClockBLE.c: 148: numDays -= YearLength( tm->year );
	ldw	x, (0x09, sp)
	jreq	00120$
	ldw	x, (0x0b, sp)
	jreq	00117$
	ldw	x, (0x0d, sp)
	jrne	00117$
00120$:
	ldw	x, #0x016e
	.byte 0xbc
00117$:
	ldw	x, #0x016d
00118$:
	negw	x
	addw	x, (0x0f, sp)
	ldw	(0x03, sp), x
;	./src/OSAL_ClockBLE.c: 149: tm->year++;
	ldw	x, (0x07, sp)
	incw	x
	ldw	y, (0x05, sp)
	ldw	(y), x
	jra	00101$
00103$:
;	./src/OSAL_ClockBLE.c: 152: tm->month = 0;
	ldw	x, (0x01, sp)
	addw	x, #0x0004
	ldw	(0x0e, sp), x
	clr	(x)
;	./src/OSAL_ClockBLE.c: 153: while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
00104$:
	ldw	x, (0x0e, sp)
	ld	a, (x)
;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
	ldw	x, (0x05, sp)
	ldw	x, (x)
;	./src/OSAL_ClockBLE.c: 153: while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
	ldw	(0x11, sp), x
	ldw	y, #0x0190
	divw	x, y
	tnzw	y
	jreq	00126$
	ldw	x, (0x11, sp)
	ldw	y, #0x0064
	divw	x, y
	tnzw	y
	jreq	00125$
	push	a
	ld	a, (0x13, sp)
	bcp	a, #0x03
	pop	a
	jreq	00126$
00125$:
	clrw	x
	jra	00127$
00126$:
	exg	a, xl
	ld	a, #0x01
	exg	a, xl
00127$:
	push	a
	ld	a, xl
	push	a
	call	_monthLength
	popw	x
	ld	(0x12, sp), a
	clr	(0x11, sp)
	ldw	x, (0x03, sp)
	cpw	x, (0x11, sp)
	jrc	00106$
;	./src/OSAL_ClockBLE.c: 155: numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
	ldw	x, (0x0e, sp)
	ld	a, (x)
	ld	(0x10, sp), a
;	./src/OSAL_ClockBLE.c: 146: while ( numDays >= YearLength( tm->year ) )
	ldw	x, (0x05, sp)
	ldw	x, (x)
	ld	a, xl
;	./src/OSAL_ClockBLE.c: 155: numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
	pushw	x
	ld	xl, a
	ldw	y, #0x0190
	divw	x, y
	ldw	(0x13, sp), y
	popw	x
	ldw	y, (0x11, sp)
	jreq	00132$
	pushw	x
	ld	xl, a
	ldw	y, #0x0064
	divw	x, y
	popw	x
	tnzw	y
	jreq	00131$
	bcp	a, #0x03
	jreq	00132$
00131$:
	clrw	x
	jra	00133$
00132$:
	ld	a, #0x01
	ld	xl, a
00133$:
	ld	a, (0x10, sp)
	push	a
	ld	a, xl
	push	a
	call	_monthLength
	popw	x
	clrw	x
	ld	xl, a
	ldw	y, (0x03, sp)
	ldw	(0x11, sp), x
	subw	y, (0x11, sp)
	ldw	(0x03, sp), y
;	./src/OSAL_ClockBLE.c: 156: tm->month++;
	ldw	x, (0x0e, sp)
	inc	(x)
	jp	00104$
00106$:
;	./src/OSAL_ClockBLE.c: 159: tm->day = numDays;
	ldw	x, (0x01, sp)
	ld	a, (0x04, sp)
	ld	(0x0003, x), a
;	./src/OSAL_ClockBLE.c: 161: }
	addw	sp, #18
	ret
;	./src/OSAL_ClockBLE.c: 172: static uint8 monthLength( uint8 lpyr, uint8 mon )
;	-----------------------------------------
;	 function monthLength
;	-----------------------------------------
_monthLength:
;	./src/OSAL_ClockBLE.c: 174: uint8 days = 31;
	ld	a, #0x1f
	ld	xl, a
;	./src/OSAL_ClockBLE.c: 176: if ( mon == 1 ) // feb
	ld	a, (0x04, sp)
	dec	a
	jrne	00106$
;	./src/OSAL_ClockBLE.c: 178: days = ( 28 + lpyr );
	ld	a, (0x03, sp)
	add	a, #0x1c
	ld	xl, a
	jra	00107$
00106$:
;	./src/OSAL_ClockBLE.c: 182: if ( mon > 6 ) // aug-dec
	ld	a, (0x04, sp)
	cp	a, #0x06
	jrule	00102$
;	./src/OSAL_ClockBLE.c: 184: mon--;
	dec	(0x04, sp)
00102$:
;	./src/OSAL_ClockBLE.c: 187: if ( mon & 1 )
	ld	a, (0x04, sp)
	srl	a
	jrnc	00107$
;	./src/OSAL_ClockBLE.c: 189: days = 30;
	ld	a, #0x1e
	ld	xl, a
00107$:
;	./src/OSAL_ClockBLE.c: 193: return ( days );
	ld	a, xl
;	./src/OSAL_ClockBLE.c: 194: }
	ret
;	./src/OSAL_ClockBLE.c: 205: UTCTime osal_ConvertUTCSecs( UTCTimeStruct *tm )
;	-----------------------------------------
;	 function osal_ConvertUTCSecs
;	-----------------------------------------
_osal_ConvertUTCSecs:
	sub	sp, #12
;	./src/OSAL_ClockBLE.c: 210: seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;
	ldw	y, (0x0f, sp)
	ldw	(0x0b, sp), y
	ldw	x, y
	ld	a, (0x2, x)
	clrw	x
	ld	xl, a
	clrw	y
	pushw	x
	pushw	y
	push	#0x3c
	clrw	x
	pushw	x
	push	#0x00
	call	__mullong
	addw	sp, #8
	ldw	(0x09, sp), x
	ldw	(0x07, sp), y
	ldw	x, (0x0b, sp)
	ld	a, (0x1, x)
	clrw	y
	clrw	x
	ld	yl, a
	addw	y, (0x09, sp)
	ld	a, xl
	adc	a, (0x08, sp)
	rlwa	x
	adc	a, (0x07, sp)
	ld	xh, a
	pushw	y
	pushw	x
	push	#0x3c
	clrw	x
	pushw	x
	push	#0x00
	call	__mullong
	addw	sp, #8
	ldw	(0x09, sp), x
	ldw	(0x07, sp), y
	ldw	x, (0x0b, sp)
	ld	a, (x)
	clrw	y
	clrw	x
	ld	yl, a
	addw	y, (0x09, sp)
	ld	a, xl
	adc	a, (0x08, sp)
	rlwa	x
	adc	a, (0x07, sp)
	ld	xh, a
	ldw	(0x03, sp), y
	ldw	(0x01, sp), x
;	./src/OSAL_ClockBLE.c: 215: uint16 days = tm->day;
	ldw	x, (0x0b, sp)
	ld	a, (0x3, x)
	clrw	x
	ld	xl, a
	ldw	(0x05, sp), x
;	./src/OSAL_ClockBLE.c: 219: int8 month = tm->month;
	ldw	x, (0x0b, sp)
	ld	a, (0x4, x)
;	./src/OSAL_ClockBLE.c: 220: while ( --month >= 0 )
	ldw	y, (0x0b, sp)
	ldw	(0x07, sp), y
00101$:
	dec	a
;	./src/OSAL_ClockBLE.c: 222: days += monthLength( IsLeapYear( tm->year ), month );
	ldw	x, (0x07, sp)
	ldw	x, (0x5, x)
;	./src/OSAL_ClockBLE.c: 220: while ( --month >= 0 )
	tnz	a
	jrmi	00103$
;	./src/OSAL_ClockBLE.c: 222: days += monthLength( IsLeapYear( tm->year ), month );
	ldw	(0x09, sp), x
	ldw	y, #0x0190
	divw	x, y
	ldw	(0x0b, sp), y
	ldw	x, y
	jreq	00110$
	ldw	x, (0x09, sp)
	ldw	y, #0x0064
	divw	x, y
	tnzw	y
	jreq	00109$
	push	a
	ld	a, (0x0b, sp)
	bcp	a, #0x03
	pop	a
	jreq	00110$
00109$:
	clrw	x
	jra	00111$
00110$:
	exg	a, xl
	ld	a, #0x01
	exg	a, xl
00111$:
	push	a
	push	a
	pushw	x
	addw	sp, #1
	call	_monthLength
	popw	x
	ld	xl, a
	pop	a
	rlwa	x
	clr	a
	rrwa	x
	ldw	y, (0x05, sp)
	ldw	(0x0b, sp), x
	addw	y, (0x0b, sp)
	ldw	(0x05, sp), y
	jra	00101$
00103$:
;	./src/OSAL_ClockBLE.c: 228: uint16 year = tm->year;
;	./src/OSAL_ClockBLE.c: 229: while ( --year >= BEGYEAR )
	ldw	(0x0b, sp), x
00104$:
	ldw	x, (0x0b, sp)
	decw	x
	ldw	(0x0b, sp), x
	ldw	(0x07, sp), x
	cpw	x, #0x07d0
	jrc	00106$
;	./src/OSAL_ClockBLE.c: 231: days += YearLength( year );
	ldw	x, (0x07, sp)
	ldw	y, #0x0190
	divw	x, y
	tnzw	y
	jreq	00118$
	ldw	x, (0x07, sp)
	ldw	y, #0x0064
	divw	x, y
	ldw	(0x09, sp), y
	ldw	x, y
	jreq	00115$
	ld	a, (0x08, sp)
	bcp	a, #0x03
	jrne	00115$
00118$:
	ldw	x, #0x016e
	.byte 0xbc
00115$:
	ldw	x, #0x016d
00116$:
	ldw	y, (0x05, sp)
	ldw	(0x09, sp), y
	addw	x, (0x09, sp)
	ldw	(0x05, sp), x
	jra	00104$
00106$:
;	./src/OSAL_ClockBLE.c: 236: seconds += (days * DAY);
	ldw	y, (0x05, sp)
	clrw	x
	pushw	y
	pushw	x
	push	#0x80
	push	#0x51
	push	#0x01
	push	#0x00
	call	__mullong
	addw	sp, #8
	exgw	x, y
	addw	y, (0x03, sp)
	ld	a, xl
	adc	a, (0x02, sp)
	rlwa	x
	adc	a, (0x01, sp)
	ld	xh, a
	exgw	x, y
;	./src/OSAL_ClockBLE.c: 239: return ( seconds );
;	./src/OSAL_ClockBLE.c: 240: }
	addw	sp, #12
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
__xinit__timeMSec:
	.dw #0x0000
__xinit__OSAL_timeSeconds:
	.byte #0x00, #0x00, #0x00, #0x00	; 0
	.area CABS (ABS)
