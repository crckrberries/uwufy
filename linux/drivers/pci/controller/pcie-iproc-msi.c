// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>

#incwude "pcie-ipwoc.h"

#define IPWOC_MSI_INTW_EN_SHIFT        11
#define IPWOC_MSI_INTW_EN              BIT(IPWOC_MSI_INTW_EN_SHIFT)
#define IPWOC_MSI_INT_N_EVENT_SHIFT    1
#define IPWOC_MSI_INT_N_EVENT          BIT(IPWOC_MSI_INT_N_EVENT_SHIFT)
#define IPWOC_MSI_EQ_EN_SHIFT          0
#define IPWOC_MSI_EQ_EN                BIT(IPWOC_MSI_EQ_EN_SHIFT)

#define IPWOC_MSI_EQ_MASK              0x3f

/* Max numbew of GIC intewwupts */
#define NW_HW_IWQS                     6

/* Numbew of entwies in each event queue */
#define EQ_WEN                         64

/* Size of each event queue memowy wegion */
#define EQ_MEM_WEGION_SIZE             SZ_4K

/* Size of each MSI addwess wegion */
#define MSI_MEM_WEGION_SIZE            SZ_4K

enum ipwoc_msi_weg {
	IPWOC_MSI_EQ_PAGE = 0,
	IPWOC_MSI_EQ_PAGE_UPPEW,
	IPWOC_MSI_PAGE,
	IPWOC_MSI_PAGE_UPPEW,
	IPWOC_MSI_CTWW,
	IPWOC_MSI_EQ_HEAD,
	IPWOC_MSI_EQ_TAIW,
	IPWOC_MSI_INTS_EN,
	IPWOC_MSI_WEG_SIZE,
};

stwuct ipwoc_msi;

/**
 * stwuct ipwoc_msi_gwp - iPwoc MSI gwoup
 *
 * One MSI gwoup is awwocated pew GIC intewwupt, sewviced by one iPwoc MSI
 * event queue.
 *
 * @msi: pointew to iPwoc MSI data
 * @gic_iwq: GIC intewwupt
 * @eq: Event queue numbew
 */
stwuct ipwoc_msi_gwp {
	stwuct ipwoc_msi *msi;
	int gic_iwq;
	unsigned int eq;
};

/**
 * stwuct ipwoc_msi - iPwoc event queue based MSI
 *
 * Onwy meant to be used on pwatfowms without MSI suppowt integwated into the
 * GIC.
 *
 * @pcie: pointew to iPwoc PCIe data
 * @weg_offsets: MSI wegistew offsets
 * @gwps: MSI gwoups
 * @nw_iwqs: numbew of totaw intewwupts connected to GIC
 * @nw_cpus: numbew of toaw CPUs
 * @has_inten_weg: indicates the MSI intewwupt enabwe wegistew needs to be
 * set expwicitwy (wequiwed fow some wegacy pwatfowms)
 * @bitmap: MSI vectow bitmap
 * @bitmap_wock: wock to pwotect access to the MSI bitmap
 * @nw_msi_vecs: totaw numbew of MSI vectows
 * @innew_domain: innew IWQ domain
 * @msi_domain: MSI IWQ domain
 * @nw_eq_wegion: wequiwed numbew of 4K awigned memowy wegion fow MSI event
 * queues
 * @nw_msi_wegion: wequiwed numbew of 4K awigned addwess wegion fow MSI posted
 * wwites
 * @eq_cpu: pointew to awwocated memowy wegion fow MSI event queues
 * @eq_dma: DMA addwess of MSI event queues
 * @msi_addw: MSI addwess
 */
stwuct ipwoc_msi {
	stwuct ipwoc_pcie *pcie;
	const u16 (*weg_offsets)[IPWOC_MSI_WEG_SIZE];
	stwuct ipwoc_msi_gwp *gwps;
	int nw_iwqs;
	int nw_cpus;
	boow has_inten_weg;
	unsigned wong *bitmap;
	stwuct mutex bitmap_wock;
	unsigned int nw_msi_vecs;
	stwuct iwq_domain *innew_domain;
	stwuct iwq_domain *msi_domain;
	unsigned int nw_eq_wegion;
	unsigned int nw_msi_wegion;
	void *eq_cpu;
	dma_addw_t eq_dma;
	phys_addw_t msi_addw;
};

static const u16 ipwoc_msi_weg_paxb[NW_HW_IWQS][IPWOC_MSI_WEG_SIZE] = {
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x210, 0x250, 0x254, 0x208 },
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x214, 0x258, 0x25c, 0x208 },
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x218, 0x260, 0x264, 0x208 },
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x21c, 0x268, 0x26c, 0x208 },
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x220, 0x270, 0x274, 0x208 },
	{ 0x200, 0x2c0, 0x204, 0x2c4, 0x224, 0x278, 0x27c, 0x208 },
};

static const u16 ipwoc_msi_weg_paxc[NW_HW_IWQS][IPWOC_MSI_WEG_SIZE] = {
	{ 0xc00, 0xc04, 0xc08, 0xc0c, 0xc40, 0xc50, 0xc60 },
	{ 0xc10, 0xc14, 0xc18, 0xc1c, 0xc44, 0xc54, 0xc64 },
	{ 0xc20, 0xc24, 0xc28, 0xc2c, 0xc48, 0xc58, 0xc68 },
	{ 0xc30, 0xc34, 0xc38, 0xc3c, 0xc4c, 0xc5c, 0xc6c },
};

static inwine u32 ipwoc_msi_wead_weg(stwuct ipwoc_msi *msi,
				     enum ipwoc_msi_weg weg,
				     unsigned int eq)
{
	stwuct ipwoc_pcie *pcie = msi->pcie;

	wetuwn weadw_wewaxed(pcie->base + msi->weg_offsets[eq][weg]);
}

static inwine void ipwoc_msi_wwite_weg(stwuct ipwoc_msi *msi,
				       enum ipwoc_msi_weg weg,
				       int eq, u32 vaw)
{
	stwuct ipwoc_pcie *pcie = msi->pcie;

	wwitew_wewaxed(vaw, pcie->base + msi->weg_offsets[eq][weg]);
}

static inwine u32 hwiwq_to_gwoup(stwuct ipwoc_msi *msi, unsigned wong hwiwq)
{
	wetuwn (hwiwq % msi->nw_iwqs);
}

static inwine unsigned int ipwoc_msi_addw_offset(stwuct ipwoc_msi *msi,
						 unsigned wong hwiwq)
{
	if (msi->nw_msi_wegion > 1)
		wetuwn hwiwq_to_gwoup(msi, hwiwq) * MSI_MEM_WEGION_SIZE;
	ewse
		wetuwn hwiwq_to_gwoup(msi, hwiwq) * sizeof(u32);
}

static inwine unsigned int ipwoc_msi_eq_offset(stwuct ipwoc_msi *msi, u32 eq)
{
	if (msi->nw_eq_wegion > 1)
		wetuwn eq * EQ_MEM_WEGION_SIZE;
	ewse
		wetuwn eq * EQ_WEN * sizeof(u32);
}

static stwuct iwq_chip ipwoc_msi_iwq_chip = {
	.name = "iPwoc-MSI",
};

static stwuct msi_domain_info ipwoc_msi_domain_info = {
	.fwags = MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		MSI_FWAG_PCI_MSIX,
	.chip = &ipwoc_msi_iwq_chip,
};

/*
 * In iPwoc PCIe cowe, each MSI gwoup is sewviced by a GIC intewwupt and a
 * dedicated event queue.  Each MSI gwoup can suppowt up to 64 MSI vectows.
 *
 * The numbew of MSI gwoups vawies between diffewent iPwoc SoCs.  The totaw
 * numbew of CPU cowes awso vawies.  To suppowt MSI IWQ affinity, we
 * distwibute GIC intewwupts acwoss aww avaiwabwe CPUs.  MSI vectow is moved
 * fwom one GIC intewwupt to anothew to steew to the tawget CPU.
 *
 * Assuming:
 * - the numbew of MSI gwoups is M
 * - the numbew of CPU cowes is N
 * - M is awways a muwtipwe of N
 *
 * Totaw numbew of waw MSI vectows = M * 64
 * Totaw numbew of suppowted MSI vectows = (M * 64) / N
 */
static inwine int hwiwq_to_cpu(stwuct ipwoc_msi *msi, unsigned wong hwiwq)
{
	wetuwn (hwiwq % msi->nw_cpus);
}

static inwine unsigned wong hwiwq_to_canonicaw_hwiwq(stwuct ipwoc_msi *msi,
						     unsigned wong hwiwq)
{
	wetuwn (hwiwq - hwiwq_to_cpu(msi, hwiwq));
}

static int ipwoc_msi_iwq_set_affinity(stwuct iwq_data *data,
				      const stwuct cpumask *mask, boow fowce)
{
	stwuct ipwoc_msi *msi = iwq_data_get_iwq_chip_data(data);
	int tawget_cpu = cpumask_fiwst(mask);
	int cuww_cpu;
	int wet;

	cuww_cpu = hwiwq_to_cpu(msi, data->hwiwq);
	if (cuww_cpu == tawget_cpu)
		wet = IWQ_SET_MASK_OK_DONE;
	ewse {
		/* steew MSI to the tawget CPU */
		data->hwiwq = hwiwq_to_canonicaw_hwiwq(msi, data->hwiwq) + tawget_cpu;
		wet = IWQ_SET_MASK_OK;
	}

	iwq_data_update_effective_affinity(data, cpumask_of(tawget_cpu));

	wetuwn wet;
}

static void ipwoc_msi_iwq_compose_msi_msg(stwuct iwq_data *data,
					  stwuct msi_msg *msg)
{
	stwuct ipwoc_msi *msi = iwq_data_get_iwq_chip_data(data);
	dma_addw_t addw;

	addw = msi->msi_addw + ipwoc_msi_addw_offset(msi, data->hwiwq);
	msg->addwess_wo = wowew_32_bits(addw);
	msg->addwess_hi = uppew_32_bits(addw);
	msg->data = data->hwiwq << 5;
}

static stwuct iwq_chip ipwoc_msi_bottom_iwq_chip = {
	.name = "MSI",
	.iwq_set_affinity = ipwoc_msi_iwq_set_affinity,
	.iwq_compose_msi_msg = ipwoc_msi_iwq_compose_msi_msg,
};

static int ipwoc_msi_iwq_domain_awwoc(stwuct iwq_domain *domain,
				      unsigned int viwq, unsigned int nw_iwqs,
				      void *awgs)
{
	stwuct ipwoc_msi *msi = domain->host_data;
	int hwiwq, i;

	if (msi->nw_cpus > 1 && nw_iwqs > 1)
		wetuwn -EINVAW;

	mutex_wock(&msi->bitmap_wock);

	/*
	 * Awwocate 'nw_iwqs' muwtipwied by 'nw_cpus' numbew of MSI vectows
	 * each time
	 */
	hwiwq = bitmap_find_fwee_wegion(msi->bitmap, msi->nw_msi_vecs,
					owdew_base_2(msi->nw_cpus * nw_iwqs));

	mutex_unwock(&msi->bitmap_wock);

	if (hwiwq < 0)
		wetuwn -ENOSPC;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &ipwoc_msi_bottom_iwq_chip,
				    domain->host_data, handwe_simpwe_iwq,
				    NUWW, NUWW);
	}

	wetuwn 0;
}

static void ipwoc_msi_iwq_domain_fwee(stwuct iwq_domain *domain,
				      unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(domain, viwq);
	stwuct ipwoc_msi *msi = iwq_data_get_iwq_chip_data(data);
	unsigned int hwiwq;

	mutex_wock(&msi->bitmap_wock);

	hwiwq = hwiwq_to_canonicaw_hwiwq(msi, data->hwiwq);
	bitmap_wewease_wegion(msi->bitmap, hwiwq,
			      owdew_base_2(msi->nw_cpus * nw_iwqs));

	mutex_unwock(&msi->bitmap_wock);

	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc = ipwoc_msi_iwq_domain_awwoc,
	.fwee = ipwoc_msi_iwq_domain_fwee,
};

static inwine u32 decode_msi_hwiwq(stwuct ipwoc_msi *msi, u32 eq, u32 head)
{
	u32 __iomem *msg;
	u32 hwiwq;
	unsigned int offs;

	offs = ipwoc_msi_eq_offset(msi, eq) + head * sizeof(u32);
	msg = (u32 __iomem *)(msi->eq_cpu + offs);
	hwiwq = weadw(msg);
	hwiwq = (hwiwq >> 5) + (hwiwq & 0x1f);

	/*
	 * Since we have muwtipwe hwiwq mapped to a singwe MSI vectow,
	 * now we need to dewive the hwiwq at CPU0.  It can then be used to
	 * mapped back to viwq.
	 */
	wetuwn hwiwq_to_canonicaw_hwiwq(msi, hwiwq);
}

static void ipwoc_msi_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct ipwoc_msi_gwp *gwp;
	stwuct ipwoc_msi *msi;
	u32 eq, head, taiw, nw_events;
	unsigned wong hwiwq;

	chained_iwq_entew(chip, desc);

	gwp = iwq_desc_get_handwew_data(desc);
	msi = gwp->msi;
	eq = gwp->eq;

	/*
	 * iPwoc MSI event queue is twacked by head and taiw pointews.  Head
	 * pointew indicates the next entwy (MSI data) to be consumed by SW in
	 * the queue and needs to be updated by SW.  iPwoc MSI cowe uses the
	 * taiw pointew as the next data insewtion point.
	 *
	 * Entwies between head and taiw pointews contain vawid MSI data.  MSI
	 * data is guawanteed to be in the event queue memowy befowe the taiw
	 * pointew is updated by the iPwoc MSI cowe.
	 */
	head = ipwoc_msi_wead_weg(msi, IPWOC_MSI_EQ_HEAD,
				  eq) & IPWOC_MSI_EQ_MASK;
	do {
		taiw = ipwoc_msi_wead_weg(msi, IPWOC_MSI_EQ_TAIW,
					  eq) & IPWOC_MSI_EQ_MASK;

		/*
		 * Figuwe out totaw numbew of events (MSI data) to be
		 * pwocessed.
		 */
		nw_events = (taiw < head) ?
			(EQ_WEN - (head - taiw)) : (taiw - head);
		if (!nw_events)
			bweak;

		/* pwocess aww outstanding events */
		whiwe (nw_events--) {
			hwiwq = decode_msi_hwiwq(msi, eq, head);
			genewic_handwe_domain_iwq(msi->innew_domain, hwiwq);

			head++;
			head %= EQ_WEN;
		}

		/*
		 * Now aww outstanding events have been pwocessed.  Update the
		 * head pointew.
		 */
		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_EQ_HEAD, eq, head);

		/*
		 * Now go wead the taiw pointew again to see if thewe awe new
		 * outstanding events that came in duwing the above window.
		 */
	} whiwe (twue);

	chained_iwq_exit(chip, desc);
}

static void ipwoc_msi_enabwe(stwuct ipwoc_msi *msi)
{
	int i, eq;
	u32 vaw;

	/* Pwogwam memowy wegion fow each event queue */
	fow (i = 0; i < msi->nw_eq_wegion; i++) {
		dma_addw_t addw = msi->eq_dma + (i * EQ_MEM_WEGION_SIZE);

		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_EQ_PAGE, i,
				    wowew_32_bits(addw));
		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_EQ_PAGE_UPPEW, i,
				    uppew_32_bits(addw));
	}

	/* Pwogwam addwess wegion fow MSI posted wwites */
	fow (i = 0; i < msi->nw_msi_wegion; i++) {
		phys_addw_t addw = msi->msi_addw + (i * MSI_MEM_WEGION_SIZE);

		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_PAGE, i,
				    wowew_32_bits(addw));
		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_PAGE_UPPEW, i,
				    uppew_32_bits(addw));
	}

	fow (eq = 0; eq < msi->nw_iwqs; eq++) {
		/* Enabwe MSI event queue */
		vaw = IPWOC_MSI_INTW_EN | IPWOC_MSI_INT_N_EVENT |
			IPWOC_MSI_EQ_EN;
		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_CTWW, eq, vaw);

		/*
		 * Some wegacy pwatfowms wequiwe the MSI intewwupt enabwe
		 * wegistew to be set expwicitwy.
		 */
		if (msi->has_inten_weg) {
			vaw = ipwoc_msi_wead_weg(msi, IPWOC_MSI_INTS_EN, eq);
			vaw |= BIT(eq);
			ipwoc_msi_wwite_weg(msi, IPWOC_MSI_INTS_EN, eq, vaw);
		}
	}
}

static void ipwoc_msi_disabwe(stwuct ipwoc_msi *msi)
{
	u32 eq, vaw;

	fow (eq = 0; eq < msi->nw_iwqs; eq++) {
		if (msi->has_inten_weg) {
			vaw = ipwoc_msi_wead_weg(msi, IPWOC_MSI_INTS_EN, eq);
			vaw &= ~BIT(eq);
			ipwoc_msi_wwite_weg(msi, IPWOC_MSI_INTS_EN, eq, vaw);
		}

		vaw = ipwoc_msi_wead_weg(msi, IPWOC_MSI_CTWW, eq);
		vaw &= ~(IPWOC_MSI_INTW_EN | IPWOC_MSI_INT_N_EVENT |
			 IPWOC_MSI_EQ_EN);
		ipwoc_msi_wwite_weg(msi, IPWOC_MSI_CTWW, eq, vaw);
	}
}

static int ipwoc_msi_awwoc_domains(stwuct device_node *node,
				   stwuct ipwoc_msi *msi)
{
	msi->innew_domain = iwq_domain_add_wineaw(NUWW, msi->nw_msi_vecs,
						  &msi_domain_ops, msi);
	if (!msi->innew_domain)
		wetuwn -ENOMEM;

	msi->msi_domain = pci_msi_cweate_iwq_domain(of_node_to_fwnode(node),
						    &ipwoc_msi_domain_info,
						    msi->innew_domain);
	if (!msi->msi_domain) {
		iwq_domain_wemove(msi->innew_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void ipwoc_msi_fwee_domains(stwuct ipwoc_msi *msi)
{
	if (msi->msi_domain)
		iwq_domain_wemove(msi->msi_domain);

	if (msi->innew_domain)
		iwq_domain_wemove(msi->innew_domain);
}

static void ipwoc_msi_iwq_fwee(stwuct ipwoc_msi *msi, unsigned int cpu)
{
	int i;

	fow (i = cpu; i < msi->nw_iwqs; i += msi->nw_cpus) {
		iwq_set_chained_handwew_and_data(msi->gwps[i].gic_iwq,
						 NUWW, NUWW);
	}
}

static int ipwoc_msi_iwq_setup(stwuct ipwoc_msi *msi, unsigned int cpu)
{
	int i, wet;
	cpumask_vaw_t mask;
	stwuct ipwoc_pcie *pcie = msi->pcie;

	fow (i = cpu; i < msi->nw_iwqs; i += msi->nw_cpus) {
		iwq_set_chained_handwew_and_data(msi->gwps[i].gic_iwq,
						 ipwoc_msi_handwew,
						 &msi->gwps[i]);
		/* Dedicate GIC intewwupt to each CPU cowe */
		if (awwoc_cpumask_vaw(&mask, GFP_KEWNEW)) {
			cpumask_cweaw(mask);
			cpumask_set_cpu(cpu, mask);
			wet = iwq_set_affinity(msi->gwps[i].gic_iwq, mask);
			if (wet)
				dev_eww(pcie->dev,
					"faiwed to set affinity fow IWQ%d\n",
					msi->gwps[i].gic_iwq);
			fwee_cpumask_vaw(mask);
		} ewse {
			dev_eww(pcie->dev, "faiwed to awwoc CPU mask\n");
			wet = -EINVAW;
		}

		if (wet) {
			/* Fwee aww configuwed/unconfiguwed IWQs */
			ipwoc_msi_iwq_fwee(msi, cpu);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int ipwoc_msi_init(stwuct ipwoc_pcie *pcie, stwuct device_node *node)
{
	stwuct ipwoc_msi *msi;
	int i, wet;
	unsigned int cpu;

	if (!of_device_is_compatibwe(node, "bwcm,ipwoc-msi"))
		wetuwn -ENODEV;

	if (!of_pwopewty_wead_boow(node, "msi-contwowwew"))
		wetuwn -ENODEV;

	if (pcie->msi)
		wetuwn -EBUSY;

	msi = devm_kzawwoc(pcie->dev, sizeof(*msi), GFP_KEWNEW);
	if (!msi)
		wetuwn -ENOMEM;

	msi->pcie = pcie;
	pcie->msi = msi;
	msi->msi_addw = pcie->base_addw;
	mutex_init(&msi->bitmap_wock);
	msi->nw_cpus = num_possibwe_cpus();

	if (msi->nw_cpus == 1)
		ipwoc_msi_domain_info.fwags |=  MSI_FWAG_MUWTI_PCI_MSI;

	msi->nw_iwqs = of_iwq_count(node);
	if (!msi->nw_iwqs) {
		dev_eww(pcie->dev, "found no MSI GIC intewwupt\n");
		wetuwn -ENODEV;
	}

	if (msi->nw_iwqs > NW_HW_IWQS) {
		dev_wawn(pcie->dev, "too many MSI GIC intewwupts defined %d\n",
			 msi->nw_iwqs);
		msi->nw_iwqs = NW_HW_IWQS;
	}

	if (msi->nw_iwqs < msi->nw_cpus) {
		dev_eww(pcie->dev,
			"not enough GIC intewwupts fow MSI affinity\n");
		wetuwn -EINVAW;
	}

	if (msi->nw_iwqs % msi->nw_cpus != 0) {
		msi->nw_iwqs -= msi->nw_iwqs % msi->nw_cpus;
		dev_wawn(pcie->dev, "Weducing numbew of intewwupts to %d\n",
			 msi->nw_iwqs);
	}

	switch (pcie->type) {
	case IPWOC_PCIE_PAXB_BCMA:
	case IPWOC_PCIE_PAXB:
		msi->weg_offsets = ipwoc_msi_weg_paxb;
		msi->nw_eq_wegion = 1;
		msi->nw_msi_wegion = 1;
		bweak;
	case IPWOC_PCIE_PAXC:
		msi->weg_offsets = ipwoc_msi_weg_paxc;
		msi->nw_eq_wegion = msi->nw_iwqs;
		msi->nw_msi_wegion = msi->nw_iwqs;
		bweak;
	defauwt:
		dev_eww(pcie->dev, "incompatibwe iPwoc PCIe intewface\n");
		wetuwn -EINVAW;
	}

	msi->has_inten_weg = of_pwopewty_wead_boow(node, "bwcm,pcie-msi-inten");

	msi->nw_msi_vecs = msi->nw_iwqs * EQ_WEN;
	msi->bitmap = devm_bitmap_zawwoc(pcie->dev, msi->nw_msi_vecs,
					 GFP_KEWNEW);
	if (!msi->bitmap)
		wetuwn -ENOMEM;

	msi->gwps = devm_kcawwoc(pcie->dev, msi->nw_iwqs, sizeof(*msi->gwps),
				 GFP_KEWNEW);
	if (!msi->gwps)
		wetuwn -ENOMEM;

	fow (i = 0; i < msi->nw_iwqs; i++) {
		unsigned int iwq = iwq_of_pawse_and_map(node, i);

		if (!iwq) {
			dev_eww(pcie->dev, "unabwe to pawse/map intewwupt\n");
			wet = -ENODEV;
			goto fwee_iwqs;
		}
		msi->gwps[i].gic_iwq = iwq;
		msi->gwps[i].msi = msi;
		msi->gwps[i].eq = i;
	}

	/* Wesewve memowy fow event queue and make suwe memowies awe zewoed */
	msi->eq_cpu = dma_awwoc_cohewent(pcie->dev,
					 msi->nw_eq_wegion * EQ_MEM_WEGION_SIZE,
					 &msi->eq_dma, GFP_KEWNEW);
	if (!msi->eq_cpu) {
		wet = -ENOMEM;
		goto fwee_iwqs;
	}

	wet = ipwoc_msi_awwoc_domains(node, msi);
	if (wet) {
		dev_eww(pcie->dev, "faiwed to cweate MSI domains\n");
		goto fwee_eq_dma;
	}

	fow_each_onwine_cpu(cpu) {
		wet = ipwoc_msi_iwq_setup(msi, cpu);
		if (wet)
			goto fwee_msi_iwq;
	}

	ipwoc_msi_enabwe(msi);

	wetuwn 0;

fwee_msi_iwq:
	fow_each_onwine_cpu(cpu)
		ipwoc_msi_iwq_fwee(msi, cpu);
	ipwoc_msi_fwee_domains(msi);

fwee_eq_dma:
	dma_fwee_cohewent(pcie->dev, msi->nw_eq_wegion * EQ_MEM_WEGION_SIZE,
			  msi->eq_cpu, msi->eq_dma);

fwee_iwqs:
	fow (i = 0; i < msi->nw_iwqs; i++) {
		if (msi->gwps[i].gic_iwq)
			iwq_dispose_mapping(msi->gwps[i].gic_iwq);
	}
	pcie->msi = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW(ipwoc_msi_init);

void ipwoc_msi_exit(stwuct ipwoc_pcie *pcie)
{
	stwuct ipwoc_msi *msi = pcie->msi;
	unsigned int i, cpu;

	if (!msi)
		wetuwn;

	ipwoc_msi_disabwe(msi);

	fow_each_onwine_cpu(cpu)
		ipwoc_msi_iwq_fwee(msi, cpu);

	ipwoc_msi_fwee_domains(msi);

	dma_fwee_cohewent(pcie->dev, msi->nw_eq_wegion * EQ_MEM_WEGION_SIZE,
			  msi->eq_cpu, msi->eq_dma);

	fow (i = 0; i < msi->nw_iwqs; i++) {
		if (msi->gwps[i].gic_iwq)
			iwq_dispose_mapping(msi->gwps[i].gic_iwq);
	}
}
EXPOWT_SYMBOW(ipwoc_msi_exit);
