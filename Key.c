#include <xc.h>
#include "Beep.h"
#include "Key.h"
#include "Oled.h"
//#include "PositionControl.h"

KeyType OnOffKey={0},UpKey={0},DownKey={0},ConfirmKey={0},StartInjectKey={0};

unsigned char KeyScanPeriod =0;

#if 1
void KEY_Init(void) //
{ 
   
#if 1
    //LATB = 0;
   // PORTB = 0;
    //ADCON1 = 0x00;
    
    //ADCON0 = 0x00;
    ADCON1 = 0x0C;

    TRISBbits.RB3 =1;//KEY_V
    TRISBbits.RB4 =1;//KEY_WAKE
    
    TRISDbits.RD6 =1;//KEY_UP
    TRISDbits.RD7 =1;//KEY_DOWN
    
    TRISBbits.RB5 =1;//ACTION_BUTTON
    

    
    TRISBbits.RB0 =1;//LP_BUTTON

    
    TRISAbits.RA3 =1;//STATUS_CHARGE
    //TRISB = 0xff;
    
#endif
    
    
#if 0
    //RCONbits.IPEN = 1;
    
    INTCON2bits.INTEDG0 =0;//falling edge
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0E = 1;//int0 enabled
     
     
    //TRISB = 0xff;
    INTCONbits.RBIE =1;
    INTCONbits.PEIE =1;
    INTCONbits.GIE =1;
    
#endif
       
}

uint8_t KEY_Scan(void)
{           
        if(KEY_UP == 0)
        {
           
             delay_nms(10);
            
             if(KEY_UP == 0)
             {
                 while(KEY_UP == 0);
                   buzz();
                   
                   return KEY_UP_PRESSED;
             }
        }
        if(KEY_DOWN == 0)
        {
         
             delay_nms(10);
             if(KEY_DOWN == 0)
             {
                 while(KEY_DOWN == 0);
                   buzz();
                   
                   return KEY_DOWN_PRESSED;
             }
            
            
            //buzz();
        }
        if(KEY_V == 0)
        {
              delay_nms(10);
             if(KEY_V == 0)
             {
                 while(KEY_V == 0);
                   buzz();
                   
                   return KEY_V_PRESSED;
             }
        }  
        
        
        
        return KEY_NOT_PRESSED;
}












void KeyFuction(void)
{
    

}


#endif