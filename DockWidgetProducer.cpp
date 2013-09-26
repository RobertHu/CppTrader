#include "DockWidgetProducer.h"
#include "StringConstants.h"
#include <qtextedit.h>
#include <qtableview.h>
#include "mymodel.h"

int DockWidgetProducer::Counter = 0;

DockWidgetProducer::~DockWidgetProducer(void)
{
}

DockWidgetProducer DockWidgetProducer::Default;


QDockWidget* DockWidgetProducer::createWidget(const QString& title, QWidget* parent,int index)
{
	if(title ==  *StringConstants::WIDGET3)
	{
		return createTableWidget(title,parent,index);
	}
	else
	{
		return createGeneralWidget(title,parent,index);
	}

}
QDockWidget* DockWidgetProducer::createWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName)
{
	if(title ==  *StringConstants::WIDGET3)
	{
		return createTableWidgetWithObjectName(title,parent,objectName);
	}
	else
	{
		return createGeneralWidgetWithObjectName(title,parent,objectName);
	}

}


QDockWidget* DockWidgetProducer::createGeneralWidget(const QString& title, QWidget* parent,int index)
{
	DockParameter parameter;
	parameter.objectName=objectNameTemplate.arg(index );
	return createCeneralWidgetCommon(title,parent,parameter);
}
QDockWidget* DockWidgetProducer::createGeneralWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName)
{
	DockParameter parameter;
	parameter.objectName =QString::fromStdString(objectName);
	return createCeneralWidgetCommon(title,parent,parameter);
}

QDockWidget* DockWidgetProducer::createCeneralWidgetCommon(const QString& title, QWidget* parent, DockParameter& parameter)
{
	parameter.title= title;
	parameter.feature=QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable ;
	parameter.allowArea= Qt::AllDockWidgetAreas;
	auto te1 = new QTextEdit();
	te1->setText(tr("window, the dock widget can be moved between docks by the user"));
	parameter.content=te1;
	parameter.parent=parent;
	return setWidgetProperty(parameter);
}



QDockWidget* DockWidgetProducer::createTableWidget(const QString& title, QWidget* parent,int index)
{
	DockParameter parameter;
	parameter.objectName=objectNameTemplate.arg(index );
	return createTableWidgetCommon(title,parent,parameter);
}

QDockWidget* DockWidgetProducer::createTableWidgetWithObjectName(const QString& title, QWidget* parent,const std::string& objectName)
{
	DockParameter parameter;
	parameter.objectName= QString::fromStdString(objectName);
	return createTableWidgetCommon(title,parent,parameter);
}

QDockWidget* DockWidgetProducer::createTableWidgetCommon(const QString& title, QWidget* parent, DockParameter& parameter)
{
	QTableView *tableView = new QTableView();
	MyModel *model = new MyModel(nullptr);
	tableView->setModel(model);
	parameter.content=tableView;
	parameter.title= title;
	parameter.feature = QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable;
	parameter.allowArea=Qt::AllDockWidgetAreas;
	parameter.parent=parent;
	return setWidgetProperty(parameter);
}

QDockWidget* DockWidgetProducer::setWidgetProperty(const DockParameter& parameter)
{
	QDockWidget *dock=new QDockWidget(parameter.title,parameter.parent);
	dock->setFeatures(parameter.feature);
	dock->setAllowedAreas(parameter.allowArea);
	dock->setWidget(parameter.content);
	dock->setObjectName(parameter.objectName);
	dock->setAttribute(Qt::WA_DeleteOnClose,true);
	return dock;
}
