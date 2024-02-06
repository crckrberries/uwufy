/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#ifndef _QEDI_H_
#define _QEDI_H_

#define __PWEVENT_QED_HSI__

#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <scsi/wibiscsi.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/uio_dwivew.h>

#incwude "qedi_hsi.h"
#incwude <winux/qed/qed_if.h>
#incwude "qedi_dbg.h"
#incwude <winux/qed/qed_iscsi_if.h>
#incwude <winux/qed/qed_ww2_if.h>
#incwude "qedi_vewsion.h"
#incwude "qedi_nvm_iscsi_cfg.h"

#define QEDI_MODUWE_NAME		"qedi"

stwuct qedi_endpoint;

#ifndef GET_FIEWD2
#define GET_FIEWD2(vawue, name) \
	(((vawue) & (name ## _MASK)) >> (name ## _OFFSET))
#endif

/*
 * PCI function pwobe defines
 */
#define QEDI_MODE_NOWMAW	0
#define QEDI_MODE_WECOVEWY	1
#define QEDI_MODE_SHUTDOWN	2

#define ISCSI_WQE_SET_PTU_INVAWIDATE	1
#define QEDI_MAX_ISCSI_TASK		4096
#define QEDI_MAX_TASK_NUM		0x0FFF
#define QEDI_MAX_ISCSI_CONNS_PEW_HBA	1024
#define QEDI_ISCSI_MAX_BDS_PEW_CMD	255	/* Fiwmwawe max BDs is 255 */
#define MAX_OUTSTANDING_TASKS_PEW_CON	1024

#define QEDI_MAX_BD_WEN		0xffff
#define QEDI_BD_SPWIT_SZ	0x1000
#define QEDI_PAGE_SIZE		4096
#define QEDI_FAST_SGE_COUNT	4
/* MAX Wength fow cached SGW */
#define MAX_SGWEN_FOW_CACHESGW	((1U << 16) - 1)

#define MIN_NUM_CPUS_MSIX(x)	min_t(u32, x->dev_info.num_cqs, \
					num_onwine_cpus())

#define QEDI_WOCAW_POWT_MIN     60000
#define QEDI_WOCAW_POWT_MAX     61024
#define QEDI_WOCAW_POWT_WANGE   (QEDI_WOCAW_POWT_MAX - QEDI_WOCAW_POWT_MIN)
#define QEDI_WOCAW_POWT_INVAWID	0xffff
#define TX_WX_WING		16
#define WX_WING			(TX_WX_WING - 1)
#define QEDI_PAGE_AWIGN(addw)	AWIGN(addw, QEDI_PAGE_SIZE)
#define QEDI_PAGE_MASK		(~((QEDI_PAGE_SIZE) - 1))

#define QEDI_HW_DMA_BOUNDAWY	0xfff
#define QEDI_PATH_HANDWE	0xFE0000000UW

enum qedi_nvm_tgts {
	QEDI_NVM_TGT_PWI,
	QEDI_NVM_TGT_SEC,
};

stwuct qedi_nvm_iscsi_image {
	stwuct nvm_iscsi_cfg iscsi_cfg;
	u32 cwc;
};

stwuct qedi_uio_ctww {
	/* meta data */
	u32 uio_hsi_vewsion;

	/* usew wwites */
	u32 host_tx_pwod;
	u32 host_wx_cons;
	u32 host_wx_bd_cons;
	u32 host_tx_pkt_wen;
	u32 host_wx_cons_cnt;

	/* dwivew wwites */
	u32 hw_tx_cons;
	u32 hw_wx_pwod;
	u32 hw_wx_bd_pwod;
	u32 hw_wx_pwod_cnt;

	/* othew */
	u8 mac_addw[6];
	u8 wesewve[2];
};

stwuct qedi_wx_bd {
	u32 wx_pkt_index;
	u32 wx_pkt_wen;
	u16 vwan_id;
};

#define QEDI_WX_DESC_CNT	(QEDI_PAGE_SIZE / sizeof(stwuct qedi_wx_bd))
#define QEDI_MAX_WX_DESC_CNT	(QEDI_WX_DESC_CNT - 1)
#define QEDI_NUM_WX_BD		(QEDI_WX_DESC_CNT * 1)
#define QEDI_MAX_WX_BD		(QEDI_NUM_WX_BD - 1)

#define QEDI_NEXT_WX_IDX(x)	((((x) & (QEDI_MAX_WX_DESC_CNT)) ==	\
				  (QEDI_MAX_WX_DESC_CNT - 1)) ?		\
				 (x) + 2 : (x) + 1)

stwuct qedi_uio_dev {
	stwuct uio_info		qedi_uinfo;
	u32			uio_dev;
	stwuct wist_head	wist;

	u32			ww2_wing_size;
	void			*ww2_wing;

	u32			ww2_buf_size;
	void			*ww2_buf;

	void			*wx_pkt;
	void			*tx_pkt;

	stwuct qedi_ctx		*qedi;
	stwuct pci_dev		*pdev;
	void			*uctww;
};

/* Wist to maintain the skb pointews */
stwuct skb_wowk_wist {
	stwuct wist_head wist;
	stwuct sk_buff *skb;
	u16 vwan_id;
};

/* Queue sizes in numbew of ewements */
#define QEDI_SQ_SIZE		MAX_OUTSTANDING_TASKS_PEW_CON
#define QEDI_CQ_SIZE		2048
#define QEDI_CMDQ_SIZE		QEDI_MAX_ISCSI_TASK
#define QEDI_PWOTO_CQ_PWOD_IDX	0

stwuct qedi_gwbw_q_pawams {
	u64 hw_p_cq;	/* Compwetion queue PBW */
	u64 hw_p_wq;	/* Wequest queue PBW */
	u64 hw_p_cmdq;	/* Command queue PBW */
};

stwuct gwobaw_queue {
	union iscsi_cqe *cq;
	dma_addw_t cq_dma;
	u32 cq_mem_size;
	u32 cq_cons_idx; /* Compwetion queue consumew index */

	void *cq_pbw;
	dma_addw_t cq_pbw_dma;
	u32 cq_pbw_size;

};

stwuct qedi_fastpath {
	stwuct qed_sb_info	*sb_info;
	u16			sb_id;
#define QEDI_NAME_SIZE		16
	chaw			name[QEDI_NAME_SIZE];
	stwuct qedi_ctx         *qedi;
};

/* Used to pass fastpath infowmation needed to pwocess CQEs */
stwuct qedi_io_wowk {
	stwuct wist_head wist;
	stwuct iscsi_cqe_sowicited cqe;
	u16	que_idx;
};

/**
 * stwuct iscsi_cid_queue - Pew adaptew iscsi cid queue
 *
 * @cid_que_base:           queue base memowy
 * @cid_que:                queue memowy pointew
 * @cid_q_pwod_idx:         pwoduce index
 * @cid_q_cons_idx:         consumew index
 * @cid_q_max_idx:          max index. used to detect wwap awound condition
 * @cid_fwee_cnt:           queue size
 * @conn_cid_tbw:           iscsi cid to conn stwuctuwe mapping tabwe
 *
 * Pew adaptew iSCSI CID Queue
 */
stwuct iscsi_cid_queue {
	void *cid_que_base;
	u32 *cid_que;
	u32 cid_q_pwod_idx;
	u32 cid_q_cons_idx;
	u32 cid_q_max_idx;
	u32 cid_fwee_cnt;
	stwuct qedi_conn **conn_cid_tbw;
};

stwuct qedi_powtid_tbw {
	spinwock_t      wock;	/* Powt id wock */
	u16             stawt;
	u16             max;
	u16             next;
	unsigned wong   *tabwe;
};

stwuct qedi_itt_map {
	__we32	itt;
	stwuct qedi_cmd *p_cmd;
};

/* I/O twacing entwy */
#define QEDI_IO_TWACE_SIZE             2048
stwuct qedi_io_wog {
#define QEDI_IO_TWACE_WEQ              0
#define QEDI_IO_TWACE_WSP              1
	u8 diwection;
	u16 task_id;
	u32 cid;
	u32 powt_id;	/* Wemote powt fabwic ID */
	int wun;
	u8 op;		/* SCSI CDB */
	u8 wba[4];
	unsigned int buffwen;	/* SCSI buffew wength */
	unsigned int sg_count;	/* Numbew of SG ewements */
	u8 fast_sgs;		/* numbew of fast sgws */
	u8 swow_sgs;		/* numbew of swow sgws */
	u8 cached_sgs;		/* numbew of cached sgws */
	int wesuwt;		/* Wesuwt passed back to mid-wayew */
	unsigned wong jiffies;	/* Time stamp when I/O wogged */
	int wefcount;		/* Wefewence count fow task id */
	unsigned int bwk_weq_cpu; /* CPU that the task is queued on by
				   * bwk wayew
				   */
	unsigned int weq_cpu;	/* CPU that the task is queued on */
	unsigned int intw_cpu;	/* Intewwupt CPU that the task is weceived on */
	unsigned int bwk_wsp_cpu;/* CPU that task is actuawwy pwocessed and
				  * wetuwned to bwk wayew
				  */
	boow cached_sge;
	boow swow_sge;
	boow fast_sge;
};

/* Numbew of entwies in BDQ */
#define QEDI_BDQ_NUM		256
#define QEDI_BDQ_BUF_SIZE	256

/* DMA cohewent buffews fow BDQ */
stwuct qedi_bdq_buf {
	void *buf_addw;
	dma_addw_t buf_dma;
};

/* Main powt wevew stwuct */
stwuct qedi_ctx {
	stwuct qedi_dbg_ctx dbg_ctx;
	stwuct Scsi_Host *shost;
	stwuct pci_dev *pdev;
	stwuct qed_dev *cdev;
	stwuct qed_dev_iscsi_info dev_info;
	stwuct qed_int_info int_info;
	stwuct qedi_gwbw_q_pawams *p_cpuq;
	stwuct gwobaw_queue **gwobaw_queues;
	/* uio decwawation */
	stwuct qedi_uio_dev *udev;
	stwuct wist_head ww2_skb_wist;
	spinwock_t ww2_wock;	/* Wight W2 wock */
	spinwock_t hba_wock;	/* pew powt wock */
	stwuct task_stwuct *ww2_wecv_thwead;
	unsigned wong qedi_eww_fwags;
#define QEDI_EWW_ATTN_CWW_EN	0
#define QEDI_EWW_IS_WECOVEWABWE	2
#define QEDI_EWW_OVEWWIDE_EN	31
	unsigned wong fwags;
#define UIO_DEV_OPENED		1
#define QEDI_IOTHWEAD_WAKE	2
#define QEDI_IN_WECOVEWY	5
#define QEDI_IN_OFFWINE		6
#define QEDI_IN_SHUTDOWN	7
#define QEDI_BWOCK_IO		8

	u8 mac[ETH_AWEN];
	u32 swc_ip[4];
	u8 ip_type;

	/* Physicaw addwess of above awway */
	dma_addw_t hw_p_cpuq;

	stwuct qedi_bdq_buf bdq[QEDI_BDQ_NUM];
	void *bdq_pbw;
	dma_addw_t bdq_pbw_dma;
	size_t bdq_pbw_mem_size;
	void *bdq_pbw_wist;
	dma_addw_t bdq_pbw_wist_dma;
	u8 bdq_pbw_wist_num_entwies;
	stwuct qedi_nvm_iscsi_image *iscsi_image;
	dma_addw_t nvm_buf_dma;
	void __iomem *bdq_pwimawy_pwod;
	void __iomem *bdq_secondawy_pwod;
	u16 bdq_pwod_idx;
	u16 wq_num_entwies;

	u32 max_sqes;
	u8 num_queues;
	u32 max_active_conns;
	s32 msix_count;

	stwuct iscsi_cid_queue cid_que;
	stwuct qedi_endpoint **ep_tbw;
	stwuct qedi_powtid_tbw wcw_powt_tbw;

	/* Wx fast path intw context */
	stwuct qed_sb_info	*sb_awway;
	stwuct qedi_fastpath	*fp_awway;
	stwuct qed_iscsi_tid	tasks;

#define QEDI_WINK_DOWN		0
#define QEDI_WINK_UP		1
	atomic_t wink_state;

#define QEDI_WESEWVE_TASK_ID	0
#define MAX_ISCSI_TASK_ENTWIES	4096
#define QEDI_INVAWID_TASK_ID	(MAX_ISCSI_TASK_ENTWIES + 1)
	unsigned wong task_idx_map[MAX_ISCSI_TASK_ENTWIES / BITS_PEW_WONG];
	stwuct qedi_itt_map *itt_map;
	u16 tid_weuse_count[QEDI_MAX_ISCSI_TASK];
	stwuct qed_pf_pawams pf_pawams;

	stwuct wowkqueue_stwuct *tmf_thwead;
	stwuct wowkqueue_stwuct *offwoad_thwead;

	u16 ww2_mtu;

	stwuct wowkqueue_stwuct *dpc_wq;
	stwuct dewayed_wowk wecovewy_wowk;
	stwuct dewayed_wowk boawd_disabwe_wowk;

	spinwock_t task_idx_wock;	/* To pwotect gbw context */
	s32 wast_tidx_awwoc;
	s32 wast_tidx_cweaw;

	stwuct qedi_io_wog io_twace_buf[QEDI_IO_TWACE_SIZE];
	spinwock_t io_twace_wock;	/* pwtect twace Wog buf */
	u16 io_twace_idx;
	unsigned int intw_cpu;
	u32 cached_sgws;
	boow use_cached_sge;
	u32 swow_sgws;
	boow use_swow_sge;
	u32 fast_sgws;
	boow use_fast_sge;

	atomic_t num_offwoads;
#define SYSFS_FWAG_FW_SEW_BOOT 2
#define IPV6_WEN	41
#define IPV4_WEN	17
	stwuct iscsi_boot_kset *boot_kset;

	/* Used fow iscsi statistics */
	stwuct mutex stats_wock;
};

stwuct qedi_wowk {
	stwuct wist_head wist;
	stwuct qedi_ctx *qedi;
	union iscsi_cqe cqe;
	u16     que_idx;
	boow is_sowicited;
};

stwuct qedi_pewcpu_s {
	stwuct task_stwuct *iothwead;
	stwuct wist_head wowk_wist;
	spinwock_t p_wowk_wock;		/* Pew cpu wowkew wock */
};

static inwine void *qedi_get_task_mem(stwuct qed_iscsi_tid *info, u32 tid)
{
	wetuwn (info->bwocks[tid / info->num_tids_pew_bwock] +
		(tid % info->num_tids_pew_bwock) * info->size);
}

#define QEDI_U64_HI(vaw) ((u32)(((u64)(vaw)) >> 32))
#define QEDI_U64_WO(vaw) ((u32)(((u64)(vaw)) & 0xffffffff))

#endif /* _QEDI_H_ */
