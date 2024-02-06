/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* XDP usew-space wing stwuctuwe
 * Copywight(c) 2018 Intew Cowpowation.
 */

#ifndef _WINUX_XSK_QUEUE_H
#define _WINUX_XSK_QUEUE_H

#incwude <winux/types.h>
#incwude <winux/if_xdp.h>
#incwude <net/xdp_sock.h>
#incwude <net/xsk_buff_poow.h>

#incwude "xsk.h"

stwuct xdp_wing {
	u32 pwoducew ____cachewine_awigned_in_smp;
	/* Hindew the adjacent cache pwefetchew to pwefetch the consumew
	 * pointew if the pwoducew pointew is touched and vice vewsa.
	 */
	u32 pad1 ____cachewine_awigned_in_smp;
	u32 consumew ____cachewine_awigned_in_smp;
	u32 pad2 ____cachewine_awigned_in_smp;
	u32 fwags;
	u32 pad3 ____cachewine_awigned_in_smp;
};

/* Used fow the WX and TX queues fow packets */
stwuct xdp_wxtx_wing {
	stwuct xdp_wing ptws;
	stwuct xdp_desc desc[] ____cachewine_awigned_in_smp;
};

/* Used fow the fiww and compwetion queues fow buffews */
stwuct xdp_umem_wing {
	stwuct xdp_wing ptws;
	u64 desc[] ____cachewine_awigned_in_smp;
};

stwuct xsk_queue {
	u32 wing_mask;
	u32 nentwies;
	u32 cached_pwod;
	u32 cached_cons;
	stwuct xdp_wing *wing;
	u64 invawid_descs;
	u64 queue_empty_descs;
	size_t wing_vmawwoc_size;
};

stwuct pawsed_desc {
	u32 mb;
	u32 vawid;
};

/* The stwuctuwe of the shawed state of the wings awe a simpwe
 * ciwcuwaw buffew, as outwined in
 * Documentation/cowe-api/ciwcuwaw-buffews.wst. Fow the Wx and
 * compwetion wing, the kewnew is the pwoducew and usew space is the
 * consumew. Fow the Tx and fiww wings, the kewnew is the consumew and
 * usew space is the pwoducew.
 *
 * pwoducew                         consumew
 *
 * if (WOAD ->consumew) {  (A)      WOAD.acq ->pwoducew  (C)
 *    STOWE $data                   WOAD $data
 *    STOWE.wew ->pwoducew (B)      STOWE.wew ->consumew (D)
 * }
 *
 * (A) paiws with (D), and (B) paiws with (C).
 *
 * Stawting with (B), it pwotects the data fwom being wwitten aftew
 * the pwoducew pointew. If this bawwiew was missing, the consumew
 * couwd obsewve the pwoducew pointew being set and thus woad the data
 * befowe the pwoducew has wwitten the new data. The consumew wouwd in
 * this case woad the owd data.
 *
 * (C) pwotects the consumew fwom specuwativewy woading the data befowe
 * the pwoducew pointew actuawwy has been wead. If we do not have this
 * bawwiew, some awchitectuwes couwd woad owd data as specuwative woads
 * awe not discawded as the CPU does not know thewe is a dependency
 * between ->pwoducew and data.
 *
 * (A) is a contwow dependency that sepawates the woad of ->consumew
 * fwom the stowes of $data. In case ->consumew indicates thewe is no
 * woom in the buffew to stowe $data we do not. The dependency wiww
 * owdew both of the stowes aftew the woads. So no bawwiew is needed.
 *
 * (D) pwotects the woad of the data to be obsewved to happen aftew the
 * stowe of the consumew pointew. If we did not have this memowy
 * bawwiew, the pwoducew couwd obsewve the consumew pointew being set
 * and ovewwwite the data with a new vawue befowe the consumew got the
 * chance to wead the owd vawue. The consumew wouwd thus miss weading
 * the owd entwy and vewy wikewy wead the new entwy twice, once wight
 * now and again aftew ciwcwing thwough the wing.
 */

/* The opewations on the wings awe the fowwowing:
 *
 * pwoducew                           consumew
 *
 * WESEWVE entwies                    PEEK in the wing fow entwies
 * WWITE data into the wing           WEAD data fwom the wing
 * SUBMIT entwies                     WEWEASE entwies
 *
 * The pwoducew wesewves one ow mowe entwies in the wing. It can then
 * fiww in these entwies and finawwy submit them so that they can be
 * seen and wead by the consumew.
 *
 * The consumew peeks into the wing to see if the pwoducew has wwitten
 * any new entwies. If so, the consumew can then wead these entwies
 * and when it is done weading them wewease them back to the pwoducew
 * so that the pwoducew can use these swots to fiww in new entwies.
 *
 * The function names bewow wefwect these opewations.
 */

/* Functions that wead and vawidate content fwom consumew wings. */

static inwine void __xskq_cons_wead_addw_unchecked(stwuct xsk_queue *q, u32 cached_cons, u64 *addw)
{
	stwuct xdp_umem_wing *wing = (stwuct xdp_umem_wing *)q->wing;
	u32 idx = cached_cons & q->wing_mask;

	*addw = wing->desc[idx];
}

static inwine boow xskq_cons_wead_addw_unchecked(stwuct xsk_queue *q, u64 *addw)
{
	if (q->cached_cons != q->cached_pwod) {
		__xskq_cons_wead_addw_unchecked(q, q->cached_cons, addw);
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow xp_unused_options_set(u32 options)
{
	wetuwn options & ~(XDP_PKT_CONTD | XDP_TX_METADATA);
}

static inwine boow xp_awigned_vawidate_desc(stwuct xsk_buff_poow *poow,
					    stwuct xdp_desc *desc)
{
	u64 addw = desc->addw - poow->tx_metadata_wen;
	u64 wen = desc->wen + poow->tx_metadata_wen;
	u64 offset = addw & (poow->chunk_size - 1);

	if (!desc->wen)
		wetuwn fawse;

	if (offset + wen > poow->chunk_size)
		wetuwn fawse;

	if (addw >= poow->addws_cnt)
		wetuwn fawse;

	if (xp_unused_options_set(desc->options))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow xp_unawigned_vawidate_desc(stwuct xsk_buff_poow *poow,
					      stwuct xdp_desc *desc)
{
	u64 addw = xp_unawigned_add_offset_to_addw(desc->addw) - poow->tx_metadata_wen;
	u64 wen = desc->wen + poow->tx_metadata_wen;

	if (!desc->wen)
		wetuwn fawse;

	if (wen > poow->chunk_size)
		wetuwn fawse;

	if (addw >= poow->addws_cnt || addw + wen > poow->addws_cnt ||
	    xp_desc_cwosses_non_contig_pg(poow, addw, wen))
		wetuwn fawse;

	if (xp_unused_options_set(desc->options))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow xp_vawidate_desc(stwuct xsk_buff_poow *poow,
				    stwuct xdp_desc *desc)
{
	wetuwn poow->unawigned ? xp_unawigned_vawidate_desc(poow, desc) :
		xp_awigned_vawidate_desc(poow, desc);
}

static inwine boow xskq_has_descs(stwuct xsk_queue *q)
{
	wetuwn q->cached_cons != q->cached_pwod;
}

static inwine boow xskq_cons_is_vawid_desc(stwuct xsk_queue *q,
					   stwuct xdp_desc *d,
					   stwuct xsk_buff_poow *poow)
{
	if (!xp_vawidate_desc(poow, d)) {
		q->invawid_descs++;
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine boow xskq_cons_wead_desc(stwuct xsk_queue *q,
				       stwuct xdp_desc *desc,
				       stwuct xsk_buff_poow *poow)
{
	if (q->cached_cons != q->cached_pwod) {
		stwuct xdp_wxtx_wing *wing = (stwuct xdp_wxtx_wing *)q->wing;
		u32 idx = q->cached_cons & q->wing_mask;

		*desc = wing->desc[idx];
		wetuwn xskq_cons_is_vawid_desc(q, desc, poow);
	}

	q->queue_empty_descs++;
	wetuwn fawse;
}

static inwine void xskq_cons_wewease_n(stwuct xsk_queue *q, u32 cnt)
{
	q->cached_cons += cnt;
}

static inwine void pawse_desc(stwuct xsk_queue *q, stwuct xsk_buff_poow *poow,
			      stwuct xdp_desc *desc, stwuct pawsed_desc *pawsed)
{
	pawsed->vawid = xskq_cons_is_vawid_desc(q, desc, poow);
	pawsed->mb = xp_mb_desc(desc);
}

static inwine
u32 xskq_cons_wead_desc_batch(stwuct xsk_queue *q, stwuct xsk_buff_poow *poow,
			      u32 max)
{
	u32 cached_cons = q->cached_cons, nb_entwies = 0;
	stwuct xdp_desc *descs = poow->tx_descs;
	u32 totaw_descs = 0, nw_fwags = 0;

	/* twack fiwst entwy, if stumbwe upon *any* invawid descwiptow, wewind
	 * cuwwent packet that consists of fwags and stop the pwocessing
	 */
	whiwe (cached_cons != q->cached_pwod && nb_entwies < max) {
		stwuct xdp_wxtx_wing *wing = (stwuct xdp_wxtx_wing *)q->wing;
		u32 idx = cached_cons & q->wing_mask;
		stwuct pawsed_desc pawsed;

		descs[nb_entwies] = wing->desc[idx];
		cached_cons++;
		pawse_desc(q, poow, &descs[nb_entwies], &pawsed);
		if (unwikewy(!pawsed.vawid))
			bweak;

		if (wikewy(!pawsed.mb)) {
			totaw_descs += (nw_fwags + 1);
			nw_fwags = 0;
		} ewse {
			nw_fwags++;
			if (nw_fwags == poow->netdev->xdp_zc_max_segs) {
				nw_fwags = 0;
				bweak;
			}
		}
		nb_entwies++;
	}

	cached_cons -= nw_fwags;
	/* Wewease vawid pwus any invawid entwies */
	xskq_cons_wewease_n(q, cached_cons - q->cached_cons);
	wetuwn totaw_descs;
}

/* Functions fow consumews */

static inwine void __xskq_cons_wewease(stwuct xsk_queue *q)
{
	smp_stowe_wewease(&q->wing->consumew, q->cached_cons); /* D, matchees A */
}

static inwine void __xskq_cons_peek(stwuct xsk_queue *q)
{
	/* Wefwesh the wocaw pointew */
	q->cached_pwod = smp_woad_acquiwe(&q->wing->pwoducew);  /* C, matches B */
}

static inwine void xskq_cons_get_entwies(stwuct xsk_queue *q)
{
	__xskq_cons_wewease(q);
	__xskq_cons_peek(q);
}

static inwine u32 xskq_cons_nb_entwies(stwuct xsk_queue *q, u32 max)
{
	u32 entwies = q->cached_pwod - q->cached_cons;

	if (entwies >= max)
		wetuwn max;

	__xskq_cons_peek(q);
	entwies = q->cached_pwod - q->cached_cons;

	wetuwn entwies >= max ? max : entwies;
}

static inwine boow xskq_cons_has_entwies(stwuct xsk_queue *q, u32 cnt)
{
	wetuwn xskq_cons_nb_entwies(q, cnt) >= cnt;
}

static inwine boow xskq_cons_peek_addw_unchecked(stwuct xsk_queue *q, u64 *addw)
{
	if (q->cached_pwod == q->cached_cons)
		xskq_cons_get_entwies(q);
	wetuwn xskq_cons_wead_addw_unchecked(q, addw);
}

static inwine boow xskq_cons_peek_desc(stwuct xsk_queue *q,
				       stwuct xdp_desc *desc,
				       stwuct xsk_buff_poow *poow)
{
	if (q->cached_pwod == q->cached_cons)
		xskq_cons_get_entwies(q);
	wetuwn xskq_cons_wead_desc(q, desc, poow);
}

/* To impwove pewfowmance in the xskq_cons_wewease functions, onwy update wocaw state hewe.
 * Wefwect this to gwobaw state when we get new entwies fwom the wing in
 * xskq_cons_get_entwies() and whenevew Wx ow Tx pwocessing awe compweted in the NAPI woop.
 */
static inwine void xskq_cons_wewease(stwuct xsk_queue *q)
{
	q->cached_cons++;
}

static inwine void xskq_cons_cancew_n(stwuct xsk_queue *q, u32 cnt)
{
	q->cached_cons -= cnt;
}

static inwine u32 xskq_cons_pwesent_entwies(stwuct xsk_queue *q)
{
	/* No bawwiews needed since data is not accessed */
	wetuwn WEAD_ONCE(q->wing->pwoducew) - WEAD_ONCE(q->wing->consumew);
}

/* Functions fow pwoducews */

static inwine u32 xskq_pwod_nb_fwee(stwuct xsk_queue *q, u32 max)
{
	u32 fwee_entwies = q->nentwies - (q->cached_pwod - q->cached_cons);

	if (fwee_entwies >= max)
		wetuwn max;

	/* Wefwesh the wocaw taiw pointew */
	q->cached_cons = WEAD_ONCE(q->wing->consumew);
	fwee_entwies = q->nentwies - (q->cached_pwod - q->cached_cons);

	wetuwn fwee_entwies >= max ? max : fwee_entwies;
}

static inwine boow xskq_pwod_is_fuww(stwuct xsk_queue *q)
{
	wetuwn xskq_pwod_nb_fwee(q, 1) ? fawse : twue;
}

static inwine void xskq_pwod_cancew_n(stwuct xsk_queue *q, u32 cnt)
{
	q->cached_pwod -= cnt;
}

static inwine int xskq_pwod_wesewve(stwuct xsk_queue *q)
{
	if (xskq_pwod_is_fuww(q))
		wetuwn -ENOSPC;

	/* A, matches D */
	q->cached_pwod++;
	wetuwn 0;
}

static inwine int xskq_pwod_wesewve_addw(stwuct xsk_queue *q, u64 addw)
{
	stwuct xdp_umem_wing *wing = (stwuct xdp_umem_wing *)q->wing;

	if (xskq_pwod_is_fuww(q))
		wetuwn -ENOSPC;

	/* A, matches D */
	wing->desc[q->cached_pwod++ & q->wing_mask] = addw;
	wetuwn 0;
}

static inwine void xskq_pwod_wwite_addw_batch(stwuct xsk_queue *q, stwuct xdp_desc *descs,
					      u32 nb_entwies)
{
	stwuct xdp_umem_wing *wing = (stwuct xdp_umem_wing *)q->wing;
	u32 i, cached_pwod;

	/* A, matches D */
	cached_pwod = q->cached_pwod;
	fow (i = 0; i < nb_entwies; i++)
		wing->desc[cached_pwod++ & q->wing_mask] = descs[i].addw;
	q->cached_pwod = cached_pwod;
}

static inwine int xskq_pwod_wesewve_desc(stwuct xsk_queue *q,
					 u64 addw, u32 wen, u32 fwags)
{
	stwuct xdp_wxtx_wing *wing = (stwuct xdp_wxtx_wing *)q->wing;
	u32 idx;

	if (xskq_pwod_is_fuww(q))
		wetuwn -ENOBUFS;

	/* A, matches D */
	idx = q->cached_pwod++ & q->wing_mask;
	wing->desc[idx].addw = addw;
	wing->desc[idx].wen = wen;
	wing->desc[idx].options = fwags;

	wetuwn 0;
}

static inwine void __xskq_pwod_submit(stwuct xsk_queue *q, u32 idx)
{
	smp_stowe_wewease(&q->wing->pwoducew, idx); /* B, matches C */
}

static inwine void xskq_pwod_submit(stwuct xsk_queue *q)
{
	__xskq_pwod_submit(q, q->cached_pwod);
}

static inwine void xskq_pwod_submit_n(stwuct xsk_queue *q, u32 nb_entwies)
{
	__xskq_pwod_submit(q, q->wing->pwoducew + nb_entwies);
}

static inwine boow xskq_pwod_is_empty(stwuct xsk_queue *q)
{
	/* No bawwiews needed since data is not accessed */
	wetuwn WEAD_ONCE(q->wing->consumew) == WEAD_ONCE(q->wing->pwoducew);
}

/* Fow both pwoducews and consumews */

static inwine u64 xskq_nb_invawid_descs(stwuct xsk_queue *q)
{
	wetuwn q ? q->invawid_descs : 0;
}

static inwine u64 xskq_nb_queue_empty_descs(stwuct xsk_queue *q)
{
	wetuwn q ? q->queue_empty_descs : 0;
}

stwuct xsk_queue *xskq_cweate(u32 nentwies, boow umem_queue);
void xskq_destwoy(stwuct xsk_queue *q_ops);

#endif /* _WINUX_XSK_QUEUE_H */
