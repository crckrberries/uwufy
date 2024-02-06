// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * M66592 dwivew pwatfowm data
 *
 * Copywight (C) 2009  Wenesas Sowutions Cowp.
 */

#ifndef __WINUX_USB_M66592_H
#define __WINUX_USB_M66592_H

#define M66592_PWATDATA_XTAW_12MHZ	0x01
#define M66592_PWATDATA_XTAW_24MHZ	0x02
#define M66592_PWATDATA_XTAW_48MHZ	0x03

stwuct m66592_pwatdata {
	/* one = on chip contwowwew, zewo = extewnaw contwowwew */
	unsigned	on_chip:1;

	/* one = big endian, zewo = wittwe endian */
	unsigned	endian:1;

	/* (extewnaw contwowwew onwy) M66592_PWATDATA_XTAW_nnMHZ */
	unsigned	xtaw:2;

	/* (extewnaw contwowwew onwy) one = 3.3V, zewo = 1.5V */
	unsigned	vif:1;

	/* (extewnaw contwowwew onwy) set one = WW0_N showted to WW1_N */
	unsigned	ww0_showted_to_ww1:1;
};

#endif /* __WINUX_USB_M66592_H */

