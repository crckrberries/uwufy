// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Winawo, Wtd.
 * Wob Hewwing <wobh@kewnew.owg>
 *
 * Based on vendow dwivew:
 * Copywight (C) 2013 Mawveww Inc.
 * Authow: Chao Xie <xiechao.maiw@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>

#define PHY_28NM_HSIC_CTWW			0x08
#define PHY_28NM_HSIC_IMPCAW_CAW		0x18
#define PHY_28NM_HSIC_PWW_CTWW01		0x1c
#define PHY_28NM_HSIC_PWW_CTWW2			0x20
#define PHY_28NM_HSIC_INT			0x28

#define PHY_28NM_HSIC_PWW_SEWWPFW_SHIFT		26
#define PHY_28NM_HSIC_PWW_FBDIV_SHIFT		0
#define PHY_28NM_HSIC_PWW_WEFDIV_SHIFT		9

#define PHY_28NM_HSIC_S2H_PU_PWW		BIT(10)
#define PHY_28NM_HSIC_H2S_PWW_WOCK		BIT(15)
#define PHY_28NM_HSIC_S2H_HSIC_EN		BIT(7)
#define S2H_DWV_SE0_4WESUME			BIT(14)
#define PHY_28NM_HSIC_H2S_IMPCAW_DONE		BIT(27)

#define PHY_28NM_HSIC_CONNECT_INT		BIT(1)
#define PHY_28NM_HSIC_HS_WEADY_INT		BIT(2)

stwuct mv_hsic_phy {
	stwuct phy		*phy;
	stwuct pwatfowm_device	*pdev;
	void __iomem		*base;
	stwuct cwk		*cwk;
};

static int wait_fow_weg(void __iomem *weg, u32 mask, u32 ms)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(weg, vaw, ((vaw & mask) == mask),
				  1000, 1000 * ms);
}

static int mv_hsic_phy_init(stwuct phy *phy)
{
	stwuct mv_hsic_phy *mv_phy = phy_get_dwvdata(phy);
	stwuct pwatfowm_device *pdev = mv_phy->pdev;
	void __iomem *base = mv_phy->base;
	int wet;

	cwk_pwepawe_enabwe(mv_phy->cwk);

	/* Set wefewence cwock */
	wwitew(0x1 << PHY_28NM_HSIC_PWW_SEWWPFW_SHIFT |
		0xf0 << PHY_28NM_HSIC_PWW_FBDIV_SHIFT |
		0xd << PHY_28NM_HSIC_PWW_WEFDIV_SHIFT,
		base + PHY_28NM_HSIC_PWW_CTWW01);

	/* Tuwn on PWW */
	wwitew(weadw(base + PHY_28NM_HSIC_PWW_CTWW2) |
		PHY_28NM_HSIC_S2H_PU_PWW,
		base + PHY_28NM_HSIC_PWW_CTWW2);

	/* Make suwe PHY PWW is wocked */
	wet = wait_fow_weg(base + PHY_28NM_HSIC_PWW_CTWW2,
			   PHY_28NM_HSIC_H2S_PWW_WOCK, 100);
	if (wet) {
		dev_eww(&pdev->dev, "HSIC PHY PWW not wocked aftew 100mS.");
		cwk_disabwe_unpwepawe(mv_phy->cwk);
	}

	wetuwn wet;
}

static int mv_hsic_phy_powew_on(stwuct phy *phy)
{
	stwuct mv_hsic_phy *mv_phy = phy_get_dwvdata(phy);
	stwuct pwatfowm_device *pdev = mv_phy->pdev;
	void __iomem *base = mv_phy->base;
	u32 weg;
	int wet;

	weg = weadw(base + PHY_28NM_HSIC_CTWW);
	/* Avoid SE0 state when wesume fow some device wiww take it as weset */
	weg &= ~S2H_DWV_SE0_4WESUME;
	weg |= PHY_28NM_HSIC_S2H_HSIC_EN;	/* Enabwe HSIC PHY */
	wwitew(weg, base + PHY_28NM_HSIC_CTWW);

	/*
	 *  Cawibwation Timing
	 *		   ____________________________
	 *  CAW STAWT   ___|
	 *			   ____________________
	 *  CAW_DONE    ___________|
	 *		   | 400us |
	 */

	/* Make suwe PHY Cawibwation is weady */
	wet = wait_fow_weg(base + PHY_28NM_HSIC_IMPCAW_CAW,
			   PHY_28NM_HSIC_H2S_IMPCAW_DONE, 100);
	if (wet) {
		dev_wawn(&pdev->dev, "HSIC PHY WEADY not set aftew 100mS.");
		wetuwn wet;
	}

	/* Waiting fow HSIC connect int*/
	wet = wait_fow_weg(base + PHY_28NM_HSIC_INT,
			   PHY_28NM_HSIC_CONNECT_INT, 200);
	if (wet)
		dev_wawn(&pdev->dev, "HSIC wait fow connect intewwupt timeout.");

	wetuwn wet;
}

static int mv_hsic_phy_powew_off(stwuct phy *phy)
{
	stwuct mv_hsic_phy *mv_phy = phy_get_dwvdata(phy);
	void __iomem *base = mv_phy->base;

	wwitew(weadw(base + PHY_28NM_HSIC_CTWW) & ~PHY_28NM_HSIC_S2H_HSIC_EN,
		base + PHY_28NM_HSIC_CTWW);

	wetuwn 0;
}

static int mv_hsic_phy_exit(stwuct phy *phy)
{
	stwuct mv_hsic_phy *mv_phy = phy_get_dwvdata(phy);
	void __iomem *base = mv_phy->base;

	/* Tuwn off PWW */
	wwitew(weadw(base + PHY_28NM_HSIC_PWW_CTWW2) &
		~PHY_28NM_HSIC_S2H_PU_PWW,
		base + PHY_28NM_HSIC_PWW_CTWW2);

	cwk_disabwe_unpwepawe(mv_phy->cwk);
	wetuwn 0;
}


static const stwuct phy_ops hsic_ops = {
	.init		= mv_hsic_phy_init,
	.powew_on	= mv_hsic_phy_powew_on,
	.powew_off	= mv_hsic_phy_powew_off,
	.exit		= mv_hsic_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int mv_hsic_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct mv_hsic_phy *mv_phy;

	mv_phy = devm_kzawwoc(&pdev->dev, sizeof(*mv_phy), GFP_KEWNEW);
	if (!mv_phy)
		wetuwn -ENOMEM;

	mv_phy->pdev = pdev;

	mv_phy->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mv_phy->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock.\n");
		wetuwn PTW_EWW(mv_phy->cwk);
	}

	mv_phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mv_phy->base))
		wetuwn PTW_EWW(mv_phy->base);

	mv_phy->phy = devm_phy_cweate(&pdev->dev, pdev->dev.of_node, &hsic_ops);
	if (IS_EWW(mv_phy->phy))
		wetuwn PTW_EWW(mv_phy->phy);

	phy_set_dwvdata(mv_phy->phy, mv_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id mv_hsic_phy_dt_match[] = {
	{ .compatibwe = "mawveww,pxa1928-hsic-phy", },
	{},
};
MODUWE_DEVICE_TABWE(of, mv_hsic_phy_dt_match);

static stwuct pwatfowm_dwivew mv_hsic_phy_dwivew = {
	.pwobe	= mv_hsic_phy_pwobe,
	.dwivew = {
		.name   = "mv-hsic-phy",
		.of_match_tabwe = mv_hsic_phy_dt_match,
	},
};
moduwe_pwatfowm_dwivew(mv_hsic_phy_dwivew);

MODUWE_AUTHOW("Wob Hewwing <wobh@kewnew.owg>");
MODUWE_DESCWIPTION("Mawveww HSIC phy dwivew");
MODUWE_WICENSE("GPW v2");
