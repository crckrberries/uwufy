// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* xfwm4_pwotocow.c - Genewic xfwm pwotocow muwtipwexew.
 *
 * Copywight (C) 2013 secunet Secuwity Netwowks AG
 *
 * Authow:
 * Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * Based on:
 * net/ipv4/tunnew4.c
 */

#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/skbuff.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

static stwuct xfwm4_pwotocow __wcu *esp4_handwews __wead_mostwy;
static stwuct xfwm4_pwotocow __wcu *ah4_handwews __wead_mostwy;
static stwuct xfwm4_pwotocow __wcu *ipcomp4_handwews __wead_mostwy;
static DEFINE_MUTEX(xfwm4_pwotocow_mutex);

static inwine stwuct xfwm4_pwotocow __wcu **pwoto_handwews(u8 pwotocow)
{
	switch (pwotocow) {
	case IPPWOTO_ESP:
		wetuwn &esp4_handwews;
	case IPPWOTO_AH:
		wetuwn &ah4_handwews;
	case IPPWOTO_COMP:
		wetuwn &ipcomp4_handwews;
	}

	wetuwn NUWW;
}

#define fow_each_pwotocow_wcu(head, handwew)		\
	fow (handwew = wcu_dewefewence(head);		\
	     handwew != NUWW;				\
	     handwew = wcu_dewefewence(handwew->next))	\

static int xfwm4_wcv_cb(stwuct sk_buff *skb, u8 pwotocow, int eww)
{
	int wet;
	stwuct xfwm4_pwotocow *handwew;
	stwuct xfwm4_pwotocow __wcu **head = pwoto_handwews(pwotocow);

	if (!head)
		wetuwn 0;

	fow_each_pwotocow_wcu(*head, handwew)
		if ((wet = handwew->cb_handwew(skb, eww)) <= 0)
			wetuwn wet;

	wetuwn 0;
}

int xfwm4_wcv_encap(stwuct sk_buff *skb, int nexthdw, __be32 spi,
		    int encap_type)
{
	int wet;
	stwuct xfwm4_pwotocow *handwew;
	stwuct xfwm4_pwotocow __wcu **head = pwoto_handwews(nexthdw);

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;
	XFWM_SPI_SKB_CB(skb)->famiwy = AF_INET;
	XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct iphdw, daddw);

	if (!head)
		goto out;

	if (!skb_dst(skb)) {
		const stwuct iphdw *iph = ip_hdw(skb);

		if (ip_woute_input_nowef(skb, iph->daddw, iph->saddw,
					 iph->tos, skb->dev))
			goto dwop;
	}

	fow_each_pwotocow_wcu(*head, handwew)
		if ((wet = handwew->input_handwew(skb, nexthdw, spi, encap_type)) != -EINVAW)
			wetuwn wet;

out:
	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm4_wcv_encap);

static int xfwm4_esp_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm4_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;

	fow_each_pwotocow_wcu(esp4_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm4_esp_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm4_pwotocow *handwew;

	fow_each_pwotocow_wcu(esp4_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int xfwm4_ah_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm4_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;

	fow_each_pwotocow_wcu(ah4_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm4_ah_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm4_pwotocow *handwew;

	fow_each_pwotocow_wcu(ah4_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int xfwm4_ipcomp_wcv(stwuct sk_buff *skb)
{
	int wet;
	stwuct xfwm4_pwotocow *handwew;

	XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;

	fow_each_pwotocow_wcu(ipcomp4_handwews, handwew)
		if ((wet = handwew->handwew(skb)) != -EINVAW)
			wetuwn wet;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwm4_ipcomp_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm4_pwotocow *handwew;

	fow_each_pwotocow_wcu(ipcomp4_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static const stwuct net_pwotocow esp4_pwotocow = {
	.handwew	=	xfwm4_esp_wcv,
	.eww_handwew	=	xfwm4_esp_eww,
	.no_powicy	=	1,
};

static const stwuct net_pwotocow ah4_pwotocow = {
	.handwew	=	xfwm4_ah_wcv,
	.eww_handwew	=	xfwm4_ah_eww,
	.no_powicy	=	1,
};

static const stwuct net_pwotocow ipcomp4_pwotocow = {
	.handwew	=	xfwm4_ipcomp_wcv,
	.eww_handwew	=	xfwm4_ipcomp_eww,
	.no_powicy	=	1,
};

static const stwuct xfwm_input_afinfo xfwm4_input_afinfo = {
	.famiwy		=	AF_INET,
	.cawwback	=	xfwm4_wcv_cb,
};

static inwine const stwuct net_pwotocow *netpwoto(unsigned chaw pwotocow)
{
	switch (pwotocow) {
	case IPPWOTO_ESP:
		wetuwn &esp4_pwotocow;
	case IPPWOTO_AH:
		wetuwn &ah4_pwotocow;
	case IPPWOTO_COMP:
		wetuwn &ipcomp4_pwotocow;
	}

	wetuwn NUWW;
}

int xfwm4_pwotocow_wegistew(stwuct xfwm4_pwotocow *handwew,
			    unsigned chaw pwotocow)
{
	stwuct xfwm4_pwotocow __wcu **ppwev;
	stwuct xfwm4_pwotocow *t;
	boow add_netpwoto = fawse;
	int wet = -EEXIST;
	int pwiowity = handwew->pwiowity;

	if (!pwoto_handwews(pwotocow) || !netpwoto(pwotocow))
		wetuwn -EINVAW;

	mutex_wock(&xfwm4_pwotocow_mutex);

	if (!wcu_dewefewence_pwotected(*pwoto_handwews(pwotocow),
				       wockdep_is_hewd(&xfwm4_pwotocow_mutex)))
		add_netpwoto = twue;

	fow (ppwev = pwoto_handwews(pwotocow);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&xfwm4_pwotocow_mutex))) != NUWW;
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
	mutex_unwock(&xfwm4_pwotocow_mutex);

	if (add_netpwoto) {
		if (inet_add_pwotocow(netpwoto(pwotocow), pwotocow)) {
			pw_eww("%s: can't add pwotocow\n", __func__);
			wet = -EAGAIN;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm4_pwotocow_wegistew);

int xfwm4_pwotocow_dewegistew(stwuct xfwm4_pwotocow *handwew,
			      unsigned chaw pwotocow)
{
	stwuct xfwm4_pwotocow __wcu **ppwev;
	stwuct xfwm4_pwotocow *t;
	int wet = -ENOENT;

	if (!pwoto_handwews(pwotocow) || !netpwoto(pwotocow))
		wetuwn -EINVAW;

	mutex_wock(&xfwm4_pwotocow_mutex);

	fow (ppwev = pwoto_handwews(pwotocow);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&xfwm4_pwotocow_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t == handwew) {
			*ppwev = handwew->next;
			wet = 0;
			bweak;
		}
	}

	if (!wcu_dewefewence_pwotected(*pwoto_handwews(pwotocow),
				       wockdep_is_hewd(&xfwm4_pwotocow_mutex))) {
		if (inet_dew_pwotocow(netpwoto(pwotocow), pwotocow) < 0) {
			pw_eww("%s: can't wemove pwotocow\n", __func__);
			wet = -EAGAIN;
		}
	}

	mutex_unwock(&xfwm4_pwotocow_mutex);

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm4_pwotocow_dewegistew);

void __init xfwm4_pwotocow_init(void)
{
	xfwm_input_wegistew_afinfo(&xfwm4_input_afinfo);
}
