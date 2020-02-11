#include "main.h"
#include "init.c"


#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"

#include "audio_init.c"

#define PWM_PERIOD            100000
#define SWITCH_DELAY    ((uint32_t)2000000)

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);






/************************************************************************/
void TIM2_IRQHandler()
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
 
    state ^= 0x01;
}
 
 
 
/************************************************************************/ 


void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);
      

     // state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);

     
   }
}

void EXTI1_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line1) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line1);

     // state_1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);

      
   }
}

int main(void)
{

   SetSysClockTo84();
   configure_buttons_0();
   configure_buttons_1();


   init_board_led();


 // Разрешаем прерывания
    __enable_irq();
    // инициализация
    initGPIO();
    initTimer();
    initI2C();
    initI2S();
    initCS32L22();
 
    // Включаем SPI3
    I2S_Cmd(SPI3, ENABLE);
 
    // настраиваем прерывание по переполнению таймера
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    NVIC_EnableIRQ(TIM2_IRQn);
 
    while(1)
    {
        // Если флаг выставлен, то можно передавать данные
	if (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE))
	{
	    if (state == 0x00)
	    {
                // Если переменная state = 0, то посылаем нули
		SPI_I2S_SendData(SPI3, 0x00);
	    }
	    else
	    {
                // А если переменная state != 0, то посылаем 
                // максимальное значение, в итоге получаем 
                // прямоугольные импульсы
   		SPI_I2S_SendData(SPI3, 0xFF);
	    }
	}

   //for (int j=0; j<4;j++) 
        {
           int j =0;
            GPIO_ResetBits(GPIOD,GPIO_Pin_12 << j );
        //    delay(SWITCH_DELAY);
            GPIO_SetBits(GPIOD, GPIO_Pin_12 << j);
        }
   
   			
    }


    
   
}
