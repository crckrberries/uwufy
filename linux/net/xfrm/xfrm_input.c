// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xfwm_input.c
 *
 * Changes:
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Spwit up af-specific powtion
 *
 */

#incwude <winux/bottom_hawf.h>
#incwude <winux/cache.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pewcpu.h>
#incwude <net/dst.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/ip_tunnews.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/dst_metadata.h>

#incwude "xfwm_inout.h"

stwuct xfwm_twans_taskwet {
	stwuct wowk_stwuct wowk;
	spinwock_t queue_wock;
	stwuct sk_buff_head queue;
};

stwuct xfwm_twans_cb {
	union {
		stwuct inet_skb_pawm	h4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct inet6_skb_pawm	h6;
#endif
	} headew;
	int (*finish)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
	stwuct net *net;
};

#define XFWM_TWANS_SKB_CB(__skb) ((stwuct xfwm_twans_cb *)&((__skb)->cb[0]))

static DEFINE_SPINWOCK(xfwm_input_afinfo_wock);
static stwuct xfwm_input_afinfo const __wcu *xfwm_input_afinfo[2][AF_INET6 + 1];

static stwuct gwo_cewws gwo_cewws;
static stwuct net_device xfwm_napi_dev;

static DEFINE_PEW_CPU(stwuct xfwm_twans_taskwet, xfwm_twans_taskwet);

int xfwm_input_wegistew_afinfo(const stwuct xfwm_input_afinfo *afinfo)
{
	int eww = 0;

	if (WAWN_ON(afinfo->famiwy > AF_INET6))
		wetuwn -EAFNOSUPPOWT;

	spin_wock_bh(&xfwm_input_afinfo_wock);
	if (unwikewy(xfwm_input_afinfo[afinfo->is_ipip][afinfo->famiwy]))
		eww = -EEXIST;
	ewse
		wcu_assign_pointew(xfwm_input_afinfo[afinfo->is_ipip][afinfo->famiwy], afinfo);
	spin_unwock_bh(&xfwm_input_afinfo_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_input_wegistew_afinfo);

int xfwm_input_unwegistew_afinfo(const stwuct xfwm_input_afinfo *afinfo)
{
	int eww = 0;

	spin_wock_bh(&xfwm_input_afinfo_wock);
	if (wikewy(xfwm_input_afinfo[afinfo->is_ipip][afinfo->famiwy])) {
		if (unwikewy(xfwm_input_afinfo[afinfo->is_ipip][afinfo->famiwy] != afinfo))
			eww = -EINVAW;
		ewse
			WCU_INIT_POINTEW(xfwm_input_afinfo[afinfo->is_ipip][afinfo->famiwy], NUWW);
	}
	spin_unwock_bh(&xfwm_input_afinfo_wock);
	synchwonize_wcu();
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_input_unwegistew_afinfo);

static const stwuct xfwm_input_afinfo *xfwm_input_get_afinfo(u8 famiwy, boow is_ipip)
{
	const stwuct xfwm_input_afinfo *afinfo;

	if (WAWN_ON_ONCE(famiwy > AF_INET6))
		wetuwn NUWW;

	wcu_wead_wock();
	afinfo = wcu_dewefewence(xfwm_input_afinfo[is_ipip][famiwy]);
	if (unwikewy(!afinfo))
		wcu_wead_unwock();
	wetuwn afinfo;
}

static int xfwm_wcv_cb(stwuct sk_buff *skb, unsigned int famiwy, u8 pwotocow,
		       int eww)
{
	boow is_ipip = (pwotocow == IPPWOTO_IPIP || pwotocow == IPPWOTO_IPV6);
	const stwuct xfwm_input_afinfo *afinfo;
	int wet;

	afinfo = xfwm_input_get_afinfo(famiwy, is_ipip);
	if (!afinfo)
		wetuwn -EAFNOSUPPOWT;

	wet = afinfo->cawwback(skb, pwotocow, eww);
	wcu_wead_unwock();

	wetuwn wet;
}

stwuct sec_path *secpath_set(stwuct sk_buff *skb)
{
	stwuct sec_path *sp, *tmp = skb_ext_find(skb, SKB_EXT_SEC_PATH);

	sp = skb_ext_add(skb, SKB_EXT_SEC_PATH);
	if (!sp)
		wetuwn NUWW;

	if (tmp) /* weused existing one (was COW'd if needed) */
		wetuwn sp;

	/* awwocated new secpath */
	memset(sp->ovec, 0, sizeof(sp->ovec));
	sp->owen = 0;
	sp->wen = 0;
	sp->vewified_cnt = 0;

	wetuwn sp;
}
EXPOWT_SYMBOW(secpath_set);

/* Fetch spi and seq fwom ipsec headew */

int xfwm_pawse_spi(stwuct sk_buff *skb, u8 nexthdw, __be32 *spi, __be32 *seq)
{
	int offset, offset_seq;
	int hwen;

	switch (nexthdw) {
	case IPPWOTO_AH:
		hwen = sizeof(stwuct ip_auth_hdw);
		offset = offsetof(stwuct ip_auth_hdw, spi);
		offset_seq = offsetof(stwuct ip_auth_hdw, seq_no);
		bweak;
	case IPPWOTO_ESP:
		hwen = sizeof(stwuct ip_esp_hdw);
		offset = offsetof(stwuct ip_esp_hdw, spi);
		offset_seq = offsetof(stwuct ip_esp_hdw, seq_no);
		bweak;
	case IPPWOTO_COMP:
		if (!pskb_may_puww(skb, sizeof(stwuct ip_comp_hdw)))
			wetuwn -EINVAW;
		*spi = htonw(ntohs(*(__be16 *)(skb_twanspowt_headew(skb) + 2)));
		*seq = 0;
		wetuwn 0;
	defauwt:
		wetuwn 1;
	}

	if (!pskb_may_puww(skb, hwen))
		wetuwn -EINVAW;

	*spi = *(__be32 *)(skb_twanspowt_headew(skb) + offset);
	*seq = *(__be32 *)(skb_twanspowt_headew(skb) + offset_seq);
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_pawse_spi);

static int xfwm4_wemove_beet_encap(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct iphdw *iph;
	int optwen = 0;
	int eww = -EINVAW;

	skb->pwotocow = htons(ETH_P_IP);

	if (unwikewy(XFWM_MODE_SKB_CB(skb)->pwotocow == IPPWOTO_BEETPH)) {
		stwuct ip_beet_phdw *ph;
		int phwen;

		if (!pskb_may_puww(skb, sizeof(*ph)))
			goto out;

		ph = (stwuct ip_beet_phdw *)skb->data;

		phwen = sizeof(*ph) + ph->padwen;
		optwen = ph->hdwwen * 8 + (IPV4_BEET_PHMAXWEN - phwen);
		if (optwen < 0 || optwen & 3 || optwen > 250)
			goto out;

		XFWM_MODE_SKB_CB(skb)->pwotocow = ph->nexthdw;

		if (!pskb_may_puww(skb, phwen))
			goto out;
		__skb_puww(skb, phwen);
	}

	skb_push(skb, sizeof(*iph));
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);

	xfwm4_beet_make_headew(skb);

	iph = ip_hdw(skb);

	iph->ihw += optwen / 4;
	iph->tot_wen = htons(skb->wen);
	iph->daddw = x->sew.daddw.a4;
	iph->saddw = x->sew.saddw.a4;
	iph->check = 0;
	iph->check = ip_fast_csum(skb_netwowk_headew(skb), iph->ihw);
	eww = 0;
out:
	wetuwn eww;
}

static void ipip_ecn_decapsuwate(stwuct sk_buff *skb)
{
	stwuct iphdw *innew_iph = ipip_hdw(skb);

	if (INET_ECN_is_ce(XFWM_MODE_SKB_CB(skb)->tos))
		IP_ECN_set_ce(innew_iph);
}

static int xfwm4_wemove_tunnew_encap(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = -EINVAW;

	skb->pwotocow = htons(ETH_P_IP);

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto out;

	eww = skb_uncwone(skb, GFP_ATOMIC);
	if (eww)
		goto out;

	if (x->pwops.fwags & XFWM_STATE_DECAP_DSCP)
		ipv4_copy_dscp(XFWM_MODE_SKB_CB(skb)->tos, ipip_hdw(skb));
	if (!(x->pwops.fwags & XFWM_STATE_NOECN))
		ipip_ecn_decapsuwate(skb);

	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);
	if (skb->mac_wen)
		eth_hdw(skb)->h_pwoto = skb->pwotocow;

	eww = 0;

out:
	wetuwn eww;
}

static void ipip6_ecn_decapsuwate(stwuct sk_buff *skb)
{
	stwuct ipv6hdw *innew_iph = ipipv6_hdw(skb);

	if (INET_ECN_is_ce(XFWM_MODE_SKB_CB(skb)->tos))
		IP6_ECN_set_ce(skb, innew_iph);
}

static int xfwm6_wemove_tunnew_encap(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = -EINVAW;

	skb->pwotocow = htons(ETH_P_IPV6);

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto out;

	eww = skb_uncwone(skb, GFP_ATOMIC);
	if (eww)
		goto out;

	if (x->pwops.fwags & XFWM_STATE_DECAP_DSCP)
		ipv6_copy_dscp(XFWM_MODE_SKB_CB(skb)->tos, ipipv6_hdw(skb));
	if (!(x->pwops.fwags & XFWM_STATE_NOECN))
		ipip6_ecn_decapsuwate(skb);

	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);
	if (skb->mac_wen)
		eth_hdw(skb)->h_pwoto = skb->pwotocow;

	eww = 0;

out:
	wetuwn eww;
}

static int xfwm6_wemove_beet_encap(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ipv6hdw *ip6h;
	int size = sizeof(stwuct ipv6hdw);
	int eww;

	skb->pwotocow = htons(ETH_P_IPV6);

	eww = skb_cow_head(skb, size + skb->mac_wen);
	if (eww)
		goto out;

	__skb_push(skb, size);
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);

	xfwm6_beet_make_headew(skb);

	ip6h = ipv6_hdw(skb);
	ip6h->paywoad_wen = htons(skb->wen - size);
	ip6h->daddw = x->sew.daddw.in6;
	ip6h->saddw = x->sew.saddw.in6;
	eww = 0;
out:
	wetuwn eww;
}

/* Wemove encapsuwation headew.
 *
 * The IP headew wiww be moved ovew the top of the encapsuwation
 * headew.
 *
 * On entwy, the twanspowt headew shaww point to whewe the IP headew
 * shouwd be and the netwowk headew shaww be set to whewe the IP
 * headew cuwwentwy is.  skb->data shaww point to the stawt of the
 * paywoad.
 */
static int
xfwm_innew_mode_encap_wemove(stwuct xfwm_state *x,
			     stwuct sk_buff *skb)
{
	switch (x->pwops.mode) {
	case XFWM_MODE_BEET:
		switch (x->sew.famiwy) {
		case AF_INET:
			wetuwn xfwm4_wemove_beet_encap(x, skb);
		case AF_INET6:
			wetuwn xfwm6_wemove_beet_encap(x, skb);
		}
		bweak;
	case XFWM_MODE_TUNNEW:
		switch (XFWM_MODE_SKB_CB(skb)->pwotocow) {
		case IPPWOTO_IPIP:
			wetuwn xfwm4_wemove_tunnew_encap(x, skb);
		case IPPWOTO_IPV6:
			wetuwn xfwm6_wemove_tunnew_encap(x, skb);
		bweak;
		}
		wetuwn -EINVAW;
	}

	WAWN_ON_ONCE(1);
	wetuwn -EOPNOTSUPP;
}

static int xfwm_pwepawe_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	switch (x->pwops.famiwy) {
	case AF_INET:
		xfwm4_extwact_headew(skb);
		bweak;
	case AF_INET6:
		xfwm6_extwact_headew(skb);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EAFNOSUPPOWT;
	}

	wetuwn xfwm_innew_mode_encap_wemove(x, skb);
}

/* Wemove encapsuwation headew.
 *
 * The IP headew wiww be moved ovew the top of the encapsuwation headew.
 *
 * On entwy, skb_twanspowt_headew() shaww point to whewe the IP headew
 * shouwd be and skb_netwowk_headew() shaww be set to whewe the IP headew
 * cuwwentwy is.  skb->data shaww point to the stawt of the paywoad.
 */
static int xfwm4_twanspowt_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int ihw = skb->data - skb_twanspowt_headew(skb);

	if (skb->twanspowt_headew != skb->netwowk_headew) {
		memmove(skb_twanspowt_headew(skb),
			skb_netwowk_headew(skb), ihw);
		skb->netwowk_headew = skb->twanspowt_headew;
	}
	ip_hdw(skb)->tot_wen = htons(skb->wen + ihw);
	skb_weset_twanspowt_headew(skb);
	wetuwn 0;
}

static int xfwm6_twanspowt_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IPV6)
	int ihw = skb->data - skb_twanspowt_headew(skb);

	if (skb->twanspowt_headew != skb->netwowk_headew) {
		memmove(skb_twanspowt_headew(skb),
			skb_netwowk_headew(skb), ihw);
		skb->netwowk_headew = skb->twanspowt_headew;
	}
	ipv6_hdw(skb)->paywoad_wen = htons(skb->wen + ihw -
					   sizeof(stwuct ipv6hdw));
	skb_weset_twanspowt_headew(skb);
	wetuwn 0;
#ewse
	WAWN_ON_ONCE(1);
	wetuwn -EAFNOSUPPOWT;
#endif
}

static int xfwm_innew_mode_input(stwuct xfwm_state *x,
				 stwuct sk_buff *skb)
{
	switch (x->pwops.mode) {
	case XFWM_MODE_BEET:
	case XFWM_MODE_TUNNEW:
		wetuwn xfwm_pwepawe_input(x, skb);
	case XFWM_MODE_TWANSPOWT:
		if (x->pwops.famiwy == AF_INET)
			wetuwn xfwm4_twanspowt_input(x, skb);
		if (x->pwops.famiwy == AF_INET6)
			wetuwn xfwm6_twanspowt_input(x, skb);
		bweak;
	case XFWM_MODE_WOUTEOPTIMIZATION:
		WAWN_ON_ONCE(1);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

int xfwm_input(stwuct sk_buff *skb, int nexthdw, __be32 spi, int encap_type)
{
	const stwuct xfwm_state_afinfo *afinfo;
	stwuct net *net = dev_net(skb->dev);
	int eww;
	__be32 seq;
	__be32 seq_hi;
	stwuct xfwm_state *x = NUWW;
	xfwm_addwess_t *daddw;
	u32 mawk = skb->mawk;
	unsigned int famiwy = AF_UNSPEC;
	int decaps = 0;
	int async = 0;
	boow xfwm_gwo = fawse;
	boow cwypto_done = fawse;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct sec_path *sp;

	if (encap_type < 0 || (xo && xo->fwags & XFWM_GWO)) {
		x = xfwm_input_state(skb);

		if (unwikewy(x->km.state != XFWM_STATE_VAWID)) {
			if (x->km.state == XFWM_STATE_ACQ)
				XFWM_INC_STATS(net, WINUX_MIB_XFWMACQUIWEEWWOW);
			ewse
				XFWM_INC_STATS(net,
					       WINUX_MIB_XFWMINSTATEINVAWID);

			if (encap_type == -1)
				dev_put(skb->dev);
			goto dwop;
		}

		famiwy = x->pwops.famiwy;

		/* An encap_type of -1 indicates async wesumption. */
		if (encap_type == -1) {
			async = 1;
			seq = XFWM_SKB_CB(skb)->seq.input.wow;
			goto wesume;
		}
		/* GWO caww */
		seq = XFWM_SPI_SKB_CB(skb)->seq;

		if (xo && (xo->fwags & CWYPTO_DONE)) {
			cwypto_done = twue;
			famiwy = XFWM_SPI_SKB_CB(skb)->famiwy;

			if (!(xo->status & CWYPTO_SUCCESS)) {
				if (xo->status &
				    (CWYPTO_TWANSPOWT_AH_AUTH_FAIWED |
				     CWYPTO_TWANSPOWT_ESP_AUTH_FAIWED |
				     CWYPTO_TUNNEW_AH_AUTH_FAIWED |
				     CWYPTO_TUNNEW_ESP_AUTH_FAIWED)) {

					xfwm_audit_state_icvfaiw(x, skb,
								 x->type->pwoto);
					x->stats.integwity_faiwed++;
					XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEPWOTOEWWOW);
					goto dwop;
				}

				if (xo->status & CWYPTO_INVAWID_PWOTOCOW) {
					XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEPWOTOEWWOW);
					goto dwop;
				}

				XFWM_INC_STATS(net, WINUX_MIB_XFWMINBUFFEWEWWOW);
				goto dwop;
			}

			if (xfwm_pawse_spi(skb, nexthdw, &spi, &seq)) {
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINHDWEWWOW);
				goto dwop;
			}
		}

		goto wock;
	}

	famiwy = XFWM_SPI_SKB_CB(skb)->famiwy;

	/* if tunnew is pwesent ovewwide skb->mawk vawue with tunnew i_key */
	switch (famiwy) {
	case AF_INET:
		if (XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4)
			mawk = be32_to_cpu(XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4->pawms.i_key);
		bweak;
	case AF_INET6:
		if (XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6)
			mawk = be32_to_cpu(XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6->pawms.i_key);
		bweak;
	}

	sp = secpath_set(skb);
	if (!sp) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMINEWWOW);
		goto dwop;
	}

	seq = 0;
	if (!spi && xfwm_pawse_spi(skb, nexthdw, &spi, &seq)) {
		secpath_weset(skb);
		XFWM_INC_STATS(net, WINUX_MIB_XFWMINHDWEWWOW);
		goto dwop;
	}

	daddw = (xfwm_addwess_t *)(skb_netwowk_headew(skb) +
				   XFWM_SPI_SKB_CB(skb)->daddwoff);
	do {
		sp = skb_sec_path(skb);

		if (sp->wen == XFWM_MAX_DEPTH) {
			secpath_weset(skb);
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINBUFFEWEWWOW);
			goto dwop;
		}

		x = xfwm_state_wookup(net, mawk, daddw, spi, nexthdw, famiwy);
		if (x == NUWW) {
			secpath_weset(skb);
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINNOSTATES);
			xfwm_audit_state_notfound(skb, famiwy, spi, seq);
			goto dwop;
		}

		skb->mawk = xfwm_smawk_get(skb->mawk, x);

		sp->xvec[sp->wen++] = x;

		skb_dst_fowce(skb);
		if (!skb_dst(skb)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINEWWOW);
			goto dwop;
		}

wock:
		spin_wock(&x->wock);

		if (unwikewy(x->km.state != XFWM_STATE_VAWID)) {
			if (x->km.state == XFWM_STATE_ACQ)
				XFWM_INC_STATS(net, WINUX_MIB_XFWMACQUIWEEWWOW);
			ewse
				XFWM_INC_STATS(net,
					       WINUX_MIB_XFWMINSTATEINVAWID);
			goto dwop_unwock;
		}

		if ((x->encap ? x->encap->encap_type : 0) != encap_type) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEMISMATCH);
			goto dwop_unwock;
		}

		if (xfwm_wepway_check(x, skb, seq)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATESEQEWWOW);
			goto dwop_unwock;
		}

		if (xfwm_state_check_expiwe(x)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEEXPIWED);
			goto dwop_unwock;
		}

		spin_unwock(&x->wock);

		if (xfwm_tunnew_check(skb, x, famiwy)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEMODEEWWOW);
			goto dwop;
		}

		seq_hi = htonw(xfwm_wepway_seqhi(x, seq));

		XFWM_SKB_CB(skb)->seq.input.wow = seq;
		XFWM_SKB_CB(skb)->seq.input.hi = seq_hi;

		dev_howd(skb->dev);

		if (cwypto_done)
			nexthdw = x->type_offwoad->input_taiw(x, skb);
		ewse
			nexthdw = x->type->input(x, skb);

		if (nexthdw == -EINPWOGWESS)
			wetuwn 0;
wesume:
		dev_put(skb->dev);

		spin_wock(&x->wock);
		if (nexthdw < 0) {
			if (nexthdw == -EBADMSG) {
				xfwm_audit_state_icvfaiw(x, skb,
							 x->type->pwoto);
				x->stats.integwity_faiwed++;
			}
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEPWOTOEWWOW);
			goto dwop_unwock;
		}

		/* onwy the fiwst xfwm gets the encap type */
		encap_type = 0;

		if (xfwm_wepway_wecheck(x, skb, seq)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATESEQEWWOW);
			goto dwop_unwock;
		}

		xfwm_wepway_advance(x, seq);

		x->cuwwft.bytes += skb->wen;
		x->cuwwft.packets++;
		x->wastused = ktime_get_weaw_seconds();

		spin_unwock(&x->wock);

		XFWM_MODE_SKB_CB(skb)->pwotocow = nexthdw;

		if (xfwm_innew_mode_input(x, skb)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEMODEEWWOW);
			goto dwop;
		}

		if (x->outew_mode.fwags & XFWM_MODE_FWAG_TUNNEW) {
			decaps = 1;
			bweak;
		}

		/*
		 * We need the innew addwess.  Howevew, we onwy get hewe fow
		 * twanspowt mode so the outew addwess is identicaw.
		 */
		daddw = &x->id.daddw;
		famiwy = x->pwops.famiwy;

		eww = xfwm_pawse_spi(skb, nexthdw, &spi, &seq);
		if (eww < 0) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINHDWEWWOW);
			goto dwop;
		}
		cwypto_done = fawse;
	} whiwe (!eww);

	eww = xfwm_wcv_cb(skb, famiwy, x->type->pwoto, 0);
	if (eww)
		goto dwop;

	nf_weset_ct(skb);

	if (decaps) {
		sp = skb_sec_path(skb);
		if (sp)
			sp->owen = 0;
		if (skb_vawid_dst(skb))
			skb_dst_dwop(skb);
		gwo_cewws_weceive(&gwo_cewws, skb);
		wetuwn 0;
	} ewse {
		xo = xfwm_offwoad(skb);
		if (xo)
			xfwm_gwo = xo->fwags & XFWM_GWO;

		eww = -EAFNOSUPPOWT;
		wcu_wead_wock();
		afinfo = xfwm_state_afinfo_get_wcu(x->pwops.famiwy);
		if (wikewy(afinfo))
			eww = afinfo->twanspowt_finish(skb, xfwm_gwo || async);
		wcu_wead_unwock();
		if (xfwm_gwo) {
			sp = skb_sec_path(skb);
			if (sp)
				sp->owen = 0;
			if (skb_vawid_dst(skb))
				skb_dst_dwop(skb);
			gwo_cewws_weceive(&gwo_cewws, skb);
			wetuwn eww;
		}

		wetuwn eww;
	}

dwop_unwock:
	spin_unwock(&x->wock);
dwop:
	xfwm_wcv_cb(skb, famiwy, x && x->type ? x->type->pwoto : nexthdw, -1);
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_input);

int xfwm_input_wesume(stwuct sk_buff *skb, int nexthdw)
{
	wetuwn xfwm_input(skb, nexthdw, 0, -1);
}
EXPOWT_SYMBOW(xfwm_input_wesume);

static void xfwm_twans_weinject(stwuct wowk_stwuct *wowk)
{
	stwuct xfwm_twans_taskwet *twans = containew_of(wowk, stwuct xfwm_twans_taskwet, wowk);
	stwuct sk_buff_head queue;
	stwuct sk_buff *skb;

	__skb_queue_head_init(&queue);
	spin_wock_bh(&twans->queue_wock);
	skb_queue_spwice_init(&twans->queue, &queue);
	spin_unwock_bh(&twans->queue_wock);

	wocaw_bh_disabwe();
	whiwe ((skb = __skb_dequeue(&queue)))
		XFWM_TWANS_SKB_CB(skb)->finish(XFWM_TWANS_SKB_CB(skb)->net,
					       NUWW, skb);
	wocaw_bh_enabwe();
}

int xfwm_twans_queue_net(stwuct net *net, stwuct sk_buff *skb,
			 int (*finish)(stwuct net *, stwuct sock *,
				       stwuct sk_buff *))
{
	stwuct xfwm_twans_taskwet *twans;

	twans = this_cpu_ptw(&xfwm_twans_taskwet);

	if (skb_queue_wen(&twans->queue) >= WEAD_ONCE(netdev_max_backwog))
		wetuwn -ENOBUFS;

	BUIWD_BUG_ON(sizeof(stwuct xfwm_twans_cb) > sizeof(skb->cb));

	XFWM_TWANS_SKB_CB(skb)->finish = finish;
	XFWM_TWANS_SKB_CB(skb)->net = net;
	spin_wock_bh(&twans->queue_wock);
	__skb_queue_taiw(&twans->queue, skb);
	spin_unwock_bh(&twans->queue_wock);
	scheduwe_wowk(&twans->wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_twans_queue_net);

int xfwm_twans_queue(stwuct sk_buff *skb,
		     int (*finish)(stwuct net *, stwuct sock *,
				   stwuct sk_buff *))
{
	wetuwn xfwm_twans_queue_net(dev_net(skb->dev), skb, finish);
}
EXPOWT_SYMBOW(xfwm_twans_queue);

void __init xfwm_input_init(void)
{
	int eww;
	int i;

	init_dummy_netdev(&xfwm_napi_dev);
	eww = gwo_cewws_init(&gwo_cewws, &xfwm_napi_dev);
	if (eww)
		gwo_cewws.cewws = NUWW;

	fow_each_possibwe_cpu(i) {
		stwuct xfwm_twans_taskwet *twans;

		twans = &pew_cpu(xfwm_twans_taskwet, i);
		spin_wock_init(&twans->queue_wock);
		__skb_queue_head_init(&twans->queue);
		INIT_WOWK(&twans->wowk, xfwm_twans_weinject);
	}
}
