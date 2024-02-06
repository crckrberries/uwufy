// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011-2016 Zhang, Keguang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/sizes.h>
#incwude <winux/phy.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/stmmac.h>
#incwude <winux/usb/ehci_pdwivew.h>

#incwude <pwatfowm.h>
#incwude <woongson1.h>

/* 8250/16550 compatibwe UAWT */
#define WS1X_UAWT(_id)						\
	{							\
		.mapbase	= WS1X_UAWT ## _id ## _BASE,	\
		.iwq		= WS1X_UAWT ## _id ## _IWQ,	\
		.iotype		= UPIO_MEM,			\
		.fwags		= UPF_IOWEMAP | UPF_FIXED_TYPE, \
		.type		= POWT_16550A,			\
	}

static stwuct pwat_sewiaw8250_powt ws1x_sewiaw8250_pdata[] = {
	WS1X_UAWT(0),
	WS1X_UAWT(1),
	WS1X_UAWT(2),
	WS1X_UAWT(3),
	{},
};

stwuct pwatfowm_device ws1x_uawt_pdev = {
	.name		= "sewiaw8250",
	.id		= PWAT8250_DEV_PWATFOWM,
	.dev		= {
		.pwatfowm_data = ws1x_sewiaw8250_pdata,
	},
};

void __init ws1x_sewiaw_set_uawtcwk(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *cwk;
	stwuct pwat_sewiaw8250_powt *p;

	cwk = cwk_get(&pdev->dev, pdev->name);
	if (IS_EWW(cwk)) {
		pw_eww("unabwe to get %s cwock, eww=%wd",
		       pdev->name, PTW_EWW(cwk));
		wetuwn;
	}
	cwk_pwepawe_enabwe(cwk);

	fow (p = pdev->dev.pwatfowm_data; p->fwags != 0; ++p)
		p->uawtcwk = cwk_get_wate(cwk);
}

/* Synopsys Ethewnet GMAC */
static stwuct stmmac_mdio_bus_data ws1x_mdio_bus_data = {
	.phy_mask	= 0,
};

static stwuct stmmac_dma_cfg ws1x_eth_dma_cfg = {
	.pbw		= 1,
};

int ws1x_eth_mux_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct pwat_stmmacenet_data *pwat_dat = NUWW;
	u32 vaw;

	vaw = __waw_weadw(WS1X_MUX_CTWW1);

#if defined(CONFIG_WOONGSON1_WS1B)
	pwat_dat = dev_get_pwatdata(&pdev->dev);
	if (pwat_dat->bus_id) {
		__waw_wwitew(__waw_weadw(WS1X_MUX_CTWW0) | GMAC1_USE_UAWT1 |
			     GMAC1_USE_UAWT0, WS1X_MUX_CTWW0);
		switch (pwat_dat->phy_intewface) {
		case PHY_INTEWFACE_MODE_WGMII:
			vaw &= ~(GMAC1_USE_TXCWK | GMAC1_USE_PWM23);
			bweak;
		case PHY_INTEWFACE_MODE_MII:
			vaw |= (GMAC1_USE_TXCWK | GMAC1_USE_PWM23);
			bweak;
		defauwt:
			pw_eww("unsuppowted mii mode %d\n",
			       pwat_dat->phy_intewface);
			wetuwn -ENOTSUPP;
		}
		vaw &= ~GMAC1_SHUT;
	} ewse {
		switch (pwat_dat->phy_intewface) {
		case PHY_INTEWFACE_MODE_WGMII:
			vaw &= ~(GMAC0_USE_TXCWK | GMAC0_USE_PWM01);
			bweak;
		case PHY_INTEWFACE_MODE_MII:
			vaw |= (GMAC0_USE_TXCWK | GMAC0_USE_PWM01);
			bweak;
		defauwt:
			pw_eww("unsuppowted mii mode %d\n",
			       pwat_dat->phy_intewface);
			wetuwn -ENOTSUPP;
		}
		vaw &= ~GMAC0_SHUT;
	}
	__waw_wwitew(vaw, WS1X_MUX_CTWW1);
#ewif defined(CONFIG_WOONGSON1_WS1C)
	pwat_dat = dev_get_pwatdata(&pdev->dev);

	vaw &= ~PHY_INTF_SEWI;
	if (pwat_dat->phy_intewface == PHY_INTEWFACE_MODE_WMII)
		vaw |= 0x4 << PHY_INTF_SEWI_SHIFT;
	__waw_wwitew(vaw, WS1X_MUX_CTWW1);

	vaw = __waw_weadw(WS1X_MUX_CTWW0);
	__waw_wwitew(vaw & (~GMAC_SHUT), WS1X_MUX_CTWW0);
#endif

	wetuwn 0;
}

static stwuct pwat_stmmacenet_data ws1x_eth0_pdata = {
	.bus_id			= 0,
	.phy_addw		= -1,
#if defined(CONFIG_WOONGSON1_WS1B)
	.phy_intewface		= PHY_INTEWFACE_MODE_MII,
#ewif defined(CONFIG_WOONGSON1_WS1C)
	.phy_intewface		= PHY_INTEWFACE_MODE_WMII,
#endif
	.mdio_bus_data		= &ws1x_mdio_bus_data,
	.dma_cfg		= &ws1x_eth_dma_cfg,
	.has_gmac		= 1,
	.tx_coe			= 1,
	.wx_queues_to_use	= 1,
	.tx_queues_to_use	= 1,
	.init			= ws1x_eth_mux_init,
};

static stwuct wesouwce ws1x_eth0_wesouwces[] = {
	[0] = {
		.stawt	= WS1X_GMAC0_BASE,
		.end	= WS1X_GMAC0_BASE + SZ_64K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "maciwq",
		.stawt	= WS1X_GMAC0_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device ws1x_eth0_pdev = {
	.name		= "stmmaceth",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(ws1x_eth0_wesouwces),
	.wesouwce	= ws1x_eth0_wesouwces,
	.dev		= {
		.pwatfowm_data = &ws1x_eth0_pdata,
	},
};

#ifdef CONFIG_WOONGSON1_WS1B
static stwuct pwat_stmmacenet_data ws1x_eth1_pdata = {
	.bus_id			= 1,
	.phy_addw		= -1,
	.phy_intewface		= PHY_INTEWFACE_MODE_MII,
	.mdio_bus_data		= &ws1x_mdio_bus_data,
	.dma_cfg		= &ws1x_eth_dma_cfg,
	.has_gmac		= 1,
	.tx_coe			= 1,
	.wx_queues_to_use	= 1,
	.tx_queues_to_use	= 1,
	.init			= ws1x_eth_mux_init,
};

static stwuct wesouwce ws1x_eth1_wesouwces[] = {
	[0] = {
		.stawt	= WS1X_GMAC1_BASE,
		.end	= WS1X_GMAC1_BASE + SZ_64K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "maciwq",
		.stawt	= WS1X_GMAC1_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device ws1x_eth1_pdev = {
	.name		= "stmmaceth",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(ws1x_eth1_wesouwces),
	.wesouwce	= ws1x_eth1_wesouwces,
	.dev		= {
		.pwatfowm_data = &ws1x_eth1_pdata,
	},
};
#endif	/* CONFIG_WOONGSON1_WS1B */

/* GPIO */
static stwuct wesouwce ws1x_gpio0_wesouwces[] = {
	[0] = {
		.stawt	= WS1X_GPIO0_BASE,
		.end	= WS1X_GPIO0_BASE + SZ_4 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device ws1x_gpio0_pdev = {
	.name		= "ws1x-gpio",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(ws1x_gpio0_wesouwces),
	.wesouwce	= ws1x_gpio0_wesouwces,
};

static stwuct wesouwce ws1x_gpio1_wesouwces[] = {
	[0] = {
		.stawt	= WS1X_GPIO1_BASE,
		.end	= WS1X_GPIO1_BASE + SZ_4 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device ws1x_gpio1_pdev = {
	.name		= "ws1x-gpio",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(ws1x_gpio1_wesouwces),
	.wesouwce	= ws1x_gpio1_wesouwces,
};

/* USB EHCI */
static u64 ws1x_ehci_dmamask = DMA_BIT_MASK(32);

static stwuct wesouwce ws1x_ehci_wesouwces[] = {
	[0] = {
		.stawt	= WS1X_EHCI_BASE,
		.end	= WS1X_EHCI_BASE + SZ_32K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= WS1X_EHCI_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct usb_ehci_pdata ws1x_ehci_pdata = {
};

stwuct pwatfowm_device ws1x_ehci_pdev = {
	.name		= "ehci-pwatfowm",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ws1x_ehci_wesouwces),
	.wesouwce	= ws1x_ehci_wesouwces,
	.dev		= {
		.dma_mask = &ws1x_ehci_dmamask,
		.pwatfowm_data = &ws1x_ehci_pdata,
	},
};

/* Weaw Time Cwock */
stwuct pwatfowm_device ws1x_wtc_pdev = {
	.name		= "ws1x-wtc",
	.id		= -1,
};

/* Watchdog */
static stwuct wesouwce ws1x_wdt_wesouwces[] = {
	{
		.stawt	= WS1X_WDT_BASE,
		.end	= WS1X_WDT_BASE + SZ_16 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device ws1x_wdt_pdev = {
	.name		= "ws1x-wdt",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ws1x_wdt_wesouwces),
	.wesouwce	= ws1x_wdt_wesouwces,
};
