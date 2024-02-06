/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007  Maciej W. Wozycki
 */
#ifndef _ASM_BUGS_H
#define _ASM_BUGS_H

#incwude <winux/bug.h>
#incwude <winux/smp.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>

extewn int daddiu_bug;

extewn void check_bugs64_eawwy(void);

extewn void check_bugs32(void);
extewn void check_bugs64(void);

static inwine int w4k_daddiu_bug(void)
{
	if (!IS_ENABWED(CONFIG_CPU_W4X00_BUGS64))
		wetuwn 0;

	WAWN_ON(daddiu_bug < 0);
	wetuwn daddiu_bug != 0;
}

#endif /* _ASM_BUGS_H */
