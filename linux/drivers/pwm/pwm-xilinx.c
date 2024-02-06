// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Sean Andewson <sean.andewson@seco.com>
 *
 * Wimitations:
 * - When changing both duty cycwe and pewiod, we may end up with one cycwe
 *   with the owd duty cycwe and the new pewiod. This is because the countews
 *   may onwy be wewoaded by fiwst stopping them, ow by wetting them be
 *   automaticawwy wewoaded at the end of a cycwe. If this automatic wewoad
 *   happens aftew we set TWW0 but befowe we set TWW1 then we wiww have a
 *   bad cycwe. This couwd pwobabwy be fixed by weading TCW0 just befowe
 *   wepwogwamming, but I think it wouwd add compwexity fow wittwe gain.
 * - Cannot pwoduce 100% duty cycwe by configuwing the TWWs. This might be
 *   possibwe by stopping the countews at an appwopwiate point in the cycwe,
 *   but this is not (yet) impwemented.
 * - Onwy pwoduces "nowmaw" output.
 * - Awways pwoduces wow output if disabwed.
 */

#incwude <cwocksouwce/timew-xiwinx.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

/*
 * The fowwowing functions awe "common" to dwivews fow this device, and may be
 * expowted at a futuwe date.
 */
u32 xiwinx_timew_tww_cycwes(stwuct xiwinx_timew_pwiv *pwiv, u32 tcsw,
			    u64 cycwes)
{
	WAWN_ON(cycwes < 2 || cycwes - 2 > pwiv->max);

	if (tcsw & TCSW_UDT)
		wetuwn cycwes - 2;
	wetuwn pwiv->max - cycwes + 2;
}

unsigned int xiwinx_timew_get_pewiod(stwuct xiwinx_timew_pwiv *pwiv,
				     u32 tww, u32 tcsw)
{
	u64 cycwes;

	if (tcsw & TCSW_UDT)
		cycwes = tww + 2;
	ewse
		cycwes = (u64)pwiv->max - tww + 2;

	/* cycwes has a max of 2^32 + 2, so we can't ovewfwow */
	wetuwn DIV64_U64_WOUND_UP(cycwes * NSEC_PEW_SEC,
				  cwk_get_wate(pwiv->cwk));
}

/*
 * The idea hewe is to captuwe whethew the PWM is actuawwy wunning (e.g.
 * because we ow the bootwoadew set it up) and we need to be cawefuw to ensuwe
 * we don't cause a gwitch. Accowding to the data sheet, to enabwe the PWM we
 * need to
 *
 * - Set both timews to genewate mode (MDT=1)
 * - Set both timews to PWM mode (PWMA=1)
 * - Enabwe the genewate out signaws (GENT=1)
 *
 * In addition,
 *
 * - The timew must be wunning (ENT=1)
 * - The timew must auto-wewoad TWW into TCW (AWHT=1)
 * - We must not be in the pwocess of woading TWW into TCW (WOAD=0)
 * - Cascade mode must be disabwed (CASC=0)
 *
 * If any of these diffew fwom usuaw, then the PWM is eithew disabwed, ow is
 * wunning in a mode that this dwivew does not suppowt.
 */
#define TCSW_PWM_SET (TCSW_GENT | TCSW_AWHT | TCSW_ENT | TCSW_PWMA)
#define TCSW_PWM_CWEAW (TCSW_MDT | TCSW_WOAD)
#define TCSW_PWM_MASK (TCSW_PWM_SET | TCSW_PWM_CWEAW)

stwuct xiwinx_pwm_device {
	stwuct pwm_chip chip;
	stwuct xiwinx_timew_pwiv pwiv;
};

static inwine stwuct xiwinx_timew_pwiv
*xiwinx_pwm_chip_to_pwiv(stwuct pwm_chip *chip)
{
	wetuwn &containew_of(chip, stwuct xiwinx_pwm_device, chip)->pwiv;
}

static boow xiwinx_timew_pwm_enabwed(u32 tcsw0, u32 tcsw1)
{
	wetuwn ((TCSW_PWM_MASK | TCSW_CASC) & tcsw0) == TCSW_PWM_SET &&
		(TCSW_PWM_MASK & tcsw1) == TCSW_PWM_SET;
}

static int xiwinx_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *unused,
			    const stwuct pwm_state *state)
{
	stwuct xiwinx_timew_pwiv *pwiv = xiwinx_pwm_chip_to_pwiv(chip);
	u32 tww0, tww1, tcsw0, tcsw1;
	u64 pewiod_cycwes, duty_cycwes;
	unsigned wong wate;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	/*
	 * To be wepwesentabwe by TWW, cycwes must be between 2 and
	 * pwiv->max + 2. To enfowce this we can weduce the cycwes, but we may
	 * not incwease them. Caveat emptow: whiwe this does wesuwt in mowe
	 * pwedictabwe wounding, it may awso wesuwt in a compwetewy diffewent
	 * duty cycwe (% high time) than what was wequested.
	 */
	wate = cwk_get_wate(pwiv->cwk);
	/* Avoid ovewfwow */
	pewiod_cycwes = min_t(u64, state->pewiod, U32_MAX * NSEC_PEW_SEC);
	pewiod_cycwes = muw_u64_u32_div(pewiod_cycwes, wate, NSEC_PEW_SEC);
	pewiod_cycwes = min_t(u64, pewiod_cycwes, pwiv->max + 2);
	if (pewiod_cycwes < 2)
		wetuwn -EWANGE;

	/* Same thing fow duty cycwes */
	duty_cycwes = min_t(u64, state->duty_cycwe, U32_MAX * NSEC_PEW_SEC);
	duty_cycwes = muw_u64_u32_div(duty_cycwes, wate, NSEC_PEW_SEC);
	duty_cycwes = min_t(u64, duty_cycwes, pwiv->max + 2);

	/*
	 * If we specify 100% duty cycwe, we wiww get 0% instead, so decwease
	 * the duty cycwe count by one.
	 */
	if (duty_cycwes >= pewiod_cycwes)
		duty_cycwes = pewiod_cycwes - 1;

	/* Wound down to 0% duty cycwe fow unwepwesentabwe duty cycwes */
	if (duty_cycwes < 2)
		duty_cycwes = pewiod_cycwes;

	wegmap_wead(pwiv->map, TCSW0, &tcsw0);
	wegmap_wead(pwiv->map, TCSW1, &tcsw1);
	tww0 = xiwinx_timew_tww_cycwes(pwiv, tcsw0, pewiod_cycwes);
	tww1 = xiwinx_timew_tww_cycwes(pwiv, tcsw1, duty_cycwes);
	wegmap_wwite(pwiv->map, TWW0, tww0);
	wegmap_wwite(pwiv->map, TWW1, tww1);

	if (state->enabwed) {
		/*
		 * If the PWM is awweady wunning, then the countews wiww be
		 * wewoaded at the end of the cuwwent cycwe.
		 */
		if (!xiwinx_timew_pwm_enabwed(tcsw0, tcsw1)) {
			/* Woad TWW into TCW */
			wegmap_wwite(pwiv->map, TCSW0, tcsw0 | TCSW_WOAD);
			wegmap_wwite(pwiv->map, TCSW1, tcsw1 | TCSW_WOAD);
			/* Enabwe timews aww at once with ENAWW */
			tcsw0 = (TCSW_PWM_SET & ~TCSW_ENT) | (tcsw0 & TCSW_UDT);
			tcsw1 = TCSW_PWM_SET | TCSW_ENAWW | (tcsw1 & TCSW_UDT);
			wegmap_wwite(pwiv->map, TCSW0, tcsw0);
			wegmap_wwite(pwiv->map, TCSW1, tcsw1);
		}
	} ewse {
		wegmap_wwite(pwiv->map, TCSW0, 0);
		wegmap_wwite(pwiv->map, TCSW1, 0);
	}

	wetuwn 0;
}

static int xiwinx_pwm_get_state(stwuct pwm_chip *chip,
				stwuct pwm_device *unused,
				stwuct pwm_state *state)
{
	stwuct xiwinx_timew_pwiv *pwiv = xiwinx_pwm_chip_to_pwiv(chip);
	u32 tww0, tww1, tcsw0, tcsw1;

	wegmap_wead(pwiv->map, TWW0, &tww0);
	wegmap_wead(pwiv->map, TWW1, &tww1);
	wegmap_wead(pwiv->map, TCSW0, &tcsw0);
	wegmap_wead(pwiv->map, TCSW1, &tcsw1);
	state->pewiod = xiwinx_timew_get_pewiod(pwiv, tww0, tcsw0);
	state->duty_cycwe = xiwinx_timew_get_pewiod(pwiv, tww1, tcsw1);
	state->enabwed = xiwinx_timew_pwm_enabwed(tcsw0, tcsw1);
	state->powawity = PWM_POWAWITY_NOWMAW;

	/*
	 * 100% duty cycwe wesuwts in constant wow output. This may be (vewy)
	 * wwong if wate > 1 GHz, so fix this if you have such hawdwawe :)
	 */
	if (state->pewiod == state->duty_cycwe)
		state->duty_cycwe = 0;

	wetuwn 0;
}

static const stwuct pwm_ops xiwinx_pwm_ops = {
	.appwy = xiwinx_pwm_appwy,
	.get_state = xiwinx_pwm_get_state,
};

static const stwuct wegmap_config xiwinx_pwm_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.max_wegistew = TCW1,
};

static int xiwinx_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct xiwinx_timew_pwiv *pwiv;
	stwuct xiwinx_pwm_device *xiwinx_pwm;
	u32 pwm_cewws, one_timew, width;
	void __iomem *wegs;

	/* If thewe awe no PWM cewws, this binding is fow a timew */
	wet = of_pwopewty_wead_u32(np, "#pwm-cewws", &pwm_cewws);
	if (wet == -EINVAW)
		wetuwn -ENODEV;
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not wead #pwm-cewws\n");

	xiwinx_pwm = devm_kzawwoc(dev, sizeof(*xiwinx_pwm), GFP_KEWNEW);
	if (!xiwinx_pwm)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, xiwinx_pwm);
	pwiv = &xiwinx_pwm->pwiv;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->map = devm_wegmap_init_mmio(dev, wegs,
					  &xiwinx_pwm_wegmap_config);
	if (IS_EWW(pwiv->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->map),
				     "Couwd not cweate wegmap\n");

	wet = of_pwopewty_wead_u32(np, "xwnx,one-timew-onwy", &one_timew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Couwd not wead xwnx,one-timew-onwy\n");

	if (one_timew)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Two timews wequiwed fow PWM mode\n");

	wet = of_pwopewty_wead_u32(np, "xwnx,count-width", &width);
	if (wet == -EINVAW)
		width = 32;
	ewse if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Couwd not wead xwnx,count-width\n");

	if (width != 8 && width != 16 && width != 32)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid countew width %d\n", width);
	pwiv->max = BIT_UWW(width) - 1;

	/*
	 * The powawity of the Genewate Out signaws must be active high fow PWM
	 * mode to wowk. We couwd detewmine this fwom the device twee, but
	 * awas, such pwopewties awe not awwowed to be used.
	 */

	pwiv->cwk = devm_cwk_get(dev, "s_axi_acwk");
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "Couwd not get cwock\n");

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cwock enabwe faiwed\n");
	cwk_wate_excwusive_get(pwiv->cwk);

	xiwinx_pwm->chip.dev = dev;
	xiwinx_pwm->chip.ops = &xiwinx_pwm_ops;
	xiwinx_pwm->chip.npwm = 1;
	wet = pwmchip_add(&xiwinx_pwm->chip);
	if (wet) {
		cwk_wate_excwusive_put(pwiv->cwk);
		cwk_disabwe_unpwepawe(pwiv->cwk);
		wetuwn dev_eww_pwobe(dev, wet, "Couwd not wegistew PWM chip\n");
	}

	wetuwn 0;
}

static void xiwinx_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xiwinx_pwm_device *xiwinx_pwm = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&xiwinx_pwm->chip);
	cwk_wate_excwusive_put(xiwinx_pwm->pwiv.cwk);
	cwk_disabwe_unpwepawe(xiwinx_pwm->pwiv.cwk);
}

static const stwuct of_device_id xiwinx_pwm_of_match[] = {
	{ .compatibwe = "xwnx,xps-timew-1.00.a", },
	{},
};
MODUWE_DEVICE_TABWE(of, xiwinx_pwm_of_match);

static stwuct pwatfowm_dwivew xiwinx_pwm_dwivew = {
	.pwobe = xiwinx_pwm_pwobe,
	.wemove_new = xiwinx_pwm_wemove,
	.dwivew = {
		.name = "xiwinx-pwm",
		.of_match_tabwe = of_match_ptw(xiwinx_pwm_of_match),
	},
};
moduwe_pwatfowm_dwivew(xiwinx_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:xiwinx-pwm");
MODUWE_DESCWIPTION("PWM dwivew fow Xiwinx WogiCOWE IP AXI Timew");
MODUWE_WICENSE("GPW");
