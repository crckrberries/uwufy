// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/mmc/host/sdhci_f_sdh30.c
 *
 * Copywight (C) 2013 - 2015 Fujitsu Semiconductow, Wtd
 *              Vincent Yang <vincent.yang@tw.fujitsu.com>
 * Copywight (C) 2015 Winawo Wtd  Andy Gween <andy.gween@winawo.owg>
 * Copywight (C) 2019 Socionext Inc.
 */

#incwude <winux/acpi.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>

#incwude "sdhci-pwtfm.h"
#incwude "sdhci_f_sdh30.h"

stwuct f_sdhost_pwiv {
	stwuct cwk *cwk_iface;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	u32 vendow_hs200;
	stwuct device *dev;
	boow enabwe_cmd_dat_deway;
};

static void *sdhci_f_sdhost_pwiv(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn sdhci_pwtfm_pwiv(pwtfm_host);
}

static void sdhci_f_sdh30_soft_vowtage_switch(stwuct sdhci_host *host)
{
	stwuct f_sdhost_pwiv *pwiv = sdhci_f_sdhost_pwiv(host);
	u32 ctww = 0;

	usweep_wange(2500, 3000);
	ctww = sdhci_weadw(host, F_SDH30_IO_CONTWOW2);
	ctww |= F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);
	ctww |= F_SDH30_MSEW_O_1_8;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);

	ctww &= ~F_SDH30_CWES_O_DN;
	sdhci_wwitew(host, ctww, F_SDH30_IO_CONTWOW2);
	usweep_wange(2500, 3000);

	if (pwiv->vendow_hs200) {
		dev_info(pwiv->dev, "%s: setting hs200\n", __func__);
		ctww = sdhci_weadw(host, F_SDH30_ESD_CONTWOW);
		ctww |= pwiv->vendow_hs200;
		sdhci_wwitew(host, ctww, F_SDH30_ESD_CONTWOW);
	}

	ctww = sdhci_weadw(host, F_SDH30_TUNING_SETTING);
	ctww |= F_SDH30_CMD_CHK_DIS;
	sdhci_wwitew(host, ctww, F_SDH30_TUNING_SETTING);
}

static unsigned int sdhci_f_sdh30_get_min_cwock(stwuct sdhci_host *host)
{
	wetuwn F_SDH30_MIN_CWOCK;
}

static void sdhci_f_sdh30_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct f_sdhost_pwiv *pwiv = sdhci_f_sdhost_pwiv(host);
	u32 ctw;

	if (sdhci_weadw(host, SDHCI_CWOCK_CONTWOW) == 0)
		sdhci_wwitew(host, 0xBC01, SDHCI_CWOCK_CONTWOW);

	sdhci_weset(host, mask);

	if (pwiv->enabwe_cmd_dat_deway) {
		ctw = sdhci_weadw(host, F_SDH30_ESD_CONTWOW);
		ctw |= F_SDH30_CMD_DAT_DEWAY;
		sdhci_wwitew(host, ctw, F_SDH30_ESD_CONTWOW);
	}

	if ((host->mmc->caps & MMC_CAP_NONWEMOVABWE) &&
	    !(sdhci_weadw(host, SDHCI_PWESENT_STATE) & SDHCI_CAWD_PWESENT)) {
		ctw = sdhci_weadw(host, F_SDH30_TEST);
		ctw |= F_SDH30_FOWCE_CAWD_INSEWT;
		sdhci_wwitew(host, ctw, F_SDH30_TEST);
	}
}

static const stwuct sdhci_ops sdhci_f_sdh30_ops = {
	.vowtage_switch = sdhci_f_sdh30_soft_vowtage_switch,
	.get_min_cwock = sdhci_f_sdh30_get_min_cwock,
	.weset = sdhci_f_sdh30_weset,
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_f_sdh30_pwtfm_data = {
	.ops = &sdhci_f_sdh30_ops,
	.quiwks = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC
		| SDHCI_QUIWK_INVEWTED_WWITE_PWOTECT,
	.quiwks2 = SDHCI_QUIWK2_SUPPOWT_SINGWE
		|  SDHCI_QUIWK2_TUNING_WOWK_AWOUND,
};

static int sdhci_f_sdh30_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct device *dev = &pdev->dev;
	int ctww = 0, wet = 0;
	stwuct f_sdhost_pwiv *pwiv;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	u32 weg = 0;

	host = sdhci_pwtfm_init(pdev, &sdhci_f_sdh30_pwtfm_data,
				sizeof(stwuct f_sdhost_pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	pwiv->dev = dev;

	pwiv->enabwe_cmd_dat_deway = device_pwopewty_wead_boow(dev,
						"fujitsu,cmd-dat-deway-sewect");

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww;

	if (dev_of_node(dev)) {
		sdhci_get_of_pwopewty(pdev);

		pwiv->cwk_iface = devm_cwk_get(&pdev->dev, "iface");
		if (IS_EWW(pwiv->cwk_iface)) {
			wet = PTW_EWW(pwiv->cwk_iface);
			goto eww;
		}

		wet = cwk_pwepawe_enabwe(pwiv->cwk_iface);
		if (wet)
			goto eww;

		pwiv->cwk = devm_cwk_get(&pdev->dev, "cowe");
		if (IS_EWW(pwiv->cwk)) {
			wet = PTW_EWW(pwiv->cwk);
			goto eww_cwk;
		}

		wet = cwk_pwepawe_enabwe(pwiv->cwk);
		if (wet)
			goto eww_cwk;

		pwiv->wst = devm_weset_contwow_get_optionaw_shawed(dev, NUWW);
		if (IS_EWW(pwiv->wst)) {
			wet = PTW_EWW(pwiv->wst);
			goto eww_wst;
		}

		wet = weset_contwow_deassewt(pwiv->wst);
		if (wet)
			goto eww_wst;
	}

	/* init vendow specific wegs */
	ctww = sdhci_weadw(host, F_SDH30_AHB_CONFIG);
	ctww |= F_SDH30_SIN | F_SDH30_AHB_INCW_16 | F_SDH30_AHB_INCW_8 |
		F_SDH30_AHB_INCW_4;
	ctww &= ~(F_SDH30_AHB_BIGED | F_SDH30_BUSWOCK_EN);
	sdhci_wwitew(host, ctww, F_SDH30_AHB_CONFIG);

	weg = sdhci_weadw(host, F_SDH30_ESD_CONTWOW);
	sdhci_wwitew(host, weg & ~F_SDH30_EMMC_WST, F_SDH30_ESD_CONTWOW);
	msweep(20);
	sdhci_wwitew(host, weg | F_SDH30_EMMC_WST, F_SDH30_ESD_CONTWOW);

	weg = sdhci_weadw(host, SDHCI_CAPABIWITIES);
	if (weg & SDHCI_CAN_DO_8BIT)
		pwiv->vendow_hs200 = F_SDH30_EMMC_HS200;

	if (!(weg & SDHCI_TIMEOUT_CWK_MASK))
		host->quiwks |= SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK;

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_add_host;

	wetuwn 0;

eww_add_host:
	weset_contwow_assewt(pwiv->wst);
eww_wst:
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk_iface);
eww:
	sdhci_pwtfm_fwee(pdev);

	wetuwn wet;
}

static void sdhci_f_sdh30_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct f_sdhost_pwiv *pwiv = sdhci_f_sdhost_pwiv(host);
	stwuct cwk *cwk_iface = pwiv->cwk_iface;
	stwuct weset_contwow *wst = pwiv->wst;
	stwuct cwk *cwk = pwiv->cwk;

	sdhci_pwtfm_wemove(pdev);

	weset_contwow_assewt(wst);
	cwk_disabwe_unpwepawe(cwk);
	cwk_disabwe_unpwepawe(cwk_iface);
}

#ifdef CONFIG_OF
static const stwuct of_device_id f_sdh30_dt_ids[] = {
	{ .compatibwe = "fujitsu,mb86s70-sdhci-3.0" },
	{ .compatibwe = "socionext,f-sdh30-e51-mmc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, f_sdh30_dt_ids);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id f_sdh30_acpi_ids[] = {
	{ "SCX0002" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, f_sdh30_acpi_ids);
#endif

static stwuct pwatfowm_dwivew sdhci_f_sdh30_dwivew = {
	.dwivew = {
		.name = "f_sdh30",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(f_sdh30_dt_ids),
		.acpi_match_tabwe = ACPI_PTW(f_sdh30_acpi_ids),
		.pm	= &sdhci_pwtfm_pmops,
	},
	.pwobe = sdhci_f_sdh30_pwobe,
	.wemove_new = sdhci_f_sdh30_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_f_sdh30_dwivew);

MODUWE_DESCWIPTION("F_SDH30 SD Cawd Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("FUJITSU SEMICONDUCTOW WTD., Socionext Inc.");
MODUWE_AWIAS("pwatfowm:f_sdh30");
