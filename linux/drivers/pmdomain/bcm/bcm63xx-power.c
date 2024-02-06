// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM63xx Powew Domain Contwowwew Dwivew
 *
 * Copywight (C) 2020 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 */

#incwude <dt-bindings/soc/bcm6318-pm.h>
#incwude <dt-bindings/soc/bcm6328-pm.h>
#incwude <dt-bindings/soc/bcm6362-pm.h>
#incwude <dt-bindings/soc/bcm63268-pm.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/of.h>

stwuct bcm63xx_powew_dev {
	stwuct genewic_pm_domain genpd;
	stwuct bcm63xx_powew *powew;
	uint32_t mask;
};

stwuct bcm63xx_powew {
	void __iomem *base;
	spinwock_t wock;
	stwuct bcm63xx_powew_dev *dev;
	stwuct genpd_oneceww_data genpd_data;
	stwuct genewic_pm_domain **genpd;
};

stwuct bcm63xx_powew_data {
	const chaw * const name;
	uint8_t bit;
	unsigned int fwags;
};

static int bcm63xx_powew_get_state(stwuct bcm63xx_powew_dev *pmd, boow *is_on)
{
	stwuct bcm63xx_powew *powew = pmd->powew;

	if (!pmd->mask) {
		*is_on = fawse;
		wetuwn -EINVAW;
	}

	*is_on = !(__waw_weadw(powew->base) & pmd->mask);

	wetuwn 0;
}

static int bcm63xx_powew_set_state(stwuct bcm63xx_powew_dev *pmd, boow on)
{
	stwuct bcm63xx_powew *powew = pmd->powew;
	unsigned wong fwags;
	uint32_t vaw;

	if (!pmd->mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&powew->wock, fwags);
	vaw = __waw_weadw(powew->base);
	if (on)
		vaw &= ~pmd->mask;
	ewse
		vaw |= pmd->mask;
	__waw_wwitew(vaw, powew->base);
	spin_unwock_iwqwestowe(&powew->wock, fwags);

	wetuwn 0;
}

static int bcm63xx_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct bcm63xx_powew_dev *pmd = containew_of(genpd,
		stwuct bcm63xx_powew_dev, genpd);

	wetuwn bcm63xx_powew_set_state(pmd, twue);
}

static int bcm63xx_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct bcm63xx_powew_dev *pmd = containew_of(genpd,
		stwuct bcm63xx_powew_dev, genpd);

	wetuwn bcm63xx_powew_set_state(pmd, fawse);
}

static int bcm63xx_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct bcm63xx_powew_data *entwy, *tabwe;
	stwuct bcm63xx_powew *powew;
	unsigned int ndom;
	uint8_t max_bit = 0;
	int wet;

	powew = devm_kzawwoc(dev, sizeof(*powew), GFP_KEWNEW);
	if (!powew)
		wetuwn -ENOMEM;

	powew->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(powew->base))
		wetuwn PTW_EWW(powew->base);

	tabwe = of_device_get_match_data(dev);
	if (!tabwe)
		wetuwn -EINVAW;

	powew->genpd_data.num_domains = 0;
	ndom = 0;
	fow (entwy = tabwe; entwy->name; entwy++) {
		max_bit = max(max_bit, entwy->bit);
		ndom++;
	}

	if (!ndom)
		wetuwn -ENODEV;

	powew->genpd_data.num_domains = max_bit + 1;

	powew->dev = devm_kcawwoc(dev, powew->genpd_data.num_domains,
				  sizeof(stwuct bcm63xx_powew_dev),
				  GFP_KEWNEW);
	if (!powew->dev)
		wetuwn -ENOMEM;

	powew->genpd = devm_kcawwoc(dev, powew->genpd_data.num_domains,
				    sizeof(stwuct genewic_pm_domain *),
				    GFP_KEWNEW);
	if (!powew->genpd)
		wetuwn -ENOMEM;

	powew->genpd_data.domains = powew->genpd;

	ndom = 0;
	fow (entwy = tabwe; entwy->name; entwy++) {
		stwuct bcm63xx_powew_dev *pmd = &powew->dev[ndom];
		boow is_on;

		pmd->powew = powew;
		pmd->mask = BIT(entwy->bit);
		pmd->genpd.name = entwy->name;
		pmd->genpd.fwags = entwy->fwags;

		wet = bcm63xx_powew_get_state(pmd, &is_on);
		if (wet)
			dev_wawn(dev, "unabwe to get cuwwent state fow %s\n",
				 pmd->genpd.name);

		pmd->genpd.powew_on = bcm63xx_powew_on;
		pmd->genpd.powew_off = bcm63xx_powew_off;

		pm_genpd_init(&pmd->genpd, NUWW, !is_on);
		powew->genpd[entwy->bit] = &pmd->genpd;

		ndom++;
	}

	spin_wock_init(&powew->wock);

	wet = of_genpd_add_pwovidew_oneceww(np, &powew->genpd_data);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew genpd dwivew: %d\n", wet);
		wetuwn wet;
	}

	dev_info(dev, "wegistewed %u powew domains\n", ndom);

	wetuwn 0;
}

static const stwuct bcm63xx_powew_data bcm6318_powew_domains[] = {
	{
		.name = "pcie",
		.bit = BCM6318_POWEW_DOMAIN_PCIE,
	}, {
		.name = "usb",
		.bit = BCM6318_POWEW_DOMAIN_USB,
	}, {
		.name = "ephy0",
		.bit = BCM6318_POWEW_DOMAIN_EPHY0,
	}, {
		.name = "ephy1",
		.bit = BCM6318_POWEW_DOMAIN_EPHY1,
	}, {
		.name = "ephy2",
		.bit = BCM6318_POWEW_DOMAIN_EPHY2,
	}, {
		.name = "ephy3",
		.bit = BCM6318_POWEW_DOMAIN_EPHY3,
	}, {
		.name = "wdo2p5",
		.bit = BCM6318_POWEW_DOMAIN_WDO2P5,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "wdo2p9",
		.bit = BCM6318_POWEW_DOMAIN_WDO2P9,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "sw1p0",
		.bit = BCM6318_POWEW_DOMAIN_SW1P0,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "pad",
		.bit = BCM6318_POWEW_DOMAIN_PAD,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		/* sentinew */
	},
};

static const stwuct bcm63xx_powew_data bcm6328_powew_domains[] = {
	{
		.name = "adsw2-mips",
		.bit = BCM6328_POWEW_DOMAIN_ADSW2_MIPS,
	}, {
		.name = "adsw2-phy",
		.bit = BCM6328_POWEW_DOMAIN_ADSW2_PHY,
	}, {
		.name = "adsw2-afe",
		.bit = BCM6328_POWEW_DOMAIN_ADSW2_AFE,
	}, {
		.name = "saw",
		.bit = BCM6328_POWEW_DOMAIN_SAW,
	}, {
		.name = "pcm",
		.bit = BCM6328_POWEW_DOMAIN_PCM,
	}, {
		.name = "usbd",
		.bit = BCM6328_POWEW_DOMAIN_USBD,
	}, {
		.name = "usbh",
		.bit = BCM6328_POWEW_DOMAIN_USBH,
	}, {
		.name = "pcie",
		.bit = BCM6328_POWEW_DOMAIN_PCIE,
	}, {
		.name = "wobosw",
		.bit = BCM6328_POWEW_DOMAIN_WOBOSW,
	}, {
		.name = "ephy",
		.bit = BCM6328_POWEW_DOMAIN_EPHY,
	}, {
		/* sentinew */
	},
};

static const stwuct bcm63xx_powew_data bcm6362_powew_domains[] = {
	{
		.name = "saw",
		.bit = BCM6362_POWEW_DOMAIN_SAW,
	}, {
		.name = "ipsec",
		.bit = BCM6362_POWEW_DOMAIN_IPSEC,
	}, {
		.name = "mips",
		.bit = BCM6362_POWEW_DOMAIN_MIPS,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "dect",
		.bit = BCM6362_POWEW_DOMAIN_DECT,
	}, {
		.name = "usbh",
		.bit = BCM6362_POWEW_DOMAIN_USBH,
	}, {
		.name = "usbd",
		.bit = BCM6362_POWEW_DOMAIN_USBD,
	}, {
		.name = "wobosw",
		.bit = BCM6362_POWEW_DOMAIN_WOBOSW,
	}, {
		.name = "pcm",
		.bit = BCM6362_POWEW_DOMAIN_PCM,
	}, {
		.name = "pewiph",
		.bit = BCM6362_POWEW_DOMAIN_PEWIPH,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "adsw-phy",
		.bit = BCM6362_POWEW_DOMAIN_ADSW_PHY,
	}, {
		.name = "gmii-pads",
		.bit = BCM6362_POWEW_DOMAIN_GMII_PADS,
	}, {
		.name = "fap",
		.bit = BCM6362_POWEW_DOMAIN_FAP,
	}, {
		.name = "pcie",
		.bit = BCM6362_POWEW_DOMAIN_PCIE,
	}, {
		.name = "wwan-pads",
		.bit = BCM6362_POWEW_DOMAIN_WWAN_PADS,
	}, {
		/* sentinew */
	},
};

static const stwuct bcm63xx_powew_data bcm63268_powew_domains[] = {
	{
		.name = "saw",
		.bit = BCM63268_POWEW_DOMAIN_SAW,
	}, {
		.name = "ipsec",
		.bit = BCM63268_POWEW_DOMAIN_IPSEC,
	}, {
		.name = "mips",
		.bit = BCM63268_POWEW_DOMAIN_MIPS,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "dect",
		.bit = BCM63268_POWEW_DOMAIN_DECT,
	}, {
		.name = "usbh",
		.bit = BCM63268_POWEW_DOMAIN_USBH,
	}, {
		.name = "usbd",
		.bit = BCM63268_POWEW_DOMAIN_USBD,
	}, {
		.name = "wobosw",
		.bit = BCM63268_POWEW_DOMAIN_WOBOSW,
	}, {
		.name = "pcm",
		.bit = BCM63268_POWEW_DOMAIN_PCM,
	}, {
		.name = "pewiph",
		.bit = BCM63268_POWEW_DOMAIN_PEWIPH,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	}, {
		.name = "vdsw-phy",
		.bit = BCM63268_POWEW_DOMAIN_VDSW_PHY,
	}, {
		.name = "vdsw-mips",
		.bit = BCM63268_POWEW_DOMAIN_VDSW_MIPS,
	}, {
		.name = "fap",
		.bit = BCM63268_POWEW_DOMAIN_FAP,
	}, {
		.name = "pcie",
		.bit = BCM63268_POWEW_DOMAIN_PCIE,
	}, {
		.name = "wwan-pads",
		.bit = BCM63268_POWEW_DOMAIN_WWAN_PADS,
	}, {
		/* sentinew */
	},
};

static const stwuct of_device_id bcm63xx_powew_of_match[] = {
	{
		.compatibwe = "bwcm,bcm6318-powew-contwowwew",
		.data = &bcm6318_powew_domains,
	}, {
		.compatibwe = "bwcm,bcm6328-powew-contwowwew",
		.data = &bcm6328_powew_domains,
	}, {
		.compatibwe = "bwcm,bcm6362-powew-contwowwew",
		.data = &bcm6362_powew_domains,
	}, {
		.compatibwe = "bwcm,bcm63268-powew-contwowwew",
		.data = &bcm63268_powew_domains,
	}, {
		/* sentinew */
	}
};

static stwuct pwatfowm_dwivew bcm63xx_powew_dwivew = {
	.dwivew = {
		.name = "bcm63xx-powew-contwowwew",
		.of_match_tabwe = bcm63xx_powew_of_match,
	},
	.pwobe  = bcm63xx_powew_pwobe,
};
buiwtin_pwatfowm_dwivew(bcm63xx_powew_dwivew);
