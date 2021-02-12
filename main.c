#include <intrinsics.h>
#include "stm32f10x.h"
#include "main.h"

void Sleep(int msec);

void main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_ClocksTypeDef RCC_Clocks;
  
  __disable_interrupt();
  
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  //SystemInit();
  
  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  
  // PA5 connected LED2
  
  /*RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);*/
  RCC->APB2ENR |= 0x00000004;
  /*RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);*/
  RCC->APB2RSTR &= ~0x4;
  RCC->APB2RSTR &= 0xFFFFFFF;
  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  __enable_interrupt();
  
  while(1)
  {   
    GPIO_WriteBit(GPIOA,GPIO_Pin_5 ,Bit_SET);
    Sleep(1000);
    //Delay(1000);
    
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
    Sleep(1000);
    //Delay(1000);
  }
}

// sleep cpu
void Sleep(int msec){
  int i, j;
  for(i = 0; i < msec; i++)
  {
    for(j = 0; j < 72000/4; j++)
    {
    }
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if(TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}