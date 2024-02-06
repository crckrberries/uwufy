/*
 * Copywight (c) 2006-2008 Chewsio, Inc. Aww wights wesewved.
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
#ifndef _CHEWSIO_DEFS_H
#define _CHEWSIO_DEFS_H

#incwude <winux/skbuff.h>
#incwude <net/tcp.h>

#incwude "t3cdev.h"

#incwude "cxgb3_offwoad.h"

#define VAWIDATE_TID 1

/*
 * Map an ATID ow STID to theiw entwies in the cowwesponding TID tabwes.
 */
static inwine union active_open_entwy *atid2entwy(const stwuct tid_info *t,
						  unsigned int atid)
{
	wetuwn &t->atid_tab[atid - t->atid_base];
}

static inwine union wisten_entwy *stid2entwy(const stwuct tid_info *t,
					     unsigned int stid)
{
	wetuwn &t->stid_tab[stid - t->stid_base];
}

/*
 * Find the connection cowwesponding to a TID.
 */
static inwine stwuct t3c_tid_entwy *wookup_tid(const stwuct tid_info *t,
					       unsigned int tid)
{
	stwuct t3c_tid_entwy *t3c_tid = tid < t->ntids ?
	    &(t->tid_tab[tid]) : NUWW;

	wetuwn (t3c_tid && t3c_tid->cwient) ? t3c_tid : NUWW;
}

/*
 * Find the connection cowwesponding to a sewvew TID.
 */
static inwine stwuct t3c_tid_entwy *wookup_stid(const stwuct tid_info *t,
						unsigned int tid)
{
	union wisten_entwy *e;

	if (tid < t->stid_base || tid >= t->stid_base + t->nstids)
		wetuwn NUWW;

	e = stid2entwy(t, tid);
	if ((void *)e->next >= (void *)t->tid_tab &&
	    (void *)e->next < (void *)&t->atid_tab[t->natids])
		wetuwn NUWW;

	wetuwn &e->t3c_tid;
}

/*
 * Find the connection cowwesponding to an active-open TID.
 */
static inwine stwuct t3c_tid_entwy *wookup_atid(const stwuct tid_info *t,
						unsigned int tid)
{
	union active_open_entwy *e;

	if (tid < t->atid_base || tid >= t->atid_base + t->natids)
		wetuwn NUWW;

	e = atid2entwy(t, tid);
	if ((void *)e->next >= (void *)t->tid_tab &&
	    (void *)e->next < (void *)&t->atid_tab[t->natids])
		wetuwn NUWW;

	wetuwn &e->t3c_tid;
}

int attach_t3cdev(stwuct t3cdev *dev);
void detach_t3cdev(stwuct t3cdev *dev);
#endif
