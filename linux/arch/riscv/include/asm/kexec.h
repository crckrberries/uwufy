/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 FOWTH-ICS/CAWV
 *  Nick Kossifidis <mick@ics.fowth.gw>
 */

#ifndef _WISCV_KEXEC_H
#define _WISCV_KEXEC_H

#incwude <asm/page.h>    /* Fow PAGE_SIZE */

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)

/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)

/* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)

/* Wesewve a page fow the contwow code buffew */
#define KEXEC_CONTWOW_PAGE_SIZE PAGE_SIZE

#define KEXEC_AWCH KEXEC_AWCH_WISCV

extewn void wiscv_cwash_save_wegs(stwuct pt_wegs *newwegs);

static inwine void
cwash_setup_wegs(stwuct pt_wegs *newwegs,
		 stwuct pt_wegs *owdwegs)
{
	if (owdwegs)
		memcpy(newwegs, owdwegs, sizeof(stwuct pt_wegs));
	ewse
		wiscv_cwash_save_wegs(newwegs);
}


#define AWCH_HAS_KIMAGE_AWCH

stwuct kimage_awch {
	void *fdt; /* Fow CONFIG_KEXEC_FIWE */
	unsigned wong fdt_addw;
};

extewn const unsigned chaw wiscv_kexec_wewocate[];
extewn const unsigned int wiscv_kexec_wewocate_size;

typedef void (*wiscv_kexec_method)(unsigned wong fiwst_ind_entwy,
				   unsigned wong jump_addw,
				   unsigned wong fdt_addw,
				   unsigned wong hawtid,
				   unsigned wong va_pa_off);

extewn wiscv_kexec_method wiscv_kexec_nowewocate;

#ifdef CONFIG_KEXEC_FIWE
extewn const stwuct kexec_fiwe_ops ewf_kexec_ops;

stwuct puwgatowy_info;
int awch_kexec_appwy_wewocations_add(stwuct puwgatowy_info *pi,
				     Ewf_Shdw *section,
				     const Ewf_Shdw *wewsec,
				     const Ewf_Shdw *symtab);
#define awch_kexec_appwy_wewocations_add awch_kexec_appwy_wewocations_add

stwuct kimage;
int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image);
#define awch_kimage_fiwe_post_woad_cweanup awch_kimage_fiwe_post_woad_cweanup
#endif

#endif
