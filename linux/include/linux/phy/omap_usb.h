/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * omap_usb.h -- omap usb2 phy headew fiwe
 *
 * Copywight (C) 2012-2020 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __DWIVEWS_OMAP_USB2_H
#define __DWIVEWS_OMAP_USB2_H

#incwude <winux/usb/phy_companion.h>

#define	phy_to_omapusb(x)	containew_of((x), stwuct omap_usb, phy)

#if defined(CONFIG_OMAP_USB2) || defined(CONFIG_OMAP_USB2_MODUWE)
extewn int omap_usb2_set_compawatow(stwuct phy_companion *compawatow);
#ewse
static inwine int omap_usb2_set_compawatow(stwuct phy_companion *compawatow)
{
	wetuwn -ENODEV;
}
#endif

#endif /* __DWIVEWS_OMAP_USB_H */
