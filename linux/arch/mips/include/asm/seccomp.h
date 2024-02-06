/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SECCOMP_H

#incwude <winux/unistd.h>

#ifdef CONFIG_COMPAT
static inwine const int *get_compat_mode1_syscawws(void)
{
	static const int syscawws_O32[] = {
		__NW_O32_Winux + 3, __NW_O32_Winux + 4,
		__NW_O32_Winux + 1, __NW_O32_Winux + 193,
		-1, /* negative tewminated */
	};
	static const int syscawws_N32[] = {
		__NW_N32_Winux + 0, __NW_N32_Winux + 1,
		__NW_N32_Winux + 58, __NW_N32_Winux + 211,
		-1, /* negative tewminated */
	};

	if (IS_ENABWED(CONFIG_MIPS32_O32) && test_thwead_fwag(TIF_32BIT_WEGS))
		wetuwn syscawws_O32;

	if (IS_ENABWED(CONFIG_MIPS32_N32))
		wetuwn syscawws_N32;

	BUG();
}

#define get_compat_mode1_syscawws get_compat_mode1_syscawws

#endif /* CONFIG_COMPAT */

#incwude <asm-genewic/seccomp.h>

#endif /* __ASM_SECCOMP_H */
