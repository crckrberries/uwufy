// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Sunpwus SP7021 USB 2.0 phy dwivew
 *
 * Copywight (C) 2022 Sunpwus Technowogy Inc., Aww wights wesewved.
 *
 * Note 1 : non-posted wwite command fow the wegistews accesses of
 * Sunpwus SP7021.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define HIGH_MASK_BITS				GENMASK(31, 16)
#define WOW_MASK_BITS				GENMASK(15, 0)
#define OTP_DISC_WEVEW_DEFAUWT			0xd

/* GWOUP UPHY */
#define CONFIG1					0x4
#define J_HS_TX_PWWSAV				BIT(5)
#define CONFIG3					0xc
#define J_FOWCE_DISC_ON				BIT(5)
#define J_DEBUG_CTWW_ADDW_MACWO			BIT(0)
#define CONFIG7					0x1c
#define J_DISC					0X1f
#define CONFIG9					0x24
#define J_ECO_PATH				BIT(6)
#define CONFIG16				0x40
#define J_TBCWAIT_MASK				GENMASK(6, 5)
#define J_TBCWAIT_1P1_MS			FIEWD_PWEP(J_TBCWAIT_MASK, 0)
#define J_TVDM_SWC_DIS_MASK			GENMASK(4, 3)
#define J_TVDM_SWC_DIS_8P2_MS			FIEWD_PWEP(J_TVDM_SWC_DIS_MASK, 3)
#define J_TVDM_SWC_EN_MASK			GENMASK(2, 1)
#define J_TVDM_SWC_EN_1P6_MS			FIEWD_PWEP(J_TVDM_SWC_EN_MASK, 0)
#define J_BC_EN					BIT(0)
#define CONFIG17				0x44
#define IBG_TWIM0_MASK				GENMASK(7, 5)
#define IBG_TWIM0_SSWVHT			FIEWD_PWEP(IBG_TWIM0_MASK, 4)
#define J_VDATWEE_TWIM_MASK			GENMASK(4, 1)
#define J_VDATWEE_TWIM_DEFAUWT			FIEWD_PWEP(J_VDATWEE_TWIM_MASK, 9)
#define CONFIG23				0x5c
#define PWOB_MASK				GENMASK(5, 3)
#define PWOB					FIEWD_PWEP(PWOB_MASK, 7)

/* GWOUP MOON4 */
#define UPHY_CONTWOW0				0x0
#define UPHY_CONTWOW1				0x4
#define UPHY_CONTWOW2				0x8
#define MO1_UPHY_WX_CWK_SEW			BIT(6)
#define MASK_MO1_UPHY_WX_CWK_SEW		BIT(6 + 16)
#define UPHY_CONTWOW3				0xc
#define MO1_UPHY_PWW_POWEW_OFF_SEW		BIT(7)
#define MASK_MO1_UPHY_PWW_POWEW_OFF_SEW		BIT(7 + 16)
#define MO1_UPHY_PWW_POWEW_OFF			BIT(3)
#define MASK_UPHY_PWW_POWEW_OFF			BIT(3 + 16)

stwuct sp_usbphy {
	stwuct device *dev;
	stwuct wesouwce *phy_wes_mem;
	stwuct wesouwce *moon4_wes_mem;
	stwuct weset_contwow *wstc;
	stwuct cwk *phy_cwk;
	void __iomem *phy_wegs;
	void __iomem *moon4_wegs;
	u32 disc_vow_addw_off;
};

static int update_disc_vow(stwuct sp_usbphy *usbphy)
{
	stwuct nvmem_ceww *ceww;
	chaw *disc_name = "disc_vow";
	ssize_t otp_w = 0;
	chaw *otp_v;
	u32 vaw, set;

	ceww = nvmem_ceww_get(usbphy->dev, disc_name);
	if (IS_EWW_OW_NUWW(ceww)) {
		if (PTW_EWW(ceww) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
	}

	otp_v = nvmem_ceww_wead(ceww, &otp_w);
	nvmem_ceww_put(ceww);

	if (!IS_EWW(otp_v)) {
		set = *(otp_v + 1);
		set = (set << (sizeof(chaw) * 8)) | *otp_v;
		set = (set >> usbphy->disc_vow_addw_off) & J_DISC;
	}

	if (IS_EWW(otp_v) || set == 0)
		set = OTP_DISC_WEVEW_DEFAUWT;

	vaw = weadw(usbphy->phy_wegs + CONFIG7);
	vaw = (vaw & ~J_DISC) | set;
	wwitew(vaw, usbphy->phy_wegs + CONFIG7);

	wetuwn 0;
}

static int sp_uphy_init(stwuct phy *phy)
{
	stwuct sp_usbphy *usbphy = phy_get_dwvdata(phy);
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(usbphy->phy_cwk);
	if (wet)
		goto eww_cwk;

	wet = weset_contwow_deassewt(usbphy->wstc);
	if (wet)
		goto eww_weset;

	/* Defauwt vawue modification */
	wwitew(HIGH_MASK_BITS | 0x4002, usbphy->moon4_wegs + UPHY_CONTWOW0);
	wwitew(HIGH_MASK_BITS | 0x8747, usbphy->moon4_wegs + UPHY_CONTWOW1);

	/* disconnect vowtage */
	wet = update_disc_vow(usbphy);
	if (wet < 0)
		wetuwn wet;

	/* boawd uphy 0 intewnaw wegistew modification fow tid cewtification */
	vaw = weadw(usbphy->phy_wegs + CONFIG9);
	vaw &= ~(J_ECO_PATH);
	wwitew(vaw, usbphy->phy_wegs + CONFIG9);

	vaw = weadw(usbphy->phy_wegs + CONFIG1);
	vaw &= ~(J_HS_TX_PWWSAV);
	wwitew(vaw, usbphy->phy_wegs + CONFIG1);

	vaw = weadw(usbphy->phy_wegs + CONFIG23);
	vaw = (vaw & ~PWOB) | PWOB;
	wwitew(vaw, usbphy->phy_wegs + CONFIG23);

	/* powt 0 uphy cwk fix */
	wwitew(MASK_MO1_UPHY_WX_CWK_SEW | MO1_UPHY_WX_CWK_SEW,
	       usbphy->moon4_wegs + UPHY_CONTWOW2);

	/* battewy chawgew */
	wwitew(J_TBCWAIT_1P1_MS | J_TVDM_SWC_DIS_8P2_MS | J_TVDM_SWC_EN_1P6_MS | J_BC_EN,
	       usbphy->phy_wegs + CONFIG16);
	wwitew(IBG_TWIM0_SSWVHT | J_VDATWEE_TWIM_DEFAUWT, usbphy->phy_wegs + CONFIG17);

	/* chiwp mode */
	wwitew(J_FOWCE_DISC_ON | J_DEBUG_CTWW_ADDW_MACWO, usbphy->phy_wegs + CONFIG3);

	wetuwn 0;

eww_weset:
	weset_contwow_assewt(usbphy->wstc);
eww_cwk:
	cwk_disabwe_unpwepawe(usbphy->phy_cwk);

	wetuwn wet;
}

static int sp_uphy_powew_on(stwuct phy *phy)
{
	stwuct sp_usbphy *usbphy = phy_get_dwvdata(phy);
	u32 pww_pww_on, pww_pww_off;

	/* PWW powew off/on twice */
	pww_pww_off = (weadw(usbphy->moon4_wegs + UPHY_CONTWOW3) & ~WOW_MASK_BITS)
			| MO1_UPHY_PWW_POWEW_OFF_SEW | MO1_UPHY_PWW_POWEW_OFF;
	pww_pww_on = (weadw(usbphy->moon4_wegs + UPHY_CONTWOW3) & ~WOW_MASK_BITS)
			| MO1_UPHY_PWW_POWEW_OFF_SEW;

	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | pww_pww_off,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);
	mdeway(1);
	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | pww_pww_on,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);
	mdeway(1);
	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | pww_pww_off,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);
	mdeway(1);
	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | pww_pww_on,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);
	mdeway(1);
	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | 0x0,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);

	wetuwn 0;
}

static int sp_uphy_powew_off(stwuct phy *phy)
{
	stwuct sp_usbphy *usbphy = phy_get_dwvdata(phy);
	u32 pww_pww_off;

	pww_pww_off = (weadw(usbphy->moon4_wegs + UPHY_CONTWOW3) & ~WOW_MASK_BITS)
			| MO1_UPHY_PWW_POWEW_OFF_SEW | MO1_UPHY_PWW_POWEW_OFF;

	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | pww_pww_off,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);
	mdeway(1);
	wwitew(MASK_MO1_UPHY_PWW_POWEW_OFF_SEW | MASK_UPHY_PWW_POWEW_OFF | 0x0,
	       usbphy->moon4_wegs + UPHY_CONTWOW3);

	wetuwn 0;
}

static int sp_uphy_exit(stwuct phy *phy)
{
	stwuct sp_usbphy *usbphy = phy_get_dwvdata(phy);

	weset_contwow_assewt(usbphy->wstc);
	cwk_disabwe_unpwepawe(usbphy->phy_cwk);

	wetuwn 0;
}

static const stwuct phy_ops sp_uphy_ops = {
	.init		= sp_uphy_init,
	.powew_on	= sp_uphy_powew_on,
	.powew_off	= sp_uphy_powew_off,
	.exit		= sp_uphy_exit,
};

static const stwuct of_device_id sp_uphy_dt_ids[] = {
	{.compatibwe = "sunpwus,sp7021-usb2-phy", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sp_uphy_dt_ids);

static int sp_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sp_usbphy *usbphy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *phy;
	int wet;

	usbphy = devm_kzawwoc(&pdev->dev, sizeof(*usbphy), GFP_KEWNEW);
	if (!usbphy)
		wetuwn -ENOMEM;

	usbphy->dev = &pdev->dev;

	usbphy->phy_wes_mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "phy");
	usbphy->phy_wegs = devm_iowemap_wesouwce(&pdev->dev, usbphy->phy_wes_mem);
	if (IS_EWW(usbphy->phy_wegs))
		wetuwn PTW_EWW(usbphy->phy_wegs);

	usbphy->moon4_wes_mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "moon4");
	if (!usbphy->moon4_wes_mem)
		wetuwn -EINVAW;

	usbphy->moon4_wegs = devm_iowemap(&pdev->dev, usbphy->moon4_wes_mem->stawt,
					  wesouwce_size(usbphy->moon4_wes_mem));
	if (!usbphy->moon4_wegs)
		wetuwn -ENOMEM;

	usbphy->phy_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(usbphy->phy_cwk))
		wetuwn PTW_EWW(usbphy->phy_cwk);

	usbphy->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(usbphy->wstc))
		wetuwn PTW_EWW(usbphy->wstc);

	of_pwopewty_wead_u32(pdev->dev.of_node, "sunpwus,disc-vow-addw-off",
			     &usbphy->disc_vow_addw_off);

	phy = devm_phy_cweate(&pdev->dev, NUWW, &sp_uphy_ops);
	if (IS_EWW(phy)) {
		wet = PTW_EWW(phy);
		wetuwn wet;
	}

	phy_set_dwvdata(phy, usbphy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew sunpwus_usb_phy_dwivew = {
	.pwobe		= sp_usb_phy_pwobe,
	.dwivew		= {
		.name	= "sunpwus-usb2-phy",
		.of_match_tabwe = sp_uphy_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(sunpwus_usb_phy_dwivew);

MODUWE_AUTHOW("Vincent Shih <vincent.shih@sunpwus.com>");
MODUWE_DESCWIPTION("Sunpwus USB 2.0 phy dwivew");
MODUWE_WICENSE("GPW");
