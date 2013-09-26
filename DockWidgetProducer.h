#ifndef DOCKWIDGETPRODUCER_H
#define DOCKWIDGETPRODUCER_H
#include <qdockwidget.h>
class DockParameter;


class DockWidgetProducer:public QObject
{
	Q_OBJECT
public:
	~DockWidgetProducer(void);
private:
	DockWidgetProducer(void):objectNameTemplate(QString("dockWidgetObjectName%1"))
	{
	}
	QDockWidget* createGeneralWidget(const QString& title, QWidget* parent,int index);
	QDockWidget* createGeneralWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName);

	QDockWidget* createCeneralWidgetCommon(const QString& title, QWidget* parent, DockParameter& parameter);

	QDockWidget* createTableWidget(const QString& title, QWidget* parent,int index);
	QDockWidget* createTableWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName);
	QDockWidget* createTableWidgetCommon(const QString& title, QWidget* parent, DockParameter& parameter);

	QDockWidget* setWidgetProperty(const DockParameter& parameter);
private:
	static int Counter;
	QString objectNameTemplate;
public:
	static DockWidgetProducer Default;
	QDockWidget* createWidget(const QString& title, QWidget* parent,int index);
	QDockWidget* createWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName);
};


class DockParameter
{
public:
	QString title;
	QWidget *content;
	QWidget *parent;
	QString objectName;
	QDockWidget::DockWidgetFeatures feature;
	Qt::DockWidgetAreas allowArea;
};


#endif

