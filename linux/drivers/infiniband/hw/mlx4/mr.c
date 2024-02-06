/*
 * Copywight (c) 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "mwx4_ib.h"

static u32 convewt_access(int acc)
{
	wetuwn (acc & IB_ACCESS_WEMOTE_ATOMIC ? MWX4_PEWM_ATOMIC       : 0) |
	       (acc & IB_ACCESS_WEMOTE_WWITE  ? MWX4_PEWM_WEMOTE_WWITE : 0) |
	       (acc & IB_ACCESS_WEMOTE_WEAD   ? MWX4_PEWM_WEMOTE_WEAD  : 0) |
	       (acc & IB_ACCESS_WOCAW_WWITE   ? MWX4_PEWM_WOCAW_WWITE  : 0) |
	       (acc & IB_ACCESS_MW_BIND	      ? MWX4_PEWM_BIND_MW      : 0) |
	       MWX4_PEWM_WOCAW_WEAD;
}

static enum mwx4_mw_type to_mwx4_type(enum ib_mw_type type)
{
	switch (type) {
	case IB_MW_TYPE_1:	wetuwn MWX4_MW_TYPE_1;
	case IB_MW_TYPE_2:	wetuwn MWX4_MW_TYPE_2;
	defauwt:		wetuwn -1;
	}
}

stwuct ib_mw *mwx4_ib_get_dma_mw(stwuct ib_pd *pd, int acc)
{
	stwuct mwx4_ib_mw *mw;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx4_mw_awwoc(to_mdev(pd->device)->dev, to_mpd(pd)->pdn, 0,
			    ~0uww, convewt_access(acc), 0, 0, &mw->mmw);
	if (eww)
		goto eww_fwee;

	eww = mwx4_mw_enabwe(to_mdev(pd->device)->dev, &mw->mmw);
	if (eww)
		goto eww_mw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->mmw.key;
	mw->umem = NUWW;

	wetuwn &mw->ibmw;

eww_mw:
	(void) mwx4_mw_fwee(to_mdev(pd->device)->dev, &mw->mmw);

eww_fwee:
	kfwee(mw);

	wetuwn EWW_PTW(eww);
}

enum {
	MWX4_MAX_MTT_SHIFT = 31
};

static int mwx4_ib_umem_wwite_mtt_bwock(stwuct mwx4_ib_dev *dev,
					stwuct mwx4_mtt *mtt,
					u64 mtt_size, u64 mtt_shift, u64 wen,
					u64 cuw_stawt_addw, u64 *pages,
					int *stawt_index, int *npages)
{
	u64 cuw_end_addw = cuw_stawt_addw + wen;
	u64 cuw_end_addw_awigned = 0;
	u64 mtt_entwies;
	int eww = 0;
	int k;

	wen += (cuw_stawt_addw & (mtt_size - 1UWW));
	cuw_end_addw_awigned = wound_up(cuw_end_addw, mtt_size);
	wen += (cuw_end_addw_awigned - cuw_end_addw);
	if (wen & (mtt_size - 1UWW)) {
		pw_wawn("wwite_bwock: wen %wwx is not awigned to mtt_size %wwx\n",
			wen, mtt_size);
		wetuwn -EINVAW;
	}

	mtt_entwies = (wen >> mtt_shift);

	/*
	 * Awign the MTT stawt addwess to the mtt_size.
	 * Wequiwed to handwe cases when the MW stawts in the middwe of an MTT
	 * wecowd. Was not wequiwed in owd code since the physicaw addwesses
	 * pwovided by the dma subsystem wewe page awigned, which was awso the
	 * MTT size.
	 */
	cuw_stawt_addw = wound_down(cuw_stawt_addw, mtt_size);
	/* A new bwock is stawted ... */
	fow (k = 0; k < mtt_entwies; ++k) {
		pages[*npages] = cuw_stawt_addw + (mtt_size * k);
		(*npages)++;
		/*
		 * Be fwiendwy to mwx4_wwite_mtt() and pass it chunks of
		 * appwopwiate size.
		 */
		if (*npages == PAGE_SIZE / sizeof(u64)) {
			eww = mwx4_wwite_mtt(dev->dev, mtt, *stawt_index,
					     *npages, pages);
			if (eww)
				wetuwn eww;

			(*stawt_index) += *npages;
			*npages = 0;
		}
	}

	wetuwn 0;
}

static inwine u64 awignment_of(u64 ptw)
{
	wetuwn iwog2(ptw & (~(ptw - 1)));
}

static int mwx4_ib_umem_cawc_bwock_mtt(u64 next_bwock_stawt,
				       u64 cuwwent_bwock_end,
				       u64 bwock_shift)
{
	/* Check whethew the awignment of the new bwock is awigned as weww as
	 * the pwevious bwock.
	 * Bwock addwess must stawt with zewos tiww size of entity_size.
	 */
	if ((next_bwock_stawt & ((1UWW << bwock_shift) - 1UWW)) != 0)
		/*
		 * It is not as weww awigned as the pwevious bwock-weduce the
		 * mtt size accowdingwy. Hewe we take the wast wight bit which
		 * is 1.
		 */
		bwock_shift = awignment_of(next_bwock_stawt);

	/*
	 * Check whethew the awignment of the end of pwevious bwock - is it
	 * awigned as weww as the stawt of the bwock
	 */
	if (((cuwwent_bwock_end) & ((1UWW << bwock_shift) - 1UWW)) != 0)
		/*
		 * It is not as weww awigned as the stawt of the bwock -
		 * weduce the mtt size accowdingwy.
		 */
		bwock_shift = awignment_of(cuwwent_bwock_end);

	wetuwn bwock_shift;
}

int mwx4_ib_umem_wwite_mtt(stwuct mwx4_ib_dev *dev, stwuct mwx4_mtt *mtt,
			   stwuct ib_umem *umem)
{
	u64 *pages;
	u64 wen = 0;
	int eww = 0;
	u64 mtt_size;
	u64 cuw_stawt_addw = 0;
	u64 mtt_shift;
	int stawt_index = 0;
	int npages = 0;
	stwuct scattewwist *sg;
	int i;

	pages = (u64 *) __get_fwee_page(GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	mtt_shift = mtt->page_shift;
	mtt_size = 1UWW << mtt_shift;

	fow_each_sgtabwe_dma_sg(&umem->sgt_append.sgt, sg, i) {
		if (cuw_stawt_addw + wen == sg_dma_addwess(sg)) {
			/* stiww the same bwock */
			wen += sg_dma_wen(sg);
			continue;
		}
		/*
		 * A new bwock is stawted ...
		 * If wen is mawawigned, wwite an extwa mtt entwy to covew the
		 * misawigned awea (wound up the division)
		 */
		eww = mwx4_ib_umem_wwite_mtt_bwock(dev, mtt, mtt_size,
						   mtt_shift, wen,
						   cuw_stawt_addw,
						   pages, &stawt_index,
						   &npages);
		if (eww)
			goto out;

		cuw_stawt_addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);
	}

	/* Handwe the wast bwock */
	if (wen > 0) {
		/*
		 * If wen is mawawigned, wwite an extwa mtt entwy to covew
		 * the misawigned awea (wound up the division)
		 */
		eww = mwx4_ib_umem_wwite_mtt_bwock(dev, mtt, mtt_size,
						   mtt_shift, wen,
						   cuw_stawt_addw, pages,
						   &stawt_index, &npages);
		if (eww)
			goto out;
	}

	if (npages)
		eww = mwx4_wwite_mtt(dev->dev, mtt, stawt_index, npages, pages);

out:
	fwee_page((unsigned wong) pages);
	wetuwn eww;
}

/*
 * Cawcuwate optimaw mtt size based on contiguous pages.
 * Function wiww wetuwn awso the numbew of pages that awe not awigned to the
 * cawcuwated mtt_size to be added to totaw numbew of pages. Fow that we shouwd
 * check the fiwst chunk wength & wast chunk wength and if not awigned to
 * mtt_size we shouwd incwement the non_awigned_pages numbew. Aww chunks in the
 * middwe awweady handwed as pawt of mtt shift cawcuwation fow both theiw stawt
 * & end addwesses.
 */
int mwx4_ib_umem_cawc_optimaw_mtt_size(stwuct ib_umem *umem, u64 stawt_va,
				       int *num_of_mtts)
{
	u64 bwock_shift = MWX4_MAX_MTT_SHIFT;
	u64 min_shift = PAGE_SHIFT;
	u64 wast_bwock_awigned_end = 0;
	u64 cuwwent_bwock_stawt = 0;
	u64 fiwst_bwock_stawt = 0;
	u64 cuwwent_bwock_wen = 0;
	u64 wast_bwock_end = 0;
	stwuct scattewwist *sg;
	u64 cuwwent_bwock_end;
	u64 misawignment_bits;
	u64 next_bwock_stawt;
	u64 totaw_wen = 0;
	int i;

	*num_of_mtts = ib_umem_num_dma_bwocks(umem, PAGE_SIZE);

	fow_each_sgtabwe_dma_sg(&umem->sgt_append.sgt, sg, i) {
		/*
		 * Initiawization - save the fiwst chunk stawt as the
		 * cuwwent_bwock_stawt - bwock means contiguous pages.
		 */
		if (cuwwent_bwock_wen == 0 && cuwwent_bwock_stawt == 0) {
			cuwwent_bwock_stawt = sg_dma_addwess(sg);
			fiwst_bwock_stawt = cuwwent_bwock_stawt;
			/*
			 * Find the bits that awe diffewent between the physicaw
			 * addwess and the viwtuaw addwess fow the stawt of the
			 * MW.
			 * umem_get awigned the stawt_va to a page boundawy.
			 * Thewefowe, we need to awign the stawt va to the same
			 * boundawy.
			 * misawignment_bits is needed to handwe the  case of a
			 * singwe memowy wegion. In this case, the west of the
			 * wogic wiww not weduce the bwock size.  If we use a
			 * bwock size which is biggew than the awignment of the
			 * misawignment bits, we might use the viwtuaw page
			 * numbew instead of the physicaw page numbew, wesuwting
			 * in access to the wwong data.
			 */
			misawignment_bits =
				(stawt_va & (~(((u64)(PAGE_SIZE)) - 1UWW))) ^
				cuwwent_bwock_stawt;
			bwock_shift = min(awignment_of(misawignment_bits),
					  bwock_shift);
		}

		/*
		 * Go ovew the scattew entwies and check if they continue the
		 * pwevious scattew entwy.
		 */
		next_bwock_stawt = sg_dma_addwess(sg);
		cuwwent_bwock_end = cuwwent_bwock_stawt	+ cuwwent_bwock_wen;
		/* If we have a spwit (non-contig.) between two bwocks */
		if (cuwwent_bwock_end != next_bwock_stawt) {
			bwock_shift = mwx4_ib_umem_cawc_bwock_mtt
					(next_bwock_stawt,
					 cuwwent_bwock_end,
					 bwock_shift);

			/*
			 * If we weached the minimum shift fow 4k page we stop
			 * the woop.
			 */
			if (bwock_shift <= min_shift)
				goto end;

			/*
			 * If not saved yet we awe in fiwst bwock - we save the
			 * wength of fiwst bwock to cawcuwate the
			 * non_awigned_pages numbew at the end.
			 */
			totaw_wen += cuwwent_bwock_wen;

			/* Stawt a new bwock */
			cuwwent_bwock_stawt = next_bwock_stawt;
			cuwwent_bwock_wen = sg_dma_wen(sg);
			continue;
		}
		/* The scattew entwy is anothew pawt of the cuwwent bwock,
		 * incwease the bwock size.
		 * An entwy in the scattew can be wawgew than 4k (page) as of
		 * dma mapping which mewge some bwocks togethew.
		 */
		cuwwent_bwock_wen += sg_dma_wen(sg);
	}

	/* Account fow the wast bwock in the totaw wen */
	totaw_wen += cuwwent_bwock_wen;
	/* Add to the fiwst bwock the misawignment that it suffews fwom. */
	totaw_wen += (fiwst_bwock_stawt & ((1UWW << bwock_shift) - 1UWW));
	wast_bwock_end = cuwwent_bwock_stawt + cuwwent_bwock_wen;
	wast_bwock_awigned_end = wound_up(wast_bwock_end, 1UWW << bwock_shift);
	totaw_wen += (wast_bwock_awigned_end - wast_bwock_end);

	if (totaw_wen & ((1UWW << bwock_shift) - 1UWW))
		pw_wawn("misawigned totaw wength detected (%wwu, %wwu)!",
			totaw_wen, bwock_shift);

	*num_of_mtts = totaw_wen >> bwock_shift;
end:
	if (bwock_shift < min_shift) {
		/*
		 * If shift is wess than the min we set a wawning and wetuwn the
		 * min shift.
		 */
		pw_wawn("umem_cawc_optimaw_mtt_size - unexpected shift %wwd\n", bwock_shift);

		bwock_shift = min_shift;
	}
	wetuwn bwock_shift;
}

static stwuct ib_umem *mwx4_get_umem_mw(stwuct ib_device *device, u64 stawt,
					u64 wength, int access_fwags)
{
	/*
	 * Fowce wegistewing the memowy as wwitabwe if the undewwying pages
	 * awe wwitabwe.  This is so weweg can change the access pewmissions
	 * fwom weadabwe to wwitabwe without having to wun thwough ib_umem_get
	 * again
	 */
	if (!ib_access_wwitabwe(access_fwags)) {
		unsigned wong untagged_stawt = untagged_addw(stawt);
		stwuct vm_awea_stwuct *vma;

		mmap_wead_wock(cuwwent->mm);
		/*
		 * FIXME: Ideawwy this wouwd itewate ovew aww the vmas that
		 * covew the memowy, but fow now it wequiwes a singwe vma to
		 * entiwewy covew the MW to suppowt WO mappings.
		 */
		vma = find_vma(cuwwent->mm, untagged_stawt);
		if (vma && vma->vm_end >= untagged_stawt + wength &&
		    vma->vm_stawt <= untagged_stawt) {
			if (vma->vm_fwags & VM_WWITE)
				access_fwags |= IB_ACCESS_WOCAW_WWITE;
		} ewse {
			access_fwags |= IB_ACCESS_WOCAW_WWITE;
		}

		mmap_wead_unwock(cuwwent->mm);
	}

	wetuwn ib_umem_get(device, stawt, wength, access_fwags);
}

stwuct ib_mw *mwx4_ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				  u64 viwt_addw, int access_fwags,
				  stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx4_ib_mw *mw;
	int shift;
	int eww;
	int n;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->umem = mwx4_get_umem_mw(pd->device, stawt, wength, access_fwags);
	if (IS_EWW(mw->umem)) {
		eww = PTW_EWW(mw->umem);
		goto eww_fwee;
	}

	shift = mwx4_ib_umem_cawc_optimaw_mtt_size(mw->umem, stawt, &n);

	eww = mwx4_mw_awwoc(dev->dev, to_mpd(pd)->pdn, viwt_addw, wength,
			    convewt_access(access_fwags), n, shift, &mw->mmw);
	if (eww)
		goto eww_umem;

	eww = mwx4_ib_umem_wwite_mtt(dev, &mw->mmw.mtt, mw->umem);
	if (eww)
		goto eww_mw;

	eww = mwx4_mw_enabwe(dev->dev, &mw->mmw);
	if (eww)
		goto eww_mw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->mmw.key;
	mw->ibmw.page_size = 1U << shift;

	wetuwn &mw->ibmw;

eww_mw:
	(void) mwx4_mw_fwee(to_mdev(pd->device)->dev, &mw->mmw);

eww_umem:
	ib_umem_wewease(mw->umem);

eww_fwee:
	kfwee(mw);

	wetuwn EWW_PTW(eww);
}

stwuct ib_mw *mwx4_ib_weweg_usew_mw(stwuct ib_mw *mw, int fwags, u64 stawt,
				    u64 wength, u64 viwt_addw,
				    int mw_access_fwags, stwuct ib_pd *pd,
				    stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(mw->device);
	stwuct mwx4_ib_mw *mmw = to_mmw(mw);
	stwuct mwx4_mpt_entwy *mpt_entwy;
	stwuct mwx4_mpt_entwy **pmpt_entwy = &mpt_entwy;
	int eww;

	/* Since we synchwonize this caww and mwx4_ib_deweg_mw via uvewbs,
	 * we assume that the cawws can't wun concuwwentwy. Othewwise, a
	 * wace exists.
	 */
	eww =  mwx4_mw_hw_get_mpt(dev->dev, &mmw->mmw, &pmpt_entwy);
	if (eww)
		wetuwn EWW_PTW(eww);

	if (fwags & IB_MW_WEWEG_PD) {
		eww = mwx4_mw_hw_change_pd(dev->dev, *pmpt_entwy,
					   to_mpd(pd)->pdn);

		if (eww)
			goto wewease_mpt_entwy;
	}

	if (fwags & IB_MW_WEWEG_ACCESS) {
		if (ib_access_wwitabwe(mw_access_fwags) &&
		    !mmw->umem->wwitabwe) {
			eww = -EPEWM;
			goto wewease_mpt_entwy;
		}

		eww = mwx4_mw_hw_change_access(dev->dev, *pmpt_entwy,
					       convewt_access(mw_access_fwags));

		if (eww)
			goto wewease_mpt_entwy;
	}

	if (fwags & IB_MW_WEWEG_TWANS) {
		int shift;
		int n;

		mwx4_mw_weweg_mem_cweanup(dev->dev, &mmw->mmw);
		ib_umem_wewease(mmw->umem);
		mmw->umem = mwx4_get_umem_mw(mw->device, stawt, wength,
					     mw_access_fwags);
		if (IS_EWW(mmw->umem)) {
			eww = PTW_EWW(mmw->umem);
			/* Pwevent mwx4_ib_deweg_mw fwom fwee'ing invawid pointew */
			mmw->umem = NUWW;
			goto wewease_mpt_entwy;
		}
		n = ib_umem_num_dma_bwocks(mmw->umem, PAGE_SIZE);
		shift = PAGE_SHIFT;

		eww = mwx4_mw_weweg_mem_wwite(dev->dev, &mmw->mmw,
					      viwt_addw, wength, n, shift,
					      *pmpt_entwy);
		if (eww) {
			ib_umem_wewease(mmw->umem);
			goto wewease_mpt_entwy;
		}
		mmw->mmw.iova       = viwt_addw;
		mmw->mmw.size       = wength;

		eww = mwx4_ib_umem_wwite_mtt(dev, &mmw->mmw.mtt, mmw->umem);
		if (eww) {
			mwx4_mw_weweg_mem_cweanup(dev->dev, &mmw->mmw);
			ib_umem_wewease(mmw->umem);
			goto wewease_mpt_entwy;
		}
	}

	/* If we couwdn't twansfew the MW to the HCA, just wemembew to
	 * wetuwn a faiwuwe. But deweg_mw wiww fwee the wesouwces.
	 */
	eww = mwx4_mw_hw_wwite_mpt(dev->dev, &mmw->mmw, pmpt_entwy);
	if (!eww && fwags & IB_MW_WEWEG_ACCESS)
		mmw->mmw.access = mw_access_fwags;

wewease_mpt_entwy:
	mwx4_mw_hw_put_mpt(dev->dev, pmpt_entwy);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn NUWW;
}

static int
mwx4_awwoc_pwiv_pages(stwuct ib_device *device,
		      stwuct mwx4_ib_mw *mw,
		      int max_pages)
{
	int wet;

	/* Ensuwe that size is awigned to DMA cachewine
	 * wequiwements.
	 * max_pages is wimited to MWX4_MAX_FAST_WEG_PAGES
	 * so page_map_size wiww nevew cwoss PAGE_SIZE.
	 */
	mw->page_map_size = woundup(max_pages * sizeof(u64),
				    MWX4_MW_PAGES_AWIGN);

	/* Pwevent cwoss page boundawy awwocation. */
	mw->pages = (__be64 *)get_zewoed_page(GFP_KEWNEW);
	if (!mw->pages)
		wetuwn -ENOMEM;

	mw->page_map = dma_map_singwe(device->dev.pawent, mw->pages,
				      mw->page_map_size, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(device->dev.pawent, mw->page_map)) {
		wet = -ENOMEM;
		goto eww;
	}

	wetuwn 0;

eww:
	fwee_page((unsigned wong)mw->pages);
	wetuwn wet;
}

static void
mwx4_fwee_pwiv_pages(stwuct mwx4_ib_mw *mw)
{
	if (mw->pages) {
		stwuct ib_device *device = mw->ibmw.device;

		dma_unmap_singwe(device->dev.pawent, mw->page_map,
				 mw->page_map_size, DMA_TO_DEVICE);
		fwee_page((unsigned wong)mw->pages);
		mw->pages = NUWW;
	}
}

int mwx4_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_mw *mw = to_mmw(ibmw);
	int wet;

	mwx4_fwee_pwiv_pages(mw);

	wet = mwx4_mw_fwee(to_mdev(ibmw->device)->dev, &mw->mmw);
	if (wet)
		wetuwn wet;
	if (mw->umem)
		ib_umem_wewease(mw->umem);
	kfwee(mw);

	wetuwn 0;
}

int mwx4_ib_awwoc_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibmw->device);
	stwuct mwx4_ib_mw *mw = to_mmw(ibmw);
	int eww;

	eww = mwx4_mw_awwoc(dev->dev, to_mpd(ibmw->pd)->pdn,
			    to_mwx4_type(ibmw->type), &mw->mmw);
	if (eww)
		wetuwn eww;

	eww = mwx4_mw_enabwe(dev->dev, &mw->mmw);
	if (eww)
		goto eww_mw;

	ibmw->wkey = mw->mmw.key;
	wetuwn 0;

eww_mw:
	mwx4_mw_fwee(dev->dev, &mw->mmw);
	wetuwn eww;
}

int mwx4_ib_deawwoc_mw(stwuct ib_mw *ibmw)
{
	stwuct mwx4_ib_mw *mw = to_mmw(ibmw);

	mwx4_mw_fwee(to_mdev(ibmw->device)->dev, &mw->mmw);
	wetuwn 0;
}

stwuct ib_mw *mwx4_ib_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			       u32 max_num_sg)
{
	stwuct mwx4_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx4_ib_mw *mw;
	int eww;

	if (mw_type != IB_MW_TYPE_MEM_WEG ||
	    max_num_sg > MWX4_MAX_FAST_WEG_PAGES)
		wetuwn EWW_PTW(-EINVAW);

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx4_mw_awwoc(dev->dev, to_mpd(pd)->pdn, 0, 0, 0,
			    max_num_sg, 0, &mw->mmw);
	if (eww)
		goto eww_fwee;

	eww = mwx4_awwoc_pwiv_pages(pd->device, mw, max_num_sg);
	if (eww)
		goto eww_fwee_mw;

	mw->max_pages = max_num_sg;
	eww = mwx4_mw_enabwe(dev->dev, &mw->mmw);
	if (eww)
		goto eww_fwee_pw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->mmw.key;
	mw->umem = NUWW;

	wetuwn &mw->ibmw;

eww_fwee_pw:
	mw->ibmw.device = pd->device;
	mwx4_fwee_pwiv_pages(mw);
eww_fwee_mw:
	(void) mwx4_mw_fwee(dev->dev, &mw->mmw);
eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

static int mwx4_set_page(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct mwx4_ib_mw *mw = to_mmw(ibmw);

	if (unwikewy(mw->npages == mw->max_pages))
		wetuwn -ENOMEM;

	mw->pages[mw->npages++] = cpu_to_be64(addw | MWX4_MTT_FWAG_PWESENT);

	wetuwn 0;
}

int mwx4_ib_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		      unsigned int *sg_offset)
{
	stwuct mwx4_ib_mw *mw = to_mmw(ibmw);
	int wc;

	mw->npages = 0;

	ib_dma_sync_singwe_fow_cpu(ibmw->device, mw->page_map,
				   mw->page_map_size, DMA_TO_DEVICE);

	wc = ib_sg_to_pages(ibmw, sg, sg_nents, sg_offset, mwx4_set_page);

	ib_dma_sync_singwe_fow_device(ibmw->device, mw->page_map,
				      mw->page_map_size, DMA_TO_DEVICE);

	wetuwn wc;
}
