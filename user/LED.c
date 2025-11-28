#include "LED.h"
#include "SysTick.h"
// 共阳极数码管段选编码 (a-g, dp)
// 0=亮, 1=灭（因为共阳极是低电平点亮）
// 编码顺序：dp,g,f,e,d,c,b,a
const uint8_t SEGMENT_CODE[] = {
    0xC0, // 0 - a,b,c,d,e,f,g
    0xF9, // 1 - b,c
    0xA4, // 2 - a,b,d,e,g
    0xB0, // 3 - a,b,c,d,g
    0x99, // 4 - b,c,f,g
    0x92, // 5 - a,c,d,f,g
    0x82, // 6 - a,c,d,e,f,g
    0xF8, // 7 - a,b,c
    0x80, // 8 - a,b,c,d,e,f,g
    0x90, // 9 - a,b,c,d,f,g
    0x88, // A - a,b,c,e,f,g
    0x83, // b - c,d,e,f,g
    0xC6, // C - a,d,e,f
    0xA1, // d - b,c,d,e,g
    0x86, // E - a,d,e,f,g
    0x8E  // F - a,e,f,g
};

void LED_Init(void)
{
    RCC->APB2ENR |= 3 << 4; // 使能 PORTC 和 PORTD 时钟

    // 配置PC10-13为推挽输出（用作数码管位选）
    GPIOC->CRH &= 0xFF0000FF;
    GPIOC->CRH |= 0x00333300; // PC.10 11 12 13 推挽输出

    // 配置PD0-7为推挽输出（用作数码管段选）
    GPIOD->CRL &= 0X00000000;

    GPIOD->CRL |= 0X33333333; // PD.0 1 2 3 4 5 6 7 推挽输出

    // 共阳极初始状态：所有段选置高（熄灭）
    GPIOD->BSRR = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

    // 初始状态：所有位选置高（熄灭所有数码管）
    GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
}

// 显示缓冲区，存储最近按下的4个数字（0-15对应0-F）
uint8_t display_buffer[4] = {16,16,16,16}; // 最右边初始显示0，其余不显示

void Update_Number(uint8_t num)
{    

    // 将新数字添加到缓冲区（自右向左）
    for (int i = 0; i < 3; i++)
    {
        display_buffer[i] = display_buffer[i + 1];
    }
    display_buffer[3] = num;

}

void Refresh_Display(void)
{
    for (int i = 3; i >= 0; i--)
    {
        // 熄灭所有数码管
        GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;

        // 选择对应的数码管
        switch (i)
        {
        case 0:
            GPIOC->BRR = GPIO_Pin_10;
            break; // 最右
        case 1:
            GPIOC->BRR = GPIO_Pin_11;
            break;
        case 2:
            GPIOC->BRR = GPIO_Pin_12;
            break;
        case 3:
            GPIOC->BRR = GPIO_Pin_13;
            break; // 最左
        }

        // 显示数字或熄灭
        if (display_buffer[i] < 16)
            GPIOD->ODR = (GPIOD->ODR & 0xFF00) | SEGMENT_CODE[display_buffer[i]];
        else
            GPIOD->ODR = (GPIOD->ODR & 0xFF00) | 0xFF; // 不显示

        delay_ms(5); // 扫描延时，保持显示稳定
    }
}

void Display_Clear(void)
{
    // 清空显示缓冲区
    for (int i = 0; i < 4; i++)
    {
        display_buffer[i] = 0;
    }

    // 熄灭所有数码管
    GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIOD->ODR = (GPIOD->ODR & 0xFF00) | 0xFF;
}