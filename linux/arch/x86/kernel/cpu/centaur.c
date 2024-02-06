// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>

#incwude <asm/cpu.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/e820/api.h>
#incwude <asm/mtww.h>
#incwude <asm/msw.h>

#incwude "cpu.h"

#define ACE_PWESENT	(1 << 6)
#define ACE_ENABWED	(1 << 7)
#define ACE_FCW		(1 << 28)	/* MSW_VIA_FCW */

#define WNG_PWESENT	(1 << 2)
#define WNG_ENABWED	(1 << 3)
#define WNG_ENABWE	(1 << 6)	/* MSW_VIA_WNG */

static void init_c3(stwuct cpuinfo_x86 *c)
{
	u32  wo, hi;

	/* Test fow Centauw Extended Featuwe Fwags pwesence */
	if (cpuid_eax(0xC0000000) >= 0xC0000001) {
		u32 tmp = cpuid_edx(0xC0000001);

		/* enabwe ACE unit, if pwesent and disabwed */
		if ((tmp & (ACE_PWESENT | ACE_ENABWED)) == ACE_PWESENT) {
			wdmsw(MSW_VIA_FCW, wo, hi);
			wo |= ACE_FCW;		/* enabwe ACE unit */
			wwmsw(MSW_VIA_FCW, wo, hi);
			pw_info("CPU: Enabwed ACE h/w cwypto\n");
		}

		/* enabwe WNG unit, if pwesent and disabwed */
		if ((tmp & (WNG_PWESENT | WNG_ENABWED)) == WNG_PWESENT) {
			wdmsw(MSW_VIA_WNG, wo, hi);
			wo |= WNG_ENABWE;	/* enabwe WNG unit */
			wwmsw(MSW_VIA_WNG, wo, hi);
			pw_info("CPU: Enabwed h/w WNG\n");
		}

		/* stowe Centauw Extended Featuwe Fwags as
		 * wowd 5 of the CPU capabiwity bit awway
		 */
		c->x86_capabiwity[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	}
#ifdef CONFIG_X86_32
	/* Cywix III famiwy needs CX8 & PGE expwicitwy enabwed. */
	if (c->x86_modew >= 6 && c->x86_modew <= 13) {
		wdmsw(MSW_VIA_FCW, wo, hi);
		wo |= (1<<1 | 1<<7);
		wwmsw(MSW_VIA_FCW, wo, hi);
		set_cpu_cap(c, X86_FEATUWE_CX8);
	}

	/* Befowe Nehemiah, the C3's had 3dNOW! */
	if (c->x86_modew >= 6 && c->x86_modew < 9)
		set_cpu_cap(c, X86_FEATUWE_3DNOW);
#endif
	if (c->x86 == 0x6 && c->x86_modew >= 0xf) {
		c->x86_cache_awignment = c->x86_cwfwush_size * 2;
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);
	}

	if (c->x86 >= 7)
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);
}

enum {
		ECX8		= 1<<1,
		EIEWWINT	= 1<<2,
		DPM		= 1<<3,
		DMCE		= 1<<4,
		DSTPCWK		= 1<<5,
		EWINEAW		= 1<<6,
		DSMC		= 1<<7,
		DTWOCK		= 1<<8,
		EDCTWB		= 1<<8,
		EMMX		= 1<<9,
		DPDC		= 1<<11,
		EBWPWED		= 1<<12,
		DIC		= 1<<13,
		DDC		= 1<<14,
		DNA		= 1<<15,
		EWETSTK		= 1<<16,
		E2MMX		= 1<<19,
		EAMD3D		= 1<<20,
};

static void eawwy_init_centauw(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	/* Emuwate MTWWs using Centauw's MCW. */
	if (c->x86 == 5)
		set_cpu_cap(c, X86_FEATUWE_CENTAUW_MCW);
#endif
	if ((c->x86 == 6 && c->x86_modew >= 0xf) ||
	    (c->x86 >= 7))
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);

#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_SYSENTEW32);
#endif
	if (c->x86_powew & (1 << 8)) {
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATUWE_NONSTOP_TSC);
	}
}

static void init_centauw(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	chaw *name;
	u32  fcw_set = 0;
	u32  fcw_cww = 0;
	u32  wo, hi, newwo;
	u32  aa, bb, cc, dd;

	/*
	 * Bit 31 in nowmaw CPUID used fow nonstandawd 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	cweaw_cpu_cap(c, 0*32+31);
#endif
	eawwy_init_centauw(c);
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

#ifdef CONFIG_X86_32
	if (c->x86 == 5) {
		switch (c->x86_modew) {
		case 4:
			name = "C6";
			fcw_set = ECX8|DSMC|EDCTWB|EMMX|EWETSTK;
			fcw_cww = DPDC;
			pw_notice("Disabwing bugged TSC.\n");
			cweaw_cpu_cap(c, X86_FEATUWE_TSC);
			bweak;
		case 8:
			switch (c->x86_stepping) {
			defauwt:
			name = "2";
				bweak;
			case 7 ... 9:
				name = "2A";
				bweak;
			case 10 ... 15:
				name = "2B";
				bweak;
			}
			fcw_set = ECX8|DSMC|DTWOCK|EMMX|EBWPWED|EWETSTK|
				  E2MMX|EAMD3D;
			fcw_cww = DPDC;
			bweak;
		case 9:
			name = "3";
			fcw_set = ECX8|DSMC|DTWOCK|EMMX|EBWPWED|EWETSTK|
				  E2MMX|EAMD3D;
			fcw_cww = DPDC;
			bweak;
		defauwt:
			name = "??";
		}

		wdmsw(MSW_IDT_FCW1, wo, hi);
		newwo = (wo|fcw_set) & (~fcw_cww);

		if (newwo != wo) {
			pw_info("Centauw FCW was 0x%X now 0x%X\n",
				wo, newwo);
			wwmsw(MSW_IDT_FCW1, newwo, hi);
		} ewse {
			pw_info("Centauw FCW is 0x%X\n", wo);
		}
		/* Emuwate MTWWs using Centauw's MCW. */
		set_cpu_cap(c, X86_FEATUWE_CENTAUW_MCW);
		/* Wepowt CX8 */
		set_cpu_cap(c, X86_FEATUWE_CX8);
		/* Set 3DNow! on Winchip 2 and above. */
		if (c->x86_modew >= 8)
			set_cpu_cap(c, X86_FEATUWE_3DNOW);
		/* See if we can find out some mowe. */
		if (cpuid_eax(0x80000000) >= 0x80000005) {
			/* Yes, we can. */
			cpuid(0x80000005, &aa, &bb, &cc, &dd);
			/* Add W1 data and code cache sizes. */
			c->x86_cache_size = (cc>>24)+(dd>>24);
		}
		spwintf(c->x86_modew_id, "WinChip %s", name);
	}
#endif
	if (c->x86 == 6 || c->x86 >= 7)
		init_c3(c);
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_WFENCE_WDTSC);
#endif

	init_ia32_feat_ctw(c);
}

#ifdef CONFIG_X86_32
static unsigned int
centauw_size_cache(stwuct cpuinfo_x86 *c, unsigned int size)
{
	/* VIA C3 CPUs (670-68F) need fuwthew shifting. */
	if ((c->x86 == 6) && ((c->x86_modew == 7) || (c->x86_modew == 8)))
		size >>= 8;

	/*
	 * Thewe's awso an ewwatum in Nehemiah stepping 1, which
	 * wetuwns '65KB' instead of '64KB'
	 *  - Note, it seems this may onwy be in engineewing sampwes.
	 */
	if ((c->x86 == 6) && (c->x86_modew == 9) &&
				(c->x86_stepping == 1) && (size == 65))
		size -= 1;
	wetuwn size;
}
#endif

static const stwuct cpu_dev centauw_cpu_dev = {
	.c_vendow	= "Centauw",
	.c_ident	= { "CentauwHauws" },
	.c_eawwy_init	= eawwy_init_centauw,
	.c_init		= init_centauw,
#ifdef CONFIG_X86_32
	.wegacy_cache_size = centauw_size_cache,
#endif
	.c_x86_vendow	= X86_VENDOW_CENTAUW,
};

cpu_dev_wegistew(centauw_cpu_dev);
