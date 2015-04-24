
#include "DrawWindow.h"

/*--------------------------�¼���Ӧ����-------------------------------*/
void DrawWindow::paintEvent(QPaintEvent *event){
	Q_UNUSED(event);
	QPainter gp(this);
	if(IsGraph==YES){
		drawBirds_withGraph(&gp);
	}
	else if(IsGraph==NO){
		drawBirds_withoutGraph(&gp);
	}
}
void DrawWindow::timerEvent(QTimerEvent *event){	//��ʱ��
	if(HasLeader==YES){
		control_withLeader();
	}else if(HasLeader==NO){
		control_withoutLeader();
	}
}
void DrawWindow::startDrawing(){	//�ⲿ����������Ķ�ʱ���ķ���
	myTimerID=startTimer(Dett*1000);		//��ʼ������ʱ��
	//����ռ�
	neighbor=new int*[BirdNum];
	for(int i=0;i<BirdNum;i++)
		neighbor[i]=new int[BirdNum];
	//��ʼ������
	for(int i=0;i<BirdNum;i++)
		for(int j=0;j<BirdNum;j++)
			neighbor[i][j]=0;	//��ʾ������
	//��ʼ����������
	visited=new char[BirdNum];
}

/*--------------------------��ͼ����-------------------------------*/
void DrawWindow::drawBirds_withoutGraph(QPainter *gp){
	int start=0;
	int startAngle=0;
	if(HasLeader==YES){
		start=1;
		hawk->setRect(flocks[0].coord_x,flocks[0].coord_y,rectWidth,rectHeight);
		startAngle=(int)(flocks[0].oritation)*16;
		gp->setBrush(QBrush("#000000"));
		gp->drawPie(*hawk,startAngle,spanAngle);
	}
	for(int i=start;i<BirdNum;i++){
		hawk->setRect(flocks[i].coord_x,flocks[i].coord_y,rectWidth,rectHeight);
		startAngle=(int)(flocks[i].oritation*16);
		gp->setBrush(QBrush("#1ac500"));
		gp->drawPie(*hawk,startAngle,spanAngle);	
	} 
	//��������
	drawPlotter();
}

void DrawWindow::drawBirds_withGraph(QPainter *gp){
	int start=0;
	int startAngle=0;
	if(HasLeader==YES){
		start=1;
		hawk->setRect(flocks[0].coord_x,flocks[0].coord_y,rectWidth,rectHeight);
		startAngle=(int)(flocks[0].oritation)*16;
		gp->setBrush(QBrush("#000000"));
		gp->drawPie(*hawk,startAngle,spanAngle);
	}
	for(int i=start;i<BirdNum;i++){
		hawk->setRect(flocks[i].coord_x,flocks[i].coord_y,rectWidth,rectHeight);
		startAngle=(int)(flocks[i].oritation)*16;
		gp->setBrush(QBrush("#1ac500"));
		gp->drawPie(*hawk,startAngle,spanAngle);
	}
	//����ֱ��
	int Ion;
	int Jon;
	for(int i=0;i<BirdNum;i++){
		Ion=flocks[i].isOnThePlane;
		for(int j=i+1;j<BirdNum;j++){
			Jon=flocks[j].isOnThePlane;
			if(neighbor[i][j]==1&&Ion==YES&&Jon==YES){
				gp->setPen(QPen(Qt::red,1,Qt::SolidLine));
				gp->drawLine(flocks[i].coord_x+rectWidth/2,flocks[i].coord_y+rectHeight/2,
				flocks[j].coord_x+rectWidth/2,flocks[j].coord_y+rectHeight/2);
			}
		}
	}
	//��������
	drawPlotter();
}

/*--------------------------���Ʋ���-------------------------------*/
void DrawWindow::control_withoutLeader(){	//��������Ϳ����������ӵ��˶��ķ���:���쵼
	//3.0 ���»�����������
	repaint();
	//1.�����ھ�
	update_Neighbor();
	double Rtheta=0;
	double detTheta;
	double direction;
	int NBnum=0;
	//2.�����������ӵķ���
	for(int i=0;i<BirdNum;i++){	//���µ�iֻ����˶�����
		Rtheta=0;
		NBnum=0;
		for(int j=i;j<BirdNum;j++){
			if(neighbor[i][j]==1){	//�ҳ��ھ�
				Rtheta+=flocks[j].oritation;
				NBnum++;
			}
		}
		//���µ�iֻ��ķ���
		detTheta=((qrand()+0.0)/(RAND_MAX+0.0))*Yita;
		direction=((qrand()+0.0)/(RAND_MAX+0.0));
		if(direction>0.5)
			detTheta=0-detTheta;
		flocks[i].oritation=(Rtheta+detTheta)/(NBnum);
	}
	
	for(int i=0;i<BirdNum;i++){
		//3.�����������ӵ�λ��
		flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation/360)*2*MY_PI);
		flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation/360)*2*MY_PI);
		//flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation));
		//flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation));
		//3.1 ���������Ա߽硪��X��
		if(flocks[i].coord_x<LOW_X){
			flocks[i].coord_x=UP_X;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_x>UP_X){
			flocks[i].coord_x=LOW_X;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_y<LOW_Y){
			flocks[i].coord_y=UP_Y;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_y>UP_Y){
			flocks[i].coord_y=LOW_Y;	  
			flocks[i].isOnThePlane=NO;
		}else{
			flocks[i].isOnThePlane=YES;
		}
	}
}

void DrawWindow::control_withLeader(){	//��������Ϳ����������ӵ��˶��ķ���:���쵼
	//0.0 ���»�����������
	repaint();
	//1.�����ھ�
	update_Neighbor();
	double Rtheta=0;
	double detTheta=0;
	double direction=0;
	int NBnum=0;
	int indicator=0;
	//2.�����������ӵķ���
	for(int i=1;i<BirdNum;i++){	//���µ�iֻ����˶�����
		Rtheta=0;
		indicator=0;
		NBnum=0;
		for(int j=0;j<=i;j++){
			if(neighbor[i][j]==1){	//�ҳ��ھ�
				if(j==0){
					indicator=1;
				}
				Rtheta+=flocks[j].oritation;
				NBnum++;
			}
		}
		//���µ�iֻ��ķ���
		detTheta=((qrand()+0.0)/(RAND_MAX+0.0))*Yita;
		direction=((qrand()+0.0)/(RAND_MAX+0.0));
		if(direction>0.5)
			detTheta=0-detTheta;
		
		if(indicator==0)	
			flocks[i].oritation=(Rtheta+detTheta)/(NBnum);
		else if(indicator==1)
			flocks[i].oritation=(flocks[0].oritation+Rtheta+detTheta)/(NBnum+1);
	}
	for(int i=0;i<BirdNum;i++){
		//3.�����������ӵ�λ��
		flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation/360)*2*MY_PI);
		flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation/360)*2*MY_PI);
		//3.1 ���������Ա߽硪��X��
		if(flocks[i].coord_x<LOW_X){
			flocks[i].coord_x=UP_X;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_x>UP_X){
			flocks[i].coord_x=LOW_X;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_y<LOW_Y){
			flocks[i].coord_y=UP_Y;
			flocks[i].isOnThePlane=NO;
		}else if(flocks[i].coord_y>UP_Y){
			flocks[i].coord_y=LOW_Y;	  
			flocks[i].isOnThePlane=NO;
		}else{
			flocks[i].isOnThePlane=YES;
		}	  
	}
}

/*--------------------------�����ڽӾ���ķ���-------------------------------*/
void DrawWindow::update_Neighbor(){
	double temp1;
	double temp2;
	double temp3;
	double temp4;
	double dist;
	for(int i=0;i<BirdNum;i++){
		temp3=flocks[i].coord_x;
		temp4=flocks[i].coord_y;
		for(int j=i;j<BirdNum;j++){
			temp1=temp3-flocks[j].coord_x;
			temp2=temp4-flocks[j].coord_y;
			temp1=temp1*temp1;
			temp2=temp2*temp2;
			dist=sqrt(temp1+temp2);
			if(dist<Radius){	//�ھ�
				neighbor[i][j]=1;
				neighbor[j][i]=1;
			}else if(dist>=Radius){	//���ھ�
				neighbor[i][j]=0;
				neighbor[j][i]=0;			
			}
		}
	}
}

int DrawWindow::subGraphNumber(){
	//�㷨�����ڡ��㷨���ۡ�
	int num=0;
	int unvisitedNum=BirdNum;
	//��ʼ��Ϊ��
	for(int i=0;i<BirdNum;i++)
		visited[i]=0;
	for(int i=0;i<BirdNum;i++){
		if(visited[i]==0){//���û�б�����
			num++;
			//���ʽ��i��Ӧ��ͼ��������ȱ���
			dfs(i);
		}
	}
	return num;
}

void DrawWindow::dfs(int start){
	for(int i=0;i<BirdNum;i++){	//����start��ÿһ���ڽӵ�
		if(neighbor[start][i]&&visited[i]==0){
			visited[i]=1;//��ʾ���ʹ�
			dfs(i);
		}
	}
}

void DrawWindow::drawPlotter(){
	GroupNumber.append(QPointF(myTimer,subGraphNumber()));
	plotter.setting.setPlotter(0,myTimer,0,BirdNum);
	plotter.setCurveData(GroupNumber);
	//ʱ������
	myTimer++;
}