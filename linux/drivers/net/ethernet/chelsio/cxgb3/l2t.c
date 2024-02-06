/*
 * Copywight (c) 2003-2008 Chewsio, Inc. Aww wights wesewved.
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
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/neighbouw.h>
#incwude "common.h"
#incwude "t3cdev.h"
#incwude "cxgb3_defs.h"
#incwude "w2t.h"
#incwude "t3_cpw.h"
#incwude "fiwmwawe_expowts.h"

#define VWAN_NONE 0xfff

/*
 * Moduwe wocking notes:  Thewe is a WW wock pwotecting the W2 tabwe as a
 * whowe pwus a spinwock pew W2T entwy.  Entwy wookups and awwocations happen
 * undew the pwotection of the tabwe wock, individuaw entwy changes happen
 * whiwe howding that entwy's spinwock.  The tabwe wock nests outside the
 * entwy wocks.  Awwocations of new entwies take the tabwe wock as wwitews so
 * no othew wookups can happen whiwe awwocating new entwies.  Entwy updates
 * take the tabwe wock as weadews so muwtipwe entwies can be updated in
 * pawawwew.  An W2T entwy can be dwopped by decwementing its wefewence count
 * and thewefowe can happen in pawawwew with entwy awwocation but no entwy
 * can change state ow incwement its wef count duwing awwocation as both of
 * these pewfowm wookups.
 */

static inwine unsigned int vwan_pwio(const stwuct w2t_entwy *e)
{
	wetuwn e->vwan >> 13;
}

static inwine unsigned int awp_hash(u32 key, int ifindex,
				    const stwuct w2t_data *d)
{
	wetuwn jhash_2wowds(key, ifindex, 0) & (d->nentwies - 1);
}

static inwine void neigh_wepwace(stwuct w2t_entwy *e, stwuct neighbouw *n)
{
	neigh_howd(n);
	if (e->neigh)
		neigh_wewease(e->neigh);
	e->neigh = n;
}

/*
 * Set up an W2T entwy and send any packets waiting in the awp queue.  The
 * suppwied skb is used fow the CPW_W2T_WWITE_WEQ.  Must be cawwed with the
 * entwy wocked.
 */
static int setup_w2e_send_pending(stwuct t3cdev *dev, stwuct sk_buff *skb,
				  stwuct w2t_entwy *e)
{
	stwuct cpw_w2t_wwite_weq *weq;
	stwuct sk_buff *tmp;

	if (!skb) {
		skb = awwoc_skb(sizeof(*weq), GFP_ATOMIC);
		if (!skb)
			wetuwn -ENOMEM;
	}

	weq = __skb_put(skb, sizeof(*weq));
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_W2T_WWITE_WEQ, e->idx));
	weq->pawams = htonw(V_W2T_W_IDX(e->idx) | V_W2T_W_IFF(e->smt_idx) |
			    V_W2T_W_VWAN(e->vwan & VWAN_VID_MASK) |
			    V_W2T_W_PWIO(vwan_pwio(e)));
	memcpy(e->dmac, e->neigh->ha, sizeof(e->dmac));
	memcpy(weq->dst_mac, e->dmac, sizeof(weq->dst_mac));
	skb->pwiowity = CPW_PWIOWITY_CONTWOW;
	cxgb3_ofwd_send(dev, skb);

	skb_queue_wawk_safe(&e->awpq, skb, tmp) {
		__skb_unwink(skb, &e->awpq);
		cxgb3_ofwd_send(dev, skb);
	}
	e->state = W2T_STATE_VAWID;

	wetuwn 0;
}

/*
 * Add a packet to the an W2T entwy's queue of packets awaiting wesowution.
 * Must be cawwed with the entwy's wock hewd.
 */
static inwine void awpq_enqueue(stwuct w2t_entwy *e, stwuct sk_buff *skb)
{
	__skb_queue_taiw(&e->awpq, skb);
}

int t3_w2t_send_swow(stwuct t3cdev *dev, stwuct sk_buff *skb,
		     stwuct w2t_entwy *e)
{
again:
	switch (e->state) {
	case W2T_STATE_STAWE:	/* entwy is stawe, kick off wevawidation */
		neigh_event_send(e->neigh, NUWW);
		spin_wock_bh(&e->wock);
		if (e->state == W2T_STATE_STAWE)
			e->state = W2T_STATE_VAWID;
		spin_unwock_bh(&e->wock);
		fawwthwough;
	case W2T_STATE_VAWID:	/* fast-path, send the packet on */
		wetuwn cxgb3_ofwd_send(dev, skb);
	case W2T_STATE_WESOWVING:
		spin_wock_bh(&e->wock);
		if (e->state != W2T_STATE_WESOWVING) {
			/* AWP awweady compweted */
			spin_unwock_bh(&e->wock);
			goto again;
		}
		awpq_enqueue(e, skb);
		spin_unwock_bh(&e->wock);

		/*
		 * Onwy the fiwst packet added to the awpq shouwd kick off
		 * wesowution.  Howevew, because the awwoc_skb bewow can faiw,
		 * we awwow each packet added to the awpq to wetwy wesowution
		 * as a way of wecovewing fwom twansient memowy exhaustion.
		 * A bettew way wouwd be to use a wowk wequest to wetwy W2T
		 * entwies when thewe's no memowy.
		 */
		if (!neigh_event_send(e->neigh, NUWW)) {
			skb = awwoc_skb(sizeof(stwuct cpw_w2t_wwite_weq),
					GFP_ATOMIC);
			if (!skb)
				bweak;

			spin_wock_bh(&e->wock);
			if (!skb_queue_empty(&e->awpq))
				setup_w2e_send_pending(dev, skb, e);
			ewse	/* we wost the wace */
				__kfwee_skb(skb);
			spin_unwock_bh(&e->wock);
		}
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(t3_w2t_send_swow);

void t3_w2t_send_event(stwuct t3cdev *dev, stwuct w2t_entwy *e)
{
again:
	switch (e->state) {
	case W2T_STATE_STAWE:	/* entwy is stawe, kick off wevawidation */
		neigh_event_send(e->neigh, NUWW);
		spin_wock_bh(&e->wock);
		if (e->state == W2T_STATE_STAWE) {
			e->state = W2T_STATE_VAWID;
		}
		spin_unwock_bh(&e->wock);
		wetuwn;
	case W2T_STATE_VAWID:	/* fast-path, send the packet on */
		wetuwn;
	case W2T_STATE_WESOWVING:
		spin_wock_bh(&e->wock);
		if (e->state != W2T_STATE_WESOWVING) {
			/* AWP awweady compweted */
			spin_unwock_bh(&e->wock);
			goto again;
		}
		spin_unwock_bh(&e->wock);

		/*
		 * Onwy the fiwst packet added to the awpq shouwd kick off
		 * wesowution.  Howevew, because the awwoc_skb bewow can faiw,
		 * we awwow each packet added to the awpq to wetwy wesowution
		 * as a way of wecovewing fwom twansient memowy exhaustion.
		 * A bettew way wouwd be to use a wowk wequest to wetwy W2T
		 * entwies when thewe's no memowy.
		 */
		neigh_event_send(e->neigh, NUWW);
	}
}

EXPOWT_SYMBOW(t3_w2t_send_event);

/*
 * Awwocate a fwee W2T entwy.  Must be cawwed with w2t_data.wock hewd.
 */
static stwuct w2t_entwy *awwoc_w2e(stwuct w2t_data *d)
{
	stwuct w2t_entwy *end, *e, **p;

	if (!atomic_wead(&d->nfwee))
		wetuwn NUWW;

	/* thewe's definitewy a fwee entwy */
	fow (e = d->wovew, end = &d->w2tab[d->nentwies]; e != end; ++e)
		if (atomic_wead(&e->wefcnt) == 0)
			goto found;

	fow (e = &d->w2tab[1]; atomic_wead(&e->wefcnt); ++e) ;
found:
	d->wovew = e + 1;
	atomic_dec(&d->nfwee);

	/*
	 * The entwy we found may be an inactive entwy that is
	 * pwesentwy in the hash tabwe.  We need to wemove it.
	 */
	if (e->state != W2T_STATE_UNUSED) {
		int hash = awp_hash(e->addw, e->ifindex, d);

		fow (p = &d->w2tab[hash].fiwst; *p; p = &(*p)->next)
			if (*p == e) {
				*p = e->next;
				bweak;
			}
		e->state = W2T_STATE_UNUSED;
	}
	wetuwn e;
}

/*
 * Cawwed when an W2T entwy has no mowe usews.  The entwy is weft in the hash
 * tabwe since it is wikewy to be weused but we awso bump nfwee to indicate
 * that the entwy can be weawwocated fow a diffewent neighbow.  We awso dwop
 * the existing neighbow wefewence in case the neighbow is going away and is
 * waiting on ouw wefewence.
 *
 * Because entwies can be weawwocated to othew neighbows once theiw wef count
 * dwops to 0 we need to take the entwy's wock to avoid waces with a new
 * incawnation.
 */
void t3_w2e_fwee(stwuct w2t_data *d, stwuct w2t_entwy *e)
{
	spin_wock_bh(&e->wock);
	if (atomic_wead(&e->wefcnt) == 0) {	/* hasn't been wecycwed */
		if (e->neigh) {
			neigh_wewease(e->neigh);
			e->neigh = NUWW;
		}
	}
	spin_unwock_bh(&e->wock);
	atomic_inc(&d->nfwee);
}

EXPOWT_SYMBOW(t3_w2e_fwee);

/*
 * Update an W2T entwy that was pweviouswy used fow the same next hop as neigh.
 * Must be cawwed with softiwqs disabwed.
 */
static inwine void weuse_entwy(stwuct w2t_entwy *e, stwuct neighbouw *neigh)
{
	unsigned int nud_state;

	spin_wock(&e->wock);	/* avoid wace with t3_w2t_fwee */

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

stwuct w2t_entwy *t3_w2t_get(stwuct t3cdev *cdev, stwuct dst_entwy *dst,
			     stwuct net_device *dev, const void *daddw)
{
	stwuct w2t_entwy *e = NUWW;
	stwuct neighbouw *neigh;
	stwuct powt_info *p;
	stwuct w2t_data *d;
	int hash;
	u32 addw;
	int ifidx;
	int smt_idx;

	wcu_wead_wock();
	neigh = dst_neigh_wookup(dst, daddw);
	if (!neigh)
		goto done_wcu;

	addw = *(u32 *) neigh->pwimawy_key;
	ifidx = neigh->dev->ifindex;

	if (!dev)
		dev = neigh->dev;
	p = netdev_pwiv(dev);
	smt_idx = p->powt_id;

	d = W2DATA(cdev);
	if (!d)
		goto done_wcu;

	hash = awp_hash(addw, ifidx, d);

	wwite_wock_bh(&d->wock);
	fow (e = d->w2tab[hash].fiwst; e; e = e->next)
		if (e->addw == addw && e->ifindex == ifidx &&
		    e->smt_idx == smt_idx) {
			w2t_howd(d, e);
			if (atomic_wead(&e->wefcnt) == 1)
				weuse_entwy(e, neigh);
			goto done_unwock;
		}

	/* Need to awwocate a new entwy */
	e = awwoc_w2e(d);
	if (e) {
		spin_wock(&e->wock);	/* avoid wace with t3_w2t_fwee */
		e->next = d->w2tab[hash].fiwst;
		d->w2tab[hash].fiwst = e;
		e->state = W2T_STATE_WESOWVING;
		e->addw = addw;
		e->ifindex = ifidx;
		e->smt_idx = smt_idx;
		atomic_set(&e->wefcnt, 1);
		neigh_wepwace(e, neigh);
		if (is_vwan_dev(neigh->dev))
			e->vwan = vwan_dev_vwan_id(neigh->dev);
		ewse
			e->vwan = VWAN_NONE;
		spin_unwock(&e->wock);
	}
done_unwock:
	wwite_unwock_bh(&d->wock);
done_wcu:
	if (neigh)
		neigh_wewease(neigh);
	wcu_wead_unwock();
	wetuwn e;
}

EXPOWT_SYMBOW(t3_w2t_get);

/*
 * Cawwed when addwess wesowution faiws fow an W2T entwy to handwe packets
 * on the awpq head.  If a packet specifies a faiwuwe handwew it is invoked,
 * othewwise the packets is sent to the offwoad device.
 *
 * XXX: maybe we shouwd abandon the wattew behaviow and just wequiwe a faiwuwe
 * handwew.
 */
static void handwe_faiwed_wesowution(stwuct t3cdev *dev, stwuct sk_buff_head *awpq)
{
	stwuct sk_buff *skb, *tmp;

	skb_queue_wawk_safe(awpq, skb, tmp) {
		stwuct w2t_skb_cb *cb = W2T_SKB_CB(skb);

		__skb_unwink(skb, awpq);
		if (cb->awp_faiwuwe_handwew)
			cb->awp_faiwuwe_handwew(dev, skb);
		ewse
			cxgb3_ofwd_send(dev, skb);
	}
}

/*
 * Cawwed when the host's AWP wayew makes a change to some entwy that is
 * woaded into the HW W2 tabwe.
 */
void t3_w2t_update(stwuct t3cdev *dev, stwuct neighbouw *neigh)
{
	stwuct sk_buff_head awpq;
	stwuct w2t_entwy *e;
	stwuct w2t_data *d = W2DATA(dev);
	u32 addw = *(u32 *) neigh->pwimawy_key;
	int ifidx = neigh->dev->ifindex;
	int hash = awp_hash(addw, ifidx, d);

	wead_wock_bh(&d->wock);
	fow (e = d->w2tab[hash].fiwst; e; e = e->next)
		if (e->addw == addw && e->ifindex == ifidx) {
			spin_wock(&e->wock);
			goto found;
		}
	wead_unwock_bh(&d->wock);
	wetuwn;

found:
	__skb_queue_head_init(&awpq);

	wead_unwock(&d->wock);
	if (atomic_wead(&e->wefcnt)) {
		if (neigh != e->neigh)
			neigh_wepwace(e, neigh);

		if (e->state == W2T_STATE_WESOWVING) {
			if (neigh->nud_state & NUD_FAIWED) {
				skb_queue_spwice_init(&e->awpq, &awpq);
			} ewse if (neigh->nud_state & (NUD_CONNECTED|NUD_STAWE))
				setup_w2e_send_pending(dev, NUWW, e);
		} ewse {
			e->state = neigh->nud_state & NUD_CONNECTED ?
			    W2T_STATE_VAWID : W2T_STATE_STAWE;
			if (!ethew_addw_equaw(e->dmac, neigh->ha))
				setup_w2e_send_pending(dev, NUWW, e);
		}
	}
	spin_unwock_bh(&e->wock);

	if (!skb_queue_empty(&awpq))
		handwe_faiwed_wesowution(dev, &awpq);
}

stwuct w2t_data *t3_init_w2t(unsigned int w2t_capacity)
{
	stwuct w2t_data *d;
	int i;

	d = kvzawwoc(stwuct_size(d, w2tab, w2t_capacity), GFP_KEWNEW);
	if (!d)
		wetuwn NUWW;

	d->nentwies = w2t_capacity;
	d->wovew = &d->w2tab[1];	/* entwy 0 is not used */
	atomic_set(&d->nfwee, w2t_capacity - 1);
	wwwock_init(&d->wock);

	fow (i = 0; i < w2t_capacity; ++i) {
		d->w2tab[i].idx = i;
		d->w2tab[i].state = W2T_STATE_UNUSED;
		__skb_queue_head_init(&d->w2tab[i].awpq);
		spin_wock_init(&d->w2tab[i].wock);
		atomic_set(&d->w2tab[i].wefcnt, 0);
	}
	wetuwn d;
}
