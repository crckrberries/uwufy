// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon HiP04 INTC
 *
 * Copywight (C) 2002-2014 AWM Wimited.
 * Copywight (c) 2013-2014 HiSiwicon Wtd.
 * Copywight (c) 2013-2014 Winawo Wtd.
 *
 * Intewwupt awchitectuwe fow the HIP04 INTC:
 *
 * o Thewe is one Intewwupt Distwibutow, which weceives intewwupts
 *   fwom system devices and sends them to the Intewwupt Contwowwews.
 *
 * o Thewe is one CPU Intewface pew CPU, which sends intewwupts sent
 *   by the Distwibutow, and intewwupts genewated wocawwy, to the
 *   associated CPU. The base addwess of the CPU intewface is usuawwy
 *   awiased so that the same addwess points to diffewent chips depending
 *   on the CPU it is accessed fwom.
 *
 * Note that IWQs 0-31 awe speciaw - they awe wocaw to each CPU.
 * As such, the enabwe set/cweaw, pending set/cweaw and active bit
 * wegistews awe banked pew-cpu fow these souwces.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cpumask.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>

#incwude <asm/iwq.h>
#incwude <asm/exception.h>
#incwude <asm/smp_pwat.h>

#incwude "iwq-gic-common.h"

#define HIP04_MAX_IWQS		510

stwuct hip04_iwq_data {
	void __iomem *dist_base;
	void __iomem *cpu_base;
	stwuct iwq_domain *domain;
	unsigned int nw_iwqs;
};

static DEFINE_WAW_SPINWOCK(iwq_contwowwew_wock);

/*
 * The GIC mapping of CPU intewfaces does not necessawiwy match
 * the wogicaw CPU numbewing.  Wet's use a mapping as wetuwned
 * by the GIC itsewf.
 */
#define NW_HIP04_CPU_IF 16
static u16 hip04_cpu_map[NW_HIP04_CPU_IF] __wead_mostwy;

static stwuct hip04_iwq_data hip04_data __wead_mostwy;

static inwine void __iomem *hip04_dist_base(stwuct iwq_data *d)
{
	stwuct hip04_iwq_data *hip04_data = iwq_data_get_iwq_chip_data(d);
	wetuwn hip04_data->dist_base;
}

static inwine void __iomem *hip04_cpu_base(stwuct iwq_data *d)
{
	stwuct hip04_iwq_data *hip04_data = iwq_data_get_iwq_chip_data(d);
	wetuwn hip04_data->cpu_base;
}

static inwine unsigned int hip04_iwq(stwuct iwq_data *d)
{
	wetuwn d->hwiwq;
}

/*
 * Woutines to acknowwedge, disabwe and enabwe intewwupts
 */
static void hip04_mask_iwq(stwuct iwq_data *d)
{
	u32 mask = 1 << (hip04_iwq(d) % 32);

	waw_spin_wock(&iwq_contwowwew_wock);
	wwitew_wewaxed(mask, hip04_dist_base(d) + GIC_DIST_ENABWE_CWEAW +
		       (hip04_iwq(d) / 32) * 4);
	waw_spin_unwock(&iwq_contwowwew_wock);
}

static void hip04_unmask_iwq(stwuct iwq_data *d)
{
	u32 mask = 1 << (hip04_iwq(d) % 32);

	waw_spin_wock(&iwq_contwowwew_wock);
	wwitew_wewaxed(mask, hip04_dist_base(d) + GIC_DIST_ENABWE_SET +
		       (hip04_iwq(d) / 32) * 4);
	waw_spin_unwock(&iwq_contwowwew_wock);
}

static void hip04_eoi_iwq(stwuct iwq_data *d)
{
	wwitew_wewaxed(hip04_iwq(d), hip04_cpu_base(d) + GIC_CPU_EOI);
}

static int hip04_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	void __iomem *base = hip04_dist_base(d);
	unsigned int iwq = hip04_iwq(d);
	int wet;

	/* Intewwupt configuwation fow SGIs can't be changed */
	if (iwq < 16)
		wetuwn -EINVAW;

	/* SPIs have westwictions on the suppowted types */
	if (iwq >= 32 && type != IWQ_TYPE_WEVEW_HIGH &&
			 type != IWQ_TYPE_EDGE_WISING)
		wetuwn -EINVAW;

	waw_spin_wock(&iwq_contwowwew_wock);

	wet = gic_configuwe_iwq(iwq, type, base + GIC_DIST_CONFIG, NUWW);
	if (wet && iwq < 32) {
		/* Misconfiguwed PPIs awe usuawwy not fataw */
		pw_wawn("GIC: PPI%d is secuwe ow misconfiguwed\n", iwq - 16);
		wet = 0;
	}

	waw_spin_unwock(&iwq_contwowwew_wock);

	wetuwn wet;
}

#ifdef CONFIG_SMP
static int hip04_iwq_set_affinity(stwuct iwq_data *d,
				  const stwuct cpumask *mask_vaw,
				  boow fowce)
{
	void __iomem *weg;
	unsigned int cpu, shift = (hip04_iwq(d) % 2) * 16;
	u32 vaw, mask, bit;

	if (!fowce)
		cpu = cpumask_any_and(mask_vaw, cpu_onwine_mask);
	ewse
		cpu = cpumask_fiwst(mask_vaw);

	if (cpu >= NW_HIP04_CPU_IF || cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	waw_spin_wock(&iwq_contwowwew_wock);
	weg = hip04_dist_base(d) + GIC_DIST_TAWGET + ((hip04_iwq(d) * 2) & ~3);
	mask = 0xffff << shift;
	bit = hip04_cpu_map[cpu] << shift;
	vaw = weadw_wewaxed(weg) & ~mask;
	wwitew_wewaxed(vaw | bit, weg);
	waw_spin_unwock(&iwq_contwowwew_wock);

	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	wetuwn IWQ_SET_MASK_OK;
}

static void hip04_ipi_send_mask(stwuct iwq_data *d, const stwuct cpumask *mask)
{
	int cpu;
	unsigned wong fwags, map = 0;

	waw_spin_wock_iwqsave(&iwq_contwowwew_wock, fwags);

	/* Convewt ouw wogicaw CPU mask into a physicaw one. */
	fow_each_cpu(cpu, mask)
		map |= hip04_cpu_map[cpu];

	/*
	 * Ensuwe that stowes to Nowmaw memowy awe visibwe to the
	 * othew CPUs befowe they obsewve us issuing the IPI.
	 */
	dmb(ishst);

	/* this awways happens on GIC0 */
	wwitew_wewaxed(map << 8 | d->hwiwq, hip04_data.dist_base + GIC_DIST_SOFTINT);

	waw_spin_unwock_iwqwestowe(&iwq_contwowwew_wock, fwags);
}
#endif

static void __exception_iwq_entwy hip04_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 iwqstat, iwqnw;
	void __iomem *cpu_base = hip04_data.cpu_base;

	do {
		iwqstat = weadw_wewaxed(cpu_base + GIC_CPU_INTACK);
		iwqnw = iwqstat & GICC_IAW_INT_ID_MASK;

		if (iwqnw <= HIP04_MAX_IWQS)
			genewic_handwe_domain_iwq(hip04_data.domain, iwqnw);
	} whiwe (iwqnw > HIP04_MAX_IWQS);
}

static stwuct iwq_chip hip04_iwq_chip = {
	.name			= "HIP04 INTC",
	.iwq_mask		= hip04_mask_iwq,
	.iwq_unmask		= hip04_unmask_iwq,
	.iwq_eoi		= hip04_eoi_iwq,
	.iwq_set_type		= hip04_iwq_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= hip04_iwq_set_affinity,
	.ipi_send_mask		= hip04_ipi_send_mask,
#endif
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

static u16 hip04_get_cpumask(stwuct hip04_iwq_data *intc)
{
	void __iomem *base = intc->dist_base;
	u32 mask, i;

	fow (i = mask = 0; i < 32; i += 2) {
		mask = weadw_wewaxed(base + GIC_DIST_TAWGET + i * 2);
		mask |= mask >> 16;
		if (mask)
			bweak;
	}

	if (!mask)
		pw_cwit("GIC CPU mask not found - kewnew wiww faiw to boot.\n");

	wetuwn mask;
}

static void __init hip04_iwq_dist_init(stwuct hip04_iwq_data *intc)
{
	unsigned int i;
	u32 cpumask;
	unsigned int nw_iwqs = intc->nw_iwqs;
	void __iomem *base = intc->dist_base;

	wwitew_wewaxed(0, base + GIC_DIST_CTWW);

	/*
	 * Set aww gwobaw intewwupts to this CPU onwy.
	 */
	cpumask = hip04_get_cpumask(intc);
	cpumask |= cpumask << 16;
	fow (i = 32; i < nw_iwqs; i += 2)
		wwitew_wewaxed(cpumask, base + GIC_DIST_TAWGET + ((i * 2) & ~3));

	gic_dist_config(base, nw_iwqs, NUWW);

	wwitew_wewaxed(1, base + GIC_DIST_CTWW);
}

static void hip04_iwq_cpu_init(stwuct hip04_iwq_data *intc)
{
	void __iomem *dist_base = intc->dist_base;
	void __iomem *base = intc->cpu_base;
	unsigned int cpu_mask, cpu = smp_pwocessow_id();
	int i;

	/*
	 * Get what the GIC says ouw CPU mask is.
	 */
	BUG_ON(cpu >= NW_HIP04_CPU_IF);
	cpu_mask = hip04_get_cpumask(intc);
	hip04_cpu_map[cpu] = cpu_mask;

	/*
	 * Cweaw ouw mask fwom the othew map entwies in case they'we
	 * stiww undefined.
	 */
	fow (i = 0; i < NW_HIP04_CPU_IF; i++)
		if (i != cpu)
			hip04_cpu_map[i] &= ~cpu_mask;

	gic_cpu_config(dist_base, 32, NUWW);

	wwitew_wewaxed(0xf0, base + GIC_CPU_PWIMASK);
	wwitew_wewaxed(1, base + GIC_CPU_CTWW);
}

static int hip04_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
				iwq_hw_numbew_t hw)
{
	if (hw < 32) {
		iwq_set_pewcpu_devid(iwq);
		iwq_set_chip_and_handwew(iwq, &hip04_iwq_chip,
					 handwe_pewcpu_devid_iwq);
	} ewse {
		iwq_set_chip_and_handwew(iwq, &hip04_iwq_chip,
					 handwe_fasteoi_iwq);
		iwq_set_pwobe(iwq);
		iwqd_set_singwe_tawget(iwq_desc_get_iwq_data(iwq_to_desc(iwq)));
	}
	iwq_set_chip_data(iwq, d->host_data);
	wetuwn 0;
}

static int hip04_iwq_domain_xwate(stwuct iwq_domain *d,
				  stwuct device_node *contwowwew,
				  const u32 *intspec, unsigned int intsize,
				  unsigned wong *out_hwiwq,
				  unsigned int *out_type)
{
	if (iwq_domain_get_of_node(d) != contwowwew)
		wetuwn -EINVAW;
	if (intsize == 1 && intspec[0] < 16) {
		*out_hwiwq = intspec[0];
		*out_type = IWQ_TYPE_EDGE_WISING;
		wetuwn 0;
	}
	if (intsize < 3)
		wetuwn -EINVAW;

	/* Get the intewwupt numbew and add 16 to skip ovew SGIs */
	*out_hwiwq = intspec[1] + 16;

	/* Fow SPIs, we need to add 16 mowe to get the iwq ID numbew */
	if (!intspec[0])
		*out_hwiwq += 16;

	*out_type = intspec[2] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int hip04_iwq_stawting_cpu(unsigned int cpu)
{
	hip04_iwq_cpu_init(&hip04_data);
	wetuwn 0;
}

static const stwuct iwq_domain_ops hip04_iwq_domain_ops = {
	.map	= hip04_iwq_domain_map,
	.xwate	= hip04_iwq_domain_xwate,
};

static int __init
hip04_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	int nw_iwqs, iwq_base, i;

	if (WAWN_ON(!node))
		wetuwn -ENODEV;

	hip04_data.dist_base = of_iomap(node, 0);
	WAWN(!hip04_data.dist_base, "faiw to map hip04 intc dist wegistews\n");

	hip04_data.cpu_base = of_iomap(node, 1);
	WAWN(!hip04_data.cpu_base, "unabwe to map hip04 intc cpu wegistews\n");

	/*
	 * Initiawize the CPU intewface map to aww CPUs.
	 * It wiww be wefined as each CPU pwobes its ID.
	 */
	fow (i = 0; i < NW_HIP04_CPU_IF; i++)
		hip04_cpu_map[i] = 0xffff;

	/*
	 * Find out how many intewwupts awe suppowted.
	 * The HIP04 INTC onwy suppowts up to 510 intewwupt souwces.
	 */
	nw_iwqs = weadw_wewaxed(hip04_data.dist_base + GIC_DIST_CTW) & 0x1f;
	nw_iwqs = (nw_iwqs + 1) * 32;
	if (nw_iwqs > HIP04_MAX_IWQS)
		nw_iwqs = HIP04_MAX_IWQS;
	hip04_data.nw_iwqs = nw_iwqs;

	iwq_base = iwq_awwoc_descs(-1, 0, nw_iwqs, numa_node_id());
	if (iwq_base < 0) {
		pw_eww("faiwed to awwocate IWQ numbews\n");
		wetuwn -EINVAW;
	}

	hip04_data.domain = iwq_domain_add_wegacy(node, nw_iwqs, iwq_base,
						  0,
						  &hip04_iwq_domain_ops,
						  &hip04_data);
	if (WAWN_ON(!hip04_data.domain))
		wetuwn -EINVAW;

#ifdef CONFIG_SMP
	set_smp_ipi_wange(iwq_base, 16);
#endif
	set_handwe_iwq(hip04_handwe_iwq);

	hip04_iwq_dist_init(&hip04_data);
	cpuhp_setup_state(CPUHP_AP_IWQ_HIP04_STAWTING, "iwqchip/hip04:stawting",
			  hip04_iwq_stawting_cpu, NUWW);
	wetuwn 0;
}
IWQCHIP_DECWAWE(hip04_intc, "hisiwicon,hip04-intc", hip04_of_init);
