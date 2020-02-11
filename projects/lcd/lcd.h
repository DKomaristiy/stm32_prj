#ifndef LCD_H_
#define LCD_H_
//------------------------------------------------
#include "stdint.h"
#include <stm32f4xx.h>

//------------------------------------------------
//------------------------------------------------
#define d4_set() GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define d5_set() GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define d6_set() GPIO_SetBits(GPIOD, GPIO_Pin_6)
#define d7_set() GPIO_SetBits(GPIOD, GPIO_Pin_7)
#define d4_reset() GPIO_ResetBits(GPIOD,GPIO_Pin_4)
#define d5_reset() GPIO_ResetBits(GPIOD,GPIO_Pin_5)
#define d6_reset() GPIO_ResetBits(GPIOD,GPIO_Pin_6)
#define d7_reset() GPIO_ResetBits(GPIOD,GPIO_Pin_7)
#define e1 GPIO_SetBits(GPIOB, GPIO_Pin_9) 
#define e0 GPIO_ResetBits(GPIOB,GPIO_Pin_9) 
#define rs1 GPIO_SetBits(GPIOB, GPIO_Pin_8) // RS � 1
#define rs0 GPIO_ResetBits(GPIOB,GPIO_Pin_8)  // RS � 0
//------------------------------------------------

void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
//------------------------------------------------
#endif /* LCD_H_ */
