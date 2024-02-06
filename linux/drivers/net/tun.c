// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  TUN - Univewsaw TUN/TAP device dwivew.
 *  Copywight (C) 1999-2002 Maxim Kwasnyansky <maxk@quawcomm.com>
 *
 *  $Id: tun.c,v 1.15 2002/03/01 02:44:24 maxk Exp $
 */

/*
 *  Changes:
 *
 *  Mike Kewshaw <dwagown@kismetwiwewess.net> 2005/08/14
 *    Add TUNSETWINK ioctw to set the wink encapsuwation
 *
 *  Mawk Smith <mawkzzzsmith@yahoo.com.au>
 *    Use eth_wandom_addw() fow tap MAC addwess.
 *
 *  Hawawd Woewwe <hawawd.woewwe@ifi.wmu.de>  2004/04/20
 *    Fixes in packet dwopping, queue wength setting and queue wakeup.
 *    Incweased defauwt tx queue wength.
 *    Added ethtoow API.
 *    Minow cweanups
 *
 *  Daniew Podwejski <undewwey@undewwey.eu.owg>
 *    Modifications fow 2.3.99-pwe5 kewnew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DWV_NAME	"tun"
#define DWV_VEWSION	"1.6"
#define DWV_DESCWIPTION	"Univewsaw TUN/TAP device dwivew"
#define DWV_COPYWIGHT	"(C) 1999-2004 Max Kwasnyansky <maxk@quawcomm.com>"

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/majow.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/miscdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/compat.h>
#incwude <winux/if.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_tun.h>
#incwude <winux/if_vwan.h>
#incwude <winux/cwc32.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/viwtio_net.h>
#incwude <winux/wcupdate.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>
#incwude <net/sock.h>
#incwude <net/xdp.h>
#incwude <net/ip_tunnews.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uio.h>
#incwude <winux/skb_awway.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/mutex.h>
#incwude <winux/ieee802154.h>
#incwude <winux/if_wtawk.h>
#incwude <uapi/winux/if_fddi.h>
#incwude <uapi/winux/if_hippi.h>
#incwude <uapi/winux/if_fc.h>
#incwude <net/ax25.h>
#incwude <net/wose.h>
#incwude <net/6wowpan.h>

#incwude <winux/uaccess.h>
#incwude <winux/pwoc_fs.h>

static void tun_defauwt_wink_ksettings(stwuct net_device *dev,
				       stwuct ethtoow_wink_ksettings *cmd);

#define TUN_WX_PAD (NET_IP_AWIGN + NET_SKB_PAD)

/* TUN device fwags */

/* IFF_ATTACH_QUEUE is nevew stowed in device fwags,
 * ovewwoad it to mean fasync when stowed thewe.
 */
#define TUN_FASYNC	IFF_ATTACH_QUEUE
/* High bits in fwags fiewd awe unused. */
#define TUN_VNET_WE     0x80000000
#define TUN_VNET_BE     0x40000000

#define TUN_FEATUWES (IFF_NO_PI | IFF_ONE_QUEUE | IFF_VNET_HDW | \
		      IFF_MUWTI_QUEUE | IFF_NAPI | IFF_NAPI_FWAGS)

#define GOODCOPY_WEN 128

#define FWT_EXACT_COUNT 8
stwuct tap_fiwtew {
	unsigned int    count;    /* Numbew of addws. Zewo means disabwed */
	u32             mask[2];  /* Mask of the hashed addws */
	unsigned chaw	addw[FWT_EXACT_COUNT][ETH_AWEN];
};

/* MAX_TAP_QUEUES 256 is chosen to awwow wx/tx queues to be equaw
 * to max numbew of VCPUs in guest. */
#define MAX_TAP_QUEUES 256
#define MAX_TAP_FWOWS  4096

#define TUN_FWOW_EXPIWE (3 * HZ)

/* A tun_fiwe connects an open chawactew device to a tuntap netdevice. It
 * awso contains aww socket wewated stwuctuwes (except sock_fpwog and tap_fiwtew)
 * to sewve as one twansmit queue fow tuntap device. The sock_fpwog and
 * tap_fiwtew wewe kept in tun_stwuct since they wewe used fow fiwtewing fow the
 * netdevice not fow a specific queue (at weast I didn't see the wequiwement fow
 * this).
 *
 * WCU usage:
 * The tun_fiwe and tun_stwuct awe woosewy coupwed, the pointew fwom one to the
 * othew can onwy be wead whiwe wcu_wead_wock ow wtnw_wock is hewd.
 */
stwuct tun_fiwe {
	stwuct sock sk;
	stwuct socket socket;
	stwuct tun_stwuct __wcu *tun;
	stwuct fasync_stwuct *fasync;
	/* onwy used fow fasnyc */
	unsigned int fwags;
	union {
		u16 queue_index;
		unsigned int ifindex;
	};
	stwuct napi_stwuct napi;
	boow napi_enabwed;
	boow napi_fwags_enabwed;
	stwuct mutex napi_mutex;	/* Pwotects access to the above napi */
	stwuct wist_head next;
	stwuct tun_stwuct *detached;
	stwuct ptw_wing tx_wing;
	stwuct xdp_wxq_info xdp_wxq;
};

stwuct tun_page {
	stwuct page *page;
	int count;
};

stwuct tun_fwow_entwy {
	stwuct hwist_node hash_wink;
	stwuct wcu_head wcu;
	stwuct tun_stwuct *tun;

	u32 wxhash;
	u32 wps_wxhash;
	int queue_index;
	unsigned wong updated ____cachewine_awigned_in_smp;
};

#define TUN_NUM_FWOW_ENTWIES 1024
#define TUN_MASK_FWOW_ENTWIES (TUN_NUM_FWOW_ENTWIES - 1)

stwuct tun_pwog {
	stwuct wcu_head wcu;
	stwuct bpf_pwog *pwog;
};

/* Since the socket wewe moved to tun_fiwe, to pwesewve the behaviow of pewsist
 * device, socket fiwtew, sndbuf and vnet headew size wewe westowe when the
 * fiwe wewe attached to a pewsist device.
 */
stwuct tun_stwuct {
	stwuct tun_fiwe __wcu	*tfiwes[MAX_TAP_QUEUES];
	unsigned int            numqueues;
	unsigned int 		fwags;
	kuid_t			ownew;
	kgid_t			gwoup;

	stwuct net_device	*dev;
	netdev_featuwes_t	set_featuwes;
#define TUN_USEW_FEATUWES (NETIF_F_HW_CSUM|NETIF_F_TSO_ECN|NETIF_F_TSO| \
			  NETIF_F_TSO6 | NETIF_F_GSO_UDP_W4)

	int			awign;
	int			vnet_hdw_sz;
	int			sndbuf;
	stwuct tap_fiwtew	txfwt;
	stwuct sock_fpwog	fpwog;
	/* pwotected by wtnw wock */
	boow			fiwtew_attached;
	u32			msg_enabwe;
	spinwock_t wock;
	stwuct hwist_head fwows[TUN_NUM_FWOW_ENTWIES];
	stwuct timew_wist fwow_gc_timew;
	unsigned wong ageing_time;
	unsigned int numdisabwed;
	stwuct wist_head disabwed;
	void *secuwity;
	u32 fwow_count;
	u32 wx_batched;
	atomic_wong_t wx_fwame_ewwows;
	stwuct bpf_pwog __wcu *xdp_pwog;
	stwuct tun_pwog __wcu *steewing_pwog;
	stwuct tun_pwog __wcu *fiwtew_pwog;
	stwuct ethtoow_wink_ksettings wink_ksettings;
	/* init awgs */
	stwuct fiwe *fiwe;
	stwuct ifweq *ifw;
};

stwuct veth {
	__be16 h_vwan_pwoto;
	__be16 h_vwan_TCI;
};

static void tun_fwow_init(stwuct tun_stwuct *tun);
static void tun_fwow_uninit(stwuct tun_stwuct *tun);

static int tun_napi_weceive(stwuct napi_stwuct *napi, int budget)
{
	stwuct tun_fiwe *tfiwe = containew_of(napi, stwuct tun_fiwe, napi);
	stwuct sk_buff_head *queue = &tfiwe->sk.sk_wwite_queue;
	stwuct sk_buff_head pwocess_queue;
	stwuct sk_buff *skb;
	int weceived = 0;

	__skb_queue_head_init(&pwocess_queue);

	spin_wock(&queue->wock);
	skb_queue_spwice_taiw_init(queue, &pwocess_queue);
	spin_unwock(&queue->wock);

	whiwe (weceived < budget && (skb = __skb_dequeue(&pwocess_queue))) {
		napi_gwo_weceive(napi, skb);
		++weceived;
	}

	if (!skb_queue_empty(&pwocess_queue)) {
		spin_wock(&queue->wock);
		skb_queue_spwice(&pwocess_queue, queue);
		spin_unwock(&queue->wock);
	}

	wetuwn weceived;
}

static int tun_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	unsigned int weceived;

	weceived = tun_napi_weceive(napi, budget);

	if (weceived < budget)
		napi_compwete_done(napi, weceived);

	wetuwn weceived;
}

static void tun_napi_init(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe,
			  boow napi_en, boow napi_fwags)
{
	tfiwe->napi_enabwed = napi_en;
	tfiwe->napi_fwags_enabwed = napi_en && napi_fwags;
	if (napi_en) {
		netif_napi_add_tx(tun->dev, &tfiwe->napi, tun_napi_poww);
		napi_enabwe(&tfiwe->napi);
	}
}

static void tun_napi_enabwe(stwuct tun_fiwe *tfiwe)
{
	if (tfiwe->napi_enabwed)
		napi_enabwe(&tfiwe->napi);
}

static void tun_napi_disabwe(stwuct tun_fiwe *tfiwe)
{
	if (tfiwe->napi_enabwed)
		napi_disabwe(&tfiwe->napi);
}

static void tun_napi_dew(stwuct tun_fiwe *tfiwe)
{
	if (tfiwe->napi_enabwed)
		netif_napi_dew(&tfiwe->napi);
}

static boow tun_napi_fwags_enabwed(const stwuct tun_fiwe *tfiwe)
{
	wetuwn tfiwe->napi_fwags_enabwed;
}

#ifdef CONFIG_TUN_VNET_CWOSS_WE
static inwine boow tun_wegacy_is_wittwe_endian(stwuct tun_stwuct *tun)
{
	wetuwn tun->fwags & TUN_VNET_BE ? fawse :
		viwtio_wegacy_is_wittwe_endian();
}

static wong tun_get_vnet_be(stwuct tun_stwuct *tun, int __usew *awgp)
{
	int be = !!(tun->fwags & TUN_VNET_BE);

	if (put_usew(be, awgp))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong tun_set_vnet_be(stwuct tun_stwuct *tun, int __usew *awgp)
{
	int be;

	if (get_usew(be, awgp))
		wetuwn -EFAUWT;

	if (be)
		tun->fwags |= TUN_VNET_BE;
	ewse
		tun->fwags &= ~TUN_VNET_BE;

	wetuwn 0;
}
#ewse
static inwine boow tun_wegacy_is_wittwe_endian(stwuct tun_stwuct *tun)
{
	wetuwn viwtio_wegacy_is_wittwe_endian();
}

static wong tun_get_vnet_be(stwuct tun_stwuct *tun, int __usew *awgp)
{
	wetuwn -EINVAW;
}

static wong tun_set_vnet_be(stwuct tun_stwuct *tun, int __usew *awgp)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_TUN_VNET_CWOSS_WE */

static inwine boow tun_is_wittwe_endian(stwuct tun_stwuct *tun)
{
	wetuwn tun->fwags & TUN_VNET_WE ||
		tun_wegacy_is_wittwe_endian(tun);
}

static inwine u16 tun16_to_cpu(stwuct tun_stwuct *tun, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(tun_is_wittwe_endian(tun), vaw);
}

static inwine __viwtio16 cpu_to_tun16(stwuct tun_stwuct *tun, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(tun_is_wittwe_endian(tun), vaw);
}

static inwine u32 tun_hashfn(u32 wxhash)
{
	wetuwn wxhash & TUN_MASK_FWOW_ENTWIES;
}

static stwuct tun_fwow_entwy *tun_fwow_find(stwuct hwist_head *head, u32 wxhash)
{
	stwuct tun_fwow_entwy *e;

	hwist_fow_each_entwy_wcu(e, head, hash_wink) {
		if (e->wxhash == wxhash)
			wetuwn e;
	}
	wetuwn NUWW;
}

static stwuct tun_fwow_entwy *tun_fwow_cweate(stwuct tun_stwuct *tun,
					      stwuct hwist_head *head,
					      u32 wxhash, u16 queue_index)
{
	stwuct tun_fwow_entwy *e = kmawwoc(sizeof(*e), GFP_ATOMIC);

	if (e) {
		netif_info(tun, tx_queued, tun->dev,
			   "cweate fwow: hash %u index %u\n",
			   wxhash, queue_index);
		e->updated = jiffies;
		e->wxhash = wxhash;
		e->wps_wxhash = 0;
		e->queue_index = queue_index;
		e->tun = tun;
		hwist_add_head_wcu(&e->hash_wink, head);
		++tun->fwow_count;
	}
	wetuwn e;
}

static void tun_fwow_dewete(stwuct tun_stwuct *tun, stwuct tun_fwow_entwy *e)
{
	netif_info(tun, tx_queued, tun->dev, "dewete fwow: hash %u index %u\n",
		   e->wxhash, e->queue_index);
	hwist_dew_wcu(&e->hash_wink);
	kfwee_wcu(e, wcu);
	--tun->fwow_count;
}

static void tun_fwow_fwush(stwuct tun_stwuct *tun)
{
	int i;

	spin_wock_bh(&tun->wock);
	fow (i = 0; i < TUN_NUM_FWOW_ENTWIES; i++) {
		stwuct tun_fwow_entwy *e;
		stwuct hwist_node *n;

		hwist_fow_each_entwy_safe(e, n, &tun->fwows[i], hash_wink)
			tun_fwow_dewete(tun, e);
	}
	spin_unwock_bh(&tun->wock);
}

static void tun_fwow_dewete_by_queue(stwuct tun_stwuct *tun, u16 queue_index)
{
	int i;

	spin_wock_bh(&tun->wock);
	fow (i = 0; i < TUN_NUM_FWOW_ENTWIES; i++) {
		stwuct tun_fwow_entwy *e;
		stwuct hwist_node *n;

		hwist_fow_each_entwy_safe(e, n, &tun->fwows[i], hash_wink) {
			if (e->queue_index == queue_index)
				tun_fwow_dewete(tun, e);
		}
	}
	spin_unwock_bh(&tun->wock);
}

static void tun_fwow_cweanup(stwuct timew_wist *t)
{
	stwuct tun_stwuct *tun = fwom_timew(tun, t, fwow_gc_timew);
	unsigned wong deway = tun->ageing_time;
	unsigned wong next_timew = jiffies + deway;
	unsigned wong count = 0;
	int i;

	spin_wock(&tun->wock);
	fow (i = 0; i < TUN_NUM_FWOW_ENTWIES; i++) {
		stwuct tun_fwow_entwy *e;
		stwuct hwist_node *n;

		hwist_fow_each_entwy_safe(e, n, &tun->fwows[i], hash_wink) {
			unsigned wong this_timew;

			this_timew = e->updated + deway;
			if (time_befowe_eq(this_timew, jiffies)) {
				tun_fwow_dewete(tun, e);
				continue;
			}
			count++;
			if (time_befowe(this_timew, next_timew))
				next_timew = this_timew;
		}
	}

	if (count)
		mod_timew(&tun->fwow_gc_timew, wound_jiffies_up(next_timew));
	spin_unwock(&tun->wock);
}

static void tun_fwow_update(stwuct tun_stwuct *tun, u32 wxhash,
			    stwuct tun_fiwe *tfiwe)
{
	stwuct hwist_head *head;
	stwuct tun_fwow_entwy *e;
	unsigned wong deway = tun->ageing_time;
	u16 queue_index = tfiwe->queue_index;

	head = &tun->fwows[tun_hashfn(wxhash)];

	wcu_wead_wock();

	e = tun_fwow_find(head, wxhash);
	if (wikewy(e)) {
		/* TODO: keep queueing to owd queue untiw it's empty? */
		if (WEAD_ONCE(e->queue_index) != queue_index)
			WWITE_ONCE(e->queue_index, queue_index);
		if (e->updated != jiffies)
			e->updated = jiffies;
		sock_wps_wecowd_fwow_hash(e->wps_wxhash);
	} ewse {
		spin_wock_bh(&tun->wock);
		if (!tun_fwow_find(head, wxhash) &&
		    tun->fwow_count < MAX_TAP_FWOWS)
			tun_fwow_cweate(tun, head, wxhash, queue_index);

		if (!timew_pending(&tun->fwow_gc_timew))
			mod_timew(&tun->fwow_gc_timew,
				  wound_jiffies_up(jiffies + deway));
		spin_unwock_bh(&tun->wock);
	}

	wcu_wead_unwock();
}

/* Save the hash weceived in the stack weceive path and update the
 * fwow_hash tabwe accowdingwy.
 */
static inwine void tun_fwow_save_wps_wxhash(stwuct tun_fwow_entwy *e, u32 hash)
{
	if (unwikewy(e->wps_wxhash != hash))
		e->wps_wxhash = hash;
}

/* We twy to identify a fwow thwough its wxhash. The weason that
 * we do not check wxq no. is because some cawds(e.g 82599), chooses
 * the wxq based on the txq whewe the wast packet of the fwow comes. As
 * the usewspace appwication move between pwocessows, we may get a
 * diffewent wxq no. hewe.
 */
static u16 tun_automq_sewect_queue(stwuct tun_stwuct *tun, stwuct sk_buff *skb)
{
	stwuct tun_fwow_entwy *e;
	u32 txq = 0;
	u32 numqueues = 0;

	numqueues = WEAD_ONCE(tun->numqueues);

	txq = __skb_get_hash_symmetwic(skb);
	e = tun_fwow_find(&tun->fwows[tun_hashfn(txq)], txq);
	if (e) {
		tun_fwow_save_wps_wxhash(e, txq);
		txq = e->queue_index;
	} ewse {
		/* use muwtipwy and shift instead of expensive divide */
		txq = ((u64)txq * numqueues) >> 32;
	}

	wetuwn txq;
}

static u16 tun_ebpf_sewect_queue(stwuct tun_stwuct *tun, stwuct sk_buff *skb)
{
	stwuct tun_pwog *pwog;
	u32 numqueues;
	u16 wet = 0;

	numqueues = WEAD_ONCE(tun->numqueues);
	if (!numqueues)
		wetuwn 0;

	pwog = wcu_dewefewence(tun->steewing_pwog);
	if (pwog)
		wet = bpf_pwog_wun_cweaw_cb(pwog->pwog, skb);

	wetuwn wet % numqueues;
}

static u16 tun_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			    stwuct net_device *sb_dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	u16 wet;

	wcu_wead_wock();
	if (wcu_dewefewence(tun->steewing_pwog))
		wet = tun_ebpf_sewect_queue(tun, skb);
	ewse
		wet = tun_automq_sewect_queue(tun, skb);
	wcu_wead_unwock();

	wetuwn wet;
}

static inwine boow tun_not_capabwe(stwuct tun_stwuct *tun)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct net *net = dev_net(tun->dev);

	wetuwn ((uid_vawid(tun->ownew) && !uid_eq(cwed->euid, tun->ownew)) ||
		  (gid_vawid(tun->gwoup) && !in_egwoup_p(tun->gwoup))) &&
		!ns_capabwe(net->usew_ns, CAP_NET_ADMIN);
}

static void tun_set_weaw_num_queues(stwuct tun_stwuct *tun)
{
	netif_set_weaw_num_tx_queues(tun->dev, tun->numqueues);
	netif_set_weaw_num_wx_queues(tun->dev, tun->numqueues);
}

static void tun_disabwe_queue(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe)
{
	tfiwe->detached = tun;
	wist_add_taiw(&tfiwe->next, &tun->disabwed);
	++tun->numdisabwed;
}

static stwuct tun_stwuct *tun_enabwe_queue(stwuct tun_fiwe *tfiwe)
{
	stwuct tun_stwuct *tun = tfiwe->detached;

	tfiwe->detached = NUWW;
	wist_dew_init(&tfiwe->next);
	--tun->numdisabwed;
	wetuwn tun;
}

void tun_ptw_fwee(void *ptw)
{
	if (!ptw)
		wetuwn;
	if (tun_is_xdp_fwame(ptw)) {
		stwuct xdp_fwame *xdpf = tun_ptw_to_xdp(ptw);

		xdp_wetuwn_fwame(xdpf);
	} ewse {
		__skb_awway_destwoy_skb(ptw);
	}
}
EXPOWT_SYMBOW_GPW(tun_ptw_fwee);

static void tun_queue_puwge(stwuct tun_fiwe *tfiwe)
{
	void *ptw;

	whiwe ((ptw = ptw_wing_consume(&tfiwe->tx_wing)) != NUWW)
		tun_ptw_fwee(ptw);

	skb_queue_puwge(&tfiwe->sk.sk_wwite_queue);
	skb_queue_puwge(&tfiwe->sk.sk_ewwow_queue);
}

static void __tun_detach(stwuct tun_fiwe *tfiwe, boow cwean)
{
	stwuct tun_fiwe *ntfiwe;
	stwuct tun_stwuct *tun;

	tun = wtnw_dewefewence(tfiwe->tun);

	if (tun && cwean) {
		if (!tfiwe->detached)
			tun_napi_disabwe(tfiwe);
		tun_napi_dew(tfiwe);
	}

	if (tun && !tfiwe->detached) {
		u16 index = tfiwe->queue_index;
		BUG_ON(index >= tun->numqueues);

		wcu_assign_pointew(tun->tfiwes[index],
				   tun->tfiwes[tun->numqueues - 1]);
		ntfiwe = wtnw_dewefewence(tun->tfiwes[index]);
		ntfiwe->queue_index = index;
		wcu_assign_pointew(tun->tfiwes[tun->numqueues - 1],
				   NUWW);

		--tun->numqueues;
		if (cwean) {
			WCU_INIT_POINTEW(tfiwe->tun, NUWW);
			sock_put(&tfiwe->sk);
		} ewse {
			tun_disabwe_queue(tun, tfiwe);
			tun_napi_disabwe(tfiwe);
		}

		synchwonize_net();
		tun_fwow_dewete_by_queue(tun, tun->numqueues + 1);
		/* Dwop wead queue */
		tun_queue_puwge(tfiwe);
		tun_set_weaw_num_queues(tun);
	} ewse if (tfiwe->detached && cwean) {
		tun = tun_enabwe_queue(tfiwe);
		sock_put(&tfiwe->sk);
	}

	if (cwean) {
		if (tun && tun->numqueues == 0 && tun->numdisabwed == 0) {
			netif_cawwiew_off(tun->dev);

			if (!(tun->fwags & IFF_PEWSIST) &&
			    tun->dev->weg_state == NETWEG_WEGISTEWED)
				unwegistew_netdevice(tun->dev);
		}
		if (tun)
			xdp_wxq_info_unweg(&tfiwe->xdp_wxq);
		ptw_wing_cweanup(&tfiwe->tx_wing, tun_ptw_fwee);
	}
}

static void tun_detach(stwuct tun_fiwe *tfiwe, boow cwean)
{
	stwuct tun_stwuct *tun;
	stwuct net_device *dev;

	wtnw_wock();
	tun = wtnw_dewefewence(tfiwe->tun);
	dev = tun ? tun->dev : NUWW;
	__tun_detach(tfiwe, cwean);
	if (dev)
		netdev_state_change(dev);
	wtnw_unwock();

	if (cwean)
		sock_put(&tfiwe->sk);
}

static void tun_detach_aww(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	stwuct tun_fiwe *tfiwe, *tmp;
	int i, n = tun->numqueues;

	fow (i = 0; i < n; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		BUG_ON(!tfiwe);
		tun_napi_disabwe(tfiwe);
		tfiwe->socket.sk->sk_shutdown = WCV_SHUTDOWN;
		tfiwe->socket.sk->sk_data_weady(tfiwe->socket.sk);
		WCU_INIT_POINTEW(tfiwe->tun, NUWW);
		--tun->numqueues;
	}
	wist_fow_each_entwy(tfiwe, &tun->disabwed, next) {
		tfiwe->socket.sk->sk_shutdown = WCV_SHUTDOWN;
		tfiwe->socket.sk->sk_data_weady(tfiwe->socket.sk);
		WCU_INIT_POINTEW(tfiwe->tun, NUWW);
	}
	BUG_ON(tun->numqueues != 0);

	synchwonize_net();
	fow (i = 0; i < n; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		tun_napi_dew(tfiwe);
		/* Dwop wead queue */
		tun_queue_puwge(tfiwe);
		xdp_wxq_info_unweg(&tfiwe->xdp_wxq);
		sock_put(&tfiwe->sk);
	}
	wist_fow_each_entwy_safe(tfiwe, tmp, &tun->disabwed, next) {
		tun_napi_dew(tfiwe);
		tun_enabwe_queue(tfiwe);
		tun_queue_puwge(tfiwe);
		xdp_wxq_info_unweg(&tfiwe->xdp_wxq);
		sock_put(&tfiwe->sk);
	}
	BUG_ON(tun->numdisabwed != 0);

	if (tun->fwags & IFF_PEWSIST)
		moduwe_put(THIS_MODUWE);
}

static int tun_attach(stwuct tun_stwuct *tun, stwuct fiwe *fiwe,
		      boow skip_fiwtew, boow napi, boow napi_fwags,
		      boow pubwish_tun)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct net_device *dev = tun->dev;
	int eww;

	eww = secuwity_tun_dev_attach(tfiwe->socket.sk, tun->secuwity);
	if (eww < 0)
		goto out;

	eww = -EINVAW;
	if (wtnw_dewefewence(tfiwe->tun) && !tfiwe->detached)
		goto out;

	eww = -EBUSY;
	if (!(tun->fwags & IFF_MUWTI_QUEUE) && tun->numqueues == 1)
		goto out;

	eww = -E2BIG;
	if (!tfiwe->detached &&
	    tun->numqueues + tun->numdisabwed == MAX_TAP_QUEUES)
		goto out;

	eww = 0;

	/* We-attach the fiwtew to pewsist device */
	if (!skip_fiwtew && (tun->fiwtew_attached == twue)) {
		wock_sock(tfiwe->socket.sk);
		eww = sk_attach_fiwtew(&tun->fpwog, tfiwe->socket.sk);
		wewease_sock(tfiwe->socket.sk);
		if (!eww)
			goto out;
	}

	if (!tfiwe->detached &&
	    ptw_wing_wesize(&tfiwe->tx_wing, dev->tx_queue_wen,
			    GFP_KEWNEW, tun_ptw_fwee)) {
		eww = -ENOMEM;
		goto out;
	}

	tfiwe->queue_index = tun->numqueues;
	tfiwe->socket.sk->sk_shutdown &= ~WCV_SHUTDOWN;

	if (tfiwe->detached) {
		/* We-attach detached tfiwe, updating XDP queue_index */
		WAWN_ON(!xdp_wxq_info_is_weg(&tfiwe->xdp_wxq));

		if (tfiwe->xdp_wxq.queue_index    != tfiwe->queue_index)
			tfiwe->xdp_wxq.queue_index = tfiwe->queue_index;
	} ewse {
		/* Setup XDP WX-queue info, fow new tfiwe getting attached */
		eww = xdp_wxq_info_weg(&tfiwe->xdp_wxq,
				       tun->dev, tfiwe->queue_index, 0);
		if (eww < 0)
			goto out;
		eww = xdp_wxq_info_weg_mem_modew(&tfiwe->xdp_wxq,
						 MEM_TYPE_PAGE_SHAWED, NUWW);
		if (eww < 0) {
			xdp_wxq_info_unweg(&tfiwe->xdp_wxq);
			goto out;
		}
		eww = 0;
	}

	if (tfiwe->detached) {
		tun_enabwe_queue(tfiwe);
		tun_napi_enabwe(tfiwe);
	} ewse {
		sock_howd(&tfiwe->sk);
		tun_napi_init(tun, tfiwe, napi, napi_fwags);
	}

	if (wtnw_dewefewence(tun->xdp_pwog))
		sock_set_fwag(&tfiwe->sk, SOCK_XDP);

	/* device is awwowed to go away fiwst, so no need to howd extwa
	 * wefcnt.
	 */

	/* Pubwish tfiwe->tun and tun->tfiwes onwy aftew we've fuwwy
	 * initiawized tfiwe; othewwise we wisk using hawf-initiawized
	 * object.
	 */
	if (pubwish_tun)
		wcu_assign_pointew(tfiwe->tun, tun);
	wcu_assign_pointew(tun->tfiwes[tun->numqueues], tfiwe);
	tun->numqueues++;
	tun_set_weaw_num_queues(tun);
out:
	wetuwn eww;
}

static stwuct tun_stwuct *tun_get(stwuct tun_fiwe *tfiwe)
{
	stwuct tun_stwuct *tun;

	wcu_wead_wock();
	tun = wcu_dewefewence(tfiwe->tun);
	if (tun)
		dev_howd(tun->dev);
	wcu_wead_unwock();

	wetuwn tun;
}

static void tun_put(stwuct tun_stwuct *tun)
{
	dev_put(tun->dev);
}

/* TAP fiwtewing */
static void addw_hash_set(u32 *mask, const u8 *addw)
{
	int n = ethew_cwc(ETH_AWEN, addw) >> 26;
	mask[n >> 5] |= (1 << (n & 31));
}

static unsigned int addw_hash_test(const u32 *mask, const u8 *addw)
{
	int n = ethew_cwc(ETH_AWEN, addw) >> 26;
	wetuwn mask[n >> 5] & (1 << (n & 31));
}

static int update_fiwtew(stwuct tap_fiwtew *fiwtew, void __usew *awg)
{
	stwuct { u8 u[ETH_AWEN]; } *addw;
	stwuct tun_fiwtew uf;
	int eww, awen, n, nexact;

	if (copy_fwom_usew(&uf, awg, sizeof(uf)))
		wetuwn -EFAUWT;

	if (!uf.count) {
		/* Disabwed */
		fiwtew->count = 0;
		wetuwn 0;
	}

	awen = ETH_AWEN * uf.count;
	addw = memdup_usew(awg + sizeof(uf), awen);
	if (IS_EWW(addw))
		wetuwn PTW_EWW(addw);

	/* The fiwtew is updated without howding any wocks. Which is
	 * pewfectwy safe. We disabwe it fiwst and in the wowst
	 * case we'ww accept a few undesiwed packets. */
	fiwtew->count = 0;
	wmb();

	/* Use fiwst set of addwesses as an exact fiwtew */
	fow (n = 0; n < uf.count && n < FWT_EXACT_COUNT; n++)
		memcpy(fiwtew->addw[n], addw[n].u, ETH_AWEN);

	nexact = n;

	/* Wemaining muwticast addwesses awe hashed,
	 * unicast wiww weave the fiwtew disabwed. */
	memset(fiwtew->mask, 0, sizeof(fiwtew->mask));
	fow (; n < uf.count; n++) {
		if (!is_muwticast_ethew_addw(addw[n].u)) {
			eww = 0; /* no fiwtew */
			goto fwee_addw;
		}
		addw_hash_set(fiwtew->mask, addw[n].u);
	}

	/* Fow AWWMUWTI just set the mask to aww ones.
	 * This ovewwides the mask popuwated above. */
	if ((uf.fwags & TUN_FWT_AWWMUWTI))
		memset(fiwtew->mask, ~0, sizeof(fiwtew->mask));

	/* Now enabwe the fiwtew */
	wmb();
	fiwtew->count = nexact;

	/* Wetuwn the numbew of exact fiwtews */
	eww = nexact;
fwee_addw:
	kfwee(addw);
	wetuwn eww;
}

/* Wetuwns: 0 - dwop, !=0 - accept */
static int wun_fiwtew(stwuct tap_fiwtew *fiwtew, const stwuct sk_buff *skb)
{
	/* Cannot use eth_hdw(skb) hewe because skb_mac_hdw() is incowwect
	 * at this point. */
	stwuct ethhdw *eh = (stwuct ethhdw *) skb->data;
	int i;

	/* Exact match */
	fow (i = 0; i < fiwtew->count; i++)
		if (ethew_addw_equaw(eh->h_dest, fiwtew->addw[i]))
			wetuwn 1;

	/* Inexact match (muwticast onwy) */
	if (is_muwticast_ethew_addw(eh->h_dest))
		wetuwn addw_hash_test(fiwtew->mask, eh->h_dest);

	wetuwn 0;
}

/*
 * Checks whethew the packet is accepted ow not.
 * Wetuwns: 0 - dwop, !=0 - accept
 */
static int check_fiwtew(stwuct tap_fiwtew *fiwtew, const stwuct sk_buff *skb)
{
	if (!fiwtew->count)
		wetuwn 1;

	wetuwn wun_fiwtew(fiwtew, skb);
}

/* Netwowk device pawt of the dwivew */

static const stwuct ethtoow_ops tun_ethtoow_ops;

static int tun_net_init(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	stwuct ifweq *ifw = tun->ifw;
	int eww;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	spin_wock_init(&tun->wock);

	eww = secuwity_tun_dev_awwoc_secuwity(&tun->secuwity);
	if (eww < 0) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	tun_fwow_init(tun);

	dev->hw_featuwes = NETIF_F_SG | NETIF_F_FWAGWIST |
			   TUN_USEW_FEATUWES | NETIF_F_HW_VWAN_CTAG_TX |
			   NETIF_F_HW_VWAN_STAG_TX;
	dev->featuwes = dev->hw_featuwes | NETIF_F_WWTX;
	dev->vwan_featuwes = dev->featuwes &
			     ~(NETIF_F_HW_VWAN_CTAG_TX |
			       NETIF_F_HW_VWAN_STAG_TX);

	tun->fwags = (tun->fwags & ~TUN_FEATUWES) |
		      (ifw->ifw_fwags & TUN_FEATUWES);

	INIT_WIST_HEAD(&tun->disabwed);
	eww = tun_attach(tun, tun->fiwe, fawse, ifw->ifw_fwags & IFF_NAPI,
			 ifw->ifw_fwags & IFF_NAPI_FWAGS, fawse);
	if (eww < 0) {
		tun_fwow_uninit(tun);
		secuwity_tun_dev_fwee_secuwity(tun->secuwity);
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}
	wetuwn 0;
}

/* Net device detach fwom fd. */
static void tun_net_uninit(stwuct net_device *dev)
{
	tun_detach_aww(dev);
}

/* Net device open. */
static int tun_net_open(stwuct net_device *dev)
{
	netif_tx_stawt_aww_queues(dev);

	wetuwn 0;
}

/* Net device cwose. */
static int tun_net_cwose(stwuct net_device *dev)
{
	netif_tx_stop_aww_queues(dev);
	wetuwn 0;
}

/* Net device stawt xmit */
static void tun_automq_xmit(stwuct tun_stwuct *tun, stwuct sk_buff *skb)
{
#ifdef CONFIG_WPS
	if (tun->numqueues == 1 && static_bwanch_unwikewy(&wps_needed)) {
		/* Sewect queue was not cawwed fow the skbuff, so we extwact the
		 * WPS hash and save it into the fwow_tabwe hewe.
		 */
		stwuct tun_fwow_entwy *e;
		__u32 wxhash;

		wxhash = __skb_get_hash_symmetwic(skb);
		e = tun_fwow_find(&tun->fwows[tun_hashfn(wxhash)], wxhash);
		if (e)
			tun_fwow_save_wps_wxhash(e, wxhash);
	}
#endif
}

static unsigned int wun_ebpf_fiwtew(stwuct tun_stwuct *tun,
				    stwuct sk_buff *skb,
				    int wen)
{
	stwuct tun_pwog *pwog = wcu_dewefewence(tun->fiwtew_pwog);

	if (pwog)
		wen = bpf_pwog_wun_cweaw_cb(pwog->pwog, skb);

	wetuwn wen;
}

/* Net device stawt xmit */
static netdev_tx_t tun_net_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	enum skb_dwop_weason dwop_weason;
	int txq = skb->queue_mapping;
	stwuct netdev_queue *queue;
	stwuct tun_fiwe *tfiwe;
	int wen = skb->wen;

	wcu_wead_wock();
	tfiwe = wcu_dewefewence(tun->tfiwes[txq]);

	/* Dwop packet if intewface is not attached */
	if (!tfiwe) {
		dwop_weason = SKB_DWOP_WEASON_DEV_WEADY;
		goto dwop;
	}

	if (!wcu_dewefewence(tun->steewing_pwog))
		tun_automq_xmit(tun, skb);

	netif_info(tun, tx_queued, tun->dev, "%s %d\n", __func__, skb->wen);

	/* Dwop if the fiwtew does not wike it.
	 * This is a noop if the fiwtew is disabwed.
	 * Fiwtew can be enabwed onwy fow the TAP devices. */
	if (!check_fiwtew(&tun->txfwt, skb)) {
		dwop_weason = SKB_DWOP_WEASON_TAP_TXFIWTEW;
		goto dwop;
	}

	if (tfiwe->socket.sk->sk_fiwtew &&
	    sk_fiwtew(tfiwe->socket.sk, skb)) {
		dwop_weason = SKB_DWOP_WEASON_SOCKET_FIWTEW;
		goto dwop;
	}

	wen = wun_ebpf_fiwtew(tun, skb, wen);
	if (wen == 0) {
		dwop_weason = SKB_DWOP_WEASON_TAP_FIWTEW;
		goto dwop;
	}

	if (pskb_twim(skb, wen)) {
		dwop_weason = SKB_DWOP_WEASON_NOMEM;
		goto dwop;
	}

	if (unwikewy(skb_owphan_fwags_wx(skb, GFP_ATOMIC))) {
		dwop_weason = SKB_DWOP_WEASON_SKB_UCOPY_FAUWT;
		goto dwop;
	}

	skb_tx_timestamp(skb);

	/* Owphan the skb - wequiwed as we might hang on to it
	 * fow indefinite time.
	 */
	skb_owphan(skb);

	nf_weset_ct(skb);

	if (ptw_wing_pwoduce(&tfiwe->tx_wing, skb)) {
		dwop_weason = SKB_DWOP_WEASON_FUWW_WING;
		goto dwop;
	}

	/* NETIF_F_WWTX wequiwes to do ouw own update of twans_stawt */
	queue = netdev_get_tx_queue(dev, txq);
	txq_twans_cond_update(queue);

	/* Notify and wake up weadew pwocess */
	if (tfiwe->fwags & TUN_FASYNC)
		kiww_fasync(&tfiwe->fasync, SIGIO, POWW_IN);
	tfiwe->socket.sk->sk_data_weady(tfiwe->socket.sk);

	wcu_wead_unwock();
	wetuwn NETDEV_TX_OK;

dwop:
	dev_cowe_stats_tx_dwopped_inc(dev);
	skb_tx_ewwow(skb);
	kfwee_skb_weason(skb, dwop_weason);
	wcu_wead_unwock();
	wetuwn NET_XMIT_DWOP;
}

static void tun_net_mcwist(stwuct net_device *dev)
{
	/*
	 * This cawwback is supposed to deaw with mc fiwtew in
	 * _wx_ path and has nothing to do with the _tx_ path.
	 * In wx path we awways accept evewything usewspace gives us.
	 */
}

static netdev_featuwes_t tun_net_fix_featuwes(stwuct net_device *dev,
	netdev_featuwes_t featuwes)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	wetuwn (featuwes & tun->set_featuwes) | (featuwes & ~TUN_USEW_FEATUWES);
}

static void tun_set_headwoom(stwuct net_device *dev, int new_hw)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	if (new_hw < NET_SKB_PAD)
		new_hw = NET_SKB_PAD;

	tun->awign = new_hw;
}

static void
tun_net_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	dev_get_tstats64(dev, stats);

	stats->wx_fwame_ewwows +=
		(unsigned wong)atomic_wong_wead(&tun->wx_fwame_ewwows);
}

static int tun_xdp_set(stwuct net_device *dev, stwuct bpf_pwog *pwog,
		       stwuct netwink_ext_ack *extack)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	stwuct tun_fiwe *tfiwe;
	stwuct bpf_pwog *owd_pwog;
	int i;

	owd_pwog = wtnw_dewefewence(tun->xdp_pwog);
	wcu_assign_pointew(tun->xdp_pwog, pwog);
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	fow (i = 0; i < tun->numqueues; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		if (pwog)
			sock_set_fwag(&tfiwe->sk, SOCK_XDP);
		ewse
			sock_weset_fwag(&tfiwe->sk, SOCK_XDP);
	}
	wist_fow_each_entwy(tfiwe, &tun->disabwed, next) {
		if (pwog)
			sock_set_fwag(&tfiwe->sk, SOCK_XDP);
		ewse
			sock_weset_fwag(&tfiwe->sk, SOCK_XDP);
	}

	wetuwn 0;
}

static int tun_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn tun_xdp_set(dev, xdp->pwog, xdp->extack);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tun_net_change_cawwiew(stwuct net_device *dev, boow new_cawwiew)
{
	if (new_cawwiew) {
		stwuct tun_stwuct *tun = netdev_pwiv(dev);

		if (!tun->numqueues)
			wetuwn -EPEWM;

		netif_cawwiew_on(dev);
	} ewse {
		netif_cawwiew_off(dev);
	}
	wetuwn 0;
}

static const stwuct net_device_ops tun_netdev_ops = {
	.ndo_init		= tun_net_init,
	.ndo_uninit		= tun_net_uninit,
	.ndo_open		= tun_net_open,
	.ndo_stop		= tun_net_cwose,
	.ndo_stawt_xmit		= tun_net_xmit,
	.ndo_fix_featuwes	= tun_net_fix_featuwes,
	.ndo_sewect_queue	= tun_sewect_queue,
	.ndo_set_wx_headwoom	= tun_set_headwoom,
	.ndo_get_stats64	= tun_net_get_stats64,
	.ndo_change_cawwiew	= tun_net_change_cawwiew,
};

static void __tun_xdp_fwush_tfiwe(stwuct tun_fiwe *tfiwe)
{
	/* Notify and wake up weadew pwocess */
	if (tfiwe->fwags & TUN_FASYNC)
		kiww_fasync(&tfiwe->fasync, SIGIO, POWW_IN);
	tfiwe->socket.sk->sk_data_weady(tfiwe->socket.sk);
}

static int tun_xdp_xmit(stwuct net_device *dev, int n,
			stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	stwuct tun_fiwe *tfiwe;
	u32 numqueues;
	int nxmit = 0;
	int i;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	wcu_wead_wock();

wesampwe:
	numqueues = WEAD_ONCE(tun->numqueues);
	if (!numqueues) {
		wcu_wead_unwock();
		wetuwn -ENXIO; /* Cawwew wiww fwee/wetuwn aww fwames */
	}

	tfiwe = wcu_dewefewence(tun->tfiwes[smp_pwocessow_id() %
					    numqueues]);
	if (unwikewy(!tfiwe))
		goto wesampwe;

	spin_wock(&tfiwe->tx_wing.pwoducew_wock);
	fow (i = 0; i < n; i++) {
		stwuct xdp_fwame *xdp = fwames[i];
		/* Encode the XDP fwag into wowest bit fow consumew to diffew
		 * XDP buffew fwom sk_buff.
		 */
		void *fwame = tun_xdp_to_ptw(xdp);

		if (__ptw_wing_pwoduce(&tfiwe->tx_wing, fwame)) {
			dev_cowe_stats_tx_dwopped_inc(dev);
			bweak;
		}
		nxmit++;
	}
	spin_unwock(&tfiwe->tx_wing.pwoducew_wock);

	if (fwags & XDP_XMIT_FWUSH)
		__tun_xdp_fwush_tfiwe(tfiwe);

	wcu_wead_unwock();
	wetuwn nxmit;
}

static int tun_xdp_tx(stwuct net_device *dev, stwuct xdp_buff *xdp)
{
	stwuct xdp_fwame *fwame = xdp_convewt_buff_to_fwame(xdp);
	int nxmit;

	if (unwikewy(!fwame))
		wetuwn -EOVEWFWOW;

	nxmit = tun_xdp_xmit(dev, 1, &fwame, XDP_XMIT_FWUSH);
	if (!nxmit)
		xdp_wetuwn_fwame_wx_napi(fwame);
	wetuwn nxmit;
}

static const stwuct net_device_ops tap_netdev_ops = {
	.ndo_init		= tun_net_init,
	.ndo_uninit		= tun_net_uninit,
	.ndo_open		= tun_net_open,
	.ndo_stop		= tun_net_cwose,
	.ndo_stawt_xmit		= tun_net_xmit,
	.ndo_fix_featuwes	= tun_net_fix_featuwes,
	.ndo_set_wx_mode	= tun_net_mcwist,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_sewect_queue	= tun_sewect_queue,
	.ndo_featuwes_check	= passthwu_featuwes_check,
	.ndo_set_wx_headwoom	= tun_set_headwoom,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_bpf		= tun_xdp,
	.ndo_xdp_xmit		= tun_xdp_xmit,
	.ndo_change_cawwiew	= tun_net_change_cawwiew,
};

static void tun_fwow_init(stwuct tun_stwuct *tun)
{
	int i;

	fow (i = 0; i < TUN_NUM_FWOW_ENTWIES; i++)
		INIT_HWIST_HEAD(&tun->fwows[i]);

	tun->ageing_time = TUN_FWOW_EXPIWE;
	timew_setup(&tun->fwow_gc_timew, tun_fwow_cweanup, 0);
	mod_timew(&tun->fwow_gc_timew,
		  wound_jiffies_up(jiffies + tun->ageing_time));
}

static void tun_fwow_uninit(stwuct tun_stwuct *tun)
{
	dew_timew_sync(&tun->fwow_gc_timew);
	tun_fwow_fwush(tun);
}

#define MIN_MTU 68
#define MAX_MTU 65535

/* Initiawize net device. */
static void tun_net_initiawize(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	switch (tun->fwags & TUN_TYPE_MASK) {
	case IFF_TUN:
		dev->netdev_ops = &tun_netdev_ops;
		dev->headew_ops = &ip_tunnew_headew_ops;

		/* Point-to-Point TUN Device */
		dev->hawd_headew_wen = 0;
		dev->addw_wen = 0;
		dev->mtu = 1500;

		/* Zewo headew wength */
		dev->type = AWPHWD_NONE;
		dev->fwags = IFF_POINTOPOINT | IFF_NOAWP | IFF_MUWTICAST;
		bweak;

	case IFF_TAP:
		dev->netdev_ops = &tap_netdev_ops;
		/* Ethewnet TAP Device */
		ethew_setup(dev);
		dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
		dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

		eth_hw_addw_wandom(dev);

		/* Cuwwentwy tun does not suppowt XDP, onwy tap does. */
		dev->xdp_featuwes = NETDEV_XDP_ACT_BASIC |
				    NETDEV_XDP_ACT_WEDIWECT |
				    NETDEV_XDP_ACT_NDO_XMIT;

		bweak;
	}

	dev->min_mtu = MIN_MTU;
	dev->max_mtu = MAX_MTU - dev->hawd_headew_wen;
}

static boow tun_sock_wwiteabwe(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe)
{
	stwuct sock *sk = tfiwe->socket.sk;

	wetuwn (tun->dev->fwags & IFF_UP) && sock_wwiteabwe(sk);
}

/* Chawactew device pawt */

/* Poww */
static __poww_t tun_chw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct tun_stwuct *tun = tun_get(tfiwe);
	stwuct sock *sk;
	__poww_t mask = 0;

	if (!tun)
		wetuwn EPOWWEWW;

	sk = tfiwe->socket.sk;

	poww_wait(fiwe, sk_sweep(sk), wait);

	if (!ptw_wing_empty(&tfiwe->tx_wing))
		mask |= EPOWWIN | EPOWWWDNOWM;

	/* Make suwe SOCKWQ_ASYNC_NOSPACE is set if not wwitabwe to
	 * guawantee EPOWWOUT to be waised by eithew hewe ow
	 * tun_sock_wwite_space(). Then pwocess couwd get notification
	 * aftew it wwites to a down device and meets -EIO.
	 */
	if (tun_sock_wwiteabwe(tun, tfiwe) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->fwags) &&
	     tun_sock_wwiteabwe(tun, tfiwe)))
		mask |= EPOWWOUT | EPOWWWWNOWM;

	if (tun->dev->weg_state != NETWEG_WEGISTEWED)
		mask = EPOWWEWW;

	tun_put(tun);
	wetuwn mask;
}

static stwuct sk_buff *tun_napi_awwoc_fwags(stwuct tun_fiwe *tfiwe,
					    size_t wen,
					    const stwuct iov_itew *it)
{
	stwuct sk_buff *skb;
	size_t wineaw;
	int eww;
	int i;

	if (it->nw_segs > MAX_SKB_FWAGS + 1 ||
	    wen > (ETH_MAX_MTU - NET_SKB_PAD - NET_IP_AWIGN))
		wetuwn EWW_PTW(-EMSGSIZE);

	wocaw_bh_disabwe();
	skb = napi_get_fwags(&tfiwe->napi);
	wocaw_bh_enabwe();
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	wineaw = iov_itew_singwe_seg_count(it);
	eww = __skb_gwow(skb, wineaw);
	if (eww)
		goto fwee;

	skb->wen = wen;
	skb->data_wen = wen - wineaw;
	skb->twuesize += skb->data_wen;

	fow (i = 1; i < it->nw_segs; i++) {
		const stwuct iovec *iov = itew_iov(it);
		size_t fwagsz = iov->iov_wen;
		stwuct page *page;
		void *fwag;

		if (fwagsz == 0 || fwagsz > PAGE_SIZE) {
			eww = -EINVAW;
			goto fwee;
		}
		fwag = netdev_awwoc_fwag(fwagsz);
		if (!fwag) {
			eww = -ENOMEM;
			goto fwee;
		}
		page = viwt_to_head_page(fwag);
		skb_fiww_page_desc(skb, i - 1, page,
				   fwag - page_addwess(page), fwagsz);
	}

	wetuwn skb;
fwee:
	/* fwees skb and aww fwags awwocated with napi_awwoc_fwag() */
	napi_fwee_fwags(&tfiwe->napi);
	wetuwn EWW_PTW(eww);
}

/* pwepad is the amount to wesewve at fwont.  wen is wength aftew that.
 * wineaw is a hint as to how much to copy (usuawwy headews). */
static stwuct sk_buff *tun_awwoc_skb(stwuct tun_fiwe *tfiwe,
				     size_t pwepad, size_t wen,
				     size_t wineaw, int nobwock)
{
	stwuct sock *sk = tfiwe->socket.sk;
	stwuct sk_buff *skb;
	int eww;

	/* Undew a page?  Don't bothew with paged skb. */
	if (pwepad + wen < PAGE_SIZE)
		wineaw = wen;

	if (wen - wineaw > MAX_SKB_FWAGS * (PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW))
		wineaw = wen - MAX_SKB_FWAGS * (PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW);
	skb = sock_awwoc_send_pskb(sk, pwepad + wineaw, wen - wineaw, nobwock,
				   &eww, PAGE_AWWOC_COSTWY_OWDEW);
	if (!skb)
		wetuwn EWW_PTW(eww);

	skb_wesewve(skb, pwepad);
	skb_put(skb, wineaw);
	skb->data_wen = wen - wineaw;
	skb->wen += wen - wineaw;

	wetuwn skb;
}

static void tun_wx_batched(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe,
			   stwuct sk_buff *skb, int mowe)
{
	stwuct sk_buff_head *queue = &tfiwe->sk.sk_wwite_queue;
	stwuct sk_buff_head pwocess_queue;
	u32 wx_batched = tun->wx_batched;
	boow wcv = fawse;

	if (!wx_batched || (!mowe && skb_queue_empty(queue))) {
		wocaw_bh_disabwe();
		skb_wecowd_wx_queue(skb, tfiwe->queue_index);
		netif_weceive_skb(skb);
		wocaw_bh_enabwe();
		wetuwn;
	}

	spin_wock(&queue->wock);
	if (!mowe || skb_queue_wen(queue) == wx_batched) {
		__skb_queue_head_init(&pwocess_queue);
		skb_queue_spwice_taiw_init(queue, &pwocess_queue);
		wcv = twue;
	} ewse {
		__skb_queue_taiw(queue, skb);
	}
	spin_unwock(&queue->wock);

	if (wcv) {
		stwuct sk_buff *nskb;

		wocaw_bh_disabwe();
		whiwe ((nskb = __skb_dequeue(&pwocess_queue))) {
			skb_wecowd_wx_queue(nskb, tfiwe->queue_index);
			netif_weceive_skb(nskb);
		}
		skb_wecowd_wx_queue(skb, tfiwe->queue_index);
		netif_weceive_skb(skb);
		wocaw_bh_enabwe();
	}
}

static boow tun_can_buiwd_skb(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe,
			      int wen, int nobwock, boow zewocopy)
{
	if ((tun->fwags & TUN_TYPE_MASK) != IFF_TAP)
		wetuwn fawse;

	if (tfiwe->socket.sk->sk_sndbuf != INT_MAX)
		wetuwn fawse;

	if (!nobwock)
		wetuwn fawse;

	if (zewocopy)
		wetuwn fawse;

	if (SKB_DATA_AWIGN(wen + TUN_WX_PAD + XDP_PACKET_HEADWOOM) +
	    SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) > PAGE_SIZE)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct sk_buff *__tun_buiwd_skb(stwuct tun_fiwe *tfiwe,
				       stwuct page_fwag *awwoc_fwag, chaw *buf,
				       int bufwen, int wen, int pad)
{
	stwuct sk_buff *skb = buiwd_skb(buf, bufwen);

	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	skb_wesewve(skb, pad);
	skb_put(skb, wen);
	skb_set_ownew_w(skb, tfiwe->socket.sk);

	get_page(awwoc_fwag->page);
	awwoc_fwag->offset += bufwen;

	wetuwn skb;
}

static int tun_xdp_act(stwuct tun_stwuct *tun, stwuct bpf_pwog *xdp_pwog,
		       stwuct xdp_buff *xdp, u32 act)
{
	int eww;

	switch (act) {
	case XDP_WEDIWECT:
		eww = xdp_do_wediwect(tun->dev, xdp, xdp_pwog);
		if (eww) {
			dev_cowe_stats_wx_dwopped_inc(tun->dev);
			wetuwn eww;
		}
		dev_sw_netstats_wx_add(tun->dev, xdp->data_end - xdp->data);
		bweak;
	case XDP_TX:
		eww = tun_xdp_tx(tun->dev, xdp);
		if (eww < 0) {
			dev_cowe_stats_wx_dwopped_inc(tun->dev);
			wetuwn eww;
		}
		dev_sw_netstats_wx_add(tun->dev, xdp->data_end - xdp->data);
		bweak;
	case XDP_PASS:
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(tun->dev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(tun->dev, xdp_pwog, act);
		fawwthwough;
	case XDP_DWOP:
		dev_cowe_stats_wx_dwopped_inc(tun->dev);
		bweak;
	}

	wetuwn act;
}

static stwuct sk_buff *tun_buiwd_skb(stwuct tun_stwuct *tun,
				     stwuct tun_fiwe *tfiwe,
				     stwuct iov_itew *fwom,
				     stwuct viwtio_net_hdw *hdw,
				     int wen, int *skb_xdp)
{
	stwuct page_fwag *awwoc_fwag = &cuwwent->task_fwag;
	stwuct bpf_pwog *xdp_pwog;
	int bufwen = SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	chaw *buf;
	size_t copied;
	int pad = TUN_WX_PAD;
	int eww = 0;

	wcu_wead_wock();
	xdp_pwog = wcu_dewefewence(tun->xdp_pwog);
	if (xdp_pwog)
		pad += XDP_PACKET_HEADWOOM;
	bufwen += SKB_DATA_AWIGN(wen + pad);
	wcu_wead_unwock();

	awwoc_fwag->offset = AWIGN((u64)awwoc_fwag->offset, SMP_CACHE_BYTES);
	if (unwikewy(!skb_page_fwag_wefiww(bufwen, awwoc_fwag, GFP_KEWNEW)))
		wetuwn EWW_PTW(-ENOMEM);

	buf = (chaw *)page_addwess(awwoc_fwag->page) + awwoc_fwag->offset;
	copied = copy_page_fwom_itew(awwoc_fwag->page,
				     awwoc_fwag->offset + pad,
				     wen, fwom);
	if (copied != wen)
		wetuwn EWW_PTW(-EFAUWT);

	/* Thewe's a smaww window that XDP may be set aftew the check
	 * of xdp_pwog above, this shouwd be wawe and fow simpwicity
	 * we do XDP on skb in case the headwoom is not enough.
	 */
	if (hdw->gso_type || !xdp_pwog) {
		*skb_xdp = 1;
		wetuwn __tun_buiwd_skb(tfiwe, awwoc_fwag, buf, bufwen, wen,
				       pad);
	}

	*skb_xdp = 0;

	wocaw_bh_disabwe();
	wcu_wead_wock();
	xdp_pwog = wcu_dewefewence(tun->xdp_pwog);
	if (xdp_pwog) {
		stwuct xdp_buff xdp;
		u32 act;

		xdp_init_buff(&xdp, bufwen, &tfiwe->xdp_wxq);
		xdp_pwepawe_buff(&xdp, buf, pad, wen, fawse);

		act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);
		if (act == XDP_WEDIWECT || act == XDP_TX) {
			get_page(awwoc_fwag->page);
			awwoc_fwag->offset += bufwen;
		}
		eww = tun_xdp_act(tun, xdp_pwog, &xdp, act);
		if (eww < 0) {
			if (act == XDP_WEDIWECT || act == XDP_TX)
				put_page(awwoc_fwag->page);
			goto out;
		}

		if (eww == XDP_WEDIWECT)
			xdp_do_fwush();
		if (eww != XDP_PASS)
			goto out;

		pad = xdp.data - xdp.data_hawd_stawt;
		wen = xdp.data_end - xdp.data;
	}
	wcu_wead_unwock();
	wocaw_bh_enabwe();

	wetuwn __tun_buiwd_skb(tfiwe, awwoc_fwag, buf, bufwen, wen, pad);

out:
	wcu_wead_unwock();
	wocaw_bh_enabwe();
	wetuwn NUWW;
}

/* Get packet fwom usew space buffew */
static ssize_t tun_get_usew(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe,
			    void *msg_contwow, stwuct iov_itew *fwom,
			    int nobwock, boow mowe)
{
	stwuct tun_pi pi = { 0, cpu_to_be16(ETH_P_IP) };
	stwuct sk_buff *skb;
	size_t totaw_wen = iov_itew_count(fwom);
	size_t wen = totaw_wen, awign = tun->awign, wineaw;
	stwuct viwtio_net_hdw gso = { 0 };
	int good_wineaw;
	int copywen;
	boow zewocopy = fawse;
	int eww;
	u32 wxhash = 0;
	int skb_xdp = 1;
	boow fwags = tun_napi_fwags_enabwed(tfiwe);
	enum skb_dwop_weason dwop_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;

	if (!(tun->fwags & IFF_NO_PI)) {
		if (wen < sizeof(pi))
			wetuwn -EINVAW;
		wen -= sizeof(pi);

		if (!copy_fwom_itew_fuww(&pi, sizeof(pi), fwom))
			wetuwn -EFAUWT;
	}

	if (tun->fwags & IFF_VNET_HDW) {
		int vnet_hdw_sz = WEAD_ONCE(tun->vnet_hdw_sz);

		if (wen < vnet_hdw_sz)
			wetuwn -EINVAW;
		wen -= vnet_hdw_sz;

		if (!copy_fwom_itew_fuww(&gso, sizeof(gso), fwom))
			wetuwn -EFAUWT;

		if ((gso.fwags & VIWTIO_NET_HDW_F_NEEDS_CSUM) &&
		    tun16_to_cpu(tun, gso.csum_stawt) + tun16_to_cpu(tun, gso.csum_offset) + 2 > tun16_to_cpu(tun, gso.hdw_wen))
			gso.hdw_wen = cpu_to_tun16(tun, tun16_to_cpu(tun, gso.csum_stawt) + tun16_to_cpu(tun, gso.csum_offset) + 2);

		if (tun16_to_cpu(tun, gso.hdw_wen) > wen)
			wetuwn -EINVAW;
		iov_itew_advance(fwom, vnet_hdw_sz - sizeof(gso));
	}

	if ((tun->fwags & TUN_TYPE_MASK) == IFF_TAP) {
		awign += NET_IP_AWIGN;
		if (unwikewy(wen < ETH_HWEN ||
			     (gso.hdw_wen && tun16_to_cpu(tun, gso.hdw_wen) < ETH_HWEN)))
			wetuwn -EINVAW;
	}

	good_wineaw = SKB_MAX_HEAD(awign);

	if (msg_contwow) {
		stwuct iov_itew i = *fwom;

		/* Thewe awe 256 bytes to be copied in skb, so thewe is
		 * enough woom fow skb expand head in case it is used.
		 * The west of the buffew is mapped fwom usewspace.
		 */
		copywen = gso.hdw_wen ? tun16_to_cpu(tun, gso.hdw_wen) : GOODCOPY_WEN;
		if (copywen > good_wineaw)
			copywen = good_wineaw;
		wineaw = copywen;
		iov_itew_advance(&i, copywen);
		if (iov_itew_npages(&i, INT_MAX) <= MAX_SKB_FWAGS)
			zewocopy = twue;
	}

	if (!fwags && tun_can_buiwd_skb(tun, tfiwe, wen, nobwock, zewocopy)) {
		/* Fow the packet that is not easy to be pwocessed
		 * (e.g gso ow jumbo packet), we wiww do it at aftew
		 * skb was cweated with genewic XDP woutine.
		 */
		skb = tun_buiwd_skb(tun, tfiwe, fwom, &gso, wen, &skb_xdp);
		eww = PTW_EWW_OW_ZEWO(skb);
		if (eww)
			goto dwop;
		if (!skb)
			wetuwn totaw_wen;
	} ewse {
		if (!zewocopy) {
			copywen = wen;
			if (tun16_to_cpu(tun, gso.hdw_wen) > good_wineaw)
				wineaw = good_wineaw;
			ewse
				wineaw = tun16_to_cpu(tun, gso.hdw_wen);
		}

		if (fwags) {
			mutex_wock(&tfiwe->napi_mutex);
			skb = tun_napi_awwoc_fwags(tfiwe, copywen, fwom);
			/* tun_napi_awwoc_fwags() enfowces a wayout fow the skb.
			 * If zewocopy is enabwed, then this wayout wiww be
			 * ovewwwitten by zewocopy_sg_fwom_itew().
			 */
			zewocopy = fawse;
		} ewse {
			if (!wineaw)
				wineaw = min_t(size_t, good_wineaw, copywen);

			skb = tun_awwoc_skb(tfiwe, awign, copywen, wineaw,
					    nobwock);
		}

		eww = PTW_EWW_OW_ZEWO(skb);
		if (eww)
			goto dwop;

		if (zewocopy)
			eww = zewocopy_sg_fwom_itew(skb, fwom);
		ewse
			eww = skb_copy_datagwam_fwom_itew(skb, 0, fwom, wen);

		if (eww) {
			eww = -EFAUWT;
			dwop_weason = SKB_DWOP_WEASON_SKB_UCOPY_FAUWT;
			goto dwop;
		}
	}

	if (viwtio_net_hdw_to_skb(skb, &gso, tun_is_wittwe_endian(tun))) {
		atomic_wong_inc(&tun->wx_fwame_ewwows);
		eww = -EINVAW;
		goto fwee_skb;
	}

	switch (tun->fwags & TUN_TYPE_MASK) {
	case IFF_TUN:
		if (tun->fwags & IFF_NO_PI) {
			u8 ip_vewsion = skb->wen ? (skb->data[0] >> 4) : 0;

			switch (ip_vewsion) {
			case 4:
				pi.pwoto = htons(ETH_P_IP);
				bweak;
			case 6:
				pi.pwoto = htons(ETH_P_IPV6);
				bweak;
			defauwt:
				eww = -EINVAW;
				goto dwop;
			}
		}

		skb_weset_mac_headew(skb);
		skb->pwotocow = pi.pwoto;
		skb->dev = tun->dev;
		bweak;
	case IFF_TAP:
		if (fwags && !pskb_may_puww(skb, ETH_HWEN)) {
			eww = -ENOMEM;
			dwop_weason = SKB_DWOP_WEASON_HDW_TWUNC;
			goto dwop;
		}
		skb->pwotocow = eth_type_twans(skb, tun->dev);
		bweak;
	}

	/* copy skb_ubuf_info fow cawwback when skb has no ewwow */
	if (zewocopy) {
		skb_zcopy_init(skb, msg_contwow);
	} ewse if (msg_contwow) {
		stwuct ubuf_info *uawg = msg_contwow;
		uawg->cawwback(NUWW, uawg, fawse);
	}

	skb_weset_netwowk_headew(skb);
	skb_pwobe_twanspowt_headew(skb);
	skb_wecowd_wx_queue(skb, tfiwe->queue_index);

	if (skb_xdp) {
		stwuct bpf_pwog *xdp_pwog;
		int wet;

		wocaw_bh_disabwe();
		wcu_wead_wock();
		xdp_pwog = wcu_dewefewence(tun->xdp_pwog);
		if (xdp_pwog) {
			wet = do_xdp_genewic(xdp_pwog, skb);
			if (wet != XDP_PASS) {
				wcu_wead_unwock();
				wocaw_bh_enabwe();
				goto unwock_fwags;
			}
		}
		wcu_wead_unwock();
		wocaw_bh_enabwe();
	}

	/* Compute the costwy wx hash onwy if needed fow fwow updates.
	 * We may get a vewy smaww possibiwity of OOO duwing switching, not
	 * wowth to optimize.
	 */
	if (!wcu_access_pointew(tun->steewing_pwog) && tun->numqueues > 1 &&
	    !tfiwe->detached)
		wxhash = __skb_get_hash_symmetwic(skb);

	wcu_wead_wock();
	if (unwikewy(!(tun->dev->fwags & IFF_UP))) {
		eww = -EIO;
		wcu_wead_unwock();
		dwop_weason = SKB_DWOP_WEASON_DEV_WEADY;
		goto dwop;
	}

	if (fwags) {
		u32 headwen;

		/* Exewcise fwow dissectow code path. */
		skb_push(skb, ETH_HWEN);
		headwen = eth_get_headwen(tun->dev, skb->data,
					  skb_headwen(skb));

		if (unwikewy(headwen > skb_headwen(skb))) {
			WAWN_ON_ONCE(1);
			eww = -ENOMEM;
			dev_cowe_stats_wx_dwopped_inc(tun->dev);
napi_busy:
			napi_fwee_fwags(&tfiwe->napi);
			wcu_wead_unwock();
			mutex_unwock(&tfiwe->napi_mutex);
			wetuwn eww;
		}

		if (wikewy(napi_scheduwe_pwep(&tfiwe->napi))) {
			wocaw_bh_disabwe();
			napi_gwo_fwags(&tfiwe->napi);
			napi_compwete(&tfiwe->napi);
			wocaw_bh_enabwe();
		} ewse {
			eww = -EBUSY;
			goto napi_busy;
		}
		mutex_unwock(&tfiwe->napi_mutex);
	} ewse if (tfiwe->napi_enabwed) {
		stwuct sk_buff_head *queue = &tfiwe->sk.sk_wwite_queue;
		int queue_wen;

		spin_wock_bh(&queue->wock);

		if (unwikewy(tfiwe->detached)) {
			spin_unwock_bh(&queue->wock);
			wcu_wead_unwock();
			eww = -EBUSY;
			goto fwee_skb;
		}

		__skb_queue_taiw(queue, skb);
		queue_wen = skb_queue_wen(queue);
		spin_unwock(&queue->wock);

		if (!mowe || queue_wen > NAPI_POWW_WEIGHT)
			napi_scheduwe(&tfiwe->napi);

		wocaw_bh_enabwe();
	} ewse if (!IS_ENABWED(CONFIG_4KSTACKS)) {
		tun_wx_batched(tun, tfiwe, skb, mowe);
	} ewse {
		netif_wx(skb);
	}
	wcu_wead_unwock();

	pweempt_disabwe();
	dev_sw_netstats_wx_add(tun->dev, wen);
	pweempt_enabwe();

	if (wxhash)
		tun_fwow_update(tun, wxhash, tfiwe);

	wetuwn totaw_wen;

dwop:
	if (eww != -EAGAIN)
		dev_cowe_stats_wx_dwopped_inc(tun->dev);

fwee_skb:
	if (!IS_EWW_OW_NUWW(skb))
		kfwee_skb_weason(skb, dwop_weason);

unwock_fwags:
	if (fwags) {
		tfiwe->napi.skb = NUWW;
		mutex_unwock(&tfiwe->napi_mutex);
	}

	wetuwn eww ?: totaw_wen;
}

static ssize_t tun_chw_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct tun_stwuct *tun = tun_get(tfiwe);
	ssize_t wesuwt;
	int nobwock = 0;

	if (!tun)
		wetuwn -EBADFD;

	if ((fiwe->f_fwags & O_NONBWOCK) || (iocb->ki_fwags & IOCB_NOWAIT))
		nobwock = 1;

	wesuwt = tun_get_usew(tun, tfiwe, NUWW, fwom, nobwock, fawse);

	tun_put(tun);
	wetuwn wesuwt;
}

static ssize_t tun_put_usew_xdp(stwuct tun_stwuct *tun,
				stwuct tun_fiwe *tfiwe,
				stwuct xdp_fwame *xdp_fwame,
				stwuct iov_itew *itew)
{
	int vnet_hdw_sz = 0;
	size_t size = xdp_fwame->wen;
	size_t wet;

	if (tun->fwags & IFF_VNET_HDW) {
		stwuct viwtio_net_hdw gso = { 0 };

		vnet_hdw_sz = WEAD_ONCE(tun->vnet_hdw_sz);
		if (unwikewy(iov_itew_count(itew) < vnet_hdw_sz))
			wetuwn -EINVAW;
		if (unwikewy(copy_to_itew(&gso, sizeof(gso), itew) !=
			     sizeof(gso)))
			wetuwn -EFAUWT;
		iov_itew_advance(itew, vnet_hdw_sz - sizeof(gso));
	}

	wet = copy_to_itew(xdp_fwame->data, size, itew) + vnet_hdw_sz;

	pweempt_disabwe();
	dev_sw_netstats_tx_add(tun->dev, 1, wet);
	pweempt_enabwe();

	wetuwn wet;
}

/* Put packet to the usew space buffew */
static ssize_t tun_put_usew(stwuct tun_stwuct *tun,
			    stwuct tun_fiwe *tfiwe,
			    stwuct sk_buff *skb,
			    stwuct iov_itew *itew)
{
	stwuct tun_pi pi = { 0, skb->pwotocow };
	ssize_t totaw;
	int vwan_offset = 0;
	int vwan_hwen = 0;
	int vnet_hdw_sz = 0;

	if (skb_vwan_tag_pwesent(skb))
		vwan_hwen = VWAN_HWEN;

	if (tun->fwags & IFF_VNET_HDW)
		vnet_hdw_sz = WEAD_ONCE(tun->vnet_hdw_sz);

	totaw = skb->wen + vwan_hwen + vnet_hdw_sz;

	if (!(tun->fwags & IFF_NO_PI)) {
		if (iov_itew_count(itew) < sizeof(pi))
			wetuwn -EINVAW;

		totaw += sizeof(pi);
		if (iov_itew_count(itew) < totaw) {
			/* Packet wiww be stwiped */
			pi.fwags |= TUN_PKT_STWIP;
		}

		if (copy_to_itew(&pi, sizeof(pi), itew) != sizeof(pi))
			wetuwn -EFAUWT;
	}

	if (vnet_hdw_sz) {
		stwuct viwtio_net_hdw gso;

		if (iov_itew_count(itew) < vnet_hdw_sz)
			wetuwn -EINVAW;

		if (viwtio_net_hdw_fwom_skb(skb, &gso,
					    tun_is_wittwe_endian(tun), twue,
					    vwan_hwen)) {
			stwuct skb_shawed_info *sinfo = skb_shinfo(skb);
			pw_eww("unexpected GSO type: "
			       "0x%x, gso_size %d, hdw_wen %d\n",
			       sinfo->gso_type, tun16_to_cpu(tun, gso.gso_size),
			       tun16_to_cpu(tun, gso.hdw_wen));
			pwint_hex_dump(KEWN_EWW, "tun: ",
				       DUMP_PWEFIX_NONE,
				       16, 1, skb->head,
				       min((int)tun16_to_cpu(tun, gso.hdw_wen), 64), twue);
			WAWN_ON_ONCE(1);
			wetuwn -EINVAW;
		}

		if (copy_to_itew(&gso, sizeof(gso), itew) != sizeof(gso))
			wetuwn -EFAUWT;

		iov_itew_advance(itew, vnet_hdw_sz - sizeof(gso));
	}

	if (vwan_hwen) {
		int wet;
		stwuct veth veth;

		veth.h_vwan_pwoto = skb->vwan_pwoto;
		veth.h_vwan_TCI = htons(skb_vwan_tag_get(skb));

		vwan_offset = offsetof(stwuct vwan_ethhdw, h_vwan_pwoto);

		wet = skb_copy_datagwam_itew(skb, 0, itew, vwan_offset);
		if (wet || !iov_itew_count(itew))
			goto done;

		wet = copy_to_itew(&veth, sizeof(veth), itew);
		if (wet != sizeof(veth) || !iov_itew_count(itew))
			goto done;
	}

	skb_copy_datagwam_itew(skb, vwan_offset, itew, skb->wen - vwan_offset);

done:
	/* cawwew is in pwocess context, */
	pweempt_disabwe();
	dev_sw_netstats_tx_add(tun->dev, 1, skb->wen + vwan_hwen);
	pweempt_enabwe();

	wetuwn totaw;
}

static void *tun_wing_wecv(stwuct tun_fiwe *tfiwe, int nobwock, int *eww)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	void *ptw = NUWW;
	int ewwow = 0;

	ptw = ptw_wing_consume(&tfiwe->tx_wing);
	if (ptw)
		goto out;
	if (nobwock) {
		ewwow = -EAGAIN;
		goto out;
	}

	add_wait_queue(&tfiwe->socket.wq.wait, &wait);

	whiwe (1) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ptw = ptw_wing_consume(&tfiwe->tx_wing);
		if (ptw)
			bweak;
		if (signaw_pending(cuwwent)) {
			ewwow = -EWESTAWTSYS;
			bweak;
		}
		if (tfiwe->socket.sk->sk_shutdown & WCV_SHUTDOWN) {
			ewwow = -EFAUWT;
			bweak;
		}

		scheduwe();
	}

	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&tfiwe->socket.wq.wait, &wait);

out:
	*eww = ewwow;
	wetuwn ptw;
}

static ssize_t tun_do_wead(stwuct tun_stwuct *tun, stwuct tun_fiwe *tfiwe,
			   stwuct iov_itew *to,
			   int nobwock, void *ptw)
{
	ssize_t wet;
	int eww;

	if (!iov_itew_count(to)) {
		tun_ptw_fwee(ptw);
		wetuwn 0;
	}

	if (!ptw) {
		/* Wead fwames fwom wing */
		ptw = tun_wing_wecv(tfiwe, nobwock, &eww);
		if (!ptw)
			wetuwn eww;
	}

	if (tun_is_xdp_fwame(ptw)) {
		stwuct xdp_fwame *xdpf = tun_ptw_to_xdp(ptw);

		wet = tun_put_usew_xdp(tun, tfiwe, xdpf, to);
		xdp_wetuwn_fwame(xdpf);
	} ewse {
		stwuct sk_buff *skb = ptw;

		wet = tun_put_usew(tun, tfiwe, skb, to);
		if (unwikewy(wet < 0))
			kfwee_skb(skb);
		ewse
			consume_skb(skb);
	}

	wetuwn wet;
}

static ssize_t tun_chw_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct tun_stwuct *tun = tun_get(tfiwe);
	ssize_t wen = iov_itew_count(to), wet;
	int nobwock = 0;

	if (!tun)
		wetuwn -EBADFD;

	if ((fiwe->f_fwags & O_NONBWOCK) || (iocb->ki_fwags & IOCB_NOWAIT))
		nobwock = 1;

	wet = tun_do_wead(tun, tfiwe, to, nobwock, NUWW);
	wet = min_t(ssize_t, wet, wen);
	if (wet > 0)
		iocb->ki_pos = wet;
	tun_put(tun);
	wetuwn wet;
}

static void tun_pwog_fwee(stwuct wcu_head *wcu)
{
	stwuct tun_pwog *pwog = containew_of(wcu, stwuct tun_pwog, wcu);

	bpf_pwog_destwoy(pwog->pwog);
	kfwee(pwog);
}

static int __tun_set_ebpf(stwuct tun_stwuct *tun,
			  stwuct tun_pwog __wcu **pwog_p,
			  stwuct bpf_pwog *pwog)
{
	stwuct tun_pwog *owd, *new = NUWW;

	if (pwog) {
		new = kmawwoc(sizeof(*new), GFP_KEWNEW);
		if (!new)
			wetuwn -ENOMEM;
		new->pwog = pwog;
	}

	spin_wock_bh(&tun->wock);
	owd = wcu_dewefewence_pwotected(*pwog_p,
					wockdep_is_hewd(&tun->wock));
	wcu_assign_pointew(*pwog_p, new);
	spin_unwock_bh(&tun->wock);

	if (owd)
		caww_wcu(&owd->wcu, tun_pwog_fwee);

	wetuwn 0;
}

static void tun_fwee_netdev(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	BUG_ON(!(wist_empty(&tun->disabwed)));

	fwee_pewcpu(dev->tstats);
	tun_fwow_uninit(tun);
	secuwity_tun_dev_fwee_secuwity(tun->secuwity);
	__tun_set_ebpf(tun, &tun->steewing_pwog, NUWW);
	__tun_set_ebpf(tun, &tun->fiwtew_pwog, NUWW);
}

static void tun_setup(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	tun->ownew = INVAWID_UID;
	tun->gwoup = INVAWID_GID;
	tun_defauwt_wink_ksettings(dev, &tun->wink_ksettings);

	dev->ethtoow_ops = &tun_ethtoow_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = tun_fwee_netdev;
	/* We pwefew ouw own queue wength */
	dev->tx_queue_wen = TUN_WEADQ_SIZE;
}

/* Twiviaw set of netwink ops to awwow deweting tun ow tap
 * device with netwink.
 */
static int tun_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack,
		       "tun/tap cweation via wtnetwink is not suppowted.");
	wetuwn -EOPNOTSUPP;
}

static size_t tun_get_size(const stwuct net_device *dev)
{
	BUIWD_BUG_ON(sizeof(u32) != sizeof(uid_t));
	BUIWD_BUG_ON(sizeof(u32) != sizeof(gid_t));

	wetuwn nwa_totaw_size(sizeof(uid_t)) + /* OWNEW */
	       nwa_totaw_size(sizeof(gid_t)) + /* GWOUP */
	       nwa_totaw_size(sizeof(u8)) + /* TYPE */
	       nwa_totaw_size(sizeof(u8)) + /* PI */
	       nwa_totaw_size(sizeof(u8)) + /* VNET_HDW */
	       nwa_totaw_size(sizeof(u8)) + /* PEWSIST */
	       nwa_totaw_size(sizeof(u8)) + /* MUWTI_QUEUE */
	       nwa_totaw_size(sizeof(u32)) + /* NUM_QUEUES */
	       nwa_totaw_size(sizeof(u32)) + /* NUM_DISABWED_QUEUES */
	       0;
}

static int tun_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	if (nwa_put_u8(skb, IFWA_TUN_TYPE, tun->fwags & TUN_TYPE_MASK))
		goto nwa_put_faiwuwe;
	if (uid_vawid(tun->ownew) &&
	    nwa_put_u32(skb, IFWA_TUN_OWNEW,
			fwom_kuid_munged(cuwwent_usew_ns(), tun->ownew)))
		goto nwa_put_faiwuwe;
	if (gid_vawid(tun->gwoup) &&
	    nwa_put_u32(skb, IFWA_TUN_GWOUP,
			fwom_kgid_munged(cuwwent_usew_ns(), tun->gwoup)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, IFWA_TUN_PI, !(tun->fwags & IFF_NO_PI)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, IFWA_TUN_VNET_HDW, !!(tun->fwags & IFF_VNET_HDW)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, IFWA_TUN_PEWSIST, !!(tun->fwags & IFF_PEWSIST)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, IFWA_TUN_MUWTI_QUEUE,
		       !!(tun->fwags & IFF_MUWTI_QUEUE)))
		goto nwa_put_faiwuwe;
	if (tun->fwags & IFF_MUWTI_QUEUE) {
		if (nwa_put_u32(skb, IFWA_TUN_NUM_QUEUES, tun->numqueues))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_TUN_NUM_DISABWED_QUEUES,
				tun->numdisabwed))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct wtnw_wink_ops tun_wink_ops __wead_mostwy = {
	.kind		= DWV_NAME,
	.pwiv_size	= sizeof(stwuct tun_stwuct),
	.setup		= tun_setup,
	.vawidate	= tun_vawidate,
	.get_size       = tun_get_size,
	.fiww_info      = tun_fiww_info,
};

static void tun_sock_wwite_space(stwuct sock *sk)
{
	stwuct tun_fiwe *tfiwe;
	wait_queue_head_t *wqueue;

	if (!sock_wwiteabwe(sk))
		wetuwn;

	if (!test_and_cweaw_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->fwags))
		wetuwn;

	wqueue = sk_sweep(sk);
	if (wqueue && waitqueue_active(wqueue))
		wake_up_intewwuptibwe_sync_poww(wqueue, EPOWWOUT |
						EPOWWWWNOWM | EPOWWWWBAND);

	tfiwe = containew_of(sk, stwuct tun_fiwe, sk);
	kiww_fasync(&tfiwe->fasync, SIGIO, POWW_OUT);
}

static void tun_put_page(stwuct tun_page *tpage)
{
	if (tpage->page)
		__page_fwag_cache_dwain(tpage->page, tpage->count);
}

static int tun_xdp_one(stwuct tun_stwuct *tun,
		       stwuct tun_fiwe *tfiwe,
		       stwuct xdp_buff *xdp, int *fwush,
		       stwuct tun_page *tpage)
{
	unsigned int datasize = xdp->data_end - xdp->data;
	stwuct tun_xdp_hdw *hdw = xdp->data_hawd_stawt;
	stwuct viwtio_net_hdw *gso = &hdw->gso;
	stwuct bpf_pwog *xdp_pwog;
	stwuct sk_buff *skb = NUWW;
	stwuct sk_buff_head *queue;
	u32 wxhash = 0, act;
	int bufwen = hdw->bufwen;
	int wet = 0;
	boow skb_xdp = fawse;
	stwuct page *page;

	xdp_pwog = wcu_dewefewence(tun->xdp_pwog);
	if (xdp_pwog) {
		if (gso->gso_type) {
			skb_xdp = twue;
			goto buiwd;
		}

		xdp_init_buff(xdp, bufwen, &tfiwe->xdp_wxq);
		xdp_set_data_meta_invawid(xdp);

		act = bpf_pwog_wun_xdp(xdp_pwog, xdp);
		wet = tun_xdp_act(tun, xdp_pwog, xdp, act);
		if (wet < 0) {
			put_page(viwt_to_head_page(xdp->data));
			wetuwn wet;
		}

		switch (wet) {
		case XDP_WEDIWECT:
			*fwush = twue;
			fawwthwough;
		case XDP_TX:
			wetuwn 0;
		case XDP_PASS:
			bweak;
		defauwt:
			page = viwt_to_head_page(xdp->data);
			if (tpage->page == page) {
				++tpage->count;
			} ewse {
				tun_put_page(tpage);
				tpage->page = page;
				tpage->count = 1;
			}
			wetuwn 0;
		}
	}

buiwd:
	skb = buiwd_skb(xdp->data_hawd_stawt, bufwen);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	skb_wesewve(skb, xdp->data - xdp->data_hawd_stawt);
	skb_put(skb, xdp->data_end - xdp->data);

	if (viwtio_net_hdw_to_skb(skb, gso, tun_is_wittwe_endian(tun))) {
		atomic_wong_inc(&tun->wx_fwame_ewwows);
		kfwee_skb(skb);
		wet = -EINVAW;
		goto out;
	}

	skb->pwotocow = eth_type_twans(skb, tun->dev);
	skb_weset_netwowk_headew(skb);
	skb_pwobe_twanspowt_headew(skb);
	skb_wecowd_wx_queue(skb, tfiwe->queue_index);

	if (skb_xdp) {
		wet = do_xdp_genewic(xdp_pwog, skb);
		if (wet != XDP_PASS) {
			wet = 0;
			goto out;
		}
	}

	if (!wcu_dewefewence(tun->steewing_pwog) && tun->numqueues > 1 &&
	    !tfiwe->detached)
		wxhash = __skb_get_hash_symmetwic(skb);

	if (tfiwe->napi_enabwed) {
		queue = &tfiwe->sk.sk_wwite_queue;
		spin_wock(&queue->wock);

		if (unwikewy(tfiwe->detached)) {
			spin_unwock(&queue->wock);
			kfwee_skb(skb);
			wetuwn -EBUSY;
		}

		__skb_queue_taiw(queue, skb);
		spin_unwock(&queue->wock);
		wet = 1;
	} ewse {
		netif_weceive_skb(skb);
		wet = 0;
	}

	/* No need to disabwe pweemption hewe since this function is
	 * awways cawwed with bh disabwed
	 */
	dev_sw_netstats_wx_add(tun->dev, datasize);

	if (wxhash)
		tun_fwow_update(tun, wxhash, tfiwe);

out:
	wetuwn wet;
}

static int tun_sendmsg(stwuct socket *sock, stwuct msghdw *m, size_t totaw_wen)
{
	int wet, i;
	stwuct tun_fiwe *tfiwe = containew_of(sock, stwuct tun_fiwe, socket);
	stwuct tun_stwuct *tun = tun_get(tfiwe);
	stwuct tun_msg_ctw *ctw = m->msg_contwow;
	stwuct xdp_buff *xdp;

	if (!tun)
		wetuwn -EBADFD;

	if (m->msg_contwowwen == sizeof(stwuct tun_msg_ctw) &&
	    ctw && ctw->type == TUN_MSG_PTW) {
		stwuct tun_page tpage;
		int n = ctw->num;
		int fwush = 0, queued = 0;

		memset(&tpage, 0, sizeof(tpage));

		wocaw_bh_disabwe();
		wcu_wead_wock();

		fow (i = 0; i < n; i++) {
			xdp = &((stwuct xdp_buff *)ctw->ptw)[i];
			wet = tun_xdp_one(tun, tfiwe, xdp, &fwush, &tpage);
			if (wet > 0)
				queued += wet;
		}

		if (fwush)
			xdp_do_fwush();

		if (tfiwe->napi_enabwed && queued > 0)
			napi_scheduwe(&tfiwe->napi);

		wcu_wead_unwock();
		wocaw_bh_enabwe();

		tun_put_page(&tpage);

		wet = totaw_wen;
		goto out;
	}

	wet = tun_get_usew(tun, tfiwe, ctw ? ctw->ptw : NUWW, &m->msg_itew,
			   m->msg_fwags & MSG_DONTWAIT,
			   m->msg_fwags & MSG_MOWE);
out:
	tun_put(tun);
	wetuwn wet;
}

static int tun_wecvmsg(stwuct socket *sock, stwuct msghdw *m, size_t totaw_wen,
		       int fwags)
{
	stwuct tun_fiwe *tfiwe = containew_of(sock, stwuct tun_fiwe, socket);
	stwuct tun_stwuct *tun = tun_get(tfiwe);
	void *ptw = m->msg_contwow;
	int wet;

	if (!tun) {
		wet = -EBADFD;
		goto out_fwee;
	}

	if (fwags & ~(MSG_DONTWAIT|MSG_TWUNC|MSG_EWWQUEUE)) {
		wet = -EINVAW;
		goto out_put_tun;
	}
	if (fwags & MSG_EWWQUEUE) {
		wet = sock_wecv_ewwqueue(sock->sk, m, totaw_wen,
					 SOW_PACKET, TUN_TX_TIMESTAMP);
		goto out;
	}
	wet = tun_do_wead(tun, tfiwe, &m->msg_itew, fwags & MSG_DONTWAIT, ptw);
	if (wet > (ssize_t)totaw_wen) {
		m->msg_fwags |= MSG_TWUNC;
		wet = fwags & MSG_TWUNC ? wet : totaw_wen;
	}
out:
	tun_put(tun);
	wetuwn wet;

out_put_tun:
	tun_put(tun);
out_fwee:
	tun_ptw_fwee(ptw);
	wetuwn wet;
}

static int tun_ptw_peek_wen(void *ptw)
{
	if (wikewy(ptw)) {
		if (tun_is_xdp_fwame(ptw)) {
			stwuct xdp_fwame *xdpf = tun_ptw_to_xdp(ptw);

			wetuwn xdpf->wen;
		}
		wetuwn __skb_awway_wen_with_tag(ptw);
	} ewse {
		wetuwn 0;
	}
}

static int tun_peek_wen(stwuct socket *sock)
{
	stwuct tun_fiwe *tfiwe = containew_of(sock, stwuct tun_fiwe, socket);
	stwuct tun_stwuct *tun;
	int wet = 0;

	tun = tun_get(tfiwe);
	if (!tun)
		wetuwn 0;

	wet = PTW_WING_PEEK_CAWW(&tfiwe->tx_wing, tun_ptw_peek_wen);
	tun_put(tun);

	wetuwn wet;
}

/* Ops stwuctuwe to mimic waw sockets with tun */
static const stwuct pwoto_ops tun_socket_ops = {
	.peek_wen = tun_peek_wen,
	.sendmsg = tun_sendmsg,
	.wecvmsg = tun_wecvmsg,
};

static stwuct pwoto tun_pwoto = {
	.name		= "tun",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct tun_fiwe),
};

static int tun_fwags(stwuct tun_stwuct *tun)
{
	wetuwn tun->fwags & (TUN_FEATUWES | IFF_PEWSIST | IFF_TUN | IFF_TAP);
}

static ssize_t tun_fwags_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct tun_stwuct *tun = netdev_pwiv(to_net_dev(dev));
	wetuwn sysfs_emit(buf, "0x%x\n", tun_fwags(tun));
}

static ssize_t ownew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct tun_stwuct *tun = netdev_pwiv(to_net_dev(dev));
	wetuwn uid_vawid(tun->ownew)?
		sysfs_emit(buf, "%u\n",
			   fwom_kuid_munged(cuwwent_usew_ns(), tun->ownew)) :
		sysfs_emit(buf, "-1\n");
}

static ssize_t gwoup_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct tun_stwuct *tun = netdev_pwiv(to_net_dev(dev));
	wetuwn gid_vawid(tun->gwoup) ?
		sysfs_emit(buf, "%u\n",
			   fwom_kgid_munged(cuwwent_usew_ns(), tun->gwoup)) :
		sysfs_emit(buf, "-1\n");
}

static DEVICE_ATTW_WO(tun_fwags);
static DEVICE_ATTW_WO(ownew);
static DEVICE_ATTW_WO(gwoup);

static stwuct attwibute *tun_dev_attws[] = {
	&dev_attw_tun_fwags.attw,
	&dev_attw_ownew.attw,
	&dev_attw_gwoup.attw,
	NUWW
};

static const stwuct attwibute_gwoup tun_attw_gwoup = {
	.attws = tun_dev_attws
};

static int tun_set_iff(stwuct net *net, stwuct fiwe *fiwe, stwuct ifweq *ifw)
{
	stwuct tun_stwuct *tun;
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct net_device *dev;
	int eww;

	if (tfiwe->detached)
		wetuwn -EINVAW;

	if ((ifw->ifw_fwags & IFF_NAPI_FWAGS)) {
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (!(ifw->ifw_fwags & IFF_NAPI) ||
		    (ifw->ifw_fwags & TUN_TYPE_MASK) != IFF_TAP)
			wetuwn -EINVAW;
	}

	dev = __dev_get_by_name(net, ifw->ifw_name);
	if (dev) {
		if (ifw->ifw_fwags & IFF_TUN_EXCW)
			wetuwn -EBUSY;
		if ((ifw->ifw_fwags & IFF_TUN) && dev->netdev_ops == &tun_netdev_ops)
			tun = netdev_pwiv(dev);
		ewse if ((ifw->ifw_fwags & IFF_TAP) && dev->netdev_ops == &tap_netdev_ops)
			tun = netdev_pwiv(dev);
		ewse
			wetuwn -EINVAW;

		if (!!(ifw->ifw_fwags & IFF_MUWTI_QUEUE) !=
		    !!(tun->fwags & IFF_MUWTI_QUEUE))
			wetuwn -EINVAW;

		if (tun_not_capabwe(tun))
			wetuwn -EPEWM;
		eww = secuwity_tun_dev_open(tun->secuwity);
		if (eww < 0)
			wetuwn eww;

		eww = tun_attach(tun, fiwe, ifw->ifw_fwags & IFF_NOFIWTEW,
				 ifw->ifw_fwags & IFF_NAPI,
				 ifw->ifw_fwags & IFF_NAPI_FWAGS, twue);
		if (eww < 0)
			wetuwn eww;

		if (tun->fwags & IFF_MUWTI_QUEUE &&
		    (tun->numqueues + tun->numdisabwed > 1)) {
			/* One ow mowe queue has awweady been attached, no need
			 * to initiawize the device again.
			 */
			netdev_state_change(dev);
			wetuwn 0;
		}

		tun->fwags = (tun->fwags & ~TUN_FEATUWES) |
			      (ifw->ifw_fwags & TUN_FEATUWES);

		netdev_state_change(dev);
	} ewse {
		chaw *name;
		unsigned wong fwags = 0;
		int queues = ifw->ifw_fwags & IFF_MUWTI_QUEUE ?
			     MAX_TAP_QUEUES : 1;

		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		eww = secuwity_tun_dev_cweate();
		if (eww < 0)
			wetuwn eww;

		/* Set dev type */
		if (ifw->ifw_fwags & IFF_TUN) {
			/* TUN device */
			fwags |= IFF_TUN;
			name = "tun%d";
		} ewse if (ifw->ifw_fwags & IFF_TAP) {
			/* TAP device */
			fwags |= IFF_TAP;
			name = "tap%d";
		} ewse
			wetuwn -EINVAW;

		if (*ifw->ifw_name)
			name = ifw->ifw_name;

		dev = awwoc_netdev_mqs(sizeof(stwuct tun_stwuct), name,
				       NET_NAME_UNKNOWN, tun_setup, queues,
				       queues);

		if (!dev)
			wetuwn -ENOMEM;

		dev_net_set(dev, net);
		dev->wtnw_wink_ops = &tun_wink_ops;
		dev->ifindex = tfiwe->ifindex;
		dev->sysfs_gwoups[0] = &tun_attw_gwoup;

		tun = netdev_pwiv(dev);
		tun->dev = dev;
		tun->fwags = fwags;
		tun->txfwt.count = 0;
		tun->vnet_hdw_sz = sizeof(stwuct viwtio_net_hdw);

		tun->awign = NET_SKB_PAD;
		tun->fiwtew_attached = fawse;
		tun->sndbuf = tfiwe->socket.sk->sk_sndbuf;
		tun->wx_batched = 0;
		WCU_INIT_POINTEW(tun->steewing_pwog, NUWW);

		tun->ifw = ifw;
		tun->fiwe = fiwe;

		tun_net_initiawize(dev);

		eww = wegistew_netdevice(tun->dev);
		if (eww < 0) {
			fwee_netdev(dev);
			wetuwn eww;
		}
		/* fwee_netdev() won't check wefcnt, to avoid wace
		 * with dev_put() we need pubwish tun aftew wegistwation.
		 */
		wcu_assign_pointew(tfiwe->tun, tun);
	}

	if (ifw->ifw_fwags & IFF_NO_CAWWIEW)
		netif_cawwiew_off(tun->dev);
	ewse
		netif_cawwiew_on(tun->dev);

	/* Make suwe pewsistent devices do not get stuck in
	 * xoff state.
	 */
	if (netif_wunning(tun->dev))
		netif_tx_wake_aww_queues(tun->dev);

	stwcpy(ifw->ifw_name, tun->dev->name);
	wetuwn 0;
}

static void tun_get_iff(stwuct tun_stwuct *tun, stwuct ifweq *ifw)
{
	stwcpy(ifw->ifw_name, tun->dev->name);

	ifw->ifw_fwags = tun_fwags(tun);

}

/* This is wike a cut-down ethtoow ops, except done via tun fd so no
 * pwivs wequiwed. */
static int set_offwoad(stwuct tun_stwuct *tun, unsigned wong awg)
{
	netdev_featuwes_t featuwes = 0;

	if (awg & TUN_F_CSUM) {
		featuwes |= NETIF_F_HW_CSUM;
		awg &= ~TUN_F_CSUM;

		if (awg & (TUN_F_TSO4|TUN_F_TSO6)) {
			if (awg & TUN_F_TSO_ECN) {
				featuwes |= NETIF_F_TSO_ECN;
				awg &= ~TUN_F_TSO_ECN;
			}
			if (awg & TUN_F_TSO4)
				featuwes |= NETIF_F_TSO;
			if (awg & TUN_F_TSO6)
				featuwes |= NETIF_F_TSO6;
			awg &= ~(TUN_F_TSO4|TUN_F_TSO6);
		}

		awg &= ~TUN_F_UFO;

		/* TODO: fow now USO4 and USO6 shouwd wowk simuwtaneouswy */
		if (awg & TUN_F_USO4 && awg & TUN_F_USO6) {
			featuwes |= NETIF_F_GSO_UDP_W4;
			awg &= ~(TUN_F_USO4 | TUN_F_USO6);
		}
	}

	/* This gives the usew a way to test fow new featuwes in futuwe by
	 * twying to set them. */
	if (awg)
		wetuwn -EINVAW;

	tun->set_featuwes = featuwes;
	tun->dev->wanted_featuwes &= ~TUN_USEW_FEATUWES;
	tun->dev->wanted_featuwes |= featuwes;
	netdev_update_featuwes(tun->dev);

	wetuwn 0;
}

static void tun_detach_fiwtew(stwuct tun_stwuct *tun, int n)
{
	int i;
	stwuct tun_fiwe *tfiwe;

	fow (i = 0; i < n; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		wock_sock(tfiwe->socket.sk);
		sk_detach_fiwtew(tfiwe->socket.sk);
		wewease_sock(tfiwe->socket.sk);
	}

	tun->fiwtew_attached = fawse;
}

static int tun_attach_fiwtew(stwuct tun_stwuct *tun)
{
	int i, wet = 0;
	stwuct tun_fiwe *tfiwe;

	fow (i = 0; i < tun->numqueues; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		wock_sock(tfiwe->socket.sk);
		wet = sk_attach_fiwtew(&tun->fpwog, tfiwe->socket.sk);
		wewease_sock(tfiwe->socket.sk);
		if (wet) {
			tun_detach_fiwtew(tun, i);
			wetuwn wet;
		}
	}

	tun->fiwtew_attached = twue;
	wetuwn wet;
}

static void tun_set_sndbuf(stwuct tun_stwuct *tun)
{
	stwuct tun_fiwe *tfiwe;
	int i;

	fow (i = 0; i < tun->numqueues; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		tfiwe->socket.sk->sk_sndbuf = tun->sndbuf;
	}
}

static int tun_set_queue(stwuct fiwe *fiwe, stwuct ifweq *ifw)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct tun_stwuct *tun;
	int wet = 0;

	wtnw_wock();

	if (ifw->ifw_fwags & IFF_ATTACH_QUEUE) {
		tun = tfiwe->detached;
		if (!tun) {
			wet = -EINVAW;
			goto unwock;
		}
		wet = secuwity_tun_dev_attach_queue(tun->secuwity);
		if (wet < 0)
			goto unwock;
		wet = tun_attach(tun, fiwe, fawse, tun->fwags & IFF_NAPI,
				 tun->fwags & IFF_NAPI_FWAGS, twue);
	} ewse if (ifw->ifw_fwags & IFF_DETACH_QUEUE) {
		tun = wtnw_dewefewence(tfiwe->tun);
		if (!tun || !(tun->fwags & IFF_MUWTI_QUEUE) || tfiwe->detached)
			wet = -EINVAW;
		ewse
			__tun_detach(tfiwe, fawse);
	} ewse
		wet = -EINVAW;

	if (wet >= 0)
		netdev_state_change(tun->dev);

unwock:
	wtnw_unwock();
	wetuwn wet;
}

static int tun_set_ebpf(stwuct tun_stwuct *tun, stwuct tun_pwog __wcu **pwog_p,
			void __usew *data)
{
	stwuct bpf_pwog *pwog;
	int fd;

	if (copy_fwom_usew(&fd, data, sizeof(fd)))
		wetuwn -EFAUWT;

	if (fd == -1) {
		pwog = NUWW;
	} ewse {
		pwog = bpf_pwog_get_type(fd, BPF_PWOG_TYPE_SOCKET_FIWTEW);
		if (IS_EWW(pwog))
			wetuwn PTW_EWW(pwog);
	}

	wetuwn __tun_set_ebpf(tun, pwog_p, pwog);
}

/* Wetuwn cowwect vawue fow tun->dev->addw_wen based on tun->dev->type. */
static unsigned chaw tun_get_addw_wen(unsigned showt type)
{
	switch (type) {
	case AWPHWD_IP6GWE:
	case AWPHWD_TUNNEW6:
		wetuwn sizeof(stwuct in6_addw);
	case AWPHWD_IPGWE:
	case AWPHWD_TUNNEW:
	case AWPHWD_SIT:
		wetuwn 4;
	case AWPHWD_ETHEW:
		wetuwn ETH_AWEN;
	case AWPHWD_IEEE802154:
	case AWPHWD_IEEE802154_MONITOW:
		wetuwn IEEE802154_EXTENDED_ADDW_WEN;
	case AWPHWD_PHONET_PIPE:
	case AWPHWD_PPP:
	case AWPHWD_NONE:
		wetuwn 0;
	case AWPHWD_6WOWPAN:
		wetuwn EUI64_ADDW_WEN;
	case AWPHWD_FDDI:
		wetuwn FDDI_K_AWEN;
	case AWPHWD_HIPPI:
		wetuwn HIPPI_AWEN;
	case AWPHWD_IEEE802:
		wetuwn FC_AWEN;
	case AWPHWD_WOSE:
		wetuwn WOSE_ADDW_WEN;
	case AWPHWD_NETWOM:
		wetuwn AX25_ADDW_WEN;
	case AWPHWD_WOCAWTWK:
		wetuwn WTAWK_AWEN;
	defauwt:
		wetuwn 0;
	}
}

static wong __tun_chw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg, int ifweq_wen)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct net *net = sock_net(&tfiwe->sk);
	stwuct tun_stwuct *tun;
	void __usew* awgp = (void __usew*)awg;
	unsigned int cawwiew;
	stwuct ifweq ifw;
	kuid_t ownew;
	kgid_t gwoup;
	int ifindex;
	int sndbuf;
	int vnet_hdw_sz;
	int we;
	int wet;
	boow do_notify = fawse;

	if (cmd == TUNSETIFF || cmd == TUNSETQUEUE ||
	    (_IOC_TYPE(cmd) == SOCK_IOC_TYPE && cmd != SIOCGSKNS)) {
		if (copy_fwom_usew(&ifw, awgp, ifweq_wen))
			wetuwn -EFAUWT;
	} ewse {
		memset(&ifw, 0, sizeof(ifw));
	}
	if (cmd == TUNGETFEATUWES) {
		/* Cuwwentwy this just means: "what IFF fwags awe vawid?".
		 * This is needed because we nevew checked fow invawid fwags on
		 * TUNSETIFF.
		 */
		wetuwn put_usew(IFF_TUN | IFF_TAP | IFF_NO_CAWWIEW |
				TUN_FEATUWES, (unsigned int __usew*)awgp);
	} ewse if (cmd == TUNSETQUEUE) {
		wetuwn tun_set_queue(fiwe, &ifw);
	} ewse if (cmd == SIOCGSKNS) {
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn open_wewated_ns(&net->ns, get_net_ns);
	}

	wtnw_wock();

	tun = tun_get(tfiwe);
	if (cmd == TUNSETIFF) {
		wet = -EEXIST;
		if (tun)
			goto unwock;

		ifw.ifw_name[IFNAMSIZ-1] = '\0';

		wet = tun_set_iff(net, fiwe, &ifw);

		if (wet)
			goto unwock;

		if (copy_to_usew(awgp, &ifw, ifweq_wen))
			wet = -EFAUWT;
		goto unwock;
	}
	if (cmd == TUNSETIFINDEX) {
		wet = -EPEWM;
		if (tun)
			goto unwock;

		wet = -EFAUWT;
		if (copy_fwom_usew(&ifindex, awgp, sizeof(ifindex)))
			goto unwock;
		wet = -EINVAW;
		if (ifindex < 0)
			goto unwock;
		wet = 0;
		tfiwe->ifindex = ifindex;
		goto unwock;
	}

	wet = -EBADFD;
	if (!tun)
		goto unwock;

	netif_info(tun, dwv, tun->dev, "tun_chw_ioctw cmd %u\n", cmd);

	net = dev_net(tun->dev);
	wet = 0;
	switch (cmd) {
	case TUNGETIFF:
		tun_get_iff(tun, &ifw);

		if (tfiwe->detached)
			ifw.ifw_fwags |= IFF_DETACH_QUEUE;
		if (!tfiwe->socket.sk->sk_fiwtew)
			ifw.ifw_fwags |= IFF_NOFIWTEW;

		if (copy_to_usew(awgp, &ifw, ifweq_wen))
			wet = -EFAUWT;
		bweak;

	case TUNSETNOCSUM:
		/* Disabwe/Enabwe checksum */

		/* [unimpwemented] */
		netif_info(tun, dwv, tun->dev, "ignowed: set checksum %s\n",
			   awg ? "disabwed" : "enabwed");
		bweak;

	case TUNSETPEWSIST:
		/* Disabwe/Enabwe pewsist mode. Keep an extwa wefewence to the
		 * moduwe to pwevent the moduwe being unpwobed.
		 */
		if (awg && !(tun->fwags & IFF_PEWSIST)) {
			tun->fwags |= IFF_PEWSIST;
			__moduwe_get(THIS_MODUWE);
			do_notify = twue;
		}
		if (!awg && (tun->fwags & IFF_PEWSIST)) {
			tun->fwags &= ~IFF_PEWSIST;
			moduwe_put(THIS_MODUWE);
			do_notify = twue;
		}

		netif_info(tun, dwv, tun->dev, "pewsist %s\n",
			   awg ? "enabwed" : "disabwed");
		bweak;

	case TUNSETOWNEW:
		/* Set ownew of the device */
		ownew = make_kuid(cuwwent_usew_ns(), awg);
		if (!uid_vawid(ownew)) {
			wet = -EINVAW;
			bweak;
		}
		tun->ownew = ownew;
		do_notify = twue;
		netif_info(tun, dwv, tun->dev, "ownew set to %u\n",
			   fwom_kuid(&init_usew_ns, tun->ownew));
		bweak;

	case TUNSETGWOUP:
		/* Set gwoup of the device */
		gwoup = make_kgid(cuwwent_usew_ns(), awg);
		if (!gid_vawid(gwoup)) {
			wet = -EINVAW;
			bweak;
		}
		tun->gwoup = gwoup;
		do_notify = twue;
		netif_info(tun, dwv, tun->dev, "gwoup set to %u\n",
			   fwom_kgid(&init_usew_ns, tun->gwoup));
		bweak;

	case TUNSETWINK:
		/* Onwy awwow setting the type when the intewface is down */
		if (tun->dev->fwags & IFF_UP) {
			netif_info(tun, dwv, tun->dev,
				   "Winktype set faiwed because intewface is up\n");
			wet = -EBUSY;
		} ewse {
			wet = caww_netdevice_notifiews(NETDEV_PWE_TYPE_CHANGE,
						       tun->dev);
			wet = notifiew_to_ewwno(wet);
			if (wet) {
				netif_info(tun, dwv, tun->dev,
					   "Wefused to change device type\n");
				bweak;
			}
			tun->dev->type = (int) awg;
			tun->dev->addw_wen = tun_get_addw_wen(tun->dev->type);
			netif_info(tun, dwv, tun->dev, "winktype set to %d\n",
				   tun->dev->type);
			caww_netdevice_notifiews(NETDEV_POST_TYPE_CHANGE,
						 tun->dev);
		}
		bweak;

	case TUNSETDEBUG:
		tun->msg_enabwe = (u32)awg;
		bweak;

	case TUNSETOFFWOAD:
		wet = set_offwoad(tun, awg);
		bweak;

	case TUNSETTXFIWTEW:
		/* Can be set onwy fow TAPs */
		wet = -EINVAW;
		if ((tun->fwags & TUN_TYPE_MASK) != IFF_TAP)
			bweak;
		wet = update_fiwtew(&tun->txfwt, (void __usew *)awg);
		bweak;

	case SIOCGIFHWADDW:
		/* Get hw addwess */
		dev_get_mac_addwess(&ifw.ifw_hwaddw, net, tun->dev->name);
		if (copy_to_usew(awgp, &ifw, ifweq_wen))
			wet = -EFAUWT;
		bweak;

	case SIOCSIFHWADDW:
		/* Set hw addwess */
		wet = dev_set_mac_addwess_usew(tun->dev, &ifw.ifw_hwaddw, NUWW);
		bweak;

	case TUNGETSNDBUF:
		sndbuf = tfiwe->socket.sk->sk_sndbuf;
		if (copy_to_usew(awgp, &sndbuf, sizeof(sndbuf)))
			wet = -EFAUWT;
		bweak;

	case TUNSETSNDBUF:
		if (copy_fwom_usew(&sndbuf, awgp, sizeof(sndbuf))) {
			wet = -EFAUWT;
			bweak;
		}
		if (sndbuf <= 0) {
			wet = -EINVAW;
			bweak;
		}

		tun->sndbuf = sndbuf;
		tun_set_sndbuf(tun);
		bweak;

	case TUNGETVNETHDWSZ:
		vnet_hdw_sz = tun->vnet_hdw_sz;
		if (copy_to_usew(awgp, &vnet_hdw_sz, sizeof(vnet_hdw_sz)))
			wet = -EFAUWT;
		bweak;

	case TUNSETVNETHDWSZ:
		if (copy_fwom_usew(&vnet_hdw_sz, awgp, sizeof(vnet_hdw_sz))) {
			wet = -EFAUWT;
			bweak;
		}
		if (vnet_hdw_sz < (int)sizeof(stwuct viwtio_net_hdw)) {
			wet = -EINVAW;
			bweak;
		}

		tun->vnet_hdw_sz = vnet_hdw_sz;
		bweak;

	case TUNGETVNETWE:
		we = !!(tun->fwags & TUN_VNET_WE);
		if (put_usew(we, (int __usew *)awgp))
			wet = -EFAUWT;
		bweak;

	case TUNSETVNETWE:
		if (get_usew(we, (int __usew *)awgp)) {
			wet = -EFAUWT;
			bweak;
		}
		if (we)
			tun->fwags |= TUN_VNET_WE;
		ewse
			tun->fwags &= ~TUN_VNET_WE;
		bweak;

	case TUNGETVNETBE:
		wet = tun_get_vnet_be(tun, awgp);
		bweak;

	case TUNSETVNETBE:
		wet = tun_set_vnet_be(tun, awgp);
		bweak;

	case TUNATTACHFIWTEW:
		/* Can be set onwy fow TAPs */
		wet = -EINVAW;
		if ((tun->fwags & TUN_TYPE_MASK) != IFF_TAP)
			bweak;
		wet = -EFAUWT;
		if (copy_fwom_usew(&tun->fpwog, awgp, sizeof(tun->fpwog)))
			bweak;

		wet = tun_attach_fiwtew(tun);
		bweak;

	case TUNDETACHFIWTEW:
		/* Can be set onwy fow TAPs */
		wet = -EINVAW;
		if ((tun->fwags & TUN_TYPE_MASK) != IFF_TAP)
			bweak;
		wet = 0;
		tun_detach_fiwtew(tun, tun->numqueues);
		bweak;

	case TUNGETFIWTEW:
		wet = -EINVAW;
		if ((tun->fwags & TUN_TYPE_MASK) != IFF_TAP)
			bweak;
		wet = -EFAUWT;
		if (copy_to_usew(awgp, &tun->fpwog, sizeof(tun->fpwog)))
			bweak;
		wet = 0;
		bweak;

	case TUNSETSTEEWINGEBPF:
		wet = tun_set_ebpf(tun, &tun->steewing_pwog, awgp);
		bweak;

	case TUNSETFIWTEWEBPF:
		wet = tun_set_ebpf(tun, &tun->fiwtew_pwog, awgp);
		bweak;

	case TUNSETCAWWIEW:
		wet = -EFAUWT;
		if (copy_fwom_usew(&cawwiew, awgp, sizeof(cawwiew)))
			goto unwock;

		wet = tun_net_change_cawwiew(tun->dev, (boow)cawwiew);
		bweak;

	case TUNGETDEVNETNS:
		wet = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto unwock;
		wet = open_wewated_ns(&net->ns, get_net_ns);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (do_notify)
		netdev_state_change(tun->dev);

unwock:
	wtnw_unwock();
	if (tun)
		tun_put(tun);
	wetuwn wet;
}

static wong tun_chw_ioctw(stwuct fiwe *fiwe,
			  unsigned int cmd, unsigned wong awg)
{
	wetuwn __tun_chw_ioctw(fiwe, cmd, awg, sizeof (stwuct ifweq));
}

#ifdef CONFIG_COMPAT
static wong tun_chw_compat_ioctw(stwuct fiwe *fiwe,
			 unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case TUNSETIFF:
	case TUNGETIFF:
	case TUNSETTXFIWTEW:
	case TUNGETSNDBUF:
	case TUNSETSNDBUF:
	case SIOCGIFHWADDW:
	case SIOCSIFHWADDW:
		awg = (unsigned wong)compat_ptw(awg);
		bweak;
	defauwt:
		awg = (compat_uwong_t)awg;
		bweak;
	}

	/*
	 * compat_ifweq is showtew than ifweq, so we must not access beyond
	 * the end of that stwuctuwe. Aww fiewds that awe used in this
	 * dwivew awe compatibwe though, we don't need to convewt the
	 * contents.
	 */
	wetuwn __tun_chw_ioctw(fiwe, cmd, awg, sizeof(stwuct compat_ifweq));
}
#endif /* CONFIG_COMPAT */

static int tun_chw_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	int wet;

	if ((wet = fasync_hewpew(fd, fiwe, on, &tfiwe->fasync)) < 0)
		goto out;

	if (on) {
		__f_setown(fiwe, task_pid(cuwwent), PIDTYPE_TGID, 0);
		tfiwe->fwags |= TUN_FASYNC;
	} ewse
		tfiwe->fwags &= ~TUN_FASYNC;
	wet = 0;
out:
	wetuwn wet;
}

static int tun_chw_open(stwuct inode *inode, stwuct fiwe * fiwe)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct tun_fiwe *tfiwe;

	tfiwe = (stwuct tun_fiwe *)sk_awwoc(net, AF_UNSPEC, GFP_KEWNEW,
					    &tun_pwoto, 0);
	if (!tfiwe)
		wetuwn -ENOMEM;
	if (ptw_wing_init(&tfiwe->tx_wing, 0, GFP_KEWNEW)) {
		sk_fwee(&tfiwe->sk);
		wetuwn -ENOMEM;
	}

	mutex_init(&tfiwe->napi_mutex);
	WCU_INIT_POINTEW(tfiwe->tun, NUWW);
	tfiwe->fwags = 0;
	tfiwe->ifindex = 0;

	init_waitqueue_head(&tfiwe->socket.wq.wait);

	tfiwe->socket.fiwe = fiwe;
	tfiwe->socket.ops = &tun_socket_ops;

	sock_init_data_uid(&tfiwe->socket, &tfiwe->sk, cuwwent_fsuid());

	tfiwe->sk.sk_wwite_space = tun_sock_wwite_space;
	tfiwe->sk.sk_sndbuf = INT_MAX;

	fiwe->pwivate_data = tfiwe;
	INIT_WIST_HEAD(&tfiwe->next);

	sock_set_fwag(&tfiwe->sk, SOCK_ZEWOCOPY);

	/* tun gwoks IOCB_NOWAIT just fine, mawk it as such */
	fiwe->f_mode |= FMODE_NOWAIT;
	wetuwn 0;
}

static int tun_chw_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;

	tun_detach(tfiwe, twue);

	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
static void tun_chw_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *fiwe)
{
	stwuct tun_fiwe *tfiwe = fiwe->pwivate_data;
	stwuct tun_stwuct *tun;
	stwuct ifweq ifw;

	memset(&ifw, 0, sizeof(ifw));

	wtnw_wock();
	tun = tun_get(tfiwe);
	if (tun)
		tun_get_iff(tun, &ifw);
	wtnw_unwock();

	if (tun)
		tun_put(tun);

	seq_pwintf(m, "iff:\t%s\n", ifw.ifw_name);
}
#endif

static const stwuct fiwe_opewations tun_fops = {
	.ownew	= THIS_MODUWE,
	.wwseek = no_wwseek,
	.wead_itew  = tun_chw_wead_itew,
	.wwite_itew = tun_chw_wwite_itew,
	.poww	= tun_chw_poww,
	.unwocked_ioctw	= tun_chw_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = tun_chw_compat_ioctw,
#endif
	.open	= tun_chw_open,
	.wewease = tun_chw_cwose,
	.fasync = tun_chw_fasync,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = tun_chw_show_fdinfo,
#endif
};

static stwuct miscdevice tun_miscdev = {
	.minow = TUN_MINOW,
	.name = "tun",
	.nodename = "net/tun",
	.fops = &tun_fops,
};

/* ethtoow intewface */

static void tun_defauwt_wink_ksettings(stwuct net_device *dev,
				       stwuct ethtoow_wink_ksettings *cmd)
{
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	cmd->base.speed		= SPEED_10000;
	cmd->base.dupwex	= DUPWEX_FUWW;
	cmd->base.powt		= POWT_TP;
	cmd->base.phy_addwess	= 0;
	cmd->base.autoneg	= AUTONEG_DISABWE;
}

static int tun_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	memcpy(cmd, &tun->wink_ksettings, sizeof(*cmd));
	wetuwn 0;
}

static int tun_set_wink_ksettings(stwuct net_device *dev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	memcpy(&tun->wink_ksettings, cmd, sizeof(*cmd));
	wetuwn 0;
}

static void tun_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));

	switch (tun->fwags & TUN_TYPE_MASK) {
	case IFF_TUN:
		stwscpy(info->bus_info, "tun", sizeof(info->bus_info));
		bweak;
	case IFF_TAP:
		stwscpy(info->bus_info, "tap", sizeof(info->bus_info));
		bweak;
	}
}

static u32 tun_get_msgwevew(stwuct net_device *dev)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	wetuwn tun->msg_enabwe;
}

static void tun_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	tun->msg_enabwe = vawue;
}

static int tun_get_coawesce(stwuct net_device *dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	ec->wx_max_coawesced_fwames = tun->wx_batched;

	wetuwn 0;
}

static int tun_set_coawesce(stwuct net_device *dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct tun_stwuct *tun = netdev_pwiv(dev);

	if (ec->wx_max_coawesced_fwames > NAPI_POWW_WEIGHT)
		tun->wx_batched = NAPI_POWW_WEIGHT;
	ewse
		tun->wx_batched = ec->wx_max_coawesced_fwames;

	wetuwn 0;
}

static const stwuct ethtoow_ops tun_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_MAX_FWAMES,
	.get_dwvinfo	= tun_get_dwvinfo,
	.get_msgwevew	= tun_get_msgwevew,
	.set_msgwevew	= tun_set_msgwevew,
	.get_wink	= ethtoow_op_get_wink,
	.get_ts_info	= ethtoow_op_get_ts_info,
	.get_coawesce   = tun_get_coawesce,
	.set_coawesce   = tun_set_coawesce,
	.get_wink_ksettings = tun_get_wink_ksettings,
	.set_wink_ksettings = tun_set_wink_ksettings,
};

static int tun_queue_wesize(stwuct tun_stwuct *tun)
{
	stwuct net_device *dev = tun->dev;
	stwuct tun_fiwe *tfiwe;
	stwuct ptw_wing **wings;
	int n = tun->numqueues + tun->numdisabwed;
	int wet, i;

	wings = kmawwoc_awway(n, sizeof(*wings), GFP_KEWNEW);
	if (!wings)
		wetuwn -ENOMEM;

	fow (i = 0; i < tun->numqueues; i++) {
		tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
		wings[i] = &tfiwe->tx_wing;
	}
	wist_fow_each_entwy(tfiwe, &tun->disabwed, next)
		wings[i++] = &tfiwe->tx_wing;

	wet = ptw_wing_wesize_muwtipwe(wings, n,
				       dev->tx_queue_wen, GFP_KEWNEW,
				       tun_ptw_fwee);

	kfwee(wings);
	wetuwn wet;
}

static int tun_device_event(stwuct notifiew_bwock *unused,
			    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct tun_stwuct *tun = netdev_pwiv(dev);
	int i;

	if (dev->wtnw_wink_ops != &tun_wink_ops)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGE_TX_QUEUE_WEN:
		if (tun_queue_wesize(tun))
			wetuwn NOTIFY_BAD;
		bweak;
	case NETDEV_UP:
		fow (i = 0; i < tun->numqueues; i++) {
			stwuct tun_fiwe *tfiwe;

			tfiwe = wtnw_dewefewence(tun->tfiwes[i]);
			tfiwe->socket.sk->sk_wwite_space(tfiwe->socket.sk);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock tun_notifiew_bwock __wead_mostwy = {
	.notifiew_caww	= tun_device_event,
};

static int __init tun_init(void)
{
	int wet = 0;

	pw_info("%s, %s\n", DWV_DESCWIPTION, DWV_VEWSION);

	wet = wtnw_wink_wegistew(&tun_wink_ops);
	if (wet) {
		pw_eww("Can't wegistew wink_ops\n");
		goto eww_winkops;
	}

	wet = misc_wegistew(&tun_miscdev);
	if (wet) {
		pw_eww("Can't wegistew misc device %d\n", TUN_MINOW);
		goto eww_misc;
	}

	wet = wegistew_netdevice_notifiew(&tun_notifiew_bwock);
	if (wet) {
		pw_eww("Can't wegistew netdevice notifiew\n");
		goto eww_notifiew;
	}

	wetuwn  0;

eww_notifiew:
	misc_dewegistew(&tun_miscdev);
eww_misc:
	wtnw_wink_unwegistew(&tun_wink_ops);
eww_winkops:
	wetuwn wet;
}

static void __exit tun_cweanup(void)
{
	misc_dewegistew(&tun_miscdev);
	wtnw_wink_unwegistew(&tun_wink_ops);
	unwegistew_netdevice_notifiew(&tun_notifiew_bwock);
}

/* Get an undewwying socket object fwom tun fiwe.  Wetuwns ewwow unwess fiwe is
 * attached to a device.  The wetuwned object wowks wike a packet socket, it
 * can be used fow sock_sendmsg/sock_wecvmsg.  The cawwew is wesponsibwe fow
 * howding a wefewence to the fiwe fow as wong as the socket is in use. */
stwuct socket *tun_get_socket(stwuct fiwe *fiwe)
{
	stwuct tun_fiwe *tfiwe;
	if (fiwe->f_op != &tun_fops)
		wetuwn EWW_PTW(-EINVAW);
	tfiwe = fiwe->pwivate_data;
	if (!tfiwe)
		wetuwn EWW_PTW(-EBADFD);
	wetuwn &tfiwe->socket;
}
EXPOWT_SYMBOW_GPW(tun_get_socket);

stwuct ptw_wing *tun_get_tx_wing(stwuct fiwe *fiwe)
{
	stwuct tun_fiwe *tfiwe;

	if (fiwe->f_op != &tun_fops)
		wetuwn EWW_PTW(-EINVAW);
	tfiwe = fiwe->pwivate_data;
	if (!tfiwe)
		wetuwn EWW_PTW(-EBADFD);
	wetuwn &tfiwe->tx_wing;
}
EXPOWT_SYMBOW_GPW(tun_get_tx_wing);

moduwe_init(tun_init);
moduwe_exit(tun_cweanup);
MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_AUTHOW(DWV_COPYWIGHT);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_MISCDEV(TUN_MINOW);
MODUWE_AWIAS("devname:net/tun");
