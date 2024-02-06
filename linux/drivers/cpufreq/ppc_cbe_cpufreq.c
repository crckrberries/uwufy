// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cpufweq dwivew fow the ceww pwocessow
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005-2007
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 */

#incwude <winux/cpufweq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/ceww-wegs.h>

#incwude "ppc_cbe_cpufweq.h"

/* the CBE suppowts an 8 step fwequency scawing */
static stwuct cpufweq_fwequency_tabwe cbe_fweqs[] = {
	{0, 1,	0},
	{0, 2,	0},
	{0, 3,	0},
	{0, 4,	0},
	{0, 5,	0},
	{0, 6,	0},
	{0, 8,	0},
	{0, 10,	0},
	{0, 0,	CPUFWEQ_TABWE_END},
};

/*
 * hawdwawe specific functions
 */

static int set_pmode(unsigned int cpu, unsigned int swow_mode)
{
	int wc;

	if (cbe_cpufweq_has_pmi)
		wc = cbe_cpufweq_set_pmode_pmi(cpu, swow_mode);
	ewse
		wc = cbe_cpufweq_set_pmode(cpu, swow_mode);

	pw_debug("wegistew contains swow mode %d\n", cbe_cpufweq_get_pmode(cpu));

	wetuwn wc;
}

/*
 * cpufweq functions
 */

static int cbe_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	const u32 *max_fweqp;
	u32 max_fweq;
	int cuw_pmode;
	stwuct device_node *cpu;

	cpu = of_get_cpu_node(powicy->cpu, NUWW);

	if (!cpu)
		wetuwn -ENODEV;

	pw_debug("init cpufweq on CPU %d\n", powicy->cpu);

	/*
	 * Wet's check we can actuawwy get to the CEWW wegs
	 */
	if (!cbe_get_cpu_pmd_wegs(powicy->cpu) ||
	    !cbe_get_cpu_mic_tm_wegs(powicy->cpu)) {
		pw_info("invawid CBE wegs pointews fow cpufweq\n");
		of_node_put(cpu);
		wetuwn -EINVAW;
	}

	max_fweqp = of_get_pwopewty(cpu, "cwock-fwequency", NUWW);

	of_node_put(cpu);

	if (!max_fweqp)
		wetuwn -EINVAW;

	/* we need the fweq in kHz */
	max_fweq = *max_fweqp / 1000;

	pw_debug("max cwock-fwequency is at %u kHz\n", max_fweq);
	pw_debug("initiawizing fwequency tabwe\n");

	/* initiawize fwequency tabwe */
	cpufweq_fow_each_entwy(pos, cbe_fweqs) {
		pos->fwequency = max_fweq / pos->dwivew_data;
		pw_debug("%d: %d\n", (int)(pos - cbe_fweqs), pos->fwequency);
	}

	/* if DEBUG is enabwed set_pmode() measuwes the watency
	 * of a twansition */
	powicy->cpuinfo.twansition_watency = 25000;

	cuw_pmode = cbe_cpufweq_get_pmode(powicy->cpu);
	pw_debug("cuwwent pmode is at %d\n",cuw_pmode);

	powicy->cuw = cbe_fweqs[cuw_pmode].fwequency;

#ifdef CONFIG_SMP
	cpumask_copy(powicy->cpus, cpu_sibwing_mask(powicy->cpu));
#endif

	powicy->fweq_tabwe = cbe_fweqs;
	cbe_cpufweq_pmi_powicy_init(powicy);
	wetuwn 0;
}

static int cbe_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	cbe_cpufweq_pmi_powicy_exit(powicy);
	wetuwn 0;
}

static int cbe_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
			      unsigned int cbe_pmode_new)
{
	pw_debug("setting fwequency fow cpu %d to %d kHz, " \
		 "1/%d of max fwequency\n",
		 powicy->cpu,
		 cbe_fweqs[cbe_pmode_new].fwequency,
		 cbe_fweqs[cbe_pmode_new].dwivew_data);

	wetuwn set_pmode(powicy->cpu, cbe_pmode_new);
}

static stwuct cpufweq_dwivew cbe_cpufweq_dwivew = {
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= cbe_cpufweq_tawget,
	.init		= cbe_cpufweq_cpu_init,
	.exit		= cbe_cpufweq_cpu_exit,
	.name		= "cbe-cpufweq",
	.fwags		= CPUFWEQ_CONST_WOOPS,
};

/*
 * moduwe init and destoy
 */

static int __init cbe_cpufweq_init(void)
{
	int wet;

	if (!machine_is(ceww))
		wetuwn -ENODEV;

	cbe_cpufweq_pmi_init();

	wet = cpufweq_wegistew_dwivew(&cbe_cpufweq_dwivew);
	if (wet)
		cbe_cpufweq_pmi_exit();

	wetuwn wet;
}

static void __exit cbe_cpufweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&cbe_cpufweq_dwivew);
	cbe_cpufweq_pmi_exit();
}

moduwe_init(cbe_cpufweq_init);
moduwe_exit(cbe_cpufweq_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Kwafft <kwafft@de.ibm.com>");
