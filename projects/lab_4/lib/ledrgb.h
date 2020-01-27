#ifndef MAIN_H__
#define MAIN_H__

/**
  ******************************************************************************
  * @file    ledrgb.c
  * @author  D.Komaristiy
  * @version V1.0.0
  * @date    10-12-2019
  * @brief   This file provides to manage the led color
  * */


#include <stm32f4xx.h>

/* PWM frequency */
#define PWM_FREQUENCY_HZ      50
#define PWM_PERIOD            100000
#define PRESCALE_TIM          840



void configure_leds(void);
void configure_timers(uint32_t prescaler, uint32_t period);
void configure_pwm(void);
void start_timers(void);
void init_and_start_led(void);
int set_color(uint8_t red, uint8_t green, uint8_t blue, uint32_t period);



#endif
