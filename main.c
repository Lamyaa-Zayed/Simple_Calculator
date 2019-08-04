#include "Calculator.h"

int main(void)
{

    //unsigned char Key_Pressed;
    LCD_init();
    KeyPad_init();
    LCD_Send_String((unsigned char*)"*Welcome LAMYAA*");
    _delay_ms(2000);

    while(1)
    {
    	//_delay_ms(5000);
    	//LCD_CLear_Screen();
    	//LCD_Display_Number( 12 );
    	//LDC_Display_Real_Number( 15.6);
    	//_delay_ms(5000);
    	/*Key_Pressed=KeyPad_GetKey();
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
                    	_delay_ms(500);
                        break;
        }*/
    	LCD_CLear_Screen();
        Simple_CALC();
    }

    return 0;
}
