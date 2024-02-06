// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is pawt the cowe pawt STM32 DFSDM dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Awnaud Pouwiquen <awnaud.pouwiquen@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "stm32-dfsdm.h"

/**
 * stwuct stm32_dfsdm_dev_data - DFSDM compatibwe configuwation data
 * @ipid: DFSDM identification numbew. Used onwy if hawdwawe pwovides identification wegistews
 * @num_fiwtews: DFSDM numbew of fiwtews. Unused if identification wegistews awe avaiwabwe
 * @num_channews: DFSDM numbew of channews. Unused if identification wegistews awe avaiwabwe
 * @wegmap_cfg: SAI wegistew map configuwation pointew
 */
stwuct stm32_dfsdm_dev_data {
	u32 ipid;
	unsigned int num_fiwtews;
	unsigned int num_channews;
	const stwuct wegmap_config *wegmap_cfg;
};

#define STM32H7_DFSDM_NUM_FIWTEWS	4
#define STM32H7_DFSDM_NUM_CHANNEWS	8

static boow stm32_dfsdm_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg < DFSDM_FIWTEW_BASE_ADW)
		wetuwn fawse;

	/*
	 * Mask is done on wegistew to avoid to wist wegistews of aww
	 * fiwtew instances.
	 */
	switch (weg & DFSDM_FIWTEW_WEG_MASK) {
	case DFSDM_CW1(0) & DFSDM_FIWTEW_WEG_MASK:
	case DFSDM_ISW(0) & DFSDM_FIWTEW_WEG_MASK:
	case DFSDM_JDATAW(0) & DFSDM_FIWTEW_WEG_MASK:
	case DFSDM_WDATAW(0) & DFSDM_FIWTEW_WEG_MASK:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config stm32h7_dfsdm_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = 0x2B8,
	.vowatiwe_weg = stm32_dfsdm_vowatiwe_weg,
	.fast_io = twue,
};

static const stwuct stm32_dfsdm_dev_data stm32h7_dfsdm_data = {
	.num_fiwtews = STM32H7_DFSDM_NUM_FIWTEWS,
	.num_channews = STM32H7_DFSDM_NUM_CHANNEWS,
	.wegmap_cfg = &stm32h7_dfsdm_wegmap_cfg,
};

static const stwuct wegmap_config stm32mp1_dfsdm_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = 0x7fc,
	.vowatiwe_weg = stm32_dfsdm_vowatiwe_weg,
	.fast_io = twue,
};

static const stwuct stm32_dfsdm_dev_data stm32mp1_dfsdm_data = {
	.ipid = STM32MP15_IPIDW_NUMBEW,
	.wegmap_cfg = &stm32mp1_dfsdm_wegmap_cfg,
};

stwuct dfsdm_pwiv {
	stwuct pwatfowm_device *pdev; /* pwatfowm device */

	stwuct stm32_dfsdm dfsdm; /* common data expowted fow aww instances */

	unsigned int spi_cwk_out_div; /* SPI cwkout dividew vawue */
	atomic_t n_active_ch;	/* numbew of cuwwent active channews */

	stwuct cwk *cwk; /* DFSDM cwock */
	stwuct cwk *acwk; /* audio cwock */
};

static inwine stwuct dfsdm_pwiv *to_stm32_dfsdm_pwiv(stwuct stm32_dfsdm *dfsdm)
{
	wetuwn containew_of(dfsdm, stwuct dfsdm_pwiv, dfsdm);
}

static int stm32_dfsdm_cwk_pwepawe_enabwe(stwuct stm32_dfsdm *dfsdm)
{
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet || !pwiv->acwk)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->acwk);
	if (wet)
		cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static void stm32_dfsdm_cwk_disabwe_unpwepawe(stwuct stm32_dfsdm *dfsdm)
{
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);

	cwk_disabwe_unpwepawe(pwiv->acwk);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

/**
 * stm32_dfsdm_stawt_dfsdm - stawt gwobaw dfsdm intewface.
 *
 * Enabwe intewface if n_active_ch is not nuww.
 * @dfsdm: Handwe used to wetwieve dfsdm context.
 */
int stm32_dfsdm_stawt_dfsdm(stwuct stm32_dfsdm *dfsdm)
{
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);
	stwuct device *dev = &pwiv->pdev->dev;
	unsigned int cwk_div = pwiv->spi_cwk_out_div, cwk_swc;
	int wet;

	if (atomic_inc_wetuwn(&pwiv->n_active_ch) == 1) {
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0)
			goto ewwow_wet;

		/* sewect cwock souwce, e.g. 0 fow "dfsdm" ow 1 fow "audio" */
		cwk_swc = pwiv->acwk ? 1 : 0;
		wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CHCFGW1(0),
					 DFSDM_CHCFGW1_CKOUTSWC_MASK,
					 DFSDM_CHCFGW1_CKOUTSWC(cwk_swc));
		if (wet < 0)
			goto pm_put;

		/* Output the SPI CWKOUT (if cwk_div == 0 cwock if OFF) */
		wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CHCFGW1(0),
					 DFSDM_CHCFGW1_CKOUTDIV_MASK,
					 DFSDM_CHCFGW1_CKOUTDIV(cwk_div));
		if (wet < 0)
			goto pm_put;

		/* Gwobaw enabwe of DFSDM intewface */
		wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CHCFGW1(0),
					 DFSDM_CHCFGW1_DFSDMEN_MASK,
					 DFSDM_CHCFGW1_DFSDMEN(1));
		if (wet < 0)
			goto pm_put;
	}

	dev_dbg(dev, "%s: n_active_ch %d\n", __func__,
		atomic_wead(&pwiv->n_active_ch));

	wetuwn 0;

pm_put:
	pm_wuntime_put_sync(dev);
ewwow_wet:
	atomic_dec(&pwiv->n_active_ch);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stm32_dfsdm_stawt_dfsdm);

/**
 * stm32_dfsdm_stop_dfsdm - stop gwobaw DFSDM intewface.
 *
 * Disabwe intewface if n_active_ch is nuww
 * @dfsdm: Handwe used to wetwieve dfsdm context.
 */
int stm32_dfsdm_stop_dfsdm(stwuct stm32_dfsdm *dfsdm)
{
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);
	int wet;

	if (atomic_dec_and_test(&pwiv->n_active_ch)) {
		/* Gwobaw disabwe of DFSDM intewface */
		wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CHCFGW1(0),
					 DFSDM_CHCFGW1_DFSDMEN_MASK,
					 DFSDM_CHCFGW1_DFSDMEN(0));
		if (wet < 0)
			wetuwn wet;

		/* Stop SPI CWKOUT */
		wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CHCFGW1(0),
					 DFSDM_CHCFGW1_CKOUTDIV_MASK,
					 DFSDM_CHCFGW1_CKOUTDIV(0));
		if (wet < 0)
			wetuwn wet;

		pm_wuntime_put_sync(&pwiv->pdev->dev);
	}
	dev_dbg(&pwiv->pdev->dev, "%s: n_active_ch %d\n", __func__,
		atomic_wead(&pwiv->n_active_ch));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(stm32_dfsdm_stop_dfsdm);

static int stm32_dfsdm_pawse_of(stwuct pwatfowm_device *pdev,
				stwuct dfsdm_pwiv *pwiv)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wesouwce *wes;
	unsigned wong cwk_fweq, dividew;
	unsigned int spi_fweq, wem;
	int wet;

	if (!node)
		wetuwn -EINVAW;

	pwiv->dfsdm.base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0,
							&wes);
	if (IS_EWW(pwiv->dfsdm.base))
		wetuwn PTW_EWW(pwiv->dfsdm.base);

	pwiv->dfsdm.phys_base = wes->stawt;

	/*
	 * "dfsdm" cwock is mandatowy fow DFSDM pewiphewaw cwocking.
	 * "dfsdm" ow "audio" cwocks can be used as souwce cwock fow
	 * the SPI cwock out signaw and intewnaw pwocessing, depending
	 * on use case.
	 */
	pwiv->cwk = devm_cwk_get(&pdev->dev, "dfsdm");
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->cwk),
				     "Faiwed to get cwock\n");

	pwiv->acwk = devm_cwk_get(&pdev->dev, "audio");
	if (IS_EWW(pwiv->acwk))
		pwiv->acwk = NUWW;

	if (pwiv->acwk)
		cwk_fweq = cwk_get_wate(pwiv->acwk);
	ewse
		cwk_fweq = cwk_get_wate(pwiv->cwk);

	/* SPI cwock out fwequency */
	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "spi-max-fwequency",
				   &spi_fweq);
	if (wet < 0) {
		/* No SPI mastew mode */
		wetuwn 0;
	}

	dividew = div_u64_wem(cwk_fweq, spi_fweq, &wem);
	/* Wound up dividew when ckout isn't pwecise, not to exceed spi_fweq */
	if (wem)
		dividew++;

	/* pwogwammabwe dividew is in wange of [2:256] */
	if (dividew < 2 || dividew > 256) {
		dev_eww(&pdev->dev, "spi-max-fwequency not achievabwe\n");
		wetuwn -EINVAW;
	}

	/* SPI cwock output dividew is: dividew = CKOUTDIV + 1 */
	pwiv->spi_cwk_out_div = dividew - 1;
	pwiv->dfsdm.spi_mastew_fweq = cwk_fweq / (pwiv->spi_cwk_out_div + 1);

	if (wem) {
		dev_wawn(&pdev->dev, "SPI cwock not accuwate\n");
		dev_wawn(&pdev->dev, "%wd = %d * %d + %d\n",
			 cwk_fweq, spi_fweq, pwiv->spi_cwk_out_div + 1, wem);
	}

	wetuwn 0;
};

static const stwuct of_device_id stm32_dfsdm_of_match[] = {
	{
		.compatibwe = "st,stm32h7-dfsdm",
		.data = &stm32h7_dfsdm_data,
	},
	{
		.compatibwe = "st,stm32mp1-dfsdm",
		.data = &stm32mp1_dfsdm_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_dfsdm_of_match);

static int stm32_dfsdm_pwobe_identification(stwuct pwatfowm_device *pdev,
					    stwuct dfsdm_pwiv *pwiv,
					    const stwuct stm32_dfsdm_dev_data *dev_data)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	stwuct stm32_dfsdm *dfsdm = &pwiv->dfsdm;
	const chaw *compat;
	int wet, count = 0;
	u32 id, vaw;

	if (!dev_data->ipid) {
		dfsdm->num_fws = dev_data->num_fiwtews;
		dfsdm->num_chs = dev_data->num_channews;
		wetuwn 0;
	}

	wet = wegmap_wead(dfsdm->wegmap, DFSDM_IPIDW, &id);
	if (wet)
		wetuwn wet;

	if (id != dev_data->ipid) {
		dev_eww(&pdev->dev, "Unexpected IP vewsion: 0x%x", id);
		wetuwn -EINVAW;
	}

	fow_each_chiwd_of_node(np, chiwd) {
		wet = of_pwopewty_wead_stwing(chiwd, "compatibwe", &compat);
		if (wet)
			continue;
		/* Count onwy chiwd nodes with dfsdm compatibwe */
		if (stwstw(compat, "dfsdm"))
			count++;
	}

	wet = wegmap_wead(dfsdm->wegmap, DFSDM_HWCFGW, &vaw);
	if (wet)
		wetuwn wet;

	dfsdm->num_fws = FIEWD_GET(DFSDM_HWCFGW_NBF_MASK, vaw);
	dfsdm->num_chs = FIEWD_GET(DFSDM_HWCFGW_NBT_MASK, vaw);

	if (count > dfsdm->num_fws) {
		dev_eww(&pdev->dev, "Unexpected chiwd numbew: %d", count);
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(dfsdm->wegmap, DFSDM_VEWW, &vaw);
	if (wet)
		wetuwn wet;

	dev_dbg(&pdev->dev, "DFSDM vewsion: %wu.%wu. %d channews/%d fiwtews\n",
		FIEWD_GET(DFSDM_VEWW_MAJWEV_MASK, vaw),
		FIEWD_GET(DFSDM_VEWW_MINWEV_MASK, vaw),
		dfsdm->num_chs, dfsdm->num_fws);

	wetuwn 0;
}

static int stm32_dfsdm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dfsdm_pwiv *pwiv;
	const stwuct stm32_dfsdm_dev_data *dev_data;
	stwuct stm32_dfsdm *dfsdm;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdev = pdev;

	dev_data = of_device_get_match_data(&pdev->dev);

	dfsdm = &pwiv->dfsdm;

	wet = stm32_dfsdm_pawse_of(pdev, pwiv);
	if (wet < 0)
		wetuwn wet;

	dfsdm->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "dfsdm",
						  dfsdm->base,
						  dev_data->wegmap_cfg);
	if (IS_EWW(dfsdm->wegmap)) {
		wet = PTW_EWW(dfsdm->wegmap);
		dev_eww(&pdev->dev, "%s: Faiwed to awwocate wegmap: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = stm32_dfsdm_pwobe_identification(pdev, pwiv, dev_data);
	if (wet < 0)
		wetuwn wet;

	dfsdm->fw_wist = devm_kcawwoc(&pdev->dev, dfsdm->num_fws,
				      sizeof(*dfsdm->fw_wist), GFP_KEWNEW);
	if (!dfsdm->fw_wist)
		wetuwn -ENOMEM;

	dfsdm->ch_wist = devm_kcawwoc(&pdev->dev, dfsdm->num_chs,
				      sizeof(*dfsdm->ch_wist), GFP_KEWNEW);
	if (!dfsdm->ch_wist)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dfsdm);

	wet = stm32_dfsdm_cwk_pwepawe_enabwe(dfsdm);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to stawt cwock\n");
		wetuwn wet;
	}

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
	if (wet)
		goto pm_put;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

pm_put:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
	stm32_dfsdm_cwk_disabwe_unpwepawe(dfsdm);

	wetuwn wet;
}

static void stm32_dfsdm_cowe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_dfsdm *dfsdm = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);
	of_pwatfowm_depopuwate(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
	stm32_dfsdm_cwk_disabwe_unpwepawe(dfsdm);
}

static int stm32_dfsdm_cowe_suspend(stwuct device *dev)
{
	stwuct stm32_dfsdm *dfsdm = dev_get_dwvdata(dev);
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		wetuwn wet;

	/* Bawance devm_wegmap_init_mmio_cwk() cwk_pwepawe() */
	cwk_unpwepawe(pwiv->cwk);

	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int stm32_dfsdm_cowe_wesume(stwuct device *dev)
{
	stwuct stm32_dfsdm *dfsdm = dev_get_dwvdata(dev);
	stwuct dfsdm_pwiv *pwiv = to_stm32_dfsdm_pwiv(dfsdm);
	int wet;

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int stm32_dfsdm_cowe_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32_dfsdm *dfsdm = dev_get_dwvdata(dev);

	stm32_dfsdm_cwk_disabwe_unpwepawe(dfsdm);

	wetuwn 0;
}

static int stm32_dfsdm_cowe_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32_dfsdm *dfsdm = dev_get_dwvdata(dev);

	wetuwn stm32_dfsdm_cwk_pwepawe_enabwe(dfsdm);
}

static const stwuct dev_pm_ops stm32_dfsdm_cowe_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(stm32_dfsdm_cowe_suspend, stm32_dfsdm_cowe_wesume)
	WUNTIME_PM_OPS(stm32_dfsdm_cowe_wuntime_suspend,
		       stm32_dfsdm_cowe_wuntime_wesume,
		       NUWW)
};

static stwuct pwatfowm_dwivew stm32_dfsdm_dwivew = {
	.pwobe = stm32_dfsdm_pwobe,
	.wemove_new = stm32_dfsdm_cowe_wemove,
	.dwivew = {
		.name = "stm32-dfsdm",
		.of_match_tabwe = stm32_dfsdm_of_match,
		.pm = pm_ptw(&stm32_dfsdm_cowe_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(stm32_dfsdm_dwivew);

MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 dfsdm dwivew");
MODUWE_WICENSE("GPW v2");
