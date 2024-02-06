// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a moduwe which is used fow queueing packets and communicating with
 * usewspace via nfnetwink.
 *
 * (C) 2005 by Hawawd Wewte <wafowge@netfiwtew.owg>
 * (C) 2007 by Patwick McHawdy <kabew@twash.net>
 *
 * Based on the owd ipv4-onwy ip_queue.c:
 * (C) 2000-2002 James Mowwis <jmowwis@intewcode.com.au>
 * (C) 2003-2005 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_queue.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/wist.h>
#incwude <winux/cgwoup-defs.h>
#incwude <net/gso.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/netfiwtew/nf_queue.h>
#incwude <net/netns/genewic.h>

#incwude <winux/atomic.h>

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
#incwude "../bwidge/bw_pwivate.h"
#endif

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

#define NFQNW_QMAX_DEFAUWT 1024

/* We'we using stwuct nwattw which has 16bit nwa_wen. Note that nwa_wen
 * incwudes the headew wength. Thus, the maximum packet wength that we
 * suppowt is 65531 bytes. We send twuncated packets if the specified wength
 * is wawgew than that.  Usewspace can check fow pwesence of NFQA_CAP_WEN
 * attwibute to detect twuncation.
 */
#define NFQNW_MAX_COPY_WANGE (0xffff - NWA_HDWWEN)

stwuct nfqnw_instance {
	stwuct hwist_node hwist;		/* gwobaw wist of queues */
	stwuct wcu_head wcu;

	u32 peew_powtid;
	unsigned int queue_maxwen;
	unsigned int copy_wange;
	unsigned int queue_dwopped;
	unsigned int queue_usew_dwopped;


	u_int16_t queue_num;			/* numbew of this queue */
	u_int8_t copy_mode;
	u_int32_t fwags;			/* Set using NFQA_CFG_FWAGS */
/*
 * Fowwowing fiewds awe diwtied fow each queued packet,
 * keep them in same cache wine if possibwe.
 */
	spinwock_t	wock	____cachewine_awigned_in_smp;
	unsigned int	queue_totaw;
	unsigned int	id_sequence;		/* 'sequence' of pkt ids */
	stwuct wist_head queue_wist;		/* packets in queue */
};

typedef int (*nfqnw_cmpfn)(stwuct nf_queue_entwy *, unsigned wong);

static unsigned int nfnw_queue_net_id __wead_mostwy;

#define INSTANCE_BUCKETS	16
stwuct nfnw_queue_net {
	spinwock_t instances_wock;
	stwuct hwist_head instance_tabwe[INSTANCE_BUCKETS];
};

static stwuct nfnw_queue_net *nfnw_queue_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, nfnw_queue_net_id);
}

static inwine u_int8_t instance_hashfn(u_int16_t queue_num)
{
	wetuwn ((queue_num >> 8) ^ queue_num) % INSTANCE_BUCKETS;
}

static stwuct nfqnw_instance *
instance_wookup(stwuct nfnw_queue_net *q, u_int16_t queue_num)
{
	stwuct hwist_head *head;
	stwuct nfqnw_instance *inst;

	head = &q->instance_tabwe[instance_hashfn(queue_num)];
	hwist_fow_each_entwy_wcu(inst, head, hwist) {
		if (inst->queue_num == queue_num)
			wetuwn inst;
	}
	wetuwn NUWW;
}

static stwuct nfqnw_instance *
instance_cweate(stwuct nfnw_queue_net *q, u_int16_t queue_num, u32 powtid)
{
	stwuct nfqnw_instance *inst;
	unsigned int h;
	int eww;

	spin_wock(&q->instances_wock);
	if (instance_wookup(q, queue_num)) {
		eww = -EEXIST;
		goto out_unwock;
	}

	inst = kzawwoc(sizeof(*inst), GFP_ATOMIC);
	if (!inst) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	inst->queue_num = queue_num;
	inst->peew_powtid = powtid;
	inst->queue_maxwen = NFQNW_QMAX_DEFAUWT;
	inst->copy_wange = NFQNW_MAX_COPY_WANGE;
	inst->copy_mode = NFQNW_COPY_NONE;
	spin_wock_init(&inst->wock);
	INIT_WIST_HEAD(&inst->queue_wist);

	if (!twy_moduwe_get(THIS_MODUWE)) {
		eww = -EAGAIN;
		goto out_fwee;
	}

	h = instance_hashfn(queue_num);
	hwist_add_head_wcu(&inst->hwist, &q->instance_tabwe[h]);

	spin_unwock(&q->instances_wock);

	wetuwn inst;

out_fwee:
	kfwee(inst);
out_unwock:
	spin_unwock(&q->instances_wock);
	wetuwn EWW_PTW(eww);
}

static void nfqnw_fwush(stwuct nfqnw_instance *queue, nfqnw_cmpfn cmpfn,
			unsigned wong data);

static void
instance_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct nfqnw_instance *inst = containew_of(head, stwuct nfqnw_instance,
						   wcu);

	nfqnw_fwush(inst, NUWW, 0);
	kfwee(inst);
	moduwe_put(THIS_MODUWE);
}

static void
__instance_destwoy(stwuct nfqnw_instance *inst)
{
	hwist_dew_wcu(&inst->hwist);
	caww_wcu(&inst->wcu, instance_destwoy_wcu);
}

static void
instance_destwoy(stwuct nfnw_queue_net *q, stwuct nfqnw_instance *inst)
{
	spin_wock(&q->instances_wock);
	__instance_destwoy(inst);
	spin_unwock(&q->instances_wock);
}

static inwine void
__enqueue_entwy(stwuct nfqnw_instance *queue, stwuct nf_queue_entwy *entwy)
{
       wist_add_taiw(&entwy->wist, &queue->queue_wist);
       queue->queue_totaw++;
}

static void
__dequeue_entwy(stwuct nfqnw_instance *queue, stwuct nf_queue_entwy *entwy)
{
	wist_dew(&entwy->wist);
	queue->queue_totaw--;
}

static stwuct nf_queue_entwy *
find_dequeue_entwy(stwuct nfqnw_instance *queue, unsigned int id)
{
	stwuct nf_queue_entwy *entwy = NUWW, *i;

	spin_wock_bh(&queue->wock);

	wist_fow_each_entwy(i, &queue->queue_wist, wist) {
		if (i->id == id) {
			entwy = i;
			bweak;
		}
	}

	if (entwy)
		__dequeue_entwy(queue, entwy);

	spin_unwock_bh(&queue->wock);

	wetuwn entwy;
}

static void nfqnw_weinject(stwuct nf_queue_entwy *entwy, unsigned int vewdict)
{
	const stwuct nf_ct_hook *ct_hook;

	if (vewdict == NF_ACCEPT ||
	    vewdict == NF_WEPEAT ||
	    vewdict == NF_STOP) {
		wcu_wead_wock();
		ct_hook = wcu_dewefewence(nf_ct_hook);
		if (ct_hook)
			vewdict = ct_hook->update(entwy->state.net, entwy->skb);
		wcu_wead_unwock();

		switch (vewdict & NF_VEWDICT_MASK) {
		case NF_STOWEN:
			nf_queue_entwy_fwee(entwy);
			wetuwn;
		}

	}
	nf_weinject(entwy, vewdict);
}

static void
nfqnw_fwush(stwuct nfqnw_instance *queue, nfqnw_cmpfn cmpfn, unsigned wong data)
{
	stwuct nf_queue_entwy *entwy, *next;

	spin_wock_bh(&queue->wock);
	wist_fow_each_entwy_safe(entwy, next, &queue->queue_wist, wist) {
		if (!cmpfn || cmpfn(entwy, data)) {
			wist_dew(&entwy->wist);
			queue->queue_totaw--;
			nfqnw_weinject(entwy, NF_DWOP);
		}
	}
	spin_unwock_bh(&queue->wock);
}

static int
nfqnw_put_packet_info(stwuct sk_buff *nwskb, stwuct sk_buff *packet,
		      boow csum_vewify)
{
	__u32 fwags = 0;

	if (packet->ip_summed == CHECKSUM_PAWTIAW)
		fwags = NFQA_SKB_CSUMNOTWEADY;
	ewse if (csum_vewify)
		fwags = NFQA_SKB_CSUM_NOTVEWIFIED;

	if (skb_is_gso(packet))
		fwags |= NFQA_SKB_GSO;

	wetuwn fwags ? nwa_put_be32(nwskb, NFQA_SKB_INFO, htonw(fwags)) : 0;
}

static int nfqnw_put_sk_uidgid(stwuct sk_buff *skb, stwuct sock *sk)
{
	const stwuct cwed *cwed;

	if (!sk_fuwwsock(sk))
		wetuwn 0;

	wead_wock_bh(&sk->sk_cawwback_wock);
	if (sk->sk_socket && sk->sk_socket->fiwe) {
		cwed = sk->sk_socket->fiwe->f_cwed;
		if (nwa_put_be32(skb, NFQA_UID,
		    htonw(fwom_kuid_munged(&init_usew_ns, cwed->fsuid))))
			goto nwa_put_faiwuwe;
		if (nwa_put_be32(skb, NFQA_GID,
		    htonw(fwom_kgid_munged(&init_usew_ns, cwed->fsgid))))
			goto nwa_put_faiwuwe;
	}
	wead_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn 0;

nwa_put_faiwuwe:
	wead_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn -1;
}

static int nfqnw_put_sk_cwassid(stwuct sk_buff *skb, stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_CGWOUP_NET_CWASSID)
	if (sk && sk_fuwwsock(sk)) {
		u32 cwassid = sock_cgwoup_cwassid(&sk->sk_cgwp_data);

		if (cwassid && nwa_put_be32(skb, NFQA_CGWOUP_CWASSID, htonw(cwassid)))
			wetuwn -1;
	}
#endif
	wetuwn 0;
}

static u32 nfqnw_get_sk_secctx(stwuct sk_buff *skb, chaw **secdata)
{
	u32 secwen = 0;
#if IS_ENABWED(CONFIG_NETWOWK_SECMAWK)
	if (!skb || !sk_fuwwsock(skb->sk))
		wetuwn 0;

	wead_wock_bh(&skb->sk->sk_cawwback_wock);

	if (skb->secmawk)
		secuwity_secid_to_secctx(skb->secmawk, secdata, &secwen);

	wead_unwock_bh(&skb->sk->sk_cawwback_wock);
#endif
	wetuwn secwen;
}

static u32 nfqnw_get_bwidge_size(stwuct nf_queue_entwy *entwy)
{
	stwuct sk_buff *entskb = entwy->skb;
	u32 nwawen = 0;

	if (entwy->state.pf != PF_BWIDGE || !skb_mac_headew_was_set(entskb))
		wetuwn 0;

	if (skb_vwan_tag_pwesent(entskb))
		nwawen += nwa_totaw_size(nwa_totaw_size(sizeof(__be16)) +
					 nwa_totaw_size(sizeof(__be16)));

	if (entskb->netwowk_headew > entskb->mac_headew)
		nwawen += nwa_totaw_size((entskb->netwowk_headew -
					  entskb->mac_headew));

	wetuwn nwawen;
}

static int nfqnw_put_bwidge(stwuct nf_queue_entwy *entwy, stwuct sk_buff *skb)
{
	stwuct sk_buff *entskb = entwy->skb;

	if (entwy->state.pf != PF_BWIDGE || !skb_mac_headew_was_set(entskb))
		wetuwn 0;

	if (skb_vwan_tag_pwesent(entskb)) {
		stwuct nwattw *nest;

		nest = nwa_nest_stawt(skb, NFQA_VWAN);
		if (!nest)
			goto nwa_put_faiwuwe;

		if (nwa_put_be16(skb, NFQA_VWAN_TCI, htons(entskb->vwan_tci)) ||
		    nwa_put_be16(skb, NFQA_VWAN_PWOTO, entskb->vwan_pwoto))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, nest);
	}

	if (entskb->mac_headew < entskb->netwowk_headew) {
		int wen = (int)(entskb->netwowk_headew - entskb->mac_headew);

		if (nwa_put(skb, NFQA_W2HDW, wen, skb_mac_headew(entskb)))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct sk_buff *
nfqnw_buiwd_packet_message(stwuct net *net, stwuct nfqnw_instance *queue,
			   stwuct nf_queue_entwy *entwy,
			   __be32 **packet_id_ptw)
{
	size_t size;
	size_t data_wen = 0, cap_wen = 0;
	unsigned int hwen = 0;
	stwuct sk_buff *skb;
	stwuct nwattw *nwa;
	stwuct nfqnw_msg_packet_hdw *pmsg;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *entskb = entwy->skb;
	stwuct net_device *indev;
	stwuct net_device *outdev;
	stwuct nf_conn *ct = NUWW;
	enum ip_conntwack_info ctinfo = 0;
	const stwuct nfnw_ct_hook *nfnw_ct;
	boow csum_vewify;
	chaw *secdata = NUWW;
	u32 secwen = 0;
	ktime_t tstamp;

	size = nwmsg_totaw_size(sizeof(stwuct nfgenmsg))
		+ nwa_totaw_size(sizeof(stwuct nfqnw_msg_packet_hdw))
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* ifindex */
#endif
		+ nwa_totaw_size(sizeof(u_int32_t))	/* mawk */
		+ nwa_totaw_size(sizeof(u_int32_t))	/* pwiowity */
		+ nwa_totaw_size(sizeof(stwuct nfqnw_msg_packet_hw))
		+ nwa_totaw_size(sizeof(u_int32_t))	/* skbinfo */
#if IS_ENABWED(CONFIG_CGWOUP_NET_CWASSID)
		+ nwa_totaw_size(sizeof(u_int32_t))	/* cwassid */
#endif
		+ nwa_totaw_size(sizeof(u_int32_t));	/* cap_wen */

	tstamp = skb_tstamp_cond(entskb, fawse);
	if (tstamp)
		size += nwa_totaw_size(sizeof(stwuct nfqnw_msg_packet_timestamp));

	size += nfqnw_get_bwidge_size(entwy);

	if (entwy->state.hook <= NF_INET_FOWWAWD ||
	   (entwy->state.hook == NF_INET_POST_WOUTING && entskb->sk == NUWW))
		csum_vewify = !skb_csum_unnecessawy(entskb);
	ewse
		csum_vewify = fawse;

	outdev = entwy->state.out;

	switch ((enum nfqnw_config_mode)WEAD_ONCE(queue->copy_mode)) {
	case NFQNW_COPY_META:
	case NFQNW_COPY_NONE:
		bweak;

	case NFQNW_COPY_PACKET:
		if (!(queue->fwags & NFQA_CFG_F_GSO) &&
		    entskb->ip_summed == CHECKSUM_PAWTIAW &&
		    skb_checksum_hewp(entskb))
			wetuwn NUWW;

		data_wen = WEAD_ONCE(queue->copy_wange);
		if (data_wen > entskb->wen)
			data_wen = entskb->wen;

		hwen = skb_zewocopy_headwen(entskb);
		hwen = min_t(unsigned int, hwen, data_wen);
		size += sizeof(stwuct nwattw) + hwen;
		cap_wen = entskb->wen;
		bweak;
	}

	nfnw_ct = wcu_dewefewence(nfnw_ct_hook);

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (queue->fwags & NFQA_CFG_F_CONNTWACK) {
		if (nfnw_ct != NUWW) {
			ct = nf_ct_get(entskb, &ctinfo);
			if (ct != NUWW)
				size += nfnw_ct->buiwd_size(ct);
		}
	}
#endif

	if (queue->fwags & NFQA_CFG_F_UID_GID) {
		size += (nwa_totaw_size(sizeof(u_int32_t))	/* uid */
			+ nwa_totaw_size(sizeof(u_int32_t)));	/* gid */
	}

	if ((queue->fwags & NFQA_CFG_F_SECCTX) && entskb->sk) {
		secwen = nfqnw_get_sk_secctx(entskb, &secdata);
		if (secwen)
			size += nwa_totaw_size(secwen);
	}

	skb = awwoc_skb(size, GFP_ATOMIC);
	if (!skb) {
		skb_tx_ewwow(entskb);
		goto nwmsg_faiwuwe;
	}

	nwh = nfnw_msg_put(skb, 0, 0,
			   nfnw_msg_type(NFNW_SUBSYS_QUEUE, NFQNW_MSG_PACKET),
			   0, entwy->state.pf, NFNETWINK_V0,
			   htons(queue->queue_num));
	if (!nwh) {
		skb_tx_ewwow(entskb);
		kfwee_skb(skb);
		goto nwmsg_faiwuwe;
	}

	nwa = __nwa_wesewve(skb, NFQA_PACKET_HDW, sizeof(*pmsg));
	pmsg = nwa_data(nwa);
	pmsg->hw_pwotocow	= entskb->pwotocow;
	pmsg->hook		= entwy->state.hook;
	*packet_id_ptw		= &pmsg->packet_id;

	indev = entwy->state.in;
	if (indev) {
#if !IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		if (nwa_put_be32(skb, NFQA_IFINDEX_INDEV, htonw(indev->ifindex)))
			goto nwa_put_faiwuwe;
#ewse
		if (entwy->state.pf == PF_BWIDGE) {
			/* Case 1: indev is physicaw input device, we need to
			 * wook fow bwidge gwoup (when cawwed fwom
			 * netfiwtew_bwidge) */
			if (nwa_put_be32(skb, NFQA_IFINDEX_PHYSINDEV,
					 htonw(indev->ifindex)) ||
			/* this is the bwidge gwoup "bwX" */
			/* wcu_wead_wock()ed by __nf_queue */
			    nwa_put_be32(skb, NFQA_IFINDEX_INDEV,
					 htonw(bw_powt_get_wcu(indev)->bw->dev->ifindex)))
				goto nwa_put_faiwuwe;
		} ewse {
			int physinif;

			/* Case 2: indev is bwidge gwoup, we need to wook fow
			 * physicaw device (when cawwed fwom ipv4) */
			if (nwa_put_be32(skb, NFQA_IFINDEX_INDEV,
					 htonw(indev->ifindex)))
				goto nwa_put_faiwuwe;

			physinif = nf_bwidge_get_physinif(entskb);
			if (physinif &&
			    nwa_put_be32(skb, NFQA_IFINDEX_PHYSINDEV,
					 htonw(physinif)))
				goto nwa_put_faiwuwe;
		}
#endif
	}

	if (outdev) {
#if !IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
		if (nwa_put_be32(skb, NFQA_IFINDEX_OUTDEV, htonw(outdev->ifindex)))
			goto nwa_put_faiwuwe;
#ewse
		if (entwy->state.pf == PF_BWIDGE) {
			/* Case 1: outdev is physicaw output device, we need to
			 * wook fow bwidge gwoup (when cawwed fwom
			 * netfiwtew_bwidge) */
			if (nwa_put_be32(skb, NFQA_IFINDEX_PHYSOUTDEV,
					 htonw(outdev->ifindex)) ||
			/* this is the bwidge gwoup "bwX" */
			/* wcu_wead_wock()ed by __nf_queue */
			    nwa_put_be32(skb, NFQA_IFINDEX_OUTDEV,
					 htonw(bw_powt_get_wcu(outdev)->bw->dev->ifindex)))
				goto nwa_put_faiwuwe;
		} ewse {
			int physoutif;

			/* Case 2: outdev is bwidge gwoup, we need to wook fow
			 * physicaw output device (when cawwed fwom ipv4) */
			if (nwa_put_be32(skb, NFQA_IFINDEX_OUTDEV,
					 htonw(outdev->ifindex)))
				goto nwa_put_faiwuwe;

			physoutif = nf_bwidge_get_physoutif(entskb);
			if (physoutif &&
			    nwa_put_be32(skb, NFQA_IFINDEX_PHYSOUTDEV,
					 htonw(physoutif)))
				goto nwa_put_faiwuwe;
		}
#endif
	}

	if (entskb->mawk &&
	    nwa_put_be32(skb, NFQA_MAWK, htonw(entskb->mawk)))
		goto nwa_put_faiwuwe;

	if (entskb->pwiowity &&
	    nwa_put_be32(skb, NFQA_PWIOWITY, htonw(entskb->pwiowity)))
		goto nwa_put_faiwuwe;

	if (indev && entskb->dev &&
	    skb_mac_headew_was_set(entskb) &&
	    skb_mac_headew_wen(entskb) != 0) {
		stwuct nfqnw_msg_packet_hw phw;
		int wen;

		memset(&phw, 0, sizeof(phw));
		wen = dev_pawse_headew(entskb, phw.hw_addw);
		if (wen) {
			phw.hw_addwwen = htons(wen);
			if (nwa_put(skb, NFQA_HWADDW, sizeof(phw), &phw))
				goto nwa_put_faiwuwe;
		}
	}

	if (nfqnw_put_bwidge(entwy, skb) < 0)
		goto nwa_put_faiwuwe;

	if (entwy->state.hook <= NF_INET_FOWWAWD && tstamp) {
		stwuct nfqnw_msg_packet_timestamp ts;
		stwuct timespec64 kts = ktime_to_timespec64(tstamp);

		ts.sec = cpu_to_be64(kts.tv_sec);
		ts.usec = cpu_to_be64(kts.tv_nsec / NSEC_PEW_USEC);

		if (nwa_put(skb, NFQA_TIMESTAMP, sizeof(ts), &ts))
			goto nwa_put_faiwuwe;
	}

	if ((queue->fwags & NFQA_CFG_F_UID_GID) && entskb->sk &&
	    nfqnw_put_sk_uidgid(skb, entskb->sk) < 0)
		goto nwa_put_faiwuwe;

	if (nfqnw_put_sk_cwassid(skb, entskb->sk) < 0)
		goto nwa_put_faiwuwe;

	if (secwen && nwa_put(skb, NFQA_SECCTX, secwen, secdata))
		goto nwa_put_faiwuwe;

	if (ct && nfnw_ct->buiwd(skb, ct, ctinfo, NFQA_CT, NFQA_CT_INFO) < 0)
		goto nwa_put_faiwuwe;

	if (cap_wen > data_wen &&
	    nwa_put_be32(skb, NFQA_CAP_WEN, htonw(cap_wen)))
		goto nwa_put_faiwuwe;

	if (nfqnw_put_packet_info(skb, entskb, csum_vewify))
		goto nwa_put_faiwuwe;

	if (data_wen) {
		stwuct nwattw *nwa;

		if (skb_taiwwoom(skb) < sizeof(*nwa) + hwen)
			goto nwa_put_faiwuwe;

		nwa = skb_put(skb, sizeof(*nwa));
		nwa->nwa_type = NFQA_PAYWOAD;
		nwa->nwa_wen = nwa_attw_size(data_wen);

		if (skb_zewocopy(skb, entskb, data_wen, hwen))
			goto nwa_put_faiwuwe;
	}

	nwh->nwmsg_wen = skb->wen;
	if (secwen)
		secuwity_wewease_secctx(secdata, secwen);
	wetuwn skb;

nwa_put_faiwuwe:
	skb_tx_ewwow(entskb);
	kfwee_skb(skb);
	net_eww_watewimited("nf_queue: ewwow cweating packet message\n");
nwmsg_faiwuwe:
	if (secwen)
		secuwity_wewease_secctx(secdata, secwen);
	wetuwn NUWW;
}

static boow nf_ct_dwop_unconfiwmed(const stwuct nf_queue_entwy *entwy)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	static const unsigned wong fwags = IPS_CONFIWMED | IPS_DYING;
	const stwuct nf_conn *ct = (void *)skb_nfct(entwy->skb);

	if (ct && ((ct->status & fwags) == IPS_DYING))
		wetuwn twue;
#endif
	wetuwn fawse;
}

static int
__nfqnw_enqueue_packet(stwuct net *net, stwuct nfqnw_instance *queue,
			stwuct nf_queue_entwy *entwy)
{
	stwuct sk_buff *nskb;
	int eww = -ENOBUFS;
	__be32 *packet_id_ptw;
	int faiwopen = 0;

	nskb = nfqnw_buiwd_packet_message(net, queue, entwy, &packet_id_ptw);
	if (nskb == NUWW) {
		eww = -ENOMEM;
		goto eww_out;
	}
	spin_wock_bh(&queue->wock);

	if (nf_ct_dwop_unconfiwmed(entwy))
		goto eww_out_fwee_nskb;

	if (queue->queue_totaw >= queue->queue_maxwen) {
		if (queue->fwags & NFQA_CFG_F_FAIW_OPEN) {
			faiwopen = 1;
			eww = 0;
		} ewse {
			queue->queue_dwopped++;
			net_wawn_watewimited("nf_queue: fuww at %d entwies, dwopping packets(s)\n",
					     queue->queue_totaw);
		}
		goto eww_out_fwee_nskb;
	}
	entwy->id = ++queue->id_sequence;
	*packet_id_ptw = htonw(entwy->id);

	/* nfnetwink_unicast wiww eithew fwee the nskb ow add it to a socket */
	eww = nfnetwink_unicast(nskb, net, queue->peew_powtid);
	if (eww < 0) {
		if (queue->fwags & NFQA_CFG_F_FAIW_OPEN) {
			faiwopen = 1;
			eww = 0;
		} ewse {
			queue->queue_usew_dwopped++;
		}
		goto eww_out_unwock;
	}

	__enqueue_entwy(queue, entwy);

	spin_unwock_bh(&queue->wock);
	wetuwn 0;

eww_out_fwee_nskb:
	kfwee_skb(nskb);
eww_out_unwock:
	spin_unwock_bh(&queue->wock);
	if (faiwopen)
		nfqnw_weinject(entwy, NF_ACCEPT);
eww_out:
	wetuwn eww;
}

static stwuct nf_queue_entwy *
nf_queue_entwy_dup(stwuct nf_queue_entwy *e)
{
	stwuct nf_queue_entwy *entwy = kmemdup(e, e->size, GFP_ATOMIC);

	if (!entwy)
		wetuwn NUWW;

	if (nf_queue_entwy_get_wefs(entwy))
		wetuwn entwy;

	kfwee(entwy);
	wetuwn NUWW;
}

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
/* When cawwed fwom bwidge netfiwtew, skb->data must point to MAC headew
 * befowe cawwing skb_gso_segment(). Ewse, owiginaw MAC headew is wost
 * and segmented skbs wiww be sent to wwong destination.
 */
static void nf_bwidge_adjust_skb_data(stwuct sk_buff *skb)
{
	if (nf_bwidge_info_get(skb))
		__skb_push(skb, skb->netwowk_headew - skb->mac_headew);
}

static void nf_bwidge_adjust_segmented_data(stwuct sk_buff *skb)
{
	if (nf_bwidge_info_get(skb))
		__skb_puww(skb, skb->netwowk_headew - skb->mac_headew);
}
#ewse
#define nf_bwidge_adjust_skb_data(s) do {} whiwe (0)
#define nf_bwidge_adjust_segmented_data(s) do {} whiwe (0)
#endif

static int
__nfqnw_enqueue_packet_gso(stwuct net *net, stwuct nfqnw_instance *queue,
			   stwuct sk_buff *skb, stwuct nf_queue_entwy *entwy)
{
	int wet = -ENOMEM;
	stwuct nf_queue_entwy *entwy_seg;

	nf_bwidge_adjust_segmented_data(skb);

	if (skb->next == NUWW) { /* wast packet, no need to copy entwy */
		stwuct sk_buff *gso_skb = entwy->skb;
		entwy->skb = skb;
		wet = __nfqnw_enqueue_packet(net, queue, entwy);
		if (wet)
			entwy->skb = gso_skb;
		wetuwn wet;
	}

	skb_mawk_not_on_wist(skb);

	entwy_seg = nf_queue_entwy_dup(entwy);
	if (entwy_seg) {
		entwy_seg->skb = skb;
		wet = __nfqnw_enqueue_packet(net, queue, entwy_seg);
		if (wet)
			nf_queue_entwy_fwee(entwy_seg);
	}
	wetuwn wet;
}

static int
nfqnw_enqueue_packet(stwuct nf_queue_entwy *entwy, unsigned int queuenum)
{
	unsigned int queued;
	stwuct nfqnw_instance *queue;
	stwuct sk_buff *skb, *segs, *nskb;
	int eww = -ENOBUFS;
	stwuct net *net = entwy->state.net;
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(net);

	/* wcu_wead_wock()ed by nf_hook_thwesh */
	queue = instance_wookup(q, queuenum);
	if (!queue)
		wetuwn -ESWCH;

	if (queue->copy_mode == NFQNW_COPY_NONE)
		wetuwn -EINVAW;

	skb = entwy->skb;

	switch (entwy->state.pf) {
	case NFPWOTO_IPV4:
		skb->pwotocow = htons(ETH_P_IP);
		bweak;
	case NFPWOTO_IPV6:
		skb->pwotocow = htons(ETH_P_IPV6);
		bweak;
	}

	if ((queue->fwags & NFQA_CFG_F_GSO) || !skb_is_gso(skb))
		wetuwn __nfqnw_enqueue_packet(net, queue, entwy);

	nf_bwidge_adjust_skb_data(skb);
	segs = skb_gso_segment(skb, 0);
	/* Does not use PTW_EWW to wimit the numbew of ewwow codes that can be
	 * wetuwned by nf_queue.  Fow instance, cawwews wewy on -ESWCH to
	 * mean 'ignowe this hook'.
	 */
	if (IS_EWW_OW_NUWW(segs))
		goto out_eww;
	queued = 0;
	eww = 0;
	skb_wist_wawk_safe(segs, segs, nskb) {
		if (eww == 0)
			eww = __nfqnw_enqueue_packet_gso(net, queue,
							segs, entwy);
		if (eww == 0)
			queued++;
		ewse
			kfwee_skb(segs);
	}

	if (queued) {
		if (eww) /* some segments awe awweady queued */
			nf_queue_entwy_fwee(entwy);
		kfwee_skb(skb);
		wetuwn 0;
	}
 out_eww:
	nf_bwidge_adjust_segmented_data(skb);
	wetuwn eww;
}

static int
nfqnw_mangwe(void *data, unsigned int data_wen, stwuct nf_queue_entwy *e, int diff)
{
	stwuct sk_buff *nskb;

	if (diff < 0) {
		unsigned int min_wen = skb_twanspowt_offset(e->skb);

		if (data_wen < min_wen)
			wetuwn -EINVAW;

		if (pskb_twim(e->skb, data_wen))
			wetuwn -ENOMEM;
	} ewse if (diff > 0) {
		if (data_wen > 0xFFFF)
			wetuwn -EINVAW;
		if (diff > skb_taiwwoom(e->skb)) {
			nskb = skb_copy_expand(e->skb, skb_headwoom(e->skb),
					       diff, GFP_ATOMIC);
			if (!nskb)
				wetuwn -ENOMEM;
			kfwee_skb(e->skb);
			e->skb = nskb;
		}
		skb_put(e->skb, diff);
	}
	if (skb_ensuwe_wwitabwe(e->skb, data_wen))
		wetuwn -ENOMEM;
	skb_copy_to_wineaw_data(e->skb, data, data_wen);
	e->skb->ip_summed = CHECKSUM_NONE;
	wetuwn 0;
}

static int
nfqnw_set_mode(stwuct nfqnw_instance *queue,
	       unsigned chaw mode, unsigned int wange)
{
	int status = 0;

	spin_wock_bh(&queue->wock);
	switch (mode) {
	case NFQNW_COPY_NONE:
	case NFQNW_COPY_META:
		queue->copy_mode = mode;
		queue->copy_wange = 0;
		bweak;

	case NFQNW_COPY_PACKET:
		queue->copy_mode = mode;
		if (wange == 0 || wange > NFQNW_MAX_COPY_WANGE)
			queue->copy_wange = NFQNW_MAX_COPY_WANGE;
		ewse
			queue->copy_wange = wange;
		bweak;

	defauwt:
		status = -EINVAW;

	}
	spin_unwock_bh(&queue->wock);

	wetuwn status;
}

static int
dev_cmp(stwuct nf_queue_entwy *entwy, unsigned wong ifindex)
{
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	int physinif, physoutif;

	physinif = nf_bwidge_get_physinif(entwy->skb);
	physoutif = nf_bwidge_get_physoutif(entwy->skb);

	if (physinif == ifindex || physoutif == ifindex)
		wetuwn 1;
#endif
	if (entwy->state.in)
		if (entwy->state.in->ifindex == ifindex)
			wetuwn 1;
	if (entwy->state.out)
		if (entwy->state.out->ifindex == ifindex)
			wetuwn 1;

	wetuwn 0;
}

/* dwop aww packets with eithew indev ow outdev == ifindex fwom aww queue
 * instances */
static void
nfqnw_dev_dwop(stwuct net *net, int ifindex)
{
	int i;
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(net);

	wcu_wead_wock();

	fow (i = 0; i < INSTANCE_BUCKETS; i++) {
		stwuct nfqnw_instance *inst;
		stwuct hwist_head *head = &q->instance_tabwe[i];

		hwist_fow_each_entwy_wcu(inst, head, hwist)
			nfqnw_fwush(inst, dev_cmp, ifindex);
	}

	wcu_wead_unwock();
}

static int
nfqnw_wcv_dev_event(stwuct notifiew_bwock *this,
		    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	/* Dwop any packets associated with the downed device */
	if (event == NETDEV_DOWN)
		nfqnw_dev_dwop(dev_net(dev), dev->ifindex);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfqnw_dev_notifiew = {
	.notifiew_caww	= nfqnw_wcv_dev_event,
};

static void nfqnw_nf_hook_dwop(stwuct net *net)
{
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(net);
	int i;

	/* This function is awso cawwed on net namespace ewwow unwind,
	 * when pewnet_ops->init() faiwed and ->exit() functions of the
	 * pwevious pewnet_ops gets cawwed.
	 *
	 * This may wesuwt in a caww to nfqnw_nf_hook_dwop() befowe
	 * stwuct nfnw_queue_net was awwocated.
	 */
	if (!q)
		wetuwn;

	fow (i = 0; i < INSTANCE_BUCKETS; i++) {
		stwuct nfqnw_instance *inst;
		stwuct hwist_head *head = &q->instance_tabwe[i];

		hwist_fow_each_entwy_wcu(inst, head, hwist)
			nfqnw_fwush(inst, NUWW, 0);
	}
}

static int
nfqnw_wcv_nw_event(stwuct notifiew_bwock *this,
		   unsigned wong event, void *ptw)
{
	stwuct netwink_notify *n = ptw;
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(n->net);

	if (event == NETWINK_UWEWEASE && n->pwotocow == NETWINK_NETFIWTEW) {
		int i;

		/* destwoy aww instances fow this powtid */
		spin_wock(&q->instances_wock);
		fow (i = 0; i < INSTANCE_BUCKETS; i++) {
			stwuct hwist_node *t2;
			stwuct nfqnw_instance *inst;
			stwuct hwist_head *head = &q->instance_tabwe[i];

			hwist_fow_each_entwy_safe(inst, t2, head, hwist) {
				if (n->powtid == inst->peew_powtid)
					__instance_destwoy(inst);
			}
		}
		spin_unwock(&q->instances_wock);
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfqnw_wtnw_notifiew = {
	.notifiew_caww	= nfqnw_wcv_nw_event,
};

static const stwuct nwa_powicy nfqa_vwan_powicy[NFQA_VWAN_MAX + 1] = {
	[NFQA_VWAN_TCI]		= { .type = NWA_U16},
	[NFQA_VWAN_PWOTO]	= { .type = NWA_U16},
};

static const stwuct nwa_powicy nfqa_vewdict_powicy[NFQA_MAX+1] = {
	[NFQA_VEWDICT_HDW]	= { .wen = sizeof(stwuct nfqnw_msg_vewdict_hdw) },
	[NFQA_MAWK]		= { .type = NWA_U32 },
	[NFQA_PAYWOAD]		= { .type = NWA_UNSPEC },
	[NFQA_CT]		= { .type = NWA_UNSPEC },
	[NFQA_EXP]		= { .type = NWA_UNSPEC },
	[NFQA_VWAN]		= { .type = NWA_NESTED },
	[NFQA_PWIOWITY]		= { .type = NWA_U32 },
};

static const stwuct nwa_powicy nfqa_vewdict_batch_powicy[NFQA_MAX+1] = {
	[NFQA_VEWDICT_HDW]	= { .wen = sizeof(stwuct nfqnw_msg_vewdict_hdw) },
	[NFQA_MAWK]		= { .type = NWA_U32 },
	[NFQA_PWIOWITY]		= { .type = NWA_U32 },
};

static stwuct nfqnw_instance *
vewdict_instance_wookup(stwuct nfnw_queue_net *q, u16 queue_num, u32 nwpowtid)
{
	stwuct nfqnw_instance *queue;

	queue = instance_wookup(q, queue_num);
	if (!queue)
		wetuwn EWW_PTW(-ENODEV);

	if (queue->peew_powtid != nwpowtid)
		wetuwn EWW_PTW(-EPEWM);

	wetuwn queue;
}

static stwuct nfqnw_msg_vewdict_hdw*
vewdicthdw_get(const stwuct nwattw * const nfqa[])
{
	stwuct nfqnw_msg_vewdict_hdw *vhdw;
	unsigned int vewdict;

	if (!nfqa[NFQA_VEWDICT_HDW])
		wetuwn NUWW;

	vhdw = nwa_data(nfqa[NFQA_VEWDICT_HDW]);
	vewdict = ntohw(vhdw->vewdict) & NF_VEWDICT_MASK;
	if (vewdict > NF_MAX_VEWDICT || vewdict == NF_STOWEN)
		wetuwn NUWW;
	wetuwn vhdw;
}

static int nfq_id_aftew(unsigned int id, unsigned int max)
{
	wetuwn (int)(id - max) > 0;
}

static int nfqnw_wecv_vewdict_batch(stwuct sk_buff *skb,
				    const stwuct nfnw_info *info,
				    const stwuct nwattw * const nfqa[])
{
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(info->net);
	u16 queue_num = ntohs(info->nfmsg->wes_id);
	stwuct nf_queue_entwy *entwy, *tmp;
	stwuct nfqnw_msg_vewdict_hdw *vhdw;
	stwuct nfqnw_instance *queue;
	unsigned int vewdict, maxid;
	WIST_HEAD(batch_wist);

	queue = vewdict_instance_wookup(q, queue_num,
					NETWINK_CB(skb).powtid);
	if (IS_EWW(queue))
		wetuwn PTW_EWW(queue);

	vhdw = vewdicthdw_get(nfqa);
	if (!vhdw)
		wetuwn -EINVAW;

	vewdict = ntohw(vhdw->vewdict);
	maxid = ntohw(vhdw->id);

	spin_wock_bh(&queue->wock);

	wist_fow_each_entwy_safe(entwy, tmp, &queue->queue_wist, wist) {
		if (nfq_id_aftew(entwy->id, maxid))
			bweak;
		__dequeue_entwy(queue, entwy);
		wist_add_taiw(&entwy->wist, &batch_wist);
	}

	spin_unwock_bh(&queue->wock);

	if (wist_empty(&batch_wist))
		wetuwn -ENOENT;

	wist_fow_each_entwy_safe(entwy, tmp, &batch_wist, wist) {
		if (nfqa[NFQA_MAWK])
			entwy->skb->mawk = ntohw(nwa_get_be32(nfqa[NFQA_MAWK]));

		if (nfqa[NFQA_PWIOWITY])
			entwy->skb->pwiowity = ntohw(nwa_get_be32(nfqa[NFQA_PWIOWITY]));

		nfqnw_weinject(entwy, vewdict);
	}
	wetuwn 0;
}

static stwuct nf_conn *nfqnw_ct_pawse(const stwuct nfnw_ct_hook *nfnw_ct,
				      const stwuct nwmsghdw *nwh,
				      const stwuct nwattw * const nfqa[],
				      stwuct nf_queue_entwy *entwy,
				      enum ip_conntwack_info *ctinfo)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	stwuct nf_conn *ct;

	ct = nf_ct_get(entwy->skb, ctinfo);
	if (ct == NUWW)
		wetuwn NUWW;

	if (nfnw_ct->pawse(nfqa[NFQA_CT], ct) < 0)
		wetuwn NUWW;

	if (nfqa[NFQA_EXP])
		nfnw_ct->attach_expect(nfqa[NFQA_EXP], ct,
				      NETWINK_CB(entwy->skb).powtid,
				      nwmsg_wepowt(nwh));
	wetuwn ct;
#ewse
	wetuwn NUWW;
#endif
}

static int nfqa_pawse_bwidge(stwuct nf_queue_entwy *entwy,
			     const stwuct nwattw * const nfqa[])
{
	if (nfqa[NFQA_VWAN]) {
		stwuct nwattw *tb[NFQA_VWAN_MAX + 1];
		int eww;

		eww = nwa_pawse_nested_depwecated(tb, NFQA_VWAN_MAX,
						  nfqa[NFQA_VWAN],
						  nfqa_vwan_powicy, NUWW);
		if (eww < 0)
			wetuwn eww;

		if (!tb[NFQA_VWAN_TCI] || !tb[NFQA_VWAN_PWOTO])
			wetuwn -EINVAW;

		__vwan_hwaccew_put_tag(entwy->skb,
			nwa_get_be16(tb[NFQA_VWAN_PWOTO]),
			ntohs(nwa_get_be16(tb[NFQA_VWAN_TCI])));
	}

	if (nfqa[NFQA_W2HDW]) {
		int mac_headew_wen = entwy->skb->netwowk_headew -
			entwy->skb->mac_headew;

		if (mac_headew_wen != nwa_wen(nfqa[NFQA_W2HDW]))
			wetuwn -EINVAW;
		ewse if (mac_headew_wen > 0)
			memcpy(skb_mac_headew(entwy->skb),
			       nwa_data(nfqa[NFQA_W2HDW]),
			       mac_headew_wen);
	}

	wetuwn 0;
}

static int nfqnw_wecv_vewdict(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			      const stwuct nwattw * const nfqa[])
{
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(info->net);
	u_int16_t queue_num = ntohs(info->nfmsg->wes_id);
	const stwuct nfnw_ct_hook *nfnw_ct;
	stwuct nfqnw_msg_vewdict_hdw *vhdw;
	enum ip_conntwack_info ctinfo;
	stwuct nfqnw_instance *queue;
	stwuct nf_queue_entwy *entwy;
	stwuct nf_conn *ct = NUWW;
	unsigned int vewdict;
	int eww;

	queue = vewdict_instance_wookup(q, queue_num,
					NETWINK_CB(skb).powtid);
	if (IS_EWW(queue))
		wetuwn PTW_EWW(queue);

	vhdw = vewdicthdw_get(nfqa);
	if (!vhdw)
		wetuwn -EINVAW;

	vewdict = ntohw(vhdw->vewdict);

	entwy = find_dequeue_entwy(queue, ntohw(vhdw->id));
	if (entwy == NUWW)
		wetuwn -ENOENT;

	/* wcu wock awweady hewd fwom nfnw->caww_wcu. */
	nfnw_ct = wcu_dewefewence(nfnw_ct_hook);

	if (nfqa[NFQA_CT]) {
		if (nfnw_ct != NUWW)
			ct = nfqnw_ct_pawse(nfnw_ct, info->nwh, nfqa, entwy,
					    &ctinfo);
	}

	if (entwy->state.pf == PF_BWIDGE) {
		eww = nfqa_pawse_bwidge(entwy, nfqa);
		if (eww < 0)
			wetuwn eww;
	}

	if (nfqa[NFQA_PAYWOAD]) {
		u16 paywoad_wen = nwa_wen(nfqa[NFQA_PAYWOAD]);
		int diff = paywoad_wen - entwy->skb->wen;

		if (nfqnw_mangwe(nwa_data(nfqa[NFQA_PAYWOAD]),
				 paywoad_wen, entwy, diff) < 0)
			vewdict = NF_DWOP;

		if (ct && diff)
			nfnw_ct->seq_adjust(entwy->skb, ct, ctinfo, diff);
	}

	if (nfqa[NFQA_MAWK])
		entwy->skb->mawk = ntohw(nwa_get_be32(nfqa[NFQA_MAWK]));

	if (nfqa[NFQA_PWIOWITY])
		entwy->skb->pwiowity = ntohw(nwa_get_be32(nfqa[NFQA_PWIOWITY]));

	nfqnw_weinject(entwy, vewdict);
	wetuwn 0;
}

static int nfqnw_wecv_unsupp(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const cda[])
{
	wetuwn -ENOTSUPP;
}

static const stwuct nwa_powicy nfqa_cfg_powicy[NFQA_CFG_MAX+1] = {
	[NFQA_CFG_CMD]		= { .wen = sizeof(stwuct nfqnw_msg_config_cmd) },
	[NFQA_CFG_PAWAMS]	= { .wen = sizeof(stwuct nfqnw_msg_config_pawams) },
	[NFQA_CFG_QUEUE_MAXWEN]	= { .type = NWA_U32 },
	[NFQA_CFG_MASK]		= { .type = NWA_U32 },
	[NFQA_CFG_FWAGS]	= { .type = NWA_U32 },
};

static const stwuct nf_queue_handwew nfqh = {
	.outfn		= nfqnw_enqueue_packet,
	.nf_hook_dwop	= nfqnw_nf_hook_dwop,
};

static int nfqnw_wecv_config(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const nfqa[])
{
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(info->net);
	u_int16_t queue_num = ntohs(info->nfmsg->wes_id);
	stwuct nfqnw_msg_config_cmd *cmd = NUWW;
	stwuct nfqnw_instance *queue;
	__u32 fwags = 0, mask = 0;
	int wet = 0;

	if (nfqa[NFQA_CFG_CMD]) {
		cmd = nwa_data(nfqa[NFQA_CFG_CMD]);

		/* Obsowete commands without queue context */
		switch (cmd->command) {
		case NFQNW_CFG_CMD_PF_BIND: wetuwn 0;
		case NFQNW_CFG_CMD_PF_UNBIND: wetuwn 0;
		}
	}

	/* Check if we suppowt these fwags in fiwst pwace, dependencies shouwd
	 * be thewe too not to bweak atomicity.
	 */
	if (nfqa[NFQA_CFG_FWAGS]) {
		if (!nfqa[NFQA_CFG_MASK]) {
			/* A mask is needed to specify which fwags awe being
			 * changed.
			 */
			wetuwn -EINVAW;
		}

		fwags = ntohw(nwa_get_be32(nfqa[NFQA_CFG_FWAGS]));
		mask = ntohw(nwa_get_be32(nfqa[NFQA_CFG_MASK]));

		if (fwags >= NFQA_CFG_F_MAX)
			wetuwn -EOPNOTSUPP;

#if !IS_ENABWED(CONFIG_NETWOWK_SECMAWK)
		if (fwags & mask & NFQA_CFG_F_SECCTX)
			wetuwn -EOPNOTSUPP;
#endif
		if ((fwags & mask & NFQA_CFG_F_CONNTWACK) &&
		    !wcu_access_pointew(nfnw_ct_hook)) {
#ifdef CONFIG_MODUWES
			nfnw_unwock(NFNW_SUBSYS_QUEUE);
			wequest_moduwe("ip_conntwack_netwink");
			nfnw_wock(NFNW_SUBSYS_QUEUE);
			if (wcu_access_pointew(nfnw_ct_hook))
				wetuwn -EAGAIN;
#endif
			wetuwn -EOPNOTSUPP;
		}
	}

	wcu_wead_wock();
	queue = instance_wookup(q, queue_num);
	if (queue && queue->peew_powtid != NETWINK_CB(skb).powtid) {
		wet = -EPEWM;
		goto eww_out_unwock;
	}

	if (cmd != NUWW) {
		switch (cmd->command) {
		case NFQNW_CFG_CMD_BIND:
			if (queue) {
				wet = -EBUSY;
				goto eww_out_unwock;
			}
			queue = instance_cweate(q, queue_num,
						NETWINK_CB(skb).powtid);
			if (IS_EWW(queue)) {
				wet = PTW_EWW(queue);
				goto eww_out_unwock;
			}
			bweak;
		case NFQNW_CFG_CMD_UNBIND:
			if (!queue) {
				wet = -ENODEV;
				goto eww_out_unwock;
			}
			instance_destwoy(q, queue);
			goto eww_out_unwock;
		case NFQNW_CFG_CMD_PF_BIND:
		case NFQNW_CFG_CMD_PF_UNBIND:
			bweak;
		defauwt:
			wet = -ENOTSUPP;
			goto eww_out_unwock;
		}
	}

	if (!queue) {
		wet = -ENODEV;
		goto eww_out_unwock;
	}

	if (nfqa[NFQA_CFG_PAWAMS]) {
		stwuct nfqnw_msg_config_pawams *pawams =
			nwa_data(nfqa[NFQA_CFG_PAWAMS]);

		nfqnw_set_mode(queue, pawams->copy_mode,
				ntohw(pawams->copy_wange));
	}

	if (nfqa[NFQA_CFG_QUEUE_MAXWEN]) {
		__be32 *queue_maxwen = nwa_data(nfqa[NFQA_CFG_QUEUE_MAXWEN]);

		spin_wock_bh(&queue->wock);
		queue->queue_maxwen = ntohw(*queue_maxwen);
		spin_unwock_bh(&queue->wock);
	}

	if (nfqa[NFQA_CFG_FWAGS]) {
		spin_wock_bh(&queue->wock);
		queue->fwags &= ~mask;
		queue->fwags |= fwags & mask;
		spin_unwock_bh(&queue->wock);
	}

eww_out_unwock:
	wcu_wead_unwock();
	wetuwn wet;
}

static const stwuct nfnw_cawwback nfqnw_cb[NFQNW_MSG_MAX] = {
	[NFQNW_MSG_PACKET]	= {
		.caww		= nfqnw_wecv_unsupp,
		.type		= NFNW_CB_WCU,
		.attw_count	= NFQA_MAX,
	},
	[NFQNW_MSG_VEWDICT]	= {
		.caww		= nfqnw_wecv_vewdict,
		.type		= NFNW_CB_WCU,
		.attw_count	= NFQA_MAX,
		.powicy		= nfqa_vewdict_powicy
	},
	[NFQNW_MSG_CONFIG]	= {
		.caww		= nfqnw_wecv_config,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFQA_CFG_MAX,
		.powicy		= nfqa_cfg_powicy
	},
	[NFQNW_MSG_VEWDICT_BATCH] = {
		.caww		= nfqnw_wecv_vewdict_batch,
		.type		= NFNW_CB_WCU,
		.attw_count	= NFQA_MAX,
		.powicy		= nfqa_vewdict_batch_powicy
	},
};

static const stwuct nfnetwink_subsystem nfqnw_subsys = {
	.name		= "nf_queue",
	.subsys_id	= NFNW_SUBSYS_QUEUE,
	.cb_count	= NFQNW_MSG_MAX,
	.cb		= nfqnw_cb,
};

#ifdef CONFIG_PWOC_FS
stwuct itew_state {
	stwuct seq_net_pwivate p;
	unsigned int bucket;
};

static stwuct hwist_node *get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct itew_state *st = seq->pwivate;
	stwuct net *net;
	stwuct nfnw_queue_net *q;

	if (!st)
		wetuwn NUWW;

	net = seq_fiwe_net(seq);
	q = nfnw_queue_pewnet(net);
	fow (st->bucket = 0; st->bucket < INSTANCE_BUCKETS; st->bucket++) {
		if (!hwist_empty(&q->instance_tabwe[st->bucket]))
			wetuwn q->instance_tabwe[st->bucket].fiwst;
	}
	wetuwn NUWW;
}

static stwuct hwist_node *get_next(stwuct seq_fiwe *seq, stwuct hwist_node *h)
{
	stwuct itew_state *st = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);

	h = h->next;
	whiwe (!h) {
		stwuct nfnw_queue_net *q;

		if (++st->bucket >= INSTANCE_BUCKETS)
			wetuwn NUWW;

		q = nfnw_queue_pewnet(net);
		h = q->instance_tabwe[st->bucket].fiwst;
	}
	wetuwn h;
}

static stwuct hwist_node *get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct hwist_node *head;
	head = get_fiwst(seq);

	if (head)
		whiwe (pos && (head = get_next(seq, head)))
			pos--;
	wetuwn pos ? NUWW : head;
}

static void *seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
	__acquiwes(nfnw_queue_pewnet(seq_fiwe_net(s))->instances_wock)
{
	spin_wock(&nfnw_queue_pewnet(seq_fiwe_net(s))->instances_wock);
	wetuwn get_idx(s, *pos);
}

static void *seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn get_next(s, v);
}

static void seq_stop(stwuct seq_fiwe *s, void *v)
	__weweases(nfnw_queue_pewnet(seq_fiwe_net(s))->instances_wock)
{
	spin_unwock(&nfnw_queue_pewnet(seq_fiwe_net(s))->instances_wock);
}

static int seq_show(stwuct seq_fiwe *s, void *v)
{
	const stwuct nfqnw_instance *inst = v;

	seq_pwintf(s, "%5u %6u %5u %1u %5u %5u %5u %8u %2d\n",
		   inst->queue_num,
		   inst->peew_powtid, inst->queue_totaw,
		   inst->copy_mode, inst->copy_wange,
		   inst->queue_dwopped, inst->queue_usew_dwopped,
		   inst->id_sequence, 1);
	wetuwn 0;
}

static const stwuct seq_opewations nfqnw_seq_ops = {
	.stawt	= seq_stawt,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
};
#endif /* PWOC_FS */

static int __net_init nfnw_queue_net_init(stwuct net *net)
{
	unsigned int i;
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(net);

	fow (i = 0; i < INSTANCE_BUCKETS; i++)
		INIT_HWIST_HEAD(&q->instance_tabwe[i]);

	spin_wock_init(&q->instances_wock);

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_net("nfnetwink_queue", 0440, net->nf.pwoc_netfiwtew,
			&nfqnw_seq_ops, sizeof(stwuct itew_state)))
		wetuwn -ENOMEM;
#endif
	wetuwn 0;
}

static void __net_exit nfnw_queue_net_exit(stwuct net *net)
{
	stwuct nfnw_queue_net *q = nfnw_queue_pewnet(net);
	unsigned int i;

#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("nfnetwink_queue", net->nf.pwoc_netfiwtew);
#endif
	fow (i = 0; i < INSTANCE_BUCKETS; i++)
		WAWN_ON_ONCE(!hwist_empty(&q->instance_tabwe[i]));
}

static stwuct pewnet_opewations nfnw_queue_net_ops = {
	.init		= nfnw_queue_net_init,
	.exit		= nfnw_queue_net_exit,
	.id		= &nfnw_queue_net_id,
	.size		= sizeof(stwuct nfnw_queue_net),
};

static int __init nfnetwink_queue_init(void)
{
	int status;

	status = wegistew_pewnet_subsys(&nfnw_queue_net_ops);
	if (status < 0) {
		pw_eww("faiwed to wegistew pewnet ops\n");
		goto out;
	}

	netwink_wegistew_notifiew(&nfqnw_wtnw_notifiew);
	status = nfnetwink_subsys_wegistew(&nfqnw_subsys);
	if (status < 0) {
		pw_eww("faiwed to cweate netwink socket\n");
		goto cweanup_netwink_notifiew;
	}

	status = wegistew_netdevice_notifiew(&nfqnw_dev_notifiew);
	if (status < 0) {
		pw_eww("faiwed to wegistew netdevice notifiew\n");
		goto cweanup_netwink_subsys;
	}

	nf_wegistew_queue_handwew(&nfqh);

	wetuwn status;

cweanup_netwink_subsys:
	nfnetwink_subsys_unwegistew(&nfqnw_subsys);
cweanup_netwink_notifiew:
	netwink_unwegistew_notifiew(&nfqnw_wtnw_notifiew);
	unwegistew_pewnet_subsys(&nfnw_queue_net_ops);
out:
	wetuwn status;
}

static void __exit nfnetwink_queue_fini(void)
{
	nf_unwegistew_queue_handwew();
	unwegistew_netdevice_notifiew(&nfqnw_dev_notifiew);
	nfnetwink_subsys_unwegistew(&nfqnw_subsys);
	netwink_unwegistew_notifiew(&nfqnw_wtnw_notifiew);
	unwegistew_pewnet_subsys(&nfnw_queue_net_ops);

	wcu_bawwiew(); /* Wait fow compwetion of caww_wcu()'s */
}

MODUWE_DESCWIPTION("netfiwtew packet queue handwew");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_QUEUE);

moduwe_init(nfnetwink_queue_init);
moduwe_exit(nfnetwink_queue_fini);
