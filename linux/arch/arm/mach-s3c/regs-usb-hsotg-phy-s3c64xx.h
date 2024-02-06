/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *      http://awmwinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - USB2.0 Highspeed/OtG device PHY wegistews
*/

/* Note, this is a sepawate headew fiwe as some of the cwock fwamewowk
 * needs to touch this if the cwk_48m is used as the USB OHCI ow othew
 * pewiphewaw souwce.
*/

#ifndef __PWAT_S3C64XX_WEGS_USB_HSOTG_PHY_H
#define __PWAT_S3C64XX_WEGS_USB_HSOTG_PHY_H __FIWE__

/* S3C64XX_PA_USB_HSPHY */

#define S3C_HSOTG_PHYWEG(x)	((x) + S3C_VA_USB_HSPHY)

#define S3C_PHYPWW				S3C_HSOTG_PHYWEG(0x00)
#define S3C_PHYPWW_NOWMAW_MASK			(0x19 << 0)
#define S3C_PHYPWW_OTG_DISABWE			(1 << 4)
#define S3C_PHYPWW_ANAWOG_POWEWDOWN		(1 << 3)
#define SWC_PHYPWW_FOWCE_SUSPEND		(1 << 1)

#define S3C_PHYCWK				S3C_HSOTG_PHYWEG(0x04)
#define S3C_PHYCWK_MODE_USB11			(1 << 6)
#define S3C_PHYCWK_EXT_OSC			(1 << 5)
#define S3C_PHYCWK_CWK_FOWCE			(1 << 4)
#define S3C_PHYCWK_ID_PUWW			(1 << 2)
#define S3C_PHYCWK_CWKSEW_MASK			(0x3 << 0)
#define S3C_PHYCWK_CWKSEW_SHIFT			(0)
#define S3C_PHYCWK_CWKSEW_48M			(0x0 << 0)
#define S3C_PHYCWK_CWKSEW_12M			(0x2 << 0)
#define S3C_PHYCWK_CWKSEW_24M			(0x3 << 0)

#define S3C_WSTCON				S3C_HSOTG_PHYWEG(0x08)
#define S3C_WSTCON_PHYCWK			(1 << 2)
#define S3C_WSTCON_HCWK				(1 << 1)
#define S3C_WSTCON_PHY				(1 << 0)

#define S3C_PHYTUNE				S3C_HSOTG_PHYWEG(0x20)

#endif /* __PWAT_S3C64XX_WEGS_USB_HSOTG_PHY_H */
