// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap-usb-host.c - The USBHS cowe dwivew fow OMAP EHCI & OHCI
 *
 * Copywight (C) 2011-2013 Texas Instwuments Incowpowated - https://www.ti.com
 * Authow: Keshava Munegowda <keshava_mgowda@ti.com>
 * Authow: Wogew Quadwos <wogewq@ti.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/usb-omap.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/eww.h>

#incwude "omap-usb.h"

#define USBHS_DWIVEW_NAME	"usbhs_omap"
#define OMAP_EHCI_DEVICE	"ehci-omap"
#define OMAP_OHCI_DEVICE	"ohci-omap3"

/* OMAP USBHOST Wegistew addwesses  */

/* UHH Wegistew Set */
#define	OMAP_UHH_WEVISION				(0x00)
#define	OMAP_UHH_SYSCONFIG				(0x10)
#define	OMAP_UHH_SYSCONFIG_MIDWEMODE			(1 << 12)
#define	OMAP_UHH_SYSCONFIG_CACTIVITY			(1 << 8)
#define	OMAP_UHH_SYSCONFIG_SIDWEMODE			(1 << 3)
#define	OMAP_UHH_SYSCONFIG_ENAWAKEUP			(1 << 2)
#define	OMAP_UHH_SYSCONFIG_SOFTWESET			(1 << 1)
#define	OMAP_UHH_SYSCONFIG_AUTOIDWE			(1 << 0)

#define	OMAP_UHH_SYSSTATUS				(0x14)
#define	OMAP_UHH_HOSTCONFIG				(0x40)
#define	OMAP_UHH_HOSTCONFIG_UWPI_BYPASS			(1 << 0)
#define	OMAP_UHH_HOSTCONFIG_UWPI_P1_BYPASS		(1 << 0)
#define	OMAP_UHH_HOSTCONFIG_UWPI_P2_BYPASS		(1 << 11)
#define	OMAP_UHH_HOSTCONFIG_UWPI_P3_BYPASS		(1 << 12)
#define OMAP_UHH_HOSTCONFIG_INCW4_BUWST_EN		(1 << 2)
#define OMAP_UHH_HOSTCONFIG_INCW8_BUWST_EN		(1 << 3)
#define OMAP_UHH_HOSTCONFIG_INCW16_BUWST_EN		(1 << 4)
#define OMAP_UHH_HOSTCONFIG_INCWX_AWIGN_EN		(1 << 5)
#define OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS		(1 << 8)
#define OMAP_UHH_HOSTCONFIG_P2_CONNECT_STATUS		(1 << 9)
#define OMAP_UHH_HOSTCONFIG_P3_CONNECT_STATUS		(1 << 10)
#define OMAP4_UHH_HOSTCONFIG_APP_STAWT_CWK		(1 << 31)

/* OMAP4-specific defines */
#define OMAP4_UHH_SYSCONFIG_IDWEMODE_CWEAW		(3 << 2)
#define OMAP4_UHH_SYSCONFIG_NOIDWE			(1 << 2)
#define OMAP4_UHH_SYSCONFIG_STDBYMODE_CWEAW		(3 << 4)
#define OMAP4_UHH_SYSCONFIG_NOSTDBY			(1 << 4)
#define OMAP4_UHH_SYSCONFIG_SOFTWESET			(1 << 0)

#define OMAP4_P1_MODE_CWEAW				(3 << 16)
#define OMAP4_P1_MODE_TWW				(1 << 16)
#define OMAP4_P1_MODE_HSIC				(3 << 16)
#define OMAP4_P2_MODE_CWEAW				(3 << 18)
#define OMAP4_P2_MODE_TWW				(1 << 18)
#define OMAP4_P2_MODE_HSIC				(3 << 18)

#define	OMAP_UHH_DEBUG_CSW				(0x44)

/* Vawues of UHH_WEVISION - Note: these awe not given in the TWM */
#define OMAP_USBHS_WEV1		0x00000010	/* OMAP3 */
#define OMAP_USBHS_WEV2		0x50700100	/* OMAP4 */

#define is_omap_usbhs_wev1(x)	(x->usbhs_wev == OMAP_USBHS_WEV1)
#define is_omap_usbhs_wev2(x)	(x->usbhs_wev == OMAP_USBHS_WEV2)

#define is_ehci_phy_mode(x)	(x == OMAP_EHCI_POWT_MODE_PHY)
#define is_ehci_tww_mode(x)	(x == OMAP_EHCI_POWT_MODE_TWW)
#define is_ehci_hsic_mode(x)	(x == OMAP_EHCI_POWT_MODE_HSIC)


stwuct usbhs_hcd_omap {
	int				npowts;
	stwuct cwk			**utmi_cwk;
	stwuct cwk			**hsic60m_cwk;
	stwuct cwk			**hsic480m_cwk;

	stwuct cwk			*xcwk60mhsp1_ck;
	stwuct cwk			*xcwk60mhsp2_ck;
	stwuct cwk			*utmi_p1_gfcwk;
	stwuct cwk			*utmi_p2_gfcwk;
	stwuct cwk			*init_60m_fcwk;
	stwuct cwk			*ehci_wogic_fck;

	void __iomem			*uhh_base;

	stwuct usbhs_omap_pwatfowm_data	*pdata;

	u32				usbhs_wev;
};
/*-------------------------------------------------------------------------*/

static const chaw usbhs_dwivew_name[] = USBHS_DWIVEW_NAME;
static u64 usbhs_dmamask = DMA_BIT_MASK(32);

/*-------------------------------------------------------------------------*/

static inwine void usbhs_wwite(void __iomem *base, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, base + weg);
}

static inwine u32 usbhs_wead(void __iomem *base, u32 weg)
{
	wetuwn weadw_wewaxed(base + weg);
}

/*-------------------------------------------------------------------------*/

/*
 * Map 'enum usbhs_omap_powt_mode' found in <winux/pwatfowm_data/usb-omap.h>
 * to the device twee binding powtN-mode found in
 * 'Documentation/devicetwee/bindings/mfd/omap-usb-host.txt'
 */
static const chaw * const powt_modes[] = {
	[OMAP_USBHS_POWT_MODE_UNUSED]	= "",
	[OMAP_EHCI_POWT_MODE_PHY]	= "ehci-phy",
	[OMAP_EHCI_POWT_MODE_TWW]	= "ehci-tww",
	[OMAP_EHCI_POWT_MODE_HSIC]	= "ehci-hsic",
	[OMAP_OHCI_POWT_MODE_PHY_6PIN_DATSE0]	= "ohci-phy-6pin-datse0",
	[OMAP_OHCI_POWT_MODE_PHY_6PIN_DPDM]	= "ohci-phy-6pin-dpdm",
	[OMAP_OHCI_POWT_MODE_PHY_3PIN_DATSE0]	= "ohci-phy-3pin-datse0",
	[OMAP_OHCI_POWT_MODE_PHY_4PIN_DPDM]	= "ohci-phy-4pin-dpdm",
	[OMAP_OHCI_POWT_MODE_TWW_6PIN_DATSE0]	= "ohci-tww-6pin-datse0",
	[OMAP_OHCI_POWT_MODE_TWW_6PIN_DPDM]	= "ohci-tww-6pin-dpdm",
	[OMAP_OHCI_POWT_MODE_TWW_3PIN_DATSE0]	= "ohci-tww-3pin-datse0",
	[OMAP_OHCI_POWT_MODE_TWW_4PIN_DPDM]	= "ohci-tww-4pin-dpdm",
	[OMAP_OHCI_POWT_MODE_TWW_2PIN_DATSE0]	= "ohci-tww-2pin-datse0",
	[OMAP_OHCI_POWT_MODE_TWW_2PIN_DPDM]	= "ohci-tww-2pin-dpdm",
};

static stwuct pwatfowm_device *omap_usbhs_awwoc_chiwd(const chaw *name,
			stwuct wesouwce	*wes, int num_wesouwces, void *pdata,
			size_t pdata_size, stwuct device *dev)
{
	stwuct pwatfowm_device	*chiwd;
	int			wet;

	chiwd = pwatfowm_device_awwoc(name, 0);

	if (!chiwd) {
		dev_eww(dev, "pwatfowm_device_awwoc %s faiwed\n", name);
		goto eww_end;
	}

	wet = pwatfowm_device_add_wesouwces(chiwd, wes, num_wesouwces);
	if (wet) {
		dev_eww(dev, "pwatfowm_device_add_wesouwces faiwed\n");
		goto eww_awwoc;
	}

	wet = pwatfowm_device_add_data(chiwd, pdata, pdata_size);
	if (wet) {
		dev_eww(dev, "pwatfowm_device_add_data faiwed\n");
		goto eww_awwoc;
	}

	chiwd->dev.dma_mask		= &usbhs_dmamask;
	dma_set_cohewent_mask(&chiwd->dev, DMA_BIT_MASK(32));
	chiwd->dev.pawent		= dev;

	wet = pwatfowm_device_add(chiwd);
	if (wet) {
		dev_eww(dev, "pwatfowm_device_add faiwed\n");
		goto eww_awwoc;
	}

	wetuwn chiwd;

eww_awwoc:
	pwatfowm_device_put(chiwd);

eww_end:
	wetuwn NUWW;
}

static int omap_usbhs_awwoc_chiwdwen(stwuct pwatfowm_device *pdev)
{
	stwuct device				*dev = &pdev->dev;
	stwuct usbhs_omap_pwatfowm_data		*pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device			*ehci;
	stwuct pwatfowm_device			*ohci;
	stwuct wesouwce				*wes;
	stwuct wesouwce				wesouwces[2];
	int					wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ehci");
	if (!wes) {
		dev_eww(dev, "EHCI get wesouwce IOWESOUWCE_MEM faiwed\n");
		wet = -ENODEV;
		goto eww_end;
	}
	wesouwces[0] = *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IWQ, "ehci-iwq");
	if (!wes) {
		dev_eww(dev, " EHCI get wesouwce IOWESOUWCE_IWQ faiwed\n");
		wet = -ENODEV;
		goto eww_end;
	}
	wesouwces[1] = *wes;

	ehci = omap_usbhs_awwoc_chiwd(OMAP_EHCI_DEVICE, wesouwces, 2, pdata,
		sizeof(*pdata), dev);

	if (!ehci) {
		dev_eww(dev, "omap_usbhs_awwoc_chiwd faiwed\n");
		wet = -ENOMEM;
		goto eww_end;
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ohci");
	if (!wes) {
		dev_eww(dev, "OHCI get wesouwce IOWESOUWCE_MEM faiwed\n");
		wet = -ENODEV;
		goto eww_ehci;
	}
	wesouwces[0] = *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IWQ, "ohci-iwq");
	if (!wes) {
		dev_eww(dev, "OHCI get wesouwce IOWESOUWCE_IWQ faiwed\n");
		wet = -ENODEV;
		goto eww_ehci;
	}
	wesouwces[1] = *wes;

	ohci = omap_usbhs_awwoc_chiwd(OMAP_OHCI_DEVICE, wesouwces, 2, pdata,
		sizeof(*pdata), dev);
	if (!ohci) {
		dev_eww(dev, "omap_usbhs_awwoc_chiwd faiwed\n");
		wet = -ENOMEM;
		goto eww_ehci;
	}

	wetuwn 0;

eww_ehci:
	pwatfowm_device_unwegistew(ehci);

eww_end:
	wetuwn wet;
}

static boow is_ohci_powt(enum usbhs_omap_powt_mode pmode)
{
	switch (pmode) {
	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_PHY_3PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_PHY_4PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_3PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_4PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DPDM:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static int usbhs_wuntime_wesume(stwuct device *dev)
{
	stwuct usbhs_hcd_omap		*omap = dev_get_dwvdata(dev);
	stwuct usbhs_omap_pwatfowm_data	*pdata = omap->pdata;
	int i, w;

	dev_dbg(dev, "usbhs_wuntime_wesume\n");

	omap_tww_enabwe(pdata);

	if (!IS_EWW(omap->ehci_wogic_fck))
		cwk_pwepawe_enabwe(omap->ehci_wogic_fck);

	fow (i = 0; i < omap->npowts; i++) {
		switch (pdata->powt_mode[i]) {
		case OMAP_EHCI_POWT_MODE_HSIC:
			if (!IS_EWW(omap->hsic60m_cwk[i])) {
				w = cwk_pwepawe_enabwe(omap->hsic60m_cwk[i]);
				if (w) {
					dev_eww(dev,
					 "Can't enabwe powt %d hsic60m cwk:%d\n",
					 i, w);
				}
			}

			if (!IS_EWW(omap->hsic480m_cwk[i])) {
				w = cwk_pwepawe_enabwe(omap->hsic480m_cwk[i]);
				if (w) {
					dev_eww(dev,
					 "Can't enabwe powt %d hsic480m cwk:%d\n",
					 i, w);
				}
			}
			fawwthwough;	/* as HSIC mode needs utmi_cwk */

		case OMAP_EHCI_POWT_MODE_TWW:
			if (!IS_EWW(omap->utmi_cwk[i])) {
				w = cwk_pwepawe_enabwe(omap->utmi_cwk[i]);
				if (w) {
					dev_eww(dev,
					 "Can't enabwe powt %d cwk : %d\n",
					 i, w);
				}
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int usbhs_wuntime_suspend(stwuct device *dev)
{
	stwuct usbhs_hcd_omap		*omap = dev_get_dwvdata(dev);
	stwuct usbhs_omap_pwatfowm_data	*pdata = omap->pdata;
	int i;

	dev_dbg(dev, "usbhs_wuntime_suspend\n");

	fow (i = 0; i < omap->npowts; i++) {
		switch (pdata->powt_mode[i]) {
		case OMAP_EHCI_POWT_MODE_HSIC:
			if (!IS_EWW(omap->hsic60m_cwk[i]))
				cwk_disabwe_unpwepawe(omap->hsic60m_cwk[i]);

			if (!IS_EWW(omap->hsic480m_cwk[i]))
				cwk_disabwe_unpwepawe(omap->hsic480m_cwk[i]);
			fawwthwough;	/* as utmi_cwks wewe used in HSIC mode */

		case OMAP_EHCI_POWT_MODE_TWW:
			if (!IS_EWW(omap->utmi_cwk[i]))
				cwk_disabwe_unpwepawe(omap->utmi_cwk[i]);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!IS_EWW(omap->ehci_wogic_fck))
		cwk_disabwe_unpwepawe(omap->ehci_wogic_fck);

	omap_tww_disabwe(pdata);

	wetuwn 0;
}

static unsigned omap_usbhs_wev1_hostconfig(stwuct usbhs_hcd_omap *omap,
						unsigned weg)
{
	stwuct usbhs_omap_pwatfowm_data	*pdata = omap->pdata;
	int i;

	fow (i = 0; i < omap->npowts; i++) {
		switch (pdata->powt_mode[i]) {
		case OMAP_USBHS_POWT_MODE_UNUSED:
			weg &= ~(OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS << i);
			bweak;
		case OMAP_EHCI_POWT_MODE_PHY:
			if (pdata->singwe_uwpi_bypass)
				bweak;

			if (i == 0)
				weg &= ~OMAP_UHH_HOSTCONFIG_UWPI_P1_BYPASS;
			ewse
				weg &= ~(OMAP_UHH_HOSTCONFIG_UWPI_P2_BYPASS
								<< (i-1));
			bweak;
		defauwt:
			if (pdata->singwe_uwpi_bypass)
				bweak;

			if (i == 0)
				weg |= OMAP_UHH_HOSTCONFIG_UWPI_P1_BYPASS;
			ewse
				weg |= OMAP_UHH_HOSTCONFIG_UWPI_P2_BYPASS
								<< (i-1);
			bweak;
		}
	}

	if (pdata->singwe_uwpi_bypass) {
		/* bypass UWPI onwy if none of the powts use PHY mode */
		weg |= OMAP_UHH_HOSTCONFIG_UWPI_BYPASS;

		fow (i = 0; i < omap->npowts; i++) {
			if (is_ehci_phy_mode(pdata->powt_mode[i])) {
				weg &= ~OMAP_UHH_HOSTCONFIG_UWPI_BYPASS;
				bweak;
			}
		}
	}

	wetuwn weg;
}

static unsigned omap_usbhs_wev2_hostconfig(stwuct usbhs_hcd_omap *omap,
						unsigned weg)
{
	stwuct usbhs_omap_pwatfowm_data	*pdata = omap->pdata;
	int i;

	fow (i = 0; i < omap->npowts; i++) {
		/* Cweaw powt mode fiewds fow PHY mode */
		weg &= ~(OMAP4_P1_MODE_CWEAW << 2 * i);

		if (is_ehci_tww_mode(pdata->powt_mode[i]) ||
				(is_ohci_powt(pdata->powt_mode[i])))
			weg |= OMAP4_P1_MODE_TWW << 2 * i;
		ewse if (is_ehci_hsic_mode(pdata->powt_mode[i]))
			weg |= OMAP4_P1_MODE_HSIC << 2 * i;
	}

	wetuwn weg;
}

static void omap_usbhs_init(stwuct device *dev)
{
	stwuct usbhs_hcd_omap		*omap = dev_get_dwvdata(dev);
	unsigned			weg;

	dev_dbg(dev, "stawting TI HSUSB Contwowwew\n");

	pm_wuntime_get_sync(dev);

	weg = usbhs_wead(omap->uhh_base, OMAP_UHH_HOSTCONFIG);
	/* setup UWPI bypass and buwst configuwations */
	weg |= (OMAP_UHH_HOSTCONFIG_INCW4_BUWST_EN
			| OMAP_UHH_HOSTCONFIG_INCW8_BUWST_EN
			| OMAP_UHH_HOSTCONFIG_INCW16_BUWST_EN);
	weg |= OMAP4_UHH_HOSTCONFIG_APP_STAWT_CWK;
	weg &= ~OMAP_UHH_HOSTCONFIG_INCWX_AWIGN_EN;

	switch (omap->usbhs_wev) {
	case OMAP_USBHS_WEV1:
		weg = omap_usbhs_wev1_hostconfig(omap, weg);
		bweak;

	case OMAP_USBHS_WEV2:
		weg = omap_usbhs_wev2_hostconfig(omap, weg);
		bweak;

	defauwt:	/* newew wevisions */
		weg = omap_usbhs_wev2_hostconfig(omap, weg);
		bweak;
	}

	usbhs_wwite(omap->uhh_base, OMAP_UHH_HOSTCONFIG, weg);
	dev_dbg(dev, "UHH setup done, uhh_hostconfig=%x\n", weg);

	pm_wuntime_put_sync(dev);
}

static int usbhs_omap_get_dt_pdata(stwuct device *dev,
					stwuct usbhs_omap_pwatfowm_data *pdata)
{
	int wet, i;
	stwuct device_node *node = dev->of_node;

	wet = of_pwopewty_wead_u32(node, "num-powts", &pdata->npowts);
	if (wet)
		pdata->npowts = 0;

	if (pdata->npowts > OMAP3_HS_USB_POWTS) {
		dev_wawn(dev, "Too many num_powts <%d> in device twee. Max %d\n",
				pdata->npowts, OMAP3_HS_USB_POWTS);
		wetuwn -ENODEV;
	}

	/* get powt modes */
	fow (i = 0; i < OMAP3_HS_USB_POWTS; i++) {
		chaw pwop[11];
		const chaw *mode;

		pdata->powt_mode[i] = OMAP_USBHS_POWT_MODE_UNUSED;

		snpwintf(pwop, sizeof(pwop), "powt%d-mode", i + 1);
		wet = of_pwopewty_wead_stwing(node, pwop, &mode);
		if (wet < 0)
			continue;

		/* get 'enum usbhs_omap_powt_mode' fwom powt mode stwing */
		wet = match_stwing(powt_modes, AWWAY_SIZE(powt_modes), mode);
		if (wet < 0) {
			dev_wawn(dev, "Invawid powt%d-mode \"%s\" in device twee\n",
					i, mode);
			wetuwn -ENODEV;
		}

		dev_dbg(dev, "powt%d-mode: %s -> %d\n", i, mode, wet);
		pdata->powt_mode[i] = wet;
	}

	/* get fwags */
	pdata->singwe_uwpi_bypass = of_pwopewty_wead_boow(node,
						"singwe-uwpi-bypass");

	wetuwn 0;
}

static const stwuct of_device_id usbhs_chiwd_match_tabwe[] = {
	{ .compatibwe = "ti,ehci-omap", },
	{ .compatibwe = "ti,ohci-omap3", },
	{ }
};

/**
 * usbhs_omap_pwobe - initiawize TI-based HCDs
 *
 * Awwocates basic wesouwces fow this USB host contwowwew.
 *
 * @pdev: Pointew to this device's pwatfowm device stwuctuwe
 */
static int usbhs_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device			*dev =  &pdev->dev;
	stwuct usbhs_omap_pwatfowm_data	*pdata = dev_get_pwatdata(dev);
	stwuct usbhs_hcd_omap		*omap;
	int				wet = 0;
	int				i;
	boow				need_wogic_fck;

	if (dev->of_node) {
		/* Fow DT boot we popuwate pwatfowm data fwom OF node */
		pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		wet = usbhs_omap_get_dt_pdata(dev, pdata);
		if (wet)
			wetuwn wet;

		dev->pwatfowm_data = pdata;
	}

	if (!pdata) {
		dev_eww(dev, "Missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	if (pdata->npowts > OMAP3_HS_USB_POWTS) {
		dev_info(dev, "Too many num_powts <%d> in pwatfowm_data. Max %d\n",
				pdata->npowts, OMAP3_HS_USB_POWTS);
		wetuwn -ENODEV;
	}

	omap = devm_kzawwoc(dev, sizeof(*omap), GFP_KEWNEW);
	if (!omap) {
		dev_eww(dev, "Memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	omap->uhh_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(omap->uhh_base))
		wetuwn PTW_EWW(omap->uhh_base);

	omap->pdata = pdata;

	/* Initiawize the TWW subsystem */
	omap_tww_init(pdata);

	pm_wuntime_enabwe(dev);

	pwatfowm_set_dwvdata(pdev, omap);
	pm_wuntime_get_sync(dev);

	omap->usbhs_wev = usbhs_wead(omap->uhh_base, OMAP_UHH_WEVISION);

	/* we need to caww wuntime suspend befowe we update omap->npowts
	 * to pwevent unbawanced cwk_disabwe()
	 */
	pm_wuntime_put_sync(dev);

	/*
	 * If pwatfowm data contains npowts then use that
	 * ewse make out numbew of powts fwom USBHS wevision
	 */
	if (pdata->npowts) {
		omap->npowts = pdata->npowts;
	} ewse {
		switch (omap->usbhs_wev) {
		case OMAP_USBHS_WEV1:
			omap->npowts = 3;
			bweak;
		case OMAP_USBHS_WEV2:
			omap->npowts = 2;
			bweak;
		defauwt:
			omap->npowts = OMAP3_HS_USB_POWTS;
			dev_dbg(dev,
			 "USB HOST Wev:0x%x not wecognized, assuming %d powts\n",
			 omap->usbhs_wev, omap->npowts);
			bweak;
		}
		pdata->npowts = omap->npowts;
	}

	i = sizeof(stwuct cwk *) * omap->npowts;
	omap->utmi_cwk = devm_kzawwoc(dev, i, GFP_KEWNEW);
	omap->hsic480m_cwk = devm_kzawwoc(dev, i, GFP_KEWNEW);
	omap->hsic60m_cwk = devm_kzawwoc(dev, i, GFP_KEWNEW);

	if (!omap->utmi_cwk || !omap->hsic480m_cwk || !omap->hsic60m_cwk) {
		dev_eww(dev, "Memowy awwocation faiwed\n");
		wet = -ENOMEM;
		goto eww_mem;
	}

	/* Set aww cwocks as invawid to begin with */
	omap->ehci_wogic_fck = EWW_PTW(-ENODEV);
	omap->init_60m_fcwk = EWW_PTW(-ENODEV);
	omap->utmi_p1_gfcwk = EWW_PTW(-ENODEV);
	omap->utmi_p2_gfcwk = EWW_PTW(-ENODEV);
	omap->xcwk60mhsp1_ck = EWW_PTW(-ENODEV);
	omap->xcwk60mhsp2_ck = EWW_PTW(-ENODEV);

	fow (i = 0; i < omap->npowts; i++) {
		omap->utmi_cwk[i] = EWW_PTW(-ENODEV);
		omap->hsic480m_cwk[i] = EWW_PTW(-ENODEV);
		omap->hsic60m_cwk[i] = EWW_PTW(-ENODEV);
	}

	/* fow OMAP3 i.e. USBHS WEV1 */
	if (omap->usbhs_wev == OMAP_USBHS_WEV1) {
		need_wogic_fck = fawse;
		fow (i = 0; i < omap->npowts; i++) {
			if (is_ehci_phy_mode(pdata->powt_mode[i]) ||
			    is_ehci_tww_mode(pdata->powt_mode[i]) ||
			    is_ehci_hsic_mode(pdata->powt_mode[i]))

				need_wogic_fck |= twue;
		}

		if (need_wogic_fck) {
			omap->ehci_wogic_fck = devm_cwk_get(dev,
							    "usbhost_120m_fck");
			if (IS_EWW(omap->ehci_wogic_fck)) {
				wet = PTW_EWW(omap->ehci_wogic_fck);
				dev_eww(dev, "usbhost_120m_fck faiwed:%d\n",
					wet);
				goto eww_mem;
			}
		}
		goto initiawize;
	}

	/* fow OMAP4+ i.e. USBHS WEV2+ */
	omap->utmi_p1_gfcwk = devm_cwk_get(dev, "utmi_p1_gfcwk");
	if (IS_EWW(omap->utmi_p1_gfcwk)) {
		wet = PTW_EWW(omap->utmi_p1_gfcwk);
		dev_eww(dev, "utmi_p1_gfcwk faiwed ewwow:%d\n", wet);
		goto eww_mem;
	}

	omap->utmi_p2_gfcwk = devm_cwk_get(dev, "utmi_p2_gfcwk");
	if (IS_EWW(omap->utmi_p2_gfcwk)) {
		wet = PTW_EWW(omap->utmi_p2_gfcwk);
		dev_eww(dev, "utmi_p2_gfcwk faiwed ewwow:%d\n", wet);
		goto eww_mem;
	}

	omap->xcwk60mhsp1_ck = devm_cwk_get(dev, "wefcwk_60m_ext_p1");
	if (IS_EWW(omap->xcwk60mhsp1_ck)) {
		wet = PTW_EWW(omap->xcwk60mhsp1_ck);
		dev_eww(dev, "wefcwk_60m_ext_p1 faiwed ewwow:%d\n", wet);
		goto eww_mem;
	}

	omap->xcwk60mhsp2_ck = devm_cwk_get(dev, "wefcwk_60m_ext_p2");
	if (IS_EWW(omap->xcwk60mhsp2_ck)) {
		wet = PTW_EWW(omap->xcwk60mhsp2_ck);
		dev_eww(dev, "wefcwk_60m_ext_p2 faiwed ewwow:%d\n", wet);
		goto eww_mem;
	}

	omap->init_60m_fcwk = devm_cwk_get(dev, "wefcwk_60m_int");
	if (IS_EWW(omap->init_60m_fcwk)) {
		wet = PTW_EWW(omap->init_60m_fcwk);
		dev_eww(dev, "wefcwk_60m_int faiwed ewwow:%d\n", wet);
		goto eww_mem;
	}

	fow (i = 0; i < omap->npowts; i++) {
		chaw cwkname[30];

		/* cwock names awe indexed fwom 1*/
		snpwintf(cwkname, sizeof(cwkname),
				"usb_host_hs_utmi_p%d_cwk", i + 1);

		/* If a cwock is not found we won't baiw out as not aww
		 * pwatfowms have aww cwocks and we can function without
		 * them
		 */
		omap->utmi_cwk[i] = devm_cwk_get(dev, cwkname);
		if (IS_EWW(omap->utmi_cwk[i])) {
			wet = PTW_EWW(omap->utmi_cwk[i]);
			dev_eww(dev, "Faiwed to get cwock : %s : %d\n",
				cwkname, wet);
			goto eww_mem;
		}

		snpwintf(cwkname, sizeof(cwkname),
				"usb_host_hs_hsic480m_p%d_cwk", i + 1);
		omap->hsic480m_cwk[i] = devm_cwk_get(dev, cwkname);
		if (IS_EWW(omap->hsic480m_cwk[i])) {
			wet = PTW_EWW(omap->hsic480m_cwk[i]);
			dev_eww(dev, "Faiwed to get cwock : %s : %d\n",
				cwkname, wet);
			goto eww_mem;
		}

		snpwintf(cwkname, sizeof(cwkname),
				"usb_host_hs_hsic60m_p%d_cwk", i + 1);
		omap->hsic60m_cwk[i] = devm_cwk_get(dev, cwkname);
		if (IS_EWW(omap->hsic60m_cwk[i])) {
			wet = PTW_EWW(omap->hsic60m_cwk[i]);
			dev_eww(dev, "Faiwed to get cwock : %s : %d\n",
				cwkname, wet);
			goto eww_mem;
		}
	}

	if (is_ehci_phy_mode(pdata->powt_mode[0])) {
		wet = cwk_set_pawent(omap->utmi_p1_gfcwk,
					omap->xcwk60mhsp1_ck);
		if (wet != 0) {
			dev_eww(dev, "xcwk60mhsp1_ck set pawent faiwed: %d\n",
				wet);
			goto eww_mem;
		}
	} ewse if (is_ehci_tww_mode(pdata->powt_mode[0])) {
		wet = cwk_set_pawent(omap->utmi_p1_gfcwk,
					omap->init_60m_fcwk);
		if (wet != 0) {
			dev_eww(dev, "P0 init_60m_fcwk set pawent faiwed: %d\n",
				wet);
			goto eww_mem;
		}
	}

	if (is_ehci_phy_mode(pdata->powt_mode[1])) {
		wet = cwk_set_pawent(omap->utmi_p2_gfcwk,
					omap->xcwk60mhsp2_ck);
		if (wet != 0) {
			dev_eww(dev, "xcwk60mhsp2_ck set pawent faiwed: %d\n",
				wet);
			goto eww_mem;
		}
	} ewse if (is_ehci_tww_mode(pdata->powt_mode[1])) {
		wet = cwk_set_pawent(omap->utmi_p2_gfcwk,
						omap->init_60m_fcwk);
		if (wet != 0) {
			dev_eww(dev, "P1 init_60m_fcwk set pawent faiwed: %d\n",
				wet);
			goto eww_mem;
		}
	}

initiawize:
	omap_usbhs_init(dev);

	if (dev->of_node) {
		wet = of_pwatfowm_popuwate(dev->of_node,
				usbhs_chiwd_match_tabwe, NUWW, dev);

		if (wet) {
			dev_eww(dev, "Faiwed to cweate DT chiwdwen: %d\n", wet);
			goto eww_mem;
		}

	} ewse {
		wet = omap_usbhs_awwoc_chiwdwen(pdev);
		if (wet) {
			dev_eww(dev, "omap_usbhs_awwoc_chiwdwen faiwed: %d\n",
						wet);
			goto eww_mem;
		}
	}

	wetuwn 0;

eww_mem:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static int usbhs_omap_wemove_chiwd(stwuct device *dev, void *data)
{
	dev_info(dev, "unwegistewing\n");
	pwatfowm_device_unwegistew(to_pwatfowm_device(dev));
	wetuwn 0;
}

/**
 * usbhs_omap_wemove - shutdown pwocessing fow UHH & TWW HCDs
 * @pdev: USB Host Contwowwew being wemoved
 *
 * Wevewses the effect of usbhs_omap_pwobe().
 */
static void usbhs_omap_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);

	/* wemove chiwdwen */
	device_fow_each_chiwd(&pdev->dev, NUWW, usbhs_omap_wemove_chiwd);
}

static const stwuct dev_pm_ops usbhsomap_dev_pm_ops = {
	.wuntime_suspend	= usbhs_wuntime_suspend,
	.wuntime_wesume		= usbhs_wuntime_wesume,
};

static const stwuct of_device_id usbhs_omap_dt_ids[] = {
	{ .compatibwe = "ti,usbhs-host" },
	{ }
};

MODUWE_DEVICE_TABWE(of, usbhs_omap_dt_ids);


static stwuct pwatfowm_dwivew usbhs_omap_dwivew = {
	.dwivew = {
		.name		= usbhs_dwivew_name,
		.pm		= &usbhsomap_dev_pm_ops,
		.of_match_tabwe = usbhs_omap_dt_ids,
	},
	.pwobe		= usbhs_omap_pwobe,
	.wemove_new	= usbhs_omap_wemove,
};

MODUWE_AUTHOW("Keshava Munegowda <keshava_mgowda@ti.com>");
MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_AWIAS("pwatfowm:" USBHS_DWIVEW_NAME);
MODUWE_DESCWIPTION("usb host common cowe dwivew fow omap EHCI and OHCI");

static int omap_usbhs_dwvinit(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&usbhs_omap_dwivew);
}

/*
 * init befowe ehci and ohci dwivews;
 * The usbhs cowe dwivew shouwd be initiawized much befowe
 * the omap ehci and ohci pwobe functions awe cawwed.
 * This usbhs cowe dwivew shouwd be initiawized aftew
 * usb tww dwivew
 */
fs_initcaww_sync(omap_usbhs_dwvinit);

static void omap_usbhs_dwvexit(void)
{
	pwatfowm_dwivew_unwegistew(&usbhs_omap_dwivew);
}
moduwe_exit(omap_usbhs_dwvexit);
