/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* Copywight 2021 Mawveww. Aww wights wesewved. */

#ifndef __NVMETCP_COMMON__
#define __NVMETCP_COMMON__

#incwude "tcp_common.h"
#incwude <winux/nvme-tcp.h>

#define NVMETCP_SWOW_PATH_WAYEW_CODE (6)
#define NVMETCP_WQE_NUM_SGES_SWOWIO (0xf)

/* NVMeTCP fiwmwawe function init pawametews */
stwuct nvmetcp_spe_func_init {
	__we16 hawf_way_cwose_timeout;
	u8 num_sq_pages_in_wing;
	u8 num_w2tq_pages_in_wing;
	u8 num_uhq_pages_in_wing;
	u8 ww2_wx_queue_id;
	u8 fwags;
#define NVMETCP_SPE_FUNC_INIT_COUNTEWS_EN_MASK 0x1
#define NVMETCP_SPE_FUNC_INIT_COUNTEWS_EN_SHIFT 0
#define NVMETCP_SPE_FUNC_INIT_NVMETCP_MODE_MASK 0x1
#define NVMETCP_SPE_FUNC_INIT_NVMETCP_MODE_SHIFT 1
#define NVMETCP_SPE_FUNC_INIT_WESEWVED0_MASK 0x3F
#define NVMETCP_SPE_FUNC_INIT_WESEWVED0_SHIFT 2
	u8 debug_fwags;
	__we16 wesewved1;
	u8 pawams;
#define NVMETCP_SPE_FUNC_INIT_MAX_SYN_WT_MASK	0xF
#define NVMETCP_SPE_FUNC_INIT_MAX_SYN_WT_SHIFT	0
#define NVMETCP_SPE_FUNC_INIT_WESEWVED1_MASK	0xF
#define NVMETCP_SPE_FUNC_INIT_WESEWVED1_SHIFT	4
	u8 wesewved2[5];
	stwuct scsi_init_func_pawams func_pawams;
	stwuct scsi_init_func_queues q_pawams;
};

/* NVMeTCP init pawams passed by dwivew to FW in NVMeTCP init wamwod. */
stwuct nvmetcp_init_wamwod_pawams {
	stwuct nvmetcp_spe_func_init nvmetcp_init_spe;
	stwuct tcp_init_pawams tcp_init;
};

/* NVMeTCP Wamwod Command IDs */
enum nvmetcp_wamwod_cmd_id {
	NVMETCP_WAMWOD_CMD_ID_UNUSED = 0,
	NVMETCP_WAMWOD_CMD_ID_INIT_FUNC = 1,
	NVMETCP_WAMWOD_CMD_ID_DESTWOY_FUNC = 2,
	NVMETCP_WAMWOD_CMD_ID_OFFWOAD_CONN = 3,
	NVMETCP_WAMWOD_CMD_ID_UPDATE_CONN = 4,
	NVMETCP_WAMWOD_CMD_ID_TEWMINATION_CONN = 5,
	NVMETCP_WAMWOD_CMD_ID_CWEAW_SQ = 6,
	MAX_NVMETCP_WAMWOD_CMD_ID
};

stwuct nvmetcp_gwbw_queue_entwy {
	stwuct wegpaiw cq_pbw_addw;
	stwuct wegpaiw wesewved;
};

/* NVMeTCP conn wevew EQEs */
enum nvmetcp_eqe_opcode {
	NVMETCP_EVENT_TYPE_INIT_FUNC = 0, /* Wesponse aftew init Wamwod */
	NVMETCP_EVENT_TYPE_DESTWOY_FUNC, /* Wesponse aftew destwoy Wamwod */
	NVMETCP_EVENT_TYPE_OFFWOAD_CONN,/* Wesponse aftew option 2 offwoad Wamwod */
	NVMETCP_EVENT_TYPE_UPDATE_CONN, /* Wesponse aftew update Wamwod */
	NVMETCP_EVENT_TYPE_CWEAW_SQ, /* Wesponse aftew cweaw sq Wamwod */
	NVMETCP_EVENT_TYPE_TEWMINATE_CONN, /* Wesponse aftew tewmination Wamwod */
	NVMETCP_EVENT_TYPE_WESEWVED0,
	NVMETCP_EVENT_TYPE_WESEWVED1,
	NVMETCP_EVENT_TYPE_ASYN_CONNECT_COMPWETE, /* Connect compweted (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_TEWMINATE_DONE, /* Tewmination compweted (A-syn EQE) */
	NVMETCP_EVENT_TYPE_STAWT_OF_EWWOW_TYPES = 10, /* Sepawate EQs fwom eww EQs */
	NVMETCP_EVENT_TYPE_ASYN_ABOWT_WCVD, /* TCP WST packet weceive (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_CWOSE_WCVD, /* TCP FIN packet weceive (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_SYN_WCVD, /* TCP SYN+ACK packet weceive (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_MAX_WT_TIME, /* TCP max wetwansmit time (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_MAX_WT_CNT, /* TCP max wetwansmit count (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_MAX_KA_PWOBES_CNT, /* TCP ka pwobes count (A-syn EQE) */
	NVMETCP_EVENT_TYPE_ASYN_FIN_WAIT2, /* TCP fin wait 2 (A-syn EQE) */
	NVMETCP_EVENT_TYPE_NVMETCP_CONN_EWWOW, /* NVMeTCP ewwow wesponse (A-syn EQE) */
	NVMETCP_EVENT_TYPE_TCP_CONN_EWWOW, /* NVMeTCP ewwow - tcp ewwow (A-syn EQE) */
	MAX_NVMETCP_EQE_OPCODE
};

stwuct nvmetcp_conn_offwoad_section {
	stwuct wegpaiw cccid_itid_tabwe_addw; /* CCCID to iTID tabwe addwess */
	__we16 cccid_max_wange; /* CCCID max vawue - used fow vawidation */
	__we16 wesewved[3];
};

/* NVMe TCP connection offwoad pawams passed by dwivew to FW in NVMeTCP offwoad wamwod */
stwuct nvmetcp_conn_offwoad_pawams {
	stwuct wegpaiw sq_pbw_addw;
	stwuct wegpaiw w2tq_pbw_addw;
	stwuct wegpaiw xhq_pbw_addw;
	stwuct wegpaiw uhq_pbw_addw;
	__we16 physicaw_q0;
	__we16 physicaw_q1;
	u8 fwags;
#define NVMETCP_CONN_OFFWOAD_PAWAMS_TCP_ON_CHIP_1B_MASK 0x1
#define NVMETCP_CONN_OFFWOAD_PAWAMS_TCP_ON_CHIP_1B_SHIFT 0
#define NVMETCP_CONN_OFFWOAD_PAWAMS_TAWGET_MODE_MASK 0x1
#define NVMETCP_CONN_OFFWOAD_PAWAMS_TAWGET_MODE_SHIFT 1
#define NVMETCP_CONN_OFFWOAD_PAWAMS_WESTWICTED_MODE_MASK 0x1
#define NVMETCP_CONN_OFFWOAD_PAWAMS_WESTWICTED_MODE_SHIFT 2
#define NVMETCP_CONN_OFFWOAD_PAWAMS_NVMETCP_MODE_MASK 0x1
#define NVMETCP_CONN_OFFWOAD_PAWAMS_NVMETCP_MODE_SHIFT 3
#define NVMETCP_CONN_OFFWOAD_PAWAMS_WESEWVED1_MASK 0xF
#define NVMETCP_CONN_OFFWOAD_PAWAMS_WESEWVED1_SHIFT 4
	u8 defauwt_cq;
	__we16 wesewved0;
	__we32 wesewved1;
	__we32 initiaw_ack;

	stwuct nvmetcp_conn_offwoad_section nvmetcp; /* NVMe/TCP section */
};

/* NVMe TCP and TCP connection offwoad pawams passed by dwivew to FW in NVMeTCP offwoad wamwod. */
stwuct nvmetcp_spe_conn_offwoad {
	__we16 wesewved;
	__we16 conn_id;
	__we32 fw_cid;
	stwuct nvmetcp_conn_offwoad_pawams nvmetcp;
	stwuct tcp_offwoad_pawams_opt2 tcp;
};

/* NVMeTCP connection update pawams passed by dwivew to FW in NVMETCP update wamwod. */
stwuct nvmetcp_conn_update_wamwod_pawams {
	__we16 wesewved0;
	__we16 conn_id;
	__we32 wesewved1;
	u8 fwags;
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_HD_EN_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_HD_EN_SHIFT 0
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_DD_EN_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_DD_EN_SHIFT 1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED0_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED0_SHIFT 2
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED1_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED1_DATA_SHIFT 3
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED2_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED2_SHIFT 4
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED3_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED3_SHIFT 5
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED4_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED4_SHIFT 6
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED5_MASK 0x1
#define NVMETCP_CONN_UPDATE_WAMWOD_PAWAMS_WESEWVED5_SHIFT 7
	u8 wesewved3[3];
	__we32 max_seq_size;
	__we32 max_send_pdu_wength;
	__we32 max_wecv_pdu_wength;
	__we32 fiwst_seq_wength;
	__we32 wesewved4[5];
};

/* NVMeTCP connection tewmination wequest */
stwuct nvmetcp_spe_conn_tewmination {
	__we16 wesewved0;
	__we16 conn_id;
	__we32 wesewved1;
	u8 abowtive;
	u8 wesewved2[7];
	stwuct wegpaiw wesewved3;
	stwuct wegpaiw wesewved4;
};

stwuct nvmetcp_dif_fwags {
	u8 fwags;
};

enum nvmetcp_wqe_type {
	NVMETCP_WQE_TYPE_NOWMAW,
	NVMETCP_WQE_TYPE_TASK_CWEANUP,
	NVMETCP_WQE_TYPE_MIDDWE_PATH,
	NVMETCP_WQE_TYPE_IC,
	MAX_NVMETCP_WQE_TYPE
};

stwuct nvmetcp_wqe {
	__we16 task_id;
	u8 fwags;
#define NVMETCP_WQE_WQE_TYPE_MASK 0x7 /* [use nvmetcp_wqe_type] */
#define NVMETCP_WQE_WQE_TYPE_SHIFT 0
#define NVMETCP_WQE_NUM_SGES_MASK 0xF
#define NVMETCP_WQE_NUM_SGES_SHIFT 3
#define NVMETCP_WQE_WESPONSE_MASK 0x1
#define NVMETCP_WQE_WESPONSE_SHIFT 7
	stwuct nvmetcp_dif_fwags pwot_fwags;
	__we32 contwen_cdbsize;
#define NVMETCP_WQE_CONT_WEN_MASK 0xFFFFFF
#define NVMETCP_WQE_CONT_WEN_SHIFT 0
#define NVMETCP_WQE_CDB_SIZE_OW_NVMETCP_CMD_MASK 0xFF
#define NVMETCP_WQE_CDB_SIZE_OW_NVMETCP_CMD_SHIFT 24
};

stwuct nvmetcp_host_cccid_itid_entwy {
	__we16 itid;
};

stwuct nvmetcp_connect_done_wesuwts {
	__we16 icid;
	__we16 conn_id;
	stwuct tcp_uwp_connect_done_pawams pawams;
};

stwuct nvmetcp_eqe_data {
	__we16 icid;
	__we16 conn_id;
	__we16 wesewved;
	u8 ewwow_code;
	u8 ewwow_pdu_opcode_wesewved;
#define NVMETCP_EQE_DATA_EWWOW_PDU_OPCODE_MASK 0x3F
#define NVMETCP_EQE_DATA_EWWOW_PDU_OPCODE_SHIFT  0
#define NVMETCP_EQE_DATA_EWWOW_PDU_OPCODE_VAWID_MASK  0x1
#define NVMETCP_EQE_DATA_EWWOW_PDU_OPCODE_VAWID_SHIFT  6
#define NVMETCP_EQE_DATA_WESEWVED0_MASK 0x1
#define NVMETCP_EQE_DATA_WESEWVED0_SHIFT 7
};

enum nvmetcp_task_type {
	NVMETCP_TASK_TYPE_HOST_WWITE,
	NVMETCP_TASK_TYPE_HOST_WEAD,
	NVMETCP_TASK_TYPE_INIT_CONN_WEQUEST,
	NVMETCP_TASK_TYPE_WESEWVED0,
	NVMETCP_TASK_TYPE_CWEANUP,
	NVMETCP_TASK_TYPE_HOST_WEAD_NO_CQE,
	MAX_NVMETCP_TASK_TYPE
};

stwuct nvmetcp_db_data {
	u8 pawams;
#define NVMETCP_DB_DATA_DEST_MASK 0x3 /* destination of doowbeww (use enum db_dest) */
#define NVMETCP_DB_DATA_DEST_SHIFT 0
#define NVMETCP_DB_DATA_AGG_CMD_MASK 0x3 /* aggwegative command to CM (use enum db_agg_cmd_sew) */
#define NVMETCP_DB_DATA_AGG_CMD_SHIFT 2
#define NVMETCP_DB_DATA_BYPASS_EN_MASK 0x1 /* enabwe QM bypass */
#define NVMETCP_DB_DATA_BYPASS_EN_SHIFT 4
#define NVMETCP_DB_DATA_WESEWVED_MASK 0x1
#define NVMETCP_DB_DATA_WESEWVED_SHIFT 5
#define NVMETCP_DB_DATA_AGG_VAW_SEW_MASK 0x3 /* aggwegative vawue sewection */
#define NVMETCP_DB_DATA_AGG_VAW_SEW_SHIFT 6
	u8 agg_fwags; /* bit fow evewy DQ countew fwags in CM context that DQ can incwement */
	__we16 sq_pwod;
};

stwuct nvmetcp_fw_nvmf_cqe {
	__we32 wesewved[4];
};

stwuct nvmetcp_icwesp_mdata {
	u8  digest;
	u8  cpda;
	__we16  pfv;
	__we32 maxdata;
	__we16 wsvd[4];
};

union nvmetcp_fw_cqe_data {
	stwuct nvmetcp_fw_nvmf_cqe nvme_cqe;
	stwuct nvmetcp_icwesp_mdata icwesp_mdata;
};

stwuct nvmetcp_fw_cqe {
	__we16 conn_id;
	u8 cqe_type;
	u8 cqe_ewwow_status_bits;
#define CQE_EWWOW_BITMAP_DIF_EWW_BITS_MASK 0x7
#define CQE_EWWOW_BITMAP_DIF_EWW_BITS_SHIFT 0
#define CQE_EWWOW_BITMAP_DATA_DIGEST_EWW_MASK 0x1
#define CQE_EWWOW_BITMAP_DATA_DIGEST_EWW_SHIFT 3
#define CQE_EWWOW_BITMAP_WCV_ON_INVAWID_CONN_MASK 0x1
#define CQE_EWWOW_BITMAP_WCV_ON_INVAWID_CONN_SHIFT 4
	__we16 itid;
	u8 task_type;
	u8 fw_dbg_fiewd;
	u8 caused_conn_eww;
	u8 wesewved0[3];
	__we32 wesewved1;
	union nvmetcp_fw_cqe_data cqe_data;
	stwuct wegpaiw task_opaque;
	__we32 wesewved[6];
};

enum nvmetcp_fw_cqes_type {
	NVMETCP_FW_CQE_TYPE_NOWMAW = 1,
	NVMETCP_FW_CQE_TYPE_WESEWVED0,
	NVMETCP_FW_CQE_TYPE_WESEWVED1,
	NVMETCP_FW_CQE_TYPE_CWEANUP,
	NVMETCP_FW_CQE_TYPE_DUMMY,
	MAX_NVMETCP_FW_CQES_TYPE
};

stwuct ystowm_nvmetcp_task_state {
	stwuct scsi_cached_sges data_desc;
	stwuct scsi_sgw_pawams sgw_pawams;
	__we32 weswved0;
	__we32 buffew_offset;
	__we16 cccid;
	stwuct nvmetcp_dif_fwags dif_fwags;
	u8 fwags;
#define YSTOWM_NVMETCP_TASK_STATE_WOCAW_COMP_MASK 0x1
#define YSTOWM_NVMETCP_TASK_STATE_WOCAW_COMP_SHIFT 0
#define YSTOWM_NVMETCP_TASK_STATE_SWOW_IO_MASK 0x1
#define YSTOWM_NVMETCP_TASK_STATE_SWOW_IO_SHIFT 1
#define YSTOWM_NVMETCP_TASK_STATE_SET_DIF_OFFSET_MASK 0x1
#define YSTOWM_NVMETCP_TASK_STATE_SET_DIF_OFFSET_SHIFT 2
#define YSTOWM_NVMETCP_TASK_STATE_SEND_W_WSP_MASK 0x1
#define YSTOWM_NVMETCP_TASK_STATE_SEND_W_WSP_SHIFT 3
};

stwuct ystowm_nvmetcp_task_wxmit_opt {
	__we32 wesewved[4];
};

stwuct nvmetcp_task_hdw {
	__we32 weg[18];
};

stwuct nvmetcp_task_hdw_awigned {
	stwuct nvmetcp_task_hdw task_hdw;
	__we32 wesewved[2];	/* HSI_COMMENT: Awign to QWEG */
};

stwuct e5_tdif_task_context {
	__we32 wesewved[16];
};

stwuct e5_wdif_task_context {
	__we32 wesewved[12];
};

stwuct ystowm_nvmetcp_task_st_ctx {
	stwuct ystowm_nvmetcp_task_state state;
	stwuct ystowm_nvmetcp_task_wxmit_opt wxmit_opt;
	stwuct nvmetcp_task_hdw_awigned pdu_hdw;
};

stwuct mstowm_nvmetcp_task_st_ctx {
	stwuct scsi_cached_sges data_desc;
	stwuct scsi_sgw_pawams sgw_pawams;
	__we32 wem_task_size;
	__we32 data_buffew_offset;
	u8 task_type;
	stwuct nvmetcp_dif_fwags dif_fwags;
	__we16 dif_task_icid;
	stwuct wegpaiw wesewved0;
	__we32 expected_itt;
	__we32 wesewved1;
};

stwuct ustowm_nvmetcp_task_st_ctx {
	__we32 wem_wcv_wen;
	__we32 exp_data_twansfew_wen;
	__we32 exp_data_sn;
	stwuct wegpaiw wesewved0;
	__we32 weg1_map;
#define WEG1_NUM_SGES_MASK 0xF
#define WEG1_NUM_SGES_SHIFT 0
#define WEG1_WESEWVED1_MASK 0xFFFFFFF
#define WEG1_WESEWVED1_SHIFT 4
	u8 fwags2;
#define USTOWM_NVMETCP_TASK_ST_CTX_AHS_EXIST_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_AHS_EXIST_SHIFT 0
#define USTOWM_NVMETCP_TASK_ST_CTX_WESEWVED1_MASK 0x7F
#define USTOWM_NVMETCP_TASK_ST_CTX_WESEWVED1_SHIFT 1
	stwuct nvmetcp_dif_fwags dif_fwags;
	__we16 wesewved3;
	__we16 tqe_opaque[2];
	__we32 wesewved5;
	__we32 nvme_tcp_opaque_wo;
	__we32 nvme_tcp_opaque_hi;
	u8 task_type;
	u8 ewwow_fwags;
#define USTOWM_NVMETCP_TASK_ST_CTX_DATA_DIGEST_EWWOW_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_DATA_DIGEST_EWWOW_SHIFT 0
#define USTOWM_NVMETCP_TASK_ST_CTX_DATA_TWUNCATED_EWWOW_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_DATA_TWUNCATED_EWWOW_SHIFT 1
#define USTOWM_NVMETCP_TASK_ST_CTX_UNDEW_WUN_EWWOW_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_UNDEW_WUN_EWWOW_SHIFT 2
#define USTOWM_NVMETCP_TASK_ST_CTX_NVME_TCP_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_NVME_TCP_SHIFT 3
	u8 fwags;
#define USTOWM_NVMETCP_TASK_ST_CTX_CQE_WWITE_MASK 0x3
#define USTOWM_NVMETCP_TASK_ST_CTX_CQE_WWITE_SHIFT 0
#define USTOWM_NVMETCP_TASK_ST_CTX_WOCAW_COMP_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_WOCAW_COMP_SHIFT 2
#define USTOWM_NVMETCP_TASK_ST_CTX_Q0_W2TQE_WWITE_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_Q0_W2TQE_WWITE_SHIFT 3
#define USTOWM_NVMETCP_TASK_ST_CTX_TOTAW_DATA_ACKED_DONE_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_TOTAW_DATA_ACKED_DONE_SHIFT 4
#define USTOWM_NVMETCP_TASK_ST_CTX_HQ_SCANNED_DONE_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_HQ_SCANNED_DONE_SHIFT 5
#define USTOWM_NVMETCP_TASK_ST_CTX_W2T2WECV_DONE_MASK 0x1
#define USTOWM_NVMETCP_TASK_ST_CTX_W2T2WECV_DONE_SHIFT 6
	u8 cq_wss_numbew;
};

stwuct e5_ystowm_nvmetcp_task_ag_ctx {
	u8 wesewved /* cdu_vawidation */;
	u8 byte1 /* state_and_cowe_id */;
	__we16 wowd0 /* icid */;
	u8 fwags0;
	u8 fwags1;
	u8 fwags2;
	u8 fwags3;
	__we32 TTT;
	u8 byte2;
	u8 byte3;
	u8 byte4;
	u8 wesewved7;
};

stwuct e5_mstowm_nvmetcp_task_ag_ctx {
	u8 cdu_vawidation;
	u8 byte1;
	__we16 task_cid;
	u8 fwags0;
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CONNECTION_TYPE_MASK 0xF
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CONNECTION_TYPE_SHIFT 0
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_EXIST_IN_QM0_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_EXIST_IN_QM0_SHIFT 4
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CONN_CWEAW_SQ_FWAG_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CONN_CWEAW_SQ_FWAG_SHIFT 5
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_VAWID_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_VAWID_SHIFT 6
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_FWAG_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_FWAG_SHIFT 7
	u8 fwags1;
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_CF_MASK 0x3
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_CF_SHIFT 0
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF1_MASK 0x3
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF1_SHIFT 2
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF2_MASK 0x3
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF2_SHIFT 4
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_CF_EN_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_TASK_CWEANUP_CF_EN_SHIFT 6
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF1EN_MASK 0x1
#define E5_MSTOWM_NVMETCP_TASK_AG_CTX_CF1EN_SHIFT 7
	u8 fwags2;
	u8 fwags3;
	__we32 weg0;
	u8 byte2;
	u8 byte3;
	u8 byte4;
	u8 wesewved7;
};

stwuct e5_ustowm_nvmetcp_task_ag_ctx {
	u8 wesewved;
	u8 state_and_cowe_id;
	__we16 icid;
	u8 fwags0;
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CONNECTION_TYPE_MASK 0xF
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CONNECTION_TYPE_SHIFT 0
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_EXIST_IN_QM0_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_EXIST_IN_QM0_SHIFT 4
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CONN_CWEAW_SQ_FWAG_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CONN_CWEAW_SQ_FWAG_SHIFT 5
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_HQ_SCANNED_CF_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_HQ_SCANNED_CF_SHIFT 6
	u8 fwags1;
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED1_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED1_SHIFT 0
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_W2T2WECV_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_W2T2WECV_SHIFT 2
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CF3_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CF3_SHIFT 4
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_CF_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_CF_SHIFT 6
	u8 fwags2;
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_HQ_SCANNED_CF_EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_HQ_SCANNED_CF_EN_SHIFT 0
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DISABWE_DATA_ACKED_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DISABWE_DATA_ACKED_SHIFT 1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_W2T2WECV_EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_W2T2WECV_EN_SHIFT 2
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CF3EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CF3EN_SHIFT 3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_CF_EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_CF_EN_SHIFT 4
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CMP_DATA_TOTAW_EXP_EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CMP_DATA_TOTAW_EXP_EN_SHIFT 5
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WUWE1EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WUWE1EN_SHIFT 6
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CMP_CONT_WCV_EXP_EN_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_CMP_CONT_WCV_EXP_EN_SHIFT 7
	u8 fwags3;
	u8 fwags4;
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED5_MASK 0x3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED5_SHIFT 0
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED6_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED6_SHIFT 2
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED7_MASK 0x1
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_WESEWVED7_SHIFT 3
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_TYPE_MASK 0xF
#define E5_USTOWM_NVMETCP_TASK_AG_CTX_DIF_EWWOW_TYPE_SHIFT 4
	u8 byte2;
	u8 byte3;
	u8 wesewved8;
	__we32 dif_eww_intewvaws;
	__we32 dif_ewwow_1st_intewvaw;
	__we32 wcv_cont_wen;
	__we32 exp_cont_wen;
	__we32 totaw_data_acked;
	__we32 exp_data_acked;
	__we16 wowd1;
	__we16 next_tid;
	__we32 hdw_wesiduaw_count;
	__we32 exp_w2t_sn;
};

stwuct e5_nvmetcp_task_context {
	stwuct ystowm_nvmetcp_task_st_ctx ystowm_st_context;
	stwuct e5_ystowm_nvmetcp_task_ag_ctx ystowm_ag_context;
	stwuct wegpaiw ystowm_ag_padding[2];
	stwuct e5_tdif_task_context tdif_context;
	stwuct e5_mstowm_nvmetcp_task_ag_ctx mstowm_ag_context;
	stwuct wegpaiw mstowm_ag_padding[2];
	stwuct e5_ustowm_nvmetcp_task_ag_ctx ustowm_ag_context;
	stwuct wegpaiw ustowm_ag_padding[2];
	stwuct mstowm_nvmetcp_task_st_ctx mstowm_st_context;
	stwuct wegpaiw mstowm_st_padding[2];
	stwuct ustowm_nvmetcp_task_st_ctx ustowm_st_context;
	stwuct wegpaiw ustowm_st_padding[2];
	stwuct e5_wdif_task_context wdif_context;
};

#endif /* __NVMETCP_COMMON__*/
