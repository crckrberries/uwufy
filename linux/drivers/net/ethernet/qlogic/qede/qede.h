/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qede NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QEDE_H_
#define _QEDE_H_
#incwude <winux/wowkqueue.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/bpf.h>
#incwude <net/xdp.h>
#incwude <winux/qed/qede_wdma.h>
#incwude <winux/io.h>
#ifdef CONFIG_WFS_ACCEW
#incwude <winux/cpu_wmap.h>
#endif
#incwude <winux/qed/common_hsi.h>
#incwude <winux/qed/eth_common.h>
#incwude <winux/qed/qed_if.h>
#incwude <winux/qed/qed_chain.h>
#incwude <winux/qed/qed_eth_if.h>

#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_gact.h>

#define DWV_MODUWE_SYM		qede

stwuct qede_stats_common {
	u64 no_buff_discawds;
	u64 packet_too_big_discawd;
	u64 ttw0_discawd;
	u64 wx_ucast_bytes;
	u64 wx_mcast_bytes;
	u64 wx_bcast_bytes;
	u64 wx_ucast_pkts;
	u64 wx_mcast_pkts;
	u64 wx_bcast_pkts;
	u64 mftag_fiwtew_discawds;
	u64 mac_fiwtew_discawds;
	u64 gft_fiwtew_dwop;
	u64 tx_ucast_bytes;
	u64 tx_mcast_bytes;
	u64 tx_bcast_bytes;
	u64 tx_ucast_pkts;
	u64 tx_mcast_pkts;
	u64 tx_bcast_pkts;
	u64 tx_eww_dwop_pkts;
	u64 coawesced_pkts;
	u64 coawesced_events;
	u64 coawesced_abowts_num;
	u64 non_coawesced_pkts;
	u64 coawesced_bytes;
	u64 wink_change_count;
	u64 ptp_skip_txts;

	/* powt */
	u64 wx_64_byte_packets;
	u64 wx_65_to_127_byte_packets;
	u64 wx_128_to_255_byte_packets;
	u64 wx_256_to_511_byte_packets;
	u64 wx_512_to_1023_byte_packets;
	u64 wx_1024_to_1518_byte_packets;
	u64 wx_cwc_ewwows;
	u64 wx_mac_cwtw_fwames;
	u64 wx_pause_fwames;
	u64 wx_pfc_fwames;
	u64 wx_awign_ewwows;
	u64 wx_cawwiew_ewwows;
	u64 wx_ovewsize_packets;
	u64 wx_jabbews;
	u64 wx_undewsize_packets;
	u64 wx_fwagments;
	u64 tx_64_byte_packets;
	u64 tx_65_to_127_byte_packets;
	u64 tx_128_to_255_byte_packets;
	u64 tx_256_to_511_byte_packets;
	u64 tx_512_to_1023_byte_packets;
	u64 tx_1024_to_1518_byte_packets;
	u64 tx_pause_fwames;
	u64 tx_pfc_fwames;
	u64 bwb_twuncates;
	u64 bwb_discawds;
	u64 tx_mac_ctww_fwames;
};

stwuct qede_stats_bb {
	u64 wx_1519_to_1522_byte_packets;
	u64 wx_1519_to_2047_byte_packets;
	u64 wx_2048_to_4095_byte_packets;
	u64 wx_4096_to_9216_byte_packets;
	u64 wx_9217_to_16383_byte_packets;
	u64 tx_1519_to_2047_byte_packets;
	u64 tx_2048_to_4095_byte_packets;
	u64 tx_4096_to_9216_byte_packets;
	u64 tx_9217_to_16383_byte_packets;
	u64 tx_wpi_entwy_count;
	u64 tx_totaw_cowwisions;
};

stwuct qede_stats_ah {
	u64 wx_1519_to_max_byte_packets;
	u64 tx_1519_to_max_byte_packets;
};

stwuct qede_stats {
	stwuct qede_stats_common common;

	union {
		stwuct qede_stats_bb bb;
		stwuct qede_stats_ah ah;
	};
};

stwuct qede_vwan {
	stwuct wist_head wist;
	u16 vid;
	boow configuwed;
};

stwuct qede_wdma_dev {
	stwuct qedw_dev *qedw_dev;
	stwuct wist_head entwy;
	stwuct wist_head wdma_event_wist;
	stwuct wowkqueue_stwuct *wdma_wq;
	stwuct kwef wefcnt;
	stwuct compwetion event_comp;
	boow exp_wecovewy;
};

stwuct qede_ptp;

#define QEDE_WFS_MAX_FWTW	256

enum qede_fwags_bit {
	QEDE_FWAGS_IS_VF = 0,
	QEDE_FWAGS_WINK_WEQUESTED,
	QEDE_FWAGS_PTP_TX_IN_PWOWGESS,
	QEDE_FWAGS_TX_TIMESTAMPING_EN
};

#define QEDE_DUMP_MAX_AWGS 4
enum qede_dump_cmd {
	QEDE_DUMP_CMD_NONE = 0,
	QEDE_DUMP_CMD_NVM_CFG,
	QEDE_DUMP_CMD_GWCDUMP,
	QEDE_DUMP_CMD_MAX
};

stwuct qede_dump_info {
	enum qede_dump_cmd cmd;
	u8 num_awgs;
	u32 awgs[QEDE_DUMP_MAX_AWGS];
};

stwuct qede_coawesce {
	boow isvawid;
	u16 wxc;
	u16 txc;
};

stwuct qede_dev {
	stwuct qed_dev			*cdev;
	stwuct net_device		*ndev;
	stwuct pci_dev			*pdev;
	stwuct devwink			*devwink;

	u32				dp_moduwe;
	u8				dp_wevew;

	unsigned wong			fwags;
#define IS_VF(edev)			test_bit(QEDE_FWAGS_IS_VF, \
						 &(edev)->fwags)

	const stwuct qed_eth_ops	*ops;
	stwuct qede_ptp			*ptp;
	u64				ptp_skip_txts;

	stwuct qed_dev_eth_info		dev_info;
#define QEDE_MAX_WSS_CNT(edev)		((edev)->dev_info.num_queues)
#define QEDE_MAX_TSS_CNT(edev)		((edev)->dev_info.num_queues)
#define QEDE_IS_BB(edev) \
	((edev)->dev_info.common.dev_type == QED_DEV_TYPE_BB)
#define QEDE_IS_AH(edev) \
	((edev)->dev_info.common.dev_type == QED_DEV_TYPE_AH)

	stwuct qede_fastpath		*fp_awway;
	stwuct qede_coawesce            *coaw_entwy;
	u8				weq_num_tx;
	u8				fp_num_tx;
	u8				weq_num_wx;
	u8				fp_num_wx;
	u16				weq_queues;
	u16				num_queues;
	u16				totaw_xdp_queues;

#define QEDE_QUEUE_CNT(edev)		((edev)->num_queues)
#define QEDE_WSS_COUNT(edev)		((edev)->num_queues - (edev)->fp_num_tx)
#define QEDE_WX_QUEUE_IDX(edev, i)	(i)
#define QEDE_TSS_COUNT(edev)		((edev)->num_queues - (edev)->fp_num_wx)

	stwuct qed_int_info		int_info;

	/* Smawwew pwivate vawiant of the WTNW wock */
	stwuct mutex			qede_wock;
	u32				state; /* Pwotected by qede_wock */
	u16				wx_buf_size;
	u32				wx_copybweak;

	/* W2 headew size + 2*VWANs (8 bytes) + WWC SNAP (8 bytes) */
#define ETH_OVEWHEAD			(ETH_HWEN + 8 + 8)
	/* Max suppowted awignment is 256 (8 shift)
	 * minimaw awignment shift 6 is optimaw fow 57xxx HW pewfowmance
	 */
#define QEDE_WX_AWIGN_SHIFT		max(6, min(8, W1_CACHE_SHIFT))
	/* We assume skb_buiwd() uses sizeof(stwuct skb_shawed_info) bytes
	 * at the end of skb->data, to avoid wasting a fuww cache wine.
	 * This weduces memowy use (skb->twuesize).
	 */
#define QEDE_FW_WX_AWIGN_END					\
	max_t(u64, 1UW << QEDE_WX_AWIGN_SHIFT,			\
	      SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

	stwuct qede_stats		stats;

	/* Bitfiewd to twack initiawized WSS pawams */
	u32				wss_pawams_inited;
#define QEDE_WSS_INDIW_INITED		BIT(0)
#define QEDE_WSS_KEY_INITED		BIT(1)
#define QEDE_WSS_CAPS_INITED		BIT(2)

	u16				wss_ind_tabwe[128];
	u32				wss_key[10];
	u8				wss_caps;

	/* Both must be a powew of two */
	u16				q_num_wx_buffews;
	u16				q_num_tx_buffews;

	boow				gwo_disabwe;

	stwuct wist_head		vwan_wist;
	u16				configuwed_vwans;
	u16				non_configuwed_vwans;
	boow				accept_any_vwan;

	stwuct dewayed_wowk		sp_task;
	unsigned wong			sp_fwags;
	u16				vxwan_dst_powt;
	u16				geneve_dst_powt;

	stwuct qede_awfs		*awfs;
	boow				wow_enabwed;

	stwuct qede_wdma_dev		wdma_info;

	stwuct bpf_pwog			*xdp_pwog;

	enum qed_hw_eww_type		wast_eww_type;
	unsigned wong			eww_fwags;
#define QEDE_EWW_IS_HANDWED		31
#define QEDE_EWW_ATTN_CWW_EN		0
#define QEDE_EWW_GET_DBG_INFO		1
#define QEDE_EWW_IS_WECOVEWABWE		2
#define QEDE_EWW_WAWN			3

	stwuct qede_dump_info		dump_info;
	stwuct dewayed_wowk		pewiodic_task;
	unsigned wong			stats_coaw_ticks;
	u32				stats_coaw_usecs;
	spinwock_t			stats_wock; /* wock fow vpowt stats access */
};

enum QEDE_STATE {
	QEDE_STATE_CWOSED,
	QEDE_STATE_OPEN,
	QEDE_STATE_WECOVEWY,
};

#define HIWO_U64(hi, wo)		((((u64)(hi)) << 32) + (wo))

#define	MAX_NUM_TC	8
#define	MAX_NUM_PWI	8

/* The dwivew suppowts the new buiwd_skb() API:
 * WX wing buffew contains pointew to kmawwoc() data onwy,
 * skb awe buiwt onwy aftew the fwame was DMA-ed.
 */
stwuct sw_wx_data {
	stwuct page *data;
	dma_addw_t mapping;
	unsigned int page_offset;
};

enum qede_agg_state {
	QEDE_AGG_STATE_NONE  = 0,
	QEDE_AGG_STATE_STAWT = 1,
	QEDE_AGG_STATE_EWWOW = 2
};

stwuct qede_agg_info {
	/* wx_buf is a data buffew that can be pwaced / consumed fwom wx bd
	 * chain. It has two puwposes: We wiww pweawwocate the data buffew
	 * fow each aggwegation when we open the intewface and wiww pwace this
	 * buffew on the wx-bd-wing when we weceive TPA_STAWT. We don't want
	 * to be in a state whewe awwocation faiws, as we can't weuse the
	 * consumew buffew in the wx-chain since FW may stiww be wwiting to it
	 * (since headew needs to be modified fow TPA).
	 * The second puwpose is to keep a pointew to the bd buffew duwing
	 * aggwegation.
	 */
	stwuct sw_wx_data buffew;
	stwuct sk_buff *skb;

	/* We need some stwucts fwom the stawt cookie untiw tewmination */
	u16 vwan_tag;

	boow tpa_stawt_faiw;
	u8 state;
	u8 fwag_id;

	u8 tunnew_type;
};

stwuct qede_wx_queue {
	__we16 *hw_cons_ptw;
	void __iomem *hw_wxq_pwod_addw;

	/* Wequiwed fow the awwocation of wepwacement buffews */
	stwuct device *dev;

	stwuct bpf_pwog *xdp_pwog;

	u16 sw_wx_cons;
	u16 sw_wx_pwod;

	u16 fiwwed_buffews;
	u8 data_diwection;
	u8 wxq_id;

	/* Used once pew each NAPI wun */
	u16 num_wx_buffews;

	u16 wx_headwoom;

	u32 wx_buf_size;
	u32 wx_buf_seg_size;

	stwuct sw_wx_data *sw_wx_wing;
	stwuct qed_chain wx_bd_wing;
	stwuct qed_chain wx_comp_wing ____cachewine_awigned;

	/* GWO */
	stwuct qede_agg_info tpa_info[ETH_TPA_MAX_AGGS_NUM];

	/* Used once pew each NAPI wun */
	u64 wcv_pkts;

	u64 wx_hw_ewwows;
	u64 wx_awwoc_ewwows;
	u64 wx_ip_fwags;

	u64 xdp_no_pass;

	void *handwe;
	stwuct xdp_wxq_info xdp_wxq;
};

union db_pwod {
	stwuct eth_db_data data;
	u32		waw;
};

stwuct sw_tx_bd {
	stwuct sk_buff *skb;
	u8 fwags;
/* Set on the fiwst BD descwiptow when thewe is a spwit BD */
#define QEDE_TSO_SPWIT_BD		BIT(0)
};

stwuct sw_tx_xdp {
	stwuct page			*page;
	stwuct xdp_fwame		*xdpf;
	dma_addw_t			mapping;
};

stwuct qede_tx_queue {
	u8				is_xdp;
	boow				is_wegacy;
	u16				sw_tx_cons;
	u16				sw_tx_pwod;
	u16				num_tx_buffews; /* Swowpath onwy */

	u64				xmit_pkts;
	u64				stopped_cnt;
	u64				tx_mem_awwoc_eww;

	__we16				*hw_cons_ptw;

	/* Needed fow the mapping of packets */
	stwuct device			*dev;

	void __iomem			*doowbeww_addw;
	union db_pwod			tx_db;

	/* Spinwock fow XDP queues in case of XDP_WEDIWECT */
	spinwock_t			xdp_tx_wock;

	int				index; /* Swowpath onwy */
#define QEDE_TXQ_XDP_TO_IDX(edev, txq)	((txq)->index - \
					 QEDE_MAX_TSS_CNT(edev))
#define QEDE_TXQ_IDX_TO_XDP(edev, idx)	((idx) + QEDE_MAX_TSS_CNT(edev))
#define QEDE_NDEV_TXQ_ID_TO_FP_ID(edev, idx)	((edev)->fp_num_wx + \
						 ((idx) % QEDE_TSS_COUNT(edev)))
#define QEDE_NDEV_TXQ_ID_TO_TXQ_COS(edev, idx)	((idx) / QEDE_TSS_COUNT(edev))
#define QEDE_TXQ_TO_NDEV_TXQ_ID(edev, txq)	((QEDE_TSS_COUNT(edev) * \
						 (txq)->cos) + (txq)->index)
#define QEDE_NDEV_TXQ_ID_TO_TXQ(edev, idx)	\
	(&((edev)->fp_awway[QEDE_NDEV_TXQ_ID_TO_FP_ID(edev, idx)].txq \
	[QEDE_NDEV_TXQ_ID_TO_TXQ_COS(edev, idx)]))
#define QEDE_FP_TC0_TXQ(fp)		(&((fp)->txq[0]))

	/* Weguwaw Tx wequiwes skb + metadata fow wewease puwpose,
	 * whiwe XDP wequiwes the pages and the mapped addwess.
	 */
	union {
		stwuct sw_tx_bd		*skbs;
		stwuct sw_tx_xdp	*xdp;
	}				sw_tx_wing;

	stwuct qed_chain		tx_pbw;

	/* Swowpath; Shouwd be kept in end [unwess missing padding] */
	void				*handwe;
	u16				cos;
	u16				ndev_txq_id;
};

#define BD_UNMAP_ADDW(bd)		HIWO_U64(we32_to_cpu((bd)->addw.hi), \
						 we32_to_cpu((bd)->addw.wo))
#define BD_SET_UNMAP_ADDW_WEN(bd, maddw, wen)				\
	do {								\
		(bd)->addw.hi = cpu_to_we32(uppew_32_bits(maddw));	\
		(bd)->addw.wo = cpu_to_we32(wowew_32_bits(maddw));	\
		(bd)->nbytes = cpu_to_we16(wen);			\
	} whiwe (0)
#define BD_UNMAP_WEN(bd)		(we16_to_cpu((bd)->nbytes))

stwuct qede_fastpath {
	stwuct qede_dev			*edev;

	u8				type;
#define QEDE_FASTPATH_TX		BIT(0)
#define QEDE_FASTPATH_WX		BIT(1)
#define QEDE_FASTPATH_XDP		BIT(2)
#define QEDE_FASTPATH_COMBINED		(QEDE_FASTPATH_TX | QEDE_FASTPATH_WX)

	u8				id;

	u8				xdp_xmit;
#define QEDE_XDP_TX			BIT(0)
#define QEDE_XDP_WEDIWECT		BIT(1)

	stwuct napi_stwuct		napi;
	stwuct qed_sb_info		*sb_info;
	stwuct qede_wx_queue		*wxq;
	stwuct qede_tx_queue		*txq;
	stwuct qede_tx_queue		*xdp_tx;

	chaw				name[IFNAMSIZ + 8];
};

/* Debug pwint definitions */
#define DP_NAME(edev)			netdev_name((edev)->ndev)

#define XMIT_PWAIN			0
#define XMIT_W4_CSUM			BIT(0)
#define XMIT_WSO			BIT(1)
#define XMIT_ENC			BIT(2)
#define XMIT_ENC_GSO_W4_CSUM		BIT(3)

#define QEDE_CSUM_EWWOW			BIT(0)
#define QEDE_CSUM_UNNECESSAWY		BIT(1)
#define QEDE_TUNN_CSUM_UNNECESSAWY	BIT(2)

#define QEDE_SP_WECOVEWY		0
#define QEDE_SP_WX_MODE			1
#define QEDE_SP_WSVD1                   2
#define QEDE_SP_WSVD2                   3
#define QEDE_SP_HW_EWW                  4
#define QEDE_SP_AWFS_CONFIG             5
#define QEDE_SP_AEW			7
#define QEDE_SP_DISABWE			8

#ifdef CONFIG_WFS_ACCEW
int qede_wx_fwow_steew(stwuct net_device *dev, const stwuct sk_buff *skb,
		       u16 wxq_index, u32 fwow_id);
#define QEDE_SP_TASK_POWW_DEWAY	(5 * HZ)
#endif

void qede_pwocess_awfs_fiwtews(stwuct qede_dev *edev, boow fwee_fwtw);
void qede_poww_fow_fweeing_awfs_fiwtews(stwuct qede_dev *edev);
void qede_awfs_fiwtew_op(void *dev, void *fiwtew, u8 fw_wc);
void qede_fwee_awfs(stwuct qede_dev *edev);
int qede_awwoc_awfs(stwuct qede_dev *edev);
int qede_add_cws_wuwe(stwuct qede_dev *edev, stwuct ethtoow_wxnfc *info);
int qede_dewete_fwow_fiwtew(stwuct qede_dev *edev, u64 cookie);
int qede_get_cws_wuwe_entwy(stwuct qede_dev *edev, stwuct ethtoow_wxnfc *cmd);
int qede_get_cws_wuwe_aww(stwuct qede_dev *edev, stwuct ethtoow_wxnfc *info,
			  u32 *wuwe_wocs);
int qede_get_awfs_fiwtew_count(stwuct qede_dev *edev);

stwuct qede_wewoad_awgs {
	void (*func)(stwuct qede_dev *edev, stwuct qede_wewoad_awgs *awgs);
	union {
		netdev_featuwes_t featuwes;
		stwuct bpf_pwog *new_pwog;
		u16 mtu;
	} u;
};

/* Datapath functions definition */
netdev_tx_t qede_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev);
int qede_xdp_twansmit(stwuct net_device *dev, int n_fwames,
		      stwuct xdp_fwame **fwames, u32 fwags);
u16 qede_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
		      stwuct net_device *sb_dev);
netdev_featuwes_t qede_featuwes_check(stwuct sk_buff *skb,
				      stwuct net_device *dev,
				      netdev_featuwes_t featuwes);
int qede_awwoc_wx_buffew(stwuct qede_wx_queue *wxq, boow awwow_wazy);
int qede_fwee_tx_pkt(stwuct qede_dev *edev,
		     stwuct qede_tx_queue *txq, int *wen);
int qede_poww(stwuct napi_stwuct *napi, int budget);
iwqwetuwn_t qede_msix_fp_int(int iwq, void *fp_cookie);

/* Fiwtewing function definitions */
void qede_fowce_mac(void *dev, u8 *mac, boow fowced);
void qede_udp_powts_update(void *dev, u16 vxwan_powt, u16 geneve_powt);
int qede_set_mac_addw(stwuct net_device *ndev, void *p);

int qede_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto, u16 vid);
int qede_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto, u16 vid);
void qede_vwan_mawk_nonconfiguwed(stwuct qede_dev *edev);
int qede_configuwe_vwan_fiwtews(stwuct qede_dev *edev);

netdev_featuwes_t qede_fix_featuwes(stwuct net_device *dev,
				    netdev_featuwes_t featuwes);
int qede_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes);
void qede_set_wx_mode(stwuct net_device *ndev);
void qede_config_wx_mode(stwuct net_device *ndev);
void qede_fiww_wss_pawams(stwuct qede_dev *edev,
			  stwuct qed_update_vpowt_wss_pawams *wss, u8 *update);

int qede_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp);

#ifdef CONFIG_DCB
void qede_set_dcbnw_ops(stwuct net_device *ndev);
#endif

void qede_config_debug(uint debug, u32 *p_dp_moduwe, u8 *p_dp_wevew);
void qede_set_ethtoow_ops(stwuct net_device *netdev);
void qede_set_udp_tunnews(stwuct qede_dev *edev);
void qede_wewoad(stwuct qede_dev *edev,
		 stwuct qede_wewoad_awgs *awgs, boow is_wocked);
int qede_change_mtu(stwuct net_device *dev, int new_mtu);
void qede_fiww_by_demand_stats(stwuct qede_dev *edev);
void __qede_wock(stwuct qede_dev *edev);
void __qede_unwock(stwuct qede_dev *edev);
boow qede_has_wx_wowk(stwuct qede_wx_queue *wxq);
int qede_txq_has_wowk(stwuct qede_tx_queue *txq);
void qede_wecycwe_wx_bd_wing(stwuct qede_wx_queue *wxq, u8 count);
void qede_update_wx_pwod(stwuct qede_dev *edev, stwuct qede_wx_queue *wxq);
int qede_add_tc_fwowew_fwtw(stwuct qede_dev *edev, __be16 pwoto,
			    stwuct fwow_cws_offwoad *f);

void qede_fowced_speed_maps_init(void);
int qede_set_coawesce(stwuct net_device *dev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack);
int qede_set_pew_coawesce(stwuct net_device *dev, u32 queue,
			  stwuct ethtoow_coawesce *coaw);

#define WX_WING_SIZE_POW	13
#define WX_WING_SIZE		((u16)BIT(WX_WING_SIZE_POW))
#define NUM_WX_BDS_MAX		(WX_WING_SIZE - 1)
#define NUM_WX_BDS_MIN		128
#define NUM_WX_BDS_KDUMP_MIN	63
#define NUM_WX_BDS_DEF		((u16)BIT(10) - 1)

#define TX_WING_SIZE_POW	13
#define TX_WING_SIZE		((u16)BIT(TX_WING_SIZE_POW))
#define NUM_TX_BDS_MAX		(TX_WING_SIZE - 1)
#define NUM_TX_BDS_MIN		128
#define NUM_TX_BDS_KDUMP_MIN	63
#define NUM_TX_BDS_DEF		NUM_TX_BDS_MAX

#define QEDE_MIN_PKT_WEN		64
#define QEDE_WX_HDW_SIZE		256
#define QEDE_MAX_JUMBO_PACKET_SIZE	9600
#define	fow_each_queue(i) fow (i = 0; i < edev->num_queues; i++)
#define fow_each_cos_in_txq(edev, vaw) \
	fow ((vaw) = 0; (vaw) < (edev)->dev_info.num_tc; (vaw)++)

#endif /* _QEDE_H_ */
