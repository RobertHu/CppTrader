#include "qttabdetach.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTTabDetach w;
	w.show();
	return a.exec();
}
