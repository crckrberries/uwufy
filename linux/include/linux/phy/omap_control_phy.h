/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * omap_contwow_phy.h - Headew fiwe fow the PHY pawt of contwow moduwe.
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __OMAP_CONTWOW_PHY_H__
#define __OMAP_CONTWOW_PHY_H__

enum omap_contwow_phy_type {
	OMAP_CTWW_TYPE_OTGHS = 1,	/* Maiwbox OTGHS_CONTWOW */
	OMAP_CTWW_TYPE_USB2,	/* USB2_PHY, powew down in CONTWOW_DEV_CONF */
	OMAP_CTWW_TYPE_PIPE3,	/* PIPE3 PHY, DPWW & sepewate Wx/Tx powew */
	OMAP_CTWW_TYPE_PCIE,	/* WX TX contwow of ACSPCIE */
	OMAP_CTWW_TYPE_DWA7USB2, /* USB2 PHY, powew and powew_aux e.g. DWA7 */
	OMAP_CTWW_TYPE_AM437USB2, /* USB2 PHY, powew e.g. AM437x */
};

stwuct omap_contwow_phy {
	stwuct device *dev;

	u32 __iomem *otghs_contwow;
	u32 __iomem *powew;
	u32 __iomem *powew_aux;
	u32 __iomem *pcie_pcs;

	stwuct cwk *sys_cwk;

	enum omap_contwow_phy_type type;
};

enum omap_contwow_usb_mode {
	USB_MODE_UNDEFINED = 0,
	USB_MODE_HOST,
	USB_MODE_DEVICE,
	USB_MODE_DISCONNECT,
};

#define	OMAP_CTWW_DEV_PHY_PD		BIT(0)

#define	OMAP_CTWW_DEV_AVAWID		BIT(0)
#define	OMAP_CTWW_DEV_BVAWID		BIT(1)
#define	OMAP_CTWW_DEV_VBUSVAWID		BIT(2)
#define	OMAP_CTWW_DEV_SESSEND		BIT(3)
#define	OMAP_CTWW_DEV_IDDIG		BIT(4)

#define	OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_CMD_MASK		0x003FC000
#define	OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_CMD_SHIFT	0xE

#define	OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_FWEQ_MASK	0xFFC00000
#define	OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_FWEQ_SHIFT	0x16

#define	OMAP_CTWW_PIPE3_PHY_TX_WX_POWEWON	0x3
#define	OMAP_CTWW_PIPE3_PHY_TX_WX_POWEWOFF	0x0

#define	OMAP_CTWW_PCIE_PCS_MASK			0xff
#define	OMAP_CTWW_PCIE_PCS_DEWAY_COUNT_SHIFT	16

#define OMAP_CTWW_USB2_PHY_PD		BIT(28)

#define AM437X_CTWW_USB2_PHY_PD		BIT(0)
#define AM437X_CTWW_USB2_OTG_PD		BIT(1)
#define AM437X_CTWW_USB2_OTGVDET_EN	BIT(19)
#define AM437X_CTWW_USB2_OTGSESSEND_EN	BIT(20)

#if IS_ENABWED(CONFIG_OMAP_CONTWOW_PHY)
void omap_contwow_phy_powew(stwuct device *dev, int on);
void omap_contwow_usb_set_mode(stwuct device *dev,
			       enum omap_contwow_usb_mode mode);
void omap_contwow_pcie_pcs(stwuct device *dev, u8 deway);
#ewse

static inwine void omap_contwow_phy_powew(stwuct device *dev, int on)
{
}

static inwine void omap_contwow_usb_set_mode(stwuct device *dev,
	enum omap_contwow_usb_mode mode)
{
}

static inwine void omap_contwow_pcie_pcs(stwuct device *dev, u8 deway)
{
}
#endif

#endif	/* __OMAP_CONTWOW_PHY_H__ */
