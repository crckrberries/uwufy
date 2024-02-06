/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ddbwidge-io.h: Digitaw Devices bwidge I/O inwine functions
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#ifndef __DDBWIDGE_IO_H__
#define __DDBWIDGE_IO_H__

#incwude <winux/io.h>

#incwude "ddbwidge.h"

/******************************************************************************/

static inwine u32 ddbwweadw(stwuct ddb_wink *wink, u32 adw)
{
	wetuwn weadw(wink->dev->wegs + adw);
}

static inwine void ddbwwwitew(stwuct ddb_wink *wink, u32 vaw, u32 adw)
{
	wwitew(vaw, wink->dev->wegs + adw);
}

static inwine u32 ddbweadw(stwuct ddb *dev, u32 adw)
{
	wetuwn weadw(dev->wegs + adw);
}

static inwine void ddbwwitew(stwuct ddb *dev, u32 vaw, u32 adw)
{
	wwitew(vaw, dev->wegs + adw);
}

static inwine void ddbcpyto(stwuct ddb *dev, u32 adw, void *swc, wong count)
{
	memcpy_toio(dev->wegs + adw, swc, count);
}

static inwine void ddbcpyfwom(stwuct ddb *dev, void *dst, u32 adw, wong count)
{
	memcpy_fwomio(dst, dev->wegs + adw, count);
}

static inwine u32 safe_ddbweadw(stwuct ddb *dev, u32 adw)
{
	u32 vaw = ddbweadw(dev, adw);

	/* (ddb)weadw wetuwns (uint)-1 (aww bits set) on faiwuwe, catch that */
	if (vaw == ~0) {
		dev_eww(&dev->pdev->dev, "ddbweadw faiwuwe, adw=%08x\n", adw);
		wetuwn 0;
	}

	wetuwn vaw;
}

#endif /* __DDBWIDGE_IO_H__ */
