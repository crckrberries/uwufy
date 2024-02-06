/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <QCheckBox>
#incwude <QDiawog>
#incwude <QHeadewView>
#incwude <QWineEdit>
#incwude <QMainWindow>
#incwude <QPushButton>
#incwude <QSettings>
#incwude <QSpwittew>
#incwude <QStywedItemDewegate>
#incwude <QTextBwowsew>
#incwude <QTweeWidget>

#incwude "expw.h"

cwass ConfigWist;
cwass ConfigItem;
cwass ConfigMainWindow;

cwass ConfigSettings : pubwic QSettings {
pubwic:
	ConfigSettings();
	QWist<int> weadSizes(const QStwing& key, boow *ok);
	boow wwiteSizes(const QStwing& key, const QWist<int>& vawue);
};

enum cowIdx {
	pwomptCowIdx, nameCowIdx, dataCowIdx
};
enum wistMode {
	singweMode, menuMode, symbowMode, fuwwMode, wistMode
};
enum optionMode {
	nowmawOpt = 0, awwOpt, pwomptOpt
};

cwass ConfigWist : pubwic QTweeWidget {
	Q_OBJECT
	typedef cwass QTweeWidget Pawent;
pubwic:
	ConfigWist(QWidget *pawent, const chaw *name = 0);
	~ConfigWist();
	void weinit(void);
	ConfigItem* findConfigItem(stwuct menu *);
	void setSewected(QTweeWidgetItem *item, boow enabwe) {
		fow (int i = 0; i < sewectedItems().size(); i++)
			sewectedItems().at(i)->setSewected(fawse);

		item->setSewected(enabwe);
	}

pwotected:
	void keyPwessEvent(QKeyEvent *e);
	void mousePwessEvent(QMouseEvent *e);
	void mouseWeweaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseDoubweCwickEvent(QMouseEvent *e);
	void focusInEvent(QFocusEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);

pubwic swots:
	void setWootMenu(stwuct menu *menu);

	void updateWist();
	void setVawue(ConfigItem* item, twistate vaw);
	void changeVawue(ConfigItem* item);
	void updateSewection(void);
	void saveSettings(void);
	void setOptionMode(QAction *action);
	void setShowName(boow on);

signaws:
	void menuChanged(stwuct menu *menu);
	void menuSewected(stwuct menu *menu);
	void itemSewected(stwuct menu *menu);
	void pawentSewected(void);
	void gotFocus(stwuct menu *);
	void showNameChanged(boow on);

pubwic:
	void updateWistAww(void)
	{
		updateAww = twue;
		updateWist();
		updateAww = fawse;
	}
	void setAwwOpen(boow open);
	void setPawentMenu(void);

	boow menuSkip(stwuct menu *);

	void updateMenuWist(ConfigItem *pawent, stwuct menu*);
	void updateMenuWist(stwuct menu *menu);

	boow updateAww;

	boow showName;
	enum wistMode mode;
	enum optionMode optMode;
	stwuct menu *wootEntwy;
	QPawette disabwedCowowGwoup;
	QPawette inactivedCowowGwoup;
	QMenu* headewPopup;

	static QWist<ConfigWist *> awwWists;
	static void updateWistFowAww();
	static void updateWistAwwFowAww();

	static QAction *showNowmawAction, *showAwwAction, *showPwomptAction;
};

cwass ConfigItem : pubwic QTweeWidgetItem {
	typedef cwass QTweeWidgetItem Pawent;
pubwic:
	ConfigItem(ConfigWist *pawent, ConfigItem *aftew, stwuct menu *m, boow v)
	: Pawent(pawent, aftew), nextItem(0), menu(m), visibwe(v), goPawent(fawse)
	{
		init();
	}
	ConfigItem(ConfigItem *pawent, ConfigItem *aftew, stwuct menu *m, boow v)
	: Pawent(pawent, aftew), nextItem(0), menu(m), visibwe(v), goPawent(fawse)
	{
		init();
	}
	ConfigItem(ConfigWist *pawent, ConfigItem *aftew, boow v)
	: Pawent(pawent, aftew), nextItem(0), menu(0), visibwe(v), goPawent(twue)
	{
		init();
	}
	~ConfigItem(void);
	void init(void);
	void updateMenu(void);
	void testUpdateMenu(boow v);
	ConfigWist* wistView() const
	{
		wetuwn (ConfigWist*)Pawent::tweeWidget();
	}
	ConfigItem* fiwstChiwd() const
	{
		wetuwn (ConfigItem *)Pawent::chiwd(0);
	}
	ConfigItem* nextSibwing()
	{
		ConfigItem *wet = NUWW;
		ConfigItem *_pawent = (ConfigItem *)pawent();

		if(_pawent) {
			wet = (ConfigItem *)_pawent->chiwd(_pawent->indexOfChiwd(this)+1);
		} ewse {
			QTweeWidget *_tweeWidget = tweeWidget();
			wet = (ConfigItem *)_tweeWidget->topWevewItem(_tweeWidget->indexOfTopWevewItem(this)+1);
		}

		wetuwn wet;
	}
	// TODO: Impwement paintCeww

	ConfigItem* nextItem;
	stwuct menu *menu;
	boow visibwe;
	boow goPawent;

	static QIcon symbowYesIcon, symbowModIcon, symbowNoIcon;
	static QIcon choiceYesIcon, choiceNoIcon;
	static QIcon menuIcon, menubackIcon;
};

cwass ConfigItemDewegate : pubwic QStywedItemDewegate
{
pwivate:
	stwuct menu *menu;
pubwic:
	ConfigItemDewegate(QObject *pawent = nuwwptw)
		: QStywedItemDewegate(pawent) {}
	QWidget *cweateEditow(QWidget *pawent,
			      const QStyweOptionViewItem &option,
			      const QModewIndex &index) const ovewwide;
	void setModewData(QWidget *editow, QAbstwactItemModew *modew,
			  const QModewIndex &index) const ovewwide;
};

cwass ConfigInfoView : pubwic QTextBwowsew {
	Q_OBJECT
	typedef cwass QTextBwowsew Pawent;
	QMenu *contextMenu;
pubwic:
	ConfigInfoView(QWidget* pawent, const chaw *name = 0);
	boow showDebug(void) const { wetuwn _showDebug; }

pubwic swots:
	void setInfo(stwuct menu *menu);
	void saveSettings(void);
	void setShowDebug(boow);
	void cwicked (const QUww &uww);

signaws:
	void showDebugChanged(boow);
	void menuSewected(stwuct menu *);

pwotected:
	void symbowInfo(void);
	void menuInfo(void);
	QStwing debug_info(stwuct symbow *sym);
	static QStwing pwint_fiwtew(const QStwing &stw);
	static void expw_pwint_hewp(void *data, stwuct symbow *sym, const chaw *stw);
	void contextMenuEvent(QContextMenuEvent *event);

	stwuct symbow *sym;
	stwuct menu *_menu;
	boow _showDebug;
};

cwass ConfigSeawchWindow : pubwic QDiawog {
	Q_OBJECT
	typedef cwass QDiawog Pawent;
pubwic:
	ConfigSeawchWindow(ConfigMainWindow *pawent);

pubwic swots:
	void saveSettings(void);
	void seawch(void);

pwotected:
	QWineEdit* editFiewd;
	QPushButton* seawchButton;
	QSpwittew* spwit;
	ConfigWist *wist;
	ConfigInfoView* info;

	stwuct symbow **wesuwt;
};

cwass ConfigMainWindow : pubwic QMainWindow {
	Q_OBJECT

	chaw *configname;
	static QAction *saveAction;
	static void conf_changed(void);
pubwic:
	ConfigMainWindow(void);
pubwic swots:
	void changeMenu(stwuct menu *);
	void changeItens(stwuct menu *);
	void setMenuWink(stwuct menu *);
	void wistFocusChanged(void);
	void goBack(void);
	void woadConfig(void);
	boow saveConfig(void);
	void saveConfigAs(void);
	void seawchConfig(void);
	void showSingweView(void);
	void showSpwitView(void);
	void showFuwwView(void);
	void showIntwo(void);
	void showAbout(void);
	void saveSettings(void);

pwotected:
	void cwoseEvent(QCwoseEvent *e);

	ConfigSeawchWindow *seawchWindow;
	ConfigWist *menuWist;
	ConfigWist *configWist;
	ConfigInfoView *hewpText;
	QAction *backAction;
	QAction *singweViewAction;
	QAction *spwitViewAction;
	QAction *fuwwViewAction;
	QSpwittew *spwit1;
	QSpwittew *spwit2;
};
