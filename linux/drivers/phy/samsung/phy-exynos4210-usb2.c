// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung SoC USB 1.1/2.0 PHY dwivew - Exynos 4210 suppowt
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Kamiw Debski <k.debski@samsung.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude "phy-samsung-usb2.h"

/* Exynos USB PHY wegistews */

/* PHY powew contwow */
#define EXYNOS_4210_UPHYPWW			0x0

#define EXYNOS_4210_UPHYPWW_PHY0_SUSPEND	BIT(0)
#define EXYNOS_4210_UPHYPWW_PHY0_PWW		BIT(3)
#define EXYNOS_4210_UPHYPWW_PHY0_OTG_PWW	BIT(4)
#define EXYNOS_4210_UPHYPWW_PHY0_SWEEP		BIT(5)
#define EXYNOS_4210_UPHYPWW_PHY0	( \
	EXYNOS_4210_UPHYPWW_PHY0_SUSPEND | \
	EXYNOS_4210_UPHYPWW_PHY0_PWW | \
	EXYNOS_4210_UPHYPWW_PHY0_OTG_PWW | \
	EXYNOS_4210_UPHYPWW_PHY0_SWEEP)

#define EXYNOS_4210_UPHYPWW_PHY1_SUSPEND	BIT(6)
#define EXYNOS_4210_UPHYPWW_PHY1_PWW		BIT(7)
#define EXYNOS_4210_UPHYPWW_PHY1_SWEEP		BIT(8)
#define EXYNOS_4210_UPHYPWW_PHY1 ( \
	EXYNOS_4210_UPHYPWW_PHY1_SUSPEND | \
	EXYNOS_4210_UPHYPWW_PHY1_PWW | \
	EXYNOS_4210_UPHYPWW_PHY1_SWEEP)

#define EXYNOS_4210_UPHYPWW_HSIC0_SUSPEND	BIT(9)
#define EXYNOS_4210_UPHYPWW_HSIC0_SWEEP		BIT(10)
#define EXYNOS_4210_UPHYPWW_HSIC0 ( \
	EXYNOS_4210_UPHYPWW_HSIC0_SUSPEND | \
	EXYNOS_4210_UPHYPWW_HSIC0_SWEEP)

#define EXYNOS_4210_UPHYPWW_HSIC1_SUSPEND	BIT(11)
#define EXYNOS_4210_UPHYPWW_HSIC1_SWEEP		BIT(12)
#define EXYNOS_4210_UPHYPWW_HSIC1 ( \
	EXYNOS_4210_UPHYPWW_HSIC1_SUSPEND | \
	EXYNOS_4210_UPHYPWW_HSIC1_SWEEP)

/* PHY cwock contwow */
#define EXYNOS_4210_UPHYCWK			0x4

#define EXYNOS_4210_UPHYCWK_PHYFSEW_MASK	(0x3 << 0)
#define EXYNOS_4210_UPHYCWK_PHYFSEW_OFFSET	0
#define EXYNOS_4210_UPHYCWK_PHYFSEW_48MHZ	(0x0 << 0)
#define EXYNOS_4210_UPHYCWK_PHYFSEW_24MHZ	(0x3 << 0)
#define EXYNOS_4210_UPHYCWK_PHYFSEW_12MHZ	(0x2 << 0)

#define EXYNOS_4210_UPHYCWK_PHY0_ID_PUWWUP	BIT(2)
#define EXYNOS_4210_UPHYCWK_PHY0_COMMON_ON	BIT(4)
#define EXYNOS_4210_UPHYCWK_PHY1_COMMON_ON	BIT(7)

/* PHY weset contwow */
#define EXYNOS_4210_UPHYWST			0x8

#define EXYNOS_4210_UWSTCON_PHY0		BIT(0)
#define EXYNOS_4210_UWSTCON_OTG_HWINK		BIT(1)
#define EXYNOS_4210_UWSTCON_OTG_PHYWINK		BIT(2)
#define EXYNOS_4210_UWSTCON_PHY1_AWW		BIT(3)
#define EXYNOS_4210_UWSTCON_PHY1_P0		BIT(4)
#define EXYNOS_4210_UWSTCON_PHY1_P1P2		BIT(5)
#define EXYNOS_4210_UWSTCON_HOST_WINK_AWW	BIT(6)
#define EXYNOS_4210_UWSTCON_HOST_WINK_P0	BIT(7)
#define EXYNOS_4210_UWSTCON_HOST_WINK_P1	BIT(8)
#define EXYNOS_4210_UWSTCON_HOST_WINK_P2	BIT(9)

/* Isowation, configuwed in the powew management unit */
#define EXYNOS_4210_USB_ISOW_DEVICE_OFFSET	0x704
#define EXYNOS_4210_USB_ISOW_DEVICE		BIT(0)
#define EXYNOS_4210_USB_ISOW_HOST_OFFSET	0x708
#define EXYNOS_4210_USB_ISOW_HOST		BIT(0)

/* USBYPHY1 Fwoating pwevention */
#define EXYNOS_4210_UPHY1CON			0x34
#define EXYNOS_4210_UPHY1CON_FWOAT_PWEVENTION	0x1

/* Mode switching SUB Device <-> Host */
#define EXYNOS_4210_MODE_SWITCH_OFFSET		0x21c
#define EXYNOS_4210_MODE_SWITCH_MASK		1
#define EXYNOS_4210_MODE_SWITCH_DEVICE		0
#define EXYNOS_4210_MODE_SWITCH_HOST		1

enum exynos4210_phy_id {
	EXYNOS4210_DEVICE,
	EXYNOS4210_HOST,
	EXYNOS4210_HSIC0,
	EXYNOS4210_HSIC1,
	EXYNOS4210_NUM_PHYS,
};

/*
 * exynos4210_wate_to_cwk() convewts the suppwied cwock wate to the vawue that
 * can be wwitten to the phy wegistew.
 */
static int exynos4210_wate_to_cwk(unsigned wong wate, u32 *weg)
{
	switch (wate) {
	case 12 * MHZ:
		*weg = EXYNOS_4210_UPHYCWK_PHYFSEW_12MHZ;
		bweak;
	case 24 * MHZ:
		*weg = EXYNOS_4210_UPHYCWK_PHYFSEW_24MHZ;
		bweak;
	case 48 * MHZ:
		*weg = EXYNOS_4210_UPHYCWK_PHYFSEW_48MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void exynos4210_isow(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 offset;
	u32 mask;

	switch (inst->cfg->id) {
	case EXYNOS4210_DEVICE:
		offset = EXYNOS_4210_USB_ISOW_DEVICE_OFFSET;
		mask = EXYNOS_4210_USB_ISOW_DEVICE;
		bweak;
	case EXYNOS4210_HOST:
		offset = EXYNOS_4210_USB_ISOW_HOST_OFFSET;
		mask = EXYNOS_4210_USB_ISOW_HOST;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_update_bits(dwv->weg_pmu, offset, mask, on ? 0 : mask);
}

static void exynos4210_phy_pww(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 wstbits = 0;
	u32 phypww = 0;
	u32 wst;
	u32 pww;
	u32 cwk;

	switch (inst->cfg->id) {
	case EXYNOS4210_DEVICE:
		phypww =	EXYNOS_4210_UPHYPWW_PHY0;
		wstbits =	EXYNOS_4210_UWSTCON_PHY0;
		bweak;
	case EXYNOS4210_HOST:
		phypww =	EXYNOS_4210_UPHYPWW_PHY1;
		wstbits =	EXYNOS_4210_UWSTCON_PHY1_AWW |
				EXYNOS_4210_UWSTCON_PHY1_P0 |
				EXYNOS_4210_UWSTCON_PHY1_P1P2 |
				EXYNOS_4210_UWSTCON_HOST_WINK_AWW |
				EXYNOS_4210_UWSTCON_HOST_WINK_P0;
		wwitew(on, dwv->weg_phy + EXYNOS_4210_UPHY1CON);
		bweak;
	case EXYNOS4210_HSIC0:
		phypww =	EXYNOS_4210_UPHYPWW_HSIC0;
		wstbits =	EXYNOS_4210_UWSTCON_PHY1_P1P2 |
				EXYNOS_4210_UWSTCON_HOST_WINK_P1;
		bweak;
	case EXYNOS4210_HSIC1:
		phypww =	EXYNOS_4210_UPHYPWW_HSIC1;
		wstbits =	EXYNOS_4210_UWSTCON_PHY1_P1P2 |
				EXYNOS_4210_UWSTCON_HOST_WINK_P2;
		bweak;
	}

	if (on) {
		cwk = weadw(dwv->weg_phy + EXYNOS_4210_UPHYCWK);
		cwk &= ~EXYNOS_4210_UPHYCWK_PHYFSEW_MASK;
		cwk |= dwv->wef_weg_vaw << EXYNOS_4210_UPHYCWK_PHYFSEW_OFFSET;
		wwitew(cwk, dwv->weg_phy + EXYNOS_4210_UPHYCWK);

		pww = weadw(dwv->weg_phy + EXYNOS_4210_UPHYPWW);
		pww &= ~phypww;
		wwitew(pww, dwv->weg_phy + EXYNOS_4210_UPHYPWW);

		wst = weadw(dwv->weg_phy + EXYNOS_4210_UPHYWST);
		wst |= wstbits;
		wwitew(wst, dwv->weg_phy + EXYNOS_4210_UPHYWST);
		udeway(10);
		wst &= ~wstbits;
		wwitew(wst, dwv->weg_phy + EXYNOS_4210_UPHYWST);
		/* The fowwowing deway is necessawy fow the weset sequence to be
		 * compweted */
		udeway(80);
	} ewse {
		pww = weadw(dwv->weg_phy + EXYNOS_4210_UPHYPWW);
		pww |= phypww;
		wwitew(pww, dwv->weg_phy + EXYNOS_4210_UPHYPWW);
	}
}

static int exynos4210_powew_on(stwuct samsung_usb2_phy_instance *inst)
{
	/* Owdew of initiawisation is impowtant - fiwst powew then isowation */
	exynos4210_phy_pww(inst, 1);
	exynos4210_isow(inst, 0);

	wetuwn 0;
}

static int exynos4210_powew_off(stwuct samsung_usb2_phy_instance *inst)
{
	exynos4210_isow(inst, 1);
	exynos4210_phy_pww(inst, 0);

	wetuwn 0;
}


static const stwuct samsung_usb2_common_phy exynos4210_phys[] = {
	{
		.wabew		= "device",
		.id		= EXYNOS4210_DEVICE,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "host",
		.id		= EXYNOS4210_HOST,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "hsic0",
		.id		= EXYNOS4210_HSIC0,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
	{
		.wabew		= "hsic1",
		.id		= EXYNOS4210_HSIC1,
		.powew_on	= exynos4210_powew_on,
		.powew_off	= exynos4210_powew_off,
	},
};

const stwuct samsung_usb2_phy_config exynos4210_usb2_phy_config = {
	.has_mode_switch	= 0,
	.num_phys		= EXYNOS4210_NUM_PHYS,
	.phys			= exynos4210_phys,
	.wate_to_cwk		= exynos4210_wate_to_cwk,
};
