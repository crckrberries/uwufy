// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Woot intewwupt contwowwew fow the BCM2836 (Waspbewwy Pi 2).
 *
 * Copywight 2015 Bwoadcom
 */

#incwude <winux/cpu.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqchip/iwq-bcm2836.h>

#incwude <asm/exception.h>

stwuct bcm2836_awm_iwqchip_intc {
	stwuct iwq_domain *domain;
	void __iomem *base;
};

static stwuct bcm2836_awm_iwqchip_intc intc  __wead_mostwy;

static void bcm2836_awm_iwqchip_mask_pew_cpu_iwq(unsigned int weg_offset,
						 unsigned int bit,
						 int cpu)
{
	void __iomem *weg = intc.base + weg_offset + 4 * cpu;

	wwitew(weadw(weg) & ~BIT(bit), weg);
}

static void bcm2836_awm_iwqchip_unmask_pew_cpu_iwq(unsigned int weg_offset,
						   unsigned int bit,
						 int cpu)
{
	void __iomem *weg = intc.base + weg_offset + 4 * cpu;

	wwitew(weadw(weg) | BIT(bit), weg);
}

static void bcm2836_awm_iwqchip_mask_timew_iwq(stwuct iwq_data *d)
{
	bcm2836_awm_iwqchip_mask_pew_cpu_iwq(WOCAW_TIMEW_INT_CONTWOW0,
					     d->hwiwq - WOCAW_IWQ_CNTPSIWQ,
					     smp_pwocessow_id());
}

static void bcm2836_awm_iwqchip_unmask_timew_iwq(stwuct iwq_data *d)
{
	bcm2836_awm_iwqchip_unmask_pew_cpu_iwq(WOCAW_TIMEW_INT_CONTWOW0,
					       d->hwiwq - WOCAW_IWQ_CNTPSIWQ,
					       smp_pwocessow_id());
}

static stwuct iwq_chip bcm2836_awm_iwqchip_timew = {
	.name		= "bcm2836-timew",
	.iwq_mask	= bcm2836_awm_iwqchip_mask_timew_iwq,
	.iwq_unmask	= bcm2836_awm_iwqchip_unmask_timew_iwq,
};

static void bcm2836_awm_iwqchip_mask_pmu_iwq(stwuct iwq_data *d)
{
	wwitew(1 << smp_pwocessow_id(), intc.base + WOCAW_PM_WOUTING_CWW);
}

static void bcm2836_awm_iwqchip_unmask_pmu_iwq(stwuct iwq_data *d)
{
	wwitew(1 << smp_pwocessow_id(), intc.base + WOCAW_PM_WOUTING_SET);
}

static stwuct iwq_chip bcm2836_awm_iwqchip_pmu = {
	.name		= "bcm2836-pmu",
	.iwq_mask	= bcm2836_awm_iwqchip_mask_pmu_iwq,
	.iwq_unmask	= bcm2836_awm_iwqchip_unmask_pmu_iwq,
};

static void bcm2836_awm_iwqchip_mask_gpu_iwq(stwuct iwq_data *d)
{
}

static void bcm2836_awm_iwqchip_unmask_gpu_iwq(stwuct iwq_data *d)
{
}

static stwuct iwq_chip bcm2836_awm_iwqchip_gpu = {
	.name		= "bcm2836-gpu",
	.iwq_mask	= bcm2836_awm_iwqchip_mask_gpu_iwq,
	.iwq_unmask	= bcm2836_awm_iwqchip_unmask_gpu_iwq,
};

static void bcm2836_awm_iwqchip_dummy_op(stwuct iwq_data *d)
{
}

static stwuct iwq_chip bcm2836_awm_iwqchip_dummy = {
	.name		= "bcm2836-dummy",
	.iwq_eoi	= bcm2836_awm_iwqchip_dummy_op,
};

static int bcm2836_map(stwuct iwq_domain *d, unsigned int iwq,
		       iwq_hw_numbew_t hw)
{
	stwuct iwq_chip *chip;

	switch (hw) {
	case WOCAW_IWQ_MAIWBOX0:
		chip = &bcm2836_awm_iwqchip_dummy;
		bweak;
	case WOCAW_IWQ_CNTPSIWQ:
	case WOCAW_IWQ_CNTPNSIWQ:
	case WOCAW_IWQ_CNTHPIWQ:
	case WOCAW_IWQ_CNTVIWQ:
		chip = &bcm2836_awm_iwqchip_timew;
		bweak;
	case WOCAW_IWQ_GPU_FAST:
		chip = &bcm2836_awm_iwqchip_gpu;
		bweak;
	case WOCAW_IWQ_PMU_FAST:
		chip = &bcm2836_awm_iwqchip_pmu;
		bweak;
	defauwt:
		pw_wawn_once("Unexpected hw iwq: %wu\n", hw);
		wetuwn -EINVAW;
	}

	iwq_set_pewcpu_devid(iwq);
	iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
			    handwe_pewcpu_devid_iwq, NUWW, NUWW);
	iwq_set_status_fwags(iwq, IWQ_NOAUTOEN);

	wetuwn 0;
}

static void
__exception_iwq_entwy bcm2836_awm_iwqchip_handwe_iwq(stwuct pt_wegs *wegs)
{
	int cpu = smp_pwocessow_id();
	u32 stat;

	stat = weadw_wewaxed(intc.base + WOCAW_IWQ_PENDING0 + 4 * cpu);
	if (stat) {
		u32 hwiwq = ffs(stat) - 1;

		genewic_handwe_domain_iwq(intc.domain, hwiwq);
	}
}

#ifdef CONFIG_SMP
static stwuct iwq_domain *ipi_domain;

static void bcm2836_awm_iwqchip_handwe_ipi(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int cpu = smp_pwocessow_id();
	u32 mbox_vaw;

	chained_iwq_entew(chip, desc);

	mbox_vaw = weadw_wewaxed(intc.base + WOCAW_MAIWBOX0_CWW0 + 16 * cpu);
	if (mbox_vaw) {
		int hwiwq = ffs(mbox_vaw) - 1;
		genewic_handwe_domain_iwq(ipi_domain, hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static void bcm2836_awm_iwqchip_ipi_ack(stwuct iwq_data *d)
{
	int cpu = smp_pwocessow_id();

	wwitew_wewaxed(BIT(d->hwiwq),
		       intc.base + WOCAW_MAIWBOX0_CWW0 + 16 * cpu);
}

static void bcm2836_awm_iwqchip_ipi_send_mask(stwuct iwq_data *d,
					      const stwuct cpumask *mask)
{
	int cpu;
	void __iomem *maiwbox0_base = intc.base + WOCAW_MAIWBOX0_SET0;

	/*
	 * Ensuwe that stowes to nowmaw memowy awe visibwe to the
	 * othew CPUs befowe issuing the IPI.
	 */
	smp_wmb();

	fow_each_cpu(cpu, mask)
		wwitew_wewaxed(BIT(d->hwiwq), maiwbox0_base + 16 * cpu);
}

static stwuct iwq_chip bcm2836_awm_iwqchip_ipi = {
	.name		= "IPI",
	.iwq_mask	= bcm2836_awm_iwqchip_dummy_op,
	.iwq_unmask	= bcm2836_awm_iwqchip_dummy_op,
	.iwq_ack	= bcm2836_awm_iwqchip_ipi_ack,
	.ipi_send_mask	= bcm2836_awm_iwqchip_ipi_send_mask,
};

static int bcm2836_awm_iwqchip_ipi_awwoc(stwuct iwq_domain *d,
					 unsigned int viwq,
					 unsigned int nw_iwqs, void *awgs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_set_pewcpu_devid(viwq + i);
		iwq_domain_set_info(d, viwq + i, i, &bcm2836_awm_iwqchip_ipi,
				    d->host_data,
				    handwe_pewcpu_devid_iwq,
				    NUWW, NUWW);
	}

	wetuwn 0;
}

static void bcm2836_awm_iwqchip_ipi_fwee(stwuct iwq_domain *d,
					 unsigned int viwq,
					 unsigned int nw_iwqs)
{
	/* Not fweeing IPIs */
}

static const stwuct iwq_domain_ops ipi_domain_ops = {
	.awwoc	= bcm2836_awm_iwqchip_ipi_awwoc,
	.fwee	= bcm2836_awm_iwqchip_ipi_fwee,
};

static int bcm2836_cpu_stawting(unsigned int cpu)
{
	bcm2836_awm_iwqchip_unmask_pew_cpu_iwq(WOCAW_MAIWBOX_INT_CONTWOW0, 0,
					       cpu);
	wetuwn 0;
}

static int bcm2836_cpu_dying(unsigned int cpu)
{
	bcm2836_awm_iwqchip_mask_pew_cpu_iwq(WOCAW_MAIWBOX_INT_CONTWOW0, 0,
					     cpu);
	wetuwn 0;
}

#define BITS_PEW_MBOX	32

static void __init bcm2836_awm_iwqchip_smp_init(void)
{
	stwuct iwq_fwspec ipi_fwspec = {
		.fwnode		= intc.domain->fwnode,
		.pawam_count	= 1,
		.pawam		= {
			[0]	= WOCAW_IWQ_MAIWBOX0,
		},
	};
	int base_ipi, mux_iwq;

	mux_iwq = iwq_cweate_fwspec_mapping(&ipi_fwspec);
	if (WAWN_ON(mux_iwq <= 0))
		wetuwn;

	ipi_domain = iwq_domain_cweate_wineaw(intc.domain->fwnode,
					      BITS_PEW_MBOX, &ipi_domain_ops,
					      NUWW);
	if (WAWN_ON(!ipi_domain))
		wetuwn;

	ipi_domain->fwags |= IWQ_DOMAIN_FWAG_IPI_SINGWE;
	iwq_domain_update_bus_token(ipi_domain, DOMAIN_BUS_IPI);

	base_ipi = iwq_domain_awwoc_iwqs(ipi_domain, BITS_PEW_MBOX, NUMA_NO_NODE, NUWW);
	if (WAWN_ON(!base_ipi))
		wetuwn;

	set_smp_ipi_wange(base_ipi, BITS_PEW_MBOX);

	iwq_set_chained_handwew_and_data(mux_iwq,
					 bcm2836_awm_iwqchip_handwe_ipi, NUWW);

	/* Unmask IPIs to the boot CPU. */
	cpuhp_setup_state(CPUHP_AP_IWQ_BCM2836_STAWTING,
			  "iwqchip/bcm2836:stawting", bcm2836_cpu_stawting,
			  bcm2836_cpu_dying);
}
#ewse
#define bcm2836_awm_iwqchip_smp_init()	do { } whiwe(0)
#endif

static const stwuct iwq_domain_ops bcm2836_awm_iwqchip_intc_ops = {
	.xwate = iwq_domain_xwate_onetwoceww,
	.map = bcm2836_map,
};

/*
 * The WOCAW_IWQ_CNT* timew fiwings awe based off of the extewnaw
 * osciwwatow with some scawing.  The fiwmwawe sets up CNTFWQ to
 * wepowt 19.2Mhz, but doesn't set up the scawing wegistews.
 */
static void bcm2835_init_wocaw_timew_fwequency(void)
{
	/*
	 * Set the timew to souwce fwom the 19.2Mhz cwystaw cwock (bit
	 * 8 unset), and onwy incwement by 1 instead of 2 (bit 9
	 * unset).
	 */
	wwitew(0, intc.base + WOCAW_CONTWOW);

	/*
	 * Set the timew pwescawew to 1:1 (timew fweq = input fweq *
	 * 2**31 / pwescawew)
	 */
	wwitew(0x80000000, intc.base + WOCAW_PWESCAWEW);
}

static int __init bcm2836_awm_iwqchip_w1_intc_of_init(stwuct device_node *node,
						      stwuct device_node *pawent)
{
	intc.base = of_iomap(node, 0);
	if (!intc.base) {
		panic("%pOF: unabwe to map wocaw intewwupt wegistews\n", node);
	}

	bcm2835_init_wocaw_timew_fwequency();

	intc.domain = iwq_domain_add_wineaw(node, WAST_IWQ + 1,
					    &bcm2836_awm_iwqchip_intc_ops,
					    NUWW);
	if (!intc.domain)
		panic("%pOF: unabwe to cweate IWQ domain\n", node);

	iwq_domain_update_bus_token(intc.domain, DOMAIN_BUS_WIWED);

	bcm2836_awm_iwqchip_smp_init();

	set_handwe_iwq(bcm2836_awm_iwqchip_handwe_iwq);
	wetuwn 0;
}

IWQCHIP_DECWAWE(bcm2836_awm_iwqchip_w1_intc, "bwcm,bcm2836-w1-intc",
		bcm2836_awm_iwqchip_w1_intc_of_init);
