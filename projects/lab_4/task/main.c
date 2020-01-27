#include "main.h"
#include "init.c"
#include <../lib/ledrgb.h>
#include "usart.c"

#define PWM_PERIOD            100000
#define SWITCH_DELAY    ((uint32_t)2000000)

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);


void delay(uint32_t value)
{
   for (uint32_t i=0; i<value;i++)
   {
      __NOP();
   }

}

int color = 1;
int led = 1;
int counter = 0;
int state,state_1;

void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);
      

     // state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);

      if (state)
         counter++;

     // if (counter > 2)
      {
         switch (color)
         {
         case 1:
            set_color(198,5,248,PWM_PERIOD);
            break;
         case 2:
            set_color(255,245,0,PWM_PERIOD);
            break;
         case 3:
            set_color(151,174,240,PWM_PERIOD);
            break;
         }

         color = color + 1;
         if (color == 4 )
            color = 1;

         counter = 0;
      }
   }
}

void EXTI1_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line1) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line1);

     // state_1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);

      if (state_1)
         counter++;

    //  if (counter > 2)
      {
         switch (led)
         {
         case 1:
            set_color(255,0,0,PWM_PERIOD);
            break;
         case 2:
            set_color(0,255,0,PWM_PERIOD);
            break;
         case 3:
            set_color(0,0,255,PWM_PERIOD);
            break;
         }

         led = led + 1;
         if (led == 4 )
            led = 1;

         counter = 0;

      }
   }
}

int main(void)
{

   SetSysClockTo84();
   configure_buttons_0();
   configure_buttons_1();
   init_and_start_led();



    
   init_board_led();

   init_gpio_usart();
   usart_init();

   USART_SendData(USART2,0x55);
   USART_SendData(USART2,0xAA);

   print("Hello from stm32 ");

   for (;;)
   {
     for (int j=0; j<4;j++) 
        {
            GPIO_ResetBits(GPIOD,GPIO_Pin_12 << j );
            delay(SWITCH_DELAY);
            GPIO_SetBits(GPIOD, GPIO_Pin_12 << j);
        }
   }
}
