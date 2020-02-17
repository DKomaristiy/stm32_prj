
#include <stm32f4xx.h>

#include "main.h"
#include "timer.h"
#include <stdio.h>

uint16_t ADC_Data=0;

/* Private function prototypes -----------------------------------------------*/
void SetSysClockTo168(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
void adc_init() ;
uint16_t readADC1(uint8_t channel);

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

int main(void)
{
	char str1[7];
	uint16_t adc_value=0;

  /* Configure the system clock */
  SetSysClockTo168();

  configure_timer_2();

  init_board_led();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  
  adc_init();

  sleep_tick_ms(1500);
  ADC_TempSensorVrefintCmd(ENABLE); 

	LCD_ini();
	LCD_Clear();
  sleep_tick_ms(1000);

  LCD_SetPos(0, 1);
  LCD_String("HELLO FRom MK");

  while (1)
  {
		adc_value = readADC1(ADC_Channel_5);
		LCD_SetPos(0, 0);
    utoa(adc_value, str1, 10);
   	LCD_String(str1);
		
		if(adc_value<200) LCD_String(" RIGHT KEY ");
		else if(adc_value<700) LCD_String(" UP KEY    ");
		else if(adc_value<1200) LCD_String(" DOWN KEY  ");
		else if(adc_value<1800) LCD_String(" LEFT KEY  ");
		else if(adc_value<2300) LCD_String(" SELECT KEY");
		sleep_tick_ms(200);
    

   /*for (int j=0; j<4;j++) 
        {    
            GPIO_SetBits(GPIOD, GPIO_Pin_12 << j);     
            sleep_tick_ms(1000);
            GPIO_ResetBits(GPIOD,GPIO_Pin_12 << j ); 
            
        }
      */  
  }
  

}

/** System Clock Configuration
*/

void SetSysClockTo168(void)
{
  int HSEStartUpStatus;
  RCC_DeInit();
  /* Enable HSE */
  RCC_HSEConfig( RCC_HSE_ON);


  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {

     RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,4);

     RCC_PLLCmd( ENABLE);

        /* Wait till PLL is ready */
     while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
     {
     }

     /* Select PLL as system clock source */
     RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);

     /* Wait till PLL is used as system clock source */
     while (RCC_GetSYSCLKSource() != 0x08)
     {
     }

  }
}


void adc_init() 
{
       ADC_InitTypeDef ADC_InitStructure;
       ADC_StructInit(&ADC_InitStructure);
 
       ADC_CommonInitTypeDef adc_init;
       ADC_CommonStructInit(&adc_init);
       /* разрешаем тактирование AЦП1 */
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
       /* сбрасываем настройки АЦП */
       ADC_DeInit();
 
       /* АЦП1 и АЦП2 работают независимо */
       adc_init.ADC_Mode = ADC_Mode_Independent;
       adc_init.ADC_Prescaler = ADC_Prescaler_Div2;
       /* выключаем scan conversion */
       ADC_InitStructure.ADC_ScanConvMode = DISABLE;
       /* Не делать длительные преобразования */
       ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
 
       /* Начинать преобразование программно, а не по срабатыванию триггера */
       ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
       /* 12 битное преобразование. результат в 12 младших разрядах результата */
       ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
 
       /* инициализация */
       ADC_CommonInit(&adc_init);
 
       ADC_Init(ADC1, &ADC_InitStructure);
       /* Включаем АЦП1 */
       ADC_Cmd(ADC1, ENABLE);

      
}
uint16_t readADC1(uint8_t channel)
{
   ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_3Cycles);
   // начинаем работу
   ADC_SoftwareStartConv(ADC1);
   // ждём пока преобразуется напряжение в код
   while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
   // возвращаем результат
   return ADC_GetConversionValue(ADC1);
}

static void MX_GPIO_Init(void)
{


  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIO Ports Clock Enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

  //GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM1);

  //PA5 – вход АЦП
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*Configure GPIO pin Output Level */
  GPIO_ResetBits(GPIOD, GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7);

  /*Configure GPIO pin Output Level */
  GPIO_ResetBits(GPIOD, GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7);
  GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_9 );

  /*Configure GPIO pins : PD4 PD5 PD6 PD7 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /*Configure GPIO pins : PB8 PB9 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  

}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{

}

#endif

