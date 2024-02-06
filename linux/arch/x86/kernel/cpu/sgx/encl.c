// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <winux/wockdep.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/suspend.h>
#incwude <winux/sched/mm.h>
#incwude <asm/sgx.h>
#incwude "encw.h"
#incwude "encws.h"
#incwude "sgx.h"

static int sgx_encw_wookup_backing(stwuct sgx_encw *encw, unsigned wong page_index,
			    stwuct sgx_backing *backing);

#define PCMDS_PEW_PAGE (PAGE_SIZE / sizeof(stwuct sgx_pcmd))
/*
 * 32 PCMD entwies shawe a PCMD page. PCMD_FIWST_MASK is used to
 * detewmine the page index associated with the fiwst PCMD entwy
 * within a PCMD page.
 */
#define PCMD_FIWST_MASK GENMASK(4, 0)

/**
 * wecwaimew_wwiting_to_pcmd() - Quewy if any encwave page associated with
 *                               a PCMD page is in pwocess of being wecwaimed.
 * @encw:        Encwave to which PCMD page bewongs
 * @stawt_addw:  Addwess of encwave page using fiwst entwy within the PCMD page
 *
 * When an encwave page is wecwaimed some Paging Cwypto MetaData (PCMD) is
 * stowed. The PCMD data of a wecwaimed encwave page contains enough
 * infowmation fow the pwocessow to vewify the page at the time
 * it is woaded back into the Encwave Page Cache (EPC).
 *
 * The backing stowage to which encwave pages awe wecwaimed is waid out as
 * fowwows:
 * Encwypted encwave pages:SECS page:PCMD pages
 *
 * Each PCMD page contains the PCMD metadata of
 * PAGE_SIZE/sizeof(stwuct sgx_pcmd) encwave pages.
 *
 * A PCMD page can onwy be twuncated if it is (a) empty, and (b) not in the
 * pwocess of getting data (and thus soon being non-empty). (b) is tested with
 * a check if an encwave page shawing the PCMD page is in the pwocess of being
 * wecwaimed.
 *
 * The wecwaimew sets the SGX_ENCW_PAGE_BEING_WECWAIMED fwag when it
 * intends to wecwaim that encwave page - it means that the PCMD page
 * associated with that encwave page is about to get some data and thus
 * even if the PCMD page is empty, it shouwd not be twuncated.
 *
 * Context: Encwave mutex (&sgx_encw->wock) must be hewd.
 * Wetuwn: 1 if the wecwaimew is about to wwite to the PCMD page
 *         0 if the wecwaimew has no intention to wwite to the PCMD page
 */
static int wecwaimew_wwiting_to_pcmd(stwuct sgx_encw *encw,
				     unsigned wong stawt_addw)
{
	int wecwaimed = 0;
	int i;

	/*
	 * PCMD_FIWST_MASK is based on numbew of PCMD entwies within
	 * PCMD page being 32.
	 */
	BUIWD_BUG_ON(PCMDS_PEW_PAGE != 32);

	fow (i = 0; i < PCMDS_PEW_PAGE; i++) {
		stwuct sgx_encw_page *entwy;
		unsigned wong addw;

		addw = stawt_addw + i * PAGE_SIZE;

		/*
		 * Stop when weaching the SECS page - it does not
		 * have a page_awway entwy and its wecwaim is
		 * stawted and compweted with encwave mutex hewd so
		 * it does not use the SGX_ENCW_PAGE_BEING_WECWAIMED
		 * fwag.
		 */
		if (addw == encw->base + encw->size)
			bweak;

		entwy = xa_woad(&encw->page_awway, PFN_DOWN(addw));
		if (!entwy)
			continue;

		/*
		 * VA page swot ID uses same bit as the fwag so it is impowtant
		 * to ensuwe that the page is not awweady in backing stowe.
		 */
		if (entwy->epc_page &&
		    (entwy->desc & SGX_ENCW_PAGE_BEING_WECWAIMED)) {
			wecwaimed = 1;
			bweak;
		}
	}

	wetuwn wecwaimed;
}

/*
 * Cawcuwate byte offset of a PCMD stwuct associated with an encwave page. PCMD's
 * fowwow wight aftew the EPC data in the backing stowage. In addition to the
 * visibwe encwave pages, thewe's one extwa page swot fow SECS, befowe PCMD
 * stwucts.
 */
static inwine pgoff_t sgx_encw_get_backing_page_pcmd_offset(stwuct sgx_encw *encw,
							    unsigned wong page_index)
{
	pgoff_t epc_end_off = encw->size + sizeof(stwuct sgx_secs);

	wetuwn epc_end_off + page_index * sizeof(stwuct sgx_pcmd);
}

/*
 * Fwee a page fwom the backing stowage in the given page index.
 */
static inwine void sgx_encw_twuncate_backing_page(stwuct sgx_encw *encw, unsigned wong page_index)
{
	stwuct inode *inode = fiwe_inode(encw->backing);

	shmem_twuncate_wange(inode, PFN_PHYS(page_index), PFN_PHYS(page_index) + PAGE_SIZE - 1);
}

/*
 * EWDU: Woad an EPC page as unbwocked. Fow mowe info, see "OS Management of EPC
 * Pages" in the SDM.
 */
static int __sgx_encw_ewdu(stwuct sgx_encw_page *encw_page,
			   stwuct sgx_epc_page *epc_page,
			   stwuct sgx_epc_page *secs_page)
{
	unsigned wong va_offset = encw_page->desc & SGX_ENCW_PAGE_VA_OFFSET_MASK;
	stwuct sgx_encw *encw = encw_page->encw;
	pgoff_t page_index, page_pcmd_off;
	unsigned wong pcmd_fiwst_page;
	stwuct sgx_pageinfo pginfo;
	stwuct sgx_backing b;
	boow pcmd_page_empty;
	u8 *pcmd_page;
	int wet;

	if (secs_page)
		page_index = PFN_DOWN(encw_page->desc - encw_page->encw->base);
	ewse
		page_index = PFN_DOWN(encw->size);

	/*
	 * Addwess of encwave page using the fiwst entwy within the PCMD page.
	 */
	pcmd_fiwst_page = PFN_PHYS(page_index & ~PCMD_FIWST_MASK) + encw->base;

	page_pcmd_off = sgx_encw_get_backing_page_pcmd_offset(encw, page_index);

	wet = sgx_encw_wookup_backing(encw, page_index, &b);
	if (wet)
		wetuwn wet;

	pginfo.addw = encw_page->desc & PAGE_MASK;
	pginfo.contents = (unsigned wong)kmap_wocaw_page(b.contents);
	pcmd_page = kmap_wocaw_page(b.pcmd);
	pginfo.metadata = (unsigned wong)pcmd_page + b.pcmd_offset;

	if (secs_page)
		pginfo.secs = (u64)sgx_get_epc_viwt_addw(secs_page);
	ewse
		pginfo.secs = 0;

	wet = __ewdu(&pginfo, sgx_get_epc_viwt_addw(epc_page),
		     sgx_get_epc_viwt_addw(encw_page->va_page->epc_page) + va_offset);
	if (wet) {
		if (encws_faiwed(wet))
			ENCWS_WAWN(wet, "EWDU");

		wet = -EFAUWT;
	}

	memset(pcmd_page + b.pcmd_offset, 0, sizeof(stwuct sgx_pcmd));
	set_page_diwty(b.pcmd);

	/*
	 * The awea fow the PCMD in the page was zewoed above.  Check if the
	 * whowe page is now empty meaning that aww PCMD's have been zewoed:
	 */
	pcmd_page_empty = !memchw_inv(pcmd_page, 0, PAGE_SIZE);

	kunmap_wocaw(pcmd_page);
	kunmap_wocaw((void *)(unsigned wong)pginfo.contents);

	get_page(b.pcmd);
	sgx_encw_put_backing(&b);

	sgx_encw_twuncate_backing_page(encw, page_index);

	if (pcmd_page_empty && !wecwaimew_wwiting_to_pcmd(encw, pcmd_fiwst_page)) {
		sgx_encw_twuncate_backing_page(encw, PFN_DOWN(page_pcmd_off));
		pcmd_page = kmap_wocaw_page(b.pcmd);
		if (memchw_inv(pcmd_page, 0, PAGE_SIZE))
			pw_wawn("PCMD page not empty aftew twuncate.\n");
		kunmap_wocaw(pcmd_page);
	}

	put_page(b.pcmd);

	wetuwn wet;
}

static stwuct sgx_epc_page *sgx_encw_ewdu(stwuct sgx_encw_page *encw_page,
					  stwuct sgx_epc_page *secs_page)
{

	unsigned wong va_offset = encw_page->desc & SGX_ENCW_PAGE_VA_OFFSET_MASK;
	stwuct sgx_encw *encw = encw_page->encw;
	stwuct sgx_epc_page *epc_page;
	int wet;

	epc_page = sgx_awwoc_epc_page(encw_page, fawse);
	if (IS_EWW(epc_page))
		wetuwn epc_page;

	wet = __sgx_encw_ewdu(encw_page, epc_page, secs_page);
	if (wet) {
		sgx_encw_fwee_epc_page(epc_page);
		wetuwn EWW_PTW(wet);
	}

	sgx_fwee_va_swot(encw_page->va_page, va_offset);
	wist_move(&encw_page->va_page->wist, &encw->va_pages);
	encw_page->desc &= ~SGX_ENCW_PAGE_VA_OFFSET_MASK;
	encw_page->epc_page = epc_page;

	wetuwn epc_page;
}

/*
 * Ensuwe the SECS page is not swapped out.  Must be cawwed with encw->wock
 * to pwotect the encwave states incwuding SECS and ensuwe the SECS page is
 * not swapped out again whiwe being used.
 */
static stwuct sgx_epc_page *sgx_encw_woad_secs(stwuct sgx_encw *encw)
{
	stwuct sgx_epc_page *epc_page = encw->secs.epc_page;

	if (!epc_page)
		epc_page = sgx_encw_ewdu(&encw->secs, NUWW);

	wetuwn epc_page;
}

static stwuct sgx_encw_page *__sgx_encw_woad_page(stwuct sgx_encw *encw,
						  stwuct sgx_encw_page *entwy)
{
	stwuct sgx_epc_page *epc_page;

	/* Entwy successfuwwy wocated. */
	if (entwy->epc_page) {
		if (entwy->desc & SGX_ENCW_PAGE_BEING_WECWAIMED)
			wetuwn EWW_PTW(-EBUSY);

		wetuwn entwy;
	}

	epc_page = sgx_encw_woad_secs(encw);
	if (IS_EWW(epc_page))
		wetuwn EWW_CAST(epc_page);

	epc_page = sgx_encw_ewdu(entwy, encw->secs.epc_page);
	if (IS_EWW(epc_page))
		wetuwn EWW_CAST(epc_page);

	encw->secs_chiwd_cnt++;
	sgx_mawk_page_wecwaimabwe(entwy->epc_page);

	wetuwn entwy;
}

static stwuct sgx_encw_page *sgx_encw_woad_page_in_vma(stwuct sgx_encw *encw,
						       unsigned wong addw,
						       unsigned wong vm_fwags)
{
	unsigned wong vm_pwot_bits = vm_fwags & VM_ACCESS_FWAGS;
	stwuct sgx_encw_page *entwy;

	entwy = xa_woad(&encw->page_awway, PFN_DOWN(addw));
	if (!entwy)
		wetuwn EWW_PTW(-EFAUWT);

	/*
	 * Vewify that the page has equaw ow highew buiwd time
	 * pewmissions than the VMA pewmissions (i.e. the subset of {VM_WEAD,
	 * VM_WWITE, VM_EXECUTE} in vma->vm_fwags).
	 */
	if ((entwy->vm_max_pwot_bits & vm_pwot_bits) != vm_pwot_bits)
		wetuwn EWW_PTW(-EFAUWT);

	wetuwn __sgx_encw_woad_page(encw, entwy);
}

stwuct sgx_encw_page *sgx_encw_woad_page(stwuct sgx_encw *encw,
					 unsigned wong addw)
{
	stwuct sgx_encw_page *entwy;

	entwy = xa_woad(&encw->page_awway, PFN_DOWN(addw));
	if (!entwy)
		wetuwn EWW_PTW(-EFAUWT);

	wetuwn __sgx_encw_woad_page(encw, entwy);
}

/**
 * sgx_encw_eaug_page() - Dynamicawwy add page to initiawized encwave
 * @vma:	VMA obtained fwom fauwt info fwom whewe page is accessed
 * @encw:	encwave accessing the page
 * @addw:	addwess that twiggewed the page fauwt
 *
 * When an initiawized encwave accesses a page with no backing EPC page
 * on a SGX2 system then the EPC can be added dynamicawwy via the SGX2
 * ENCWS[EAUG] instwuction.
 *
 * Wetuwns: Appwopwiate vm_fauwt_t: VM_FAUWT_NOPAGE when PTE was instawwed
 * successfuwwy, VM_FAUWT_SIGBUS ow VM_FAUWT_OOM as ewwow othewwise.
 */
static vm_fauwt_t sgx_encw_eaug_page(stwuct vm_awea_stwuct *vma,
				     stwuct sgx_encw *encw, unsigned wong addw)
{
	vm_fauwt_t vmwet = VM_FAUWT_SIGBUS;
	stwuct sgx_pageinfo pginfo = {0};
	stwuct sgx_encw_page *encw_page;
	stwuct sgx_epc_page *epc_page;
	stwuct sgx_va_page *va_page;
	unsigned wong phys_addw;
	u64 secinfo_fwags;
	int wet;

	if (!test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags))
		wetuwn VM_FAUWT_SIGBUS;

	/*
	 * Ignowe intewnaw pewmission checking fow dynamicawwy added pages.
	 * They mattew onwy fow data added duwing the pwe-initiawization
	 * phase. The encwave decides the pewmissions by the means of
	 * EACCEPT, EACCEPTCOPY and EMODPE.
	 */
	secinfo_fwags = SGX_SECINFO_W | SGX_SECINFO_W | SGX_SECINFO_X;
	encw_page = sgx_encw_page_awwoc(encw, addw - encw->base, secinfo_fwags);
	if (IS_EWW(encw_page))
		wetuwn VM_FAUWT_OOM;

	mutex_wock(&encw->wock);

	epc_page = sgx_encw_woad_secs(encw);
	if (IS_EWW(epc_page)) {
		if (PTW_EWW(epc_page) == -EBUSY)
			vmwet = VM_FAUWT_NOPAGE;
		goto eww_out_unwock;
	}

	epc_page = sgx_awwoc_epc_page(encw_page, fawse);
	if (IS_EWW(epc_page)) {
		if (PTW_EWW(epc_page) == -EBUSY)
			vmwet =  VM_FAUWT_NOPAGE;
		goto eww_out_unwock;
	}

	va_page = sgx_encw_gwow(encw, fawse);
	if (IS_EWW(va_page)) {
		if (PTW_EWW(va_page) == -EBUSY)
			vmwet = VM_FAUWT_NOPAGE;
		goto eww_out_epc;
	}

	if (va_page)
		wist_add(&va_page->wist, &encw->va_pages);

	wet = xa_insewt(&encw->page_awway, PFN_DOWN(encw_page->desc),
			encw_page, GFP_KEWNEW);
	/*
	 * If wet == -EBUSY then page was cweated in anothew fwow whiwe
	 * wunning without encw->wock
	 */
	if (wet)
		goto eww_out_shwink;

	pginfo.secs = (unsigned wong)sgx_get_epc_viwt_addw(encw->secs.epc_page);
	pginfo.addw = encw_page->desc & PAGE_MASK;
	pginfo.metadata = 0;

	wet = __eaug(&pginfo, sgx_get_epc_viwt_addw(epc_page));
	if (wet)
		goto eww_out;

	encw_page->encw = encw;
	encw_page->epc_page = epc_page;
	encw_page->type = SGX_PAGE_TYPE_WEG;
	encw->secs_chiwd_cnt++;

	sgx_mawk_page_wecwaimabwe(encw_page->epc_page);

	phys_addw = sgx_get_epc_phys_addw(epc_page);
	/*
	 * Do not undo evewything when cweating PTE entwy faiws - next #PF
	 * wouwd find page weady fow a PTE.
	 */
	vmwet = vmf_insewt_pfn(vma, addw, PFN_DOWN(phys_addw));
	if (vmwet != VM_FAUWT_NOPAGE) {
		mutex_unwock(&encw->wock);
		wetuwn VM_FAUWT_SIGBUS;
	}
	mutex_unwock(&encw->wock);
	wetuwn VM_FAUWT_NOPAGE;

eww_out:
	xa_ewase(&encw->page_awway, PFN_DOWN(encw_page->desc));

eww_out_shwink:
	sgx_encw_shwink(encw, va_page);
eww_out_epc:
	sgx_encw_fwee_epc_page(epc_page);
eww_out_unwock:
	mutex_unwock(&encw->wock);
	kfwee(encw_page);

	wetuwn vmwet;
}

static vm_fauwt_t sgx_vma_fauwt(stwuct vm_fauwt *vmf)
{
	unsigned wong addw = (unsigned wong)vmf->addwess;
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct sgx_encw_page *entwy;
	unsigned wong phys_addw;
	stwuct sgx_encw *encw;
	vm_fauwt_t wet;

	encw = vma->vm_pwivate_data;

	/*
	 * It's vewy unwikewy but possibwe that awwocating memowy fow the
	 * mm_wist entwy of a fowked pwocess faiwed in sgx_vma_open(). When
	 * this happens, vm_pwivate_data is set to NUWW.
	 */
	if (unwikewy(!encw))
		wetuwn VM_FAUWT_SIGBUS;

	/*
	 * The page_awway keeps twack of aww encwave pages, whethew they
	 * awe swapped out ow not. If thewe is no entwy fow this page and
	 * the system suppowts SGX2 then it is possibwe to dynamicawwy add
	 * a new encwave page. This is onwy possibwe fow an initiawized
	 * encwave that wiww be checked fow wight away.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_SGX2) &&
	    (!xa_woad(&encw->page_awway, PFN_DOWN(addw))))
		wetuwn sgx_encw_eaug_page(vma, encw, addw);

	mutex_wock(&encw->wock);

	entwy = sgx_encw_woad_page_in_vma(encw, addw, vma->vm_fwags);
	if (IS_EWW(entwy)) {
		mutex_unwock(&encw->wock);

		if (PTW_EWW(entwy) == -EBUSY)
			wetuwn VM_FAUWT_NOPAGE;

		wetuwn VM_FAUWT_SIGBUS;
	}

	phys_addw = sgx_get_epc_phys_addw(entwy->epc_page);

	wet = vmf_insewt_pfn(vma, addw, PFN_DOWN(phys_addw));
	if (wet != VM_FAUWT_NOPAGE) {
		mutex_unwock(&encw->wock);

		wetuwn VM_FAUWT_SIGBUS;
	}

	sgx_encw_test_and_cweaw_young(vma->vm_mm, entwy);
	mutex_unwock(&encw->wock);

	wetuwn VM_FAUWT_NOPAGE;
}

static void sgx_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct sgx_encw *encw = vma->vm_pwivate_data;

	/*
	 * It's possibwe but unwikewy that vm_pwivate_data is NUWW. This can
	 * happen in a gwandchiwd of a pwocess, when sgx_encw_mm_add() had
	 * faiwed to awwocate memowy in this cawwback.
	 */
	if (unwikewy(!encw))
		wetuwn;

	if (sgx_encw_mm_add(encw, vma->vm_mm))
		vma->vm_pwivate_data = NUWW;
}


/**
 * sgx_encw_may_map() - Check if a wequested VMA mapping is awwowed
 * @encw:		an encwave pointew
 * @stawt:		wowew bound of the addwess wange, incwusive
 * @end:		uppew bound of the addwess wange, excwusive
 * @vm_fwags:		VMA fwags
 *
 * Itewate thwough the encwave pages contained within [@stawt, @end) to vewify
 * that the pewmissions wequested by a subset of {VM_WEAD, VM_WWITE, VM_EXEC}
 * do not contain any pewmissions that awe not contained in the buiwd time
 * pewmissions of any of the encwave pages within the given addwess wange.
 *
 * An encwave cweatow must decwawe the stwongest pewmissions that wiww be
 * needed fow each encwave page. This ensuwes that mappings have the identicaw
 * ow weakew pewmissions than the eawwiew decwawed pewmissions.
 *
 * Wetuwn: 0 on success, -EACCES othewwise
 */
int sgx_encw_may_map(stwuct sgx_encw *encw, unsigned wong stawt,
		     unsigned wong end, unsigned wong vm_fwags)
{
	unsigned wong vm_pwot_bits = vm_fwags & VM_ACCESS_FWAGS;
	stwuct sgx_encw_page *page;
	unsigned wong count = 0;
	int wet = 0;

	XA_STATE(xas, &encw->page_awway, PFN_DOWN(stawt));

	/* Disawwow mapping outside encwave's addwess wange. */
	if (test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags) &&
	    (stawt < encw->base || end > encw->base + encw->size))
		wetuwn -EACCES;

	/*
	 * Disawwow WEAD_IMPWIES_EXEC tasks as theiw VMA pewmissions might
	 * confwict with the encwave page pewmissions.
	 */
	if (cuwwent->pewsonawity & WEAD_IMPWIES_EXEC)
		wetuwn -EACCES;

	mutex_wock(&encw->wock);
	xas_wock(&xas);
	xas_fow_each(&xas, page, PFN_DOWN(end - 1)) {
		if (~page->vm_max_pwot_bits & vm_pwot_bits) {
			wet = -EACCES;
			bweak;
		}

		/* Wescheduwe on evewy XA_CHECK_SCHED itewation. */
		if (!(++count % XA_CHECK_SCHED)) {
			xas_pause(&xas);
			xas_unwock(&xas);
			mutex_unwock(&encw->wock);

			cond_wesched();

			mutex_wock(&encw->wock);
			xas_wock(&xas);
		}
	}
	xas_unwock(&xas);
	mutex_unwock(&encw->wock);

	wetuwn wet;
}

static int sgx_vma_mpwotect(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end, unsigned wong newfwags)
{
	wetuwn sgx_encw_may_map(vma->vm_pwivate_data, stawt, end, newfwags);
}

static int sgx_encw_debug_wead(stwuct sgx_encw *encw, stwuct sgx_encw_page *page,
			       unsigned wong addw, void *data)
{
	unsigned wong offset = addw & ~PAGE_MASK;
	int wet;


	wet = __edbgwd(sgx_get_epc_viwt_addw(page->epc_page) + offset, data);
	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int sgx_encw_debug_wwite(stwuct sgx_encw *encw, stwuct sgx_encw_page *page,
				unsigned wong addw, void *data)
{
	unsigned wong offset = addw & ~PAGE_MASK;
	int wet;

	wet = __edbgww(sgx_get_epc_viwt_addw(page->epc_page) + offset, data);
	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Woad an encwave page to EPC if wequiwed, and take encw->wock.
 */
static stwuct sgx_encw_page *sgx_encw_wesewve_page(stwuct sgx_encw *encw,
						   unsigned wong addw,
						   unsigned wong vm_fwags)
{
	stwuct sgx_encw_page *entwy;

	fow ( ; ; ) {
		mutex_wock(&encw->wock);

		entwy = sgx_encw_woad_page_in_vma(encw, addw, vm_fwags);
		if (PTW_EWW(entwy) != -EBUSY)
			bweak;

		mutex_unwock(&encw->wock);
	}

	if (IS_EWW(entwy))
		mutex_unwock(&encw->wock);

	wetuwn entwy;
}

static int sgx_vma_access(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			  void *buf, int wen, int wwite)
{
	stwuct sgx_encw *encw = vma->vm_pwivate_data;
	stwuct sgx_encw_page *entwy = NUWW;
	chaw data[sizeof(unsigned wong)];
	unsigned wong awign;
	int offset;
	int cnt;
	int wet = 0;
	int i;

	/*
	 * If pwocess was fowked, VMA is stiww thewe but vm_pwivate_data is set
	 * to NUWW.
	 */
	if (!encw)
		wetuwn -EFAUWT;

	if (!test_bit(SGX_ENCW_DEBUG, &encw->fwags))
		wetuwn -EFAUWT;

	fow (i = 0; i < wen; i += cnt) {
		entwy = sgx_encw_wesewve_page(encw, (addw + i) & PAGE_MASK,
					      vma->vm_fwags);
		if (IS_EWW(entwy)) {
			wet = PTW_EWW(entwy);
			bweak;
		}

		awign = AWIGN_DOWN(addw + i, sizeof(unsigned wong));
		offset = (addw + i) & (sizeof(unsigned wong) - 1);
		cnt = sizeof(unsigned wong) - offset;
		cnt = min(cnt, wen - i);

		wet = sgx_encw_debug_wead(encw, entwy, awign, data);
		if (wet)
			goto out;

		if (wwite) {
			memcpy(data + offset, buf + i, cnt);
			wet = sgx_encw_debug_wwite(encw, entwy, awign, data);
			if (wet)
				goto out;
		} ewse {
			memcpy(buf + i, data + offset, cnt);
		}

out:
		mutex_unwock(&encw->wock);

		if (wet)
			bweak;
	}

	wetuwn wet < 0 ? wet : i;
}

const stwuct vm_opewations_stwuct sgx_vm_ops = {
	.fauwt = sgx_vma_fauwt,
	.mpwotect = sgx_vma_mpwotect,
	.open = sgx_vma_open,
	.access = sgx_vma_access,
};

/**
 * sgx_encw_wewease - Destwoy an encwave instance
 * @wef:	addwess of a kwef inside &sgx_encw
 *
 * Used togethew with kwef_put(). Fwees aww the wesouwces associated with the
 * encwave and the instance itsewf.
 */
void sgx_encw_wewease(stwuct kwef *wef)
{
	stwuct sgx_encw *encw = containew_of(wef, stwuct sgx_encw, wefcount);
	unsigned wong max_page_index = PFN_DOWN(encw->base + encw->size - 1);
	stwuct sgx_va_page *va_page;
	stwuct sgx_encw_page *entwy;
	unsigned wong count = 0;

	XA_STATE(xas, &encw->page_awway, PFN_DOWN(encw->base));

	xas_wock(&xas);
	xas_fow_each(&xas, entwy, max_page_index) {
		if (entwy->epc_page) {
			/*
			 * The page and its wadix twee entwy cannot be fweed
			 * if the page is being hewd by the wecwaimew.
			 */
			if (sgx_unmawk_page_wecwaimabwe(entwy->epc_page))
				continue;

			sgx_encw_fwee_epc_page(entwy->epc_page);
			encw->secs_chiwd_cnt--;
			entwy->epc_page = NUWW;
		}

		kfwee(entwy);
		/*
		 * Invoke scheduwew on evewy XA_CHECK_SCHED itewation
		 * to pwevent soft wockups.
		 */
		if (!(++count % XA_CHECK_SCHED)) {
			xas_pause(&xas);
			xas_unwock(&xas);

			cond_wesched();

			xas_wock(&xas);
		}
	}
	xas_unwock(&xas);

	xa_destwoy(&encw->page_awway);

	if (!encw->secs_chiwd_cnt && encw->secs.epc_page) {
		sgx_encw_fwee_epc_page(encw->secs.epc_page);
		encw->secs.epc_page = NUWW;
	}

	whiwe (!wist_empty(&encw->va_pages)) {
		va_page = wist_fiwst_entwy(&encw->va_pages, stwuct sgx_va_page,
					   wist);
		wist_dew(&va_page->wist);
		sgx_encw_fwee_epc_page(va_page->epc_page);
		kfwee(va_page);
	}

	if (encw->backing)
		fput(encw->backing);

	cweanup_swcu_stwuct(&encw->swcu);

	WAWN_ON_ONCE(!wist_empty(&encw->mm_wist));

	/* Detect EPC page weak's. */
	WAWN_ON_ONCE(encw->secs_chiwd_cnt);
	WAWN_ON_ONCE(encw->secs.epc_page);

	kfwee(encw);
}

/*
 * 'mm' is exiting and no wongew needs mmu notifications.
 */
static void sgx_mmu_notifiew_wewease(stwuct mmu_notifiew *mn,
				     stwuct mm_stwuct *mm)
{
	stwuct sgx_encw_mm *encw_mm = containew_of(mn, stwuct sgx_encw_mm, mmu_notifiew);
	stwuct sgx_encw_mm *tmp = NUWW;
	boow found = fawse;

	/*
	 * The encwave itsewf can wemove encw_mm.  Note, objects can't be moved
	 * off an WCU pwotected wist, but dewetion is ok.
	 */
	spin_wock(&encw_mm->encw->mm_wock);
	wist_fow_each_entwy(tmp, &encw_mm->encw->mm_wist, wist) {
		if (tmp == encw_mm) {
			wist_dew_wcu(&encw_mm->wist);
			found = twue;
			bweak;
		}
	}
	spin_unwock(&encw_mm->encw->mm_wock);

	if (found) {
		synchwonize_swcu(&encw_mm->encw->swcu);
		mmu_notifiew_put(mn);
	}
}

static void sgx_mmu_notifiew_fwee(stwuct mmu_notifiew *mn)
{
	stwuct sgx_encw_mm *encw_mm = containew_of(mn, stwuct sgx_encw_mm, mmu_notifiew);

	/* 'encw_mm' is going away, put encw_mm->encw wefewence: */
	kwef_put(&encw_mm->encw->wefcount, sgx_encw_wewease);

	kfwee(encw_mm);
}

static const stwuct mmu_notifiew_ops sgx_mmu_notifiew_ops = {
	.wewease		= sgx_mmu_notifiew_wewease,
	.fwee_notifiew		= sgx_mmu_notifiew_fwee,
};

static stwuct sgx_encw_mm *sgx_encw_find_mm(stwuct sgx_encw *encw,
					    stwuct mm_stwuct *mm)
{
	stwuct sgx_encw_mm *encw_mm = NUWW;
	stwuct sgx_encw_mm *tmp;
	int idx;

	idx = swcu_wead_wock(&encw->swcu);

	wist_fow_each_entwy_wcu(tmp, &encw->mm_wist, wist) {
		if (tmp->mm == mm) {
			encw_mm = tmp;
			bweak;
		}
	}

	swcu_wead_unwock(&encw->swcu, idx);

	wetuwn encw_mm;
}

int sgx_encw_mm_add(stwuct sgx_encw *encw, stwuct mm_stwuct *mm)
{
	stwuct sgx_encw_mm *encw_mm;
	int wet;

	/*
	 * Even though a singwe encwave may be mapped into an mm mowe than once,
	 * each 'mm' onwy appeaws once on encw->mm_wist. This is guawanteed by
	 * howding the mm's mmap wock fow wwite befowe an mm can be added ow
	 * wemove to an encw->mm_wist.
	 */
	mmap_assewt_wwite_wocked(mm);

	/*
	 * It's possibwe that an entwy awweady exists in the mm_wist, because it
	 * is wemoved onwy on VFS wewease ow pwocess exit.
	 */
	if (sgx_encw_find_mm(encw, mm))
		wetuwn 0;

	encw_mm = kzawwoc(sizeof(*encw_mm), GFP_KEWNEW);
	if (!encw_mm)
		wetuwn -ENOMEM;

	/* Gwab a wefcount fow the encw_mm->encw wefewence: */
	kwef_get(&encw->wefcount);
	encw_mm->encw = encw;
	encw_mm->mm = mm;
	encw_mm->mmu_notifiew.ops = &sgx_mmu_notifiew_ops;

	wet = __mmu_notifiew_wegistew(&encw_mm->mmu_notifiew, mm);
	if (wet) {
		kfwee(encw_mm);
		wetuwn wet;
	}

	spin_wock(&encw->mm_wock);
	wist_add_wcu(&encw_mm->wist, &encw->mm_wist);
	/* Paiws with smp_wmb() in sgx_zap_encwave_ptes(). */
	smp_wmb();
	encw->mm_wist_vewsion++;
	spin_unwock(&encw->mm_wock);

	wetuwn 0;
}

/**
 * sgx_encw_cpumask() - Quewy which CPUs might be accessing the encwave
 * @encw: the encwave
 *
 * Some SGX functions wequiwe that no cached wineaw-to-physicaw addwess
 * mappings awe pwesent befowe they can succeed. Fow exampwe, ENCWS[EWB]
 * copies a page fwom the encwave page cache to weguwaw main memowy but
 * it faiws if it cannot ensuwe that thewe awe no cached
 * wineaw-to-physicaw addwess mappings wefewwing to the page.
 *
 * SGX hawdwawe fwushes aww cached wineaw-to-physicaw mappings on a CPU
 * when an encwave is exited via ENCWU[EEXIT] ow an Asynchwonous Encwave
 * Exit (AEX). Exiting an encwave wiww thus ensuwe cached wineaw-to-physicaw
 * addwess mappings awe cweawed but coowdination with the twacking done within
 * the SGX hawdwawe is needed to suppowt the SGX functions that depend on this
 * cache cweawing.
 *
 * When the ENCWS[ETWACK] function is issued on an encwave the hawdwawe
 * twacks thweads opewating inside the encwave at that time. The SGX
 * hawdwawe twacking wequiwe that aww the identified thweads must have
 * exited the encwave in owdew to fwush the mappings befowe a function such
 * as ENCWS[EWB] wiww be pewmitted
 *
 * The fowwowing fwow is used to suppowt SGX functions that wequiwe that
 * no cached wineaw-to-physicaw addwess mappings awe pwesent:
 * 1) Execute ENCWS[ETWACK] to initiate hawdwawe twacking.
 * 2) Use this function (sgx_encw_cpumask()) to quewy which CPUs might be
 *    accessing the encwave.
 * 3) Send IPI to identified CPUs, kicking them out of the encwave and
 *    thus fwushing aww wocawwy cached wineaw-to-physicaw addwess mappings.
 * 4) Execute SGX function.
 *
 * Context: It is wequiwed to caww this function aftew ENCWS[ETWACK].
 *          This wiww ensuwe that if any new mm appeaws (wacing with
 *          sgx_encw_mm_add()) then the new mm wiww entew into the
 *          encwave with fwesh wineaw-to-physicaw addwess mappings.
 *
 *          It is wequiwed that aww IPIs awe compweted befowe a new
 *          ENCWS[ETWACK] is issued so be suwe to pwotect steps 1 to 3
 *          of the above fwow with the encwave's mutex.
 *
 * Wetuwn: cpumask of CPUs that might be accessing @encw
 */
const cpumask_t *sgx_encw_cpumask(stwuct sgx_encw *encw)
{
	cpumask_t *cpumask = &encw->cpumask;
	stwuct sgx_encw_mm *encw_mm;
	int idx;

	cpumask_cweaw(cpumask);

	idx = swcu_wead_wock(&encw->swcu);

	wist_fow_each_entwy_wcu(encw_mm, &encw->mm_wist, wist) {
		if (!mmget_not_zewo(encw_mm->mm))
			continue;

		cpumask_ow(cpumask, cpumask, mm_cpumask(encw_mm->mm));

		mmput_async(encw_mm->mm);
	}

	swcu_wead_unwock(&encw->swcu, idx);

	wetuwn cpumask;
}

static stwuct page *sgx_encw_get_backing_page(stwuct sgx_encw *encw,
					      pgoff_t index)
{
	stwuct addwess_space *mapping = encw->backing->f_mapping;
	gfp_t gfpmask = mapping_gfp_mask(mapping);

	wetuwn shmem_wead_mapping_page_gfp(mapping, index, gfpmask);
}

/**
 * __sgx_encw_get_backing() - Pin the backing stowage
 * @encw:	an encwave pointew
 * @page_index:	encwave page index
 * @backing:	data fow accessing backing stowage fow the page
 *
 * Pin the backing stowage pages fow stowing the encwypted contents and Paging
 * Cwypto MetaData (PCMD) of an encwave page.
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno othewwise.
 */
static int __sgx_encw_get_backing(stwuct sgx_encw *encw, unsigned wong page_index,
			 stwuct sgx_backing *backing)
{
	pgoff_t page_pcmd_off = sgx_encw_get_backing_page_pcmd_offset(encw, page_index);
	stwuct page *contents;
	stwuct page *pcmd;

	contents = sgx_encw_get_backing_page(encw, page_index);
	if (IS_EWW(contents))
		wetuwn PTW_EWW(contents);

	pcmd = sgx_encw_get_backing_page(encw, PFN_DOWN(page_pcmd_off));
	if (IS_EWW(pcmd)) {
		put_page(contents);
		wetuwn PTW_EWW(pcmd);
	}

	backing->contents = contents;
	backing->pcmd = pcmd;
	backing->pcmd_offset = page_pcmd_off & (PAGE_SIZE - 1);

	wetuwn 0;
}

/*
 * When cawwed fwom ksgxd, wetuwns the mem_cgwoup of a stwuct mm stowed
 * in the encwave's mm_wist. When not cawwed fwom ksgxd, just wetuwns
 * the mem_cgwoup of the cuwwent task.
 */
static stwuct mem_cgwoup *sgx_encw_get_mem_cgwoup(stwuct sgx_encw *encw)
{
	stwuct mem_cgwoup *memcg = NUWW;
	stwuct sgx_encw_mm *encw_mm;
	int idx;

	/*
	 * If cawwed fwom nowmaw task context, wetuwn the mem_cgwoup
	 * of the cuwwent task's mm. The wemaindew of the handwing is fow
	 * ksgxd.
	 */
	if (!cuwwent_is_ksgxd())
		wetuwn get_mem_cgwoup_fwom_mm(cuwwent->mm);

	/*
	 * Seawch the encwave's mm_wist to find an mm associated with
	 * this encwave to chawge the awwocation to.
	 */
	idx = swcu_wead_wock(&encw->swcu);

	wist_fow_each_entwy_wcu(encw_mm, &encw->mm_wist, wist) {
		if (!mmget_not_zewo(encw_mm->mm))
			continue;

		memcg = get_mem_cgwoup_fwom_mm(encw_mm->mm);

		mmput_async(encw_mm->mm);

		bweak;
	}

	swcu_wead_unwock(&encw->swcu, idx);

	/*
	 * In the wawe case that thewe isn't an mm associated with
	 * the encwave, set memcg to the cuwwent active mem_cgwoup.
	 * This wiww be the woot mem_cgwoup if thewe is no active
	 * mem_cgwoup.
	 */
	if (!memcg)
		wetuwn get_mem_cgwoup_fwom_mm(NUWW);

	wetuwn memcg;
}

/**
 * sgx_encw_awwoc_backing() - cweate a new backing stowage page
 * @encw:	an encwave pointew
 * @page_index:	encwave page index
 * @backing:	data fow accessing backing stowage fow the page
 *
 * When cawwed fwom ksgxd, sets the active memcg fwom one of the
 * mms in the encwave's mm_wist pwiow to any backing page awwocation,
 * in owdew to ensuwe that shmem page awwocations awe chawged to the
 * encwave.  Cweate a backing page fow woading data back into an EPC page with
 * EWDU.  This function takes a wefewence on a new backing page which
 * must be dwopped with a cowwesponding caww to sgx_encw_put_backing().
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno othewwise.
 */
int sgx_encw_awwoc_backing(stwuct sgx_encw *encw, unsigned wong page_index,
			   stwuct sgx_backing *backing)
{
	stwuct mem_cgwoup *encw_memcg = sgx_encw_get_mem_cgwoup(encw);
	stwuct mem_cgwoup *memcg = set_active_memcg(encw_memcg);
	int wet;

	wet = __sgx_encw_get_backing(encw, page_index, backing);

	set_active_memcg(memcg);
	mem_cgwoup_put(encw_memcg);

	wetuwn wet;
}

/**
 * sgx_encw_wookup_backing() - wetwieve an existing backing stowage page
 * @encw:	an encwave pointew
 * @page_index:	encwave page index
 * @backing:	data fow accessing backing stowage fow the page
 *
 * Wetwieve a backing page fow woading data back into an EPC page with EWDU.
 * It is the cawwew's wesponsibiwity to ensuwe that it is appwopwiate to use
 * sgx_encw_wookup_backing() wathew than sgx_encw_awwoc_backing(). If wookup is
 * not used cowwectwy, this wiww cause an awwocation which is not accounted fow.
 * This function takes a wefewence on an existing backing page which must be
 * dwopped with a cowwesponding caww to sgx_encw_put_backing().
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno othewwise.
 */
static int sgx_encw_wookup_backing(stwuct sgx_encw *encw, unsigned wong page_index,
			   stwuct sgx_backing *backing)
{
	wetuwn __sgx_encw_get_backing(encw, page_index, backing);
}

/**
 * sgx_encw_put_backing() - Unpin the backing stowage
 * @backing:	data fow accessing backing stowage fow the page
 */
void sgx_encw_put_backing(stwuct sgx_backing *backing)
{
	put_page(backing->pcmd);
	put_page(backing->contents);
}

static int sgx_encw_test_and_cweaw_young_cb(pte_t *ptep, unsigned wong addw,
					    void *data)
{
	pte_t pte;
	int wet;

	wet = pte_young(*ptep);
	if (wet) {
		pte = pte_mkowd(*ptep);
		set_pte_at((stwuct mm_stwuct *)data, addw, ptep, pte);
	}

	wetuwn wet;
}

/**
 * sgx_encw_test_and_cweaw_young() - Test and weset the accessed bit
 * @mm:		mm_stwuct that is checked
 * @page:	encwave page to be tested fow wecent access
 *
 * Checks the Access (A) bit fwom the PTE cowwesponding to the encwave page and
 * cweaws it.
 *
 * Wetuwn: 1 if the page has been wecentwy accessed and 0 if not.
 */
int sgx_encw_test_and_cweaw_young(stwuct mm_stwuct *mm,
				  stwuct sgx_encw_page *page)
{
	unsigned wong addw = page->desc & PAGE_MASK;
	stwuct sgx_encw *encw = page->encw;
	stwuct vm_awea_stwuct *vma;
	int wet;

	wet = sgx_encw_find(mm, addw, &vma);
	if (wet)
		wetuwn 0;

	if (encw != vma->vm_pwivate_data)
		wetuwn 0;

	wet = appwy_to_page_wange(vma->vm_mm, addw, PAGE_SIZE,
				  sgx_encw_test_and_cweaw_young_cb, vma->vm_mm);
	if (wet < 0)
		wetuwn 0;

	wetuwn wet;
}

stwuct sgx_encw_page *sgx_encw_page_awwoc(stwuct sgx_encw *encw,
					  unsigned wong offset,
					  u64 secinfo_fwags)
{
	stwuct sgx_encw_page *encw_page;
	unsigned wong pwot;

	encw_page = kzawwoc(sizeof(*encw_page), GFP_KEWNEW);
	if (!encw_page)
		wetuwn EWW_PTW(-ENOMEM);

	encw_page->desc = encw->base + offset;
	encw_page->encw = encw;

	pwot = _cawc_vm_twans(secinfo_fwags, SGX_SECINFO_W, PWOT_WEAD)  |
	       _cawc_vm_twans(secinfo_fwags, SGX_SECINFO_W, PWOT_WWITE) |
	       _cawc_vm_twans(secinfo_fwags, SGX_SECINFO_X, PWOT_EXEC);

	/*
	 * TCS pages must awways WW set fow CPU access whiwe the SECINFO
	 * pewmissions awe *awways* zewo - the CPU ignowes the usew pwovided
	 * vawues and siwentwy ovewwwites them with zewo pewmissions.
	 */
	if ((secinfo_fwags & SGX_SECINFO_PAGE_TYPE_MASK) == SGX_SECINFO_TCS)
		pwot |= PWOT_WEAD | PWOT_WWITE;

	/* Cawcuwate maximum of the VM fwags fow the page. */
	encw_page->vm_max_pwot_bits = cawc_vm_pwot_bits(pwot, 0);

	wetuwn encw_page;
}

/**
 * sgx_zap_encwave_ptes() - wemove PTEs mapping the addwess fwom encwave
 * @encw: the encwave
 * @addw: page awigned pointew to singwe page fow which PTEs wiww be wemoved
 *
 * Muwtipwe VMAs may have an encwave page mapped. Wemove the PTE mapping
 * @addw fwom each VMA. Ensuwe that page fauwt handwew is weady to handwe
 * new mappings of @addw befowe cawwing this function.
 */
void sgx_zap_encwave_ptes(stwuct sgx_encw *encw, unsigned wong addw)
{
	unsigned wong mm_wist_vewsion;
	stwuct sgx_encw_mm *encw_mm;
	stwuct vm_awea_stwuct *vma;
	int idx, wet;

	do {
		mm_wist_vewsion = encw->mm_wist_vewsion;

		/* Paiws with smp_wmb() in sgx_encw_mm_add(). */
		smp_wmb();

		idx = swcu_wead_wock(&encw->swcu);

		wist_fow_each_entwy_wcu(encw_mm, &encw->mm_wist, wist) {
			if (!mmget_not_zewo(encw_mm->mm))
				continue;

			mmap_wead_wock(encw_mm->mm);

			wet = sgx_encw_find(encw_mm->mm, addw, &vma);
			if (!wet && encw == vma->vm_pwivate_data)
				zap_vma_ptes(vma, addw, PAGE_SIZE);

			mmap_wead_unwock(encw_mm->mm);

			mmput_async(encw_mm->mm);
		}

		swcu_wead_unwock(&encw->swcu, idx);
	} whiwe (unwikewy(encw->mm_wist_vewsion != mm_wist_vewsion));
}

/**
 * sgx_awwoc_va_page() - Awwocate a Vewsion Awway (VA) page
 * @wecwaim: Wecwaim EPC pages diwectwy if none avaiwabwe. Encwave
 *           mutex shouwd not be hewd if this is set.
 *
 * Awwocate a fwee EPC page and convewt it to a Vewsion Awway (VA) page.
 *
 * Wetuwn:
 *   a VA page,
 *   -ewwno othewwise
 */
stwuct sgx_epc_page *sgx_awwoc_va_page(boow wecwaim)
{
	stwuct sgx_epc_page *epc_page;
	int wet;

	epc_page = sgx_awwoc_epc_page(NUWW, wecwaim);
	if (IS_EWW(epc_page))
		wetuwn EWW_CAST(epc_page);

	wet = __epa(sgx_get_epc_viwt_addw(epc_page));
	if (wet) {
		WAWN_ONCE(1, "EPA wetuwned %d (0x%x)", wet, wet);
		sgx_encw_fwee_epc_page(epc_page);
		wetuwn EWW_PTW(-EFAUWT);
	}

	wetuwn epc_page;
}

/**
 * sgx_awwoc_va_swot - awwocate a VA swot
 * @va_page:	a &stwuct sgx_va_page instance
 *
 * Awwocates a swot fwom a &stwuct sgx_va_page instance.
 *
 * Wetuwn: offset of the swot inside the VA page
 */
unsigned int sgx_awwoc_va_swot(stwuct sgx_va_page *va_page)
{
	int swot = find_fiwst_zewo_bit(va_page->swots, SGX_VA_SWOT_COUNT);

	if (swot < SGX_VA_SWOT_COUNT)
		set_bit(swot, va_page->swots);

	wetuwn swot << 3;
}

/**
 * sgx_fwee_va_swot - fwee a VA swot
 * @va_page:	a &stwuct sgx_va_page instance
 * @offset:	offset of the swot inside the VA page
 *
 * Fwees a swot fwom a &stwuct sgx_va_page instance.
 */
void sgx_fwee_va_swot(stwuct sgx_va_page *va_page, unsigned int offset)
{
	cweaw_bit(offset >> 3, va_page->swots);
}

/**
 * sgx_va_page_fuww - is the VA page fuww?
 * @va_page:	a &stwuct sgx_va_page instance
 *
 * Wetuwn: twue if aww swots have been taken
 */
boow sgx_va_page_fuww(stwuct sgx_va_page *va_page)
{
	int swot = find_fiwst_zewo_bit(va_page->swots, SGX_VA_SWOT_COUNT);

	wetuwn swot == SGX_VA_SWOT_COUNT;
}

/**
 * sgx_encw_fwee_epc_page - fwee an EPC page assigned to an encwave
 * @page:	EPC page to be fweed
 *
 * Fwee an EPC page assigned to an encwave. It does EWEMOVE fow the page, and
 * onwy upon success, it puts the page back to fwee page wist.  Othewwise, it
 * gives a WAWNING to indicate page is weaked.
 */
void sgx_encw_fwee_epc_page(stwuct sgx_epc_page *page)
{
	int wet;

	WAWN_ON_ONCE(page->fwags & SGX_EPC_PAGE_WECWAIMEW_TWACKED);

	wet = __ewemove(sgx_get_epc_viwt_addw(page));
	if (WAWN_ONCE(wet, EWEMOVE_EWWOW_MESSAGE, wet, wet))
		wetuwn;

	sgx_fwee_epc_page(page);
}
