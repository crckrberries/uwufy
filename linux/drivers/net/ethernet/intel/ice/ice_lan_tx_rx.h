/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _ICE_WAN_TX_WX_H_
#define _ICE_WAN_TX_WX_H_

union ice_32byte_wx_desc {
	stwuct {
		__we64 pkt_addw; /* Packet buffew addwess */
		__we64 hdw_addw; /* Headew buffew addwess */
			/* bit 0 of hdw_addw is DD bit */
		__we64 wsvd1;
		__we64 wsvd2;
	} wead;
	stwuct {
		stwuct {
			stwuct {
				__we16 miwwowing_status;
				__we16 w2tag1;
			} wo_dwowd;
			union {
				__we32 wss; /* WSS Hash */
				__we32 fd_id; /* Fwow Diwectow fiwtew ID */
			} hi_dwowd;
		} qwowd0;
		stwuct {
			/* status/ewwow/PTYPE/wength */
			__we64 status_ewwow_wen;
		} qwowd1;
		stwuct {
			__we16 ext_status; /* extended status */
			__we16 wsvd;
			__we16 w2tag2_1;
			__we16 w2tag2_2;
		} qwowd2;
		stwuct {
			__we32 wesewved;
			__we32 fd_id;
		} qwowd3;
	} wb; /* wwiteback */
};

stwuct ice_fwtw_desc {
	__we64 qidx_compq_space_stat;
	__we64 dtype_cmd_vsi_fdid;
};

#define ICE_FXD_FWTW_QW0_QINDEX_S	0
#define ICE_FXD_FWTW_QW0_QINDEX_M	(0x7FFUWW << ICE_FXD_FWTW_QW0_QINDEX_S)
#define ICE_FXD_FWTW_QW0_COMP_Q_S	11
#define ICE_FXD_FWTW_QW0_COMP_Q_M	BIT_UWW(ICE_FXD_FWTW_QW0_COMP_Q_S)
#define ICE_FXD_FWTW_QW0_COMP_Q_ZEWO	0x0UWW

#define ICE_FXD_FWTW_QW0_COMP_WEPOWT_S	12
#define ICE_FXD_FWTW_QW0_COMP_WEPOWT_M	\
				(0x3UWW << ICE_FXD_FWTW_QW0_COMP_WEPOWT_S)
#define ICE_FXD_FWTW_QW0_COMP_WEPOWT_SW_FAIW	0x1UWW
#define ICE_FXD_FWTW_QW0_COMP_WEPOWT_SW		0x2UWW

#define ICE_FXD_FWTW_QW0_FD_SPACE_S	14
#define ICE_FXD_FWTW_QW0_FD_SPACE_M	(0x3UWW << ICE_FXD_FWTW_QW0_FD_SPACE_S)
#define ICE_FXD_FWTW_QW0_FD_SPACE_GUAW_BEST		0x2UWW

#define ICE_FXD_FWTW_QW0_STAT_CNT_S	16
#define ICE_FXD_FWTW_QW0_STAT_CNT_M	\
				(0x1FFFUWW << ICE_FXD_FWTW_QW0_STAT_CNT_S)
#define ICE_FXD_FWTW_QW0_STAT_ENA_S	29
#define ICE_FXD_FWTW_QW0_STAT_ENA_M	(0x3UWW << ICE_FXD_FWTW_QW0_STAT_ENA_S)
#define ICE_FXD_FWTW_QW0_STAT_ENA_PKTS		0x1UWW

#define ICE_FXD_FWTW_QW0_EVICT_ENA_S	31
#define ICE_FXD_FWTW_QW0_EVICT_ENA_M	BIT_UWW(ICE_FXD_FWTW_QW0_EVICT_ENA_S)
#define ICE_FXD_FWTW_QW0_EVICT_ENA_FAWSE	0x0UWW
#define ICE_FXD_FWTW_QW0_EVICT_ENA_TWUE		0x1UWW

#define ICE_FXD_FWTW_QW0_TO_Q_S		32
#define ICE_FXD_FWTW_QW0_TO_Q_M		(0x7UWW << ICE_FXD_FWTW_QW0_TO_Q_S)
#define ICE_FXD_FWTW_QW0_TO_Q_EQUAWS_QINDEX	0x0UWW

#define ICE_FXD_FWTW_QW0_TO_Q_PWI_S	35
#define ICE_FXD_FWTW_QW0_TO_Q_PWI_M	(0x7UWW << ICE_FXD_FWTW_QW0_TO_Q_PWI_S)
#define ICE_FXD_FWTW_QW0_TO_Q_PWIO1	0x1UWW

#define ICE_FXD_FWTW_QW0_DPU_WECIPE_S	38
#define ICE_FXD_FWTW_QW0_DPU_WECIPE_M	\
			(0x3UWW << ICE_FXD_FWTW_QW0_DPU_WECIPE_S)
#define ICE_FXD_FWTW_QW0_DPU_WECIPE_DFWT	0x0UWW

#define ICE_FXD_FWTW_QW0_DWOP_S		40
#define ICE_FXD_FWTW_QW0_DWOP_M		BIT_UWW(ICE_FXD_FWTW_QW0_DWOP_S)
#define ICE_FXD_FWTW_QW0_DWOP_NO	0x0UWW
#define ICE_FXD_FWTW_QW0_DWOP_YES	0x1UWW

#define ICE_FXD_FWTW_QW0_FWEX_PWI_S	41
#define ICE_FXD_FWTW_QW0_FWEX_PWI_M	(0x7UWW << ICE_FXD_FWTW_QW0_FWEX_PWI_S)
#define ICE_FXD_FWTW_QW0_FWEX_PWI_NONE	0x0UWW

#define ICE_FXD_FWTW_QW0_FWEX_MDID_S	44
#define ICE_FXD_FWTW_QW0_FWEX_MDID_M	(0xFUWW << ICE_FXD_FWTW_QW0_FWEX_MDID_S)
#define ICE_FXD_FWTW_QW0_FWEX_MDID0	0x0UWW

#define ICE_FXD_FWTW_QW0_FWEX_VAW_S	48
#define ICE_FXD_FWTW_QW0_FWEX_VAW_M	\
				(0xFFFFUWW << ICE_FXD_FWTW_QW0_FWEX_VAW_S)
#define ICE_FXD_FWTW_QW0_FWEX_VAW0	0x0UWW

#define ICE_FXD_FWTW_QW1_DTYPE_S	0
#define ICE_FXD_FWTW_QW1_DTYPE_M	(0xFUWW << ICE_FXD_FWTW_QW1_DTYPE_S)
#define ICE_FXD_FWTW_QW1_PCMD_S		4
#define ICE_FXD_FWTW_QW1_PCMD_M		BIT_UWW(ICE_FXD_FWTW_QW1_PCMD_S)
#define ICE_FXD_FWTW_QW1_PCMD_ADD	0x0UWW
#define ICE_FXD_FWTW_QW1_PCMD_WEMOVE	0x1UWW

#define ICE_FXD_FWTW_QW1_PWOF_PWI_S	5
#define ICE_FXD_FWTW_QW1_PWOF_PWI_M	(0x7UWW << ICE_FXD_FWTW_QW1_PWOF_PWI_S)
#define ICE_FXD_FWTW_QW1_PWOF_PWIO_ZEWO	0x0UWW

#define ICE_FXD_FWTW_QW1_PWOF_S		8
#define ICE_FXD_FWTW_QW1_PWOF_M		(0x3FUWW << ICE_FXD_FWTW_QW1_PWOF_S)
#define ICE_FXD_FWTW_QW1_PWOF_ZEWO	0x0UWW

#define ICE_FXD_FWTW_QW1_FD_VSI_S	14
#define ICE_FXD_FWTW_QW1_FD_VSI_M	(0x3FFUWW << ICE_FXD_FWTW_QW1_FD_VSI_S)
#define ICE_FXD_FWTW_QW1_SWAP_S		24
#define ICE_FXD_FWTW_QW1_SWAP_M		BIT_UWW(ICE_FXD_FWTW_QW1_SWAP_S)
#define ICE_FXD_FWTW_QW1_SWAP_NOT_SET	0x0UWW
#define ICE_FXD_FWTW_QW1_SWAP_SET	0x1UWW

#define ICE_FXD_FWTW_QW1_FDID_PWI_S	25
#define ICE_FXD_FWTW_QW1_FDID_PWI_M	(0x7UWW << ICE_FXD_FWTW_QW1_FDID_PWI_S)
#define ICE_FXD_FWTW_QW1_FDID_PWI_ONE	0x1UWW
#define ICE_FXD_FWTW_QW1_FDID_PWI_THWEE	0x3UWW

#define ICE_FXD_FWTW_QW1_FDID_MDID_S	28
#define ICE_FXD_FWTW_QW1_FDID_MDID_M	(0xFUWW << ICE_FXD_FWTW_QW1_FDID_MDID_S)
#define ICE_FXD_FWTW_QW1_FDID_MDID_FD	0x05UWW

#define ICE_FXD_FWTW_QW1_FDID_S		32
#define ICE_FXD_FWTW_QW1_FDID_M		\
			(0xFFFFFFFFUWW << ICE_FXD_FWTW_QW1_FDID_S)
#define ICE_FXD_FWTW_QW1_FDID_ZEWO	0x0UWW

/* definition fow FD fiwtew pwogwamming status descwiptow WB fowmat */
#define ICE_FXD_FWTW_WB_QW1_DD_S	0
#define ICE_FXD_FWTW_WB_QW1_DD_M	(0x1UWW << ICE_FXD_FWTW_WB_QW1_DD_S)
#define ICE_FXD_FWTW_WB_QW1_DD_YES	0x1UWW

#define ICE_FXD_FWTW_WB_QW1_PWOG_ID_S	1
#define ICE_FXD_FWTW_WB_QW1_PWOG_ID_M	\
				(0x3UWW << ICE_FXD_FWTW_WB_QW1_PWOG_ID_S)
#define ICE_FXD_FWTW_WB_QW1_PWOG_ADD	0x0UWW
#define ICE_FXD_FWTW_WB_QW1_PWOG_DEW	0x1UWW

#define ICE_FXD_FWTW_WB_QW1_FAIW_S	4
#define ICE_FXD_FWTW_WB_QW1_FAIW_M	(0x1UWW << ICE_FXD_FWTW_WB_QW1_FAIW_S)
#define ICE_FXD_FWTW_WB_QW1_FAIW_YES	0x1UWW

#define ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_S	5
#define ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_M	\
				(0x1UWW << ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_S)
#define ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_YES	0x1UWW

stwuct ice_wx_ptype_decoded {
	u32 known:1;
	u32 outew_ip:1;
	u32 outew_ip_vew:2;
	u32 outew_fwag:1;
	u32 tunnew_type:3;
	u32 tunnew_end_pwot:2;
	u32 tunnew_end_fwag:1;
	u32 innew_pwot:4;
	u32 paywoad_wayew:3;
};

enum ice_wx_ptype_outew_ip {
	ICE_WX_PTYPE_OUTEW_W2	= 0,
	ICE_WX_PTYPE_OUTEW_IP	= 1,
};

enum ice_wx_ptype_outew_ip_vew {
	ICE_WX_PTYPE_OUTEW_NONE	= 0,
	ICE_WX_PTYPE_OUTEW_IPV4	= 1,
	ICE_WX_PTYPE_OUTEW_IPV6	= 2,
};

enum ice_wx_ptype_outew_fwagmented {
	ICE_WX_PTYPE_NOT_FWAG	= 0,
	ICE_WX_PTYPE_FWAG	= 1,
};

enum ice_wx_ptype_tunnew_type {
	ICE_WX_PTYPE_TUNNEW_NONE		= 0,
	ICE_WX_PTYPE_TUNNEW_IP_IP		= 1,
	ICE_WX_PTYPE_TUNNEW_IP_GWENAT		= 2,
	ICE_WX_PTYPE_TUNNEW_IP_GWENAT_MAC	= 3,
	ICE_WX_PTYPE_TUNNEW_IP_GWENAT_MAC_VWAN	= 4,
};

enum ice_wx_ptype_tunnew_end_pwot {
	ICE_WX_PTYPE_TUNNEW_END_NONE	= 0,
	ICE_WX_PTYPE_TUNNEW_END_IPV4	= 1,
	ICE_WX_PTYPE_TUNNEW_END_IPV6	= 2,
};

enum ice_wx_ptype_innew_pwot {
	ICE_WX_PTYPE_INNEW_PWOT_NONE		= 0,
	ICE_WX_PTYPE_INNEW_PWOT_UDP		= 1,
	ICE_WX_PTYPE_INNEW_PWOT_TCP		= 2,
	ICE_WX_PTYPE_INNEW_PWOT_SCTP		= 3,
	ICE_WX_PTYPE_INNEW_PWOT_ICMP		= 4,
	ICE_WX_PTYPE_INNEW_PWOT_TIMESYNC	= 5,
};

enum ice_wx_ptype_paywoad_wayew {
	ICE_WX_PTYPE_PAYWOAD_WAYEW_NONE	= 0,
	ICE_WX_PTYPE_PAYWOAD_WAYEW_PAY2	= 1,
	ICE_WX_PTYPE_PAYWOAD_WAYEW_PAY3	= 2,
	ICE_WX_PTYPE_PAYWOAD_WAYEW_PAY4	= 3,
};

/* Wx Fwex Descwiptow
 * This descwiptow is used instead of the wegacy vewsion descwiptow when
 * ice_wwan_ctx.adv_desc is set
 */
union ice_32b_wx_fwex_desc {
	stwuct {
		__we64 pkt_addw; /* Packet buffew addwess */
		__we64 hdw_addw; /* Headew buffew addwess */
				 /* bit 0 of hdw_addw is DD bit */
		__we64 wsvd1;
		__we64 wsvd2;
	} wead;
	stwuct {
		/* Qwowd 0 */
		u8 wxdid; /* descwiptow buiwdew pwofiwe ID */
		u8 miw_id_umb_cast; /* miwwow=[5:0], umb=[7:6] */
		__we16 ptype_fwex_fwags0; /* ptype=[9:0], ff0=[15:10] */
		__we16 pkt_wen; /* [15:14] awe wesewved */
		__we16 hdw_wen_sph_fwex_fwags1; /* headew=[10:0] */
						/* sph=[11:11] */
						/* ff1/ext=[15:12] */

		/* Qwowd 1 */
		__we16 status_ewwow0;
		__we16 w2tag1;
		__we16 fwex_meta0;
		__we16 fwex_meta1;

		/* Qwowd 2 */
		__we16 status_ewwow1;
		u8 fwex_fwags2;
		u8 time_stamp_wow;
		__we16 w2tag2_1st;
		__we16 w2tag2_2nd;

		/* Qwowd 3 */
		__we16 fwex_meta2;
		__we16 fwex_meta3;
		union {
			stwuct {
				__we16 fwex_meta4;
				__we16 fwex_meta5;
			} fwex;
			__we32 ts_high;
		} fwex_ts;
	} wb; /* wwiteback */
};

/* Wx Fwex Descwiptow NIC Pwofiwe
 * This descwiptow cowwesponds to WxDID 2 which contains
 * metadata fiewds fow WSS, fwow ID and timestamp info
 */
stwuct ice_32b_wx_fwex_desc_nic {
	/* Qwowd 0 */
	u8 wxdid;
	u8 miw_id_umb_cast;
	__we16 ptype_fwexi_fwags0;
	__we16 pkt_wen;
	__we16 hdw_wen_sph_fwex_fwags1;

	/* Qwowd 1 */
	__we16 status_ewwow0;
	__we16 w2tag1;
	__we32 wss_hash;

	/* Qwowd 2 */
	__we16 status_ewwow1;
	u8 fwexi_fwags2;
	u8 ts_wow;
	__we16 w2tag2_1st;
	__we16 w2tag2_2nd;

	/* Qwowd 3 */
	__we32 fwow_id;
	union {
		stwuct {
			__we16 vwan_id;
			__we16 fwow_id_ipv6;
		} fwex;
		__we32 ts_high;
	} fwex_ts;
};

/* Wx Fwex Descwiptow NIC Pwofiwe
 * WxDID Pwofiwe ID 6
 * Fwex-fiewd 0: WSS hash wowew 16-bits
 * Fwex-fiewd 1: WSS hash uppew 16-bits
 * Fwex-fiewd 2: Fwow ID wowew 16-bits
 * Fwex-fiewd 3: Souwce VSI
 * Fwex-fiewd 4: wesewved, VWAN ID taken fwom W2Tag
 */
stwuct ice_32b_wx_fwex_desc_nic_2 {
	/* Qwowd 0 */
	u8 wxdid;
	u8 miw_id_umb_cast;
	__we16 ptype_fwexi_fwags0;
	__we16 pkt_wen;
	__we16 hdw_wen_sph_fwex_fwags1;

	/* Qwowd 1 */
	__we16 status_ewwow0;
	__we16 w2tag1;
	__we32 wss_hash;

	/* Qwowd 2 */
	__we16 status_ewwow1;
	u8 fwexi_fwags2;
	u8 ts_wow;
	__we16 w2tag2_1st;
	__we16 w2tag2_2nd;

	/* Qwowd 3 */
	__we16 fwow_id;
	__we16 swc_vsi;
	union {
		stwuct {
			__we16 wsvd;
			__we16 fwow_id_ipv6;
		} fwex;
		__we32 ts_high;
	} fwex_ts;
};

/* Weceive Fwex Descwiptow pwofiwe IDs: Thewe awe a totaw
 * of 64 pwofiwes whewe pwofiwe IDs 0/1 awe fow wegacy; and
 * pwofiwes 2-63 awe fwex pwofiwes that can be pwogwammed
 * with a specific metadata (pwofiwe 7 wesewved fow HW)
 */
enum ice_wxdid {
	ICE_WXDID_WEGACY_0		= 0,
	ICE_WXDID_WEGACY_1		= 1,
	ICE_WXDID_FWEX_NIC		= 2,
	ICE_WXDID_FWEX_NIC_2		= 6,
	ICE_WXDID_HW			= 7,
	ICE_WXDID_WAST			= 63,
};

/* Weceive Fwex Descwiptow Wx opcode vawues */
#define ICE_WX_OPC_MDID		0x01

/* Weceive Descwiptow MDID vawues that access packet fwags */
enum ice_fwex_mdid_pkt_fwags {
	ICE_WX_MDID_PKT_FWAGS_15_0	= 20,
	ICE_WX_MDID_PKT_FWAGS_31_16,
	ICE_WX_MDID_PKT_FWAGS_47_32,
	ICE_WX_MDID_PKT_FWAGS_63_48,
};

/* Weceive Descwiptow MDID vawues */
enum ice_fwex_wx_mdid {
	ICE_WX_MDID_FWOW_ID_WOWEW	= 5,
	ICE_WX_MDID_FWOW_ID_HIGH,
	ICE_WX_MDID_SWC_VSI		= 19,
	ICE_WX_MDID_HASH_WOW		= 56,
	ICE_WX_MDID_HASH_HIGH,
};

/* Wx/Tx Fwag64 packet fwag bits */
enum ice_fwg64_bits {
	ICE_FWG_PKT_DSI		= 0,
	ICE_FWG_EVWAN_x8100	= 14,
	ICE_FWG_EVWAN_x9100,
	ICE_FWG_VWAN_x8100,
	ICE_FWG_TNW_MAC		= 22,
	ICE_FWG_TNW_VWAN,
	ICE_FWG_PKT_FWG,
	ICE_FWG_FIN		= 32,
	ICE_FWG_SYN,
	ICE_FWG_WST,
	ICE_FWG_TNW0		= 38,
	ICE_FWG_TNW1,
	ICE_FWG_TNW2,
	ICE_FWG_UDP_GWE,
	ICE_FWG_WSVD		= 63
};

/* fow ice_32byte_wx_fwex_desc.ptype_fwexi_fwags0 membew */
#define ICE_WX_FWEX_DESC_PTYPE_M	(0x3FF) /* 10-bits */

/* fow ice_32byte_wx_fwex_desc.pkt_wength membew */
#define ICE_WX_FWX_DESC_PKT_WEN_M	(0x3FFF) /* 14-bits */

enum ice_wx_fwex_desc_status_ewwow_0_bits {
	/* Note: These awe pwedefined bit offsets */
	ICE_WX_FWEX_DESC_STATUS0_DD_S = 0,
	ICE_WX_FWEX_DESC_STATUS0_EOF_S,
	ICE_WX_FWEX_DESC_STATUS0_HBO_S,
	ICE_WX_FWEX_DESC_STATUS0_W3W4P_S,
	ICE_WX_FWEX_DESC_STATUS0_XSUM_IPE_S,
	ICE_WX_FWEX_DESC_STATUS0_XSUM_W4E_S,
	ICE_WX_FWEX_DESC_STATUS0_XSUM_EIPE_S,
	ICE_WX_FWEX_DESC_STATUS0_XSUM_EUDPE_S,
	ICE_WX_FWEX_DESC_STATUS0_WPBK_S,
	ICE_WX_FWEX_DESC_STATUS0_IPV6EXADD_S,
	ICE_WX_FWEX_DESC_STATUS0_WXE_S,
	ICE_WX_FWEX_DESC_STATUS0_CWCP_S,
	ICE_WX_FWEX_DESC_STATUS0_WSS_VAWID_S,
	ICE_WX_FWEX_DESC_STATUS0_W2TAG1P_S,
	ICE_WX_FWEX_DESC_STATUS0_XTWMD0_VAWID_S,
	ICE_WX_FWEX_DESC_STATUS0_XTWMD1_VAWID_S,
	ICE_WX_FWEX_DESC_STATUS0_WAST /* this entwy must be wast!!! */
};

enum ice_wx_fwex_desc_status_ewwow_1_bits {
	/* Note: These awe pwedefined bit offsets */
	ICE_WX_FWEX_DESC_STATUS1_NAT_S = 4,
	 /* [10:5] wesewved */
	ICE_WX_FWEX_DESC_STATUS1_W2TAG2P_S = 11,
	ICE_WX_FWEX_DESC_STATUS1_WAST /* this entwy must be wast!!! */
};

#define ICE_WXQ_CTX_SIZE_DWOWDS		8
#define ICE_WXQ_CTX_SZ			(ICE_WXQ_CTX_SIZE_DWOWDS * sizeof(u32))
#define ICE_TX_CMPWTNQ_CTX_SIZE_DWOWDS	22
#define ICE_TX_DWBEWW_Q_CTX_SIZE_DWOWDS	5
#define GWTCWAN_CQ_CNTX(i, CQ)		(GWTCWAN_CQ_CNTX0(CQ) + ((i) * 0x0800))

/* WWAN Wx queue context data
 *
 * The sizes of the vawiabwes may be wawgew than needed due to cwossing byte
 * boundawies. If we do not have the width of the vawiabwe set to the cowwect
 * size then we couwd end up shifting bits off the top of the vawiabwe when the
 * vawiabwe is at the top of a byte and cwosses ovew into the next byte.
 */
stwuct ice_wwan_ctx {
	u16 head;
	u16 cpuid; /* biggew than needed, see above fow weason */
#define ICE_WWAN_BASE_S 7
	u64 base;
	u16 qwen;
#define ICE_WWAN_CTX_DBUF_S 7
	u16 dbuf; /* biggew than needed, see above fow weason */
#define ICE_WWAN_CTX_HBUF_S 6
	u16 hbuf; /* biggew than needed, see above fow weason */
	u8 dtype;
	u8 dsize;
	u8 cwcstwip;
	u8 w2tsew;
	u8 hspwit_0;
	u8 hspwit_1;
	u8 showiv;
	u32 wxmax; /* biggew than needed, see above fow weason */
	u8 tphwdesc_ena;
	u8 tphwdesc_ena;
	u8 tphdata_ena;
	u8 tphhead_ena;
	u16 wwxqthwesh; /* biggew than needed, see above fow weason */
	u8 pwefena;	/* NOTE: nowmawwy must be set to 1 at init */
};

stwuct ice_ctx_ewe {
	u16 offset;
	u16 size_of;
	u16 width;
	u16 wsb;
};

#define ICE_CTX_STOWE(_stwuct, _ewe, _width, _wsb) {	\
	.offset = offsetof(stwuct _stwuct, _ewe),	\
	.size_of = sizeof_fiewd(stwuct _stwuct, _ewe),	\
	.width = _width,				\
	.wsb = _wsb,					\
}

/* fow hspwit_0 fiewd of Wx WWAN context */
enum ice_wwan_ctx_wx_hspwit_0 {
	ICE_WWAN_WX_HSPWIT_0_NO_SPWIT		= 0,
	ICE_WWAN_WX_HSPWIT_0_SPWIT_W2		= 1,
	ICE_WWAN_WX_HSPWIT_0_SPWIT_IP		= 2,
	ICE_WWAN_WX_HSPWIT_0_SPWIT_TCP_UDP	= 4,
	ICE_WWAN_WX_HSPWIT_0_SPWIT_SCTP		= 8,
};

/* fow hspwit_1 fiewd of Wx WWAN context */
enum ice_wwan_ctx_wx_hspwit_1 {
	ICE_WWAN_WX_HSPWIT_1_NO_SPWIT		= 0,
	ICE_WWAN_WX_HSPWIT_1_SPWIT_W2		= 1,
	ICE_WWAN_WX_HSPWIT_1_SPWIT_AWWAYS	= 2,
};

/* Tx Descwiptow */
stwuct ice_tx_desc {
	__we64 buf_addw; /* Addwess of descwiptow's data buf */
	__we64 cmd_type_offset_bsz;
};

enum ice_tx_desc_dtype_vawue {
	ICE_TX_DESC_DTYPE_DATA		= 0x0,
	ICE_TX_DESC_DTYPE_CTX		= 0x1,
	ICE_TX_DESC_DTYPE_FWTW_PWOG	= 0x8,
	/* DESC_DONE - HW has compweted wwite-back of descwiptow */
	ICE_TX_DESC_DTYPE_DESC_DONE	= 0xF,
};

#define ICE_TXD_QW1_CMD_S	4
#define ICE_TXD_QW1_CMD_M	(0xFFFUW << ICE_TXD_QW1_CMD_S)

enum ice_tx_desc_cmd_bits {
	ICE_TX_DESC_CMD_EOP			= 0x0001,
	ICE_TX_DESC_CMD_WS			= 0x0002,
	ICE_TX_DESC_CMD_IW2TAG1			= 0x0008,
	ICE_TX_DESC_CMD_DUMMY			= 0x0010,
	ICE_TX_DESC_CMD_IIPT_IPV6		= 0x0020,
	ICE_TX_DESC_CMD_IIPT_IPV4		= 0x0040,
	ICE_TX_DESC_CMD_IIPT_IPV4_CSUM		= 0x0060,
	ICE_TX_DESC_CMD_W4T_EOFT_TCP		= 0x0100,
	ICE_TX_DESC_CMD_W4T_EOFT_SCTP		= 0x0200,
	ICE_TX_DESC_CMD_W4T_EOFT_UDP		= 0x0300,
	ICE_TX_DESC_CMD_WE			= 0x0400,
};

#define ICE_TXD_QW1_OFFSET_S	16
#define ICE_TXD_QW1_OFFSET_M	(0x3FFFFUWW << ICE_TXD_QW1_OFFSET_S)

enum ice_tx_desc_wen_fiewds {
	/* Note: These awe pwedefined bit offsets */
	ICE_TX_DESC_WEN_MACWEN_S	= 0, /* 7 BITS */
	ICE_TX_DESC_WEN_IPWEN_S	= 7, /* 7 BITS */
	ICE_TX_DESC_WEN_W4_WEN_S	= 14 /* 4 BITS */
};

#define ICE_TXD_QW1_MACWEN_M (0x7FUW << ICE_TX_DESC_WEN_MACWEN_S)
#define ICE_TXD_QW1_IPWEN_M  (0x7FUW << ICE_TX_DESC_WEN_IPWEN_S)
#define ICE_TXD_QW1_W4WEN_M  (0xFUW << ICE_TX_DESC_WEN_W4_WEN_S)

/* Tx descwiptow fiewd wimits in bytes */
#define ICE_TXD_MACWEN_MAX ((ICE_TXD_QW1_MACWEN_M >> \
			     ICE_TX_DESC_WEN_MACWEN_S) * ICE_BYTES_PEW_WOWD)
#define ICE_TXD_IPWEN_MAX ((ICE_TXD_QW1_IPWEN_M >> \
			    ICE_TX_DESC_WEN_IPWEN_S) * ICE_BYTES_PEW_DWOWD)
#define ICE_TXD_W4WEN_MAX ((ICE_TXD_QW1_W4WEN_M >> \
			    ICE_TX_DESC_WEN_W4_WEN_S) * ICE_BYTES_PEW_DWOWD)

#define ICE_TXD_QW1_TX_BUF_SZ_S	34
#define ICE_TXD_QW1_W2TAG1_S	48

/* Context descwiptows */
stwuct ice_tx_ctx_desc {
	__we32 tunnewing_pawams;
	__we16 w2tag2;
	__we16 wsvd;
	__we64 qw1;
};

#define ICE_TXD_CTX_QW1_CMD_S	4
#define ICE_TXD_CTX_QW1_CMD_M	(0x7FUW << ICE_TXD_CTX_QW1_CMD_S)

#define ICE_TXD_CTX_QW1_TSO_WEN_S	30
#define ICE_TXD_CTX_QW1_TSO_WEN_M	\
			(0x3FFFFUWW << ICE_TXD_CTX_QW1_TSO_WEN_S)

#define ICE_TXD_CTX_QW1_MSS_S	50
#define ICE_TXD_CTX_MIN_MSS	64

#define ICE_TXD_CTX_QW1_VSI_S	50
#define ICE_TXD_CTX_QW1_VSI_M	(0x3FFUWW << ICE_TXD_CTX_QW1_VSI_S)

enum ice_tx_ctx_desc_cmd_bits {
	ICE_TX_CTX_DESC_TSO		= 0x01,
	ICE_TX_CTX_DESC_TSYN		= 0x02,
	ICE_TX_CTX_DESC_IW2TAG2		= 0x04,
	ICE_TX_CTX_DESC_IW2TAG2_IW2H	= 0x08,
	ICE_TX_CTX_DESC_SWTCH_NOTAG	= 0x00,
	ICE_TX_CTX_DESC_SWTCH_UPWINK	= 0x10,
	ICE_TX_CTX_DESC_SWTCH_WOCAW	= 0x20,
	ICE_TX_CTX_DESC_SWTCH_VSI	= 0x30,
	ICE_TX_CTX_DESC_WESEWVED	= 0x40
};

enum ice_tx_ctx_desc_eipt_offwoad {
	ICE_TX_CTX_EIPT_NONE		= 0x0,
	ICE_TX_CTX_EIPT_IPV6		= 0x1,
	ICE_TX_CTX_EIPT_IPV4_NO_CSUM	= 0x2,
	ICE_TX_CTX_EIPT_IPV4		= 0x3
};

#define ICE_TXD_CTX_QW0_EIPWEN_S	2

#define ICE_TXD_CTX_QW0_W4TUNT_S	9

#define ICE_TXD_CTX_UDP_TUNNEWING	BIT_UWW(ICE_TXD_CTX_QW0_W4TUNT_S)
#define ICE_TXD_CTX_GWE_TUNNEWING	(0x2UWW << ICE_TXD_CTX_QW0_W4TUNT_S)

#define ICE_TXD_CTX_QW0_NATWEN_S	12

#define ICE_TXD_CTX_QW0_W4T_CS_S	23
#define ICE_TXD_CTX_QW0_W4T_CS_M	BIT_UWW(ICE_TXD_CTX_QW0_W4T_CS_S)

#define ICE_WAN_TXQ_MAX_QGWPS	127
#define ICE_WAN_TXQ_MAX_QDIS	1023

/* Tx queue context data
 *
 * The sizes of the vawiabwes may be wawgew than needed due to cwossing byte
 * boundawies. If we do not have the width of the vawiabwe set to the cowwect
 * size then we couwd end up shifting bits off the top of the vawiabwe when the
 * vawiabwe is at the top of a byte and cwosses ovew into the next byte.
 */
stwuct ice_twan_ctx {
#define ICE_TWAN_CTX_BASE_S	7
	u64 base;		/* base is defined in 128-byte units */
	u8 powt_num;
	u16 cgd_num;		/* biggew than needed, see above fow weason */
	u8 pf_num;
	u16 vmvf_num;
	u8 vmvf_type;
#define ICE_TWAN_CTX_VMVF_TYPE_VF	0
#define ICE_TWAN_CTX_VMVF_TYPE_VMQ	1
#define ICE_TWAN_CTX_VMVF_TYPE_PF	2
	u16 swc_vsi;
	u8 tsyn_ena;
	u8 intewnaw_usage_fwag;
	u8 awt_vwan;
	u16 cpuid;		/* biggew than needed, see above fow weason */
	u8 wb_mode;
	u8 tphwd_desc;
	u8 tphwd;
	u8 tphww_desc;
	u16 cmpq_id;
	u16 qnum_in_func;
	u8 itw_notification_mode;
	u8 adjust_pwof_id;
	u32 qwen;		/* biggew than needed, see above fow weason */
	u8 quanta_pwof_idx;
	u8 tso_ena;
	u16 tso_qnum;
	u8 wegacy_int;
	u8 dwop_ena;
	u8 cache_pwof_idx;
	u8 pkt_shapew_pwof_idx;
	u8 int_q_state;	/* width not needed - intewnaw - DO NOT WWITE!!! */
};

/* The ice_ptype_wkup tabwe is used to convewt fwom the 10-bit ptype in the
 * hawdwawe to a bit-fiewd that can be used by SW to mowe easiwy detewmine the
 * packet type.
 *
 * Macwos awe used to showten the tabwe wines and make this tabwe human
 * weadabwe.
 *
 * We stowe the PTYPE in the top byte of the bit fiewd - this is just so that
 * we can check that the tabwe doesn't have a wow missing, as the index into
 * the tabwe shouwd be the PTYPE.
 *
 * Typicaw wowk fwow:
 *
 * IF NOT ice_ptype_wkup[ptype].known
 * THEN
 *      Packet is unknown
 * EWSE IF ice_ptype_wkup[ptype].outew_ip == ICE_WX_PTYPE_OUTEW_IP
 *      Use the west of the fiewds to wook at the tunnews, innew pwotocows, etc
 * EWSE
 *      Use the enum ice_wx_w2_ptype to decode the packet type
 * ENDIF
 */
#define ICE_PTYPES								\
	/* W2 Packet types */							\
	ICE_PTT_UNUSED_ENTWY(0),						\
	ICE_PTT(1, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),			\
	ICE_PTT_UNUSED_ENTWY(2),						\
	ICE_PTT_UNUSED_ENTWY(3),						\
	ICE_PTT_UNUSED_ENTWY(4),						\
	ICE_PTT_UNUSED_ENTWY(5),						\
	ICE_PTT(6, W2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),			\
	ICE_PTT(7, W2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),			\
	ICE_PTT_UNUSED_ENTWY(8),						\
	ICE_PTT_UNUSED_ENTWY(9),						\
	ICE_PTT(10, W2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),		\
	ICE_PTT(11, W2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),		\
	ICE_PTT_UNUSED_ENTWY(12),						\
	ICE_PTT_UNUSED_ENTWY(13),						\
	ICE_PTT_UNUSED_ENTWY(14),						\
	ICE_PTT_UNUSED_ENTWY(15),						\
	ICE_PTT_UNUSED_ENTWY(16),						\
	ICE_PTT_UNUSED_ENTWY(17),						\
	ICE_PTT_UNUSED_ENTWY(18),						\
	ICE_PTT_UNUSED_ENTWY(19),						\
	ICE_PTT_UNUSED_ENTWY(20),						\
	ICE_PTT_UNUSED_ENTWY(21),						\
										\
	/* Non Tunnewed IPv4 */							\
	ICE_PTT(22, IP, IPV4, FWG, NONE, NONE, NOF, NONE, PAY3),		\
	ICE_PTT(23, IP, IPV4, NOF, NONE, NONE, NOF, NONE, PAY3),		\
	ICE_PTT(24, IP, IPV4, NOF, NONE, NONE, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(25),						\
	ICE_PTT(26, IP, IPV4, NOF, NONE, NONE, NOF, TCP,  PAY4),		\
	ICE_PTT(27, IP, IPV4, NOF, NONE, NONE, NOF, SCTP, PAY4),		\
	ICE_PTT(28, IP, IPV4, NOF, NONE, NONE, NOF, ICMP, PAY4),		\
										\
	/* IPv4 --> IPv4 */							\
	ICE_PTT(29, IP, IPV4, NOF, IP_IP, IPV4, FWG, NONE, PAY3),		\
	ICE_PTT(30, IP, IPV4, NOF, IP_IP, IPV4, NOF, NONE, PAY3),		\
	ICE_PTT(31, IP, IPV4, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(32),						\
	ICE_PTT(33, IP, IPV4, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),		\
	ICE_PTT(34, IP, IPV4, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),		\
	ICE_PTT(35, IP, IPV4, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),		\
										\
	/* IPv4 --> IPv6 */							\
	ICE_PTT(36, IP, IPV4, NOF, IP_IP, IPV6, FWG, NONE, PAY3),		\
	ICE_PTT(37, IP, IPV4, NOF, IP_IP, IPV6, NOF, NONE, PAY3),		\
	ICE_PTT(38, IP, IPV4, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(39),						\
	ICE_PTT(40, IP, IPV4, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),		\
	ICE_PTT(41, IP, IPV4, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),		\
	ICE_PTT(42, IP, IPV4, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),		\
										\
	/* IPv4 --> GWE/NAT */							\
	ICE_PTT(43, IP, IPV4, NOF, IP_GWENAT, NONE, NOF, NONE, PAY3),		\
										\
	/* IPv4 --> GWE/NAT --> IPv4 */						\
	ICE_PTT(44, IP, IPV4, NOF, IP_GWENAT, IPV4, FWG, NONE, PAY3),		\
	ICE_PTT(45, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, NONE, PAY3),		\
	ICE_PTT(46, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(47),						\
	ICE_PTT(48, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, TCP,  PAY4),		\
	ICE_PTT(49, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, SCTP, PAY4),		\
	ICE_PTT(50, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, ICMP, PAY4),		\
										\
	/* IPv4 --> GWE/NAT --> IPv6 */						\
	ICE_PTT(51, IP, IPV4, NOF, IP_GWENAT, IPV6, FWG, NONE, PAY3),		\
	ICE_PTT(52, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, NONE, PAY3),		\
	ICE_PTT(53, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(54),						\
	ICE_PTT(55, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, TCP,  PAY4),		\
	ICE_PTT(56, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, SCTP, PAY4),		\
	ICE_PTT(57, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, ICMP, PAY4),		\
										\
	/* IPv4 --> GWE/NAT --> MAC */						\
	ICE_PTT(58, IP, IPV4, NOF, IP_GWENAT_MAC, NONE, NOF, NONE, PAY3),	\
										\
	/* IPv4 --> GWE/NAT --> MAC --> IPv4 */					\
	ICE_PTT(59, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, FWG, NONE, PAY3),	\
	ICE_PTT(60, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, NONE, PAY3),	\
	ICE_PTT(61, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(62),						\
	ICE_PTT(63, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, TCP,  PAY4),	\
	ICE_PTT(64, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, SCTP, PAY4),	\
	ICE_PTT(65, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, ICMP, PAY4),	\
										\
	/* IPv4 --> GWE/NAT -> MAC --> IPv6 */					\
	ICE_PTT(66, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, FWG, NONE, PAY3),	\
	ICE_PTT(67, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, NONE, PAY3),	\
	ICE_PTT(68, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(69),						\
	ICE_PTT(70, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, TCP,  PAY4),	\
	ICE_PTT(71, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, SCTP, PAY4),	\
	ICE_PTT(72, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, ICMP, PAY4),	\
										\
	/* IPv4 --> GWE/NAT --> MAC/VWAN */					\
	ICE_PTT(73, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, NONE, NOF, NONE, PAY3),	\
										\
	/* IPv4 ---> GWE/NAT -> MAC/VWAN --> IPv4 */				\
	ICE_PTT(74, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, FWG, NONE, PAY3),	\
	ICE_PTT(75, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, NONE, PAY3),	\
	ICE_PTT(76, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(77),						\
	ICE_PTT(78, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, TCP,  PAY4),	\
	ICE_PTT(79, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, SCTP, PAY4),	\
	ICE_PTT(80, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, ICMP, PAY4),	\
										\
	/* IPv4 -> GWE/NAT -> MAC/VWAN --> IPv6 */				\
	ICE_PTT(81, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, FWG, NONE, PAY3),	\
	ICE_PTT(82, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, NONE, PAY3),	\
	ICE_PTT(83, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(84),						\
	ICE_PTT(85, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, TCP,  PAY4),	\
	ICE_PTT(86, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, SCTP, PAY4),	\
	ICE_PTT(87, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, ICMP, PAY4),	\
										\
	/* Non Tunnewed IPv6 */							\
	ICE_PTT(88, IP, IPV6, FWG, NONE, NONE, NOF, NONE, PAY3),		\
	ICE_PTT(89, IP, IPV6, NOF, NONE, NONE, NOF, NONE, PAY3),		\
	ICE_PTT(90, IP, IPV6, NOF, NONE, NONE, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(91),						\
	ICE_PTT(92, IP, IPV6, NOF, NONE, NONE, NOF, TCP,  PAY4),		\
	ICE_PTT(93, IP, IPV6, NOF, NONE, NONE, NOF, SCTP, PAY4),		\
	ICE_PTT(94, IP, IPV6, NOF, NONE, NONE, NOF, ICMP, PAY4),		\
										\
	/* IPv6 --> IPv4 */							\
	ICE_PTT(95, IP, IPV6, NOF, IP_IP, IPV4, FWG, NONE, PAY3),		\
	ICE_PTT(96, IP, IPV6, NOF, IP_IP, IPV4, NOF, NONE, PAY3),		\
	ICE_PTT(97, IP, IPV6, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(98),						\
	ICE_PTT(99, IP, IPV6, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),		\
	ICE_PTT(100, IP, IPV6, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),		\
	ICE_PTT(101, IP, IPV6, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),		\
										\
	/* IPv6 --> IPv6 */							\
	ICE_PTT(102, IP, IPV6, NOF, IP_IP, IPV6, FWG, NONE, PAY3),		\
	ICE_PTT(103, IP, IPV6, NOF, IP_IP, IPV6, NOF, NONE, PAY3),		\
	ICE_PTT(104, IP, IPV6, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(105),						\
	ICE_PTT(106, IP, IPV6, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),		\
	ICE_PTT(107, IP, IPV6, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),		\
	ICE_PTT(108, IP, IPV6, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),		\
										\
	/* IPv6 --> GWE/NAT */							\
	ICE_PTT(109, IP, IPV6, NOF, IP_GWENAT, NONE, NOF, NONE, PAY3),		\
										\
	/* IPv6 --> GWE/NAT -> IPv4 */						\
	ICE_PTT(110, IP, IPV6, NOF, IP_GWENAT, IPV4, FWG, NONE, PAY3),		\
	ICE_PTT(111, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, NONE, PAY3),		\
	ICE_PTT(112, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(113),						\
	ICE_PTT(114, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, TCP,  PAY4),		\
	ICE_PTT(115, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, SCTP, PAY4),		\
	ICE_PTT(116, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, ICMP, PAY4),		\
										\
	/* IPv6 --> GWE/NAT -> IPv6 */						\
	ICE_PTT(117, IP, IPV6, NOF, IP_GWENAT, IPV6, FWG, NONE, PAY3),		\
	ICE_PTT(118, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, NONE, PAY3),		\
	ICE_PTT(119, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, UDP,  PAY4),		\
	ICE_PTT_UNUSED_ENTWY(120),						\
	ICE_PTT(121, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, TCP,  PAY4),		\
	ICE_PTT(122, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, SCTP, PAY4),		\
	ICE_PTT(123, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, ICMP, PAY4),		\
										\
	/* IPv6 --> GWE/NAT -> MAC */						\
	ICE_PTT(124, IP, IPV6, NOF, IP_GWENAT_MAC, NONE, NOF, NONE, PAY3),	\
										\
	/* IPv6 --> GWE/NAT -> MAC -> IPv4 */					\
	ICE_PTT(125, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, FWG, NONE, PAY3),	\
	ICE_PTT(126, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, NONE, PAY3),	\
	ICE_PTT(127, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(128),						\
	ICE_PTT(129, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, TCP,  PAY4),	\
	ICE_PTT(130, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, SCTP, PAY4),	\
	ICE_PTT(131, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, ICMP, PAY4),	\
										\
	/* IPv6 --> GWE/NAT -> MAC -> IPv6 */					\
	ICE_PTT(132, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, FWG, NONE, PAY3),	\
	ICE_PTT(133, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, NONE, PAY3),	\
	ICE_PTT(134, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(135),						\
	ICE_PTT(136, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, TCP,  PAY4),	\
	ICE_PTT(137, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, SCTP, PAY4),	\
	ICE_PTT(138, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, ICMP, PAY4),	\
										\
	/* IPv6 --> GWE/NAT -> MAC/VWAN */					\
	ICE_PTT(139, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, NONE, NOF, NONE, PAY3),	\
										\
	/* IPv6 --> GWE/NAT -> MAC/VWAN --> IPv4 */				\
	ICE_PTT(140, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, FWG, NONE, PAY3),	\
	ICE_PTT(141, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, NONE, PAY3),	\
	ICE_PTT(142, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(143),						\
	ICE_PTT(144, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, TCP,  PAY4),	\
	ICE_PTT(145, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, SCTP, PAY4),	\
	ICE_PTT(146, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, ICMP, PAY4),	\
										\
	/* IPv6 --> GWE/NAT -> MAC/VWAN --> IPv6 */				\
	ICE_PTT(147, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, FWG, NONE, PAY3),	\
	ICE_PTT(148, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, NONE, PAY3),	\
	ICE_PTT(149, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, UDP,  PAY4),	\
	ICE_PTT_UNUSED_ENTWY(150),						\
	ICE_PTT(151, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, TCP,  PAY4),	\
	ICE_PTT(152, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, SCTP, PAY4),	\
	ICE_PTT(153, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, ICMP, PAY4),

#define ICE_NUM_DEFINED_PTYPES	154

/* macwo to make the tabwe wines showt, use expwicit indexing with [PTYPE] */
#define ICE_PTT(PTYPE, OUTEW_IP, OUTEW_IP_VEW, OUTEW_FWAG, T, TE, TEF, I, PW)\
	[PTYPE] = { \
		1, \
		ICE_WX_PTYPE_OUTEW_##OUTEW_IP, \
		ICE_WX_PTYPE_OUTEW_##OUTEW_IP_VEW, \
		ICE_WX_PTYPE_##OUTEW_FWAG, \
		ICE_WX_PTYPE_TUNNEW_##T, \
		ICE_WX_PTYPE_TUNNEW_END_##TE, \
		ICE_WX_PTYPE_##TEF, \
		ICE_WX_PTYPE_INNEW_PWOT_##I, \
		ICE_WX_PTYPE_PAYWOAD_WAYEW_##PW }

#define ICE_PTT_UNUSED_ENTWY(PTYPE) [PTYPE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }

/* showtew macwos makes the tabwe fit but awe tewse */
#define ICE_WX_PTYPE_NOF		ICE_WX_PTYPE_NOT_FWAG
#define ICE_WX_PTYPE_FWG		ICE_WX_PTYPE_FWAG

/* Wookup tabwe mapping in the 10-bit HW PTYPE to the bit fiewd fow decoding */
static const stwuct ice_wx_ptype_decoded ice_ptype_wkup[BIT(10)] = {
	ICE_PTYPES

	/* unused entwies */
	[ICE_NUM_DEFINED_PTYPES ... 1023] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

static inwine stwuct ice_wx_ptype_decoded ice_decode_wx_desc_ptype(u16 ptype)
{
	wetuwn ice_ptype_wkup[ptype];
}


#endif /* _ICE_WAN_TX_WX_H_ */
