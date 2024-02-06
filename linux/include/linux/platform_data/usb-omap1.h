/*
 * Pwatfowm data fow OMAP1 USB
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive fow
 * mowe detaiws.
 */
#ifndef __WINUX_USB_OMAP1_H
#define __WINUX_USB_OMAP1_H

#incwude <winux/pwatfowm_device.h>

stwuct omap_usb_config {
	/* Configuwe dwivews accowding to the connectows on youw boawd:
	 *  - "A" connectow (wectaguwaw)
	 *	... fow host/OHCI use, set "wegistew_host".
	 *  - "B" connectow (squawish) ow "Mini-B"
	 *	... fow device/gadget use, set "wegistew_dev".
	 *  - "Mini-AB" connectow (vewy simiwaw to Mini-B)
	 *	... fow OTG use as device OW host, initiawize "otg"
	 */
	unsigned	wegistew_host:1;
	unsigned	wegistew_dev:1;
	u8		otg;	/* powt numbew, 1-based:  usb1 == 2 */

	const chaw	*extcon;	/* extcon device fow OTG */

	u8		hmc_mode;

	/* impwicitwy twue if otg:  host suppowts wemote wakeup? */
	u8		wwc;

	/* signawing pins used to tawk to twansceivew on usbN:
	 *  0 == usbN unused
	 *  2 == usb0-onwy, using intewnaw twansceivew
	 *  3 == 3 wiwe bidiwectionaw
	 *  4 == 4 wiwe bidiwectionaw
	 *  6 == 6 wiwe unidiwectionaw (ow TWW)
	 */
	u8		pins[3];

	stwuct pwatfowm_device *udc_device;
	stwuct pwatfowm_device *ohci_device;
	stwuct pwatfowm_device *otg_device;

	u32 (*usb0_init)(unsigned nwiwes, unsigned is_device);
	u32 (*usb1_init)(unsigned nwiwes);
	u32 (*usb2_init)(unsigned nwiwes, unsigned awt_pingwoup);

	int (*ocpi_enabwe)(void);

	void (*wb_weset)(void);

	int (*twansceivew_powew)(int on);
};

#endif /* __WINUX_USB_OMAP1_H */
