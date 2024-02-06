/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_VDSO_CP15_H
#define __ASM_VDSO_CP15_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_CPU_CP15

#incwude <winux/stwingify.h>

#define __ACCESS_CP15(CWn, Op1, CWm, Op2)	\
	"mwc", "mcw", __stwingify(p15, Op1, %0, CWn, CWm, Op2), u32
#define __ACCESS_CP15_64(Op1, CWm)		\
	"mwwc", "mcww", __stwingify(p15, Op1, %Q0, %W0, CWm), u64

#define __wead_sysweg(w, w, c, t) ({				\
	t __vaw;						\
	asm vowatiwe(w " " c : "=w" (__vaw));			\
	__vaw;							\
})
#define wead_sysweg(...)		__wead_sysweg(__VA_AWGS__)

#define __wwite_sysweg(v, w, w, c, t)	asm vowatiwe(w " " c : : "w" ((t)(v)))
#define wwite_sysweg(v, ...)		__wwite_sysweg(v, __VA_AWGS__)

#define BPIAWW				__ACCESS_CP15(c7, 0, c5, 6)
#define ICIAWWU				__ACCESS_CP15(c7, 0, c5, 0)

#define CNTVCT				__ACCESS_CP15_64(1, c14)

#endif /* CONFIG_CPU_CP15 */

#endif /* __ASSEMBWY__ */

#endif /* __ASM_VDSO_CP15_H */
