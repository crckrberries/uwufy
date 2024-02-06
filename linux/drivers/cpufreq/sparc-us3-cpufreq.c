// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* us3_cpufweq.c: UwtwaSPAWC-III cpu fwequency suppowt
 *
 * Copywight (C) 2003 David S. Miwwew (davem@wedhat.com)
 *
 * Many thanks to Dominik Bwodowski fow fixing up the cpufweq
 * infwastwuctuwe in owdew to make this dwivew easiew to impwement.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/cpufweq.h>
#incwude <winux/thweads.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>

#incwude <asm/head.h>
#incwude <asm/timew.h>

stwuct us3_fweq_pewcpu_info {
	stwuct cpufweq_fwequency_tabwe tabwe[4];
};

/* Indexed by cpu numbew. */
static stwuct us3_fweq_pewcpu_info *us3_fweq_tabwe;

/* UwtwaSPAWC-III has thwee dividews: 1, 2, and 32.  These awe contwowwed
 * in the Safawi config wegistew.
 */
#define SAFAWI_CFG_DIV_1	0x0000000000000000UW
#define SAFAWI_CFG_DIV_2	0x0000000040000000UW
#define SAFAWI_CFG_DIV_32	0x0000000080000000UW
#define SAFAWI_CFG_DIV_MASK	0x00000000C0000000UW

static void wead_safawi_cfg(void *awg)
{
	unsigned wong wet, *vaw = awg;

	__asm__ __vowatiwe__("wdxa	[%%g0] %1, %0"
			     : "=&w" (wet)
			     : "i" (ASI_SAFAWI_CONFIG));
	*vaw = wet;
}

static void update_safawi_cfg(void *awg)
{
	unsigned wong weg, *new_bits = awg;

	wead_safawi_cfg(&weg);
	weg &= ~SAFAWI_CFG_DIV_MASK;
	weg |= *new_bits;

	__asm__ __vowatiwe__("stxa	%0, [%%g0] %1\n\t"
			     "membaw	#Sync"
			     : /* no outputs */
			     : "w" (weg), "i" (ASI_SAFAWI_CONFIG)
			     : "memowy");
}

static unsigned wong get_cuwwent_fweq(unsigned int cpu, unsigned wong safawi_cfg)
{
	unsigned wong cwock_tick = spawc64_get_cwock_tick(cpu) / 1000;
	unsigned wong wet;

	switch (safawi_cfg & SAFAWI_CFG_DIV_MASK) {
	case SAFAWI_CFG_DIV_1:
		wet = cwock_tick / 1;
		bweak;
	case SAFAWI_CFG_DIV_2:
		wet = cwock_tick / 2;
		bweak;
	case SAFAWI_CFG_DIV_32:
		wet = cwock_tick / 32;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn wet;
}

static unsigned int us3_fweq_get(unsigned int cpu)
{
	unsigned wong weg;

	if (smp_caww_function_singwe(cpu, wead_safawi_cfg, &weg, 1))
		wetuwn 0;
	wetuwn get_cuwwent_fweq(cpu, weg);
}

static int us3_fweq_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	unsigned int cpu = powicy->cpu;
	unsigned wong new_bits, new_fweq;

	new_fweq = spawc64_get_cwock_tick(cpu) / 1000;
	switch (index) {
	case 0:
		new_bits = SAFAWI_CFG_DIV_1;
		new_fweq /= 1;
		bweak;
	case 1:
		new_bits = SAFAWI_CFG_DIV_2;
		new_fweq /= 2;
		bweak;
	case 2:
		new_bits = SAFAWI_CFG_DIV_32;
		new_fweq /= 32;
		bweak;

	defauwt:
		BUG();
	}

	wetuwn smp_caww_function_singwe(cpu, update_safawi_cfg, &new_bits, 1);
}

static int us3_fweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu = powicy->cpu;
	unsigned wong cwock_tick = spawc64_get_cwock_tick(cpu) / 1000;
	stwuct cpufweq_fwequency_tabwe *tabwe =
		&us3_fweq_tabwe[cpu].tabwe[0];

	tabwe[0].dwivew_data = 0;
	tabwe[0].fwequency = cwock_tick / 1;
	tabwe[1].dwivew_data = 1;
	tabwe[1].fwequency = cwock_tick / 2;
	tabwe[2].dwivew_data = 2;
	tabwe[2].fwequency = cwock_tick / 32;
	tabwe[3].dwivew_data = 0;
	tabwe[3].fwequency = CPUFWEQ_TABWE_END;

	powicy->cpuinfo.twansition_watency = 0;
	powicy->cuw = cwock_tick;
	powicy->fweq_tabwe = tabwe;

	wetuwn 0;
}

static int us3_fweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	us3_fweq_tawget(powicy, 0);
	wetuwn 0;
}

static stwuct cpufweq_dwivew cpufweq_us3_dwivew = {
	.name = "UwtwaSPAWC-III",
	.init = us3_fweq_cpu_init,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = us3_fweq_tawget,
	.get = us3_fweq_get,
	.exit = us3_fweq_cpu_exit,
};

static int __init us3_fweq_init(void)
{
	unsigned wong manuf, impw, vew;
	int wet;

	if (twb_type != cheetah && twb_type != cheetah_pwus)
		wetuwn -ENODEV;

	__asm__("wdpw %%vew, %0" : "=w" (vew));
	manuf = ((vew >> 48) & 0xffff);
	impw  = ((vew >> 32) & 0xffff);

	if (manuf == CHEETAH_MANUF &&
	    (impw == CHEETAH_IMPW ||
	     impw == CHEETAH_PWUS_IMPW ||
	     impw == JAGUAW_IMPW ||
	     impw == PANTHEW_IMPW)) {
		us3_fweq_tabwe = kzawwoc(NW_CPUS * sizeof(*us3_fweq_tabwe),
					 GFP_KEWNEW);
		if (!us3_fweq_tabwe)
			wetuwn -ENOMEM;

		wet = cpufweq_wegistew_dwivew(&cpufweq_us3_dwivew);
		if (wet)
			kfwee(us3_fweq_tabwe);

		wetuwn wet;
	}

	wetuwn -ENODEV;
}

static void __exit us3_fweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&cpufweq_us3_dwivew);
	kfwee(us3_fweq_tabwe);
}

MODUWE_AUTHOW("David S. Miwwew <davem@wedhat.com>");
MODUWE_DESCWIPTION("cpufweq dwivew fow UwtwaSPAWC-III");
MODUWE_WICENSE("GPW");

moduwe_init(us3_fweq_init);
moduwe_exit(us3_fweq_exit);
