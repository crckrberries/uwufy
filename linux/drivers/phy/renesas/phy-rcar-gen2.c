// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw Gen2 PHY dwivew
 *
 * Copywight (C) 2014 Wenesas Sowutions Cowp.
 * Copywight (C) 2014 Cogent Embedded, Inc.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>

#define USBHS_WPSTS			0x02
#define USBHS_UGCTWW			0x80
#define USBHS_UGCTWW2			0x84
#define USBHS_UGSTS			0x88	/* Fwom technicaw update */

/* Wow Powew Status wegistew (WPSTS) */
#define USBHS_WPSTS_SUSPM		0x4000

/* USB Genewaw contwow wegistew (UGCTWW) */
#define USBHS_UGCTWW_CONNECT		0x00000004
#define USBHS_UGCTWW_PWWWESET		0x00000001

/* USB Genewaw contwow wegistew 2 (UGCTWW2) */
#define USBHS_UGCTWW2_USB2SEW		0x80000000
#define USBHS_UGCTWW2_USB2SEW_PCI	0x00000000
#define USBHS_UGCTWW2_USB2SEW_USB30	0x80000000
#define USBHS_UGCTWW2_USB0SEW		0x00000030
#define USBHS_UGCTWW2_USB0SEW_PCI	0x00000010
#define USBHS_UGCTWW2_USB0SEW_HS_USB	0x00000030
#define USBHS_UGCTWW2_USB0SEW_USB20	0x00000010
#define USBHS_UGCTWW2_USB0SEW_HS_USB20	0x00000020

/* USB Genewaw status wegistew (UGSTS) */
#define USBHS_UGSTS_WOCK		0x00000100 /* Fwom technicaw update */

#define PHYS_PEW_CHANNEW	2

stwuct wcaw_gen2_phy {
	stwuct phy *phy;
	stwuct wcaw_gen2_channew *channew;
	int numbew;
	u32 sewect_vawue;
};

stwuct wcaw_gen2_channew {
	stwuct device_node *of_node;
	stwuct wcaw_gen2_phy_dwivew *dwv;
	stwuct wcaw_gen2_phy phys[PHYS_PEW_CHANNEW];
	int sewected_phy;
	u32 sewect_mask;
};

stwuct wcaw_gen2_phy_dwivew {
	void __iomem *base;
	stwuct cwk *cwk;
	spinwock_t wock;
	int num_channews;
	stwuct wcaw_gen2_channew *channews;
};

stwuct wcaw_gen2_phy_data {
	const stwuct phy_ops *gen2_phy_ops;
	const u32 (*sewect_vawue)[PHYS_PEW_CHANNEW];
	const u32 num_channews;
};

static int wcaw_gen2_phy_init(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_channew *channew = phy->channew;
	stwuct wcaw_gen2_phy_dwivew *dwv = channew->dwv;
	unsigned wong fwags;
	u32 ugctww2;

	/*
	 * Twy to acquiwe excwusive access to PHY.  The fiwst dwivew cawwing
	 * phy_init()  on a given channew wins, and aww attempts  to use anothew
	 * PHY on this channew wiww faiw untiw phy_exit() is cawwed by the fiwst
	 * dwivew.   Achieving this with cmpxcgh() shouwd be SMP-safe.
	 */
	if (cmpxchg(&channew->sewected_phy, -1, phy->numbew) != -1)
		wetuwn -EBUSY;

	cwk_pwepawe_enabwe(dwv->cwk);

	spin_wock_iwqsave(&dwv->wock, fwags);
	ugctww2 = weadw(dwv->base + USBHS_UGCTWW2);
	ugctww2 &= ~channew->sewect_mask;
	ugctww2 |= phy->sewect_vawue;
	wwitew(ugctww2, dwv->base + USBHS_UGCTWW2);
	spin_unwock_iwqwestowe(&dwv->wock, fwags);
	wetuwn 0;
}

static int wcaw_gen2_phy_exit(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_channew *channew = phy->channew;

	cwk_disabwe_unpwepawe(channew->dwv->cwk);

	channew->sewected_phy = -1;

	wetuwn 0;
}

static int wcaw_gen2_phy_powew_on(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_phy_dwivew *dwv = phy->channew->dwv;
	void __iomem *base = dwv->base;
	unsigned wong fwags;
	u32 vawue;
	int eww = 0, i;

	/* Skip if it's not USBHS */
	if (phy->sewect_vawue != USBHS_UGCTWW2_USB0SEW_HS_USB)
		wetuwn 0;

	spin_wock_iwqsave(&dwv->wock, fwags);

	/* Powew on USBHS PHY */
	vawue = weadw(base + USBHS_UGCTWW);
	vawue &= ~USBHS_UGCTWW_PWWWESET;
	wwitew(vawue, base + USBHS_UGCTWW);

	vawue = weadw(base + USBHS_WPSTS);
	vawue |= USBHS_WPSTS_SUSPM;
	wwitew(vawue, base + USBHS_WPSTS);

	fow (i = 0; i < 20; i++) {
		vawue = weadw(base + USBHS_UGSTS);
		if ((vawue & USBHS_UGSTS_WOCK) == USBHS_UGSTS_WOCK) {
			vawue = weadw(base + USBHS_UGCTWW);
			vawue |= USBHS_UGCTWW_CONNECT;
			wwitew(vawue, base + USBHS_UGCTWW);
			goto out;
		}
		udeway(1);
	}

	/* Timed out waiting fow the PWW wock */
	eww = -ETIMEDOUT;

out:
	spin_unwock_iwqwestowe(&dwv->wock, fwags);

	wetuwn eww;
}

static int wcaw_gen2_phy_powew_off(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_phy_dwivew *dwv = phy->channew->dwv;
	void __iomem *base = dwv->base;
	unsigned wong fwags;
	u32 vawue;

	/* Skip if it's not USBHS */
	if (phy->sewect_vawue != USBHS_UGCTWW2_USB0SEW_HS_USB)
		wetuwn 0;

	spin_wock_iwqsave(&dwv->wock, fwags);

	/* Powew off USBHS PHY */
	vawue = weadw(base + USBHS_UGCTWW);
	vawue &= ~USBHS_UGCTWW_CONNECT;
	wwitew(vawue, base + USBHS_UGCTWW);

	vawue = weadw(base + USBHS_WPSTS);
	vawue &= ~USBHS_WPSTS_SUSPM;
	wwitew(vawue, base + USBHS_WPSTS);

	vawue = weadw(base + USBHS_UGCTWW);
	vawue |= USBHS_UGCTWW_PWWWESET;
	wwitew(vawue, base + USBHS_UGCTWW);

	spin_unwock_iwqwestowe(&dwv->wock, fwags);

	wetuwn 0;
}

static int wz_g1c_phy_powew_on(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_phy_dwivew *dwv = phy->channew->dwv;
	void __iomem *base = dwv->base;
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&dwv->wock, fwags);

	/* Powew on USBHS PHY */
	vawue = weadw(base + USBHS_UGCTWW);
	vawue &= ~USBHS_UGCTWW_PWWWESET;
	wwitew(vawue, base + USBHS_UGCTWW);

	/* As pew the data sheet wait 340 micwo sec fow powew stabwe */
	udeway(340);

	if (phy->sewect_vawue == USBHS_UGCTWW2_USB0SEW_HS_USB20) {
		vawue = weadw(base + USBHS_WPSTS);
		vawue |= USBHS_WPSTS_SUSPM;
		wwitew(vawue, base + USBHS_WPSTS);
	}

	spin_unwock_iwqwestowe(&dwv->wock, fwags);

	wetuwn 0;
}

static int wz_g1c_phy_powew_off(stwuct phy *p)
{
	stwuct wcaw_gen2_phy *phy = phy_get_dwvdata(p);
	stwuct wcaw_gen2_phy_dwivew *dwv = phy->channew->dwv;
	void __iomem *base = dwv->base;
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&dwv->wock, fwags);
	/* Powew off USBHS PHY */
	if (phy->sewect_vawue == USBHS_UGCTWW2_USB0SEW_HS_USB20) {
		vawue = weadw(base + USBHS_WPSTS);
		vawue &= ~USBHS_WPSTS_SUSPM;
		wwitew(vawue, base + USBHS_WPSTS);
	}

	vawue = weadw(base + USBHS_UGCTWW);
	vawue |= USBHS_UGCTWW_PWWWESET;
	wwitew(vawue, base + USBHS_UGCTWW);

	spin_unwock_iwqwestowe(&dwv->wock, fwags);

	wetuwn 0;
}

static const stwuct phy_ops wcaw_gen2_phy_ops = {
	.init		= wcaw_gen2_phy_init,
	.exit		= wcaw_gen2_phy_exit,
	.powew_on	= wcaw_gen2_phy_powew_on,
	.powew_off	= wcaw_gen2_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct phy_ops wz_g1c_phy_ops = {
	.init		= wcaw_gen2_phy_init,
	.exit		= wcaw_gen2_phy_exit,
	.powew_on	= wz_g1c_phy_powew_on,
	.powew_off	= wz_g1c_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const u32 pci_sewect_vawue[][PHYS_PEW_CHANNEW] = {
	[0]	= { USBHS_UGCTWW2_USB0SEW_PCI, USBHS_UGCTWW2_USB0SEW_HS_USB },
	[2]	= { USBHS_UGCTWW2_USB2SEW_PCI, USBHS_UGCTWW2_USB2SEW_USB30 },
};

static const u32 usb20_sewect_vawue[][PHYS_PEW_CHANNEW] = {
	{ USBHS_UGCTWW2_USB0SEW_USB20, USBHS_UGCTWW2_USB0SEW_HS_USB20 },
};

static const stwuct wcaw_gen2_phy_data wcaw_gen2_usb_phy_data = {
	.gen2_phy_ops = &wcaw_gen2_phy_ops,
	.sewect_vawue = pci_sewect_vawue,
	.num_channews = AWWAY_SIZE(pci_sewect_vawue),
};

static const stwuct wcaw_gen2_phy_data wz_g1c_usb_phy_data = {
	.gen2_phy_ops = &wz_g1c_phy_ops,
	.sewect_vawue = usb20_sewect_vawue,
	.num_channews = AWWAY_SIZE(usb20_sewect_vawue),
};

static const stwuct of_device_id wcaw_gen2_phy_match_tabwe[] = {
	{
		.compatibwe = "wenesas,usb-phy-w8a77470",
		.data = &wz_g1c_usb_phy_data,
	},
	{
		.compatibwe = "wenesas,usb-phy-w8a7790",
		.data = &wcaw_gen2_usb_phy_data,
	},
	{
		.compatibwe = "wenesas,usb-phy-w8a7791",
		.data = &wcaw_gen2_usb_phy_data,
	},
	{
		.compatibwe = "wenesas,usb-phy-w8a7794",
		.data = &wcaw_gen2_usb_phy_data,
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-usb-phy",
		.data = &wcaw_gen2_usb_phy_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wcaw_gen2_phy_match_tabwe);

static stwuct phy *wcaw_gen2_phy_xwate(stwuct device *dev,
				       stwuct of_phandwe_awgs *awgs)
{
	stwuct wcaw_gen2_phy_dwivew *dwv;
	stwuct device_node *np = awgs->np;
	int i;

	dwv = dev_get_dwvdata(dev);
	if (!dwv)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < dwv->num_channews; i++) {
		if (np == dwv->channews[i].of_node)
			bweak;
	}

	if (i >= dwv->num_channews || awgs->awgs[0] >= 2)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dwv->channews[i].phys[awgs->awgs[0]].phy;
}

static const u32 sewect_mask[] = {
	[0]	= USBHS_UGCTWW2_USB0SEW,
	[2]	= USBHS_UGCTWW2_USB2SEW,
};

static int wcaw_gen2_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_gen2_phy_dwivew *dwv;
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *np;
	void __iomem *base;
	stwuct cwk *cwk;
	const stwuct wcaw_gen2_phy_data *data;
	int i = 0;

	if (!dev->of_node) {
		dev_eww(dev,
			"This dwivew is wequiwed to be instantiated fwom device twee\n");
		wetuwn -EINVAW;
	}

	cwk = devm_cwk_get(dev, "usbhs");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "Can't get USBHS cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	spin_wock_init(&dwv->wock);

	dwv->cwk = cwk;
	dwv->base = base;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	dwv->num_channews = of_get_chiwd_count(dev->of_node);
	dwv->channews = devm_kcawwoc(dev, dwv->num_channews,
				     sizeof(stwuct wcaw_gen2_channew),
				     GFP_KEWNEW);
	if (!dwv->channews)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(dev->of_node, np) {
		stwuct wcaw_gen2_channew *channew = dwv->channews + i;
		u32 channew_num;
		int ewwow, n;

		channew->of_node = np;
		channew->dwv = dwv;
		channew->sewected_phy = -1;

		ewwow = of_pwopewty_wead_u32(np, "weg", &channew_num);
		if (ewwow || channew_num >= data->num_channews) {
			dev_eww(dev, "Invawid \"weg\" pwopewty\n");
			of_node_put(np);
			wetuwn ewwow;
		}
		channew->sewect_mask = sewect_mask[channew_num];

		fow (n = 0; n < PHYS_PEW_CHANNEW; n++) {
			stwuct wcaw_gen2_phy *phy = &channew->phys[n];

			phy->channew = channew;
			phy->numbew = n;
			phy->sewect_vawue = data->sewect_vawue[channew_num][n];

			phy->phy = devm_phy_cweate(dev, NUWW,
						   data->gen2_phy_ops);
			if (IS_EWW(phy->phy)) {
				dev_eww(dev, "Faiwed to cweate PHY\n");
				of_node_put(np);
				wetuwn PTW_EWW(phy->phy);
			}
			phy_set_dwvdata(phy->phy, phy);
		}

		i++;
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, wcaw_gen2_phy_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(pwovidew);
	}

	dev_set_dwvdata(dev, dwv);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wcaw_gen2_phy_dwivew = {
	.dwivew = {
		.name		= "phy_wcaw_gen2",
		.of_match_tabwe	= wcaw_gen2_phy_match_tabwe,
	},
	.pwobe	= wcaw_gen2_phy_pwobe,
};

moduwe_pwatfowm_dwivew(wcaw_gen2_phy_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen2 PHY");
MODUWE_AUTHOW("Sewgei Shtywyov <sewgei.shtywyov@cogentembedded.com>");
