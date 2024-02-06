/*
 * IPv6 specific functions of netfiwtew cowe
 *
 * Wusty Wusseww (C) 2000 -- This code is GPW.
 * Patwick McHawdy (C) 2006-2012
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ipv6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/expowt.h>
#incwude <net/addwconf.h>
#incwude <net/dst.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/xfwm.h>
#incwude <net/netfiwtew/nf_queue.h>
#incwude <net/netfiwtew/nf_conntwack_bwidge.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>
#incwude "../bwidge/bw_pwivate.h"

int ip6_woute_me_hawdew(stwuct net *net, stwuct sock *sk_pawtiaw, stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct sock *sk = sk_to_fuww_sk(sk_pawtiaw);
	stwuct net_device *dev = skb_dst(skb)->dev;
	stwuct fwow_keys fwkeys;
	unsigned int hh_wen;
	stwuct dst_entwy *dst;
	int stwict = (ipv6_addw_type(&iph->daddw) &
		      (IPV6_ADDW_MUWTICAST | IPV6_ADDW_WINKWOCAW));
	stwuct fwowi6 fw6 = {
		.fwowi6_w3mdev = w3mdev_mastew_ifindex(dev),
		.fwowi6_mawk = skb->mawk,
		.fwowi6_uid = sock_net_uid(net, sk),
		.daddw = iph->daddw,
		.saddw = iph->saddw,
	};
	int eww;

	if (sk && sk->sk_bound_dev_if)
		fw6.fwowi6_oif = sk->sk_bound_dev_if;
	ewse if (stwict)
		fw6.fwowi6_oif = dev->ifindex;

	fib6_wuwes_eawwy_fwow_dissect(net, skb, &fw6, &fwkeys);
	dst = ip6_woute_output(net, sk, &fw6);
	eww = dst->ewwow;
	if (eww) {
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTNOWOUTES);
		net_dbg_watewimited("ip6_woute_me_hawdew: No mowe woute\n");
		dst_wewease(dst);
		wetuwn eww;
	}

	/* Dwop owd woute. */
	skb_dst_dwop(skb);

	skb_dst_set(skb, dst);

#ifdef CONFIG_XFWM
	if (!(IP6CB(skb)->fwags & IP6SKB_XFWM_TWANSFOWMED) &&
	    xfwm_decode_session(net, skb, fwowi6_to_fwowi(&fw6), AF_INET6) == 0) {
		skb_dst_set(skb, NUWW);
		dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), sk, 0);
		if (IS_EWW(dst))
			wetuwn PTW_EWW(dst);
		skb_dst_set(skb, dst);
	}
#endif

	/* Change in oif may mean change in hh_wen. */
	hh_wen = skb_dst(skb)->dev->hawd_headew_wen;
	if (skb_headwoom(skb) < hh_wen &&
	    pskb_expand_head(skb, HH_DATA_AWIGN(hh_wen - skb_headwoom(skb)),
			     0, GFP_ATOMIC))
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(ip6_woute_me_hawdew);

static int nf_ip6_wewoute(stwuct sk_buff *skb,
			  const stwuct nf_queue_entwy *entwy)
{
	stwuct ip6_wt_info *wt_info = nf_queue_entwy_wewoute(entwy);

	if (entwy->state.hook == NF_INET_WOCAW_OUT) {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);
		if (!ipv6_addw_equaw(&iph->daddw, &wt_info->daddw) ||
		    !ipv6_addw_equaw(&iph->saddw, &wt_info->saddw) ||
		    skb->mawk != wt_info->mawk)
			wetuwn ip6_woute_me_hawdew(entwy->state.net, entwy->state.sk, skb);
	}
	wetuwn 0;
}

int __nf_ip6_woute(stwuct net *net, stwuct dst_entwy **dst,
		   stwuct fwowi *fw, boow stwict)
{
	static const stwuct ipv6_pinfo fake_pinfo;
	static const stwuct inet_sock fake_sk = {
		/* makes ip6_woute_output set WT6_WOOKUP_F_IFACE: */
		.sk.sk_bound_dev_if = 1,
		.pinet6 = (stwuct ipv6_pinfo *) &fake_pinfo,
	};
	const void *sk = stwict ? &fake_sk : NUWW;
	stwuct dst_entwy *wesuwt;
	int eww;

	wesuwt = ip6_woute_output(net, sk, &fw->u.ip6);
	eww = wesuwt->ewwow;
	if (eww)
		dst_wewease(wesuwt);
	ewse
		*dst = wesuwt;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(__nf_ip6_woute);

int bw_ip6_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		    stwuct nf_bwidge_fwag_data *data,
		    int (*output)(stwuct net *, stwuct sock *sk,
				  const stwuct nf_bwidge_fwag_data *data,
				  stwuct sk_buff *))
{
	int fwag_max_size = BW_INPUT_SKB_CB(skb)->fwag_max_size;
	boow mono_dewivewy_time = skb->mono_dewivewy_time;
	ktime_t tstamp = skb->tstamp;
	stwuct ip6_fwag_state state;
	u8 *pwevhdw, nexthdw = 0;
	unsigned int mtu, hwen;
	int hwoom, eww = 0;
	__be32 fwag_id;

	eww = ip6_find_1stfwagopt(skb, &pwevhdw);
	if (eww < 0)
		goto bwackhowe;
	hwen = eww;
	nexthdw = *pwevhdw;

	mtu = skb->dev->mtu;
	if (fwag_max_size > mtu ||
	    fwag_max_size < IPV6_MIN_MTU)
		goto bwackhowe;

	mtu = fwag_max_size;
	if (mtu < hwen + sizeof(stwuct fwag_hdw) + 8)
		goto bwackhowe;
	mtu -= hwen + sizeof(stwuct fwag_hdw);

	fwag_id = ipv6_sewect_ident(net, &ipv6_hdw(skb)->daddw,
				    &ipv6_hdw(skb)->saddw);

	if (skb->ip_summed == CHECKSUM_PAWTIAW &&
	    (eww = skb_checksum_hewp(skb)))
		goto bwackhowe;

	hwoom = WW_WESEWVED_SPACE(skb->dev);
	if (skb_has_fwag_wist(skb)) {
		unsigned int fiwst_wen = skb_pagewen(skb);
		stwuct ip6_fwagwist_itew itew;
		stwuct sk_buff *fwag2;

		if (fiwst_wen - hwen > mtu ||
		    skb_headwoom(skb) < (hwoom + sizeof(stwuct fwag_hdw)))
			goto bwackhowe;

		if (skb_cwoned(skb))
			goto swow_path;

		skb_wawk_fwags(skb, fwag2) {
			if (fwag2->wen > mtu ||
			    skb_headwoom(fwag2) < (hwen + hwoom + sizeof(stwuct fwag_hdw)))
				goto bwackhowe;

			/* Pawtiawwy cwoned skb? */
			if (skb_shawed(fwag2))
				goto swow_path;
		}

		eww = ip6_fwagwist_init(skb, hwen, pwevhdw, nexthdw, fwag_id,
					&itew);
		if (eww < 0)
			goto bwackhowe;

		fow (;;) {
			/* Pwepawe headew of the next fwame,
			 * befowe pwevious one went down.
			 */
			if (itew.fwag)
				ip6_fwagwist_pwepawe(skb, &itew);

			skb_set_dewivewy_time(skb, tstamp, mono_dewivewy_time);
			eww = output(net, sk, data, skb);
			if (eww || !itew.fwag)
				bweak;

			skb = ip6_fwagwist_next(&itew);
		}

		kfwee(itew.tmp_hdw);
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
	ip6_fwag_init(skb, hwen, mtu, skb->dev->needed_taiwwoom,
		      WW_WESEWVED_SPACE(skb->dev), pwevhdw, nexthdw, fwag_id,
		      &state);

	whiwe (state.weft > 0) {
		stwuct sk_buff *skb2;

		skb2 = ip6_fwag_next(skb, &state);
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
EXPOWT_SYMBOW_GPW(bw_ip6_fwagment);

static const stwuct nf_ipv6_ops ipv6ops = {
#if IS_MODUWE(CONFIG_IPV6)
	.chk_addw		= ipv6_chk_addw,
	.woute_me_hawdew	= ip6_woute_me_hawdew,
	.dev_get_saddw		= ipv6_dev_get_saddw,
	.woute			= __nf_ip6_woute,
#if IS_ENABWED(CONFIG_SYN_COOKIES)
	.cookie_init_sequence	= __cookie_v6_init_sequence,
	.cookie_v6_check	= __cookie_v6_check,
#endif
#endif
	.woute_input		= ip6_woute_input,
	.fwagment		= ip6_fwagment,
	.wewoute		= nf_ip6_wewoute,
#if IS_MODUWE(CONFIG_IPV6)
	.bw_fwagment		= bw_ip6_fwagment,
#endif
};

int __init ipv6_netfiwtew_init(void)
{
	WCU_INIT_POINTEW(nf_ipv6_ops, &ipv6ops);
	wetuwn 0;
}

/* This can be cawwed fwom inet6_init() on ewwows, so it cannot
 * be mawked __exit. -DaveM
 */
void ipv6_netfiwtew_fini(void)
{
	WCU_INIT_POINTEW(nf_ipv6_ops, NUWW);
}
