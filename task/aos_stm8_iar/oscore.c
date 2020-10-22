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

//void *_get_SP( void )
//{
//	asm("popw   y");
//	asm("ldw    x, sp");
//	asm("pushw  y");
//	asm("ret");
  //asm("ldw x, sp");
  //asm("ret");
//}

/* -------------------------------------------------------------------------- */

//void _set_SP( void *sp )
//{
//	asm("popw   y");
//	asm("popw   x");
//	asm("ldw    sp, x");
//	asm("pushw  x");
//	asm("pushw  y");
//
//	asm("ret");
  //asm("ldw sp, x");
  //asm("ret");
//}

/* -------------------------------------------------------------------------- */

//unsigned char _get_CC( void )
//{
//	asm("push   cc");
//	asm("pop    a");
//
//	asm("ret");
//}
//
/* -------------------------------------------------------------------------- */
//
//void _set_CC( unsigned char cc )
//{
//	(void) cc;
//
//	asm("ld     a, (3, sp)");
//
//	asm("push   a");
//	asm("pop    cc");
//
//	asm("ret");
//}
