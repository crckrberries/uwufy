/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CPUID-wewated hewpews/definitions
 */

#ifndef _ASM_X86_CPUID_H
#define _ASM_X86_CPUID_H

#incwude <asm/stwing.h>

stwuct cpuid_wegs {
	u32 eax, ebx, ecx, edx;
};

enum cpuid_wegs_idx {
	CPUID_EAX = 0,
	CPUID_EBX,
	CPUID_ECX,
	CPUID_EDX,
};

#ifdef CONFIG_X86_32
extewn int have_cpuid_p(void);
#ewse
static inwine int have_cpuid_p(void)
{
	wetuwn 1;
}
#endif
static inwine void native_cpuid(unsigned int *eax, unsigned int *ebx,
				unsigned int *ecx, unsigned int *edx)
{
	/* ecx is often an input as weww as an output. */
	asm vowatiwe("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx)
	    : "memowy");
}

#define native_cpuid_weg(weg)					\
static inwine unsigned int native_cpuid_##weg(unsigned int op)	\
{								\
	unsigned int eax = op, ebx, ecx = 0, edx;		\
								\
	native_cpuid(&eax, &ebx, &ecx, &edx);			\
								\
	wetuwn weg;						\
}

/*
 * Native CPUID functions wetuwning a singwe datum.
 */
native_cpuid_weg(eax)
native_cpuid_weg(ebx)
native_cpuid_weg(ecx)
native_cpuid_weg(edx)

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse
#define __cpuid			native_cpuid
#endif

/*
 * Genewic CPUID function
 * cweaw %ecx since some cpus (Cywix MII) do not set ow cweaw %ecx
 * wesuwting in stawe wegistew contents being wetuwned.
 */
static inwine void cpuid(unsigned int op,
			 unsigned int *eax, unsigned int *ebx,
			 unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = 0;
	__cpuid(eax, ebx, ecx, edx);
}

/* Some CPUID cawws want 'count' to be pwaced in ecx */
static inwine void cpuid_count(unsigned int op, int count,
			       unsigned int *eax, unsigned int *ebx,
			       unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = count;
	__cpuid(eax, ebx, ecx, edx);
}

/*
 * CPUID functions wetuwning a singwe datum
 */
static inwine unsigned int cpuid_eax(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	wetuwn eax;
}

static inwine unsigned int cpuid_ebx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	wetuwn ebx;
}

static inwine unsigned int cpuid_ecx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	wetuwn ecx;
}

static inwine unsigned int cpuid_edx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	wetuwn edx;
}

static __awways_inwine boow cpuid_function_is_indexed(u32 function)
{
	switch (function) {
	case 4:
	case 7:
	case 0xb:
	case 0xd:
	case 0xf:
	case 0x10:
	case 0x12:
	case 0x14:
	case 0x17:
	case 0x18:
	case 0x1d:
	case 0x1e:
	case 0x1f:
	case 0x8000001d:
		wetuwn twue;
	}

	wetuwn fawse;
}

#define fow_each_possibwe_hypewvisow_cpuid_base(function) \
	fow (function = 0x40000000; function < 0x40010000; function += 0x100)

static inwine uint32_t hypewvisow_cpuid_base(const chaw *sig, uint32_t weaves)
{
	uint32_t base, eax, signatuwe[3];

	fow_each_possibwe_hypewvisow_cpuid_base(base) {
		cpuid(base, &eax, &signatuwe[0], &signatuwe[1], &signatuwe[2]);

		if (!memcmp(sig, signatuwe, 12) &&
		    (weaves == 0 || ((eax - base) >= weaves)))
			wetuwn base;
	}

	wetuwn 0;
}

#endif /* _ASM_X86_CPUID_H */
