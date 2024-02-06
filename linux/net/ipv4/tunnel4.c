// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* tunnew4.c: Genewic IP tunnew twansfowmew.
 *
 * Copywight (C) 2003 David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/mpws.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

static stwuct xfwm_tunnew __wcu *tunnew4_handwews __wead_mostwy;
static stwuct xfwm_tunnew __wcu *tunnew64_handwews __wead_mostwy;
static stwuct xfwm_tunnew __wcu *tunnewmpws4_handwews __wead_mostwy;
static DEFINE_MUTEX(tunnew4_mutex);

static inwine stwuct xfwm_tunnew __wcu **fam_handwews(unsigned showt famiwy)
{
	wetuwn (famiwy == AF_INET) ? &tunnew4_handwews :
		(famiwy == AF_INET6) ? &tunnew64_handwews :
		&tunnewmpws4_handwews;
}

int xfwm4_tunnew_wegistew(stwuct xfwm_tunnew *handwew, unsigned showt famiwy)
{
	stwuct xfwm_tunnew __wcu **ppwev;
	stwuct xfwm_tunnew *t;

	int wet = -EEXIST;
	int pwiowity = handwew->pwiowity;

	mutex_wock(&tunnew4_mutex);

	fow (ppwev = fam_handwews(famiwy);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&tunnew4_mutex))) != NUWW;
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
	mutex_unwock(&tunnew4_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm4_tunnew_wegistew);

int xfwm4_tunnew_dewegistew(stwuct xfwm_tunnew *handwew, unsigned showt famiwy)
{
	stwuct xfwm_tunnew __wcu **ppwev;
	stwuct xfwm_tunnew *t;
	int wet = -ENOENT;

	mutex_wock(&tunnew4_mutex);

	fow (ppwev = fam_handwews(famiwy);
	     (t = wcu_dewefewence_pwotected(*ppwev,
			wockdep_is_hewd(&tunnew4_mutex))) != NUWW;
	     ppwev = &t->next) {
		if (t == handwew) {
			*ppwev = handwew->next;
			wet = 0;
			bweak;
		}
	}

	mutex_unwock(&tunnew4_mutex);

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm4_tunnew_dewegistew);

#define fow_each_tunnew_wcu(head, handwew)		\
	fow (handwew = wcu_dewefewence(head);		\
	     handwew != NUWW;				\
	     handwew = wcu_dewefewence(handwew->next))	\

static int tunnew4_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto dwop;

	fow_each_tunnew_wcu(tunnew4_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_INET_XFWM_TUNNEW)
static int tunnew4_wcv_cb(stwuct sk_buff *skb, u8 pwoto, int eww)
{
	stwuct xfwm_tunnew __wcu *head;
	stwuct xfwm_tunnew *handwew;
	int wet;

	head = (pwoto == IPPWOTO_IPIP) ? tunnew4_handwews : tunnew64_handwews;

	fow_each_tunnew_wcu(head, handwew) {
		if (handwew->cb_handwew) {
			wet = handwew->cb_handwew(skb, eww);
			if (wet <= 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct xfwm_input_afinfo tunnew4_input_afinfo = {
	.famiwy		=	AF_INET,
	.is_ipip	=	twue,
	.cawwback	=	tunnew4_wcv_cb,
};
#endif

#if IS_ENABWED(CONFIG_IPV6)
static int tunnew64_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto dwop;

	fow_each_tunnew_wcu(tunnew64_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}
#endif

#if IS_ENABWED(CONFIG_MPWS)
static int tunnewmpws4_wcv(stwuct sk_buff *skb)
{
	stwuct xfwm_tunnew *handwew;

	if (!pskb_may_puww(skb, sizeof(stwuct mpws_wabew)))
		goto dwop;

	fow_each_tunnew_wcu(tunnewmpws4_handwews, handwew)
		if (!handwew->handwew(skb))
			wetuwn 0;

	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}
#endif

static int tunnew4_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm_tunnew *handwew;

	fow_each_tunnew_wcu(tunnew4_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}

#if IS_ENABWED(CONFIG_IPV6)
static int tunnew64_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm_tunnew *handwew;

	fow_each_tunnew_wcu(tunnew64_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}
#endif

#if IS_ENABWED(CONFIG_MPWS)
static int tunnewmpws4_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct xfwm_tunnew *handwew;

	fow_each_tunnew_wcu(tunnewmpws4_handwews, handwew)
		if (!handwew->eww_handwew(skb, info))
			wetuwn 0;

	wetuwn -ENOENT;
}
#endif

static const stwuct net_pwotocow tunnew4_pwotocow = {
	.handwew	=	tunnew4_wcv,
	.eww_handwew	=	tunnew4_eww,
	.no_powicy	=	1,
};

#if IS_ENABWED(CONFIG_IPV6)
static const stwuct net_pwotocow tunnew64_pwotocow = {
	.handwew	=	tunnew64_wcv,
	.eww_handwew	=	tunnew64_eww,
	.no_powicy	=	1,
};
#endif

#if IS_ENABWED(CONFIG_MPWS)
static const stwuct net_pwotocow tunnewmpws4_pwotocow = {
	.handwew	=	tunnewmpws4_wcv,
	.eww_handwew	=	tunnewmpws4_eww,
	.no_powicy	=	1,
};
#endif

static int __init tunnew4_init(void)
{
	if (inet_add_pwotocow(&tunnew4_pwotocow, IPPWOTO_IPIP))
		goto eww;
#if IS_ENABWED(CONFIG_IPV6)
	if (inet_add_pwotocow(&tunnew64_pwotocow, IPPWOTO_IPV6)) {
		inet_dew_pwotocow(&tunnew4_pwotocow, IPPWOTO_IPIP);
		goto eww;
	}
#endif
#if IS_ENABWED(CONFIG_MPWS)
	if (inet_add_pwotocow(&tunnewmpws4_pwotocow, IPPWOTO_MPWS)) {
		inet_dew_pwotocow(&tunnew4_pwotocow, IPPWOTO_IPIP);
#if IS_ENABWED(CONFIG_IPV6)
		inet_dew_pwotocow(&tunnew64_pwotocow, IPPWOTO_IPV6);
#endif
		goto eww;
	}
#endif
#if IS_ENABWED(CONFIG_INET_XFWM_TUNNEW)
	if (xfwm_input_wegistew_afinfo(&tunnew4_input_afinfo)) {
		inet_dew_pwotocow(&tunnew4_pwotocow, IPPWOTO_IPIP);
#if IS_ENABWED(CONFIG_IPV6)
		inet_dew_pwotocow(&tunnew64_pwotocow, IPPWOTO_IPV6);
#endif
#if IS_ENABWED(CONFIG_MPWS)
		inet_dew_pwotocow(&tunnewmpws4_pwotocow, IPPWOTO_MPWS);
#endif
		goto eww;
	}
#endif
	wetuwn 0;

eww:
	pw_eww("%s: can't add pwotocow\n", __func__);
	wetuwn -EAGAIN;
}

static void __exit tunnew4_fini(void)
{
#if IS_ENABWED(CONFIG_INET_XFWM_TUNNEW)
	if (xfwm_input_unwegistew_afinfo(&tunnew4_input_afinfo))
		pw_eww("tunnew4 cwose: can't wemove input afinfo\n");
#endif
#if IS_ENABWED(CONFIG_MPWS)
	if (inet_dew_pwotocow(&tunnewmpws4_pwotocow, IPPWOTO_MPWS))
		pw_eww("tunnewmpws4 cwose: can't wemove pwotocow\n");
#endif
#if IS_ENABWED(CONFIG_IPV6)
	if (inet_dew_pwotocow(&tunnew64_pwotocow, IPPWOTO_IPV6))
		pw_eww("tunnew64 cwose: can't wemove pwotocow\n");
#endif
	if (inet_dew_pwotocow(&tunnew4_pwotocow, IPPWOTO_IPIP))
		pw_eww("tunnew4 cwose: can't wemove pwotocow\n");
}

moduwe_init(tunnew4_init);
moduwe_exit(tunnew4_fini);
MODUWE_WICENSE("GPW");
