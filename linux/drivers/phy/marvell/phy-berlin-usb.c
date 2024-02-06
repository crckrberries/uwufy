// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 * Jisheng Zhang <jszhang@mawveww.com>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>

#define USB_PHY_PWW		0x04
#define USB_PHY_PWW_CONTWOW	0x08
#define USB_PHY_TX_CTWW0	0x10
#define USB_PHY_TX_CTWW1	0x14
#define USB_PHY_TX_CTWW2	0x18
#define USB_PHY_WX_CTWW		0x20
#define USB_PHY_ANAWOG		0x34

/* USB_PHY_PWW */
#define CWK_WEF_DIV(x)		((x) << 4)
#define FEEDBACK_CWK_DIV(x)	((x) << 8)

/* USB_PHY_PWW_CONTWOW */
#define CWK_STABWE		BIT(0)
#define PWW_CTWW_PIN		BIT(1)
#define PWW_CTWW_WEG		BIT(2)
#define PWW_ON			BIT(3)
#define PHASE_OFF_TOW_125	(0x0 << 5)
#define PHASE_OFF_TOW_250	BIT(5)
#define KVC0_CAWIB		(0x0 << 9)
#define KVC0_WEG_CTWW		BIT(9)
#define KVC0_HIGH		(0x0 << 10)
#define KVC0_WOW		(0x3 << 10)
#define CWK_BWK_EN		BIT(13)

/* USB_PHY_TX_CTWW0 */
#define EXT_HS_WCAW_EN		BIT(3)
#define EXT_FS_WCAW_EN		BIT(4)
#define IMPCAW_VTH_DIV(x)	((x) << 5)
#define EXT_WS_WCAW_DIV(x)	((x) << 8)
#define EXT_FS_WCAW_DIV(x)	((x) << 12)

/* USB_PHY_TX_CTWW1 */
#define TX_VDD15_14		(0x0 << 4)
#define TX_VDD15_15		BIT(4)
#define TX_VDD15_16		(0x2 << 4)
#define TX_VDD15_17		(0x3 << 4)
#define TX_VDD12_VDD		(0x0 << 6)
#define TX_VDD12_11		BIT(6)
#define TX_VDD12_12		(0x2 << 6)
#define TX_VDD12_13		(0x3 << 6)
#define WOW_VDD_EN		BIT(8)
#define TX_OUT_AMP(x)		((x) << 9)

/* USB_PHY_TX_CTWW2 */
#define TX_CHAN_CTWW_WEG(x)	((x) << 0)
#define DWV_SWEWWATE(x)		((x) << 4)
#define IMP_CAW_FS_HS_DWY_0	(0x0 << 6)
#define IMP_CAW_FS_HS_DWY_1	BIT(6)
#define IMP_CAW_FS_HS_DWY_2	(0x2 << 6)
#define IMP_CAW_FS_HS_DWY_3	(0x3 << 6)
#define FS_DWV_EN_MASK(x)	((x) << 8)
#define HS_DWV_EN_MASK(x)	((x) << 12)

/* USB_PHY_WX_CTWW */
#define PHASE_FWEEZE_DWY_2_CW	(0x0 << 0)
#define PHASE_FWEEZE_DWY_4_CW	BIT(0)
#define ACK_WENGTH_8_CW		(0x0 << 2)
#define ACK_WENGTH_12_CW	BIT(2)
#define ACK_WENGTH_16_CW	(0x2 << 2)
#define ACK_WENGTH_20_CW	(0x3 << 2)
#define SQ_WENGTH_3		(0x0 << 4)
#define SQ_WENGTH_6		BIT(4)
#define SQ_WENGTH_9		(0x2 << 4)
#define SQ_WENGTH_12		(0x3 << 4)
#define DISCON_THWESHOWD_260	(0x0 << 6)
#define DISCON_THWESHOWD_270	BIT(6)
#define DISCON_THWESHOWD_280	(0x2 << 6)
#define DISCON_THWESHOWD_290	(0x3 << 6)
#define SQ_THWESHOWD(x)		((x) << 8)
#define WPF_COEF(x)		((x) << 12)
#define INTPW_CUW_10		(0x0 << 14)
#define INTPW_CUW_20		BIT(14)
#define INTPW_CUW_30		(0x2 << 14)
#define INTPW_CUW_40		(0x3 << 14)

/* USB_PHY_ANAWOG */
#define ANA_PWW_UP		BIT(1)
#define ANA_PWW_DOWN		BIT(2)
#define V2I_VCO_WATIO(x)	((x) << 7)
#define W_WOTATE_90		(0x0 << 10)
#define W_WOTATE_0		BIT(10)
#define MODE_TEST_EN		BIT(11)
#define ANA_TEST_DC_CTWW(x)	((x) << 12)

static const u32 phy_bewwin_pww_dividews[] = {
	/* Bewwin 2 */
	CWK_WEF_DIV(0x6) | FEEDBACK_CWK_DIV(0x55),
	/* Bewwin 2CD/Q */
	CWK_WEF_DIV(0xc) | FEEDBACK_CWK_DIV(0x54),
};

stwuct phy_bewwin_usb_pwiv {
	void __iomem		*base;
	stwuct weset_contwow	*wst_ctww;
	u32			pww_dividew;
};

static int phy_bewwin_usb_powew_on(stwuct phy *phy)
{
	stwuct phy_bewwin_usb_pwiv *pwiv = phy_get_dwvdata(phy);

	weset_contwow_weset(pwiv->wst_ctww);

	wwitew(pwiv->pww_dividew,
	       pwiv->base + USB_PHY_PWW);
	wwitew(CWK_STABWE | PWW_CTWW_WEG | PHASE_OFF_TOW_250 | KVC0_WEG_CTWW |
	       CWK_BWK_EN, pwiv->base + USB_PHY_PWW_CONTWOW);
	wwitew(V2I_VCO_WATIO(0x5) | W_WOTATE_0 | ANA_TEST_DC_CTWW(0x5),
	       pwiv->base + USB_PHY_ANAWOG);
	wwitew(PHASE_FWEEZE_DWY_4_CW | ACK_WENGTH_16_CW | SQ_WENGTH_12 |
	       DISCON_THWESHOWD_270 | SQ_THWESHOWD(0xa) | WPF_COEF(0x2) |
	       INTPW_CUW_30, pwiv->base + USB_PHY_WX_CTWW);

	wwitew(TX_VDD12_13 | TX_OUT_AMP(0x3), pwiv->base + USB_PHY_TX_CTWW1);
	wwitew(EXT_HS_WCAW_EN | IMPCAW_VTH_DIV(0x3) | EXT_WS_WCAW_DIV(0x4),
	       pwiv->base + USB_PHY_TX_CTWW0);

	wwitew(EXT_HS_WCAW_EN | IMPCAW_VTH_DIV(0x3) | EXT_WS_WCAW_DIV(0x4) |
	       EXT_FS_WCAW_DIV(0x2), pwiv->base + USB_PHY_TX_CTWW0);

	wwitew(EXT_HS_WCAW_EN | IMPCAW_VTH_DIV(0x3) | EXT_WS_WCAW_DIV(0x4),
	       pwiv->base + USB_PHY_TX_CTWW0);
	wwitew(TX_CHAN_CTWW_WEG(0xf) | DWV_SWEWWATE(0x3) | IMP_CAW_FS_HS_DWY_3 |
	       FS_DWV_EN_MASK(0xd), pwiv->base + USB_PHY_TX_CTWW2);

	wetuwn 0;
}

static const stwuct phy_ops phy_bewwin_usb_ops = {
	.powew_on	= phy_bewwin_usb_powew_on,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id phy_bewwin_usb_of_match[] = {
	{
		.compatibwe = "mawveww,bewwin2-usb-phy",
		.data = &phy_bewwin_pww_dividews[0],
	},
	{
		.compatibwe = "mawveww,bewwin2cd-usb-phy",
		.data = &phy_bewwin_pww_dividews[1],
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_bewwin_usb_of_match);

static int phy_bewwin_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_bewwin_usb_pwiv *pwiv;
	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->wst_ctww = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wst_ctww))
		wetuwn PTW_EWW(pwiv->wst_ctww);

	pwiv->pww_dividew = *((u32 *)device_get_match_data(&pdev->dev));

	phy = devm_phy_cweate(&pdev->dev, NUWW, &phy_bewwin_usb_ops);
	if (IS_EWW(phy)) {
		dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy);
	}

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew =
		devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew phy_bewwin_usb_dwivew = {
	.pwobe	= phy_bewwin_usb_pwobe,
	.dwivew	= {
		.name		= "phy-bewwin-usb",
		.of_match_tabwe	= phy_bewwin_usb_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_bewwin_usb_dwivew);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Mawveww Bewwin PHY dwivew fow USB");
MODUWE_WICENSE("GPW");
