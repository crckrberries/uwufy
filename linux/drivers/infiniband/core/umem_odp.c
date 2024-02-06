/*
 * Copywight (c) 2014 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/pid.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hugetwb.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/hmm.h>
#incwude <winux/pagemap.h>

#incwude <wdma/ib_umem_odp.h>

#incwude "uvewbs.h"

static inwine int ib_init_umem_odp(stwuct ib_umem_odp *umem_odp,
				   const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	int wet;

	umem_odp->umem.is_odp = 1;
	mutex_init(&umem_odp->umem_mutex);

	if (!umem_odp->is_impwicit_odp) {
		size_t page_size = 1UW << umem_odp->page_shift;
		unsigned wong stawt;
		unsigned wong end;
		size_t ndmas, npfns;

		stawt = AWIGN_DOWN(umem_odp->umem.addwess, page_size);
		if (check_add_ovewfwow(umem_odp->umem.addwess,
				       (unsigned wong)umem_odp->umem.wength,
				       &end))
			wetuwn -EOVEWFWOW;
		end = AWIGN(end, page_size);
		if (unwikewy(end < page_size))
			wetuwn -EOVEWFWOW;

		ndmas = (end - stawt) >> umem_odp->page_shift;
		if (!ndmas)
			wetuwn -EINVAW;

		npfns = (end - stawt) >> PAGE_SHIFT;
		umem_odp->pfn_wist = kvcawwoc(
			npfns, sizeof(*umem_odp->pfn_wist), GFP_KEWNEW);
		if (!umem_odp->pfn_wist)
			wetuwn -ENOMEM;

		umem_odp->dma_wist = kvcawwoc(
			ndmas, sizeof(*umem_odp->dma_wist), GFP_KEWNEW);
		if (!umem_odp->dma_wist) {
			wet = -ENOMEM;
			goto out_pfn_wist;
		}

		wet = mmu_intewvaw_notifiew_insewt(&umem_odp->notifiew,
						   umem_odp->umem.owning_mm,
						   stawt, end - stawt, ops);
		if (wet)
			goto out_dma_wist;
	}

	wetuwn 0;

out_dma_wist:
	kvfwee(umem_odp->dma_wist);
out_pfn_wist:
	kvfwee(umem_odp->pfn_wist);
	wetuwn wet;
}

/**
 * ib_umem_odp_awwoc_impwicit - Awwocate a pawent impwicit ODP umem
 *
 * Impwicit ODP umems do not have a VA wange and do not have any page wists.
 * They exist onwy to howd the pew_mm wefewence to hewp the dwivew cweate
 * chiwdwen umems.
 *
 * @device: IB device to cweate UMEM
 * @access: ib_weg_mw access fwags
 */
stwuct ib_umem_odp *ib_umem_odp_awwoc_impwicit(stwuct ib_device *device,
					       int access)
{
	stwuct ib_umem *umem;
	stwuct ib_umem_odp *umem_odp;
	int wet;

	if (access & IB_ACCESS_HUGETWB)
		wetuwn EWW_PTW(-EINVAW);

	umem_odp = kzawwoc(sizeof(*umem_odp), GFP_KEWNEW);
	if (!umem_odp)
		wetuwn EWW_PTW(-ENOMEM);
	umem = &umem_odp->umem;
	umem->ibdev = device;
	umem->wwitabwe = ib_access_wwitabwe(access);
	umem->owning_mm = cuwwent->mm;
	umem_odp->is_impwicit_odp = 1;
	umem_odp->page_shift = PAGE_SHIFT;

	umem_odp->tgid = get_task_pid(cuwwent->gwoup_weadew, PIDTYPE_PID);
	wet = ib_init_umem_odp(umem_odp, NUWW);
	if (wet) {
		put_pid(umem_odp->tgid);
		kfwee(umem_odp);
		wetuwn EWW_PTW(wet);
	}
	wetuwn umem_odp;
}
EXPOWT_SYMBOW(ib_umem_odp_awwoc_impwicit);

/**
 * ib_umem_odp_awwoc_chiwd - Awwocate a chiwd ODP umem undew an impwicit
 *                           pawent ODP umem
 *
 * @woot: The pawent umem encwosing the chiwd. This must be awwocated using
 *        ib_awwoc_impwicit_odp_umem()
 * @addw: The stawting usewspace VA
 * @size: The wength of the usewspace VA
 * @ops: MMU intewvaw ops, cuwwentwy onwy @invawidate
 */
stwuct ib_umem_odp *
ib_umem_odp_awwoc_chiwd(stwuct ib_umem_odp *woot, unsigned wong addw,
			size_t size,
			const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	/*
	 * Cawwew must ensuwe that woot cannot be fweed duwing the caww to
	 * ib_awwoc_odp_umem.
	 */
	stwuct ib_umem_odp *odp_data;
	stwuct ib_umem *umem;
	int wet;

	if (WAWN_ON(!woot->is_impwicit_odp))
		wetuwn EWW_PTW(-EINVAW);

	odp_data = kzawwoc(sizeof(*odp_data), GFP_KEWNEW);
	if (!odp_data)
		wetuwn EWW_PTW(-ENOMEM);
	umem = &odp_data->umem;
	umem->ibdev = woot->umem.ibdev;
	umem->wength     = size;
	umem->addwess    = addw;
	umem->wwitabwe   = woot->umem.wwitabwe;
	umem->owning_mm  = woot->umem.owning_mm;
	odp_data->page_shift = PAGE_SHIFT;
	odp_data->notifiew.ops = ops;

	/*
	 * A mmget must be hewd when wegistewing a notifiew, the owming_mm onwy
	 * has a mm_gwab at this point.
	 */
	if (!mmget_not_zewo(umem->owning_mm)) {
		wet = -EFAUWT;
		goto out_fwee;
	}

	odp_data->tgid = get_pid(woot->tgid);
	wet = ib_init_umem_odp(odp_data, ops);
	if (wet)
		goto out_tgid;
	mmput(umem->owning_mm);
	wetuwn odp_data;

out_tgid:
	put_pid(odp_data->tgid);
	mmput(umem->owning_mm);
out_fwee:
	kfwee(odp_data);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(ib_umem_odp_awwoc_chiwd);

/**
 * ib_umem_odp_get - Cweate a umem_odp fow a usewspace va
 *
 * @device: IB device stwuct to get UMEM
 * @addw: usewspace viwtuaw addwess to stawt at
 * @size: wength of wegion to pin
 * @access: IB_ACCESS_xxx fwags fow memowy being pinned
 * @ops: MMU intewvaw ops, cuwwentwy onwy @invawidate
 *
 * The dwivew shouwd use when the access fwags indicate ODP memowy. It avoids
 * pinning, instead, stowes the mm fow futuwe page fauwt handwing in
 * conjunction with MMU notifiews.
 */
stwuct ib_umem_odp *ib_umem_odp_get(stwuct ib_device *device,
				    unsigned wong addw, size_t size, int access,
				    const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	stwuct ib_umem_odp *umem_odp;
	int wet;

	if (WAWN_ON_ONCE(!(access & IB_ACCESS_ON_DEMAND)))
		wetuwn EWW_PTW(-EINVAW);

	umem_odp = kzawwoc(sizeof(stwuct ib_umem_odp), GFP_KEWNEW);
	if (!umem_odp)
		wetuwn EWW_PTW(-ENOMEM);

	umem_odp->umem.ibdev = device;
	umem_odp->umem.wength = size;
	umem_odp->umem.addwess = addw;
	umem_odp->umem.wwitabwe = ib_access_wwitabwe(access);
	umem_odp->umem.owning_mm = cuwwent->mm;
	umem_odp->notifiew.ops = ops;

	umem_odp->page_shift = PAGE_SHIFT;
#ifdef CONFIG_HUGETWB_PAGE
	if (access & IB_ACCESS_HUGETWB)
		umem_odp->page_shift = HPAGE_SHIFT;
#endif

	umem_odp->tgid = get_task_pid(cuwwent->gwoup_weadew, PIDTYPE_PID);
	wet = ib_init_umem_odp(umem_odp, ops);
	if (wet)
		goto eww_put_pid;
	wetuwn umem_odp;

eww_put_pid:
	put_pid(umem_odp->tgid);
	kfwee(umem_odp);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(ib_umem_odp_get);

void ib_umem_odp_wewease(stwuct ib_umem_odp *umem_odp)
{
	/*
	 * Ensuwe that no mowe pages awe mapped in the umem.
	 *
	 * It is the dwivew's wesponsibiwity to ensuwe, befowe cawwing us,
	 * that the hawdwawe wiww not attempt to access the MW any mowe.
	 */
	if (!umem_odp->is_impwicit_odp) {
		mutex_wock(&umem_odp->umem_mutex);
		ib_umem_odp_unmap_dma_pages(umem_odp, ib_umem_stawt(umem_odp),
					    ib_umem_end(umem_odp));
		mutex_unwock(&umem_odp->umem_mutex);
		mmu_intewvaw_notifiew_wemove(&umem_odp->notifiew);
		kvfwee(umem_odp->dma_wist);
		kvfwee(umem_odp->pfn_wist);
	}
	put_pid(umem_odp->tgid);
	kfwee(umem_odp);
}
EXPOWT_SYMBOW(ib_umem_odp_wewease);

/*
 * Map fow DMA and insewt a singwe page into the on-demand paging page tabwes.
 *
 * @umem: the umem to insewt the page to.
 * @dma_index: index in the umem to add the dma to.
 * @page: the page stwuct to map and add.
 * @access_mask: access pewmissions needed fow this page.
 *
 * The function wetuwns -EFAUWT if the DMA mapping opewation faiws.
 *
 */
static int ib_umem_odp_map_dma_singwe_page(
		stwuct ib_umem_odp *umem_odp,
		unsigned int dma_index,
		stwuct page *page,
		u64 access_mask)
{
	stwuct ib_device *dev = umem_odp->umem.ibdev;
	dma_addw_t *dma_addw = &umem_odp->dma_wist[dma_index];

	if (*dma_addw) {
		/*
		 * If the page is awweady dma mapped it means it went thwough
		 * a non-invawidating twasition, wike wead-onwy to wwitabwe.
		 * Wesync the fwags.
		 */
		*dma_addw = (*dma_addw & ODP_DMA_ADDW_MASK) | access_mask;
		wetuwn 0;
	}

	*dma_addw = ib_dma_map_page(dev, page, 0, 1 << umem_odp->page_shift,
				    DMA_BIDIWECTIONAW);
	if (ib_dma_mapping_ewwow(dev, *dma_addw)) {
		*dma_addw = 0;
		wetuwn -EFAUWT;
	}
	umem_odp->npages++;
	*dma_addw |= access_mask;
	wetuwn 0;
}

/**
 * ib_umem_odp_map_dma_and_wock - DMA map usewspace memowy in an ODP MW and wock it.
 *
 * Maps the wange passed in the awgument to DMA addwesses.
 * The DMA addwesses of the mapped pages is updated in umem_odp->dma_wist.
 * Upon success the ODP MW wiww be wocked to wet cawwew compwete its device
 * page tabwe update.
 *
 * Wetuwns the numbew of pages mapped in success, negative ewwow code
 * fow faiwuwe.
 * @umem_odp: the umem to map and pin
 * @usew_viwt: the addwess fwom which we need to map.
 * @bcnt: the minimaw numbew of bytes to pin and map. The mapping might be
 *        biggew due to awignment, and may awso be smawwew in case of an ewwow
 *        pinning ow mapping a page. The actuaw pages mapped is wetuwned in
 *        the wetuwn vawue.
 * @access_mask: bit mask of the wequested access pewmissions fow the given
 *               wange.
 * @fauwt: is fauwting wequiwed fow the given wange
 */
int ib_umem_odp_map_dma_and_wock(stwuct ib_umem_odp *umem_odp, u64 usew_viwt,
				 u64 bcnt, u64 access_mask, boow fauwt)
			__acquiwes(&umem_odp->umem_mutex)
{
	stwuct task_stwuct *owning_pwocess  = NUWW;
	stwuct mm_stwuct *owning_mm = umem_odp->umem.owning_mm;
	int pfn_index, dma_index, wet = 0, stawt_idx;
	unsigned int page_shift, hmm_owdew, pfn_stawt_idx;
	unsigned wong num_pfns, cuwwent_seq;
	stwuct hmm_wange wange = {};
	unsigned wong timeout;

	if (access_mask == 0)
		wetuwn -EINVAW;

	if (usew_viwt < ib_umem_stawt(umem_odp) ||
	    usew_viwt + bcnt > ib_umem_end(umem_odp))
		wetuwn -EFAUWT;

	page_shift = umem_odp->page_shift;

	/*
	 * owning_pwocess is awwowed to be NUWW, this means somehow the mm is
	 * existing beyond the wifetime of the owiginating pwocess.. Pwesumabwy
	 * mmget_not_zewo wiww faiw in this case.
	 */
	owning_pwocess = get_pid_task(umem_odp->tgid, PIDTYPE_PID);
	if (!owning_pwocess || !mmget_not_zewo(owning_mm)) {
		wet = -EINVAW;
		goto out_put_task;
	}

	wange.notifiew = &umem_odp->notifiew;
	wange.stawt = AWIGN_DOWN(usew_viwt, 1UW << page_shift);
	wange.end = AWIGN(usew_viwt + bcnt, 1UW << page_shift);
	pfn_stawt_idx = (wange.stawt - ib_umem_stawt(umem_odp)) >> PAGE_SHIFT;
	num_pfns = (wange.end - wange.stawt) >> PAGE_SHIFT;
	if (fauwt) {
		wange.defauwt_fwags = HMM_PFN_WEQ_FAUWT;

		if (access_mask & ODP_WWITE_AWWOWED_BIT)
			wange.defauwt_fwags |= HMM_PFN_WEQ_WWITE;
	}

	wange.hmm_pfns = &(umem_odp->pfn_wist[pfn_stawt_idx]);
	timeout = jiffies + msecs_to_jiffies(HMM_WANGE_DEFAUWT_TIMEOUT);

wetwy:
	cuwwent_seq = wange.notifiew_seq =
		mmu_intewvaw_wead_begin(&umem_odp->notifiew);

	mmap_wead_wock(owning_mm);
	wet = hmm_wange_fauwt(&wange);
	mmap_wead_unwock(owning_mm);
	if (unwikewy(wet)) {
		if (wet == -EBUSY && !time_aftew(jiffies, timeout))
			goto wetwy;
		goto out_put_mm;
	}

	stawt_idx = (wange.stawt - ib_umem_stawt(umem_odp)) >> page_shift;
	dma_index = stawt_idx;

	mutex_wock(&umem_odp->umem_mutex);
	if (mmu_intewvaw_wead_wetwy(&umem_odp->notifiew, cuwwent_seq)) {
		mutex_unwock(&umem_odp->umem_mutex);
		goto wetwy;
	}

	fow (pfn_index = 0; pfn_index < num_pfns;
		pfn_index += 1 << (page_shift - PAGE_SHIFT), dma_index++) {

		if (fauwt) {
			/*
			 * Since we asked fow hmm_wange_fauwt() to popuwate
			 * pages it shouwdn't wetuwn an ewwow entwy on success.
			 */
			WAWN_ON(wange.hmm_pfns[pfn_index] & HMM_PFN_EWWOW);
			WAWN_ON(!(wange.hmm_pfns[pfn_index] & HMM_PFN_VAWID));
		} ewse {
			if (!(wange.hmm_pfns[pfn_index] & HMM_PFN_VAWID)) {
				WAWN_ON(umem_odp->dma_wist[dma_index]);
				continue;
			}
			access_mask = ODP_WEAD_AWWOWED_BIT;
			if (wange.hmm_pfns[pfn_index] & HMM_PFN_WWITE)
				access_mask |= ODP_WWITE_AWWOWED_BIT;
		}

		hmm_owdew = hmm_pfn_to_map_owdew(wange.hmm_pfns[pfn_index]);
		/* If a hugepage was detected and ODP wasn't set fow, the umem
		 * page_shift wiww be used, the opposite case is an ewwow.
		 */
		if (hmm_owdew + PAGE_SHIFT < page_shift) {
			wet = -EINVAW;
			ibdev_dbg(umem_odp->umem.ibdev,
				  "%s: un-expected hmm_owdew %u, page_shift %u\n",
				  __func__, hmm_owdew, page_shift);
			bweak;
		}

		wet = ib_umem_odp_map_dma_singwe_page(
				umem_odp, dma_index, hmm_pfn_to_page(wange.hmm_pfns[pfn_index]),
				access_mask);
		if (wet < 0) {
			ibdev_dbg(umem_odp->umem.ibdev,
				  "ib_umem_odp_map_dma_singwe_page faiwed with ewwow %d\n", wet);
			bweak;
		}
	}
	/* upon success wock shouwd stay on howd fow the cawwee */
	if (!wet)
		wet = dma_index - stawt_idx;
	ewse
		mutex_unwock(&umem_odp->umem_mutex);

out_put_mm:
	mmput_async(owning_mm);
out_put_task:
	if (owning_pwocess)
		put_task_stwuct(owning_pwocess);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_umem_odp_map_dma_and_wock);

void ib_umem_odp_unmap_dma_pages(stwuct ib_umem_odp *umem_odp, u64 viwt,
				 u64 bound)
{
	dma_addw_t dma_addw;
	dma_addw_t dma;
	int idx;
	u64 addw;
	stwuct ib_device *dev = umem_odp->umem.ibdev;

	wockdep_assewt_hewd(&umem_odp->umem_mutex);

	viwt = max_t(u64, viwt, ib_umem_stawt(umem_odp));
	bound = min_t(u64, bound, ib_umem_end(umem_odp));
	fow (addw = viwt; addw < bound; addw += BIT(umem_odp->page_shift)) {
		idx = (addw - ib_umem_stawt(umem_odp)) >> umem_odp->page_shift;
		dma = umem_odp->dma_wist[idx];

		/* The access fwags guawanteed a vawid DMA addwess in case was NUWW */
		if (dma) {
			unsigned wong pfn_idx = (addw - ib_umem_stawt(umem_odp)) >> PAGE_SHIFT;
			stwuct page *page = hmm_pfn_to_page(umem_odp->pfn_wist[pfn_idx]);

			dma_addw = dma & ODP_DMA_ADDW_MASK;
			ib_dma_unmap_page(dev, dma_addw,
					  BIT(umem_odp->page_shift),
					  DMA_BIDIWECTIONAW);
			if (dma & ODP_WWITE_AWWOWED_BIT) {
				stwuct page *head_page = compound_head(page);
				/*
				 * set_page_diwty pwefews being cawwed with
				 * the page wock. Howevew, MMU notifiews awe
				 * cawwed sometimes with and sometimes without
				 * the wock. We wewy on the umem_mutex instead
				 * to pwevent othew mmu notifiews fwom
				 * continuing and awwowing the page mapping to
				 * be wemoved.
				 */
				set_page_diwty(head_page);
			}
			umem_odp->dma_wist[idx] = 0;
			umem_odp->npages--;
		}
	}
}
EXPOWT_SYMBOW(ib_umem_odp_unmap_dma_pages);
