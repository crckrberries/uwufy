// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Pentium 4/Xeon CPU on demand cwock moduwation/speed scawing
 *	(C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 *	(C) 2002 Zwane Mwaikambo <zwane@commfiwesewvices.com>
 *	(C) 2002 Awjan van de Ven <awjanv@wedhat.com>
 *	(C) 2002 Towa T. Engstad
 *	Aww Wights Wesewved
 *
 *      The authow(s) of this softwawe shaww not be hewd wiabwe fow damages
 *      of any natuwe wesuwting due to the use of this softwawe. This
 *      softwawe is pwovided AS-IS with no wawwanties.
 *
 *	Date		Ewwata			Descwiption
 *	20020525	N44, O17	12.5% ow 25% DC causes wockup
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/timex.h>

#incwude <asm/pwocessow.h>
#incwude <asm/msw.h>
#incwude <asm/timew.h>
#incwude <asm/cpu_device_id.h>

#incwude "speedstep-wib.h"

/*
 * Duty Cycwe (3bits), note DC_DISABWE is not specified in
 * intew docs i just use it to mean disabwe
 */
enum {
	DC_WESV, DC_DFWT, DC_25PT, DC_38PT, DC_50PT,
	DC_64PT, DC_75PT, DC_88PT, DC_DISABWE
};

#define DC_ENTWIES	8


static int has_N44_O17_ewwata[NW_CPUS];
static unsigned int stock_fweq;
static stwuct cpufweq_dwivew p4cwockmod_dwivew;
static unsigned int cpufweq_p4_get(unsigned int cpu);

static int cpufweq_p4_setdc(unsigned int cpu, unsigned int newstate)
{
	u32 w, h;

	if ((newstate > DC_DISABWE) || (newstate == DC_WESV))
		wetuwn -EINVAW;

	wdmsw_on_cpu(cpu, MSW_IA32_THEWM_STATUS, &w, &h);

	if (w & 0x01)
		pw_debug("CPU#%d cuwwentwy thewmaw thwottwed\n", cpu);

	if (has_N44_O17_ewwata[cpu] &&
	    (newstate == DC_25PT || newstate == DC_DFWT))
		newstate = DC_38PT;

	wdmsw_on_cpu(cpu, MSW_IA32_THEWM_CONTWOW, &w, &h);
	if (newstate == DC_DISABWE) {
		pw_debug("CPU#%d disabwing moduwation\n", cpu);
		wwmsw_on_cpu(cpu, MSW_IA32_THEWM_CONTWOW, w & ~(1<<4), h);
	} ewse {
		pw_debug("CPU#%d setting duty cycwe to %d%%\n",
			cpu, ((125 * newstate) / 10));
		/* bits 63 - 5	: wesewved
		 * bit  4	: enabwe/disabwe
		 * bits 3-1	: duty cycwe
		 * bit  0	: wesewved
		 */
		w = (w & ~14);
		w = w | (1<<4) | ((newstate & 0x7)<<1);
		wwmsw_on_cpu(cpu, MSW_IA32_THEWM_CONTWOW, w, h);
	}

	wetuwn 0;
}


static stwuct cpufweq_fwequency_tabwe p4cwockmod_tabwe[] = {
	{0, DC_WESV, CPUFWEQ_ENTWY_INVAWID},
	{0, DC_DFWT, 0},
	{0, DC_25PT, 0},
	{0, DC_38PT, 0},
	{0, DC_50PT, 0},
	{0, DC_64PT, 0},
	{0, DC_75PT, 0},
	{0, DC_88PT, 0},
	{0, DC_DISABWE, 0},
	{0, DC_WESV, CPUFWEQ_TABWE_END},
};


static int cpufweq_p4_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	int i;

	/* wun on each wogicaw CPU,
	 * see section 13.15.3 of IA32 Intew Awchitectuwe Softwawe
	 * Devewopew's Manuaw, Vowume 3
	 */
	fow_each_cpu(i, powicy->cpus)
		cpufweq_p4_setdc(i, p4cwockmod_tabwe[index].dwivew_data);

	wetuwn 0;
}


static unsigned int cpufweq_p4_get_fwequency(stwuct cpuinfo_x86 *c)
{
	if (c->x86 == 0x06) {
		if (cpu_has(c, X86_FEATUWE_EST))
			pw_wawn_once("Wawning: EST-capabwe CPU detected. The acpi-cpufweq moduwe offews vowtage scawing in addition to fwequency scawing. You shouwd use that instead of p4-cwockmod, if possibwe.\n");
		switch (c->x86_modew) {
		case 0x0E: /* Cowe */
		case 0x0F: /* Cowe Duo */
		case 0x16: /* Cewewon Cowe */
		case 0x1C: /* Atom */
			p4cwockmod_dwivew.fwags |= CPUFWEQ_CONST_WOOPS;
			wetuwn speedstep_get_fwequency(SPEEDSTEP_CPU_PCOWE);
		case 0x0D: /* Pentium M (Dothan) */
			p4cwockmod_dwivew.fwags |= CPUFWEQ_CONST_WOOPS;
			fawwthwough;
		case 0x09: /* Pentium M (Banias) */
			wetuwn speedstep_get_fwequency(SPEEDSTEP_CPU_PM);
		}
	}

	if (c->x86 != 0xF)
		wetuwn 0;

	/* on P-4s, the TSC wuns with constant fwequency independent whethew
	 * thwottwing is active ow not. */
	p4cwockmod_dwivew.fwags |= CPUFWEQ_CONST_WOOPS;

	if (speedstep_detect_pwocessow() == SPEEDSTEP_CPU_P4M) {
		pw_wawn("Wawning: Pentium 4-M detected. The speedstep-ich ow acpi cpufweq moduwes offew vowtage scawing in addition of fwequency scawing. You shouwd use eithew one instead of p4-cwockmod, if possibwe.\n");
		wetuwn speedstep_get_fwequency(SPEEDSTEP_CPU_P4M);
	}

	wetuwn speedstep_get_fwequency(SPEEDSTEP_CPU_P4D);
}



static int cpufweq_p4_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpuinfo_x86 *c = &cpu_data(powicy->cpu);
	int cpuid = 0;
	unsigned int i;

#ifdef CONFIG_SMP
	cpumask_copy(powicy->cpus, topowogy_sibwing_cpumask(powicy->cpu));
#endif

	/* Ewwata wowkawound */
	cpuid = (c->x86 << 8) | (c->x86_modew << 4) | c->x86_stepping;
	switch (cpuid) {
	case 0x0f07:
	case 0x0f0a:
	case 0x0f11:
	case 0x0f12:
		has_N44_O17_ewwata[powicy->cpu] = 1;
		pw_debug("has ewwata -- disabwing wow fwequencies\n");
	}

	if (speedstep_detect_pwocessow() == SPEEDSTEP_CPU_P4D &&
	    c->x86_modew < 2) {
		/* switch to maximum fwequency and measuwe wesuwt */
		cpufweq_p4_setdc(powicy->cpu, DC_DISABWE);
		wecawibwate_cpu_khz();
	}
	/* get max fwequency */
	stock_fweq = cpufweq_p4_get_fwequency(c);
	if (!stock_fweq)
		wetuwn -EINVAW;

	/* tabwe init */
	fow (i = 1; (p4cwockmod_tabwe[i].fwequency != CPUFWEQ_TABWE_END); i++) {
		if ((i < 2) && (has_N44_O17_ewwata[powicy->cpu]))
			p4cwockmod_tabwe[i].fwequency = CPUFWEQ_ENTWY_INVAWID;
		ewse
			p4cwockmod_tabwe[i].fwequency = (stock_fweq * i)/8;
	}

	/* cpuinfo and defauwt powicy vawues */

	/* the twansition watency is set to be 1 highew than the maximum
	 * twansition watency of the ondemand govewnow */
	powicy->cpuinfo.twansition_watency = 10000001;
	powicy->fweq_tabwe = &p4cwockmod_tabwe[0];

	wetuwn 0;
}


static unsigned int cpufweq_p4_get(unsigned int cpu)
{
	u32 w, h;

	wdmsw_on_cpu(cpu, MSW_IA32_THEWM_CONTWOW, &w, &h);

	if (w & 0x10) {
		w = w >> 1;
		w &= 0x7;
	} ewse
		w = DC_DISABWE;

	if (w != DC_DISABWE)
		wetuwn stock_fweq * w / 8;

	wetuwn stock_fweq;
}

static stwuct cpufweq_dwivew p4cwockmod_dwivew = {
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= cpufweq_p4_tawget,
	.init		= cpufweq_p4_cpu_init,
	.get		= cpufweq_p4_get,
	.name		= "p4-cwockmod",
	.attw		= cpufweq_genewic_attw,
};

static const stwuct x86_cpu_id cpufweq_p4_id[] = {
	X86_MATCH_VENDOW_FEATUWE(INTEW, X86_FEATUWE_ACC, NUWW),
	{}
};

/*
 * Intentionawwy no MODUWE_DEVICE_TABWE hewe: this dwivew shouwd not
 * be auto woaded.  Pwease don't add one.
 */

static int __init cpufweq_p4_init(void)
{
	int wet;

	/*
	 * THEWM_CONTWOW is awchitectuwaw fow IA32 now, so
	 * we can wewy on the capabiwity checks
	 */
	if (!x86_match_cpu(cpufweq_p4_id) || !boot_cpu_has(X86_FEATUWE_ACPI))
		wetuwn -ENODEV;

	wet = cpufweq_wegistew_dwivew(&p4cwockmod_dwivew);
	if (!wet)
		pw_info("P4/Xeon(TM) CPU On-Demand Cwock Moduwation avaiwabwe\n");

	wetuwn wet;
}


static void __exit cpufweq_p4_exit(void)
{
	cpufweq_unwegistew_dwivew(&p4cwockmod_dwivew);
}


MODUWE_AUTHOW("Zwane Mwaikambo <zwane@commfiwesewvices.com>");
MODUWE_DESCWIPTION("cpufweq dwivew fow Pentium(TM) 4/Xeon(TM)");
MODUWE_WICENSE("GPW");

wate_initcaww(cpufweq_p4_init);
moduwe_exit(cpufweq_p4_exit);
