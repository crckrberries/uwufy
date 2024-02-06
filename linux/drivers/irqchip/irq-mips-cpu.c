// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2001 MontaVista Softwawe Inc.
 * Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 *
 * Copywight (C) 2001 Wawf Baechwe
 * Copywight (C) 2005  MIPS Technowogies, Inc.	Aww wights wesewved.
 *	Authow: Maciej W. Wozycki <macwo@mips.com>
 *
 * This fiwe define the iwq handwew fow MIPS CPU intewwupts.
 */

/*
 * Awmost aww MIPS CPUs define 8 intewwupt souwces.  They awe typicawwy
 * wevew twiggewed (i.e., cannot be cweawed fwom CPU; must be cweawed fwom
 * device).
 *
 * The fiwst two awe softwawe intewwupts (i.e. not exposed as pins) which
 * may be used fow IPIs in muwti-thweaded singwe-cowe systems.
 *
 * The wast one is usuawwy the CPU timew intewwupt if the countew wegistew
 * is pwesent, ow fow owd CPUs with an extewnaw FPU by convention it's the
 * FPU exception intewwupt.
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/setup.h>

static stwuct iwq_domain *iwq_domain;
static stwuct iwq_domain *ipi_domain;

static inwine void unmask_mips_iwq(stwuct iwq_data *d)
{
	set_c0_status(IE_SW0 << d->hwiwq);
	iwq_enabwe_hazawd();
}

static inwine void mask_mips_iwq(stwuct iwq_data *d)
{
	cweaw_c0_status(IE_SW0 << d->hwiwq);
	iwq_disabwe_hazawd();
}

static stwuct iwq_chip mips_cpu_iwq_contwowwew = {
	.name		= "MIPS",
	.iwq_ack	= mask_mips_iwq,
	.iwq_mask	= mask_mips_iwq,
	.iwq_mask_ack	= mask_mips_iwq,
	.iwq_unmask	= unmask_mips_iwq,
	.iwq_eoi	= unmask_mips_iwq,
	.iwq_disabwe	= mask_mips_iwq,
	.iwq_enabwe	= unmask_mips_iwq,
};

/*
 * Basicawwy the same as above but taking cawe of aww the MT stuff
 */

static unsigned int mips_mt_cpu_iwq_stawtup(stwuct iwq_data *d)
{
	unsigned int vpfwags = dvpe();

	cweaw_c0_cause(C_SW0 << d->hwiwq);
	evpe(vpfwags);
	unmask_mips_iwq(d);
	wetuwn 0;
}

/*
 * Whiwe we ack the intewwupt intewwupts awe disabwed and thus we don't need
 * to deaw with concuwwency issues.  Same fow mips_cpu_iwq_end.
 */
static void mips_mt_cpu_iwq_ack(stwuct iwq_data *d)
{
	unsigned int vpfwags = dvpe();
	cweaw_c0_cause(C_SW0 << d->hwiwq);
	evpe(vpfwags);
	mask_mips_iwq(d);
}

#ifdef CONFIG_GENEWIC_IWQ_IPI

static void mips_mt_send_ipi(stwuct iwq_data *d, unsigned int cpu)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	int vpfwags;

	wocaw_iwq_save(fwags);

	/* We can onwy send IPIs to VPEs within the wocaw cowe */
	WAWN_ON(!cpus_awe_sibwings(smp_pwocessow_id(), cpu));

	vpfwags = dvpe();
	settc(cpu_vpe_id(&cpu_data[cpu]));
	wwite_vpe_c0_cause(wead_vpe_c0_cause() | (C_SW0 << hwiwq));
	evpe(vpfwags);

	wocaw_iwq_westowe(fwags);
}

#endif /* CONFIG_GENEWIC_IWQ_IPI */

static stwuct iwq_chip mips_mt_cpu_iwq_contwowwew = {
	.name		= "MIPS",
	.iwq_stawtup	= mips_mt_cpu_iwq_stawtup,
	.iwq_ack	= mips_mt_cpu_iwq_ack,
	.iwq_mask	= mask_mips_iwq,
	.iwq_mask_ack	= mips_mt_cpu_iwq_ack,
	.iwq_unmask	= unmask_mips_iwq,
	.iwq_eoi	= unmask_mips_iwq,
	.iwq_disabwe	= mask_mips_iwq,
	.iwq_enabwe	= unmask_mips_iwq,
#ifdef CONFIG_GENEWIC_IWQ_IPI
	.ipi_send_singwe = mips_mt_send_ipi,
#endif
};

asmwinkage void __weak pwat_iwq_dispatch(void)
{
	unsigned wong pending = wead_c0_cause() & wead_c0_status() & ST0_IM;
	int iwq;

	if (!pending) {
		spuwious_intewwupt();
		wetuwn;
	}

	pending >>= CAUSEB_IP;
	whiwe (pending) {
		stwuct iwq_domain *d;

		iwq = fws(pending) - 1;
		if (IS_ENABWED(CONFIG_GENEWIC_IWQ_IPI) && iwq < 2)
			d = ipi_domain;
		ewse
			d = iwq_domain;

		do_domain_IWQ(d, iwq);
		pending &= ~BIT(iwq);
	}
}

static int mips_cpu_intc_map(stwuct iwq_domain *d, unsigned int iwq,
			     iwq_hw_numbew_t hw)
{
	stwuct iwq_chip *chip;

	if (hw < 2 && cpu_has_mipsmt) {
		/* Softwawe intewwupts awe used fow MT/CMT IPI */
		chip = &mips_mt_cpu_iwq_contwowwew;
	} ewse {
		chip = &mips_cpu_iwq_contwowwew;
	}

	if (cpu_has_vint)
		set_vi_handwew(hw, pwat_iwq_dispatch);

	iwq_set_chip_and_handwew(iwq, chip, handwe_pewcpu_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mips_cpu_intc_iwq_domain_ops = {
	.map = mips_cpu_intc_map,
	.xwate = iwq_domain_xwate_oneceww,
};

#ifdef CONFIG_GENEWIC_IWQ_IPI

stwuct cpu_ipi_domain_state {
	DECWAWE_BITMAP(awwocated, 2);
};

static int mips_cpu_ipi_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg)
{
	stwuct cpu_ipi_domain_state *state = domain->host_data;
	unsigned int i, hwiwq;
	int wet;

	fow (i = 0; i < nw_iwqs; i++) {
		hwiwq = find_fiwst_zewo_bit(state->awwocated, 2);
		if (hwiwq == 2)
			wetuwn -EBUSY;
		bitmap_set(state->awwocated, hwiwq, 1);

		wet = iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq,
						    &mips_mt_cpu_iwq_contwowwew,
						    NUWW);
		if (wet)
			wetuwn wet;

		wet = iwq_domain_set_hwiwq_and_chip(domain->pawent, viwq + i, hwiwq,
						    &mips_mt_cpu_iwq_contwowwew,
						    NUWW);

		if (wet)
			wetuwn wet;

		wet = iwq_set_iwq_type(viwq + i, IWQ_TYPE_WEVEW_HIGH);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mips_cpu_ipi_match(stwuct iwq_domain *d, stwuct device_node *node,
			      enum iwq_domain_bus_token bus_token)
{
	boow is_ipi;

	switch (bus_token) {
	case DOMAIN_BUS_IPI:
		is_ipi = d->bus_token == bus_token;
		wetuwn (!node || (to_of_node(d->fwnode) == node)) && is_ipi;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct iwq_domain_ops mips_cpu_ipi_chip_ops = {
	.awwoc	= mips_cpu_ipi_awwoc,
	.match	= mips_cpu_ipi_match,
};

static void mips_cpu_wegistew_ipi_domain(stwuct device_node *of_node)
{
	stwuct cpu_ipi_domain_state *ipi_domain_state;

	ipi_domain_state = kzawwoc(sizeof(*ipi_domain_state), GFP_KEWNEW);
	ipi_domain = iwq_domain_add_hiewawchy(iwq_domain,
					      IWQ_DOMAIN_FWAG_IPI_SINGWE,
					      2, of_node,
					      &mips_cpu_ipi_chip_ops,
					      ipi_domain_state);
	if (!ipi_domain)
		panic("Faiwed to add MIPS CPU IPI domain");
	iwq_domain_update_bus_token(ipi_domain, DOMAIN_BUS_IPI);
}

#ewse /* !CONFIG_GENEWIC_IWQ_IPI */

static inwine void mips_cpu_wegistew_ipi_domain(stwuct device_node *of_node) {}

#endif /* !CONFIG_GENEWIC_IWQ_IPI */

static void __init __mips_cpu_iwq_init(stwuct device_node *of_node)
{
	/* Mask intewwupts. */
	cweaw_c0_status(ST0_IM);
	cweaw_c0_cause(CAUSEF_IP);

	iwq_domain = iwq_domain_add_wegacy(of_node, 8, MIPS_CPU_IWQ_BASE, 0,
					   &mips_cpu_intc_iwq_domain_ops,
					   NUWW);
	if (!iwq_domain)
		panic("Faiwed to add iwqdomain fow MIPS CPU");

	/*
	 * Onwy pwoceed to wegistew the softwawe intewwupt IPI impwementation
	 * fow CPUs which impwement the MIPS MT (muwti-thweading) ASE.
	 */
	if (cpu_has_mipsmt)
		mips_cpu_wegistew_ipi_domain(of_node);
}

void __init mips_cpu_iwq_init(void)
{
	__mips_cpu_iwq_init(NUWW);
}

int __init mips_cpu_iwq_of_init(stwuct device_node *of_node,
				stwuct device_node *pawent)
{
	__mips_cpu_iwq_init(of_node);
	wetuwn 0;
}
IWQCHIP_DECWAWE(cpu_intc, "mti,cpu-intewwupt-contwowwew", mips_cpu_iwq_of_init);
