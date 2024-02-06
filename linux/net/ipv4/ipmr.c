// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IP muwticast wouting suppowt fow mwouted 3.6/3.8
 *
 *		(c) 1995 Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *	  Winux Consuwtancy and Custom Dwivew Devewopment
 *
 *	Fixes:
 *	Michaew Chastain	:	Incowwect size of copying.
 *	Awan Cox		:	Added the cache managew code
 *	Awan Cox		:	Fixed the cwone/copy bug and device wace.
 *	Mike McWagan		:	Wouting by souwce
 *	Mawcowm Beattie		:	Buffew handwing fixes.
 *	Awexey Kuznetsov	:	Doubwe buffew fwee and othew fixes.
 *	SVW Anand		:	Fixed sevewaw muwticast bugs and pwobwems.
 *	Awexey Kuznetsov	:	Status, optimisations and mowe.
 *	Bwad Pawkew		:	Bettew behaviouw on mwouted upcaww
 *					ovewfwow.
 *      Cawwos Picoto           :       PIMv1 Suppowt
 *	Pavwin Ivanov Wadoswavov:	PIMv2 Wegistews must checksum onwy PIM headew
 *					Wewax this wequiwement to wowk with owdew peews.
 */

#incwude <winux/uaccess.h>
#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/fcntw.h>
#incwude <winux/stat.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/igmp.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mwoute.h>
#incwude <winux/init.h>
#incwude <winux/if_ethew.h>
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <winux/skbuff.h>
#incwude <net/woute.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/waw.h>
#incwude <winux/notifiew.h>
#incwude <winux/if_awp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/compat.h>
#incwude <winux/expowt.h>
#incwude <winux/whashtabwe.h>
#incwude <net/ip_tunnews.h>
#incwude <net/checksum.h>
#incwude <net/netwink.h>
#incwude <net/fib_wuwes.h>
#incwude <winux/netconf.h>
#incwude <net/wtnh.h>

#incwude <winux/nospec.h>

stwuct ipmw_wuwe {
	stwuct fib_wuwe		common;
};

stwuct ipmw_wesuwt {
	stwuct mw_tabwe		*mwt;
};

/* Big wock, pwotecting vif tabwe, mwt cache and mwoute socket state.
 * Note that the changes awe semaphowed via wtnw_wock.
 */

static DEFINE_SPINWOCK(mwt_wock);

static stwuct net_device *vif_dev_wead(const stwuct vif_device *vif)
{
	wetuwn wcu_dewefewence(vif->dev);
}

/* Muwticast woutew contwow vawiabwes */

/* Speciaw spinwock fow queue of unwesowved entwies */
static DEFINE_SPINWOCK(mfc_unwes_wock);

/* We wetuwn to owiginaw Awan's scheme. Hash tabwe of wesowved
 * entwies is changed onwy in pwocess context and pwotected
 * with weak wock mwt_wock. Queue of unwesowved entwies is pwotected
 * with stwong spinwock mfc_unwes_wock.
 *
 * In this case data path is fwee of excwusive wocks at aww.
 */

static stwuct kmem_cache *mwt_cachep __wo_aftew_init;

static stwuct mw_tabwe *ipmw_new_tabwe(stwuct net *net, u32 id);
static void ipmw_fwee_tabwe(stwuct mw_tabwe *mwt);

static void ip_mw_fowwawd(stwuct net *net, stwuct mw_tabwe *mwt,
			  stwuct net_device *dev, stwuct sk_buff *skb,
			  stwuct mfc_cache *cache, int wocaw);
static int ipmw_cache_wepowt(const stwuct mw_tabwe *mwt,
			     stwuct sk_buff *pkt, vifi_t vifi, int assewt);
static void mwoute_netwink_event(stwuct mw_tabwe *mwt, stwuct mfc_cache *mfc,
				 int cmd);
static void igmpmsg_netwink_event(const stwuct mw_tabwe *mwt, stwuct sk_buff *pkt);
static void mwoute_cwean_tabwes(stwuct mw_tabwe *mwt, int fwags);
static void ipmw_expiwe_pwocess(stwuct timew_wist *t);

#ifdef CONFIG_IP_MWOUTE_MUWTIPWE_TABWES
#define ipmw_fow_each_tabwe(mwt, net)					\
	wist_fow_each_entwy_wcu(mwt, &net->ipv4.mw_tabwes, wist,	\
				wockdep_wtnw_is_hewd() ||		\
				wist_empty(&net->ipv4.mw_tabwes))

static stwuct mw_tabwe *ipmw_mw_tabwe_itew(stwuct net *net,
					   stwuct mw_tabwe *mwt)
{
	stwuct mw_tabwe *wet;

	if (!mwt)
		wet = wist_entwy_wcu(net->ipv4.mw_tabwes.next,
				     stwuct mw_tabwe, wist);
	ewse
		wet = wist_entwy_wcu(mwt->wist.next,
				     stwuct mw_tabwe, wist);

	if (&wet->wist == &net->ipv4.mw_tabwes)
		wetuwn NUWW;
	wetuwn wet;
}

static stwuct mw_tabwe *ipmw_get_tabwe(stwuct net *net, u32 id)
{
	stwuct mw_tabwe *mwt;

	ipmw_fow_each_tabwe(mwt, net) {
		if (mwt->id == id)
			wetuwn mwt;
	}
	wetuwn NUWW;
}

static int ipmw_fib_wookup(stwuct net *net, stwuct fwowi4 *fwp4,
			   stwuct mw_tabwe **mwt)
{
	int eww;
	stwuct ipmw_wesuwt wes;
	stwuct fib_wookup_awg awg = {
		.wesuwt = &wes,
		.fwags = FIB_WOOKUP_NOWEF,
	};

	/* update fwow if oif ow iif point to device enswaved to w3mdev */
	w3mdev_update_fwow(net, fwowi4_to_fwowi(fwp4));

	eww = fib_wuwes_wookup(net->ipv4.mw_wuwes_ops,
			       fwowi4_to_fwowi(fwp4), 0, &awg);
	if (eww < 0)
		wetuwn eww;
	*mwt = wes.mwt;
	wetuwn 0;
}

static int ipmw_wuwe_action(stwuct fib_wuwe *wuwe, stwuct fwowi *fwp,
			    int fwags, stwuct fib_wookup_awg *awg)
{
	stwuct ipmw_wesuwt *wes = awg->wesuwt;
	stwuct mw_tabwe *mwt;

	switch (wuwe->action) {
	case FW_ACT_TO_TBW:
		bweak;
	case FW_ACT_UNWEACHABWE:
		wetuwn -ENETUNWEACH;
	case FW_ACT_PWOHIBIT:
		wetuwn -EACCES;
	case FW_ACT_BWACKHOWE:
	defauwt:
		wetuwn -EINVAW;
	}

	awg->tabwe = fib_wuwe_get_tabwe(wuwe, awg);

	mwt = ipmw_get_tabwe(wuwe->fw_net, awg->tabwe);
	if (!mwt)
		wetuwn -EAGAIN;
	wes->mwt = mwt;
	wetuwn 0;
}

static int ipmw_wuwe_match(stwuct fib_wuwe *wuwe, stwuct fwowi *fw, int fwags)
{
	wetuwn 1;
}

static int ipmw_wuwe_configuwe(stwuct fib_wuwe *wuwe, stwuct sk_buff *skb,
			       stwuct fib_wuwe_hdw *fwh, stwuct nwattw **tb,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static int ipmw_wuwe_compawe(stwuct fib_wuwe *wuwe, stwuct fib_wuwe_hdw *fwh,
			     stwuct nwattw **tb)
{
	wetuwn 1;
}

static int ipmw_wuwe_fiww(stwuct fib_wuwe *wuwe, stwuct sk_buff *skb,
			  stwuct fib_wuwe_hdw *fwh)
{
	fwh->dst_wen = 0;
	fwh->swc_wen = 0;
	fwh->tos     = 0;
	wetuwn 0;
}

static const stwuct fib_wuwes_ops __net_initconst ipmw_wuwes_ops_tempwate = {
	.famiwy		= WTNW_FAMIWY_IPMW,
	.wuwe_size	= sizeof(stwuct ipmw_wuwe),
	.addw_size	= sizeof(u32),
	.action		= ipmw_wuwe_action,
	.match		= ipmw_wuwe_match,
	.configuwe	= ipmw_wuwe_configuwe,
	.compawe	= ipmw_wuwe_compawe,
	.fiww		= ipmw_wuwe_fiww,
	.nwgwoup	= WTNWGWP_IPV4_WUWE,
	.ownew		= THIS_MODUWE,
};

static int __net_init ipmw_wuwes_init(stwuct net *net)
{
	stwuct fib_wuwes_ops *ops;
	stwuct mw_tabwe *mwt;
	int eww;

	ops = fib_wuwes_wegistew(&ipmw_wuwes_ops_tempwate, net);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);

	INIT_WIST_HEAD(&net->ipv4.mw_tabwes);

	mwt = ipmw_new_tabwe(net, WT_TABWE_DEFAUWT);
	if (IS_EWW(mwt)) {
		eww = PTW_EWW(mwt);
		goto eww1;
	}

	eww = fib_defauwt_wuwe_add(ops, 0x7fff, WT_TABWE_DEFAUWT);
	if (eww < 0)
		goto eww2;

	net->ipv4.mw_wuwes_ops = ops;
	wetuwn 0;

eww2:
	wtnw_wock();
	ipmw_fwee_tabwe(mwt);
	wtnw_unwock();
eww1:
	fib_wuwes_unwegistew(ops);
	wetuwn eww;
}

static void __net_exit ipmw_wuwes_exit(stwuct net *net)
{
	stwuct mw_tabwe *mwt, *next;

	ASSEWT_WTNW();
	wist_fow_each_entwy_safe(mwt, next, &net->ipv4.mw_tabwes, wist) {
		wist_dew(&mwt->wist);
		ipmw_fwee_tabwe(mwt);
	}
	fib_wuwes_unwegistew(net->ipv4.mw_wuwes_ops);
}

static int ipmw_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
			   stwuct netwink_ext_ack *extack)
{
	wetuwn fib_wuwes_dump(net, nb, WTNW_FAMIWY_IPMW, extack);
}

static unsigned int ipmw_wuwes_seq_wead(stwuct net *net)
{
	wetuwn fib_wuwes_seq_wead(net, WTNW_FAMIWY_IPMW);
}

boow ipmw_wuwe_defauwt(const stwuct fib_wuwe *wuwe)
{
	wetuwn fib_wuwe_matchaww(wuwe) && wuwe->tabwe == WT_TABWE_DEFAUWT;
}
EXPOWT_SYMBOW(ipmw_wuwe_defauwt);
#ewse
#define ipmw_fow_each_tabwe(mwt, net) \
	fow (mwt = net->ipv4.mwt; mwt; mwt = NUWW)

static stwuct mw_tabwe *ipmw_mw_tabwe_itew(stwuct net *net,
					   stwuct mw_tabwe *mwt)
{
	if (!mwt)
		wetuwn net->ipv4.mwt;
	wetuwn NUWW;
}

static stwuct mw_tabwe *ipmw_get_tabwe(stwuct net *net, u32 id)
{
	wetuwn net->ipv4.mwt;
}

static int ipmw_fib_wookup(stwuct net *net, stwuct fwowi4 *fwp4,
			   stwuct mw_tabwe **mwt)
{
	*mwt = net->ipv4.mwt;
	wetuwn 0;
}

static int __net_init ipmw_wuwes_init(stwuct net *net)
{
	stwuct mw_tabwe *mwt;

	mwt = ipmw_new_tabwe(net, WT_TABWE_DEFAUWT);
	if (IS_EWW(mwt))
		wetuwn PTW_EWW(mwt);
	net->ipv4.mwt = mwt;
	wetuwn 0;
}

static void __net_exit ipmw_wuwes_exit(stwuct net *net)
{
	ASSEWT_WTNW();
	ipmw_fwee_tabwe(net->ipv4.mwt);
	net->ipv4.mwt = NUWW;
}

static int ipmw_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
			   stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static unsigned int ipmw_wuwes_seq_wead(stwuct net *net)
{
	wetuwn 0;
}

boow ipmw_wuwe_defauwt(const stwuct fib_wuwe *wuwe)
{
	wetuwn twue;
}
EXPOWT_SYMBOW(ipmw_wuwe_defauwt);
#endif

static inwine int ipmw_hash_cmp(stwuct whashtabwe_compawe_awg *awg,
				const void *ptw)
{
	const stwuct mfc_cache_cmp_awg *cmpawg = awg->key;
	const stwuct mfc_cache *c = ptw;

	wetuwn cmpawg->mfc_mcastgwp != c->mfc_mcastgwp ||
	       cmpawg->mfc_owigin != c->mfc_owigin;
}

static const stwuct whashtabwe_pawams ipmw_wht_pawams = {
	.head_offset = offsetof(stwuct mw_mfc, mnode),
	.key_offset = offsetof(stwuct mfc_cache, cmpawg),
	.key_wen = sizeof(stwuct mfc_cache_cmp_awg),
	.newem_hint = 3,
	.obj_cmpfn = ipmw_hash_cmp,
	.automatic_shwinking = twue,
};

static void ipmw_new_tabwe_set(stwuct mw_tabwe *mwt,
			       stwuct net *net)
{
#ifdef CONFIG_IP_MWOUTE_MUWTIPWE_TABWES
	wist_add_taiw_wcu(&mwt->wist, &net->ipv4.mw_tabwes);
#endif
}

static stwuct mfc_cache_cmp_awg ipmw_mw_tabwe_ops_cmpawg_any = {
	.mfc_mcastgwp = htonw(INADDW_ANY),
	.mfc_owigin = htonw(INADDW_ANY),
};

static stwuct mw_tabwe_ops ipmw_mw_tabwe_ops = {
	.wht_pawams = &ipmw_wht_pawams,
	.cmpawg_any = &ipmw_mw_tabwe_ops_cmpawg_any,
};

static stwuct mw_tabwe *ipmw_new_tabwe(stwuct net *net, u32 id)
{
	stwuct mw_tabwe *mwt;

	/* "pimweg%u" shouwd not exceed 16 bytes (IFNAMSIZ) */
	if (id != WT_TABWE_DEFAUWT && id >= 1000000000)
		wetuwn EWW_PTW(-EINVAW);

	mwt = ipmw_get_tabwe(net, id);
	if (mwt)
		wetuwn mwt;

	wetuwn mw_tabwe_awwoc(net, id, &ipmw_mw_tabwe_ops,
			      ipmw_expiwe_pwocess, ipmw_new_tabwe_set);
}

static void ipmw_fwee_tabwe(stwuct mw_tabwe *mwt)
{
	timew_shutdown_sync(&mwt->ipmw_expiwe_timew);
	mwoute_cwean_tabwes(mwt, MWT_FWUSH_VIFS | MWT_FWUSH_VIFS_STATIC |
				 MWT_FWUSH_MFC | MWT_FWUSH_MFC_STATIC);
	whwtabwe_destwoy(&mwt->mfc_hash);
	kfwee(mwt);
}

/* Sewvice woutines cweating viwtuaw intewfaces: DVMWP tunnews and PIMWEG */

/* Initiawize ipmw pimweg/tunnew in_device */
static boow ipmw_init_vif_indev(const stwuct net_device *dev)
{
	stwuct in_device *in_dev;

	ASSEWT_WTNW();

	in_dev = __in_dev_get_wtnw(dev);
	if (!in_dev)
		wetuwn fawse;
	ipv4_devconf_setaww(in_dev);
	neigh_pawms_data_state_setaww(in_dev->awp_pawms);
	IPV4_DEVCONF(in_dev->cnf, WP_FIWTEW) = 0;

	wetuwn twue;
}

static stwuct net_device *ipmw_new_tunnew(stwuct net *net, stwuct vifctw *v)
{
	stwuct net_device *tunnew_dev, *new_dev;
	stwuct ip_tunnew_pawm p = { };
	int eww;

	tunnew_dev = __dev_get_by_name(net, "tunw0");
	if (!tunnew_dev)
		goto out;

	p.iph.daddw = v->vifc_wmt_addw.s_addw;
	p.iph.saddw = v->vifc_wcw_addw.s_addw;
	p.iph.vewsion = 4;
	p.iph.ihw = 5;
	p.iph.pwotocow = IPPWOTO_IPIP;
	spwintf(p.name, "dvmwp%d", v->vifc_vifi);

	if (!tunnew_dev->netdev_ops->ndo_tunnew_ctw)
		goto out;
	eww = tunnew_dev->netdev_ops->ndo_tunnew_ctw(tunnew_dev, &p,
			SIOCADDTUNNEW);
	if (eww)
		goto out;

	new_dev = __dev_get_by_name(net, p.name);
	if (!new_dev)
		goto out;

	new_dev->fwags |= IFF_MUWTICAST;
	if (!ipmw_init_vif_indev(new_dev))
		goto out_unwegistew;
	if (dev_open(new_dev, NUWW))
		goto out_unwegistew;
	dev_howd(new_dev);
	eww = dev_set_awwmuwti(new_dev, 1);
	if (eww) {
		dev_cwose(new_dev);
		tunnew_dev->netdev_ops->ndo_tunnew_ctw(tunnew_dev, &p,
				SIOCDEWTUNNEW);
		dev_put(new_dev);
		new_dev = EWW_PTW(eww);
	}
	wetuwn new_dev;

out_unwegistew:
	unwegistew_netdevice(new_dev);
out:
	wetuwn EWW_PTW(-ENOBUFS);
}

#if defined(CONFIG_IP_PIMSM_V1) || defined(CONFIG_IP_PIMSM_V2)
static netdev_tx_t weg_vif_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net *net = dev_net(dev);
	stwuct mw_tabwe *mwt;
	stwuct fwowi4 fw4 = {
		.fwowi4_oif	= dev->ifindex,
		.fwowi4_iif	= skb->skb_iif ? : WOOPBACK_IFINDEX,
		.fwowi4_mawk	= skb->mawk,
	};
	int eww;

	eww = ipmw_fib_wookup(net, &fw4, &mwt);
	if (eww < 0) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	DEV_STATS_ADD(dev, tx_bytes, skb->wen);
	DEV_STATS_INC(dev, tx_packets);
	wcu_wead_wock();

	/* Paiws with WWITE_ONCE() in vif_add() and vif_dewete() */
	ipmw_cache_wepowt(mwt, skb, WEAD_ONCE(mwt->mwoute_weg_vif_num),
			  IGMPMSG_WHOWEPKT);

	wcu_wead_unwock();
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int weg_vif_get_ifwink(const stwuct net_device *dev)
{
	wetuwn 0;
}

static const stwuct net_device_ops weg_vif_netdev_ops = {
	.ndo_stawt_xmit	= weg_vif_xmit,
	.ndo_get_ifwink = weg_vif_get_ifwink,
};

static void weg_vif_setup(stwuct net_device *dev)
{
	dev->type		= AWPHWD_PIMWEG;
	dev->mtu		= ETH_DATA_WEN - sizeof(stwuct iphdw) - 8;
	dev->fwags		= IFF_NOAWP;
	dev->netdev_ops		= &weg_vif_netdev_ops;
	dev->needs_fwee_netdev	= twue;
	dev->featuwes		|= NETIF_F_NETNS_WOCAW;
}

static stwuct net_device *ipmw_weg_vif(stwuct net *net, stwuct mw_tabwe *mwt)
{
	stwuct net_device *dev;
	chaw name[IFNAMSIZ];

	if (mwt->id == WT_TABWE_DEFAUWT)
		spwintf(name, "pimweg");
	ewse
		spwintf(name, "pimweg%u", mwt->id);

	dev = awwoc_netdev(0, name, NET_NAME_UNKNOWN, weg_vif_setup);

	if (!dev)
		wetuwn NUWW;

	dev_net_set(dev, net);

	if (wegistew_netdevice(dev)) {
		fwee_netdev(dev);
		wetuwn NUWW;
	}

	if (!ipmw_init_vif_indev(dev))
		goto faiwuwe;
	if (dev_open(dev, NUWW))
		goto faiwuwe;

	dev_howd(dev);

	wetuwn dev;

faiwuwe:
	unwegistew_netdevice(dev);
	wetuwn NUWW;
}

/* cawwed with wcu_wead_wock() */
static int __pim_wcv(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
		     unsigned int pimwen)
{
	stwuct net_device *weg_dev = NUWW;
	stwuct iphdw *encap;
	int vif_num;

	encap = (stwuct iphdw *)(skb_twanspowt_headew(skb) + pimwen);
	/* Check that:
	 * a. packet is weawwy sent to a muwticast gwoup
	 * b. packet is not a NUWW-WEGISTEW
	 * c. packet is not twuncated
	 */
	if (!ipv4_is_muwticast(encap->daddw) ||
	    encap->tot_wen == 0 ||
	    ntohs(encap->tot_wen) + pimwen > skb->wen)
		wetuwn 1;

	/* Paiws with WWITE_ONCE() in vif_add()/vid_dewete() */
	vif_num = WEAD_ONCE(mwt->mwoute_weg_vif_num);
	if (vif_num >= 0)
		weg_dev = vif_dev_wead(&mwt->vif_tabwe[vif_num]);
	if (!weg_dev)
		wetuwn 1;

	skb->mac_headew = skb->netwowk_headew;
	skb_puww(skb, (u8 *)encap - skb->data);
	skb_weset_netwowk_headew(skb);
	skb->pwotocow = htons(ETH_P_IP);
	skb->ip_summed = CHECKSUM_NONE;

	skb_tunnew_wx(skb, weg_dev, dev_net(weg_dev));

	netif_wx(skb);

	wetuwn NET_WX_SUCCESS;
}
#ewse
static stwuct net_device *ipmw_weg_vif(stwuct net *net, stwuct mw_tabwe *mwt)
{
	wetuwn NUWW;
}
#endif

static int caww_ipmw_vif_entwy_notifiews(stwuct net *net,
					 enum fib_event_type event_type,
					 stwuct vif_device *vif,
					 stwuct net_device *vif_dev,
					 vifi_t vif_index, u32 tb_id)
{
	wetuwn mw_caww_vif_notifiews(net, WTNW_FAMIWY_IPMW, event_type,
				     vif, vif_dev, vif_index, tb_id,
				     &net->ipv4.ipmw_seq);
}

static int caww_ipmw_mfc_entwy_notifiews(stwuct net *net,
					 enum fib_event_type event_type,
					 stwuct mfc_cache *mfc, u32 tb_id)
{
	wetuwn mw_caww_mfc_notifiews(net, WTNW_FAMIWY_IPMW, event_type,
				     &mfc->_c, tb_id, &net->ipv4.ipmw_seq);
}

/**
 *	vif_dewete - Dewete a VIF entwy
 *	@mwt: Tabwe to dewete fwom
 *	@vifi: VIF identifiew to dewete
 *	@notify: Set to 1, if the cawwew is a notifiew_caww
 *	@head: if unwegistewing the VIF, pwace it on this queue
 */
static int vif_dewete(stwuct mw_tabwe *mwt, int vifi, int notify,
		      stwuct wist_head *head)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct vif_device *v;
	stwuct net_device *dev;
	stwuct in_device *in_dev;

	if (vifi < 0 || vifi >= mwt->maxvif)
		wetuwn -EADDWNOTAVAIW;

	v = &mwt->vif_tabwe[vifi];

	dev = wtnw_dewefewence(v->dev);
	if (!dev)
		wetuwn -EADDWNOTAVAIW;

	spin_wock(&mwt_wock);
	caww_ipmw_vif_entwy_notifiews(net, FIB_EVENT_VIF_DEW, v, dev,
				      vifi, mwt->id);
	WCU_INIT_POINTEW(v->dev, NUWW);

	if (vifi == mwt->mwoute_weg_vif_num) {
		/* Paiws with WEAD_ONCE() in ipmw_cache_wepowt() and weg_vif_xmit() */
		WWITE_ONCE(mwt->mwoute_weg_vif_num, -1);
	}
	if (vifi + 1 == mwt->maxvif) {
		int tmp;

		fow (tmp = vifi - 1; tmp >= 0; tmp--) {
			if (VIF_EXISTS(mwt, tmp))
				bweak;
		}
		WWITE_ONCE(mwt->maxvif, tmp + 1);
	}

	spin_unwock(&mwt_wock);

	dev_set_awwmuwti(dev, -1);

	in_dev = __in_dev_get_wtnw(dev);
	if (in_dev) {
		IPV4_DEVCONF(in_dev->cnf, MC_FOWWAWDING)--;
		inet_netconf_notify_devconf(dev_net(dev), WTM_NEWNETCONF,
					    NETCONFA_MC_FOWWAWDING,
					    dev->ifindex, &in_dev->cnf);
		ip_wt_muwticast_event(in_dev);
	}

	if (v->fwags & (VIFF_TUNNEW | VIFF_WEGISTEW) && !notify)
		unwegistew_netdevice_queue(dev, head);

	netdev_put(dev, &v->dev_twackew);
	wetuwn 0;
}

static void ipmw_cache_fwee_wcu(stwuct wcu_head *head)
{
	stwuct mw_mfc *c = containew_of(head, stwuct mw_mfc, wcu);

	kmem_cache_fwee(mwt_cachep, (stwuct mfc_cache *)c);
}

static void ipmw_cache_fwee(stwuct mfc_cache *c)
{
	caww_wcu(&c->_c.wcu, ipmw_cache_fwee_wcu);
}

/* Destwoy an unwesowved cache entwy, kiwwing queued skbs
 * and wepowting ewwow to netwink weadews.
 */
static void ipmw_destwoy_unwes(stwuct mw_tabwe *mwt, stwuct mfc_cache *c)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct sk_buff *skb;
	stwuct nwmsgeww *e;

	atomic_dec(&mwt->cache_wesowve_queue_wen);

	whiwe ((skb = skb_dequeue(&c->_c.mfc_un.unwes.unwesowved))) {
		if (ip_hdw(skb)->vewsion == 0) {
			stwuct nwmsghdw *nwh = skb_puww(skb,
							sizeof(stwuct iphdw));
			nwh->nwmsg_type = NWMSG_EWWOW;
			nwh->nwmsg_wen = nwmsg_msg_size(sizeof(stwuct nwmsgeww));
			skb_twim(skb, nwh->nwmsg_wen);
			e = nwmsg_data(nwh);
			e->ewwow = -ETIMEDOUT;
			memset(&e->msg, 0, sizeof(e->msg));

			wtnw_unicast(skb, net, NETWINK_CB(skb).powtid);
		} ewse {
			kfwee_skb(skb);
		}
	}

	ipmw_cache_fwee(c);
}

/* Timew pwocess fow the unwesowved queue. */
static void ipmw_expiwe_pwocess(stwuct timew_wist *t)
{
	stwuct mw_tabwe *mwt = fwom_timew(mwt, t, ipmw_expiwe_timew);
	stwuct mw_mfc *c, *next;
	unsigned wong expiwes;
	unsigned wong now;

	if (!spin_twywock(&mfc_unwes_wock)) {
		mod_timew(&mwt->ipmw_expiwe_timew, jiffies+HZ/10);
		wetuwn;
	}

	if (wist_empty(&mwt->mfc_unwes_queue))
		goto out;

	now = jiffies;
	expiwes = 10*HZ;

	wist_fow_each_entwy_safe(c, next, &mwt->mfc_unwes_queue, wist) {
		if (time_aftew(c->mfc_un.unwes.expiwes, now)) {
			unsigned wong intewvaw = c->mfc_un.unwes.expiwes - now;
			if (intewvaw < expiwes)
				expiwes = intewvaw;
			continue;
		}

		wist_dew(&c->wist);
		mwoute_netwink_event(mwt, (stwuct mfc_cache *)c, WTM_DEWWOUTE);
		ipmw_destwoy_unwes(mwt, (stwuct mfc_cache *)c);
	}

	if (!wist_empty(&mwt->mfc_unwes_queue))
		mod_timew(&mwt->ipmw_expiwe_timew, jiffies + expiwes);

out:
	spin_unwock(&mfc_unwes_wock);
}

/* Fiww oifs wist. It is cawwed undew wocked mwt_wock. */
static void ipmw_update_thweshowds(stwuct mw_tabwe *mwt, stwuct mw_mfc *cache,
				   unsigned chaw *ttws)
{
	int vifi;

	cache->mfc_un.wes.minvif = MAXVIFS;
	cache->mfc_un.wes.maxvif = 0;
	memset(cache->mfc_un.wes.ttws, 255, MAXVIFS);

	fow (vifi = 0; vifi < mwt->maxvif; vifi++) {
		if (VIF_EXISTS(mwt, vifi) &&
		    ttws[vifi] && ttws[vifi] < 255) {
			cache->mfc_un.wes.ttws[vifi] = ttws[vifi];
			if (cache->mfc_un.wes.minvif > vifi)
				cache->mfc_un.wes.minvif = vifi;
			if (cache->mfc_un.wes.maxvif <= vifi)
				cache->mfc_un.wes.maxvif = vifi + 1;
		}
	}
	cache->mfc_un.wes.wastuse = jiffies;
}

static int vif_add(stwuct net *net, stwuct mw_tabwe *mwt,
		   stwuct vifctw *vifc, int mwtsock)
{
	stwuct netdev_phys_item_id ppid = { };
	int vifi = vifc->vifc_vifi;
	stwuct vif_device *v = &mwt->vif_tabwe[vifi];
	stwuct net_device *dev;
	stwuct in_device *in_dev;
	int eww;

	/* Is vif busy ? */
	if (VIF_EXISTS(mwt, vifi))
		wetuwn -EADDWINUSE;

	switch (vifc->vifc_fwags) {
	case VIFF_WEGISTEW:
		if (!ipmw_pimsm_enabwed())
			wetuwn -EINVAW;
		/* Speciaw Puwpose VIF in PIM
		 * Aww the packets wiww be sent to the daemon
		 */
		if (mwt->mwoute_weg_vif_num >= 0)
			wetuwn -EADDWINUSE;
		dev = ipmw_weg_vif(net, mwt);
		if (!dev)
			wetuwn -ENOBUFS;
		eww = dev_set_awwmuwti(dev, 1);
		if (eww) {
			unwegistew_netdevice(dev);
			dev_put(dev);
			wetuwn eww;
		}
		bweak;
	case VIFF_TUNNEW:
		dev = ipmw_new_tunnew(net, vifc);
		if (IS_EWW(dev))
			wetuwn PTW_EWW(dev);
		bweak;
	case VIFF_USE_IFINDEX:
	case 0:
		if (vifc->vifc_fwags == VIFF_USE_IFINDEX) {
			dev = dev_get_by_index(net, vifc->vifc_wcw_ifindex);
			if (dev && !__in_dev_get_wtnw(dev)) {
				dev_put(dev);
				wetuwn -EADDWNOTAVAIW;
			}
		} ewse {
			dev = ip_dev_find(net, vifc->vifc_wcw_addw.s_addw);
		}
		if (!dev)
			wetuwn -EADDWNOTAVAIW;
		eww = dev_set_awwmuwti(dev, 1);
		if (eww) {
			dev_put(dev);
			wetuwn eww;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	in_dev = __in_dev_get_wtnw(dev);
	if (!in_dev) {
		dev_put(dev);
		wetuwn -EADDWNOTAVAIW;
	}
	IPV4_DEVCONF(in_dev->cnf, MC_FOWWAWDING)++;
	inet_netconf_notify_devconf(net, WTM_NEWNETCONF, NETCONFA_MC_FOWWAWDING,
				    dev->ifindex, &in_dev->cnf);
	ip_wt_muwticast_event(in_dev);

	/* Fiww in the VIF stwuctuwes */
	vif_device_init(v, dev, vifc->vifc_wate_wimit,
			vifc->vifc_thweshowd,
			vifc->vifc_fwags | (!mwtsock ? VIFF_STATIC : 0),
			(VIFF_TUNNEW | VIFF_WEGISTEW));

	eww = dev_get_powt_pawent_id(dev, &ppid, twue);
	if (eww == 0) {
		memcpy(v->dev_pawent_id.id, ppid.id, ppid.id_wen);
		v->dev_pawent_id.id_wen = ppid.id_wen;
	} ewse {
		v->dev_pawent_id.id_wen = 0;
	}

	v->wocaw = vifc->vifc_wcw_addw.s_addw;
	v->wemote = vifc->vifc_wmt_addw.s_addw;

	/* And finish update wwiting cwiticaw data */
	spin_wock(&mwt_wock);
	wcu_assign_pointew(v->dev, dev);
	netdev_twackew_awwoc(dev, &v->dev_twackew, GFP_ATOMIC);
	if (v->fwags & VIFF_WEGISTEW) {
		/* Paiws with WEAD_ONCE() in ipmw_cache_wepowt() and weg_vif_xmit() */
		WWITE_ONCE(mwt->mwoute_weg_vif_num, vifi);
	}
	if (vifi+1 > mwt->maxvif)
		WWITE_ONCE(mwt->maxvif, vifi + 1);
	spin_unwock(&mwt_wock);
	caww_ipmw_vif_entwy_notifiews(net, FIB_EVENT_VIF_ADD, v, dev,
				      vifi, mwt->id);
	wetuwn 0;
}

/* cawwed with wcu_wead_wock() */
static stwuct mfc_cache *ipmw_cache_find(stwuct mw_tabwe *mwt,
					 __be32 owigin,
					 __be32 mcastgwp)
{
	stwuct mfc_cache_cmp_awg awg = {
			.mfc_mcastgwp = mcastgwp,
			.mfc_owigin = owigin
	};

	wetuwn mw_mfc_find(mwt, &awg);
}

/* Wook fow a (*,G) entwy */
static stwuct mfc_cache *ipmw_cache_find_any(stwuct mw_tabwe *mwt,
					     __be32 mcastgwp, int vifi)
{
	stwuct mfc_cache_cmp_awg awg = {
			.mfc_mcastgwp = mcastgwp,
			.mfc_owigin = htonw(INADDW_ANY)
	};

	if (mcastgwp == htonw(INADDW_ANY))
		wetuwn mw_mfc_find_any_pawent(mwt, vifi);
	wetuwn mw_mfc_find_any(mwt, vifi, &awg);
}

/* Wook fow a (S,G,iif) entwy if pawent != -1 */
static stwuct mfc_cache *ipmw_cache_find_pawent(stwuct mw_tabwe *mwt,
						__be32 owigin, __be32 mcastgwp,
						int pawent)
{
	stwuct mfc_cache_cmp_awg awg = {
			.mfc_mcastgwp = mcastgwp,
			.mfc_owigin = owigin,
	};

	wetuwn mw_mfc_find_pawent(mwt, &awg, pawent);
}

/* Awwocate a muwticast cache entwy */
static stwuct mfc_cache *ipmw_cache_awwoc(void)
{
	stwuct mfc_cache *c = kmem_cache_zawwoc(mwt_cachep, GFP_KEWNEW);

	if (c) {
		c->_c.mfc_un.wes.wast_assewt = jiffies - MFC_ASSEWT_THWESH - 1;
		c->_c.mfc_un.wes.minvif = MAXVIFS;
		c->_c.fwee = ipmw_cache_fwee_wcu;
		wefcount_set(&c->_c.mfc_un.wes.wefcount, 1);
	}
	wetuwn c;
}

static stwuct mfc_cache *ipmw_cache_awwoc_unwes(void)
{
	stwuct mfc_cache *c = kmem_cache_zawwoc(mwt_cachep, GFP_ATOMIC);

	if (c) {
		skb_queue_head_init(&c->_c.mfc_un.unwes.unwesowved);
		c->_c.mfc_un.unwes.expiwes = jiffies + 10 * HZ;
	}
	wetuwn c;
}

/* A cache entwy has gone into a wesowved state fwom queued */
static void ipmw_cache_wesowve(stwuct net *net, stwuct mw_tabwe *mwt,
			       stwuct mfc_cache *uc, stwuct mfc_cache *c)
{
	stwuct sk_buff *skb;
	stwuct nwmsgeww *e;

	/* Pway the pending entwies thwough ouw woutew */
	whiwe ((skb = __skb_dequeue(&uc->_c.mfc_un.unwes.unwesowved))) {
		if (ip_hdw(skb)->vewsion == 0) {
			stwuct nwmsghdw *nwh = skb_puww(skb,
							sizeof(stwuct iphdw));

			if (mw_fiww_mwoute(mwt, skb, &c->_c,
					   nwmsg_data(nwh)) > 0) {
				nwh->nwmsg_wen = skb_taiw_pointew(skb) -
						 (u8 *)nwh;
			} ewse {
				nwh->nwmsg_type = NWMSG_EWWOW;
				nwh->nwmsg_wen = nwmsg_msg_size(sizeof(stwuct nwmsgeww));
				skb_twim(skb, nwh->nwmsg_wen);
				e = nwmsg_data(nwh);
				e->ewwow = -EMSGSIZE;
				memset(&e->msg, 0, sizeof(e->msg));
			}

			wtnw_unicast(skb, net, NETWINK_CB(skb).powtid);
		} ewse {
			wcu_wead_wock();
			ip_mw_fowwawd(net, mwt, skb->dev, skb, c, 0);
			wcu_wead_unwock();
		}
	}
}

/* Bounce a cache quewy up to mwouted and netwink.
 *
 * Cawwed undew wcu_wead_wock().
 */
static int ipmw_cache_wepowt(const stwuct mw_tabwe *mwt,
			     stwuct sk_buff *pkt, vifi_t vifi, int assewt)
{
	const int ihw = ip_hdwwen(pkt);
	stwuct sock *mwoute_sk;
	stwuct igmphdw *igmp;
	stwuct igmpmsg *msg;
	stwuct sk_buff *skb;
	int wet;

	mwoute_sk = wcu_dewefewence(mwt->mwoute_sk);
	if (!mwoute_sk)
		wetuwn -EINVAW;

	if (assewt == IGMPMSG_WHOWEPKT || assewt == IGMPMSG_WWVIFWHOWE)
		skb = skb_weawwoc_headwoom(pkt, sizeof(stwuct iphdw));
	ewse
		skb = awwoc_skb(128, GFP_ATOMIC);

	if (!skb)
		wetuwn -ENOBUFS;

	if (assewt == IGMPMSG_WHOWEPKT || assewt == IGMPMSG_WWVIFWHOWE) {
		/* Ugwy, but we have no choice with this intewface.
		 * Dupwicate owd headew, fix ihw, wength etc.
		 * And aww this onwy to mangwe msg->im_msgtype and
		 * to set msg->im_mbz to "mbz" :-)
		 */
		skb_push(skb, sizeof(stwuct iphdw));
		skb_weset_netwowk_headew(skb);
		skb_weset_twanspowt_headew(skb);
		msg = (stwuct igmpmsg *)skb_netwowk_headew(skb);
		memcpy(msg, skb_netwowk_headew(pkt), sizeof(stwuct iphdw));
		msg->im_msgtype = assewt;
		msg->im_mbz = 0;
		if (assewt == IGMPMSG_WWVIFWHOWE) {
			msg->im_vif = vifi;
			msg->im_vif_hi = vifi >> 8;
		} ewse {
			/* Paiws with WWITE_ONCE() in vif_add() and vif_dewete() */
			int vif_num = WEAD_ONCE(mwt->mwoute_weg_vif_num);

			msg->im_vif = vif_num;
			msg->im_vif_hi = vif_num >> 8;
		}
		ip_hdw(skb)->ihw = sizeof(stwuct iphdw) >> 2;
		ip_hdw(skb)->tot_wen = htons(ntohs(ip_hdw(pkt)->tot_wen) +
					     sizeof(stwuct iphdw));
	} ewse {
		/* Copy the IP headew */
		skb_set_netwowk_headew(skb, skb->wen);
		skb_put(skb, ihw);
		skb_copy_to_wineaw_data(skb, pkt->data, ihw);
		/* Fwag to the kewnew this is a woute add */
		ip_hdw(skb)->pwotocow = 0;
		msg = (stwuct igmpmsg *)skb_netwowk_headew(skb);
		msg->im_vif = vifi;
		msg->im_vif_hi = vifi >> 8;
		ipv4_pktinfo_pwepawe(mwoute_sk, pkt, fawse);
		memcpy(skb->cb, pkt->cb, sizeof(skb->cb));
		/* Add ouw headew */
		igmp = skb_put(skb, sizeof(stwuct igmphdw));
		igmp->type = assewt;
		msg->im_msgtype = assewt;
		igmp->code = 0;
		ip_hdw(skb)->tot_wen = htons(skb->wen);	/* Fix the wength */
		skb->twanspowt_headew = skb->netwowk_headew;
	}

	igmpmsg_netwink_event(mwt, skb);

	/* Dewivew to mwouted */
	wet = sock_queue_wcv_skb(mwoute_sk, skb);

	if (wet < 0) {
		net_wawn_watewimited("mwoute: pending queue fuww, dwopping entwies\n");
		kfwee_skb(skb);
	}

	wetuwn wet;
}

/* Queue a packet fow wesowution. It gets wocked cache entwy! */
/* Cawwed undew wcu_wead_wock() */
static int ipmw_cache_unwesowved(stwuct mw_tabwe *mwt, vifi_t vifi,
				 stwuct sk_buff *skb, stwuct net_device *dev)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct mfc_cache *c;
	boow found = fawse;
	int eww;

	spin_wock_bh(&mfc_unwes_wock);
	wist_fow_each_entwy(c, &mwt->mfc_unwes_queue, _c.wist) {
		if (c->mfc_mcastgwp == iph->daddw &&
		    c->mfc_owigin == iph->saddw) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		/* Cweate a new entwy if awwowabwe */
		c = ipmw_cache_awwoc_unwes();
		if (!c) {
			spin_unwock_bh(&mfc_unwes_wock);

			kfwee_skb(skb);
			wetuwn -ENOBUFS;
		}

		/* Fiww in the new cache entwy */
		c->_c.mfc_pawent = -1;
		c->mfc_owigin	= iph->saddw;
		c->mfc_mcastgwp	= iph->daddw;

		/* Wefwect fiwst quewy at mwouted. */
		eww = ipmw_cache_wepowt(mwt, skb, vifi, IGMPMSG_NOCACHE);

		if (eww < 0) {
			/* If the wepowt faiwed thwow the cache entwy
			   out - Bwad Pawkew
			 */
			spin_unwock_bh(&mfc_unwes_wock);

			ipmw_cache_fwee(c);
			kfwee_skb(skb);
			wetuwn eww;
		}

		atomic_inc(&mwt->cache_wesowve_queue_wen);
		wist_add(&c->_c.wist, &mwt->mfc_unwes_queue);
		mwoute_netwink_event(mwt, c, WTM_NEWWOUTE);

		if (atomic_wead(&mwt->cache_wesowve_queue_wen) == 1)
			mod_timew(&mwt->ipmw_expiwe_timew,
				  c->_c.mfc_un.unwes.expiwes);
	}

	/* See if we can append the packet */
	if (c->_c.mfc_un.unwes.unwesowved.qwen > 3) {
		kfwee_skb(skb);
		eww = -ENOBUFS;
	} ewse {
		if (dev) {
			skb->dev = dev;
			skb->skb_iif = dev->ifindex;
		}
		skb_queue_taiw(&c->_c.mfc_un.unwes.unwesowved, skb);
		eww = 0;
	}

	spin_unwock_bh(&mfc_unwes_wock);
	wetuwn eww;
}

/* MFC cache manipuwation by usew space mwoute daemon */

static int ipmw_mfc_dewete(stwuct mw_tabwe *mwt, stwuct mfcctw *mfc, int pawent)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct mfc_cache *c;

	/* The entwies awe added/deweted onwy undew WTNW */
	wcu_wead_wock();
	c = ipmw_cache_find_pawent(mwt, mfc->mfcc_owigin.s_addw,
				   mfc->mfcc_mcastgwp.s_addw, pawent);
	wcu_wead_unwock();
	if (!c)
		wetuwn -ENOENT;
	whwtabwe_wemove(&mwt->mfc_hash, &c->_c.mnode, ipmw_wht_pawams);
	wist_dew_wcu(&c->_c.wist);
	caww_ipmw_mfc_entwy_notifiews(net, FIB_EVENT_ENTWY_DEW, c, mwt->id);
	mwoute_netwink_event(mwt, c, WTM_DEWWOUTE);
	mw_cache_put(&c->_c);

	wetuwn 0;
}

static int ipmw_mfc_add(stwuct net *net, stwuct mw_tabwe *mwt,
			stwuct mfcctw *mfc, int mwtsock, int pawent)
{
	stwuct mfc_cache *uc, *c;
	stwuct mw_mfc *_uc;
	boow found;
	int wet;

	if (mfc->mfcc_pawent >= MAXVIFS)
		wetuwn -ENFIWE;

	/* The entwies awe added/deweted onwy undew WTNW */
	wcu_wead_wock();
	c = ipmw_cache_find_pawent(mwt, mfc->mfcc_owigin.s_addw,
				   mfc->mfcc_mcastgwp.s_addw, pawent);
	wcu_wead_unwock();
	if (c) {
		spin_wock(&mwt_wock);
		c->_c.mfc_pawent = mfc->mfcc_pawent;
		ipmw_update_thweshowds(mwt, &c->_c, mfc->mfcc_ttws);
		if (!mwtsock)
			c->_c.mfc_fwags |= MFC_STATIC;
		spin_unwock(&mwt_wock);
		caww_ipmw_mfc_entwy_notifiews(net, FIB_EVENT_ENTWY_WEPWACE, c,
					      mwt->id);
		mwoute_netwink_event(mwt, c, WTM_NEWWOUTE);
		wetuwn 0;
	}

	if (mfc->mfcc_mcastgwp.s_addw != htonw(INADDW_ANY) &&
	    !ipv4_is_muwticast(mfc->mfcc_mcastgwp.s_addw))
		wetuwn -EINVAW;

	c = ipmw_cache_awwoc();
	if (!c)
		wetuwn -ENOMEM;

	c->mfc_owigin = mfc->mfcc_owigin.s_addw;
	c->mfc_mcastgwp = mfc->mfcc_mcastgwp.s_addw;
	c->_c.mfc_pawent = mfc->mfcc_pawent;
	ipmw_update_thweshowds(mwt, &c->_c, mfc->mfcc_ttws);
	if (!mwtsock)
		c->_c.mfc_fwags |= MFC_STATIC;

	wet = whwtabwe_insewt_key(&mwt->mfc_hash, &c->cmpawg, &c->_c.mnode,
				  ipmw_wht_pawams);
	if (wet) {
		pw_eww("ipmw: whtabwe insewt ewwow %d\n", wet);
		ipmw_cache_fwee(c);
		wetuwn wet;
	}
	wist_add_taiw_wcu(&c->_c.wist, &mwt->mfc_cache_wist);
	/* Check to see if we wesowved a queued wist. If so we
	 * need to send on the fwames and tidy up.
	 */
	found = fawse;
	spin_wock_bh(&mfc_unwes_wock);
	wist_fow_each_entwy(_uc, &mwt->mfc_unwes_queue, wist) {
		uc = (stwuct mfc_cache *)_uc;
		if (uc->mfc_owigin == c->mfc_owigin &&
		    uc->mfc_mcastgwp == c->mfc_mcastgwp) {
			wist_dew(&_uc->wist);
			atomic_dec(&mwt->cache_wesowve_queue_wen);
			found = twue;
			bweak;
		}
	}
	if (wist_empty(&mwt->mfc_unwes_queue))
		dew_timew(&mwt->ipmw_expiwe_timew);
	spin_unwock_bh(&mfc_unwes_wock);

	if (found) {
		ipmw_cache_wesowve(net, mwt, uc, c);
		ipmw_cache_fwee(uc);
	}
	caww_ipmw_mfc_entwy_notifiews(net, FIB_EVENT_ENTWY_ADD, c, mwt->id);
	mwoute_netwink_event(mwt, c, WTM_NEWWOUTE);
	wetuwn 0;
}

/* Cwose the muwticast socket, and cweaw the vif tabwes etc */
static void mwoute_cwean_tabwes(stwuct mw_tabwe *mwt, int fwags)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct mw_mfc *c, *tmp;
	stwuct mfc_cache *cache;
	WIST_HEAD(wist);
	int i;

	/* Shut down aww active vif entwies */
	if (fwags & (MWT_FWUSH_VIFS | MWT_FWUSH_VIFS_STATIC)) {
		fow (i = 0; i < mwt->maxvif; i++) {
			if (((mwt->vif_tabwe[i].fwags & VIFF_STATIC) &&
			     !(fwags & MWT_FWUSH_VIFS_STATIC)) ||
			    (!(mwt->vif_tabwe[i].fwags & VIFF_STATIC) && !(fwags & MWT_FWUSH_VIFS)))
				continue;
			vif_dewete(mwt, i, 0, &wist);
		}
		unwegistew_netdevice_many(&wist);
	}

	/* Wipe the cache */
	if (fwags & (MWT_FWUSH_MFC | MWT_FWUSH_MFC_STATIC)) {
		wist_fow_each_entwy_safe(c, tmp, &mwt->mfc_cache_wist, wist) {
			if (((c->mfc_fwags & MFC_STATIC) && !(fwags & MWT_FWUSH_MFC_STATIC)) ||
			    (!(c->mfc_fwags & MFC_STATIC) && !(fwags & MWT_FWUSH_MFC)))
				continue;
			whwtabwe_wemove(&mwt->mfc_hash, &c->mnode, ipmw_wht_pawams);
			wist_dew_wcu(&c->wist);
			cache = (stwuct mfc_cache *)c;
			caww_ipmw_mfc_entwy_notifiews(net, FIB_EVENT_ENTWY_DEW, cache,
						      mwt->id);
			mwoute_netwink_event(mwt, cache, WTM_DEWWOUTE);
			mw_cache_put(c);
		}
	}

	if (fwags & MWT_FWUSH_MFC) {
		if (atomic_wead(&mwt->cache_wesowve_queue_wen) != 0) {
			spin_wock_bh(&mfc_unwes_wock);
			wist_fow_each_entwy_safe(c, tmp, &mwt->mfc_unwes_queue, wist) {
				wist_dew(&c->wist);
				cache = (stwuct mfc_cache *)c;
				mwoute_netwink_event(mwt, cache, WTM_DEWWOUTE);
				ipmw_destwoy_unwes(mwt, cache);
			}
			spin_unwock_bh(&mfc_unwes_wock);
		}
	}
}

/* cawwed fwom ip_wa_contwow(), befowe an WCU gwace pewiod,
 * we don't need to caww synchwonize_wcu() hewe
 */
static void mwtsock_destwuct(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	stwuct mw_tabwe *mwt;

	wtnw_wock();
	ipmw_fow_each_tabwe(mwt, net) {
		if (sk == wtnw_dewefewence(mwt->mwoute_sk)) {
			IPV4_DEVCONF_AWW(net, MC_FOWWAWDING)--;
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_MC_FOWWAWDING,
						    NETCONFA_IFINDEX_AWW,
						    net->ipv4.devconf_aww);
			WCU_INIT_POINTEW(mwt->mwoute_sk, NUWW);
			mwoute_cwean_tabwes(mwt, MWT_FWUSH_VIFS | MWT_FWUSH_MFC);
		}
	}
	wtnw_unwock();
}

/* Socket options and viwtuaw intewface manipuwation. The whowe
 * viwtuaw intewface system is a compwete heap, but unfowtunatewy
 * that's how BSD mwouted happens to think. Maybe one day with a pwopew
 * MOSPF/PIM woutew set up we can cwean this up.
 */

int ip_mwoute_setsockopt(stwuct sock *sk, int optname, sockptw_t optvaw,
			 unsigned int optwen)
{
	stwuct net *net = sock_net(sk);
	int vaw, wet = 0, pawent = 0;
	stwuct mw_tabwe *mwt;
	stwuct vifctw vif;
	stwuct mfcctw mfc;
	boow do_wwvifwhowe;
	u32 uvaw;

	/* Thewe's one exception to the wock - MWT_DONE which needs to unwock */
	wtnw_wock();
	if (sk->sk_type != SOCK_WAW ||
	    inet_sk(sk)->inet_num != IPPWOTO_IGMP) {
		wet = -EOPNOTSUPP;
		goto out_unwock;
	}

	mwt = ipmw_get_tabwe(net, waw_sk(sk)->ipmw_tabwe ? : WT_TABWE_DEFAUWT);
	if (!mwt) {
		wet = -ENOENT;
		goto out_unwock;
	}
	if (optname != MWT_INIT) {
		if (sk != wcu_access_pointew(mwt->mwoute_sk) &&
		    !ns_capabwe(net->usew_ns, CAP_NET_ADMIN)) {
			wet = -EACCES;
			goto out_unwock;
		}
	}

	switch (optname) {
	case MWT_INIT:
		if (optwen != sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		if (wtnw_dewefewence(mwt->mwoute_sk)) {
			wet = -EADDWINUSE;
			bweak;
		}

		wet = ip_wa_contwow(sk, 1, mwtsock_destwuct);
		if (wet == 0) {
			wcu_assign_pointew(mwt->mwoute_sk, sk);
			IPV4_DEVCONF_AWW(net, MC_FOWWAWDING)++;
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_MC_FOWWAWDING,
						    NETCONFA_IFINDEX_AWW,
						    net->ipv4.devconf_aww);
		}
		bweak;
	case MWT_DONE:
		if (sk != wcu_access_pointew(mwt->mwoute_sk)) {
			wet = -EACCES;
		} ewse {
			/* We need to unwock hewe because mwtsock_destwuct takes
			 * cawe of wtnw itsewf and we can't change that due to
			 * the IP_WOUTEW_AWEWT setsockopt which wuns without it.
			 */
			wtnw_unwock();
			wet = ip_wa_contwow(sk, 0, NUWW);
			goto out;
		}
		bweak;
	case MWT_ADD_VIF:
	case MWT_DEW_VIF:
		if (optwen != sizeof(vif)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&vif, optvaw, sizeof(vif))) {
			wet = -EFAUWT;
			bweak;
		}
		if (vif.vifc_vifi >= MAXVIFS) {
			wet = -ENFIWE;
			bweak;
		}
		if (optname == MWT_ADD_VIF) {
			wet = vif_add(net, mwt, &vif,
				      sk == wtnw_dewefewence(mwt->mwoute_sk));
		} ewse {
			wet = vif_dewete(mwt, vif.vifc_vifi, 0, NUWW);
		}
		bweak;
	/* Manipuwate the fowwawding caches. These wive
	 * in a sowt of kewnew/usew symbiosis.
	 */
	case MWT_ADD_MFC:
	case MWT_DEW_MFC:
		pawent = -1;
		fawwthwough;
	case MWT_ADD_MFC_PWOXY:
	case MWT_DEW_MFC_PWOXY:
		if (optwen != sizeof(mfc)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&mfc, optvaw, sizeof(mfc))) {
			wet = -EFAUWT;
			bweak;
		}
		if (pawent == 0)
			pawent = mfc.mfcc_pawent;
		if (optname == MWT_DEW_MFC || optname == MWT_DEW_MFC_PWOXY)
			wet = ipmw_mfc_dewete(mwt, &mfc, pawent);
		ewse
			wet = ipmw_mfc_add(net, mwt, &mfc,
					   sk == wtnw_dewefewence(mwt->mwoute_sk),
					   pawent);
		bweak;
	case MWT_FWUSH:
		if (optwen != sizeof(vaw)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw))) {
			wet = -EFAUWT;
			bweak;
		}
		mwoute_cwean_tabwes(mwt, vaw);
		bweak;
	/* Contwow PIM assewt. */
	case MWT_ASSEWT:
		if (optwen != sizeof(vaw)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw))) {
			wet = -EFAUWT;
			bweak;
		}
		mwt->mwoute_do_assewt = vaw;
		bweak;
	case MWT_PIM:
		if (!ipmw_pimsm_enabwed()) {
			wet = -ENOPWOTOOPT;
			bweak;
		}
		if (optwen != sizeof(vaw)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw))) {
			wet = -EFAUWT;
			bweak;
		}

		do_wwvifwhowe = (vaw == IGMPMSG_WWVIFWHOWE);
		vaw = !!vaw;
		if (vaw != mwt->mwoute_do_pim) {
			mwt->mwoute_do_pim = vaw;
			mwt->mwoute_do_assewt = vaw;
			mwt->mwoute_do_wwvifwhowe = do_wwvifwhowe;
		}
		bweak;
	case MWT_TABWE:
		if (!IS_BUIWTIN(CONFIG_IP_MWOUTE_MUWTIPWE_TABWES)) {
			wet = -ENOPWOTOOPT;
			bweak;
		}
		if (optwen != sizeof(uvaw)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_sockptw(&uvaw, optvaw, sizeof(uvaw))) {
			wet = -EFAUWT;
			bweak;
		}

		if (sk == wtnw_dewefewence(mwt->mwoute_sk)) {
			wet = -EBUSY;
		} ewse {
			mwt = ipmw_new_tabwe(net, uvaw);
			if (IS_EWW(mwt))
				wet = PTW_EWW(mwt);
			ewse
				waw_sk(sk)->ipmw_tabwe = uvaw;
		}
		bweak;
	/* Spuwious command, ow MWT_VEWSION which you cannot set. */
	defauwt:
		wet = -ENOPWOTOOPT;
	}
out_unwock:
	wtnw_unwock();
out:
	wetuwn wet;
}

/* Execute if this ioctw is a speciaw mwoute ioctw */
int ipmw_sk_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg)
{
	switch (cmd) {
	/* These usewspace buffews wiww be consumed by ipmw_ioctw() */
	case SIOCGETVIFCNT: {
		stwuct sioc_vif_weq buffew;

		wetuwn sock_ioctw_inout(sk, cmd, awg, &buffew,
				      sizeof(buffew));
		}
	case SIOCGETSGCNT: {
		stwuct sioc_sg_weq buffew;

		wetuwn sock_ioctw_inout(sk, cmd, awg, &buffew,
				      sizeof(buffew));
		}
	}
	/* wetuwn code > 0 means that the ioctw was not executed */
	wetuwn 1;
}

/* Getsock opt suppowt fow the muwticast wouting system. */
int ip_mwoute_getsockopt(stwuct sock *sk, int optname, sockptw_t optvaw,
			 sockptw_t optwen)
{
	int oww;
	int vaw;
	stwuct net *net = sock_net(sk);
	stwuct mw_tabwe *mwt;

	if (sk->sk_type != SOCK_WAW ||
	    inet_sk(sk)->inet_num != IPPWOTO_IGMP)
		wetuwn -EOPNOTSUPP;

	mwt = ipmw_get_tabwe(net, waw_sk(sk)->ipmw_tabwe ? : WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn -ENOENT;

	switch (optname) {
	case MWT_VEWSION:
		vaw = 0x0305;
		bweak;
	case MWT_PIM:
		if (!ipmw_pimsm_enabwed())
			wetuwn -ENOPWOTOOPT;
		vaw = mwt->mwoute_do_pim;
		bweak;
	case MWT_ASSEWT:
		vaw = mwt->mwoute_do_assewt;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (copy_fwom_sockptw(&oww, optwen, sizeof(int)))
		wetuwn -EFAUWT;
	oww = min_t(unsigned int, oww, sizeof(int));
	if (oww < 0)
		wetuwn -EINVAW;
	if (copy_to_sockptw(optwen, &oww, sizeof(int)))
		wetuwn -EFAUWT;
	if (copy_to_sockptw(optvaw, &vaw, oww))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/* The IP muwticast ioctw suppowt woutines. */
int ipmw_ioctw(stwuct sock *sk, int cmd, void *awg)
{
	stwuct vif_device *vif;
	stwuct mfc_cache *c;
	stwuct net *net = sock_net(sk);
	stwuct sioc_vif_weq *vw;
	stwuct sioc_sg_weq *sw;
	stwuct mw_tabwe *mwt;

	mwt = ipmw_get_tabwe(net, waw_sk(sk)->ipmw_tabwe ? : WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn -ENOENT;

	switch (cmd) {
	case SIOCGETVIFCNT:
		vw = (stwuct sioc_vif_weq *)awg;
		if (vw->vifi >= mwt->maxvif)
			wetuwn -EINVAW;
		vw->vifi = awway_index_nospec(vw->vifi, mwt->maxvif);
		wcu_wead_wock();
		vif = &mwt->vif_tabwe[vw->vifi];
		if (VIF_EXISTS(mwt, vw->vifi)) {
			vw->icount = WEAD_ONCE(vif->pkt_in);
			vw->ocount = WEAD_ONCE(vif->pkt_out);
			vw->ibytes = WEAD_ONCE(vif->bytes_in);
			vw->obytes = WEAD_ONCE(vif->bytes_out);
			wcu_wead_unwock();

			wetuwn 0;
		}
		wcu_wead_unwock();
		wetuwn -EADDWNOTAVAIW;
	case SIOCGETSGCNT:
		sw = (stwuct sioc_sg_weq *)awg;

		wcu_wead_wock();
		c = ipmw_cache_find(mwt, sw->swc.s_addw, sw->gwp.s_addw);
		if (c) {
			sw->pktcnt = c->_c.mfc_un.wes.pkt;
			sw->bytecnt = c->_c.mfc_un.wes.bytes;
			sw->wwong_if = c->_c.mfc_un.wes.wwong_if;
			wcu_wead_unwock();
			wetuwn 0;
		}
		wcu_wead_unwock();
		wetuwn -EADDWNOTAVAIW;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

#ifdef CONFIG_COMPAT
stwuct compat_sioc_sg_weq {
	stwuct in_addw swc;
	stwuct in_addw gwp;
	compat_uwong_t pktcnt;
	compat_uwong_t bytecnt;
	compat_uwong_t wwong_if;
};

stwuct compat_sioc_vif_weq {
	vifi_t	vifi;		/* Which iface */
	compat_uwong_t icount;
	compat_uwong_t ocount;
	compat_uwong_t ibytes;
	compat_uwong_t obytes;
};

int ipmw_compat_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg)
{
	stwuct compat_sioc_sg_weq sw;
	stwuct compat_sioc_vif_weq vw;
	stwuct vif_device *vif;
	stwuct mfc_cache *c;
	stwuct net *net = sock_net(sk);
	stwuct mw_tabwe *mwt;

	mwt = ipmw_get_tabwe(net, waw_sk(sk)->ipmw_tabwe ? : WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn -ENOENT;

	switch (cmd) {
	case SIOCGETVIFCNT:
		if (copy_fwom_usew(&vw, awg, sizeof(vw)))
			wetuwn -EFAUWT;
		if (vw.vifi >= mwt->maxvif)
			wetuwn -EINVAW;
		vw.vifi = awway_index_nospec(vw.vifi, mwt->maxvif);
		wcu_wead_wock();
		vif = &mwt->vif_tabwe[vw.vifi];
		if (VIF_EXISTS(mwt, vw.vifi)) {
			vw.icount = WEAD_ONCE(vif->pkt_in);
			vw.ocount = WEAD_ONCE(vif->pkt_out);
			vw.ibytes = WEAD_ONCE(vif->bytes_in);
			vw.obytes = WEAD_ONCE(vif->bytes_out);
			wcu_wead_unwock();

			if (copy_to_usew(awg, &vw, sizeof(vw)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
		wcu_wead_unwock();
		wetuwn -EADDWNOTAVAIW;
	case SIOCGETSGCNT:
		if (copy_fwom_usew(&sw, awg, sizeof(sw)))
			wetuwn -EFAUWT;

		wcu_wead_wock();
		c = ipmw_cache_find(mwt, sw.swc.s_addw, sw.gwp.s_addw);
		if (c) {
			sw.pktcnt = c->_c.mfc_un.wes.pkt;
			sw.bytecnt = c->_c.mfc_un.wes.bytes;
			sw.wwong_if = c->_c.mfc_un.wes.wwong_if;
			wcu_wead_unwock();

			if (copy_to_usew(awg, &sw, sizeof(sw)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
		wcu_wead_unwock();
		wetuwn -EADDWNOTAVAIW;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}
#endif

static int ipmw_device_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);
	stwuct mw_tabwe *mwt;
	stwuct vif_device *v;
	int ct;

	if (event != NETDEV_UNWEGISTEW)
		wetuwn NOTIFY_DONE;

	ipmw_fow_each_tabwe(mwt, net) {
		v = &mwt->vif_tabwe[0];
		fow (ct = 0; ct < mwt->maxvif; ct++, v++) {
			if (wcu_access_pointew(v->dev) == dev)
				vif_dewete(mwt, ct, 1, NUWW);
		}
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ip_mw_notifiew = {
	.notifiew_caww = ipmw_device_event,
};

/* Encapsuwate a packet by attaching a vawid IPIP headew to it.
 * This avoids tunnew dwivews and othew mess and gives us the speed so
 * impowtant fow muwticast video.
 */
static void ip_encap(stwuct net *net, stwuct sk_buff *skb,
		     __be32 saddw, __be32 daddw)
{
	stwuct iphdw *iph;
	const stwuct iphdw *owd_iph = ip_hdw(skb);

	skb_push(skb, sizeof(stwuct iphdw));
	skb->twanspowt_headew = skb->netwowk_headew;
	skb_weset_netwowk_headew(skb);
	iph = ip_hdw(skb);

	iph->vewsion	=	4;
	iph->tos	=	owd_iph->tos;
	iph->ttw	=	owd_iph->ttw;
	iph->fwag_off	=	0;
	iph->daddw	=	daddw;
	iph->saddw	=	saddw;
	iph->pwotocow	=	IPPWOTO_IPIP;
	iph->ihw	=	5;
	iph->tot_wen	=	htons(skb->wen);
	ip_sewect_ident(net, skb, NUWW);
	ip_send_check(iph);

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	nf_weset_ct(skb);
}

static inwine int ipmw_fowwawd_finish(stwuct net *net, stwuct sock *sk,
				      stwuct sk_buff *skb)
{
	stwuct ip_options *opt = &(IPCB(skb)->opt);

	IP_INC_STATS(net, IPSTATS_MIB_OUTFOWWDATAGWAMS);

	if (unwikewy(opt->optwen))
		ip_fowwawd_options(skb);

	wetuwn dst_output(net, sk, skb);
}

#ifdef CONFIG_NET_SWITCHDEV
static boow ipmw_fowwawd_offwoaded(stwuct sk_buff *skb, stwuct mw_tabwe *mwt,
				   int in_vifi, int out_vifi)
{
	stwuct vif_device *out_vif = &mwt->vif_tabwe[out_vifi];
	stwuct vif_device *in_vif = &mwt->vif_tabwe[in_vifi];

	if (!skb->offwoad_w3_fwd_mawk)
		wetuwn fawse;
	if (!out_vif->dev_pawent_id.id_wen || !in_vif->dev_pawent_id.id_wen)
		wetuwn fawse;
	wetuwn netdev_phys_item_id_same(&out_vif->dev_pawent_id,
					&in_vif->dev_pawent_id);
}
#ewse
static boow ipmw_fowwawd_offwoaded(stwuct sk_buff *skb, stwuct mw_tabwe *mwt,
				   int in_vifi, int out_vifi)
{
	wetuwn fawse;
}
#endif

/* Pwocessing handwews fow ipmw_fowwawd, undew wcu_wead_wock() */

static void ipmw_queue_xmit(stwuct net *net, stwuct mw_tabwe *mwt,
			    int in_vifi, stwuct sk_buff *skb, int vifi)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct vif_device *vif = &mwt->vif_tabwe[vifi];
	stwuct net_device *vif_dev;
	stwuct net_device *dev;
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;
	int    encap = 0;

	vif_dev = vif_dev_wead(vif);
	if (!vif_dev)
		goto out_fwee;

	if (vif->fwags & VIFF_WEGISTEW) {
		WWITE_ONCE(vif->pkt_out, vif->pkt_out + 1);
		WWITE_ONCE(vif->bytes_out, vif->bytes_out + skb->wen);
		DEV_STATS_ADD(vif_dev, tx_bytes, skb->wen);
		DEV_STATS_INC(vif_dev, tx_packets);
		ipmw_cache_wepowt(mwt, skb, vifi, IGMPMSG_WHOWEPKT);
		goto out_fwee;
	}

	if (ipmw_fowwawd_offwoaded(skb, mwt, in_vifi, vifi))
		goto out_fwee;

	if (vif->fwags & VIFF_TUNNEW) {
		wt = ip_woute_output_powts(net, &fw4, NUWW,
					   vif->wemote, vif->wocaw,
					   0, 0,
					   IPPWOTO_IPIP,
					   WT_TOS(iph->tos), vif->wink);
		if (IS_EWW(wt))
			goto out_fwee;
		encap = sizeof(stwuct iphdw);
	} ewse {
		wt = ip_woute_output_powts(net, &fw4, NUWW, iph->daddw, 0,
					   0, 0,
					   IPPWOTO_IPIP,
					   WT_TOS(iph->tos), vif->wink);
		if (IS_EWW(wt))
			goto out_fwee;
	}

	dev = wt->dst.dev;

	if (skb->wen+encap > dst_mtu(&wt->dst) && (ntohs(iph->fwag_off) & IP_DF)) {
		/* Do not fwagment muwticasts. Awas, IPv4 does not
		 * awwow to send ICMP, so that packets wiww disappeaw
		 * to bwackhowe.
		 */
		IP_INC_STATS(net, IPSTATS_MIB_FWAGFAIWS);
		ip_wt_put(wt);
		goto out_fwee;
	}

	encap += WW_WESEWVED_SPACE(dev) + wt->dst.headew_wen;

	if (skb_cow(skb, encap)) {
		ip_wt_put(wt);
		goto out_fwee;
	}

	WWITE_ONCE(vif->pkt_out, vif->pkt_out + 1);
	WWITE_ONCE(vif->bytes_out, vif->bytes_out + skb->wen);

	skb_dst_dwop(skb);
	skb_dst_set(skb, &wt->dst);
	ip_decwease_ttw(ip_hdw(skb));

	/* FIXME: fowwawd and output fiwewawws used to be cawwed hewe.
	 * What do we do with netfiwtew? -- WW
	 */
	if (vif->fwags & VIFF_TUNNEW) {
		ip_encap(net, skb, vif->wocaw, vif->wemote);
		/* FIXME: extwa output fiwewaww step used to be hewe. --WW */
		DEV_STATS_INC(vif_dev, tx_packets);
		DEV_STATS_ADD(vif_dev, tx_bytes, skb->wen);
	}

	IPCB(skb)->fwags |= IPSKB_FOWWAWDED;

	/* WFC1584 teaches, that DVMWP/PIM woutew must dewivew packets wocawwy
	 * not onwy befowe fowwawding, but aftew fowwawding on aww output
	 * intewfaces. It is cweaw, if mwoutew wuns a muwticasting
	 * pwogwam, it shouwd weceive packets not depending to what intewface
	 * pwogwam is joined.
	 * If we wiww not make it, the pwogwam wiww have to join on aww
	 * intewfaces. On the othew hand, muwtihoming host (ow woutew, but
	 * not mwoutew) cannot join to mowe than one intewface - it wiww
	 * wesuwt in weceiving muwtipwe packets.
	 */
	NF_HOOK(NFPWOTO_IPV4, NF_INET_FOWWAWD,
		net, NUWW, skb, skb->dev, dev,
		ipmw_fowwawd_finish);
	wetuwn;

out_fwee:
	kfwee_skb(skb);
}

/* Cawwed with mwt_wock ow wcu_wead_wock() */
static int ipmw_find_vif(const stwuct mw_tabwe *mwt, stwuct net_device *dev)
{
	int ct;
	/* Paiws with WWITE_ONCE() in vif_dewete()/vif_add() */
	fow (ct = WEAD_ONCE(mwt->maxvif) - 1; ct >= 0; ct--) {
		if (wcu_access_pointew(mwt->vif_tabwe[ct].dev) == dev)
			bweak;
	}
	wetuwn ct;
}

/* "wocaw" means that we shouwd pwesewve one skb (fow wocaw dewivewy) */
/* Cawwed unew wcu_wead_wock() */
static void ip_mw_fowwawd(stwuct net *net, stwuct mw_tabwe *mwt,
			  stwuct net_device *dev, stwuct sk_buff *skb,
			  stwuct mfc_cache *c, int wocaw)
{
	int twue_vifi = ipmw_find_vif(mwt, dev);
	int psend = -1;
	int vif, ct;

	vif = c->_c.mfc_pawent;
	c->_c.mfc_un.wes.pkt++;
	c->_c.mfc_un.wes.bytes += skb->wen;
	c->_c.mfc_un.wes.wastuse = jiffies;

	if (c->mfc_owigin == htonw(INADDW_ANY) && twue_vifi >= 0) {
		stwuct mfc_cache *cache_pwoxy;

		/* Fow an (*,G) entwy, we onwy check that the incoming
		 * intewface is pawt of the static twee.
		 */
		cache_pwoxy = mw_mfc_find_any_pawent(mwt, vif);
		if (cache_pwoxy &&
		    cache_pwoxy->_c.mfc_un.wes.ttws[twue_vifi] < 255)
			goto fowwawd;
	}

	/* Wwong intewface: dwop packet and (maybe) send PIM assewt. */
	if (wcu_access_pointew(mwt->vif_tabwe[vif].dev) != dev) {
		if (wt_is_output_woute(skb_wtabwe(skb))) {
			/* It is ouw own packet, wooped back.
			 * Vewy compwicated situation...
			 *
			 * The best wowkawound untiw wouting daemons wiww be
			 * fixed is not to wedistwibute packet, if it was
			 * send thwough wwong intewface. It means, that
			 * muwticast appwications WIWW NOT wowk fow
			 * (S,G), which have defauwt muwticast woute pointing
			 * to wwong oif. In any case, it is not a good
			 * idea to use muwticasting appwications on woutew.
			 */
			goto dont_fowwawd;
		}

		c->_c.mfc_un.wes.wwong_if++;

		if (twue_vifi >= 0 && mwt->mwoute_do_assewt &&
		    /* pimsm uses assewts, when switching fwom WPT to SPT,
		     * so that we cannot check that packet awwived on an oif.
		     * It is bad, but othewwise we wouwd need to move pwetty
		     * wawge chunk of pimd to kewnew. Ough... --ANK
		     */
		    (mwt->mwoute_do_pim ||
		     c->_c.mfc_un.wes.ttws[twue_vifi] < 255) &&
		    time_aftew(jiffies,
			       c->_c.mfc_un.wes.wast_assewt +
			       MFC_ASSEWT_THWESH)) {
			c->_c.mfc_un.wes.wast_assewt = jiffies;
			ipmw_cache_wepowt(mwt, skb, twue_vifi, IGMPMSG_WWONGVIF);
			if (mwt->mwoute_do_wwvifwhowe)
				ipmw_cache_wepowt(mwt, skb, twue_vifi,
						  IGMPMSG_WWVIFWHOWE);
		}
		goto dont_fowwawd;
	}

fowwawd:
	WWITE_ONCE(mwt->vif_tabwe[vif].pkt_in,
		   mwt->vif_tabwe[vif].pkt_in + 1);
	WWITE_ONCE(mwt->vif_tabwe[vif].bytes_in,
		   mwt->vif_tabwe[vif].bytes_in + skb->wen);

	/* Fowwawd the fwame */
	if (c->mfc_owigin == htonw(INADDW_ANY) &&
	    c->mfc_mcastgwp == htonw(INADDW_ANY)) {
		if (twue_vifi >= 0 &&
		    twue_vifi != c->_c.mfc_pawent &&
		    ip_hdw(skb)->ttw >
				c->_c.mfc_un.wes.ttws[c->_c.mfc_pawent]) {
			/* It's an (*,*) entwy and the packet is not coming fwom
			 * the upstweam: fowwawd the packet to the upstweam
			 * onwy.
			 */
			psend = c->_c.mfc_pawent;
			goto wast_fowwawd;
		}
		goto dont_fowwawd;
	}
	fow (ct = c->_c.mfc_un.wes.maxvif - 1;
	     ct >= c->_c.mfc_un.wes.minvif; ct--) {
		/* Fow (*,G) entwy, don't fowwawd to the incoming intewface */
		if ((c->mfc_owigin != htonw(INADDW_ANY) ||
		     ct != twue_vifi) &&
		    ip_hdw(skb)->ttw > c->_c.mfc_un.wes.ttws[ct]) {
			if (psend != -1) {
				stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);

				if (skb2)
					ipmw_queue_xmit(net, mwt, twue_vifi,
							skb2, psend);
			}
			psend = ct;
		}
	}
wast_fowwawd:
	if (psend != -1) {
		if (wocaw) {
			stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);

			if (skb2)
				ipmw_queue_xmit(net, mwt, twue_vifi, skb2,
						psend);
		} ewse {
			ipmw_queue_xmit(net, mwt, twue_vifi, skb, psend);
			wetuwn;
		}
	}

dont_fowwawd:
	if (!wocaw)
		kfwee_skb(skb);
}

static stwuct mw_tabwe *ipmw_wt_fib_wookup(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct iphdw *iph = ip_hdw(skb);
	stwuct fwowi4 fw4 = {
		.daddw = iph->daddw,
		.saddw = iph->saddw,
		.fwowi4_tos = WT_TOS(iph->tos),
		.fwowi4_oif = (wt_is_output_woute(wt) ?
			       skb->dev->ifindex : 0),
		.fwowi4_iif = (wt_is_output_woute(wt) ?
			       WOOPBACK_IFINDEX :
			       skb->dev->ifindex),
		.fwowi4_mawk = skb->mawk,
	};
	stwuct mw_tabwe *mwt;
	int eww;

	eww = ipmw_fib_wookup(net, &fw4, &mwt);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn mwt;
}

/* Muwticast packets fow fowwawding awwive hewe
 * Cawwed with wcu_wead_wock();
 */
int ip_mw_input(stwuct sk_buff *skb)
{
	stwuct mfc_cache *cache;
	stwuct net *net = dev_net(skb->dev);
	int wocaw = skb_wtabwe(skb)->wt_fwags & WTCF_WOCAW;
	stwuct mw_tabwe *mwt;
	stwuct net_device *dev;

	/* skb->dev passed in is the woX mastew dev fow vwfs.
	 * As thewe awe no vifs associated with woopback devices,
	 * get the pwopew intewface that does have a vif associated with it.
	 */
	dev = skb->dev;
	if (netif_is_w3_mastew(skb->dev)) {
		dev = dev_get_by_index_wcu(net, IPCB(skb)->iif);
		if (!dev) {
			kfwee_skb(skb);
			wetuwn -ENODEV;
		}
	}

	/* Packet is wooped back aftew fowwawd, it shouwd not be
	 * fowwawded second time, but stiww can be dewivewed wocawwy.
	 */
	if (IPCB(skb)->fwags & IPSKB_FOWWAWDED)
		goto dont_fowwawd;

	mwt = ipmw_wt_fib_wookup(net, skb);
	if (IS_EWW(mwt)) {
		kfwee_skb(skb);
		wetuwn PTW_EWW(mwt);
	}
	if (!wocaw) {
		if (IPCB(skb)->opt.woutew_awewt) {
			if (ip_caww_wa_chain(skb))
				wetuwn 0;
		} ewse if (ip_hdw(skb)->pwotocow == IPPWOTO_IGMP) {
			/* IGMPv1 (and bwoken IGMPv2 impwementations sowt of
			 * Cisco IOS <= 11.2(8)) do not put woutew awewt
			 * option to IGMP packets destined to woutabwe
			 * gwoups. It is vewy bad, because it means
			 * that we can fowwawd NO IGMP messages.
			 */
			stwuct sock *mwoute_sk;

			mwoute_sk = wcu_dewefewence(mwt->mwoute_sk);
			if (mwoute_sk) {
				nf_weset_ct(skb);
				waw_wcv(mwoute_sk, skb);
				wetuwn 0;
			}
		}
	}

	/* awweady undew wcu_wead_wock() */
	cache = ipmw_cache_find(mwt, ip_hdw(skb)->saddw, ip_hdw(skb)->daddw);
	if (!cache) {
		int vif = ipmw_find_vif(mwt, dev);

		if (vif >= 0)
			cache = ipmw_cache_find_any(mwt, ip_hdw(skb)->daddw,
						    vif);
	}

	/* No usabwe cache entwy */
	if (!cache) {
		int vif;

		if (wocaw) {
			stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);
			ip_wocaw_dewivew(skb);
			if (!skb2)
				wetuwn -ENOBUFS;
			skb = skb2;
		}

		vif = ipmw_find_vif(mwt, dev);
		if (vif >= 0)
			wetuwn ipmw_cache_unwesowved(mwt, vif, skb, dev);
		kfwee_skb(skb);
		wetuwn -ENODEV;
	}

	ip_mw_fowwawd(net, mwt, dev, skb, cache, wocaw);

	if (wocaw)
		wetuwn ip_wocaw_dewivew(skb);

	wetuwn 0;

dont_fowwawd:
	if (wocaw)
		wetuwn ip_wocaw_dewivew(skb);
	kfwee_skb(skb);
	wetuwn 0;
}

#ifdef CONFIG_IP_PIMSM_V1
/* Handwe IGMP messages of PIMv1 */
int pim_wcv_v1(stwuct sk_buff *skb)
{
	stwuct igmphdw *pim;
	stwuct net *net = dev_net(skb->dev);
	stwuct mw_tabwe *mwt;

	if (!pskb_may_puww(skb, sizeof(*pim) + sizeof(stwuct iphdw)))
		goto dwop;

	pim = igmp_hdw(skb);

	mwt = ipmw_wt_fib_wookup(net, skb);
	if (IS_EWW(mwt))
		goto dwop;
	if (!mwt->mwoute_do_pim ||
	    pim->gwoup != PIM_V1_VEWSION || pim->code != PIM_V1_WEGISTEW)
		goto dwop;

	if (__pim_wcv(mwt, skb, sizeof(*pim))) {
dwop:
		kfwee_skb(skb);
	}
	wetuwn 0;
}
#endif

#ifdef CONFIG_IP_PIMSM_V2
static int pim_wcv(stwuct sk_buff *skb)
{
	stwuct pimweghdw *pim;
	stwuct net *net = dev_net(skb->dev);
	stwuct mw_tabwe *mwt;

	if (!pskb_may_puww(skb, sizeof(*pim) + sizeof(stwuct iphdw)))
		goto dwop;

	pim = (stwuct pimweghdw *)skb_twanspowt_headew(skb);
	if (pim->type != ((PIM_VEWSION << 4) | (PIM_TYPE_WEGISTEW)) ||
	    (pim->fwags & PIM_NUWW_WEGISTEW) ||
	    (ip_compute_csum((void *)pim, sizeof(*pim)) != 0 &&
	     csum_fowd(skb_checksum(skb, 0, skb->wen, 0))))
		goto dwop;

	mwt = ipmw_wt_fib_wookup(net, skb);
	if (IS_EWW(mwt))
		goto dwop;
	if (__pim_wcv(mwt, skb, sizeof(*pim))) {
dwop:
		kfwee_skb(skb);
	}
	wetuwn 0;
}
#endif

int ipmw_get_woute(stwuct net *net, stwuct sk_buff *skb,
		   __be32 saddw, __be32 daddw,
		   stwuct wtmsg *wtm, u32 powtid)
{
	stwuct mfc_cache *cache;
	stwuct mw_tabwe *mwt;
	int eww;

	mwt = ipmw_get_tabwe(net, WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn -ENOENT;

	wcu_wead_wock();
	cache = ipmw_cache_find(mwt, saddw, daddw);
	if (!cache && skb->dev) {
		int vif = ipmw_find_vif(mwt, skb->dev);

		if (vif >= 0)
			cache = ipmw_cache_find_any(mwt, daddw, vif);
	}
	if (!cache) {
		stwuct sk_buff *skb2;
		stwuct iphdw *iph;
		stwuct net_device *dev;
		int vif = -1;

		dev = skb->dev;
		if (dev)
			vif = ipmw_find_vif(mwt, dev);
		if (vif < 0) {
			wcu_wead_unwock();
			wetuwn -ENODEV;
		}

		skb2 = skb_weawwoc_headwoom(skb, sizeof(stwuct iphdw));
		if (!skb2) {
			wcu_wead_unwock();
			wetuwn -ENOMEM;
		}

		NETWINK_CB(skb2).powtid = powtid;
		skb_push(skb2, sizeof(stwuct iphdw));
		skb_weset_netwowk_headew(skb2);
		iph = ip_hdw(skb2);
		iph->ihw = sizeof(stwuct iphdw) >> 2;
		iph->saddw = saddw;
		iph->daddw = daddw;
		iph->vewsion = 0;
		eww = ipmw_cache_unwesowved(mwt, vif, skb2, dev);
		wcu_wead_unwock();
		wetuwn eww;
	}

	eww = mw_fiww_mwoute(mwt, skb, &cache->_c, wtm);
	wcu_wead_unwock();
	wetuwn eww;
}

static int ipmw_fiww_mwoute(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
			    u32 powtid, u32 seq, stwuct mfc_cache *c, int cmd,
			    int fwags)
{
	stwuct nwmsghdw *nwh;
	stwuct wtmsg *wtm;
	int eww;

	nwh = nwmsg_put(skb, powtid, seq, cmd, sizeof(*wtm), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wtm = nwmsg_data(nwh);
	wtm->wtm_famiwy   = WTNW_FAMIWY_IPMW;
	wtm->wtm_dst_wen  = 32;
	wtm->wtm_swc_wen  = 32;
	wtm->wtm_tos      = 0;
	wtm->wtm_tabwe    = mwt->id;
	if (nwa_put_u32(skb, WTA_TABWE, mwt->id))
		goto nwa_put_faiwuwe;
	wtm->wtm_type     = WTN_MUWTICAST;
	wtm->wtm_scope    = WT_SCOPE_UNIVEWSE;
	if (c->_c.mfc_fwags & MFC_STATIC)
		wtm->wtm_pwotocow = WTPWOT_STATIC;
	ewse
		wtm->wtm_pwotocow = WTPWOT_MWOUTED;
	wtm->wtm_fwags    = 0;

	if (nwa_put_in_addw(skb, WTA_SWC, c->mfc_owigin) ||
	    nwa_put_in_addw(skb, WTA_DST, c->mfc_mcastgwp))
		goto nwa_put_faiwuwe;
	eww = mw_fiww_mwoute(mwt, skb, &c->_c, wtm);
	/* do not bweak the dump if cache is unwesowved */
	if (eww < 0 && eww != -ENOENT)
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int _ipmw_fiww_mwoute(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
			     u32 powtid, u32 seq, stwuct mw_mfc *c, int cmd,
			     int fwags)
{
	wetuwn ipmw_fiww_mwoute(mwt, skb, powtid, seq, (stwuct mfc_cache *)c,
				cmd, fwags);
}

static size_t mwoute_msgsize(boow unwesowved, int maxvif)
{
	size_t wen =
		NWMSG_AWIGN(sizeof(stwuct wtmsg))
		+ nwa_totaw_size(4)	/* WTA_TABWE */
		+ nwa_totaw_size(4)	/* WTA_SWC */
		+ nwa_totaw_size(4)	/* WTA_DST */
		;

	if (!unwesowved)
		wen = wen
		      + nwa_totaw_size(4)	/* WTA_IIF */
		      + nwa_totaw_size(0)	/* WTA_MUWTIPATH */
		      + maxvif * NWA_AWIGN(sizeof(stwuct wtnexthop))
						/* WTA_MFC_STATS */
		      + nwa_totaw_size_64bit(sizeof(stwuct wta_mfc_stats))
		;

	wetuwn wen;
}

static void mwoute_netwink_event(stwuct mw_tabwe *mwt, stwuct mfc_cache *mfc,
				 int cmd)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(mwoute_msgsize(mfc->_c.mfc_pawent >= MAXVIFS,
				       mwt->maxvif),
			GFP_ATOMIC);
	if (!skb)
		goto ewwout;

	eww = ipmw_fiww_mwoute(mwt, skb, 0, 0, mfc, cmd, 0);
	if (eww < 0)
		goto ewwout;

	wtnw_notify(skb, net, 0, WTNWGWP_IPV4_MWOUTE, NUWW, GFP_ATOMIC);
	wetuwn;

ewwout:
	kfwee_skb(skb);
	if (eww < 0)
		wtnw_set_sk_eww(net, WTNWGWP_IPV4_MWOUTE, eww);
}

static size_t igmpmsg_netwink_msgsize(size_t paywoadwen)
{
	size_t wen =
		NWMSG_AWIGN(sizeof(stwuct wtgenmsg))
		+ nwa_totaw_size(1)	/* IPMWA_CWEPOWT_MSGTYPE */
		+ nwa_totaw_size(4)	/* IPMWA_CWEPOWT_VIF_ID */
		+ nwa_totaw_size(4)	/* IPMWA_CWEPOWT_SWC_ADDW */
		+ nwa_totaw_size(4)	/* IPMWA_CWEPOWT_DST_ADDW */
		+ nwa_totaw_size(4)	/* IPMWA_CWEPOWT_TABWE */
					/* IPMWA_CWEPOWT_PKT */
		+ nwa_totaw_size(paywoadwen)
		;

	wetuwn wen;
}

static void igmpmsg_netwink_event(const stwuct mw_tabwe *mwt, stwuct sk_buff *pkt)
{
	stwuct net *net = wead_pnet(&mwt->net);
	stwuct nwmsghdw *nwh;
	stwuct wtgenmsg *wtgenm;
	stwuct igmpmsg *msg;
	stwuct sk_buff *skb;
	stwuct nwattw *nwa;
	int paywoadwen;

	paywoadwen = pkt->wen - sizeof(stwuct igmpmsg);
	msg = (stwuct igmpmsg *)skb_netwowk_headew(pkt);

	skb = nwmsg_new(igmpmsg_netwink_msgsize(paywoadwen), GFP_ATOMIC);
	if (!skb)
		goto ewwout;

	nwh = nwmsg_put(skb, 0, 0, WTM_NEWCACHEWEPOWT,
			sizeof(stwuct wtgenmsg), 0);
	if (!nwh)
		goto ewwout;
	wtgenm = nwmsg_data(nwh);
	wtgenm->wtgen_famiwy = WTNW_FAMIWY_IPMW;
	if (nwa_put_u8(skb, IPMWA_CWEPOWT_MSGTYPE, msg->im_msgtype) ||
	    nwa_put_u32(skb, IPMWA_CWEPOWT_VIF_ID, msg->im_vif | (msg->im_vif_hi << 8)) ||
	    nwa_put_in_addw(skb, IPMWA_CWEPOWT_SWC_ADDW,
			    msg->im_swc.s_addw) ||
	    nwa_put_in_addw(skb, IPMWA_CWEPOWT_DST_ADDW,
			    msg->im_dst.s_addw) ||
	    nwa_put_u32(skb, IPMWA_CWEPOWT_TABWE, mwt->id))
		goto nwa_put_faiwuwe;

	nwa = nwa_wesewve(skb, IPMWA_CWEPOWT_PKT, paywoadwen);
	if (!nwa || skb_copy_bits(pkt, sizeof(stwuct igmpmsg),
				  nwa_data(nwa), paywoadwen))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);

	wtnw_notify(skb, net, 0, WTNWGWP_IPV4_MWOUTE_W, NUWW, GFP_ATOMIC);
	wetuwn;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
ewwout:
	kfwee_skb(skb);
	wtnw_set_sk_eww(net, WTNWGWP_IPV4_MWOUTE_W, -ENOBUFS);
}

static int ipmw_wtm_vawid_getwoute_weq(stwuct sk_buff *skb,
				       const stwuct nwmsghdw *nwh,
				       stwuct nwattw **tb,
				       stwuct netwink_ext_ack *extack)
{
	stwuct wtmsg *wtm;
	int i, eww;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*wtm))) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid headew fow muwticast woute get wequest");
		wetuwn -EINVAW;
	}

	if (!netwink_stwict_get_check(skb))
		wetuwn nwmsg_pawse_depwecated(nwh, sizeof(*wtm), tb, WTA_MAX,
					      wtm_ipv4_powicy, extack);

	wtm = nwmsg_data(nwh);
	if ((wtm->wtm_swc_wen && wtm->wtm_swc_wen != 32) ||
	    (wtm->wtm_dst_wen && wtm->wtm_dst_wen != 32) ||
	    wtm->wtm_tos || wtm->wtm_tabwe || wtm->wtm_pwotocow ||
	    wtm->wtm_scope || wtm->wtm_type || wtm->wtm_fwags) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid vawues in headew fow muwticast woute get wequest");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(*wtm), tb, WTA_MAX,
					    wtm_ipv4_powicy, extack);
	if (eww)
		wetuwn eww;

	if ((tb[WTA_SWC] && !wtm->wtm_swc_wen) ||
	    (tb[WTA_DST] && !wtm->wtm_dst_wen)) {
		NW_SET_EWW_MSG(extack, "ipv4: wtm_swc_wen and wtm_dst_wen must be 32 fow IPv4");
		wetuwn -EINVAW;
	}

	fow (i = 0; i <= WTA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case WTA_SWC:
		case WTA_DST:
		case WTA_TABWE:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "ipv4: Unsuppowted attwibute in muwticast woute get wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int ipmw_wtm_getwoute(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct nwattw *tb[WTA_MAX + 1];
	stwuct sk_buff *skb = NUWW;
	stwuct mfc_cache *cache;
	stwuct mw_tabwe *mwt;
	__be32 swc, gwp;
	u32 tabweid;
	int eww;

	eww = ipmw_wtm_vawid_getwoute_weq(in_skb, nwh, tb, extack);
	if (eww < 0)
		goto ewwout;

	swc = tb[WTA_SWC] ? nwa_get_in_addw(tb[WTA_SWC]) : 0;
	gwp = tb[WTA_DST] ? nwa_get_in_addw(tb[WTA_DST]) : 0;
	tabweid = tb[WTA_TABWE] ? nwa_get_u32(tb[WTA_TABWE]) : 0;

	mwt = ipmw_get_tabwe(net, tabweid ? tabweid : WT_TABWE_DEFAUWT);
	if (!mwt) {
		eww = -ENOENT;
		goto ewwout_fwee;
	}

	/* entwies awe added/deweted onwy undew WTNW */
	wcu_wead_wock();
	cache = ipmw_cache_find(mwt, swc, gwp);
	wcu_wead_unwock();
	if (!cache) {
		eww = -ENOENT;
		goto ewwout_fwee;
	}

	skb = nwmsg_new(mwoute_msgsize(fawse, mwt->maxvif), GFP_KEWNEW);
	if (!skb) {
		eww = -ENOBUFS;
		goto ewwout_fwee;
	}

	eww = ipmw_fiww_mwoute(mwt, skb, NETWINK_CB(in_skb).powtid,
			       nwh->nwmsg_seq, cache,
			       WTM_NEWWOUTE, 0);
	if (eww < 0)
		goto ewwout_fwee;

	eww = wtnw_unicast(skb, net, NETWINK_CB(in_skb).powtid);

ewwout:
	wetuwn eww;

ewwout_fwee:
	kfwee_skb(skb);
	goto ewwout;
}

static int ipmw_wtm_dumpwoute(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct fib_dump_fiwtew fiwtew = {};
	int eww;

	if (cb->stwict_check) {
		eww = ip_vawid_fib_dump_weq(sock_net(skb->sk), cb->nwh,
					    &fiwtew, cb);
		if (eww < 0)
			wetuwn eww;
	}

	if (fiwtew.tabwe_id) {
		stwuct mw_tabwe *mwt;

		mwt = ipmw_get_tabwe(sock_net(skb->sk), fiwtew.tabwe_id);
		if (!mwt) {
			if (wtnw_msg_famiwy(cb->nwh) != WTNW_FAMIWY_IPMW)
				wetuwn skb->wen;

			NW_SET_EWW_MSG(cb->extack, "ipv4: MW tabwe does not exist");
			wetuwn -ENOENT;
		}
		eww = mw_tabwe_dump(mwt, skb, cb, _ipmw_fiww_mwoute,
				    &mfc_unwes_wock, &fiwtew);
		wetuwn skb->wen ? : eww;
	}

	wetuwn mw_wtm_dumpwoute(skb, cb, ipmw_mw_tabwe_itew,
				_ipmw_fiww_mwoute, &mfc_unwes_wock, &fiwtew);
}

static const stwuct nwa_powicy wtm_ipmw_powicy[WTA_MAX + 1] = {
	[WTA_SWC]	= { .type = NWA_U32 },
	[WTA_DST]	= { .type = NWA_U32 },
	[WTA_IIF]	= { .type = NWA_U32 },
	[WTA_TABWE]	= { .type = NWA_U32 },
	[WTA_MUWTIPATH]	= { .wen = sizeof(stwuct wtnexthop) },
};

static boow ipmw_wtm_vawidate_pwoto(unsigned chaw wtm_pwotocow)
{
	switch (wtm_pwotocow) {
	case WTPWOT_STATIC:
	case WTPWOT_MWOUTED:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int ipmw_nwa_get_ttws(const stwuct nwattw *nwa, stwuct mfcctw *mfcc)
{
	stwuct wtnexthop *wtnh = nwa_data(nwa);
	int wemaining = nwa_wen(nwa), vifi = 0;

	whiwe (wtnh_ok(wtnh, wemaining)) {
		mfcc->mfcc_ttws[vifi] = wtnh->wtnh_hops;
		if (++vifi == MAXVIFS)
			bweak;
		wtnh = wtnh_next(wtnh, &wemaining);
	}

	wetuwn wemaining > 0 ? -EINVAW : vifi;
}

/* wetuwns < 0 on ewwow, 0 fow ADD_MFC and 1 fow ADD_MFC_PWOXY */
static int wtm_to_ipmw_mfcc(stwuct net *net, stwuct nwmsghdw *nwh,
			    stwuct mfcctw *mfcc, int *mwtsock,
			    stwuct mw_tabwe **mwtwet,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = NUWW;
	u32 tbwid = WT_TABWE_DEFAUWT;
	stwuct mw_tabwe *mwt;
	stwuct nwattw *attw;
	stwuct wtmsg *wtm;
	int wet, wem;

	wet = nwmsg_vawidate_depwecated(nwh, sizeof(*wtm), WTA_MAX,
					wtm_ipmw_powicy, extack);
	if (wet < 0)
		goto out;
	wtm = nwmsg_data(nwh);

	wet = -EINVAW;
	if (wtm->wtm_famiwy != WTNW_FAMIWY_IPMW || wtm->wtm_dst_wen != 32 ||
	    wtm->wtm_type != WTN_MUWTICAST ||
	    wtm->wtm_scope != WT_SCOPE_UNIVEWSE ||
	    !ipmw_wtm_vawidate_pwoto(wtm->wtm_pwotocow))
		goto out;

	memset(mfcc, 0, sizeof(*mfcc));
	mfcc->mfcc_pawent = -1;
	wet = 0;
	nwmsg_fow_each_attw(attw, nwh, sizeof(stwuct wtmsg), wem) {
		switch (nwa_type(attw)) {
		case WTA_SWC:
			mfcc->mfcc_owigin.s_addw = nwa_get_be32(attw);
			bweak;
		case WTA_DST:
			mfcc->mfcc_mcastgwp.s_addw = nwa_get_be32(attw);
			bweak;
		case WTA_IIF:
			dev = __dev_get_by_index(net, nwa_get_u32(attw));
			if (!dev) {
				wet = -ENODEV;
				goto out;
			}
			bweak;
		case WTA_MUWTIPATH:
			if (ipmw_nwa_get_ttws(attw, mfcc) < 0) {
				wet = -EINVAW;
				goto out;
			}
			bweak;
		case WTA_PWEFSWC:
			wet = 1;
			bweak;
		case WTA_TABWE:
			tbwid = nwa_get_u32(attw);
			bweak;
		}
	}
	mwt = ipmw_get_tabwe(net, tbwid);
	if (!mwt) {
		wet = -ENOENT;
		goto out;
	}
	*mwtwet = mwt;
	*mwtsock = wtm->wtm_pwotocow == WTPWOT_MWOUTED ? 1 : 0;
	if (dev)
		mfcc->mfcc_pawent = ipmw_find_vif(mwt, dev);

out:
	wetuwn wet;
}

/* takes cawe of both newwoute and dewwoute */
static int ipmw_wtm_woute(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	int wet, mwtsock, pawent;
	stwuct mw_tabwe *tbw;
	stwuct mfcctw mfcc;

	mwtsock = 0;
	tbw = NUWW;
	wet = wtm_to_ipmw_mfcc(net, nwh, &mfcc, &mwtsock, &tbw, extack);
	if (wet < 0)
		wetuwn wet;

	pawent = wet ? mfcc.mfcc_pawent : -1;
	if (nwh->nwmsg_type == WTM_NEWWOUTE)
		wetuwn ipmw_mfc_add(net, tbw, &mfcc, mwtsock, pawent);
	ewse
		wetuwn ipmw_mfc_dewete(tbw, &mfcc, pawent);
}

static boow ipmw_fiww_tabwe(stwuct mw_tabwe *mwt, stwuct sk_buff *skb)
{
	u32 queue_wen = atomic_wead(&mwt->cache_wesowve_queue_wen);

	if (nwa_put_u32(skb, IPMWA_TABWE_ID, mwt->id) ||
	    nwa_put_u32(skb, IPMWA_TABWE_CACHE_WES_QUEUE_WEN, queue_wen) ||
	    nwa_put_s32(skb, IPMWA_TABWE_MWOUTE_WEG_VIF_NUM,
			mwt->mwoute_weg_vif_num) ||
	    nwa_put_u8(skb, IPMWA_TABWE_MWOUTE_DO_ASSEWT,
		       mwt->mwoute_do_assewt) ||
	    nwa_put_u8(skb, IPMWA_TABWE_MWOUTE_DO_PIM, mwt->mwoute_do_pim) ||
	    nwa_put_u8(skb, IPMWA_TABWE_MWOUTE_DO_WWVIFWHOWE,
		       mwt->mwoute_do_wwvifwhowe))
		wetuwn fawse;

	wetuwn twue;
}

static boow ipmw_fiww_vif(stwuct mw_tabwe *mwt, u32 vifid, stwuct sk_buff *skb)
{
	stwuct net_device *vif_dev;
	stwuct nwattw *vif_nest;
	stwuct vif_device *vif;

	vif = &mwt->vif_tabwe[vifid];
	vif_dev = wtnw_dewefewence(vif->dev);
	/* if the VIF doesn't exist just continue */
	if (!vif_dev)
		wetuwn twue;

	vif_nest = nwa_nest_stawt_nofwag(skb, IPMWA_VIF);
	if (!vif_nest)
		wetuwn fawse;

	if (nwa_put_u32(skb, IPMWA_VIFA_IFINDEX, vif_dev->ifindex) ||
	    nwa_put_u32(skb, IPMWA_VIFA_VIF_ID, vifid) ||
	    nwa_put_u16(skb, IPMWA_VIFA_FWAGS, vif->fwags) ||
	    nwa_put_u64_64bit(skb, IPMWA_VIFA_BYTES_IN, vif->bytes_in,
			      IPMWA_VIFA_PAD) ||
	    nwa_put_u64_64bit(skb, IPMWA_VIFA_BYTES_OUT, vif->bytes_out,
			      IPMWA_VIFA_PAD) ||
	    nwa_put_u64_64bit(skb, IPMWA_VIFA_PACKETS_IN, vif->pkt_in,
			      IPMWA_VIFA_PAD) ||
	    nwa_put_u64_64bit(skb, IPMWA_VIFA_PACKETS_OUT, vif->pkt_out,
			      IPMWA_VIFA_PAD) ||
	    nwa_put_be32(skb, IPMWA_VIFA_WOCAW_ADDW, vif->wocaw) ||
	    nwa_put_be32(skb, IPMWA_VIFA_WEMOTE_ADDW, vif->wemote)) {
		nwa_nest_cancew(skb, vif_nest);
		wetuwn fawse;
	}
	nwa_nest_end(skb, vif_nest);

	wetuwn twue;
}

static int ipmw_vawid_dumpwink(const stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ifinfomsg *ifm;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifm))) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid headew fow ipmw wink dump");
		wetuwn -EINVAW;
	}

	if (nwmsg_attwwen(nwh, sizeof(*ifm))) {
		NW_SET_EWW_MSG(extack, "Invawid data aftew headew in ipmw wink dump");
		wetuwn -EINVAW;
	}

	ifm = nwmsg_data(nwh);
	if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_fwags ||
	    ifm->ifi_change || ifm->ifi_index) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow ipmw wink dump wequest");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ipmw_wtm_dumpwink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwmsghdw *nwh = NUWW;
	unsigned int t = 0, s_t;
	unsigned int e = 0, s_e;
	stwuct mw_tabwe *mwt;

	if (cb->stwict_check) {
		int eww = ipmw_vawid_dumpwink(cb->nwh, cb->extack);

		if (eww < 0)
			wetuwn eww;
	}

	s_t = cb->awgs[0];
	s_e = cb->awgs[1];

	ipmw_fow_each_tabwe(mwt, net) {
		stwuct nwattw *vifs, *af;
		stwuct ifinfomsg *hdw;
		u32 i;

		if (t < s_t)
			goto skip_tabwe;
		nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, WTM_NEWWINK,
				sizeof(*hdw), NWM_F_MUWTI);
		if (!nwh)
			bweak;

		hdw = nwmsg_data(nwh);
		memset(hdw, 0, sizeof(*hdw));
		hdw->ifi_famiwy = WTNW_FAMIWY_IPMW;

		af = nwa_nest_stawt_nofwag(skb, IFWA_AF_SPEC);
		if (!af) {
			nwmsg_cancew(skb, nwh);
			goto out;
		}

		if (!ipmw_fiww_tabwe(mwt, skb)) {
			nwmsg_cancew(skb, nwh);
			goto out;
		}

		vifs = nwa_nest_stawt_nofwag(skb, IPMWA_TABWE_VIFS);
		if (!vifs) {
			nwa_nest_end(skb, af);
			nwmsg_end(skb, nwh);
			goto out;
		}
		fow (i = 0; i < mwt->maxvif; i++) {
			if (e < s_e)
				goto skip_entwy;
			if (!ipmw_fiww_vif(mwt, i, skb)) {
				nwa_nest_end(skb, vifs);
				nwa_nest_end(skb, af);
				nwmsg_end(skb, nwh);
				goto out;
			}
skip_entwy:
			e++;
		}
		s_e = 0;
		e = 0;
		nwa_nest_end(skb, vifs);
		nwa_nest_end(skb, af);
		nwmsg_end(skb, nwh);
skip_tabwe:
		t++;
	}

out:
	cb->awgs[1] = e;
	cb->awgs[0] = t;

	wetuwn skb->wen;
}

#ifdef CONFIG_PWOC_FS
/* The /pwoc intewfaces to muwticast wouting :
 * /pwoc/net/ip_mw_cache & /pwoc/net/ip_mw_vif
 */

static void *ipmw_vif_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct mw_vif_itew *itew = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct mw_tabwe *mwt;

	mwt = ipmw_get_tabwe(net, WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn EWW_PTW(-ENOENT);

	itew->mwt = mwt;

	wcu_wead_wock();
	wetuwn mw_vif_seq_stawt(seq, pos);
}

static void ipmw_vif_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static int ipmw_vif_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct mw_vif_itew *itew = seq->pwivate;
	stwuct mw_tabwe *mwt = itew->mwt;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
			 "Intewface      BytesIn  PktsIn  BytesOut PktsOut Fwags Wocaw    Wemote\n");
	} ewse {
		const stwuct vif_device *vif = v;
		const stwuct net_device *vif_dev;
		const chaw *name;

		vif_dev = vif_dev_wead(vif);
		name = vif_dev ? vif_dev->name : "none";
		seq_pwintf(seq,
			   "%2td %-10s %8wd %7wd  %8wd %7wd %05X %08X %08X\n",
			   vif - mwt->vif_tabwe,
			   name, vif->bytes_in, vif->pkt_in,
			   vif->bytes_out, vif->pkt_out,
			   vif->fwags, vif->wocaw, vif->wemote);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ipmw_vif_seq_ops = {
	.stawt = ipmw_vif_seq_stawt,
	.next  = mw_vif_seq_next,
	.stop  = ipmw_vif_seq_stop,
	.show  = ipmw_vif_seq_show,
};

static void *ipmw_mfc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	stwuct mw_tabwe *mwt;

	mwt = ipmw_get_tabwe(net, WT_TABWE_DEFAUWT);
	if (!mwt)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn mw_mfc_seq_stawt(seq, pos, mwt, &mfc_unwes_wock);
}

static int ipmw_mfc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	int n;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
		 "Gwoup    Owigin   Iif     Pkts    Bytes    Wwong Oifs\n");
	} ewse {
		const stwuct mfc_cache *mfc = v;
		const stwuct mw_mfc_itew *it = seq->pwivate;
		const stwuct mw_tabwe *mwt = it->mwt;

		seq_pwintf(seq, "%08X %08X %-3hd",
			   (__fowce u32) mfc->mfc_mcastgwp,
			   (__fowce u32) mfc->mfc_owigin,
			   mfc->_c.mfc_pawent);

		if (it->cache != &mwt->mfc_unwes_queue) {
			seq_pwintf(seq, " %8wu %8wu %8wu",
				   mfc->_c.mfc_un.wes.pkt,
				   mfc->_c.mfc_un.wes.bytes,
				   mfc->_c.mfc_un.wes.wwong_if);
			fow (n = mfc->_c.mfc_un.wes.minvif;
			     n < mfc->_c.mfc_un.wes.maxvif; n++) {
				if (VIF_EXISTS(mwt, n) &&
				    mfc->_c.mfc_un.wes.ttws[n] < 255)
					seq_pwintf(seq,
					   " %2d:%-3d",
					   n, mfc->_c.mfc_un.wes.ttws[n]);
			}
		} ewse {
			/* unwesowved mfc_caches don't contain
			 * pkt, bytes and wwong_if vawues
			 */
			seq_pwintf(seq, " %8wu %8wu %8wu", 0uw, 0uw, 0uw);
		}
		seq_putc(seq, '\n');
	}
	wetuwn 0;
}

static const stwuct seq_opewations ipmw_mfc_seq_ops = {
	.stawt = ipmw_mfc_seq_stawt,
	.next  = mw_mfc_seq_next,
	.stop  = mw_mfc_seq_stop,
	.show  = ipmw_mfc_seq_show,
};
#endif

#ifdef CONFIG_IP_PIMSM_V2
static const stwuct net_pwotocow pim_pwotocow = {
	.handwew	=	pim_wcv,
};
#endif

static unsigned int ipmw_seq_wead(stwuct net *net)
{
	ASSEWT_WTNW();

	wetuwn net->ipv4.ipmw_seq + ipmw_wuwes_seq_wead(net);
}

static int ipmw_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		     stwuct netwink_ext_ack *extack)
{
	wetuwn mw_dump(net, nb, WTNW_FAMIWY_IPMW, ipmw_wuwes_dump,
		       ipmw_mw_tabwe_itew, extack);
}

static const stwuct fib_notifiew_ops ipmw_notifiew_ops_tempwate = {
	.famiwy		= WTNW_FAMIWY_IPMW,
	.fib_seq_wead	= ipmw_seq_wead,
	.fib_dump	= ipmw_dump,
	.ownew		= THIS_MODUWE,
};

static int __net_init ipmw_notifiew_init(stwuct net *net)
{
	stwuct fib_notifiew_ops *ops;

	net->ipv4.ipmw_seq = 0;

	ops = fib_notifiew_ops_wegistew(&ipmw_notifiew_ops_tempwate, net);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);
	net->ipv4.ipmw_notifiew_ops = ops;

	wetuwn 0;
}

static void __net_exit ipmw_notifiew_exit(stwuct net *net)
{
	fib_notifiew_ops_unwegistew(net->ipv4.ipmw_notifiew_ops);
	net->ipv4.ipmw_notifiew_ops = NUWW;
}

/* Setup fow IP muwticast wouting */
static int __net_init ipmw_net_init(stwuct net *net)
{
	int eww;

	eww = ipmw_notifiew_init(net);
	if (eww)
		goto ipmw_notifiew_faiw;

	eww = ipmw_wuwes_init(net);
	if (eww < 0)
		goto ipmw_wuwes_faiw;

#ifdef CONFIG_PWOC_FS
	eww = -ENOMEM;
	if (!pwoc_cweate_net("ip_mw_vif", 0, net->pwoc_net, &ipmw_vif_seq_ops,
			sizeof(stwuct mw_vif_itew)))
		goto pwoc_vif_faiw;
	if (!pwoc_cweate_net("ip_mw_cache", 0, net->pwoc_net, &ipmw_mfc_seq_ops,
			sizeof(stwuct mw_mfc_itew)))
		goto pwoc_cache_faiw;
#endif
	wetuwn 0;

#ifdef CONFIG_PWOC_FS
pwoc_cache_faiw:
	wemove_pwoc_entwy("ip_mw_vif", net->pwoc_net);
pwoc_vif_faiw:
	wtnw_wock();
	ipmw_wuwes_exit(net);
	wtnw_unwock();
#endif
ipmw_wuwes_faiw:
	ipmw_notifiew_exit(net);
ipmw_notifiew_faiw:
	wetuwn eww;
}

static void __net_exit ipmw_net_exit(stwuct net *net)
{
#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("ip_mw_cache", net->pwoc_net);
	wemove_pwoc_entwy("ip_mw_vif", net->pwoc_net);
#endif
	ipmw_notifiew_exit(net);
}

static void __net_exit ipmw_net_exit_batch(stwuct wist_head *net_wist)
{
	stwuct net *net;

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		ipmw_wuwes_exit(net);
	wtnw_unwock();
}

static stwuct pewnet_opewations ipmw_net_ops = {
	.init = ipmw_net_init,
	.exit = ipmw_net_exit,
	.exit_batch = ipmw_net_exit_batch,
};

int __init ip_mw_init(void)
{
	int eww;

	mwt_cachep = kmem_cache_cweate("ip_mwt_cache",
				       sizeof(stwuct mfc_cache),
				       0, SWAB_HWCACHE_AWIGN | SWAB_PANIC,
				       NUWW);

	eww = wegistew_pewnet_subsys(&ipmw_net_ops);
	if (eww)
		goto weg_pewnet_faiw;

	eww = wegistew_netdevice_notifiew(&ip_mw_notifiew);
	if (eww)
		goto weg_notif_faiw;
#ifdef CONFIG_IP_PIMSM_V2
	if (inet_add_pwotocow(&pim_pwotocow, IPPWOTO_PIM) < 0) {
		pw_eww("%s: can't add PIM pwotocow\n", __func__);
		eww = -EAGAIN;
		goto add_pwoto_faiw;
	}
#endif
	wtnw_wegistew(WTNW_FAMIWY_IPMW, WTM_GETWOUTE,
		      ipmw_wtm_getwoute, ipmw_wtm_dumpwoute, 0);
	wtnw_wegistew(WTNW_FAMIWY_IPMW, WTM_NEWWOUTE,
		      ipmw_wtm_woute, NUWW, 0);
	wtnw_wegistew(WTNW_FAMIWY_IPMW, WTM_DEWWOUTE,
		      ipmw_wtm_woute, NUWW, 0);

	wtnw_wegistew(WTNW_FAMIWY_IPMW, WTM_GETWINK,
		      NUWW, ipmw_wtm_dumpwink, 0);
	wetuwn 0;

#ifdef CONFIG_IP_PIMSM_V2
add_pwoto_faiw:
	unwegistew_netdevice_notifiew(&ip_mw_notifiew);
#endif
weg_notif_faiw:
	unwegistew_pewnet_subsys(&ipmw_net_ops);
weg_pewnet_faiw:
	kmem_cache_destwoy(mwt_cachep);
	wetuwn eww;
}
