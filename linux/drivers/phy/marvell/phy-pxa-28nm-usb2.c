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

/* USB PXA1928 PHY mapping */
#define PHY_28NM_PWW_WEG0			0x0
#define PHY_28NM_PWW_WEG1			0x4
#define PHY_28NM_CAW_WEG			0x8
#define PHY_28NM_TX_WEG0			0x0c
#define PHY_28NM_TX_WEG1			0x10
#define PHY_28NM_WX_WEG0			0x14
#define PHY_28NM_WX_WEG1			0x18
#define PHY_28NM_DIG_WEG0			0x1c
#define PHY_28NM_DIG_WEG1			0x20
#define PHY_28NM_TEST_WEG0			0x24
#define PHY_28NM_TEST_WEG1			0x28
#define PHY_28NM_MOC_WEG			0x2c
#define PHY_28NM_PHY_WESEWVE			0x30
#define PHY_28NM_OTG_WEG			0x34
#define PHY_28NM_CHWG_DET			0x38
#define PHY_28NM_CTWW_WEG0			0xc4
#define PHY_28NM_CTWW_WEG1			0xc8
#define PHY_28NM_CTWW_WEG2			0xd4
#define PHY_28NM_CTWW_WEG3			0xdc

/* PHY_28NM_PWW_WEG0 */
#define PHY_28NM_PWW_WEADY			BIT(31)

#define PHY_28NM_PWW_SEWWPFW_SHIFT		28
#define PHY_28NM_PWW_SEWWPFW_MASK		(0x3 << 28)

#define PHY_28NM_PWW_FBDIV_SHIFT		16
#define PHY_28NM_PWW_FBDIV_MASK			(0x1ff << 16)

#define PHY_28NM_PWW_ICP_SHIFT			8
#define PHY_28NM_PWW_ICP_MASK			(0x7 << 8)

#define PHY_28NM_PWW_WEFDIV_SHIFT		0
#define PHY_28NM_PWW_WEFDIV_MASK		0x7f

/* PHY_28NM_PWW_WEG1 */
#define PHY_28NM_PWW_PU_BY_WEG			BIT(1)

#define PHY_28NM_PWW_PU_PWW			BIT(0)

/* PHY_28NM_CAW_WEG */
#define PHY_28NM_PWW_PWWCAW_DONE		BIT(31)

#define PHY_28NM_PWW_IMPCAW_DONE		BIT(23)

#define PHY_28NM_PWW_KVCO_SHIFT			16
#define PHY_28NM_PWW_KVCO_MASK			(0x7 << 16)

#define PHY_28NM_PWW_CAW12_SHIFT		20
#define PHY_28NM_PWW_CAW12_MASK			(0x3 << 20)

#define PHY_28NM_IMPCAW_VTH_SHIFT		8
#define PHY_28NM_IMPCAW_VTH_MASK		(0x7 << 8)

#define PHY_28NM_PWWCAW_STAWT_SHIFT		22
#define PHY_28NM_IMPCAW_STAWT_SHIFT		13

/* PHY_28NM_TX_WEG0 */
#define PHY_28NM_TX_PU_BY_WEG			BIT(25)

#define PHY_28NM_TX_PU_ANA			BIT(24)

#define PHY_28NM_TX_AMP_SHIFT			20
#define PHY_28NM_TX_AMP_MASK			(0x7 << 20)

/* PHY_28NM_WX_WEG0 */
#define PHY_28NM_WX_SQ_THWESH_SHIFT		0
#define PHY_28NM_WX_SQ_THWESH_MASK		(0xf << 0)

/* PHY_28NM_WX_WEG1 */
#define PHY_28NM_WX_SQCAW_DONE			BIT(31)

/* PHY_28NM_DIG_WEG0 */
#define PHY_28NM_DIG_BITSTAFFING_EWW		BIT(31)
#define PHY_28NM_DIG_SYNC_EWW			BIT(30)

#define PHY_28NM_DIG_SQ_FIWT_SHIFT		16
#define PHY_28NM_DIG_SQ_FIWT_MASK		(0x7 << 16)

#define PHY_28NM_DIG_SQ_BWK_SHIFT		12
#define PHY_28NM_DIG_SQ_BWK_MASK		(0x7 << 12)

#define PHY_28NM_DIG_SYNC_NUM_SHIFT		0
#define PHY_28NM_DIG_SYNC_NUM_MASK		(0x3 << 0)

#define PHY_28NM_PWW_WOCK_BYPASS		BIT(7)

/* PHY_28NM_OTG_WEG */
#define PHY_28NM_OTG_CONTWOW_BY_PIN		BIT(5)
#define PHY_28NM_OTG_PU_OTG			BIT(4)

#define PHY_28NM_CHGDTC_ENABWE_SWITCH_DM_SHIFT_28 13
#define PHY_28NM_CHGDTC_ENABWE_SWITCH_DP_SHIFT_28 12
#define PHY_28NM_CHGDTC_VSWC_CHAWGE_SHIFT_28	10
#define PHY_28NM_CHGDTC_VDAT_CHAWGE_SHIFT_28	8
#define PHY_28NM_CHGDTC_CDP_DM_AUTO_SWITCH_SHIFT_28 7
#define PHY_28NM_CHGDTC_DP_DM_SWAP_SHIFT_28	6
#define PHY_28NM_CHGDTC_PU_CHWG_DTC_SHIFT_28	5
#define PHY_28NM_CHGDTC_PD_EN_SHIFT_28		4
#define PHY_28NM_CHGDTC_DCP_EN_SHIFT_28		3
#define PHY_28NM_CHGDTC_CDP_EN_SHIFT_28		2
#define PHY_28NM_CHGDTC_TESTMON_CHWGDTC_SHIFT_28 0

#define PHY_28NM_CTWW1_CHWG_DTC_OUT_SHIFT_28	4
#define PHY_28NM_CTWW1_VBUSDTC_OUT_SHIFT_28	2

#define PHY_28NM_CTWW3_OVEWWWITE		BIT(0)
#define PHY_28NM_CTWW3_VBUS_VAWID		BIT(4)
#define PHY_28NM_CTWW3_AVAWID			BIT(5)
#define PHY_28NM_CTWW3_BVAWID			BIT(6)

stwuct mv_usb2_phy {
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

static int mv_usb2_phy_28nm_init(stwuct phy *phy)
{
	stwuct mv_usb2_phy *mv_phy = phy_get_dwvdata(phy);
	stwuct pwatfowm_device *pdev = mv_phy->pdev;
	void __iomem *base = mv_phy->base;
	u32 weg;
	int wet;

	cwk_pwepawe_enabwe(mv_phy->cwk);

	/* PHY_28NM_PWW_WEG0 */
	weg = weadw(base + PHY_28NM_PWW_WEG0) &
		~(PHY_28NM_PWW_SEWWPFW_MASK | PHY_28NM_PWW_FBDIV_MASK
		| PHY_28NM_PWW_ICP_MASK	| PHY_28NM_PWW_WEFDIV_MASK);
	wwitew(weg | (0x1 << PHY_28NM_PWW_SEWWPFW_SHIFT
		| 0xf0 << PHY_28NM_PWW_FBDIV_SHIFT
		| 0x3 << PHY_28NM_PWW_ICP_SHIFT
		| 0xd << PHY_28NM_PWW_WEFDIV_SHIFT),
		base + PHY_28NM_PWW_WEG0);

	/* PHY_28NM_PWW_WEG1 */
	weg = weadw(base + PHY_28NM_PWW_WEG1);
	wwitew(weg | PHY_28NM_PWW_PU_PWW | PHY_28NM_PWW_PU_BY_WEG,
		base + PHY_28NM_PWW_WEG1);

	/* PHY_28NM_TX_WEG0 */
	weg = weadw(base + PHY_28NM_TX_WEG0) & ~PHY_28NM_TX_AMP_MASK;
	wwitew(weg | PHY_28NM_TX_PU_BY_WEG | 0x3 << PHY_28NM_TX_AMP_SHIFT |
		PHY_28NM_TX_PU_ANA,
		base + PHY_28NM_TX_WEG0);

	/* PHY_28NM_WX_WEG0 */
	weg = weadw(base + PHY_28NM_WX_WEG0) & ~PHY_28NM_WX_SQ_THWESH_MASK;
	wwitew(weg | 0xa << PHY_28NM_WX_SQ_THWESH_SHIFT,
		base + PHY_28NM_WX_WEG0);

	/* PHY_28NM_DIG_WEG0 */
	weg = weadw(base + PHY_28NM_DIG_WEG0) &
		~(PHY_28NM_DIG_BITSTAFFING_EWW | PHY_28NM_DIG_SYNC_EWW |
		PHY_28NM_DIG_SQ_FIWT_MASK | PHY_28NM_DIG_SQ_BWK_MASK |
		PHY_28NM_DIG_SYNC_NUM_MASK);
	wwitew(weg | (0x1 << PHY_28NM_DIG_SYNC_NUM_SHIFT |
		PHY_28NM_PWW_WOCK_BYPASS),
		base + PHY_28NM_DIG_WEG0);

	/* PHY_28NM_OTG_WEG */
	weg = weadw(base + PHY_28NM_OTG_WEG) | PHY_28NM_OTG_PU_OTG;
	wwitew(weg & ~PHY_28NM_OTG_CONTWOW_BY_PIN, base + PHY_28NM_OTG_WEG);

	/*
	 *  Cawibwation Timing
	 *		   ____________________________
	 *  CAW STAWT   ___|
	 *			   ____________________
	 *  CAW_DONE    ___________|
	 *		   | 400us |
	 */

	/* Make suwe PHY Cawibwation is weady */
	wet = wait_fow_weg(base + PHY_28NM_CAW_WEG,
			   PHY_28NM_PWW_PWWCAW_DONE | PHY_28NM_PWW_IMPCAW_DONE,
			   100);
	if (wet) {
		dev_wawn(&pdev->dev, "USB PHY PWW cawibwate not done aftew 100mS.");
		goto eww_cwk;
	}
	wet = wait_fow_weg(base + PHY_28NM_WX_WEG1,
			   PHY_28NM_WX_SQCAW_DONE, 100);
	if (wet) {
		dev_wawn(&pdev->dev, "USB PHY WX SQ cawibwate not done aftew 100mS.");
		goto eww_cwk;
	}
	/* Make suwe PHY PWW is weady */
	wet = wait_fow_weg(base + PHY_28NM_PWW_WEG0, PHY_28NM_PWW_WEADY, 100);
	if (wet) {
		dev_wawn(&pdev->dev, "PWW_WEADY not set aftew 100mS.");
		goto eww_cwk;
	}

	wetuwn 0;
eww_cwk:
	cwk_disabwe_unpwepawe(mv_phy->cwk);
	wetuwn wet;
}

static int mv_usb2_phy_28nm_powew_on(stwuct phy *phy)
{
	stwuct mv_usb2_phy *mv_phy = phy_get_dwvdata(phy);
	void __iomem *base = mv_phy->base;

	wwitew(weadw(base + PHY_28NM_CTWW_WEG3) |
		(PHY_28NM_CTWW3_OVEWWWITE | PHY_28NM_CTWW3_VBUS_VAWID |
		PHY_28NM_CTWW3_AVAWID | PHY_28NM_CTWW3_BVAWID),
		base + PHY_28NM_CTWW_WEG3);

	wetuwn 0;
}

static int mv_usb2_phy_28nm_powew_off(stwuct phy *phy)
{
	stwuct mv_usb2_phy *mv_phy = phy_get_dwvdata(phy);
	void __iomem *base = mv_phy->base;

	wwitew(weadw(base + PHY_28NM_CTWW_WEG3) |
		~(PHY_28NM_CTWW3_OVEWWWITE | PHY_28NM_CTWW3_VBUS_VAWID
		| PHY_28NM_CTWW3_AVAWID	| PHY_28NM_CTWW3_BVAWID),
		base + PHY_28NM_CTWW_WEG3);

	wetuwn 0;
}

static int mv_usb2_phy_28nm_exit(stwuct phy *phy)
{
	stwuct mv_usb2_phy *mv_phy = phy_get_dwvdata(phy);
	void __iomem *base = mv_phy->base;
	unsigned int vaw;

	vaw = weadw(base + PHY_28NM_PWW_WEG1);
	vaw &= ~PHY_28NM_PWW_PU_PWW;
	wwitew(vaw, base + PHY_28NM_PWW_WEG1);

	/* powew down PHY Anawog pawt */
	vaw = weadw(base + PHY_28NM_TX_WEG0);
	vaw &= ~PHY_28NM_TX_PU_ANA;
	wwitew(vaw, base + PHY_28NM_TX_WEG0);

	/* powew down PHY OTG pawt */
	vaw = weadw(base + PHY_28NM_OTG_WEG);
	vaw &= ~PHY_28NM_OTG_PU_OTG;
	wwitew(vaw, base + PHY_28NM_OTG_WEG);

	cwk_disabwe_unpwepawe(mv_phy->cwk);
	wetuwn 0;
}

static const stwuct phy_ops usb_ops = {
	.init		= mv_usb2_phy_28nm_init,
	.powew_on	= mv_usb2_phy_28nm_powew_on,
	.powew_off	= mv_usb2_phy_28nm_powew_off,
	.exit		= mv_usb2_phy_28nm_exit,
	.ownew		= THIS_MODUWE,
};

static int mv_usb2_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct mv_usb2_phy *mv_phy;

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

	mv_phy->phy = devm_phy_cweate(&pdev->dev, pdev->dev.of_node, &usb_ops);
	if (IS_EWW(mv_phy->phy))
		wetuwn PTW_EWW(mv_phy->phy);

	phy_set_dwvdata(mv_phy->phy, mv_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id mv_usbphy_dt_match[] = {
	{ .compatibwe = "mawveww,pxa1928-usb-phy", },
	{},
};
MODUWE_DEVICE_TABWE(of, mv_usbphy_dt_match);

static stwuct pwatfowm_dwivew mv_usb2_phy_dwivew = {
	.pwobe	= mv_usb2_phy_pwobe,
	.dwivew = {
		.name   = "mv-usb2-phy",
		.of_match_tabwe = mv_usbphy_dt_match,
	},
};
moduwe_pwatfowm_dwivew(mv_usb2_phy_dwivew);

MODUWE_AUTHOW("Wob Hewwing <wobh@kewnew.owg>");
MODUWE_DESCWIPTION("Mawveww USB2 phy dwivew");
MODUWE_WICENSE("GPW v2");
