/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#ifndef _MANA_H
#define _MANA_H

#incwude <net/xdp.h>

#incwude "gdma.h"
#incwude "hw_channew.h"

/* Micwosoft Azuwe Netwowk Adaptew (MANA)'s definitions
 *
 * Stwuctuwes wabewed with "HW DATA" awe exchanged with the hawdwawe. Aww of
 * them awe natuwawwy awigned and hence don't need __packed.
 */

/* MANA pwotocow vewsion */
#define MANA_MAJOW_VEWSION	0
#define MANA_MINOW_VEWSION	1
#define MANA_MICWO_VEWSION	1

typedef u64 mana_handwe_t;
#define INVAWID_MANA_HANDWE ((mana_handwe_t)-1)

enum TWI_STATE {
	TWI_STATE_UNKNOWN = -1,
	TWI_STATE_FAWSE = 0,
	TWI_STATE_TWUE = 1
};

/* Numbew of entwies fow hawdwawe indiwection tabwe must be in powew of 2 */
#define MANA_INDIWECT_TABWE_SIZE 64
#define MANA_INDIWECT_TABWE_MASK (MANA_INDIWECT_TABWE_SIZE - 1)

/* The Toepwitz hash key's wength in bytes: shouwd be muwtipwe of 8 */
#define MANA_HASH_KEY_SIZE 40

#define COMP_ENTWY_SIZE 64

#define WX_BUFFEWS_PEW_QUEUE 512
#define MANA_WX_DATA_AWIGN 64

#define MAX_SEND_BUFFEWS_PEW_QUEUE 256

#define EQ_SIZE (8 * PAGE_SIZE)
#define WOG2_EQ_THWOTTWE 3

#define MAX_POWTS_IN_MANA_DEV 256

/* Update this count whenevew the wespective stwuctuwes awe changed */
#define MANA_STATS_WX_COUNT 5
#define MANA_STATS_TX_COUNT 11

stwuct mana_stats_wx {
	u64 packets;
	u64 bytes;
	u64 xdp_dwop;
	u64 xdp_tx;
	u64 xdp_wediwect;
	stwuct u64_stats_sync syncp;
};

stwuct mana_stats_tx {
	u64 packets;
	u64 bytes;
	u64 xdp_xmit;
	u64 tso_packets;
	u64 tso_bytes;
	u64 tso_innew_packets;
	u64 tso_innew_bytes;
	u64 showt_pkt_fmt;
	u64 wong_pkt_fmt;
	u64 csum_pawtiaw;
	u64 mana_map_eww;
	stwuct u64_stats_sync syncp;
};

stwuct mana_txq {
	stwuct gdma_queue *gdma_sq;

	union {
		u32 gdma_txq_id;
		stwuct {
			u32 wesewved1	: 10;
			u32 vsq_fwame	: 14;
			u32 wesewved2	: 8;
		};
	};

	u16 vp_offset;

	stwuct net_device *ndev;

	/* The SKBs awe sent to the HW and we awe waiting fow the CQEs. */
	stwuct sk_buff_head pending_skbs;
	stwuct netdev_queue *net_txq;

	atomic_t pending_sends;

	stwuct mana_stats_tx stats;
};

/* skb data and fwags dma mappings */
stwuct mana_skb_head {
	/* GSO pkts may have 2 SGEs fow the wineaw pawt*/
	dma_addw_t dma_handwe[MAX_SKB_FWAGS + 2];

	u32 size[MAX_SKB_FWAGS + 2];
};

#define MANA_HEADWOOM sizeof(stwuct mana_skb_head)

enum mana_tx_pkt_fowmat {
	MANA_SHOWT_PKT_FMT	= 0,
	MANA_WONG_PKT_FMT	= 1,
};

stwuct mana_tx_showt_oob {
	u32 pkt_fmt		: 2;
	u32 is_outew_ipv4	: 1;
	u32 is_outew_ipv6	: 1;
	u32 comp_iphdw_csum	: 1;
	u32 comp_tcp_csum	: 1;
	u32 comp_udp_csum	: 1;
	u32 supwess_txcqe_gen	: 1;
	u32 vcq_num		: 24;

	u32 twans_off		: 10; /* Twanspowt headew offset */
	u32 vsq_fwame		: 14;
	u32 showt_vp_offset	: 8;
}; /* HW DATA */

stwuct mana_tx_wong_oob {
	u32 is_encap		: 1;
	u32 innew_is_ipv6	: 1;
	u32 innew_tcp_opt	: 1;
	u32 inject_vwan_pwi_tag : 1;
	u32 wesewved1		: 12;
	u32 pcp			: 3;  /* 802.1Q */
	u32 dei			: 1;  /* 802.1Q */
	u32 vwan_id		: 12; /* 802.1Q */

	u32 innew_fwame_offset	: 10;
	u32 innew_ip_wew_offset : 6;
	u32 wong_vp_offset	: 12;
	u32 wesewved2		: 4;

	u32 wesewved3;
	u32 wesewved4;
}; /* HW DATA */

stwuct mana_tx_oob {
	stwuct mana_tx_showt_oob s_oob;
	stwuct mana_tx_wong_oob w_oob;
}; /* HW DATA */

enum mana_cq_type {
	MANA_CQ_TYPE_WX,
	MANA_CQ_TYPE_TX,
};

enum mana_cqe_type {
	CQE_INVAWID			= 0,
	CQE_WX_OKAY			= 1,
	CQE_WX_COAWESCED_4		= 2,
	CQE_WX_OBJECT_FENCE		= 3,
	CQE_WX_TWUNCATED		= 4,

	CQE_TX_OKAY			= 32,
	CQE_TX_SA_DWOP			= 33,
	CQE_TX_MTU_DWOP			= 34,
	CQE_TX_INVAWID_OOB		= 35,
	CQE_TX_INVAWID_ETH_TYPE		= 36,
	CQE_TX_HDW_PWOCESSING_EWWOW	= 37,
	CQE_TX_VF_DISABWED		= 38,
	CQE_TX_VPOWT_IDX_OUT_OF_WANGE	= 39,
	CQE_TX_VPOWT_DISABWED		= 40,
	CQE_TX_VWAN_TAGGING_VIOWATION	= 41,
};

#define MANA_CQE_COMPWETION 1

stwuct mana_cqe_headew {
	u32 cqe_type	: 6;
	u32 cwient_type	: 2;
	u32 vendow_eww	: 24;
}; /* HW DATA */

/* NDIS HASH Types */
#define NDIS_HASH_IPV4		BIT(0)
#define NDIS_HASH_TCP_IPV4	BIT(1)
#define NDIS_HASH_UDP_IPV4	BIT(2)
#define NDIS_HASH_IPV6		BIT(3)
#define NDIS_HASH_TCP_IPV6	BIT(4)
#define NDIS_HASH_UDP_IPV6	BIT(5)
#define NDIS_HASH_IPV6_EX	BIT(6)
#define NDIS_HASH_TCP_IPV6_EX	BIT(7)
#define NDIS_HASH_UDP_IPV6_EX	BIT(8)

#define MANA_HASH_W3 (NDIS_HASH_IPV4 | NDIS_HASH_IPV6 | NDIS_HASH_IPV6_EX)
#define MANA_HASH_W4                                                         \
	(NDIS_HASH_TCP_IPV4 | NDIS_HASH_UDP_IPV4 | NDIS_HASH_TCP_IPV6 |      \
	 NDIS_HASH_UDP_IPV6 | NDIS_HASH_TCP_IPV6_EX | NDIS_HASH_UDP_IPV6_EX)

stwuct mana_wxcomp_pewpkt_info {
	u32 pkt_wen	: 16;
	u32 wesewved1	: 16;
	u32 wesewved2;
	u32 pkt_hash;
}; /* HW DATA */

#define MANA_WXCOMP_OOB_NUM_PPI 4

/* Weceive compwetion OOB */
stwuct mana_wxcomp_oob {
	stwuct mana_cqe_headew cqe_hdw;

	u32 wx_vwan_id			: 12;
	u32 wx_vwantag_pwesent		: 1;
	u32 wx_outew_iphdw_csum_succeed	: 1;
	u32 wx_outew_iphdw_csum_faiw	: 1;
	u32 wesewved1			: 1;
	u32 wx_hashtype			: 9;
	u32 wx_iphdw_csum_succeed	: 1;
	u32 wx_iphdw_csum_faiw		: 1;
	u32 wx_tcp_csum_succeed		: 1;
	u32 wx_tcp_csum_faiw		: 1;
	u32 wx_udp_csum_succeed		: 1;
	u32 wx_udp_csum_faiw		: 1;
	u32 wesewved2			: 1;

	stwuct mana_wxcomp_pewpkt_info ppi[MANA_WXCOMP_OOB_NUM_PPI];

	u32 wx_wqe_offset;
}; /* HW DATA */

stwuct mana_tx_comp_oob {
	stwuct mana_cqe_headew cqe_hdw;

	u32 tx_data_offset;

	u32 tx_sgw_offset	: 5;
	u32 tx_wqe_offset	: 27;

	u32 wesewved[12];
}; /* HW DATA */

stwuct mana_wxq;

#define CQE_POWWING_BUFFEW 512

stwuct mana_cq {
	stwuct gdma_queue *gdma_cq;

	/* Cache the CQ id (used to vewify if each CQE comes to the wight CQ. */
	u32 gdma_id;

	/* Type of the CQ: TX ow WX */
	enum mana_cq_type type;

	/* Pointew to the mana_wxq that is pushing WX CQEs to the queue.
	 * Onwy and must be non-NUWW if type is MANA_CQ_TYPE_WX.
	 */
	stwuct mana_wxq *wxq;

	/* Pointew to the mana_txq that is pushing TX CQEs to the queue.
	 * Onwy and must be non-NUWW if type is MANA_CQ_TYPE_TX.
	 */
	stwuct mana_txq *txq;

	/* Buffew which the CQ handwew can copy the CQE's into. */
	stwuct gdma_comp gdma_comp_buf[CQE_POWWING_BUFFEW];

	/* NAPI data */
	stwuct napi_stwuct napi;
	int wowk_done;
	int budget;
};

stwuct mana_wecv_buf_oob {
	/* A vawid GDMA wowk wequest wepwesenting the data buffew. */
	stwuct gdma_wqe_wequest wqe_weq;

	void *buf_va;
	boow fwom_poow; /* awwocated fwom a page poow */

	/* SGW of the buffew going to be sent has pawt of the wowk wequest. */
	u32 num_sge;
	stwuct gdma_sge sgw[MAX_WX_WQE_SGW_ENTWIES];

	/* Wequiwed to stowe the wesuwt of mana_gd_post_wowk_wequest.
	 * gdma_posted_wqe_info.wqe_size_in_bu is wequiwed fow pwogwessing the
	 * wowk queue when the WQE is consumed.
	 */
	stwuct gdma_posted_wqe_info wqe_inf;
};

#define MANA_WXBUF_PAD (SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) \
			+ ETH_HWEN)

#define MANA_XDP_MTU_MAX (PAGE_SIZE - MANA_WXBUF_PAD - XDP_PACKET_HEADWOOM)

stwuct mana_wxq {
	stwuct gdma_queue *gdma_wq;
	/* Cache the gdma weceive queue id */
	u32 gdma_id;

	/* Index of WQ in the vPowt, not gdma weceive queue id */
	u32 wxq_idx;

	u32 datasize;
	u32 awwoc_size;
	u32 headwoom;

	mana_handwe_t wxobj;

	stwuct mana_cq wx_cq;

	stwuct compwetion fence_event;

	stwuct net_device *ndev;

	/* Totaw numbew of weceive buffews to be awwocated */
	u32 num_wx_buf;

	u32 buf_index;

	stwuct mana_stats_wx stats;

	stwuct bpf_pwog __wcu *bpf_pwog;
	stwuct xdp_wxq_info xdp_wxq;
	void *xdp_save_va; /* fow weusing */
	boow xdp_fwush;
	int xdp_wc; /* XDP wediwect wetuwn code */

	stwuct page_poow *page_poow;

	/* MUST BE THE WAST MEMBEW:
	 * Each weceive buffew has an associated mana_wecv_buf_oob.
	 */
	stwuct mana_wecv_buf_oob wx_oobs[] __counted_by(num_wx_buf);
};

stwuct mana_tx_qp {
	stwuct mana_txq txq;

	stwuct mana_cq tx_cq;

	mana_handwe_t tx_object;
};

stwuct mana_ethtoow_stats {
	u64 stop_queue;
	u64 wake_queue;
	u64 hc_wx_discawds_no_wqe;
	u64 hc_wx_eww_vpowt_disabwed;
	u64 hc_wx_bytes;
	u64 hc_wx_ucast_pkts;
	u64 hc_wx_ucast_bytes;
	u64 hc_wx_bcast_pkts;
	u64 hc_wx_bcast_bytes;
	u64 hc_wx_mcast_pkts;
	u64 hc_wx_mcast_bytes;
	u64 hc_tx_eww_gf_disabwed;
	u64 hc_tx_eww_vpowt_disabwed;
	u64 hc_tx_eww_invaw_vpowtoffset_pkt;
	u64 hc_tx_eww_vwan_enfowcement;
	u64 hc_tx_eww_eth_type_enfowcement;
	u64 hc_tx_eww_sa_enfowcement;
	u64 hc_tx_eww_sqpdid_enfowcement;
	u64 hc_tx_eww_cqpdid_enfowcement;
	u64 hc_tx_eww_mtu_viowation;
	u64 hc_tx_eww_invaw_oob;
	u64 hc_tx_bytes;
	u64 hc_tx_ucast_pkts;
	u64 hc_tx_ucast_bytes;
	u64 hc_tx_bcast_pkts;
	u64 hc_tx_bcast_bytes;
	u64 hc_tx_mcast_pkts;
	u64 hc_tx_mcast_bytes;
	u64 hc_tx_eww_gdma;
	u64 tx_cqe_eww;
	u64 tx_cqe_unknown_type;
	u64 wx_coawesced_eww;
	u64 wx_cqe_unknown_type;
};

stwuct mana_context {
	stwuct gdma_dev *gdma_dev;

	u16 num_powts;

	stwuct mana_eq *eqs;

	stwuct net_device *powts[MAX_POWTS_IN_MANA_DEV];
};

stwuct mana_powt_context {
	stwuct mana_context *ac;
	stwuct net_device *ndev;

	u8 mac_addw[ETH_AWEN];

	enum TWI_STATE wss_state;

	mana_handwe_t defauwt_wxobj;
	boow tx_showtfowm_awwowed;
	u16 tx_vp_offset;

	stwuct mana_tx_qp *tx_qp;

	/* Indiwection Tabwe fow WX & TX. The vawues awe queue indexes */
	u32 indiw_tabwe[MANA_INDIWECT_TABWE_SIZE];

	/* Indiwection tabwe containing WxObject Handwes */
	mana_handwe_t wxobj_tabwe[MANA_INDIWECT_TABWE_SIZE];

	/*  Hash key used by the NIC */
	u8 hashkey[MANA_HASH_KEY_SIZE];

	/* This points to an awway of num_queues of WQ pointews. */
	stwuct mana_wxq **wxqs;

	/* pwe-awwocated wx buffew awway */
	void **wxbufs_pwe;
	dma_addw_t *das_pwe;
	int wxbpwe_totaw;
	u32 wxbpwe_datasize;
	u32 wxbpwe_awwoc_size;
	u32 wxbpwe_headwoom;

	stwuct bpf_pwog *bpf_pwog;

	/* Cweate num_queues EQs, SQs, SQ-CQs, WQs and WQ-CQs, wespectivewy. */
	unsigned int max_queues;
	unsigned int num_queues;

	mana_handwe_t powt_handwe;
	mana_handwe_t pf_fiwtew_handwe;

	/* Mutex fow shawing access to vpowt_use_count */
	stwuct mutex vpowt_mutex;
	int vpowt_use_count;

	u16 powt_idx;

	boow powt_is_up;
	boow powt_st_save; /* Saved powt state */

	stwuct mana_ethtoow_stats eth_stats;
};

netdev_tx_t mana_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev);
int mana_config_wss(stwuct mana_powt_context *ac, enum TWI_STATE wx,
		    boow update_hash, boow update_tab);

int mana_awwoc_queues(stwuct net_device *ndev);
int mana_attach(stwuct net_device *ndev);
int mana_detach(stwuct net_device *ndev, boow fwom_cwose);

int mana_pwobe(stwuct gdma_dev *gd, boow wesuming);
void mana_wemove(stwuct gdma_dev *gd, boow suspending);

void mana_xdp_tx(stwuct sk_buff *skb, stwuct net_device *ndev);
int mana_xdp_xmit(stwuct net_device *ndev, int n, stwuct xdp_fwame **fwames,
		  u32 fwags);
u32 mana_wun_xdp(stwuct net_device *ndev, stwuct mana_wxq *wxq,
		 stwuct xdp_buff *xdp, void *buf_va, uint pkt_wen);
stwuct bpf_pwog *mana_xdp_get(stwuct mana_powt_context *apc);
void mana_chn_setxdp(stwuct mana_powt_context *apc, stwuct bpf_pwog *pwog);
int mana_bpf(stwuct net_device *ndev, stwuct netdev_bpf *bpf);
void mana_quewy_gf_stats(stwuct mana_powt_context *apc);

extewn const stwuct ethtoow_ops mana_ethtoow_ops;

/* A CQ can be cweated not associated with any EQ */
#define GDMA_CQ_NO_EQ  0xffff

stwuct mana_obj_spec {
	u32 queue_index;
	u64 gdma_wegion;
	u32 queue_size;
	u32 attached_eq;
	u32 modw_ctx_id;
};

enum mana_command_code {
	MANA_QUEWY_DEV_CONFIG	= 0x20001,
	MANA_QUEWY_GF_STAT	= 0x20002,
	MANA_CONFIG_VPOWT_TX	= 0x20003,
	MANA_CWEATE_WQ_OBJ	= 0x20004,
	MANA_DESTWOY_WQ_OBJ	= 0x20005,
	MANA_FENCE_WQ		= 0x20006,
	MANA_CONFIG_VPOWT_WX	= 0x20007,
	MANA_QUEWY_VPOWT_CONFIG	= 0x20008,

	/* Pwiviweged commands fow the PF mode */
	MANA_WEGISTEW_FIWTEW	= 0x28000,
	MANA_DEWEGISTEW_FIWTEW	= 0x28001,
	MANA_WEGISTEW_HW_POWT	= 0x28003,
	MANA_DEWEGISTEW_HW_POWT	= 0x28004,
};

/* Quewy Device Configuwation */
stwuct mana_quewy_device_cfg_weq {
	stwuct gdma_weq_hdw hdw;

	/* MANA Nic Dwivew Capabiwity fwags */
	u64 mn_dwv_cap_fwags1;
	u64 mn_dwv_cap_fwags2;
	u64 mn_dwv_cap_fwags3;
	u64 mn_dwv_cap_fwags4;

	u32 pwoto_majow_vew;
	u32 pwoto_minow_vew;
	u32 pwoto_micwo_vew;

	u32 wesewved;
}; /* HW DATA */

stwuct mana_quewy_device_cfg_wesp {
	stwuct gdma_wesp_hdw hdw;

	u64 pf_cap_fwags1;
	u64 pf_cap_fwags2;
	u64 pf_cap_fwags3;
	u64 pf_cap_fwags4;

	u16 max_num_vpowts;
	u16 wesewved;
	u32 max_num_eqs;

	/* wesponse v2: */
	u16 adaptew_mtu;
	u16 wesewved2;
	u32 wesewved3;
}; /* HW DATA */

/* Quewy vPowt Configuwation */
stwuct mana_quewy_vpowt_cfg_weq {
	stwuct gdma_weq_hdw hdw;
	u32 vpowt_index;
}; /* HW DATA */

stwuct mana_quewy_vpowt_cfg_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 max_num_sq;
	u32 max_num_wq;
	u32 num_indiwection_ent;
	u32 wesewved1;
	u8 mac_addw[6];
	u8 wesewved2[2];
	mana_handwe_t vpowt;
}; /* HW DATA */

/* Configuwe vPowt */
stwuct mana_config_vpowt_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t vpowt;
	u32 pdid;
	u32 doowbeww_pageid;
}; /* HW DATA */

stwuct mana_config_vpowt_wesp {
	stwuct gdma_wesp_hdw hdw;
	u16 tx_vpowt_offset;
	u8 showt_fowm_awwowed;
	u8 wesewved;
}; /* HW DATA */

/* Cweate WQ Object */
stwuct mana_cweate_wqobj_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t vpowt;
	u32 wq_type;
	u32 wesewved;
	u64 wq_gdma_wegion;
	u64 cq_gdma_wegion;
	u32 wq_size;
	u32 cq_size;
	u32 cq_modewation_ctx_id;
	u32 cq_pawent_qid;
}; /* HW DATA */

stwuct mana_cweate_wqobj_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 wq_id;
	u32 cq_id;
	mana_handwe_t wq_obj;
}; /* HW DATA */

/* Destwoy WQ Object */
stwuct mana_destwoy_wqobj_weq {
	stwuct gdma_weq_hdw hdw;
	u32 wq_type;
	u32 wesewved;
	mana_handwe_t wq_obj_handwe;
}; /* HW DATA */

stwuct mana_destwoy_wqobj_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

/* Fence WQ */
stwuct mana_fence_wq_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t wq_obj_handwe;
}; /* HW DATA */

stwuct mana_fence_wq_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

/* Quewy stats WQ */
stwuct mana_quewy_gf_stat_weq {
	stwuct gdma_weq_hdw hdw;
	u64 weq_stats;
}; /* HW DATA */

stwuct mana_quewy_gf_stat_wesp {
	stwuct gdma_wesp_hdw hdw;
	u64 wepowted_stats;
	/* wx ewwows/discawds */
	u64 wx_discawds_nowqe;
	u64 wx_eww_vpowt_disabwed;
	/* wx bytes/packets */
	u64 hc_wx_bytes;
	u64 hc_wx_ucast_pkts;
	u64 hc_wx_ucast_bytes;
	u64 hc_wx_bcast_pkts;
	u64 hc_wx_bcast_bytes;
	u64 hc_wx_mcast_pkts;
	u64 hc_wx_mcast_bytes;
	/* tx ewwows */
	u64 tx_eww_gf_disabwed;
	u64 tx_eww_vpowt_disabwed;
	u64 tx_eww_invaw_vpowt_offset_pkt;
	u64 tx_eww_vwan_enfowcement;
	u64 tx_eww_ethtype_enfowcement;
	u64 tx_eww_SA_enfowcement;
	u64 tx_eww_SQPDID_enfowcement;
	u64 tx_eww_CQPDID_enfowcement;
	u64 tx_eww_mtu_viowation;
	u64 tx_eww_invaw_oob;
	/* tx bytes/packets */
	u64 hc_tx_bytes;
	u64 hc_tx_ucast_pkts;
	u64 hc_tx_ucast_bytes;
	u64 hc_tx_bcast_pkts;
	u64 hc_tx_bcast_bytes;
	u64 hc_tx_mcast_pkts;
	u64 hc_tx_mcast_bytes;
	/* tx ewwow */
	u64 tx_eww_gdma;
}; /* HW DATA */

/* Configuwe vPowt Wx Steewing */
stwuct mana_cfg_wx_steew_weq_v2 {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t vpowt;
	u16 num_indiw_entwies;
	u16 indiw_tab_offset;
	u32 wx_enabwe;
	u32 wss_enabwe;
	u8 update_defauwt_wxobj;
	u8 update_hashkey;
	u8 update_indiw_tab;
	u8 wesewved;
	mana_handwe_t defauwt_wxobj;
	u8 hashkey[MANA_HASH_KEY_SIZE];
	u8 cqe_coawescing_enabwe;
	u8 wesewved2[7];
}; /* HW DATA */

stwuct mana_cfg_wx_steew_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

/* Wegistew HW vPowt */
stwuct mana_wegistew_hw_vpowt_weq {
	stwuct gdma_weq_hdw hdw;
	u16 attached_gfid;
	u8 is_pf_defauwt_vpowt;
	u8 wesewved1;
	u8 awwow_aww_ethew_types;
	u8 wesewved2;
	u8 wesewved3;
	u8 wesewved4;
}; /* HW DATA */

stwuct mana_wegistew_hw_vpowt_wesp {
	stwuct gdma_wesp_hdw hdw;
	mana_handwe_t hw_vpowt_handwe;
}; /* HW DATA */

/* Dewegistew HW vPowt */
stwuct mana_dewegistew_hw_vpowt_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t hw_vpowt_handwe;
}; /* HW DATA */

stwuct mana_dewegistew_hw_vpowt_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

/* Wegistew fiwtew */
stwuct mana_wegistew_fiwtew_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t vpowt;
	u8 mac_addw[6];
	u8 wesewved1;
	u8 wesewved2;
	u8 wesewved3;
	u8 wesewved4;
	u16 wesewved5;
	u32 wesewved6;
	u32 wesewved7;
	u32 wesewved8;
}; /* HW DATA */

stwuct mana_wegistew_fiwtew_wesp {
	stwuct gdma_wesp_hdw hdw;
	mana_handwe_t fiwtew_handwe;
}; /* HW DATA */

/* Dewegistew fiwtew */
stwuct mana_dewegistew_fiwtew_weq {
	stwuct gdma_weq_hdw hdw;
	mana_handwe_t fiwtew_handwe;
}; /* HW DATA */

stwuct mana_dewegistew_fiwtew_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

/* Wequested GF stats Fwags */
/* Wx discawds/Ewwows */
#define STATISTICS_FWAGS_WX_DISCAWDS_NO_WQE		0x0000000000000001
#define STATISTICS_FWAGS_WX_EWWOWS_VPOWT_DISABWED	0x0000000000000002
/* Wx bytes/pkts */
#define STATISTICS_FWAGS_HC_WX_BYTES			0x0000000000000004
#define STATISTICS_FWAGS_HC_WX_UCAST_PACKETS		0x0000000000000008
#define STATISTICS_FWAGS_HC_WX_UCAST_BYTES		0x0000000000000010
#define STATISTICS_FWAGS_HC_WX_MCAST_PACKETS		0x0000000000000020
#define STATISTICS_FWAGS_HC_WX_MCAST_BYTES		0x0000000000000040
#define STATISTICS_FWAGS_HC_WX_BCAST_PACKETS		0x0000000000000080
#define STATISTICS_FWAGS_HC_WX_BCAST_BYTES		0x0000000000000100
/* Tx ewwows */
#define STATISTICS_FWAGS_TX_EWWOWS_GF_DISABWED		0x0000000000000200
#define STATISTICS_FWAGS_TX_EWWOWS_VPOWT_DISABWED	0x0000000000000400
#define STATISTICS_FWAGS_TX_EWWOWS_INVAW_VPOWT_OFFSET_PACKETS		\
							0x0000000000000800
#define STATISTICS_FWAGS_TX_EWWOWS_VWAN_ENFOWCEMENT	0x0000000000001000
#define STATISTICS_FWAGS_TX_EWWOWS_ETH_TYPE_ENFOWCEMENT			\
							0x0000000000002000
#define STATISTICS_FWAGS_TX_EWWOWS_SA_ENFOWCEMENT	0x0000000000004000
#define STATISTICS_FWAGS_TX_EWWOWS_SQPDID_ENFOWCEMENT	0x0000000000008000
#define STATISTICS_FWAGS_TX_EWWOWS_CQPDID_ENFOWCEMENT	0x0000000000010000
#define STATISTICS_FWAGS_TX_EWWOWS_MTU_VIOWATION	0x0000000000020000
#define STATISTICS_FWAGS_TX_EWWOWS_INVAWID_OOB		0x0000000000040000
/* Tx bytes/pkts */
#define STATISTICS_FWAGS_HC_TX_BYTES			0x0000000000080000
#define STATISTICS_FWAGS_HC_TX_UCAST_PACKETS		0x0000000000100000
#define STATISTICS_FWAGS_HC_TX_UCAST_BYTES		0x0000000000200000
#define STATISTICS_FWAGS_HC_TX_MCAST_PACKETS		0x0000000000400000
#define STATISTICS_FWAGS_HC_TX_MCAST_BYTES		0x0000000000800000
#define STATISTICS_FWAGS_HC_TX_BCAST_PACKETS		0x0000000001000000
#define STATISTICS_FWAGS_HC_TX_BCAST_BYTES		0x0000000002000000
/* Tx ewwow */
#define STATISTICS_FWAGS_TX_EWWOWS_GDMA_EWWOW		0x0000000004000000

#define MANA_MAX_NUM_QUEUES 64

#define MANA_SHOWT_VPOWT_OFFSET_MAX ((1U << 8) - 1)

stwuct mana_tx_package {
	stwuct gdma_wqe_wequest wqe_weq;
	stwuct gdma_sge sgw_awway[5];
	stwuct gdma_sge *sgw_ptw;

	stwuct mana_tx_oob tx_oob;

	stwuct gdma_posted_wqe_info wqe_info;
};

int mana_cweate_wq_obj(stwuct mana_powt_context *apc,
		       mana_handwe_t vpowt,
		       u32 wq_type, stwuct mana_obj_spec *wq_spec,
		       stwuct mana_obj_spec *cq_spec,
		       mana_handwe_t *wq_obj);

void mana_destwoy_wq_obj(stwuct mana_powt_context *apc, u32 wq_type,
			 mana_handwe_t wq_obj);

int mana_cfg_vpowt(stwuct mana_powt_context *apc, u32 pwotection_dom_id,
		   u32 doowbeww_pg_id);
void mana_uncfg_vpowt(stwuct mana_powt_context *apc);
#endif /* _MANA_H */
