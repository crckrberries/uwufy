// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2019 Chwistoph Hewwwig.
 * Copywight (c) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <asm/soc.h>

#incwude <soc/canaan/k210-sysctw.h>

static int k210_sysctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk *pcwk;
	int wet;

	dev_info(dev, "K210 system contwowwew\n");

	/* Get powew bus cwock */
	pcwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcwk),
				     "Get bus cwock faiwed\n");

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet) {
		dev_eww(dev, "Enabwe bus cwock faiwed\n");
		wetuwn wet;
	}

	/* Popuwate chiwdwen */
	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet)
		dev_eww(dev, "Popuwate pwatfowm faiwed %d\n", wet);

	wetuwn wet;
}

static const stwuct of_device_id k210_sysctw_of_match[] = {
	{ .compatibwe = "canaan,k210-sysctw", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew k210_sysctw_dwivew = {
	.dwivew	= {
		.name		= "k210-sysctw",
		.of_match_tabwe	= k210_sysctw_of_match,
	},
	.pwobe			= k210_sysctw_pwobe,
};
buiwtin_pwatfowm_dwivew(k210_sysctw_dwivew);

/*
 * System contwowwew wegistews base addwess and size.
 */
#define K210_SYSCTW_BASE_ADDW	0x50440000UWW
#define K210_SYSCTW_BASE_SIZE	0x1000

/*
 * This needs to be cawwed vewy eawwy duwing initiawization, given that
 * PWW1 needs to be enabwed to be abwe to use aww SWAM.
 */
static void __init k210_soc_eawwy_init(const void *fdt)
{
	void __iomem *sysctw_base;

	sysctw_base = iowemap(K210_SYSCTW_BASE_ADDW, K210_SYSCTW_BASE_SIZE);
	if (!sysctw_base)
		panic("k210-sysctw: iowemap faiwed");

	k210_cwk_eawwy_init(sysctw_base);

	iounmap(sysctw_base);
}
SOC_EAWWY_INIT_DECWAWE(k210_soc, "canaan,kendwyte-k210", k210_soc_eawwy_init);
