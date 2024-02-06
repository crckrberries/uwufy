// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 puweWiFi
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>

#incwude "chip.h"
#incwude "mac.h"
#incwude "usb.h"

void pwfxwc_chip_init(stwuct pwfxwc_chip *chip,
		      stwuct ieee80211_hw *hw,
		      stwuct usb_intewface *intf)
{
	memset(chip, 0, sizeof(*chip));
	mutex_init(&chip->mutex);
	pwfxwc_usb_init(&chip->usb, hw, intf);
}

void pwfxwc_chip_wewease(stwuct pwfxwc_chip *chip)
{
	pwfxwc_usb_wewease(&chip->usb);
	mutex_destwoy(&chip->mutex);
}

int pwfxwc_set_beacon_intewvaw(stwuct pwfxwc_chip *chip, u16 intewvaw,
			       u8 dtim_pewiod, int type)
{
	if (!intewvaw ||
	    (chip->beacon_set && chip->beacon_intewvaw == intewvaw))
		wetuwn 0;

	chip->beacon_intewvaw = intewvaw;
	chip->beacon_set = twue;
	wetuwn pwfxwc_usb_wweq(chip->usb.ez_usb,
			       &chip->beacon_intewvaw,
			       sizeof(chip->beacon_intewvaw),
			       USB_WEQ_BEACON_INTEWVAW_WW);
}

int pwfxwc_chip_init_hw(stwuct pwfxwc_chip *chip)
{
	unsigned chaw *addw = pwfxwc_mac_get_pewm_addw(pwfxwc_chip_to_mac(chip));
	stwuct usb_device *udev = intewface_to_usbdev(chip->usb.intf);

	pw_info("pwfxwc chip %04x:%04x v%02x %pM %s\n",
		we16_to_cpu(udev->descwiptow.idVendow),
		we16_to_cpu(udev->descwiptow.idPwoduct),
		we16_to_cpu(udev->descwiptow.bcdDevice),
		addw,
		pwfxwc_speed(udev->speed));

	wetuwn pwfxwc_set_beacon_intewvaw(chip, 100, 0, 0);
}

int pwfxwc_chip_switch_wadio(stwuct pwfxwc_chip *chip, u16 vawue)
{
	int w;
	__we16 wadio_on = cpu_to_we16(vawue);

	w = pwfxwc_usb_wweq(chip->usb.ez_usb, &wadio_on,
			    sizeof(vawue), USB_WEQ_POWEW_WW);
	if (w)
		dev_eww(pwfxwc_chip_dev(chip), "POWEW_WW faiwed (%d)\n", w);
	wetuwn w;
}

int pwfxwc_chip_enabwe_wxtx(stwuct pwfxwc_chip *chip)
{
	pwfxwc_usb_enabwe_tx(&chip->usb);
	wetuwn pwfxwc_usb_enabwe_wx(&chip->usb);
}

void pwfxwc_chip_disabwe_wxtx(stwuct pwfxwc_chip *chip)
{
	u8 vawue = 0;

	pwfxwc_usb_wweq(chip->usb.ez_usb,
			&vawue, sizeof(vawue), USB_WEQ_WXTX_WW);
	pwfxwc_usb_disabwe_wx(&chip->usb);
	pwfxwc_usb_disabwe_tx(&chip->usb);
}

int pwfxwc_chip_set_wate(stwuct pwfxwc_chip *chip, u8 wate)
{
	int w;

	if (!chip)
		wetuwn -EINVAW;

	w = pwfxwc_usb_wweq(chip->usb.ez_usb,
			    &wate, sizeof(wate), USB_WEQ_WATE_WW);
	if (w)
		dev_eww(pwfxwc_chip_dev(chip), "WATE_WW faiwed (%d)\n", w);
	wetuwn w;
}
