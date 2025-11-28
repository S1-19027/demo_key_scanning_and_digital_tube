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

int KEY_read(void)//当前是否按下
{  
    int key_value = -1;

    u8 key_1 = 1;
    u8 key_2 = 1;
    u8 key_3 = 1;
    u8 key_4 = 1;

    // GPIO_ResetBits(ROW_PORT,ROW_1);
    // GPIO_SetBits(ROW_PORT,ROW_2 |ROW_3|ROW_4);
    // key_1 = GPIO_ReadInputDataBit(COL_PORT,COL_1);
    // key_2 = GPIO_ReadInputDataBit(COL_PORT,COL_2);
    // key_3 = GPIO_ReadInputDataBit(COL_PORT,COL_3);
    // key_4 = GPIO_ReadInputDataBit(COL_PORT,COL_4);

    // GPIOE->BRR = GPIO_Pin_4;
    // GPIOE->BSRR = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIOE_BRR |= 1 << 4;                            // ÉèÖÃPE4Êä³öµÍµçÆ½
    GPIOE_BSRR |= ((1 << 7) | (1 << 6) | (1 << 5)); // ÉèÖÃPE5,6,7Êä³ö¸ßµçÆ½
    if ((GPIOE_IDR & 0x1) != (uint32_t)Bit_RESET)   // ÅÐ¶ÏPE0Òý½ÅµçÆ½£¬°´ÏÂÎªµÍ
    {
        key_1 = (uint8_t)Bit_SET;
    }
    else
    {
        key_1 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x2) != (uint32_t)Bit_RESET) // ÅÐ¶ÏPE1Òý½ÅµçÆ½£¬°´ÏÂÎªµÍ
    {
        key_2 = (uint8_t)Bit_SET;
    }
    else
    {
        key_2 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x4) != (uint32_t)Bit_RESET) // ÅÐ¶ÏPE2Òý½ÅµçÆ½£¬°´ÏÂÎªµÍ
    {
        key_3 = (uint8_t)Bit_SET;
    }
    else
    {
        key_3 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x8) != (uint32_t)Bit_RESET) // ÅÐ¶ÏPE3Òý½ÅµçÆ½£¬°´ÏÂÎªµÍ
    {
        key_4 = (uint8_t)Bit_SET;
    }
    else
    {
        key_4 = (uint8_t)Bit_RESET;
    }

    if (key_1 == 0)
    {
        key_value = 0;
    }
    else
    {
    }
    if (key_2 == 0)
    {
        key_value = 1;
    }
    else
    {
    }
    if (key_3 == 0)
    {
        key_value = 2;
    }
    else
    {
    }
    if (key_4 == 0)
    {
        key_value = 3;
    }
    else
    {
    }

    //	GPIO_ResetBits(ROW_PORT,ROW_2);
    //	GPIO_SetBits(ROW_PORT,ROW_1 |ROW_3|ROW_4);
    //	key_1 = GPIO_ReadInputDataBit(COL_PORT,COL_1);
    //	key_2 = GPIO_ReadInputDataBit(COL_PORT,COL_2);
    //	key_3 = GPIO_ReadInputDataBit(COL_PORT,COL_3);
    //	key_4 = GPIO_ReadInputDataBit(COL_PORT,COL_4);

    // GPIOE->BRR = GPIO_Pin_5;
    // GPIOE->BSRR = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;

    GPIOE_BRR |= 1 << 5;
    GPIOE_BSRR |= ((1 << 7) | (1 << 6) | (1 << 4));
    if ((GPIOE_IDR & 0x1) != (uint32_t)Bit_RESET)
    {
        key_1 = (uint8_t)Bit_SET;
    }
    else
    {
        key_1 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x2) != (uint32_t)Bit_RESET)
    {
        key_2 = (uint8_t)Bit_SET;
    }
    else
    {
        key_2 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x4) != (uint32_t)Bit_RESET)
    {
        key_3 = (uint8_t)Bit_SET;
    }
    else
    {
        key_3 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x8) != (uint32_t)Bit_RESET)
    {
        key_4 = (uint8_t)Bit_SET;
    }
    else
    {
        key_4 = (uint8_t)Bit_RESET;
    }

    if (key_1 == 0)
    {
        key_value = 4;
    }
    else
    {
    }
    if (key_2 == 0)
    {
        key_value = 5;
    }
    else
    {
    }
    if (key_3 == 0)
    {
        key_value = 6;
    }
    else
    {
    }
    if (key_4 == 0)
    {
        key_value = 7;
    }
    else
    {
    }

    //	GPIO_ResetBits(ROW_PORT,ROW_3);
    //	GPIO_SetBits(ROW_PORT,ROW_1 |ROW_2|ROW_4);
    //	key_1 = GPIO_ReadInputDataBit(COL_PORT,COL_1);
    //	key_2 = GPIO_ReadInputDataBit(COL_PORT,COL_2);
    //	key_3 = GPIO_ReadInputDataBit(COL_PORT,COL_3);
    //	key_4 = GPIO_ReadInputDataBit(COL_PORT,COL_4);

    //	GPIOE->BRR = GPIO_Pin_6;
    //	GPIOE->BSRR = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_7;

    GPIOE_BRR |= 1 << 6;
    GPIOE_BSRR |= ((1 << 7) | (1 << 5) | (1 << 4));

    if ((GPIOE_IDR & 0x1) != (uint32_t)Bit_RESET)
    {
        key_1 = (uint8_t)Bit_SET;
    }
    else
    {
        key_1 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x2) != (uint32_t)Bit_RESET)
    {
        key_2 = (uint8_t)Bit_SET;
    }
    else
    {
        key_2 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x4) != (uint32_t)Bit_RESET)
    {
        key_3 = (uint8_t)Bit_SET;
    }
    else
    {
        key_3 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x8) != (uint32_t)Bit_RESET)
    {
        key_4 = (uint8_t)Bit_SET;
    }
    else
    {
        key_4 = (uint8_t)Bit_RESET;
    }

    if (key_1 == 0)
    {
        key_value = 8;
    }
    else
    {
    }
    if (key_2 == 0)
    {
        key_value = 9;
    }
    else
    {
    }
    if (key_3 == 0)
    {
        key_value = 10;
    }
    else
    {
    }
    if (key_4 == 0)
    {
        key_value = 11;
    }
    else
    {
    }

    //	GPIO_ResetBits(ROW_PORT,ROW_4);
    //	GPIO_SetBits(ROW_PORT,ROW_1 |ROW_2|ROW_3);
    //	key_1 = GPIO_ReadInputDataBit(COL_PORT,COL_1);
    //	key_2 = GPIO_ReadInputDataBit(COL_PORT,COL_2);
    //	key_3 = GPIO_ReadInputDataBit(COL_PORT,COL_3);
    //	key_4 = GPIO_ReadInputDataBit(COL_PORT,COL_4);

    //	GPIOE->BRR = GPIO_Pin_7;
    //	GPIOE->BSRR = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_4;

    GPIOE_BRR |= 1 << 7;
    GPIOE_BSRR |= ((1 << 5) | (1 << 6) | (1 << 4));

    if ((GPIOE_IDR & 0x1) != (uint32_t)Bit_RESET)
    {
        key_1 = (uint8_t)Bit_SET;
    }
    else
    {
        key_1 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x2) != (uint32_t)Bit_RESET)
    {
        key_2 = (uint8_t)Bit_SET;
    }
    else
    {
        key_2 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x4) != (uint32_t)Bit_RESET)
    {
        key_3 = (uint8_t)Bit_SET;
    }
    else
    {
        key_3 = (uint8_t)Bit_RESET;
    }
    if ((GPIOE_IDR & 0x8) != (uint32_t)Bit_RESET)
    {
        key_4 = (uint8_t)Bit_SET;
    }
    else
    {
        key_4 = (uint8_t)Bit_RESET;
    }

    if (key_1 == 0)
    {
        key_value = 12;
    }
    else
    {
    }
    if (key_2 == 0)
    {
        key_value = 13;
    }
    else
    {
    }
    if (key_3 == 0)
    {
        key_value = 14;
    }
    else
    {
    }
    if (key_4 == 0)
    {
        key_value = 15;
    }
    else
    {
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