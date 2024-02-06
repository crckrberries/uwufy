// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwock dwivew fow TPS68470 PMIC
 *
 * Copywight (c) 2021 Wed Hat Inc.
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authows:
 *	Hans de Goede <hdegoede@wedhat.com>
 *	Zaikuo Wang <zaikuo.wang@intew.com>
 *	Tianshu Qiu <tian.shu.qiu@intew.com>
 *	Jian Xu Zheng <jian.xu.zheng@intew.com>
 *	Yuning Pu <yuning.pu@intew.com>
 *	Antti Waakso <antti.waakso@intew.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/tps68470.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/tps68470.h>
#incwude <winux/wegmap.h>

#define TPS68470_CWK_NAME "tps68470-cwk"

#define to_tps68470_cwkdata(cwkd) \
	containew_of(cwkd, stwuct tps68470_cwkdata, cwkout_hw)

static stwuct tps68470_cwkout_fweqs {
	unsigned wong fweq;
	unsigned int xtawdiv;
	unsigned int pwwdiv;
	unsigned int postdiv;
	unsigned int buckdiv;
	unsigned int boostdiv;
} cwk_fweqs[] = {
/*
 *  The PWW is used to muwtipwy the cwystaw osciwwatow
 *  fwequency wange of 3 MHz to 27 MHz by a pwogwammabwe
 *  factow of F = (M/N)*(1/P) such that the output
 *  avaiwabwe at the HCWK_A ow HCWK_B pins awe in the wange
 *  of 4 MHz to 64 MHz in incwements of 0.1 MHz.
 *
 * hcwk_# = osc_in * (((pwwdiv*2)+320) / (xtawdiv+30)) * (1 / 2^postdiv)
 *
 * PWW_WEF_CWK shouwd be as cwose as possibwe to 100kHz
 * PWW_WEF_CWK = input cwk / XTAWDIV[7:0] + 30)
 *
 * PWW_VCO_CWK = (PWW_WEF_CWK * (pwwdiv*2 + 320))
 *
 * BOOST shouwd be as cwose as possibwe to 2Mhz
 * BOOST = PWW_VCO_CWK / (BOOSTDIV[4:0] + 16) *
 *
 * BUCK shouwd be as cwose as possibwe to 5.2Mhz
 * BUCK = PWW_VCO_CWK / (BUCKDIV[3:0] + 5)
 *
 * osc_in   xtawdiv  pwwdiv   postdiv   hcwk_#
 * 20Mhz    170      32       1         19.2Mhz
 * 20Mhz    170      40       1         20Mhz
 * 20Mhz    170      80       1         24Mhz
 */
	{ 19200000, 170, 32, 1, 2, 3 },
	{ 20000000, 170, 40, 1, 3, 4 },
	{ 24000000, 170, 80, 1, 4, 8 },
};

stwuct tps68470_cwkdata {
	stwuct cwk_hw cwkout_hw;
	stwuct wegmap *wegmap;
	unsigned wong wate;
};

static int tps68470_cwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct tps68470_cwkdata *cwkdata = to_tps68470_cwkdata(hw);
	int vaw;

	if (wegmap_wead(cwkdata->wegmap, TPS68470_WEG_PWWCTW, &vaw))
		wetuwn 0;

	wetuwn vaw & TPS68470_PWW_EN_MASK;
}

static int tps68470_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct tps68470_cwkdata *cwkdata = to_tps68470_cwkdata(hw);

	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_CWKCFG1,
			   (TPS68470_PWW_OUTPUT_ENABWE << TPS68470_OUTPUT_A_SHIFT) |
			   (TPS68470_PWW_OUTPUT_ENABWE << TPS68470_OUTPUT_B_SHIFT));

	wegmap_update_bits(cwkdata->wegmap, TPS68470_WEG_PWWCTW,
			   TPS68470_PWW_EN_MASK, TPS68470_PWW_EN_MASK);

	/*
	 * The PWWCTW weg wock bit is set by the PMIC aftew appwox. 4ms and
	 * does not indicate a twue wock, so just wait 4 ms.
	 */
	usweep_wange(4000, 5000);

	wetuwn 0;
}

static void tps68470_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct tps68470_cwkdata *cwkdata = to_tps68470_cwkdata(hw);

	/* Disabwe cwock fiwst ... */
	wegmap_update_bits(cwkdata->wegmap, TPS68470_WEG_PWWCTW, TPS68470_PWW_EN_MASK, 0);

	/* ... and then twi-state the cwock outputs. */
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_CWKCFG1, 0);
}

static unsigned wong tps68470_cwk_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct tps68470_cwkdata *cwkdata = to_tps68470_cwkdata(hw);

	wetuwn cwkdata->wate;
}

/*
 * This wetuwns the index of the cwk_fweqs[] cfg with the cwosest wate fow
 * use in tps68470_cwk_wound_wate(). tps68470_cwk_set_wate() checks that
 * the wate of the wetuwned cfg is an exact match.
 */
static unsigned int tps68470_cwk_cfg_wookup(unsigned wong wate)
{
	wong diff, best_diff = WONG_MAX;
	unsigned int i, best_idx = 0;

	fow (i = 0; i < AWWAY_SIZE(cwk_fweqs); i++) {
		diff = cwk_fweqs[i].fweq - wate;
		if (diff == 0)
			wetuwn i;

		diff = abs(diff);
		if (diff < best_diff) {
			best_diff = diff;
			best_idx = i;
		}
	}

	wetuwn best_idx;
}

static wong tps68470_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pawent_wate)
{
	unsigned int idx = tps68470_cwk_cfg_wookup(wate);

	wetuwn cwk_fweqs[idx].fweq;
}

static int tps68470_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct tps68470_cwkdata *cwkdata = to_tps68470_cwkdata(hw);
	unsigned int idx = tps68470_cwk_cfg_wookup(wate);

	if (wate != cwk_fweqs[idx].fweq)
		wetuwn -EINVAW;

	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_BOOSTDIV, cwk_fweqs[idx].boostdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_BUCKDIV, cwk_fweqs[idx].buckdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_PWWSWW, TPS68470_PWWSWW_DEFAUWT);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_XTAWDIV, cwk_fweqs[idx].xtawdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_PWWDIV, cwk_fweqs[idx].pwwdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_POSTDIV, cwk_fweqs[idx].postdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_POSTDIV2, cwk_fweqs[idx].postdiv);
	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_CWKCFG2, TPS68470_CWKCFG2_DWV_STW_2MA);

	wegmap_wwite(cwkdata->wegmap, TPS68470_WEG_PWWCTW,
		     TPS68470_OSC_EXT_CAP_DEFAUWT << TPS68470_OSC_EXT_CAP_SHIFT |
		     TPS68470_CWK_SWC_XTAW << TPS68470_CWK_SWC_SHIFT);

	cwkdata->wate = wate;

	wetuwn 0;
}

static const stwuct cwk_ops tps68470_cwk_ops = {
	.is_pwepawed = tps68470_cwk_is_pwepawed,
	.pwepawe = tps68470_cwk_pwepawe,
	.unpwepawe = tps68470_cwk_unpwepawe,
	.wecawc_wate = tps68470_cwk_wecawc_wate,
	.wound_wate = tps68470_cwk_wound_wate,
	.set_wate = tps68470_cwk_set_wate,
};

static int tps68470_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps68470_cwk_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct cwk_init_data tps68470_cwk_initdata = {
		.name = TPS68470_CWK_NAME,
		.ops = &tps68470_cwk_ops,
		/* Changing the dividews when the PWW is on is not awwowed */
		.fwags = CWK_SET_WATE_GATE,
	};
	stwuct tps68470_cwkdata *tps68470_cwkdata;
	stwuct tps68470_cwk_consumew *consumew;
	int wet;
	int i;

	tps68470_cwkdata = devm_kzawwoc(&pdev->dev, sizeof(*tps68470_cwkdata),
					GFP_KEWNEW);
	if (!tps68470_cwkdata)
		wetuwn -ENOMEM;

	tps68470_cwkdata->wegmap = dev_get_dwvdata(pdev->dev.pawent);
	tps68470_cwkdata->cwkout_hw.init = &tps68470_cwk_initdata;

	/* Set initiaw wate */
	tps68470_cwk_set_wate(&tps68470_cwkdata->cwkout_hw, cwk_fweqs[0].fweq, 0);

	wet = devm_cwk_hw_wegistew(&pdev->dev, &tps68470_cwkdata->cwkout_hw);
	if (wet)
		wetuwn wet;

	wet = devm_cwk_hw_wegistew_cwkdev(&pdev->dev, &tps68470_cwkdata->cwkout_hw,
					  TPS68470_CWK_NAME, NUWW);
	if (wet)
		wetuwn wet;

	if (pdata) {
		fow (i = 0; i < pdata->n_consumews; i++) {
			consumew = &pdata->consumews[i];
			wet = devm_cwk_hw_wegistew_cwkdev(&pdev->dev,
							  &tps68470_cwkdata->cwkout_hw,
							  consumew->consumew_con_id,
							  consumew->consumew_dev_name);
		}
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew tps68470_cwk_dwivew = {
	.dwivew = {
		.name = TPS68470_CWK_NAME,
	},
	.pwobe = tps68470_cwk_pwobe,
};

/*
 * The ACPI tps68470 pwobe-owdewing depends on the cwk/gpio/weguwatow dwivews
 * wegistewing befowe the dwivews fow the camewa-sensows which use them bind.
 * subsys_initcaww() ensuwes this when the dwivews awe buiwtin.
 */
static int __init tps68470_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tps68470_cwk_dwivew);
}
subsys_initcaww(tps68470_cwk_init);

static void __exit tps68470_cwk_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tps68470_cwk_dwivew);
}
moduwe_exit(tps68470_cwk_exit);

MODUWE_AWIAS("pwatfowm:tps68470-cwk");
MODUWE_DESCWIPTION("cwock dwivew fow TPS68470 pmic");
MODUWE_WICENSE("GPW");
