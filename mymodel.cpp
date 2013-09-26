
#include "mymodel.h"
#include <QTime>
#include <qbrush.h>

#include <cstdlib>
#include <ctime>
#include <sstream>

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
{
	_timer = new QTimer();
	_timer->setInterval(1000);
	connect(_timer,&QTimer::timeout, this ,&MyModel::timerHit);
	_timer->start();

	_timerNum = new QTimer();
	_timerNum->setInterval(200);
	connect(_timerNum,&QTimer::timeout,this,&MyModel::timerHit_Num);
	_timerNum->start();

}

MyModel::~MyModel()
{
	_timer->stop();
	delete _timer;
	_timerNum->stop();
	delete _timerNum;
}



int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
	return ROW;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
	return COLUMN;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
	   if(index.row()==0 && index.column()==0)
	   {
		   return QTime::currentTime().toString();
	   }
	   else if(index.column()==3)
	   {
		     std::srand(std::time(nullptr));
			 std::stringstream ss;
			 double value = rand()  + 20.5;
			 ss << value;
			 return QString::fromStdString(ss.str());
	   }

       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
	else if(role ==Qt::ForegroundRole)
	{
		 if(index.column()==0)
		 {
			QColor color = generateColor();
			 QBrush yellowBackground(color);
			 return yellowBackground;
		 }
		 else if(index.column()==3)
		 {
			 QColor color = generateColor();
			 QBrush forecolor(color);
			 return forecolor;
		 }
	}
    return QVariant();
}


QColor MyModel::generateColor() const
{
	 std::srand(std::time(nullptr));
	 int r = rand()%255 + 1;
	 int g = rand()%255 + 1;
	 int b = rand()%255 + 1;
	 return QColor::fromRgb(r,g,b);
}


void MyModel::timerHit()
{
	for(int i=0; i<ROW;i++)
	{
		QModelIndex index = createIndex(i,0);
		emit dataChanged(index ,index );
	}
}


void MyModel::timerHit_Num()
{
	for(int i=0;i< ROW;i++)
	{
		QModelIndex  index = createIndex(i,3);
		emit dataChanged(index,index);
	}
}

//! [Quoting ModelView Tutorial]
