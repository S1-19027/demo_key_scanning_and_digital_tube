/**
 ******************************************************************************
 * @file InputCaptureMode/main.c
 * @author   MCD Application Team
 * @version  V3.0.0
 * @date     04/27/2009
 * @brief    Main program body
 ******************************************************************************
 * @copy
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
 */

/** @addtogroup InputCaptureMode
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO.h"
#include "LED.h"
#include "KEY.h"
#include "sys.h"
void BoardInit()
{
  SystemInit();
}

void SysTick_Init(void)
{
  // SysTick ??:? 1ms ????
  SysTick->LOAD = 72000 - 1; // 72MHz / 1000 = 1ms
  SysTick->VAL = 0;          // ?????
  SysTick->CTRL = 0x07;      // ?? SysTick,??????,????
}

int main(void)
{
 int key_value = 0;


  //BoardInit();
  LED_Init();
  KEY_Configuration(); // 使用矩阵键盘初始化
  //SysTick_Init();
	//Display_Number(0); 
  while (1)
  {
    key_value = KEY_GetOneShot();

      // 有按键按下且与上次不同，
      // 按键值1-16对应显示0-F
		if (key_value!=-1)
		{
			
			Update_Number(key_value);
		}
		Refresh_Display();//把他们拆开来！刷新函数单独执行。
    // 防抖延时
    delay_ms(10);
  }

  return 1;
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
