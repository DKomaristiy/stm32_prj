
#include <stm32f4xx.h>

#include "main.h"
//#include "lcd.c"
//#include "timer.c"
#include "timer.h"


//#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
 // ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t ADC_Data=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SetSysClockTo168();
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

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

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	char str1[7];
	uint16_t adc_value=0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
 // HAL_Init();

  /* Configure the system clock */
  SetSysClockTo168();

  configure_timer_2();

  init_board_led();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  
 // MX_ADC1_Init();

  
  
  
sleep_tick_ms(500);

	LCD_ini();
	LCD_Clear();
 sleep_tick_ms(1000);
 LCD_SendChar("T");
 LCD_SendChar("T");
 LCD_SendChar("T");
 LCD_SendChar("T");
 LCD_SendChar("T");
LCD_SendChar("T");
  sleep_tick_ms(1000);

LCD_SendChar("T");
 LCD_SendChar("T");
 LCD_SendChar("T");
LCD_SendChar("T");
  sleep_tick_ms(1000);
LCD_SendChar("T");
 LCD_SendChar("T");




  while (1)
  {
	//	adc_value = ADC_Data;
	//	LCD_SetPos(0, 0);
	//	sprintf(str1,"%d   ",adc_value);
	/*	LCD_String(str1);
		
		if(adc_value<200) LCD_String("RIGHT KEY ");
		else if(adc_value<700) LCD_String("UP KEY    ");
		else if(adc_value<1200) LCD_String("DOWN KEY  ");
		else if(adc_value<1800) LCD_String("LEFT KEY  ");
		else if(adc_value<2300) LCD_String("SELECT KEY");
		HAL_Delay(200);
    */
  // LCD_String("HELLO FRom MK");
   //sleep_tick_ms(2000);
   for (int j=0; j<4;j++) 
        {    
            GPIO_SetBits(GPIOD, GPIO_Pin_12 << j);     
            sleep_tick_ms(1000);
            GPIO_ResetBits(GPIOD,GPIO_Pin_12 << j );
            
        }
        
 /*       sleep_tick_ms(10);
LCD_SendChar("S");
sleep_tick_ms(10);
LCD_SendChar("t");
sleep_tick_ms(10);
LCD_SendChar("1");
sleep_tick_ms(10);*/


     
      // LCD_SetPos(0, 1);
       // LCD_String("BY BY    ");
       sleep_tick_ms(1000);
        LCD_String("SELECT KEY");
        
  


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



/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  //ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  /*hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }*/

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  /* sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
*/
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{


  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIO Ports Clock Enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

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

/* USER CODE BEGIN 4 */
/*void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)
{
	ADC_Data = HAL_ADC_GetValue(hadc1);
//	HAL_ADC_Start_IT(hadc1);
}*/
/* USER CODE END 4 */
/*
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
