/***********************************************************************
ÎÄ¼þÃû³Æ£ºLED.C
¹¦    ÄÜ£ºled  IO³õÊ¼»¯
±àÐ´Ê±¼ä£º2013.4.25
±à Ð´ ÈË£º
×¢    Òâ£º
***********************************************************************/
#include "stm32f10x.h"
#include "stdio.h"
#include "Register_config.h"

#define ROW_PORT GPIOE
#define COL_PORT GPIOE

#define ROW_1 GPIO_Pin_4
#define ROW_2 GPIO_Pin_5
#define ROW_3 GPIO_Pin_6
#define ROW_4 GPIO_Pin_7

#define COL_1 GPIO_Pin_0
#define COL_2 GPIO_Pin_1
#define COL_3 GPIO_Pin_2
#define COL_4 GPIO_Pin_3

void KEY_Configuration(void)
{
    //	GPIO_InitTypeDef GPIO_InitStructure;
    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //ÐÐ
    //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(ROW_PORT,&GPIO_InitStructure);
    //
    //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //ÁÐ
    //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(GPIOE,&GPIO_InitStructure);

    /*****************¼Ä´æÆ÷°æ**********************/
    //	RCC->APB2ENR|=1<<6;    //Ê¹ÄÜPORTEÊ±ÖÓ
    //	GPIOE->CRL=0X33338888;//PE.0 1 2 3  ÉÏÀ­ÊäÈë  4 5 6 7 ÍÆÍìÊä³ö

    RCC_APB2ENR |= 1 << 6;  // Ê¹ÄÜPORTEÊ±ÖÓ
    GPIOE_CRL = 0X33338888; // PE.0 1 2 3  ÉÏÀ­ÊäÈë  4 5 6 7 ÍÆÍìÊä³ö
}
int KEY_read(void)
{
    static int LastCode = -1;     // 上一次键码
    static int key_age = 0;       // 当前键码检测到次数
    int CurrentCode = -1;
    int key_value = -1;
    
    // 扫描第一行 (PE4=0, PE5,6,7=1)
    GPIOE_BRR |= 1 << 4;
    GPIOE_BSRR |= ((1 << 7) | (1 << 6) | (1 << 5));
    
    u8 col_state = GPIOE_IDR & 0xF;
    if (col_state != 0xF) {
        if ((col_state & 0x1) == 0) CurrentCode = 0;
        else if ((col_state & 0x2) == 0) CurrentCode = 1;
        else if ((col_state & 0x4) == 0) CurrentCode = 2;
        else if ((col_state & 0x8) == 0) CurrentCode = 3;
    }
    
    // 扫描第二行 (PE5=0, PE4,6,7=1)
    GPIOE_BRR |= 1 << 5;
    GPIOE_BSRR |= ((1 << 7) | (1 << 6) | (1 << 4));
    
    col_state = GPIOE_IDR & 0xF;
    if (col_state != 0xF) {
        if ((col_state & 0x1) == 0) CurrentCode = 4;
        else if ((col_state & 0x2) == 0) CurrentCode = 5;
        else if ((col_state & 0x4) == 0) CurrentCode = 6;
        else if ((col_state & 0x8) == 0) CurrentCode = 7;
    }
    
    // 扫描第三行 (PE6=0, PE4,5,7=1)
    GPIOE_BRR |= 1 << 6;
    GPIOE_BSRR |= ((1 << 7) | (1 << 5) | (1 << 4));
    
    col_state = GPIOE_IDR & 0xF;
    if (col_state != 0xF) {
        if ((col_state & 0x1) == 0) CurrentCode = 8;
        else if ((col_state & 0x2) == 0) CurrentCode = 9;
        else if ((col_state & 0x4) == 0) CurrentCode = 10;
        else if ((col_state & 0x8) == 0) CurrentCode = 11;
    }
    
    // 扫描第四行 (PE7=0, PE4,5,6=1)
    GPIOE_BRR |= 1 << 7;
    GPIOE_BSRR |= ((1 << 5) | (1 << 6) | (1 << 4));
    
    col_state = GPIOE_IDR & 0xF;
    if (col_state != 0xF) {
        if ((col_state & 0x1) == 0) CurrentCode = 12;
        else if ((col_state & 0x2) == 0) CurrentCode = 13;
        else if ((col_state & 0x4) == 0) CurrentCode = 14;
        else if ((col_state & 0x8) == 0) CurrentCode = 15;
    }
    
    // 按键滤波算法
    if (CurrentCode == LastCode) {
        // 按键持续按下，age++
        key_age++;
        
        // 连续10次(100ms)检测到相同键码，认为按键稳定按下
        if (key_age == 10) {
            key_value = CurrentCode;  // 返回有效的按键值
        }
        else if (key_age > 10) {
            // 按键持续按下，但不重复返回值
            key_value = -1;
        }
    }
    else {
        // 键码变化，重置计数
        key_age = 0;
        LastCode = CurrentCode;
        key_value = -1;
    }
    
    // 特别处理：当按键释放时，也要重置状态
    if (CurrentCode == -1) {
        key_age = 0;
        LastCode = -1;
    }
    
    return key_value;
}
u8 KEY_Scan()//单个按键扫描
{
    u8 key_1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
    if (key_1 == 0)
    {
        delay_ms(100); // È¥¶¶¶¯
        if (key_1 == 0)
            return 1;
    }
    return 0; // ÎÞ°´¼ü°´ÏÂ
}
int KEY_GetOneShot(void)
{
    static int last_key = -1;
    int key_now = KEY_read();

    // 情况 1：没有按键
    if(key_now < 0)
    {
        if(last_key >= 0)
        {
            // 按下 → 松开，触发一次
            int temp = last_key;
            last_key = -1;
            return temp;   // 返回按键值（0~15）
        }
        last_key = -1;
        return -1;
    }

    // 情况 2：正在按着某个键
    if(last_key < 0)
    {
        // 第一次检测到按下
        last_key = key_now;
    }

    return -1;
}

int keydown = 0;
void key_test()
{
    KEY_Configuration();
    while (1)
    {
        keydown = KEY_read();
        if (keydown)
        {
            printf("%d\n", keydown);
            keydown = 0;
            delay_ms(2000);
        }
    }
}