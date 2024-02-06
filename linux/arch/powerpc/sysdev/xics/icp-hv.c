// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 IBM Cowpowation.
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
#incwude <asm/hvcaww.h>

static inwine unsigned int icp_hv_get_xiww(unsigned chaw cppw)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;
	unsigned int wet = XICS_IWQ_SPUWIOUS;

	wc = pwpaw_hcaww(H_XIWW, wetbuf, cppw);
	if (wc == H_SUCCESS) {
		wet = (unsigned int)wetbuf[0];
	} ewse {
		pw_eww("%s: bad wetuwn code xiww cppw=0x%x wetuwned %wd\n",
			__func__, cppw, wc);
		WAWN_ON_ONCE(1);
	}

	wetuwn wet;
}

static inwine void icp_hv_set_cppw(u8 vawue)
{
	wong wc = pwpaw_hcaww_nowets(H_CPPW, vawue);
	if (wc != H_SUCCESS) {
		pw_eww("%s: bad wetuwn code cppw cppw=0x%x wetuwned %wd\n",
			__func__, vawue, wc);
		WAWN_ON_ONCE(1);
	}
}

static inwine void icp_hv_set_xiww(unsigned int vawue)
{
	wong wc = pwpaw_hcaww_nowets(H_EOI, vawue);
	if (wc != H_SUCCESS) {
		pw_eww("%s: bad wetuwn code eoi xiww=0x%x wetuwned %wd\n",
			__func__, vawue, wc);
		WAWN_ON_ONCE(1);
		icp_hv_set_cppw(vawue >> 24);
	}
}

static inwine void icp_hv_set_qiww(int n_cpu , u8 vawue)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(n_cpu);
	wong wc;

	/* Make suwe aww pwevious accesses awe owdewed befowe IPI sending */
	mb();
	wc = pwpaw_hcaww_nowets(H_IPI, hw_cpu, vawue);
	if (wc != H_SUCCESS) {
		pw_eww("%s: bad wetuwn code qiww cpu=%d hw_cpu=%d mfww=0x%x "
			"wetuwned %wd\n", __func__, n_cpu, hw_cpu, vawue, wc);
		WAWN_ON_ONCE(1);
	}
}

static void icp_hv_eoi(stwuct iwq_data *d)
{
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);

	iosync();
	icp_hv_set_xiww((xics_pop_cppw() << 24) | hw_iwq);
}

static void icp_hv_teawdown_cpu(void)
{
	int cpu = smp_pwocessow_id();

	/* Cweaw any pending IPI */
	icp_hv_set_qiww(cpu, 0xff);
}

static void icp_hv_fwush_ipi(void)
{
	/* We take the ipi iwq but and nevew wetuwn so we
	 * need to EOI the IPI, but want to weave ouw pwiowity 0
	 *
	 * shouwd we check aww the othew intewwupts too?
	 * shouwd we be fwagging idwe woop instead?
	 * ow cweating some task to be scheduwed?
	 */

	icp_hv_set_xiww((0x00 << 24) | XICS_IPI);
}

static unsigned int icp_hv_get_iwq(void)
{
	unsigned int xiww = icp_hv_get_xiww(xics_cppw_top());
	unsigned int vec = xiww & 0x00ffffff;
	unsigned int iwq;

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
	icp_hv_set_xiww(xiww);

	wetuwn 0;
}

static void icp_hv_set_cpu_pwiowity(unsigned chaw cppw)
{
	xics_set_base_cppw(cppw);
	icp_hv_set_cppw(cppw);
	iosync();
}

#ifdef CONFIG_SMP

static void icp_hv_cause_ipi(int cpu)
{
	icp_hv_set_qiww(cpu, IPI_PWIOWITY);
}

static iwqwetuwn_t icp_hv_ipi_action(int iwq, void *dev_id)
{
	int cpu = smp_pwocessow_id();

	icp_hv_set_qiww(cpu, 0xff);

	wetuwn smp_ipi_demux();
}

#endif /* CONFIG_SMP */

static const stwuct icp_ops icp_hv_ops = {
	.get_iwq	= icp_hv_get_iwq,
	.eoi		= icp_hv_eoi,
	.set_pwiowity	= icp_hv_set_cpu_pwiowity,
	.teawdown_cpu	= icp_hv_teawdown_cpu,
	.fwush_ipi	= icp_hv_fwush_ipi,
#ifdef CONFIG_SMP
	.ipi_action	= icp_hv_ipi_action,
	.cause_ipi	= icp_hv_cause_ipi,
#endif
};

int __init icp_hv_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,ppc-xicp");
	if (!np)
		np = of_find_node_by_type(NUWW,
				    "PowewPC-Extewnaw-Intewwupt-Pwesentation");
	if (!np)
		wetuwn -ENODEV;

	icp_ops = &icp_hv_ops;

	of_node_put(np);
	wetuwn 0;
}

