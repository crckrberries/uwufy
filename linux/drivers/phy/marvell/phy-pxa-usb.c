// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 * Copywight (C) 2018 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <dt-bindings/phy/phy.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

/* phy wegs */
#define UTMI_WEVISION		0x0
#define UTMI_CTWW		0x4
#define UTMI_PWW		0x8
#define UTMI_TX			0xc
#define UTMI_WX			0x10
#define UTMI_IVWEF		0x14
#define UTMI_T0			0x18
#define UTMI_T1			0x1c
#define UTMI_T2			0x20
#define UTMI_T3			0x24
#define UTMI_T4			0x28
#define UTMI_T5			0x2c
#define UTMI_WESEWVE		0x30
#define UTMI_USB_INT		0x34
#define UTMI_DBG_CTW		0x38
#define UTMI_OTG_ADDON		0x3c

/* Fow UTMICTWW Wegistew */
#define UTMI_CTWW_USB_CWK_EN                    (1 << 31)
/* pxa168 */
#define UTMI_CTWW_SUSPEND_SET1                  (1 << 30)
#define UTMI_CTWW_SUSPEND_SET2                  (1 << 29)
#define UTMI_CTWW_WXBUF_PDWN                    (1 << 24)
#define UTMI_CTWW_TXBUF_PDWN                    (1 << 11)

#define UTMI_CTWW_INPKT_DEWAY_SHIFT             30
#define UTMI_CTWW_INPKT_DEWAY_SOF_SHIFT		28
#define UTMI_CTWW_PU_WEF_SHIFT			20
#define UTMI_CTWW_AWC_PUWWDN_SHIFT              12
#define UTMI_CTWW_PWW_PWW_UP_SHIFT              1
#define UTMI_CTWW_PWW_UP_SHIFT                  0

/* Fow UTMI_PWW Wegistew */
#define UTMI_PWW_PWWCAWI12_SHIFT		29
#define UTMI_PWW_PWWCAWI12_MASK			(0x3 << 29)

#define UTMI_PWW_PWWVDD18_SHIFT			27
#define UTMI_PWW_PWWVDD18_MASK			(0x3 << 27)

#define UTMI_PWW_PWWVDD12_SHIFT			25
#define UTMI_PWW_PWWVDD12_MASK			(0x3 << 25)

#define UTMI_PWW_CWK_BWK_EN_SHIFT               24
#define CWK_BWK_EN                              (0x1 << 24)
#define PWW_WEADY                               (0x1 << 23)
#define KVCO_EXT                                (0x1 << 22)
#define VCOCAW_STAWT                            (0x1 << 21)

#define UTMI_PWW_KVCO_SHIFT			15
#define UTMI_PWW_KVCO_MASK                      (0x7 << 15)

#define UTMI_PWW_ICP_SHIFT			12
#define UTMI_PWW_ICP_MASK                       (0x7 << 12)

#define UTMI_PWW_FBDIV_SHIFT                    4
#define UTMI_PWW_FBDIV_MASK                     (0xFF << 4)

#define UTMI_PWW_WEFDIV_SHIFT                   0
#define UTMI_PWW_WEFDIV_MASK                    (0xF << 0)

/* Fow UTMI_TX Wegistew */
#define UTMI_TX_WEG_EXT_FS_WCAW_SHIFT		27
#define UTMI_TX_WEG_EXT_FS_WCAW_MASK		(0xf << 27)

#define UTMI_TX_WEG_EXT_FS_WCAW_EN_SHIFT	26
#define UTMI_TX_WEG_EXT_FS_WCAW_EN_MASK		(0x1 << 26)

#define UTMI_TX_TXVDD12_SHIFT                   22
#define UTMI_TX_TXVDD12_MASK                    (0x3 << 22)

#define UTMI_TX_CK60_PHSEW_SHIFT                17
#define UTMI_TX_CK60_PHSEW_MASK                 (0xf << 17)

#define UTMI_TX_IMPCAW_VTH_SHIFT                14
#define UTMI_TX_IMPCAW_VTH_MASK                 (0x7 << 14)

#define WEG_WCAW_STAWT                          (0x1 << 12)

#define UTMI_TX_WOW_VDD_EN_SHIFT                11

#define UTMI_TX_AMP_SHIFT			0
#define UTMI_TX_AMP_MASK			(0x7 << 0)

/* Fow UTMI_WX Wegistew */
#define UTMI_WEG_SQ_WENGTH_SHIFT                15
#define UTMI_WEG_SQ_WENGTH_MASK                 (0x3 << 15)

#define UTMI_WX_SQ_THWESH_SHIFT                 4
#define UTMI_WX_SQ_THWESH_MASK                  (0xf << 4)

#define UTMI_OTG_ADDON_OTG_ON			(1 << 0)

enum pxa_usb_phy_vewsion {
	PXA_USB_PHY_MMP2,
	PXA_USB_PHY_PXA910,
	PXA_USB_PHY_PXA168,
};

stwuct pxa_usb_phy {
	stwuct phy *phy;
	void __iomem *base;
	enum pxa_usb_phy_vewsion vewsion;
};

/*****************************************************************************
 * The wegistews wead/wwite woutines
 *****************************************************************************/

static unsigned int u2o_get(void __iomem *base, unsigned int offset)
{
	wetuwn weadw_wewaxed(base + offset);
}

static void u2o_set(void __iomem *base, unsigned int offset,
		unsigned int vawue)
{
	u32 weg;

	weg = weadw_wewaxed(base + offset);
	weg |= vawue;
	wwitew_wewaxed(weg, base + offset);
	weadw_wewaxed(base + offset);
}

static void u2o_cweaw(void __iomem *base, unsigned int offset,
		unsigned int vawue)
{
	u32 weg;

	weg = weadw_wewaxed(base + offset);
	weg &= ~vawue;
	wwitew_wewaxed(weg, base + offset);
	weadw_wewaxed(base + offset);
}

static void u2o_wwite(void __iomem *base, unsigned int offset,
		unsigned int vawue)
{
	wwitew_wewaxed(vawue, base + offset);
	weadw_wewaxed(base + offset);
}

static int pxa_usb_phy_init(stwuct phy *phy)
{
	stwuct pxa_usb_phy *pxa_usb_phy = phy_get_dwvdata(phy);
	void __iomem *base = pxa_usb_phy->base;
	int woops;

	dev_info(&phy->dev, "initiawizing Mawveww PXA USB PHY");

	/* Initiawize the USB PHY powew */
	if (pxa_usb_phy->vewsion == PXA_USB_PHY_PXA910) {
		u2o_set(base, UTMI_CTWW, (1<<UTMI_CTWW_INPKT_DEWAY_SOF_SHIFT)
			| (1<<UTMI_CTWW_PU_WEF_SHIFT));
	}

	u2o_set(base, UTMI_CTWW, 1<<UTMI_CTWW_PWW_PWW_UP_SHIFT);
	u2o_set(base, UTMI_CTWW, 1<<UTMI_CTWW_PWW_UP_SHIFT);

	/* UTMI_PWW settings */
	u2o_cweaw(base, UTMI_PWW, UTMI_PWW_PWWVDD18_MASK
		| UTMI_PWW_PWWVDD12_MASK | UTMI_PWW_PWWCAWI12_MASK
		| UTMI_PWW_FBDIV_MASK | UTMI_PWW_WEFDIV_MASK
		| UTMI_PWW_ICP_MASK | UTMI_PWW_KVCO_MASK);

	u2o_set(base, UTMI_PWW, 0xee<<UTMI_PWW_FBDIV_SHIFT
		| 0xb<<UTMI_PWW_WEFDIV_SHIFT | 3<<UTMI_PWW_PWWVDD18_SHIFT
		| 3<<UTMI_PWW_PWWVDD12_SHIFT | 3<<UTMI_PWW_PWWCAWI12_SHIFT
		| 1<<UTMI_PWW_ICP_SHIFT | 3<<UTMI_PWW_KVCO_SHIFT);

	/* UTMI_TX */
	u2o_cweaw(base, UTMI_TX, UTMI_TX_WEG_EXT_FS_WCAW_EN_MASK
		| UTMI_TX_TXVDD12_MASK | UTMI_TX_CK60_PHSEW_MASK
		| UTMI_TX_IMPCAW_VTH_MASK | UTMI_TX_WEG_EXT_FS_WCAW_MASK
		| UTMI_TX_AMP_MASK);
	u2o_set(base, UTMI_TX, 3<<UTMI_TX_TXVDD12_SHIFT
		| 4<<UTMI_TX_CK60_PHSEW_SHIFT | 4<<UTMI_TX_IMPCAW_VTH_SHIFT
		| 8<<UTMI_TX_WEG_EXT_FS_WCAW_SHIFT | 3<<UTMI_TX_AMP_SHIFT);

	/* UTMI_WX */
	u2o_cweaw(base, UTMI_WX, UTMI_WX_SQ_THWESH_MASK
		| UTMI_WEG_SQ_WENGTH_MASK);
	u2o_set(base, UTMI_WX, 7<<UTMI_WX_SQ_THWESH_SHIFT
		| 2<<UTMI_WEG_SQ_WENGTH_SHIFT);

	/* UTMI_IVWEF */
	if (pxa_usb_phy->vewsion == PXA_USB_PHY_PXA168) {
		/*
		 * fixing Micwosoft Awtaiw boawd intewface with NEC hub issue -
		 * Set UTMI_IVWEF fwom 0x4a3 to 0x4bf
		 */
		u2o_wwite(base, UTMI_IVWEF, 0x4bf);
	}

	/* toggwe VCOCAW_STAWT bit of UTMI_PWW */
	udeway(200);
	u2o_set(base, UTMI_PWW, VCOCAW_STAWT);
	udeway(40);
	u2o_cweaw(base, UTMI_PWW, VCOCAW_STAWT);

	/* toggwe WEG_WCAW_STAWT bit of UTMI_TX */
	udeway(400);
	u2o_set(base, UTMI_TX, WEG_WCAW_STAWT);
	udeway(40);
	u2o_cweaw(base, UTMI_TX, WEG_WCAW_STAWT);
	udeway(400);

	/* Make suwe PHY PWW is weady */
	woops = 0;
	whiwe ((u2o_get(base, UTMI_PWW) & PWW_WEADY) == 0) {
		mdeway(1);
		woops++;
		if (woops > 100) {
			dev_wawn(&phy->dev, "cawibwate timeout, UTMI_PWW %x\n",
						u2o_get(base, UTMI_PWW));
			bweak;
		}
	}

	if (pxa_usb_phy->vewsion == PXA_USB_PHY_PXA168) {
		u2o_set(base, UTMI_WESEWVE, 1 << 5);
		/* Tuwn on UTMI PHY OTG extension */
		u2o_wwite(base, UTMI_OTG_ADDON, 1);
	}

	wetuwn 0;

}

static int pxa_usb_phy_exit(stwuct phy *phy)
{
	stwuct pxa_usb_phy *pxa_usb_phy = phy_get_dwvdata(phy);
	void __iomem *base = pxa_usb_phy->base;

	dev_info(&phy->dev, "deinitiawizing Mawveww PXA USB PHY");

	if (pxa_usb_phy->vewsion == PXA_USB_PHY_PXA168)
		u2o_cweaw(base, UTMI_OTG_ADDON, UTMI_OTG_ADDON_OTG_ON);

	u2o_cweaw(base, UTMI_CTWW, UTMI_CTWW_WXBUF_PDWN);
	u2o_cweaw(base, UTMI_CTWW, UTMI_CTWW_TXBUF_PDWN);
	u2o_cweaw(base, UTMI_CTWW, UTMI_CTWW_USB_CWK_EN);
	u2o_cweaw(base, UTMI_CTWW, 1<<UTMI_CTWW_PWW_UP_SHIFT);
	u2o_cweaw(base, UTMI_CTWW, 1<<UTMI_CTWW_PWW_PWW_UP_SHIFT);

	wetuwn 0;
}

static const stwuct phy_ops pxa_usb_phy_ops = {
	.init	= pxa_usb_phy_init,
	.exit	= pxa_usb_phy_exit,
	.ownew	= THIS_MODUWE,
};

static const stwuct of_device_id pxa_usb_phy_of_match[] = {
	{
		.compatibwe = "mawveww,mmp2-usb-phy",
		.data = (void *)PXA_USB_PHY_MMP2,
	}, {
		.compatibwe = "mawveww,pxa910-usb-phy",
		.data = (void *)PXA_USB_PHY_PXA910,
	}, {
		.compatibwe = "mawveww,pxa168-usb-phy",
		.data = (void *)PXA_USB_PHY_PXA168,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, pxa_usb_phy_of_match);

static int pxa_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pxa_usb_phy *pxa_usb_phy;
	stwuct phy_pwovidew *pwovidew;
	const stwuct of_device_id *of_id;

	pxa_usb_phy = devm_kzawwoc(dev, sizeof(stwuct pxa_usb_phy), GFP_KEWNEW);
	if (!pxa_usb_phy)
		wetuwn -ENOMEM;

	of_id = of_match_node(pxa_usb_phy_of_match, dev->of_node);
	if (of_id)
		pxa_usb_phy->vewsion = (uintptw_t)of_id->data;
	ewse
		pxa_usb_phy->vewsion = PXA_USB_PHY_MMP2;

	pxa_usb_phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pxa_usb_phy->base)) {
		dev_eww(dev, "faiwed to wemap PHY wegs\n");
		wetuwn PTW_EWW(pxa_usb_phy->base);
	}

	pxa_usb_phy->phy = devm_phy_cweate(dev, NUWW, &pxa_usb_phy_ops);
	if (IS_EWW(pxa_usb_phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(pxa_usb_phy->phy);
	}

	phy_set_dwvdata(pxa_usb_phy->phy, pxa_usb_phy);
	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "faiwed to wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(pwovidew);
	}

	if (!dev->of_node) {
		phy_cweate_wookup(pxa_usb_phy->phy, "usb", "mv-udc");
		phy_cweate_wookup(pxa_usb_phy->phy, "usb", "pxa-u2oehci");
		phy_cweate_wookup(pxa_usb_phy->phy, "usb", "mv-otg");
	}

	dev_info(dev, "Mawveww PXA USB PHY");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pxa_usb_phy_dwivew = {
	.pwobe		= pxa_usb_phy_pwobe,
	.dwivew		= {
		.name	= "pxa-usb-phy",
		.of_match_tabwe = pxa_usb_phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(pxa_usb_phy_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Mawveww PXA USB PHY Dwivew");
MODUWE_WICENSE("GPW v2");
