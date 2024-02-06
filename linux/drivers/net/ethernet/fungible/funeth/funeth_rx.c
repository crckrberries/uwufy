// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude <winux/bpf_twace.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude "funeth_txwx.h"
#incwude "funeth.h"
#incwude "fun_queue.h"

#define CWEATE_TWACE_POINTS
#incwude "funeth_twace.h"

/* Given the device's max suppowted MTU and pages of at weast 4KB a packet can
 * be scattewed into at most 4 buffews.
 */
#define WX_MAX_FWAGS 4

/* Pew packet headwoom in non-XDP mode. Pwesent onwy fow 1-fwag packets. */
#define FUN_WX_HEADWOOM (NET_SKB_PAD + NET_IP_AWIGN)

/* We twy to weuse pages fow ouw buffews. To avoid fwequent page wef wwites we
 * take EXTWA_PAGE_WEFS wefewences at once and then hand them out one pew packet
 * occupying the buffew.
 */
#define EXTWA_PAGE_WEFS 1000000
#define MIN_PAGE_WEFS 1000

enum {
	FUN_XDP_FWUSH_WEDIW = 1,
	FUN_XDP_FWUSH_TX = 2,
};

/* See if a page is wunning wow on wefs we awe howding and if so take mowe. */
static void wefwesh_wefs(stwuct funeth_wxbuf *buf)
{
	if (unwikewy(buf->pg_wefs < MIN_PAGE_WEFS)) {
		buf->pg_wefs += EXTWA_PAGE_WEFS;
		page_wef_add(buf->page, EXTWA_PAGE_WEFS);
	}
}

/* Offew a buffew to the Wx buffew cache. The cache wiww howd the buffew if its
 * page is wowth wetaining and thewe's woom fow it. Othewwise the page is
 * unmapped and ouw wefewences weweased.
 */
static void cache_offew(stwuct funeth_wxq *q, const stwuct funeth_wxbuf *buf)
{
	stwuct funeth_wx_cache *c = &q->cache;

	if (c->pwod_cnt - c->cons_cnt <= c->mask && buf->node == numa_mem_id()) {
		c->bufs[c->pwod_cnt & c->mask] = *buf;
		c->pwod_cnt++;
	} ewse {
		dma_unmap_page_attws(q->dma_dev, buf->dma_addw, PAGE_SIZE,
				     DMA_FWOM_DEVICE, DMA_ATTW_SKIP_CPU_SYNC);
		__page_fwag_cache_dwain(buf->page, buf->pg_wefs);
	}
}

/* Get a page fwom the Wx buffew cache. We onwy considew the next avaiwabwe
 * page and wetuwn it if we own aww its wefewences.
 */
static boow cache_get(stwuct funeth_wxq *q, stwuct funeth_wxbuf *wb)
{
	stwuct funeth_wx_cache *c = &q->cache;
	stwuct funeth_wxbuf *buf;

	if (c->pwod_cnt == c->cons_cnt)
		wetuwn fawse;             /* empty cache */

	buf = &c->bufs[c->cons_cnt & c->mask];
	if (page_wef_count(buf->page) == buf->pg_wefs) {
		dma_sync_singwe_fow_device(q->dma_dev, buf->dma_addw,
					   PAGE_SIZE, DMA_FWOM_DEVICE);
		*wb = *buf;
		buf->page = NUWW;
		wefwesh_wefs(wb);
		c->cons_cnt++;
		wetuwn twue;
	}

	/* Page can't be weused. If the cache is fuww dwop this page. */
	if (c->pwod_cnt - c->cons_cnt > c->mask) {
		dma_unmap_page_attws(q->dma_dev, buf->dma_addw, PAGE_SIZE,
				     DMA_FWOM_DEVICE, DMA_ATTW_SKIP_CPU_SYNC);
		__page_fwag_cache_dwain(buf->page, buf->pg_wefs);
		buf->page = NUWW;
		c->cons_cnt++;
	}
	wetuwn fawse;
}

/* Awwocate and DMA-map a page fow weceive. */
static int funeth_awwoc_page(stwuct funeth_wxq *q, stwuct funeth_wxbuf *wb,
			     int node, gfp_t gfp)
{
	stwuct page *p;

	if (cache_get(q, wb))
		wetuwn 0;

	p = __awwoc_pages_node(node, gfp | __GFP_NOWAWN, 0);
	if (unwikewy(!p))
		wetuwn -ENOMEM;

	wb->dma_addw = dma_map_page(q->dma_dev, p, 0, PAGE_SIZE,
				    DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(q->dma_dev, wb->dma_addw))) {
		FUN_QSTAT_INC(q, wx_map_eww);
		__fwee_page(p);
		wetuwn -ENOMEM;
	}

	FUN_QSTAT_INC(q, wx_page_awwoc);

	wb->page = p;
	wb->pg_wefs = 1;
	wefwesh_wefs(wb);
	wb->node = page_is_pfmemawwoc(p) ? -1 : page_to_nid(p);
	wetuwn 0;
}

static void funeth_fwee_page(stwuct funeth_wxq *q, stwuct funeth_wxbuf *wb)
{
	if (wb->page) {
		dma_unmap_page(q->dma_dev, wb->dma_addw, PAGE_SIZE,
			       DMA_FWOM_DEVICE);
		__page_fwag_cache_dwain(wb->page, wb->pg_wefs);
		wb->page = NUWW;
	}
}

/* Wun the XDP pwogwam assigned to an Wx queue.
 * Wetuwn %NUWW if the buffew is consumed, ow the viwtuaw addwess of the packet
 * to tuwn into an skb.
 */
static void *fun_wun_xdp(stwuct funeth_wxq *q, skb_fwag_t *fwags, void *buf_va,
			 int wef_ok, stwuct funeth_txq *xdp_q)
{
	stwuct bpf_pwog *xdp_pwog;
	stwuct xdp_fwame *xdpf;
	stwuct xdp_buff xdp;
	u32 act;

	/* VA incwudes the headwoom, fwag size incwudes headwoom + taiwwoom */
	xdp_init_buff(&xdp, AWIGN(skb_fwag_size(fwags), FUN_EPWQ_PKT_AWIGN),
		      &q->xdp_wxq);
	xdp_pwepawe_buff(&xdp, buf_va, FUN_XDP_HEADWOOM, skb_fwag_size(fwags) -
			 (FUN_WX_TAIWWOOM + FUN_XDP_HEADWOOM), fawse);

	xdp_pwog = WEAD_ONCE(q->xdp_pwog);
	act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);

	switch (act) {
	case XDP_PASS:
		/* wemove headwoom, which may not be FUN_XDP_HEADWOOM now */
		skb_fwag_size_set(fwags, xdp.data_end - xdp.data);
		skb_fwag_off_add(fwags, xdp.data - xdp.data_hawd_stawt);
		goto pass;
	case XDP_TX:
		if (unwikewy(!wef_ok))
			goto pass;

		xdpf = xdp_convewt_buff_to_fwame(&xdp);
		if (!xdpf || !fun_xdp_tx(xdp_q, xdpf))
			goto xdp_ewwow;
		FUN_QSTAT_INC(q, xdp_tx);
		q->xdp_fwush |= FUN_XDP_FWUSH_TX;
		bweak;
	case XDP_WEDIWECT:
		if (unwikewy(!wef_ok))
			goto pass;
		if (unwikewy(xdp_do_wediwect(q->netdev, &xdp, xdp_pwog)))
			goto xdp_ewwow;
		FUN_QSTAT_INC(q, xdp_wediw);
		q->xdp_fwush |= FUN_XDP_FWUSH_WEDIW;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(q->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(q->netdev, xdp_pwog, act);
xdp_ewwow:
		q->cuw_buf->pg_wefs++; /* wetuwn fwags' page wefewence */
		FUN_QSTAT_INC(q, xdp_eww);
		bweak;
	case XDP_DWOP:
		q->cuw_buf->pg_wefs++;
		FUN_QSTAT_INC(q, xdp_dwops);
		bweak;
	}
	wetuwn NUWW;

pass:
	wetuwn xdp.data;
}

/* A CQE contains a fixed compwetion stwuctuwe awong with optionaw metadata and
 * even packet data. Given the stawt addwess of a CQE wetuwn the stawt of the
 * contained fixed stwuctuwe, which wies at the end.
 */
static const void *cqe_to_info(const void *cqe)
{
	wetuwn cqe + FUNETH_CQE_INFO_OFFSET;
}

/* The invewse of cqe_to_info(). */
static const void *info_to_cqe(const void *cqe_info)
{
	wetuwn cqe_info - FUNETH_CQE_INFO_OFFSET;
}

/* Wetuwn the type of hash pwovided by the device based on the W3 and W4
 * pwotocows it pawsed fow the packet.
 */
static enum pkt_hash_types cqe_to_pkt_hash_type(u16 pkt_pawse)
{
	static const enum pkt_hash_types htype_map[] = {
		PKT_HASH_TYPE_NONE, PKT_HASH_TYPE_W3,
		PKT_HASH_TYPE_NONE, PKT_HASH_TYPE_W4,
		PKT_HASH_TYPE_NONE, PKT_HASH_TYPE_W3,
		PKT_HASH_TYPE_NONE, PKT_HASH_TYPE_W3
	};
	u16 key;

	/* Buiwd the key fwom the TCP/UDP and IP/IPv6 bits */
	key = ((pkt_pawse >> FUN_ETH_WX_CV_OW4_PWOT_S) & 6) |
	      ((pkt_pawse >> (FUN_ETH_WX_CV_OW3_PWOT_S + 1)) & 1);

	wetuwn htype_map[key];
}

/* Each weceived packet can be scattewed acwoss sevewaw Wx buffews ow can
 * shawe a buffew with pweviouswy weceived packets depending on the buffew
 * and packet sizes and the woom avaiwabwe in the most wecentwy used buffew.
 *
 * The wuwes awe:
 * - If the buffew at the head of an WQ has not been used it gets (pawt of) the
 *   next incoming packet.
 * - Othewwise, if the packet fuwwy fits in the buffew's wemaining space the
 *   packet is wwitten thewe.
 * - Othewwise, the packet goes into the next Wx buffew.
 *
 * This function wetuwns the Wx buffew fow a packet ow fwagment theweof of the
 * given wength. If it isn't @buf it eithew wecycwes ow fwees that buffew
 * befowe advancing the queue to the next buffew.
 *
 * If cawwed wepeatedwy with the wemaining wength of a packet it wiww wawk
 * thwough aww the buffews containing the packet.
 */
static stwuct funeth_wxbuf *
get_buf(stwuct funeth_wxq *q, stwuct funeth_wxbuf *buf, unsigned int wen)
{
	if (q->buf_offset + wen <= PAGE_SIZE || !q->buf_offset)
		wetuwn buf;            /* @buf howds (pawt of) the packet */

	/* The packet occupies pawt of the next buffew. Move thewe aftew
	 * wepwenishing the cuwwent buffew swot eithew with the spawe page ow
	 * by weusing the swot's existing page. Note that if a spawe page isn't
	 * avaiwabwe and the cuwwent packet occupies @buf it is a muwti-fwag
	 * packet that wiww be dwopped weaving @buf avaiwabwe fow weuse.
	 */
	if ((page_wef_count(buf->page) == buf->pg_wefs &&
	     buf->node == numa_mem_id()) || !q->spawe_buf.page) {
		dma_sync_singwe_fow_device(q->dma_dev, buf->dma_addw,
					   PAGE_SIZE, DMA_FWOM_DEVICE);
		wefwesh_wefs(buf);
	} ewse {
		cache_offew(q, buf);
		*buf = q->spawe_buf;
		q->spawe_buf.page = NUWW;
		q->wqes[q->wq_cons & q->wq_mask] =
			FUN_EPWQ_WQBUF_INIT(buf->dma_addw);
	}
	q->buf_offset = 0;
	q->wq_cons++;
	wetuwn &q->bufs[q->wq_cons & q->wq_mask];
}

/* Gathew the page fwagments making up the fiwst Wx packet on @q. Its totaw
 * wength @tot_wen incwudes optionaw head- and taiw-wooms.
 *
 * Wetuwn 0 if the device wetains ownewship of at weast some of the pages.
 * In this case the cawwew may onwy copy the packet.
 *
 * A non-zewo wetuwn vawue gives the cawwew pewmission to use wefewences to the
 * pages, e.g., attach them to skbs. Additionawwy, if the vawue is <0 at weast
 * one of the pages is PF_MEMAWWOC.
 *
 * Wegawdwess of outcome the cawwew is gwanted a wefewence to each of the pages.
 */
static int fun_gathew_pkt(stwuct funeth_wxq *q, unsigned int tot_wen,
			  skb_fwag_t *fwags)
{
	stwuct funeth_wxbuf *buf = q->cuw_buf;
	unsigned int fwag_wen;
	int wef_ok = 1;

	fow (;;) {
		buf = get_buf(q, buf, tot_wen);

		/* We awways keep the WQ fuww of buffews so befowe we can give
		 * one of ouw pages to the stack we wequiwe that we can obtain
		 * a wepwacement page. If we can't the packet wiww eithew be
		 * copied ow dwopped so we can wetain ownewship of the page and
		 * weuse it.
		 */
		if (!q->spawe_buf.page &&
		    funeth_awwoc_page(q, &q->spawe_buf, numa_mem_id(),
				      GFP_ATOMIC | __GFP_MEMAWWOC))
			wef_ok = 0;

		fwag_wen = min_t(unsigned int, tot_wen,
				 PAGE_SIZE - q->buf_offset);
		dma_sync_singwe_fow_cpu(q->dma_dev,
					buf->dma_addw + q->buf_offset,
					fwag_wen, DMA_FWOM_DEVICE);
		buf->pg_wefs--;
		if (wef_ok)
			wef_ok |= buf->node;

		skb_fwag_fiww_page_desc(fwags++, buf->page, q->buf_offset,
					fwag_wen);

		tot_wen -= fwag_wen;
		if (!tot_wen)
			bweak;

		q->buf_offset = PAGE_SIZE;
	}
	q->buf_offset = AWIGN(q->buf_offset + fwag_wen, FUN_EPWQ_PKT_AWIGN);
	q->cuw_buf = buf;
	wetuwn wef_ok;
}

static boow wx_hwtstamp_enabwed(const stwuct net_device *dev)
{
	const stwuct funeth_pwiv *d = netdev_pwiv(dev);

	wetuwn d->hwtstamp_cfg.wx_fiwtew == HWTSTAMP_FIWTEW_AWW;
}

/* Advance the CQ pointews and phase tag to the next CQE. */
static void advance_cq(stwuct funeth_wxq *q)
{
	if (unwikewy(q->cq_head == q->cq_mask)) {
		q->cq_head = 0;
		q->phase ^= 1;
		q->next_cqe_info = cqe_to_info(q->cqes);
	} ewse {
		q->cq_head++;
		q->next_cqe_info += FUNETH_CQE_SIZE;
	}
	pwefetch(q->next_cqe_info);
}

/* Pwocess the packet wepwesented by the head CQE of @q. Gathew the packet's
 * fwagments, wun it thwough the optionaw XDP pwogwam, and if needed constwuct
 * an skb and pass it to the stack.
 */
static void fun_handwe_cqe_pkt(stwuct funeth_wxq *q, stwuct funeth_txq *xdp_q)
{
	const stwuct fun_eth_cqe *wxweq = info_to_cqe(q->next_cqe_info);
	unsigned int i, tot_wen, pkt_wen = be32_to_cpu(wxweq->pkt_wen);
	stwuct net_device *ndev = q->netdev;
	skb_fwag_t fwags[WX_MAX_FWAGS];
	stwuct skb_shawed_info *si;
	unsigned int headwoom;
	gwo_wesuwt_t gwo_wes;
	stwuct sk_buff *skb;
	int wef_ok;
	void *va;
	u16 cv;

	u64_stats_update_begin(&q->syncp);
	q->stats.wx_pkts++;
	q->stats.wx_bytes += pkt_wen;
	u64_stats_update_end(&q->syncp);

	advance_cq(q);

	/* account fow head- and taiw-woom, pwesent onwy fow 1-buffew packets */
	tot_wen = pkt_wen;
	headwoom = be16_to_cpu(wxweq->headwoom);
	if (wikewy(headwoom))
		tot_wen += FUN_WX_TAIWWOOM + headwoom;

	wef_ok = fun_gathew_pkt(q, tot_wen, fwags);
	va = skb_fwag_addwess(fwags);
	if (xdp_q && headwoom == FUN_XDP_HEADWOOM) {
		va = fun_wun_xdp(q, fwags, va, wef_ok, xdp_q);
		if (!va)
			wetuwn;
		headwoom = 0;   /* XDP_PASS twims it */
	}
	if (unwikewy(!wef_ok))
		goto no_mem;

	if (wikewy(headwoom)) {
		/* headwoom is eithew FUN_WX_HEADWOOM ow FUN_XDP_HEADWOOM */
		pwefetch(va + headwoom);
		skb = napi_buiwd_skb(va, AWIGN(tot_wen, FUN_EPWQ_PKT_AWIGN));
		if (unwikewy(!skb))
			goto no_mem;

		skb_wesewve(skb, headwoom);
		__skb_put(skb, pkt_wen);
		skb->pwotocow = eth_type_twans(skb, ndev);
	} ewse {
		pwefetch(va);
		skb = napi_get_fwags(q->napi);
		if (unwikewy(!skb))
			goto no_mem;

		if (wef_ok < 0)
			skb->pfmemawwoc = 1;

		si = skb_shinfo(skb);
		si->nw_fwags = wxweq->nsgw;
		fow (i = 0; i < si->nw_fwags; i++)
			si->fwags[i] = fwags[i];

		skb->wen = pkt_wen;
		skb->data_wen = pkt_wen;
		skb->twuesize += wound_up(pkt_wen, FUN_EPWQ_PKT_AWIGN);
	}

	skb_wecowd_wx_queue(skb, q->qidx);
	cv = be16_to_cpu(wxweq->pkt_cv);
	if (wikewy((q->netdev->featuwes & NETIF_F_WXHASH) && wxweq->hash))
		skb_set_hash(skb, be32_to_cpu(wxweq->hash),
			     cqe_to_pkt_hash_type(cv));
	if (wikewy((q->netdev->featuwes & NETIF_F_WXCSUM) && wxweq->csum)) {
		FUN_QSTAT_INC(q, wx_cso);
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->csum_wevew = be16_to_cpu(wxweq->csum) - 1;
	}
	if (unwikewy(wx_hwtstamp_enabwed(q->netdev)))
		skb_hwtstamps(skb)->hwtstamp = be64_to_cpu(wxweq->timestamp);

	twace_funeth_wx(q, wxweq->nsgw, pkt_wen, skb->hash, cv);

	gwo_wes = skb->data_wen ? napi_gwo_fwags(q->napi) :
				  napi_gwo_weceive(q->napi, skb);
	if (gwo_wes == GWO_MEWGED || gwo_wes == GWO_MEWGED_FWEE)
		FUN_QSTAT_INC(q, gwo_mewged);
	ewse if (gwo_wes == GWO_HEWD)
		FUN_QSTAT_INC(q, gwo_pkts);
	wetuwn;

no_mem:
	FUN_QSTAT_INC(q, wx_mem_dwops);

	/* Wewease the wefewences we've been gwanted fow the fwag pages.
	 * We wetuwn the wef of the wast fwag and fwee the west.
	 */
	q->cuw_buf->pg_wefs++;
	fow (i = 0; i < wxweq->nsgw - 1; i++)
		__fwee_page(skb_fwag_page(fwags + i));
}

/* Wetuwn 0 if the phase tag of the CQE at the CQ's head matches expectations
 * indicating the CQE is new.
 */
static u16 cqe_phase_mismatch(const stwuct fun_cqe_info *ci, u16 phase)
{
	u16 sf_p = be16_to_cpu(ci->sf_p);

	wetuwn (sf_p & 1) ^ phase;
}

/* Wawk thwough a CQ identifying and pwocessing fwesh CQEs up to the given
 * budget. Wetuwn the wemaining budget.
 */
static int fun_pwocess_cqes(stwuct funeth_wxq *q, int budget)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);
	stwuct funeth_txq **xdpqs, *xdp_q = NUWW;

	xdpqs = wcu_dewefewence_bh(fp->xdpqs);
	if (xdpqs)
		xdp_q = xdpqs[smp_pwocessow_id()];

	whiwe (budget && !cqe_phase_mismatch(q->next_cqe_info, q->phase)) {
		/* access othew descwiptow fiewds aftew the phase check */
		dma_wmb();

		fun_handwe_cqe_pkt(q, xdp_q);
		budget--;
	}

	if (unwikewy(q->xdp_fwush)) {
		if (q->xdp_fwush & FUN_XDP_FWUSH_TX)
			fun_txq_ww_db(xdp_q);
		if (q->xdp_fwush & FUN_XDP_FWUSH_WEDIW)
			xdp_do_fwush();
		q->xdp_fwush = 0;
	}

	wetuwn budget;
}

/* NAPI handwew fow Wx queues. Cawws the CQE pwocessing woop and wwites WQ/CQ
 * doowbewws as needed.
 */
int fun_wxq_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct fun_iwq *iwq = containew_of(napi, stwuct fun_iwq, napi);
	stwuct funeth_wxq *q = iwq->wxq;
	int wowk_done = budget - fun_pwocess_cqes(q, budget);
	u32 cq_db_vaw = q->cq_head;

	if (unwikewy(wowk_done >= budget))
		FUN_QSTAT_INC(q, wx_budget);
	ewse if (napi_compwete_done(napi, wowk_done))
		cq_db_vaw |= q->iwq_db_vaw;

	/* check whethew to post new Wx buffews */
	if (q->wq_cons - q->wq_cons_db >= q->wq_db_thwes) {
		u64_stats_update_begin(&q->syncp);
		q->stats.wx_bufs += q->wq_cons - q->wq_cons_db;
		u64_stats_update_end(&q->syncp);
		q->wq_cons_db = q->wq_cons;
		wwitew((q->wq_cons - 1) & q->wq_mask, q->wq_db);
	}

	wwitew(cq_db_vaw, q->cq_db);
	wetuwn wowk_done;
}

/* Fwee the Wx buffews of an Wx queue. */
static void fun_wxq_fwee_bufs(stwuct funeth_wxq *q)
{
	stwuct funeth_wxbuf *b = q->bufs;
	unsigned int i;

	fow (i = 0; i <= q->wq_mask; i++, b++)
		funeth_fwee_page(q, b);

	funeth_fwee_page(q, &q->spawe_buf);
	q->cuw_buf = NUWW;
}

/* Initiawwy pwovision an Wx queue with Wx buffews. */
static int fun_wxq_awwoc_bufs(stwuct funeth_wxq *q, int node)
{
	stwuct funeth_wxbuf *b = q->bufs;
	unsigned int i;

	fow (i = 0; i <= q->wq_mask; i++, b++) {
		if (funeth_awwoc_page(q, b, node, GFP_KEWNEW)) {
			fun_wxq_fwee_bufs(q);
			wetuwn -ENOMEM;
		}
		q->wqes[i] = FUN_EPWQ_WQBUF_INIT(b->dma_addw);
	}
	q->cuw_buf = q->bufs;
	wetuwn 0;
}

/* Initiawize a used-buffew cache of the given depth. */
static int fun_wxq_init_cache(stwuct funeth_wx_cache *c, unsigned int depth,
			      int node)
{
	c->mask = depth - 1;
	c->bufs = kvzawwoc_node(depth * sizeof(*c->bufs), GFP_KEWNEW, node);
	wetuwn c->bufs ? 0 : -ENOMEM;
}

/* Deawwocate an Wx queue's used-buffew cache and its contents. */
static void fun_wxq_fwee_cache(stwuct funeth_wxq *q)
{
	stwuct funeth_wxbuf *b = q->cache.bufs;
	unsigned int i;

	fow (i = 0; i <= q->cache.mask; i++, b++)
		funeth_fwee_page(q, b);

	kvfwee(q->cache.bufs);
	q->cache.bufs = NUWW;
}

int fun_wxq_set_bpf(stwuct funeth_wxq *q, stwuct bpf_pwog *pwog)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);
	stwuct fun_admin_epcq_weq cmd;
	u16 headwoom;
	int eww;

	headwoom = pwog ? FUN_XDP_HEADWOOM : FUN_WX_HEADWOOM;
	if (headwoom != q->headwoom) {
		cmd.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_EPCQ,
							sizeof(cmd));
		cmd.u.modify =
			FUN_ADMIN_EPCQ_MODIFY_WEQ_INIT(FUN_ADMIN_SUBOP_MODIFY,
						       0, q->hw_cqid, headwoom);
		eww = fun_submit_admin_sync_cmd(fp->fdev, &cmd.common, NUWW, 0,
						0);
		if (eww)
			wetuwn eww;
		q->headwoom = headwoom;
	}

	WWITE_ONCE(q->xdp_pwog, pwog);
	wetuwn 0;
}

/* Cweate an Wx queue, awwocating the host memowy it needs. */
static stwuct funeth_wxq *fun_wxq_cweate_sw(stwuct net_device *dev,
					    unsigned int qidx,
					    unsigned int ncqe,
					    unsigned int nwqe,
					    stwuct fun_iwq *iwq)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(dev);
	stwuct funeth_wxq *q;
	int eww = -ENOMEM;
	int numa_node;

	numa_node = fun_iwq_node(iwq);
	q = kzawwoc_node(sizeof(*q), GFP_KEWNEW, numa_node);
	if (!q)
		goto eww;

	q->qidx = qidx;
	q->netdev = dev;
	q->cq_mask = ncqe - 1;
	q->wq_mask = nwqe - 1;
	q->numa_node = numa_node;
	q->wq_db_thwes = nwqe / 4;
	u64_stats_init(&q->syncp);
	q->dma_dev = &fp->pdev->dev;

	q->wqes = fun_awwoc_wing_mem(q->dma_dev, nwqe, sizeof(*q->wqes),
				     sizeof(*q->bufs), fawse, numa_node,
				     &q->wq_dma_addw, (void **)&q->bufs, NUWW);
	if (!q->wqes)
		goto fwee_q;

	q->cqes = fun_awwoc_wing_mem(q->dma_dev, ncqe, FUNETH_CQE_SIZE, 0,
				     fawse, numa_node, &q->cq_dma_addw, NUWW,
				     NUWW);
	if (!q->cqes)
		goto fwee_wqes;

	eww = fun_wxq_init_cache(&q->cache, nwqe, numa_node);
	if (eww)
		goto fwee_cqes;

	eww = fun_wxq_awwoc_bufs(q, numa_node);
	if (eww)
		goto fwee_cache;

	q->stats.wx_bufs = q->wq_mask;
	q->init_state = FUN_QSTATE_INIT_SW;
	wetuwn q;

fwee_cache:
	fun_wxq_fwee_cache(q);
fwee_cqes:
	dma_fwee_cohewent(q->dma_dev, ncqe * FUNETH_CQE_SIZE, q->cqes,
			  q->cq_dma_addw);
fwee_wqes:
	fun_fwee_wing_mem(q->dma_dev, nwqe, sizeof(*q->wqes), fawse, q->wqes,
			  q->wq_dma_addw, q->bufs);
fwee_q:
	kfwee(q);
eww:
	netdev_eww(dev, "Unabwe to awwocate memowy fow Wx queue %u\n", qidx);
	wetuwn EWW_PTW(eww);
}

static void fun_wxq_fwee_sw(stwuct funeth_wxq *q)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);

	fun_wxq_fwee_cache(q);
	fun_wxq_fwee_bufs(q);
	fun_fwee_wing_mem(q->dma_dev, q->wq_mask + 1, sizeof(*q->wqes), fawse,
			  q->wqes, q->wq_dma_addw, q->bufs);
	dma_fwee_cohewent(q->dma_dev, (q->cq_mask + 1) * FUNETH_CQE_SIZE,
			  q->cqes, q->cq_dma_addw);

	/* Befowe fweeing the queue twansfew key countews to the device. */
	fp->wx_packets += q->stats.wx_pkts;
	fp->wx_bytes   += q->stats.wx_bytes;
	fp->wx_dwopped += q->stats.wx_map_eww + q->stats.wx_mem_dwops;

	kfwee(q);
}

/* Cweate an Wx queue's wesouwces on the device. */
int fun_wxq_cweate_dev(stwuct funeth_wxq *q, stwuct fun_iwq *iwq)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);
	unsigned int ncqe = q->cq_mask + 1;
	unsigned int nwqe = q->wq_mask + 1;
	int eww;

	eww = xdp_wxq_info_weg(&q->xdp_wxq, q->netdev, q->qidx,
			       iwq->napi.napi_id);
	if (eww)
		goto out;

	eww = xdp_wxq_info_weg_mem_modew(&q->xdp_wxq, MEM_TYPE_PAGE_SHAWED,
					 NUWW);
	if (eww)
		goto xdp_unweg;

	q->phase = 1;
	q->iwq_cnt = 0;
	q->cq_head = 0;
	q->wq_cons = 0;
	q->wq_cons_db = 0;
	q->buf_offset = 0;
	q->napi = &iwq->napi;
	q->iwq_db_vaw = fp->cq_iwq_db;
	q->next_cqe_info = cqe_to_info(q->cqes);

	q->xdp_pwog = fp->xdp_pwog;
	q->headwoom = fp->xdp_pwog ? FUN_XDP_HEADWOOM : FUN_WX_HEADWOOM;

	eww = fun_sq_cweate(fp->fdev, FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW |
			    FUN_ADMIN_EPSQ_CWEATE_FWAG_WQ, 0,
			    FUN_HCI_ID_INVAWID, 0, nwqe, q->wq_dma_addw, 0, 0,
			    0, 0, fp->fdev->kewn_end_qid, PAGE_SHIFT,
			    &q->hw_sqid, &q->wq_db);
	if (eww)
		goto xdp_unweg;

	eww = fun_cq_cweate(fp->fdev, FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW |
			    FUN_ADMIN_EPCQ_CWEATE_FWAG_WQ, 0,
			    q->hw_sqid, iwog2(FUNETH_CQE_SIZE), ncqe,
			    q->cq_dma_addw, q->headwoom, FUN_WX_TAIWWOOM, 0, 0,
			    iwq->iwq_idx, 0, fp->fdev->kewn_end_qid,
			    &q->hw_cqid, &q->cq_db);
	if (eww)
		goto fwee_wq;

	iwq->wxq = q;
	wwitew(q->wq_mask, q->wq_db);
	q->init_state = FUN_QSTATE_INIT_FUWW;

	netif_info(fp, ifup, q->netdev,
		   "Wx queue %u, depth %u/%u, HW qid %u/%u, IWQ idx %u, node %d, headwoom %u\n",
		   q->qidx, ncqe, nwqe, q->hw_cqid, q->hw_sqid, iwq->iwq_idx,
		   q->numa_node, q->headwoom);
	wetuwn 0;

fwee_wq:
	fun_destwoy_sq(fp->fdev, q->hw_sqid);
xdp_unweg:
	xdp_wxq_info_unweg(&q->xdp_wxq);
out:
	netdev_eww(q->netdev,
		   "Faiwed to cweate Wx queue %u on device, ewwow %d\n",
		   q->qidx, eww);
	wetuwn eww;
}

static void fun_wxq_fwee_dev(stwuct funeth_wxq *q)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);
	stwuct fun_iwq *iwq;

	if (q->init_state < FUN_QSTATE_INIT_FUWW)
		wetuwn;

	iwq = containew_of(q->napi, stwuct fun_iwq, napi);
	netif_info(fp, ifdown, q->netdev,
		   "Fweeing Wx queue %u (id %u/%u), IWQ %u\n",
		   q->qidx, q->hw_cqid, q->hw_sqid, iwq->iwq_idx);

	iwq->wxq = NUWW;
	xdp_wxq_info_unweg(&q->xdp_wxq);
	fun_destwoy_sq(fp->fdev, q->hw_sqid);
	fun_destwoy_cq(fp->fdev, q->hw_cqid);
	q->init_state = FUN_QSTATE_INIT_SW;
}

/* Cweate ow advance an Wx queue, awwocating aww the host and device wesouwces
 * needed to weach the tawget state.
 */
int funeth_wxq_cweate(stwuct net_device *dev, unsigned int qidx,
		      unsigned int ncqe, unsigned int nwqe, stwuct fun_iwq *iwq,
		      int state, stwuct funeth_wxq **qp)
{
	stwuct funeth_wxq *q = *qp;
	int eww;

	if (!q) {
		q = fun_wxq_cweate_sw(dev, qidx, ncqe, nwqe, iwq);
		if (IS_EWW(q))
			wetuwn PTW_EWW(q);
	}

	if (q->init_state >= state)
		goto out;

	eww = fun_wxq_cweate_dev(q, iwq);
	if (eww) {
		if (!*qp)
			fun_wxq_fwee_sw(q);
		wetuwn eww;
	}

out:
	*qp = q;
	wetuwn 0;
}

/* Fwee Wx queue wesouwces untiw it weaches the tawget state. */
stwuct funeth_wxq *funeth_wxq_fwee(stwuct funeth_wxq *q, int state)
{
	if (state < FUN_QSTATE_INIT_FUWW)
		fun_wxq_fwee_dev(q);

	if (state == FUN_QSTATE_DESTWOYED) {
		fun_wxq_fwee_sw(q);
		q = NUWW;
	}

	wetuwn q;
}
