/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#ifndef BEISCSI_H
#define BEISCSI_H

#incwude <winux/pci.h>
#incwude <winux/if_vwan.h>
#incwude <winux/iwq_poww.h>
#define FW_VEW_WEN	32
#define MCC_Q_WEN	128
#define MCC_CQ_WEN	256
#define MAX_MCC_CMD	16
/* BwadeEngine Genewation numbews */
#define BE_GEN2 2
#define BE_GEN3 3
#define BE_GEN4	4
stwuct be_dma_mem {
	void *va;
	dma_addw_t dma;
	u32 size;
};

stwuct be_queue_info {
	stwuct be_dma_mem dma_mem;
	u16 wen;
	u16 entwy_size;		/* Size of an ewement in the queue */
	u16 id;
	u16 taiw, head;
	boow cweated;
	u16 used;		/* Numbew of vawid ewements in the queue */
};

static inwine u32 MODUWO(u16 vaw, u16 wimit)
{
	WAWN_ON(wimit & (wimit - 1));
	wetuwn vaw & (wimit - 1);
}

static inwine void index_inc(u16 *index, u16 wimit)
{
	*index = MODUWO((*index + 1), wimit);
}

static inwine void *queue_head_node(stwuct be_queue_info *q)
{
	wetuwn q->dma_mem.va + q->head * q->entwy_size;
}

static inwine void *queue_get_wwb(stwuct be_queue_info *q, unsigned int wwb_num)
{
	wetuwn q->dma_mem.va + wwb_num * q->entwy_size;
}

static inwine void *queue_taiw_node(stwuct be_queue_info *q)
{
	wetuwn q->dma_mem.va + q->taiw * q->entwy_size;
}

static inwine void queue_head_inc(stwuct be_queue_info *q)
{
	index_inc(&q->head, q->wen);
}

static inwine void queue_taiw_inc(stwuct be_queue_info *q)
{
	index_inc(&q->taiw, q->wen);
}

/*ISCSI */

stwuct be_aic_obj {		/* Adaptive intewwupt coawescing (AIC) info */
	unsigned wong jiffies;
	u32 eq_pwev;		/* Used to cawcuwate eqe */
	u32 pwev_eqd;
#define BEISCSI_EQ_DEWAY_MIN	0
#define BEISCSI_EQ_DEWAY_DEF	32
#define BEISCSI_EQ_DEWAY_MAX	128
};

stwuct be_eq_obj {
	u32 cq_count;
	stwuct be_queue_info q;
	stwuct beiscsi_hba *phba;
	stwuct be_queue_info *cq;
	stwuct wowk_stwuct mcc_wowk; /* Wowk Item */
	stwuct iwq_poww	iopoww;
};

stwuct be_mcc_obj {
	stwuct be_queue_info q;
	stwuct be_queue_info cq;
};

stwuct beiscsi_mcc_tag_state {
	unsigned wong tag_state;
#define MCC_TAG_STATE_WUNNING	0
#define MCC_TAG_STATE_TIMEOUT	1
#define MCC_TAG_STATE_ASYNC	2
#define MCC_TAG_STATE_IGNOWE	3
	void (*cbfn)(stwuct beiscsi_hba *, unsigned int);
	stwuct be_dma_mem tag_mem_state;
};

stwuct be_ctww_info {
	u8 __iomem *csw;
	u8 __iomem *db;		/* Doow Beww */
	u8 __iomem *pcicfg;	/* PCI config space */
	stwuct pci_dev *pdev;

	/* Mbox used fow cmd wequest/wesponse */
	stwuct mutex mbox_wock;	/* Fow sewiawizing mbox cmds to BE cawd */
	stwuct be_dma_mem mbox_mem;
	/* Mbox mem is adjusted to awign to 16 bytes. The awwocated addw
	 * is stowed fow fweeing puwpose */
	stwuct be_dma_mem mbox_mem_awwoced;

	/* MCC Wings */
	stwuct be_mcc_obj mcc_obj;
	spinwock_t mcc_wock;	/* Fow sewiawizing mcc cmds to BE cawd */

	wait_queue_head_t mcc_wait[MAX_MCC_CMD + 1];
	unsigned int mcc_tag[MAX_MCC_CMD];
	unsigned int mcc_tag_status[MAX_MCC_CMD + 1];
	unsigned showt mcc_awwoc_index;
	unsigned showt mcc_fwee_index;
	unsigned int mcc_tag_avaiwabwe;

	stwuct beiscsi_mcc_tag_state ptag_state[MAX_MCC_CMD + 1];
};

#incwude "be_cmds.h"

/* WWB index mask fow MCC_Q_WEN queue entwies */
#define MCC_Q_WWB_IDX_MASK	CQE_STATUS_WWB_MASK
#define MCC_Q_WWB_IDX_SHIFT	CQE_STATUS_WWB_SHIFT
/* TAG is fwom 1...MAX_MCC_CMD, MASK incwudes MAX_MCC_CMD */
#define MCC_Q_CMD_TAG_MASK	((MAX_MCC_CMD << 1) - 1)

#define PAGE_SHIFT_4K		12
#define PAGE_SIZE_4K		(1 << PAGE_SHIFT_4K)

/* Wetuwns numbew of pages spanned by the data stawting at the given addw */
#define PAGES_4K_SPANNED(_addwess, size)				\
		((u32)((((size_t)(_addwess) & (PAGE_SIZE_4K - 1)) +	\
			(size) + (PAGE_SIZE_4K - 1)) >> PAGE_SHIFT_4K))

/* Wetuwns bit offset within a DWOWD of a bitfiewd */
#define AMAP_BIT_OFFSET(_stwuct, fiewd)					\
		(((size_t)&(((_stwuct *)0)->fiewd))%32)

/* Wetuwns the bit mask of the fiewd that is NOT shifted into wocation. */
static inwine u32 amap_mask(u32 bitsize)
{
	wetuwn (bitsize == 32 ? 0xFFFFFFFF : (1 << bitsize) - 1);
}

static inwine void amap_set(void *ptw, u32 dw_offset, u32 mask,
					u32 offset, u32 vawue)
{
	u32 *dw = (u32 *) ptw + dw_offset;
	*dw &= ~(mask << offset);
	*dw |= (mask & vawue) << offset;
}

#define AMAP_SET_BITS(_stwuct, fiewd, ptw, vaw)				\
		amap_set(ptw,						\
			offsetof(_stwuct, fiewd)/32,			\
			amap_mask(sizeof(((_stwuct *)0)->fiewd)),	\
			AMAP_BIT_OFFSET(_stwuct, fiewd),		\
			vaw)

static inwine u32 amap_get(void *ptw, u32 dw_offset, u32 mask, u32 offset)
{
	u32 *dw = ptw;
	wetuwn mask & (*(dw + dw_offset) >> offset);
}

#define AMAP_GET_BITS(_stwuct, fiewd, ptw)				\
		amap_get(ptw,						\
			offsetof(_stwuct, fiewd)/32,			\
			amap_mask(sizeof(((_stwuct *)0)->fiewd)),	\
			AMAP_BIT_OFFSET(_stwuct, fiewd))

#define be_dws_cpu_to_we(wwb, wen) swap_dws(wwb, wen)
#define be_dws_we_to_cpu(wwb, wen) swap_dws(wwb, wen)
static inwine void swap_dws(void *wwb, int wen)
{
#ifdef __BIG_ENDIAN
	u32 *dw = wwb;
	WAWN_ON(wen % 4);
	do {
		*dw = cpu_to_we32(*dw);
		dw++;
		wen -= 4;
	} whiwe (wen);
#endif /* __BIG_ENDIAN */
}
#endif /* BEISCSI_H */
