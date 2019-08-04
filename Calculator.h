/*
 * Calculator.h
 *
 *  Created on: 26/7/2019
 *      Author: Lamyaa Zayed
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include<avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

/*
DDRA=*((volatile unsigned char *const)0x);
PortA=*((volatile unsigned char *const)0x);
PINA=*((volatile unsigned char *const)0x);

DDRC=*((volatile unsigned char *const)0x);
PortA=*((volatile unsigned char *const)0x);
PINA=*((volatile unsigned char *const)0x);

DDRD=*((volatile unsigned char *const)0x);
PortA=*((volatile unsigned char *const)0x);
PINA=*((volatile unsigned char *const)0x);
*/

#define FOUR_BIT_MODE

#define LCD_PORT PORTD
#define DDIR_LCD_PORT DDRD
#define LCD_Control_PINS PORTC
#define DDIR_LCD_Control_PINS DDRC
#define DATA_shift 0
#define LCD_D0 0
#define LCD_D1 1
#define LCD_D2 2
#define LCD_D3 3
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define KEYPAD_PORT PORTA     //write
#define KEYPAD_DDIR DDRA
#define KEYPAD_PIN PINA       //read
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7


#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE                              (0x06)

void LCD_init(void);
void LCD_CLear_Screen();
void LCD_Send_Command(unsigned char command);
void LCD_Kick();
void LCD_Send_Character(unsigned char Character);
void LCD_GOTO_XY(unsigned char Line,unsigned char Position);
void LCD_Send_String(unsigned char *String_TO_Disp);
void LCD_Display_Number(int Number);
void LDC_Display_Real_Number(double Number);
void KeyPad_init();
unsigned char KeyPad_GetKey();
void Simple_CALC();

#endif /* CALCULATOR_H_ */
