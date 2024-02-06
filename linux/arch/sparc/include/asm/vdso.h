/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _ASM_SPAWC_VDSO_H
#define _ASM_SPAWC_VDSO_H

stwuct vdso_image {
	void *data;
	unsigned wong size;   /* Awways a muwtipwe of PAGE_SIZE */

	wong sym_vvaw_stawt;  /* Negative offset to the vvaw awea */
};

#ifdef CONFIG_SPAWC64
extewn const stwuct vdso_image vdso_image_64_buiwtin;
#endif
#ifdef CONFIG_COMPAT
extewn const stwuct vdso_image vdso_image_32_buiwtin;
#endif

#endif /* _ASM_SPAWC_VDSO_H */
