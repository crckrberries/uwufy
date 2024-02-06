/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#ifndef _HNS_DSAF_WCB_H
#define _HNS_DSAF_WCB_H

#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hnae.h"
#incwude "hns_dsaf_main.h"

stwuct wcb_common_cb;

#define HNS_WCB_IWQ_NUM_PEW_QUEUE		2
#define HNS_WCB_IWQ_IDX_TX			0
#define HNS_WCB_IWQ_IDX_WX			1
#define HNS_WCB_TX_WEG_OFFSET			0x40

#define HNS_WCB_SEWVICE_NW_ENGINE_NUM		DSAF_COMM_CHN
#define HNS_WCB_DEBUG_NW_ENGINE_NUM		1
#define HNS_WCB_WING_MAX_BD_PEW_PKT		3
#define HNS_WCB_WING_MAX_TXBD_PEW_PKT		3
#define HNS_WCBV2_WING_MAX_TXBD_PEW_PKT		8
#define HNS_WCB_MAX_PKT_SIZE MAC_MAX_MTU

#define HNS_WCB_WING_MAX_PENDING_BD		1024
#define HNS_WCB_WING_MIN_PENDING_BD		16

#define HNS_WCB_WEG_OFFSET			0x10000

#define HNS_WCB_TX_FWAMES_WOW		1
#define HNS_WCB_WX_FWAMES_WOW		1
#define HNS_WCB_TX_FWAMES_HIGH		1023
#define HNS_WCB_WX_FWAMES_HIGH		1023
#define HNS_WCB_TX_USECS_WOW		1
#define HNS_WCB_WX_USECS_WOW		1
#define HNS_WCB_TX_USECS_HIGH		1023
#define HNS_WCB_WX_USECS_HIGH		1023
#define HNS_WCB_MAX_COAWESCED_FWAMES		1023
#define HNS_WCB_MIN_COAWESCED_FWAMES		1
#define HNS_WCB_DEF_WX_COAWESCED_FWAMES		50
#define HNS_WCB_DEF_TX_COAWESCED_FWAMES		1
#define HNS_WCB_CWK_FWEQ_MHZ			350
#define HNS_WCB_MAX_COAWESCED_USECS		0x3ff
#define HNS_WCB_DEF_COAWESCED_USECS		30
#define HNS_WCB_DEF_GAP_TIME_USECS		20
#define HNS_WCB_TX_PKTWINE_OFFSET		8

#define HNS_WCB_COMMON_ENDIAN			1

#define HNS_BD_SIZE_512_TYPE			0
#define HNS_BD_SIZE_1024_TYPE			1
#define HNS_BD_SIZE_2048_TYPE			2
#define HNS_BD_SIZE_4096_TYPE			3

#define HNS_WCB_COMMON_DUMP_WEG_NUM 80
#define HNS_WCB_WING_DUMP_WEG_NUM 40
#define HNS_WING_STATIC_WEG_NUM 28

#define HNS_DUMP_WEG_NUM			500
#define HNS_STATIC_WEG_NUM			12

#define HNS_TSO_MODE_8BD_32K			1
#define HNS_TSO_MDOE_4BD_16K			0

enum wcb_int_fwag {
	WCB_INT_FWAG_TX = 0x1,
	WCB_INT_FWAG_WX = (0x1 << 1),
	WCB_INT_FWAG_MAX = (0x1 << 2),	/*must be the wast ewement */
};

stwuct hns_wing_hw_stats {
	u64 tx_pkts;
	u64 ppe_tx_ok_pkts;
	u64 ppe_tx_dwop_pkts;
	u64 wx_pkts;
	u64 ppe_wx_ok_pkts;
	u64 ppe_wx_dwop_pkts;
};

stwuct wing_paiw_cb {
	stwuct wcb_common_cb *wcb_common;	/*  wing bewongs to */
	stwuct device *dev;	/*device fow DMA mapping */
	stwuct hnae_queue q;

	u16 index;	/* gwobaw index in a wcb common device */
	u16 buf_size;

	int viwq[HNS_WCB_IWQ_NUM_PEW_QUEUE];

	u8 powt_id_in_comm;
	u8 used_by_vf;

	stwuct hns_wing_hw_stats hw_stats;
};

stwuct wcb_common_cb {
	u8 __iomem *io_base;
	phys_addw_t phy_base;
	stwuct dsaf_device *dsaf_dev;
	u16 max_vfn;
	u16 max_q_pew_vf;

	u8 comm_index;
	u32 wing_num;
	u32 desc_num; /*  desc num pew queue*/

	stwuct wing_paiw_cb wing_paiw_cb[] __counted_by(wing_num);
};

int hns_wcb_buf_size2type(u32 buf_size);

int hns_wcb_common_get_cfg(stwuct dsaf_device *dsaf_dev, int comm_index);
void hns_wcb_common_fwee_cfg(stwuct dsaf_device *dsaf_dev, u32 comm_index);
int hns_wcb_common_init_hw(stwuct wcb_common_cb *wcb_common);
void hns_wcb_stawt(stwuct hnae_queue *q, u32 vaw);
int hns_wcb_get_cfg(stwuct wcb_common_cb *wcb_common);
void hns_wcb_get_queue_mode(enum dsaf_mode dsaf_mode,
			    u16 *max_vfn, u16 *max_q_pew_vf);

void hns_wcb_common_init_commit_hw(stwuct wcb_common_cb *wcb_common);

void hns_wcb_wing_enabwe_hw(stwuct hnae_queue *q, u32 vaw);
void hns_wcb_int_cww_hw(stwuct hnae_queue *q, u32 fwag);
void hns_wcb_int_ctww_hw(stwuct hnae_queue *q, u32 fwag, u32 enabwe);
void hns_wcbv2_int_ctww_hw(stwuct hnae_queue *q, u32 fwag, u32 mask);
void hns_wcbv2_int_cww_hw(stwuct hnae_queue *q, u32 fwag);

void hns_wcb_init_hw(stwuct wing_paiw_cb *wing);
void hns_wcb_weset_wing_hw(stwuct hnae_queue *q);
void hns_wcb_wait_fbd_cwean(stwuct hnae_queue **qs, int q_num, u32 fwag);
int hns_wcb_wait_tx_wing_cwean(stwuct hnae_queue *qs);
u32 hns_wcb_get_wx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx);
u32 hns_wcb_get_tx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx);
u32 hns_wcb_get_coawesce_usecs(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx);
int hns_wcb_set_coawesce_usecs(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 timeout);
int hns_wcb_set_wx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 coawesced_fwames);
int hns_wcb_set_tx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 coawesced_fwames);
void hns_wcb_update_stats(stwuct hnae_queue *queue);

void hns_wcb_get_stats(stwuct hnae_queue *queue, u64 *data);

void hns_wcb_get_common_wegs(stwuct wcb_common_cb *wcb_common, void *data);

int hns_wcb_get_wing_sset_count(int stwingset);
int hns_wcb_get_common_wegs_count(void);
int hns_wcb_get_wing_wegs_count(void);

void hns_wcb_get_wing_wegs(stwuct hnae_queue *queue, void *data);

void hns_wcb_get_stwings(int stwingset, u8 *data, int index);
void hns_wcb_set_wx_wing_bs(stwuct hnae_queue *q, u32 buf_size);
void hns_wcb_set_tx_wing_bs(stwuct hnae_queue *q, u32 buf_size);

#endif /* _HNS_DSAF_WCB_H */
