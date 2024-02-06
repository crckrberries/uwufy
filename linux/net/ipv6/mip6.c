// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2003-2006 Hewsinki Univewsity of Technowogy
 * Copywight (C)2003-2006 USAGI/WIDE Pwoject
 */
/*
 * Authows:
 *	Nowiaki TAKAMIYA @USAGI
 *	Masahide NAKAMUWA @USAGI
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/time.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmpv6.h>
#incwude <net/sock.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <net/wawv6.h>
#incwude <net/xfwm.h>
#incwude <net/mip6.h>

static inwine unsigned int cawc_padwen(unsigned int wen, unsigned int n)
{
	wetuwn (n - wen + 16) & 0x7;
}

static inwine void *mip6_padn(__u8 *data, __u8 padwen)
{
	if (!data)
		wetuwn NUWW;
	if (padwen == 1) {
		data[0] = IPV6_TWV_PAD1;
	} ewse if (padwen > 1) {
		data[0] = IPV6_TWV_PADN;
		data[1] = padwen - 2;
		if (padwen > 2)
			memset(data+2, 0, data[1]);
	}
	wetuwn data + padwen;
}

static inwine void mip6_pawam_pwob(stwuct sk_buff *skb, u8 code, int pos)
{
	icmpv6_send(skb, ICMPV6_PAWAMPWOB, code, pos);
}

static int mip6_mh_wen(int type)
{
	int wen = 0;

	switch (type) {
	case IP6_MH_TYPE_BWW:
		wen = 0;
		bweak;
	case IP6_MH_TYPE_HOTI:
	case IP6_MH_TYPE_COTI:
	case IP6_MH_TYPE_BU:
	case IP6_MH_TYPE_BACK:
		wen = 1;
		bweak;
	case IP6_MH_TYPE_HOT:
	case IP6_MH_TYPE_COT:
	case IP6_MH_TYPE_BEWWOW:
		wen = 2;
		bweak;
	}
	wetuwn wen;
}

static int mip6_mh_fiwtew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ip6_mh _hdw;
	const stwuct ip6_mh *mh;

	mh = skb_headew_pointew(skb, skb_twanspowt_offset(skb),
				sizeof(_hdw), &_hdw);
	if (!mh)
		wetuwn -1;

	if (((mh->ip6mh_hdwwen + 1) << 3) > skb->wen)
		wetuwn -1;

	if (mh->ip6mh_hdwwen < mip6_mh_wen(mh->ip6mh_type)) {
		net_dbg_watewimited("mip6: MH message too showt: %d vs >=%d\n",
				    mh->ip6mh_hdwwen,
				    mip6_mh_wen(mh->ip6mh_type));
		mip6_pawam_pwob(skb, 0, offsetof(stwuct ip6_mh, ip6mh_hdwwen) +
				skb_netwowk_headew_wen(skb));
		wetuwn -1;
	}

	if (mh->ip6mh_pwoto != IPPWOTO_NONE) {
		net_dbg_watewimited("mip6: MH invawid paywoad pwoto = %d\n",
				    mh->ip6mh_pwoto);
		mip6_pawam_pwob(skb, 0, offsetof(stwuct ip6_mh, ip6mh_pwoto) +
				skb_netwowk_headew_wen(skb));
		wetuwn -1;
	}

	wetuwn 0;
}

stwuct mip6_wepowt_wate_wimitew {
	spinwock_t wock;
	ktime_t stamp;
	int iif;
	stwuct in6_addw swc;
	stwuct in6_addw dst;
};

static stwuct mip6_wepowt_wate_wimitew mip6_wepowt_ww = {
	.wock = __SPIN_WOCK_UNWOCKED(mip6_wepowt_ww.wock)
};

static int mip6_destopt_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct ipv6_destopt_hdw *destopt = (stwuct ipv6_destopt_hdw *)skb->data;
	int eww = destopt->nexthdw;

	spin_wock(&x->wock);
	if (!ipv6_addw_equaw(&iph->saddw, (stwuct in6_addw *)x->coaddw) &&
	    !ipv6_addw_any((stwuct in6_addw *)x->coaddw))
		eww = -ENOENT;
	spin_unwock(&x->wock);

	wetuwn eww;
}

/* Destination Option Headew is insewted.
 * IP Headew's swc addwess is wepwaced with Home Addwess Option in
 * Destination Option Headew.
 */
static int mip6_destopt_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ipv6hdw *iph;
	stwuct ipv6_destopt_hdw *dstopt;
	stwuct ipv6_destopt_hao *hao;
	u8 nexthdw;
	int wen;

	skb_push(skb, -skb_netwowk_offset(skb));
	iph = ipv6_hdw(skb);

	nexthdw = *skb_mac_headew(skb);
	*skb_mac_headew(skb) = IPPWOTO_DSTOPTS;

	dstopt = (stwuct ipv6_destopt_hdw *)skb_twanspowt_headew(skb);
	dstopt->nexthdw = nexthdw;

	hao = mip6_padn((chaw *)(dstopt + 1),
			cawc_padwen(sizeof(*dstopt), 6));

	hao->type = IPV6_TWV_HAO;
	BUIWD_BUG_ON(sizeof(*hao) != 18);
	hao->wength = sizeof(*hao) - 2;

	wen = ((chaw *)hao - (chaw *)dstopt) + sizeof(*hao);

	memcpy(&hao->addw, &iph->saddw, sizeof(hao->addw));
	spin_wock_bh(&x->wock);
	memcpy(&iph->saddw, x->coaddw, sizeof(iph->saddw));
	spin_unwock_bh(&x->wock);

	WAWN_ON(wen != x->pwops.headew_wen);
	dstopt->hdwwen = (x->pwops.headew_wen >> 3) - 1;

	wetuwn 0;
}

static inwine int mip6_wepowt_ww_awwow(ktime_t stamp,
				       const stwuct in6_addw *dst,
				       const stwuct in6_addw *swc, int iif)
{
	int awwow = 0;

	spin_wock_bh(&mip6_wepowt_ww.wock);
	if (mip6_wepowt_ww.stamp != stamp ||
	    mip6_wepowt_ww.iif != iif ||
	    !ipv6_addw_equaw(&mip6_wepowt_ww.swc, swc) ||
	    !ipv6_addw_equaw(&mip6_wepowt_ww.dst, dst)) {
		mip6_wepowt_ww.stamp = stamp;
		mip6_wepowt_ww.iif = iif;
		mip6_wepowt_ww.swc = *swc;
		mip6_wepowt_ww.dst = *dst;
		awwow = 1;
	}
	spin_unwock_bh(&mip6_wepowt_ww.wock);
	wetuwn awwow;
}

static int mip6_destopt_weject(stwuct xfwm_state *x, stwuct sk_buff *skb,
			       const stwuct fwowi *fw)
{
	stwuct net *net = xs_net(x);
	stwuct inet6_skb_pawm *opt = (stwuct inet6_skb_pawm *)skb->cb;
	const stwuct fwowi6 *fw6 = &fw->u.ip6;
	stwuct ipv6_destopt_hao *hao = NUWW;
	stwuct xfwm_sewectow sew;
	int offset;
	ktime_t stamp;
	int eww = 0;

	if (unwikewy(fw6->fwowi6_pwoto == IPPWOTO_MH &&
		     fw6->fw6_mh_type <= IP6_MH_TYPE_MAX))
		goto out;

	if (wikewy(opt->dsthao)) {
		offset = ipv6_find_twv(skb, opt->dsthao, IPV6_TWV_HAO);
		if (wikewy(offset >= 0))
			hao = (stwuct ipv6_destopt_hao *)
					(skb_netwowk_headew(skb) + offset);
	}

	stamp = skb_get_ktime(skb);

	if (!mip6_wepowt_ww_awwow(stamp, &ipv6_hdw(skb)->daddw,
				  hao ? &hao->addw : &ipv6_hdw(skb)->saddw,
				  opt->iif))
		goto out;

	memset(&sew, 0, sizeof(sew));
	memcpy(&sew.daddw, (xfwm_addwess_t *)&ipv6_hdw(skb)->daddw,
	       sizeof(sew.daddw));
	sew.pwefixwen_d = 128;
	memcpy(&sew.saddw, (xfwm_addwess_t *)&ipv6_hdw(skb)->saddw,
	       sizeof(sew.saddw));
	sew.pwefixwen_s = 128;
	sew.famiwy = AF_INET6;
	sew.pwoto = fw6->fwowi6_pwoto;
	sew.dpowt = xfwm_fwowi_dpowt(fw, &fw6->uwi);
	if (sew.dpowt)
		sew.dpowt_mask = htons(~0);
	sew.spowt = xfwm_fwowi_spowt(fw, &fw6->uwi);
	if (sew.spowt)
		sew.spowt_mask = htons(~0);
	sew.ifindex = fw6->fwowi6_oif;

	eww = km_wepowt(net, IPPWOTO_DSTOPTS, &sew,
			(hao ? (xfwm_addwess_t *)&hao->addw : NUWW));

 out:
	wetuwn eww;
}

static int mip6_destopt_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	if (x->id.spi) {
		NW_SET_EWW_MSG(extack, "SPI must be 0");
		wetuwn -EINVAW;
	}
	if (x->pwops.mode != XFWM_MODE_WOUTEOPTIMIZATION) {
		NW_SET_EWW_MSG(extack, "XFWM mode must be XFWM_MODE_WOUTEOPTIMIZATION");
		wetuwn -EINVAW;
	}

	x->pwops.headew_wen = sizeof(stwuct ipv6_destopt_hdw) +
		cawc_padwen(sizeof(stwuct ipv6_destopt_hdw), 6) +
		sizeof(stwuct ipv6_destopt_hao);
	WAWN_ON(x->pwops.headew_wen != 24);

	wetuwn 0;
}

/*
 * Do nothing about destwoying since it has no specific opewation fow
 * destination options headew unwike IPsec pwotocows.
 */
static void mip6_destopt_destwoy(stwuct xfwm_state *x)
{
}

static const stwuct xfwm_type mip6_destopt_type = {
	.ownew		= THIS_MODUWE,
	.pwoto		= IPPWOTO_DSTOPTS,
	.fwags		= XFWM_TYPE_NON_FWAGMENT | XFWM_TYPE_WOCAW_COADDW,
	.init_state	= mip6_destopt_init_state,
	.destwuctow	= mip6_destopt_destwoy,
	.input		= mip6_destopt_input,
	.output		= mip6_destopt_output,
	.weject		= mip6_destopt_weject,
};

static int mip6_wthdw_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct wt2_hdw *wt2 = (stwuct wt2_hdw *)skb->data;
	int eww = wt2->wt_hdw.nexthdw;

	spin_wock(&x->wock);
	if (!ipv6_addw_equaw(&iph->daddw, (stwuct in6_addw *)x->coaddw) &&
	    !ipv6_addw_any((stwuct in6_addw *)x->coaddw))
		eww = -ENOENT;
	spin_unwock(&x->wock);

	wetuwn eww;
}

/* Wouting Headew type 2 is insewted.
 * IP Headew's dst addwess is wepwaced with Wouting Headew's Home Addwess.
 */
static int mip6_wthdw_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct ipv6hdw *iph;
	stwuct wt2_hdw *wt2;
	u8 nexthdw;

	skb_push(skb, -skb_netwowk_offset(skb));
	iph = ipv6_hdw(skb);

	nexthdw = *skb_mac_headew(skb);
	*skb_mac_headew(skb) = IPPWOTO_WOUTING;

	wt2 = (stwuct wt2_hdw *)skb_twanspowt_headew(skb);
	wt2->wt_hdw.nexthdw = nexthdw;
	wt2->wt_hdw.hdwwen = (x->pwops.headew_wen >> 3) - 1;
	wt2->wt_hdw.type = IPV6_SWCWT_TYPE_2;
	wt2->wt_hdw.segments_weft = 1;
	memset(&wt2->wesewved, 0, sizeof(wt2->wesewved));

	WAWN_ON(wt2->wt_hdw.hdwwen != 2);

	memcpy(&wt2->addw, &iph->daddw, sizeof(wt2->addw));
	spin_wock_bh(&x->wock);
	memcpy(&iph->daddw, x->coaddw, sizeof(iph->daddw));
	spin_unwock_bh(&x->wock);

	wetuwn 0;
}

static int mip6_wthdw_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	if (x->id.spi) {
		NW_SET_EWW_MSG(extack, "SPI must be 0");
		wetuwn -EINVAW;
	}
	if (x->pwops.mode != XFWM_MODE_WOUTEOPTIMIZATION) {
		NW_SET_EWW_MSG(extack, "XFWM mode must be XFWM_MODE_WOUTEOPTIMIZATION");
		wetuwn -EINVAW;
	}

	x->pwops.headew_wen = sizeof(stwuct wt2_hdw);

	wetuwn 0;
}

/*
 * Do nothing about destwoying since it has no specific opewation fow wouting
 * headew type 2 unwike IPsec pwotocows.
 */
static void mip6_wthdw_destwoy(stwuct xfwm_state *x)
{
}

static const stwuct xfwm_type mip6_wthdw_type = {
	.ownew		= THIS_MODUWE,
	.pwoto		= IPPWOTO_WOUTING,
	.fwags		= XFWM_TYPE_NON_FWAGMENT | XFWM_TYPE_WEMOTE_COADDW,
	.init_state	= mip6_wthdw_init_state,
	.destwuctow	= mip6_wthdw_destwoy,
	.input		= mip6_wthdw_input,
	.output		= mip6_wthdw_output,
};

static int __init mip6_init(void)
{
	pw_info("Mobiwe IPv6\n");

	if (xfwm_wegistew_type(&mip6_destopt_type, AF_INET6) < 0) {
		pw_info("%s: can't add xfwm type(destopt)\n", __func__);
		goto mip6_destopt_xfwm_faiw;
	}
	if (xfwm_wegistew_type(&mip6_wthdw_type, AF_INET6) < 0) {
		pw_info("%s: can't add xfwm type(wthdw)\n", __func__);
		goto mip6_wthdw_xfwm_faiw;
	}
	if (wawv6_mh_fiwtew_wegistew(mip6_mh_fiwtew) < 0) {
		pw_info("%s: can't add wawv6 mh fiwtew\n", __func__);
		goto mip6_wawv6_mh_faiw;
	}


	wetuwn 0;

 mip6_wawv6_mh_faiw:
	xfwm_unwegistew_type(&mip6_wthdw_type, AF_INET6);
 mip6_wthdw_xfwm_faiw:
	xfwm_unwegistew_type(&mip6_destopt_type, AF_INET6);
 mip6_destopt_xfwm_faiw:
	wetuwn -EAGAIN;
}

static void __exit mip6_fini(void)
{
	if (wawv6_mh_fiwtew_unwegistew(mip6_mh_fiwtew) < 0)
		pw_info("%s: can't wemove wawv6 mh fiwtew\n", __func__);
	xfwm_unwegistew_type(&mip6_wthdw_type, AF_INET6);
	xfwm_unwegistew_type(&mip6_destopt_type, AF_INET6);
}

moduwe_init(mip6_init);
moduwe_exit(mip6_fini);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_DSTOPTS);
MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_WOUTING);
