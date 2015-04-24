#ifndef BIRD_H
#define BIRD_H

#include<stdlib.h>
#include<math.h>
#include<QTime>

#define ISLEADER	1
#define NOTLEADER	-1

class Bird 
{
public:
	//����С���˶�����������
	double coord_x;
	double coord_y;
	double oritation;	//��Χ��0~360`
	int isLeader;	//�����жϸ����Ƿ����쵼
	int isOnThePlane;	//��¼��С���Ƿ��ڻ�������
	QTime t;
	
public:
	Bird(double low_x,double up_x,double low_y,double up_y){
		Random_init(low_x,up_x,low_y,up_y);
	}
	
	Bird(){}
	
	void Random_init(double low_x,double up_x,double low_y,double up_y){
		//��ʼ����С�������λ�úͷ���
		//t=QTime::currentTime();
		//qsrand(t.msec());
		coord_x=((qrand()+0.0)/(RAND_MAX+0.0))*(up_x-low_x)+low_x;
		coord_y=((qrand()+0.0)/(RAND_MAX+0.0))*(up_y-low_y)+low_y;
		oritation=((qrand()+0.0)/(RAND_MAX+0.0))*360;	//����QT�ĽǶ�
	}
};
#endif