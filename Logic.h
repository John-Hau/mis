#ifndef LOGIC_H
#define LOGIC_H

typedef struct 
{
	unsigned char InjectMode;//ע��ģʽ
    unsigned char InjectType;//ע��������
	unsigned char NeedleLength;//��ͷ����
	unsigned char InjectDepth;//��ͷ����
	unsigned char Variable;//ÿ�ֲ����¶�Ӧ���岻ͬ ע��������ע��Ƶ��
}WorkParaType;

extern WorkParaType CurrentWorkPara;


#endif