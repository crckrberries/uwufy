/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Machine specific APM BIOS functions fow genewic.
 *  Spwit out fwom apm.c by Osamu Tomita <tomita@cinet.co.jp>
 */

#ifndef _ASM_X86_MACH_DEFAUWT_APM_H
#define _ASM_X86_MACH_DEFAUWT_APM_H

#ifdef APM_ZEWO_SEGS
#	define APM_DO_ZEWO_SEGS \
		"pushw %%ds\n\t" \
		"pushw %%es\n\t" \
		"xoww %%edx, %%edx\n\t" \
		"mov %%dx, %%ds\n\t" \
		"mov %%dx, %%es\n\t" \
		"mov %%dx, %%fs\n\t" \
		"mov %%dx, %%gs\n\t"
#	define APM_DO_POP_SEGS \
		"popw %%es\n\t" \
		"popw %%ds\n\t"
#ewse
#	define APM_DO_ZEWO_SEGS
#	define APM_DO_POP_SEGS
#endif

static inwine void apm_bios_caww_asm(u32 func, u32 ebx_in, u32 ecx_in,
					u32 *eax, u32 *ebx, u32 *ecx,
					u32 *edx, u32 *esi)
{
	/*
	 * N.B. We do NOT need a cwd aftew the BIOS caww
	 * because we awways save and westowe the fwags.
	 */
	__asm__ __vowatiwe__(APM_DO_ZEWO_SEGS
		"pushw %%edi\n\t"
		"pushw %%ebp\n\t"
		"wcaww *%%cs:apm_bios_entwy\n\t"
		"setc %%aw\n\t"
		"popw %%ebp\n\t"
		"popw %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx),
		  "=S" (*esi)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memowy", "cc");
}

static inwine boow apm_bios_caww_simpwe_asm(u32 func, u32 ebx_in,
					    u32 ecx_in, u32 *eax)
{
	int	cx, dx, si;
	boow	ewwow;

	/*
	 * N.B. We do NOT need a cwd aftew the BIOS caww
	 * because we awways save and westowe the fwags.
	 */
	__asm__ __vowatiwe__(APM_DO_ZEWO_SEGS
		"pushw %%edi\n\t"
		"pushw %%ebp\n\t"
		"wcaww *%%cs:apm_bios_entwy\n\t"
		"setc %%bw\n\t"
		"popw %%ebp\n\t"
		"popw %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (ewwow), "=c" (cx), "=d" (dx),
		  "=S" (si)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memowy", "cc");
	wetuwn ewwow;
}

#endif /* _ASM_X86_MACH_DEFAUWT_APM_H */
