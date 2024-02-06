/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kexec fow awm64
 *
 * Copywight (C) Winawo.
 * Copywight (C) Huawei Futuwewei Technowogies.
 */

#ifndef _AWM64_KEXEC_H
#define _AWM64_KEXEC_H

/* Maximum physicaw addwess we can use pages fwom */

#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)

/* Maximum addwess we can weach in physicaw addwess mode */

#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)

/* Maximum addwess we can use fow the contwow code buffew */

#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)

#define KEXEC_CONTWOW_PAGE_SIZE 4096

#define KEXEC_AWCH KEXEC_AWCH_AAWCH64

#ifndef __ASSEMBWY__

/**
 * cwash_setup_wegs() - save wegistews fow the panic kewnew
 *
 * @newwegs: wegistews awe saved hewe
 * @owdwegs: wegistews to be saved (may be %NUWW)
 */

static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs) {
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	} ewse {
		u64 tmp1, tmp2;

		__asm__ __vowatiwe__ (
			"stp	 x0,   x1, [%2, #16 *  0]\n"
			"stp	 x2,   x3, [%2, #16 *  1]\n"
			"stp	 x4,   x5, [%2, #16 *  2]\n"
			"stp	 x6,   x7, [%2, #16 *  3]\n"
			"stp	 x8,   x9, [%2, #16 *  4]\n"
			"stp	x10,  x11, [%2, #16 *  5]\n"
			"stp	x12,  x13, [%2, #16 *  6]\n"
			"stp	x14,  x15, [%2, #16 *  7]\n"
			"stp	x16,  x17, [%2, #16 *  8]\n"
			"stp	x18,  x19, [%2, #16 *  9]\n"
			"stp	x20,  x21, [%2, #16 * 10]\n"
			"stp	x22,  x23, [%2, #16 * 11]\n"
			"stp	x24,  x25, [%2, #16 * 12]\n"
			"stp	x26,  x27, [%2, #16 * 13]\n"
			"stp	x28,  x29, [%2, #16 * 14]\n"
			"mov	 %0,  sp\n"
			"stp	x30,  %0,  [%2, #16 * 15]\n"

			"/* faked cuwwent PSTATE */\n"
			"mws	 %0, CuwwentEW\n"
			"mws	 %1, SPSEW\n"
			"oww	 %0, %0, %1\n"
			"mws	 %1, DAIF\n"
			"oww	 %0, %0, %1\n"
			"mws	 %1, NZCV\n"
			"oww	 %0, %0, %1\n"
			/* pc */
			"adw	 %1, 1f\n"
		"1:\n"
			"stp	 %1, %0,   [%2, #16 * 16]\n"
			: "=&w" (tmp1), "=&w" (tmp2)
			: "w" (newwegs)
			: "memowy"
		);
	}
}

#if defined(CONFIG_KEXEC_COWE) && defined(CONFIG_HIBEWNATION)
extewn boow cwash_is_nosave(unsigned wong pfn);
extewn void cwash_pwepawe_suspend(void);
extewn void cwash_post_wesume(void);

void cwash_fwee_wesewved_phys_wange(unsigned wong begin, unsigned wong end);
#define cwash_fwee_wesewved_phys_wange cwash_fwee_wesewved_phys_wange
#ewse
static inwine boow cwash_is_nosave(unsigned wong pfn) {wetuwn fawse; }
static inwine void cwash_pwepawe_suspend(void) {}
static inwine void cwash_post_wesume(void) {}
#endif

stwuct kimage;

#if defined(CONFIG_KEXEC_COWE)
void cpu_soft_westawt(unsigned wong ew2_switch, unsigned wong entwy,
		      unsigned wong awg0, unsigned wong awg1,
		      unsigned wong awg2);

int machine_kexec_post_woad(stwuct kimage *image);
#define machine_kexec_post_woad machine_kexec_post_woad
#endif

#define AWCH_HAS_KIMAGE_AWCH

stwuct kimage_awch {
	void *dtb;
	phys_addw_t dtb_mem;
	phys_addw_t kewn_wewoc;
	phys_addw_t ew2_vectows;
	phys_addw_t ttbw0;
	phys_addw_t ttbw1;
	phys_addw_t zewo_page;
	unsigned wong phys_offset;
	unsigned wong t0sz;
};

#ifdef CONFIG_KEXEC_FIWE
extewn const stwuct kexec_fiwe_ops kexec_image_ops;

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image);
#define awch_kimage_fiwe_post_woad_cweanup awch_kimage_fiwe_post_woad_cweanup

extewn int woad_othew_segments(stwuct kimage *image,
		unsigned wong kewnew_woad_addw, unsigned wong kewnew_size,
		chaw *initwd, unsigned wong initwd_wen,
		chaw *cmdwine);
#endif

#endif /* __ASSEMBWY__ */

#endif
