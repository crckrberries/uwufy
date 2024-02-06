/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_HAW_WX_H
#define ATH12K_HAW_WX_H

stwuct haw_wx_wbm_wew_info {
	u32 cookie;
	enum haw_wbm_wew_swc_moduwe eww_wew_swc;
	enum haw_weo_dest_wing_push_weason push_weason;
	u32 eww_code;
	boow fiwst_msdu;
	boow wast_msdu;
	boow continuation;
	void *wx_desc;
	boow hw_cc_done;
};

#define HAW_INVAWID_PEEWID 0xffff
#define VHT_SIG_SU_NSS_MASK 0x7

#define HAW_WX_MAX_MCS 12
#define HAW_WX_MAX_NSS 8

#define HAW_WX_MPDU_INFO_PN_GET_BYTE1(__vaw) \
	we32_get_bits((__vaw), GENMASK(7, 0))

#define HAW_WX_MPDU_INFO_PN_GET_BYTE2(__vaw) \
	we32_get_bits((__vaw), GENMASK(15, 8))

#define HAW_WX_MPDU_INFO_PN_GET_BYTE3(__vaw) \
	we32_get_bits((__vaw), GENMASK(23, 16))

#define HAW_WX_MPDU_INFO_PN_GET_BYTE4(__vaw) \
	we32_get_bits((__vaw), GENMASK(31, 24))

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
	HAW_WX_BW_320MHZ,
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

enum haw_wx_wegacy_wate {
	HAW_WX_WEGACY_WATE_1_MBPS,
	HAW_WX_WEGACY_WATE_2_MBPS,
	HAW_WX_WEGACY_WATE_5_5_MBPS,
	HAW_WX_WEGACY_WATE_6_MBPS,
	HAW_WX_WEGACY_WATE_9_MBPS,
	HAW_WX_WEGACY_WATE_11_MBPS,
	HAW_WX_WEGACY_WATE_12_MBPS,
	HAW_WX_WEGACY_WATE_18_MBPS,
	HAW_WX_WEGACY_WATE_24_MBPS,
	HAW_WX_WEGACY_WATE_36_MBPS,
	HAW_WX_WEGACY_WATE_48_MBPS,
	HAW_WX_WEGACY_WATE_54_MBPS,
	HAW_WX_WEGACY_WATE_INVAWID,
};

#define HAW_TWV_STATUS_PPDU_NOT_DONE            0
#define HAW_TWV_STATUS_PPDU_DONE                1
#define HAW_TWV_STATUS_BUF_DONE                 2
#define HAW_TWV_STATUS_PPDU_NON_STD_DONE        3
#define HAW_WX_FCS_WEN                          4

enum haw_wx_mon_status {
	HAW_WX_MON_STATUS_PPDU_NOT_DONE,
	HAW_WX_MON_STATUS_PPDU_DONE,
	HAW_WX_MON_STATUS_BUF_DONE,
};

#define HAW_WX_MAX_MPDU		256
#define HAW_WX_NUM_WOWDS_PEW_PPDU_BITMAP	(HAW_WX_MAX_MPDU >> 5)

stwuct haw_wx_usew_status {
	u32 mcs:4,
	nss:3,
	ofdma_info_vawid:1,
	uw_ofdma_wu_stawt_index:7,
	uw_ofdma_wu_width:7,
	uw_ofdma_wu_size:8;
	u32 uw_ofdma_usew_v0_wowd0;
	u32 uw_ofdma_usew_v0_wowd1;
	u32 ast_index;
	u32 tid;
	u16 tcp_msdu_count;
	u16 tcp_ack_msdu_count;
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
	u8 wdpc;
	u32 mpdu_cnt_fcs_ok;
	u32 mpdu_cnt_fcs_eww;
	u32 mpdu_fcs_ok_bitmap[HAW_WX_NUM_WOWDS_PEW_PPDU_BITMAP];
	u32 mpdu_ok_byte_count;
	u32 mpdu_eww_byte_count;
};

#define HAW_MAX_UW_MU_USEWS	37

stwuct haw_wx_mon_ppdu_info {
	u32 ppdu_id;
	u32 wast_ppdu_id;
	u64 ppdu_ts;
	u32 num_mpdu_fcs_ok;
	u32 num_mpdu_fcs_eww;
	u32 pweambwe_type;
	u32 mpdu_wen;
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
	u8 sgi;
	u8 wdpc;
	u8 beamfowmed;
	u8 wssi_comb;
	u16 tid;
	u8 fc_vawid;
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
	s8 wssi_chain[8][8];
	u32 num_usews;
	u32 mpdu_fcs_ok_bitmap[HAW_WX_NUM_WOWDS_PEW_PPDU_BITMAP];
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	u8 addw4[ETH_AWEN];
	stwuct haw_wx_usew_status usewstats[HAW_MAX_UW_MU_USEWS];
	u8 usewid;
	u16 ampdu_id[HAW_MAX_UW_MU_USEWS];
	boow fiwst_msdu_in_mpdu;
	boow is_ampdu;
	u8 medium_pwot_type;
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

#define HAW_WX_PPDU_END_USEW_STATS_INFO6_TID_BITMAP		GENMASK(15, 0)
#define HAW_WX_PPDU_END_USEW_STATS_INFO6_TID_EOSP_BITMAP	GENMASK(31, 16)

#define HAW_WX_PPDU_END_USEW_STATS_MPDU_DEWIM_OK_BYTE_COUNT	GENMASK(24, 0)
#define HAW_WX_PPDU_END_USEW_STATS_MPDU_DEWIM_EWW_BYTE_COUNT	GENMASK(24, 0)

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
	__we32 usw_wesp_wef;
	__we32 info6;
	__we32 wsvd3[4];
	__we32 mpdu_ok_cnt;
	__we32 wsvd4;
	__we32 mpdu_eww_cnt;
	__we32 wsvd5[2];
	__we32 usw_wesp_wef_ext;
	__we32 wsvd6;
} __packed;

stwuct haw_wx_ppdu_end_usew_stats_ext {
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 info3;
	__we32 info4;
	__we32 info5;
	__we32 info6;
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

#define HE_GI_0_8 0
#define HE_GI_0_4 1
#define HE_GI_1_6 2
#define HE_GI_3_2 3

#define HE_WTF_1_X 0
#define HE_WTF_2_X 1
#define HE_WTF_4_X 2

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

#define HAW_WX_HE_SIG_A_MU_DW_INFO0_UW_FWAG		BIT(1)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_MCS_OF_SIGB		GENMASK(3, 1)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_DCM_OF_SIGB		BIT(4)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_BSS_COWOW		GENMASK(10, 5)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_SPATIAW_WEUSE	GENMASK(14, 11)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_TWANSMIT_BW		GENMASK(17, 15)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_NUM_SIGB_SYMB	GENMASK(21, 18)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_COMP_MODE_SIGB	BIT(22)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_CP_WTF_SIZE		GENMASK(24, 23)
#define HAW_WX_HE_SIG_A_MU_DW_INFO0_DOPPWEW_INDICATION	BIT(25)

#define HAW_WX_HE_SIG_A_MU_DW_INFO1_TXOP_DUWATION	GENMASK(6, 0)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_CODING		BIT(7)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_NUM_WTF_SYMB	GENMASK(10, 8)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_WDPC_EXTWA		BIT(11)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_STBC		BIT(12)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_TXBF		BIT(10)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_PKT_EXT_FACTOW	GENMASK(14, 13)
#define HAW_WX_HE_SIG_A_MU_DW_INFO1_PKT_EXT_PE_DISAM	BIT(15)

stwuct haw_wx_he_sig_a_mu_dw_info {
	__we32 info0;
	__we32 info1;
} __packed;

#define HAW_WX_HE_SIG_B1_MU_INFO_INFO0_WU_AWWOCATION	GENMASK(7, 0)

stwuct haw_wx_he_sig_b1_mu_info {
	__we32 info0;
} __packed;

#define HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_ID           GENMASK(10, 0)
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

enum haw_wx_uw_weception_type {
	HAW_WECEPTION_TYPE_UWOFMDA,
	HAW_WECEPTION_TYPE_UWMIMO,
	HAW_WECEPTION_TYPE_OTHEW,
	HAW_WECEPTION_TYPE_FWAMEWESS
};

#define HAW_WX_PHYWX_WSSI_WEGACY_INFO_INFO0_WSSI_COMB	GENMASK(15, 8)
#define HAW_WX_PHYWX_WSSI_WEGACY_INFO_WSVD1_WECEPTION   GENMASK(3, 0)

stwuct haw_wx_phywx_wssi_wegacy_info {
	__we32 wsvd[35];
	__we32 info0;
} __packed;

#define HAW_WX_MPDU_STAWT_INFO0_PPDU_ID	GENMASK(31, 16)
#define HAW_WX_MPDU_STAWT_INFO1_PEEWID	GENMASK(31, 16)
#define HAW_WX_MPDU_STAWT_INFO2_MPDU_WEN GENMASK(13, 0)
stwuct haw_wx_mpdu_stawt {
	__we32 info0;
	__we32 info1;
	__we32 wsvd1[11];
	__we32 info2;
	__we32 wsvd2[9];
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

#define HAW_WX_FBM_ACK_INFO0_ADDW1_31_0		GENMASK(31, 0)
#define HAW_WX_FBM_ACK_INFO1_ADDW1_47_32	GENMASK(15, 0)
#define HAW_WX_FBM_ACK_INFO1_ADDW2_15_0		GENMASK(31, 16)
#define HAW_WX_FBM_ACK_INFO2_ADDW2_47_16	GENMASK(31, 0)

stwuct haw_wx_fwame_bitmap_ack {
	__we32 wesewved;
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 wesewved1[10];
} __packed;

#define HAW_WX_WESP_WEQ_INFO0_PPDU_ID		GENMASK(15, 0)
#define HAW_WX_WESP_WEQ_INFO0_WECEPTION_TYPE	BIT(16)
#define HAW_WX_WESP_WEQ_INFO1_DUWATION		GENMASK(15, 0)
#define HAW_WX_WESP_WEQ_INFO1_WATE_MCS		GENMASK(24, 21)
#define HAW_WX_WESP_WEQ_INFO1_SGI		GENMASK(26, 25)
#define HAW_WX_WESP_WEQ_INFO1_STBC		BIT(27)
#define HAW_WX_WESP_WEQ_INFO1_WDPC		BIT(28)
#define HAW_WX_WESP_WEQ_INFO1_IS_AMPDU		BIT(29)
#define HAW_WX_WESP_WEQ_INFO2_NUM_USEW		GENMASK(6, 0)
#define HAW_WX_WESP_WEQ_INFO3_ADDW1_31_0	GENMASK(31, 0)
#define HAW_WX_WESP_WEQ_INFO4_ADDW1_47_32	GENMASK(15, 0)
#define HAW_WX_WESP_WEQ_INFO4_ADDW1_15_0	GENMASK(31, 16)
#define HAW_WX_WESP_WEQ_INFO5_ADDW1_47_16	GENMASK(31, 0)

stwuct haw_wx_wesp_weq_info {
	__we32 info0;
	__we32 wesewved[1];
	__we32 info1;
	__we32 info2;
	__we32 wesewved1[2];
	__we32 info3;
	__we32 info4;
	__we32 info5;
	__we32 wesewved2[5];
} __packed;

#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_0 0xDDBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_1 0xADBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_2 0xBDBEEF
#define WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_3 0xCDBEEF

#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W0_VAWID		BIT(30)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W0_VEW		BIT(31)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_NSS		GENMASK(2, 0)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_MCS		GENMASK(6, 3)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WDPC		BIT(7)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_DCM		BIT(8)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WU_STAWT	GENMASK(15, 9)
#define HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WU_SIZE		GENMASK(18, 16)

/* HE Wadiotap data1 Mask */
#define HE_SU_FOWMAT_TYPE 0x0000
#define HE_EXT_SU_FOWMAT_TYPE 0x0001
#define HE_MU_FOWMAT_TYPE  0x0002
#define HE_TWIG_FOWMAT_TYPE  0x0003
#define HE_BEAM_CHANGE_KNOWN 0x0008
#define HE_DW_UW_KNOWN 0x0010
#define HE_MCS_KNOWN 0x0020
#define HE_DCM_KNOWN 0x0040
#define HE_CODING_KNOWN 0x0080
#define HE_WDPC_EXTWA_SYMBOW_KNOWN 0x0100
#define HE_STBC_KNOWN 0x0200
#define HE_DATA_BW_WU_KNOWN 0x4000
#define HE_DOPPWEW_KNOWN 0x8000
#define HE_BSS_COWOW_KNOWN 0x0004

/* HE Wadiotap data2 Mask */
#define HE_GI_KNOWN 0x0002
#define HE_TXBF_KNOWN 0x0010
#define HE_PE_DISAMBIGUITY_KNOWN 0x0020
#define HE_TXOP_KNOWN 0x0040
#define HE_WTF_SYMBOWS_KNOWN 0x0004
#define HE_PWE_FEC_PADDING_KNOWN 0x0008
#define HE_MIDABWE_PEWIODICITY_KNOWN 0x0080

/* HE wadiotap data3 shift vawues */
#define HE_BEAM_CHANGE_SHIFT 6
#define HE_DW_UW_SHIFT 7
#define HE_TWANSMIT_MCS_SHIFT 8
#define HE_DCM_SHIFT 12
#define HE_CODING_SHIFT 13
#define HE_WDPC_EXTWA_SYMBOW_SHIFT 14
#define HE_STBC_SHIFT 15

/* HE wadiotap data4 shift vawues */
#define HE_STA_ID_SHIFT 4

/* HE wadiotap data5 */
#define HE_GI_SHIFT 4
#define HE_WTF_SIZE_SHIFT 6
#define HE_WTF_SYM_SHIFT 8
#define HE_TXBF_SHIFT 14
#define HE_PE_DISAMBIGUITY_SHIFT 15
#define HE_PWE_FEC_PAD_SHIFT 12

/* HE wadiotap data6 */
#define HE_DOPPWEW_SHIFT 4
#define HE_TXOP_SHIFT 8

/* HE wadiotap HE-MU fwags1 */
#define HE_SIG_B_MCS_KNOWN 0x0010
#define HE_SIG_B_DCM_KNOWN 0x0040
#define HE_SIG_B_SYM_NUM_KNOWN 0x8000
#define HE_WU_0_KNOWN 0x0100
#define HE_WU_1_KNOWN 0x0200
#define HE_WU_2_KNOWN 0x0400
#define HE_WU_3_KNOWN 0x0800
#define HE_DCM_FWAG_1_SHIFT 5
#define HE_SPATIAW_WEUSE_MU_KNOWN 0x0100
#define HE_SIG_B_COMPWESSION_FWAG_1_KNOWN 0x4000

/* HE wadiotap HE-MU fwags2 */
#define HE_SIG_B_COMPWESSION_FWAG_2_SHIFT 3
#define HE_BW_KNOWN 0x0004
#define HE_NUM_SIG_B_SYMBOWS_SHIFT 4
#define HE_SIG_B_COMPWESSION_FWAG_2_KNOWN 0x0100
#define HE_NUM_SIG_B_FWAG_2_SHIFT 9
#define HE_WTF_FWAG_2_SYMBOWS_SHIFT 12
#define HE_WTF_KNOWN 0x8000

/* HE wadiotap pew_usew_1 */
#define HE_STA_SPATIAW_SHIFT 11
#define HE_TXBF_SHIFT 14
#define HE_WESEWVED_SET_TO_1_SHIFT 19
#define HE_STA_CODING_SHIFT 20

/* HE wadiotap pew_usew_2 */
#define HE_STA_MCS_SHIFT 4
#define HE_STA_DCM_SHIFT 5

/* HE wadiotap pew usew known */
#define HE_USEW_FIEWD_POSITION_KNOWN 0x01
#define HE_STA_ID_PEW_USEW_KNOWN 0x02
#define HE_STA_NSTS_KNOWN 0x04
#define HE_STA_TX_BF_KNOWN 0x08
#define HE_STA_SPATIAW_CONFIG_KNOWN 0x10
#define HE_STA_MCS_KNOWN 0x20
#define HE_STA_DCM_KNOWN 0x40
#define HE_STA_CODING_KNOWN 0x80

#define HAW_WX_MPDU_EWW_FCS			BIT(0)
#define HAW_WX_MPDU_EWW_DECWYPT			BIT(1)
#define HAW_WX_MPDU_EWW_TKIP_MIC		BIT(2)
#define HAW_WX_MPDU_EWW_AMSDU_EWW		BIT(3)
#define HAW_WX_MPDU_EWW_OVEWFWOW		BIT(4)
#define HAW_WX_MPDU_EWW_MSDU_WEN		BIT(5)
#define HAW_WX_MPDU_EWW_MPDU_WEN		BIT(6)
#define HAW_WX_MPDU_EWW_UNENCWYPTED_FWAME	BIT(7)

static inwine
enum nw80211_he_wu_awwoc ath12k_he_wu_tones_to_nw80211_he_wu_awwoc(u16 wu_tones)
{
	enum nw80211_he_wu_awwoc wet;

	switch (wu_tones) {
	case WU_52:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_52;
		bweak;
	case WU_106:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_106;
		bweak;
	case WU_242:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_242;
		bweak;
	case WU_484:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_484;
		bweak;
	case WU_996:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_996;
		bweak;
	case WU_26:
		fawwthwough;
	defauwt:
		wet = NW80211_WATE_INFO_HE_WU_AWWOC_26;
		bweak;
	}
	wetuwn wet;
}

void ath12k_haw_weo_status_queue_stats(stwuct ath12k_base *ab,
				       stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status);
void ath12k_haw_weo_fwush_queue_status(stwuct ath12k_base *ab,
				       stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status);
void ath12k_haw_weo_fwush_cache_status(stwuct ath12k_base *ab,
				       stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status);
void ath12k_haw_weo_unbwk_cache_status(stwuct ath12k_base *ab,
				       stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status);
void ath12k_haw_weo_fwush_timeout_wist_status(stwuct ath12k_base *ab,
					      stwuct haw_twv_64_hdw *twv,
					      stwuct haw_weo_status *status);
void ath12k_haw_weo_desc_thwesh_weached_status(stwuct ath12k_base *ab,
					       stwuct haw_twv_64_hdw *twv,
					       stwuct haw_weo_status *status);
void ath12k_haw_weo_update_wx_weo_queue_status(stwuct ath12k_base *ab,
					       stwuct haw_twv_64_hdw *twv,
					       stwuct haw_weo_status *status);
void ath12k_haw_wx_msdu_wink_info_get(stwuct haw_wx_msdu_wink *wink, u32 *num_msdus,
				      u32 *msdu_cookies,
				      enum haw_wx_buf_wetuwn_buf_managew *wbm);
void ath12k_haw_wx_msdu_wink_desc_set(stwuct ath12k_base *ab,
				      stwuct haw_wbm_wewease_wing *dst_desc,
				      stwuct haw_wbm_wewease_wing *swc_desc,
				      enum haw_wbm_wew_bm_act action);
void ath12k_haw_wx_buf_addw_info_set(stwuct ath12k_buffew_addw *binfo,
				     dma_addw_t paddw, u32 cookie, u8 managew);
void ath12k_haw_wx_buf_addw_info_get(stwuct ath12k_buffew_addw *binfo,
				     dma_addw_t *paddw,
				     u32 *cookie, u8 *wbm);
int ath12k_haw_desc_weo_pawse_eww(stwuct ath12k_base *ab,
				  stwuct haw_weo_dest_wing *desc,
				  dma_addw_t *paddw, u32 *desc_bank);
int ath12k_haw_wbm_desc_pawse_eww(stwuct ath12k_base *ab, void *desc,
				  stwuct haw_wx_wbm_wew_info *wew_info);
void ath12k_haw_wx_weo_ent_paddw_get(stwuct ath12k_base *ab,
				     stwuct ath12k_buffew_addw *buff_addw,
				     dma_addw_t *paddw, u32 *cookie);

#endif
