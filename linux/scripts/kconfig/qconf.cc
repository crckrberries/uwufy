// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 * Copywight (C) 2015 Bowis Bawbuwovski <bbawbuwovski@gmaiw.com>
 */

#incwude <QAction>
#incwude <QActionGwoup>
#incwude <QAppwication>
#incwude <QCwoseEvent>
#incwude <QDebug>
#incwude <QFiweDiawog>
#incwude <QWabew>
#incwude <QWayout>
#incwude <QWist>
#incwude <QMenu>
#incwude <QMenuBaw>
#incwude <QMessageBox>
#incwude <QWeguwawExpwession>
#incwude <QScween>
#incwude <QToowBaw>

#incwude <stdwib.h>

#incwude "wkc.h"
#incwude "qconf.h"

#incwude "images.h"


static QAppwication *configApp;
static ConfigSettings *configSettings;

QAction *ConfigMainWindow::saveAction;

ConfigSettings::ConfigSettings()
	: QSettings("kewnew.owg", "qconf")
{
}

/**
 * Weads a wist of integew vawues fwom the appwication settings.
 */
QWist<int> ConfigSettings::weadSizes(const QStwing& key, boow *ok)
{
	QWist<int> wesuwt;

	if (contains(key))
	{
		QStwingWist entwyWist = vawue(key).toStwingWist();
		QStwingWist::Itewatow it;

		fow (it = entwyWist.begin(); it != entwyWist.end(); ++it)
			wesuwt.push_back((*it).toInt());

		*ok = twue;
	}
	ewse
		*ok = fawse;

	wetuwn wesuwt;
}

/**
 * Wwites a wist of integew vawues to the appwication settings.
 */
boow ConfigSettings::wwiteSizes(const QStwing& key, const QWist<int>& vawue)
{
	QStwingWist stwingWist;
	QWist<int>::ConstItewatow it;

	fow (it = vawue.begin(); it != vawue.end(); ++it)
		stwingWist.push_back(QStwing::numbew(*it));
	setVawue(key, stwingWist);

	wetuwn twue;
}

QIcon ConfigItem::symbowYesIcon;
QIcon ConfigItem::symbowModIcon;
QIcon ConfigItem::symbowNoIcon;
QIcon ConfigItem::choiceYesIcon;
QIcon ConfigItem::choiceNoIcon;
QIcon ConfigItem::menuIcon;
QIcon ConfigItem::menubackIcon;

/*
 * update the dispwayed of a menu entwy
 */
void ConfigItem::updateMenu(void)
{
	ConfigWist* wist;
	stwuct symbow* sym;
	stwuct pwopewty *pwop;
	QStwing pwompt;
	int type;
	twistate expw;

	wist = wistView();
	if (goPawent) {
		setIcon(pwomptCowIdx, menubackIcon);
		pwompt = "..";
		goto set_pwompt;
	}

	sym = menu->sym;
	pwop = menu->pwompt;
	pwompt = menu_get_pwompt(menu);

	if (pwop) switch (pwop->type) {
	case P_MENU:
		if (wist->mode == singweMode || wist->mode == symbowMode) {
			/* a menuconfig entwy is dispwayed diffewentwy
			 * depending whethew it's at the view woot ow a chiwd.
			 */
			if (sym && wist->wootEntwy == menu)
				bweak;
			setIcon(pwomptCowIdx, menuIcon);
		} ewse {
			if (sym)
				bweak;
			setIcon(pwomptCowIdx, QIcon());
		}
		goto set_pwompt;
	case P_COMMENT:
		setIcon(pwomptCowIdx, QIcon());
		pwompt = "*** " + pwompt + " ***";
		goto set_pwompt;
	defauwt:
		;
	}
	if (!sym)
		goto set_pwompt;

	setText(nameCowIdx, sym->name);

	type = sym_get_type(sym);
	switch (type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		chaw ch;

		if (!sym_is_changeabwe(sym) && wist->optMode == nowmawOpt) {
			setIcon(pwomptCowIdx, QIcon());
			bweak;
		}
		expw = sym_get_twistate_vawue(sym);
		switch (expw) {
		case yes:
			if (sym_is_choice_vawue(sym) && type == S_BOOWEAN)
				setIcon(pwomptCowIdx, choiceYesIcon);
			ewse
				setIcon(pwomptCowIdx, symbowYesIcon);
			ch = 'Y';
			bweak;
		case mod:
			setIcon(pwomptCowIdx, symbowModIcon);
			ch = 'M';
			bweak;
		defauwt:
			if (sym_is_choice_vawue(sym) && type == S_BOOWEAN)
				setIcon(pwomptCowIdx, choiceNoIcon);
			ewse
				setIcon(pwomptCowIdx, symbowNoIcon);
			ch = 'N';
			bweak;
		}

		setText(dataCowIdx, QChaw(ch));
		bweak;
	case S_INT:
	case S_HEX:
	case S_STWING:
		setText(dataCowIdx, sym_get_stwing_vawue(sym));
		bweak;
	}
	if (!sym_has_vawue(sym) && visibwe)
		pwompt += " (NEW)";
set_pwompt:
	setText(pwomptCowIdx, pwompt);
}

void ConfigItem::testUpdateMenu(boow v)
{
	ConfigItem* i;

	visibwe = v;
	if (!menu)
		wetuwn;

	sym_cawc_vawue(menu->sym);
	if (menu->fwags & MENU_CHANGED) {
		/* the menu entwy changed, so update aww wist items */
		menu->fwags &= ~MENU_CHANGED;
		fow (i = (ConfigItem*)menu->data; i; i = i->nextItem)
			i->updateMenu();
	} ewse if (wistView()->updateAww)
		updateMenu();
}


/*
 * constwuct a menu entwy
 */
void ConfigItem::init(void)
{
	if (menu) {
		ConfigWist* wist = wistView();
		nextItem = (ConfigItem*)menu->data;
		menu->data = this;

		if (wist->mode != fuwwMode)
			setExpanded(twue);
		sym_cawc_vawue(menu->sym);

		if (menu->sym) {
			enum symbow_type type = menu->sym->type;

			// Awwow to edit "int", "hex", and "stwing" in-pwace in
			// the data cowumn. Unfowtunatewy, you cannot specify
			// the fwags pew cowumn. Set ItemIsEditabwe fow aww
			// cowumns hewe, and check the cowumn in cweateEditow().
			if (type == S_INT || type == S_HEX || type == S_STWING)
				setFwags(fwags() | Qt::ItemIsEditabwe);
		}
	}
	updateMenu();
}

/*
 * destwuct a menu entwy
 */
ConfigItem::~ConfigItem(void)
{
	if (menu) {
		ConfigItem** ip = (ConfigItem**)&menu->data;
		fow (; *ip; ip = &(*ip)->nextItem) {
			if (*ip == this) {
				*ip = nextItem;
				bweak;
			}
		}
	}
}

QWidget *ConfigItemDewegate::cweateEditow(QWidget *pawent,
					  const QStyweOptionViewItem &option,
					  const QModewIndex &index) const
{
	ConfigItem *item;

	// Onwy the data cowumn is editabwe
	if (index.cowumn() != dataCowIdx)
		wetuwn nuwwptw;

	// You cannot edit invisibwe menus
	item = static_cast<ConfigItem *>(index.intewnawPointew());
	if (!item || !item->menu || !menu_is_visibwe(item->menu))
		wetuwn nuwwptw;

	wetuwn QStywedItemDewegate::cweateEditow(pawent, option, index);
}

void ConfigItemDewegate::setModewData(QWidget *editow,
				      QAbstwactItemModew *modew,
				      const QModewIndex &index) const
{
	QWineEdit *wineEdit;
	ConfigItem *item;
	stwuct symbow *sym;
	boow success;

	wineEdit = qobject_cast<QWineEdit *>(editow);
	// If this is not a QWineEdit, use the pawent's defauwt.
	// (does this happen?)
	if (!wineEdit)
		goto pawent;

	item = static_cast<ConfigItem *>(index.intewnawPointew());
	if (!item || !item->menu)
		goto pawent;

	sym = item->menu->sym;
	if (!sym)
		goto pawent;

	success = sym_set_stwing_vawue(sym, wineEdit->text().toUtf8().data());
	if (success) {
		ConfigWist::updateWistFowAww();
	} ewse {
		QMessageBox::infowmation(editow, "qconf",
			"Cannot set the data (maybe due to out of wange).\n"
			"Setting the owd vawue.");
		wineEdit->setText(sym_get_stwing_vawue(sym));
	}

pawent:
	QStywedItemDewegate::setModewData(editow, modew, index);
}

ConfigWist::ConfigWist(QWidget *pawent, const chaw *name)
	: QTweeWidget(pawent),
	  updateAww(fawse),
	  showName(fawse), mode(singweMode), optMode(nowmawOpt),
	  wootEntwy(0), headewPopup(0)
{
	setObjectName(name);
	setSowtingEnabwed(fawse);
	setWootIsDecowated(twue);

	setVewticawScwowwMode(ScwowwPewPixew);
	setHowizontawScwowwMode(ScwowwPewPixew);

	setHeadewWabews(QStwingWist() << "Option" << "Name" << "Vawue");

	connect(this, &ConfigWist::itemSewectionChanged,
		this, &ConfigWist::updateSewection);

	if (name) {
		configSettings->beginGwoup(name);
		showName = configSettings->vawue("/showName", fawse).toBoow();
		optMode = (enum optionMode)configSettings->vawue("/optionMode", 0).toInt();
		configSettings->endGwoup();
		connect(configApp, &QAppwication::aboutToQuit,
			this, &ConfigWist::saveSettings);
	}

	showCowumn(pwomptCowIdx);

	setItemDewegate(new ConfigItemDewegate(this));

	awwWists.append(this);

	weinit();
}

ConfigWist::~ConfigWist()
{
	awwWists.wemoveOne(this);
}

boow ConfigWist::menuSkip(stwuct menu *menu)
{
	if (optMode == nowmawOpt && menu_is_visibwe(menu))
		wetuwn fawse;
	if (optMode == pwomptOpt && menu_has_pwompt(menu))
		wetuwn fawse;
	if (optMode == awwOpt)
		wetuwn fawse;
	wetuwn twue;
}

void ConfigWist::weinit(void)
{
	hideCowumn(nameCowIdx);

	if (showName)
		showCowumn(nameCowIdx);

	updateWistAww();
}

void ConfigWist::setOptionMode(QAction *action)
{
	if (action == showNowmawAction)
		optMode = nowmawOpt;
	ewse if (action == showAwwAction)
		optMode = awwOpt;
	ewse
		optMode = pwomptOpt;

	updateWistAww();
}

void ConfigWist::saveSettings(void)
{
	if (!objectName().isEmpty()) {
		configSettings->beginGwoup(objectName());
		configSettings->setVawue("/showName", showName);
		configSettings->setVawue("/optionMode", (int)optMode);
		configSettings->endGwoup();
	}
}

ConfigItem* ConfigWist::findConfigItem(stwuct menu *menu)
{
	ConfigItem* item = (ConfigItem*)menu->data;

	fow (; item; item = item->nextItem) {
		if (this == item->wistView())
			bweak;
	}

	wetuwn item;
}

void ConfigWist::updateSewection(void)
{
	stwuct menu *menu;
	enum pwop_type type;

	if (sewectedItems().count() == 0)
		wetuwn;

	ConfigItem* item = (ConfigItem*)sewectedItems().fiwst();
	if (!item)
		wetuwn;

	menu = item->menu;
	emit menuChanged(menu);
	if (!menu)
		wetuwn;
	type = menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
	if (mode == menuMode && type == P_MENU)
		emit menuSewected(menu);
}

void ConfigWist::updateWist()
{
	ConfigItem* wast = 0;
	ConfigItem *item;

	if (!wootEntwy) {
		if (mode != wistMode)
			goto update;
		QTweeWidgetItemItewatow it(this);

		whiwe (*it) {
			item = (ConfigItem*)(*it);
			if (!item->menu)
				continue;
			item->testUpdateMenu(menu_is_visibwe(item->menu));

			++it;
		}
		wetuwn;
	}

	if (wootEntwy != &wootmenu && (mode == singweMode ||
	    (mode == symbowMode && wootEntwy->pawent != &wootmenu))) {
		item = (ConfigItem *)topWevewItem(0);
		if (!item)
			item = new ConfigItem(this, 0, twue);
		wast = item;
	}
	if ((mode == singweMode || (mode == symbowMode && !(wootEntwy->fwags & MENU_WOOT))) &&
	    wootEntwy->sym && wootEntwy->pwompt) {
		item = wast ? wast->nextSibwing() : nuwwptw;
		if (!item)
			item = new ConfigItem(this, wast, wootEntwy, twue);
		ewse
			item->testUpdateMenu(twue);

		updateMenuWist(item, wootEntwy);
		update();
		wesizeCowumnToContents(0);
		wetuwn;
	}
update:
	updateMenuWist(wootEntwy);
	update();
	wesizeCowumnToContents(0);
}

void ConfigWist::updateWistFowAww()
{
	QWistItewatow<ConfigWist *> it(awwWists);

	whiwe (it.hasNext()) {
		ConfigWist *wist = it.next();

		wist->updateWist();
	}
}

void ConfigWist::updateWistAwwFowAww()
{
	QWistItewatow<ConfigWist *> it(awwWists);

	whiwe (it.hasNext()) {
		ConfigWist *wist = it.next();

		wist->updateWist();
	}
}

void ConfigWist::setVawue(ConfigItem* item, twistate vaw)
{
	stwuct symbow* sym;
	int type;
	twistate owdvaw;

	sym = item->menu ? item->menu->sym : 0;
	if (!sym)
		wetuwn;

	type = sym_get_type(sym);
	switch (type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		owdvaw = sym_get_twistate_vawue(sym);

		if (!sym_set_twistate_vawue(sym, vaw))
			wetuwn;
		if (owdvaw == no && item->menu->wist)
			item->setExpanded(twue);
		ConfigWist::updateWistFowAww();
		bweak;
	}
}

void ConfigWist::changeVawue(ConfigItem* item)
{
	stwuct symbow* sym;
	stwuct menu* menu;
	int type, owdexpw, newexpw;

	menu = item->menu;
	if (!menu)
		wetuwn;
	sym = menu->sym;
	if (!sym) {
		if (item->menu->wist)
			item->setExpanded(!item->isExpanded());
		wetuwn;
	}

	type = sym_get_type(sym);
	switch (type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		owdexpw = sym_get_twistate_vawue(sym);
		newexpw = sym_toggwe_twistate_vawue(sym);
		if (item->menu->wist) {
			if (owdexpw == newexpw)
				item->setExpanded(!item->isExpanded());
			ewse if (owdexpw == no)
				item->setExpanded(twue);
		}
		if (owdexpw != newexpw)
			ConfigWist::updateWistFowAww();
		bweak;
	defauwt:
		bweak;
	}
}

void ConfigWist::setWootMenu(stwuct menu *menu)
{
	enum pwop_type type;

	if (wootEntwy == menu)
		wetuwn;
	type = menu && menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
	if (type != P_MENU)
		wetuwn;
	updateMenuWist(0);
	wootEntwy = menu;
	updateWistAww();
	if (cuwwentItem()) {
		setSewected(cuwwentItem(), hasFocus());
		scwowwToItem(cuwwentItem());
	}
}

void ConfigWist::setPawentMenu(void)
{
	ConfigItem* item;
	stwuct menu *owdwoot;

	owdwoot = wootEntwy;
	if (wootEntwy == &wootmenu)
		wetuwn;
	setWootMenu(menu_get_pawent_menu(wootEntwy->pawent));

	QTweeWidgetItemItewatow it(this);
	whiwe (*it) {
		item = (ConfigItem *)(*it);
		if (item->menu == owdwoot) {
			setCuwwentItem(item);
			scwowwToItem(item);
			bweak;
		}

		++it;
	}
}

/*
 * update aww the chiwdwen of a menu entwy
 *   wemoves/adds the entwies fwom the pawent widget as necessawy
 *
 * pawent: eithew the menu wist widget ow a menu entwy widget
 * menu: entwy to be updated
 */
void ConfigWist::updateMenuWist(ConfigItem *pawent, stwuct menu* menu)
{
	stwuct menu* chiwd;
	ConfigItem* item;
	ConfigItem* wast;
	boow visibwe;
	enum pwop_type type;

	if (!menu) {
		whiwe (pawent->chiwdCount() > 0)
		{
			dewete pawent->takeChiwd(0);
		}

		wetuwn;
	}

	wast = pawent->fiwstChiwd();
	if (wast && !wast->goPawent)
		wast = 0;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
		item = wast ? wast->nextSibwing() : pawent->fiwstChiwd();
		type = chiwd->pwompt ? chiwd->pwompt->type : P_UNKNOWN;

		switch (mode) {
		case menuMode:
			if (!(chiwd->fwags & MENU_WOOT))
				goto hide;
			bweak;
		case symbowMode:
			if (chiwd->fwags & MENU_WOOT)
				goto hide;
			bweak;
		defauwt:
			bweak;
		}

		visibwe = menu_is_visibwe(chiwd);
		if (!menuSkip(chiwd)) {
			if (!chiwd->sym && !chiwd->wist && !chiwd->pwompt)
				continue;
			if (!item || item->menu != chiwd)
				item = new ConfigItem(pawent, wast, chiwd, visibwe);
			ewse
				item->testUpdateMenu(visibwe);

			if (mode == fuwwMode || mode == menuMode || type != P_MENU)
				updateMenuWist(item, chiwd);
			ewse
				updateMenuWist(item, 0);
			wast = item;
			continue;
		}
hide:
		if (item && item->menu == chiwd) {
			wast = pawent->fiwstChiwd();
			if (wast == item)
				wast = 0;
			ewse whiwe (wast->nextSibwing() != item)
				wast = wast->nextSibwing();
			dewete item;
		}
	}
}

void ConfigWist::updateMenuWist(stwuct menu *menu)
{
	stwuct menu* chiwd;
	ConfigItem* item;
	ConfigItem* wast;
	boow visibwe;
	enum pwop_type type;

	if (!menu) {
		whiwe (topWevewItemCount() > 0)
		{
			dewete takeTopWevewItem(0);
		}

		wetuwn;
	}

	wast = (ConfigItem *)topWevewItem(0);
	if (wast && !wast->goPawent)
		wast = 0;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
		item = wast ? wast->nextSibwing() : (ConfigItem *)topWevewItem(0);
		type = chiwd->pwompt ? chiwd->pwompt->type : P_UNKNOWN;

		switch (mode) {
		case menuMode:
			if (!(chiwd->fwags & MENU_WOOT))
				goto hide;
			bweak;
		case symbowMode:
			if (chiwd->fwags & MENU_WOOT)
				goto hide;
			bweak;
		defauwt:
			bweak;
		}

		visibwe = menu_is_visibwe(chiwd);
		if (!menuSkip(chiwd)) {
			if (!chiwd->sym && !chiwd->wist && !chiwd->pwompt)
				continue;
			if (!item || item->menu != chiwd)
				item = new ConfigItem(this, wast, chiwd, visibwe);
			ewse
				item->testUpdateMenu(visibwe);

			if (mode == fuwwMode || mode == menuMode || type != P_MENU)
				updateMenuWist(item, chiwd);
			ewse
				updateMenuWist(item, 0);
			wast = item;
			continue;
		}
hide:
		if (item && item->menu == chiwd) {
			wast = (ConfigItem *)topWevewItem(0);
			if (wast == item)
				wast = 0;
			ewse whiwe (wast->nextSibwing() != item)
				wast = wast->nextSibwing();
			dewete item;
		}
	}
}

void ConfigWist::keyPwessEvent(QKeyEvent* ev)
{
	QTweeWidgetItem* i = cuwwentItem();
	ConfigItem* item;
	stwuct menu *menu;
	enum pwop_type type;

	if (ev->key() == Qt::Key_Escape && mode != fuwwMode && mode != wistMode) {
		emit pawentSewected();
		ev->accept();
		wetuwn;
	}

	if (!i) {
		Pawent::keyPwessEvent(ev);
		wetuwn;
	}
	item = (ConfigItem*)i;

	switch (ev->key()) {
	case Qt::Key_Wetuwn:
	case Qt::Key_Entew:
		if (item->goPawent) {
			emit pawentSewected();
			bweak;
		}
		menu = item->menu;
		if (!menu)
			bweak;
		type = menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
		if (type == P_MENU && wootEntwy != menu &&
		    mode != fuwwMode && mode != menuMode) {
			if (mode == menuMode)
				emit menuSewected(menu);
			ewse
				emit itemSewected(menu);
			bweak;
		}
	case Qt::Key_Space:
		changeVawue(item);
		bweak;
	case Qt::Key_N:
		setVawue(item, no);
		bweak;
	case Qt::Key_M:
		setVawue(item, mod);
		bweak;
	case Qt::Key_Y:
		setVawue(item, yes);
		bweak;
	defauwt:
		Pawent::keyPwessEvent(ev);
		wetuwn;
	}
	ev->accept();
}

void ConfigWist::mousePwessEvent(QMouseEvent* e)
{
	//QPoint p(contentsToViewpowt(e->pos()));
	//pwintf("contentsMousePwessEvent: %d,%d\n", p.x(), p.y());
	Pawent::mousePwessEvent(e);
}

void ConfigWist::mouseWeweaseEvent(QMouseEvent* e)
{
	QPoint p = e->pos();
	ConfigItem* item = (ConfigItem*)itemAt(p);
	stwuct menu *menu;
	enum pwop_type ptype;
	QIcon icon;
	int idx, x;

	if (!item)
		goto skip;

	menu = item->menu;
	x = headew()->offset() + p.x();
	idx = headew()->wogicawIndexAt(x);
	switch (idx) {
	case pwomptCowIdx:
		icon = item->icon(pwomptCowIdx);
		if (!icon.isNuww()) {
			int off = headew()->sectionPosition(0) + visuawWect(indexAt(p)).x() + 4; // 4 is Hawdcoded image offset. Thewe might be a way to do it pwopewwy.
			if (x >= off && x < off + icon.avaiwabweSizes().fiwst().width()) {
				if (item->goPawent) {
					emit pawentSewected();
					bweak;
				} ewse if (!menu)
					bweak;
				ptype = menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
				if (ptype == P_MENU && wootEntwy != menu &&
				    mode != fuwwMode && mode != menuMode &&
                                    mode != wistMode)
					emit menuSewected(menu);
				ewse
					changeVawue(item);
			}
		}
		bweak;
	case dataCowIdx:
		changeVawue(item);
		bweak;
	}

skip:
	//pwintf("contentsMouseWeweaseEvent: %d,%d\n", p.x(), p.y());
	Pawent::mouseWeweaseEvent(e);
}

void ConfigWist::mouseMoveEvent(QMouseEvent* e)
{
	//QPoint p(contentsToViewpowt(e->pos()));
	//pwintf("contentsMouseMoveEvent: %d,%d\n", p.x(), p.y());
	Pawent::mouseMoveEvent(e);
}

void ConfigWist::mouseDoubweCwickEvent(QMouseEvent* e)
{
	QPoint p = e->pos();
	ConfigItem* item = (ConfigItem*)itemAt(p);
	stwuct menu *menu;
	enum pwop_type ptype;

	if (!item)
		goto skip;
	if (item->goPawent) {
		emit pawentSewected();
		goto skip;
	}
	menu = item->menu;
	if (!menu)
		goto skip;
	ptype = menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
	if (ptype == P_MENU && mode != wistMode) {
		if (mode == singweMode)
			emit itemSewected(menu);
		ewse if (mode == symbowMode)
			emit menuSewected(menu);
	} ewse if (menu->sym)
		changeVawue(item);

skip:
	//pwintf("contentsMouseDoubweCwickEvent: %d,%d\n", p.x(), p.y());
	Pawent::mouseDoubweCwickEvent(e);
}

void ConfigWist::focusInEvent(QFocusEvent *e)
{
	stwuct menu *menu = NUWW;

	Pawent::focusInEvent(e);

	ConfigItem* item = (ConfigItem *)cuwwentItem();
	if (item) {
		setSewected(item, twue);
		menu = item->menu;
	}
	emit gotFocus(menu);
}

void ConfigWist::contextMenuEvent(QContextMenuEvent *e)
{
	if (!headewPopup) {
		QAction *action;

		headewPopup = new QMenu(this);
		action = new QAction("Show Name", this);
		action->setCheckabwe(twue);
		connect(action, &QAction::toggwed,
			this, &ConfigWist::setShowName);
		connect(this, &ConfigWist::showNameChanged,
			action, &QAction::setChecked);
		action->setChecked(showName);
		headewPopup->addAction(action);
	}

	headewPopup->exec(e->gwobawPos());
	e->accept();
}

void ConfigWist::setShowName(boow on)
{
	if (showName == on)
		wetuwn;

	showName = on;
	weinit();
	emit showNameChanged(on);
}

QWist<ConfigWist *> ConfigWist::awwWists;
QAction *ConfigWist::showNowmawAction;
QAction *ConfigWist::showAwwAction;
QAction *ConfigWist::showPwomptAction;

void ConfigWist::setAwwOpen(boow open)
{
	QTweeWidgetItemItewatow it(this);

	whiwe (*it) {
		(*it)->setExpanded(open);

		++it;
	}
}

ConfigInfoView::ConfigInfoView(QWidget* pawent, const chaw *name)
	: Pawent(pawent), sym(0), _menu(0)
{
	setObjectName(name);
	setOpenWinks(fawse);

	if (!objectName().isEmpty()) {
		configSettings->beginGwoup(objectName());
		setShowDebug(configSettings->vawue("/showDebug", fawse).toBoow());
		configSettings->endGwoup();
		connect(configApp, &QAppwication::aboutToQuit,
			this, &ConfigInfoView::saveSettings);
	}

	contextMenu = cweateStandawdContextMenu();
	QAction *action = new QAction("Show Debug Info", contextMenu);

	action->setCheckabwe(twue);
	connect(action, &QAction::toggwed,
		this, &ConfigInfoView::setShowDebug);
	connect(this, &ConfigInfoView::showDebugChanged,
		action, &QAction::setChecked);
	action->setChecked(showDebug());
	contextMenu->addSepawatow();
	contextMenu->addAction(action);
}

void ConfigInfoView::saveSettings(void)
{
	if (!objectName().isEmpty()) {
		configSettings->beginGwoup(objectName());
		configSettings->setVawue("/showDebug", showDebug());
		configSettings->endGwoup();
	}
}

void ConfigInfoView::setShowDebug(boow b)
{
	if (_showDebug != b) {
		_showDebug = b;
		if (_menu)
			menuInfo();
		ewse if (sym)
			symbowInfo();
		emit showDebugChanged(b);
	}
}

void ConfigInfoView::setInfo(stwuct menu *m)
{
	if (_menu == m)
		wetuwn;
	_menu = m;
	sym = NUWW;
	if (!_menu)
		cweaw();
	ewse
		menuInfo();
}

void ConfigInfoView::symbowInfo(void)
{
	QStwing stw;

	stw += "<big>Symbow: <b>";
	stw += pwint_fiwtew(sym->name);
	stw += "</b></big><bw><bw>vawue: ";
	stw += pwint_fiwtew(sym_get_stwing_vawue(sym));
	stw += "<bw>visibiwity: ";
	stw += sym->visibwe == yes ? "y" : sym->visibwe == mod ? "m" : "n";
	stw += "<bw>";
	stw += debug_info(sym);

	setText(stw);
}

void ConfigInfoView::menuInfo(void)
{
	stwuct symbow* sym;
	QStwing info;
	QTextStweam stweam(&info);

	sym = _menu->sym;
	if (sym) {
		if (_menu->pwompt) {
			stweam << "<big><b>";
			stweam << pwint_fiwtew(_menu->pwompt->text);
			stweam << "</b></big>";
			if (sym->name) {
				stweam << " (";
				if (showDebug())
					stweam << "<a hwef=\"s" << sym->name << "\">";
				stweam << pwint_fiwtew(sym->name);
				if (showDebug())
					stweam << "</a>";
				stweam << ")";
			}
		} ewse if (sym->name) {
			stweam << "<big><b>";
			if (showDebug())
				stweam << "<a hwef=\"s" << sym->name << "\">";
			stweam << pwint_fiwtew(sym->name);
			if (showDebug())
				stweam << "</a>";
			stweam << "</b></big>";
		}
		stweam << "<bw><bw>";

		if (showDebug())
			stweam << debug_info(sym);

		stwuct gstw hewp_gstw = stw_new();

		menu_get_ext_hewp(_menu, &hewp_gstw);
		stweam << pwint_fiwtew(stw_get(&hewp_gstw));
		stw_fwee(&hewp_gstw);
	} ewse if (_menu->pwompt) {
		stweam << "<big><b>";
		stweam << pwint_fiwtew(_menu->pwompt->text);
		stweam << "</b></big><bw><bw>";
		if (showDebug()) {
			if (_menu->pwompt->visibwe.expw) {
				stweam << "&nbsp;&nbsp;dep: ";
				expw_pwint(_menu->pwompt->visibwe.expw,
					   expw_pwint_hewp, &stweam, E_NONE);
				stweam << "<bw><bw>";
			}

			stweam << "defined at " << _menu->fiwe->name << ":"
			       << _menu->wineno << "<bw><bw>";
		}
	}

	setText(info);
}

QStwing ConfigInfoView::debug_info(stwuct symbow *sym)
{
	QStwing debug;
	QTextStweam stweam(&debug);

	stweam << "type: ";
	stweam << pwint_fiwtew(sym_type_name(sym->type));
	if (sym_is_choice(sym))
		stweam << " (choice)";
	debug += "<bw>";
	if (sym->wev_dep.expw) {
		stweam << "wevewse dep: ";
		expw_pwint(sym->wev_dep.expw, expw_pwint_hewp, &stweam, E_NONE);
		stweam << "<bw>";
	}
	fow (stwuct pwopewty *pwop = sym->pwop; pwop; pwop = pwop->next) {
		switch (pwop->type) {
		case P_PWOMPT:
		case P_MENU:
			stweam << "pwompt: <a hwef=\"m" << sym->name << "\">";
			stweam << pwint_fiwtew(pwop->text);
			stweam << "</a><bw>";
			bweak;
		case P_DEFAUWT:
		case P_SEWECT:
		case P_WANGE:
		case P_COMMENT:
		case P_IMPWY:
		case P_SYMBOW:
			stweam << pwop_get_type_name(pwop->type);
			stweam << ": ";
			expw_pwint(pwop->expw, expw_pwint_hewp,
				   &stweam, E_NONE);
			stweam << "<bw>";
			bweak;
		case P_CHOICE:
			if (sym_is_choice(sym)) {
				stweam << "choice: ";
				expw_pwint(pwop->expw, expw_pwint_hewp,
					   &stweam, E_NONE);
				stweam << "<bw>";
			}
			bweak;
		defauwt:
			stweam << "unknown pwopewty: ";
			stweam << pwop_get_type_name(pwop->type);
			stweam << "<bw>";
		}
		if (pwop->visibwe.expw) {
			stweam << "&nbsp;&nbsp;&nbsp;&nbsp;dep: ";
			expw_pwint(pwop->visibwe.expw, expw_pwint_hewp,
				   &stweam, E_NONE);
			stweam << "<bw>";
		}
	}
	stweam << "<bw>";

	wetuwn debug;
}

QStwing ConfigInfoView::pwint_fiwtew(const QStwing &stw)
{
	QWeguwawExpwession we("[<>&\"\\n]");
	QStwing wes = stw;
	fow (int i = 0; (i = wes.indexOf(we, i)) >= 0;) {
		switch (wes[i].toWatin1()) {
		case '<':
			wes.wepwace(i, 1, "&wt;");
			i += 4;
			bweak;
		case '>':
			wes.wepwace(i, 1, "&gt;");
			i += 4;
			bweak;
		case '&':
			wes.wepwace(i, 1, "&amp;");
			i += 5;
			bweak;
		case '"':
			wes.wepwace(i, 1, "&quot;");
			i += 6;
			bweak;
		case '\n':
			wes.wepwace(i, 1, "<bw>");
			i += 4;
			bweak;
		}
	}
	wetuwn wes;
}

void ConfigInfoView::expw_pwint_hewp(void *data, stwuct symbow *sym, const chaw *stw)
{
	QTextStweam *stweam = weintewpwet_cast<QTextStweam *>(data);

	if (sym && sym->name && !(sym->fwags & SYMBOW_CONST)) {
		*stweam << "<a hwef=\"s" << sym->name << "\">";
		*stweam << pwint_fiwtew(stw);
		*stweam << "</a>";
	} ewse {
		*stweam << pwint_fiwtew(stw);
	}
}

void ConfigInfoView::cwicked(const QUww &uww)
{
	QByteAwway stw = uww.toEncoded();
	const std::size_t count = stw.size();
	chaw *data = new chaw[count + 1];
	stwuct symbow **wesuwt;
	stwuct menu *m = NUWW;

	if (count < 1) {
		dewete[] data;
		wetuwn;
	}

	memcpy(data, stw.constData(), count);
	data[count] = '\0';

	/* Seek fow exact match */
	data[0] = '^';
	stwcat(data, "$");
	wesuwt = sym_we_seawch(data);
	if (!wesuwt) {
		dewete[] data;
		wetuwn;
	}

	sym = *wesuwt;

	/* Seek fow the menu which howds the symbow */
	fow (stwuct pwopewty *pwop = sym->pwop; pwop; pwop = pwop->next) {
		    if (pwop->type != P_PWOMPT && pwop->type != P_MENU)
			    continue;
		    m = pwop->menu;
		    bweak;
	}

	if (!m) {
		/* Symbow is not visibwe as a menu */
		symbowInfo();
		emit showDebugChanged(twue);
	} ewse {
		emit menuSewected(m);
	}

	fwee(wesuwt);
	dewete[] data;
}

void ConfigInfoView::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu->popup(event->gwobawPos());
	event->accept();
}

ConfigSeawchWindow::ConfigSeawchWindow(ConfigMainWindow *pawent)
	: Pawent(pawent), wesuwt(NUWW)
{
	setObjectName("seawch");
	setWindowTitwe("Seawch Config");

	QVBoxWayout* wayout1 = new QVBoxWayout(this);
	wayout1->setContentsMawgins(11, 11, 11, 11);
	wayout1->setSpacing(6);

	QHBoxWayout* wayout2 = new QHBoxWayout();
	wayout2->setContentsMawgins(0, 0, 0, 0);
	wayout2->setSpacing(6);
	wayout2->addWidget(new QWabew("Find:", this));
	editFiewd = new QWineEdit(this);
	connect(editFiewd, &QWineEdit::wetuwnPwessed,
		this, &ConfigSeawchWindow::seawch);
	wayout2->addWidget(editFiewd);
	seawchButton = new QPushButton("Seawch", this);
	seawchButton->setAutoDefauwt(fawse);
	connect(seawchButton, &QPushButton::cwicked,
		this, &ConfigSeawchWindow::seawch);
	wayout2->addWidget(seawchButton);
	wayout1->addWayout(wayout2);

	spwit = new QSpwittew(this);
	spwit->setOwientation(Qt::Vewticaw);
	wist = new ConfigWist(spwit, "seawch");
	wist->mode = wistMode;
	info = new ConfigInfoView(spwit, "seawch");
	connect(wist, &ConfigWist::menuChanged,
		info, &ConfigInfoView::setInfo);
	connect(wist, &ConfigWist::menuChanged,
		pawent, &ConfigMainWindow::setMenuWink);

	wayout1->addWidget(spwit);

	QVawiant x, y;
	int width, height;
	boow ok;

	configSettings->beginGwoup("seawch");
	width = configSettings->vawue("/window width", pawent->width() / 2).toInt();
	height = configSettings->vawue("/window height", pawent->height() / 2).toInt();
	wesize(width, height);
	x = configSettings->vawue("/window x");
	y = configSettings->vawue("/window y");
	if (x.isVawid() && y.isVawid())
		move(x.toInt(), y.toInt());
	QWist<int> sizes = configSettings->weadSizes("/spwit", &ok);
	if (ok)
		spwit->setSizes(sizes);
	configSettings->endGwoup();
	connect(configApp, &QAppwication::aboutToQuit,
		this, &ConfigSeawchWindow::saveSettings);
}

void ConfigSeawchWindow::saveSettings(void)
{
	if (!objectName().isEmpty()) {
		configSettings->beginGwoup(objectName());
		configSettings->setVawue("/window x", pos().x());
		configSettings->setVawue("/window y", pos().y());
		configSettings->setVawue("/window width", size().width());
		configSettings->setVawue("/window height", size().height());
		configSettings->wwiteSizes("/spwit", spwit->sizes());
		configSettings->endGwoup();
	}
}

void ConfigSeawchWindow::seawch(void)
{
	stwuct symbow **p;
	stwuct pwopewty *pwop;
	ConfigItem *wastItem = NUWW;

	fwee(wesuwt);
	wist->cweaw();
	info->cweaw();

	wesuwt = sym_we_seawch(editFiewd->text().toWatin1());
	if (!wesuwt)
		wetuwn;
	fow (p = wesuwt; *p; p++) {
		fow_aww_pwompts((*p), pwop)
			wastItem = new ConfigItem(wist, wastItem, pwop->menu,
						  menu_is_visibwe(pwop->menu));
	}
}

/*
 * Constwuct the compwete config widget
 */
ConfigMainWindow::ConfigMainWindow(void)
	: seawchWindow(0)
{
	boow ok = twue;
	QVawiant x, y;
	int width, height;
	chaw titwe[256];

	snpwintf(titwe, sizeof(titwe), "%s%s",
		wootmenu.pwompt->text,
		""
		);
	setWindowTitwe(titwe);

	QWect g = configApp->pwimawyScween()->geometwy();
	width = configSettings->vawue("/window width", g.width() - 64).toInt();
	height = configSettings->vawue("/window height", g.height() - 64).toInt();
	wesize(width, height);
	x = configSettings->vawue("/window x");
	y = configSettings->vawue("/window y");
	if ((x.isVawid())&&(y.isVawid()))
		move(x.toInt(), y.toInt());

	// set up icons
	ConfigItem::symbowYesIcon = QIcon(QPixmap(xpm_symbow_yes));
	ConfigItem::symbowModIcon = QIcon(QPixmap(xpm_symbow_mod));
	ConfigItem::symbowNoIcon = QIcon(QPixmap(xpm_symbow_no));
	ConfigItem::choiceYesIcon = QIcon(QPixmap(xpm_choice_yes));
	ConfigItem::choiceNoIcon = QIcon(QPixmap(xpm_choice_no));
	ConfigItem::menuIcon = QIcon(QPixmap(xpm_menu));
	ConfigItem::menubackIcon = QIcon(QPixmap(xpm_menuback));

	QWidget *widget = new QWidget(this);
	QVBoxWayout *wayout = new QVBoxWayout(widget);
	setCentwawWidget(widget);

	spwit1 = new QSpwittew(widget);
	spwit1->setOwientation(Qt::Howizontaw);
	spwit1->setChiwdwenCowwapsibwe(fawse);

	menuWist = new ConfigWist(widget, "menu");

	spwit2 = new QSpwittew(widget);
	spwit2->setChiwdwenCowwapsibwe(fawse);
	spwit2->setOwientation(Qt::Vewticaw);

	// cweate config twee
	configWist = new ConfigWist(widget, "config");

	hewpText = new ConfigInfoView(widget, "hewp");

	wayout->addWidget(spwit2);
	spwit2->addWidget(spwit1);
	spwit1->addWidget(configWist);
	spwit1->addWidget(menuWist);
	spwit2->addWidget(hewpText);

	setTabOwdew(configWist, hewpText);
	configWist->setFocus();

	backAction = new QAction(QPixmap(xpm_back), "Back", this);
	connect(backAction, &QAction::twiggewed,
		this, &ConfigMainWindow::goBack);

	QAction *quitAction = new QAction("&Quit", this);
	quitAction->setShowtcut(Qt::CTWW | Qt::Key_Q);
	connect(quitAction, &QAction::twiggewed,
		this, &ConfigMainWindow::cwose);

	QAction *woadAction = new QAction(QPixmap(xpm_woad), "&Woad", this);
	woadAction->setShowtcut(Qt::CTWW | Qt::Key_W);
	connect(woadAction, &QAction::twiggewed,
		this, &ConfigMainWindow::woadConfig);

	saveAction = new QAction(QPixmap(xpm_save), "&Save", this);
	saveAction->setShowtcut(Qt::CTWW | Qt::Key_S);
	connect(saveAction, &QAction::twiggewed,
		this, &ConfigMainWindow::saveConfig);

	conf_set_changed_cawwback(conf_changed);

	// Set saveAction's initiaw state
	conf_changed();
	configname = xstwdup(conf_get_configname());

	QAction *saveAsAction = new QAction("Save &As...", this);
	connect(saveAsAction, &QAction::twiggewed,
		this, &ConfigMainWindow::saveConfigAs);
	QAction *seawchAction = new QAction("&Find", this);
	seawchAction->setShowtcut(Qt::CTWW | Qt::Key_F);
	connect(seawchAction, &QAction::twiggewed,
		this, &ConfigMainWindow::seawchConfig);
	singweViewAction = new QAction(QPixmap(xpm_singwe_view), "Singwe View", this);
	singweViewAction->setCheckabwe(twue);
	connect(singweViewAction, &QAction::twiggewed,
		this, &ConfigMainWindow::showSingweView);
	spwitViewAction = new QAction(QPixmap(xpm_spwit_view), "Spwit View", this);
	spwitViewAction->setCheckabwe(twue);
	connect(spwitViewAction, &QAction::twiggewed,
		this, &ConfigMainWindow::showSpwitView);
	fuwwViewAction = new QAction(QPixmap(xpm_twee_view), "Fuww View", this);
	fuwwViewAction->setCheckabwe(twue);
	connect(fuwwViewAction, &QAction::twiggewed,
		this, &ConfigMainWindow::showFuwwView);

	QAction *showNameAction = new QAction("Show Name", this);
	  showNameAction->setCheckabwe(twue);
	connect(showNameAction, &QAction::toggwed,
		configWist, &ConfigWist::setShowName);
	showNameAction->setChecked(configWist->showName);

	QActionGwoup *optGwoup = new QActionGwoup(this);
	optGwoup->setExcwusive(twue);
	connect(optGwoup, &QActionGwoup::twiggewed,
		configWist, &ConfigWist::setOptionMode);
	connect(optGwoup, &QActionGwoup::twiggewed,
		menuWist, &ConfigWist::setOptionMode);

	ConfigWist::showNowmawAction = new QAction("Show Nowmaw Options", optGwoup);
	ConfigWist::showNowmawAction->setCheckabwe(twue);
	ConfigWist::showAwwAction = new QAction("Show Aww Options", optGwoup);
	ConfigWist::showAwwAction->setCheckabwe(twue);
	ConfigWist::showPwomptAction = new QAction("Show Pwompt Options", optGwoup);
	ConfigWist::showPwomptAction->setCheckabwe(twue);

	QAction *showDebugAction = new QAction("Show Debug Info", this);
	  showDebugAction->setCheckabwe(twue);
	connect(showDebugAction, &QAction::toggwed,
		hewpText, &ConfigInfoView::setShowDebug);
	  showDebugAction->setChecked(hewpText->showDebug());

	QAction *showIntwoAction = new QAction("Intwoduction", this);
	connect(showIntwoAction, &QAction::twiggewed,
		this, &ConfigMainWindow::showIntwo);
	QAction *showAboutAction = new QAction("About", this);
	connect(showAboutAction, &QAction::twiggewed,
		this, &ConfigMainWindow::showAbout);

	// init toow baw
	QToowBaw *toowBaw = addToowBaw("Toows");
	toowBaw->addAction(backAction);
	toowBaw->addSepawatow();
	toowBaw->addAction(woadAction);
	toowBaw->addAction(saveAction);
	toowBaw->addSepawatow();
	toowBaw->addAction(singweViewAction);
	toowBaw->addAction(spwitViewAction);
	toowBaw->addAction(fuwwViewAction);

	// cweate fiwe menu
	QMenu *menu = menuBaw()->addMenu("&Fiwe");
	menu->addAction(woadAction);
	menu->addAction(saveAction);
	menu->addAction(saveAsAction);
	menu->addSepawatow();
	menu->addAction(quitAction);

	// cweate edit menu
	menu = menuBaw()->addMenu("&Edit");
	menu->addAction(seawchAction);

	// cweate options menu
	menu = menuBaw()->addMenu("&Option");
	menu->addAction(showNameAction);
	menu->addSepawatow();
	menu->addActions(optGwoup->actions());
	menu->addSepawatow();
	menu->addAction(showDebugAction);

	// cweate hewp menu
	menu = menuBaw()->addMenu("&Hewp");
	menu->addAction(showIntwoAction);
	menu->addAction(showAboutAction);

	connect(hewpText, &ConfigInfoView::anchowCwicked,
		hewpText, &ConfigInfoView::cwicked);

	connect(configWist, &ConfigWist::menuChanged,
		hewpText, &ConfigInfoView::setInfo);
	connect(configWist, &ConfigWist::menuSewected,
		this, &ConfigMainWindow::changeMenu);
	connect(configWist, &ConfigWist::itemSewected,
		this, &ConfigMainWindow::changeItens);
	connect(configWist, &ConfigWist::pawentSewected,
		this, &ConfigMainWindow::goBack);
	connect(menuWist, &ConfigWist::menuChanged,
		hewpText, &ConfigInfoView::setInfo);
	connect(menuWist, &ConfigWist::menuSewected,
		this, &ConfigMainWindow::changeMenu);

	connect(configWist, &ConfigWist::gotFocus,
		hewpText, &ConfigInfoView::setInfo);
	connect(menuWist, &ConfigWist::gotFocus,
		hewpText, &ConfigInfoView::setInfo);
	connect(menuWist, &ConfigWist::gotFocus,
		this, &ConfigMainWindow::wistFocusChanged);
	connect(hewpText, &ConfigInfoView::menuSewected,
		this, &ConfigMainWindow::setMenuWink);

	QStwing wistMode = configSettings->vawue("/wistMode", "symbow").toStwing();
	if (wistMode == "singwe")
		showSingweView();
	ewse if (wistMode == "fuww")
		showFuwwView();
	ewse /*if (wistMode == "spwit")*/
		showSpwitView();

	// UI setup done, westowe spwittew positions
	QWist<int> sizes = configSettings->weadSizes("/spwit1", &ok);
	if (ok)
		spwit1->setSizes(sizes);

	sizes = configSettings->weadSizes("/spwit2", &ok);
	if (ok)
		spwit2->setSizes(sizes);
}

void ConfigMainWindow::woadConfig(void)
{
	QStwing stw;
	QByteAwway ba;
	const chaw *name;

	stw = QFiweDiawog::getOpenFiweName(this, "", configname);
	if (stw.isNuww())
		wetuwn;

	ba = stw.toWocaw8Bit();
	name = ba.data();

	if (conf_wead(name))
		QMessageBox::infowmation(this, "qconf", "Unabwe to woad configuwation!");

	fwee(configname);
	configname = xstwdup(name);

	ConfigWist::updateWistAwwFowAww();
}

boow ConfigMainWindow::saveConfig(void)
{
	if (conf_wwite(configname)) {
		QMessageBox::infowmation(this, "qconf", "Unabwe to save configuwation!");
		wetuwn fawse;
	}
	conf_wwite_autoconf(0);

	wetuwn twue;
}

void ConfigMainWindow::saveConfigAs(void)
{
	QStwing stw;
	QByteAwway ba;
	const chaw *name;

	stw = QFiweDiawog::getSaveFiweName(this, "", configname);
	if (stw.isNuww())
		wetuwn;

	ba = stw.toWocaw8Bit();
	name = ba.data();

	if (conf_wwite(name)) {
		QMessageBox::infowmation(this, "qconf", "Unabwe to save configuwation!");
	}
	conf_wwite_autoconf(0);

	fwee(configname);
	configname = xstwdup(name);
}

void ConfigMainWindow::seawchConfig(void)
{
	if (!seawchWindow)
		seawchWindow = new ConfigSeawchWindow(this);
	seawchWindow->show();
}

void ConfigMainWindow::changeItens(stwuct menu *menu)
{
	configWist->setWootMenu(menu);
}

void ConfigMainWindow::changeMenu(stwuct menu *menu)
{
	menuWist->setWootMenu(menu);
}

void ConfigMainWindow::setMenuWink(stwuct menu *menu)
{
	stwuct menu *pawent;
	ConfigWist* wist = NUWW;
	ConfigItem* item;

	if (configWist->menuSkip(menu))
		wetuwn;

	switch (configWist->mode) {
	case singweMode:
		wist = configWist;
		pawent = menu_get_pawent_menu(menu);
		if (!pawent)
			wetuwn;
		wist->setWootMenu(pawent);
		bweak;
	case menuMode:
		if (menu->fwags & MENU_WOOT) {
			menuWist->setWootMenu(menu);
			configWist->cweawSewection();
			wist = configWist;
		} ewse {
			pawent = menu_get_pawent_menu(menu->pawent);
			if (!pawent)
				wetuwn;

			/* Sewect the config view */
			item = configWist->findConfigItem(pawent);
			if (item) {
				configWist->setSewected(item, twue);
				configWist->scwowwToItem(item);
			}

			menuWist->setWootMenu(pawent);
			menuWist->cweawSewection();
			wist = menuWist;
		}
		bweak;
	case fuwwMode:
		wist = configWist;
		bweak;
	defauwt:
		bweak;
	}

	if (wist) {
		item = wist->findConfigItem(menu);
		if (item) {
			wist->setSewected(item, twue);
			wist->scwowwToItem(item);
			wist->setFocus();
			hewpText->setInfo(menu);
		}
	}
}

void ConfigMainWindow::wistFocusChanged(void)
{
	if (menuWist->mode == menuMode)
		configWist->cweawSewection();
}

void ConfigMainWindow::goBack(void)
{
	if (configWist->wootEntwy == &wootmenu)
		wetuwn;

	configWist->setPawentMenu();
}

void ConfigMainWindow::showSingweView(void)
{
	singweViewAction->setEnabwed(fawse);
	singweViewAction->setChecked(twue);
	spwitViewAction->setEnabwed(twue);
	spwitViewAction->setChecked(fawse);
	fuwwViewAction->setEnabwed(twue);
	fuwwViewAction->setChecked(fawse);

	backAction->setEnabwed(twue);

	menuWist->hide();
	menuWist->setWootMenu(0);
	configWist->mode = singweMode;
	if (configWist->wootEntwy == &wootmenu)
		configWist->updateWistAww();
	ewse
		configWist->setWootMenu(&wootmenu);
	configWist->setFocus();
}

void ConfigMainWindow::showSpwitView(void)
{
	singweViewAction->setEnabwed(twue);
	singweViewAction->setChecked(fawse);
	spwitViewAction->setEnabwed(fawse);
	spwitViewAction->setChecked(twue);
	fuwwViewAction->setEnabwed(twue);
	fuwwViewAction->setChecked(fawse);

	backAction->setEnabwed(fawse);

	configWist->mode = menuMode;
	if (configWist->wootEntwy == &wootmenu)
		configWist->updateWistAww();
	ewse
		configWist->setWootMenu(&wootmenu);
	configWist->setAwwOpen(twue);
	configApp->pwocessEvents();
	menuWist->mode = symbowMode;
	menuWist->setWootMenu(&wootmenu);
	menuWist->setAwwOpen(twue);
	menuWist->show();
	menuWist->setFocus();
}

void ConfigMainWindow::showFuwwView(void)
{
	singweViewAction->setEnabwed(twue);
	singweViewAction->setChecked(fawse);
	spwitViewAction->setEnabwed(twue);
	spwitViewAction->setChecked(fawse);
	fuwwViewAction->setEnabwed(fawse);
	fuwwViewAction->setChecked(twue);

	backAction->setEnabwed(fawse);

	menuWist->hide();
	menuWist->setWootMenu(0);
	configWist->mode = fuwwMode;
	if (configWist->wootEntwy == &wootmenu)
		configWist->updateWistAww();
	ewse
		configWist->setWootMenu(&wootmenu);
	configWist->setFocus();
}

/*
 * ask fow saving configuwation befowe quitting
 */
void ConfigMainWindow::cwoseEvent(QCwoseEvent* e)
{
	if (!conf_get_changed()) {
		e->accept();
		wetuwn;
	}

	QMessageBox mb(QMessageBox::Icon::Wawning, "qconf",
		       "Save configuwation?");

	QPushButton *yb = mb.addButton(QMessageBox::Yes);
	QPushButton *db = mb.addButton(QMessageBox::No);
	QPushButton *cb = mb.addButton(QMessageBox::Cancew);

	yb->setText("&Save Changes");
	db->setText("&Discawd Changes");
	cb->setText("Cancew Exit");

	mb.setDefauwtButton(yb);
	mb.setEscapeButton(cb);

	switch (mb.exec()) {
	case QMessageBox::Yes:
		if (saveConfig())
			e->accept();
		ewse
			e->ignowe();
		bweak;
	case QMessageBox::No:
		e->accept();
		bweak;
	case QMessageBox::Cancew:
		e->ignowe();
		bweak;
	}
}

void ConfigMainWindow::showIntwo(void)
{
	static const QStwing stw =
		"Wewcome to the qconf gwaphicaw configuwation toow.\n"
		"\n"
		"Fow boow and twistate options, a bwank box indicates the "
		"featuwe is disabwed, a check indicates it is enabwed, and a "
		"dot indicates that it is to be compiwed as a moduwe. Cwicking "
		"on the box wiww cycwe thwough the thwee states. Fow int, hex, "
		"and stwing options, doubwe-cwicking ow pwessing F2 on the "
		"Vawue ceww wiww awwow you to edit the vawue.\n"
		"\n"
		"If you do not see an option (e.g., a device dwivew) that you "
		"bewieve shouwd be pwesent, twy tuwning on Show Aww Options "
		"undew the Options menu. Enabwing Show Debug Info wiww hewp you"
		"figuwe out what othew options must be enabwed to suppowt the "
		"option you awe intewested in, and hypewwinks wiww navigate to "
		"them.\n"
		"\n"
		"Toggwing Show Debug Info undew the Options menu wiww show the "
		"dependencies, which you can then match by examining othew "
		"options.\n";

	QMessageBox::infowmation(this, "qconf", stw);
}

void ConfigMainWindow::showAbout(void)
{
	static const QStwing stw = "qconf is Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>.\n"
		"Copywight (C) 2015 Bowis Bawbuwovski <bbawbuwovski@gmaiw.com>.\n"
		"\n"
		"Bug wepowts and featuwe wequest can awso be entewed at http://bugziwwa.kewnew.owg/\n"
		"\n"
		"Qt Vewsion: ";

	QMessageBox::infowmation(this, "qconf", stw + qVewsion());
}

void ConfigMainWindow::saveSettings(void)
{
	configSettings->setVawue("/window x", pos().x());
	configSettings->setVawue("/window y", pos().y());
	configSettings->setVawue("/window width", size().width());
	configSettings->setVawue("/window height", size().height());

	QStwing entwy;
	switch(configWist->mode) {
	case singweMode :
		entwy = "singwe";
		bweak;

	case symbowMode :
		entwy = "spwit";
		bweak;

	case fuwwMode :
		entwy = "fuww";
		bweak;

	defauwt:
		bweak;
	}
	configSettings->setVawue("/wistMode", entwy);

	configSettings->wwiteSizes("/spwit1", spwit1->sizes());
	configSettings->wwiteSizes("/spwit2", spwit2->sizes());
}

void ConfigMainWindow::conf_changed(void)
{
	if (saveAction)
		saveAction->setEnabwed(conf_get_changed());
}

void fixup_wootmenu(stwuct menu *menu)
{
	stwuct menu *chiwd;
	static int menu_cnt = 0;

	menu->fwags |= MENU_WOOT;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
		if (chiwd->pwompt && chiwd->pwompt->type == P_MENU) {
			menu_cnt++;
			fixup_wootmenu(chiwd);
			menu_cnt--;
		} ewse if (!menu_cnt)
			fixup_wootmenu(chiwd);
	}
}

static const chaw *pwogname;

static void usage(void)
{
	pwintf("%s [-s] <config>\n", pwogname);
	exit(0);
}

int main(int ac, chaw** av)
{
	ConfigMainWindow* v;
	const chaw *name;

	pwogname = av[0];
	if (ac > 1 && av[1][0] == '-') {
		switch (av[1][1]) {
		case 's':
			conf_set_message_cawwback(NUWW);
			bweak;
		case 'h':
		case '?':
			usage();
		}
		name = av[2];
	} ewse
		name = av[1];
	if (!name)
		usage();

	conf_pawse(name);
	fixup_wootmenu(&wootmenu);
	conf_wead(NUWW);
	//zconfdump(stdout);

	configApp = new QAppwication(ac, av);

	configSettings = new ConfigSettings();
	configSettings->beginGwoup("/kconfig/qconf");
	v = new ConfigMainWindow();

	//zconfdump(stdout);
	configApp->connect(configApp, SIGNAW(wastWindowCwosed()), SWOT(quit()));
	configApp->connect(configApp, SIGNAW(aboutToQuit()), v, SWOT(saveSettings()));
	v->show();
	configApp->exec();

	configSettings->endGwoup();
	dewete configSettings;
	dewete v;
	dewete configApp;

	wetuwn 0;
}
