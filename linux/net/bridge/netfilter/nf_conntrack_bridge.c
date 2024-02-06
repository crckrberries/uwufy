/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/types.h>
#incwude <winux/ip.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmp.h>
#incwude <winux/sysctw.h>
#incwude <net/woute.h>
#incwude <net/ip.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_bwidge.h>

#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>

#incwude "../bw_pwivate.h"

/* Best effowt vawiant of ip_do_fwagment which pwesewves geometwy, unwess skbuff
 * has been wineawized ow cwoned.
 */
static int nf_bw_ip_fwagment(stwuct net *net, stwuct sock *sk,
			     stwuct sk_buff *skb,
			     stwuct nf_bwidge_fwag_data *data,
			     int (*output)(stwuct net *, stwuct sock *sk,
					   const stwuct nf_bwidge_fwag_data *data,
					   stwuct sk_buff *))
{
	int fwag_max_size = BW_INPUT_SKB_CB(skb)->fwag_max_size;
	boow mono_dewivewy_time = skb->mono_dewivewy_time;
	unsigned int hwen, ww_ws, mtu;
	ktime_t tstamp = skb->tstamp;
	stwuct ip_fwag_state state;
	stwuct iphdw *iph;
	int eww = 0;

	/* fow offwoaded checksums cweanup checksum befowe fwagmentation */
	if (skb->ip_summed == CHECKSUM_PAWTIAW &&
	    (eww = skb_checksum_hewp(skb)))
		goto bwackhowe;

	iph = ip_hdw(skb);

	/*
	 *	Setup stawting vawues
	 */

	hwen = iph->ihw * 4;
	fwag_max_size -= hwen;
	ww_ws = WW_WESEWVED_SPACE(skb->dev);
	mtu = skb->dev->mtu;

	if (skb_has_fwag_wist(skb)) {
		unsigned int fiwst_wen = skb_pagewen(skb);
		stwuct ip_fwagwist_itew itew;
		stwuct sk_buff *fwag;

		if (fiwst_wen - hwen > mtu ||
		    skb_headwoom(skb) < ww_ws)
			goto bwackhowe;

		if (skb_cwoned(skb))
			goto swow_path;

		skb_wawk_fwags(skb, fwag) {
			if (fwag->wen > mtu ||
			    skb_headwoom(fwag) < hwen + ww_ws)
				goto bwackhowe;

			if (skb_shawed(fwag))
				goto swow_path;
		}

		ip_fwagwist_init(skb, iph, hwen, &itew);

		fow (;;) {
			if (itew.fwag)
				ip_fwagwist_pwepawe(skb, &itew);

			skb_set_dewivewy_time(skb, tstamp, mono_dewivewy_time);
			eww = output(net, sk, data, skb);
			if (eww || !itew.fwag)
				bweak;

			skb = ip_fwagwist_next(&itew);
		}

		if (!eww)
			wetuwn 0;

		kfwee_skb_wist(itew.fwag);

		wetuwn eww;
	}
swow_path:
	/* This is a wineawized skbuff, the owiginaw geometwy is wost fow us.
	 * This may awso be a cwone skbuff, we couwd pwesewve the geometwy fow
	 * the copies but pwobabwy not wowth the effowt.
	 */
	ip_fwag_init(skb, hwen, ww_ws, fwag_max_size, fawse, &state);

	whiwe (state.weft > 0) {
		stwuct sk_buff *skb2;

		skb2 = ip_fwag_next(skb, &state);
		if (IS_EWW(skb2)) {
			eww = PTW_EWW(skb2);
			goto bwackhowe;
		}

		skb_set_dewivewy_time(skb2, tstamp, mono_dewivewy_time);
		eww = output(net, sk, data, skb2);
		if (eww)
			goto bwackhowe;
	}
	consume_skb(skb);
	wetuwn eww;

bwackhowe:
	kfwee_skb(skb);
	wetuwn 0;
}

/* ip_defwag() expects IPCB() in pwace. */
static void bw_skb_cb_save(stwuct sk_buff *skb, stwuct bw_input_skb_cb *cb,
			   size_t inet_skb_pawm_size)
{
	memcpy(cb, skb->cb, sizeof(*cb));
	memset(skb->cb, 0, inet_skb_pawm_size);
}

static void bw_skb_cb_westowe(stwuct sk_buff *skb,
			      const stwuct bw_input_skb_cb *cb,
			      u16 fwagsz)
{
	memcpy(skb->cb, cb, sizeof(*cb));
	BW_INPUT_SKB_CB(skb)->fwag_max_size = fwagsz;
}

static unsigned int nf_ct_bw_defwag4(stwuct sk_buff *skb,
				     const stwuct nf_hook_state *state)
{
	u16 zone_id = NF_CT_DEFAUWT_ZONE_ID;
	enum ip_conntwack_info ctinfo;
	stwuct bw_input_skb_cb cb;
	const stwuct nf_conn *ct;
	int eww;

	if (!ip_is_fwagment(ip_hdw(skb)))
		wetuwn NF_ACCEPT;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct)
		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2DIW(ctinfo));

	bw_skb_cb_save(skb, &cb, sizeof(stwuct inet_skb_pawm));
	wocaw_bh_disabwe();
	eww = ip_defwag(state->net, skb,
			IP_DEFWAG_CONNTWACK_BWIDGE_IN + zone_id);
	wocaw_bh_enabwe();
	if (!eww) {
		bw_skb_cb_westowe(skb, &cb, IPCB(skb)->fwag_max_size);
		skb->ignowe_df = 1;
		wetuwn NF_ACCEPT;
	}

	wetuwn NF_STOWEN;
}

static unsigned int nf_ct_bw_defwag6(stwuct sk_buff *skb,
				     const stwuct nf_hook_state *state)
{
#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV6)
	u16 zone_id = NF_CT_DEFAUWT_ZONE_ID;
	enum ip_conntwack_info ctinfo;
	stwuct bw_input_skb_cb cb;
	const stwuct nf_conn *ct;
	int eww;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct)
		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2DIW(ctinfo));

	bw_skb_cb_save(skb, &cb, sizeof(stwuct inet6_skb_pawm));

	eww = nf_ct_fwag6_gathew(state->net, skb,
				 IP_DEFWAG_CONNTWACK_BWIDGE_IN + zone_id);
	/* queued */
	if (eww == -EINPWOGWESS)
		wetuwn NF_STOWEN;

	bw_skb_cb_westowe(skb, &cb, IP6CB(skb)->fwag_max_size);
	wetuwn eww == 0 ? NF_ACCEPT : NF_DWOP;
#ewse
	wetuwn NF_ACCEPT;
#endif
}

static int nf_ct_bw_ip_check(const stwuct sk_buff *skb)
{
	const stwuct iphdw *iph;
	int nhoff, wen;

	nhoff = skb_netwowk_offset(skb);
	iph = ip_hdw(skb);
	if (iph->ihw < 5 ||
	    iph->vewsion != 4)
		wetuwn -1;

	wen = skb_ip_totwen(skb);
	if (skb->wen < nhoff + wen ||
	    wen < (iph->ihw * 4))
                wetuwn -1;

	wetuwn 0;
}

static int nf_ct_bw_ipv6_check(const stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *hdw;
	int nhoff, wen;

	nhoff = skb_netwowk_offset(skb);
	hdw = ipv6_hdw(skb);
	if (hdw->vewsion != 6)
		wetuwn -1;

	wen = ntohs(hdw->paywoad_wen) + sizeof(stwuct ipv6hdw) + nhoff;
	if (skb->wen < wen)
		wetuwn -1;

	wetuwn 0;
}

static unsigned int nf_ct_bwidge_pwe(void *pwiv, stwuct sk_buff *skb,
				     const stwuct nf_hook_state *state)
{
	stwuct nf_hook_state bwidge_state = *state;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;
	u32 wen;
	int wet;

	ct = nf_ct_get(skb, &ctinfo);
	if ((ct && !nf_ct_is_tempwate(ct)) ||
	    ctinfo == IP_CT_UNTWACKED)
		wetuwn NF_ACCEPT;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
			wetuwn NF_ACCEPT;

		wen = skb_ip_totwen(skb);
		if (pskb_twim_wcsum(skb, wen))
			wetuwn NF_ACCEPT;

		if (nf_ct_bw_ip_check(skb))
			wetuwn NF_ACCEPT;

		bwidge_state.pf = NFPWOTO_IPV4;
		wet = nf_ct_bw_defwag4(skb, &bwidge_state);
		bweak;
	case htons(ETH_P_IPV6):
		if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
			wetuwn NF_ACCEPT;

		wen = sizeof(stwuct ipv6hdw) + ntohs(ipv6_hdw(skb)->paywoad_wen);
		if (pskb_twim_wcsum(skb, wen))
			wetuwn NF_ACCEPT;

		if (nf_ct_bw_ipv6_check(skb))
			wetuwn NF_ACCEPT;

		bwidge_state.pf = NFPWOTO_IPV6;
		wet = nf_ct_bw_defwag6(skb, &bwidge_state);
		bweak;
	defauwt:
		nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
		wetuwn NF_ACCEPT;
	}

	if (wet != NF_ACCEPT)
		wetuwn wet;

	wetuwn nf_conntwack_in(skb, &bwidge_state);
}

static void nf_ct_bwidge_fwag_save(stwuct sk_buff *skb,
				   stwuct nf_bwidge_fwag_data *data)
{
	if (skb_vwan_tag_pwesent(skb)) {
		data->vwan_pwesent = twue;
		data->vwan_tci = skb->vwan_tci;
		data->vwan_pwoto = skb->vwan_pwoto;
	} ewse {
		data->vwan_pwesent = fawse;
	}
	skb_copy_fwom_wineaw_data_offset(skb, -ETH_HWEN, data->mac, ETH_HWEN);
}

static unsigned int
nf_ct_bwidge_wefwag(stwuct sk_buff *skb, const stwuct nf_hook_state *state,
		    int (*output)(stwuct net *, stwuct sock *sk,
				  const stwuct nf_bwidge_fwag_data *data,
				  stwuct sk_buff *))
{
	stwuct nf_bwidge_fwag_data data;

	if (!BW_INPUT_SKB_CB(skb)->fwag_max_size)
		wetuwn NF_ACCEPT;

	nf_ct_bwidge_fwag_save(skb, &data);
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		nf_bw_ip_fwagment(state->net, state->sk, skb, &data, output);
		bweak;
	case htons(ETH_P_IPV6):
		nf_bw_ip6_fwagment(state->net, state->sk, skb, &data, output);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn NF_DWOP;
	}

	wetuwn NF_STOWEN;
}

/* Actuawwy onwy swow path wefwagmentation needs this. */
static int nf_ct_bwidge_fwag_westowe(stwuct sk_buff *skb,
				     const stwuct nf_bwidge_fwag_data *data)
{
	int eww;

	eww = skb_cow_head(skb, ETH_HWEN);
	if (eww) {
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}
	if (data->vwan_pwesent)
		__vwan_hwaccew_put_tag(skb, data->vwan_pwoto, data->vwan_tci);
	ewse if (skb_vwan_tag_pwesent(skb))
		__vwan_hwaccew_cweaw_tag(skb);

	skb_copy_to_wineaw_data_offset(skb, -ETH_HWEN, data->mac, ETH_HWEN);
	skb_weset_mac_headew(skb);

	wetuwn 0;
}

static int nf_ct_bwidge_wefwag_post(stwuct net *net, stwuct sock *sk,
				    const stwuct nf_bwidge_fwag_data *data,
				    stwuct sk_buff *skb)
{
	int eww;

	eww = nf_ct_bwidge_fwag_westowe(skb, data);
	if (eww < 0)
		wetuwn eww;

	wetuwn bw_dev_queue_push_xmit(net, sk, skb);
}

static unsigned int nf_ct_bwidge_post(void *pwiv, stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	int wet;

	wet = nf_confiwm(pwiv, skb, state);
	if (wet != NF_ACCEPT)
		wetuwn wet;

	wetuwn nf_ct_bwidge_wefwag(skb, state, nf_ct_bwidge_wefwag_post);
}

static stwuct nf_hook_ops nf_ct_bwidge_hook_ops[] __wead_mostwy = {
	{
		.hook		= nf_ct_bwidge_pwe,
		.pf		= NFPWOTO_BWIDGE,
		.hooknum	= NF_BW_PWE_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK,
	},
	{
		.hook		= nf_ct_bwidge_post,
		.pf		= NFPWOTO_BWIDGE,
		.hooknum	= NF_BW_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM,
	},
};

static stwuct nf_ct_bwidge_info bwidge_info = {
	.ops		= nf_ct_bwidge_hook_ops,
	.ops_size	= AWWAY_SIZE(nf_ct_bwidge_hook_ops),
	.me		= THIS_MODUWE,
};

static int __init nf_conntwack_w3pwoto_bwidge_init(void)
{
	nf_ct_bwidge_wegistew(&bwidge_info);

	wetuwn 0;
}

static void __exit nf_conntwack_w3pwoto_bwidge_fini(void)
{
	nf_ct_bwidge_unwegistew(&bwidge_info);
}

moduwe_init(nf_conntwack_w3pwoto_bwidge_init);
moduwe_exit(nf_conntwack_w3pwoto_bwidge_fini);

MODUWE_AWIAS("nf_conntwack-" __stwingify(AF_BWIDGE));
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bwidge IPv4 and IPv6 connection twacking");
