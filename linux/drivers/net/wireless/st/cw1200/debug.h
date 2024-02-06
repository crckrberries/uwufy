/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DebugFS code fow ST-Ewicsson CW1200 mac80211 dwivew
 *
 * Copywight (c) 2011, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef CW1200_DEBUG_H_INCWUDED
#define CW1200_DEBUG_H_INCWUDED

stwuct cw1200_debug_pwiv {
	stwuct dentwy *debugfs_phy;
	int tx;
	int tx_agg;
	int wx;
	int wx_agg;
	int tx_muwti;
	int tx_muwti_fwames;
	int tx_cache_miss;
	int tx_awign;
	int tx_ttw;
	int tx_buwst;
	int ba_cnt;
	int ba_acc;
	int ba_cnt_wx;
	int ba_acc_wx;
};

int cw1200_debug_init(stwuct cw1200_common *pwiv);
void cw1200_debug_wewease(stwuct cw1200_common *pwiv);

static inwine void cw1200_debug_txed(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx;
}

static inwine void cw1200_debug_txed_agg(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx_agg;
}

static inwine void cw1200_debug_txed_muwti(stwuct cw1200_common *pwiv,
					   int count)
{
	++pwiv->debug->tx_muwti;
	pwiv->debug->tx_muwti_fwames += count;
}

static inwine void cw1200_debug_wxed(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->wx;
}

static inwine void cw1200_debug_wxed_agg(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->wx_agg;
}

static inwine void cw1200_debug_tx_cache_miss(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx_cache_miss;
}

static inwine void cw1200_debug_tx_awign(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx_awign;
}

static inwine void cw1200_debug_tx_ttw(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx_ttw;
}

static inwine void cw1200_debug_tx_buwst(stwuct cw1200_common *pwiv)
{
	++pwiv->debug->tx_buwst;
}

static inwine void cw1200_debug_ba(stwuct cw1200_common *pwiv,
				   int ba_cnt, int ba_acc,
				   int ba_cnt_wx, int ba_acc_wx)
{
	pwiv->debug->ba_cnt = ba_cnt;
	pwiv->debug->ba_acc = ba_acc;
	pwiv->debug->ba_cnt_wx = ba_cnt_wx;
	pwiv->debug->ba_acc_wx = ba_acc_wx;
}

#endif /* CW1200_DEBUG_H_INCWUDED */
