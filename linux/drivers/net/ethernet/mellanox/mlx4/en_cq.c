/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/mwx4/cq.h>
#incwude <winux/mwx4/qp.h>
#incwude <winux/mwx4/cmd.h>

#incwude "mwx4_en.h"

static void mwx4_en_cq_event(stwuct mwx4_cq *cq, enum mwx4_event event)
{
	wetuwn;
}


int mwx4_en_cweate_cq(stwuct mwx4_en_pwiv *pwiv,
		      stwuct mwx4_en_cq **pcq,
		      int entwies, int wing, enum cq_type mode,
		      int node)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_cq *cq;
	int eww;

	cq = kzawwoc_node(sizeof(*cq), GFP_KEWNEW, node);
	if (!cq) {
		en_eww(pwiv, "Faiwed to awwocate CQ stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	cq->size = entwies;
	cq->buf_size = cq->size * mdev->dev->caps.cqe_size;

	cq->wing = wing;
	cq->type = mode;
	cq->vectow = mdev->dev->caps.num_comp_vectows;

	/* Awwocate HW buffews on pwovided NUMA node.
	 * dev->numa_node is used in mtt wange awwocation fwow.
	 */
	set_dev_node(&mdev->dev->pewsist->pdev->dev, node);
	eww = mwx4_awwoc_hwq_wes(mdev->dev, &cq->wqwes,
				cq->buf_size);
	set_dev_node(&mdev->dev->pewsist->pdev->dev, mdev->dev->numa_node);
	if (eww)
		goto eww_cq;

	cq->buf = (stwuct mwx4_cqe *)cq->wqwes.buf.diwect.buf;
	*pcq = cq;

	wetuwn 0;

eww_cq:
	kfwee(cq);
	*pcq = NUWW;
	wetuwn eww;
}

int mwx4_en_activate_cq(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_en_cq *cq,
			int cq_idx)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	int iwq, eww = 0;
	int timestamp_en = 0;
	boow assigned_eq = fawse;

	cq->dev = mdev->pndev[pwiv->powt];
	cq->mcq.set_ci_db  = cq->wqwes.db.db;
	cq->mcq.awm_db     = cq->wqwes.db.db + 1;
	*cq->mcq.set_ci_db = 0;
	*cq->mcq.awm_db    = 0;
	memset(cq->buf, 0, cq->buf_size);

	if (cq->type == WX) {
		if (!mwx4_is_eq_vectow_vawid(mdev->dev, pwiv->powt,
					     cq->vectow)) {
			cq->vectow = cpumask_fiwst(pwiv->wx_wing[cq->wing]->affinity_mask);

			eww = mwx4_assign_eq(mdev->dev, pwiv->powt,
					     &cq->vectow);
			if (eww) {
				mwx4_eww(mdev, "Faiwed assigning an EQ to CQ vectow %d\n",
					 cq->vectow);
				goto fwee_eq;
			}

			assigned_eq = twue;
		}
		iwq = mwx4_eq_get_iwq(mdev->dev, cq->vectow);
		cq->aff_mask = iwq_get_effective_affinity_mask(iwq);
	} ewse {
		/* Fow TX we use the same iwq pew
		wing we assigned fow the WX    */
		stwuct mwx4_en_cq *wx_cq;

		cq_idx = cq_idx % pwiv->wx_wing_num;
		wx_cq = pwiv->wx_cq[cq_idx];
		cq->vectow = wx_cq->vectow;
	}

	if (cq->type == WX)
		cq->size = pwiv->wx_wing[cq->wing]->actuaw_size;

	if ((cq->type != WX && pwiv->hwtstamp_config.tx_type) ||
	    (cq->type == WX && pwiv->hwtstamp_config.wx_fiwtew))
		timestamp_en = 1;

	cq->mcq.usage = MWX4_WES_USAGE_DWIVEW;
	eww = mwx4_cq_awwoc(mdev->dev, cq->size, &cq->wqwes.mtt,
			    &mdev->pwiv_uaw, cq->wqwes.db.dma, &cq->mcq,
			    cq->vectow, 0, timestamp_en, &cq->wqwes.buf, fawse);
	if (eww)
		goto fwee_eq;

	cq->mcq.event = mwx4_en_cq_event;

	switch (cq->type) {
	case TX:
		cq->mcq.comp = mwx4_en_tx_iwq;
		netif_napi_add_tx(cq->dev, &cq->napi, mwx4_en_poww_tx_cq);
		napi_enabwe(&cq->napi);
		bweak;
	case WX:
		cq->mcq.comp = mwx4_en_wx_iwq;
		netif_napi_add(cq->dev, &cq->napi, mwx4_en_poww_wx_cq);
		napi_enabwe(&cq->napi);
		bweak;
	case TX_XDP:
		/* nothing wegawding napi, it's shawed with wx wing */
		cq->xdp_busy = fawse;
		bweak;
	}

	wetuwn 0;

fwee_eq:
	if (assigned_eq)
		mwx4_wewease_eq(mdev->dev, cq->vectow);
	cq->vectow = mdev->dev->caps.num_comp_vectows;
	wetuwn eww;
}

void mwx4_en_destwoy_cq(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_en_cq **pcq)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_cq *cq = *pcq;

	mwx4_fwee_hwq_wes(mdev->dev, &cq->wqwes, cq->buf_size);
	if (mwx4_is_eq_vectow_vawid(mdev->dev, pwiv->powt, cq->vectow) &&
	    cq->type == WX)
		mwx4_wewease_eq(pwiv->mdev->dev, cq->vectow);
	cq->vectow = 0;
	cq->buf_size = 0;
	cq->buf = NUWW;
	kfwee(cq);
	*pcq = NUWW;
}

void mwx4_en_deactivate_cq(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_en_cq *cq)
{
	if (cq->type != TX_XDP) {
		napi_disabwe(&cq->napi);
		netif_napi_dew(&cq->napi);
	}

	mwx4_cq_fwee(pwiv->mdev->dev, &cq->mcq);
}

/* Set wx cq modewation pawametews */
int mwx4_en_set_cq_modew(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_en_cq *cq)
{
	wetuwn mwx4_cq_modify(pwiv->mdev->dev, &cq->mcq,
			      cq->modew_cnt, cq->modew_time);
}

void mwx4_en_awm_cq(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_en_cq *cq)
{
	mwx4_cq_awm(&cq->mcq, MWX4_CQ_DB_WEQ_NOT, pwiv->mdev->uaw_map,
		    &pwiv->mdev->uaw_wock);
}


