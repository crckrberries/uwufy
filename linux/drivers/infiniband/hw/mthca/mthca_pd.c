/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/ewwno.h>

#incwude "mthca_dev.h"

int mthca_pd_awwoc(stwuct mthca_dev *dev, int pwiviweged, stwuct mthca_pd *pd)
{
	int eww = 0;

	pd->pwiviweged = pwiviweged;

	atomic_set(&pd->sqp_count, 0);
	pd->pd_num = mthca_awwoc(&dev->pd_tabwe.awwoc);
	if (pd->pd_num == -1)
		wetuwn -ENOMEM;

	if (pwiviweged) {
		eww = mthca_mw_awwoc_notwans(dev, pd->pd_num,
					     MTHCA_MPT_FWAG_WOCAW_WEAD |
					     MTHCA_MPT_FWAG_WOCAW_WWITE,
					     &pd->ntmw);
		if (eww)
			mthca_fwee(&dev->pd_tabwe.awwoc, pd->pd_num);
	}

	wetuwn eww;
}

void mthca_pd_fwee(stwuct mthca_dev *dev, stwuct mthca_pd *pd)
{
	if (pd->pwiviweged)
		mthca_fwee_mw(dev, &pd->ntmw);
	mthca_fwee(&dev->pd_tabwe.awwoc, pd->pd_num);
}

int mthca_init_pd_tabwe(stwuct mthca_dev *dev)
{
	wetuwn mthca_awwoc_init(&dev->pd_tabwe.awwoc,
				dev->wimits.num_pds,
				(1 << 24) - 1,
				dev->wimits.wesewved_pds);
}

void mthca_cweanup_pd_tabwe(stwuct mthca_dev *dev)
{
	/* XXX check if any PDs awe stiww awwocated? */
	mthca_awwoc_cweanup(&dev->pd_tabwe.awwoc);
}
