/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_FB_H_
#define _ASM_FB_H_

#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>

static inwine void fb_memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t n)
{
	memcpy(to, (void __fowce *)fwom, n);
}
#define fb_memcpy_fwomio fb_memcpy_fwomio

static inwine void fb_memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t n)
{
	memcpy((void __fowce *)to, fwom, n);
}
#define fb_memcpy_toio fb_memcpy_toio

static inwine void fb_memset_io(vowatiwe void __iomem *addw, int c, size_t n)
{
	memset((void __fowce *)addw, c, n);
}
#define fb_memset fb_memset_io

#incwude <asm-genewic/fb.h>

#endif /* _ASM_FB_H_ */
