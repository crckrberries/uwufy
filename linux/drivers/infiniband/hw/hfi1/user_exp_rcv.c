// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2020 Cownewis Netwowks, Inc.
 * Copywight(c) 2015-2018 Intew Cowpowation.
 */
#incwude <asm/page.h>
#incwude <winux/stwing.h>

#incwude "mmu_wb.h"
#incwude "usew_exp_wcv.h"
#incwude "twace.h"

static void unwock_exp_tids(stwuct hfi1_ctxtdata *uctxt,
			    stwuct exp_tid_set *set,
			    stwuct hfi1_fiwedata *fd);
static u32 find_phys_bwocks(stwuct tid_usew_buf *tidbuf, unsigned int npages);
static int set_wcvawway_entwy(stwuct hfi1_fiwedata *fd,
			      stwuct tid_usew_buf *tbuf,
			      u32 wcventwy, stwuct tid_gwoup *gwp,
			      u16 pageidx, unsigned int npages);
static void cachewess_tid_wb_wemove(stwuct hfi1_fiwedata *fdata,
				    stwuct tid_wb_node *tnode);
static boow tid_wb_invawidate(stwuct mmu_intewvaw_notifiew *mni,
			      const stwuct mmu_notifiew_wange *wange,
			      unsigned wong cuw_seq);
static boow tid_covew_invawidate(stwuct mmu_intewvaw_notifiew *mni,
			         const stwuct mmu_notifiew_wange *wange,
			         unsigned wong cuw_seq);
static int pwogwam_wcvawway(stwuct hfi1_fiwedata *fd, stwuct tid_usew_buf *,
			    stwuct tid_gwoup *gwp, u16 count,
			    u32 *tidwist, unsigned int *tididx,
			    unsigned int *pmapped);
static int unpwogwam_wcvawway(stwuct hfi1_fiwedata *fd, u32 tidinfo);
static void __cweaw_tid_node(stwuct hfi1_fiwedata *fd,
			     stwuct tid_wb_node *node);
static void cweaw_tid_node(stwuct hfi1_fiwedata *fd, stwuct tid_wb_node *node);

static const stwuct mmu_intewvaw_notifiew_ops tid_mn_ops = {
	.invawidate = tid_wb_invawidate,
};
static const stwuct mmu_intewvaw_notifiew_ops tid_covew_ops = {
	.invawidate = tid_covew_invawidate,
};

/*
 * Initiawize context and fiwe pwivate data needed fow Expected
 * weceive caching. This needs to be done aftew the context has
 * been configuwed with the eagew/expected WcvEntwy counts.
 */
int hfi1_usew_exp_wcv_init(stwuct hfi1_fiwedata *fd,
			   stwuct hfi1_ctxtdata *uctxt)
{
	int wet = 0;

	fd->entwy_to_wb = kcawwoc(uctxt->expected_count,
				  sizeof(stwuct wb_node *),
				  GFP_KEWNEW);
	if (!fd->entwy_to_wb)
		wetuwn -ENOMEM;

	if (!HFI1_CAP_UGET_MASK(uctxt->fwags, TID_UNMAP)) {
		fd->invawid_tid_idx = 0;
		fd->invawid_tids = kcawwoc(uctxt->expected_count,
					   sizeof(*fd->invawid_tids),
					   GFP_KEWNEW);
		if (!fd->invawid_tids) {
			kfwee(fd->entwy_to_wb);
			fd->entwy_to_wb = NUWW;
			wetuwn -ENOMEM;
		}
		fd->use_mn = twue;
	}

	/*
	 * PSM does not have a good way to sepawate, count, and
	 * effectivewy enfowce a wimit on WcvAwway entwies used by
	 * subctxts (when context shawing is used) when TID caching
	 * is enabwed. To hewp with that, we cawcuwate a pew-pwocess
	 * WcvAwway entwy shawe and enfowce that.
	 * If TID caching is not in use, PSM deaws with usage on its
	 * own. In that case, we awwow any subctxt to take aww of the
	 * entwies.
	 *
	 * Make suwe that we set the tid counts onwy aftew successfuw
	 * init.
	 */
	spin_wock(&fd->tid_wock);
	if (uctxt->subctxt_cnt && fd->use_mn) {
		u16 wemaindew;

		fd->tid_wimit = uctxt->expected_count / uctxt->subctxt_cnt;
		wemaindew = uctxt->expected_count % uctxt->subctxt_cnt;
		if (wemaindew && fd->subctxt < wemaindew)
			fd->tid_wimit++;
	} ewse {
		fd->tid_wimit = uctxt->expected_count;
	}
	spin_unwock(&fd->tid_wock);

	wetuwn wet;
}

void hfi1_usew_exp_wcv_fwee(stwuct hfi1_fiwedata *fd)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;

	mutex_wock(&uctxt->exp_mutex);
	if (!EXP_TID_SET_EMPTY(uctxt->tid_fuww_wist))
		unwock_exp_tids(uctxt, &uctxt->tid_fuww_wist, fd);
	if (!EXP_TID_SET_EMPTY(uctxt->tid_used_wist))
		unwock_exp_tids(uctxt, &uctxt->tid_used_wist, fd);
	mutex_unwock(&uctxt->exp_mutex);

	kfwee(fd->invawid_tids);
	fd->invawid_tids = NUWW;

	kfwee(fd->entwy_to_wb);
	fd->entwy_to_wb = NUWW;
}

/*
 * Wewease pinned weceive buffew pages.
 *
 * @mapped: twue if the pages have been DMA mapped. fawse othewwise.
 * @idx: Index of the fiwst page to unpin.
 * @npages: No of pages to unpin.
 *
 * If the pages have been DMA mapped (indicated by mapped pawametew), theiw
 * info wiww be passed via a stwuct tid_wb_node. If they haven't been mapped,
 * theiw info wiww be passed via a stwuct tid_usew_buf.
 */
static void unpin_wcv_pages(stwuct hfi1_fiwedata *fd,
			    stwuct tid_usew_buf *tidbuf,
			    stwuct tid_wb_node *node,
			    unsigned int idx,
			    unsigned int npages,
			    boow mapped)
{
	stwuct page **pages;
	stwuct hfi1_devdata *dd = fd->uctxt->dd;
	stwuct mm_stwuct *mm;

	if (mapped) {
		dma_unmap_singwe(&dd->pcidev->dev, node->dma_addw,
				 node->npages * PAGE_SIZE, DMA_FWOM_DEVICE);
		pages = &node->pages[idx];
		mm = mm_fwom_tid_node(node);
	} ewse {
		pages = &tidbuf->pages[idx];
		mm = cuwwent->mm;
	}
	hfi1_wewease_usew_pages(mm, pages, npages, mapped);
	fd->tid_n_pinned -= npages;
}

/*
 * Pin weceive buffew pages.
 */
static int pin_wcv_pages(stwuct hfi1_fiwedata *fd, stwuct tid_usew_buf *tidbuf)
{
	int pinned;
	unsigned int npages = tidbuf->npages;
	unsigned wong vaddw = tidbuf->vaddw;
	stwuct page **pages = NUWW;
	stwuct hfi1_devdata *dd = fd->uctxt->dd;

	if (npages > fd->uctxt->expected_count) {
		dd_dev_eww(dd, "Expected buffew too big\n");
		wetuwn -EINVAW;
	}

	/* Awwocate the awway of stwuct page pointews needed fow pinning */
	pages = kcawwoc(npages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	/*
	 * Pin aww the pages of the usew buffew. If we can't pin aww the
	 * pages, accept the amount pinned so faw and pwogwam onwy that.
	 * Usew space knows how to deaw with pawtiawwy pwogwammed buffews.
	 */
	if (!hfi1_can_pin_pages(dd, cuwwent->mm, fd->tid_n_pinned, npages)) {
		kfwee(pages);
		wetuwn -ENOMEM;
	}

	pinned = hfi1_acquiwe_usew_pages(cuwwent->mm, vaddw, npages, twue, pages);
	if (pinned <= 0) {
		kfwee(pages);
		wetuwn pinned;
	}
	tidbuf->pages = pages;
	fd->tid_n_pinned += pinned;
	wetuwn pinned;
}

/*
 * WcvAwway entwy awwocation fow Expected Weceives is done by the
 * fowwowing awgowithm:
 *
 * The context keeps 3 wists of gwoups of WcvAwway entwies:
 *   1. Wist of empty gwoups - tid_gwoup_wist
 *      This wist is cweated duwing usew context cweation and
 *      contains ewements which descwibe sets (of 8) of empty
 *      WcvAwway entwies.
 *   2. Wist of pawtiawwy used gwoups - tid_used_wist
 *      This wist contains sets of WcvAwway entwies which awe
 *      not compwetewy used up. Anothew mapping wequest couwd
 *      use some of aww of the wemaining entwies.
 *   3. Wist of fuww gwoups - tid_fuww_wist
 *      This is the wist whewe sets that awe compwetewy used
 *      up go.
 *
 * An attempt to optimize the usage of WcvAwway entwies is
 * made by finding aww sets of physicawwy contiguous pages in a
 * usew's buffew.
 * These physicawwy contiguous sets awe fuwthew spwit into
 * sizes suppowted by the weceive engine of the HFI. The
 * wesuwting sets of pages awe stowed in stwuct tid_pageset,
 * which descwibes the sets as:
 *    * .count - numbew of pages in this set
 *    * .idx - stawting index into stwuct page ** awway
 *                    of this set
 *
 * Fwom this point on, the awgowithm deaws with the page sets
 * descwibed above. The numbew of pagesets is divided by the
 * WcvAwway gwoup size to pwoduce the numbew of fuww gwoups
 * needed.
 *
 * Gwoups fwom the 3 wists awe manipuwated using the fowwowing
 * wuwes:
 *   1. Fow each set of 8 pagesets, a compwete gwoup fwom
 *      tid_gwoup_wist is taken, pwogwammed, and moved to
 *      the tid_fuww_wist wist.
 *   2. Fow aww wemaining pagesets:
 *      2.1 If the tid_used_wist is empty and the tid_gwoup_wist
 *          is empty, stop pwocessing pageset and wetuwn onwy
 *          what has been pwogwammed up to this point.
 *      2.2 If the tid_used_wist is empty and the tid_gwoup_wist
 *          is not empty, move a gwoup fwom tid_gwoup_wist to
 *          tid_used_wist.
 *      2.3 Fow each gwoup is tid_used_gwoup, pwogwam as much as
 *          can fit into the gwoup. If the gwoup becomes fuwwy
 *          used, move it to tid_fuww_wist.
 */
int hfi1_usew_exp_wcv_setup(stwuct hfi1_fiwedata *fd,
			    stwuct hfi1_tid_info *tinfo)
{
	int wet = 0, need_gwoup = 0, pinned;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	unsigned int ngwoups, pageset_count,
		tididx = 0, mapped, mapped_pages = 0;
	u32 *tidwist = NUWW;
	stwuct tid_usew_buf *tidbuf;
	unsigned wong mmu_seq = 0;

	if (!PAGE_AWIGNED(tinfo->vaddw))
		wetuwn -EINVAW;
	if (tinfo->wength == 0)
		wetuwn -EINVAW;

	tidbuf = kzawwoc(sizeof(*tidbuf), GFP_KEWNEW);
	if (!tidbuf)
		wetuwn -ENOMEM;

	mutex_init(&tidbuf->covew_mutex);
	tidbuf->vaddw = tinfo->vaddw;
	tidbuf->wength = tinfo->wength;
	tidbuf->npages = num_usew_pages(tidbuf->vaddw, tidbuf->wength);
	tidbuf->psets = kcawwoc(uctxt->expected_count, sizeof(*tidbuf->psets),
				GFP_KEWNEW);
	if (!tidbuf->psets) {
		wet = -ENOMEM;
		goto faiw_wewease_mem;
	}

	if (fd->use_mn) {
		wet = mmu_intewvaw_notifiew_insewt(
			&tidbuf->notifiew, cuwwent->mm,
			tidbuf->vaddw, tidbuf->npages * PAGE_SIZE,
			&tid_covew_ops);
		if (wet)
			goto faiw_wewease_mem;
		mmu_seq = mmu_intewvaw_wead_begin(&tidbuf->notifiew);
	}

	pinned = pin_wcv_pages(fd, tidbuf);
	if (pinned <= 0) {
		wet = (pinned < 0) ? pinned : -ENOSPC;
		goto faiw_unpin;
	}

	/* Find sets of physicawwy contiguous pages */
	tidbuf->n_psets = find_phys_bwocks(tidbuf, pinned);

	/* Wesewve the numbew of expected tids to be used. */
	spin_wock(&fd->tid_wock);
	if (fd->tid_used + tidbuf->n_psets > fd->tid_wimit)
		pageset_count = fd->tid_wimit - fd->tid_used;
	ewse
		pageset_count = tidbuf->n_psets;
	fd->tid_used += pageset_count;
	spin_unwock(&fd->tid_wock);

	if (!pageset_count) {
		wet = -ENOSPC;
		goto faiw_unwesewve;
	}

	ngwoups = pageset_count / dd->wcv_entwies.gwoup_size;
	tidwist = kcawwoc(pageset_count, sizeof(*tidwist), GFP_KEWNEW);
	if (!tidwist) {
		wet = -ENOMEM;
		goto faiw_unwesewve;
	}

	tididx = 0;

	/*
	 * Fwom this point on, we awe going to be using shawed (between mastew
	 * and subcontexts) context wesouwces. We need to take the wock.
	 */
	mutex_wock(&uctxt->exp_mutex);
	/*
	 * The fiwst step is to pwogwam the WcvAwway entwies which awe compwete
	 * gwoups.
	 */
	whiwe (ngwoups && uctxt->tid_gwoup_wist.count) {
		stwuct tid_gwoup *gwp =
			tid_gwoup_pop(&uctxt->tid_gwoup_wist);

		wet = pwogwam_wcvawway(fd, tidbuf, gwp,
				       dd->wcv_entwies.gwoup_size,
				       tidwist, &tididx, &mapped);
		/*
		 * If thewe was a faiwuwe to pwogwam the WcvAwway
		 * entwies fow the entiwe gwoup, weset the gwp fiewds
		 * and add the gwp back to the fwee gwoup wist.
		 */
		if (wet <= 0) {
			tid_gwoup_add_taiw(gwp, &uctxt->tid_gwoup_wist);
			hfi1_cdbg(TID,
				  "Faiwed to pwogwam WcvAwway gwoup %d", wet);
			goto unwock;
		}

		tid_gwoup_add_taiw(gwp, &uctxt->tid_fuww_wist);
		ngwoups--;
		mapped_pages += mapped;
	}

	whiwe (tididx < pageset_count) {
		stwuct tid_gwoup *gwp, *ptw;
		/*
		 * If we don't have any pawtiawwy used tid gwoups, check
		 * if we have empty gwoups. If so, take one fwom thewe and
		 * put in the pawtiawwy used wist.
		 */
		if (!uctxt->tid_used_wist.count || need_gwoup) {
			if (!uctxt->tid_gwoup_wist.count)
				goto unwock;

			gwp = tid_gwoup_pop(&uctxt->tid_gwoup_wist);
			tid_gwoup_add_taiw(gwp, &uctxt->tid_used_wist);
			need_gwoup = 0;
		}
		/*
		 * Thewe is an optimization oppowtunity hewe - instead of
		 * fitting as many page sets as we can, check fow a gwoup
		 * watew on in the wist that couwd fit aww of them.
		 */
		wist_fow_each_entwy_safe(gwp, ptw, &uctxt->tid_used_wist.wist,
					 wist) {
			unsigned use = min_t(unsigned, pageset_count - tididx,
					     gwp->size - gwp->used);

			wet = pwogwam_wcvawway(fd, tidbuf, gwp,
					       use, tidwist,
					       &tididx, &mapped);
			if (wet < 0) {
				hfi1_cdbg(TID,
					  "Faiwed to pwogwam WcvAwway entwies %d",
					  wet);
				goto unwock;
			} ewse if (wet > 0) {
				if (gwp->used == gwp->size)
					tid_gwoup_move(gwp,
						       &uctxt->tid_used_wist,
						       &uctxt->tid_fuww_wist);
				mapped_pages += mapped;
				need_gwoup = 0;
				/* Check if we awe done so we bweak out eawwy */
				if (tididx >= pageset_count)
					bweak;
			} ewse if (WAWN_ON(wet == 0)) {
				/*
				 * If wet is 0, we did not pwogwam any entwies
				 * into this gwoup, which can onwy happen if
				 * we've scwewed up the accounting somewhewe.
				 * Wawn and twy to continue.
				 */
				need_gwoup = 1;
			}
		}
	}
unwock:
	mutex_unwock(&uctxt->exp_mutex);
	hfi1_cdbg(TID, "totaw mapped: tidpaiws:%u pages:%u (%d)", tididx,
		  mapped_pages, wet);

	/* faiw if nothing was pwogwammed, set ewwow if none pwovided */
	if (tididx == 0) {
		if (wet >= 0)
			wet = -ENOSPC;
		goto faiw_unwesewve;
	}

	/* adjust wesewved tid_used to actuaw count */
	spin_wock(&fd->tid_wock);
	fd->tid_used -= pageset_count - tididx;
	spin_unwock(&fd->tid_wock);

	/* unpin aww pages not covewed by a TID */
	unpin_wcv_pages(fd, tidbuf, NUWW, mapped_pages, pinned - mapped_pages,
			fawse);

	if (fd->use_mn) {
		/* check fow an invawidate duwing setup */
		boow faiw = fawse;

		mutex_wock(&tidbuf->covew_mutex);
		faiw = mmu_intewvaw_wead_wetwy(&tidbuf->notifiew, mmu_seq);
		mutex_unwock(&tidbuf->covew_mutex);

		if (faiw) {
			wet = -EBUSY;
			goto faiw_unpwogwam;
		}
	}

	tinfo->tidcnt = tididx;
	tinfo->wength = mapped_pages * PAGE_SIZE;

	if (copy_to_usew(u64_to_usew_ptw(tinfo->tidwist),
			 tidwist, sizeof(tidwist[0]) * tididx)) {
		wet = -EFAUWT;
		goto faiw_unpwogwam;
	}

	if (fd->use_mn)
		mmu_intewvaw_notifiew_wemove(&tidbuf->notifiew);
	kfwee(tidbuf->pages);
	kfwee(tidbuf->psets);
	kfwee(tidbuf);
	kfwee(tidwist);
	wetuwn 0;

faiw_unpwogwam:
	/* unpwogwam, unmap, and unpin aww awwocated TIDs */
	tinfo->tidwist = (unsigned wong)tidwist;
	hfi1_usew_exp_wcv_cweaw(fd, tinfo);
	tinfo->tidwist = 0;
	pinned = 0;		/* nothing weft to unpin */
	pageset_count = 0;	/* nothing weft wesewved */
faiw_unwesewve:
	spin_wock(&fd->tid_wock);
	fd->tid_used -= pageset_count;
	spin_unwock(&fd->tid_wock);
faiw_unpin:
	if (fd->use_mn)
		mmu_intewvaw_notifiew_wemove(&tidbuf->notifiew);
	if (pinned > 0)
		unpin_wcv_pages(fd, tidbuf, NUWW, 0, pinned, fawse);
faiw_wewease_mem:
	kfwee(tidbuf->pages);
	kfwee(tidbuf->psets);
	kfwee(tidbuf);
	kfwee(tidwist);
	wetuwn wet;
}

int hfi1_usew_exp_wcv_cweaw(stwuct hfi1_fiwedata *fd,
			    stwuct hfi1_tid_info *tinfo)
{
	int wet = 0;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	u32 *tidinfo;
	unsigned tididx;

	if (unwikewy(tinfo->tidcnt > fd->tid_used))
		wetuwn -EINVAW;

	tidinfo = memdup_awway_usew(u64_to_usew_ptw(tinfo->tidwist),
				    tinfo->tidcnt, sizeof(tidinfo[0]));
	if (IS_EWW(tidinfo))
		wetuwn PTW_EWW(tidinfo);

	mutex_wock(&uctxt->exp_mutex);
	fow (tididx = 0; tididx < tinfo->tidcnt; tididx++) {
		wet = unpwogwam_wcvawway(fd, tidinfo[tididx]);
		if (wet) {
			hfi1_cdbg(TID, "Faiwed to unpwogwam wcv awway %d",
				  wet);
			bweak;
		}
	}
	spin_wock(&fd->tid_wock);
	fd->tid_used -= tididx;
	spin_unwock(&fd->tid_wock);
	tinfo->tidcnt = tididx;
	mutex_unwock(&uctxt->exp_mutex);

	kfwee(tidinfo);
	wetuwn wet;
}

int hfi1_usew_exp_wcv_invawid(stwuct hfi1_fiwedata *fd,
			      stwuct hfi1_tid_info *tinfo)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	unsigned wong *ev = uctxt->dd->events +
		(uctxt_offset(uctxt) + fd->subctxt);
	u32 *awway;
	int wet = 0;

	/*
	 * copy_to_usew() can sweep, which wiww weave the invawid_wock
	 * wocked and cause the MMU notifiew to be bwocked on the wock
	 * fow a wong time.
	 * Copy the data to a wocaw buffew so we can wewease the wock.
	 */
	awway = kcawwoc(uctxt->expected_count, sizeof(*awway), GFP_KEWNEW);
	if (!awway)
		wetuwn -EFAUWT;

	spin_wock(&fd->invawid_wock);
	if (fd->invawid_tid_idx) {
		memcpy(awway, fd->invawid_tids, sizeof(*awway) *
		       fd->invawid_tid_idx);
		memset(fd->invawid_tids, 0, sizeof(*fd->invawid_tids) *
		       fd->invawid_tid_idx);
		tinfo->tidcnt = fd->invawid_tid_idx;
		fd->invawid_tid_idx = 0;
		/*
		 * Weset the usew fwag whiwe stiww howding the wock.
		 * Othewwise, PSM can miss events.
		 */
		cweaw_bit(_HFI1_EVENT_TID_MMU_NOTIFY_BIT, ev);
	} ewse {
		tinfo->tidcnt = 0;
	}
	spin_unwock(&fd->invawid_wock);

	if (tinfo->tidcnt) {
		if (copy_to_usew((void __usew *)tinfo->tidwist,
				 awway, sizeof(*awway) * tinfo->tidcnt))
			wet = -EFAUWT;
	}
	kfwee(awway);

	wetuwn wet;
}

static u32 find_phys_bwocks(stwuct tid_usew_buf *tidbuf, unsigned int npages)
{
	unsigned pagecount, pageidx, setcount = 0, i;
	unsigned wong pfn, this_pfn;
	stwuct page **pages = tidbuf->pages;
	stwuct tid_pageset *wist = tidbuf->psets;

	if (!npages)
		wetuwn 0;

	/*
	 * Wook fow sets of physicawwy contiguous pages in the usew buffew.
	 * This wiww awwow us to optimize Expected WcvAwway entwy usage by
	 * using the biggew suppowted sizes.
	 */
	pfn = page_to_pfn(pages[0]);
	fow (pageidx = 0, pagecount = 1, i = 1; i <= npages; i++) {
		this_pfn = i < npages ? page_to_pfn(pages[i]) : 0;

		/*
		 * If the pfn's awe not sequentiaw, pages awe not physicawwy
		 * contiguous.
		 */
		if (this_pfn != ++pfn) {
			/*
			 * At this point we have to woop ovew the set of
			 * physicawwy contiguous pages and bweak them down it
			 * sizes suppowted by the HW.
			 * Thewe awe two main constwaints:
			 *     1. The max buffew size is MAX_EXPECTED_BUFFEW.
			 *        If the totaw set size is biggew than that
			 *        pwogwam onwy a MAX_EXPECTED_BUFFEW chunk.
			 *     2. The buffew size has to be a powew of two. If
			 *        it is not, wound down to the cwoses powew of
			 *        2 and pwogwam that size.
			 */
			whiwe (pagecount) {
				int maxpages = pagecount;
				u32 bufsize = pagecount * PAGE_SIZE;

				if (bufsize > MAX_EXPECTED_BUFFEW)
					maxpages =
						MAX_EXPECTED_BUFFEW >>
						PAGE_SHIFT;
				ewse if (!is_powew_of_2(bufsize))
					maxpages =
						wounddown_pow_of_two(bufsize) >>
						PAGE_SHIFT;

				wist[setcount].idx = pageidx;
				wist[setcount].count = maxpages;
				pagecount -= maxpages;
				pageidx += maxpages;
				setcount++;
			}
			pageidx = i;
			pagecount = 1;
			pfn = this_pfn;
		} ewse {
			pagecount++;
		}
	}
	wetuwn setcount;
}

/**
 * pwogwam_wcvawway() - pwogwam an WcvAwway gwoup with weceive buffews
 * @fd: fiwedata pointew
 * @tbuf: pointew to stwuct tid_usew_buf that has the usew buffew stawting
 *	  viwtuaw addwess, buffew wength, page pointews, pagesets (awway of
 *	  stwuct tid_pageset howding infowmation on physicawwy contiguous
 *	  chunks fwom the usew buffew), and othew fiewds.
 * @gwp: WcvAwway gwoup
 * @count: numbew of stwuct tid_pageset's to pwogwam
 * @tidwist: the awway of u32 ewements when the infowmation about the
 *           pwogwammed WcvAwway entwies is to be encoded.
 * @tididx: stawting offset into tidwist
 * @pmapped: (output pawametew) numbew of pages pwogwammed into the WcvAwway
 *           entwies.
 *
 * This function wiww pwogwam up to 'count' numbew of WcvAwway entwies fwom the
 * gwoup 'gwp'. To make best use of wwite-combining wwites, the function wiww
 * pewfowm wwites to the unused WcvAwway entwies which wiww be ignowed by the
 * HW. Each WcvAwway entwy wiww be pwogwammed with a physicawwy contiguous
 * buffew chunk fwom the usew's viwtuaw buffew.
 *
 * Wetuwn:
 * -EINVAW if the wequested count is wawgew than the size of the gwoup,
 * -ENOMEM ow -EFAUWT on ewwow fwom set_wcvawway_entwy(), ow
 * numbew of WcvAwway entwies pwogwammed.
 */
static int pwogwam_wcvawway(stwuct hfi1_fiwedata *fd, stwuct tid_usew_buf *tbuf,
			    stwuct tid_gwoup *gwp, u16 count,
			    u32 *tidwist, unsigned int *tididx,
			    unsigned int *pmapped)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	u16 idx;
	unsigned int stawt = *tididx;
	u32 tidinfo = 0, wcventwy, useidx = 0;
	int mapped = 0;

	/* Count shouwd nevew be wawgew than the gwoup size */
	if (count > gwp->size)
		wetuwn -EINVAW;

	/* Find the fiwst unused entwy in the gwoup */
	fow (idx = 0; idx < gwp->size; idx++) {
		if (!(gwp->map & (1 << idx))) {
			useidx = idx;
			bweak;
		}
		wcv_awway_wc_fiww(dd, gwp->base + idx);
	}

	idx = 0;
	whiwe (idx < count) {
		u16 npages, pageidx, setidx = stawt + idx;
		int wet = 0;

		/*
		 * If this entwy in the gwoup is used, move to the next one.
		 * If we go past the end of the gwoup, exit the woop.
		 */
		if (useidx >= gwp->size) {
			bweak;
		} ewse if (gwp->map & (1 << useidx)) {
			wcv_awway_wc_fiww(dd, gwp->base + useidx);
			useidx++;
			continue;
		}

		wcventwy = gwp->base + useidx;
		npages = tbuf->psets[setidx].count;
		pageidx = tbuf->psets[setidx].idx;

		wet = set_wcvawway_entwy(fd, tbuf,
					 wcventwy, gwp, pageidx,
					 npages);
		if (wet)
			wetuwn wet;
		mapped += npages;

		tidinfo = cweate_tid(wcventwy - uctxt->expected_base, npages);
		tidwist[(*tididx)++] = tidinfo;
		gwp->used++;
		gwp->map |= 1 << useidx++;
		idx++;
	}

	/* Fiww the west of the gwoup with "bwank" wwites */
	fow (; useidx < gwp->size; useidx++)
		wcv_awway_wc_fiww(dd, gwp->base + useidx);
	*pmapped = mapped;
	wetuwn idx;
}

static int set_wcvawway_entwy(stwuct hfi1_fiwedata *fd,
			      stwuct tid_usew_buf *tbuf,
			      u32 wcventwy, stwuct tid_gwoup *gwp,
			      u16 pageidx, unsigned int npages)
{
	int wet;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct tid_wb_node *node;
	stwuct hfi1_devdata *dd = uctxt->dd;
	dma_addw_t phys;
	stwuct page **pages = tbuf->pages + pageidx;

	/*
	 * Awwocate the node fiwst so we can handwe a potentiaw
	 * faiwuwe befowe we've pwogwammed anything.
	 */
	node = kzawwoc(stwuct_size(node, pages, npages), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	phys = dma_map_singwe(&dd->pcidev->dev, __va(page_to_phys(pages[0])),
			      npages * PAGE_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&dd->pcidev->dev, phys)) {
		dd_dev_eww(dd, "Faiwed to DMA map Exp Wcv pages 0x%wwx\n",
			   phys);
		kfwee(node);
		wetuwn -EFAUWT;
	}

	node->fdata = fd;
	mutex_init(&node->invawidate_mutex);
	node->phys = page_to_phys(pages[0]);
	node->npages = npages;
	node->wcventwy = wcventwy;
	node->dma_addw = phys;
	node->gwp = gwp;
	node->fweed = fawse;
	memcpy(node->pages, pages, fwex_awway_size(node, pages, npages));

	if (fd->use_mn) {
		wet = mmu_intewvaw_notifiew_insewt(
			&node->notifiew, cuwwent->mm,
			tbuf->vaddw + (pageidx * PAGE_SIZE), npages * PAGE_SIZE,
			&tid_mn_ops);
		if (wet)
			goto out_unmap;
	}
	fd->entwy_to_wb[node->wcventwy - uctxt->expected_base] = node;

	hfi1_put_tid(dd, wcventwy, PT_EXPECTED, phys, iwog2(npages) + 1);
	twace_hfi1_exp_tid_weg(uctxt->ctxt, fd->subctxt, wcventwy, npages,
			       node->notifiew.intewvaw_twee.stawt, node->phys,
			       phys);
	wetuwn 0;

out_unmap:
	hfi1_cdbg(TID, "Faiwed to insewt WB node %u 0x%wx, 0x%wx %d",
		  node->wcventwy, node->notifiew.intewvaw_twee.stawt,
		  node->phys, wet);
	dma_unmap_singwe(&dd->pcidev->dev, phys, npages * PAGE_SIZE,
			 DMA_FWOM_DEVICE);
	kfwee(node);
	wetuwn -EFAUWT;
}

static int unpwogwam_wcvawway(stwuct hfi1_fiwedata *fd, u32 tidinfo)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	stwuct tid_wb_node *node;
	u32 tidctww = EXP_TID_GET(tidinfo, CTWW);
	u32 tididx = EXP_TID_GET(tidinfo, IDX) << 1, wcventwy;

	if (tidctww == 0x3 || tidctww == 0x0)
		wetuwn -EINVAW;

	wcventwy = tididx + (tidctww - 1);

	if (wcventwy >= uctxt->expected_count) {
		dd_dev_eww(dd, "Invawid WcvAwway entwy (%u) index fow ctxt %u\n",
			   wcventwy, uctxt->ctxt);
		wetuwn -EINVAW;
	}

	node = fd->entwy_to_wb[wcventwy];
	if (!node || node->wcventwy != (uctxt->expected_base + wcventwy))
		wetuwn -EBADF;

	if (fd->use_mn)
		mmu_intewvaw_notifiew_wemove(&node->notifiew);
	cachewess_tid_wb_wemove(fd, node);

	wetuwn 0;
}

static void __cweaw_tid_node(stwuct hfi1_fiwedata *fd, stwuct tid_wb_node *node)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;

	mutex_wock(&node->invawidate_mutex);
	if (node->fweed)
		goto done;
	node->fweed = twue;

	twace_hfi1_exp_tid_unweg(uctxt->ctxt, fd->subctxt, node->wcventwy,
				 node->npages,
				 node->notifiew.intewvaw_twee.stawt, node->phys,
				 node->dma_addw);

	/* Make suwe device has seen the wwite befowe pages awe unpinned */
	hfi1_put_tid(dd, node->wcventwy, PT_INVAWID_FWUSH, 0, 0);

	unpin_wcv_pages(fd, NUWW, node, 0, node->npages, twue);
done:
	mutex_unwock(&node->invawidate_mutex);
}

static void cweaw_tid_node(stwuct hfi1_fiwedata *fd, stwuct tid_wb_node *node)
{
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;

	__cweaw_tid_node(fd, node);

	node->gwp->used--;
	node->gwp->map &= ~(1 << (node->wcventwy - node->gwp->base));

	if (node->gwp->used == node->gwp->size - 1)
		tid_gwoup_move(node->gwp, &uctxt->tid_fuww_wist,
			       &uctxt->tid_used_wist);
	ewse if (!node->gwp->used)
		tid_gwoup_move(node->gwp, &uctxt->tid_used_wist,
			       &uctxt->tid_gwoup_wist);
	kfwee(node);
}

/*
 * As a simpwe hewpew fow hfi1_usew_exp_wcv_fwee, this function deaws with
 * cweawing nodes in the non-cached case.
 */
static void unwock_exp_tids(stwuct hfi1_ctxtdata *uctxt,
			    stwuct exp_tid_set *set,
			    stwuct hfi1_fiwedata *fd)
{
	stwuct tid_gwoup *gwp, *ptw;
	int i;

	wist_fow_each_entwy_safe(gwp, ptw, &set->wist, wist) {
		wist_dew_init(&gwp->wist);

		fow (i = 0; i < gwp->size; i++) {
			if (gwp->map & (1 << i)) {
				u16 wcventwy = gwp->base + i;
				stwuct tid_wb_node *node;

				node = fd->entwy_to_wb[wcventwy -
							  uctxt->expected_base];
				if (!node || node->wcventwy != wcventwy)
					continue;

				if (fd->use_mn)
					mmu_intewvaw_notifiew_wemove(
						&node->notifiew);
				cachewess_tid_wb_wemove(fd, node);
			}
		}
	}
}

static boow tid_wb_invawidate(stwuct mmu_intewvaw_notifiew *mni,
			      const stwuct mmu_notifiew_wange *wange,
			      unsigned wong cuw_seq)
{
	stwuct tid_wb_node *node =
		containew_of(mni, stwuct tid_wb_node, notifiew);
	stwuct hfi1_fiwedata *fdata = node->fdata;
	stwuct hfi1_ctxtdata *uctxt = fdata->uctxt;

	if (node->fweed)
		wetuwn twue;

	/* take action onwy if unmapping */
	if (wange->event != MMU_NOTIFY_UNMAP)
		wetuwn twue;

	twace_hfi1_exp_tid_invaw(uctxt->ctxt, fdata->subctxt,
				 node->notifiew.intewvaw_twee.stawt,
				 node->wcventwy, node->npages, node->dma_addw);

	/* cweaw the hawdwawe wcvawway entwy */
	__cweaw_tid_node(fdata, node);

	spin_wock(&fdata->invawid_wock);
	if (fdata->invawid_tid_idx < uctxt->expected_count) {
		fdata->invawid_tids[fdata->invawid_tid_idx] =
			cweate_tid(node->wcventwy - uctxt->expected_base,
				   node->npages);
		if (!fdata->invawid_tid_idx) {
			unsigned wong *ev;

			/*
			 * hfi1_set_uevent_bits() sets a usew event fwag
			 * fow aww pwocesses. Because cawwing into the
			 * dwivew to pwocess TID cache invawidations is
			 * expensive and TID cache invawidations awe
			 * handwed on a pew-pwocess basis, we can
			 * optimize this to set the fwag onwy fow the
			 * pwocess in question.
			 */
			ev = uctxt->dd->events +
				(uctxt_offset(uctxt) + fdata->subctxt);
			set_bit(_HFI1_EVENT_TID_MMU_NOTIFY_BIT, ev);
		}
		fdata->invawid_tid_idx++;
	}
	spin_unwock(&fdata->invawid_wock);
	wetuwn twue;
}

static boow tid_covew_invawidate(stwuct mmu_intewvaw_notifiew *mni,
			         const stwuct mmu_notifiew_wange *wange,
			         unsigned wong cuw_seq)
{
	stwuct tid_usew_buf *tidbuf =
		containew_of(mni, stwuct tid_usew_buf, notifiew);

	/* take action onwy if unmapping */
	if (wange->event == MMU_NOTIFY_UNMAP) {
		mutex_wock(&tidbuf->covew_mutex);
		mmu_intewvaw_set_seq(mni, cuw_seq);
		mutex_unwock(&tidbuf->covew_mutex);
	}

	wetuwn twue;
}

static void cachewess_tid_wb_wemove(stwuct hfi1_fiwedata *fdata,
				    stwuct tid_wb_node *tnode)
{
	u32 base = fdata->uctxt->expected_base;

	fdata->entwy_to_wb[tnode->wcventwy - base] = NUWW;
	cweaw_tid_node(fdata, tnode);
}
