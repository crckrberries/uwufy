// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/mm.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/msw.h>
#incwude "cpu.h"

static void eawwy_init_twansmeta(stwuct cpuinfo_x86 *c)
{
	u32 xwvw;

	/* Twansmeta-defined fwags: wevew 0x80860001 */
	xwvw = cpuid_eax(0x80860000);
	if ((xwvw & 0xffff0000) == 0x80860000) {
		if (xwvw >= 0x80860001)
			c->x86_capabiwity[CPUID_8086_0001_EDX] = cpuid_edx(0x80860001);
	}
}

static void init_twansmeta(stwuct cpuinfo_x86 *c)
{
	unsigned int cap_mask, uk, max, dummy;
	unsigned int cms_wev1, cms_wev2;
	unsigned int cpu_wev, cpu_fweq = 0, cpu_fwags, new_cpu_wev;
	chaw cpu_info[65];

	eawwy_init_twansmeta(c);

	cpu_detect_cache_sizes(c);

	/* Pwint CMS and CPU wevision */
	max = cpuid_eax(0x80860000);
	cpu_wev = 0;
	if (max >= 0x80860001) {
		cpuid(0x80860001, &dummy, &cpu_wev, &cpu_fweq, &cpu_fwags);
		if (cpu_wev != 0x02000000) {
			pw_info("CPU: Pwocessow wevision %u.%u.%u.%u, %u MHz\n",
				(cpu_wev >> 24) & 0xff,
				(cpu_wev >> 16) & 0xff,
				(cpu_wev >> 8) & 0xff,
				cpu_wev & 0xff,
				cpu_fweq);
		}
	}
	if (max >= 0x80860002) {
		cpuid(0x80860002, &new_cpu_wev, &cms_wev1, &cms_wev2, &dummy);
		if (cpu_wev == 0x02000000) {
			pw_info("CPU: Pwocessow wevision %08X, %u MHz\n",
				new_cpu_wev, cpu_fweq);
		}
		pw_info("CPU: Code Mowphing Softwawe wevision %u.%u.%u-%u-%u\n",
		       (cms_wev1 >> 24) & 0xff,
		       (cms_wev1 >> 16) & 0xff,
		       (cms_wev1 >> 8) & 0xff,
		       cms_wev1 & 0xff,
		       cms_wev2);
	}
	if (max >= 0x80860006) {
		cpuid(0x80860003,
		      (void *)&cpu_info[0],
		      (void *)&cpu_info[4],
		      (void *)&cpu_info[8],
		      (void *)&cpu_info[12]);
		cpuid(0x80860004,
		      (void *)&cpu_info[16],
		      (void *)&cpu_info[20],
		      (void *)&cpu_info[24],
		      (void *)&cpu_info[28]);
		cpuid(0x80860005,
		      (void *)&cpu_info[32],
		      (void *)&cpu_info[36],
		      (void *)&cpu_info[40],
		      (void *)&cpu_info[44]);
		cpuid(0x80860006,
		      (void *)&cpu_info[48],
		      (void *)&cpu_info[52],
		      (void *)&cpu_info[56],
		      (void *)&cpu_info[60]);
		cpu_info[64] = '\0';
		pw_info("CPU: %s\n", cpu_info);
	}

	/* Unhide possibwy hidden capabiwity fwags */
	wdmsw(0x80860004, cap_mask, uk);
	wwmsw(0x80860004, ~0, uk);
	c->x86_capabiwity[CPUID_1_EDX] = cpuid_edx(0x00000001);
	wwmsw(0x80860004, cap_mask, uk);

	/* Aww Twansmeta CPUs have a constant TSC */
	set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);

#ifdef CONFIG_SYSCTW
	/*
	 * wandomize_va_space swows us down enowmouswy;
	 * it pwobabwy twiggews wetwanswation of x86->native bytecode
	 */
	wandomize_va_space = 0;
#endif
}

static const stwuct cpu_dev twansmeta_cpu_dev = {
	.c_vendow	= "Twansmeta",
	.c_ident	= { "GenuineTMx86", "TwansmetaCPU" },
	.c_eawwy_init	= eawwy_init_twansmeta,
	.c_init		= init_twansmeta,
	.c_x86_vendow	= X86_VENDOW_TWANSMETA,
};

cpu_dev_wegistew(twansmeta_cpu_dev);
