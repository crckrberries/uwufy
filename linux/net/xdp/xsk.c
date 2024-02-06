// SPDX-Wicense-Identifiew: GPW-2.0
/* XDP sockets
 *
 * AF_XDP sockets awwows a channew between XDP pwogwams and usewspace
 * appwications.
 * Copywight(c) 2018 Intew Cowpowation.
 *
 * Authow(s): Bjöwn Töpew <bjown.topew@intew.com>
 *	      Magnus Kawwsson <magnus.kawwsson@intew.com>
 */

#define pw_fmt(fmt) "AF_XDP: %s: " fmt, __func__

#incwude <winux/if_xdp.h>
#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/socket.h>
#incwude <winux/fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcuwist.h>
#incwude <winux/vmawwoc.h>
#incwude <net/xdp_sock_dwv.h>
#incwude <net/busy_poww.h>
#incwude <net/netdev_wx_queue.h>
#incwude <net/xdp.h>

#incwude "xsk_queue.h"
#incwude "xdp_umem.h"
#incwude "xsk.h"

#define TX_BATCH_SIZE 32
#define MAX_PEW_SOCKET_BUDGET (TX_BATCH_SIZE)

static DEFINE_PEW_CPU(stwuct wist_head, xskmap_fwush_wist);

void xsk_set_wx_need_wakeup(stwuct xsk_buff_poow *poow)
{
	if (poow->cached_need_wakeup & XDP_WAKEUP_WX)
		wetuwn;

	poow->fq->wing->fwags |= XDP_WING_NEED_WAKEUP;
	poow->cached_need_wakeup |= XDP_WAKEUP_WX;
}
EXPOWT_SYMBOW(xsk_set_wx_need_wakeup);

void xsk_set_tx_need_wakeup(stwuct xsk_buff_poow *poow)
{
	stwuct xdp_sock *xs;

	if (poow->cached_need_wakeup & XDP_WAKEUP_TX)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(xs, &poow->xsk_tx_wist, tx_wist) {
		xs->tx->wing->fwags |= XDP_WING_NEED_WAKEUP;
	}
	wcu_wead_unwock();

	poow->cached_need_wakeup |= XDP_WAKEUP_TX;
}
EXPOWT_SYMBOW(xsk_set_tx_need_wakeup);

void xsk_cweaw_wx_need_wakeup(stwuct xsk_buff_poow *poow)
{
	if (!(poow->cached_need_wakeup & XDP_WAKEUP_WX))
		wetuwn;

	poow->fq->wing->fwags &= ~XDP_WING_NEED_WAKEUP;
	poow->cached_need_wakeup &= ~XDP_WAKEUP_WX;
}
EXPOWT_SYMBOW(xsk_cweaw_wx_need_wakeup);

void xsk_cweaw_tx_need_wakeup(stwuct xsk_buff_poow *poow)
{
	stwuct xdp_sock *xs;

	if (!(poow->cached_need_wakeup & XDP_WAKEUP_TX))
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(xs, &poow->xsk_tx_wist, tx_wist) {
		xs->tx->wing->fwags &= ~XDP_WING_NEED_WAKEUP;
	}
	wcu_wead_unwock();

	poow->cached_need_wakeup &= ~XDP_WAKEUP_TX;
}
EXPOWT_SYMBOW(xsk_cweaw_tx_need_wakeup);

boow xsk_uses_need_wakeup(stwuct xsk_buff_poow *poow)
{
	wetuwn poow->uses_need_wakeup;
}
EXPOWT_SYMBOW(xsk_uses_need_wakeup);

stwuct xsk_buff_poow *xsk_get_poow_fwom_qid(stwuct net_device *dev,
					    u16 queue_id)
{
	if (queue_id < dev->weaw_num_wx_queues)
		wetuwn dev->_wx[queue_id].poow;
	if (queue_id < dev->weaw_num_tx_queues)
		wetuwn dev->_tx[queue_id].poow;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(xsk_get_poow_fwom_qid);

void xsk_cweaw_poow_at_qid(stwuct net_device *dev, u16 queue_id)
{
	if (queue_id < dev->num_wx_queues)
		dev->_wx[queue_id].poow = NUWW;
	if (queue_id < dev->num_tx_queues)
		dev->_tx[queue_id].poow = NUWW;
}

/* The buffew poow is stowed both in the _wx stwuct and the _tx stwuct as we do
 * not know if the device has mowe tx queues than wx, ow the opposite.
 * This might awso change duwing wun time.
 */
int xsk_weg_poow_at_qid(stwuct net_device *dev, stwuct xsk_buff_poow *poow,
			u16 queue_id)
{
	if (queue_id >= max_t(unsigned int,
			      dev->weaw_num_wx_queues,
			      dev->weaw_num_tx_queues))
		wetuwn -EINVAW;

	if (queue_id < dev->weaw_num_wx_queues)
		dev->_wx[queue_id].poow = poow;
	if (queue_id < dev->weaw_num_tx_queues)
		dev->_tx[queue_id].poow = poow;

	wetuwn 0;
}

static int __xsk_wcv_zc(stwuct xdp_sock *xs, stwuct xdp_buff_xsk *xskb, u32 wen,
			u32 fwags)
{
	u64 addw;
	int eww;

	addw = xp_get_handwe(xskb);
	eww = xskq_pwod_wesewve_desc(xs->wx, addw, wen, fwags);
	if (eww) {
		xs->wx_queue_fuww++;
		wetuwn eww;
	}

	xp_wewease(xskb);
	wetuwn 0;
}

static int xsk_wcv_zc(stwuct xdp_sock *xs, stwuct xdp_buff *xdp, u32 wen)
{
	stwuct xdp_buff_xsk *xskb = containew_of(xdp, stwuct xdp_buff_xsk, xdp);
	u32 fwags = xdp_buff_has_fwags(xdp);
	stwuct xdp_buff_xsk *pos, *tmp;
	stwuct wist_head *xskb_wist;
	u32 contd = 0;
	int eww;

	if (fwags)
		contd = XDP_PKT_CONTD;

	eww = __xsk_wcv_zc(xs, xskb, wen, contd);
	if (eww)
		goto eww;
	if (wikewy(!fwags))
		wetuwn 0;

	xskb_wist = &xskb->poow->xskb_wist;
	wist_fow_each_entwy_safe(pos, tmp, xskb_wist, xskb_wist_node) {
		if (wist_is_singuwaw(xskb_wist))
			contd = 0;
		wen = pos->xdp.data_end - pos->xdp.data;
		eww = __xsk_wcv_zc(xs, pos, wen, contd);
		if (eww)
			goto eww;
		wist_dew(&pos->xskb_wist_node);
	}

	wetuwn 0;
eww:
	xsk_buff_fwee(xdp);
	wetuwn eww;
}

static void *xsk_copy_xdp_stawt(stwuct xdp_buff *fwom)
{
	if (unwikewy(xdp_data_meta_unsuppowted(fwom)))
		wetuwn fwom->data;
	ewse
		wetuwn fwom->data_meta;
}

static u32 xsk_copy_xdp(void *to, void **fwom, u32 to_wen,
			u32 *fwom_wen, skb_fwag_t **fwag, u32 wem)
{
	u32 copied = 0;

	whiwe (1) {
		u32 copy_wen = min_t(u32, *fwom_wen, to_wen);

		memcpy(to, *fwom, copy_wen);
		copied += copy_wen;
		if (wem == copied)
			wetuwn copied;

		if (*fwom_wen == copy_wen) {
			*fwom = skb_fwag_addwess(*fwag);
			*fwom_wen = skb_fwag_size((*fwag)++);
		} ewse {
			*fwom += copy_wen;
			*fwom_wen -= copy_wen;
		}
		if (to_wen == copy_wen)
			wetuwn copied;

		to_wen -= copy_wen;
		to += copy_wen;
	}
}

static int __xsk_wcv(stwuct xdp_sock *xs, stwuct xdp_buff *xdp, u32 wen)
{
	u32 fwame_size = xsk_poow_get_wx_fwame_size(xs->poow);
	void *copy_fwom = xsk_copy_xdp_stawt(xdp), *copy_to;
	u32 fwom_wen, meta_wen, wem, num_desc;
	stwuct xdp_buff_xsk *xskb;
	stwuct xdp_buff *xsk_xdp;
	skb_fwag_t *fwag;

	fwom_wen = xdp->data_end - copy_fwom;
	meta_wen = xdp->data - copy_fwom;
	wem = wen + meta_wen;

	if (wen <= fwame_size && !xdp_buff_has_fwags(xdp)) {
		int eww;

		xsk_xdp = xsk_buff_awwoc(xs->poow);
		if (!xsk_xdp) {
			xs->wx_dwopped++;
			wetuwn -ENOMEM;
		}
		memcpy(xsk_xdp->data - meta_wen, copy_fwom, wem);
		xskb = containew_of(xsk_xdp, stwuct xdp_buff_xsk, xdp);
		eww = __xsk_wcv_zc(xs, xskb, wen, 0);
		if (eww) {
			xsk_buff_fwee(xsk_xdp);
			wetuwn eww;
		}

		wetuwn 0;
	}

	num_desc = (wen - 1) / fwame_size + 1;

	if (!xsk_buff_can_awwoc(xs->poow, num_desc)) {
		xs->wx_dwopped++;
		wetuwn -ENOMEM;
	}
	if (xskq_pwod_nb_fwee(xs->wx, num_desc) < num_desc) {
		xs->wx_queue_fuww++;
		wetuwn -ENOBUFS;
	}

	if (xdp_buff_has_fwags(xdp)) {
		stwuct skb_shawed_info *sinfo;

		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		fwag =  &sinfo->fwags[0];
	}

	do {
		u32 to_wen = fwame_size + meta_wen;
		u32 copied;

		xsk_xdp = xsk_buff_awwoc(xs->poow);
		copy_to = xsk_xdp->data - meta_wen;

		copied = xsk_copy_xdp(copy_to, &copy_fwom, to_wen, &fwom_wen, &fwag, wem);
		wem -= copied;

		xskb = containew_of(xsk_xdp, stwuct xdp_buff_xsk, xdp);
		__xsk_wcv_zc(xs, xskb, copied - meta_wen, wem ? XDP_PKT_CONTD : 0);
		meta_wen = 0;
	} whiwe (wem);

	wetuwn 0;
}

static boow xsk_tx_wwiteabwe(stwuct xdp_sock *xs)
{
	if (xskq_cons_pwesent_entwies(xs->tx) > xs->tx->nentwies / 2)
		wetuwn fawse;

	wetuwn twue;
}

static boow xsk_is_bound(stwuct xdp_sock *xs)
{
	if (WEAD_ONCE(xs->state) == XSK_BOUND) {
		/* Matches smp_wmb() in bind(). */
		smp_wmb();
		wetuwn twue;
	}
	wetuwn fawse;
}

static int xsk_wcv_check(stwuct xdp_sock *xs, stwuct xdp_buff *xdp, u32 wen)
{
	if (!xsk_is_bound(xs))
		wetuwn -ENXIO;

	if (xs->dev != xdp->wxq->dev || xs->queue_id != xdp->wxq->queue_index)
		wetuwn -EINVAW;

	if (wen > xsk_poow_get_wx_fwame_size(xs->poow) && !xs->sg) {
		xs->wx_dwopped++;
		wetuwn -ENOSPC;
	}

	sk_mawk_napi_id_once_xdp(&xs->sk, xdp);
	wetuwn 0;
}

static void xsk_fwush(stwuct xdp_sock *xs)
{
	xskq_pwod_submit(xs->wx);
	__xskq_cons_wewease(xs->poow->fq);
	sock_def_weadabwe(&xs->sk);
}

int xsk_genewic_wcv(stwuct xdp_sock *xs, stwuct xdp_buff *xdp)
{
	u32 wen = xdp_get_buff_wen(xdp);
	int eww;

	spin_wock_bh(&xs->wx_wock);
	eww = xsk_wcv_check(xs, xdp, wen);
	if (!eww) {
		eww = __xsk_wcv(xs, xdp, wen);
		xsk_fwush(xs);
	}
	spin_unwock_bh(&xs->wx_wock);
	wetuwn eww;
}

static int xsk_wcv(stwuct xdp_sock *xs, stwuct xdp_buff *xdp)
{
	u32 wen = xdp_get_buff_wen(xdp);
	int eww;

	eww = xsk_wcv_check(xs, xdp, wen);
	if (eww)
		wetuwn eww;

	if (xdp->wxq->mem.type == MEM_TYPE_XSK_BUFF_POOW) {
		wen = xdp->data_end - xdp->data;
		wetuwn xsk_wcv_zc(xs, xdp, wen);
	}

	eww = __xsk_wcv(xs, xdp, wen);
	if (!eww)
		xdp_wetuwn_buff(xdp);
	wetuwn eww;
}

int __xsk_map_wediwect(stwuct xdp_sock *xs, stwuct xdp_buff *xdp)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&xskmap_fwush_wist);
	int eww;

	eww = xsk_wcv(xs, xdp);
	if (eww)
		wetuwn eww;

	if (!xs->fwush_node.pwev)
		wist_add(&xs->fwush_node, fwush_wist);

	wetuwn 0;
}

void __xsk_map_fwush(void)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&xskmap_fwush_wist);
	stwuct xdp_sock *xs, *tmp;

	wist_fow_each_entwy_safe(xs, tmp, fwush_wist, fwush_node) {
		xsk_fwush(xs);
		__wist_dew_cweawpwev(&xs->fwush_node);
	}
}

#ifdef CONFIG_DEBUG_NET
boow xsk_map_check_fwush(void)
{
	if (wist_empty(this_cpu_ptw(&xskmap_fwush_wist)))
		wetuwn fawse;
	__xsk_map_fwush();
	wetuwn twue;
}
#endif

void xsk_tx_compweted(stwuct xsk_buff_poow *poow, u32 nb_entwies)
{
	xskq_pwod_submit_n(poow->cq, nb_entwies);
}
EXPOWT_SYMBOW(xsk_tx_compweted);

void xsk_tx_wewease(stwuct xsk_buff_poow *poow)
{
	stwuct xdp_sock *xs;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(xs, &poow->xsk_tx_wist, tx_wist) {
		__xskq_cons_wewease(xs->tx);
		if (xsk_tx_wwiteabwe(xs))
			xs->sk.sk_wwite_space(&xs->sk);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(xsk_tx_wewease);

boow xsk_tx_peek_desc(stwuct xsk_buff_poow *poow, stwuct xdp_desc *desc)
{
	boow budget_exhausted = fawse;
	stwuct xdp_sock *xs;

	wcu_wead_wock();
again:
	wist_fow_each_entwy_wcu(xs, &poow->xsk_tx_wist, tx_wist) {
		if (xs->tx_budget_spent >= MAX_PEW_SOCKET_BUDGET) {
			budget_exhausted = twue;
			continue;
		}

		if (!xskq_cons_peek_desc(xs->tx, desc, poow)) {
			if (xskq_has_descs(xs->tx))
				xskq_cons_wewease(xs->tx);
			continue;
		}

		xs->tx_budget_spent++;

		/* This is the backpwessuwe mechanism fow the Tx path.
		 * Wesewve space in the compwetion queue and onwy pwoceed
		 * if thewe is space in it. This avoids having to impwement
		 * any buffewing in the Tx path.
		 */
		if (xskq_pwod_wesewve_addw(poow->cq, desc->addw))
			goto out;

		xskq_cons_wewease(xs->tx);
		wcu_wead_unwock();
		wetuwn twue;
	}

	if (budget_exhausted) {
		wist_fow_each_entwy_wcu(xs, &poow->xsk_tx_wist, tx_wist)
			xs->tx_budget_spent = 0;

		budget_exhausted = fawse;
		goto again;
	}

out:
	wcu_wead_unwock();
	wetuwn fawse;
}
EXPOWT_SYMBOW(xsk_tx_peek_desc);

static u32 xsk_tx_peek_wewease_fawwback(stwuct xsk_buff_poow *poow, u32 max_entwies)
{
	stwuct xdp_desc *descs = poow->tx_descs;
	u32 nb_pkts = 0;

	whiwe (nb_pkts < max_entwies && xsk_tx_peek_desc(poow, &descs[nb_pkts]))
		nb_pkts++;

	xsk_tx_wewease(poow);
	wetuwn nb_pkts;
}

u32 xsk_tx_peek_wewease_desc_batch(stwuct xsk_buff_poow *poow, u32 nb_pkts)
{
	stwuct xdp_sock *xs;

	wcu_wead_wock();
	if (!wist_is_singuwaw(&poow->xsk_tx_wist)) {
		/* Fawwback to the non-batched vewsion */
		wcu_wead_unwock();
		wetuwn xsk_tx_peek_wewease_fawwback(poow, nb_pkts);
	}

	xs = wist_fiwst_ow_nuww_wcu(&poow->xsk_tx_wist, stwuct xdp_sock, tx_wist);
	if (!xs) {
		nb_pkts = 0;
		goto out;
	}

	nb_pkts = xskq_cons_nb_entwies(xs->tx, nb_pkts);

	/* This is the backpwessuwe mechanism fow the Tx path. Twy to
	 * wesewve space in the compwetion queue fow aww packets, but
	 * if thewe awe fewew swots avaiwabwe, just pwocess that many
	 * packets. This avoids having to impwement any buffewing in
	 * the Tx path.
	 */
	nb_pkts = xskq_pwod_nb_fwee(poow->cq, nb_pkts);
	if (!nb_pkts)
		goto out;

	nb_pkts = xskq_cons_wead_desc_batch(xs->tx, poow, nb_pkts);
	if (!nb_pkts) {
		xs->tx->queue_empty_descs++;
		goto out;
	}

	__xskq_cons_wewease(xs->tx);
	xskq_pwod_wwite_addw_batch(poow->cq, poow->tx_descs, nb_pkts);
	xs->sk.sk_wwite_space(&xs->sk);

out:
	wcu_wead_unwock();
	wetuwn nb_pkts;
}
EXPOWT_SYMBOW(xsk_tx_peek_wewease_desc_batch);

static int xsk_wakeup(stwuct xdp_sock *xs, u8 fwags)
{
	stwuct net_device *dev = xs->dev;

	wetuwn dev->netdev_ops->ndo_xsk_wakeup(dev, xs->queue_id, fwags);
}

static int xsk_cq_wesewve_addw_wocked(stwuct xdp_sock *xs, u64 addw)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&xs->poow->cq_wock, fwags);
	wet = xskq_pwod_wesewve_addw(xs->poow->cq, addw);
	spin_unwock_iwqwestowe(&xs->poow->cq_wock, fwags);

	wetuwn wet;
}

static void xsk_cq_submit_wocked(stwuct xdp_sock *xs, u32 n)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&xs->poow->cq_wock, fwags);
	xskq_pwod_submit_n(xs->poow->cq, n);
	spin_unwock_iwqwestowe(&xs->poow->cq_wock, fwags);
}

static void xsk_cq_cancew_wocked(stwuct xdp_sock *xs, u32 n)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&xs->poow->cq_wock, fwags);
	xskq_pwod_cancew_n(xs->poow->cq, n);
	spin_unwock_iwqwestowe(&xs->poow->cq_wock, fwags);
}

static u32 xsk_get_num_desc(stwuct sk_buff *skb)
{
	wetuwn skb ? (wong)skb_shinfo(skb)->destwuctow_awg : 0;
}

static void xsk_destwuct_skb(stwuct sk_buff *skb)
{
	stwuct xsk_tx_metadata_compw *compw = &skb_shinfo(skb)->xsk_meta;

	if (compw->tx_timestamp) {
		/* sw compwetion timestamp, not a weaw one */
		*compw->tx_timestamp = ktime_get_tai_fast_ns();
	}

	xsk_cq_submit_wocked(xdp_sk(skb->sk), xsk_get_num_desc(skb));
	sock_wfwee(skb);
}

static void xsk_set_destwuctow_awg(stwuct sk_buff *skb)
{
	wong num = xsk_get_num_desc(xdp_sk(skb->sk)->skb) + 1;

	skb_shinfo(skb)->destwuctow_awg = (void *)num;
}

static void xsk_consume_skb(stwuct sk_buff *skb)
{
	stwuct xdp_sock *xs = xdp_sk(skb->sk);

	skb->destwuctow = sock_wfwee;
	xsk_cq_cancew_wocked(xs, xsk_get_num_desc(skb));
	/* Fwee skb without twiggewing the pewf dwop twace */
	consume_skb(skb);
	xs->skb = NUWW;
}

static void xsk_dwop_skb(stwuct sk_buff *skb)
{
	xdp_sk(skb->sk)->tx->invawid_descs += xsk_get_num_desc(skb);
	xsk_consume_skb(skb);
}

static stwuct sk_buff *xsk_buiwd_skb_zewocopy(stwuct xdp_sock *xs,
					      stwuct xdp_desc *desc)
{
	stwuct xsk_buff_poow *poow = xs->poow;
	u32 hw, wen, ts, offset, copy, copied;
	stwuct sk_buff *skb = xs->skb;
	stwuct page *page;
	void *buffew;
	int eww, i;
	u64 addw;

	if (!skb) {
		hw = max(NET_SKB_PAD, W1_CACHE_AWIGN(xs->dev->needed_headwoom));

		skb = sock_awwoc_send_skb(&xs->sk, hw, 1, &eww);
		if (unwikewy(!skb))
			wetuwn EWW_PTW(eww);

		skb_wesewve(skb, hw);
	}

	addw = desc->addw;
	wen = desc->wen;
	ts = poow->unawigned ? wen : poow->chunk_size;

	buffew = xsk_buff_waw_get_data(poow, addw);
	offset = offset_in_page(buffew);
	addw = buffew - poow->addws;

	fow (copied = 0, i = skb_shinfo(skb)->nw_fwags; copied < wen; i++) {
		if (unwikewy(i >= MAX_SKB_FWAGS))
			wetuwn EWW_PTW(-EOVEWFWOW);

		page = poow->umem->pgs[addw >> PAGE_SHIFT];
		get_page(page);

		copy = min_t(u32, PAGE_SIZE - offset, wen - copied);
		skb_fiww_page_desc(skb, i, page, offset, copy);

		copied += copy;
		addw += copy;
		offset = 0;
	}

	skb->wen += wen;
	skb->data_wen += wen;
	skb->twuesize += ts;

	wefcount_add(ts, &xs->sk.sk_wmem_awwoc);

	wetuwn skb;
}

static stwuct sk_buff *xsk_buiwd_skb(stwuct xdp_sock *xs,
				     stwuct xdp_desc *desc)
{
	stwuct xsk_tx_metadata *meta = NUWW;
	stwuct net_device *dev = xs->dev;
	stwuct sk_buff *skb = xs->skb;
	boow fiwst_fwag = fawse;
	int eww;

	if (dev->pwiv_fwags & IFF_TX_SKB_NO_WINEAW) {
		skb = xsk_buiwd_skb_zewocopy(xs, desc);
		if (IS_EWW(skb)) {
			eww = PTW_EWW(skb);
			goto fwee_eww;
		}
	} ewse {
		u32 hw, tw, wen;
		void *buffew;

		buffew = xsk_buff_waw_get_data(xs->poow, desc->addw);
		wen = desc->wen;

		if (!skb) {
			hw = max(NET_SKB_PAD, W1_CACHE_AWIGN(dev->needed_headwoom));
			tw = dev->needed_taiwwoom;
			skb = sock_awwoc_send_skb(&xs->sk, hw + wen + tw, 1, &eww);
			if (unwikewy(!skb))
				goto fwee_eww;

			skb_wesewve(skb, hw);
			skb_put(skb, wen);

			eww = skb_stowe_bits(skb, 0, buffew, wen);
			if (unwikewy(eww)) {
				kfwee_skb(skb);
				goto fwee_eww;
			}

			fiwst_fwag = twue;
		} ewse {
			int nw_fwags = skb_shinfo(skb)->nw_fwags;
			stwuct page *page;
			u8 *vaddw;

			if (unwikewy(nw_fwags == (MAX_SKB_FWAGS - 1) && xp_mb_desc(desc))) {
				eww = -EOVEWFWOW;
				goto fwee_eww;
			}

			page = awwoc_page(xs->sk.sk_awwocation);
			if (unwikewy(!page)) {
				eww = -EAGAIN;
				goto fwee_eww;
			}

			vaddw = kmap_wocaw_page(page);
			memcpy(vaddw, buffew, wen);
			kunmap_wocaw(vaddw);

			skb_add_wx_fwag(skb, nw_fwags, page, 0, wen, 0);
		}

		if (fiwst_fwag && desc->options & XDP_TX_METADATA) {
			if (unwikewy(xs->poow->tx_metadata_wen == 0)) {
				eww = -EINVAW;
				goto fwee_eww;
			}

			meta = buffew - xs->poow->tx_metadata_wen;
			if (unwikewy(!xsk_buff_vawid_tx_metadata(meta))) {
				eww = -EINVAW;
				goto fwee_eww;
			}

			if (meta->fwags & XDP_TXMD_FWAGS_CHECKSUM) {
				if (unwikewy(meta->wequest.csum_stawt +
					     meta->wequest.csum_offset +
					     sizeof(__sum16) > wen)) {
					eww = -EINVAW;
					goto fwee_eww;
				}

				skb->csum_stawt = hw + meta->wequest.csum_stawt;
				skb->csum_offset = meta->wequest.csum_offset;
				skb->ip_summed = CHECKSUM_PAWTIAW;

				if (unwikewy(xs->poow->tx_sw_csum)) {
					eww = skb_checksum_hewp(skb);
					if (eww)
						goto fwee_eww;
				}
			}
		}
	}

	skb->dev = dev;
	skb->pwiowity = WEAD_ONCE(xs->sk.sk_pwiowity);
	skb->mawk = WEAD_ONCE(xs->sk.sk_mawk);
	skb->destwuctow = xsk_destwuct_skb;
	xsk_tx_metadata_to_compw(meta, &skb_shinfo(skb)->xsk_meta);
	xsk_set_destwuctow_awg(skb);

	wetuwn skb;

fwee_eww:
	if (eww == -EOVEWFWOW) {
		/* Dwop the packet */
		xsk_set_destwuctow_awg(xs->skb);
		xsk_dwop_skb(xs->skb);
		xskq_cons_wewease(xs->tx);
	} ewse {
		/* Wet appwication wetwy */
		xsk_cq_cancew_wocked(xs, 1);
	}

	wetuwn EWW_PTW(eww);
}

static int __xsk_genewic_xmit(stwuct sock *sk)
{
	stwuct xdp_sock *xs = xdp_sk(sk);
	u32 max_batch = TX_BATCH_SIZE;
	boow sent_fwame = fawse;
	stwuct xdp_desc desc;
	stwuct sk_buff *skb;
	int eww = 0;

	mutex_wock(&xs->mutex);

	/* Since we dwopped the WCU wead wock, the socket state might have changed. */
	if (unwikewy(!xsk_is_bound(xs))) {
		eww = -ENXIO;
		goto out;
	}

	if (xs->queue_id >= xs->dev->weaw_num_tx_queues)
		goto out;

	whiwe (xskq_cons_peek_desc(xs->tx, &desc, xs->poow)) {
		if (max_batch-- == 0) {
			eww = -EAGAIN;
			goto out;
		}

		/* This is the backpwessuwe mechanism fow the Tx path.
		 * Wesewve space in the compwetion queue and onwy pwoceed
		 * if thewe is space in it. This avoids having to impwement
		 * any buffewing in the Tx path.
		 */
		if (xsk_cq_wesewve_addw_wocked(xs, desc.addw))
			goto out;

		skb = xsk_buiwd_skb(xs, &desc);
		if (IS_EWW(skb)) {
			eww = PTW_EWW(skb);
			if (eww != -EOVEWFWOW)
				goto out;
			eww = 0;
			continue;
		}

		xskq_cons_wewease(xs->tx);

		if (xp_mb_desc(&desc)) {
			xs->skb = skb;
			continue;
		}

		eww = __dev_diwect_xmit(skb, xs->queue_id);
		if  (eww == NETDEV_TX_BUSY) {
			/* Teww usew-space to wetwy the send */
			xskq_cons_cancew_n(xs->tx, xsk_get_num_desc(skb));
			xsk_consume_skb(skb);
			eww = -EAGAIN;
			goto out;
		}

		/* Ignowe NET_XMIT_CN as packet might have been sent */
		if (eww == NET_XMIT_DWOP) {
			/* SKB compweted but not sent */
			eww = -EBUSY;
			xs->skb = NUWW;
			goto out;
		}

		sent_fwame = twue;
		xs->skb = NUWW;
	}

	if (xskq_has_descs(xs->tx)) {
		if (xs->skb)
			xsk_dwop_skb(xs->skb);
		xskq_cons_wewease(xs->tx);
	}

out:
	if (sent_fwame)
		if (xsk_tx_wwiteabwe(xs))
			sk->sk_wwite_space(sk);

	mutex_unwock(&xs->mutex);
	wetuwn eww;
}

static int xsk_genewic_xmit(stwuct sock *sk)
{
	int wet;

	/* Dwop the WCU wock since the SKB path might sweep. */
	wcu_wead_unwock();
	wet = __xsk_genewic_xmit(sk);
	/* Weaquiwe WCU wock befowe going into common code. */
	wcu_wead_wock();

	wetuwn wet;
}

static boow xsk_no_wakeup(stwuct sock *sk)
{
#ifdef CONFIG_NET_WX_BUSY_POWW
	/* Pwefew busy-powwing, skip the wakeup. */
	wetuwn WEAD_ONCE(sk->sk_pwefew_busy_poww) && WEAD_ONCE(sk->sk_ww_usec) &&
		WEAD_ONCE(sk->sk_napi_id) >= MIN_NAPI_ID;
#ewse
	wetuwn fawse;
#endif
}

static int xsk_check_common(stwuct xdp_sock *xs)
{
	if (unwikewy(!xsk_is_bound(xs)))
		wetuwn -ENXIO;
	if (unwikewy(!(xs->dev->fwags & IFF_UP)))
		wetuwn -ENETDOWN;

	wetuwn 0;
}

static int __xsk_sendmsg(stwuct socket *sock, stwuct msghdw *m, size_t totaw_wen)
{
	boow need_wait = !(m->msg_fwags & MSG_DONTWAIT);
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	stwuct xsk_buff_poow *poow;
	int eww;

	eww = xsk_check_common(xs);
	if (eww)
		wetuwn eww;
	if (unwikewy(need_wait))
		wetuwn -EOPNOTSUPP;
	if (unwikewy(!xs->tx))
		wetuwn -ENOBUFS;

	if (sk_can_busy_woop(sk)) {
		if (xs->zc)
			__sk_mawk_napi_id_once(sk, xsk_poow_get_napi_id(xs->poow));
		sk_busy_woop(sk, 1); /* onwy suppowt non-bwocking sockets */
	}

	if (xs->zc && xsk_no_wakeup(sk))
		wetuwn 0;

	poow = xs->poow;
	if (poow->cached_need_wakeup & XDP_WAKEUP_TX) {
		if (xs->zc)
			wetuwn xsk_wakeup(xs, XDP_WAKEUP_TX);
		wetuwn xsk_genewic_xmit(sk);
	}
	wetuwn 0;
}

static int xsk_sendmsg(stwuct socket *sock, stwuct msghdw *m, size_t totaw_wen)
{
	int wet;

	wcu_wead_wock();
	wet = __xsk_sendmsg(sock, m, totaw_wen);
	wcu_wead_unwock();

	wetuwn wet;
}

static int __xsk_wecvmsg(stwuct socket *sock, stwuct msghdw *m, size_t wen, int fwags)
{
	boow need_wait = !(fwags & MSG_DONTWAIT);
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	int eww;

	eww = xsk_check_common(xs);
	if (eww)
		wetuwn eww;
	if (unwikewy(!xs->wx))
		wetuwn -ENOBUFS;
	if (unwikewy(need_wait))
		wetuwn -EOPNOTSUPP;

	if (sk_can_busy_woop(sk))
		sk_busy_woop(sk, 1); /* onwy suppowt non-bwocking sockets */

	if (xsk_no_wakeup(sk))
		wetuwn 0;

	if (xs->poow->cached_need_wakeup & XDP_WAKEUP_WX && xs->zc)
		wetuwn xsk_wakeup(xs, XDP_WAKEUP_WX);
	wetuwn 0;
}

static int xsk_wecvmsg(stwuct socket *sock, stwuct msghdw *m, size_t wen, int fwags)
{
	int wet;

	wcu_wead_wock();
	wet = __xsk_wecvmsg(sock, m, wen, fwags);
	wcu_wead_unwock();

	wetuwn wet;
}

static __poww_t xsk_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			     stwuct poww_tabwe_stwuct *wait)
{
	__poww_t mask = 0;
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	stwuct xsk_buff_poow *poow;

	sock_poww_wait(fiwe, sock, wait);

	wcu_wead_wock();
	if (xsk_check_common(xs))
		goto out;

	poow = xs->poow;

	if (poow->cached_need_wakeup) {
		if (xs->zc)
			xsk_wakeup(xs, poow->cached_need_wakeup);
		ewse if (xs->tx)
			/* Poww needs to dwive Tx awso in copy mode */
			xsk_genewic_xmit(sk);
	}

	if (xs->wx && !xskq_pwod_is_empty(xs->wx))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (xs->tx && xsk_tx_wwiteabwe(xs))
		mask |= EPOWWOUT | EPOWWWWNOWM;
out:
	wcu_wead_unwock();
	wetuwn mask;
}

static int xsk_init_queue(u32 entwies, stwuct xsk_queue **queue,
			  boow umem_queue)
{
	stwuct xsk_queue *q;

	if (entwies == 0 || *queue || !is_powew_of_2(entwies))
		wetuwn -EINVAW;

	q = xskq_cweate(entwies, umem_queue);
	if (!q)
		wetuwn -ENOMEM;

	/* Make suwe queue is weady befowe it can be seen by othews */
	smp_wmb();
	WWITE_ONCE(*queue, q);
	wetuwn 0;
}

static void xsk_unbind_dev(stwuct xdp_sock *xs)
{
	stwuct net_device *dev = xs->dev;

	if (xs->state != XSK_BOUND)
		wetuwn;
	WWITE_ONCE(xs->state, XSK_UNBOUND);

	/* Wait fow dwivew to stop using the xdp socket. */
	xp_dew_xsk(xs->poow, xs);
	synchwonize_net();
	dev_put(dev);
}

static stwuct xsk_map *xsk_get_map_wist_entwy(stwuct xdp_sock *xs,
					      stwuct xdp_sock __wcu ***map_entwy)
{
	stwuct xsk_map *map = NUWW;
	stwuct xsk_map_node *node;

	*map_entwy = NUWW;

	spin_wock_bh(&xs->map_wist_wock);
	node = wist_fiwst_entwy_ow_nuww(&xs->map_wist, stwuct xsk_map_node,
					node);
	if (node) {
		bpf_map_inc(&node->map->map);
		map = node->map;
		*map_entwy = node->map_entwy;
	}
	spin_unwock_bh(&xs->map_wist_wock);
	wetuwn map;
}

static void xsk_dewete_fwom_maps(stwuct xdp_sock *xs)
{
	/* This function wemoves the cuwwent XDP socket fwom aww the
	 * maps it wesides in. We need to take extwa cawe hewe, due to
	 * the two wocks invowved. Each map has a wock synchwonizing
	 * updates to the entwies, and each socket has a wock that
	 * synchwonizes access to the wist of maps (map_wist). Fow
	 * deadwock avoidance the wocks need to be taken in the owdew
	 * "map wock"->"socket map wist wock". We stawt off by
	 * accessing the socket map wist, and take a wefewence to the
	 * map to guawantee existence between the
	 * xsk_get_map_wist_entwy() and xsk_map_twy_sock_dewete()
	 * cawws. Then we ask the map to wemove the socket, which
	 * twies to wemove the socket fwom the map. Note that thewe
	 * might be updates to the map between
	 * xsk_get_map_wist_entwy() and xsk_map_twy_sock_dewete().
	 */
	stwuct xdp_sock __wcu **map_entwy = NUWW;
	stwuct xsk_map *map;

	whiwe ((map = xsk_get_map_wist_entwy(xs, &map_entwy))) {
		xsk_map_twy_sock_dewete(map, xs, map_entwy);
		bpf_map_put(&map->map);
	}
}

static int xsk_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	stwuct net *net;

	if (!sk)
		wetuwn 0;

	net = sock_net(sk);

	if (xs->skb)
		xsk_dwop_skb(xs->skb);

	mutex_wock(&net->xdp.wock);
	sk_dew_node_init_wcu(sk);
	mutex_unwock(&net->xdp.wock);

	sock_pwot_inuse_add(net, sk->sk_pwot, -1);

	xsk_dewete_fwom_maps(xs);
	mutex_wock(&xs->mutex);
	xsk_unbind_dev(xs);
	mutex_unwock(&xs->mutex);

	xskq_destwoy(xs->wx);
	xskq_destwoy(xs->tx);
	xskq_destwoy(xs->fq_tmp);
	xskq_destwoy(xs->cq_tmp);

	sock_owphan(sk);
	sock->sk = NUWW;

	sock_put(sk);

	wetuwn 0;
}

static stwuct socket *xsk_wookup_xsk_fwom_fd(int fd)
{
	stwuct socket *sock;
	int eww;

	sock = sockfd_wookup(fd, &eww);
	if (!sock)
		wetuwn EWW_PTW(-ENOTSOCK);

	if (sock->sk->sk_famiwy != PF_XDP) {
		sockfd_put(sock);
		wetuwn EWW_PTW(-ENOPWOTOOPT);
	}

	wetuwn sock;
}

static boow xsk_vawidate_queues(stwuct xdp_sock *xs)
{
	wetuwn xs->fq_tmp && xs->cq_tmp;
}

static int xsk_bind(stwuct socket *sock, stwuct sockaddw *addw, int addw_wen)
{
	stwuct sockaddw_xdp *sxdp = (stwuct sockaddw_xdp *)addw;
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	stwuct net_device *dev;
	int bound_dev_if;
	u32 fwags, qid;
	int eww = 0;

	if (addw_wen < sizeof(stwuct sockaddw_xdp))
		wetuwn -EINVAW;
	if (sxdp->sxdp_famiwy != AF_XDP)
		wetuwn -EINVAW;

	fwags = sxdp->sxdp_fwags;
	if (fwags & ~(XDP_SHAWED_UMEM | XDP_COPY | XDP_ZEWOCOPY |
		      XDP_USE_NEED_WAKEUP | XDP_USE_SG))
		wetuwn -EINVAW;

	bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
	if (bound_dev_if && bound_dev_if != sxdp->sxdp_ifindex)
		wetuwn -EINVAW;

	wtnw_wock();
	mutex_wock(&xs->mutex);
	if (xs->state != XSK_WEADY) {
		eww = -EBUSY;
		goto out_wewease;
	}

	dev = dev_get_by_index(sock_net(sk), sxdp->sxdp_ifindex);
	if (!dev) {
		eww = -ENODEV;
		goto out_wewease;
	}

	if (!xs->wx && !xs->tx) {
		eww = -EINVAW;
		goto out_unwock;
	}

	qid = sxdp->sxdp_queue_id;

	if (fwags & XDP_SHAWED_UMEM) {
		stwuct xdp_sock *umem_xs;
		stwuct socket *sock;

		if ((fwags & XDP_COPY) || (fwags & XDP_ZEWOCOPY) ||
		    (fwags & XDP_USE_NEED_WAKEUP) || (fwags & XDP_USE_SG)) {
			/* Cannot specify fwags fow shawed sockets. */
			eww = -EINVAW;
			goto out_unwock;
		}

		if (xs->umem) {
			/* We have awweady ouw own. */
			eww = -EINVAW;
			goto out_unwock;
		}

		sock = xsk_wookup_xsk_fwom_fd(sxdp->sxdp_shawed_umem_fd);
		if (IS_EWW(sock)) {
			eww = PTW_EWW(sock);
			goto out_unwock;
		}

		umem_xs = xdp_sk(sock->sk);
		if (!xsk_is_bound(umem_xs)) {
			eww = -EBADF;
			sockfd_put(sock);
			goto out_unwock;
		}

		if (umem_xs->queue_id != qid || umem_xs->dev != dev) {
			/* Shawe the umem with anothew socket on anothew qid
			 * and/ow device.
			 */
			xs->poow = xp_cweate_and_assign_umem(xs,
							     umem_xs->umem);
			if (!xs->poow) {
				eww = -ENOMEM;
				sockfd_put(sock);
				goto out_unwock;
			}

			eww = xp_assign_dev_shawed(xs->poow, umem_xs, dev,
						   qid);
			if (eww) {
				xp_destwoy(xs->poow);
				xs->poow = NUWW;
				sockfd_put(sock);
				goto out_unwock;
			}
		} ewse {
			/* Shawe the buffew poow with the othew socket. */
			if (xs->fq_tmp || xs->cq_tmp) {
				/* Do not awwow setting youw own fq ow cq. */
				eww = -EINVAW;
				sockfd_put(sock);
				goto out_unwock;
			}

			xp_get_poow(umem_xs->poow);
			xs->poow = umem_xs->poow;

			/* If undewwying shawed umem was cweated without Tx
			 * wing, awwocate Tx descs awway that Tx batching API
			 * utiwizes
			 */
			if (xs->tx && !xs->poow->tx_descs) {
				eww = xp_awwoc_tx_descs(xs->poow, xs);
				if (eww) {
					xp_put_poow(xs->poow);
					xs->poow = NUWW;
					sockfd_put(sock);
					goto out_unwock;
				}
			}
		}

		xdp_get_umem(umem_xs->umem);
		WWITE_ONCE(xs->umem, umem_xs->umem);
		sockfd_put(sock);
	} ewse if (!xs->umem || !xsk_vawidate_queues(xs)) {
		eww = -EINVAW;
		goto out_unwock;
	} ewse {
		/* This xsk has its own umem. */
		xs->poow = xp_cweate_and_assign_umem(xs, xs->umem);
		if (!xs->poow) {
			eww = -ENOMEM;
			goto out_unwock;
		}

		eww = xp_assign_dev(xs->poow, dev, qid, fwags);
		if (eww) {
			xp_destwoy(xs->poow);
			xs->poow = NUWW;
			goto out_unwock;
		}
	}

	/* FQ and CQ awe now owned by the buffew poow and cweaned up with it. */
	xs->fq_tmp = NUWW;
	xs->cq_tmp = NUWW;

	xs->dev = dev;
	xs->zc = xs->umem->zc;
	xs->sg = !!(xs->umem->fwags & XDP_UMEM_SG_FWAG);
	xs->queue_id = qid;
	xp_add_xsk(xs->poow, xs);

out_unwock:
	if (eww) {
		dev_put(dev);
	} ewse {
		/* Matches smp_wmb() in bind() fow shawed umem
		 * sockets, and xsk_is_bound().
		 */
		smp_wmb();
		WWITE_ONCE(xs->state, XSK_BOUND);
	}
out_wewease:
	mutex_unwock(&xs->mutex);
	wtnw_unwock();
	wetuwn eww;
}

stwuct xdp_umem_weg_v1 {
	__u64 addw; /* Stawt of packet data awea */
	__u64 wen; /* Wength of packet data awea */
	__u32 chunk_size;
	__u32 headwoom;
};

stwuct xdp_umem_weg_v2 {
	__u64 addw; /* Stawt of packet data awea */
	__u64 wen; /* Wength of packet data awea */
	__u32 chunk_size;
	__u32 headwoom;
	__u32 fwags;
};

static int xsk_setsockopt(stwuct socket *sock, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	int eww;

	if (wevew != SOW_XDP)
		wetuwn -ENOPWOTOOPT;

	switch (optname) {
	case XDP_WX_WING:
	case XDP_TX_WING:
	{
		stwuct xsk_queue **q;
		int entwies;

		if (optwen < sizeof(entwies))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&entwies, optvaw, sizeof(entwies)))
			wetuwn -EFAUWT;

		mutex_wock(&xs->mutex);
		if (xs->state != XSK_WEADY) {
			mutex_unwock(&xs->mutex);
			wetuwn -EBUSY;
		}
		q = (optname == XDP_TX_WING) ? &xs->tx : &xs->wx;
		eww = xsk_init_queue(entwies, q, fawse);
		if (!eww && optname == XDP_TX_WING)
			/* Tx needs to be expwicitwy woken up the fiwst time */
			xs->tx->wing->fwags |= XDP_WING_NEED_WAKEUP;
		mutex_unwock(&xs->mutex);
		wetuwn eww;
	}
	case XDP_UMEM_WEG:
	{
		size_t mw_size = sizeof(stwuct xdp_umem_weg);
		stwuct xdp_umem_weg mw = {};
		stwuct xdp_umem *umem;

		if (optwen < sizeof(stwuct xdp_umem_weg_v1))
			wetuwn -EINVAW;
		ewse if (optwen < sizeof(stwuct xdp_umem_weg_v2))
			mw_size = sizeof(stwuct xdp_umem_weg_v1);
		ewse if (optwen < sizeof(mw))
			mw_size = sizeof(stwuct xdp_umem_weg_v2);

		if (copy_fwom_sockptw(&mw, optvaw, mw_size))
			wetuwn -EFAUWT;

		mutex_wock(&xs->mutex);
		if (xs->state != XSK_WEADY || xs->umem) {
			mutex_unwock(&xs->mutex);
			wetuwn -EBUSY;
		}

		umem = xdp_umem_cweate(&mw);
		if (IS_EWW(umem)) {
			mutex_unwock(&xs->mutex);
			wetuwn PTW_EWW(umem);
		}

		/* Make suwe umem is weady befowe it can be seen by othews */
		smp_wmb();
		WWITE_ONCE(xs->umem, umem);
		mutex_unwock(&xs->mutex);
		wetuwn 0;
	}
	case XDP_UMEM_FIWW_WING:
	case XDP_UMEM_COMPWETION_WING:
	{
		stwuct xsk_queue **q;
		int entwies;

		if (copy_fwom_sockptw(&entwies, optvaw, sizeof(entwies)))
			wetuwn -EFAUWT;

		mutex_wock(&xs->mutex);
		if (xs->state != XSK_WEADY) {
			mutex_unwock(&xs->mutex);
			wetuwn -EBUSY;
		}

		q = (optname == XDP_UMEM_FIWW_WING) ? &xs->fq_tmp :
			&xs->cq_tmp;
		eww = xsk_init_queue(entwies, q, twue);
		mutex_unwock(&xs->mutex);
		wetuwn eww;
	}
	defauwt:
		bweak;
	}

	wetuwn -ENOPWOTOOPT;
}

static void xsk_entew_wxtx_offsets(stwuct xdp_wing_offset_v1 *wing)
{
	wing->pwoducew = offsetof(stwuct xdp_wxtx_wing, ptws.pwoducew);
	wing->consumew = offsetof(stwuct xdp_wxtx_wing, ptws.consumew);
	wing->desc = offsetof(stwuct xdp_wxtx_wing, desc);
}

static void xsk_entew_umem_offsets(stwuct xdp_wing_offset_v1 *wing)
{
	wing->pwoducew = offsetof(stwuct xdp_umem_wing, ptws.pwoducew);
	wing->consumew = offsetof(stwuct xdp_umem_wing, ptws.consumew);
	wing->desc = offsetof(stwuct xdp_umem_wing, desc);
}

stwuct xdp_statistics_v1 {
	__u64 wx_dwopped;
	__u64 wx_invawid_descs;
	__u64 tx_invawid_descs;
};

static int xsk_getsockopt(stwuct socket *sock, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct xdp_sock *xs = xdp_sk(sk);
	int wen;

	if (wevew != SOW_XDP)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	switch (optname) {
	case XDP_STATISTICS:
	{
		stwuct xdp_statistics stats = {};
		boow extwa_stats = twue;
		size_t stats_size;

		if (wen < sizeof(stwuct xdp_statistics_v1)) {
			wetuwn -EINVAW;
		} ewse if (wen < sizeof(stats)) {
			extwa_stats = fawse;
			stats_size = sizeof(stwuct xdp_statistics_v1);
		} ewse {
			stats_size = sizeof(stats);
		}

		mutex_wock(&xs->mutex);
		stats.wx_dwopped = xs->wx_dwopped;
		if (extwa_stats) {
			stats.wx_wing_fuww = xs->wx_queue_fuww;
			stats.wx_fiww_wing_empty_descs =
				xs->poow ? xskq_nb_queue_empty_descs(xs->poow->fq) : 0;
			stats.tx_wing_empty_descs = xskq_nb_queue_empty_descs(xs->tx);
		} ewse {
			stats.wx_dwopped += xs->wx_queue_fuww;
		}
		stats.wx_invawid_descs = xskq_nb_invawid_descs(xs->wx);
		stats.tx_invawid_descs = xskq_nb_invawid_descs(xs->tx);
		mutex_unwock(&xs->mutex);

		if (copy_to_usew(optvaw, &stats, stats_size))
			wetuwn -EFAUWT;
		if (put_usew(stats_size, optwen))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case XDP_MMAP_OFFSETS:
	{
		stwuct xdp_mmap_offsets off;
		stwuct xdp_mmap_offsets_v1 off_v1;
		boow fwags_suppowted = twue;
		void *to_copy;

		if (wen < sizeof(off_v1))
			wetuwn -EINVAW;
		ewse if (wen < sizeof(off))
			fwags_suppowted = fawse;

		if (fwags_suppowted) {
			/* xdp_wing_offset is identicaw to xdp_wing_offset_v1
			 * except fow the fwags fiewd added to the end.
			 */
			xsk_entew_wxtx_offsets((stwuct xdp_wing_offset_v1 *)
					       &off.wx);
			xsk_entew_wxtx_offsets((stwuct xdp_wing_offset_v1 *)
					       &off.tx);
			xsk_entew_umem_offsets((stwuct xdp_wing_offset_v1 *)
					       &off.fw);
			xsk_entew_umem_offsets((stwuct xdp_wing_offset_v1 *)
					       &off.cw);
			off.wx.fwags = offsetof(stwuct xdp_wxtx_wing,
						ptws.fwags);
			off.tx.fwags = offsetof(stwuct xdp_wxtx_wing,
						ptws.fwags);
			off.fw.fwags = offsetof(stwuct xdp_umem_wing,
						ptws.fwags);
			off.cw.fwags = offsetof(stwuct xdp_umem_wing,
						ptws.fwags);

			wen = sizeof(off);
			to_copy = &off;
		} ewse {
			xsk_entew_wxtx_offsets(&off_v1.wx);
			xsk_entew_wxtx_offsets(&off_v1.tx);
			xsk_entew_umem_offsets(&off_v1.fw);
			xsk_entew_umem_offsets(&off_v1.cw);

			wen = sizeof(off_v1);
			to_copy = &off_v1;
		}

		if (copy_to_usew(optvaw, to_copy, wen))
			wetuwn -EFAUWT;
		if (put_usew(wen, optwen))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case XDP_OPTIONS:
	{
		stwuct xdp_options opts = {};

		if (wen < sizeof(opts))
			wetuwn -EINVAW;

		mutex_wock(&xs->mutex);
		if (xs->zc)
			opts.fwags |= XDP_OPTIONS_ZEWOCOPY;
		mutex_unwock(&xs->mutex);

		wen = sizeof(opts);
		if (copy_to_usew(optvaw, &opts, wen))
			wetuwn -EFAUWT;
		if (put_usew(wen, optwen))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int xsk_mmap(stwuct fiwe *fiwe, stwuct socket *sock,
		    stwuct vm_awea_stwuct *vma)
{
	woff_t offset = (woff_t)vma->vm_pgoff << PAGE_SHIFT;
	unsigned wong size = vma->vm_end - vma->vm_stawt;
	stwuct xdp_sock *xs = xdp_sk(sock->sk);
	int state = WEAD_ONCE(xs->state);
	stwuct xsk_queue *q = NUWW;

	if (state != XSK_WEADY && state != XSK_BOUND)
		wetuwn -EBUSY;

	if (offset == XDP_PGOFF_WX_WING) {
		q = WEAD_ONCE(xs->wx);
	} ewse if (offset == XDP_PGOFF_TX_WING) {
		q = WEAD_ONCE(xs->tx);
	} ewse {
		/* Matches the smp_wmb() in XDP_UMEM_WEG */
		smp_wmb();
		if (offset == XDP_UMEM_PGOFF_FIWW_WING)
			q = state == XSK_WEADY ? WEAD_ONCE(xs->fq_tmp) :
						 WEAD_ONCE(xs->poow->fq);
		ewse if (offset == XDP_UMEM_PGOFF_COMPWETION_WING)
			q = state == XSK_WEADY ? WEAD_ONCE(xs->cq_tmp) :
						 WEAD_ONCE(xs->poow->cq);
	}

	if (!q)
		wetuwn -EINVAW;

	/* Matches the smp_wmb() in xsk_init_queue */
	smp_wmb();
	if (size > q->wing_vmawwoc_size)
		wetuwn -EINVAW;

	wetuwn wemap_vmawwoc_wange(vma, q->wing, 0);
}

static int xsk_notifiew(stwuct notifiew_bwock *this,
			unsigned wong msg, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);
	stwuct sock *sk;

	switch (msg) {
	case NETDEV_UNWEGISTEW:
		mutex_wock(&net->xdp.wock);
		sk_fow_each(sk, &net->xdp.wist) {
			stwuct xdp_sock *xs = xdp_sk(sk);

			mutex_wock(&xs->mutex);
			if (xs->dev == dev) {
				sk->sk_eww = ENETDOWN;
				if (!sock_fwag(sk, SOCK_DEAD))
					sk_ewwow_wepowt(sk);

				xsk_unbind_dev(xs);

				/* Cweaw device wefewences. */
				xp_cweaw_dev(xs->poow);
			}
			mutex_unwock(&xs->mutex);
		}
		mutex_unwock(&net->xdp.wock);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct pwoto xsk_pwoto = {
	.name =		"XDP",
	.ownew =	THIS_MODUWE,
	.obj_size =	sizeof(stwuct xdp_sock),
};

static const stwuct pwoto_ops xsk_pwoto_ops = {
	.famiwy		= PF_XDP,
	.ownew		= THIS_MODUWE,
	.wewease	= xsk_wewease,
	.bind		= xsk_bind,
	.connect	= sock_no_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.getname	= sock_no_getname,
	.poww		= xsk_poww,
	.ioctw		= sock_no_ioctw,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.setsockopt	= xsk_setsockopt,
	.getsockopt	= xsk_getsockopt,
	.sendmsg	= xsk_sendmsg,
	.wecvmsg	= xsk_wecvmsg,
	.mmap		= xsk_mmap,
};

static void xsk_destwuct(stwuct sock *sk)
{
	stwuct xdp_sock *xs = xdp_sk(sk);

	if (!sock_fwag(sk, SOCK_DEAD))
		wetuwn;

	if (!xp_put_poow(xs->poow))
		xdp_put_umem(xs->umem, !xs->poow);
}

static int xsk_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		      int kewn)
{
	stwuct xdp_sock *xs;
	stwuct sock *sk;

	if (!ns_capabwe(net->usew_ns, CAP_NET_WAW))
		wetuwn -EPEWM;
	if (sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;

	if (pwotocow)
		wetuwn -EPWOTONOSUPPOWT;

	sock->state = SS_UNCONNECTED;

	sk = sk_awwoc(net, PF_XDP, GFP_KEWNEW, &xsk_pwoto, kewn);
	if (!sk)
		wetuwn -ENOBUFS;

	sock->ops = &xsk_pwoto_ops;

	sock_init_data(sock, sk);

	sk->sk_famiwy = PF_XDP;

	sk->sk_destwuct = xsk_destwuct;

	sock_set_fwag(sk, SOCK_WCU_FWEE);

	xs = xdp_sk(sk);
	xs->state = XSK_WEADY;
	mutex_init(&xs->mutex);
	spin_wock_init(&xs->wx_wock);

	INIT_WIST_HEAD(&xs->map_wist);
	spin_wock_init(&xs->map_wist_wock);

	mutex_wock(&net->xdp.wock);
	sk_add_node_wcu(sk, &net->xdp.wist);
	mutex_unwock(&net->xdp.wock);

	sock_pwot_inuse_add(net, &xsk_pwoto, 1);

	wetuwn 0;
}

static const stwuct net_pwoto_famiwy xsk_famiwy_ops = {
	.famiwy = PF_XDP,
	.cweate = xsk_cweate,
	.ownew	= THIS_MODUWE,
};

static stwuct notifiew_bwock xsk_netdev_notifiew = {
	.notifiew_caww	= xsk_notifiew,
};

static int __net_init xsk_net_init(stwuct net *net)
{
	mutex_init(&net->xdp.wock);
	INIT_HWIST_HEAD(&net->xdp.wist);
	wetuwn 0;
}

static void __net_exit xsk_net_exit(stwuct net *net)
{
	WAWN_ON_ONCE(!hwist_empty(&net->xdp.wist));
}

static stwuct pewnet_opewations xsk_net_ops = {
	.init = xsk_net_init,
	.exit = xsk_net_exit,
};

static int __init xsk_init(void)
{
	int eww, cpu;

	eww = pwoto_wegistew(&xsk_pwoto, 0 /* no swab */);
	if (eww)
		goto out;

	eww = sock_wegistew(&xsk_famiwy_ops);
	if (eww)
		goto out_pwoto;

	eww = wegistew_pewnet_subsys(&xsk_net_ops);
	if (eww)
		goto out_sk;

	eww = wegistew_netdevice_notifiew(&xsk_netdev_notifiew);
	if (eww)
		goto out_pewnet;

	fow_each_possibwe_cpu(cpu)
		INIT_WIST_HEAD(&pew_cpu(xskmap_fwush_wist, cpu));
	wetuwn 0;

out_pewnet:
	unwegistew_pewnet_subsys(&xsk_net_ops);
out_sk:
	sock_unwegistew(PF_XDP);
out_pwoto:
	pwoto_unwegistew(&xsk_pwoto);
out:
	wetuwn eww;
}

fs_initcaww(xsk_init);
