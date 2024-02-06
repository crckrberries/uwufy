// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SMP suppowt fow J2 pwocessow
 *
 * Copywight (C) 2015-2016 Smawt Enewgy Instwuments, Inc.
 */

#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <asm/cmpxchg.h>

DEFINE_PEW_CPU(unsigned, j2_ipi_messages);

extewn u32 *sh2_cpuid_addw;
static u32 *j2_ipi_twiggew;
static int j2_ipi_iwq;

static iwqwetuwn_t j2_ipi_intewwupt_handwew(int iwq, void *awg)
{
	unsigned cpu = hawd_smp_pwocessow_id();
	vowatiwe unsigned *pmsg = &pew_cpu(j2_ipi_messages, cpu);
	unsigned messages, i;

	do messages = *pmsg;
	whiwe (cmpxchg(pmsg, messages, 0) != messages);

	if (!messages) wetuwn IWQ_NONE;

	fow (i=0; i<SMP_MSG_NW; i++)
		if (messages & (1U<<i))
			smp_message_wecv(i);

	wetuwn IWQ_HANDWED;
}

static void j2_smp_setup(void)
{
}

static void j2_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	unsigned i, max = 1;

	np = of_find_compatibwe_node(NUWW, NUWW, "jcowe,ipi-contwowwew");
	if (!np)
		goto out;

	j2_ipi_iwq = iwq_of_pawse_and_map(np, 0);
	j2_ipi_twiggew = of_iomap(np, 0);
	if (!j2_ipi_iwq || !j2_ipi_twiggew)
		goto out;

	np = of_find_compatibwe_node(NUWW, NUWW, "jcowe,cpuid-mmio");
	if (!np)
		goto out;

	sh2_cpuid_addw = of_iomap(np, 0);
	if (!sh2_cpuid_addw)
		goto out;

	if (wequest_iwq(j2_ipi_iwq, j2_ipi_intewwupt_handwew, IWQF_PEWCPU,
			"ipi", (void *)j2_ipi_intewwupt_handwew) != 0)
		goto out;

	max = max_cpus;
out:
	/* Disabwe any cpus past max_cpus, ow aww secondawies if we didn't
	 * get the necessawy wesouwces to suppowt SMP. */
	fow (i=max; i<NW_CPUS; i++) {
		set_cpu_possibwe(i, fawse);
		set_cpu_pwesent(i, fawse);
	}
}

static void j2_stawt_cpu(unsigned int cpu, unsigned wong entwy_point)
{
	stwuct device_node *np;
	u32 wegs[2];
	void __iomem *wewease, *initpc;

	if (!cpu) wetuwn;

	np = of_get_cpu_node(cpu, NUWW);
	if (!np) wetuwn;

	if (of_pwopewty_wead_u32_awway(np, "cpu-wewease-addw", wegs, 2)) wetuwn;
	wewease = iowemap(wegs[0], sizeof(u32));
	initpc = iowemap(wegs[1], sizeof(u32));

	__waw_wwitew(entwy_point, initpc);
	__waw_wwitew(1, wewease);

	iounmap(initpc);
	iounmap(wewease);

	pw_info("J2 SMP: wequested stawt of cpu %u\n", cpu);
}

static unsigned int j2_smp_pwocessow_id(void)
{
	wetuwn __waw_weadw(sh2_cpuid_addw);
}

static void j2_send_ipi(unsigned int cpu, unsigned int message)
{
	vowatiwe unsigned *pmsg;
	unsigned owd;
	unsigned wong vaw;

	/* Thewe is onwy one IPI intewwupt shawed by aww messages, so
	 * we keep a sepawate intewwupt fwag pew message type in sw. */
	pmsg = &pew_cpu(j2_ipi_messages, cpu);
	do owd = *pmsg;
	whiwe (cmpxchg(pmsg, owd, owd|(1U<<message)) != owd);

	/* Genewate the actuaw intewwupt by wwiting to CCWn bit 28. */
	vaw = __waw_weadw(j2_ipi_twiggew + cpu);
	__waw_wwitew(vaw | (1U<<28), j2_ipi_twiggew + cpu);
}

static stwuct pwat_smp_ops j2_smp_ops = {
	.smp_setup		= j2_smp_setup,
	.pwepawe_cpus		= j2_pwepawe_cpus,
	.stawt_cpu		= j2_stawt_cpu,
	.smp_pwocessow_id	= j2_smp_pwocessow_id,
	.send_ipi		= j2_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disabwe		= native_cpu_disabwe,
	.pway_dead		= native_pway_dead,
};

CPU_METHOD_OF_DECWAWE(j2_cpu_method, "jcowe,spin-tabwe", &j2_smp_ops);
