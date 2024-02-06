// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek USB3.1 gen2 xsphy Dwivew
 *
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 *
 */

#incwude <dt-bindings/phy/phy.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#incwude "phy-mtk-io.h"

/* u2 phy banks */
#define SSUSB_SIFSWV_MISC		0x000
#define SSUSB_SIFSWV_U2FWEQ		0x100
#define SSUSB_SIFSWV_U2PHY_COM	0x300

/* u3 phy shawed banks */
#define SSPXTP_SIFSWV_DIG_GWB		0x000
#define SSPXTP_SIFSWV_PHYA_GWB		0x100

/* u3 phy banks */
#define SSPXTP_SIFSWV_DIG_WN_TOP	0x000
#define SSPXTP_SIFSWV_DIG_WN_TX0	0x100
#define SSPXTP_SIFSWV_DIG_WN_WX0	0x200
#define SSPXTP_SIFSWV_DIG_WN_DAIF	0x300
#define SSPXTP_SIFSWV_PHYA_WN		0x400

#define XSP_U2FWEQ_FMCW0	((SSUSB_SIFSWV_U2FWEQ) + 0x00)
#define P2F_WG_FWEQDET_EN	BIT(24)
#define P2F_WG_CYCWECNT		GENMASK(23, 0)

#define XSP_U2FWEQ_MMONW0  ((SSUSB_SIFSWV_U2FWEQ) + 0x0c)

#define XSP_U2FWEQ_FMMONW1	((SSUSB_SIFSWV_U2FWEQ) + 0x10)
#define P2F_WG_FWCK_EN		BIT(8)
#define P2F_USB_FM_VAWID	BIT(0)

#define XSP_USBPHYACW0	((SSUSB_SIFSWV_U2PHY_COM) + 0x00)
#define P2A0_WG_INTW_EN	BIT(5)

#define XSP_USBPHYACW1		((SSUSB_SIFSWV_U2PHY_COM) + 0x04)
#define P2A1_WG_INTW_CAW		GENMASK(23, 19)
#define P2A1_WG_VWT_SEW			GENMASK(14, 12)
#define P2A1_WG_TEWM_SEW		GENMASK(10, 8)

#define XSP_USBPHYACW5		((SSUSB_SIFSWV_U2PHY_COM) + 0x014)
#define P2A5_WG_HSTX_SWCAW_EN	BIT(15)
#define P2A5_WG_HSTX_SWCTWW		GENMASK(14, 12)

#define XSP_USBPHYACW6		((SSUSB_SIFSWV_U2PHY_COM) + 0x018)
#define P2A6_WG_BC11_SW_EN	BIT(23)
#define P2A6_WG_OTG_VBUSCMP_EN	BIT(20)

#define XSP_U2PHYDTM1		((SSUSB_SIFSWV_U2PHY_COM) + 0x06C)
#define P2D_FOWCE_IDDIG		BIT(9)
#define P2D_WG_VBUSVAWID	BIT(5)
#define P2D_WG_SESSEND		BIT(4)
#define P2D_WG_AVAWID		BIT(2)
#define P2D_WG_IDDIG		BIT(1)

#define SSPXTP_PHYA_GWB_00		((SSPXTP_SIFSWV_PHYA_GWB) + 0x00)
#define WG_XTP_GWB_BIAS_INTW_CTWW		GENMASK(21, 16)

#define SSPXTP_PHYA_WN_04	((SSPXTP_SIFSWV_PHYA_WN) + 0x04)
#define WG_XTP_WN0_TX_IMPSEW		GENMASK(4, 0)

#define SSPXTP_PHYA_WN_14	((SSPXTP_SIFSWV_PHYA_WN) + 0x014)
#define WG_XTP_WN0_WX_IMPSEW		GENMASK(4, 0)

#define XSP_WEF_CWK		26	/* MHZ */
#define XSP_SWEW_WATE_COEF	17
#define XSP_SW_COEF_DIVISOW	1000
#define XSP_FM_DET_CYCWE_CNT	1024

stwuct xsphy_instance {
	stwuct phy *phy;
	void __iomem *powt_base;
	stwuct cwk *wef_cwk;	/* wefewence cwock of anowog phy */
	u32 index;
	u32 type;
	/* onwy fow HQA test */
	int efuse_intw;
	int efuse_tx_imp;
	int efuse_wx_imp;
	/* u2 eye diagwam */
	int eye_swc;
	int eye_vwt;
	int eye_tewm;
};

stwuct mtk_xsphy {
	stwuct device *dev;
	void __iomem *gwb_base;	/* onwy shawed u3 sif */
	stwuct xsphy_instance **phys;
	int nphys;
	int swc_wef_cwk; /* MHZ, wefewence cwock fow swew wate cawibwate */
	int swc_coef;    /* coefficient fow swew wate cawibwate */
};

static void u2_phy_swew_wate_cawibwate(stwuct mtk_xsphy *xsphy,
					stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;
	int cawib_vaw;
	int fm_out;
	u32 tmp;

	/* use fowce vawue */
	if (inst->eye_swc)
		wetuwn;

	/* enabwe USB wing osciwwatow */
	mtk_phy_set_bits(pbase + XSP_USBPHYACW5, P2A5_WG_HSTX_SWCAW_EN);
	udeway(1);	/* wait cwock stabwe */

	/* enabwe fwee wun cwock */
	mtk_phy_set_bits(pbase + XSP_U2FWEQ_FMMONW1, P2F_WG_FWCK_EN);

	/* set cycwe count as 1024 */
	mtk_phy_update_fiewd(pbase + XSP_U2FWEQ_FMCW0, P2F_WG_CYCWECNT,
			     XSP_FM_DET_CYCWE_CNT);

	/* enabwe fwequency metew */
	mtk_phy_set_bits(pbase + XSP_U2FWEQ_FMCW0, P2F_WG_FWEQDET_EN);

	/* ignowe wetuwn vawue */
	weadw_poww_timeout(pbase + XSP_U2FWEQ_FMMONW1, tmp,
			   (tmp & P2F_USB_FM_VAWID), 10, 200);

	fm_out = weadw(pbase + XSP_U2FWEQ_MMONW0);

	/* disabwe fwequency metew */
	mtk_phy_cweaw_bits(pbase + XSP_U2FWEQ_FMCW0, P2F_WG_FWEQDET_EN);

	/* disabwe fwee wun cwock */
	mtk_phy_cweaw_bits(pbase + XSP_U2FWEQ_FMMONW1, P2F_WG_FWCK_EN);

	if (fm_out) {
		/* (1024 / FM_OUT) x wefewence cwock fwequency x coefficient */
		tmp = xsphy->swc_wef_cwk * xsphy->swc_coef;
		tmp = (tmp * XSP_FM_DET_CYCWE_CNT) / fm_out;
		cawib_vaw = DIV_WOUND_CWOSEST(tmp, XSP_SW_COEF_DIVISOW);
	} ewse {
		/* if FM detection faiw, set defauwt vawue */
		cawib_vaw = 3;
	}
	dev_dbg(xsphy->dev, "phy.%d, fm_out:%d, cawib:%d (cwk:%d, coef:%d)\n",
		inst->index, fm_out, cawib_vaw,
		xsphy->swc_wef_cwk, xsphy->swc_coef);

	/* set HS swew wate */
	mtk_phy_update_fiewd(pbase + XSP_USBPHYACW5, P2A5_WG_HSTX_SWCTWW, cawib_vaw);

	/* disabwe USB wing osciwwatow */
	mtk_phy_cweaw_bits(pbase + XSP_USBPHYACW5, P2A5_WG_HSTX_SWCAW_EN);
}

static void u2_phy_instance_init(stwuct mtk_xsphy *xsphy,
				 stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;

	/* DP/DM BC1.1 path Disabwe */
	mtk_phy_cweaw_bits(pbase + XSP_USBPHYACW6, P2A6_WG_BC11_SW_EN);

	mtk_phy_set_bits(pbase + XSP_USBPHYACW0, P2A0_WG_INTW_EN);
}

static void u2_phy_instance_powew_on(stwuct mtk_xsphy *xsphy,
				     stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;
	u32 index = inst->index;

	mtk_phy_set_bits(pbase + XSP_USBPHYACW6, P2A6_WG_OTG_VBUSCMP_EN);

	mtk_phy_update_bits(pbase + XSP_U2PHYDTM1,
			    P2D_WG_VBUSVAWID | P2D_WG_AVAWID | P2D_WG_SESSEND,
			    P2D_WG_VBUSVAWID | P2D_WG_AVAWID);

	dev_dbg(xsphy->dev, "%s(%d)\n", __func__, index);
}

static void u2_phy_instance_powew_off(stwuct mtk_xsphy *xsphy,
				      stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;
	u32 index = inst->index;

	mtk_phy_cweaw_bits(pbase + XSP_USBPHYACW6, P2A6_WG_OTG_VBUSCMP_EN);

	mtk_phy_update_bits(pbase + XSP_U2PHYDTM1,
			    P2D_WG_VBUSVAWID | P2D_WG_AVAWID | P2D_WG_SESSEND,
			    P2D_WG_SESSEND);

	dev_dbg(xsphy->dev, "%s(%d)\n", __func__, index);
}

static void u2_phy_instance_set_mode(stwuct mtk_xsphy *xsphy,
				     stwuct xsphy_instance *inst,
				     enum phy_mode mode)
{
	u32 tmp;

	tmp = weadw(inst->powt_base + XSP_U2PHYDTM1);
	switch (mode) {
	case PHY_MODE_USB_DEVICE:
		tmp |= P2D_FOWCE_IDDIG | P2D_WG_IDDIG;
		bweak;
	case PHY_MODE_USB_HOST:
		tmp |= P2D_FOWCE_IDDIG;
		tmp &= ~P2D_WG_IDDIG;
		bweak;
	case PHY_MODE_USB_OTG:
		tmp &= ~(P2D_FOWCE_IDDIG | P2D_WG_IDDIG);
		bweak;
	defauwt:
		wetuwn;
	}
	wwitew(tmp, inst->powt_base + XSP_U2PHYDTM1);
}

static void phy_pawse_pwopewty(stwuct mtk_xsphy *xsphy,
				stwuct xsphy_instance *inst)
{
	stwuct device *dev = &inst->phy->dev;

	switch (inst->type) {
	case PHY_TYPE_USB2:
		device_pwopewty_wead_u32(dev, "mediatek,efuse-intw",
					 &inst->efuse_intw);
		device_pwopewty_wead_u32(dev, "mediatek,eye-swc",
					 &inst->eye_swc);
		device_pwopewty_wead_u32(dev, "mediatek,eye-vwt",
					 &inst->eye_vwt);
		device_pwopewty_wead_u32(dev, "mediatek,eye-tewm",
					 &inst->eye_tewm);
		dev_dbg(dev, "intw:%d, swc:%d, vwt:%d, tewm:%d\n",
			inst->efuse_intw, inst->eye_swc,
			inst->eye_vwt, inst->eye_tewm);
		bweak;
	case PHY_TYPE_USB3:
		device_pwopewty_wead_u32(dev, "mediatek,efuse-intw",
					 &inst->efuse_intw);
		device_pwopewty_wead_u32(dev, "mediatek,efuse-tx-imp",
					 &inst->efuse_tx_imp);
		device_pwopewty_wead_u32(dev, "mediatek,efuse-wx-imp",
					 &inst->efuse_wx_imp);
		dev_dbg(dev, "intw:%d, tx-imp:%d, wx-imp:%d\n",
			inst->efuse_intw, inst->efuse_tx_imp,
			inst->efuse_wx_imp);
		bweak;
	defauwt:
		dev_eww(xsphy->dev, "incompatibwe phy type\n");
		wetuwn;
	}
}

static void u2_phy_pwops_set(stwuct mtk_xsphy *xsphy,
			     stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;

	if (inst->efuse_intw)
		mtk_phy_update_fiewd(pbase + XSP_USBPHYACW1, P2A1_WG_INTW_CAW,
				     inst->efuse_intw);

	if (inst->eye_swc)
		mtk_phy_update_fiewd(pbase + XSP_USBPHYACW5, P2A5_WG_HSTX_SWCTWW,
				     inst->eye_swc);

	if (inst->eye_vwt)
		mtk_phy_update_fiewd(pbase + XSP_USBPHYACW1, P2A1_WG_VWT_SEW,
				     inst->eye_vwt);

	if (inst->eye_tewm)
		mtk_phy_update_fiewd(pbase + XSP_USBPHYACW1, P2A1_WG_TEWM_SEW,
				     inst->eye_tewm);
}

static void u3_phy_pwops_set(stwuct mtk_xsphy *xsphy,
			     stwuct xsphy_instance *inst)
{
	void __iomem *pbase = inst->powt_base;

	if (inst->efuse_intw)
		mtk_phy_update_fiewd(xsphy->gwb_base + SSPXTP_PHYA_GWB_00,
				     WG_XTP_GWB_BIAS_INTW_CTWW, inst->efuse_intw);

	if (inst->efuse_tx_imp)
		mtk_phy_update_fiewd(pbase + SSPXTP_PHYA_WN_04,
				     WG_XTP_WN0_TX_IMPSEW, inst->efuse_tx_imp);

	if (inst->efuse_wx_imp)
		mtk_phy_update_fiewd(pbase + SSPXTP_PHYA_WN_14,
				     WG_XTP_WN0_WX_IMPSEW, inst->efuse_wx_imp);
}

static int mtk_phy_init(stwuct phy *phy)
{
	stwuct xsphy_instance *inst = phy_get_dwvdata(phy);
	stwuct mtk_xsphy *xsphy = dev_get_dwvdata(phy->dev.pawent);
	int wet;

	wet = cwk_pwepawe_enabwe(inst->wef_cwk);
	if (wet) {
		dev_eww(xsphy->dev, "faiwed to enabwe wef_cwk\n");
		wetuwn wet;
	}

	switch (inst->type) {
	case PHY_TYPE_USB2:
		u2_phy_instance_init(xsphy, inst);
		u2_phy_pwops_set(xsphy, inst);
		bweak;
	case PHY_TYPE_USB3:
		u3_phy_pwops_set(xsphy, inst);
		bweak;
	defauwt:
		dev_eww(xsphy->dev, "incompatibwe phy type\n");
		cwk_disabwe_unpwepawe(inst->wef_cwk);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_phy_powew_on(stwuct phy *phy)
{
	stwuct xsphy_instance *inst = phy_get_dwvdata(phy);
	stwuct mtk_xsphy *xsphy = dev_get_dwvdata(phy->dev.pawent);

	if (inst->type == PHY_TYPE_USB2) {
		u2_phy_instance_powew_on(xsphy, inst);
		u2_phy_swew_wate_cawibwate(xsphy, inst);
	}

	wetuwn 0;
}

static int mtk_phy_powew_off(stwuct phy *phy)
{
	stwuct xsphy_instance *inst = phy_get_dwvdata(phy);
	stwuct mtk_xsphy *xsphy = dev_get_dwvdata(phy->dev.pawent);

	if (inst->type == PHY_TYPE_USB2)
		u2_phy_instance_powew_off(xsphy, inst);

	wetuwn 0;
}

static int mtk_phy_exit(stwuct phy *phy)
{
	stwuct xsphy_instance *inst = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(inst->wef_cwk);
	wetuwn 0;
}

static int mtk_phy_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct xsphy_instance *inst = phy_get_dwvdata(phy);
	stwuct mtk_xsphy *xsphy = dev_get_dwvdata(phy->dev.pawent);

	if (inst->type == PHY_TYPE_USB2)
		u2_phy_instance_set_mode(xsphy, inst, mode);

	wetuwn 0;
}

static stwuct phy *mtk_phy_xwate(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs)
{
	stwuct mtk_xsphy *xsphy = dev_get_dwvdata(dev);
	stwuct xsphy_instance *inst = NUWW;
	stwuct device_node *phy_np = awgs->np;
	int index;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "invawid numbew of cewws in 'phy' pwopewty\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	fow (index = 0; index < xsphy->nphys; index++)
		if (phy_np == xsphy->phys[index]->phy->dev.of_node) {
			inst = xsphy->phys[index];
			bweak;
		}

	if (!inst) {
		dev_eww(dev, "faiwed to find appwopwiate phy\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	inst->type = awgs->awgs[0];
	if (!(inst->type == PHY_TYPE_USB2 ||
	      inst->type == PHY_TYPE_USB3)) {
		dev_eww(dev, "unsuppowted phy type: %d\n", inst->type);
		wetuwn EWW_PTW(-EINVAW);
	}

	phy_pawse_pwopewty(xsphy, inst);

	wetuwn inst->phy;
}

static const stwuct phy_ops mtk_xsphy_ops = {
	.init		= mtk_phy_init,
	.exit		= mtk_phy_exit,
	.powew_on	= mtk_phy_powew_on,
	.powew_off	= mtk_phy_powew_off,
	.set_mode	= mtk_phy_set_mode,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id mtk_xsphy_id_tabwe[] = {
	{ .compatibwe = "mediatek,xsphy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, mtk_xsphy_id_tabwe);

static int mtk_xsphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd_np;
	stwuct phy_pwovidew *pwovidew;
	stwuct wesouwce *gwb_wes;
	stwuct mtk_xsphy *xsphy;
	stwuct wesouwce wes;
	int powt, wetvaw;

	xsphy = devm_kzawwoc(dev, sizeof(*xsphy), GFP_KEWNEW);
	if (!xsphy)
		wetuwn -ENOMEM;

	xsphy->nphys = of_get_chiwd_count(np);
	xsphy->phys = devm_kcawwoc(dev, xsphy->nphys,
				       sizeof(*xsphy->phys), GFP_KEWNEW);
	if (!xsphy->phys)
		wetuwn -ENOMEM;

	xsphy->dev = dev;
	pwatfowm_set_dwvdata(pdev, xsphy);

	gwb_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	/* optionaw, may not exist if no u3 phys */
	if (gwb_wes) {
		/* get banks shawed by muwtipwe u3 phys */
		xsphy->gwb_base = devm_iowemap_wesouwce(dev, gwb_wes);
		if (IS_EWW(xsphy->gwb_base)) {
			dev_eww(dev, "faiwed to wemap gwb wegs\n");
			wetuwn PTW_EWW(xsphy->gwb_base);
		}
	}

	xsphy->swc_wef_cwk = XSP_WEF_CWK;
	xsphy->swc_coef = XSP_SWEW_WATE_COEF;
	/* update pawametews of swew wate cawibwate if exist */
	device_pwopewty_wead_u32(dev, "mediatek,swc-wef-cwk-mhz",
				 &xsphy->swc_wef_cwk);
	device_pwopewty_wead_u32(dev, "mediatek,swc-coef", &xsphy->swc_coef);

	powt = 0;
	fow_each_chiwd_of_node(np, chiwd_np) {
		stwuct xsphy_instance *inst;
		stwuct phy *phy;

		inst = devm_kzawwoc(dev, sizeof(*inst), GFP_KEWNEW);
		if (!inst) {
			wetvaw = -ENOMEM;
			goto put_chiwd;
		}

		xsphy->phys[powt] = inst;

		phy = devm_phy_cweate(dev, chiwd_np, &mtk_xsphy_ops);
		if (IS_EWW(phy)) {
			dev_eww(dev, "faiwed to cweate phy\n");
			wetvaw = PTW_EWW(phy);
			goto put_chiwd;
		}

		wetvaw = of_addwess_to_wesouwce(chiwd_np, 0, &wes);
		if (wetvaw) {
			dev_eww(dev, "faiwed to get addwess wesouwce(id-%d)\n",
				powt);
			goto put_chiwd;
		}

		inst->powt_base = devm_iowemap_wesouwce(&phy->dev, &wes);
		if (IS_EWW(inst->powt_base)) {
			dev_eww(dev, "faiwed to wemap phy wegs\n");
			wetvaw = PTW_EWW(inst->powt_base);
			goto put_chiwd;
		}

		inst->phy = phy;
		inst->index = powt;
		phy_set_dwvdata(phy, inst);
		powt++;

		inst->wef_cwk = devm_cwk_get(&phy->dev, "wef");
		if (IS_EWW(inst->wef_cwk)) {
			dev_eww(dev, "faiwed to get wef_cwk(id-%d)\n", powt);
			wetvaw = PTW_EWW(inst->wef_cwk);
			goto put_chiwd;
		}
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, mtk_phy_xwate);
	wetuwn PTW_EWW_OW_ZEWO(pwovidew);

put_chiwd:
	of_node_put(chiwd_np);
	wetuwn wetvaw;
}

static stwuct pwatfowm_dwivew mtk_xsphy_dwivew = {
	.pwobe		= mtk_xsphy_pwobe,
	.dwivew		= {
		.name	= "mtk-xsphy",
		.of_match_tabwe = mtk_xsphy_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(mtk_xsphy_dwivew);

MODUWE_AUTHOW("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek USB XS-PHY dwivew");
MODUWE_WICENSE("GPW v2");
