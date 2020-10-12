                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module OSAL_Memory
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _osal_mem_init
                                     12 	.globl _osal_mem_kick
                                     13 	.globl _osal_mem_alloc
                                     14 	.globl _osal_mem_free
                                     15 ;--------------------------------------------------------
                                     16 ; ram data
                                     17 ;--------------------------------------------------------
                                     18 	.area DATA
      000005                         19 _theHeap:
      000005                         20 	.ds 1024
      000405                         21 _ff1:
      000405                         22 	.ds 2
      000407                         23 _osalMemStat:
      000407                         24 	.ds 1
                                     25 ;--------------------------------------------------------
                                     26 ; ram data
                                     27 ;--------------------------------------------------------
                                     28 	.area INITIALIZED
                                     29 ;--------------------------------------------------------
                                     30 ; absolute external ram data
                                     31 ;--------------------------------------------------------
                                     32 	.area DABS (ABS)
                                     33 
                                     34 ; default segment ordering for linker
                                     35 	.area HOME
                                     36 	.area GSINIT
                                     37 	.area GSFINAL
                                     38 	.area CONST
                                     39 	.area INITIALIZER
                                     40 	.area CODE
                                     41 
                                     42 ;--------------------------------------------------------
                                     43 ; global & static initialisations
                                     44 ;--------------------------------------------------------
                                     45 	.area HOME
                                     46 	.area GSINIT
                                     47 	.area GSFINAL
                                     48 	.area GSINIT
                                     49 ;--------------------------------------------------------
                                     50 ; Home
                                     51 ;--------------------------------------------------------
                                     52 	.area HOME
                                     53 	.area HOME
                                     54 ;--------------------------------------------------------
                                     55 ; code
                                     56 ;--------------------------------------------------------
                                     57 	.area CODE
                                     58 ;	./src/OSAL_Memory.c: 191: void osal_mem_init(void)
                                     59 ;	-----------------------------------------
                                     60 ;	 function osal_mem_init
                                     61 ;	-----------------------------------------
      00842A                         62 _osal_mem_init:
                                     63 ;	./src/OSAL_Memory.c: 202: theHeap[OSALMEM_LASTBLK_IDX].val = 0;
      00842A AE 04 03         [ 2]   64 	ldw	x, #(_theHeap + 0)+1022
      00842D 6F 01            [ 1]   65 	clr	(0x1, x)
      00842F 7F               [ 1]   66 	clr	(x)
                                     67 ;	./src/OSAL_Memory.c: 205: ff1 = theHeap;
      008430 AE 00 05         [ 2]   68 	ldw	x, #(_theHeap + 0)
                                     69 ;	./src/OSAL_Memory.c: 206: ff1->val = OSALMEM_SMALLBLK_BUCKET;                   // Set 'len' & clear 'inUse' field.
      008433 CF 04 05         [ 2]   70 	ldw	_ff1+0, x
      008436 90 AE 02 48      [ 2]   71 	ldw	y, #0x0248
      00843A FF               [ 2]   72 	ldw	(x), y
                                     73 ;	./src/OSAL_Memory.c: 209: theHeap[OSALMEM_SMALLBLK_HDRCNT].val = (OSALMEM_HDRSZ | OSALMEM_IN_USE);
      00843B AE 02 4D         [ 2]   74 	ldw	x, #(_theHeap + 0)+584
      00843E 90 AE 80 02      [ 2]   75 	ldw	y, #0x8002
      008442 FF               [ 2]   76 	ldw	(x), y
                                     77 ;	./src/OSAL_Memory.c: 212: theHeap[OSALMEM_BIGBLK_IDX].val = OSALMEM_BIGBLK_SZ;  // Set 'len' & clear 'inUse' field.
      008443 AE 02 4F         [ 2]   78 	ldw	x, #(_theHeap + 0)+586
      008446 90 AE 01 B4      [ 2]   79 	ldw	y, #0x01b4
      00844A FF               [ 2]   80 	ldw	(x), y
                                     81 ;	./src/OSAL_Memory.c: 220: }
      00844B 81               [ 4]   82 	ret
                                     83 ;	./src/OSAL_Memory.c: 240: void osal_mem_kick(void)
                                     84 ;	-----------------------------------------
                                     85 ;	 function osal_mem_kick
                                     86 ;	-----------------------------------------
      00844C                         87 _osal_mem_kick:
                                     88 ;	./src/OSAL_Memory.c: 243: osalMemHdr_t *tmp = osal_mem_alloc(1);
      00844C 4B 01            [ 1]   89 	push	#0x01
      00844E 4B 00            [ 1]   90 	push	#0x00
      008450 CD 84 71         [ 4]   91 	call	_osal_mem_alloc
      008453 5B 02            [ 2]   92 	addw	sp, #2
                                     93 ;	./src/OSAL_Memory.c: 245: HAL_ASSERT((tmp != NULL));
      008455 5D               [ 2]   94 	tnzw	x
      008456 26 02            [ 1]   95 	jrne	00107$
      008458                         96 00102$:
      008458 20 FE            [ 2]   97 	jra	00102$
      00845A                         98 00107$:
                                     99 ;	./src/OSAL_Memory.c: 246: HAL_ENTER_CRITICAL_SECTION(intState);  // Hold off interrupts.
      00845A 9B               [ 1]  100 	sim
      00845B 9D               [ 1]  101 	nop
      00845C 9D               [ 1]  102 	nop
                                    103 ;	./src/OSAL_Memory.c: 252: ff1 = tmp - 1;       // Set 'ff1' to point to the first available memory after the LL block.
      00845D 90 93            [ 1]  104 	ldw	y, x
      00845F 72 A2 00 02      [ 2]  105 	subw	y, #0x0002
      008463 90 CF 04 05      [ 2]  106 	ldw	_ff1+0, y
                                    107 ;	./src/OSAL_Memory.c: 253: osal_mem_free(tmp);
      008467 89               [ 2]  108 	pushw	x
      008468 CD 85 87         [ 4]  109 	call	_osal_mem_free
      00846B 85               [ 2]  110 	popw	x
                                    111 ;	./src/OSAL_Memory.c: 254: osalMemStat = 0x01;  // Set 'osalMemStat' after the free because it enables memory profiling.
      00846C 35 01 04 07      [ 1]  112 	mov	_osalMemStat+0, #0x01
                                    113 ;	./src/OSAL_Memory.c: 256: HAL_EXIT_CRITICAL_SECTION(intState);  // Re-enable interrupts.
                                    114 ;	./src/OSAL_Memory.c: 257: }
      008470 81               [ 4]  115 	ret
                                    116 ;	./src/OSAL_Memory.c: 277: void *osal_mem_alloc( uint16 size )
                                    117 ;	-----------------------------------------
                                    118 ;	 function osal_mem_alloc
                                    119 ;	-----------------------------------------
      008471                        120 _osal_mem_alloc:
      008471 52 09            [ 2]  121 	sub	sp, #9
                                    122 ;	./src/OSAL_Memory.c: 280: osalMemHdr_t *prev = NULL;
      008473 5F               [ 1]  123 	clrw	x
      008474 1F 01            [ 2]  124 	ldw	(0x01, sp), x
                                    125 ;	./src/OSAL_Memory.c: 283: uint8 coal = 0;
      008476 0F 03            [ 1]  126 	clr	(0x03, sp)
                                    127 ;	./src/OSAL_Memory.c: 285: size += OSALMEM_HDRSZ;
      008478 1E 0C            [ 2]  128 	ldw	x, (0x0c, sp)
      00847A 5C               [ 1]  129 	incw	x
      00847B 5C               [ 1]  130 	incw	x
      00847C 1F 0C            [ 2]  131 	ldw	(0x0c, sp), x
                                    132 ;	./src/OSAL_Memory.c: 302: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      00847E 9B               [ 1]  133 	sim
      00847F 9D               [ 1]  134 	nop
      008480 9D               [ 1]  135 	nop
                                    136 ;	./src/OSAL_Memory.c: 306: if ((osalMemStat == 0) || (size <= OSALMEM_SMALL_BLKSZ))
      008481 72 5D 04 07      [ 1]  137 	tnz	_osalMemStat+0
      008485 27 07            [ 1]  138 	jreq	00114$
      008487 1E 0C            [ 2]  139 	ldw	x, (0x0c, sp)
      008489 A3 00 10         [ 2]  140 	cpw	x, #0x0010
      00848C 22 07            [ 1]  141 	jrugt	00115$
      00848E                        142 00114$:
                                    143 ;	./src/OSAL_Memory.c: 308: hdr = ff1;
      00848E CE 04 05         [ 2]  144 	ldw	x, _ff1+0
      008491 1F 04            [ 2]  145 	ldw	(0x04, sp), x
      008493 20 05            [ 2]  146 	jra	00130$
      008495                        147 00115$:
                                    148 ;	./src/OSAL_Memory.c: 312: hdr = (theHeap + OSALMEM_BIGBLK_IDX);
      008495 AE 02 4F         [ 2]  149 	ldw	x, #(_theHeap + 586)
      008498 1F 04            [ 2]  150 	ldw	(0x04, sp), x
                                    151 ;	./src/OSAL_Memory.c: 315: do
      00849A                        152 00130$:
                                    153 ;	./src/OSAL_Memory.c: 317: if ( hdr->hdr.inUse )
      00849A 1E 04            [ 2]  154 	ldw	x, (0x04, sp)
      00849C E6 01            [ 1]  155 	ld	a, (0x1, x)
      00849E 4E               [ 1]  156 	swap	a
      00849F 44               [ 1]  157 	srl	a
      0084A0 44               [ 1]  158 	srl	a
      0084A1 44               [ 1]  159 	srl	a
      0084A2 A4 01            [ 1]  160 	and	a, #0x01
      0084A4 27 04            [ 1]  161 	jreq	00126$
                                    162 ;	./src/OSAL_Memory.c: 319: coal = 0;
      0084A6 0F 03            [ 1]  163 	clr	(0x03, sp)
      0084A8 20 61            [ 2]  164 	jra	00127$
      0084AA                        165 00126$:
                                    166 ;	./src/OSAL_Memory.c: 323: if ( coal != 0 )
      0084AA 0D 03            [ 1]  167 	tnz	(0x03, sp)
      0084AC 27 45            [ 1]  168 	jreq	00123$
                                    169 ;	./src/OSAL_Memory.c: 330: prev->hdr.len += hdr->hdr.len;
      0084AE 16 01            [ 2]  170 	ldw	y, (0x01, sp)
      0084B0 1E 01            [ 2]  171 	ldw	x, (0x01, sp)
      0084B2 F6               [ 1]  172 	ld	a, (x)
      0084B3 6B 07            [ 1]  173 	ld	(0x07, sp), a
      0084B5 E6 01            [ 1]  174 	ld	a, (0x1, x)
      0084B7 A4 7F            [ 1]  175 	and	a, #0x7f
      0084B9 6B 06            [ 1]  176 	ld	(0x06, sp), a
      0084BB 1E 04            [ 2]  177 	ldw	x, (0x04, sp)
      0084BD F6               [ 1]  178 	ld	a, (x)
      0084BE 6B 09            [ 1]  179 	ld	(0x09, sp), a
      0084C0 E6 01            [ 1]  180 	ld	a, (0x1, x)
      0084C2 A4 7F            [ 1]  181 	and	a, #0x7f
      0084C4 6B 08            [ 1]  182 	ld	(0x08, sp), a
      0084C6 1E 06            [ 2]  183 	ldw	x, (0x06, sp)
      0084C8 72 FB 08         [ 2]  184 	addw	x, (0x08, sp)
      0084CB 9F               [ 1]  185 	ld	a, xl
      0084CC 90 F7            [ 1]  186 	ld	(y), a
      0084CE 9E               [ 1]  187 	ld	a, xh
      0084CF A4 7F            [ 1]  188 	and	a, #0x7f
      0084D1 88               [ 1]  189 	push	a
      0084D2 A6 80            [ 1]  190 	ld	a, #0x80
      0084D4 90 E4 01         [ 1]  191 	and	a, (0x1, y)
      0084D7 1A 01            [ 1]  192 	or	a, (1, sp)
      0084D9 90 E7 01         [ 1]  193 	ld	(0x1, y), a
      0084DC 84               [ 1]  194 	pop	a
                                    195 ;	./src/OSAL_Memory.c: 332: if ( prev->hdr.len >= size )
      0084DD 1E 01            [ 2]  196 	ldw	x, (0x01, sp)
      0084DF F6               [ 1]  197 	ld	a, (x)
      0084E0 90 97            [ 1]  198 	ld	yl, a
      0084E2 E6 01            [ 1]  199 	ld	a, (0x1, x)
      0084E4 A4 7F            [ 1]  200 	and	a, #0x7f
      0084E6 90 95            [ 1]  201 	ld	yh, a
      0084E8 93               [ 1]  202 	ldw	x, y
      0084E9 13 0C            [ 2]  203 	cpw	x, (0x0c, sp)
      0084EB 25 1E            [ 1]  204 	jrc	00127$
                                    205 ;	./src/OSAL_Memory.c: 334: hdr = prev;
      0084ED 16 01            [ 2]  206 	ldw	y, (0x01, sp)
      0084EF 17 04            [ 2]  207 	ldw	(0x04, sp), y
                                    208 ;	./src/OSAL_Memory.c: 335: break;
      0084F1 20 34            [ 2]  209 	jra	00132$
      0084F3                        210 00123$:
                                    211 ;	./src/OSAL_Memory.c: 340: if ( hdr->hdr.len >= size )
      0084F3 1E 04            [ 2]  212 	ldw	x, (0x04, sp)
      0084F5 F6               [ 1]  213 	ld	a, (x)
      0084F6 90 97            [ 1]  214 	ld	yl, a
      0084F8 E6 01            [ 1]  215 	ld	a, (0x1, x)
      0084FA A4 7F            [ 1]  216 	and	a, #0x7f
      0084FC 90 95            [ 1]  217 	ld	yh, a
      0084FE 93               [ 1]  218 	ldw	x, y
      0084FF 13 0C            [ 2]  219 	cpw	x, (0x0c, sp)
      008501 24 24            [ 1]  220 	jrnc	00132$
                                    221 ;	./src/OSAL_Memory.c: 345: coal = 1;
      008503 A6 01            [ 1]  222 	ld	a, #0x01
      008505 6B 03            [ 1]  223 	ld	(0x03, sp), a
                                    224 ;	./src/OSAL_Memory.c: 346: prev = hdr;
      008507 16 04            [ 2]  225 	ldw	y, (0x04, sp)
      008509 17 01            [ 2]  226 	ldw	(0x01, sp), y
      00850B                        227 00127$:
                                    228 ;	./src/OSAL_Memory.c: 350: hdr = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
      00850B 16 04            [ 2]  229 	ldw	y, (0x04, sp)
      00850D 1E 04            [ 2]  230 	ldw	x, (0x04, sp)
      00850F F6               [ 1]  231 	ld	a, (x)
      008510 6B 09            [ 1]  232 	ld	(0x09, sp), a
      008512 E6 01            [ 1]  233 	ld	a, (0x1, x)
      008514 A4 7F            [ 1]  234 	and	a, #0x7f
      008516 6B 08            [ 1]  235 	ld	(0x08, sp), a
      008518 72 F9 08         [ 2]  236 	addw	y, (0x08, sp)
                                    237 ;	./src/OSAL_Memory.c: 352: if ( hdr->val == 0 )
      00851B 17 04            [ 2]  238 	ldw	(0x04, sp), y
      00851D 93               [ 1]  239 	ldw	x, y
      00851E FE               [ 2]  240 	ldw	x, (x)
      00851F 27 03            [ 1]  241 	jreq	00225$
      008521 CC 84 9A         [ 2]  242 	jp	00130$
      008524                        243 00225$:
                                    244 ;	./src/OSAL_Memory.c: 354: hdr = NULL;
      008524 5F               [ 1]  245 	clrw	x
      008525 1F 04            [ 2]  246 	ldw	(0x04, sp), x
                                    247 ;	./src/OSAL_Memory.c: 357: } while (1);
      008527                        248 00132$:
                                    249 ;	./src/OSAL_Memory.c: 359: if ( hdr != NULL )
                                    250 ;	./src/OSAL_Memory.c: 361: uint16 tmp = hdr->hdr.len - size;
      008527 1E 04            [ 2]  251 	ldw	x, (0x04, sp)
      008529 27 51            [ 1]  252 	jreq	00141$
      00852B F6               [ 1]  253 	ld	a, (x)
      00852C 90 97            [ 1]  254 	ld	yl, a
      00852E E6 01            [ 1]  255 	ld	a, (0x1, x)
      008530 A4 7F            [ 1]  256 	and	a, #0x7f
      008532 90 95            [ 1]  257 	ld	yh, a
      008534 72 F2 0C         [ 2]  258 	subw	y, (0x0c, sp)
                                    259 ;	./src/OSAL_Memory.c: 350: hdr = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
      008537 1E 04            [ 2]  260 	ldw	x, (0x04, sp)
      008539 1F 08            [ 2]  261 	ldw	(0x08, sp), x
                                    262 ;	./src/OSAL_Memory.c: 364: if ( tmp >= OSALMEM_MIN_BLKSZ )
      00853B 90 A3 00 04      [ 2]  263 	cpw	y, #0x0004
      00853F 25 11            [ 1]  264 	jrc	00134$
                                    265 ;	./src/OSAL_Memory.c: 367: osalMemHdr_t *next = (osalMemHdr_t *)((uint8 *)hdr + size);
      008541 1E 08            [ 2]  266 	ldw	x, (0x08, sp)
      008543 72 FB 0C         [ 2]  267 	addw	x, (0x0c, sp)
                                    268 ;	./src/OSAL_Memory.c: 368: next->val = tmp;                     // Set 'len' & clear 'inUse' field.
      008546 FF               [ 2]  269 	ldw	(x), y
                                    270 ;	./src/OSAL_Memory.c: 369: hdr->val = (size | OSALMEM_IN_USE);  // Set 'len' & 'inUse' field.
      008547 1E 0C            [ 2]  271 	ldw	x, (0x0c, sp)
      008549 58               [ 2]  272 	sllw	x
      00854A 99               [ 1]  273 	scf
      00854B 56               [ 2]  274 	rrcw	x
      00854C 16 04            [ 2]  275 	ldw	y, (0x04, sp)
      00854E 90 FF            [ 2]  276 	ldw	(y), x
      008550 20 06            [ 2]  277 	jra	00135$
      008552                        278 00134$:
                                    279 ;	./src/OSAL_Memory.c: 387: hdr->hdr.inUse = TRUE;
      008552 1E 04            [ 2]  280 	ldw	x, (0x04, sp)
      008554 5C               [ 1]  281 	incw	x
      008555 79               [ 1]  282 	rlc	(x)
      008556 99               [ 1]  283 	scf
      008557 76               [ 1]  284 	rrc	(x)
      008558                        285 00135$:
                                    286 ;	./src/OSAL_Memory.c: 435: if ((osalMemStat != 0) && (ff1 == hdr))
      008558 72 5D 04 07      [ 1]  287 	tnz	_osalMemStat+0
      00855C 27 18            [ 1]  288 	jreq	00137$
      00855E 1E 04            [ 2]  289 	ldw	x, (0x04, sp)
      008560 C3 04 05         [ 2]  290 	cpw	x, _ff1+0
      008563 26 11            [ 1]  291 	jrne	00137$
                                    292 ;	./src/OSAL_Memory.c: 437: ff1 = (osalMemHdr_t *)((uint8 *)hdr + hdr->hdr.len);
      008565 1E 04            [ 2]  293 	ldw	x, (0x04, sp)
      008567 F6               [ 1]  294 	ld	a, (x)
      008568 88               [ 1]  295 	push	a
      008569 E6 01            [ 1]  296 	ld	a, (0x1, x)
      00856B A4 7F            [ 1]  297 	and	a, #0x7f
      00856D 95               [ 1]  298 	ld	xh, a
      00856E 84               [ 1]  299 	pop	a
      00856F 97               [ 1]  300 	ld	xl, a
      008570 72 FB 08         [ 2]  301 	addw	x, (0x08, sp)
      008573 CF 04 05         [ 2]  302 	ldw	_ff1+0, x
      008576                        303 00137$:
                                    304 ;	./src/OSAL_Memory.c: 440: hdr++;
      008576 1E 04            [ 2]  305 	ldw	x, (0x04, sp)
      008578 5C               [ 1]  306 	incw	x
      008579 5C               [ 1]  307 	incw	x
      00857A 1F 04            [ 2]  308 	ldw	(0x04, sp), x
                                    309 ;	./src/OSAL_Memory.c: 443: HAL_EXIT_CRITICAL_SECTION( intState );  // Re-enable interrupts.
      00857C                        310 00141$:
                                    311 ;	./src/OSAL_Memory.c: 447: HAL_ASSERT(((halDataAlign_t)hdr % sizeof(halDataAlign_t)) == 0);
      00857C 4F               [ 1]  312 	clr	a
      00857D 4D               [ 1]  313 	tnz	a
      00857E 27 02            [ 1]  314 	jreq	00149$
      008580                        315 00144$:
      008580 20 FE            [ 2]  316 	jra	00144$
      008582                        317 00149$:
                                    318 ;	./src/OSAL_Memory.c: 455: return (void *)hdr;
      008582 1E 04            [ 2]  319 	ldw	x, (0x04, sp)
                                    320 ;	./src/OSAL_Memory.c: 456: }
      008584 5B 09            [ 2]  321 	addw	sp, #9
      008586 81               [ 4]  322 	ret
                                    323 ;	./src/OSAL_Memory.c: 476: void osal_mem_free(void *ptr)
                                    324 ;	-----------------------------------------
                                    325 ;	 function osal_mem_free
                                    326 ;	-----------------------------------------
      008587                        327 _osal_mem_free:
      008587 52 04            [ 2]  328 	sub	sp, #4
                                    329 ;	./src/OSAL_Memory.c: 479: osalMemHdr_t *hdr = (osalMemHdr_t *)ptr - 1;
      008589 1E 07            [ 2]  330 	ldw	x, (0x07, sp)
      00858B 5A               [ 2]  331 	decw	x
      00858C 5A               [ 2]  332 	decw	x
      00858D 1F 01            [ 2]  333 	ldw	(0x01, sp), x
                                    334 ;	./src/OSAL_Memory.c: 486: HAL_ASSERT(((uint8 *)ptr >= (uint8 *)theHeap) && ((uint8 *)ptr < (uint8 *)theHeap+MAXMEMHEAP));
      00858F 16 07            [ 2]  335 	ldw	y, (0x07, sp)
      008591 AE 00 05         [ 2]  336 	ldw	x, #(_theHeap + 0)
      008594 1F 03            [ 2]  337 	ldw	(0x03, sp), x
      008596 51               [ 1]  338 	exgw	x, y
      008597 13 03            [ 2]  339 	cpw	x, (0x03, sp)
      008599 51               [ 1]  340 	exgw	x, y
      00859A 25 0D            [ 1]  341 	jrc	00102$
      00859C AE 00 05         [ 2]  342 	ldw	x, #(_theHeap + 0)
      00859F 1C 04 00         [ 2]  343 	addw	x, #0x0400
      0085A2 1F 03            [ 2]  344 	ldw	(0x03, sp), x
      0085A4 93               [ 1]  345 	ldw	x, y
      0085A5 13 03            [ 2]  346 	cpw	x, (0x03, sp)
      0085A7 25 02            [ 1]  347 	jrc	00108$
      0085A9                        348 00102$:
      0085A9 20 FE            [ 2]  349 	jra	00102$
      0085AB                        350 00108$:
                                    351 ;	./src/OSAL_Memory.c: 487: HAL_ASSERT(hdr->hdr.inUse);
      0085AB 1E 01            [ 2]  352 	ldw	x, (0x01, sp)
      0085AD 5C               [ 1]  353 	incw	x
      0085AE F6               [ 1]  354 	ld	a, (x)
      0085AF 4E               [ 1]  355 	swap	a
      0085B0 44               [ 1]  356 	srl	a
      0085B1 44               [ 1]  357 	srl	a
      0085B2 44               [ 1]  358 	srl	a
      0085B3 A4 01            [ 1]  359 	and	a, #0x01
      0085B5 26 02            [ 1]  360 	jrne	00116$
      0085B7                        361 00111$:
      0085B7 20 FE            [ 2]  362 	jra	00111$
      0085B9                        363 00116$:
                                    364 ;	./src/OSAL_Memory.c: 489: HAL_ENTER_CRITICAL_SECTION( intState );  // Hold off interrupts.
      0085B9 9B               [ 1]  365 	sim
      0085BA 9D               [ 1]  366 	nop
      0085BB 9D               [ 1]  367 	nop
                                    368 ;	./src/OSAL_Memory.c: 490: hdr->hdr.inUse = FALSE;
      0085BC A6 7F            [ 1]  369 	ld	a, #0x7f
      0085BE F4               [ 1]  370 	and	a, (x)
      0085BF F7               [ 1]  371 	ld	(x), a
                                    372 ;	./src/OSAL_Memory.c: 492: if (ff1 > hdr)
                                    373 ;	./src/OSAL_Memory.c: 494: ff1 = hdr;
      0085C0 1E 01            [ 2]  374 	ldw	x, (0x01, sp)
      0085C2 C3 04 05         [ 2]  375 	cpw	x, _ff1+0
      0085C5 24 03            [ 1]  376 	jrnc	00128$
      0085C7 CF 04 05         [ 2]  377 	ldw	_ff1+0, x
                                    378 ;	./src/OSAL_Memory.c: 522: HAL_EXIT_CRITICAL_SECTION( intState );  // Re-enable interrupts.
      0085CA                        379 00128$:
                                    380 ;	./src/OSAL_Memory.c: 523: }
      0085CA 5B 04            [ 2]  381 	addw	sp, #4
      0085CC 81               [ 4]  382 	ret
                                    383 	.area CODE
                                    384 	.area CONST
                                    385 	.area INITIALIZER
                                    386 	.area CABS (ABS)
