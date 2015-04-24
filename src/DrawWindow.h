#ifndef DRAW_WIND_H
#define DRAW_WIND_H

#include<QWidget>
#include<QPainter>
#include<QImage>
#include<QPointF>
#include<QVector>
#include<QRectF>
#include<QTimer>
#include<math.h>

#include<QDialog>
#include<QMainWindow>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMessageBox>

#include "Bird.h"
#include "plotter.h"

//定义几个画板范围的参数,小鸟的运动范围在[10,520]*[10,520]之内！
#define LOW_X 		10
#define UP_X 		510 
#define LOW_Y 		10
#define UP_Y 		510
#define DET			20

#define MY_PI		3.1415926


#define CORNER_X	300
#define CORNER_Y	150	

//判断是否有领导
#define YES 	1
#define NO		0
#define DEFAULT	-1

class DrawWindow : public QWidget{
	Q_OBJECT
public:
	DrawWindow(){
		setFixedSize(DET+UP_X,DET+UP_Y);
		move(CORNER_X,CORNER_Y);
		setWindowTitle("Vicsek Model Presentation");
		rectWidth=40;
		rectHeight=30;
		spanAngle=30*16;
		hawk=new QRectF();
		//绘制子群个数的曲线图
		plotter.setWindowTitle(QObject::tr("Vicsek Model SubGraph Number Plotter"));
		plotter.setCurveData(GroupNumber);
		plotter.setting.setPlotter(0,BirdNum,0,myTimer);	//设置绘图框架的边界
	}
protected:
	void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);	//定时器
public:
	void startDrawing();
	
public:
	//绘图分为：是否绘制边
	void drawBirds(QPainter *gp);
	void drawBirds_withGraph(QPainter *gp);
	void drawBirds_withoutGraph(QPainter *gp);
	//控制分为：是否有领导
	void control_withoutLeader();	//用来计算和控制所有粒子的运动的方法:无领导
	void control_withLeader();	//用来计算和控制所有粒子的运动的方法:有领导
	//更新邻接矩阵的方法
	void update_Neighbor();
	//求子群个数的方法
	int subGraphNumber();
	void dfs(int start);
	//绘制曲线的方法
	void drawPlotter();
public:
	//计时器
	int myTimerID;
	QTime t;
	//保存获取的参数
	int BirdNum;
	double Radius;	//判断是否为邻居的半径
	double Velocity;//鸟的运动速度
	double Yita;	//鸟的随机拐弯角度的上界
	double Dett;	//画板上的鸟的更新时间
	int HasLeader;	//指示鸟群中是否有领导
	int IsGraph;	//只是是否采用图模型
	//鸟群
	Bird *flocks;
	int spanAngle;	//绘制pie的跨度角;startAngle由oritation指定
	double rectWidth;
	double rectHeight;
	QRectF *hawk;
	//邻接矩阵：判断是否为邻居的矩阵
	int **neighbor;
	//访问数组->记录某个顶点是否被访问: 0,未访问；1,访问。
	char *visited;
	//绘制子群个数的画板
	Plotter plotter;
	//记录子群的个数
	QVector<QPointF> GroupNumber;
	//时间计数器：充当x轴
	int myTimer;
};

#endif