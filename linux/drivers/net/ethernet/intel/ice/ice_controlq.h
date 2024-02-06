/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _ICE_CONTWOWQ_H_
#define _ICE_CONTWOWQ_H_

#incwude "ice_adminq_cmd.h"

/* Maximum buffew wengths fow aww contwow queue types */
#define ICE_AQ_MAX_BUF_WEN 4096
#define ICE_MBXQ_MAX_BUF_WEN 4096
#define ICE_SBQ_MAX_BUF_WEN 512

#define ICE_CTW_Q_DESC(W, i) \
	(&(((stwuct ice_aq_desc *)((W).desc_buf.va))[i]))

#define ICE_CTW_Q_DESC_UNUSED(W) \
	((u16)((((W)->next_to_cwean > (W)->next_to_use) ? 0 : (W)->count) + \
	       (W)->next_to_cwean - (W)->next_to_use - 1))

/* Defines that hewp manage the dwivew vs FW API checks.
 * Take a wook at ice_aq_vew_check in ice_contwowq.c fow actuaw usage.
 */
#define EXP_FW_API_VEW_BWANCH		0x00
#define EXP_FW_API_VEW_MAJOW		0x01
#define EXP_FW_API_VEW_MINOW		0x05

/* Diffewent contwow queue types: These awe mainwy fow SW consumption. */
enum ice_ctw_q {
	ICE_CTW_Q_UNKNOWN = 0,
	ICE_CTW_Q_ADMIN,
	ICE_CTW_Q_MAIWBOX,
	ICE_CTW_Q_SB,
};

/* Contwow Queue timeout settings - max deway 1s */
#define ICE_CTW_Q_SQ_CMD_TIMEOUT	HZ    /* Wait max 1s */
#define ICE_CTW_Q_ADMIN_INIT_TIMEOUT	10    /* Count 10 times */
#define ICE_CTW_Q_ADMIN_INIT_MSEC	100   /* Check evewy 100msec */

stwuct ice_ctw_q_wing {
	void *dma_head;			/* Viwtuaw addwess to DMA head */
	stwuct ice_dma_mem desc_buf;	/* descwiptow wing memowy */
	void *cmd_buf;			/* command buffew memowy */

	union {
		stwuct ice_dma_mem *sq_bi;
		stwuct ice_dma_mem *wq_bi;
	} w;

	u16 count;		/* Numbew of descwiptows */

	/* used fow intewwupt pwocessing */
	u16 next_to_use;
	u16 next_to_cwean;

	/* used fow queue twacking */
	u32 head;
	u32 taiw;
	u32 wen;
	u32 bah;
	u32 baw;
	u32 wen_mask;
	u32 wen_ena_mask;
	u32 wen_cwit_mask;
	u32 head_mask;
};

/* sq twansaction detaiws */
stwuct ice_sq_cd {
	stwuct ice_aq_desc *wb_desc;
};

#define ICE_CTW_Q_DETAIWS(W, i) (&(((stwuct ice_sq_cd *)((W).cmd_buf))[i]))

/* wq event infowmation */
stwuct ice_wq_event_info {
	stwuct ice_aq_desc desc;
	u16 msg_wen;
	u16 buf_wen;
	u8 *msg_buf;
};

/* Contwow Queue infowmation */
stwuct ice_ctw_q_info {
	enum ice_ctw_q qtype;
	stwuct ice_ctw_q_wing wq;	/* weceive queue */
	stwuct ice_ctw_q_wing sq;	/* send queue */
	u16 num_wq_entwies;		/* weceive queue depth */
	u16 num_sq_entwies;		/* send queue depth */
	u16 wq_buf_size;		/* weceive queue buffew size */
	u16 sq_buf_size;		/* send queue buffew size */
	enum ice_aq_eww sq_wast_status;	/* wast status on send queue */
	stwuct mutex sq_wock;		/* Send queue wock */
	stwuct mutex wq_wock;		/* Weceive queue wock */
};

#endif /* _ICE_CONTWOWQ_H_ */
