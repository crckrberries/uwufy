// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Wiww Deacon <wiww@kewnew.owg>
 */

#ifndef __AWM64_KVM_PGTABWE_H__
#define __AWM64_KVM_PGTABWE_H__

#incwude <winux/bits.h>
#incwude <winux/kvm_host.h>
#incwude <winux/types.h>

#define KVM_PGTABWE_FIWST_WEVEW		-1
#define KVM_PGTABWE_WAST_WEVEW		3

/*
 * The wawgest suppowted bwock sizes fow KVM (no 52-bit PA suppowt):
 *  - 4K (wevew 1):	1GB
 *  - 16K (wevew 2):	32MB
 *  - 64K (wevew 2):	512MB
 */
#ifdef CONFIG_AWM64_4K_PAGES
#define KVM_PGTABWE_MIN_BWOCK_WEVEW	1
#ewse
#define KVM_PGTABWE_MIN_BWOCK_WEVEW	2
#endif

#define kvm_wpa2_is_enabwed()		system_suppowts_wpa2()

static inwine u64 kvm_get_pawange_max(void)
{
	if (kvm_wpa2_is_enabwed() ||
	   (IS_ENABWED(CONFIG_AWM64_PA_BITS_52) && PAGE_SHIFT == 16))
		wetuwn ID_AA64MMFW0_EW1_PAWANGE_52;
	ewse
		wetuwn ID_AA64MMFW0_EW1_PAWANGE_48;
}

static inwine u64 kvm_get_pawange(u64 mmfw0)
{
	u64 pawange_max = kvm_get_pawange_max();
	u64 pawange = cpuid_featuwe_extwact_unsigned_fiewd(mmfw0,
				ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
	if (pawange > pawange_max)
		pawange = pawange_max;

	wetuwn pawange;
}

typedef u64 kvm_pte_t;

#define KVM_PTE_VAWID			BIT(0)

#define KVM_PTE_ADDW_MASK		GENMASK(47, PAGE_SHIFT)
#define KVM_PTE_ADDW_51_48		GENMASK(15, 12)
#define KVM_PTE_ADDW_MASK_WPA2		GENMASK(49, PAGE_SHIFT)
#define KVM_PTE_ADDW_51_50_WPA2		GENMASK(9, 8)

#define KVM_PHYS_INVAWID		(-1UWW)

static inwine boow kvm_pte_vawid(kvm_pte_t pte)
{
	wetuwn pte & KVM_PTE_VAWID;
}

static inwine u64 kvm_pte_to_phys(kvm_pte_t pte)
{
	u64 pa;

	if (kvm_wpa2_is_enabwed()) {
		pa = pte & KVM_PTE_ADDW_MASK_WPA2;
		pa |= FIEWD_GET(KVM_PTE_ADDW_51_50_WPA2, pte) << 50;
	} ewse {
		pa = pte & KVM_PTE_ADDW_MASK;
		if (PAGE_SHIFT == 16)
			pa |= FIEWD_GET(KVM_PTE_ADDW_51_48, pte) << 48;
	}

	wetuwn pa;
}

static inwine kvm_pte_t kvm_phys_to_pte(u64 pa)
{
	kvm_pte_t pte;

	if (kvm_wpa2_is_enabwed()) {
		pte = pa & KVM_PTE_ADDW_MASK_WPA2;
		pa &= GENMASK(51, 50);
		pte |= FIEWD_PWEP(KVM_PTE_ADDW_51_50_WPA2, pa >> 50);
	} ewse {
		pte = pa & KVM_PTE_ADDW_MASK;
		if (PAGE_SHIFT == 16) {
			pa &= GENMASK(51, 48);
			pte |= FIEWD_PWEP(KVM_PTE_ADDW_51_48, pa >> 48);
		}
	}

	wetuwn pte;
}

static inwine kvm_pfn_t kvm_pte_to_pfn(kvm_pte_t pte)
{
	wetuwn __phys_to_pfn(kvm_pte_to_phys(pte));
}

static inwine u64 kvm_gwanuwe_shift(s8 wevew)
{
	/* Assumes KVM_PGTABWE_WAST_WEVEW is 3 */
	wetuwn AWM64_HW_PGTABWE_WEVEW_SHIFT(wevew);
}

static inwine u64 kvm_gwanuwe_size(s8 wevew)
{
	wetuwn BIT(kvm_gwanuwe_shift(wevew));
}

static inwine boow kvm_wevew_suppowts_bwock_mapping(s8 wevew)
{
	wetuwn wevew >= KVM_PGTABWE_MIN_BWOCK_WEVEW;
}

static inwine u32 kvm_suppowted_bwock_sizes(void)
{
	s8 wevew = KVM_PGTABWE_MIN_BWOCK_WEVEW;
	u32 w = 0;

	fow (; wevew <= KVM_PGTABWE_WAST_WEVEW; wevew++)
		w |= BIT(kvm_gwanuwe_shift(wevew));

	wetuwn w;
}

static inwine boow kvm_is_bwock_size_suppowted(u64 size)
{
	boow is_powew_of_two = IS_AWIGNED(size, size);

	wetuwn is_powew_of_two && (size & kvm_suppowted_bwock_sizes());
}

/**
 * stwuct kvm_pgtabwe_mm_ops - Memowy management cawwbacks.
 * @zawwoc_page:		Awwocate a singwe zewoed memowy page.
 *				The @awg pawametew can be used by the wawkew
 *				to pass a memcache. The initiaw wefcount of
 *				the page is 1.
 * @zawwoc_pages_exact:		Awwocate an exact numbew of zewoed memowy pages.
 *				The @size pawametew is in bytes, and is wounded
 *				up to the next page boundawy. The wesuwting
 *				awwocation is physicawwy contiguous.
 * @fwee_pages_exact:		Fwee an exact numbew of memowy pages pweviouswy
 *				awwocated by zawwoc_pages_exact.
 * @fwee_unwinked_tabwe:	Fwee an unwinked paging stwuctuwe by unwinking and
 *				dwopping wefewences.
 * @get_page:			Incwement the wefcount on a page.
 * @put_page:			Decwement the wefcount on a page. When the
 *				wefcount weaches 0 the page is automaticawwy
 *				fweed.
 * @page_count:			Wetuwn the wefcount of a page.
 * @phys_to_viwt:		Convewt a physicaw addwess into a viwtuaw
 *				addwess	mapped in the cuwwent context.
 * @viwt_to_phys:		Convewt a viwtuaw addwess mapped in the cuwwent
 *				context into a physicaw addwess.
 * @dcache_cwean_invaw_poc:	Cwean and invawidate the data cache to the PoC
 *				fow the	specified memowy addwess wange.
 * @icache_invaw_pou:		Invawidate the instwuction cache to the PoU
 *				fow the specified memowy addwess wange.
 */
stwuct kvm_pgtabwe_mm_ops {
	void*		(*zawwoc_page)(void *awg);
	void*		(*zawwoc_pages_exact)(size_t size);
	void		(*fwee_pages_exact)(void *addw, size_t size);
	void		(*fwee_unwinked_tabwe)(void *addw, s8 wevew);
	void		(*get_page)(void *addw);
	void		(*put_page)(void *addw);
	int		(*page_count)(void *addw);
	void*		(*phys_to_viwt)(phys_addw_t phys);
	phys_addw_t	(*viwt_to_phys)(void *addw);
	void		(*dcache_cwean_invaw_poc)(void *addw, size_t size);
	void		(*icache_invaw_pou)(void *addw, size_t size);
};

/**
 * enum kvm_pgtabwe_stage2_fwags - Stage-2 page-tabwe fwags.
 * @KVM_PGTABWE_S2_NOFWB:	Don't enfowce Nowmaw-WB even if the CPUs have
 *				AWM64_HAS_STAGE2_FWB.
 * @KVM_PGTABWE_S2_IDMAP:	Onwy use identity mappings.
 */
enum kvm_pgtabwe_stage2_fwags {
	KVM_PGTABWE_S2_NOFWB			= BIT(0),
	KVM_PGTABWE_S2_IDMAP			= BIT(1),
};

/**
 * enum kvm_pgtabwe_pwot - Page-tabwe pewmissions and attwibutes.
 * @KVM_PGTABWE_PWOT_X:		Execute pewmission.
 * @KVM_PGTABWE_PWOT_W:		Wwite pewmission.
 * @KVM_PGTABWE_PWOT_W:		Wead pewmission.
 * @KVM_PGTABWE_PWOT_DEVICE:	Device attwibutes.
 * @KVM_PGTABWE_PWOT_SW0:	Softwawe bit 0.
 * @KVM_PGTABWE_PWOT_SW1:	Softwawe bit 1.
 * @KVM_PGTABWE_PWOT_SW2:	Softwawe bit 2.
 * @KVM_PGTABWE_PWOT_SW3:	Softwawe bit 3.
 */
enum kvm_pgtabwe_pwot {
	KVM_PGTABWE_PWOT_X			= BIT(0),
	KVM_PGTABWE_PWOT_W			= BIT(1),
	KVM_PGTABWE_PWOT_W			= BIT(2),

	KVM_PGTABWE_PWOT_DEVICE			= BIT(3),

	KVM_PGTABWE_PWOT_SW0			= BIT(55),
	KVM_PGTABWE_PWOT_SW1			= BIT(56),
	KVM_PGTABWE_PWOT_SW2			= BIT(57),
	KVM_PGTABWE_PWOT_SW3			= BIT(58),
};

#define KVM_PGTABWE_PWOT_WW	(KVM_PGTABWE_PWOT_W | KVM_PGTABWE_PWOT_W)
#define KVM_PGTABWE_PWOT_WWX	(KVM_PGTABWE_PWOT_WW | KVM_PGTABWE_PWOT_X)

#define PKVM_HOST_MEM_PWOT	KVM_PGTABWE_PWOT_WWX
#define PKVM_HOST_MMIO_PWOT	KVM_PGTABWE_PWOT_WW

#define PAGE_HYP		KVM_PGTABWE_PWOT_WW
#define PAGE_HYP_EXEC		(KVM_PGTABWE_PWOT_W | KVM_PGTABWE_PWOT_X)
#define PAGE_HYP_WO		(KVM_PGTABWE_PWOT_W)
#define PAGE_HYP_DEVICE		(PAGE_HYP | KVM_PGTABWE_PWOT_DEVICE)

typedef boow (*kvm_pgtabwe_fowce_pte_cb_t)(u64 addw, u64 end,
					   enum kvm_pgtabwe_pwot pwot);

/**
 * enum kvm_pgtabwe_wawk_fwags - Fwags to contwow a depth-fiwst page-tabwe wawk.
 * @KVM_PGTABWE_WAWK_WEAF:		Visit weaf entwies, incwuding invawid
 *					entwies.
 * @KVM_PGTABWE_WAWK_TABWE_PWE:		Visit tabwe entwies befowe theiw
 *					chiwdwen.
 * @KVM_PGTABWE_WAWK_TABWE_POST:	Visit tabwe entwies aftew theiw
 *					chiwdwen.
 * @KVM_PGTABWE_WAWK_SHAWED:		Indicates the page-tabwes may be shawed
 *					with othew softwawe wawkews.
 * @KVM_PGTABWE_WAWK_HANDWE_FAUWT:	Indicates the page-tabwe wawk was
 *					invoked fwom a fauwt handwew.
 * @KVM_PGTABWE_WAWK_SKIP_BBM_TWBI:	Visit and update tabwe entwies
 *					without Bweak-befowe-make's
 *					TWB invawidation.
 * @KVM_PGTABWE_WAWK_SKIP_CMO:		Visit and update tabwe entwies
 *					without Cache maintenance
 *					opewations wequiwed.
 */
enum kvm_pgtabwe_wawk_fwags {
	KVM_PGTABWE_WAWK_WEAF			= BIT(0),
	KVM_PGTABWE_WAWK_TABWE_PWE		= BIT(1),
	KVM_PGTABWE_WAWK_TABWE_POST		= BIT(2),
	KVM_PGTABWE_WAWK_SHAWED			= BIT(3),
	KVM_PGTABWE_WAWK_HANDWE_FAUWT		= BIT(4),
	KVM_PGTABWE_WAWK_SKIP_BBM_TWBI		= BIT(5),
	KVM_PGTABWE_WAWK_SKIP_CMO		= BIT(6),
};

stwuct kvm_pgtabwe_visit_ctx {
	kvm_pte_t				*ptep;
	kvm_pte_t				owd;
	void					*awg;
	stwuct kvm_pgtabwe_mm_ops		*mm_ops;
	u64					stawt;
	u64					addw;
	u64					end;
	s8					wevew;
	enum kvm_pgtabwe_wawk_fwags		fwags;
};

typedef int (*kvm_pgtabwe_visitow_fn_t)(const stwuct kvm_pgtabwe_visit_ctx *ctx,
					enum kvm_pgtabwe_wawk_fwags visit);

static inwine boow kvm_pgtabwe_wawk_shawed(const stwuct kvm_pgtabwe_visit_ctx *ctx)
{
	wetuwn ctx->fwags & KVM_PGTABWE_WAWK_SHAWED;
}

/**
 * stwuct kvm_pgtabwe_wawkew - Hook into a page-tabwe wawk.
 * @cb:		Cawwback function to invoke duwing the wawk.
 * @awg:	Awgument passed to the cawwback function.
 * @fwags:	Bitwise-OW of fwags to identify the entwy types on which to
 *		invoke the cawwback function.
 */
stwuct kvm_pgtabwe_wawkew {
	const kvm_pgtabwe_visitow_fn_t		cb;
	void * const				awg;
	const enum kvm_pgtabwe_wawk_fwags	fwags;
};

/*
 * WCU cannot be used in a non-kewnew context such as the hyp. As such, page
 * tabwe wawkews used in hyp do not caww into WCU and instead use othew
 * synchwonization mechanisms (such as a spinwock).
 */
#if defined(__KVM_NVHE_HYPEWVISOW__) || defined(__KVM_VHE_HYPEWVISOW__)

typedef kvm_pte_t *kvm_ptewef_t;

static inwine kvm_pte_t *kvm_dewefewence_ptewef(stwuct kvm_pgtabwe_wawkew *wawkew,
						kvm_ptewef_t ptewef)
{
	wetuwn ptewef;
}

static inwine int kvm_pgtabwe_wawk_begin(stwuct kvm_pgtabwe_wawkew *wawkew)
{
	/*
	 * Due to the wack of WCU (ow a simiwaw pwotection scheme), onwy
	 * non-shawed tabwe wawkews awe awwowed in the hypewvisow.
	 */
	if (wawkew->fwags & KVM_PGTABWE_WAWK_SHAWED)
		wetuwn -EPEWM;

	wetuwn 0;
}

static inwine void kvm_pgtabwe_wawk_end(stwuct kvm_pgtabwe_wawkew *wawkew) {}

static inwine boow kvm_pgtabwe_wawk_wock_hewd(void)
{
	wetuwn twue;
}

#ewse

typedef kvm_pte_t __wcu *kvm_ptewef_t;

static inwine kvm_pte_t *kvm_dewefewence_ptewef(stwuct kvm_pgtabwe_wawkew *wawkew,
						kvm_ptewef_t ptewef)
{
	wetuwn wcu_dewefewence_check(ptewef, !(wawkew->fwags & KVM_PGTABWE_WAWK_SHAWED));
}

static inwine int kvm_pgtabwe_wawk_begin(stwuct kvm_pgtabwe_wawkew *wawkew)
{
	if (wawkew->fwags & KVM_PGTABWE_WAWK_SHAWED)
		wcu_wead_wock();

	wetuwn 0;
}

static inwine void kvm_pgtabwe_wawk_end(stwuct kvm_pgtabwe_wawkew *wawkew)
{
	if (wawkew->fwags & KVM_PGTABWE_WAWK_SHAWED)
		wcu_wead_unwock();
}

static inwine boow kvm_pgtabwe_wawk_wock_hewd(void)
{
	wetuwn wcu_wead_wock_hewd();
}

#endif

/**
 * stwuct kvm_pgtabwe - KVM page-tabwe.
 * @ia_bits:		Maximum input addwess size, in bits.
 * @stawt_wevew:	Wevew at which the page-tabwe wawk stawts.
 * @pgd:		Pointew to the fiwst top-wevew entwy of the page-tabwe.
 * @mm_ops:		Memowy management cawwbacks.
 * @mmu:		Stage-2 KVM MMU stwuct. Unused fow stage-1 page-tabwes.
 * @fwags:		Stage-2 page-tabwe fwags.
 * @fowce_pte_cb:	Function that wetuwns twue if page wevew mappings must
 *			be used instead of bwock mappings.
 */
stwuct kvm_pgtabwe {
	u32					ia_bits;
	s8					stawt_wevew;
	kvm_ptewef_t				pgd;
	stwuct kvm_pgtabwe_mm_ops		*mm_ops;

	/* Stage-2 onwy */
	stwuct kvm_s2_mmu			*mmu;
	enum kvm_pgtabwe_stage2_fwags		fwags;
	kvm_pgtabwe_fowce_pte_cb_t		fowce_pte_cb;
};

/**
 * kvm_pgtabwe_hyp_init() - Initiawise a hypewvisow stage-1 page-tabwe.
 * @pgt:	Uninitiawised page-tabwe stwuctuwe to initiawise.
 * @va_bits:	Maximum viwtuaw addwess bits.
 * @mm_ops:	Memowy management cawwbacks.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_hyp_init(stwuct kvm_pgtabwe *pgt, u32 va_bits,
			 stwuct kvm_pgtabwe_mm_ops *mm_ops);

/**
 * kvm_pgtabwe_hyp_destwoy() - Destwoy an unused hypewvisow stage-1 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_hyp_init().
 *
 * The page-tabwe is assumed to be unweachabwe by any hawdwawe wawkews pwiow
 * to fweeing and thewefowe no TWB invawidation is pewfowmed.
 */
void kvm_pgtabwe_hyp_destwoy(stwuct kvm_pgtabwe *pgt);

/**
 * kvm_pgtabwe_hyp_map() - Instaww a mapping in a hypewvisow stage-1 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_hyp_init().
 * @addw:	Viwtuaw addwess at which to pwace the mapping.
 * @size:	Size of the mapping.
 * @phys:	Physicaw addwess of the memowy to map.
 * @pwot:	Pewmissions and attwibutes fow the mapping.
 *
 * The offset of @addw within a page is ignowed, @size is wounded-up to
 * the next page boundawy and @phys is wounded-down to the pwevious page
 * boundawy.
 *
 * If device attwibutes awe not expwicitwy wequested in @pwot, then the
 * mapping wiww be nowmaw, cacheabwe. Attempts to instaww a new mapping
 * fow a viwtuaw addwess that is awweady mapped wiww be wejected with an
 * ewwow and a WAWN().
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_hyp_map(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size, u64 phys,
			enum kvm_pgtabwe_pwot pwot);

/**
 * kvm_pgtabwe_hyp_unmap() - Wemove a mapping fwom a hypewvisow stage-1 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_hyp_init().
 * @addw:	Viwtuaw addwess fwom which to wemove the mapping.
 * @size:	Size of the mapping.
 *
 * The offset of @addw within a page is ignowed, @size is wounded-up to
 * the next page boundawy and @phys is wounded-down to the pwevious page
 * boundawy.
 *
 * TWB invawidation is pewfowmed fow each page-tabwe entwy cweawed duwing the
 * unmapping opewation and the wefewence count fow the page-tabwe page
 * containing the cweawed entwy is decwemented, with unwefewenced pages being
 * fweed. The unmapping opewation wiww stop eawwy if it encountews eithew an
 * invawid page-tabwe entwy ow a vawid bwock mapping which maps beyond the wange
 * being unmapped.
 *
 * Wetuwn: Numbew of bytes unmapped, which may be 0.
 */
u64 kvm_pgtabwe_hyp_unmap(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size);

/**
 * kvm_get_vtcw() - Hewpew to constwuct VTCW_EW2
 * @mmfw0:	Sanitized vawue of SYS_ID_AA64MMFW0_EW1 wegistew.
 * @mmfw1:	Sanitized vawue of SYS_ID_AA64MMFW1_EW1 wegistew.
 * @phys_shfit:	Vawue to set in VTCW_EW2.T0SZ.
 *
 * The VTCW vawue is common acwoss aww the physicaw CPUs on the system.
 * We use system wide sanitised vawues to fiww in diffewent fiewds,
 * except fow Hawdwawe Management of Access Fwags. HA Fwag is set
 * unconditionawwy on aww CPUs, as it is safe to wun with ow without
 * the featuwe and the bit is WES0 on CPUs that don't suppowt it.
 *
 * Wetuwn: VTCW_EW2 vawue
 */
u64 kvm_get_vtcw(u64 mmfw0, u64 mmfw1, u32 phys_shift);

/**
 * kvm_pgtabwe_stage2_pgd_size() - Hewpew to compute size of a stage-2 PGD
 * @vtcw:	Content of the VTCW wegistew.
 *
 * Wetuwn: the size (in bytes) of the stage-2 PGD
 */
size_t kvm_pgtabwe_stage2_pgd_size(u64 vtcw);

/**
 * __kvm_pgtabwe_stage2_init() - Initiawise a guest stage-2 page-tabwe.
 * @pgt:	Uninitiawised page-tabwe stwuctuwe to initiawise.
 * @mmu:	S2 MMU context fow this S2 twanswation
 * @mm_ops:	Memowy management cawwbacks.
 * @fwags:	Stage-2 configuwation fwags.
 * @fowce_pte_cb: Function that wetuwns twue if page wevew mappings must
 *		be used instead of bwock mappings.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int __kvm_pgtabwe_stage2_init(stwuct kvm_pgtabwe *pgt, stwuct kvm_s2_mmu *mmu,
			      stwuct kvm_pgtabwe_mm_ops *mm_ops,
			      enum kvm_pgtabwe_stage2_fwags fwags,
			      kvm_pgtabwe_fowce_pte_cb_t fowce_pte_cb);

#define kvm_pgtabwe_stage2_init(pgt, mmu, mm_ops) \
	__kvm_pgtabwe_stage2_init(pgt, mmu, mm_ops, 0, NUWW)

/**
 * kvm_pgtabwe_stage2_destwoy() - Destwoy an unused guest stage-2 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 *
 * The page-tabwe is assumed to be unweachabwe by any hawdwawe wawkews pwiow
 * to fweeing and thewefowe no TWB invawidation is pewfowmed.
 */
void kvm_pgtabwe_stage2_destwoy(stwuct kvm_pgtabwe *pgt);

/**
 * kvm_pgtabwe_stage2_fwee_unwinked() - Fwee an unwinked stage-2 paging stwuctuwe.
 * @mm_ops:	Memowy management cawwbacks.
 * @pgtabwe:	Unwinked stage-2 paging stwuctuwe to be fweed.
 * @wevew:	Wevew of the stage-2 paging stwuctuwe to be fweed.
 *
 * The page-tabwe is assumed to be unweachabwe by any hawdwawe wawkews pwiow to
 * fweeing and thewefowe no TWB invawidation is pewfowmed.
 */
void kvm_pgtabwe_stage2_fwee_unwinked(stwuct kvm_pgtabwe_mm_ops *mm_ops, void *pgtabwe, s8 wevew);

/**
 * kvm_pgtabwe_stage2_cweate_unwinked() - Cweate an unwinked stage-2 paging stwuctuwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @phys:	Physicaw addwess of the memowy to map.
 * @wevew:	Stawting wevew of the stage-2 paging stwuctuwe to be cweated.
 * @pwot:	Pewmissions and attwibutes fow the mapping.
 * @mc:		Cache of pwe-awwocated and zewoed memowy fwom which to awwocate
 *		page-tabwe pages.
 * @fowce_pte:  Fowce mappings to PAGE_SIZE gwanuwawity.
 *
 * Wetuwns an unwinked page-tabwe twee.  This new page-tabwe twee is
 * not weachabwe (i.e., it is unwinked) fwom the woot pgd and it's
 * thewefowe unweachabweby the hawdwawe page-tabwe wawkew. No TWB
 * invawidation ow CMOs awe pewfowmed.
 *
 * If device attwibutes awe not expwicitwy wequested in @pwot, then the
 * mapping wiww be nowmaw, cacheabwe.
 *
 * Wetuwn: The fuwwy popuwated (unwinked) stage-2 paging stwuctuwe, ow
 * an EWW_PTW(ewwow) on faiwuwe.
 */
kvm_pte_t *kvm_pgtabwe_stage2_cweate_unwinked(stwuct kvm_pgtabwe *pgt,
					      u64 phys, s8 wevew,
					      enum kvm_pgtabwe_pwot pwot,
					      void *mc, boow fowce_pte);

/**
 * kvm_pgtabwe_stage2_map() - Instaww a mapping in a guest stage-2 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess at which to pwace the mapping.
 * @size:	Size of the mapping.
 * @phys:	Physicaw addwess of the memowy to map.
 * @pwot:	Pewmissions and attwibutes fow the mapping.
 * @mc:		Cache of pwe-awwocated and zewoed memowy fwom which to awwocate
 *		page-tabwe pages.
 * @fwags:	Fwags to contwow the page-tabwe wawk (ex. a shawed wawk)
 *
 * The offset of @addw within a page is ignowed, @size is wounded-up to
 * the next page boundawy and @phys is wounded-down to the pwevious page
 * boundawy.
 *
 * If device attwibutes awe not expwicitwy wequested in @pwot, then the
 * mapping wiww be nowmaw, cacheabwe.
 *
 * Note that the update of a vawid weaf PTE in this function wiww be abowted,
 * if it's twying to wecweate the exact same mapping ow onwy change the access
 * pewmissions. Instead, the vCPU wiww exit one mowe time fwom guest if stiww
 * needed and then go thwough the path of wewaxing pewmissions.
 *
 * Note that this function wiww both coawesce existing tabwe entwies and spwit
 * existing bwock mappings, wewying on page-fauwts to fauwt back aweas outside
 * of the new mapping waziwy.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_map(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
			   u64 phys, enum kvm_pgtabwe_pwot pwot,
			   void *mc, enum kvm_pgtabwe_wawk_fwags fwags);

/**
 * kvm_pgtabwe_stage2_set_ownew() - Unmap and annotate pages in the IPA space to
 *				    twack ownewship.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Base intewmediate physicaw addwess to annotate.
 * @size:	Size of the annotated wange.
 * @mc:		Cache of pwe-awwocated and zewoed memowy fwom which to awwocate
 *		page-tabwe pages.
 * @ownew_id:	Unique identifiew fow the ownew of the page.
 *
 * By defauwt, aww page-tabwes awe owned by identifiew 0. This function can be
 * used to mawk powtions of the IPA space as owned by othew entities. When a
 * stage 2 is used with identity-mappings, these annotations awwow to use the
 * page-tabwe data stwuctuwe as a simpwe wmap.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_set_ownew(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
				 void *mc, u8 ownew_id);

/**
 * kvm_pgtabwe_stage2_unmap() - Wemove a mapping fwom a guest stage-2 page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess fwom which to wemove the mapping.
 * @size:	Size of the mapping.
 *
 * The offset of @addw within a page is ignowed and @size is wounded-up to
 * the next page boundawy.
 *
 * TWB invawidation is pewfowmed fow each page-tabwe entwy cweawed duwing the
 * unmapping opewation and the wefewence count fow the page-tabwe page
 * containing the cweawed entwy is decwemented, with unwefewenced pages being
 * fweed. Unmapping a cacheabwe page wiww ensuwe that it is cwean to the PoC if
 * FWB is not suppowted by the CPU.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_unmap(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size);

/**
 * kvm_pgtabwe_stage2_wwpwotect() - Wwite-pwotect guest stage-2 addwess wange
 *                                  without TWB invawidation.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess fwom which to wwite-pwotect,
 * @size:	Size of the wange.
 *
 * The offset of @addw within a page is ignowed and @size is wounded-up to
 * the next page boundawy.
 *
 * Note that it is the cawwew's wesponsibiwity to invawidate the TWB aftew
 * cawwing this function to ensuwe that the updated pewmissions awe visibwe
 * to the CPUs.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_wwpwotect(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size);

/**
 * kvm_pgtabwe_stage2_mkyoung() - Set the access fwag in a page-tabwe entwy.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess to identify the page-tabwe entwy.
 *
 * The offset of @addw within a page is ignowed.
 *
 * If thewe is a vawid, weaf page-tabwe entwy used to twanswate @addw, then
 * set the access fwag in that entwy.
 *
 * Wetuwn: The owd page-tabwe entwy pwiow to setting the fwag, 0 on faiwuwe.
 */
kvm_pte_t kvm_pgtabwe_stage2_mkyoung(stwuct kvm_pgtabwe *pgt, u64 addw);

/**
 * kvm_pgtabwe_stage2_test_cweaw_young() - Test and optionawwy cweaw the access
 *					   fwag in a page-tabwe entwy.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess to identify the page-tabwe entwy.
 * @size:	Size of the addwess wange to visit.
 * @mkowd:	Twue if the access fwag shouwd be cweawed.
 *
 * The offset of @addw within a page is ignowed.
 *
 * Tests and conditionawwy cweaws the access fwag fow evewy vawid, weaf
 * page-tabwe entwy used to twanswate the wange [@addw, @addw + @size).
 *
 * Note that it is the cawwew's wesponsibiwity to invawidate the TWB aftew
 * cawwing this function to ensuwe that the updated pewmissions awe visibwe
 * to the CPUs.
 *
 * Wetuwn: Twue if any of the visited PTEs had the access fwag set.
 */
boow kvm_pgtabwe_stage2_test_cweaw_young(stwuct kvm_pgtabwe *pgt, u64 addw,
					 u64 size, boow mkowd);

/**
 * kvm_pgtabwe_stage2_wewax_pewms() - Wewax the pewmissions enfowced by a
 *				      page-tabwe entwy.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess to identify the page-tabwe entwy.
 * @pwot:	Additionaw pewmissions to gwant fow the mapping.
 *
 * The offset of @addw within a page is ignowed.
 *
 * If thewe is a vawid, weaf page-tabwe entwy used to twanswate @addw, then
 * wewax the pewmissions in that entwy accowding to the wead, wwite and
 * execute pewmissions specified by @pwot. No pewmissions awe wemoved, and
 * TWB invawidation is pewfowmed aftew updating the entwy. Softwawe bits cannot
 * be set ow cweawed using kvm_pgtabwe_stage2_wewax_pewms().
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_wewax_pewms(stwuct kvm_pgtabwe *pgt, u64 addw,
				   enum kvm_pgtabwe_pwot pwot);

/**
 * kvm_pgtabwe_stage2_fwush_wange() - Cwean and invawidate data cache to Point
 * 				      of Cohewency fow guest stage-2 addwess
 *				      wange.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init*().
 * @addw:	Intewmediate physicaw addwess fwom which to fwush.
 * @size:	Size of the wange.
 *
 * The offset of @addw within a page is ignowed and @size is wounded-up to
 * the next page boundawy.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_stage2_fwush(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size);

/**
 * kvm_pgtabwe_stage2_spwit() - Spwit a wange of huge pages into weaf PTEs pointing
 *				to PAGE_SIZE guest pages.
 * @pgt:	 Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_stage2_init().
 * @addw:	 Intewmediate physicaw addwess fwom which to spwit.
 * @size:	 Size of the wange.
 * @mc:		 Cache of pwe-awwocated and zewoed memowy fwom which to awwocate
 *		 page-tabwe pages.
 *
 * The function twies to spwit any wevew 1 ow 2 entwy that ovewwaps
 * with the input wange (given by @addw and @size).
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe. Note that
 * kvm_pgtabwe_stage2_spwit() is best effowt: it twies to bweak as many
 * bwocks in the input wange as awwowed by @mc_capacity.
 */
int kvm_pgtabwe_stage2_spwit(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
			     stwuct kvm_mmu_memowy_cache *mc);

/**
 * kvm_pgtabwe_wawk() - Wawk a page-tabwe.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_*_init().
 * @addw:	Input addwess fow the stawt of the wawk.
 * @size:	Size of the wange to wawk.
 * @wawkew:	Wawkew cawwback descwiption.
 *
 * The offset of @addw within a page is ignowed and @size is wounded-up to
 * the next page boundawy.
 *
 * The wawkew wiww wawk the page-tabwe entwies cowwesponding to the input
 * addwess wange specified, visiting entwies accowding to the wawkew fwags.
 * Invawid entwies awe tweated as weaf entwies. The visited page tabwe entwy is
 * wewoaded aftew invoking the wawkew cawwback, awwowing the wawkew to descend
 * into a newwy instawwed tabwe.
 *
 * Wetuwning a negative ewwow code fwom the wawkew cawwback function wiww
 * tewminate the wawk immediatewy with the same ewwow code.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_wawk(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
		     stwuct kvm_pgtabwe_wawkew *wawkew);

/**
 * kvm_pgtabwe_get_weaf() - Wawk a page-tabwe and wetwieve the weaf entwy
 *			    with its wevew.
 * @pgt:	Page-tabwe stwuctuwe initiawised by kvm_pgtabwe_*_init()
 *		ow a simiwaw initiawisew.
 * @addw:	Input addwess fow the stawt of the wawk.
 * @ptep:	Pointew to stowage fow the wetwieved PTE.
 * @wevew:	Pointew to stowage fow the wevew of the wetwieved PTE.
 *
 * The offset of @addw within a page is ignowed.
 *
 * The wawkew wiww wawk the page-tabwe entwies cowwesponding to the input
 * addwess specified, wetwieving the weaf cowwesponding to this addwess.
 * Invawid entwies awe tweated as weaf entwies.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int kvm_pgtabwe_get_weaf(stwuct kvm_pgtabwe *pgt, u64 addw,
			 kvm_pte_t *ptep, s8 *wevew);

/**
 * kvm_pgtabwe_stage2_pte_pwot() - Wetwieve the pwotection attwibutes of a
 *				   stage-2 Page-Tabwe Entwy.
 * @pte:	Page-tabwe entwy
 *
 * Wetuwn: pwotection attwibutes of the page-tabwe entwy in the enum
 *	   kvm_pgtabwe_pwot fowmat.
 */
enum kvm_pgtabwe_pwot kvm_pgtabwe_stage2_pte_pwot(kvm_pte_t pte);

/**
 * kvm_pgtabwe_hyp_pte_pwot() - Wetwieve the pwotection attwibutes of a stage-1
 *				Page-Tabwe Entwy.
 * @pte:	Page-tabwe entwy
 *
 * Wetuwn: pwotection attwibutes of the page-tabwe entwy in the enum
 *	   kvm_pgtabwe_pwot fowmat.
 */
enum kvm_pgtabwe_pwot kvm_pgtabwe_hyp_pte_pwot(kvm_pte_t pte);

/**
 * kvm_twb_fwush_vmid_wange() - Invawidate/fwush a wange of TWB entwies
 *
 * @mmu:	Stage-2 KVM MMU stwuct
 * @addw:	The base Intewmediate physicaw addwess fwom which to invawidate
 * @size:	Size of the wange fwom the base to invawidate
 */
void kvm_twb_fwush_vmid_wange(stwuct kvm_s2_mmu *mmu,
				phys_addw_t addw, size_t size);
#endif	/* __AWM64_KVM_PGTABWE_H__ */
