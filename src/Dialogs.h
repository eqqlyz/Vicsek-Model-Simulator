#ifndef GETPARA_H
#define GETPARA_H

#include "DrawWindow.h"

class getParaDialog : public QDialog
{
	Q_OBJECT
public:
	getParaDialog(QWidget *parent=0);
//信号:暂时未定义
signals:
	void find_Next();
	void find_Previous();
//槽
public slots:
	void init_Flocks();
	void update_Flocks();
	void update_HasLeader();
	void update_IsGraph();

public:
	//获取参数的控件
	QLabel *disp_BirdNum;			//鸟儿的数目
	QLineEdit *edit_BirdNum;
	QLabel *disp_Radius;			//影响半径
	QLineEdit *edit_Radius;
	QLabel *disp_Yita;				//随机因子：随机拐弯角度的上界
	QLineEdit *edit_Yita;
	QLabel *disp_Velocity;			//鸟儿的速度
	QLineEdit *edit_Velocity;
	QLabel *disp_RepaintTime;		//每次更新的时间
	QLineEdit *edit_RepaintTime;
	QLabel *disp_HasLeader;			//鸟群中是否有领导
	QComboBox *edit_HasLeader;	
	QLabel *disp_IsGraph;			//是否采用图的模型
	QComboBox *edit_IsGraph;	
	
	QPushButton *init_Flock;		//控制按钮
	QPushButton *Go;
	
	//显示鸟群的画板
	DrawWindow *HuaBan;
	int HasLeader;
	int IsGraph;
};
#endif