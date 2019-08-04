/*
 * Calculator.c
 *
 *  Created on: 26/7/2019
 *      Author: Lamyaa Zayed
 */

#include"Calculator.h"
int KeyPad_Row[]={R0,R1,R2,R3};
int KeyPad_Col[]={C0,C1,C2,C3};
void LCD_init(void)
{

	_delay_ms(20);
	DDIR_LCD_Control_PINS |= (1<<LCD_EN | 1<<LCD_RW | 1<<LCD_RS) ;
	LCD_Control_PINS &= ~(1<<LCD_EN | 1<<LCD_RW | 1<<LCD_RS) ;

	DDIR_LCD_PORT |= 0xFF ;
	_delay_ms(15);

	LCD_CLear_Screen();

	LCD_Send_Command(0x02);
	LCD_Send_Command(LCD_FUNCTION_8BIT_2LINES);

	LCD_Send_Command(LCD_ENTRY_MODE);
	LCD_Send_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_Command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_CLear_Screen ()
{
	LCD_Send_Command(LCD_CLEAR_SCREEN);
}

void LCD_Send_Command(unsigned char command)
{
#if 0
	LCD_PORT = (LCD_PORT & 0xF0) | (command >> 4);
	LCD_Control_PINS &= ~ ((1<<LCD_RW)|(1<<LCD_RS));
	LCD_Kick();
	LCD_PORT = (LCD_PORT & 0xF0) | (command & 0x0F);
	LCD_Control_PINS &= ~ ((1<<LCD_RW)|(1<<LCD_RS));
	LCD_Kick();
#endif
	LCD_PORT = command;
	LCD_Control_PINS &= ~((1 << LCD_RW) | (1 << LCD_RS));
	LCD_Kick();
}

/*void LCD_Send_Command_4mode(unsigned char command)
{
	LCD_PORT&= 0x0F;
	LCD_PORT |= (command&0xF0);
	LCD_Control_PINS &= ~ ((1<<LCD_RW)|(1<<LCD_RS));
	LCD_Control_PINS &= 0x0F;  // Make Data Nibble as 0000
	LCD_Control_PINS |= ((command<<4)&0xF0);
}*/
/*void LCD_init()
{
    _delay_ms(20);
    DDIR_LCD_Control |=(1<<EN_SW | 1<<RS_SW | 1<<RW_SW);
    LCD_Control &=~(1<<EN_SW | 1<<RS_SW | 1<<RW_SW);
    DDIR_LCD_PORT =0xff;
    _delay_ms(15);
    LCD_Clear_Screen();
    LCD_Send_Command(0x02);
    LCD_Send_Command(LCD_Fcn_4bits_2lines);
    LCD_Send_Command(LCD_Entry_Mode);
    LCD_Send_Command(LCD_Begin_At_First_Row);
    LCD_Send_Command(LCD_Disp_ON_Cursor_Blink);
}*/
/*void LCD_Clear_Screen()
{
    LCD_Send_Command(LCD_Clear_Screen);
}*/
/*void LCD_Send_Command(unsigned char Command)
{
    LCD_PORT=(LCD_PORT&0x0f)|(Command&0xf0);
    LCD_PORT_Control&=~(1<<RW_SW | 1<<RS_SW);
    LCD_Kick();
    LCD_PORT=(LCD_PORT&0x0f) | (Command<<4);
    LCD_PORT_Control&=~(1<<RW_SW | 1<<RS_SW);
    LCD_Kick();
}*/

void LCD_Kick()
{
	LCD_Control_PINS&=~(1<<LCD_EN);
    _delay_us(0.5);
    LCD_Control_PINS|=(1<<LCD_EN);
}

void LCD_Send_Character(unsigned char Character)
{
#if 0
	LCD_PORT = (LCD_PORT & 0xF0) | (Character >> 4);
    LCD_Control_PINS|=(1<<LCD_RS);
    LCD_Control_PINS&=~(LCD_RW);
    LCD_Kick();
    LCD_PORT = (LCD_PORT & 0xF0) | (Character & 0x0F);
    LCD_Control_PINS|=(1<<LCD_RS);
    LCD_Control_PINS&=~(LCD_RW);
    LCD_Kick();
#endif
	LCD_PORT = Character;
	LCD_Control_PINS |= (1 << LCD_RS);
	LCD_Control_PINS &= ~(1<<LCD_RW);
	LCD_Kick();
}
void LCD_GOTO_XY(unsigned char Line,unsigned char Position)
{
    if(Position>=0 && Position<16)
    {
        switch(Line)
        {
        	case 0: LCD_Send_Command((LCD_BEGIN_AT_FIRST_RAW)+Position);break;
        	case 1: LCD_Send_Command((LCD_BEGIN_AT_SECOND_RAW)+Position);break;
        	default: break;
        }
    }
}

void LCD_Send_String(unsigned char *String_TO_Disp)
{
    int count;
    //int Size_OF_String = sizeof(String_TO_Disp)/sizeof(String_TO_Disp[0]);
    for(count=0;( (count<16) && (String_TO_Disp[count]!=0));count++)
    {
    	LCD_Send_Character(String_TO_Disp[count]);
    }
    /*
	if (Size_OF_String >= 16)
	{
		LCD_GOTO_XY(1, 0);
		for (; ((count < 32) && (String_TO_Disp[count] != 0)); count++)
		{
			LCD_Send_Character(String_TO_Disp[count]);
		}
	}*/
}

void LCD_Display_Number(int Number)
{
    char Str[7];
    sprintf(Str,"%d",Number);
    LCD_Send_String((unsigned char*)Str);
}

void LDC_Display_Real_Number(double Number)
{
    int NUM_First=Number;
    int NUM_Second=(Number-NUM_First)*1000;
    char Str[16];
    char Sign =(Number<0)?'-':':';
    sprintf(Str,"%c %d. %04d",Sign,NUM_First,NUM_Second);
    LCD_Send_String((unsigned char*)Str);
}

void KeyPad_init()
{
	KEYPAD_DDIR &=~(1<<R0|1<<R1|1<<R2|1<<R3);
	KEYPAD_DDIR |=(1<<C0|1<<C1|1<<C2|1<<C3);
    KEYPAD_PORT |= 0xF0;
}

unsigned char KeyPad_GetKey()
{
    short i,j;
    //KEYPAD_PORT &=~((1<<KeyPad_Col[0])|(1<<KeyPad_Col[1])|(1<<KeyPad_Col[2])|(1<<KeyPad_Col[3]));
    //while(KEYPAD_PIN!=0xF0);
    while(1)
    {
    	for(i=0;i<4;i++)
    	    {
    			KEYPAD_PORT|=((1<<KeyPad_Col[0])|(1<<KeyPad_Col[1])|(1<<KeyPad_Col[2])|(1<<KeyPad_Col[3]));
    			KEYPAD_PORT&= ~(1<<KeyPad_Col[i]);
    	    	_delay_ms(5);
    	        for(j=0;j<4;j++)
    	        {
    	            if(!(KEYPAD_PIN & (1<<KeyPad_Row[j])))
    	            {
    	            	_delay_ms(20);
    	                if(!(KEYPAD_PIN & (1<<KeyPad_Row[j])))
    	                {
    	                	switch(i)
    	                	                {
    	                	                    case 0:{
    	                	                                if(j==0) return '7';
    	                	                                else if (j==1) return '4';
    	                	                                else if (j==2) return '1';
    	                	                                else if (j==3) return '.';
    	                	                                break;
    	                	                             }
    	                	                    case 1:{
    	                	                                if(j==0) return '8';
    	                	                                else if (j==1) return '5';
    	                	                                else if (j==2) return '2';
    	                	                                else if (j==3) return '0';
    	                	                                break;
    	                	                             }
    	                	                   case 2:{
    	                	                                if(j==0) return '9';
    	                	                                else if (j==1) return '6';
    	                	                                else if (j==2) return '3';
    	                	                                else if (j==3) return '=';
    	                	                                break;
    	                	                             }
    	                	                   case 3:{
    	                	                                if(j==0) return '/';
    	                	                                else if(j==1) return '*';
    	                	                                else if (j==2) return '-';
    	                	                                else if (j==3) return '+';
    	                	                                break;
    	                	                             }
    	                	                }
    	                }

    	            }
    	        }
    	    }
    }
    LCD_Send_String((unsigned char*)"No KEY Pressed");
    return 'A';
}

void KEYPAD_CLEAR()
{
	if(KeyPad_GetKey()=='.')
	{
		LCD_CLear_Screen();
		_delay_ms(500);
	}
}

void Simple_CALC()
{
	unsigned char Key_Pressed;
	unsigned char First_Digit , Second_Digit , First_Operator , Second_Oparator;
	unsigned char Result , Calc_ERROR=0;
	LCD_CLear_Screen();
	Key_Pressed=KeyPad_GetKey();
	//KEYPAD_CLEAR();
    First_Digit=Key_Pressed;
    LCD_Send_Character(First_Digit);
    _delay_ms(500);
    Key_Pressed=KeyPad_GetKey();
    //KEYPAD_CLEAR();
    First_Operator=Key_Pressed;
    LCD_Send_Character(First_Operator);
    _delay_ms(500);
    Key_Pressed=KeyPad_GetKey();
    //KEYPAD_CLEAR();
    Second_Digit=Key_Pressed;
    LCD_Send_Character(Second_Digit);
    _delay_ms(500);
    Key_Pressed=KeyPad_GetKey();
    //KEYPAD_CLEAR();
    Second_Oparator=Key_Pressed;
    LCD_Send_Character(Second_Oparator);
    _delay_ms(500);

    switch(First_Operator)
    {

        case '+':{
        			Result=(First_Digit&0x0F)+(Second_Digit&0x0F);
                    //LCD_Send_Character(Result);
                    //_delay_ms(500);
                    break;
                 }
        case '-':{
        			Result=(First_Digit&0x0F)-(Second_Digit&0x0F);
                    //LCD_Send_Character(Result);
                    //_delay_ms(500);
                    break;
                 }
        case '*':{
        			Result=(First_Digit&0x0F)*(Second_Digit&0x0F);
                    //LCD_Send_Character(Result);
                    //_delay_ms(500);
                    break;
                 }
        case '/':{
        			Result=(First_Digit&0x0F)/(Second_Digit&0x0F);
        			if((Second_Digit&0x0F)==0)
        			{
        				Calc_ERROR=1;
        			}
                    //LCD_Send_Character(Result);
                    //_delay_ms(500);
                    break;
                 }
        default: {
        			LCD_Send_String((unsigned char*)"Error");
        		    _delay_ms(500);
        			break;
        		 }
    }
    if(Calc_ERROR==1)
    {
    	LCD_Send_String((unsigned char*)"Error");
    }
    else
    {
    	 LCD_Send_Character(Result|0x30);
    	 _delay_ms(500);
    }
    Key_Pressed=KeyPad_GetKey();
    KEYPAD_CLEAR();
}
