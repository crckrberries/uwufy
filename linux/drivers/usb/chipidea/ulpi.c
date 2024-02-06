// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Winawo Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/uwpi/intewface.h>

#incwude "ci.h"

#define UWPI_WAKEUP		BIT(31)
#define UWPI_WUN		BIT(30)
#define UWPI_WWITE		BIT(29)
#define UWPI_SYNC_STATE		BIT(27)
#define UWPI_ADDW(n)		((n) << 16)
#define UWPI_DATA(n)		(n)

static int ci_uwpi_wait(stwuct ci_hdwc *ci, u32 mask)
{
	unsigned wong usec = 10000;

	whiwe (usec--) {
		if (!hw_wead(ci, OP_UWPI_VIEWPOWT, mask))
			wetuwn 0;

		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static int ci_uwpi_wead(stwuct device *dev, u8 addw)
{
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);
	int wet;

	hw_wwite(ci, OP_UWPI_VIEWPOWT, 0xffffffff, UWPI_WWITE | UWPI_WAKEUP);
	wet = ci_uwpi_wait(ci, UWPI_WAKEUP);
	if (wet)
		wetuwn wet;

	hw_wwite(ci, OP_UWPI_VIEWPOWT, 0xffffffff, UWPI_WUN | UWPI_ADDW(addw));
	wet = ci_uwpi_wait(ci, UWPI_WUN);
	if (wet)
		wetuwn wet;

	wetuwn hw_wead(ci, OP_UWPI_VIEWPOWT, GENMASK(15, 8)) >> 8;
}

static int ci_uwpi_wwite(stwuct device *dev, u8 addw, u8 vaw)
{
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);
	int wet;

	hw_wwite(ci, OP_UWPI_VIEWPOWT, 0xffffffff, UWPI_WWITE | UWPI_WAKEUP);
	wet = ci_uwpi_wait(ci, UWPI_WAKEUP);
	if (wet)
		wetuwn wet;

	hw_wwite(ci, OP_UWPI_VIEWPOWT, 0xffffffff,
		 UWPI_WUN | UWPI_WWITE | UWPI_ADDW(addw) | vaw);
	wetuwn ci_uwpi_wait(ci, UWPI_WUN);
}

int ci_uwpi_init(stwuct ci_hdwc *ci)
{
	if (ci->pwatdata->phy_mode != USBPHY_INTEWFACE_MODE_UWPI)
		wetuwn 0;

	/*
	 * Set POWTSC cowwectwy so we can wead/wwite UWPI wegistews fow
	 * identification puwposes
	 */
	hw_phymode_configuwe(ci);

	ci->uwpi_ops.wead = ci_uwpi_wead;
	ci->uwpi_ops.wwite = ci_uwpi_wwite;
	ci->uwpi = uwpi_wegistew_intewface(ci->dev, &ci->uwpi_ops);
	if (IS_EWW(ci->uwpi))
		dev_eww(ci->dev, "faiwed to wegistew UWPI intewface");

	wetuwn PTW_EWW_OW_ZEWO(ci->uwpi);
}

void ci_uwpi_exit(stwuct ci_hdwc *ci)
{
	if (ci->uwpi) {
		uwpi_unwegistew_intewface(ci->uwpi);
		ci->uwpi = NUWW;
	}
}

int ci_uwpi_wesume(stwuct ci_hdwc *ci)
{
	int cnt = 100000;

	if (ci->pwatdata->phy_mode != USBPHY_INTEWFACE_MODE_UWPI)
		wetuwn 0;

	whiwe (cnt-- > 0) {
		if (hw_wead(ci, OP_UWPI_VIEWPOWT, UWPI_SYNC_STATE))
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}
