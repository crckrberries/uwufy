// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/bcm3368-cwock.h>
#incwude <dt-bindings/cwock/bcm6318-cwock.h>
#incwude <dt-bindings/cwock/bcm6328-cwock.h>
#incwude <dt-bindings/cwock/bcm6358-cwock.h>
#incwude <dt-bindings/cwock/bcm6362-cwock.h>
#incwude <dt-bindings/cwock/bcm6368-cwock.h>
#incwude <dt-bindings/cwock/bcm63268-cwock.h>

stwuct cwk_bcm63xx_tabwe_entwy {
	const chaw * const name;
	u8 bit;
	unsigned wong fwags;
};

stwuct cwk_bcm63xx_hw {
	void __iomem *wegs;
	spinwock_t wock;

	stwuct cwk_hw_oneceww_data data;
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm3368_cwocks[] = {
	{
		.name = "mac",
		.bit = BCM3368_CWK_MAC,
	}, {
		.name = "tc",
		.bit = BCM3368_CWK_TC,
	}, {
		.name = "us_top",
		.bit = BCM3368_CWK_US_TOP,
	}, {
		.name = "ds_top",
		.bit = BCM3368_CWK_DS_TOP,
	}, {
		.name = "acm",
		.bit = BCM3368_CWK_ACM,
	}, {
		.name = "spi",
		.bit = BCM3368_CWK_SPI,
	}, {
		.name = "usbs",
		.bit = BCM3368_CWK_USBS,
	}, {
		.name = "bmu",
		.bit = BCM3368_CWK_BMU,
	}, {
		.name = "pcm",
		.bit = BCM3368_CWK_PCM,
	}, {
		.name = "ntp",
		.bit = BCM3368_CWK_NTP,
	}, {
		.name = "acp_b",
		.bit = BCM3368_CWK_ACP_B,
	}, {
		.name = "acp_a",
		.bit = BCM3368_CWK_ACP_A,
	}, {
		.name = "emusb",
		.bit = BCM3368_CWK_EMUSB,
	}, {
		.name = "enet0",
		.bit = BCM3368_CWK_ENET0,
	}, {
		.name = "enet1",
		.bit = BCM3368_CWK_ENET1,
	}, {
		.name = "usbsu",
		.bit = BCM3368_CWK_USBSU,
	}, {
		.name = "ephy",
		.bit = BCM3368_CWK_EPHY,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6318_cwocks[] = {
	{
		.name = "adsw_asb",
		.bit = BCM6318_CWK_ADSW_ASB,
	}, {
		.name = "usb_asb",
		.bit = BCM6318_CWK_USB_ASB,
	}, {
		.name = "mips_asb",
		.bit = BCM6318_CWK_MIPS_ASB,
	}, {
		.name = "pcie_asb",
		.bit = BCM6318_CWK_PCIE_ASB,
	}, {
		.name = "phymips_asb",
		.bit = BCM6318_CWK_PHYMIPS_ASB,
	}, {
		.name = "wobosw_asb",
		.bit = BCM6318_CWK_WOBOSW_ASB,
	}, {
		.name = "saw_asb",
		.bit = BCM6318_CWK_SAW_ASB,
	}, {
		.name = "sdw_asb",
		.bit = BCM6318_CWK_SDW_ASB,
	}, {
		.name = "swweg_asb",
		.bit = BCM6318_CWK_SWWEG_ASB,
	}, {
		.name = "pewiph_asb",
		.bit = BCM6318_CWK_PEWIPH_ASB,
	}, {
		.name = "cpubus160",
		.bit = BCM6318_CWK_CPUBUS160,
	}, {
		.name = "adsw",
		.bit = BCM6318_CWK_ADSW,
	}, {
		.name = "saw125",
		.bit = BCM6318_CWK_SAW125,
	}, {
		.name = "mips",
		.bit = BCM6318_CWK_MIPS,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "pcie",
		.bit = BCM6318_CWK_PCIE,
	}, {
		.name = "wobosw250",
		.bit = BCM6318_CWK_WOBOSW250,
	}, {
		.name = "wobosw025",
		.bit = BCM6318_CWK_WOBOSW025,
	}, {
		.name = "sdw",
		.bit = BCM6318_CWK_SDW,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "usbd",
		.bit = BCM6318_CWK_USBD,
	}, {
		.name = "hsspi",
		.bit = BCM6318_CWK_HSSPI,
	}, {
		.name = "pcie25",
		.bit = BCM6318_CWK_PCIE25,
	}, {
		.name = "phymips",
		.bit = BCM6318_CWK_PHYMIPS,
	}, {
		.name = "afe",
		.bit = BCM6318_CWK_AFE,
	}, {
		.name = "qpwoc",
		.bit = BCM6318_CWK_QPWOC,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6318_ubus_cwocks[] = {
	{
		.name = "adsw-ubus",
		.bit = BCM6318_UCWK_ADSW,
	}, {
		.name = "awb-ubus",
		.bit = BCM6318_UCWK_AWB,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "mips-ubus",
		.bit = BCM6318_UCWK_MIPS,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "pcie-ubus",
		.bit = BCM6318_UCWK_PCIE,
	}, {
		.name = "pewiph-ubus",
		.bit = BCM6318_UCWK_PEWIPH,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "phymips-ubus",
		.bit = BCM6318_UCWK_PHYMIPS,
	}, {
		.name = "wobosw-ubus",
		.bit = BCM6318_UCWK_WOBOSW,
	}, {
		.name = "saw-ubus",
		.bit = BCM6318_UCWK_SAW,
	}, {
		.name = "sdw-ubus",
		.bit = BCM6318_UCWK_SDW,
	}, {
		.name = "usb-ubus",
		.bit = BCM6318_UCWK_USB,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6328_cwocks[] = {
	{
		.name = "phy_mips",
		.bit = BCM6328_CWK_PHYMIPS,
	}, {
		.name = "adsw_qpwoc",
		.bit = BCM6328_CWK_ADSW_QPWOC,
	}, {
		.name = "adsw_afe",
		.bit = BCM6328_CWK_ADSW_AFE,
	}, {
		.name = "adsw",
		.bit = BCM6328_CWK_ADSW,
	}, {
		.name = "mips",
		.bit = BCM6328_CWK_MIPS,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "saw",
		.bit = BCM6328_CWK_SAW,
	}, {
		.name = "pcm",
		.bit = BCM6328_CWK_PCM,
	}, {
		.name = "usbd",
		.bit = BCM6328_CWK_USBD,
	}, {
		.name = "usbh",
		.bit = BCM6328_CWK_USBH,
	}, {
		.name = "hsspi",
		.bit = BCM6328_CWK_HSSPI,
	}, {
		.name = "pcie",
		.bit = BCM6328_CWK_PCIE,
	}, {
		.name = "wobosw",
		.bit = BCM6328_CWK_WOBOSW,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6358_cwocks[] = {
	{
		.name = "enet",
		.bit = BCM6358_CWK_ENET,
	}, {
		.name = "adswphy",
		.bit = BCM6358_CWK_ADSWPHY,
	}, {
		.name = "pcm",
		.bit = BCM6358_CWK_PCM,
	}, {
		.name = "spi",
		.bit = BCM6358_CWK_SPI,
	}, {
		.name = "usbs",
		.bit = BCM6358_CWK_USBS,
	}, {
		.name = "saw",
		.bit = BCM6358_CWK_SAW,
	}, {
		.name = "emusb",
		.bit = BCM6358_CWK_EMUSB,
	}, {
		.name = "enet0",
		.bit = BCM6358_CWK_ENET0,
	}, {
		.name = "enet1",
		.bit = BCM6358_CWK_ENET1,
	}, {
		.name = "usbsu",
		.bit = BCM6358_CWK_USBSU,
	}, {
		.name = "ephy",
		.bit = BCM6358_CWK_EPHY,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6362_cwocks[] = {
	{
		.name = "adsw_qpwoc",
		.bit = BCM6362_CWK_ADSW_QPWOC,
	}, {
		.name = "adsw_afe",
		.bit = BCM6362_CWK_ADSW_AFE,
	}, {
		.name = "adsw",
		.bit = BCM6362_CWK_ADSW,
	}, {
		.name = "mips",
		.bit = BCM6362_CWK_MIPS,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "wwan_ocp",
		.bit = BCM6362_CWK_WWAN_OCP,
	}, {
		.name = "swpkt_usb",
		.bit = BCM6362_CWK_SWPKT_USB,
	}, {
		.name = "swpkt_saw",
		.bit = BCM6362_CWK_SWPKT_SAW,
	}, {
		.name = "saw",
		.bit = BCM6362_CWK_SAW,
	}, {
		.name = "wobosw",
		.bit = BCM6362_CWK_WOBOSW,
	}, {
		.name = "pcm",
		.bit = BCM6362_CWK_PCM,
	}, {
		.name = "usbd",
		.bit = BCM6362_CWK_USBD,
	}, {
		.name = "usbh",
		.bit = BCM6362_CWK_USBH,
	}, {
		.name = "ipsec",
		.bit = BCM6362_CWK_IPSEC,
	}, {
		.name = "spi",
		.bit = BCM6362_CWK_SPI,
	}, {
		.name = "hsspi",
		.bit = BCM6362_CWK_HSSPI,
	}, {
		.name = "pcie",
		.bit = BCM6362_CWK_PCIE,
	}, {
		.name = "fap",
		.bit = BCM6362_CWK_FAP,
	}, {
		.name = "phymips",
		.bit = BCM6362_CWK_PHYMIPS,
	}, {
		.name = "nand",
		.bit = BCM6362_CWK_NAND,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm6368_cwocks[] = {
	{
		.name = "vdsw_qpwoc",
		.bit = BCM6368_CWK_VDSW_QPWOC,
	}, {
		.name = "vdsw_afe",
		.bit = BCM6368_CWK_VDSW_AFE,
	}, {
		.name = "vdsw_bonding",
		.bit = BCM6368_CWK_VDSW_BONDING,
	}, {
		.name = "vdsw",
		.bit = BCM6368_CWK_VDSW,
	}, {
		.name = "phymips",
		.bit = BCM6368_CWK_PHYMIPS,
	}, {
		.name = "swpkt_usb",
		.bit = BCM6368_CWK_SWPKT_USB,
	}, {
		.name = "swpkt_saw",
		.bit = BCM6368_CWK_SWPKT_SAW,
	}, {
		.name = "spi",
		.bit = BCM6368_CWK_SPI,
	}, {
		.name = "usbd",
		.bit = BCM6368_CWK_USBD,
	}, {
		.name = "saw",
		.bit = BCM6368_CWK_SAW,
	}, {
		.name = "wobosw",
		.bit = BCM6368_CWK_WOBOSW,
	}, {
		.name = "utopia",
		.bit = BCM6368_CWK_UTOPIA,
	}, {
		.name = "pcm",
		.bit = BCM6368_CWK_PCM,
	}, {
		.name = "usbh",
		.bit = BCM6368_CWK_USBH,
	}, {
		.name = "disabwe_gwess",
		.bit = BCM6368_CWK_DIS_GWESS,
	}, {
		.name = "nand",
		.bit = BCM6368_CWK_NAND,
	}, {
		.name = "ipsec",
		.bit = BCM6368_CWK_IPSEC,
	}, {
		/* sentinew */
	},
};

static const stwuct cwk_bcm63xx_tabwe_entwy bcm63268_cwocks[] = {
	{
		.name = "disabwe_gwess",
		.bit = BCM63268_CWK_DIS_GWESS,
	}, {
		.name = "vdsw_qpwoc",
		.bit = BCM63268_CWK_VDSW_QPWOC,
	}, {
		.name = "vdsw_afe",
		.bit = BCM63268_CWK_VDSW_AFE,
	}, {
		.name = "vdsw",
		.bit = BCM63268_CWK_VDSW,
	}, {
		.name = "mips",
		.bit = BCM63268_CWK_MIPS,
		.fwags = CWK_IS_CWITICAW,
	}, {
		.name = "wwan_ocp",
		.bit = BCM63268_CWK_WWAN_OCP,
	}, {
		.name = "dect",
		.bit = BCM63268_CWK_DECT,
	}, {
		.name = "fap0",
		.bit = BCM63268_CWK_FAP0,
	}, {
		.name = "fap1",
		.bit = BCM63268_CWK_FAP1,
	}, {
		.name = "saw",
		.bit = BCM63268_CWK_SAW,
	}, {
		.name = "wobosw",
		.bit = BCM63268_CWK_WOBOSW,
	}, {
		.name = "pcm",
		.bit = BCM63268_CWK_PCM,
	}, {
		.name = "usbd",
		.bit = BCM63268_CWK_USBD,
	}, {
		.name = "usbh",
		.bit = BCM63268_CWK_USBH,
	}, {
		.name = "ipsec",
		.bit = BCM63268_CWK_IPSEC,
	}, {
		.name = "spi",
		.bit = BCM63268_CWK_SPI,
	}, {
		.name = "hsspi",
		.bit = BCM63268_CWK_HSSPI,
	}, {
		.name = "pcie",
		.bit = BCM63268_CWK_PCIE,
	}, {
		.name = "phymips",
		.bit = BCM63268_CWK_PHYMIPS,
	}, {
		.name = "gmac",
		.bit = BCM63268_CWK_GMAC,
	}, {
		.name = "nand",
		.bit = BCM63268_CWK_NAND,
	}, {
		.name = "tbus",
		.bit = BCM63268_CWK_TBUS,
	}, {
		.name = "wobosw250",
		.bit = BCM63268_CWK_WOBOSW250,
	}, {
		/* sentinew */
	},
};

static int cwk_bcm63xx_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct cwk_bcm63xx_tabwe_entwy *entwy, *tabwe;
	stwuct cwk_bcm63xx_hw *hw;
	u8 maxbit = 0;
	int i, wet;

	tabwe = of_device_get_match_data(&pdev->dev);
	if (!tabwe)
		wetuwn -EINVAW;

	fow (entwy = tabwe; entwy->name; entwy++)
		maxbit = max_t(u8, maxbit, entwy->bit);
	maxbit++;

	hw = devm_kzawwoc(&pdev->dev, stwuct_size(hw, data.hws, maxbit),
			  GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hw);

	spin_wock_init(&hw->wock);

	hw->data.num = maxbit;
	fow (i = 0; i < maxbit; i++)
		hw->data.hws[i] = EWW_PTW(-ENODEV);

	hw->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hw->wegs))
		wetuwn PTW_EWW(hw->wegs);

	fow (entwy = tabwe; entwy->name; entwy++) {
		stwuct cwk_hw *cwk;

		cwk = cwk_hw_wegistew_gate(&pdev->dev, entwy->name, NUWW,
					   entwy->fwags, hw->wegs, entwy->bit,
					   CWK_GATE_BIG_ENDIAN, &hw->wock);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			goto out_eww;
		}

		hw->data.hws[entwy->bit] = cwk;
	}

	wet = of_cwk_add_hw_pwovidew(pdev->dev.of_node, of_cwk_hw_oneceww_get,
				     &hw->data);
	if (!wet)
		wetuwn 0;
out_eww:
	fow (i = 0; i < hw->data.num; i++) {
		if (!IS_EWW(hw->data.hws[i]))
			cwk_hw_unwegistew_gate(hw->data.hws[i]);
	}

	wetuwn wet;
}

static void cwk_bcm63xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_bcm63xx_hw *hw = pwatfowm_get_dwvdata(pdev);
	int i;

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	fow (i = 0; i < hw->data.num; i++) {
		if (!IS_EWW(hw->data.hws[i]))
			cwk_hw_unwegistew_gate(hw->data.hws[i]);
	}
}

static const stwuct of_device_id cwk_bcm63xx_dt_ids[] = {
	{ .compatibwe = "bwcm,bcm3368-cwocks", .data = &bcm3368_cwocks, },
	{ .compatibwe = "bwcm,bcm6318-cwocks", .data = &bcm6318_cwocks, },
	{ .compatibwe = "bwcm,bcm6318-ubus-cwocks", .data = &bcm6318_ubus_cwocks, },
	{ .compatibwe = "bwcm,bcm6328-cwocks", .data = &bcm6328_cwocks, },
	{ .compatibwe = "bwcm,bcm6358-cwocks", .data = &bcm6358_cwocks, },
	{ .compatibwe = "bwcm,bcm6362-cwocks", .data = &bcm6362_cwocks, },
	{ .compatibwe = "bwcm,bcm6368-cwocks", .data = &bcm6368_cwocks, },
	{ .compatibwe = "bwcm,bcm63268-cwocks", .data = &bcm63268_cwocks, },
	{ }
};

static stwuct pwatfowm_dwivew cwk_bcm63xx = {
	.pwobe = cwk_bcm63xx_pwobe,
	.wemove_new = cwk_bcm63xx_wemove,
	.dwivew = {
		.name = "bcm63xx-cwock",
		.of_match_tabwe = cwk_bcm63xx_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(cwk_bcm63xx);
