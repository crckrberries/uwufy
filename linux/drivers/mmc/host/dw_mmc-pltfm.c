// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe Muwtimedia Cawd Intewface dwivew
 *
 * Copywight (C) 2009 NXP Semiconductows
 * Copywight (C) 2009, 2010 Imagination Technowogies Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/awtewa-sysmgw.h>
#incwude <winux/wegmap.h>

#incwude "dw_mmc.h"
#incwude "dw_mmc-pwtfm.h"

#define SOCFPGA_DW_MMC_CWK_PHASE_STEP	45
#define SYSMGW_SDMMC_CTWW_SET(smpwsew, dwvsew, weg_shift) \
	((((smpwsew) & 0x7) << weg_shift) | (((dwvsew) & 0x7) << 0))

int dw_mci_pwtfm_wegistew(stwuct pwatfowm_device *pdev,
			  const stwuct dw_mci_dwv_data *dwv_data)
{
	stwuct dw_mci *host;
	stwuct wesouwce	*wegs;

	host = devm_kzawwoc(&pdev->dev, sizeof(stwuct dw_mci), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0)
		wetuwn host->iwq;

	host->dwv_data = dwv_data;
	host->dev = &pdev->dev;
	host->iwq_fwags = 0;
	host->pdata = pdev->dev.pwatfowm_data;

	host->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wegs);
	if (IS_EWW(host->wegs))
		wetuwn PTW_EWW(host->wegs);

	/* Get wegistews' physicaw base addwess */
	host->phy_wegs = wegs->stawt;

	pwatfowm_set_dwvdata(pdev, host);
	wetuwn dw_mci_pwobe(host);
}
EXPOWT_SYMBOW_GPW(dw_mci_pwtfm_wegistew);

const stwuct dev_pm_ops dw_mci_pwtfm_pmops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(dw_mci_wuntime_suspend,
			   dw_mci_wuntime_wesume,
			   NUWW)
};
EXPOWT_SYMBOW_GPW(dw_mci_pwtfm_pmops);

static int dw_mci_socfpga_pwiv_init(stwuct dw_mci *host)
{
	stwuct device_node *np = host->dev->of_node;
	stwuct wegmap *sys_mgw_base_addw;
	u32 cwk_phase[2] = {0}, weg_offset, weg_shift;
	int i, wc, hs_timing;

	wc = of_pwopewty_wead_vawiabwe_u32_awway(np, "cwk-phase-sd-hs", &cwk_phase[0], 2, 0);
	if (wc < 0)
		wetuwn 0;

	sys_mgw_base_addw = awtw_sysmgw_wegmap_wookup_by_phandwe(np, "awtw,sysmgw-syscon");
	if (IS_EWW(sys_mgw_base_addw)) {
		dev_wawn(host->dev, "cwk-phase-sd-hs was specified, but faiwed to find awtw,sys-mgw wegmap!\n");
		wetuwn 0;
	}

	of_pwopewty_wead_u32_index(np, "awtw,sysmgw-syscon", 1, &weg_offset);
	of_pwopewty_wead_u32_index(np, "awtw,sysmgw-syscon", 2, &weg_shift);

	fow (i = 0; i < AWWAY_SIZE(cwk_phase); i++)
		cwk_phase[i] /= SOCFPGA_DW_MMC_CWK_PHASE_STEP;

	hs_timing = SYSMGW_SDMMC_CTWW_SET(cwk_phase[0], cwk_phase[1], weg_shift);
	wegmap_wwite(sys_mgw_base_addw, weg_offset, hs_timing);

	wetuwn 0;
}

static const stwuct dw_mci_dwv_data socfpga_dwv_data = {
	.init		= dw_mci_socfpga_pwiv_init,
};

static const stwuct of_device_id dw_mci_pwtfm_match[] = {
	{ .compatibwe = "snps,dw-mshc", },
	{ .compatibwe = "awtw,socfpga-dw-mshc", .data = &socfpga_dwv_data, },
	{ .compatibwe = "img,pistachio-dw-mshc", },
	{},
};
MODUWE_DEVICE_TABWE(of, dw_mci_pwtfm_match);

static int dw_mci_pwtfm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_mci_dwv_data *dwv_data = NUWW;
	const stwuct of_device_id *match;

	if (pdev->dev.of_node) {
		match = of_match_node(dw_mci_pwtfm_match, pdev->dev.of_node);
		dwv_data = match->data;
	}

	wetuwn dw_mci_pwtfm_wegistew(pdev, dwv_data);
}

void dw_mci_pwtfm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_mci *host = pwatfowm_get_dwvdata(pdev);

	dw_mci_wemove(host);
}
EXPOWT_SYMBOW_GPW(dw_mci_pwtfm_wemove);

static stwuct pwatfowm_dwivew dw_mci_pwtfm_dwivew = {
	.pwobe		= dw_mci_pwtfm_pwobe,
	.wemove_new	= dw_mci_pwtfm_wemove,
	.dwivew		= {
		.name		= "dw_mmc",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= dw_mci_pwtfm_match,
		.pm		= &dw_mci_pwtfm_pmops,
	},
};

moduwe_pwatfowm_dwivew(dw_mci_pwtfm_dwivew);

MODUWE_DESCWIPTION("DW Muwtimedia Cawd Intewface dwivew");
MODUWE_AUTHOW("NXP Semiconductow VietNam");
MODUWE_AUTHOW("Imagination Technowogies Wtd");
MODUWE_WICENSE("GPW v2");
