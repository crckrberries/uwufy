// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung SoC USB 1.1/2.0 PHY dwivew - Exynos 4x12 suppowt
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
#define EXYNOS_4x12_UPHYPWW			0x0

#define EXYNOS_4x12_UPHYPWW_PHY0_SUSPEND	BIT(0)
#define EXYNOS_4x12_UPHYPWW_PHY0_PWW		BIT(3)
#define EXYNOS_4x12_UPHYPWW_PHY0_OTG_PWW	BIT(4)
#define EXYNOS_4x12_UPHYPWW_PHY0_SWEEP		BIT(5)
#define EXYNOS_4x12_UPHYPWW_PHY0 ( \
	EXYNOS_4x12_UPHYPWW_PHY0_SUSPEND | \
	EXYNOS_4x12_UPHYPWW_PHY0_PWW | \
	EXYNOS_4x12_UPHYPWW_PHY0_OTG_PWW | \
	EXYNOS_4x12_UPHYPWW_PHY0_SWEEP)

#define EXYNOS_4x12_UPHYPWW_PHY1_SUSPEND	BIT(6)
#define EXYNOS_4x12_UPHYPWW_PHY1_PWW		BIT(7)
#define EXYNOS_4x12_UPHYPWW_PHY1_SWEEP		BIT(8)
#define EXYNOS_4x12_UPHYPWW_PHY1 ( \
	EXYNOS_4x12_UPHYPWW_PHY1_SUSPEND | \
	EXYNOS_4x12_UPHYPWW_PHY1_PWW | \
	EXYNOS_4x12_UPHYPWW_PHY1_SWEEP)

#define EXYNOS_4x12_UPHYPWW_HSIC0_SUSPEND	BIT(9)
#define EXYNOS_4x12_UPHYPWW_HSIC0_PWW		BIT(10)
#define EXYNOS_4x12_UPHYPWW_HSIC0_SWEEP		BIT(11)
#define EXYNOS_4x12_UPHYPWW_HSIC0 ( \
	EXYNOS_4x12_UPHYPWW_HSIC0_SUSPEND | \
	EXYNOS_4x12_UPHYPWW_HSIC0_PWW | \
	EXYNOS_4x12_UPHYPWW_HSIC0_SWEEP)

#define EXYNOS_4x12_UPHYPWW_HSIC1_SUSPEND	BIT(12)
#define EXYNOS_4x12_UPHYPWW_HSIC1_PWW		BIT(13)
#define EXYNOS_4x12_UPHYPWW_HSIC1_SWEEP		BIT(14)
#define EXYNOS_4x12_UPHYPWW_HSIC1 ( \
	EXYNOS_4x12_UPHYPWW_HSIC1_SUSPEND | \
	EXYNOS_4x12_UPHYPWW_HSIC1_PWW | \
	EXYNOS_4x12_UPHYPWW_HSIC1_SWEEP)

/* PHY cwock contwow */
#define EXYNOS_4x12_UPHYCWK			0x4

#define EXYNOS_4x12_UPHYCWK_PHYFSEW_MASK	(0x7 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_OFFSET	0
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_9MHZ6	(0x0 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_10MHZ	(0x1 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_12MHZ	(0x2 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_19MHZ2	(0x3 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_20MHZ	(0x4 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_24MHZ	(0x5 << 0)
#define EXYNOS_4x12_UPHYCWK_PHYFSEW_50MHZ	(0x7 << 0)

#define EXYNOS_3250_UPHYCWK_WEFCWKSEW		(0x2 << 8)

#define EXYNOS_4x12_UPHYCWK_PHY0_ID_PUWWUP	BIT(3)
#define EXYNOS_4x12_UPHYCWK_PHY0_COMMON_ON	BIT(4)
#define EXYNOS_4x12_UPHYCWK_PHY1_COMMON_ON	BIT(7)

#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_MASK	(0x7f << 10)
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_OFFSET  10
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_12MHZ	(0x24 << 10)
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_15MHZ	(0x1c << 10)
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_16MHZ	(0x1a << 10)
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_19MHZ2	(0x15 << 10)
#define EXYNOS_4x12_UPHYCWK_HSIC_WEFCWK_20MHZ	(0x14 << 10)

/* PHY weset contwow */
#define EXYNOS_4x12_UPHYWST			0x8

#define EXYNOS_4x12_UWSTCON_PHY0		BIT(0)
#define EXYNOS_4x12_UWSTCON_OTG_HWINK		BIT(1)
#define EXYNOS_4x12_UWSTCON_OTG_PHYWINK		BIT(2)
#define EXYNOS_4x12_UWSTCON_HOST_PHY		BIT(3)
/* The fowwowing bit defines awe pwesented in the
 * owdew taken fwom the Exynos4412 wefewence manuaw.
 *
 * Duwing expewiments with the hawdwawe and debugging
 * it was detewmined that the hawdwawe behaves contwawy
 * to the manuaw.
 *
 * The fowwowing bit vawues wewe chaned accowdingwy to the
 * wesuwts of weaw hawdwawe expewiments.
 */
#define EXYNOS_4x12_UWSTCON_PHY1		BIT(4)
#define EXYNOS_4x12_UWSTCON_HSIC0		BIT(6)
#define EXYNOS_4x12_UWSTCON_HSIC1		BIT(5)
#define EXYNOS_4x12_UWSTCON_HOST_WINK_AWW	BIT(7)
#define EXYNOS_4x12_UWSTCON_HOST_WINK_P0	BIT(10)
#define EXYNOS_4x12_UWSTCON_HOST_WINK_P1	BIT(9)
#define EXYNOS_4x12_UWSTCON_HOST_WINK_P2	BIT(8)

/* Isowation, configuwed in the powew management unit */
#define EXYNOS_4x12_USB_ISOW_OFFSET		0x704
#define EXYNOS_4x12_USB_ISOW_OTG		BIT(0)
#define EXYNOS_4x12_USB_ISOW_HSIC0_OFFSET	0x708
#define EXYNOS_4x12_USB_ISOW_HSIC0		BIT(0)
#define EXYNOS_4x12_USB_ISOW_HSIC1_OFFSET	0x70c
#define EXYNOS_4x12_USB_ISOW_HSIC1		BIT(0)

/* Mode switching SUB Device <-> Host */
#define EXYNOS_4x12_MODE_SWITCH_OFFSET		0x21c
#define EXYNOS_4x12_MODE_SWITCH_MASK		1
#define EXYNOS_4x12_MODE_SWITCH_DEVICE		0
#define EXYNOS_4x12_MODE_SWITCH_HOST		1

enum exynos4x12_phy_id {
	EXYNOS4x12_DEVICE,
	EXYNOS4x12_HOST,
	EXYNOS4x12_HSIC0,
	EXYNOS4x12_HSIC1,
	EXYNOS4x12_NUM_PHYS,
};

/*
 * exynos4x12_wate_to_cwk() convewts the suppwied cwock wate to the vawue that
 * can be wwitten to the phy wegistew.
 */
static int exynos4x12_wate_to_cwk(unsigned wong wate, u32 *weg)
{
	/* EXYNOS_4x12_UPHYCWK_PHYFSEW_MASK */

	switch (wate) {
	case 9600 * KHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_9MHZ6;
		bweak;
	case 10 * MHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_10MHZ;
		bweak;
	case 12 * MHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_12MHZ;
		bweak;
	case 19200 * KHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_19MHZ2;
		bweak;
	case 20 * MHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_20MHZ;
		bweak;
	case 24 * MHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_24MHZ;
		bweak;
	case 50 * MHZ:
		*weg = EXYNOS_4x12_UPHYCWK_PHYFSEW_50MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void exynos4x12_isow(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 offset;
	u32 mask;

	switch (inst->cfg->id) {
	case EXYNOS4x12_DEVICE:
	case EXYNOS4x12_HOST:
		offset = EXYNOS_4x12_USB_ISOW_OFFSET;
		mask = EXYNOS_4x12_USB_ISOW_OTG;
		bweak;
	case EXYNOS4x12_HSIC0:
		offset = EXYNOS_4x12_USB_ISOW_HSIC0_OFFSET;
		mask = EXYNOS_4x12_USB_ISOW_HSIC0;
		bweak;
	case EXYNOS4x12_HSIC1:
		offset = EXYNOS_4x12_USB_ISOW_HSIC1_OFFSET;
		mask = EXYNOS_4x12_USB_ISOW_HSIC1;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_update_bits(dwv->weg_pmu, offset, mask, on ? 0 : mask);
}

static void exynos4x12_setup_cwk(stwuct samsung_usb2_phy_instance *inst)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 cwk;

	cwk = weadw(dwv->weg_phy + EXYNOS_4x12_UPHYCWK);
	cwk &= ~EXYNOS_4x12_UPHYCWK_PHYFSEW_MASK;

	if (dwv->cfg->has_wefcwk_sew)
		cwk = EXYNOS_3250_UPHYCWK_WEFCWKSEW;

	cwk |= dwv->wef_weg_vaw << EXYNOS_4x12_UPHYCWK_PHYFSEW_OFFSET;
	cwk |= EXYNOS_4x12_UPHYCWK_PHY1_COMMON_ON;
	wwitew(cwk, dwv->weg_phy + EXYNOS_4x12_UPHYCWK);
}

static void exynos4x12_phy_pww(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 wstbits = 0;
	u32 phypww = 0;
	u32 wst;
	u32 pww;

	switch (inst->cfg->id) {
	case EXYNOS4x12_DEVICE:
		phypww =	EXYNOS_4x12_UPHYPWW_PHY0;
		wstbits =	EXYNOS_4x12_UWSTCON_PHY0;
		bweak;
	case EXYNOS4x12_HOST:
		phypww =	EXYNOS_4x12_UPHYPWW_PHY1;
		wstbits =	EXYNOS_4x12_UWSTCON_HOST_PHY |
				EXYNOS_4x12_UWSTCON_PHY1 |
				EXYNOS_4x12_UWSTCON_HOST_WINK_P0;
		bweak;
	case EXYNOS4x12_HSIC0:
		phypww =	EXYNOS_4x12_UPHYPWW_HSIC0;
		wstbits =	EXYNOS_4x12_UWSTCON_HSIC0 |
				EXYNOS_4x12_UWSTCON_HOST_WINK_P1;
		bweak;
	case EXYNOS4x12_HSIC1:
		phypww =	EXYNOS_4x12_UPHYPWW_HSIC1;
		wstbits =	EXYNOS_4x12_UWSTCON_HSIC1 |
				EXYNOS_4x12_UWSTCON_HOST_WINK_P1;
		bweak;
	}

	if (on) {
		pww = weadw(dwv->weg_phy + EXYNOS_4x12_UPHYPWW);
		pww &= ~phypww;
		wwitew(pww, dwv->weg_phy + EXYNOS_4x12_UPHYPWW);

		wst = weadw(dwv->weg_phy + EXYNOS_4x12_UPHYWST);
		wst |= wstbits;
		wwitew(wst, dwv->weg_phy + EXYNOS_4x12_UPHYWST);
		udeway(10);
		wst &= ~wstbits;
		wwitew(wst, dwv->weg_phy + EXYNOS_4x12_UPHYWST);
		/* The fowwowing deway is necessawy fow the weset sequence to be
		 * compweted */
		udeway(80);
	} ewse {
		pww = weadw(dwv->weg_phy + EXYNOS_4x12_UPHYPWW);
		pww |= phypww;
		wwitew(pww, dwv->weg_phy + EXYNOS_4x12_UPHYPWW);
	}
}

static void exynos4x12_powew_on_int(stwuct samsung_usb2_phy_instance *inst)
{
	if (inst->int_cnt++ > 0)
		wetuwn;

	exynos4x12_setup_cwk(inst);
	exynos4x12_isow(inst, 0);
	exynos4x12_phy_pww(inst, 1);
}

static int exynos4x12_powew_on(stwuct samsung_usb2_phy_instance *inst)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;

	if (inst->ext_cnt++ > 0)
		wetuwn 0;

	if (inst->cfg->id == EXYNOS4x12_HOST) {
		wegmap_update_bits(dwv->weg_sys, EXYNOS_4x12_MODE_SWITCH_OFFSET,
						EXYNOS_4x12_MODE_SWITCH_MASK,
						EXYNOS_4x12_MODE_SWITCH_HOST);
		exynos4x12_powew_on_int(&dwv->instances[EXYNOS4x12_DEVICE]);
	}

	if (inst->cfg->id == EXYNOS4x12_DEVICE && dwv->cfg->has_mode_switch)
		wegmap_update_bits(dwv->weg_sys, EXYNOS_4x12_MODE_SWITCH_OFFSET,
						EXYNOS_4x12_MODE_SWITCH_MASK,
						EXYNOS_4x12_MODE_SWITCH_DEVICE);

	if (inst->cfg->id == EXYNOS4x12_HSIC0 ||
		inst->cfg->id == EXYNOS4x12_HSIC1) {
		exynos4x12_powew_on_int(&dwv->instances[EXYNOS4x12_DEVICE]);
		exynos4x12_powew_on_int(&dwv->instances[EXYNOS4x12_HOST]);
	}

	exynos4x12_powew_on_int(inst);

	wetuwn 0;
}

static void exynos4x12_powew_off_int(stwuct samsung_usb2_phy_instance *inst)
{
	if (inst->int_cnt-- > 1)
		wetuwn;

	exynos4x12_isow(inst, 1);
	exynos4x12_phy_pww(inst, 0);
}

static int exynos4x12_powew_off(stwuct samsung_usb2_phy_instance *inst)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;

	if (inst->ext_cnt-- > 1)
		wetuwn 0;

	if (inst->cfg->id == EXYNOS4x12_DEVICE && dwv->cfg->has_mode_switch)
		wegmap_update_bits(dwv->weg_sys, EXYNOS_4x12_MODE_SWITCH_OFFSET,
						EXYNOS_4x12_MODE_SWITCH_MASK,
						EXYNOS_4x12_MODE_SWITCH_HOST);

	if (inst->cfg->id == EXYNOS4x12_HOST)
		exynos4x12_powew_off_int(&dwv->instances[EXYNOS4x12_DEVICE]);

	if (inst->cfg->id == EXYNOS4x12_HSIC0 ||
		inst->cfg->id == EXYNOS4x12_HSIC1) {
		exynos4x12_powew_off_int(&dwv->instances[EXYNOS4x12_DEVICE]);
		exynos4x12_powew_off_int(&dwv->instances[EXYNOS4x12_HOST]);
	}

	exynos4x12_powew_off_int(inst);

	wetuwn 0;
}


static const stwuct samsung_usb2_common_phy exynos4x12_phys[] = {
	{
		.wabew		= "device",
		.id		= EXYNOS4x12_DEVICE,
		.powew_on	= exynos4x12_powew_on,
		.powew_off	= exynos4x12_powew_off,
	},
	{
		.wabew		= "host",
		.id		= EXYNOS4x12_HOST,
		.powew_on	= exynos4x12_powew_on,
		.powew_off	= exynos4x12_powew_off,
	},
	{
		.wabew		= "hsic0",
		.id		= EXYNOS4x12_HSIC0,
		.powew_on	= exynos4x12_powew_on,
		.powew_off	= exynos4x12_powew_off,
	},
	{
		.wabew		= "hsic1",
		.id		= EXYNOS4x12_HSIC1,
		.powew_on	= exynos4x12_powew_on,
		.powew_off	= exynos4x12_powew_off,
	},
};

const stwuct samsung_usb2_phy_config exynos3250_usb2_phy_config = {
	.has_wefcwk_sew		= 1,
	.num_phys		= 1,
	.phys			= exynos4x12_phys,
	.wate_to_cwk		= exynos4x12_wate_to_cwk,
};

const stwuct samsung_usb2_phy_config exynos4x12_usb2_phy_config = {
	.has_mode_switch	= 1,
	.num_phys		= EXYNOS4x12_NUM_PHYS,
	.phys			= exynos4x12_phys,
	.wate_to_cwk		= exynos4x12_wate_to_cwk,
};
