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

/*
#define d4_set() GPIO_WriteBit(GPIOD, GPIO_Pin_4,Bit_SET)
#define d5_set() GPIO_WriteBit(GPIOD, GPIO_Pin_5,Bit_SET)
#define d6_set() GPIO_WriteBit(GPIOD, GPIO_Pin_6,Bit_SET)
#define d7_set() GPIO_WriteBit(GPIOD, GPIO_Pin_7,Bit_SET)
#define d4_reset() GPIO_WriteBit(GPIOD, GPIO_Pin_4,Bit_RESET)
#define d5_reset() GPIO_WriteBit(GPIOD, GPIO_Pin_5,Bit_RESET)
#define d6_reset() GPIO_WriteBit(GPIOD, GPIO_Pin_6,Bit_RESET)
#define d7_reset() GPIO_WriteBit(GPIOD, GPIO_Pin_7,Bit_RESET)
#define e1 GPIO_WriteBit(GPIOB, GPIO_Pin_9,Bit_SET) 
#define e0 GPIO_WriteBit(GPIOB, GPIO_Pin_9,Bit_RESET) 
#define rs1 GPIO_WriteBit(GPIOB, GPIO_Pin_8,Bit_SET) // RS � 1
#define rs0 GPIO_WriteBit(GPIOB, GPIO_Pin_8,Bit_RESET) // RS � 0
*/
//------------------------------------------------

void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
void LCD_WriteData(uint8_t dt);
void LCD_Command(uint8_t dt);
void LCD_Data(uint8_t dt);
void delay(void);

void Delay_t(uint32_t value);
//------------------------------------------------
#endif /* LCD_H_ */
