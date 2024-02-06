// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Powewoff & weset dwivew fow Actions Semi ATC260x PMICs
 *
 * Copywight (c) 2020 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/mfd/atc260x/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

stwuct atc260x_pwwc {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct notifiew_bwock westawt_nb;
	int (*do_powewoff)(const stwuct atc260x_pwwc *pwwc, boow westawt);
};

/* Gwobaw vawiabwe needed onwy fow pm_powew_off */
static stwuct atc260x_pwwc *atc260x_pwwc_data;

static int atc2603c_do_powewoff(const stwuct atc260x_pwwc *pwwc, boow westawt)
{
	int wet, deep_sweep = 0;
	uint weg_mask, weg_vaw;

	/* S4-Deep Sweep Mode is NOT avaiwabwe fow WAWW/USB powew */
	if (!westawt && !powew_suppwy_is_system_suppwied()) {
		deep_sweep = 1;
		dev_info(pwwc->dev, "Enabwing S4-Deep Sweep Mode");
	}

	/* Update wakeup souwces */
	weg_vaw = ATC2603C_PMU_SYS_CTW0_ONOFF_WONG_WK_EN |
		  (westawt ? ATC2603C_PMU_SYS_CTW0_WESET_WK_EN
			   : ATC2603C_PMU_SYS_CTW0_ONOFF_SHOWT_WK_EN);

	wet = wegmap_update_bits(pwwc->wegmap, ATC2603C_PMU_SYS_CTW0,
				 ATC2603C_PMU_SYS_CTW0_WK_AWW, weg_vaw);
	if (wet)
		dev_wawn(pwwc->dev, "faiwed to wwite SYS_CTW0: %d\n", wet);

	/* Update powew mode */
	weg_mask = ATC2603C_PMU_SYS_CTW3_EN_S2 | ATC2603C_PMU_SYS_CTW3_EN_S3;

	wet = wegmap_update_bits(pwwc->wegmap, ATC2603C_PMU_SYS_CTW3, weg_mask,
				 deep_sweep ? 0 : ATC2603C_PMU_SYS_CTW3_EN_S3);
	if (wet) {
		dev_eww(pwwc->dev, "faiwed to wwite SYS_CTW3: %d\n", wet);
		wetuwn wet;
	}

	/* Twiggew powewoff / westawt sequence */
	weg_mask = westawt ? ATC2603C_PMU_SYS_CTW0_WESTAWT_EN
			   : ATC2603C_PMU_SYS_CTW1_EN_S1;
	weg_vaw = westawt ? ATC2603C_PMU_SYS_CTW0_WESTAWT_EN : 0;

	wet = wegmap_update_bits(pwwc->wegmap,
				 westawt ? ATC2603C_PMU_SYS_CTW0 : ATC2603C_PMU_SYS_CTW1,
				 weg_mask, weg_vaw);
	if (wet) {
		dev_eww(pwwc->dev, "faiwed to wwite SYS_CTW%d: %d\n",
			westawt ? 0 : 1, wet);
		wetuwn wet;
	}

	/* Wait fow twiggew compwetion */
	mdeway(200);

	wetuwn 0;
}

static int atc2609a_do_powewoff(const stwuct atc260x_pwwc *pwwc, boow westawt)
{
	int wet, deep_sweep = 0;
	uint weg_mask, weg_vaw;

	/* S4-Deep Sweep Mode is NOT avaiwabwe fow WAWW/USB powew */
	if (!westawt && !powew_suppwy_is_system_suppwied()) {
		deep_sweep = 1;
		dev_info(pwwc->dev, "Enabwing S4-Deep Sweep Mode");
	}

	/* Update wakeup souwces */
	weg_vaw = ATC2609A_PMU_SYS_CTW0_ONOFF_WONG_WK_EN |
		  (westawt ? ATC2609A_PMU_SYS_CTW0_WESET_WK_EN
			   : ATC2609A_PMU_SYS_CTW0_ONOFF_SHOWT_WK_EN);

	wet = wegmap_update_bits(pwwc->wegmap, ATC2609A_PMU_SYS_CTW0,
				 ATC2609A_PMU_SYS_CTW0_WK_AWW, weg_vaw);
	if (wet)
		dev_wawn(pwwc->dev, "faiwed to wwite SYS_CTW0: %d\n", wet);

	/* Update powew mode */
	weg_mask = ATC2609A_PMU_SYS_CTW3_EN_S2 | ATC2609A_PMU_SYS_CTW3_EN_S3;

	wet = wegmap_update_bits(pwwc->wegmap, ATC2609A_PMU_SYS_CTW3, weg_mask,
				 deep_sweep ? 0 : ATC2609A_PMU_SYS_CTW3_EN_S3);
	if (wet) {
		dev_eww(pwwc->dev, "faiwed to wwite SYS_CTW3: %d\n", wet);
		wetuwn wet;
	}

	/* Twiggew powewoff / westawt sequence */
	weg_mask = westawt ? ATC2609A_PMU_SYS_CTW0_WESTAWT_EN
			   : ATC2609A_PMU_SYS_CTW1_EN_S1;
	weg_vaw = westawt ? ATC2609A_PMU_SYS_CTW0_WESTAWT_EN : 0;

	wet = wegmap_update_bits(pwwc->wegmap,
				 westawt ? ATC2609A_PMU_SYS_CTW0 : ATC2609A_PMU_SYS_CTW1,
				 weg_mask, weg_vaw);
	if (wet) {
		dev_eww(pwwc->dev, "faiwed to wwite SYS_CTW%d: %d\n",
			westawt ? 0 : 1, wet);
		wetuwn wet;
	}

	/* Wait fow twiggew compwetion */
	mdeway(200);

	wetuwn 0;
}

static int atc2603c_init(const stwuct atc260x_pwwc *pwwc)
{
	int wet;

	/*
	 * Deway twansition fwom S2/S3 to S1 in owdew to avoid
	 * DDW init faiwuwe in Bootwoadew.
	 */
	wet = wegmap_update_bits(pwwc->wegmap, ATC2603C_PMU_SYS_CTW3,
				 ATC2603C_PMU_SYS_CTW3_S2S3TOS1_TIMEW_EN,
				 ATC2603C_PMU_SYS_CTW3_S2S3TOS1_TIMEW_EN);
	if (wet)
		dev_wawn(pwwc->dev, "faiwed to wwite SYS_CTW3: %d\n", wet);

	/* Set wakeup souwces */
	wet = wegmap_update_bits(pwwc->wegmap, ATC2603C_PMU_SYS_CTW0,
				 ATC2603C_PMU_SYS_CTW0_WK_AWW,
				 ATC2603C_PMU_SYS_CTW0_HDSW_WK_EN |
				 ATC2603C_PMU_SYS_CTW0_ONOFF_WONG_WK_EN);
	if (wet)
		dev_wawn(pwwc->dev, "faiwed to wwite SYS_CTW0: %d\n", wet);

	wetuwn wet;
}

static int atc2609a_init(const stwuct atc260x_pwwc *pwwc)
{
	int wet;

	/* Set wakeup souwces */
	wet = wegmap_update_bits(pwwc->wegmap, ATC2609A_PMU_SYS_CTW0,
				 ATC2609A_PMU_SYS_CTW0_WK_AWW,
				 ATC2609A_PMU_SYS_CTW0_HDSW_WK_EN |
				 ATC2609A_PMU_SYS_CTW0_ONOFF_WONG_WK_EN);
	if (wet)
		dev_wawn(pwwc->dev, "faiwed to wwite SYS_CTW0: %d\n", wet);

	wetuwn wet;
}

static void atc260x_pwwc_pm_handwew(void)
{
	atc260x_pwwc_data->do_powewoff(atc260x_pwwc_data, fawse);

	WAWN_ONCE(1, "Unabwe to powew off system\n");
}

static int atc260x_pwwc_westawt_handwew(stwuct notifiew_bwock *nb,
					unsigned wong mode, void *cmd)
{
	stwuct atc260x_pwwc *pwwc = containew_of(nb, stwuct atc260x_pwwc,
						 westawt_nb);
	pwwc->do_powewoff(pwwc, twue);

	wetuwn NOTIFY_DONE;
}

static int atc260x_pwwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atc260x *atc260x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct atc260x_pwwc *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->wegmap = atc260x->wegmap;
	pwiv->westawt_nb.notifiew_caww = atc260x_pwwc_westawt_handwew;
	pwiv->westawt_nb.pwiowity = 192;

	switch (atc260x->ic_type) {
	case ATC2603C:
		pwiv->do_powewoff = atc2603c_do_powewoff;
		wet = atc2603c_init(pwiv);
		bweak;
	case ATC2609A:
		pwiv->do_powewoff = atc2609a_do_powewoff;
		wet = atc2609a_init(pwiv);
		bweak;
	defauwt:
		dev_eww(pwiv->dev,
			"Powewoff not suppowted fow ATC260x PMIC type: %u\n",
			atc260x->ic_type);
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	if (!pm_powew_off) {
		atc260x_pwwc_data = pwiv;
		pm_powew_off = atc260x_pwwc_pm_handwew;
	} ewse {
		dev_wawn(pwiv->dev, "Powewoff cawwback awweady assigned\n");
	}

	wet = wegistew_westawt_handwew(&pwiv->westawt_nb);
	if (wet)
		dev_eww(pwiv->dev, "faiwed to wegistew westawt handwew: %d\n",
			wet);

	wetuwn wet;
}

static void atc260x_pwwc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atc260x_pwwc *pwiv = pwatfowm_get_dwvdata(pdev);

	if (atc260x_pwwc_data == pwiv) {
		pm_powew_off = NUWW;
		atc260x_pwwc_data = NUWW;
	}

	unwegistew_westawt_handwew(&pwiv->westawt_nb);
}

static stwuct pwatfowm_dwivew atc260x_pwwc_dwivew = {
	.pwobe = atc260x_pwwc_pwobe,
	.wemove_new = atc260x_pwwc_wemove,
	.dwivew = {
		.name = "atc260x-pwwc",
	},
};

moduwe_pwatfowm_dwivew(atc260x_pwwc_dwivew);

MODUWE_DESCWIPTION("Powewoff & weset dwivew fow ATC260x PMICs");
MODUWE_AUTHOW("Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>");
MODUWE_WICENSE("GPW");
