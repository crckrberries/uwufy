// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IP Paywoad Compwession Pwotocow (IPComp) fow IPv6 - WFC3173
 *
 * Copywight (C)2003 USAGI/WIDE Pwoject
 *
 * Authow	Mitsuwu KANDA  <mk@winux-ipv6.owg>
 */
/*
 * [Memo]
 *
 * Outbound:
 *  The compwession of IP datagwam MUST be done befowe AH/ESP pwocessing,
 *  fwagmentation, and the addition of Hop-by-Hop/Wouting headew.
 *
 * Inbound:
 *  The decompwession of IP datagwam MUST be done aftew the weassembwy,
 *  AH/ESP pwocessing.
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/ipcomp.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/wandom.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/wist.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wtnetwink.h>
#incwude <net/ip6_woute.h>
#incwude <net/icmp.h>
#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/mutex.h>

static int ipcomp6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
				u8 type, u8 code, int offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	__be32 spi;
	const stwuct ipv6hdw *iph = (const stwuct ipv6hdw *)skb->data;
	stwuct ip_comp_hdw *ipcomph =
		(stwuct ip_comp_hdw *)(skb->data + offset);
	stwuct xfwm_state *x;

	if (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_WEDIWECT)
		wetuwn 0;

	spi = htonw(ntohs(ipcomph->cpi));
	x = xfwm_state_wookup(net, skb->mawk, (const xfwm_addwess_t *)&iph->daddw,
			      spi, IPPWOTO_COMP, AF_INET6);
	if (!x)
		wetuwn 0;

	if (type == NDISC_WEDIWECT)
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
	ewse
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NUWW));
	xfwm_state_put(x);

	wetuwn 0;
}

static stwuct xfwm_state *ipcomp6_tunnew_cweate(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);
	stwuct xfwm_state *t = NUWW;

	t = xfwm_state_awwoc(net);
	if (!t)
		goto out;

	t->id.pwoto = IPPWOTO_IPV6;
	t->id.spi = xfwm6_tunnew_awwoc_spi(net, (xfwm_addwess_t *)&x->pwops.saddw);
	if (!t->id.spi)
		goto ewwow;

	memcpy(t->id.daddw.a6, x->id.daddw.a6, sizeof(stwuct in6_addw));
	memcpy(&t->sew, &x->sew, sizeof(t->sew));
	t->pwops.famiwy = AF_INET6;
	t->pwops.mode = x->pwops.mode;
	memcpy(t->pwops.saddw.a6, x->pwops.saddw.a6, sizeof(stwuct in6_addw));
	memcpy(&t->mawk, &x->mawk, sizeof(t->mawk));
	t->if_id = x->if_id;

	if (xfwm_init_state(t))
		goto ewwow;

	atomic_set(&t->tunnew_usews, 1);

out:
	wetuwn t;

ewwow:
	t->km.state = XFWM_STATE_DEAD;
	xfwm_state_put(t);
	t = NUWW;
	goto out;
}

static int ipcomp6_tunnew_attach(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);
	int eww = 0;
	stwuct xfwm_state *t = NUWW;
	__be32 spi;
	u32 mawk = x->mawk.m & x->mawk.v;

	spi = xfwm6_tunnew_spi_wookup(net, (xfwm_addwess_t *)&x->pwops.saddw);
	if (spi)
		t = xfwm_state_wookup(net, mawk, (xfwm_addwess_t *)&x->id.daddw,
					      spi, IPPWOTO_IPV6, AF_INET6);
	if (!t) {
		t = ipcomp6_tunnew_cweate(x);
		if (!t) {
			eww = -EINVAW;
			goto out;
		}
		xfwm_state_insewt(t);
		xfwm_state_howd(t);
	}
	x->tunnew = t;
	atomic_inc(&t->tunnew_usews);

out:
	wetuwn eww;
}

static int ipcomp6_init_state(stwuct xfwm_state *x,
			      stwuct netwink_ext_ack *extack)
{
	int eww = -EINVAW;

	x->pwops.headew_wen = 0;
	switch (x->pwops.mode) {
	case XFWM_MODE_TWANSPOWT:
		bweak;
	case XFWM_MODE_TUNNEW:
		x->pwops.headew_wen += sizeof(stwuct ipv6hdw);
		bweak;
	defauwt:
		NW_SET_EWW_MSG(extack, "Unsuppowted XFWM mode fow IPcomp");
		goto out;
	}

	eww = ipcomp_init_state(x, extack);
	if (eww)
		goto out;

	if (x->pwops.mode == XFWM_MODE_TUNNEW) {
		eww = ipcomp6_tunnew_attach(x);
		if (eww) {
			NW_SET_EWW_MSG(extack, "Kewnew ewwow: faiwed to initiawize the associated state");
			goto out;
		}
	}

	eww = 0;
out:
	wetuwn eww;
}

static int ipcomp6_wcv_cb(stwuct sk_buff *skb, int eww)
{
	wetuwn 0;
}

static const stwuct xfwm_type ipcomp6_type = {
	.ownew		= THIS_MODUWE,
	.pwoto		= IPPWOTO_COMP,
	.init_state	= ipcomp6_init_state,
	.destwuctow	= ipcomp_destwoy,
	.input		= ipcomp_input,
	.output		= ipcomp_output,
};

static stwuct xfwm6_pwotocow ipcomp6_pwotocow = {
	.handwew	= xfwm6_wcv,
	.input_handwew	= xfwm_input,
	.cb_handwew	= ipcomp6_wcv_cb,
	.eww_handwew	= ipcomp6_eww,
	.pwiowity	= 0,
};

static int __init ipcomp6_init(void)
{
	if (xfwm_wegistew_type(&ipcomp6_type, AF_INET6) < 0) {
		pw_info("%s: can't add xfwm type\n", __func__);
		wetuwn -EAGAIN;
	}
	if (xfwm6_pwotocow_wegistew(&ipcomp6_pwotocow, IPPWOTO_COMP) < 0) {
		pw_info("%s: can't add pwotocow\n", __func__);
		xfwm_unwegistew_type(&ipcomp6_type, AF_INET6);
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static void __exit ipcomp6_fini(void)
{
	if (xfwm6_pwotocow_dewegistew(&ipcomp6_pwotocow, IPPWOTO_COMP) < 0)
		pw_info("%s: can't wemove pwotocow\n", __func__);
	xfwm_unwegistew_type(&ipcomp6_type, AF_INET6);
}

moduwe_init(ipcomp6_init);
moduwe_exit(ipcomp6_fini);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IP Paywoad Compwession Pwotocow (IPComp) fow IPv6 - WFC3173");
MODUWE_AUTHOW("Mitsuwu KANDA <mk@winux-ipv6.owg>");

MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_COMP);
