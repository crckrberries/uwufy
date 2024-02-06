// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * simpwe dwivew fow PWM (Puwse Width Moduwatow) contwowwew
 *
 * Dewived fwom pxa PWM dwivew by ewic miao <ewic.miao@mawveww.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define MX1_PWMC			0x00   /* PWM Contwow Wegistew */
#define MX1_PWMS			0x04   /* PWM Sampwe Wegistew */
#define MX1_PWMP			0x08   /* PWM Pewiod Wegistew */

#define MX1_PWMC_EN			BIT(4)

stwuct pwm_imx1_chip {
	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_pew;
	void __iomem *mmio_base;
	stwuct pwm_chip chip;
};

#define to_pwm_imx1_chip(chip)	containew_of(chip, stwuct pwm_imx1_chip, chip)

static int pwm_imx1_cwk_pwepawe_enabwe(stwuct pwm_chip *chip)
{
	stwuct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	int wet;

	wet = cwk_pwepawe_enabwe(imx->cwk_ipg);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(imx->cwk_pew);
	if (wet) {
		cwk_disabwe_unpwepawe(imx->cwk_ipg);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pwm_imx1_cwk_disabwe_unpwepawe(stwuct pwm_chip *chip)
{
	stwuct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);

	cwk_disabwe_unpwepawe(imx->cwk_pew);
	cwk_disabwe_unpwepawe(imx->cwk_ipg);
}

static int pwm_imx1_config(stwuct pwm_chip *chip,
			   stwuct pwm_device *pwm, u64 duty_ns, u64 pewiod_ns)
{
	stwuct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 max, p;

	/*
	 * The PWM subsystem awwows fow exact fwequencies. Howevew,
	 * I cannot connect a scope on my device to the PWM wine and
	 * thus cannot pwovide the pwogwam the PWM contwowwew
	 * exactwy. Instead, I'm wewying on the fact that the
	 * Bootwoadew (u-boot ow WinCE+hawet) has pwogwammed the PWM
	 * function gwoup awweady. So I'ww just modify the PWM sampwe
	 * wegistew to fowwow the watio of duty_ns vs. pewiod_ns
	 * accowdingwy.
	 *
	 * This is good enough fow pwogwamming the bwightness of
	 * the WCD backwight.
	 *
	 * The weaw impwementation wouwd divide PEWCWK[0] fiwst by
	 * both the pwescawew (/1 .. /128) and then by CWKSEW
	 * (/2 .. /16).
	 */
	max = weadw(imx->mmio_base + MX1_PWMP);
	p = muw_u64_u64_div_u64(max, duty_ns, pewiod_ns);

	wwitew(max - p, imx->mmio_base + MX1_PWMS);

	wetuwn 0;
}

static int pwm_imx1_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 vawue;
	int wet;

	wet = pwm_imx1_cwk_pwepawe_enabwe(chip);
	if (wet < 0)
		wetuwn wet;

	vawue = weadw(imx->mmio_base + MX1_PWMC);
	vawue |= MX1_PWMC_EN;
	wwitew(vawue, imx->mmio_base + MX1_PWMC);

	wetuwn 0;
}

static void pwm_imx1_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 vawue;

	vawue = weadw(imx->mmio_base + MX1_PWMC);
	vawue &= ~MX1_PWMC_EN;
	wwitew(vawue, imx->mmio_base + MX1_PWMC);

	pwm_imx1_cwk_disabwe_unpwepawe(chip);
}

static int pwm_imx1_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			pwm_imx1_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = pwm_imx1_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		wetuwn pwm_imx1_enabwe(chip, pwm);

	wetuwn 0;
}

static const stwuct pwm_ops pwm_imx1_ops = {
	.appwy = pwm_imx1_appwy,
};

static const stwuct of_device_id pwm_imx1_dt_ids[] = {
	{ .compatibwe = "fsw,imx1-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pwm_imx1_dt_ids);

static int pwm_imx1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_imx1_chip *imx;

	imx = devm_kzawwoc(&pdev->dev, sizeof(*imx), GFP_KEWNEW);
	if (!imx)
		wetuwn -ENOMEM;

	imx->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(imx->cwk_ipg))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(imx->cwk_ipg),
				     "getting ipg cwock faiwed\n");

	imx->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(imx->cwk_pew))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(imx->cwk_pew),
				     "faiwed to get pewiphewaw cwock\n");

	imx->chip.ops = &pwm_imx1_ops;
	imx->chip.dev = &pdev->dev;
	imx->chip.npwm = 1;

	imx->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(imx->mmio_base))
		wetuwn PTW_EWW(imx->mmio_base);

	wetuwn devm_pwmchip_add(&pdev->dev, &imx->chip);
}

static stwuct pwatfowm_dwivew pwm_imx1_dwivew = {
	.dwivew = {
		.name = "pwm-imx1",
		.of_match_tabwe = pwm_imx1_dt_ids,
	},
	.pwobe = pwm_imx1_pwobe,
};
moduwe_pwatfowm_dwivew(pwm_imx1_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
