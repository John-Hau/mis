//#include <p18cxxx.h>
//#include<pic18.h>  
#include <xc.h>
#include "Timer.h"
//#include "Ad.h"
#include "Key.h"
#include "PositionControl.h"
#include "Beep.h"
#include"MotorDrive.h"

unsigned char LastNeedleFeedback =0;
unsigned char LastInjectionFeedback =0;
unsigned char flag =0;


//void __interrupt(high_priority) ISR(void)
void __interrupt(high_priority) ISR(void)
{
  //1ms��ʱ�ж�
  unsigned char i =0;

  if(T0IE && T0IF) // ˵��127us��ʱʱ�䵽��
  {
#if 0
	if(AdSampleTaskTime)
	{
		AdSampleTaskTime--;
	}
#endif
	if(KeyScanPeriod)
	{
		KeyScanPeriod--;
	}
//λ�ü��
    i =NEEDLE_MOTOR_FEEDBACK2;
    if(LastNeedleFeedback != i)
	{
		if(NeedleRunDir)//fan
		{
			NeedleMotorCurrentPosition--;		
		}
		else
		{
			NeedleMotorCurrentPosition++;		
		}
		LastNeedleFeedback = i;
	}

    i =INJECTION_MOTOR_FEEDBACK2;
    if(LastInjectionFeedback != i)
	{
		InjectionMotorCurrentPosition++;
		LastInjectionFeedback = i;
	}

	//����״̬	
	if(StartWorkFlag ==1)//��������״̬
	{
		switch(CurrentWorkPara.InjectMode)
		{
			case CONTINUE_WORK_MODE:
					
					if(ContinueWorkState ==0)//����������һ�� �������
					{
						NeedleRunDir =0;
						//NeedleMotorForwardRun();			
						CLEAR_L298N_INPUT3_PIN;    			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						if((NeedleMotorCurrentPosition > NeedleMotorAimPosition) ||(NeedleMotorCurrentPosition == NeedleMotorAimPosition))
						{
							//NeedleMotorFastStop();
							SET_L298N_INPUT3_PIN; 			
							SET_L298N_INPUT4_PIN;  			
							SET_L298N_B_ENABLE_PIN;  		

							ContinueWorkState =1;
						}
					}
					else if(ContinueWorkState == 1)
					{
						//InjectionMotorForwardRun();
						SET_L298N_INPUT1_PIN;
						CLEAR_L298N_INPUT2_PIN;
						SET_L298N_A_ENABLE_PIN;
 
						if((InjectionMotorCurrentPosition > InjectionMotorAimPosition)||(InjectionMotorCurrentPosition == InjectionMotorAimPosition))
						{
							//InjectionMotorFastStop();
							SET_L298N_INPUT1_PIN;
							SET_L298N_INPUT2_PIN;
							SET_L298N_A_ENABLE_PIN;
  
							ContinueWorkState =2;
						}
					}
					else if(ContinueWorkState == 2)
					{
						NeedleRunDir =1;
				
						if((NeedleMotorCurrentPosition <  NeedleInitPosition)||(NeedleMotorCurrentPosition ==  NeedleInitPosition))
						{
							//NeedleMotorFastStop();
							SET_L298N_INPUT3_PIN; 			
							SET_L298N_INPUT4_PIN;  			
							SET_L298N_B_ENABLE_PIN;  		
 
							ContinueWorkState =3;
						}
						else
						{
							//NeedleMotorReverseRun();	
							SET_L298N_INPUT3_PIN; 			 			
							CLEAR_L298N_INPUT4_PIN; 
							SET_L298N_B_ENABLE_PIN;  		
		
						}			
					}
					else if(ContinueWorkState ==3)
					{
						ContinueWorkState =3;
						if(!ContinueWorkTimeCount)//��������ʱ�䵽
						{
							ContinueWorkTimeCount =ContinueWorkTimePeriod;
							ContinueWorkState =0;
							InjectionMotorAimPosition =InjectionMotorCurrentPosition + InjectionStepMotorStepPulseNum;//
						}
					}
					else
					{
				
					}
					if(ContinueWorkTimeCount)
					{
						ContinueWorkTimeCount--;					
					}
			
			break;	

			case MICROSCALE_WORK_MODE:
		
			break;
	
			default:

			break;
	
		}
	}
	else  //δ����������ť
	{
		//��ʼ��
		if(!NeedleMotorFindZeroPosFlag)//��ʼ���������
		{
			if(NEEDLE_MOTOR_LI_POS_PIN ==0 )//��������λ����	
			{
				//if(flag ==0)
				{
					//GIE=0;  // ������������Ҫ ���жϹ�
					NeedleMotorCurrentPosition =0;
					flag =1;
					//GIE=1;  // ������������Ҫ ���жϿ�
					//NeedleMotorForwardRun();//�����ж����ظ����ú�������Ϊ����չ��			
					CLEAR_L298N_INPUT3_PIN;    			
					SET_L298N_INPUT4_PIN;  			 
					SET_L298N_B_ENABLE_PIN;

					if(CurrentWorkPara.NeedleLength ==4)
					{
						NeedleInitPosition =NEEDLE_LENGTH_4MM_ZERO_PULSE_NUM;
						NeedleMotorAimPosition =NeedleInitPosition;
					}
					else if(CurrentWorkPara.NeedleLength ==6)
					{
						NeedleInitPosition =NEEDLE_LENGTH_6MM_ZERO_PULSE_NUM;
						NeedleMotorAimPosition =NeedleInitPosition;
					}
					else if(CurrentWorkPara.NeedleLength ==13)
					{
						NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
						NeedleMotorAimPosition =NeedleInitPosition;
					}
					else
					{
						NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
						NeedleMotorAimPosition =NeedleInitPosition;
					}  		 
	
				}
	
			}
			else
			{
				if(flag ==1)
				{
					if((NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition))
					{
						//NeedleMotorFastStop();//�����ж����ظ����ú�������Ϊ����չ��
						SET_L298N_INPUT3_PIN; 			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						NeedleMotorFindZeroPosFlag =1;//��ճ�ʼ����־
						flag =0;
					}
				}
				else
				{
					//NeedleMotorReverseRun();////�����ж����ظ����ú�������Ϊ����չ��
					SET_L298N_INPUT3_PIN; 			  			
					CLEAR_L298N_INPUT4_PIN; 
					SET_L298N_B_ENABLE_PIN;  		
		
					flag =0;				
				}

			}	
		}
		else
		{
			//NeedleMotorFastStop();
			SET_L298N_INPUT3_PIN; 			
			SET_L298N_INPUT4_PIN;  			
			SET_L298N_B_ENABLE_PIN;
			//InjectionMotorFastStop();
			SET_L298N_INPUT1_PIN;
			SET_L298N_INPUT2_PIN;
			SET_L298N_A_ENABLE_PIN; 		
		}
 
	}



  }
    T0IF=0; // ��ձ�־λ��ʹCPU����ȷ��Ӧ�´��ж�
} 

void TimerInit(void)
{
	T0CS=0; // ѡ��CLKOUT�ź�Ϊʱ��Դ
	PSA=0; // Ԥ��Ƶ����TIMER0��
	T0PS2=0;
	T0PS1=0;
	T0PS0=0; // ��Ƶ��Ϊ1:8��FOSC/4/2=2
	T08BIT =1;//����Ϊ8λģʽ 0.5us*255 =127us  
	T0IF=0; // Timer0�жϱ�־λ���  
	T0IE=1; // Timer0�ж�ʹ��λ��λ������Timer0�ж�
	GIE=1;  // ���жϴ�
	TMR0=0; // Timer0����ֵ�Ĵ�������  
}