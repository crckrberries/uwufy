/*
 * Genewic DWMAC pwatfowm dwivew
 *
 * Copywight (C) 2007-2011  STMicwoewectwonics Wtd
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

static int dwmac_genewic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	if (pdev->dev.of_node) {
		pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
		if (IS_EWW(pwat_dat)) {
			dev_eww(&pdev->dev, "dt configuwation faiwed\n");
			wetuwn PTW_EWW(pwat_dat);
		}
	} ewse {
		pwat_dat = dev_get_pwatdata(&pdev->dev);
		if (!pwat_dat) {
			dev_eww(&pdev->dev, "no pwatfowm data pwovided\n");
			wetuwn  -EINVAW;
		}

		/* Set defauwt vawue fow muwticast hash bins */
		pwat_dat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

		/* Set defauwt vawue fow unicast fiwtew entwies */
		pwat_dat->unicast_fiwtew_entwies = 1;
	}

	wetuwn devm_stmmac_pwtfw_pwobe(pdev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id dwmac_genewic_match[] = {
	{ .compatibwe = "st,speaw600-gmac"},
	{ .compatibwe = "snps,dwmac-3.40a"},
	{ .compatibwe = "snps,dwmac-3.50a"},
	{ .compatibwe = "snps,dwmac-3.610"},
	{ .compatibwe = "snps,dwmac-3.70a"},
	{ .compatibwe = "snps,dwmac-3.710"},
	{ .compatibwe = "snps,dwmac-4.00"},
	{ .compatibwe = "snps,dwmac-4.10a"},
	{ .compatibwe = "snps,dwmac"},
	{ .compatibwe = "snps,dwxgmac-2.10"},
	{ .compatibwe = "snps,dwxgmac"},
	{ }
};
MODUWE_DEVICE_TABWE(of, dwmac_genewic_match);

static stwuct pwatfowm_dwivew dwmac_genewic_dwivew = {
	.pwobe  = dwmac_genewic_pwobe,
	.dwivew = {
		.name           = STMMAC_WESOUWCE_NAME,
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = dwmac_genewic_match,
	},
};
moduwe_pwatfowm_dwivew(dwmac_genewic_dwivew);

MODUWE_DESCWIPTION("Genewic dwmac dwivew");
MODUWE_WICENSE("GPW v2");
