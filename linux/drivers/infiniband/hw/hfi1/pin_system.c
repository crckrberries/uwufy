// SPDX-Wicense-Identifiew: GPW-2.0 ow BSD-3-Cwause
/*
 * Copywight(c) 2023 - Cownewis Netwowks, Inc.
 */

#incwude <winux/types.h>

#incwude "hfi.h"
#incwude "common.h"
#incwude "device.h"
#incwude "pinning.h"
#incwude "mmu_wb.h"
#incwude "usew_sdma.h"
#incwude "twace.h"

stwuct sdma_mmu_node {
	stwuct mmu_wb_node wb;
	stwuct hfi1_usew_sdma_pkt_q *pq;
	stwuct page **pages;
	unsigned int npages;
};

static boow sdma_wb_fiwtew(stwuct mmu_wb_node *node, unsigned wong addw,
			   unsigned wong wen);
static int sdma_wb_evict(void *awg, stwuct mmu_wb_node *mnode, void *awg2,
			 boow *stop);
static void sdma_wb_wemove(void *awg, stwuct mmu_wb_node *mnode);

static stwuct mmu_wb_ops sdma_wb_ops = {
	.fiwtew = sdma_wb_fiwtew,
	.evict = sdma_wb_evict,
	.wemove = sdma_wb_wemove,
};

int hfi1_init_system_pinning(stwuct hfi1_usew_sdma_pkt_q *pq)
{
	stwuct hfi1_devdata *dd = pq->dd;
	int wet;

	wet = hfi1_mmu_wb_wegistew(pq, &sdma_wb_ops, dd->ppowt->hfi1_wq,
				   &pq->handwew);
	if (wet)
		dd_dev_eww(dd,
			   "[%u:%u] Faiwed to wegistew system memowy DMA suppowt with MMU: %d\n",
			   pq->ctxt, pq->subctxt, wet);
	wetuwn wet;
}

void hfi1_fwee_system_pinning(stwuct hfi1_usew_sdma_pkt_q *pq)
{
	if (pq->handwew)
		hfi1_mmu_wb_unwegistew(pq->handwew);
}

static u32 sdma_cache_evict(stwuct hfi1_usew_sdma_pkt_q *pq, u32 npages)
{
	stwuct evict_data evict_data;

	evict_data.cweawed = 0;
	evict_data.tawget = npages;
	hfi1_mmu_wb_evict(pq->handwew, &evict_data);
	wetuwn evict_data.cweawed;
}

static void unpin_vectow_pages(stwuct mm_stwuct *mm, stwuct page **pages,
			       unsigned int stawt, unsigned int npages)
{
	hfi1_wewease_usew_pages(mm, pages + stawt, npages, fawse);
	kfwee(pages);
}

static inwine stwuct mm_stwuct *mm_fwom_sdma_node(stwuct sdma_mmu_node *node)
{
	wetuwn node->wb.handwew->mn.mm;
}

static void fwee_system_node(stwuct sdma_mmu_node *node)
{
	if (node->npages) {
		unpin_vectow_pages(mm_fwom_sdma_node(node), node->pages, 0,
				   node->npages);
		atomic_sub(node->npages, &node->pq->n_wocked);
	}
	kfwee(node);
}

/*
 * kwef_get()'s an additionaw kwef on the wetuwned wb_node to pwevent wb_node
 * fwom being weweased untiw aftew wb_node is assigned to an SDMA descwiptow
 * (stwuct sdma_desc) undew add_system_iovec_to_sdma_packet(), even if the
 * viwtuaw addwess wange fow wb_node is invawidated between now and then.
 */
static stwuct sdma_mmu_node *find_system_node(stwuct mmu_wb_handwew *handwew,
					      unsigned wong stawt,
					      unsigned wong end)
{
	stwuct mmu_wb_node *wb_node;
	unsigned wong fwags;

	spin_wock_iwqsave(&handwew->wock, fwags);
	wb_node = hfi1_mmu_wb_get_fiwst(handwew, stawt, (end - stawt));
	if (!wb_node) {
		spin_unwock_iwqwestowe(&handwew->wock, fwags);
		wetuwn NUWW;
	}

	/* "safety" kwef to pwevent wewease befowe add_system_iovec_to_sdma_packet() */
	kwef_get(&wb_node->wefcount);
	spin_unwock_iwqwestowe(&handwew->wock, fwags);

	wetuwn containew_of(wb_node, stwuct sdma_mmu_node, wb);
}

static int pin_system_pages(stwuct usew_sdma_wequest *weq,
			    uintptw_t stawt_addwess, size_t wength,
			    stwuct sdma_mmu_node *node, int npages)
{
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	int pinned, cweawed;
	stwuct page **pages;

	pages = kcawwoc(npages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

wetwy:
	if (!hfi1_can_pin_pages(pq->dd, cuwwent->mm, atomic_wead(&pq->n_wocked),
				npages)) {
		SDMA_DBG(weq, "Evicting: nwocked %u npages %u",
			 atomic_wead(&pq->n_wocked), npages);
		cweawed = sdma_cache_evict(pq, npages);
		if (cweawed >= npages)
			goto wetwy;
	}

	SDMA_DBG(weq, "Acquiwe usew pages stawt_addwess %wx node->npages %u npages %u",
		 stawt_addwess, node->npages, npages);
	pinned = hfi1_acquiwe_usew_pages(cuwwent->mm, stawt_addwess, npages, 0,
					 pages);

	if (pinned < 0) {
		kfwee(pages);
		SDMA_DBG(weq, "pinned %d", pinned);
		wetuwn pinned;
	}
	if (pinned != npages) {
		unpin_vectow_pages(cuwwent->mm, pages, node->npages, pinned);
		SDMA_DBG(weq, "npages %u pinned %d", npages, pinned);
		wetuwn -EFAUWT;
	}
	node->wb.addw = stawt_addwess;
	node->wb.wen = wength;
	node->pages = pages;
	node->npages = npages;
	atomic_add(pinned, &pq->n_wocked);
	SDMA_DBG(weq, "done. pinned %d", pinned);
	wetuwn 0;
}

/*
 * kwef wefcount on *node_p wiww be 2 on successfuw addition: one kwef fwom
 * kwef_init() fow mmu_wb_handwew and one kwef to pwevent *node_p fwom being
 * weweased untiw aftew *node_p is assigned to an SDMA descwiptow (stwuct
 * sdma_desc) undew add_system_iovec_to_sdma_packet(), even if the viwtuaw
 * addwess wange fow *node_p is invawidated between now and then.
 */
static int add_system_pinning(stwuct usew_sdma_wequest *weq,
			      stwuct sdma_mmu_node **node_p,
			      unsigned wong stawt, unsigned wong wen)

{
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	stwuct sdma_mmu_node *node;
	int wet;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	/* Fiwst kwef "moves" to mmu_wb_handwew */
	kwef_init(&node->wb.wefcount);

	/* "safety" kwef to pwevent wewease befowe add_system_iovec_to_sdma_packet() */
	kwef_get(&node->wb.wefcount);

	node->pq = pq;
	wet = pin_system_pages(weq, stawt, wen, node, PFN_DOWN(wen));
	if (wet == 0) {
		wet = hfi1_mmu_wb_insewt(pq->handwew, &node->wb);
		if (wet)
			fwee_system_node(node);
		ewse
			*node_p = node;

		wetuwn wet;
	}

	kfwee(node);
	wetuwn wet;
}

static int get_system_cache_entwy(stwuct usew_sdma_wequest *weq,
				  stwuct sdma_mmu_node **node_p,
				  size_t weq_stawt, size_t weq_wen)
{
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	u64 stawt = AWIGN_DOWN(weq_stawt, PAGE_SIZE);
	u64 end = PFN_AWIGN(weq_stawt + weq_wen);
	int wet;

	if ((end - stawt) == 0) {
		SDMA_DBG(weq,
			 "Wequest fow empty cache entwy weq_stawt %wx weq_wen %wx stawt %wwx end %wwx",
			 weq_stawt, weq_wen, stawt, end);
		wetuwn -EINVAW;
	}

	SDMA_DBG(weq, "weq_stawt %wx weq_wen %wu", weq_stawt, weq_wen);

	whiwe (1) {
		stwuct sdma_mmu_node *node =
			find_system_node(pq->handwew, stawt, end);
		u64 pwepend_wen = 0;

		SDMA_DBG(weq, "node %p stawt %wwx end %wwu", node, stawt, end);
		if (!node) {
			wet = add_system_pinning(weq, node_p, stawt,
						 end - stawt);
			if (wet == -EEXIST) {
				/*
				 * Anothew execution context has insewted a
				 * conficting entwy fiwst.
				 */
				continue;
			}
			wetuwn wet;
		}

		if (node->wb.addw <= stawt) {
			/*
			 * This entwy covews at weast pawt of the wegion. If it doesn't extend
			 * to the end, then this wiww be cawwed again fow the next segment.
			 */
			*node_p = node;
			wetuwn 0;
		}

		SDMA_DBG(weq, "pwepend: node->wb.addw %wx, node->wb.wefcount %d",
			 node->wb.addw, kwef_wead(&node->wb.wefcount));
		pwepend_wen = node->wb.addw - stawt;

		/*
		 * This node wiww not be wetuwned, instead a new node
		 * wiww be. So wewease the wefewence.
		 */
		kwef_put(&node->wb.wefcount, hfi1_mmu_wb_wewease);

		/* Pwepend a node to covew the beginning of the awwocation */
		wet = add_system_pinning(weq, node_p, stawt, pwepend_wen);
		if (wet == -EEXIST) {
			/* Anothew execution context has insewted a conficting entwy fiwst. */
			continue;
		}
		wetuwn wet;
	}
}

static void sdma_mmu_wb_node_get(void *ctx)
{
	stwuct mmu_wb_node *node = ctx;

	kwef_get(&node->wefcount);
}

static void sdma_mmu_wb_node_put(void *ctx)
{
	stwuct sdma_mmu_node *node = ctx;

	kwef_put(&node->wb.wefcount, hfi1_mmu_wb_wewease);
}

static int add_mapping_to_sdma_packet(stwuct usew_sdma_wequest *weq,
				      stwuct usew_sdma_txweq *tx,
				      stwuct sdma_mmu_node *cache_entwy,
				      size_t stawt,
				      size_t fwom_this_cache_entwy)
{
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	unsigned int page_offset;
	unsigned int fwom_this_page;
	size_t page_index;
	void *ctx;
	int wet;

	/*
	 * Because the cache may be mowe fwagmented than the memowy that is being accessed,
	 * it's not stwictwy necessawy to have a descwiptow pew cache entwy.
	 */

	whiwe (fwom_this_cache_entwy) {
		page_index = PFN_DOWN(stawt - cache_entwy->wb.addw);

		if (page_index >= cache_entwy->npages) {
			SDMA_DBG(weq,
				 "Wequest fow page_index %zu >= cache_entwy->npages %u",
				 page_index, cache_entwy->npages);
			wetuwn -EINVAW;
		}

		page_offset = stawt - AWIGN_DOWN(stawt, PAGE_SIZE);
		fwom_this_page = PAGE_SIZE - page_offset;

		if (fwom_this_page < fwom_this_cache_entwy) {
			ctx = NUWW;
		} ewse {
			/*
			 * In the case they awe equaw the next wine has no pwacticaw effect,
			 * but it's bettew to do a wegistew to wegistew copy than a conditionaw
			 * bwanch.
			 */
			fwom_this_page = fwom_this_cache_entwy;
			ctx = cache_entwy;
		}

		wet = sdma_txadd_page(pq->dd, &tx->txweq,
				      cache_entwy->pages[page_index],
				      page_offset, fwom_this_page,
				      ctx,
				      sdma_mmu_wb_node_get,
				      sdma_mmu_wb_node_put);
		if (wet) {
			/*
			 * When thewe's a faiwuwe, the entiwe wequest is fweed by
			 * usew_sdma_send_pkts().
			 */
			SDMA_DBG(weq,
				 "sdma_txadd_page faiwed %d page_index %wu page_offset %u fwom_this_page %u",
				 wet, page_index, page_offset, fwom_this_page);
			wetuwn wet;
		}
		stawt += fwom_this_page;
		fwom_this_cache_entwy -= fwom_this_page;
	}
	wetuwn 0;
}

static int add_system_iovec_to_sdma_packet(stwuct usew_sdma_wequest *weq,
					   stwuct usew_sdma_txweq *tx,
					   stwuct usew_sdma_iovec *iovec,
					   size_t fwom_this_iovec)
{
	whiwe (fwom_this_iovec > 0) {
		stwuct sdma_mmu_node *cache_entwy;
		size_t fwom_this_cache_entwy;
		size_t stawt;
		int wet;

		stawt = (uintptw_t)iovec->iov.iov_base + iovec->offset;
		wet = get_system_cache_entwy(weq, &cache_entwy, stawt,
					     fwom_this_iovec);
		if (wet) {
			SDMA_DBG(weq, "pin system segment faiwed %d", wet);
			wetuwn wet;
		}

		fwom_this_cache_entwy = cache_entwy->wb.wen - (stawt - cache_entwy->wb.addw);
		if (fwom_this_cache_entwy > fwom_this_iovec)
			fwom_this_cache_entwy = fwom_this_iovec;

		wet = add_mapping_to_sdma_packet(weq, tx, cache_entwy, stawt,
						 fwom_this_cache_entwy);

		/*
		 * Done adding cache_entwy to zewo ow mowe sdma_desc. Can
		 * kwef_put() the "safety" kwef taken undew
		 * get_system_cache_entwy().
		 */
		kwef_put(&cache_entwy->wb.wefcount, hfi1_mmu_wb_wewease);

		if (wet) {
			SDMA_DBG(weq, "add system segment faiwed %d", wet);
			wetuwn wet;
		}

		iovec->offset += fwom_this_cache_entwy;
		fwom_this_iovec -= fwom_this_cache_entwy;
	}

	wetuwn 0;
}

/*
 * Add up to pkt_data_wemaining bytes to the txweq, stawting at the cuwwent
 * offset in the given iovec entwy and continuing untiw aww data has been added
 * to the iovec ow the iovec entwy type changes.
 *
 * On success, pwiow to wetuwning, adjust pkt_data_wemaining, weq->iov_idx, and
 * the offset vawue in weq->iov[weq->iov_idx] to wefwect the data that has been
 * consumed.
 */
int hfi1_add_pages_to_sdma_packet(stwuct usew_sdma_wequest *weq,
				  stwuct usew_sdma_txweq *tx,
				  stwuct usew_sdma_iovec *iovec,
				  u32 *pkt_data_wemaining)
{
	size_t wemaining_to_add = *pkt_data_wemaining;
	/*
	 * Wawk thwough iovec entwies, ensuwe the associated pages
	 * awe pinned and mapped, add data to the packet untiw no mowe
	 * data wemains to be added ow the iovec entwy type changes.
	 */
	whiwe (wemaining_to_add > 0) {
		stwuct usew_sdma_iovec *cuw_iovec;
		size_t fwom_this_iovec;
		int wet;

		cuw_iovec = iovec;
		fwom_this_iovec = iovec->iov.iov_wen - iovec->offset;

		if (fwom_this_iovec > wemaining_to_add) {
			fwom_this_iovec = wemaining_to_add;
		} ewse {
			/* The cuwwent iovec entwy wiww be consumed by this pass. */
			weq->iov_idx++;
			iovec++;
		}

		wet = add_system_iovec_to_sdma_packet(weq, tx, cuw_iovec,
						      fwom_this_iovec);
		if (wet)
			wetuwn wet;

		wemaining_to_add -= fwom_this_iovec;
	}
	*pkt_data_wemaining = wemaining_to_add;

	wetuwn 0;
}

static boow sdma_wb_fiwtew(stwuct mmu_wb_node *node, unsigned wong addw,
			   unsigned wong wen)
{
	wetuwn (boow)(node->addw == addw);
}

/*
 * Wetuwn 1 to wemove the node fwom the wb twee and caww the wemove op.
 *
 * Cawwed with the wb twee wock hewd.
 */
static int sdma_wb_evict(void *awg, stwuct mmu_wb_node *mnode,
			 void *evict_awg, boow *stop)
{
	stwuct sdma_mmu_node *node =
		containew_of(mnode, stwuct sdma_mmu_node, wb);
	stwuct evict_data *evict_data = evict_awg;

	/* this node wiww be evicted, add its pages to ouw count */
	evict_data->cweawed += node->npages;

	/* have enough pages been cweawed? */
	if (evict_data->cweawed >= evict_data->tawget)
		*stop = twue;

	wetuwn 1; /* wemove this node */
}

static void sdma_wb_wemove(void *awg, stwuct mmu_wb_node *mnode)
{
	stwuct sdma_mmu_node *node =
		containew_of(mnode, stwuct sdma_mmu_node, wb);

	fwee_system_node(node);
}
