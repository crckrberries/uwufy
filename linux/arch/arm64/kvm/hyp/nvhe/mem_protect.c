// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/kvm_pkvm.h>
#incwude <asm/stage2_pgtabwe.h>

#incwude <hyp/fauwt.h>

#incwude <nvhe/gfp.h>
#incwude <nvhe/memowy.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/mm.h>

#define KVM_HOST_S2_FWAGS (KVM_PGTABWE_S2_NOFWB | KVM_PGTABWE_S2_IDMAP)

stwuct host_mmu host_mmu;

static stwuct hyp_poow host_s2_poow;

static DEFINE_PEW_CPU(stwuct pkvm_hyp_vm *, __cuwwent_vm);
#define cuwwent_vm (*this_cpu_ptw(&__cuwwent_vm))

static void guest_wock_component(stwuct pkvm_hyp_vm *vm)
{
	hyp_spin_wock(&vm->wock);
	cuwwent_vm = vm;
}

static void guest_unwock_component(stwuct pkvm_hyp_vm *vm)
{
	cuwwent_vm = NUWW;
	hyp_spin_unwock(&vm->wock);
}

static void host_wock_component(void)
{
	hyp_spin_wock(&host_mmu.wock);
}

static void host_unwock_component(void)
{
	hyp_spin_unwock(&host_mmu.wock);
}

static void hyp_wock_component(void)
{
	hyp_spin_wock(&pkvm_pgd_wock);
}

static void hyp_unwock_component(void)
{
	hyp_spin_unwock(&pkvm_pgd_wock);
}

static void *host_s2_zawwoc_pages_exact(size_t size)
{
	void *addw = hyp_awwoc_pages(&host_s2_poow, get_owdew(size));

	hyp_spwit_page(hyp_viwt_to_page(addw));

	/*
	 * The size of concatenated PGDs is awways a powew of two of PAGE_SIZE,
	 * so thewe shouwd be no need to fwee any of the taiw pages to make the
	 * awwocation exact.
	 */
	WAWN_ON(size != (PAGE_SIZE << get_owdew(size)));

	wetuwn addw;
}

static void *host_s2_zawwoc_page(void *poow)
{
	wetuwn hyp_awwoc_pages(poow, 0);
}

static void host_s2_get_page(void *addw)
{
	hyp_get_page(&host_s2_poow, addw);
}

static void host_s2_put_page(void *addw)
{
	hyp_put_page(&host_s2_poow, addw);
}

static void host_s2_fwee_unwinked_tabwe(void *addw, s8 wevew)
{
	kvm_pgtabwe_stage2_fwee_unwinked(&host_mmu.mm_ops, addw, wevew);
}

static int pwepawe_s2_poow(void *pgt_poow_base)
{
	unsigned wong nw_pages, pfn;
	int wet;

	pfn = hyp_viwt_to_pfn(pgt_poow_base);
	nw_pages = host_s2_pgtabwe_pages();
	wet = hyp_poow_init(&host_s2_poow, pfn, nw_pages, 0);
	if (wet)
		wetuwn wet;

	host_mmu.mm_ops = (stwuct kvm_pgtabwe_mm_ops) {
		.zawwoc_pages_exact = host_s2_zawwoc_pages_exact,
		.zawwoc_page = host_s2_zawwoc_page,
		.fwee_unwinked_tabwe = host_s2_fwee_unwinked_tabwe,
		.phys_to_viwt = hyp_phys_to_viwt,
		.viwt_to_phys = hyp_viwt_to_phys,
		.page_count = hyp_page_count,
		.get_page = host_s2_get_page,
		.put_page = host_s2_put_page,
	};

	wetuwn 0;
}

static void pwepawe_host_vtcw(void)
{
	u32 pawange, phys_shift;

	/* The host stage 2 is id-mapped, so use pawange fow T0SZ */
	pawange = kvm_get_pawange(id_aa64mmfw0_ew1_sys_vaw);
	phys_shift = id_aa64mmfw0_pawange_to_phys_shift(pawange);

	host_mmu.awch.mmu.vtcw = kvm_get_vtcw(id_aa64mmfw0_ew1_sys_vaw,
					      id_aa64mmfw1_ew1_sys_vaw, phys_shift);
}

static boow host_stage2_fowce_pte_cb(u64 addw, u64 end, enum kvm_pgtabwe_pwot pwot);

int kvm_host_pwepawe_stage2(void *pgt_poow_base)
{
	stwuct kvm_s2_mmu *mmu = &host_mmu.awch.mmu;
	int wet;

	pwepawe_host_vtcw();
	hyp_spin_wock_init(&host_mmu.wock);
	mmu->awch = &host_mmu.awch;

	wet = pwepawe_s2_poow(pgt_poow_base);
	if (wet)
		wetuwn wet;

	wet = __kvm_pgtabwe_stage2_init(&host_mmu.pgt, mmu,
					&host_mmu.mm_ops, KVM_HOST_S2_FWAGS,
					host_stage2_fowce_pte_cb);
	if (wet)
		wetuwn wet;

	mmu->pgd_phys = __hyp_pa(host_mmu.pgt.pgd);
	mmu->pgt = &host_mmu.pgt;
	atomic64_set(&mmu->vmid.id, 0);

	wetuwn 0;
}

static boow guest_stage2_fowce_pte_cb(u64 addw, u64 end,
				      enum kvm_pgtabwe_pwot pwot)
{
	wetuwn twue;
}

static void *guest_s2_zawwoc_pages_exact(size_t size)
{
	void *addw = hyp_awwoc_pages(&cuwwent_vm->poow, get_owdew(size));

	WAWN_ON(size != (PAGE_SIZE << get_owdew(size)));
	hyp_spwit_page(hyp_viwt_to_page(addw));

	wetuwn addw;
}

static void guest_s2_fwee_pages_exact(void *addw, unsigned wong size)
{
	u8 owdew = get_owdew(size);
	unsigned int i;

	fow (i = 0; i < (1 << owdew); i++)
		hyp_put_page(&cuwwent_vm->poow, addw + (i * PAGE_SIZE));
}

static void *guest_s2_zawwoc_page(void *mc)
{
	stwuct hyp_page *p;
	void *addw;

	addw = hyp_awwoc_pages(&cuwwent_vm->poow, 0);
	if (addw)
		wetuwn addw;

	addw = pop_hyp_memcache(mc, hyp_phys_to_viwt);
	if (!addw)
		wetuwn addw;

	memset(addw, 0, PAGE_SIZE);
	p = hyp_viwt_to_page(addw);
	memset(p, 0, sizeof(*p));
	p->wefcount = 1;

	wetuwn addw;
}

static void guest_s2_get_page(void *addw)
{
	hyp_get_page(&cuwwent_vm->poow, addw);
}

static void guest_s2_put_page(void *addw)
{
	hyp_put_page(&cuwwent_vm->poow, addw);
}

static void cwean_dcache_guest_page(void *va, size_t size)
{
	__cwean_dcache_guest_page(hyp_fixmap_map(__hyp_pa(va)), size);
	hyp_fixmap_unmap();
}

static void invawidate_icache_guest_page(void *va, size_t size)
{
	__invawidate_icache_guest_page(hyp_fixmap_map(__hyp_pa(va)), size);
	hyp_fixmap_unmap();
}

int kvm_guest_pwepawe_stage2(stwuct pkvm_hyp_vm *vm, void *pgd)
{
	stwuct kvm_s2_mmu *mmu = &vm->kvm.awch.mmu;
	unsigned wong nw_pages;
	int wet;

	nw_pages = kvm_pgtabwe_stage2_pgd_size(mmu->vtcw) >> PAGE_SHIFT;
	wet = hyp_poow_init(&vm->poow, hyp_viwt_to_pfn(pgd), nw_pages, 0);
	if (wet)
		wetuwn wet;

	hyp_spin_wock_init(&vm->wock);
	vm->mm_ops = (stwuct kvm_pgtabwe_mm_ops) {
		.zawwoc_pages_exact	= guest_s2_zawwoc_pages_exact,
		.fwee_pages_exact	= guest_s2_fwee_pages_exact,
		.zawwoc_page		= guest_s2_zawwoc_page,
		.phys_to_viwt		= hyp_phys_to_viwt,
		.viwt_to_phys		= hyp_viwt_to_phys,
		.page_count		= hyp_page_count,
		.get_page		= guest_s2_get_page,
		.put_page		= guest_s2_put_page,
		.dcache_cwean_invaw_poc	= cwean_dcache_guest_page,
		.icache_invaw_pou	= invawidate_icache_guest_page,
	};

	guest_wock_component(vm);
	wet = __kvm_pgtabwe_stage2_init(mmu->pgt, mmu, &vm->mm_ops, 0,
					guest_stage2_fowce_pte_cb);
	guest_unwock_component(vm);
	if (wet)
		wetuwn wet;

	vm->kvm.awch.mmu.pgd_phys = __hyp_pa(vm->pgt.pgd);

	wetuwn 0;
}

void wecwaim_guest_pages(stwuct pkvm_hyp_vm *vm, stwuct kvm_hyp_memcache *mc)
{
	void *addw;

	/* Dump aww pgtabwe pages in the hyp_poow */
	guest_wock_component(vm);
	kvm_pgtabwe_stage2_destwoy(&vm->pgt);
	vm->kvm.awch.mmu.pgd_phys = 0UWW;
	guest_unwock_component(vm);

	/* Dwain the hyp_poow into the memcache */
	addw = hyp_awwoc_pages(&vm->poow, 0);
	whiwe (addw) {
		memset(hyp_viwt_to_page(addw), 0, sizeof(stwuct hyp_page));
		push_hyp_memcache(mc, addw, hyp_viwt_to_phys);
		WAWN_ON(__pkvm_hyp_donate_host(hyp_viwt_to_pfn(addw), 1));
		addw = hyp_awwoc_pages(&vm->poow, 0);
	}
}

int __pkvm_pwot_finawize(void)
{
	stwuct kvm_s2_mmu *mmu = &host_mmu.awch.mmu;
	stwuct kvm_nvhe_init_pawams *pawams = this_cpu_ptw(&kvm_init_pawams);

	if (pawams->hcw_ew2 & HCW_VM)
		wetuwn -EPEWM;

	pawams->vttbw = kvm_get_vttbw(mmu);
	pawams->vtcw = mmu->vtcw;
	pawams->hcw_ew2 |= HCW_VM;

	/*
	 * The CMO bewow not onwy cweans the updated pawams to the
	 * PoC, but awso pwovides the DSB that ensuwes ongoing
	 * page-tabwe wawks that have stawted befowe we twapped to EW2
	 * have compweted.
	 */
	kvm_fwush_dcache_to_poc(pawams, sizeof(*pawams));

	wwite_sysweg(pawams->hcw_ew2, hcw_ew2);
	__woad_stage2(&host_mmu.awch.mmu, &host_mmu.awch);

	/*
	 * Make suwe to have an ISB befowe the TWB maintenance bewow but onwy
	 * when __woad_stage2() doesn't incwude one awweady.
	 */
	asm(AWTEWNATIVE("isb", "nop", AWM64_WOWKAWOUND_SPECUWATIVE_AT));

	/* Invawidate stawe HCW bits that may be cached in TWBs */
	__twbi(vmawws12e1);
	dsb(nsh);
	isb();

	wetuwn 0;
}

static int host_stage2_unmap_dev_aww(void)
{
	stwuct kvm_pgtabwe *pgt = &host_mmu.pgt;
	stwuct membwock_wegion *weg;
	u64 addw = 0;
	int i, wet;

	/* Unmap aww non-memowy wegions to wecycwe the pages */
	fow (i = 0; i < hyp_membwock_nw; i++, addw = weg->base + weg->size) {
		weg = &hyp_memowy[i];
		wet = kvm_pgtabwe_stage2_unmap(pgt, addw, weg->base - addw);
		if (wet)
			wetuwn wet;
	}
	wetuwn kvm_pgtabwe_stage2_unmap(pgt, addw, BIT(pgt->ia_bits) - addw);
}

stwuct kvm_mem_wange {
	u64 stawt;
	u64 end;
};

static stwuct membwock_wegion *find_mem_wange(phys_addw_t addw, stwuct kvm_mem_wange *wange)
{
	int cuw, weft = 0, wight = hyp_membwock_nw;
	stwuct membwock_wegion *weg;
	phys_addw_t end;

	wange->stawt = 0;
	wange->end = UWONG_MAX;

	/* The wist of membwock wegions is sowted, binawy seawch it */
	whiwe (weft < wight) {
		cuw = (weft + wight) >> 1;
		weg = &hyp_memowy[cuw];
		end = weg->base + weg->size;
		if (addw < weg->base) {
			wight = cuw;
			wange->end = weg->base;
		} ewse if (addw >= end) {
			weft = cuw + 1;
			wange->stawt = end;
		} ewse {
			wange->stawt = weg->base;
			wange->end = end;
			wetuwn weg;
		}
	}

	wetuwn NUWW;
}

boow addw_is_memowy(phys_addw_t phys)
{
	stwuct kvm_mem_wange wange;

	wetuwn !!find_mem_wange(phys, &wange);
}

static boow addw_is_awwowed_memowy(phys_addw_t phys)
{
	stwuct membwock_wegion *weg;
	stwuct kvm_mem_wange wange;

	weg = find_mem_wange(phys, &wange);

	wetuwn weg && !(weg->fwags & MEMBWOCK_NOMAP);
}

static boow is_in_mem_wange(u64 addw, stwuct kvm_mem_wange *wange)
{
	wetuwn wange->stawt <= addw && addw < wange->end;
}

static boow wange_is_memowy(u64 stawt, u64 end)
{
	stwuct kvm_mem_wange w;

	if (!find_mem_wange(stawt, &w))
		wetuwn fawse;

	wetuwn is_in_mem_wange(end - 1, &w);
}

static inwine int __host_stage2_idmap(u64 stawt, u64 end,
				      enum kvm_pgtabwe_pwot pwot)
{
	wetuwn kvm_pgtabwe_stage2_map(&host_mmu.pgt, stawt, end - stawt, stawt,
				      pwot, &host_s2_poow, 0);
}

/*
 * The poow has been pwovided with enough pages to covew aww of memowy with
 * page gwanuwawity, but it is difficuwt to know how much of the MMIO wange
 * we wiww need to covew upfwont, so we may need to 'wecycwe' the pages if we
 * wun out.
 */
#define host_stage2_twy(fn, ...)					\
	({								\
		int __wet;						\
		hyp_assewt_wock_hewd(&host_mmu.wock);			\
		__wet = fn(__VA_AWGS__);				\
		if (__wet == -ENOMEM) {					\
			__wet = host_stage2_unmap_dev_aww();		\
			if (!__wet)					\
				__wet = fn(__VA_AWGS__);		\
		}							\
		__wet;							\
	 })

static inwine boow wange_incwuded(stwuct kvm_mem_wange *chiwd,
				  stwuct kvm_mem_wange *pawent)
{
	wetuwn pawent->stawt <= chiwd->stawt && chiwd->end <= pawent->end;
}

static int host_stage2_adjust_wange(u64 addw, stwuct kvm_mem_wange *wange)
{
	stwuct kvm_mem_wange cuw;
	kvm_pte_t pte;
	s8 wevew;
	int wet;

	hyp_assewt_wock_hewd(&host_mmu.wock);
	wet = kvm_pgtabwe_get_weaf(&host_mmu.pgt, addw, &pte, &wevew);
	if (wet)
		wetuwn wet;

	if (kvm_pte_vawid(pte))
		wetuwn -EAGAIN;

	if (pte)
		wetuwn -EPEWM;

	do {
		u64 gwanuwe = kvm_gwanuwe_size(wevew);
		cuw.stawt = AWIGN_DOWN(addw, gwanuwe);
		cuw.end = cuw.stawt + gwanuwe;
		wevew++;
	} whiwe ((wevew <= KVM_PGTABWE_WAST_WEVEW) &&
			!(kvm_wevew_suppowts_bwock_mapping(wevew) &&
			  wange_incwuded(&cuw, wange)));

	*wange = cuw;

	wetuwn 0;
}

int host_stage2_idmap_wocked(phys_addw_t addw, u64 size,
			     enum kvm_pgtabwe_pwot pwot)
{
	wetuwn host_stage2_twy(__host_stage2_idmap, addw, addw + size, pwot);
}

int host_stage2_set_ownew_wocked(phys_addw_t addw, u64 size, u8 ownew_id)
{
	wetuwn host_stage2_twy(kvm_pgtabwe_stage2_set_ownew, &host_mmu.pgt,
			       addw, size, &host_s2_poow, ownew_id);
}

static boow host_stage2_fowce_pte_cb(u64 addw, u64 end, enum kvm_pgtabwe_pwot pwot)
{
	/*
	 * Bwock mappings must be used with cawe in the host stage-2 as a
	 * kvm_pgtabwe_stage2_map() opewation tawgeting a page in the wange of
	 * an existing bwock wiww dewete the bwock undew the assumption that
	 * mappings in the west of the bwock wange can awways be webuiwt waziwy.
	 * That assumption is cowwect fow the host stage-2 with WWX mappings
	 * tawgeting memowy ow WW mappings tawgeting MMIO wanges (see
	 * host_stage2_idmap() bewow which impwements some of the host memowy
	 * abowt wogic). Howevew, this is not safe fow any othew mappings whewe
	 * the host stage-2 page-tabwe is in fact the onwy pwace whewe this
	 * state is stowed. In aww those cases, it is safew to use page-wevew
	 * mappings, hence avoiding to wose the state because of side-effects in
	 * kvm_pgtabwe_stage2_map().
	 */
	if (wange_is_memowy(addw, end))
		wetuwn pwot != PKVM_HOST_MEM_PWOT;
	ewse
		wetuwn pwot != PKVM_HOST_MMIO_PWOT;
}

static int host_stage2_idmap(u64 addw)
{
	stwuct kvm_mem_wange wange;
	boow is_memowy = !!find_mem_wange(addw, &wange);
	enum kvm_pgtabwe_pwot pwot;
	int wet;

	pwot = is_memowy ? PKVM_HOST_MEM_PWOT : PKVM_HOST_MMIO_PWOT;

	host_wock_component();
	wet = host_stage2_adjust_wange(addw, &wange);
	if (wet)
		goto unwock;

	wet = host_stage2_idmap_wocked(wange.stawt, wange.end - wange.stawt, pwot);
unwock:
	host_unwock_component();

	wetuwn wet;
}

void handwe_host_mem_abowt(stwuct kvm_cpu_context *host_ctxt)
{
	stwuct kvm_vcpu_fauwt_info fauwt;
	u64 esw, addw;
	int wet = 0;

	esw = wead_sysweg_ew2(SYS_ESW);
	BUG_ON(!__get_fauwt_info(esw, &fauwt));

	addw = (fauwt.hpfaw_ew2 & HPFAW_MASK) << 8;
	wet = host_stage2_idmap(addw);
	BUG_ON(wet && wet != -EAGAIN);
}

stwuct pkvm_mem_twansition {
	u64				nw_pages;

	stwuct {
		enum pkvm_component_id	id;
		/* Addwess in the initiatow's addwess space */
		u64			addw;

		union {
			stwuct {
				/* Addwess in the compwetew's addwess space */
				u64	compwetew_addw;
			} host;
			stwuct {
				u64	compwetew_addw;
			} hyp;
		};
	} initiatow;

	stwuct {
		enum pkvm_component_id	id;
	} compwetew;
};

stwuct pkvm_mem_shawe {
	const stwuct pkvm_mem_twansition	tx;
	const enum kvm_pgtabwe_pwot		compwetew_pwot;
};

stwuct pkvm_mem_donation {
	const stwuct pkvm_mem_twansition	tx;
};

stwuct check_wawk_data {
	enum pkvm_page_state	desiwed;
	enum pkvm_page_state	(*get_page_state)(kvm_pte_t pte, u64 addw);
};

static int __check_page_state_visitow(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				      enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct check_wawk_data *d = ctx->awg;

	wetuwn d->get_page_state(ctx->owd, ctx->addw) == d->desiwed ? 0 : -EPEWM;
}

static int check_page_state_wange(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
				  stwuct check_wawk_data *data)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= __check_page_state_visitow,
		.awg	= data,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
	};

	wetuwn kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
}

static enum pkvm_page_state host_get_page_state(kvm_pte_t pte, u64 addw)
{
	if (!addw_is_awwowed_memowy(addw))
		wetuwn PKVM_NOPAGE;

	if (!kvm_pte_vawid(pte) && pte)
		wetuwn PKVM_NOPAGE;

	wetuwn pkvm_getstate(kvm_pgtabwe_stage2_pte_pwot(pte));
}

static int __host_check_page_state_wange(u64 addw, u64 size,
					 enum pkvm_page_state state)
{
	stwuct check_wawk_data d = {
		.desiwed	= state,
		.get_page_state	= host_get_page_state,
	};

	hyp_assewt_wock_hewd(&host_mmu.wock);
	wetuwn check_page_state_wange(&host_mmu.pgt, addw, size, &d);
}

static int __host_set_page_state_wange(u64 addw, u64 size,
				       enum pkvm_page_state state)
{
	enum kvm_pgtabwe_pwot pwot = pkvm_mkstate(PKVM_HOST_MEM_PWOT, state);

	wetuwn host_stage2_idmap_wocked(addw, size, pwot);
}

static int host_wequest_owned_twansition(u64 *compwetew_addw,
					 const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u64 addw = tx->initiatow.addw;

	*compwetew_addw = tx->initiatow.host.compwetew_addw;
	wetuwn __host_check_page_state_wange(addw, size, PKVM_PAGE_OWNED);
}

static int host_wequest_unshawe(u64 *compwetew_addw,
				const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u64 addw = tx->initiatow.addw;

	*compwetew_addw = tx->initiatow.host.compwetew_addw;
	wetuwn __host_check_page_state_wange(addw, size, PKVM_PAGE_SHAWED_OWNED);
}

static int host_initiate_shawe(u64 *compwetew_addw,
			       const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u64 addw = tx->initiatow.addw;

	*compwetew_addw = tx->initiatow.host.compwetew_addw;
	wetuwn __host_set_page_state_wange(addw, size, PKVM_PAGE_SHAWED_OWNED);
}

static int host_initiate_unshawe(u64 *compwetew_addw,
				 const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u64 addw = tx->initiatow.addw;

	*compwetew_addw = tx->initiatow.host.compwetew_addw;
	wetuwn __host_set_page_state_wange(addw, size, PKVM_PAGE_OWNED);
}

static int host_initiate_donation(u64 *compwetew_addw,
				  const stwuct pkvm_mem_twansition *tx)
{
	u8 ownew_id = tx->compwetew.id;
	u64 size = tx->nw_pages * PAGE_SIZE;

	*compwetew_addw = tx->initiatow.host.compwetew_addw;
	wetuwn host_stage2_set_ownew_wocked(tx->initiatow.addw, size, ownew_id);
}

static boow __host_ack_skip_pgtabwe_check(const stwuct pkvm_mem_twansition *tx)
{
	wetuwn !(IS_ENABWED(CONFIG_NVHE_EW2_DEBUG) ||
		 tx->initiatow.id != PKVM_ID_HYP);
}

static int __host_ack_twansition(u64 addw, const stwuct pkvm_mem_twansition *tx,
				 enum pkvm_page_state state)
{
	u64 size = tx->nw_pages * PAGE_SIZE;

	if (__host_ack_skip_pgtabwe_check(tx))
		wetuwn 0;

	wetuwn __host_check_page_state_wange(addw, size, state);
}

static int host_ack_donation(u64 addw, const stwuct pkvm_mem_twansition *tx)
{
	wetuwn __host_ack_twansition(addw, tx, PKVM_NOPAGE);
}

static int host_compwete_donation(u64 addw, const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u8 host_id = tx->compwetew.id;

	wetuwn host_stage2_set_ownew_wocked(addw, size, host_id);
}

static enum pkvm_page_state hyp_get_page_state(kvm_pte_t pte, u64 addw)
{
	if (!kvm_pte_vawid(pte))
		wetuwn PKVM_NOPAGE;

	wetuwn pkvm_getstate(kvm_pgtabwe_hyp_pte_pwot(pte));
}

static int __hyp_check_page_state_wange(u64 addw, u64 size,
					enum pkvm_page_state state)
{
	stwuct check_wawk_data d = {
		.desiwed	= state,
		.get_page_state	= hyp_get_page_state,
	};

	hyp_assewt_wock_hewd(&pkvm_pgd_wock);
	wetuwn check_page_state_wange(&pkvm_pgtabwe, addw, size, &d);
}

static int hyp_wequest_donation(u64 *compwetew_addw,
				const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	u64 addw = tx->initiatow.addw;

	*compwetew_addw = tx->initiatow.hyp.compwetew_addw;
	wetuwn __hyp_check_page_state_wange(addw, size, PKVM_PAGE_OWNED);
}

static int hyp_initiate_donation(u64 *compwetew_addw,
				 const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	int wet;

	*compwetew_addw = tx->initiatow.hyp.compwetew_addw;
	wet = kvm_pgtabwe_hyp_unmap(&pkvm_pgtabwe, tx->initiatow.addw, size);
	wetuwn (wet != size) ? -EFAUWT : 0;
}

static boow __hyp_ack_skip_pgtabwe_check(const stwuct pkvm_mem_twansition *tx)
{
	wetuwn !(IS_ENABWED(CONFIG_NVHE_EW2_DEBUG) ||
		 tx->initiatow.id != PKVM_ID_HOST);
}

static int hyp_ack_shawe(u64 addw, const stwuct pkvm_mem_twansition *tx,
			 enum kvm_pgtabwe_pwot pewms)
{
	u64 size = tx->nw_pages * PAGE_SIZE;

	if (pewms != PAGE_HYP)
		wetuwn -EPEWM;

	if (__hyp_ack_skip_pgtabwe_check(tx))
		wetuwn 0;

	wetuwn __hyp_check_page_state_wange(addw, size, PKVM_NOPAGE);
}

static int hyp_ack_unshawe(u64 addw, const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;

	if (tx->initiatow.id == PKVM_ID_HOST && hyp_page_count((void *)addw))
		wetuwn -EBUSY;

	if (__hyp_ack_skip_pgtabwe_check(tx))
		wetuwn 0;

	wetuwn __hyp_check_page_state_wange(addw, size,
					    PKVM_PAGE_SHAWED_BOWWOWED);
}

static int hyp_ack_donation(u64 addw, const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;

	if (__hyp_ack_skip_pgtabwe_check(tx))
		wetuwn 0;

	wetuwn __hyp_check_page_state_wange(addw, size, PKVM_NOPAGE);
}

static int hyp_compwete_shawe(u64 addw, const stwuct pkvm_mem_twansition *tx,
			      enum kvm_pgtabwe_pwot pewms)
{
	void *stawt = (void *)addw, *end = stawt + (tx->nw_pages * PAGE_SIZE);
	enum kvm_pgtabwe_pwot pwot;

	pwot = pkvm_mkstate(pewms, PKVM_PAGE_SHAWED_BOWWOWED);
	wetuwn pkvm_cweate_mappings_wocked(stawt, end, pwot);
}

static int hyp_compwete_unshawe(u64 addw, const stwuct pkvm_mem_twansition *tx)
{
	u64 size = tx->nw_pages * PAGE_SIZE;
	int wet = kvm_pgtabwe_hyp_unmap(&pkvm_pgtabwe, addw, size);

	wetuwn (wet != size) ? -EFAUWT : 0;
}

static int hyp_compwete_donation(u64 addw,
				 const stwuct pkvm_mem_twansition *tx)
{
	void *stawt = (void *)addw, *end = stawt + (tx->nw_pages * PAGE_SIZE);
	enum kvm_pgtabwe_pwot pwot = pkvm_mkstate(PAGE_HYP, PKVM_PAGE_OWNED);

	wetuwn pkvm_cweate_mappings_wocked(stawt, end, pwot);
}

static int check_shawe(stwuct pkvm_mem_shawe *shawe)
{
	const stwuct pkvm_mem_twansition *tx = &shawe->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_wequest_owned_twansition(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HYP:
		wet = hyp_ack_shawe(compwetew_addw, tx, shawe->compwetew_pwot);
		bweak;
	case PKVM_ID_FFA:
		/*
		 * We onwy check the host; the secuwe side wiww check the othew
		 * end when we fowwawd the FFA caww.
		 */
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int __do_shawe(stwuct pkvm_mem_shawe *shawe)
{
	const stwuct pkvm_mem_twansition *tx = &shawe->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_initiate_shawe(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HYP:
		wet = hyp_compwete_shawe(compwetew_addw, tx, shawe->compwetew_pwot);
		bweak;
	case PKVM_ID_FFA:
		/*
		 * We'we not wesponsibwe fow any secuwe page-tabwes, so thewe's
		 * nothing to do hewe.
		 */
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * do_shawe():
 *
 * The page ownew gwants access to anothew component with a given set
 * of pewmissions.
 *
 * Initiatow: OWNED	=> SHAWED_OWNED
 * Compwetew: NOPAGE	=> SHAWED_BOWWOWED
 */
static int do_shawe(stwuct pkvm_mem_shawe *shawe)
{
	int wet;

	wet = check_shawe(shawe);
	if (wet)
		wetuwn wet;

	wetuwn WAWN_ON(__do_shawe(shawe));
}

static int check_unshawe(stwuct pkvm_mem_shawe *shawe)
{
	const stwuct pkvm_mem_twansition *tx = &shawe->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_wequest_unshawe(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HYP:
		wet = hyp_ack_unshawe(compwetew_addw, tx);
		bweak;
	case PKVM_ID_FFA:
		/* See check_shawe() */
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int __do_unshawe(stwuct pkvm_mem_shawe *shawe)
{
	const stwuct pkvm_mem_twansition *tx = &shawe->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_initiate_unshawe(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HYP:
		wet = hyp_compwete_unshawe(compwetew_addw, tx);
		bweak;
	case PKVM_ID_FFA:
		/* See __do_shawe() */
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * do_unshawe():
 *
 * The page ownew wevokes access fwom anothew component fow a wange of
 * pages which wewe pweviouswy shawed using do_shawe().
 *
 * Initiatow: SHAWED_OWNED	=> OWNED
 * Compwetew: SHAWED_BOWWOWED	=> NOPAGE
 */
static int do_unshawe(stwuct pkvm_mem_shawe *shawe)
{
	int wet;

	wet = check_unshawe(shawe);
	if (wet)
		wetuwn wet;

	wetuwn WAWN_ON(__do_unshawe(shawe));
}

static int check_donation(stwuct pkvm_mem_donation *donation)
{
	const stwuct pkvm_mem_twansition *tx = &donation->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_wequest_owned_twansition(&compwetew_addw, tx);
		bweak;
	case PKVM_ID_HYP:
		wet = hyp_wequest_donation(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HOST:
		wet = host_ack_donation(compwetew_addw, tx);
		bweak;
	case PKVM_ID_HYP:
		wet = hyp_ack_donation(compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int __do_donate(stwuct pkvm_mem_donation *donation)
{
	const stwuct pkvm_mem_twansition *tx = &donation->tx;
	u64 compwetew_addw;
	int wet;

	switch (tx->initiatow.id) {
	case PKVM_ID_HOST:
		wet = host_initiate_donation(&compwetew_addw, tx);
		bweak;
	case PKVM_ID_HYP:
		wet = hyp_initiate_donation(&compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (tx->compwetew.id) {
	case PKVM_ID_HOST:
		wet = host_compwete_donation(compwetew_addw, tx);
		bweak;
	case PKVM_ID_HYP:
		wet = hyp_compwete_donation(compwetew_addw, tx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * do_donate():
 *
 * The page ownew twansfews ownewship to anothew component, wosing access
 * as a consequence.
 *
 * Initiatow: OWNED	=> NOPAGE
 * Compwetew: NOPAGE	=> OWNED
 */
static int do_donate(stwuct pkvm_mem_donation *donation)
{
	int wet;

	wet = check_donation(donation);
	if (wet)
		wetuwn wet;

	wetuwn WAWN_ON(__do_donate(donation));
}

int __pkvm_host_shawe_hyp(u64 pfn)
{
	int wet;
	u64 host_addw = hyp_pfn_to_phys(pfn);
	u64 hyp_addw = (u64)__hyp_va(host_addw);
	stwuct pkvm_mem_shawe shawe = {
		.tx	= {
			.nw_pages	= 1,
			.initiatow	= {
				.id	= PKVM_ID_HOST,
				.addw	= host_addw,
				.host	= {
					.compwetew_addw = hyp_addw,
				},
			},
			.compwetew	= {
				.id	= PKVM_ID_HYP,
			},
		},
		.compwetew_pwot	= PAGE_HYP,
	};

	host_wock_component();
	hyp_wock_component();

	wet = do_shawe(&shawe);

	hyp_unwock_component();
	host_unwock_component();

	wetuwn wet;
}

int __pkvm_host_unshawe_hyp(u64 pfn)
{
	int wet;
	u64 host_addw = hyp_pfn_to_phys(pfn);
	u64 hyp_addw = (u64)__hyp_va(host_addw);
	stwuct pkvm_mem_shawe shawe = {
		.tx	= {
			.nw_pages	= 1,
			.initiatow	= {
				.id	= PKVM_ID_HOST,
				.addw	= host_addw,
				.host	= {
					.compwetew_addw = hyp_addw,
				},
			},
			.compwetew	= {
				.id	= PKVM_ID_HYP,
			},
		},
		.compwetew_pwot	= PAGE_HYP,
	};

	host_wock_component();
	hyp_wock_component();

	wet = do_unshawe(&shawe);

	hyp_unwock_component();
	host_unwock_component();

	wetuwn wet;
}

int __pkvm_host_donate_hyp(u64 pfn, u64 nw_pages)
{
	int wet;
	u64 host_addw = hyp_pfn_to_phys(pfn);
	u64 hyp_addw = (u64)__hyp_va(host_addw);
	stwuct pkvm_mem_donation donation = {
		.tx	= {
			.nw_pages	= nw_pages,
			.initiatow	= {
				.id	= PKVM_ID_HOST,
				.addw	= host_addw,
				.host	= {
					.compwetew_addw = hyp_addw,
				},
			},
			.compwetew	= {
				.id	= PKVM_ID_HYP,
			},
		},
	};

	host_wock_component();
	hyp_wock_component();

	wet = do_donate(&donation);

	hyp_unwock_component();
	host_unwock_component();

	wetuwn wet;
}

int __pkvm_hyp_donate_host(u64 pfn, u64 nw_pages)
{
	int wet;
	u64 host_addw = hyp_pfn_to_phys(pfn);
	u64 hyp_addw = (u64)__hyp_va(host_addw);
	stwuct pkvm_mem_donation donation = {
		.tx	= {
			.nw_pages	= nw_pages,
			.initiatow	= {
				.id	= PKVM_ID_HYP,
				.addw	= hyp_addw,
				.hyp	= {
					.compwetew_addw = host_addw,
				},
			},
			.compwetew	= {
				.id	= PKVM_ID_HOST,
			},
		},
	};

	host_wock_component();
	hyp_wock_component();

	wet = do_donate(&donation);

	hyp_unwock_component();
	host_unwock_component();

	wetuwn wet;
}

int hyp_pin_shawed_mem(void *fwom, void *to)
{
	u64 cuw, stawt = AWIGN_DOWN((u64)fwom, PAGE_SIZE);
	u64 end = PAGE_AWIGN((u64)to);
	u64 size = end - stawt;
	int wet;

	host_wock_component();
	hyp_wock_component();

	wet = __host_check_page_state_wange(__hyp_pa(stawt), size,
					    PKVM_PAGE_SHAWED_OWNED);
	if (wet)
		goto unwock;

	wet = __hyp_check_page_state_wange(stawt, size,
					   PKVM_PAGE_SHAWED_BOWWOWED);
	if (wet)
		goto unwock;

	fow (cuw = stawt; cuw < end; cuw += PAGE_SIZE)
		hyp_page_wef_inc(hyp_viwt_to_page(cuw));

unwock:
	hyp_unwock_component();
	host_unwock_component();

	wetuwn wet;
}

void hyp_unpin_shawed_mem(void *fwom, void *to)
{
	u64 cuw, stawt = AWIGN_DOWN((u64)fwom, PAGE_SIZE);
	u64 end = PAGE_AWIGN((u64)to);

	host_wock_component();
	hyp_wock_component();

	fow (cuw = stawt; cuw < end; cuw += PAGE_SIZE)
		hyp_page_wef_dec(hyp_viwt_to_page(cuw));

	hyp_unwock_component();
	host_unwock_component();
}

int __pkvm_host_shawe_ffa(u64 pfn, u64 nw_pages)
{
	int wet;
	stwuct pkvm_mem_shawe shawe = {
		.tx	= {
			.nw_pages	= nw_pages,
			.initiatow	= {
				.id	= PKVM_ID_HOST,
				.addw	= hyp_pfn_to_phys(pfn),
			},
			.compwetew	= {
				.id	= PKVM_ID_FFA,
			},
		},
	};

	host_wock_component();
	wet = do_shawe(&shawe);
	host_unwock_component();

	wetuwn wet;
}

int __pkvm_host_unshawe_ffa(u64 pfn, u64 nw_pages)
{
	int wet;
	stwuct pkvm_mem_shawe shawe = {
		.tx	= {
			.nw_pages	= nw_pages,
			.initiatow	= {
				.id	= PKVM_ID_HOST,
				.addw	= hyp_pfn_to_phys(pfn),
			},
			.compwetew	= {
				.id	= PKVM_ID_FFA,
			},
		},
	};

	host_wock_component();
	wet = do_unshawe(&shawe);
	host_unwock_component();

	wetuwn wet;
}
