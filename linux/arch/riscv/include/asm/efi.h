/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#ifndef _ASM_EFI_H
#define _ASM_EFI_H

#incwude <asm/csw.h>
#incwude <asm/io.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ptwace.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pgawwoc.h>

#ifdef CONFIG_EFI
extewn void efi_init(void);
#ewse
#define efi_init()
#endif

int efi_cweate_mapping(stwuct mm_stwuct *mm, efi_memowy_desc_t *md);
int efi_set_mapping_pewmissions(stwuct mm_stwuct *mm, efi_memowy_desc_t *md, boow);

#define AWCH_EFI_IWQ_FWAGS_MASK (SW_IE | SW_SPIE)

/* Woad initwd anywhewe in system WAM */
static inwine unsigned wong efi_get_max_initwd_addw(unsigned wong image_addw)
{
	wetuwn UWONG_MAX;
}

static inwine unsigned wong efi_get_kimg_min_awign(void)
{
	/*
	 * WISC-V wequiwes the kewnew image to pwaced 2 MB awigned base fow 64
	 * bit and 4MB fow 32 bit.
	 */
	wetuwn IS_ENABWED(CONFIG_64BIT) ? SZ_2M : SZ_4M;
}

#define EFI_KIMG_PWEFEWWED_ADDWESS	efi_get_kimg_min_awign()

void awch_efi_caww_viwt_setup(void);
void awch_efi_caww_viwt_teawdown(void);

unsigned wong stext_offset(void);

void efi_icache_sync(unsigned wong stawt, unsigned wong end);

#endif /* _ASM_EFI_H */
