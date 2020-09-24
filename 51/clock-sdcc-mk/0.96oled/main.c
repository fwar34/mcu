//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）
//              RES  接P12
//              DC   接P13
//              CS   接P14               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
//All rights reserved
//******************************************************************************/
#include "REG51.h"
#include "oled.h"
#include "bmp.h"

int main(void)
{	u8 t;
    OLED_Init();			//初始化OLED  
    OLED_Clear()  	; 
        
    t=' ';
    OLED_ShowCHinese(54,0,3);//电
    OLED_ShowCHinese(72,0,4);//子
    OLED_ShowCHinese(90,0,5);//科
    OLED_ShowCHinese(108,0,6);//技
    while(1) 
    {		
        OLED_Clear();
        OLED_ShowCHinese(54,0,3);//电
        OLED_ShowCHinese(72,0,4);//子
        OLED_ShowCHinese(90,0,5);//科
        OLED_ShowCHinese(108,0,6);//技
        OLED_ShowString(6,3,"0.96' OLED TEST",16);
        OLED_ShowString(0,6,"ASCII:",16);  
        OLED_ShowString(63,6,"CODE:",16);  
        OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
        t++;
        if(t>'~')t=' ';
        OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
        delay_ms(8000);
        delay_ms(8000);

        delay_ms(8000);
        delay_ms(8000);
        delay_ms(8000);
        OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
        delay_ms(8000);
        delay_ms(8000);
        delay_ms(8000);
        delay_ms(8000);
        OLED_DrawBMP(0,0,128,8,BMP1);
        delay_ms(8000);
        delay_ms(8000);
        delay_ms(8000);
        delay_ms(8000);
    }	  
	
}
	
