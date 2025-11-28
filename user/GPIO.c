/***********************************************************************
�ļ����ƣ�LED.C
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺���´�������ο�
***********************************************************************/
#include "stm32f10x.h"

#define RCC_APB2ENR (*((volatile unsigned int *)0x40021018)) // APB2 ����ʱ��ʹ�ܼĴ���
#define GPIOE_CRH (*((volatile unsigned int *)0x40011804))   // �˿����ø߼Ĵ���
#define GPIOE_BSRR (*((volatile unsigned int *)0x40011810))  // �˿�λ����/��λ�Ĵ���
#define GPIOE_IDR (*((volatile unsigned int *)0x40011808))   // �˿��������ݼĴ���
#define GPIOE_ODR (*((volatile unsigned int *)0x4001180C))   // �˿�������ݼĴ���

#define GPIOB_CRL (*((volatile unsigned int *)0x40010C00))  // �˿����õͼĴ���
#define GPIOB_IDR (*((volatile unsigned int *)0x40010C08))  // �˿��������ݼĴ���
#define GPIOB_BSRR (*((volatile unsigned int *)0x40010C10)) // �˿�λ����/��λ�Ĵ���
// ??????
extern uint8_t LED_Mode;
extern uint8_t LED_Step;
extern uint32_t Get_Tick(void);

//void LED_Init(void)
//{
//    RCC->APB2ENR |= 3 << 4; // 使能 PORTC 和 PORTD 时钟
//    GPIOC->CRH &= 0xFF0000FF;
//    GPIOC->CRH |= 0x00333300; // PC.10 11 12 13 推挽输出
//    // GPIOC->ODR|=15<<10; //PC.10 11 12 13 输出高
//    GPIOD->CRL &= 0X00000000;
 //   GPIOD->CRL |= 0X33333333; // PD.0 1 2 3 4 5 6 7 推挽输出
 //   // GPIOD->ODR |= 0xFF; //PD.0 1 2 3 4 5 6 7 输出高
  //  GPIOD->BSRR = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; // 输出高电平
   // GPIOD->BSRR = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   // GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
//}

void Delay(unsigned int nCount)
{
    while (nCount > 0)
    {
        nCount--;
    }
}

void KEY_Init(void)
{
    RCC_APB2ENR |= 1 << 3;     // ʹ��PORTBʱ��
    GPIOB_CRL &= ~(0xf << 24); // PB.6��������
    GPIOB_CRL |= (0x08 << 24); // PB.6��������
    GPIOB_BSRR = (1 << 6);
}

//u8 KEY_Scan(void)
//{

   // u8 key_1 = 0;
   // if (GPIOB_IDR & 0x40)
   //     key_1 = 0;
   // else
  //      key_1 = 1;
 //   if (key_1 == 1)
 //   {
//        delay_ms(100); // ȥ����
//        if (GPIOB_IDR & 0x40)
//            key_1 = 0;

//        if (key_1 == 1)
//            return 1;
//    }
//    return 0; // �ް�������
//}
