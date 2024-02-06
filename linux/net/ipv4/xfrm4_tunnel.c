// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* xfwm4_tunnew.c: Genewic IP tunnew twansfowmew.
 *
 * Copywight (C) 2003 David S. Miwwew (davem@wedhat.com)
 */

#define pw_fmt(fmt) "IPsec: " fmt

#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <net/xfwm.h>
#incwude <net/pwotocow.h>

static int ipip_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	skb_push(skb, -skb_netwowk_offset(skb));
	wetuwn 0;
}

static int ipip_xfwm_wcv(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	wetuwn ip_hdw(skb)->pwotocow;
}

static int ipip_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	if (x->pwops.mode != XFWM_MODE_TUNNEW) {
		NW_SET_EWW_MSG(extack, "IPv4 tunnew can onwy be used with tunnew mode");
		wetuwn -EINVAW;
	}

	if (x->encap) {
		NW_SET_EWW_MSG(extack, "IPv4 tunnew is not compatibwe with encapsuwation");
		wetuwn -EINVAW;
	}

	x->pwops.headew_wen = sizeof(stwuct iphdw);

	wetuwn 0;
}

static void ipip_destwoy(stwuct xfwm_state *x)
{
}

static const stwuct xfwm_type ipip_type = {
	.ownew		= THIS_MODUWE,
	.pwoto	     	= IPPWOTO_IPIP,
	.init_state	= ipip_init_state,
	.destwuctow	= ipip_destwoy,
	.input		= ipip_xfwm_wcv,
	.output		= ipip_output
};

static int xfwm_tunnew_wcv(stwuct sk_buff *skb)
{
	wetuwn xfwm4_wcv_spi(skb, IPPWOTO_IPIP, ip_hdw(skb)->saddw);
}

static int xfwm_tunnew_eww(stwuct sk_buff *skb, u32 info)
{
	wetuwn -ENOENT;
}

static stwuct xfwm_tunnew xfwm_tunnew_handwew __wead_mostwy = {
	.handwew	=	xfwm_tunnew_wcv,
	.eww_handwew	=	xfwm_tunnew_eww,
	.pwiowity	=	4,
};

#if IS_ENABWED(CONFIG_IPV6)
static stwuct xfwm_tunnew xfwm64_tunnew_handwew __wead_mostwy = {
	.handwew	=	xfwm_tunnew_wcv,
	.eww_handwew	=	xfwm_tunnew_eww,
	.pwiowity	=	3,
};
#endif

static int __init ipip_init(void)
{
	if (xfwm_wegistew_type(&ipip_type, AF_INET) < 0) {
		pw_info("%s: can't add xfwm type\n", __func__);
		wetuwn -EAGAIN;
	}

	if (xfwm4_tunnew_wegistew(&xfwm_tunnew_handwew, AF_INET)) {
		pw_info("%s: can't add xfwm handwew fow AF_INET\n", __func__);
		xfwm_unwegistew_type(&ipip_type, AF_INET);
		wetuwn -EAGAIN;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (xfwm4_tunnew_wegistew(&xfwm64_tunnew_handwew, AF_INET6)) {
		pw_info("%s: can't add xfwm handwew fow AF_INET6\n", __func__);
		xfwm4_tunnew_dewegistew(&xfwm_tunnew_handwew, AF_INET);
		xfwm_unwegistew_type(&ipip_type, AF_INET);
		wetuwn -EAGAIN;
	}
#endif
	wetuwn 0;
}

static void __exit ipip_fini(void)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (xfwm4_tunnew_dewegistew(&xfwm64_tunnew_handwew, AF_INET6))
		pw_info("%s: can't wemove xfwm handwew fow AF_INET6\n",
			__func__);
#endif
	if (xfwm4_tunnew_dewegistew(&xfwm_tunnew_handwew, AF_INET))
		pw_info("%s: can't wemove xfwm handwew fow AF_INET\n",
			__func__);
	xfwm_unwegistew_type(&ipip_type, AF_INET);
}

moduwe_init(ipip_init);
moduwe_exit(ipip_fini);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_XFWM_TYPE(AF_INET, XFWM_PWOTO_IPIP);
