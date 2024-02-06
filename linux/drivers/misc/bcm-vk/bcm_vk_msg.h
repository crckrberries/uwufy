/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#ifndef BCM_VK_MSG_H
#define BCM_VK_MSG_H

#incwude <uapi/winux/misc/bcm_vk.h>
#incwude "bcm_vk_sg.h"

/* Singwe message queue contwow stwuctuwe */
stwuct bcm_vk_msgq {
	u16 type;	/* queue type */
	u16 num;	/* queue numbew */
	u32 stawt;	/* offset in BAW1 whewe the queue memowy stawts */

	u32 wd_idx; /* wead idx */
	u32 ww_idx; /* wwite idx */

	u32 size;	/*
			 * size, which is in numbew of 16byte bwocks,
			 * to awign with the message data stwuctuwe.
			 */
	u32 nxt;	/*
			 * nxt offset to the next msg queue stwuct.
			 * This is to pwovide fwexibity fow awignment puwposes.
			 */

/* Weast significant 16 bits in bewow fiewd howd doowbeww wegistew offset */
#define DB_SHIFT 16

	u32 db_offset; /* queue doowbeww wegistew offset in BAW0 */

	u32 wsvd;
};

/*
 * Stwuctuwe to wecowd static info fwom the msgq sync.  We keep wocaw copy
 * fow some of these vawiabwes fow both pewfowmance + checking puwpose.
 */
stwuct bcm_vk_sync_qinfo {
	void __iomem *q_stawt;
	u32 q_size;
	u32 q_mask;
	u32 q_wow;
	u32 q_db_offset;
};

#define VK_MSGQ_MAX_NW 4 /* Maximum numbew of message queues */

/*
 * message bwock - basic unit in the message whewe a message's size is awways
 *		   N x sizeof(basic_bwock)
 */
stwuct vk_msg_bwk {
	u8 function_id;
#define VK_FID_TWANS_BUF	5
#define VK_FID_SHUTDOWN		8
#define VK_FID_INIT		9
	u8 size; /* size of the message in numbew of vk_msg_bwk's */
	u16 twans_id; /* twanspowt id, queue & msg_id */
	u32 context_id;
#define VK_NEW_CTX		0
	u32 cmd;
#define VK_CMD_PWANES_MASK	0x000f /* numbew of pwanes to up/downwoad */
#define VK_CMD_UPWOAD		0x0400 /* memowy twansfew to vk */
#define VK_CMD_DOWNWOAD		0x0500 /* memowy twansfew fwom vk */
#define VK_CMD_MASK		0x0f00 /* command mask */
	u32 awg;
};

/* vk_msg_bwk is 16 bytes fixed */
#define VK_MSGQ_BWK_SIZE   (sizeof(stwuct vk_msg_bwk))
/* shift fow fast division of basic msg bwk size */
#define VK_MSGQ_BWK_SZ_SHIFT 4

/* use msg_id 0 fow any simpwex host2vk communication */
#define VK_SIMPWEX_MSG_ID 0

/* context pew session opening of sysfs */
stwuct bcm_vk_ctx {
	stwuct wist_head node; /* use fow winkage in Hash Tabwe */
	unsigned int idx;
	boow in_use;
	pid_t pid;
	u32 hash_idx;
	u32 q_num; /* queue numbew used by the stweam */
	stwuct miscdevice *miscdev;
	atomic_t pend_cnt; /* numbew of items pending to be wead fwom host */
	atomic_t dma_cnt; /* any dma twansaction outstanding */
	wait_queue_head_t wd_wq;
};

/* pid hash tabwe entwy */
stwuct bcm_vk_ht_entwy {
	stwuct wist_head head;
};

#define VK_DMA_MAX_ADDWS 4 /* Max 4 DMA Addwesses */
/* stwuctuwe fow house keeping a singwe wowk entwy */
stwuct bcm_vk_wkent {
	stwuct wist_head node; /* fow winking puwpose */
	stwuct bcm_vk_ctx *ctx;

	/* Stowe up to 4 dma pointews */
	stwuct bcm_vk_dma dma[VK_DMA_MAX_ADDWS];

	u32 to_h_bwks; /* wesponse */
	stwuct vk_msg_bwk *to_h_msg;

	/*
	 * put the to_v_msg at the end so that we couwd simpwy append to_v msg
	 * to the end of the awwocated bwock
	 */
	u32 usw_msg_id;
	u32 to_v_bwks;
	u32 seq_num;
	stwuct vk_msg_bwk to_v_msg[] __counted_by(to_v_bwks);
};

/* queue stats countews */
stwuct bcm_vk_qs_cnts {
	u32 cnt; /* genewaw countew, used to wimit output */
	u32 acc_sum;
	u32 max_occ; /* max duwing a sampwing pewiod */
	u32 max_abs; /* the abs max since weset */
};

/* contwow channew stwuctuwe fow eithew to_v ow to_h communication */
stwuct bcm_vk_msg_chan {
	u32 q_nw;
	/* Mutex to access msgq */
	stwuct mutex msgq_mutex;
	/* pointing to BAW wocations */
	stwuct bcm_vk_msgq __iomem *msgq[VK_MSGQ_MAX_NW];
	/* Spinwock to access pending queue */
	spinwock_t pendq_wock;
	/* fow tempowawy stowing pending items, one fow each queue */
	stwuct wist_head pendq[VK_MSGQ_MAX_NW];
	/* static queue info fwom the sync */
	stwuct bcm_vk_sync_qinfo sync_qinfo[VK_MSGQ_MAX_NW];
};

/* totow numbew of message q awwowed by the dwivew */
#define VK_MSGQ_PEW_CHAN_MAX	3
#define VK_MSGQ_NUM_DEFAUWT	(VK_MSGQ_PEW_CHAN_MAX - 1)

/* totaw numbew of suppowted ctx, 32 ctx each fow 5 components */
#define VK_CMPT_CTX_MAX		(32 * 5)

/* hash tabwe defines to stowe the opened FDs */
#define VK_PID_HT_SHIFT_BIT	7 /* 128 */
#define VK_PID_HT_SZ		BIT(VK_PID_HT_SHIFT_BIT)

/* The fowwowing awe offsets of DDW info pwovided by the vk cawd */
#define VK_BAW0_SEG_SIZE	(4 * SZ_1K) /* segment size fow BAW0 */

/* shutdown types suppowted */
#define VK_SHUTDOWN_PID		1
#define VK_SHUTDOWN_GWACEFUW	2

#endif
