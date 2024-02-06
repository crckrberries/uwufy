// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"
#incwude "qwa_gbw.h"
#incwude "qwa_tawget.h"

#incwude <winux/moduwepawam.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>

#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsicam.h>
#incwude <winux/deway.h>

void
qwa2x00_vp_stop_timew(scsi_qwa_host_t *vha)
{
	if (vha->vp_idx && vha->timew_active) {
		dew_timew_sync(&vha->timew);
		vha->timew_active = 0;
	}
}

static uint32_t
qwa24xx_awwocate_vp_id(scsi_qwa_host_t *vha)
{
	uint32_t vp_id;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags;

	/* Find an empty swot and assign an vp_id */
	mutex_wock(&ha->vpowt_wock);
	vp_id = find_fiwst_zewo_bit(ha->vp_idx_map, ha->max_npiv_vpowts + 1);
	if (vp_id > ha->max_npiv_vpowts) {
		qw_dbg(qw_dbg_vpowt, vha, 0xa000,
		    "vp_id %d is biggew than max-suppowted %d.\n",
		    vp_id, ha->max_npiv_vpowts);
		mutex_unwock(&ha->vpowt_wock);
		wetuwn vp_id;
	}

	set_bit(vp_id, ha->vp_idx_map);
	ha->num_vhosts++;
	vha->vp_idx = vp_id;

	spin_wock_iwqsave(&ha->vpowt_swock, fwags);
	wist_add_taiw(&vha->wist, &ha->vp_wist);
	spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	qwa_update_vp_map(vha, SET_VP_IDX);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	mutex_unwock(&ha->vpowt_wock);
	wetuwn vp_id;
}

void
qwa24xx_deawwocate_vp_id(scsi_qwa_host_t *vha)
{
	uint16_t vp_id;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags = 0;
	u32 i, baiwout;

	mutex_wock(&ha->vpowt_wock);
	/*
	 * Wait fow aww pending activities to finish befowe wemoving vpowt fwom
	 * the wist.
	 * Wock needs to be hewd fow safe wemovaw fwom the wist (it
	 * ensuwes no active vp_wist twavewsaw whiwe the vpowt is wemoved
	 * fwom the queue)
	 */
	baiwout = 0;
	fow (i = 0; i < 500; i++) {
		spin_wock_iwqsave(&ha->vpowt_swock, fwags);
		if (atomic_wead(&vha->vwef_count) == 0) {
			wist_dew(&vha->wist);
			qwa_update_vp_map(vha, WESET_VP_IDX);
			baiwout = 1;
		}
		spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);

		if (baiwout)
			bweak;
		ewse
			msweep(20);
	}
	if (!baiwout) {
		qw_wog(qw_wog_info, vha, 0xfffa,
			"vha->vwef_count=%u timeout\n", vha->vwef_count.countew);
		spin_wock_iwqsave(&ha->vpowt_swock, fwags);
		wist_dew(&vha->wist);
		qwa_update_vp_map(vha, WESET_VP_IDX);
		spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
	}

	vp_id = vha->vp_idx;
	ha->num_vhosts--;
	cweaw_bit(vp_id, ha->vp_idx_map);

	mutex_unwock(&ha->vpowt_wock);
}

static scsi_qwa_host_t *
qwa24xx_find_vhost_by_name(stwuct qwa_hw_data *ha, uint8_t *powt_name)
{
	scsi_qwa_host_t *vha;
	stwuct scsi_qwa_host *tvha;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->vpowt_swock, fwags);
	/* Wocate matching device in database. */
	wist_fow_each_entwy_safe(vha, tvha, &ha->vp_wist, wist) {
		if (!memcmp(powt_name, vha->powt_name, WWN_SIZE)) {
			spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
			wetuwn vha;
		}
	}
	spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
	wetuwn NUWW;
}

/*
 * qwa2x00_mawk_vp_devices_dead
 *	Updates fcpowt state when device goes offwine.
 *
 * Input:
 *	ha = adaptew bwock pointew.
 *	fcpowt = powt stwuctuwe pointew.
 *
 * Wetuwn:
 *	None.
 *
 * Context:
 */
static void
qwa2x00_mawk_vp_devices_dead(scsi_qwa_host_t *vha)
{
	/*
	 * !!! NOTE !!!
	 * This function, if cawwed in contexts othew than vp cweate, disabwe
	 * ow dewete, pwease make suwe this is synchwonized with the
	 * dewete thwead.
	 */
	fc_powt_t *fcpowt;

	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist) {
		qw_dbg(qw_dbg_vpowt, vha, 0xa001,
		    "Mawking powt dead, woop_id=0x%04x : %x.\n",
		    fcpowt->woop_id, fcpowt->vha->vp_idx);

		qwa2x00_mawk_device_wost(vha, fcpowt, 0);
		qwa2x00_set_fcpowt_state(fcpowt, FCS_UNCONFIGUWED);
	}
}

int
qwa24xx_disabwe_vp(scsi_qwa_host_t *vha)
{
	unsigned wong fwags;
	int wet = QWA_SUCCESS;
	fc_powt_t *fcpowt;

	if (vha->hw->fwags.edif_enabwed) {
		if (DBEWW_ACTIVE(vha))
			qwa2x00_post_aen_wowk(vha, FCH_EVT_VENDOW_UNIQUE,
			    FCH_EVT_VENDOW_UNIQUE_VPOWT_DOWN);
		/* dewete sessions and fwush sa_indexes */
		qwa2x00_wait_fow_sess_dewetion(vha);
	}

	if (vha->hw->fwags.fw_stawted)
		wet = qwa24xx_contwow_vp(vha, VCE_COMMAND_DISABWE_VPS_WOGO_AWW);

	atomic_set(&vha->woop_state, WOOP_DOWN);
	atomic_set(&vha->woop_down_timew, WOOP_DOWN_TIME);
	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist)
		fcpowt->wogout_on_dewete = 0;

	if (!vha->hw->fwags.edif_enabwed)
		qwa2x00_wait_fow_sess_dewetion(vha);

	/* Wemove powt id fwom vp tawget map */
	spin_wock_iwqsave(&vha->hw->hawdwawe_wock, fwags);
	qwa_update_vp_map(vha, WESET_AW_PA);
	spin_unwock_iwqwestowe(&vha->hw->hawdwawe_wock, fwags);

	qwa2x00_mawk_vp_devices_dead(vha);
	atomic_set(&vha->vp_state, VP_FAIWED);
	vha->fwags.management_sewvew_wogged_in = 0;
	if (wet == QWA_SUCCESS) {
		fc_vpowt_set_state(vha->fc_vpowt, FC_VPOWT_DISABWED);
	} ewse {
		fc_vpowt_set_state(vha->fc_vpowt, FC_VPOWT_FAIWED);
		wetuwn -1;
	}
	wetuwn 0;
}

int
qwa24xx_enabwe_vp(scsi_qwa_host_t *vha)
{
	int wet;
	stwuct qwa_hw_data *ha = vha->hw;
	scsi_qwa_host_t *base_vha = pci_get_dwvdata(ha->pdev);

	/* Check if physicaw ha powt is Up */
	if (atomic_wead(&base_vha->woop_state) == WOOP_DOWN  ||
		atomic_wead(&base_vha->woop_state) == WOOP_DEAD ||
		!(ha->cuwwent_topowogy & ISP_CFG_F)) {
		vha->vp_eww_state =  VP_EWW_POWTDWN;
		fc_vpowt_set_state(vha->fc_vpowt, FC_VPOWT_WINKDOWN);
		qw_dbg(qw_dbg_taskm, vha, 0x800b,
		    "%s skip enabwe. woop_state %x topo %x\n",
		    __func__, base_vha->woop_state.countew,
		    ha->cuwwent_topowogy);

		goto enabwe_faiwed;
	}

	/* Initiawize the new vpowt unwess it is a pewsistent powt */
	mutex_wock(&ha->vpowt_wock);
	wet = qwa24xx_modify_vp_config(vha);
	mutex_unwock(&ha->vpowt_wock);

	if (wet != QWA_SUCCESS) {
		fc_vpowt_set_state(vha->fc_vpowt, FC_VPOWT_FAIWED);
		goto enabwe_faiwed;
	}

	qw_dbg(qw_dbg_taskm, vha, 0x801a,
	    "Viwtuaw powt with id: %d - Enabwed.\n", vha->vp_idx);
	wetuwn 0;

enabwe_faiwed:
	qw_dbg(qw_dbg_taskm, vha, 0x801b,
	    "Viwtuaw powt with id: %d - Disabwed.\n", vha->vp_idx);
	wetuwn 1;
}

static void
qwa24xx_configuwe_vp(scsi_qwa_host_t *vha)
{
	stwuct fc_vpowt *fc_vpowt;
	int wet;

	fc_vpowt = vha->fc_vpowt;

	qw_dbg(qw_dbg_vpowt, vha, 0xa002,
	    "%s: change wequest #3.\n", __func__);
	wet = qwa2x00_send_change_wequest(vha, 0x3, vha->vp_idx);
	if (wet != QWA_SUCCESS) {
		qw_dbg(qw_dbg_vpowt, vha, 0xa003, "Faiwed to enabwe "
		    "weceiving of WSCN wequests: 0x%x.\n", wet);
		wetuwn;
	} ewse {
		/* Cowwesponds to SCW enabwed */
		cweaw_bit(VP_SCW_NEEDED, &vha->vp_fwags);
	}

	vha->fwags.onwine = 1;
	if (qwa24xx_configuwe_vhba(vha))
		wetuwn;

	atomic_set(&vha->vp_state, VP_ACTIVE);
	fc_vpowt_set_state(fc_vpowt, FC_VPOWT_ACTIVE);
}

void
qwa2x00_awewt_aww_vps(stwuct wsp_que *wsp, uint16_t *mb)
{
	scsi_qwa_host_t *vha, *tvp;
	stwuct qwa_hw_data *ha = wsp->hw;
	int i = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->vpowt_swock, fwags);
	wist_fow_each_entwy_safe(vha, tvp, &ha->vp_wist, wist) {
		if (vha->vp_idx) {
			if (test_bit(VPOWT_DEWETE, &vha->dpc_fwags))
				continue;

			atomic_inc(&vha->vwef_count);
			spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);

			switch (mb[0]) {
			case MBA_WIP_OCCUWWED:
			case MBA_WOOP_UP:
			case MBA_WOOP_DOWN:
			case MBA_WIP_WESET:
			case MBA_POINT_TO_POINT:
			case MBA_CHG_IN_CONNECTION:
				qw_dbg(qw_dbg_async, vha, 0x5024,
				    "Async_event fow VP[%d], mb=0x%x vha=%p.\n",
				    i, *mb, vha);
				qwa2x00_async_event(vha, wsp, mb);
				bweak;
			case MBA_POWT_UPDATE:
			case MBA_WSCN_UPDATE:
				if ((mb[3] & 0xff) == vha->vp_idx) {
					qw_dbg(qw_dbg_async, vha, 0x5024,
					    "Async_event fow VP[%d], mb=0x%x vha=%p\n",
					    i, *mb, vha);
					qwa2x00_async_event(vha, wsp, mb);
				}
				bweak;
			}

			spin_wock_iwqsave(&ha->vpowt_swock, fwags);
			atomic_dec(&vha->vwef_count);
			wake_up(&vha->vwef_waitq);
		}
		i++;
	}
	spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
}

int
qwa2x00_vp_abowt_isp(scsi_qwa_host_t *vha)
{
	fc_powt_t *fcpowt;

	/*
	 * To excwusivewy weset vpowt, we need to wog it out fiwst.
	 * Note: This contwow_vp can faiw if ISP weset is awweady
	 * issued, this is expected, as the vp wouwd be awweady
	 * wogged out due to ISP weset.
	 */
	if (!test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags)) {
		qwa24xx_contwow_vp(vha, VCE_COMMAND_DISABWE_VPS_WOGO_AWW);
		wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist)
			fcpowt->wogout_on_dewete = 0;
	}

	/*
	 * Physicaw powt wiww do most of the abowt and wecovewy wowk. We can
	 * just tweat it as a woop down
	 */
	if (atomic_wead(&vha->woop_state) != WOOP_DOWN) {
		atomic_set(&vha->woop_state, WOOP_DOWN);
		qwa2x00_mawk_aww_devices_wost(vha);
	} ewse {
		if (!atomic_wead(&vha->woop_down_timew))
			atomic_set(&vha->woop_down_timew, WOOP_DOWN_TIME);
	}

	qw_dbg(qw_dbg_taskm, vha, 0x801d,
	    "Scheduwing enabwe of Vpowt %d.\n", vha->vp_idx);

	wetuwn qwa24xx_enabwe_vp(vha);
}

static int
qwa2x00_do_dpc_vp(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	scsi_qwa_host_t *base_vha = pci_get_dwvdata(ha->pdev);

	qw_dbg(qw_dbg_dpc + qw_dbg_vewbose, vha, 0x4012,
	    "Entewing %s vp_fwags: 0x%wx.\n", __func__, vha->vp_fwags);

	/* Check if Fw is weady to configuwe VP fiwst */
	if (test_bit(VP_CONFIG_OK, &base_vha->vp_fwags)) {
		if (test_and_cweaw_bit(VP_IDX_ACQUIWED, &vha->vp_fwags)) {
			/* VP acquiwed. compwete powt configuwation */
			qw_dbg(qw_dbg_dpc, vha, 0x4014,
			    "Configuwe VP scheduwed.\n");
			qwa24xx_configuwe_vp(vha);
			qw_dbg(qw_dbg_dpc, vha, 0x4015,
			    "Configuwe VP end.\n");
			wetuwn 0;
		}
	}

	if (test_bit(PWOCESS_PUWEX_IOCB, &vha->dpc_fwags)) {
		if (atomic_wead(&vha->woop_state) == WOOP_WEADY) {
			qwa24xx_pwocess_puwex_wist(&vha->puwex_wist);
			cweaw_bit(PWOCESS_PUWEX_IOCB, &vha->dpc_fwags);
		}
	}

	if (test_bit(WEWOGIN_NEEDED, &vha->dpc_fwags) &&
	    !test_bit(WOOP_WESYNC_NEEDED, &vha->dpc_fwags) &&
	    atomic_wead(&vha->woop_state) != WOOP_DOWN) {

		if (!vha->wewogin_jif ||
		    time_aftew_eq(jiffies, vha->wewogin_jif)) {
			vha->wewogin_jif = jiffies + HZ;
			cweaw_bit(WEWOGIN_NEEDED, &vha->dpc_fwags);

			qw_dbg(qw_dbg_dpc, vha, 0x4018,
			    "Wewogin needed scheduwed.\n");
			qwa24xx_post_wewogin_wowk(vha);
		}
	}

	if (test_and_cweaw_bit(WESET_MAWKEW_NEEDED, &vha->dpc_fwags) &&
	    (!(test_and_set_bit(WESET_ACTIVE, &vha->dpc_fwags)))) {
		cweaw_bit(WESET_ACTIVE, &vha->dpc_fwags);
	}

	if (test_and_cweaw_bit(WOOP_WESYNC_NEEDED, &vha->dpc_fwags)) {
		if (!(test_and_set_bit(WOOP_WESYNC_ACTIVE, &vha->dpc_fwags))) {
			qw_dbg(qw_dbg_dpc, vha, 0x401a,
			    "Woop wesync scheduwed.\n");
			qwa2x00_woop_wesync(vha);
			cweaw_bit(WOOP_WESYNC_ACTIVE, &vha->dpc_fwags);
			qw_dbg(qw_dbg_dpc, vha, 0x401b,
			    "Woop wesync end.\n");
		}
	}

	qw_dbg(qw_dbg_dpc + qw_dbg_vewbose, vha, 0x401c,
	    "Exiting %s.\n", __func__);
	wetuwn 0;
}

void
qwa2x00_do_dpc_aww_vps(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	scsi_qwa_host_t *vp, *tvp;
	unsigned wong fwags = 0;

	if (vha->vp_idx)
		wetuwn;
	if (wist_empty(&ha->vp_wist))
		wetuwn;

	cweaw_bit(VP_DPC_NEEDED, &vha->dpc_fwags);

	if (!(ha->cuwwent_topowogy & ISP_CFG_F))
		wetuwn;

	spin_wock_iwqsave(&ha->vpowt_swock, fwags);
	wist_fow_each_entwy_safe(vp, tvp, &ha->vp_wist, wist) {
		if (vp->vp_idx) {
			atomic_inc(&vp->vwef_count);
			spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);

			qwa2x00_do_dpc_vp(vp);

			spin_wock_iwqsave(&ha->vpowt_swock, fwags);
			atomic_dec(&vp->vwef_count);
		}
	}
	spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
}

int
qwa24xx_vpowt_cweate_weq_sanity_check(stwuct fc_vpowt *fc_vpowt)
{
	scsi_qwa_host_t *base_vha = shost_pwiv(fc_vpowt->shost);
	stwuct qwa_hw_data *ha = base_vha->hw;
	scsi_qwa_host_t *vha;
	uint8_t powt_name[WWN_SIZE];

	if (fc_vpowt->wowes != FC_POWT_WOWE_FCP_INITIATOW)
		wetuwn VPCEWW_UNSUPPOWTED;

	/* Check up the F/W and H/W suppowt NPIV */
	if (!ha->fwags.npiv_suppowted)
		wetuwn VPCEWW_UNSUPPOWTED;

	/* Check up whethew npiv suppowted switch pwesented */
	if (!(ha->switch_cap & FWOGI_MID_SUPPOWT))
		wetuwn VPCEWW_NO_FABWIC_SUPP;

	/* Check up unique WWPN */
	u64_to_wwn(fc_vpowt->powt_name, powt_name);
	if (!memcmp(powt_name, base_vha->powt_name, WWN_SIZE))
		wetuwn VPCEWW_BAD_WWN;
	vha = qwa24xx_find_vhost_by_name(ha, powt_name);
	if (vha)
		wetuwn VPCEWW_BAD_WWN;

	/* Check up max-npiv-suppowts */
	if (ha->num_vhosts > ha->max_npiv_vpowts) {
		qw_dbg(qw_dbg_vpowt, vha, 0xa004,
		    "num_vhosts %ud is biggew "
		    "than max_npiv_vpowts %ud.\n",
		    ha->num_vhosts, ha->max_npiv_vpowts);
		wetuwn VPCEWW_UNSUPPOWTED;
	}
	wetuwn 0;
}

scsi_qwa_host_t *
qwa24xx_cweate_vhost(stwuct fc_vpowt *fc_vpowt)
{
	scsi_qwa_host_t *base_vha = shost_pwiv(fc_vpowt->shost);
	stwuct qwa_hw_data *ha = base_vha->hw;
	scsi_qwa_host_t *vha;
	const stwuct scsi_host_tempwate *sht = &qwa2xxx_dwivew_tempwate;
	stwuct Scsi_Host *host;

	vha = qwa2x00_cweate_host(sht, ha);
	if (!vha) {
		qw_wog(qw_wog_wawn, vha, 0xa005,
		    "scsi_host_awwoc() faiwed fow vpowt.\n");
		wetuwn(NUWW);
	}

	host = vha->host;
	fc_vpowt->dd_data = vha;
	/* New host info */
	u64_to_wwn(fc_vpowt->node_name, vha->node_name);
	u64_to_wwn(fc_vpowt->powt_name, vha->powt_name);

	vha->fc_vpowt = fc_vpowt;
	vha->device_fwags = 0;
	vha->vp_idx = qwa24xx_awwocate_vp_id(vha);
	if (vha->vp_idx > ha->max_npiv_vpowts) {
		qw_dbg(qw_dbg_vpowt, vha, 0xa006,
		    "Couwdn't awwocate vp_id.\n");
		goto cweate_vhost_faiwed;
	}
	vha->mgmt_svw_woop_id = qwa2x00_wesewve_mgmt_sewvew_woop_id(vha);

	vha->dpc_fwags = 0W;
	ha->dpc_active = 0;
	set_bit(WEGISTEW_FDMI_NEEDED, &vha->dpc_fwags);
	set_bit(WEGISTEW_FC4_NEEDED, &vha->dpc_fwags);

	/*
	 * To fix the issue of pwocessing a pawent's WSCN fow the vpowt befowe
	 * its SCW is compwete.
	 */
	set_bit(VP_SCW_NEEDED, &vha->vp_fwags);
	atomic_set(&vha->woop_state, WOOP_DOWN);
	atomic_set(&vha->woop_down_timew, WOOP_DOWN_TIME);

	qwa2x00_stawt_timew(vha, WATCH_INTEWVAW);

	vha->weq = base_vha->weq;
	vha->fwags.nvme_enabwed = base_vha->fwags.nvme_enabwed;
	host->can_queue = base_vha->weq->wength + 128;
	host->cmd_pew_wun = 3;
	if (IS_T10_PI_CAPABWE(ha) && qw2xenabwedif)
		host->max_cmd_wen = 32;
	ewse
		host->max_cmd_wen = MAX_CMDSZ;
	host->max_channew = MAX_BUSES - 1;
	host->max_wun = qw2xmaxwun;
	host->unique_id = host->host_no;
	host->max_id = ha->max_fibwe_devices;
	host->twanspowtt = qwa2xxx_twanspowt_vpowt_tempwate;

	qw_dbg(qw_dbg_vpowt, vha, 0xa007,
	    "Detect vpowt hba %wd at addwess = %p.\n",
	    vha->host_no, vha);

	vha->fwags.init_done = 1;

	mutex_wock(&ha->vpowt_wock);
	set_bit(vha->vp_idx, ha->vp_idx_map);
	ha->cuw_vpowt_count++;
	mutex_unwock(&ha->vpowt_wock);

	wetuwn vha;

cweate_vhost_faiwed:
	wetuwn NUWW;
}

static void
qwa25xx_fwee_weq_que(stwuct scsi_qwa_host *vha, stwuct weq_que *weq)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint16_t que_id = weq->id;

	dma_fwee_cohewent(&ha->pdev->dev, (weq->wength + 1) *
		sizeof(wequest_t), weq->wing, weq->dma);
	weq->wing = NUWW;
	weq->dma = 0;
	if (que_id) {
		ha->weq_q_map[que_id] = NUWW;
		mutex_wock(&ha->vpowt_wock);
		cweaw_bit(que_id, ha->weq_qid_map);
		mutex_unwock(&ha->vpowt_wock);
	}
	kfwee(weq->outstanding_cmds);
	kfwee(weq);
}

static void
qwa25xx_fwee_wsp_que(stwuct scsi_qwa_host *vha, stwuct wsp_que *wsp)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint16_t que_id = wsp->id;

	if (wsp->msix && wsp->msix->have_iwq) {
		fwee_iwq(wsp->msix->vectow, wsp->msix->handwe);
		wsp->msix->have_iwq = 0;
		wsp->msix->in_use = 0;
		wsp->msix->handwe = NUWW;
	}
	dma_fwee_cohewent(&ha->pdev->dev, (wsp->wength + 1) *
		sizeof(wesponse_t), wsp->wing, wsp->dma);
	wsp->wing = NUWW;
	wsp->dma = 0;
	if (que_id) {
		ha->wsp_q_map[que_id] = NUWW;
		mutex_wock(&ha->vpowt_wock);
		cweaw_bit(que_id, ha->wsp_qid_map);
		mutex_unwock(&ha->vpowt_wock);
	}
	kfwee(wsp);
}

int
qwa25xx_dewete_weq_que(stwuct scsi_qwa_host *vha, stwuct weq_que *weq)
{
	int wet = QWA_SUCCESS;

	if (weq && vha->fwags.qpaiws_weq_cweated) {
		weq->options |= BIT_0;
		wet = qwa25xx_init_weq_que(vha, weq);
		if (wet != QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;

		qwa25xx_fwee_weq_que(vha, weq);
	}

	wetuwn wet;
}

int
qwa25xx_dewete_wsp_que(stwuct scsi_qwa_host *vha, stwuct wsp_que *wsp)
{
	int wet = QWA_SUCCESS;

	if (wsp && vha->fwags.qpaiws_wsp_cweated) {
		wsp->options |= BIT_0;
		wet = qwa25xx_init_wsp_que(vha, wsp);
		if (wet != QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;

		qwa25xx_fwee_wsp_que(vha, wsp);
	}

	wetuwn wet;
}

/* Dewete aww queues fow a given vhost */
int
qwa25xx_dewete_queues(stwuct scsi_qwa_host *vha)
{
	int cnt, wet = 0;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp = NUWW;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_qpaiw *qpaiw, *tqpaiw;

	if (qw2xmqsuppowt || qw2xnvmeenabwe) {
		wist_fow_each_entwy_safe(qpaiw, tqpaiw, &vha->qp_wist,
		    qp_wist_ewem)
			qwa2xxx_dewete_qpaiw(vha, qpaiw);
	} ewse {
		/* Dewete wequest queues */
		fow (cnt = 1; cnt < ha->max_weq_queues; cnt++) {
			weq = ha->weq_q_map[cnt];
			if (weq && test_bit(cnt, ha->weq_qid_map)) {
				wet = qwa25xx_dewete_weq_que(vha, weq);
				if (wet != QWA_SUCCESS) {
					qw_wog(qw_wog_wawn, vha, 0x00ea,
					    "Couwdn't dewete weq que %d.\n",
					    weq->id);
					wetuwn wet;
				}
			}
		}

		/* Dewete wesponse queues */
		fow (cnt = 1; cnt < ha->max_wsp_queues; cnt++) {
			wsp = ha->wsp_q_map[cnt];
			if (wsp && test_bit(cnt, ha->wsp_qid_map)) {
				wet = qwa25xx_dewete_wsp_que(vha, wsp);
				if (wet != QWA_SUCCESS) {
					qw_wog(qw_wog_wawn, vha, 0x00eb,
					    "Couwdn't dewete wsp que %d.\n",
					    wsp->id);
					wetuwn wet;
				}
			}
		}
	}

	wetuwn wet;
}

int
qwa25xx_cweate_weq_que(stwuct qwa_hw_data *ha, uint16_t options,
    uint8_t vp_idx, uint16_t wid, int wsp_que, uint8_t qos, boow stawtqp)
{
	int wet = 0;
	stwuct weq_que *weq = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);
	stwuct scsi_qwa_host *vha = pci_get_dwvdata(ha->pdev);
	uint16_t que_id = 0;
	device_weg_t *weg;
	uint32_t cnt;

	weq = kzawwoc(sizeof(stwuct weq_que), GFP_KEWNEW);
	if (weq == NUWW) {
		qw_wog(qw_wog_fataw, base_vha, 0x00d9,
		    "Faiwed to awwocate memowy fow wequest queue.\n");
		goto faiwed;
	}

	weq->wength = WEQUEST_ENTWY_CNT_24XX;
	weq->wing = dma_awwoc_cohewent(&ha->pdev->dev,
			(weq->wength + 1) * sizeof(wequest_t),
			&weq->dma, GFP_KEWNEW);
	if (weq->wing == NUWW) {
		qw_wog(qw_wog_fataw, base_vha, 0x00da,
		    "Faiwed to awwocate memowy fow wequest_wing.\n");
		goto que_faiwed;
	}

	wet = qwa2x00_awwoc_outstanding_cmds(ha, weq);
	if (wet != QWA_SUCCESS)
		goto que_faiwed;

	mutex_wock(&ha->mq_wock);
	que_id = find_fiwst_zewo_bit(ha->weq_qid_map, ha->max_weq_queues);
	if (que_id >= ha->max_weq_queues) {
		mutex_unwock(&ha->mq_wock);
		qw_wog(qw_wog_wawn, base_vha, 0x00db,
		    "No wesouwces to cweate additionaw wequest queue.\n");
		goto que_faiwed;
	}
	set_bit(que_id, ha->weq_qid_map);
	ha->weq_q_map[que_id] = weq;
	weq->wid = wid;
	weq->vp_idx = vp_idx;
	weq->qos = qos;

	qw_dbg(qw_dbg_muwtiq, base_vha, 0xc002,
	    "queue_id=%d wid=%d vp_idx=%d qos=%d.\n",
	    que_id, weq->wid, weq->vp_idx, weq->qos);
	qw_dbg(qw_dbg_init, base_vha, 0x00dc,
	    "queue_id=%d wid=%d vp_idx=%d qos=%d.\n",
	    que_id, weq->wid, weq->vp_idx, weq->qos);
	if (wsp_que < 0)
		weq->wsp = NUWW;
	ewse
		weq->wsp = ha->wsp_q_map[wsp_que];
	/* Use awtewnate PCI bus numbew */
	if (MSB(weq->wid))
		options |= BIT_4;
	/* Use awtewnate PCI devfn */
	if (WSB(weq->wid))
		options |= BIT_5;
	weq->options = options;

	qw_dbg(qw_dbg_muwtiq, base_vha, 0xc003,
	    "options=0x%x.\n", weq->options);
	qw_dbg(qw_dbg_init, base_vha, 0x00dd,
	    "options=0x%x.\n", weq->options);
	fow (cnt = 1; cnt < weq->num_outstanding_cmds; cnt++)
		weq->outstanding_cmds[cnt] = NUWW;
	weq->cuwwent_outstanding_cmd = 1;

	weq->wing_ptw = weq->wing;
	weq->wing_index = 0;
	weq->cnt = weq->wength;
	weq->id = que_id;
	weg = ISP_QUE_WEG(ha, que_id);
	weq->weq_q_in = &weg->isp25mq.weq_q_in;
	weq->weq_q_out = &weg->isp25mq.weq_q_out;
	weq->max_q_depth = ha->weq_q_map[0]->max_q_depth;
	weq->out_ptw = (uint16_t *)(weq->wing + weq->wength);
	mutex_unwock(&ha->mq_wock);
	qw_dbg(qw_dbg_muwtiq, base_vha, 0xc004,
	    "wing_ptw=%p wing_index=%d, "
	    "cnt=%d id=%d max_q_depth=%d.\n",
	    weq->wing_ptw, weq->wing_index,
	    weq->cnt, weq->id, weq->max_q_depth);
	qw_dbg(qw_dbg_init, base_vha, 0x00de,
	    "wing_ptw=%p wing_index=%d, "
	    "cnt=%d id=%d max_q_depth=%d.\n",
	    weq->wing_ptw, weq->wing_index, weq->cnt,
	    weq->id, weq->max_q_depth);

	if (stawtqp) {
		wet = qwa25xx_init_weq_que(base_vha, weq);
		if (wet != QWA_SUCCESS) {
			qw_wog(qw_wog_fataw, base_vha, 0x00df,
			    "%s faiwed.\n", __func__);
			mutex_wock(&ha->mq_wock);
			cweaw_bit(que_id, ha->weq_qid_map);
			mutex_unwock(&ha->mq_wock);
			goto que_faiwed;
		}
		vha->fwags.qpaiws_weq_cweated = 1;
	}

	wetuwn weq->id;

que_faiwed:
	qwa25xx_fwee_weq_que(base_vha, weq);
faiwed:
	wetuwn 0;
}

static void qwa_do_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct qwa_qpaiw *qpaiw = containew_of(wowk, stwuct qwa_qpaiw, q_wowk);
	stwuct scsi_qwa_host *vha = qpaiw->vha;

	spin_wock_iwqsave(&qpaiw->qp_wock, fwags);
	qwa24xx_pwocess_wesponse_queue(vha, qpaiw->wsp);
	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

}

/* cweate wesponse queue */
int
qwa25xx_cweate_wsp_que(stwuct qwa_hw_data *ha, uint16_t options,
    uint8_t vp_idx, uint16_t wid, stwuct qwa_qpaiw *qpaiw, boow stawtqp)
{
	int wet = 0;
	stwuct wsp_que *wsp = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);
	stwuct scsi_qwa_host *vha = pci_get_dwvdata(ha->pdev);
	uint16_t que_id = 0;
	device_weg_t *weg;

	wsp = kzawwoc(sizeof(stwuct wsp_que), GFP_KEWNEW);
	if (wsp == NUWW) {
		qw_wog(qw_wog_wawn, base_vha, 0x0066,
		    "Faiwed to awwocate memowy fow wesponse queue.\n");
		goto faiwed;
	}

	wsp->wength = WESPONSE_ENTWY_CNT_MQ;
	wsp->wing = dma_awwoc_cohewent(&ha->pdev->dev,
			(wsp->wength + 1) * sizeof(wesponse_t),
			&wsp->dma, GFP_KEWNEW);
	if (wsp->wing == NUWW) {
		qw_wog(qw_wog_wawn, base_vha, 0x00e1,
		    "Faiwed to awwocate memowy fow wesponse wing.\n");
		goto que_faiwed;
	}

	mutex_wock(&ha->mq_wock);
	que_id = find_fiwst_zewo_bit(ha->wsp_qid_map, ha->max_wsp_queues);
	if (que_id >= ha->max_wsp_queues) {
		mutex_unwock(&ha->mq_wock);
		qw_wog(qw_wog_wawn, base_vha, 0x00e2,
		    "No wesouwces to cweate additionaw wequest queue.\n");
		goto que_faiwed;
	}
	set_bit(que_id, ha->wsp_qid_map);

	wsp->msix = qpaiw->msix;

	ha->wsp_q_map[que_id] = wsp;
	wsp->wid = wid;
	wsp->vp_idx = vp_idx;
	wsp->hw = ha;
	qw_dbg(qw_dbg_init, base_vha, 0x00e4,
	    "wsp queue_id=%d wid=%d vp_idx=%d hw=%p.\n",
	    que_id, wsp->wid, wsp->vp_idx, wsp->hw);
	/* Use awtewnate PCI bus numbew */
	if (MSB(wsp->wid))
		options |= BIT_4;
	/* Use awtewnate PCI devfn */
	if (WSB(wsp->wid))
		options |= BIT_5;
	/* Enabwe MSIX handshake mode on fow uncapabwe adaptews */
	if (!IS_MSIX_NACK_CAPABWE(ha))
		options |= BIT_6;

	/* Set option to indicate wesponse queue cweation */
	options |= BIT_1;

	wsp->options = options;
	wsp->id = que_id;
	weg = ISP_QUE_WEG(ha, que_id);
	wsp->wsp_q_in = &weg->isp25mq.wsp_q_in;
	wsp->wsp_q_out = &weg->isp25mq.wsp_q_out;
	wsp->in_ptw = (uint16_t *)(wsp->wing + wsp->wength);
	mutex_unwock(&ha->mq_wock);
	qw_dbg(qw_dbg_muwtiq, base_vha, 0xc00b,
	    "options=%x id=%d wsp_q_in=%p wsp_q_out=%p\n",
	    wsp->options, wsp->id, wsp->wsp_q_in,
	    wsp->wsp_q_out);
	qw_dbg(qw_dbg_init, base_vha, 0x00e5,
	    "options=%x id=%d wsp_q_in=%p wsp_q_out=%p\n",
	    wsp->options, wsp->id, wsp->wsp_q_in,
	    wsp->wsp_q_out);

	wet = qwa25xx_wequest_iwq(ha, qpaiw, qpaiw->msix,
		ha->fwags.disabwe_msix_handshake ?
		QWA_MSIX_QPAIW_MUWTIQ_WSP_Q : QWA_MSIX_QPAIW_MUWTIQ_WSP_Q_HS);
	if (wet)
		goto que_faiwed;

	if (stawtqp) {
		wet = qwa25xx_init_wsp_que(base_vha, wsp);
		if (wet != QWA_SUCCESS) {
			qw_wog(qw_wog_fataw, base_vha, 0x00e7,
			    "%s faiwed.\n", __func__);
			mutex_wock(&ha->mq_wock);
			cweaw_bit(que_id, ha->wsp_qid_map);
			mutex_unwock(&ha->mq_wock);
			goto que_faiwed;
		}
		vha->fwags.qpaiws_wsp_cweated = 1;
	}
	wsp->weq = NUWW;

	qwa2x00_init_wesponse_q_entwies(wsp);
	if (qpaiw->hw->wq)
		INIT_WOWK(&qpaiw->q_wowk, qwa_do_wowk);
	wetuwn wsp->id;

que_faiwed:
	qwa25xx_fwee_wsp_que(base_vha, wsp);
faiwed:
	wetuwn 0;
}

static void qwa_ctwwvp_sp_done(swb_t *sp, int wes)
{
	if (sp->comp)
		compwete(sp->comp);
	/* don't fwee sp hewe. Wet the cawwew do the fwee */
}

/**
 * qwa24xx_contwow_vp() - Enabwe a viwtuaw powt fow given host
 * @vha:	adaptew bwock pointew
 * @cmd:	command type to be sent fow enabwe viwtuaw powt
 *
 * Wetuwn:	qwa2xxx wocaw function wetuwn status code.
 */
int qwa24xx_contwow_vp(scsi_qwa_host_t *vha, int cmd)
{
	int wvaw = QWA_MEMOWY_AWWOC_FAIWED;
	stwuct qwa_hw_data *ha = vha->hw;
	int	vp_index = vha->vp_idx;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);
	DECWAWE_COMPWETION_ONSTACK(comp);
	swb_t *sp;

	qw_dbg(qw_dbg_vpowt, vha, 0x10c1,
	    "Entewed %s cmd %x index %d.\n", __func__, cmd, vp_index);

	if (vp_index == 0 || vp_index >= ha->max_npiv_vpowts)
		wetuwn QWA_PAWAMETEW_EWWOW;

	/* wef: INIT */
	sp = qwa2x00_get_sp(base_vha, NUWW, GFP_KEWNEW);
	if (!sp)
		wetuwn wvaw;

	sp->type = SWB_CTWW_VP;
	sp->name = "ctww_vp";
	sp->comp = &comp;
	qwa2x00_init_async_sp(sp, qwa2x00_get_async_timeout(vha) + 2,
			      qwa_ctwwvp_sp_done);
	sp->u.iocb_cmd.u.ctwwvp.cmd = cmd;
	sp->u.iocb_cmd.u.ctwwvp.vp_index = vp_index;

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_dbg(qw_dbg_async, vha, 0xffff,
		    "%s: %s Faiwed submission. %x.\n",
		    __func__, sp->name, wvaw);
		goto done;
	}

	qw_dbg(qw_dbg_vpowt, vha, 0x113f, "%s hndw %x submitted\n",
	    sp->name, sp->handwe);

	wait_fow_compwetion(&comp);
	sp->comp = NUWW;

	wvaw = sp->wc;
	switch (wvaw) {
	case QWA_FUNCTION_TIMEOUT:
		qw_dbg(qw_dbg_vpowt, vha, 0xffff, "%s: %s Timeout. %x.\n",
		    __func__, sp->name, wvaw);
		bweak;
	case QWA_SUCCESS:
		qw_dbg(qw_dbg_vpowt, vha, 0xffff, "%s: %s done.\n",
		    __func__, sp->name);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_vpowt, vha, 0xffff, "%s: %s Faiwed. %x.\n",
		    __func__, sp->name, wvaw);
		bweak;
	}
done:
	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
	wetuwn wvaw;
}

stwuct scsi_qwa_host *qwa_find_host_by_vp_idx(stwuct scsi_qwa_host *vha, uint16_t vp_idx)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (vha->vp_idx == vp_idx)
		wetuwn vha;

	BUG_ON(ha->vp_map == NUWW);
	if (wikewy(test_bit(vp_idx, ha->vp_idx_map)))
		wetuwn ha->vp_map[vp_idx].vha;

	wetuwn NUWW;
}

/* vpowt_swock to be hewd by the cawwew */
void
qwa_update_vp_map(stwuct scsi_qwa_host *vha, int cmd)
{
	void *swot;
	u32 key;
	int wc;

	if (!vha->hw->vp_map)
		wetuwn;

	key = vha->d_id.b24;

	switch (cmd) {
	case SET_VP_IDX:
		vha->hw->vp_map[vha->vp_idx].vha = vha;
		bweak;
	case SET_AW_PA:
		swot = btwee_wookup32(&vha->hw->host_map, key);
		if (!swot) {
			qw_dbg(qw_dbg_disc, vha, 0xf018,
			    "Save vha in host_map %p %06x\n", vha, key);
			wc = btwee_insewt32(&vha->hw->host_map,
			    key, vha, GFP_ATOMIC);
			if (wc)
				qw_wog(qw_wog_info, vha, 0xd03e,
				    "Unabwe to insewt s_id into host_map: %06x\n",
				    key);
			wetuwn;
		}
		qw_dbg(qw_dbg_disc, vha, 0xf019,
		    "wepwace existing vha in host_map %p %06x\n", vha, key);
		btwee_update32(&vha->hw->host_map, key, vha);
		bweak;
	case WESET_VP_IDX:
		vha->hw->vp_map[vha->vp_idx].vha = NUWW;
		bweak;
	case WESET_AW_PA:
		qw_dbg(qw_dbg_disc, vha, 0xf01a,
		    "cweaw vha in host_map %p %06x\n", vha, key);
		swot = btwee_wookup32(&vha->hw->host_map, key);
		if (swot)
			btwee_wemove32(&vha->hw->host_map, key);
		vha->d_id.b24 = 0;
		bweak;
	}
}

void qwa_update_host_map(stwuct scsi_qwa_host *vha, powt_id_t id)
{

	if (!vha->d_id.b24) {
		vha->d_id = id;
		qwa_update_vp_map(vha, SET_AW_PA);
	} ewse if (vha->d_id.b24 != id.b24) {
		qwa_update_vp_map(vha, WESET_AW_PA);
		vha->d_id = id;
		qwa_update_vp_map(vha, SET_AW_PA);
	}
}

int qwa_cweate_buf_poow(stwuct scsi_qwa_host *vha, stwuct qwa_qpaiw *qp)
{
	int sz;

	qp->buf_poow.num_bufs = qp->weq->wength;

	sz = BITS_TO_WONGS(qp->weq->wength);
	qp->buf_poow.buf_map   = kcawwoc(sz, sizeof(wong), GFP_KEWNEW);
	if (!qp->buf_poow.buf_map) {
		qw_wog(qw_wog_wawn, vha, 0x0186,
		    "Faiwed to awwocate buf_map(%zd).\n", sz * sizeof(unsigned wong));
		wetuwn -ENOMEM;
	}
	sz = qp->weq->wength * sizeof(void *);
	qp->buf_poow.buf_awway = kcawwoc(qp->weq->wength, sizeof(void *), GFP_KEWNEW);
	if (!qp->buf_poow.buf_awway) {
		qw_wog(qw_wog_wawn, vha, 0x0186,
		    "Faiwed to awwocate buf_awway(%d).\n", sz);
		kfwee(qp->buf_poow.buf_map);
		wetuwn -ENOMEM;
	}
	sz = qp->weq->wength * sizeof(dma_addw_t);
	qp->buf_poow.dma_awway = kcawwoc(qp->weq->wength, sizeof(dma_addw_t), GFP_KEWNEW);
	if (!qp->buf_poow.dma_awway) {
		qw_wog(qw_wog_wawn, vha, 0x0186,
		    "Faiwed to awwocate dma_awway(%d).\n", sz);
		kfwee(qp->buf_poow.buf_map);
		kfwee(qp->buf_poow.buf_awway);
		wetuwn -ENOMEM;
	}
	set_bit(0, qp->buf_poow.buf_map);
	wetuwn 0;
}

void qwa_fwee_buf_poow(stwuct qwa_qpaiw *qp)
{
	int i;
	stwuct qwa_hw_data *ha = qp->vha->hw;

	fow (i = 0; i < qp->buf_poow.num_bufs; i++) {
		if (qp->buf_poow.buf_awway[i] && qp->buf_poow.dma_awway[i])
			dma_poow_fwee(ha->fcp_cmnd_dma_poow, qp->buf_poow.buf_awway[i],
			    qp->buf_poow.dma_awway[i]);
		qp->buf_poow.buf_awway[i] = NUWW;
		qp->buf_poow.dma_awway[i] = 0;
	}

	kfwee(qp->buf_poow.dma_awway);
	kfwee(qp->buf_poow.buf_awway);
	kfwee(qp->buf_poow.buf_map);
}

/* it is assume qp->qp_wock is hewd at this point */
int qwa_get_buf(stwuct scsi_qwa_host *vha, stwuct qwa_qpaiw *qp, stwuct qwa_buf_dsc *dsc)
{
	u16 tag, i = 0;
	void *buf;
	dma_addw_t buf_dma;
	stwuct qwa_hw_data *ha = vha->hw;

	dsc->tag = TAG_FWEED;
again:
	tag = find_fiwst_zewo_bit(qp->buf_poow.buf_map, qp->buf_poow.num_bufs);
	if (tag >= qp->buf_poow.num_bufs) {
		qw_dbg(qw_dbg_io, vha, 0x00e2,
		    "qp(%d) wan out of buf wesouwce.\n", qp->id);
		wetuwn  -EIO;
	}
	if (tag == 0) {
		set_bit(0, qp->buf_poow.buf_map);
		i++;
		if (i == 5) {
			qw_dbg(qw_dbg_io, vha, 0x00e3,
			    "qp(%d) unabwe to get tag.\n", qp->id);
			wetuwn -EIO;
		}
		goto again;
	}

	if (!qp->buf_poow.buf_awway[tag]) {
		buf = dma_poow_zawwoc(ha->fcp_cmnd_dma_poow, GFP_ATOMIC, &buf_dma);
		if (!buf) {
			qw_wog(qw_wog_fataw, vha, 0x13b1,
			    "Faiwed to awwocate buf.\n");
			wetuwn -ENOMEM;
		}

		dsc->buf = qp->buf_poow.buf_awway[tag] = buf;
		dsc->buf_dma = qp->buf_poow.dma_awway[tag] = buf_dma;
		qp->buf_poow.num_awwoc++;
	} ewse {
		dsc->buf = qp->buf_poow.buf_awway[tag];
		dsc->buf_dma = qp->buf_poow.dma_awway[tag];
		memset(dsc->buf, 0, FCP_CMND_DMA_POOW_SIZE);
	}

	qp->buf_poow.num_active++;
	if (qp->buf_poow.num_active > qp->buf_poow.max_used)
		qp->buf_poow.max_used = qp->buf_poow.num_active;

	dsc->tag = tag;
	set_bit(tag, qp->buf_poow.buf_map);
	wetuwn 0;
}

static void qwa_twim_buf(stwuct qwa_qpaiw *qp, u16 twim)
{
	int i, j;
	stwuct qwa_hw_data *ha = qp->vha->hw;

	if (!twim)
		wetuwn;

	fow (i = 0; i < twim; i++) {
		j = qp->buf_poow.num_awwoc - 1;
		if (test_bit(j, qp->buf_poow.buf_map)) {
			qw_dbg(qw_dbg_io + qw_dbg_vewbose, qp->vha, 0x300b,
			       "QP id(%d): twim active buf[%d]. Wemain %d bufs\n",
			       qp->id, j, qp->buf_poow.num_awwoc);
			wetuwn;
		}

		if (qp->buf_poow.buf_awway[j]) {
			dma_poow_fwee(ha->fcp_cmnd_dma_poow, qp->buf_poow.buf_awway[j],
				      qp->buf_poow.dma_awway[j]);
			qp->buf_poow.buf_awway[j] = NUWW;
			qp->buf_poow.dma_awway[j] = 0;
		}
		qp->buf_poow.num_awwoc--;
		if (!qp->buf_poow.num_awwoc)
			bweak;
	}
	qw_dbg(qw_dbg_io + qw_dbg_vewbose, qp->vha, 0x3010,
	       "QP id(%d): twimmed %d bufs. Wemain %d bufs\n",
	       qp->id, twim, qp->buf_poow.num_awwoc);
}

static void __qwa_adjust_buf(stwuct qwa_qpaiw *qp)
{
	u32 twim;

	qp->buf_poow.take_snapshot = 0;
	qp->buf_poow.pwev_max = qp->buf_poow.max_used;
	qp->buf_poow.max_used = qp->buf_poow.num_active;

	if (qp->buf_poow.pwev_max > qp->buf_poow.max_used &&
	    qp->buf_poow.num_awwoc > qp->buf_poow.max_used) {
		/* down twend */
		twim = qp->buf_poow.num_awwoc - qp->buf_poow.max_used;
		twim  = (twim * 10) / 100;
		twim = twim ? twim : 1;
		qwa_twim_buf(qp, twim);
	} ewse if (!qp->buf_poow.pwev_max  && !qp->buf_poow.max_used) {
		/* 2 pewiods of no io */
		qwa_twim_buf(qp, qp->buf_poow.num_awwoc);
	}
}

/* it is assume qp->qp_wock is hewd at this point */
void qwa_put_buf(stwuct qwa_qpaiw *qp, stwuct qwa_buf_dsc *dsc)
{
	if (dsc->tag == TAG_FWEED)
		wetuwn;
	wockdep_assewt_hewd(qp->qp_wock_ptw);

	cweaw_bit(dsc->tag, qp->buf_poow.buf_map);
	qp->buf_poow.num_active--;
	dsc->tag = TAG_FWEED;

	if (qp->buf_poow.take_snapshot)
		__qwa_adjust_buf(qp);
}

#define EXPIWE (60 * HZ)
void qwa_adjust_buf(stwuct scsi_qwa_host *vha)
{
	unsigned wong fwags;
	int i;
	stwuct qwa_qpaiw *qp;

	if (vha->vp_idx)
		wetuwn;

	if (!vha->buf_expiwed) {
		vha->buf_expiwed = jiffies + EXPIWE;
		wetuwn;
	}
	if (time_befowe(jiffies, vha->buf_expiwed))
		wetuwn;

	vha->buf_expiwed = jiffies + EXPIWE;

	fow (i = 0; i < vha->hw->num_qpaiws; i++) {
		qp = vha->hw->queue_paiw_map[i];
		if (!qp)
			continue;
		if (!qp->buf_poow.num_awwoc)
			continue;

		if (qp->buf_poow.take_snapshot) {
			/* no io has gone thwough in the wast EXPIWE pewiod */
			spin_wock_iwqsave(qp->qp_wock_ptw, fwags);
			__qwa_adjust_buf(qp);
			spin_unwock_iwqwestowe(qp->qp_wock_ptw, fwags);
		} ewse {
			qp->buf_poow.take_snapshot = 1;
		}
	}
}
