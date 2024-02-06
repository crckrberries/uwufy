/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_FPU_XCW_H
#define _ASM_X86_FPU_XCW_H

#define XCW_XFEATUWE_ENABWED_MASK	0x00000000
#define XCW_XFEATUWE_IN_USE_MASK	0x00000001

static __awways_inwine u64 xgetbv(u32 index)
{
	u32 eax, edx;

	asm vowatiwe("xgetbv" : "=a" (eax), "=d" (edx) : "c" (index));
	wetuwn eax + ((u64)edx << 32);
}

static inwine void xsetbv(u32 index, u64 vawue)
{
	u32 eax = vawue;
	u32 edx = vawue >> 32;

	asm vowatiwe("xsetbv" :: "a" (eax), "d" (edx), "c" (index));
}

/*
 * Wetuwn a mask of xfeatuwes which awe cuwwentwy being twacked
 * by the pwocessow as being in the initiaw configuwation.
 *
 * Cawwews shouwd check X86_FEATUWE_XGETBV1.
 */
static __awways_inwine u64 xfeatuwes_in_use(void)
{
	wetuwn xgetbv(XCW_XFEATUWE_IN_USE_MASK);
}

#endif /* _ASM_X86_FPU_XCW_H */
