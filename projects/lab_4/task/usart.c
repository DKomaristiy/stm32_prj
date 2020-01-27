#include "main.h"
#include "stdio.h"

void init_gpio_usart()
{
 GPIO_InitTypeDef GPIO_InitStructure;  
 GPIO_StructInit(&GPIO_InitStructure);

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
 

GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //PD5 to TX USART2
GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //PD6 to RX USART2


// PD5 -> TX UART.
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOD, &GPIO_InitStructure); 
 
//PD6  -> RX UART. 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
GPIO_Init(GPIOD, &GPIO_InitStructure);

}

void usart_init()
{
  USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
        
  
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // управлени потоком - нет
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;       
        

        
  USART_Init(USART2, &USART_InitStructure); 
  
  USART_Cmd(USART2, ENABLE);

   // выделяем место под буффер
  // setvbuf(stdout, NULL, _IONBF, 0);

}

void print(const char* str)
{
   for(unsigned int i = 0; str[i]; i++)
   {
      while(!USART_GetFlagStatus(USART2,USART_FLAG_TC));
      USART_SendData(USART2,str[i]);
   }
}

void init_board_led()
{
     GPIO_InitTypeDef GPIO_InitStructure;


    /* Enable peripheral clock for LEDs and buttons port */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Init LEDs */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Turn all the leds off */
    GPIO_SetBits(GPIOA, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

}