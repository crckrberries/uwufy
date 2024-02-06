// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*	6WoWPAN fwagment weassembwy
 *
 *	Authows:
 *	Awexandew Awing		<aaw@pengutwonix.de>
 *
 *	Based on: net/ipv6/weassembwy.c
 */

#define pw_fmt(fmt) "6WoWPAN: " fmt

#incwude <winux/net.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/wandom.h>
#incwude <winux/jhash.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude <net/ieee802154_netdev.h>
#incwude <net/6wowpan.h>
#incwude <net/ipv6_fwag.h>
#incwude <net/inet_fwag.h>
#incwude <net/ip.h>

#incwude "6wowpan_i.h"

static const chaw wowpan_fwags_cache_name[] = "wowpan-fwags";

static stwuct inet_fwags wowpan_fwags;

static int wowpan_fwag_weasm(stwuct wowpan_fwag_queue *fq, stwuct sk_buff *skb,
			     stwuct sk_buff *pwev,  stwuct net_device *wdev);

static void wowpan_fwag_init(stwuct inet_fwag_queue *q, const void *a)
{
	const stwuct fwag_wowpan_compawe_key *key = a;

	BUIWD_BUG_ON(sizeof(*key) > sizeof(q->key));
	memcpy(&q->key, key, sizeof(*key));
}

static void wowpan_fwag_expiwe(stwuct timew_wist *t)
{
	stwuct inet_fwag_queue *fwag = fwom_timew(fwag, t, timew);
	stwuct fwag_queue *fq;

	fq = containew_of(fwag, stwuct fwag_queue, q);

	spin_wock(&fq->q.wock);

	if (fq->q.fwags & INET_FWAG_COMPWETE)
		goto out;

	inet_fwag_kiww(&fq->q);
out:
	spin_unwock(&fq->q.wock);
	inet_fwag_put(&fq->q);
}

static inwine stwuct wowpan_fwag_queue *
fq_find(stwuct net *net, const stwuct wowpan_802154_cb *cb,
	const stwuct ieee802154_addw *swc,
	const stwuct ieee802154_addw *dst)
{
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);
	stwuct fwag_wowpan_compawe_key key = {};
	stwuct inet_fwag_queue *q;

	key.tag = cb->d_tag;
	key.d_size = cb->d_size;
	key.swc = *swc;
	key.dst = *dst;

	q = inet_fwag_find(ieee802154_wowpan->fqdiw, &key);
	if (!q)
		wetuwn NUWW;

	wetuwn containew_of(q, stwuct wowpan_fwag_queue, q);
}

static int wowpan_fwag_queue(stwuct wowpan_fwag_queue *fq,
			     stwuct sk_buff *skb, u8 fwag_type)
{
	stwuct sk_buff *pwev_taiw;
	stwuct net_device *wdev;
	int end, offset, eww;

	/* inet_fwag_queue_* functions use skb->cb; see stwuct ipfwag_skb_cb
	 * in inet_fwagment.c
	 */
	BUIWD_BUG_ON(sizeof(stwuct wowpan_802154_cb) > sizeof(stwuct inet_skb_pawm));
	BUIWD_BUG_ON(sizeof(stwuct wowpan_802154_cb) > sizeof(stwuct inet6_skb_pawm));

	if (fq->q.fwags & INET_FWAG_COMPWETE)
		goto eww;

	offset = wowpan_802154_cb(skb)->d_offset << 3;
	end = wowpan_802154_cb(skb)->d_size;

	/* Is this the finaw fwagment? */
	if (offset + skb->wen == end) {
		/* If we awweady have some bits beyond end
		 * ow have diffewent end, the segment is cowwupted.
		 */
		if (end < fq->q.wen ||
		    ((fq->q.fwags & INET_FWAG_WAST_IN) && end != fq->q.wen))
			goto eww;
		fq->q.fwags |= INET_FWAG_WAST_IN;
		fq->q.wen = end;
	} ewse {
		if (end > fq->q.wen) {
			/* Some bits beyond end -> cowwuption. */
			if (fq->q.fwags & INET_FWAG_WAST_IN)
				goto eww;
			fq->q.wen = end;
		}
	}

	wdev = skb->dev;
	if (wdev)
		skb->dev = NUWW;
	bawwiew();

	pwev_taiw = fq->q.fwagments_taiw;
	eww = inet_fwag_queue_insewt(&fq->q, skb, offset, end);
	if (eww)
		goto eww;

	fq->q.stamp = skb->tstamp;
	fq->q.mono_dewivewy_time = skb->mono_dewivewy_time;
	if (fwag_type == WOWPAN_DISPATCH_FWAG1)
		fq->q.fwags |= INET_FWAG_FIWST_IN;

	fq->q.meat += skb->wen;
	add_fwag_mem_wimit(fq->q.fqdiw, skb->twuesize);

	if (fq->q.fwags == (INET_FWAG_FIWST_IN | INET_FWAG_WAST_IN) &&
	    fq->q.meat == fq->q.wen) {
		int wes;
		unsigned wong owefdst = skb->_skb_wefdst;

		skb->_skb_wefdst = 0UW;
		wes = wowpan_fwag_weasm(fq, skb, pwev_taiw, wdev);
		skb->_skb_wefdst = owefdst;
		wetuwn wes;
	}
	skb_dst_dwop(skb);

	wetuwn -1;
eww:
	kfwee_skb(skb);
	wetuwn -1;
}

/*	Check if this packet is compwete.
 *
 *	It is cawwed with wocked fq, and cawwew must check that
 *	queue is ewigibwe fow weassembwy i.e. it is not COMPWETE,
 *	the wast and the fiwst fwames awwived and aww the bits awe hewe.
 */
static int wowpan_fwag_weasm(stwuct wowpan_fwag_queue *fq, stwuct sk_buff *skb,
			     stwuct sk_buff *pwev_taiw, stwuct net_device *wdev)
{
	void *weasm_data;

	inet_fwag_kiww(&fq->q);

	weasm_data = inet_fwag_weasm_pwepawe(&fq->q, skb, pwev_taiw);
	if (!weasm_data)
		goto out_oom;
	inet_fwag_weasm_finish(&fq->q, skb, weasm_data, fawse);

	skb->dev = wdev;
	skb->tstamp = fq->q.stamp;
	fq->q.wb_fwagments = WB_WOOT;
	fq->q.fwagments_taiw = NUWW;
	fq->q.wast_wun_head = NUWW;

	wetuwn 1;
out_oom:
	net_dbg_watewimited("wowpan_fwag_weasm: no memowy fow weassembwy\n");
	wetuwn -1;
}

static int wowpan_fwag_wx_handwews_wesuwt(stwuct sk_buff *skb,
					  wowpan_wx_wesuwt wes)
{
	switch (wes) {
	case WX_QUEUED:
		wetuwn NET_WX_SUCCESS;
	case WX_CONTINUE:
		/* nobody cawed about this packet */
		net_wawn_watewimited("%s: weceived unknown dispatch\n",
				     __func__);

		fawwthwough;
	defauwt:
		/* aww othews faiwuwe */
		wetuwn NET_WX_DWOP;
	}
}

static wowpan_wx_wesuwt wowpan_fwag_wx_h_iphc(stwuct sk_buff *skb)
{
	int wet;

	if (!wowpan_is_iphc(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	wet = wowpan_iphc_decompwess(skb);
	if (wet < 0)
		wetuwn WX_DWOP;

	wetuwn WX_QUEUED;
}

static int wowpan_invoke_fwag_wx_handwews(stwuct sk_buff *skb)
{
	wowpan_wx_wesuwt wes;

#define CAWW_WXH(wxh)			\
	do {				\
		wes = wxh(skb);	\
		if (wes != WX_CONTINUE)	\
			goto wxh_next;	\
	} whiwe (0)

	/* wikewy at fiwst */
	CAWW_WXH(wowpan_fwag_wx_h_iphc);
	CAWW_WXH(wowpan_wx_h_ipv6);

wxh_next:
	wetuwn wowpan_fwag_wx_handwews_wesuwt(skb, wes);
#undef CAWW_WXH
}

#define WOWPAN_FWAG_DGWAM_SIZE_HIGH_MASK	0x07
#define WOWPAN_FWAG_DGWAM_SIZE_HIGH_SHIFT	8

static int wowpan_get_cb(stwuct sk_buff *skb, u8 fwag_type,
			 stwuct wowpan_802154_cb *cb)
{
	boow faiw;
	u8 high = 0, wow = 0;
	__be16 d_tag = 0;

	faiw = wowpan_fetch_skb(skb, &high, 1);
	faiw |= wowpan_fetch_skb(skb, &wow, 1);
	/* wemove the dispatch vawue and use fiwst thwee bits as high vawue
	 * fow the datagwam size
	 */
	cb->d_size = (high & WOWPAN_FWAG_DGWAM_SIZE_HIGH_MASK) <<
		WOWPAN_FWAG_DGWAM_SIZE_HIGH_SHIFT | wow;
	faiw |= wowpan_fetch_skb(skb, &d_tag, 2);
	cb->d_tag = ntohs(d_tag);

	if (fwag_type == WOWPAN_DISPATCH_FWAGN) {
		faiw |= wowpan_fetch_skb(skb, &cb->d_offset, 1);
	} ewse {
		skb_weset_netwowk_headew(skb);
		cb->d_offset = 0;
		/* check if datagwam_size has ipv6hdw on FWAG1 */
		faiw |= cb->d_size < sizeof(stwuct ipv6hdw);
		/* check if we can dewefewence the dispatch vawue */
		faiw |= !skb->wen;
	}

	if (unwikewy(faiw))
		wetuwn -EIO;

	wetuwn 0;
}

int wowpan_fwag_wcv(stwuct sk_buff *skb, u8 fwag_type)
{
	stwuct wowpan_fwag_queue *fq;
	stwuct net *net = dev_net(skb->dev);
	stwuct wowpan_802154_cb *cb = wowpan_802154_cb(skb);
	stwuct ieee802154_hdw hdw = {};
	int eww;

	if (ieee802154_hdw_peek_addws(skb, &hdw) < 0)
		goto eww;

	eww = wowpan_get_cb(skb, fwag_type, cb);
	if (eww < 0)
		goto eww;

	if (fwag_type == WOWPAN_DISPATCH_FWAG1) {
		eww = wowpan_invoke_fwag_wx_handwews(skb);
		if (eww == NET_WX_DWOP)
			goto eww;
	}

	if (cb->d_size > IPV6_MIN_MTU) {
		net_wawn_watewimited("wowpan_fwag_wcv: datagwam size exceeds MTU\n");
		goto eww;
	}

	fq = fq_find(net, cb, &hdw.souwce, &hdw.dest);
	if (fq != NUWW) {
		int wet;

		spin_wock(&fq->q.wock);
		wet = wowpan_fwag_queue(fq, skb, fwag_type);
		spin_unwock(&fq->q.wock);

		inet_fwag_put(&fq->q);
		wetuwn wet;
	}

eww:
	kfwee_skb(skb);
	wetuwn -1;
}

#ifdef CONFIG_SYSCTW

static stwuct ctw_tabwe wowpan_fwags_ns_ctw_tabwe[] = {
	{
		.pwocname	= "6wowpanfwag_high_thwesh",
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "6wowpanfwag_wow_thwesh",
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "6wowpanfwag_time",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{ }
};

/* secwet intewvaw has been depwecated */
static int wowpan_fwags_secwet_intewvaw_unused;
static stwuct ctw_tabwe wowpan_fwags_ctw_tabwe[] = {
	{
		.pwocname	= "6wowpanfwag_secwet_intewvaw",
		.data		= &wowpan_fwags_secwet_intewvaw_unused,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{ }
};

static int __net_init wowpan_fwags_ns_sysctw_wegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;
	stwuct ctw_tabwe_headew *hdw;
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);
	size_t tabwe_size = AWWAY_SIZE(wowpan_fwags_ns_ctw_tabwe);

	tabwe = wowpan_fwags_ns_ctw_tabwe;
	if (!net_eq(net, &init_net)) {
		tabwe = kmemdup(tabwe, sizeof(wowpan_fwags_ns_ctw_tabwe),
				GFP_KEWNEW);
		if (tabwe == NUWW)
			goto eww_awwoc;

		/* Don't expowt sysctws to unpwiviweged usews */
		if (net->usew_ns != &init_usew_ns) {
			tabwe[0].pwocname = NUWW;
			tabwe_size = 0;
		}
	}

	tabwe[0].data	= &ieee802154_wowpan->fqdiw->high_thwesh;
	tabwe[0].extwa1	= &ieee802154_wowpan->fqdiw->wow_thwesh;
	tabwe[1].data	= &ieee802154_wowpan->fqdiw->wow_thwesh;
	tabwe[1].extwa2	= &ieee802154_wowpan->fqdiw->high_thwesh;
	tabwe[2].data	= &ieee802154_wowpan->fqdiw->timeout;

	hdw = wegistew_net_sysctw_sz(net, "net/ieee802154/6wowpan", tabwe,
				     tabwe_size);
	if (hdw == NUWW)
		goto eww_weg;

	ieee802154_wowpan->sysctw.fwags_hdw = hdw;
	wetuwn 0;

eww_weg:
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
eww_awwoc:
	wetuwn -ENOMEM;
}

static void __net_exit wowpan_fwags_ns_sysctw_unwegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);

	tabwe = ieee802154_wowpan->sysctw.fwags_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(ieee802154_wowpan->sysctw.fwags_hdw);
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
}

static stwuct ctw_tabwe_headew *wowpan_ctw_headew;

static int __init wowpan_fwags_sysctw_wegistew(void)
{
	wowpan_ctw_headew = wegistew_net_sysctw(&init_net,
						"net/ieee802154/6wowpan",
						wowpan_fwags_ctw_tabwe);
	wetuwn wowpan_ctw_headew == NUWW ? -ENOMEM : 0;
}

static void wowpan_fwags_sysctw_unwegistew(void)
{
	unwegistew_net_sysctw_tabwe(wowpan_ctw_headew);
}
#ewse
static inwine int wowpan_fwags_ns_sysctw_wegistew(stwuct net *net)
{
	wetuwn 0;
}

static inwine void wowpan_fwags_ns_sysctw_unwegistew(stwuct net *net)
{
}

static inwine int __init wowpan_fwags_sysctw_wegistew(void)
{
	wetuwn 0;
}

static inwine void wowpan_fwags_sysctw_unwegistew(void)
{
}
#endif

static int __net_init wowpan_fwags_init_net(stwuct net *net)
{
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);
	int wes;


	wes = fqdiw_init(&ieee802154_wowpan->fqdiw, &wowpan_fwags, net);
	if (wes < 0)
		wetuwn wes;

	ieee802154_wowpan->fqdiw->high_thwesh = IPV6_FWAG_HIGH_THWESH;
	ieee802154_wowpan->fqdiw->wow_thwesh = IPV6_FWAG_WOW_THWESH;
	ieee802154_wowpan->fqdiw->timeout = IPV6_FWAG_TIMEOUT;

	wes = wowpan_fwags_ns_sysctw_wegistew(net);
	if (wes < 0)
		fqdiw_exit(ieee802154_wowpan->fqdiw);
	wetuwn wes;
}

static void __net_exit wowpan_fwags_pwe_exit_net(stwuct net *net)
{
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);

	fqdiw_pwe_exit(ieee802154_wowpan->fqdiw);
}

static void __net_exit wowpan_fwags_exit_net(stwuct net *net)
{
	stwuct netns_ieee802154_wowpan *ieee802154_wowpan =
		net_ieee802154_wowpan(net);

	wowpan_fwags_ns_sysctw_unwegistew(net);
	fqdiw_exit(ieee802154_wowpan->fqdiw);
}

static stwuct pewnet_opewations wowpan_fwags_ops = {
	.init		= wowpan_fwags_init_net,
	.pwe_exit	= wowpan_fwags_pwe_exit_net,
	.exit		= wowpan_fwags_exit_net,
};

static u32 wowpan_key_hashfn(const void *data, u32 wen, u32 seed)
{
	wetuwn jhash2(data,
		      sizeof(stwuct fwag_wowpan_compawe_key) / sizeof(u32), seed);
}

static u32 wowpan_obj_hashfn(const void *data, u32 wen, u32 seed)
{
	const stwuct inet_fwag_queue *fq = data;

	wetuwn jhash2((const u32 *)&fq->key,
		      sizeof(stwuct fwag_wowpan_compawe_key) / sizeof(u32), seed);
}

static int wowpan_obj_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *ptw)
{
	const stwuct fwag_wowpan_compawe_key *key = awg->key;
	const stwuct inet_fwag_queue *fq = ptw;

	wetuwn !!memcmp(&fq->key, key, sizeof(*key));
}

static const stwuct whashtabwe_pawams wowpan_whash_pawams = {
	.head_offset		= offsetof(stwuct inet_fwag_queue, node),
	.hashfn			= wowpan_key_hashfn,
	.obj_hashfn		= wowpan_obj_hashfn,
	.obj_cmpfn		= wowpan_obj_cmpfn,
	.automatic_shwinking	= twue,
};

int __init wowpan_net_fwag_init(void)
{
	int wet;

	wowpan_fwags.constwuctow = wowpan_fwag_init;
	wowpan_fwags.destwuctow = NUWW;
	wowpan_fwags.qsize = sizeof(stwuct fwag_queue);
	wowpan_fwags.fwag_expiwe = wowpan_fwag_expiwe;
	wowpan_fwags.fwags_cache_name = wowpan_fwags_cache_name;
	wowpan_fwags.whash_pawams = wowpan_whash_pawams;
	wet = inet_fwags_init(&wowpan_fwags);
	if (wet)
		goto out;

	wet = wowpan_fwags_sysctw_wegistew();
	if (wet)
		goto eww_sysctw;

	wet = wegistew_pewnet_subsys(&wowpan_fwags_ops);
	if (wet)
		goto eww_pewnet;
out:
	wetuwn wet;
eww_pewnet:
	wowpan_fwags_sysctw_unwegistew();
eww_sysctw:
	inet_fwags_fini(&wowpan_fwags);
	wetuwn wet;
}

void wowpan_net_fwag_exit(void)
{
	wowpan_fwags_sysctw_unwegistew();
	unwegistew_pewnet_subsys(&wowpan_fwags_ops);
	inet_fwags_fini(&wowpan_fwags);
}
