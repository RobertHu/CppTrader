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
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <memory>


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

PageWidget::PageWidget(const QJsonObject& jsonObj,QWidget *parent ):QMainWindow(parent)
{
	init();
	QString objectName = jsonObj["objectName"].toString();
	QString title = jsonObj["title"].toString();
	bool isDetached = jsonObj["isDetached"].toBool();
	QString detachedObjectName = jsonObj["detachedObjectName"].toString();
	setObjectName(objectName);
	_title=title;
	_isDetached = isDetached;
	_detachedObjectName=detachedObjectName;

	QJsonArray children= jsonObj["children"].toArray();
	if(children.size()==0) return;
	for(auto begin=children.begin(), end= children.end();begin!=end;++begin)
	{
		QJsonObject child = begin.operator*().toObject();
		QString childObjectName= child["objectName"].toString();
		QString childTitle=child["title"].toString();
		auto dockWidget = DockWidgetProducer::Default.createWidgetWithObjectName(childTitle,this,childObjectName.toStdString());
		addChild(dockWidget);
	}
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


QJsonObject* PageWidget::getSelfAndChildrenObjectName()
{
	return getSelfAndChildrenObjectNameCommon(false,tr(""));
}

QJsonObject* PageWidget::getSelfAndChildrenObjectNameByDetachedPath(QString& objectName)
 {
	 return getSelfAndChildrenObjectNameCommon(true,objectName);
 }

QJsonObject* PageWidget::getSelfAndChildrenObjectNameCommon(bool isDetached,QString& detachedObjectName)
 {
	 QJsonObject* jsonObj = new QJsonObject;
	jsonObj->insert("objectName",objectName());
	jsonObj->insert("title",_title);
	jsonObj->insert("isDetached",isDetached);
	jsonObj->insert("detachedObjectName",detachedObjectName);
	QJsonArray jsonArray;
	QList<QDockWidget*> dockChildren = findChildren<QDockWidget*>();
	for(int i=0;i<dockChildren.size();i++)
	{
		auto dockWidget= dockChildren.at(i);
		QJsonObject widgetObject;
		widgetObject.insert("objectName",dockWidget->objectName());
		widgetObject.insert("title",dockWidget->windowTitle());
		jsonArray.append(widgetObject);
	}
	jsonObj->insert("children",jsonArray);
	return jsonObj;
 }
