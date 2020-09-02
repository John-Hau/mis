#ifndef DISPLAY_H
#define DISPLAY_H

extern unsigned char DisplayTaskTime;

extern void DisplayTask(void);

#define DISPLAY_TASK_PERIOD  100  //100ms

#define INJECT_MODE_DISPLAY_X   1  		//ע��ģʽX����λ��
#define INJECT_MODE_DISPLAY_Y   1  		//ע��ģʽY����λ��

#define DUMP_ENERGY_DISPLAY_X   87  		//ʣ�����X����λ��
#define DUMP_ENERGY_DISPLAY_Y   2  		//ʣ�����Y����λ��

#define INJECT_TYPE_DISPLAY_X   	25  	//ע�������� X����λ��
#define INJECT_TYPE_DISPLAY_Y   	71  	//ע�������� Y����λ��

#define NEEDLE_LENGTH_DISPLAY_X   	25  	//��ͷ���� X����λ��
#define NEEDLE_LENGTH_DISPLAY_Y   	39  	//��ͷ���� Y����λ��

#define INJECT_DEPTH_DISPLAY_X   	87  	//ע����� X����λ��
#define INJECT_DEPTH_DISPLAY_Y   	39  	//ע����� Y����λ��

#define VARIABLE_DISPLAY_X   		88  	//���� X����λ��
#define VARIABLE_DISPLAY_Y   		71  	//���� Y����λ��

#endif