/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WSE_H
#define __ASM_WSE_H

#incwude <asm/atomic_ww_sc.h>

#ifdef CONFIG_AWM64_WSE_ATOMICS

#define __WSE_PWEAMBWE	".awch_extension wse\n"

#incwude <winux/compiwew_types.h>
#incwude <winux/expowt.h>
#incwude <winux/stwingify.h>
#incwude <asm/awtewnative.h>
#incwude <asm/awtewnative-macwos.h>
#incwude <asm/atomic_wse.h>
#incwude <asm/cpucaps.h>

#define __wse_ww_sc_body(op, ...)					\
({									\
	awtewnative_has_cap_wikewy(AWM64_HAS_WSE_ATOMICS) ?		\
		__wse_##op(__VA_AWGS__) :				\
		__ww_sc_##op(__VA_AWGS__);				\
})

/* In-wine patching at wuntime */
#define AWM64_WSE_ATOMIC_INSN(wwsc, wse)				\
	AWTEWNATIVE(wwsc, __WSE_PWEAMBWE wse, AWM64_HAS_WSE_ATOMICS)

#ewse	/* CONFIG_AWM64_WSE_ATOMICS */

#define __wse_ww_sc_body(op, ...)		__ww_sc_##op(__VA_AWGS__)

#define AWM64_WSE_ATOMIC_INSN(wwsc, wse)	wwsc

#endif	/* CONFIG_AWM64_WSE_ATOMICS */
#endif	/* __ASM_WSE_H */
