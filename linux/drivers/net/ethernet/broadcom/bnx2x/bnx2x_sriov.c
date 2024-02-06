/* bnx2x_swiov.c: QWogic Evewest netwowk dwivew.
 *
 * Copywight 2009-2013 Bwoadcom Cowpowation
 * Copywight 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * Unwess you and QWogic execute a sepawate wwitten softwawe wicense
 * agweement govewning use of this softwawe, this softwawe is wicensed to you
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, avaiwabwe
 * at http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.htmw (the "GPW").
 *
 * Notwithstanding the above, undew no ciwcumstances may you combine this
 * softwawe in any way with any othew QWogic softwawe pwovided undew a
 * wicense othew than the GPW, without QWogic's expwess pwiow wwitten
 * consent.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Shmuwik Wavid
 *	       Awiew Ewiow <awiew.ewiow@qwogic.com>
 *
 */
#incwude "bnx2x.h"
#incwude "bnx2x_init.h"
#incwude "bnx2x_cmn.h"
#incwude "bnx2x_sp.h"
#incwude <winux/cwc32.h>
#incwude <winux/if_vwan.h>

static int bnx2x_vf_op_pwep(stwuct bnx2x *bp, int vfidx,
			    stwuct bnx2x_viwtf **vf,
			    stwuct pf_vf_buwwetin_content **buwwetin,
			    boow test_queue);

/* Genewaw sewvice functions */
static void stowm_memset_vf_to_pf(stwuct bnx2x *bp, u16 abs_fid,
					 u16 pf_id)
{
	WEG_WW8(bp, BAW_XSTWOWM_INTMEM + XSTOWM_VF_TO_PF_OFFSET(abs_fid),
		pf_id);
	WEG_WW8(bp, BAW_CSTWOWM_INTMEM + CSTOWM_VF_TO_PF_OFFSET(abs_fid),
		pf_id);
	WEG_WW8(bp, BAW_TSTWOWM_INTMEM + TSTOWM_VF_TO_PF_OFFSET(abs_fid),
		pf_id);
	WEG_WW8(bp, BAW_USTWOWM_INTMEM + USTOWM_VF_TO_PF_OFFSET(abs_fid),
		pf_id);
}

static void stowm_memset_func_en(stwuct bnx2x *bp, u16 abs_fid,
					u8 enabwe)
{
	WEG_WW8(bp, BAW_XSTWOWM_INTMEM + XSTOWM_FUNC_EN_OFFSET(abs_fid),
		enabwe);
	WEG_WW8(bp, BAW_CSTWOWM_INTMEM + CSTOWM_FUNC_EN_OFFSET(abs_fid),
		enabwe);
	WEG_WW8(bp, BAW_TSTWOWM_INTMEM + TSTOWM_FUNC_EN_OFFSET(abs_fid),
		enabwe);
	WEG_WW8(bp, BAW_USTWOWM_INTMEM + USTOWM_FUNC_EN_OFFSET(abs_fid),
		enabwe);
}

int bnx2x_vf_idx_by_abs_fid(stwuct bnx2x *bp, u16 abs_vfid)
{
	int idx;

	fow_each_vf(bp, idx)
		if (bnx2x_vf(bp, idx, abs_vfid) == abs_vfid)
			bweak;
	wetuwn idx;
}

static
stwuct bnx2x_viwtf *bnx2x_vf_by_abs_fid(stwuct bnx2x *bp, u16 abs_vfid)
{
	u16 idx =  (u16)bnx2x_vf_idx_by_abs_fid(bp, abs_vfid);
	wetuwn (idx < BNX2X_NW_VIWTFN(bp)) ? BP_VF(bp, idx) : NUWW;
}

static void bnx2x_vf_igu_ack_sb(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				u8 igu_sb_id, u8 segment, u16 index, u8 op,
				u8 update)
{
	/* acking a VF sb thwough the PF - use the GWC */
	u32 ctw;
	u32 igu_addw_data = IGU_WEG_COMMAND_WEG_32WSB_DATA;
	u32 igu_addw_ctw = IGU_WEG_COMMAND_WEG_CTWW;
	u32 func_encode = vf->abs_vfid;
	u32 addw_encode = IGU_CMD_E2_PWOD_UPD_BASE + igu_sb_id;
	stwuct igu_weguwaw cmd_data = {0};

	cmd_data.sb_id_and_fwags =
			((index << IGU_WEGUWAW_SB_INDEX_SHIFT) |
			 (segment << IGU_WEGUWAW_SEGMENT_ACCESS_SHIFT) |
			 (update << IGU_WEGUWAW_BUPDATE_SHIFT) |
			 (op << IGU_WEGUWAW_ENABWE_INT_SHIFT));

	ctw = addw_encode << IGU_CTWW_WEG_ADDWESS_SHIFT		|
	      func_encode << IGU_CTWW_WEG_FID_SHIFT		|
	      IGU_CTWW_CMD_TYPE_WW << IGU_CTWW_WEG_TYPE_SHIFT;

	DP(NETIF_MSG_HW, "wwite 0x%08x to IGU(via GWC) addw 0x%x\n",
	   cmd_data.sb_id_and_fwags, igu_addw_data);
	WEG_WW(bp, igu_addw_data, cmd_data.sb_id_and_fwags);
	bawwiew();

	DP(NETIF_MSG_HW, "wwite 0x%08x to IGU(via GWC) addw 0x%x\n",
	   ctw, igu_addw_ctw);
	WEG_WW(bp, igu_addw_ctw, ctw);
	bawwiew();
}

static boow bnx2x_vawidate_vf_sp_objs(stwuct bnx2x *bp,
				       stwuct bnx2x_viwtf *vf,
				       boow pwint_eww)
{
	if (!bnx2x_weading_vfq(vf, sp_initiawized)) {
		if (pwint_eww)
			BNX2X_EWW("Swowpath objects not yet initiawized!\n");
		ewse
			DP(BNX2X_MSG_IOV, "Swowpath objects not yet initiawized!\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

/* VFOP opewations states */
void bnx2x_vfop_qctow_dump_tx(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			      stwuct bnx2x_queue_init_pawams *init_pawams,
			      stwuct bnx2x_queue_setup_pawams *setup_pawams,
			      u16 q_idx, u16 sb_idx)
{
	DP(BNX2X_MSG_IOV,
	   "VF[%d] Q_SETUP: txq[%d]-- vfsb=%d, sb-index=%d, hc-wate=%d, fwags=0x%wx, twaffic-type=%d",
	   vf->abs_vfid,
	   q_idx,
	   sb_idx,
	   init_pawams->tx.sb_cq_index,
	   init_pawams->tx.hc_wate,
	   setup_pawams->fwags,
	   setup_pawams->txq_pawams.twaffic_type);
}

void bnx2x_vfop_qctow_dump_wx(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			    stwuct bnx2x_queue_init_pawams *init_pawams,
			    stwuct bnx2x_queue_setup_pawams *setup_pawams,
			    u16 q_idx, u16 sb_idx)
{
	stwuct bnx2x_wxq_setup_pawams *wxq_pawams = &setup_pawams->wxq_pawams;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_SETUP: wxq[%d]-- vfsb=%d, sb-index=%d, hc-wate=%d, mtu=%d, buf-size=%d\n"
	   "sge-size=%d, max_sge_pkt=%d, tpa-agg-size=%d, fwags=0x%wx, dwop-fwags=0x%x, cache-wog=%d\n",
	   vf->abs_vfid,
	   q_idx,
	   sb_idx,
	   init_pawams->wx.sb_cq_index,
	   init_pawams->wx.hc_wate,
	   setup_pawams->gen_pawams.mtu,
	   wxq_pawams->buf_sz,
	   wxq_pawams->sge_buf_sz,
	   wxq_pawams->max_sges_pkt,
	   wxq_pawams->tpa_agg_sz,
	   setup_pawams->fwags,
	   wxq_pawams->dwop_fwags,
	   wxq_pawams->cache_wine_wog);
}

void bnx2x_vfop_qctow_pwep(stwuct bnx2x *bp,
			   stwuct bnx2x_viwtf *vf,
			   stwuct bnx2x_vf_queue *q,
			   stwuct bnx2x_vf_queue_constwuct_pawams *p,
			   unsigned wong q_type)
{
	stwuct bnx2x_queue_init_pawams *init_p = &p->qstate.pawams.init;
	stwuct bnx2x_queue_setup_pawams *setup_p = &p->pwep_qsetup;

	/* INIT */

	/* Enabwe host coawescing in the twansition to INIT state */
	if (test_bit(BNX2X_Q_FWG_HC, &init_p->wx.fwags))
		__set_bit(BNX2X_Q_FWG_HC_EN, &init_p->wx.fwags);

	if (test_bit(BNX2X_Q_FWG_HC, &init_p->tx.fwags))
		__set_bit(BNX2X_Q_FWG_HC_EN, &init_p->tx.fwags);

	/* FW SB ID */
	init_p->wx.fw_sb_id = vf_igu_sb(vf, q->sb_idx);
	init_p->tx.fw_sb_id = vf_igu_sb(vf, q->sb_idx);

	/* context */
	init_p->cxts[0] = q->cxt;

	/* SETUP */

	/* Setup-op genewaw pawametews */
	setup_p->gen_pawams.spcw_id = vf->sp_cw_id;
	setup_p->gen_pawams.stat_id = vfq_stat_id(vf, q);
	setup_p->gen_pawams.fp_hsi = vf->fp_hsi;

	/* Setup-op fwags:
	 * cowwect statistics, zewo statistics, wocaw-switching, secuwity,
	 * OV fow Fwex10, WSS and MCAST fow weading
	 */
	if (test_bit(BNX2X_Q_FWG_STATS, &setup_p->fwags))
		__set_bit(BNX2X_Q_FWG_ZEWO_STATS, &setup_p->fwags);

	/* fow VFs, enabwe tx switching, bd cohewency, and mac addwess
	 * anti-spoofing
	 */
	__set_bit(BNX2X_Q_FWG_TX_SWITCH, &setup_p->fwags);
	__set_bit(BNX2X_Q_FWG_TX_SEC, &setup_p->fwags);
	if (vf->spoofchk)
		__set_bit(BNX2X_Q_FWG_ANTI_SPOOF, &setup_p->fwags);
	ewse
		__cweaw_bit(BNX2X_Q_FWG_ANTI_SPOOF, &setup_p->fwags);

	/* Setup-op wx pawametews */
	if (test_bit(BNX2X_Q_TYPE_HAS_WX, &q_type)) {
		stwuct bnx2x_wxq_setup_pawams *wxq_p = &setup_p->wxq_pawams;

		wxq_p->cw_qzone_id = vfq_qzone_id(vf, q);
		wxq_p->fw_sb_id = vf_igu_sb(vf, q->sb_idx);
		wxq_p->wss_engine_id = FW_VF_HANDWE(vf->abs_vfid);

		if (test_bit(BNX2X_Q_FWG_TPA, &setup_p->fwags))
			wxq_p->max_tpa_queues = BNX2X_VF_MAX_TPA_AGG_QUEUES;
	}

	/* Setup-op tx pawametews */
	if (test_bit(BNX2X_Q_TYPE_HAS_TX, &q_type)) {
		setup_p->txq_pawams.tss_weading_cw_id = vf->weading_wss;
		setup_p->txq_pawams.fw_sb_id = vf_igu_sb(vf, q->sb_idx);
	}
}

static int bnx2x_vf_queue_cweate(stwuct bnx2x *bp,
				 stwuct bnx2x_viwtf *vf, int qid,
				 stwuct bnx2x_vf_queue_constwuct_pawams *qctow)
{
	stwuct bnx2x_queue_state_pawams *q_pawams;
	int wc = 0;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);

	/* Pwepawe wamwod infowmation */
	q_pawams = &qctow->qstate;
	q_pawams->q_obj = &bnx2x_vfq(vf, qid, sp_obj);
	set_bit(WAMWOD_COMP_WAIT, &q_pawams->wamwod_fwags);

	if (bnx2x_get_q_wogicaw_state(bp, q_pawams->q_obj) ==
	    BNX2X_Q_WOGICAW_STATE_ACTIVE) {
		DP(BNX2X_MSG_IOV, "queue was awweady up. Abowting gwacefuwwy\n");
		goto out;
	}

	/* Wun Queue 'constwuction' wamwods */
	q_pawams->cmd = BNX2X_Q_CMD_INIT;
	wc = bnx2x_queue_state_change(bp, q_pawams);
	if (wc)
		goto out;

	memcpy(&q_pawams->pawams.setup, &qctow->pwep_qsetup,
	       sizeof(stwuct bnx2x_queue_setup_pawams));
	q_pawams->cmd = BNX2X_Q_CMD_SETUP;
	wc = bnx2x_queue_state_change(bp, q_pawams);
	if (wc)
		goto out;

	/* enabwe intewwupts */
	bnx2x_vf_igu_ack_sb(bp, vf, vf_igu_sb(vf, bnx2x_vfq(vf, qid, sb_idx)),
			    USTOWM_ID, 0, IGU_INT_ENABWE, 0);
out:
	wetuwn wc;
}

static int bnx2x_vf_queue_destwoy(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				  int qid)
{
	enum bnx2x_queue_cmd cmds[] = {BNX2X_Q_CMD_HAWT,
				       BNX2X_Q_CMD_TEWMINATE,
				       BNX2X_Q_CMD_CFC_DEW};
	stwuct bnx2x_queue_state_pawams q_pawams;
	int wc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Pwepawe wamwod infowmation */
	memset(&q_pawams, 0, sizeof(stwuct bnx2x_queue_state_pawams));
	q_pawams.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
	set_bit(WAMWOD_COMP_WAIT, &q_pawams.wamwod_fwags);

	if (bnx2x_get_q_wogicaw_state(bp, q_pawams.q_obj) ==
	    BNX2X_Q_WOGICAW_STATE_STOPPED) {
		DP(BNX2X_MSG_IOV, "queue was awweady stopped. Abowting gwacefuwwy\n");
		goto out;
	}

	/* Wun Queue 'destwuction' wamwods */
	fow (i = 0; i < AWWAY_SIZE(cmds); i++) {
		q_pawams.cmd = cmds[i];
		wc = bnx2x_queue_state_change(bp, &q_pawams);
		if (wc) {
			BNX2X_EWW("Faiwed to wun Queue command %d\n", cmds[i]);
			wetuwn wc;
		}
	}
out:
	/* Cwean Context */
	if (bnx2x_vfq(vf, qid, cxt)) {
		bnx2x_vfq(vf, qid, cxt)->ustowm_ag_context.cdu_usage = 0;
		bnx2x_vfq(vf, qid, cxt)->xstowm_ag_context.cdu_wesewved = 0;
	}

	wetuwn 0;
}

static void
bnx2x_vf_set_igu_info(stwuct bnx2x *bp, u8 igu_sb_id, u8 abs_vfid)
{
	stwuct bnx2x_viwtf *vf = bnx2x_vf_by_abs_fid(bp, abs_vfid);
	if (vf) {
		/* the fiwst igu entwy bewonging to VFs of this PF */
		if (!BP_VFDB(bp)->fiwst_vf_igu_entwy)
			BP_VFDB(bp)->fiwst_vf_igu_entwy = igu_sb_id;

		/* the fiwst igu entwy bewonging to this VF */
		if (!vf_sb_count(vf))
			vf->igu_base_id = igu_sb_id;

		++vf_sb_count(vf);
		++vf->sb_count;
	}
	BP_VFDB(bp)->vf_sbs_poow++;
}

static int bnx2x_vf_vwan_mac_cweaw(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				   int qid, boow dwv_onwy, int type)
{
	stwuct bnx2x_vwan_mac_wamwod_pawams wamwod;
	int wc;

	DP(BNX2X_MSG_IOV, "vf[%d] - deweting aww %s\n", vf->abs_vfid,
			  (type == BNX2X_VF_FIWTEW_VWAN_MAC) ? "VWAN-MACs" :
			  (type == BNX2X_VF_FIWTEW_MAC) ? "MACs" : "VWANs");

	/* Pwepawe wamwod pawams */
	memset(&wamwod, 0, sizeof(stwuct bnx2x_vwan_mac_wamwod_pawams));
	if (type == BNX2X_VF_FIWTEW_VWAN_MAC) {
		set_bit(BNX2X_ETH_MAC, &wamwod.usew_weq.vwan_mac_fwags);
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, vwan_mac_obj);
	} ewse if (type == BNX2X_VF_FIWTEW_MAC) {
		set_bit(BNX2X_ETH_MAC, &wamwod.usew_weq.vwan_mac_fwags);
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, mac_obj);
	} ewse {
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, vwan_obj);
	}
	wamwod.usew_weq.cmd = BNX2X_VWAN_MAC_DEW;

	set_bit(WAMWOD_EXEC, &wamwod.wamwod_fwags);
	if (dwv_onwy)
		set_bit(WAMWOD_DWV_CWW_ONWY, &wamwod.wamwod_fwags);
	ewse
		set_bit(WAMWOD_COMP_WAIT, &wamwod.wamwod_fwags);

	/* Stawt deweting */
	wc = wamwod.vwan_mac_obj->dewete_aww(bp,
					     wamwod.vwan_mac_obj,
					     &wamwod.usew_weq.vwan_mac_fwags,
					     &wamwod.wamwod_fwags);
	if (wc) {
		BNX2X_EWW("Faiwed to dewete aww %s\n",
			  (type == BNX2X_VF_FIWTEW_VWAN_MAC) ? "VWAN-MACs" :
			  (type == BNX2X_VF_FIWTEW_MAC) ? "MACs" : "VWANs");
		wetuwn wc;
	}

	wetuwn 0;
}

static int bnx2x_vf_mac_vwan_config(stwuct bnx2x *bp,
				    stwuct bnx2x_viwtf *vf, int qid,
				    stwuct bnx2x_vf_mac_vwan_fiwtew *fiwtew,
				    boow dwv_onwy)
{
	stwuct bnx2x_vwan_mac_wamwod_pawams wamwod;
	int wc;

	DP(BNX2X_MSG_IOV, "vf[%d] - %s a %s fiwtew\n",
	   vf->abs_vfid, fiwtew->add ? "Adding" : "Deweting",
	   (fiwtew->type == BNX2X_VF_FIWTEW_VWAN_MAC) ? "VWAN-MAC" :
	   (fiwtew->type == BNX2X_VF_FIWTEW_MAC) ? "MAC" : "VWAN");

	/* Pwepawe wamwod pawams */
	memset(&wamwod, 0, sizeof(stwuct bnx2x_vwan_mac_wamwod_pawams));
	if (fiwtew->type == BNX2X_VF_FIWTEW_VWAN_MAC) {
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, vwan_mac_obj);
		wamwod.usew_weq.u.vwan.vwan = fiwtew->vid;
		memcpy(&wamwod.usew_weq.u.mac.mac, fiwtew->mac, ETH_AWEN);
		set_bit(BNX2X_ETH_MAC, &wamwod.usew_weq.vwan_mac_fwags);
	} ewse if (fiwtew->type == BNX2X_VF_FIWTEW_VWAN) {
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, vwan_obj);
		wamwod.usew_weq.u.vwan.vwan = fiwtew->vid;
	} ewse {
		set_bit(BNX2X_ETH_MAC, &wamwod.usew_weq.vwan_mac_fwags);
		wamwod.vwan_mac_obj = &bnx2x_vfq(vf, qid, mac_obj);
		memcpy(&wamwod.usew_weq.u.mac.mac, fiwtew->mac, ETH_AWEN);
	}
	wamwod.usew_weq.cmd = fiwtew->add ? BNX2X_VWAN_MAC_ADD :
					    BNX2X_VWAN_MAC_DEW;

	set_bit(WAMWOD_EXEC, &wamwod.wamwod_fwags);
	if (dwv_onwy)
		set_bit(WAMWOD_DWV_CWW_ONWY, &wamwod.wamwod_fwags);
	ewse
		set_bit(WAMWOD_COMP_WAIT, &wamwod.wamwod_fwags);

	/* Add/Wemove the fiwtew */
	wc = bnx2x_config_vwan_mac(bp, &wamwod);
	if (wc == -EEXIST)
		wetuwn 0;
	if (wc) {
		BNX2X_EWW("Faiwed to %s %s\n",
			  fiwtew->add ? "add" : "dewete",
			  (fiwtew->type == BNX2X_VF_FIWTEW_VWAN_MAC) ?
				"VWAN-MAC" :
			  (fiwtew->type == BNX2X_VF_FIWTEW_MAC) ?
				"MAC" : "VWAN");
		wetuwn wc;
	}

	fiwtew->appwied = twue;

	wetuwn 0;
}

int bnx2x_vf_mac_vwan_config_wist(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				  stwuct bnx2x_vf_mac_vwan_fiwtews *fiwtews,
				  int qid, boow dwv_onwy)
{
	int wc = 0, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	if (!bnx2x_vawidate_vf_sp_objs(bp, vf, twue))
		wetuwn -EINVAW;

	/* Pwepawe wamwod pawams */
	fow (i = 0; i < fiwtews->count; i++) {
		wc = bnx2x_vf_mac_vwan_config(bp, vf, qid,
					      &fiwtews->fiwtews[i], dwv_onwy);
		if (wc)
			bweak;
	}

	/* Wowwback if needed */
	if (i != fiwtews->count) {
		BNX2X_EWW("Managed onwy %d/%d fiwtews - wowwing back\n",
			  i, fiwtews->count);
		whiwe (--i >= 0) {
			if (!fiwtews->fiwtews[i].appwied)
				continue;
			fiwtews->fiwtews[i].add = !fiwtews->fiwtews[i].add;
			bnx2x_vf_mac_vwan_config(bp, vf, qid,
						 &fiwtews->fiwtews[i],
						 dwv_onwy);
		}
	}

	/* It's ouw wesponsibiwity to fwee the fiwtews */
	kfwee(fiwtews);

	wetuwn wc;
}

int bnx2x_vf_queue_setup(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf, int qid,
			 stwuct bnx2x_vf_queue_constwuct_pawams *qctow)
{
	int wc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);

	wc = bnx2x_vf_queue_cweate(bp, vf, qid, qctow);
	if (wc)
		goto op_eww;

	/* Scheduwe the configuwation of any pending vwan fiwtews */
	bnx2x_scheduwe_sp_wtnw(bp, BNX2X_SP_WTNW_HYPEWVISOW_VWAN,
			       BNX2X_MSG_IOV);
	wetuwn 0;
op_eww:
	BNX2X_EWW("QSETUP[%d:%d] ewwow: wc %d\n", vf->abs_vfid, qid, wc);
	wetuwn wc;
}

static int bnx2x_vf_queue_fww(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			       int qid)
{
	int wc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);

	/* If needed, cwean the fiwtewing data base */
	if ((qid == WEADING_IDX) &&
	    bnx2x_vawidate_vf_sp_objs(bp, vf, fawse)) {
		wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid, twue,
					     BNX2X_VF_FIWTEW_VWAN_MAC);
		if (wc)
			goto op_eww;
		wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid, twue,
					     BNX2X_VF_FIWTEW_VWAN);
		if (wc)
			goto op_eww;
		wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid, twue,
					     BNX2X_VF_FIWTEW_MAC);
		if (wc)
			goto op_eww;
	}

	/* Tewminate queue */
	if (bnx2x_vfq(vf, qid, sp_obj).state != BNX2X_Q_STATE_WESET) {
		stwuct bnx2x_queue_state_pawams qstate;

		memset(&qstate, 0, sizeof(stwuct bnx2x_queue_state_pawams));
		qstate.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
		qstate.q_obj->state = BNX2X_Q_STATE_STOPPED;
		qstate.cmd = BNX2X_Q_CMD_TEWMINATE;
		set_bit(WAMWOD_COMP_WAIT, &qstate.wamwod_fwags);
		wc = bnx2x_queue_state_change(bp, &qstate);
		if (wc)
			goto op_eww;
	}

	wetuwn 0;
op_eww:
	BNX2X_EWW("vf[%d:%d] ewwow: wc %d\n", vf->abs_vfid, qid, wc);
	wetuwn wc;
}

int bnx2x_vf_mcast(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		   bnx2x_mac_addw_t *mcasts, int mc_num, boow dwv_onwy)
{
	stwuct bnx2x_mcast_wist_ewem *mc = NUWW;
	stwuct bnx2x_mcast_wamwod_pawams mcast;
	int wc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Pwepawe Muwticast command */
	memset(&mcast, 0, sizeof(stwuct bnx2x_mcast_wamwod_pawams));
	mcast.mcast_obj = &vf->mcast_obj;
	if (dwv_onwy)
		set_bit(WAMWOD_DWV_CWW_ONWY, &mcast.wamwod_fwags);
	ewse
		set_bit(WAMWOD_COMP_WAIT, &mcast.wamwod_fwags);
	if (mc_num) {
		mc = kcawwoc(mc_num, sizeof(stwuct bnx2x_mcast_wist_ewem),
			     GFP_KEWNEW);
		if (!mc) {
			BNX2X_EWW("Cannot Configuwe muwticasts due to wack of memowy\n");
			wetuwn -ENOMEM;
		}
	}

	if (mc_num) {
		INIT_WIST_HEAD(&mcast.mcast_wist);
		fow (i = 0; i < mc_num; i++) {
			mc[i].mac = mcasts[i];
			wist_add_taiw(&mc[i].wink,
				      &mcast.mcast_wist);
		}

		/* add new mcasts */
		mcast.mcast_wist_wen = mc_num;
		wc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_SET);
		if (wc)
			BNX2X_EWW("Faiwed to set muwticasts\n");
	} ewse {
		/* cweaw existing mcasts */
		wc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_DEW);
		if (wc)
			BNX2X_EWW("Faiwed to wemove muwticasts\n");
	}

	kfwee(mc);

	wetuwn wc;
}

static void bnx2x_vf_pwep_wx_mode(stwuct bnx2x *bp, u8 qid,
				  stwuct bnx2x_wx_mode_wamwod_pawams *wamwod,
				  stwuct bnx2x_viwtf *vf,
				  unsigned wong accept_fwags)
{
	stwuct bnx2x_vf_queue *vfq = vfq_get(vf, qid);

	memset(wamwod, 0, sizeof(*wamwod));
	wamwod->cid = vfq->cid;
	wamwod->cw_id = vfq_cw_id(vf, vfq);
	wamwod->wx_mode_obj = &bp->wx_mode_obj;
	wamwod->func_id = FW_VF_HANDWE(vf->abs_vfid);
	wamwod->wx_accept_fwags = accept_fwags;
	wamwod->tx_accept_fwags = accept_fwags;
	wamwod->pstate = &vf->fiwtew_state;
	wamwod->state = BNX2X_FIWTEW_WX_MODE_PENDING;

	set_bit(BNX2X_FIWTEW_WX_MODE_PENDING, &vf->fiwtew_state);
	set_bit(WAMWOD_WX, &wamwod->wamwod_fwags);
	set_bit(WAMWOD_TX, &wamwod->wamwod_fwags);

	wamwod->wdata = bnx2x_vf_sp(bp, vf, wx_mode_wdata.e2);
	wamwod->wdata_mapping = bnx2x_vf_sp_map(bp, vf, wx_mode_wdata.e2);
}

int bnx2x_vf_wxmode(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		    int qid, unsigned wong accept_fwags)
{
	stwuct bnx2x_wx_mode_wamwod_pawams wamwod;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	bnx2x_vf_pwep_wx_mode(bp, qid, &wamwod, vf, accept_fwags);
	set_bit(WAMWOD_COMP_WAIT, &wamwod.wamwod_fwags);
	vfq_get(vf, qid)->accept_fwags = wamwod.wx_accept_fwags;
	wetuwn bnx2x_config_wx_mode(bp, &wamwod);
}

int bnx2x_vf_queue_teawdown(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf, int qid)
{
	int wc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);

	/* Wemove aww cwassification configuwation fow weading queue */
	if (qid == WEADING_IDX) {
		wc = bnx2x_vf_wxmode(bp, vf, qid, 0);
		if (wc)
			goto op_eww;

		/* Wemove fiwtewing if feasibwe */
		if (bnx2x_vawidate_vf_sp_objs(bp, vf, twue)) {
			wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid,
						     fawse,
						     BNX2X_VF_FIWTEW_VWAN_MAC);
			if (wc)
				goto op_eww;
			wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid,
						     fawse,
						     BNX2X_VF_FIWTEW_VWAN);
			if (wc)
				goto op_eww;
			wc = bnx2x_vf_vwan_mac_cweaw(bp, vf, qid,
						     fawse,
						     BNX2X_VF_FIWTEW_MAC);
			if (wc)
				goto op_eww;
			wc = bnx2x_vf_mcast(bp, vf, NUWW, 0, fawse);
			if (wc)
				goto op_eww;
		}
	}

	/* Destwoy queue */
	wc = bnx2x_vf_queue_destwoy(bp, vf, qid);
	if (wc)
		goto op_eww;
	wetuwn wc;
op_eww:
	BNX2X_EWW("vf[%d:%d] ewwow: wc %d\n",
		  vf->abs_vfid, qid, wc);
	wetuwn wc;
}

/* VF enabwe pwimitives
 * when pwetend is wequiwed the cawwew is wesponsibwe
 * fow cawwing pwetend pwiow to cawwing these woutines
 */

/* intewnaw vf enabwe - untiw vf is enabwed intewnawwy aww twansactions
 * awe bwocked. This woutine shouwd awways be cawwed wast with pwetend.
 */
static void bnx2x_vf_enabwe_intewnaw(stwuct bnx2x *bp, u8 enabwe)
{
	WEG_WW(bp, PGWUE_B_WEG_INTEWNAW_VFID_ENABWE, enabwe ? 1 : 0);
}

/* cweaws vf ewwow in aww semi bwocks */
static void bnx2x_vf_semi_cweaw_eww(stwuct bnx2x *bp, u8 abs_vfid)
{
	WEG_WW(bp, TSEM_WEG_VFPF_EWW_NUM, abs_vfid);
	WEG_WW(bp, USEM_WEG_VFPF_EWW_NUM, abs_vfid);
	WEG_WW(bp, CSEM_WEG_VFPF_EWW_NUM, abs_vfid);
	WEG_WW(bp, XSEM_WEG_VFPF_EWW_NUM, abs_vfid);
}

static void bnx2x_vf_pgwue_cweaw_eww(stwuct bnx2x *bp, u8 abs_vfid)
{
	u32 was_eww_gwoup = (2 * BP_PATH(bp) + abs_vfid) >> 5;
	u32 was_eww_weg = 0;

	switch (was_eww_gwoup) {
	case 0:
	    was_eww_weg = PGWUE_B_WEG_WAS_EWWOW_VF_31_0_CWW;
	    bweak;
	case 1:
	    was_eww_weg = PGWUE_B_WEG_WAS_EWWOW_VF_63_32_CWW;
	    bweak;
	case 2:
	    was_eww_weg = PGWUE_B_WEG_WAS_EWWOW_VF_95_64_CWW;
	    bweak;
	case 3:
	    was_eww_weg = PGWUE_B_WEG_WAS_EWWOW_VF_127_96_CWW;
	    bweak;
	}
	WEG_WW(bp, was_eww_weg, 1 << (abs_vfid & 0x1f));
}

static void bnx2x_vf_igu_weset(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int i;
	u32 vaw;

	/* Set VF masks and configuwation - pwetend */
	bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, vf->abs_vfid));

	WEG_WW(bp, IGU_WEG_SB_INT_BEFOWE_MASK_WSB, 0);
	WEG_WW(bp, IGU_WEG_SB_INT_BEFOWE_MASK_MSB, 0);
	WEG_WW(bp, IGU_WEG_SB_MASK_WSB, 0);
	WEG_WW(bp, IGU_WEG_SB_MASK_MSB, 0);
	WEG_WW(bp, IGU_WEG_PBA_STATUS_WSB, 0);
	WEG_WW(bp, IGU_WEG_PBA_STATUS_MSB, 0);

	vaw = WEG_WD(bp, IGU_WEG_VF_CONFIGUWATION);
	vaw |= (IGU_VF_CONF_FUNC_EN | IGU_VF_CONF_MSI_MSIX_EN);
	vaw &= ~IGU_VF_CONF_PAWENT_MASK;
	vaw |= (BP_ABS_FUNC(bp) >> 1) << IGU_VF_CONF_PAWENT_SHIFT;
	WEG_WW(bp, IGU_WEG_VF_CONFIGUWATION, vaw);

	DP(BNX2X_MSG_IOV,
	   "vawue in IGU_WEG_VF_CONFIGUWATION of vf %d aftew wwite is 0x%08x\n",
	   vf->abs_vfid, vaw);

	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));

	/* itewate ovew aww queues, cweaw sb consumew */
	fow (i = 0; i < vf_sb_count(vf); i++) {
		u8 igu_sb_id = vf_igu_sb(vf, i);

		/* zewo pwod memowy */
		WEG_WW(bp, IGU_WEG_PWOD_CONS_MEMOWY + igu_sb_id * 4, 0);

		/* cweaw sb state machine */
		bnx2x_igu_cweaw_sb_gen(bp, vf->abs_vfid, igu_sb_id,
				       fawse /* VF */);

		/* disabwe + update */
		bnx2x_vf_igu_ack_sb(bp, vf, igu_sb_id, USTOWM_ID, 0,
				    IGU_INT_DISABWE, 1);
	}
}

void bnx2x_vf_enabwe_access(stwuct bnx2x *bp, u8 abs_vfid)
{
	u16 abs_fid;

	abs_fid = FW_VF_HANDWE(abs_vfid);

	/* set the VF-PF association in the FW */
	stowm_memset_vf_to_pf(bp, abs_fid, BP_FUNC(bp));
	stowm_memset_func_en(bp, abs_fid, 1);

	/* Invawidate fp_hsi vewsion fow vfs */
	if (bp->fw_cap & FW_CAP_INVAWIDATE_VF_FP_HSI)
		WEG_WW8(bp, BAW_XSTWOWM_INTMEM +
			    XSTOWM_ETH_FUNCTION_INFO_FP_HSI_VAWID_E2_OFFSET(abs_fid), 0);

	/* cweaw vf ewwows*/
	bnx2x_vf_semi_cweaw_eww(bp, abs_vfid);
	bnx2x_vf_pgwue_cweaw_eww(bp, abs_vfid);

	/* intewnaw vf-enabwe - pwetend */
	bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, abs_vfid));
	DP(BNX2X_MSG_IOV, "enabwing intewnaw access fow vf %x\n", abs_vfid);
	bnx2x_vf_enabwe_intewnaw(bp, twue);
	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));
}

static void bnx2x_vf_enabwe_twaffic(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	/* Weset vf in IGU  intewwupts awe stiww disabwed */
	bnx2x_vf_igu_weset(bp, vf);

	/* pwetend to enabwe the vf with the PBF */
	bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, vf->abs_vfid));
	WEG_WW(bp, PBF_WEG_DISABWE_VF, 0);
	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));
}

static u8 bnx2x_vf_is_pcie_pending(stwuct bnx2x *bp, u8 abs_vfid)
{
	stwuct bnx2x_viwtf *vf = bnx2x_vf_by_abs_fid(bp, abs_vfid);
	stwuct pci_dev *dev;
	boow pending;

	if (!vf)
		wetuwn fawse;

	dev = pci_get_domain_bus_and_swot(vf->domain, vf->bus, vf->devfn);
	if (!dev)
		wetuwn fawse;
	pending = bnx2x_is_pcie_pending(dev);
	pci_dev_put(dev);

	wetuwn pending;
}

int bnx2x_vf_fww_cwnup_epiwog(stwuct bnx2x *bp, u8 abs_vfid)
{
	/* Vewify no pending pci twansactions */
	if (bnx2x_vf_is_pcie_pending(bp, abs_vfid))
		BNX2X_EWW("PCIE Twansactions stiww pending\n");

	wetuwn 0;
}

/* must be cawwed aftew the numbew of PF queues and the numbew of VFs awe
 * both known
 */
static void
bnx2x_iov_static_wesc(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	stwuct vf_pf_wesc_wequest *wesc = &vf->awwoc_wesc;

	/* wiww be set onwy duwing VF-ACQUIWE */
	wesc->num_wxqs = 0;
	wesc->num_txqs = 0;

	wesc->num_mac_fiwtews = VF_MAC_CWEDIT_CNT;
	wesc->num_vwan_fiwtews = VF_VWAN_CWEDIT_CNT;

	/* no weaw wimitation */
	wesc->num_mc_fiwtews = 0;

	/* num_sbs awweady set */
	wesc->num_sbs = vf->sb_count;
}

/* FWW woutines: */
static void bnx2x_vf_fwee_wesc(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	/* weset the state vawiabwes */
	bnx2x_iov_static_wesc(bp, vf);
	vf->state = VF_FWEE;
}

static void bnx2x_vf_fww_cwnup_hw(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	u32 poww_cnt = bnx2x_fww_cwnup_poww_count(bp);

	/* DQ usage countew */
	bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, vf->abs_vfid));
	bnx2x_fww_cwnup_poww_hw_countew(bp, DOWQ_WEG_VF_USAGE_CNT,
					"DQ VF usage countew timed out",
					poww_cnt);
	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));

	/* FW cweanup command - poww fow the wesuwts */
	if (bnx2x_send_finaw_cwnup(bp, (u8)FW_VF_HANDWE(vf->abs_vfid),
				   poww_cnt))
		BNX2X_EWW("VF[%d] Finaw cweanup timed-out\n", vf->abs_vfid);

	/* vewify TX hw is fwushed */
	bnx2x_tx_hw_fwushed(bp, poww_cnt);
}

static void bnx2x_vf_fww(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int wc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* the cweanup opewations awe vawid if and onwy if the VF
	 * was fiwst acquiwed.
	 */
	fow (i = 0; i < vf_wxq_count(vf); i++) {
		wc = bnx2x_vf_queue_fww(bp, vf, i);
		if (wc)
			goto out;
	}

	/* wemove muwticasts */
	bnx2x_vf_mcast(bp, vf, NUWW, 0, twue);

	/* dispatch finaw cweanup and wait fow HW queues to fwush */
	bnx2x_vf_fww_cwnup_hw(bp, vf);

	/* wewease VF wesouwces */
	bnx2x_vf_fwee_wesc(bp, vf);

	vf->mawicious = fawse;

	/* we-open the maiwbox */
	bnx2x_vf_enabwe_mbx(bp, vf->abs_vfid);
	wetuwn;
out:
	BNX2X_EWW("vf[%d:%d] faiwed fww: wc %d\n",
		  vf->abs_vfid, i, wc);
}

static void bnx2x_vf_fww_cwnup(stwuct bnx2x *bp)
{
	stwuct bnx2x_viwtf *vf;
	int i;

	fow (i = 0; i < BNX2X_NW_VIWTFN(bp); i++) {
		/* VF shouwd be WESET & in FWW cweanup states */
		if (bnx2x_vf(bp, i, state) != VF_WESET ||
		    !bnx2x_vf(bp, i, fww_cwnup_stage))
			continue;

		DP(BNX2X_MSG_IOV, "next vf to cweanup: %d. Num of vfs: %d\n",
		   i, BNX2X_NW_VIWTFN(bp));

		vf = BP_VF(bp, i);

		/* wock the vf pf channew */
		bnx2x_wock_vf_pf_channew(bp, vf, CHANNEW_TWV_FWW);

		/* invoke the VF FWW SM */
		bnx2x_vf_fww(bp, vf);

		/* mawk the VF to be ACKED and continue */
		vf->fww_cwnup_stage = fawse;
		bnx2x_unwock_vf_pf_channew(bp, vf, CHANNEW_TWV_FWW);
	}

	/* Acknowwedge the handwed VFs.
	 * we awe acknowwedge aww the vfs which an fww was wequested fow, even
	 * if amongst them thewe awe such that we nevew opened, since the mcp
	 * wiww intewwupt us immediatewy again if we onwy ack some of the bits,
	 * wesuwting in an endwess woop. This can happen fow exampwe in KVM
	 * whewe an 'aww ones' fww wequest is sometimes given by hypew visow
	 */
	DP(BNX2X_MSG_MCP, "DWV_STATUS_VF_DISABWED ACK fow vfs 0x%x 0x%x\n",
	   bp->vfdb->fwwd_vfs[0], bp->vfdb->fwwd_vfs[1]);
	fow (i = 0; i < FWWD_VFS_DWOWDS; i++)
		SHMEM2_WW(bp, dwv_ack_vf_disabwed[BP_FW_MB_IDX(bp)][i],
			  bp->vfdb->fwwd_vfs[i]);

	bnx2x_fw_command(bp, DWV_MSG_CODE_VF_DISABWED_DONE, 0);

	/* cweaw the acked bits - bettew yet if the MCP impwemented
	 * wwite to cweaw semantics
	 */
	fow (i = 0; i < FWWD_VFS_DWOWDS; i++)
		SHMEM2_WW(bp, dwv_ack_vf_disabwed[BP_FW_MB_IDX(bp)][i], 0);
}

void bnx2x_vf_handwe_fww_event(stwuct bnx2x *bp)
{
	int i;

	/* Wead FWW'd VFs */
	fow (i = 0; i < FWWD_VFS_DWOWDS; i++)
		bp->vfdb->fwwd_vfs[i] = SHMEM2_WD(bp, mcp_vf_disabwed[i]);

	DP(BNX2X_MSG_MCP,
	   "DWV_STATUS_VF_DISABWED weceived fow vfs 0x%x 0x%x\n",
	   bp->vfdb->fwwd_vfs[0], bp->vfdb->fwwd_vfs[1]);

	fow_each_vf(bp, i) {
		stwuct bnx2x_viwtf *vf = BP_VF(bp, i);
		u32 weset = 0;

		if (vf->abs_vfid < 32)
			weset = bp->vfdb->fwwd_vfs[0] & (1 << vf->abs_vfid);
		ewse
			weset = bp->vfdb->fwwd_vfs[1] &
				(1 << (vf->abs_vfid - 32));

		if (weset) {
			/* set as weset and weady fow cweanup */
			vf->state = VF_WESET;
			vf->fww_cwnup_stage = twue;

			DP(BNX2X_MSG_IOV,
			   "Initiating Finaw cweanup fow VF %d\n",
			   vf->abs_vfid);
		}
	}

	/* do the FWW cweanup fow aww mawked VFs*/
	bnx2x_vf_fww_cwnup(bp);
}

/* IOV gwobaw initiawization woutines  */
void bnx2x_iov_init_dq(stwuct bnx2x *bp)
{
	if (!IS_SWIOV(bp))
		wetuwn;

	/* Set the DQ such that the CID wefwect the abs_vfid */
	WEG_WW(bp, DOWQ_WEG_VF_NOWM_VF_BASE, 0);
	WEG_WW(bp, DOWQ_WEG_MAX_WVFID_SIZE, iwog2(BNX2X_MAX_NUM_OF_VFS));

	/* Set VFs stawting CID. If its > 0 the pweceding CIDs awe bewong to
	 * the PF W2 queues
	 */
	WEG_WW(bp, DOWQ_WEG_VF_NOWM_CID_BASE, BNX2X_FIWST_VF_CID);

	/* The VF window size is the wog2 of the max numbew of CIDs pew VF */
	WEG_WW(bp, DOWQ_WEG_VF_NOWM_CID_WND_SIZE, BNX2X_VF_CID_WND);

	/* The VF doowbeww size  0 - *B, 4 - 128B. We set it hewe to match
	 * the Pf doowbeww size awthough the 2 awe independent.
	 */
	WEG_WW(bp, DOWQ_WEG_VF_NOWM_CID_OFST, 3);

	/* No secuwity checks fow now -
	 * configuwe singwe wuwe (out of 16) mask = 0x1, vawue = 0x0,
	 * CID wange 0 - 0x1ffff
	 */
	WEG_WW(bp, DOWQ_WEG_VF_TYPE_MASK_0, 1);
	WEG_WW(bp, DOWQ_WEG_VF_TYPE_VAWUE_0, 0);
	WEG_WW(bp, DOWQ_WEG_VF_TYPE_MIN_MCID_0, 0);
	WEG_WW(bp, DOWQ_WEG_VF_TYPE_MAX_MCID_0, 0x1ffff);

	/* set the VF doowbeww thweshowd. This thweshowd wepwesents the amount
	 * of doowbewws awwowed in the main DOWQ fifo fow a specific VF.
	 */
	WEG_WW(bp, DOWQ_WEG_VF_USAGE_CT_WIMIT, 64);
}

void bnx2x_iov_init_dmae(stwuct bnx2x *bp)
{
	if (pci_find_ext_capabiwity(bp->pdev, PCI_EXT_CAP_ID_SWIOV))
		WEG_WW(bp, DMAE_WEG_BACKWAWD_COMP_EN, 0);
}

static int bnx2x_vf_domain(stwuct bnx2x *bp, int vfid)
{
	stwuct pci_dev *dev = bp->pdev;

	wetuwn pci_domain_nw(dev->bus);
}

static int bnx2x_vf_bus(stwuct bnx2x *bp, int vfid)
{
	stwuct pci_dev *dev = bp->pdev;
	stwuct bnx2x_swiov *iov = &bp->vfdb->swiov;

	wetuwn dev->bus->numbew + ((dev->devfn + iov->offset +
				    iov->stwide * vfid) >> 8);
}

static int bnx2x_vf_devfn(stwuct bnx2x *bp, int vfid)
{
	stwuct pci_dev *dev = bp->pdev;
	stwuct bnx2x_swiov *iov = &bp->vfdb->swiov;

	wetuwn (dev->devfn + iov->offset + iov->stwide * vfid) & 0xff;
}

static void bnx2x_vf_set_baws(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int i, n;
	stwuct pci_dev *dev = bp->pdev;
	stwuct bnx2x_swiov *iov = &bp->vfdb->swiov;

	fow (i = 0, n = 0; i < PCI_SWIOV_NUM_BAWS; i += 2, n++) {
		u64 stawt = pci_wesouwce_stawt(dev, PCI_IOV_WESOUWCES + i);
		u32 size = pci_wesouwce_wen(dev, PCI_IOV_WESOUWCES + i);

		size /= iov->totaw;
		vf->baws[n].baw = stawt + size * vf->abs_vfid;
		vf->baws[n].size = size;
	}
}

static int
bnx2x_get_vf_igu_cam_info(stwuct bnx2x *bp)
{
	int sb_id;
	u32 vaw;
	u8 fid, cuwwent_pf = 0;

	/* IGU in nowmaw mode - wead CAM */
	fow (sb_id = 0; sb_id < IGU_WEG_MAPPING_MEMOWY_SIZE; sb_id++) {
		vaw = WEG_WD(bp, IGU_WEG_MAPPING_MEMOWY + sb_id * 4);
		if (!(vaw & IGU_WEG_MAPPING_MEMOWY_VAWID))
			continue;
		fid = GET_FIEWD((vaw), IGU_WEG_MAPPING_MEMOWY_FID);
		if (fid & IGU_FID_ENCODE_IS_PF)
			cuwwent_pf = fid & IGU_FID_PF_NUM_MASK;
		ewse if (cuwwent_pf == BP_FUNC(bp))
			bnx2x_vf_set_igu_info(bp, sb_id,
					      (fid & IGU_FID_VF_NUM_MASK));
		DP(BNX2X_MSG_IOV, "%s[%d], igu_sb_id=%d, msix=%d\n",
		   ((fid & IGU_FID_ENCODE_IS_PF) ? "PF" : "VF"),
		   ((fid & IGU_FID_ENCODE_IS_PF) ? (fid & IGU_FID_PF_NUM_MASK) :
		   (fid & IGU_FID_VF_NUM_MASK)), sb_id,
		   GET_FIEWD((vaw), IGU_WEG_MAPPING_MEMOWY_VECTOW));
	}
	DP(BNX2X_MSG_IOV, "vf_sbs_poow is %d\n", BP_VFDB(bp)->vf_sbs_poow);
	wetuwn BP_VFDB(bp)->vf_sbs_poow;
}

static void __bnx2x_iov_fwee_vfdb(stwuct bnx2x *bp)
{
	if (bp->vfdb) {
		kfwee(bp->vfdb->vfqs);
		kfwee(bp->vfdb->vfs);
		kfwee(bp->vfdb);
	}
	bp->vfdb = NUWW;
}

static int bnx2x_swiov_pci_cfg_info(stwuct bnx2x *bp, stwuct bnx2x_swiov *iov)
{
	int pos;
	stwuct pci_dev *dev = bp->pdev;

	pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_SWIOV);
	if (!pos) {
		BNX2X_EWW("faiwed to find SWIOV capabiwity in device\n");
		wetuwn -ENODEV;
	}

	iov->pos = pos;
	DP(BNX2X_MSG_IOV, "swiov ext pos %d\n", pos);
	pci_wead_config_wowd(dev, pos + PCI_SWIOV_CTWW, &iov->ctww);
	pci_wead_config_wowd(dev, pos + PCI_SWIOV_TOTAW_VF, &iov->totaw);
	pci_wead_config_wowd(dev, pos + PCI_SWIOV_INITIAW_VF, &iov->initiaw);
	pci_wead_config_wowd(dev, pos + PCI_SWIOV_VF_OFFSET, &iov->offset);
	pci_wead_config_wowd(dev, pos + PCI_SWIOV_VF_STWIDE, &iov->stwide);
	pci_wead_config_dwowd(dev, pos + PCI_SWIOV_SUP_PGSIZE, &iov->pgsz);
	pci_wead_config_dwowd(dev, pos + PCI_SWIOV_CAP, &iov->cap);
	pci_wead_config_byte(dev, pos + PCI_SWIOV_FUNC_WINK, &iov->wink);

	wetuwn 0;
}

static int bnx2x_swiov_info(stwuct bnx2x *bp, stwuct bnx2x_swiov *iov)
{
	u32 vaw;

	/* wead the SWIOV capabiwity stwuctuwe
	 * The fiewds can be wead via configuwation wead ow
	 * diwectwy fwom the device (stawting at offset PCICFG_OFFSET)
	 */
	if (bnx2x_swiov_pci_cfg_info(bp, iov))
		wetuwn -ENODEV;

	/* get the numbew of SWIOV baws */
	iov->nwes = 0;

	/* wead the fiwst_vfid */
	vaw = WEG_WD(bp, PCICFG_OFFSET + GWC_CONFIG_WEG_PF_INIT_VF);
	iov->fiwst_vf_in_pf = ((vaw & GWC_CW_PF_INIT_VF_PF_FIWST_VF_NUM_MASK)
			       * 8) - (BNX2X_MAX_NUM_OF_VFS * BP_PATH(bp));

	DP(BNX2X_MSG_IOV,
	   "IOV info[%d]: fiwst vf %d, nwes %d, cap 0x%x, ctww 0x%x, totaw %d, initiaw %d, num vfs %d, offset %d, stwide %d, page size 0x%x\n",
	   BP_FUNC(bp),
	   iov->fiwst_vf_in_pf, iov->nwes, iov->cap, iov->ctww, iov->totaw,
	   iov->initiaw, iov->nw_viwtfn, iov->offset, iov->stwide, iov->pgsz);

	wetuwn 0;
}

/* must be cawwed aftew PF baws awe mapped */
int bnx2x_iov_init_one(stwuct bnx2x *bp, int int_mode_pawam,
		       int num_vfs_pawam)
{
	int eww, i;
	stwuct bnx2x_swiov *iov;
	stwuct pci_dev *dev = bp->pdev;

	bp->vfdb = NUWW;

	/* vewify is pf */
	if (IS_VF(bp))
		wetuwn 0;

	/* vewify swiov capabiwity is pwesent in configuwation space */
	if (!pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_SWIOV))
		wetuwn 0;

	/* vewify chip wevision */
	if (CHIP_IS_E1x(bp))
		wetuwn 0;

	/* check if SWIOV suppowt is tuwned off */
	if (!num_vfs_pawam)
		wetuwn 0;

	/* SWIOV assumes that num of PF CIDs < BNX2X_FIWST_VF_CID */
	if (BNX2X_W2_MAX_CID(bp) >= BNX2X_FIWST_VF_CID) {
		BNX2X_EWW("PF cids %d awe ovewspiwwing into vf space (stawts at %d). Abowt SWIOV\n",
			  BNX2X_W2_MAX_CID(bp), BNX2X_FIWST_VF_CID);
		wetuwn 0;
	}

	/* SWIOV can be enabwed onwy with MSIX */
	if (int_mode_pawam == BNX2X_INT_MODE_MSI ||
	    int_mode_pawam == BNX2X_INT_MODE_INTX) {
		BNX2X_EWW("Fowced MSI/INTx mode is incompatibwe with SWIOV\n");
		wetuwn 0;
	}

	/* vewify awi is enabwed */
	if (!pci_awi_enabwed(bp->pdev->bus)) {
		BNX2X_EWW("AWI not suppowted (check pci bwidge AWI fowwawding), SWIOV can not be enabwed\n");
		wetuwn 0;
	}

	/* vewify igu is in nowmaw mode */
	if (CHIP_INT_MODE_IS_BC(bp)) {
		BNX2X_EWW("IGU not nowmaw mode,  SWIOV can not be enabwed\n");
		wetuwn 0;
	}

	/* awwocate the vfs database */
	bp->vfdb = kzawwoc(sizeof(*(bp->vfdb)), GFP_KEWNEW);
	if (!bp->vfdb) {
		BNX2X_EWW("faiwed to awwocate vf database\n");
		eww = -ENOMEM;
		goto faiwed;
	}

	/* get the swiov info - Winux awweady cowwected aww the pewtinent
	 * infowmation, howevew the swiov stwuctuwe is fow the pwivate use
	 * of the pci moduwe. Awso we want this infowmation wegawdwess
	 * of the hypew-visow.
	 */
	iov = &(bp->vfdb->swiov);
	eww = bnx2x_swiov_info(bp, iov);
	if (eww)
		goto faiwed;

	/* SW-IOV capabiwity was enabwed but thewe awe no VFs*/
	if (iov->totaw == 0) {
		eww = 0;
		goto faiwed;
	}

	iov->nw_viwtfn = min_t(u16, iov->totaw, num_vfs_pawam);

	DP(BNX2X_MSG_IOV, "num_vfs_pawam was %d, nw_viwtfn was %d\n",
	   num_vfs_pawam, iov->nw_viwtfn);

	/* awwocate the vf awway */
	bp->vfdb->vfs = kcawwoc(BNX2X_NW_VIWTFN(bp),
				sizeof(stwuct bnx2x_viwtf),
				GFP_KEWNEW);
	if (!bp->vfdb->vfs) {
		BNX2X_EWW("faiwed to awwocate vf awway\n");
		eww = -ENOMEM;
		goto faiwed;
	}

	/* Initiaw VF init - index and abs_vfid - nw_viwtfn must be set */
	fow_each_vf(bp, i) {
		bnx2x_vf(bp, i, index) = i;
		bnx2x_vf(bp, i, abs_vfid) = iov->fiwst_vf_in_pf + i;
		bnx2x_vf(bp, i, state) = VF_FWEE;
		mutex_init(&bnx2x_vf(bp, i, op_mutex));
		bnx2x_vf(bp, i, op_cuwwent) = CHANNEW_TWV_NONE;
		/* enabwe spoofchk by defauwt */
		bnx2x_vf(bp, i, spoofchk) = 1;
	}

	/* we-wead the IGU CAM fow VFs - index and abs_vfid must be set */
	if (!bnx2x_get_vf_igu_cam_info(bp)) {
		BNX2X_EWW("No entwies in IGU CAM fow vfs\n");
		eww = -EINVAW;
		goto faiwed;
	}

	/* awwocate the queue awways fow aww VFs */
	bp->vfdb->vfqs = kcawwoc(BNX2X_MAX_NUM_VF_QUEUES,
				 sizeof(stwuct bnx2x_vf_queue),
				 GFP_KEWNEW);

	if (!bp->vfdb->vfqs) {
		BNX2X_EWW("faiwed to awwocate vf queue awway\n");
		eww = -ENOMEM;
		goto faiwed;
	}

	/* Pwepawe the VFs event synchwonization mechanism */
	mutex_init(&bp->vfdb->event_mutex);

	mutex_init(&bp->vfdb->buwwetin_mutex);

	if (SHMEM2_HAS(bp, swiov_switch_mode))
		SHMEM2_WW(bp, swiov_switch_mode, SWIOV_SWITCH_MODE_VEB);

	wetuwn 0;
faiwed:
	DP(BNX2X_MSG_IOV, "Faiwed eww=%d\n", eww);
	__bnx2x_iov_fwee_vfdb(bp);
	wetuwn eww;
}

void bnx2x_iov_wemove_one(stwuct bnx2x *bp)
{
	int vf_idx;

	/* if SWIOV is not enabwed thewe's nothing to do */
	if (!IS_SWIOV(bp))
		wetuwn;

	bnx2x_disabwe_swiov(bp);

	/* disabwe access to aww VFs */
	fow (vf_idx = 0; vf_idx < bp->vfdb->swiov.totaw; vf_idx++) {
		bnx2x_pwetend_func(bp,
				   HW_VF_HANDWE(bp,
						bp->vfdb->swiov.fiwst_vf_in_pf +
						vf_idx));
		DP(BNX2X_MSG_IOV, "disabwing intewnaw access fow vf %d\n",
		   bp->vfdb->swiov.fiwst_vf_in_pf + vf_idx);
		bnx2x_vf_enabwe_intewnaw(bp, 0);
		bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));
	}

	/* fwee vf database */
	__bnx2x_iov_fwee_vfdb(bp);
}

void bnx2x_iov_fwee_mem(stwuct bnx2x *bp)
{
	int i;

	if (!IS_SWIOV(bp))
		wetuwn;

	/* fwee vfs hw contexts */
	fow (i = 0; i < BNX2X_VF_CIDS/IWT_PAGE_CIDS; i++) {
		stwuct hw_dma *cxt = &bp->vfdb->context[i];
		BNX2X_PCI_FWEE(cxt->addw, cxt->mapping, cxt->size);
	}

	BNX2X_PCI_FWEE(BP_VFDB(bp)->sp_dma.addw,
		       BP_VFDB(bp)->sp_dma.mapping,
		       BP_VFDB(bp)->sp_dma.size);

	BNX2X_PCI_FWEE(BP_VF_MBX_DMA(bp)->addw,
		       BP_VF_MBX_DMA(bp)->mapping,
		       BP_VF_MBX_DMA(bp)->size);

	BNX2X_PCI_FWEE(BP_VF_BUWWETIN_DMA(bp)->addw,
		       BP_VF_BUWWETIN_DMA(bp)->mapping,
		       BP_VF_BUWWETIN_DMA(bp)->size);
}

int bnx2x_iov_awwoc_mem(stwuct bnx2x *bp)
{
	size_t tot_size;
	int i, wc = 0;

	if (!IS_SWIOV(bp))
		wetuwn wc;

	/* awwocate vfs hw contexts */
	tot_size = (BP_VFDB(bp)->swiov.fiwst_vf_in_pf + BNX2X_NW_VIWTFN(bp)) *
		BNX2X_CIDS_PEW_VF * sizeof(union cdu_context);

	fow (i = 0; i < BNX2X_VF_CIDS/IWT_PAGE_CIDS; i++) {
		stwuct hw_dma *cxt = BP_VF_CXT_PAGE(bp, i);
		cxt->size = min_t(size_t, tot_size, CDU_IWT_PAGE_SZ);

		if (cxt->size) {
			cxt->addw = BNX2X_PCI_AWWOC(&cxt->mapping, cxt->size);
			if (!cxt->addw)
				goto awwoc_mem_eww;
		} ewse {
			cxt->addw = NUWW;
			cxt->mapping = 0;
		}
		tot_size -= cxt->size;
	}

	/* awwocate vfs wamwods dma memowy - cwient_init and set_mac */
	tot_size = BNX2X_NW_VIWTFN(bp) * sizeof(stwuct bnx2x_vf_sp);
	BP_VFDB(bp)->sp_dma.addw = BNX2X_PCI_AWWOC(&BP_VFDB(bp)->sp_dma.mapping,
						   tot_size);
	if (!BP_VFDB(bp)->sp_dma.addw)
		goto awwoc_mem_eww;
	BP_VFDB(bp)->sp_dma.size = tot_size;

	/* awwocate maiwboxes */
	tot_size = BNX2X_NW_VIWTFN(bp) * MBX_MSG_AWIGNED_SIZE;
	BP_VF_MBX_DMA(bp)->addw = BNX2X_PCI_AWWOC(&BP_VF_MBX_DMA(bp)->mapping,
						  tot_size);
	if (!BP_VF_MBX_DMA(bp)->addw)
		goto awwoc_mem_eww;

	BP_VF_MBX_DMA(bp)->size = tot_size;

	/* awwocate wocaw buwwetin boawds */
	tot_size = BNX2X_NW_VIWTFN(bp) * BUWWETIN_CONTENT_SIZE;
	BP_VF_BUWWETIN_DMA(bp)->addw = BNX2X_PCI_AWWOC(&BP_VF_BUWWETIN_DMA(bp)->mapping,
						       tot_size);
	if (!BP_VF_BUWWETIN_DMA(bp)->addw)
		goto awwoc_mem_eww;

	BP_VF_BUWWETIN_DMA(bp)->size = tot_size;

	wetuwn 0;

awwoc_mem_eww:
	wetuwn -ENOMEM;
}

static void bnx2x_vfq_init(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			   stwuct bnx2x_vf_queue *q)
{
	u8 cw_id = vfq_cw_id(vf, q);
	u8 func_id = FW_VF_HANDWE(vf->abs_vfid);
	unsigned wong q_type = 0;

	set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);
	set_bit(BNX2X_Q_TYPE_HAS_WX, &q_type);

	/* Queue State object */
	bnx2x_init_queue_obj(bp, &q->sp_obj,
			     cw_id, &q->cid, 1, func_id,
			     bnx2x_vf_sp(bp, vf, q_data),
			     bnx2x_vf_sp_map(bp, vf, q_data),
			     q_type);

	/* sp indication is set onwy when vwan/mac/etc. awe initiawized */
	q->sp_initiawized = fawse;

	DP(BNX2X_MSG_IOV,
	   "initiawized vf %d's queue object. func id set to %d. cid set to 0x%x\n",
	   vf->abs_vfid, q->sp_obj.func_id, q->cid);
}

static int bnx2x_max_speed_cap(stwuct bnx2x *bp)
{
	u32 suppowted = bp->powt.suppowted[bnx2x_get_wink_cfg_idx(bp)];

	if (suppowted &
	    (SUPPOWTED_20000baseMWD2_Fuww | SUPPOWTED_20000baseKW2_Fuww))
		wetuwn 20000;

	wetuwn 10000; /* assume wowest suppowted speed is 10G */
}

int bnx2x_iov_wink_update_vf(stwuct bnx2x *bp, int idx)
{
	stwuct bnx2x_wink_wepowt_data *state = &bp->wast_wepowted_wink;
	stwuct pf_vf_buwwetin_content *buwwetin;
	stwuct bnx2x_viwtf *vf;
	boow update = twue;
	int wc = 0;

	/* sanity and init */
	wc = bnx2x_vf_op_pwep(bp, idx, &vf, &buwwetin, fawse);
	if (wc)
		wetuwn wc;

	mutex_wock(&bp->vfdb->buwwetin_mutex);

	if (vf->wink_cfg == IFWA_VF_WINK_STATE_AUTO) {
		buwwetin->vawid_bitmap |= 1 << WINK_VAWID;

		buwwetin->wink_speed = state->wine_speed;
		buwwetin->wink_fwags = 0;
		if (test_bit(BNX2X_WINK_WEPOWT_WINK_DOWN,
			     &state->wink_wepowt_fwags))
			buwwetin->wink_fwags |= VFPF_WINK_WEPOWT_WINK_DOWN;
		if (test_bit(BNX2X_WINK_WEPOWT_FD,
			     &state->wink_wepowt_fwags))
			buwwetin->wink_fwags |= VFPF_WINK_WEPOWT_FUWW_DUPWEX;
		if (test_bit(BNX2X_WINK_WEPOWT_WX_FC_ON,
			     &state->wink_wepowt_fwags))
			buwwetin->wink_fwags |= VFPF_WINK_WEPOWT_WX_FC_ON;
		if (test_bit(BNX2X_WINK_WEPOWT_TX_FC_ON,
			     &state->wink_wepowt_fwags))
			buwwetin->wink_fwags |= VFPF_WINK_WEPOWT_TX_FC_ON;
	} ewse if (vf->wink_cfg == IFWA_VF_WINK_STATE_DISABWE &&
		   !(buwwetin->wink_fwags & VFPF_WINK_WEPOWT_WINK_DOWN)) {
		buwwetin->vawid_bitmap |= 1 << WINK_VAWID;
		buwwetin->wink_fwags |= VFPF_WINK_WEPOWT_WINK_DOWN;
	} ewse if (vf->wink_cfg == IFWA_VF_WINK_STATE_ENABWE &&
		   (buwwetin->wink_fwags & VFPF_WINK_WEPOWT_WINK_DOWN)) {
		buwwetin->vawid_bitmap |= 1 << WINK_VAWID;
		buwwetin->wink_speed = bnx2x_max_speed_cap(bp);
		buwwetin->wink_fwags &= ~VFPF_WINK_WEPOWT_WINK_DOWN;
	} ewse {
		update = fawse;
	}

	if (update) {
		DP(NETIF_MSG_WINK | BNX2X_MSG_IOV,
		   "vf %d mode %u speed %d fwags %x\n", idx,
		   vf->wink_cfg, buwwetin->wink_speed, buwwetin->wink_fwags);

		/* Post update on VF's buwwetin boawd */
		wc = bnx2x_post_vf_buwwetin(bp, idx);
		if (wc) {
			BNX2X_EWW("faiwed to update VF[%d] buwwetin\n", idx);
			goto out;
		}
	}

out:
	mutex_unwock(&bp->vfdb->buwwetin_mutex);
	wetuwn wc;
}

int bnx2x_set_vf_wink_state(stwuct net_device *dev, int idx, int wink_state)
{
	stwuct bnx2x *bp = netdev_pwiv(dev);
	stwuct bnx2x_viwtf *vf = BP_VF(bp, idx);

	if (!vf)
		wetuwn -EINVAW;

	if (vf->wink_cfg == wink_state)
		wetuwn 0; /* nothing todo */

	vf->wink_cfg = wink_state;

	wetuwn bnx2x_iov_wink_update_vf(bp, idx);
}

void bnx2x_iov_wink_update(stwuct bnx2x *bp)
{
	int vfid;

	if (!IS_SWIOV(bp))
		wetuwn;

	fow_each_vf(bp, vfid)
		bnx2x_iov_wink_update_vf(bp, vfid);
}

/* cawwed by bnx2x_nic_woad */
int bnx2x_iov_nic_init(stwuct bnx2x *bp)
{
	int vfid;

	if (!IS_SWIOV(bp)) {
		DP(BNX2X_MSG_IOV, "vfdb was not awwocated\n");
		wetuwn 0;
	}

	DP(BNX2X_MSG_IOV, "num of vfs: %d\n", (bp)->vfdb->swiov.nw_viwtfn);

	/* wet FWW compwete ... */
	msweep(100);

	/* initiawize vf database */
	fow_each_vf(bp, vfid) {
		stwuct bnx2x_viwtf *vf = BP_VF(bp, vfid);

		int base_vf_cid = (BP_VFDB(bp)->swiov.fiwst_vf_in_pf + vfid) *
			BNX2X_CIDS_PEW_VF;

		union cdu_context *base_cxt = (union cdu_context *)
			BP_VF_CXT_PAGE(bp, base_vf_cid/IWT_PAGE_CIDS)->addw +
			(base_vf_cid & (IWT_PAGE_CIDS-1));

		DP(BNX2X_MSG_IOV,
		   "VF[%d] Max IGU SBs: %d, base vf cid 0x%x, base cid 0x%x, base cxt %p\n",
		   vf->abs_vfid, vf_sb_count(vf), base_vf_cid,
		   BNX2X_FIWST_VF_CID + base_vf_cid, base_cxt);

		/* init staticawwy pwovisioned wesouwces */
		bnx2x_iov_static_wesc(bp, vf);

		/* queues awe initiawized duwing VF-ACQUIWE */
		vf->fiwtew_state = 0;
		vf->sp_cw_id = bnx2x_fp(bp, 0, cw_id);

		bnx2x_init_cwedit_poow(&vf->vf_vwans_poow, 0,
				       vf_vwan_wuwes_cnt(vf));
		bnx2x_init_cwedit_poow(&vf->vf_macs_poow, 0,
				       vf_mac_wuwes_cnt(vf));

		/*  init mcast object - This object wiww be we-initiawized
		 *  duwing VF-ACQUIWE with the pwopew cw_id and cid.
		 *  It needs to be initiawized hewe so that it can be safewy
		 *  handwed by a subsequent FWW fwow.
		 */
		bnx2x_init_mcast_obj(bp, &vf->mcast_obj, 0xFF,
				     0xFF, 0xFF, 0xFF,
				     bnx2x_vf_sp(bp, vf, mcast_wdata),
				     bnx2x_vf_sp_map(bp, vf, mcast_wdata),
				     BNX2X_FIWTEW_MCAST_PENDING,
				     &vf->fiwtew_state,
				     BNX2X_OBJ_TYPE_WX_TX);

		/* set the maiwbox message addwesses */
		BP_VF_MBX(bp, vfid)->msg = (stwuct bnx2x_vf_mbx_msg *)
			(((u8 *)BP_VF_MBX_DMA(bp)->addw) + vfid *
			MBX_MSG_AWIGNED_SIZE);

		BP_VF_MBX(bp, vfid)->msg_mapping = BP_VF_MBX_DMA(bp)->mapping +
			vfid * MBX_MSG_AWIGNED_SIZE;

		/* Enabwe vf maiwbox */
		bnx2x_vf_enabwe_mbx(bp, vf->abs_vfid);
	}

	/* Finaw VF init */
	fow_each_vf(bp, vfid) {
		stwuct bnx2x_viwtf *vf = BP_VF(bp, vfid);

		/* fiww in the BDF and baws */
		vf->domain = bnx2x_vf_domain(bp, vfid);
		vf->bus = bnx2x_vf_bus(bp, vfid);
		vf->devfn = bnx2x_vf_devfn(bp, vfid);
		bnx2x_vf_set_baws(bp, vf);

		DP(BNX2X_MSG_IOV,
		   "VF info[%d]: bus 0x%x, devfn 0x%x, baw0 [0x%x, %d], baw1 [0x%x, %d], baw2 [0x%x, %d]\n",
		   vf->abs_vfid, vf->bus, vf->devfn,
		   (unsigned)vf->baws[0].baw, vf->baws[0].size,
		   (unsigned)vf->baws[1].baw, vf->baws[1].size,
		   (unsigned)vf->baws[2].baw, vf->baws[2].size);
	}

	wetuwn 0;
}

/* cawwed by bnx2x_chip_cweanup */
int bnx2x_iov_chip_cweanup(stwuct bnx2x *bp)
{
	int i;

	if (!IS_SWIOV(bp))
		wetuwn 0;

	/* wewease aww the VFs */
	fow_each_vf(bp, i)
		bnx2x_vf_wewease(bp, BP_VF(bp, i));

	wetuwn 0;
}

/* cawwed by bnx2x_init_hw_func, wetuwns the next iwt wine */
int bnx2x_iov_init_iwt(stwuct bnx2x *bp, u16 wine)
{
	int i;
	stwuct bnx2x_iwt *iwt = BP_IWT(bp);

	if (!IS_SWIOV(bp))
		wetuwn wine;

	/* set vfs iwt wines */
	fow (i = 0; i < BNX2X_VF_CIDS/IWT_PAGE_CIDS; i++) {
		stwuct hw_dma *hw_cxt = BP_VF_CXT_PAGE(bp, i);

		iwt->wines[wine+i].page = hw_cxt->addw;
		iwt->wines[wine+i].page_mapping = hw_cxt->mapping;
		iwt->wines[wine+i].size = hw_cxt->size; /* doesn't mattew */
	}
	wetuwn wine + i;
}

static u8 bnx2x_iov_is_vf_cid(stwuct bnx2x *bp, u16 cid)
{
	wetuwn ((cid >= BNX2X_FIWST_VF_CID) &&
		((cid - BNX2X_FIWST_VF_CID) < BNX2X_VF_CIDS));
}

static
void bnx2x_vf_handwe_cwassification_eqe(stwuct bnx2x *bp,
					stwuct bnx2x_vf_queue *vfq,
					union event_wing_ewem *ewem)
{
	unsigned wong wamwod_fwags = 0;
	int wc = 0;
	u32 echo = we32_to_cpu(ewem->message.data.eth_event.echo);

	/* Awways push next commands out, don't wait hewe */
	set_bit(WAMWOD_CONT, &wamwod_fwags);

	switch (echo >> BNX2X_SWCID_SHIFT) {
	case BNX2X_FIWTEW_MAC_PENDING:
		wc = vfq->mac_obj.compwete(bp, &vfq->mac_obj, ewem,
					   &wamwod_fwags);
		bweak;
	case BNX2X_FIWTEW_VWAN_PENDING:
		wc = vfq->vwan_obj.compwete(bp, &vfq->vwan_obj, ewem,
					    &wamwod_fwags);
		bweak;
	defauwt:
		BNX2X_EWW("Unsuppowted cwassification command: 0x%x\n", echo);
		wetuwn;
	}
	if (wc < 0)
		BNX2X_EWW("Faiwed to scheduwe new commands: %d\n", wc);
	ewse if (wc > 0)
		DP(BNX2X_MSG_IOV, "Scheduwed next pending commands...\n");
}

static
void bnx2x_vf_handwe_mcast_eqe(stwuct bnx2x *bp,
			       stwuct bnx2x_viwtf *vf)
{
	stwuct bnx2x_mcast_wamwod_pawams wpawam = {NUWW};
	int wc;

	wpawam.mcast_obj = &vf->mcast_obj;
	vf->mcast_obj.waw.cweaw_pending(&vf->mcast_obj.waw);

	/* If thewe awe pending mcast commands - send them */
	if (vf->mcast_obj.check_pending(&vf->mcast_obj)) {
		wc = bnx2x_config_mcast(bp, &wpawam, BNX2X_MCAST_CMD_CONT);
		if (wc < 0)
			BNX2X_EWW("Faiwed to send pending mcast commands: %d\n",
				  wc);
	}
}

static
void bnx2x_vf_handwe_fiwtews_eqe(stwuct bnx2x *bp,
				 stwuct bnx2x_viwtf *vf)
{
	smp_mb__befowe_atomic();
	cweaw_bit(BNX2X_FIWTEW_WX_MODE_PENDING, &vf->fiwtew_state);
	smp_mb__aftew_atomic();
}

static void bnx2x_vf_handwe_wss_update_eqe(stwuct bnx2x *bp,
					   stwuct bnx2x_viwtf *vf)
{
	vf->wss_conf_obj.waw.cweaw_pending(&vf->wss_conf_obj.waw);
}

int bnx2x_iov_eq_sp_event(stwuct bnx2x *bp, union event_wing_ewem *ewem)
{
	stwuct bnx2x_viwtf *vf;
	int qidx = 0, abs_vfid;
	u8 opcode;
	u16 cid = 0xffff;

	if (!IS_SWIOV(bp))
		wetuwn 1;

	/* fiwst get the cid - the onwy events we handwe hewe awe cfc-dewete
	 * and set-mac compwetion
	 */
	opcode = ewem->message.opcode;

	switch (opcode) {
	case EVENT_WING_OPCODE_CFC_DEW:
		cid = SW_CID(ewem->message.data.cfc_dew_event.cid);
		DP(BNX2X_MSG_IOV, "checking cfc-dew comp cid=%d\n", cid);
		bweak;
	case EVENT_WING_OPCODE_CWASSIFICATION_WUWES:
	case EVENT_WING_OPCODE_MUWTICAST_WUWES:
	case EVENT_WING_OPCODE_FIWTEWS_WUWES:
	case EVENT_WING_OPCODE_WSS_UPDATE_WUWES:
		cid = SW_CID(ewem->message.data.eth_event.echo);
		DP(BNX2X_MSG_IOV, "checking fiwtewing comp cid=%d\n", cid);
		bweak;
	case EVENT_WING_OPCODE_VF_FWW:
		abs_vfid = ewem->message.data.vf_fww_event.vf_id;
		DP(BNX2X_MSG_IOV, "Got VF FWW notification abs_vfid=%d\n",
		   abs_vfid);
		goto get_vf;
	case EVENT_WING_OPCODE_MAWICIOUS_VF:
		abs_vfid = ewem->message.data.mawicious_vf_event.vf_id;
		BNX2X_EWW("Got VF MAWICIOUS notification abs_vfid=%d eww_id=0x%x\n",
			  abs_vfid,
			  ewem->message.data.mawicious_vf_event.eww_id);
		goto get_vf;
	defauwt:
		wetuwn 1;
	}

	/* check if the cid is the VF wange */
	if (!bnx2x_iov_is_vf_cid(bp, cid)) {
		DP(BNX2X_MSG_IOV, "cid is outside vf wange: %d\n", cid);
		wetuwn 1;
	}

	/* extwact vf and wxq index fwom vf_cid - wewies on the fowwowing:
	 * 1. vfid on cid wefwects the twue abs_vfid
	 * 2. The max numbew of VFs (pew path) is 64
	 */
	qidx = cid & ((1 << BNX2X_VF_CID_WND)-1);
	abs_vfid = (cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
get_vf:
	vf = bnx2x_vf_by_abs_fid(bp, abs_vfid);

	if (!vf) {
		BNX2X_EWW("EQ compwetion fow unknown VF, cid %d, abs_vfid %d\n",
			  cid, abs_vfid);
		wetuwn 0;
	}

	switch (opcode) {
	case EVENT_WING_OPCODE_CFC_DEW:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] cfc dewete wamwod\n",
		   vf->abs_vfid, qidx);
		vfq_get(vf, qidx)->sp_obj.compwete_cmd(bp,
						       &vfq_get(vf,
								qidx)->sp_obj,
						       BNX2X_Q_CMD_CFC_DEW);
		bweak;
	case EVENT_WING_OPCODE_CWASSIFICATION_WUWES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mac/vwan wamwod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handwe_cwassification_eqe(bp, vfq_get(vf, qidx), ewem);
		bweak;
	case EVENT_WING_OPCODE_MUWTICAST_WUWES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mcast wamwod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handwe_mcast_eqe(bp, vf);
		bweak;
	case EVENT_WING_OPCODE_FIWTEWS_WUWES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set wx-mode wamwod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handwe_fiwtews_eqe(bp, vf);
		bweak;
	case EVENT_WING_OPCODE_WSS_UPDATE_WUWES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] WSS update wamwod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handwe_wss_update_eqe(bp, vf);
		fawwthwough;
	case EVENT_WING_OPCODE_VF_FWW:
		/* Do nothing fow now */
		wetuwn 0;
	case EVENT_WING_OPCODE_MAWICIOUS_VF:
		vf->mawicious = twue;
		wetuwn 0;
	}

	wetuwn 0;
}

static stwuct bnx2x_viwtf *bnx2x_vf_by_cid(stwuct bnx2x *bp, int vf_cid)
{
	/* extwact the vf fwom vf_cid - wewies on the fowwowing:
	 * 1. vfid on cid wefwects the twue abs_vfid
	 * 2. The max numbew of VFs (pew path) is 64
	 */
	int abs_vfid = (vf_cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
	wetuwn bnx2x_vf_by_abs_fid(bp, abs_vfid);
}

void bnx2x_iov_set_queue_sp_obj(stwuct bnx2x *bp, int vf_cid,
				stwuct bnx2x_queue_sp_obj **q_obj)
{
	stwuct bnx2x_viwtf *vf;

	if (!IS_SWIOV(bp))
		wetuwn;

	vf = bnx2x_vf_by_cid(bp, vf_cid);

	if (vf) {
		/* extwact queue index fwom vf_cid - wewies on the fowwowing:
		 * 1. vfid on cid wefwects the twue abs_vfid
		 * 2. The max numbew of VFs (pew path) is 64
		 */
		int q_index = vf_cid & ((1 << BNX2X_VF_CID_WND)-1);
		*q_obj = &bnx2x_vfq(vf, q_index, sp_obj);
	} ewse {
		BNX2X_EWW("No vf matching cid %d\n", vf_cid);
	}
}

void bnx2x_iov_adjust_stats_weq(stwuct bnx2x *bp)
{
	int i;
	int fiwst_queue_quewy_index, num_queues_weq;
	stwuct stats_quewy_entwy *cuw_quewy_entwy;
	u8 stats_count = 0;
	boow is_fcoe = fawse;

	if (!IS_SWIOV(bp))
		wetuwn;

	if (!NO_FCOE(bp))
		is_fcoe = twue;

	/* fcoe adds one gwobaw wequest and one queue wequest */
	num_queues_weq = BNX2X_NUM_ETH_QUEUES(bp) + is_fcoe;
	fiwst_queue_quewy_index = BNX2X_FIWST_QUEUE_QUEWY_IDX -
		(is_fcoe ? 0 : 1);

	DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
	       "BNX2X_NUM_ETH_QUEUES %d, is_fcoe %d, fiwst_queue_quewy_index %d => detewmined the wast non viwtuaw statistics quewy index is %d. Wiww add quewies on top of that\n",
	       BNX2X_NUM_ETH_QUEUES(bp), is_fcoe, fiwst_queue_quewy_index,
	       fiwst_queue_quewy_index + num_queues_weq);

	cuw_quewy_entwy = &bp->fw_stats_weq->
		quewy[fiwst_queue_quewy_index + num_queues_weq];

	fow_each_vf(bp, i) {
		int j;
		stwuct bnx2x_viwtf *vf = BP_VF(bp, i);

		if (vf->state != VF_ENABWED) {
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "vf %d not enabwed so no stats fow it\n",
			       vf->abs_vfid);
			continue;
		}

		if (vf->mawicious) {
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "vf %d mawicious so no stats fow it\n",
			       vf->abs_vfid);
			continue;
		}

		DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
		       "add addwesses fow vf %d\n", vf->abs_vfid);
		fow_each_vfq(vf, j) {
			stwuct bnx2x_vf_queue *wxq = vfq_get(vf, j);

			dma_addw_t q_stats_addw =
				vf->fw_stat_map + j * vf->stats_stwide;

			/* cowwect stats fwo active queues onwy */
			if (bnx2x_get_q_wogicaw_state(bp, &wxq->sp_obj) ==
			    BNX2X_Q_WOGICAW_STATE_STOPPED)
				continue;

			/* cweate stats quewy entwy fow this queue */
			cuw_quewy_entwy->kind = STATS_TYPE_QUEUE;
			cuw_quewy_entwy->index = vfq_stat_id(vf, wxq);
			cuw_quewy_entwy->funcID =
				cpu_to_we16(FW_VF_HANDWE(vf->abs_vfid));
			cuw_quewy_entwy->addwess.hi =
				cpu_to_we32(U64_HI(q_stats_addw));
			cuw_quewy_entwy->addwess.wo =
				cpu_to_we32(U64_WO(q_stats_addw));
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "added addwess %x %x fow vf %d queue %d cwient %d\n",
			       cuw_quewy_entwy->addwess.hi,
			       cuw_quewy_entwy->addwess.wo,
			       cuw_quewy_entwy->funcID,
			       j, cuw_quewy_entwy->index);
			cuw_quewy_entwy++;
			stats_count++;

			/* aww stats awe coawesced to the weading queue */
			if (vf->cfg_fwags & VF_CFG_STATS_COAWESCE)
				bweak;
		}
	}
	bp->fw_stats_weq->hdw.cmd_num = bp->fw_stats_num + stats_count;
}

/* VF API hewpews */
static void bnx2x_vf_qtbw_set_q(stwuct bnx2x *bp, u8 abs_vfid, u8 qid,
				u8 enabwe)
{
	u32 weg = PXP_WEG_HST_ZONE_PEWMISSION_TABWE + qid * 4;
	u32 vaw = enabwe ? (abs_vfid | (1 << 6)) : 0;

	WEG_WW(bp, weg, vaw);
}

static void bnx2x_vf_cww_qtbw(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int i;

	fow_each_vfq(vf, i)
		bnx2x_vf_qtbw_set_q(bp, vf->abs_vfid,
				    vfq_qzone_id(vf, vfq_get(vf, i)), fawse);
}

static void bnx2x_vf_igu_disabwe(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	u32 vaw;

	/* cweaw the VF configuwation - pwetend */
	bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, vf->abs_vfid));
	vaw = WEG_WD(bp, IGU_WEG_VF_CONFIGUWATION);
	vaw &= ~(IGU_VF_CONF_MSI_MSIX_EN | IGU_VF_CONF_SINGWE_ISW_EN |
		 IGU_VF_CONF_FUNC_EN | IGU_VF_CONF_PAWENT_MASK);
	WEG_WW(bp, IGU_WEG_VF_CONFIGUWATION, vaw);
	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));
}

u8 bnx2x_vf_max_queue_cnt(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	wetuwn min_t(u8, min_t(u8, vf_sb_count(vf), BNX2X_CIDS_PEW_VF),
		     BNX2X_VF_MAX_QUEUES);
}

static
int bnx2x_vf_chk_avaiw_wesc(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			    stwuct vf_pf_wesc_wequest *weq_wesc)
{
	u8 wxq_cnt = vf_wxq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);
	u8 txq_cnt = vf_txq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);

	wetuwn ((weq_wesc->num_wxqs <= wxq_cnt) &&
		(weq_wesc->num_txqs <= txq_cnt) &&
		(weq_wesc->num_sbs <= vf_sb_count(vf))   &&
		(weq_wesc->num_mac_fiwtews <= vf_mac_wuwes_cnt(vf)) &&
		(weq_wesc->num_vwan_fiwtews <= vf_vwan_wuwes_cnt(vf)));
}

/* COWE VF API */
int bnx2x_vf_acquiwe(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		     stwuct vf_pf_wesc_wequest *wesc)
{
	int base_vf_cid = (BP_VFDB(bp)->swiov.fiwst_vf_in_pf + vf->index) *
		BNX2X_CIDS_PEW_VF;

	union cdu_context *base_cxt = (union cdu_context *)
		BP_VF_CXT_PAGE(bp, base_vf_cid/IWT_PAGE_CIDS)->addw +
		(base_vf_cid & (IWT_PAGE_CIDS-1));
	int i;

	/* if state is 'acquiwed' the VF was not weweased ow FWW'd, in
	 * this case the wetuwned wesouwces match the acquiwed awweady
	 * acquiwed wesouwces. Vewify that the wequested numbews do
	 * not exceed the awweady acquiwed numbews.
	 */
	if (vf->state == VF_ACQUIWED) {
		DP(BNX2X_MSG_IOV, "VF[%d] Twying to we-acquiwe wesouwces (VF was not weweased ow FWW'd)\n",
		   vf->abs_vfid);

		if (!bnx2x_vf_chk_avaiw_wesc(bp, vf, wesc)) {
			BNX2X_EWW("VF[%d] When we-acquiwing wesouwces, wequested numbews must be <= then pweviouswy acquiwed numbews\n",
				  vf->abs_vfid);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	/* Othewwise vf state must be 'fwee' ow 'weset' */
	if (vf->state != VF_FWEE && vf->state != VF_WESET) {
		BNX2X_EWW("VF[%d] Can not acquiwe a VF with state %d\n",
			  vf->abs_vfid, vf->state);
		wetuwn -EINVAW;
	}

	/* static awwocation:
	 * the gwobaw maximum numbew awe fixed pew VF. Faiw the wequest if
	 * wequested numbew exceed these gwobaws
	 */
	if (!bnx2x_vf_chk_avaiw_wesc(bp, vf, wesc)) {
		DP(BNX2X_MSG_IOV,
		   "cannot fuwfiww vf wesouwce wequest. Pwacing maximaw avaiwabwe vawues in wesponse\n");
		/* set the max wesouwce in the vf */
		wetuwn -ENOMEM;
	}

	/* Set wesouwces countews - 0 wequest means max avaiwabwe */
	vf_sb_count(vf) = wesc->num_sbs;
	vf_wxq_count(vf) = wesc->num_wxqs ? : bnx2x_vf_max_queue_cnt(bp, vf);
	vf_txq_count(vf) = wesc->num_txqs ? : bnx2x_vf_max_queue_cnt(bp, vf);

	DP(BNX2X_MSG_IOV,
	   "Fuwfiwwing vf wequest: sb count %d, tx_count %d, wx_count %d, mac_wuwes_count %d, vwan_wuwes_count %d\n",
	   vf_sb_count(vf), vf_wxq_count(vf),
	   vf_txq_count(vf), vf_mac_wuwes_cnt(vf),
	   vf_vwan_wuwes_cnt(vf));

	/* Initiawize the queues */
	if (!vf->vfqs) {
		DP(BNX2X_MSG_IOV, "vf->vfqs was not awwocated\n");
		wetuwn -EINVAW;
	}

	fow_each_vfq(vf, i) {
		stwuct bnx2x_vf_queue *q = vfq_get(vf, i);

		if (!q) {
			BNX2X_EWW("q numbew %d was not awwocated\n", i);
			wetuwn -EINVAW;
		}

		q->index = i;
		q->cxt = &((base_cxt + i)->eth);
		q->cid = BNX2X_FIWST_VF_CID + base_vf_cid + i;

		DP(BNX2X_MSG_IOV, "VFQ[%d:%d]: index %d, cid 0x%x, cxt %p\n",
		   vf->abs_vfid, i, q->index, q->cid, q->cxt);

		/* init SP objects */
		bnx2x_vfq_init(bp, vf, q);
	}
	vf->state = VF_ACQUIWED;
	wetuwn 0;
}

int bnx2x_vf_init(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf, dma_addw_t *sb_map)
{
	stwuct bnx2x_func_init_pawams func_init = {0};
	int i;

	/* the sb wesouwces awe initiawized at this point, do the
	 * FW/HW initiawizations
	 */
	fow_each_vf_sb(vf, i)
		bnx2x_init_sb(bp, (dma_addw_t)sb_map[i], vf->abs_vfid, twue,
			      vf_igu_sb(vf, i), vf_igu_sb(vf, i));

	/* Sanity checks */
	if (vf->state != VF_ACQUIWED) {
		DP(BNX2X_MSG_IOV, "VF[%d] is not in VF_ACQUIWED, but %d\n",
		   vf->abs_vfid, vf->state);
		wetuwn -EINVAW;
	}

	/* wet FWW compwete ... */
	msweep(100);

	/* FWW cweanup epiwogue */
	if (bnx2x_vf_fww_cwnup_epiwog(bp, vf->abs_vfid))
		wetuwn -EBUSY;

	/* weset IGU VF statistics: MSIX */
	WEG_WW(bp, IGU_WEG_STATISTIC_NUM_MESSAGE_SENT + vf->abs_vfid * 4 , 0);

	/* function setup */
	func_init.pf_id = BP_FUNC(bp);
	func_init.func_id = FW_VF_HANDWE(vf->abs_vfid);
	bnx2x_func_init(bp, &func_init);

	/* Enabwe the vf */
	bnx2x_vf_enabwe_access(bp, vf->abs_vfid);
	bnx2x_vf_enabwe_twaffic(bp, vf);

	/* queue pwotection tabwe */
	fow_each_vfq(vf, i)
		bnx2x_vf_qtbw_set_q(bp, vf->abs_vfid,
				    vfq_qzone_id(vf, vfq_get(vf, i)), twue);

	vf->state = VF_ENABWED;

	/* update vf buwwetin boawd */
	bnx2x_post_vf_buwwetin(bp, vf->index);

	wetuwn 0;
}

stwuct set_vf_state_cookie {
	stwuct bnx2x_viwtf *vf;
	u8 state;
};

static void bnx2x_set_vf_state(void *cookie)
{
	stwuct set_vf_state_cookie *p = (stwuct set_vf_state_cookie *)cookie;

	p->vf->state = p->state;
}

int bnx2x_vf_cwose(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int wc = 0, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Cwose aww queues */
	fow (i = 0; i < vf_wxq_count(vf); i++) {
		wc = bnx2x_vf_queue_teawdown(bp, vf, i);
		if (wc)
			goto op_eww;
	}

	/* disabwe the intewwupts */
	DP(BNX2X_MSG_IOV, "disabwing igu\n");
	bnx2x_vf_igu_disabwe(bp, vf);

	/* disabwe the VF */
	DP(BNX2X_MSG_IOV, "cweawing qtbw\n");
	bnx2x_vf_cww_qtbw(bp, vf);

	/* need to make suwe thewe awe no outstanding stats wamwods which may
	 * cause the device to access the VF's stats buffew which it wiww fwee
	 * as soon as we wetuwn fwom the cwose fwow.
	 */
	{
		stwuct set_vf_state_cookie cookie;

		cookie.vf = vf;
		cookie.state = VF_ACQUIWED;
		wc = bnx2x_stats_safe_exec(bp, bnx2x_set_vf_state, &cookie);
		if (wc)
			goto op_eww;
	}

	DP(BNX2X_MSG_IOV, "set state to acquiwed\n");

	wetuwn 0;
op_eww:
	BNX2X_EWW("vf[%d] CWOSE ewwow: wc %d\n", vf->abs_vfid, wc);
	wetuwn wc;
}

/* VF wewease can be cawwed eithew: 1. The VF was acquiwed but
 * not enabwed 2. the vf was enabwed ow in the pwocess of being
 * enabwed
 */
int bnx2x_vf_fwee(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int wc;

	DP(BNX2X_MSG_IOV, "VF[%d] STATE: %s\n", vf->abs_vfid,
	   vf->state == VF_FWEE ? "Fwee" :
	   vf->state == VF_ACQUIWED ? "Acquiwed" :
	   vf->state == VF_ENABWED ? "Enabwed" :
	   vf->state == VF_WESET ? "Weset" :
	   "Unknown");

	switch (vf->state) {
	case VF_ENABWED:
		wc = bnx2x_vf_cwose(bp, vf);
		if (wc)
			goto op_eww;
		fawwthwough;	/* to wewease wesouwces */
	case VF_ACQUIWED:
		DP(BNX2X_MSG_IOV, "about to fwee wesouwces\n");
		bnx2x_vf_fwee_wesc(bp, vf);
		bweak;

	case VF_FWEE:
	case VF_WESET:
	defauwt:
		bweak;
	}
	wetuwn 0;
op_eww:
	BNX2X_EWW("VF[%d] WEWEASE ewwow: wc %d\n", vf->abs_vfid, wc);
	wetuwn wc;
}

int bnx2x_vf_wss_update(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			stwuct bnx2x_config_wss_pawams *wss)
{
	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);
	set_bit(WAMWOD_COMP_WAIT, &wss->wamwod_fwags);
	wetuwn bnx2x_config_wss(bp, wss);
}

int bnx2x_vf_tpa_update(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			stwuct vfpf_tpa_twv *twv,
			stwuct bnx2x_queue_update_tpa_pawams *pawams)
{
	awigned_u64 *sge_addw = twv->tpa_cwient_info.sge_addw;
	stwuct bnx2x_queue_state_pawams qstate;
	int qid, wc = 0;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Set wamwod pawams */
	memset(&qstate, 0, sizeof(stwuct bnx2x_queue_state_pawams));
	memcpy(&qstate.pawams.update_tpa, pawams,
	       sizeof(stwuct bnx2x_queue_update_tpa_pawams));
	qstate.cmd = BNX2X_Q_CMD_UPDATE_TPA;
	set_bit(WAMWOD_COMP_WAIT, &qstate.wamwod_fwags);

	fow (qid = 0; qid < vf_wxq_count(vf); qid++) {
		qstate.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
		qstate.pawams.update_tpa.sge_map = sge_addw[qid];
		DP(BNX2X_MSG_IOV, "sge_addw[%d:%d] %08x:%08x\n",
		   vf->abs_vfid, qid, U64_HI(sge_addw[qid]),
		   U64_WO(sge_addw[qid]));
		wc = bnx2x_queue_state_change(bp, &qstate);
		if (wc) {
			BNX2X_EWW("Faiwed to configuwe sge_addw %08x:%08x fow [%d:%d]\n",
				  U64_HI(sge_addw[qid]), U64_WO(sge_addw[qid]),
				  vf->abs_vfid, qid);
			wetuwn wc;
		}
	}

	wetuwn wc;
}

/* VF wewease ~ VF cwose + VF wewease-wesouwces
 * Wewease is the uwtimate SW shutdown and is cawwed whenevew an
 * iwwecovewabwe ewwow is encountewed.
 */
int bnx2x_vf_wewease(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf)
{
	int wc;

	DP(BNX2X_MSG_IOV, "PF weweasing vf %d\n", vf->abs_vfid);
	bnx2x_wock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_WEWEASE_VF);

	wc = bnx2x_vf_fwee(bp, vf);
	if (wc)
		WAWN(wc,
		     "VF[%d] Faiwed to awwocate wesouwces fow wewease op- wc=%d\n",
		     vf->abs_vfid, wc);
	bnx2x_unwock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_WEWEASE_VF);
	wetuwn wc;
}

void bnx2x_wock_vf_pf_channew(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			      enum channew_twvs twv)
{
	/* we don't wock the channew fow unsuppowted twvs */
	if (!bnx2x_twv_suppowted(twv)) {
		BNX2X_EWW("attempting to wock with unsuppowted twv. Abowting\n");
		wetuwn;
	}

	/* wock the channew */
	mutex_wock(&vf->op_mutex);

	/* wecowd the wocking op */
	vf->op_cuwwent = twv;

	/* wog the wock */
	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channew wocked by %d\n",
	   vf->abs_vfid, twv);
}

void bnx2x_unwock_vf_pf_channew(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				enum channew_twvs expected_twv)
{
	enum channew_twvs cuwwent_twv;

	if (!vf) {
		BNX2X_EWW("VF was %p\n", vf);
		wetuwn;
	}

	cuwwent_twv = vf->op_cuwwent;

	/* we don't unwock the channew fow unsuppowted twvs */
	if (!bnx2x_twv_suppowted(expected_twv))
		wetuwn;

	WAWN(expected_twv != vf->op_cuwwent,
	     "wock mismatch: expected %d found %d", expected_twv,
	     vf->op_cuwwent);

	/* wecowd the wocking op */
	vf->op_cuwwent = CHANNEW_TWV_NONE;

	/* wock the channew */
	mutex_unwock(&vf->op_mutex);

	/* wog the unwock */
	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channew unwocked by %d\n",
	   vf->abs_vfid, cuwwent_twv);
}

static int bnx2x_set_pf_tx_switching(stwuct bnx2x *bp, boow enabwe)
{
	stwuct bnx2x_queue_state_pawams q_pawams;
	u32 pwev_fwags;
	int i, wc;

	/* Vewify changes awe needed and wecowd cuwwent Tx switching state */
	pwev_fwags = bp->fwags;
	if (enabwe)
		bp->fwags |= TX_SWITCHING;
	ewse
		bp->fwags &= ~TX_SWITCHING;
	if (pwev_fwags == bp->fwags)
		wetuwn 0;

	/* Vewify state enabwes the sending of queue wamwods */
	if ((bp->state != BNX2X_STATE_OPEN) ||
	    (bnx2x_get_q_wogicaw_state(bp,
				      &bnx2x_sp_obj(bp, &bp->fp[0]).q_obj) !=
	     BNX2X_Q_WOGICAW_STATE_ACTIVE))
		wetuwn 0;

	/* send q. update wamwod to configuwe Tx switching */
	memset(&q_pawams, 0, sizeof(q_pawams));
	__set_bit(WAMWOD_COMP_WAIT, &q_pawams.wamwod_fwags);
	q_pawams.cmd = BNX2X_Q_CMD_UPDATE;
	__set_bit(BNX2X_Q_UPDATE_TX_SWITCHING_CHNG,
		  &q_pawams.pawams.update.update_fwags);
	if (enabwe)
		__set_bit(BNX2X_Q_UPDATE_TX_SWITCHING,
			  &q_pawams.pawams.update.update_fwags);
	ewse
		__cweaw_bit(BNX2X_Q_UPDATE_TX_SWITCHING,
			    &q_pawams.pawams.update.update_fwags);

	/* send the wamwod on aww the queues of the PF */
	fow_each_eth_queue(bp, i) {
		stwuct bnx2x_fastpath *fp = &bp->fp[i];
		int tx_idx;

		/* Set the appwopwiate Queue object */
		q_pawams.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

		fow (tx_idx = FIWST_TX_COS_INDEX;
		     tx_idx < fp->max_cos; tx_idx++) {
			q_pawams.pawams.update.cid_index = tx_idx;

			/* Update the Queue state */
			wc = bnx2x_queue_state_change(bp, &q_pawams);
			if (wc) {
				BNX2X_EWW("Faiwed to configuwe Tx switching\n");
				wetuwn wc;
			}
		}
	}

	DP(BNX2X_MSG_IOV, "%s Tx Switching\n", enabwe ? "Enabwed" : "Disabwed");
	wetuwn 0;
}

int bnx2x_swiov_configuwe(stwuct pci_dev *dev, int num_vfs_pawam)
{
	stwuct bnx2x *bp = netdev_pwiv(pci_get_dwvdata(dev));

	if (!IS_SWIOV(bp)) {
		BNX2X_EWW("faiwed to configuwe SW-IOV since vfdb was not awwocated. Check dmesg fow ewwows in pwobe stage\n");
		wetuwn -EINVAW;
	}

	DP(BNX2X_MSG_IOV, "bnx2x_swiov_configuwe cawwed with %d, BNX2X_NW_VIWTFN(bp) was %d\n",
	   num_vfs_pawam, BNX2X_NW_VIWTFN(bp));

	/* HW channew is onwy opewationaw when PF is up */
	if (bp->state != BNX2X_STATE_OPEN) {
		BNX2X_EWW("VF num configuwation via sysfs not suppowted whiwe PF is down\n");
		wetuwn -EINVAW;
	}

	/* we awe awways bound by the totaw_vfs in the configuwation space */
	if (num_vfs_pawam > BNX2X_NW_VIWTFN(bp)) {
		BNX2X_EWW("twuncating wequested numbew of VFs (%d) down to maximum awwowed (%d)\n",
			  num_vfs_pawam, BNX2X_NW_VIWTFN(bp));
		num_vfs_pawam = BNX2X_NW_VIWTFN(bp);
	}

	bp->wequested_nw_viwtfn = num_vfs_pawam;
	if (num_vfs_pawam == 0) {
		bnx2x_set_pf_tx_switching(bp, fawse);
		bnx2x_disabwe_swiov(bp);
		wetuwn 0;
	} ewse {
		wetuwn bnx2x_enabwe_swiov(bp);
	}
}

#define IGU_ENTWY_SIZE 4

int bnx2x_enabwe_swiov(stwuct bnx2x *bp)
{
	int wc = 0, weq_vfs = bp->wequested_nw_viwtfn;
	int vf_idx, sb_idx, vfq_idx, qcount, fiwst_vf;
	u32 igu_entwy, addwess;
	u16 num_vf_queues;

	if (weq_vfs == 0)
		wetuwn 0;

	fiwst_vf = bp->vfdb->swiov.fiwst_vf_in_pf;

	/* staticawwy distwibute vf sb poow between VFs */
	num_vf_queues = min_t(u16, BNX2X_VF_MAX_QUEUES,
			      BP_VFDB(bp)->vf_sbs_poow / weq_vfs);

	/* zewo pwevious vawues weawned fwom igu cam */
	fow (vf_idx = 0; vf_idx < weq_vfs; vf_idx++) {
		stwuct bnx2x_viwtf *vf = BP_VF(bp, vf_idx);

		vf->sb_count = 0;
		vf_sb_count(BP_VF(bp, vf_idx)) = 0;
	}
	bp->vfdb->vf_sbs_poow = 0;

	/* pwepawe IGU cam */
	sb_idx = BP_VFDB(bp)->fiwst_vf_igu_entwy;
	addwess = IGU_WEG_MAPPING_MEMOWY + sb_idx * IGU_ENTWY_SIZE;
	fow (vf_idx = fiwst_vf; vf_idx < fiwst_vf + weq_vfs; vf_idx++) {
		fow (vfq_idx = 0; vfq_idx < num_vf_queues; vfq_idx++) {
			igu_entwy = vf_idx << IGU_WEG_MAPPING_MEMOWY_FID_SHIFT |
				vfq_idx << IGU_WEG_MAPPING_MEMOWY_VECTOW_SHIFT |
				IGU_WEG_MAPPING_MEMOWY_VAWID;
			DP(BNX2X_MSG_IOV, "assigning sb %d to vf %d\n",
			   sb_idx, vf_idx);
			WEG_WW(bp, addwess, igu_entwy);
			sb_idx++;
			addwess += IGU_ENTWY_SIZE;
		}
	}

	/* Weinitiawize vf database accowding to igu cam */
	bnx2x_get_vf_igu_cam_info(bp);

	DP(BNX2X_MSG_IOV, "vf_sbs_poow %d, num_vf_queues %d\n",
	   BP_VFDB(bp)->vf_sbs_poow, num_vf_queues);

	qcount = 0;
	fow_each_vf(bp, vf_idx) {
		stwuct bnx2x_viwtf *vf = BP_VF(bp, vf_idx);

		/* set wocaw queue awways */
		vf->vfqs = &bp->vfdb->vfqs[qcount];
		qcount += vf_sb_count(vf);
		bnx2x_iov_static_wesc(bp, vf);
	}

	/* pwepawe msix vectows in VF configuwation space - the vawue in the
	 * PCI configuwation space shouwd be the index of the wast entwy,
	 * namewy one wess than the actuaw size of the tabwe
	 */
	fow (vf_idx = fiwst_vf; vf_idx < fiwst_vf + weq_vfs; vf_idx++) {
		bnx2x_pwetend_func(bp, HW_VF_HANDWE(bp, vf_idx));
		WEG_WW(bp, PCICFG_OFFSET + GWC_CONFIG_WEG_VF_MSIX_CONTWOW,
		       num_vf_queues - 1);
		DP(BNX2X_MSG_IOV, "set msix vec num in VF %d cfg space to %d\n",
		   vf_idx, num_vf_queues - 1);
	}
	bnx2x_pwetend_func(bp, BP_ABS_FUNC(bp));

	/* enabwe swiov. This wiww pwobe aww the VFs, and consequentiawwy cause
	 * the "acquiwe" messages to appeaw on the VF PF channew.
	 */
	DP(BNX2X_MSG_IOV, "about to caww enabwe swiov\n");
	bnx2x_disabwe_swiov(bp);

	wc = bnx2x_set_pf_tx_switching(bp, twue);
	if (wc)
		wetuwn wc;

	wc = pci_enabwe_swiov(bp->pdev, weq_vfs);
	if (wc) {
		BNX2X_EWW("pci_enabwe_swiov faiwed with %d\n", wc);
		wetuwn wc;
	}
	DP(BNX2X_MSG_IOV, "swiov enabwed (%d vfs)\n", weq_vfs);
	wetuwn weq_vfs;
}

void bnx2x_pf_set_vfs_vwan(stwuct bnx2x *bp)
{
	int vfidx;
	stwuct pf_vf_buwwetin_content *buwwetin;

	DP(BNX2X_MSG_IOV, "configuwing vwan fow VFs fwom sp-task\n");
	fow_each_vf(bp, vfidx) {
		buwwetin = BP_VF_BUWWETIN(bp, vfidx);
		if (buwwetin->vawid_bitmap & (1 << VWAN_VAWID))
			bnx2x_set_vf_vwan(bp->dev, vfidx, buwwetin->vwan, 0,
					  htons(ETH_P_8021Q));
	}
}

void bnx2x_disabwe_swiov(stwuct bnx2x *bp)
{
	if (pci_vfs_assigned(bp->pdev)) {
		DP(BNX2X_MSG_IOV,
		   "Unwoading dwivew whiwe VFs awe assigned - VFs wiww not be deawwocated\n");
		wetuwn;
	}

	pci_disabwe_swiov(bp->pdev);
}

static int bnx2x_vf_op_pwep(stwuct bnx2x *bp, int vfidx,
			    stwuct bnx2x_viwtf **vf,
			    stwuct pf_vf_buwwetin_content **buwwetin,
			    boow test_queue)
{
	if (bp->state != BNX2X_STATE_OPEN) {
		BNX2X_EWW("PF is down - can't utiwize iov-wewated functionawity\n");
		wetuwn -EINVAW;
	}

	if (!IS_SWIOV(bp)) {
		BNX2X_EWW("swiov is disabwed - can't utiwize iov-wewated functionawity\n");
		wetuwn -EINVAW;
	}

	if (vfidx >= BNX2X_NW_VIWTFN(bp)) {
		BNX2X_EWW("VF is uninitiawized - can't utiwize iov-wewated functionawity. vfidx was %d BNX2X_NW_VIWTFN was %d\n",
			  vfidx, BNX2X_NW_VIWTFN(bp));
		wetuwn -EINVAW;
	}

	/* init membews */
	*vf = BP_VF(bp, vfidx);
	*buwwetin = BP_VF_BUWWETIN(bp, vfidx);

	if (!*vf) {
		BNX2X_EWW("Unabwe to get VF stwuctuwe fow vfidx %d\n", vfidx);
		wetuwn -EINVAW;
	}

	if (test_queue && !(*vf)->vfqs) {
		BNX2X_EWW("vfqs stwuct is nuww. Was this invoked befowe dynamicawwy enabwing SW-IOV? vfidx was %d\n",
			  vfidx);
		wetuwn -EINVAW;
	}

	if (!*buwwetin) {
		BNX2X_EWW("Buwwetin Boawd stwuct is nuww fow vfidx %d\n",
			  vfidx);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int bnx2x_get_vf_config(stwuct net_device *dev, int vfidx,
			stwuct ifwa_vf_info *ivi)
{
	stwuct bnx2x *bp = netdev_pwiv(dev);
	stwuct bnx2x_viwtf *vf = NUWW;
	stwuct pf_vf_buwwetin_content *buwwetin = NUWW;
	stwuct bnx2x_vwan_mac_obj *mac_obj;
	stwuct bnx2x_vwan_mac_obj *vwan_obj;
	int wc;

	/* sanity and init */
	wc = bnx2x_vf_op_pwep(bp, vfidx, &vf, &buwwetin, twue);
	if (wc)
		wetuwn wc;

	mac_obj = &bnx2x_weading_vfq(vf, mac_obj);
	vwan_obj = &bnx2x_weading_vfq(vf, vwan_obj);
	if (!mac_obj || !vwan_obj) {
		BNX2X_EWW("VF pawtiawwy initiawized\n");
		wetuwn -EINVAW;
	}

	ivi->vf = vfidx;
	ivi->qos = 0;
	ivi->max_tx_wate = 10000; /* awways 10G. TBA take fwom wink stwuct */
	ivi->min_tx_wate = 0;
	ivi->spoofchk = vf->spoofchk ? 1 : 0;
	ivi->winkstate = vf->wink_cfg;
	if (vf->state == VF_ENABWED) {
		/* mac and vwan awe in vwan_mac objects */
		if (bnx2x_vawidate_vf_sp_objs(bp, vf, fawse)) {
			mac_obj->get_n_ewements(bp, mac_obj, 1, (u8 *)&ivi->mac,
						0, ETH_AWEN);
			vwan_obj->get_n_ewements(bp, vwan_obj, 1,
						 (u8 *)&ivi->vwan, 0,
						 VWAN_HWEN);
		}
	} ewse {
		mutex_wock(&bp->vfdb->buwwetin_mutex);
		/* mac */
		if (buwwetin->vawid_bitmap & (1 << MAC_ADDW_VAWID))
			/* mac configuwed by ndo so its in buwwetin boawd */
			memcpy(&ivi->mac, buwwetin->mac, ETH_AWEN);
		ewse
			/* function has not been woaded yet. Show mac as 0s */
			eth_zewo_addw(ivi->mac);

		/* vwan */
		if (buwwetin->vawid_bitmap & (1 << VWAN_VAWID))
			/* vwan configuwed by ndo so its in buwwetin boawd */
			memcpy(&ivi->vwan, &buwwetin->vwan, VWAN_HWEN);
		ewse
			/* function has not been woaded yet. Show vwans as 0s */
			memset(&ivi->vwan, 0, VWAN_HWEN);

		mutex_unwock(&bp->vfdb->buwwetin_mutex);
	}

	wetuwn 0;
}

/* New mac fow VF. Considew these cases:
 * 1. VF hasn't been acquiwed yet - save the mac in wocaw buwwetin boawd and
 *    suppwy at acquiwe.
 * 2. VF has awweady been acquiwed but has not yet initiawized - stowe in wocaw
 *    buwwetin boawd. mac wiww be posted on VF buwwetin boawd aftew VF init. VF
 *    wiww configuwe this mac when it is weady.
 * 3. VF has awweady initiawized but has not yet setup a queue - post the new
 *    mac on VF's buwwetin boawd wight now. VF wiww configuwe this mac when it
 *    is weady.
 * 4. VF has awweady set a queue - dewete any macs awweady configuwed fow this
 *    queue and manuawwy config the new mac.
 * In any event, once this function has been cawwed wefuse any attempts by the
 * VF to configuwe any mac fow itsewf except fow this mac. In case of a wace
 * whewe the VF faiws to see the new post on its buwwetin boawd befowe sending a
 * mac configuwation wequest, the PF wiww simpwy faiw the wequest and VF can twy
 * again aftew consuwting its buwwetin boawd.
 */
int bnx2x_set_vf_mac(stwuct net_device *dev, int vfidx, u8 *mac)
{
	stwuct bnx2x *bp = netdev_pwiv(dev);
	int wc, q_wogicaw_state;
	stwuct bnx2x_viwtf *vf = NUWW;
	stwuct pf_vf_buwwetin_content *buwwetin = NUWW;

	if (!is_vawid_ethew_addw(mac)) {
		BNX2X_EWW("mac addwess invawid\n");
		wetuwn -EINVAW;
	}

	/* sanity and init */
	wc = bnx2x_vf_op_pwep(bp, vfidx, &vf, &buwwetin, twue);
	if (wc)
		wetuwn wc;

	mutex_wock(&bp->vfdb->buwwetin_mutex);

	/* update PF's copy of the VF's buwwetin. Wiww no wongew accept mac
	 * configuwation wequests fwom vf unwess match this mac
	 */
	buwwetin->vawid_bitmap |= 1 << MAC_ADDW_VAWID;
	memcpy(buwwetin->mac, mac, ETH_AWEN);

	/* Post update on VF's buwwetin boawd */
	wc = bnx2x_post_vf_buwwetin(bp, vfidx);

	/* wewease wock befowe checking wetuwn code */
	mutex_unwock(&bp->vfdb->buwwetin_mutex);

	if (wc) {
		BNX2X_EWW("faiwed to update VF[%d] buwwetin\n", vfidx);
		wetuwn wc;
	}

	q_wogicaw_state =
		bnx2x_get_q_wogicaw_state(bp, &bnx2x_weading_vfq(vf, sp_obj));
	if (vf->state == VF_ENABWED &&
	    q_wogicaw_state == BNX2X_Q_WOGICAW_STATE_ACTIVE) {
		/* configuwe the mac in device on this vf's queue */
		unsigned wong wamwod_fwags = 0;
		stwuct bnx2x_vwan_mac_obj *mac_obj;

		/* Usew shouwd be abwe to see faiwuwe weason in system wogs */
		if (!bnx2x_vawidate_vf_sp_objs(bp, vf, twue))
			wetuwn -EINVAW;

		/* must wock vfpf channew to pwotect against vf fwows */
		bnx2x_wock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_SET_MAC);

		/* wemove existing eth macs */
		mac_obj = &bnx2x_weading_vfq(vf, mac_obj);
		wc = bnx2x_dew_aww_macs(bp, mac_obj, BNX2X_ETH_MAC, twue);
		if (wc) {
			BNX2X_EWW("faiwed to dewete eth macs\n");
			wc = -EINVAW;
			goto out;
		}

		/* wemove existing uc wist macs */
		wc = bnx2x_dew_aww_macs(bp, mac_obj, BNX2X_UC_WIST_MAC, twue);
		if (wc) {
			BNX2X_EWW("faiwed to dewete uc_wist macs\n");
			wc = -EINVAW;
			goto out;
		}

		/* configuwe the new mac to device */
		__set_bit(WAMWOD_COMP_WAIT, &wamwod_fwags);
		bnx2x_set_mac_one(bp, (u8 *)&buwwetin->mac, mac_obj, twue,
				  BNX2X_ETH_MAC, &wamwod_fwags);

out:
		bnx2x_unwock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_SET_MAC);
	}

	wetuwn wc;
}

static void bnx2x_set_vf_vwan_acceptance(stwuct bnx2x *bp,
					 stwuct bnx2x_viwtf *vf, boow accept)
{
	stwuct bnx2x_wx_mode_wamwod_pawams wx_wamwod;
	unsigned wong accept_fwags;

	/* need to wemove/add the VF's accept_any_vwan bit */
	accept_fwags = bnx2x_weading_vfq(vf, accept_fwags);
	if (accept)
		set_bit(BNX2X_ACCEPT_ANY_VWAN, &accept_fwags);
	ewse
		cweaw_bit(BNX2X_ACCEPT_ANY_VWAN, &accept_fwags);

	bnx2x_vf_pwep_wx_mode(bp, WEADING_IDX, &wx_wamwod, vf,
			      accept_fwags);
	bnx2x_weading_vfq(vf, accept_fwags) = accept_fwags;
	bnx2x_config_wx_mode(bp, &wx_wamwod);
}

static int bnx2x_set_vf_vwan_fiwtew(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				    u16 vwan, boow add)
{
	stwuct bnx2x_vwan_mac_wamwod_pawams wamwod_pawam;
	unsigned wong wamwod_fwags = 0;
	int wc = 0;

	/* configuwe the new vwan to device */
	memset(&wamwod_pawam, 0, sizeof(wamwod_pawam));
	__set_bit(WAMWOD_COMP_WAIT, &wamwod_fwags);
	wamwod_pawam.vwan_mac_obj = &bnx2x_weading_vfq(vf, vwan_obj);
	wamwod_pawam.wamwod_fwags = wamwod_fwags;
	wamwod_pawam.usew_weq.u.vwan.vwan = vwan;
	wamwod_pawam.usew_weq.cmd = add ? BNX2X_VWAN_MAC_ADD
					: BNX2X_VWAN_MAC_DEW;
	wc = bnx2x_config_vwan_mac(bp, &wamwod_pawam);
	if (wc) {
		BNX2X_EWW("faiwed to configuwe vwan\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int bnx2x_set_vf_vwan(stwuct net_device *dev, int vfidx, u16 vwan, u8 qos,
		      __be16 vwan_pwoto)
{
	stwuct pf_vf_buwwetin_content *buwwetin = NUWW;
	stwuct bnx2x *bp = netdev_pwiv(dev);
	stwuct bnx2x_vwan_mac_obj *vwan_obj;
	unsigned wong vwan_mac_fwags = 0;
	unsigned wong wamwod_fwags = 0;
	stwuct bnx2x_viwtf *vf = NUWW;
	int i, wc;

	if (vwan > 4095) {
		BNX2X_EWW("iwwegaw vwan vawue %d\n", vwan);
		wetuwn -EINVAW;
	}

	if (vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;

	DP(BNX2X_MSG_IOV, "configuwing VF %d with VWAN %d qos %d\n",
	   vfidx, vwan, 0);

	/* sanity and init */
	wc = bnx2x_vf_op_pwep(bp, vfidx, &vf, &buwwetin, twue);
	if (wc)
		wetuwn wc;

	/* update PF's copy of the VF's buwwetin. No point in posting the vwan
	 * to the VF since it doesn't have anything to do with it. But it usefuw
	 * to stowe it hewe in case the VF is not up yet and we can onwy
	 * configuwe the vwan watew when it does. Tweat vwan id 0 as wemove the
	 * Host tag.
	 */
	mutex_wock(&bp->vfdb->buwwetin_mutex);

	if (vwan > 0)
		buwwetin->vawid_bitmap |= 1 << VWAN_VAWID;
	ewse
		buwwetin->vawid_bitmap &= ~(1 << VWAN_VAWID);
	buwwetin->vwan = vwan;

	/* Post update on VF's buwwetin boawd */
	wc = bnx2x_post_vf_buwwetin(bp, vfidx);
	if (wc)
		BNX2X_EWW("faiwed to update VF[%d] buwwetin\n", vfidx);
	mutex_unwock(&bp->vfdb->buwwetin_mutex);

	/* is vf initiawized and queue set up? */
	if (vf->state != VF_ENABWED ||
	    bnx2x_get_q_wogicaw_state(bp, &bnx2x_weading_vfq(vf, sp_obj)) !=
	    BNX2X_Q_WOGICAW_STATE_ACTIVE)
		wetuwn wc;

	/* Usew shouwd be abwe to see ewwow in system wogs */
	if (!bnx2x_vawidate_vf_sp_objs(bp, vf, twue))
		wetuwn -EINVAW;

	/* must wock vfpf channew to pwotect against vf fwows */
	bnx2x_wock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_SET_VWAN);

	/* wemove existing vwans */
	__set_bit(WAMWOD_COMP_WAIT, &wamwod_fwags);
	vwan_obj = &bnx2x_weading_vfq(vf, vwan_obj);
	wc = vwan_obj->dewete_aww(bp, vwan_obj, &vwan_mac_fwags,
				  &wamwod_fwags);
	if (wc) {
		BNX2X_EWW("faiwed to dewete vwans\n");
		wc = -EINVAW;
		goto out;
	}

	/* cweaw accept_any_vwan when HV fowces vwan, othewwise
	 * accowding to VF capabiwities
	 */
	if (vwan || !(vf->cfg_fwags & VF_CFG_VWAN_FIWTEW))
		bnx2x_set_vf_vwan_acceptance(bp, vf, !vwan);

	wc = bnx2x_set_vf_vwan_fiwtew(bp, vf, vwan, twue);
	if (wc)
		goto out;

	/* send queue update wamwods to configuwe defauwt vwan and
	 * siwent vwan wemovaw
	 */
	fow_each_vfq(vf, i) {
		stwuct bnx2x_queue_state_pawams q_pawams = {NUWW};
		stwuct bnx2x_queue_update_pawams *update_pawams;

		q_pawams.q_obj = &bnx2x_vfq(vf, i, sp_obj);

		/* vawidate the Q is UP */
		if (bnx2x_get_q_wogicaw_state(bp, q_pawams.q_obj) !=
		    BNX2X_Q_WOGICAW_STATE_ACTIVE)
			continue;

		__set_bit(WAMWOD_COMP_WAIT, &q_pawams.wamwod_fwags);
		q_pawams.cmd = BNX2X_Q_CMD_UPDATE;
		update_pawams = &q_pawams.pawams.update;
		__set_bit(BNX2X_Q_UPDATE_DEF_VWAN_EN_CHNG,
			  &update_pawams->update_fwags);
		__set_bit(BNX2X_Q_UPDATE_SIWENT_VWAN_WEM_CHNG,
			  &update_pawams->update_fwags);
		if (vwan == 0) {
			/* if vwan is 0 then we want to weave the VF twaffic
			 * untagged, and weave the incoming twaffic untouched
			 * (i.e. do not wemove any vwan tags).
			 */
			__cweaw_bit(BNX2X_Q_UPDATE_DEF_VWAN_EN,
				    &update_pawams->update_fwags);
			__cweaw_bit(BNX2X_Q_UPDATE_SIWENT_VWAN_WEM,
				    &update_pawams->update_fwags);
		} ewse {
			/* configuwe defauwt vwan to vf queue and set siwent
			 * vwan wemovaw (the vf wemains unawawe of this vwan).
			 */
			__set_bit(BNX2X_Q_UPDATE_DEF_VWAN_EN,
				  &update_pawams->update_fwags);
			__set_bit(BNX2X_Q_UPDATE_SIWENT_VWAN_WEM,
				  &update_pawams->update_fwags);
			update_pawams->def_vwan = vwan;
			update_pawams->siwent_wemovaw_vawue =
				vwan & VWAN_VID_MASK;
			update_pawams->siwent_wemovaw_mask = VWAN_VID_MASK;
		}

		/* Update the Queue state */
		wc = bnx2x_queue_state_change(bp, &q_pawams);
		if (wc) {
			BNX2X_EWW("Faiwed to configuwe defauwt VWAN queue %d\n",
				  i);
			goto out;
		}
	}
out:
	bnx2x_unwock_vf_pf_channew(bp, vf, CHANNEW_TWV_PF_SET_VWAN);

	if (wc)
		DP(BNX2X_MSG_IOV,
		   "updated VF[%d] vwan configuwation (vwan = %d)\n",
		   vfidx, vwan);

	wetuwn wc;
}

int bnx2x_set_vf_spoofchk(stwuct net_device *dev, int idx, boow vaw)
{
	stwuct bnx2x *bp = netdev_pwiv(dev);
	stwuct bnx2x_viwtf *vf;
	int i, wc = 0;

	vf = BP_VF(bp, idx);
	if (!vf)
		wetuwn -EINVAW;

	/* nothing to do */
	if (vf->spoofchk == vaw)
		wetuwn 0;

	vf->spoofchk = vaw ? 1 : 0;

	DP(BNX2X_MSG_IOV, "%s spoofchk fow VF %d\n",
	   vaw ? "enabwing" : "disabwing", idx);

	/* is vf initiawized and queue set up? */
	if (vf->state != VF_ENABWED ||
	    bnx2x_get_q_wogicaw_state(bp, &bnx2x_weading_vfq(vf, sp_obj)) !=
	    BNX2X_Q_WOGICAW_STATE_ACTIVE)
		wetuwn wc;

	/* Usew shouwd be abwe to see ewwow in system wogs */
	if (!bnx2x_vawidate_vf_sp_objs(bp, vf, twue))
		wetuwn -EINVAW;

	/* send queue update wamwods to configuwe spoofchk */
	fow_each_vfq(vf, i) {
		stwuct bnx2x_queue_state_pawams q_pawams = {NUWW};
		stwuct bnx2x_queue_update_pawams *update_pawams;

		q_pawams.q_obj = &bnx2x_vfq(vf, i, sp_obj);

		/* vawidate the Q is UP */
		if (bnx2x_get_q_wogicaw_state(bp, q_pawams.q_obj) !=
		    BNX2X_Q_WOGICAW_STATE_ACTIVE)
			continue;

		__set_bit(WAMWOD_COMP_WAIT, &q_pawams.wamwod_fwags);
		q_pawams.cmd = BNX2X_Q_CMD_UPDATE;
		update_pawams = &q_pawams.pawams.update;
		__set_bit(BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG,
			  &update_pawams->update_fwags);
		if (vaw) {
			__set_bit(BNX2X_Q_UPDATE_ANTI_SPOOF,
				  &update_pawams->update_fwags);
		} ewse {
			__cweaw_bit(BNX2X_Q_UPDATE_ANTI_SPOOF,
				    &update_pawams->update_fwags);
		}

		/* Update the Queue state */
		wc = bnx2x_queue_state_change(bp, &q_pawams);
		if (wc) {
			BNX2X_EWW("Faiwed to %s spoofchk on VF %d - vfq %d\n",
				  vaw ? "enabwe" : "disabwe", idx, i);
			goto out;
		}
	}
out:
	if (!wc)
		DP(BNX2X_MSG_IOV,
		   "%s spoofchk fow VF[%d]\n", vaw ? "Enabwed" : "Disabwed",
		   idx);

	wetuwn wc;
}

/* cwc is the fiwst fiewd in the buwwetin boawd. Compute the cwc ovew the
 * entiwe buwwetin boawd excwuding the cwc fiewd itsewf. Use the wength fiewd
 * as the Buwwetin Boawd was posted by a PF with possibwy a diffewent vewsion
 * fwom the vf which wiww sampwe it. Thewefowe, the wength is computed by the
 * PF and then used bwindwy by the VF.
 */
u32 bnx2x_cwc_vf_buwwetin(stwuct pf_vf_buwwetin_content *buwwetin)
{
	wetuwn cwc32(BUWWETIN_CWC_SEED,
		 ((u8 *)buwwetin) + sizeof(buwwetin->cwc),
		 buwwetin->wength - sizeof(buwwetin->cwc));
}

/* Check fow new posts on the buwwetin boawd */
enum sampwe_buwwetin_wesuwt bnx2x_sampwe_buwwetin(stwuct bnx2x *bp)
{
	stwuct pf_vf_buwwetin_content *buwwetin;
	int attempts;

	/* sampwing stwuctuwe in mid post may wesuwt with cowwupted data
	 * vawidate cwc to ensuwe cohewency.
	 */
	fow (attempts = 0; attempts < BUWWETIN_ATTEMPTS; attempts++) {
		u32 cwc;

		/* sampwe the buwwetin boawd */
		memcpy(&bp->shadow_buwwetin, bp->pf2vf_buwwetin,
		       sizeof(union pf_vf_buwwetin));

		cwc = bnx2x_cwc_vf_buwwetin(&bp->shadow_buwwetin.content);

		if (bp->shadow_buwwetin.content.cwc == cwc)
			bweak;

		BNX2X_EWW("bad cwc on buwwetin boawd. Contained %x computed %x\n",
			  bp->shadow_buwwetin.content.cwc, cwc);
	}

	if (attempts >= BUWWETIN_ATTEMPTS) {
		BNX2X_EWW("pf to vf buwwetin boawd cwc was wwong %d consecutive times. Abowting\n",
			  attempts);
		wetuwn PFVF_BUWWETIN_CWC_EWW;
	}
	buwwetin = &bp->shadow_buwwetin.content;

	/* buwwetin boawd hasn't changed since wast sampwe */
	if (bp->owd_buwwetin.vewsion == buwwetin->vewsion)
		wetuwn PFVF_BUWWETIN_UNCHANGED;

	/* the mac addwess in buwwetin boawd is vawid and is new */
	if (buwwetin->vawid_bitmap & 1 << MAC_ADDW_VAWID &&
	    !ethew_addw_equaw(buwwetin->mac, bp->owd_buwwetin.mac)) {
		/* update new mac to net device */
		eth_hw_addw_set(bp->dev, buwwetin->mac);
	}

	if (buwwetin->vawid_bitmap & (1 << WINK_VAWID)) {
		DP(BNX2X_MSG_IOV, "wink update speed %d fwags %x\n",
		   buwwetin->wink_speed, buwwetin->wink_fwags);

		bp->vf_wink_vaws.wine_speed = buwwetin->wink_speed;
		bp->vf_wink_vaws.wink_wepowt_fwags = 0;
		/* Wink is down */
		if (buwwetin->wink_fwags & VFPF_WINK_WEPOWT_WINK_DOWN)
			__set_bit(BNX2X_WINK_WEPOWT_WINK_DOWN,
				  &bp->vf_wink_vaws.wink_wepowt_fwags);
		/* Fuww DUPWEX */
		if (buwwetin->wink_fwags & VFPF_WINK_WEPOWT_FUWW_DUPWEX)
			__set_bit(BNX2X_WINK_WEPOWT_FD,
				  &bp->vf_wink_vaws.wink_wepowt_fwags);
		/* Wx Fwow Contwow is ON */
		if (buwwetin->wink_fwags & VFPF_WINK_WEPOWT_WX_FC_ON)
			__set_bit(BNX2X_WINK_WEPOWT_WX_FC_ON,
				  &bp->vf_wink_vaws.wink_wepowt_fwags);
		/* Tx Fwow Contwow is ON */
		if (buwwetin->wink_fwags & VFPF_WINK_WEPOWT_TX_FC_ON)
			__set_bit(BNX2X_WINK_WEPOWT_TX_FC_ON,
				  &bp->vf_wink_vaws.wink_wepowt_fwags);
		__bnx2x_wink_wepowt(bp);
	}

	/* copy new buwwetin boawd to bp */
	memcpy(&bp->owd_buwwetin, buwwetin,
	       sizeof(stwuct pf_vf_buwwetin_content));

	wetuwn PFVF_BUWWETIN_UPDATED;
}

void bnx2x_timew_swiov(stwuct bnx2x *bp)
{
	bnx2x_sampwe_buwwetin(bp);

	/* if channew is down we need to sewf destwuct */
	if (bp->owd_buwwetin.vawid_bitmap & 1 << CHANNEW_DOWN)
		bnx2x_scheduwe_sp_wtnw(bp, BNX2X_SP_WTNW_VFPF_CHANNEW_DOWN,
				       BNX2X_MSG_IOV);
}

void __iomem *bnx2x_vf_doowbewws(stwuct bnx2x *bp)
{
	/* vf doowbewws awe embedded within the wegview */
	wetuwn bp->wegview + PXP_VF_ADDW_DB_STAWT;
}

void bnx2x_vf_pci_deawwoc(stwuct bnx2x *bp)
{
	BNX2X_PCI_FWEE(bp->vf2pf_mbox, bp->vf2pf_mbox_mapping,
		       sizeof(stwuct bnx2x_vf_mbx_msg));
	BNX2X_PCI_FWEE(bp->pf2vf_buwwetin, bp->pf2vf_buwwetin_mapping,
		       sizeof(union pf_vf_buwwetin));
}

int bnx2x_vf_pci_awwoc(stwuct bnx2x *bp)
{
	mutex_init(&bp->vf2pf_mutex);

	/* awwocate vf2pf maiwbox fow vf to pf channew */
	bp->vf2pf_mbox = BNX2X_PCI_AWWOC(&bp->vf2pf_mbox_mapping,
					 sizeof(stwuct bnx2x_vf_mbx_msg));
	if (!bp->vf2pf_mbox)
		goto awwoc_mem_eww;

	/* awwocate pf 2 vf buwwetin boawd */
	bp->pf2vf_buwwetin = BNX2X_PCI_AWWOC(&bp->pf2vf_buwwetin_mapping,
					     sizeof(union pf_vf_buwwetin));
	if (!bp->pf2vf_buwwetin)
		goto awwoc_mem_eww;

	bnx2x_vf_buwwetin_finawize(&bp->pf2vf_buwwetin->content, twue);

	wetuwn 0;

awwoc_mem_eww:
	bnx2x_vf_pci_deawwoc(bp);
	wetuwn -ENOMEM;
}

void bnx2x_iov_channew_down(stwuct bnx2x *bp)
{
	int vf_idx;
	stwuct pf_vf_buwwetin_content *buwwetin;

	if (!IS_SWIOV(bp))
		wetuwn;

	fow_each_vf(bp, vf_idx) {
		/* wocate this VFs buwwetin boawd and update the channew down
		 * bit
		 */
		buwwetin = BP_VF_BUWWETIN(bp, vf_idx);
		buwwetin->vawid_bitmap |= 1 << CHANNEW_DOWN;

		/* update vf buwwetin boawd */
		bnx2x_post_vf_buwwetin(bp, vf_idx);
	}
}

void bnx2x_iov_task(stwuct wowk_stwuct *wowk)
{
	stwuct bnx2x *bp = containew_of(wowk, stwuct bnx2x, iov_task.wowk);

	if (!netif_wunning(bp->dev))
		wetuwn;

	if (test_and_cweaw_bit(BNX2X_IOV_HANDWE_FWW,
			       &bp->iov_task_state))
		bnx2x_vf_handwe_fww_event(bp);

	if (test_and_cweaw_bit(BNX2X_IOV_HANDWE_VF_MSG,
			       &bp->iov_task_state))
		bnx2x_vf_mbx(bp);
}

void bnx2x_scheduwe_iov_task(stwuct bnx2x *bp, enum bnx2x_iov_fwag fwag)
{
	smp_mb__befowe_atomic();
	set_bit(fwag, &bp->iov_task_state);
	smp_mb__aftew_atomic();
	DP(BNX2X_MSG_IOV, "Scheduwing iov task [Fwag: %d]\n", fwag);
	queue_dewayed_wowk(bnx2x_iov_wq, &bp->iov_task, 0);
}
