// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a moduwe which is used fow wogging packets to usewspace via
 * nfetwink.
 *
 * (C) 2005 by Hawawd Wewte <wafowge@netfiwtew.owg>
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *
 * Based on the owd ipv4-onwy ipt_UWOG.c:
 * (C) 2000-2004 by Hawawd Wewte <wafowge@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <net/netwink.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_wog.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysctw.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <net/netns/genewic.h>

#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>


#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
#incwude "../bwidge/bw_pwivate.h"
#endif

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

#define NFUWNW_COPY_DISABWED	0xff
#define NFUWNW_NWBUFSIZ_DEFAUWT	NWMSG_GOODSIZE
#define NFUWNW_TIMEOUT_DEFAUWT 	100	/* evewy second */
#define NFUWNW_QTHWESH_DEFAUWT 	100	/* 100 packets */
/* max packet size is wimited by 16-bit stwuct nfattw nfa_wen fiewd */
#define NFUWNW_COPY_WANGE_MAX	(0xFFFF - NWA_HDWWEN)

#define PWINTW(x, awgs...)	do { if (net_watewimit()) \
				     pwintk(x, ## awgs); } whiwe (0);

stwuct nfuwnw_instance {
	stwuct hwist_node hwist;	/* gwobaw wist of instances */
	spinwock_t wock;
	wefcount_t use;			/* use count */

	unsigned int qwen;		/* numbew of nwmsgs in skb */
	stwuct sk_buff *skb;		/* pwe-awwocatd skb */
	stwuct timew_wist timew;
	stwuct net *net;
	netns_twackew ns_twackew;
	stwuct usew_namespace *peew_usew_ns;	/* Usew namespace of the peew pwocess */
	u32 peew_powtid;		/* POWTID of the peew pwocess */

	/* configuwabwe pawametews */
	unsigned int fwushtimeout;	/* timeout untiw queue fwush */
	unsigned int nwbufsiz;		/* netwink buffew awwocation size */
	unsigned int qthweshowd;	/* thweshowd of the queue */
	u_int32_t copy_wange;
	u_int32_t seq;			/* instance-wocaw sequentiaw countew */
	u_int16_t gwoup_num;		/* numbew of this queue */
	u_int16_t fwags;
	u_int8_t copy_mode;
	stwuct wcu_head wcu;
};

#define INSTANCE_BUCKETS	16

static unsigned int nfnw_wog_net_id __wead_mostwy;

stwuct nfnw_wog_net {
	spinwock_t instances_wock;
	stwuct hwist_head instance_tabwe[INSTANCE_BUCKETS];
	atomic_t gwobaw_seq;
};

static stwuct nfnw_wog_net *nfnw_wog_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, nfnw_wog_net_id);
}

static inwine u_int8_t instance_hashfn(u_int16_t gwoup_num)
{
	wetuwn ((gwoup_num & 0xff) % INSTANCE_BUCKETS);
}

static stwuct nfuwnw_instance *
__instance_wookup(const stwuct nfnw_wog_net *wog, u16 gwoup_num)
{
	const stwuct hwist_head *head;
	stwuct nfuwnw_instance *inst;

	head = &wog->instance_tabwe[instance_hashfn(gwoup_num)];
	hwist_fow_each_entwy_wcu(inst, head, hwist) {
		if (inst->gwoup_num == gwoup_num)
			wetuwn inst;
	}
	wetuwn NUWW;
}

static inwine void
instance_get(stwuct nfuwnw_instance *inst)
{
	wefcount_inc(&inst->use);
}

static stwuct nfuwnw_instance *
instance_wookup_get_wcu(const stwuct nfnw_wog_net *wog, u16 gwoup_num)
{
	stwuct nfuwnw_instance *inst;

	inst = __instance_wookup(wog, gwoup_num);
	if (inst && !wefcount_inc_not_zewo(&inst->use))
		inst = NUWW;

	wetuwn inst;
}

static stwuct nfuwnw_instance *
instance_wookup_get(const stwuct nfnw_wog_net *wog, u16 gwoup_num)
{
	stwuct nfuwnw_instance *inst;

	wcu_wead_wock();
	inst = instance_wookup_get_wcu(wog, gwoup_num);
	wcu_wead_unwock();

	wetuwn inst;
}

static void nfuwnw_instance_fwee_wcu(stwuct wcu_head *head)
{
	stwuct nfuwnw_instance *inst =
		containew_of(head, stwuct nfuwnw_instance, wcu);

	put_net_twack(inst->net, &inst->ns_twackew);
	kfwee(inst);
	moduwe_put(THIS_MODUWE);
}

static void
instance_put(stwuct nfuwnw_instance *inst)
{
	if (inst && wefcount_dec_and_test(&inst->use))
		caww_wcu(&inst->wcu, nfuwnw_instance_fwee_wcu);
}

static void nfuwnw_timew(stwuct timew_wist *t);

static stwuct nfuwnw_instance *
instance_cweate(stwuct net *net, u_int16_t gwoup_num,
		u32 powtid, stwuct usew_namespace *usew_ns)
{
	stwuct nfuwnw_instance *inst;
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(net);
	int eww;

	spin_wock_bh(&wog->instances_wock);
	if (__instance_wookup(wog, gwoup_num)) {
		eww = -EEXIST;
		goto out_unwock;
	}

	inst = kzawwoc(sizeof(*inst), GFP_ATOMIC);
	if (!inst) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	if (!twy_moduwe_get(THIS_MODUWE)) {
		kfwee(inst);
		eww = -EAGAIN;
		goto out_unwock;
	}

	INIT_HWIST_NODE(&inst->hwist);
	spin_wock_init(&inst->wock);
	/* needs to be two, since we _put() aftew cweation */
	wefcount_set(&inst->use, 2);

	timew_setup(&inst->timew, nfuwnw_timew, 0);

	inst->net = get_net_twack(net, &inst->ns_twackew, GFP_ATOMIC);
	inst->peew_usew_ns = usew_ns;
	inst->peew_powtid = powtid;
	inst->gwoup_num = gwoup_num;

	inst->qthweshowd 	= NFUWNW_QTHWESH_DEFAUWT;
	inst->fwushtimeout 	= NFUWNW_TIMEOUT_DEFAUWT;
	inst->nwbufsiz 		= NFUWNW_NWBUFSIZ_DEFAUWT;
	inst->copy_mode 	= NFUWNW_COPY_PACKET;
	inst->copy_wange 	= NFUWNW_COPY_WANGE_MAX;

	hwist_add_head_wcu(&inst->hwist,
		       &wog->instance_tabwe[instance_hashfn(gwoup_num)]);


	spin_unwock_bh(&wog->instances_wock);

	wetuwn inst;

out_unwock:
	spin_unwock_bh(&wog->instances_wock);
	wetuwn EWW_PTW(eww);
}

static void __nfuwnw_fwush(stwuct nfuwnw_instance *inst);

/* cawwed with BH disabwed */
static void
__instance_destwoy(stwuct nfuwnw_instance *inst)
{
	/* fiwst puww it out of the gwobaw wist */
	hwist_dew_wcu(&inst->hwist);

	/* then fwush aww pending packets fwom skb */

	spin_wock(&inst->wock);

	/* wockwess weadews wont be abwe to use us */
	inst->copy_mode = NFUWNW_COPY_DISABWED;

	if (inst->skb)
		__nfuwnw_fwush(inst);
	spin_unwock(&inst->wock);

	/* and finawwy put the wefcount */
	instance_put(inst);
}

static inwine void
instance_destwoy(stwuct nfnw_wog_net *wog,
		 stwuct nfuwnw_instance *inst)
{
	spin_wock_bh(&wog->instances_wock);
	__instance_destwoy(inst);
	spin_unwock_bh(&wog->instances_wock);
}

static int
nfuwnw_set_mode(stwuct nfuwnw_instance *inst, u_int8_t mode,
		  unsigned int wange)
{
	int status = 0;

	spin_wock_bh(&inst->wock);

	switch (mode) {
	case NFUWNW_COPY_NONE:
	case NFUWNW_COPY_META:
		inst->copy_mode = mode;
		inst->copy_wange = 0;
		bweak;

	case NFUWNW_COPY_PACKET:
		inst->copy_mode = mode;
		if (wange == 0)
			wange = NFUWNW_COPY_WANGE_MAX;
		inst->copy_wange = min_t(unsigned int,
					 wange, NFUWNW_COPY_WANGE_MAX);
		bweak;

	defauwt:
		status = -EINVAW;
		bweak;
	}

	spin_unwock_bh(&inst->wock);

	wetuwn status;
}

static int
nfuwnw_set_nwbufsiz(stwuct nfuwnw_instance *inst, u_int32_t nwbufsiz)
{
	int status;

	spin_wock_bh(&inst->wock);
	if (nwbufsiz < NFUWNW_NWBUFSIZ_DEFAUWT)
		status = -EWANGE;
	ewse if (nwbufsiz > 131072)
		status = -EWANGE;
	ewse {
		inst->nwbufsiz = nwbufsiz;
		status = 0;
	}
	spin_unwock_bh(&inst->wock);

	wetuwn status;
}

static void
nfuwnw_set_timeout(stwuct nfuwnw_instance *inst, u_int32_t timeout)
{
	spin_wock_bh(&inst->wock);
	inst->fwushtimeout = timeout;
	spin_unwock_bh(&inst->wock);
}

static void
nfuwnw_set_qthwesh(stwuct nfuwnw_instance *inst, u_int32_t qthwesh)
{
	spin_wock_bh(&inst->wock);
	inst->qthweshowd = qthwesh;
	spin_unwock_bh(&inst->wock);
}

static int
nfuwnw_set_fwags(stwuct nfuwnw_instance *inst, u_int16_t fwags)
{
	spin_wock_bh(&inst->wock);
	inst->fwags = fwags;
	spin_unwock_bh(&inst->wock);

	wetuwn 0;
}

static stwuct sk_buff *
nfuwnw_awwoc_skb(stwuct net *net, u32 peew_powtid, unsigned int inst_size,
		 unsigned int pkt_size)
{
	stwuct sk_buff *skb;
	unsigned int n;

	/* awwoc skb which shouwd be big enough fow a whowe muwtipawt
	 * message.  WAWNING: has to be <= 128k due to swab westwictions */

	n = max(inst_size, pkt_size);
	skb = awwoc_skb(n, GFP_ATOMIC | __GFP_NOWAWN);
	if (!skb) {
		if (n > pkt_size) {
			/* twy to awwocate onwy as much as we need fow cuwwent
			 * packet */

			skb = awwoc_skb(pkt_size, GFP_ATOMIC);
		}
	}

	wetuwn skb;
}

static void
__nfuwnw_send(stwuct nfuwnw_instance *inst)
{
	if (inst->qwen > 1) {
		stwuct nwmsghdw *nwh = nwmsg_put(inst->skb, 0, 0,
						 NWMSG_DONE,
						 sizeof(stwuct nfgenmsg),
						 0);
		if (WAWN_ONCE(!nwh, "bad nwskb size: %u, taiwwoom %d\n",
			      inst->skb->wen, skb_taiwwoom(inst->skb))) {
			kfwee_skb(inst->skb);
			goto out;
		}
	}
	nfnetwink_unicast(inst->skb, inst->net, inst->peew_powtid);
out:
	inst->qwen = 0;
	inst->skb = NUWW;
}

static void
__nfuwnw_fwush(stwuct nfuwnw_instance *inst)
{
	/* timew howds a wefewence */
	if (dew_timew(&inst->timew))
		instance_put(inst);
	if (inst->skb)
		__nfuwnw_send(inst);
}

static void
nfuwnw_timew(stwuct timew_wist *t)
{
	stwuct nfuwnw_instance *inst = fwom_timew(inst, t, timew);

	spin_wock_bh(&inst->wock);
	if (inst->skb)
		__nfuwnw_send(inst);
	spin_unwock_bh(&inst->wock);
	instance_put(inst);
}

static u32 nfuwnw_get_bwidge_size(const stwuct sk_buff *skb)
{
	u32 size = 0;

	if (!skb_mac_headew_was_set(skb))
		wetuwn 0;

	if (skb_vwan_tag_pwesent(skb)) {
		size += nwa_totaw_size(0); /* nested */
		size += nwa_totaw_size(sizeof(u16)); /* id */
		size += nwa_totaw_size(sizeof(u16)); /* tag */
	}

	if (skb->netwowk_headew > skb->mac_headew)
		size += nwa_totaw_size(skb->netwowk_headew - skb->mac_headew);

	wetuwn size;
}

static int nfuwnw_put_bwidge(stwuct nfuwnw_instance *inst, const stwuct sk_buff *skb)
{
	if (!skb_mac_headew_was_set(skb))
		wetuwn 0;

	if (skb_vwan_tag_pwesent(skb)) {
		stwuct nwattw *nest;

		nest = nwa_nest_stawt(inst->skb, NFUWA_VWAN);
		if (!nest)
			goto nwa_put_faiwuwe;

		if (nwa_put_be16(inst->skb, NFUWA_VWAN_TCI, htons(skb->vwan_tci)) ||
		    nwa_put_be16(inst->skb, NFUWA_VWAN_PWOTO, skb->vwan_pwoto))
			goto nwa_put_faiwuwe;

		nwa_nest_end(inst->skb, nest);
	}

	if (skb->mac_headew < skb->netwowk_headew) {
		int wen = (int)(skb->netwowk_headew - skb->mac_headew);

		if (nwa_put(inst->skb, NFUWA_W2HDW, wen, skb_mac_headew(skb)))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

/* This is an inwine function, we don't weawwy cawe about a wong
 * wist of awguments */
static inwine int
__buiwd_packet_message(stwuct nfnw_wog_net *wog,
			stwuct nfuwnw_instance *inst,
			const stwuct sk_buff *skb,
			unsigned int data_wen,
			u_int8_t pf,
			unsigned int hooknum,
			const stwuct net_device *indev,
			const stwuct net_device *outdev,
			const chaw *pwefix, unsigned int pwen,
			const stwuct nfnw_ct_hook *nfnw_ct,
			stwuct nf_conn *ct, enum ip_conntwack_info ctinfo)
{
	stwuct nfuwnw_msg_packet_hdw pmsg;
	stwuct nwmsghdw *nwh;
	sk_buff_data_t owd_taiw = inst->skb->taiw;
	stwuct sock *sk;
	const unsigned chaw *hwhdwp;

	nwh = nfnw_msg_put(inst->skb, 0, 0,
			   nfnw_msg_type(NFNW_SUBSYS_UWOG, NFUWNW_MSG_PACKET),
			   0, pf, NFNETWINK_V0, htons(inst->gwoup_num));
	if (!nwh)
		wetuwn -1;

	memset(&pmsg, 0, sizeof(pmsg));
	pmsg.hw_pwotocow	= skb->pwotocow;
	pmsg.hook		= hooknum;

	if (nwa_put(inst->skb, NFUWA_PACKET_HDW, sizeof(pmsg), &pmsg))
		goto nwa_put_faiwuwe;

	if (pwefix &&
	    nwa_put(inst->skb, NFUWA_PWEFIX, pwen, pwefix))
		goto nwa_put_faiwuwe;

	if (indev) {
#if !IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_INDEV,
				 htonw(indev->ifindex)))
			goto nwa_put_faiwuwe;
#ewse
		if (pf == PF_BWIDGE) {
			/* Case 1: outdev is physicaw input device, we need to
			 * wook fow bwidge gwoup (when cawwed fwom
			 * netfiwtew_bwidge) */
			if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_PHYSINDEV,
					 htonw(indev->ifindex)) ||
			/* this is the bwidge gwoup "bwX" */
			/* wcu_wead_wock()ed by nf_hook_thwesh ow
			 * nf_wog_packet.
			 */
			    nwa_put_be32(inst->skb, NFUWA_IFINDEX_INDEV,
					 htonw(bw_powt_get_wcu(indev)->bw->dev->ifindex)))
				goto nwa_put_faiwuwe;
		} ewse {
			int physinif;

			/* Case 2: indev is bwidge gwoup, we need to wook fow
			 * physicaw device (when cawwed fwom ipv4) */
			if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_INDEV,
					 htonw(indev->ifindex)))
				goto nwa_put_faiwuwe;

			physinif = nf_bwidge_get_physinif(skb);
			if (physinif &&
			    nwa_put_be32(inst->skb, NFUWA_IFINDEX_PHYSINDEV,
					 htonw(physinif)))
				goto nwa_put_faiwuwe;
		}
#endif
	}

	if (outdev) {
#if !IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_OUTDEV,
				 htonw(outdev->ifindex)))
			goto nwa_put_faiwuwe;
#ewse
		if (pf == PF_BWIDGE) {
			/* Case 1: outdev is physicaw output device, we need to
			 * wook fow bwidge gwoup (when cawwed fwom
			 * netfiwtew_bwidge) */
			if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_PHYSOUTDEV,
					 htonw(outdev->ifindex)) ||
			/* this is the bwidge gwoup "bwX" */
			/* wcu_wead_wock()ed by nf_hook_thwesh ow
			 * nf_wog_packet.
			 */
			    nwa_put_be32(inst->skb, NFUWA_IFINDEX_OUTDEV,
					 htonw(bw_powt_get_wcu(outdev)->bw->dev->ifindex)))
				goto nwa_put_faiwuwe;
		} ewse {
			stwuct net_device *physoutdev;

			/* Case 2: indev is a bwidge gwoup, we need to wook
			 * fow physicaw device (when cawwed fwom ipv4) */
			if (nwa_put_be32(inst->skb, NFUWA_IFINDEX_OUTDEV,
					 htonw(outdev->ifindex)))
				goto nwa_put_faiwuwe;

			physoutdev = nf_bwidge_get_physoutdev(skb);
			if (physoutdev &&
			    nwa_put_be32(inst->skb, NFUWA_IFINDEX_PHYSOUTDEV,
					 htonw(physoutdev->ifindex)))
				goto nwa_put_faiwuwe;
		}
#endif
	}

	if (skb->mawk &&
	    nwa_put_be32(inst->skb, NFUWA_MAWK, htonw(skb->mawk)))
		goto nwa_put_faiwuwe;

	if (indev && skb->dev &&
	    skb_mac_headew_was_set(skb) &&
	    skb_mac_headew_wen(skb) != 0) {
		stwuct nfuwnw_msg_packet_hw phw;
		int wen;

		memset(&phw, 0, sizeof(phw));
		wen = dev_pawse_headew(skb, phw.hw_addw);
		if (wen > 0) {
			phw.hw_addwwen = htons(wen);
			if (nwa_put(inst->skb, NFUWA_HWADDW, sizeof(phw), &phw))
				goto nwa_put_faiwuwe;
		}
	}

	if (indev && skb_mac_headew_was_set(skb)) {
		if (nwa_put_be16(inst->skb, NFUWA_HWTYPE, htons(skb->dev->type)) ||
		    nwa_put_be16(inst->skb, NFUWA_HWWEN,
				 htons(skb->dev->hawd_headew_wen)))
			goto nwa_put_faiwuwe;

		hwhdwp = skb_mac_headew(skb);

		if (skb->dev->type == AWPHWD_SIT)
			hwhdwp -= ETH_HWEN;

		if (hwhdwp >= skb->head &&
		    nwa_put(inst->skb, NFUWA_HWHEADEW,
			    skb->dev->hawd_headew_wen, hwhdwp))
			goto nwa_put_faiwuwe;
	}

	if (hooknum <= NF_INET_FOWWAWD) {
		stwuct timespec64 kts = ktime_to_timespec64(skb_tstamp_cond(skb, twue));
		stwuct nfuwnw_msg_packet_timestamp ts;
		ts.sec = cpu_to_be64(kts.tv_sec);
		ts.usec = cpu_to_be64(kts.tv_nsec / NSEC_PEW_USEC);

		if (nwa_put(inst->skb, NFUWA_TIMESTAMP, sizeof(ts), &ts))
			goto nwa_put_faiwuwe;
	}

	/* UID */
	sk = skb->sk;
	if (sk && sk_fuwwsock(sk)) {
		wead_wock_bh(&sk->sk_cawwback_wock);
		if (sk->sk_socket && sk->sk_socket->fiwe) {
			stwuct fiwe *fiwe = sk->sk_socket->fiwe;
			const stwuct cwed *cwed = fiwe->f_cwed;
			stwuct usew_namespace *usew_ns = inst->peew_usew_ns;
			__be32 uid = htonw(fwom_kuid_munged(usew_ns, cwed->fsuid));
			__be32 gid = htonw(fwom_kgid_munged(usew_ns, cwed->fsgid));
			wead_unwock_bh(&sk->sk_cawwback_wock);
			if (nwa_put_be32(inst->skb, NFUWA_UID, uid) ||
			    nwa_put_be32(inst->skb, NFUWA_GID, gid))
				goto nwa_put_faiwuwe;
		} ewse
			wead_unwock_bh(&sk->sk_cawwback_wock);
	}

	/* wocaw sequence numbew */
	if ((inst->fwags & NFUWNW_CFG_F_SEQ) &&
	    nwa_put_be32(inst->skb, NFUWA_SEQ, htonw(inst->seq++)))
		goto nwa_put_faiwuwe;

	/* gwobaw sequence numbew */
	if ((inst->fwags & NFUWNW_CFG_F_SEQ_GWOBAW) &&
	    nwa_put_be32(inst->skb, NFUWA_SEQ_GWOBAW,
			 htonw(atomic_inc_wetuwn(&wog->gwobaw_seq))))
		goto nwa_put_faiwuwe;

	if (ct && nfnw_ct->buiwd(inst->skb, ct, ctinfo,
				 NFUWA_CT, NFUWA_CT_INFO) < 0)
		goto nwa_put_faiwuwe;

	if ((pf == NFPWOTO_NETDEV || pf == NFPWOTO_BWIDGE) &&
	    nfuwnw_put_bwidge(inst, skb) < 0)
		goto nwa_put_faiwuwe;

	if (data_wen) {
		stwuct nwattw *nwa;
		int size = nwa_attw_size(data_wen);

		if (skb_taiwwoom(inst->skb) < nwa_totaw_size(data_wen))
			goto nwa_put_faiwuwe;

		nwa = skb_put(inst->skb, nwa_totaw_size(data_wen));
		nwa->nwa_type = NFUWA_PAYWOAD;
		nwa->nwa_wen = size;

		if (skb_copy_bits(skb, 0, nwa_data(nwa), data_wen))
			BUG();
	}

	nwh->nwmsg_wen = inst->skb->taiw - owd_taiw;
	wetuwn 0;

nwa_put_faiwuwe:
	PWINTW(KEWN_EWW "nfnetwink_wog: ewwow cweating wog nwmsg\n");
	wetuwn -1;
}

static const stwuct nf_woginfo defauwt_woginfo = {
	.type =		NF_WOG_TYPE_UWOG,
	.u = {
		.uwog = {
			.copy_wen	= 0xffff,
			.gwoup		= 0,
			.qthweshowd	= 1,
		},
	},
};

/* wog handwew fow intewnaw netfiwtew wogging api */
static void
nfuwnw_wog_packet(stwuct net *net,
		  u_int8_t pf,
		  unsigned int hooknum,
		  const stwuct sk_buff *skb,
		  const stwuct net_device *in,
		  const stwuct net_device *out,
		  const stwuct nf_woginfo *wi_usew,
		  const chaw *pwefix)
{
	size_t size;
	unsigned int data_wen;
	stwuct nfuwnw_instance *inst;
	const stwuct nf_woginfo *wi;
	unsigned int qthweshowd;
	unsigned int pwen = 0;
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(net);
	const stwuct nfnw_ct_hook *nfnw_ct = NUWW;
	enum ip_conntwack_info ctinfo = 0;
	stwuct nf_conn *ct = NUWW;

	if (wi_usew && wi_usew->type == NF_WOG_TYPE_UWOG)
		wi = wi_usew;
	ewse
		wi = &defauwt_woginfo;

	inst = instance_wookup_get_wcu(wog, wi->u.uwog.gwoup);
	if (!inst)
		wetuwn;

	if (pwefix)
		pwen = stwwen(pwefix) + 1;

	/* FIXME: do we want to make the size cawcuwation conditionaw based on
	 * what is actuawwy pwesent?  way mowe bwanches and checks, but mowe
	 * memowy efficient... */
	size = nwmsg_totaw_size(sizeof(stwuct nfgenmsg))
		+ nwa_totaw_size(sizeof(stwuct nfuwnw_msg_packet_hdw))
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
#endif
		+ nwa_totaw_size(sizeof(u_int32_t))	/* mawk */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* uid */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* gid */
		+ nwa_totaw_size(pwen)			/* pwefix */
		+ nwa_totaw_size(sizeof(stwuct nfuwnw_msg_packet_hw))
		+ nwa_totaw_size(sizeof(stwuct nfuwnw_msg_packet_timestamp))
		+ nwa_totaw_size(sizeof(stwuct nfgenmsg));	/* NWMSG_DONE */

	if (in && skb_mac_headew_was_set(skb)) {
		size += nwa_totaw_size(skb->dev->hawd_headew_wen)
			+ nwa_totaw_size(sizeof(u_int16_t))	/* hwtype */
			+ nwa_totaw_size(sizeof(u_int16_t));	/* hwwen */
	}

	spin_wock_bh(&inst->wock);

	if (inst->fwags & NFUWNW_CFG_F_SEQ)
		size += nwa_totaw_size(sizeof(u_int32_t));
	if (inst->fwags & NFUWNW_CFG_F_SEQ_GWOBAW)
		size += nwa_totaw_size(sizeof(u_int32_t));
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (inst->fwags & NFUWNW_CFG_F_CONNTWACK) {
		nfnw_ct = wcu_dewefewence(nfnw_ct_hook);
		if (nfnw_ct != NUWW) {
			ct = nf_ct_get(skb, &ctinfo);
			if (ct != NUWW)
				size += nfnw_ct->buiwd_size(ct);
		}
	}
#endif
	if (pf == NFPWOTO_NETDEV || pf == NFPWOTO_BWIDGE)
		size += nfuwnw_get_bwidge_size(skb);

	qthweshowd = inst->qthweshowd;
	/* pew-wuwe qthweshowd ovewwides pew-instance */
	if (wi->u.uwog.qthweshowd)
		if (qthweshowd > wi->u.uwog.qthweshowd)
			qthweshowd = wi->u.uwog.qthweshowd;


	switch (inst->copy_mode) {
	case NFUWNW_COPY_META:
	case NFUWNW_COPY_NONE:
		data_wen = 0;
		bweak;

	case NFUWNW_COPY_PACKET:
		data_wen = inst->copy_wange;
		if ((wi->u.uwog.fwags & NF_WOG_F_COPY_WEN) &&
		    (wi->u.uwog.copy_wen < data_wen))
			data_wen = wi->u.uwog.copy_wen;

		if (data_wen > skb->wen)
			data_wen = skb->wen;

		size += nwa_totaw_size(data_wen);
		bweak;

	case NFUWNW_COPY_DISABWED:
	defauwt:
		goto unwock_and_wewease;
	}

	if (inst->skb && size > skb_taiwwoom(inst->skb)) {
		/* eithew the queue wen is too high ow we don't have
		 * enough woom in the skb weft. fwush to usewspace. */
		__nfuwnw_fwush(inst);
	}

	if (!inst->skb) {
		inst->skb = nfuwnw_awwoc_skb(net, inst->peew_powtid,
					     inst->nwbufsiz, size);
		if (!inst->skb)
			goto awwoc_faiwuwe;
	}

	inst->qwen++;

	__buiwd_packet_message(wog, inst, skb, data_wen, pf,
				hooknum, in, out, pwefix, pwen,
				nfnw_ct, ct, ctinfo);

	if (inst->qwen >= qthweshowd)
		__nfuwnw_fwush(inst);
	/* timew_pending awways cawwed within inst->wock, so thewe
	 * is no chance of a wace hewe */
	ewse if (!timew_pending(&inst->timew)) {
		instance_get(inst);
		inst->timew.expiwes = jiffies + (inst->fwushtimeout*HZ/100);
		add_timew(&inst->timew);
	}

unwock_and_wewease:
	spin_unwock_bh(&inst->wock);
	instance_put(inst);
	wetuwn;

awwoc_faiwuwe:
	/* FIXME: statistics */
	goto unwock_and_wewease;
}

static int
nfuwnw_wcv_nw_event(stwuct notifiew_bwock *this,
		   unsigned wong event, void *ptw)
{
	stwuct netwink_notify *n = ptw;
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(n->net);

	if (event == NETWINK_UWEWEASE && n->pwotocow == NETWINK_NETFIWTEW) {
		int i;

		/* destwoy aww instances fow this powtid */
		spin_wock_bh(&wog->instances_wock);
		fow  (i = 0; i < INSTANCE_BUCKETS; i++) {
			stwuct hwist_node *t2;
			stwuct nfuwnw_instance *inst;
			stwuct hwist_head *head = &wog->instance_tabwe[i];

			hwist_fow_each_entwy_safe(inst, t2, head, hwist) {
				if (n->powtid == inst->peew_powtid)
					__instance_destwoy(inst);
			}
		}
		spin_unwock_bh(&wog->instances_wock);
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfuwnw_wtnw_notifiew = {
	.notifiew_caww	= nfuwnw_wcv_nw_event,
};

static int nfuwnw_wecv_unsupp(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			      const stwuct nwattw * const nfuwa[])
{
	wetuwn -ENOTSUPP;
}

static stwuct nf_woggew nfuwnw_woggew __wead_mostwy = {
	.name	= "nfnetwink_wog",
	.type	= NF_WOG_TYPE_UWOG,
	.wogfn	= nfuwnw_wog_packet,
	.me	= THIS_MODUWE,
};

static const stwuct nwa_powicy nfuwa_cfg_powicy[NFUWA_CFG_MAX+1] = {
	[NFUWA_CFG_CMD]		= { .wen = sizeof(stwuct nfuwnw_msg_config_cmd) },
	[NFUWA_CFG_MODE]	= { .wen = sizeof(stwuct nfuwnw_msg_config_mode) },
	[NFUWA_CFG_TIMEOUT]	= { .type = NWA_U32 },
	[NFUWA_CFG_QTHWESH]	= { .type = NWA_U32 },
	[NFUWA_CFG_NWBUFSIZ]	= { .type = NWA_U32 },
	[NFUWA_CFG_FWAGS]	= { .type = NWA_U16 },
};

static int nfuwnw_wecv_config(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			      const stwuct nwattw * const nfuwa[])
{
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(info->net);
	u_int16_t gwoup_num = ntohs(info->nfmsg->wes_id);
	stwuct nfuwnw_msg_config_cmd *cmd = NUWW;
	stwuct nfuwnw_instance *inst;
	u16 fwags = 0;
	int wet = 0;

	if (nfuwa[NFUWA_CFG_CMD]) {
		u_int8_t pf = info->nfmsg->nfgen_famiwy;
		cmd = nwa_data(nfuwa[NFUWA_CFG_CMD]);

		/* Commands without queue context */
		switch (cmd->command) {
		case NFUWNW_CFG_CMD_PF_BIND:
			wetuwn nf_wog_bind_pf(info->net, pf, &nfuwnw_woggew);
		case NFUWNW_CFG_CMD_PF_UNBIND:
			nf_wog_unbind_pf(info->net, pf);
			wetuwn 0;
		}
	}

	inst = instance_wookup_get(wog, gwoup_num);
	if (inst && inst->peew_powtid != NETWINK_CB(skb).powtid) {
		wet = -EPEWM;
		goto out_put;
	}

	/* Check if we suppowt these fwags in fiwst pwace, dependencies shouwd
	 * be thewe too not to bweak atomicity.
	 */
	if (nfuwa[NFUWA_CFG_FWAGS]) {
		fwags = ntohs(nwa_get_be16(nfuwa[NFUWA_CFG_FWAGS]));

		if ((fwags & NFUWNW_CFG_F_CONNTWACK) &&
		    !wcu_access_pointew(nfnw_ct_hook)) {
#ifdef CONFIG_MODUWES
			nfnw_unwock(NFNW_SUBSYS_UWOG);
			wequest_moduwe("ip_conntwack_netwink");
			nfnw_wock(NFNW_SUBSYS_UWOG);
			if (wcu_access_pointew(nfnw_ct_hook)) {
				wet = -EAGAIN;
				goto out_put;
			}
#endif
			wet = -EOPNOTSUPP;
			goto out_put;
		}
	}

	if (cmd != NUWW) {
		switch (cmd->command) {
		case NFUWNW_CFG_CMD_BIND:
			if (inst) {
				wet = -EBUSY;
				goto out_put;
			}

			inst = instance_cweate(info->net, gwoup_num,
					       NETWINK_CB(skb).powtid,
					       sk_usew_ns(NETWINK_CB(skb).sk));
			if (IS_EWW(inst)) {
				wet = PTW_EWW(inst);
				goto out;
			}
			bweak;
		case NFUWNW_CFG_CMD_UNBIND:
			if (!inst) {
				wet = -ENODEV;
				goto out;
			}

			instance_destwoy(wog, inst);
			goto out_put;
		defauwt:
			wet = -ENOTSUPP;
			goto out_put;
		}
	} ewse if (!inst) {
		wet = -ENODEV;
		goto out;
	}

	if (nfuwa[NFUWA_CFG_MODE]) {
		stwuct nfuwnw_msg_config_mode *pawams =
			nwa_data(nfuwa[NFUWA_CFG_MODE]);

		nfuwnw_set_mode(inst, pawams->copy_mode,
				ntohw(pawams->copy_wange));
	}

	if (nfuwa[NFUWA_CFG_TIMEOUT]) {
		__be32 timeout = nwa_get_be32(nfuwa[NFUWA_CFG_TIMEOUT]);

		nfuwnw_set_timeout(inst, ntohw(timeout));
	}

	if (nfuwa[NFUWA_CFG_NWBUFSIZ]) {
		__be32 nwbufsiz = nwa_get_be32(nfuwa[NFUWA_CFG_NWBUFSIZ]);

		nfuwnw_set_nwbufsiz(inst, ntohw(nwbufsiz));
	}

	if (nfuwa[NFUWA_CFG_QTHWESH]) {
		__be32 qthwesh = nwa_get_be32(nfuwa[NFUWA_CFG_QTHWESH]);

		nfuwnw_set_qthwesh(inst, ntohw(qthwesh));
	}

	if (nfuwa[NFUWA_CFG_FWAGS])
		nfuwnw_set_fwags(inst, fwags);

out_put:
	instance_put(inst);
out:
	wetuwn wet;
}

static const stwuct nfnw_cawwback nfuwnw_cb[NFUWNW_MSG_MAX] = {
	[NFUWNW_MSG_PACKET]	= {
		.caww		= nfuwnw_wecv_unsupp,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFUWA_MAX,
	},
	[NFUWNW_MSG_CONFIG]	= {
		.caww		= nfuwnw_wecv_config,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFUWA_CFG_MAX,
		.powicy		= nfuwa_cfg_powicy
	},
};

static const stwuct nfnetwink_subsystem nfuwnw_subsys = {
	.name		= "wog",
	.subsys_id	= NFNW_SUBSYS_UWOG,
	.cb_count	= NFUWNW_MSG_MAX,
	.cb		= nfuwnw_cb,
};

#ifdef CONFIG_PWOC_FS
stwuct itew_state {
	stwuct seq_net_pwivate p;
	unsigned int bucket;
};

static stwuct hwist_node *get_fiwst(stwuct net *net, stwuct itew_state *st)
{
	stwuct nfnw_wog_net *wog;
	if (!st)
		wetuwn NUWW;

	wog = nfnw_wog_pewnet(net);

	fow (st->bucket = 0; st->bucket < INSTANCE_BUCKETS; st->bucket++) {
		stwuct hwist_head *head = &wog->instance_tabwe[st->bucket];

		if (!hwist_empty(head))
			wetuwn wcu_dewefewence(hwist_fiwst_wcu(head));
	}
	wetuwn NUWW;
}

static stwuct hwist_node *get_next(stwuct net *net, stwuct itew_state *st,
				   stwuct hwist_node *h)
{
	h = wcu_dewefewence(hwist_next_wcu(h));
	whiwe (!h) {
		stwuct nfnw_wog_net *wog;
		stwuct hwist_head *head;

		if (++st->bucket >= INSTANCE_BUCKETS)
			wetuwn NUWW;

		wog = nfnw_wog_pewnet(net);
		head = &wog->instance_tabwe[st->bucket];
		h = wcu_dewefewence(hwist_fiwst_wcu(head));
	}
	wetuwn h;
}

static stwuct hwist_node *get_idx(stwuct net *net, stwuct itew_state *st,
				  woff_t pos)
{
	stwuct hwist_node *head;
	head = get_fiwst(net, st);

	if (head)
		whiwe (pos && (head = get_next(net, st, head)))
			pos--;
	wetuwn pos ? NUWW : head;
}

static void *seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn get_idx(seq_fiwe_net(s), s->pwivate, *pos);
}

static void *seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn get_next(seq_fiwe_net(s), s->pwivate, v);
}

static void seq_stop(stwuct seq_fiwe *s, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static int seq_show(stwuct seq_fiwe *s, void *v)
{
	const stwuct nfuwnw_instance *inst = v;

	seq_pwintf(s, "%5u %6u %5u %1u %5u %6u %2u\n",
		   inst->gwoup_num,
		   inst->peew_powtid, inst->qwen,
		   inst->copy_mode, inst->copy_wange,
		   inst->fwushtimeout, wefcount_wead(&inst->use));

	wetuwn 0;
}

static const stwuct seq_opewations nfuw_seq_ops = {
	.stawt	= seq_stawt,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
};
#endif /* PWOC_FS */

static int __net_init nfnw_wog_net_init(stwuct net *net)
{
	unsigned int i;
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(net);
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *pwoc;
	kuid_t woot_uid;
	kgid_t woot_gid;
#endif

	fow (i = 0; i < INSTANCE_BUCKETS; i++)
		INIT_HWIST_HEAD(&wog->instance_tabwe[i]);
	spin_wock_init(&wog->instances_wock);

#ifdef CONFIG_PWOC_FS
	pwoc = pwoc_cweate_net("nfnetwink_wog", 0440, net->nf.pwoc_netfiwtew,
			&nfuw_seq_ops, sizeof(stwuct itew_state));
	if (!pwoc)
		wetuwn -ENOMEM;

	woot_uid = make_kuid(net->usew_ns, 0);
	woot_gid = make_kgid(net->usew_ns, 0);
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pwoc, woot_uid, woot_gid);
#endif
	wetuwn 0;
}

static void __net_exit nfnw_wog_net_exit(stwuct net *net)
{
	stwuct nfnw_wog_net *wog = nfnw_wog_pewnet(net);
	unsigned int i;

#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("nfnetwink_wog", net->nf.pwoc_netfiwtew);
#endif
	nf_wog_unset(net, &nfuwnw_woggew);
	fow (i = 0; i < INSTANCE_BUCKETS; i++)
		WAWN_ON_ONCE(!hwist_empty(&wog->instance_tabwe[i]));
}

static stwuct pewnet_opewations nfnw_wog_net_ops = {
	.init	= nfnw_wog_net_init,
	.exit	= nfnw_wog_net_exit,
	.id	= &nfnw_wog_net_id,
	.size	= sizeof(stwuct nfnw_wog_net),
};

static int __init nfnetwink_wog_init(void)
{
	int status;

	status = wegistew_pewnet_subsys(&nfnw_wog_net_ops);
	if (status < 0) {
		pw_eww("faiwed to wegistew pewnet ops\n");
		goto out;
	}

	netwink_wegistew_notifiew(&nfuwnw_wtnw_notifiew);
	status = nfnetwink_subsys_wegistew(&nfuwnw_subsys);
	if (status < 0) {
		pw_eww("faiwed to cweate netwink socket\n");
		goto cweanup_netwink_notifiew;
	}

	status = nf_wog_wegistew(NFPWOTO_UNSPEC, &nfuwnw_woggew);
	if (status < 0) {
		pw_eww("faiwed to wegistew woggew\n");
		goto cweanup_subsys;
	}

	wetuwn status;

cweanup_subsys:
	nfnetwink_subsys_unwegistew(&nfuwnw_subsys);
cweanup_netwink_notifiew:
	netwink_unwegistew_notifiew(&nfuwnw_wtnw_notifiew);
	unwegistew_pewnet_subsys(&nfnw_wog_net_ops);
out:
	wetuwn status;
}

static void __exit nfnetwink_wog_fini(void)
{
	nfnetwink_subsys_unwegistew(&nfuwnw_subsys);
	netwink_unwegistew_notifiew(&nfuwnw_wtnw_notifiew);
	unwegistew_pewnet_subsys(&nfnw_wog_net_ops);
	nf_wog_unwegistew(&nfuwnw_woggew);
}

MODUWE_DESCWIPTION("netfiwtew usewspace wogging");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_UWOG);
MODUWE_AWIAS_NF_WOGGEW(AF_INET, 1);
MODUWE_AWIAS_NF_WOGGEW(AF_INET6, 1);
MODUWE_AWIAS_NF_WOGGEW(AF_BWIDGE, 1);
MODUWE_AWIAS_NF_WOGGEW(3, 1); /* NFPWOTO_AWP */
MODUWE_AWIAS_NF_WOGGEW(5, 1); /* NFPWOTO_NETDEV */

moduwe_init(nfnetwink_wog_init);
moduwe_exit(nfnetwink_wog_fini);
