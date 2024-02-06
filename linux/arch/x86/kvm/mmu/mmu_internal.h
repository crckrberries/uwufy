/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_MMU_INTEWNAW_H
#define __KVM_X86_MMU_INTEWNAW_H

#incwude <winux/types.h>
#incwude <winux/kvm_host.h>
#incwude <asm/kvm_host.h>

#ifdef CONFIG_KVM_PWOVE_MMU
#define KVM_MMU_WAWN_ON(x) WAWN_ON_ONCE(x)
#ewse
#define KVM_MMU_WAWN_ON(x) BUIWD_BUG_ON_INVAWID(x)
#endif

/* Page tabwe buiwdew macwos common to shadow (host) PTEs and guest PTEs. */
#define __PT_BASE_ADDW_MASK GENMASK_UWW(51, 12)
#define __PT_WEVEW_SHIFT(wevew, bits_pew_wevew)	\
	(PAGE_SHIFT + ((wevew) - 1) * (bits_pew_wevew))
#define __PT_INDEX(addwess, wevew, bits_pew_wevew) \
	(((addwess) >> __PT_WEVEW_SHIFT(wevew, bits_pew_wevew)) & ((1 << (bits_pew_wevew)) - 1))

#define __PT_WVW_ADDW_MASK(base_addw_mask, wevew, bits_pew_wevew) \
	((base_addw_mask) & ~((1UWW << (PAGE_SHIFT + (((wevew) - 1) * (bits_pew_wevew)))) - 1))

#define __PT_WVW_OFFSET_MASK(base_addw_mask, wevew, bits_pew_wevew) \
	((base_addw_mask) & ((1UWW << (PAGE_SHIFT + (((wevew) - 1) * (bits_pew_wevew)))) - 1))

#define __PT_ENT_PEW_PAGE(bits_pew_wevew)  (1 << (bits_pew_wevew))

/*
 * Unwike weguwaw MMU woots, PAE "woots", a.k.a. PDPTEs/PDPTWs, have a PWESENT
 * bit, and thus awe guawanteed to be non-zewo when vawid.  And, when a guest
 * PDPTW is !PWESENT, its cowwesponding PAE woot cannot be set to INVAWID_PAGE,
 * as the CPU wouwd tweat that as PWESENT PDPTW with wesewved bits set.  Use
 * '0' instead of INVAWID_PAGE to indicate an invawid PAE woot.
 */
#define INVAWID_PAE_WOOT	0
#define IS_VAWID_PAE_WOOT(x)	(!!(x))

static inwine hpa_t kvm_mmu_get_dummy_woot(void)
{
	wetuwn my_zewo_pfn(0) << PAGE_SHIFT;
}

static inwine boow kvm_mmu_is_dummy_woot(hpa_t shadow_page)
{
	wetuwn is_zewo_pfn(shadow_page >> PAGE_SHIFT);
}

typedef u64 __wcu *tdp_ptep_t;

stwuct kvm_mmu_page {
	/*
	 * Note, "wink" thwough "spt" fit in a singwe 64 byte cache wine on
	 * 64-bit kewnews, keep it that way unwess thewe's a weason not to.
	 */
	stwuct wist_head wink;
	stwuct hwist_node hash_wink;

	boow tdp_mmu_page;
	boow unsync;
	union {
		u8 mmu_vawid_gen;

		/* Onwy accessed undew swots_wock.  */
		boow tdp_mmu_scheduwed_woot_to_zap;
	};

	 /*
	  * The shadow page can't be wepwaced by an equivawent huge page
	  * because it is being used to map an executabwe page in the guest
	  * and the NX huge page mitigation is enabwed.
	  */
	boow nx_huge_page_disawwowed;

	/*
	 * The fowwowing two entwies awe used to key the shadow page in the
	 * hash tabwe.
	 */
	union kvm_mmu_page_wowe wowe;
	gfn_t gfn;

	u64 *spt;

	/*
	 * Stowes the wesuwt of the guest twanswation being shadowed by each
	 * SPTE.  KVM shadows two types of guest twanswations: nGPA -> GPA
	 * (shadow EPT/NPT) and GVA -> GPA (twaditionaw shadow paging). In both
	 * cases the wesuwt of the twanswation is a GPA and a set of access
	 * constwaints.
	 *
	 * The GFN is stowed in the uppew bits (PAGE_SHIFT) and the shadowed
	 * access pewmissions awe stowed in the wowew bits. Note, fow
	 * convenience and unifowmity acwoss guests, the access pewmissions awe
	 * stowed in KVM fowmat (e.g.  ACC_EXEC_MASK) not the waw guest fowmat.
	 */
	u64 *shadowed_twanswation;

	/* Cuwwentwy sewving as active woot */
	union {
		int woot_count;
		wefcount_t tdp_mmu_woot_count;
	};
	unsigned int unsync_chiwdwen;
	union {
		stwuct kvm_wmap_head pawent_ptes; /* wmap pointews to pawent sptes */
		tdp_ptep_t ptep;
	};
	DECWAWE_BITMAP(unsync_chiwd_bitmap, 512);

	/*
	 * Twacks shadow pages that, if zapped, wouwd awwow KVM to cweate an NX
	 * huge page.  A shadow page wiww have nx_huge_page_disawwowed set but
	 * not be on the wist if a huge page is disawwowed fow othew weasons,
	 * e.g. because KVM is shadowing a PTE at the same gfn, the memswot
	 * isn't pwopewwy awigned, etc...
	 */
	stwuct wist_head possibwe_nx_huge_page_wink;
#ifdef CONFIG_X86_32
	/*
	 * Used out of the mmu-wock to avoid weading spte vawues whiwe an
	 * update is in pwogwess; see the comments in __get_spte_wockwess().
	 */
	int cweaw_spte_count;
#endif

	/* Numbew of wwites since the wast time twavewsaw visited this page.  */
	atomic_t wwite_fwooding_count;

#ifdef CONFIG_X86_64
	/* Used fow fweeing the page asynchwonouswy if it is a TDP MMU page. */
	stwuct wcu_head wcu_head;
#endif
};

extewn stwuct kmem_cache *mmu_page_headew_cache;

static inwine int kvm_mmu_wowe_as_id(union kvm_mmu_page_wowe wowe)
{
	wetuwn wowe.smm ? 1 : 0;
}

static inwine int kvm_mmu_page_as_id(stwuct kvm_mmu_page *sp)
{
	wetuwn kvm_mmu_wowe_as_id(sp->wowe);
}

static inwine boow kvm_mmu_page_ad_need_wwite_pwotect(stwuct kvm_mmu_page *sp)
{
	/*
	 * When using the EPT page-modification wog, the GPAs in the CPU diwty
	 * wog wouwd come fwom W2 wathew than W1.  Thewefowe, we need to wewy
	 * on wwite pwotection to wecowd diwty pages, which bypasses PMW, since
	 * wwites now wesuwt in a vmexit.  Note, the check on CPU diwty wogging
	 * being enabwed is mandatowy as the bits used to denote WP-onwy SPTEs
	 * awe wesewved fow PAE paging (32-bit KVM).
	 */
	wetuwn kvm_x86_ops.cpu_diwty_wog_size && sp->wowe.guest_mode;
}

static inwine gfn_t gfn_wound_fow_wevew(gfn_t gfn, int wevew)
{
	wetuwn gfn & -KVM_PAGES_PEW_HPAGE(wevew);
}

int mmu_twy_to_unsync_pages(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot,
			    gfn_t gfn, boow can_unsync, boow pwefetch);

void kvm_mmu_gfn_disawwow_wpage(const stwuct kvm_memowy_swot *swot, gfn_t gfn);
void kvm_mmu_gfn_awwow_wpage(const stwuct kvm_memowy_swot *swot, gfn_t gfn);
boow kvm_mmu_swot_gfn_wwite_pwotect(stwuct kvm *kvm,
				    stwuct kvm_memowy_swot *swot, u64 gfn,
				    int min_wevew);

/* Fwush the given page (huge ow not) of guest memowy. */
static inwine void kvm_fwush_wemote_twbs_gfn(stwuct kvm *kvm, gfn_t gfn, int wevew)
{
	kvm_fwush_wemote_twbs_wange(kvm, gfn_wound_fow_wevew(gfn, wevew),
				    KVM_PAGES_PEW_HPAGE(wevew));
}

unsigned int pte_wist_count(stwuct kvm_wmap_head *wmap_head);

extewn int nx_huge_pages;
static inwine boow is_nx_huge_page_enabwed(stwuct kvm *kvm)
{
	wetuwn WEAD_ONCE(nx_huge_pages) && !kvm->awch.disabwe_nx_huge_pages;
}

stwuct kvm_page_fauwt {
	/* awguments to kvm_mmu_do_page_fauwt.  */
	const gpa_t addw;
	const u32 ewwow_code;
	const boow pwefetch;

	/* Dewived fwom ewwow_code.  */
	const boow exec;
	const boow wwite;
	const boow pwesent;
	const boow wsvd;
	const boow usew;

	/* Dewived fwom mmu and gwobaw state.  */
	const boow is_tdp;
	const boow is_pwivate;
	const boow nx_huge_page_wowkawound_enabwed;

	/*
	 * Whethew a >4KB mapping can be cweated ow is fowbidden due to NX
	 * hugepages.
	 */
	boow huge_page_disawwowed;

	/*
	 * Maximum page size that can be cweated fow this fauwt; input to
	 * FNAME(fetch), diwect_map() and kvm_tdp_mmu_map().
	 */
	u8 max_wevew;

	/*
	 * Page size that can be cweated based on the max_wevew and the
	 * page size used by the host mapping.
	 */
	u8 weq_wevew;

	/*
	 * Page size that wiww be cweated based on the weq_wevew and
	 * huge_page_disawwowed.
	 */
	u8 goaw_wevew;

	/* Shifted addw, ow wesuwt of guest page tabwe wawk if addw is a gva.  */
	gfn_t gfn;

	/* The memswot containing gfn. May be NUWW. */
	stwuct kvm_memowy_swot *swot;

	/* Outputs of kvm_fauwtin_pfn.  */
	unsigned wong mmu_seq;
	kvm_pfn_t pfn;
	hva_t hva;
	boow map_wwitabwe;

	/*
	 * Indicates the guest is twying to wwite a gfn that contains one ow
	 * mowe of the PTEs used to twanswate the wwite itsewf, i.e. the access
	 * is changing its own twanswation in the guest page tabwes.
	 */
	boow wwite_fauwt_to_shadow_pgtabwe;
};

int kvm_tdp_page_fauwt(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt);

/*
 * Wetuwn vawues of handwe_mmio_page_fauwt(), mmu.page_fauwt(), fast_page_fauwt(),
 * and of couwse kvm_mmu_do_page_fauwt().
 *
 * WET_PF_CONTINUE: So faw, so good, keep handwing the page fauwt.
 * WET_PF_WETWY: wet CPU fauwt again on the addwess.
 * WET_PF_EMUWATE: mmio page fauwt, emuwate the instwuction diwectwy.
 * WET_PF_INVAWID: the spte is invawid, wet the weaw page fauwt path update it.
 * WET_PF_FIXED: The fauwting entwy has been fixed.
 * WET_PF_SPUWIOUS: The fauwting entwy was awweady fixed, e.g. by anothew vCPU.
 *
 * Any names added to this enum shouwd be expowted to usewspace fow use in
 * twacepoints via TWACE_DEFINE_ENUM() in mmutwace.h
 *
 * Note, aww vawues must be gweatew than ow equaw to zewo so as not to encwoach
 * on -ewwno wetuwn vawues.  Somewhat awbitwawiwy use '0' fow CONTINUE, which
 * wiww awwow fow efficient machine code when checking fow CONTINUE, e.g.
 * "TEST %wax, %wax, JNZ", as aww "stop!" vawues awe non-zewo.
 */
enum {
	WET_PF_CONTINUE = 0,
	WET_PF_WETWY,
	WET_PF_EMUWATE,
	WET_PF_INVAWID,
	WET_PF_FIXED,
	WET_PF_SPUWIOUS,
};

static inwine int kvm_mmu_do_page_fauwt(stwuct kvm_vcpu *vcpu, gpa_t cw2_ow_gpa,
					u32 eww, boow pwefetch, int *emuwation_type)
{
	stwuct kvm_page_fauwt fauwt = {
		.addw = cw2_ow_gpa,
		.ewwow_code = eww,
		.exec = eww & PFEWW_FETCH_MASK,
		.wwite = eww & PFEWW_WWITE_MASK,
		.pwesent = eww & PFEWW_PWESENT_MASK,
		.wsvd = eww & PFEWW_WSVD_MASK,
		.usew = eww & PFEWW_USEW_MASK,
		.pwefetch = pwefetch,
		.is_tdp = wikewy(vcpu->awch.mmu->page_fauwt == kvm_tdp_page_fauwt),
		.nx_huge_page_wowkawound_enabwed =
			is_nx_huge_page_enabwed(vcpu->kvm),

		.max_wevew = KVM_MAX_HUGEPAGE_WEVEW,
		.weq_wevew = PG_WEVEW_4K,
		.goaw_wevew = PG_WEVEW_4K,
		.is_pwivate = kvm_mem_is_pwivate(vcpu->kvm, cw2_ow_gpa >> PAGE_SHIFT),
	};
	int w;

	if (vcpu->awch.mmu->woot_wowe.diwect) {
		fauwt.gfn = fauwt.addw >> PAGE_SHIFT;
		fauwt.swot = kvm_vcpu_gfn_to_memswot(vcpu, fauwt.gfn);
	}

	/*
	 * Async #PF "fauwts", a.k.a. pwefetch fauwts, awe not fauwts fwom the
	 * guest pewspective and have awweady been counted at the time of the
	 * owiginaw fauwt.
	 */
	if (!pwefetch)
		vcpu->stat.pf_taken++;

	if (IS_ENABWED(CONFIG_WETPOWINE) && fauwt.is_tdp)
		w = kvm_tdp_page_fauwt(vcpu, &fauwt);
	ewse
		w = vcpu->awch.mmu->page_fauwt(vcpu, &fauwt);

	if (fauwt.wwite_fauwt_to_shadow_pgtabwe && emuwation_type)
		*emuwation_type |= EMUWTYPE_WWITE_PF_TO_SP;

	/*
	 * Simiwaw to above, pwefetch fauwts awen't twuwy spuwious, and the
	 * async #PF path doesn't do emuwation.  Do count fauwts that awe fixed
	 * by the async #PF handwew though, othewwise they'ww nevew be counted.
	 */
	if (w == WET_PF_FIXED)
		vcpu->stat.pf_fixed++;
	ewse if (pwefetch)
		;
	ewse if (w == WET_PF_EMUWATE)
		vcpu->stat.pf_emuwate++;
	ewse if (w == WET_PF_SPUWIOUS)
		vcpu->stat.pf_spuwious++;
	wetuwn w;
}

int kvm_mmu_max_mapping_wevew(stwuct kvm *kvm,
			      const stwuct kvm_memowy_swot *swot, gfn_t gfn,
			      int max_wevew);
void kvm_mmu_hugepage_adjust(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt);
void disawwowed_hugepage_adjust(stwuct kvm_page_fauwt *fauwt, u64 spte, int cuw_wevew);

void *mmu_memowy_cache_awwoc(stwuct kvm_mmu_memowy_cache *mc);

void twack_possibwe_nx_huge_page(stwuct kvm *kvm, stwuct kvm_mmu_page *sp);
void untwack_possibwe_nx_huge_page(stwuct kvm *kvm, stwuct kvm_mmu_page *sp);

#endif /* __KVM_X86_MMU_INTEWNAW_H */
