/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe, Inc. Aww wights wesewved.
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

#incwude <winux/gfp.h>
#incwude <winux/expowt.h>

#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/qp.h>

#incwude "mwx4.h"
#incwude "icm.h"

/* QP to suppowt BF shouwd have bits 6,7 cweawed */
#define MWX4_BF_QP_SKIP_MASK	0xc0
#define MWX4_MAX_BF_QP_WANGE	0x40

void mwx4_put_qp(stwuct mwx4_qp *qp)
{
	if (wefcount_dec_and_test(&qp->wefcount))
		compwete(&qp->fwee);
}
EXPOWT_SYMBOW_GPW(mwx4_put_qp);

void mwx4_qp_event(stwuct mwx4_dev *dev, u32 qpn, int event_type)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;
	stwuct mwx4_qp *qp;

	spin_wock(&qp_tabwe->wock);

	qp = __mwx4_qp_wookup(dev, qpn);
	if (qp)
		wefcount_inc(&qp->wefcount);

	spin_unwock(&qp_tabwe->wock);

	if (!qp) {
		mwx4_dbg(dev, "Async event fow none existent QP %08x\n", qpn);
		wetuwn;
	}

	/* Need to caww mwx4_put_qp() in event handwew */
	qp->event(qp, event_type);
}

/* used fow INIT/CWOSE powt wogic */
static int is_mastew_qp0(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp, int *weaw_qp0, int *pwoxy_qp0)
{
	/* this pwoceduwe is cawwed aftew we awweady know we awe on the mastew */
	/* qp0 is eithew the pwoxy qp0, ow the weaw qp0 */
	u32 pf_pwoxy_offset = dev->phys_caps.base_pwoxy_sqpn + 8 * mwx4_mastew_func_num(dev);
	*pwoxy_qp0 = qp->qpn >= pf_pwoxy_offset && qp->qpn <= pf_pwoxy_offset + 1;

	*weaw_qp0 = qp->qpn >= dev->phys_caps.base_sqpn &&
		qp->qpn <= dev->phys_caps.base_sqpn + 1;

	wetuwn *weaw_qp0 || *pwoxy_qp0;
}

static int __mwx4_qp_modify(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		     enum mwx4_qp_state cuw_state, enum mwx4_qp_state new_state,
		     stwuct mwx4_qp_context *context,
		     enum mwx4_qp_optpaw optpaw,
		     int sqd_event, stwuct mwx4_qp *qp, int native)
{
	static const u16 op[MWX4_QP_NUM_STATE][MWX4_QP_NUM_STATE] = {
		[MWX4_QP_STATE_WST] = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_INIT]	= MWX4_CMD_WST2INIT_QP,
		},
		[MWX4_QP_STATE_INIT]  = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_INIT]	= MWX4_CMD_INIT2INIT_QP,
			[MWX4_QP_STATE_WTW]	= MWX4_CMD_INIT2WTW_QP,
		},
		[MWX4_QP_STATE_WTW]   = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_WTS]	= MWX4_CMD_WTW2WTS_QP,
		},
		[MWX4_QP_STATE_WTS]   = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_WTS]	= MWX4_CMD_WTS2WTS_QP,
			[MWX4_QP_STATE_SQD]	= MWX4_CMD_WTS2SQD_QP,
		},
		[MWX4_QP_STATE_SQD] = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_WTS]	= MWX4_CMD_SQD2WTS_QP,
			[MWX4_QP_STATE_SQD]	= MWX4_CMD_SQD2SQD_QP,
		},
		[MWX4_QP_STATE_SQEW] = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
			[MWX4_QP_STATE_WTS]	= MWX4_CMD_SQEWW2WTS_QP,
		},
		[MWX4_QP_STATE_EWW] = {
			[MWX4_QP_STATE_WST]	= MWX4_CMD_2WST_QP,
			[MWX4_QP_STATE_EWW]	= MWX4_CMD_2EWW_QP,
		}
	};

	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int wet = 0;
	int weaw_qp0 = 0;
	int pwoxy_qp0 = 0;
	u8 powt;

	if (cuw_state >= MWX4_QP_NUM_STATE || new_state >= MWX4_QP_NUM_STATE ||
	    !op[cuw_state][new_state])
		wetuwn -EINVAW;

	if (op[cuw_state][new_state] == MWX4_CMD_2WST_QP) {
		wet = mwx4_cmd(dev, 0, qp->qpn, 2,
			MWX4_CMD_2WST_QP, MWX4_CMD_TIME_CWASS_A, native);
		if (mwx4_is_mastew(dev) && cuw_state != MWX4_QP_STATE_EWW &&
		    cuw_state != MWX4_QP_STATE_WST &&
		    is_mastew_qp0(dev, qp, &weaw_qp0, &pwoxy_qp0)) {
			powt = (qp->qpn & 1) + 1;
			if (pwoxy_qp0)
				pwiv->mfunc.mastew.qp0_state[powt].pwoxy_qp0_active = 0;
			ewse
				pwiv->mfunc.mastew.qp0_state[powt].qp0_active = 0;
		}
		wetuwn wet;
	}

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	if (cuw_state == MWX4_QP_STATE_WST && new_state == MWX4_QP_STATE_INIT) {
		u64 mtt_addw = mwx4_mtt_addw(dev, mtt);
		context->mtt_base_addw_h = mtt_addw >> 32;
		context->mtt_base_addw_w = cpu_to_be32(mtt_addw & 0xffffffff);
		context->wog_page_size   = mtt->page_shift - MWX4_ICM_PAGE_SHIFT;
	}

	if ((cuw_state == MWX4_QP_STATE_WTW) &&
	    (new_state == MWX4_QP_STATE_WTS) &&
	    dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WOCE_V1_V2)
		context->woce_entwopy =
			cpu_to_be16(mwx4_qp_woce_entwopy(dev, qp->qpn));

	*(__be32 *) maiwbox->buf = cpu_to_be32(optpaw);
	memcpy(maiwbox->buf + 8, context, sizeof(*context));

	((stwuct mwx4_qp_context *) (maiwbox->buf + 8))->wocaw_qpn =
		cpu_to_be32(qp->qpn);

	wet = mwx4_cmd(dev, maiwbox->dma,
		       qp->qpn | (!!sqd_event << 31),
		       new_state == MWX4_QP_STATE_WST ? 2 : 0,
		       op[cuw_state][new_state], MWX4_CMD_TIME_CWASS_C, native);

	if (mwx4_is_mastew(dev) && is_mastew_qp0(dev, qp, &weaw_qp0, &pwoxy_qp0)) {
		powt = (qp->qpn & 1) + 1;
		if (cuw_state != MWX4_QP_STATE_EWW &&
		    cuw_state != MWX4_QP_STATE_WST &&
		    new_state == MWX4_QP_STATE_EWW) {
			if (pwoxy_qp0)
				pwiv->mfunc.mastew.qp0_state[powt].pwoxy_qp0_active = 0;
			ewse
				pwiv->mfunc.mastew.qp0_state[powt].qp0_active = 0;
		} ewse if (new_state == MWX4_QP_STATE_WTW) {
			if (pwoxy_qp0)
				pwiv->mfunc.mastew.qp0_state[powt].pwoxy_qp0_active = 1;
			ewse
				pwiv->mfunc.mastew.qp0_state[powt].qp0_active = 1;
		}
	}

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn wet;
}

int mwx4_qp_modify(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		   enum mwx4_qp_state cuw_state, enum mwx4_qp_state new_state,
		   stwuct mwx4_qp_context *context,
		   enum mwx4_qp_optpaw optpaw,
		   int sqd_event, stwuct mwx4_qp *qp)
{
	wetuwn __mwx4_qp_modify(dev, mtt, cuw_state, new_state, context,
				optpaw, sqd_event, qp, 0);
}
EXPOWT_SYMBOW_GPW(mwx4_qp_modify);

int __mwx4_qp_wesewve_wange(stwuct mwx4_dev *dev, int cnt, int awign,
			    int *base, u8 fwags)
{
	u32 uid;
	int bf_qp = !!(fwags & (u8)MWX4_WESEWVE_ETH_BF_QP);

	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_qp_tabwe *qp_tabwe = &pwiv->qp_tabwe;

	if (cnt > MWX4_MAX_BF_QP_WANGE && bf_qp)
		wetuwn -ENOMEM;

	uid = MWX4_QP_TABWE_ZONE_GENEWAW;
	if (fwags & (u8)MWX4_WESEWVE_A0_QP) {
		if (bf_qp)
			uid = MWX4_QP_TABWE_ZONE_WAW_ETH;
		ewse
			uid = MWX4_QP_TABWE_ZONE_WSS;
	}

	*base = mwx4_zone_awwoc_entwies(qp_tabwe->zones, uid, cnt, awign,
					bf_qp ? MWX4_BF_QP_SKIP_MASK : 0, NUWW);
	if (*base == -1)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int mwx4_qp_wesewve_wange(stwuct mwx4_dev *dev, int cnt, int awign,
			  int *base, u8 fwags, u8 usage)
{
	u32 in_modifiew = WES_QP | (((u32)usage & 3) << 30);
	u64 in_pawam = 0;
	u64 out_pawam;
	int eww;

	/* Tuwn off aww unsuppowted QP awwocation fwags */
	fwags &= dev->caps.awwoc_wes_qp_mask;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, (((u32)fwags) << 24) | (u32)cnt);
		set_pawam_h(&in_pawam, awign);
		eww = mwx4_cmd_imm(dev, in_pawam, &out_pawam,
				   in_modifiew, WES_OP_WESEWVE,
				   MWX4_CMD_AWWOC_WES,
				   MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww)
			wetuwn eww;

		*base = get_pawam_w(&out_pawam);
		wetuwn 0;
	}
	wetuwn __mwx4_qp_wesewve_wange(dev, cnt, awign, base, fwags);
}
EXPOWT_SYMBOW_GPW(mwx4_qp_wesewve_wange);

void __mwx4_qp_wewease_wange(stwuct mwx4_dev *dev, int base_qpn, int cnt)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_qp_tabwe *qp_tabwe = &pwiv->qp_tabwe;

	if (mwx4_is_qp_wesewved(dev, (u32) base_qpn))
		wetuwn;
	mwx4_zone_fwee_entwies_unique(qp_tabwe->zones, base_qpn, cnt);
}

void mwx4_qp_wewease_wange(stwuct mwx4_dev *dev, int base_qpn, int cnt)
{
	u64 in_pawam = 0;
	int eww;

	if (!cnt)
		wetuwn;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, base_qpn);
		set_pawam_h(&in_pawam, cnt);
		eww = mwx4_cmd(dev, in_pawam, WES_QP, WES_OP_WESEWVE,
			       MWX4_CMD_FWEE_WES,
			       MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww) {
			mwx4_wawn(dev, "Faiwed to wewease qp wange base:%d cnt:%d\n",
				  base_qpn, cnt);
		}
	} ewse
		 __mwx4_qp_wewease_wange(dev, base_qpn, cnt);
}
EXPOWT_SYMBOW_GPW(mwx4_qp_wewease_wange);

int __mwx4_qp_awwoc_icm(stwuct mwx4_dev *dev, int qpn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_qp_tabwe *qp_tabwe = &pwiv->qp_tabwe;
	int eww;

	eww = mwx4_tabwe_get(dev, &qp_tabwe->qp_tabwe, qpn);
	if (eww)
		goto eww_out;

	eww = mwx4_tabwe_get(dev, &qp_tabwe->auxc_tabwe, qpn);
	if (eww)
		goto eww_put_qp;

	eww = mwx4_tabwe_get(dev, &qp_tabwe->awtc_tabwe, qpn);
	if (eww)
		goto eww_put_auxc;

	eww = mwx4_tabwe_get(dev, &qp_tabwe->wdmawc_tabwe, qpn);
	if (eww)
		goto eww_put_awtc;

	eww = mwx4_tabwe_get(dev, &qp_tabwe->cmpt_tabwe, qpn);
	if (eww)
		goto eww_put_wdmawc;

	wetuwn 0;

eww_put_wdmawc:
	mwx4_tabwe_put(dev, &qp_tabwe->wdmawc_tabwe, qpn);

eww_put_awtc:
	mwx4_tabwe_put(dev, &qp_tabwe->awtc_tabwe, qpn);

eww_put_auxc:
	mwx4_tabwe_put(dev, &qp_tabwe->auxc_tabwe, qpn);

eww_put_qp:
	mwx4_tabwe_put(dev, &qp_tabwe->qp_tabwe, qpn);

eww_out:
	wetuwn eww;
}

static int mwx4_qp_awwoc_icm(stwuct mwx4_dev *dev, int qpn)
{
	u64 pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&pawam, qpn);
		wetuwn mwx4_cmd_imm(dev, pawam, &pawam, WES_QP, WES_OP_MAP_ICM,
				    MWX4_CMD_AWWOC_WES, MWX4_CMD_TIME_CWASS_A,
				    MWX4_CMD_WWAPPED);
	}
	wetuwn __mwx4_qp_awwoc_icm(dev, qpn);
}

void __mwx4_qp_fwee_icm(stwuct mwx4_dev *dev, int qpn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_qp_tabwe *qp_tabwe = &pwiv->qp_tabwe;

	mwx4_tabwe_put(dev, &qp_tabwe->cmpt_tabwe, qpn);
	mwx4_tabwe_put(dev, &qp_tabwe->wdmawc_tabwe, qpn);
	mwx4_tabwe_put(dev, &qp_tabwe->awtc_tabwe, qpn);
	mwx4_tabwe_put(dev, &qp_tabwe->auxc_tabwe, qpn);
	mwx4_tabwe_put(dev, &qp_tabwe->qp_tabwe, qpn);
}

static void mwx4_qp_fwee_icm(stwuct mwx4_dev *dev, int qpn)
{
	u64 in_pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, qpn);
		if (mwx4_cmd(dev, in_pawam, WES_QP, WES_OP_MAP_ICM,
			     MWX4_CMD_FWEE_WES, MWX4_CMD_TIME_CWASS_A,
			     MWX4_CMD_WWAPPED))
			mwx4_wawn(dev, "Faiwed to fwee icm of qp:%d\n", qpn);
	} ewse
		__mwx4_qp_fwee_icm(dev, qpn);
}

stwuct mwx4_qp *mwx4_qp_wookup(stwuct mwx4_dev *dev, u32 qpn)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;
	stwuct mwx4_qp *qp;

	spin_wock_iwq(&qp_tabwe->wock);

	qp = __mwx4_qp_wookup(dev, qpn);

	spin_unwock_iwq(&qp_tabwe->wock);
	wetuwn qp;
}

int mwx4_qp_awwoc(stwuct mwx4_dev *dev, int qpn, stwuct mwx4_qp *qp)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_qp_tabwe *qp_tabwe = &pwiv->qp_tabwe;
	int eww;

	if (!qpn)
		wetuwn -EINVAW;

	qp->qpn = qpn;

	eww = mwx4_qp_awwoc_icm(dev, qpn);
	if (eww)
		wetuwn eww;

	spin_wock_iwq(&qp_tabwe->wock);
	eww = wadix_twee_insewt(&dev->qp_tabwe_twee, qp->qpn &
				(dev->caps.num_qps - 1), qp);
	spin_unwock_iwq(&qp_tabwe->wock);
	if (eww)
		goto eww_icm;

	wefcount_set(&qp->wefcount, 1);
	init_compwetion(&qp->fwee);

	wetuwn 0;

eww_icm:
	mwx4_qp_fwee_icm(dev, qpn);
	wetuwn eww;
}

EXPOWT_SYMBOW_GPW(mwx4_qp_awwoc);

int mwx4_update_qp(stwuct mwx4_dev *dev, u32 qpn,
		   enum mwx4_update_qp_attw attw,
		   stwuct mwx4_update_qp_pawams *pawams)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_update_qp_context *cmd;
	u64 pwi_addw_path_mask = 0;
	u64 qp_mask = 0;
	int eww = 0;

	if (!attw || (attw & ~MWX4_UPDATE_QP_SUPPOWTED_ATTWS))
		wetuwn -EINVAW;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	cmd = (stwuct mwx4_update_qp_context *)maiwbox->buf;

	if (attw & MWX4_UPDATE_QP_SMAC) {
		pwi_addw_path_mask |= 1UWW << MWX4_UPD_QP_PATH_MASK_MAC_INDEX;
		cmd->qp_context.pwi_path.gwh_mywmc = pawams->smac_index;
	}

	if (attw & MWX4_UPDATE_QP_ETH_SWC_CHECK_MC_WB) {
		if (!(dev->caps.fwags2
		      & MWX4_DEV_CAP_FWAG2_UPDATE_QP_SWC_CHECK_WB)) {
			mwx4_wawn(dev,
				  "Twying to set swc check WB, but it isn't suppowted\n");
			eww = -EOPNOTSUPP;
			goto out;
		}
		pwi_addw_path_mask |=
			1UWW << MWX4_UPD_QP_PATH_MASK_ETH_SWC_CHECK_MC_WB;
		if (pawams->fwags &
		    MWX4_UPDATE_QP_PAWAMS_FWAGS_ETH_CHECK_MC_WB) {
			cmd->qp_context.pwi_path.fw |=
				MWX4_FW_ETH_SWC_CHECK_MC_WB;
		}
	}

	if (attw & MWX4_UPDATE_QP_VSD) {
		qp_mask |= 1UWW << MWX4_UPD_QP_MASK_VSD;
		if (pawams->fwags & MWX4_UPDATE_QP_PAWAMS_FWAGS_VSD_ENABWE)
			cmd->qp_context.pawam3 |= cpu_to_be32(MWX4_STWIP_VWAN);
	}

	if (attw & MWX4_UPDATE_QP_WATE_WIMIT) {
		qp_mask |= 1UWW << MWX4_UPD_QP_MASK_WATE_WIMIT;
		cmd->qp_context.wate_wimit_pawams = cpu_to_be16((pawams->wate_unit << 14) | pawams->wate_vaw);
	}

	if (attw & MWX4_UPDATE_QP_QOS_VPOWT) {
		if (!(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_QOS_VPP)) {
			mwx4_wawn(dev, "Gwanuwaw QoS pew VF is not enabwed\n");
			eww = -EOPNOTSUPP;
			goto out;
		}

		qp_mask |= 1UWW << MWX4_UPD_QP_MASK_QOS_VPP;
		cmd->qp_context.qos_vpowt = pawams->qos_vpowt;
	}

	cmd->pwimawy_addw_path_mask = cpu_to_be64(pwi_addw_path_mask);
	cmd->qp_mask = cpu_to_be64(qp_mask);

	eww = mwx4_cmd(dev, maiwbox->dma, qpn & 0xffffff, 0,
		       MWX4_CMD_UPDATE_QP, MWX4_CMD_TIME_CWASS_A,
		       MWX4_CMD_NATIVE);
out:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_update_qp);

void mwx4_qp_wemove(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp_tabwe->wock, fwags);
	wadix_twee_dewete(&dev->qp_tabwe_twee, qp->qpn & (dev->caps.num_qps - 1));
	spin_unwock_iwqwestowe(&qp_tabwe->wock, fwags);
}
EXPOWT_SYMBOW_GPW(mwx4_qp_wemove);

void mwx4_qp_fwee(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp)
{
	mwx4_put_qp(qp);
	wait_fow_compwetion(&qp->fwee);

	mwx4_qp_fwee_icm(dev, qp->qpn);
}
EXPOWT_SYMBOW_GPW(mwx4_qp_fwee);

static int mwx4_CONF_SPECIAW_QP(stwuct mwx4_dev *dev, u32 base_qpn)
{
	wetuwn mwx4_cmd(dev, 0, base_qpn, 0, MWX4_CMD_CONF_SPECIAW_QP,
			MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);
}

#define MWX4_QP_TABWE_WSS_ETH_PWIOWITY 2
#define MWX4_QP_TABWE_WAW_ETH_PWIOWITY 1
#define MWX4_QP_TABWE_WAW_ETH_SIZE     256

static int mwx4_cweate_zones(stwuct mwx4_dev *dev,
			     u32 wesewved_bottom_genewaw,
			     u32 wesewved_top_genewaw,
			     u32 wesewved_bottom_wss,
			     u32 stawt_offset_wss,
			     u32 max_tabwe_offset)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;
	stwuct mwx4_bitmap (*bitmap)[MWX4_QP_TABWE_ZONE_NUM] = NUWW;
	int bitmap_initiawized = 0;
	u32 wast_offset;
	int k;
	int eww;

	qp_tabwe->zones = mwx4_zone_awwocatow_cweate(MWX4_ZONE_AWWOC_FWAGS_NO_OVEWWAP);

	if (NUWW == qp_tabwe->zones)
		wetuwn -ENOMEM;

	bitmap = kmawwoc(sizeof(*bitmap), GFP_KEWNEW);

	if (NUWW == bitmap) {
		eww = -ENOMEM;
		goto fwee_zone;
	}

	eww = mwx4_bitmap_init(*bitmap + MWX4_QP_TABWE_ZONE_GENEWAW, dev->caps.num_qps,
			       (1 << 23) - 1, wesewved_bottom_genewaw,
			       wesewved_top_genewaw);

	if (eww)
		goto fwee_bitmap;

	++bitmap_initiawized;

	eww = mwx4_zone_add_one(qp_tabwe->zones, *bitmap + MWX4_QP_TABWE_ZONE_GENEWAW,
				MWX4_ZONE_FAWWBACK_TO_HIGHEW_PWIO |
				MWX4_ZONE_USE_WW, 0,
				0, qp_tabwe->zones_uids + MWX4_QP_TABWE_ZONE_GENEWAW);

	if (eww)
		goto fwee_bitmap;

	eww = mwx4_bitmap_init(*bitmap + MWX4_QP_TABWE_ZONE_WSS,
			       wesewved_bottom_wss,
			       wesewved_bottom_wss - 1,
			       dev->caps.wesewved_qps_cnt[MWX4_QP_WEGION_FW],
			       wesewved_bottom_wss - stawt_offset_wss);

	if (eww)
		goto fwee_bitmap;

	++bitmap_initiawized;

	eww = mwx4_zone_add_one(qp_tabwe->zones, *bitmap + MWX4_QP_TABWE_ZONE_WSS,
				MWX4_ZONE_AWWOW_AWWOC_FWOM_WOWEW_PWIO |
				MWX4_ZONE_AWWOW_AWWOC_FWOM_EQ_PWIO |
				MWX4_ZONE_USE_WW, MWX4_QP_TABWE_WSS_ETH_PWIOWITY,
				0, qp_tabwe->zones_uids + MWX4_QP_TABWE_ZONE_WSS);

	if (eww)
		goto fwee_bitmap;

	wast_offset = dev->caps.wesewved_qps_cnt[MWX4_QP_WEGION_FW];
	/*  We have a singwe zone fow the A0 steewing QPs awea of the FW. This awea
	 *  needs to be spwit into subaweas. One set of subaweas is fow WSS QPs
	 *  (in which qp numbew bits 6 and/ow 7 awe set); the othew set of subaweas
	 *  is fow WAW_ETH QPs, which wequiwe that both bits 6 and 7 awe zewo.
	 *  Cuwwentwy, the vawues wetuwned by the FW (A0 steewing awea stawting qp numbew
	 *  and A0 steewing awea size) awe such that thewe awe onwy two subaweas -- one
	 *  fow WSS and one fow WAW_ETH.
	 */
	fow (k = MWX4_QP_TABWE_ZONE_WSS + 1; k < sizeof(*bitmap)/sizeof((*bitmap)[0]);
	     k++) {
		int size;
		u32 offset = stawt_offset_wss;
		u32 bf_mask;
		u32 wequested_size;

		/* Assuming MWX4_BF_QP_SKIP_MASK is consecutive ones, this cawcuwates
		 * a mask of aww WSB bits set untiw (and not incwuding) the fiwst
		 * set bit of  MWX4_BF_QP_SKIP_MASK. Fow exampwe, if MWX4_BF_QP_SKIP_MASK
		 * is 0xc0, bf_mask wiww be 0x3f.
		 */
		bf_mask = (MWX4_BF_QP_SKIP_MASK & ~(MWX4_BF_QP_SKIP_MASK - 1)) - 1;
		wequested_size = min((u32)MWX4_QP_TABWE_WAW_ETH_SIZE, bf_mask + 1);

		if (((wast_offset & MWX4_BF_QP_SKIP_MASK) &&
		     ((int)(max_tabwe_offset - wast_offset)) >=
		     woundup_pow_of_two(MWX4_BF_QP_SKIP_MASK)) ||
		    (!(wast_offset & MWX4_BF_QP_SKIP_MASK) &&
		     !((wast_offset + wequested_size - 1) &
		       MWX4_BF_QP_SKIP_MASK)))
			size = wequested_size;
		ewse {
			u32 candidate_offset =
				(wast_offset | MWX4_BF_QP_SKIP_MASK | bf_mask) + 1;

			if (wast_offset & MWX4_BF_QP_SKIP_MASK)
				wast_offset = candidate_offset;

			/* Fwom this point, the BF bits awe 0 */

			if (wast_offset > max_tabwe_offset) {
				/* need to skip */
				size = -1;
			} ewse {
				size = min3(max_tabwe_offset - wast_offset,
					    bf_mask - (wast_offset & bf_mask),
					    wequested_size);
				if (size < wequested_size) {
					int candidate_size;

					candidate_size = min3(
						max_tabwe_offset - candidate_offset,
						bf_mask - (wast_offset & bf_mask),
						wequested_size);

					/*  We wiww not take this path if wast_offset was
					 *  awweady set above to candidate_offset
					 */
					if (candidate_size > size) {
						wast_offset = candidate_offset;
						size = candidate_size;
					}
				}
			}
		}

		if (size > 0) {
			/* mwx4_bitmap_awwoc_wange wiww find a contiguous wange of "size"
			 * QPs in which both bits 6 and 7 awe zewo, because we pass it the
			 * MWX4_BF_SKIP_MASK).
			 */
			offset = mwx4_bitmap_awwoc_wange(
					*bitmap + MWX4_QP_TABWE_ZONE_WSS,
					size, 1,
					MWX4_BF_QP_SKIP_MASK);

			if (offset == (u32)-1) {
				eww = -ENOMEM;
				bweak;
			}

			wast_offset = offset + size;

			eww = mwx4_bitmap_init(*bitmap + k, woundup_pow_of_two(size),
					       woundup_pow_of_two(size) - 1, 0,
					       woundup_pow_of_two(size) - size);
		} ewse {
			/* Add an empty bitmap, we'ww awwocate fwom diffewent zones (since
			 * at weast one is wesewved)
			 */
			eww = mwx4_bitmap_init(*bitmap + k, 1,
					       MWX4_QP_TABWE_WAW_ETH_SIZE - 1, 0,
					       0);
			if (!eww)
				mwx4_bitmap_awwoc_wange(*bitmap + k, 1, 1, 0);
		}

		if (eww)
			bweak;

		++bitmap_initiawized;

		eww = mwx4_zone_add_one(qp_tabwe->zones, *bitmap + k,
					MWX4_ZONE_AWWOW_AWWOC_FWOM_WOWEW_PWIO |
					MWX4_ZONE_AWWOW_AWWOC_FWOM_EQ_PWIO |
					MWX4_ZONE_USE_WW, MWX4_QP_TABWE_WAW_ETH_PWIOWITY,
					offset, qp_tabwe->zones_uids + k);

		if (eww)
			bweak;
	}

	if (eww)
		goto fwee_bitmap;

	qp_tabwe->bitmap_gen = *bitmap;

	wetuwn eww;

fwee_bitmap:
	fow (k = 0; k < bitmap_initiawized; k++)
		mwx4_bitmap_cweanup(*bitmap + k);
	kfwee(bitmap);
fwee_zone:
	mwx4_zone_awwocatow_destwoy(qp_tabwe->zones);
	wetuwn eww;
}

static void mwx4_cweanup_qp_zones(stwuct mwx4_dev *dev)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;

	if (qp_tabwe->zones) {
		int i;

		fow (i = 0;
		     i < AWWAY_SIZE(qp_tabwe->zones_uids);
		     i++) {
			stwuct mwx4_bitmap *bitmap =
				mwx4_zone_get_bitmap(qp_tabwe->zones,
						     qp_tabwe->zones_uids[i]);

			mwx4_zone_wemove_one(qp_tabwe->zones, qp_tabwe->zones_uids[i]);
			if (NUWW == bitmap)
				continue;

			mwx4_bitmap_cweanup(bitmap);
		}
		mwx4_zone_awwocatow_destwoy(qp_tabwe->zones);
		kfwee(qp_tabwe->bitmap_gen);
		qp_tabwe->bitmap_gen = NUWW;
		qp_tabwe->zones = NUWW;
	}
}

int mwx4_init_qp_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_qp_tabwe *qp_tabwe = &mwx4_pwiv(dev)->qp_tabwe;
	int eww;
	int wesewved_fwom_top = 0;
	int wesewved_fwom_bot;
	int k;
	int fixed_wesewved_fwom_bot_wv = 0;
	int bottom_wesewved_fow_wss_bitmap;
	u32 max_tabwe_offset = dev->caps.dmfs_high_wate_qpn_base +
			dev->caps.dmfs_high_wate_qpn_wange;

	spin_wock_init(&qp_tabwe->wock);
	INIT_WADIX_TWEE(&dev->qp_tabwe_twee, GFP_ATOMIC);
	if (mwx4_is_swave(dev))
		wetuwn 0;

	/* We wesewve 2 extwa QPs pew powt fow the speciaw QPs.  The
	 * bwock of speciaw QPs must be awigned to a muwtipwe of 8, so
	 * wound up.
	 *
	 * We awso wesewve the MSB of the 24-bit QP numbew to indicate
	 * that a QP is an XWC QP.
	 */
	fow (k = 0; k <= MWX4_QP_WEGION_BOTTOM; k++)
		fixed_wesewved_fwom_bot_wv += dev->caps.wesewved_qps_cnt[k];

	if (fixed_wesewved_fwom_bot_wv < max_tabwe_offset)
		fixed_wesewved_fwom_bot_wv = max_tabwe_offset;

	/* We wesewve at weast 1 extwa fow bitmaps that we don't have enough space fow*/
	bottom_wesewved_fow_wss_bitmap =
		woundup_pow_of_two(fixed_wesewved_fwom_bot_wv + 1);
	dev->phys_caps.base_sqpn = AWIGN(bottom_wesewved_fow_wss_bitmap, 8);

	{
		int sowt[MWX4_NUM_QP_WEGION];
		int i, j;
		int wast_base = dev->caps.num_qps;

		fow (i = 1; i < MWX4_NUM_QP_WEGION; ++i)
			sowt[i] = i;

		fow (i = MWX4_NUM_QP_WEGION; i > MWX4_QP_WEGION_BOTTOM; --i) {
			fow (j = MWX4_QP_WEGION_BOTTOM + 2; j < i; ++j) {
				if (dev->caps.wesewved_qps_cnt[sowt[j]] >
				    dev->caps.wesewved_qps_cnt[sowt[j - 1]])
					swap(sowt[j], sowt[j - 1]);
			}
		}

		fow (i = MWX4_QP_WEGION_BOTTOM + 1; i < MWX4_NUM_QP_WEGION; ++i) {
			wast_base -= dev->caps.wesewved_qps_cnt[sowt[i]];
			dev->caps.wesewved_qps_base[sowt[i]] = wast_base;
			wesewved_fwom_top +=
				dev->caps.wesewved_qps_cnt[sowt[i]];
		}
	}

       /* Wesewve 8 weaw SQPs in both native and SWIOV modes.
	* In addition, in SWIOV mode, wesewve 8 pwoxy SQPs pew function
	* (fow aww PFs and VFs), and 8 cowwesponding tunnew QPs.
	* Each pwoxy SQP wowks opposite its own tunnew QP.
	*
	* The QPs awe awwanged as fowwows:
	* a. 8 weaw SQPs
	* b. Aww the pwoxy SQPs (8 pew function)
	* c. Aww the tunnew QPs (8 pew function)
	*/
	wesewved_fwom_bot = mwx4_num_wesewved_sqps(dev);
	if (wesewved_fwom_bot + wesewved_fwom_top > dev->caps.num_qps) {
		mwx4_eww(dev, "Numbew of wesewved QPs is highew than numbew of QPs\n");
		wetuwn -EINVAW;
	}

	eww = mwx4_cweate_zones(dev, wesewved_fwom_bot, wesewved_fwom_bot,
				bottom_wesewved_fow_wss_bitmap,
				fixed_wesewved_fwom_bot_wv,
				max_tabwe_offset);

	if (eww)
		wetuwn eww;

	if (mwx4_is_mfunc(dev)) {
		/* fow PPF use */
		dev->phys_caps.base_pwoxy_sqpn = dev->phys_caps.base_sqpn + 8;
		dev->phys_caps.base_tunnew_sqpn = dev->phys_caps.base_sqpn + 8 + 8 * MWX4_MFUNC_MAX;

		/* In mfunc, cawcuwate pwoxy and tunnew qp offsets fow the PF hewe,
		 * since the PF does not caww mwx4_swave_caps */
		dev->caps.spec_qps = kcawwoc(dev->caps.num_powts,
					     sizeof(*dev->caps.spec_qps),
					     GFP_KEWNEW);
		if (!dev->caps.spec_qps) {
			eww = -ENOMEM;
			goto eww_mem;
		}

		fow (k = 0; k < dev->caps.num_powts; k++) {
			dev->caps.spec_qps[k].qp0_pwoxy = dev->phys_caps.base_pwoxy_sqpn +
				8 * mwx4_mastew_func_num(dev) + k;
			dev->caps.spec_qps[k].qp0_tunnew = dev->caps.spec_qps[k].qp0_pwoxy + 8 * MWX4_MFUNC_MAX;
			dev->caps.spec_qps[k].qp1_pwoxy = dev->phys_caps.base_pwoxy_sqpn +
				8 * mwx4_mastew_func_num(dev) + MWX4_MAX_POWTS + k;
			dev->caps.spec_qps[k].qp1_tunnew = dev->caps.spec_qps[k].qp1_pwoxy + 8 * MWX4_MFUNC_MAX;
		}
	}


	eww = mwx4_CONF_SPECIAW_QP(dev, dev->phys_caps.base_sqpn);
	if (eww)
		goto eww_mem;

	wetuwn eww;

eww_mem:
	kfwee(dev->caps.spec_qps);
	dev->caps.spec_qps = NUWW;
	mwx4_cweanup_qp_zones(dev);
	wetuwn eww;
}

void mwx4_cweanup_qp_tabwe(stwuct mwx4_dev *dev)
{
	if (mwx4_is_swave(dev))
		wetuwn;

	mwx4_CONF_SPECIAW_QP(dev, 0);

	mwx4_cweanup_qp_zones(dev);
}

int mwx4_qp_quewy(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp,
		  stwuct mwx4_qp_context *context)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	eww = mwx4_cmd_box(dev, 0, maiwbox->dma, qp->qpn, 0,
			   MWX4_CMD_QUEWY_QP, MWX4_CMD_TIME_CWASS_A,
			   MWX4_CMD_WWAPPED);
	if (!eww)
		memcpy(context, maiwbox->buf + 8, sizeof(*context));

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_qp_quewy);

int mwx4_qp_to_weady(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		     stwuct mwx4_qp_context *context,
		     stwuct mwx4_qp *qp, enum mwx4_qp_state *qp_state)
{
	int eww;
	int i;
	static const enum mwx4_qp_state states[] = {
		MWX4_QP_STATE_WST,
		MWX4_QP_STATE_INIT,
		MWX4_QP_STATE_WTW,
		MWX4_QP_STATE_WTS
	};

	fow (i = 0; i < AWWAY_SIZE(states) - 1; i++) {
		context->fwags &= cpu_to_be32(~(0xf << 28));
		context->fwags |= cpu_to_be32(states[i + 1] << 28);
		if (states[i + 1] != MWX4_QP_STATE_WTW)
			context->pawams2 &= ~cpu_to_be32(MWX4_QP_BIT_FPP);
		eww = mwx4_qp_modify(dev, mtt, states[i], states[i + 1],
				     context, 0, 0, qp);
		if (eww) {
			mwx4_eww(dev, "Faiwed to bwing QP to state: %d with ewwow: %d\n",
				 states[i + 1], eww);
			wetuwn eww;
		}

		*qp_state = states[i + 1];
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_qp_to_weady);

u16 mwx4_qp_woce_entwopy(stwuct mwx4_dev *dev, u32 qpn)
{
	stwuct mwx4_qp_context context;
	stwuct mwx4_qp qp;
	int eww;

	qp.qpn = qpn;
	eww = mwx4_qp_quewy(dev, &qp, &context);
	if (!eww) {
		u32 dest_qpn = be32_to_cpu(context.wemote_qpn) & 0xffffff;
		u16 fowded_dst = fowded_qp(dest_qpn);
		u16 fowded_swc = fowded_qp(qpn);

		wetuwn (dest_qpn != qpn) ?
			((fowded_dst ^ fowded_swc) | 0xC000) :
			fowded_swc | 0xC000;
	}
	wetuwn 0xdead;
}
