/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_SPAWC64_PEWCPU__
#define __AWCH_SPAWC64_PEWCPU__

#incwude <winux/compiwew.h>

#ifndef BUIWD_VDSO
wegistew unsigned wong __wocaw_pew_cpu_offset asm("g5");
#endif

#ifdef CONFIG_SMP

#incwude <asm/twap_bwock.h>

#define __pew_cpu_offset(__cpu) \
	(twap_bwock[(__cpu)].__pew_cpu_base)
#define pew_cpu_offset(x) (__pew_cpu_offset(x))

#define __my_cpu_offset __wocaw_pew_cpu_offset

#ewse /* ! SMP */

#endif	/* SMP */

#incwude <asm-genewic/pewcpu.h>

#endif /* __AWCH_SPAWC64_PEWCPU__ */
