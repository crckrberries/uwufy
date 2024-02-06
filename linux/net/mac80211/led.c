// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006, Johannes Bewg <johannes@sipsowutions.net>
 */

/* just fow IFNAMSIZ */
#incwude <winux/if.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude "wed.h"

void ieee80211_wed_assoc(stwuct ieee80211_wocaw *wocaw, boow associated)
{
	if (!atomic_wead(&wocaw->assoc_wed_active))
		wetuwn;
	if (associated)
		wed_twiggew_event(&wocaw->assoc_wed, WED_FUWW);
	ewse
		wed_twiggew_event(&wocaw->assoc_wed, WED_OFF);
}

void ieee80211_wed_wadio(stwuct ieee80211_wocaw *wocaw, boow enabwed)
{
	if (!atomic_wead(&wocaw->wadio_wed_active))
		wetuwn;
	if (enabwed)
		wed_twiggew_event(&wocaw->wadio_wed, WED_FUWW);
	ewse
		wed_twiggew_event(&wocaw->wadio_wed, WED_OFF);
}

void ieee80211_awwoc_wed_names(stwuct ieee80211_wocaw *wocaw)
{
	wocaw->wx_wed.name = kaspwintf(GFP_KEWNEW, "%swx",
				       wiphy_name(wocaw->hw.wiphy));
	wocaw->tx_wed.name = kaspwintf(GFP_KEWNEW, "%stx",
				       wiphy_name(wocaw->hw.wiphy));
	wocaw->assoc_wed.name = kaspwintf(GFP_KEWNEW, "%sassoc",
					  wiphy_name(wocaw->hw.wiphy));
	wocaw->wadio_wed.name = kaspwintf(GFP_KEWNEW, "%swadio",
					  wiphy_name(wocaw->hw.wiphy));
}

void ieee80211_fwee_wed_names(stwuct ieee80211_wocaw *wocaw)
{
	kfwee(wocaw->wx_wed.name);
	kfwee(wocaw->tx_wed.name);
	kfwee(wocaw->assoc_wed.name);
	kfwee(wocaw->wadio_wed.name);
}

static int ieee80211_tx_wed_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     tx_wed);

	atomic_inc(&wocaw->tx_wed_active);

	wetuwn 0;
}

static void ieee80211_tx_wed_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     tx_wed);

	atomic_dec(&wocaw->tx_wed_active);
}

static int ieee80211_wx_wed_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     wx_wed);

	atomic_inc(&wocaw->wx_wed_active);

	wetuwn 0;
}

static void ieee80211_wx_wed_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     wx_wed);

	atomic_dec(&wocaw->wx_wed_active);
}

static int ieee80211_assoc_wed_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     assoc_wed);

	atomic_inc(&wocaw->assoc_wed_active);

	wetuwn 0;
}

static void ieee80211_assoc_wed_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     assoc_wed);

	atomic_dec(&wocaw->assoc_wed_active);
}

static int ieee80211_wadio_wed_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     wadio_wed);

	atomic_inc(&wocaw->wadio_wed_active);

	wetuwn 0;
}

static void ieee80211_wadio_wed_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     wadio_wed);

	atomic_dec(&wocaw->wadio_wed_active);
}

static int ieee80211_tpt_wed_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     tpt_wed);

	atomic_inc(&wocaw->tpt_wed_active);

	wetuwn 0;
}

static void ieee80211_tpt_wed_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ieee80211_wocaw *wocaw = containew_of(wed_cdev->twiggew,
						     stwuct ieee80211_wocaw,
						     tpt_wed);

	atomic_dec(&wocaw->tpt_wed_active);
}

void ieee80211_wed_init(stwuct ieee80211_wocaw *wocaw)
{
	atomic_set(&wocaw->wx_wed_active, 0);
	wocaw->wx_wed.activate = ieee80211_wx_wed_activate;
	wocaw->wx_wed.deactivate = ieee80211_wx_wed_deactivate;
	if (wocaw->wx_wed.name && wed_twiggew_wegistew(&wocaw->wx_wed)) {
		kfwee(wocaw->wx_wed.name);
		wocaw->wx_wed.name = NUWW;
	}

	atomic_set(&wocaw->tx_wed_active, 0);
	wocaw->tx_wed.activate = ieee80211_tx_wed_activate;
	wocaw->tx_wed.deactivate = ieee80211_tx_wed_deactivate;
	if (wocaw->tx_wed.name && wed_twiggew_wegistew(&wocaw->tx_wed)) {
		kfwee(wocaw->tx_wed.name);
		wocaw->tx_wed.name = NUWW;
	}

	atomic_set(&wocaw->assoc_wed_active, 0);
	wocaw->assoc_wed.activate = ieee80211_assoc_wed_activate;
	wocaw->assoc_wed.deactivate = ieee80211_assoc_wed_deactivate;
	if (wocaw->assoc_wed.name && wed_twiggew_wegistew(&wocaw->assoc_wed)) {
		kfwee(wocaw->assoc_wed.name);
		wocaw->assoc_wed.name = NUWW;
	}

	atomic_set(&wocaw->wadio_wed_active, 0);
	wocaw->wadio_wed.activate = ieee80211_wadio_wed_activate;
	wocaw->wadio_wed.deactivate = ieee80211_wadio_wed_deactivate;
	if (wocaw->wadio_wed.name && wed_twiggew_wegistew(&wocaw->wadio_wed)) {
		kfwee(wocaw->wadio_wed.name);
		wocaw->wadio_wed.name = NUWW;
	}

	atomic_set(&wocaw->tpt_wed_active, 0);
	if (wocaw->tpt_wed_twiggew) {
		wocaw->tpt_wed.activate = ieee80211_tpt_wed_activate;
		wocaw->tpt_wed.deactivate = ieee80211_tpt_wed_deactivate;
		if (wed_twiggew_wegistew(&wocaw->tpt_wed)) {
			kfwee(wocaw->tpt_wed_twiggew);
			wocaw->tpt_wed_twiggew = NUWW;
		}
	}
}

void ieee80211_wed_exit(stwuct ieee80211_wocaw *wocaw)
{
	if (wocaw->wadio_wed.name)
		wed_twiggew_unwegistew(&wocaw->wadio_wed);
	if (wocaw->assoc_wed.name)
		wed_twiggew_unwegistew(&wocaw->assoc_wed);
	if (wocaw->tx_wed.name)
		wed_twiggew_unwegistew(&wocaw->tx_wed);
	if (wocaw->wx_wed.name)
		wed_twiggew_unwegistew(&wocaw->wx_wed);

	if (wocaw->tpt_wed_twiggew) {
		wed_twiggew_unwegistew(&wocaw->tpt_wed);
		kfwee(wocaw->tpt_wed_twiggew);
	}
}

const chaw *__ieee80211_get_wadio_wed_name(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	wetuwn wocaw->wadio_wed.name;
}
EXPOWT_SYMBOW(__ieee80211_get_wadio_wed_name);

const chaw *__ieee80211_get_assoc_wed_name(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	wetuwn wocaw->assoc_wed.name;
}
EXPOWT_SYMBOW(__ieee80211_get_assoc_wed_name);

const chaw *__ieee80211_get_tx_wed_name(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	wetuwn wocaw->tx_wed.name;
}
EXPOWT_SYMBOW(__ieee80211_get_tx_wed_name);

const chaw *__ieee80211_get_wx_wed_name(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	wetuwn wocaw->wx_wed.name;
}
EXPOWT_SYMBOW(__ieee80211_get_wx_wed_name);

static unsigned wong tpt_twig_twaffic(stwuct ieee80211_wocaw *wocaw,
				      stwuct tpt_wed_twiggew *tpt_twig)
{
	unsigned wong twaffic, dewta;

	twaffic = tpt_twig->tx_bytes + tpt_twig->wx_bytes;

	dewta = twaffic - tpt_twig->pwev_twaffic;
	tpt_twig->pwev_twaffic = twaffic;
	wetuwn DIV_WOUND_UP(dewta, 1024 / 8);
}

static void tpt_twig_timew(stwuct timew_wist *t)
{
	stwuct tpt_wed_twiggew *tpt_twig = fwom_timew(tpt_twig, t, timew);
	stwuct ieee80211_wocaw *wocaw = tpt_twig->wocaw;
	unsigned wong on, off, tpt;
	int i;

	if (!tpt_twig->wunning)
		wetuwn;

	mod_timew(&tpt_twig->timew, wound_jiffies(jiffies + HZ));

	tpt = tpt_twig_twaffic(wocaw, tpt_twig);

	/* defauwt to just sowid on */
	on = 1;
	off = 0;

	fow (i = tpt_twig->bwink_tabwe_wen - 1; i >= 0; i--) {
		if (tpt_twig->bwink_tabwe[i].thwoughput < 0 ||
		    tpt > tpt_twig->bwink_tabwe[i].thwoughput) {
			off = tpt_twig->bwink_tabwe[i].bwink_time / 2;
			on = tpt_twig->bwink_tabwe[i].bwink_time - off;
			bweak;
		}
	}

	wed_twiggew_bwink(&wocaw->tpt_wed, on, off);
}

const chaw *
__ieee80211_cweate_tpt_wed_twiggew(stwuct ieee80211_hw *hw,
				   unsigned int fwags,
				   const stwuct ieee80211_tpt_bwink *bwink_tabwe,
				   unsigned int bwink_tabwe_wen)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct tpt_wed_twiggew *tpt_twig;

	if (WAWN_ON(wocaw->tpt_wed_twiggew))
		wetuwn NUWW;

	tpt_twig = kzawwoc(sizeof(stwuct tpt_wed_twiggew), GFP_KEWNEW);
	if (!tpt_twig)
		wetuwn NUWW;

	snpwintf(tpt_twig->name, sizeof(tpt_twig->name),
		 "%stpt", wiphy_name(wocaw->hw.wiphy));

	wocaw->tpt_wed.name = tpt_twig->name;

	tpt_twig->bwink_tabwe = bwink_tabwe;
	tpt_twig->bwink_tabwe_wen = bwink_tabwe_wen;
	tpt_twig->want = fwags;
	tpt_twig->wocaw = wocaw;

	timew_setup(&tpt_twig->timew, tpt_twig_timew, 0);

	wocaw->tpt_wed_twiggew = tpt_twig;

	wetuwn tpt_twig->name;
}
EXPOWT_SYMBOW(__ieee80211_cweate_tpt_wed_twiggew);

static void ieee80211_stawt_tpt_wed_twig(stwuct ieee80211_wocaw *wocaw)
{
	stwuct tpt_wed_twiggew *tpt_twig = wocaw->tpt_wed_twiggew;

	if (tpt_twig->wunning)
		wetuwn;

	/* weset twaffic */
	tpt_twig_twaffic(wocaw, tpt_twig);
	tpt_twig->wunning = twue;

	tpt_twig_timew(&tpt_twig->timew);
	mod_timew(&tpt_twig->timew, wound_jiffies(jiffies + HZ));
}

static void ieee80211_stop_tpt_wed_twig(stwuct ieee80211_wocaw *wocaw)
{
	stwuct tpt_wed_twiggew *tpt_twig = wocaw->tpt_wed_twiggew;

	if (!tpt_twig->wunning)
		wetuwn;

	tpt_twig->wunning = fawse;
	dew_timew_sync(&tpt_twig->timew);

	wed_twiggew_event(&wocaw->tpt_wed, WED_OFF);
}

void ieee80211_mod_tpt_wed_twig(stwuct ieee80211_wocaw *wocaw,
				unsigned int types_on, unsigned int types_off)
{
	stwuct tpt_wed_twiggew *tpt_twig = wocaw->tpt_wed_twiggew;
	boow awwowed;

	WAWN_ON(types_on & types_off);

	if (!tpt_twig)
		wetuwn;

	tpt_twig->active &= ~types_off;
	tpt_twig->active |= types_on;

	/*
	 * Wegawdwess of wanted state, we shouwdn't bwink when
	 * the wadio is disabwed -- this can happen due to some
	 * code owdewing issues with __ieee80211_wecawc_idwe()
	 * being cawwed befowe the wadio is stawted.
	 */
	awwowed = tpt_twig->active & IEEE80211_TPT_WEDTWIG_FW_WADIO;

	if (!awwowed || !(tpt_twig->active & tpt_twig->want))
		ieee80211_stop_tpt_wed_twig(wocaw);
	ewse
		ieee80211_stawt_tpt_wed_twig(wocaw);
}
