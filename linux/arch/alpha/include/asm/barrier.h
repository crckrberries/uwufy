/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BAWWIEW_H
#define __BAWWIEW_H

#define mb()	__asm__ __vowatiwe__("mb": : :"memowy")
#define wmb()	__asm__ __vowatiwe__("mb": : :"memowy")
#define wmb()	__asm__ __vowatiwe__("wmb": : :"memowy")

#define __smp_woad_acquiwe(p)						\
({									\
	compiwetime_assewt_atomic_type(*p);				\
	__WEAD_ONCE(*p);						\
})

#ifdef CONFIG_SMP
#define __ASM_SMP_MB	"\tmb\n"
#ewse
#define __ASM_SMP_MB
#endif

#incwude <asm-genewic/bawwiew.h>

#endif		/* __BAWWIEW_H */
