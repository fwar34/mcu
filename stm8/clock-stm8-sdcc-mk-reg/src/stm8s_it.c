/**
******************************************************************************
* @file     stm8s_it.c
* @author   MCD Application Team
* @version  V2.0.4
* @date     26-April-2018
* @brief    Main Interrupt Service Routines.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"

#include "dht11.sdcc.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"
#include "lcd1602.sdcc.h"
#include "infrared.sdcc.h"

extern unsigned char ch_count;//两次ch键进入设置的时间计数
extern unsigned char first_ch_flag;//表示第一次按ch的标志
extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否显示的标志
extern unsigned short idle_count;//最后一次设置开始空闲计数

static unsigned int count = 40;//dht11更新的计数

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/** @addtogroup GPIO_Toggle
 * @{
 */
#ifdef _COSMIC_
/**
 * @brief  Dummy interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(NonHandledInterrupt, 25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*_COSMIC_*/

/**
 * @brief  TRAP interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
 * @brief  Top Level Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TLI_IRQHandler, 0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Auto Wake Up Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Clock Controller Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  External Interrupt PORTA Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  External Interrupt PORTB Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  External Interrupt PORTC Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  External Interrupt PORTD Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    /* ReadIr(); */
    IrMachine();
    key_scan();
}

/**
 * @brief  External Interrupt PORTE Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#ifdef STM8S903
/**
 * @brief  External Interrupt PORTF Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S903*/

#if defined (STM8S208) || defined (STM8AF52Ax)
/**
 * @brief CAN RX Interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CAN_RX_IRQHandler, 8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  CAN TX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CAN_TX_IRQHandler, 9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S208 || STM8AF52Ax */

/**
 * @brief  SPI Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Timer1 Update/Overflow/Trigger/Break Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Timer1 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

#ifdef STM8S903
/**
 * @brief  Timer5 Update/Overflow/Break/Trigger Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
 * @brief  Timer5 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8S001 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
/**
 * @brief  Timer2 Update/Overflow/Break Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Timer2 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S903*/

#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) || defined(STM8AF62Ax) || defined(STM8AF52Ax) || defined(STM8AF626x)
/**
 * @brief Timer3 Update/Overflow/Break Interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  Timer3 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S208, STM8S207 or STM8S105 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */

#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) || defined(STM8S001) || defined(STM8AF62Ax) || defined(STM8AF52Ax) || defined(STM8S903)
/**
 * @brief  UART1 TX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  UART1 RX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S105 || STM8S001 */

/**
 * @brief  I2C Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x)
/**
 * @brief  UART2 TX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  UART2 RX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    /* UART2_ClearITPendingBit(UART2_IT_RXNE); */
    uart_recv_buf[uart_recv_buf_index++] = uart_recv_byte();
    if (uart_recv_buf_index >= 255)
        uart_recv_buf_index = 0;
}
#endif /* STM8S105*/

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
 * @brief  UART3 TX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART3_TX_IRQHandler, 20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @brief  UART3 RX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART3_RX_IRQHandler, 21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
 * @brief  ADC2 interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(ADC2_IRQHandler, 22)
{

    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    return;

}
#else /*STM8S105, STM8S103 or STM8S903 or STM8AF626x */
/**
 * @brief  ADC1 interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{

    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    return;

}
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#ifdef STM8S903
/**
 * @brief  Timer6 Update/Overflow/Trigger Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8S001 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
/**
 * @brief  Timer4 Update/Overflow Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
        
    if (ch_count > 0) {//第一次点击ch按钮会把ch_count设置成1
        ++ch_count;
        if (ch_count > 20) {//1s过后没有点击第二次ch按钮的话重置字段
            ch_count = 0;
        }
    }

    if (idle_count > 0) {//每一次设置会把idle_count设置成1,所以大于0才判断是否是设置空闲超时
        ++idle_count;
        if (idle_count > 20 * 10) {//设置空闲了10秒之后退出
            idle_count = 0;
            exit_settings();
        }
    }

    if (++count >= 500 * 2) {//1000ms * 2 -> 2s更新一次dht11
        /* lcd_light_back = !lcd_light_back; */
        count = 0;//reset counter
        dht11_read_data();
        display_dht11();
    }

    process_key();//处理物理按键
}
#endif /*STM8S903*/

/**
 * @brief  Eeprom EEC Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
