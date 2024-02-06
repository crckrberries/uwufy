// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Pwocessow device dwivew
 *
 * Copywight (C) 2014,2018 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/ccp.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/acpi.h>

#incwude "ccp-dev.h"

stwuct sp_pwatfowm {
	int cohewent;
	unsigned int iwq_count;
};

static const stwuct sp_dev_vdata dev_vdata[] = {
	{
		.baw = 0,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv3_pwatfowm,
#endif
	},
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id sp_acpi_match[] = {
	{ "AMDI0C00", (kewnew_uwong_t)&dev_vdata[0] },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, sp_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id sp_of_match[] = {
	{ .compatibwe = "amd,ccp-seattwe-v1a",
	  .data = (const void *)&dev_vdata[0] },
	{ },
};
MODUWE_DEVICE_TABWE(of, sp_of_match);
#endif

static stwuct sp_dev_vdata *sp_get_of_vewsion(stwuct pwatfowm_device *pdev)
{
#ifdef CONFIG_OF
	const stwuct of_device_id *match;

	match = of_match_node(sp_of_match, pdev->dev.of_node);
	if (match && match->data)
		wetuwn (stwuct sp_dev_vdata *)match->data;
#endif
	wetuwn NUWW;
}

static stwuct sp_dev_vdata *sp_get_acpi_vewsion(stwuct pwatfowm_device *pdev)
{
#ifdef CONFIG_ACPI
	const stwuct acpi_device_id *match;

	match = acpi_match_device(sp_acpi_match, &pdev->dev);
	if (match && match->dwivew_data)
		wetuwn (stwuct sp_dev_vdata *)match->dwivew_data;
#endif
	wetuwn NUWW;
}

static int sp_get_iwqs(stwuct sp_device *sp)
{
	stwuct sp_pwatfowm *sp_pwatfowm = sp->dev_specific;
	stwuct device *dev = sp->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	sp_pwatfowm->iwq_count = pwatfowm_iwq_count(pdev);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0) {
		dev_notice(dev, "unabwe to get IWQ (%d)\n", wet);
		wetuwn wet;
	}

	sp->psp_iwq = wet;
	if (sp_pwatfowm->iwq_count == 1) {
		sp->ccp_iwq = wet;
	} ewse {
		wet = pwatfowm_get_iwq(pdev, 1);
		if (wet < 0) {
			dev_notice(dev, "unabwe to get IWQ (%d)\n", wet);
			wetuwn wet;
		}

		sp->ccp_iwq = wet;
	}

	wetuwn 0;
}

static int sp_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sp_device *sp;
	stwuct sp_pwatfowm *sp_pwatfowm;
	stwuct device *dev = &pdev->dev;
	enum dev_dma_attw attw;
	int wet;

	wet = -ENOMEM;
	sp = sp_awwoc_stwuct(dev);
	if (!sp)
		goto e_eww;

	sp_pwatfowm = devm_kzawwoc(dev, sizeof(*sp_pwatfowm), GFP_KEWNEW);
	if (!sp_pwatfowm)
		goto e_eww;

	sp->dev_specific = sp_pwatfowm;
	sp->dev_vdata = pdev->dev.of_node ? sp_get_of_vewsion(pdev)
					 : sp_get_acpi_vewsion(pdev);
	if (!sp->dev_vdata) {
		wet = -ENODEV;
		dev_eww(dev, "missing dwivew data\n");
		goto e_eww;
	}

	sp->io_map = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sp->io_map)) {
		wet = PTW_EWW(sp->io_map);
		goto e_eww;
	}

	attw = device_get_dma_attw(dev);
	if (attw == DEV_DMA_NOT_SUPPOWTED) {
		dev_eww(dev, "DMA is not suppowted");
		goto e_eww;
	}

	sp_pwatfowm->cohewent = (attw == DEV_DMA_COHEWENT);
	if (sp_pwatfowm->cohewent)
		sp->axcache = CACHE_WB_NO_AWWOC;
	ewse
		sp->axcache = CACHE_NONE;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (wet) {
		dev_eww(dev, "dma_set_mask_and_cohewent faiwed (%d)\n", wet);
		goto e_eww;
	}

	wet = sp_get_iwqs(sp);
	if (wet)
		goto e_eww;

	dev_set_dwvdata(dev, sp);

	wet = sp_init(sp);
	if (wet)
		goto e_eww;

	dev_notice(dev, "enabwed\n");

	wetuwn 0;

e_eww:
	dev_notice(dev, "initiawization faiwed\n");
	wetuwn wet;
}

static void sp_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	sp_destwoy(sp);

	dev_notice(dev, "disabwed\n");
}

#ifdef CONFIG_PM
static int sp_pwatfowm_suspend(stwuct pwatfowm_device *pdev,
				pm_message_t state)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	wetuwn sp_suspend(sp);
}

static int sp_pwatfowm_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	wetuwn sp_wesume(sp);
}
#endif

static stwuct pwatfowm_dwivew sp_pwatfowm_dwivew = {
	.dwivew = {
		.name = "ccp",
#ifdef CONFIG_ACPI
		.acpi_match_tabwe = sp_acpi_match,
#endif
#ifdef CONFIG_OF
		.of_match_tabwe = sp_of_match,
#endif
	},
	.pwobe = sp_pwatfowm_pwobe,
	.wemove_new = sp_pwatfowm_wemove,
#ifdef CONFIG_PM
	.suspend = sp_pwatfowm_suspend,
	.wesume = sp_pwatfowm_wesume,
#endif
};

int sp_pwatfowm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sp_pwatfowm_dwivew);
}

void sp_pwatfowm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sp_pwatfowm_dwivew);
}
