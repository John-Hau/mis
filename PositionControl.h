
#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H

#define NEEDLE_MOTOR_FEEDBACK1 (PORTCbits.RC0)
#define NEEDLE_MOTOR_FEEDBACK2 (PORTBbits.RB2)

#define INJECTION_MOTOR_FEEDBACK1 (PORTAbits.RA4)
#define INJECTION_MOTOR_FEEDBACK2 (PORTDbits.RD1)

//Needle Motor: 1 Pulse = (15.783/������ٱ�*���һȦ���������) mm
//15.783 mm �ⲿ�����ת1Ȧ�ݸ��߹��ľ���
//��41:1
#define NEEDLE_ONE_PULSE_TO_MM							24	//1�������Ӧum

#define NEEDLE_LENGTH_4MM_ZERO_PULSE_NUM				491				
#define NEEDLE_LENGTH_6MM_ZERO_PULSE_NUM			    408	
#define NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM			    116	

//�볤��
#define INJECTION_LENGTH_4MM								0 //4MM
#define INJECTION_LENGTH_6MM								1 //6MM
#define INJECTION_LENGTH_13MM								2 //14MM

//Injection Motor:1 Pulse = (�ݾ�/���ⲿ���ٱ�*������ٱȣ�*���һȦ���������) mm
//15.783 mm �ⲿ�����ת1Ȧ�ݸ��߹��ľ���
//עҺ�����22:1
#define INJECTION_ONE_PULSE_TO_MM						3	//1�������Ӧum��

#define INJECTION_1_ML_TYPE								0			//1mlע����
#define INJECTION_2_ML_TYPE								1			//2mlע����
#define INJECTION_2_5_ML_TYPE							2			//2.5mlע��
#define INJECTION_5_ML_TYPE								3			//5mlע����
#define INJECTION_10_ML_TYPE							4			//10mlע����


#define INJECTION_1_ML_LENGTH							57639			//1mlע������Ч���� um
#define INJECTION_2_ML_LENGTH							32004			//2mlע������Ч���� um
#define INJECTION_2_5_ML_LENGTH							40005			//2.5mlע������Ч���� um
#define INJECTION_5_ML_LENGTH							41005			//5mlע������Ч���� um
#define INJECTION_10_ML_LENGTH							57505			//10mlע������Ч���� um

//������й���ģʽ ���������
#define CONTINUE_WORK_MODE								0				//��������ģʽ
#define MICROSCALE_WORK_MODE							1				//��������ģʽ



typedef struct 
{
	unsigned char InjectMode;//ע��ģʽ
    unsigned char InjectType;//ע��������
	unsigned char NeedleLength;//��ͷ����
	unsigned char InjectDepth;//��ͷ����
	unsigned char Variable;//ÿ�ֲ����¶�Ӧ���岻ͬ ע��������ע��Ƶ��
}WorkParaType;

extern WorkParaType CurrentWorkPara;

extern volatile unsigned int InjectionMotorCurrentPosition,InjectionMotorAimPosition;	//ע����λ��
extern volatile  int NeedleMotorCurrentPosition,NeedleMotorAimPosition;		//ע�������λ��
extern volatile unsigned int NeedleInitPosition;
extern unsigned char NeedleMotorFindZeroPosFlag;

extern unsigned int  ContinueWorkTimePeriod ;
extern unsigned int  ContinueWorkTimeCount;
extern unsigned char NeedleRunDir;
extern unsigned char StartWorkFlag,ContinueWorkState ;
extern unsigned int  InjectionStepMotorStepPulseNum;
extern unsigned int InjectionStepMotorStepPulseMaxNum ;


extern void PositionCheckInit(void);
extern void NeedleFindZeroPosFun(void);
extern void CalContinueWorkTimePeriod(void);


#endif