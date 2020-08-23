#ifndef AD_H
#define AD_H

#define INJECTION_MOTOR_CHANNEL 	0
#define NEEDLE_MOTOR_CHANNEL 		1
#define BAT_VOLT_CHANNEL 			2

#define ARRAY_LENGTH 5

extern void ADInit(void);
extern void EnableAd(void);
extern void CloseAd(void);
extern void AdSampleTask(void);

extern unsigned int InjectionMotorAdAverageValue ;//ע����Adƽ��ֵ
extern unsigned int NeedleMotorAdAverageValue ;//ע�������Adƽ��ֵ
extern unsigned int BatteryVoltAdAverageValue ;//��ص�ѹ


#define AD_SAMPLE_PERIOD 2  //1ms

#define INJECTION_MOTOR_PROTECT_CURRENT 	1000  //mA
#define NEEDLE_MOTOR_PROTECT_CURRENT 		1000  //mA

extern unsigned char AdSampleTaskTime;

#define VOLT_AD_1_TO_VOLT  					88  //8.837  //ÿ��ADֵ��Ӧ8.837mv ����10��
#define INJECTION_MOTOR_AD_1_TO_CURRENT  	10  //1AD-1.03889ma   ����10��
#define NEEDLE_MOTOR_AD_1_TO_CURRENT  		10  //1AD-1.03889ma   ����10��

//extern volatile unsigned int BatteryVolt;//��ص�ѹ
extern unsigned int InjectionMotorCurrent;//ע��������
extern unsigned int NeedleMotorCurrent;//����������

#endif