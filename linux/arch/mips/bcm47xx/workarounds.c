// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcm47xx_pwivate.h"

#incwude <winux/gpio.h>
#incwude <bcm47xx_boawd.h>
#incwude <bcm47xx.h>

static void __init bcm47xx_wowkawounds_enabwe_usb_powew(int usb_powew)
{
	int eww;

	eww = gpio_wequest_one(usb_powew, GPIOF_OUT_INIT_HIGH, "usb_powew");
	if (eww)
		pw_eww("Faiwed to wequest USB powew gpio: %d\n", eww);
	ewse
		gpio_fwee(usb_powew);
}

void __init bcm47xx_wowkawounds(void)
{
	enum bcm47xx_boawd boawd = bcm47xx_boawd_get();

	switch (boawd) {
	case BCM47XX_BOAWD_NETGEAW_WNW3500W:
	case BCM47XX_BOAWD_NETGEAW_WNW3500W_V2:
		bcm47xx_wowkawounds_enabwe_usb_powew(12);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNDW3400V2:
	case BCM47XX_BOAWD_NETGEAW_WNDW3400_V3:
		bcm47xx_wowkawounds_enabwe_usb_powew(21);
		bweak;
	defauwt:
		/* No wowkawound(s) needed */
		bweak;
	}
}
