#include <p18cxxx.h>
#include <xc.h>
#include "PositionControl.h"

volatile unsigned int InjectionMotorCurrentPosition =0,InjectionMotorAimPosition =0;	//ע����λ��
volatile int NeedleMotorCurrentPosition =0,NeedleMotorAimPosition =0;		//ע�������λ��
volatile unsigned int NeedleInitPosition =0;		//ע�������λ��

unsigned int InjectDepthNeedPulseNum=0;//��ע�������Ҫ������
unsigned int InjectAmountNeedPulseNum=0;//����ע������Ҫ������

unsigned char NeedleMotorFindZeroPosFlag =0;//0:��������  1:�Ѿ��ҹ�ԭ��λ�� ON->OFF���� �ı��������������

unsigned int  ContinueWorkTimePeriod =0;
unsigned int  ContinueWorkTimeCount =0;
unsigned char NeedleRunDir =0;//0 �� 1����
unsigned char StartWorkFlag =0,ContinueWorkState =0;
unsigned int  InjectionStepMotorStepPulseNum =0;
unsigned int InjectionStepMotorStepPulseMaxNum =0;
WorkParaType CurrentWorkPara;


#if 0
void NeedleFindZeroPosFun(void)
{
	static unsigned char flag =0;//��ʼ���׶� 0���������е���λ 1���������е�Ŀ��λ��
	//��ʼ��
	if(!NeedleMotorFindZeroPosFlag)//��ʼ���������
	{
		if(NEEDLE_MOTOR_LI_POS_PIN ==0)//��������λ����	
		{
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
			if(flag ==0)
			{
				//GIE=0;  // ������������Ҫ ���жϹ�
				NeedleMotorCurrentPosition =0;
				flag =1;
				//GIE=1;  // ������������Ҫ ���жϿ�
				//NeedleMotorForwardRun();//�����ж����ظ����ú�������Ϊ����չ��			
				CLEAR_L298N_INPUT3_PIN;    			
				SET_L298N_INPUT4_PIN;  			 
				SET_L298N_B_ENABLE_PIN;  		 

			}
			else
			{
				if(NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition)
				{
					//NeedleMotorFastStop();//�����ж����ظ����ú�������Ϊ����չ��
					SET_L298N_INPUT3_PIN; 			
					SET_L298N_INPUT4_PIN;  			
					SET_L298N_B_ENABLE_PIN;  		
					NeedleMotorFindZeroPosFlag =0;//��ճ�ʼ����־
				}
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
#endif


//ÿ��������8�η�������
void CalContinueWorkTimePeriod(void)
{
	//����1��������ע����ٴμ���  ��������ʱ���жϸ��� 127us����
	//60 000 000(us)/127(us)/CurrentWorkPara.Variable; 
	ContinueWorkTimePeriod =472441/CurrentWorkPara.Variable; 
}

//������������ģʽעҺ�������ǰ����
void CalContinueWorkModeInjectionStepPulseAndMaxPuse(void)
{
	if(INJECTION_1_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_1_ML_LENGTH;
		InjectionStepMotorStepPulseNum =500;//������Ҫ��д���㹫ʽ
	}
	else if(INJECTION_2_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_2_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//������Ҫ��д���㹫ʽ	
	}
	else if(INJECTION_2_5_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_2_5_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//������Ҫ��д���㹫ʽ	
	}
	else if(INJECTION_5_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_5_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//������Ҫ��д���㹫ʽ	
	}
	else if(INJECTION_10_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_10_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//������Ҫ��д���㹫ʽ	
	}
	else
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_1_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//������Ҫ��д���㹫ʽ
	}
}
//����ģʽ��57λĿǰ�趨���ƣ��������ʵ����������ר�ú�����������ģʽ�µ��β�����
#if 0
void ContinueMode(void)
{
	static unsigned char flag =0;//��ʼ���׶� 0���������е���λ 1���������е�Ŀ��λ��
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
			if(NEEDLE_MOTOR_LI_POS_PIN ==0)//��������λ����	
			{
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
				if(flag ==0)
				{
					//GIE=0;  // ������������Ҫ ���жϹ�
					NeedleMotorCurrentPosition =0;
					flag =1;
					//GIE=1;  // ������������Ҫ ���жϿ�
					//NeedleMotorForwardRun();//�����ж����ظ����ú�������Ϊ����չ��			
					CLEAR_L298N_INPUT3_PIN;    			
					SET_L298N_INPUT4_PIN;  			 
					SET_L298N_B_ENABLE_PIN;  		 
	
				}
				else
				{
					if(NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition)
					{
						//NeedleMotorFastStop();//�����ж����ظ����ú�������Ϊ����չ��
						SET_L298N_INPUT3_PIN; 			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						NeedleMotorFindZeroPosFlag =0;//��ճ�ʼ����־
					}
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
#endif
void InJectionOnceRunPulseCal(void)
{
	
}
void NeedleOnceRunPulseCal(void)
{
	
}

void MotorRunControl(void)
{

}
void PositionCheckInit(void)
{
	DDRCbits.RC0  =1;	//Needle
	DDRBbits.RB2  =1;	//

	DDRAbits.RA4  =1;	//Injection
	DDRDbits.RD1  =1;	//

	InjectionMotorCurrentPosition =0;
	InjectionMotorAimPosition =0;
	NeedleMotorCurrentPosition =0;
	NeedleInitPosition =0;		//ע�������λ��
	NeedleMotorAimPosition =0 + NeedleInitPosition;		//ע�������λ��
	
	CurrentWorkPara.InjectMode =CONTINUE_WORK_MODE;
	CurrentWorkPara.InjectType =INJECTION_1_ML_TYPE;
	CurrentWorkPara.NeedleLength =INJECTION_LENGTH_4MM;
	CurrentWorkPara.InjectDepth =1;//1MM
	CurrentWorkPara.Variable =100;

	CalContinueWorkTimePeriod();
	CalContinueWorkModeInjectionStepPulseAndMaxPuse();

}