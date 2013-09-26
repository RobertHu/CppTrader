#include "WidgetBox.h"
#include "PageWidget.h"
#include <qstandarditemmodel.h>
#include <qlistview.h>
#include  <qboxlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "StringConstants.h"

WidgetBox::WidgetBox(QWidget * parent):QDialog(parent)
{
	setFixedSize(200,250);
	setModal(true);
	setWindowTitle(tr("Select Widgets"));

	 _model = new QStandardItemModel();

	QStandardItem *parentItem = _model->invisibleRootItem();
	appendItem(*StringConstants::WIDGET1,parentItem);
	appendItem(*StringConstants::WIDGET2,parentItem);
	appendItem(*StringConstants::WIDGET3,parentItem);
	appendItem(*StringConstants::WIDGET4,parentItem);
	_listView= new QListView();
	_listView->setModel(_model);

	_listView->setSelectionBehavior(QAbstractItemView::SelectRows);

	QVBoxLayout * vlayout = new QVBoxLayout();
	QPushButton *btn = new QPushButton();
	btn->setText(tr("ok"));

	connect(btn,&QPushButton::clicked,this,&WidgetBox::getSelectedWidget);

	vlayout->addWidget(_listView);
	vlayout->addWidget(btn);
	this->setLayout(vlayout);
}

void WidgetBox::getSelectedWidget()
{
	int rows = _model->rowCount();
	for(int i=0;i<rows;i++)
	{
		auto item = _model->item(i);
		if(item->checkState() == Qt::CheckState::Checked)
		{
			auto data = item->data(Qt::DisplayRole);
			emit appendWidget(data.toString());
			item->setCheckState(Qt::Unchecked);
		}

	}

	close();
}


void WidgetBox::appendItem(const QString& text, QStandardItem* parent)
{
	QStandardItem *item = new QStandardItem(text);
	item->setEditable(false);
	item->setCheckable(true);
	parent->appendRow(item);
}

