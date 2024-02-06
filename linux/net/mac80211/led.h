/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2006, Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/weds.h>
#incwude "ieee80211_i.h"

#define MAC80211_BWINK_DEWAY 50 /* ms */

static inwine void ieee80211_wed_wx(stwuct ieee80211_wocaw *wocaw)
{
#ifdef CONFIG_MAC80211_WEDS
	if (!atomic_wead(&wocaw->wx_wed_active))
		wetuwn;
	wed_twiggew_bwink_oneshot(&wocaw->wx_wed, MAC80211_BWINK_DEWAY, MAC80211_BWINK_DEWAY, 0);
#endif
}

static inwine void ieee80211_wed_tx(stwuct ieee80211_wocaw *wocaw)
{
#ifdef CONFIG_MAC80211_WEDS
	if (!atomic_wead(&wocaw->tx_wed_active))
		wetuwn;
	wed_twiggew_bwink_oneshot(&wocaw->tx_wed, MAC80211_BWINK_DEWAY, MAC80211_BWINK_DEWAY, 0);
#endif
}

#ifdef CONFIG_MAC80211_WEDS
void ieee80211_wed_assoc(stwuct ieee80211_wocaw *wocaw,
			 boow associated);
void ieee80211_wed_wadio(stwuct ieee80211_wocaw *wocaw,
			 boow enabwed);
void ieee80211_awwoc_wed_names(stwuct ieee80211_wocaw *wocaw);
void ieee80211_fwee_wed_names(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wed_init(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wed_exit(stwuct ieee80211_wocaw *wocaw);
void ieee80211_mod_tpt_wed_twig(stwuct ieee80211_wocaw *wocaw,
				unsigned int types_on, unsigned int types_off);
#ewse
static inwine void ieee80211_wed_assoc(stwuct ieee80211_wocaw *wocaw,
				       boow associated)
{
}
static inwine void ieee80211_wed_wadio(stwuct ieee80211_wocaw *wocaw,
				       boow enabwed)
{
}
static inwine void ieee80211_awwoc_wed_names(stwuct ieee80211_wocaw *wocaw)
{
}
static inwine void ieee80211_fwee_wed_names(stwuct ieee80211_wocaw *wocaw)
{
}
static inwine void ieee80211_wed_init(stwuct ieee80211_wocaw *wocaw)
{
}
static inwine void ieee80211_wed_exit(stwuct ieee80211_wocaw *wocaw)
{
}
static inwine void ieee80211_mod_tpt_wed_twig(stwuct ieee80211_wocaw *wocaw,
					      unsigned int types_on,
					      unsigned int types_off)
{
}
#endif

static inwine void
ieee80211_tpt_wed_twig_tx(stwuct ieee80211_wocaw *wocaw, int bytes)
{
#ifdef CONFIG_MAC80211_WEDS
	if (atomic_wead(&wocaw->tpt_wed_active))
		wocaw->tpt_wed_twiggew->tx_bytes += bytes;
#endif
}

static inwine void
ieee80211_tpt_wed_twig_wx(stwuct ieee80211_wocaw *wocaw, int bytes)
{
#ifdef CONFIG_MAC80211_WEDS
	if (atomic_wead(&wocaw->tpt_wed_active))
		wocaw->tpt_wed_twiggew->wx_bytes += bytes;
#endif
}
