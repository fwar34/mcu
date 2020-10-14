#include "iostm8.h"

void gpio_init()
{
    PA_DDR |= 1 << 2; //输出
    PA_CR1 |= 1 << 2; //推挽输出
    PA_CR2 &= ~(1 << 2); //没有中断
    PA_ODR &= ~(1 << 2); //初始输出低电平

    PD_DDR |= MASK_PD_DDR_DDR4;
    PD_CR1 |= MASK_PD_CR1_C14;
    PD_CR2 &= ~MASK_PD_CR2_C24;
    PD_ODR |= MASK_PD_ODR_ODR4; //输出高电平
}

void delay(unsigned int count)
{
    while (--count);
}

void main()
{
    gpio_init();
    /* PA_ODR_ODR2 = 0; */
    /* PA_ODR &= ~(1 << 2); //初始输出低电平 */
    /* PA_ODR &= ~MASK_PA_ODR_ODR2; */
    while (1) {
        PA_ODR_ODR2 = !PA_ODR_ODR2;
        delay(6000);
    }
}
