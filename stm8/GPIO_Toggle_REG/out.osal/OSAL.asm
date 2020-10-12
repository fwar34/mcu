;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module OSAL
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _osalInitTasks
	.globl _osalTimerInit
	.globl _osal_mem_free
	.globl _osal_mem_alloc
	.globl _osal_mem_kick
	.globl _osal_mem_init
	.globl _memset
	.globl _osal_qHead
	.globl _osal_memcpy
	.globl _osal_revmemcpy
	.globl _osal_memdup
	.globl _osal_memcmp
	.globl _osal_memset
	.globl _osal_msg_allocate
	.globl _osal_msg_deallocate
	.globl _osal_msg_send
	.globl _osal_msg_push_front
	.globl _osal_msg_receive
	.globl _osal_msg_find
	.globl _osal_msg_enqueue
	.globl _osal_msg_dequeue
	.globl _osal_msg_push
	.globl _osal_msg_extract
	.globl _osal_msg_enqueue_max
	.globl _osal_set_event
	.globl _osal_clear_event
	.globl _osal_isr_register
	.globl _osal_int_enable
	.globl _osal_int_disable
	.globl _osal_init_system
	.globl _osal_start_system
	.globl _osal_run_system
	.globl _osal_self
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_osal_qHead::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
_activeTaskID:
	.ds 1
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
;	./src/OSAL.c: 49: void *osal_memcpy( void *dst, const void *src, unsigned int len )
;	-----------------------------------------
;	 function osal_memcpy
;	-----------------------------------------
_osal_memcpy:
	sub	sp, #6
;	./src/OSAL.c: 54: pSrc = src;
	ldw	y, (0x0b, sp)
;	./src/OSAL.c: 55: pDst = dst;
	ldw	x, (0x09, sp)
;	./src/OSAL.c: 57: while ( len-- )
	ldw	(0x03, sp), y
	ldw	y, (0x0d, sp)
	ldw	(0x05, sp), y
00101$:
	ldw	y, (0x05, sp)
	ldw	(0x01, sp), y
	ldw	y, (0x05, sp)
	decw	y
	ldw	(0x05, sp), y
	ldw	y, (0x01, sp)
	jreq	00108$
;	./src/OSAL.c: 58: *pDst++ = *pSrc++;
	ldw	y, (0x03, sp)
	ld	a, (y)
	ldw	y, (0x03, sp)
	incw	y
	ldw	(0x03, sp), y
	ld	(x), a
	incw	x
	jra	00101$
00108$:
;	./src/OSAL.c: 60: return ( pDst );
;	./src/OSAL.c: 61: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 80: void *osal_revmemcpy( void *dst, const void *src, unsigned int len )
;	-----------------------------------------
;	 function osal_revmemcpy
;	-----------------------------------------
_osal_revmemcpy:
	sub	sp, #6
;	./src/OSAL.c: 85: pSrc = src;
	ldw	y, (0x0b, sp)
;	./src/OSAL.c: 86: pSrc += (len-1);
	ldw	x, (0x0d, sp)
	decw	x
	ldw	(0x05, sp), x
	addw	y, (0x05, sp)
;	./src/OSAL.c: 87: pDst = dst;
	ldw	x, (0x09, sp)
;	./src/OSAL.c: 89: while ( len-- )
	ldw	(0x03, sp), y
	ldw	y, (0x0d, sp)
	ldw	(0x05, sp), y
00101$:
	ldw	y, (0x05, sp)
	ldw	(0x01, sp), y
	ldw	y, (0x05, sp)
	decw	y
	ldw	(0x05, sp), y
	ldw	y, (0x01, sp)
	jreq	00108$
;	./src/OSAL.c: 90: *pDst++ = *pSrc--;
	ldw	y, (0x03, sp)
	ld	a, (y)
	ldw	y, (0x03, sp)
	decw	y
	ldw	(0x03, sp), y
	ld	(x), a
	incw	x
	jra	00101$
00108$:
;	./src/OSAL.c: 92: return ( pDst );
;	./src/OSAL.c: 93: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 107: void *osal_memdup( const void *src, unsigned int len )
;	-----------------------------------------
;	 function osal_memdup
;	-----------------------------------------
_osal_memdup:
	pushw	x
;	./src/OSAL.c: 111: pDst = osal_mem_alloc( len );
	ldw	x, (0x07, sp)
	pushw	x
	call	_osal_mem_alloc
	addw	sp, #2
;	./src/OSAL.c: 114: VOID osal_memcpy( pDst, src, len );
	ldw	(0x01, sp), x
;	./src/OSAL.c: 112: if ( pDst )
	tnzw	x
	jreq	00102$
;	./src/OSAL.c: 114: VOID osal_memcpy( pDst, src, len );
	ldw	x, (0x07, sp)
	pushw	x
	ldw	x, (0x07, sp)
	pushw	x
	ldw	x, (0x05, sp)
	pushw	x
	call	_osal_memcpy
	addw	sp, #6
00102$:
;	./src/OSAL.c: 117: return ( (void *)pDst );
	ldw	x, (0x01, sp)
;	./src/OSAL.c: 118: }
	addw	sp, #2
	ret
;	./src/OSAL.c: 133: uint8 osal_memcmp( const void *src1, const void *src2, unsigned int len )
;	-----------------------------------------
;	 function osal_memcmp
;	-----------------------------------------
_osal_memcmp:
	sub	sp, #6
;	./src/OSAL.c: 138: pSrc1 = src1;
	ldw	y, (0x09, sp)
;	./src/OSAL.c: 139: pSrc2 = src2;
	ldw	x, (0x0b, sp)
;	./src/OSAL.c: 141: while ( len-- )
	ldw	(0x03, sp), y
	ldw	(0x05, sp), x
	ldw	y, (0x0d, sp)
00103$:
	ldw	(0x01, sp), y
	decw	y
	ldw	x, (0x01, sp)
	jreq	00105$
;	./src/OSAL.c: 143: if( *pSrc1++ != *pSrc2++ )
	ldw	x, (0x03, sp)
	ld	a, (x)
	ld	(0x02, sp), a
	ldw	x, (0x03, sp)
	incw	x
	ldw	(0x03, sp), x
	ldw	x, (0x05, sp)
	ld	a, (x)
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
	cp	a, (0x02, sp)
	jreq	00103$
;	./src/OSAL.c: 144: return FALSE;
	clr	a
;	./src/OSAL.c: 146: return TRUE;
	.byte 0xc5
00105$:
	ld	a, #0x01
00106$:
;	./src/OSAL.c: 147: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 163: void *osal_memset( void *dest, uint8 value, int len )
;	-----------------------------------------
;	 function osal_memset
;	-----------------------------------------
_osal_memset:
;	./src/OSAL.c: 165: return memset( dest, value, len );
	clrw	x
	ld	a, (0x05, sp)
	ld	xl, a
	ldw	y, (0x06, sp)
	pushw	y
	pushw	x
	ldw	x, (0x07, sp)
	pushw	x
	call	_memset
	addw	sp, #6
;	./src/OSAL.c: 166: }
	ret
;	./src/OSAL.c: 194: uint8 * osal_msg_allocate( uint16 len )
;	-----------------------------------------
;	 function osal_msg_allocate
;	-----------------------------------------
_osal_msg_allocate:
;	./src/OSAL.c: 198: if ( len == 0 )
;	./src/OSAL.c: 199: return ( NULL );
	ldw	x, (0x03, sp)
	jrne	00102$
	ret
00102$:
;	./src/OSAL.c: 201: hdr = (osal_msg_hdr_t *) osal_mem_alloc( (short)(len + sizeof( osal_msg_hdr_t )) );
	ldw	x, (0x03, sp)
	addw	x, #0x0005
	pushw	x
	call	_osal_mem_alloc
	addw	sp, #2
	exgw	x, y
;	./src/OSAL.c: 202: if ( hdr )
	tnzw	y
	jreq	00104$
;	./src/OSAL.c: 204: hdr->next = NULL;
	ldw	x, y
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL.c: 205: hdr->len = len;
	ldw	x, y
	incw	x
	incw	x
	ld	a, (0x04, sp)
	ld	(0x1, x), a
	ld	a, (0x03, sp)
	ld	(x), a
;	./src/OSAL.c: 206: hdr->dest_id = TASK_NO_TASK;
	ld	a, #0xff
	ld	(0x0004, y), a
;	./src/OSAL.c: 207: return ( (uint8 *) (hdr + 1) );
	ldw	x, y
	addw	x, #0x0005
	ret
00104$:
;	./src/OSAL.c: 210: return ( NULL );
	clrw	x
;	./src/OSAL.c: 211: }
	ret
;	./src/OSAL.c: 227: uint8 osal_msg_deallocate( uint8 *msg_ptr )
;	-----------------------------------------
;	 function osal_msg_deallocate
;	-----------------------------------------
_osal_msg_deallocate:
;	./src/OSAL.c: 231: if ( msg_ptr == NULL )
	ldw	x, (0x03, sp)
	jrne	00102$
;	./src/OSAL.c: 232: return ( INVALID_MSG_POINTER );
	ld	a, #0x05
	ret
00102$:
;	./src/OSAL.c: 235: if ( OSAL_MSG_ID( msg_ptr ) != TASK_NO_TASK )
	ldw	x, (0x03, sp)
	addw	x, #0xffff
	ld	a, (x)
	inc	a
	jreq	00104$
;	./src/OSAL.c: 236: return ( MSG_BUFFER_NOT_AVAIL );
	ld	a, #0x04
	ret
00104$:
;	./src/OSAL.c: 238: x = (uint8 *)((uint8 *)msg_ptr - sizeof( osal_msg_hdr_t ));
	ldw	x, (0x03, sp)
	subw	x, #0x0005
;	./src/OSAL.c: 240: osal_mem_free( (void *)x );
	pushw	x
	call	_osal_mem_free
	popw	x
;	./src/OSAL.c: 242: return ( SUCCESS );
	clr	a
;	./src/OSAL.c: 243: }
	ret
;	./src/OSAL.c: 262: uint8 osal_msg_send( uint8 destination_task, uint8 *msg_ptr )
;	-----------------------------------------
;	 function osal_msg_send
;	-----------------------------------------
_osal_msg_send:
;	./src/OSAL.c: 264: return ( osal_msg_enqueue_push( destination_task, msg_ptr, FALSE ) );
	push	#0x00
	ldw	x, (0x05, sp)
	pushw	x
	ld	a, (0x06, sp)
	push	a
	call	_osal_msg_enqueue_push
	addw	sp, #4
;	./src/OSAL.c: 265: }
	ret
;	./src/OSAL.c: 283: uint8 osal_msg_push_front( uint8 destination_task, uint8 *msg_ptr )
;	-----------------------------------------
;	 function osal_msg_push_front
;	-----------------------------------------
_osal_msg_push_front:
;	./src/OSAL.c: 285: return ( osal_msg_enqueue_push( destination_task, msg_ptr, TRUE ) );
	push	#0x01
	ldw	x, (0x05, sp)
	pushw	x
	ld	a, (0x06, sp)
	push	a
	call	_osal_msg_enqueue_push
	addw	sp, #4
;	./src/OSAL.c: 286: }
	ret
;	./src/OSAL.c: 306: static uint8 osal_msg_enqueue_push( uint8 destination_task, uint8 *msg_ptr, uint8 push )
;	-----------------------------------------
;	 function osal_msg_enqueue_push
;	-----------------------------------------
_osal_msg_enqueue_push:
;	./src/OSAL.c: 308: if ( msg_ptr == NULL )
	ldw	x, (0x04, sp)
	jrne	00102$
;	./src/OSAL.c: 310: return ( INVALID_MSG_POINTER );
	ld	a, #0x05
	ret
00102$:
;	./src/OSAL.c: 313: if ( destination_task >= tasksCnt )
	ld	a, _tasksCnt+0
	cp	a, (0x03, sp)
	jrugt	00104$
;	./src/OSAL.c: 315: osal_msg_deallocate( msg_ptr );
	ldw	x, (0x04, sp)
	pushw	x
	call	_osal_msg_deallocate
	popw	x
;	./src/OSAL.c: 316: return ( INVALID_TASK );
	ld	a, #0x03
	ret
00104$:
;	./src/OSAL.c: 320: if ( OSAL_MSG_NEXT( msg_ptr ) != NULL ||
	ldw	y, (0x04, sp)
	ldw	x, y
	addw	x, #0xfffb
	ldw	x, (x)
	jrne	00105$
;	./src/OSAL.c: 321: OSAL_MSG_ID( msg_ptr ) != TASK_NO_TASK )
	ldw	x, y
	decw	x
	ld	a, (x)
	inc	a
	jreq	00106$
00105$:
;	./src/OSAL.c: 323: osal_msg_deallocate( msg_ptr );
	ldw	x, (0x04, sp)
	pushw	x
	call	_osal_msg_deallocate
	popw	x
;	./src/OSAL.c: 324: return ( INVALID_MSG_POINTER );
	ld	a, #0x05
	ret
00106$:
;	./src/OSAL.c: 327: OSAL_MSG_ID( msg_ptr ) = destination_task;
	ld	a, (0x03, sp)
	ld	(x), a
;	./src/OSAL.c: 332: osal_msg_push( &osal_qHead, msg_ptr );
	ldw	x, (0x04, sp)
;	./src/OSAL.c: 329: if ( push == TRUE )
	ld	a, (0x06, sp)
	dec	a
	jrne	00109$
;	./src/OSAL.c: 332: osal_msg_push( &osal_qHead, msg_ptr );
	pushw	x
	push	#<(_osal_qHead + 0)
	push	#((_osal_qHead + 0) >> 8)
	call	_osal_msg_push
	addw	sp, #4
	jra	00110$
00109$:
;	./src/OSAL.c: 337: osal_msg_enqueue( &osal_qHead, msg_ptr );
	pushw	x
	push	#<(_osal_qHead + 0)
	push	#((_osal_qHead + 0) >> 8)
	call	_osal_msg_enqueue
	addw	sp, #4
00110$:
;	./src/OSAL.c: 341: osal_set_event( destination_task, SYS_EVENT_MSG );
	push	#0x00
	push	#0x80
	ld	a, (0x05, sp)
	push	a
	call	_osal_set_event
	addw	sp, #3
;	./src/OSAL.c: 343: return ( SUCCESS );
	clr	a
;	./src/OSAL.c: 344: }
	ret
;	./src/OSAL.c: 359: uint8 *osal_msg_receive( uint8 task_id )
;	-----------------------------------------
;	 function osal_msg_receive
;	-----------------------------------------
_osal_msg_receive:
	sub	sp, #6
;	./src/OSAL.c: 362: osal_msg_hdr_t *prevHdr = NULL;
	clrw	x
	ldw	(0x01, sp), x
;	./src/OSAL.c: 363: osal_msg_hdr_t *foundHdr = NULL;
	clrw	x
	ldw	(0x03, sp), x
;	./src/OSAL.c: 367: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 370: listHdr = osal_qHead;
	ldw	y, _osal_qHead+0
;	./src/OSAL.c: 373: while ( listHdr != NULL )
00114$:
	tnzw	y
	jreq	00116$
;	./src/OSAL.c: 375: if ( (listHdr - 1)->dest_id == task_id )
	ldw	x, y
	subw	x, #0x0005
	ldw	(0x05, sp), x
	ld	a, (0x4, x)
	cp	a, (0x09, sp)
	jrne	00111$
;	./src/OSAL.c: 377: if ( foundHdr == NULL )
	ldw	x, (0x03, sp)
	jrne	00116$
;	./src/OSAL.c: 380: foundHdr = listHdr;
	ldw	(0x03, sp), y
;	./src/OSAL.c: 385: break;
00111$:
;	./src/OSAL.c: 388: if ( foundHdr == NULL )
	ldw	x, (0x03, sp)
	jrne	00113$
;	./src/OSAL.c: 390: prevHdr = listHdr;
	ldw	(0x01, sp), y
00113$:
;	./src/OSAL.c: 392: listHdr = OSAL_MSG_NEXT( listHdr );
	ldw	x, (0x05, sp)
	ldw	x, (x)
	exgw	x, y
	jra	00114$
00116$:
;	./src/OSAL.c: 396: if ( listHdr != NULL )
	tnzw	y
	jreq	00118$
;	./src/OSAL.c: 399: osal_set_event( task_id, SYS_EVENT_MSG );
	push	#0x00
	push	#0x80
	ld	a, (0x0b, sp)
	push	a
	call	_osal_set_event
	addw	sp, #3
	jra	00119$
00118$:
;	./src/OSAL.c: 404: osal_clear_event( task_id, SYS_EVENT_MSG );
	push	#0x00
	push	#0x80
	ld	a, (0x0b, sp)
	push	a
	call	_osal_clear_event
	addw	sp, #3
00119$:
;	./src/OSAL.c: 408: if ( foundHdr != NULL )
	ldw	x, (0x03, sp)
	jreq	00122$
;	./src/OSAL.c: 411: osal_msg_extract( &osal_qHead, foundHdr, prevHdr );
	ldw	x, (0x01, sp)
	ldw	y, (0x03, sp)
	pushw	x
	pushw	y
	push	#<(_osal_qHead + 0)
	push	#((_osal_qHead + 0) >> 8)
	call	_osal_msg_extract
	addw	sp, #6
;	./src/OSAL.c: 415: HAL_EXIT_CRITICAL_SECTION(intState);
00122$:
;	./src/OSAL.c: 417: return ( (uint8*) foundHdr );
	ldw	x, (0x03, sp)
;	./src/OSAL.c: 418: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 438: osal_event_hdr_t *osal_msg_find(uint8 task_id, uint8 event)
;	-----------------------------------------
;	 function osal_msg_find
;	-----------------------------------------
_osal_msg_find:
	pushw	x
;	./src/OSAL.c: 443: HAL_ENTER_CRITICAL_SECTION(intState);  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL.c: 445: pHdr = osal_qHead;  // Point to the top of the queue.
	ldw	x, _osal_qHead+0
;	./src/OSAL.c: 448: while (pHdr != NULL)
00110$:
;	./src/OSAL.c: 450: if (((pHdr-1)->dest_id == task_id) && (((osal_event_hdr_t *)pHdr)->event == event))
	ldw	(0x01, sp), x
;	./src/OSAL.c: 448: while (pHdr != NULL)
	tnzw	x
	jreq	00113$
;	./src/OSAL.c: 450: if (((pHdr-1)->dest_id == task_id) && (((osal_event_hdr_t *)pHdr)->event == event))
	subw	x, #0x0005
	ldw	y, x
	ld	a, (0x4, y)
	cp	a, (0x05, sp)
	jrne	00108$
	ldw	y, (0x01, sp)
	ld	a, (y)
	cp	a, (0x06, sp)
	jreq	00113$
;	./src/OSAL.c: 452: break;
00108$:
;	./src/OSAL.c: 455: pHdr = OSAL_MSG_NEXT(pHdr);
	ldw	x, (x)
	jra	00110$
;	./src/OSAL.c: 458: HAL_EXIT_CRITICAL_SECTION(intState);  // Release interrupts.
00113$:
;	./src/OSAL.c: 460: return (osal_event_hdr_t *)pHdr;
	ldw	x, (0x01, sp)
;	./src/OSAL.c: 461: }
	addw	sp, #2
	ret
;	./src/OSAL.c: 475: void osal_msg_enqueue( osal_msg_q_t *q_ptr, void *msg_ptr )
;	-----------------------------------------
;	 function osal_msg_enqueue
;	-----------------------------------------
_osal_msg_enqueue:
	sub	sp, #4
;	./src/OSAL.c: 481: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 483: OSAL_MSG_NEXT( msg_ptr ) = NULL;
	ldw	x, (0x09, sp)
	subw	x, #0x0005
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL.c: 485: if ( *q_ptr == NULL )
	ldw	y, (0x07, sp)
	ldw	(0x03, sp), y
	ldw	x, y
	ldw	x, (x)
	jrne	00109$
;	./src/OSAL.c: 487: *q_ptr = msg_ptr;
	ldw	x, (0x03, sp)
	ldw	y, (0x09, sp)
	ldw	(x), y
	jra	00116$
00109$:
;	./src/OSAL.c: 492: for ( list = *q_ptr; OSAL_MSG_NEXT( list ) != NULL; list = OSAL_MSG_NEXT( list ) );
	ldw	(0x03, sp), x
00114$:
	ldw	x, (0x03, sp)
	subw	x, #0x0005
	ldw	(0x01, sp), x
	ldw	x, (x)
	ldw	(0x03, sp), x
	jrne	00114$
;	./src/OSAL.c: 495: OSAL_MSG_NEXT( list ) = msg_ptr;
	ldw	x, (0x01, sp)
	ldw	y, (0x09, sp)
	ldw	(x), y
;	./src/OSAL.c: 499: HAL_EXIT_CRITICAL_SECTION(intState);
00116$:
;	./src/OSAL.c: 500: }
	addw	sp, #4
	ret
;	./src/OSAL.c: 513: void *osal_msg_dequeue( osal_msg_q_t *q_ptr )
;	-----------------------------------------
;	 function osal_msg_dequeue
;	-----------------------------------------
_osal_msg_dequeue:
	sub	sp, #6
;	./src/OSAL.c: 515: void *msg_ptr = NULL;
	clrw	x
	ldw	(0x01, sp), x
;	./src/OSAL.c: 519: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 521: if ( *q_ptr != NULL )
	ldw	y, (0x09, sp)
	ldw	x, y
	ldw	x, (x)
	jreq	00109$
;	./src/OSAL.c: 524: msg_ptr = *q_ptr;
;	./src/OSAL.c: 525: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
	ldw	(0x01, sp), x
	ldw	(0x03, sp), x
	subw	x, #0x0005
	ldw	(0x05, sp), x
	ldw	x, (x)
	ldw	(y), x
;	./src/OSAL.c: 526: OSAL_MSG_NEXT( msg_ptr ) = NULL;
	ldw	x, (0x05, sp)
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL.c: 527: OSAL_MSG_ID( msg_ptr ) = TASK_NO_TASK;
	ldw	x, (0x03, sp)
	decw	x
	ld	a, #0xff
	ld	(x), a
;	./src/OSAL.c: 531: HAL_EXIT_CRITICAL_SECTION(intState);
00109$:
;	./src/OSAL.c: 533: return msg_ptr;
	ldw	x, (0x01, sp)
;	./src/OSAL.c: 534: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 549: void osal_msg_push( osal_msg_q_t *q_ptr, void *msg_ptr )
;	-----------------------------------------
;	 function osal_msg_push
;	-----------------------------------------
_osal_msg_push:
	pushw	x
;	./src/OSAL.c: 554: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 557: OSAL_MSG_NEXT( msg_ptr ) = *q_ptr;
	ldw	x, (0x07, sp)
	subw	x, #0x0005
	ldw	y, (0x05, sp)
	ldw	(0x01, sp), y
	ldw	y, (y)
	ldw	(x), y
;	./src/OSAL.c: 558: *q_ptr = msg_ptr;
	ldw	x, (0x01, sp)
	ldw	y, (0x07, sp)
	ldw	(x), y
;	./src/OSAL.c: 561: HAL_EXIT_CRITICAL_SECTION(intState);
;	./src/OSAL.c: 562: }
	popw	x
	ret
;	./src/OSAL.c: 578: void osal_msg_extract( osal_msg_q_t *q_ptr, void *msg_ptr, void *prev_ptr )
;	-----------------------------------------
;	 function osal_msg_extract
;	-----------------------------------------
_osal_msg_extract:
	sub	sp, #6
;	./src/OSAL.c: 583: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 585: if ( msg_ptr == *q_ptr )
	ldw	y, (0x09, sp)
	ldw	(0x05, sp), y
	ldw	x, y
	ldw	x, (x)
;	./src/OSAL.c: 588: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
	ldw	y, (0x0b, sp)
	ldw	(0x01, sp), y
	subw	y, #0x0005
	ldw	(0x03, sp), y
	ldw	y, (y)
;	./src/OSAL.c: 585: if ( msg_ptr == *q_ptr )
	cpw	x, (0x0b, sp)
	jrne	00108$
;	./src/OSAL.c: 588: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
	ldw	x, (0x05, sp)
	ldw	(x), y
	jra	00109$
00108$:
;	./src/OSAL.c: 593: OSAL_MSG_NEXT( prev_ptr ) = OSAL_MSG_NEXT( msg_ptr );
	ldw	x, (0x0d, sp)
	subw	x, #0x0005
	ldw	(0x05, sp), x
	ldw	(x), y
00109$:
;	./src/OSAL.c: 595: OSAL_MSG_NEXT( msg_ptr ) = NULL;
	ldw	x, (0x03, sp)
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL.c: 596: OSAL_MSG_ID( msg_ptr ) = TASK_NO_TASK;
	ldw	x, (0x01, sp)
	decw	x
	ld	a, #0xff
	ld	(x), a
;	./src/OSAL.c: 599: HAL_EXIT_CRITICAL_SECTION(intState);
;	./src/OSAL.c: 600: }
	addw	sp, #6
	ret
;	./src/OSAL.c: 616: uint8 osal_msg_enqueue_max( osal_msg_q_t *q_ptr, void *msg_ptr, uint8 max )
;	-----------------------------------------
;	 function osal_msg_enqueue_max
;	-----------------------------------------
_osal_msg_enqueue_max:
	sub	sp, #4
;	./src/OSAL.c: 619: uint8 ret = FALSE;
	clr	(0x01, sp)
;	./src/OSAL.c: 623: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 626: if ( *q_ptr == NULL )
	ldw	y, (0x07, sp)
	ldw	(0x03, sp), y
	ldw	x, y
	ldw	x, (x)
	jrne	00114$
;	./src/OSAL.c: 628: *q_ptr = msg_ptr;
	ldw	x, (0x03, sp)
	ldw	y, (0x09, sp)
	ldw	(x), y
;	./src/OSAL.c: 629: ret = TRUE;
	ld	a, #0x01
	ld	(0x01, sp), a
	jra	00116$
00114$:
;	./src/OSAL.c: 634: list = *q_ptr;
	ldw	(0x02, sp), x
;	./src/OSAL.c: 635: max--;
	dec	(0x0b, sp)
;	./src/OSAL.c: 636: while ( (OSAL_MSG_NEXT( list ) != NULL) && (max > 0) )
	ld	a, (0x0b, sp)
	ld	(0x04, sp), a
00108$:
	ldw	x, (0x02, sp)
	subw	x, #0x0005
	ldw	(0x02, sp), x
	ldw	x, (x)
	jreq	00110$
	tnz	(0x04, sp)
	jreq	00110$
;	./src/OSAL.c: 638: list = OSAL_MSG_NEXT( list );
	ldw	(0x02, sp), x
;	./src/OSAL.c: 639: max--;
	dec	(0x04, sp)
	jra	00108$
00110$:
;	./src/OSAL.c: 643: if ( max != 0 )
	tnz	(0x04, sp)
	jreq	00116$
;	./src/OSAL.c: 645: OSAL_MSG_NEXT( list ) = msg_ptr;
	ldw	x, (0x02, sp)
	ldw	y, (0x09, sp)
	ldw	(x), y
;	./src/OSAL.c: 646: ret = TRUE;
	ld	a, #0x01
	ld	(0x01, sp), a
;	./src/OSAL.c: 651: HAL_EXIT_CRITICAL_SECTION(intState);
00116$:
;	./src/OSAL.c: 653: return ret;
	ld	a, (0x01, sp)
;	./src/OSAL.c: 654: }
	addw	sp, #4
	ret
;	./src/OSAL.c: 669: uint8 osal_set_event( uint8 task_id, uint16 event_flag )
;	-----------------------------------------
;	 function osal_set_event
;	-----------------------------------------
_osal_set_event:
;	./src/OSAL.c: 671: if ( task_id < tasksCnt )
	ld	a, _tasksCnt+0
	cp	a, (0x03, sp)
	jrule	00110$
;	./src/OSAL.c: 674: HAL_ENTER_CRITICAL_SECTION(intState);    // Hold off interrupts
	sim
	nop
	nop
;	./src/OSAL.c: 675: tasksEvents[task_id] |= event_flag;  // Stuff the event bit(s)
	ld	a, (0x03, sp)
	clrw	x
	ld	xl, a
	sllw	x
	addw	x, _tasksEvents+0
	ldw	y, x
	ldw	x, (x)
	ld	a, xl
	or	a, (0x05, sp)
	rlwa	x
	or	a, (0x04, sp)
	ld	xh, a
	ldw	(y), x
;	./src/OSAL.c: 677: return ( SUCCESS );
	clr	a
	ret
00110$:
;	./src/OSAL.c: 681: return ( INVALID_TASK );
	ld	a, #0x03
;	./src/OSAL.c: 683: }
	ret
;	./src/OSAL.c: 698: uint8 osal_clear_event( uint8 task_id, uint16 event_flag )
;	-----------------------------------------
;	 function osal_clear_event
;	-----------------------------------------
_osal_clear_event:
	pushw	x
;	./src/OSAL.c: 700: if ( task_id < tasksCnt )
	ld	a, _tasksCnt+0
	cp	a, (0x05, sp)
	jrule	00110$
;	./src/OSAL.c: 703: HAL_ENTER_CRITICAL_SECTION(intState);    // Hold off interrupts
	sim
	nop
	nop
;	./src/OSAL.c: 704: tasksEvents[task_id] &= ~(event_flag);   // Clear the event bit(s)
	ld	a, (0x05, sp)
	clrw	x
	ld	xl, a
	sllw	x
	addw	x, _tasksEvents+0
	ldw	y, x
	ldw	x, (x)
	ldw	(0x01, sp), x
	ldw	x, (0x06, sp)
	cplw	x
	ld	a, xl
	and	a, (0x02, sp)
	rlwa	x
	and	a, (0x01, sp)
	ld	xh, a
	ldw	(y), x
;	./src/OSAL.c: 706: return ( SUCCESS );
	clr	a
;	./src/OSAL.c: 710: return ( INVALID_TASK );
	.byte 0xc5
00110$:
	ld	a, #0x03
00112$:
;	./src/OSAL.c: 712: }
	popw	x
	ret
;	./src/OSAL.c: 727: uint8 osal_isr_register( uint8 interrupt_id, void (*isr_ptr)( uint8* ) )
;	-----------------------------------------
;	 function osal_isr_register
;	-----------------------------------------
_osal_isr_register:
;	./src/OSAL.c: 732: return ( SUCCESS );
	clr	a
;	./src/OSAL.c: 733: }
	ret
;	./src/OSAL.c: 752: uint8 osal_int_enable( uint8 interrupt_id )
;	-----------------------------------------
;	 function osal_int_enable
;	-----------------------------------------
_osal_int_enable:
;	./src/OSAL.c: 755: if ( interrupt_id == INTS_ALL )
	ld	a, (0x03, sp)
	inc	a
	jrne	00105$
;	./src/OSAL.c: 757: HAL_ENABLE_INTERRUPTS();
	rim
	nop
	nop
;	./src/OSAL.c: 758: return ( SUCCESS );
	clr	a
	ret
00105$:
;	./src/OSAL.c: 762: return ( INVALID_INTERRUPT_ID );
	ld	a, #0x07
;	./src/OSAL.c: 764: }
	ret
;	./src/OSAL.c: 782: uint8 osal_int_disable( uint8 interrupt_id )
;	-----------------------------------------
;	 function osal_int_disable
;	-----------------------------------------
_osal_int_disable:
;	./src/OSAL.c: 785: if ( interrupt_id == INTS_ALL )
	ld	a, (0x03, sp)
	inc	a
	jrne	00105$
;	./src/OSAL.c: 787: HAL_DISABLE_INTERRUPTS();
	sim
	nop
	nop
;	./src/OSAL.c: 788: return ( SUCCESS );
	clr	a
	ret
00105$:
;	./src/OSAL.c: 792: return ( INVALID_INTERRUPT_ID );
	ld	a, #0x07
;	./src/OSAL.c: 794: }
	ret
;	./src/OSAL.c: 808: uint8 osal_init_system( void )
;	-----------------------------------------
;	 function osal_init_system
;	-----------------------------------------
_osal_init_system:
;	./src/OSAL.c: 811: osal_mem_init();
	call	_osal_mem_init
;	./src/OSAL.c: 814: osal_qHead = NULL;
	clrw	x
	ldw	_osal_qHead+0, x
;	./src/OSAL.c: 817: osalTimerInit();
	call	_osalTimerInit
;	./src/OSAL.c: 820: osalInitTasks();
	call	_osalInitTasks
;	./src/OSAL.c: 823: osal_mem_kick();
	call	_osal_mem_kick
;	./src/OSAL.c: 825: return ( SUCCESS );
	clr	a
;	./src/OSAL.c: 826: }
	ret
;	./src/OSAL.c: 840: void osal_start_system( void )
;	-----------------------------------------
;	 function osal_start_system
;	-----------------------------------------
_osal_start_system:
00102$:
;	./src/OSAL.c: 844: osal_run_system();
	call	_osal_run_system
	jra	00102$
;	./src/OSAL.c: 846: }
	ret
;	./src/OSAL.c: 862: void osal_run_system( void )
;	-----------------------------------------
;	 function osal_run_system
;	-----------------------------------------
_osal_run_system:
	sub	sp, #5
;	./src/OSAL.c: 866: do {
	clr	(0x05, sp)
00103$:
;	./src/OSAL.c: 867: if (tasksEvents[idx])  // Task is highest priority that is ready.
	ld	a, (0x05, sp)
	clrw	x
	ld	xl, a
	sllw	x
	addw	x, _tasksEvents+0
	ldw	x, (x)
;	./src/OSAL.c: 871: } while (++idx < tasksCnt);
	ld	a, _tasksCnt+0
;	./src/OSAL.c: 867: if (tasksEvents[idx])  // Task is highest priority that is ready.
	tnzw	x
	jrne	00105$
;	./src/OSAL.c: 871: } while (++idx < tasksCnt);
	inc	(0x05, sp)
	cp	a, (0x05, sp)
	jrugt	00103$
00105$:
;	./src/OSAL.c: 873: if (idx < tasksCnt)
	cp	a, (0x05, sp)
	jrule	00124$
;	./src/OSAL.c: 878: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 879: events = tasksEvents[idx];
	clrw	x
	ld	a, (0x05, sp)
	ld	xl, a
	sllw	x
	ldw	(0x03, sp), x
	ldw	x, _tasksEvents+0
	addw	x, (0x03, sp)
	ldw	y, x
	ldw	y, (y)
;	./src/OSAL.c: 880: tasksEvents[idx] = 0;  // Clear the Events for this task.
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL.c: 883: activeTaskID = idx;
	ld	a, (0x05, sp)
	ld	_activeTaskID+0, a
;	./src/OSAL.c: 884: events = (tasksArr[idx])( idx, events );
	ldw	x, (0x03, sp)
	addw	x, #(_tasksArr + 0)
	ldw	x, (x)
	pushw	y
	ld	a, (0x07, sp)
	push	a
	call	(x)
	addw	sp, #3
	ldw	(0x01, sp), x
;	./src/OSAL.c: 885: activeTaskID = TASK_NO_TASK;
	mov	_activeTaskID+0, #0xff
;	./src/OSAL.c: 887: HAL_ENTER_CRITICAL_SECTION(intState);
	sim
	nop
	nop
;	./src/OSAL.c: 888: tasksEvents[idx] |= events;  // Add back unprocessed events to the current task.
	ldw	y, _tasksEvents+0
	addw	y, (0x03, sp)
	ldw	x, y
	ldw	x, (x)
	ld	a, xl
	or	a, (0x02, sp)
	rlwa	x
	or	a, (0x01, sp)
	ld	xh, a
	ldw	(y), x
;	./src/OSAL.c: 889: HAL_EXIT_CRITICAL_SECTION(intState);
00124$:
;	./src/OSAL.c: 892: }
	addw	sp, #5
	ret
;	./src/OSAL.c: 908: uint8 osal_self( void )
;	-----------------------------------------
;	 function osal_self
;	-----------------------------------------
_osal_self:
;	./src/OSAL.c: 910: return ( activeTaskID );
	ld	a, _activeTaskID+0
;	./src/OSAL.c: 911: }
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
__xinit__activeTaskID:
	.db #0xff	; 255
	.area CABS (ABS)
