                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module OSAL
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _osalInitTasks
                                     12 	.globl _osalTimerInit
                                     13 	.globl _osal_mem_free
                                     14 	.globl _osal_mem_alloc
                                     15 	.globl _osal_mem_kick
                                     16 	.globl _osal_mem_init
                                     17 	.globl _memset
                                     18 	.globl _osal_qHead
                                     19 	.globl _osal_memcpy
                                     20 	.globl _osal_revmemcpy
                                     21 	.globl _osal_memdup
                                     22 	.globl _osal_memcmp
                                     23 	.globl _osal_memset
                                     24 	.globl _osal_msg_allocate
                                     25 	.globl _osal_msg_deallocate
                                     26 	.globl _osal_msg_send
                                     27 	.globl _osal_msg_push_front
                                     28 	.globl _osal_msg_receive
                                     29 	.globl _osal_msg_find
                                     30 	.globl _osal_msg_enqueue
                                     31 	.globl _osal_msg_dequeue
                                     32 	.globl _osal_msg_push
                                     33 	.globl _osal_msg_extract
                                     34 	.globl _osal_msg_enqueue_max
                                     35 	.globl _osal_set_event
                                     36 	.globl _osal_clear_event
                                     37 	.globl _osal_isr_register
                                     38 	.globl _osal_int_enable
                                     39 	.globl _osal_int_disable
                                     40 	.globl _osal_init_system
                                     41 	.globl _osal_start_system
                                     42 	.globl _osal_run_system
                                     43 	.globl _osal_self
                                     44 ;--------------------------------------------------------
                                     45 ; ram data
                                     46 ;--------------------------------------------------------
                                     47 	.area DATA
      000001                         48 _osal_qHead::
      000001                         49 	.ds 2
                                     50 ;--------------------------------------------------------
                                     51 ; ram data
                                     52 ;--------------------------------------------------------
                                     53 	.area INITIALIZED
      00040E                         54 _activeTaskID:
      00040E                         55 	.ds 1
                                     56 ;--------------------------------------------------------
                                     57 ; absolute external ram data
                                     58 ;--------------------------------------------------------
                                     59 	.area DABS (ABS)
                                     60 
                                     61 ; default segment ordering for linker
                                     62 	.area HOME
                                     63 	.area GSINIT
                                     64 	.area GSFINAL
                                     65 	.area CONST
                                     66 	.area INITIALIZER
                                     67 	.area CODE
                                     68 
                                     69 ;--------------------------------------------------------
                                     70 ; global & static initialisations
                                     71 ;--------------------------------------------------------
                                     72 	.area HOME
                                     73 	.area GSINIT
                                     74 	.area GSFINAL
                                     75 	.area GSINIT
                                     76 ;--------------------------------------------------------
                                     77 ; Home
                                     78 ;--------------------------------------------------------
                                     79 	.area HOME
                                     80 	.area HOME
                                     81 ;--------------------------------------------------------
                                     82 ; code
                                     83 ;--------------------------------------------------------
                                     84 	.area CODE
                                     85 ;	./src/OSAL.c: 49: void *osal_memcpy( void *dst, const void *src, unsigned int len )
                                     86 ;	-----------------------------------------
                                     87 ;	 function osal_memcpy
                                     88 ;	-----------------------------------------
      00802E                         89 _osal_memcpy:
      00802E 52 06            [ 2]   90 	sub	sp, #6
                                     91 ;	./src/OSAL.c: 54: pSrc = src;
      008030 16 0B            [ 2]   92 	ldw	y, (0x0b, sp)
                                     93 ;	./src/OSAL.c: 55: pDst = dst;
      008032 1E 09            [ 2]   94 	ldw	x, (0x09, sp)
                                     95 ;	./src/OSAL.c: 57: while ( len-- )
      008034 17 03            [ 2]   96 	ldw	(0x03, sp), y
      008036 16 0D            [ 2]   97 	ldw	y, (0x0d, sp)
      008038 17 05            [ 2]   98 	ldw	(0x05, sp), y
      00803A                         99 00101$:
      00803A 16 05            [ 2]  100 	ldw	y, (0x05, sp)
      00803C 17 01            [ 2]  101 	ldw	(0x01, sp), y
      00803E 16 05            [ 2]  102 	ldw	y, (0x05, sp)
      008040 90 5A            [ 2]  103 	decw	y
      008042 17 05            [ 2]  104 	ldw	(0x05, sp), y
      008044 16 01            [ 2]  105 	ldw	y, (0x01, sp)
      008046 27 0E            [ 1]  106 	jreq	00108$
                                    107 ;	./src/OSAL.c: 58: *pDst++ = *pSrc++;
      008048 16 03            [ 2]  108 	ldw	y, (0x03, sp)
      00804A 90 F6            [ 1]  109 	ld	a, (y)
      00804C 16 03            [ 2]  110 	ldw	y, (0x03, sp)
      00804E 90 5C            [ 1]  111 	incw	y
      008050 17 03            [ 2]  112 	ldw	(0x03, sp), y
      008052 F7               [ 1]  113 	ld	(x), a
      008053 5C               [ 1]  114 	incw	x
      008054 20 E4            [ 2]  115 	jra	00101$
      008056                        116 00108$:
                                    117 ;	./src/OSAL.c: 60: return ( pDst );
                                    118 ;	./src/OSAL.c: 61: }
      008056 5B 06            [ 2]  119 	addw	sp, #6
      008058 81               [ 4]  120 	ret
                                    121 ;	./src/OSAL.c: 80: void *osal_revmemcpy( void *dst, const void *src, unsigned int len )
                                    122 ;	-----------------------------------------
                                    123 ;	 function osal_revmemcpy
                                    124 ;	-----------------------------------------
      008059                        125 _osal_revmemcpy:
      008059 52 06            [ 2]  126 	sub	sp, #6
                                    127 ;	./src/OSAL.c: 85: pSrc = src;
      00805B 16 0B            [ 2]  128 	ldw	y, (0x0b, sp)
                                    129 ;	./src/OSAL.c: 86: pSrc += (len-1);
      00805D 1E 0D            [ 2]  130 	ldw	x, (0x0d, sp)
      00805F 5A               [ 2]  131 	decw	x
      008060 1F 05            [ 2]  132 	ldw	(0x05, sp), x
      008062 72 F9 05         [ 2]  133 	addw	y, (0x05, sp)
                                    134 ;	./src/OSAL.c: 87: pDst = dst;
      008065 1E 09            [ 2]  135 	ldw	x, (0x09, sp)
                                    136 ;	./src/OSAL.c: 89: while ( len-- )
      008067 17 03            [ 2]  137 	ldw	(0x03, sp), y
      008069 16 0D            [ 2]  138 	ldw	y, (0x0d, sp)
      00806B 17 05            [ 2]  139 	ldw	(0x05, sp), y
      00806D                        140 00101$:
      00806D 16 05            [ 2]  141 	ldw	y, (0x05, sp)
      00806F 17 01            [ 2]  142 	ldw	(0x01, sp), y
      008071 16 05            [ 2]  143 	ldw	y, (0x05, sp)
      008073 90 5A            [ 2]  144 	decw	y
      008075 17 05            [ 2]  145 	ldw	(0x05, sp), y
      008077 16 01            [ 2]  146 	ldw	y, (0x01, sp)
      008079 27 0E            [ 1]  147 	jreq	00108$
                                    148 ;	./src/OSAL.c: 90: *pDst++ = *pSrc--;
      00807B 16 03            [ 2]  149 	ldw	y, (0x03, sp)
      00807D 90 F6            [ 1]  150 	ld	a, (y)
      00807F 16 03            [ 2]  151 	ldw	y, (0x03, sp)
      008081 90 5A            [ 2]  152 	decw	y
      008083 17 03            [ 2]  153 	ldw	(0x03, sp), y
      008085 F7               [ 1]  154 	ld	(x), a
      008086 5C               [ 1]  155 	incw	x
      008087 20 E4            [ 2]  156 	jra	00101$
      008089                        157 00108$:
                                    158 ;	./src/OSAL.c: 92: return ( pDst );
                                    159 ;	./src/OSAL.c: 93: }
      008089 5B 06            [ 2]  160 	addw	sp, #6
      00808B 81               [ 4]  161 	ret
                                    162 ;	./src/OSAL.c: 107: void *osal_memdup( const void *src, unsigned int len )
                                    163 ;	-----------------------------------------
                                    164 ;	 function osal_memdup
                                    165 ;	-----------------------------------------
      00808C                        166 _osal_memdup:
      00808C 89               [ 2]  167 	pushw	x
                                    168 ;	./src/OSAL.c: 111: pDst = osal_mem_alloc( len );
      00808D 1E 07            [ 2]  169 	ldw	x, (0x07, sp)
      00808F 89               [ 2]  170 	pushw	x
      008090 CD 84 71         [ 4]  171 	call	_osal_mem_alloc
      008093 5B 02            [ 2]  172 	addw	sp, #2
                                    173 ;	./src/OSAL.c: 114: VOID osal_memcpy( pDst, src, len );
      008095 1F 01            [ 2]  174 	ldw	(0x01, sp), x
                                    175 ;	./src/OSAL.c: 112: if ( pDst )
      008097 5D               [ 2]  176 	tnzw	x
      008098 27 0E            [ 1]  177 	jreq	00102$
                                    178 ;	./src/OSAL.c: 114: VOID osal_memcpy( pDst, src, len );
      00809A 1E 07            [ 2]  179 	ldw	x, (0x07, sp)
      00809C 89               [ 2]  180 	pushw	x
      00809D 1E 07            [ 2]  181 	ldw	x, (0x07, sp)
      00809F 89               [ 2]  182 	pushw	x
      0080A0 1E 05            [ 2]  183 	ldw	x, (0x05, sp)
      0080A2 89               [ 2]  184 	pushw	x
      0080A3 CD 80 2E         [ 4]  185 	call	_osal_memcpy
      0080A6 5B 06            [ 2]  186 	addw	sp, #6
      0080A8                        187 00102$:
                                    188 ;	./src/OSAL.c: 117: return ( (void *)pDst );
      0080A8 1E 01            [ 2]  189 	ldw	x, (0x01, sp)
                                    190 ;	./src/OSAL.c: 118: }
      0080AA 5B 02            [ 2]  191 	addw	sp, #2
      0080AC 81               [ 4]  192 	ret
                                    193 ;	./src/OSAL.c: 133: uint8 osal_memcmp( const void *src1, const void *src2, unsigned int len )
                                    194 ;	-----------------------------------------
                                    195 ;	 function osal_memcmp
                                    196 ;	-----------------------------------------
      0080AD                        197 _osal_memcmp:
      0080AD 52 06            [ 2]  198 	sub	sp, #6
                                    199 ;	./src/OSAL.c: 138: pSrc1 = src1;
      0080AF 16 09            [ 2]  200 	ldw	y, (0x09, sp)
                                    201 ;	./src/OSAL.c: 139: pSrc2 = src2;
      0080B1 1E 0B            [ 2]  202 	ldw	x, (0x0b, sp)
                                    203 ;	./src/OSAL.c: 141: while ( len-- )
      0080B3 17 03            [ 2]  204 	ldw	(0x03, sp), y
      0080B5 1F 05            [ 2]  205 	ldw	(0x05, sp), x
      0080B7 16 0D            [ 2]  206 	ldw	y, (0x0d, sp)
      0080B9                        207 00103$:
      0080B9 17 01            [ 2]  208 	ldw	(0x01, sp), y
      0080BB 90 5A            [ 2]  209 	decw	y
      0080BD 1E 01            [ 2]  210 	ldw	x, (0x01, sp)
      0080BF 27 18            [ 1]  211 	jreq	00105$
                                    212 ;	./src/OSAL.c: 143: if( *pSrc1++ != *pSrc2++ )
      0080C1 1E 03            [ 2]  213 	ldw	x, (0x03, sp)
      0080C3 F6               [ 1]  214 	ld	a, (x)
      0080C4 6B 02            [ 1]  215 	ld	(0x02, sp), a
      0080C6 1E 03            [ 2]  216 	ldw	x, (0x03, sp)
      0080C8 5C               [ 1]  217 	incw	x
      0080C9 1F 03            [ 2]  218 	ldw	(0x03, sp), x
      0080CB 1E 05            [ 2]  219 	ldw	x, (0x05, sp)
      0080CD F6               [ 1]  220 	ld	a, (x)
      0080CE 1E 05            [ 2]  221 	ldw	x, (0x05, sp)
      0080D0 5C               [ 1]  222 	incw	x
      0080D1 1F 05            [ 2]  223 	ldw	(0x05, sp), x
      0080D3 11 02            [ 1]  224 	cp	a, (0x02, sp)
      0080D5 27 E2            [ 1]  225 	jreq	00103$
                                    226 ;	./src/OSAL.c: 144: return FALSE;
      0080D7 4F               [ 1]  227 	clr	a
                                    228 ;	./src/OSAL.c: 146: return TRUE;
      0080D8 C5                     229 	.byte 0xc5
      0080D9                        230 00105$:
      0080D9 A6 01            [ 1]  231 	ld	a, #0x01
      0080DB                        232 00106$:
                                    233 ;	./src/OSAL.c: 147: }
      0080DB 5B 06            [ 2]  234 	addw	sp, #6
      0080DD 81               [ 4]  235 	ret
                                    236 ;	./src/OSAL.c: 163: void *osal_memset( void *dest, uint8 value, int len )
                                    237 ;	-----------------------------------------
                                    238 ;	 function osal_memset
                                    239 ;	-----------------------------------------
      0080DE                        240 _osal_memset:
                                    241 ;	./src/OSAL.c: 165: return memset( dest, value, len );
      0080DE 5F               [ 1]  242 	clrw	x
      0080DF 7B 05            [ 1]  243 	ld	a, (0x05, sp)
      0080E1 97               [ 1]  244 	ld	xl, a
      0080E2 16 06            [ 2]  245 	ldw	y, (0x06, sp)
      0080E4 90 89            [ 2]  246 	pushw	y
      0080E6 89               [ 2]  247 	pushw	x
      0080E7 1E 07            [ 2]  248 	ldw	x, (0x07, sp)
      0080E9 89               [ 2]  249 	pushw	x
      0080EA CD 8D 1B         [ 4]  250 	call	_memset
      0080ED 5B 06            [ 2]  251 	addw	sp, #6
                                    252 ;	./src/OSAL.c: 166: }
      0080EF 81               [ 4]  253 	ret
                                    254 ;	./src/OSAL.c: 194: uint8 * osal_msg_allocate( uint16 len )
                                    255 ;	-----------------------------------------
                                    256 ;	 function osal_msg_allocate
                                    257 ;	-----------------------------------------
      0080F0                        258 _osal_msg_allocate:
                                    259 ;	./src/OSAL.c: 198: if ( len == 0 )
                                    260 ;	./src/OSAL.c: 199: return ( NULL );
      0080F0 1E 03            [ 2]  261 	ldw	x, (0x03, sp)
      0080F2 26 01            [ 1]  262 	jrne	00102$
      0080F4 81               [ 4]  263 	ret
      0080F5                        264 00102$:
                                    265 ;	./src/OSAL.c: 201: hdr = (osal_msg_hdr_t *) osal_mem_alloc( (short)(len + sizeof( osal_msg_hdr_t )) );
      0080F5 1E 03            [ 2]  266 	ldw	x, (0x03, sp)
      0080F7 1C 00 05         [ 2]  267 	addw	x, #0x0005
      0080FA 89               [ 2]  268 	pushw	x
      0080FB CD 84 71         [ 4]  269 	call	_osal_mem_alloc
      0080FE 5B 02            [ 2]  270 	addw	sp, #2
      008100 51               [ 1]  271 	exgw	x, y
                                    272 ;	./src/OSAL.c: 202: if ( hdr )
      008101 90 5D            [ 2]  273 	tnzw	y
      008103 27 18            [ 1]  274 	jreq	00104$
                                    275 ;	./src/OSAL.c: 204: hdr->next = NULL;
      008105 93               [ 1]  276 	ldw	x, y
      008106 6F 01            [ 1]  277 	clr	(0x1, x)
      008108 7F               [ 1]  278 	clr	(x)
                                    279 ;	./src/OSAL.c: 205: hdr->len = len;
      008109 93               [ 1]  280 	ldw	x, y
      00810A 5C               [ 1]  281 	incw	x
      00810B 5C               [ 1]  282 	incw	x
      00810C 7B 04            [ 1]  283 	ld	a, (0x04, sp)
      00810E E7 01            [ 1]  284 	ld	(0x1, x), a
      008110 7B 03            [ 1]  285 	ld	a, (0x03, sp)
      008112 F7               [ 1]  286 	ld	(x), a
                                    287 ;	./src/OSAL.c: 206: hdr->dest_id = TASK_NO_TASK;
      008113 A6 FF            [ 1]  288 	ld	a, #0xff
      008115 90 E7 04         [ 1]  289 	ld	(0x0004, y), a
                                    290 ;	./src/OSAL.c: 207: return ( (uint8 *) (hdr + 1) );
      008118 93               [ 1]  291 	ldw	x, y
      008119 1C 00 05         [ 2]  292 	addw	x, #0x0005
      00811C 81               [ 4]  293 	ret
      00811D                        294 00104$:
                                    295 ;	./src/OSAL.c: 210: return ( NULL );
      00811D 5F               [ 1]  296 	clrw	x
                                    297 ;	./src/OSAL.c: 211: }
      00811E 81               [ 4]  298 	ret
                                    299 ;	./src/OSAL.c: 227: uint8 osal_msg_deallocate( uint8 *msg_ptr )
                                    300 ;	-----------------------------------------
                                    301 ;	 function osal_msg_deallocate
                                    302 ;	-----------------------------------------
      00811F                        303 _osal_msg_deallocate:
                                    304 ;	./src/OSAL.c: 231: if ( msg_ptr == NULL )
      00811F 1E 03            [ 2]  305 	ldw	x, (0x03, sp)
      008121 26 03            [ 1]  306 	jrne	00102$
                                    307 ;	./src/OSAL.c: 232: return ( INVALID_MSG_POINTER );
      008123 A6 05            [ 1]  308 	ld	a, #0x05
      008125 81               [ 4]  309 	ret
      008126                        310 00102$:
                                    311 ;	./src/OSAL.c: 235: if ( OSAL_MSG_ID( msg_ptr ) != TASK_NO_TASK )
      008126 1E 03            [ 2]  312 	ldw	x, (0x03, sp)
      008128 1C FF FF         [ 2]  313 	addw	x, #0xffff
      00812B F6               [ 1]  314 	ld	a, (x)
      00812C 4C               [ 1]  315 	inc	a
      00812D 27 03            [ 1]  316 	jreq	00104$
                                    317 ;	./src/OSAL.c: 236: return ( MSG_BUFFER_NOT_AVAIL );
      00812F A6 04            [ 1]  318 	ld	a, #0x04
      008131 81               [ 4]  319 	ret
      008132                        320 00104$:
                                    321 ;	./src/OSAL.c: 238: x = (uint8 *)((uint8 *)msg_ptr - sizeof( osal_msg_hdr_t ));
      008132 1E 03            [ 2]  322 	ldw	x, (0x03, sp)
      008134 1D 00 05         [ 2]  323 	subw	x, #0x0005
                                    324 ;	./src/OSAL.c: 240: osal_mem_free( (void *)x );
      008137 89               [ 2]  325 	pushw	x
      008138 CD 85 87         [ 4]  326 	call	_osal_mem_free
      00813B 85               [ 2]  327 	popw	x
                                    328 ;	./src/OSAL.c: 242: return ( SUCCESS );
      00813C 4F               [ 1]  329 	clr	a
                                    330 ;	./src/OSAL.c: 243: }
      00813D 81               [ 4]  331 	ret
                                    332 ;	./src/OSAL.c: 262: uint8 osal_msg_send( uint8 destination_task, uint8 *msg_ptr )
                                    333 ;	-----------------------------------------
                                    334 ;	 function osal_msg_send
                                    335 ;	-----------------------------------------
      00813E                        336 _osal_msg_send:
                                    337 ;	./src/OSAL.c: 264: return ( osal_msg_enqueue_push( destination_task, msg_ptr, FALSE ) );
      00813E 4B 00            [ 1]  338 	push	#0x00
      008140 1E 05            [ 2]  339 	ldw	x, (0x05, sp)
      008142 89               [ 2]  340 	pushw	x
      008143 7B 06            [ 1]  341 	ld	a, (0x06, sp)
      008145 88               [ 1]  342 	push	a
      008146 CD 81 5A         [ 4]  343 	call	_osal_msg_enqueue_push
      008149 5B 04            [ 2]  344 	addw	sp, #4
                                    345 ;	./src/OSAL.c: 265: }
      00814B 81               [ 4]  346 	ret
                                    347 ;	./src/OSAL.c: 283: uint8 osal_msg_push_front( uint8 destination_task, uint8 *msg_ptr )
                                    348 ;	-----------------------------------------
                                    349 ;	 function osal_msg_push_front
                                    350 ;	-----------------------------------------
      00814C                        351 _osal_msg_push_front:
                                    352 ;	./src/OSAL.c: 285: return ( osal_msg_enqueue_push( destination_task, msg_ptr, TRUE ) );
      00814C 4B 01            [ 1]  353 	push	#0x01
      00814E 1E 05            [ 2]  354 	ldw	x, (0x05, sp)
      008150 89               [ 2]  355 	pushw	x
      008151 7B 06            [ 1]  356 	ld	a, (0x06, sp)
      008153 88               [ 1]  357 	push	a
      008154 CD 81 5A         [ 4]  358 	call	_osal_msg_enqueue_push
      008157 5B 04            [ 2]  359 	addw	sp, #4
                                    360 ;	./src/OSAL.c: 286: }
      008159 81               [ 4]  361 	ret
                                    362 ;	./src/OSAL.c: 306: static uint8 osal_msg_enqueue_push( uint8 destination_task, uint8 *msg_ptr, uint8 push )
                                    363 ;	-----------------------------------------
                                    364 ;	 function osal_msg_enqueue_push
                                    365 ;	-----------------------------------------
      00815A                        366 _osal_msg_enqueue_push:
                                    367 ;	./src/OSAL.c: 308: if ( msg_ptr == NULL )
      00815A 1E 04            [ 2]  368 	ldw	x, (0x04, sp)
      00815C 26 03            [ 1]  369 	jrne	00102$
                                    370 ;	./src/OSAL.c: 310: return ( INVALID_MSG_POINTER );
      00815E A6 05            [ 1]  371 	ld	a, #0x05
      008160 81               [ 4]  372 	ret
      008161                        373 00102$:
                                    374 ;	./src/OSAL.c: 313: if ( destination_task >= tasksCnt )
      008161 C6 80 26         [ 1]  375 	ld	a, _tasksCnt+0
      008164 11 03            [ 1]  376 	cp	a, (0x03, sp)
      008166 22 0A            [ 1]  377 	jrugt	00104$
                                    378 ;	./src/OSAL.c: 315: osal_msg_deallocate( msg_ptr );
      008168 1E 04            [ 2]  379 	ldw	x, (0x04, sp)
      00816A 89               [ 2]  380 	pushw	x
      00816B CD 81 1F         [ 4]  381 	call	_osal_msg_deallocate
      00816E 85               [ 2]  382 	popw	x
                                    383 ;	./src/OSAL.c: 316: return ( INVALID_TASK );
      00816F A6 03            [ 1]  384 	ld	a, #0x03
      008171 81               [ 4]  385 	ret
      008172                        386 00104$:
                                    387 ;	./src/OSAL.c: 320: if ( OSAL_MSG_NEXT( msg_ptr ) != NULL ||
      008172 16 04            [ 2]  388 	ldw	y, (0x04, sp)
      008174 93               [ 1]  389 	ldw	x, y
      008175 1C FF FB         [ 2]  390 	addw	x, #0xfffb
      008178 FE               [ 2]  391 	ldw	x, (x)
      008179 26 06            [ 1]  392 	jrne	00105$
                                    393 ;	./src/OSAL.c: 321: OSAL_MSG_ID( msg_ptr ) != TASK_NO_TASK )
      00817B 93               [ 1]  394 	ldw	x, y
      00817C 5A               [ 2]  395 	decw	x
      00817D F6               [ 1]  396 	ld	a, (x)
      00817E 4C               [ 1]  397 	inc	a
      00817F 27 0A            [ 1]  398 	jreq	00106$
      008181                        399 00105$:
                                    400 ;	./src/OSAL.c: 323: osal_msg_deallocate( msg_ptr );
      008181 1E 04            [ 2]  401 	ldw	x, (0x04, sp)
      008183 89               [ 2]  402 	pushw	x
      008184 CD 81 1F         [ 4]  403 	call	_osal_msg_deallocate
      008187 85               [ 2]  404 	popw	x
                                    405 ;	./src/OSAL.c: 324: return ( INVALID_MSG_POINTER );
      008188 A6 05            [ 1]  406 	ld	a, #0x05
      00818A 81               [ 4]  407 	ret
      00818B                        408 00106$:
                                    409 ;	./src/OSAL.c: 327: OSAL_MSG_ID( msg_ptr ) = destination_task;
      00818B 7B 03            [ 1]  410 	ld	a, (0x03, sp)
      00818D F7               [ 1]  411 	ld	(x), a
                                    412 ;	./src/OSAL.c: 332: osal_msg_push( &osal_qHead, msg_ptr );
      00818E 1E 04            [ 2]  413 	ldw	x, (0x04, sp)
                                    414 ;	./src/OSAL.c: 329: if ( push == TRUE )
      008190 7B 06            [ 1]  415 	ld	a, (0x06, sp)
      008192 4A               [ 1]  416 	dec	a
      008193 26 0C            [ 1]  417 	jrne	00109$
                                    418 ;	./src/OSAL.c: 332: osal_msg_push( &osal_qHead, msg_ptr );
      008195 89               [ 2]  419 	pushw	x
      008196 4B 01            [ 1]  420 	push	#<(_osal_qHead + 0)
      008198 4B 00            [ 1]  421 	push	#((_osal_qHead + 0) >> 8)
      00819A CD 82 A5         [ 4]  422 	call	_osal_msg_push
      00819D 5B 04            [ 2]  423 	addw	sp, #4
      00819F 20 0A            [ 2]  424 	jra	00110$
      0081A1                        425 00109$:
                                    426 ;	./src/OSAL.c: 337: osal_msg_enqueue( &osal_qHead, msg_ptr );
      0081A1 89               [ 2]  427 	pushw	x
      0081A2 4B 01            [ 1]  428 	push	#<(_osal_qHead + 0)
      0081A4 4B 00            [ 1]  429 	push	#((_osal_qHead + 0) >> 8)
      0081A6 CD 82 49         [ 4]  430 	call	_osal_msg_enqueue
      0081A9 5B 04            [ 2]  431 	addw	sp, #4
      0081AB                        432 00110$:
                                    433 ;	./src/OSAL.c: 341: osal_set_event( destination_task, SYS_EVENT_MSG );
      0081AB 4B 00            [ 1]  434 	push	#0x00
      0081AD 4B 80            [ 1]  435 	push	#0x80
      0081AF 7B 05            [ 1]  436 	ld	a, (0x05, sp)
      0081B1 88               [ 1]  437 	push	a
      0081B2 CD 83 3A         [ 4]  438 	call	_osal_set_event
      0081B5 5B 03            [ 2]  439 	addw	sp, #3
                                    440 ;	./src/OSAL.c: 343: return ( SUCCESS );
      0081B7 4F               [ 1]  441 	clr	a
                                    442 ;	./src/OSAL.c: 344: }
      0081B8 81               [ 4]  443 	ret
                                    444 ;	./src/OSAL.c: 359: uint8 *osal_msg_receive( uint8 task_id )
                                    445 ;	-----------------------------------------
                                    446 ;	 function osal_msg_receive
                                    447 ;	-----------------------------------------
      0081B9                        448 _osal_msg_receive:
      0081B9 52 06            [ 2]  449 	sub	sp, #6
                                    450 ;	./src/OSAL.c: 362: osal_msg_hdr_t *prevHdr = NULL;
      0081BB 5F               [ 1]  451 	clrw	x
      0081BC 1F 01            [ 2]  452 	ldw	(0x01, sp), x
                                    453 ;	./src/OSAL.c: 363: osal_msg_hdr_t *foundHdr = NULL;
      0081BE 5F               [ 1]  454 	clrw	x
      0081BF 1F 03            [ 2]  455 	ldw	(0x03, sp), x
                                    456 ;	./src/OSAL.c: 367: HAL_ENTER_CRITICAL_SECTION(intState);
      0081C1 9B               [ 1]  457 	sim
      0081C2 9D               [ 1]  458 	nop
      0081C3 9D               [ 1]  459 	nop
                                    460 ;	./src/OSAL.c: 370: listHdr = osal_qHead;
      0081C4 90 CE 00 01      [ 2]  461 	ldw	y, _osal_qHead+0
                                    462 ;	./src/OSAL.c: 373: while ( listHdr != NULL )
      0081C8                        463 00114$:
      0081C8 90 5D            [ 2]  464 	tnzw	y
      0081CA 27 1E            [ 1]  465 	jreq	00116$
                                    466 ;	./src/OSAL.c: 375: if ( (listHdr - 1)->dest_id == task_id )
      0081CC 93               [ 1]  467 	ldw	x, y
      0081CD 1D 00 05         [ 2]  468 	subw	x, #0x0005
      0081D0 1F 05            [ 2]  469 	ldw	(0x05, sp), x
      0081D2 E6 04            [ 1]  470 	ld	a, (0x4, x)
      0081D4 11 09            [ 1]  471 	cp	a, (0x09, sp)
      0081D6 26 06            [ 1]  472 	jrne	00111$
                                    473 ;	./src/OSAL.c: 377: if ( foundHdr == NULL )
      0081D8 1E 03            [ 2]  474 	ldw	x, (0x03, sp)
      0081DA 26 0E            [ 1]  475 	jrne	00116$
                                    476 ;	./src/OSAL.c: 380: foundHdr = listHdr;
      0081DC 17 03            [ 2]  477 	ldw	(0x03, sp), y
                                    478 ;	./src/OSAL.c: 385: break;
      0081DE                        479 00111$:
                                    480 ;	./src/OSAL.c: 388: if ( foundHdr == NULL )
      0081DE 1E 03            [ 2]  481 	ldw	x, (0x03, sp)
      0081E0 26 02            [ 1]  482 	jrne	00113$
                                    483 ;	./src/OSAL.c: 390: prevHdr = listHdr;
      0081E2 17 01            [ 2]  484 	ldw	(0x01, sp), y
      0081E4                        485 00113$:
                                    486 ;	./src/OSAL.c: 392: listHdr = OSAL_MSG_NEXT( listHdr );
      0081E4 1E 05            [ 2]  487 	ldw	x, (0x05, sp)
      0081E6 FE               [ 2]  488 	ldw	x, (x)
      0081E7 51               [ 1]  489 	exgw	x, y
      0081E8 20 DE            [ 2]  490 	jra	00114$
      0081EA                        491 00116$:
                                    492 ;	./src/OSAL.c: 396: if ( listHdr != NULL )
      0081EA 90 5D            [ 2]  493 	tnzw	y
      0081EC 27 0E            [ 1]  494 	jreq	00118$
                                    495 ;	./src/OSAL.c: 399: osal_set_event( task_id, SYS_EVENT_MSG );
      0081EE 4B 00            [ 1]  496 	push	#0x00
      0081F0 4B 80            [ 1]  497 	push	#0x80
      0081F2 7B 0B            [ 1]  498 	ld	a, (0x0b, sp)
      0081F4 88               [ 1]  499 	push	a
      0081F5 CD 83 3A         [ 4]  500 	call	_osal_set_event
      0081F8 5B 03            [ 2]  501 	addw	sp, #3
      0081FA 20 0C            [ 2]  502 	jra	00119$
      0081FC                        503 00118$:
                                    504 ;	./src/OSAL.c: 404: osal_clear_event( task_id, SYS_EVENT_MSG );
      0081FC 4B 00            [ 1]  505 	push	#0x00
      0081FE 4B 80            [ 1]  506 	push	#0x80
      008200 7B 0B            [ 1]  507 	ld	a, (0x0b, sp)
      008202 88               [ 1]  508 	push	a
      008203 CD 83 5E         [ 4]  509 	call	_osal_clear_event
      008206 5B 03            [ 2]  510 	addw	sp, #3
      008208                        511 00119$:
                                    512 ;	./src/OSAL.c: 408: if ( foundHdr != NULL )
      008208 1E 03            [ 2]  513 	ldw	x, (0x03, sp)
      00820A 27 10            [ 1]  514 	jreq	00122$
                                    515 ;	./src/OSAL.c: 411: osal_msg_extract( &osal_qHead, foundHdr, prevHdr );
      00820C 1E 01            [ 2]  516 	ldw	x, (0x01, sp)
      00820E 16 03            [ 2]  517 	ldw	y, (0x03, sp)
      008210 89               [ 2]  518 	pushw	x
      008211 90 89            [ 2]  519 	pushw	y
      008213 4B 01            [ 1]  520 	push	#<(_osal_qHead + 0)
      008215 4B 00            [ 1]  521 	push	#((_osal_qHead + 0) >> 8)
      008217 CD 82 BC         [ 4]  522 	call	_osal_msg_extract
      00821A 5B 06            [ 2]  523 	addw	sp, #6
                                    524 ;	./src/OSAL.c: 415: HAL_EXIT_CRITICAL_SECTION(intState);
      00821C                        525 00122$:
                                    526 ;	./src/OSAL.c: 417: return ( (uint8*) foundHdr );
      00821C 1E 03            [ 2]  527 	ldw	x, (0x03, sp)
                                    528 ;	./src/OSAL.c: 418: }
      00821E 5B 06            [ 2]  529 	addw	sp, #6
      008220 81               [ 4]  530 	ret
                                    531 ;	./src/OSAL.c: 438: osal_event_hdr_t *osal_msg_find(uint8 task_id, uint8 event)
                                    532 ;	-----------------------------------------
                                    533 ;	 function osal_msg_find
                                    534 ;	-----------------------------------------
      008221                        535 _osal_msg_find:
      008221 89               [ 2]  536 	pushw	x
                                    537 ;	./src/OSAL.c: 443: HAL_ENTER_CRITICAL_SECTION(intState);  // Hold off interrupts.
      008222 9B               [ 1]  538 	sim
      008223 9D               [ 1]  539 	nop
      008224 9D               [ 1]  540 	nop
                                    541 ;	./src/OSAL.c: 445: pHdr = osal_qHead;  // Point to the top of the queue.
      008225 CE 00 01         [ 2]  542 	ldw	x, _osal_qHead+0
                                    543 ;	./src/OSAL.c: 448: while (pHdr != NULL)
      008228                        544 00110$:
                                    545 ;	./src/OSAL.c: 450: if (((pHdr-1)->dest_id == task_id) && (((osal_event_hdr_t *)pHdr)->event == event))
      008228 1F 01            [ 2]  546 	ldw	(0x01, sp), x
                                    547 ;	./src/OSAL.c: 448: while (pHdr != NULL)
      00822A 5D               [ 2]  548 	tnzw	x
      00822B 27 17            [ 1]  549 	jreq	00113$
                                    550 ;	./src/OSAL.c: 450: if (((pHdr-1)->dest_id == task_id) && (((osal_event_hdr_t *)pHdr)->event == event))
      00822D 1D 00 05         [ 2]  551 	subw	x, #0x0005
      008230 90 93            [ 1]  552 	ldw	y, x
      008232 90 E6 04         [ 1]  553 	ld	a, (0x4, y)
      008235 11 05            [ 1]  554 	cp	a, (0x05, sp)
      008237 26 08            [ 1]  555 	jrne	00108$
      008239 16 01            [ 2]  556 	ldw	y, (0x01, sp)
      00823B 90 F6            [ 1]  557 	ld	a, (y)
      00823D 11 06            [ 1]  558 	cp	a, (0x06, sp)
      00823F 27 03            [ 1]  559 	jreq	00113$
                                    560 ;	./src/OSAL.c: 452: break;
      008241                        561 00108$:
                                    562 ;	./src/OSAL.c: 455: pHdr = OSAL_MSG_NEXT(pHdr);
      008241 FE               [ 2]  563 	ldw	x, (x)
      008242 20 E4            [ 2]  564 	jra	00110$
                                    565 ;	./src/OSAL.c: 458: HAL_EXIT_CRITICAL_SECTION(intState);  // Release interrupts.
      008244                        566 00113$:
                                    567 ;	./src/OSAL.c: 460: return (osal_event_hdr_t *)pHdr;
      008244 1E 01            [ 2]  568 	ldw	x, (0x01, sp)
                                    569 ;	./src/OSAL.c: 461: }
      008246 5B 02            [ 2]  570 	addw	sp, #2
      008248 81               [ 4]  571 	ret
                                    572 ;	./src/OSAL.c: 475: void osal_msg_enqueue( osal_msg_q_t *q_ptr, void *msg_ptr )
                                    573 ;	-----------------------------------------
                                    574 ;	 function osal_msg_enqueue
                                    575 ;	-----------------------------------------
      008249                        576 _osal_msg_enqueue:
      008249 52 04            [ 2]  577 	sub	sp, #4
                                    578 ;	./src/OSAL.c: 481: HAL_ENTER_CRITICAL_SECTION(intState);
      00824B 9B               [ 1]  579 	sim
      00824C 9D               [ 1]  580 	nop
      00824D 9D               [ 1]  581 	nop
                                    582 ;	./src/OSAL.c: 483: OSAL_MSG_NEXT( msg_ptr ) = NULL;
      00824E 1E 09            [ 2]  583 	ldw	x, (0x09, sp)
      008250 1D 00 05         [ 2]  584 	subw	x, #0x0005
      008253 6F 01            [ 1]  585 	clr	(0x1, x)
      008255 7F               [ 1]  586 	clr	(x)
                                    587 ;	./src/OSAL.c: 485: if ( *q_ptr == NULL )
      008256 16 07            [ 2]  588 	ldw	y, (0x07, sp)
      008258 17 03            [ 2]  589 	ldw	(0x03, sp), y
      00825A 93               [ 1]  590 	ldw	x, y
      00825B FE               [ 2]  591 	ldw	x, (x)
      00825C 26 07            [ 1]  592 	jrne	00109$
                                    593 ;	./src/OSAL.c: 487: *q_ptr = msg_ptr;
      00825E 1E 03            [ 2]  594 	ldw	x, (0x03, sp)
      008260 16 09            [ 2]  595 	ldw	y, (0x09, sp)
      008262 FF               [ 2]  596 	ldw	(x), y
      008263 20 13            [ 2]  597 	jra	00116$
      008265                        598 00109$:
                                    599 ;	./src/OSAL.c: 492: for ( list = *q_ptr; OSAL_MSG_NEXT( list ) != NULL; list = OSAL_MSG_NEXT( list ) );
      008265 1F 03            [ 2]  600 	ldw	(0x03, sp), x
      008267                        601 00114$:
      008267 1E 03            [ 2]  602 	ldw	x, (0x03, sp)
      008269 1D 00 05         [ 2]  603 	subw	x, #0x0005
      00826C 1F 01            [ 2]  604 	ldw	(0x01, sp), x
      00826E FE               [ 2]  605 	ldw	x, (x)
      00826F 1F 03            [ 2]  606 	ldw	(0x03, sp), x
      008271 26 F4            [ 1]  607 	jrne	00114$
                                    608 ;	./src/OSAL.c: 495: OSAL_MSG_NEXT( list ) = msg_ptr;
      008273 1E 01            [ 2]  609 	ldw	x, (0x01, sp)
      008275 16 09            [ 2]  610 	ldw	y, (0x09, sp)
      008277 FF               [ 2]  611 	ldw	(x), y
                                    612 ;	./src/OSAL.c: 499: HAL_EXIT_CRITICAL_SECTION(intState);
      008278                        613 00116$:
                                    614 ;	./src/OSAL.c: 500: }
      008278 5B 04            [ 2]  615 	addw	sp, #4
      00827A 81               [ 4]  616 	ret
                                    617 ;	./src/OSAL.c: 513: void *osal_msg_dequeue( osal_msg_q_t *q_ptr )
                                    618 ;	-----------------------------------------
                                    619 ;	 function osal_msg_dequeue
                                    620 ;	-----------------------------------------
      00827B                        621 _osal_msg_dequeue:
      00827B 52 06            [ 2]  622 	sub	sp, #6
                                    623 ;	./src/OSAL.c: 515: void *msg_ptr = NULL;
      00827D 5F               [ 1]  624 	clrw	x
      00827E 1F 01            [ 2]  625 	ldw	(0x01, sp), x
                                    626 ;	./src/OSAL.c: 519: HAL_ENTER_CRITICAL_SECTION(intState);
      008280 9B               [ 1]  627 	sim
      008281 9D               [ 1]  628 	nop
      008282 9D               [ 1]  629 	nop
                                    630 ;	./src/OSAL.c: 521: if ( *q_ptr != NULL )
      008283 16 09            [ 2]  631 	ldw	y, (0x09, sp)
      008285 93               [ 1]  632 	ldw	x, y
      008286 FE               [ 2]  633 	ldw	x, (x)
      008287 27 17            [ 1]  634 	jreq	00109$
                                    635 ;	./src/OSAL.c: 524: msg_ptr = *q_ptr;
                                    636 ;	./src/OSAL.c: 525: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
      008289 1F 01            [ 2]  637 	ldw	(0x01, sp), x
      00828B 1F 03            [ 2]  638 	ldw	(0x03, sp), x
      00828D 1D 00 05         [ 2]  639 	subw	x, #0x0005
      008290 1F 05            [ 2]  640 	ldw	(0x05, sp), x
      008292 FE               [ 2]  641 	ldw	x, (x)
      008293 90 FF            [ 2]  642 	ldw	(y), x
                                    643 ;	./src/OSAL.c: 526: OSAL_MSG_NEXT( msg_ptr ) = NULL;
      008295 1E 05            [ 2]  644 	ldw	x, (0x05, sp)
      008297 6F 01            [ 1]  645 	clr	(0x1, x)
      008299 7F               [ 1]  646 	clr	(x)
                                    647 ;	./src/OSAL.c: 527: OSAL_MSG_ID( msg_ptr ) = TASK_NO_TASK;
      00829A 1E 03            [ 2]  648 	ldw	x, (0x03, sp)
      00829C 5A               [ 2]  649 	decw	x
      00829D A6 FF            [ 1]  650 	ld	a, #0xff
      00829F F7               [ 1]  651 	ld	(x), a
                                    652 ;	./src/OSAL.c: 531: HAL_EXIT_CRITICAL_SECTION(intState);
      0082A0                        653 00109$:
                                    654 ;	./src/OSAL.c: 533: return msg_ptr;
      0082A0 1E 01            [ 2]  655 	ldw	x, (0x01, sp)
                                    656 ;	./src/OSAL.c: 534: }
      0082A2 5B 06            [ 2]  657 	addw	sp, #6
      0082A4 81               [ 4]  658 	ret
                                    659 ;	./src/OSAL.c: 549: void osal_msg_push( osal_msg_q_t *q_ptr, void *msg_ptr )
                                    660 ;	-----------------------------------------
                                    661 ;	 function osal_msg_push
                                    662 ;	-----------------------------------------
      0082A5                        663 _osal_msg_push:
      0082A5 89               [ 2]  664 	pushw	x
                                    665 ;	./src/OSAL.c: 554: HAL_ENTER_CRITICAL_SECTION(intState);
      0082A6 9B               [ 1]  666 	sim
      0082A7 9D               [ 1]  667 	nop
      0082A8 9D               [ 1]  668 	nop
                                    669 ;	./src/OSAL.c: 557: OSAL_MSG_NEXT( msg_ptr ) = *q_ptr;
      0082A9 1E 07            [ 2]  670 	ldw	x, (0x07, sp)
      0082AB 1D 00 05         [ 2]  671 	subw	x, #0x0005
      0082AE 16 05            [ 2]  672 	ldw	y, (0x05, sp)
      0082B0 17 01            [ 2]  673 	ldw	(0x01, sp), y
      0082B2 90 FE            [ 2]  674 	ldw	y, (y)
      0082B4 FF               [ 2]  675 	ldw	(x), y
                                    676 ;	./src/OSAL.c: 558: *q_ptr = msg_ptr;
      0082B5 1E 01            [ 2]  677 	ldw	x, (0x01, sp)
      0082B7 16 07            [ 2]  678 	ldw	y, (0x07, sp)
      0082B9 FF               [ 2]  679 	ldw	(x), y
                                    680 ;	./src/OSAL.c: 561: HAL_EXIT_CRITICAL_SECTION(intState);
                                    681 ;	./src/OSAL.c: 562: }
      0082BA 85               [ 2]  682 	popw	x
      0082BB 81               [ 4]  683 	ret
                                    684 ;	./src/OSAL.c: 578: void osal_msg_extract( osal_msg_q_t *q_ptr, void *msg_ptr, void *prev_ptr )
                                    685 ;	-----------------------------------------
                                    686 ;	 function osal_msg_extract
                                    687 ;	-----------------------------------------
      0082BC                        688 _osal_msg_extract:
      0082BC 52 06            [ 2]  689 	sub	sp, #6
                                    690 ;	./src/OSAL.c: 583: HAL_ENTER_CRITICAL_SECTION(intState);
      0082BE 9B               [ 1]  691 	sim
      0082BF 9D               [ 1]  692 	nop
      0082C0 9D               [ 1]  693 	nop
                                    694 ;	./src/OSAL.c: 585: if ( msg_ptr == *q_ptr )
      0082C1 16 09            [ 2]  695 	ldw	y, (0x09, sp)
      0082C3 17 05            [ 2]  696 	ldw	(0x05, sp), y
      0082C5 93               [ 1]  697 	ldw	x, y
      0082C6 FE               [ 2]  698 	ldw	x, (x)
                                    699 ;	./src/OSAL.c: 588: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
      0082C7 16 0B            [ 2]  700 	ldw	y, (0x0b, sp)
      0082C9 17 01            [ 2]  701 	ldw	(0x01, sp), y
      0082CB 72 A2 00 05      [ 2]  702 	subw	y, #0x0005
      0082CF 17 03            [ 2]  703 	ldw	(0x03, sp), y
      0082D1 90 FE            [ 2]  704 	ldw	y, (y)
                                    705 ;	./src/OSAL.c: 585: if ( msg_ptr == *q_ptr )
      0082D3 13 0B            [ 2]  706 	cpw	x, (0x0b, sp)
      0082D5 26 05            [ 1]  707 	jrne	00108$
                                    708 ;	./src/OSAL.c: 588: *q_ptr = OSAL_MSG_NEXT( msg_ptr );
      0082D7 1E 05            [ 2]  709 	ldw	x, (0x05, sp)
      0082D9 FF               [ 2]  710 	ldw	(x), y
      0082DA 20 08            [ 2]  711 	jra	00109$
      0082DC                        712 00108$:
                                    713 ;	./src/OSAL.c: 593: OSAL_MSG_NEXT( prev_ptr ) = OSAL_MSG_NEXT( msg_ptr );
      0082DC 1E 0D            [ 2]  714 	ldw	x, (0x0d, sp)
      0082DE 1D 00 05         [ 2]  715 	subw	x, #0x0005
      0082E1 1F 05            [ 2]  716 	ldw	(0x05, sp), x
      0082E3 FF               [ 2]  717 	ldw	(x), y
      0082E4                        718 00109$:
                                    719 ;	./src/OSAL.c: 595: OSAL_MSG_NEXT( msg_ptr ) = NULL;
      0082E4 1E 03            [ 2]  720 	ldw	x, (0x03, sp)
      0082E6 6F 01            [ 1]  721 	clr	(0x1, x)
      0082E8 7F               [ 1]  722 	clr	(x)
                                    723 ;	./src/OSAL.c: 596: OSAL_MSG_ID( msg_ptr ) = TASK_NO_TASK;
      0082E9 1E 01            [ 2]  724 	ldw	x, (0x01, sp)
      0082EB 5A               [ 2]  725 	decw	x
      0082EC A6 FF            [ 1]  726 	ld	a, #0xff
      0082EE F7               [ 1]  727 	ld	(x), a
                                    728 ;	./src/OSAL.c: 599: HAL_EXIT_CRITICAL_SECTION(intState);
                                    729 ;	./src/OSAL.c: 600: }
      0082EF 5B 06            [ 2]  730 	addw	sp, #6
      0082F1 81               [ 4]  731 	ret
                                    732 ;	./src/OSAL.c: 616: uint8 osal_msg_enqueue_max( osal_msg_q_t *q_ptr, void *msg_ptr, uint8 max )
                                    733 ;	-----------------------------------------
                                    734 ;	 function osal_msg_enqueue_max
                                    735 ;	-----------------------------------------
      0082F2                        736 _osal_msg_enqueue_max:
      0082F2 52 04            [ 2]  737 	sub	sp, #4
                                    738 ;	./src/OSAL.c: 619: uint8 ret = FALSE;
      0082F4 0F 01            [ 1]  739 	clr	(0x01, sp)
                                    740 ;	./src/OSAL.c: 623: HAL_ENTER_CRITICAL_SECTION(intState);
      0082F6 9B               [ 1]  741 	sim
      0082F7 9D               [ 1]  742 	nop
      0082F8 9D               [ 1]  743 	nop
                                    744 ;	./src/OSAL.c: 626: if ( *q_ptr == NULL )
      0082F9 16 07            [ 2]  745 	ldw	y, (0x07, sp)
      0082FB 17 03            [ 2]  746 	ldw	(0x03, sp), y
      0082FD 93               [ 1]  747 	ldw	x, y
      0082FE FE               [ 2]  748 	ldw	x, (x)
      0082FF 26 0B            [ 1]  749 	jrne	00114$
                                    750 ;	./src/OSAL.c: 628: *q_ptr = msg_ptr;
      008301 1E 03            [ 2]  751 	ldw	x, (0x03, sp)
      008303 16 09            [ 2]  752 	ldw	y, (0x09, sp)
      008305 FF               [ 2]  753 	ldw	(x), y
                                    754 ;	./src/OSAL.c: 629: ret = TRUE;
      008306 A6 01            [ 1]  755 	ld	a, #0x01
      008308 6B 01            [ 1]  756 	ld	(0x01, sp), a
      00830A 20 29            [ 2]  757 	jra	00116$
      00830C                        758 00114$:
                                    759 ;	./src/OSAL.c: 634: list = *q_ptr;
      00830C 1F 02            [ 2]  760 	ldw	(0x02, sp), x
                                    761 ;	./src/OSAL.c: 635: max--;
      00830E 0A 0B            [ 1]  762 	dec	(0x0b, sp)
                                    763 ;	./src/OSAL.c: 636: while ( (OSAL_MSG_NEXT( list ) != NULL) && (max > 0) )
      008310 7B 0B            [ 1]  764 	ld	a, (0x0b, sp)
      008312 6B 04            [ 1]  765 	ld	(0x04, sp), a
      008314                        766 00108$:
      008314 1E 02            [ 2]  767 	ldw	x, (0x02, sp)
      008316 1D 00 05         [ 2]  768 	subw	x, #0x0005
      008319 1F 02            [ 2]  769 	ldw	(0x02, sp), x
      00831B FE               [ 2]  770 	ldw	x, (x)
      00831C 27 0A            [ 1]  771 	jreq	00110$
      00831E 0D 04            [ 1]  772 	tnz	(0x04, sp)
      008320 27 06            [ 1]  773 	jreq	00110$
                                    774 ;	./src/OSAL.c: 638: list = OSAL_MSG_NEXT( list );
      008322 1F 02            [ 2]  775 	ldw	(0x02, sp), x
                                    776 ;	./src/OSAL.c: 639: max--;
      008324 0A 04            [ 1]  777 	dec	(0x04, sp)
      008326 20 EC            [ 2]  778 	jra	00108$
      008328                        779 00110$:
                                    780 ;	./src/OSAL.c: 643: if ( max != 0 )
      008328 0D 04            [ 1]  781 	tnz	(0x04, sp)
      00832A 27 09            [ 1]  782 	jreq	00116$
                                    783 ;	./src/OSAL.c: 645: OSAL_MSG_NEXT( list ) = msg_ptr;
      00832C 1E 02            [ 2]  784 	ldw	x, (0x02, sp)
      00832E 16 09            [ 2]  785 	ldw	y, (0x09, sp)
      008330 FF               [ 2]  786 	ldw	(x), y
                                    787 ;	./src/OSAL.c: 646: ret = TRUE;
      008331 A6 01            [ 1]  788 	ld	a, #0x01
      008333 6B 01            [ 1]  789 	ld	(0x01, sp), a
                                    790 ;	./src/OSAL.c: 651: HAL_EXIT_CRITICAL_SECTION(intState);
      008335                        791 00116$:
                                    792 ;	./src/OSAL.c: 653: return ret;
      008335 7B 01            [ 1]  793 	ld	a, (0x01, sp)
                                    794 ;	./src/OSAL.c: 654: }
      008337 5B 04            [ 2]  795 	addw	sp, #4
      008339 81               [ 4]  796 	ret
                                    797 ;	./src/OSAL.c: 669: uint8 osal_set_event( uint8 task_id, uint16 event_flag )
                                    798 ;	-----------------------------------------
                                    799 ;	 function osal_set_event
                                    800 ;	-----------------------------------------
      00833A                        801 _osal_set_event:
                                    802 ;	./src/OSAL.c: 671: if ( task_id < tasksCnt )
      00833A C6 80 26         [ 1]  803 	ld	a, _tasksCnt+0
      00833D 11 03            [ 1]  804 	cp	a, (0x03, sp)
      00833F 23 1A            [ 2]  805 	jrule	00110$
                                    806 ;	./src/OSAL.c: 674: HAL_ENTER_CRITICAL_SECTION(intState);    // Hold off interrupts
      008341 9B               [ 1]  807 	sim
      008342 9D               [ 1]  808 	nop
      008343 9D               [ 1]  809 	nop
                                    810 ;	./src/OSAL.c: 675: tasksEvents[task_id] |= event_flag;  // Stuff the event bit(s)
      008344 7B 03            [ 1]  811 	ld	a, (0x03, sp)
      008346 5F               [ 1]  812 	clrw	x
      008347 97               [ 1]  813 	ld	xl, a
      008348 58               [ 2]  814 	sllw	x
      008349 72 BB 00 03      [ 2]  815 	addw	x, _tasksEvents+0
      00834D 90 93            [ 1]  816 	ldw	y, x
      00834F FE               [ 2]  817 	ldw	x, (x)
      008350 9F               [ 1]  818 	ld	a, xl
      008351 1A 05            [ 1]  819 	or	a, (0x05, sp)
      008353 02               [ 1]  820 	rlwa	x
      008354 1A 04            [ 1]  821 	or	a, (0x04, sp)
      008356 95               [ 1]  822 	ld	xh, a
      008357 90 FF            [ 2]  823 	ldw	(y), x
                                    824 ;	./src/OSAL.c: 677: return ( SUCCESS );
      008359 4F               [ 1]  825 	clr	a
      00835A 81               [ 4]  826 	ret
      00835B                        827 00110$:
                                    828 ;	./src/OSAL.c: 681: return ( INVALID_TASK );
      00835B A6 03            [ 1]  829 	ld	a, #0x03
                                    830 ;	./src/OSAL.c: 683: }
      00835D 81               [ 4]  831 	ret
                                    832 ;	./src/OSAL.c: 698: uint8 osal_clear_event( uint8 task_id, uint16 event_flag )
                                    833 ;	-----------------------------------------
                                    834 ;	 function osal_clear_event
                                    835 ;	-----------------------------------------
      00835E                        836 _osal_clear_event:
      00835E 89               [ 2]  837 	pushw	x
                                    838 ;	./src/OSAL.c: 700: if ( task_id < tasksCnt )
      00835F C6 80 26         [ 1]  839 	ld	a, _tasksCnt+0
      008362 11 05            [ 1]  840 	cp	a, (0x05, sp)
      008364 23 1F            [ 2]  841 	jrule	00110$
                                    842 ;	./src/OSAL.c: 703: HAL_ENTER_CRITICAL_SECTION(intState);    // Hold off interrupts
      008366 9B               [ 1]  843 	sim
      008367 9D               [ 1]  844 	nop
      008368 9D               [ 1]  845 	nop
                                    846 ;	./src/OSAL.c: 704: tasksEvents[task_id] &= ~(event_flag);   // Clear the event bit(s)
      008369 7B 05            [ 1]  847 	ld	a, (0x05, sp)
      00836B 5F               [ 1]  848 	clrw	x
      00836C 97               [ 1]  849 	ld	xl, a
      00836D 58               [ 2]  850 	sllw	x
      00836E 72 BB 00 03      [ 2]  851 	addw	x, _tasksEvents+0
      008372 90 93            [ 1]  852 	ldw	y, x
      008374 FE               [ 2]  853 	ldw	x, (x)
      008375 1F 01            [ 2]  854 	ldw	(0x01, sp), x
      008377 1E 06            [ 2]  855 	ldw	x, (0x06, sp)
      008379 53               [ 2]  856 	cplw	x
      00837A 9F               [ 1]  857 	ld	a, xl
      00837B 14 02            [ 1]  858 	and	a, (0x02, sp)
      00837D 02               [ 1]  859 	rlwa	x
      00837E 14 01            [ 1]  860 	and	a, (0x01, sp)
      008380 95               [ 1]  861 	ld	xh, a
      008381 90 FF            [ 2]  862 	ldw	(y), x
                                    863 ;	./src/OSAL.c: 706: return ( SUCCESS );
      008383 4F               [ 1]  864 	clr	a
                                    865 ;	./src/OSAL.c: 710: return ( INVALID_TASK );
      008384 C5                     866 	.byte 0xc5
      008385                        867 00110$:
      008385 A6 03            [ 1]  868 	ld	a, #0x03
      008387                        869 00112$:
                                    870 ;	./src/OSAL.c: 712: }
      008387 85               [ 2]  871 	popw	x
      008388 81               [ 4]  872 	ret
                                    873 ;	./src/OSAL.c: 727: uint8 osal_isr_register( uint8 interrupt_id, void (*isr_ptr)( uint8* ) )
                                    874 ;	-----------------------------------------
                                    875 ;	 function osal_isr_register
                                    876 ;	-----------------------------------------
      008389                        877 _osal_isr_register:
                                    878 ;	./src/OSAL.c: 732: return ( SUCCESS );
      008389 4F               [ 1]  879 	clr	a
                                    880 ;	./src/OSAL.c: 733: }
      00838A 81               [ 4]  881 	ret
                                    882 ;	./src/OSAL.c: 752: uint8 osal_int_enable( uint8 interrupt_id )
                                    883 ;	-----------------------------------------
                                    884 ;	 function osal_int_enable
                                    885 ;	-----------------------------------------
      00838B                        886 _osal_int_enable:
                                    887 ;	./src/OSAL.c: 755: if ( interrupt_id == INTS_ALL )
      00838B 7B 03            [ 1]  888 	ld	a, (0x03, sp)
      00838D 4C               [ 1]  889 	inc	a
      00838E 26 05            [ 1]  890 	jrne	00105$
                                    891 ;	./src/OSAL.c: 757: HAL_ENABLE_INTERRUPTS();
      008390 9A               [ 1]  892 	rim
      008391 9D               [ 1]  893 	nop
      008392 9D               [ 1]  894 	nop
                                    895 ;	./src/OSAL.c: 758: return ( SUCCESS );
      008393 4F               [ 1]  896 	clr	a
      008394 81               [ 4]  897 	ret
      008395                        898 00105$:
                                    899 ;	./src/OSAL.c: 762: return ( INVALID_INTERRUPT_ID );
      008395 A6 07            [ 1]  900 	ld	a, #0x07
                                    901 ;	./src/OSAL.c: 764: }
      008397 81               [ 4]  902 	ret
                                    903 ;	./src/OSAL.c: 782: uint8 osal_int_disable( uint8 interrupt_id )
                                    904 ;	-----------------------------------------
                                    905 ;	 function osal_int_disable
                                    906 ;	-----------------------------------------
      008398                        907 _osal_int_disable:
                                    908 ;	./src/OSAL.c: 785: if ( interrupt_id == INTS_ALL )
      008398 7B 03            [ 1]  909 	ld	a, (0x03, sp)
      00839A 4C               [ 1]  910 	inc	a
      00839B 26 05            [ 1]  911 	jrne	00105$
                                    912 ;	./src/OSAL.c: 787: HAL_DISABLE_INTERRUPTS();
      00839D 9B               [ 1]  913 	sim
      00839E 9D               [ 1]  914 	nop
      00839F 9D               [ 1]  915 	nop
                                    916 ;	./src/OSAL.c: 788: return ( SUCCESS );
      0083A0 4F               [ 1]  917 	clr	a
      0083A1 81               [ 4]  918 	ret
      0083A2                        919 00105$:
                                    920 ;	./src/OSAL.c: 792: return ( INVALID_INTERRUPT_ID );
      0083A2 A6 07            [ 1]  921 	ld	a, #0x07
                                    922 ;	./src/OSAL.c: 794: }
      0083A4 81               [ 4]  923 	ret
                                    924 ;	./src/OSAL.c: 808: uint8 osal_init_system( void )
                                    925 ;	-----------------------------------------
                                    926 ;	 function osal_init_system
                                    927 ;	-----------------------------------------
      0083A5                        928 _osal_init_system:
                                    929 ;	./src/OSAL.c: 811: osal_mem_init();
      0083A5 CD 84 2A         [ 4]  930 	call	_osal_mem_init
                                    931 ;	./src/OSAL.c: 814: osal_qHead = NULL;
      0083A8 5F               [ 1]  932 	clrw	x
      0083A9 CF 00 01         [ 2]  933 	ldw	_osal_qHead+0, x
                                    934 ;	./src/OSAL.c: 817: osalTimerInit();
      0083AC CD 86 00         [ 4]  935 	call	_osalTimerInit
                                    936 ;	./src/OSAL.c: 820: osalInitTasks();
      0083AF CD 84 29         [ 4]  937 	call	_osalInitTasks
                                    938 ;	./src/OSAL.c: 823: osal_mem_kick();
      0083B2 CD 84 4C         [ 4]  939 	call	_osal_mem_kick
                                    940 ;	./src/OSAL.c: 825: return ( SUCCESS );
      0083B5 4F               [ 1]  941 	clr	a
                                    942 ;	./src/OSAL.c: 826: }
      0083B6 81               [ 4]  943 	ret
                                    944 ;	./src/OSAL.c: 840: void osal_start_system( void )
                                    945 ;	-----------------------------------------
                                    946 ;	 function osal_start_system
                                    947 ;	-----------------------------------------
      0083B7                        948 _osal_start_system:
      0083B7                        949 00102$:
                                    950 ;	./src/OSAL.c: 844: osal_run_system();
      0083B7 CD 83 BD         [ 4]  951 	call	_osal_run_system
      0083BA 20 FB            [ 2]  952 	jra	00102$
                                    953 ;	./src/OSAL.c: 846: }
      0083BC 81               [ 4]  954 	ret
                                    955 ;	./src/OSAL.c: 862: void osal_run_system( void )
                                    956 ;	-----------------------------------------
                                    957 ;	 function osal_run_system
                                    958 ;	-----------------------------------------
      0083BD                        959 _osal_run_system:
      0083BD 52 05            [ 2]  960 	sub	sp, #5
                                    961 ;	./src/OSAL.c: 866: do {
      0083BF 0F 05            [ 1]  962 	clr	(0x05, sp)
      0083C1                        963 00103$:
                                    964 ;	./src/OSAL.c: 867: if (tasksEvents[idx])  // Task is highest priority that is ready.
      0083C1 7B 05            [ 1]  965 	ld	a, (0x05, sp)
      0083C3 5F               [ 1]  966 	clrw	x
      0083C4 97               [ 1]  967 	ld	xl, a
      0083C5 58               [ 2]  968 	sllw	x
      0083C6 72 BB 00 03      [ 2]  969 	addw	x, _tasksEvents+0
      0083CA FE               [ 2]  970 	ldw	x, (x)
                                    971 ;	./src/OSAL.c: 871: } while (++idx < tasksCnt);
      0083CB C6 80 26         [ 1]  972 	ld	a, _tasksCnt+0
                                    973 ;	./src/OSAL.c: 867: if (tasksEvents[idx])  // Task is highest priority that is ready.
      0083CE 5D               [ 2]  974 	tnzw	x
      0083CF 26 06            [ 1]  975 	jrne	00105$
                                    976 ;	./src/OSAL.c: 871: } while (++idx < tasksCnt);
      0083D1 0C 05            [ 1]  977 	inc	(0x05, sp)
      0083D3 11 05            [ 1]  978 	cp	a, (0x05, sp)
      0083D5 22 EA            [ 1]  979 	jrugt	00103$
      0083D7                        980 00105$:
                                    981 ;	./src/OSAL.c: 873: if (idx < tasksCnt)
      0083D7 11 05            [ 1]  982 	cp	a, (0x05, sp)
      0083D9 23 45            [ 2]  983 	jrule	00124$
                                    984 ;	./src/OSAL.c: 878: HAL_ENTER_CRITICAL_SECTION(intState);
      0083DB 9B               [ 1]  985 	sim
      0083DC 9D               [ 1]  986 	nop
      0083DD 9D               [ 1]  987 	nop
                                    988 ;	./src/OSAL.c: 879: events = tasksEvents[idx];
      0083DE 5F               [ 1]  989 	clrw	x
      0083DF 7B 05            [ 1]  990 	ld	a, (0x05, sp)
      0083E1 97               [ 1]  991 	ld	xl, a
      0083E2 58               [ 2]  992 	sllw	x
      0083E3 1F 03            [ 2]  993 	ldw	(0x03, sp), x
      0083E5 CE 00 03         [ 2]  994 	ldw	x, _tasksEvents+0
      0083E8 72 FB 03         [ 2]  995 	addw	x, (0x03, sp)
      0083EB 90 93            [ 1]  996 	ldw	y, x
      0083ED 90 FE            [ 2]  997 	ldw	y, (y)
                                    998 ;	./src/OSAL.c: 880: tasksEvents[idx] = 0;  // Clear the Events for this task.
      0083EF 6F 01            [ 1]  999 	clr	(0x1, x)
      0083F1 7F               [ 1] 1000 	clr	(x)
                                   1001 ;	./src/OSAL.c: 883: activeTaskID = idx;
      0083F2 7B 05            [ 1] 1002 	ld	a, (0x05, sp)
      0083F4 C7 04 0E         [ 1] 1003 	ld	_activeTaskID+0, a
                                   1004 ;	./src/OSAL.c: 884: events = (tasksArr[idx])( idx, events );
      0083F7 1E 03            [ 2] 1005 	ldw	x, (0x03, sp)
      0083F9 1C 80 24         [ 2] 1006 	addw	x, #(_tasksArr + 0)
      0083FC FE               [ 2] 1007 	ldw	x, (x)
      0083FD 90 89            [ 2] 1008 	pushw	y
      0083FF 7B 07            [ 1] 1009 	ld	a, (0x07, sp)
      008401 88               [ 1] 1010 	push	a
      008402 FD               [ 4] 1011 	call	(x)
      008403 5B 03            [ 2] 1012 	addw	sp, #3
      008405 1F 01            [ 2] 1013 	ldw	(0x01, sp), x
                                   1014 ;	./src/OSAL.c: 885: activeTaskID = TASK_NO_TASK;
      008407 35 FF 04 0E      [ 1] 1015 	mov	_activeTaskID+0, #0xff
                                   1016 ;	./src/OSAL.c: 887: HAL_ENTER_CRITICAL_SECTION(intState);
      00840B 9B               [ 1] 1017 	sim
      00840C 9D               [ 1] 1018 	nop
      00840D 9D               [ 1] 1019 	nop
                                   1020 ;	./src/OSAL.c: 888: tasksEvents[idx] |= events;  // Add back unprocessed events to the current task.
      00840E 90 CE 00 03      [ 2] 1021 	ldw	y, _tasksEvents+0
      008412 72 F9 03         [ 2] 1022 	addw	y, (0x03, sp)
      008415 93               [ 1] 1023 	ldw	x, y
      008416 FE               [ 2] 1024 	ldw	x, (x)
      008417 9F               [ 1] 1025 	ld	a, xl
      008418 1A 02            [ 1] 1026 	or	a, (0x02, sp)
      00841A 02               [ 1] 1027 	rlwa	x
      00841B 1A 01            [ 1] 1028 	or	a, (0x01, sp)
      00841D 95               [ 1] 1029 	ld	xh, a
      00841E 90 FF            [ 2] 1030 	ldw	(y), x
                                   1031 ;	./src/OSAL.c: 889: HAL_EXIT_CRITICAL_SECTION(intState);
      008420                       1032 00124$:
                                   1033 ;	./src/OSAL.c: 892: }
      008420 5B 05            [ 2] 1034 	addw	sp, #5
      008422 81               [ 4] 1035 	ret
                                   1036 ;	./src/OSAL.c: 908: uint8 osal_self( void )
                                   1037 ;	-----------------------------------------
                                   1038 ;	 function osal_self
                                   1039 ;	-----------------------------------------
      008423                       1040 _osal_self:
                                   1041 ;	./src/OSAL.c: 910: return ( activeTaskID );
      008423 C6 04 0E         [ 1] 1042 	ld	a, _activeTaskID+0
                                   1043 ;	./src/OSAL.c: 911: }
      008426 81               [ 4] 1044 	ret
                                   1045 	.area CODE
                                   1046 	.area CONST
                                   1047 	.area INITIALIZER
      008027                       1048 __xinit__activeTaskID:
      008027 FF                    1049 	.db #0xff	; 255
                                   1050 	.area CABS (ABS)
