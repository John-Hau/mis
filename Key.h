#ifndef KEY_H
#define KEY_H

//��������
#define ON_OFF_BUTTON_PIN 					PORTBbits.RB4  		/*���ػ�����*/
#define UP_BUTTON_PIN  						PORTDbits.RD4  		/*���ϵ��ڰ���*/
#define DOWN_BUTTON_PIN  					PORTDbits.RD7  		/*���µ��ڰ���*/
#define COMFIRM_BUTTON_PIN  				PORTBbits.RB3  		/*ȷ�ϰ���*/

#define START_WORK_BUTTON_PIN  				PORTBbits.RB5  		/*�˹���ģʽ�¿�ʼ��������*/
	 
#define KEY_SCAN_PERIOD_CONST 10 //ms

extern unsigned char KeyScanPeriod;

typedef struct  
{
	unsigned char NewValue;				//
	unsigned char OldValue;				//
	unsigned char SendValue;			//
	unsigned char SendValueChangeFlag;	//	
	unsigned char FiterTimesCount;		//�˲���������
	unsigned char FiterTimes;			//�˲�����

}KeyType;

extern KeyType OnOffKey,UpKey,DownKey,ConfirmKey,StartInjectKey;

extern void KEY_Init(void);//IO��ʼ��
extern void KEY_Scan(void);	
extern void KeyFuction(void);


#endif