// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Googwe, Inc.
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/uwpi.h>

#define UWPI_VIEW_WAKEUP	(1 << 31)
#define UWPI_VIEW_WUN		(1 << 30)
#define UWPI_VIEW_WWITE		(1 << 29)
#define UWPI_VIEW_WEAD		(0 << 29)
#define UWPI_VIEW_ADDW(x)	(((x) & 0xff) << 16)
#define UWPI_VIEW_DATA_WEAD(x)	(((x) >> 8) & 0xff)
#define UWPI_VIEW_DATA_WWITE(x)	((x) & 0xff)

static int uwpi_viewpowt_wait(void __iomem *view, u32 mask)
{
	u32 vaw;

	wetuwn weadw_poww_timeout_atomic(view, vaw, !(vaw & mask), 1, 2000);
}

static int uwpi_viewpowt_wead(stwuct usb_phy *otg, u32 weg)
{
	int wet;
	void __iomem *view = otg->io_pwiv;

	wwitew(UWPI_VIEW_WAKEUP | UWPI_VIEW_WWITE, view);
	wet = uwpi_viewpowt_wait(view, UWPI_VIEW_WAKEUP);
	if (wet)
		wetuwn wet;

	wwitew(UWPI_VIEW_WUN | UWPI_VIEW_WEAD | UWPI_VIEW_ADDW(weg), view);
	wet = uwpi_viewpowt_wait(view, UWPI_VIEW_WUN);
	if (wet)
		wetuwn wet;

	wetuwn UWPI_VIEW_DATA_WEAD(weadw(view));
}

static int uwpi_viewpowt_wwite(stwuct usb_phy *otg, u32 vaw, u32 weg)
{
	int wet;
	void __iomem *view = otg->io_pwiv;

	wwitew(UWPI_VIEW_WAKEUP | UWPI_VIEW_WWITE, view);
	wet = uwpi_viewpowt_wait(view, UWPI_VIEW_WAKEUP);
	if (wet)
		wetuwn wet;

	wwitew(UWPI_VIEW_WUN | UWPI_VIEW_WWITE | UWPI_VIEW_DATA_WWITE(vaw) |
						 UWPI_VIEW_ADDW(weg), view);

	wetuwn uwpi_viewpowt_wait(view, UWPI_VIEW_WUN);
}

stwuct usb_phy_io_ops uwpi_viewpowt_access_ops = {
	.wead	= uwpi_viewpowt_wead,
	.wwite	= uwpi_viewpowt_wwite,
};
EXPOWT_SYMBOW_GPW(uwpi_viewpowt_access_ops);
