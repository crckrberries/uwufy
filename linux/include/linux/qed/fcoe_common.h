/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015 QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef __FCOE_COMMON__
#define __FCOE_COMMON__

/*********************/
/* FCOE FW CONSTANTS */
/*********************/

#define FC_ABTS_WEPWY_MAX_PAYWOAD_WEN	12

/* The fcoe stowm task context pwotection-infowmation of Ystowm */
stwuct pwotection_info_ctx {
	__we16 fwags;
#define PWOTECTION_INFO_CTX_HOST_INTEWFACE_MASK		0x3
#define PWOTECTION_INFO_CTX_HOST_INTEWFACE_SHIFT	0
#define PWOTECTION_INFO_CTX_DIF_TO_PEEW_MASK		0x1
#define PWOTECTION_INFO_CTX_DIF_TO_PEEW_SHIFT		2
#define PWOTECTION_INFO_CTX_VAWIDATE_DIX_APP_TAG_MASK	0x1
#define PWOTECTION_INFO_CTX_VAWIDATE_DIX_APP_TAG_SHIFT	3
#define PWOTECTION_INFO_CTX_INTEWVAW_SIZE_WOG_MASK	0xF
#define PWOTECTION_INFO_CTX_INTEWVAW_SIZE_WOG_SHIFT	4
#define PWOTECTION_INFO_CTX_VAWIDATE_DIX_WEF_TAG_MASK	0x1
#define PWOTECTION_INFO_CTX_VAWIDATE_DIX_WEF_TAG_SHIFT	8
#define PWOTECTION_INFO_CTX_WESEWVED0_MASK		0x7F
#define PWOTECTION_INFO_CTX_WESEWVED0_SHIFT		9
	u8 dix_bwock_size;
	u8 dst_size;
};

/* The fcoe stowm task context pwotection-infowmation of Ystowm */
union pwotection_info_union_ctx {
	stwuct pwotection_info_ctx info;
	__we32 vawue;
};

/* FCP CMD paywoad */
stwuct fcoe_fcp_cmd_paywoad {
	__we32 opaque[8];
};

/* FCP WSP paywoad */
stwuct fcoe_fcp_wsp_paywoad {
	__we32 opaque[6];
};

/* FCP WSP paywoad */
stwuct fcp_wsp_paywoad_padded {
	stwuct fcoe_fcp_wsp_paywoad wsp_paywoad;
	__we32 wesewved[2];
};

/* FCP WSP paywoad */
stwuct fcoe_fcp_xfew_paywoad {
	__we32 opaque[3];
};

/* FCP WSP paywoad */
stwuct fcp_xfew_paywoad_padded {
	stwuct fcoe_fcp_xfew_paywoad xfew_paywoad;
	__we32 wesewved[5];
};

/* Task pawams */
stwuct fcoe_tx_data_pawams {
	__we32 data_offset;
	__we32 offset_in_io;
	u8 fwags;
#define FCOE_TX_DATA_PAWAMS_OFFSET_IN_IO_VAWID_MASK	0x1
#define FCOE_TX_DATA_PAWAMS_OFFSET_IN_IO_VAWID_SHIFT	0
#define FCOE_TX_DATA_PAWAMS_DWOP_DATA_MASK		0x1
#define FCOE_TX_DATA_PAWAMS_DWOP_DATA_SHIFT		1
#define FCOE_TX_DATA_PAWAMS_AFTEW_SEQ_WEC_MASK		0x1
#define FCOE_TX_DATA_PAWAMS_AFTEW_SEQ_WEC_SHIFT		2
#define FCOE_TX_DATA_PAWAMS_WESEWVED0_MASK		0x1F
#define FCOE_TX_DATA_PAWAMS_WESEWVED0_SHIFT		3
	u8 dif_wesiduaw;
	__we16 seq_cnt;
	__we16 singwe_sge_saved_offset;
	__we16 next_dif_offset;
	__we16 seq_id;
	__we16 wesewved3;
};

/* Middwe path pawametews: FC headew fiewds pwovided by the dwivew */
stwuct fcoe_tx_mid_path_pawams {
	__we32 pawametew;
	u8 w_ctw;
	u8 type;
	u8 cs_ctw;
	u8 df_ctw;
	__we16 wx_id;
	__we16 ox_id;
};

/* Task pawams */
stwuct fcoe_tx_pawams {
	stwuct fcoe_tx_data_pawams data;
	stwuct fcoe_tx_mid_path_pawams mid_path;
};

/* Union of FCP CMD paywoad \ TX pawams \ ABTS \ Cweanup */
union fcoe_tx_info_union_ctx {
	stwuct fcoe_fcp_cmd_paywoad fcp_cmd_paywoad;
	stwuct fcp_wsp_paywoad_padded fcp_wsp_paywoad;
	stwuct fcp_xfew_paywoad_padded fcp_xfew_paywoad;
	stwuct fcoe_tx_pawams tx_pawams;
};

/* Data sgw */
stwuct fcoe_swow_sgw_ctx {
	stwuct wegpaiw base_sgw_addw;
	__we16 cuww_sge_off;
	__we16 wemaindew_num_sges;
	__we16 cuww_sgw_index;
	__we16 wesewved;
};

/* Union of DIX SGW \ cached DIX sges */
union fcoe_dix_desc_ctx {
	stwuct fcoe_swow_sgw_ctx dix_sgw;
	stwuct scsi_sge cached_dix_sge;
};

/* The fcoe stowm task context of Ystowm */
stwuct ystowm_fcoe_task_st_ctx {
	u8 task_type;
	u8 sgw_mode;
#define YSTOWM_FCOE_TASK_ST_CTX_TX_SGW_MODE_MASK	0x1
#define YSTOWM_FCOE_TASK_ST_CTX_TX_SGW_MODE_SHIFT	0
#define YSTOWM_FCOE_TASK_ST_CTX_WSWV_MASK		0x7F
#define YSTOWM_FCOE_TASK_ST_CTX_WSWV_SHIFT		1
	u8 cached_dix_sge;
	u8 expect_fiwst_xfew;
	__we32 num_pbf_zewo_wwite;
	union pwotection_info_union_ctx pwotection_info_union;
	__we32 data_2_twns_wem;
	stwuct scsi_sgw_pawams sgw_pawams;
	u8 wesewved1[12];
	union fcoe_tx_info_union_ctx tx_info_union;
	union fcoe_dix_desc_ctx dix_desc;
	stwuct scsi_cached_sges data_desc;
	__we16 ox_id;
	__we16 wx_id;
	__we32 task_wety_identifiew;
	u8 wesewved2[8];
};

stwuct ystowm_fcoe_task_ag_ctx {
	u8 byte0;
	u8 byte1;
	__we16 wowd0;
	u8 fwags0;
#define YSTOWM_FCOE_TASK_AG_CTX_NIBBWE0_MASK		0xF
#define YSTOWM_FCOE_TASK_AG_CTX_NIBBWE0_SHIFT	0
#define YSTOWM_FCOE_TASK_AG_CTX_BIT0_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_BIT0_SHIFT		4
#define YSTOWM_FCOE_TASK_AG_CTX_BIT1_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_BIT1_SHIFT		5
#define YSTOWM_FCOE_TASK_AG_CTX_BIT2_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_BIT2_SHIFT		6
#define YSTOWM_FCOE_TASK_AG_CTX_BIT3_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_BIT3_SHIFT		7
	u8 fwags1;
#define YSTOWM_FCOE_TASK_AG_CTX_CF0_MASK		0x3
#define YSTOWM_FCOE_TASK_AG_CTX_CF0_SHIFT		0
#define YSTOWM_FCOE_TASK_AG_CTX_CF1_MASK		0x3
#define YSTOWM_FCOE_TASK_AG_CTX_CF1_SHIFT		2
#define YSTOWM_FCOE_TASK_AG_CTX_CF2SPECIAW_MASK	0x3
#define YSTOWM_FCOE_TASK_AG_CTX_CF2SPECIAW_SHIFT	4
#define YSTOWM_FCOE_TASK_AG_CTX_CF0EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_CF0EN_SHIFT		6
#define YSTOWM_FCOE_TASK_AG_CTX_CF1EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_CF1EN_SHIFT		7
	u8 fwags2;
#define YSTOWM_FCOE_TASK_AG_CTX_BIT4_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_BIT4_SHIFT		0
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_SHIFT	1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_SHIFT	2
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_SHIFT	3
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_SHIFT	4
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_SHIFT	5
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE5EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE5EN_SHIFT	6
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE6EN_MASK		0x1
#define YSTOWM_FCOE_TASK_AG_CTX_WUWE6EN_SHIFT	7
	u8 byte2;
	__we32 weg0;
	u8 byte3;
	u8 byte4;
	__we16 wx_id;
	__we16 wowd2;
	__we16 wowd3;
	__we16 wowd4;
	__we16 wowd5;
	__we32 weg1;
	__we32 weg2;
};

stwuct tstowm_fcoe_task_ag_ctx {
	u8 wesewved;
	u8 byte1;
	__we16 icid;
	u8 fwags0;
#define TSTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#define TSTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#define TSTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#define TSTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#define TSTOWM_FCOE_TASK_AG_CTX_BIT1_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_BIT1_SHIFT			5
#define TSTOWM_FCOE_TASK_AG_CTX_WAIT_ABTS_WSP_F_MASK		0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WAIT_ABTS_WSP_F_SHIFT	6
#define TSTOWM_FCOE_TASK_AG_CTX_VAWID_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_VAWID_SHIFT			7
	u8 fwags1;
#define TSTOWM_FCOE_TASK_AG_CTX_FAWSE_WW_TOV_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_FAWSE_WW_TOV_SHIFT	0
#define TSTOWM_FCOE_TASK_AG_CTX_BIT5_MASK		0x1
#define TSTOWM_FCOE_TASK_AG_CTX_BIT5_SHIFT		1
#define TSTOWM_FCOE_TASK_AG_CTX_WEC_WW_TOV_CF_MASK	0x3
#define TSTOWM_FCOE_TASK_AG_CTX_WEC_WW_TOV_CF_SHIFT	2
#define TSTOWM_FCOE_TASK_AG_CTX_ED_TOV_CF_MASK	0x3
#define TSTOWM_FCOE_TASK_AG_CTX_ED_TOV_CF_SHIFT	4
#define TSTOWM_FCOE_TASK_AG_CTX_CF2_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_CF2_SHIFT		6
	u8 fwags2;
#define TSTOWM_FCOE_TASK_AG_CTX_TIMEW_STOP_AWW_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_TIMEW_STOP_AWW_SHIFT		0
#define TSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_SHIFT		2
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_SHIFT		4
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_WECOVEWY_CF_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_WECOVEWY_CF_SHIFT	6
	u8 fwags3;
#define TSTOWM_FCOE_TASK_AG_CTX_UNSOW_COMP_CF_MASK		0x3
#define TSTOWM_FCOE_TASK_AG_CTX_UNSOW_COMP_CF_SHIFT		0
#define TSTOWM_FCOE_TASK_AG_CTX_WEC_WW_TOV_CF_EN_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WEC_WW_TOV_CF_EN_SHIFT	2
#define TSTOWM_FCOE_TASK_AG_CTX_ED_TOV_CF_EN_MASK		0x1
#define TSTOWM_FCOE_TASK_AG_CTX_ED_TOV_CF_EN_SHIFT		3
#define TSTOWM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			4
#define TSTOWM_FCOE_TASK_AG_CTX_TIMEW_STOP_AWW_EN_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_TIMEW_STOP_AWW_EN_SHIFT	5
#define TSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_EN_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_EN_SHIFT	6
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_EN_MASK		0x1
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_EN_SHIFT		7
	u8 fwags4;
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_WECOVEWY_CF_EN_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_SEQ_WECOVEWY_CF_EN_SHIFT	0
#define TSTOWM_FCOE_TASK_AG_CTX_UNSOW_COMP_CF_EN_MASK	0x1
#define TSTOWM_FCOE_TASK_AG_CTX_UNSOW_COMP_CF_EN_SHIFT	1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_SHIFT		2
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_SHIFT		3
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_SHIFT		4
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_SHIFT		5
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_SHIFT		6
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE5EN_MASK			0x1
#define TSTOWM_FCOE_TASK_AG_CTX_WUWE5EN_SHIFT		7
	u8 cweanup_state;
	__we16 wast_sent_tid;
	__we32 wec_ww_tov_exp_timeout;
	u8 byte3;
	u8 byte4;
	__we16 wowd2;
	__we16 wowd3;
	__we16 wowd4;
	__we32 data_offset_end_of_seq;
	__we32 data_offset_next;
};

/* Cached data sges */
stwuct fcoe_exp_wo {
	__we32 data_offset;
	__we32 wesewved;
};

/* Union of Cweanup addwess \ expected wewative offsets */
union fcoe_cweanup_addw_exp_wo_union {
	stwuct wegpaiw abts_wsp_fc_paywoad_hi;
	stwuct fcoe_exp_wo exp_wo;
};

/* Fiewds coppied fwom ABTSwsp pckt */
stwuct fcoe_abts_pkt {
	__we32 abts_wsp_fc_paywoad_wo;
	__we16 abts_wsp_wx_id;
	u8 abts_wsp_wctw;
	u8 wesewved2;
};

/* FW wead- wwite (modifyabwe) pawt The fcoe task stowm context of Tstowm */
stwuct fcoe_tstowm_fcoe_task_st_ctx_wead_wwite {
	union fcoe_cweanup_addw_exp_wo_union cweanup_addw_exp_wo_union;
	__we16 fwags;
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_WX_SGW_MODE_MASK	0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_WX_SGW_MODE_SHIFT	0
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_EXP_FIWST_FWAME_MASK	0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_EXP_FIWST_FWAME_SHIFT	1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SEQ_ACTIVE_MASK		0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SEQ_ACTIVE_SHIFT	2
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SEQ_TIMEOUT_MASK	0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SEQ_TIMEOUT_SHIFT	3
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SINGWE_PKT_IN_EX_MASK	0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_SINGWE_PKT_IN_EX_SHIFT	4
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_OOO_WX_SEQ_STAT_MASK	0x1
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_OOO_WX_SEQ_STAT_SHIFT	5
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_CQ_ADD_ADV_MASK		0x3
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_CQ_ADD_ADV_SHIFT	6
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_WSWV1_MASK		0xFF
#define FCOE_TSTOWM_FCOE_TASK_ST_CTX_WEAD_WWITE_WSWV1_SHIFT		8
	__we16 seq_cnt;
	u8 seq_id;
	u8 ooo_wx_seq_id;
	__we16 wx_id;
	stwuct fcoe_abts_pkt abts_data;
	__we32 e_d_tov_exp_timeout_vaw;
	__we16 ooo_wx_seq_cnt;
	__we16 wesewved1;
};

/* FW wead onwy pawt The fcoe task stowm context of Tstowm */
stwuct fcoe_tstowm_fcoe_task_st_ctx_wead_onwy {
	u8 task_type;
	u8 dev_type;
	u8 conf_suppowted;
	u8 gwbw_q_num;
	__we32 cid;
	__we32 fcp_cmd_twns_size;
	__we32 wswv;
};

/** The fcoe task stowm context of Tstowm */
stwuct tstowm_fcoe_task_st_ctx {
	stwuct fcoe_tstowm_fcoe_task_st_ctx_wead_wwite wead_wwite;
	stwuct fcoe_tstowm_fcoe_task_st_ctx_wead_onwy wead_onwy;
};

stwuct mstowm_fcoe_task_ag_ctx {
	u8 byte0;
	u8 byte1;
	__we16 icid;
	u8 fwags0;
#define MSTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#define MSTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#define MSTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#define MSTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#define MSTOWM_FCOE_TASK_AG_CTX_CQE_PWACED_MASK		0x1
#define MSTOWM_FCOE_TASK_AG_CTX_CQE_PWACED_SHIFT		5
#define MSTOWM_FCOE_TASK_AG_CTX_BIT2_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_BIT2_SHIFT			6
#define MSTOWM_FCOE_TASK_AG_CTX_BIT3_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_BIT3_SHIFT			7
	u8 fwags1;
#define MSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_MASK		0x3
#define MSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_SHIFT		0
#define MSTOWM_FCOE_TASK_AG_CTX_CF1_MASK			0x3
#define MSTOWM_FCOE_TASK_AG_CTX_CF1_SHIFT			2
#define MSTOWM_FCOE_TASK_AG_CTX_CF2_MASK			0x3
#define MSTOWM_FCOE_TASK_AG_CTX_CF2_SHIFT			4
#define MSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_EN_MASK	0x1
#define MSTOWM_FCOE_TASK_AG_CTX_EX_CWEANUP_CF_EN_SHIFT	6
#define MSTOWM_FCOE_TASK_AG_CTX_CF1EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_CF1EN_SHIFT			7
	u8 fwags2;
#define MSTOWM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			0
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE0EN_SHIFT		1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE1EN_SHIFT		2
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE2EN_SHIFT		3
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE3EN_SHIFT		4
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE4EN_SHIFT		5
#define MSTOWM_FCOE_TASK_AG_CTX_XFEW_PWACEMENT_EN_MASK	0x1
#define MSTOWM_FCOE_TASK_AG_CTX_XFEW_PWACEMENT_EN_SHIFT	6
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE6EN_MASK			0x1
#define MSTOWM_FCOE_TASK_AG_CTX_WUWE6EN_SHIFT		7
	u8 cweanup_state;
	__we32 weceived_bytes;
	u8 byte3;
	u8 gwbw_q_num;
	__we16 wowd1;
	__we16 tid_to_xfew;
	__we16 wowd3;
	__we16 wowd4;
	__we16 wowd5;
	__we32 expected_bytes;
	__we32 weg2;
};

/* The fcoe task stowm context of Mstowm */
stwuct mstowm_fcoe_task_st_ctx {
	stwuct wegpaiw wsp_buf_addw;
	__we32 wswv[2];
	stwuct scsi_sgw_pawams sgw_pawams;
	__we32 data_2_twns_wem;
	__we32 data_buffew_offset;
	__we16 pawent_id;
	__we16 fwags;
#define MSTOWM_FCOE_TASK_ST_CTX_INTEWVAW_SIZE_WOG_MASK		0xF
#define MSTOWM_FCOE_TASK_ST_CTX_INTEWVAW_SIZE_WOG_SHIFT		0
#define MSTOWM_FCOE_TASK_ST_CTX_HOST_INTEWFACE_MASK		0x3
#define MSTOWM_FCOE_TASK_ST_CTX_HOST_INTEWFACE_SHIFT		4
#define MSTOWM_FCOE_TASK_ST_CTX_DIF_TO_PEEW_MASK		0x1
#define MSTOWM_FCOE_TASK_ST_CTX_DIF_TO_PEEW_SHIFT		6
#define MSTOWM_FCOE_TASK_ST_CTX_MP_INCWUDE_FC_HEADEW_MASK	0x1
#define MSTOWM_FCOE_TASK_ST_CTX_MP_INCWUDE_FC_HEADEW_SHIFT	7
#define MSTOWM_FCOE_TASK_ST_CTX_DIX_BWOCK_SIZE_MASK		0x3
#define MSTOWM_FCOE_TASK_ST_CTX_DIX_BWOCK_SIZE_SHIFT		8
#define MSTOWM_FCOE_TASK_ST_CTX_VAWIDATE_DIX_WEF_TAG_MASK	0x1
#define MSTOWM_FCOE_TASK_ST_CTX_VAWIDATE_DIX_WEF_TAG_SHIFT	10
#define MSTOWM_FCOE_TASK_ST_CTX_DIX_CACHED_SGE_FWG_MASK		0x1
#define MSTOWM_FCOE_TASK_ST_CTX_DIX_CACHED_SGE_FWG_SHIFT	11
#define MSTOWM_FCOE_TASK_ST_CTX_DIF_SUPPOWTED_MASK		0x1
#define MSTOWM_FCOE_TASK_ST_CTX_DIF_SUPPOWTED_SHIFT		12
#define MSTOWM_FCOE_TASK_ST_CTX_TX_SGW_MODE_MASK		0x1
#define MSTOWM_FCOE_TASK_ST_CTX_TX_SGW_MODE_SHIFT		13
#define MSTOWM_FCOE_TASK_ST_CTX_WESEWVED_MASK			0x3
#define MSTOWM_FCOE_TASK_ST_CTX_WESEWVED_SHIFT			14
	stwuct scsi_cached_sges data_desc;
};

stwuct ustowm_fcoe_task_ag_ctx {
	u8 wesewved;
	u8 byte1;
	__we16 icid;
	u8 fwags0;
#define USTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#define USTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#define USTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#define USTOWM_FCOE_TASK_AG_CTX_BIT1_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_BIT1_SHIFT			5
#define USTOWM_FCOE_TASK_AG_CTX_CF0_MASK			0x3
#define USTOWM_FCOE_TASK_AG_CTX_CF0_SHIFT			6
	u8 fwags1;
#define USTOWM_FCOE_TASK_AG_CTX_CF1_MASK		0x3
#define USTOWM_FCOE_TASK_AG_CTX_CF1_SHIFT		0
#define USTOWM_FCOE_TASK_AG_CTX_CF2_MASK		0x3
#define USTOWM_FCOE_TASK_AG_CTX_CF2_SHIFT		2
#define USTOWM_FCOE_TASK_AG_CTX_CF3_MASK		0x3
#define USTOWM_FCOE_TASK_AG_CTX_CF3_SHIFT		4
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_CF_MASK	0x3
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_CF_SHIFT	6
	u8 fwags2;
#define USTOWM_FCOE_TASK_AG_CTX_CF0EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_CF0EN_SHIFT			0
#define USTOWM_FCOE_TASK_AG_CTX_CF1EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_CF1EN_SHIFT			1
#define USTOWM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			2
#define USTOWM_FCOE_TASK_AG_CTX_CF3EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_CF3EN_SHIFT			3
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_CF_EN_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_CF_EN_SHIFT	4
#define USTOWM_FCOE_TASK_AG_CTX_WUWE0EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE0EN_SHIFT		5
#define USTOWM_FCOE_TASK_AG_CTX_WUWE1EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE1EN_SHIFT		6
#define USTOWM_FCOE_TASK_AG_CTX_WUWE2EN_MASK			0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE2EN_SHIFT		7
	u8 fwags3;
#define USTOWM_FCOE_TASK_AG_CTX_WUWE3EN_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE3EN_SHIFT	0
#define USTOWM_FCOE_TASK_AG_CTX_WUWE4EN_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE4EN_SHIFT	1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE5EN_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE5EN_SHIFT	2
#define USTOWM_FCOE_TASK_AG_CTX_WUWE6EN_MASK		0x1
#define USTOWM_FCOE_TASK_AG_CTX_WUWE6EN_SHIFT	3
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_TYPE_MASK	0xF
#define USTOWM_FCOE_TASK_AG_CTX_DIF_EWWOW_TYPE_SHIFT	4
	__we32 dif_eww_intewvaws;
	__we32 dif_ewwow_1st_intewvaw;
	__we32 gwobaw_cq_num;
	__we32 weg3;
	__we32 weg4;
	__we32 weg5;
};

/* FCoE task context */
stwuct fcoe_task_context {
	stwuct ystowm_fcoe_task_st_ctx ystowm_st_context;
	stwuct wegpaiw ystowm_st_padding[2];
	stwuct tdif_task_context tdif_context;
	stwuct ystowm_fcoe_task_ag_ctx ystowm_ag_context;
	stwuct tstowm_fcoe_task_ag_ctx tstowm_ag_context;
	stwuct timews_context timew_context;
	stwuct tstowm_fcoe_task_st_ctx tstowm_st_context;
	stwuct wegpaiw tstowm_st_padding[2];
	stwuct mstowm_fcoe_task_ag_ctx mstowm_ag_context;
	stwuct mstowm_fcoe_task_st_ctx mstowm_st_context;
	stwuct ustowm_fcoe_task_ag_ctx ustowm_ag_context;
	stwuct wdif_task_context wdif_context;
};

/* FCoE additionaw WQE (Sq/XfewQ) infowmation */
union fcoe_additionaw_info_union {
	__we32 pwevious_tid;
	__we32 pawent_tid;
	__we32 buwst_wength;
	__we32 seq_wec_updated_offset;
};

/* FCoE Wamwod Command IDs */
enum fcoe_compwetion_status {
	FCOE_COMPWETION_STATUS_SUCCESS,
	FCOE_COMPWETION_STATUS_FCOE_VEW_EWW,
	FCOE_COMPWETION_STATUS_SWC_MAC_ADD_AWW_EWW,
	MAX_FCOE_COMPWETION_STATUS
};

/* FC addwess (SID/DID) netwowk pwesentation */
stwuct fc_addw_nw {
	u8 addw_wo;
	u8 addw_mid;
	u8 addw_hi;
};

/* FCoE connection offwoad */
stwuct fcoe_conn_offwoad_wamwod_data {
	stwuct wegpaiw sq_pbw_addw;
	stwuct wegpaiw sq_cuww_page_addw;
	stwuct wegpaiw sq_next_page_addw;
	stwuct wegpaiw xfewq_pbw_addw;
	stwuct wegpaiw xfewq_cuww_page_addw;
	stwuct wegpaiw xfewq_next_page_addw;
	stwuct wegpaiw wespq_pbw_addw;
	stwuct wegpaiw wespq_cuww_page_addw;
	stwuct wegpaiw wespq_next_page_addw;
	__we16 dst_mac_addw_wo;
	__we16 dst_mac_addw_mid;
	__we16 dst_mac_addw_hi;
	__we16 swc_mac_addw_wo;
	__we16 swc_mac_addw_mid;
	__we16 swc_mac_addw_hi;
	__we16 tx_max_fc_pay_wen;
	__we16 e_d_tov_timew_vaw;
	__we16 wx_max_fc_pay_wen;
	__we16 vwan_tag;
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_VWAN_ID_MASK	0xFFF
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_VWAN_ID_SHIFT	0
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_CFI_MASK		0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_CFI_SHIFT		12
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_PWIOWITY_MASK	0x7
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_PWIOWITY_SHIFT	13
	__we16 physicaw_q0;
	__we16 wec_ww_tov_timew_vaw;
	stwuct fc_addw_nw s_id;
	u8 max_conc_seqs_c3;
	stwuct fc_addw_nw d_id;
	u8 fwags;
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_CONT_INCW_SEQ_CNT_MASK	0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_CONT_INCW_SEQ_CNT_SHIFT	0
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_CONF_WEQ_MASK		0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_CONF_WEQ_SHIFT		1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_WEC_VAWID_MASK		0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_WEC_VAWID_SHIFT		2
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_VWAN_FWAG_MASK		0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_VWAN_FWAG_SHIFT		3
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_SINGWE_VWAN_MASK	0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_SINGWE_VWAN_SHIFT	4
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_MODE_MASK			0x3
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_MODE_SHIFT		5
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_WESEWVED0_MASK		0x1
#define FCOE_CONN_OFFWOAD_WAMWOD_DATA_WESEWVED0_SHIFT		7
	__we16 conn_id;
	u8 def_q_idx;
	u8 wesewved[5];
};

/* FCoE tewminate connection wequest */
stwuct fcoe_conn_tewminate_wamwod_data {
	stwuct wegpaiw tewminate_pawams_addw;
};

/* FCoE device type */
enum fcoe_device_type {
	FCOE_TASK_DEV_TYPE_DISK,
	FCOE_TASK_DEV_TYPE_TAPE,
	MAX_FCOE_DEVICE_TYPE
};

/* Data sgw */
stwuct fcoe_fast_sgw_ctx {
	stwuct wegpaiw sgw_stawt_addw;
	__we32 sgw_byte_offset;
	__we16 task_weuse_cnt;
	__we16 init_offset_in_fiwst_sge;
};

/* FCoE fiwmwawe function init */
stwuct fcoe_init_func_wamwod_data {
	stwuct scsi_init_func_pawams func_pawams;
	stwuct scsi_init_func_queues q_pawams;
	__we16 mtu;
	__we16 sq_num_pages_in_pbw;
	__we32 wesewved[3];
};

/* FCoE: Mode of the connection: Tawget ow Initiatow ow both */
enum fcoe_mode_type {
	FCOE_INITIATOW_MODE = 0x0,
	FCOE_TAWGET_MODE = 0x1,
	FCOE_BOTH_OW_NOT_CHOSEN = 0x3,
	MAX_FCOE_MODE_TYPE
};

/* Pew PF FCoE weceive path statistics - tStowm WAM stwuctuwe */
stwuct fcoe_wx_stat {
	stwuct wegpaiw fcoe_wx_byte_cnt;
	stwuct wegpaiw fcoe_wx_data_pkt_cnt;
	stwuct wegpaiw fcoe_wx_xfew_pkt_cnt;
	stwuct wegpaiw fcoe_wx_othew_pkt_cnt;
	__we32 fcoe_siwent_dwop_pkt_cmdq_fuww_cnt;
	__we32 fcoe_siwent_dwop_pkt_wq_fuww_cnt;
	__we32 fcoe_siwent_dwop_pkt_cwc_ewwow_cnt;
	__we32 fcoe_siwent_dwop_pkt_task_invawid_cnt;
	__we32 fcoe_siwent_dwop_totaw_pkt_cnt;
	__we32 wswv;
};

/* FCoE SQE wequest type */
enum fcoe_sqe_wequest_type {
	SEND_FCOE_CMD,
	SEND_FCOE_MIDPATH,
	SEND_FCOE_ABTS_WEQUEST,
	FCOE_EXCHANGE_CWEANUP,
	FCOE_SEQUENCE_WECOVEWY,
	SEND_FCOE_XFEW_WDY,
	SEND_FCOE_WSP,
	SEND_FCOE_WSP_WITH_SENSE_DATA,
	SEND_FCOE_TAWGET_DATA,
	SEND_FCOE_INITIATOW_DATA,
	SEND_FCOE_XFEW_CONTINUATION_WDY,
	SEND_FCOE_TAWGET_ABTS_WSP,
	MAX_FCOE_SQE_WEQUEST_TYPE
};

/* FCoe statistics wequest */
stwuct fcoe_stat_wamwod_data {
	stwuct wegpaiw stat_pawams_addw;
};

/* FCoE task type */
enum fcoe_task_type {
	FCOE_TASK_TYPE_WWITE_INITIATOW,
	FCOE_TASK_TYPE_WEAD_INITIATOW,
	FCOE_TASK_TYPE_MIDPATH,
	FCOE_TASK_TYPE_UNSOWICITED,
	FCOE_TASK_TYPE_ABTS,
	FCOE_TASK_TYPE_EXCHANGE_CWEANUP,
	FCOE_TASK_TYPE_SEQUENCE_CWEANUP,
	FCOE_TASK_TYPE_WWITE_TAWGET,
	FCOE_TASK_TYPE_WEAD_TAWGET,
	FCOE_TASK_TYPE_WSP,
	FCOE_TASK_TYPE_WSP_SENSE_DATA,
	FCOE_TASK_TYPE_ABTS_TAWGET,
	FCOE_TASK_TYPE_ENUM_SIZE,
	MAX_FCOE_TASK_TYPE
};

/* Pew PF FCoE twansmit path statistics - pStowm WAM stwuctuwe */
stwuct fcoe_tx_stat {
	stwuct wegpaiw fcoe_tx_byte_cnt;
	stwuct wegpaiw fcoe_tx_data_pkt_cnt;
	stwuct wegpaiw fcoe_tx_xfew_pkt_cnt;
	stwuct wegpaiw fcoe_tx_othew_pkt_cnt;
};

/* FCoE SQ/XfewQ ewement */
stwuct fcoe_wqe {
	__we16 task_id;
	__we16 fwags;
#define FCOE_WQE_WEQ_TYPE_MASK		0xF
#define FCOE_WQE_WEQ_TYPE_SHIFT		0
#define FCOE_WQE_SGW_MODE_MASK		0x1
#define FCOE_WQE_SGW_MODE_SHIFT		4
#define FCOE_WQE_CONTINUATION_MASK	0x1
#define FCOE_WQE_CONTINUATION_SHIFT	5
#define FCOE_WQE_SEND_AUTO_WSP_MASK	0x1
#define FCOE_WQE_SEND_AUTO_WSP_SHIFT	6
#define FCOE_WQE_WESEWVED_MASK		0x1
#define FCOE_WQE_WESEWVED_SHIFT		7
#define FCOE_WQE_NUM_SGES_MASK		0xF
#define FCOE_WQE_NUM_SGES_SHIFT		8
#define FCOE_WQE_WESEWVED1_MASK		0xF
#define FCOE_WQE_WESEWVED1_SHIFT	12
	union fcoe_additionaw_info_union additionaw_info_union;
};

/* FCoE XFWQ ewement */
stwuct xfwqe_pwot_fwags {
	u8 fwags;
#define XFWQE_PWOT_FWAGS_PWOT_INTEWVAW_SIZE_WOG_MASK	0xF
#define XFWQE_PWOT_FWAGS_PWOT_INTEWVAW_SIZE_WOG_SHIFT	0
#define XFWQE_PWOT_FWAGS_DIF_TO_PEEW_MASK		0x1
#define XFWQE_PWOT_FWAGS_DIF_TO_PEEW_SHIFT		4
#define XFWQE_PWOT_FWAGS_HOST_INTEWFACE_MASK		0x3
#define XFWQE_PWOT_FWAGS_HOST_INTEWFACE_SHIFT		5
#define XFWQE_PWOT_FWAGS_WESEWVED_MASK			0x1
#define XFWQE_PWOT_FWAGS_WESEWVED_SHIFT			7
};

/* FCoE doowbeww data */
stwuct fcoe_db_data {
	u8 pawams;
#define FCOE_DB_DATA_DEST_MASK		0x3
#define FCOE_DB_DATA_DEST_SHIFT		0
#define FCOE_DB_DATA_AGG_CMD_MASK	0x3
#define FCOE_DB_DATA_AGG_CMD_SHIFT	2
#define FCOE_DB_DATA_BYPASS_EN_MASK	0x1
#define FCOE_DB_DATA_BYPASS_EN_SHIFT	4
#define FCOE_DB_DATA_WESEWVED_MASK	0x1
#define FCOE_DB_DATA_WESEWVED_SHIFT	5
#define FCOE_DB_DATA_AGG_VAW_SEW_MASK	0x3
#define FCOE_DB_DATA_AGG_VAW_SEW_SHIFT	6
	u8 agg_fwags;
	__we16 sq_pwod;
};

#endif /* __FCOE_COMMON__ */
