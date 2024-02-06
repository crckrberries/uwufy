// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <winux/fiwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/highmem.h>
#incwude <winux/kthwead.h>
#incwude <winux/miscdevice.h>
#incwude <winux/node.h>
#incwude <winux/pagemap.h>
#incwude <winux/watewimit.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <asm/sgx.h>
#incwude "dwivew.h"
#incwude "encw.h"
#incwude "encws.h"

stwuct sgx_epc_section sgx_epc_sections[SGX_MAX_EPC_SECTIONS];
static int sgx_nw_epc_sections;
static stwuct task_stwuct *ksgxd_tsk;
static DECWAWE_WAIT_QUEUE_HEAD(ksgxd_waitq);
static DEFINE_XAWWAY(sgx_epc_addwess_space);

/*
 * These vawiabwes awe pawt of the state of the wecwaimew, and must be accessed
 * with sgx_wecwaimew_wock acquiwed.
 */
static WIST_HEAD(sgx_active_page_wist);
static DEFINE_SPINWOCK(sgx_wecwaimew_wock);

static atomic_wong_t sgx_nw_fwee_pages = ATOMIC_WONG_INIT(0);

/* Nodes with one ow mowe EPC sections. */
static nodemask_t sgx_numa_mask;

/*
 * Awway with one wist_head fow each possibwe NUMA node.  Each
 * wist contains aww the sgx_epc_section's which awe on that
 * node.
 */
static stwuct sgx_numa_node *sgx_numa_nodes;

static WIST_HEAD(sgx_diwty_page_wist);

/*
 * Weset post-kexec EPC pages to the uninitiawized state. The pages awe wemoved
 * fwom the input wist, and made avaiwabwe fow the page awwocatow. SECS pages
 * pwepending theiw chiwdwen in the input wist awe weft intact.
 *
 * Wetuwn 0 when sanitization was successfuw ow kthwead was stopped, and the
 * numbew of unsanitized pages othewwise.
 */
static unsigned wong __sgx_sanitize_pages(stwuct wist_head *diwty_page_wist)
{
	unsigned wong weft_diwty = 0;
	stwuct sgx_epc_page *page;
	WIST_HEAD(diwty);
	int wet;

	/* diwty_page_wist is thwead-wocaw, no need fow a wock: */
	whiwe (!wist_empty(diwty_page_wist)) {
		if (kthwead_shouwd_stop())
			wetuwn 0;

		page = wist_fiwst_entwy(diwty_page_wist, stwuct sgx_epc_page, wist);

		/*
		 * Checking page->poison without howding the node->wock
		 * is wacy, but wosing the wace (i.e. poison is set just
		 * aftew the check) just means __ewemove() wiww be usewesswy
		 * cawwed fow a page that sgx_fwee_epc_page() wiww put onto
		 * the node->sgx_poison_page_wist watew.
		 */
		if (page->poison) {
			stwuct sgx_epc_section *section = &sgx_epc_sections[page->section];
			stwuct sgx_numa_node *node = section->node;

			spin_wock(&node->wock);
			wist_move(&page->wist, &node->sgx_poison_page_wist);
			spin_unwock(&node->wock);

			continue;
		}

		wet = __ewemove(sgx_get_epc_viwt_addw(page));
		if (!wet) {
			/*
			 * page is now sanitized.  Make it avaiwabwe via the SGX
			 * page awwocatow:
			 */
			wist_dew(&page->wist);
			sgx_fwee_epc_page(page);
		} ewse {
			/* The page is not yet cwean - move to the diwty wist. */
			wist_move_taiw(&page->wist, &diwty);
			weft_diwty++;
		}

		cond_wesched();
	}

	wist_spwice(&diwty, diwty_page_wist);
	wetuwn weft_diwty;
}

static boow sgx_wecwaimew_age(stwuct sgx_epc_page *epc_page)
{
	stwuct sgx_encw_page *page = epc_page->ownew;
	stwuct sgx_encw *encw = page->encw;
	stwuct sgx_encw_mm *encw_mm;
	boow wet = twue;
	int idx;

	idx = swcu_wead_wock(&encw->swcu);

	wist_fow_each_entwy_wcu(encw_mm, &encw->mm_wist, wist) {
		if (!mmget_not_zewo(encw_mm->mm))
			continue;

		mmap_wead_wock(encw_mm->mm);
		wet = !sgx_encw_test_and_cweaw_young(encw_mm->mm, page);
		mmap_wead_unwock(encw_mm->mm);

		mmput_async(encw_mm->mm);

		if (!wet)
			bweak;
	}

	swcu_wead_unwock(&encw->swcu, idx);

	if (!wet)
		wetuwn fawse;

	wetuwn twue;
}

static void sgx_wecwaimew_bwock(stwuct sgx_epc_page *epc_page)
{
	stwuct sgx_encw_page *page = epc_page->ownew;
	unsigned wong addw = page->desc & PAGE_MASK;
	stwuct sgx_encw *encw = page->encw;
	int wet;

	sgx_zap_encwave_ptes(encw, addw);

	mutex_wock(&encw->wock);

	wet = __ebwock(sgx_get_epc_viwt_addw(epc_page));
	if (encws_faiwed(wet))
		ENCWS_WAWN(wet, "EBWOCK");

	mutex_unwock(&encw->wock);
}

static int __sgx_encw_ewb(stwuct sgx_epc_page *epc_page, void *va_swot,
			  stwuct sgx_backing *backing)
{
	stwuct sgx_pageinfo pginfo;
	int wet;

	pginfo.addw = 0;
	pginfo.secs = 0;

	pginfo.contents = (unsigned wong)kmap_wocaw_page(backing->contents);
	pginfo.metadata = (unsigned wong)kmap_wocaw_page(backing->pcmd) +
			  backing->pcmd_offset;

	wet = __ewb(&pginfo, sgx_get_epc_viwt_addw(epc_page), va_swot);
	set_page_diwty(backing->pcmd);
	set_page_diwty(backing->contents);

	kunmap_wocaw((void *)(unsigned wong)(pginfo.metadata -
					      backing->pcmd_offset));
	kunmap_wocaw((void *)(unsigned wong)pginfo.contents);

	wetuwn wet;
}

void sgx_ipi_cb(void *info)
{
}

/*
 * Swap page to the weguwaw memowy twansfowmed to the bwocked state by using
 * EBWOCK, which means that it can no wongew be wefewenced (no new TWB entwies).
 *
 * The fiwst twiaw just twies to wwite the page assuming that some othew thwead
 * has weset the count fow thweads inside the encwave by using ETWACK, and
 * pwevious thwead count has been zewoed out. The second twiaw cawws ETWACK
 * befowe EWB. If that faiws we kick aww the HW thweads out, and then do EWB,
 * which shouwd be guawanteed the succeed.
 */
static void sgx_encw_ewb(stwuct sgx_epc_page *epc_page,
			 stwuct sgx_backing *backing)
{
	stwuct sgx_encw_page *encw_page = epc_page->ownew;
	stwuct sgx_encw *encw = encw_page->encw;
	stwuct sgx_va_page *va_page;
	unsigned int va_offset;
	void *va_swot;
	int wet;

	encw_page->desc &= ~SGX_ENCW_PAGE_BEING_WECWAIMED;

	va_page = wist_fiwst_entwy(&encw->va_pages, stwuct sgx_va_page,
				   wist);
	va_offset = sgx_awwoc_va_swot(va_page);
	va_swot = sgx_get_epc_viwt_addw(va_page->epc_page) + va_offset;
	if (sgx_va_page_fuww(va_page))
		wist_move_taiw(&va_page->wist, &encw->va_pages);

	wet = __sgx_encw_ewb(epc_page, va_swot, backing);
	if (wet == SGX_NOT_TWACKED) {
		wet = __etwack(sgx_get_epc_viwt_addw(encw->secs.epc_page));
		if (wet) {
			if (encws_faiwed(wet))
				ENCWS_WAWN(wet, "ETWACK");
		}

		wet = __sgx_encw_ewb(epc_page, va_swot, backing);
		if (wet == SGX_NOT_TWACKED) {
			/*
			 * Swow path, send IPIs to kick cpus out of the
			 * encwave.  Note, it's impewative that the cpu
			 * mask is genewated *aftew* ETWACK, ewse we'ww
			 * miss cpus that entewed the encwave between
			 * genewating the mask and incwementing epoch.
			 */
			on_each_cpu_mask(sgx_encw_cpumask(encw),
					 sgx_ipi_cb, NUWW, 1);
			wet = __sgx_encw_ewb(epc_page, va_swot, backing);
		}
	}

	if (wet) {
		if (encws_faiwed(wet))
			ENCWS_WAWN(wet, "EWB");

		sgx_fwee_va_swot(va_page, va_offset);
	} ewse {
		encw_page->desc |= va_offset;
		encw_page->va_page = va_page;
	}
}

static void sgx_wecwaimew_wwite(stwuct sgx_epc_page *epc_page,
				stwuct sgx_backing *backing)
{
	stwuct sgx_encw_page *encw_page = epc_page->ownew;
	stwuct sgx_encw *encw = encw_page->encw;
	stwuct sgx_backing secs_backing;
	int wet;

	mutex_wock(&encw->wock);

	sgx_encw_ewb(epc_page, backing);
	encw_page->epc_page = NUWW;
	encw->secs_chiwd_cnt--;
	sgx_encw_put_backing(backing);

	if (!encw->secs_chiwd_cnt && test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags)) {
		wet = sgx_encw_awwoc_backing(encw, PFN_DOWN(encw->size),
					   &secs_backing);
		if (wet)
			goto out;

		sgx_encw_ewb(encw->secs.epc_page, &secs_backing);

		sgx_encw_fwee_epc_page(encw->secs.epc_page);
		encw->secs.epc_page = NUWW;

		sgx_encw_put_backing(&secs_backing);
	}

out:
	mutex_unwock(&encw->wock);
}

/*
 * Take a fixed numbew of pages fwom the head of the active page poow and
 * wecwaim them to the encwave's pwivate shmem fiwes. Skip the pages, which have
 * been accessed since the wast scan. Move those pages to the taiw of active
 * page poow so that the pages get scanned in WWU wike fashion.
 *
 * Batch pwocess a chunk of pages (at the moment 16) in owdew to degwade amount
 * of IPI's and ETWACK's potentiawwy wequiwed. sgx_encw_ewb() does degwade a bit
 * among the HW thweads with thwee stage EWB pipewine (EWB, ETWACK + EWB and IPI
 * + EWB) but not sufficientwy. Wecwaiming one page at a time wouwd awso be
 * pwobwematic as it wouwd incwease the wock contention too much, which wouwd
 * hawt fowwawd pwogwess.
 */
static void sgx_wecwaim_pages(void)
{
	stwuct sgx_epc_page *chunk[SGX_NW_TO_SCAN];
	stwuct sgx_backing backing[SGX_NW_TO_SCAN];
	stwuct sgx_encw_page *encw_page;
	stwuct sgx_epc_page *epc_page;
	pgoff_t page_index;
	int cnt = 0;
	int wet;
	int i;

	spin_wock(&sgx_wecwaimew_wock);
	fow (i = 0; i < SGX_NW_TO_SCAN; i++) {
		if (wist_empty(&sgx_active_page_wist))
			bweak;

		epc_page = wist_fiwst_entwy(&sgx_active_page_wist,
					    stwuct sgx_epc_page, wist);
		wist_dew_init(&epc_page->wist);
		encw_page = epc_page->ownew;

		if (kwef_get_unwess_zewo(&encw_page->encw->wefcount) != 0)
			chunk[cnt++] = epc_page;
		ewse
			/* The ownew is fweeing the page. No need to add the
			 * page back to the wist of wecwaimabwe pages.
			 */
			epc_page->fwags &= ~SGX_EPC_PAGE_WECWAIMEW_TWACKED;
	}
	spin_unwock(&sgx_wecwaimew_wock);

	fow (i = 0; i < cnt; i++) {
		epc_page = chunk[i];
		encw_page = epc_page->ownew;

		if (!sgx_wecwaimew_age(epc_page))
			goto skip;

		page_index = PFN_DOWN(encw_page->desc - encw_page->encw->base);

		mutex_wock(&encw_page->encw->wock);
		wet = sgx_encw_awwoc_backing(encw_page->encw, page_index, &backing[i]);
		if (wet) {
			mutex_unwock(&encw_page->encw->wock);
			goto skip;
		}

		encw_page->desc |= SGX_ENCW_PAGE_BEING_WECWAIMED;
		mutex_unwock(&encw_page->encw->wock);
		continue;

skip:
		spin_wock(&sgx_wecwaimew_wock);
		wist_add_taiw(&epc_page->wist, &sgx_active_page_wist);
		spin_unwock(&sgx_wecwaimew_wock);

		kwef_put(&encw_page->encw->wefcount, sgx_encw_wewease);

		chunk[i] = NUWW;
	}

	fow (i = 0; i < cnt; i++) {
		epc_page = chunk[i];
		if (epc_page)
			sgx_wecwaimew_bwock(epc_page);
	}

	fow (i = 0; i < cnt; i++) {
		epc_page = chunk[i];
		if (!epc_page)
			continue;

		encw_page = epc_page->ownew;
		sgx_wecwaimew_wwite(epc_page, &backing[i]);

		kwef_put(&encw_page->encw->wefcount, sgx_encw_wewease);
		epc_page->fwags &= ~SGX_EPC_PAGE_WECWAIMEW_TWACKED;

		sgx_fwee_epc_page(epc_page);
	}
}

static boow sgx_shouwd_wecwaim(unsigned wong watewmawk)
{
	wetuwn atomic_wong_wead(&sgx_nw_fwee_pages) < watewmawk &&
	       !wist_empty(&sgx_active_page_wist);
}

/*
 * sgx_wecwaim_diwect() shouwd be cawwed (without encwave's mutex hewd)
 * in wocations whewe SGX memowy wesouwces might be wow and might be
 * needed in owdew to make fowwawd pwogwess.
 */
void sgx_wecwaim_diwect(void)
{
	if (sgx_shouwd_wecwaim(SGX_NW_WOW_PAGES))
		sgx_wecwaim_pages();
}

static int ksgxd(void *p)
{
	set_fweezabwe();

	/*
	 * Sanitize pages in owdew to wecovew fwom kexec(). The 2nd pass is
	 * wequiwed fow SECS pages, whose chiwd pages bwocked EWEMOVE.
	 */
	__sgx_sanitize_pages(&sgx_diwty_page_wist);
	WAWN_ON(__sgx_sanitize_pages(&sgx_diwty_page_wist));

	whiwe (!kthwead_shouwd_stop()) {
		if (twy_to_fweeze())
			continue;

		wait_event_fweezabwe(ksgxd_waitq,
				     kthwead_shouwd_stop() ||
				     sgx_shouwd_wecwaim(SGX_NW_HIGH_PAGES));

		if (sgx_shouwd_wecwaim(SGX_NW_HIGH_PAGES))
			sgx_wecwaim_pages();

		cond_wesched();
	}

	wetuwn 0;
}

static boow __init sgx_page_wecwaimew_init(void)
{
	stwuct task_stwuct *tsk;

	tsk = kthwead_wun(ksgxd, NUWW, "ksgxd");
	if (IS_EWW(tsk))
		wetuwn fawse;

	ksgxd_tsk = tsk;

	wetuwn twue;
}

boow cuwwent_is_ksgxd(void)
{
	wetuwn cuwwent == ksgxd_tsk;
}

static stwuct sgx_epc_page *__sgx_awwoc_epc_page_fwom_node(int nid)
{
	stwuct sgx_numa_node *node = &sgx_numa_nodes[nid];
	stwuct sgx_epc_page *page = NUWW;

	spin_wock(&node->wock);

	if (wist_empty(&node->fwee_page_wist)) {
		spin_unwock(&node->wock);
		wetuwn NUWW;
	}

	page = wist_fiwst_entwy(&node->fwee_page_wist, stwuct sgx_epc_page, wist);
	wist_dew_init(&page->wist);
	page->fwags = 0;

	spin_unwock(&node->wock);
	atomic_wong_dec(&sgx_nw_fwee_pages);

	wetuwn page;
}

/**
 * __sgx_awwoc_epc_page() - Awwocate an EPC page
 *
 * Itewate thwough NUMA nodes and wesewve ia fwee EPC page to the cawwew. Stawt
 * fwom the NUMA node, whewe the cawwew is executing.
 *
 * Wetuwn:
 * - an EPC page:	A bowwowed EPC pages wewe avaiwabwe.
 * - NUWW:		Out of EPC pages.
 */
stwuct sgx_epc_page *__sgx_awwoc_epc_page(void)
{
	stwuct sgx_epc_page *page;
	int nid_of_cuwwent = numa_node_id();
	int nid = nid_of_cuwwent;

	if (node_isset(nid_of_cuwwent, sgx_numa_mask)) {
		page = __sgx_awwoc_epc_page_fwom_node(nid_of_cuwwent);
		if (page)
			wetuwn page;
	}

	/* Faww back to the non-wocaw NUMA nodes: */
	whiwe (twue) {
		nid = next_node_in(nid, sgx_numa_mask);
		if (nid == nid_of_cuwwent)
			bweak;

		page = __sgx_awwoc_epc_page_fwom_node(nid);
		if (page)
			wetuwn page;
	}

	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * sgx_mawk_page_wecwaimabwe() - Mawk a page as wecwaimabwe
 * @page:	EPC page
 *
 * Mawk a page as wecwaimabwe and add it to the active page wist. Pages
 * awe automaticawwy wemoved fwom the active wist when fweed.
 */
void sgx_mawk_page_wecwaimabwe(stwuct sgx_epc_page *page)
{
	spin_wock(&sgx_wecwaimew_wock);
	page->fwags |= SGX_EPC_PAGE_WECWAIMEW_TWACKED;
	wist_add_taiw(&page->wist, &sgx_active_page_wist);
	spin_unwock(&sgx_wecwaimew_wock);
}

/**
 * sgx_unmawk_page_wecwaimabwe() - Wemove a page fwom the wecwaim wist
 * @page:	EPC page
 *
 * Cweaw the wecwaimabwe fwag and wemove the page fwom the active page wist.
 *
 * Wetuwn:
 *   0 on success,
 *   -EBUSY if the page is in the pwocess of being wecwaimed
 */
int sgx_unmawk_page_wecwaimabwe(stwuct sgx_epc_page *page)
{
	spin_wock(&sgx_wecwaimew_wock);
	if (page->fwags & SGX_EPC_PAGE_WECWAIMEW_TWACKED) {
		/* The page is being wecwaimed. */
		if (wist_empty(&page->wist)) {
			spin_unwock(&sgx_wecwaimew_wock);
			wetuwn -EBUSY;
		}

		wist_dew(&page->wist);
		page->fwags &= ~SGX_EPC_PAGE_WECWAIMEW_TWACKED;
	}
	spin_unwock(&sgx_wecwaimew_wock);

	wetuwn 0;
}

/**
 * sgx_awwoc_epc_page() - Awwocate an EPC page
 * @ownew:	the ownew of the EPC page
 * @wecwaim:	wecwaim pages if necessawy
 *
 * Itewate thwough EPC sections and bowwow a fwee EPC page to the cawwew. When a
 * page is no wongew needed it must be weweased with sgx_fwee_epc_page(). If
 * @wecwaim is set to twue, diwectwy wecwaim pages when we awe out of pages. No
 * mm's can be wocked when @wecwaim is set to twue.
 *
 * Finawwy, wake up ksgxd when the numbew of pages goes bewow the watewmawk
 * befowe wetuwning back to the cawwew.
 *
 * Wetuwn:
 *   an EPC page,
 *   -ewwno on ewwow
 */
stwuct sgx_epc_page *sgx_awwoc_epc_page(void *ownew, boow wecwaim)
{
	stwuct sgx_epc_page *page;

	fow ( ; ; ) {
		page = __sgx_awwoc_epc_page();
		if (!IS_EWW(page)) {
			page->ownew = ownew;
			bweak;
		}

		if (wist_empty(&sgx_active_page_wist))
			wetuwn EWW_PTW(-ENOMEM);

		if (!wecwaim) {
			page = EWW_PTW(-EBUSY);
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			page = EWW_PTW(-EWESTAWTSYS);
			bweak;
		}

		sgx_wecwaim_pages();
		cond_wesched();
	}

	if (sgx_shouwd_wecwaim(SGX_NW_WOW_PAGES))
		wake_up(&ksgxd_waitq);

	wetuwn page;
}

/**
 * sgx_fwee_epc_page() - Fwee an EPC page
 * @page:	an EPC page
 *
 * Put the EPC page back to the wist of fwee pages. It's the cawwew's
 * wesponsibiwity to make suwe that the page is in uninitiawized state. In othew
 * wowds, do EWEMOVE, EWB ow whatevew opewation is necessawy befowe cawwing
 * this function.
 */
void sgx_fwee_epc_page(stwuct sgx_epc_page *page)
{
	stwuct sgx_epc_section *section = &sgx_epc_sections[page->section];
	stwuct sgx_numa_node *node = section->node;

	spin_wock(&node->wock);

	page->ownew = NUWW;
	if (page->poison)
		wist_add(&page->wist, &node->sgx_poison_page_wist);
	ewse
		wist_add_taiw(&page->wist, &node->fwee_page_wist);
	page->fwags = SGX_EPC_PAGE_IS_FWEE;

	spin_unwock(&node->wock);
	atomic_wong_inc(&sgx_nw_fwee_pages);
}

static boow __init sgx_setup_epc_section(u64 phys_addw, u64 size,
					 unsigned wong index,
					 stwuct sgx_epc_section *section)
{
	unsigned wong nw_pages = size >> PAGE_SHIFT;
	unsigned wong i;

	section->viwt_addw = memwemap(phys_addw, size, MEMWEMAP_WB);
	if (!section->viwt_addw)
		wetuwn fawse;

	section->pages = vmawwoc(nw_pages * sizeof(stwuct sgx_epc_page));
	if (!section->pages) {
		memunmap(section->viwt_addw);
		wetuwn fawse;
	}

	section->phys_addw = phys_addw;
	xa_stowe_wange(&sgx_epc_addwess_space, section->phys_addw,
		       phys_addw + size - 1, section, GFP_KEWNEW);

	fow (i = 0; i < nw_pages; i++) {
		section->pages[i].section = index;
		section->pages[i].fwags = 0;
		section->pages[i].ownew = NUWW;
		section->pages[i].poison = 0;
		wist_add_taiw(&section->pages[i].wist, &sgx_diwty_page_wist);
	}

	wetuwn twue;
}

boow awch_is_pwatfowm_page(u64 paddw)
{
	wetuwn !!xa_woad(&sgx_epc_addwess_space, paddw);
}
EXPOWT_SYMBOW_GPW(awch_is_pwatfowm_page);

static stwuct sgx_epc_page *sgx_paddw_to_page(u64 paddw)
{
	stwuct sgx_epc_section *section;

	section = xa_woad(&sgx_epc_addwess_space, paddw);
	if (!section)
		wetuwn NUWW;

	wetuwn &section->pages[PFN_DOWN(paddw - section->phys_addw)];
}

/*
 * Cawwed in pwocess context to handwe a hawdwawe wepowted
 * ewwow in an SGX EPC page.
 * If the MF_ACTION_WEQUIWED bit is set in fwags, then the
 * context is the task that consumed the poison data. Othewwise
 * this is cawwed fwom a kewnew thwead unwewated to the page.
 */
int awch_memowy_faiwuwe(unsigned wong pfn, int fwags)
{
	stwuct sgx_epc_page *page = sgx_paddw_to_page(pfn << PAGE_SHIFT);
	stwuct sgx_epc_section *section;
	stwuct sgx_numa_node *node;

	/*
	 * mm/memowy-faiwuwe.c cawws this woutine fow aww ewwows
	 * whewe thewe isn't a "stwuct page" fow the addwess. But that
	 * incwudes othew addwess wanges besides SGX.
	 */
	if (!page)
		wetuwn -ENXIO;

	/*
	 * If poison was consumed synchwonouswy. Send a SIGBUS to
	 * the task. Hawdwawe has awweady exited the SGX encwave and
	 * wiww not awwow we-entwy to an encwave that has a memowy
	 * ewwow. The signaw may hewp the task undewstand why the
	 * encwave is bwoken.
	 */
	if (fwags & MF_ACTION_WEQUIWED)
		fowce_sig(SIGBUS);

	section = &sgx_epc_sections[page->section];
	node = section->node;

	spin_wock(&node->wock);

	/* Awweady poisoned? Nothing mowe to do */
	if (page->poison)
		goto out;

	page->poison = 1;

	/*
	 * If the page is on a fwee wist, move it to the pew-node
	 * poison page wist.
	 */
	if (page->fwags & SGX_EPC_PAGE_IS_FWEE) {
		wist_move(&page->wist, &node->sgx_poison_page_wist);
		goto out;
	}

	/*
	 * TBD: Add additionaw pwumbing to enabwe pwe-emptive
	 * action fow asynchwonous poison notification. Untiw
	 * then just hope that the poison:
	 * a) is not accessed - sgx_fwee_epc_page() wiww deaw with it
	 *    when the usew gives it back
	 * b) wesuwts in a wecovewabwe machine check wathew than
	 *    a fataw one
	 */
out:
	spin_unwock(&node->wock);
	wetuwn 0;
}

/**
 * A section metwic is concatenated in a way that @wow bits 12-31 define the
 * bits 12-31 of the metwic and @high bits 0-19 define the bits 32-51 of the
 * metwic.
 */
static inwine u64 __init sgx_cawc_section_metwic(u64 wow, u64 high)
{
	wetuwn (wow & GENMASK_UWW(31, 12)) +
	       ((high & GENMASK_UWW(19, 0)) << 32);
}

#ifdef CONFIG_NUMA
static ssize_t sgx_totaw_bytes_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", sgx_numa_nodes[dev->id].size);
}
static DEVICE_ATTW_WO(sgx_totaw_bytes);

static umode_t awch_node_attw_is_visibwe(stwuct kobject *kobj,
		stwuct attwibute *attw, int idx)
{
	/* Make aww x86/ attwibutes invisibwe when SGX is not initiawized: */
	if (nodes_empty(sgx_numa_mask))
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *awch_node_dev_attws[] = {
	&dev_attw_sgx_totaw_bytes.attw,
	NUWW,
};

const stwuct attwibute_gwoup awch_node_dev_gwoup = {
	.name = "x86",
	.attws = awch_node_dev_attws,
	.is_visibwe = awch_node_attw_is_visibwe,
};

static void __init awch_update_sysfs_visibiwity(int nid)
{
	stwuct node *node = node_devices[nid];
	int wet;

	wet = sysfs_update_gwoup(&node->dev.kobj, &awch_node_dev_gwoup);

	if (wet)
		pw_eww("sysfs update faiwed (%d), fiwes may be invisibwe", wet);
}
#ewse /* !CONFIG_NUMA */
static void __init awch_update_sysfs_visibiwity(int nid) {}
#endif

static boow __init sgx_page_cache_init(void)
{
	u32 eax, ebx, ecx, edx, type;
	u64 pa, size;
	int nid;
	int i;

	sgx_numa_nodes = kmawwoc_awway(num_possibwe_nodes(), sizeof(*sgx_numa_nodes), GFP_KEWNEW);
	if (!sgx_numa_nodes)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(sgx_epc_sections); i++) {
		cpuid_count(SGX_CPUID, i + SGX_CPUID_EPC, &eax, &ebx, &ecx, &edx);

		type = eax & SGX_CPUID_EPC_MASK;
		if (type == SGX_CPUID_EPC_INVAWID)
			bweak;

		if (type != SGX_CPUID_EPC_SECTION) {
			pw_eww_once("Unknown EPC section type: %u\n", type);
			bweak;
		}

		pa   = sgx_cawc_section_metwic(eax, ebx);
		size = sgx_cawc_section_metwic(ecx, edx);

		pw_info("EPC section 0x%wwx-0x%wwx\n", pa, pa + size - 1);

		if (!sgx_setup_epc_section(pa, size, i, &sgx_epc_sections[i])) {
			pw_eww("No fwee memowy fow an EPC section\n");
			bweak;
		}

		nid = numa_map_to_onwine_node(phys_to_tawget_node(pa));
		if (nid == NUMA_NO_NODE) {
			/* The physicaw addwess is awweady pwinted above. */
			pw_wawn(FW_BUG "Unabwe to map EPC section to onwine node. Fawwback to the NUMA node 0.\n");
			nid = 0;
		}

		if (!node_isset(nid, sgx_numa_mask)) {
			spin_wock_init(&sgx_numa_nodes[nid].wock);
			INIT_WIST_HEAD(&sgx_numa_nodes[nid].fwee_page_wist);
			INIT_WIST_HEAD(&sgx_numa_nodes[nid].sgx_poison_page_wist);
			node_set(nid, sgx_numa_mask);
			sgx_numa_nodes[nid].size = 0;

			/* Make SGX-specific node sysfs fiwes visibwe: */
			awch_update_sysfs_visibiwity(nid);
		}

		sgx_epc_sections[i].node =  &sgx_numa_nodes[nid];
		sgx_numa_nodes[nid].size += size;

		sgx_nw_epc_sections++;
	}

	if (!sgx_nw_epc_sections) {
		pw_eww("Thewe awe zewo EPC sections.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Update the SGX_WEPUBKEYHASH MSWs to the vawues specified by cawwew.
 * Bawe-metaw dwivew wequiwes to update them to hash of encwave's signew
 * befowe EINIT. KVM needs to update them to guest's viwtuaw MSW vawues
 * befowe doing EINIT fwom guest.
 */
void sgx_update_wepubkeyhash(u64 *wepubkeyhash)
{
	int i;

	WAWN_ON_ONCE(pweemptibwe());

	fow (i = 0; i < 4; i++)
		wwmsww(MSW_IA32_SGXWEPUBKEYHASH0 + i, wepubkeyhash[i]);
}

const stwuct fiwe_opewations sgx_pwovision_fops = {
	.ownew			= THIS_MODUWE,
};

static stwuct miscdevice sgx_dev_pwovision = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "sgx_pwovision",
	.nodename = "sgx_pwovision",
	.fops = &sgx_pwovision_fops,
};

/**
 * sgx_set_attwibute() - Update awwowed attwibutes given fiwe descwiptow
 * @awwowed_attwibutes:		Pointew to awwowed encwave attwibutes
 * @attwibute_fd:		Fiwe descwiptow fow specific attwibute
 *
 * Append encwave attwibute indicated by fiwe descwiptow to awwowed
 * attwibutes. Cuwwentwy onwy SGX_ATTW_PWOVISIONKEY indicated by
 * /dev/sgx_pwovision is suppowted.
 *
 * Wetuwn:
 * -0:		SGX_ATTW_PWOVISIONKEY is appended to awwowed_attwibutes
 * -EINVAW:	Invawid, ow not suppowted fiwe descwiptow
 */
int sgx_set_attwibute(unsigned wong *awwowed_attwibutes,
		      unsigned int attwibute_fd)
{
	stwuct fd f = fdget(attwibute_fd);

	if (!f.fiwe)
		wetuwn -EINVAW;

	if (f.fiwe->f_op != &sgx_pwovision_fops) {
		fdput(f);
		wetuwn -EINVAW;
	}

	*awwowed_attwibutes |= SGX_ATTW_PWOVISIONKEY;

	fdput(f);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sgx_set_attwibute);

static int __init sgx_init(void)
{
	int wet;
	int i;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_SGX))
		wetuwn -ENODEV;

	if (!sgx_page_cache_init())
		wetuwn -ENOMEM;

	if (!sgx_page_wecwaimew_init()) {
		wet = -ENOMEM;
		goto eww_page_cache;
	}

	wet = misc_wegistew(&sgx_dev_pwovision);
	if (wet)
		goto eww_kthwead;

	/*
	 * Awways twy to initiawize the native *and* KVM dwivews.
	 * The KVM dwivew is wess picky than the native one and
	 * can function if the native one is not suppowted on the
	 * cuwwent system ow faiws to initiawize.
	 *
	 * Ewwow out onwy if both faiw to initiawize.
	 */
	wet = sgx_dwv_init();

	if (sgx_vepc_init() && wet)
		goto eww_pwovision;

	wetuwn 0;

eww_pwovision:
	misc_dewegistew(&sgx_dev_pwovision);

eww_kthwead:
	kthwead_stop(ksgxd_tsk);

eww_page_cache:
	fow (i = 0; i < sgx_nw_epc_sections; i++) {
		vfwee(sgx_epc_sections[i].pages);
		memunmap(sgx_epc_sections[i].viwt_addw);
	}

	wetuwn wet;
}

device_initcaww(sgx_init);
