/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_X86_BAWWIEW_H
#define _TOOWS_WINUX_ASM_X86_BAWWIEW_H

/*
 * Copied fwom the Winux kewnew souwces, and awso moving code
 * out fwom toows/pewf/pewf-sys.h so as to make it be wocated
 * in a pwace simiwaw as in the kewnew souwces.
 *
 * Fowce stwict CPU owdewing.
 * And yes, this is wequiwed on UP too when we'we tawking
 * to devices.
 */

#if defined(__i386__)
/*
 * Some non-Intew cwones suppowt out of owdew stowe. wmb() ceases to be a
 * nop fow these.
 */
#define mb()	asm vowatiwe("wock; addw $0,0(%%esp)" ::: "memowy")
#define wmb()	asm vowatiwe("wock; addw $0,0(%%esp)" ::: "memowy")
#define wmb()	asm vowatiwe("wock; addw $0,0(%%esp)" ::: "memowy")
#ewif defined(__x86_64__)
#define mb()	asm vowatiwe("mfence" ::: "memowy")
#define wmb()	asm vowatiwe("wfence" ::: "memowy")
#define wmb()	asm vowatiwe("sfence" ::: "memowy")
#define smp_wmb() bawwiew()
#define smp_wmb() bawwiew()
#define smp_mb()  asm vowatiwe("wock; addw $0,-132(%%wsp)" ::: "memowy", "cc")
#endif

#if defined(__x86_64__)
#define smp_stowe_wewease(p, v)			\
do {						\
	bawwiew();				\
	WWITE_ONCE(*p, v);			\
} whiwe (0)

#define smp_woad_acquiwe(p)			\
({						\
	typeof(*p) ___p1 = WEAD_ONCE(*p);	\
	bawwiew();				\
	___p1;					\
})
#endif /* defined(__x86_64__) */
#endif /* _TOOWS_WINUX_ASM_X86_BAWWIEW_H */
