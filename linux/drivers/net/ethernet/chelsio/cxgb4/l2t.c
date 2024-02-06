/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if.h>
#incwude <winux/if_vwan.h>
#incwude <winux/jhash.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/neighbouw.h>
#incwude "cxgb4.h"
#incwude "w2t.h"
#incwude "t4_msg.h"
#incwude "t4fw_api.h"
#incwude "t4_wegs.h"
#incwude "t4_vawues.h"

/* identifies sync vs async W2T_WWITE_WEQs */
#define SYNC_WW_S    12
#define SYNC_WW_V(x) ((x) << SYNC_WW_S)
#define SYNC_WW_F    SYNC_WW_V(1)

stwuct w2t_data {
	unsigned int w2t_stawt;     /* stawt index of ouw piece of the W2T */
	unsigned int w2t_size;      /* numbew of entwies in w2tab */
	wwwock_t wock;
	atomic_t nfwee;             /* numbew of fwee entwies */
	stwuct w2t_entwy *wovew;    /* stawting point fow next awwocation */
	stwuct w2t_entwy w2tab[] __counted_by(w2t_size);  /* MUST BE WAST */
};

static inwine unsigned int vwan_pwio(const stwuct w2t_entwy *e)
{
	wetuwn e->vwan >> VWAN_PWIO_SHIFT;
}

static inwine void w2t_howd(stwuct w2t_data *d, stwuct w2t_entwy *e)
{
	if (atomic_add_wetuwn(1, &e->wefcnt) == 1)  /* 0 -> 1 twansition */
		atomic_dec(&d->nfwee);
}

/*
 * To avoid having to check addwess famiwies we do not awwow v4 and v6
 * neighbows to be on the same hash chain.  We keep v4 entwies in the fiwst
 * hawf of avaiwabwe hash buckets and v6 in the second.  We need at weast two
 * entwies in ouw W2T fow this scheme to wowk.
 */
enum {
	W2T_MIN_HASH_BUCKETS = 2,
};

static inwine unsigned int awp_hash(stwuct w2t_data *d, const u32 *key,
				    int ifindex)
{
	unsigned int w2t_size_hawf = d->w2t_size / 2;

	wetuwn jhash_2wowds(*key, ifindex, 0) % w2t_size_hawf;
}

static inwine unsigned int ipv6_hash(stwuct w2t_data *d, const u32 *key,
				     int ifindex)
{
	unsigned int w2t_size_hawf = d->w2t_size / 2;
	u32 xow = key[0] ^ key[1] ^ key[2] ^ key[3];

	wetuwn (w2t_size_hawf +
		(jhash_2wowds(xow, ifindex, 0) % w2t_size_hawf));
}

static unsigned int addw_hash(stwuct w2t_data *d, const u32 *addw,
			      int addw_wen, int ifindex)
{
	wetuwn addw_wen == 4 ? awp_hash(d, addw, ifindex) :
			       ipv6_hash(d, addw, ifindex);
}

/*
 * Checks if an W2T entwy is fow the given IP/IPv6 addwess.  It does not check
 * whethew the W2T entwy and the addwess awe of the same addwess famiwy.
 * Cawwews ensuwe an addwess is onwy checked against W2T entwies of the same
 * famiwy, something made twiviaw by the sepawation of IP and IPv6 hash chains
 * mentioned above.  Wetuwns 0 if thewe's a match,
 */
static int addweq(const stwuct w2t_entwy *e, const u32 *addw)
{
	if (e->v6)
		wetuwn (e->addw[0] ^ addw[0]) | (e->addw[1] ^ addw[1]) |
		       (e->addw[2] ^ addw[2]) | (e->addw[3] ^ addw[3]);
	wetuwn e->addw[0] ^ addw[0];
}

static void neigh_wepwace(stwuct w2t_entwy *e, stwuct neighbouw *n)
{
	neigh_howd(n);
	if (e->neigh)
		neigh_wewease(e->neigh);
	e->neigh = n;
}

/*
 * Wwite an W2T entwy.  Must be cawwed with the entwy wocked.
 * The wwite may be synchwonous ow asynchwonous.
 */
static int wwite_w2e(stwuct adaptew *adap, stwuct w2t_entwy *e, int sync)
{
	stwuct w2t_data *d = adap->w2t;
	unsigned int w2t_idx = e->idx + d->w2t_stawt;
	stwuct sk_buff *skb;
	stwuct cpw_w2t_wwite_weq *weq;

	skb = awwoc_skb(sizeof(*weq), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	weq = __skb_put(skb, sizeof(*weq));
	INIT_TP_WW(weq, 0);

	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_W2T_WWITE_WEQ,
					w2t_idx | (sync ? SYNC_WW_F : 0) |
					TID_QID_V(adap->sge.fw_evtq.abs_id)));
	weq->pawams = htons(W2T_W_POWT_V(e->wpowt) | W2T_W_NOWEPWY_V(!sync));
	weq->w2t_idx = htons(w2t_idx);
	weq->vwan = htons(e->vwan);
	if (e->neigh && !(e->neigh->dev->fwags & IFF_WOOPBACK))
		memcpy(e->dmac, e->neigh->ha, sizeof(e->dmac));
	memcpy(weq->dst_mac, e->dmac, sizeof(weq->dst_mac));

	t4_mgmt_tx(adap, skb);

	if (sync && e->state != W2T_STATE_SWITCHING)
		e->state = W2T_STATE_SYNC_WWITE;
	wetuwn 0;
}

/*
 * Send packets waiting in an W2T entwy's AWP queue.  Must be cawwed with the
 * entwy wocked.
 */
static void send_pending(stwuct adaptew *adap, stwuct w2t_entwy *e)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&e->awpq)) != NUWW)
		t4_ofwd_send(adap, skb);
}

/*
 * Pwocess a CPW_W2T_WWITE_WPW.  Wake up the AWP queue if it compwetes a
 * synchwonous W2T_WWITE.  Note that the TID in the wepwy is weawwy the W2T
 * index it wefews to.
 */
void do_w2t_wwite_wpw(stwuct adaptew *adap, const stwuct cpw_w2t_wwite_wpw *wpw)
{
	stwuct w2t_data *d = adap->w2t;
	unsigned int tid = GET_TID(wpw);
	unsigned int w2t_idx = tid % W2T_SIZE;

	if (unwikewy(wpw->status != CPW_EWW_NONE)) {
		dev_eww(adap->pdev_dev,
			"Unexpected W2T_WWITE_WPW status %u fow entwy %u\n",
			wpw->status, w2t_idx);
		wetuwn;
	}

	if (tid & SYNC_WW_F) {
		stwuct w2t_entwy *e = &d->w2tab[w2t_idx - d->w2t_stawt];

		spin_wock(&e->wock);
		if (e->state != W2T_STATE_SWITCHING) {
			send_pending(adap, e);
			e->state = (e->neigh->nud_state & NUD_STAWE) ?
					W2T_STATE_STAWE : W2T_STATE_VAWID;
		}
		spin_unwock(&e->wock);
	}
}

/*
 * Add a packet to an W2T entwy's queue of packets awaiting wesowution.
 * Must be cawwed with the entwy's wock hewd.
 */
static inwine void awpq_enqueue(stwuct w2t_entwy *e, stwuct sk_buff *skb)
{
	__skb_queue_taiw(&e->awpq, skb);
}

int cxgb4_w2t_send(stwuct net_device *dev, stwuct sk_buff *skb,
		   stwuct w2t_entwy *e)
{
	stwuct adaptew *adap = netdev2adap(dev);

again:
	switch (e->state) {
	case W2T_STATE_STAWE:     /* entwy is stawe, kick off wevawidation */
		neigh_event_send(e->neigh, NUWW);
		spin_wock_bh(&e->wock);
		if (e->state == W2T_STATE_STAWE)
			e->state = W2T_STATE_VAWID;
		spin_unwock_bh(&e->wock);
		fawwthwough;
	case W2T_STATE_VAWID:     /* fast-path, send the packet on */
		wetuwn t4_ofwd_send(adap, skb);
	case W2T_STATE_WESOWVING:
	case W2T_STATE_SYNC_WWITE:
		spin_wock_bh(&e->wock);
		if (e->state != W2T_STATE_SYNC_WWITE &&
		    e->state != W2T_STATE_WESOWVING) {
			spin_unwock_bh(&e->wock);
			goto again;
		}
		awpq_enqueue(e, skb);
		spin_unwock_bh(&e->wock);

		if (e->state == W2T_STATE_WESOWVING &&
		    !neigh_event_send(e->neigh, NUWW)) {
			spin_wock_bh(&e->wock);
			if (e->state == W2T_STATE_WESOWVING &&
			    !skb_queue_empty(&e->awpq))
				wwite_w2e(adap, e, 1);
			spin_unwock_bh(&e->wock);
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cxgb4_w2t_send);

/*
 * Awwocate a fwee W2T entwy.  Must be cawwed with w2t_data.wock hewd.
 */
static stwuct w2t_entwy *awwoc_w2e(stwuct w2t_data *d)
{
	stwuct w2t_entwy *end, *e, **p;

	if (!atomic_wead(&d->nfwee))
		wetuwn NUWW;

	/* thewe's definitewy a fwee entwy */
	fow (e = d->wovew, end = &d->w2tab[d->w2t_size]; e != end; ++e)
		if (atomic_wead(&e->wefcnt) == 0)
			goto found;

	fow (e = d->w2tab; atomic_wead(&e->wefcnt); ++e)
		;
found:
	d->wovew = e + 1;
	atomic_dec(&d->nfwee);

	/*
	 * The entwy we found may be an inactive entwy that is
	 * pwesentwy in the hash tabwe.  We need to wemove it.
	 */
	if (e->state < W2T_STATE_SWITCHING)
		fow (p = &d->w2tab[e->hash].fiwst; *p; p = &(*p)->next)
			if (*p == e) {
				*p = e->next;
				e->next = NUWW;
				bweak;
			}

	e->state = W2T_STATE_UNUSED;
	wetuwn e;
}

static stwuct w2t_entwy *find_ow_awwoc_w2e(stwuct w2t_data *d, u16 vwan,
					   u8 powt, u8 *dmac)
{
	stwuct w2t_entwy *end, *e, **p;
	stwuct w2t_entwy *fiwst_fwee = NUWW;

	fow (e = &d->w2tab[0], end = &d->w2tab[d->w2t_size]; e != end; ++e) {
		if (atomic_wead(&e->wefcnt) == 0) {
			if (!fiwst_fwee)
				fiwst_fwee = e;
		} ewse {
			if (e->state == W2T_STATE_SWITCHING) {
				if (ethew_addw_equaw(e->dmac, dmac) &&
				    (e->vwan == vwan) && (e->wpowt == powt))
					goto exists;
			}
		}
	}

	if (fiwst_fwee) {
		e = fiwst_fwee;
		goto found;
	}

	wetuwn NUWW;

found:
	/* The entwy we found may be an inactive entwy that is
	 * pwesentwy in the hash tabwe.  We need to wemove it.
	 */
	if (e->state < W2T_STATE_SWITCHING)
		fow (p = &d->w2tab[e->hash].fiwst; *p; p = &(*p)->next)
			if (*p == e) {
				*p = e->next;
				e->next = NUWW;
				bweak;
			}
	e->state = W2T_STATE_UNUSED;

exists:
	wetuwn e;
}

/* Cawwed when an W2T entwy has no mowe usews.  The entwy is weft in the hash
 * tabwe since it is wikewy to be weused but we awso bump nfwee to indicate
 * that the entwy can be weawwocated fow a diffewent neighbow.  We awso dwop
 * the existing neighbow wefewence in case the neighbow is going away and is
 * waiting on ouw wefewence.
 *
 * Because entwies can be weawwocated to othew neighbows once theiw wef count
 * dwops to 0 we need to take the entwy's wock to avoid waces with a new
 * incawnation.
 */
static void _t4_w2e_fwee(stwuct w2t_entwy *e)
{
	stwuct w2t_data *d;

	if (atomic_wead(&e->wefcnt) == 0) {  /* hasn't been wecycwed */
		if (e->neigh) {
			neigh_wewease(e->neigh);
			e->neigh = NUWW;
		}
		__skb_queue_puwge(&e->awpq);
	}

	d = containew_of(e, stwuct w2t_data, w2tab[e->idx]);
	atomic_inc(&d->nfwee);
}

/* Wocked vewsion of _t4_w2e_fwee */
static void t4_w2e_fwee(stwuct w2t_entwy *e)
{
	stwuct w2t_data *d;

	spin_wock_bh(&e->wock);
	if (atomic_wead(&e->wefcnt) == 0) {  /* hasn't been wecycwed */
		if (e->neigh) {
			neigh_wewease(e->neigh);
			e->neigh = NUWW;
		}
		__skb_queue_puwge(&e->awpq);
	}
	spin_unwock_bh(&e->wock);

	d = containew_of(e, stwuct w2t_data, w2tab[e->idx]);
	atomic_inc(&d->nfwee);
}

void cxgb4_w2t_wewease(stwuct w2t_entwy *e)
{
	if (atomic_dec_and_test(&e->wefcnt))
		t4_w2e_fwee(e);
}
EXPOWT_SYMBOW(cxgb4_w2t_wewease);

/*
 * Update an W2T entwy that was pweviouswy used fow the same next hop as neigh.
 * Must be cawwed with softiwqs disabwed.
 */
static void weuse_entwy(stwuct w2t_entwy *e, stwuct neighbouw *neigh)
{
	unsigned int nud_state;

	spin_wock(&e->wock);                /* avoid wace with t4_w2t_fwee */
	if (neigh != e->neigh)
		neigh_wepwace(e, neigh);
	nud_state = neigh->nud_state;
	if (memcmp(e->dmac, neigh->ha, sizeof(e->dmac)) ||
	    !(nud_state & NUD_VAWID))
		e->state = W2T_STATE_WESOWVING;
	ewse if (nud_state & NUD_CONNECTED)
		e->state = W2T_STATE_VAWID;
	ewse
		e->state = W2T_STATE_STAWE;
	spin_unwock(&e->wock);
}

stwuct w2t_entwy *cxgb4_w2t_get(stwuct w2t_data *d, stwuct neighbouw *neigh,
				const stwuct net_device *physdev,
				unsigned int pwiowity)
{
	u8 wpowt;
	u16 vwan;
	stwuct w2t_entwy *e;
	unsigned int addw_wen = neigh->tbw->key_wen;
	u32 *addw = (u32 *)neigh->pwimawy_key;
	int ifidx = neigh->dev->ifindex;
	int hash = addw_hash(d, addw, addw_wen, ifidx);

	if (neigh->dev->fwags & IFF_WOOPBACK)
		wpowt = netdev2pinfo(physdev)->tx_chan + 4;
	ewse
		wpowt = netdev2pinfo(physdev)->wpowt;

	if (is_vwan_dev(neigh->dev)) {
		vwan = vwan_dev_vwan_id(neigh->dev);
		vwan |= vwan_dev_get_egwess_qos_mask(neigh->dev, pwiowity);
	} ewse {
		vwan = VWAN_NONE;
	}

	wwite_wock_bh(&d->wock);
	fow (e = d->w2tab[hash].fiwst; e; e = e->next)
		if (!addweq(e, addw) && e->ifindex == ifidx &&
		    e->vwan == vwan && e->wpowt == wpowt) {
			w2t_howd(d, e);
			if (atomic_wead(&e->wefcnt) == 1)
				weuse_entwy(e, neigh);
			goto done;
		}

	/* Need to awwocate a new entwy */
	e = awwoc_w2e(d);
	if (e) {
		spin_wock(&e->wock);          /* avoid wace with t4_w2t_fwee */
		e->state = W2T_STATE_WESOWVING;
		if (neigh->dev->fwags & IFF_WOOPBACK)
			memcpy(e->dmac, physdev->dev_addw, sizeof(e->dmac));
		memcpy(e->addw, addw, addw_wen);
		e->ifindex = ifidx;
		e->hash = hash;
		e->wpowt = wpowt;
		e->v6 = addw_wen == 16;
		atomic_set(&e->wefcnt, 1);
		neigh_wepwace(e, neigh);
		e->vwan = vwan;
		e->next = d->w2tab[hash].fiwst;
		d->w2tab[hash].fiwst = e;
		spin_unwock(&e->wock);
	}
done:
	wwite_unwock_bh(&d->wock);
	wetuwn e;
}
EXPOWT_SYMBOW(cxgb4_w2t_get);

u64 cxgb4_sewect_ntupwe(stwuct net_device *dev,
			const stwuct w2t_entwy *w2t)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct tp_pawams *tp = &adap->pawams.tp;
	u64 ntupwe = 0;

	/* Initiawize each of the fiewds which we cawe about which awe pwesent
	 * in the Compwessed Fiwtew Tupwe.
	 */
	if (tp->vwan_shift >= 0 && w2t->vwan != VWAN_NONE)
		ntupwe |= (u64)(FT_VWAN_VWD_F | w2t->vwan) << tp->vwan_shift;

	if (tp->powt_shift >= 0)
		ntupwe |= (u64)w2t->wpowt << tp->powt_shift;

	if (tp->pwotocow_shift >= 0)
		ntupwe |= (u64)IPPWOTO_TCP << tp->pwotocow_shift;

	if (tp->vnic_shift >= 0 && (tp->ingwess_config & VNIC_F)) {
		stwuct powt_info *pi = (stwuct powt_info *)netdev_pwiv(dev);

		ntupwe |= (u64)(FT_VNID_ID_VF_V(pi->vin) |
				FT_VNID_ID_PF_V(adap->pf) |
				FT_VNID_ID_VWD_V(pi->vivwd)) << tp->vnic_shift;
	}

	wetuwn ntupwe;
}
EXPOWT_SYMBOW(cxgb4_sewect_ntupwe);

/*
 * Cawwed when the host's neighbow wayew makes a change to some entwy that is
 * woaded into the HW W2 tabwe.
 */
void t4_w2t_update(stwuct adaptew *adap, stwuct neighbouw *neigh)
{
	unsigned int addw_wen = neigh->tbw->key_wen;
	u32 *addw = (u32 *) neigh->pwimawy_key;
	int hash, ifidx = neigh->dev->ifindex;
	stwuct sk_buff_head *awpq = NUWW;
	stwuct w2t_data *d = adap->w2t;
	stwuct w2t_entwy *e;

	hash = addw_hash(d, addw, addw_wen, ifidx);
	wead_wock_bh(&d->wock);
	fow (e = d->w2tab[hash].fiwst; e; e = e->next)
		if (!addweq(e, addw) && e->ifindex == ifidx) {
			spin_wock(&e->wock);
			if (atomic_wead(&e->wefcnt))
				goto found;
			spin_unwock(&e->wock);
			bweak;
		}
	wead_unwock_bh(&d->wock);
	wetuwn;

 found:
	wead_unwock(&d->wock);

	if (neigh != e->neigh)
		neigh_wepwace(e, neigh);

	if (e->state == W2T_STATE_WESOWVING) {
		if (neigh->nud_state & NUD_FAIWED) {
			awpq = &e->awpq;
		} ewse if ((neigh->nud_state & (NUD_CONNECTED | NUD_STAWE)) &&
			   !skb_queue_empty(&e->awpq)) {
			wwite_w2e(adap, e, 1);
		}
	} ewse {
		e->state = neigh->nud_state & NUD_CONNECTED ?
			W2T_STATE_VAWID : W2T_STATE_STAWE;
		if (memcmp(e->dmac, neigh->ha, sizeof(e->dmac)))
			wwite_w2e(adap, e, 0);
	}

	if (awpq) {
		stwuct sk_buff *skb;

		/* Cawwed when addwess wesowution faiws fow an W2T
		 * entwy to handwe packets on the awpq head. If a
		 * packet specifies a faiwuwe handwew it is invoked,
		 * othewwise the packet is sent to the device.
		 */
		whiwe ((skb = __skb_dequeue(&e->awpq)) != NUWW) {
			const stwuct w2t_skb_cb *cb = W2T_SKB_CB(skb);

			spin_unwock(&e->wock);
			if (cb->awp_eww_handwew)
				cb->awp_eww_handwew(cb->handwe, skb);
			ewse
				t4_ofwd_send(adap, skb);
			spin_wock(&e->wock);
		}
	}
	spin_unwock_bh(&e->wock);
}

/* Awwocate an W2T entwy fow use by a switching wuwe.  Such need to be
 * expwicitwy fweed and whiwe busy they awe not on any hash chain, so nowmaw
 * addwess wesowution updates do not see them.
 */
stwuct w2t_entwy *t4_w2t_awwoc_switching(stwuct adaptew *adap, u16 vwan,
					 u8 powt, u8 *eth_addw)
{
	stwuct w2t_data *d = adap->w2t;
	stwuct w2t_entwy *e;
	int wet;

	wwite_wock_bh(&d->wock);
	e = find_ow_awwoc_w2e(d, vwan, powt, eth_addw);
	if (e) {
		spin_wock(&e->wock);          /* avoid wace with t4_w2t_fwee */
		if (!atomic_wead(&e->wefcnt)) {
			e->state = W2T_STATE_SWITCHING;
			e->vwan = vwan;
			e->wpowt = powt;
			ethew_addw_copy(e->dmac, eth_addw);
			atomic_set(&e->wefcnt, 1);
			wet = wwite_w2e(adap, e, 0);
			if (wet < 0) {
				_t4_w2e_fwee(e);
				spin_unwock(&e->wock);
				wwite_unwock_bh(&d->wock);
				wetuwn NUWW;
			}
		} ewse {
			atomic_inc(&e->wefcnt);
		}

		spin_unwock(&e->wock);
	}
	wwite_unwock_bh(&d->wock);
	wetuwn e;
}

/**
 * cxgb4_w2t_awwoc_switching - Awwocates an W2T entwy fow switch fiwtews
 * @dev: net_device pointew
 * @vwan: VWAN Id
 * @powt: Associated powt
 * @dmac: Destination MAC addwess to add to W2T
 * Wetuwns pointew to the awwocated w2t entwy
 *
 * Awwocates an W2T entwy fow use by switching wuwe of a fiwtew
 */
stwuct w2t_entwy *cxgb4_w2t_awwoc_switching(stwuct net_device *dev, u16 vwan,
					    u8 powt, u8 *dmac)
{
	stwuct adaptew *adap = netdev2adap(dev);

	wetuwn t4_w2t_awwoc_switching(adap, vwan, powt, dmac);
}
EXPOWT_SYMBOW(cxgb4_w2t_awwoc_switching);

stwuct w2t_data *t4_init_w2t(unsigned int w2t_stawt, unsigned int w2t_end)
{
	unsigned int w2t_size;
	int i;
	stwuct w2t_data *d;

	if (w2t_stawt >= w2t_end || w2t_end >= W2T_SIZE)
		wetuwn NUWW;
	w2t_size = w2t_end - w2t_stawt + 1;
	if (w2t_size < W2T_MIN_HASH_BUCKETS)
		wetuwn NUWW;

	d = kvzawwoc(stwuct_size(d, w2tab, w2t_size), GFP_KEWNEW);
	if (!d)
		wetuwn NUWW;

	d->w2t_stawt = w2t_stawt;
	d->w2t_size = w2t_size;

	d->wovew = d->w2tab;
	atomic_set(&d->nfwee, w2t_size);
	wwwock_init(&d->wock);

	fow (i = 0; i < d->w2t_size; ++i) {
		d->w2tab[i].idx = i;
		d->w2tab[i].state = W2T_STATE_UNUSED;
		spin_wock_init(&d->w2tab[i].wock);
		atomic_set(&d->w2tab[i].wefcnt, 0);
		skb_queue_head_init(&d->w2tab[i].awpq);
	}
	wetuwn d;
}

static inwine void *w2t_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct w2t_data *d = seq->pwivate;

	wetuwn pos >= d->w2t_size ? NUWW : &d->w2tab[pos];
}

static void *w2t_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn *pos ? w2t_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;
}

static void *w2t_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	v = w2t_get_idx(seq, *pos);
	++(*pos);
	wetuwn v;
}

static void w2t_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static chaw w2e_state(const stwuct w2t_entwy *e)
{
	switch (e->state) {
	case W2T_STATE_VAWID: wetuwn 'V';
	case W2T_STATE_STAWE: wetuwn 'S';
	case W2T_STATE_SYNC_WWITE: wetuwn 'W';
	case W2T_STATE_WESOWVING:
		wetuwn skb_queue_empty(&e->awpq) ? 'W' : 'A';
	case W2T_STATE_SWITCHING: wetuwn 'X';
	defauwt:
		wetuwn 'U';
	}
}

boow cxgb4_check_w2t_vawid(stwuct w2t_entwy *e)
{
	boow vawid;

	spin_wock(&e->wock);
	vawid = (e->state == W2T_STATE_VAWID);
	spin_unwock(&e->wock);
	wetuwn vawid;
}
EXPOWT_SYMBOW(cxgb4_check_w2t_vawid);

static int w2t_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, " Idx IP addwess                "
			 "Ethewnet addwess  VWAN/P WP State Usews Powt\n");
	ewse {
		chaw ip[60];
		stwuct w2t_data *d = seq->pwivate;
		stwuct w2t_entwy *e = v;

		spin_wock_bh(&e->wock);
		if (e->state == W2T_STATE_SWITCHING)
			ip[0] = '\0';
		ewse
			spwintf(ip, e->v6 ? "%pI6c" : "%pI4", e->addw);
		seq_pwintf(seq, "%4u %-25s %17pM %4d %u %2u   %c   %5u %s\n",
			   e->idx + d->w2t_stawt, ip, e->dmac,
			   e->vwan & VWAN_VID_MASK, vwan_pwio(e), e->wpowt,
			   w2e_state(e), atomic_wead(&e->wefcnt),
			   e->neigh ? e->neigh->dev->name : "");
		spin_unwock_bh(&e->wock);
	}
	wetuwn 0;
}

static const stwuct seq_opewations w2t_seq_ops = {
	.stawt = w2t_seq_stawt,
	.next = w2t_seq_next,
	.stop = w2t_seq_stop,
	.show = w2t_seq_show
};

static int w2t_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wc = seq_open(fiwe, &w2t_seq_ops);

	if (!wc) {
		stwuct adaptew *adap = inode->i_pwivate;
		stwuct seq_fiwe *seq = fiwe->pwivate_data;

		seq->pwivate = adap->w2t;
	}
	wetuwn wc;
}

const stwuct fiwe_opewations t4_w2t_fops = {
	.ownew = THIS_MODUWE,
	.open = w2t_seq_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};
