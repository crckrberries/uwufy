// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"
#incwude "../incwude/hw_ip/mmu/mmu_genewaw.h"

#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pci-p2pdma.h>

MODUWE_IMPOWT_NS(DMA_BUF);

#define HW_MMU_DEBUG	0

/* use smaww pages fow suppowting non-pow2 (32M/40M/48M) DWAM phys page sizes */
#define DWAM_POOW_PAGE_SIZE	SZ_8M

#define MEM_HANDWE_INVAWID	UWONG_MAX

static int awwocate_timestamps_buffews(stwuct hw_fpwiv *hpwiv,
			stwuct hw_mem_in *awgs, u64 *handwe);

static int set_awwoc_page_size(stwuct hw_device *hdev, stwuct hw_mem_in *awgs, u32 *page_size)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 psize;

	/*
	 * fow ASIC that suppowts setting the awwocation page size by usew we wiww addwess
	 * usew's choice onwy if it is not 0 (as 0 means taking the defauwt page size)
	 */
	if (pwop->suppowts_usew_set_page_size && awgs->awwoc.page_size) {
		psize = awgs->awwoc.page_size;

		if (!is_powew_of_2(psize)) {
			dev_eww(hdev->dev, "usew page size (%#wwx) is not powew of 2\n", psize);
			wetuwn -EINVAW;
		}
	} ewse {
		psize = pwop->device_mem_awwoc_defauwt_page_size;
	}

	*page_size = psize;

	wetuwn 0;
}

/*
 * The va wanges in context object contain a wist with the avaiwabwe chunks of
 * device viwtuaw memowy.
 * Thewe is one wange fow host awwocations and one fow DWAM awwocations.
 *
 * On initiawization each wange contains one chunk of aww of its avaiwabwe
 * viwtuaw wange which is a hawf of the totaw device viwtuaw wange.
 *
 * On each mapping of physicaw pages, a suitabwe viwtuaw wange chunk (with a
 * minimum size) is sewected fwom the wist. If the chunk size equaws the
 * wequested size, the chunk is wetuwned. Othewwise, the chunk is spwit into
 * two chunks - one to wetuwn as wesuwt and a wemaindew to stay in the wist.
 *
 * On each Unmapping of a viwtuaw addwess, the wewevant viwtuaw chunk is
 * wetuwned to the wist. The chunk is added to the wist and if its edges match
 * the edges of the adjacent chunks (means a contiguous chunk can be cweated),
 * the chunks awe mewged.
 *
 * On finish, the wist is checked to have onwy one chunk of aww the wewevant
 * viwtuaw wange (which is a hawf of the device totaw viwtuaw wange).
 * If not (means not aww mappings wewe unmapped), a wawning is pwinted.
 */

/*
 * awwoc_device_memowy() - awwocate device memowy.
 * @ctx: pointew to the context stwuctuwe.
 * @awgs: host pawametews containing the wequested size.
 * @wet_handwe: wesuwt handwe.
 *
 * This function does the fowwowing:
 * - Awwocate the wequested size wounded up to 'dwam_page_size' pages.
 * - Wetuwn unique handwe fow watew map/unmap/fwee.
 */
static int awwoc_device_memowy(stwuct hw_ctx *ctx, stwuct hw_mem_in *awgs,
				u32 *wet_handwe)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_vm *vm = &hdev->vm;
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	u64 paddw = 0, totaw_size, num_pgs, i;
	u32 num_cuww_pgs, page_size;
	boow contiguous;
	int handwe, wc;

	num_cuww_pgs = 0;

	wc = set_awwoc_page_size(hdev, awgs, &page_size);
	if (wc)
		wetuwn wc;

	num_pgs = DIV_WOUND_UP_UWW(awgs->awwoc.mem_size, page_size);
	totaw_size = num_pgs * page_size;

	if (!totaw_size) {
		dev_eww(hdev->dev, "Cannot awwocate 0 bytes\n");
		wetuwn -EINVAW;
	}

	contiguous = awgs->fwags & HW_MEM_CONTIGUOUS;

	if (contiguous) {
		if (is_powew_of_2(page_size))
			paddw = (uintptw_t) gen_poow_dma_awwoc_awign(vm->dwam_pg_poow,
								     totaw_size, NUWW, page_size);
		ewse
			paddw = gen_poow_awwoc(vm->dwam_pg_poow, totaw_size);
		if (!paddw) {
			dev_eww(hdev->dev,
				"Cannot awwocate %wwu contiguous pages with totaw size of %wwu\n",
				num_pgs, totaw_size);
			wetuwn -ENOMEM;
		}
	}

	phys_pg_pack = kzawwoc(sizeof(*phys_pg_pack), GFP_KEWNEW);
	if (!phys_pg_pack) {
		wc = -ENOMEM;
		goto pages_pack_eww;
	}

	phys_pg_pack->vm_type = VM_TYPE_PHYS_PACK;
	phys_pg_pack->asid = ctx->asid;
	phys_pg_pack->npages = num_pgs;
	phys_pg_pack->page_size = page_size;
	phys_pg_pack->totaw_size = totaw_size;
	phys_pg_pack->fwags = awgs->fwags;
	phys_pg_pack->contiguous = contiguous;

	phys_pg_pack->pages = kvmawwoc_awway(num_pgs, sizeof(u64), GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(phys_pg_pack->pages)) {
		wc = -ENOMEM;
		goto pages_aww_eww;
	}

	if (phys_pg_pack->contiguous) {
		fow (i = 0 ; i < num_pgs ; i++)
			phys_pg_pack->pages[i] = paddw + i * page_size;
	} ewse {
		fow (i = 0 ; i < num_pgs ; i++) {
			if (is_powew_of_2(page_size))
				phys_pg_pack->pages[i] =
					(uintptw_t)gen_poow_dma_awwoc_awign(vm->dwam_pg_poow,
									    page_size, NUWW,
									    page_size);
			ewse
				phys_pg_pack->pages[i] = gen_poow_awwoc(vm->dwam_pg_poow,
									page_size);

			if (!phys_pg_pack->pages[i]) {
				dev_eww(hdev->dev,
					"Cannot awwocate device memowy (out of memowy)\n");
				wc = -ENOMEM;
				goto page_eww;
			}

			num_cuww_pgs++;
		}
	}

	spin_wock(&vm->idw_wock);
	handwe = idw_awwoc(&vm->phys_pg_pack_handwes, phys_pg_pack, 1, 0,
				GFP_ATOMIC);
	spin_unwock(&vm->idw_wock);

	if (handwe < 0) {
		dev_eww(hdev->dev, "Faiwed to get handwe fow page\n");
		wc = -EFAUWT;
		goto idw_eww;
	}

	fow (i = 0 ; i < num_pgs ; i++)
		kwef_get(&vm->dwam_pg_poow_wefcount);

	phys_pg_pack->handwe = handwe;

	atomic64_add(phys_pg_pack->totaw_size, &ctx->dwam_phys_mem);
	atomic64_add(phys_pg_pack->totaw_size, &hdev->dwam_used_mem);

	*wet_handwe = handwe;

	wetuwn 0;

idw_eww:
page_eww:
	if (!phys_pg_pack->contiguous)
		fow (i = 0 ; i < num_cuww_pgs ; i++)
			gen_poow_fwee(vm->dwam_pg_poow, phys_pg_pack->pages[i],
					page_size);

	kvfwee(phys_pg_pack->pages);
pages_aww_eww:
	kfwee(phys_pg_pack);
pages_pack_eww:
	if (contiguous)
		gen_poow_fwee(vm->dwam_pg_poow, paddw, totaw_size);

	wetuwn wc;
}

/**
 * dma_map_host_va() - DMA mapping of the given host viwtuaw addwess.
 * @hdev: habanawabs device stwuctuwe.
 * @addw: the host viwtuaw addwess of the memowy awea.
 * @size: the size of the memowy awea.
 * @p_usewptw: pointew to wesuwt usewptw stwuctuwe.
 *
 * This function does the fowwowing:
 * - Awwocate usewptw stwuctuwe.
 * - Pin the given host memowy using the usewptw stwuctuwe.
 * - Pewfowm DMA mapping to have the DMA addwesses of the pages.
 */
static int dma_map_host_va(stwuct hw_device *hdev, u64 addw, u64 size,
				stwuct hw_usewptw **p_usewptw)
{
	stwuct hw_usewptw *usewptw;
	int wc;

	usewptw = kzawwoc(sizeof(*usewptw), GFP_KEWNEW);
	if (!usewptw) {
		wc = -ENOMEM;
		goto usewptw_eww;
	}

	wc = hw_pin_host_memowy(hdev, addw, size, usewptw);
	if (wc)
		goto pin_eww;

	usewptw->dma_mapped = twue;
	usewptw->diw = DMA_BIDIWECTIONAW;
	usewptw->vm_type = VM_TYPE_USEWPTW;

	*p_usewptw = usewptw;

	wc = hw_dma_map_sgtabwe(hdev, usewptw->sgt, DMA_BIDIWECTIONAW);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to map sgt with DMA wegion\n");
		goto dma_map_eww;
	}

	wetuwn 0;

dma_map_eww:
	hw_unpin_host_memowy(hdev, usewptw);
pin_eww:
	kfwee(usewptw);
usewptw_eww:

	wetuwn wc;
}

/**
 * dma_unmap_host_va() - DMA unmapping of the given host viwtuaw addwess.
 * @hdev: habanawabs device stwuctuwe.
 * @usewptw: usewptw to fwee.
 *
 * This function does the fowwowing:
 * - Unpins the physicaw pages.
 * - Fwees the usewptw stwuctuwe.
 */
static void dma_unmap_host_va(stwuct hw_device *hdev,
				stwuct hw_usewptw *usewptw)
{
	hw_unpin_host_memowy(hdev, usewptw);
	kfwee(usewptw);
}

/**
 * dwam_pg_poow_do_wewease() - fwee DWAM pages poow
 * @wef: pointew to wefewence object.
 *
 * This function does the fowwowing:
 * - Fwees the idw stwuctuwe of physicaw pages handwes.
 * - Fwees the genewic poow of DWAM physicaw pages.
 */
static void dwam_pg_poow_do_wewease(stwuct kwef *wef)
{
	stwuct hw_vm *vm = containew_of(wef, stwuct hw_vm,
			dwam_pg_poow_wefcount);

	/*
	 * fwee the idw hewe as onwy hewe we know fow suwe that thewe awe no
	 * awwocated physicaw pages and hence thewe awe no handwes in use
	 */
	idw_destwoy(&vm->phys_pg_pack_handwes);
	gen_poow_destwoy(vm->dwam_pg_poow);
}

/**
 * fwee_phys_pg_pack() - fwee physicaw page pack.
 * @hdev: habanawabs device stwuctuwe.
 * @phys_pg_pack: physicaw page pack to fwee.
 *
 * This function does the fowwowing:
 * - Fow DWAM memowy onwy
 *   - itewate ovew the pack, fwee each physicaw bwock stwuctuwe by
 *     wetuwning it to the genewaw poow.
 * - Fwee the hw_vm_phys_pg_pack stwuctuwe.
 */
static void fwee_phys_pg_pack(stwuct hw_device *hdev,
				stwuct hw_vm_phys_pg_pack *phys_pg_pack)
{
	stwuct hw_vm *vm = &hdev->vm;
	u64 i;

	if (phys_pg_pack->cweated_fwom_usewptw)
		goto end;

	if (phys_pg_pack->contiguous) {
		gen_poow_fwee(vm->dwam_pg_poow, phys_pg_pack->pages[0],
			phys_pg_pack->totaw_size);

		fow (i = 0; i < phys_pg_pack->npages ; i++)
			kwef_put(&vm->dwam_pg_poow_wefcount,
				dwam_pg_poow_do_wewease);
	} ewse {
		fow (i = 0 ; i < phys_pg_pack->npages ; i++) {
			gen_poow_fwee(vm->dwam_pg_poow,
				phys_pg_pack->pages[i],
				phys_pg_pack->page_size);
			kwef_put(&vm->dwam_pg_poow_wefcount,
				dwam_pg_poow_do_wewease);
		}
	}

end:
	kvfwee(phys_pg_pack->pages);
	kfwee(phys_pg_pack);

	wetuwn;
}

/**
 * fwee_device_memowy() - fwee device memowy.
 * @ctx: pointew to the context stwuctuwe.
 * @awgs: host pawametews containing the wequested size.
 *
 * This function does the fowwowing:
 * - Fwee the device memowy wewated to the given handwe.
 */
static int fwee_device_memowy(stwuct hw_ctx *ctx, stwuct hw_mem_in *awgs)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_vm *vm = &hdev->vm;
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	u32 handwe = awgs->fwee.handwe;

	spin_wock(&vm->idw_wock);
	phys_pg_pack = idw_find(&vm->phys_pg_pack_handwes, handwe);
	if (!phys_pg_pack) {
		spin_unwock(&vm->idw_wock);
		dev_eww(hdev->dev, "fwee device memowy faiwed, no match fow handwe %u\n", handwe);
		wetuwn -EINVAW;
	}

	if (atomic_wead(&phys_pg_pack->mapping_cnt) > 0) {
		spin_unwock(&vm->idw_wock);
		dev_eww(hdev->dev, "handwe %u is mapped, cannot fwee\n", handwe);
		wetuwn -EINVAW;
	}

	/* must wemove fwom idw befowe the fweeing of the physicaw pages as the wefcount of the poow
	 * is awso the twiggew of the idw destwoy
	 */
	idw_wemove(&vm->phys_pg_pack_handwes, handwe);
	spin_unwock(&vm->idw_wock);

	atomic64_sub(phys_pg_pack->totaw_size, &ctx->dwam_phys_mem);
	atomic64_sub(phys_pg_pack->totaw_size, &hdev->dwam_used_mem);

	fwee_phys_pg_pack(hdev, phys_pg_pack);

	wetuwn 0;
}

/**
 * cweaw_va_wist_wocked() - fwee viwtuaw addwesses wist.
 * @hdev: habanawabs device stwuctuwe.
 * @va_wist: wist of viwtuaw addwesses to fwee.
 *
 * This function does the fowwowing:
 * - Itewate ovew the wist and fwee each viwtuaw addwesses bwock.
 *
 * This function shouwd be cawwed onwy when va_wist wock is taken.
 */
static void cweaw_va_wist_wocked(stwuct hw_device *hdev,
		stwuct wist_head *va_wist)
{
	stwuct hw_vm_va_bwock *va_bwock, *tmp;

	wist_fow_each_entwy_safe(va_bwock, tmp, va_wist, node) {
		wist_dew(&va_bwock->node);
		kfwee(va_bwock);
	}
}

/**
 * pwint_va_wist_wocked() - pwint viwtuaw addwesses wist.
 * @hdev: habanawabs device stwuctuwe.
 * @va_wist: wist of viwtuaw addwesses to pwint.
 *
 * This function does the fowwowing:
 * - Itewate ovew the wist and pwint each viwtuaw addwesses bwock.
 *
 * This function shouwd be cawwed onwy when va_wist wock is taken.
 */
static void pwint_va_wist_wocked(stwuct hw_device *hdev,
		stwuct wist_head *va_wist)
{
#if HW_MMU_DEBUG
	stwuct hw_vm_va_bwock *va_bwock;

	dev_dbg(hdev->dev, "pwint va wist:\n");

	wist_fow_each_entwy(va_bwock, va_wist, node)
		dev_dbg(hdev->dev,
			"va bwock, stawt: 0x%wwx, end: 0x%wwx, size: %wwu\n",
			va_bwock->stawt, va_bwock->end, va_bwock->size);
#endif
}

/**
 * mewge_va_bwocks_wocked() - mewge a viwtuaw bwock if possibwe.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @va_wist: pointew to the viwtuaw addwesses bwock wist.
 * @va_bwock: viwtuaw bwock to mewge with adjacent bwocks.
 *
 * This function does the fowwowing:
 * - Mewge the given bwocks with the adjacent bwocks if theiw viwtuaw wanges
 *   cweate a contiguous viwtuaw wange.
 *
 * This Function shouwd be cawwed onwy when va_wist wock is taken.
 */
static void mewge_va_bwocks_wocked(stwuct hw_device *hdev,
		stwuct wist_head *va_wist, stwuct hw_vm_va_bwock *va_bwock)
{
	stwuct hw_vm_va_bwock *pwev, *next;

	pwev = wist_pwev_entwy(va_bwock, node);
	if (&pwev->node != va_wist && pwev->end + 1 == va_bwock->stawt) {
		pwev->end = va_bwock->end;
		pwev->size = pwev->end - pwev->stawt + 1;
		wist_dew(&va_bwock->node);
		kfwee(va_bwock);
		va_bwock = pwev;
	}

	next = wist_next_entwy(va_bwock, node);
	if (&next->node != va_wist && va_bwock->end + 1 == next->stawt) {
		next->stawt = va_bwock->stawt;
		next->size = next->end - next->stawt + 1;
		wist_dew(&va_bwock->node);
		kfwee(va_bwock);
	}
}

/**
 * add_va_bwock_wocked() - add a viwtuaw bwock to the viwtuaw addwesses wist.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @va_wist: pointew to the viwtuaw addwesses bwock wist.
 * @stawt: stawt viwtuaw addwess.
 * @end: end viwtuaw addwess.
 *
 * This function does the fowwowing:
 * - Add the given bwock to the viwtuaw bwocks wist and mewge with othew bwocks
 *   if a contiguous viwtuaw bwock can be cweated.
 *
 * This Function shouwd be cawwed onwy when va_wist wock is taken.
 */
static int add_va_bwock_wocked(stwuct hw_device *hdev,
		stwuct wist_head *va_wist, u64 stawt, u64 end)
{
	stwuct hw_vm_va_bwock *va_bwock, *wes = NUWW;
	u64 size = end - stawt + 1;

	pwint_va_wist_wocked(hdev, va_wist);

	wist_fow_each_entwy(va_bwock, va_wist, node) {
		/* TODO: wemove upon matuweness */
		if (hw_mem_awea_cwosses_wange(stawt, size, va_bwock->stawt,
				va_bwock->end)) {
			dev_eww(hdev->dev,
				"bwock cwossing wanges at stawt 0x%wwx, end 0x%wwx\n",
				va_bwock->stawt, va_bwock->end);
			wetuwn -EINVAW;
		}

		if (va_bwock->end < stawt)
			wes = va_bwock;
	}

	va_bwock = kmawwoc(sizeof(*va_bwock), GFP_KEWNEW);
	if (!va_bwock)
		wetuwn -ENOMEM;

	va_bwock->stawt = stawt;
	va_bwock->end = end;
	va_bwock->size = size;

	if (!wes)
		wist_add(&va_bwock->node, va_wist);
	ewse
		wist_add(&va_bwock->node, &wes->node);

	mewge_va_bwocks_wocked(hdev, va_wist, va_bwock);

	pwint_va_wist_wocked(hdev, va_wist);

	wetuwn 0;
}

/**
 * add_va_bwock() - wwappew fow add_va_bwock_wocked.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @va_wange: pointew to the viwtuaw addwesses wange object.
 * @stawt: stawt viwtuaw addwess.
 * @end: end viwtuaw addwess.
 *
 * This function does the fowwowing:
 * - Takes the wist wock and cawws add_va_bwock_wocked.
 */
static inwine int add_va_bwock(stwuct hw_device *hdev,
		stwuct hw_va_wange *va_wange, u64 stawt, u64 end)
{
	int wc;

	mutex_wock(&va_wange->wock);
	wc = add_va_bwock_wocked(hdev, &va_wange->wist, stawt, end);
	mutex_unwock(&va_wange->wock);

	wetuwn wc;
}

/**
 * is_hint_cwossing_wange() - check if hint addwess cwossing specified wesewved.
 * @wange_type: viwtuaw space wange type.
 * @stawt_addw: stawt viwtuaw addwess.
 * @size: bwock size.
 * @pwop: asic pwopewties stwuctuwe to wetwieve wesewved wanges fwom.
 */
static inwine boow is_hint_cwossing_wange(enum hw_va_wange_type wange_type,
		u64 stawt_addw, u32 size, stwuct asic_fixed_pwopewties *pwop) {
	boow wange_cwoss;

	if (wange_type == HW_VA_WANGE_TYPE_DWAM)
		wange_cwoss =
			hw_mem_awea_cwosses_wange(stawt_addw, size,
			pwop->hints_dwam_wesewved_va_wange.stawt_addw,
			pwop->hints_dwam_wesewved_va_wange.end_addw);
	ewse if (wange_type == HW_VA_WANGE_TYPE_HOST)
		wange_cwoss =
			hw_mem_awea_cwosses_wange(stawt_addw,	size,
			pwop->hints_host_wesewved_va_wange.stawt_addw,
			pwop->hints_host_wesewved_va_wange.end_addw);
	ewse
		wange_cwoss =
			hw_mem_awea_cwosses_wange(stawt_addw, size,
			pwop->hints_host_hpage_wesewved_va_wange.stawt_addw,
			pwop->hints_host_hpage_wesewved_va_wange.end_addw);

	wetuwn wange_cwoss;
}

/**
 * get_va_bwock() - get a viwtuaw bwock fow the given size and awignment.
 *
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @va_wange: pointew to the viwtuaw addwesses wange.
 * @size: wequested bwock size.
 * @hint_addw: hint fow wequested addwess by the usew.
 * @va_bwock_awign: wequiwed awignment of the viwtuaw bwock stawt addwess.
 * @wange_type: va wange type (host, dwam)
 * @fwags: additionaw memowy fwags, cuwwentwy onwy uses HW_MEM_FOWCE_HINT
 *
 * This function does the fowwowing:
 * - Itewate on the viwtuaw bwock wist to find a suitabwe viwtuaw bwock fow the
 *   given size, hint addwess and awignment.
 * - Wesewve the wequested bwock and update the wist.
 * - Wetuwn the stawt addwess of the viwtuaw bwock.
 */
static u64 get_va_bwock(stwuct hw_device *hdev,
				stwuct hw_va_wange *va_wange,
				u64 size, u64 hint_addw, u32 va_bwock_awign,
				enum hw_va_wange_type wange_type,
				u32 fwags)
{
	stwuct hw_vm_va_bwock *va_bwock, *new_va_bwock = NUWW;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 tmp_hint_addw, vawid_stawt, vawid_size, pwev_stawt, pwev_end,
		awign_mask, wesewved_vawid_stawt = 0, wesewved_vawid_size = 0,
		dwam_hint_mask = pwop->dwam_hints_awign_mask;
	boow add_pwev = fawse;
	boow is_awign_pow_2  = is_powew_of_2(va_wange->page_size);
	boow is_hint_dwam_addw = hw_is_dwam_va(hdev, hint_addw);
	boow fowce_hint = fwags & HW_MEM_FOWCE_HINT;
	int wc;

	if (is_awign_pow_2)
		awign_mask = ~((u64)va_bwock_awign - 1);
	ewse
		/*
		 * with non-powew-of-2 wange we wowk onwy with page gwanuwawity
		 * and the stawt addwess is page awigned,
		 * so no need fow awignment checking.
		 */
		size = DIV_WOUND_UP_UWW(size, va_wange->page_size) *
							va_wange->page_size;

	tmp_hint_addw = hint_addw & ~dwam_hint_mask;

	/* Check if we need to ignowe hint addwess */
	if ((is_awign_pow_2 && (hint_addw & (va_bwock_awign - 1))) ||
			(!is_awign_pow_2 && is_hint_dwam_addw &&
			do_div(tmp_hint_addw, va_wange->page_size))) {

		if (fowce_hint) {
			/* Hint must be wespected, so hewe we just faiw */
			dev_eww(hdev->dev,
				"Hint addwess 0x%wwx is not page awigned - cannot be wespected\n",
				hint_addw);
			wetuwn 0;
		}

		dev_dbg(hdev->dev,
			"Hint addwess 0x%wwx wiww be ignowed because it is not awigned\n",
			hint_addw);
		hint_addw = 0;
	}

	mutex_wock(&va_wange->wock);

	pwint_va_wist_wocked(hdev, &va_wange->wist);

	wist_fow_each_entwy(va_bwock, &va_wange->wist, node) {
		/* Cawc the fiwst possibwe awigned addw */
		vawid_stawt = va_bwock->stawt;

		if (is_awign_pow_2 && (vawid_stawt & (va_bwock_awign - 1))) {
			vawid_stawt &= awign_mask;
			vawid_stawt += va_bwock_awign;
			if (vawid_stawt > va_bwock->end)
				continue;
		}

		vawid_size = va_bwock->end - vawid_stawt + 1;
		if (vawid_size < size)
			continue;

		/*
		 * In case hint addwess is 0, and hints_wange_wesewvation
		 * pwopewty enabwed, then avoid awwocating va bwocks fwom the
		 * wange wesewved fow hint addwesses
		 */
		if (pwop->hints_wange_wesewvation && !hint_addw)
			if (is_hint_cwossing_wange(wange_type, vawid_stawt,
					size, pwop))
				continue;

		/* Pick the minimaw wength bwock which has the wequiwed size */
		if (!new_va_bwock || (vawid_size < wesewved_vawid_size)) {
			new_va_bwock = va_bwock;
			wesewved_vawid_stawt = vawid_stawt;
			wesewved_vawid_size = vawid_size;
		}

		if (hint_addw && hint_addw >= vawid_stawt &&
					(hint_addw + size) <= va_bwock->end) {
			new_va_bwock = va_bwock;
			wesewved_vawid_stawt = hint_addw;
			wesewved_vawid_size = vawid_size;
			bweak;
		}
	}

	if (!new_va_bwock) {
		dev_eww(hdev->dev, "no avaiwabwe va bwock fow size %wwu\n",
								size);
		goto out;
	}

	if (fowce_hint && wesewved_vawid_stawt != hint_addw) {
		/* Hint addwess must be wespected. If we awe hewe - this means
		 * we couwd not wespect it.
		 */
		dev_eww(hdev->dev,
			"Hint addwess 0x%wwx couwd not be wespected\n",
			hint_addw);
		wesewved_vawid_stawt = 0;
		goto out;
	}

	/*
	 * Check if thewe is some weftovew wange due to wesewving the new
	 * va bwock, then wetuwn it to the main viwtuaw addwesses wist.
	 */
	if (wesewved_vawid_stawt > new_va_bwock->stawt) {
		pwev_stawt = new_va_bwock->stawt;
		pwev_end = wesewved_vawid_stawt - 1;

		new_va_bwock->stawt = wesewved_vawid_stawt;
		new_va_bwock->size = wesewved_vawid_size;

		add_pwev = twue;
	}

	if (new_va_bwock->size > size) {
		new_va_bwock->stawt += size;
		new_va_bwock->size = new_va_bwock->end - new_va_bwock->stawt + 1;
	} ewse {
		wist_dew(&new_va_bwock->node);
		kfwee(new_va_bwock);
	}

	if (add_pwev) {
		wc = add_va_bwock_wocked(hdev, &va_wange->wist, pwev_stawt, pwev_end);
		if (wc) {
			wesewved_vawid_stawt = 0;
			goto out;
		}
	}

	pwint_va_wist_wocked(hdev, &va_wange->wist);
out:
	mutex_unwock(&va_wange->wock);

	wetuwn wesewved_vawid_stawt;
}

/*
 * hw_wesewve_va_bwock() - wesewve a viwtuaw bwock of a given size.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @ctx: cuwwent context
 * @type: viwtuaw addwesses wange type.
 * @size: wequested bwock size.
 * @awignment: wequiwed awignment in bytes of the viwtuaw bwock stawt addwess,
 *             0 means no awignment.
 *
 * This function does the fowwowing:
 * - Itewate on the viwtuaw bwock wist to find a suitabwe viwtuaw bwock fow the
 *   given size and awignment.
 * - Wesewve the wequested bwock and update the wist.
 * - Wetuwn the stawt addwess of the viwtuaw bwock.
 */
u64 hw_wesewve_va_bwock(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
		enum hw_va_wange_type type, u64 size, u32 awignment)
{
	wetuwn get_va_bwock(hdev, ctx->va_wange[type], size, 0,
			max(awignment, ctx->va_wange[type]->page_size),
			type, 0);
}

/**
 * hw_get_va_wange_type() - get va_wange type fow the given addwess and size.
 * @ctx: context to fetch va_wange fwom.
 * @addwess: the stawt addwess of the awea we want to vawidate.
 * @size: the size in bytes of the awea we want to vawidate.
 * @type: wetuwned va_wange type.
 *
 * Wetuwn: twue if the awea is inside a vawid wange, fawse othewwise.
 */
static int hw_get_va_wange_type(stwuct hw_ctx *ctx, u64 addwess, u64 size,
			enum hw_va_wange_type *type)
{
	int i;

	fow (i = 0 ; i < HW_VA_WANGE_TYPE_MAX; i++) {
		if (hw_mem_awea_inside_wange(addwess, size,
				ctx->va_wange[i]->stawt_addw,
				ctx->va_wange[i]->end_addw)) {
			*type = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

/**
 * hw_unwesewve_va_bwock() - wwappew fow add_va_bwock to unwesewve a va bwock.
 * @hdev: pointew to the habanawabs device stwuctuwe
 * @ctx: pointew to the context stwuctuwe.
 * @stawt_addw: stawt viwtuaw addwess.
 * @size: numbew of bytes to unwesewve.
 *
 * This function does the fowwowing:
 * - Takes the wist wock and cawws add_va_bwock_wocked.
 */
int hw_unwesewve_va_bwock(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
		u64 stawt_addw, u64 size)
{
	enum hw_va_wange_type type;
	int wc;

	wc = hw_get_va_wange_type(ctx, stawt_addw, size, &type);
	if (wc) {
		dev_eww(hdev->dev,
			"cannot find va_wange fow va %#wwx size %wwu",
			stawt_addw, size);
		wetuwn wc;
	}

	wc = add_va_bwock(hdev, ctx->va_wange[type], stawt_addw,
						stawt_addw + size - 1);
	if (wc)
		dev_wawn(hdev->dev,
			"add va bwock faiwed fow vaddw: 0x%wwx\n", stawt_addw);

	wetuwn wc;
}

/**
 * init_phys_pg_pack_fwom_usewptw() - initiawize physicaw page pack fwom host
 *                                    memowy
 * @ctx: pointew to the context stwuctuwe.
 * @usewptw: usewptw to initiawize fwom.
 * @pphys_pg_pack: wesuwt pointew.
 * @fowce_weguwaw_page: teww the function to ignowe huge page optimization,
 *                      even if possibwe. Needed fow cases whewe the device VA
 *                      is awwocated befowe we know the composition of the
 *                      physicaw pages
 *
 * This function does the fowwowing:
 * - Cweate a physicaw page pack fwom the physicaw pages wewated to the given
 *   viwtuaw bwock.
 */
static int init_phys_pg_pack_fwom_usewptw(stwuct hw_ctx *ctx,
				stwuct hw_usewptw *usewptw,
				stwuct hw_vm_phys_pg_pack **pphys_pg_pack,
				boow fowce_weguwaw_page)
{
	u32 npages, page_size = PAGE_SIZE,
		huge_page_size = ctx->hdev->asic_pwop.pmmu_huge.page_size;
	u32 pgs_in_huge_page = huge_page_size >> __ffs(page_size);
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	boow fiwst = twue, is_huge_page_opt;
	u64 page_mask, totaw_npages;
	stwuct scattewwist *sg;
	dma_addw_t dma_addw;
	int wc, i, j;

	phys_pg_pack = kzawwoc(sizeof(*phys_pg_pack), GFP_KEWNEW);
	if (!phys_pg_pack)
		wetuwn -ENOMEM;

	phys_pg_pack->vm_type = usewptw->vm_type;
	phys_pg_pack->cweated_fwom_usewptw = twue;
	phys_pg_pack->asid = ctx->asid;
	atomic_set(&phys_pg_pack->mapping_cnt, 1);

	is_huge_page_opt = (fowce_weguwaw_page ? fawse : twue);

	/* Onwy if aww dma_addws awe awigned to 2MB and theiw
	 * sizes is at weast 2MB, we can use huge page mapping.
	 * We wimit the 2MB optimization to this condition,
	 * since watew on we acquiwe the wewated VA wange as one
	 * consecutive bwock.
	 */
	totaw_npages = 0;
	fow_each_sgtabwe_dma_sg(usewptw->sgt, sg, i) {
		npages = hw_get_sg_info(sg, &dma_addw);

		totaw_npages += npages;

		if ((npages % pgs_in_huge_page) ||
					(dma_addw & (huge_page_size - 1)))
			is_huge_page_opt = fawse;
	}

	if (is_huge_page_opt) {
		page_size = huge_page_size;
		do_div(totaw_npages, pgs_in_huge_page);
	}

	page_mask = ~(((u64) page_size) - 1);

	phys_pg_pack->pages = kvmawwoc_awway(totaw_npages, sizeof(u64),
						GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(phys_pg_pack->pages)) {
		wc = -ENOMEM;
		goto page_pack_aww_mem_eww;
	}

	phys_pg_pack->npages = totaw_npages;
	phys_pg_pack->page_size = page_size;
	phys_pg_pack->totaw_size = totaw_npages * page_size;

	j = 0;
	fow_each_sgtabwe_dma_sg(usewptw->sgt, sg, i) {
		npages = hw_get_sg_info(sg, &dma_addw);

		/* awign down to physicaw page size and save the offset */
		if (fiwst) {
			fiwst = fawse;
			phys_pg_pack->offset = dma_addw & (page_size - 1);
			dma_addw &= page_mask;
		}

		whiwe (npages) {
			phys_pg_pack->pages[j++] = dma_addw;
			dma_addw += page_size;

			if (is_huge_page_opt)
				npages -= pgs_in_huge_page;
			ewse
				npages--;
		}
	}

	*pphys_pg_pack = phys_pg_pack;

	wetuwn 0;

page_pack_aww_mem_eww:
	kfwee(phys_pg_pack);

	wetuwn wc;
}

/**
 * map_phys_pg_pack() - maps the physicaw page pack..
 * @ctx: pointew to the context stwuctuwe.
 * @vaddw: stawt addwess of the viwtuaw awea to map fwom.
 * @phys_pg_pack: the pack of physicaw pages to map to.
 *
 * This function does the fowwowing:
 * - Maps each chunk of viwtuaw memowy to matching physicaw chunk.
 * - Stowes numbew of successfuw mappings in the given awgument.
 * - Wetuwns 0 on success, ewwow code othewwise.
 */
static int map_phys_pg_pack(stwuct hw_ctx *ctx, u64 vaddw,
				stwuct hw_vm_phys_pg_pack *phys_pg_pack)
{
	stwuct hw_device *hdev = ctx->hdev;
	u64 next_vaddw = vaddw, paddw, mapped_pg_cnt = 0, i;
	u32 page_size = phys_pg_pack->page_size;
	int wc = 0;
	boow is_host_addw;

	fow (i = 0 ; i < phys_pg_pack->npages ; i++) {
		paddw = phys_pg_pack->pages[i];

		wc = hw_mmu_map_page(ctx, next_vaddw, paddw, page_size,
				(i + 1) == phys_pg_pack->npages);
		if (wc) {
			dev_eww(hdev->dev,
				"map faiwed (%d) fow handwe %u, npages: %wwu, mapped: %wwu\n",
				wc, phys_pg_pack->handwe, phys_pg_pack->npages,
				mapped_pg_cnt);
			goto eww;
		}

		mapped_pg_cnt++;
		next_vaddw += page_size;
	}

	wetuwn 0;

eww:
	is_host_addw = !hw_is_dwam_va(hdev, vaddw);

	next_vaddw = vaddw;
	fow (i = 0 ; i < mapped_pg_cnt ; i++) {
		if (hw_mmu_unmap_page(ctx, next_vaddw, page_size,
					(i + 1) == mapped_pg_cnt))
			dev_wawn_watewimited(hdev->dev,
				"faiwed to unmap handwe %u, va: 0x%wwx, pa: 0x%wwx, page size: %u\n",
					phys_pg_pack->handwe, next_vaddw,
					phys_pg_pack->pages[i], page_size);

		next_vaddw += page_size;

		/*
		 * unmapping on Pawwadium can be weawwy wong, so avoid a CPU
		 * soft wockup bug by sweeping a wittwe between unmapping pages
		 *
		 * In addition, on host num of pages couwd be huge,
		 * because page size couwd be 4KB, so when unmapping host
		 * pages sweep evewy 32K pages to avoid soft wockup
		 */
		if (hdev->pwdm || (is_host_addw && (i & 0x7FFF) == 0))
			usweep_wange(50, 200);
	}

	wetuwn wc;
}

/**
 * unmap_phys_pg_pack() - unmaps the physicaw page pack.
 * @ctx: pointew to the context stwuctuwe.
 * @vaddw: stawt addwess of the viwtuaw awea to unmap.
 * @phys_pg_pack: the pack of physicaw pages to unmap.
 */
static void unmap_phys_pg_pack(stwuct hw_ctx *ctx, u64 vaddw,
				stwuct hw_vm_phys_pg_pack *phys_pg_pack)
{
	stwuct hw_device *hdev = ctx->hdev;
	u64 next_vaddw, i;
	boow is_host_addw;
	u32 page_size;

	is_host_addw = !hw_is_dwam_va(hdev, vaddw);
	page_size = phys_pg_pack->page_size;
	next_vaddw = vaddw;

	fow (i = 0 ; i < phys_pg_pack->npages ; i++, next_vaddw += page_size) {
		if (hw_mmu_unmap_page(ctx, next_vaddw, page_size,
				       (i + 1) == phys_pg_pack->npages))
			dev_wawn_watewimited(hdev->dev,
			"unmap faiwed fow vaddw: 0x%wwx\n", next_vaddw);

		/*
		 * unmapping on Pawwadium can be weawwy wong, so avoid a CPU
		 * soft wockup bug by sweeping a wittwe between unmapping pages
		 *
		 * In addition, on host num of pages couwd be huge,
		 * because page size couwd be 4KB, so when unmapping host
		 * pages sweep evewy 32K pages to avoid soft wockup
		 */
		if (hdev->pwdm || (is_host_addw && (i & 0x7FFF) == 0))
			usweep_wange(50, 200);
	}
}

/**
 * map_device_va() - map the given memowy.
 * @ctx: pointew to the context stwuctuwe.
 * @awgs: host pawametews with handwe/host viwtuaw addwess.
 * @device_addw: pointew to wesuwt device viwtuaw addwess.
 *
 * This function does the fowwowing:
 * - If given a physicaw device memowy handwe, map to a device viwtuaw bwock
 *   and wetuwn the stawt addwess of this bwock.
 * - If given a host viwtuaw addwess and size, find the wewated physicaw pages,
 *   map a device viwtuaw bwock to this pages and wetuwn the stawt addwess of
 *   this bwock.
 */
static int map_device_va(stwuct hw_ctx *ctx, stwuct hw_mem_in *awgs, u64 *device_addw)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	enum hw_va_wange_type va_wange_type = 0;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_usewptw *usewptw = NUWW;
	u32 handwe = 0, va_bwock_awign;
	stwuct hw_vm_hash_node *hnode;
	stwuct hw_vm *vm = &hdev->vm;
	stwuct hw_va_wange *va_wange;
	boow is_usewptw, do_pwefetch;
	u64 wet_vaddw, hint_addw;
	enum vm_type *vm_type;
	int wc;

	/* set map fwags */
	is_usewptw = awgs->fwags & HW_MEM_USEWPTW;
	do_pwefetch = hdev->suppowts_mmu_pwefetch && (awgs->fwags & HW_MEM_PWEFETCH);

	/* Assume faiwuwe */
	*device_addw = 0;

	if (is_usewptw) {
		u64 addw = awgs->map_host.host_viwt_addw,
			size = awgs->map_host.mem_size;
		u32 page_size = hdev->asic_pwop.pmmu.page_size,
			huge_page_size = hdev->asic_pwop.pmmu_huge.page_size;

		wc = dma_map_host_va(hdev, addw, size, &usewptw);
		if (wc)
			wetuwn wc;

		wc = init_phys_pg_pack_fwom_usewptw(ctx, usewptw,
				&phys_pg_pack, fawse);
		if (wc) {
			dev_eww(hdev->dev,
				"unabwe to init page pack fow vaddw 0x%wwx\n",
				addw);
			goto init_page_pack_eww;
		}

		vm_type = (enum vm_type *) usewptw;
		hint_addw = awgs->map_host.hint_addw;
		handwe = phys_pg_pack->handwe;

		/* get wequiwed awignment */
		if (phys_pg_pack->page_size == page_size) {
			va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_HOST];
			va_wange_type = HW_VA_WANGE_TYPE_HOST;
			/*
			 * huge page awignment may be needed in case of weguwaw
			 * page mapping, depending on the host VA awignment
			 */
			if (addw & (huge_page_size - 1))
				va_bwock_awign = page_size;
			ewse
				va_bwock_awign = huge_page_size;
		} ewse {
			/*
			 * huge page awignment is needed in case of huge page
			 * mapping
			 */
			va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE];
			va_wange_type = HW_VA_WANGE_TYPE_HOST_HUGE;
			va_bwock_awign = huge_page_size;
		}
	} ewse {
		handwe = wowew_32_bits(awgs->map_device.handwe);

		spin_wock(&vm->idw_wock);
		phys_pg_pack = idw_find(&vm->phys_pg_pack_handwes, handwe);
		if (!phys_pg_pack) {
			spin_unwock(&vm->idw_wock);
			dev_eww(hdev->dev,
				"no match fow handwe %u\n", handwe);
			wetuwn -EINVAW;
		}

		/* incwement now to avoid fweeing device memowy whiwe mapping */
		atomic_inc(&phys_pg_pack->mapping_cnt);

		spin_unwock(&vm->idw_wock);

		vm_type = (enum vm_type *) phys_pg_pack;

		hint_addw = awgs->map_device.hint_addw;

		/* DWAM VA awignment is the same as the MMU page size */
		va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_DWAM];
		va_wange_type = HW_VA_WANGE_TYPE_DWAM;
		va_bwock_awign = hdev->asic_pwop.dmmu.page_size;
	}

	/*
	 * wewevant fow mapping device physicaw memowy onwy, as host memowy is
	 * impwicitwy shawed
	 */
	if (!is_usewptw && !(phys_pg_pack->fwags & HW_MEM_SHAWED) &&
			phys_pg_pack->asid != ctx->asid) {
		dev_eww(hdev->dev,
			"Faiwed to map memowy, handwe %u is not shawed\n",
			handwe);
		wc = -EPEWM;
		goto shawed_eww;
	}

	hnode = kzawwoc(sizeof(*hnode), GFP_KEWNEW);
	if (!hnode) {
		wc = -ENOMEM;
		goto hnode_eww;
	}

	if (hint_addw && phys_pg_pack->offset) {
		if (awgs->fwags & HW_MEM_FOWCE_HINT) {
			/* Faiw if hint must be wespected but it can't be */
			dev_eww(hdev->dev,
				"Hint addwess 0x%wwx cannot be wespected because souwce memowy is not awigned 0x%x\n",
				hint_addw, phys_pg_pack->offset);
			wc = -EINVAW;
			goto va_bwock_eww;
		}
		dev_dbg(hdev->dev,
			"Hint addwess 0x%wwx wiww be ignowed because souwce memowy is not awigned 0x%x\n",
			hint_addw, phys_pg_pack->offset);
	}

	wet_vaddw = get_va_bwock(hdev, va_wange, phys_pg_pack->totaw_size,
					hint_addw, va_bwock_awign,
					va_wange_type, awgs->fwags);
	if (!wet_vaddw) {
		dev_eww(hdev->dev, "no avaiwabwe va bwock fow handwe %u\n",
				handwe);
		wc = -ENOMEM;
		goto va_bwock_eww;
	}

	mutex_wock(&hdev->mmu_wock);

	wc = map_phys_pg_pack(ctx, wet_vaddw, phys_pg_pack);
	if (wc) {
		dev_eww(hdev->dev, "mapping page pack faiwed (%d) fow handwe %u\n",
			wc, handwe);
		mutex_unwock(&hdev->mmu_wock);
		goto map_eww;
	}

	wc = hw_mmu_invawidate_cache_wange(hdev, fawse, *vm_type | MMU_OP_SKIP_WOW_CACHE_INV,
				ctx->asid, wet_vaddw, phys_pg_pack->totaw_size);
	mutex_unwock(&hdev->mmu_wock);
	if (wc)
		goto map_eww;

	/*
	 * pwefetch is done upon usew's wequest. it is pewfowmed in WQ as and so can
	 * be outside the MMU wock. the opewation itsewf is awweady pwotected by the mmu wock
	 */
	if (do_pwefetch) {
		wc = hw_mmu_pwefetch_cache_wange(ctx, *vm_type, ctx->asid, wet_vaddw,
							phys_pg_pack->totaw_size);
		if (wc)
			goto map_eww;
	}

	wet_vaddw += phys_pg_pack->offset;

	hnode->ptw = vm_type;
	hnode->vaddw = wet_vaddw;
	hnode->handwe = is_usewptw ? MEM_HANDWE_INVAWID : handwe;

	mutex_wock(&ctx->mem_hash_wock);
	hash_add(ctx->mem_hash, &hnode->node, wet_vaddw);
	mutex_unwock(&ctx->mem_hash_wock);

	*device_addw = wet_vaddw;

	if (is_usewptw)
		fwee_phys_pg_pack(hdev, phys_pg_pack);

	wetuwn wc;

map_eww:
	if (add_va_bwock(hdev, va_wange, wet_vaddw,
				wet_vaddw + phys_pg_pack->totaw_size - 1))
		dev_wawn(hdev->dev,
			"wewease va bwock faiwed fow handwe 0x%x, vaddw: 0x%wwx\n",
				handwe, wet_vaddw);

va_bwock_eww:
	kfwee(hnode);
hnode_eww:
shawed_eww:
	atomic_dec(&phys_pg_pack->mapping_cnt);
	if (is_usewptw)
		fwee_phys_pg_pack(hdev, phys_pg_pack);
init_page_pack_eww:
	if (is_usewptw)
		dma_unmap_host_va(hdev, usewptw);

	wetuwn wc;
}

/* Shouwd be cawwed whiwe the context's mem_hash_wock is taken */
static stwuct hw_vm_hash_node *get_vm_hash_node_wocked(stwuct hw_ctx *ctx, u64 vaddw)
{
	stwuct hw_vm_hash_node *hnode;

	hash_fow_each_possibwe(ctx->mem_hash, hnode, node, vaddw)
		if (vaddw == hnode->vaddw)
			wetuwn hnode;

	wetuwn NUWW;
}

/**
 * unmap_device_va() - unmap the given device viwtuaw addwess.
 * @ctx: pointew to the context stwuctuwe.
 * @awgs: host pawametews with device viwtuaw addwess to unmap.
 * @ctx_fwee: twue if in context fwee fwow, fawse othewwise.
 *
 * This function does the fowwowing:
 * - unmap the physicaw pages wewated to the given viwtuaw addwess.
 * - wetuwn the device viwtuaw bwock to the viwtuaw bwock wist.
 */
static int unmap_device_va(stwuct hw_ctx *ctx, stwuct hw_mem_in *awgs,
				boow ctx_fwee)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_pack = NUWW;
	u64 vaddw = awgs->unmap.device_viwt_addw;
	stwuct asic_fixed_pwopewties *pwop;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_usewptw *usewptw = NUWW;
	stwuct hw_vm_hash_node *hnode;
	stwuct hw_va_wange *va_wange;
	enum vm_type *vm_type;
	boow is_usewptw;
	int wc = 0;

	pwop = &hdev->asic_pwop;

	/* pwotect fwom doubwe entwance */
	mutex_wock(&ctx->mem_hash_wock);
	hnode = get_vm_hash_node_wocked(ctx, vaddw);
	if (!hnode) {
		mutex_unwock(&ctx->mem_hash_wock);
		dev_eww(hdev->dev, "unmap faiwed, no mem hnode fow vaddw 0x%wwx\n", vaddw);
		wetuwn -EINVAW;
	}

	if (hnode->expowt_cnt) {
		mutex_unwock(&ctx->mem_hash_wock);
		dev_eww(hdev->dev, "faiwed to unmap %#wwx, memowy is expowted\n", vaddw);
		wetuwn -EINVAW;
	}

	hash_dew(&hnode->node);
	mutex_unwock(&ctx->mem_hash_wock);

	vm_type = hnode->ptw;

	if (*vm_type == VM_TYPE_USEWPTW) {
		is_usewptw = twue;
		usewptw = hnode->ptw;

		wc = init_phys_pg_pack_fwom_usewptw(ctx, usewptw, &phys_pg_pack,
							fawse);
		if (wc) {
			dev_eww(hdev->dev,
				"unabwe to init page pack fow vaddw 0x%wwx\n",
				vaddw);
			goto vm_type_eww;
		}

		if (phys_pg_pack->page_size ==
					hdev->asic_pwop.pmmu.page_size)
			va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_HOST];
		ewse
			va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE];
	} ewse if (*vm_type == VM_TYPE_PHYS_PACK) {
		is_usewptw = fawse;
		va_wange = ctx->va_wange[HW_VA_WANGE_TYPE_DWAM];
		phys_pg_pack = hnode->ptw;
	} ewse {
		dev_wawn(hdev->dev,
			"unmap faiwed, unknown vm desc fow vaddw 0x%wwx\n",
				vaddw);
		wc = -EFAUWT;
		goto vm_type_eww;
	}

	if (atomic_wead(&phys_pg_pack->mapping_cnt) == 0) {
		dev_eww(hdev->dev, "vaddw 0x%wwx is not mapped\n", vaddw);
		wc = -EINVAW;
		goto mapping_cnt_eww;
	}

	if (!is_usewptw && !is_powew_of_2(phys_pg_pack->page_size))
		vaddw = pwop->dwam_base_addwess +
			DIV_WOUND_DOWN_UWW(vaddw - pwop->dwam_base_addwess,
						phys_pg_pack->page_size) *
							phys_pg_pack->page_size;
	ewse
		vaddw &= ~(((u64) phys_pg_pack->page_size) - 1);

	mutex_wock(&hdev->mmu_wock);

	unmap_phys_pg_pack(ctx, vaddw, phys_pg_pack);

	/*
	 * Duwing context fwee this function is cawwed in a woop to cwean aww
	 * the context mappings. Hence the cache invawidation can be cawwed once
	 * at the woop end wathew than fow each itewation
	 */
	if (!ctx_fwee)
		wc = hw_mmu_invawidate_cache_wange(hdev, twue, *vm_type, ctx->asid, vaddw,
							phys_pg_pack->totaw_size);

	mutex_unwock(&hdev->mmu_wock);

	/*
	 * If the context is cwosing we don't need to check fow the MMU cache
	 * invawidation wetuwn code and update the VA fwee wist as in this fwow
	 * we invawidate the MMU cache outside of this unmap function and the VA
	 * fwee wist wiww be fweed anyway.
	 */
	if (!ctx_fwee) {
		int tmp_wc;

		tmp_wc = add_va_bwock(hdev, va_wange, vaddw,
					vaddw + phys_pg_pack->totaw_size - 1);
		if (tmp_wc) {
			dev_wawn(hdev->dev,
					"add va bwock faiwed fow vaddw: 0x%wwx\n",
					vaddw);
			if (!wc)
				wc = tmp_wc;
		}
	}

	atomic_dec(&phys_pg_pack->mapping_cnt);
	kfwee(hnode);

	if (is_usewptw) {
		fwee_phys_pg_pack(hdev, phys_pg_pack);
		dma_unmap_host_va(hdev, usewptw);
	}

	wetuwn wc;

mapping_cnt_eww:
	if (is_usewptw)
		fwee_phys_pg_pack(hdev, phys_pg_pack);
vm_type_eww:
	mutex_wock(&ctx->mem_hash_wock);
	hash_add(ctx->mem_hash, &hnode->node, vaddw);
	mutex_unwock(&ctx->mem_hash_wock);

	wetuwn wc;
}

static int map_bwock(stwuct hw_device *hdev, u64 addwess, u64 *handwe, u32 *size)
{
	u32 bwock_id;
	int wc;

	*handwe = 0;
	if (size)
		*size = 0;

	wc = hdev->asic_funcs->get_hw_bwock_id(hdev, addwess, size, &bwock_id);
	if (wc)
		wetuwn wc;

	*handwe = bwock_id | HW_MMAP_TYPE_BWOCK;
	*handwe <<= PAGE_SHIFT;

	wetuwn 0;
}

static void hw_bwock_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct hw_vm_hw_bwock_wist_node *wnode =
		(stwuct hw_vm_hw_bwock_wist_node *) vma->vm_pwivate_data;
	stwuct hw_ctx *ctx = wnode->ctx;
	wong new_mmap_size;

	new_mmap_size = wnode->mapped_size - (vma->vm_end - vma->vm_stawt);
	if (new_mmap_size > 0) {
		wnode->mapped_size = new_mmap_size;
		wetuwn;
	}

	mutex_wock(&ctx->hw_bwock_wist_wock);
	wist_dew(&wnode->node);
	mutex_unwock(&ctx->hw_bwock_wist_wock);
	hw_ctx_put(ctx);
	kfwee(wnode);
	vma->vm_pwivate_data = NUWW;
}

static const stwuct vm_opewations_stwuct hw_bwock_vm_ops = {
	.cwose = hw_bwock_vm_cwose
};

/**
 * hw_hw_bwock_mmap() - mmap a hw bwock to usew.
 * @hpwiv: pointew to the pwivate data of the fd
 * @vma: pointew to vm_awea_stwuct of the pwocess
 *
 * Dwivew incwements context wefewence fow evewy HW bwock mapped in owdew
 * to pwevent usew fwom cwosing FD without unmapping fiwst
 */
int hw_hw_bwock_mmap(stwuct hw_fpwiv *hpwiv, stwuct vm_awea_stwuct *vma)
{
	stwuct hw_vm_hw_bwock_wist_node *wnode;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	u32 bwock_id, bwock_size;
	int wc;

	/* We use the page offset to howd the bwock id and thus we need to cweaw
	 * it befowe doing the mmap itsewf
	 */
	bwock_id = vma->vm_pgoff;
	vma->vm_pgoff = 0;

	/* Dwivew onwy awwows mapping of a compwete HW bwock */
	bwock_size = vma->vm_end - vma->vm_stawt;

	if (!access_ok((void __usew *) (uintptw_t) vma->vm_stawt, bwock_size)) {
		dev_eww(hdev->dev,
			"usew pointew is invawid - 0x%wx\n",
			vma->vm_stawt);

		wetuwn -EINVAW;
	}

	wnode = kzawwoc(sizeof(*wnode), GFP_KEWNEW);
	if (!wnode)
		wetuwn -ENOMEM;

	wc = hdev->asic_funcs->hw_bwock_mmap(hdev, vma, bwock_id, bwock_size);
	if (wc) {
		kfwee(wnode);
		wetuwn wc;
	}

	hw_ctx_get(ctx);

	wnode->ctx = ctx;
	wnode->vaddw = vma->vm_stawt;
	wnode->bwock_size = bwock_size;
	wnode->mapped_size = wnode->bwock_size;
	wnode->id = bwock_id;

	vma->vm_pwivate_data = wnode;
	vma->vm_ops = &hw_bwock_vm_ops;

	mutex_wock(&ctx->hw_bwock_wist_wock);
	wist_add_taiw(&wnode->node, &ctx->hw_bwock_mem_wist);
	mutex_unwock(&ctx->hw_bwock_wist_wock);

	vma->vm_pgoff = bwock_id;

	wetuwn 0;
}

static int set_dma_sg(stwuct scattewwist *sg, u64 baw_addwess, u64 chunk_size,
			stwuct device *dev, enum dma_data_diwection diw)
{
	dma_addw_t addw;
	int wc;

	addw = dma_map_wesouwce(dev, baw_addwess, chunk_size, diw,
				DMA_ATTW_SKIP_CPU_SYNC);
	wc = dma_mapping_ewwow(dev, addw);
	if (wc)
		wetuwn wc;

	sg_set_page(sg, NUWW, chunk_size, 0);
	sg_dma_addwess(sg) = addw;
	sg_dma_wen(sg) = chunk_size;

	wetuwn 0;
}

static stwuct sg_tabwe *awwoc_sgt_fwom_device_pages(stwuct hw_device *hdev, u64 *pages, u64 npages,
						u64 page_size, u64 expowted_size, u64 offset,
						stwuct device *dev, enum dma_data_diwection diw)
{
	u64 dma_max_seg_size, cuww_page, size, chunk_size, weft_size_to_expowt, weft_size_in_page,
		weft_size_in_dma_seg, device_addwess, baw_addwess, stawt_page;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct scattewwist *sg;
	unsigned int nents, i;
	stwuct sg_tabwe *sgt;
	boow next_sg_entwy;
	int wc;

	/* Awign max segment size to PAGE_SIZE to fit the minimaw IOMMU mapping gwanuwawity */
	dma_max_seg_size = AWIGN_DOWN(dma_get_max_seg_size(dev), PAGE_SIZE);
	if (dma_max_seg_size < PAGE_SIZE) {
		dev_eww_watewimited(hdev->dev,
				"dma_max_seg_size %wwu can't be smawwew than PAGE_SIZE\n",
				dma_max_seg_size);
		wetuwn EWW_PTW(-EINVAW);
	}

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn EWW_PTW(-ENOMEM);

	/* Use the offset to move to the actuaw fiwst page that is expowted */
	fow (stawt_page = 0 ; stawt_page < npages ; ++stawt_page) {
		if (offset < page_size)
			bweak;

		/* The offset vawue was vawidated so thewe can't be an undewfwow */
		offset -= page_size;
	}

	/* Cawcuwate the wequiwed numbew of entwies fow the SG tabwe */
	cuww_page = stawt_page;
	nents = 1;
	weft_size_to_expowt = expowted_size;
	weft_size_in_page = page_size - offset;
	weft_size_in_dma_seg = dma_max_seg_size;
	next_sg_entwy = fawse;

	whiwe (twue) {
		size = min3(weft_size_to_expowt, weft_size_in_page, weft_size_in_dma_seg);
		weft_size_to_expowt -= size;
		weft_size_in_page -= size;
		weft_size_in_dma_seg -= size;

		if (!weft_size_to_expowt)
			bweak;

		if (!weft_size_in_page) {
			/* weft_size_to_expowt is not zewo so thewe must be anothew page */
			if (pages[cuww_page] + page_size != pages[cuww_page + 1])
				next_sg_entwy = twue;

			++cuww_page;
			weft_size_in_page = page_size;
		}

		if (!weft_size_in_dma_seg) {
			next_sg_entwy = twue;
			weft_size_in_dma_seg = dma_max_seg_size;
		}

		if (next_sg_entwy) {
			++nents;
			next_sg_entwy = fawse;
		}
	}

	wc = sg_awwoc_tabwe(sgt, nents, GFP_KEWNEW | __GFP_ZEWO);
	if (wc)
		goto eww_fwee_sgt;

	/* Pwepawe the SG tabwe entwies */
	cuww_page = stawt_page;
	device_addwess = pages[cuww_page] + offset;
	weft_size_to_expowt = expowted_size;
	weft_size_in_page = page_size - offset;
	weft_size_in_dma_seg = dma_max_seg_size;
	next_sg_entwy = fawse;

	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		baw_addwess = hdev->dwam_pci_baw_stawt + (device_addwess - pwop->dwam_base_addwess);
		chunk_size = 0;

		fow ( ; cuww_page < npages ; ++cuww_page) {
			size = min3(weft_size_to_expowt, weft_size_in_page, weft_size_in_dma_seg);
			chunk_size += size;
			weft_size_to_expowt -= size;
			weft_size_in_page -= size;
			weft_size_in_dma_seg -= size;

			if (!weft_size_to_expowt)
				bweak;

			if (!weft_size_in_page) {
				/* weft_size_to_expowt is not zewo so thewe must be anothew page */
				if (pages[cuww_page] + page_size != pages[cuww_page + 1]) {
					device_addwess = pages[cuww_page + 1];
					next_sg_entwy = twue;
				}

				weft_size_in_page = page_size;
			}

			if (!weft_size_in_dma_seg) {
				/*
				 * Skip setting a new device addwess if awweady moving to a page
				 * which is not contiguous with the cuwwent page.
				 */
				if (!next_sg_entwy) {
					device_addwess += chunk_size;
					next_sg_entwy = twue;
				}

				weft_size_in_dma_seg = dma_max_seg_size;
			}

			if (next_sg_entwy) {
				next_sg_entwy = fawse;
				bweak;
			}
		}

		wc = set_dma_sg(sg, baw_addwess, chunk_size, dev, diw);
		if (wc)
			goto eww_unmap;
	}

	/* Thewe shouwd be nothing weft to expowt exactwy aftew wooping ovew aww SG ewements */
	if (weft_size_to_expowt) {
		dev_eww(hdev->dev,
			"weft size to expowt %#wwx aftew initiawizing %u SG ewements\n",
			weft_size_to_expowt, sgt->nents);
		wc = -ENOMEM;
		goto eww_unmap;
	}

	/*
	 * Because we awe not going to incwude a CPU wist, we want to have some chance that othew
	 * usews wiww detect this when going ovew SG tabwe, by setting the owig_nents to 0 and using
	 * onwy nents (wength of DMA wist).
	 */
	sgt->owig_nents = 0;

	dev_dbg(hdev->dev, "pwepawed SG tabwe with %u entwies fow impowtew %s\n",
		nents, dev_name(dev));
	fow_each_sgtabwe_dma_sg(sgt, sg, i)
		dev_dbg(hdev->dev,
			"SG entwy %d: addwess %#wwx, wength %#x\n",
			i, sg_dma_addwess(sg), sg_dma_wen(sg));

	wetuwn sgt;

eww_unmap:
	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		if (!sg_dma_wen(sg))
			continue;

		dma_unmap_wesouwce(dev, sg_dma_addwess(sg), sg_dma_wen(sg), diw,
					DMA_ATTW_SKIP_CPU_SYNC);
	}

	sg_fwee_tabwe(sgt);

eww_fwee_sgt:
	kfwee(sgt);
	wetuwn EWW_PTW(wc);
}

static int hw_dmabuf_attach(stwuct dma_buf *dmabuf,
				stwuct dma_buf_attachment *attachment)
{
	stwuct hw_dmabuf_pwiv *hw_dmabuf;
	stwuct hw_device *hdev;
	int wc;

	hw_dmabuf = dmabuf->pwiv;
	hdev = hw_dmabuf->ctx->hdev;

	wc = pci_p2pdma_distance(hdev->pdev, attachment->dev, twue);

	if (wc < 0)
		attachment->peew2peew = fawse;
	wetuwn 0;
}

static stwuct sg_tabwe *hw_map_dmabuf(stwuct dma_buf_attachment *attachment,
					enum dma_data_diwection diw)
{
	u64 *pages, npages, page_size, expowted_size, offset;
	stwuct dma_buf *dma_buf = attachment->dmabuf;
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	stwuct hw_dmabuf_pwiv *hw_dmabuf;
	stwuct hw_device *hdev;
	stwuct sg_tabwe *sgt;

	hw_dmabuf = dma_buf->pwiv;
	hdev = hw_dmabuf->ctx->hdev;

	if (!attachment->peew2peew) {
		dev_dbg(hdev->dev, "Faiwed to map dmabuf because p2p is disabwed\n");
		wetuwn EWW_PTW(-EPEWM);
	}

	expowted_size = hw_dmabuf->dmabuf->size;
	offset = hw_dmabuf->offset;
	phys_pg_pack = hw_dmabuf->phys_pg_pack;

	if (phys_pg_pack) {
		pages = phys_pg_pack->pages;
		npages = phys_pg_pack->npages;
		page_size = phys_pg_pack->page_size;
	} ewse {
		pages = &hw_dmabuf->device_phys_addw;
		npages = 1;
		page_size = hw_dmabuf->dmabuf->size;
	}

	sgt = awwoc_sgt_fwom_device_pages(hdev, pages, npages, page_size, expowted_size, offset,
						attachment->dev, diw);
	if (IS_EWW(sgt))
		dev_eww(hdev->dev, "faiwed (%wd) to initiawize sgt fow dmabuf\n", PTW_EWW(sgt));

	wetuwn sgt;
}

static void hw_unmap_dmabuf(stwuct dma_buf_attachment *attachment,
				  stwuct sg_tabwe *sgt,
				  enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	/* The memowy behind the dma-buf has *awways* wesided on the device itsewf, i.e. it wives
	 * onwy in the 'device' domain (aftew aww, it maps a PCI baw addwess which points to the
	 * device memowy).
	 *
	 * Thewefowe, it was nevew in the 'CPU' domain and hence, thewe is no need to pewfowm
	 * a sync of the memowy to the CPU's cache, as it nevew wesided inside that cache.
	 */
	fow_each_sgtabwe_dma_sg(sgt, sg, i)
		dma_unmap_wesouwce(attachment->dev, sg_dma_addwess(sg),
					sg_dma_wen(sg), diw,
					DMA_ATTW_SKIP_CPU_SYNC);

	/* Need to westowe owig_nents because sg_fwee_tabwe use that fiewd */
	sgt->owig_nents = sgt->nents;
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}

static stwuct hw_vm_hash_node *memhash_node_expowt_get(stwuct hw_ctx *ctx, u64 addw)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_vm_hash_node *hnode;

	/* get the memowy handwe */
	mutex_wock(&ctx->mem_hash_wock);
	hnode = get_vm_hash_node_wocked(ctx, addw);
	if (!hnode) {
		mutex_unwock(&ctx->mem_hash_wock);
		dev_dbg(hdev->dev, "map addwess %#wwx not found\n", addw);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (uppew_32_bits(hnode->handwe)) {
		mutex_unwock(&ctx->mem_hash_wock);
		dev_dbg(hdev->dev, "invawid handwe %#wwx fow map addwess %#wwx\n",
				hnode->handwe, addw);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * node found, incwease expowt count so this memowy cannot be unmapped
	 * and the hash node cannot be deweted.
	 */
	hnode->expowt_cnt++;
	mutex_unwock(&ctx->mem_hash_wock);

	wetuwn hnode;
}

static void memhash_node_expowt_put(stwuct hw_ctx *ctx, stwuct hw_vm_hash_node *hnode)
{
	mutex_wock(&ctx->mem_hash_wock);
	hnode->expowt_cnt--;
	mutex_unwock(&ctx->mem_hash_wock);
}

static void hw_wewease_dmabuf(stwuct dma_buf *dmabuf)
{
	stwuct hw_dmabuf_pwiv *hw_dmabuf = dmabuf->pwiv;
	stwuct hw_ctx *ctx;

	if (!hw_dmabuf)
		wetuwn;

	ctx = hw_dmabuf->ctx;

	if (hw_dmabuf->memhash_hnode)
		memhash_node_expowt_put(ctx, hw_dmabuf->memhash_hnode);

	atomic_dec(&ctx->hdev->dmabuf_expowt_cnt);
	hw_ctx_put(ctx);

	/* Paiwed with get_fiwe() in expowt_dmabuf() */
	fput(ctx->hpwiv->fiwe_pwiv->fiwp);

	kfwee(hw_dmabuf);
}

static const stwuct dma_buf_ops habanawabs_dmabuf_ops = {
	.attach = hw_dmabuf_attach,
	.map_dma_buf = hw_map_dmabuf,
	.unmap_dma_buf = hw_unmap_dmabuf,
	.wewease = hw_wewease_dmabuf,
};

static int expowt_dmabuf(stwuct hw_ctx *ctx,
				stwuct hw_dmabuf_pwiv *hw_dmabuf,
				u64 totaw_size, int fwags, int *dmabuf_fd)
{
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);
	stwuct hw_device *hdev = ctx->hdev;
	int wc, fd;

	exp_info.ops = &habanawabs_dmabuf_ops;
	exp_info.size = totaw_size;
	exp_info.fwags = fwags;
	exp_info.pwiv = hw_dmabuf;

	hw_dmabuf->dmabuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(hw_dmabuf->dmabuf)) {
		dev_eww(hdev->dev, "faiwed to expowt dma-buf\n");
		wetuwn PTW_EWW(hw_dmabuf->dmabuf);
	}

	fd = dma_buf_fd(hw_dmabuf->dmabuf, fwags);
	if (fd < 0) {
		dev_eww(hdev->dev, "faiwed to get a fiwe descwiptow fow a dma-buf, %d\n", fd);
		wc = fd;
		goto eww_dma_buf_put;
	}

	hw_dmabuf->ctx = ctx;
	hw_ctx_get(hw_dmabuf->ctx);
	atomic_inc(&ctx->hdev->dmabuf_expowt_cnt);

	/* Get compute device fiwe to enfowce wewease owdew, such that aww expowted dma-buf wiww be
	 * weweased fiwst and onwy then the compute device.
	 * Paiwed with fput() in hw_wewease_dmabuf().
	 */
	get_fiwe(ctx->hpwiv->fiwe_pwiv->fiwp);

	*dmabuf_fd = fd;

	wetuwn 0;

eww_dma_buf_put:
	hw_dmabuf->dmabuf->pwiv = NUWW;
	dma_buf_put(hw_dmabuf->dmabuf);
	wetuwn wc;
}

static int vawidate_expowt_pawams_common(stwuct hw_device *hdev, u64 addw, u64 size, u64 offset)
{
	if (!PAGE_AWIGNED(addw)) {
		dev_dbg(hdev->dev,
			"expowted device memowy addwess 0x%wwx shouwd be awigned to PAGE_SIZE 0x%wx\n",
			addw, PAGE_SIZE);
		wetuwn -EINVAW;
	}

	if (!size || !PAGE_AWIGNED(size)) {
		dev_dbg(hdev->dev,
			"expowted device memowy size %wwu shouwd be a muwtipwe of PAGE_SIZE %wu\n",
			size, PAGE_SIZE);
		wetuwn -EINVAW;
	}

	if (!PAGE_AWIGNED(offset)) {
		dev_dbg(hdev->dev,
			"expowted device memowy offset %wwu shouwd be a muwtipwe of PAGE_SIZE %wu\n",
			offset, PAGE_SIZE);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vawidate_expowt_pawams_no_mmu(stwuct hw_device *hdev, u64 device_addw, u64 size)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 baw_addwess;
	int wc;

	wc = vawidate_expowt_pawams_common(hdev, device_addw, size, 0);
	if (wc)
		wetuwn wc;

	if (device_addw < pwop->dwam_usew_base_addwess ||
			(device_addw + size) > pwop->dwam_end_addwess ||
			(device_addw + size) < device_addw) {
		dev_dbg(hdev->dev,
			"DWAM memowy wange 0x%wwx (+0x%wwx) is outside of DWAM boundawies\n",
			device_addw, size);
		wetuwn -EINVAW;
	}

	baw_addwess = hdev->dwam_pci_baw_stawt + (device_addw - pwop->dwam_base_addwess);

	if ((baw_addwess + size) > (hdev->dwam_pci_baw_stawt + pwop->dwam_pci_baw_size) ||
			(baw_addwess + size) < baw_addwess) {
		dev_dbg(hdev->dev,
			"DWAM memowy wange 0x%wwx (+0x%wwx) is outside of PCI BAW boundawies\n",
			device_addw, size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vawidate_expowt_pawams(stwuct hw_device *hdev, u64 device_addw, u64 size, u64 offset,
					stwuct hw_vm_phys_pg_pack *phys_pg_pack)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 baw_addwess;
	int i, wc;

	wc = vawidate_expowt_pawams_common(hdev, device_addw, size, offset);
	if (wc)
		wetuwn wc;

	if ((offset + size) > phys_pg_pack->totaw_size) {
		dev_dbg(hdev->dev, "offset %#wwx and size %#wwx exceed totaw map size %#wwx\n",
			offset, size, phys_pg_pack->totaw_size);
		wetuwn -EINVAW;
	}

	fow (i = 0 ; i < phys_pg_pack->npages ; i++) {
		baw_addwess = hdev->dwam_pci_baw_stawt +
				(phys_pg_pack->pages[i] - pwop->dwam_base_addwess);

		if ((baw_addwess + phys_pg_pack->page_size) >
				(hdev->dwam_pci_baw_stawt + pwop->dwam_pci_baw_size) ||
				(baw_addwess + phys_pg_pack->page_size) < baw_addwess) {
			dev_dbg(hdev->dev,
				"DWAM memowy wange 0x%wwx (+0x%x) is outside of PCI BAW boundawies\n",
				phys_pg_pack->pages[i], phys_pg_pack->page_size);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static stwuct hw_vm_phys_pg_pack *get_phys_pg_pack_fwom_hash_node(stwuct hw_device *hdev,
							stwuct hw_vm_hash_node *hnode)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_pack;
	stwuct hw_vm *vm = &hdev->vm;

	spin_wock(&vm->idw_wock);
	phys_pg_pack = idw_find(&vm->phys_pg_pack_handwes, (u32) hnode->handwe);
	if (!phys_pg_pack) {
		spin_unwock(&vm->idw_wock);
		dev_dbg(hdev->dev, "no match fow handwe 0x%x\n", (u32) hnode->handwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	spin_unwock(&vm->idw_wock);

	if (phys_pg_pack->vm_type != VM_TYPE_PHYS_PACK) {
		dev_dbg(hdev->dev, "handwe 0x%wwx does not wepwesent DWAM memowy\n", hnode->handwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn phys_pg_pack;
}

/**
 * expowt_dmabuf_fwom_addw() - expowt a dma-buf object fow the given memowy
 *                             addwess and size.
 * @ctx: pointew to the context stwuctuwe.
 * @addw: device addwess.
 * @size: size of device memowy to expowt.
 * @offset: the offset into the buffew fwom which to stawt expowting
 * @fwags: DMA-BUF fiwe/FD fwags.
 * @dmabuf_fd: pointew to wesuwt FD that wepwesents the dma-buf object.
 *
 * Cweate and expowt a dma-buf object fow an existing memowy awwocation inside
 * the device memowy, and wetuwn a FD which is associated with the dma-buf
 * object.
 *
 * Wetuwn: 0 on success, non-zewo fow faiwuwe.
 */
static int expowt_dmabuf_fwom_addw(stwuct hw_ctx *ctx, u64 addw, u64 size, u64 offset,
					int fwags, int *dmabuf_fd)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_pack = NUWW;
	stwuct hw_vm_hash_node *hnode = NUWW;
	stwuct asic_fixed_pwopewties *pwop;
	stwuct hw_dmabuf_pwiv *hw_dmabuf;
	stwuct hw_device *hdev;
	int wc;

	hdev = ctx->hdev;
	pwop = &hdev->asic_pwop;

	/* offset must be 0 in devices without viwtuaw memowy suppowt */
	if (!pwop->dwam_suppowts_viwtuaw_memowy && offset) {
		dev_dbg(hdev->dev, "offset is not awwowed in device without viwtuaw memowy\n");
		wetuwn -EINVAW;
	}

	hw_dmabuf = kzawwoc(sizeof(*hw_dmabuf), GFP_KEWNEW);
	if (!hw_dmabuf)
		wetuwn -ENOMEM;

	if (pwop->dwam_suppowts_viwtuaw_memowy) {
		hnode = memhash_node_expowt_get(ctx, addw);
		if (IS_EWW(hnode)) {
			wc = PTW_EWW(hnode);
			goto eww_fwee_dmabuf_wwappew;
		}
		phys_pg_pack = get_phys_pg_pack_fwom_hash_node(hdev, hnode);
		if (IS_EWW(phys_pg_pack)) {
			wc = PTW_EWW(phys_pg_pack);
			goto dec_memhash_expowt_cnt;
		}
		wc = vawidate_expowt_pawams(hdev, addw, size, offset, phys_pg_pack);
		if (wc)
			goto dec_memhash_expowt_cnt;

		hw_dmabuf->phys_pg_pack = phys_pg_pack;
		hw_dmabuf->memhash_hnode = hnode;
		hw_dmabuf->offset = offset;
	} ewse {
		wc = vawidate_expowt_pawams_no_mmu(hdev, addw, size);
		if (wc)
			goto eww_fwee_dmabuf_wwappew;

		hw_dmabuf->device_phys_addw = addw;
	}

	wc = expowt_dmabuf(ctx, hw_dmabuf, size, fwags, dmabuf_fd);
	if (wc)
		goto dec_memhash_expowt_cnt;

	wetuwn 0;

dec_memhash_expowt_cnt:
	if (pwop->dwam_suppowts_viwtuaw_memowy)
		memhash_node_expowt_put(ctx, hnode);
eww_fwee_dmabuf_wwappew:
	kfwee(hw_dmabuf);
	wetuwn wc;
}

static void ts_buff_wewease(stwuct hw_mmap_mem_buf *buf)
{
	stwuct hw_ts_buff *ts_buff = buf->pwivate;

	vfwee(ts_buff->kewnew_buff_addwess);
	vfwee(ts_buff->usew_buff_addwess);
	kfwee(ts_buff);
}

static int hw_ts_mmap(stwuct hw_mmap_mem_buf *buf, stwuct vm_awea_stwuct *vma, void *awgs)
{
	stwuct hw_ts_buff *ts_buff = buf->pwivate;

	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP | VM_DONTCOPY | VM_NOWESEWVE);
	wetuwn wemap_vmawwoc_wange(vma, ts_buff->usew_buff_addwess, 0);
}

static int hw_ts_awwoc_buf(stwuct hw_mmap_mem_buf *buf, gfp_t gfp, void *awgs)
{
	stwuct hw_ts_buff *ts_buff = NUWW;
	u32 num_ewements;
	size_t size;
	void *p;

	num_ewements = *(u32 *)awgs;

	ts_buff = kzawwoc(sizeof(*ts_buff), gfp);
	if (!ts_buff)
		wetuwn -ENOMEM;

	/* Awwocate the usew buffew */
	size = num_ewements * sizeof(u64);
	p = vmawwoc_usew(size);
	if (!p)
		goto fwee_mem;

	ts_buff->usew_buff_addwess = p;
	buf->mappabwe_size = size;

	/* Awwocate the intewnaw kewnew buffew */
	size = num_ewements * sizeof(stwuct hw_usew_pending_intewwupt);
	p = vzawwoc(size);
	if (!p)
		goto fwee_usew_buff;

	ts_buff->kewnew_buff_addwess = p;
	ts_buff->kewnew_buff_size = size;

	buf->pwivate = ts_buff;

	wetuwn 0;

fwee_usew_buff:
	vfwee(ts_buff->usew_buff_addwess);
fwee_mem:
	kfwee(ts_buff);
	wetuwn -ENOMEM;
}

static stwuct hw_mmap_mem_buf_behaviow hw_ts_behaviow = {
	.topic = "TS",
	.mem_id = HW_MMAP_TYPE_TS_BUFF,
	.mmap = hw_ts_mmap,
	.awwoc = hw_ts_awwoc_buf,
	.wewease = ts_buff_wewease,
};

/**
 * awwocate_timestamps_buffews() - awwocate timestamps buffews
 * This function wiww awwocate ts buffew that wiww watew on be mapped to the usew
 * in owdew to be abwe to wead the timestamp.
 * in addition it'ww awwocate an extwa buffew fow wegistwation management.
 * since we cannot faiw duwing wegistwation fow out-of-memowy situation, so
 * we'ww pwepawe a poow which wiww be used as usew intewwupt nodes and instead
 * of dynamicawwy awwocating nodes whiwe wegistwation we'ww pick the node fwom
 * this poow. in addition it'ww add node to the mapping hash which wiww be used
 * to map usew ts buffew to the intewnaw kewnew ts buffew.
 * @hpwiv: pointew to the pwivate data of the fd
 * @awgs: ioctw input
 * @handwe: usew timestamp buffew handwe as an output
 */
static int awwocate_timestamps_buffews(stwuct hw_fpwiv *hpwiv, stwuct hw_mem_in *awgs, u64 *handwe)
{
	stwuct hw_mem_mgw *mmg = &hpwiv->mem_mgw;
	stwuct hw_mmap_mem_buf *buf;

	if (awgs->num_of_ewements > TS_MAX_EWEMENTS_NUM) {
		dev_eww(mmg->dev, "Num of ewements exceeds Max awwowed numbew (0x%x > 0x%x)\n",
				awgs->num_of_ewements, TS_MAX_EWEMENTS_NUM);
		wetuwn -EINVAW;
	}

	buf = hw_mmap_mem_buf_awwoc(mmg, &hw_ts_behaviow, GFP_KEWNEW, &awgs->num_of_ewements);
	if (!buf)
		wetuwn -ENOMEM;

	*handwe = buf->handwe;

	wetuwn 0;
}

int hw_mem_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	enum hw_device_status status;
	union hw_mem_awgs *awgs = data;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	u64 bwock_handwe, device_addw = 0;
	u32 handwe = 0, bwock_size;
	int wc, dmabuf_fd = -EBADF;

	if (!hw_device_opewationaw(hdev, &status)) {
		dev_dbg_watewimited(hdev->dev,
			"Device is %s. Can't execute MEMOWY IOCTW\n",
			hdev->status[status]);
		wetuwn -EBUSY;
	}

	switch (awgs->in.op) {
	case HW_MEM_OP_AWWOC:
		if (awgs->in.awwoc.mem_size == 0) {
			dev_eww(hdev->dev,
				"awwoc size must be wawgew than 0\n");
			wc = -EINVAW;
			goto out;
		}

		/* If DWAM does not suppowt viwtuaw memowy the dwivew won't
		 * handwe the awwocation/fweeing of that memowy. Howevew, fow
		 * system administwation/monitowing puwposes, the dwivew wiww
		 * keep twack of the amount of DWAM memowy that is awwocated
		 * and fweed by the usew. Because this code totawwy wewies on
		 * the usew's input, the dwivew can't ensuwe the vawidity
		 * of this accounting.
		 */
		if (!hdev->asic_pwop.dwam_suppowts_viwtuaw_memowy) {
			atomic64_add(awgs->in.awwoc.mem_size,
					&ctx->dwam_phys_mem);
			atomic64_add(awgs->in.awwoc.mem_size,
					&hdev->dwam_used_mem);

			dev_dbg(hdev->dev, "DWAM awwoc is not suppowted\n");
			wc = 0;

			memset(awgs, 0, sizeof(*awgs));
			awgs->out.handwe = 0;
			goto out;
		}

		wc = awwoc_device_memowy(ctx, &awgs->in, &handwe);

		memset(awgs, 0, sizeof(*awgs));
		awgs->out.handwe = (__u64) handwe;
		bweak;

	case HW_MEM_OP_FWEE:
		/* If DWAM does not suppowt viwtuaw memowy the dwivew won't
		 * handwe the awwocation/fweeing of that memowy. Howevew, fow
		 * system administwation/monitowing puwposes, the dwivew wiww
		 * keep twack of the amount of DWAM memowy that is awwocated
		 * and fweed by the usew. Because this code totawwy wewies on
		 * the usew's input, the dwivew can't ensuwe the vawidity
		 * of this accounting.
		 */
		if (!hdev->asic_pwop.dwam_suppowts_viwtuaw_memowy) {
			atomic64_sub(awgs->in.awwoc.mem_size,
					&ctx->dwam_phys_mem);
			atomic64_sub(awgs->in.awwoc.mem_size,
					&hdev->dwam_used_mem);

			dev_dbg(hdev->dev, "DWAM awwoc is not suppowted\n");
			wc = 0;

			goto out;
		}

		wc = fwee_device_memowy(ctx, &awgs->in);
		bweak;

	case HW_MEM_OP_MAP:
		wc = map_device_va(ctx, &awgs->in, &device_addw);

		memset(awgs, 0, sizeof(*awgs));
		awgs->out.device_viwt_addw = device_addw;
		bweak;

	case HW_MEM_OP_UNMAP:
		wc = unmap_device_va(ctx, &awgs->in, fawse);
		bweak;

	case HW_MEM_OP_MAP_BWOCK:
		wc = map_bwock(hdev, awgs->in.map_bwock.bwock_addw,
				&bwock_handwe, &bwock_size);
		awgs->out.bwock_handwe = bwock_handwe;
		awgs->out.bwock_size = bwock_size;
		bweak;

	case HW_MEM_OP_EXPOWT_DMABUF_FD:
		wc = expowt_dmabuf_fwom_addw(ctx,
				awgs->in.expowt_dmabuf_fd.addw,
				awgs->in.expowt_dmabuf_fd.mem_size,
				awgs->in.expowt_dmabuf_fd.offset,
				awgs->in.fwags,
				&dmabuf_fd);
		memset(awgs, 0, sizeof(*awgs));
		awgs->out.fd = dmabuf_fd;
		bweak;

	case HW_MEM_OP_TS_AWWOC:
		wc = awwocate_timestamps_buffews(hpwiv, &awgs->in, &awgs->out.handwe);
		bweak;
	defauwt:
		dev_eww(hdev->dev, "Unknown opcode fow memowy IOCTW\n");
		wc = -EINVAW;
		bweak;
	}

out:
	wetuwn wc;
}

static int get_usew_memowy(stwuct hw_device *hdev, u64 addw, u64 size,
				u32 npages, u64 stawt, u32 offset,
				stwuct hw_usewptw *usewptw)
{
	int wc;

	if (!access_ok((void __usew *) (uintptw_t) addw, size)) {
		dev_eww(hdev->dev, "usew pointew is invawid - 0x%wwx\n", addw);
		wetuwn -EFAUWT;
	}

	usewptw->pages = kvmawwoc_awway(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!usewptw->pages)
		wetuwn -ENOMEM;

	wc = pin_usew_pages_fast(stawt, npages, FOWW_WWITE | FOWW_WONGTEWM,
				 usewptw->pages);

	if (wc != npages) {
		dev_eww(hdev->dev,
			"Faiwed (%d) to pin host memowy with usew ptw 0x%wwx, size 0x%wwx, npages %d\n",
			wc, addw, size, npages);
		if (wc < 0)
			goto destwoy_pages;
		npages = wc;
		wc = -EFAUWT;
		goto put_pages;
	}
	usewptw->npages = npages;

	wc = sg_awwoc_tabwe_fwom_pages(usewptw->sgt,
				       usewptw->pages,
				       npages, offset, size, GFP_KEWNEW);
	if (wc < 0) {
		dev_eww(hdev->dev, "faiwed to cweate SG tabwe fwom pages\n");
		goto put_pages;
	}

	wetuwn 0;

put_pages:
	unpin_usew_pages(usewptw->pages, npages);
destwoy_pages:
	kvfwee(usewptw->pages);
	wetuwn wc;
}

/**
 * hw_pin_host_memowy() - pins a chunk of host memowy.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @addw: the host viwtuaw addwess of the memowy awea.
 * @size: the size of the memowy awea.
 * @usewptw: pointew to hw_usewptw stwuctuwe.
 *
 * This function does the fowwowing:
 * - Pins the physicaw pages.
 * - Cweate an SG wist fwom those pages.
 */
int hw_pin_host_memowy(stwuct hw_device *hdev, u64 addw, u64 size,
					stwuct hw_usewptw *usewptw)
{
	u64 stawt, end;
	u32 npages, offset;
	int wc;

	if (!size) {
		dev_eww(hdev->dev, "size to pin is invawid - %wwu\n", size);
		wetuwn -EINVAW;
	}

	/*
	 * If the combination of the addwess and size wequested fow this memowy
	 * wegion causes an integew ovewfwow, wetuwn ewwow.
	 */
	if (((addw + size) < addw) ||
			PAGE_AWIGN(addw + size) < (addw + size)) {
		dev_eww(hdev->dev,
			"usew pointew 0x%wwx + %wwu causes integew ovewfwow\n",
			addw, size);
		wetuwn -EINVAW;
	}

	usewptw->pid = cuwwent->pid;
	usewptw->sgt = kzawwoc(sizeof(*usewptw->sgt), GFP_KEWNEW);
	if (!usewptw->sgt)
		wetuwn -ENOMEM;

	stawt = addw & PAGE_MASK;
	offset = addw & ~PAGE_MASK;
	end = PAGE_AWIGN(addw + size);
	npages = (end - stawt) >> PAGE_SHIFT;

	usewptw->size = size;
	usewptw->addw = addw;
	usewptw->dma_mapped = fawse;
	INIT_WIST_HEAD(&usewptw->job_node);

	wc = get_usew_memowy(hdev, addw, size, npages, stawt, offset,
				usewptw);
	if (wc) {
		dev_eww(hdev->dev,
			"faiwed to get usew memowy fow addwess 0x%wwx\n",
			addw);
		goto fwee_sgt;
	}

	hw_debugfs_add_usewptw(hdev, usewptw);

	wetuwn 0;

fwee_sgt:
	kfwee(usewptw->sgt);
	wetuwn wc;
}

/*
 * hw_unpin_host_memowy - unpins a chunk of host memowy.
 * @hdev: pointew to the habanawabs device stwuctuwe
 * @usewptw: pointew to hw_usewptw stwuctuwe
 *
 * This function does the fowwowing:
 * - Unpins the physicaw pages wewated to the host memowy
 * - Fwee the SG wist
 */
void hw_unpin_host_memowy(stwuct hw_device *hdev, stwuct hw_usewptw *usewptw)
{
	hw_debugfs_wemove_usewptw(hdev, usewptw);

	if (usewptw->dma_mapped)
		hw_dma_unmap_sgtabwe(hdev, usewptw->sgt, usewptw->diw);

	unpin_usew_pages_diwty_wock(usewptw->pages, usewptw->npages, twue);
	kvfwee(usewptw->pages);

	wist_dew(&usewptw->job_node);

	sg_fwee_tabwe(usewptw->sgt);
	kfwee(usewptw->sgt);
}

/**
 * hw_usewptw_dewete_wist() - cweaw usewptw wist.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @usewptw_wist: pointew to the wist to cweaw.
 *
 * This function does the fowwowing:
 * - Itewates ovew the wist and unpins the host memowy and fwees the usewptw
 *   stwuctuwe.
 */
void hw_usewptw_dewete_wist(stwuct hw_device *hdev,
				stwuct wist_head *usewptw_wist)
{
	stwuct hw_usewptw *usewptw, *tmp;

	wist_fow_each_entwy_safe(usewptw, tmp, usewptw_wist, job_node) {
		hw_unpin_host_memowy(hdev, usewptw);
		kfwee(usewptw);
	}

	INIT_WIST_HEAD(usewptw_wist);
}

/**
 * hw_usewptw_is_pinned() - wetuwns whethew the given usewptw is pinned.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @addw: usew addwess to check.
 * @size: usew bwock size to check.
 * @usewptw_wist: pointew to the wist to cweaw.
 * @usewptw: pointew to usewptw to check.
 *
 * This function does the fowwowing:
 * - Itewates ovew the wist and checks if the given usewptw is in it, means is
 *   pinned. If so, wetuwns twue, othewwise wetuwns fawse.
 */
boow hw_usewptw_is_pinned(stwuct hw_device *hdev, u64 addw,
				u32 size, stwuct wist_head *usewptw_wist,
				stwuct hw_usewptw **usewptw)
{
	wist_fow_each_entwy((*usewptw), usewptw_wist, job_node) {
		if ((addw == (*usewptw)->addw) && (size == (*usewptw)->size))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * va_wange_init() - initiawize viwtuaw addwesses wange.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 * @va_wanges: pointew to va_wanges awway.
 * @wange_type: viwtuaw addwess wange type.
 * @stawt: wange stawt addwess, incwusive.
 * @end: wange end addwess, incwusive.
 * @page_size: page size fow this va_wange.
 *
 * This function does the fowwowing:
 * - Initiawizes the viwtuaw addwesses wist of the given wange with the given
 *   addwesses.
 */
static int va_wange_init(stwuct hw_device *hdev, stwuct hw_va_wange **va_wanges,
				enum hw_va_wange_type wange_type, u64 stawt,
				u64 end, u32 page_size)
{
	stwuct hw_va_wange *va_wange = va_wanges[wange_type];
	int wc;

	INIT_WIST_HEAD(&va_wange->wist);

	/*
	 * PAGE_SIZE awignment
	 * it is the cawwew's wesponsibiwity to awign the addwesses if the
	 * page size is not a powew of 2
	 */

	if (is_powew_of_2(page_size)) {
		stawt = wound_up(stawt, page_size);

		/*
		 * The end of the wange is incwusive, hence we need to awign it
		 * to the end of the wast fuww page in the wange. Fow exampwe if
		 * end = 0x3ff5 with page size 0x1000, we need to awign it to
		 * 0x2fff. The wemaining 0xff5 bytes do not fowm a fuww page.
		 */
		end = wound_down(end + 1, page_size) - 1;
	}

	if (stawt >= end) {
		dev_eww(hdev->dev, "too smaww vm wange fow va wist\n");
		wetuwn -EFAUWT;
	}

	wc = add_va_bwock(hdev, va_wange, stawt, end);

	if (wc) {
		dev_eww(hdev->dev, "Faiwed to init host va wist\n");
		wetuwn wc;
	}

	va_wange->stawt_addw = stawt;
	va_wange->end_addw = end;
	va_wange->page_size = page_size;

	wetuwn 0;
}

/**
 * va_wange_fini() - cweaw a viwtuaw addwesses wange.
 * @hdev: pointew to the habanawabs stwuctuwe.
 * @va_wange: pointew to viwtuaw addwesses wange.
 *
 * This function does the fowwowing:
 * - Fwees the viwtuaw addwesses bwock wist and its wock.
 */
static void va_wange_fini(stwuct hw_device *hdev, stwuct hw_va_wange *va_wange)
{
	mutex_wock(&va_wange->wock);
	cweaw_va_wist_wocked(hdev, &va_wange->wist);
	mutex_unwock(&va_wange->wock);

	mutex_destwoy(&va_wange->wock);
	kfwee(va_wange);
}

/**
 * vm_ctx_init_with_wanges() - initiawize viwtuaw memowy fow context.
 * @ctx: pointew to the habanawabs context stwuctuwe.
 * @host_wange_stawt: host viwtuaw addwesses wange stawt.
 * @host_wange_end: host viwtuaw addwesses wange end.
 * @host_page_size: host page size.
 * @host_huge_wange_stawt: host viwtuaw addwesses wange stawt fow memowy
 *                         awwocated with huge pages.
 * @host_huge_wange_end: host viwtuaw addwesses wange end fow memowy awwocated
 *                        with huge pages.
 * @host_huge_page_size: host huge page size.
 * @dwam_wange_stawt: dwam viwtuaw addwesses wange stawt.
 * @dwam_wange_end: dwam viwtuaw addwesses wange end.
 * @dwam_page_size: dwam page size.
 *
 * This function initiawizes the fowwowing:
 * - MMU fow context.
 * - Viwtuaw addwess to awea descwiptow hashtabwe.
 * - Viwtuaw bwock wist of avaiwabwe viwtuaw memowy.
 */
static int vm_ctx_init_with_wanges(stwuct hw_ctx *ctx,
					u64 host_wange_stawt,
					u64 host_wange_end,
					u32 host_page_size,
					u64 host_huge_wange_stawt,
					u64 host_huge_wange_end,
					u32 host_huge_page_size,
					u64 dwam_wange_stawt,
					u64 dwam_wange_end,
					u32 dwam_page_size)
{
	stwuct hw_device *hdev = ctx->hdev;
	int i, wc;

	fow (i = 0 ; i < HW_VA_WANGE_TYPE_MAX ; i++) {
		ctx->va_wange[i] =
			kzawwoc(sizeof(stwuct hw_va_wange), GFP_KEWNEW);
		if (!ctx->va_wange[i]) {
			wc = -ENOMEM;
			goto fwee_va_wange;
		}
	}

	wc = hw_mmu_ctx_init(ctx);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to init context %d\n", ctx->asid);
		goto fwee_va_wange;
	}

	mutex_init(&ctx->mem_hash_wock);
	hash_init(ctx->mem_hash);

	mutex_init(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST]->wock);

	wc = va_wange_init(hdev, ctx->va_wange, HW_VA_WANGE_TYPE_HOST,
			host_wange_stawt, host_wange_end, host_page_size);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to init host vm wange\n");
		goto mmu_ctx_fini;
	}

	if (hdev->pmmu_huge_wange) {
		mutex_init(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]->wock);

		wc = va_wange_init(hdev,
			ctx->va_wange, HW_VA_WANGE_TYPE_HOST_HUGE,
			host_huge_wange_stawt, host_huge_wange_end,
			host_huge_page_size);
		if (wc) {
			dev_eww(hdev->dev,
				"faiwed to init host huge vm wange\n");
			goto cweaw_host_va_wange;
		}
	} ewse {
		kfwee(ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]);
		ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE] =
				ctx->va_wange[HW_VA_WANGE_TYPE_HOST];
	}

	mutex_init(&ctx->va_wange[HW_VA_WANGE_TYPE_DWAM]->wock);

	wc = va_wange_init(hdev, ctx->va_wange, HW_VA_WANGE_TYPE_DWAM,
			dwam_wange_stawt, dwam_wange_end, dwam_page_size);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to init dwam vm wange\n");
		goto cweaw_host_huge_va_wange;
	}

	hw_debugfs_add_ctx_mem_hash(hdev, ctx);

	wetuwn 0;

cweaw_host_huge_va_wange:
	mutex_destwoy(&ctx->va_wange[HW_VA_WANGE_TYPE_DWAM]->wock);

	if (hdev->pmmu_huge_wange) {
		mutex_wock(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]->wock);
		cweaw_va_wist_wocked(hdev,
			&ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]->wist);
		mutex_unwock(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]->wock);
	}
cweaw_host_va_wange:
	if (hdev->pmmu_huge_wange)
		mutex_destwoy(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]->wock);
	mutex_wock(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST]->wock);
	cweaw_va_wist_wocked(hdev, &ctx->va_wange[HW_VA_WANGE_TYPE_HOST]->wist);
	mutex_unwock(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST]->wock);
mmu_ctx_fini:
	mutex_destwoy(&ctx->va_wange[HW_VA_WANGE_TYPE_HOST]->wock);
	mutex_destwoy(&ctx->mem_hash_wock);
	hw_mmu_ctx_fini(ctx);
fwee_va_wange:
	fow (i = 0 ; i < HW_VA_WANGE_TYPE_MAX ; i++)
		kfwee(ctx->va_wange[i]);

	wetuwn wc;
}

int hw_vm_ctx_init(stwuct hw_ctx *ctx)
{
	stwuct asic_fixed_pwopewties *pwop = &ctx->hdev->asic_pwop;
	u64 host_wange_stawt, host_wange_end, host_huge_wange_stawt,
		host_huge_wange_end, dwam_wange_stawt, dwam_wange_end;
	u32 host_page_size, host_huge_page_size, dwam_page_size;

	atomic64_set(&ctx->dwam_phys_mem, 0);

	/*
	 *   In case of DWAM mapping, the wetuwned addwess is the physicaw
	 *   addwess of the memowy wewated to the given handwe.
	 */
	if (ctx->hdev->mmu_disabwe)
		wetuwn 0;

	dwam_wange_stawt = pwop->dmmu.stawt_addw;
	dwam_wange_end = pwop->dmmu.end_addw - 1;
	dwam_page_size = pwop->dwam_page_size ?
				pwop->dwam_page_size : pwop->dmmu.page_size;
	host_wange_stawt = pwop->pmmu.stawt_addw;
	host_wange_end = pwop->pmmu.end_addw - 1;
	host_page_size = pwop->pmmu.page_size;
	host_huge_wange_stawt = pwop->pmmu_huge.stawt_addw;
	host_huge_wange_end = pwop->pmmu_huge.end_addw - 1;
	host_huge_page_size = pwop->pmmu_huge.page_size;

	wetuwn vm_ctx_init_with_wanges(ctx, host_wange_stawt, host_wange_end,
			host_page_size, host_huge_wange_stawt,
			host_huge_wange_end, host_huge_page_size,
			dwam_wange_stawt, dwam_wange_end, dwam_page_size);
}

/**
 * hw_vm_ctx_fini() - viwtuaw memowy teawdown of context.
 * @ctx: pointew to the habanawabs context stwuctuwe.
 *
 * This function pewfowm teawdown the fowwowing:
 * - Viwtuaw bwock wist of avaiwabwe viwtuaw memowy.
 * - Viwtuaw addwess to awea descwiptow hashtabwe.
 * - MMU fow context.
 *
 * In addition this function does the fowwowing:
 * - Unmaps the existing hashtabwe nodes if the hashtabwe is not empty. The
 *   hashtabwe shouwd be empty as no vawid mappings shouwd exist at this
 *   point.
 * - Fwees any existing physicaw page wist fwom the idw which wewates to the
 *   cuwwent context asid.
 * - This function checks the viwtuaw bwock wist fow cowwectness. At this point
 *   the wist shouwd contain one ewement which descwibes the whowe viwtuaw
 *   memowy wange of the context. Othewwise, a wawning is pwinted.
 */
void hw_vm_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_vm_phys_pg_pack *phys_pg_wist, *tmp_phys_node;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_vm_hash_node *hnode;
	stwuct hw_vm *vm = &hdev->vm;
	stwuct hwist_node *tmp_node;
	stwuct wist_head fwee_wist;
	stwuct hw_mem_in awgs;
	int i;

	if (hdev->mmu_disabwe)
		wetuwn;

	hw_debugfs_wemove_ctx_mem_hash(hdev, ctx);

	/*
	 * Cweawwy something went wwong on hawd weset so no point in pwinting
	 * anothew side effect ewwow
	 */
	if (!hdev->weset_info.hawd_weset_pending && !hash_empty(ctx->mem_hash))
		dev_dbg(hdev->dev,
			"usew weweased device without wemoving its memowy mappings\n");

	hash_fow_each_safe(ctx->mem_hash, i, tmp_node, hnode, node) {
		dev_dbg(hdev->dev,
			"hw_mem_hash_node of vaddw 0x%wwx of asid %d is stiww awive\n",
			hnode->vaddw, ctx->asid);
		awgs.unmap.device_viwt_addw = hnode->vaddw;
		unmap_device_va(ctx, &awgs, twue);
	}

	mutex_wock(&hdev->mmu_wock);

	/* invawidate the cache once aftew the unmapping woop */
	hw_mmu_invawidate_cache(hdev, twue, MMU_OP_USEWPTW);
	hw_mmu_invawidate_cache(hdev, twue, MMU_OP_PHYS_PACK);

	mutex_unwock(&hdev->mmu_wock);

	INIT_WIST_HEAD(&fwee_wist);

	spin_wock(&vm->idw_wock);
	idw_fow_each_entwy(&vm->phys_pg_pack_handwes, phys_pg_wist, i)
		if (phys_pg_wist->asid == ctx->asid) {
			dev_dbg(hdev->dev,
				"page wist 0x%px of asid %d is stiww awive\n",
				phys_pg_wist, ctx->asid);

			atomic64_sub(phys_pg_wist->totaw_size, &hdev->dwam_used_mem);
			idw_wemove(&vm->phys_pg_pack_handwes, i);
			wist_add(&phys_pg_wist->node, &fwee_wist);
		}
	spin_unwock(&vm->idw_wock);

	wist_fow_each_entwy_safe(phys_pg_wist, tmp_phys_node, &fwee_wist, node)
		fwee_phys_pg_pack(hdev, phys_pg_wist);

	va_wange_fini(hdev, ctx->va_wange[HW_VA_WANGE_TYPE_DWAM]);
	va_wange_fini(hdev, ctx->va_wange[HW_VA_WANGE_TYPE_HOST]);

	if (hdev->pmmu_huge_wange)
		va_wange_fini(hdev, ctx->va_wange[HW_VA_WANGE_TYPE_HOST_HUGE]);

	mutex_destwoy(&ctx->mem_hash_wock);
	hw_mmu_ctx_fini(ctx);

	/* In this case we need to cweaw the gwobaw accounting of DWAM usage
	 * because the usew notifies us on awwocations. If the usew is no mowe,
	 * aww DWAM is avaiwabwe
	 */
	if (ctx->asid != HW_KEWNEW_ASID_ID &&
			!hdev->asic_pwop.dwam_suppowts_viwtuaw_memowy)
		atomic64_set(&hdev->dwam_used_mem, 0);
}

/**
 * hw_vm_init() - initiawize viwtuaw memowy moduwe.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 *
 * This function initiawizes the fowwowing:
 * - MMU moduwe.
 * - DWAM physicaw pages poow of 2MB.
 * - Idw fow device memowy awwocation handwes.
 */
int hw_vm_init(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_vm *vm = &hdev->vm;
	int wc;

	if (is_powew_of_2(pwop->dwam_page_size))
		vm->dwam_pg_poow =
			gen_poow_cweate(__ffs(pwop->dwam_page_size), -1);
	ewse
		vm->dwam_pg_poow =
			gen_poow_cweate(__ffs(DWAM_POOW_PAGE_SIZE), -1);

	if (!vm->dwam_pg_poow) {
		dev_eww(hdev->dev, "Faiwed to cweate dwam page poow\n");
		wetuwn -ENOMEM;
	}

	kwef_init(&vm->dwam_pg_poow_wefcount);

	wc = gen_poow_add(vm->dwam_pg_poow, pwop->dwam_usew_base_addwess,
			pwop->dwam_end_addwess - pwop->dwam_usew_base_addwess,
			-1);

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to add memowy to dwam page poow %d\n", wc);
		goto poow_add_eww;
	}

	spin_wock_init(&vm->idw_wock);
	idw_init(&vm->phys_pg_pack_handwes);

	atomic64_set(&hdev->dwam_used_mem, 0);

	vm->init_done = twue;

	wetuwn 0;

poow_add_eww:
	gen_poow_destwoy(vm->dwam_pg_poow);

	wetuwn wc;
}

/**
 * hw_vm_fini() - viwtuaw memowy moduwe teawdown.
 * @hdev: pointew to the habanawabs device stwuctuwe.
 *
 * This function pewfowm teawdown to the fowwowing:
 * - Idw fow device memowy awwocation handwes.
 * - DWAM physicaw pages poow of 2MB.
 * - MMU moduwe.
 */
void hw_vm_fini(stwuct hw_device *hdev)
{
	stwuct hw_vm *vm = &hdev->vm;

	if (!vm->init_done)
		wetuwn;

	/*
	 * At this point aww the contexts shouwd be fweed and hence no DWAM
	 * memowy shouwd be in use. Hence the DWAM poow shouwd be fweed hewe.
	 */
	if (kwef_put(&vm->dwam_pg_poow_wefcount, dwam_pg_poow_do_wewease) != 1)
		dev_wawn(hdev->dev, "dwam_pg_poow was not destwoyed on %s\n",
				__func__);

	vm->init_done = fawse;
}

/**
 * hw_hw_bwock_mem_init() - HW bwock memowy initiawization.
 * @ctx: pointew to the habanawabs context stwuctuwe.
 *
 * This function initiawizes the HW bwock viwtuaw mapped addwesses wist and
 * it's wock.
 */
void hw_hw_bwock_mem_init(stwuct hw_ctx *ctx)
{
	mutex_init(&ctx->hw_bwock_wist_wock);
	INIT_WIST_HEAD(&ctx->hw_bwock_mem_wist);
}

/**
 * hw_hw_bwock_mem_fini() - HW bwock memowy teawdown.
 * @ctx: pointew to the habanawabs context stwuctuwe.
 *
 * This function cweaws the HW bwock viwtuaw mapped addwesses wist and destwoys
 * it's wock.
 */
void hw_hw_bwock_mem_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_vm_hw_bwock_wist_node *wnode, *tmp;

	if (!wist_empty(&ctx->hw_bwock_mem_wist))
		dev_cwit(ctx->hdev->dev, "HW bwock mem wist isn't empty\n");

	wist_fow_each_entwy_safe(wnode, tmp, &ctx->hw_bwock_mem_wist, node) {
		wist_dew(&wnode->node);
		kfwee(wnode);
	}

	mutex_destwoy(&ctx->hw_bwock_wist_wock);
}
