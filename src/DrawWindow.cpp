
#include "DrawWindow.h"

/*--------------------------事件响应部分-------------------------------*/
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
void DrawWindow::timerEvent(QTimerEvent *event){	//定时器
	if(HasLeader==YES){
		control_withLeader();
	}else if(HasLeader==NO){
		control_withoutLeader();
	}
}
void DrawWindow::startDrawing(){	//外部类启动该类的定时器的方法
	myTimerID=startTimer(Dett*1000);		//开始启动计时器
	//申请空间
	neighbor=new int*[BirdNum];
	for(int i=0;i<BirdNum;i++)
		neighbor[i]=new int[BirdNum];
	//初始化数组
	for(int i=0;i<BirdNum;i++)
		for(int j=0;j<BirdNum;j++)
			neighbor[i][j]=0;	//表示不相邻
	//初始化访问数组
	visited=new char[BirdNum];
}

/*--------------------------绘图部分-------------------------------*/
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
	//绘制曲线
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
	//绘制直线
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
	//绘制曲线
	drawPlotter();
}

/*--------------------------控制部分-------------------------------*/
void DrawWindow::control_withoutLeader(){	//用来计算和控制所有粒子的运动的方法:无领导
	//3.0 重新绘制所有粒子
	repaint();
	//1.更新邻居
	update_Neighbor();
	double Rtheta=0;
	double detTheta;
	double direction;
	int NBnum=0;
	//2.更新所有粒子的方向
	for(int i=0;i<BirdNum;i++){	//更新第i只鸟的运动方向
		Rtheta=0;
		NBnum=0;
		for(int j=i;j<BirdNum;j++){
			if(neighbor[i][j]==1){	//找出邻居
				Rtheta+=flocks[j].oritation;
				NBnum++;
			}
		}
		//更新第i只鸟的方向
		detTheta=((qrand()+0.0)/(RAND_MAX+0.0))*Yita;
		direction=((qrand()+0.0)/(RAND_MAX+0.0));
		if(direction>0.5)
			detTheta=0-detTheta;
		flocks[i].oritation=(Rtheta+detTheta)/(NBnum);
	}
	
	for(int i=0;i<BirdNum;i++){
		//3.更新所有粒子的位置
		flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation/360)*2*MY_PI);
		flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation/360)*2*MY_PI);
		//flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation));
		//flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation));
		//3.1 更新周期性边界——X轴
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

void DrawWindow::control_withLeader(){	//用来计算和控制所有粒子的运动的方法:有领导
	//0.0 重新绘制所有粒子
	repaint();
	//1.更新邻居
	update_Neighbor();
	double Rtheta=0;
	double detTheta=0;
	double direction=0;
	int NBnum=0;
	int indicator=0;
	//2.更新所有粒子的方向
	for(int i=1;i<BirdNum;i++){	//更新第i只鸟的运动方向
		Rtheta=0;
		indicator=0;
		NBnum=0;
		for(int j=0;j<=i;j++){
			if(neighbor[i][j]==1){	//找出邻居
				if(j==0){
					indicator=1;
				}
				Rtheta+=flocks[j].oritation;
				NBnum++;
			}
		}
		//更新第i只鸟的方向
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
		//3.更新所有粒子的位置
		flocks[i].coord_x+=Velocity*Dett*cos((flocks[i].oritation/360)*2*MY_PI);
		flocks[i].coord_y+=Velocity*Dett*sin((flocks[i].oritation/360)*2*MY_PI);
		//3.1 更新周期性边界——X轴
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

/*--------------------------更新邻接矩阵的方法-------------------------------*/
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
			if(dist<Radius){	//邻居
				neighbor[i][j]=1;
				neighbor[j][i]=1;
			}else if(dist>=Radius){	//非邻居
				neighbor[i][j]=0;
				neighbor[j][i]=0;			
			}
		}
	}
}

int DrawWindow::subGraphNumber(){
	//算法来自于《算法导论》
	int num=0;
	int unvisitedNum=BirdNum;
	//初始化为零
	for(int i=0;i<BirdNum;i++)
		visited[i]=0;
	for(int i=0;i<BirdNum;i++){
		if(visited[i]==0){//如果没有被访问
			num++;
			//访问结点i对应的图：采用深度遍历
			dfs(i);
		}
	}
	return num;
}

void DrawWindow::dfs(int start){
	for(int i=0;i<BirdNum;i++){	//遍历start的每一个邻接点
		if(neighbor[start][i]&&visited[i]==0){
			visited[i]=1;//表示访问过
			dfs(i);
		}
	}
}

void DrawWindow::drawPlotter(){
	GroupNumber.append(QPointF(myTimer,subGraphNumber()));
	plotter.setting.setPlotter(0,myTimer,0,BirdNum);
	plotter.setCurveData(GroupNumber);
	//时间增加
	myTimer++;
}