#ifndef GETPARA_H
#define GETPARA_H

#include "DrawWindow.h"

class getParaDialog : public QDialog
{
	Q_OBJECT
public:
	getParaDialog(QWidget *parent=0);
//�ź�:��ʱδ����
signals:
	void find_Next();
	void find_Previous();
//��
public slots:
	void init_Flocks();
	void update_Flocks();
	void update_HasLeader();
	void update_IsGraph();

public:
	//��ȡ�����Ŀؼ�
	QLabel *disp_BirdNum;			//�������Ŀ
	QLineEdit *edit_BirdNum;
	QLabel *disp_Radius;			//Ӱ��뾶
	QLineEdit *edit_Radius;
	QLabel *disp_Yita;				//������ӣ��������Ƕȵ��Ͻ�
	QLineEdit *edit_Yita;
	QLabel *disp_Velocity;			//������ٶ�
	QLineEdit *edit_Velocity;
	QLabel *disp_RepaintTime;		//ÿ�θ��µ�ʱ��
	QLineEdit *edit_RepaintTime;
	QLabel *disp_HasLeader;			//��Ⱥ���Ƿ����쵼
	QComboBox *edit_HasLeader;	
	QLabel *disp_IsGraph;			//�Ƿ����ͼ��ģ��
	QComboBox *edit_IsGraph;	
	
	QPushButton *init_Flock;		//���ư�ť
	QPushButton *Go;
	
	//��ʾ��Ⱥ�Ļ���
	DrawWindow *HuaBan;
	int HasLeader;
	int IsGraph;
};
#endif