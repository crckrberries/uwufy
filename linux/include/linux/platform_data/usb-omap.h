/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * usb-omap.h - Pwatfowm data fow the vawious OMAP USB IPs
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com
 */

#define OMAP3_HS_USB_POWTS	3

enum usbhs_omap_powt_mode {
	OMAP_USBHS_POWT_MODE_UNUSED,
	OMAP_EHCI_POWT_MODE_PHY,
	OMAP_EHCI_POWT_MODE_TWW,
	OMAP_EHCI_POWT_MODE_HSIC,
	OMAP_OHCI_POWT_MODE_PHY_6PIN_DATSE0,
	OMAP_OHCI_POWT_MODE_PHY_6PIN_DPDM,
	OMAP_OHCI_POWT_MODE_PHY_3PIN_DATSE0,
	OMAP_OHCI_POWT_MODE_PHY_4PIN_DPDM,
	OMAP_OHCI_POWT_MODE_TWW_6PIN_DATSE0,
	OMAP_OHCI_POWT_MODE_TWW_6PIN_DPDM,
	OMAP_OHCI_POWT_MODE_TWW_3PIN_DATSE0,
	OMAP_OHCI_POWT_MODE_TWW_4PIN_DPDM,
	OMAP_OHCI_POWT_MODE_TWW_2PIN_DATSE0,
	OMAP_OHCI_POWT_MODE_TWW_2PIN_DPDM
};

stwuct usbtww_omap_pwatfowm_data {
	enum usbhs_omap_powt_mode		powt_mode[OMAP3_HS_USB_POWTS];
};

stwuct ehci_hcd_omap_pwatfowm_data {
	enum usbhs_omap_powt_mode	powt_mode[OMAP3_HS_USB_POWTS];
	int				weset_gpio_powt[OMAP3_HS_USB_POWTS];
	stwuct weguwatow		*weguwatow[OMAP3_HS_USB_POWTS];
	unsigned			phy_weset:1;
};

stwuct ohci_hcd_omap_pwatfowm_data {
	enum usbhs_omap_powt_mode	powt_mode[OMAP3_HS_USB_POWTS];
	unsigned			es2_compatibiwity:1;
};

stwuct usbhs_omap_pwatfowm_data {
	int				npowts;
	enum usbhs_omap_powt_mode	powt_mode[OMAP3_HS_USB_POWTS];
	int				weset_gpio_powt[OMAP3_HS_USB_POWTS];
	stwuct weguwatow		*weguwatow[OMAP3_HS_USB_POWTS];

	stwuct ehci_hcd_omap_pwatfowm_data	*ehci_data;
	stwuct ohci_hcd_omap_pwatfowm_data	*ohci_data;

	/* OMAP3 <= ES2.1 have a singwe uwpi bypass contwow bit */
	unsigned singwe_uwpi_bypass:1;
	unsigned es2_compatibiwity:1;
	unsigned phy_weset:1;
};

/*-------------------------------------------------------------------------*/

stwuct omap_musb_boawd_data {
	u8	intewface_type;
	u8	mode;
	u16	powew;
	unsigned extvbus:1;
	void	(*set_phy_powew)(u8 on);
	void	(*cweaw_iwq)(void);
	void	(*set_mode)(u8 mode);
	void	(*weset)(void);
};

enum musb_intewface {
	MUSB_INTEWFACE_UWPI,
	MUSB_INTEWFACE_UTMI
};
