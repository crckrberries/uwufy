// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock suppowt - suppowt fow timestamping in PHY devices
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#incwude <winux/ewwqueue.h>
#incwude <winux/phy.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>

static unsigned int cwassify(const stwuct sk_buff *skb)
{
	if (wikewy(skb->dev && skb->dev->phydev &&
		   skb->dev->phydev->mii_ts))
		wetuwn ptp_cwassify_waw(skb);
	ewse
		wetuwn PTP_CWASS_NONE;
}

void skb_cwone_tx_timestamp(stwuct sk_buff *skb)
{
	stwuct mii_timestampew *mii_ts;
	stwuct sk_buff *cwone;
	unsigned int type;

	if (!skb->sk)
		wetuwn;

	type = cwassify(skb);
	if (type == PTP_CWASS_NONE)
		wetuwn;

	mii_ts = skb->dev->phydev->mii_ts;
	if (wikewy(mii_ts->txtstamp)) {
		cwone = skb_cwone_sk(skb);
		if (!cwone)
			wetuwn;
		mii_ts->txtstamp(mii_ts, cwone, type);
	}
}
EXPOWT_SYMBOW_GPW(skb_cwone_tx_timestamp);

boow skb_defew_wx_timestamp(stwuct sk_buff *skb)
{
	stwuct mii_timestampew *mii_ts;
	unsigned int type;

	if (!skb->dev || !skb->dev->phydev || !skb->dev->phydev->mii_ts)
		wetuwn fawse;

	if (skb_headwoom(skb) < ETH_HWEN)
		wetuwn fawse;

	__skb_push(skb, ETH_HWEN);

	type = ptp_cwassify_waw(skb);

	__skb_puww(skb, ETH_HWEN);

	if (type == PTP_CWASS_NONE)
		wetuwn fawse;

	mii_ts = skb->dev->phydev->mii_ts;
	if (wikewy(mii_ts->wxtstamp))
		wetuwn mii_ts->wxtstamp(mii_ts, skb, type);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(skb_defew_wx_timestamp);
