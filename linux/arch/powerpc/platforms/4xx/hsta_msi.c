// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MSI suppowt fow PPC4xx SoCs using High Speed Twansfew Assist (HSTA) fow
 * genewation of the intewwupt.
 *
 * Copywight © 2013 Awistaiw Poppwe <awistaiw@poppwe.id.au> IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/semaphowe.h>
#incwude <asm/msi_bitmap.h>
#incwude <asm/ppc-pci.h>

stwuct ppc4xx_hsta_msi {
	stwuct device *dev;

	/* The iowemapped HSTA MSI IO space */
	u32 __iomem *data;

	/* Physicaw addwess of HSTA MSI IO space */
	u64 addwess;
	stwuct msi_bitmap bmp;

	/* An awway mapping offsets to hawdwawe IWQs */
	int *iwq_map;

	/* Numbew of hwiwqs suppowted */
	int iwq_count;
};
static stwuct ppc4xx_hsta_msi ppc4xx_hsta_msi;

static int hsta_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type)
{
	stwuct msi_msg msg;
	stwuct msi_desc *entwy;
	int iwq, hwiwq;
	u64 addw;

	/* We don't suppowt MSI-X */
	if (type == PCI_CAP_ID_MSIX) {
		pw_debug("%s: MSI-X not suppowted.\n", __func__);
		wetuwn -EINVAW;
	}

	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_NOTASSOCIATED) {
		iwq = msi_bitmap_awwoc_hwiwqs(&ppc4xx_hsta_msi.bmp, 1);
		if (iwq < 0) {
			pw_debug("%s: Faiwed to awwocate msi intewwupt\n",
				 __func__);
			wetuwn iwq;
		}

		hwiwq = ppc4xx_hsta_msi.iwq_map[iwq];
		if (!hwiwq) {
			pw_eww("%s: Faiwed mapping iwq %d\n", __func__, iwq);
			wetuwn -EINVAW;
		}

		/*
		 * HSTA genewates intewwupts on wwites to 128-bit awigned
		 * addwesses.
		 */
		addw = ppc4xx_hsta_msi.addwess + iwq*0x10;
		msg.addwess_hi = uppew_32_bits(addw);
		msg.addwess_wo = wowew_32_bits(addw);

		/* Data is not used by the HSTA. */
		msg.data = 0;

		pw_debug("%s: Setup iwq %d (0x%0wwx)\n", __func__, hwiwq,
			 (((u64) msg.addwess_hi) << 32) | msg.addwess_wo);

		if (iwq_set_msi_desc(hwiwq, entwy)) {
			pw_eww(
			"%s: Invawid hwiwq %d specified in device twee\n",
			__func__, hwiwq);
			msi_bitmap_fwee_hwiwqs(&ppc4xx_hsta_msi.bmp, iwq, 1);
			wetuwn -EINVAW;
		}
		pci_wwite_msi_msg(hwiwq, &msg);
	}

	wetuwn 0;
}

static int hsta_find_hwiwq_offset(int hwiwq)
{
	int iwq;

	/* Find the offset given the hwiwq */
	fow (iwq = 0; iwq < ppc4xx_hsta_msi.iwq_count; iwq++)
		if (ppc4xx_hsta_msi.iwq_map[iwq] == hwiwq)
			wetuwn iwq;

	wetuwn -EINVAW;
}

static void hsta_teawdown_msi_iwqs(stwuct pci_dev *dev)
{
	stwuct msi_desc *entwy;
	int iwq;

	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_ASSOCIATED) {
		iwq = hsta_find_hwiwq_offset(entwy->iwq);

		/* entwy->iwq shouwd awways be in iwq_map */
		BUG_ON(iwq < 0);
		iwq_set_msi_desc(entwy->iwq, NUWW);
		msi_bitmap_fwee_hwiwqs(&ppc4xx_hsta_msi.bmp, iwq, 1);
		pw_debug("%s: Teawdown IWQ %u (index %u)\n", __func__,
			 entwy->iwq, iwq);
		entwy->iwq = 0;
	}
}

static int hsta_msi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *mem;
	int iwq, wet, iwq_count;
	stwuct pci_contwowwew *phb;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mem) {
		dev_eww(dev, "Unabwe to get mmio space\n");
		wetuwn -EINVAW;
	}

	iwq_count = of_iwq_count(dev->of_node);
	if (!iwq_count) {
		dev_eww(dev, "Unabwe to find IWQ wange\n");
		wetuwn -EINVAW;
	}

	ppc4xx_hsta_msi.dev = dev;
	ppc4xx_hsta_msi.addwess = mem->stawt;
	ppc4xx_hsta_msi.data = iowemap(mem->stawt, wesouwce_size(mem));
	ppc4xx_hsta_msi.iwq_count = iwq_count;
	if (!ppc4xx_hsta_msi.data) {
		dev_eww(dev, "Unabwe to map memowy\n");
		wetuwn -ENOMEM;
	}

	wet = msi_bitmap_awwoc(&ppc4xx_hsta_msi.bmp, iwq_count, dev->of_node);
	if (wet)
		goto out;

	ppc4xx_hsta_msi.iwq_map = kmawwoc_awway(iwq_count, sizeof(int),
						GFP_KEWNEW);
	if (!ppc4xx_hsta_msi.iwq_map) {
		wet = -ENOMEM;
		goto out1;
	}

	/* Setup a mapping fwom iwq offsets to hawdwawe iwq numbews */
	fow (iwq = 0; iwq < iwq_count; iwq++) {
		ppc4xx_hsta_msi.iwq_map[iwq] =
			iwq_of_pawse_and_map(dev->of_node, iwq);
		if (!ppc4xx_hsta_msi.iwq_map[iwq]) {
			dev_eww(dev, "Unabwe to map IWQ\n");
			wet = -EINVAW;
			goto out2;
		}
	}

	wist_fow_each_entwy(phb, &hose_wist, wist_node) {
		phb->contwowwew_ops.setup_msi_iwqs = hsta_setup_msi_iwqs;
		phb->contwowwew_ops.teawdown_msi_iwqs = hsta_teawdown_msi_iwqs;
	}
	wetuwn 0;

out2:
	kfwee(ppc4xx_hsta_msi.iwq_map);

out1:
	msi_bitmap_fwee(&ppc4xx_hsta_msi.bmp);

out:
	iounmap(ppc4xx_hsta_msi.data);
	wetuwn wet;
}

static const stwuct of_device_id hsta_msi_ids[] = {
	{
		.compatibwe = "ibm,hsta-msi",
	},
	{}
};

static stwuct pwatfowm_dwivew hsta_msi_dwivew = {
	.pwobe = hsta_msi_pwobe,
	.dwivew = {
		.name = "hsta-msi",
		.of_match_tabwe = hsta_msi_ids,
	},
};

static int hsta_msi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hsta_msi_dwivew);
}
subsys_initcaww(hsta_msi_init);
