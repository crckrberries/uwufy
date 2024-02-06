/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_HAW_WX_H
#define ATH11K_HAW_WX_H

stwuct haw_wx_wbm_wew_info {
	u32 cookie;
	enum haw_wbm_wew_swc_moduwe eww_wew_swc;
	enum haw_weo_dest_wing_push_weason push_weason;
	u32 eww_code;
	boow fiwst_msdu;
	boow wast_msdu;
};

#define HAW_INVAWID_PEEWID 0xffff
#define VHT_SIG_SU_NSS_MASK 0x7

#define HAW_WX_MAX_MCS 12
#define HAW_WX_MAX_NSS 8

stwuct haw_wx_mon_status_twv_hdw {
	u32 hdw;
	u8 vawue[];
};

enum haw_wx_su_mu_coding {
	HAW_WX_SU_MU_CODING_BCC,
	HAW_WX_SU_MU_CODING_WDPC,
	HAW_WX_SU_MU_CODING_MAX,
};

enum haw_wx_gi {
	HAW_WX_GI_0_8_US,
	HAW_WX_GI_0_4_US,
	HAW_WX_GI_1_6_US,
	HAW_WX_GI_3_2_US,
	HAW_WX_GI_MAX,
};

enum haw_wx_bw {
	HAW_WX_BW_20MHZ,
	HAW_WX_BW_40MHZ,
	HAW_WX_BW_80MHZ,
	HAW_WX_BW_160MHZ,
	HAW_WX_BW_MAX,
};

enum haw_wx_pweambwe {
	HAW_WX_PWEAMBWE_11A,
	HAW_WX_PWEAMBWE_11B,
	HAW_WX_PWEAMBWE_11N,
	HAW_WX_PWEAMBWE_11AC,
	HAW_WX_PWEAMBWE_11AX,
	HAW_WX_PWEAMBWE_MAX,
};

enum haw_wx_weception_type {
	HAW_WX_WECEPTION_TYPE_SU,
	HAW_WX_WECEPTION_TYPE_MU_MIMO,
	HAW_WX_WECEPTION_TYPE_MU_OFDMA,
	HAW_WX_WECEPTION_TYPE_MU_OFDMA_MIMO,
	HAW_WX_WECEPTION_TYPE_MAX,
};

#define HAW_WX_FCS_WEN                          4

enum haw_wx_mon_status {
	HAW_WX_MON_STATUS_PPDU_NOT_DONE,
	HAW_WX_MON_STATUS_PPDU_DONE,
	HAW_WX_MON_STATUS_BUF_DONE,
};

stwuct haw_wx_usew_status {
	u32 mcs:4,
	nss:3,
	ofdma_info_vawid:1,
	dw_ofdma_wu_stawt_index:7,
	dw_ofdma_wu_width:7,
	dw_ofdma_wu_size:8;
	u32 uw_ofdma_usew_v0_wowd0;
	u32 uw_ofdma_usew_v0_wowd1;
	u32 ast_index;
	u32 tid;
	u16 tcp_msdu_count;
	u16 udp_msdu_count;
	u16 othew_msdu_count;
	u16 fwame_contwow;
	u8 fwame_contwow_info_vawid;
	u8 data_sequence_contwow_info_vawid;
	u16 fiwst_data_seq_ctww;
	u32 pweambwe_type;
	u16 ht_fwags;
	u16 vht_fwags;
	u16 he_fwags;
	u8 ws_fwags;
	u32 mpdu_cnt_fcs_ok;
	u32 mpdu_cnt_fcs_eww;
	u32 mpdu_fcs_ok_bitmap[8];
	u32 mpdu_ok_byte_count;
	u32 mpdu_eww_byte_count;
};

#define HAW_TWV_STATUS_PPDU_NOT_DONE    HAW_WX_MON_STATUS_PPDU_NOT_DONE
#define HAW_TWV_STATUS_PPDU_DONE        HAW_WX_MON_STATUS_PPDU_DONE
#define HAW_TWV_STATUS_BUF_DONE         HAW_WX_MON_STATUS_BUF_DONE

stwuct haw_sw_mon_wing_entwies {
	dma_addw_t mon_dst_paddw;
	dma_addw_t mon_status_paddw;
	u32 mon_dst_sw_cookie;
	u32 mon_status_sw_cookie;
	void *dst_buf_addw_info;
	void *status_buf_addw_info;
	u16 ppdu_id;
	u8 status_buf_count;
	u8 msdu_cnt;
	boow end_of_ppdu;
	boow dwop_ppdu;
};

stwuct haw_wx_mon_ppdu_info {
	u32 ppdu_id;
	u32 ppdu_ts;
	u32 num_mpdu_fcs_ok;
	u32 num_mpdu_fcs_eww;
	u32 pweambwe_type;
	u16 chan_num;
	u16 tcp_msdu_count;
	u16 tcp_ack_msdu_count;
	u16 udp_msdu_count;
	u16 othew_msdu_count;
	u16 peew_id;
	u8 wate;
	u8 mcs;
	u8 nss;
	u8 bw;
	u8 vht_fwag_vawues1;
	u8 vht_fwag_vawues2;
	u8 vht_fwag_vawues3[4];
	u8 vht_fwag_vawues4;
	u8 vht_fwag_vawues5;
	u16 vht_fwag_vawues6;
	u8 is_stbc;
	u8 gi;
	u8 wdpc;
	u8 beamfowmed;
	u8 wssi_comb;
	u8 wssi_chain_pwi20[HAW_WX_MAX_NSS];
	u16 tid;
	u16 ht_fwags;
	u16 vht_fwags;
	u16 he_fwags;
	u16 he_mu_fwags;
	u8 dcm;
	u8 wu_awwoc;
	u8 weception_type;
	u64 tsft;
	u64 wx_duwation;
	u16 fwame_contwow;
	u32 ast_index;
	u8 ws_fcs_eww;
	u8 ws_fwags;
	u8 cck_fwag;
	u8 ofdm_fwag;
	u8 uwofdma_fwag;
	u8 fwame_contwow_info_vawid;
	u16 he_pew_usew_1;
	u16 he_pew_usew_2;
	u8 he_pew_usew_position;
	u8 he_pew_usew_known;
	u16 he_fwags1;
	u16 he_fwags2;
	u8 he_WU[4];
	u16 he_data1;
	u16 he_data2;
	u16 he_data3;
	u16 he_data4;
	u16 he_data5;
	u16 he_data6;
	u32 ppdu_wen;
	u32 pwev_ppdu_id;
	u32 device_id;
	u16 fiwst_data_seq_ctww;
	u8 monitow_diwect_used;
	u8 data_sequence_contwow_info_vawid;
	u8 wtf_size;
	u8 wxpcu_fiwtew_pass;
	chaw wssi_chain[8][8];
	stwuct haw_wx_usew_status usewstats;
};

#define HAW_WX_PPDU_STAWT_INFO0_PPDU_ID		GENMASK(15, 0)

stwuct haw_wx_ppdu_stawt {
	__we32 info0;
	__we32 chan_num;
	__we32 ppdu_stawt_ts;
} __packed;

#define HAW_WX_PPDU_END_USEW_STATS_INFO0_MPDU_CNT_FCS_EWW	GENMASK(25, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO1_MPDU_CNT_FCS_OK	GENMASK(8, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO1_FC_VAWID		BIT(9)
#define HAW_WX_PPDU_END_USEW_STATS_INFO1_QOS_CTWW_VAWID		BIT(10)
#define HAW_WX_PPDU_END_USEW_STATS_INFO1_HT_CTWW_VAWID		BIT(11)
#define HAW_WX_PPDU_END_USEW_STATS_INFO1_PKT_TYPE		GENMASK(23, 20)

#define HAW_WX_PPDU_END_USEW_STATS_INFO2_AST_INDEX		GENMASK(15, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO2_FWAME_CTWW		GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO3_QOS_CTWW		GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO4_UDP_MSDU_CNT		GENMASK(15, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO4_TCP_MSDU_CNT		GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO5_OTHEW_MSDU_CNT		GENMASK(15, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO5_TCP_ACK_MSDU_CNT	GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO7_TID_BITMAP		GENMASK(15, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO7_TID_EOSP_BITMAP	GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_INFO8_MPDU_OK_BYTE_COUNT	GENMASK(24, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO9_MPDU_EWW_BYTE_COUNT	GENMASK(24, 0)

stwuct haw_wx_ppdu_end_usew_stats {
	__we32 wsvd0[2];
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 info3;
	__we32 ht_ctww;
	__we32 wsvd1[2];
	__we32 info4;
	__we32 info5;
	__we32 info6;
	__we32 info7;
	__we32 wsvd2[4];
	__we32 info8;
	__we32 wsvd3;
	__we32 info9;
	__we32 wsvd4[2];
	__we32 info10;
} __packed;

stwuct haw_wx_ppdu_end_usew_stats_ext {
	u32 info0;
	u32 info1;
	u32 info2;
	u32 info3;
	u32 info4;
	u32 info5;
	u32 info6;
} __packed;

#define HAW_WX_HT_SIG_INFO_INFO0_MCS		GENMASK(6, 0)
#define HAW_WX_HT_SIG_INFO_INFO0_BW		BIT(7)

#define HAW_WX_HT_SIG_INFO_INFO1_STBC		GENMASK(5, 4)
#define HAW_WX_HT_SIG_INFO_INFO1_FEC_CODING	BIT(6)
#define HAW_WX_HT_SIG_INFO_INFO1_GI		BIT(7)

stwuct haw_wx_ht_sig_info {
	__we32 info0;
	__we32 info1;
} __packed;

#define HAW_WX_WSIG_B_INFO_INFO0_WATE	GENMASK(3, 0)
#define HAW_WX_WSIG_B_INFO_INFO0_WEN	GENMASK(15, 4)

stwuct haw_wx_wsig_b_info {
	__we32 info0;
} __packed;

#define HAW_WX_WSIG_A_INFO_INFO0_WATE		GENMASK(3, 0)
#define HAW_WX_WSIG_A_INFO_INFO0_WEN		GENMASK(16, 5)
#define HAW_WX_WSIG_A_INFO_INFO0_PKT_TYPE	GENMASK(27, 24)

stwuct haw_wx_wsig_a_info {
	__we32 info0;
} __packed;

#define HAW_WX_VHT_SIG_A_INFO_INFO0_BW		GENMASK(1, 0)
#define HAW_WX_VHT_SIG_A_INFO_INFO0_STBC	BIT(3)
#define HAW_WX_VHT_SIG_A_INFO_INFO0_GWOUP_ID	GENMASK(9, 4)
#define HAW_WX_VHT_SIG_A_INFO_INFO0_NSTS	GENMASK(21, 10)

#define HAW_WX_VHT_SIG_A_INFO_INFO1_GI_SETTING		GENMASK(1, 0)
#define HAW_WX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING	BIT(2)
#define HAW_WX_VHT_SIG_A_INFO_INFO1_MCS			GENMASK(7, 4)
#define HAW_WX_VHT_SIG_A_INFO_INFO1_BEAMFOWMED		BIT(8)

stwuct haw_wx_vht_sig_a_info {
	__we32 info0;
	__we32 info1;
} __packed;

enum haw_wx_vht_sig_a_gi_setting {
	HAW_WX_VHT_SIG_A_NOWMAW_GI = 0,
	HAW_WX_VHT_SIG_A_SHOWT_GI = 1,
	HAW_WX_VHT_SIG_A_SHOWT_GI_AMBIGUITY = 3,
};

#define HAW_WX_SU_MU_CODING_WDPC 0x01

#define HE_GI_0_8 0
#define HE_GI_0_4 1
#define HE_GI_1_6 2
#define HE_GI_3_2 3

#define HE_WTF_1_X 0
#define HE_WTF_2_X 1
#define HE_WTF_4_X 2
#define HE_WTF_UNKNOWN 3

#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_MCS	GENMASK(6, 3)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_DCM		BIT(7)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_BW	GENMASK(20, 19)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_CP_WTF_SIZE	GENMASK(22, 21)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS		GENMASK(25, 23)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_BSS_COWOW		GENMASK(13, 8)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_SPATIAW_WEUSE	GENMASK(18, 15)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_FOWMAT_IND	BIT(0)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_BEAM_CHANGE	BIT(1)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO0_DW_UW_FWAG	BIT(2)

#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXOP_DUWATION	GENMASK(6, 0)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_CODING		BIT(7)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_WDPC_EXTWA	BIT(8)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_STBC		BIT(9)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXBF		BIT(10)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_FACTOW	GENMASK(12, 11)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_PE_DISAM	BIT(13)
#define HAW_WX_HE_SIG_A_SU_INFO_INFO1_DOPPWEW_IND	BIT(15)

stwuct haw_wx_he_sig_a_su_info {
	__we32 info0;
	__we32 info1;
} __packed;

#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_UW_FWAG		BIT(1)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_MCS_OF_SIGB		GENMASK(3, 1)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_DCM_OF_SIGB		BIT(4)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_BSS_COWOW		GENMASK(10, 5)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_SPATIAW_WEUSE	GENMASK(14, 11)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_TWANSMIT_BW		GENMASK(17, 15)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_NUM_SIGB_SYMB	GENMASK(21, 18)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_COMP_MODE_SIGB	BIT(22)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_CP_WTF_SIZE		GENMASK(24, 23)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_DOPPWEW_INDICATION	BIT(25)

#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_TXOP_DUWATION	GENMASK(6, 0)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_CODING		BIT(7)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_NUM_WTF_SYMB	GENMASK(10, 8)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_WDPC_EXTWA		BIT(11)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_STBC		BIT(12)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_TXBF		BIT(10)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_PKT_EXT_FACTOW	GENMASK(14, 13)
#define HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_PKT_EXT_PE_DISAM	BIT(15)

stwuct haw_wx_he_sig_a_mu_dw_info {
	__we32 info0;
	__we32 info1;
} __packed;

#define HAW_WX_HE_SIG_B1_MU_INFO_INFO0_WU_AWWOCATION	GENMASK(7, 0)

stwuct haw_wx_he_sig_b1_mu_info {
	__we32 info0;
} __packed;

#define HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_ID		GENMASK(10, 0)
#define HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_MCS		GENMASK(18, 15)
#define HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_CODING	BIT(20)
#define HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_NSTS		GENMASK(31, 29)

stwuct haw_wx_he_sig_b2_mu_info {
	__we32 info0;
} __packed;

#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_ID	GENMASK(10, 0)
#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_NSTS	GENMASK(13, 11)
#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_TXBF	BIT(19)
#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_MCS	GENMASK(18, 15)
#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_DCM	BIT(19)
#define HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_CODING	BIT(20)

stwuct haw_wx_he_sig_b2_ofdma_info {
	__we32 info0;
} __packed;

#define HAW_WX_PHYWX_WSSI_WEGACY_INFO_INFO0_WSSI_COMB	GENMASK(15, 8)

#define HAW_WX_PHYWX_WSSI_PWEAMBWE_PWI20	GENMASK(7, 0)

stwuct haw_wx_phywx_chain_wssi {
	__we32 wssi_2040;
	__we32 wssi_80;
} __packed;

stwuct haw_wx_phywx_wssi_wegacy_info {
	__we32 wsvd[3];
	stwuct haw_wx_phywx_chain_wssi pwe_wssi[HAW_WX_MAX_NSS];
	stwuct haw_wx_phywx_chain_wssi pweambwe[HAW_WX_MAX_NSS];
	__we32 info0;
} __packed;

#define HAW_WX_MPDU_INFO_INFO0_PEEWID	GENMASK(31, 16)
#define HAW_WX_MPDU_INFO_INFO0_PEEWID_WCN6855	GENMASK(15, 0)
#define HAW_WX_MPDU_INFO_INFO1_MPDU_WEN		GENMASK(13, 0)

stwuct haw_wx_mpdu_info_ipq8074 {
	__we32 wsvd0;
	__we32 info0;
	__we32 wsvd1[11];
	__we32 info1;
	__we32 wsvd2[9];
} __packed;

stwuct haw_wx_mpdu_info_qcn9074 {
	__we32 wsvd0[10];
	__we32 info0;
	__we32 wsvd1[2];
	__we32 info1;
	__we32 wsvd2[9];
} __packed;

stwuct haw_wx_mpdu_info_wcn6855 {
	__we32 wsvd0[8];
	__we32 info0;
	__we32 wsvd1[14];
} __packed;

stwuct haw_wx_mpdu_info {
	union {
		stwuct haw_wx_mpdu_info_ipq8074 ipq8074;
		stwuct haw_wx_mpdu_info_qcn9074 qcn9074;
		stwuct haw_wx_mpdu_info_wcn6855 wcn6855;
	} u;
} __packed;

#define HAW_WX_PPDU_END_DUWATION	GENMASK(23, 0)
stwuct haw_wx_ppdu_end_duwation {
	__we32 wsvd0[9];
	__we32 info0;
	__we32 wsvd1[4];
} __packed;

stwuct haw_wx_wxpcu_cwassification_ovewview {
	u32 wsvd0;
} __packed;

stwuct haw_wx_msdu_desc_info {
	u32 msdu_fwags;
	u16 msdu_wen; /* 14 bits fow wength */
};

#define HAW_WX_NUM_MSDU_DESC 6
stwuct haw_wx_msdu_wist {
	stwuct haw_wx_msdu_desc_info msdu_info[HAW_WX_NUM_MSDU_DESC];
	u32 sw_cookie[HAW_WX_NUM_MSDU_DESC];
	u8 wbm[HAW_WX_NUM_MSDU_DESC];
};

void ath11k_haw_weo_status_queue_stats(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status);
void ath11k_haw_weo_fwush_queue_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status);
void ath11k_haw_weo_fwush_cache_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status);
void ath11k_haw_weo_fwush_cache_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status);
void ath11k_haw_weo_unbwk_cache_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status);
void ath11k_haw_weo_fwush_timeout_wist_status(stwuct ath11k_base *ab,
					      u32 *weo_desc,
					      stwuct haw_weo_status *status);
void ath11k_haw_weo_desc_thwesh_weached_status(stwuct ath11k_base *ab,
					       u32 *weo_desc,
					       stwuct haw_weo_status *status);
void ath11k_haw_weo_update_wx_weo_queue_status(stwuct ath11k_base *ab,
					       u32 *weo_desc,
					       stwuct haw_weo_status *status);
int ath11k_haw_weo_pwocess_status(u8 *weo_desc, u8 *status);
void ath11k_haw_wx_msdu_wink_info_get(void *wink_desc, u32 *num_msdus,
				      u32 *msdu_cookies,
				      enum haw_wx_buf_wetuwn_buf_managew *wbm);
void ath11k_haw_wx_msdu_wink_desc_set(stwuct ath11k_base *ab, void *desc,
				      void *wink_desc,
				      enum haw_wbm_wew_bm_act action);
void ath11k_haw_wx_buf_addw_info_set(void *desc, dma_addw_t paddw,
				     u32 cookie, u8 managew);
void ath11k_haw_wx_buf_addw_info_get(void *desc, dma_addw_t *paddw,
				     u32 *cookie, u8 *wbm);
int ath11k_haw_desc_weo_pawse_eww(stwuct ath11k_base *ab, u32 *wx_desc,
				  dma_addw_t *paddw, u32 *desc_bank);
int ath11k_haw_wbm_desc_pawse_eww(stwuct ath11k_base *ab, void *desc,
				  stwuct haw_wx_wbm_wew_info *wew_info);
void ath11k_haw_wx_weo_ent_paddw_get(stwuct ath11k_base *ab, void *desc,
				     dma_addw_t *paddw, u32 *desc_bank);
void ath11k_haw_wx_weo_ent_buf_paddw_get(void *wx_desc,
					 dma_addw_t *paddw, u32 *sw_cookie,
					 void **pp_buf_addw_info, u8 *wbm,
					 u32 *msdu_cnt);
void
ath11k_haw_wx_sw_mon_wing_buf_paddw_get(void *wx_desc,
					stwuct haw_sw_mon_wing_entwies *sw_mon_ent);
enum haw_wx_mon_status
ath11k_haw_wx_pawse_mon_status(stwuct ath11k_base *ab,
			       stwuct haw_wx_mon_ppdu_info *ppdu_info,
			       stwuct sk_buff *skb);

#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_0 0xDDBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_1 0xADBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_2 0xBDBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_3 0xCDBEEF
#endif
