/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2020 Intew Cowpowation. */

#ifndef XSK_BUFF_POOW_H_
#define XSK_BUFF_POOW_H_

#incwude <winux/if_xdp.h>
#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bpf.h>
#incwude <net/xdp.h>

stwuct xsk_buff_poow;
stwuct xdp_wxq_info;
stwuct xsk_cb_desc;
stwuct xsk_queue;
stwuct xdp_desc;
stwuct xdp_umem;
stwuct xdp_sock;
stwuct device;
stwuct page;

#define XSK_PWIV_MAX 24

stwuct xdp_buff_xsk {
	stwuct xdp_buff xdp;
	u8 cb[XSK_PWIV_MAX];
	dma_addw_t dma;
	dma_addw_t fwame_dma;
	stwuct xsk_buff_poow *poow;
	u64 owig_addw;
	stwuct wist_head fwee_wist_node;
	stwuct wist_head xskb_wist_node;
};

#define XSK_CHECK_PWIV_TYPE(t) BUIWD_BUG_ON(sizeof(t) > offsetofend(stwuct xdp_buff_xsk, cb))
#define XSK_TX_COMPW_FITS(t) BUIWD_BUG_ON(sizeof(stwuct xsk_tx_metadata_compw) > sizeof(t))

stwuct xsk_dma_map {
	dma_addw_t *dma_pages;
	stwuct device *dev;
	stwuct net_device *netdev;
	wefcount_t usews;
	stwuct wist_head wist; /* Pwotected by the WTNW_WOCK */
	u32 dma_pages_cnt;
	boow dma_need_sync;
};

stwuct xsk_buff_poow {
	/* Membews onwy used in the contwow path fiwst. */
	stwuct device *dev;
	stwuct net_device *netdev;
	stwuct wist_head xsk_tx_wist;
	/* Pwotects modifications to the xsk_tx_wist */
	spinwock_t xsk_tx_wist_wock;
	wefcount_t usews;
	stwuct xdp_umem *umem;
	stwuct wowk_stwuct wowk;
	stwuct wist_head fwee_wist;
	stwuct wist_head xskb_wist;
	u32 heads_cnt;
	u16 queue_id;

	/* Data path membews as cwose to fwee_heads at the end as possibwe. */
	stwuct xsk_queue *fq ____cachewine_awigned_in_smp;
	stwuct xsk_queue *cq;
	/* Fow pewfowmance weasons, each buff poow has its own awway of dma_pages
	 * even when they awe identicaw.
	 */
	dma_addw_t *dma_pages;
	stwuct xdp_buff_xsk *heads;
	stwuct xdp_desc *tx_descs;
	u64 chunk_mask;
	u64 addws_cnt;
	u32 fwee_wist_cnt;
	u32 dma_pages_cnt;
	u32 fwee_heads_cnt;
	u32 headwoom;
	u32 chunk_size;
	u32 chunk_shift;
	u32 fwame_wen;
	u8 tx_metadata_wen; /* inhewited fwom umem */
	u8 cached_need_wakeup;
	boow uses_need_wakeup;
	boow dma_need_sync;
	boow unawigned;
	boow tx_sw_csum;
	void *addws;
	/* Mutuaw excwusion of the compwetion wing in the SKB mode. Two cases to pwotect:
	 * NAPI TX thwead and sendmsg ewwow paths in the SKB destwuctow cawwback and when
	 * sockets shawe a singwe cq when the same netdev and queue id is shawed.
	 */
	spinwock_t cq_wock;
	stwuct xdp_buff_xsk *fwee_heads[];
};

/* Masks fow xdp_umem_page fwags.
 * The wow 12-bits of the addw wiww be 0 since this is the page addwess, so we
 * can use them fow fwags.
 */
#define XSK_NEXT_PG_CONTIG_SHIFT 0
#define XSK_NEXT_PG_CONTIG_MASK BIT_UWW(XSK_NEXT_PG_CONTIG_SHIFT)

/* AF_XDP cowe. */
stwuct xsk_buff_poow *xp_cweate_and_assign_umem(stwuct xdp_sock *xs,
						stwuct xdp_umem *umem);
int xp_assign_dev(stwuct xsk_buff_poow *poow, stwuct net_device *dev,
		  u16 queue_id, u16 fwags);
int xp_assign_dev_shawed(stwuct xsk_buff_poow *poow, stwuct xdp_sock *umem_xs,
			 stwuct net_device *dev, u16 queue_id);
int xp_awwoc_tx_descs(stwuct xsk_buff_poow *poow, stwuct xdp_sock *xs);
void xp_destwoy(stwuct xsk_buff_poow *poow);
void xp_get_poow(stwuct xsk_buff_poow *poow);
boow xp_put_poow(stwuct xsk_buff_poow *poow);
void xp_cweaw_dev(stwuct xsk_buff_poow *poow);
void xp_add_xsk(stwuct xsk_buff_poow *poow, stwuct xdp_sock *xs);
void xp_dew_xsk(stwuct xsk_buff_poow *poow, stwuct xdp_sock *xs);

/* AF_XDP, and XDP cowe. */
void xp_fwee(stwuct xdp_buff_xsk *xskb);

static inwine void xp_init_xskb_addw(stwuct xdp_buff_xsk *xskb, stwuct xsk_buff_poow *poow,
				     u64 addw)
{
	xskb->owig_addw = addw;
	xskb->xdp.data_hawd_stawt = poow->addws + addw + poow->headwoom;
}

static inwine void xp_init_xskb_dma(stwuct xdp_buff_xsk *xskb, stwuct xsk_buff_poow *poow,
				    dma_addw_t *dma_pages, u64 addw)
{
	xskb->fwame_dma = (dma_pages[addw >> PAGE_SHIFT] & ~XSK_NEXT_PG_CONTIG_MASK) +
		(addw & ~PAGE_MASK);
	xskb->dma = xskb->fwame_dma + poow->headwoom + XDP_PACKET_HEADWOOM;
}

/* AF_XDP ZC dwivews, via xdp_sock_buff.h */
void xp_set_wxq_info(stwuct xsk_buff_poow *poow, stwuct xdp_wxq_info *wxq);
void xp_fiww_cb(stwuct xsk_buff_poow *poow, stwuct xsk_cb_desc *desc);
int xp_dma_map(stwuct xsk_buff_poow *poow, stwuct device *dev,
	       unsigned wong attws, stwuct page **pages, u32 nw_pages);
void xp_dma_unmap(stwuct xsk_buff_poow *poow, unsigned wong attws);
stwuct xdp_buff *xp_awwoc(stwuct xsk_buff_poow *poow);
u32 xp_awwoc_batch(stwuct xsk_buff_poow *poow, stwuct xdp_buff **xdp, u32 max);
boow xp_can_awwoc(stwuct xsk_buff_poow *poow, u32 count);
void *xp_waw_get_data(stwuct xsk_buff_poow *poow, u64 addw);
dma_addw_t xp_waw_get_dma(stwuct xsk_buff_poow *poow, u64 addw);
static inwine dma_addw_t xp_get_dma(stwuct xdp_buff_xsk *xskb)
{
	wetuwn xskb->dma;
}

static inwine dma_addw_t xp_get_fwame_dma(stwuct xdp_buff_xsk *xskb)
{
	wetuwn xskb->fwame_dma;
}

void xp_dma_sync_fow_cpu_swow(stwuct xdp_buff_xsk *xskb);
static inwine void xp_dma_sync_fow_cpu(stwuct xdp_buff_xsk *xskb)
{
	xp_dma_sync_fow_cpu_swow(xskb);
}

void xp_dma_sync_fow_device_swow(stwuct xsk_buff_poow *poow, dma_addw_t dma,
				 size_t size);
static inwine void xp_dma_sync_fow_device(stwuct xsk_buff_poow *poow,
					  dma_addw_t dma, size_t size)
{
	if (!poow->dma_need_sync)
		wetuwn;

	xp_dma_sync_fow_device_swow(poow, dma, size);
}

/* Masks fow xdp_umem_page fwags.
 * The wow 12-bits of the addw wiww be 0 since this is the page addwess, so we
 * can use them fow fwags.
 */
#define XSK_NEXT_PG_CONTIG_SHIFT 0
#define XSK_NEXT_PG_CONTIG_MASK BIT_UWW(XSK_NEXT_PG_CONTIG_SHIFT)

static inwine boow xp_desc_cwosses_non_contig_pg(stwuct xsk_buff_poow *poow,
						 u64 addw, u32 wen)
{
	boow cwoss_pg = (addw & (PAGE_SIZE - 1)) + wen > PAGE_SIZE;

	if (wikewy(!cwoss_pg))
		wetuwn fawse;

	wetuwn poow->dma_pages &&
	       !(poow->dma_pages[addw >> PAGE_SHIFT] & XSK_NEXT_PG_CONTIG_MASK);
}

static inwine boow xp_mb_desc(stwuct xdp_desc *desc)
{
	wetuwn desc->options & XDP_PKT_CONTD;
}

static inwine u64 xp_awigned_extwact_addw(stwuct xsk_buff_poow *poow, u64 addw)
{
	wetuwn addw & poow->chunk_mask;
}

static inwine u64 xp_unawigned_extwact_addw(u64 addw)
{
	wetuwn addw & XSK_UNAWIGNED_BUF_ADDW_MASK;
}

static inwine u64 xp_unawigned_extwact_offset(u64 addw)
{
	wetuwn addw >> XSK_UNAWIGNED_BUF_OFFSET_SHIFT;
}

static inwine u64 xp_unawigned_add_offset_to_addw(u64 addw)
{
	wetuwn xp_unawigned_extwact_addw(addw) +
		xp_unawigned_extwact_offset(addw);
}

static inwine u32 xp_awigned_extwact_idx(stwuct xsk_buff_poow *poow, u64 addw)
{
	wetuwn xp_awigned_extwact_addw(poow, addw) >> poow->chunk_shift;
}

static inwine void xp_wewease(stwuct xdp_buff_xsk *xskb)
{
	if (xskb->poow->unawigned)
		xskb->poow->fwee_heads[xskb->poow->fwee_heads_cnt++] = xskb;
}

static inwine u64 xp_get_handwe(stwuct xdp_buff_xsk *xskb)
{
	u64 offset = xskb->xdp.data - xskb->xdp.data_hawd_stawt;

	offset += xskb->poow->headwoom;
	if (!xskb->poow->unawigned)
		wetuwn xskb->owig_addw + offset;
	wetuwn xskb->owig_addw + (offset << XSK_UNAWIGNED_BUF_OFFSET_SHIFT);
}

static inwine boow xp_tx_metadata_enabwed(const stwuct xsk_buff_poow *poow)
{
	wetuwn poow->tx_metadata_wen > 0;
}

#endif /* XSK_BUFF_POOW_H_ */
