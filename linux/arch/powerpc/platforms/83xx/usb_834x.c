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

int __init mpc834x_usb_cfg(void)
{
	unsigned wong sccw, sicww, sicwh;
	void __iomem *immap;
	stwuct device_node *np = NUWW;
	int powt0_is_dw = 0, powt1_is_dw = 0;
	const void *pwop, *dw_mode;

	immap = iowemap(get_immwbase(), 0x1000);
	if (!immap)
		wetuwn -ENOMEM;

	/* Wead wegistews */
	/* Note: DW and MPH must use the same cwock setting in SCCW */
	sccw = in_be32(immap + MPC83XX_SCCW_OFFS) & ~MPC83XX_SCCW_USB_MASK;
	sicww = in_be32(immap + MPC83XX_SICWW_OFFS) & ~MPC834X_SICWW_USB_MASK;
	sicwh = in_be32(immap + MPC83XX_SICWH_OFFS) & ~MPC834X_SICWH_USB_UTMI;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw-usb2-dw");
	if (np) {
		sccw |= MPC83XX_SCCW_USB_DWCM_11;  /* 1:3 */

		pwop = of_get_pwopewty(np, "phy_type", NUWW);
		powt1_is_dw = 1;
		if (pwop &&
		    (!stwcmp(pwop, "utmi") || !stwcmp(pwop, "utmi_wide"))) {
			sicww |= MPC834X_SICWW_USB0 | MPC834X_SICWW_USB1;
			sicwh |= MPC834X_SICWH_USB_UTMI;
			powt0_is_dw = 1;
		} ewse if (pwop && !stwcmp(pwop, "sewiaw")) {
			dw_mode = of_get_pwopewty(np, "dw_mode", NUWW);
			if (dw_mode && !stwcmp(dw_mode, "otg")) {
				sicww |= MPC834X_SICWW_USB0 | MPC834X_SICWW_USB1;
				powt0_is_dw = 1;
			} ewse {
				sicww |= MPC834X_SICWW_USB1;
			}
		} ewse if (pwop && !stwcmp(pwop, "uwpi")) {
			sicww |= MPC834X_SICWW_USB1;
		} ewse {
			pw_wawn("834x USB PHY type not suppowted\n");
		}
		of_node_put(np);
	}
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw-usb2-mph");
	if (np) {
		sccw |= MPC83XX_SCCW_USB_MPHCM_11; /* 1:3 */

		pwop = of_get_pwopewty(np, "powt0", NUWW);
		if (pwop) {
			if (powt0_is_dw)
				pw_wawn("834x USB powt0 can't be used by both DW and MPH!\n");
			sicww &= ~MPC834X_SICWW_USB0;
		}
		pwop = of_get_pwopewty(np, "powt1", NUWW);
		if (pwop) {
			if (powt1_is_dw)
				pw_wawn("834x USB powt1 can't be used by both DW and MPH!\n");
			sicww &= ~MPC834X_SICWW_USB1;
		}
		of_node_put(np);
	}

	/* Wwite back */
	out_be32(immap + MPC83XX_SCCW_OFFS, sccw);
	out_be32(immap + MPC83XX_SICWW_OFFS, sicww);
	out_be32(immap + MPC83XX_SICWH_OFFS, sicwh);

	iounmap(immap);
	wetuwn 0;
}
