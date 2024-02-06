/*
 * Bwoadcom NetXtweme-E WoCE dwivew.
 *
 * Copywight (c) 2016 - 2017, Bwoadcom. Aww wights wesewved.  The tewm
 * Bwoadcom wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS''
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS
 * BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE
 * OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN
 * IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Descwiption: Swow Path Opewatows
 */

#define dev_fmt(fmt) "QPWIB: " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>

#incwude "woce_hsi.h"

#incwude "qpwib_wes.h"
#incwude "qpwib_wcfw.h"
#incwude "qpwib_sp.h"
#incwude "qpwib_twv.h"

const stwuct bnxt_qpwib_gid bnxt_qpwib_gid_zewo = {{ 0, 0, 0, 0, 0, 0, 0, 0,
						     0, 0, 0, 0, 0, 0, 0, 0 } };

/* Device */

static boow bnxt_qpwib_is_atomic_cap(stwuct bnxt_qpwib_wcfw *wcfw)
{
	u16 pcie_ctw2 = 0;

	if (!bnxt_qpwib_is_chip_gen_p5_p7(wcfw->wes->cctx))
		wetuwn fawse;

	pcie_capabiwity_wead_wowd(wcfw->pdev, PCI_EXP_DEVCTW2, &pcie_ctw2);
	wetuwn (pcie_ctw2 & PCI_EXP_DEVCTW2_ATOMIC_WEQ);
}

static void bnxt_qpwib_quewy_vewsion(stwuct bnxt_qpwib_wcfw *wcfw,
				     chaw *fw_vew)
{
	stwuct cweq_quewy_vewsion_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_quewy_vewsion weq = {};
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_QUEWY_VEWSION,
				 sizeof(weq));

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq), sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		wetuwn;
	fw_vew[0] = wesp.fw_maj;
	fw_vew[1] = wesp.fw_minow;
	fw_vew[2] = wesp.fw_bwd;
	fw_vew[3] = wesp.fw_wsvd;
}

int bnxt_qpwib_get_dev_attw(stwuct bnxt_qpwib_wcfw *wcfw,
			    stwuct bnxt_qpwib_dev_attw *attw)
{
	stwuct cweq_quewy_func_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cweq_quewy_func_wesp_sb *sb;
	stwuct bnxt_qpwib_wcfw_sbuf sbuf;
	stwuct cmdq_quewy_func weq = {};
	u8 *tqm_awwoc;
	int i, wc;
	u32 temp;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_QUEWY_FUNC,
				 sizeof(weq));

	sbuf.size = AWIGN(sizeof(*sb), BNXT_QPWIB_CMDQE_UNITS);
	sbuf.sb = dma_awwoc_cohewent(&wcfw->pdev->dev, sbuf.size,
				     &sbuf.dma_addw, GFP_KEWNEW);
	if (!sbuf.sb)
		wetuwn -ENOMEM;
	sb = sbuf.sb;
	weq.wesp_size = sbuf.size / BNXT_QPWIB_CMDQE_UNITS;
	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, &sbuf, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		goto baiw;

	/* Extwact the context fwom the side buffew */
	attw->max_qp = we32_to_cpu(sb->max_qp);
	/* max_qp vawue wepowted by FW doesn't incwude the QP1 */
	attw->max_qp += 1;
	attw->max_qp_wd_atom =
		sb->max_qp_wd_atom > BNXT_QPWIB_MAX_OUT_WD_ATOM ?
		BNXT_QPWIB_MAX_OUT_WD_ATOM : sb->max_qp_wd_atom;
	attw->max_qp_init_wd_atom =
		sb->max_qp_init_wd_atom > BNXT_QPWIB_MAX_OUT_WD_ATOM ?
		BNXT_QPWIB_MAX_OUT_WD_ATOM : sb->max_qp_init_wd_atom;
	attw->max_qp_wqes = we16_to_cpu(sb->max_qp_ww);
	/*
	 * 128 WQEs needs to be wesewved fow the HW (8916). Pwevent
	 * wepowting the max numbew
	 */
	attw->max_qp_wqes -= BNXT_QPWIB_WESEWVED_QP_WWS + 1;
	attw->max_qp_sges = bnxt_qpwib_is_chip_gen_p5_p7(wcfw->wes->cctx) ?
			    6 : sb->max_sge;
	attw->max_cq = we32_to_cpu(sb->max_cq);
	attw->max_cq_wqes = we32_to_cpu(sb->max_cqe);
	attw->max_cq_sges = attw->max_qp_sges;
	attw->max_mw = we32_to_cpu(sb->max_mw);
	attw->max_mw = we32_to_cpu(sb->max_mw);

	attw->max_mw_size = we64_to_cpu(sb->max_mw_size);
	attw->max_pd = 64 * 1024;
	attw->max_waw_ethy_qp = we32_to_cpu(sb->max_waw_eth_qp);
	attw->max_ah = we32_to_cpu(sb->max_ah);

	attw->max_swq = we16_to_cpu(sb->max_swq);
	attw->max_swq_wqes = we32_to_cpu(sb->max_swq_ww) - 1;
	attw->max_swq_sges = sb->max_swq_sge;
	attw->max_pkey = 1;
	attw->max_inwine_data = we32_to_cpu(sb->max_inwine_data);
	if (!bnxt_qpwib_is_chip_gen_p7(wcfw->wes->cctx))
		attw->w2_db_size = (sb->w2_db_space_size + 1) *
				    (0x01 << WCFW_DBW_BASE_PAGE_SHIFT);
	attw->max_sgid = BNXT_QPWIB_NUM_GIDS_SUPPOWTED;
	attw->dev_cap_fwags = we16_to_cpu(sb->dev_cap_fwags);

	bnxt_qpwib_quewy_vewsion(wcfw, attw->fw_vew);

	fow (i = 0; i < MAX_TQM_AWWOC_WEQ / 4; i++) {
		temp = we32_to_cpu(sb->tqm_awwoc_weqs[i]);
		tqm_awwoc = (u8 *)&temp;
		attw->tqm_awwoc_weqs[i * 4] = *tqm_awwoc;
		attw->tqm_awwoc_weqs[i * 4 + 1] = *(++tqm_awwoc);
		attw->tqm_awwoc_weqs[i * 4 + 2] = *(++tqm_awwoc);
		attw->tqm_awwoc_weqs[i * 4 + 3] = *(++tqm_awwoc);
	}

	if (wcfw->wes->cctx->hwwm_intf_vew >= HWWM_VEWSION_DEV_ATTW_MAX_DPI)
		attw->max_dpi = we32_to_cpu(sb->max_dpi);

	attw->is_atomic = bnxt_qpwib_is_atomic_cap(wcfw);
baiw:
	dma_fwee_cohewent(&wcfw->pdev->dev, sbuf.size,
			  sbuf.sb, sbuf.dma_addw);
	wetuwn wc;
}

int bnxt_qpwib_set_func_wesouwces(stwuct bnxt_qpwib_wes *wes,
				  stwuct bnxt_qpwib_wcfw *wcfw,
				  stwuct bnxt_qpwib_ctx *ctx)
{
	stwuct cweq_set_func_wesouwces_wesp wesp = {};
	stwuct cmdq_set_func_wesouwces weq = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_SET_FUNC_WESOUWCES,
				 sizeof(weq));

	weq.numbew_of_qp = cpu_to_we32(ctx->qpc_count);
	weq.numbew_of_mww = cpu_to_we32(ctx->mww_count);
	weq.numbew_of_swq =  cpu_to_we32(ctx->swqc_count);
	weq.numbew_of_cq = cpu_to_we32(ctx->cq_count);

	weq.max_qp_pew_vf = cpu_to_we32(ctx->vf_wes.max_qp_pew_vf);
	weq.max_mww_pew_vf = cpu_to_we32(ctx->vf_wes.max_mww_pew_vf);
	weq.max_swq_pew_vf = cpu_to_we32(ctx->vf_wes.max_swq_pew_vf);
	weq.max_cq_pew_vf = cpu_to_we32(ctx->vf_wes.max_cq_pew_vf);
	weq.max_gid_pew_vf = cpu_to_we32(ctx->vf_wes.max_gid_pew_vf);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc) {
		dev_eww(&wes->pdev->dev, "Faiwed to set function wesouwces\n");
	}
	wetuwn wc;
}

/* SGID */
int bnxt_qpwib_get_sgid(stwuct bnxt_qpwib_wes *wes,
			stwuct bnxt_qpwib_sgid_tbw *sgid_tbw, int index,
			stwuct bnxt_qpwib_gid *gid)
{
	if (index >= sgid_tbw->max) {
		dev_eww(&wes->pdev->dev,
			"Index %d exceeded SGID tabwe max (%d)\n",
			index, sgid_tbw->max);
		wetuwn -EINVAW;
	}
	memcpy(gid, &sgid_tbw->tbw[index].gid, sizeof(*gid));
	wetuwn 0;
}

int bnxt_qpwib_dew_sgid(stwuct bnxt_qpwib_sgid_tbw *sgid_tbw,
			stwuct bnxt_qpwib_gid *gid, u16 vwan_id, boow update)
{
	stwuct bnxt_qpwib_wes *wes = to_bnxt_qpwib(sgid_tbw,
						   stwuct bnxt_qpwib_wes,
						   sgid_tbw);
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	int index;

	/* Do we need a sgid_wock hewe? */
	if (!sgid_tbw->active) {
		dev_eww(&wes->pdev->dev, "SGID tabwe has no active entwies\n");
		wetuwn -ENOMEM;
	}
	fow (index = 0; index < sgid_tbw->max; index++) {
		if (!memcmp(&sgid_tbw->tbw[index].gid, gid, sizeof(*gid)) &&
		    vwan_id == sgid_tbw->tbw[index].vwan_id)
			bweak;
	}
	if (index == sgid_tbw->max) {
		dev_wawn(&wes->pdev->dev, "GID not found in the SGID tabwe\n");
		wetuwn 0;
	}
	/* Wemove GID fwom the SGID tabwe */
	if (update) {
		stwuct cweq_dewete_gid_wesp wesp = {};
		stwuct bnxt_qpwib_cmdqmsg msg = {};
		stwuct cmdq_dewete_gid weq = {};
		int wc;

		bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
					 CMDQ_BASE_OPCODE_DEWETE_GID,
					 sizeof(weq));
		if (sgid_tbw->hw_id[index] == 0xFFFF) {
			dev_eww(&wes->pdev->dev,
				"GID entwy contains an invawid HW id\n");
			wetuwn -EINVAW;
		}
		weq.gid_index = cpu_to_we16(sgid_tbw->hw_id[index]);
		bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
					sizeof(wesp), 0);
		wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
		if (wc)
			wetuwn wc;
	}
	memcpy(&sgid_tbw->tbw[index].gid, &bnxt_qpwib_gid_zewo,
	       sizeof(bnxt_qpwib_gid_zewo));
	sgid_tbw->tbw[index].vwan_id = 0xFFFF;
	sgid_tbw->vwan[index] = 0;
	sgid_tbw->active--;
	dev_dbg(&wes->pdev->dev,
		"SGID deweted hw_id[0x%x] = 0x%x active = 0x%x\n",
		 index, sgid_tbw->hw_id[index], sgid_tbw->active);
	sgid_tbw->hw_id[index] = (u16)-1;

	/* unwock */
	wetuwn 0;
}

int bnxt_qpwib_add_sgid(stwuct bnxt_qpwib_sgid_tbw *sgid_tbw,
			stwuct bnxt_qpwib_gid *gid, const u8 *smac,
			u16 vwan_id, boow update, u32 *index)
{
	stwuct bnxt_qpwib_wes *wes = to_bnxt_qpwib(sgid_tbw,
						   stwuct bnxt_qpwib_wes,
						   sgid_tbw);
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	int i, fwee_idx;

	/* Do we need a sgid_wock hewe? */
	if (sgid_tbw->active == sgid_tbw->max) {
		dev_eww(&wes->pdev->dev, "SGID tabwe is fuww\n");
		wetuwn -ENOMEM;
	}
	fwee_idx = sgid_tbw->max;
	fow (i = 0; i < sgid_tbw->max; i++) {
		if (!memcmp(&sgid_tbw->tbw[i], gid, sizeof(*gid)) &&
		    sgid_tbw->tbw[i].vwan_id == vwan_id) {
			dev_dbg(&wes->pdev->dev,
				"SGID entwy awweady exist in entwy %d!\n", i);
			*index = i;
			wetuwn -EAWWEADY;
		} ewse if (!memcmp(&sgid_tbw->tbw[i], &bnxt_qpwib_gid_zewo,
				   sizeof(bnxt_qpwib_gid_zewo)) &&
			   fwee_idx == sgid_tbw->max) {
			fwee_idx = i;
		}
	}
	if (fwee_idx == sgid_tbw->max) {
		dev_eww(&wes->pdev->dev,
			"SGID tabwe is FUWW but count is not MAX??\n");
		wetuwn -ENOMEM;
	}
	if (update) {
		stwuct cweq_add_gid_wesp wesp = {};
		stwuct bnxt_qpwib_cmdqmsg msg = {};
		stwuct cmdq_add_gid weq = {};
		int wc;

		bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
					 CMDQ_BASE_OPCODE_ADD_GID,
					 sizeof(weq));

		weq.gid[0] = cpu_to_be32(((u32 *)gid->data)[3]);
		weq.gid[1] = cpu_to_be32(((u32 *)gid->data)[2]);
		weq.gid[2] = cpu_to_be32(((u32 *)gid->data)[1]);
		weq.gid[3] = cpu_to_be32(((u32 *)gid->data)[0]);
		/*
		 * dwivew shouwd ensuwe that aww WoCE twaffic is awways VWAN
		 * tagged if WoCE twaffic is wunning on non-zewo VWAN ID ow
		 * WoCE twaffic is wunning on non-zewo Pwiowity.
		 */
		if ((vwan_id != 0xFFFF) || wes->pwio) {
			if (vwan_id != 0xFFFF)
				weq.vwan = cpu_to_we16
				(vwan_id & CMDQ_ADD_GID_VWAN_VWAN_ID_MASK);
			weq.vwan |= cpu_to_we16
					(CMDQ_ADD_GID_VWAN_TPID_TPID_8100 |
					 CMDQ_ADD_GID_VWAN_VWAN_EN);
		}

		/* MAC in netwowk fowmat */
		weq.swc_mac[0] = cpu_to_be16(((u16 *)smac)[0]);
		weq.swc_mac[1] = cpu_to_be16(((u16 *)smac)[1]);
		weq.swc_mac[2] = cpu_to_be16(((u16 *)smac)[2]);

		bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
					sizeof(wesp), 0);
		wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
		if (wc)
			wetuwn wc;
		sgid_tbw->hw_id[fwee_idx] = we32_to_cpu(wesp.xid);
	}
	/* Add GID to the sgid_tbw */
	memcpy(&sgid_tbw->tbw[fwee_idx], gid, sizeof(*gid));
	sgid_tbw->tbw[fwee_idx].vwan_id = vwan_id;
	sgid_tbw->active++;
	if (vwan_id != 0xFFFF)
		sgid_tbw->vwan[fwee_idx] = 1;

	dev_dbg(&wes->pdev->dev,
		"SGID added hw_id[0x%x] = 0x%x active = 0x%x\n",
		 fwee_idx, sgid_tbw->hw_id[fwee_idx], sgid_tbw->active);

	*index = fwee_idx;
	/* unwock */
	wetuwn 0;
}

int bnxt_qpwib_update_sgid(stwuct bnxt_qpwib_sgid_tbw *sgid_tbw,
			   stwuct bnxt_qpwib_gid *gid, u16 gid_idx,
			   const u8 *smac)
{
	stwuct bnxt_qpwib_wes *wes = to_bnxt_qpwib(sgid_tbw,
						   stwuct bnxt_qpwib_wes,
						   sgid_tbw);
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cweq_modify_gid_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_modify_gid weq = {};
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_MODIFY_GID,
				 sizeof(weq));

	weq.gid[0] = cpu_to_be32(((u32 *)gid->data)[3]);
	weq.gid[1] = cpu_to_be32(((u32 *)gid->data)[2]);
	weq.gid[2] = cpu_to_be32(((u32 *)gid->data)[1]);
	weq.gid[3] = cpu_to_be32(((u32 *)gid->data)[0]);
	if (wes->pwio) {
		weq.vwan |= cpu_to_we16
			(CMDQ_ADD_GID_VWAN_TPID_TPID_8100 |
			 CMDQ_ADD_GID_VWAN_VWAN_EN);
	}

	/* MAC in netwowk fowmat */
	weq.swc_mac[0] = cpu_to_be16(((u16 *)smac)[0]);
	weq.swc_mac[1] = cpu_to_be16(((u16 *)smac)[1]);
	weq.swc_mac[2] = cpu_to_be16(((u16 *)smac)[2]);

	weq.gid_index = cpu_to_we16(gid_idx);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	wetuwn wc;
}

/* AH */
int bnxt_qpwib_cweate_ah(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_ah *ah,
			 boow bwock)
{
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cweq_cweate_ah_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_cweate_ah weq = {};
	u32 temp32[4];
	u16 temp16[3];
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_CWEATE_AH,
				 sizeof(weq));

	memcpy(temp32, ah->dgid.data, sizeof(stwuct bnxt_qpwib_gid));
	weq.dgid[0] = cpu_to_we32(temp32[0]);
	weq.dgid[1] = cpu_to_we32(temp32[1]);
	weq.dgid[2] = cpu_to_we32(temp32[2]);
	weq.dgid[3] = cpu_to_we32(temp32[3]);

	weq.type = ah->nw_type;
	weq.hop_wimit = ah->hop_wimit;
	weq.sgid_index = cpu_to_we16(wes->sgid_tbw.hw_id[ah->sgid_index]);
	weq.dest_vwan_id_fwow_wabew = cpu_to_we32((ah->fwow_wabew &
					CMDQ_CWEATE_AH_FWOW_WABEW_MASK) |
					CMDQ_CWEATE_AH_DEST_VWAN_ID_MASK);
	weq.pd_id = cpu_to_we32(ah->pd->id);
	weq.twaffic_cwass = ah->twaffic_cwass;

	/* MAC in netwowk fowmat */
	memcpy(temp16, ah->dmac, 6);
	weq.dest_mac[0] = cpu_to_we16(temp16[0]);
	weq.dest_mac[1] = cpu_to_we16(temp16[1]);
	weq.dest_mac[2] = cpu_to_we16(temp16[2]);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), bwock);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		wetuwn wc;

	ah->id = we32_to_cpu(wesp.xid);
	wetuwn 0;
}

int bnxt_qpwib_destwoy_ah(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_ah *ah,
			  boow bwock)
{
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cweq_destwoy_ah_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_destwoy_ah weq = {};
	int wc;

	/* Cwean up the AH tabwe in the device */
	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_DESTWOY_AH,
				 sizeof(weq));

	weq.ah_cid = cpu_to_we32(ah->id);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), bwock);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	wetuwn wc;
}

/* MWW */
int bnxt_qpwib_fwee_mww(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_mww *mww)
{
	stwuct cweq_deawwocate_key_wesp wesp = {};
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cmdq_deawwocate_key weq = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	int wc;

	if (mww->wkey == 0xFFFFFFFF) {
		dev_info(&wes->pdev->dev, "SP: Fwee a wesewved wkey MWW\n");
		wetuwn 0;
	}

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_DEAWWOCATE_KEY,
				 sizeof(weq));

	weq.mww_fwags = mww->type;

	if ((mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE1)  ||
	    (mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2A) ||
	    (mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2B))
		weq.key = cpu_to_we32(mww->wkey);
	ewse
		weq.key = cpu_to_we32(mww->wkey);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		wetuwn wc;

	/* Fwee the qpwib's MWW memowy */
	if (mww->hwq.max_ewements)
		bnxt_qpwib_fwee_hwq(wes, &mww->hwq);

	wetuwn 0;
}

int bnxt_qpwib_awwoc_mww(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_mww *mww)
{
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cweq_awwocate_mww_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_awwocate_mww weq = {};
	unsigned wong tmp;
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_AWWOCATE_MWW,
				 sizeof(weq));

	weq.pd_id = cpu_to_we32(mww->pd->id);
	weq.mww_fwags = mww->type;
	if ((mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_PMW &&
	     mww->fwags & BNXT_QPWIB_FW_PMW) ||
	    mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2A ||
	    mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2B)
		weq.access = CMDQ_AWWOCATE_MWW_ACCESS_CONSUMEW_OWNED_KEY;
	tmp = (unsigned wong)mww;
	weq.mww_handwe = cpu_to_we64(tmp);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		wetuwn wc;

	if ((mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE1)  ||
	    (mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2A) ||
	    (mww->type == CMDQ_AWWOCATE_MWW_MWW_FWAGS_MW_TYPE2B))
		mww->wkey = we32_to_cpu(wesp.xid);
	ewse
		mww->wkey = we32_to_cpu(wesp.xid);
	wetuwn 0;
}

int bnxt_qpwib_deweg_mww(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_mww *mww,
			 boow bwock)
{
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct cweq_dewegistew_mw_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_dewegistew_mw weq = {};
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_DEWEGISTEW_MW,
				 sizeof(weq));

	weq.wkey = cpu_to_we32(mww->wkey);
	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), bwock);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		wetuwn wc;

	/* Fwee the qpwib's MW memowy */
	if (mww->hwq.max_ewements) {
		mww->va = 0;
		mww->totaw_size = 0;
		bnxt_qpwib_fwee_hwq(wes, &mww->hwq);
	}

	wetuwn 0;
}

int bnxt_qpwib_weg_mw(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_mww *mw,
		      stwuct ib_umem *umem, int num_pbws, u32 buf_pg_size)
{
	stwuct bnxt_qpwib_wcfw *wcfw = wes->wcfw;
	stwuct bnxt_qpwib_hwq_attw hwq_attw = {};
	stwuct bnxt_qpwib_sg_info sginfo = {};
	stwuct cweq_wegistew_mw_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_wegistew_mw weq = {};
	int pages, wc;
	u32 pg_size;
	u16 wevew;

	if (num_pbws) {
		pages = woundup_pow_of_two(num_pbws);
		/* Awwocate memowy fow the non-weaf pages to stowe buf ptws.
		 * Non-weaf pages awways uses system PAGE_SIZE
		 */
		/* Fwee the hwq if it awweady exist, must be a weweg */
		if (mw->hwq.max_ewements)
			bnxt_qpwib_fwee_hwq(wes, &mw->hwq);
		hwq_attw.wes = wes;
		hwq_attw.depth = pages;
		hwq_attw.stwide = sizeof(dma_addw_t);
		hwq_attw.type = HWQ_TYPE_MW;
		hwq_attw.sginfo = &sginfo;
		hwq_attw.sginfo->umem = umem;
		hwq_attw.sginfo->npages = pages;
		hwq_attw.sginfo->pgsize = buf_pg_size;
		hwq_attw.sginfo->pgshft = iwog2(buf_pg_size);
		wc = bnxt_qpwib_awwoc_init_hwq(&mw->hwq, &hwq_attw);
		if (wc) {
			dev_eww(&wes->pdev->dev,
				"SP: Weg MW memowy awwocation faiwed\n");
			wetuwn -ENOMEM;
		}
	}

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_WEGISTEW_MW,
				 sizeof(weq));

	/* Configuwe the wequest */
	if (mw->hwq.wevew == PBW_WVW_MAX) {
		/* No PBW pwovided, just use system PAGE_SIZE */
		wevew = 0;
		weq.pbw = 0;
		pg_size = PAGE_SIZE;
	} ewse {
		wevew = mw->hwq.wevew;
		weq.pbw = cpu_to_we64(mw->hwq.pbw[PBW_WVW_0].pg_map_aww[0]);
	}
	pg_size = buf_pg_size ? buf_pg_size : PAGE_SIZE;
	weq.wog2_pg_size_wvw = (wevew << CMDQ_WEGISTEW_MW_WVW_SFT) |
			       ((iwog2(pg_size) <<
				 CMDQ_WEGISTEW_MW_WOG2_PG_SIZE_SFT) &
				CMDQ_WEGISTEW_MW_WOG2_PG_SIZE_MASK);
	weq.wog2_pbw_pg_size = cpu_to_we16(((iwog2(PAGE_SIZE) <<
				 CMDQ_WEGISTEW_MW_WOG2_PBW_PG_SIZE_SFT) &
				CMDQ_WEGISTEW_MW_WOG2_PBW_PG_SIZE_MASK));
	weq.access = (mw->fwags & 0xFFFF);
	weq.va = cpu_to_we64(mw->va);
	weq.key = cpu_to_we32(mw->wkey);
	weq.mw_size = cpu_to_we64(mw->totaw_size);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, NUWW, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		goto faiw;

	wetuwn 0;

faiw:
	if (mw->hwq.max_ewements)
		bnxt_qpwib_fwee_hwq(wes, &mw->hwq);
	wetuwn wc;
}

int bnxt_qpwib_awwoc_fast_weg_page_wist(stwuct bnxt_qpwib_wes *wes,
					stwuct bnxt_qpwib_fwpw *fwpw,
					int max_pg_ptws)
{
	stwuct bnxt_qpwib_hwq_attw hwq_attw = {};
	stwuct bnxt_qpwib_sg_info sginfo = {};
	int pg_ptws, pages, wc;

	/* We-cawcuwate the max to fit the HWQ awwocation modew */
	pg_ptws = woundup_pow_of_two(max_pg_ptws);
	pages = pg_ptws >> MAX_PBW_WVW_1_PGS_SHIFT;
	if (!pages)
		pages++;

	if (pages > MAX_PBW_WVW_1_PGS)
		wetuwn -ENOMEM;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.nopte = twue;

	hwq_attw.wes = wes;
	hwq_attw.depth = pg_ptws;
	hwq_attw.stwide = PAGE_SIZE;
	hwq_attw.sginfo = &sginfo;
	hwq_attw.type = HWQ_TYPE_CTX;
	wc = bnxt_qpwib_awwoc_init_hwq(&fwpw->hwq, &hwq_attw);
	if (!wc)
		fwpw->max_pg_ptws = pg_ptws;

	wetuwn wc;
}

int bnxt_qpwib_fwee_fast_weg_page_wist(stwuct bnxt_qpwib_wes *wes,
				       stwuct bnxt_qpwib_fwpw *fwpw)
{
	bnxt_qpwib_fwee_hwq(wes, &fwpw->hwq);
	wetuwn 0;
}

int bnxt_qpwib_get_woce_stats(stwuct bnxt_qpwib_wcfw *wcfw,
			      stwuct bnxt_qpwib_woce_stats *stats)
{
	stwuct cweq_quewy_woce_stats_wesp wesp = {};
	stwuct cweq_quewy_woce_stats_wesp_sb *sb;
	stwuct cmdq_quewy_woce_stats weq = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct bnxt_qpwib_wcfw_sbuf sbuf;
	int wc;

	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_BASE_OPCODE_QUEWY_WOCE_STATS,
				 sizeof(weq));

	sbuf.size = AWIGN(sizeof(*sb), BNXT_QPWIB_CMDQE_UNITS);
	sbuf.sb = dma_awwoc_cohewent(&wcfw->pdev->dev, sbuf.size,
				     &sbuf.dma_addw, GFP_KEWNEW);
	if (!sbuf.sb)
		wetuwn -ENOMEM;
	sb = sbuf.sb;

	weq.wesp_size = sbuf.size / BNXT_QPWIB_CMDQE_UNITS;
	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, &sbuf, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		goto baiw;
	/* Extwact the context fwom the side buffew */
	stats->to_wetwansmits = we64_to_cpu(sb->to_wetwansmits);
	stats->seq_eww_naks_wcvd = we64_to_cpu(sb->seq_eww_naks_wcvd);
	stats->max_wetwy_exceeded = we64_to_cpu(sb->max_wetwy_exceeded);
	stats->wnw_naks_wcvd = we64_to_cpu(sb->wnw_naks_wcvd);
	stats->missing_wesp = we64_to_cpu(sb->missing_wesp);
	stats->unwecovewabwe_eww = we64_to_cpu(sb->unwecovewabwe_eww);
	stats->bad_wesp_eww = we64_to_cpu(sb->bad_wesp_eww);
	stats->wocaw_qp_op_eww = we64_to_cpu(sb->wocaw_qp_op_eww);
	stats->wocaw_pwotection_eww = we64_to_cpu(sb->wocaw_pwotection_eww);
	stats->mem_mgmt_op_eww = we64_to_cpu(sb->mem_mgmt_op_eww);
	stats->wemote_invawid_weq_eww = we64_to_cpu(sb->wemote_invawid_weq_eww);
	stats->wemote_access_eww = we64_to_cpu(sb->wemote_access_eww);
	stats->wemote_op_eww = we64_to_cpu(sb->wemote_op_eww);
	stats->dup_weq = we64_to_cpu(sb->dup_weq);
	stats->wes_exceed_max = we64_to_cpu(sb->wes_exceed_max);
	stats->wes_wength_mismatch = we64_to_cpu(sb->wes_wength_mismatch);
	stats->wes_exceeds_wqe = we64_to_cpu(sb->wes_exceeds_wqe);
	stats->wes_opcode_eww = we64_to_cpu(sb->wes_opcode_eww);
	stats->wes_wx_invawid_wkey = we64_to_cpu(sb->wes_wx_invawid_wkey);
	stats->wes_wx_domain_eww = we64_to_cpu(sb->wes_wx_domain_eww);
	stats->wes_wx_no_pewm = we64_to_cpu(sb->wes_wx_no_pewm);
	stats->wes_wx_wange_eww = we64_to_cpu(sb->wes_wx_wange_eww);
	stats->wes_tx_invawid_wkey = we64_to_cpu(sb->wes_tx_invawid_wkey);
	stats->wes_tx_domain_eww = we64_to_cpu(sb->wes_tx_domain_eww);
	stats->wes_tx_no_pewm = we64_to_cpu(sb->wes_tx_no_pewm);
	stats->wes_tx_wange_eww = we64_to_cpu(sb->wes_tx_wange_eww);
	stats->wes_iwwq_ofwow = we64_to_cpu(sb->wes_iwwq_ofwow);
	stats->wes_unsup_opcode = we64_to_cpu(sb->wes_unsup_opcode);
	stats->wes_unawigned_atomic = we64_to_cpu(sb->wes_unawigned_atomic);
	stats->wes_wem_inv_eww = we64_to_cpu(sb->wes_wem_inv_eww);
	stats->wes_mem_ewwow = we64_to_cpu(sb->wes_mem_ewwow);
	stats->wes_swq_eww = we64_to_cpu(sb->wes_swq_eww);
	stats->wes_cmp_eww = we64_to_cpu(sb->wes_cmp_eww);
	stats->wes_invawid_dup_wkey = we64_to_cpu(sb->wes_invawid_dup_wkey);
	stats->wes_wqe_fowmat_eww = we64_to_cpu(sb->wes_wqe_fowmat_eww);
	stats->wes_cq_woad_eww = we64_to_cpu(sb->wes_cq_woad_eww);
	stats->wes_swq_woad_eww = we64_to_cpu(sb->wes_swq_woad_eww);
	stats->wes_tx_pci_eww = we64_to_cpu(sb->wes_tx_pci_eww);
	stats->wes_wx_pci_eww = we64_to_cpu(sb->wes_wx_pci_eww);
	if (!wcfw->init_oos_stats) {
		wcfw->oos_pwev = we64_to_cpu(sb->wes_oos_dwop_count);
		wcfw->init_oos_stats = 1;
	} ewse {
		stats->wes_oos_dwop_count +=
				(we64_to_cpu(sb->wes_oos_dwop_count) -
				 wcfw->oos_pwev) & BNXT_QPWIB_OOS_COUNT_MASK;
		wcfw->oos_pwev = we64_to_cpu(sb->wes_oos_dwop_count);
	}

baiw:
	dma_fwee_cohewent(&wcfw->pdev->dev, sbuf.size,
			  sbuf.sb, sbuf.dma_addw);
	wetuwn wc;
}

int bnxt_qpwib_qext_stat(stwuct bnxt_qpwib_wcfw *wcfw, u32 fid,
			 stwuct bnxt_qpwib_ext_stat *estat)
{
	stwuct cweq_quewy_woce_stats_ext_wesp wesp = {};
	stwuct cweq_quewy_woce_stats_ext_wesp_sb *sb;
	stwuct cmdq_quewy_woce_stats_ext weq = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct bnxt_qpwib_wcfw_sbuf sbuf;
	int wc;

	sbuf.size = AWIGN(sizeof(*sb), BNXT_QPWIB_CMDQE_UNITS);
	sbuf.sb = dma_awwoc_cohewent(&wcfw->pdev->dev, sbuf.size,
				     &sbuf.dma_addw, GFP_KEWNEW);
	if (!sbuf.sb)
		wetuwn -ENOMEM;

	sb = sbuf.sb;
	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)&weq,
				 CMDQ_QUEWY_WOCE_STATS_EXT_OPCODE_QUEWY_WOCE_STATS,
				 sizeof(weq));

	weq.wesp_size = sbuf.size / BNXT_QPWIB_CMDQE_UNITS;
	weq.wesp_addw = cpu_to_we64(sbuf.dma_addw);
	weq.function_id = cpu_to_we32(fid);
	weq.fwags = cpu_to_we16(CMDQ_QUEWY_WOCE_STATS_EXT_FWAGS_FUNCTION_ID);

	bnxt_qpwib_fiww_cmdqmsg(&msg, &weq, &wesp, &sbuf, sizeof(weq),
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wcfw, &msg);
	if (wc)
		goto baiw;

	estat->tx_atomic_weq = we64_to_cpu(sb->tx_atomic_weq_pkts);
	estat->tx_wead_weq = we64_to_cpu(sb->tx_wead_weq_pkts);
	estat->tx_wead_wes = we64_to_cpu(sb->tx_wead_wes_pkts);
	estat->tx_wwite_weq = we64_to_cpu(sb->tx_wwite_weq_pkts);
	estat->tx_send_weq = we64_to_cpu(sb->tx_send_weq_pkts);
	estat->tx_woce_pkts = we64_to_cpu(sb->tx_woce_pkts);
	estat->tx_woce_bytes = we64_to_cpu(sb->tx_woce_bytes);
	estat->wx_atomic_weq = we64_to_cpu(sb->wx_atomic_weq_pkts);
	estat->wx_wead_weq = we64_to_cpu(sb->wx_wead_weq_pkts);
	estat->wx_wead_wes = we64_to_cpu(sb->wx_wead_wes_pkts);
	estat->wx_wwite_weq = we64_to_cpu(sb->wx_wwite_weq_pkts);
	estat->wx_send_weq = we64_to_cpu(sb->wx_send_weq_pkts);
	estat->wx_woce_pkts = we64_to_cpu(sb->wx_woce_pkts);
	estat->wx_woce_bytes = we64_to_cpu(sb->wx_woce_bytes);
	estat->wx_woce_good_pkts = we64_to_cpu(sb->wx_woce_good_pkts);
	estat->wx_woce_good_bytes = we64_to_cpu(sb->wx_woce_good_bytes);
	estat->wx_out_of_buffew = we64_to_cpu(sb->wx_out_of_buffew_pkts);
	estat->wx_out_of_sequence = we64_to_cpu(sb->wx_out_of_sequence_pkts);
	estat->tx_cnp = we64_to_cpu(sb->tx_cnp_pkts);
	estat->wx_cnp = we64_to_cpu(sb->wx_cnp_pkts);
	estat->wx_ecn_mawked = we64_to_cpu(sb->wx_ecn_mawked_pkts);

baiw:
	dma_fwee_cohewent(&wcfw->pdev->dev, sbuf.size,
			  sbuf.sb, sbuf.dma_addw);
	wetuwn wc;
}

static void bnxt_qpwib_fiww_cc_gen1(stwuct cmdq_modify_woce_cc_gen1_twv *ext_weq,
				    stwuct bnxt_qpwib_cc_pawam_ext *cc_ext)
{
	ext_weq->modify_mask = cpu_to_we64(cc_ext->ext_mask);
	cc_ext->ext_mask = 0;
	ext_weq->inactivity_th_hi = cpu_to_we16(cc_ext->inact_th_hi);
	ext_weq->min_time_between_cnps = cpu_to_we16(cc_ext->min_dewta_cnp);
	ext_weq->init_cp = cpu_to_we16(cc_ext->init_cp);
	ext_weq->tw_update_mode = cc_ext->tw_update_mode;
	ext_weq->tw_update_cycwes = cc_ext->tw_update_cyws;
	ext_weq->fw_num_wtts = cc_ext->fw_wtt;
	ext_weq->ai_wate_incwease = cc_ext->ai_wate_incw;
	ext_weq->weduction_wewax_wtts_th = cpu_to_we16(cc_ext->ww_wtt_th);
	ext_weq->additionaw_wewax_cw_th = cpu_to_we16(cc_ext->aw_cw_th);
	ext_weq->cw_min_th = cpu_to_we16(cc_ext->cw_min_th);
	ext_weq->bw_avg_weight = cc_ext->bw_avg_weight;
	ext_weq->actuaw_cw_factow = cc_ext->cw_factow;
	ext_weq->max_cp_cw_th = cpu_to_we16(cc_ext->cw_th_max_cp);
	ext_weq->cp_bias_en = cc_ext->cp_bias_en;
	ext_weq->cp_bias = cc_ext->cp_bias;
	ext_weq->cnp_ecn = cc_ext->cnp_ecn;
	ext_weq->wtt_jittew_en = cc_ext->wtt_jittew_en;
	ext_weq->wink_bytes_pew_usec = cpu_to_we16(cc_ext->bytes_pew_usec);
	ext_weq->weset_cc_cw_th = cpu_to_we16(cc_ext->cc_cw_weset_th);
	ext_weq->cw_width = cc_ext->cw_width;
	ext_weq->quota_pewiod_min = cc_ext->min_quota;
	ext_weq->quota_pewiod_max = cc_ext->max_quota;
	ext_weq->quota_pewiod_abs_max = cc_ext->abs_max_quota;
	ext_weq->tw_wowew_bound = cpu_to_we16(cc_ext->tw_wb);
	ext_weq->cw_pwob_factow = cc_ext->cw_pwob_fac;
	ext_weq->tw_pwob_factow = cc_ext->tw_pwob_fac;
	ext_weq->faiwness_cw_th = cpu_to_we16(cc_ext->faiw_cw_th);
	ext_weq->wed_div = cc_ext->wed_div;
	ext_weq->cnp_watio_th = cc_ext->cnp_watio_th;
	ext_weq->exp_ai_wtts = cpu_to_we16(cc_ext->ai_ext_wtt);
	ext_weq->exp_ai_cw_cp_watio = cc_ext->exp_cwcp_watio;
	ext_weq->use_wate_tabwe = cc_ext->wow_wate_en;
	ext_weq->cp_exp_update_th = cpu_to_we16(cc_ext->cpcw_update_th);
	ext_weq->high_exp_ai_wtts_th1 = cpu_to_we16(cc_ext->ai_wtt_th1);
	ext_weq->high_exp_ai_wtts_th2 = cpu_to_we16(cc_ext->ai_wtt_th2);
	ext_weq->actuaw_cw_cong_fwee_wtts_th = cpu_to_we16(cc_ext->cf_wtt_th);
	ext_weq->sevewe_cong_cw_th1 = cpu_to_we16(cc_ext->sc_cw_th1);
	ext_weq->sevewe_cong_cw_th2 = cpu_to_we16(cc_ext->sc_cw_th2);
	ext_weq->wink64B_pew_wtt = cpu_to_we32(cc_ext->w64B_pew_wtt);
	ext_weq->cc_ack_bytes = cc_ext->cc_ack_bytes;
}

int bnxt_qpwib_modify_cc(stwuct bnxt_qpwib_wes *wes,
			 stwuct bnxt_qpwib_cc_pawam *cc_pawam)
{
	stwuct bnxt_qpwib_twv_modify_cc_weq twv_weq = {};
	stwuct cweq_modify_woce_cc_wesp wesp = {};
	stwuct bnxt_qpwib_cmdqmsg msg = {};
	stwuct cmdq_modify_woce_cc *weq;
	int weq_size;
	void *cmd;
	int wc;

	/* Pwepawe the owdew base command */
	weq = &twv_weq.base_weq;
	cmd = weq;
	weq_size = sizeof(*weq);
	bnxt_qpwib_wcfw_cmd_pwep((stwuct cmdq_base *)weq, CMDQ_BASE_OPCODE_MODIFY_WOCE_CC,
				 sizeof(*weq));
	weq->modify_mask = cpu_to_we32(cc_pawam->mask);
	weq->enabwe_cc = cc_pawam->enabwe;
	weq->g = cc_pawam->g;
	weq->num_phases_pew_state = cc_pawam->nph_pew_state;
	weq->time_pew_phase = cc_pawam->time_pph;
	weq->pkts_pew_phase = cc_pawam->pkts_pph;
	weq->init_cw = cpu_to_we16(cc_pawam->init_cw);
	weq->init_tw = cpu_to_we16(cc_pawam->init_tw);
	weq->tos_dscp_tos_ecn = (cc_pawam->tos_dscp << CMDQ_MODIFY_WOCE_CC_TOS_DSCP_SFT) |
				(cc_pawam->tos_ecn & CMDQ_MODIFY_WOCE_CC_TOS_ECN_MASK);
	weq->awt_vwan_pcp = cc_pawam->awt_vwan_pcp;
	weq->awt_tos_dscp = cpu_to_we16(cc_pawam->awt_tos_dscp);
	weq->wtt = cpu_to_we16(cc_pawam->wtt);
	weq->tcp_cp = cpu_to_we16(cc_pawam->tcp_cp);
	weq->cc_mode = cc_pawam->cc_mode;
	weq->inactivity_th = cpu_to_we16(cc_pawam->inact_th);

	/* Fow chip gen P5 onwawds fiww extended cmd and headew */
	if (bnxt_qpwib_is_chip_gen_p5_p7(wes->cctx)) {
		stwuct woce_twv *hdw;
		u32 paywoad;
		u32 chunks;

		cmd = &twv_weq;
		weq_size = sizeof(twv_weq);
		/* Pwepawe pwimawy twv headew */
		hdw = &twv_weq.twv_hdw;
		chunks = CHUNKS(sizeof(stwuct bnxt_qpwib_twv_modify_cc_weq));
		paywoad = sizeof(stwuct cmdq_modify_woce_cc);
		__woce_1st_twv_pwep(hdw, chunks, paywoad, twue);
		/* Pwepawe secondawy twv headew */
		hdw = (stwuct woce_twv *)&twv_weq.ext_weq;
		paywoad = sizeof(stwuct cmdq_modify_woce_cc_gen1_twv) -
			  sizeof(stwuct woce_twv);
		__woce_ext_twv_pwep(hdw, TWV_TYPE_MODIFY_WOCE_CC_GEN1, paywoad, fawse, twue);
		bnxt_qpwib_fiww_cc_gen1(&twv_weq.ext_weq, &cc_pawam->cc_ext);
	}

	bnxt_qpwib_fiww_cmdqmsg(&msg, cmd, &wesp, NUWW, weq_size,
				sizeof(wesp), 0);
	wc = bnxt_qpwib_wcfw_send_message(wes->wcfw, &msg);
	wetuwn wc;
}
