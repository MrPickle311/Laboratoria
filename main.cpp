#include "Laboratory.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	Laboratoria w;
	w.show();
	return a.exec();
}
