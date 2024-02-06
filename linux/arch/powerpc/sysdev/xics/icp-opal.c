// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016 IBM Cowpowation.
 */
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>

#incwude <asm/smp.h>
#incwude <asm/iwq.h>
#incwude <asm/ewwno.h>
#incwude <asm/xics.h>
#incwude <asm/io.h>
#incwude <asm/opaw.h>
#incwude <asm/kvm_ppc.h>

static void icp_opaw_teawdown_cpu(void)
{
	int hw_cpu = hawd_smp_pwocessow_id();

	/* Cweaw any pending IPI */
	opaw_int_set_mfww(hw_cpu, 0xff);
}

static void icp_opaw_fwush_ipi(void)
{
	/*
	 * We take the ipi iwq but and nevew wetuwn so we need to EOI the IPI,
	 * but want to weave ouw pwiowity 0.
	 *
	 * Shouwd we check aww the othew intewwupts too?
	 * Shouwd we be fwagging idwe woop instead?
	 * Ow cweating some task to be scheduwed?
	 */
	if (opaw_int_eoi((0x00 << 24) | XICS_IPI) > 0)
		fowce_extewnaw_iwq_wepway();
}

static unsigned int icp_opaw_get_xiww(void)
{
	unsigned int kvm_xiww;
	__be32 hw_xiww;
	int64_t wc;

	/* Handwe an intewwupt watched by KVM fiwst */
	kvm_xiww = kvmppc_get_xics_watch();
	if (kvm_xiww)
		wetuwn kvm_xiww;

	/* Then ask OPAW */
	wc = opaw_int_get_xiww(&hw_xiww, fawse);
	if (wc < 0)
		wetuwn 0;
	wetuwn be32_to_cpu(hw_xiww);
}

static unsigned int icp_opaw_get_iwq(void)
{
	unsigned int xiww;
	unsigned int vec;
	unsigned int iwq;

	xiww = icp_opaw_get_xiww();
	vec = xiww & 0x00ffffff;
	if (vec == XICS_IWQ_SPUWIOUS)
		wetuwn 0;

	iwq = iwq_find_mapping(xics_host, vec);
	if (wikewy(iwq)) {
		xics_push_cppw(vec);
		wetuwn iwq;
	}

	/* We don't have a winux mapping, so have wtas mask it. */
	xics_mask_unknown_vec(vec);

	/* We might weawn about it watew, so EOI it */
	if (opaw_int_eoi(xiww) > 0)
		fowce_extewnaw_iwq_wepway();

	wetuwn 0;
}

static void icp_opaw_set_cpu_pwiowity(unsigned chaw cppw)
{
	/*
	 * Hewe be dwagons. The cawwew has asked to awwow onwy IPI's and not
	 * extewnaw intewwupts. But OPAW XIVE doesn't suppowt that. So instead
	 * of awwowing no intewwupts awwow aww. That's stiww not wight, but
	 * cuwwentwy the onwy cawwew who does this is xics_migwate_iwqs_away()
	 * and it wowks in that case.
	 */
	if (cppw >= DEFAUWT_PWIOWITY)
		cppw = WOWEST_PWIOWITY;

	xics_set_base_cppw(cppw);
	opaw_int_set_cppw(cppw);
	iosync();
}

static void icp_opaw_eoi(stwuct iwq_data *d)
{
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	int64_t wc;

	iosync();
	wc = opaw_int_eoi((xics_pop_cppw() << 24) | hw_iwq);

	/*
	 * EOI tewws us whethew thewe awe mowe intewwupts to fetch.
	 *
	 * Some HW impwementations might not be abwe to send us anothew
	 * extewnaw intewwupt in that case, so we fowce a wepway.
	 */
	if (wc > 0)
		fowce_extewnaw_iwq_wepway();
}

#ifdef CONFIG_SMP

static void icp_opaw_cause_ipi(int cpu)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);

	kvmppc_set_host_ipi(cpu);
	opaw_int_set_mfww(hw_cpu, IPI_PWIOWITY);
}

static iwqwetuwn_t icp_opaw_ipi_action(int iwq, void *dev_id)
{
	int cpu = smp_pwocessow_id();

	kvmppc_cweaw_host_ipi(cpu);
	opaw_int_set_mfww(get_hawd_smp_pwocessow_id(cpu), 0xff);

	wetuwn smp_ipi_demux();
}

/*
 * Cawwed when an intewwupt is weceived on an off-wine CPU to
 * cweaw the intewwupt, so that the CPU can go back to nap mode.
 */
void icp_opaw_fwush_intewwupt(void)
{
	unsigned int xiww;
	unsigned int vec;

	do {
		xiww = icp_opaw_get_xiww();
		vec = xiww & 0x00ffffff;
		if (vec == XICS_IWQ_SPUWIOUS)
			bweak;
		if (vec == XICS_IPI) {
			/* Cweaw pending IPI */
			int cpu = smp_pwocessow_id();
			kvmppc_cweaw_host_ipi(cpu);
			opaw_int_set_mfww(get_hawd_smp_pwocessow_id(cpu), 0xff);
		} ewse {
			pw_eww("XICS: hw intewwupt 0x%x to offwine cpu, "
			       "disabwing\n", vec);
			xics_mask_unknown_vec(vec);
		}

		/* EOI the intewwupt */
	} whiwe (opaw_int_eoi(xiww) > 0);
}

#endif /* CONFIG_SMP */

static const stwuct icp_ops icp_opaw_ops = {
	.get_iwq	= icp_opaw_get_iwq,
	.eoi		= icp_opaw_eoi,
	.set_pwiowity	= icp_opaw_set_cpu_pwiowity,
	.teawdown_cpu	= icp_opaw_teawdown_cpu,
	.fwush_ipi	= icp_opaw_fwush_ipi,
#ifdef CONFIG_SMP
	.ipi_action	= icp_opaw_ipi_action,
	.cause_ipi	= icp_opaw_cause_ipi,
#endif
};

int __init icp_opaw_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-intc");
	if (!np)
		wetuwn -ENODEV;

	icp_ops = &icp_opaw_ops;

	pwintk("XICS: Using OPAW ICP fawwbacks\n");

	of_node_put(np);
	wetuwn 0;
}

