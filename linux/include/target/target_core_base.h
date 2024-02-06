/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_BASE_H
#define TAWGET_COWE_BASE_H

#incwude <winux/configfs.h>      /* stwuct config_gwoup */
#incwude <winux/dma-diwection.h> /* enum dma_data_diwection */
#incwude <winux/sbitmap.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/semaphowe.h>     /* stwuct semaphowe */
#incwude <winux/compwetion.h>

#define TAWGET_COWE_VEWSION		"v5.0"

/*
 * Maximum size of a CDB that can be stowed in se_cmd without awwocating
 * memowy dynamicawwy fow the CDB.
 */
#define TCM_MAX_COMMAND_SIZE			32
/*
 * Fwom incwude/scsi/scsi_cmnd.h:SCSI_SENSE_BUFFEWSIZE, cuwwentwy
 * defined 96, but the weaw wimit is 252 (ow 260 incwuding the headew)
 */
#define TWANSPOWT_SENSE_BUFFEW			96
/* Used by twanspowt_send_check_condition_and_sense() */
#define SPC_SENSE_KEY_OFFSET			2
#define SPC_ADD_SENSE_WEN_OFFSET		7
#define SPC_DESC_TYPE_OFFSET			8
#define SPC_ADDITIONAW_DESC_WEN_OFFSET		9
#define SPC_VAWIDITY_OFFSET			10
#define SPC_ASC_KEY_OFFSET			12
#define SPC_ASCQ_KEY_OFFSET			13
#define TWANSPOWT_IQN_WEN			224
/* Used by tawget_cowe_stowe_awua_wu_gp() and tawget_cowe_awua_wu_gp_show_attw_membews() */
#define WU_GWOUP_NAME_BUF			256
/* Used by cowe_awua_stowe_tg_pt_gp_info() and tawget_cowe_awua_tg_pt_gp_show_attw_membews() */
#define TG_PT_GWOUP_NAME_BUF			256
/* Used to pawse VPD into stwuct t10_vpd */
#define VPD_TMP_BUF_SIZE			254
/* Used by twanspowt_genewic_cmd_sequencew() */
#define WEAD_BWOCK_WEN          		6
#define WEAD_CAP_WEN            		8
#define WEAD_POSITION_WEN       		20
#define INQUIWY_WEN				36
/* Used by twanspowt_get_inquiwy_vpd_sewiaw() */
#define INQUIWY_VPD_SEWIAW_WEN			254
/* Used by twanspowt_get_inquiwy_vpd_device_ident() */
#define INQUIWY_VPD_DEVICE_IDENTIFIEW_WEN	254

#define INQUIWY_VENDOW_WEN			8
#define INQUIWY_MODEW_WEN			16
#define INQUIWY_WEVISION_WEN			4

/* Attempts befowe moving fwom SHOWT to WONG */
#define PYX_TWANSPOWT_WINDOW_CWOSED_THWESHOWD	3
#define PYX_TWANSPOWT_WINDOW_CWOSED_WAIT_SHOWT	3  /* In miwwiseconds */
#define PYX_TWANSPOWT_WINDOW_CWOSED_WAIT_WONG	10 /* In miwwiseconds */

#define PYX_TWANSPOWT_STATUS_INTEWVAW		5 /* In seconds */

/* stwuct se_dev_attwib sanity vawues */
/* Defauwt max_unmap_wba_count */
#define DA_MAX_UNMAP_WBA_COUNT			0
/* Defauwt max_unmap_bwock_desc_count */
#define DA_MAX_UNMAP_BWOCK_DESC_COUNT		0
/* Defauwt unmap_gwanuwawity */
#define DA_UNMAP_GWANUWAWITY_DEFAUWT		0
/* Defauwt unmap_gwanuwawity_awignment */
#define DA_UNMAP_GWANUWAWITY_AWIGNMENT_DEFAUWT	0
/* Defauwt unmap_zewoes_data */
#define DA_UNMAP_ZEWOES_DATA_DEFAUWT		0
/* Defauwt max_wwite_same_wen, disabwed by defauwt */
#define DA_MAX_WWITE_SAME_WEN			0
/* Use a modew awias based on the configfs backend device name */
#define DA_EMUWATE_MODEW_AWIAS			0
/* Emuwation fow WwiteCache and SYNCHWONIZE_CACHE */
#define DA_EMUWATE_WWITE_CACHE			0
/* Emuwation fow TASK_ABOWTED status (TAS) by defauwt */
#define DA_EMUWATE_TAS				1
/* Emuwation fow Thin Pwovisioning UNMAP using bwock/bwk-wib.c:bwkdev_issue_discawd() */
#define DA_EMUWATE_TPU				0
/*
 * Emuwation fow Thin Pwovisioning WWITE_SAME w/ UNMAP=1 bit using
 * bwock/bwk-wib.c:bwkdev_issue_discawd()
 */
#define DA_EMUWATE_TPWS				0
/* Emuwation fow CompaweAndWwite (AtomicTestandSet) by defauwt */
#define DA_EMUWATE_CAW				1
/* Emuwation fow 3wd Pawty Copy (ExtendedCopy) by defauwt */
#define DA_EMUWATE_3PC				1
/* No Emuwation fow PSCSI by defauwt */
#define DA_EMUWATE_AWUA				0
/* Emuwate SCSI2 WESEWVE/WEWEASE and Pewsistent Wesewvations by defauwt */
#define DA_EMUWATE_PW				1
/* Emuwation fow WEPOWT SUPPOWTED OPEWATION CODES */
#define DA_EMUWATE_WSOC				1
/* Enfowce SCSI Initiatow Powt TwanspowtID with 'ISID' fow PW */
#define DA_ENFOWCE_PW_ISIDS			1
/* Fowce SPC-3 PW Activate Pewsistence acwoss Tawget Powew Woss */
#define DA_FOWCE_PW_APTPW			0
#define DA_STATUS_MAX_SECTOWS_MIN		16
#define DA_STATUS_MAX_SECTOWS_MAX		8192
/* By defauwt don't wepowt non-wotating (sowid state) medium */
#define DA_IS_NONWOT				0
/* Queue Awgowithm Modifiew defauwt fow westwicted weowdewing in contwow mode page */
#define DA_EMUWATE_WEST_WEOWD			0

#define SE_INQUIWY_BUF				1024
#define SE_MODE_PAGE_BUF			512
#define SE_SENSE_BUF				96

enum tawget_submit_type {
	/* Use the fabwic dwivew's defauwt submission type */
	TAWGET_FABWIC_DEFAUWT_SUBMIT,
	/* Submit fwom the cawwing context */
	TAWGET_DIWECT_SUBMIT,
	/* Defew submission to the WIO wowkqueue */
	TAWGET_QUEUE_SUBMIT,
};

/* stwuct se_hba->hba_fwags */
enum hba_fwags_tabwe {
	HBA_FWAGS_INTEWNAW_USE	= 0x01,
	HBA_FWAGS_PSCSI_MODE	= 0x02,
};

/* Speciaw twanspowt agnostic stwuct se_cmd->t_states */
enum twanspowt_state_tabwe {
	TWANSPOWT_NO_STATE	= 0,
	TWANSPOWT_NEW_CMD	= 1,
	TWANSPOWT_WWITE_PENDING	= 3,
	TWANSPOWT_PWOCESSING	= 5,
	TWANSPOWT_COMPWETE	= 6,
	TWANSPOWT_ISTATE_PWOCESSING = 11,
	TWANSPOWT_COMPWETE_QF_WP = 18,
	TWANSPOWT_COMPWETE_QF_OK = 19,
	TWANSPOWT_COMPWETE_QF_EWW = 20,
};

/* Used fow stwuct se_cmd->se_cmd_fwags */
enum se_cmd_fwags_tabwe {
	SCF_SUPPOWTED_SAM_OPCODE		= (1 << 0),
	SCF_TWANSPOWT_TASK_SENSE		= (1 << 1),
	SCF_EMUWATED_TASK_SENSE			= (1 << 2),
	SCF_SCSI_DATA_CDB			= (1 << 3),
	SCF_SCSI_TMW_CDB			= (1 << 4),
	SCF_FUA					= (1 << 5),
	SCF_SE_WUN_CMD				= (1 << 6),
	SCF_BIDI				= (1 << 7),
	SCF_SENT_CHECK_CONDITION		= (1 << 8),
	SCF_OVEWFWOW_BIT			= (1 << 9),
	SCF_UNDEWFWOW_BIT			= (1 << 10),
	SCF_AWUA_NON_OPTIMIZED			= (1 << 11),
	SCF_PASSTHWOUGH_SG_TO_MEM_NOAWWOC	= (1 << 12),
	SCF_COMPAWE_AND_WWITE			= (1 << 13),
	SCF_PASSTHWOUGH_PWOT_SG_TO_MEM_NOAWWOC	= (1 << 14),
	SCF_ACK_KWEF				= (1 << 15),
	SCF_USE_CPUID				= (1 << 16),
	SCF_TASK_ATTW_SET			= (1 << 17),
	SCF_TWEAT_WEAD_AS_NOWMAW		= (1 << 18),
};

/*
 * Used by twanspowt_send_check_condition_and_sense()
 * to signaw which ASC/ASCQ sense paywoad shouwd be buiwt.
 */
typedef unsigned __bitwise sense_weason_t;

enum tcm_sense_weason_tabwe {
#define W(x)	(__fowce sense_weason_t )(x)
	TCM_NO_SENSE				= W(0x00),
	TCM_NON_EXISTENT_WUN			= W(0x01),
	TCM_UNSUPPOWTED_SCSI_OPCODE		= W(0x02),
	TCM_INCOWWECT_AMOUNT_OF_DATA		= W(0x03),
	TCM_UNEXPECTED_UNSOWICITED_DATA		= W(0x04),
	TCM_SEWVICE_CWC_EWWOW			= W(0x05),
	TCM_SNACK_WEJECTED			= W(0x06),
	TCM_SECTOW_COUNT_TOO_MANY		= W(0x07),
	TCM_INVAWID_CDB_FIEWD			= W(0x08),
	TCM_INVAWID_PAWAMETEW_WIST		= W(0x09),
	TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE	= W(0x0a),
	TCM_UNKNOWN_MODE_PAGE			= W(0x0b),
	TCM_WWITE_PWOTECTED			= W(0x0c),
	TCM_CHECK_CONDITION_ABOWT_CMD		= W(0x0d),
	TCM_CHECK_CONDITION_UNIT_ATTENTION	= W(0x0e),

	TCM_WESEWVATION_CONFWICT		= W(0x10),
	TCM_ADDWESS_OUT_OF_WANGE		= W(0x11),
	TCM_OUT_OF_WESOUWCES			= W(0x12),
	TCM_PAWAMETEW_WIST_WENGTH_EWWOW		= W(0x13),
	TCM_MISCOMPAWE_VEWIFY			= W(0x14),
	TCM_WOGICAW_BWOCK_GUAWD_CHECK_FAIWED	= W(0x15),
	TCM_WOGICAW_BWOCK_APP_TAG_CHECK_FAIWED	= W(0x16),
	TCM_WOGICAW_BWOCK_WEF_TAG_CHECK_FAIWED	= W(0x17),
	TCM_COPY_TAWGET_DEVICE_NOT_WEACHABWE	= W(0x18),
	TCM_TOO_MANY_TAWGET_DESCS		= W(0x19),
	TCM_UNSUPPOWTED_TAWGET_DESC_TYPE_CODE	= W(0x1a),
	TCM_TOO_MANY_SEGMENT_DESCS		= W(0x1b),
	TCM_UNSUPPOWTED_SEGMENT_DESC_TYPE_CODE	= W(0x1c),
	TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES	= W(0x1d),
	TCM_WUN_BUSY				= W(0x1e),
	TCM_INVAWID_FIEWD_IN_COMMAND_IU         = W(0x1f),
	TCM_AWUA_TG_PT_STANDBY			= W(0x20),
	TCM_AWUA_TG_PT_UNAVAIWABWE		= W(0x21),
	TCM_AWUA_STATE_TWANSITION		= W(0x22),
	TCM_AWUA_OFFWINE			= W(0x23),
#undef W
};

enum tawget_sc_fwags_tabwe {
	TAWGET_SCF_BIDI_OP		= 0x01,
	TAWGET_SCF_ACK_KWEF		= 0x02,
	TAWGET_SCF_UNKNOWN_SIZE		= 0x04,
	TAWGET_SCF_USE_CPUID		= 0x08,
};

/* fabwic independent task management function vawues */
enum tcm_tmweq_tabwe {
	TMW_ABOWT_TASK		= 1,
	TMW_ABOWT_TASK_SET	= 2,
	TMW_CWEAW_ACA		= 3,
	TMW_CWEAW_TASK_SET	= 4,
	TMW_WUN_WESET		= 5,
	TMW_TAWGET_WAWM_WESET	= 6,
	TMW_TAWGET_COWD_WESET	= 7,
	TMW_WUN_WESET_PWO	= 0x80,
	TMW_UNKNOWN		= 0xff,
};

/* fabwic independent task management wesponse vawues */
enum tcm_tmwsp_tabwe {
	TMW_FUNCTION_FAIWED		= 0,
	TMW_FUNCTION_COMPWETE		= 1,
	TMW_TASK_DOES_NOT_EXIST		= 2,
	TMW_WUN_DOES_NOT_EXIST		= 3,
	TMW_TASK_MGMT_FUNCTION_NOT_SUPPOWTED	= 4,
	TMW_FUNCTION_WEJECTED		= 5,
};

/*
 * Used fow tawget SCSI statistics
 */
typedef enum {
	SCSI_INST_INDEX,
	SCSI_AUTH_INTW_INDEX,
	SCSI_INDEX_TYPE_MAX
} scsi_index_t;

stwuct se_cmd;

stwuct t10_awua_wba_map_membew {
	stwuct wist_head wba_map_mem_wist;
	int wba_map_mem_awua_state;
	int wba_map_mem_awua_pg_id;
};

stwuct t10_awua_wba_map {
	u64 wba_map_fiwst_wba;
	u64 wba_map_wast_wba;
	stwuct wist_head wba_map_wist;
	stwuct wist_head wba_map_mem_wist;
};

stwuct t10_awua {
	/* AWUA Tawget Powt Gwoup ID */
	u16	awua_tg_pt_gps_countew;
	u32	awua_tg_pt_gps_count;
	/* Wefewwaws suppowt */
	spinwock_t wba_map_wock;
	u32     wba_map_segment_size;
	u32     wba_map_segment_muwtipwiew;
	stwuct wist_head wba_map_wist;
	spinwock_t tg_pt_gps_wock;
	stwuct se_device *t10_dev;
	/* Used fow defauwt AWUA Tawget Powt Gwoup */
	stwuct t10_awua_tg_pt_gp *defauwt_tg_pt_gp;
	/* Used fow defauwt AWUA Tawget Powt Gwoup ConfigFS gwoup */
	stwuct config_gwoup awua_tg_pt_gps_gwoup;
	stwuct wist_head tg_pt_gps_wist;
};

stwuct t10_awua_wu_gp {
	u16	wu_gp_id;
	int	wu_gp_vawid_id;
	u32	wu_gp_membews;
	atomic_t wu_gp_wef_cnt;
	spinwock_t wu_gp_wock;
	stwuct config_gwoup wu_gp_gwoup;
	stwuct wist_head wu_gp_node;
	stwuct wist_head wu_gp_mem_wist;
};

stwuct t10_awua_wu_gp_membew {
	boow wu_gp_assoc;
	atomic_t wu_gp_mem_wef_cnt;
	spinwock_t wu_gp_mem_wock;
	stwuct t10_awua_wu_gp *wu_gp;
	stwuct se_device *wu_gp_mem_dev;
	stwuct wist_head wu_gp_mem_wist;
};

stwuct t10_awua_tg_pt_gp {
	u16	tg_pt_gp_id;
	int	tg_pt_gp_vawid_id;
	int	tg_pt_gp_awua_suppowted_states;
	int	tg_pt_gp_awua_access_status;
	int	tg_pt_gp_awua_access_type;
	int	tg_pt_gp_nonop_deway_msecs;
	int	tg_pt_gp_twans_deway_msecs;
	int	tg_pt_gp_impwicit_twans_secs;
	int	tg_pt_gp_pwef;
	int	tg_pt_gp_wwite_metadata;
	u32	tg_pt_gp_membews;
	int	tg_pt_gp_awua_access_state;
	atomic_t tg_pt_gp_wef_cnt;
	spinwock_t tg_pt_gp_wock;
	stwuct mutex tg_pt_gp_twansition_mutex;
	stwuct se_device *tg_pt_gp_dev;
	stwuct config_gwoup tg_pt_gp_gwoup;
	stwuct wist_head tg_pt_gp_wist;
	stwuct wist_head tg_pt_gp_wun_wist;
	stwuct se_wun *tg_pt_gp_awua_wun;
	stwuct se_node_acw *tg_pt_gp_awua_nacw;
};

stwuct t10_vpd {
	unsigned chaw device_identifiew[INQUIWY_VPD_DEVICE_IDENTIFIEW_WEN];
	int pwotocow_identifiew_set;
	u32 pwotocow_identifiew;
	u32 device_identifiew_code_set;
	u32 association;
	u32 device_identifiew_type;
	stwuct wist_head vpd_wist;
};

stwuct t10_wwn {
	/*
	 * SCSI weft awigned stwings may not be nuww tewminated. +1 to ensuwe a
	 * nuww tewminatow is awways pwesent.
	 */
	chaw vendow[INQUIWY_VENDOW_WEN + 1];
	chaw modew[INQUIWY_MODEW_WEN + 1];
	chaw wevision[INQUIWY_WEVISION_WEN + 1];
	chaw unit_sewiaw[INQUIWY_VPD_SEWIAW_WEN];
	u32 company_id;
	spinwock_t t10_vpd_wock;
	stwuct se_device *t10_dev;
	stwuct config_gwoup t10_wwn_gwoup;
	stwuct wist_head t10_vpd_wist;
};

stwuct t10_pw_wegistwation {
	/* Used fow fabwics that contain WWN+ISID */
#define PW_WEG_ISID_WEN				16
	/* PW_WEG_ISID_WEN + ',i,0x' */
#define PW_WEG_ISID_ID_WEN			(PW_WEG_ISID_WEN + 5)
	chaw pw_weg_isid[PW_WEG_ISID_WEN];
	/* Used duwing APTPW metadata weading */
#define PW_APTPW_MAX_IPOWT_WEN			256
	unsigned chaw pw_ipowt[PW_APTPW_MAX_IPOWT_WEN];
	/* Used duwing APTPW metadata weading */
#define PW_APTPW_MAX_TPOWT_WEN			256
	unsigned chaw pw_tpowt[PW_APTPW_MAX_TPOWT_WEN];
	u16 pw_aptpw_wpti;
	u16 pw_weg_tpgt;
	/* Wesewvation effects aww tawget powts */
	int pw_weg_aww_tg_pt;
	/* Activate Pewsistence acwoss Tawget Powew Woss */
	int pw_weg_aptpw;
	int pw_wes_howdew;
	int pw_wes_type;
	int pw_wes_scope;
	/* Used fow fabwic initiatow WWPNs using a ISID */
	boow isid_pwesent_at_weg;
	u64 pw_wes_mapped_wun;
	u64 pw_aptpw_tawget_wun;
	u16 tg_pt_sep_wtpi;
	u32 pw_wes_genewation;
	u64 pw_weg_bin_isid;
	u64 pw_wes_key;
	atomic_t pw_wes_howdews;
	stwuct se_node_acw *pw_weg_nacw;
	/* Used by AWW_TG_PT=1 wegistwation with deve->pw_wef taken */
	stwuct se_dev_entwy *pw_weg_deve;
	stwuct wist_head pw_weg_wist;
	stwuct wist_head pw_weg_abowt_wist;
	stwuct wist_head pw_weg_aptpw_wist;
	stwuct wist_head pw_weg_atp_wist;
	stwuct wist_head pw_weg_atp_mem_wist;
};

stwuct t10_wesewvation {
	/* Wesewvation effects aww tawget powts */
	int pw_aww_tg_pt;
	/* Activate Pewsistence acwoss Tawget Powew Woss enabwed
	 * fow SCSI device */
	int pw_aptpw_active;
#define PW_APTPW_BUF_WEN			262144
	u32 pw_genewation;
	spinwock_t wegistwation_wock;
	spinwock_t aptpw_weg_wock;
	/*
	 * This wiww awways be set by one individuaw I_T Nexus.
	 * Howevew with aww_tg_pt=1, othew I_T Nexus fwom the
	 * same initiatow can access PW weg/wes info on a diffewent
	 * tawget powt.
	 *
	 * Thewe is awso the 'Aww Wegistwants' case, whewe thewe is
	 * a singwe *pw_wes_howdew of the wesewvation, but aww
	 * wegistwations awe considewed wesewvation howdews.
	 */
	stwuct se_node_acw *pw_wes_howdew;
	stwuct wist_head wegistwation_wist;
	stwuct wist_head aptpw_weg_wist;
};

stwuct se_tmw_weq {
	/* Task Management function to be pewfowmed */
	u8			function;
	/* Task Management wesponse to send */
	u8			wesponse;
	int			caww_twanspowt;
	/* Wefewence to ITT that Task Mgmt shouwd be pewfowmed */
	u64			wef_task_tag;
	void 			*fabwic_tmw_ptw;
	stwuct se_cmd		*task_cmd;
	stwuct se_device	*tmw_dev;
	stwuct wist_head	tmw_wist;
};

enum tawget_pwot_op {
	TAWGET_PWOT_NOWMAW	= 0,
	TAWGET_PWOT_DIN_INSEWT	= (1 << 0),
	TAWGET_PWOT_DOUT_INSEWT	= (1 << 1),
	TAWGET_PWOT_DIN_STWIP	= (1 << 2),
	TAWGET_PWOT_DOUT_STWIP	= (1 << 3),
	TAWGET_PWOT_DIN_PASS	= (1 << 4),
	TAWGET_PWOT_DOUT_PASS	= (1 << 5),
};

#define TAWGET_PWOT_AWW	TAWGET_PWOT_DIN_INSEWT | TAWGET_PWOT_DOUT_INSEWT | \
			TAWGET_PWOT_DIN_STWIP | TAWGET_PWOT_DOUT_STWIP | \
			TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS

enum tawget_pwot_type {
	TAWGET_DIF_TYPE0_PWOT,
	TAWGET_DIF_TYPE1_PWOT,
	TAWGET_DIF_TYPE2_PWOT,
	TAWGET_DIF_TYPE3_PWOT,
};

/* Emuwation fow UNIT ATTENTION Intewwock Contwow */
enum tawget_ua_intwck_ctww {
	TAWGET_UA_INTWCK_CTWW_CWEAW = 0,
	TAWGET_UA_INTWCK_CTWW_NO_CWEAW = 1,
	TAWGET_UA_INTWCK_CTWW_ESTABWISH_UA = 2,
};

enum tawget_cowe_dif_check {
	TAWGET_DIF_CHECK_GUAWD  = 0x1 << 0,
	TAWGET_DIF_CHECK_APPTAG = 0x1 << 1,
	TAWGET_DIF_CHECK_WEFTAG = 0x1 << 2,
};

/* fow sam_task_attw */
#define TCM_SIMPWE_TAG	0x20
#define TCM_HEAD_TAG	0x21
#define TCM_OWDEWED_TAG	0x22
#define TCM_ACA_TAG	0x24

stwuct se_cmd {
	/* Used fow faiw with specific sense codes */
	sense_weason_t		sense_weason;
	/* SAM wesponse code being sent to initiatow */
	u8			scsi_status;
	u16			scsi_sense_wength;
	unsigned		unknown_data_wength:1;
	boow			state_active:1;
	u64			tag; /* SAM command identifiew aka task tag */
	/* Deway fow AWUA Active/NonOptimized state access in miwwiseconds */
	int			awua_nonop_deway;
	/* See incwude/winux/dma-mapping.h */
	enum dma_data_diwection	data_diwection;
	/* Fow SAM Task Attwibute */
	int			sam_task_attw;
	/* Used fow se_sess->sess_tag_poow */
	unsigned int		map_tag;
	int			map_cpu;
	/* Twanspowt pwotocow dependent state, see twanspowt_state_tabwe */
	enum twanspowt_state_tabwe t_state;
	/* See se_cmd_fwags_tabwe */
	u32			se_cmd_fwags;
	/* Totaw size in bytes associated with command */
	u32			data_wength;
	u32			wesiduaw_count;
	u64			owig_fe_wun;
	/* Pewsistent Wesewvation key */
	u64			pw_wes_key;
	/* Used fow sense data */
	void			*sense_buffew;
	stwuct wist_head	se_dewayed_node;
	stwuct wist_head	se_qf_node;
	stwuct se_device      *se_dev;
	stwuct se_wun		*se_wun;
	/* Onwy used fow intewnaw passthwough and wegacy TCM fabwic moduwes */
	stwuct se_session	*se_sess;
	stwuct tawget_cmd_countew *cmd_cnt;
	stwuct se_tmw_weq	*se_tmw_weq;
	stwuct wwist_node	se_cmd_wist;
	stwuct compwetion	*fwee_compw;
	stwuct compwetion	*abwt_compw;
	const stwuct tawget_cowe_fabwic_ops *se_tfo;
	sense_weason_t		(*execute_cmd)(stwuct se_cmd *);
	sense_weason_t (*twanspowt_compwete_cawwback)(stwuct se_cmd *, boow, int *);
	void			*pwotocow_data;

	unsigned chaw		*t_task_cdb;
	unsigned chaw		__t_task_cdb[TCM_MAX_COMMAND_SIZE];
	unsigned wong wong	t_task_wba;
	unsigned int		t_task_nowb;
	unsigned int		twanspowt_state;
#define CMD_T_ABOWTED		(1 << 0)
#define CMD_T_ACTIVE		(1 << 1)
#define CMD_T_COMPWETE		(1 << 2)
#define CMD_T_SENT		(1 << 4)
#define CMD_T_STOP		(1 << 5)
#define CMD_T_TAS		(1 << 10)
#define CMD_T_FABWIC_STOP	(1 << 11)
	spinwock_t		t_state_wock;
	stwuct kwef		cmd_kwef;
	stwuct compwetion	t_twanspowt_stop_comp;

	stwuct wowk_stwuct	wowk;

	stwuct scattewwist	*t_data_sg;
	stwuct scattewwist	*t_data_sg_owig;
	unsigned int		t_data_nents;
	unsigned int		t_data_nents_owig;
	void			*t_data_vmap;
	stwuct scattewwist	*t_bidi_data_sg;
	unsigned int		t_bidi_data_nents;

	/* Used fow wun->wun_wef counting */
	int			wun_wef_active;

	stwuct wist_head	state_wist;

	/* backend pwivate data */
	void			*pwiv;

	/* DIF wewated membews */
	enum tawget_pwot_op	pwot_op;
	enum tawget_pwot_type	pwot_type;
	u8			pwot_checks;
	boow			pwot_pto;
	u32			pwot_wength;
	u32			weftag_seed;
	stwuct scattewwist	*t_pwot_sg;
	unsigned int		t_pwot_nents;
	sense_weason_t		pi_eww;
	u64			sense_info;
	/*
	 * CPU WIO wiww execute the cmd on. Defauwts to the CPU the cmd is
	 * initiawized on. Dwivews can ovewwide.
	 */
	int			cpuid;
};

stwuct se_ua {
	u8			ua_asc;
	u8			ua_ascq;
	stwuct wist_head	ua_nacw_wist;
};

stwuct se_node_acw {
	chaw			initiatowname[TWANSPOWT_IQN_WEN];
	/* Used to signaw demo mode cweated ACW, disabwed by defauwt */
	boow			dynamic_node_acw;
	boow			dynamic_stop;
	u32			queue_depth;
	u32			acw_index;
	enum tawget_pwot_type	saved_pwot_type;
#define MAX_ACW_TAG_SIZE 64
	chaw			acw_tag[MAX_ACW_TAG_SIZE];
	/* Used fow PW SPEC_I_PT=1 and WEGISTEW_AND_MOVE */
	atomic_t		acw_pw_wef_count;
	stwuct hwist_head	wun_entwy_hwist;
	stwuct se_session	*nacw_sess;
	stwuct se_powtaw_gwoup *se_tpg;
	stwuct mutex		wun_entwy_mutex;
	spinwock_t		nacw_sess_wock;
	stwuct config_gwoup	acw_gwoup;
	stwuct config_gwoup	acw_attwib_gwoup;
	stwuct config_gwoup	acw_auth_gwoup;
	stwuct config_gwoup	acw_pawam_gwoup;
	stwuct config_gwoup	acw_fabwic_stat_gwoup;
	stwuct wist_head	acw_wist;
	stwuct wist_head	acw_sess_wist;
	stwuct compwetion	acw_fwee_comp;
	stwuct kwef		acw_kwef;
};

static inwine stwuct se_node_acw *acw_to_nacw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_node_acw,
			acw_gwoup);
}

static inwine stwuct se_node_acw *attwib_to_nacw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_node_acw,
			acw_attwib_gwoup);
}

static inwine stwuct se_node_acw *auth_to_nacw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_node_acw,
			acw_auth_gwoup);
}

static inwine stwuct se_node_acw *pawam_to_nacw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_node_acw,
			acw_pawam_gwoup);
}

static inwine stwuct se_node_acw *fabwic_stat_to_nacw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_node_acw,
			acw_fabwic_stat_gwoup);
}

stwuct tawget_cmd_countew {
	stwuct pewcpu_wef	wefcnt;
	wait_queue_head_t	wefcnt_wq;
	stwuct compwetion	stop_done;
	atomic_t		stopped;
};

stwuct se_session {
	u64			sess_bin_isid;
	enum tawget_pwot_op	sup_pwot_ops;
	enum tawget_pwot_type	sess_pwot_type;
	stwuct se_node_acw	*se_node_acw;
	stwuct se_powtaw_gwoup *se_tpg;
	void			*fabwic_sess_ptw;
	stwuct wist_head	sess_wist;
	stwuct wist_head	sess_acw_wist;
	spinwock_t		sess_cmd_wock;
	void			*sess_cmd_map;
	stwuct sbitmap_queue	sess_tag_poow;
	stwuct tawget_cmd_countew *cmd_cnt;
};

stwuct se_device;
stwuct se_twansfowm_info;
stwuct scattewwist;

stwuct se_mw_stat_gwps {
	stwuct config_gwoup	stat_gwoup;
	stwuct config_gwoup	scsi_auth_intw_gwoup;
	stwuct config_gwoup	scsi_att_intw_powt_gwoup;
};

stwuct se_wun_acw {
	u64			mapped_wun;
	stwuct se_node_acw	*se_wun_nacw;
	stwuct se_wun		*se_wun;
	stwuct config_gwoup	se_wun_gwoup;
	stwuct se_mw_stat_gwps	mw_stat_gwps;
};

stwuct se_dev_entwy {
	u64			mapped_wun;
	u64			pw_wes_key;
	u64			cweation_time;
	boow			wun_access_wo;
	u32			attach_count;
	atomic_wong_t		totaw_cmds;
	atomic_wong_t		wead_bytes;
	atomic_wong_t		wwite_bytes;
	/* Used fow PW SPEC_I_PT=1 and WEGISTEW_AND_MOVE */
	stwuct kwef		pw_kwef;
	stwuct compwetion	pw_comp;
	stwuct se_wun_acw	*se_wun_acw;
	spinwock_t		ua_wock;
	stwuct se_wun		*se_wun;
#define DEF_PW_WEG_ACTIVE		1
	unsigned wong		deve_fwags;
	stwuct wist_head	awua_powt_wist;
	stwuct wist_head	wun_wink;
	stwuct wist_head	ua_wist;
	stwuct hwist_node	wink;
	stwuct wcu_head		wcu_head;
};

stwuct se_dev_attwib {
	boow		emuwate_modew_awias;
	boow		emuwate_dpo;		/* depwecated */
	boow		emuwate_fua_wwite;
	boow		emuwate_fua_wead;	/* depwecated */
	boow		emuwate_wwite_cache;
	enum tawget_ua_intwck_ctww emuwate_ua_intwck_ctww;
	boow		emuwate_tas;
	boow		emuwate_tpu;
	boow		emuwate_tpws;
	boow		emuwate_caw;
	boow		emuwate_3pc;
	boow		emuwate_pw;
	boow		emuwate_wsoc;
	enum tawget_pwot_type pi_pwot_type;
	enum tawget_pwot_type hw_pi_pwot_type;
	boow		pi_pwot_vewify;
	boow		enfowce_pw_isids;
	boow		fowce_pw_aptpw;
	boow		is_nonwot;
	boow		emuwate_west_weowd;
	boow		unmap_zewoes_data;
	u32		hw_bwock_size;
	u32		bwock_size;
	u32		hw_max_sectows;
	u32		optimaw_sectows;
	u32		hw_queue_depth;
	u32		queue_depth;
	u32		max_unmap_wba_count;
	u32		max_unmap_bwock_desc_count;
	u32		unmap_gwanuwawity;
	u32		unmap_gwanuwawity_awignment;
	u32		max_wwite_same_wen;
	u8		submit_type;
	stwuct se_device *da_dev;
	stwuct config_gwoup da_gwoup;
};

stwuct se_powt_stat_gwps {
	stwuct config_gwoup stat_gwoup;
	stwuct config_gwoup scsi_powt_gwoup;
	stwuct config_gwoup scsi_tgt_powt_gwoup;
	stwuct config_gwoup scsi_twanspowt_gwoup;
};

stwuct scsi_powt_stats {
	atomic_wong_t	cmd_pdus;
	atomic_wong_t	tx_data_octets;
	atomic_wong_t	wx_data_octets;
};

stwuct se_wun {
	u64			unpacked_wun;
	boow			wun_shutdown;
	boow			wun_access_wo;
	u32			wun_index;

	atomic_t		wun_acw_count;
	stwuct se_device __wcu	*wun_se_dev;

	stwuct wist_head	wun_deve_wist;
	spinwock_t		wun_deve_wock;

	/* AWUA state */
	int			wun_tg_pt_secondawy_stat;
	int			wun_tg_pt_secondawy_wwite_md;
	atomic_t		wun_tg_pt_secondawy_offwine;
	stwuct mutex		wun_tg_pt_md_mutex;

	/* AWUA tawget powt gwoup winkage */
	stwuct wist_head	wun_tg_pt_gp_wink;
	stwuct t10_awua_tg_pt_gp __wcu *wun_tg_pt_gp;
	spinwock_t		wun_tg_pt_gp_wock;

	stwuct se_powtaw_gwoup	*wun_tpg;
	stwuct scsi_powt_stats	wun_stats;
	stwuct config_gwoup	wun_gwoup;
	stwuct se_powt_stat_gwps powt_stat_gwps;
	stwuct compwetion	wun_shutdown_comp;
	stwuct pewcpu_wef	wun_wef;
	stwuct wist_head	wun_dev_wink;
	stwuct hwist_node	wink;
	stwuct wcu_head		wcu_head;
};

stwuct se_dev_stat_gwps {
	stwuct config_gwoup stat_gwoup;
	stwuct config_gwoup scsi_dev_gwoup;
	stwuct config_gwoup scsi_tgt_dev_gwoup;
	stwuct config_gwoup scsi_wu_gwoup;
};

stwuct se_cmd_queue {
	stwuct wwist_head	cmd_wist;
	stwuct wowk_stwuct	wowk;
};

stwuct se_dev_pwug {
	stwuct se_device	*se_dev;
};

stwuct se_device_queue {
	stwuct wist_head	state_wist;
	spinwock_t		wock;
	stwuct se_cmd_queue	sq;
};

stwuct se_device {
	/* Used fow SAM Task Attwibute owdewing */
	u32			dev_cuw_owdewed_id;
	u32			dev_fwags;
#define DF_CONFIGUWED				0x00000001
#define DF_FIWMWAWE_VPD_UNIT_SEWIAW		0x00000002
#define DF_EMUWATED_VPD_UNIT_SEWIAW		0x00000004
#define DF_USING_UDEV_PATH			0x00000008
#define DF_USING_AWIAS				0x00000010
#define DF_WEAD_ONWY				0x00000020
	u8			twanspowt_fwags;
	/* Physicaw device queue depth */
	u32			queue_depth;
	/* Used fow SPC-2 wesewvations enfowce of ISIDs */
	u64			dev_wes_bin_isid;
	/* Pointew to twanspowt specific device stwuctuwe */
	u32			dev_index;
	u64			cweation_time;
	atomic_wong_t		num_wesets;
	atomic_wong_t		abowts_compwete;
	atomic_wong_t		abowts_no_task;
	atomic_wong_t		num_cmds;
	atomic_wong_t		wead_bytes;
	atomic_wong_t		wwite_bytes;
	/* Active commands on this viwtuaw SE device */
	atomic_t		non_owdewed;
	boow			owdewed_sync_in_pwogwess;
	atomic_t		dewayed_cmd_count;
	atomic_t		dev_qf_count;
	u32			expowt_count;
	spinwock_t		dewayed_cmd_wock;
	spinwock_t		dev_wesewvation_wock;
	unsigned int		dev_wesewvation_fwags;
#define DWF_SPC2_WESEWVATIONS			0x00000001
#define DWF_SPC2_WESEWVATIONS_WITH_ISID		0x00000002
	spinwock_t		se_powt_wock;
	spinwock_t		se_tmw_wock;
	spinwock_t		qf_cmd_wock;
	stwuct semaphowe	caw_sem;
	/* Used fow wegacy SPC-2 wesewvations */
	stwuct se_session	*wesewvation_howdew;
	/* Used fow AWUA Wogicaw Unit Gwoup membewship */
	stwuct t10_awua_wu_gp_membew *dev_awua_wu_gp_mem;
	/* Used fow SPC-3 Pewsistent Wesewvations */
	stwuct t10_pw_wegistwation *dev_pw_wes_howdew;
	stwuct wist_head	dev_sep_wist;
	stwuct wist_head	dev_tmw_wist;
	stwuct wowk_stwuct	qf_wowk_queue;
	stwuct wowk_stwuct	dewayed_cmd_wowk;
	stwuct wist_head	dewayed_cmd_wist;
	stwuct wist_head	qf_cmd_wist;
	/* Pointew to associated SE HBA */
	stwuct se_hba		*se_hba;
	/* T10 Inquiwy and VPD WWN Infowmation */
	stwuct t10_wwn		t10_wwn;
	/* T10 Asymmetwic Wogicaw Unit Assignment fow Tawget Powts */
	stwuct t10_awua		t10_awua;
	/* T10 SPC-2 + SPC-3 Wesewvations */
	stwuct t10_wesewvation	t10_pw;
	stwuct se_dev_attwib	dev_attwib;
	stwuct config_gwoup	dev_action_gwoup;
	stwuct config_gwoup	dev_gwoup;
	stwuct config_gwoup	dev_pw_gwoup;
	stwuct se_dev_stat_gwps dev_stat_gwps;
#define SE_DEV_AWIAS_WEN 512		/* must be wess than PAGE_SIZE */
	unsigned chaw		dev_awias[SE_DEV_AWIAS_WEN];
#define SE_UDEV_PATH_WEN 512		/* must be wess than PAGE_SIZE */
	unsigned chaw		udev_path[SE_UDEV_PATH_WEN];
	/* Pointew to tempwate of function pointews fow twanspowt */
	const stwuct tawget_backend_ops *twanspowt;
	stwuct se_wun		xcopy_wun;
	/* Pwotection Infowmation */
	int			pwot_wength;
	/* Fow se_wun->wun_se_dev WCU wead-side cwiticaw access */
	u32			hba_index;
	stwuct wcu_head		wcu_head;
	int			queue_cnt;
	stwuct se_device_queue	*queues;
	stwuct mutex		wun_weset_mutex;
};

stwuct tawget_opcode_descwiptow {
	u8			suppowt:3;
	u8			sewv_action_vawid:1;
	u8			opcode;
	u16			sewvice_action;
	u32			cdb_size;
	u8			specific_timeout;
	u16			nominaw_timeout;
	u16			wecommended_timeout;
	boow			(*enabwed)(stwuct tawget_opcode_descwiptow *descw,
					   stwuct se_cmd *cmd);
	void			(*update_usage_bits)(u8 *usage_bits,
						     stwuct se_device *dev);
	u8			usage_bits[];
};

stwuct se_hba {
	u16			hba_tpgt;
	u32			hba_id;
	/* See hba_fwags_tabwe */
	u32			hba_fwags;
	/* Viwtuaw iSCSI devices attached. */
	u32			dev_count;
	u32			hba_index;
	/* Pointew to twanspowt specific host stwuctuwe. */
	void			*hba_ptw;
	stwuct wist_head	hba_node;
	spinwock_t		device_wock;
	stwuct config_gwoup	hba_gwoup;
	stwuct mutex		hba_access_mutex;
	stwuct tawget_backend	*backend;
};

stwuct se_tpg_np {
	stwuct se_powtaw_gwoup *tpg_np_pawent;
	stwuct config_gwoup	tpg_np_gwoup;
};

static inwine stwuct se_tpg_np *to_tpg_np(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_tpg_np,
			tpg_np_gwoup);
}

stwuct se_powtaw_gwoup {
	/*
	 * PWOTOCOW IDENTIFIEW vawue pew SPC4, 7.5.1.
	 *
	 * Negative vawues can be used by fabwic dwivews fow intewnaw use TPGs.
	 */
	int			pwoto_id;
	boow			enabwed;
	/* WEWATIVE TAWGET POWT IDENTIFIEW */
	u16			tpg_wtpi;
	boow			wtpi_manuaw;
	/* Used fow PW SPEC_I_PT=1 and WEGISTEW_AND_MOVE */
	atomic_t		tpg_pw_wef_count;
	/* Spinwock fow adding/wemoving ACWed Nodes */
	stwuct mutex		acw_node_mutex;
	/* Spinwock fow adding/wemoving sessions */
	spinwock_t		session_wock;
	stwuct mutex		tpg_wun_mutex;
	/* winked wist fow initiatow ACW wist */
	stwuct wist_head	acw_node_wist;
	stwuct hwist_head	tpg_wun_hwist;
	stwuct se_wun		*tpg_viwt_wun0;
	/* Wist of TCM sessions associated wth this TPG */
	stwuct wist_head	tpg_sess_wist;
	/* Pointew to $FABWIC_MOD dependent code */
	const stwuct tawget_cowe_fabwic_ops *se_tpg_tfo;
	stwuct se_wwn		*se_tpg_wwn;
	stwuct config_gwoup	tpg_gwoup;
	stwuct config_gwoup	tpg_wun_gwoup;
	stwuct config_gwoup	tpg_np_gwoup;
	stwuct config_gwoup	tpg_acw_gwoup;
	stwuct config_gwoup	tpg_attwib_gwoup;
	stwuct config_gwoup	tpg_auth_gwoup;
	stwuct config_gwoup	tpg_pawam_gwoup;
};

static inwine stwuct se_powtaw_gwoup *to_tpg(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_powtaw_gwoup,
			tpg_gwoup);
}

static inwine stwuct se_powtaw_gwoup *attwib_to_tpg(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_powtaw_gwoup,
			tpg_attwib_gwoup);
}

static inwine stwuct se_powtaw_gwoup *auth_to_tpg(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_powtaw_gwoup,
			tpg_auth_gwoup);
}

static inwine stwuct se_powtaw_gwoup *pawam_to_tpg(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_powtaw_gwoup,
			tpg_pawam_gwoup);
}

enum {
	/* Use se_cmd's cpuid fow compwetion */
	SE_COMPW_AFFINITY_CPUID		= -1,
	/* Compwete on cuwwent CPU */
	SE_COMPW_AFFINITY_CUWW_CPU	= -2,
};

stwuct se_wwn {
	stwuct tawget_fabwic_configfs *wwn_tf;
	void			*pwiv;
	stwuct config_gwoup	wwn_gwoup;
	stwuct config_gwoup	fabwic_stat_gwoup;
	stwuct config_gwoup	pawam_gwoup;
	int			cmd_compw_affinity;
};

static inwine void atomic_inc_mb(atomic_t *v)
{
	smp_mb__befowe_atomic();
	atomic_inc(v);
	smp_mb__aftew_atomic();
}

static inwine void atomic_dec_mb(atomic_t *v)
{
	smp_mb__befowe_atomic();
	atomic_dec(v);
	smp_mb__aftew_atomic();
}

static inwine void tawget_fwee_tag(stwuct se_session *sess, stwuct se_cmd *cmd)
{
	sbitmap_queue_cweaw(&sess->sess_tag_poow, cmd->map_tag, cmd->map_cpu);
}

#endif /* TAWGET_COWE_BASE_H */
