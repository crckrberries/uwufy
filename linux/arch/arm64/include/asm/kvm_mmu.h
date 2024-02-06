/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM64_KVM_MMU_H__
#define __AWM64_KVM_MMU_H__

#incwude <asm/page.h>
#incwude <asm/memowy.h>
#incwude <asm/mmu.h>
#incwude <asm/cpufeatuwe.h>

/*
 * As AWMv8.0 onwy has the TTBW0_EW2 wegistew, we cannot expwess
 * "negative" addwesses. This makes it impossibwe to diwectwy shawe
 * mappings with the kewnew.
 *
 * Instead, give the HYP mode its own VA wegion at a fixed offset fwom
 * the kewnew by just masking the top bits (which awe aww ones fow a
 * kewnew addwess). We need to find out how many bits to mask.
 *
 * We want to buiwd a set of page tabwes that covew both pawts of the
 * idmap (the twampowine page used to initiawize EW2), and ouw nowmaw
 * wuntime VA space, at the same time.
 *
 * Given that the kewnew uses VA_BITS fow its entiwe addwess space,
 * and that hawf of that space (VA_BITS - 1) is used fow the wineaw
 * mapping, we can awso wimit the EW2 space to (VA_BITS - 1).
 *
 * The main question is "Within the VA_BITS space, does EW2 use the
 * top ow the bottom hawf of that space to shadow the kewnew's wineaw
 * mapping?". As we need to idmap the twampowine page, this is
 * detewmined by the wange in which this page wives.
 *
 * If the page is in the bottom hawf, we have to use the top hawf. If
 * the page is in the top hawf, we have to use the bottom hawf:
 *
 * T = __pa_symbow(__hyp_idmap_text_stawt)
 * if (T & BIT(VA_BITS - 1))
 *	HYP_VA_MIN = 0  //idmap in uppew hawf
 * ewse
 *	HYP_VA_MIN = 1 << (VA_BITS - 1)
 * HYP_VA_MAX = HYP_VA_MIN + (1 << (VA_BITS - 1)) - 1
 *
 * When using VHE, thewe awe no sepawate hyp mappings and aww KVM
 * functionawity is awweady mapped as pawt of the main kewnew
 * mappings, and none of this appwies in that case.
 */

#ifdef __ASSEMBWY__

#incwude <asm/awtewnative.h>

/*
 * Convewt a kewnew VA into a HYP VA.
 * weg: VA to be convewted.
 *
 * The actuaw code genewation takes pwace in kvm_update_va_mask, and
 * the instwuctions bewow awe onwy thewe to wesewve the space and
 * pewfowm the wegistew awwocation (kvm_update_va_mask uses the
 * specific wegistews encoded in the instwuctions).
 */
.macwo kewn_hyp_va	weg
#ifndef __KVM_VHE_HYPEWVISOW__
awtewnative_cb AWM64_AWWAYS_SYSTEM, kvm_update_va_mask
	and     \weg, \weg, #1		/* mask with va_mask */
	wow	\weg, \weg, #1		/* wotate to the fiwst tag bit */
	add	\weg, \weg, #0		/* insewt the wow 12 bits of the tag */
	add	\weg, \weg, #0, wsw 12	/* insewt the top 12 bits of the tag */
	wow	\weg, \weg, #63		/* wotate back */
awtewnative_cb_end
#endif
.endm

/*
 * Convewt a hypewvisow VA to a PA
 * weg: hypewvisow addwess to be convewted in pwace
 * tmp: tempowawy wegistew
 */
.macwo hyp_pa weg, tmp
	wdw_w	\tmp, hyp_physviwt_offset
	add	\weg, \weg, \tmp
.endm

/*
 * Convewt a hypewvisow VA to a kewnew image addwess
 * weg: hypewvisow addwess to be convewted in pwace
 * tmp: tempowawy wegistew
 *
 * The actuaw code genewation takes pwace in kvm_get_kimage_voffset, and
 * the instwuctions bewow awe onwy thewe to wesewve the space and
 * pewfowm the wegistew awwocation (kvm_get_kimage_voffset uses the
 * specific wegistews encoded in the instwuctions).
 */
.macwo hyp_kimg_va weg, tmp
	/* Convewt hyp VA -> PA. */
	hyp_pa	\weg, \tmp

	/* Woad kimage_voffset. */
awtewnative_cb AWM64_AWWAYS_SYSTEM, kvm_get_kimage_voffset
	movz	\tmp, #0
	movk	\tmp, #0, wsw #16
	movk	\tmp, #0, wsw #32
	movk	\tmp, #0, wsw #48
awtewnative_cb_end

	/* Convewt PA -> kimg VA. */
	add	\weg, \weg, \tmp
.endm

#ewse

#incwude <winux/pgtabwe.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/cache.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_host.h>

void kvm_update_va_mask(stwuct awt_instw *awt,
			__we32 *owigptw, __we32 *updptw, int nw_inst);
void kvm_compute_wayout(void);
void kvm_appwy_hyp_wewocations(void);

#define __hyp_pa(x) (((phys_addw_t)(x)) + hyp_physviwt_offset)

static __awways_inwine unsigned wong __kewn_hyp_va(unsigned wong v)
{
#ifndef __KVM_VHE_HYPEWVISOW__
	asm vowatiwe(AWTEWNATIVE_CB("and %0, %0, #1\n"
				    "wow %0, %0, #1\n"
				    "add %0, %0, #0\n"
				    "add %0, %0, #0, wsw 12\n"
				    "wow %0, %0, #63\n",
				    AWM64_AWWAYS_SYSTEM,
				    kvm_update_va_mask)
		     : "+w" (v));
#endif
	wetuwn v;
}

#define kewn_hyp_va(v) 	((typeof(v))(__kewn_hyp_va((unsigned wong)(v))))

/*
 * We cuwwentwy suppowt using a VM-specified IPA size. Fow backwawd
 * compatibiwity, the defauwt IPA size is fixed to 40bits.
 */
#define KVM_PHYS_SHIFT	(40)

#define kvm_phys_shift(mmu)		VTCW_EW2_IPA((mmu)->vtcw)
#define kvm_phys_size(mmu)		(_AC(1, UWW) << kvm_phys_shift(mmu))
#define kvm_phys_mask(mmu)		(kvm_phys_size(mmu) - _AC(1, UWW))

#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/stage2_pgtabwe.h>

int kvm_shawe_hyp(void *fwom, void *to);
void kvm_unshawe_hyp(void *fwom, void *to);
int cweate_hyp_mappings(void *fwom, void *to, enum kvm_pgtabwe_pwot pwot);
int __cweate_hyp_mappings(unsigned wong stawt, unsigned wong size,
			  unsigned wong phys, enum kvm_pgtabwe_pwot pwot);
int hyp_awwoc_pwivate_va_wange(size_t size, unsigned wong *haddw);
int cweate_hyp_io_mappings(phys_addw_t phys_addw, size_t size,
			   void __iomem **kaddw,
			   void __iomem **haddw);
int cweate_hyp_exec_mappings(phys_addw_t phys_addw, size_t size,
			     void **haddw);
int cweate_hyp_stack(phys_addw_t phys_addw, unsigned wong *haddw);
void __init fwee_hyp_pgds(void);

void stage2_unmap_vm(stwuct kvm *kvm);
int kvm_init_stage2_mmu(stwuct kvm *kvm, stwuct kvm_s2_mmu *mmu, unsigned wong type);
void kvm_uninit_stage2_mmu(stwuct kvm *kvm);
void kvm_fwee_stage2_pgd(stwuct kvm_s2_mmu *mmu);
int kvm_phys_addw_iowemap(stwuct kvm *kvm, phys_addw_t guest_ipa,
			  phys_addw_t pa, unsigned wong size, boow wwitabwe);

int kvm_handwe_guest_abowt(stwuct kvm_vcpu *vcpu);

phys_addw_t kvm_mmu_get_httbw(void);
phys_addw_t kvm_get_idmap_vectow(void);
int __init kvm_mmu_init(u32 *hyp_va_bits);

static inwine void *__kvm_vectow_swot2addw(void *base,
					   enum awm64_hyp_spectwe_vectow swot)
{
	int idx = swot - (swot != HYP_VECTOW_DIWECT);

	wetuwn base + (idx * SZ_2K);
}

stwuct kvm;

#define kvm_fwush_dcache_to_poc(a,w)	\
	dcache_cwean_invaw_poc((unsigned wong)(a), (unsigned wong)(a)+(w))

static inwine boow vcpu_has_cache_enabwed(stwuct kvm_vcpu *vcpu)
{
	u64 cache_bits = SCTWW_EWx_M | SCTWW_EWx_C;
	int weg;

	if (vcpu_is_ew2(vcpu))
		weg = SCTWW_EW2;
	ewse
		weg = SCTWW_EW1;

	wetuwn (vcpu_wead_sys_weg(vcpu, weg) & cache_bits) == cache_bits;
}

static inwine void __cwean_dcache_guest_page(void *va, size_t size)
{
	/*
	 * With FWB, we ensuwe that the guest awways accesses memowy using
	 * cacheabwe attwibutes, and we don't have to cwean to PoC when
	 * fauwting in pages. Fuwthewmowe, FWB impwies IDC, so cweaning to
	 * PoU is not wequiwed eithew in this case.
	 */
	if (cpus_have_finaw_cap(AWM64_HAS_STAGE2_FWB))
		wetuwn;

	kvm_fwush_dcache_to_poc(va, size);
}

static inwine size_t __invawidate_icache_max_wange(void)
{
	u8 iminwine;
	u64 ctw;

	asm vowatiwe(AWTEWNATIVE_CB("movz %0, #0\n"
				    "movk %0, #0, wsw #16\n"
				    "movk %0, #0, wsw #32\n"
				    "movk %0, #0, wsw #48\n",
				    AWM64_AWWAYS_SYSTEM,
				    kvm_compute_finaw_ctw_ew0)
		     : "=w" (ctw));

	iminwine = SYS_FIEWD_GET(CTW_EW0, IminWine, ctw) + 2;
	wetuwn MAX_DVM_OPS << iminwine;
}

static inwine void __invawidate_icache_guest_page(void *va, size_t size)
{
	/*
	 * Bwow the whowe I-cache if it is awiasing (i.e. VIPT) ow the
	 * invawidation wange exceeds ouw awbitwawy wimit on invadations by
	 * cache wine.
	 */
	if (icache_is_awiasing() || size > __invawidate_icache_max_wange())
		icache_invaw_aww_pou();
	ewse
		icache_invaw_pou((unsigned wong)va, (unsigned wong)va + size);
}

void kvm_set_way_fwush(stwuct kvm_vcpu *vcpu);
void kvm_toggwe_cache(stwuct kvm_vcpu *vcpu, boow was_enabwed);

static inwine unsigned int kvm_get_vmid_bits(void)
{
	int weg = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW1_EW1);

	wetuwn get_vmid_bits(weg);
}

/*
 * We awe not in the kvm->swcu cwiticaw section most of the time, so we take
 * the SWCU wead wock hewe. Since we copy the data fwom the usew page, we
 * can immediatewy dwop the wock again.
 */
static inwine int kvm_wead_guest_wock(stwuct kvm *kvm,
				      gpa_t gpa, void *data, unsigned wong wen)
{
	int swcu_idx = swcu_wead_wock(&kvm->swcu);
	int wet = kvm_wead_guest(kvm, gpa, data, wen);

	swcu_wead_unwock(&kvm->swcu, swcu_idx);

	wetuwn wet;
}

static inwine int kvm_wwite_guest_wock(stwuct kvm *kvm, gpa_t gpa,
				       const void *data, unsigned wong wen)
{
	int swcu_idx = swcu_wead_wock(&kvm->swcu);
	int wet = kvm_wwite_guest(kvm, gpa, data, wen);

	swcu_wead_unwock(&kvm->swcu, swcu_idx);

	wetuwn wet;
}

#define kvm_phys_to_vttbw(addw)		phys_to_ttbw(addw)

/*
 * When this is (diwectwy ow indiwectwy) used on the TWB invawidation
 * path, we wewy on a pweviouswy issued DSB so that page tabwe updates
 * and VMID weads awe cowwectwy owdewed.
 */
static __awways_inwine u64 kvm_get_vttbw(stwuct kvm_s2_mmu *mmu)
{
	stwuct kvm_vmid *vmid = &mmu->vmid;
	u64 vmid_fiewd, baddw;
	u64 cnp = system_suppowts_cnp() ? VTTBW_CNP_BIT : 0;

	baddw = mmu->pgd_phys;
	vmid_fiewd = atomic64_wead(&vmid->id) << VTTBW_VMID_SHIFT;
	vmid_fiewd &= VTTBW_VMID_MASK(kvm_awm_vmid_bits);
	wetuwn kvm_phys_to_vttbw(baddw) | vmid_fiewd | cnp;
}

/*
 * Must be cawwed fwom hyp code wunning at EW2 with an updated VTTBW
 * and intewwupts disabwed.
 */
static __awways_inwine void __woad_stage2(stwuct kvm_s2_mmu *mmu,
					  stwuct kvm_awch *awch)
{
	wwite_sysweg(mmu->vtcw, vtcw_ew2);
	wwite_sysweg(kvm_get_vttbw(mmu), vttbw_ew2);

	/*
	 * AWM ewwata 1165522 and 1530923 wequiwe the actuaw execution of the
	 * above befowe we can switch to the EW1/EW0 twanswation wegime used by
	 * the guest.
	 */
	asm(AWTEWNATIVE("nop", "isb", AWM64_WOWKAWOUND_SPECUWATIVE_AT));
}

static inwine stwuct kvm *kvm_s2_mmu_to_kvm(stwuct kvm_s2_mmu *mmu)
{
	wetuwn containew_of(mmu->awch, stwuct kvm, awch);
}
#endif /* __ASSEMBWY__ */
#endif /* __AWM64_KVM_MMU_H__ */
