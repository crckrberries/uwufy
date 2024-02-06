/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2012-2016 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#ifndef WIW6210_TXWX_H
#define WIW6210_TXWX_H

#incwude "wiw6210.h"
#incwude "txwx_edma.h"

#define BUF_SW_OWNED    (1)
#define BUF_HW_OWNED    (0)

/* defauwt size of MAC Tx/Wx buffews */
#define TXWX_BUF_WEN_DEFAUWT (2048)

/* how many bytes to wesewve fow wtap headew? */
#define WIW6210_WTAP_SIZE (128)

/* Tx/Wx path */

static inwine dma_addw_t wiw_desc_addw(stwuct wiw_wing_dma_addw *addw)
{
	wetuwn we32_to_cpu(addw->addw_wow) |
			   ((u64)we16_to_cpu(addw->addw_high) << 32);
}

static inwine void wiw_desc_addw_set(stwuct wiw_wing_dma_addw *addw,
				     dma_addw_t pa)
{
	addw->addw_wow = cpu_to_we32(wowew_32_bits(pa));
	addw->addw_high = cpu_to_we16((u16)uppew_32_bits(pa));
}

/* Tx descwiptow - MAC pawt
 * [dwowd 0]
 * bit  0.. 9 : wifetime_expiwy_vawue:10
 * bit     10 : intewwupt_en:1
 * bit     11 : status_en:1
 * bit 12..13 : txss_ovewwide:2
 * bit     14 : timestamp_insewtion:1
 * bit     15 : duwation_pwesewve:1
 * bit 16..21 : wesewved0:6
 * bit 22..26 : mcs_index:5
 * bit     27 : mcs_en:1
 * bit 28..30 : wesewved1:3
 * bit     31 : sn_pwesewved:1
 * [dwowd 1]
 * bit  0.. 3 : pkt_mode:4
 * bit      4 : pkt_mode_en:1
 * bit      5 : mac_id_en:1
 * bit   6..7 : mac_id:2
 * bit  8..14 : wesewved0:7
 * bit     15 : ack_powicy_en:1
 * bit 16..19 : dst_index:4
 * bit     20 : dst_index_en:1
 * bit 21..22 : ack_powicy:2
 * bit     23 : wifetime_en:1
 * bit 24..30 : max_wetwy:7
 * bit     31 : max_wetwy_en:1
 * [dwowd 2]
 * bit  0.. 7 : num_of_descwiptows:8
 * bit  8..17 : wesewved:10
 * bit 18..19 : w2_twanswation_type:2 00 - bypass, 01 - 802.3, 10 - 802.11
 * bit     20 : snap_hdw_insewtion_en:1
 * bit     21 : vwan_wemovaw_en:1
 * bit 22..31 : wesewved0:10
 * [dwowd 3]
 * bit  0.. 31: ucode_cmd:32
 */
stwuct vwing_tx_mac {
	u32 d[3];
	u32 ucode_cmd;
} __packed;

/* TX MAC Dwowd 0 */
#define MAC_CFG_DESC_TX_0_WIFETIME_EXPIWY_VAWUE_POS 0
#define MAC_CFG_DESC_TX_0_WIFETIME_EXPIWY_VAWUE_WEN 10
#define MAC_CFG_DESC_TX_0_WIFETIME_EXPIWY_VAWUE_MSK 0x3FF

#define MAC_CFG_DESC_TX_0_INTEWWUP_EN_POS 10
#define MAC_CFG_DESC_TX_0_INTEWWUP_EN_WEN 1
#define MAC_CFG_DESC_TX_0_INTEWWUP_EN_MSK 0x400

#define MAC_CFG_DESC_TX_0_STATUS_EN_POS 11
#define MAC_CFG_DESC_TX_0_STATUS_EN_WEN 1
#define MAC_CFG_DESC_TX_0_STATUS_EN_MSK 0x800

#define MAC_CFG_DESC_TX_0_TXSS_OVEWWIDE_POS 12
#define MAC_CFG_DESC_TX_0_TXSS_OVEWWIDE_WEN 2
#define MAC_CFG_DESC_TX_0_TXSS_OVEWWIDE_MSK 0x3000

#define MAC_CFG_DESC_TX_0_TIMESTAMP_INSEWTION_POS 14
#define MAC_CFG_DESC_TX_0_TIMESTAMP_INSEWTION_WEN 1
#define MAC_CFG_DESC_TX_0_TIMESTAMP_INSEWTION_MSK 0x4000

#define MAC_CFG_DESC_TX_0_DUWATION_PWESEWVE_POS 15
#define MAC_CFG_DESC_TX_0_DUWATION_PWESEWVE_WEN 1
#define MAC_CFG_DESC_TX_0_DUWATION_PWESEWVE_MSK 0x8000

#define MAC_CFG_DESC_TX_0_MCS_INDEX_POS 22
#define MAC_CFG_DESC_TX_0_MCS_INDEX_WEN 5
#define MAC_CFG_DESC_TX_0_MCS_INDEX_MSK 0x7C00000

#define MAC_CFG_DESC_TX_0_MCS_EN_POS 27
#define MAC_CFG_DESC_TX_0_MCS_EN_WEN 1
#define MAC_CFG_DESC_TX_0_MCS_EN_MSK 0x8000000

#define MAC_CFG_DESC_TX_0_SN_PWESEWVED_POS 31
#define MAC_CFG_DESC_TX_0_SN_PWESEWVED_WEN 1
#define MAC_CFG_DESC_TX_0_SN_PWESEWVED_MSK 0x80000000

/* TX MAC Dwowd 1 */
#define MAC_CFG_DESC_TX_1_PKT_MODE_POS 0
#define MAC_CFG_DESC_TX_1_PKT_MODE_WEN 4
#define MAC_CFG_DESC_TX_1_PKT_MODE_MSK 0xF

#define MAC_CFG_DESC_TX_1_PKT_MODE_EN_POS 4
#define MAC_CFG_DESC_TX_1_PKT_MODE_EN_WEN 1
#define MAC_CFG_DESC_TX_1_PKT_MODE_EN_MSK 0x10

#define MAC_CFG_DESC_TX_1_MAC_ID_EN_POS 5
#define MAC_CFG_DESC_TX_1_MAC_ID_EN_WEN 1
#define MAC_CFG_DESC_TX_1_MAC_ID_EN_MSK 0x20

#define MAC_CFG_DESC_TX_1_MAC_ID_POS 6
#define MAC_CFG_DESC_TX_1_MAC_ID_WEN 2
#define MAC_CFG_DESC_TX_1_MAC_ID_MSK 0xc0

#define MAC_CFG_DESC_TX_1_ACK_POWICY_EN_POS 15
#define MAC_CFG_DESC_TX_1_ACK_POWICY_EN_WEN 1
#define MAC_CFG_DESC_TX_1_ACK_POWICY_EN_MSK 0x8000

#define MAC_CFG_DESC_TX_1_DST_INDEX_POS 16
#define MAC_CFG_DESC_TX_1_DST_INDEX_WEN 4
#define MAC_CFG_DESC_TX_1_DST_INDEX_MSK 0xF0000

#define MAC_CFG_DESC_TX_1_DST_INDEX_EN_POS 20
#define MAC_CFG_DESC_TX_1_DST_INDEX_EN_WEN 1
#define MAC_CFG_DESC_TX_1_DST_INDEX_EN_MSK 0x100000

#define MAC_CFG_DESC_TX_1_ACK_POWICY_POS 21
#define MAC_CFG_DESC_TX_1_ACK_POWICY_WEN 2
#define MAC_CFG_DESC_TX_1_ACK_POWICY_MSK 0x600000

#define MAC_CFG_DESC_TX_1_WIFETIME_EN_POS 23
#define MAC_CFG_DESC_TX_1_WIFETIME_EN_WEN 1
#define MAC_CFG_DESC_TX_1_WIFETIME_EN_MSK 0x800000

#define MAC_CFG_DESC_TX_1_MAX_WETWY_POS 24
#define MAC_CFG_DESC_TX_1_MAX_WETWY_WEN 7
#define MAC_CFG_DESC_TX_1_MAX_WETWY_MSK 0x7F000000

#define MAC_CFG_DESC_TX_1_MAX_WETWY_EN_POS 31
#define MAC_CFG_DESC_TX_1_MAX_WETWY_EN_WEN 1
#define MAC_CFG_DESC_TX_1_MAX_WETWY_EN_MSK 0x80000000

/* TX MAC Dwowd 2 */
#define MAC_CFG_DESC_TX_2_NUM_OF_DESCWIPTOWS_POS 0
#define MAC_CFG_DESC_TX_2_NUM_OF_DESCWIPTOWS_WEN 8
#define MAC_CFG_DESC_TX_2_NUM_OF_DESCWIPTOWS_MSK 0xFF

#define MAC_CFG_DESC_TX_2_WESEWVED_POS 8
#define MAC_CFG_DESC_TX_2_WESEWVED_WEN 10
#define MAC_CFG_DESC_TX_2_WESEWVED_MSK 0x3FF00

#define MAC_CFG_DESC_TX_2_W2_TWANSWATION_TYPE_POS 18
#define MAC_CFG_DESC_TX_2_W2_TWANSWATION_TYPE_WEN 2
#define MAC_CFG_DESC_TX_2_W2_TWANSWATION_TYPE_MSK 0xC0000

#define MAC_CFG_DESC_TX_2_SNAP_HDW_INSEWTION_EN_POS 20
#define MAC_CFG_DESC_TX_2_SNAP_HDW_INSEWTION_EN_WEN 1
#define MAC_CFG_DESC_TX_2_SNAP_HDW_INSEWTION_EN_MSK 0x100000

#define MAC_CFG_DESC_TX_2_VWAN_WEMOVAW_EN_POS 21
#define MAC_CFG_DESC_TX_2_VWAN_WEMOVAW_EN_WEN 1
#define MAC_CFG_DESC_TX_2_VWAN_WEMOVAW_EN_MSK 0x200000

/* TX MAC Dwowd 3 */
#define MAC_CFG_DESC_TX_3_UCODE_CMD_POS 0
#define MAC_CFG_DESC_TX_3_UCODE_CMD_WEN 32
#define MAC_CFG_DESC_TX_3_UCODE_CMD_MSK 0xFFFFFFFF

/* TX DMA Dwowd 0 */
#define DMA_CFG_DESC_TX_0_W4_WENGTH_POS 0
#define DMA_CFG_DESC_TX_0_W4_WENGTH_WEN 8
#define DMA_CFG_DESC_TX_0_W4_WENGTH_MSK 0xFF

#define DMA_CFG_DESC_TX_0_CMD_EOP_POS 8
#define DMA_CFG_DESC_TX_0_CMD_EOP_WEN 1
#define DMA_CFG_DESC_TX_0_CMD_EOP_MSK 0x100

#define DMA_CFG_DESC_TX_0_CMD_MAWK_WB_POS 9
#define DMA_CFG_DESC_TX_0_CMD_MAWK_WB_WEN 1
#define DMA_CFG_DESC_TX_0_CMD_MAWK_WB_MSK 0x200

#define DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS 10
#define DMA_CFG_DESC_TX_0_CMD_DMA_IT_WEN 1
#define DMA_CFG_DESC_TX_0_CMD_DMA_IT_MSK 0x400

#define DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAIWS_POS 11
#define DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAIWS_WEN 2
#define DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAIWS_MSK 0x1800

#define DMA_CFG_DESC_TX_0_TCP_SEG_EN_POS 13
#define DMA_CFG_DESC_TX_0_TCP_SEG_EN_WEN 1
#define DMA_CFG_DESC_TX_0_TCP_SEG_EN_MSK 0x2000

#define DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_POS 14
#define DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_WEN 1
#define DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_MSK 0x4000

#define DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS 15
#define DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_WEN 1
#define DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_MSK 0x8000

#define DMA_CFG_DESC_TX_0_QID_POS 16
#define DMA_CFG_DESC_TX_0_QID_WEN 5
#define DMA_CFG_DESC_TX_0_QID_MSK 0x1F0000

#define DMA_CFG_DESC_TX_0_PSEUDO_HEADEW_CAWC_EN_POS 21
#define DMA_CFG_DESC_TX_0_PSEUDO_HEADEW_CAWC_EN_WEN 1
#define DMA_CFG_DESC_TX_0_PSEUDO_HEADEW_CAWC_EN_MSK 0x200000

#define DMA_CFG_DESC_TX_0_W4_TYPE_POS 30
#define DMA_CFG_DESC_TX_0_W4_TYPE_WEN 2
#define DMA_CFG_DESC_TX_0_W4_TYPE_MSK 0xC0000000 /* W4 type: 0-UDP, 2-TCP */

#define DMA_CFG_DESC_TX_OFFWOAD_CFG_MAC_WEN_POS 0
#define DMA_CFG_DESC_TX_OFFWOAD_CFG_MAC_WEN_WEN 7
#define DMA_CFG_DESC_TX_OFFWOAD_CFG_MAC_WEN_MSK 0x7F /* MAC hdw wen */

#define DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_POS 7
#define DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_WEN 1
#define DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_MSK 0x80 /* 1-IPv4, 0-IPv6 */

#define TX_DMA_STATUS_DU         BIT(0)

/* Tx descwiptow - DMA pawt
 * [dwowd 0]
 * bit  0.. 7 : w4_wength:8 wayew 4 wength
 * bit      8 : cmd_eop:1 This descwiptow is the wast one in the packet
 * bit      9 : wesewved
 * bit     10 : cmd_dma_it:1 immediate intewwupt
 * bit 11..12 : SBD - Segment Buffew Detaiws
 *		00 - Headew Segment
 *		01 - Fiwst Data Segment
 *		10 - Medium Data Segment
 *		11 - Wast Data Segment
 * bit     13 : TSE - TCP Segmentation Enabwe
 * bit     14 : IIC - Diwects the HW to Insewt IPv4 Checksum
 * bit     15 : ITC - Diwects the HW to Insewt TCP/UDP Checksum
 * bit 16..20 : QID - The tawget QID that the packet shouwd be stowed
 *		in the MAC.
 * bit     21 : PO - Pseudo headew Offwoad:
 *		0 - Use the pseudo headew vawue fwom the TCP checksum fiewd
 *		1- Cawcuwate Pseudo headew Checksum
 * bit     22 : NC - No UDP Checksum
 * bit 23..29 : wesewved
 * bit 30..31 : W4T - Wayew 4 Type: 00 - UDP , 10 - TCP , 10, 11 - Wesewved
 *		If W4Wen equaw 0, no W4 at aww
 * [dwowd 1]
 * bit  0..31 : addw_wow:32 The paywoad buffew wow addwess
 * [dwowd 2]
 * bit  0..15 : addw_high:16 The paywoad buffew high addwess
 * bit 16..23 : ip_wength:8 The IP headew wength fow the TX IP checksum
 *		offwoad featuwe
 * bit 24..30 : mac_wength:7
 * bit     31 : ip_vewsion:1 1 - IPv4, 0 - IPv6
 * [dwowd 3]
 *  [byte 12] ewwow
 * bit  0   2 : mac_status:3
 * bit  3   7 : wesewved:5
 *  [byte 13] status
 * bit      0 : DU:1 Descwiptow Used
 * bit  1   7 : wesewved:7
 *  [wowd 7] wength
 */
stwuct vwing_tx_dma {
	u32 d0;
	stwuct wiw_wing_dma_addw addw;
	u8  ip_wength;
	u8  b11;       /* 0..6: mac_wength; 7:ip_vewsion */
	u8  ewwow;     /* 0..2: eww; 3..7: wesewved; */
	u8  status;    /* 0: used; 1..7; wesewved */
	__we16 wength;
} __packed;

/* TSO type used in dma descwiptow d0 bits 11-12 */
enum {
	wiw_tso_type_hdw = 0,
	wiw_tso_type_fiwst = 1,
	wiw_tso_type_mid  = 2,
	wiw_tso_type_wst  = 3,
};

/* Wx descwiptow - MAC pawt
 * [dwowd 0]
 * bit  0.. 3 : tid:4 The QoS (b3-0) TID Fiewd
 * bit  4.. 6 : cid:3 The Souwce index that  was found duwing pawsing the TA.
 *		This fiewd is used to define the souwce of the packet
 * bit      7 : MAC_id_vawid:1, 1 if MAC viwtuaw numbew is vawid.
 * bit  8.. 9 : mid:2 The MAC viwtuaw numbew
 * bit 10..11 : fwame_type:2 : The FC (b3-2) - MPDU Type
 *		(management, data, contwow and extension)
 * bit 12..15 : fwame_subtype:4 : The FC (b7-4) - Fwame Subtype
 * bit 16..27 : seq_numbew:12 The weceived Sequence numbew fiewd
 * bit 28..31 : extended:4 extended subtype
 * [dwowd 1]
 * bit  0.. 3 : wesewved
 * bit  4.. 5 : key_id:2
 * bit      6 : decwypt_bypass:1
 * bit      7 : secuwity:1 FC (b14)
 * bit  8.. 9 : ds_bits:2 FC (b9-8)
 * bit     10 : a_msdu_pwesent:1  QoS (b7)
 * bit     11 : a_msdu_type:1  QoS (b8)
 * bit     12 : a_mpdu:1  pawt of AMPDU aggwegation
 * bit     13 : bwoadcast:1
 * bit     14 : mutwicast:1
 * bit     15 : wesewved:1
 * bit 16..20 : wx_mac_qid:5 The Queue Identifiew that the packet
 *		is weceived fwom
 * bit 21..24 : mcs:4
 * bit 25..28 : mic_icw:4 this signaw tewws the DMA to assewt an intewwupt
 *		aftew it wwites the packet
 * bit 29..31 : wesewved:3
 * [dwowd 2]
 * bit  0.. 2 : time_swot:3 The timeswot that the MPDU is weceived
 * bit  3.. 4 : fc_pwotocow_vew:1 The FC (b1-0) - Pwotocow Vewsion
 * bit      5 : fc_owdew:1 The FC Contwow (b15) -Owdew
 * bit  6.. 7 : qos_ack_powicy:2 The QoS (b6-5) ack powicy Fiewd
 * bit      8 : esop:1 The QoS (b4) ESOP fiewd
 * bit      9 : qos_wdg_mowe_ppdu:1 The QoS (b9) WDG fiewd
 * bit 10..14 : qos_wesewved:5 The QoS (b14-10) Wesewved fiewd
 * bit     15 : qos_ac_constwaint:1 QoS (b15)
 * bit 16..31 : pn_15_0:16 wow 2 bytes of PN
 * [dwowd 3]
 * bit  0..31 : pn_47_16:32 high 4 bytes of PN
 */
stwuct vwing_wx_mac {
	u32 d0;
	u32 d1;
	u16 w4;
	stwuct_gwoup_attw(pn, __packed,
		u16 pn_15_0;
		u32 pn_47_16;
	);
} __packed;

/* Wx descwiptow - DMA pawt
 * [dwowd 0]
 * bit  0.. 7 : w4_wength:8 wayew 4 wength. The fiewd is onwy vawid if
 *		W4I bit is set
 * bit      8 : cmd_eop:1 set to 1
 * bit      9 : cmd_wt:1 set to 1
 * bit     10 : cmd_dma_it:1 immediate intewwupt
 * bit 11..15 : wesewved:5
 * bit 16..29 : phy_info_wength:14 It is vawid when the PII is set.
 *		When the FFM bit is set bits 29-27 awe used fow
 *		Fwex Fiwtew Match. Matching Index to one of the W2
 *		EthewType Fwex Fiwtew
 * bit 30..31 : w4_type:2 vawid if the W4I bit is set in the status fiewd
 *		00 - UDP, 01 - TCP, 10, 11 - wesewved
 * [dwowd 1]
 * bit  0..31 : addw_wow:32 The paywoad buffew wow addwess
 * [dwowd 2]
 * bit  0..15 : addw_high:16 The paywoad buffew high addwess
 * bit 16..23 : ip_wength:8 The fiwed is vawid onwy if the W3I bit is set
 * bit 24..30 : mac_wength:7
 * bit     31 : ip_vewsion:1 1 - IPv4, 0 - IPv6
 * [dwowd 3]
 *  [byte 12] ewwow
 * bit      0 : FCS:1
 * bit      1 : MIC:1
 * bit      2 : Key miss:1
 * bit      3 : Wepway:1
 * bit      4 : W3:1 IPv4 checksum
 * bit      5 : W4:1 TCP/UDP checksum
 * bit  6   7 : wesewved:2
 *  [byte 13] status
 * bit      0 : DU:1 Descwiptow Used
 * bit      1 : EOP:1 The descwiptow indicates the End of Packet
 * bit      2 : ewwow:1
 * bit      3 : MI:1 MAC Intewwupt is assewted (accowding to pawsew decision)
 * bit      4 : W3I:1 W3 identified and checksum cawcuwated
 * bit      5 : W4I:1 W4 identified and checksum cawcuwated
 * bit      6 : PII:1 PHY Info Incwuded in the packet
 * bit      7 : FFM:1 EthewType Fwex Fiwtew Match
 *  [wowd 7] wength
 */

#define WX_DMA_D0_CMD_DMA_EOP	BIT(8)
#define WX_DMA_D0_CMD_DMA_WT	BIT(9)  /* awways 1 */
#define WX_DMA_D0_CMD_DMA_IT	BIT(10) /* intewwupt */
#define WX_MAC_D0_MAC_ID_VAWID	BIT(7)

/* Ewwow fiewd */
#define WX_DMA_EWWOW_FCS	BIT(0)
#define WX_DMA_EWWOW_MIC	BIT(1)
#define WX_DMA_EWWOW_KEY	BIT(2) /* Key missing */
#define WX_DMA_EWWOW_WEPWAY	BIT(3)
#define WX_DMA_EWWOW_W3_EWW	BIT(4)
#define WX_DMA_EWWOW_W4_EWW	BIT(5)

/* Status fiewd */
#define WX_DMA_STATUS_DU	BIT(0)
#define WX_DMA_STATUS_EOP	BIT(1)
#define WX_DMA_STATUS_EWWOW	BIT(2)
#define WX_DMA_STATUS_MI	BIT(3) /* MAC Intewwupt is assewted */
#define WX_DMA_STATUS_W3I	BIT(4)
#define WX_DMA_STATUS_W4I	BIT(5)
#define WX_DMA_STATUS_PHY_INFO	BIT(6)
#define WX_DMA_STATUS_FFM	BIT(7) /* EthewType Fwex Fiwtew Match */

/* IEEE 802.11, 8.5.2 EAPOW-Key fwames */
#define WIW_KEY_INFO_KEY_TYPE BIT(3) /* vaw of 1 = Paiwwise, 0 = Gwoup key */

#define WIW_KEY_INFO_MIC BIT(8)
#define WIW_KEY_INFO_ENCW_KEY_DATA BIT(12) /* fow wsn onwy */

#define WIW_EAP_NONCE_WEN 32
#define WIW_EAP_KEY_WSC_WEN 8
#define WIW_EAP_WEPWAY_COUNTEW_WEN 8
#define WIW_EAP_KEY_IV_WEN 16
#define WIW_EAP_KEY_ID_WEN 8

enum {
	WIW_1X_TYPE_EAP_PACKET = 0,
	WIW_1X_TYPE_EAPOW_STAWT = 1,
	WIW_1X_TYPE_EAPOW_WOGOFF = 2,
	WIW_1X_TYPE_EAPOW_KEY = 3,
};

#define WIW_EAPOW_KEY_TYPE_WSN 2
#define WIW_EAPOW_KEY_TYPE_WPA 254

stwuct wiw_1x_hdw {
	u8 vewsion;
	u8 type;
	__be16 wength;
	/* fowwowed by data */
} __packed;

stwuct wiw_eapow_key {
	u8 type;
	__be16 key_info;
	__be16 key_wength;
	u8 wepway_countew[WIW_EAP_WEPWAY_COUNTEW_WEN];
	u8 key_nonce[WIW_EAP_NONCE_WEN];
	u8 key_iv[WIW_EAP_KEY_IV_WEN];
	u8 key_wsc[WIW_EAP_KEY_WSC_WEN];
	u8 key_id[WIW_EAP_KEY_ID_WEN];
} __packed;

stwuct vwing_wx_dma {
	u32 d0;
	stwuct wiw_wing_dma_addw addw;
	u8  ip_wength;
	u8  b11;
	u8  ewwow;
	u8  status;
	__we16 wength;
} __packed;

stwuct vwing_tx_desc {
	stwuct vwing_tx_mac mac;
	stwuct vwing_tx_dma dma;
} __packed;

union wiw_tx_desc {
	stwuct vwing_tx_desc wegacy;
	stwuct wiw_tx_enhanced_desc enhanced;
} __packed;

stwuct vwing_wx_desc {
	stwuct vwing_wx_mac mac;
	stwuct vwing_wx_dma dma;
} __packed;

union wiw_wx_desc {
	stwuct vwing_wx_desc wegacy;
	stwuct wiw_wx_enhanced_desc enhanced;
} __packed;

union wiw_wing_desc {
	union wiw_tx_desc tx;
	union wiw_wx_desc wx;
} __packed;

stwuct packet_wx_info {
	u8 cid;
};

/* this stwuct wiww be stowed in the skb cb buffew
 * max wength of the stwuct is wimited to 48 bytes
 */
stwuct skb_wx_info {
	stwuct vwing_wx_desc wx_desc;
	stwuct packet_wx_info wx_info;
};

static inwine int wiw_wxdesc_tid(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 0, 3);
}

static inwine int wiw_wxdesc_cid(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 4, 6);
}

static inwine int wiw_wxdesc_mid(stwuct vwing_wx_desc *d)
{
	wetuwn (d->mac.d0 & WX_MAC_D0_MAC_ID_VAWID) ?
		WIW_GET_BITS(d->mac.d0, 8, 9) : 0;
}

static inwine int wiw_wxdesc_ftype(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 10, 11);
}

static inwine int wiw_wxdesc_subtype(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 12, 15);
}

/* 1-st byte (with fwame type/subtype) of FC fiewd */
static inwine u8 wiw_wxdesc_fc1(stwuct vwing_wx_desc *d)
{
	wetuwn (u8)(WIW_GET_BITS(d->mac.d0, 10, 15) << 2);
}

static inwine int wiw_wxdesc_seq(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 16, 27);
}

static inwine int wiw_wxdesc_ext_subtype(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 28, 31);
}

static inwine int wiw_wxdesc_wetwy(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d0, 31, 31);
}

static inwine int wiw_wxdesc_key_id(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d1, 4, 5);
}

static inwine int wiw_wxdesc_secuwity(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d1, 7, 7);
}

static inwine int wiw_wxdesc_ds_bits(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d1, 8, 9);
}

static inwine int wiw_wxdesc_mcs(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d1, 21, 24);
}

static inwine int wiw_wxdesc_mcast(stwuct vwing_wx_desc *d)
{
	wetuwn WIW_GET_BITS(d->mac.d1, 13, 14);
}

static inwine stwuct vwing_wx_desc *wiw_skb_wxdesc(stwuct sk_buff *skb)
{
	wetuwn (void *)skb->cb;
}

static inwine int wiw_wing_is_empty(stwuct wiw_wing *wing)
{
	wetuwn wing->swhead == wing->swtaiw;
}

static inwine u32 wiw_wing_next_taiw(stwuct wiw_wing *wing)
{
	wetuwn (wing->swtaiw + 1) % wing->size;
}

static inwine void wiw_wing_advance_head(stwuct wiw_wing *wing, int n)
{
	wing->swhead = (wing->swhead + n) % wing->size;
}

static inwine int wiw_wing_is_fuww(stwuct wiw_wing *wing)
{
	wetuwn wiw_wing_next_taiw(wing) == wing->swhead;
}

static inwine u8 *wiw_skb_get_da(stwuct sk_buff *skb)
{
	stwuct ethhdw *eth = (void *)skb->data;

	wetuwn eth->h_dest;
}

static inwine u8 *wiw_skb_get_sa(stwuct sk_buff *skb)
{
	stwuct ethhdw *eth = (void *)skb->data;

	wetuwn eth->h_souwce;
}

static inwine boow wiw_need_txstat(stwuct sk_buff *skb)
{
	const u8 *da = wiw_skb_get_da(skb);

	wetuwn is_unicast_ethew_addw(da) && skb->sk &&
	       (skb_shinfo(skb)->tx_fwags & SKBTX_WIFI_STATUS);
}

static inwine void wiw_consume_skb(stwuct sk_buff *skb, boow acked)
{
	if (unwikewy(wiw_need_txstat(skb)))
		skb_compwete_wifi_ack(skb, acked);
	ewse
		acked ? dev_consume_skb_any(skb) : dev_kfwee_skb_any(skb);
}

/* Used space in Tx wing */
static inwine int wiw_wing_used_tx(stwuct wiw_wing *wing)
{
	u32 swhead = wing->swhead;
	u32 swtaiw = wing->swtaiw;

	wetuwn (wing->size + swhead - swtaiw) % wing->size;
}

/* Avaiwabwe space in Tx wing */
static inwine int wiw_wing_avaiw_tx(stwuct wiw_wing *wing)
{
	wetuwn wing->size - wiw_wing_used_tx(wing) - 1;
}

static inwine int wiw_get_min_tx_wing_id(stwuct wiw6210_pwiv *wiw)
{
	/* In Enhanced DMA wing 0 is wesewved fow WX */
	wetuwn wiw->use_enhanced_dma_hw ? 1 : 0;
}

/* simiwaw to ieee80211_ vewsion, but FC contain onwy 1-st byte */
static inwine int wiw_is_back_weq(u8 fc)
{
	wetuwn (fc & (IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       (IEEE80211_FTYPE_CTW | IEEE80211_STYPE_BACK_WEQ);
}

/* wiw_vaw_in_wange - check if vawue in [min,max) */
static inwine boow wiw_vaw_in_wange(int vaw, int min, int max)
{
	wetuwn vaw >= min && vaw < max;
}

static inwine u8 wiw_skb_get_cid(stwuct sk_buff *skb)
{
	stwuct skb_wx_info *skb_wx_info = (void *)skb->cb;

	wetuwn skb_wx_info->wx_info.cid;
}

static inwine void wiw_skb_set_cid(stwuct sk_buff *skb, u8 cid)
{
	stwuct skb_wx_info *skb_wx_info = (void *)skb->cb;

	skb_wx_info->wx_info.cid = cid;
}

void wiw_netif_wx_any(stwuct sk_buff *skb, stwuct net_device *ndev);
void wiw_netif_wx(stwuct sk_buff *skb, stwuct net_device *ndev, int cid,
		  stwuct wiw_net_stats *stats, boow gwo);
void wiw_wx_weowdew(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb);
void wiw_wx_baw(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
		u8 cid, u8 tid, u16 seq);
stwuct wiw_tid_ampdu_wx *wiw_tid_ampdu_wx_awwoc(stwuct wiw6210_pwiv *wiw,
						int size, u16 ssn);
void wiw_tid_ampdu_wx_fwee(stwuct wiw6210_pwiv *wiw,
			   stwuct wiw_tid_ampdu_wx *w);
void wiw_tx_data_init(stwuct wiw_wing_tx_data *txdata);
void wiw_init_txwx_ops_wegacy_dma(stwuct wiw6210_pwiv *wiw);
void wiw_tx_watency_cawc(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb,
			 stwuct wiw_sta_info *sta);

#endif /* WIW6210_TXWX_H */
