#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H
#include <qobject.h>
#include <qsettings.h>
#include <functional>

class LayoutManager: QObject
{
	Q_OBJECT
public:
	LayoutManager(const QString& settingFileName, const QString& layoutFileName):
		_settingFileName(settingFileName),_layoutFileName(layoutFileName),_Settings(settingFileName,QSettings::IniFormat),
		_mainWindowGroup(tr("MainWindow")),_tabPageGroup(tr("TabControl")),
		_geometry(tr("Geometry")),_state(tr("State")),
		_itemSeparator('|'),_tabPageObjectNameAndTitleSeparator('_')
	{

	}
	~LayoutManager(void);
public :
	static LayoutManager Default;

private:
	QString _settingFileName;
	QString _layoutFileName;
	QSettings _Settings;
	QString _mainWindowGroup;
	QString _tabPageGroup;
	const QString  _geometry;
	const QString _state;
	char _itemSeparator;
	char _tabPageObjectNameAndTitleSeparator;

public:

	char getItemSeparator() const
	{
		return _itemSeparator;
	}

	char getTabPageObjectNameAndTitleSeparator() const
	{
		return _tabPageObjectNameAndTitleSeparator;
	}


	void WriteSettings(const QString& groupName,std::function<void()> func)
	{
		_Settings.beginGroup(groupName);
		func();
		_Settings.endGroup();
	}

	void ReadSettings(const QString& groupName, std::function<void()> func)
	{
		_Settings.beginGroup(groupName);
		func();
		_Settings.endGroup();
	}

public :
	QSettings& getQSettings()
	{
		return _Settings;
	}

	const QString& getGeometry(){return _geometry;}
	const QString& getState() {return _state;}


	void WriteMainWindowSettings(std::function<void()> func)
	{
		WriteSettings(_mainWindowGroup,func);
	}
	void ReadMainWindowSettings(std::function<void()> func)
	{
		ReadSettings(_mainWindowGroup,func);
	}

	void WriteTabPageSettings(std::function<void()> func)
	{
		WriteSettings(_tabPageGroup,func);
	}

	void ReadTabPageSettings(std::function<void()> func)
	{
		ReadSettings(_tabPageGroup,func);
	}

};
#endif

