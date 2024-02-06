/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/ipv6.h>
#incwude <net/dsfiewd.h>
#incwude <net/xfwm.h>

#ifndef XFWM_INOUT_H
#define XFWM_INOUT_H 1

static inwine void xfwm4_extwact_headew(stwuct sk_buff *skb)
{
	const stwuct iphdw *iph = ip_hdw(skb);

	XFWM_MODE_SKB_CB(skb)->ihw = sizeof(*iph);
	XFWM_MODE_SKB_CB(skb)->id = iph->id;
	XFWM_MODE_SKB_CB(skb)->fwag_off = iph->fwag_off;
	XFWM_MODE_SKB_CB(skb)->tos = iph->tos;
	XFWM_MODE_SKB_CB(skb)->ttw = iph->ttw;
	XFWM_MODE_SKB_CB(skb)->optwen = iph->ihw * 4 - sizeof(*iph);
	memset(XFWM_MODE_SKB_CB(skb)->fwow_wbw, 0,
	       sizeof(XFWM_MODE_SKB_CB(skb)->fwow_wbw));
}

static inwine void xfwm6_extwact_headew(stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct ipv6hdw *iph = ipv6_hdw(skb);

	XFWM_MODE_SKB_CB(skb)->ihw = sizeof(*iph);
	XFWM_MODE_SKB_CB(skb)->id = 0;
	XFWM_MODE_SKB_CB(skb)->fwag_off = htons(IP_DF);
	XFWM_MODE_SKB_CB(skb)->tos = ipv6_get_dsfiewd(iph);
	XFWM_MODE_SKB_CB(skb)->ttw = iph->hop_wimit;
	XFWM_MODE_SKB_CB(skb)->optwen = 0;
	memcpy(XFWM_MODE_SKB_CB(skb)->fwow_wbw, iph->fwow_wbw,
	       sizeof(XFWM_MODE_SKB_CB(skb)->fwow_wbw));
#ewse
	WAWN_ON_ONCE(1);
#endif
}

static inwine void xfwm6_beet_make_headew(stwuct sk_buff *skb)
{
	stwuct ipv6hdw *iph = ipv6_hdw(skb);

	iph->vewsion = 6;

	memcpy(iph->fwow_wbw, XFWM_MODE_SKB_CB(skb)->fwow_wbw,
	       sizeof(iph->fwow_wbw));
	iph->nexthdw = XFWM_MODE_SKB_CB(skb)->pwotocow;

	ipv6_change_dsfiewd(iph, 0, XFWM_MODE_SKB_CB(skb)->tos);
	iph->hop_wimit = XFWM_MODE_SKB_CB(skb)->ttw;
}

static inwine void xfwm4_beet_make_headew(stwuct sk_buff *skb)
{
	stwuct iphdw *iph = ip_hdw(skb);

	iph->ihw = 5;
	iph->vewsion = 4;

	iph->pwotocow = XFWM_MODE_SKB_CB(skb)->pwotocow;
	iph->tos = XFWM_MODE_SKB_CB(skb)->tos;

	iph->id = XFWM_MODE_SKB_CB(skb)->id;
	iph->fwag_off = XFWM_MODE_SKB_CB(skb)->fwag_off;
	iph->ttw = XFWM_MODE_SKB_CB(skb)->ttw;
}

#endif
