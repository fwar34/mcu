/******************************************************************************

    @file    StateOS: oscore.c
    @author  Rajmund Szymanski
    @date    29.03.2020
    @brief   StateOS port file for STM8 uC.

 ******************************************************************************

   Copyright (c) 2018-2020 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

/* -------------------------------------------------------------------------- */

void *_get_SP( void )
{
	__asm

#ifdef __SDCC_MODEL_LARGE
	pop    a
#endif
	popw   y
	ldw    x, sp
	pushw  y
#ifdef __SDCC_MODEL_LARGE
	push   a
	retf
#else
	ret
#endif

	__endasm;
}

/* -------------------------------------------------------------------------- */

void _set_SP( void *sp )
{
	(void) sp;

	__asm

#ifdef __SDCC_MODEL_LARGE
	pop    a
#endif
	popw   y
	popw   x
	ldw    sp, x
	pushw  x
	pushw  y
#ifdef __SDCC_MODEL_LARGE
	push   a
	retf
#else
	ret
#endif

	__endasm;
}

/* -------------------------------------------------------------------------- */

unsigned char _get_CC( void )
{
	__asm

	push   cc
	pop    a
#ifdef __SDCC_MODEL_LARGE
	retf
#else
	ret
#endif

	__endasm;
}

/* -------------------------------------------------------------------------- */

void _set_CC( unsigned char cc )
{
	(void) cc;

	__asm

#ifdef __SDCC_MODEL_LARGE
	ld     a, (4, sp)
#else
	ld     a, (3, sp)
#endif
	push   a
	pop    cc
#ifdef __SDCC_MODEL_LARGE
	retf
#else
	ret
#endif

	__endasm;
}
