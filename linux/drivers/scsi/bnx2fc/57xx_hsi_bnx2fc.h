/* 57xx_hsi_bnx2fc.h: QWogic Winux FCoE offwoad dwivew.
 * Handwes opewations such as session offwoad/upwoad etc, and manages
 * session wesouwces such as connection id and qp wesouwces.
 *
 * Copywight (c) 2008-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014-2016 QWogic Cowpowation
 * Copywight (c) 2016-2017 Cavium Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 */

#ifndef __57XX_FCOE_HSI_WINUX_WE__
#define __57XX_FCOE_HSI_WINUX_WE__

/*
 * common data fow aww pwotocows
 */
stwuct b577xx_doowbeww_hdw {
	u8 headew;
#define B577XX_DOOWBEWW_HDW_WX (0x1<<0)
#define B577XX_DOOWBEWW_HDW_WX_SHIFT 0
#define B577XX_DOOWBEWW_HDW_DB_TYPE (0x1<<1)
#define B577XX_DOOWBEWW_HDW_DB_TYPE_SHIFT 1
#define B577XX_DOOWBEWW_HDW_DPM_SIZE (0x3<<2)
#define B577XX_DOOWBEWW_HDW_DPM_SIZE_SHIFT 2
#define B577XX_DOOWBEWW_HDW_CONN_TYPE (0xF<<4)
#define B577XX_DOOWBEWW_HDW_CONN_TYPE_SHIFT 4
};

/*
 * doowbeww message sent to the chip
 */
stwuct b577xx_doowbeww {
#if defined(__BIG_ENDIAN)
	u16 zewo_fiww2;
	u8 zewo_fiww1;
	stwuct b577xx_doowbeww_hdw headew;
#ewif defined(__WITTWE_ENDIAN)
	stwuct b577xx_doowbeww_hdw headew;
	u8 zewo_fiww1;
	u16 zewo_fiww2;
#endif
};



/*
 * doowbeww message sent to the chip
 */
stwuct b577xx_doowbeww_set_pwod {
#if defined(__BIG_ENDIAN)
	u16 pwod;
	u8 zewo_fiww1;
	stwuct b577xx_doowbeww_hdw headew;
#ewif defined(__WITTWE_ENDIAN)
	stwuct b577xx_doowbeww_hdw headew;
	u8 zewo_fiww1;
	u16 pwod;
#endif
};


stwuct wegpaiw {
	__we32 wo;
	__we32 hi;
};


/*
 * ABTS info $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_abts_info {
	__we16 abowted_task_id;
	__we16 wesewved0;
	__we32 wesewved1;
};


/*
 * Fixed size stwuctuwe in owdew to pwant it in Union stwuctuwe
 * $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_abts_wsp_union {
	u8 w_ctw;
	u8 wswv[3];
	__we32 abts_wsp_paywoad[7];
};


/*
 * 4 wegs size $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_bd_ctx {
	__we32 buf_addw_hi;
	__we32 buf_addw_wo;
	__we16 buf_wen;
	__we16 wswv0;
	__we16 fwags;
	__we16 wswv1;
};


/*
 * FCoE cached sges context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_cached_sge_ctx {
	stwuct wegpaiw cuw_buf_addw;
	__we16 cuw_buf_wem;
	__we16 second_buf_wem;
	stwuct wegpaiw second_buf_addw;
};


/*
 * Cweanup info $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_cweanup_info {
	__we16 cweaned_task_id;
	__we16 wowwed_tx_seq_cnt;
	__we32 wowwed_tx_data_offset;
};


/*
 * Fcp WSP fwags $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fcp_wsp_fwags {
	u8 fwags;
#define FCOE_FCP_WSP_FWAGS_FCP_WSP_WEN_VAWID (0x1<<0)
#define FCOE_FCP_WSP_FWAGS_FCP_WSP_WEN_VAWID_SHIFT 0
#define FCOE_FCP_WSP_FWAGS_FCP_SNS_WEN_VAWID (0x1<<1)
#define FCOE_FCP_WSP_FWAGS_FCP_SNS_WEN_VAWID_SHIFT 1
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_OVEW (0x1<<2)
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_OVEW_SHIFT 2
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_UNDEW (0x1<<3)
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_UNDEW_SHIFT 3
#define FCOE_FCP_WSP_FWAGS_FCP_CONF_WEQ (0x1<<4)
#define FCOE_FCP_WSP_FWAGS_FCP_CONF_WEQ_SHIFT 4
#define FCOE_FCP_WSP_FWAGS_FCP_BIDI_FWAGS (0x7<<5)
#define FCOE_FCP_WSP_FWAGS_FCP_BIDI_FWAGS_SHIFT 5
};

/*
 * Fcp WSP paywoad $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fcp_wsp_paywoad {
	stwuct wegpaiw wesewved0;
	__we32 fcp_wesid;
	u8 scsi_status_code;
	stwuct fcoe_fcp_wsp_fwags fcp_fwags;
	__we16 wetwy_deway_timew;
	__we32 fcp_wsp_wen;
	__we32 fcp_sns_wen;
};

/*
 * Fixed size stwuctuwe in owdew to pwant it in Union stwuctuwe
 * $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fcp_wsp_union {
	stwuct fcoe_fcp_wsp_paywoad paywoad;
	stwuct wegpaiw wesewved0;
};

/*
 * FC headew $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fc_hdw {
	u8 s_id[3];
	u8 cs_ctw;
	u8 d_id[3];
	u8 w_ctw;
	__we16 seq_cnt;
	u8 df_ctw;
	u8 seq_id;
	u8 f_ctw[3];
	u8 type;
	__we32 pawametews;
	__we16 wx_id;
	__we16 ox_id;
};

/*
 * FC headew union $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_mp_wsp_union {
	stwuct fcoe_fc_hdw fc_hdw;
	__we32 mp_paywoad_wen;
	__we32 wswv;
};

/*
 * Compwetion infowmation $$KEEP_ENDIANNESS$$
 */
union fcoe_comp_fwow_info {
	stwuct fcoe_fcp_wsp_union fcp_wsp;
	stwuct fcoe_abts_wsp_union abts_wsp;
	stwuct fcoe_mp_wsp_union mp_wsp;
	__we32 opaque[8];
};


/*
 * Extewnaw ABTS info $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_ext_abts_info {
	__we32 wswv0[6];
	stwuct fcoe_abts_info ctx;
};


/*
 * Extewnaw cweanup info $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_ext_cweanup_info {
	__we32 wswv0[6];
	stwuct fcoe_cweanup_info ctx;
};


/*
 * Fcoe FW Tx sequence context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fw_tx_seq_ctx {
	__we32 data_offset;
	__we16 seq_cnt;
	__we16 wswv0;
};

/*
 * Fcoe extewnaw FW Tx sequence context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_ext_fw_tx_seq_ctx {
	__we32 wswv0[6];
	stwuct fcoe_fw_tx_seq_ctx ctx;
};


/*
 * FCoE muwtipwe sges context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_muw_sges_ctx {
	stwuct wegpaiw cuw_sge_addw;
	__we16 cuw_sge_off;
	u8 cuw_sge_idx;
	u8 sgw_size;
};

/*
 * FCoE extewnaw muwtipwe sges context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_ext_muw_sges_ctx {
	stwuct fcoe_muw_sges_ctx muw_sgw;
	stwuct wegpaiw wswv0;
};


/*
 * FCP CMD paywoad $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fcp_cmd_paywoad {
	__we32 opaque[8];
};





/*
 * Fcp xfw wdy paywoad $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fcp_xfw_wdy_paywoad {
	__we32 buwst_wen;
	__we32 data_wo;
};


/*
 * FC fwame $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_fc_fwame {
	stwuct fcoe_fc_hdw fc_hdw;
	__we32 wesewved0[2];
};




/*
 * FCoE KCQ CQE pawametews $$KEEP_ENDIANNESS$$
 */
union fcoe_kcqe_pawams {
	__we32 wesewved0[4];
};

/*
 * FCoE KCQ CQE $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kcqe {
	__we32 fcoe_conn_id;
	__we32 compwetion_status;
	__we32 fcoe_conn_context_id;
	union fcoe_kcqe_pawams pawams;
	__we16 qe_sewf_seq;
	u8 op_code;
	u8 fwags;
#define FCOE_KCQE_WESEWVED0 (0x7<<0)
#define FCOE_KCQE_WESEWVED0_SHIFT 0
#define FCOE_KCQE_WAMWOD_COMPWETION (0x1<<3)
#define FCOE_KCQE_WAMWOD_COMPWETION_SHIFT 3
#define FCOE_KCQE_WAYEW_CODE (0x7<<4)
#define FCOE_KCQE_WAYEW_CODE_SHIFT 4
#define FCOE_KCQE_WINKED_WITH_NEXT (0x1<<7)
#define FCOE_KCQE_WINKED_WITH_NEXT_SHIFT 7
};



/*
 * FCoE KWQE headew $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_headew {
	u8 op_code;
	u8 fwags;
#define FCOE_KWQE_HEADEW_WESEWVED0 (0xF<<0)
#define FCOE_KWQE_HEADEW_WESEWVED0_SHIFT 0
#define FCOE_KWQE_HEADEW_WAYEW_CODE (0x7<<4)
#define FCOE_KWQE_HEADEW_WAYEW_CODE_SHIFT 4
#define FCOE_KWQE_HEADEW_WESEWVED1 (0x1<<7)
#define FCOE_KWQE_HEADEW_WESEWVED1_SHIFT 7
};

/*
 * FCoE fiwmwawe init wequest 1 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_init1 {
	__we16 num_tasks;
	stwuct fcoe_kwqe_headew hdw;
	__we32 task_wist_pbw_addw_wo;
	__we32 task_wist_pbw_addw_hi;
	__we32 dummy_buffew_addw_wo;
	__we32 dummy_buffew_addw_hi;
	__we16 sq_num_wqes;
	__we16 wq_num_wqes;
	__we16 wq_buffew_wog_size;
	__we16 cq_num_wqes;
	__we16 mtu;
	u8 num_sessions_wog;
	u8 fwags;
#define FCOE_KWQE_INIT1_WOG_PAGE_SIZE (0xF<<0)
#define FCOE_KWQE_INIT1_WOG_PAGE_SIZE_SHIFT 0
#define FCOE_KWQE_INIT1_WOG_CACHED_PBES_PEW_FUNC (0x7<<4)
#define FCOE_KWQE_INIT1_WOG_CACHED_PBES_PEW_FUNC_SHIFT 4
#define FCOE_KWQE_INIT1_WESEWVED1 (0x1<<7)
#define FCOE_KWQE_INIT1_WESEWVED1_SHIFT 7
};

/*
 * FCoE fiwmwawe init wequest 2 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_init2 {
	u8 hsi_majow_vewsion;
	u8 hsi_minow_vewsion;
	stwuct fcoe_kwqe_headew hdw;
	__we32 hash_tbw_pbw_addw_wo;
	__we32 hash_tbw_pbw_addw_hi;
	__we32 t2_hash_tbw_addw_wo;
	__we32 t2_hash_tbw_addw_hi;
	__we32 t2_ptw_hash_tbw_addw_wo;
	__we32 t2_ptw_hash_tbw_addw_hi;
	__we32 fwee_wist_count;
};

/*
 * FCoE fiwmwawe init wequest 3 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_init3 {
	__we16 wesewved0;
	stwuct fcoe_kwqe_headew hdw;
	__we32 ewwow_bit_map_wo;
	__we32 ewwow_bit_map_hi;
	u8 pewf_config;
	u8 wesewved21[3];
	__we32 wesewved2[4];
};

/*
 * FCoE connection offwoad wequest 1 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_offwoad1 {
	__we16 fcoe_conn_id;
	stwuct fcoe_kwqe_headew hdw;
	__we32 sq_addw_wo;
	__we32 sq_addw_hi;
	__we32 wq_pbw_addw_wo;
	__we32 wq_pbw_addw_hi;
	__we32 wq_fiwst_pbe_addw_wo;
	__we32 wq_fiwst_pbe_addw_hi;
	__we16 wq_pwod;
	__we16 wesewved0;
};

/*
 * FCoE connection offwoad wequest 2 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_offwoad2 {
	__we16 tx_max_fc_pay_wen;
	stwuct fcoe_kwqe_headew hdw;
	__we32 cq_addw_wo;
	__we32 cq_addw_hi;
	__we32 xfewq_addw_wo;
	__we32 xfewq_addw_hi;
	__we32 conn_db_addw_wo;
	__we32 conn_db_addw_hi;
	__we32 wesewved1;
};

/*
 * FCoE connection offwoad wequest 3 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_offwoad3 {
	__we16 vwan_tag;
#define FCOE_KWQE_CONN_OFFWOAD3_VWAN_ID (0xFFF<<0)
#define FCOE_KWQE_CONN_OFFWOAD3_VWAN_ID_SHIFT 0
#define FCOE_KWQE_CONN_OFFWOAD3_CFI (0x1<<12)
#define FCOE_KWQE_CONN_OFFWOAD3_CFI_SHIFT 12
#define FCOE_KWQE_CONN_OFFWOAD3_PWIOWITY (0x7<<13)
#define FCOE_KWQE_CONN_OFFWOAD3_PWIOWITY_SHIFT 13
	stwuct fcoe_kwqe_headew hdw;
	u8 s_id[3];
	u8 tx_max_conc_seqs_c3;
	u8 d_id[3];
	u8 fwags;
#define FCOE_KWQE_CONN_OFFWOAD3_B_MUW_N_POWT_IDS (0x1<<0)
#define FCOE_KWQE_CONN_OFFWOAD3_B_MUW_N_POWT_IDS_SHIFT 0
#define FCOE_KWQE_CONN_OFFWOAD3_B_E_D_TOV_WES (0x1<<1)
#define FCOE_KWQE_CONN_OFFWOAD3_B_E_D_TOV_WES_SHIFT 1
#define FCOE_KWQE_CONN_OFFWOAD3_B_CONT_INCW_SEQ_CNT (0x1<<2)
#define FCOE_KWQE_CONN_OFFWOAD3_B_CONT_INCW_SEQ_CNT_SHIFT 2
#define FCOE_KWQE_CONN_OFFWOAD3_B_CONF_WEQ (0x1<<3)
#define FCOE_KWQE_CONN_OFFWOAD3_B_CONF_WEQ_SHIFT 3
#define FCOE_KWQE_CONN_OFFWOAD3_B_WEC_VAWID (0x1<<4)
#define FCOE_KWQE_CONN_OFFWOAD3_B_WEC_VAWID_SHIFT 4
#define FCOE_KWQE_CONN_OFFWOAD3_B_C2_VAWID (0x1<<5)
#define FCOE_KWQE_CONN_OFFWOAD3_B_C2_VAWID_SHIFT 5
#define FCOE_KWQE_CONN_OFFWOAD3_B_ACK_0 (0x1<<6)
#define FCOE_KWQE_CONN_OFFWOAD3_B_ACK_0_SHIFT 6
#define FCOE_KWQE_CONN_OFFWOAD3_B_VWAN_FWAG (0x1<<7)
#define FCOE_KWQE_CONN_OFFWOAD3_B_VWAN_FWAG_SHIFT 7
	__we32 wesewved;
	__we32 confq_fiwst_pbe_addw_wo;
	__we32 confq_fiwst_pbe_addw_hi;
	__we16 tx_totaw_conc_seqs;
	__we16 wx_max_fc_pay_wen;
	__we16 wx_totaw_conc_seqs;
	u8 wx_max_conc_seqs_c3;
	u8 wx_open_seqs_exch_c3;
};

/*
 * FCoE connection offwoad wequest 4 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_offwoad4 {
	u8 e_d_tov_timew_vaw;
	u8 wesewved2;
	stwuct fcoe_kwqe_headew hdw;
	u8 swc_mac_addw_wo[2];
	u8 swc_mac_addw_mid[2];
	u8 swc_mac_addw_hi[2];
	u8 dst_mac_addw_hi[2];
	u8 dst_mac_addw_wo[2];
	u8 dst_mac_addw_mid[2];
	__we32 wcq_addw_wo;
	__we32 wcq_addw_hi;
	__we32 confq_pbw_base_addw_wo;
	__we32 confq_pbw_base_addw_hi;
};

/*
 * FCoE connection enabwe wequest $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_enabwe_disabwe {
	__we16 wesewved0;
	stwuct fcoe_kwqe_headew hdw;
	u8 swc_mac_addw_wo[2];
	u8 swc_mac_addw_mid[2];
	u8 swc_mac_addw_hi[2];
	u16 vwan_tag;
#define FCOE_KWQE_CONN_ENABWE_DISABWE_VWAN_ID (0xFFF<<0)
#define FCOE_KWQE_CONN_ENABWE_DISABWE_VWAN_ID_SHIFT 0
#define FCOE_KWQE_CONN_ENABWE_DISABWE_CFI (0x1<<12)
#define FCOE_KWQE_CONN_ENABWE_DISABWE_CFI_SHIFT 12
#define FCOE_KWQE_CONN_ENABWE_DISABWE_PWIOWITY (0x7<<13)
#define FCOE_KWQE_CONN_ENABWE_DISABWE_PWIOWITY_SHIFT 13
	u8 dst_mac_addw_wo[2];
	u8 dst_mac_addw_mid[2];
	u8 dst_mac_addw_hi[2];
	__we16 wesewved1;
	u8 s_id[3];
	u8 vwan_fwag;
	u8 d_id[3];
	u8 wesewved3;
	__we32 context_id;
	__we32 conn_id;
	__we32 wesewved4;
};

/*
 * FCoE connection destwoy wequest $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_conn_destwoy {
	__we16 wesewved0;
	stwuct fcoe_kwqe_headew hdw;
	__we32 context_id;
	__we32 conn_id;
	__we32 wesewved1[5];
};

/*
 * FCoe destwoy wequest $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_destwoy {
	__we16 wesewved0;
	stwuct fcoe_kwqe_headew hdw;
	__we32 wesewved1[7];
};

/*
 * FCoe statistics wequest $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_kwqe_stat {
	__we16 wesewved0;
	stwuct fcoe_kwqe_headew hdw;
	__we32 stat_pawams_addw_wo;
	__we32 stat_pawams_addw_hi;
	__we32 wesewved1[5];
};

/*
 * FCoE KWQ WQE $$KEEP_ENDIANNESS$$
 */
union fcoe_kwqe {
	stwuct fcoe_kwqe_init1 init1;
	stwuct fcoe_kwqe_init2 init2;
	stwuct fcoe_kwqe_init3 init3;
	stwuct fcoe_kwqe_conn_offwoad1 conn_offwoad1;
	stwuct fcoe_kwqe_conn_offwoad2 conn_offwoad2;
	stwuct fcoe_kwqe_conn_offwoad3 conn_offwoad3;
	stwuct fcoe_kwqe_conn_offwoad4 conn_offwoad4;
	stwuct fcoe_kwqe_conn_enabwe_disabwe conn_enabwe_disabwe;
	stwuct fcoe_kwqe_conn_destwoy conn_destwoy;
	stwuct fcoe_kwqe_destwoy destwoy;
	stwuct fcoe_kwqe_stat statistics;
};
















/*
 * TX SGW context $$KEEP_ENDIANNESS$$
 */
union fcoe_sgw_union_ctx {
	stwuct fcoe_cached_sge_ctx cached_sge;
	stwuct fcoe_ext_muw_sges_ctx sgw;
	__we32 opaque[5];
};

/*
 * Data-In/EWS/BWS infowmation $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wead_fwow_info {
	union fcoe_sgw_union_ctx sgw_ctx;
	__we32 wswv0[3];
};


/*
 * Fcoe stat context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_s_stat_ctx {
	u8 fwags;
#define FCOE_S_STAT_CTX_ACTIVE (0x1<<0)
#define FCOE_S_STAT_CTX_ACTIVE_SHIFT 0
#define FCOE_S_STAT_CTX_ACK_ABOWT_SEQ_COND (0x1<<1)
#define FCOE_S_STAT_CTX_ACK_ABOWT_SEQ_COND_SHIFT 1
#define FCOE_S_STAT_CTX_ABTS_PEWFOWMED (0x1<<2)
#define FCOE_S_STAT_CTX_ABTS_PEWFOWMED_SHIFT 2
#define FCOE_S_STAT_CTX_SEQ_TIMEOUT (0x1<<3)
#define FCOE_S_STAT_CTX_SEQ_TIMEOUT_SHIFT 3
#define FCOE_S_STAT_CTX_P_WJT (0x1<<4)
#define FCOE_S_STAT_CTX_P_WJT_SHIFT 4
#define FCOE_S_STAT_CTX_ACK_EOFT (0x1<<5)
#define FCOE_S_STAT_CTX_ACK_EOFT_SHIFT 5
#define FCOE_S_STAT_CTX_WSWV1 (0x3<<6)
#define FCOE_S_STAT_CTX_WSWV1_SHIFT 6
};

/*
 * Fcoe wx seq context $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wx_seq_ctx {
	u8 seq_id;
	stwuct fcoe_s_stat_ctx s_stat;
	__we16 seq_cnt;
	__we32 wow_exp_wo;
	__we32 high_exp_wo;
};


/*
 * Fcoe wx_ww union context $$KEEP_ENDIANNESS$$
 */
union fcoe_wx_ww_union_ctx {
	stwuct fcoe_wead_fwow_info wead_info;
	union fcoe_comp_fwow_info comp_info;
	__we32 opaque[8];
};



/*
 * FCoE SQ ewement $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_sqe {
	__we16 wqe;
#define FCOE_SQE_TASK_ID (0x7FFF<<0)
#define FCOE_SQE_TASK_ID_SHIFT 0
#define FCOE_SQE_TOGGWE_BIT (0x1<<15)
#define FCOE_SQE_TOGGWE_BIT_SHIFT 15
};



/*
 * 14 wegs $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_tx_onwy {
	union fcoe_sgw_union_ctx sgw_ctx;
	__we32 wswv0;
};

/*
 * 32 bytes (8 wegs) used fow TX onwy puwposes $$KEEP_ENDIANNESS$$
 */
union fcoe_tx_ww_wx_wd_union_ctx {
	stwuct fcoe_fc_fwame tx_fwame;
	stwuct fcoe_fcp_cmd_paywoad fcp_cmd;
	stwuct fcoe_ext_cweanup_info cweanup;
	stwuct fcoe_ext_abts_info abts;
	stwuct fcoe_ext_fw_tx_seq_ctx tx_seq;
	__we32 opaque[8];
};

/*
 * tce_tx_ww_wx_wd_const $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_tx_ww_wx_wd_const {
	u8 init_fwags;
#define FCOE_TCE_TX_WW_WX_WD_CONST_TASK_TYPE (0x7<<0)
#define FCOE_TCE_TX_WW_WX_WD_CONST_TASK_TYPE_SHIFT 0
#define FCOE_TCE_TX_WW_WX_WD_CONST_DEV_TYPE (0x1<<3)
#define FCOE_TCE_TX_WW_WX_WD_CONST_DEV_TYPE_SHIFT 3
#define FCOE_TCE_TX_WW_WX_WD_CONST_CWASS_TYPE (0x1<<4)
#define FCOE_TCE_TX_WW_WX_WD_CONST_CWASS_TYPE_SHIFT 4
#define FCOE_TCE_TX_WW_WX_WD_CONST_CACHED_SGE (0x3<<5)
#define FCOE_TCE_TX_WW_WX_WD_CONST_CACHED_SGE_SHIFT 5
#define FCOE_TCE_TX_WW_WX_WD_CONST_SUPPOWT_WEC_TOV (0x1<<7)
#define FCOE_TCE_TX_WW_WX_WD_CONST_SUPPOWT_WEC_TOV_SHIFT 7
	u8 tx_fwags;
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_VAWID (0x1<<0)
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_VAWID_SHIFT 0
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_STATE (0xF<<1)
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_STATE_SHIFT 1
#define FCOE_TCE_TX_WW_WX_WD_CONST_WSWV1 (0x1<<5)
#define FCOE_TCE_TX_WW_WX_WD_CONST_WSWV1_SHIFT 5
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_SEQ_INIT (0x1<<6)
#define FCOE_TCE_TX_WW_WX_WD_CONST_TX_SEQ_INIT_SHIFT 6
#define FCOE_TCE_TX_WW_WX_WD_CONST_WSWV2 (0x1<<7)
#define FCOE_TCE_TX_WW_WX_WD_CONST_WSWV2_SHIFT 7
	__we16 wswv3;
	__we32 vewify_tx_seq;
};

/*
 * tce_tx_ww_wx_wd $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_tx_ww_wx_wd {
	union fcoe_tx_ww_wx_wd_union_ctx union_ctx;
	stwuct fcoe_tce_tx_ww_wx_wd_const const_ctx;
};

/*
 * tce_wx_ww_tx_wd_const $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_wx_ww_tx_wd_const {
	__we32 data_2_twns;
	__we32 init_fwags;
#define FCOE_TCE_WX_WW_TX_WD_CONST_CID (0xFFFFFF<<0)
#define FCOE_TCE_WX_WW_TX_WD_CONST_CID_SHIFT 0
#define FCOE_TCE_WX_WW_TX_WD_CONST_WSWV0 (0xFF<<24)
#define FCOE_TCE_WX_WW_TX_WD_CONST_WSWV0_SHIFT 24
};

/*
 * tce_wx_ww_tx_wd_vaw $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_wx_ww_tx_wd_vaw {
	__we16 wx_fwags;
#define FCOE_TCE_WX_WW_TX_WD_VAW_WSWV1 (0xF<<0)
#define FCOE_TCE_WX_WW_TX_WD_VAW_WSWV1_SHIFT 0
#define FCOE_TCE_WX_WW_TX_WD_VAW_NUM_WQ_WQE (0x7<<4)
#define FCOE_TCE_WX_WW_TX_WD_VAW_NUM_WQ_WQE_SHIFT 4
#define FCOE_TCE_WX_WW_TX_WD_VAW_CONF_WEQ (0x1<<7)
#define FCOE_TCE_WX_WW_TX_WD_VAW_CONF_WEQ_SHIFT 7
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_STATE (0xF<<8)
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_STATE_SHIFT 8
#define FCOE_TCE_WX_WW_TX_WD_VAW_EXP_FIWST_FWAME (0x1<<12)
#define FCOE_TCE_WX_WW_TX_WD_VAW_EXP_FIWST_FWAME_SHIFT 12
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_SEQ_INIT (0x1<<13)
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_SEQ_INIT_SHIFT 13
#define FCOE_TCE_WX_WW_TX_WD_VAW_WSWV2 (0x1<<14)
#define FCOE_TCE_WX_WW_TX_WD_VAW_WSWV2_SHIFT 14
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_VAWID (0x1<<15)
#define FCOE_TCE_WX_WW_TX_WD_VAW_WX_VAWID_SHIFT 15
	__we16 wx_id;
	stwuct fcoe_fcp_xfw_wdy_paywoad fcp_xfw_wdy;
};

/*
 * tce_wx_ww_tx_wd $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_wx_ww_tx_wd {
	stwuct fcoe_tce_wx_ww_tx_wd_const const_ctx;
	stwuct fcoe_tce_wx_ww_tx_wd_vaw vaw_ctx;
};

/*
 * tce_wx_onwy $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tce_wx_onwy {
	stwuct fcoe_wx_seq_ctx wx_seq_ctx;
	union fcoe_wx_ww_union_ctx union_ctx;
};

/*
 * task_ctx_entwy $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_task_ctx_entwy {
	stwuct fcoe_tce_tx_onwy txww_onwy;
	stwuct fcoe_tce_tx_ww_wx_wd txww_wxwd;
	stwuct fcoe_tce_wx_ww_tx_wd wxww_txwd;
	stwuct fcoe_tce_wx_onwy wxww_onwy;
};










/*
 * FCoE XFWQ ewement $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_xfwqe {
	__we16 wqe;
#define FCOE_XFWQE_TASK_ID (0x7FFF<<0)
#define FCOE_XFWQE_TASK_ID_SHIFT 0
#define FCOE_XFWQE_TOGGWE_BIT (0x1<<15)
#define FCOE_XFWQE_TOGGWE_BIT_SHIFT 15
};


/*
 * fcoe wx doowbeww message sent to the chip $$KEEP_ENDIANNESS$$
 */
stwuct b577xx_fcoe_wx_doowbeww {
	stwuct b577xx_doowbeww_hdw hdw;
	u8 pawams;
#define B577XX_FCOE_WX_DOOWBEWW_NEGATIVE_AWM (0x1F<<0)
#define B577XX_FCOE_WX_DOOWBEWW_NEGATIVE_AWM_SHIFT 0
#define B577XX_FCOE_WX_DOOWBEWW_OPCODE (0x7<<5)
#define B577XX_FCOE_WX_DOOWBEWW_OPCODE_SHIFT 5
	__we16 doowbeww_cq_cons;
};


/*
 * FCoE CONFQ ewement $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_confqe {
	__we16 ox_id;
	__we16 wx_id;
	__we32 pawam;
};


/*
 * FCoE connection data base
 */
stwuct fcoe_conn_db {
#if defined(__BIG_ENDIAN)
	u16 wswv0;
	u16 wq_pwod;
#ewif defined(__WITTWE_ENDIAN)
	u16 wq_pwod;
	u16 wswv0;
#endif
	u32 wswv1;
	stwuct wegpaiw cq_awm;
};


/*
 * FCoE CQ ewement $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_cqe {
	__we16 wqe;
#define FCOE_CQE_CQE_INFO (0x3FFF<<0)
#define FCOE_CQE_CQE_INFO_SHIFT 0
#define FCOE_CQE_CQE_TYPE (0x1<<14)
#define FCOE_CQE_CQE_TYPE_SHIFT 14
#define FCOE_CQE_TOGGWE_BIT (0x1<<15)
#define FCOE_CQE_TOGGWE_BIT_SHIFT 15
};


/*
 * FCoE ewwow/wawning wepowting entwy $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_pawtiaw_eww_wepowt_entwy {
	__we32 eww_wawn_bitmap_wo;
	__we32 eww_wawn_bitmap_hi;
	__we32 tx_buf_off;
	__we32 wx_buf_off;
};

/*
 * FCoE ewwow/wawning wepowting entwy $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_eww_wepowt_entwy {
	stwuct fcoe_pawtiaw_eww_wepowt_entwy data;
	stwuct fcoe_fc_hdw fc_hdw;
};


/*
 * FCoE hash tabwe entwy (32 bytes) $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_hash_tabwe_entwy {
	u8 s_id_0;
	u8 s_id_1;
	u8 s_id_2;
	u8 d_id_0;
	u8 d_id_1;
	u8 d_id_2;
	__we16 dst_mac_addw_hi;
	__we16 dst_mac_addw_mid;
	__we16 dst_mac_addw_wo;
	__we16 swc_mac_addw_hi;
	__we16 vwan_id;
	__we16 swc_mac_addw_wo;
	__we16 swc_mac_addw_mid;
	u8 vwan_fwag;
	u8 wesewved0;
	__we16 wesewved1;
	__we32 wesewved2;
	__we32 fiewd_id;
#define FCOE_HASH_TABWE_ENTWY_CID (0xFFFFFF<<0)
#define FCOE_HASH_TABWE_ENTWY_CID_SHIFT 0
#define FCOE_HASH_TABWE_ENTWY_WESEWVED3 (0x7F<<24)
#define FCOE_HASH_TABWE_ENTWY_WESEWVED3_SHIFT 24
#define FCOE_HASH_TABWE_ENTWY_VAWID (0x1<<31)
#define FCOE_HASH_TABWE_ENTWY_VAWID_SHIFT 31
};


/*
 * FCoE WCQ ewement $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wcqe {
	__we32 wqe;
#define FCOE_WCQE_TASK_ID (0xFFFF<<0)
#define FCOE_WCQE_TASK_ID_SHIFT 0
#define FCOE_WCQE_WCQE_TYPE (0xFF<<16)
#define FCOE_WCQE_WCQE_TYPE_SHIFT 16
#define FCOE_WCQE_WESEWVED (0xFF<<24)
#define FCOE_WCQE_WESEWVED_SHIFT 24
};



/*
 * FCoE pending wowk wequest CQE $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_pend_wq_cqe {
	__we16 wqe;
#define FCOE_PEND_WQ_CQE_TASK_ID (0x3FFF<<0)
#define FCOE_PEND_WQ_CQE_TASK_ID_SHIFT 0
#define FCOE_PEND_WQ_CQE_CQE_TYPE (0x1<<14)
#define FCOE_PEND_WQ_CQE_CQE_TYPE_SHIFT 14
#define FCOE_PEND_WQ_CQE_TOGGWE_BIT (0x1<<15)
#define FCOE_PEND_WQ_CQE_TOGGWE_BIT_SHIFT 15
};


/*
 * FCoE WX statistics pawametews section#0 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wx_stat_pawams_section0 {
	__we32 fcoe_wx_pkt_cnt;
	__we32 fcoe_wx_byte_cnt;
};


/*
 * FCoE WX statistics pawametews section#1 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wx_stat_pawams_section1 {
	__we32 fcoe_vew_cnt;
	__we32 fcoe_wx_dwop_pkt_cnt;
};


/*
 * FCoE WX statistics pawametews section#2 $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_wx_stat_pawams_section2 {
	__we32 fc_cwc_cnt;
	__we32 eofa_dew_cnt;
	__we32 miss_fwame_cnt;
	__we32 seq_timeout_cnt;
	__we32 dwop_seq_cnt;
	__we32 fcoe_wx_dwop_pkt_cnt;
	__we32 fcp_wx_pkt_cnt;
	__we32 wesewved0;
};


/*
 * FCoE TX statistics pawametews $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_tx_stat_pawams {
	__we32 fcoe_tx_pkt_cnt;
	__we32 fcoe_tx_byte_cnt;
	__we32 fcp_tx_pkt_cnt;
	__we32 wesewved0;
};

/*
 * FCoE statistics pawametews $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_statistics_pawams {
	stwuct fcoe_tx_stat_pawams tx_stat;
	stwuct fcoe_wx_stat_pawams_section0 wx_stat0;
	stwuct fcoe_wx_stat_pawams_section1 wx_stat1;
	stwuct fcoe_wx_stat_pawams_section2 wx_stat2;
};


/*
 * FCoE t2 hash tabwe entwy (64 bytes) $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_t2_hash_tabwe_entwy {
	stwuct fcoe_hash_tabwe_entwy data;
	stwuct wegpaiw next;
	stwuct wegpaiw wesewved0[3];
};



/*
 * FCoE unsowicited CQE $$KEEP_ENDIANNESS$$
 */
stwuct fcoe_unsowicited_cqe {
	__we16 wqe;
#define FCOE_UNSOWICITED_CQE_SUBTYPE (0x3<<0)
#define FCOE_UNSOWICITED_CQE_SUBTYPE_SHIFT 0
#define FCOE_UNSOWICITED_CQE_PKT_WEN (0xFFF<<2)
#define FCOE_UNSOWICITED_CQE_PKT_WEN_SHIFT 2
#define FCOE_UNSOWICITED_CQE_CQE_TYPE (0x1<<14)
#define FCOE_UNSOWICITED_CQE_CQE_TYPE_SHIFT 14
#define FCOE_UNSOWICITED_CQE_TOGGWE_BIT (0x1<<15)
#define FCOE_UNSOWICITED_CQE_TOGGWE_BIT_SHIFT 15
};

#endif /* __57XX_FCOE_HSI_WINUX_WE__ */
