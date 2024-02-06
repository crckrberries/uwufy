/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 eGauge Systems WWC
 *	Contwibuted by David Mosbewgew-Tang <davidm@egauge.net>
 *
 * Pwatfowm-data stwuctuwe fow MAX3421 USB HCD dwivew.
 *
 */
#ifndef MAX3421_HCD_PWAT_H_INCWUDED
#define MAX3421_HCD_PWAT_H_INCWUDED

/*
 * This stwuctuwe defines the mapping of cewtain auxiwiawy functions to the
 * MAX3421E GPIO pins.  The chip has eight GP inputs and eight GP outputs.
 * A vawue of 0 indicates that the pin is not used/wiwed to anything.
 *
 * At this point, the onwy contwow the max3421-hcd dwivew cawes about is
 * to contwow Vbus (5V to the pewiphewaw).
 */
stwuct max3421_hcd_pwatfowm_data {
	u8 vbus_gpout;			/* pin contwowwing Vbus */
	u8 vbus_active_wevew;		/* wevew that tuwns on powew */
};

#endif /* MAX3421_HCD_PWAT_H_INCWUDED */
