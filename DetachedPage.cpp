#include "DetachedPage.h"
#include <qtoolbar.h>
#include <qaction.h>

#include "PageWidget.h"
#include <qtoolbutton.h>
#include "LayoutManager.h"

DetachedPage::DetachedPage(QWidget* parent, PageWidget* pageWidget):QDialog(parent),_widgetBox(pageWidget),
	_toolBar(new QToolBar()),_PageWidget(pageWidget)
{
	QAction *action = new QAction(tr("add Widget"),this);
	QToolButton *qtoolbtn=new QToolButton(this);
	qtoolbtn->setDefaultAction(action);
	_toolBar->addWidget(qtoolbtn);
	qtoolbtn->setStyleSheet("QToolButton:hover {background-color:blue} QToolButton:!hover { background-color: white }");
	connect(action,&QAction::triggered,this,&DetachedPage::showWidgetBox);
	connect(&_widgetBox,&WidgetBox::appendWidget,pageWidget,&PageWidget::appendChild);
}

DetachedPage::~DetachedPage(void)
{
}


void DetachedPage::closeEvent(QCloseEvent* /*event*/)
{
	emit OnClose(this);
}


void DetachedPage::showWidgetBox()
{
	_widgetBox.show();
}


void DetachedPage::saveSettings()
{
	auto &manager = LayoutManager::Default;
	auto window = this;
	manager.WriteSettings(window->objectName(),[&]()
	{
		auto &settings = manager.getQSettings();
		settings.setValue(manager.getGeometry(),window->saveGeometry());
	});
}


void DetachedPage::loadSettings()
{
	auto &manager =  LayoutManager::Default;
	auto window = this;
	manager.ReadSettings(window->objectName(),[&]()
	{
		auto &settings = manager.getQSettings();
		window->restoreGeometry(settings.value(manager.getGeometry()).toByteArray());
	});
}

QString DetachedPage::getSelfAndChildrenObjectName()
{
	return _PageWidget->getSelfAndChildrenObjectNameByDetachedPath(objectName());
}