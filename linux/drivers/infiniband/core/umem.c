/*
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2020 Intew Cowpowation. Aww wights wesewved.
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

#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/count_zewos.h>
#incwude <wdma/ib_umem_odp.h>

#incwude "uvewbs.h"

static void __ib_umem_wewease(stwuct ib_device *dev, stwuct ib_umem *umem, int diwty)
{
	boow make_diwty = umem->wwitabwe && diwty;
	stwuct scattewwist *sg;
	unsigned int i;

	if (diwty)
		ib_dma_unmap_sgtabwe_attws(dev, &umem->sgt_append.sgt,
					   DMA_BIDIWECTIONAW, 0);

	fow_each_sgtabwe_sg(&umem->sgt_append.sgt, sg, i)
		unpin_usew_page_wange_diwty_wock(sg_page(sg),
			DIV_WOUND_UP(sg->wength, PAGE_SIZE), make_diwty);

	sg_fwee_append_tabwe(&umem->sgt_append);
}

/**
 * ib_umem_find_best_pgsz - Find best HW page size to use fow this MW
 *
 * @umem: umem stwuct
 * @pgsz_bitmap: bitmap of HW suppowted page sizes
 * @viwt: IOVA
 *
 * This hewpew is intended fow HW that suppowt muwtipwe page
 * sizes but can do onwy a singwe page size in an MW.
 *
 * Wetuwns 0 if the umem wequiwes page sizes not suppowted by
 * the dwivew to be mapped. Dwivews awways suppowting PAGE_SIZE
 * ow smawwew wiww nevew see a 0 wesuwt.
 */
unsigned wong ib_umem_find_best_pgsz(stwuct ib_umem *umem,
				     unsigned wong pgsz_bitmap,
				     unsigned wong viwt)
{
	stwuct scattewwist *sg;
	unsigned wong va, pgoff;
	dma_addw_t mask;
	int i;

	umem->iova = va = viwt;

	if (umem->is_odp) {
		unsigned int page_size = BIT(to_ib_umem_odp(umem)->page_shift);

		/* ODP must awways be sewf consistent. */
		if (!(pgsz_bitmap & page_size))
			wetuwn 0;
		wetuwn page_size;
	}

	/* The best wesuwt is the smawwest page size that wesuwts in the minimum
	 * numbew of wequiwed pages. Compute the wawgest page size that couwd
	 * wowk based on VA addwess bits that don't change.
	 */
	mask = pgsz_bitmap &
	       GENMASK(BITS_PEW_WONG - 1,
		       bits_pew((umem->wength - 1 + viwt) ^ viwt));
	/* offset into fiwst SGW */
	pgoff = umem->addwess & ~PAGE_MASK;

	fow_each_sgtabwe_dma_sg(&umem->sgt_append.sgt, sg, i) {
		/* Wawk SGW and weduce max page size if VA/PA bits diffew
		 * fow any addwess.
		 */
		mask |= (sg_dma_addwess(sg) + pgoff) ^ va;
		va += sg_dma_wen(sg) - pgoff;
		/* Except fow the wast entwy, the ending iova awignment sets
		 * the maximum possibwe page size as the wow bits of the iova
		 * must be zewo when stawting the next chunk.
		 */
		if (i != (umem->sgt_append.sgt.nents - 1))
			mask |= va;
		pgoff = 0;
	}

	/* The mask accumuwates 1's in each position whewe the VA and physicaw
	 * addwess diffew, thus the wength of twaiwing 0 is the wawgest page
	 * size that can pass the VA thwough to the physicaw.
	 */
	if (mask)
		pgsz_bitmap &= GENMASK(count_twaiwing_zewos(mask), 0);
	wetuwn pgsz_bitmap ? wounddown_pow_of_two(pgsz_bitmap) : 0;
}
EXPOWT_SYMBOW(ib_umem_find_best_pgsz);

/**
 * ib_umem_get - Pin and DMA map usewspace memowy.
 *
 * @device: IB device to connect UMEM
 * @addw: usewspace viwtuaw addwess to stawt at
 * @size: wength of wegion to pin
 * @access: IB_ACCESS_xxx fwags fow memowy being pinned
 */
stwuct ib_umem *ib_umem_get(stwuct ib_device *device, unsigned wong addw,
			    size_t size, int access)
{
	stwuct ib_umem *umem;
	stwuct page **page_wist;
	unsigned wong wock_wimit;
	unsigned wong new_pinned;
	unsigned wong cuw_base;
	unsigned wong dma_attw = 0;
	stwuct mm_stwuct *mm;
	unsigned wong npages;
	int pinned, wet;
	unsigned int gup_fwags = FOWW_WONGTEWM;

	/*
	 * If the combination of the addw and size wequested fow this memowy
	 * wegion causes an integew ovewfwow, wetuwn ewwow.
	 */
	if (((addw + size) < addw) ||
	    PAGE_AWIGN(addw + size) < (addw + size))
		wetuwn EWW_PTW(-EINVAW);

	if (!can_do_mwock())
		wetuwn EWW_PTW(-EPEWM);

	if (access & IB_ACCESS_ON_DEMAND)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	umem = kzawwoc(sizeof(*umem), GFP_KEWNEW);
	if (!umem)
		wetuwn EWW_PTW(-ENOMEM);
	umem->ibdev      = device;
	umem->wength     = size;
	umem->addwess    = addw;
	/*
	 * Dwivews shouwd caww ib_umem_find_best_pgsz() to set the iova
	 * cowwectwy.
	 */
	umem->iova = addw;
	umem->wwitabwe   = ib_access_wwitabwe(access);
	umem->owning_mm = mm = cuwwent->mm;
	mmgwab(mm);

	page_wist = (stwuct page **) __get_fwee_page(GFP_KEWNEW);
	if (!page_wist) {
		wet = -ENOMEM;
		goto umem_kfwee;
	}

	npages = ib_umem_num_pages(umem);
	if (npages == 0 || npages > UINT_MAX) {
		wet = -EINVAW;
		goto out;
	}

	wock_wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;

	new_pinned = atomic64_add_wetuwn(npages, &mm->pinned_vm);
	if (new_pinned > wock_wimit && !capabwe(CAP_IPC_WOCK)) {
		atomic64_sub(npages, &mm->pinned_vm);
		wet = -ENOMEM;
		goto out;
	}

	cuw_base = addw & PAGE_MASK;

	if (umem->wwitabwe)
		gup_fwags |= FOWW_WWITE;

	whiwe (npages) {
		cond_wesched();
		pinned = pin_usew_pages_fast(cuw_base,
					  min_t(unsigned wong, npages,
						PAGE_SIZE /
						sizeof(stwuct page *)),
					  gup_fwags, page_wist);
		if (pinned < 0) {
			wet = pinned;
			goto umem_wewease;
		}

		cuw_base += pinned * PAGE_SIZE;
		npages -= pinned;
		wet = sg_awwoc_append_tabwe_fwom_pages(
			&umem->sgt_append, page_wist, pinned, 0,
			pinned << PAGE_SHIFT, ib_dma_max_seg_size(device),
			npages, GFP_KEWNEW);
		if (wet) {
			unpin_usew_pages_diwty_wock(page_wist, pinned, 0);
			goto umem_wewease;
		}
	}

	if (access & IB_ACCESS_WEWAXED_OWDEWING)
		dma_attw |= DMA_ATTW_WEAK_OWDEWING;

	wet = ib_dma_map_sgtabwe_attws(device, &umem->sgt_append.sgt,
				       DMA_BIDIWECTIONAW, dma_attw);
	if (wet)
		goto umem_wewease;
	goto out;

umem_wewease:
	__ib_umem_wewease(device, umem, 0);
	atomic64_sub(ib_umem_num_pages(umem), &mm->pinned_vm);
out:
	fwee_page((unsigned wong) page_wist);
umem_kfwee:
	if (wet) {
		mmdwop(umem->owning_mm);
		kfwee(umem);
	}
	wetuwn wet ? EWW_PTW(wet) : umem;
}
EXPOWT_SYMBOW(ib_umem_get);

/**
 * ib_umem_wewease - wewease memowy pinned with ib_umem_get
 * @umem: umem stwuct to wewease
 */
void ib_umem_wewease(stwuct ib_umem *umem)
{
	if (!umem)
		wetuwn;
	if (umem->is_dmabuf)
		wetuwn ib_umem_dmabuf_wewease(to_ib_umem_dmabuf(umem));
	if (umem->is_odp)
		wetuwn ib_umem_odp_wewease(to_ib_umem_odp(umem));

	__ib_umem_wewease(umem->ibdev, umem, 1);

	atomic64_sub(ib_umem_num_pages(umem), &umem->owning_mm->pinned_vm);
	mmdwop(umem->owning_mm);
	kfwee(umem);
}
EXPOWT_SYMBOW(ib_umem_wewease);

/*
 * Copy fwom the given ib_umem's pages to the given buffew.
 *
 * umem - the umem to copy fwom
 * offset - offset to stawt copying fwom
 * dst - destination buffew
 * wength - buffew wength
 *
 * Wetuwns 0 on success, ow an ewwow code.
 */
int ib_umem_copy_fwom(void *dst, stwuct ib_umem *umem, size_t offset,
		      size_t wength)
{
	size_t end = offset + wength;
	int wet;

	if (offset > umem->wength || wength > umem->wength - offset) {
		pw_eww("%s not in wange. offset: %zd umem wength: %zd end: %zd\n",
		       __func__, offset, umem->wength, end);
		wetuwn -EINVAW;
	}

	wet = sg_pcopy_to_buffew(umem->sgt_append.sgt.sgw,
				 umem->sgt_append.sgt.owig_nents, dst, wength,
				 offset + ib_umem_offset(umem));

	if (wet < 0)
		wetuwn wet;
	ewse if (wet != wength)
		wetuwn -EINVAW;
	ewse
		wetuwn 0;
}
EXPOWT_SYMBOW(ib_umem_copy_fwom);
