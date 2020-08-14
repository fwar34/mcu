#include "stm8s.h"
#include "delay.h"
  
#define RS_PORT GPIOB
#define E_PORT GPIOB
#define DB_PORT GPIOB

#define DB7_PORT GPIOB
#define DB6_PORT GPIOB
#define DB5_PORT GPIOB
#define DB4_PORT GPIOB

#define RS_PIN GPIO_PIN_0
#define E_PIN GPIO_PIN_1
#define DB7_PIN GPIO_PIN_7
#define DB6_PIN GPIO_PIN_6
#define DB5_PIN GPIO_PIN_5
#define DB4_PIN GPIO_PIN_4

void LCD_Write(unsigned char isData,unsigned char cmd)
{
    delay_us(600); //Hardcoding delay, keep waiting while the LCD is busy
  
    if (isData) {
        GPIO_WriteHigh(RS_PORT, RS_PIN);
    } else {
        GPIO_WriteLow(RS_PORT, RS_PIN);
    }
    GPIO_WriteLow(E_PORT, E_PIN);
  
    GPIO_Write(DB_PORT, (GPIO_ReadOutputData(DB_PORT) & 0x0F) | (cmd & 0xF0));
    nop();
    nop();
    GPIO_WriteHigh(E_PORT, E_PIN);     //E = 1
    nop();
    nop();
    GPIO_WriteLow(E_PORT, E_PIN);     //E = 0
  
  
    GPIO_Write(DB_PORT, (GPIO_ReadOutputData(DB_PORT) & 0x0F | (cmd << 4 & 0xF0)));
    nop();
    nop();
    GPIO_WriteHigh(E_PORT, E_PIN);     //E = 1
    nop();
    nop();
    GPIO_WriteLow(E_PORT, E_PIN);     //E = 0
}
  
void LCD_Init(void)
{
    GPIO_Init(RS_PORT,RS_PIN ,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(E_PORT,E_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB7_PORT,DB7_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB6_PORT,DB6_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB5_PORT,DB5_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB4_PORT,DB4_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
      
    //delay_ms(100);
    GPIO_WriteHigh(E_PORT, E_PIN);     //E = 1
    
      
    LCD_Write(0,0x33);
    //delay_ms(4);
    LCD_Write(0,0x32);
    //delay_ms(4);
    LCD_Write(0,0x28);           
    LCD_Write(0,0x0c);
    LCD_Write(0,0x06);
    LCD_Write(0,0x01);  
    //LCD_Write(0,0x80);  
    //delay_ms(200);
}


  
void LCD_Locate(unsigned char x,unsigned char y)
{ 
    LCD_Write(0, x + (y?0xc0:0x80));    
} 
  
void LCD_PrintString(char* c)
{
    while(*c)
    {
        LCD_Write(1,*c);
        c++;
    }
}

void main()
{
    char msg[] = "test";
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//HSI 不分频，主时钟 16M
    delay_init(16);
    LCD_Init();

    LCD_Locate(1, 0);
    LCD_PrintString(msg);

    while (1);
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

    /* Infinite loop */
    while (1)
    {
    }
}
#endif
