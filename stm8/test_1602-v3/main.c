#include "stm8s.h"
#include "delay.h"
  
#define NULL 0
#define Pin(p) (1<<p) 
#define BitGet(bit, i) ((bit>>i)&1)
#define GPIO_PinSet(GPIOx, pin) SetBit(GPIOx->ODR, pin)
#define GPIO_PinClr(GPIOx, pin) ClrBit(GPIOx->ODR, pin)
#define GPIO_PinGet(GPIOx, pin) BitGet(GPIOx->IDR, pin)
#define GPIO_Pin(GPIOx, pin, v) if(v){SetBit(GPIOx->ODR, pin);}else{ClrBit(GPIOx->ODR, pin);}
//#define GPIO_PinInit(GPIOx, pin, mode) GPIO_Init(GPIOx, 1<<pin, mode)    lcd1602 #define lcd_clear() lcd_write(0,0x01) void lcd_init(void); lcd_write(unsigned char isdata,unsigned cmd); lcd_locate(unsigned x,unsigned y); lcd_printstring(char* c); util functions util_delay(unsigned int a); #endif

#define RS_PORT GPIOB
#define E_PORT GPIOB
#define DB_PORT GPIOB

#define DB7_PORT GPIOB
#define DB6_PORT GPIOB
#define DB5_PORT GPIOB
#define DB4_PORT GPIOB

#define RS_PIN GPIO_PIN_0
#define E_PIN GPIO_PIN_2
#define DB7_PIN GPIO_PIN_7
#define DB6_PIN GPIO_PIN_6
#define DB5_PIN GPIO_PIN_5
#define DB4_PIN GPIO_PIN_4

void LCD_Write(unsigned char isData,unsigned char cmd)
{
    delay_us(2000); //Hardcoding delay, keep waiting while the LCD is busy
      
  
    GPIO_Pin(RS_PORT, RS_PIN, isData);
    GPIO_PinClr(E_PORT, E_PIN);
  
  
    GPIO_Pin(DB7_PORT, DB7_PIN, BitGet(cmd, 7));
    GPIO_Pin(DB6_PORT, DB6_PIN, BitGet(cmd, 6));
    GPIO_Pin(DB5_PORT, DB5_PIN, BitGet(cmd, 5));
    GPIO_Pin(DB4_PORT, DB4_PIN, BitGet(cmd, 4));
    nop();
    nop();
    GPIO_PinSet(E_PORT, E_PIN);     //E = 1
    nop();
    nop();
    GPIO_PinClr(E_PORT, E_PIN);     //E = 0
  
  
    GPIO_Pin(DB7_PORT, DB7_PIN, BitGet(cmd, 3));
    GPIO_Pin(DB6_PORT, DB6_PIN, BitGet(cmd, 2));
    GPIO_Pin(DB5_PORT, DB5_PIN, BitGet(cmd, 1));
    GPIO_Pin(DB4_PORT, DB4_PIN, BitGet(cmd, 0)); 
    nop();
    nop();
    GPIO_PinSet(E_PORT, E_PIN);     //E = 1
    nop();
    nop();
    GPIO_PinClr(E_PORT, E_PIN);     //E = 0
}
  
void LCD_Init(void)
{
    GPIO_Init(RS_PORT,RS_PIN ,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(E_PORT,E_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB7_PORT,DB7_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB6_PORT,DB6_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB5_PORT,DB5_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(DB4_PORT,DB4_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
      
    delay_us(1000);
      
    LCD_Write(0,0x33);
    LCD_Write(0,0x32);
    LCD_Write(0,0x28);           
    LCD_Write(0,0x0c);
    LCD_Write(0,0x01);  
    LCD_Write(0,0x80);  
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
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//HSI 不分频，主时钟 16M
    delay_init(16);
    LCD_Init();

    LCD_Write(1,0xC1);
    LCD_Write(1,0xD9); 
    LCD_Write(1,0xC9);

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
