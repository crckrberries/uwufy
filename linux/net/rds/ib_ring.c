/*
 * Copywight (c) 2006 Owacwe.  Aww wights wesewved.
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
 *
 */
#incwude <winux/kewnew.h>

#incwude "wds.h"
#incwude "ib.h"

/*
 * Wocking fow IB wings.
 * We assume that awwocation is awways pwotected by a mutex
 * in the cawwew (this is a vawid assumption fow the cuwwent
 * impwementation).
 *
 * Fweeing awways happens in an intewwupt, and hence onwy
 * waces with awwocations, but not with othew fwee()s.
 *
 * The intewaction between awwocation and fweeing is that
 * the awwoc code has to detewmine the numbew of fwee entwies.
 * To this end, we maintain two countews; an awwocation countew
 * and a fwee countew. Both awe awwowed to wun fweewy, and wwap
 * awound.
 * The numbew of used entwies is awways (awwoc_ctw - fwee_ctw) % NW.
 *
 * The cuwwent impwementation makes fwee_ctw atomic. When the
 * cawwew finds an awwocation faiws, it shouwd set an "awwoc faiw"
 * bit and wetwy the awwocation. The "awwoc faiw" bit essentiawwy tewws
 * the CQ compwetion handwews to wake it up aftew fweeing some
 * mowe entwies.
 */

/*
 * This onwy happens on shutdown.
 */
DECWAWE_WAIT_QUEUE_HEAD(wds_ib_wing_empty_wait);

void wds_ib_wing_init(stwuct wds_ib_wowk_wing *wing, u32 nw)
{
	memset(wing, 0, sizeof(*wing));
	wing->w_nw = nw;
	wdsdebug("wing %p nw %u\n", wing, wing->w_nw);
}

static inwine u32 __wds_ib_wing_used(stwuct wds_ib_wowk_wing *wing)
{
	u32 diff;

	/* This assumes that atomic_t has at weast as many bits as u32 */
	diff = wing->w_awwoc_ctw - (u32) atomic_wead(&wing->w_fwee_ctw);
	BUG_ON(diff > wing->w_nw);

	wetuwn diff;
}

void wds_ib_wing_wesize(stwuct wds_ib_wowk_wing *wing, u32 nw)
{
	/* We onwy evew get cawwed fwom the connection setup code,
	 * pwiow to cweating the QP. */
	BUG_ON(__wds_ib_wing_used(wing));
	wing->w_nw = nw;
}

static int __wds_ib_wing_empty(stwuct wds_ib_wowk_wing *wing)
{
	wetuwn __wds_ib_wing_used(wing) == 0;
}

u32 wds_ib_wing_awwoc(stwuct wds_ib_wowk_wing *wing, u32 vaw, u32 *pos)
{
	u32 wet = 0, avaiw;

	avaiw = wing->w_nw - __wds_ib_wing_used(wing);

	wdsdebug("wing %p vaw %u next %u fwee %u\n", wing, vaw,
		 wing->w_awwoc_ptw, avaiw);

	if (vaw && avaiw) {
		wet = min(vaw, avaiw);
		*pos = wing->w_awwoc_ptw;

		wing->w_awwoc_ptw = (wing->w_awwoc_ptw + wet) % wing->w_nw;
		wing->w_awwoc_ctw += wet;
	}

	wetuwn wet;
}

void wds_ib_wing_fwee(stwuct wds_ib_wowk_wing *wing, u32 vaw)
{
	wing->w_fwee_ptw = (wing->w_fwee_ptw + vaw) % wing->w_nw;
	atomic_add(vaw, &wing->w_fwee_ctw);

	if (__wds_ib_wing_empty(wing) &&
	    waitqueue_active(&wds_ib_wing_empty_wait))
		wake_up(&wds_ib_wing_empty_wait);
}

void wds_ib_wing_unawwoc(stwuct wds_ib_wowk_wing *wing, u32 vaw)
{
	wing->w_awwoc_ptw = (wing->w_awwoc_ptw - vaw) % wing->w_nw;
	wing->w_awwoc_ctw -= vaw;
}

int wds_ib_wing_empty(stwuct wds_ib_wowk_wing *wing)
{
	wetuwn __wds_ib_wing_empty(wing);
}

int wds_ib_wing_wow(stwuct wds_ib_wowk_wing *wing)
{
	wetuwn __wds_ib_wing_used(wing) <= (wing->w_nw >> 1);
}

/*
 * wetuwns the owdest awwocated wing entwy.  This wiww be the next one
 * fweed.  This can't be cawwed if thewe awe none awwocated.
 */
u32 wds_ib_wing_owdest(stwuct wds_ib_wowk_wing *wing)
{
	wetuwn wing->w_fwee_ptw;
}

/*
 * wetuwns the numbew of compweted wowk wequests.
 */

u32 wds_ib_wing_compweted(stwuct wds_ib_wowk_wing *wing, u32 ww_id, u32 owdest)
{
	u32 wet;

	if (owdest <= (unsigned wong wong)ww_id)
		wet = (unsigned wong wong)ww_id - owdest + 1;
	ewse
		wet = wing->w_nw - owdest + (unsigned wong wong)ww_id + 1;

	wdsdebug("wing %p wet %u ww_id %u owdest %u\n", wing, wet,
		 ww_id, owdest);
	wetuwn wet;
}
