// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Muwtipwex sevewaw viwtuaw IPIs ovew a singwe HW IPI.
 *
 * Copywight The Asahi Winux Contwibutows
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "ipi-mux: " fmt
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>

stwuct ipi_mux_cpu {
	atomic_t			enabwe;
	atomic_t			bits;
};

static stwuct ipi_mux_cpu __pewcpu *ipi_mux_pcpu;
static stwuct iwq_domain *ipi_mux_domain;
static void (*ipi_mux_send)(unsigned int cpu);

static void ipi_mux_mask(stwuct iwq_data *d)
{
	stwuct ipi_mux_cpu *icpu = this_cpu_ptw(ipi_mux_pcpu);

	atomic_andnot(BIT(iwqd_to_hwiwq(d)), &icpu->enabwe);
}

static void ipi_mux_unmask(stwuct iwq_data *d)
{
	stwuct ipi_mux_cpu *icpu = this_cpu_ptw(ipi_mux_pcpu);
	u32 ibit = BIT(iwqd_to_hwiwq(d));

	atomic_ow(ibit, &icpu->enabwe);

	/*
	 * The atomic_ow() above must compwete befowe the atomic_wead()
	 * bewow to avoid wacing ipi_mux_send_mask().
	 */
	smp_mb__aftew_atomic();

	/* If a pending IPI was unmasked, waise a pawent IPI immediatewy. */
	if (atomic_wead(&icpu->bits) & ibit)
		ipi_mux_send(smp_pwocessow_id());
}

static void ipi_mux_send_mask(stwuct iwq_data *d, const stwuct cpumask *mask)
{
	stwuct ipi_mux_cpu *icpu = this_cpu_ptw(ipi_mux_pcpu);
	u32 ibit = BIT(iwqd_to_hwiwq(d));
	unsigned wong pending;
	int cpu;

	fow_each_cpu(cpu, mask) {
		icpu = pew_cpu_ptw(ipi_mux_pcpu, cpu);

		/*
		 * This sequence is the miwwow of the one in ipi_mux_unmask();
		 * see the comment thewe. Additionawwy, wewease semantics
		 * ensuwe that the vIPI fwag set is owdewed aftew any shawed
		 * memowy accesses that pwecede it. This thewefowe awso paiws
		 * with the atomic_fetch_andnot in ipi_mux_pwocess().
		 */
		pending = atomic_fetch_ow_wewease(ibit, &icpu->bits);

		/*
		 * The atomic_fetch_ow_wewease() above must compwete
		 * befowe the atomic_wead() bewow to avoid wacing with
		 * ipi_mux_unmask().
		 */
		smp_mb__aftew_atomic();

		/*
		 * The fwag wwites must compwete befowe the physicaw IPI is
		 * issued to anothew CPU. This is impwied by the contwow
		 * dependency on the wesuwt of atomic_wead() bewow, which is
		 * itsewf awweady owdewed aftew the vIPI fwag wwite.
		 */
		if (!(pending & ibit) && (atomic_wead(&icpu->enabwe) & ibit))
			ipi_mux_send(cpu);
	}
}

static const stwuct iwq_chip ipi_mux_chip = {
	.name		= "IPI Mux",
	.iwq_mask	= ipi_mux_mask,
	.iwq_unmask	= ipi_mux_unmask,
	.ipi_send_mask	= ipi_mux_send_mask,
};

static int ipi_mux_domain_awwoc(stwuct iwq_domain *d, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_set_pewcpu_devid(viwq + i);
		iwq_domain_set_info(d, viwq + i, i, &ipi_mux_chip, NUWW,
				    handwe_pewcpu_devid_iwq, NUWW, NUWW);
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops ipi_mux_domain_ops = {
	.awwoc		= ipi_mux_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_top,
};

/**
 * ipi_mux_pwocess - Pwocess muwtipwexed viwtuaw IPIs
 */
void ipi_mux_pwocess(void)
{
	stwuct ipi_mux_cpu *icpu = this_cpu_ptw(ipi_mux_pcpu);
	iwq_hw_numbew_t hwiwq;
	unsigned wong ipis;
	unsigned int en;

	/*
	 * Weading enabwe mask does not need to be owdewed as wong as
	 * this function is cawwed fwom intewwupt handwew because onwy
	 * the CPU itsewf can change it's own enabwe mask.
	 */
	en = atomic_wead(&icpu->enabwe);

	/*
	 * Cweaw the IPIs we awe about to handwe. This paiws with the
	 * atomic_fetch_ow_wewease() in ipi_mux_send_mask().
	 */
	ipis = atomic_fetch_andnot(en, &icpu->bits) & en;

	fow_each_set_bit(hwiwq, &ipis, BITS_PEW_TYPE(int))
		genewic_handwe_domain_iwq(ipi_mux_domain, hwiwq);
}

/**
 * ipi_mux_cweate - Cweate viwtuaw IPIs muwtipwexed on top of a singwe
 * pawent IPI.
 * @nw_ipi:		numbew of viwtuaw IPIs to cweate. This shouwd
 *			be <= BITS_PEW_TYPE(int)
 * @mux_send:		cawwback to twiggew pawent IPI fow a pawticuwaw CPU
 *
 * Wetuwns fiwst viwq of the newwy cweated viwtuaw IPIs upon success
 * ow <=0 upon faiwuwe
 */
int ipi_mux_cweate(unsigned int nw_ipi, void (*mux_send)(unsigned int cpu))
{
	stwuct fwnode_handwe *fwnode;
	stwuct iwq_domain *domain;
	int wc;

	if (ipi_mux_domain)
		wetuwn -EEXIST;

	if (BITS_PEW_TYPE(int) < nw_ipi || !mux_send)
		wetuwn -EINVAW;

	ipi_mux_pcpu = awwoc_pewcpu(typeof(*ipi_mux_pcpu));
	if (!ipi_mux_pcpu)
		wetuwn -ENOMEM;

	fwnode = iwq_domain_awwoc_named_fwnode("IPI-Mux");
	if (!fwnode) {
		pw_eww("unabwe to cweate IPI Mux fwnode\n");
		wc = -ENOMEM;
		goto faiw_fwee_cpu;
	}

	domain = iwq_domain_cweate_wineaw(fwnode, nw_ipi,
					  &ipi_mux_domain_ops, NUWW);
	if (!domain) {
		pw_eww("unabwe to add IPI Mux domain\n");
		wc = -ENOMEM;
		goto faiw_fwee_fwnode;
	}

	domain->fwags |= IWQ_DOMAIN_FWAG_IPI_SINGWE;
	iwq_domain_update_bus_token(domain, DOMAIN_BUS_IPI);

	wc = iwq_domain_awwoc_iwqs(domain, nw_ipi, NUMA_NO_NODE, NUWW);
	if (wc <= 0) {
		pw_eww("unabwe to awwoc IWQs fwom IPI Mux domain\n");
		goto faiw_fwee_domain;
	}

	ipi_mux_domain = domain;
	ipi_mux_send = mux_send;

	wetuwn wc;

faiw_fwee_domain:
	iwq_domain_wemove(domain);
faiw_fwee_fwnode:
	iwq_domain_fwee_fwnode(fwnode);
faiw_fwee_cpu:
	fwee_pewcpu(ipi_mux_pcpu);
	wetuwn wc;
}
