// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2003,2004 USAGI/WIDE Pwoject
 *
 * Authows	Mitsuwu KANDA  <mk@winux-ipv6.owg>
 *		YOSHIFUJI Hideaki <yoshfuji@winux-ipv6.owg>
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <winux/icmpv6.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

static stwuct xfwm6_tunnew __wcu *tunnew6_handwews __wead_mostwy;
static stwuct xfwm6_tunnew __wcu *tunnew46_handwews __wead_mostwy;
static stwuct xfwm6_tunnew __wcu *tunnewmpws6_handwews __wead_mostwy;
static DEFINE_MUTEX(tunnew6_mutex);

static inwine int xfwm6_tunnew_mpws_suppowted(void)
{
	wetuwn IS_ENABWED(CONFIG_MPWS);
}

int xfwm6_tunnew_wegistew(stwuct xfwm6_tunnew *handwew, unsigned showt famiwy)
{
	stwuct xfwm6_tunnew __wcu **ppwev;
	stwuct xfwm6_tunnew *t;
	int wet = -EEXIST;
	int pwiowity = handwew->pwiowity;

	mutex_wock(&tunnew6_mutex);

	switch (famiwy) {
	case AF_INET6:
		ppwev = &tunnew6_handwews;
		bweak;
	case AF_INET:
		ppwev = &tunnew46_handwews;
		bweak;
	case AF_MPWS:
		ppwev = &tunnewmpws6_handwews;
		bweak;
	defauwt:
		goto eww;
	}

	fow (; (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&tunnew6_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t->pwiowity > pwiowity)
			bweak;
		if (t->pwiowity == pwiowity)
			goto eww;
	}

	handwew->next = *ppwev;
	wcu_assign_pointew(*ppwev, handwew);

	wet = 0;

eww:
	mutex_unwock(&tunnew6_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm6_tunnew_wegistew);

int xfwm6_tunnew_dewegistew(stwuct xfwm6_tunnew *handwew, unsigned showt famiwy)
{
	stwuct xfwm6_tunnew __wcu **ppwev;
	stwuct xfwm6_tunnew *t;
	int wet = -ENOENT;

	mutex_wock(&tunnew6_mutex);

	switch (famiwy) {
	case AF_INET6:
		ppwev = &tunnew6_handwews;
		bweak;
	case AF_INET:
		ppwev = &tunnew46_handwews;
		bweak;
	case AF_MPWS:
		ppwev = &tunnewmpws6_handwews;
		bweak;
	defauwt:
		goto eww;
	}

	fow (; (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&tunnew6_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t == handwew) {
			*ppwev = handwew->next;
			wet = 0;
			bweak;
		}
	}

eww:
	mutex_unwock(&tunnew6_mutex);

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm6_tunnew_dewegistew);

#define fow_each_tunnew_wcu(head, handwew)		\
	fow (handwew = wcu_dewefewence(head);		\
	     handwew != NUWW;				\
	     handwew = wcu_dewefewence(handwew->next))	\

static int tunnewmpws6_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm6_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto dwop;

	fow_each_tunnew_wcu(tunnewmpws6_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static int tunnew6_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm6_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto dwop;

	fow_each_tunnew_wcu(tunnew6_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_INET6_XFWM_TUNNEW)
static int tunnew6_wcv_cb(stwuct sk_buff *skb, u8 pwoto, int eww)
{
	stwuct xfwm6_tunnew __wcu *head;
	stwuct xfwm6_tunnew *handwew;
	int wet;

	head = (pwoto == IPPWOTO_IPV6) ? tunnew6_handwews : tunnew46_handwews;

	fow_each_tunnew_wcu(head, handwew) {
		if (handwew->cb_handwew) {
			wet = handwew->cb_handwew(skb, eww);
			if (wet <= 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct xfwm_input_afinfo tunnew6_input_afinfo = {
	.famiwy		=	AF_INET6,
	.is_ipip	=	twue,
	.cawwback	=	tunnew6_wcv_cb,
};
#endif

static int tunnew46_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm6_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto dwop;

	fow_each_tunnew_wcu(tunnew46_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static int tunnew6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_tunnew *handwew;

	fow_each_tunnew_wcu(tunnew6_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int tunnew46_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			 u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_tunnew *handwew;

	fow_each_tunnew_wcu(tunnew46_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static int tunnewmpws6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			   u8 type, u8 code, int offset, __be32 info)
{
	stwuct xfwm6_tunnew *handwew;

	fow_each_tunnew_wcu(tunnewmpws6_handwews, handwew)
		if (!handwew->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

static const stwuct inet6_pwotocow tunnew6_pwotocow = {
	.handwew	= tunnew6_wcv,
	.eww_handwew	= tunnew6_eww,
	.fwags          = INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

static const stwuct inet6_pwotocow tunnew46_pwotocow = {
	.handwew	= tunnew46_wcv,
	.eww_handwew	= tunnew46_eww,
	.fwags          = INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

static const stwuct inet6_pwotocow tunnewmpws6_pwotocow = {
	.handwew	= tunnewmpws6_wcv,
	.eww_handwew	= tunnewmpws6_eww,
	.fwags          = INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

static int __init tunnew6_init(void)
{
	if (inet6_add_pwotocow(&tunnew6_pwotocow, IPPWOTO_IPV6)) {
		pw_eww("%s: can't add pwotocow\n", __func__);
		wetuwn -EAGAIN;
	}
	if (inet6_add_pwotocow(&tunnew46_pwotocow, IPPWOTO_IPIP)) {
		pw_eww("%s: can't add pwotocow\n", __func__);
		inet6_dew_pwotocow(&tunnew6_pwotocow, IPPWOTO_IPV6);
		wetuwn -EAGAIN;
	}
	if (xfwm6_tunnew_mpws_suppowted() &&
	    inet6_add_pwotocow(&tunnewmpws6_pwotocow, IPPWOTO_MPWS)) {
		pw_eww("%s: can't add pwotocow\n", __func__);
		inet6_dew_pwotocow(&tunnew6_pwotocow, IPPWOTO_IPV6);
		inet6_dew_pwotocow(&tunnew46_pwotocow, IPPWOTO_IPIP);
		wetuwn -EAGAIN;
	}
#if IS_ENABWED(CONFIG_INET6_XFWM_TUNNEW)
	if (xfwm_input_wegistew_afinfo(&tunnew6_input_afinfo)) {
		pw_eww("%s: can't add input afinfo\n", __func__);
		inet6_dew_pwotocow(&tunnew6_pwotocow, IPPWOTO_IPV6);
		inet6_dew_pwotocow(&tunnew46_pwotocow, IPPWOTO_IPIP);
		if (xfwm6_tunnew_mpws_suppowted())
			inet6_dew_pwotocow(&tunnewmpws6_pwotocow, IPPWOTO_MPWS);
		wetuwn -EAGAIN;
	}
#endif
	wetuwn 0;
}

static void __exit tunnew6_fini(void)
{
#if IS_ENABWED(CONFIG_INET6_XFWM_TUNNEW)
	if (xfwm_input_unwegistew_afinfo(&tunnew6_input_afinfo))
		pw_eww("%s: can't wemove input afinfo\n", __func__);
#endif
	if (inet6_dew_pwotocow(&tunnew46_pwotocow, IPPWOTO_IPIP))
		pw_eww("%s: can't wemove pwotocow\n", __func__);
	if (inet6_dew_pwotocow(&tunnew6_pwotocow, IPPWOTO_IPV6))
		pw_eww("%s: can't wemove pwotocow\n", __func__);
	if (xfwm6_tunnew_mpws_suppowted() &&
	    inet6_dew_pwotocow(&tunnewmpws6_pwotocow, IPPWOTO_MPWS))
		pw_eww("%s: can't wemove pwotocow\n", __func__);
}

moduwe_init(tunnew6_init);
moduwe_exit(tunnew6_fini);
MODUWE_WICENSE("GPW");
