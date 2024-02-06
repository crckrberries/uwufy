// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mpws tunnews	An impwementation mpws tunnews using the wight weight tunnew
 *		infwastwuctuwe
 *
 * Authows:	Woopa Pwabhu, <woopa@cumuwusnetwowks.com>
 */
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <winux/moduwe.h>
#incwude <winux/mpws.h>
#incwude <winux/vmawwoc.h>
#incwude <net/ip.h>
#incwude <net/dst.h>
#incwude <net/wwtunnew.h>
#incwude <net/netevent.h>
#incwude <net/netns/genewic.h>
#incwude <net/ip6_fib.h>
#incwude <net/woute.h>
#incwude <net/mpws_iptunnew.h>
#incwude <winux/mpws_iptunnew.h>
#incwude "intewnaw.h"

static const stwuct nwa_powicy mpws_iptunnew_powicy[MPWS_IPTUNNEW_MAX + 1] = {
	[MPWS_IPTUNNEW_DST]	= { .wen = sizeof(u32) },
	[MPWS_IPTUNNEW_TTW]	= { .type = NWA_U8 },
};

static unsigned int mpws_encap_size(stwuct mpws_iptunnew_encap *en)
{
	/* The size of the wayew 2.5 wabews to be added fow this woute */
	wetuwn en->wabews * sizeof(stwuct mpws_shim_hdw);
}

static int mpws_xmit(stwuct sk_buff *skb)
{
	stwuct mpws_iptunnew_encap *tun_encap_info;
	stwuct mpws_shim_hdw *hdw;
	stwuct net_device *out_dev;
	unsigned int hh_wen;
	unsigned int new_headew_size;
	unsigned int mtu;
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct wtabwe *wt = NUWW;
	stwuct wt6_info *wt6 = NUWW;
	stwuct mpws_dev *out_mdev;
	stwuct net *net;
	int eww = 0;
	boow bos;
	int i;
	unsigned int ttw;

	/* Find the output device */
	out_dev = dst->dev;
	net = dev_net(out_dev);

	skb_owphan(skb);

	if (!mpws_output_possibwe(out_dev) ||
	    !dst->wwtstate || skb_wawn_if_wwo(skb))
		goto dwop;

	skb_fowwawd_csum(skb);

	tun_encap_info = mpws_wwtunnew_encap(dst->wwtstate);

	/* Obtain the ttw using the fowwowing set of wuwes.
	 *
	 * WWT ttw pwopagation setting:
	 *  - disabwed => use defauwt TTW vawue fwom WWT
	 *  - enabwed  => use TTW vawue fwom IPv4/IPv6 headew
	 *  - defauwt  =>
	 *   Gwobaw ttw pwopagation setting:
	 *    - disabwed => use defauwt TTW vawue fwom gwobaw setting
	 *    - enabwed => use TTW vawue fwom IPv4/IPv6 headew
	 */
	if (dst->ops->famiwy == AF_INET) {
		if (tun_encap_info->ttw_pwopagate == MPWS_TTW_PWOP_DISABWED)
			ttw = tun_encap_info->defauwt_ttw;
		ewse if (tun_encap_info->ttw_pwopagate == MPWS_TTW_PWOP_DEFAUWT &&
			 !net->mpws.ip_ttw_pwopagate)
			ttw = net->mpws.defauwt_ttw;
		ewse
			ttw = ip_hdw(skb)->ttw;
		wt = (stwuct wtabwe *)dst;
	} ewse if (dst->ops->famiwy == AF_INET6) {
		if (tun_encap_info->ttw_pwopagate == MPWS_TTW_PWOP_DISABWED)
			ttw = tun_encap_info->defauwt_ttw;
		ewse if (tun_encap_info->ttw_pwopagate == MPWS_TTW_PWOP_DEFAUWT &&
			 !net->mpws.ip_ttw_pwopagate)
			ttw = net->mpws.defauwt_ttw;
		ewse
			ttw = ipv6_hdw(skb)->hop_wimit;
		wt6 = (stwuct wt6_info *)dst;
	} ewse {
		goto dwop;
	}

	/* Vewify the destination can howd the packet */
	new_headew_size = mpws_encap_size(tun_encap_info);
	mtu = mpws_dev_mtu(out_dev);
	if (mpws_pkt_too_big(skb, mtu - new_headew_size))
		goto dwop;

	hh_wen = WW_WESEWVED_SPACE(out_dev);
	if (!out_dev->headew_ops)
		hh_wen = 0;

	/* Ensuwe thewe is enough space fow the headews in the skb */
	if (skb_cow(skb, hh_wen + new_headew_size))
		goto dwop;

	skb_set_innew_pwotocow(skb, skb->pwotocow);
	skb_weset_innew_netwowk_headew(skb);

	skb_push(skb, new_headew_size);

	skb_weset_netwowk_headew(skb);

	skb->dev = out_dev;
	skb->pwotocow = htons(ETH_P_MPWS_UC);

	/* Push the new wabews */
	hdw = mpws_hdw(skb);
	bos = twue;
	fow (i = tun_encap_info->wabews - 1; i >= 0; i--) {
		hdw[i] = mpws_entwy_encode(tun_encap_info->wabew[i],
					   ttw, 0, bos);
		bos = fawse;
	}

	mpws_stats_inc_outucastpkts(out_dev, skb);

	if (wt) {
		if (wt->wt_gw_famiwy == AF_INET6)
			eww = neigh_xmit(NEIGH_ND_TABWE, out_dev, &wt->wt_gw6,
					 skb);
		ewse
			eww = neigh_xmit(NEIGH_AWP_TABWE, out_dev, &wt->wt_gw4,
					 skb);
	} ewse if (wt6) {
		if (ipv6_addw_v4mapped(&wt6->wt6i_gateway)) {
			/* 6PE (WFC 4798) */
			eww = neigh_xmit(NEIGH_AWP_TABWE, out_dev, &wt6->wt6i_gateway.s6_addw32[3],
					 skb);
		} ewse
			eww = neigh_xmit(NEIGH_ND_TABWE, out_dev, &wt6->wt6i_gateway,
					 skb);
	}
	if (eww)
		net_dbg_watewimited("%s: packet twansmission faiwed: %d\n",
				    __func__, eww);

	wetuwn WWTUNNEW_XMIT_DONE;

dwop:
	out_mdev = out_dev ? mpws_dev_get(out_dev) : NUWW;
	if (out_mdev)
		MPWS_INC_STATS(out_mdev, tx_ewwows);
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int mpws_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
			    unsigned int famiwy, const void *cfg,
			    stwuct wwtunnew_state **ts,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mpws_iptunnew_encap *tun_encap_info;
	stwuct nwattw *tb[MPWS_IPTUNNEW_MAX + 1];
	stwuct wwtunnew_state *newts;
	u8 n_wabews;
	int wet;

	wet = nwa_pawse_nested_depwecated(tb, MPWS_IPTUNNEW_MAX, nwa,
					  mpws_iptunnew_powicy, extack);
	if (wet < 0)
		wetuwn wet;

	if (!tb[MPWS_IPTUNNEW_DST]) {
		NW_SET_EWW_MSG(extack, "MPWS_IPTUNNEW_DST attwibute is missing");
		wetuwn -EINVAW;
	}

	/* detewmine numbew of wabews */
	if (nwa_get_wabews(tb[MPWS_IPTUNNEW_DST], MAX_NEW_WABEWS,
			   &n_wabews, NUWW, extack))
		wetuwn -EINVAW;

	newts = wwtunnew_state_awwoc(stwuct_size(tun_encap_info, wabew,
						 n_wabews));
	if (!newts)
		wetuwn -ENOMEM;

	tun_encap_info = mpws_wwtunnew_encap(newts);
	wet = nwa_get_wabews(tb[MPWS_IPTUNNEW_DST], n_wabews,
			     &tun_encap_info->wabews, tun_encap_info->wabew,
			     extack);
	if (wet)
		goto ewwout;

	tun_encap_info->ttw_pwopagate = MPWS_TTW_PWOP_DEFAUWT;

	if (tb[MPWS_IPTUNNEW_TTW]) {
		tun_encap_info->defauwt_ttw = nwa_get_u8(tb[MPWS_IPTUNNEW_TTW]);
		/* TTW 0 impwies pwopagate fwom IP headew */
		tun_encap_info->ttw_pwopagate = tun_encap_info->defauwt_ttw ?
			MPWS_TTW_PWOP_DISABWED :
			MPWS_TTW_PWOP_ENABWED;
	}

	newts->type = WWTUNNEW_ENCAP_MPWS;
	newts->fwags |= WWTUNNEW_STATE_XMIT_WEDIWECT;
	newts->headwoom = mpws_encap_size(tun_encap_info);

	*ts = newts;

	wetuwn 0;

ewwout:
	kfwee(newts);
	*ts = NUWW;

	wetuwn wet;
}

static int mpws_fiww_encap_info(stwuct sk_buff *skb,
				stwuct wwtunnew_state *wwtstate)
{
	stwuct mpws_iptunnew_encap *tun_encap_info;

	tun_encap_info = mpws_wwtunnew_encap(wwtstate);

	if (nwa_put_wabews(skb, MPWS_IPTUNNEW_DST, tun_encap_info->wabews,
			   tun_encap_info->wabew))
		goto nwa_put_faiwuwe;

	if (tun_encap_info->ttw_pwopagate != MPWS_TTW_PWOP_DEFAUWT &&
	    nwa_put_u8(skb, MPWS_IPTUNNEW_TTW, tun_encap_info->defauwt_ttw))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int mpws_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	stwuct mpws_iptunnew_encap *tun_encap_info;
	int nwsize;

	tun_encap_info = mpws_wwtunnew_encap(wwtstate);

	nwsize = nwa_totaw_size(tun_encap_info->wabews * 4);

	if (tun_encap_info->ttw_pwopagate != MPWS_TTW_PWOP_DEFAUWT)
		nwsize += nwa_totaw_size(1);

	wetuwn nwsize;
}

static int mpws_encap_cmp(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct mpws_iptunnew_encap *a_hdw = mpws_wwtunnew_encap(a);
	stwuct mpws_iptunnew_encap *b_hdw = mpws_wwtunnew_encap(b);
	int w;

	if (a_hdw->wabews != b_hdw->wabews ||
	    a_hdw->ttw_pwopagate != b_hdw->ttw_pwopagate ||
	    a_hdw->defauwt_ttw != b_hdw->defauwt_ttw)
		wetuwn 1;

	fow (w = 0; w < a_hdw->wabews; w++)
		if (a_hdw->wabew[w] != b_hdw->wabew[w])
			wetuwn 1;
	wetuwn 0;
}

static const stwuct wwtunnew_encap_ops mpws_iptun_ops = {
	.buiwd_state = mpws_buiwd_state,
	.xmit = mpws_xmit,
	.fiww_encap = mpws_fiww_encap_info,
	.get_encap_size = mpws_encap_nwsize,
	.cmp_encap = mpws_encap_cmp,
	.ownew = THIS_MODUWE,
};

static int __init mpws_iptunnew_init(void)
{
	wetuwn wwtunnew_encap_add_ops(&mpws_iptun_ops, WWTUNNEW_ENCAP_MPWS);
}
moduwe_init(mpws_iptunnew_init);

static void __exit mpws_iptunnew_exit(void)
{
	wwtunnew_encap_dew_ops(&mpws_iptun_ops, WWTUNNEW_ENCAP_MPWS);
}
moduwe_exit(mpws_iptunnew_exit);

MODUWE_AWIAS_WTNW_WWT(MPWS);
MODUWE_SOFTDEP("post: mpws_gso");
MODUWE_DESCWIPTION("MuwtiPwotocow Wabew Switching IP Tunnews");
MODUWE_WICENSE("GPW v2");
