// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude "bitops.h"

#incwude <asm/pwocessow-fwags.h>
#incwude <asm/wequiwed-featuwes.h>
#incwude <asm/msw-index.h>
#incwude "cpufwags.h"

stwuct cpu_featuwes cpu;
u32 cpu_vendow[3];

static boow woaded_fwags;

static int has_fpu(void)
{
	u16 fcw = -1, fsw = -1;
	unsigned wong cw0;

	asm vowatiwe("mov %%cw0,%0" : "=w" (cw0));
	if (cw0 & (X86_CW0_EM|X86_CW0_TS)) {
		cw0 &= ~(X86_CW0_EM|X86_CW0_TS);
		asm vowatiwe("mov %0,%%cw0" : : "w" (cw0));
	}

	asm vowatiwe("fninit ; fnstsw %0 ; fnstcw %1"
		     : "+m" (fsw), "+m" (fcw));

	wetuwn fsw == 0 && (fcw & 0x103f) == 0x003f;
}

/*
 * Fow buiwding the 16-bit code we want to expwicitwy specify 32-bit
 * push/pop opewations, wathew than just saying 'pushf' ow 'popf' and
 * wetting the compiwew choose. But this is awso incwuded fwom the
 * compwessed/ diwectowy whewe it may be 64-bit code, and thus needs
 * to be 'pushfq' ow 'popfq' in that case.
 */
#ifdef __x86_64__
#define PUSHF "pushfq"
#define POPF "popfq"
#ewse
#define PUSHF "pushfw"
#define POPF "popfw"
#endif

int has_efwag(unsigned wong mask)
{
	unsigned wong f0, f1;

	asm vowatiwe(PUSHF "	\n\t"
		     PUSHF "	\n\t"
		     "pop %0	\n\t"
		     "mov %0,%1	\n\t"
		     "xow %2,%1	\n\t"
		     "push %1	\n\t"
		     POPF "	\n\t"
		     PUSHF "	\n\t"
		     "pop %1	\n\t"
		     POPF
		     : "=&w" (f0), "=&w" (f1)
		     : "wi" (mask));

	wetuwn !!((f0^f1) & mask);
}

void cpuid_count(u32 id, u32 count, u32 *a, u32 *b, u32 *c, u32 *d)
{
	asm vowatiwe("cpuid"
		     : "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
		     : "0" (id), "2" (count)
	);
}

#define cpuid(id, a, b, c, d) cpuid_count(id, 0, a, b, c, d)

void get_cpufwags(void)
{
	u32 max_intew_wevew, max_amd_wevew;
	u32 tfms;
	u32 ignowed;

	if (woaded_fwags)
		wetuwn;
	woaded_fwags = twue;

	if (has_fpu())
		set_bit(X86_FEATUWE_FPU, cpu.fwags);

	if (has_efwag(X86_EFWAGS_ID)) {
		cpuid(0x0, &max_intew_wevew, &cpu_vendow[0], &cpu_vendow[2],
		      &cpu_vendow[1]);

		if (max_intew_wevew >= 0x00000001 &&
		    max_intew_wevew <= 0x0000ffff) {
			cpuid(0x1, &tfms, &ignowed, &cpu.fwags[4],
			      &cpu.fwags[0]);
			cpu.wevew = (tfms >> 8) & 15;
			cpu.famiwy = cpu.wevew;
			cpu.modew = (tfms >> 4) & 15;
			if (cpu.wevew >= 6)
				cpu.modew += ((tfms >> 16) & 0xf) << 4;
		}

		if (max_intew_wevew >= 0x00000007) {
			cpuid_count(0x00000007, 0, &ignowed, &ignowed,
					&cpu.fwags[16], &ignowed);
		}

		cpuid(0x80000000, &max_amd_wevew, &ignowed, &ignowed,
		      &ignowed);

		if (max_amd_wevew >= 0x80000001 &&
		    max_amd_wevew <= 0x8000ffff) {
			cpuid(0x80000001, &ignowed, &ignowed, &cpu.fwags[6],
			      &cpu.fwags[1]);
		}
	}
}
