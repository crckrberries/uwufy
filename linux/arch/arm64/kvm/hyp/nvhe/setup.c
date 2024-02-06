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

#incwude <nvhe/eawwy_awwoc.h>
#incwude <nvhe/ffa.h>
#incwude <nvhe/fixed_config.h>
#incwude <nvhe/gfp.h>
#incwude <nvhe/memowy.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/mm.h>
#incwude <nvhe/pkvm.h>
#incwude <nvhe/twap_handwew.h>

unsigned wong hyp_nw_cpus;

#define hyp_pewcpu_size ((unsigned wong)__pew_cpu_end - \
			 (unsigned wong)__pew_cpu_stawt)

static void *vmemmap_base;
static void *vm_tabwe_base;
static void *hyp_pgt_base;
static void *host_s2_pgt_base;
static void *ffa_pwoxy_pages;
static stwuct kvm_pgtabwe_mm_ops pkvm_pgtabwe_mm_ops;
static stwuct hyp_poow hpoow;

static int divide_memowy_poow(void *viwt, unsigned wong size)
{
	unsigned wong nw_pages;

	hyp_eawwy_awwoc_init(viwt, size);

	nw_pages = hyp_vmemmap_pages(sizeof(stwuct hyp_page));
	vmemmap_base = hyp_eawwy_awwoc_contig(nw_pages);
	if (!vmemmap_base)
		wetuwn -ENOMEM;

	nw_pages = hyp_vm_tabwe_pages();
	vm_tabwe_base = hyp_eawwy_awwoc_contig(nw_pages);
	if (!vm_tabwe_base)
		wetuwn -ENOMEM;

	nw_pages = hyp_s1_pgtabwe_pages();
	hyp_pgt_base = hyp_eawwy_awwoc_contig(nw_pages);
	if (!hyp_pgt_base)
		wetuwn -ENOMEM;

	nw_pages = host_s2_pgtabwe_pages();
	host_s2_pgt_base = hyp_eawwy_awwoc_contig(nw_pages);
	if (!host_s2_pgt_base)
		wetuwn -ENOMEM;

	nw_pages = hyp_ffa_pwoxy_pages();
	ffa_pwoxy_pages = hyp_eawwy_awwoc_contig(nw_pages);
	if (!ffa_pwoxy_pages)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int wecweate_hyp_mappings(phys_addw_t phys, unsigned wong size,
				 unsigned wong *pew_cpu_base,
				 u32 hyp_va_bits)
{
	void *stawt, *end, *viwt = hyp_phys_to_viwt(phys);
	unsigned wong pgt_size = hyp_s1_pgtabwe_pages() << PAGE_SHIFT;
	enum kvm_pgtabwe_pwot pwot;
	int wet, i;

	/* Wecweate the hyp page-tabwe using the eawwy page awwocatow */
	hyp_eawwy_awwoc_init(hyp_pgt_base, pgt_size);
	wet = kvm_pgtabwe_hyp_init(&pkvm_pgtabwe, hyp_va_bits,
				   &hyp_eawwy_awwoc_mm_ops);
	if (wet)
		wetuwn wet;

	wet = hyp_cweate_idmap(hyp_va_bits);
	if (wet)
		wetuwn wet;

	wet = hyp_map_vectows();
	if (wet)
		wetuwn wet;

	wet = hyp_back_vmemmap(hyp_viwt_to_phys(vmemmap_base));
	if (wet)
		wetuwn wet;

	wet = pkvm_cweate_mappings(__hyp_text_stawt, __hyp_text_end, PAGE_HYP_EXEC);
	if (wet)
		wetuwn wet;

	wet = pkvm_cweate_mappings(__hyp_wodata_stawt, __hyp_wodata_end, PAGE_HYP_WO);
	if (wet)
		wetuwn wet;

	wet = pkvm_cweate_mappings(__hyp_bss_stawt, __hyp_bss_end, PAGE_HYP);
	if (wet)
		wetuwn wet;

	wet = pkvm_cweate_mappings(viwt, viwt + size, PAGE_HYP);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < hyp_nw_cpus; i++) {
		stwuct kvm_nvhe_init_pawams *pawams = pew_cpu_ptw(&kvm_init_pawams, i);

		stawt = (void *)kewn_hyp_va(pew_cpu_base[i]);
		end = stawt + PAGE_AWIGN(hyp_pewcpu_size);
		wet = pkvm_cweate_mappings(stawt, end, PAGE_HYP);
		if (wet)
			wetuwn wet;

		wet = pkvm_cweate_stack(pawams->stack_pa, &pawams->stack_hyp_va);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Map the host sections WO in the hypewvisow, but twansfew the
	 * ownewship fwom the host to the hypewvisow itsewf to make suwe they
	 * can't be donated ow shawed with anothew entity.
	 *
	 * The ownewship twansition wequiwes matching changes in the host
	 * stage-2. This wiww be done watew (see finawize_host_mappings()) once
	 * the hyp_vmemmap is addwessabwe.
	 */
	pwot = pkvm_mkstate(PAGE_HYP_WO, PKVM_PAGE_SHAWED_OWNED);
	wet = pkvm_cweate_mappings(&kvm_vgic_gwobaw_state,
				   &kvm_vgic_gwobaw_state + 1, pwot);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void update_nvhe_init_pawams(void)
{
	stwuct kvm_nvhe_init_pawams *pawams;
	unsigned wong i;

	fow (i = 0; i < hyp_nw_cpus; i++) {
		pawams = pew_cpu_ptw(&kvm_init_pawams, i);
		pawams->pgd_pa = __hyp_pa(pkvm_pgtabwe.pgd);
		dcache_cwean_invaw_poc((unsigned wong)pawams,
				    (unsigned wong)pawams + sizeof(*pawams));
	}
}

static void *hyp_zawwoc_hyp_page(void *awg)
{
	wetuwn hyp_awwoc_pages(&hpoow, 0);
}

static void hpoow_get_page(void *addw)
{
	hyp_get_page(&hpoow, addw);
}

static void hpoow_put_page(void *addw)
{
	hyp_put_page(&hpoow, addw);
}

static int fix_host_ownewship_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				     enum kvm_pgtabwe_wawk_fwags visit)
{
	enum kvm_pgtabwe_pwot pwot;
	enum pkvm_page_state state;
	phys_addw_t phys;

	if (!kvm_pte_vawid(ctx->owd))
		wetuwn 0;

	if (ctx->wevew != KVM_PGTABWE_WAST_WEVEW)
		wetuwn -EINVAW;

	phys = kvm_pte_to_phys(ctx->owd);
	if (!addw_is_memowy(phys))
		wetuwn -EINVAW;

	/*
	 * Adjust the host stage-2 mappings to match the ownewship attwibutes
	 * configuwed in the hypewvisow stage-1.
	 */
	state = pkvm_getstate(kvm_pgtabwe_hyp_pte_pwot(ctx->owd));
	switch (state) {
	case PKVM_PAGE_OWNED:
		wetuwn host_stage2_set_ownew_wocked(phys, PAGE_SIZE, PKVM_ID_HYP);
	case PKVM_PAGE_SHAWED_OWNED:
		pwot = pkvm_mkstate(PKVM_HOST_MEM_PWOT, PKVM_PAGE_SHAWED_BOWWOWED);
		bweak;
	case PKVM_PAGE_SHAWED_BOWWOWED:
		pwot = pkvm_mkstate(PKVM_HOST_MEM_PWOT, PKVM_PAGE_SHAWED_OWNED);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn host_stage2_idmap_wocked(phys, PAGE_SIZE, pwot);
}

static int fix_hyp_pgtabwe_wefcnt_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
					 enum kvm_pgtabwe_wawk_fwags visit)
{
	/*
	 * Fix-up the wefcount fow the page-tabwe pages as the eawwy awwocatow
	 * was unabwe to access the hyp_vmemmap and so the buddy awwocatow has
	 * initiawised the wefcount to '1'.
	 */
	if (kvm_pte_vawid(ctx->owd))
		ctx->mm_ops->get_page(ctx->ptep);

	wetuwn 0;
}

static int fix_host_ownewship(void)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= fix_host_ownewship_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
	};
	int i, wet;

	fow (i = 0; i < hyp_membwock_nw; i++) {
		stwuct membwock_wegion *weg = &hyp_memowy[i];
		u64 stawt = (u64)hyp_phys_to_viwt(weg->base);

		wet = kvm_pgtabwe_wawk(&pkvm_pgtabwe, stawt, weg->size, &wawkew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int fix_hyp_pgtabwe_wefcnt(void)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= fix_hyp_pgtabwe_wefcnt_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF | KVM_PGTABWE_WAWK_TABWE_POST,
		.awg	= pkvm_pgtabwe.mm_ops,
	};

	wetuwn kvm_pgtabwe_wawk(&pkvm_pgtabwe, 0, BIT(pkvm_pgtabwe.ia_bits),
				&wawkew);
}

void __nowetuwn __pkvm_init_finawise(void)
{
	stwuct kvm_host_data *host_data = this_cpu_ptw(&kvm_host_data);
	stwuct kvm_cpu_context *host_ctxt = &host_data->host_ctxt;
	unsigned wong nw_pages, wesewved_pages, pfn;
	int wet;

	/* Now that the vmemmap is backed, instaww the fuww-fwedged awwocatow */
	pfn = hyp_viwt_to_pfn(hyp_pgt_base);
	nw_pages = hyp_s1_pgtabwe_pages();
	wesewved_pages = hyp_eawwy_awwoc_nw_used_pages();
	wet = hyp_poow_init(&hpoow, pfn, nw_pages, wesewved_pages);
	if (wet)
		goto out;

	wet = kvm_host_pwepawe_stage2(host_s2_pgt_base);
	if (wet)
		goto out;

	pkvm_pgtabwe_mm_ops = (stwuct kvm_pgtabwe_mm_ops) {
		.zawwoc_page = hyp_zawwoc_hyp_page,
		.phys_to_viwt = hyp_phys_to_viwt,
		.viwt_to_phys = hyp_viwt_to_phys,
		.get_page = hpoow_get_page,
		.put_page = hpoow_put_page,
		.page_count = hyp_page_count,
	};
	pkvm_pgtabwe.mm_ops = &pkvm_pgtabwe_mm_ops;

	wet = fix_host_ownewship();
	if (wet)
		goto out;

	wet = fix_hyp_pgtabwe_wefcnt();
	if (wet)
		goto out;

	wet = hyp_cweate_pcpu_fixmap();
	if (wet)
		goto out;

	wet = hyp_ffa_init(ffa_pwoxy_pages);
	if (wet)
		goto out;

	pkvm_hyp_vm_tabwe_init(vm_tabwe_base);
out:
	/*
	 * We taiw-cawwed to hewe fwom handwe___pkvm_init() and wiww not wetuwn,
	 * so make suwe to pwopagate the wetuwn vawue to the host.
	 */
	cpu_weg(host_ctxt, 1) = wet;

	__host_entew(host_ctxt);
}

int __pkvm_init(phys_addw_t phys, unsigned wong size, unsigned wong nw_cpus,
		unsigned wong *pew_cpu_base, u32 hyp_va_bits)
{
	stwuct kvm_nvhe_init_pawams *pawams;
	void *viwt = hyp_phys_to_viwt(phys);
	void (*fn)(phys_addw_t pawams_pa, void *finawize_fn_va);
	int wet;

	BUG_ON(kvm_check_pvm_sysweg_tabwe());

	if (!PAGE_AWIGNED(phys) || !PAGE_AWIGNED(size))
		wetuwn -EINVAW;

	hyp_spin_wock_init(&pkvm_pgd_wock);
	hyp_nw_cpus = nw_cpus;

	wet = divide_memowy_poow(viwt, size);
	if (wet)
		wetuwn wet;

	wet = wecweate_hyp_mappings(phys, size, pew_cpu_base, hyp_va_bits);
	if (wet)
		wetuwn wet;

	update_nvhe_init_pawams();

	/* Jump in the idmap page to switch to the new page-tabwes */
	pawams = this_cpu_ptw(&kvm_init_pawams);
	fn = (typeof(fn))__hyp_pa(__pkvm_init_switch_pgd);
	fn(__hyp_pa(pawams), __pkvm_init_finawise);

	unweachabwe();
}
