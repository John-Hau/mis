#include<xc.h> 
#include <stdio.h>
#include<stdlib.h> 
#include "Oled.h"	 
#include "Beep.h"
#include "Key.h"	
#include "gui.h"	
void delay_nms(uint32_t n)
{
    uint16_t i=0;
    while(n)
    {
    
        for(i=0;i<5000;i++)
            NOP();
        
        n--;
    }

}

void delay_f(uint32_t n)
{
    uint16_t i=0;
    while(n)
    {
    
        for(i=0;i<500;i++)
            NOP();
        
        n--;
    }

}








void delay_pwm(uint16_t  n)
{
    while(n)
    {
         NOP();
         n--;
    }
}


void delay(unsigned int  x)
{
  	unsigned int  i,j;
    for(i=0;i<x;i++)
       for(j=0;j<10000;j++);
}

static void i2c_Delay(void)
{
	uint32_t i;
	//for (i = 0; i < 10; i++);
    
    
      	//unsigned int  i,j;
    //for(i=0;i<100;i++)
       //for(j=0;j<100;j++);
    
    
    
    
    
}

void i2c_Start(void)
{

	EEPROM_I2C_SDA_1();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_0();
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
}


void i2c_Stop(void)
{
	
	EEPROM_I2C_SDA_0();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_1();
}


void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			EEPROM_I2C_SDA_1();
		}
		else
		{
			EEPROM_I2C_SDA_0();
		}
		i2c_Delay();
		EEPROM_I2C_SCL_1();
		i2c_Delay();	
		EEPROM_I2C_SCL_0();
		if (i == 7)
		{
			 EEPROM_I2C_SDA_1(); 
		}
		_ucByte <<= 1;	
		i2c_Delay();
	}
}


uint8_t i2c_ReadByte(void)
{
#if 0
	uint8_t i;
	uint8_t value;
    
    //DDRCbits.RC4 =1;//====================input mode
    TRISCbits.RC4 =1;
    
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		EEPROM_I2C_SCL_1();
		i2c_Delay();
		if (EEPROM_I2C_SDA_READ())
		{
			value++;
		}
        //DDRCbits.RC4 =0;//====================come back to output mode
		EEPROM_I2C_SCL_0();
		i2c_Delay();
	}
    // DDRCbits.RC4 =0;//====================come back to output mode
     TRISCbits.RC4 =1;
	return value;
#endif
}


uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	EEPROM_I2C_SDA_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();
   // DDRCbits.RC4 =1;//====================sda input mode
    
#if defined(ORIGINAL)
    TRISCbits.RC4 =1;//original
    
#elif defined(LTEMP)
    TRISCbits.RC3 =1;//temp
#endif
    
	i2c_Delay();
	if (EEPROM_I2C_SDA_READ())	
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
   
	EEPROM_I2C_SCL_0();
    // DDRCbits.RC4 =0;//====================come back to output mode

     #if defined(ORIGINAL)
    TRISCbits.RC4 =0;//original
    
    #elif defined(LTEMP)
        TRISCbits.RC3 =0;//temp
    #endif
     
     
     
	i2c_Delay();
    
	return re;
}


void i2c_Ack(void)
{
	EEPROM_I2C_SDA_0();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	EEPROM_I2C_SDA_1();
}


void i2c_NAck(void)
{
	EEPROM_I2C_SDA_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
}


void i2c_CfgGpio(void)
{
    
    //PORTCbits.RC3 =1;//SCL
    //DDRCbits.RC3 =0;
    TRISCbits.RC3 =0;
    LATCbits.LC3 =0;
       
    
    //PORTCbits.RC4 =1;
    //DDRCbits.RC4 =0;//SDA
    TRISCbits.RC4 =0;
    LATCbits.LC4 =0;
    
   
    
     
    //PORTEbits.RE1 =1;
    //DDREbits.RE1 =0;//res
    TRISEbits.RE1 =0;
    //LATEbits.LE1 =1;
    // LATEbits.LATE1=1;
  //LATEbits.LATE1=0;
  LATEbits.LATE1=0;
  //delay(500);
  //delay(2);
    //PORTCbits.RC3 =1;//SCL
    //PORTCbits.RC4 =1;//SDA
    //i2c_Stop();
     
}



	   
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}
//================================================================================
//AD converter  Battery
//================================================================================



unsigned int StartAndReadAdValue(unsigned char ch)
{
#if 0
	unsigned int delay =1000;
	unsigned int value =0; 

	//SetAdChanel(ch);
	//StartAdConvert();
	while(delay-- && (ADCON0 & 0x2));
	
	value=((unsigned int)ADRESH <<2)|value; 
		
	return(value);	
#endif
}



uint8_t AD_init(void)
{
    
    TRISAbits.RA0 =1;//AD0
    TRISAbits.RA1 =1;//Motor sense A
    TRISAbits.RA2 =1;//Motor sense B
    
    
    
    ADCON2bits.ACQT = 4;
   // ADCON0bits.CHS = 0;//choose channel 0
    ADCON0bits.ADON = 1;


    return 1;
}








uint16_t get_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
    uint8_t ts=0; 
   uint16_t rv=0;
   ADCON0bits.CHS = 0;//choose channel 0
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   //ts = rv;
   return rv;




}




uint16_t get_SenseA_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
 
   uint16_t rv=0;
   ADCON0bits.CHS = 1;//choose channel 1
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   return rv;
}



uint16_t get_SenseB_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
   uint16_t rv=0;
   ADCON0bits.CHS = 2;//choose channel 2
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   //ts = rv;
   return rv;




}










//=============================================================================================
//=============================================================================================


uint8_t ee_CheckDevice(uint8_t _Address)
{
    
#if 1
	uint8_t ucAck;
	
	i2c_Start();		

	
	i2c_SendByte(_Address | EEPROM_I2C_WR);
	ucAck = i2c_WaitAck();	

	i2c_Stop();			

	i2c_NAck();	
	
	return ucAck;
    
    
#endif
}



uint8_t ee_WaitStandby(void)
{

}


uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
    
#if 0
	uint16_t i;
	
	
	
	
	i2c_Start();
	
	
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	
	 
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}

	
	i2c_SendByte((uint8_t)_usAddress);
	
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}
	
	
	i2c_Start();
	
	
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_RD);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}	
	
	
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = i2c_ReadByte();	
		
		
		if (i != _usSize - 1)
		{
			i2c_Ack();	
		}
		else
		{
			i2c_NAck();	
		}
	}
	
	i2c_Stop();
	return 1;	

cmd_fail: 
	i2c_Stop();
	return 0;
    
    
    
    
#endif
}

//uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint8_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	//uint16_t usAddr;
    uint8_t usAddr;

	usAddr = _usAddress;	
	//for (i = 0; i < _usSize; i++)
	{
		//if ((i == 0) || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0)
		{
			//i2c_Stop();
			
			//for (m = 0; m < 1000; m++)
            //for (m = 0; m < 1; m++)
			{				
				i2c_Start();
				
				i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	
				
				if (i2c_WaitAck() == 0)
				{
                    
                    //buzz();
					//break;
				}
                else
                {
                     //buzz();
                }
			}
			if (m  == 1000)
			{
				//goto cmd_fail;	
			}
		
			i2c_SendByte(usAddr);
			
			if (i2c_WaitAck() != 0)
			{
                //buzz();
				//goto cmd_fail;	
			}
		}
	
		//i2c_SendByte(_pWriteBuf[i]);
	    i2c_SendByte(_pWriteBuf[0]);
		if (i2c_WaitAck() != 0)
		{
            //buzz();
			//goto cmd_fail;	
		}

		//usAddr++;
	}
	
	i2c_Stop();
	
	//if(ee_WaitStandby() == 1)
		//goto cmd_fail;
	
	return 1;

cmd_fail: 
	i2c_Stop();
   // buzz();
	return 0;
}





uint8_t write_buf[256];
uint8_t read_buf[256];

uint8_t ee_Test(void) 
{
      return 1;
}







void LCD_backlight_init(void)
{

}

void LCD_On(void)
{

     //PORTEbits.RE0 =1;
      LATEbits.LE0 =1;
     
     
     
}
void LCD_Off(void)
{
    //PORTEbits.RE0 =0;
    LATEbits.LE0 =0;
    
 
}

void LCD_Blink(void)
{

     LATEbits.LE0 =1;
     delay(50);
     LATEbits.LE0 =0;
}


uint8_t setYX_LCD(uint8_t py,uint8_t px)
{


   write_buf[0]=0x80 + px;//X address
	ee_WriteBytes(write_buf, 0x00, 1);
    
   
    write_buf[0]=0x40 + py;//Y address
	ee_WriteBytes(write_buf, 0x00, 1);
    
    return 1;
   
}













uint8_t ms = 0x66;
uint8_t ss=0;
uint8_t css=0;
uint8_t rcnt=0;
uint8_t page=0;
uint16_t xtt=0;



const uint8_t blank_m[2][23]={
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
    0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
};




const uint8_t c_m[2][23]= {
  
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x98, 0xb8, 0xb0, 0xb0, 0xb0, 0xb8, 0x9f, 
    0x8f, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x19, 0x1d, 0x0d, 0x0d, 0x0d, 0x1d, 0xf9, 
    0xf1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,

    
};





const uint8_t drops_m [2][23]={
    
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80, 0x80, 
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80, 0x80, 
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80,


   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1, 0x01, 
   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1, 0x01,
   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1,
 

  
};




const uint8_t drop_m[2][23] ={
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81,
    0x83, 0x86, 0x9d, 0xbd, 0x9d, 0x86, 0x83, 0x81, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    
    
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf1,
    0xf9, 0xcd, 0xb5, 0xb5, 0xb5, 0x6d, 0xf9, 0xf1, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,


};

//==============================================================================


const uint8_t mem_m [2][23]={
    0x9f, 0x9f, 0x90, 0x9f, 0x9f, 0x90, 0x9f, 0x9f, 
    0x80, 0x9d, 0x95, 0x95, 0x9f, 0x8e, 0x80, 0xbf, 
    0xbf, 0x90, 0x88, 0x90, 0xbf, 0xbf, 0x80,
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x51, 0x7d, 0x3d, 
    0x01, 0x51, 0x7d, 0x3d, 0x01, 0x39, 0x7d, 0x45, 
    0x7d, 0x39, 0x01, 0x01, 0x01, 0x01, 0x01,

    

};

const uint8_t bat_m[2][23]={
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8f, 
    0x8b, 0xbb, 0xa3, 0xa3, 0xa3, 0xbb, 0x8b, 0x8f, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xfd, 
    0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,


};



const uint8_t n_blank_m[3][19]={
  
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,

    
    
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,

    
    
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10

    
    
    
};




const uint8_t n_0_m[3][19]={

     0x20,0x20,0x20,0x20,0x20,0x20,0x23,0x27,
     0x26,0x26,0x26,0x27,0x23,0x20,0x20,0x20,
     0x20,0x20,0x20,
     
      0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,
     0x03,0x03,0x03,0xFF,0xFE,0x00,0x00,0x00,
     0x00,0x00,0x00,
     
     0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
     0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
     0x10,0x10,0x10

};




const uint8_t n_1_m[3][19]={

  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x27, 0x27, 0x23, 0x20, 0x20, 0x20, 0x20, 0x20, 
  0x20, 0x20, 0x20,
          

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 


  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 
             

};







const uint8_t n_1P5_m[3][19]={

    0x26, 0x26, 0x26, 0x27, 0x27, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x27, 0x27, 0x23, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20,
    
    0x3e, 0x7f, 0x63, 0xe3, 0xc3, 0x00, 0x06, 0x06, 
    0x00, 0x03, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    


    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 

};






const uint8_t n_2P5_m[3][19]={

0x26, 0x26, 0x26, 0x27, 0x27, 0x20, 0x20, 0x20, 
0x20, 0x23, 0x27, 0x26, 0x26, 0x27, 0x23, 0x20, 
0x20, 0x20, 0x20,

0x3e, 0x7f, 0x63, 0xe3, 0xc3, 0x00, 0x06, 0x06, 
0x00, 0x83, 0xc3, 0x63, 0x33, 0x1f, 0x0f, 0x00, 
0x00, 0x00, 0x00, 



0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 
};




const uint8_t n_2_m[3][19]={

    
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 
0x27, 0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,
    

        
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 
0xc3, 0x63, 0x33, 0x1f, 0x0f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
        

0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 



};











const uint8_t n_3_m[3][19]={

  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23,
 0x27, 0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x20, 
 0x20, 0x20, 0x20,
 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde,
 0xff, 0x63, 0x63, 0x07, 0x06, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 
 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
 0x10, 0x10, 0x10, 
       
        

         
         
         
         
         
};








const uint8_t n_4_m[3][19]={
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x27, 0x27, 
0x20, 0x20, 0x20, 0x27, 0x27, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,


0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
0x60, 0x60, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,


0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10



};


const uint8_t n_6_m[3][19]={

0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x27, 
0x26, 0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 
0x63, 0x63, 0x63, 0xff, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 

0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 


};










const uint8_t n_5_m[3][19]={

0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x26, 0x26, 
0x26, 0x26, 0x26, 0x27, 0x27, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,


0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 
0x63, 0x63, 0x63, 0xe3, 0xe3, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,

0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10

};





const uint8_t n_10_m[3][19]={

              
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 
0x27, 0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x27, 
0x27, 0x23, 0x20,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 
0xff, 0x03, 0x03, 0xff, 0xfe, 0x00, 0x03, 0xff, 
0xff, 0x03, 0x00, 

        
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10,  
        

};








const uint8_t n_13_m[3][19]={
  
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x27, 
0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x20, 0x27, 
0x27, 0x23, 0x20,

    
    
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xff,
0x63, 0x63, 0x07, 0x06, 0x00, 0x00, 0x03, 0xff, 
0xff, 0x03, 0x00,

    
    
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10

    
    
    
};


const uint8_t n_100_m[3][19]={

    
    0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x23, 0x27, 
    0x26, 0x27, 0x23, 0x20, 0x20, 0x27, 0x27, 0x23, 
    0x20, 0x20, 0x20,
        
    0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0xfe, 0xff, 
    0x03, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x03, 
    0x00, 0x00, 0x00, 
    
    
    
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 
};





const uint8_t n_200_m[3][19]={
  
0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x23, 0x27,
0x26, 0x27, 0x23, 0x20, 0x23, 0x27, 0x26, 0x26, 
0x27, 0x23, 0x20,

0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0xfe, 0xff, 
0x03, 0xff, 0xfe, 0x00, 0x83, 0xc3, 0x63, 0x33, 
0x1f, 0x0f, 0x00, 



0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 

    
    
    
};
const uint8_t n_150_m[3][19]={
  
    0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x26, 0x26, 
  0x26, 0x27, 0x27, 0x20, 0x20, 0x27, 0x27, 0x23, 
  0x20, 0x20, 0x20,
    
    

  
  0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0x3e, 0x7f, 
  0x63, 0xe3, 0xc3, 0x00, 0x03, 0xff, 0xff, 0x03, 
  0x00, 0x00, 0x00, 
  
      0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 
  
};



const uint8_t n_300_m[3][19]={
  
0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x23, 0x27, 
0x26, 0x27, 0x23, 0x20, 0x23, 0x27, 0x26, 0x26, 
0x27, 0x23, 0x20,

0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0xfe, 0xff, 
0x03, 0xff, 0xfe, 0x00, 0xde, 0xff, 0x63, 0x63, 
0x07, 0x06, 0x00, 



0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 
    
    
    
};




















const uint8_t n_250_m[3][19]={
  
    0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x26, 0x26, 
    0x26, 0x27, 0x27, 0x20, 0x23, 0x27, 0x26, 0x26, 
    0x27, 0x23, 0x20,
    
    0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0x3e, 0x7f, 
    0x63, 0xe3, 0xc3, 0x00, 0x83, 0xc3, 0x63, 0x33, 
    0x1f, 0x0f, 0x00,

     0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10
    

    
    
    
};







uint8_t display_n_blank(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
    if(y==1)
    {
            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
              temp = n_blank_m[0][ms];
              ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_blank_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_blank_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                 tori = temp; 
                 temp = 0xf0;        
                 ee_WriteBytes(&temp, 0x40, 1);
             }
            
            }
    }
    else if(y ==2)
    {
    
            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
              temp = n_blank_m[0][ms];
              ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_blank_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_blank_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
           
             setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                 tori = temp;
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    
    
    }

}




//==============================================================================
//uint8_t n_x_m[3][19]={0};
uint8_t (*n_x_m)[19] = NULL;
//uint8_t display_num(uint8_t y,uint8_t x, uint8_t mode)
uint8_t display_num(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

    switch(mode&0x7f)
    {
        
        case NUM_0:
        n_x_m = n_0_m;
        break;
        
        case NUM_1:
        n_x_m = n_1_m;
        break;
        
        case NUM_2:
        n_x_m = n_2_m;
        break;
        
        case NUM_3:
            n_x_m = n_3_m;
        break;
        
        case NUM_4:
            n_x_m = n_4_m;
        break;
        
        case NUM_5:
            n_x_m = n_5_m;
        break;
        
        case NUM_6:
            n_x_m = n_6_m;
        break;
        
        case NUM_10:
            n_x_m = n_10_m;
        break;
        
        case NUM_13:
            n_x_m = n_13_m;
        break;
        
        case NUM_100:
            n_x_m = n_100_m;
        break;
        
        case NUM_150:
            n_x_m = n_150_m;
        break;
        
        case NUM_200:
            n_x_m = n_200_m;
        break;
        
        case NUM_250:
            n_x_m = n_250_m;
        break;
        
        case NUM_300:
            n_x_m = n_300_m;
        break;
        
        case NUM_1P5:
            n_x_m = n_1P5_m;
        break;
        
        case NUM_2P5:
             n_x_m = n_2P5_m;
        break;
        
    }
    
    
            if((mode&0x80) == MODE_NORMAL)
            {         
         
             //setYX_LCD(5,x);
            setYX_LCD(2+y,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
               //temp = n_300_m[0][ms];
               temp = n_x_m[0][ms];
               ee_WriteBytes(&temp, 0x40, 1);
            }
            
             //setYX_LCD(6,x);
             setYX_LCD(3+y,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  //temp = n_300_m[1][ms];
                  temp = n_x_m[1][ms];
       
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              //setYX_LCD(7,x);
              setYX_LCD(4+y,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                //temp = n_300_m[2][ms];
                temp = n_x_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if((mode&0x80) == MODE_REVERSE)
            {
            
             //setYX_LCD(5,x);
             setYX_LCD(2+y,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                //temp = n_300_m[0][ms];
                temp = n_x_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(6,x);
             setYX_LCD(3+y,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  //temp = n_300_m[1][ms];
                  temp = n_x_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
               //setYX_LCD(7,x);
               setYX_LCD(4+y,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 //temp = n_300_m[2][ms];
                 temp = n_x_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}












//==============================================================================


void display_bat(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =bat_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = bat_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = bat_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = bat_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}


void display_mem(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =mem_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = mem_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = mem_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = mem_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}












void display_blank_mode_pa(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =blank_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = blank_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = blank_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = blank_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}








void display_cmode(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
          
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =c_m[0][ms];
                 
                     ee_WriteBytes(&temp, 0x40, 1);
                }

             
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = c_m[1][ms];
                
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
       
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = c_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                

                     ee_WriteBytes(&temp, 0x40, 1);
                }

         
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = c_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                
                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}











void display_drops(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =drops_m[0][ms];
                    ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drops_m[1][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = drops_m[0][ms];
                    tori = temp;
                    temp = ~temp;
                    //temp |= tori;
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drops_m[1][ms];
                     tori =temp;

                        temp = ~temp;
                        //temp |= tori;

                    
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
            
    
    
    
    
    }



}



void display_drop(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =drop_m[0][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drop_m[1][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = drop_m[0][ms];
                    tori = temp;
                    


                        temp = ~temp;
                        //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drop_m[1][ms];
                     tori =temp;
                     temp = ~temp;
                      //temp |= tori;
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
            
    
    
    
    
    }



}


//==============================================================================
//==============================================================================

const uint8_t ptna_frame[2][WIDTH_PATTERN_A]=
{
0x3f, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x40, 0x3f,

    
0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x02, 0xfc,

  
};

const uint8_t ptnd_frame[3][WIDTH_PATTERN_D]=
{
 0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x21, 0x23, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,
 
 
 
 0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0xe0, 
 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff,
 
 
 0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

  
};



const uint8_t ptne_frame[3][WIDTH_PATTERN_D]=
{
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,


0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x04, 0x06, 0x07, 0x07, 0x70, 0x88, 0x88, 0x88,
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,


0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 
0xd0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    
    
    
};









const uint8_t ptnf_frame[3][WIDTH_PATTERN_D]={
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 
    0x22, 0x21, 0x2a, 0x24, 0x22, 0x20, 0x10, 0x0f,
    
    
    0xff, 0x00, 0x00, 0x00, 0x01, 0x01, 0x1f, 0x00,
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x1c, 0x24, 0x44, 0x88, 0x10, 
    0x20, 0x40, 0x80, 0x40, 0x00, 0x00, 0x00, 0xff,
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    

    
    };



const uint8_t ptng_frame[3][WIDTH_PATTERN_D]={

   0x0f, 0x10, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x2f, 
    0x24, 0x22, 0x24, 0x2f, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x29, 0x2f, 
    0x2f, 0x29, 0x28, 0x20, 0x21, 0x23, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x23, 0xa2, 0xa3, 0xa0, 0x2b, 0xa0,
    0x2f, 0x24, 0x26, 0xa4, 0x2f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7a, 0xf9, 0xc0, 0xc0, 0xe0, 0xf0, 
    0xf0, 0xe0, 0xc0, 0xc0, 0xe0, 0xf0, 0x00, 0xff,

    
    0xc0, 0x20, 0x90, 0x10, 0x90, 0x10, 0x90, 0x10, 
    0x90, 0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,
};



const uint8_t ptnh_frame[3][WIDTH_PATTERN_D]={

0x0f, 0x10, 0x20, 0x25, 0x25, 0x27, 0x20, 0x27,
0x25, 0x27, 0x20, 0x24, 0x24, 0x27, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x26, 
0x26, 0x26, 0x26, 0x26, 0x27, 0x27, 0x10, 0x0f,


0xff, 0x00, 0x10, 0xd1, 0x51, 0x51, 0x10, 0x15, 
0x10, 0xd7, 0x12, 0x51, 0x52, 0xd7, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x60, 0x60, 0x60, 0x60, 0xff, 0xff, 0x00, 0xff,


0xc0, 0x20, 0x10, 0xd0, 0x10, 0xd0, 0x10, 0xd0, 
0x10, 0xd0, 0x10, 0x10, 0x10, 0xd0, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x20, 0xc0,





};


const uint8_t ptni_frame[3][WIDTH_PATTERN_D]={
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x24, 0x27, 0x24, 0x24, 
    0x24, 0x24, 0x24, 0x27, 0x24, 0x20, 0x10, 0x0f,
    
    
    0xff, 0x00, 0x00, 0x00, 0x00, 0x13, 0x24, 0x24, 
    0x24, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8b, 0xd3,
    0xe3, 0xd3, 0x8b, 0x07, 0x00, 0x00, 0x00, 0xff,

    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 
    0x90, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x90, 0x90, 
    0x90, 0x90, 0x90, 0x90, 0x90, 0x10, 0x20, 0xc0,

    
    
    
    };






uint8_t display_frame_abc(uint8_t y,uint8_t x, uint8_t mode)
{
    
    uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
           
                setYX_LCD(0,x);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {
                    
                    temp =ptna_frame[0][ms];
                   
                     ee_WriteBytes(&temp, 0x40, 1);
                }

               
                setYX_LCD(1,x);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = ptna_frame[1][ms];
                    
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
           
              setYX_LCD(0,x);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {

                    temp = ptna_frame[0][ms];
                    tori = temp;
                    
                    if(ms ==0 || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp = ~temp;
                        temp  |= tori;
                        temp  &= 0x3f;
                        
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = ~temp;
                        temp |= tori;
                        temp  &= 0x7f;;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp |= tori;
                        
                    }

                     ee_WriteBytes(&temp, 0x40, 1);
                }

              
                setYX_LCD(1,x);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = ptna_frame[1][ms];
                     tori =temp;
                    if(ms ==0  || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp = ~temp; 
                        temp |= tori;
                        temp  &= 0xfc;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                       
                        temp = ~temp;
                        temp |= tori;
                        temp  &= 0xfe;
                                   
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp |= tori;
                    }
                     
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
             
    
    }





}




uint8_t display_frame_de(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
     
    if (y == 1)
    {
            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnd_frame[0][ms];
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                temp = ptnd_frame[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
     
             setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                temp = ptnd_frame[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnd_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnd_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnd_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            }
    }
    else if(y == 2)
    {
      if(mode == MODE_NORMAL)
        {         
           
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
              temp = ptne_frame[0][ms];
              ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                temp = ptne_frame[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                temp = ptne_frame[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptne_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptne_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             
               setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptne_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

    }

}

//==============================================================================
uint8_t (*ptnx_frame)[WIDTH_PATTERN_D]=NULL;
uint8_t display_frame_fghi(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
     
    switch(y)
    {
        case TYPE_F:
            ptnx_frame = ptnf_frame;
            break;
            
        case TYPE_G:
            ptnx_frame = ptng_frame;
            break;  
            
        case TYPE_H:
            ptnx_frame = ptnh_frame;
            break;
        
          case TYPE_I:
              ptnx_frame = ptni_frame;
            break;
        
    }

    if(mode == MODE_NORMAL)
            {         
           
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
               temp = ptnx_frame[0][ms];
               ee_WriteBytes(&temp, 0x40, 1);
            }
            
            
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnx_frame[1][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnx_frame[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnx_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                   
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnx_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnx_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    



}






//3
//3
//7
//5
//3



//2





uint8_t clear_screen(void)
{
    
    
    uint8_t page,col;
  for(page=0;page<9;page++)  
  {
    setYX_LCD(page,0);
    write_buf[0] =0x00;
       for(col=0;col<99;col++)
        {
            ee_WriteBytes(write_buf, 0x40, 1);
        }
  }



}

void initial_work_setting(void)
{
    
    
    
}


void initial_ui_setting(void)
{
    #if 1
    display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, MODE_NORMAL);
    display_cmode(LEFT,COL_PAGE0_MDROPS,MODE_NORMAL);
    
    display_frame_abc(LEFT,COL_PAGE0_PATTERN_B, MODE_NORMAL);
    display_mem(LEFT,COL_PAGE0_MEM,MODE_NORMAL);

    display_frame_abc(LEFT,COL_PAGE0_PATTERN_C, MODE_NORMAL);
    display_bat(LEFT,COL_PAGE0_BAT,MODE_NORMAL);
    
    //------------------------------------------------------------
    
    display_frame_de(LEFT,COL_PAGE0_PATTERN_D, MODE_NORMAL);
    display_num(MIDDLE,COL_PAGE0_DN, NUM_4);
  
    
    
    display_frame_de(RIGHT,COL_PAGE0_PATTERN_E, MODE_NORMAL);
    display_num(MIDDLE,COL_PAGE0_EN, NUM_1);

    //-------------------------------------------------------------------

    display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, MODE_NORMAL);
    display_num(BOTTOM,COL_PAGE0_FN, NUM_2P5);
    
    
    display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G, MODE_NORMAL);
    display_num(BOTTOM,COL_PAGE0_GN, NUM_3);
 
#endif
    
    
    hg_op.cur_working_mode = WORK_MODE_C;//now we assume working in DROPS ;
    hg_op.cnt_target_posrst = POS_4_RST;     //len=4mm
    hg_op.needle_len = NEEDLE_LEN_4_MM;
    
    hg_op.inject_len = INJECT_LEN_1_MM;
    
    hg_op.tube_cap = TUBE_CAP_2P5_ML;
    hg_op.work_freq = DROPS_MODE_250_FREQ;
    
    hg_op.push_len = 140;//146
    
    
    
    
    
    
    
    
}








void Initial_LY096BG30(void)
{
    
i2c_CfgGpio();
  

#if 1

 LATEbits.LATE1=0;
 delay(1);//=====================

LATEbits.LATE1=1;
delay(1);

#endif

    write_buf[0]=0x21;  
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
	
    write_buf[0]=0x15;
    ee_WriteBytes(write_buf, 0x00, 1);

    write_buf[0]=0x08;
	ee_WriteBytes(write_buf, 0x00, 1);

    write_buf[0]=0x9f;
	ee_WriteBytes(write_buf, 0x00, 1);
    
    write_buf[0]=0x20;
	ee_WriteBytes(write_buf, 0x00, 1);
    
    write_buf[0]=0x05;
	ee_WriteBytes(write_buf, 0x00, 1);

    write_buf[0]=0x0c;//normal
     //write_buf[0]=0x08;//blank
   // write_buf[0]=0x0d;//reverse
	ee_WriteBytes(write_buf, 0x00, 1);
    
    clear_screen();
    initial_ui_setting();
#if 0
    display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, MODE_NORMAL);
    display_cmode(LEFT,COL_PAGE0_MDROPS,MODE_NORMAL);
    
    display_frame_abc(LEFT,COL_PAGE0_PATTERN_B, MODE_NORMAL);
    display_mem(LEFT,COL_PAGE0_MEM,MODE_NORMAL);

    display_frame_abc(LEFT,COL_PAGE0_PATTERN_C, MODE_NORMAL);
    display_bat(LEFT,COL_PAGE0_BAT,MODE_NORMAL);
    
    //------------------------------------------------------------
    
    display_frame_de(LEFT,COL_PAGE0_PATTERN_D, MODE_NORMAL);
    display_num(MIDDLE,COL_PAGE0_DN, NUM_4);
  
    
    
    display_frame_de(RIGHT,COL_PAGE0_PATTERN_E, MODE_NORMAL);
    display_num(MIDDLE,COL_PAGE0_EN, NUM_1);

    //-------------------------------------------------------------------

    display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, MODE_NORMAL);
    display_num(BOTTOM,COL_PAGE0_FN, NUM_2P5);
    
    
    display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G, MODE_NORMAL);
    display_num(BOTTOM,COL_PAGE0_GN, NUM_3);
 
#endif
    

}


//c mode
//4  6  13                 //0  1  2  3  4
//1  2  2.5  5  10         //3


//m drop
//4  6  13                // 0  1  2  3  4
//1  2  2.5  5  10        //100   150  200  250   300


//s  drop
//4  6  13                //0  1  2  3  4
//1  2  2.5  5  10        //0  1  2  3







#if 0
interface_t interface_x ={0};

uint8_t hg_interface(void)
{
    
    return 1;
}
#endif