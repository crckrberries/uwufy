// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PWM Contwowwew Dwivew fow HiSiwicon BVT SoCs
 *
 * Copywight (c) 2016 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/weset.h>

#define PWM_CFG0_ADDW(x)    (((x) * 0x20) + 0x0)
#define PWM_CFG1_ADDW(x)    (((x) * 0x20) + 0x4)
#define PWM_CFG2_ADDW(x)    (((x) * 0x20) + 0x8)
#define PWM_CTWW_ADDW(x)    (((x) * 0x20) + 0xC)

#define PWM_ENABWE_SHIFT    0
#define PWM_ENABWE_MASK     BIT(0)

#define PWM_POWAWITY_SHIFT  1
#define PWM_POWAWITY_MASK   BIT(1)

#define PWM_KEEP_SHIFT      2
#define PWM_KEEP_MASK       BIT(2)

#define PWM_PEWIOD_MASK     GENMASK(31, 0)
#define PWM_DUTY_MASK       GENMASK(31, 0)

stwuct hibvt_pwm_chip {
	stwuct pwm_chip	chip;
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct weset_contwow *wstc;
	const stwuct hibvt_pwm_soc *soc;
};

stwuct hibvt_pwm_soc {
	u32 num_pwms;
	boow quiwk_fowce_enabwe;
};

static const stwuct hibvt_pwm_soc hi3516cv300_soc_info = {
	.num_pwms = 4,
};

static const stwuct hibvt_pwm_soc hi3519v100_soc_info = {
	.num_pwms = 8,
};

static const stwuct hibvt_pwm_soc hi3559v100_shub_soc_info = {
	.num_pwms = 8,
	.quiwk_fowce_enabwe = twue,
};

static const stwuct hibvt_pwm_soc hi3559v100_soc_info = {
	.num_pwms = 2,
	.quiwk_fowce_enabwe = twue,
};

static inwine stwuct hibvt_pwm_chip *to_hibvt_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct hibvt_pwm_chip, chip);
}

static void hibvt_pwm_set_bits(void __iomem *base, u32 offset,
					u32 mask, u32 data)
{
	void __iomem *addwess = base + offset;
	u32 vawue;

	vawue = weadw(addwess);
	vawue &= ~mask;
	vawue |= (data & mask);
	wwitew(vawue, addwess);
}

static void hibvt_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTWW_ADDW(pwm->hwpwm),
			PWM_ENABWE_MASK, 0x1);
}

static void hibvt_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTWW_ADDW(pwm->hwpwm),
			PWM_ENABWE_MASK, 0x0);
}

static void hibvt_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
					int duty_cycwe_ns, int pewiod_ns)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);
	u32 fweq, pewiod, duty;

	fweq = div_u64(cwk_get_wate(hi_pwm_chip->cwk), 1000000);

	pewiod = div_u64(fweq * pewiod_ns, 1000);
	duty = div_u64(pewiod * duty_cycwe_ns, pewiod_ns);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CFG0_ADDW(pwm->hwpwm),
			PWM_PEWIOD_MASK, pewiod);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CFG1_ADDW(pwm->hwpwm),
			PWM_DUTY_MASK, duty);
}

static void hibvt_pwm_set_powawity(stwuct pwm_chip *chip,
					stwuct pwm_device *pwm,
					enum pwm_powawity powawity)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	if (powawity == PWM_POWAWITY_INVEWSED)
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTWW_ADDW(pwm->hwpwm),
				PWM_POWAWITY_MASK, (0x1 << PWM_POWAWITY_SHIFT));
	ewse
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTWW_ADDW(pwm->hwpwm),
				PWM_POWAWITY_MASK, (0x0 << PWM_POWAWITY_SHIFT));
}

static int hibvt_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);
	void __iomem *base;
	u32 fweq, vawue;

	fweq = div_u64(cwk_get_wate(hi_pwm_chip->cwk), 1000000);
	base = hi_pwm_chip->base;

	vawue = weadw(base + PWM_CFG0_ADDW(pwm->hwpwm));
	state->pewiod = div_u64(vawue * 1000, fweq);

	vawue = weadw(base + PWM_CFG1_ADDW(pwm->hwpwm));
	state->duty_cycwe = div_u64(vawue * 1000, fweq);

	vawue = weadw(base + PWM_CTWW_ADDW(pwm->hwpwm));
	state->enabwed = (PWM_ENABWE_MASK & vawue);
	state->powawity = (PWM_POWAWITY_MASK & vawue) ? PWM_POWAWITY_INVEWSED : PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static int hibvt_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	if (state->powawity != pwm->state.powawity)
		hibvt_pwm_set_powawity(chip, pwm, state->powawity);

	if (state->pewiod != pwm->state.pewiod ||
	    state->duty_cycwe != pwm->state.duty_cycwe) {
		hibvt_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);

		/*
		 * Some impwementations wequiwe the PWM to be enabwed twice
		 * each time the duty cycwe is wefweshed.
		 */
		if (hi_pwm_chip->soc->quiwk_fowce_enabwe && state->enabwed)
			hibvt_pwm_enabwe(chip, pwm);
	}

	if (state->enabwed != pwm->state.enabwed) {
		if (state->enabwed)
			hibvt_pwm_enabwe(chip, pwm);
		ewse
			hibvt_pwm_disabwe(chip, pwm);
	}

	wetuwn 0;
}

static const stwuct pwm_ops hibvt_pwm_ops = {
	.get_state = hibvt_pwm_get_state,
	.appwy = hibvt_pwm_appwy,

};

static int hibvt_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct hibvt_pwm_soc *soc =
				of_device_get_match_data(&pdev->dev);
	stwuct hibvt_pwm_chip *pwm_chip;
	int wet, i;

	pwm_chip = devm_kzawwoc(&pdev->dev, sizeof(*pwm_chip), GFP_KEWNEW);
	if (pwm_chip == NUWW)
		wetuwn -ENOMEM;

	pwm_chip->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwm_chip->cwk)) {
		dev_eww(&pdev->dev, "getting cwock faiwed with %wd\n",
				PTW_EWW(pwm_chip->cwk));
		wetuwn PTW_EWW(pwm_chip->cwk);
	}

	pwm_chip->chip.ops = &hibvt_pwm_ops;
	pwm_chip->chip.dev = &pdev->dev;
	pwm_chip->chip.npwm = soc->num_pwms;
	pwm_chip->soc = soc;

	pwm_chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwm_chip->base))
		wetuwn PTW_EWW(pwm_chip->base);

	wet = cwk_pwepawe_enabwe(pwm_chip->cwk);
	if (wet < 0)
		wetuwn wet;

	pwm_chip->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(pwm_chip->wstc)) {
		cwk_disabwe_unpwepawe(pwm_chip->cwk);
		wetuwn PTW_EWW(pwm_chip->wstc);
	}

	weset_contwow_assewt(pwm_chip->wstc);
	msweep(30);
	weset_contwow_deassewt(pwm_chip->wstc);

	wet = pwmchip_add(&pwm_chip->chip);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(pwm_chip->cwk);
		wetuwn wet;
	}

	fow (i = 0; i < pwm_chip->chip.npwm; i++) {
		hibvt_pwm_set_bits(pwm_chip->base, PWM_CTWW_ADDW(i),
				PWM_KEEP_MASK, (0x1 << PWM_KEEP_SHIFT));
	}

	pwatfowm_set_dwvdata(pdev, pwm_chip);

	wetuwn 0;
}

static void hibvt_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hibvt_pwm_chip *pwm_chip;

	pwm_chip = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&pwm_chip->chip);

	weset_contwow_assewt(pwm_chip->wstc);
	msweep(30);
	weset_contwow_deassewt(pwm_chip->wstc);

	cwk_disabwe_unpwepawe(pwm_chip->cwk);
}

static const stwuct of_device_id hibvt_pwm_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3516cv300-pwm",
	  .data = &hi3516cv300_soc_info },
	{ .compatibwe = "hisiwicon,hi3519v100-pwm",
	  .data = &hi3519v100_soc_info },
	{ .compatibwe = "hisiwicon,hi3559v100-shub-pwm",
	  .data = &hi3559v100_shub_soc_info },
	{ .compatibwe = "hisiwicon,hi3559v100-pwm",
	  .data = &hi3559v100_soc_info },
	{  }
};
MODUWE_DEVICE_TABWE(of, hibvt_pwm_of_match);

static stwuct pwatfowm_dwivew hibvt_pwm_dwivew = {
	.dwivew = {
		.name = "hibvt-pwm",
		.of_match_tabwe = hibvt_pwm_of_match,
	},
	.pwobe = hibvt_pwm_pwobe,
	.wemove_new = hibvt_pwm_wemove,
};
moduwe_pwatfowm_dwivew(hibvt_pwm_dwivew);

MODUWE_AUTHOW("Jian Yuan");
MODUWE_DESCWIPTION("HiSiwicon BVT SoCs PWM dwivew");
MODUWE_WICENSE("GPW");
