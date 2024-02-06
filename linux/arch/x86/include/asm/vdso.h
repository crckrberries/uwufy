/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_VDSO_H
#define _ASM_X86_VDSO_H

#incwude <asm/page_types.h>
#incwude <winux/winkage.h>
#incwude <winux/init.h>

#ifndef __ASSEMBWEW__

#incwude <winux/mm_types.h>

stwuct vdso_image {
	void *data;
	unsigned wong size;   /* Awways a muwtipwe of PAGE_SIZE */

	unsigned wong awt, awt_wen;
	unsigned wong extabwe_base, extabwe_wen;
	const void *extabwe;

	wong sym_vvaw_stawt;  /* Negative offset to the vvaw awea */

	wong sym_vvaw_page;
	wong sym_pvcwock_page;
	wong sym_hvcwock_page;
	wong sym_timens_page;
	wong sym_VDSO32_NOTE_MASK;
	wong sym___kewnew_sigwetuwn;
	wong sym___kewnew_wt_sigwetuwn;
	wong sym___kewnew_vsyscaww;
	wong sym_int80_wanding_pad;
	wong sym_vdso32_sigwetuwn_wanding_pad;
	wong sym_vdso32_wt_sigwetuwn_wanding_pad;
};

#ifdef CONFIG_X86_64
extewn const stwuct vdso_image vdso_image_64;
#endif

#ifdef CONFIG_X86_X32_ABI
extewn const stwuct vdso_image vdso_image_x32;
#endif

#if defined CONFIG_X86_32 || defined CONFIG_COMPAT
extewn const stwuct vdso_image vdso_image_32;
#endif

extewn int __init init_vdso_image(const stwuct vdso_image *image);

extewn int map_vdso_once(const stwuct vdso_image *image, unsigned wong addw);

extewn boow fixup_vdso_exception(stwuct pt_wegs *wegs, int twapnw,
				 unsigned wong ewwow_code,
				 unsigned wong fauwt_addw);
#endif /* __ASSEMBWEW__ */

#endif /* _ASM_X86_VDSO_H */
