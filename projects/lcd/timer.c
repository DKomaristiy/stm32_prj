#include "lcd.h"
#include "timer.h"
//------------------------------------------------
static volatile unsigned long tick_counter = 0;



unsigned long osif_tick_count(void)
{
	unsigned long ret;
	__disable_irq;
	ret = tick_counter;
	__enable_irq;
    return ret;
}

void sleep_tick_ms(unsigned long timeout_ms)
{
	if(timeout_ms)
	{
		unsigned long  t =0;
		t = osif_tick_count() + timeout_ms;
		while(osif_tick_count() != t);
		
		
	}

}

void configure_timer_2(void)
{
   TIM_TimeBaseInitTypeDef tim_init;
   NVIC_InitTypeDef     timer_nvic_init_structure = { 0x0 };
   /* Second timer to track brightness change */
   TIM_TimeBaseStructInit(&tim_init);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   tim_init.TIM_Prescaler         = 168 - 1;
   tim_init.TIM_Period            = 999;
   tim_init.TIM_ClockDivision     = TIM_CKD_DIV1;
   tim_init.TIM_RepetitionCounter = 0;
   TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
   TIM_TimeBaseInit(TIM2, &tim_init);

   /* Configure timer interrupts */
   TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
   timer_nvic_init_structure.NVIC_IRQChannel = TIM2_IRQn;
   timer_nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 0;
   timer_nvic_init_structure.NVIC_IRQChannelSubPriority = 1;
   timer_nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&timer_nvic_init_structure);

   TIM_Cmd(TIM2, ENABLE);
 

}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        tick_counter +=1;
		
       
    }
}





