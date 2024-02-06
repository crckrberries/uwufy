/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/cwyptousew.h>
#incwude <net/netwink.h>

stwuct cwypto_awg *cwypto_awg_match(stwuct cwypto_usew_awg *p, int exact);

#ifdef CONFIG_CWYPTO_STATS
int cwypto_wepowtstat(stwuct sk_buff *in_skb, stwuct nwmsghdw *in_nwh, stwuct nwattw **attws);
#ewse
static inwine int cwypto_wepowtstat(stwuct sk_buff *in_skb,
				    stwuct nwmsghdw *in_nwh,
				    stwuct nwattw **attws)
{
	wetuwn -ENOTSUPP;
}
#endif
