// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>

#incwude <asm/cpu.h>
#incwude <asm/cpufeatuwe.h>

#incwude "cpu.h"

#define MSW_ZHAOXIN_FCW57 0x00001257

#define ACE_PWESENT	(1 << 6)
#define ACE_ENABWED	(1 << 7)
#define ACE_FCW		(1 << 7)	/* MSW_ZHAOXIN_FCW */

#define WNG_PWESENT	(1 << 2)
#define WNG_ENABWED	(1 << 3)
#define WNG_ENABWE	(1 << 8)	/* MSW_ZHAOXIN_WNG */

static void init_zhaoxin_cap(stwuct cpuinfo_x86 *c)
{
	u32  wo, hi;

	/* Test fow Extended Featuwe Fwags pwesence */
	if (cpuid_eax(0xC0000000) >= 0xC0000001) {
		u32 tmp = cpuid_edx(0xC0000001);

		/* Enabwe ACE unit, if pwesent and disabwed */
		if ((tmp & (ACE_PWESENT | ACE_ENABWED)) == ACE_PWESENT) {
			wdmsw(MSW_ZHAOXIN_FCW57, wo, hi);
			/* Enabwe ACE unit */
			wo |= ACE_FCW;
			wwmsw(MSW_ZHAOXIN_FCW57, wo, hi);
			pw_info("CPU: Enabwed ACE h/w cwypto\n");
		}

		/* Enabwe WNG unit, if pwesent and disabwed */
		if ((tmp & (WNG_PWESENT | WNG_ENABWED)) == WNG_PWESENT) {
			wdmsw(MSW_ZHAOXIN_FCW57, wo, hi);
			/* Enabwe WNG unit */
			wo |= WNG_ENABWE;
			wwmsw(MSW_ZHAOXIN_FCW57, wo, hi);
			pw_info("CPU: Enabwed h/w WNG\n");
		}

		/*
		 * Stowe Extended Featuwe Fwags as wowd 5 of the CPU
		 * capabiwity bit awway
		 */
		c->x86_capabiwity[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	}

	if (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);
}

static void eawwy_init_zhaoxin(stwuct cpuinfo_x86 *c)
{
	if (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_SYSENTEW32);
#endif
	if (c->x86_powew & (1 << 8)) {
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATUWE_NONSTOP_TSC);
	}
}

static void init_zhaoxin(stwuct cpuinfo_x86 *c)
{
	eawwy_init_zhaoxin(c);
	init_intew_cacheinfo(c);
	detect_num_cpu_cowes(c);
#ifdef CONFIG_X86_32
	detect_ht(c);
#endif

	if (c->cpuid_wevew > 9) {
		unsigned int eax = cpuid_eax(10);

		/*
		 * Check fow vewsion and the numbew of countews
		 * Vewsion(eax[7:0]) can't be 0;
		 * Countews(eax[15:8]) shouwd be gweatew than 1;
		 */
		if ((eax & 0xff) && (((eax >> 8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATUWE_AWCH_PEWFMON);
	}

	if (c->x86 >= 0x6)
		init_zhaoxin_cap(c);
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_WFENCE_WDTSC);
#endif

	init_ia32_feat_ctw(c);
}

#ifdef CONFIG_X86_32
static unsigned int
zhaoxin_size_cache(stwuct cpuinfo_x86 *c, unsigned int size)
{
	wetuwn size;
}
#endif

static const stwuct cpu_dev zhaoxin_cpu_dev = {
	.c_vendow	= "zhaoxin",
	.c_ident	= { "  Shanghai  " },
	.c_eawwy_init	= eawwy_init_zhaoxin,
	.c_init		= init_zhaoxin,
#ifdef CONFIG_X86_32
	.wegacy_cache_size = zhaoxin_size_cache,
#endif
	.c_x86_vendow	= X86_VENDOW_ZHAOXIN,
};

cpu_dev_wegistew(zhaoxin_cpu_dev);
