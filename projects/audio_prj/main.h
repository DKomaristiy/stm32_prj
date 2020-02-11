#ifndef MAIN_H__
#define MAIN_H__

#include <stm32f4xx.h>

/* PWM frequency */
#define PWM_FREQUENCY_HZ      50

void configure_buttons_0(void);
void configure_buttons_1(void);
void SetSysClockTo84(void);
void usart_init();
void init_gpio_usart();
void init_board_led();




#endif
