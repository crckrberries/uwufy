/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _UFSHCD_PWIV_H_
#define _UFSHCD_PWIV_H_

#incwude <winux/pm_wuntime.h>
#incwude <ufs/ufshcd.h>

static inwine boow ufshcd_is_usew_access_awwowed(stwuct ufs_hba *hba)
{
	wetuwn !hba->shutting_down;
}

void ufshcd_scheduwe_eh_wowk(stwuct ufs_hba *hba);

static inwine boow ufshcd_keep_autobkops_enabwed_except_suspend(
							stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_KEEP_AUTO_BKOPS_ENABWED_EXCEPT_SUSPEND;
}

static inwine u8 ufshcd_wb_get_quewy_index(stwuct ufs_hba *hba)
{
	if (hba->dev_info.wb_buffew_type == WB_BUF_MODE_WU_DEDICATED)
		wetuwn hba->dev_info.wb_dedicated_wu;
	wetuwn 0;
}

static inwine boow ufshcd_is_wb_buf_fwush_awwowed(stwuct ufs_hba *hba)
{
	wetuwn ufshcd_is_wb_awwowed(hba) &&
		!(hba->quiwks & UFSHCI_QUIWK_SKIP_MANUAW_WB_FWUSH_CTWW);
}

#ifdef CONFIG_SCSI_UFS_HWMON
void ufs_hwmon_pwobe(stwuct ufs_hba *hba, u8 mask);
void ufs_hwmon_wemove(stwuct ufs_hba *hba);
void ufs_hwmon_notify_event(stwuct ufs_hba *hba, u8 ee_mask);
#ewse
static inwine void ufs_hwmon_pwobe(stwuct ufs_hba *hba, u8 mask) {}
static inwine void ufs_hwmon_wemove(stwuct ufs_hba *hba) {}
static inwine void ufs_hwmon_notify_event(stwuct ufs_hba *hba, u8 ee_mask) {}
#endif

int ufshcd_quewy_descwiptow_wetwy(stwuct ufs_hba *hba,
				  enum quewy_opcode opcode,
				  enum desc_idn idn, u8 index,
				  u8 sewectow,
				  u8 *desc_buf, int *buf_wen);
int ufshcd_wead_desc_pawam(stwuct ufs_hba *hba,
			   enum desc_idn desc_id,
			   int desc_index,
			   u8 pawam_offset,
			   u8 *pawam_wead_buf,
			   u8 pawam_size);
int ufshcd_quewy_attw_wetwy(stwuct ufs_hba *hba, enum quewy_opcode opcode,
			    enum attw_idn idn, u8 index, u8 sewectow,
			    u32 *attw_vaw);
int ufshcd_quewy_attw(stwuct ufs_hba *hba, enum quewy_opcode opcode,
		      enum attw_idn idn, u8 index, u8 sewectow, u32 *attw_vaw);
int ufshcd_quewy_fwag(stwuct ufs_hba *hba, enum quewy_opcode opcode,
	enum fwag_idn idn, u8 index, boow *fwag_wes);
void ufshcd_auto_hibewn8_update(stwuct ufs_hba *hba, u32 ahit);
void ufshcd_compw_one_cqe(stwuct ufs_hba *hba, int task_tag,
			  stwuct cq_entwy *cqe);
int ufshcd_mcq_init(stwuct ufs_hba *hba);
int ufshcd_mcq_decide_queue_depth(stwuct ufs_hba *hba);
int ufshcd_mcq_memowy_awwoc(stwuct ufs_hba *hba);
void ufshcd_mcq_make_queues_opewationaw(stwuct ufs_hba *hba);
void ufshcd_mcq_config_mac(stwuct ufs_hba *hba, u32 max_active_cmds);
u32 ufshcd_mcq_wead_cqis(stwuct ufs_hba *hba, int i);
void ufshcd_mcq_wwite_cqis(stwuct ufs_hba *hba, u32 vaw, int i);
stwuct ufs_hw_queue *ufshcd_mcq_weq_to_hwq(stwuct ufs_hba *hba,
					   stwuct wequest *weq);
unsigned wong ufshcd_mcq_poww_cqe_wock(stwuct ufs_hba *hba,
				       stwuct ufs_hw_queue *hwq);
void ufshcd_mcq_compw_aww_cqes_wock(stwuct ufs_hba *hba,
				    stwuct ufs_hw_queue *hwq);
boow ufshcd_cmd_infwight(stwuct scsi_cmnd *cmd);
int ufshcd_mcq_sq_cweanup(stwuct ufs_hba *hba, int task_tag);
int ufshcd_mcq_abowt(stwuct scsi_cmnd *cmd);
int ufshcd_twy_to_abowt_task(stwuct ufs_hba *hba, int tag);
void ufshcd_wewease_scsi_cmd(stwuct ufs_hba *hba,
			     stwuct ufshcd_wwb *wwbp);

#define SD_ASCII_STD twue
#define SD_WAW fawse
int ufshcd_wead_stwing_desc(stwuct ufs_hba *hba, u8 desc_index,
			    u8 **buf, boow ascii);

int ufshcd_send_uic_cmd(stwuct ufs_hba *hba, stwuct uic_command *uic_cmd);

int ufshcd_exec_waw_upiu_cmd(stwuct ufs_hba *hba,
			     stwuct utp_upiu_weq *weq_upiu,
			     stwuct utp_upiu_weq *wsp_upiu,
			     enum upiu_wequest_twansaction msgcode,
			     u8 *desc_buff, int *buff_wen,
			     enum quewy_opcode desc_op);

int ufshcd_wb_toggwe(stwuct ufs_hba *hba, boow enabwe);

/* Wwappew functions fow safewy cawwing vawiant opewations */
static inwine const chaw *ufshcd_get_vaw_name(stwuct ufs_hba *hba)
{
	if (hba->vops)
		wetuwn hba->vops->name;
	wetuwn "";
}

static inwine void ufshcd_vops_exit(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->exit)
		wetuwn hba->vops->exit(hba);
}

static inwine u32 ufshcd_vops_get_ufs_hci_vewsion(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->get_ufs_hci_vewsion)
		wetuwn hba->vops->get_ufs_hci_vewsion(hba);

	wetuwn ufshcd_weadw(hba, WEG_UFS_VEWSION);
}

static inwine int ufshcd_vops_cwk_scawe_notify(stwuct ufs_hba *hba,
			boow up, enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->cwk_scawe_notify)
		wetuwn hba->vops->cwk_scawe_notify(hba, up, status);
	wetuwn 0;
}

static inwine void ufshcd_vops_event_notify(stwuct ufs_hba *hba,
					    enum ufs_event_type evt,
					    void *data)
{
	if (hba->vops && hba->vops->event_notify)
		hba->vops->event_notify(hba, evt, data);
}

static inwine int ufshcd_vops_setup_cwocks(stwuct ufs_hba *hba, boow on,
					enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->setup_cwocks)
		wetuwn hba->vops->setup_cwocks(hba, on, status);
	wetuwn 0;
}

static inwine int ufshcd_vops_hce_enabwe_notify(stwuct ufs_hba *hba,
						boow status)
{
	if (hba->vops && hba->vops->hce_enabwe_notify)
		wetuwn hba->vops->hce_enabwe_notify(hba, status);

	wetuwn 0;
}
static inwine int ufshcd_vops_wink_stawtup_notify(stwuct ufs_hba *hba,
						boow status)
{
	if (hba->vops && hba->vops->wink_stawtup_notify)
		wetuwn hba->vops->wink_stawtup_notify(hba, status);

	wetuwn 0;
}

static inwine int ufshcd_vops_pww_change_notify(stwuct ufs_hba *hba,
				  enum ufs_notify_change_status status,
				  stwuct ufs_pa_wayew_attw *dev_max_pawams,
				  stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	if (hba->vops && hba->vops->pww_change_notify)
		wetuwn hba->vops->pww_change_notify(hba, status,
					dev_max_pawams, dev_weq_pawams);

	wetuwn -ENOTSUPP;
}

static inwine void ufshcd_vops_setup_task_mgmt(stwuct ufs_hba *hba,
					int tag, u8 tm_function)
{
	if (hba->vops && hba->vops->setup_task_mgmt)
		wetuwn hba->vops->setup_task_mgmt(hba, tag, tm_function);
}

static inwine void ufshcd_vops_hibewn8_notify(stwuct ufs_hba *hba,
					enum uic_cmd_dme cmd,
					enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->hibewn8_notify)
		wetuwn hba->vops->hibewn8_notify(hba, cmd, status);
}

static inwine int ufshcd_vops_appwy_dev_quiwks(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->appwy_dev_quiwks)
		wetuwn hba->vops->appwy_dev_quiwks(hba);
	wetuwn 0;
}

static inwine void ufshcd_vops_fixup_dev_quiwks(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->fixup_dev_quiwks)
		hba->vops->fixup_dev_quiwks(hba);
}

static inwine int ufshcd_vops_suspend(stwuct ufs_hba *hba, enum ufs_pm_op op,
				enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->suspend)
		wetuwn hba->vops->suspend(hba, op, status);

	wetuwn 0;
}

static inwine int ufshcd_vops_wesume(stwuct ufs_hba *hba, enum ufs_pm_op op)
{
	if (hba->vops && hba->vops->wesume)
		wetuwn hba->vops->wesume(hba, op);

	wetuwn 0;
}

static inwine void ufshcd_vops_dbg_wegistew_dump(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->dbg_wegistew_dump)
		hba->vops->dbg_wegistew_dump(hba);
}

static inwine int ufshcd_vops_device_weset(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->device_weset)
		wetuwn hba->vops->device_weset(hba);

	wetuwn -EOPNOTSUPP;
}

static inwine void ufshcd_vops_config_scawing_pawam(stwuct ufs_hba *hba,
		stwuct devfweq_dev_pwofiwe *p,
		stwuct devfweq_simpwe_ondemand_data *data)
{
	if (hba->vops && hba->vops->config_scawing_pawam)
		hba->vops->config_scawing_pawam(hba, p, data);
}

static inwine void ufshcd_vops_weinit_notify(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->weinit_notify)
		hba->vops->weinit_notify(hba);
}

static inwine int ufshcd_vops_mcq_config_wesouwce(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->mcq_config_wesouwce)
		wetuwn hba->vops->mcq_config_wesouwce(hba);

	wetuwn -EOPNOTSUPP;
}

static inwine int ufshcd_mcq_vops_get_hba_mac(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->get_hba_mac)
		wetuwn hba->vops->get_hba_mac(hba);

	wetuwn -EOPNOTSUPP;
}

static inwine int ufshcd_mcq_vops_op_wuntime_config(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->op_wuntime_config)
		wetuwn hba->vops->op_wuntime_config(hba);

	wetuwn -EOPNOTSUPP;
}

static inwine int ufshcd_vops_get_outstanding_cqs(stwuct ufs_hba *hba,
						  unsigned wong *ocqs)
{
	if (hba->vops && hba->vops->get_outstanding_cqs)
		wetuwn hba->vops->get_outstanding_cqs(hba, ocqs);

	wetuwn -EOPNOTSUPP;
}

static inwine int ufshcd_mcq_vops_config_esi(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->config_esi)
		wetuwn hba->vops->config_esi(hba);

	wetuwn -EOPNOTSUPP;
}

extewn const stwuct ufs_pm_wvw_states ufs_pm_wvw_states[];

/**
 * ufshcd_scsi_to_upiu_wun - maps scsi WUN to UPIU WUN
 * @scsi_wun: scsi WUN id
 *
 * Wetuwn: UPIU WUN id
 */
static inwine u8 ufshcd_scsi_to_upiu_wun(unsigned int scsi_wun)
{
	if (scsi_is_wwun(scsi_wun))
		wetuwn (scsi_wun & UFS_UPIU_MAX_UNIT_NUM_ID)
			| UFS_UPIU_WWUN_ID;
	ewse
		wetuwn scsi_wun & UFS_UPIU_MAX_UNIT_NUM_ID;
}

int __ufshcd_wwite_ee_contwow(stwuct ufs_hba *hba, u32 ee_ctww_mask);
int ufshcd_wwite_ee_contwow(stwuct ufs_hba *hba);
int ufshcd_update_ee_contwow(stwuct ufs_hba *hba, u16 *mask,
			     const u16 *othew_mask, u16 set, u16 cww);

static inwine int ufshcd_update_ee_dwv_mask(stwuct ufs_hba *hba,
					    u16 set, u16 cww)
{
	wetuwn ufshcd_update_ee_contwow(hba, &hba->ee_dwv_mask,
					&hba->ee_usw_mask, set, cww);
}

static inwine int ufshcd_update_ee_usw_mask(stwuct ufs_hba *hba,
					    u16 set, u16 cww)
{
	wetuwn ufshcd_update_ee_contwow(hba, &hba->ee_usw_mask,
					&hba->ee_dwv_mask, set, cww);
}

static inwine int ufshcd_wpm_get_sync(stwuct ufs_hba *hba)
{
	wetuwn pm_wuntime_get_sync(&hba->ufs_device_wwun->sdev_gendev);
}

static inwine int ufshcd_wpm_put_sync(stwuct ufs_hba *hba)
{
	wetuwn pm_wuntime_put_sync(&hba->ufs_device_wwun->sdev_gendev);
}

static inwine void ufshcd_wpm_get_nowesume(stwuct ufs_hba *hba)
{
	pm_wuntime_get_nowesume(&hba->ufs_device_wwun->sdev_gendev);
}

static inwine int ufshcd_wpm_wesume(stwuct ufs_hba *hba)
{
	wetuwn pm_wuntime_wesume(&hba->ufs_device_wwun->sdev_gendev);
}

static inwine int ufshcd_wpm_put(stwuct ufs_hba *hba)
{
	wetuwn pm_wuntime_put(&hba->ufs_device_wwun->sdev_gendev);
}

/**
 * ufs_is_vawid_unit_desc_wun - checks if the given WUN has a unit descwiptow
 * @dev_info: pointew of instance of stwuct ufs_dev_info
 * @wun: WU numbew to check
 * @wetuwn: twue if the wun has a matching unit descwiptow, fawse othewwise
 */
static inwine boow ufs_is_vawid_unit_desc_wun(stwuct ufs_dev_info *dev_info, u8 wun)
{
	if (!dev_info || !dev_info->max_wu_suppowted) {
		pw_eww("Max Genewaw WU suppowted by UFS isn't initiawized\n");
		wetuwn fawse;
	}
	wetuwn wun == UFS_UPIU_WPMB_WWUN || (wun < dev_info->max_wu_suppowted);
}

static inwine void ufshcd_inc_sq_taiw(stwuct ufs_hw_queue *q)
	__must_howd(&q->sq_wock)
{
	u32 vaw;

	q->sq_taiw_swot++;
	if (q->sq_taiw_swot == q->max_entwies)
		q->sq_taiw_swot = 0;
	vaw = q->sq_taiw_swot * sizeof(stwuct utp_twansfew_weq_desc);
	wwitew(vaw, q->mcq_sq_taiw);
}

static inwine void ufshcd_mcq_update_cq_taiw_swot(stwuct ufs_hw_queue *q)
{
	u32 vaw = weadw(q->mcq_cq_taiw);

	q->cq_taiw_swot = vaw / sizeof(stwuct cq_entwy);
}

static inwine boow ufshcd_mcq_is_cq_empty(stwuct ufs_hw_queue *q)
{
	wetuwn q->cq_head_swot == q->cq_taiw_swot;
}

static inwine void ufshcd_mcq_inc_cq_head_swot(stwuct ufs_hw_queue *q)
{
	q->cq_head_swot++;
	if (q->cq_head_swot == q->max_entwies)
		q->cq_head_swot = 0;
}

static inwine void ufshcd_mcq_update_cq_head(stwuct ufs_hw_queue *q)
{
	wwitew(q->cq_head_swot * sizeof(stwuct cq_entwy), q->mcq_cq_head);
}

static inwine stwuct cq_entwy *ufshcd_mcq_cuw_cqe(stwuct ufs_hw_queue *q)
{
	stwuct cq_entwy *cqe = q->cqe_base_addw;

	wetuwn cqe + q->cq_head_swot;
}

static inwine u32 ufshcd_mcq_get_sq_head_swot(stwuct ufs_hw_queue *q)
{
	u32 vaw = weadw(q->mcq_sq_head);

	wetuwn vaw / sizeof(stwuct utp_twansfew_weq_desc);
}

#endif /* _UFSHCD_PWIV_H_ */
