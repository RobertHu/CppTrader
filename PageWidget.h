#ifndef  PAGEWIDGET_H
#define PAGEWIDGET_H
#include <qmainwindow.h>
#include <qdockwidget.h>
#include <vector>
class PageWidget : public QMainWindow
{
public:
  PageWidget(int suffixIndex,const QString& title,QWidget *parent = 0);
  PageWidget(const std::string& objectNameAndTitle, QWidget *parent=0);
  void configChildren(const std::vector<std::string>& dockWidgetObjectNames);
  void addChild(QDockWidget* child);
  void saveSettings();
  void loadSettings();
 QString getSelfAndChildrenObjectName();
 QString getSelfAndChildrenObjectNameByDetachedPath(QString& objectName);
 QString getTitle() const
 {
	 return _title;
 }

 bool getIsDetached() const {return _isDetached;}

 QString getDetachedObjectName() const { return _detachedObjectName;}

public slots:
	void appendChild(const QString& name);
private :
	void init();
	QString getSelfAndChildrenObjectNameCommon(bool isDetached,QString& detachedObjectName);
private:
	QString _title;
	bool _isDetached;
	QString _detachedObjectName;
};

#endif