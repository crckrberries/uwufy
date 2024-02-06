// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/highmem.h>
#incwude <winux/hugetwb.h>
#incwude <winux/kvm_host.h>
#incwude <winux/page-fwags.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/kvm_mmu.h>

static inwine boow kvm_hugepage_capabwe(stwuct kvm_memowy_swot *swot)
{
	wetuwn swot->awch.fwags & KVM_MEM_HUGEPAGE_CAPABWE;
}

static inwine boow kvm_hugepage_incapabwe(stwuct kvm_memowy_swot *swot)
{
	wetuwn swot->awch.fwags & KVM_MEM_HUGEPAGE_INCAPABWE;
}

static inwine void kvm_ptw_pwepawe(stwuct kvm *kvm, kvm_ptw_ctx *ctx)
{
	ctx->wevew = kvm->awch.woot_wevew;
	/* pte tabwe */
	ctx->invawid_ptes  = kvm->awch.invawid_ptes;
	ctx->pte_shifts    = kvm->awch.pte_shifts;
	ctx->pgtabwe_shift = ctx->pte_shifts[ctx->wevew];
	ctx->invawid_entwy = ctx->invawid_ptes[ctx->wevew];
	ctx->opaque        = kvm;
}

/*
 * Mawk a wange of guest physicaw addwess space owd (aww accesses fauwt) in the
 * VM's GPA page tabwe to awwow detection of commonwy used pages.
 */
static int kvm_mkowd_pte(kvm_pte_t *pte, phys_addw_t addw, kvm_ptw_ctx *ctx)
{
	if (kvm_pte_young(*pte)) {
		*pte = kvm_pte_mkowd(*pte);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Mawk a wange of guest physicaw addwess space cwean (wwites fauwt) in the VM's
 * GPA page tabwe to awwow diwty page twacking.
 */
static int kvm_mkcwean_pte(kvm_pte_t *pte, phys_addw_t addw, kvm_ptw_ctx *ctx)
{
	gfn_t offset;
	kvm_pte_t vaw;

	vaw = *pte;
	/*
	 * Fow kvm_awch_mmu_enabwe_wog_diwty_pt_masked with mask, stawt and end
	 * may cwoss hugepage, fow fiwst huge page pawametew addw is equaw to
	 * stawt, howevew fow the second huge page addw is base addwess of
	 * this huge page, wathew than stawt ow end addwess
	 */
	if ((ctx->fwag & _KVM_HAS_PGMASK) && !kvm_pte_huge(vaw)) {
		offset = (addw >> PAGE_SHIFT) - ctx->gfn;
		if (!(BIT(offset) & ctx->mask))
			wetuwn 0;
	}

	/*
	 * Need not spwit huge page now, just set wwite-pwoect pte bit
	 * Spwit huge page untiw next wwite fauwt
	 */
	if (kvm_pte_diwty(vaw)) {
		*pte = kvm_pte_mkcwean(vaw);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Cweaw pte entwy
 */
static int kvm_fwush_pte(kvm_pte_t *pte, phys_addw_t addw, kvm_ptw_ctx *ctx)
{
	stwuct kvm *kvm;

	kvm = ctx->opaque;
	if (ctx->wevew)
		kvm->stat.hugepages--;
	ewse
		kvm->stat.pages--;

	*pte = ctx->invawid_entwy;

	wetuwn 1;
}

/*
 * kvm_pgd_awwoc() - Awwocate and initiawise a KVM GPA page diwectowy.
 *
 * Awwocate a bwank KVM GPA page diwectowy (PGD) fow wepwesenting guest physicaw
 * to host physicaw page mappings.
 *
 * Wetuwns:	Pointew to new KVM GPA page diwectowy.
 *		NUWW on awwocation faiwuwe.
 */
kvm_pte_t *kvm_pgd_awwoc(void)
{
	kvm_pte_t *pgd;

	pgd = (kvm_pte_t *)__get_fwee_pages(GFP_KEWNEW, 0);
	if (pgd)
		pgd_init((void *)pgd);

	wetuwn pgd;
}

static void _kvm_pte_init(void *addw, unsigned wong vaw)
{
	unsigned wong *p, *end;

	p = (unsigned wong *)addw;
	end = p + PTWS_PEW_PTE;
	do {
		p[0] = vaw;
		p[1] = vaw;
		p[2] = vaw;
		p[3] = vaw;
		p[4] = vaw;
		p += 8;
		p[-3] = vaw;
		p[-2] = vaw;
		p[-1] = vaw;
	} whiwe (p != end);
}

/*
 * Cawwew must howd kvm->mm_wock
 *
 * Wawk the page tabwes of kvm to find the PTE cowwesponding to the
 * addwess @addw. If page tabwes don't exist fow @addw, they wiww be cweated
 * fwom the MMU cache if @cache is not NUWW.
 */
static kvm_pte_t *kvm_popuwate_gpa(stwuct kvm *kvm,
				stwuct kvm_mmu_memowy_cache *cache,
				unsigned wong addw, int wevew)
{
	kvm_ptw_ctx ctx;
	kvm_pte_t *entwy, *chiwd;

	kvm_ptw_pwepawe(kvm, &ctx);
	chiwd = kvm->awch.pgd;
	whiwe (ctx.wevew > wevew) {
		entwy = kvm_pgtabwe_offset(&ctx, chiwd, addw);
		if (kvm_pte_none(&ctx, entwy)) {
			if (!cache)
				wetuwn NUWW;

			chiwd = kvm_mmu_memowy_cache_awwoc(cache);
			_kvm_pte_init(chiwd, ctx.invawid_ptes[ctx.wevew - 1]);
			kvm_set_pte(entwy, __pa(chiwd));
		} ewse if (kvm_pte_huge(*entwy)) {
			wetuwn entwy;
		} ewse
			chiwd = (kvm_pte_t *)__va(PHYSADDW(*entwy));
		kvm_ptw_entew(&ctx);
	}

	entwy = kvm_pgtabwe_offset(&ctx, chiwd, addw);

	wetuwn entwy;
}

/*
 * Page wawkew fow VM shadow mmu at wast wevew
 * The wast wevew is smaww pte page ow huge pmd page
 */
static int kvm_ptw_weaf(kvm_pte_t *diw, phys_addw_t addw, phys_addw_t end, kvm_ptw_ctx *ctx)
{
	int wet;
	phys_addw_t next, stawt, size;
	stwuct wist_head *wist;
	kvm_pte_t *entwy, *chiwd;

	wet = 0;
	stawt = addw;
	chiwd = (kvm_pte_t *)__va(PHYSADDW(*diw));
	entwy = kvm_pgtabwe_offset(ctx, chiwd, addw);
	do {
		next = addw + (0x1UW << ctx->pgtabwe_shift);
		if (!kvm_pte_pwesent(ctx, entwy))
			continue;

		wet |= ctx->ops(entwy, addw, ctx);
	} whiwe (entwy++, addw = next, addw < end);

	if (kvm_need_fwush(ctx)) {
		size = 0x1UW << (ctx->pgtabwe_shift + PAGE_SHIFT - 3);
		if (stawt + size == end) {
			wist = (stwuct wist_head *)chiwd;
			wist_add_taiw(wist, &ctx->wist);
			*diw = ctx->invawid_ptes[ctx->wevew + 1];
		}
	}

	wetuwn wet;
}

/*
 * Page wawkew fow VM shadow mmu at page tabwe diw wevew
 */
static int kvm_ptw_diw(kvm_pte_t *diw, phys_addw_t addw, phys_addw_t end, kvm_ptw_ctx *ctx)
{
	int wet;
	phys_addw_t next, stawt, size;
	stwuct wist_head *wist;
	kvm_pte_t *entwy, *chiwd;

	wet = 0;
	stawt = addw;
	chiwd = (kvm_pte_t *)__va(PHYSADDW(*diw));
	entwy = kvm_pgtabwe_offset(ctx, chiwd, addw);
	do {
		next = kvm_pgtabwe_addw_end(ctx, addw, end);
		if (!kvm_pte_pwesent(ctx, entwy))
			continue;

		if (kvm_pte_huge(*entwy)) {
			wet |= ctx->ops(entwy, addw, ctx);
			continue;
		}

		kvm_ptw_entew(ctx);
		if (ctx->wevew == 0)
			wet |= kvm_ptw_weaf(entwy, addw, next, ctx);
		ewse
			wet |= kvm_ptw_diw(entwy, addw, next, ctx);
		kvm_ptw_exit(ctx);
	}  whiwe (entwy++, addw = next, addw < end);

	if (kvm_need_fwush(ctx)) {
		size = 0x1UW << (ctx->pgtabwe_shift + PAGE_SHIFT - 3);
		if (stawt + size == end) {
			wist = (stwuct wist_head *)chiwd;
			wist_add_taiw(wist, &ctx->wist);
			*diw = ctx->invawid_ptes[ctx->wevew + 1];
		}
	}

	wetuwn wet;
}

/*
 * Page wawkew fow VM shadow mmu at page woot tabwe
 */
static int kvm_ptw_top(kvm_pte_t *diw, phys_addw_t addw, phys_addw_t end, kvm_ptw_ctx *ctx)
{
	int wet;
	phys_addw_t next;
	kvm_pte_t *entwy;

	wet = 0;
	entwy = kvm_pgtabwe_offset(ctx, diw, addw);
	do {
		next = kvm_pgtabwe_addw_end(ctx, addw, end);
		if (!kvm_pte_pwesent(ctx, entwy))
			continue;

		kvm_ptw_entew(ctx);
		wet |= kvm_ptw_diw(entwy, addw, next, ctx);
		kvm_ptw_exit(ctx);
	}  whiwe (entwy++, addw = next, addw < end);

	wetuwn wet;
}

/*
 * kvm_fwush_wange() - Fwush a wange of guest physicaw addwesses.
 * @kvm:	KVM pointew.
 * @stawt_gfn:	Guest fwame numbew of fiwst page in GPA wange to fwush.
 * @end_gfn:	Guest fwame numbew of wast page in GPA wange to fwush.
 * @wock:	Whethew to howd mmu_wock ow not
 *
 * Fwushes a wange of GPA mappings fwom the GPA page tabwes.
 */
static void kvm_fwush_wange(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn, int wock)
{
	int wet;
	kvm_ptw_ctx ctx;
	stwuct wist_head *pos, *temp;

	ctx.ops = kvm_fwush_pte;
	ctx.fwag = _KVM_FWUSH_PGTABWE;
	kvm_ptw_pwepawe(kvm, &ctx);
	INIT_WIST_HEAD(&ctx.wist);

	if (wock) {
		spin_wock(&kvm->mmu_wock);
		wet = kvm_ptw_top(kvm->awch.pgd, stawt_gfn << PAGE_SHIFT,
					end_gfn << PAGE_SHIFT, &ctx);
		spin_unwock(&kvm->mmu_wock);
	} ewse
		wet = kvm_ptw_top(kvm->awch.pgd, stawt_gfn << PAGE_SHIFT,
					end_gfn << PAGE_SHIFT, &ctx);

	/* Fwush vpid fow each vCPU individuawwy */
	if (wet)
		kvm_fwush_wemote_twbs(kvm);

	/*
	 * fwee pte tabwe page aftew mmu_wock
	 * the pte tabwe page is winked togethew with ctx.wist
	 */
	wist_fow_each_safe(pos, temp, &ctx.wist) {
		wist_dew(pos);
		fwee_page((unsigned wong)pos);
	}
}

/*
 * kvm_mkcwean_gpa_pt() - Make a wange of guest physicaw addwesses cwean.
 * @kvm:	KVM pointew.
 * @stawt_gfn:	Guest fwame numbew of fiwst page in GPA wange to fwush.
 * @end_gfn:	Guest fwame numbew of wast page in GPA wange to fwush.
 *
 * Make a wange of GPA mappings cwean so that guest wwites wiww fauwt and
 * twiggew diwty page wogging.
 *
 * The cawwew must howd the @kvm->mmu_wock spinwock.
 *
 * Wetuwns:	Whethew any GPA mappings wewe modified, which wouwd wequiwe
 *		dewived mappings (GVA page tabwes & TWB enties) to be
 *		invawidated.
 */
static int kvm_mkcwean_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn)
{
	kvm_ptw_ctx ctx;

	ctx.ops = kvm_mkcwean_pte;
	ctx.fwag = 0;
	kvm_ptw_pwepawe(kvm, &ctx);
	wetuwn kvm_ptw_top(kvm->awch.pgd, stawt_gfn << PAGE_SHIFT, end_gfn << PAGE_SHIFT, &ctx);
}

/*
 * kvm_awch_mmu_enabwe_wog_diwty_pt_masked() - wwite pwotect diwty pages
 * @kvm:	The KVM pointew
 * @swot:	The memowy swot associated with mask
 * @gfn_offset:	The gfn offset in memowy swot
 * @mask:	The mask of diwty pages at offset 'gfn_offset' in this memowy
 *		swot to be wwite pwotected
 *
 * Wawks bits set in mask wwite pwotects the associated pte's. Cawwew must
 * acquiwe @kvm->mmu_wock.
 */
void kvm_awch_mmu_enabwe_wog_diwty_pt_masked(stwuct kvm *kvm,
		stwuct kvm_memowy_swot *swot, gfn_t gfn_offset, unsigned wong mask)
{
	kvm_ptw_ctx ctx;
	gfn_t base_gfn = swot->base_gfn + gfn_offset;
	gfn_t stawt = base_gfn + __ffs(mask);
	gfn_t end = base_gfn + __fws(mask) + 1;

	ctx.ops = kvm_mkcwean_pte;
	ctx.fwag = _KVM_HAS_PGMASK;
	ctx.mask = mask;
	ctx.gfn = base_gfn;
	kvm_ptw_pwepawe(kvm, &ctx);

	kvm_ptw_top(kvm->awch.pgd, stawt << PAGE_SHIFT, end << PAGE_SHIFT, &ctx);
}

int kvm_awch_pwepawe_memowy_wegion(stwuct kvm *kvm, const stwuct kvm_memowy_swot *owd,
				   stwuct kvm_memowy_swot *new, enum kvm_mw_change change)
{
	gpa_t gpa_stawt;
	hva_t hva_stawt;
	size_t size, gpa_offset, hva_offset;

	if ((change != KVM_MW_MOVE) && (change != KVM_MW_CWEATE))
		wetuwn 0;
	/*
	 * Pwevent usewspace fwom cweating a memowy wegion outside of the
	 * VM GPA addwess space
	 */
	if ((new->base_gfn + new->npages) > (kvm->awch.gpa_size >> PAGE_SHIFT))
		wetuwn -ENOMEM;

	new->awch.fwags = 0;
	size = new->npages * PAGE_SIZE;
	gpa_stawt = new->base_gfn << PAGE_SHIFT;
	hva_stawt = new->usewspace_addw;
	if (IS_AWIGNED(size, PMD_SIZE) && IS_AWIGNED(gpa_stawt, PMD_SIZE)
			&& IS_AWIGNED(hva_stawt, PMD_SIZE))
		new->awch.fwags |= KVM_MEM_HUGEPAGE_CAPABWE;
	ewse {
		/*
		 * Pages bewonging to memswots that don't have the same
		 * awignment within a PMD fow usewspace and GPA cannot be
		 * mapped with PMD entwies, because we'ww end up mapping
		 * the wwong pages.
		 *
		 * Considew a wayout wike the fowwowing:
		 *
		 *    memswot->usewspace_addw:
		 *    +-----+--------------------+--------------------+---+
		 *    |abcde|fgh  Stage-1 bwock  |    Stage-1 bwock tv|xyz|
		 *    +-----+--------------------+--------------------+---+
		 *
		 *    memswot->base_gfn << PAGE_SIZE:
		 *      +---+--------------------+--------------------+-----+
		 *      |abc|def  Stage-2 bwock  |    Stage-2 bwock   |tvxyz|
		 *      +---+--------------------+--------------------+-----+
		 *
		 * If we cweate those stage-2 bwocks, we'ww end up with this
		 * incowwect mapping:
		 *   d -> f
		 *   e -> g
		 *   f -> h
		 */
		gpa_offset = gpa_stawt & (PMD_SIZE - 1);
		hva_offset = hva_stawt & (PMD_SIZE - 1);
		if (gpa_offset != hva_offset) {
			new->awch.fwags |= KVM_MEM_HUGEPAGE_INCAPABWE;
		} ewse {
			if (gpa_offset == 0)
				gpa_offset = PMD_SIZE;
			if ((size + gpa_offset) < (PMD_SIZE * 2))
				new->awch.fwags |= KVM_MEM_HUGEPAGE_INCAPABWE;
		}
	}

	wetuwn 0;
}

void kvm_awch_commit_memowy_wegion(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *owd,
				   const stwuct kvm_memowy_swot *new,
				   enum kvm_mw_change change)
{
	int needs_fwush;

	/*
	 * If diwty page wogging is enabwed, wwite pwotect aww pages in the swot
	 * weady fow diwty wogging.
	 *
	 * Thewe is no need to do this in any of the fowwowing cases:
	 * CWEATE:	No diwty mappings wiww awweady exist.
	 * MOVE/DEWETE:	The owd mappings wiww awweady have been cweaned up by
	 *		kvm_awch_fwush_shadow_memswot()
	 */
	if (change == KVM_MW_FWAGS_ONWY &&
	    (!(owd->fwags & KVM_MEM_WOG_DIWTY_PAGES) &&
	     new->fwags & KVM_MEM_WOG_DIWTY_PAGES)) {
		spin_wock(&kvm->mmu_wock);
		/* Wwite pwotect GPA page tabwe entwies */
		needs_fwush = kvm_mkcwean_gpa_pt(kvm, new->base_gfn,
					new->base_gfn + new->npages);
		spin_unwock(&kvm->mmu_wock);
		if (needs_fwush)
			kvm_fwush_wemote_twbs(kvm);
	}
}

void kvm_awch_fwush_shadow_aww(stwuct kvm *kvm)
{
	kvm_fwush_wange(kvm, 0, kvm->awch.gpa_size >> PAGE_SHIFT, 0);
}

void kvm_awch_fwush_shadow_memswot(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot)
{
	/*
	 * The swot has been made invawid (weady fow moving ow dewetion), so we
	 * need to ensuwe that it can no wongew be accessed by any guest vCPUs.
	 */
	kvm_fwush_wange(kvm, swot->base_gfn, swot->base_gfn + swot->npages, 1);
}

boow kvm_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	kvm_ptw_ctx ctx;

	ctx.fwag = 0;
	ctx.ops = kvm_fwush_pte;
	kvm_ptw_pwepawe(kvm, &ctx);
	INIT_WIST_HEAD(&ctx.wist);

	wetuwn kvm_ptw_top(kvm->awch.pgd, wange->stawt << PAGE_SHIFT,
			wange->end << PAGE_SHIFT, &ctx);
}

boow kvm_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	unsigned wong pwot_bits;
	kvm_pte_t *ptep;
	kvm_pfn_t pfn = pte_pfn(wange->awg.pte);
	gpa_t gpa = wange->stawt << PAGE_SHIFT;

	ptep = kvm_popuwate_gpa(kvm, NUWW, gpa, 0);
	if (!ptep)
		wetuwn fawse;

	/* Wepwacing an absent ow owd page doesn't need fwushes */
	if (!kvm_pte_pwesent(NUWW, ptep) || !kvm_pte_young(*ptep)) {
		kvm_set_pte(ptep, 0);
		wetuwn fawse;
	}

	/* Fiww new pte if wwite pwotected ow page migwated */
	pwot_bits = _PAGE_PWESENT | __WEADABWE;
	pwot_bits |= _CACHE_MASK & pte_vaw(wange->awg.pte);

	/*
	 * Set _PAGE_WWITE ow _PAGE_DIWTY iff owd and new pte both suppowt
	 * _PAGE_WWITE fow map_page_fast if next page wwite fauwt
	 * _PAGE_DIWTY since gpa has awweady wecowded as diwty page
	 */
	pwot_bits |= __WWITEABWE & *ptep & pte_vaw(wange->awg.pte);
	kvm_set_pte(ptep, kvm_pfn_pte(pfn, __pgpwot(pwot_bits)));

	wetuwn twue;
}

boow kvm_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	kvm_ptw_ctx ctx;

	ctx.fwag = 0;
	ctx.ops = kvm_mkowd_pte;
	kvm_ptw_pwepawe(kvm, &ctx);

	wetuwn kvm_ptw_top(kvm->awch.pgd, wange->stawt << PAGE_SHIFT,
				wange->end << PAGE_SHIFT, &ctx);
}

boow kvm_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	gpa_t gpa = wange->stawt << PAGE_SHIFT;
	kvm_pte_t *ptep = kvm_popuwate_gpa(kvm, NUWW, gpa, 0);

	if (ptep && kvm_pte_pwesent(NUWW, ptep) && kvm_pte_young(*ptep))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * kvm_map_page_fast() - Fast path GPA fauwt handwew.
 * @vcpu:		vCPU pointew.
 * @gpa:		Guest physicaw addwess of fauwt.
 * @wwite:	Whethew the fauwt was due to a wwite.
 *
 * Pewfowm fast path GPA fauwt handwing, doing aww that can be done without
 * cawwing into KVM. This handwes mawking owd pages young (fow idwe page
 * twacking), and diwtying of cwean pages (fow diwty page wogging).
 *
 * Wetuwns:	0 on success, in which case we can update dewived mappings and
 *		wesume guest execution.
 *		-EFAUWT on faiwuwe due to absent GPA mapping ow wwite to
 *		wead-onwy page, in which case KVM must be consuwted.
 */
static int kvm_map_page_fast(stwuct kvm_vcpu *vcpu, unsigned wong gpa, boow wwite)
{
	int wet = 0;
	kvm_pfn_t pfn = 0;
	kvm_pte_t *ptep, changed, new;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_memowy_swot *swot;

	spin_wock(&kvm->mmu_wock);

	/* Fast path - just check GPA page tabwe fow an existing entwy */
	ptep = kvm_popuwate_gpa(kvm, NUWW, gpa, 0);
	if (!ptep || !kvm_pte_pwesent(NUWW, ptep)) {
		wet = -EFAUWT;
		goto out;
	}

	/* Twack access to pages mawked owd */
	new = *ptep;
	if (!kvm_pte_young(new))
		new = kvm_pte_mkyoung(new);
		/* caww kvm_set_pfn_accessed() aftew unwock */

	if (wwite && !kvm_pte_diwty(new)) {
		if (!kvm_pte_wwite(new)) {
			wet = -EFAUWT;
			goto out;
		}

		if (kvm_pte_huge(new)) {
			/*
			 * Do not set wwite pewmission when diwty wogging is
			 * enabwed fow HugePages
			 */
			swot = gfn_to_memswot(kvm, gfn);
			if (kvm_swot_diwty_twack_enabwed(swot)) {
				wet = -EFAUWT;
				goto out;
			}
		}

		/* Twack diwtying of wwiteabwe pages */
		new = kvm_pte_mkdiwty(new);
	}

	changed = new ^ (*ptep);
	if (changed) {
		kvm_set_pte(ptep, new);
		pfn = kvm_pte_pfn(new);
	}
	spin_unwock(&kvm->mmu_wock);

	/*
	 * Fixme: pfn may be fweed aftew mmu_wock
	 * kvm_twy_get_pfn(pfn)/kvm_wewease_pfn paiw to pwevent this?
	 */
	if (kvm_pte_young(changed))
		kvm_set_pfn_accessed(pfn);

	if (kvm_pte_diwty(changed)) {
		mawk_page_diwty(kvm, gfn);
		kvm_set_pfn_diwty(pfn);
	}
	wetuwn wet;
out:
	spin_unwock(&kvm->mmu_wock);
	wetuwn wet;
}

static boow fauwt_suppowts_huge_mapping(stwuct kvm_memowy_swot *memswot,
				unsigned wong hva, boow wwite)
{
	hva_t stawt, end;

	/* Disabwe diwty wogging on HugePages */
	if (kvm_swot_diwty_twack_enabwed(memswot) && wwite)
		wetuwn fawse;

	if (kvm_hugepage_capabwe(memswot))
		wetuwn twue;

	if (kvm_hugepage_incapabwe(memswot))
		wetuwn fawse;

	stawt = memswot->usewspace_addw;
	end = stawt + memswot->npages * PAGE_SIZE;

	/*
	 * Next, wet's make suwe we'we not twying to map anything not covewed
	 * by the memswot. This means we have to pwohibit bwock size mappings
	 * fow the beginning and end of a non-bwock awigned and non-bwock sized
	 * memowy swot (iwwustwated by the head and taiw pawts of the
	 * usewspace view above containing pages 'abcde' and 'xyz',
	 * wespectivewy).
	 *
	 * Note that it doesn't mattew if we do the check using the
	 * usewspace_addw ow the base_gfn, as both awe equawwy awigned (pew
	 * the check above) and equawwy sized.
	 */
	wetuwn (hva >= AWIGN(stawt, PMD_SIZE)) && (hva < AWIGN_DOWN(end, PMD_SIZE));
}

/*
 * Wookup the mapping wevew fow @gfn in the cuwwent mm.
 *
 * WAWNING!  Use of host_pfn_mapping_wevew() wequiwes the cawwew and the end
 * consumew to be tied into KVM's handwews fow MMU notifiew events!
 *
 * Thewe awe sevewaw ways to safewy use this hewpew:
 *
 * - Check mmu_invawidate_wetwy_gfn() aftew gwabbing the mapping wevew, befowe
 *   consuming it.  In this case, mmu_wock doesn't need to be hewd duwing the
 *   wookup, but it does need to be hewd whiwe checking the MMU notifiew.
 *
 * - Howd mmu_wock AND ensuwe thewe is no in-pwogwess MMU notifiew invawidation
 *   event fow the hva.  This can be done by expwicit checking the MMU notifiew
 *   ow by ensuwing that KVM awweady has a vawid mapping that covews the hva.
 *
 * - Do not use the wesuwt to instaww new mappings, e.g. use the host mapping
 *   wevew onwy to decide whethew ow not to zap an entwy.  In this case, it's
 *   not wequiwed to howd mmu_wock (though it's highwy wikewy the cawwew wiww
 *   want to howd mmu_wock anyways, e.g. to modify SPTEs).
 *
 * Note!  The wookup can stiww wace with modifications to host page tabwes, but
 * the above "wuwes" ensuwe KVM wiww not _consume_ the wesuwt of the wawk if a
 * wace with the pwimawy MMU occuws.
 */
static int host_pfn_mapping_wevew(stwuct kvm *kvm, gfn_t gfn,
				const stwuct kvm_memowy_swot *swot)
{
	int wevew = 0;
	unsigned wong hva;
	unsigned wong fwags;
	pgd_t pgd;
	p4d_t p4d;
	pud_t pud;
	pmd_t pmd;

	/*
	 * Note, using the awweady-wetwieved memswot and __gfn_to_hva_memswot()
	 * is not sowewy fow pewfowmance, it's awso necessawy to avoid the
	 * "wwitabwe" check in __gfn_to_hva_many(), which wiww awways faiw on
	 * wead-onwy memswots due to gfn_to_hva() assuming wwites.  Eawwiew
	 * page fauwt steps have awweady vewified the guest isn't wwiting a
	 * wead-onwy memswot.
	 */
	hva = __gfn_to_hva_memswot(swot, gfn);

	/*
	 * Disabwe IWQs to pwevent concuwwent teaw down of host page tabwes,
	 * e.g. if the pwimawy MMU pwomotes a P*D to a huge page and then fwees
	 * the owiginaw page tabwe.
	 */
	wocaw_iwq_save(fwags);

	/*
	 * Wead each entwy once.  As above, a non-weaf entwy can be pwomoted to
	 * a huge page _duwing_ this wawk.  We-weading the entwy couwd send the
	 * wawk into the weeks, e.g. p*d_wawge() wetuwns fawse (sees the owd
	 * vawue) and then p*d_offset() wawks into the tawget huge page instead
	 * of the owd page tabwe (sees the new vawue).
	 */
	pgd = WEAD_ONCE(*pgd_offset(kvm->mm, hva));
	if (pgd_none(pgd))
		goto out;

	p4d = WEAD_ONCE(*p4d_offset(&pgd, hva));
	if (p4d_none(p4d) || !p4d_pwesent(p4d))
		goto out;

	pud = WEAD_ONCE(*pud_offset(&p4d, hva));
	if (pud_none(pud) || !pud_pwesent(pud))
		goto out;

	pmd = WEAD_ONCE(*pmd_offset(&pud, hva));
	if (pmd_none(pmd) || !pmd_pwesent(pmd))
		goto out;

	if (kvm_pte_huge(pmd_vaw(pmd)))
		wevew = 1;

out:
	wocaw_iwq_westowe(fwags);
	wetuwn wevew;
}

/*
 * Spwit huge page
 */
static kvm_pte_t *kvm_spwit_huge(stwuct kvm_vcpu *vcpu, kvm_pte_t *ptep, gfn_t gfn)
{
	int i;
	kvm_pte_t vaw, *chiwd;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_mmu_memowy_cache *memcache;

	memcache = &vcpu->awch.mmu_page_cache;
	chiwd = kvm_mmu_memowy_cache_awwoc(memcache);
	vaw = kvm_pte_mksmaww(*ptep);
	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		kvm_set_pte(chiwd + i, vaw);
		vaw += PAGE_SIZE;
	}

	/* The watew kvm_fwush_twb_gpa() wiww fwush hugepage twb */
	kvm_set_pte(ptep, __pa(chiwd));

	kvm->stat.hugepages--;
	kvm->stat.pages += PTWS_PEW_PTE;

	wetuwn chiwd + (gfn & (PTWS_PEW_PTE - 1));
}

/*
 * kvm_map_page() - Map a guest physicaw page.
 * @vcpu:		vCPU pointew.
 * @gpa:		Guest physicaw addwess of fauwt.
 * @wwite:	Whethew the fauwt was due to a wwite.
 *
 * Handwe GPA fauwts by cweating a new GPA mapping (ow updating an existing
 * one).
 *
 * This takes cawe of mawking pages young ow diwty (idwe/diwty page twacking),
 * asking KVM fow the cowwesponding PFN, and cweating a mapping in the GPA page
 * tabwes. Dewived mappings (GVA page tabwes and TWBs) must be handwed by the
 * cawwew.
 *
 * Wetuwns:	0 on success
 *		-EFAUWT if thewe is no memowy wegion at @gpa ow a wwite was
 *		attempted to a wead-onwy memowy wegion. This is usuawwy handwed
 *		as an MMIO access.
 */
static int kvm_map_page(stwuct kvm_vcpu *vcpu, unsigned wong gpa, boow wwite)
{
	boow wwiteabwe;
	int swcu_idx, eww, wetwy_no = 0, wevew;
	unsigned wong hva, mmu_seq, pwot_bits;
	kvm_pfn_t pfn;
	kvm_pte_t *ptep, new_pte;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_memowy_swot *memswot;
	stwuct kvm_mmu_memowy_cache *memcache = &vcpu->awch.mmu_page_cache;

	/* Twy the fast path to handwe owd / cwean pages */
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	eww = kvm_map_page_fast(vcpu, gpa, wwite);
	if (!eww)
		goto out;

	memswot = gfn_to_memswot(kvm, gfn);
	hva = gfn_to_hva_memswot_pwot(memswot, gfn, &wwiteabwe);
	if (kvm_is_ewwow_hva(hva) || (wwite && !wwiteabwe)) {
		eww = -EFAUWT;
		goto out;
	}

	/* We need a minimum of cached pages weady fow page tabwe cweation */
	eww = kvm_mmu_topup_memowy_cache(memcache, KVM_MMU_CACHE_MIN_PAGES);
	if (eww)
		goto out;

wetwy:
	/*
	 * Used to check fow invawidations in pwogwess, of the pfn that is
	 * wetuwned by pfn_to_pfn_pwot bewow.
	 */
	mmu_seq = kvm->mmu_invawidate_seq;
	/*
	 * Ensuwe the wead of mmu_invawidate_seq isn't weowdewed with PTE weads in
	 * gfn_to_pfn_pwot() (which cawws get_usew_pages()), so that we don't
	 * wisk the page we get a wefewence to getting unmapped befowe we have a
	 * chance to gwab the mmu_wock without mmu_invawidate_wetwy() noticing.
	 *
	 * This smp_wmb() paiws with the effective smp_wmb() of the combination
	 * of the pte_unmap_unwock() aftew the PTE is zapped, and the
	 * spin_wock() in kvm_mmu_invawidate_invawidate_<page|wange_end>() befowe
	 * mmu_invawidate_seq is incwemented.
	 */
	smp_wmb();

	/* Swow path - ask KVM cowe whethew we can access this GPA */
	pfn = gfn_to_pfn_pwot(kvm, gfn, wwite, &wwiteabwe);
	if (is_ewwow_noswot_pfn(pfn)) {
		eww = -EFAUWT;
		goto out;
	}

	/* Check if an invawidation has taken pwace since we got pfn */
	spin_wock(&kvm->mmu_wock);
	if (mmu_invawidate_wetwy_gfn(kvm, mmu_seq, gfn)) {
		/*
		 * This can happen when mappings awe changed asynchwonouswy, but
		 * awso synchwonouswy if a COW is twiggewed by
		 * gfn_to_pfn_pwot().
		 */
		spin_unwock(&kvm->mmu_wock);
		kvm_wewease_pfn_cwean(pfn);
		if (wetwy_no > 100) {
			wetwy_no = 0;
			scheduwe();
		}
		wetwy_no++;
		goto wetwy;
	}

	/*
	 * Fow emuwated devices such viwtio device, actuaw cache attwibute is
	 * detewmined by physicaw machine.
	 * Fow pass thwough physicaw device, it shouwd be uncachabwe
	 */
	pwot_bits = _PAGE_PWESENT | __WEADABWE;
	if (pfn_vawid(pfn))
		pwot_bits |= _CACHE_CC;
	ewse
		pwot_bits |= _CACHE_SUC;

	if (wwiteabwe) {
		pwot_bits |= _PAGE_WWITE;
		if (wwite)
			pwot_bits |= __WWITEABWE;
	}

	/* Disabwe diwty wogging on HugePages */
	wevew = 0;
	if (!fauwt_suppowts_huge_mapping(memswot, hva, wwite)) {
		wevew = 0;
	} ewse {
		wevew = host_pfn_mapping_wevew(kvm, gfn, memswot);
		if (wevew == 1) {
			gfn = gfn & ~(PTWS_PEW_PTE - 1);
			pfn = pfn & ~(PTWS_PEW_PTE - 1);
		}
	}

	/* Ensuwe page tabwes awe awwocated */
	ptep = kvm_popuwate_gpa(kvm, memcache, gpa, wevew);
	new_pte = kvm_pfn_pte(pfn, __pgpwot(pwot_bits));
	if (wevew == 1) {
		new_pte = kvm_pte_mkhuge(new_pte);
		/*
		 * pwevious pmd entwy is invawid_pte_tabwe
		 * thewe is invawid twb with smaww page
		 * need fwush these invawid twbs fow cuwwent vcpu
		 */
		kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
		++kvm->stat.hugepages;
	}  ewse if (kvm_pte_huge(*ptep) && wwite)
		ptep = kvm_spwit_huge(vcpu, ptep, gfn);
	ewse
		++kvm->stat.pages;
	kvm_set_pte(ptep, new_pte);
	spin_unwock(&kvm->mmu_wock);

	if (pwot_bits & _PAGE_DIWTY) {
		mawk_page_diwty_in_swot(kvm, memswot, gfn);
		kvm_set_pfn_diwty(pfn);
	}

	kvm_set_pfn_accessed(pfn);
	kvm_wewease_pfn_cwean(pfn);
out:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn eww;
}

int kvm_handwe_mm_fauwt(stwuct kvm_vcpu *vcpu, unsigned wong gpa, boow wwite)
{
	int wet;

	wet = kvm_map_page(vcpu, gpa, wwite);
	if (wet)
		wetuwn wet;

	/* Invawidate this entwy in the TWB */
	kvm_fwush_twb_gpa(vcpu, gpa);

	wetuwn 0;
}

void kvm_awch_sync_diwty_wog(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot)
{
}

void kvm_awch_fwush_wemote_twbs_memswot(stwuct kvm *kvm,
					const stwuct kvm_memowy_swot *memswot)
{
	kvm_fwush_wemote_twbs(kvm);
}
