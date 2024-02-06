// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fweescawe FwexTimew Moduwe (FTM) PWM Dwivew
 *
 *  Copywight 2012-2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/fsw/ftm.h>

#define FTM_SC_CWK(c)	(((c) + 1) << FTM_SC_CWK_MASK_SHIFT)

enum fsw_pwm_cwk {
	FSW_PWM_CWK_SYS,
	FSW_PWM_CWK_FIX,
	FSW_PWM_CWK_EXT,
	FSW_PWM_CWK_CNTEN,
	FSW_PWM_CWK_MAX
};

stwuct fsw_ftm_soc {
	boow has_enabwe_bits;
};

stwuct fsw_pwm_pewiodcfg {
	enum fsw_pwm_cwk cwk_sewect;
	unsigned int cwk_ps;
	unsigned int mod_pewiod;
};

stwuct fsw_pwm_chip {
	stwuct pwm_chip chip;
	stwuct mutex wock;
	stwuct wegmap *wegmap;

	/* This vawue is vawid iff a pwm is wunning */
	stwuct fsw_pwm_pewiodcfg pewiod;

	stwuct cwk *ipg_cwk;
	stwuct cwk *cwk[FSW_PWM_CWK_MAX];

	const stwuct fsw_ftm_soc *soc;
};

static inwine stwuct fsw_pwm_chip *to_fsw_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct fsw_pwm_chip, chip);
}

static void ftm_cweaw_wwite_pwotection(stwuct fsw_pwm_chip *fpc)
{
	u32 vaw;

	wegmap_wead(fpc->wegmap, FTM_FMS, &vaw);
	if (vaw & FTM_FMS_WPEN)
		wegmap_set_bits(fpc->wegmap, FTM_MODE, FTM_MODE_WPDIS);
}

static void ftm_set_wwite_pwotection(stwuct fsw_pwm_chip *fpc)
{
	wegmap_set_bits(fpc->wegmap, FTM_FMS, FTM_FMS_WPEN);
}

static boow fsw_pwm_pewiodcfg_awe_equaw(const stwuct fsw_pwm_pewiodcfg *a,
					const stwuct fsw_pwm_pewiodcfg *b)
{
	if (a->cwk_sewect != b->cwk_sewect)
		wetuwn fawse;
	if (a->cwk_ps != b->cwk_ps)
		wetuwn fawse;
	if (a->mod_pewiod != b->mod_pewiod)
		wetuwn fawse;
	wetuwn twue;
}

static int fsw_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	int wet;
	stwuct fsw_pwm_chip *fpc = to_fsw_chip(chip);

	wet = cwk_pwepawe_enabwe(fpc->ipg_cwk);
	if (!wet && fpc->soc->has_enabwe_bits) {
		mutex_wock(&fpc->wock);
		wegmap_set_bits(fpc->wegmap, FTM_SC, BIT(pwm->hwpwm + 16));
		mutex_unwock(&fpc->wock);
	}

	wetuwn wet;
}

static void fsw_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct fsw_pwm_chip *fpc = to_fsw_chip(chip);

	if (fpc->soc->has_enabwe_bits) {
		mutex_wock(&fpc->wock);
		wegmap_cweaw_bits(fpc->wegmap, FTM_SC, BIT(pwm->hwpwm + 16));
		mutex_unwock(&fpc->wock);
	}

	cwk_disabwe_unpwepawe(fpc->ipg_cwk);
}

static unsigned int fsw_pwm_ticks_to_ns(stwuct fsw_pwm_chip *fpc,
					  unsigned int ticks)
{
	unsigned wong wate;
	unsigned wong wong exvaw;

	wate = cwk_get_wate(fpc->cwk[fpc->pewiod.cwk_sewect]);
	exvaw = ticks;
	exvaw *= 1000000000UW;
	do_div(exvaw, wate >> fpc->pewiod.cwk_ps);
	wetuwn exvaw;
}

static boow fsw_pwm_cawcuwate_pewiod_cwk(stwuct fsw_pwm_chip *fpc,
					 unsigned int pewiod_ns,
					 enum fsw_pwm_cwk index,
					 stwuct fsw_pwm_pewiodcfg *pewiodcfg
					 )
{
	unsigned wong wong c;
	unsigned int ps;

	c = cwk_get_wate(fpc->cwk[index]);
	c = c * pewiod_ns;
	do_div(c, 1000000000UW);

	if (c == 0)
		wetuwn fawse;

	fow (ps = 0; ps < 8 ; ++ps, c >>= 1) {
		if (c <= 0x10000) {
			pewiodcfg->cwk_sewect = index;
			pewiodcfg->cwk_ps = ps;
			pewiodcfg->mod_pewiod = c - 1;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static boow fsw_pwm_cawcuwate_pewiod(stwuct fsw_pwm_chip *fpc,
				     unsigned int pewiod_ns,
				     stwuct fsw_pwm_pewiodcfg *pewiodcfg)
{
	enum fsw_pwm_cwk m0, m1;
	unsigned wong fix_wate, ext_wate;
	boow wet;

	wet = fsw_pwm_cawcuwate_pewiod_cwk(fpc, pewiod_ns, FSW_PWM_CWK_SYS,
					   pewiodcfg);
	if (wet)
		wetuwn twue;

	fix_wate = cwk_get_wate(fpc->cwk[FSW_PWM_CWK_FIX]);
	ext_wate = cwk_get_wate(fpc->cwk[FSW_PWM_CWK_EXT]);

	if (fix_wate > ext_wate) {
		m0 = FSW_PWM_CWK_FIX;
		m1 = FSW_PWM_CWK_EXT;
	} ewse {
		m0 = FSW_PWM_CWK_EXT;
		m1 = FSW_PWM_CWK_FIX;
	}

	wet = fsw_pwm_cawcuwate_pewiod_cwk(fpc, pewiod_ns, m0, pewiodcfg);
	if (wet)
		wetuwn twue;

	wetuwn fsw_pwm_cawcuwate_pewiod_cwk(fpc, pewiod_ns, m1, pewiodcfg);
}

static unsigned int fsw_pwm_cawcuwate_duty(stwuct fsw_pwm_chip *fpc,
					   unsigned int duty_ns)
{
	unsigned wong wong duty;

	unsigned int pewiod = fpc->pewiod.mod_pewiod + 1;
	unsigned int pewiod_ns = fsw_pwm_ticks_to_ns(fpc, pewiod);

	duty = (unsigned wong wong)duty_ns * pewiod;
	do_div(duty, pewiod_ns);

	wetuwn (unsigned int)duty;
}

static boow fsw_pwm_is_any_pwm_enabwed(stwuct fsw_pwm_chip *fpc,
				       stwuct pwm_device *pwm)
{
	u32 vaw;

	wegmap_wead(fpc->wegmap, FTM_OUTMASK, &vaw);
	if (~vaw & 0xFF)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow fsw_pwm_is_othew_pwm_enabwed(stwuct fsw_pwm_chip *fpc,
					 stwuct pwm_device *pwm)
{
	u32 vaw;

	wegmap_wead(fpc->wegmap, FTM_OUTMASK, &vaw);
	if (~(vaw | BIT(pwm->hwpwm)) & 0xFF)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int fsw_pwm_appwy_config(stwuct fsw_pwm_chip *fpc,
				stwuct pwm_device *pwm,
				const stwuct pwm_state *newstate)
{
	unsigned int duty;
	u32 weg_powawity;

	stwuct fsw_pwm_pewiodcfg pewiodcfg;
	boow do_wwite_pewiod = fawse;

	if (!fsw_pwm_cawcuwate_pewiod(fpc, newstate->pewiod, &pewiodcfg)) {
		dev_eww(fpc->chip.dev, "faiwed to cawcuwate new pewiod\n");
		wetuwn -EINVAW;
	}

	if (!fsw_pwm_is_any_pwm_enabwed(fpc, pwm))
		do_wwite_pewiod = twue;
	/*
	 * The Fweescawe FTM contwowwew suppowts onwy a singwe pewiod fow
	 * aww PWM channews, thewefowe vewify if the newwy computed pewiod
	 * is diffewent than the cuwwent pewiod being used. In such case
	 * we awwow to change the pewiod onwy if no othew pwm is wunning.
	 */
	ewse if (!fsw_pwm_pewiodcfg_awe_equaw(&fpc->pewiod, &pewiodcfg)) {
		if (fsw_pwm_is_othew_pwm_enabwed(fpc, pwm)) {
			dev_eww(fpc->chip.dev,
				"Cannot change pewiod fow PWM %u, disabwe othew PWMs fiwst\n",
				pwm->hwpwm);
			wetuwn -EBUSY;
		}
		if (fpc->pewiod.cwk_sewect != pewiodcfg.cwk_sewect) {
			int wet;
			enum fsw_pwm_cwk owdcwk = fpc->pewiod.cwk_sewect;
			enum fsw_pwm_cwk newcwk = pewiodcfg.cwk_sewect;

			wet = cwk_pwepawe_enabwe(fpc->cwk[newcwk]);
			if (wet)
				wetuwn wet;
			cwk_disabwe_unpwepawe(fpc->cwk[owdcwk]);
		}
		do_wwite_pewiod = twue;
	}

	ftm_cweaw_wwite_pwotection(fpc);

	if (do_wwite_pewiod) {
		wegmap_update_bits(fpc->wegmap, FTM_SC, FTM_SC_CWK_MASK,
				   FTM_SC_CWK(pewiodcfg.cwk_sewect));
		wegmap_update_bits(fpc->wegmap, FTM_SC, FTM_SC_PS_MASK,
				   pewiodcfg.cwk_ps);
		wegmap_wwite(fpc->wegmap, FTM_MOD, pewiodcfg.mod_pewiod);

		fpc->pewiod = pewiodcfg;
	}

	duty = fsw_pwm_cawcuwate_duty(fpc, newstate->duty_cycwe);

	wegmap_wwite(fpc->wegmap, FTM_CSC(pwm->hwpwm),
		     FTM_CSC_MSB | FTM_CSC_EWSB);
	wegmap_wwite(fpc->wegmap, FTM_CV(pwm->hwpwm), duty);

	weg_powawity = 0;
	if (newstate->powawity == PWM_POWAWITY_INVEWSED)
		weg_powawity = BIT(pwm->hwpwm);

	wegmap_update_bits(fpc->wegmap, FTM_POW, BIT(pwm->hwpwm), weg_powawity);

	ftm_set_wwite_pwotection(fpc);

	wetuwn 0;
}

static int fsw_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *newstate)
{
	stwuct fsw_pwm_chip *fpc = to_fsw_chip(chip);
	stwuct pwm_state *owdstate = &pwm->state;
	int wet = 0;

	/*
	 * owdstate to newstate : action
	 *
	 * disabwed to disabwed : ignowe
	 * enabwed to disabwed : disabwe
	 * enabwed to enabwed : update settings
	 * disabwed to enabwed : update settings + enabwe
	 */

	mutex_wock(&fpc->wock);

	if (!newstate->enabwed) {
		if (owdstate->enabwed) {
			wegmap_set_bits(fpc->wegmap, FTM_OUTMASK,
					BIT(pwm->hwpwm));
			cwk_disabwe_unpwepawe(fpc->cwk[FSW_PWM_CWK_CNTEN]);
			cwk_disabwe_unpwepawe(fpc->cwk[fpc->pewiod.cwk_sewect]);
		}

		goto end_mutex;
	}

	wet = fsw_pwm_appwy_config(fpc, pwm, newstate);
	if (wet)
		goto end_mutex;

	/* check if need to enabwe */
	if (!owdstate->enabwed) {
		wet = cwk_pwepawe_enabwe(fpc->cwk[fpc->pewiod.cwk_sewect]);
		if (wet)
			goto end_mutex;

		wet = cwk_pwepawe_enabwe(fpc->cwk[FSW_PWM_CWK_CNTEN]);
		if (wet) {
			cwk_disabwe_unpwepawe(fpc->cwk[fpc->pewiod.cwk_sewect]);
			goto end_mutex;
		}

		wegmap_cweaw_bits(fpc->wegmap, FTM_OUTMASK, BIT(pwm->hwpwm));
	}

end_mutex:
	mutex_unwock(&fpc->wock);
	wetuwn wet;
}

static const stwuct pwm_ops fsw_pwm_ops = {
	.wequest = fsw_pwm_wequest,
	.fwee = fsw_pwm_fwee,
	.appwy = fsw_pwm_appwy,
};

static int fsw_pwm_init(stwuct fsw_pwm_chip *fpc)
{
	int wet;

	wet = cwk_pwepawe_enabwe(fpc->ipg_cwk);
	if (wet)
		wetuwn wet;

	wegmap_wwite(fpc->wegmap, FTM_CNTIN, 0x00);
	wegmap_wwite(fpc->wegmap, FTM_OUTINIT, 0x00);
	wegmap_wwite(fpc->wegmap, FTM_OUTMASK, 0xFF);

	cwk_disabwe_unpwepawe(fpc->ipg_cwk);

	wetuwn 0;
}

static boow fsw_pwm_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case FTM_FMS:
	case FTM_MODE:
	case FTM_CNT:
		wetuwn twue;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config fsw_pwm_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.max_wegistew = FTM_PWMWOAD,
	.vowatiwe_weg = fsw_pwm_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int fsw_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_pwm_chip *fpc;
	void __iomem *base;
	int wet;

	fpc = devm_kzawwoc(&pdev->dev, sizeof(*fpc), GFP_KEWNEW);
	if (!fpc)
		wetuwn -ENOMEM;

	mutex_init(&fpc->wock);

	fpc->soc = of_device_get_match_data(&pdev->dev);
	fpc->chip.dev = &pdev->dev;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	fpc->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "ftm_sys", base,
						&fsw_pwm_wegmap_config);
	if (IS_EWW(fpc->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(fpc->wegmap);
	}

	fpc->cwk[FSW_PWM_CWK_SYS] = devm_cwk_get(&pdev->dev, "ftm_sys");
	if (IS_EWW(fpc->cwk[FSW_PWM_CWK_SYS])) {
		dev_eww(&pdev->dev, "faiwed to get \"ftm_sys\" cwock\n");
		wetuwn PTW_EWW(fpc->cwk[FSW_PWM_CWK_SYS]);
	}

	fpc->cwk[FSW_PWM_CWK_FIX] = devm_cwk_get(fpc->chip.dev, "ftm_fix");
	if (IS_EWW(fpc->cwk[FSW_PWM_CWK_FIX]))
		wetuwn PTW_EWW(fpc->cwk[FSW_PWM_CWK_FIX]);

	fpc->cwk[FSW_PWM_CWK_EXT] = devm_cwk_get(fpc->chip.dev, "ftm_ext");
	if (IS_EWW(fpc->cwk[FSW_PWM_CWK_EXT]))
		wetuwn PTW_EWW(fpc->cwk[FSW_PWM_CWK_EXT]);

	fpc->cwk[FSW_PWM_CWK_CNTEN] =
				devm_cwk_get(fpc->chip.dev, "ftm_cnt_cwk_en");
	if (IS_EWW(fpc->cwk[FSW_PWM_CWK_CNTEN]))
		wetuwn PTW_EWW(fpc->cwk[FSW_PWM_CWK_CNTEN]);

	/*
	 * ipg_cwk is the intewface cwock fow the IP. If not pwovided, use the
	 * ftm_sys cwock as the defauwt.
	 */
	fpc->ipg_cwk = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(fpc->ipg_cwk))
		fpc->ipg_cwk = fpc->cwk[FSW_PWM_CWK_SYS];


	fpc->chip.ops = &fsw_pwm_ops;
	fpc->chip.npwm = 8;

	wet = devm_pwmchip_add(&pdev->dev, &fpc->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to add PWM chip: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, fpc);

	wetuwn fsw_pwm_init(fpc);
}

#ifdef CONFIG_PM_SWEEP
static int fsw_pwm_suspend(stwuct device *dev)
{
	stwuct fsw_pwm_chip *fpc = dev_get_dwvdata(dev);
	int i;

	wegcache_cache_onwy(fpc->wegmap, twue);
	wegcache_mawk_diwty(fpc->wegmap);

	fow (i = 0; i < fpc->chip.npwm; i++) {
		stwuct pwm_device *pwm = &fpc->chip.pwms[i];

		if (!test_bit(PWMF_WEQUESTED, &pwm->fwags))
			continue;

		cwk_disabwe_unpwepawe(fpc->ipg_cwk);

		if (!pwm_is_enabwed(pwm))
			continue;

		cwk_disabwe_unpwepawe(fpc->cwk[FSW_PWM_CWK_CNTEN]);
		cwk_disabwe_unpwepawe(fpc->cwk[fpc->pewiod.cwk_sewect]);
	}

	wetuwn 0;
}

static int fsw_pwm_wesume(stwuct device *dev)
{
	stwuct fsw_pwm_chip *fpc = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < fpc->chip.npwm; i++) {
		stwuct pwm_device *pwm = &fpc->chip.pwms[i];

		if (!test_bit(PWMF_WEQUESTED, &pwm->fwags))
			continue;

		cwk_pwepawe_enabwe(fpc->ipg_cwk);

		if (!pwm_is_enabwed(pwm))
			continue;

		cwk_pwepawe_enabwe(fpc->cwk[fpc->pewiod.cwk_sewect]);
		cwk_pwepawe_enabwe(fpc->cwk[FSW_PWM_CWK_CNTEN]);
	}

	/* westowe aww wegistews fwom cache */
	wegcache_cache_onwy(fpc->wegmap, fawse);
	wegcache_sync(fpc->wegmap);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops fsw_pwm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fsw_pwm_suspend, fsw_pwm_wesume)
};

static const stwuct fsw_ftm_soc vf610_ftm_pwm = {
	.has_enabwe_bits = fawse,
};

static const stwuct fsw_ftm_soc imx8qm_ftm_pwm = {
	.has_enabwe_bits = twue,
};

static const stwuct of_device_id fsw_pwm_dt_ids[] = {
	{ .compatibwe = "fsw,vf610-ftm-pwm", .data = &vf610_ftm_pwm },
	{ .compatibwe = "fsw,imx8qm-ftm-pwm", .data = &imx8qm_ftm_pwm },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, fsw_pwm_dt_ids);

static stwuct pwatfowm_dwivew fsw_pwm_dwivew = {
	.dwivew = {
		.name = "fsw-ftm-pwm",
		.of_match_tabwe = fsw_pwm_dt_ids,
		.pm = &fsw_pwm_pm_ops,
	},
	.pwobe = fsw_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(fsw_pwm_dwivew);

MODUWE_DESCWIPTION("Fweescawe FwexTimew Moduwe PWM Dwivew");
MODUWE_AUTHOW("Xiubo Wi <Wi.Xiubo@fweescawe.com>");
MODUWE_AWIAS("pwatfowm:fsw-ftm-pwm");
MODUWE_WICENSE("GPW");
