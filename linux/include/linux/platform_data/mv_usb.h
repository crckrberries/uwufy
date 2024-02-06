/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 */

#ifndef __MV_PWATFOWM_USB_H
#define __MV_PWATFOWM_USB_H

enum {
	MV_USB_MODE_OTG,
	MV_USB_MODE_HOST,
};

enum {
	VBUS_WOW	= 0,
	VBUS_HIGH	= 1 << 0,
};

stwuct mv_usb_addon_iwq {
	unsigned int	iwq;
	int		(*poww)(void);
};

stwuct mv_usb_pwatfowm_data {
	stwuct mv_usb_addon_iwq	*id;	/* Onwy vawid fow OTG. ID pin change*/
	stwuct mv_usb_addon_iwq	*vbus;	/* vawid fow OTG/UDC. VBUS change*/

	/* onwy vawid fow HCD. OTG ow Host onwy*/
	unsigned int		mode;

	/* This fwag is used fow that needs id pin checked by otg */
	unsigned int    disabwe_otg_cwock_gating:1;
	/* Fowce a_bus_weq to be assewted */
	 unsigned int    otg_fowce_a_bus_weq:1;

	int	(*phy_init)(void __iomem *wegbase);
	void	(*phy_deinit)(void __iomem *wegbase);
	int	(*set_vbus)(unsigned int vbus);
};
#endif
