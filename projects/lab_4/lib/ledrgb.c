/**
  ******************************************************************************
  * @file    ledrgb.c
  * @author  D.Komaristiy
  * @version V1.0.0
  * @date    10-12-2019
  * @brief   This file provides to manage the led color
  * */

#include "ledrgb.h"

/** @addtogroup STM32f407DIS
  * @{
  */

/** @defgroup LED
  * @brief Led driver modules
  *
  *
  * @attention The driver allows you to control the color of the LED
  *

  */


/**
  * @brief  Configures port pins for PWM

  * @param  None
  * @retval None
  */

void configure_leds(void)
{
    GPIO_InitTypeDef gpio_init;
    GPIO_StructInit(&gpio_init);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);

    /* Initialize GPIOs for an alternative function (TIM1 PWM output) */
    gpio_init.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &gpio_init);
}

/**
  * @brief  Configures timer for PWM

  * @param prescaler: value of  timer prescaler
  * @param period: value of  timer period
  * @retval None
  */

void configure_timers(uint32_t prescaler, uint32_t period)
{
    /* Timer */
    TIM_TimeBaseInitTypeDef tim_init;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseStructInit(&tim_init);
    tim_init.TIM_Prescaler         = prescaler;
    tim_init.TIM_CounterMode       = TIM_CounterMode_Up;
    tim_init.TIM_Period            = period / PWM_FREQUENCY_HZ - 1;
    tim_init.TIM_ClockDivision     = TIM_CKD_DIV1;
    tim_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &tim_init);


}

/**
  * @brief  Configure PWM for three channels 1 to 3

  * @param  None
  * @retval None
  */

void configure_pwm(void)
{
    TIM_OCInitTypeDef tim_oc_init;

    TIM_OCStructInit(&tim_oc_init);

    tim_oc_init.TIM_OCMode      = TIM_OCMode_PWM1;
    tim_oc_init.TIM_Pulse       = 0; //(uint16_t)(100000 / PWM_FREQUENCY_HZ - 1) ;
    tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init.TIM_OCPolarity  = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM1, &tim_oc_init);
    TIM_OC2Init(TIM1, &tim_oc_init);
    TIM_OC3Init(TIM1, &tim_oc_init);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/**
  * @brief  Starts the timer

  * @param  None
  * @retval None
  */


void start_timers(void)
{
    TIM_Cmd(TIM1, ENABLE);
}


/**
  * @brief  Enable and change color LED

  * @param  red: where red can be  0 to 255
  * @param  green: where red can be  0 to 255
  * @param  blue: where red can be  0 to 255
  * @param  period: value of period for pulse, where pulse = (period / PWM_FREQUENCY_HZ-1) /255 ;
  * @retval 0
  */


int set_color(uint8_t red, uint8_t green, uint8_t blue, uint32_t period)
{
    uint32_t pulse = (period / PWM_FREQUENCY_HZ-1) /255 ;

    TIM_SetCompare1(TIM1, pulse * red);
    TIM_SetCompare2(TIM1, pulse * green);
    TIM_SetCompare3(TIM1, pulse * blue);

    return 0;
}

/**
  * @brief  Initializing and running the periphery of LED

  * @param  None
  * @retval None
  */

void init_and_start_led(void)
{
  configure_leds();
  configure_timers(PRESCALE_TIM, PWM_PERIOD);
  configure_pwm();
  start_timers();
  

}


