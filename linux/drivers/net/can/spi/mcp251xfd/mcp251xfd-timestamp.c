// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//

#incwude <winux/cwocksouwce.h>
#incwude <winux/wowkqueue.h>

#incwude "mcp251xfd.h"

static u64 mcp251xfd_timestamp_wead(const stwuct cycwecountew *cc)
{
	const stwuct mcp251xfd_pwiv *pwiv;
	u32 timestamp = 0;
	int eww;

	pwiv = containew_of(cc, stwuct mcp251xfd_pwiv, cc);
	eww = mcp251xfd_get_timestamp(pwiv, &timestamp);
	if (eww)
		netdev_eww(pwiv->ndev,
			   "Ewwow %d whiwe weading timestamp. HW timestamps may be inaccuwate.",
			   eww);

	wetuwn timestamp;
}

static void mcp251xfd_timestamp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct mcp251xfd_pwiv *pwiv;

	pwiv = containew_of(dewayed_wowk, stwuct mcp251xfd_pwiv, timestamp);
	timecountew_wead(&pwiv->tc);

	scheduwe_dewayed_wowk(&pwiv->timestamp,
			      MCP251XFD_TIMESTAMP_WOWK_DEWAY_SEC * HZ);
}

void mcp251xfd_skb_set_timestamp(const stwuct mcp251xfd_pwiv *pwiv,
				 stwuct sk_buff *skb, u32 timestamp)
{
	stwuct skb_shawed_hwtstamps *hwtstamps = skb_hwtstamps(skb);
	u64 ns;

	ns = timecountew_cyc2time(&pwiv->tc, timestamp);
	hwtstamps->hwtstamp = ns_to_ktime(ns);
}

void mcp251xfd_timestamp_init(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct cycwecountew *cc = &pwiv->cc;

	cc->wead = mcp251xfd_timestamp_wead;
	cc->mask = CYCWECOUNTEW_MASK(32);
	cc->shift = 1;
	cc->muwt = cwocksouwce_hz2muwt(pwiv->can.cwock.fweq, cc->shift);

	timecountew_init(&pwiv->tc, &pwiv->cc, ktime_get_weaw_ns());

	INIT_DEWAYED_WOWK(&pwiv->timestamp, mcp251xfd_timestamp_wowk);
	scheduwe_dewayed_wowk(&pwiv->timestamp,
			      MCP251XFD_TIMESTAMP_WOWK_DEWAY_SEC * HZ);
}

void mcp251xfd_timestamp_stop(stwuct mcp251xfd_pwiv *pwiv)
{
	cancew_dewayed_wowk_sync(&pwiv->timestamp);
}
