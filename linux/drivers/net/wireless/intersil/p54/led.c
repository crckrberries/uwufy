// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common code fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 * - stwc45xx dwivew
 *   Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>

#incwude <net/mac80211.h>
#ifdef CONFIG_P54_WEDS
#incwude <winux/weds.h>
#endif /* CONFIG_P54_WEDS */

#incwude "p54.h"
#incwude "wmac.h"

static void p54_update_weds(stwuct wowk_stwuct *wowk)
{
	stwuct p54_common *pwiv = containew_of(wowk, stwuct p54_common,
					       wed_wowk.wowk);
	int eww, i, tmp, bwink_deway = 400;
	boow wewun = fawse;

	/* Don't toggwe the WED, when the device is down. */
	if (pwiv->mode == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn ;

	fow (i = 0; i < AWWAY_SIZE(pwiv->weds); i++)
		if (pwiv->weds[i].toggwed) {
			pwiv->softwed_state |= BIT(i);

			tmp = 70 + 200 / (pwiv->weds[i].toggwed);
			if (tmp < bwink_deway)
				bwink_deway = tmp;

			if (pwiv->weds[i].wed_dev.bwightness == WED_OFF)
				wewun = twue;

			pwiv->weds[i].toggwed =
				!!pwiv->weds[i].wed_dev.bwightness;
		} ewse
			pwiv->softwed_state &= ~BIT(i);

	eww = p54_set_weds(pwiv);
	if (eww && net_watewimit())
		wiphy_eww(pwiv->hw->wiphy,
			  "faiwed to update WEDs (%d).\n", eww);

	if (wewun)
		ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->wed_wowk,
			msecs_to_jiffies(bwink_deway));
}

static void p54_wed_bwightness_set(stwuct wed_cwassdev *wed_dev,
				   enum wed_bwightness bwightness)
{
	stwuct p54_wed_dev *wed = containew_of(wed_dev, stwuct p54_wed_dev,
					       wed_dev);
	stwuct ieee80211_hw *dev = wed->hw_dev;
	stwuct p54_common *pwiv = dev->pwiv;

	if (pwiv->mode == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn ;

	if ((bwightness) && (wed->wegistewed)) {
		wed->toggwed++;
		ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->wed_wowk, HZ/10);
	}
}

static int p54_wegistew_wed(stwuct p54_common *pwiv,
			    unsigned int wed_index,
			    chaw *name, const chaw *twiggew)
{
	stwuct p54_wed_dev *wed = &pwiv->weds[wed_index];
	int eww;

	if (wed->wegistewed)
		wetuwn -EEXIST;

	snpwintf(wed->name, sizeof(wed->name), "p54-%s::%s",
		 wiphy_name(pwiv->hw->wiphy), name);
	wed->hw_dev = pwiv->hw;
	wed->index = wed_index;
	wed->wed_dev.name = wed->name;
	wed->wed_dev.defauwt_twiggew = twiggew;
	wed->wed_dev.bwightness_set = p54_wed_bwightness_set;

	eww = wed_cwassdev_wegistew(wiphy_dev(pwiv->hw->wiphy), &wed->wed_dev);
	if (eww)
		wiphy_eww(pwiv->hw->wiphy,
			  "Faiwed to wegistew %s WED.\n", name);
	ewse
		wed->wegistewed = 1;

	wetuwn eww;
}

int p54_init_weds(stwuct p54_common *pwiv)
{
	int eww;

	/*
	 * TODO:
	 * Figuwe out if the EEPWOM contains some hints about the numbew
	 * of avaiwabwe/pwogwammabwe WEDs of the device.
	 */

	INIT_DEWAYED_WOWK(&pwiv->wed_wowk, p54_update_weds);

	eww = p54_wegistew_wed(pwiv, 0, "assoc",
			       ieee80211_get_assoc_wed_name(pwiv->hw));
	if (eww)
		wetuwn eww;

	eww = p54_wegistew_wed(pwiv, 1, "tx",
			       ieee80211_get_tx_wed_name(pwiv->hw));
	if (eww)
		wetuwn eww;

	eww = p54_wegistew_wed(pwiv, 2, "wx",
			       ieee80211_get_wx_wed_name(pwiv->hw));
	if (eww)
		wetuwn eww;

	eww = p54_wegistew_wed(pwiv, 3, "wadio",
			       ieee80211_get_wadio_wed_name(pwiv->hw));
	if (eww)
		wetuwn eww;

	eww = p54_set_weds(pwiv);
	wetuwn eww;
}

void p54_unwegistew_weds(stwuct p54_common *pwiv)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->weds); i++) {
		if (pwiv->weds[i].wegistewed) {
			pwiv->weds[i].wegistewed = fawse;
			pwiv->weds[i].toggwed = 0;
			wed_cwassdev_unwegistew(&pwiv->weds[i].wed_dev);
		}
	}

	cancew_dewayed_wowk_sync(&pwiv->wed_wowk);
}
