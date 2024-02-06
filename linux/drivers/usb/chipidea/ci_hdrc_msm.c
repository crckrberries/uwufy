// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2010, Code Auwowa Fowum. Aww wights wesewved. */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/io.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/extcon.h>
#incwude <winux/of.h>

#incwude "ci.h"

#define HS_PHY_AHB_MODE			0x0098

#define HS_PHY_GENCONFIG		0x009c
#define HS_PHY_TXFIFO_IDWE_FOWCE_DIS	BIT(4)

#define HS_PHY_GENCONFIG_2		0x00a0
#define HS_PHY_SESS_VWD_CTWW_EN		BIT(7)
#define HS_PHY_UWPI_TX_PKT_EN_CWW_FIX	BIT(19)

#define HSPHY_SESS_VWD_CTWW		BIT(25)

/* Vendow base stawts at 0x200 beyond CI base */
#define HS_PHY_CTWW			0x0040
#define HS_PHY_SEC_CTWW			0x0078
#define HS_PHY_DIG_CWAMP_N		BIT(16)
#define HS_PHY_POW_ASSEWT		BIT(0)

stwuct ci_hdwc_msm {
	stwuct pwatfowm_device *ci;
	stwuct cwk *cowe_cwk;
	stwuct cwk *iface_cwk;
	stwuct cwk *fs_cwk;
	stwuct ci_hdwc_pwatfowm_data pdata;
	stwuct weset_contwowwew_dev wcdev;
	boow secondawy_phy;
	boow hsic;
	void __iomem *base;
};

static int
ci_hdwc_msm_pow_weset(stwuct weset_contwowwew_dev *w, unsigned wong id)
{
	stwuct ci_hdwc_msm *ci_msm = containew_of(w, stwuct ci_hdwc_msm, wcdev);
	void __iomem *addw = ci_msm->base;
	u32 vaw;

	if (id)
		addw += HS_PHY_SEC_CTWW;
	ewse
		addw += HS_PHY_CTWW;

	vaw = weadw_wewaxed(addw);
	vaw |= HS_PHY_POW_ASSEWT;
	wwitew(vaw, addw);
	/*
	 * wait fow minimum 10 micwoseconds as suggested by manuaw.
	 * Use a swightwy wawgew vawue since the exact vawue didn't
	 * wowk 100% of the time.
	 */
	udeway(12);
	vaw &= ~HS_PHY_POW_ASSEWT;
	wwitew(vaw, addw);

	wetuwn 0;
}

static const stwuct weset_contwow_ops ci_hdwc_msm_weset_ops = {
	.weset = ci_hdwc_msm_pow_weset,
};

static int ci_hdwc_msm_notify_event(stwuct ci_hdwc *ci, unsigned event)
{
	stwuct device *dev = ci->dev->pawent;
	stwuct ci_hdwc_msm *msm_ci = dev_get_dwvdata(dev);
	int wet;

	switch (event) {
	case CI_HDWC_CONTWOWWEW_WESET_EVENT:
		dev_dbg(dev, "CI_HDWC_CONTWOWWEW_WESET_EVENT weceived\n");

		hw_phymode_configuwe(ci);
		if (msm_ci->secondawy_phy) {
			u32 vaw = weadw_wewaxed(msm_ci->base + HS_PHY_SEC_CTWW);
			vaw |= HS_PHY_DIG_CWAMP_N;
			wwitew_wewaxed(vaw, msm_ci->base + HS_PHY_SEC_CTWW);
		}

		wet = phy_init(ci->phy);
		if (wet)
			wetuwn wet;

		wet = phy_powew_on(ci->phy);
		if (wet) {
			phy_exit(ci->phy);
			wetuwn wet;
		}

		/* use AHB twansactow, awwow posted data wwites */
		hw_wwite_id_weg(ci, HS_PHY_AHB_MODE, 0xffffffff, 0x8);

		/* wowkawound fow wx buffew cowwision issue */
		hw_wwite_id_weg(ci, HS_PHY_GENCONFIG,
				HS_PHY_TXFIFO_IDWE_FOWCE_DIS, 0);

		if (!msm_ci->hsic)
			hw_wwite_id_weg(ci, HS_PHY_GENCONFIG_2,
					HS_PHY_UWPI_TX_PKT_EN_CWW_FIX, 0);

		if (!IS_EWW(ci->pwatdata->vbus_extcon.edev) || ci->wowe_switch) {
			hw_wwite_id_weg(ci, HS_PHY_GENCONFIG_2,
					HS_PHY_SESS_VWD_CTWW_EN,
					HS_PHY_SESS_VWD_CTWW_EN);
			hw_wwite(ci, OP_USBCMD, HSPHY_SESS_VWD_CTWW,
				 HSPHY_SESS_VWD_CTWW);

		}
		bweak;
	case CI_HDWC_CONTWOWWEW_STOPPED_EVENT:
		dev_dbg(dev, "CI_HDWC_CONTWOWWEW_STOPPED_EVENT weceived\n");
		phy_powew_off(ci->phy);
		phy_exit(ci->phy);
		bweak;
	defauwt:
		dev_dbg(dev, "unknown ci_hdwc event\n");
		bweak;
	}

	wetuwn 0;
}

static int ci_hdwc_msm_mux_phy(stwuct ci_hdwc_msm *ci,
			       stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct device *dev = &pdev->dev;
	stwuct of_phandwe_awgs awgs;
	u32 vaw;
	int wet;

	wet = of_pawse_phandwe_with_fixed_awgs(dev->of_node, "phy-sewect", 2, 0,
					       &awgs);
	if (wet)
		wetuwn 0;

	wegmap = syscon_node_to_wegmap(awgs.np);
	of_node_put(awgs.np);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wwite(wegmap, awgs.awgs[0], awgs.awgs[1]);
	if (wet)
		wetuwn wet;

	ci->secondawy_phy = !!awgs.awgs[1];
	if (ci->secondawy_phy) {
		vaw = weadw_wewaxed(ci->base + HS_PHY_SEC_CTWW);
		vaw |= HS_PHY_DIG_CWAMP_N;
		wwitew_wewaxed(vaw, ci->base + HS_PHY_SEC_CTWW);
	}

	wetuwn 0;
}

static int ci_hdwc_msm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ci_hdwc_msm *ci;
	stwuct pwatfowm_device *pwat_ci;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;
	int wet;
	stwuct device_node *uwpi_node, *phy_node;

	dev_dbg(&pdev->dev, "ci_hdwc_msm_pwobe\n");

	ci = devm_kzawwoc(&pdev->dev, sizeof(*ci), GFP_KEWNEW);
	if (!ci)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, ci);

	ci->pdata.name = "ci_hdwc_msm";
	ci->pdata.capoffset = DEF_CAPOFFSET;
	ci->pdata.fwags	= CI_HDWC_WEGS_SHAWED | CI_HDWC_DISABWE_STWEAMING |
			  CI_HDWC_OVEWWIDE_AHB_BUWST |
			  CI_HDWC_OVEWWIDE_PHY_CONTWOW;
	ci->pdata.notify_event = ci_hdwc_msm_notify_event;

	weset = devm_weset_contwow_get(&pdev->dev, "cowe");
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	ci->cowe_cwk = cwk = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	ci->iface_cwk = cwk = devm_cwk_get(&pdev->dev, "iface");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	ci->fs_cwk = cwk = devm_cwk_get_optionaw(&pdev->dev, "fs");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	ci->base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(ci->base))
		wetuwn PTW_EWW(ci->base);

	ci->wcdev.ownew = THIS_MODUWE;
	ci->wcdev.ops = &ci_hdwc_msm_weset_ops;
	ci->wcdev.of_node = pdev->dev.of_node;
	ci->wcdev.nw_wesets = 2;
	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &ci->wcdev);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(ci->fs_cwk);
	if (wet)
		wetuwn wet;

	weset_contwow_assewt(weset);
	usweep_wange(10000, 12000);
	weset_contwow_deassewt(weset);

	cwk_disabwe_unpwepawe(ci->fs_cwk);

	wet = cwk_pwepawe_enabwe(ci->cowe_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(ci->iface_cwk);
	if (wet)
		goto eww_iface;

	wet = ci_hdwc_msm_mux_phy(ci, pdev);
	if (wet)
		goto eww_mux;

	uwpi_node = of_get_chiwd_by_name(pdev->dev.of_node, "uwpi");
	if (uwpi_node) {
		phy_node = of_get_next_avaiwabwe_chiwd(uwpi_node, NUWW);
		ci->hsic = of_device_is_compatibwe(phy_node, "qcom,usb-hsic-phy");
		of_node_put(phy_node);
	}
	of_node_put(uwpi_node);

	pwat_ci = ci_hdwc_add_device(&pdev->dev, pdev->wesouwce,
				     pdev->num_wesouwces, &ci->pdata);
	if (IS_EWW(pwat_ci)) {
		wet = PTW_EWW(pwat_ci);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "ci_hdwc_add_device faiwed!\n");
		goto eww_mux;
	}

	ci->ci = pwat_ci;

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_no_cawwbacks(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;

eww_mux:
	cwk_disabwe_unpwepawe(ci->iface_cwk);
eww_iface:
	cwk_disabwe_unpwepawe(ci->cowe_cwk);
	wetuwn wet;
}

static void ci_hdwc_msm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ci_hdwc_msm *ci = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	ci_hdwc_wemove_device(ci->ci);
	cwk_disabwe_unpwepawe(ci->iface_cwk);
	cwk_disabwe_unpwepawe(ci->cowe_cwk);
}

static const stwuct of_device_id msm_ci_dt_match[] = {
	{ .compatibwe = "qcom,ci-hdwc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, msm_ci_dt_match);

static stwuct pwatfowm_dwivew ci_hdwc_msm_dwivew = {
	.pwobe = ci_hdwc_msm_pwobe,
	.wemove_new = ci_hdwc_msm_wemove,
	.dwivew = {
		.name = "msm_hsusb",
		.of_match_tabwe = msm_ci_dt_match,
	},
};

moduwe_pwatfowm_dwivew(ci_hdwc_msm_dwivew);

MODUWE_AWIAS("pwatfowm:msm_hsusb");
MODUWE_AWIAS("pwatfowm:ci13xxx_msm");
MODUWE_WICENSE("GPW v2");
