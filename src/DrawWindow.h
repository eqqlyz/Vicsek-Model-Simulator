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

//���弸�����巶Χ�Ĳ���,С����˶���Χ��[10,520]*[10,520]֮�ڣ�
#define LOW_X 		10
#define UP_X 		510 
#define LOW_Y 		10
#define UP_Y 		510
#define DET			20

#define MY_PI		3.1415926


#define CORNER_X	300
#define CORNER_Y	150	

//�ж��Ƿ����쵼
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
		//������Ⱥ����������ͼ
		plotter.setWindowTitle(QObject::tr("Vicsek Model SubGraph Number Plotter"));
		plotter.setCurveData(GroupNumber);
		plotter.setting.setPlotter(0,BirdNum,0,myTimer);	//���û�ͼ��ܵı߽�
	}
protected:
	void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);	//��ʱ��
public:
	void startDrawing();
	
public:
	//��ͼ��Ϊ���Ƿ���Ʊ�
	void drawBirds(QPainter *gp);
	void drawBirds_withGraph(QPainter *gp);
	void drawBirds_withoutGraph(QPainter *gp);
	//���Ʒ�Ϊ���Ƿ����쵼
	void control_withoutLeader();	//��������Ϳ����������ӵ��˶��ķ���:���쵼
	void control_withLeader();	//��������Ϳ����������ӵ��˶��ķ���:���쵼
	//�����ڽӾ���ķ���
	void update_Neighbor();
	//����Ⱥ�����ķ���
	int subGraphNumber();
	void dfs(int start);
	//�������ߵķ���
	void drawPlotter();
public:
	//��ʱ��
	int myTimerID;
	QTime t;
	//�����ȡ�Ĳ���
	int BirdNum;
	double Radius;	//�ж��Ƿ�Ϊ�ھӵİ뾶
	double Velocity;//����˶��ٶ�
	double Yita;	//����������Ƕȵ��Ͻ�
	double Dett;	//�����ϵ���ĸ���ʱ��
	int HasLeader;	//ָʾ��Ⱥ���Ƿ����쵼
	int IsGraph;	//ֻ���Ƿ����ͼģ��
	//��Ⱥ
	Bird *flocks;
	int spanAngle;	//����pie�Ŀ�Ƚ�;startAngle��oritationָ��
	double rectWidth;
	double rectHeight;
	QRectF *hawk;
	//�ڽӾ����ж��Ƿ�Ϊ�ھӵľ���
	int **neighbor;
	//��������->��¼ĳ�������Ƿ񱻷���: 0,δ���ʣ�1,���ʡ�
	char *visited;
	//������Ⱥ�����Ļ���
	Plotter plotter;
	//��¼��Ⱥ�ĸ���
	QVector<QPointF> GroupNumber;
	//ʱ����������䵱x��
	int myTimer;
};

#endif