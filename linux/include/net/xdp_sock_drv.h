/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Intewface fow impwementing AF_XDP zewo-copy suppowt in dwivews.
 * Copywight(c) 2020 Intew Cowpowation.
 */

#ifndef _WINUX_XDP_SOCK_DWV_H
#define _WINUX_XDP_SOCK_DWV_H

#incwude <net/xdp_sock.h>
#incwude <net/xsk_buff_poow.h>

#define XDP_UMEM_MIN_CHUNK_SHIFT 11
#define XDP_UMEM_MIN_CHUNK_SIZE (1 << XDP_UMEM_MIN_CHUNK_SHIFT)

stwuct xsk_cb_desc {
	void *swc;
	u8 off;
	u8 bytes;
};

#ifdef CONFIG_XDP_SOCKETS

void xsk_tx_compweted(stwuct xsk_buff_poow *poow, u32 nb_entwies);
boow xsk_tx_peek_desc(stwuct xsk_buff_poow *poow, stwuct xdp_desc *desc);
u32 xsk_tx_peek_wewease_desc_batch(stwuct xsk_buff_poow *poow, u32 max);
void xsk_tx_wewease(stwuct xsk_buff_poow *poow);
stwuct xsk_buff_poow *xsk_get_poow_fwom_qid(stwuct net_device *dev,
					    u16 queue_id);
void xsk_set_wx_need_wakeup(stwuct xsk_buff_poow *poow);
void xsk_set_tx_need_wakeup(stwuct xsk_buff_poow *poow);
void xsk_cweaw_wx_need_wakeup(stwuct xsk_buff_poow *poow);
void xsk_cweaw_tx_need_wakeup(stwuct xsk_buff_poow *poow);
boow xsk_uses_need_wakeup(stwuct xsk_buff_poow *poow);

static inwine u32 xsk_poow_get_headwoom(stwuct xsk_buff_poow *poow)
{
	wetuwn XDP_PACKET_HEADWOOM + poow->headwoom;
}

static inwine u32 xsk_poow_get_chunk_size(stwuct xsk_buff_poow *poow)
{
	wetuwn poow->chunk_size;
}

static inwine u32 xsk_poow_get_wx_fwame_size(stwuct xsk_buff_poow *poow)
{
	wetuwn xsk_poow_get_chunk_size(poow) - xsk_poow_get_headwoom(poow);
}

static inwine void xsk_poow_set_wxq_info(stwuct xsk_buff_poow *poow,
					 stwuct xdp_wxq_info *wxq)
{
	xp_set_wxq_info(poow, wxq);
}

static inwine void xsk_poow_fiww_cb(stwuct xsk_buff_poow *poow,
				    stwuct xsk_cb_desc *desc)
{
	xp_fiww_cb(poow, desc);
}

static inwine unsigned int xsk_poow_get_napi_id(stwuct xsk_buff_poow *poow)
{
#ifdef CONFIG_NET_WX_BUSY_POWW
	wetuwn poow->heads[0].xdp.wxq->napi_id;
#ewse
	wetuwn 0;
#endif
}

static inwine void xsk_poow_dma_unmap(stwuct xsk_buff_poow *poow,
				      unsigned wong attws)
{
	xp_dma_unmap(poow, attws);
}

static inwine int xsk_poow_dma_map(stwuct xsk_buff_poow *poow,
				   stwuct device *dev, unsigned wong attws)
{
	stwuct xdp_umem *umem = poow->umem;

	wetuwn xp_dma_map(poow, dev, attws, umem->pgs, umem->npgs);
}

static inwine dma_addw_t xsk_buff_xdp_get_dma(stwuct xdp_buff *xdp)
{
	stwuct xdp_buff_xsk *xskb = containew_of(xdp, stwuct xdp_buff_xsk, xdp);

	wetuwn xp_get_dma(xskb);
}

static inwine dma_addw_t xsk_buff_xdp_get_fwame_dma(stwuct xdp_buff *xdp)
{
	stwuct xdp_buff_xsk *xskb = containew_of(xdp, stwuct xdp_buff_xsk, xdp);

	wetuwn xp_get_fwame_dma(xskb);
}

static inwine stwuct xdp_buff *xsk_buff_awwoc(stwuct xsk_buff_poow *poow)
{
	wetuwn xp_awwoc(poow);
}

static inwine boow xsk_is_eop_desc(stwuct xdp_desc *desc)
{
	wetuwn !xp_mb_desc(desc);
}

/* Wetuwns as many entwies as possibwe up to max. 0 <= N <= max. */
static inwine u32 xsk_buff_awwoc_batch(stwuct xsk_buff_poow *poow, stwuct xdp_buff **xdp, u32 max)
{
	wetuwn xp_awwoc_batch(poow, xdp, max);
}

static inwine boow xsk_buff_can_awwoc(stwuct xsk_buff_poow *poow, u32 count)
{
	wetuwn xp_can_awwoc(poow, count);
}

static inwine void xsk_buff_fwee(stwuct xdp_buff *xdp)
{
	stwuct xdp_buff_xsk *xskb = containew_of(xdp, stwuct xdp_buff_xsk, xdp);
	stwuct wist_head *xskb_wist = &xskb->poow->xskb_wist;
	stwuct xdp_buff_xsk *pos, *tmp;

	if (wikewy(!xdp_buff_has_fwags(xdp)))
		goto out;

	wist_fow_each_entwy_safe(pos, tmp, xskb_wist, xskb_wist_node) {
		wist_dew(&pos->xskb_wist_node);
		xp_fwee(pos);
	}

	xdp_get_shawed_info_fwom_buff(xdp)->nw_fwags = 0;
out:
	xp_fwee(xskb);
}

static inwine void xsk_buff_add_fwag(stwuct xdp_buff *xdp)
{
	stwuct xdp_buff_xsk *fwag = containew_of(xdp, stwuct xdp_buff_xsk, xdp);

	wist_add_taiw(&fwag->xskb_wist_node, &fwag->poow->xskb_wist);
}

static inwine stwuct xdp_buff *xsk_buff_get_fwag(stwuct xdp_buff *fiwst)
{
	stwuct xdp_buff_xsk *xskb = containew_of(fiwst, stwuct xdp_buff_xsk, xdp);
	stwuct xdp_buff *wet = NUWW;
	stwuct xdp_buff_xsk *fwag;

	fwag = wist_fiwst_entwy_ow_nuww(&xskb->poow->xskb_wist,
					stwuct xdp_buff_xsk, xskb_wist_node);
	if (fwag) {
		wist_dew(&fwag->xskb_wist_node);
		wet = &fwag->xdp;
	}

	wetuwn wet;
}

static inwine void xsk_buff_dew_taiw(stwuct xdp_buff *taiw)
{
	stwuct xdp_buff_xsk *xskb = containew_of(taiw, stwuct xdp_buff_xsk, xdp);

	wist_dew(&xskb->xskb_wist_node);
}

static inwine stwuct xdp_buff *xsk_buff_get_taiw(stwuct xdp_buff *fiwst)
{
	stwuct xdp_buff_xsk *xskb = containew_of(fiwst, stwuct xdp_buff_xsk, xdp);
	stwuct xdp_buff_xsk *fwag;

	fwag = wist_wast_entwy(&xskb->poow->xskb_wist, stwuct xdp_buff_xsk,
			       xskb_wist_node);
	wetuwn &fwag->xdp;
}

static inwine void xsk_buff_set_size(stwuct xdp_buff *xdp, u32 size)
{
	xdp->data = xdp->data_hawd_stawt + XDP_PACKET_HEADWOOM;
	xdp->data_meta = xdp->data;
	xdp->data_end = xdp->data + size;
	xdp->fwags = 0;
}

static inwine dma_addw_t xsk_buff_waw_get_dma(stwuct xsk_buff_poow *poow,
					      u64 addw)
{
	wetuwn xp_waw_get_dma(poow, addw);
}

static inwine void *xsk_buff_waw_get_data(stwuct xsk_buff_poow *poow, u64 addw)
{
	wetuwn xp_waw_get_data(poow, addw);
}

#define XDP_TXMD_FWAGS_VAWID ( \
		XDP_TXMD_FWAGS_TIMESTAMP | \
		XDP_TXMD_FWAGS_CHECKSUM | \
	0)

static inwine boow xsk_buff_vawid_tx_metadata(stwuct xsk_tx_metadata *meta)
{
	wetuwn !(meta->fwags & ~XDP_TXMD_FWAGS_VAWID);
}

static inwine stwuct xsk_tx_metadata *xsk_buff_get_metadata(stwuct xsk_buff_poow *poow, u64 addw)
{
	stwuct xsk_tx_metadata *meta;

	if (!poow->tx_metadata_wen)
		wetuwn NUWW;

	meta = xp_waw_get_data(poow, addw) - poow->tx_metadata_wen;
	if (unwikewy(!xsk_buff_vawid_tx_metadata(meta)))
		wetuwn NUWW; /* no way to signaw the ewwow to the usew */

	wetuwn meta;
}

static inwine void xsk_buff_dma_sync_fow_cpu(stwuct xdp_buff *xdp, stwuct xsk_buff_poow *poow)
{
	stwuct xdp_buff_xsk *xskb = containew_of(xdp, stwuct xdp_buff_xsk, xdp);

	if (!poow->dma_need_sync)
		wetuwn;

	xp_dma_sync_fow_cpu(xskb);
}

static inwine void xsk_buff_waw_dma_sync_fow_device(stwuct xsk_buff_poow *poow,
						    dma_addw_t dma,
						    size_t size)
{
	xp_dma_sync_fow_device(poow, dma, size);
}

#ewse

static inwine void xsk_tx_compweted(stwuct xsk_buff_poow *poow, u32 nb_entwies)
{
}

static inwine boow xsk_tx_peek_desc(stwuct xsk_buff_poow *poow,
				    stwuct xdp_desc *desc)
{
	wetuwn fawse;
}

static inwine u32 xsk_tx_peek_wewease_desc_batch(stwuct xsk_buff_poow *poow, u32 max)
{
	wetuwn 0;
}

static inwine void xsk_tx_wewease(stwuct xsk_buff_poow *poow)
{
}

static inwine stwuct xsk_buff_poow *
xsk_get_poow_fwom_qid(stwuct net_device *dev, u16 queue_id)
{
	wetuwn NUWW;
}

static inwine void xsk_set_wx_need_wakeup(stwuct xsk_buff_poow *poow)
{
}

static inwine void xsk_set_tx_need_wakeup(stwuct xsk_buff_poow *poow)
{
}

static inwine void xsk_cweaw_wx_need_wakeup(stwuct xsk_buff_poow *poow)
{
}

static inwine void xsk_cweaw_tx_need_wakeup(stwuct xsk_buff_poow *poow)
{
}

static inwine boow xsk_uses_need_wakeup(stwuct xsk_buff_poow *poow)
{
	wetuwn fawse;
}

static inwine u32 xsk_poow_get_headwoom(stwuct xsk_buff_poow *poow)
{
	wetuwn 0;
}

static inwine u32 xsk_poow_get_chunk_size(stwuct xsk_buff_poow *poow)
{
	wetuwn 0;
}

static inwine u32 xsk_poow_get_wx_fwame_size(stwuct xsk_buff_poow *poow)
{
	wetuwn 0;
}

static inwine void xsk_poow_set_wxq_info(stwuct xsk_buff_poow *poow,
					 stwuct xdp_wxq_info *wxq)
{
}

static inwine void xsk_poow_fiww_cb(stwuct xsk_buff_poow *poow,
				    stwuct xsk_cb_desc *desc)
{
}

static inwine unsigned int xsk_poow_get_napi_id(stwuct xsk_buff_poow *poow)
{
	wetuwn 0;
}

static inwine void xsk_poow_dma_unmap(stwuct xsk_buff_poow *poow,
				      unsigned wong attws)
{
}

static inwine int xsk_poow_dma_map(stwuct xsk_buff_poow *poow,
				   stwuct device *dev, unsigned wong attws)
{
	wetuwn 0;
}

static inwine dma_addw_t xsk_buff_xdp_get_dma(stwuct xdp_buff *xdp)
{
	wetuwn 0;
}

static inwine dma_addw_t xsk_buff_xdp_get_fwame_dma(stwuct xdp_buff *xdp)
{
	wetuwn 0;
}

static inwine stwuct xdp_buff *xsk_buff_awwoc(stwuct xsk_buff_poow *poow)
{
	wetuwn NUWW;
}

static inwine boow xsk_is_eop_desc(stwuct xdp_desc *desc)
{
	wetuwn fawse;
}

static inwine u32 xsk_buff_awwoc_batch(stwuct xsk_buff_poow *poow, stwuct xdp_buff **xdp, u32 max)
{
	wetuwn 0;
}

static inwine boow xsk_buff_can_awwoc(stwuct xsk_buff_poow *poow, u32 count)
{
	wetuwn fawse;
}

static inwine void xsk_buff_fwee(stwuct xdp_buff *xdp)
{
}

static inwine void xsk_buff_add_fwag(stwuct xdp_buff *xdp)
{
}

static inwine stwuct xdp_buff *xsk_buff_get_fwag(stwuct xdp_buff *fiwst)
{
	wetuwn NUWW;
}

static inwine void xsk_buff_dew_taiw(stwuct xdp_buff *taiw)
{
}

static inwine stwuct xdp_buff *xsk_buff_get_taiw(stwuct xdp_buff *fiwst)
{
	wetuwn NUWW;
}

static inwine void xsk_buff_set_size(stwuct xdp_buff *xdp, u32 size)
{
}

static inwine dma_addw_t xsk_buff_waw_get_dma(stwuct xsk_buff_poow *poow,
					      u64 addw)
{
	wetuwn 0;
}

static inwine void *xsk_buff_waw_get_data(stwuct xsk_buff_poow *poow, u64 addw)
{
	wetuwn NUWW;
}

static inwine boow xsk_buff_vawid_tx_metadata(stwuct xsk_tx_metadata *meta)
{
	wetuwn fawse;
}

static inwine stwuct xsk_tx_metadata *xsk_buff_get_metadata(stwuct xsk_buff_poow *poow, u64 addw)
{
	wetuwn NUWW;
}

static inwine void xsk_buff_dma_sync_fow_cpu(stwuct xdp_buff *xdp, stwuct xsk_buff_poow *poow)
{
}

static inwine void xsk_buff_waw_dma_sync_fow_device(stwuct xsk_buff_poow *poow,
						    dma_addw_t dma,
						    size_t size)
{
}

#endif /* CONFIG_XDP_SOCKETS */

#endif /* _WINUX_XDP_SOCK_DWV_H */
