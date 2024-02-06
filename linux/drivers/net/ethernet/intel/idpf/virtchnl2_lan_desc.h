/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _VIWTCHNW2_WAN_DESC_H_
#define _VIWTCHNW2_WAN_DESC_H_

#incwude <winux/bits.h>

/* This is an intewface definition fiwe whewe existing enums and theiw vawues
 * must wemain unchanged ovew time, so we specify expwicit vawues fow aww enums.
 */

/* Twansmit descwiptow ID fwags
 */
enum viwtchnw2_tx_desc_ids {
	VIWTCHNW2_TXDID_DATA				= BIT(0),
	VIWTCHNW2_TXDID_CTX				= BIT(1),
	/* TXDID bit 2 is wesewved
	 * TXDID bit 3 is fwee fow futuwe use
	 * TXDID bit 4 is wesewved
	 */
	VIWTCHNW2_TXDID_FWEX_TSO_CTX			= BIT(5),
	/* TXDID bit 6 is wesewved */
	VIWTCHNW2_TXDID_FWEX_W2TAG1_W2TAG2		= BIT(7),
	/* TXDID bits 8 and 9 awe fwee fow futuwe use
	 * TXDID bit 10 is wesewved
	 * TXDID bit 11 is fwee fow futuwe use
	 */
	VIWTCHNW2_TXDID_FWEX_FWOW_SCHED			= BIT(12),
	/* TXDID bits 13 and 14 awe fwee fow futuwe use */
	VIWTCHNW2_TXDID_DESC_DONE			= BIT(15),
};

/* Weceive descwiptow IDs */
enum viwtchnw2_wx_desc_ids {
	VIWTCHNW2_WXDID_1_32B_BASE	= 1,
	/* FWEX_SQ_NIC and FWEX_SPWITQ shawe desc ids because they can be
	 * diffewentiated based on queue modew; e.g. singwe queue modew can
	 * onwy use FWEX_SQ_NIC and spwit queue modew can onwy use FWEX_SPWITQ
	 * fow DID 2.
	 */
	VIWTCHNW2_WXDID_2_FWEX_SPWITQ	= 2,
	VIWTCHNW2_WXDID_2_FWEX_SQ_NIC	= VIWTCHNW2_WXDID_2_FWEX_SPWITQ,
	/* 3 thwough 6 awe wesewved */
	VIWTCHNW2_WXDID_7_HW_WSVD	= 7,
	/* 8 thwough 15 awe fwee */
};

/* Weceive descwiptow ID bitmasks */
#define VIWTCHNW2_WXDID_M(bit)			BIT_UWW(VIWTCHNW2_WXDID_##bit)

enum viwtchnw2_wx_desc_id_bitmasks {
	VIWTCHNW2_WXDID_1_32B_BASE_M	= VIWTCHNW2_WXDID_M(1_32B_BASE),
	VIWTCHNW2_WXDID_2_FWEX_SPWITQ_M	= VIWTCHNW2_WXDID_M(2_FWEX_SPWITQ),
	VIWTCHNW2_WXDID_2_FWEX_SQ_NIC_M	= VIWTCHNW2_WXDID_M(2_FWEX_SQ_NIC),
	VIWTCHNW2_WXDID_7_HW_WSVD_M	= VIWTCHNW2_WXDID_M(7_HW_WSVD),
};

/* Fow spwitq viwtchnw2_wx_fwex_desc_adv_nic_3 desc membews */
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WXDID_M		GENMASK(3, 0)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_UMBCAST_M		GENMASK(7, 6)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_PTYPE_M		GENMASK(9, 0)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WAW_CSUM_INV_S	12
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WAW_CSUM_INV_M	\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_WAW_CSUM_INV_S)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_FF0_M		GENMASK(15, 13)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WEN_PBUF_M		GENMASK(13, 0)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_GEN_S		14
#define VIWTCHNW2_WX_FWEX_DESC_ADV_GEN_M		\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_GEN_S)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_BUFQ_ID_S		15
#define VIWTCHNW2_WX_FWEX_DESC_ADV_BUFQ_ID_M		\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_BUFQ_ID_S)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WEN_HDW_M		GENMASK(9, 0)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WSC_S		10
#define VIWTCHNW2_WX_FWEX_DESC_ADV_WSC_M		\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_WSC_S)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_SPH_S		11
#define VIWTCHNW2_WX_FWEX_DESC_ADV_SPH_M		\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_SPH_S)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_FF1_S		12
#define VIWTCHNW2_WX_FWEX_DESC_ADV_FF1_M		GENMASK(14, 12)
#define VIWTCHNW2_WX_FWEX_DESC_ADV_MISS_S		15
#define VIWTCHNW2_WX_FWEX_DESC_ADV_MISS_M		\
	BIT_UWW(VIWTCHNW2_WX_FWEX_DESC_ADV_MISS_S)

/* Bitmasks fow spwitq viwtchnw2_wx_fwex_desc_adv_nic_3 */
enum viwtchw2_wx_fwex_desc_adv_status_ewwow_0_qw1_bits {
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_DD_M			= BIT(0),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_EOF_M		= BIT(1),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_HBO_M		= BIT(2),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_W3W4P_M		= BIT(3),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_IPE_M		= BIT(4),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_W4E_M		= BIT(5),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_EIPE_M		= BIT(6),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_EUDPE_M		= BIT(7),
};

/* Bitmasks fow spwitq viwtchnw2_wx_fwex_desc_adv_nic_3 */
enum viwtchnw2_wx_fwex_desc_adv_status_ewwow_0_qw0_bits {
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_WPBK_M		= BIT(0),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_IPV6EXADD_M		= BIT(1),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_WXE_M		= BIT(2),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_CWCP_M		= BIT(3),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_WSS_VAWID_M		= BIT(4),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_W2TAG1P_M		= BIT(5),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XTWMD0_VAWID_M	= BIT(6),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XTWMD1_VAWID_M	= BIT(7),
};

/* Bitmasks fow spwitq viwtchnw2_wx_fwex_desc_adv_nic_3 */
enum viwtchnw2_wx_fwex_desc_adv_status_ewwow_1_bits {
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_WSVD_M		= GENMASK(1, 0),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_ATWAEFAIW_M		= BIT(2),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_W2TAG2P_M		= BIT(3),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_XTWMD2_VAWID_M	= BIT(4),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_XTWMD3_VAWID_M	= BIT(5),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_XTWMD4_VAWID_M	= BIT(6),
	VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS1_XTWMD5_VAWID_M	= BIT(7),
};

/* Fow singweq (fwex) viwtchnw2_wx_fwex_desc fiewds
 * Fow viwtchnw2_wx_fwex_desc.ptype_fwex_fwags0 membew
 */
#define VIWTCHNW2_WX_FWEX_DESC_PTYPE_M				GENMASK(9, 0)

/* Fow viwtchnw2_wx_fwex_desc.pkt_wen membew */
#define VIWTCHNW2_WX_FWEX_DESC_PKT_WEN_M			GENMASK(13, 0)

/* Bitmasks fow singweq (fwex) viwtchnw2_wx_fwex_desc */
enum viwtchnw2_wx_fwex_desc_status_ewwow_0_bits {
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_DD_M			= BIT(0),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_EOF_M			= BIT(1),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_HBO_M			= BIT(2),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_W3W4P_M			= BIT(3),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XSUM_IPE_M		= BIT(4),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XSUM_W4E_M		= BIT(5),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XSUM_EIPE_M		= BIT(6),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XSUM_EUDPE_M		= BIT(7),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_WPBK_M			= BIT(8),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_IPV6EXADD_M		= BIT(9),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_WXE_M			= BIT(10),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_CWCP_M			= BIT(11),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_WSS_VAWID_M		= BIT(12),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_W2TAG1P_M		= BIT(13),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XTWMD0_VAWID_M		= BIT(14),
	VIWTCHNW2_WX_FWEX_DESC_STATUS0_XTWMD1_VAWID_M		= BIT(15),
};

/* Bitmasks fow singweq (fwex) viwtchnw2_wx_fwex_desc */
enum viwtchnw2_wx_fwex_desc_status_ewwow_1_bits {
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_CPM_M			= GENMASK(3, 0),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_NAT_M			= BIT(4),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_CWYPTO_M			= BIT(5),
	/* [10:6] wesewved */
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_W2TAG2P_M		= BIT(11),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_XTWMD2_VAWID_M		= BIT(12),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_XTWMD3_VAWID_M		= BIT(13),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_XTWMD4_VAWID_M		= BIT(14),
	VIWTCHNW2_WX_FWEX_DESC_STATUS1_XTWMD5_VAWID_M		= BIT(15),
};

/* Fow viwtchnw2_wx_fwex_desc.ts_wow membew */
#define VIWTCHNW2_WX_FWEX_TSTAMP_VAWID				BIT(0)

/* Fow singweq (non fwex) viwtchnw2_singweq_base_wx_desc wegacy desc membews */
#define VIWTCHNW2_WX_BASE_DESC_QW1_WEN_PBUF_M		GENMASK_UWW(51, 38)
#define VIWTCHNW2_WX_BASE_DESC_QW1_PTYPE_M		GENMASK_UWW(37, 30)
#define VIWTCHNW2_WX_BASE_DESC_QW1_EWWOW_M		GENMASK_UWW(26, 19)
#define VIWTCHNW2_WX_BASE_DESC_QW1_STATUS_M		GENMASK_UWW(18, 0)

/* Bitmasks fow singweq (base) viwtchnw2_wx_base_desc */
enum viwtchnw2_wx_base_desc_status_bits {
	VIWTCHNW2_WX_BASE_DESC_STATUS_DD_M		= BIT(0),
	VIWTCHNW2_WX_BASE_DESC_STATUS_EOF_M		= BIT(1),
	VIWTCHNW2_WX_BASE_DESC_STATUS_W2TAG1P_M		= BIT(2),
	VIWTCHNW2_WX_BASE_DESC_STATUS_W3W4P_M		= BIT(3),
	VIWTCHNW2_WX_BASE_DESC_STATUS_CWCP_M		= BIT(4),
	VIWTCHNW2_WX_BASE_DESC_STATUS_WSVD_M		= GENMASK(7, 5),
	VIWTCHNW2_WX_BASE_DESC_STATUS_EXT_UDP_0_M	= BIT(8),
	VIWTCHNW2_WX_BASE_DESC_STATUS_UMBCAST_M		= GENMASK(10, 9),
	VIWTCHNW2_WX_BASE_DESC_STATUS_FWM_M		= BIT(11),
	VIWTCHNW2_WX_BASE_DESC_STATUS_FWTSTAT_M		= GENMASK(13, 12),
	VIWTCHNW2_WX_BASE_DESC_STATUS_WPBK_M		= BIT(14),
	VIWTCHNW2_WX_BASE_DESC_STATUS_IPV6EXADD_M	= BIT(15),
	VIWTCHNW2_WX_BASE_DESC_STATUS_WSVD1_M		= GENMASK(17, 16),
	VIWTCHNW2_WX_BASE_DESC_STATUS_INT_UDP_0_M	= BIT(18),
};

/* Bitmasks fow singweq (base) viwtchnw2_wx_base_desc */
enum viwtchnw2_wx_base_desc_ewwow_bits {
	VIWTCHNW2_WX_BASE_DESC_EWWOW_WXE_M		= BIT(0),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_ATWAEFAIW_M	= BIT(1),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_HBO_M		= BIT(2),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_W3W4E_M		= GENMASK(5, 3),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_IPE_M		= BIT(3),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_W4E_M		= BIT(4),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_EIPE_M		= BIT(5),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_OVEWSIZE_M		= BIT(6),
	VIWTCHNW2_WX_BASE_DESC_EWWOW_PPWS_M		= BIT(7),
};

/* Bitmasks fow singweq (base) viwtchnw2_wx_base_desc */
#define VIWTCHNW2_WX_BASE_DESC_FWTSTAT_WSS_HASH_M	GENMASK(13, 12)

/**
 * stwuct viwtchnw2_spwitq_wx_buf_desc - SpwitQ WX buffew descwiptow fowmat
 * @qwowd0: WX buffew stwuct.
 * @qwowd0.buf_id: Buffew identifiew.
 * @qwowd0.wsvd0: Wesewved.
 * @qwowd0.wsvd1: Wesewved.
 * @pkt_addw: Packet buffew addwess.
 * @hdw_addw: Headew buffew addwess.
 * @wsvd2: Wewsewved.
 *
 * Weceive Descwiptows
 * SpwitQ buffew
 * |                                       16|                   0|
 * ----------------------------------------------------------------
 * | WSV                                     | Buffew ID          |
 * ----------------------------------------------------------------
 * | Wx packet buffew addwess                                     |
 * ----------------------------------------------------------------
 * | Wx headew buffew addwess                                     |
 * ----------------------------------------------------------------
 * | WSV                                                          |
 * ----------------------------------------------------------------
 * |                                                             0|
 */
stwuct viwtchnw2_spwitq_wx_buf_desc {
	stwuct {
		__we16  buf_id;
		__we16  wsvd0;
		__we32  wsvd1;
	} qwowd0;
	__we64  pkt_addw;
	__we64  hdw_addw;
	__we64  wsvd2;
};

/**
 * stwuct viwtchnw2_singweq_wx_buf_desc - SingweQ WX buffew descwiptow fowmat.
 * @pkt_addw: Packet buffew addwess.
 * @hdw_addw: Headew buffew addwess.
 * @wsvd1: Wesewved.
 * @wsvd2: Wesewved.
 *
 * SingweQ buffew
 * |                                                             0|
 * ----------------------------------------------------------------
 * | Wx packet buffew addwess                                     |
 * ----------------------------------------------------------------
 * | Wx headew buffew addwess                                     |
 * ----------------------------------------------------------------
 * | WSV                                                          |
 * ----------------------------------------------------------------
 * | WSV                                                          |
 * ----------------------------------------------------------------
 * |                                                             0|
 */
stwuct viwtchnw2_singweq_wx_buf_desc {
	__we64  pkt_addw;
	__we64  hdw_addw;
	__we64  wsvd1;
	__we64  wsvd2;
};

/**
 * stwuct viwtchnw2_singweq_base_wx_desc - WX descwiptow wwiteback fowmat.
 * @qwowd0: Fiwst quad wowd stwuct.
 * @qwowd0.wo_dwowd: Wowew duaw wowd stwuct.
 * @qwowd0.wo_dwowd.miwwowing_status: Miwwowed packet status.
 * @qwowd0.wo_dwowd.w2tag1: Stwipped W2 tag fwom the weceived packet.
 * @qwowd0.hi_dwowd: High duaw wowd union.
 * @qwowd0.hi_dwowd.wss: WSS hash.
 * @qwowd0.hi_dwowd.fd_id: Fwow diwectow fiwtew id.
 * @qwowd1: Second quad wowd stwuct.
 * @qwowd1.status_ewwow_ptype_wen: Status/ewwow/PTYPE/wength.
 * @qwowd2: Thiwd quad wowd stwuct.
 * @qwowd2.ext_status: Extended status.
 * @qwowd2.wsvd: Wesewved.
 * @qwowd2.w2tag2_1: Extwacted W2 tag 2 fwom the packet.
 * @qwowd2.w2tag2_2: Wesewved.
 * @qwowd3: Fouwth quad wowd stwuct.
 * @qwowd3.wesewved: Wesewved.
 * @qwowd3.fd_id: Fwow diwectow fiwtew id.
 *
 * Pwofiwe ID 0x1, SingweQ, base wwiteback fowmat
 */
stwuct viwtchnw2_singweq_base_wx_desc {
	stwuct {
		stwuct {
			__we16 miwwowing_status;
			__we16 w2tag1;
		} wo_dwowd;
		union {
			__we32 wss;
			__we32 fd_id;
		} hi_dwowd;
	} qwowd0;
	stwuct {
		__we64 status_ewwow_ptype_wen;
	} qwowd1;
	stwuct {
		__we16 ext_status;
		__we16 wsvd;
		__we16 w2tag2_1;
		__we16 w2tag2_2;
	} qwowd2;
	stwuct {
		__we32 wesewved;
		__we32 fd_id;
	} qwowd3;
};

/**
 * stwuct viwtchnw2_wx_fwex_desc_nic - WX descwiptow wwiteback fowmat.
 *
 * @wxdid: Descwiptow buiwdew pwofiwe id.
 * @miw_id_umb_cast: umb_cast=[7:6], miwwow=[5:0]
 * @ptype_fwex_fwags0: ff0=[15:10], ptype=[9:0]
 * @pkt_wen: Packet wength, [15:14] awe wesewved.
 * @hdw_wen_sph_fwex_fwags1: ff1/ext=[15:12], sph=[11], headew=[10:0].
 * @status_ewwow0: Status/Ewwow section 0.
 * @w2tag1: Stwipped W2 tag fwom the weceived packet
 * @wss_hash: WSS hash.
 * @status_ewwow1: Status/Ewwow section 1.
 * @fwexi_fwags2: Fwexibwe fwags section 2.
 * @ts_wow: Wowew wowd of timestamp vawue.
 * @w2tag2_1st: Fiwst W2TAG2.
 * @w2tag2_2nd: Second W2TAG2.
 * @fwow_id: Fwow id.
 * @fwex_ts: Timestamp and fwexibwe fwow id union.
 * @fwex_ts.ts_high: Timestamp highew wowd of the timestamp vawue.
 * @fwex_ts.fwex.wsvd: Wesewved.
 * @fwex_ts.fwex.fwow_id_ipv6: IPv6 fwow id.
 *
 * Pwofiwe ID 0x2, SingweQ, fwex wwiteback fowmat
 */
stwuct viwtchnw2_wx_fwex_desc_nic {
	/* Qwowd 0 */
	u8 wxdid;
	u8 miw_id_umb_cast;
	__we16 ptype_fwex_fwags0;
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
			__we16 wsvd;
			__we16 fwow_id_ipv6;
		} fwex;
		__we32 ts_high;
	} fwex_ts;
};

/**
 * stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 - WX descwiptow wwiteback fowmat.
 * @wxdid_ucast: ucast=[7:6], wsvd=[5:4], pwofiwe_id=[3:0].
 * @status_eww0_qw0: Status/Ewwow section 0 in quad wowd 0.
 * @ptype_eww_ffwags0: ff0=[15:12], udp_wen_eww=[11], ip_hdw_eww=[10],
 *		       ptype=[9:0].
 * @pktwen_gen_bufq_id: bufq_id=[15] onwy in spwitq, gen=[14] onwy in spwitq,
 *			pwen=[13:0].
 * @hdwwen_fwags: miss_pwepend=[15], twunc_miww=[14], int_udp_0=[13],
 *		  ext_udp0=[12], sph=[11] onwy in spwitq, wsc=[10]
 *		  onwy in spwitq, headew=[9:0].
 * @status_eww0_qw1: Status/Ewwow section 0 in quad wowd 1.
 * @status_eww1: Status/Ewwow section 1.
 * @ffwags1: Fwexibwe fwags section 1.
 * @ts_wow: Wowew wowd of timestamp vawue.
 * @buf_id: Buffew identifiew. Onwy in spwitq mode.
 * @misc: Union.
 * @misc.waw_cs: Waw checksum.
 * @misc.w2tag1: Stwipped W2 tag fwom the weceived packet
 * @misc.wscsegwen:
 * @hash1: Wowew bits of Wx hash vawue.
 * @ff2_miwwid_hash2: Union.
 * @ff2_miwwid_hash2.ffwags2: Fwexibwe fwags section 2.
 * @ff2_miwwid_hash2.miwwowid: Miwwow id.
 * @ff2_miwwid_hash2.wscsegwen: WSC segment wength.
 * @hash3: Uppew bits of Wx hash vawue.
 * @w2tag2: Extwacted W2 tag 2 fwom the packet.
 * @fmd4: Fwexibwe metadata containew 4.
 * @w2tag1: Stwipped W2 tag fwom the weceived packet
 * @fmd6: Fwexibwe metadata containew 6.
 * @ts_high: Timestamp highew wowd of the timestamp vawue.
 *
 * Pwofiwe ID 0x2, SpwitQ, fwex wwiteback fowmat
 *
 * Fwex-fiewd 0: BuffewID
 * Fwex-fiewd 1: Waw checksum/W2TAG1/WSC Seg Wen (detewmined by HW)
 * Fwex-fiewd 2: Hash[15:0]
 * Fwex-fwags 2: Hash[23:16]
 * Fwex-fiewd 3: W2TAG2
 * Fwex-fiewd 5: W2TAG1
 * Fwex-fiewd 7: Timestamp (uppew 32 bits)
 */
stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 {
	/* Qwowd 0 */
	u8 wxdid_ucast;
	u8 status_eww0_qw0;
	__we16 ptype_eww_ffwags0;
	__we16 pktwen_gen_bufq_id;
	__we16 hdwwen_fwags;
	/* Qwowd 1 */
	u8 status_eww0_qw1;
	u8 status_eww1;
	u8 ffwags1;
	u8 ts_wow;
	__we16 buf_id;
	union {
		__we16 waw_cs;
		__we16 w2tag1;
		__we16 wscsegwen;
	} misc;
	/* Qwowd 2 */
	__we16 hash1;
	union {
		u8 ffwags2;
		u8 miwwowid;
		u8 hash2;
	} ff2_miwwid_hash2;
	u8 hash3;
	__we16 w2tag2;
	__we16 fmd4;
	/* Qwowd 3 */
	__we16 w2tag1;
	__we16 fmd6;
	__we32 ts_high;
};

/* Common union fow accessing descwiptow fowmat stwucts */
union viwtchnw2_wx_desc {
	stwuct viwtchnw2_singweq_base_wx_desc		base_wb;
	stwuct viwtchnw2_wx_fwex_desc_nic		fwex_nic_wb;
	stwuct viwtchnw2_wx_fwex_desc_adv_nic_3		fwex_adv_nic_3_wb;
};

#endif /* _VIWTCHNW_WAN_DESC_H_ */
