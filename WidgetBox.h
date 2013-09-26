#ifndef  WIDGETBOX_H
#define WIDGETBOX_H
#include <qdialog.h>
#include "PageWidget.h"
class QWidget;
class QStandardItemModel;
class QListView;
class PageWidget;
class QStandardItem;
class WidgetBox : public QDialog
{
	Q_OBJECT
public:
	WidgetBox(QWidget * parent);
private :
	WidgetBox(const WidgetBox&);
	const WidgetBox& operator = (const WidgetBox&);

	QStandardItemModel* _model;
	QListView* _listView;
	void appendItem(const QString& text, QStandardItem* parent);
signals:
	void appendWidget(const QString& name);
private slots:
	void getSelectedWidget();
};
#endif

