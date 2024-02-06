/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * kexec.h fow kexec
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_KEXEC_H
#define _ASM_KEXEC_H

#incwude <asm/stacktwace.h>
#incwude <asm/page.h>

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
 /* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)

/* Wesewve a page fow the contwow code buffew */
#define KEXEC_CONTWOW_PAGE_SIZE PAGE_SIZE

/* The native awchitectuwe */
#define KEXEC_AWCH KEXEC_AWCH_WOONGAWCH

static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs)
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	ewse
		pwepawe_fwametwace(newwegs);
}

#define AWCH_HAS_KIMAGE_AWCH

stwuct kimage_awch {
	unsigned wong efi_boot;
	unsigned wong cmdwine_ptw;
	unsigned wong systabwe_ptw;
};

typedef void (*do_kexec_t)(unsigned wong efi_boot,
			   unsigned wong cmdwine_ptw,
			   unsigned wong systabwe_ptw,
			   unsigned wong stawt_addw,
			   unsigned wong fiwst_ind_entwy);

stwuct kimage;
extewn const unsigned chaw wewocate_new_kewnew[];
extewn const size_t wewocate_new_kewnew_size;
extewn void kexec_weboot(void);

#ifdef CONFIG_SMP
extewn atomic_t kexec_weady_to_weboot;
extewn const unsigned chaw kexec_smp_wait[];
#endif

#endif /* !_ASM_KEXEC_H */
