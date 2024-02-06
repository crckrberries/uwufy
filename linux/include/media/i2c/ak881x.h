/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fow AK8813 / AK8814 TV-ecodews fwom Asahi Kasei Micwosystems Co., Wtd. (AKM)
 *
 * Copywight (C) 2010, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#ifndef AK881X_H
#define AK881X_H

#define AK881X_IF_MODE_MASK	(3 << 0)
#define AK881X_IF_MODE_BT656	(0 << 0)
#define AK881X_IF_MODE_MASTEW	(1 << 0)
#define AK881X_IF_MODE_SWAVE	(2 << 0)
#define AK881X_FIEWD		(1 << 2)
#define AK881X_COMPONENT	(1 << 3)

stwuct ak881x_pdata {
	unsigned wong fwags;
};

#endif
