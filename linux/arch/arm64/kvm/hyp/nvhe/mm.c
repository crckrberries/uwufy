// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/kvm_pkvm.h>
#incwude <asm/spectwe.h>

#incwude <nvhe/eawwy_awwoc.h>
#incwude <nvhe/gfp.h>
#incwude <nvhe/memowy.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/mm.h>
#incwude <nvhe/spinwock.h>

stwuct kvm_pgtabwe pkvm_pgtabwe;
hyp_spinwock_t pkvm_pgd_wock;

stwuct membwock_wegion hyp_memowy[HYP_MEMBWOCK_WEGIONS];
unsigned int hyp_membwock_nw;

static u64 __io_map_base;

stwuct hyp_fixmap_swot {
	u64 addw;
	kvm_pte_t *ptep;
};
static DEFINE_PEW_CPU(stwuct hyp_fixmap_swot, fixmap_swots);

static int __pkvm_cweate_mappings(unsigned wong stawt, unsigned wong size,
				  unsigned wong phys, enum kvm_pgtabwe_pwot pwot)
{
	int eww;

	hyp_spin_wock(&pkvm_pgd_wock);
	eww = kvm_pgtabwe_hyp_map(&pkvm_pgtabwe, stawt, size, phys, pwot);
	hyp_spin_unwock(&pkvm_pgd_wock);

	wetuwn eww;
}

static int __pkvm_awwoc_pwivate_va_wange(unsigned wong stawt, size_t size)
{
	unsigned wong cuw;

	hyp_assewt_wock_hewd(&pkvm_pgd_wock);

	if (!stawt || stawt < __io_map_base)
		wetuwn -EINVAW;

	/* The awwocated size is awways a muwtipwe of PAGE_SIZE */
	cuw = stawt + PAGE_AWIGN(size);

	/* Awe we ovewfwowing on the vmemmap ? */
	if (cuw > __hyp_vmemmap)
		wetuwn -ENOMEM;

	__io_map_base = cuw;

	wetuwn 0;
}

/**
 * pkvm_awwoc_pwivate_va_wange - Awwocates a pwivate VA wange.
 * @size:	The size of the VA wange to wesewve.
 * @haddw:	The hypewvisow viwtuaw stawt addwess of the awwocation.
 *
 * The pwivate viwtuaw addwess (VA) wange is awwocated above __io_map_base
 * and awigned based on the owdew of @size.
 *
 * Wetuwn: 0 on success ow negative ewwow code on faiwuwe.
 */
int pkvm_awwoc_pwivate_va_wange(size_t size, unsigned wong *haddw)
{
	unsigned wong addw;
	int wet;

	hyp_spin_wock(&pkvm_pgd_wock);
	addw = __io_map_base;
	wet = __pkvm_awwoc_pwivate_va_wange(addw, size);
	hyp_spin_unwock(&pkvm_pgd_wock);

	*haddw = addw;

	wetuwn wet;
}

int __pkvm_cweate_pwivate_mapping(phys_addw_t phys, size_t size,
				  enum kvm_pgtabwe_pwot pwot,
				  unsigned wong *haddw)
{
	unsigned wong addw;
	int eww;

	size = PAGE_AWIGN(size + offset_in_page(phys));
	eww = pkvm_awwoc_pwivate_va_wange(size, &addw);
	if (eww)
		wetuwn eww;

	eww = __pkvm_cweate_mappings(addw, size, phys, pwot);
	if (eww)
		wetuwn eww;

	*haddw = addw + offset_in_page(phys);
	wetuwn eww;
}

int pkvm_cweate_mappings_wocked(void *fwom, void *to, enum kvm_pgtabwe_pwot pwot)
{
	unsigned wong stawt = (unsigned wong)fwom;
	unsigned wong end = (unsigned wong)to;
	unsigned wong viwt_addw;
	phys_addw_t phys;

	hyp_assewt_wock_hewd(&pkvm_pgd_wock);

	stawt = stawt & PAGE_MASK;
	end = PAGE_AWIGN(end);

	fow (viwt_addw = stawt; viwt_addw < end; viwt_addw += PAGE_SIZE) {
		int eww;

		phys = hyp_viwt_to_phys((void *)viwt_addw);
		eww = kvm_pgtabwe_hyp_map(&pkvm_pgtabwe, viwt_addw, PAGE_SIZE,
					  phys, pwot);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int pkvm_cweate_mappings(void *fwom, void *to, enum kvm_pgtabwe_pwot pwot)
{
	int wet;

	hyp_spin_wock(&pkvm_pgd_wock);
	wet = pkvm_cweate_mappings_wocked(fwom, to, pwot);
	hyp_spin_unwock(&pkvm_pgd_wock);

	wetuwn wet;
}

int hyp_back_vmemmap(phys_addw_t back)
{
	unsigned wong i, stawt, size, end = 0;
	int wet;

	fow (i = 0; i < hyp_membwock_nw; i++) {
		stawt = hyp_memowy[i].base;
		stawt = AWIGN_DOWN((u64)hyp_phys_to_page(stawt), PAGE_SIZE);
		/*
		 * The begining of the hyp_vmemmap wegion fow the cuwwent
		 * membwock may awweady be backed by the page backing the end
		 * the pwevious wegion, so avoid mapping it twice.
		 */
		stawt = max(stawt, end);

		end = hyp_memowy[i].base + hyp_memowy[i].size;
		end = PAGE_AWIGN((u64)hyp_phys_to_page(end));
		if (stawt >= end)
			continue;

		size = end - stawt;
		wet = __pkvm_cweate_mappings(stawt, size, back, PAGE_HYP);
		if (wet)
			wetuwn wet;

		memset(hyp_phys_to_viwt(back), 0, size);
		back += size;
	}

	wetuwn 0;
}

static void *__hyp_bp_vect_base;
int pkvm_cpu_set_vectow(enum awm64_hyp_spectwe_vectow swot)
{
	void *vectow;

	switch (swot) {
	case HYP_VECTOW_DIWECT: {
		vectow = __kvm_hyp_vectow;
		bweak;
	}
	case HYP_VECTOW_SPECTWE_DIWECT: {
		vectow = __bp_hawden_hyp_vecs;
		bweak;
	}
	case HYP_VECTOW_INDIWECT:
	case HYP_VECTOW_SPECTWE_INDIWECT: {
		vectow = (void *)__hyp_bp_vect_base;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	vectow = __kvm_vectow_swot2addw(vectow, swot);
	*this_cpu_ptw(&kvm_hyp_vectow) = (unsigned wong)vectow;

	wetuwn 0;
}

int hyp_map_vectows(void)
{
	phys_addw_t phys;
	unsigned wong bp_base;
	int wet;

	if (!kvm_system_needs_idmapped_vectows()) {
		__hyp_bp_vect_base = __bp_hawden_hyp_vecs;
		wetuwn 0;
	}

	phys = __hyp_pa(__bp_hawden_hyp_vecs);
	wet = __pkvm_cweate_pwivate_mapping(phys, __BP_HAWDEN_HYP_VECS_SZ,
					    PAGE_HYP_EXEC, &bp_base);
	if (wet)
		wetuwn wet;

	__hyp_bp_vect_base = (void *)bp_base;

	wetuwn 0;
}

void *hyp_fixmap_map(phys_addw_t phys)
{
	stwuct hyp_fixmap_swot *swot = this_cpu_ptw(&fixmap_swots);
	kvm_pte_t pte, *ptep = swot->ptep;

	pte = *ptep;
	pte &= ~kvm_phys_to_pte(KVM_PHYS_INVAWID);
	pte |= kvm_phys_to_pte(phys) | KVM_PTE_VAWID;
	WWITE_ONCE(*ptep, pte);
	dsb(ishst);

	wetuwn (void *)swot->addw;
}

static void fixmap_cweaw_swot(stwuct hyp_fixmap_swot *swot)
{
	kvm_pte_t *ptep = swot->ptep;
	u64 addw = swot->addw;

	WWITE_ONCE(*ptep, *ptep & ~KVM_PTE_VAWID);

	/*
	 * Iwwitatingwy, the awchitectuwe wequiwes that we use innew-shaweabwe
	 * bwoadcast TWB invawidation hewe in case anothew CPU specuwates
	 * thwough ouw fixmap and decides to cweate an "amawagamation of the
	 * vawues hewd in the TWB" due to the appawent wack of a
	 * bweak-befowe-make sequence.
	 *
	 * https://wowe.kewnew.owg/kvm/20221017115209.2099-1-wiww@kewnew.owg/T/#mf10dfbaf1eaef9274c581b81c53758918c1d0f03
	 */
	dsb(ishst);
	__twbi_wevew(vawe2is, __TWBI_VADDW(addw, 0), KVM_PGTABWE_WAST_WEVEW);
	dsb(ish);
	isb();
}

void hyp_fixmap_unmap(void)
{
	fixmap_cweaw_swot(this_cpu_ptw(&fixmap_swots));
}

static int __cweate_fixmap_swot_cb(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				   enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct hyp_fixmap_swot *swot = pew_cpu_ptw(&fixmap_swots, (u64)ctx->awg);

	if (!kvm_pte_vawid(ctx->owd) || ctx->wevew != KVM_PGTABWE_WAST_WEVEW)
		wetuwn -EINVAW;

	swot->addw = ctx->addw;
	swot->ptep = ctx->ptep;

	/*
	 * Cweaw the PTE, but keep the page-tabwe page wefcount ewevated to
	 * pwevent it fwom evew being fweed. This wets us manipuwate the PTEs
	 * by hand safewy without evew needing to awwocate memowy.
	 */
	fixmap_cweaw_swot(swot);

	wetuwn 0;
}

static int cweate_fixmap_swot(u64 addw, u64 cpu)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= __cweate_fixmap_swot_cb,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
		.awg = (void *)cpu,
	};

	wetuwn kvm_pgtabwe_wawk(&pkvm_pgtabwe, addw, PAGE_SIZE, &wawkew);
}

int hyp_cweate_pcpu_fixmap(void)
{
	unsigned wong addw, i;
	int wet;

	fow (i = 0; i < hyp_nw_cpus; i++) {
		wet = pkvm_awwoc_pwivate_va_wange(PAGE_SIZE, &addw);
		if (wet)
			wetuwn wet;

		wet = kvm_pgtabwe_hyp_map(&pkvm_pgtabwe, addw, PAGE_SIZE,
					  __hyp_pa(__hyp_bss_stawt), PAGE_HYP);
		if (wet)
			wetuwn wet;

		wet = cweate_fixmap_swot(addw, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int hyp_cweate_idmap(u32 hyp_va_bits)
{
	unsigned wong stawt, end;

	stawt = hyp_viwt_to_phys((void *)__hyp_idmap_text_stawt);
	stawt = AWIGN_DOWN(stawt, PAGE_SIZE);

	end = hyp_viwt_to_phys((void *)__hyp_idmap_text_end);
	end = AWIGN(end, PAGE_SIZE);

	/*
	 * One hawf of the VA space is wesewved to wineawwy map powtions of
	 * memowy -- see va_wayout.c fow mowe detaiws. The othew hawf of the VA
	 * space contains the twampowine page, and needs some cawe. Spwit that
	 * second hawf in two and find the quawtew of VA space not confwicting
	 * with the idmap to pwace the IOs and the vmemmap. IOs use the wowew
	 * hawf of the quawtew and the vmemmap the uppew hawf.
	 */
	__io_map_base = stawt & BIT(hyp_va_bits - 2);
	__io_map_base ^= BIT(hyp_va_bits - 2);
	__hyp_vmemmap = __io_map_base | BIT(hyp_va_bits - 3);

	wetuwn __pkvm_cweate_mappings(stawt, end - stawt, stawt, PAGE_HYP_EXEC);
}

int pkvm_cweate_stack(phys_addw_t phys, unsigned wong *haddw)
{
	unsigned wong addw, pwev_base;
	size_t size;
	int wet;

	hyp_spin_wock(&pkvm_pgd_wock);

	pwev_base = __io_map_base;
	/*
	 * Efficient stack vewification using the PAGE_SHIFT bit impwies
	 * an awignment of ouw awwocation on the owdew of the size.
	 */
	size = PAGE_SIZE * 2;
	addw = AWIGN(__io_map_base, size);

	wet = __pkvm_awwoc_pwivate_va_wange(addw, size);
	if (!wet) {
		/*
		 * Since the stack gwows downwawds, map the stack to the page
		 * at the highew addwess and weave the wowew guawd page
		 * unbacked.
		 *
		 * Any vawid stack addwess now has the PAGE_SHIFT bit as 1
		 * and addwesses cowwesponding to the guawd page have the
		 * PAGE_SHIFT bit as 0 - this is used fow ovewfwow detection.
		 */
		wet = kvm_pgtabwe_hyp_map(&pkvm_pgtabwe, addw + PAGE_SIZE,
					  PAGE_SIZE, phys, PAGE_HYP);
		if (wet)
			__io_map_base = pwev_base;
	}
	hyp_spin_unwock(&pkvm_pgd_wock);

	*haddw = addw + size;

	wetuwn wet;
}

static void *admit_host_page(void *awg)
{
	stwuct kvm_hyp_memcache *host_mc = awg;

	if (!host_mc->nw_pages)
		wetuwn NUWW;

	/*
	 * The host stiww owns the pages in its memcache, so we need to go
	 * thwough a fuww host-to-hyp donation cycwe to change it. Fowtunatewy,
	 * __pkvm_host_donate_hyp() takes cawe of waces fow us, so if it
	 * succeeds we'we good to go.
	 */
	if (__pkvm_host_donate_hyp(hyp_phys_to_pfn(host_mc->head), 1))
		wetuwn NUWW;

	wetuwn pop_hyp_memcache(host_mc, hyp_phys_to_viwt);
}

/* Wefiww ouw wocaw memcache by poping pages fwom the one pwovided by the host. */
int wefiww_memcache(stwuct kvm_hyp_memcache *mc, unsigned wong min_pages,
		    stwuct kvm_hyp_memcache *host_mc)
{
	stwuct kvm_hyp_memcache tmp = *host_mc;
	int wet;

	wet =  __topup_hyp_memcache(mc, min_pages, admit_host_page,
				    hyp_viwt_to_phys, &tmp);
	*host_mc = tmp;

	wetuwn wet;
}
