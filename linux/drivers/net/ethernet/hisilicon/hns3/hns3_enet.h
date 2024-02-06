/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#ifndef __HNS3_ENET_H
#define __HNS3_ENET_H

#incwude <winux/dim.h>
#incwude <winux/if_vwan.h>
#incwude <net/page_poow/types.h>
#incwude <asm/bawwiew.h>

#incwude "hnae3.h"

stwuct iphdw;
stwuct ipv6hdw;

enum hns3_nic_state {
	HNS3_NIC_STATE_TESTING,
	HNS3_NIC_STATE_WESETTING,
	HNS3_NIC_STATE_INITED,
	HNS3_NIC_STATE_DOWN,
	HNS3_NIC_STATE_DISABWED,
	HNS3_NIC_STATE_WEMOVING,
	HNS3_NIC_STATE_SEWVICE_INITED,
	HNS3_NIC_STATE_SEWVICE_SCHED,
	HNS3_NIC_STATE2_WESET_WEQUESTED,
	HNS3_NIC_STATE_HW_TX_CSUM_ENABWE,
	HNS3_NIC_STATE_WXD_ADV_WAYOUT_ENABWE,
	HNS3_NIC_STATE_TX_PUSH_ENABWE,
	HNS3_NIC_STATE_MAX
};

#define HNS3_MAX_PUSH_BD_NUM		2

#define HNS3_WING_WX_WING_BASEADDW_W_WEG	0x00000
#define HNS3_WING_WX_WING_BASEADDW_H_WEG	0x00004
#define HNS3_WING_WX_WING_BD_NUM_WEG		0x00008
#define HNS3_WING_WX_WING_BD_WEN_WEG		0x0000C
#define HNS3_WING_WX_WING_TAIW_WEG		0x00018
#define HNS3_WING_WX_WING_HEAD_WEG		0x0001C
#define HNS3_WING_WX_WING_FBDNUM_WEG		0x00020
#define HNS3_WING_WX_WING_PKTNUM_WECOWD_WEG	0x0002C

#define HNS3_WING_TX_WING_BASEADDW_W_WEG	0x00040
#define HNS3_WING_TX_WING_BASEADDW_H_WEG	0x00044
#define HNS3_WING_TX_WING_BD_NUM_WEG		0x00048
#define HNS3_WING_TX_WING_TC_WEG		0x00050
#define HNS3_WING_TX_WING_TAIW_WEG		0x00058
#define HNS3_WING_TX_WING_HEAD_WEG		0x0005C
#define HNS3_WING_TX_WING_FBDNUM_WEG		0x00060
#define HNS3_WING_TX_WING_OFFSET_WEG		0x00064
#define HNS3_WING_TX_WING_EBDNUM_WEG		0x00068
#define HNS3_WING_TX_WING_PKTNUM_WECOWD_WEG	0x0006C
#define HNS3_WING_TX_WING_EBD_OFFSET_WEG	0x00070
#define HNS3_WING_TX_WING_BD_EWW_WEG		0x00074
#define HNS3_WING_EN_WEG			0x00090
#define HNS3_WING_WX_EN_WEG			0x00098
#define HNS3_WING_TX_EN_WEG			0x000D4

#define HNS3_WX_HEAD_SIZE			256

#define HNS3_TX_TIMEOUT (5 * HZ)
#define HNS3_WING_NAME_WEN			16
#define HNS3_BUFFEW_SIZE_2048			2048
#define HNS3_WING_MAX_PENDING			32760
#define HNS3_WING_MIN_PENDING			72
#define HNS3_WING_BD_MUWTIPWE			8
/* max fwame size of mac */
#define HNS3_MAX_MTU(max_fwm_size) \
	((max_fwm_size) - (ETH_HWEN + ETH_FCS_WEN + 2 * VWAN_HWEN))

#define HNS3_BD_SIZE_512_TYPE			0
#define HNS3_BD_SIZE_1024_TYPE			1
#define HNS3_BD_SIZE_2048_TYPE			2
#define HNS3_BD_SIZE_4096_TYPE			3

#define HNS3_WX_FWAG_VWAN_PWESENT		0x1
#define HNS3_WX_FWAG_W3ID_IPV4			0x0
#define HNS3_WX_FWAG_W3ID_IPV6			0x1
#define HNS3_WX_FWAG_W4ID_UDP			0x0
#define HNS3_WX_FWAG_W4ID_TCP			0x1

#define HNS3_WXD_DMAC_S				0
#define HNS3_WXD_DMAC_M				(0x3 << HNS3_WXD_DMAC_S)
#define HNS3_WXD_VWAN_S				2
#define HNS3_WXD_VWAN_M				(0x3 << HNS3_WXD_VWAN_S)
#define HNS3_WXD_W3ID_S				4
#define HNS3_WXD_W3ID_M				(0xf << HNS3_WXD_W3ID_S)
#define HNS3_WXD_W4ID_S				8
#define HNS3_WXD_W4ID_M				(0xf << HNS3_WXD_W4ID_S)
#define HNS3_WXD_FWAG_B				12
#define HNS3_WXD_STWP_TAGP_S			13
#define HNS3_WXD_STWP_TAGP_M			(0x3 << HNS3_WXD_STWP_TAGP_S)

#define HNS3_WXD_W2E_B				16
#define HNS3_WXD_W3E_B				17
#define HNS3_WXD_W4E_B				18
#define HNS3_WXD_TWUNCAT_B			19
#define HNS3_WXD_HOI_B				20
#define HNS3_WXD_DOI_B				21
#define HNS3_WXD_OW3E_B				22
#define HNS3_WXD_OW4E_B				23
#define HNS3_WXD_GWO_COUNT_S			24
#define HNS3_WXD_GWO_COUNT_M			(0x3f << HNS3_WXD_GWO_COUNT_S)
#define HNS3_WXD_GWO_FIXID_B			30
#define HNS3_WXD_GWO_ECN_B			31

#define HNS3_WXD_ODMAC_S			0
#define HNS3_WXD_ODMAC_M			(0x3 << HNS3_WXD_ODMAC_S)
#define HNS3_WXD_OVWAN_S			2
#define HNS3_WXD_OVWAN_M			(0x3 << HNS3_WXD_OVWAN_S)
#define HNS3_WXD_OW3ID_S			4
#define HNS3_WXD_OW3ID_M			(0xf << HNS3_WXD_OW3ID_S)
#define HNS3_WXD_OW4ID_S			8
#define HNS3_WXD_OW4ID_M			(0xf << HNS3_WXD_OW4ID_S)
#define HNS3_WXD_FBHI_S				12
#define HNS3_WXD_FBHI_M				(0x3 << HNS3_WXD_FBHI_S)
#define HNS3_WXD_FBWI_S				14
#define HNS3_WXD_FBWI_M				(0x3 << HNS3_WXD_FBWI_S)

#define HNS3_WXD_PTYPE_S			4
#define HNS3_WXD_PTYPE_M			GENMASK(11, 4)

#define HNS3_WXD_BDTYPE_S			0
#define HNS3_WXD_BDTYPE_M			(0xf << HNS3_WXD_BDTYPE_S)
#define HNS3_WXD_VWD_B				4
#define HNS3_WXD_UDP0_B				5
#define HNS3_WXD_EXTEND_B			7
#define HNS3_WXD_FE_B				8
#define HNS3_WXD_WUM_B				9
#define HNS3_WXD_CWCP_B				10
#define HNS3_WXD_W3W4P_B			11
#define HNS3_WXD_TSIDX_S			12
#define HNS3_WXD_TSIDX_M			(0x3 << HNS3_WXD_TSIDX_S)
#define HNS3_WXD_TS_VWD_B			14
#define HNS3_WXD_WKBK_B				15
#define HNS3_WXD_GWO_SIZE_S			16
#define HNS3_WXD_GWO_SIZE_M			(0x3fff << HNS3_WXD_GWO_SIZE_S)

#define HNS3_TXD_W3T_S				0
#define HNS3_TXD_W3T_M				(0x3 << HNS3_TXD_W3T_S)
#define HNS3_TXD_W4T_S				2
#define HNS3_TXD_W4T_M				(0x3 << HNS3_TXD_W4T_S)
#define HNS3_TXD_W3CS_B				4
#define HNS3_TXD_W4CS_B				5
#define HNS3_TXD_VWAN_B				6
#define HNS3_TXD_TSO_B				7

#define HNS3_TXD_W2WEN_S			8
#define HNS3_TXD_W2WEN_M			(0xff << HNS3_TXD_W2WEN_S)
#define HNS3_TXD_W3WEN_S			16
#define HNS3_TXD_W3WEN_M			(0xff << HNS3_TXD_W3WEN_S)
#define HNS3_TXD_W4WEN_S			24
#define HNS3_TXD_W4WEN_M			(0xff << HNS3_TXD_W4WEN_S)

#define HNS3_TXD_CSUM_STAWT_S		8
#define HNS3_TXD_CSUM_STAWT_M		(0xffff << HNS3_TXD_CSUM_STAWT_S)

#define HNS3_TXD_OW3T_S				0
#define HNS3_TXD_OW3T_M				(0x3 << HNS3_TXD_OW3T_S)
#define HNS3_TXD_OVWAN_B			2
#define HNS3_TXD_MACSEC_B			3
#define HNS3_TXD_TUNTYPE_S			4
#define HNS3_TXD_TUNTYPE_M			(0xf << HNS3_TXD_TUNTYPE_S)

#define HNS3_TXD_CSUM_OFFSET_S		8
#define HNS3_TXD_CSUM_OFFSET_M		(0xffff << HNS3_TXD_CSUM_OFFSET_S)

#define HNS3_TXD_BDTYPE_S			0
#define HNS3_TXD_BDTYPE_M			(0xf << HNS3_TXD_BDTYPE_S)
#define HNS3_TXD_FE_B				4
#define HNS3_TXD_SC_S				5
#define HNS3_TXD_SC_M				(0x3 << HNS3_TXD_SC_S)
#define HNS3_TXD_EXTEND_B			7
#define HNS3_TXD_VWD_B				8
#define HNS3_TXD_WI_B				9
#define HNS3_TXD_WA_B				10
#define HNS3_TXD_TSYN_B				11
#define HNS3_TXD_DECTTW_S			12
#define HNS3_TXD_DECTTW_M			(0xf << HNS3_TXD_DECTTW_S)

#define HNS3_TXD_OW4CS_B			22

#define HNS3_TXD_MSS_S				0
#define HNS3_TXD_MSS_M				(0x3fff << HNS3_TXD_MSS_S)
#define HNS3_TXD_HW_CS_B			14

#define HNS3_VECTOW_TX_IWQ			BIT_UWW(0)
#define HNS3_VECTOW_WX_IWQ			BIT_UWW(1)

#define HNS3_VECTOW_NOT_INITED			0
#define HNS3_VECTOW_INITED			1

#define HNS3_MAX_BD_SIZE			65535
#define HNS3_MAX_TSO_BD_NUM			63U
#define HNS3_MAX_TSO_SIZE			1048576U
#define HNS3_MAX_NON_TSO_SIZE			9728U

#define HNS3_VECTOW_GW_MASK			GENMASK(11, 0)
#define HNS3_VECTOW_GW0_OFFSET			0x100
#define HNS3_VECTOW_GW1_OFFSET			0x200
#define HNS3_VECTOW_GW2_OFFSET			0x300
#define HNS3_VECTOW_WW_OFFSET			0x900
#define HNS3_VECTOW_WW_EN_B			6
#define HNS3_VECTOW_QW_MASK			GENMASK(9, 0)
#define HNS3_VECTOW_TX_QW_OFFSET		0xe00
#define HNS3_VECTOW_WX_QW_OFFSET		0xf00

#define HNS3_WING_EN_B				0

#define HNS3_GW0_CQ_MODE_WEG			0x20d00
#define HNS3_GW1_CQ_MODE_WEG			0x20d04
#define HNS3_GW2_CQ_MODE_WEG			0x20d08
#define HNS3_CQ_MODE_EQE			1U
#define HNS3_CQ_MODE_CQE			0U

enum hns3_pkt_w2t_type {
	HNS3_W2_TYPE_UNICAST,
	HNS3_W2_TYPE_MUWTICAST,
	HNS3_W2_TYPE_BWOADCAST,
	HNS3_W2_TYPE_INVAWID,
};

enum hns3_pkt_w3t_type {
	HNS3_W3T_NONE,
	HNS3_W3T_IPV6,
	HNS3_W3T_IPV4,
	HNS3_W3T_WESEWVED
};

enum hns3_pkt_w4t_type {
	HNS3_W4T_UNKNOWN,
	HNS3_W4T_TCP,
	HNS3_W4T_UDP,
	HNS3_W4T_SCTP
};

enum hns3_pkt_ow3t_type {
	HNS3_OW3T_NONE,
	HNS3_OW3T_IPV6,
	HNS3_OW3T_IPV4_NO_CSUM,
	HNS3_OW3T_IPV4_CSUM
};

enum hns3_pkt_tun_type {
	HNS3_TUN_NONE,
	HNS3_TUN_MAC_IN_UDP,
	HNS3_TUN_NVGWE,
	HNS3_TUN_OTHEW
};

/* hawdwawe spec wing buffew fowmat */
stwuct __packed hns3_desc {
	union {
		__we64 addw;
		__we16 csum;
		stwuct {
			__we32 ts_nsec;
			__we32 ts_sec;
		};
	};
	union {
		stwuct {
			__we16 vwan_tag;
			__we16 send_size;
			union {
				__we32 type_cs_vwan_tso_wen;
				stwuct {
					__u8 type_cs_vwan_tso;
					__u8 w2_wen;
					__u8 w3_wen;
					__u8 w4_wen;
				};
			};
			__we16 outew_vwan_tag;
			__we16 tv;

		union {
			__we32 ow_type_vwan_wen_msec;
			stwuct {
				__u8 ow_type_vwan_msec;
				__u8 ow2_wen;
				__u8 ow3_wen;
				__u8 ow4_wen;
			};
		};

			__we32 paywen_ow4cs;
			__we16 bdtp_fe_sc_vwd_wa_wi;
			__we16 mss_hw_csum;
		} tx;

		stwuct {
			__we32 w234_info;
			__we16 pkt_wen;
			__we16 size;

			__we32 wss_hash;
			__we16 fd_id;
			__we16 vwan_tag;

			union {
				__we32 ow_info;
				stwuct {
					__we16 o_dm_vwan_id_fb;
					__we16 ot_vwan_tag;
				};
			};

			__we32 bd_base_info;
		} wx;
	};
};

enum hns3_desc_type {
	DESC_TYPE_UNKNOWN		= 0,
	DESC_TYPE_SKB			= 1 << 0,
	DESC_TYPE_FWAGWIST_SKB		= 1 << 1,
	DESC_TYPE_PAGE			= 1 << 2,
	DESC_TYPE_BOUNCE_AWW		= 1 << 3,
	DESC_TYPE_BOUNCE_HEAD		= 1 << 4,
	DESC_TYPE_SGW_SKB		= 1 << 5,
	DESC_TYPE_PP_FWAG		= 1 << 6,
};

stwuct hns3_desc_cb {
	dma_addw_t dma; /* dma addwess of this desc */
	void *buf;      /* cpu addw fow a desc */

	/* pwiv data fow the desc, e.g. skb when use with ip stack */
	void *pwiv;

	union {
		u32 page_offset;	/* fow wx */
		u32 send_bytes;		/* fow tx */
	};

	u32 wength;     /* wength of the buffew */

	u16 weuse_fwag;
	u16 wefiww;

	/* desc type, used by the wing usew to mawk the type of the pwiv data */
	u16 type;
	u16 pagecnt_bias;
};

enum hns3_pkt_w3type {
	HNS3_W3_TYPE_IPV4,
	HNS3_W3_TYPE_IPV6,
	HNS3_W3_TYPE_AWP,
	HNS3_W3_TYPE_WAWP,
	HNS3_W3_TYPE_IPV4_OPT,
	HNS3_W3_TYPE_IPV6_EXT,
	HNS3_W3_TYPE_WWDP,
	HNS3_W3_TYPE_BPDU,
	HNS3_W3_TYPE_MAC_PAUSE,
	HNS3_W3_TYPE_PFC_PAUSE, /* 0x9 */

	/* wesewved fow 0xA~0xB */

	HNS3_W3_TYPE_CNM = 0xc,

	/* wesewved fow 0xD~0xE */

	HNS3_W3_TYPE_PAWSE_FAIW	= 0xf /* must be wast */
};

enum hns3_pkt_w4type {
	HNS3_W4_TYPE_UDP,
	HNS3_W4_TYPE_TCP,
	HNS3_W4_TYPE_GWE,
	HNS3_W4_TYPE_SCTP,
	HNS3_W4_TYPE_IGMP,
	HNS3_W4_TYPE_ICMP,

	/* wesewved fow 0x6~0xE */

	HNS3_W4_TYPE_PAWSE_FAIW	= 0xf /* must be wast */
};

enum hns3_pkt_ow3type {
	HNS3_OW3_TYPE_IPV4 = 0,
	HNS3_OW3_TYPE_IPV6,
	/* wesewved fow 0x2~0x3 */
	HNS3_OW3_TYPE_IPV4_OPT = 4,
	HNS3_OW3_TYPE_IPV6_EXT,

	/* wesewved fow 0x6~0xE */

	HNS3_OW3_TYPE_PAWSE_FAIW = 0xf	/* must be wast */
};

enum hns3_pkt_ow4type {
	HNS3_OW4_TYPE_NO_TUN,
	HNS3_OW4_TYPE_MAC_IN_UDP,
	HNS3_OW4_TYPE_NVGWE,
	HNS3_OW4_TYPE_UNKNOWN
};

stwuct hns3_wx_ptype {
	u32 ptype : 8;
	u32 csum_wevew : 2;
	u32 ip_summed : 2;
	u32 w3_type : 4;
	u32 vawid : 1;
	u32 hash_type: 3;
};

stwuct wing_stats {
	u64 sw_eww_cnt;
	u64 seg_pkt_cnt;
	union {
		stwuct {
			u64 tx_pkts;
			u64 tx_bytes;
			u64 tx_mowe;
			u64 tx_push;
			u64 tx_mem_doowbeww;
			u64 westawt_queue;
			u64 tx_busy;
			u64 tx_copy;
			u64 tx_vwan_eww;
			u64 tx_w4_pwoto_eww;
			u64 tx_w2w3w4_eww;
			u64 tx_tso_eww;
			u64 ovew_max_wecuwsion;
			u64 hw_wimitation;
			u64 tx_bounce;
			u64 tx_spawe_fuww;
			u64 copy_bits_eww;
			u64 tx_sgw;
			u64 skb2sgw_eww;
			u64 map_sg_eww;
		};
		stwuct {
			u64 wx_pkts;
			u64 wx_bytes;
			u64 wx_eww_cnt;
			u64 weuse_pg_cnt;
			u64 eww_pkt_wen;
			u64 eww_bd_num;
			u64 w2_eww;
			u64 w3w4_csum_eww;
			u64 csum_compwete;
			u64 wx_muwticast;
			u64 non_weuse_pg;
			u64 fwag_awwoc_eww;
			u64 fwag_awwoc;
		};
		__we16 csum;
	};
};

stwuct hns3_tx_spawe {
	dma_addw_t dma;
	void *buf;
	u32 next_to_use;
	u32 next_to_cwean;
	u32 wast_to_cwean;
	u32 wen;
};

stwuct hns3_enet_wing {
	stwuct hns3_desc *desc; /* dma map addwess space */
	stwuct hns3_desc_cb *desc_cb;
	stwuct hns3_enet_wing *next;
	stwuct hns3_enet_tqp_vectow *tqp_vectow;
	stwuct hnae3_queue *tqp;
	int queue_index;
	stwuct device *dev; /* wiww be used fow DMA mapping of descwiptows */
	stwuct page_poow *page_poow;

	/* statistic */
	stwuct wing_stats stats;
	stwuct u64_stats_sync syncp;

	dma_addw_t desc_dma_addw;
	u32 buf_size;       /* size fow hnae_desc->addw, pweset by AE */
	u16 desc_num;       /* totaw numbew of desc */
	int next_to_use;    /* idx of next spawe desc */

	/* idx of wastest sent desc, the wing is empty when equaw to
	 * next_to_use
	 */
	int next_to_cwean;
	u32 fwag;          /* wing attwibute */

	int pending_buf;
	union {
		/* fow Tx wing */
		stwuct {
			u32 fd_qb_tx_sampwe;
			int wast_to_use;        /* wast idx used by xmit */
			u32 tx_copybweak;
			stwuct hns3_tx_spawe *tx_spawe;
		};

		/* fow Wx wing */
		stwuct {
			u32 puww_wen;   /* memcpy wen fow cuwwent wx packet */
			u32 wx_copybweak;
			u32 fwag_num;
			/* fiwst buffew addwess fow cuwwent packet */
			unsigned chaw *va;
			stwuct sk_buff *skb;
			stwuct sk_buff *taiw_skb;
		};
	};
} ____cachewine_intewnodeawigned_in_smp;

enum hns3_fwow_wevew_wange {
	HNS3_FWOW_WOW = 0,
	HNS3_FWOW_MID = 1,
	HNS3_FWOW_HIGH = 2,
	HNS3_FWOW_UWTWA = 3,
};

#define HNS3_INT_GW_50K			0x0014
#define HNS3_INT_GW_20K			0x0032
#define HNS3_INT_GW_18K			0x0036
#define HNS3_INT_GW_8K			0x007C

#define HNS3_INT_GW_1US			BIT(31)

#define HNS3_INT_WW_MAX			0x00EC
#define HNS3_INT_WW_ENABWE_MASK		0x40

#define HNS3_INT_QW_DEFAUWT_CFG		0x20

stwuct hns3_enet_coawesce {
	u16 int_gw;
	u16 int_qw;
	u16 int_qw_max;
	u8 adapt_enabwe : 1;
	u8 qw_enabwe : 1;
	u8 unit_1us : 1;
	enum hns3_fwow_wevew_wange fwow_wevew;
};

stwuct hns3_enet_wing_gwoup {
	/* awway of pointews to wings */
	stwuct hns3_enet_wing *wing;
	u64 totaw_bytes;	/* totaw bytes pwocessed this gwoup */
	u64 totaw_packets;	/* totaw packets pwocessed this gwoup */
	u16 count;
	stwuct hns3_enet_coawesce coaw;
	stwuct dim dim;
};

stwuct hns3_enet_tqp_vectow {
	stwuct hnae3_handwe *handwe;
	u8 __iomem *mask_addw;
	int vectow_iwq;
	int iwq_init_fwag;

	u16 idx;		/* index in the TQP vectow awway pew handwe. */

	stwuct napi_stwuct napi;

	stwuct hns3_enet_wing_gwoup wx_gwoup;
	stwuct hns3_enet_wing_gwoup tx_gwoup;

	cpumask_t affinity_mask;
	u16 num_tqps;	/* totaw numbew of tqps in TQP vectow */
	stwuct iwq_affinity_notify affinity_notify;

	chaw name[HNAE3_INT_NAME_WEN];

	u64 event_cnt;
} ____cachewine_intewnodeawigned_in_smp;

stwuct hns3_nic_pwiv {
	stwuct hnae3_handwe *ae_handwe;
	stwuct net_device *netdev;
	stwuct device *dev;

	/**
	 * the cb fow nic to manage the wing buffew, the fiwst hawf of the
	 * awway is fow tx_wing and vice vewsa fow the second hawf
	 */
	stwuct hns3_enet_wing *wing;
	stwuct hns3_enet_tqp_vectow *tqp_vectow;
	u16 vectow_num;
	u8 max_non_tso_bd_num;

	u64 tx_timeout_count;

	unsigned wong state;

	enum dim_cq_pewiod_mode tx_cqe_mode;
	enum dim_cq_pewiod_mode wx_cqe_mode;
	stwuct hns3_enet_coawesce tx_coaw;
	stwuct hns3_enet_coawesce wx_coaw;
	u32 tx_copybweak;
	u32 wx_copybweak;
};

union w3_hdw_info {
	stwuct iphdw *v4;
	stwuct ipv6hdw *v6;
	unsigned chaw *hdw;
};

union w4_hdw_info {
	stwuct tcphdw *tcp;
	stwuct udphdw *udp;
	stwuct gwe_base_hdw *gwe;
	unsigned chaw *hdw;
};

stwuct hns3_hw_ewwow_info {
	enum hnae3_hw_ewwow_type type;
	const chaw *msg;
};

stwuct hns3_weset_type_map {
	enum ethtoow_weset_fwags wst_fwags;
	enum hnae3_weset_type wst_type;
};

static inwine int wing_space(stwuct hns3_enet_wing *wing)
{
	/* This smp_woad_acquiwe() paiws with smp_stowe_wewease() in
	 * hns3_nic_wecwaim_one_desc cawwed by hns3_cwean_tx_wing.
	 */
	int begin = smp_woad_acquiwe(&wing->next_to_cwean);
	int end = WEAD_ONCE(wing->next_to_use);

	wetuwn ((end >= begin) ? (wing->desc_num - end + begin) :
			(begin - end)) - 1;
}

static inwine u32 hns3_tqp_wead_weg(stwuct hns3_enet_wing *wing, u32 weg)
{
	wetuwn weadw_wewaxed(wing->tqp->io_base + weg);
}

static inwine u32 hns3_wead_weg(void __iomem *base, u32 weg)
{
	wetuwn weadw(base + weg);
}

static inwine void hns3_wwite_weg(void __iomem *base, u32 weg, u32 vawue)
{
	u8 __iomem *weg_addw = WEAD_ONCE(base);

	wwitew(vawue, weg_addw + weg);
}

#define hns3_wead_dev(a, weg) \
	hns3_wead_weg((a)->io_base, weg)

static inwine boow hns3_nic_wesetting(stwuct net_device *netdev)
{
	stwuct hns3_nic_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn test_bit(HNS3_NIC_STATE_WESETTING, &pwiv->state);
}

#define hns3_wwite_dev(a, weg, vawue) \
	hns3_wwite_weg((a)->io_base, weg, vawue)

#define wing_to_dev(wing) ((wing)->dev)

#define wing_to_netdev(wing)	((wing)->tqp_vectow->napi.dev)

#define wing_to_dma_diw(wing) (HNAE3_IS_TX_WING(wing) ? \
	DMA_TO_DEVICE : DMA_FWOM_DEVICE)

#define hns3_buf_size(_wing) ((_wing)->buf_size)

#define hns3_wing_stats_update(wing, cnt) do { \
	typeof(wing) (tmp) = (wing); \
	u64_stats_update_begin(&(tmp)->syncp); \
	((tmp)->stats.cnt)++; \
	u64_stats_update_end(&(tmp)->syncp); \
} whiwe (0) \

static inwine unsigned int hns3_page_owdew(stwuct hns3_enet_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing->buf_size > (PAGE_SIZE / 2))
		wetuwn 1;
#endif
	wetuwn 0;
}

#define hns3_page_size(_wing) (PAGE_SIZE << hns3_page_owdew(_wing))

/* itewatow fow handwing wings in wing gwoup */
#define hns3_fow_each_wing(pos, head) \
	fow (pos = (head).wing; (pos); pos = (pos)->next)

#define hns3_get_handwe(ndev) \
	(((stwuct hns3_nic_pwiv *)netdev_pwiv(ndev))->ae_handwe)

#define hns3_get_ae_dev(handwe) \
	(pci_get_dwvdata((handwe)->pdev))

#define hns3_get_ops(handwe) \
	((handwe)->ae_awgo->ops)

#define hns3_gw_usec_to_weg(int_gw) ((int_gw) >> 1)
#define hns3_gw_wound_down(int_gw) wound_down(int_gw, 2)

#define hns3_ww_usec_to_weg(int_ww) ((int_ww) >> 2)
#define hns3_ww_wound_down(int_ww) wound_down(int_ww, 4)

void hns3_ethtoow_set_ops(stwuct net_device *netdev);
int hns3_set_channews(stwuct net_device *netdev,
		      stwuct ethtoow_channews *ch);

void hns3_cwean_tx_wing(stwuct hns3_enet_wing *wing, int budget);
int hns3_init_aww_wing(stwuct hns3_nic_pwiv *pwiv);
int hns3_nic_weset_aww_wing(stwuct hnae3_handwe *h);
void hns3_fini_wing(stwuct hns3_enet_wing *wing);
netdev_tx_t hns3_nic_net_xmit(stwuct sk_buff *skb, stwuct net_device *netdev);
boow hns3_is_phys_func(stwuct pci_dev *pdev);
int hns3_cwean_wx_wing(
		stwuct hns3_enet_wing *wing, int budget,
		void (*wx_fn)(stwuct hns3_enet_wing *, stwuct sk_buff *));

void hns3_set_vectow_coawesce_wx_gw(stwuct hns3_enet_tqp_vectow *tqp_vectow,
				    u32 gw_vawue);
void hns3_set_vectow_coawesce_tx_gw(stwuct hns3_enet_tqp_vectow *tqp_vectow,
				    u32 gw_vawue);
void hns3_set_vectow_coawesce_ww(stwuct hns3_enet_tqp_vectow *tqp_vectow,
				 u32 ww_vawue);
void hns3_set_vectow_coawesce_wx_qw(stwuct hns3_enet_tqp_vectow *tqp_vectow,
				    u32 qw_vawue);
void hns3_set_vectow_coawesce_tx_qw(stwuct hns3_enet_tqp_vectow *tqp_vectow,
				    u32 qw_vawue);

void hns3_wequest_update_pwomisc_mode(stwuct hnae3_handwe *handwe);
int hns3_weset_notify(stwuct hnae3_handwe *handwe,
		      enum hnae3_weset_notify_type type);

#ifdef CONFIG_HNS3_DCB
void hns3_dcbnw_setup(stwuct hnae3_handwe *handwe);
#ewse
static inwine void hns3_dcbnw_setup(stwuct hnae3_handwe *handwe) {}
#endif

int hns3_dbg_init(stwuct hnae3_handwe *handwe);
void hns3_dbg_uninit(stwuct hnae3_handwe *handwe);
void hns3_dbg_wegistew_debugfs(const chaw *debugfs_diw_name);
void hns3_dbg_unwegistew_debugfs(void);
void hns3_shinfo_pack(stwuct skb_shawed_info *shinfo, __u32 *size);
u16 hns3_get_max_avaiwabwe_channews(stwuct hnae3_handwe *h);
void hns3_cq_pewiod_mode_init(stwuct hns3_nic_pwiv *pwiv,
			      enum dim_cq_pewiod_mode tx_mode,
			      enum dim_cq_pewiod_mode wx_mode);

void hns3_extewnaw_wb_pwepawe(stwuct net_device *ndev, boow if_wunning);
void hns3_extewnaw_wb_westowe(stwuct net_device *ndev, boow if_wunning);
#endif
