#include "PageWidget.h"
#include <qtableview.h>
#include <qtextedit.h>
#include <qaction.h>
#include "mymodel.h"
#include "WidgetBox.h"
#include "DockWidgetProducer.h"
#include "StringConstants.h"
#include "LayoutManager.h"
#include <vector>
#include "MaxSuffixHelper.h"
#include "LayoutLineParser.h"


PageWidget::PageWidget(int suffixIndex,const QString& titile,QWidget *parent):QMainWindow(parent),
	_title(titile),_isDetached(false), _detachedObjectName("")
{
	setObjectName(tr("PageWidgetObjectName%1").arg(suffixIndex));
	init();
}

PageWidget::PageWidget(const std::string& line, QWidget *parent):QMainWindow(parent)
{
	init();
	auto parameter = LayoutLineParser::Default.parse(line,LayoutManager::Default.getTabPageObjectNameAndTitleSeparator());
	auto objectName = QString::fromStdString(parameter[0]);
	_title =QString::fromStdString(parameter[1]);
	_isDetached =  parameter[2] == "1";
	if(_isDetached)
	{
		_detachedObjectName = QString::fromStdString(parameter[3]);
	}
	setObjectName(objectName);
}

void PageWidget::init()
{
	setWindowTitle(tr("DockWindows"));
	QTextEdit *te = new QTextEdit(this);
	te->setText(tr("Main Window"));
	te->setAlignment(Qt::AlignCenter);
	setCentralWidget(te);
	this->centralWidget()->hide();
	this->setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AnimatedDocks);
}

void PageWidget::configChildren(const std::vector<std::string>& dockWidgetObjectNames)
{   
	auto begin = dockWidgetObjectNames.cbegin() + 1;
	auto end= dockWidgetObjectNames.cend();
	for( ;begin!=end;++begin)
	{
		auto objectNameAndTitle = LayoutLineParser::Default.parse(*begin,LayoutManager::Default.getTabPageObjectNameAndTitleSeparator());
		auto objectName = objectNameAndTitle[0];
		auto title =QString::fromStdString(objectNameAndTitle[1]);
		auto dockWidget = DockWidgetProducer::Default.createWidgetWithObjectName(title,this,objectName);
		addChild(dockWidget);
	}
}

void PageWidget::loadSettings()
{
	auto  &manager = LayoutManager::Default;
	auto *window = this;
	manager.ReadSettings(objectName(),[&]()
	{
		auto &settings = manager.getQSettings();
		window->restoreGeometry(settings.value(manager.getGeometry()).toByteArray());
		window->restoreState(settings.value(manager.getState()).toByteArray());
	});
}

void PageWidget::addChild(QDockWidget* child)
{
	addDockWidget(Qt::LeftDockWidgetArea,child,Qt::Horizontal);
}

void PageWidget::appendChild(const QString& name)
{
	std::vector<std::string> objectNames;
	auto list = findChildren<QDockWidget*>();
	for(int i=0;i<list.size();i++)
	{
		objectNames.push_back(list.at(i)->objectName().toStdString());
	}
	int index = MaxSuffixHelper::Default.getMaxSuffixIndex(objectNames);
	auto widget=DockWidgetProducer::Default.createWidget(name,this,++index);
	addChild(widget);
}


void PageWidget::saveSettings()
{
	auto* window = this;
	auto &manager = LayoutManager::Default;
	manager.WriteSettings(objectName(),[&]()
	{
		auto &settings = manager.getQSettings();
		settings.setValue(manager.getGeometry(),window->saveGeometry());
		settings.setValue(manager.getState(),window->saveState());
	});
}


QString PageWidget::getSelfAndChildrenObjectName()
{
	return getSelfAndChildrenObjectNameCommon(false,tr(""));
}

QString PageWidget::getSelfAndChildrenObjectNameByDetachedPath(QString& objectName)
 {
	 return getSelfAndChildrenObjectNameCommon(true,objectName);
 }

QString PageWidget::getSelfAndChildrenObjectNameCommon(bool isDetached,QString& detachedObjectName)
 {
	QString result("");
	QString tabPageObjectName = objectName();
	result += tr("%1_%2").arg(tabPageObjectName).arg(_title);
	if(isDetached)
	{
		result += tr("_1_%2").arg(detachedObjectName);
	}
	else{
		result += tr("_0");
	}
	QList<QDockWidget*> dockChildren = findChildren<QDockWidget*>();
	for(int i=0;i<dockChildren.size();i++)
	{
		auto dockWidget= dockChildren.at(i);
		result += "|";
		result += tr("%1_%2").arg(dockWidget->objectName()).arg(dockWidget->windowTitle());
	}
	return result;
 }
