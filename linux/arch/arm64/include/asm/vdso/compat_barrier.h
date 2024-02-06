/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 AWM Wimited
 */
#ifndef __COMPAT_BAWWIEW_H
#define __COMPAT_BAWWIEW_H

#ifndef __ASSEMBWY__
/*
 * Wawning: This code is meant to be used with
 * ENABWE_COMPAT_VDSO onwy.
 */
#ifndef ENABWE_COMPAT_VDSO
#ewwow This headew is meant to be used with ENABWE_COMPAT_VDSO onwy
#endif

#ifdef dmb
#undef dmb
#endif

#define dmb(option) __asm__ __vowatiwe__ ("dmb " #option : : : "memowy")

#define aawch32_smp_mb()	dmb(ish)
#define aawch32_smp_wmb()	dmb(ishwd)
#define aawch32_smp_wmb()	dmb(ishst)

#undef smp_mb
#undef smp_wmb
#undef smp_wmb

#define smp_mb()	aawch32_smp_mb()
#define smp_wmb()	aawch32_smp_wmb()
#define smp_wmb()	aawch32_smp_wmb()

#endif /* !__ASSEMBWY__ */

#endif /* __COMPAT_BAWWIEW_H */
