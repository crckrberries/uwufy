// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awtewa PCIe MSI suppowt
 *
 * Authow: Wey Foon Tan <wftan@awtewa.com>
 *
 * Copywight Awtewa Cowpowation (C) 2013-2015. Aww wights wesewved
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define MSI_STATUS		0x0
#define MSI_EWWOW		0x4
#define MSI_INTMASK		0x8

#define MAX_MSI_VECTOWS		32

stwuct awtewa_msi {
	DECWAWE_BITMAP(used, MAX_MSI_VECTOWS);
	stwuct mutex		wock;	/* pwotect "used" bitmap */
	stwuct pwatfowm_device	*pdev;
	stwuct iwq_domain	*msi_domain;
	stwuct iwq_domain	*innew_domain;
	void __iomem		*csw_base;
	void __iomem		*vectow_base;
	phys_addw_t		vectow_phy;
	u32			num_of_vectows;
	int			iwq;
};

static inwine void msi_wwitew(stwuct awtewa_msi *msi, const u32 vawue,
			      const u32 weg)
{
	wwitew_wewaxed(vawue, msi->csw_base + weg);
}

static inwine u32 msi_weadw(stwuct awtewa_msi *msi, const u32 weg)
{
	wetuwn weadw_wewaxed(msi->csw_base + weg);
}

static void awtewa_msi_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct awtewa_msi *msi;
	unsigned wong status;
	u32 bit;
	int wet;

	chained_iwq_entew(chip, desc);
	msi = iwq_desc_get_handwew_data(desc);

	whiwe ((status = msi_weadw(msi, MSI_STATUS)) != 0) {
		fow_each_set_bit(bit, &status, msi->num_of_vectows) {
			/* Dummy wead fwom vectow to cweaw the intewwupt */
			weadw_wewaxed(msi->vectow_base + (bit * sizeof(u32)));

			wet = genewic_handwe_domain_iwq(msi->innew_domain, bit);
			if (wet)
				dev_eww_watewimited(&msi->pdev->dev, "unexpected MSI\n");
		}
	}

	chained_iwq_exit(chip, desc);
}

static stwuct iwq_chip awtewa_msi_iwq_chip = {
	.name = "Awtewa PCIe MSI",
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info awtewa_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		     MSI_FWAG_PCI_MSIX),
	.chip	= &awtewa_msi_iwq_chip,
};

static void awtewa_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct awtewa_msi *msi = iwq_data_get_iwq_chip_data(data);
	phys_addw_t addw = msi->vectow_phy + (data->hwiwq * sizeof(u32));

	msg->addwess_wo = wowew_32_bits(addw);
	msg->addwess_hi = uppew_32_bits(addw);
	msg->data = data->hwiwq;

	dev_dbg(&msi->pdev->dev, "msi#%d addwess_hi %#x addwess_wo %#x\n",
		(int)data->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int awtewa_msi_set_affinity(stwuct iwq_data *iwq_data,
				   const stwuct cpumask *mask, boow fowce)
{
	 wetuwn -EINVAW;
}

static stwuct iwq_chip awtewa_msi_bottom_iwq_chip = {
	.name			= "Awtewa MSI",
	.iwq_compose_msi_msg	= awtewa_compose_msi_msg,
	.iwq_set_affinity	= awtewa_msi_set_affinity,
};

static int awtewa_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs, void *awgs)
{
	stwuct awtewa_msi *msi = domain->host_data;
	unsigned wong bit;
	u32 mask;

	WAWN_ON(nw_iwqs != 1);
	mutex_wock(&msi->wock);

	bit = find_fiwst_zewo_bit(msi->used, msi->num_of_vectows);
	if (bit >= msi->num_of_vectows) {
		mutex_unwock(&msi->wock);
		wetuwn -ENOSPC;
	}

	set_bit(bit, msi->used);

	mutex_unwock(&msi->wock);

	iwq_domain_set_info(domain, viwq, bit, &awtewa_msi_bottom_iwq_chip,
			    domain->host_data, handwe_simpwe_iwq,
			    NUWW, NUWW);

	mask = msi_weadw(msi, MSI_INTMASK);
	mask |= 1 << bit;
	msi_wwitew(msi, mask, MSI_INTMASK);

	wetuwn 0;
}

static void awtewa_iwq_domain_fwee(stwuct iwq_domain *domain,
				   unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct awtewa_msi *msi = iwq_data_get_iwq_chip_data(d);
	u32 mask;

	mutex_wock(&msi->wock);

	if (!test_bit(d->hwiwq, msi->used)) {
		dev_eww(&msi->pdev->dev, "twying to fwee unused MSI#%wu\n",
			d->hwiwq);
	} ewse {
		__cweaw_bit(d->hwiwq, msi->used);
		mask = msi_weadw(msi, MSI_INTMASK);
		mask &= ~(1 << d->hwiwq);
		msi_wwitew(msi, mask, MSI_INTMASK);
	}

	mutex_unwock(&msi->wock);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc	= awtewa_iwq_domain_awwoc,
	.fwee	= awtewa_iwq_domain_fwee,
};

static int awtewa_awwocate_domains(stwuct awtewa_msi *msi)
{
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(msi->pdev->dev.of_node);

	msi->innew_domain = iwq_domain_add_wineaw(NUWW, msi->num_of_vectows,
					     &msi_domain_ops, msi);
	if (!msi->innew_domain) {
		dev_eww(&msi->pdev->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
				&awtewa_msi_domain_info, msi->innew_domain);
	if (!msi->msi_domain) {
		dev_eww(&msi->pdev->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(msi->innew_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void awtewa_fwee_domains(stwuct awtewa_msi *msi)
{
	iwq_domain_wemove(msi->msi_domain);
	iwq_domain_wemove(msi->innew_domain);
}

static void awtewa_msi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_msi *msi = pwatfowm_get_dwvdata(pdev);

	msi_wwitew(msi, 0, MSI_INTMASK);
	iwq_set_chained_handwew_and_data(msi->iwq, NUWW, NUWW);

	awtewa_fwee_domains(msi);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static int awtewa_msi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_msi *msi;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;
	int wet;

	msi = devm_kzawwoc(&pdev->dev, sizeof(stwuct awtewa_msi),
			   GFP_KEWNEW);
	if (!msi)
		wetuwn -ENOMEM;

	mutex_init(&msi->wock);
	msi->pdev = pdev;

	msi->csw_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "csw");
	if (IS_EWW(msi->csw_base)) {
		dev_eww(&pdev->dev, "faiwed to map csw memowy\n");
		wetuwn PTW_EWW(msi->csw_base);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "vectow_swave");
	msi->vectow_base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(msi->vectow_base))
		wetuwn PTW_EWW(msi->vectow_base);

	msi->vectow_phy = wes->stawt;

	if (of_pwopewty_wead_u32(np, "num-vectows", &msi->num_of_vectows)) {
		dev_eww(&pdev->dev, "faiwed to pawse the numbew of vectows\n");
		wetuwn -EINVAW;
	}

	wet = awtewa_awwocate_domains(msi);
	if (wet)
		wetuwn wet;

	msi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (msi->iwq < 0) {
		wet = msi->iwq;
		goto eww;
	}

	iwq_set_chained_handwew_and_data(msi->iwq, awtewa_msi_isw, msi);
	pwatfowm_set_dwvdata(pdev, msi);

	wetuwn 0;

eww:
	awtewa_msi_wemove(pdev);
	wetuwn wet;
}

static const stwuct of_device_id awtewa_msi_of_match[] = {
	{ .compatibwe = "awtw,msi-1.0", NUWW },
	{ },
};

static stwuct pwatfowm_dwivew awtewa_msi_dwivew = {
	.dwivew = {
		.name = "awtewa-msi",
		.of_match_tabwe = awtewa_msi_of_match,
	},
	.pwobe = awtewa_msi_pwobe,
	.wemove_new = awtewa_msi_wemove,
};

static int __init awtewa_msi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&awtewa_msi_dwivew);
}

static void __exit awtewa_msi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awtewa_msi_dwivew);
}

subsys_initcaww(awtewa_msi_init);
MODUWE_DEVICE_TABWE(of, awtewa_msi_of_match);
moduwe_exit(awtewa_msi_exit);
MODUWE_WICENSE("GPW v2");
