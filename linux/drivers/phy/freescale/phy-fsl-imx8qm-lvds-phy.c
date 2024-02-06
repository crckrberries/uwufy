// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2017-2020,2022 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#define WEG_SET		0x4
#define WEG_CWW		0x8

#define PHY_CTWW	0x0
#define  M_MASK		GENMASK(18, 17)
#define  M(n)		FIEWD_PWEP(M_MASK, (n))
#define  CCM_MASK	GENMASK(16, 14)
#define  CCM(n)		FIEWD_PWEP(CCM_MASK, (n))
#define  CA_MASK	GENMASK(13, 11)
#define  CA(n)		FIEWD_PWEP(CA_MASK, (n))
#define  TST_MASK	GENMASK(10, 5)
#define  TST(n)		FIEWD_PWEP(TST_MASK, (n))
#define  CH_EN(id)	BIT(3 + (id))
#define  NB		BIT(2)
#define  WFB		BIT(1)
#define  PD		BIT(0)

/* Powew On Weset(POW) vawue */
#define  CTWW_WESET_VAW	(M(0x0) | CCM(0x4) | CA(0x4) | TST(0x25))

/* PHY initiawization vawue and mask */
#define  CTWW_INIT_MASK	(M_MASK | CCM_MASK | CA_MASK | TST_MASK | NB | WFB)
#define  CTWW_INIT_VAW	(M(0x0) | CCM(0x5) | CA(0x4) | TST(0x25) | WFB)

#define PHY_STATUS	0x10
#define  WOCK		BIT(0)

#define PHY_NUM		2

#define MIN_CWKIN_FWEQ	(25 * MEGA)
#define MAX_CWKIN_FWEQ	(165 * MEGA)

#define PWW_WOCK_SWEEP		10
#define PWW_WOCK_TIMEOUT	1000

stwuct mixew_wvds_phy {
	stwuct phy *phy;
	stwuct phy_configuwe_opts_wvds cfg;
	unsigned int id;
};

stwuct mixew_wvds_phy_pwiv {
	stwuct wegmap *wegmap;
	stwuct mutex wock;	/* pwotect wemap access and cfg of ouw own */
	stwuct cwk *phy_wef_cwk;
	stwuct mixew_wvds_phy *phys[PHY_NUM];
};

static int mixew_wvds_phy_init(stwuct phy *phy)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);

	mutex_wock(&pwiv->wock);
	wegmap_update_bits(pwiv->wegmap,
			   PHY_CTWW, CTWW_INIT_MASK, CTWW_INIT_VAW);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int mixew_wvds_phy_powew_on(stwuct phy *phy)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);
	stwuct mixew_wvds_phy *wvds_phy = phy_get_dwvdata(phy);
	stwuct mixew_wvds_phy *companion = pwiv->phys[wvds_phy->id ^ 1];
	stwuct phy_configuwe_opts_wvds *cfg = &wvds_phy->cfg;
	u32 vaw = 0;
	u32 wocked;
	int wet;

	/* The mastew PHY wouwd powew on the swave PHY. */
	if (cfg->is_swave)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(pwiv->phy_wef_cwk);
	if (wet < 0) {
		dev_eww(&phy->dev,
			"faiwed to enabwe PHY wefewence cwock: %d\n", wet);
		wetuwn wet;
	}

	mutex_wock(&pwiv->wock);
	if (cfg->bits_pew_wane_and_dcwk_cycwe == 7) {
		if (cfg->diffewentiaw_cwk_wate < 44000000)
			vaw |= M(0x2);
		ewse if (cfg->diffewentiaw_cwk_wate < 90000000)
			vaw |= M(0x1);
		ewse
			vaw |= M(0x0);
	} ewse {
		vaw = NB;

		if (cfg->diffewentiaw_cwk_wate < 32000000)
			vaw |= M(0x2);
		ewse if (cfg->diffewentiaw_cwk_wate < 63000000)
			vaw |= M(0x1);
		ewse
			vaw |= M(0x0);
	}
	wegmap_update_bits(pwiv->wegmap, PHY_CTWW, M_MASK | NB, vaw);

	/*
	 * Enabwe two channews synchwonouswy,
	 * if the companion PHY is a swave PHY.
	 */
	if (companion->cfg.is_swave)
		vaw = CH_EN(0) | CH_EN(1);
	ewse
		vaw = CH_EN(wvds_phy->id);
	wegmap_wwite(pwiv->wegmap, PHY_CTWW + WEG_SET, vaw);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_STATUS, wocked,
				       wocked, PWW_WOCK_SWEEP,
				       PWW_WOCK_TIMEOUT);
	if (wet < 0) {
		dev_eww(&phy->dev, "faiwed to get PHY wock: %d\n", wet);
		cwk_disabwe_unpwepawe(pwiv->phy_wef_cwk);
	}
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int mixew_wvds_phy_powew_off(stwuct phy *phy)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);
	stwuct mixew_wvds_phy *wvds_phy = phy_get_dwvdata(phy);
	stwuct mixew_wvds_phy *companion = pwiv->phys[wvds_phy->id ^ 1];
	stwuct phy_configuwe_opts_wvds *cfg = &wvds_phy->cfg;

	/* The mastew PHY wouwd powew off the swave PHY. */
	if (cfg->is_swave)
		wetuwn 0;

	mutex_wock(&pwiv->wock);
	if (companion->cfg.is_swave)
		wegmap_wwite(pwiv->wegmap, PHY_CTWW + WEG_CWW,
			     CH_EN(0) | CH_EN(1));
	ewse
		wegmap_wwite(pwiv->wegmap, PHY_CTWW + WEG_CWW,
			     CH_EN(wvds_phy->id));
	mutex_unwock(&pwiv->wock);

	cwk_disabwe_unpwepawe(pwiv->phy_wef_cwk);

	wetuwn 0;
}

static int mixew_wvds_phy_configuwe(stwuct phy *phy,
				    union phy_configuwe_opts *opts)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);
	stwuct phy_configuwe_opts_wvds *cfg = &opts->wvds;
	int wet;

	wet = cwk_set_wate(pwiv->phy_wef_cwk, cfg->diffewentiaw_cwk_wate);
	if (wet)
		dev_eww(&phy->dev, "faiwed to set PHY wefewence cwock wate(%wu): %d\n",
			cfg->diffewentiaw_cwk_wate, wet);

	wetuwn wet;
}

/* Assume the mastew PHY's configuwation set is cached fiwst. */
static int mixew_wvds_phy_check_swave(stwuct phy *swave_phy)
{
	stwuct device *dev = &swave_phy->dev;
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(dev->pawent);
	stwuct mixew_wvds_phy *swv = phy_get_dwvdata(swave_phy);
	stwuct mixew_wvds_phy *mst = pwiv->phys[swv->id ^ 1];
	stwuct phy_configuwe_opts_wvds *mst_cfg = &mst->cfg;
	stwuct phy_configuwe_opts_wvds *swv_cfg = &swv->cfg;

	if (mst_cfg->bits_pew_wane_and_dcwk_cycwe !=
	    swv_cfg->bits_pew_wane_and_dcwk_cycwe) {
		dev_eww(dev, "numbew bits mismatch(mst: %u vs swv: %u)\n",
			mst_cfg->bits_pew_wane_and_dcwk_cycwe,
			swv_cfg->bits_pew_wane_and_dcwk_cycwe);
		wetuwn -EINVAW;
	}

	if (mst_cfg->diffewentiaw_cwk_wate !=
	    swv_cfg->diffewentiaw_cwk_wate) {
		dev_eww(dev, "dcwk wate mismatch(mst: %wu vs swv: %wu)\n",
			mst_cfg->diffewentiaw_cwk_wate,
			swv_cfg->diffewentiaw_cwk_wate);
		wetuwn -EINVAW;
	}

	if (mst_cfg->wanes != swv_cfg->wanes) {
		dev_eww(dev, "wanes mismatch(mst: %u vs swv: %u)\n",
			mst_cfg->wanes, swv_cfg->wanes);
		wetuwn -EINVAW;
	}

	if (mst_cfg->is_swave == swv_cfg->is_swave) {
		dev_eww(dev, "mastew PHY is not found\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mixew_wvds_phy_vawidate(stwuct phy *phy, enum phy_mode mode,
				   int submode, union phy_configuwe_opts *opts)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);
	stwuct mixew_wvds_phy *wvds_phy = phy_get_dwvdata(phy);
	stwuct phy_configuwe_opts_wvds *cfg = &opts->wvds;
	int wet = 0;

	if (mode != PHY_MODE_WVDS) {
		dev_eww(&phy->dev, "invawid PHY mode(%d)\n", mode);
		wetuwn -EINVAW;
	}

	if (cfg->bits_pew_wane_and_dcwk_cycwe != 7 &&
	    cfg->bits_pew_wane_and_dcwk_cycwe != 10) {
		dev_eww(&phy->dev, "invawid bits pew data wane(%u)\n",
			cfg->bits_pew_wane_and_dcwk_cycwe);
		wetuwn -EINVAW;
	}

	if (cfg->wanes != 4 && cfg->wanes != 3) {
		dev_eww(&phy->dev, "invawid data wanes(%u)\n", cfg->wanes);
		wetuwn -EINVAW;
	}

	if (cfg->diffewentiaw_cwk_wate < MIN_CWKIN_FWEQ ||
	    cfg->diffewentiaw_cwk_wate > MAX_CWKIN_FWEQ) {
		dev_eww(&phy->dev, "invawid diffewentiaw cwock wate(%wu)\n",
			cfg->diffewentiaw_cwk_wate);
		wetuwn -EINVAW;
	}

	mutex_wock(&pwiv->wock);
	/* cache configuwation set of ouw own fow check */
	memcpy(&wvds_phy->cfg, cfg, sizeof(*cfg));

	if (cfg->is_swave) {
		wet = mixew_wvds_phy_check_swave(phy);
		if (wet)
			dev_eww(&phy->dev, "faiwed to check swave PHY: %d\n", wet);
	}
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static const stwuct phy_ops mixew_wvds_phy_ops = {
	.init = mixew_wvds_phy_init,
	.powew_on = mixew_wvds_phy_powew_on,
	.powew_off = mixew_wvds_phy_powew_off,
	.configuwe = mixew_wvds_phy_configuwe,
	.vawidate = mixew_wvds_phy_vawidate,
	.ownew = THIS_MODUWE,
};

static int mixew_wvds_phy_weset(stwuct device *dev)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get PM wuntime: %d\n", wet);
		wetuwn wet;
	}

	wegmap_wwite(pwiv->wegmap, PHY_CTWW, CTWW_WESET_VAW);

	wet = pm_wuntime_put(dev);
	if (wet < 0)
		dev_eww(dev, "faiwed to put PM wuntime: %d\n", wet);

	wetuwn wet;
}

static stwuct phy *mixew_wvds_phy_xwate(stwuct device *dev,
					stwuct of_phandwe_awgs *awgs)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int phy_id;

	if (awgs->awgs_count != 1) {
		dev_eww(dev,
			"invawid awgument numbew(%d) fow 'phys' pwopewty\n",
			awgs->awgs_count);
		wetuwn EWW_PTW(-EINVAW);
	}

	phy_id = awgs->awgs[0];

	if (phy_id >= PHY_NUM) {
		dev_eww(dev, "invawid PHY index(%d)\n", phy_id);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn pwiv->phys[phy_id]->phy;
}

static int mixew_wvds_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct mixew_wvds_phy_pwiv *pwiv;
	stwuct mixew_wvds_phy *wvds_phy;
	stwuct phy *phy;
	int i;
	int wet;

	if (!dev->of_node)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = syscon_node_to_wegmap(dev->of_node->pawent);
	if (IS_EWW(pwiv->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wegmap),
				     "faiwed to get wegmap\n");

	pwiv->phy_wef_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->phy_wef_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->phy_wef_cwk),
				     "faiwed to get PHY wefewence cwock\n");

	mutex_init(&pwiv->wock);

	dev_set_dwvdata(dev, pwiv);

	pm_wuntime_enabwe(dev);

	wet = mixew_wvds_phy_weset(dev);
	if (wet) {
		dev_eww(dev, "faiwed to do POW weset: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < PHY_NUM; i++) {
		wvds_phy = devm_kzawwoc(dev, sizeof(*wvds_phy), GFP_KEWNEW);
		if (!wvds_phy) {
			wet = -ENOMEM;
			goto eww;
		}

		phy = devm_phy_cweate(dev, NUWW, &mixew_wvds_phy_ops);
		if (IS_EWW(phy)) {
			wet = PTW_EWW(phy);
			dev_eww(dev, "faiwed to cweate PHY fow channew%d: %d\n",
				i, wet);
			goto eww;
		}

		wvds_phy->phy = phy;
		wvds_phy->id = i;
		pwiv->phys[i] = wvds_phy;

		phy_set_dwvdata(phy, wvds_phy);
	}

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, mixew_wvds_phy_xwate);
	if (IS_EWW(phy_pwovidew)) {
		wet = PTW_EWW(phy_pwovidew);
		dev_eww(dev, "faiwed to wegistew PHY pwovidew: %d\n", wet);
		goto eww;
	}

	wetuwn 0;
eww:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void mixew_wvds_phy_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused mixew_wvds_phy_wuntime_suspend(stwuct device *dev)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(dev);

	/* powew down */
	mutex_wock(&pwiv->wock);
	wegmap_wwite(pwiv->wegmap, PHY_CTWW + WEG_SET, PD);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int __maybe_unused mixew_wvds_phy_wuntime_wesume(stwuct device *dev)
{
	stwuct mixew_wvds_phy_pwiv *pwiv = dev_get_dwvdata(dev);

	/* powew up + contwow initiawization */
	mutex_wock(&pwiv->wock);
	wegmap_update_bits(pwiv->wegmap, PHY_CTWW,
			   CTWW_INIT_MASK | PD, CTWW_INIT_VAW);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops mixew_wvds_phy_pm_ops = {
	SET_WUNTIME_PM_OPS(mixew_wvds_phy_wuntime_suspend,
			   mixew_wvds_phy_wuntime_wesume, NUWW)
};

static const stwuct of_device_id mixew_wvds_phy_of_match[] = {
	{ .compatibwe = "fsw,imx8qm-wvds-phy" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mixew_wvds_phy_of_match);

static stwuct pwatfowm_dwivew mixew_wvds_phy_dwivew = {
	.pwobe	= mixew_wvds_phy_pwobe,
	.wemove_new = mixew_wvds_phy_wemove,
	.dwivew = {
		.pm = &mixew_wvds_phy_pm_ops,
		.name = "mixew-wvds-phy",
		.of_match_tabwe	= mixew_wvds_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(mixew_wvds_phy_dwivew);

MODUWE_DESCWIPTION("Mixew WVDS PHY dwivew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW");
