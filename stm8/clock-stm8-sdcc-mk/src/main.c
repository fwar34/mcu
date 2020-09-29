/**
******************************************************************************
* @file    GPIO_Toggle\main.c
* @author  MCD Application Team
* @version V2.0.4
* @date    26-April-2018
* @brief   This file contains the main function for GPIO Toggle example.
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
#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */

#include "ds1302.sdcc.h"
#include "lcd1602.sdcc.h"
#include "dht11.sdcc.h"
#include "delay.sdcc.h"
#include "infrared.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"

extern void Timer0Init(void);//50毫秒@11.0592MHz
extern void Timer1Init(void); //dht11和ir在使用
extern void Timer3Init(void);

extern unsigned int new_value;

/**
 * @addtogroup GPIO_Toggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

#define LED_GPIO_PORT  (GPIOA)
#define LED_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

void display_idle_count()
{
    /* unsigned char i = idle_count / 10; */
    /* unsigned char j = idle_count % 10; */
    unsigned char i = new_value / 10;
    unsigned char j = new_value % 10;
    write_char(0, 14, i + '0');
    write_char(0, 15, j + '0');
}


/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main(void)
{
    /* Initialize I/Os in Output Mode */
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    /* unsigned char msg[] = "hello"; */
    //初始时间20年8月16号14点16分55秒星期天
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    /* DS1302_TIME current_time; */

    initLcd1602();
    ds1302_init();
    UartInit();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init(); //
    Timer1Init(); //dht11 use
    Timer3Init();
    beep_mute();
    IrInit();
    lcd_light_back = 1;

    wait_for_dht11();
    lcdWriteCmd(0x01); //1602清屏
    TR0 = 1;

    while (1)
    {
        /* ds1302_read_time(&current_time); */
        /* display(&current_time); */
        display_idle_count();

        /* ds1302_read_time(&current_time); */
        /* display(&current_time); */
    }
}

/**
 * @brief Delay
 * @param nCount
 * @retval None
 */
void Delay(uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    //remove unuse warning
    (void)file; 
    (void)line;

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/