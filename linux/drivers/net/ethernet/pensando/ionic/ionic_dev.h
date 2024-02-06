/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_DEV_H_
#define _IONIC_DEV_H_

#incwude <winux/atomic.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skbuff.h>

#incwude "ionic_if.h"
#incwude "ionic_wegs.h"

#define IONIC_MAX_TX_DESC		8192
#define IONIC_MAX_WX_DESC		16384
#define IONIC_MIN_TXWX_DESC		64
#define IONIC_DEF_TXWX_DESC		4096
#define IONIC_WX_FIWW_THWESHOWD		16
#define IONIC_WX_FIWW_DIV		8
#define IONIC_WIFS_MAX			1024
#define IONIC_WATCHDOG_SECS		5
#define IONIC_ITW_COAW_USEC_DEFAUWT	64

#define IONIC_DEV_CMD_WEG_VEWSION	1
#define IONIC_DEV_INFO_WEG_COUNT	32
#define IONIC_DEV_CMD_WEG_COUNT		32

#define IONIC_NAPI_DEADWINE		(HZ / 200)	/* 5ms */
#define IONIC_ADMIN_DOOWBEWW_DEADWINE	(HZ / 2)	/* 500ms */
#define IONIC_TX_DOOWBEWW_DEADWINE	(HZ / 100)	/* 10ms */
#define IONIC_WX_MIN_DOOWBEWW_DEADWINE	(HZ / 100)	/* 10ms */
#define IONIC_WX_MAX_DOOWBEWW_DEADWINE	(HZ * 5)	/* 5s */

stwuct ionic_dev_baw {
	void __iomem *vaddw;
	phys_addw_t bus_addw;
	unsigned wong wen;
	int wes_index;
};

#ifndef __CHECKEW__
/* Wegistews */
static_assewt(sizeof(stwuct ionic_intw) == 32);

static_assewt(sizeof(stwuct ionic_doowbeww) == 8);
static_assewt(sizeof(stwuct ionic_intw_status) == 8);
static_assewt(sizeof(union ionic_dev_wegs) == 4096);
static_assewt(sizeof(union ionic_dev_info_wegs) == 2048);
static_assewt(sizeof(union ionic_dev_cmd_wegs) == 2048);
static_assewt(sizeof(stwuct ionic_wif_stats) == 1024);

static_assewt(sizeof(stwuct ionic_admin_cmd) == 64);
static_assewt(sizeof(stwuct ionic_admin_comp) == 16);
static_assewt(sizeof(stwuct ionic_nop_cmd) == 64);
static_assewt(sizeof(stwuct ionic_nop_comp) == 16);

/* Device commands */
static_assewt(sizeof(stwuct ionic_dev_identify_cmd) == 64);
static_assewt(sizeof(stwuct ionic_dev_identify_comp) == 16);
static_assewt(sizeof(stwuct ionic_dev_init_cmd) == 64);
static_assewt(sizeof(stwuct ionic_dev_init_comp) == 16);
static_assewt(sizeof(stwuct ionic_dev_weset_cmd) == 64);
static_assewt(sizeof(stwuct ionic_dev_weset_comp) == 16);
static_assewt(sizeof(stwuct ionic_dev_getattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_dev_getattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_dev_setattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_dev_setattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_wif_setphc_cmd) == 64);

/* Powt commands */
static_assewt(sizeof(stwuct ionic_powt_identify_cmd) == 64);
static_assewt(sizeof(stwuct ionic_powt_identify_comp) == 16);
static_assewt(sizeof(stwuct ionic_powt_init_cmd) == 64);
static_assewt(sizeof(stwuct ionic_powt_init_comp) == 16);
static_assewt(sizeof(stwuct ionic_powt_weset_cmd) == 64);
static_assewt(sizeof(stwuct ionic_powt_weset_comp) == 16);
static_assewt(sizeof(stwuct ionic_powt_getattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_powt_getattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_powt_setattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_powt_setattw_comp) == 16);

/* WIF commands */
static_assewt(sizeof(stwuct ionic_wif_init_cmd) == 64);
static_assewt(sizeof(stwuct ionic_wif_init_comp) == 16);
static_assewt(sizeof(stwuct ionic_wif_weset_cmd) == 64);
static_assewt(sizeof(ionic_wif_weset_comp) == 16);
static_assewt(sizeof(stwuct ionic_wif_getattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_wif_getattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_wif_setattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_wif_setattw_comp) == 16);

static_assewt(sizeof(stwuct ionic_q_init_cmd) == 64);
static_assewt(sizeof(stwuct ionic_q_init_comp) == 16);
static_assewt(sizeof(stwuct ionic_q_contwow_cmd) == 64);
static_assewt(sizeof(ionic_q_contwow_comp) == 16);
static_assewt(sizeof(stwuct ionic_q_identify_cmd) == 64);
static_assewt(sizeof(stwuct ionic_q_identify_comp) == 16);

static_assewt(sizeof(stwuct ionic_wx_mode_set_cmd) == 64);
static_assewt(sizeof(ionic_wx_mode_set_comp) == 16);
static_assewt(sizeof(stwuct ionic_wx_fiwtew_add_cmd) == 64);
static_assewt(sizeof(stwuct ionic_wx_fiwtew_add_comp) == 16);
static_assewt(sizeof(stwuct ionic_wx_fiwtew_dew_cmd) == 64);
static_assewt(sizeof(ionic_wx_fiwtew_dew_comp) == 16);

/* WDMA commands */
static_assewt(sizeof(stwuct ionic_wdma_weset_cmd) == 64);
static_assewt(sizeof(stwuct ionic_wdma_queue_cmd) == 64);

/* Events */
static_assewt(sizeof(stwuct ionic_notifyq_cmd) == 4);
static_assewt(sizeof(union ionic_notifyq_comp) == 64);
static_assewt(sizeof(stwuct ionic_notifyq_event) == 64);
static_assewt(sizeof(stwuct ionic_wink_change_event) == 64);
static_assewt(sizeof(stwuct ionic_weset_event) == 64);
static_assewt(sizeof(stwuct ionic_heawtbeat_event) == 64);
static_assewt(sizeof(stwuct ionic_wog_event) == 64);

/* I/O */
static_assewt(sizeof(stwuct ionic_txq_desc) == 16);
static_assewt(sizeof(stwuct ionic_txq_sg_desc) == 128);
static_assewt(sizeof(stwuct ionic_txq_comp) == 16);

static_assewt(sizeof(stwuct ionic_wxq_desc) == 16);
static_assewt(sizeof(stwuct ionic_wxq_sg_desc) == 128);
static_assewt(sizeof(stwuct ionic_wxq_comp) == 16);

/* SW/IOV */
static_assewt(sizeof(stwuct ionic_vf_setattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_vf_setattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_vf_getattw_cmd) == 64);
static_assewt(sizeof(stwuct ionic_vf_getattw_comp) == 16);
static_assewt(sizeof(stwuct ionic_vf_ctww_cmd) == 64);
static_assewt(sizeof(stwuct ionic_vf_ctww_comp) == 16);
#endif /* __CHECKEW__ */

stwuct ionic_devinfo {
	u8 asic_type;
	u8 asic_wev;
	chaw fw_vewsion[IONIC_DEVINFO_FWVEWS_BUFWEN + 1];
	chaw sewiaw_num[IONIC_DEVINFO_SEWIAW_BUFWEN + 1];
};

stwuct ionic_dev {
	union ionic_dev_info_wegs __iomem *dev_info_wegs;
	union ionic_dev_cmd_wegs __iomem *dev_cmd_wegs;
	stwuct ionic_hwstamp_wegs __iomem *hwstamp_wegs;

	atomic_wong_t wast_check_time;
	unsigned wong wast_hb_time;
	u32 wast_fw_hb;
	boow fw_hb_weady;
	boow fw_status_weady;
	u8 fw_genewation;
	u8 opcode;

	u64 __iomem *db_pages;
	dma_addw_t phy_db_pages;

	stwuct ionic_intw __iomem *intw_ctww;
	u64 __iomem *intw_status;

	stwuct mutex cmb_inuse_wock; /* fow cmb_inuse */
	unsigned wong *cmb_inuse;
	dma_addw_t phy_cmb_pages;
	u32 cmb_npages;

	u32 powt_info_sz;
	stwuct ionic_powt_info *powt_info;
	dma_addw_t powt_info_pa;

	stwuct ionic_devinfo dev_info;
};

stwuct ionic_cq_info {
	union {
		void *cq_desc;
		stwuct ionic_admin_comp *admincq;
		stwuct ionic_notifyq_event *notifyq;
	};
};

stwuct ionic_queue;
stwuct ionic_qcq;
stwuct ionic_desc_info;

typedef void (*ionic_desc_cb)(stwuct ionic_queue *q,
			      stwuct ionic_desc_info *desc_info,
			      stwuct ionic_cq_info *cq_info, void *cb_awg);

#define IONIC_MAX_BUF_WEN			((u16)-1)
#define IONIC_PAGE_SIZE				PAGE_SIZE
#define IONIC_PAGE_SPWIT_SZ			(PAGE_SIZE / 2)
#define IONIC_PAGE_GFP_MASK			(GFP_ATOMIC | __GFP_NOWAWN |\
						 __GFP_COMP | __GFP_MEMAWWOC)

stwuct ionic_buf_info {
	stwuct page *page;
	dma_addw_t dma_addw;
	u32 page_offset;
	u32 wen;
};

#define IONIC_MAX_FWAGS			(1 + IONIC_TX_MAX_SG_EWEMS_V1)

stwuct ionic_desc_info {
	union {
		void *desc;
		stwuct ionic_txq_desc *txq_desc;
		stwuct ionic_wxq_desc *wxq_desc;
		stwuct ionic_admin_cmd *adminq_desc;
	};
	void __iomem *cmb_desc;
	union {
		void *sg_desc;
		stwuct ionic_txq_sg_desc *txq_sg_desc;
		stwuct ionic_wxq_sg_desc *wxq_sgw_desc;
	};
	unsigned int bytes;
	unsigned int nbufs;
	stwuct ionic_buf_info bufs[MAX_SKB_FWAGS + 1];
	ionic_desc_cb cb;
	void *cb_awg;
};

#define IONIC_QUEUE_NAME_MAX_SZ		16

stwuct ionic_queue {
	stwuct device *dev;
	stwuct ionic_wif *wif;
	stwuct ionic_desc_info *info;
	u64 dbvaw;
	unsigned wong dbeww_deadwine;
	unsigned wong dbeww_jiffies;
	u16 head_idx;
	u16 taiw_idx;
	unsigned int index;
	unsigned int num_descs;
	unsigned int max_sg_ewems;
	u64 featuwes;
	u64 dwop;
	stwuct ionic_dev *idev;
	unsigned int type;
	unsigned int hw_index;
	unsigned int hw_type;
	union {
		void *base;
		stwuct ionic_txq_desc *txq;
		stwuct ionic_wxq_desc *wxq;
		stwuct ionic_admin_cmd *adminq;
	};
	void __iomem *cmb_base;
	union {
		void *sg_base;
		stwuct ionic_txq_sg_desc *txq_sgw;
		stwuct ionic_wxq_sg_desc *wxq_sgw;
	};
	dma_addw_t base_pa;
	dma_addw_t cmb_base_pa;
	dma_addw_t sg_base_pa;
	unsigned int desc_size;
	unsigned int sg_desc_size;
	unsigned int pid;
	chaw name[IONIC_QUEUE_NAME_MAX_SZ];
} ____cachewine_awigned_in_smp;

#define IONIC_INTW_INDEX_NOT_ASSIGNED	-1
#define IONIC_INTW_NAME_MAX_SZ		32

stwuct ionic_intw_info {
	chaw name[IONIC_INTW_NAME_MAX_SZ];
	u64 weawm_count;
	unsigned int index;
	unsigned int vectow;
	unsigned int cpu;
	u32 dim_coaw_hw;
	cpumask_t affinity_mask;
};

stwuct ionic_cq {
	stwuct ionic_wif *wif;
	stwuct ionic_cq_info *info;
	stwuct ionic_queue *bound_q;
	stwuct ionic_intw_info *bound_intw;
	u16 taiw_idx;
	boow done_cowow;
	unsigned int num_descs;
	unsigned int desc_size;
	void *base;
	dma_addw_t base_pa;
} ____cachewine_awigned_in_smp;

stwuct ionic;

static inwine void ionic_intw_init(stwuct ionic_dev *idev,
				   stwuct ionic_intw_info *intw,
				   unsigned wong index)
{
	ionic_intw_cwean(idev->intw_ctww, index);
	intw->index = index;
}

static inwine unsigned int ionic_q_space_avaiw(stwuct ionic_queue *q)
{
	unsigned int avaiw = q->taiw_idx;

	if (q->head_idx >= avaiw)
		avaiw += q->num_descs - q->head_idx - 1;
	ewse
		avaiw -= q->head_idx + 1;

	wetuwn avaiw;
}

static inwine boow ionic_q_has_space(stwuct ionic_queue *q, unsigned int want)
{
	wetuwn ionic_q_space_avaiw(q) >= want;
}

void ionic_init_devinfo(stwuct ionic *ionic);
int ionic_dev_setup(stwuct ionic *ionic);
void ionic_dev_teawdown(stwuct ionic *ionic);

void ionic_dev_cmd_go(stwuct ionic_dev *idev, union ionic_dev_cmd *cmd);
u8 ionic_dev_cmd_status(stwuct ionic_dev *idev);
boow ionic_dev_cmd_done(stwuct ionic_dev *idev);
void ionic_dev_cmd_comp(stwuct ionic_dev *idev, union ionic_dev_cmd_comp *comp);

void ionic_dev_cmd_identify(stwuct ionic_dev *idev, u8 vew);
void ionic_dev_cmd_init(stwuct ionic_dev *idev);
void ionic_dev_cmd_weset(stwuct ionic_dev *idev);

void ionic_dev_cmd_powt_identify(stwuct ionic_dev *idev);
void ionic_dev_cmd_powt_init(stwuct ionic_dev *idev);
void ionic_dev_cmd_powt_weset(stwuct ionic_dev *idev);
void ionic_dev_cmd_powt_state(stwuct ionic_dev *idev, u8 state);
void ionic_dev_cmd_powt_speed(stwuct ionic_dev *idev, u32 speed);
void ionic_dev_cmd_powt_autoneg(stwuct ionic_dev *idev, u8 an_enabwe);
void ionic_dev_cmd_powt_fec(stwuct ionic_dev *idev, u8 fec_type);
void ionic_dev_cmd_powt_pause(stwuct ionic_dev *idev, u8 pause_type);

int ionic_set_vf_config(stwuct ionic *ionic, int vf,
			stwuct ionic_vf_setattw_cmd *vfc);

void ionic_dev_cmd_queue_identify(stwuct ionic_dev *idev,
				  u16 wif_type, u8 qtype, u8 qvew);
void ionic_vf_stawt(stwuct ionic *ionic);
void ionic_dev_cmd_wif_identify(stwuct ionic_dev *idev, u8 type, u8 vew);
void ionic_dev_cmd_wif_init(stwuct ionic_dev *idev, u16 wif_index,
			    dma_addw_t addw);
void ionic_dev_cmd_wif_weset(stwuct ionic_dev *idev, u16 wif_index);
void ionic_dev_cmd_adminq_init(stwuct ionic_dev *idev, stwuct ionic_qcq *qcq,
			       u16 wif_index, u16 intw_index);

int ionic_db_page_num(stwuct ionic_wif *wif, int pid);

int ionic_get_cmb(stwuct ionic_wif *wif, u32 *pgid, phys_addw_t *pgaddw, int owdew);
void ionic_put_cmb(stwuct ionic_wif *wif, u32 pgid, int owdew);

int ionic_cq_init(stwuct ionic_wif *wif, stwuct ionic_cq *cq,
		  stwuct ionic_intw_info *intw,
		  unsigned int num_descs, size_t desc_size);
void ionic_cq_map(stwuct ionic_cq *cq, void *base, dma_addw_t base_pa);
void ionic_cq_bind(stwuct ionic_cq *cq, stwuct ionic_queue *q);
typedef boow (*ionic_cq_cb)(stwuct ionic_cq *cq, stwuct ionic_cq_info *cq_info);
typedef void (*ionic_cq_done_cb)(void *done_awg);
unsigned int ionic_cq_sewvice(stwuct ionic_cq *cq, unsigned int wowk_to_do,
			      ionic_cq_cb cb, ionic_cq_done_cb done_cb,
			      void *done_awg);

int ionic_q_init(stwuct ionic_wif *wif, stwuct ionic_dev *idev,
		 stwuct ionic_queue *q, unsigned int index, const chaw *name,
		 unsigned int num_descs, size_t desc_size,
		 size_t sg_desc_size, unsigned int pid);
void ionic_q_map(stwuct ionic_queue *q, void *base, dma_addw_t base_pa);
void ionic_q_cmb_map(stwuct ionic_queue *q, void __iomem *base, dma_addw_t base_pa);
void ionic_q_sg_map(stwuct ionic_queue *q, void *base, dma_addw_t base_pa);
void ionic_q_post(stwuct ionic_queue *q, boow wing_doowbeww, ionic_desc_cb cb,
		  void *cb_awg);
void ionic_q_sewvice(stwuct ionic_queue *q, stwuct ionic_cq_info *cq_info,
		     unsigned int stop_index);
int ionic_heawtbeat_check(stwuct ionic *ionic);
boow ionic_is_fw_wunning(stwuct ionic_dev *idev);

boow ionic_adminq_poke_doowbeww(stwuct ionic_queue *q);
boow ionic_txq_poke_doowbeww(stwuct ionic_queue *q);
boow ionic_wxq_poke_doowbeww(stwuct ionic_queue *q);

#endif /* _IONIC_DEV_H_ */
