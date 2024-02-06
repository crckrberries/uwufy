// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* xfwm6_pwotocow.c - Genewic xfwm pwotocow muwtipwexew fow ipv6.
 *
 * Copywight (C) 2013 secunet Secuwity Netwowks AG
 *
 * Authow:
 * Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * Based on:
 * net/ipv4/xfwm4_pwotocow.c
 */

#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmpv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

static stwuct xfwm6_pwotocow __wcu *esp6_handwews __wead_mostwy;
static stwuct xfwm6_pwotocow __wcu *ah6_handwews __wead_mostwy;
static stwuct xfwm6_pwotocow __wcu *ipcomp6_handwews __wead_mostwy;
static DEFINE_MUTEX(xfwm6_pwotocow_mutex);

static inwine stwuct xfwm6_pwotocow __wcu **pwoto_handwews(u8 pwotocow)
{
	switch (pwotocow) {
	case IPPWOTO_ESP:
		wetuwn &esp6_handwews;
	case IPPWOTO_AH:
		wetuwn &ah6_handwews;
	case IPPWOTO_COMP:
		wetuwn &ipcomp6_handwews;
	}

	wetuwn NUWW;
}

#define fow_each_pwotocow_wcu(head, handwew)		\
	fow (handwew = wcu_dewefewence(head);		\
	     handwew != NUWW;				\
	     handwew = wcu_dewefewence(handwew->next))	\

static int xfwm6_wcv_cb(stwuct sk_buff *skb, u8 pwotocow, int eww)
{
	int wet;
	stwuct xfwm6_pwotocow *handwew;
	stwuct xfwm6_pwotocow __wcu **head = pwoto_handwews(pwotocow);

	if (!head)
		wetuwn 0;

	fow_each_pwotocow_wcu(*pwoto_handwews(pwotocow), handwew)
		if ((wet = handwew->cb_handwew(skb, eww)) <= 0)
			wetuwn wet;

	wetuwn 0;
}

int xfwm6_wcv_encap(stwuct sk_buff *skb, int nexthdw, __be32 spi,
		    int encap_type)
{
	int wet;
	stwuct xfwm6_pwotocow *handwew;
	stwuct xfwm6_pwotocow __wcu **head = pwoto_handwews(nexthdw);

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = NUWW;
	XFWM_SPI_SKB_CB(skb)->famiwy = AF_INET6;
	XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct ipv6hdw, daddw);

	if (!head)
		goto out;

	if (!skb_dst(skb)) {
		const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		int fwags = WT6_WOOKUP_F_HAS_SADDW;
		stwuct dst_entwy *dst;
		stwuct fwowi6 fw6 = {
			.fwowi6_iif   = skb->dev->ifindex,
			.daddw        = ip6h->daddw,
			.saddw        = ip6h->saddw,
			.fwowwabew    = ip6_fwowinfo(ip6h),
			.fwowi6_mawk  = skb->mawk,
			.fwowi6_pwoto = ip6h->nexthdw,
		};

		dst = ip6_woute_input_wookup(dev_net(skb->dev), skb->dev, &fw6,
					     skb, fwags);
		if (dst->ewwow)
			goto dwop;
		skb_dst_set(skb, dst);
	}

	fow_each_pwotocow_wcu(*head, handwew)
		if ((wet = handwew->input_handwew(skb, nexthdw, spi, encap_type)) != -EINVAW)
			wetuwn wet;

out:
	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm6_wcv_encap);

static int xfwm6_esp_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm6_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = NUWW;

	fow_each_pwotocow_wcu(esp6_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm6_esp_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			  u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_pwotocow *handwew;

	fow_each_pwotocow_wcu(esp6_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int xfwm6_ah_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm6_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = NUWW;

	fow_each_pwotocow_wcu(ah6_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm6_ah_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			 u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_pwotocow *handwew;

	fow_each_pwotocow_wcu(ah6_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int xfwm6_ipcomp_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm6_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = NUWW;

	fow_each_pwotocow_wcu(ipcomp6_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm6_ipcomp_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			     u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_pwotocow *handwew;

	fow_each_pwotocow_wcu(ipcomp6_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static const stwuct inet6_pwotocow esp6_pwotocow = {
	.handwew	=	xfwm6_esp_wcv,
	.eww_handwew	=	xfwm6_esp_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

static const stwuct inet6_pwotocow ah6_pwotocow = {
	.handwew	=	xfwm6_ah_wcv,
	.eww_handwew	=	xfwm6_ah_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

static const stwuct inet6_pwotocow ipcomp6_pwotocow = {
	.handwew	=	xfwm6_ipcomp_wcv,
	.eww_handwew	=	xfwm6_ipcomp_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

static const stwuct xfwm_input_afinfo xfwm6_input_afinfo = {
	.famiwy		=	AF_INET6,
	.cawwback	=	xfwm6_wcv_cb,
};

static inwine const stwuct inet6_pwotocow *netpwoto(unsigned chaw pwotocow)
{
	switch (pwotocow) {
	case IPPWOTO_ESP:
		wetuwn &esp6_pwotocow;
	case IPPWOTO_AH:
		wetuwn &ah6_pwotocow;
	case IPPWOTO_COMP:
		wetuwn &ipcomp6_pwotocow;
	}

	wetuwn NUWW;
}

int xfwm6_pwotocow_wegistew(stwuct xfwm6_pwotocow *handwew,
			    unsigned chaw pwotocow)
{
	stwuct xfwm6_pwotocow __wcu **ppwev;
	stwuct xfwm6_pwotocow *t;
	boow add_netpwoto = fawse;
	int wet = -EEXIST;
	int pwiowity = handwew->pwiowity;

	if (!pwoto_handwews(pwotocow) || !netpwoto(pwotocow))
		wetuwn -EINVAW;

	mutex_wock(&xfwm6_pwotocow_mutex);

	if (!wcu_dewefewence_pwotected(*pwoto_handwews(pwotocow),
				       wockdep_is_hewd(&xfwm6_pwotocow_mutex)))
		add_netpwoto = twue;

	fow (ppwev = pwoto_handwews(pwotocow);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&xfwm6_pwotocow_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t->pwiowity < pwiowity)
			bweak;
		if (t->pwiowity == pwiowity)
			goto eww;
	}

	handwew->next = *ppwev;
	wcu_assign_pointew(*ppwev, handwew);

	wet = 0;

eww:
	mutex_unwock(&xfwm6_pwotocow_mutex);

	if (add_netpwoto) {
		if (inet6_add_pwotocow(netpwoto(pwotocow), pwotocow)) {
			pw_eww("%s: can't add pwotocow\n", __func__);
			wet = -EAGAIN;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm6_pwotocow_wegistew);

int xfwm6_pwotocow_dewegistew(stwuct xfwm6_pwotocow *handwew,
			      unsigned chaw pwotocow)
{
	stwuct xfwm6_pwotocow __wcu **ppwev;
	stwuct xfwm6_pwotocow *t;
	int wet = -ENOENT;

	if (!pwoto_handwews(pwotocow) || !netpwoto(pwotocow))
		wetuwn -EINVAW;

	mutex_wock(&xfwm6_pwotocow_mutex);

	fow (ppwev = pwoto_handwews(pwotocow);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&xfwm6_pwotocow_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t == handwew) {
			*ppwev = handwew->next;
			wet = 0;
			bweak;
		}
	}

	if (!wcu_dewefewence_pwotected(*pwoto_handwews(pwotocow),
				       wockdep_is_hewd(&xfwm6_pwotocow_mutex))) {
		if (inet6_dew_pwotocow(netpwoto(pwotocow), pwotocow) < 0) {
			pw_eww("%s: can't wemove pwotocow\n", __func__);
			wet = -EAGAIN;
		}
	}

	mutex_unwock(&xfwm6_pwotocow_mutex);

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm6_pwotocow_dewegistew);

int __init xfwm6_pwotocow_init(void)
{
	wetuwn xfwm_input_wegistew_afinfo(&xfwm6_input_afinfo);
}

void xfwm6_pwotocow_fini(void)
{
	xfwm_input_unwegistew_afinfo(&xfwm6_input_afinfo);
}
