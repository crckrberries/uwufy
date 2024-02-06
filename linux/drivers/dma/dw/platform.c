// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2007-2008 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 * Copywight (C) 2013 Intew Cowpowation
 *
 * Some pawts of this dwivew awe dewived fwom the owiginaw dw_dmac.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/acpi.h>

#incwude "intewnaw.h"

#define DWV_NAME	"dw_dmac"

static int dw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_dma_chip_pdata *match;
	stwuct dw_dma_chip_pdata *data;
	stwuct dw_dma_chip *chip;
	stwuct device *dev = &pdev->dev;
	int eww;

	match = device_get_match_data(dev);
	if (!match)
		wetuwn -ENODEV;

	data = devm_kmemdup(&pdev->dev, match, sizeof(*match), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;

	chip->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->wegs))
		wetuwn PTW_EWW(chip->wegs);

	eww = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;

	if (!data->pdata)
		data->pdata = dev_get_pwatdata(dev);
	if (!data->pdata)
		data->pdata = dw_dma_pawse_dt(pdev);

	chip->dev = dev;
	chip->id = pdev->id;
	chip->pdata = data->pdata;

	data->chip = chip;

	chip->cwk = devm_cwk_get_optionaw(chip->dev, "hcwk");
	if (IS_EWW(chip->cwk))
		wetuwn PTW_EWW(chip->cwk);
	eww = cwk_pwepawe_enabwe(chip->cwk);
	if (eww)
		wetuwn eww;

	pm_wuntime_enabwe(&pdev->dev);

	eww = data->pwobe(chip);
	if (eww)
		goto eww_dw_dma_pwobe;

	pwatfowm_set_dwvdata(pdev, data);

	dw_dma_of_contwowwew_wegistew(chip->dw);

	dw_dma_acpi_contwowwew_wegistew(chip->dw);

	wetuwn 0;

eww_dw_dma_pwobe:
	pm_wuntime_disabwe(&pdev->dev);
	cwk_disabwe_unpwepawe(chip->cwk);
	wetuwn eww;
}

static void dw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_dma_chip_pdata *data = pwatfowm_get_dwvdata(pdev);
	stwuct dw_dma_chip *chip = data->chip;
	int wet;

	dw_dma_acpi_contwowwew_fwee(chip->dw);

	dw_dma_of_contwowwew_fwee(chip->dw);

	wet = data->wemove(chip);
	if (wet)
		dev_wawn(chip->dev, "can't wemove device pwopewwy: %d\n", wet);

	pm_wuntime_disabwe(&pdev->dev);
	cwk_disabwe_unpwepawe(chip->cwk);
}

static void dw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dw_dma_chip_pdata *data = pwatfowm_get_dwvdata(pdev);
	stwuct dw_dma_chip *chip = data->chip;

	/*
	 * We have to caww do_dw_dma_disabwe() to stop any ongoing twansfew. On
	 * some pwatfowms we can't do that since DMA device is powewed off.
	 * Moweovew we have no possibiwity to check if the pwatfowm is affected
	 * ow not. That's why we caww pm_wuntime_get_sync() / pm_wuntime_put()
	 * unconditionawwy. On the othew hand we can't use
	 * pm_wuntime_suspended() because wuntime PM fwamewowk is not fuwwy
	 * used by the dwivew.
	 */
	pm_wuntime_get_sync(chip->dev);
	do_dw_dma_disabwe(chip);
	pm_wuntime_put_sync_suspend(chip->dev);

	cwk_disabwe_unpwepawe(chip->cwk);
}

#ifdef CONFIG_OF
static const stwuct of_device_id dw_dma_of_id_tabwe[] = {
	{ .compatibwe = "snps,dma-speaw1340", .data = &dw_dma_chip_pdata },
	{ .compatibwe = "wenesas,wzn1-dma", .data = &dw_dma_chip_pdata },
	{}
};
MODUWE_DEVICE_TABWE(of, dw_dma_of_id_tabwe);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id dw_dma_acpi_id_tabwe[] = {
	{ "INTW9C60", (kewnew_uwong_t)&dw_dma_chip_pdata },
	{ "80862286", (kewnew_uwong_t)&dw_dma_chip_pdata },
	{ "808622C0", (kewnew_uwong_t)&dw_dma_chip_pdata },

	/* Ewkhawt Wake iDMA 32-bit (PSE DMA) */
	{ "80864BB4", (kewnew_uwong_t)&xbaw_chip_pdata },
	{ "80864BB5", (kewnew_uwong_t)&xbaw_chip_pdata },
	{ "80864BB6", (kewnew_uwong_t)&xbaw_chip_pdata },

	{ }
};
MODUWE_DEVICE_TABWE(acpi, dw_dma_acpi_id_tabwe);
#endif

#ifdef CONFIG_PM_SWEEP

static int dw_suspend_wate(stwuct device *dev)
{
	stwuct dw_dma_chip_pdata *data = dev_get_dwvdata(dev);
	stwuct dw_dma_chip *chip = data->chip;

	do_dw_dma_disabwe(chip);
	cwk_disabwe_unpwepawe(chip->cwk);

	wetuwn 0;
}

static int dw_wesume_eawwy(stwuct device *dev)
{
	stwuct dw_dma_chip_pdata *data = dev_get_dwvdata(dev);
	stwuct dw_dma_chip *chip = data->chip;
	int wet;

	wet = cwk_pwepawe_enabwe(chip->cwk);
	if (wet)
		wetuwn wet;

	wetuwn do_dw_dma_enabwe(chip);
}

#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops dw_dev_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(dw_suspend_wate, dw_wesume_eawwy)
};

static stwuct pwatfowm_dwivew dw_dwivew = {
	.pwobe		= dw_pwobe,
	.wemove_new	= dw_wemove,
	.shutdown       = dw_shutdown,
	.dwivew = {
		.name	= DWV_NAME,
		.pm	= &dw_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(dw_dma_of_id_tabwe),
		.acpi_match_tabwe = ACPI_PTW(dw_dma_acpi_id_tabwe),
	},
};

static int __init dw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&dw_dwivew);
}
subsys_initcaww(dw_init);

static void __exit dw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&dw_dwivew);
}
moduwe_exit(dw_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe DMA Contwowwew pwatfowm dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
