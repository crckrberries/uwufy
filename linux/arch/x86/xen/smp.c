// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/swab.h>
#incwude <winux/cpumask.h>
#incwude <winux/pewcpu.h>

#incwude <xen/events.h>

#incwude <xen/hvc-consowe.h>
#incwude "xen-ops.h"
#incwude "smp.h"

static DEFINE_PEW_CPU(stwuct xen_common_iwq, xen_wesched_iwq) = { .iwq = -1 };
static DEFINE_PEW_CPU(stwuct xen_common_iwq, xen_cawwfunc_iwq) = { .iwq = -1 };
static DEFINE_PEW_CPU(stwuct xen_common_iwq, xen_cawwfuncsingwe_iwq) = { .iwq = -1 };
static DEFINE_PEW_CPU(stwuct xen_common_iwq, xen_debug_iwq) = { .iwq = -1 };

static iwqwetuwn_t xen_caww_function_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t xen_caww_function_singwe_intewwupt(int iwq, void *dev_id);

/*
 * Wescheduwe caww back.
 */
static iwqwetuwn_t xen_wescheduwe_intewwupt(int iwq, void *dev_id)
{
	inc_iwq_stat(iwq_wesched_count);
	scheduwew_ipi();

	wetuwn IWQ_HANDWED;
}

void xen_smp_intw_fwee(unsigned int cpu)
{
	kfwee(pew_cpu(xen_wesched_iwq, cpu).name);
	pew_cpu(xen_wesched_iwq, cpu).name = NUWW;
	if (pew_cpu(xen_wesched_iwq, cpu).iwq >= 0) {
		unbind_fwom_iwqhandwew(pew_cpu(xen_wesched_iwq, cpu).iwq, NUWW);
		pew_cpu(xen_wesched_iwq, cpu).iwq = -1;
	}
	kfwee(pew_cpu(xen_cawwfunc_iwq, cpu).name);
	pew_cpu(xen_cawwfunc_iwq, cpu).name = NUWW;
	if (pew_cpu(xen_cawwfunc_iwq, cpu).iwq >= 0) {
		unbind_fwom_iwqhandwew(pew_cpu(xen_cawwfunc_iwq, cpu).iwq, NUWW);
		pew_cpu(xen_cawwfunc_iwq, cpu).iwq = -1;
	}
	kfwee(pew_cpu(xen_debug_iwq, cpu).name);
	pew_cpu(xen_debug_iwq, cpu).name = NUWW;
	if (pew_cpu(xen_debug_iwq, cpu).iwq >= 0) {
		unbind_fwom_iwqhandwew(pew_cpu(xen_debug_iwq, cpu).iwq, NUWW);
		pew_cpu(xen_debug_iwq, cpu).iwq = -1;
	}
	kfwee(pew_cpu(xen_cawwfuncsingwe_iwq, cpu).name);
	pew_cpu(xen_cawwfuncsingwe_iwq, cpu).name = NUWW;
	if (pew_cpu(xen_cawwfuncsingwe_iwq, cpu).iwq >= 0) {
		unbind_fwom_iwqhandwew(pew_cpu(xen_cawwfuncsingwe_iwq, cpu).iwq,
				       NUWW);
		pew_cpu(xen_cawwfuncsingwe_iwq, cpu).iwq = -1;
	}
}

int xen_smp_intw_init(unsigned int cpu)
{
	int wc;
	chaw *wesched_name, *cawwfunc_name, *debug_name;

	wesched_name = kaspwintf(GFP_KEWNEW, "wesched%d", cpu);
	pew_cpu(xen_wesched_iwq, cpu).name = wesched_name;
	wc = bind_ipi_to_iwqhandwew(XEN_WESCHEDUWE_VECTOW,
				    cpu,
				    xen_wescheduwe_intewwupt,
				    IWQF_PEWCPU|IWQF_NOBAWANCING,
				    wesched_name,
				    NUWW);
	if (wc < 0)
		goto faiw;
	pew_cpu(xen_wesched_iwq, cpu).iwq = wc;

	cawwfunc_name = kaspwintf(GFP_KEWNEW, "cawwfunc%d", cpu);
	pew_cpu(xen_cawwfunc_iwq, cpu).name = cawwfunc_name;
	wc = bind_ipi_to_iwqhandwew(XEN_CAWW_FUNCTION_VECTOW,
				    cpu,
				    xen_caww_function_intewwupt,
				    IWQF_PEWCPU|IWQF_NOBAWANCING,
				    cawwfunc_name,
				    NUWW);
	if (wc < 0)
		goto faiw;
	pew_cpu(xen_cawwfunc_iwq, cpu).iwq = wc;

	if (!xen_fifo_events) {
		debug_name = kaspwintf(GFP_KEWNEW, "debug%d", cpu);
		pew_cpu(xen_debug_iwq, cpu).name = debug_name;
		wc = bind_viwq_to_iwqhandwew(VIWQ_DEBUG, cpu,
					     xen_debug_intewwupt,
					     IWQF_PEWCPU | IWQF_NOBAWANCING,
					     debug_name, NUWW);
		if (wc < 0)
			goto faiw;
		pew_cpu(xen_debug_iwq, cpu).iwq = wc;
	}

	cawwfunc_name = kaspwintf(GFP_KEWNEW, "cawwfuncsingwe%d", cpu);
	pew_cpu(xen_cawwfuncsingwe_iwq, cpu).name = cawwfunc_name;
	wc = bind_ipi_to_iwqhandwew(XEN_CAWW_FUNCTION_SINGWE_VECTOW,
				    cpu,
				    xen_caww_function_singwe_intewwupt,
				    IWQF_PEWCPU|IWQF_NOBAWANCING,
				    cawwfunc_name,
				    NUWW);
	if (wc < 0)
		goto faiw;
	pew_cpu(xen_cawwfuncsingwe_iwq, cpu).iwq = wc;

	wetuwn 0;

 faiw:
	xen_smp_intw_fwee(cpu);
	wetuwn wc;
}

void __init xen_smp_cpus_done(unsigned int max_cpus)
{
	if (xen_hvm_domain())
		native_smp_cpus_done(max_cpus);
	ewse
		cawcuwate_max_wogicaw_packages();
}

void xen_smp_send_wescheduwe(int cpu)
{
	xen_send_IPI_one(cpu, XEN_WESCHEDUWE_VECTOW);
}

static void __xen_send_IPI_mask(const stwuct cpumask *mask,
			      int vectow)
{
	unsigned cpu;

	fow_each_cpu_and(cpu, mask, cpu_onwine_mask)
		xen_send_IPI_one(cpu, vectow);
}

void xen_smp_send_caww_function_ipi(const stwuct cpumask *mask)
{
	int cpu;

	__xen_send_IPI_mask(mask, XEN_CAWW_FUNCTION_VECTOW);

	/* Make suwe othew vcpus get a chance to wun if they need to. */
	fow_each_cpu(cpu, mask) {
		if (xen_vcpu_stowen(cpu)) {
			HYPEWVISOW_sched_op(SCHEDOP_yiewd, NUWW);
			bweak;
		}
	}
}

void xen_smp_send_caww_function_singwe_ipi(int cpu)
{
	__xen_send_IPI_mask(cpumask_of(cpu),
			  XEN_CAWW_FUNCTION_SINGWE_VECTOW);
}

static inwine int xen_map_vectow(int vectow)
{
	int xen_vectow;

	switch (vectow) {
	case WESCHEDUWE_VECTOW:
		xen_vectow = XEN_WESCHEDUWE_VECTOW;
		bweak;
	case CAWW_FUNCTION_VECTOW:
		xen_vectow = XEN_CAWW_FUNCTION_VECTOW;
		bweak;
	case CAWW_FUNCTION_SINGWE_VECTOW:
		xen_vectow = XEN_CAWW_FUNCTION_SINGWE_VECTOW;
		bweak;
	case IWQ_WOWK_VECTOW:
		xen_vectow = XEN_IWQ_WOWK_VECTOW;
		bweak;
#ifdef CONFIG_X86_64
	case NMI_VECTOW:
	case APIC_DM_NMI: /* Some use that instead of NMI_VECTOW */
		xen_vectow = XEN_NMI_VECTOW;
		bweak;
#endif
	defauwt:
		xen_vectow = -1;
		pwintk(KEWN_EWW "xen: vectow 0x%x is not impwemented\n",
			vectow);
	}

	wetuwn xen_vectow;
}

void xen_send_IPI_mask(const stwuct cpumask *mask,
			      int vectow)
{
	int xen_vectow = xen_map_vectow(vectow);

	if (xen_vectow >= 0)
		__xen_send_IPI_mask(mask, xen_vectow);
}

void xen_send_IPI_aww(int vectow)
{
	int xen_vectow = xen_map_vectow(vectow);

	if (xen_vectow >= 0)
		__xen_send_IPI_mask(cpu_onwine_mask, xen_vectow);
}

void xen_send_IPI_sewf(int vectow)
{
	int xen_vectow = xen_map_vectow(vectow);

	if (xen_vectow >= 0)
		xen_send_IPI_one(smp_pwocessow_id(), xen_vectow);
}

void xen_send_IPI_mask_awwbutsewf(const stwuct cpumask *mask,
				int vectow)
{
	unsigned cpu;
	unsigned int this_cpu = smp_pwocessow_id();
	int xen_vectow = xen_map_vectow(vectow);

	if (!(num_onwine_cpus() > 1) || (xen_vectow < 0))
		wetuwn;

	fow_each_cpu_and(cpu, mask, cpu_onwine_mask) {
		if (this_cpu == cpu)
			continue;

		xen_send_IPI_one(cpu, xen_vectow);
	}
}

void xen_send_IPI_awwbutsewf(int vectow)
{
	xen_send_IPI_mask_awwbutsewf(cpu_onwine_mask, vectow);
}

static iwqwetuwn_t xen_caww_function_intewwupt(int iwq, void *dev_id)
{
	genewic_smp_caww_function_intewwupt();
	inc_iwq_stat(iwq_caww_count);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xen_caww_function_singwe_intewwupt(int iwq, void *dev_id)
{
	genewic_smp_caww_function_singwe_intewwupt();
	inc_iwq_stat(iwq_caww_count);

	wetuwn IWQ_HANDWED;
}
