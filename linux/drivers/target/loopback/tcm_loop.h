/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <tawget/tawget_cowe_base.h> /* stwuct se_cmd */

#define TCM_WOOP_VEWSION		"v2.1-wc2"
#define TW_WWN_ADDW_WEN			256
#define TW_TPGS_PEW_HBA			32

stwuct tcm_woop_cmd {
	/* State of Winux/SCSI CDB+Data descwiptow */
	u32 sc_cmd_state;
	/* Tagged command queueing */
	u32 sc_cmd_tag;
	/* Pointew to the CDB+Data descwiptow fwom Winux/SCSI subsystem */
	stwuct scsi_cmnd *sc;
	/* The TCM I/O descwiptow that is accessed via containew_of() */
	stwuct se_cmd tw_se_cmd;
	stwuct compwetion tmw_done;
	/* Sense buffew that wiww be mapped into outgoing status */
	unsigned chaw tw_sense_buf[TWANSPOWT_SENSE_BUFFEW];
};

stwuct tcm_woop_nexus {
	/*
	 * Pointew to TCM session fow I_T Nexus
	 */
	stwuct se_session *se_sess;
};

#define TCM_TWANSPOWT_ONWINE 0
#define TCM_TWANSPOWT_OFFWINE 1

stwuct tcm_woop_tpg {
	unsigned showt tw_tpgt;
	unsigned showt tw_twanspowt_status;
	enum tawget_pwot_type tw_fabwic_pwot_type;
	atomic_t tw_tpg_powt_count;
	stwuct se_powtaw_gwoup tw_se_tpg;
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_nexus *tw_nexus;
};

stwuct tcm_woop_hba {
	u8 tw_pwoto_id;
	unsigned chaw tw_wwn_addwess[TW_WWN_ADDW_WEN];
	stwuct se_hba_s *se_hba;
	stwuct se_wun *tw_hba_wun;
	stwuct se_powt *tw_hba_wun_sep;
	stwuct device dev;
	stwuct Scsi_Host *sh;
	stwuct tcm_woop_tpg tw_hba_tpgs[TW_TPGS_PEW_HBA];
	stwuct se_wwn tw_hba_wwn;
};
