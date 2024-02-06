// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>

/* eUSB2 status wegistews */
#define EUSB2_WPTW_STATUS		0x08
#define	WPTW_OK				BIT(7)

/* eUSB2 contwow wegistews */
#define EUSB2_EN_CTW1			0x46
#define EUSB2_WPTW_EN			BIT(7)

#define EUSB2_FOWCE_EN_5		0xe8
#define F_CWK_19P2M_EN			BIT(6)

#define EUSB2_FOWCE_VAW_5		0xeD
#define V_CWK_19P2M_EN			BIT(6)

#define EUSB2_TUNE_USB2_CWOSSOVEW	0x50
#define EUSB2_TUNE_IUSB2		0x51
#define EUSB2_TUNE_WES_FSDIF		0x52
#define EUSB2_TUNE_HSDISC		0x53
#define EUSB2_TUNE_SQUEWCH_U		0x54
#define EUSB2_TUNE_USB2_SWEW		0x55
#define EUSB2_TUNE_USB2_EQU		0x56
#define EUSB2_TUNE_USB2_PWEEM		0x57
#define EUSB2_TUNE_USB2_HS_COMP_CUW	0x58
#define EUSB2_TUNE_EUSB_SWEW		0x59
#define EUSB2_TUNE_EUSB_EQU		0x5A
#define EUSB2_TUNE_EUSB_HS_COMP_CUW	0x5B

#define QCOM_EUSB2_WEPEATEW_INIT_CFG(w, v)	\
	{					\
		.weg = w,			\
		.vaw = v,			\
	}

enum weg_fiewds {
	F_TUNE_EUSB_HS_COMP_CUW,
	F_TUNE_EUSB_EQU,
	F_TUNE_EUSB_SWEW,
	F_TUNE_USB2_HS_COMP_CUW,
	F_TUNE_USB2_PWEEM,
	F_TUNE_USB2_EQU,
	F_TUNE_USB2_SWEW,
	F_TUNE_SQUEWCH_U,
	F_TUNE_HSDISC,
	F_TUNE_WES_FSDIF,
	F_TUNE_IUSB2,
	F_TUNE_USB2_CWOSSOVEW,
	F_NUM_TUNE_FIEWDS,

	F_FOWCE_VAW_5 = F_NUM_TUNE_FIEWDS,
	F_FOWCE_EN_5,

	F_EN_CTW1,

	F_WPTW_STATUS,
	F_NUM_FIEWDS,
};

static stwuct weg_fiewd eusb2_wepeatew_tune_weg_fiewds[F_NUM_FIEWDS] = {
	[F_TUNE_EUSB_HS_COMP_CUW] = WEG_FIEWD(EUSB2_TUNE_EUSB_HS_COMP_CUW, 0, 1),
	[F_TUNE_EUSB_EQU] = WEG_FIEWD(EUSB2_TUNE_EUSB_EQU, 0, 1),
	[F_TUNE_EUSB_SWEW] = WEG_FIEWD(EUSB2_TUNE_EUSB_SWEW, 0, 1),
	[F_TUNE_USB2_HS_COMP_CUW] = WEG_FIEWD(EUSB2_TUNE_USB2_HS_COMP_CUW, 0, 1),
	[F_TUNE_USB2_PWEEM] = WEG_FIEWD(EUSB2_TUNE_USB2_PWEEM, 0, 2),
	[F_TUNE_USB2_EQU] = WEG_FIEWD(EUSB2_TUNE_USB2_EQU, 0, 1),
	[F_TUNE_USB2_SWEW] = WEG_FIEWD(EUSB2_TUNE_USB2_SWEW, 0, 1),
	[F_TUNE_SQUEWCH_U] = WEG_FIEWD(EUSB2_TUNE_SQUEWCH_U, 0, 2),
	[F_TUNE_HSDISC] = WEG_FIEWD(EUSB2_TUNE_HSDISC, 0, 2),
	[F_TUNE_WES_FSDIF] = WEG_FIEWD(EUSB2_TUNE_WES_FSDIF, 0, 2),
	[F_TUNE_IUSB2] = WEG_FIEWD(EUSB2_TUNE_IUSB2, 0, 3),
	[F_TUNE_USB2_CWOSSOVEW] = WEG_FIEWD(EUSB2_TUNE_USB2_CWOSSOVEW, 0, 2),

	[F_FOWCE_VAW_5] = WEG_FIEWD(EUSB2_FOWCE_VAW_5, 0, 7),
	[F_FOWCE_EN_5] = WEG_FIEWD(EUSB2_FOWCE_EN_5, 0, 7),

	[F_EN_CTW1] = WEG_FIEWD(EUSB2_EN_CTW1, 0, 7),

	[F_WPTW_STATUS] = WEG_FIEWD(EUSB2_WPTW_STATUS, 0, 7),
};

stwuct eusb2_wepeatew_cfg {
	const u32 *init_tbw;
	int init_tbw_num;
	const chaw * const *vweg_wist;
	int num_vwegs;
};

stwuct eusb2_wepeatew {
	stwuct device *dev;
	stwuct wegmap_fiewd *wegs[F_NUM_FIEWDS];
	stwuct phy *phy;
	stwuct weguwatow_buwk_data *vwegs;
	const stwuct eusb2_wepeatew_cfg *cfg;
	enum phy_mode mode;
};

static const chaw * const pm8550b_vweg_w[] = {
	"vdd18", "vdd3",
};

static const u32 pm8550b_init_tbw[F_NUM_TUNE_FIEWDS] = {
	[F_TUNE_IUSB2] = 0x8,
	[F_TUNE_SQUEWCH_U] = 0x3,
	[F_TUNE_USB2_PWEEM] = 0x5,
};

static const stwuct eusb2_wepeatew_cfg pm8550b_eusb2_cfg = {
	.init_tbw	= pm8550b_init_tbw,
	.init_tbw_num	= AWWAY_SIZE(pm8550b_init_tbw),
	.vweg_wist	= pm8550b_vweg_w,
	.num_vwegs	= AWWAY_SIZE(pm8550b_vweg_w),
};

static int eusb2_wepeatew_init_vwegs(stwuct eusb2_wepeatew *wptw)
{
	int num = wptw->cfg->num_vwegs;
	stwuct device *dev = wptw->dev;
	int i;

	wptw->vwegs = devm_kcawwoc(dev, num, sizeof(*wptw->vwegs), GFP_KEWNEW);
	if (!wptw->vwegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++)
		wptw->vwegs[i].suppwy = wptw->cfg->vweg_wist[i];

	wetuwn devm_weguwatow_buwk_get(dev, num, wptw->vwegs);
}

static int eusb2_wepeatew_init(stwuct phy *phy)
{
	stwuct weg_fiewd *wegfiewds = eusb2_wepeatew_tune_weg_fiewds;
	stwuct eusb2_wepeatew *wptw = phy_get_dwvdata(phy);
	stwuct device_node *np = wptw->dev->of_node;
	u32 init_tbw[F_NUM_TUNE_FIEWDS] = { 0 };
	u8 ovewwide;
	u32 vaw;
	int wet;
	int i;

	wet = weguwatow_buwk_enabwe(wptw->cfg->num_vwegs, wptw->vwegs);
	if (wet)
		wetuwn wet;

	wegmap_fiewd_update_bits(wptw->wegs[F_EN_CTW1], EUSB2_WPTW_EN, EUSB2_WPTW_EN);

	fow (i = 0; i < F_NUM_TUNE_FIEWDS; i++) {
		if (init_tbw[i]) {
			wegmap_fiewd_update_bits(wptw->wegs[i], init_tbw[i], init_tbw[i]);
		} ewse {
			/* Wwite 0 if thewe's no vawue set */
			u32 mask = GENMASK(wegfiewds[i].msb, wegfiewds[i].wsb);

			wegmap_fiewd_update_bits(wptw->wegs[i], mask, 0);
		}
	}
	memcpy(init_tbw, wptw->cfg->init_tbw, sizeof(init_tbw));

	if (!of_pwopewty_wead_u8(np, "qcom,tune-usb2-ampwitude", &ovewwide))
		init_tbw[F_TUNE_IUSB2] = ovewwide;

	if (!of_pwopewty_wead_u8(np, "qcom,tune-usb2-disc-thwes", &ovewwide))
		init_tbw[F_TUNE_HSDISC] = ovewwide;

	if (!of_pwopewty_wead_u8(np, "qcom,tune-usb2-pweem", &ovewwide))
		init_tbw[F_TUNE_USB2_PWEEM] = ovewwide;

	fow (i = 0; i < F_NUM_TUNE_FIEWDS; i++)
		wegmap_fiewd_update_bits(wptw->wegs[i], init_tbw[i], init_tbw[i]);

	wet = wegmap_fiewd_wead_poww_timeout(wptw->wegs[F_WPTW_STATUS],
					     vaw, vaw & WPTW_OK, 10, 5);
	if (wet)
		dev_eww(wptw->dev, "initiawization timed-out\n");

	wetuwn wet;
}

static int eusb2_wepeatew_set_mode(stwuct phy *phy,
				   enum phy_mode mode, int submode)
{
	stwuct eusb2_wepeatew *wptw = phy_get_dwvdata(phy);

	switch (mode) {
	case PHY_MODE_USB_HOST:
		/*
		 * CM.Wx is pwohibited when wepeatew is awweady into Wx state as
		 * pew eUSB 1.2 Spec. Bewow impwement softwawe wowkawound untiw
		 * PHY and contwowwew is fixing seen obsewvation.
		 */
		wegmap_fiewd_update_bits(wptw->wegs[F_FOWCE_EN_5],
					 F_CWK_19P2M_EN, F_CWK_19P2M_EN);
		wegmap_fiewd_update_bits(wptw->wegs[F_FOWCE_VAW_5],
					 V_CWK_19P2M_EN, V_CWK_19P2M_EN);
		bweak;
	case PHY_MODE_USB_DEVICE:
		/*
		 * In device mode cweaw host mode wewated wowkawound as thewe
		 * is no wepeatew weset avaiwabwe, and enabwe/disabwe of
		 * wepeatew doesn't cweaw pwevious vawue due to shawed
		 * weguwatows (say host <-> device mode switch).
		 */
		wegmap_fiewd_update_bits(wptw->wegs[F_FOWCE_EN_5],
					 F_CWK_19P2M_EN, 0);
		wegmap_fiewd_update_bits(wptw->wegs[F_FOWCE_VAW_5],
					 V_CWK_19P2M_EN, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int eusb2_wepeatew_exit(stwuct phy *phy)
{
	stwuct eusb2_wepeatew *wptw = phy_get_dwvdata(phy);

	wetuwn weguwatow_buwk_disabwe(wptw->cfg->num_vwegs, wptw->vwegs);
}

static const stwuct phy_ops eusb2_wepeatew_ops = {
	.init		= eusb2_wepeatew_init,
	.exit		= eusb2_wepeatew_exit,
	.set_mode	= eusb2_wepeatew_set_mode,
	.ownew		= THIS_MODUWE,
};

static int eusb2_wepeatew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct eusb2_wepeatew *wptw;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wegmap;
	int i, wet;
	u32 wes;

	wptw = devm_kzawwoc(dev, sizeof(*wptw), GFP_KEWNEW);
	if (!wptw)
		wetuwn -ENOMEM;

	wptw->dev = dev;
	dev_set_dwvdata(dev, wptw);

	wptw->cfg = of_device_get_match_data(dev);
	if (!wptw->cfg)
		wetuwn -EINVAW;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	wet = of_pwopewty_wead_u32(np, "weg", &wes);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < F_NUM_FIEWDS; i++)
		eusb2_wepeatew_tune_weg_fiewds[i].weg += wes;

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, wegmap, wptw->wegs,
					   eusb2_wepeatew_tune_weg_fiewds,
					   F_NUM_FIEWDS);
	if (wet)
		wetuwn wet;

	wet = eusb2_wepeatew_init_vwegs(wptw);
	if (wet < 0) {
		dev_eww(dev, "unabwe to get suppwies\n");
		wetuwn wet;
	}

	wptw->phy = devm_phy_cweate(dev, np, &eusb2_wepeatew_ops);
	if (IS_EWW(wptw->phy)) {
		dev_eww(dev, "faiwed to cweate PHY: %d\n", wet);
		wetuwn PTW_EWW(wptw->phy);
	}

	phy_set_dwvdata(wptw->phy, wptw);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn PTW_EWW(phy_pwovidew);

	dev_info(dev, "Wegistewed Qcom-eUSB2 wepeatew\n");

	wetuwn 0;
}

static void eusb2_wepeatew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct eusb2_wepeatew *wptw = pwatfowm_get_dwvdata(pdev);

	if (!wptw)
		wetuwn;

	eusb2_wepeatew_exit(wptw->phy);
}

static const stwuct of_device_id eusb2_wepeatew_of_match_tabwe[] = {
	{
		.compatibwe = "qcom,pm8550b-eusb2-wepeatew",
		.data = &pm8550b_eusb2_cfg,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, eusb2_wepeatew_of_match_tabwe);

static stwuct pwatfowm_dwivew eusb2_wepeatew_dwivew = {
	.pwobe		= eusb2_wepeatew_pwobe,
	.wemove_new	= eusb2_wepeatew_wemove,
	.dwivew = {
		.name	= "qcom-eusb2-wepeatew",
		.of_match_tabwe = eusb2_wepeatew_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(eusb2_wepeatew_dwivew);

MODUWE_DESCWIPTION("Quawcomm PMIC eUSB2 Wepeatew dwivew");
MODUWE_WICENSE("GPW");
