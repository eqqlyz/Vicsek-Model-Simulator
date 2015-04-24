#include <QtGui>
#include <iostream>
#include "Dialogs.h"

getParaDialog::getParaDialog(QWidget *parent)
	:QDialog(parent){
	//�����Ŀ
	disp_BirdNum=new QLabel(tr("Particle Number"));
	disp_BirdNum->setFixedWidth(110);
	edit_BirdNum=new QLineEdit;
	edit_BirdNum->setFixedWidth(110);
	disp_BirdNum->setBuddy(edit_BirdNum);
	//����Ӿ��뾶
	disp_Radius=new QLabel(tr("View Radius"));
	disp_Radius->setFixedWidth(110);
	edit_Radius=new QLineEdit;
	edit_Radius->setFixedWidth(110);
	disp_Radius->setBuddy(edit_Radius);
	//��ķ����ٶ�
	disp_Velocity=new QLabel(tr("Particle Velocity"));
	disp_Velocity->setFixedWidth(110);
	edit_Velocity=new QLineEdit;
	edit_Velocity->setFixedWidth(110);
	disp_Velocity->setBuddy(edit_Velocity);
	//����������Ƕ��Ͻ�
	disp_Yita=new QLabel(tr("Random direction"));
	disp_Yita->setFixedWidth(110);
	edit_Yita=new QLineEdit;
	edit_Yita->setFixedWidth(110);
	disp_Yita->setBuddy(edit_Yita);
	//�������ʱ��
	disp_RepaintTime=new QLabel(tr("Update Time"));
	disp_RepaintTime->setFixedWidth(110);
	edit_RepaintTime=new QLineEdit;
	edit_RepaintTime->setFixedWidth(110);
	disp_RepaintTime->setBuddy(edit_RepaintTime);
	//�Ƿ����쵼
	disp_HasLeader=new QLabel(tr("Has Leader or not"));
	disp_HasLeader->setFixedWidth(110);
	edit_HasLeader=new QComboBox;
	edit_HasLeader->addItem(tr("Default"));
	edit_HasLeader->addItem(tr("Yes"));
	edit_HasLeader->addItem(tr("No"));
	edit_HasLeader->setFixedWidth(110);
	disp_HasLeader->setBuddy(edit_HasLeader);	
	//�Ƿ����ͼģ��
	disp_IsGraph=new QLabel(tr("Graph or not"));
	disp_IsGraph->setFixedWidth(110);
	edit_IsGraph=new QComboBox;
	edit_IsGraph->addItem(tr("Default"));
	edit_IsGraph->addItem(tr("Use graph"));
	edit_IsGraph->addItem(tr("No graph"));
	edit_IsGraph->setFixedWidth(110);
	disp_IsGraph->setBuddy(edit_IsGraph);
	//����
	init_Flock=new QPushButton(tr("Initiation"));
	Go=new QPushButton(tr("Go"));
	//�¼���Ӧ����
	connect(edit_HasLeader, SIGNAL(currentIndexChanged(int)),this, SLOT(update_HasLeader()));
	connect(edit_IsGraph,SIGNAL(currentIndexChanged(int)),this,SLOT(update_IsGraph()));
	connect(init_Flock,SIGNAL(clicked()),this,SLOT(init_Flocks()));
	connect(Go,SIGNAL(clicked()),this,SLOT(update_Flocks()));
	//�ؼ�����
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
	//���ȸ��²���ֵ
	update_HasLeader();
	update_IsGraph();
	//�ж��Ƿ�Ϸ�ʹ��
	if(HasLeader==DEFAULT||IsGraph==DEFAULT){//��ʾ����ʹ����Ϣ
		QMessageBox *qmb=new QMessageBox;
		qmb->setWindowTitle("Error Usage!");
		qmb->setText("Choose Leader or Graph , please!");
		qmb->show();
	}else if(HasLeader==YES||HasLeader==NO){//�����쵼��ʱ�򣬻�Ҫ�����쵼
		HuaBan=new DrawWindow;	
		//1.���ȣ�Ҫ��ȡ����������BirdNum,Radius,Velocity
		HuaBan->BirdNum=(int)((edit_BirdNum->text()).toDouble());
		HuaBan->Radius=(edit_Radius->text()).toDouble();
		HuaBan->Velocity=(edit_Velocity->text()).toDouble();
		HuaBan->Dett=((edit_RepaintTime->text()).toDouble())/1000.0;	//������ת��Ϊ��
		HuaBan->HasLeader=HasLeader;
		HuaBan->IsGraph=IsGraph;
		HuaBan->myTimer=0;
		HuaBan->GroupNumber.clear();	//����Ⱥ����Ⱥ������ʼ��Ϊ0
		//2.�ٴΣ���ʼ����Ⱥ
		HuaBan->flocks=new Bird[HuaBan->BirdNum];
		for(int i=0;i<HuaBan->BirdNum;i++){
			HuaBan->flocks[i].Random_init(LOW_X,UP_X,LOW_Y,UP_Y);
			HuaBan->flocks[i].isLeader=NOTLEADER;
			HuaBan->flocks[i].isOnThePlane=YES;	//��С���ڻ�����
		}
		//3.�����Ϊ0��������Ϊ�쵼
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