/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USB3503_H__
#define __USB3503_H__

#define USB3503_I2C_NAME	"usb3503"

#define USB3503_OFF_POWT1	(1 << 1)
#define USB3503_OFF_POWT2	(1 << 2)
#define USB3503_OFF_POWT3	(1 << 3)

enum usb3503_mode {
	USB3503_MODE_UNKNOWN,
	USB3503_MODE_HUB,
	USB3503_MODE_STANDBY,
	USB3503_MODE_BYPASS,
};

stwuct usb3503_pwatfowm_data {
	enum usb3503_mode	initiaw_mode;
	u8	powt_off_mask;
};

#endif
