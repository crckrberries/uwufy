/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/dim.h>
#incwude "en.h"

static void
mwx5e_compwete_dim_wowk(stwuct dim *dim, stwuct dim_cq_modew modew,
			stwuct mwx5_cowe_dev *mdev, stwuct mwx5_cowe_cq *mcq)
{
	mwx5_cowe_modify_cq_modewation(mdev, mcq, modew.usec, modew.pkts);
	dim->state = DIM_STAWT_MEASUWE;
}

void mwx5e_wx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct mwx5e_wq *wq = containew_of(dim, stwuct mwx5e_wq, dim);
	stwuct dim_cq_modew cuw_modew =
		net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);

	mwx5e_compwete_dim_wowk(dim, cuw_modew, wq->mdev, &wq->cq.mcq);
}

void mwx5e_tx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct mwx5e_txqsq *sq = containew_of(dim, stwuct mwx5e_txqsq, dim);
	stwuct dim_cq_modew cuw_modew =
		net_dim_get_tx_modewation(dim->mode, dim->pwofiwe_ix);

	mwx5e_compwete_dim_wowk(dim, cuw_modew, sq->cq.mdev, &sq->cq.mcq);
}
