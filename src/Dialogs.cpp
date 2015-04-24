#include <QtGui>
#include <iostream>
#include "Dialogs.h"

getParaDialog::getParaDialog(QWidget *parent)
	:QDialog(parent){
	//鸟的数目
	disp_BirdNum=new QLabel(tr("Particle Number"));
	disp_BirdNum->setFixedWidth(110);
	edit_BirdNum=new QLineEdit;
	edit_BirdNum->setFixedWidth(110);
	disp_BirdNum->setBuddy(edit_BirdNum);
	//鸟的视觉半径
	disp_Radius=new QLabel(tr("View Radius"));
	disp_Radius->setFixedWidth(110);
	edit_Radius=new QLineEdit;
	edit_Radius->setFixedWidth(110);
	disp_Radius->setBuddy(edit_Radius);
	//鸟的飞行速度
	disp_Velocity=new QLabel(tr("Particle Velocity"));
	disp_Velocity->setFixedWidth(110);
	edit_Velocity=new QLineEdit;
	edit_Velocity->setFixedWidth(110);
	disp_Velocity->setBuddy(edit_Velocity);
	//鸟的随机拐弯角度上界
	disp_Yita=new QLabel(tr("Random direction"));
	disp_Yita->setFixedWidth(110);
	edit_Yita=new QLineEdit;
	edit_Yita->setFixedWidth(110);
	disp_Yita->setBuddy(edit_Yita);
	//画板更新时间
	disp_RepaintTime=new QLabel(tr("Update Time"));
	disp_RepaintTime->setFixedWidth(110);
	edit_RepaintTime=new QLineEdit;
	edit_RepaintTime->setFixedWidth(110);
	disp_RepaintTime->setBuddy(edit_RepaintTime);
	//是否有领导
	disp_HasLeader=new QLabel(tr("Has Leader or not"));
	disp_HasLeader->setFixedWidth(110);
	edit_HasLeader=new QComboBox;
	edit_HasLeader->addItem(tr("Default"));
	edit_HasLeader->addItem(tr("Yes"));
	edit_HasLeader->addItem(tr("No"));
	edit_HasLeader->setFixedWidth(110);
	disp_HasLeader->setBuddy(edit_HasLeader);	
	//是否采用图模型
	disp_IsGraph=new QLabel(tr("Graph or not"));
	disp_IsGraph->setFixedWidth(110);
	edit_IsGraph=new QComboBox;
	edit_IsGraph->addItem(tr("Default"));
	edit_IsGraph->addItem(tr("Use graph"));
	edit_IsGraph->addItem(tr("No graph"));
	edit_IsGraph->setFixedWidth(110);
	disp_IsGraph->setBuddy(edit_IsGraph);
	//按键
	init_Flock=new QPushButton(tr("Initiation"));
	Go=new QPushButton(tr("Go"));
	//事件响应函数
	connect(edit_HasLeader, SIGNAL(currentIndexChanged(int)),this, SLOT(update_HasLeader()));
	connect(edit_IsGraph,SIGNAL(currentIndexChanged(int)),this,SLOT(update_IsGraph()));
	connect(init_Flock,SIGNAL(clicked()),this,SLOT(init_Flocks()));
	connect(Go,SIGNAL(clicked()),this,SLOT(update_Flocks()));
	//控件布局
	QHBoxLayout *H_layout1=new QHBoxLayout;
	H_layout1->addWidget(disp_BirdNum);
	H_layout1->addWidget(edit_BirdNum);

	QHBoxLayout *H_layout2=new QHBoxLayout;
	H_layout2->addWidget(disp_Radius);
	H_layout2->addWidget(edit_Radius);
	
	QHBoxLayout *H_layout3=new QHBoxLayout;
	H_layout3->addWidget(disp_Velocity);
	H_layout3->addWidget(edit_Velocity);
	
	QHBoxLayout *H_layout4=new QHBoxLayout;
	H_layout4->addWidget(disp_Yita);
	H_layout4->addWidget(edit_Yita);
	
	QHBoxLayout *H_layout5=new QHBoxLayout;
	H_layout5->addWidget(disp_RepaintTime);
	H_layout5->addWidget(edit_RepaintTime);	
	
	QHBoxLayout *H_layout6=new QHBoxLayout;
	H_layout6->addWidget(disp_HasLeader);
	H_layout6->addWidget(edit_HasLeader);	
	
	QHBoxLayout *H_layout7=new QHBoxLayout;
	H_layout7->addWidget(disp_IsGraph);
	H_layout7->addWidget(edit_IsGraph);
	
	QHBoxLayout *H_layout8=new QHBoxLayout;
	H_layout8->addWidget(init_Flock);
	H_layout8->addWidget(Go);
	
	QVBoxLayout *layout=new QVBoxLayout;
	layout->addLayout(H_layout1);
	layout->addLayout(H_layout2);
	layout->addLayout(H_layout3);
	layout->addLayout(H_layout4);
	layout->addLayout(H_layout5);
	layout->addLayout(H_layout6);
	layout->addLayout(H_layout7);
	layout->addLayout(H_layout8);
	setLayout(layout);
	setWindowTitle("Vicsek Model");
	setFixedHeight(sizeHint().height());
}

void getParaDialog::init_Flocks(){
	//首先更新部分值
	update_HasLeader();
	update_IsGraph();
	//判断是否合法使用
	if(HasLeader==DEFAULT||IsGraph==DEFAULT){//提示错误使用信息
		QMessageBox *qmb=new QMessageBox;
		qmb->setWindowTitle("Error Usage!");
		qmb->setText("Choose Leader or Graph , please!");
		qmb->show();
	}else if(HasLeader==YES||HasLeader==NO){//当有领导的时候，还要设置领导
		HuaBan=new DrawWindow;	
		//1.首先，要获取三个参数：BirdNum,Radius,Velocity
		HuaBan->BirdNum=(int)((edit_BirdNum->text()).toDouble());
		HuaBan->Radius=(edit_Radius->text()).toDouble();
		HuaBan->Velocity=(edit_Velocity->text()).toDouble();
		HuaBan->Dett=((edit_RepaintTime->text()).toDouble())/1000.0;	//将毫秒转换为秒
		HuaBan->HasLeader=HasLeader;
		HuaBan->IsGraph=IsGraph;
		HuaBan->myTimer=0;
		HuaBan->GroupNumber.clear();	//将鸟群的子群个数初始化为0
		//2.再次，初始化鸟群
		HuaBan->flocks=new Bird[HuaBan->BirdNum];
		for(int i=0;i<HuaBan->BirdNum;i++){
			HuaBan->flocks[i].Random_init(LOW_X,UP_X,LOW_Y,UP_Y);
			HuaBan->flocks[i].isLeader=NOTLEADER;
			HuaBan->flocks[i].isOnThePlane=YES;	//该小鸟在画布上
		}
		//3.将标号为0的鸟设置为领导
		if(HasLeader==YES)	
			HuaBan->flocks[0].isLeader=ISLEADER;
	}
}
void getParaDialog::update_Flocks(){
	HuaBan->startDrawing();
	HuaBan->show();
	HuaBan->plotter.show();
}

void getParaDialog::update_HasLeader(){
	int current=edit_HasLeader->currentIndex();
	if(current==2){
		HasLeader=NO;
	}else if(current==1){
		HasLeader=YES; 
	}else if(current==0){
		HasLeader=DEFAULT;
	}
}

void getParaDialog::update_IsGraph(){
	int current=edit_IsGraph->currentIndex();
	if(current==1){
		IsGraph=YES;
	}else if(current==2){
		IsGraph=NO;
	}else if(current==0){
		IsGraph=DEFAULT;
	}
}