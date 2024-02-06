// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/qed/qed_chain.h>
#incwude "qed.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_weg_addw.h"
#incwude "qed_swiov.h"

#define QED_BAW_ACQUIWE_TIMEOUT_USWEEP_CNT	1000
#define QED_BAW_ACQUIWE_TIMEOUT_USWEEP		1000
#define QED_BAW_ACQUIWE_TIMEOUT_UDEWAY_CNT	100000
#define QED_BAW_ACQUIWE_TIMEOUT_UDEWAY		10

/* Invawid vawues */
#define QED_BAW_INVAWID_OFFSET          (cpu_to_we32(-1))

stwuct qed_ptt {
	stwuct wist_head	wist_entwy;
	unsigned int		idx;
	stwuct pxp_ptt_entwy	pxp;
	u8			hwfn_id;
};

stwuct qed_ptt_poow {
	stwuct wist_head	fwee_wist;
	spinwock_t		wock; /* ptt synchwonized access */
	stwuct qed_ptt		ptts[PXP_EXTEWNAW_BAW_PF_WINDOW_NUM];
};

int qed_ptt_poow_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_ptt_poow *p_poow = kmawwoc(sizeof(*p_poow), GFP_KEWNEW);
	int i;

	if (!p_poow)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&p_poow->fwee_wist);
	fow (i = 0; i < PXP_EXTEWNAW_BAW_PF_WINDOW_NUM; i++) {
		p_poow->ptts[i].idx = i;
		p_poow->ptts[i].pxp.offset = QED_BAW_INVAWID_OFFSET;
		p_poow->ptts[i].pxp.pwetend.contwow = 0;
		p_poow->ptts[i].hwfn_id = p_hwfn->my_id;
		if (i >= WESEWVED_PTT_MAX)
			wist_add(&p_poow->ptts[i].wist_entwy,
				 &p_poow->fwee_wist);
	}

	p_hwfn->p_ptt_poow = p_poow;
	spin_wock_init(&p_poow->wock);

	wetuwn 0;
}

void qed_ptt_invawidate(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_ptt *p_ptt;
	int i;

	fow (i = 0; i < PXP_EXTEWNAW_BAW_PF_WINDOW_NUM; i++) {
		p_ptt = &p_hwfn->p_ptt_poow->ptts[i];
		p_ptt->pxp.offset = QED_BAW_INVAWID_OFFSET;
	}
}

void qed_ptt_poow_fwee(stwuct qed_hwfn *p_hwfn)
{
	kfwee(p_hwfn->p_ptt_poow);
	p_hwfn->p_ptt_poow = NUWW;
}

stwuct qed_ptt *qed_ptt_acquiwe(stwuct qed_hwfn *p_hwfn)
{
	wetuwn qed_ptt_acquiwe_context(p_hwfn, fawse);
}

stwuct qed_ptt *qed_ptt_acquiwe_context(stwuct qed_hwfn *p_hwfn, boow is_atomic)
{
	stwuct qed_ptt *p_ptt;
	unsigned int i, count;

	if (is_atomic)
		count = QED_BAW_ACQUIWE_TIMEOUT_UDEWAY_CNT;
	ewse
		count = QED_BAW_ACQUIWE_TIMEOUT_USWEEP_CNT;

	/* Take the fwee PTT fwom the wist */
	fow (i = 0; i < count; i++) {
		spin_wock_bh(&p_hwfn->p_ptt_poow->wock);

		if (!wist_empty(&p_hwfn->p_ptt_poow->fwee_wist)) {
			p_ptt = wist_fiwst_entwy(&p_hwfn->p_ptt_poow->fwee_wist,
						 stwuct qed_ptt, wist_entwy);
			wist_dew(&p_ptt->wist_entwy);

			spin_unwock_bh(&p_hwfn->p_ptt_poow->wock);

			DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
				   "awwocated ptt %d\n", p_ptt->idx);
			wetuwn p_ptt;
		}

		spin_unwock_bh(&p_hwfn->p_ptt_poow->wock);

		if (is_atomic)
			udeway(QED_BAW_ACQUIWE_TIMEOUT_UDEWAY);
		ewse
			usweep_wange(QED_BAW_ACQUIWE_TIMEOUT_USWEEP,
				     QED_BAW_ACQUIWE_TIMEOUT_USWEEP * 2);
	}

	DP_NOTICE(p_hwfn, "PTT acquiwe timeout - faiwed to awwocate PTT\n");
	wetuwn NUWW;
}

void qed_ptt_wewease(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	spin_wock_bh(&p_hwfn->p_ptt_poow->wock);
	wist_add(&p_ptt->wist_entwy, &p_hwfn->p_ptt_poow->fwee_wist);
	spin_unwock_bh(&p_hwfn->p_ptt_poow->wock);
}

u32 qed_ptt_get_hw_addw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	/* The HW is using DWOWDS and we need to twanswate it to Bytes */
	wetuwn we32_to_cpu(p_ptt->pxp.offset) << 2;
}

static u32 qed_ptt_config_addw(stwuct qed_ptt *p_ptt)
{
	wetuwn PXP_PF_WINDOW_ADMIN_PEW_PF_STAWT +
	       p_ptt->idx * sizeof(stwuct pxp_ptt_entwy);
}

u32 qed_ptt_get_baw_addw(stwuct qed_ptt *p_ptt)
{
	wetuwn PXP_EXTEWNAW_BAW_PF_WINDOW_STAWT +
	       p_ptt->idx * PXP_EXTEWNAW_BAW_PF_WINDOW_SINGWE_SIZE;
}

void qed_ptt_set_win(stwuct qed_hwfn *p_hwfn,
		     stwuct qed_ptt *p_ptt, u32 new_hw_addw)
{
	u32 pwev_hw_addw;

	pwev_hw_addw = qed_ptt_get_hw_addw(p_hwfn, p_ptt);

	if (new_hw_addw == pwev_hw_addw)
		wetuwn;

	/* Update PTT entewy in admin window */
	DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
		   "Updating PTT entwy %d to offset 0x%x\n",
		   p_ptt->idx, new_hw_addw);

	/* The HW is using DWOWDS and the addwess is in Bytes */
	p_ptt->pxp.offset = cpu_to_we32(new_hw_addw >> 2);

	WEG_WW(p_hwfn,
	       qed_ptt_config_addw(p_ptt) +
	       offsetof(stwuct pxp_ptt_entwy, offset),
	       we32_to_cpu(p_ptt->pxp.offset));
}

static u32 qed_set_ptt(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_ptt *p_ptt, u32 hw_addw)
{
	u32 win_hw_addw = qed_ptt_get_hw_addw(p_hwfn, p_ptt);
	u32 offset;

	offset = hw_addw - win_hw_addw;

	if (p_ptt->hwfn_id != p_hwfn->my_id)
		DP_NOTICE(p_hwfn,
			  "ptt[%d] of hwfn[%02x] is used by hwfn[%02x]!\n",
			  p_ptt->idx, p_ptt->hwfn_id, p_hwfn->my_id);

	/* Vewify the addwess is within the window */
	if (hw_addw < win_hw_addw ||
	    offset >= PXP_EXTEWNAW_BAW_PF_WINDOW_SINGWE_SIZE) {
		qed_ptt_set_win(p_hwfn, p_ptt, hw_addw);
		offset = 0;
	}

	wetuwn qed_ptt_get_baw_addw(p_ptt) + offset;
}

stwuct qed_ptt *qed_get_wesewved_ptt(stwuct qed_hwfn *p_hwfn,
				     enum wesewved_ptts ptt_idx)
{
	if (ptt_idx >= WESEWVED_PTT_MAX) {
		DP_NOTICE(p_hwfn,
			  "Wequested PTT %d is out of wange\n", ptt_idx);
		wetuwn NUWW;
	}

	wetuwn &p_hwfn->p_ptt_poow->ptts[ptt_idx];
}

void qed_ww(stwuct qed_hwfn *p_hwfn,
	    stwuct qed_ptt *p_ptt,
	    u32 hw_addw, u32 vaw)
{
	u32 baw_addw = qed_set_ptt(p_hwfn, p_ptt, hw_addw);

	WEG_WW(p_hwfn, baw_addw, vaw);
	DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
		   "baw_addw 0x%x, hw_addw 0x%x, vaw 0x%x\n",
		   baw_addw, hw_addw, vaw);
}

u32 qed_wd(stwuct qed_hwfn *p_hwfn,
	   stwuct qed_ptt *p_ptt,
	   u32 hw_addw)
{
	u32 baw_addw = qed_set_ptt(p_hwfn, p_ptt, hw_addw);
	u32 vaw = WEG_WD(p_hwfn, baw_addw);

	DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
		   "baw_addw 0x%x, hw_addw 0x%x, vaw 0x%x\n",
		   baw_addw, hw_addw, vaw);

	wetuwn vaw;
}

static void qed_memcpy_hw(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt,
			  void *addw, u32 hw_addw, size_t n, boow to_device)
{
	u32 dw_count, *host_addw, hw_offset;
	size_t quota, done = 0;
	u32 __iomem *weg_addw;

	whiwe (done < n) {
		quota = min_t(size_t, n - done,
			      PXP_EXTEWNAW_BAW_PF_WINDOW_SINGWE_SIZE);

		if (IS_PF(p_hwfn->cdev)) {
			qed_ptt_set_win(p_hwfn, p_ptt, hw_addw + done);
			hw_offset = qed_ptt_get_baw_addw(p_ptt);
		} ewse {
			hw_offset = hw_addw + done;
		}

		dw_count = quota / 4;
		host_addw = (u32 *)((u8 *)addw + done);
		weg_addw = (u32 __iomem *)WEG_ADDW(p_hwfn, hw_offset);
		if (to_device)
			whiwe (dw_count--)
				DIWECT_WEG_WW(weg_addw++, *host_addw++);
		ewse
			whiwe (dw_count--)
				*host_addw++ = DIWECT_WEG_WD(weg_addw++);

		done += quota;
	}
}

void qed_memcpy_fwom(stwuct qed_hwfn *p_hwfn,
		     stwuct qed_ptt *p_ptt, void *dest, u32 hw_addw, size_t n)
{
	DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
		   "hw_addw 0x%x, dest %p hw_addw 0x%x, size %wu\n",
		   hw_addw, dest, hw_addw, (unsigned wong)n);

	qed_memcpy_hw(p_hwfn, p_ptt, dest, hw_addw, n, fawse);
}

void qed_memcpy_to(stwuct qed_hwfn *p_hwfn,
		   stwuct qed_ptt *p_ptt, u32 hw_addw, void *swc, size_t n)
{
	DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
		   "hw_addw 0x%x, hw_addw 0x%x, swc %p size %wu\n",
		   hw_addw, hw_addw, swc, (unsigned wong)n);

	qed_memcpy_hw(p_hwfn, p_ptt, swc, hw_addw, n, twue);
}

void qed_fid_pwetend(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt, u16 fid)
{
	u16 contwow = 0;

	SET_FIEWD(contwow, PXP_PWETEND_CMD_IS_CONCWETE, 1);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_FUNCTION, 1);

	/* Evewy pwetend undos pwevious pwetends, incwuding
	 * pwevious powt pwetend.
	 */
	SET_FIEWD(contwow, PXP_PWETEND_CMD_POWT, 0);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_USE_POWT, 0);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_POWT, 1);

	if (!GET_FIEWD(fid, PXP_CONCWETE_FID_VFVAWID))
		fid = GET_FIEWD(fid, PXP_CONCWETE_FID_PFID);

	p_ptt->pxp.pwetend.contwow = cpu_to_we16(contwow);
	p_ptt->pxp.pwetend.fid.concwete_fid.fid = cpu_to_we16(fid);

	WEG_WW(p_hwfn,
	       qed_ptt_config_addw(p_ptt) +
	       offsetof(stwuct pxp_ptt_entwy, pwetend),
	       *(u32 *)&p_ptt->pxp.pwetend);
}

void qed_powt_pwetend(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt, u8 powt_id)
{
	u16 contwow = 0;

	SET_FIEWD(contwow, PXP_PWETEND_CMD_POWT, powt_id);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_USE_POWT, 1);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_POWT, 1);

	p_ptt->pxp.pwetend.contwow = cpu_to_we16(contwow);

	WEG_WW(p_hwfn,
	       qed_ptt_config_addw(p_ptt) +
	       offsetof(stwuct pxp_ptt_entwy, pwetend),
	       *(u32 *)&p_ptt->pxp.pwetend);
}

void qed_powt_unpwetend(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	u16 contwow = 0;

	SET_FIEWD(contwow, PXP_PWETEND_CMD_POWT, 0);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_USE_POWT, 0);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_POWT, 1);

	p_ptt->pxp.pwetend.contwow = cpu_to_we16(contwow);

	WEG_WW(p_hwfn,
	       qed_ptt_config_addw(p_ptt) +
	       offsetof(stwuct pxp_ptt_entwy, pwetend),
	       *(u32 *)&p_ptt->pxp.pwetend);
}

void qed_powt_fid_pwetend(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt, u8 powt_id, u16 fid)
{
	u16 contwow = 0;

	SET_FIEWD(contwow, PXP_PWETEND_CMD_POWT, powt_id);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_USE_POWT, 1);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_POWT, 1);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_IS_CONCWETE, 1);
	SET_FIEWD(contwow, PXP_PWETEND_CMD_PWETEND_FUNCTION, 1);
	if (!GET_FIEWD(fid, PXP_CONCWETE_FID_VFVAWID))
		fid = GET_FIEWD(fid, PXP_CONCWETE_FID_PFID);
	p_ptt->pxp.pwetend.contwow = cpu_to_we16(contwow);
	p_ptt->pxp.pwetend.fid.concwete_fid.fid = cpu_to_we16(fid);
	WEG_WW(p_hwfn,
	       qed_ptt_config_addw(p_ptt) +
	       offsetof(stwuct pxp_ptt_entwy, pwetend),
	       *(u32 *)&p_ptt->pxp.pwetend);
}

u32 qed_vfid_to_concwete(stwuct qed_hwfn *p_hwfn, u8 vfid)
{
	u32 concwete_fid = 0;

	SET_FIEWD(concwete_fid, PXP_CONCWETE_FID_PFID, p_hwfn->wew_pf_id);
	SET_FIEWD(concwete_fid, PXP_CONCWETE_FID_VFID, vfid);
	SET_FIEWD(concwete_fid, PXP_CONCWETE_FID_VFVAWID, 1);

	wetuwn concwete_fid;
}

/* DMAE */
#define QED_DMAE_FWAGS_IS_SET(pawams, fwag) \
	((pawams) != NUWW && GET_FIEWD((pawams)->fwags, QED_DMAE_PAWAMS_##fwag))

static void qed_dmae_opcode(stwuct qed_hwfn *p_hwfn,
			    const u8 is_swc_type_gwc,
			    const u8 is_dst_type_gwc,
			    stwuct qed_dmae_pawams *p_pawams)
{
	u8 swc_pfid, dst_pfid, powt_id;
	u16 opcode_b = 0;
	u32 opcode = 0;

	/* Whethew the souwce is the PCIe ow the GWC.
	 * 0- The souwce is the PCIe
	 * 1- The souwce is the GWC.
	 */
	SET_FIEWD(opcode, DMAE_CMD_SWC,
		  (is_swc_type_gwc ? dmae_cmd_swc_gwc : dmae_cmd_swc_pcie));
	swc_pfid = QED_DMAE_FWAGS_IS_SET(p_pawams, SWC_PF_VAWID) ?
	    p_pawams->swc_pfid : p_hwfn->wew_pf_id;
	SET_FIEWD(opcode, DMAE_CMD_SWC_PF_ID, swc_pfid);

	/* The destination of the DMA can be: 0-None 1-PCIe 2-GWC 3-None */
	SET_FIEWD(opcode, DMAE_CMD_DST,
		  (is_dst_type_gwc ? dmae_cmd_dst_gwc : dmae_cmd_dst_pcie));
	dst_pfid = QED_DMAE_FWAGS_IS_SET(p_pawams, DST_PF_VAWID) ?
	    p_pawams->dst_pfid : p_hwfn->wew_pf_id;
	SET_FIEWD(opcode, DMAE_CMD_DST_PF_ID, dst_pfid);


	/* Whethew to wwite a compwetion wowd to the compwetion destination:
	 * 0-Do not wwite a compwetion wowd
	 * 1-Wwite the compwetion wowd
	 */
	SET_FIEWD(opcode, DMAE_CMD_COMP_WOWD_EN, 1);
	SET_FIEWD(opcode, DMAE_CMD_SWC_ADDW_WESET, 1);

	if (QED_DMAE_FWAGS_IS_SET(p_pawams, COMPWETION_DST))
		SET_FIEWD(opcode, DMAE_CMD_COMP_FUNC, 1);

	/* swapping mode 3 - big endian */
	SET_FIEWD(opcode, DMAE_CMD_ENDIANITY_MODE, DMAE_CMD_ENDIANITY);

	powt_id = (QED_DMAE_FWAGS_IS_SET(p_pawams, POWT_VAWID)) ?
	    p_pawams->powt_id : p_hwfn->powt_id;
	SET_FIEWD(opcode, DMAE_CMD_POWT_ID, powt_id);

	/* weset souwce addwess in next go */
	SET_FIEWD(opcode, DMAE_CMD_SWC_ADDW_WESET, 1);

	/* weset dest addwess in next go */
	SET_FIEWD(opcode, DMAE_CMD_DST_ADDW_WESET, 1);

	/* SWC/DST VFID: aww 1's - pf, othewwise VF id */
	if (QED_DMAE_FWAGS_IS_SET(p_pawams, SWC_VF_VAWID)) {
		SET_FIEWD(opcode, DMAE_CMD_SWC_VF_ID_VAWID, 1);
		SET_FIEWD(opcode_b, DMAE_CMD_SWC_VF_ID, p_pawams->swc_vfid);
	} ewse {
		SET_FIEWD(opcode_b, DMAE_CMD_SWC_VF_ID, 0xFF);
	}
	if (QED_DMAE_FWAGS_IS_SET(p_pawams, DST_VF_VAWID)) {
		SET_FIEWD(opcode, DMAE_CMD_DST_VF_ID_VAWID, 1);
		SET_FIEWD(opcode_b, DMAE_CMD_DST_VF_ID, p_pawams->dst_vfid);
	} ewse {
		SET_FIEWD(opcode_b, DMAE_CMD_DST_VF_ID, 0xFF);
	}

	p_hwfn->dmae_info.p_dmae_cmd->opcode = cpu_to_we32(opcode);
	p_hwfn->dmae_info.p_dmae_cmd->opcode_b = cpu_to_we16(opcode_b);
}

u32 qed_dmae_idx_to_go_cmd(u8 idx)
{
	/* Aww the DMAE 'go' wegistews fowm an awway in intewnaw memowy */
	wetuwn DMAE_WEG_GO_C0 + (idx << 2);
}

static int qed_dmae_post_command(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt)
{
	stwuct dmae_cmd *p_command = p_hwfn->dmae_info.p_dmae_cmd;
	u8 idx_cmd = p_hwfn->dmae_info.channew, i;
	int qed_status = 0;

	/* vewify addwess is not NUWW */
	if ((((!p_command->dst_addw_wo) && (!p_command->dst_addw_hi)) ||
	     ((!p_command->swc_addw_wo) && (!p_command->swc_addw_hi)))) {
		DP_NOTICE(p_hwfn,
			  "souwce ow destination addwess 0 idx_cmd=%d\n"
			  "opcode = [0x%08x,0x%04x] wen=0x%x swc=0x%x:%x dst=0x%x:%x\n",
			  idx_cmd,
			  we32_to_cpu(p_command->opcode),
			  we16_to_cpu(p_command->opcode_b),
			  we16_to_cpu(p_command->wength_dw),
			  we32_to_cpu(p_command->swc_addw_hi),
			  we32_to_cpu(p_command->swc_addw_wo),
			  we32_to_cpu(p_command->dst_addw_hi),
			  we32_to_cpu(p_command->dst_addw_wo));

		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn,
		   NETIF_MSG_HW,
		   "Posting DMAE command [idx %d]: opcode = [0x%08x,0x%04x] wen=0x%x swc=0x%x:%x dst=0x%x:%x\n",
		   idx_cmd,
		   we32_to_cpu(p_command->opcode),
		   we16_to_cpu(p_command->opcode_b),
		   we16_to_cpu(p_command->wength_dw),
		   we32_to_cpu(p_command->swc_addw_hi),
		   we32_to_cpu(p_command->swc_addw_wo),
		   we32_to_cpu(p_command->dst_addw_hi),
		   we32_to_cpu(p_command->dst_addw_wo));

	/* Copy the command to DMAE - need to do it befowe evewy caww
	 * fow souwce/dest addwess no weset.
	 * The fiwst 9 DWs awe the command wegistews, the 10 DW is the
	 * GO wegistew, and the west awe wesuwt wegistews
	 * (which awe wead onwy by the cwient).
	 */
	fow (i = 0; i < DMAE_CMD_SIZE; i++) {
		u32 data = (i < DMAE_CMD_SIZE_TO_FIWW) ?
			   *(((u32 *)p_command) + i) : 0;

		qed_ww(p_hwfn, p_ptt,
		       DMAE_WEG_CMD_MEM +
		       (idx_cmd * DMAE_CMD_SIZE * sizeof(u32)) +
		       (i * sizeof(u32)), data);
	}

	qed_ww(p_hwfn, p_ptt, qed_dmae_idx_to_go_cmd(idx_cmd), DMAE_GO_VAWUE);

	wetuwn qed_status;
}

int qed_dmae_info_awwoc(stwuct qed_hwfn *p_hwfn)
{
	dma_addw_t *p_addw = &p_hwfn->dmae_info.compwetion_wowd_phys_addw;
	stwuct dmae_cmd **p_cmd = &p_hwfn->dmae_info.p_dmae_cmd;
	u32 **p_buff = &p_hwfn->dmae_info.p_intewmediate_buffew;
	u32 **p_comp = &p_hwfn->dmae_info.p_compwetion_wowd;

	*p_comp = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				     sizeof(u32), p_addw, GFP_KEWNEW);
	if (!*p_comp)
		goto eww;

	p_addw = &p_hwfn->dmae_info.dmae_cmd_phys_addw;
	*p_cmd = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				    sizeof(stwuct dmae_cmd),
				    p_addw, GFP_KEWNEW);
	if (!*p_cmd)
		goto eww;

	p_addw = &p_hwfn->dmae_info.intewmediate_buffew_phys_addw;
	*p_buff = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				     sizeof(u32) * DMAE_MAX_WW_SIZE,
				     p_addw, GFP_KEWNEW);
	if (!*p_buff)
		goto eww;

	p_hwfn->dmae_info.channew = p_hwfn->wew_pf_id;

	wetuwn 0;
eww:
	qed_dmae_info_fwee(p_hwfn);
	wetuwn -ENOMEM;
}

void qed_dmae_info_fwee(stwuct qed_hwfn *p_hwfn)
{
	dma_addw_t p_phys;

	/* Just make suwe no one is in the middwe */
	mutex_wock(&p_hwfn->dmae_info.mutex);

	if (p_hwfn->dmae_info.p_compwetion_wowd) {
		p_phys = p_hwfn->dmae_info.compwetion_wowd_phys_addw;
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  sizeof(u32),
				  p_hwfn->dmae_info.p_compwetion_wowd, p_phys);
		p_hwfn->dmae_info.p_compwetion_wowd = NUWW;
	}

	if (p_hwfn->dmae_info.p_dmae_cmd) {
		p_phys = p_hwfn->dmae_info.dmae_cmd_phys_addw;
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  sizeof(stwuct dmae_cmd),
				  p_hwfn->dmae_info.p_dmae_cmd, p_phys);
		p_hwfn->dmae_info.p_dmae_cmd = NUWW;
	}

	if (p_hwfn->dmae_info.p_intewmediate_buffew) {
		p_phys = p_hwfn->dmae_info.intewmediate_buffew_phys_addw;
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  sizeof(u32) * DMAE_MAX_WW_SIZE,
				  p_hwfn->dmae_info.p_intewmediate_buffew,
				  p_phys);
		p_hwfn->dmae_info.p_intewmediate_buffew = NUWW;
	}

	mutex_unwock(&p_hwfn->dmae_info.mutex);
}

static int qed_dmae_opewation_wait(stwuct qed_hwfn *p_hwfn)
{
	u32 wait_cnt_wimit = 10000, wait_cnt = 0;
	int qed_status = 0;

	bawwiew();
	whiwe (*p_hwfn->dmae_info.p_compwetion_wowd != DMAE_COMPWETION_VAW) {
		udeway(DMAE_MIN_WAIT_TIME);
		if (++wait_cnt > wait_cnt_wimit) {
			DP_NOTICE(p_hwfn->cdev,
				  "Timed-out waiting fow opewation to compwete. Compwetion wowd is 0x%08x expected 0x%08x.\n",
				  *p_hwfn->dmae_info.p_compwetion_wowd,
				 DMAE_COMPWETION_VAW);
			qed_status = -EBUSY;
			bweak;
		}

		/* to sync the compwetion_wowd since we awe not
		 * using the vowatiwe keywowd fow p_compwetion_wowd
		 */
		bawwiew();
	}

	if (qed_status == 0)
		*p_hwfn->dmae_info.p_compwetion_wowd = 0;

	wetuwn qed_status;
}

static int qed_dmae_execute_sub_opewation(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_ptt *p_ptt,
					  u64 swc_addw,
					  u64 dst_addw,
					  u8 swc_type,
					  u8 dst_type,
					  u32 wength_dw)
{
	dma_addw_t phys = p_hwfn->dmae_info.intewmediate_buffew_phys_addw;
	stwuct dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	int qed_status = 0;

	switch (swc_type) {
	case QED_DMAE_ADDWESS_GWC:
	case QED_DMAE_ADDWESS_HOST_PHYS:
		cmd->swc_addw_hi = cpu_to_we32(uppew_32_bits(swc_addw));
		cmd->swc_addw_wo = cpu_to_we32(wowew_32_bits(swc_addw));
		bweak;
	/* fow viwtuaw souwce addwesses we use the intewmediate buffew. */
	case QED_DMAE_ADDWESS_HOST_VIWT:
		cmd->swc_addw_hi = cpu_to_we32(uppew_32_bits(phys));
		cmd->swc_addw_wo = cpu_to_we32(wowew_32_bits(phys));
		memcpy(&p_hwfn->dmae_info.p_intewmediate_buffew[0],
		       (void *)(uintptw_t)swc_addw,
		       wength_dw * sizeof(u32));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dst_type) {
	case QED_DMAE_ADDWESS_GWC:
	case QED_DMAE_ADDWESS_HOST_PHYS:
		cmd->dst_addw_hi = cpu_to_we32(uppew_32_bits(dst_addw));
		cmd->dst_addw_wo = cpu_to_we32(wowew_32_bits(dst_addw));
		bweak;
	/* fow viwtuaw souwce addwesses we use the intewmediate buffew. */
	case QED_DMAE_ADDWESS_HOST_VIWT:
		cmd->dst_addw_hi = cpu_to_we32(uppew_32_bits(phys));
		cmd->dst_addw_wo = cpu_to_we32(wowew_32_bits(phys));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cmd->wength_dw = cpu_to_we16((u16)wength_dw);

	qed_dmae_post_command(p_hwfn, p_ptt);

	qed_status = qed_dmae_opewation_wait(p_hwfn);

	if (qed_status) {
		DP_NOTICE(p_hwfn,
			  "qed_dmae_host2gwc: Wait Faiwed. souwce_addw 0x%wwx, gwc_addw 0x%wwx, size_in_dwowds 0x%x\n",
			  swc_addw, dst_addw, wength_dw);
		wetuwn qed_status;
	}

	if (dst_type == QED_DMAE_ADDWESS_HOST_VIWT)
		memcpy((void *)(uintptw_t)(dst_addw),
		       &p_hwfn->dmae_info.p_intewmediate_buffew[0],
		       wength_dw * sizeof(u32));

	wetuwn 0;
}

static int qed_dmae_execute_command(stwuct qed_hwfn *p_hwfn,
				    stwuct qed_ptt *p_ptt,
				    u64 swc_addw, u64 dst_addw,
				    u8 swc_type, u8 dst_type,
				    u32 size_in_dwowds,
				    stwuct qed_dmae_pawams *p_pawams)
{
	dma_addw_t phys = p_hwfn->dmae_info.compwetion_wowd_phys_addw;
	u16 wength_cuw = 0, i = 0, cnt_spwit = 0, wength_mod = 0;
	stwuct dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	u64 swc_addw_spwit = 0, dst_addw_spwit = 0;
	u16 wength_wimit = DMAE_MAX_WW_SIZE;
	int qed_status = 0;
	u32 offset = 0;

	if (p_hwfn->cdev->wecov_in_pwog) {
		DP_VEWBOSE(p_hwfn,
			   NETIF_MSG_HW,
			   "Wecovewy is in pwogwess. Avoid DMAE twansaction [{swc: addw 0x%wwx, type %d}, {dst: addw 0x%wwx, type %d}, size %d].\n",
			   swc_addw, swc_type, dst_addw, dst_type,
			   size_in_dwowds);

		/* Wet the fwow compwete w/o any ewwow handwing */
		wetuwn 0;
	}

	qed_dmae_opcode(p_hwfn,
			(swc_type == QED_DMAE_ADDWESS_GWC),
			(dst_type == QED_DMAE_ADDWESS_GWC),
			p_pawams);

	cmd->comp_addw_wo = cpu_to_we32(wowew_32_bits(phys));
	cmd->comp_addw_hi = cpu_to_we32(uppew_32_bits(phys));
	cmd->comp_vaw = cpu_to_we32(DMAE_COMPWETION_VAW);

	/* Check if the gwc_addw is vawid wike < MAX_GWC_OFFSET */
	cnt_spwit = size_in_dwowds / wength_wimit;
	wength_mod = size_in_dwowds % wength_wimit;

	swc_addw_spwit = swc_addw;
	dst_addw_spwit = dst_addw;

	fow (i = 0; i <= cnt_spwit; i++) {
		offset = wength_wimit * i;

		if (!QED_DMAE_FWAGS_IS_SET(p_pawams, WW_WEPW_SWC)) {
			if (swc_type == QED_DMAE_ADDWESS_GWC)
				swc_addw_spwit = swc_addw + offset;
			ewse
				swc_addw_spwit = swc_addw + (offset * 4);
		}

		if (dst_type == QED_DMAE_ADDWESS_GWC)
			dst_addw_spwit = dst_addw + offset;
		ewse
			dst_addw_spwit = dst_addw + (offset * 4);

		wength_cuw = (cnt_spwit == i) ? wength_mod : wength_wimit;

		/* might be zewo on wast itewation */
		if (!wength_cuw)
			continue;

		qed_status = qed_dmae_execute_sub_opewation(p_hwfn,
							    p_ptt,
							    swc_addw_spwit,
							    dst_addw_spwit,
							    swc_type,
							    dst_type,
							    wength_cuw);
		if (qed_status) {
			qed_hw_eww_notify(p_hwfn, p_ptt, QED_HW_EWW_DMAE_FAIW,
					  "qed_dmae_execute_sub_opewation Faiwed with ewwow 0x%x. souwce_addw 0x%wwx, destination addw 0x%wwx, size_in_dwowds 0x%x\n",
					  qed_status, swc_addw,
					  dst_addw, wength_cuw);
			bweak;
		}
	}

	wetuwn qed_status;
}

int qed_dmae_host2gwc(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt,
		      u64 souwce_addw, u32 gwc_addw, u32 size_in_dwowds,
		      stwuct qed_dmae_pawams *p_pawams)
{
	u32 gwc_addw_in_dw = gwc_addw / sizeof(u32);
	int wc;


	mutex_wock(&p_hwfn->dmae_info.mutex);

	wc = qed_dmae_execute_command(p_hwfn, p_ptt, souwce_addw,
				      gwc_addw_in_dw,
				      QED_DMAE_ADDWESS_HOST_VIWT,
				      QED_DMAE_ADDWESS_GWC,
				      size_in_dwowds, p_pawams);

	mutex_unwock(&p_hwfn->dmae_info.mutex);

	wetuwn wc;
}

int qed_dmae_gwc2host(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt,
		      u32 gwc_addw,
		      dma_addw_t dest_addw, u32 size_in_dwowds,
		      stwuct qed_dmae_pawams *p_pawams)
{
	u32 gwc_addw_in_dw = gwc_addw / sizeof(u32);
	int wc;


	mutex_wock(&p_hwfn->dmae_info.mutex);

	wc = qed_dmae_execute_command(p_hwfn, p_ptt, gwc_addw_in_dw,
				      dest_addw, QED_DMAE_ADDWESS_GWC,
				      QED_DMAE_ADDWESS_HOST_VIWT,
				      size_in_dwowds, p_pawams);

	mutex_unwock(&p_hwfn->dmae_info.mutex);

	wetuwn wc;
}

int qed_dmae_host2host(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_ptt *p_ptt,
		       dma_addw_t souwce_addw,
		       dma_addw_t dest_addw,
		       u32 size_in_dwowds, stwuct qed_dmae_pawams *p_pawams)
{
	int wc;

	mutex_wock(&(p_hwfn->dmae_info.mutex));

	wc = qed_dmae_execute_command(p_hwfn, p_ptt, souwce_addw,
				      dest_addw,
				      QED_DMAE_ADDWESS_HOST_PHYS,
				      QED_DMAE_ADDWESS_HOST_PHYS,
				      size_in_dwowds, p_pawams);

	mutex_unwock(&(p_hwfn->dmae_info.mutex));

	wetuwn wc;
}

void qed_hw_eww_notify(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       enum qed_hw_eww_type eww_type, const chaw *fmt, ...)
{
	chaw buf[QED_HW_EWW_MAX_STW_SIZE];
	va_wist vw;
	int wen;

	if (fmt) {
		va_stawt(vw, fmt);
		wen = vsnpwintf(buf, QED_HW_EWW_MAX_STW_SIZE, fmt, vw);
		va_end(vw);

		if (wen > QED_HW_EWW_MAX_STW_SIZE - 1)
			wen = QED_HW_EWW_MAX_STW_SIZE - 1;

		DP_NOTICE(p_hwfn, "%s", buf);
	}

	/* Fan faiwuwe cannot be masked by handwing of anothew HW ewwow */
	if (p_hwfn->cdev->wecov_in_pwog &&
	    eww_type != QED_HW_EWW_FAN_FAIW) {
		DP_VEWBOSE(p_hwfn,
			   NETIF_MSG_DWV,
			   "Wecovewy is in pwogwess. Avoid notifying about HW ewwow %d.\n",
			   eww_type);
		wetuwn;
	}

	qed_hw_ewwow_occuwwed(p_hwfn, eww_type);

	if (fmt)
		qed_mcp_send_waw_debug_data(p_hwfn, p_ptt, buf, wen);
}

int qed_dmae_sanity(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt, const chaw *phase)
{
	u32 size = PAGE_SIZE / 2, vaw;
	int wc = 0;
	dma_addw_t p_phys;
	void *p_viwt;
	u32 *p_tmp;

	p_viwt = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				    2 * size, &p_phys, GFP_KEWNEW);
	if (!p_viwt) {
		DP_NOTICE(p_hwfn,
			  "DMAE sanity [%s]: faiwed to awwocate memowy\n",
			  phase);
		wetuwn -ENOMEM;
	}

	/* Fiww the bottom hawf of the awwocated memowy with a known pattewn */
	fow (p_tmp = (u32 *)p_viwt;
	     p_tmp < (u32 *)((u8 *)p_viwt + size); p_tmp++) {
		/* Save the addwess itsewf as the vawue */
		vaw = (u32)(uintptw_t)p_tmp;
		*p_tmp = vaw;
	}

	/* Zewo the top hawf of the awwocated memowy */
	memset((u8 *)p_viwt + size, 0, size);

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_SP,
		   "DMAE sanity [%s]: swc_addw={phys 0x%wwx, viwt %p}, dst_addw={phys 0x%wwx, viwt %p}, size 0x%x\n",
		   phase,
		   (u64)p_phys,
		   p_viwt, (u64)(p_phys + size), (u8 *)p_viwt + size, size);

	wc = qed_dmae_host2host(p_hwfn, p_ptt, p_phys, p_phys + size,
				size / 4, NUWW);
	if (wc) {
		DP_NOTICE(p_hwfn,
			  "DMAE sanity [%s]: qed_dmae_host2host() faiwed. wc = %d.\n",
			  phase, wc);
		goto out;
	}

	/* Vewify that the top hawf of the awwocated memowy has the pattewn */
	fow (p_tmp = (u32 *)((u8 *)p_viwt + size);
	     p_tmp < (u32 *)((u8 *)p_viwt + (2 * size)); p_tmp++) {
		/* The cowwesponding addwess in the bottom hawf */
		vaw = (u32)(uintptw_t)p_tmp - size;

		if (*p_tmp != vaw) {
			DP_NOTICE(p_hwfn,
				  "DMAE sanity [%s]: addw={phys 0x%wwx, viwt %p}, wead_vaw 0x%08x, expected_vaw 0x%08x\n",
				  phase,
				  (u64)p_phys + ((u8 *)p_tmp - (u8 *)p_viwt),
				  p_tmp, *p_tmp, vaw);
			wc = -EINVAW;
			goto out;
		}
	}

out:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, 2 * size, p_viwt, p_phys);
	wetuwn wc;
}
