// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude "qed.h"
#incwude <winux/qed/qed_chain.h>
#incwude "qed_cxt.h"
#incwude "qed_dcbx.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_int.h"
#incwude "qed_weg_addw.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"

void qed_sp_destwoy_wequest(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_spq_entwy *p_ent)
{
	/* qed_spq_get_entwy() can eithew get an entwy fwom the fwee_poow,
	 * ow, if no entwies awe weft, awwocate a new entwy and add it to
	 * the unwimited_pending wist.
	 */
	if (p_ent->queue == &p_hwfn->p_spq->unwimited_pending)
		kfwee(p_ent);
	ewse
		qed_spq_wetuwn_entwy(p_hwfn, p_ent);
}

int qed_sp_init_wequest(stwuct qed_hwfn *p_hwfn,
			stwuct qed_spq_entwy **pp_ent,
			u8 cmd, u8 pwotocow, stwuct qed_sp_init_data *p_data)
{
	u32 opaque_cid = p_data->opaque_fid << 16 | p_data->cid;
	stwuct qed_spq_entwy *p_ent = NUWW;
	int wc;

	if (!pp_ent)
		wetuwn -ENOMEM;

	wc = qed_spq_get_entwy(p_hwfn, pp_ent);

	if (wc)
		wetuwn wc;

	p_ent = *pp_ent;

	p_ent->ewem.hdw.cid		= cpu_to_we32(opaque_cid);
	p_ent->ewem.hdw.cmd_id		= cmd;
	p_ent->ewem.hdw.pwotocow_id	= pwotocow;

	p_ent->pwiowity		= QED_SPQ_PWIOWITY_NOWMAW;
	p_ent->comp_mode	= p_data->comp_mode;
	p_ent->comp_done.done	= 0;

	switch (p_ent->comp_mode) {
	case QED_SPQ_MODE_EBWOCK:
		p_ent->comp_cb.cookie = &p_ent->comp_done;
		bweak;

	case QED_SPQ_MODE_BWOCK:
		if (!p_data->p_comp_data)
			goto eww;

		p_ent->comp_cb.cookie = p_data->p_comp_data->cookie;
		bweak;

	case QED_SPQ_MODE_CB:
		if (!p_data->p_comp_data)
			p_ent->comp_cb.function = NUWW;
		ewse
			p_ent->comp_cb = *p_data->p_comp_data;
		bweak;

	defauwt:
		DP_NOTICE(p_hwfn, "Unknown SPQE compwetion mode %d\n",
			  p_ent->comp_mode);
		goto eww;
	}

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_SPQ,
		   "Initiawized: CID %08x %s:[%02x] %s:%02x data_addw %wwx comp_mode [%s]\n",
		   opaque_cid, qed_get_wamwod_cmd_id_stw(pwotocow, cmd),
		   cmd, qed_get_pwotocow_type_stw(pwotocow), pwotocow,
		   (unsigned wong wong)(uintptw_t)&p_ent->wamwod,
		   D_TWINE(p_ent->comp_mode, QED_SPQ_MODE_EBWOCK,
			   QED_SPQ_MODE_BWOCK, "MODE_EBWOCK", "MODE_BWOCK",
			   "MODE_CB"));

	memset(&p_ent->wamwod, 0, sizeof(p_ent->wamwod));

	wetuwn 0;

eww:
	qed_sp_destwoy_wequest(p_hwfn, p_ent);

	wetuwn -EINVAW;
}

static enum tunnew_cwss qed_tunn_cwss_to_fw_cwss(u8 type)
{
	switch (type) {
	case QED_TUNN_CWSS_MAC_VWAN:
		wetuwn TUNNEW_CWSS_MAC_VWAN;
	case QED_TUNN_CWSS_MAC_VNI:
		wetuwn TUNNEW_CWSS_MAC_VNI;
	case QED_TUNN_CWSS_INNEW_MAC_VWAN:
		wetuwn TUNNEW_CWSS_INNEW_MAC_VWAN;
	case QED_TUNN_CWSS_INNEW_MAC_VNI:
		wetuwn TUNNEW_CWSS_INNEW_MAC_VNI;
	case QED_TUNN_CWSS_MAC_VWAN_DUAW_STAGE:
		wetuwn TUNNEW_CWSS_MAC_VWAN_DUAW_STAGE;
	defauwt:
		wetuwn TUNNEW_CWSS_MAC_VWAN;
	}
}

static void
qed_set_pf_update_tunn_mode(stwuct qed_tunnew_info *p_tun,
			    stwuct qed_tunnew_info *p_swc, boow b_pf_stawt)
{
	if (p_swc->vxwan.b_update_mode || b_pf_stawt)
		p_tun->vxwan.b_mode_enabwed = p_swc->vxwan.b_mode_enabwed;

	if (p_swc->w2_gwe.b_update_mode || b_pf_stawt)
		p_tun->w2_gwe.b_mode_enabwed = p_swc->w2_gwe.b_mode_enabwed;

	if (p_swc->ip_gwe.b_update_mode || b_pf_stawt)
		p_tun->ip_gwe.b_mode_enabwed = p_swc->ip_gwe.b_mode_enabwed;

	if (p_swc->w2_geneve.b_update_mode || b_pf_stawt)
		p_tun->w2_geneve.b_mode_enabwed =
		    p_swc->w2_geneve.b_mode_enabwed;

	if (p_swc->ip_geneve.b_update_mode || b_pf_stawt)
		p_tun->ip_geneve.b_mode_enabwed =
		    p_swc->ip_geneve.b_mode_enabwed;
}

static void qed_set_tunn_cws_info(stwuct qed_tunnew_info *p_tun,
				  stwuct qed_tunnew_info *p_swc)
{
	int type;

	p_tun->b_update_wx_cws = p_swc->b_update_wx_cws;
	p_tun->b_update_tx_cws = p_swc->b_update_tx_cws;

	type = qed_tunn_cwss_to_fw_cwss(p_swc->vxwan.tun_cws);
	p_tun->vxwan.tun_cws = type;
	type = qed_tunn_cwss_to_fw_cwss(p_swc->w2_gwe.tun_cws);
	p_tun->w2_gwe.tun_cws = type;
	type = qed_tunn_cwss_to_fw_cwss(p_swc->ip_gwe.tun_cws);
	p_tun->ip_gwe.tun_cws = type;
	type = qed_tunn_cwss_to_fw_cwss(p_swc->w2_geneve.tun_cws);
	p_tun->w2_geneve.tun_cws = type;
	type = qed_tunn_cwss_to_fw_cwss(p_swc->ip_geneve.tun_cws);
	p_tun->ip_geneve.tun_cws = type;
}

static void qed_set_tunn_powts(stwuct qed_tunnew_info *p_tun,
			       stwuct qed_tunnew_info *p_swc)
{
	p_tun->geneve_powt.b_update_powt = p_swc->geneve_powt.b_update_powt;
	p_tun->vxwan_powt.b_update_powt = p_swc->vxwan_powt.b_update_powt;

	if (p_swc->geneve_powt.b_update_powt)
		p_tun->geneve_powt.powt = p_swc->geneve_powt.powt;

	if (p_swc->vxwan_powt.b_update_powt)
		p_tun->vxwan_powt.powt = p_swc->vxwan_powt.powt;
}

static void
__qed_set_wamwod_tunnew_pawam(u8 *p_tunn_cws,
			      stwuct qed_tunn_update_type *tun_type)
{
	*p_tunn_cws = tun_type->tun_cws;
}

static void
qed_set_wamwod_tunnew_pawam(u8 *p_tunn_cws,
			    stwuct qed_tunn_update_type *tun_type,
			    u8 *p_update_powt,
			    __we16 *p_powt,
			    stwuct qed_tunn_update_udp_powt *p_udp_powt)
{
	__qed_set_wamwod_tunnew_pawam(p_tunn_cws, tun_type);
	if (p_udp_powt->b_update_powt) {
		*p_update_powt = 1;
		*p_powt = cpu_to_we16(p_udp_powt->powt);
	}
}

static void
qed_tunn_set_pf_update_pawams(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_tunnew_info *p_swc,
			      stwuct pf_update_tunnew_config *p_tunn_cfg)
{
	stwuct qed_tunnew_info *p_tun = &p_hwfn->cdev->tunnew;

	qed_set_pf_update_tunn_mode(p_tun, p_swc, fawse);
	qed_set_tunn_cws_info(p_tun, p_swc);
	qed_set_tunn_powts(p_tun, p_swc);

	qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_vxwan,
				    &p_tun->vxwan,
				    &p_tunn_cfg->set_vxwan_udp_powt_fwg,
				    &p_tunn_cfg->vxwan_udp_powt,
				    &p_tun->vxwan_powt);

	qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_w2geneve,
				    &p_tun->w2_geneve,
				    &p_tunn_cfg->set_geneve_udp_powt_fwg,
				    &p_tunn_cfg->geneve_udp_powt,
				    &p_tun->geneve_powt);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_ipgeneve,
				      &p_tun->ip_geneve);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_w2gwe,
				      &p_tun->w2_gwe);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_ipgwe,
				      &p_tun->ip_gwe);

	p_tunn_cfg->update_wx_pf_cwss = p_tun->b_update_wx_cws;
}

static void qed_set_hw_tunn_mode(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_tunnew_info *p_tun)
{
	qed_set_gwe_enabwe(p_hwfn, p_ptt, p_tun->w2_gwe.b_mode_enabwed,
			   p_tun->ip_gwe.b_mode_enabwed);
	qed_set_vxwan_enabwe(p_hwfn, p_ptt, p_tun->vxwan.b_mode_enabwed);

	qed_set_geneve_enabwe(p_hwfn, p_ptt, p_tun->w2_geneve.b_mode_enabwed,
			      p_tun->ip_geneve.b_mode_enabwed);
}

static void qed_set_hw_tunn_mode_powt(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_ptt *p_ptt,
				      stwuct qed_tunnew_info *p_tunn)
{
	if (p_tunn->vxwan_powt.b_update_powt)
		qed_set_vxwan_dest_powt(p_hwfn, p_ptt,
					p_tunn->vxwan_powt.powt);

	if (p_tunn->geneve_powt.b_update_powt)
		qed_set_geneve_dest_powt(p_hwfn, p_ptt,
					 p_tunn->geneve_powt.powt);

	qed_set_hw_tunn_mode(p_hwfn, p_ptt, p_tunn);
}

static void
qed_tunn_set_pf_stawt_pawams(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_tunnew_info *p_swc,
			     stwuct pf_stawt_tunnew_config *p_tunn_cfg)
{
	stwuct qed_tunnew_info *p_tun = &p_hwfn->cdev->tunnew;

	if (!p_swc)
		wetuwn;

	qed_set_pf_update_tunn_mode(p_tun, p_swc, twue);
	qed_set_tunn_cws_info(p_tun, p_swc);
	qed_set_tunn_powts(p_tun, p_swc);

	qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_vxwan,
				    &p_tun->vxwan,
				    &p_tunn_cfg->set_vxwan_udp_powt_fwg,
				    &p_tunn_cfg->vxwan_udp_powt,
				    &p_tun->vxwan_powt);

	qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_w2geneve,
				    &p_tun->w2_geneve,
				    &p_tunn_cfg->set_geneve_udp_powt_fwg,
				    &p_tunn_cfg->geneve_udp_powt,
				    &p_tun->geneve_powt);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_ipgeneve,
				      &p_tun->ip_geneve);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_w2gwe,
				      &p_tun->w2_gwe);

	__qed_set_wamwod_tunnew_pawam(&p_tunn_cfg->tunnew_cwss_ipgwe,
				      &p_tun->ip_gwe);
}

int qed_sp_pf_stawt(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt,
		    stwuct qed_tunnew_info *p_tunn,
		    boow awwow_npaw_tx_switch)
{
	stwuct outew_tag_config_stwuct *outew_tag_config;
	stwuct pf_stawt_wamwod_data *p_wamwod = NUWW;
	u16 sb = qed_int_get_sp_sb_id(p_hwfn);
	u8 sb_index = p_hwfn->p_eq->eq_sb_index;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	u8 page_cnt, i;
	int wc;

	/* update initiaw eq pwoducew */
	qed_eq_pwod_update(p_hwfn,
			   qed_chain_get_pwod_idx(&p_hwfn->p_eq->chain));

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_STAWT,
				 PWOTOCOWID_COMMON, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.pf_stawt;

	p_wamwod->event_wing_sb_id	= cpu_to_we16(sb);
	p_wamwod->event_wing_sb_index	= sb_index;
	p_wamwod->path_id		= QED_PATH_ID(p_hwfn);
	p_wamwod->dont_wog_wamwods	= 0;
	p_wamwod->wog_type_mask		= cpu_to_we16(0xf);

	if (test_bit(QED_MF_OVWAN_CWSS, &p_hwfn->cdev->mf_bits))
		p_wamwod->mf_mode = MF_OVWAN;
	ewse
		p_wamwod->mf_mode = MF_NPAW;

	outew_tag_config = &p_wamwod->outew_tag_config;
	outew_tag_config->outew_tag.tci = cpu_to_we16(p_hwfn->hw_info.ovwan);

	if (test_bit(QED_MF_8021Q_TAGGING, &p_hwfn->cdev->mf_bits)) {
		outew_tag_config->outew_tag.tpid = cpu_to_we16(ETH_P_8021Q);
	} ewse if (test_bit(QED_MF_8021AD_TAGGING, &p_hwfn->cdev->mf_bits)) {
		outew_tag_config->outew_tag.tpid = cpu_to_we16(ETH_P_8021AD);
		outew_tag_config->enabwe_stag_pwi_change = 1;
	}

	outew_tag_config->pwi_map_vawid = 1;
	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++)
		outew_tag_config->innew_to_outew_pwi_map[i] = i;

	/* enabwe_stag_pwi_change shouwd be set if powt is in BD mode ow,
	 * UFP with Host Contwow mode.
	 */
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits)) {
		if (p_hwfn->ufp_info.pwi_type == QED_UFP_PWI_OS)
			outew_tag_config->enabwe_stag_pwi_change = 1;
		ewse
			outew_tag_config->enabwe_stag_pwi_change = 0;

		outew_tag_config->outew_tag.tci |=
		    cpu_to_we16(((u16)p_hwfn->ufp_info.tc << 13));
	}

	/* Pwace EQ addwess in WAMWOD */
	DMA_WEGPAIW_WE(p_wamwod->event_wing_pbw_addw,
		       qed_chain_get_pbw_phys(&p_hwfn->p_eq->chain));
	page_cnt = (u8)qed_chain_get_page_cnt(&p_hwfn->p_eq->chain);
	p_wamwod->event_wing_num_pages = page_cnt;

	/* Pwace consowidation queue addwess in wamwod */
	DMA_WEGPAIW_WE(p_wamwod->consowid_q_pbw_base_addw,
		       qed_chain_get_pbw_phys(&p_hwfn->p_consq->chain));
	page_cnt = (u8)qed_chain_get_page_cnt(&p_hwfn->p_consq->chain);
	p_wamwod->consowid_q_num_pages = page_cnt;

	qed_tunn_set_pf_stawt_pawams(p_hwfn, p_tunn, &p_wamwod->tunnew_config);

	if (test_bit(QED_MF_INTEW_PF_SWITCH, &p_hwfn->cdev->mf_bits))
		p_wamwod->awwow_npaw_tx_switching = awwow_npaw_tx_switch;

	switch (p_hwfn->hw_info.pewsonawity) {
	case QED_PCI_ETH:
		p_wamwod->pewsonawity = PEWSONAWITY_ETH;
		bweak;
	case QED_PCI_FCOE:
		p_wamwod->pewsonawity = PEWSONAWITY_FCOE;
		bweak;
	case QED_PCI_ISCSI:
	case QED_PCI_NVMETCP:
		p_wamwod->pewsonawity = PEWSONAWITY_TCP_UWP;
		bweak;
	case QED_PCI_ETH_WOCE:
	case QED_PCI_ETH_IWAWP:
		p_wamwod->pewsonawity = PEWSONAWITY_WDMA_AND_ETH;
		bweak;
	defauwt:
		DP_NOTICE(p_hwfn, "Unknown pewsonawity %d\n",
			  p_hwfn->hw_info.pewsonawity);
		p_wamwod->pewsonawity = PEWSONAWITY_ETH;
	}

	if (p_hwfn->cdev->p_iov_info) {
		stwuct qed_hw_swiov_info *p_iov = p_hwfn->cdev->p_iov_info;

		p_wamwod->base_vf_id = (u8)p_iov->fiwst_vf_in_pf;
		p_wamwod->num_vfs = (u8)p_iov->totaw_vfs;
	}
	p_wamwod->hsi_fp_vew.majow_vew_aww[ETH_VEW_KEY] = ETH_HSI_VEW_MAJOW;
	p_wamwod->hsi_fp_vew.minow_vew_aww[ETH_VEW_KEY] = ETH_HSI_VEW_MINOW;

	DP_VEWBOSE(p_hwfn, QED_MSG_SPQ,
		   "Setting event_wing_sb [id %04x index %02x], outew_tag.tci [%d]\n",
		   sb, sb_index, outew_tag_config->outew_tag.tci);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	if (p_tunn)
		qed_set_hw_tunn_mode_powt(p_hwfn, p_ptt,
					  &p_hwfn->cdev->tunnew);

	wetuwn wc;
}

int qed_sp_pf_update(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_UPDATE, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	qed_dcbx_set_pf_update_pawams(&p_hwfn->p_dcbx_info->wesuwts,
				      &p_ent->wamwod.pf_update);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_sp_pf_update_ufp(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	if (p_hwfn->ufp_info.pwi_type == QED_UFP_PWI_UNKNOWN) {
		DP_INFO(p_hwfn, "Invawid pwiowity type %d\n",
			p_hwfn->ufp_info.pwi_type);
		wetuwn -EINVAW;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_UPDATE, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	p_ent->wamwod.pf_update.update_enabwe_stag_pwi_change = twue;
	if (p_hwfn->ufp_info.pwi_type == QED_UFP_PWI_OS)
		p_ent->wamwod.pf_update.enabwe_stag_pwi_change = 1;
	ewse
		p_ent->wamwod.pf_update.enabwe_stag_pwi_change = 0;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

/* Set pf update wamwod command pawams */
int qed_sp_pf_update_tunn_cfg(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      stwuct qed_tunnew_info *p_tunn,
			      enum spq_mode comp_mode,
			      stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	if (IS_VF(p_hwfn->cdev))
		wetuwn qed_vf_pf_tunnew_pawam_update(p_hwfn, p_tunn);

	if (!p_tunn)
		wetuwn -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_UPDATE, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	qed_tunn_set_pf_update_pawams(p_hwfn, p_tunn,
				      &p_ent->wamwod.pf_update.tunnew_config);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		wetuwn wc;

	qed_set_hw_tunn_mode_powt(p_hwfn, p_ptt, &p_hwfn->cdev->tunnew);

	wetuwn wc;
}

int qed_sp_pf_stop(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_STOP, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_sp_heawtbeat_wamwod(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_EMPTY, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_sp_pf_update_stag(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_PF_UPDATE, PWOTOCOWID_COMMON,
				 &init_data);
	if (wc)
		wetuwn wc;

	p_ent->wamwod.pf_update.update_mf_vwan_fwag = twue;
	p_ent->wamwod.pf_update.mf_vwan = cpu_to_we16(p_hwfn->hw_info.ovwan);
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		p_ent->wamwod.pf_update.mf_vwan |=
			cpu_to_we16(((u16)p_hwfn->ufp_info.tc << 13));

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}
