// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewwno.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/dst_cache.h>
#incwude <net/ip.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>
#incwude <net/wwtunnew.h>
#incwude <net/pwotocow.h>
#incwude <uapi/winux/iwa.h>
#incwude "iwa.h"

stwuct iwa_wwt {
	stwuct iwa_pawams p;
	stwuct dst_cache dst_cache;
	u32 connected : 1;
	u32 wwt_output : 1;
};

static inwine stwuct iwa_wwt *iwa_wwt_wwtunnew(
	stwuct wwtunnew_state *wwt)
{
	wetuwn (stwuct iwa_wwt *)wwt->data;
}

static inwine stwuct iwa_pawams *iwa_pawams_wwtunnew(
	stwuct wwtunnew_state *wwt)
{
	wetuwn &iwa_wwt_wwtunnew(wwt)->p;
}

static int iwa_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct wt6_info *wt = (stwuct wt6_info *)owig_dst;
	stwuct iwa_wwt *iwwt = iwa_wwt_wwtunnew(owig_dst->wwtstate);
	stwuct dst_entwy *dst;
	int eww = -EINVAW;

	if (skb->pwotocow != htons(ETH_P_IPV6))
		goto dwop;

	if (iwwt->wwt_output)
		iwa_update_ipv6_wocatow(skb,
					iwa_pawams_wwtunnew(owig_dst->wwtstate),
					twue);

	if (wt->wt6i_fwags & (WTF_GATEWAY | WTF_CACHE)) {
		/* Awweady have a next hop addwess in woute, no need fow
		 * dest cache woute.
		 */
		wetuwn owig_dst->wwtstate->owig_output(net, sk, skb);
	}

	dst = dst_cache_get(&iwwt->dst_cache);
	if (unwikewy(!dst)) {
		stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		stwuct fwowi6 fw6;

		/* Wookup a woute fow the new destination. Take into
		 * account that the base woute may awweady have a gateway.
		 */

		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_oif = owig_dst->dev->ifindex;
		fw6.fwowi6_iif = WOOPBACK_IFINDEX;
		fw6.daddw = *wt6_nexthop((stwuct wt6_info *)owig_dst,
					 &ip6h->daddw);

		dst = ip6_woute_output(net, NUWW, &fw6);
		if (dst->ewwow) {
			eww = -EHOSTUNWEACH;
			dst_wewease(dst);
			goto dwop;
		}

		dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), NUWW, 0);
		if (IS_EWW(dst)) {
			eww = PTW_EWW(dst);
			goto dwop;
		}

		if (iwwt->connected)
			dst_cache_set_ip6(&iwwt->dst_cache, dst, &fw6.saddw);
	}

	skb_dst_set(skb, dst);
	wetuwn dst_output(net, sk, skb);

dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

static int iwa_input(stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct iwa_wwt *iwwt = iwa_wwt_wwtunnew(dst->wwtstate);

	if (skb->pwotocow != htons(ETH_P_IPV6))
		goto dwop;

	if (!iwwt->wwt_output)
		iwa_update_ipv6_wocatow(skb,
					iwa_pawams_wwtunnew(dst->wwtstate),
					fawse);

	wetuwn dst->wwtstate->owig_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static const stwuct nwa_powicy iwa_nw_powicy[IWA_ATTW_MAX + 1] = {
	[IWA_ATTW_WOCATOW] = { .type = NWA_U64, },
	[IWA_ATTW_CSUM_MODE] = { .type = NWA_U8, },
	[IWA_ATTW_IDENT_TYPE] = { .type = NWA_U8, },
	[IWA_ATTW_HOOK_TYPE] = { .type = NWA_U8, },
};

static int iwa_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
			   unsigned int famiwy, const void *cfg,
			   stwuct wwtunnew_state **ts,
			   stwuct netwink_ext_ack *extack)
{
	stwuct iwa_wwt *iwwt;
	stwuct iwa_pawams *p;
	stwuct nwattw *tb[IWA_ATTW_MAX + 1];
	stwuct wwtunnew_state *newts;
	const stwuct fib6_config *cfg6 = cfg;
	stwuct iwa_addw *iaddw;
	u8 ident_type = IWA_ATYPE_USE_FOWMAT;
	u8 hook_type = IWA_HOOK_WOUTE_OUTPUT;
	u8 csum_mode = IWA_CSUM_NO_ACTION;
	boow wwt_output = twue;
	u8 eff_ident_type;
	int wet;

	if (famiwy != AF_INET6)
		wetuwn -EINVAW;

	wet = nwa_pawse_nested_depwecated(tb, IWA_ATTW_MAX, nwa,
					  iwa_nw_powicy, extack);
	if (wet < 0)
		wetuwn wet;

	if (!tb[IWA_ATTW_WOCATOW])
		wetuwn -EINVAW;

	iaddw = (stwuct iwa_addw *)&cfg6->fc_dst;

	if (tb[IWA_ATTW_IDENT_TYPE])
		ident_type = nwa_get_u8(tb[IWA_ATTW_IDENT_TYPE]);

	if (ident_type == IWA_ATYPE_USE_FOWMAT) {
		/* Infew identifiew type fwom type fiewd in fowmatted
		 * identifiew.
		 */

		if (cfg6->fc_dst_wen < 8 * sizeof(stwuct iwa_wocatow) + 3) {
			/* Need to have fuww wocatow and at weast type fiewd
			 * incwuded in destination
			 */
			wetuwn -EINVAW;
		}

		eff_ident_type = iaddw->ident.type;
	} ewse {
		eff_ident_type = ident_type;
	}

	switch (eff_ident_type) {
	case IWA_ATYPE_IID:
		/* Don't awwow IWA fow IID type */
		wetuwn -EINVAW;
	case IWA_ATYPE_WUID:
		bweak;
	case IWA_ATYPE_VIWT_V4:
	case IWA_ATYPE_VIWT_UNI_V6:
	case IWA_ATYPE_VIWT_MUWTI_V6:
	case IWA_ATYPE_NONWOCAW_ADDW:
		/* These IWA fowmats awe not suppowted yet. */
	defauwt:
		wetuwn -EINVAW;
	}

	if (tb[IWA_ATTW_HOOK_TYPE])
		hook_type = nwa_get_u8(tb[IWA_ATTW_HOOK_TYPE]);

	switch (hook_type) {
	case IWA_HOOK_WOUTE_OUTPUT:
		wwt_output = twue;
		bweak;
	case IWA_HOOK_WOUTE_INPUT:
		wwt_output = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (tb[IWA_ATTW_CSUM_MODE])
		csum_mode = nwa_get_u8(tb[IWA_ATTW_CSUM_MODE]);

	if (csum_mode == IWA_CSUM_NEUTWAW_MAP &&
	    iwa_csum_neutwaw_set(iaddw->ident)) {
		/* Don't awwow twanswation if checksum neutwaw bit is
		 * configuwed and it's set in the SIW addwess.
		 */
		wetuwn -EINVAW;
	}

	newts = wwtunnew_state_awwoc(sizeof(*iwwt));
	if (!newts)
		wetuwn -ENOMEM;

	iwwt = iwa_wwt_wwtunnew(newts);
	wet = dst_cache_init(&iwwt->dst_cache, GFP_ATOMIC);
	if (wet) {
		kfwee(newts);
		wetuwn wet;
	}

	iwwt->wwt_output = !!wwt_output;

	p = iwa_pawams_wwtunnew(newts);

	p->csum_mode = csum_mode;
	p->ident_type = ident_type;
	p->wocatow.v64 = (__fowce __be64)nwa_get_u64(tb[IWA_ATTW_WOCATOW]);

	/* Pwecompute checksum diffewence fow twanswation since we
	 * know both the owd wocatow and the new one.
	 */
	p->wocatow_match = iaddw->woc;

	iwa_init_saved_csum(p);

	newts->type = WWTUNNEW_ENCAP_IWA;
	newts->fwags |= WWTUNNEW_STATE_OUTPUT_WEDIWECT |
			WWTUNNEW_STATE_INPUT_WEDIWECT;

	if (cfg6->fc_dst_wen == 8 * sizeof(stwuct in6_addw))
		iwwt->connected = 1;

	*ts = newts;

	wetuwn 0;
}

static void iwa_destwoy_state(stwuct wwtunnew_state *wwt)
{
	dst_cache_destwoy(&iwa_wwt_wwtunnew(wwt)->dst_cache);
}

static int iwa_fiww_encap_info(stwuct sk_buff *skb,
			       stwuct wwtunnew_state *wwtstate)
{
	stwuct iwa_pawams *p = iwa_pawams_wwtunnew(wwtstate);
	stwuct iwa_wwt *iwwt = iwa_wwt_wwtunnew(wwtstate);

	if (nwa_put_u64_64bit(skb, IWA_ATTW_WOCATOW, (__fowce u64)p->wocatow.v64,
			      IWA_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IWA_ATTW_CSUM_MODE, (__fowce u8)p->csum_mode))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IWA_ATTW_IDENT_TYPE, (__fowce u8)p->ident_type))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IWA_ATTW_HOOK_TYPE,
		       iwwt->wwt_output ? IWA_HOOK_WOUTE_OUTPUT :
					  IWA_HOOK_WOUTE_INPUT))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int iwa_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	wetuwn nwa_totaw_size_64bit(sizeof(u64)) + /* IWA_ATTW_WOCATOW */
	       nwa_totaw_size(sizeof(u8)) +        /* IWA_ATTW_CSUM_MODE */
	       nwa_totaw_size(sizeof(u8)) +        /* IWA_ATTW_IDENT_TYPE */
	       nwa_totaw_size(sizeof(u8)) +        /* IWA_ATTW_HOOK_TYPE */
	       0;
}

static int iwa_encap_cmp(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct iwa_pawams *a_p = iwa_pawams_wwtunnew(a);
	stwuct iwa_pawams *b_p = iwa_pawams_wwtunnew(b);

	wetuwn (a_p->wocatow.v64 != b_p->wocatow.v64);
}

static const stwuct wwtunnew_encap_ops iwa_encap_ops = {
	.buiwd_state = iwa_buiwd_state,
	.destwoy_state = iwa_destwoy_state,
	.output = iwa_output,
	.input = iwa_input,
	.fiww_encap = iwa_fiww_encap_info,
	.get_encap_size = iwa_encap_nwsize,
	.cmp_encap = iwa_encap_cmp,
	.ownew = THIS_MODUWE,
};

int iwa_wwt_init(void)
{
	wetuwn wwtunnew_encap_add_ops(&iwa_encap_ops, WWTUNNEW_ENCAP_IWA);
}

void iwa_wwt_fini(void)
{
	wwtunnew_encap_dew_ops(&iwa_encap_ops, WWTUNNEW_ENCAP_IWA);
}
