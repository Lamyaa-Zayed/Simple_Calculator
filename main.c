#include "Calculator.h"

int main(void)
{

    unsigned char Key_Pressed;
    LCD_init();
    KeyPad_init();
    LCD_Send_String("LAMYAA");

    while(0)
    {
    	LCD_Send_String("LAMYAA");
    	_delay_ms(1000);
    	Key_Pressed=KeyPad_GetKey();
        switch(Key_Pressed)
        {
            case 'A':{
                        break;
                     }
            case '.':{
            	LCD_CLear_Screen();
                        break;
                     }
            default:
                        LCD_Send_Character(Key_Pressed);
                        break;
        }
        Simple_CALC();
    }

    return 0;
}
