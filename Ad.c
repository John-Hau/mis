#include <p18cxxx.h>
#include "Ad.h"

unsigned char AdSampleTaskTime =0;

unsigned int InjectionMotorAdAverageValue =0;//ע����Adƽ��ֵ
unsigned int NeedleMotorAdAverageValue =0;
unsigned int BatteryVoltAdAverageValue =0;

unsigned int InJectionCrrentAdArray[ARRAY_LENGTH]={0,0,0,0,0};//ע��������Adֵ
unsigned int NeedleCrrentAdArray[ARRAY_LENGTH]={0,0,0,0,0};//ע�����������Adֵ
unsigned int BatteryAdArray[ARRAY_LENGTH]={0,0,0,0,0};//��ص�ѹAdֵ

//volatile unsigned int BatteryVolt =0;//��ص�ѹ
unsigned int InjectionMotorCurrent =0;//ע��������
unsigned int NeedleMotorCurrent =0;//����������

void EnableAd(void)
{
	ADCON0 =ADCON0 | 0x01;
}

void CloseAd(void)
{
	ADCON0 =ADCON0 & 0xfe;
}

void SetAdChanel(unsigned char ch)
{
	ADCON0 =(ch <<2) | (ADCON0 & 0x3);
}

void StartAdConvert(void)
{
	ADCON0 =ADCON0 | 0x01;
}


unsigned int StartAndReadAdValue(unsigned char ch)
{
	unsigned int delay =1000;
	unsigned int value =0; 

	SetAdChanel(ch);
	StartAdConvert();
	while(delay-- && (ADCON0 & 0x2));
	
	value=((unsigned int)ADRESH <<2)|value; 
		
	return(value);	
}

//*pData ָ��Adֵ����  *pPar����ֵ����
void CalAdAverage(unsigned int *pData,unsigned int *pPar)
{
	unsigned char Index =0;
	unsigned long aver =0;
	unsigned long sum =0;
	
	for(Index = 0;Index <ARRAY_LENGTH ;Index++)
	{
		sum += *(pData + Index );
 	}		

	*pPar = (unsigned int)((unsigned long)sum/ARRAY_LENGTH);	
}

//value �����ӵ���ֵ  pData���ݻ�����

void AddDataToBuff(unsigned int *pData,unsigned int value)
{
	unsigned char Index =0;
	
	for(Index = ARRAY_LENGTH-1;Index > 0;Index--)
	{
		*(pData+Index) =*(pData+Index-1);
	}	
	*pData = value;
}

//����Ϊ��ѯ��ʽ
void ADInit(void)
{
	unsigned char delay=100;

	ADCON0=0x01; /*ѡ��RA0ͨ����AD ģ��ʹ��*/
  	ADCON1=0x0c; /*�ο���ѹΪϵͳVDD��GND������ͨ����Ϊģ������*/ 
    ADCON2=0x09; /*ת���������룬AD �ɼ�ʱ��=2TAD��ϵͳʱ��Fosc/8*/	
  	while(delay--); /*��ʱn����������*/
    EnableAd();
}
void CalVoltValue(void)
{
	BatteryVolt =(unsigned long)VOLT_AD_1_TO_VOLT *BatteryVoltAdAverageValue/10;
}
void InJectionCrrentValue(void)
{
	InjectionMotorCurrent =(unsigned long)INJECTION_MOTOR_AD_1_TO_CURRENT *InjectionMotorAdAverageValue/10;
}

void NeedleCrrentValue(void)
{
	NeedleMotorCurrent =(unsigned long)NEEDLE_MOTOR_AD_1_TO_CURRENT *NeedleMotorAdAverageValue/10;
}

void AdSampleTask(void)
{
	static unsigned char counter =0;
	unsigned int value =0;
	if(!AdSampleTaskTime)
	{
		AdSampleTaskTime =AD_SAMPLE_PERIOD;
		switch(counter)
		{
			case 0:
					value = StartAndReadAdValue(INJECTION_MOTOR_CHANNEL);
					AddDataToBuff(&InJectionCrrentAdArray[0],value);
					CalAdAverage(&InJectionCrrentAdArray[0],&InjectionMotorAdAverageValue);
					InJectionCrrentValue();
					break;
			case 1:
					value = StartAndReadAdValue(NEEDLE_MOTOR_CHANNEL);
					AddDataToBuff(&NeedleCrrentAdArray[0],value);
					CalAdAverage(&NeedleCrrentAdArray[0],&NeedleMotorAdAverageValue);
					NeedleCrrentValue();
					break;
			case 2:
					value = StartAndReadAdValue(BAT_VOLT_CHANNEL);
					AddDataToBuff(&BatteryAdArray[0],value);
					CalAdAverage(&BatteryAdArray[0],&BatteryVoltAdAverageValue);
					CalVoltValue();
					break;
			case 3:
						
					break;
			default:

					break;
	
		}
		if(++counter > 4)
		{
			counter =0;
		}
	}
}




