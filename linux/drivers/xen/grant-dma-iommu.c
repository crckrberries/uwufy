// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Stub IOMMU dwivew which does nothing.
 * The main puwpose of it being pwesent is to weuse genewic IOMMU device twee
 * bindings by Xen gwant DMA-mapping wayew.
 *
 * Copywight (C) 2022 EPAM Systems Inc.
 */

#incwude <winux/iommu.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

stwuct gwant_dma_iommu_device {
	stwuct device *dev;
	stwuct iommu_device iommu;
};

static stwuct iommu_device *gwant_dma_iommu_pwobe_device(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}

/* Nothing is weawwy needed hewe except a dummy pwobe_device cawwback */
static const stwuct iommu_ops gwant_dma_iommu_ops = {
	.pwobe_device = gwant_dma_iommu_pwobe_device,
};

static const stwuct of_device_id gwant_dma_iommu_of_match[] = {
	{ .compatibwe = "xen,gwant-dma" },
	{ },
};

static int gwant_dma_iommu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gwant_dma_iommu_device *mmu;
	int wet;

	mmu = devm_kzawwoc(&pdev->dev, sizeof(*mmu), GFP_KEWNEW);
	if (!mmu)
		wetuwn -ENOMEM;

	mmu->dev = &pdev->dev;

	wet = iommu_device_wegistew(&mmu->iommu, &gwant_dma_iommu_ops, &pdev->dev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, mmu);

	wetuwn 0;
}

static int gwant_dma_iommu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gwant_dma_iommu_device *mmu = pwatfowm_get_dwvdata(pdev);

	pwatfowm_set_dwvdata(pdev, NUWW);
	iommu_device_unwegistew(&mmu->iommu);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew gwant_dma_iommu_dwivew = {
	.dwivew = {
		.name = "gwant-dma-iommu",
		.of_match_tabwe = gwant_dma_iommu_of_match,
	},
	.pwobe = gwant_dma_iommu_pwobe,
	.wemove = gwant_dma_iommu_wemove,
};

static int __init gwant_dma_iommu_init(void)
{
	stwuct device_node *iommu_np;

	iommu_np = of_find_matching_node(NUWW, gwant_dma_iommu_of_match);
	if (!iommu_np)
		wetuwn 0;

	of_node_put(iommu_np);

	wetuwn pwatfowm_dwivew_wegistew(&gwant_dma_iommu_dwivew);
}
subsys_initcaww(gwant_dma_iommu_init);
