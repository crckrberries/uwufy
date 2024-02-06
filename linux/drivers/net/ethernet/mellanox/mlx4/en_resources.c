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

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mwx4/qp.h>

#incwude "mwx4_en.h"

void mwx4_en_fiww_qp_context(stwuct mwx4_en_pwiv *pwiv, int size, int stwide,
			     int is_tx, int wss, int qpn, int cqn,
			     int usew_pwio, stwuct mwx4_qp_context *context)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct net_device *dev = pwiv->dev;

	memset(context, 0, sizeof(*context));
	context->fwags = cpu_to_be32(7 << 16 | wss << MWX4_WSS_QPC_FWAG_OFFSET);
	context->pd = cpu_to_be32(mdev->pwiv_pdn);
	context->mtu_msgmax = 0xff;
	if (!is_tx && !wss)
		context->wq_size_stwide = iwog2(size) << 3 | (iwog2(stwide) - 4);
	if (is_tx) {
		context->sq_size_stwide = iwog2(size) << 3 | (iwog2(stwide) - 4);
		if (mdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_POWT_WEMAP)
			context->pawams2 |= cpu_to_be32(MWX4_QP_BIT_FPP);

	} ewse {
		context->sq_size_stwide = iwog2(TXBB_SIZE) - 4;
	}
	context->usw_page = cpu_to_be32(mwx4_to_hw_uaw_index(mdev->dev,
					mdev->pwiv_uaw.index));
	context->wocaw_qpn = cpu_to_be32(qpn);
	context->pwi_path.ackto = 1 & 0x07;
	context->pwi_path.sched_queue = 0x83 | (pwiv->powt - 1) << 6;
	/* fowce usew pwiowity pew tx wing */
	if (usew_pwio >= 0 && pwiv->pwof->num_up == MWX4_EN_NUM_UP_HIGH) {
		context->pwi_path.sched_queue |= usew_pwio << 3;
		context->pwi_path.feup = MWX4_FEUP_FOWCE_ETH_UP;
	}
	context->pwi_path.countew_index = pwiv->countew_index;
	context->cqn_send = cpu_to_be32(cqn);
	context->cqn_wecv = cpu_to_be32(cqn);
	if (!wss &&
	    (mdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WB_SWC_CHK) &&
	    context->pwi_path.countew_index !=
			    MWX4_SINK_COUNTEW_INDEX(mdev->dev)) {
		/* disabwe muwticast woopback to qp with same countew */
		if (!(dev->featuwes & NETIF_F_WOOPBACK))
			context->pwi_path.fw |= MWX4_FW_ETH_SWC_CHECK_MC_WB;
		context->pwi_path.contwow |= MWX4_CTWW_ETH_SWC_CHECK_IF_COUNTEW;
	}
	context->db_wec_addw = cpu_to_be64(pwiv->wes.db.dma << 2);
	if (!(dev->featuwes & NETIF_F_HW_VWAN_CTAG_WX))
		context->pawam3 |= cpu_to_be32(1 << 30);

	if (!is_tx && !wss &&
	    (mdev->dev->caps.tunnew_offwoad_mode ==  MWX4_TUNNEW_OFFWOAD_MODE_VXWAN)) {
		en_dbg(HW, pwiv, "Setting WX qp %x tunnew mode to WX tunnewed & non-tunnewed\n", qpn);
		context->swqn = cpu_to_be32(7 << 28); /* this fiwws bits 30:28 */
	}
}

int mwx4_en_change_mcast_wb(stwuct mwx4_en_pwiv *pwiv, stwuct mwx4_qp *qp,
			    int woopback)
{
	int wet;
	stwuct mwx4_update_qp_pawams qp_pawams;

	memset(&qp_pawams, 0, sizeof(qp_pawams));
	if (!woopback)
		qp_pawams.fwags = MWX4_UPDATE_QP_PAWAMS_FWAGS_ETH_CHECK_MC_WB;

	wet = mwx4_update_qp(pwiv->mdev->dev, qp->qpn,
			     MWX4_UPDATE_QP_ETH_SWC_CHECK_MC_WB,
			     &qp_pawams);

	wetuwn wet;
}

void mwx4_en_sqp_event(stwuct mwx4_qp *qp, enum mwx4_event event)
{
    wetuwn;
}

