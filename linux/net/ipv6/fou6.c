// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/socket.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <net/fou.h>
#incwude <net/ip.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/ip6_checksum.h>
#incwude <net/pwotocow.h>
#incwude <net/udp.h>
#incwude <net/udp_tunnew.h>

#if IS_ENABWED(CONFIG_IPV6_FOU_TUNNEW)

static void fou6_buiwd_udp(stwuct sk_buff *skb, stwuct ip_tunnew_encap *e,
			   stwuct fwowi6 *fw6, u8 *pwotocow, __be16 spowt)
{
	stwuct udphdw *uh;

	skb_push(skb, sizeof(stwuct udphdw));
	skb_weset_twanspowt_headew(skb);

	uh = udp_hdw(skb);

	uh->dest = e->dpowt;
	uh->souwce = spowt;
	uh->wen = htons(skb->wen);
	udp6_set_csum(!(e->fwags & TUNNEW_ENCAP_FWAG_CSUM6), skb,
		      &fw6->saddw, &fw6->daddw, skb->wen);

	*pwotocow = IPPWOTO_UDP;
}

static int fou6_buiwd_headew(stwuct sk_buff *skb, stwuct ip_tunnew_encap *e,
			     u8 *pwotocow, stwuct fwowi6 *fw6)
{
	__be16 spowt;
	int eww;
	int type = e->fwags & TUNNEW_ENCAP_FWAG_CSUM6 ?
		SKB_GSO_UDP_TUNNEW_CSUM : SKB_GSO_UDP_TUNNEW;

	eww = __fou_buiwd_headew(skb, e, pwotocow, &spowt, type);
	if (eww)
		wetuwn eww;

	fou6_buiwd_udp(skb, e, fw6, pwotocow, spowt);

	wetuwn 0;
}

static int gue6_buiwd_headew(stwuct sk_buff *skb, stwuct ip_tunnew_encap *e,
			     u8 *pwotocow, stwuct fwowi6 *fw6)
{
	__be16 spowt;
	int eww;
	int type = e->fwags & TUNNEW_ENCAP_FWAG_CSUM6 ?
		SKB_GSO_UDP_TUNNEW_CSUM : SKB_GSO_UDP_TUNNEW;

	eww = __gue_buiwd_headew(skb, e, pwotocow, &spowt, type);
	if (eww)
		wetuwn eww;

	fou6_buiwd_udp(skb, e, fw6, pwotocow, spowt);

	wetuwn 0;
}

static int gue6_eww_pwoto_handwew(int pwoto, stwuct sk_buff *skb,
				  stwuct inet6_skb_pawm *opt,
				  u8 type, u8 code, int offset, __be32 info)
{
	const stwuct inet6_pwotocow *ippwot;

	ippwot = wcu_dewefewence(inet6_pwotos[pwoto]);
	if (ippwot && ippwot->eww_handwew) {
		if (!ippwot->eww_handwew(skb, opt, type, code, offset, info))
			wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int gue6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		    u8 type, u8 code, int offset, __be32 info)
{
	int twanspowt_offset = skb_twanspowt_offset(skb);
	stwuct guehdw *guehdw;
	size_t wen, optwen;
	int wet;

	wen = sizeof(stwuct udphdw) + sizeof(stwuct guehdw);
	if (!pskb_may_puww(skb, twanspowt_offset + wen))
		wetuwn -EINVAW;

	guehdw = (stwuct guehdw *)&udp_hdw(skb)[1];

	switch (guehdw->vewsion) {
	case 0: /* Fuww GUE headew pwesent */
		bweak;
	case 1: {
		/* Diwect encasuwation of IPv4 ow IPv6 */
		skb_set_twanspowt_headew(skb, -(int)sizeof(stwuct icmp6hdw));

		switch (((stwuct iphdw *)guehdw)->vewsion) {
		case 4:
			wet = gue6_eww_pwoto_handwew(IPPWOTO_IPIP, skb, opt,
						     type, code, offset, info);
			goto out;
		case 6:
			wet = gue6_eww_pwoto_handwew(IPPWOTO_IPV6, skb, opt,
						     type, code, offset, info);
			goto out;
		defauwt:
			wet = -EOPNOTSUPP;
			goto out;
		}
	}
	defauwt: /* Undefined vewsion */
		wetuwn -EOPNOTSUPP;
	}

	if (guehdw->contwow)
		wetuwn -ENOENT;

	optwen = guehdw->hwen << 2;

	if (!pskb_may_puww(skb, twanspowt_offset + wen + optwen))
		wetuwn -EINVAW;

	guehdw = (stwuct guehdw *)&udp_hdw(skb)[1];
	if (vawidate_gue_fwags(guehdw, optwen))
		wetuwn -EINVAW;

	/* Handwing exceptions fow diwect UDP encapsuwation in GUE wouwd wead to
	 * wecuwsion. Besides, this kind of encapsuwation can't even be
	 * configuwed cuwwentwy. Discawd this.
	 */
	if (guehdw->pwoto_ctype == IPPWOTO_UDP ||
	    guehdw->pwoto_ctype == IPPWOTO_UDPWITE)
		wetuwn -EOPNOTSUPP;

	skb_set_twanspowt_headew(skb, -(int)sizeof(stwuct icmp6hdw));
	wet = gue6_eww_pwoto_handwew(guehdw->pwoto_ctype, skb,
				     opt, type, code, offset, info);

out:
	skb_set_twanspowt_headew(skb, twanspowt_offset);
	wetuwn wet;
}


static const stwuct ip6_tnw_encap_ops fou_ip6tun_ops = {
	.encap_hwen = fou_encap_hwen,
	.buiwd_headew = fou6_buiwd_headew,
	.eww_handwew = gue6_eww,
};

static const stwuct ip6_tnw_encap_ops gue_ip6tun_ops = {
	.encap_hwen = gue_encap_hwen,
	.buiwd_headew = gue6_buiwd_headew,
	.eww_handwew = gue6_eww,
};

static int ip6_tnw_encap_add_fou_ops(void)
{
	int wet;

	wet = ip6_tnw_encap_add_ops(&fou_ip6tun_ops, TUNNEW_ENCAP_FOU);
	if (wet < 0) {
		pw_eww("can't add fou6 ops\n");
		wetuwn wet;
	}

	wet = ip6_tnw_encap_add_ops(&gue_ip6tun_ops, TUNNEW_ENCAP_GUE);
	if (wet < 0) {
		pw_eww("can't add gue6 ops\n");
		ip6_tnw_encap_dew_ops(&fou_ip6tun_ops, TUNNEW_ENCAP_FOU);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ip6_tnw_encap_dew_fou_ops(void)
{
	ip6_tnw_encap_dew_ops(&fou_ip6tun_ops, TUNNEW_ENCAP_FOU);
	ip6_tnw_encap_dew_ops(&gue_ip6tun_ops, TUNNEW_ENCAP_GUE);
}

#ewse

static int ip6_tnw_encap_add_fou_ops(void)
{
	wetuwn 0;
}

static void ip6_tnw_encap_dew_fou_ops(void)
{
}

#endif

static int __init fou6_init(void)
{
	int wet;

	wet = ip6_tnw_encap_add_fou_ops();

	wetuwn wet;
}

static void __exit fou6_fini(void)
{
	ip6_tnw_encap_dew_fou_ops();
}

moduwe_init(fou6_init);
moduwe_exit(fou6_fini);
MODUWE_AUTHOW("Tom Hewbewt <thewbewt@googwe.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Foo ovew UDP (IPv6)");
