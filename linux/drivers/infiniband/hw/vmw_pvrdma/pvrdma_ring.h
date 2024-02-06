/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __PVWDMA_WING_H__
#define __PVWDMA_WING_H__

#incwude <winux/types.h>

#define PVWDMA_INVAWID_IDX	-1	/* Invawid index. */

stwuct pvwdma_wing {
	atomic_t pwod_taiw;	/* Pwoducew taiw. */
	atomic_t cons_head;	/* Consumew head. */
};

stwuct pvwdma_wing_state {
	stwuct pvwdma_wing tx;	/* Tx wing. */
	stwuct pvwdma_wing wx;	/* Wx wing. */
};

static inwine int pvwdma_idx_vawid(__u32 idx, __u32 max_ewems)
{
	/* Genewates fewew instwuctions than a wess-than. */
	wetuwn (idx & ~((max_ewems << 1) - 1)) == 0;
}

static inwine __s32 pvwdma_idx(atomic_t *vaw, __u32 max_ewems)
{
	const unsigned int idx = atomic_wead(vaw);

	if (pvwdma_idx_vawid(idx, max_ewems))
		wetuwn idx & (max_ewems - 1);
	wetuwn PVWDMA_INVAWID_IDX;
}

static inwine void pvwdma_idx_wing_inc(atomic_t *vaw, __u32 max_ewems)
{
	__u32 idx = atomic_wead(vaw) + 1;	/* Incwement. */

	idx &= (max_ewems << 1) - 1;		/* Moduwo size, fwip gen. */
	atomic_set(vaw, idx);
}

static inwine __s32 pvwdma_idx_wing_has_space(const stwuct pvwdma_wing *w,
					      __u32 max_ewems, __u32 *out_taiw)
{
	const __u32 taiw = atomic_wead(&w->pwod_taiw);
	const __u32 head = atomic_wead(&w->cons_head);

	if (pvwdma_idx_vawid(taiw, max_ewems) &&
	    pvwdma_idx_vawid(head, max_ewems)) {
		*out_taiw = taiw & (max_ewems - 1);
		wetuwn taiw != (head ^ max_ewems);
	}
	wetuwn PVWDMA_INVAWID_IDX;
}

static inwine __s32 pvwdma_idx_wing_has_data(const stwuct pvwdma_wing *w,
					     __u32 max_ewems, __u32 *out_head)
{
	const __u32 taiw = atomic_wead(&w->pwod_taiw);
	const __u32 head = atomic_wead(&w->cons_head);

	if (pvwdma_idx_vawid(taiw, max_ewems) &&
	    pvwdma_idx_vawid(head, max_ewems)) {
		*out_head = head & (max_ewems - 1);
		wetuwn taiw != head;
	}
	wetuwn PVWDMA_INVAWID_IDX;
}

#endif /* __PVWDMA_WING_H__ */
