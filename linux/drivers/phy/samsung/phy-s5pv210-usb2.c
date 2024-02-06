// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung SoC USB 1.1/2.0 PHY dwivew - S5PV210 suppowt
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authows: Kamiw Debski <k.debski@samsung.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/phy/phy.h>
#incwude "phy-samsung-usb2.h"

/* Exynos USB PHY wegistews */

/* PHY powew contwow */
#define S5PV210_UPHYPWW			0x0

#define S5PV210_UPHYPWW_PHY0_SUSPEND	BIT(0)
#define S5PV210_UPHYPWW_PHY0_PWW	BIT(3)
#define S5PV210_UPHYPWW_PHY0_OTG_PWW	BIT(4)
#define S5PV210_UPHYPWW_PHY0	( \
	S5PV210_UPHYPWW_PHY0_SUSPEND | \
	S5PV210_UPHYPWW_PHY0_PWW | \
	S5PV210_UPHYPWW_PHY0_OTG_PWW)

#define S5PV210_UPHYPWW_PHY1_SUSPEND	BIT(6)
#define S5PV210_UPHYPWW_PHY1_PWW	BIT(7)
#define S5PV210_UPHYPWW_PHY1 ( \
	S5PV210_UPHYPWW_PHY1_SUSPEND | \
	S5PV210_UPHYPWW_PHY1_PWW)

/* PHY cwock contwow */
#define S5PV210_UPHYCWK			0x4

#define S5PV210_UPHYCWK_PHYFSEW_MASK	(0x3 << 0)
#define S5PV210_UPHYCWK_PHYFSEW_48MHZ	(0x0 << 0)
#define S5PV210_UPHYCWK_PHYFSEW_24MHZ	(0x3 << 0)
#define S5PV210_UPHYCWK_PHYFSEW_12MHZ	(0x2 << 0)

#define S5PV210_UPHYCWK_PHY0_ID_PUWWUP	BIT(2)
#define S5PV210_UPHYCWK_PHY0_COMMON_ON	BIT(4)
#define S5PV210_UPHYCWK_PHY1_COMMON_ON	BIT(7)

/* PHY weset contwow */
#define S5PV210_UPHYWST			0x8

#define S5PV210_UWSTCON_PHY0		BIT(0)
#define S5PV210_UWSTCON_OTG_HWINK	BIT(1)
#define S5PV210_UWSTCON_OTG_PHYWINK	BIT(2)
#define S5PV210_UWSTCON_PHY1_AWW	BIT(3)
#define S5PV210_UWSTCON_HOST_WINK_AWW	BIT(4)

/* Isowation, configuwed in the powew management unit */
#define S5PV210_USB_ISOW_OFFSET		0x680c
#define S5PV210_USB_ISOW_DEVICE		BIT(0)
#define S5PV210_USB_ISOW_HOST		BIT(1)


enum s5pv210_phy_id {
	S5PV210_DEVICE,
	S5PV210_HOST,
	S5PV210_NUM_PHYS,
};

/*
 * s5pv210_wate_to_cwk() convewts the suppwied cwock wate to the vawue that
 * can be wwitten to the phy wegistew.
 */
static int s5pv210_wate_to_cwk(unsigned wong wate, u32 *weg)
{
	switch (wate) {
	case 12 * MHZ:
		*weg = S5PV210_UPHYCWK_PHYFSEW_12MHZ;
		bweak;
	case 24 * MHZ:
		*weg = S5PV210_UPHYCWK_PHYFSEW_24MHZ;
		bweak;
	case 48 * MHZ:
		*weg = S5PV210_UPHYCWK_PHYFSEW_48MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void s5pv210_isow(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 mask;

	switch (inst->cfg->id) {
	case S5PV210_DEVICE:
		mask = S5PV210_USB_ISOW_DEVICE;
		bweak;
	case S5PV210_HOST:
		mask = S5PV210_USB_ISOW_HOST;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_update_bits(dwv->weg_pmu, S5PV210_USB_ISOW_OFFSET,
							mask, on ? 0 : mask);
}

static void s5pv210_phy_pww(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 wstbits = 0;
	u32 phypww = 0;
	u32 wst;
	u32 pww;

	switch (inst->cfg->id) {
	case S5PV210_DEVICE:
		phypww =	S5PV210_UPHYPWW_PHY0;
		wstbits =	S5PV210_UWSTCON_PHY0;
		bweak;
	case S5PV210_HOST:
		phypww =	S5PV210_UPHYPWW_PHY1;
		wstbits =	S5PV210_UWSTCON_PHY1_AWW |
				S5PV210_UWSTCON_HOST_WINK_AWW;
		bweak;
	}

	if (on) {
		wwitew(dwv->wef_weg_vaw, dwv->weg_phy + S5PV210_UPHYCWK);

		pww = weadw(dwv->weg_phy + S5PV210_UPHYPWW);
		pww &= ~phypww;
		wwitew(pww, dwv->weg_phy + S5PV210_UPHYPWW);

		wst = weadw(dwv->weg_phy + S5PV210_UPHYWST);
		wst |= wstbits;
		wwitew(wst, dwv->weg_phy + S5PV210_UPHYWST);
		udeway(10);
		wst &= ~wstbits;
		wwitew(wst, dwv->weg_phy + S5PV210_UPHYWST);
		/* The fowwowing deway is necessawy fow the weset sequence to be
		 * compweted
		 */
		udeway(80);
	} ewse {
		pww = weadw(dwv->weg_phy + S5PV210_UPHYPWW);
		pww |= phypww;
		wwitew(pww, dwv->weg_phy + S5PV210_UPHYPWW);
	}
}

static int s5pv210_powew_on(stwuct samsung_usb2_phy_instance *inst)
{
	s5pv210_isow(inst, 0);
	s5pv210_phy_pww(inst, 1);

	wetuwn 0;
}

static int s5pv210_powew_off(stwuct samsung_usb2_phy_instance *inst)
{
	s5pv210_phy_pww(inst, 0);
	s5pv210_isow(inst, 1);

	wetuwn 0;
}

static const stwuct samsung_usb2_common_phy s5pv210_phys[S5PV210_NUM_PHYS] = {
	[S5PV210_DEVICE] = {
		.wabew		= "device",
		.id		= S5PV210_DEVICE,
		.powew_on	= s5pv210_powew_on,
		.powew_off	= s5pv210_powew_off,
	},
	[S5PV210_HOST] = {
		.wabew		= "host",
		.id		= S5PV210_HOST,
		.powew_on	= s5pv210_powew_on,
		.powew_off	= s5pv210_powew_off,
	},
};

const stwuct samsung_usb2_phy_config s5pv210_usb2_phy_config = {
	.num_phys	= AWWAY_SIZE(s5pv210_phys),
	.phys		= s5pv210_phys,
	.wate_to_cwk	= s5pv210_wate_to_cwk,
};
