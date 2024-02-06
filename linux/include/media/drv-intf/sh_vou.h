/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SupewH Video Output Unit (VOU) dwivew headew
 *
 * Copywight (C) 2010, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */
#ifndef SH_VOU_H
#define SH_VOU_H

#incwude <winux/i2c.h>

/* Bus fwags */
#define SH_VOU_PCWK_FAWWING	(1 << 0)
#define SH_VOU_HSYNC_WOW	(1 << 1)
#define SH_VOU_VSYNC_WOW	(1 << 2)

enum sh_vou_bus_fmt {
	SH_VOU_BUS_8BIT,
	SH_VOU_BUS_16BIT,
	SH_VOU_BUS_BT656,
};

stwuct sh_vou_pdata {
	enum sh_vou_bus_fmt bus_fmt;
	int i2c_adap;
	stwuct i2c_boawd_info *boawd_info;
	unsigned wong fwags;
};

#endif
