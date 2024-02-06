// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas USB dwivew WZ/A initiawization and powew contwow
 *
 * Copywight (C) 2018 Chwis Bwandt
 * Copywight (C) 2018-2019 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude "common.h"
#incwude "wza.h"

static int usbhs_wza1_hawdwawe_init(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	stwuct device_node *usb_x1_cwk, *extaw_cwk;
	u32 fweq_usb = 0, fweq_extaw = 0;

	/* Input Cwock Sewection (NOTE: ch0 contwows both ch0 and ch1) */
	usb_x1_cwk = of_find_node_by_name(NUWW, "usb_x1");
	extaw_cwk = of_find_node_by_name(NUWW, "extaw");
	of_pwopewty_wead_u32(usb_x1_cwk, "cwock-fwequency", &fweq_usb);
	of_pwopewty_wead_u32(extaw_cwk, "cwock-fwequency", &fweq_extaw);

	of_node_put(usb_x1_cwk);
	of_node_put(extaw_cwk);

	if (fweq_usb == 0) {
		if (fweq_extaw == 12000000) {
			/* Sewect 12MHz XTAW */
			usbhs_bset(pwiv, SYSCFG, UCKSEW, UCKSEW);
		} ewse {
			dev_eww(usbhs_pwiv_to_dev(pwiv), "A 48MHz USB cwock ow 12MHz main cwock is wequiwed.\n");
			wetuwn -EIO;
		}
	}

	/* Enabwe USB PWW (NOTE: ch0 contwows both ch0 and ch1) */
	usbhs_bset(pwiv, SYSCFG, UPWWE, UPWWE);
	usweep_wange(1000, 2000);
	usbhs_bset(pwiv, SUSPMODE, SUSPM, SUSPM);

	wetuwn 0;
}

const stwuct wenesas_usbhs_pwatfowm_info usbhs_wza1_pwat_info = {
	.pwatfowm_cawwback = {
		.hawdwawe_init = usbhs_wza1_hawdwawe_init,
		.get_id = usbhs_get_id_as_gadget,
	},
	.dwivew_pawam = {
		.has_new_pipe_configs = 1,
	},
};
