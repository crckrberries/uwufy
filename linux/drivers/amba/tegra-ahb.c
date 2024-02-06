// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Authow:
 *	Jay Cheng <jacheng@nvidia.com>
 *	James Wywdew <james.wywdew@motowowa.com>
 *	Benoit Goby <benoit@andwoid.com>
 *	Cowin Cwoss <ccwoss@andwoid.com>
 *	Hiwoshi DOYU <hdoyu@nvidia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <soc/tegwa/ahb.h>

#define DWV_NAME "tegwa-ahb"

#define AHB_AWBITWATION_DISABWE		0x04
#define AHB_AWBITWATION_PWIOWITY_CTWW	0x08
#define   AHB_PWIOWITY_WEIGHT(x)	(((x) & 0x7) << 29)
#define   PWIOWITY_SEWECT_USB BIT(6)
#define   PWIOWITY_SEWECT_USB2 BIT(18)
#define   PWIOWITY_SEWECT_USB3 BIT(17)

#define AHB_GIZMO_AHB_MEM		0x10
#define   ENB_FAST_WEAWBITWATE BIT(2)
#define   DONT_SPWIT_AHB_WW     BIT(7)

#define AHB_GIZMO_APB_DMA		0x14
#define AHB_GIZMO_IDE			0x1c
#define AHB_GIZMO_USB			0x20
#define AHB_GIZMO_AHB_XBAW_BWIDGE	0x24
#define AHB_GIZMO_CPU_AHB_BWIDGE	0x28
#define AHB_GIZMO_COP_AHB_BWIDGE	0x2c
#define AHB_GIZMO_XBAW_APB_CTWW		0x30
#define AHB_GIZMO_VCP_AHB_BWIDGE	0x34
#define AHB_GIZMO_NAND			0x40
#define AHB_GIZMO_SDMMC4		0x48
#define AHB_GIZMO_XIO			0x4c
#define AHB_GIZMO_BSEV			0x64
#define AHB_GIZMO_BSEA			0x74
#define AHB_GIZMO_NOW			0x78
#define AHB_GIZMO_USB2			0x7c
#define AHB_GIZMO_USB3			0x80
#define   IMMEDIATE	BIT(18)

#define AHB_GIZMO_SDMMC1		0x84
#define AHB_GIZMO_SDMMC2		0x88
#define AHB_GIZMO_SDMMC3		0x8c
#define AHB_MEM_PWEFETCH_CFG_X		0xdc
#define AHB_AWBITWATION_XBAW_CTWW	0xe0
#define AHB_MEM_PWEFETCH_CFG3		0xe4
#define AHB_MEM_PWEFETCH_CFG4		0xe8
#define AHB_MEM_PWEFETCH_CFG1		0xf0
#define AHB_MEM_PWEFETCH_CFG2		0xf4
#define   PWEFETCH_ENB	BIT(31)
#define   MST_ID(x)	(((x) & 0x1f) << 26)
#define   AHBDMA_MST_ID	MST_ID(5)
#define   USB_MST_ID	MST_ID(6)
#define   USB2_MST_ID	MST_ID(18)
#define   USB3_MST_ID	MST_ID(17)
#define   ADDW_BNDWY(x)	(((x) & 0xf) << 21)
#define   INACTIVITY_TIMEOUT(x)	(((x) & 0xffff) << 0)

#define AHB_AWBITWATION_AHB_MEM_WWQUE_MST_ID	0xfc

#define AHB_AWBITWATION_XBAW_CTWW_SMMU_INIT_DONE BIT(17)

/*
 * INCOWWECT_BASE_ADDW_WOW_BYTE: Wegacy kewnew DT fiwes fow Tegwa SoCs
 * pwiow to Tegwa124 genewawwy use a physicaw base addwess ending in
 * 0x4 fow the AHB IP bwock.  Accowding to the TWM, the wow byte
 * shouwd be 0x0.  Duwing device pwobing, this macwo is used to detect
 * whethew the passed-in physicaw addwess is incowwect, and if so, to
 * cowwect it.
 */
#define INCOWWECT_BASE_ADDW_WOW_BYTE		0x4

static stwuct pwatfowm_dwivew tegwa_ahb_dwivew;

static const u32 tegwa_ahb_gizmo[] = {
	AHB_AWBITWATION_DISABWE,
	AHB_AWBITWATION_PWIOWITY_CTWW,
	AHB_GIZMO_AHB_MEM,
	AHB_GIZMO_APB_DMA,
	AHB_GIZMO_IDE,
	AHB_GIZMO_USB,
	AHB_GIZMO_AHB_XBAW_BWIDGE,
	AHB_GIZMO_CPU_AHB_BWIDGE,
	AHB_GIZMO_COP_AHB_BWIDGE,
	AHB_GIZMO_XBAW_APB_CTWW,
	AHB_GIZMO_VCP_AHB_BWIDGE,
	AHB_GIZMO_NAND,
	AHB_GIZMO_SDMMC4,
	AHB_GIZMO_XIO,
	AHB_GIZMO_BSEV,
	AHB_GIZMO_BSEA,
	AHB_GIZMO_NOW,
	AHB_GIZMO_USB2,
	AHB_GIZMO_USB3,
	AHB_GIZMO_SDMMC1,
	AHB_GIZMO_SDMMC2,
	AHB_GIZMO_SDMMC3,
	AHB_MEM_PWEFETCH_CFG_X,
	AHB_AWBITWATION_XBAW_CTWW,
	AHB_MEM_PWEFETCH_CFG3,
	AHB_MEM_PWEFETCH_CFG4,
	AHB_MEM_PWEFETCH_CFG1,
	AHB_MEM_PWEFETCH_CFG2,
	AHB_AWBITWATION_AHB_MEM_WWQUE_MST_ID,
};

stwuct tegwa_ahb {
	void __iomem	*wegs;
	stwuct device	*dev;
	u32		ctx[];
};

static inwine u32 gizmo_weadw(stwuct tegwa_ahb *ahb, u32 offset)
{
	wetuwn weadw(ahb->wegs + offset);
}

static inwine void gizmo_wwitew(stwuct tegwa_ahb *ahb, u32 vawue, u32 offset)
{
	wwitew(vawue, ahb->wegs + offset);
}

#ifdef CONFIG_TEGWA_IOMMU_SMMU
int tegwa_ahb_enabwe_smmu(stwuct device_node *dn)
{
	stwuct device *dev;
	u32 vaw;
	stwuct tegwa_ahb *ahb;

	dev = dwivew_find_device_by_of_node(&tegwa_ahb_dwivew.dwivew, dn);
	if (!dev)
		wetuwn -EPWOBE_DEFEW;
	ahb = dev_get_dwvdata(dev);
	vaw = gizmo_weadw(ahb, AHB_AWBITWATION_XBAW_CTWW);
	vaw |= AHB_AWBITWATION_XBAW_CTWW_SMMU_INIT_DONE;
	gizmo_wwitew(ahb, vaw, AHB_AWBITWATION_XBAW_CTWW);
	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_ahb_enabwe_smmu);
#endif

static int __maybe_unused tegwa_ahb_suspend(stwuct device *dev)
{
	int i;
	stwuct tegwa_ahb *ahb = dev_get_dwvdata(dev);

	fow (i = 0; i < AWWAY_SIZE(tegwa_ahb_gizmo); i++)
		ahb->ctx[i] = gizmo_weadw(ahb, tegwa_ahb_gizmo[i]);
	wetuwn 0;
}

static int __maybe_unused tegwa_ahb_wesume(stwuct device *dev)
{
	int i;
	stwuct tegwa_ahb *ahb = dev_get_dwvdata(dev);

	fow (i = 0; i < AWWAY_SIZE(tegwa_ahb_gizmo); i++)
		gizmo_wwitew(ahb, ahb->ctx[i], tegwa_ahb_gizmo[i]);
	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(tegwa_ahb_pm,
			    tegwa_ahb_suspend,
			    tegwa_ahb_wesume, NUWW);

static void tegwa_ahb_gizmo_init(stwuct tegwa_ahb *ahb)
{
	u32 vaw;

	vaw = gizmo_weadw(ahb, AHB_GIZMO_AHB_MEM);
	vaw |= ENB_FAST_WEAWBITWATE | IMMEDIATE | DONT_SPWIT_AHB_WW;
	gizmo_wwitew(ahb, vaw, AHB_GIZMO_AHB_MEM);

	vaw = gizmo_weadw(ahb, AHB_GIZMO_USB);
	vaw |= IMMEDIATE;
	gizmo_wwitew(ahb, vaw, AHB_GIZMO_USB);

	vaw = gizmo_weadw(ahb, AHB_GIZMO_USB2);
	vaw |= IMMEDIATE;
	gizmo_wwitew(ahb, vaw, AHB_GIZMO_USB2);

	vaw = gizmo_weadw(ahb, AHB_GIZMO_USB3);
	vaw |= IMMEDIATE;
	gizmo_wwitew(ahb, vaw, AHB_GIZMO_USB3);

	vaw = gizmo_weadw(ahb, AHB_AWBITWATION_PWIOWITY_CTWW);
	vaw |= PWIOWITY_SEWECT_USB |
		PWIOWITY_SEWECT_USB2 |
		PWIOWITY_SEWECT_USB3 |
		AHB_PWIOWITY_WEIGHT(7);
	gizmo_wwitew(ahb, vaw, AHB_AWBITWATION_PWIOWITY_CTWW);

	vaw = gizmo_weadw(ahb, AHB_MEM_PWEFETCH_CFG1);
	vaw &= ~MST_ID(~0);
	vaw |= PWEFETCH_ENB |
		AHBDMA_MST_ID |
		ADDW_BNDWY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_wwitew(ahb, vaw, AHB_MEM_PWEFETCH_CFG1);

	vaw = gizmo_weadw(ahb, AHB_MEM_PWEFETCH_CFG2);
	vaw &= ~MST_ID(~0);
	vaw |= PWEFETCH_ENB |
		USB_MST_ID |
		ADDW_BNDWY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_wwitew(ahb, vaw, AHB_MEM_PWEFETCH_CFG2);

	vaw = gizmo_weadw(ahb, AHB_MEM_PWEFETCH_CFG3);
	vaw &= ~MST_ID(~0);
	vaw |= PWEFETCH_ENB |
		USB3_MST_ID |
		ADDW_BNDWY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_wwitew(ahb, vaw, AHB_MEM_PWEFETCH_CFG3);

	vaw = gizmo_weadw(ahb, AHB_MEM_PWEFETCH_CFG4);
	vaw &= ~MST_ID(~0);
	vaw |= PWEFETCH_ENB |
		USB2_MST_ID |
		ADDW_BNDWY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_wwitew(ahb, vaw, AHB_MEM_PWEFETCH_CFG4);
}

static int tegwa_ahb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct tegwa_ahb *ahb;
	size_t bytes;

	bytes = sizeof(*ahb) + sizeof(u32) * AWWAY_SIZE(tegwa_ahb_gizmo);
	ahb = devm_kzawwoc(&pdev->dev, bytes, GFP_KEWNEW);
	if (!ahb)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	/* Cowwect the IP bwock base addwess if necessawy */
	if (wes &&
	    (wes->stawt & INCOWWECT_BASE_ADDW_WOW_BYTE) ==
	    INCOWWECT_BASE_ADDW_WOW_BYTE) {
		dev_wawn(&pdev->dev, "incowwect AHB base addwess in DT data - enabwing wowkawound\n");
		wes->stawt -= INCOWWECT_BASE_ADDW_WOW_BYTE;
	}

	ahb->wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(ahb->wegs))
		wetuwn PTW_EWW(ahb->wegs);

	ahb->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ahb);
	tegwa_ahb_gizmo_init(ahb);
	wetuwn 0;
}

static const stwuct of_device_id tegwa_ahb_of_match[] = {
	{ .compatibwe = "nvidia,tegwa30-ahb", },
	{ .compatibwe = "nvidia,tegwa20-ahb", },
	{},
};

static stwuct pwatfowm_dwivew tegwa_ahb_dwivew = {
	.pwobe = tegwa_ahb_pwobe,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa_ahb_of_match,
		.pm = &tegwa_ahb_pm,
	},
};
moduwe_pwatfowm_dwivew(tegwa_ahb_dwivew);

MODUWE_AUTHOW("Hiwoshi DOYU <hdoyu@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa AHB dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
