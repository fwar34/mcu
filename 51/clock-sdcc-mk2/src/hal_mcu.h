
#ifndef _HAL_MCU_H
#define _HAL_MCU_H


/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "hal_types.h"
/* #include "ioSTC8.h" */
#include <mcs51/8051.h>


#define HAL_ASSERT(expr)    st( if (!( expr )) while(1); )
#define st(x)      do { x } while (__LINE__ == -1)
//����STC8�ٷ��ֲḽ¼A2������/�ر��жϴ����ͺ�������Ҫ�ȴ�1-2��ָ������ϵͳ���ܳ��׿���/�ر��ж�
#define HAL_ENABLE_INTERRUPTS()         st(EA = 1;  __asm__("nop"); __asm__("nop"); )
#define HAL_DISABLE_INTERRUPTS()        st(EA = 0;  __asm__("nop"); __asm__("nop"); )
#define HAL_INTERRUPTS_ARE_ENABLED()    (EA)

typedef unsigned char halIntState_t;
#define HAL_ENTER_CRITICAL_SECTION(x)   st( x = EA;  HAL_DISABLE_INTERRUPTS(); )
#define HAL_EXIT_CRITICAL_SECTION(x)    st( EA = x;)
#define HAL_CRITICAL_STATEMENT(x)       st( halIntState_t _s; HAL_ENTER_CRITICAL_SECTION(_s); x; HAL_EXIT_CRITICAL_SECTION(_s); )

/* ------------------------------------------------------------------------------------------------
 *                               Memory Attributes and Compiler Macros
 * ------------------------------------------------------------------------------------------------
 */

/* ----------- IAR Compiler ----------- */
#ifdef __IAR_SYSTEMS_ICC__
#define CODE      __code
#define XDATA     __xdata
#define DATA      __data
#define NEAR_FUNC __near_func
#define ASM_NOP    asm("NOP")

/* ----------- SDCC Compiler ----------- */
#elif defined __SDCC
#define CODE   __code
#define DATA      __data
#define XDATA  __xdata
#define ASM_NOP   __asm__("nop")

/* ----------- KEIL Compiler ----------- */
#elif defined __KEIL__
#define  CODE   code
#define  XDATA  xdata
#define ASM_NOP   __nop()

/* ----------- GNU Compiler ----------- */
#elif defined __GNUC__
#define ASM_NOP __asm__ __volatile__ ("nop")

/* ---------- MSVC compiler ---------- */
#elif _MSC_VER
#define ASM_NOP __asm NOP

/* ----------- CCS Compiler ----------- */
#elif defined __TI_COMPILER_VERSION
#define ASM_NOP    asm(" NOP")

/* ----------- Unrecognized Compiler ----------- */
#else
#error "ERROR: Unknown compiler."
#endif


/* ------------------------------------------------------------------------------------------------
 *                                        Standard Defines
 * ------------------------------------------------------------------------------------------------
 */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif


#endif
