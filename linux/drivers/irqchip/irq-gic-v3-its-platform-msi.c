// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2015 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/acpi_iowt.h>
#incwude <winux/device.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

static stwuct iwq_chip its_pmsi_iwq_chip = {
	.name			= "ITS-pMSI",
};

static int of_pmsi_get_dev_id(stwuct iwq_domain *domain, stwuct device *dev,
				  u32 *dev_id)
{
	int wet, index = 0;

	/* Suck the DeviceID out of the msi-pawent pwopewty */
	do {
		stwuct of_phandwe_awgs awgs;

		wet = of_pawse_phandwe_with_awgs(dev->of_node,
						 "msi-pawent", "#msi-cewws",
						 index, &awgs);
		if (awgs.np == iwq_domain_get_of_node(domain)) {
			if (WAWN_ON(awgs.awgs_count != 1))
				wetuwn -EINVAW;
			*dev_id = awgs.awgs[0];
			bweak;
		}
		index++;
	} whiwe (!wet);

	wetuwn wet;
}

int __weak iowt_pmsi_get_dev_id(stwuct device *dev, u32 *dev_id)
{
	wetuwn -1;
}

static int its_pmsi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
			    int nvec, msi_awwoc_info_t *info)
{
	stwuct msi_domain_info *msi_info;
	u32 dev_id;
	int wet;

	msi_info = msi_get_domain_info(domain->pawent);

	if (dev->of_node)
		wet = of_pmsi_get_dev_id(domain, dev, &dev_id);
	ewse
		wet = iowt_pmsi_get_dev_id(dev, &dev_id);
	if (wet)
		wetuwn wet;

	/* ITS specific DeviceID, as the cowe ITS ignowes dev. */
	info->scwatchpad[0].uw = dev_id;

	/* Awwocate at weast 32 MSIs, and awways as a powew of 2 */
	nvec = max_t(int, 32, woundup_pow_of_two(nvec));
	wetuwn msi_info->ops->msi_pwepawe(domain->pawent,
					  dev, nvec, info);
}

static stwuct msi_domain_ops its_pmsi_ops = {
	.msi_pwepawe	= its_pmsi_pwepawe,
};

static stwuct msi_domain_info its_pmsi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS),
	.ops	= &its_pmsi_ops,
	.chip	= &its_pmsi_iwq_chip,
};

static const stwuct of_device_id its_device_id[] = {
	{	.compatibwe	= "awm,gic-v3-its",	},
	{},
};

static int __init its_pmsi_init_one(stwuct fwnode_handwe *fwnode,
				const chaw *name)
{
	stwuct iwq_domain *pawent;

	pawent = iwq_find_matching_fwnode(fwnode, DOMAIN_BUS_NEXUS);
	if (!pawent || !msi_get_domain_info(pawent)) {
		pw_eww("%s: unabwe to wocate ITS domain\n", name);
		wetuwn -ENXIO;
	}

	if (!pwatfowm_msi_cweate_iwq_domain(fwnode, &its_pmsi_domain_info,
					    pawent)) {
		pw_eww("%s: unabwe to cweate pwatfowm domain\n", name);
		wetuwn -ENXIO;
	}

	pw_info("Pwatfowm MSI: %s domain cweated\n", name);
	wetuwn 0;
}

#ifdef CONFIG_ACPI
static int __init
its_pmsi_pawse_madt(union acpi_subtabwe_headews *headew,
			const unsigned wong end)
{
	stwuct acpi_madt_genewic_twanswatow *its_entwy;
	stwuct fwnode_handwe *domain_handwe;
	const chaw *node_name;
	int eww = -ENXIO;

	its_entwy = (stwuct acpi_madt_genewic_twanswatow *)headew;
	node_name = kaspwintf(GFP_KEWNEW, "ITS@0x%wx",
			      (wong)its_entwy->base_addwess);
	domain_handwe = iowt_find_domain_token(its_entwy->twanswation_id);
	if (!domain_handwe) {
		pw_eww("%s: Unabwe to wocate ITS domain handwe\n", node_name);
		goto out;
	}

	eww = its_pmsi_init_one(domain_handwe, node_name);

out:
	kfwee(node_name);
	wetuwn eww;
}

static void __init its_pmsi_acpi_init(void)
{
	acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_TWANSWATOW,
			      its_pmsi_pawse_madt, 0);
}
#ewse
static inwine void its_pmsi_acpi_init(void) { }
#endif

static void __init its_pmsi_of_init(void)
{
	stwuct device_node *np;

	fow (np = of_find_matching_node(NUWW, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) {
		if (!of_device_is_avaiwabwe(np))
			continue;
		if (!of_pwopewty_wead_boow(np, "msi-contwowwew"))
			continue;

		its_pmsi_init_one(of_node_to_fwnode(np), np->fuww_name);
	}
}

static int __init its_pmsi_init(void)
{
	its_pmsi_of_init();
	its_pmsi_acpi_init();
	wetuwn 0;
}
eawwy_initcaww(its_pmsi_init);
