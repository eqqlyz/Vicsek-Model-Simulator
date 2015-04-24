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
	//定义小鸟运动的三个参数
	double coord_x;
	double coord_y;
	double oritation;	//范围：0~360`
	int isLeader;	//用来判断该鸟是否是领导
	int isOnThePlane;	//记录该小鸟是否在画布上面
	QTime t;
	
public:
	Bird(double low_x,double up_x,double low_y,double up_y){
		Random_init(low_x,up_x,low_y,up_y);
	}
	
	Bird(){}
	
	void Random_init(double low_x,double up_x,double low_y,double up_y){
		//初始化该小鸟的坐标位置和方向
		//t=QTime::currentTime();
		//qsrand(t.msec());
		coord_x=((qrand()+0.0)/(RAND_MAX+0.0))*(up_x-low_x)+low_x;
		coord_y=((qrand()+0.0)/(RAND_MAX+0.0))*(up_y-low_y)+low_y;
		oritation=((qrand()+0.0)/(RAND_MAX+0.0))*360;	//采用QT的角度
	}
};
#endif