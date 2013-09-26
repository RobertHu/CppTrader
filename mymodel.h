#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QTimer>
#include <qcolor.h>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent);
	~MyModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	
private:
	enum
	{
		ROW= 20,
		COLUMN = 15
	};
	QTimer *_timer;
	QTimer *_timerNum;
	QColor generateColor() const;
private slots:
	void timerHit();
	void timerHit_Num();



};
//! [Quoting ModelView Tutorial]

#endif // MYMODEL_H
