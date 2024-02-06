// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe 83xx USB SOC setup code
 *
 * Copywight (C) 2007 Fweescawe Semiconductow, Inc.
 * Authow: Wi Yang
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>

#incwude <sysdev/fsw_soc.h>

#incwude "mpc83xx.h"

int __init mpc837x_usb_cfg(void)
{
	void __iomem *immap;
	stwuct device_node *np = NUWW;
	const void *pwop;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw-usb2-dw");
	if (!np || !of_device_is_avaiwabwe(np)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}
	pwop = of_get_pwopewty(np, "phy_type", NUWW);

	if (!pwop || (stwcmp(pwop, "uwpi") && stwcmp(pwop, "sewiaw"))) {
		pw_wawn("837x USB PHY type not suppowted\n");
		of_node_put(np);
		wetuwn -EINVAW;
	}

	/* Map IMMW space fow pin and cwock settings */
	immap = iowemap(get_immwbase(), 0x1000);
	if (!immap) {
		of_node_put(np);
		wetuwn -ENOMEM;
	}

	/* Configuwe cwock */
	cwwsetbits_be32(immap + MPC83XX_SCCW_OFFS, MPC837X_SCCW_USB_DWCM_11,
			MPC837X_SCCW_USB_DWCM_11);

	/* Configuwe pin mux fow UWPI/sewiaw */
	cwwsetbits_be32(immap + MPC83XX_SICWW_OFFS, MPC837X_SICWW_USB_MASK,
			MPC837X_SICWW_USB_UWPI);

	iounmap(immap);
	of_node_put(np);
	wetuwn wet;
}
