;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module OSAL_Memory
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _osal_mem_init
	.globl _osal_mem_kick
	.globl _osal_mem_alloc
	.globl _osal_mem_free
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_theHeap:
	.ds 1024
_ff1:
	.ds 2
_osalMemStat:
	.ds 1
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
;	./src/OSAL_Memory.c: 191: void osal_mem_init(void)
;	-----------------------------------------
;	 function osal_mem_init
;	-----------------------------------------
_osal_mem_init:
;	./src/OSAL_Memory.c: 202: theHeap[OSALMEM_LASTBLK_IDX].val = 0;
	ldw	x, #(_theHeap + 0)+1022
	clr	(0x1, x)
	clr	(x)
;	./src/OSAL_Memory.c: 205: ff1 = theHeap;
	ldw	x, #(_theHeap + 0)
;	./src/OSAL_Memory.c: 206: ff1->val = OSALMEM_SMALLBLK_BUCKET;                   // Set 'len' & clear 'inUse' field.
	ldw	_ff1+0, x
	ldw	y, #0x0248
	ldw	(x), y
;	./src/OSAL_Memory.c: 209: theHeap[OSALMEM_SMALLBLK_HDRCNT].val = (OSALMEM_HDRSZ | OSALMEM_IN_USE);
	ldw	x, #(_theHeap + 0)+584
	ldw	y, #0x8002
	ldw	(x), y
;	./src/OSAL_Memory.c: 212: theHeap[OSALMEM_BIGBLK_IDX].val = OSALMEM_BIGBLK_SZ;  // Set 'len' & clear 'inUse' field.
	ldw	x, #(_theHeap + 0)+586
	ldw	y, #0x01b4
	ldw	(x), y
;	./src/OSAL_Memory.c: 220: }
	ret
;	./src/OSAL_Memory.c: 240: void osal_mem_kick(void)
;	-----------------------------------------
;	 function osal_mem_kick
;	-----------------------------------------
_osal_mem_kick:
;	./src/OSAL_Memory.c: 243: osalMemHdr_t *tmp = osal_mem_alloc(1);
	push	#0x01
	push	#0x00
	call	_osal_mem_alloc
	addw	sp, #2
;	./src/OSAL_Memory.c: 245: HAL_ASSERT((tmp != NULL));
	tnzw	x
	jrne	00107$
00102$:
	jra	00102$
00107$:
;	./src/OSAL_Memory.c: 246: HAL_ENTER_CRITICAL_SECTION(intState);  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Memory.c: 252: ff1 = tmp - 1;       // Set 'ff1' to point to the first available memory after the LL block.
	ldw	y, x
	subw	y, #0x0002
	ldw	_ff1+0, y
;	./src/OSAL_Memory.c: 253: osal_mem_free(tmp);
	pushw	x
	call	_osal_mem_free
	popw	x
;	./src/OSAL_Memory.c: 254: osalMemStat = 0x01;  // Set 'osalMemStat' after the free because it enables memory profiling.
	mov	_osalMemStat+0, #0x01
;	./src/OSAL_Memory.c: 256: HAL_EXIT_CRITICAL_SECTION(intState);  // Re-enable interrupts.
;	./src/OSAL_Memory.c: 257: }
	ret
;	./src/OSAL_Memory.c: 277: void *osal_mem_alloc( uint16 size )
;	-----------------------------------------
;	 function osal_mem_alloc
;	-----------------------------------------
_osal_mem_alloc:
	sub	sp, #9
;	./src/OSAL_Memory.c: 280: osalMemHdr_t *prev = NULL;
	clrw	x
	ldw	(0x01, sp), x
;	./src/OSAL_Memory.c: 283: uint8 coal = 0;
	clr	(0x03, sp)
;	./src/OSAL_Memory.c: 285: size += OSALMEM_HDRSZ;
	ldw	x, (0x0c, sp)
	incw	x
	incw	x
	ldw	(0x0c, sp), x
;	./src/OSAL_Memory.c: 302: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Memory.c: 306: if ((osalMemStat == 0) || (size <= OSALMEM_SMALL_BLKSZ))
	tnz	_osalMemStat+0
	jreq	00114$
	ldw	x, (0x0c, sp)
	cpw	x, #0x0010
	jrugt	00115$
00114$:
;	./src/OSAL_Memory.c: 308: hdr = ff1;
	ldw	x, _ff1+0
	ldw	(0x04, sp), x
	jra	00130$
00115$:
;	./src/OSAL_Memory.c: 312: hdr = (theHeap + OSALMEM_BIGBLK_IDX);
	ldw	x, #(_theHeap + 586)
	ldw	(0x04, sp), x
;	./src/OSAL_Memory.c: 315: do
00130$:
;	./src/OSAL_Memory.c: 317: if ( hdr->hdr.inUse )
	ldw	x, (0x04, sp)
	ld	a, (0x1, x)
	swap	a
	srl	a
	srl	a
	srl	a
	and	a, #0x01
	jreq	00126$
;	./src/OSAL_Memory.c: 319: coal = 0;
	clr	(0x03, sp)
	jra	00127$
00126$:
;	./src/OSAL_Memory.c: 323: if ( coal != 0 )
	tnz	(0x03, sp)
	jreq	00123$
;	./src/OSAL_Memory.c: 330: prev->hdr.len += hdr->hdr.len;
	ldw	y, (0x01, sp)
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	(0x07, sp), a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	(0x06, sp), a
	ldw	x, (0x04, sp)
	ld	a, (x)
	ld	(0x09, sp), a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	(0x08, sp), a
	ldw	x, (0x06, sp)
	addw	x, (0x08, sp)
	ld	a, xl
	ld	(y), a
	ld	a, xh
	and	a, #0x7f
	push	a
	ld	a, #0x80
	and	a, (0x1, y)
	or	a, (1, sp)
	ld	(0x1, y), a
	pop	a
;	./src/OSAL_Memory.c: 332: if ( prev->hdr.len >= size )
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	yl, a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	yh, a
	ldw	x, y
	cpw	x, (0x0c, sp)
	jrc	00127$
;	./src/OSAL_Memory.c: 334: hdr = prev;
	ldw	y, (0x01, sp)
	ldw	(0x04, sp), y
;	./src/OSAL_Memory.c: 335: break;
	jra	00132$
00123$:
;	./src/OSAL_Memory.c: 340: if ( hdr->hdr.len >= size )
	ldw	x, (0x04, sp)
	ld	a, (x)
	ld	yl, a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	yh, a
	ldw	x, y
	cpw	x, (0x0c, sp)
	jrnc	00132$
;	./src/OSAL_Memory.c: 345: coal = 1;
	ld	a, #0x01
	ld	(0x03, sp), a
;	./src/OSAL_Memory.c: 346: prev = hdr;
	ldw	y, (0x04, sp)
	ldw	(0x01, sp), y
00127$:
;	./src/OSAL_Memory.c: 350: hdr = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
	ldw	y, (0x04, sp)
	ldw	x, (0x04, sp)
	ld	a, (x)
	ld	(0x09, sp), a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	(0x08, sp), a
	addw	y, (0x08, sp)
;	./src/OSAL_Memory.c: 352: if ( hdr->val == 0 )
	ldw	(0x04, sp), y
	ldw	x, y
	ldw	x, (x)
	jreq	00225$
	jp	00130$
00225$:
;	./src/OSAL_Memory.c: 354: hdr = NULL;
	clrw	x
	ldw	(0x04, sp), x
;	./src/OSAL_Memory.c: 357: } while (1);
00132$:
;	./src/OSAL_Memory.c: 359: if ( hdr != NULL )
;	./src/OSAL_Memory.c: 361: uint16 tmp = hdr->hdr.len - size;
	ldw	x, (0x04, sp)
	jreq	00141$
	ld	a, (x)
	ld	yl, a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	yh, a
	subw	y, (0x0c, sp)
;	./src/OSAL_Memory.c: 350: hdr = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
	ldw	x, (0x04, sp)
	ldw	(0x08, sp), x
;	./src/OSAL_Memory.c: 364: if ( tmp >= OSALMEM_MIN_BLKSZ )
	cpw	y, #0x0004
	jrc	00134$
;	./src/OSAL_Memory.c: 367: osalMemHdr_t *next = (osalMemHdr_t *)((uint8 *)hdr + size);
	ldw	x, (0x08, sp)
	addw	x, (0x0c, sp)
;	./src/OSAL_Memory.c: 368: next->val = tmp;                     // Set 'len' & clear 'inUse' field.
	ldw	(x), y
;	./src/OSAL_Memory.c: 369: hdr->val = (size | OSALMEM_IN_USE);  // Set 'len' & 'inUse' field.
	ldw	x, (0x0c, sp)
	sllw	x
	scf
	rrcw	x
	ldw	y, (0x04, sp)
	ldw	(y), x
	jra	00135$
00134$:
;	./src/OSAL_Memory.c: 387: hdr->hdr.inUse = TRUE;
	ldw	x, (0x04, sp)
	incw	x
	rlc	(x)
	scf
	rrc	(x)
00135$:
;	./src/OSAL_Memory.c: 435: if ((osalMemStat != 0) && (ff1 == hdr))
	tnz	_osalMemStat+0
	jreq	00137$
	ldw	x, (0x04, sp)
	cpw	x, _ff1+0
	jrne	00137$
;	./src/OSAL_Memory.c: 437: ff1 = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
	ldw	x, (0x04, sp)
	ld	a, (x)
	push	a
	ld	a, (0x1, x)
	and	a, #0x7f
	ld	xh, a
	pop	a
	ld	xl, a
	addw	x, (0x08, sp)
	ldw	_ff1+0, x
00137$:
;	./src/OSAL_Memory.c: 440: hdr++;
	ldw	x, (0x04, sp)
	incw	x
	incw	x
	ldw	(0x04, sp), x
;	./src/OSAL_Memory.c: 443: HAL_EXIT_CRITICAL_SECTION( intState );  // Re-enable interrupts.
00141$:
;	./src/OSAL_Memory.c: 447: HAL_ASSERT(((halDataAlign_t)hdr % sizeof(halDataAlign_t)) == 0);
	clr	a
	tnz	a
	jreq	00149$
00144$:
	jra	00144$
00149$:
;	./src/OSAL_Memory.c: 455: return (void *)hdr;
	ldw	x, (0x04, sp)
;	./src/OSAL_Memory.c: 456: }
	addw	sp, #9
	ret
;	./src/OSAL_Memory.c: 476: void osal_mem_free(void *ptr)
;	-----------------------------------------
;	 function osal_mem_free
;	-----------------------------------------
_osal_mem_free:
	sub	sp, #4
;	./src/OSAL_Memory.c: 479: osalMemHdr_t *hdr = (osalMemHdr_t *)ptr - 1;
	ldw	x, (0x07, sp)
	decw	x
	decw	x
	ldw	(0x01, sp), x
;	./src/OSAL_Memory.c: 486: HAL_ASSERT(((uint8 *)ptr >= (uint8 *)theHeap) && ((uint8 *)ptr < (uint8 *)theHeap+MAXMEMHEAP));
	ldw	y, (0x07, sp)
	ldw	x, #(_theHeap + 0)
	ldw	(0x03, sp), x
	exgw	x, y
	cpw	x, (0x03, sp)
	exgw	x, y
	jrc	00102$
	ldw	x, #(_theHeap + 0)
	addw	x, #0x0400
	ldw	(0x03, sp), x
	ldw	x, y
	cpw	x, (0x03, sp)
	jrc	00108$
00102$:
	jra	00102$
00108$:
;	./src/OSAL_Memory.c: 487: HAL_ASSERT(hdr->hdr.inUse);
	ldw	x, (0x01, sp)
	incw	x
	ld	a, (x)
	swap	a
	srl	a
	srl	a
	srl	a
	and	a, #0x01
	jrne	00116$
00111$:
	jra	00111$
00116$:
;	./src/OSAL_Memory.c: 489: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
	sim
	nop
	nop
;	./src/OSAL_Memory.c: 490: hdr->hdr.inUse = FALSE;
	ld	a, #0x7f
	and	a, (x)
	ld	(x), a
;	./src/OSAL_Memory.c: 492: if (ff1 > hdr)
;	./src/OSAL_Memory.c: 494: ff1 = hdr;
	ldw	x, (0x01, sp)
	cpw	x, _ff1+0
	jrnc	00128$
	ldw	_ff1+0, x
;	./src/OSAL_Memory.c: 522: HAL_EXIT_CRITICAL_SECTION( intState );  // Re-enable interrupts.
00128$:
;	./src/OSAL_Memory.c: 523: }
	addw	sp, #4
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
