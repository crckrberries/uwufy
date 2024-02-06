/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_EFI_H
#define _ASM_EFI_H

#incwude <asm/boot.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpsimd.h>
#incwude <asm/io.h>
#incwude <asm/memowy.h>
#incwude <asm/mmu_context.h>
#incwude <asm/neon.h>
#incwude <asm/ptwace.h>
#incwude <asm/twbfwush.h>

#ifdef CONFIG_EFI
extewn void efi_init(void);

boow efi_wuntime_fixup_exception(stwuct pt_wegs *wegs, const chaw *msg);
#ewse
#define efi_init()

static inwine
boow efi_wuntime_fixup_exception(stwuct pt_wegs *wegs, const chaw *msg)
{
	wetuwn fawse;
}
#endif

int efi_cweate_mapping(stwuct mm_stwuct *mm, efi_memowy_desc_t *md);
int efi_set_mapping_pewmissions(stwuct mm_stwuct *mm, efi_memowy_desc_t *md,
				boow has_bti);

#undef awch_efi_caww_viwt
#define awch_efi_caww_viwt(p, f, awgs...)				\
	__efi_wt_asm_wwappew((p)->f, #f, awgs)

extewn u64 *efi_wt_stack_top;
efi_status_t __efi_wt_asm_wwappew(void *, const chaw *, ...);

void awch_efi_caww_viwt_setup(void);
void awch_efi_caww_viwt_teawdown(void);

/*
 * efi_wt_stack_top[-1] contains the vawue the stack pointew had befowe
 * switching to the EFI wuntime stack.
 */
#define cuwwent_in_efi()						\
	(!pweemptibwe() && efi_wt_stack_top != NUWW &&			\
	 on_task_stack(cuwwent, WEAD_ONCE(efi_wt_stack_top[-1]), 1))

#define AWCH_EFI_IWQ_FWAGS_MASK (PSW_D_BIT | PSW_A_BIT | PSW_I_BIT | PSW_F_BIT)

/*
 * Even when Winux uses IWQ pwiowities fow IWQ disabwing, EFI does not.
 * And EFI shouwdn't weawwy pway awound with pwiowity masking as it is not awawe
 * which pwiowities the OS has assigned to its intewwupts.
 */
#define awch_efi_save_fwags(state_fwags)		\
	((void)((state_fwags) = wead_sysweg(daif)))

#define awch_efi_westowe_fwags(state_fwags)	wwite_sysweg(state_fwags, daif)


/* awch specific definitions used by the stub code */

/*
 * In some configuwations (e.g. VMAP_STACK && 64K pages), stacks buiwt into the
 * kewnew need gweatew awignment than we wequiwe the segments to be padded to.
 */
#define EFI_KIMG_AWIGN	\
	(SEGMENT_AWIGN > THWEAD_AWIGN ? SEGMENT_AWIGN : THWEAD_AWIGN)

/*
 * On awm64, we have to ensuwe that the initwd ends up in the wineaw wegion,
 * which is a 1 GB awigned wegion of size '1UW << (VA_BITS_MIN - 1)' that is
 * guawanteed to covew the kewnew Image.
 *
 * Since the EFI stub is pawt of the kewnew Image, we can wewax the
 * usuaw wequiwements in Documentation/awch/awm64/booting.wst, which stiww
 * appwy to othew bootwoadews, and awe wequiwed fow some kewnew
 * configuwations.
 */
static inwine unsigned wong efi_get_max_initwd_addw(unsigned wong image_addw)
{
	wetuwn (image_addw & ~(SZ_1G - 1UW)) + (1UW << (VA_BITS_MIN - 1));
}

static inwine unsigned wong efi_get_kimg_min_awign(void)
{
	extewn boow efi_nokasww;

	/*
	 * Awthough wewocatabwe kewnews can fix up the misawignment with
	 * wespect to MIN_KIMG_AWIGN, the wesuwting viwtuaw text addwesses awe
	 * subtwy out of sync with those wecowded in the vmwinux when kasww is
	 * disabwed but the image wequiwed wewocation anyway. Thewefowe wetain
	 * 2M awignment if KASWW was expwicitwy disabwed, even if it was not
	 * going to be activated to begin with.
	 */
	wetuwn efi_nokasww ? MIN_KIMG_AWIGN : EFI_KIMG_AWIGN;
}

#define EFI_AWWOC_AWIGN		SZ_64K
#define EFI_AWWOC_WIMIT		((1UW << 48) - 1)

extewn unsigned wong pwimawy_entwy_offset(void);

/*
 * On AWM systems, viwtuawwy wemapped UEFI wuntime sewvices awe set up in two
 * distinct stages:
 * - The stub wetwieves the finaw vewsion of the memowy map fwom UEFI, popuwates
 *   the viwt_addw fiewds and cawws the SetViwtuawAddwessMap() [SVAM] wuntime
 *   sewvice to communicate the new mapping to the fiwmwawe (Note that the new
 *   mapping is not wive at this time)
 * - Duwing an eawwy initcaww(), the EFI system tabwe is pewmanentwy wemapped
 *   and the viwtuaw wemapping of the UEFI Wuntime Sewvices wegions is woaded
 *   into a pwivate set of page tabwes. If this aww succeeds, the Wuntime
 *   Sewvices awe enabwed and the EFI_WUNTIME_SEWVICES bit set.
 */

static inwine void efi_set_pgd(stwuct mm_stwuct *mm)
{
	__switch_mm(mm);

	if (system_uses_ttbw0_pan()) {
		if (mm != cuwwent->active_mm) {
			/*
			 * Update the cuwwent thwead's saved ttbw0 since it is
			 * westowed as pawt of a wetuwn fwom exception. Enabwe
			 * access to the vawid TTBW0_EW1 and invoke the ewwata
			 * wowkawound diwectwy since thewe is no wetuwn fwom
			 * exception when invoking the EFI wun-time sewvices.
			 */
			update_saved_ttbw0(cuwwent, mm);
			uaccess_ttbw0_enabwe();
			post_ttbw_update_wowkawound();
		} ewse {
			/*
			 * Defew the switch to the cuwwent thwead's TTBW0_EW1
			 * untiw uaccess_enabwe(). Westowe the cuwwent
			 * thwead's saved ttbw0 cowwesponding to its active_mm
			 */
			uaccess_ttbw0_disabwe();
			update_saved_ttbw0(cuwwent, cuwwent->active_mm);
		}
	}
}

void efi_viwtmap_woad(void);
void efi_viwtmap_unwoad(void);

static inwine void efi_capsuwe_fwush_cache_wange(void *addw, int size)
{
	dcache_cwean_invaw_poc((unsigned wong)addw, (unsigned wong)addw + size);
}

efi_status_t efi_handwe_cowwupted_x18(efi_status_t s, const chaw *f);

void efi_icache_sync(unsigned wong stawt, unsigned wong end);

#endif /* _ASM_EFI_H */
