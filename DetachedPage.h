#ifndef DETACHEDPAGE_H 
#define DETACHEDPAGE_H 
#include <qdialog.h>
#include <memory>
#include "WidgetBox.h"
class QToolBar;
class QWidget;
class PageWidget;


class DetachedPage: public QDialog
{
	Q_OBJECT
public:
	DetachedPage(QWidget* parent,PageWidget* pageWidget);
	~DetachedPage(void);
	QToolBar* getToolBar() const
	{
	  return  _toolBar.get();
	}
	PageWidget* getPageWidget() const { return _PageWidget;}
	void saveSettings();
	void loadSettings();
	QString getSelfAndChildrenObjectName();
protected:
  void closeEvent(QCloseEvent *event);
private:
	std::unique_ptr<QToolBar> _toolBar;
	WidgetBox _widgetBox;
	PageWidget* _PageWidget;
	DetachedPage(const DetachedPage& );
	const DetachedPage& operator = (const DetachedPage&);

signals:
    void OnClose (QWidget* widget);
private slots:
	void showWidgetBox();
	
};
#endif

