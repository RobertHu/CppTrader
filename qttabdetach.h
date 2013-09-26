#ifndef QTTABDETACH_H
#define QTTABDETACH_H

#include <QtWidgets/QMainWindow>
#include "ui_qttabdetach.h"

class QTTabDetach : public QMainWindow
{
	Q_OBJECT

public:
	QTTabDetach(QWidget *parent = 0);
	~QTTabDetach();

private:
	Ui::QTTabDetachClass ui;
};

#endif // QTTABDETACH_H
