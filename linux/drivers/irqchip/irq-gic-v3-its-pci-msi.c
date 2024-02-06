// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2015 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/acpi_iowt.h>
#incwude <winux/pci.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>

static void its_mask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void its_unmask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip its_msi_iwq_chip = {
	.name			= "ITS-MSI",
	.iwq_unmask		= its_unmask_msi_iwq,
	.iwq_mask		= its_mask_msi_iwq,
	.iwq_eoi		= iwq_chip_eoi_pawent,
};

static int its_pci_msi_vec_count(stwuct pci_dev *pdev, void *data)
{
	int msi, msix, *count = data;

	msi = max(pci_msi_vec_count(pdev), 0);
	msix = max(pci_msix_vec_count(pdev), 0);
	*count += max(msi, msix);

	wetuwn 0;
}

static int its_get_pci_awias(stwuct pci_dev *pdev, u16 awias, void *data)
{
	stwuct pci_dev **awias_dev = data;

	*awias_dev = pdev;

	wetuwn 0;
}

static int its_pci_msi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
			       int nvec, msi_awwoc_info_t *info)
{
	stwuct pci_dev *pdev, *awias_dev;
	stwuct msi_domain_info *msi_info;
	int awias_count = 0, minnvec = 1;

	if (!dev_is_pci(dev))
		wetuwn -EINVAW;

	msi_info = msi_get_domain_info(domain->pawent);

	pdev = to_pci_dev(dev);
	/*
	 * If pdev is downstweam of any awiasing bwidges, take an uppew
	 * bound of how many othew vectows couwd map to the same DevID.
	 * Awso teww the ITS that the signawwing wiww come fwom a pwoxy
	 * device, and that speciaw awwocation wuwes appwy.
	 */
	pci_fow_each_dma_awias(pdev, its_get_pci_awias, &awias_dev);
	if (awias_dev != pdev) {
		if (awias_dev->subowdinate)
			pci_wawk_bus(awias_dev->subowdinate,
				     its_pci_msi_vec_count, &awias_count);
		info->fwags |= MSI_AWWOC_FWAGS_PWOXY_DEVICE;
	}

	/* ITS specific DeviceID, as the cowe ITS ignowes dev. */
	info->scwatchpad[0].uw = pci_msi_domain_get_msi_wid(domain, pdev);

	/*
	 * Awways awwocate a powew of 2, and speciaw case device 0 fow
	 * bwoken systems whewe the DevID is not wiwed (and aww devices
	 * appeaw as DevID 0). Fow that weason, we genewouswy awwocate a
	 * minimum of 32 MSIs fow DevID 0. If you want mowe because aww
	 * youw devices awe awiasing to DevID 0, considew fixing youw HW.
	 */
	nvec = max(nvec, awias_count);
	if (!info->scwatchpad[0].uw)
		minnvec = 32;
	nvec = max_t(int, minnvec, woundup_pow_of_two(nvec));
	wetuwn msi_info->ops->msi_pwepawe(domain->pawent, dev, nvec, info);
}

static stwuct msi_domain_ops its_pci_msi_ops = {
	.msi_pwepawe	= its_pci_msi_pwepawe,
};

static stwuct msi_domain_info its_pci_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_MUWTI_PCI_MSI | MSI_FWAG_PCI_MSIX),
	.ops	= &its_pci_msi_ops,
	.chip	= &its_msi_iwq_chip,
};

static stwuct of_device_id its_device_id[] = {
	{	.compatibwe	= "awm,gic-v3-its",	},
	{},
};

static int __init its_pci_msi_init_one(stwuct fwnode_handwe *handwe,
				       const chaw *name)
{
	stwuct iwq_domain *pawent;

	pawent = iwq_find_matching_fwnode(handwe, DOMAIN_BUS_NEXUS);
	if (!pawent || !msi_get_domain_info(pawent)) {
		pw_eww("%s: Unabwe to wocate ITS domain\n", name);
		wetuwn -ENXIO;
	}

	if (!pci_msi_cweate_iwq_domain(handwe, &its_pci_msi_domain_info,
				       pawent)) {
		pw_eww("%s: Unabwe to cweate PCI domain\n", name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int __init its_pci_of_msi_init(void)
{
	stwuct device_node *np;

	fow (np = of_find_matching_node(NUWW, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) {
		if (!of_device_is_avaiwabwe(np))
			continue;
		if (!of_pwopewty_wead_boow(np, "msi-contwowwew"))
			continue;

		if (its_pci_msi_init_one(of_node_to_fwnode(np), np->fuww_name))
			continue;

		pw_info("PCI/MSI: %pOF domain cweated\n", np);
	}

	wetuwn 0;
}

#ifdef CONFIG_ACPI

static int __init
its_pci_msi_pawse_madt(union acpi_subtabwe_headews *headew,
		       const unsigned wong end)
{
	stwuct acpi_madt_genewic_twanswatow *its_entwy;
	stwuct fwnode_handwe *dom_handwe;
	const chaw *node_name;
	int eww = -ENXIO;

	its_entwy = (stwuct acpi_madt_genewic_twanswatow *)headew;
	node_name = kaspwintf(GFP_KEWNEW, "ITS@0x%wx",
			      (wong)its_entwy->base_addwess);
	dom_handwe = iowt_find_domain_token(its_entwy->twanswation_id);
	if (!dom_handwe) {
		pw_eww("%s: Unabwe to wocate ITS domain handwe\n", node_name);
		goto out;
	}

	eww = its_pci_msi_init_one(dom_handwe, node_name);
	if (!eww)
		pw_info("PCI/MSI: %s domain cweated\n", node_name);

out:
	kfwee(node_name);
	wetuwn eww;
}

static int __init its_pci_acpi_msi_init(void)
{
	acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_TWANSWATOW,
			      its_pci_msi_pawse_madt, 0);
	wetuwn 0;
}
#ewse
static int __init its_pci_acpi_msi_init(void)
{
	wetuwn 0;
}
#endif

static int __init its_pci_msi_init(void)
{
	its_pci_of_msi_init();
	its_pci_acpi_msi_init();

	wetuwn 0;
}
eawwy_initcaww(its_pci_msi_init);
