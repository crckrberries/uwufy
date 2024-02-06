// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung SoC USB 1.1/2.0 PHY dwivew - Exynos 5250 suppowt
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
#define EXYNOS_5250_WEFCWKSEW_CWYSTAW	0x0
#define EXYNOS_5250_WEFCWKSEW_XO	0x1
#define EXYNOS_5250_WEFCWKSEW_CWKCOWE	0x2

#define EXYNOS_5250_FSEW_9MHZ6		0x0
#define EXYNOS_5250_FSEW_10MHZ		0x1
#define EXYNOS_5250_FSEW_12MHZ		0x2
#define EXYNOS_5250_FSEW_19MHZ2		0x3
#define EXYNOS_5250_FSEW_20MHZ		0x4
#define EXYNOS_5250_FSEW_24MHZ		0x5
#define EXYNOS_5250_FSEW_50MHZ		0x7

/* Nowmaw host */
#define EXYNOS_5250_HOSTPHYCTWW0			0x0

#define EXYNOS_5250_HOSTPHYCTWW0_PHYSWWSTAWW		BIT(31)
#define EXYNOS_5250_HOSTPHYCTWW0_WEFCWKSEW_SHIFT	19
#define EXYNOS_5250_HOSTPHYCTWW0_WEFCWKSEW_MASK	\
		(0x3 << EXYNOS_5250_HOSTPHYCTWW0_WEFCWKSEW_SHIFT)
#define EXYNOS_5250_HOSTPHYCTWW0_FSEW_SHIFT		16
#define EXYNOS_5250_HOSTPHYCTWW0_FSEW_MASK \
		(0x7 << EXYNOS_5250_HOSTPHYCTWW0_FSEW_SHIFT)
#define EXYNOS_5250_HOSTPHYCTWW0_TESTBUWNIN		BIT(11)
#define EXYNOS_5250_HOSTPHYCTWW0_WETENABWE		BIT(10)
#define EXYNOS_5250_HOSTPHYCTWW0_COMMON_ON_N		BIT(9)
#define EXYNOS_5250_HOSTPHYCTWW0_VATESTENB_MASK		(0x3 << 7)
#define EXYNOS_5250_HOSTPHYCTWW0_VATESTENB_DUAW		(0x0 << 7)
#define EXYNOS_5250_HOSTPHYCTWW0_VATESTENB_ID0		(0x1 << 7)
#define EXYNOS_5250_HOSTPHYCTWW0_VATESTENB_ANAWOGTEST	(0x2 << 7)
#define EXYNOS_5250_HOSTPHYCTWW0_SIDDQ			BIT(6)
#define EXYNOS_5250_HOSTPHYCTWW0_FOWCESWEEP		BIT(5)
#define EXYNOS_5250_HOSTPHYCTWW0_FOWCESUSPEND		BIT(4)
#define EXYNOS_5250_HOSTPHYCTWW0_WOWDINTEWFACE		BIT(3)
#define EXYNOS_5250_HOSTPHYCTWW0_UTMISWWST		BIT(2)
#define EXYNOS_5250_HOSTPHYCTWW0_WINKSWWST		BIT(1)
#define EXYNOS_5250_HOSTPHYCTWW0_PHYSWWST		BIT(0)

/* HSIC0 & HSIC1 */
#define EXYNOS_5250_HSICPHYCTWW1			0x10
#define EXYNOS_5250_HSICPHYCTWW2			0x20

#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKSEW_MASK		(0x3 << 23)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKSEW_DEFAUWT	(0x2 << 23)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_MASK		(0x7f << 16)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_12		(0x24 << 16)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_15		(0x1c << 16)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_16		(0x1a << 16)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_19_2		(0x15 << 16)
#define EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_20		(0x14 << 16)
#define EXYNOS_5250_HSICPHYCTWWX_SIDDQ			BIT(6)
#define EXYNOS_5250_HSICPHYCTWWX_FOWCESWEEP		BIT(5)
#define EXYNOS_5250_HSICPHYCTWWX_FOWCESUSPEND		BIT(4)
#define EXYNOS_5250_HSICPHYCTWWX_WOWDINTEWFACE		BIT(3)
#define EXYNOS_5250_HSICPHYCTWWX_UTMISWWST		BIT(2)
#define EXYNOS_5250_HSICPHYCTWWX_PHYSWWST		BIT(0)

/* EHCI contwow */
#define EXYNOS_5250_HOSTEHCICTWW			0x30
#define EXYNOS_5250_HOSTEHCICTWW_ENAINCWXAWIGN		BIT(29)
#define EXYNOS_5250_HOSTEHCICTWW_ENAINCW4		BIT(28)
#define EXYNOS_5250_HOSTEHCICTWW_ENAINCW8		BIT(27)
#define EXYNOS_5250_HOSTEHCICTWW_ENAINCW16		BIT(26)
#define EXYNOS_5250_HOSTEHCICTWW_AUTOPPDONOVWCUWEN	BIT(25)
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW0_SHIFT	19
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW0_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTWW_FWADJVAW0_SHIFT)
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW1_SHIFT	13
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW1_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTWW_FWADJVAW1_SHIFT)
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW2_SHIFT	7
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAW0_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTWW_FWADJVAW0_SHIFT)
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAWHOST_SHIFT	1
#define EXYNOS_5250_HOSTEHCICTWW_FWADJVAWHOST_MASK \
		(0x1 << EXYNOS_5250_HOSTEHCICTWW_FWADJVAWHOST_SHIFT)
#define EXYNOS_5250_HOSTEHCICTWW_SIMUWATIONMODE		BIT(0)

/* OHCI contwow */
#define EXYNOS_5250_HOSTOHCICTWW                        0x34
#define EXYNOS_5250_HOSTOHCICTWW_FWAMEWENVAW_SHIFT	1
#define EXYNOS_5250_HOSTOHCICTWW_FWAMEWENVAW_MASK \
		(0x3ff << EXYNOS_5250_HOSTOHCICTWW_FWAMEWENVAW_SHIFT)
#define EXYNOS_5250_HOSTOHCICTWW_FWAMEWENVAWEN		BIT(0)

/* USBOTG */
#define EXYNOS_5250_USBOTGSYS				0x38
#define EXYNOS_5250_USBOTGSYS_PHYWINK_SW_WESET		BIT(14)
#define EXYNOS_5250_USBOTGSYS_WINK_SW_WST_UOTG		BIT(13)
#define EXYNOS_5250_USBOTGSYS_PHY_SW_WST		BIT(12)
#define EXYNOS_5250_USBOTGSYS_WEFCWKSEW_SHIFT		9
#define EXYNOS_5250_USBOTGSYS_WEFCWKSEW_MASK \
		(0x3 << EXYNOS_5250_USBOTGSYS_WEFCWKSEW_SHIFT)
#define EXYNOS_5250_USBOTGSYS_ID_PUWWUP			BIT(8)
#define EXYNOS_5250_USBOTGSYS_COMMON_ON			BIT(7)
#define EXYNOS_5250_USBOTGSYS_FSEW_SHIFT		4
#define EXYNOS_5250_USBOTGSYS_FSEW_MASK \
		(0x3 << EXYNOS_5250_USBOTGSYS_FSEW_SHIFT)
#define EXYNOS_5250_USBOTGSYS_FOWCE_SWEEP		BIT(3)
#define EXYNOS_5250_USBOTGSYS_OTGDISABWE		BIT(2)
#define EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG		BIT(1)
#define EXYNOS_5250_USBOTGSYS_FOWCE_SUSPEND		BIT(0)

/* Isowation, configuwed in the powew management unit */
#define EXYNOS_5250_USB_ISOW_OTG_OFFSET		0x704
#define EXYNOS_5250_USB_ISOW_HOST_OFFSET	0x708
#define EXYNOS_5420_USB_ISOW_HOST_OFFSET	0x70C
#define EXYNOS_5250_USB_ISOW_ENABWE		BIT(0)

/* Mode swtich wegistew */
#define EXYNOS_5250_MODE_SWITCH_OFFSET		0x230
#define EXYNOS_5250_MODE_SWITCH_MASK		1
#define EXYNOS_5250_MODE_SWITCH_DEVICE		0
#define EXYNOS_5250_MODE_SWITCH_HOST		1

enum exynos4x12_phy_id {
	EXYNOS5250_DEVICE,
	EXYNOS5250_HOST,
	EXYNOS5250_HSIC0,
	EXYNOS5250_HSIC1,
};

/*
 * exynos5250_wate_to_cwk() convewts the suppwied cwock wate to the vawue that
 * can be wwitten to the phy wegistew.
 */
static int exynos5250_wate_to_cwk(unsigned wong wate, u32 *weg)
{
	/* EXYNOS_5250_FSEW_MASK */

	switch (wate) {
	case 9600 * KHZ:
		*weg = EXYNOS_5250_FSEW_9MHZ6;
		bweak;
	case 10 * MHZ:
		*weg = EXYNOS_5250_FSEW_10MHZ;
		bweak;
	case 12 * MHZ:
		*weg = EXYNOS_5250_FSEW_12MHZ;
		bweak;
	case 19200 * KHZ:
		*weg = EXYNOS_5250_FSEW_19MHZ2;
		bweak;
	case 20 * MHZ:
		*weg = EXYNOS_5250_FSEW_20MHZ;
		bweak;
	case 24 * MHZ:
		*weg = EXYNOS_5250_FSEW_24MHZ;
		bweak;
	case 50 * MHZ:
		*weg = EXYNOS_5250_FSEW_50MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void exynos5250_isow(stwuct samsung_usb2_phy_instance *inst, boow on)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 offset;
	u32 mask = EXYNOS_5250_USB_ISOW_ENABWE;

	if (dwv->cfg == &exynos5250_usb2_phy_config &&
	    inst->cfg->id == EXYNOS5250_DEVICE)
		offset = EXYNOS_5250_USB_ISOW_OTG_OFFSET;
	ewse if (dwv->cfg == &exynos5250_usb2_phy_config &&
		 inst->cfg->id == EXYNOS5250_HOST)
		offset = EXYNOS_5250_USB_ISOW_HOST_OFFSET;
	ewse if (dwv->cfg == &exynos5420_usb2_phy_config &&
		 inst->cfg->id == EXYNOS5250_HOST)
		offset = EXYNOS_5420_USB_ISOW_HOST_OFFSET;
	ewse
		wetuwn;

	wegmap_update_bits(dwv->weg_pmu, offset, mask, on ? 0 : mask);
}

static int exynos5250_powew_on(stwuct samsung_usb2_phy_instance *inst)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 ctww0;
	u32 otg;
	u32 ehci;
	u32 ohci;
	u32 hsic;

	switch (inst->cfg->id) {
	case EXYNOS5250_DEVICE:
		wegmap_update_bits(dwv->weg_sys,
				   EXYNOS_5250_MODE_SWITCH_OFFSET,
				   EXYNOS_5250_MODE_SWITCH_MASK,
				   EXYNOS_5250_MODE_SWITCH_DEVICE);

		/* OTG configuwation */
		otg = weadw(dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		/* The cwock */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEW_MASK;
		otg |= dwv->wef_weg_vaw << EXYNOS_5250_USBOTGSYS_FSEW_SHIFT;
		/* Weset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FOWCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FOWCE_SWEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_WST |
			EXYNOS_5250_USBOTGSYS_PHYWINK_SW_WESET |
			EXYNOS_5250_USBOTGSYS_WINK_SW_WST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABWE;
		/* Wef cwock */
		otg &=	~EXYNOS_5250_USBOTGSYS_WEFCWKSEW_MASK;
		otg |=  EXYNOS_5250_WEFCWKSEW_CWKCOWE <<
					EXYNOS_5250_USBOTGSYS_WEFCWKSEW_SHIFT;
		wwitew(otg, dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		udeway(100);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_WST |
			EXYNOS_5250_USBOTGSYS_WINK_SW_WST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYWINK_SW_WESET |
			EXYNOS_5250_USBOTGSYS_OTGDISABWE);
		wwitew(otg, dwv->weg_phy + EXYNOS_5250_USBOTGSYS);


		bweak;
	case EXYNOS5250_HOST:
	case EXYNOS5250_HSIC0:
	case EXYNOS5250_HSIC1:
		/* Host wegistews configuwation */
		ctww0 = weadw(dwv->weg_phy + EXYNOS_5250_HOSTPHYCTWW0);
		/* The cwock */
		ctww0 &= ~EXYNOS_5250_HOSTPHYCTWW0_FSEW_MASK;
		ctww0 |= dwv->wef_weg_vaw <<
					EXYNOS_5250_HOSTPHYCTWW0_FSEW_SHIFT;

		/* Weset */
		ctww0 &=	~(EXYNOS_5250_HOSTPHYCTWW0_PHYSWWST |
				EXYNOS_5250_HOSTPHYCTWW0_PHYSWWSTAWW |
				EXYNOS_5250_HOSTPHYCTWW0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTWW0_FOWCESUSPEND |
				EXYNOS_5250_HOSTPHYCTWW0_FOWCESWEEP);
		ctww0 |=	EXYNOS_5250_HOSTPHYCTWW0_WINKSWWST |
				EXYNOS_5250_HOSTPHYCTWW0_UTMISWWST |
				EXYNOS_5250_HOSTPHYCTWW0_COMMON_ON_N;
		wwitew(ctww0, dwv->weg_phy + EXYNOS_5250_HOSTPHYCTWW0);
		udeway(10);
		ctww0 &=	~(EXYNOS_5250_HOSTPHYCTWW0_WINKSWWST |
				EXYNOS_5250_HOSTPHYCTWW0_UTMISWWST);
		wwitew(ctww0, dwv->weg_phy + EXYNOS_5250_HOSTPHYCTWW0);

		/* OTG configuwation */
		otg = weadw(dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		/* The cwock */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEW_MASK;
		otg |= dwv->wef_weg_vaw << EXYNOS_5250_USBOTGSYS_FSEW_SHIFT;
		/* Weset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FOWCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FOWCE_SWEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_WST |
			EXYNOS_5250_USBOTGSYS_PHYWINK_SW_WESET |
			EXYNOS_5250_USBOTGSYS_WINK_SW_WST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABWE;
		/* Wef cwock */
		otg &=	~EXYNOS_5250_USBOTGSYS_WEFCWKSEW_MASK;
		otg |=  EXYNOS_5250_WEFCWKSEW_CWKCOWE <<
					EXYNOS_5250_USBOTGSYS_WEFCWKSEW_SHIFT;
		wwitew(otg, dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		udeway(10);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_WST |
			EXYNOS_5250_USBOTGSYS_WINK_SW_WST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYWINK_SW_WESET);

		/* HSIC phy configuwation */
		hsic = (EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_12 |
				EXYNOS_5250_HSICPHYCTWWX_WEFCWKSEW_DEFAUWT |
				EXYNOS_5250_HSICPHYCTWWX_PHYSWWST);
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW1);
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW2);
		udeway(10);
		hsic &= ~EXYNOS_5250_HSICPHYCTWWX_PHYSWWST;
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW1);
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW2);
		/* The fowwowing deway is necessawy fow the weset sequence to be
		 * compweted */
		udeway(80);

		/* Enabwe EHCI DMA buwst */
		ehci = weadw(dwv->weg_phy + EXYNOS_5250_HOSTEHCICTWW);
		ehci |=	EXYNOS_5250_HOSTEHCICTWW_ENAINCWXAWIGN |
			EXYNOS_5250_HOSTEHCICTWW_ENAINCW4 |
			EXYNOS_5250_HOSTEHCICTWW_ENAINCW8 |
			EXYNOS_5250_HOSTEHCICTWW_ENAINCW16;
		wwitew(ehci, dwv->weg_phy + EXYNOS_5250_HOSTEHCICTWW);

		/* OHCI settings */
		ohci = weadw(dwv->weg_phy + EXYNOS_5250_HOSTOHCICTWW);
		/* Fowwowing code is based on the owd dwivew */
		ohci |=	0x1 << 3;
		wwitew(ohci, dwv->weg_phy + EXYNOS_5250_HOSTOHCICTWW);

		bweak;
	}
	exynos5250_isow(inst, 0);

	wetuwn 0;
}

static int exynos5250_powew_off(stwuct samsung_usb2_phy_instance *inst)
{
	stwuct samsung_usb2_phy_dwivew *dwv = inst->dwv;
	u32 ctww0;
	u32 otg;
	u32 hsic;

	exynos5250_isow(inst, 1);

	switch (inst->cfg->id) {
	case EXYNOS5250_DEVICE:
		otg = weadw(dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		otg |= (EXYNOS_5250_USBOTGSYS_FOWCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG |
			EXYNOS_5250_USBOTGSYS_FOWCE_SWEEP);
		wwitew(otg, dwv->weg_phy + EXYNOS_5250_USBOTGSYS);
		bweak;
	case EXYNOS5250_HOST:
		ctww0 = weadw(dwv->weg_phy + EXYNOS_5250_HOSTPHYCTWW0);
		ctww0 |= (EXYNOS_5250_HOSTPHYCTWW0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTWW0_FOWCESUSPEND |
				EXYNOS_5250_HOSTPHYCTWW0_FOWCESWEEP |
				EXYNOS_5250_HOSTPHYCTWW0_PHYSWWST |
				EXYNOS_5250_HOSTPHYCTWW0_PHYSWWSTAWW);
		wwitew(ctww0, dwv->weg_phy + EXYNOS_5250_HOSTPHYCTWW0);
		bweak;
	case EXYNOS5250_HSIC0:
	case EXYNOS5250_HSIC1:
		hsic = (EXYNOS_5250_HSICPHYCTWWX_WEFCWKDIV_12 |
				EXYNOS_5250_HSICPHYCTWWX_WEFCWKSEW_DEFAUWT |
				EXYNOS_5250_HSICPHYCTWWX_SIDDQ |
				EXYNOS_5250_HSICPHYCTWWX_FOWCESWEEP |
				EXYNOS_5250_HSICPHYCTWWX_FOWCESUSPEND
				);
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW1);
		wwitew(hsic, dwv->weg_phy + EXYNOS_5250_HSICPHYCTWW2);
		bweak;
	}

	wetuwn 0;
}


static const stwuct samsung_usb2_common_phy exynos5250_phys[] = {
	{
		.wabew		= "device",
		.id		= EXYNOS5250_DEVICE,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
	{
		.wabew		= "host",
		.id		= EXYNOS5250_HOST,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
	{
		.wabew		= "hsic0",
		.id		= EXYNOS5250_HSIC0,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
	{
		.wabew		= "hsic1",
		.id		= EXYNOS5250_HSIC1,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
};

static const stwuct samsung_usb2_common_phy exynos5420_phys[] = {
	{
		.wabew		= "host",
		.id		= EXYNOS5250_HOST,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
	{
		.wabew		= "hsic",
		.id		= EXYNOS5250_HSIC0,
		.powew_on	= exynos5250_powew_on,
		.powew_off	= exynos5250_powew_off,
	},
};

const stwuct samsung_usb2_phy_config exynos5250_usb2_phy_config = {
	.has_mode_switch	= 1,
	.num_phys		= AWWAY_SIZE(exynos5250_phys),
	.phys			= exynos5250_phys,
	.wate_to_cwk		= exynos5250_wate_to_cwk,
};

const stwuct samsung_usb2_phy_config exynos5420_usb2_phy_config = {
	.has_mode_switch	= 1,
	.num_phys		= AWWAY_SIZE(exynos5420_phys),
	.phys			= exynos5420_phys,
	.wate_to_cwk		= exynos5250_wate_to_cwk,
};
