#include <QApplication>
#include "Dialogs.h"

int main(int argc,char *argv[]){
	QApplication app(argc,argv);
	
	getParaDialog *Dlogs=new getParaDialog;
	Dlogs->show();
	
	return app.exec();
}