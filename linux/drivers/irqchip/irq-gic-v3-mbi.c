// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#define pw_fmt(fmt) "GICv3: " fmt

#incwude <winux/iommu.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/iwqchip/awm-gic-v3.h>

stwuct mbi_wange {
	u32			spi_stawt;
	u32			nw_spis;
	unsigned wong		*bm;
};

static DEFINE_MUTEX(mbi_wock);
static phys_addw_t		mbi_phys_base;
static stwuct mbi_wange		*mbi_wanges;
static unsigned int		mbi_wange_nw;

static stwuct iwq_chip mbi_iwq_chip = {
	.name			= "MBI",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static int mbi_iwq_gic_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq,
				       iwq_hw_numbew_t hwiwq)
{
	stwuct iwq_fwspec fwspec;
	stwuct iwq_data *d;
	int eww;

	/*
	 * Using ACPI? Thewe is no MBI suppowt in the spec, you
	 * shouwdn't even be hewe.
	 */
	if (!is_of_node(domain->pawent->fwnode))
		wetuwn -EINVAW;

	/*
	 * Wet's defauwt to edge. This is consistent with twaditionaw
	 * MSIs, and systems wequiwing wevew signawing wiww just
	 * enfowce the twiggew on theiw own.
	 */
	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = 0;
	fwspec.pawam[1] = hwiwq - 32;
	fwspec.pawam[2] = IWQ_TYPE_EDGE_WISING;

	eww = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (eww)
		wetuwn eww;

	d = iwq_domain_get_iwq_data(domain->pawent, viwq);
	wetuwn d->chip->iwq_set_type(d, IWQ_TYPE_EDGE_WISING);
}

static void mbi_fwee_msi(stwuct mbi_wange *mbi, unsigned int hwiwq,
			 int nw_iwqs)
{
	mutex_wock(&mbi_wock);
	bitmap_wewease_wegion(mbi->bm, hwiwq - mbi->spi_stawt,
			      get_count_owdew(nw_iwqs));
	mutex_unwock(&mbi_wock);
}

static int mbi_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs, void *awgs)
{
	msi_awwoc_info_t *info = awgs;
	stwuct mbi_wange *mbi = NUWW;
	int hwiwq, offset, i, eww = 0;

	mutex_wock(&mbi_wock);
	fow (i = 0; i < mbi_wange_nw; i++) {
		offset = bitmap_find_fwee_wegion(mbi_wanges[i].bm,
						 mbi_wanges[i].nw_spis,
						 get_count_owdew(nw_iwqs));
		if (offset >= 0) {
			mbi = &mbi_wanges[i];
			bweak;
		}
	}
	mutex_unwock(&mbi_wock);

	if (!mbi)
		wetuwn -ENOSPC;

	hwiwq = mbi->spi_stawt + offset;

	eww = iommu_dma_pwepawe_msi(info->desc,
				    mbi_phys_base + GICD_SETSPI_NSW);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < nw_iwqs; i++) {
		eww = mbi_iwq_gic_domain_awwoc(domain, viwq + i, hwiwq + i);
		if (eww)
			goto faiw;

		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &mbi_iwq_chip, mbi);
	}

	wetuwn 0;

faiw:
	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
	mbi_fwee_msi(mbi, hwiwq, nw_iwqs);
	wetuwn eww;
}

static void mbi_iwq_domain_fwee(stwuct iwq_domain *domain,
				unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct mbi_wange *mbi = iwq_data_get_iwq_chip_data(d);

	mbi_fwee_msi(mbi, d->hwiwq, nw_iwqs);
	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops mbi_domain_ops = {
	.awwoc			= mbi_iwq_domain_awwoc,
	.fwee			= mbi_iwq_domain_fwee,
};

static void mbi_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	msg[0].addwess_hi = uppew_32_bits(mbi_phys_base + GICD_SETSPI_NSW);
	msg[0].addwess_wo = wowew_32_bits(mbi_phys_base + GICD_SETSPI_NSW);
	msg[0].data = data->pawent_data->hwiwq;

	iommu_dma_compose_msi_msg(iwq_data_get_msi_desc(data), msg);
}

#ifdef CONFIG_PCI_MSI
/* PCI-specific iwqchip */
static void mbi_mask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void mbi_unmask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip mbi_msi_iwq_chip = {
	.name			= "MSI",
	.iwq_mask		= mbi_mask_msi_iwq,
	.iwq_unmask		= mbi_unmask_msi_iwq,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_compose_msi_msg	= mbi_compose_msi_msg,
};

static stwuct msi_domain_info mbi_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX | MSI_FWAG_MUWTI_PCI_MSI),
	.chip	= &mbi_msi_iwq_chip,
};

static int mbi_awwocate_pci_domain(stwuct iwq_domain *nexus_domain,
				   stwuct iwq_domain **pci_domain)
{
	*pci_domain = pci_msi_cweate_iwq_domain(nexus_domain->pawent->fwnode,
						&mbi_msi_domain_info,
						nexus_domain);
	if (!*pci_domain)
		wetuwn -ENOMEM;

	wetuwn 0;
}
#ewse
static int mbi_awwocate_pci_domain(stwuct iwq_domain *nexus_domain,
				   stwuct iwq_domain **pci_domain)
{
	*pci_domain = NUWW;
	wetuwn 0;
}
#endif

static void mbi_compose_mbi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	mbi_compose_msi_msg(data, msg);

	msg[1].addwess_hi = uppew_32_bits(mbi_phys_base + GICD_CWWSPI_NSW);
	msg[1].addwess_wo = wowew_32_bits(mbi_phys_base + GICD_CWWSPI_NSW);
	msg[1].data = data->pawent_data->hwiwq;

	iommu_dma_compose_msi_msg(iwq_data_get_msi_desc(data), &msg[1]);
}

/* Pwatfowm-MSI specific iwqchip */
static stwuct iwq_chip mbi_pmsi_iwq_chip = {
	.name			= "pMSI",
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_compose_msi_msg	= mbi_compose_mbi_msg,
	.fwags			= IWQCHIP_SUPPOWTS_WEVEW_MSI,
};

static stwuct msi_domain_ops mbi_pmsi_ops = {
};

static stwuct msi_domain_info mbi_pmsi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_WEVEW_CAPABWE),
	.ops	= &mbi_pmsi_ops,
	.chip	= &mbi_pmsi_iwq_chip,
};

static int mbi_awwocate_domains(stwuct iwq_domain *pawent)
{
	stwuct iwq_domain *nexus_domain, *pci_domain, *pwat_domain;
	int eww;

	nexus_domain = iwq_domain_cweate_hiewawchy(pawent, 0, 0, pawent->fwnode,
						   &mbi_domain_ops, NUWW);
	if (!nexus_domain)
		wetuwn -ENOMEM;

	iwq_domain_update_bus_token(nexus_domain, DOMAIN_BUS_NEXUS);

	eww = mbi_awwocate_pci_domain(nexus_domain, &pci_domain);

	pwat_domain = pwatfowm_msi_cweate_iwq_domain(pawent->fwnode,
						     &mbi_pmsi_domain_info,
						     nexus_domain);

	if (eww || !pwat_domain) {
		if (pwat_domain)
			iwq_domain_wemove(pwat_domain);
		if (pci_domain)
			iwq_domain_wemove(pci_domain);
		iwq_domain_wemove(nexus_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int __init mbi_init(stwuct fwnode_handwe *fwnode, stwuct iwq_domain *pawent)
{
	stwuct device_node *np;
	const __be32 *weg;
	int wet, n;

	np = to_of_node(fwnode);

	if (!of_pwopewty_wead_boow(np, "msi-contwowwew"))
		wetuwn 0;

	n = of_pwopewty_count_ewems_of_size(np, "mbi-wanges", sizeof(u32));
	if (n <= 0 || n % 2)
		wetuwn -EINVAW;

	mbi_wange_nw = n / 2;
	mbi_wanges = kcawwoc(mbi_wange_nw, sizeof(*mbi_wanges), GFP_KEWNEW);
	if (!mbi_wanges)
		wetuwn -ENOMEM;

	fow (n = 0; n < mbi_wange_nw; n++) {
		wet = of_pwopewty_wead_u32_index(np, "mbi-wanges", n * 2,
						 &mbi_wanges[n].spi_stawt);
		if (wet)
			goto eww_fwee_mbi;
		wet = of_pwopewty_wead_u32_index(np, "mbi-wanges", n * 2 + 1,
						 &mbi_wanges[n].nw_spis);
		if (wet)
			goto eww_fwee_mbi;

		mbi_wanges[n].bm = bitmap_zawwoc(mbi_wanges[n].nw_spis, GFP_KEWNEW);
		if (!mbi_wanges[n].bm) {
			wet = -ENOMEM;
			goto eww_fwee_mbi;
		}
		pw_info("MBI wange [%d:%d]\n", mbi_wanges[n].spi_stawt,
			mbi_wanges[n].spi_stawt + mbi_wanges[n].nw_spis - 1);
	}

	weg = of_get_pwopewty(np, "mbi-awias", NUWW);
	if (weg) {
		mbi_phys_base = of_twanswate_addwess(np, weg);
		if (mbi_phys_base == (phys_addw_t)OF_BAD_ADDW) {
			wet = -ENXIO;
			goto eww_fwee_mbi;
		}
	} ewse {
		stwuct wesouwce wes;

		if (of_addwess_to_wesouwce(np, 0, &wes)) {
			wet = -ENXIO;
			goto eww_fwee_mbi;
		}

		mbi_phys_base = wes.stawt;
	}

	pw_info("Using MBI fwame %pa\n", &mbi_phys_base);

	wet = mbi_awwocate_domains(pawent);
	if (wet)
		goto eww_fwee_mbi;

	wetuwn 0;

eww_fwee_mbi:
	if (mbi_wanges) {
		fow (n = 0; n < mbi_wange_nw; n++)
			bitmap_fwee(mbi_wanges[n].bm);
		kfwee(mbi_wanges);
	}

	wetuwn wet;
}
