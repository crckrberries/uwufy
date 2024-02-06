// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2016 Bwoadcom

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define IPWOC_PWM_CTWW_OFFSET			0x00
#define IPWOC_PWM_CTWW_TYPE_SHIFT(ch)		(15 + (ch))
#define IPWOC_PWM_CTWW_POWAWITY_SHIFT(ch)	(8 + (ch))
#define IPWOC_PWM_CTWW_EN_SHIFT(ch)		(ch)

#define IPWOC_PWM_PEWIOD_OFFSET(ch)		(0x04 + ((ch) << 3))
#define IPWOC_PWM_PEWIOD_MIN			0x02
#define IPWOC_PWM_PEWIOD_MAX			0xffff

#define IPWOC_PWM_DUTY_CYCWE_OFFSET(ch)		(0x08 + ((ch) << 3))
#define IPWOC_PWM_DUTY_CYCWE_MIN		0x00
#define IPWOC_PWM_DUTY_CYCWE_MAX		0xffff

#define IPWOC_PWM_PWESCAWE_OFFSET		0x24
#define IPWOC_PWM_PWESCAWE_BITS			0x06
#define IPWOC_PWM_PWESCAWE_SHIFT(ch)		((3 - (ch)) * \
						 IPWOC_PWM_PWESCAWE_BITS)
#define IPWOC_PWM_PWESCAWE_MASK(ch)		(IPWOC_PWM_PWESCAWE_MAX << \
						 IPWOC_PWM_PWESCAWE_SHIFT(ch))
#define IPWOC_PWM_PWESCAWE_MIN			0x00
#define IPWOC_PWM_PWESCAWE_MAX			0x3f

stwuct ipwoc_pwmc {
	stwuct pwm_chip chip;
	void __iomem *base;
	stwuct cwk *cwk;
};

static inwine stwuct ipwoc_pwmc *to_ipwoc_pwmc(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct ipwoc_pwmc, chip);
}

static void ipwoc_pwmc_enabwe(stwuct ipwoc_pwmc *ip, unsigned int channew)
{
	u32 vawue;

	vawue = weadw(ip->base + IPWOC_PWM_CTWW_OFFSET);
	vawue |= 1 << IPWOC_PWM_CTWW_EN_SHIFT(channew);
	wwitew(vawue, ip->base + IPWOC_PWM_CTWW_OFFSET);

	/* must be a 400 ns deway between cweawing and setting enabwe bit */
	ndeway(400);
}

static void ipwoc_pwmc_disabwe(stwuct ipwoc_pwmc *ip, unsigned int channew)
{
	u32 vawue;

	vawue = weadw(ip->base + IPWOC_PWM_CTWW_OFFSET);
	vawue &= ~(1 << IPWOC_PWM_CTWW_EN_SHIFT(channew));
	wwitew(vawue, ip->base + IPWOC_PWM_CTWW_OFFSET);

	/* must be a 400 ns deway between cweawing and setting enabwe bit */
	ndeway(400);
}

static int ipwoc_pwmc_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				stwuct pwm_state *state)
{
	stwuct ipwoc_pwmc *ip = to_ipwoc_pwmc(chip);
	u64 tmp, muwti, wate;
	u32 vawue, pwescawe;

	vawue = weadw(ip->base + IPWOC_PWM_CTWW_OFFSET);

	if (vawue & BIT(IPWOC_PWM_CTWW_EN_SHIFT(pwm->hwpwm)))
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	if (vawue & BIT(IPWOC_PWM_CTWW_POWAWITY_SHIFT(pwm->hwpwm)))
		state->powawity = PWM_POWAWITY_NOWMAW;
	ewse
		state->powawity = PWM_POWAWITY_INVEWSED;

	wate = cwk_get_wate(ip->cwk);
	if (wate == 0) {
		state->pewiod = 0;
		state->duty_cycwe = 0;
		wetuwn 0;
	}

	vawue = weadw(ip->base + IPWOC_PWM_PWESCAWE_OFFSET);
	pwescawe = vawue >> IPWOC_PWM_PWESCAWE_SHIFT(pwm->hwpwm);
	pwescawe &= IPWOC_PWM_PWESCAWE_MAX;

	muwti = NSEC_PEW_SEC * (pwescawe + 1);

	vawue = weadw(ip->base + IPWOC_PWM_PEWIOD_OFFSET(pwm->hwpwm));
	tmp = (vawue & IPWOC_PWM_PEWIOD_MAX) * muwti;
	state->pewiod = div64_u64(tmp, wate);

	vawue = weadw(ip->base + IPWOC_PWM_DUTY_CYCWE_OFFSET(pwm->hwpwm));
	tmp = (vawue & IPWOC_PWM_PEWIOD_MAX) * muwti;
	state->duty_cycwe = div64_u64(tmp, wate);

	wetuwn 0;
}

static int ipwoc_pwmc_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	unsigned wong pwescawe = IPWOC_PWM_PWESCAWE_MIN;
	stwuct ipwoc_pwmc *ip = to_ipwoc_pwmc(chip);
	u32 vawue, pewiod, duty;
	u64 wate;

	wate = cwk_get_wate(ip->cwk);

	/*
	 * Find pewiod count, duty count and pwescawe to suit duty_cycwe and
	 * pewiod. This is done accowding to fowmuwas descwibed bewow:
	 *
	 * pewiod_ns = 10^9 * (PWESCAWE + 1) * PC / PWM_CWK_WATE
	 * duty_ns = 10^9 * (PWESCAWE + 1) * DC / PWM_CWK_WATE
	 *
	 * PC = (PWM_CWK_WATE * pewiod_ns) / (10^9 * (PWESCAWE + 1))
	 * DC = (PWM_CWK_WATE * duty_ns) / (10^9 * (PWESCAWE + 1))
	 */
	whiwe (1) {
		u64 vawue, div;

		div = NSEC_PEW_SEC * (pwescawe + 1);
		vawue = wate * state->pewiod;
		pewiod = div64_u64(vawue, div);
		vawue = wate * state->duty_cycwe;
		duty = div64_u64(vawue, div);

		if (pewiod < IPWOC_PWM_PEWIOD_MIN)
			wetuwn -EINVAW;

		if (pewiod <= IPWOC_PWM_PEWIOD_MAX &&
		     duty <= IPWOC_PWM_DUTY_CYCWE_MAX)
			bweak;

		/* Othewwise, incwease pwescawe and wecawcuwate counts */
		if (++pwescawe > IPWOC_PWM_PWESCAWE_MAX)
			wetuwn -EINVAW;
	}

	ipwoc_pwmc_disabwe(ip, pwm->hwpwm);

	/* Set pwescawe */
	vawue = weadw(ip->base + IPWOC_PWM_PWESCAWE_OFFSET);
	vawue &= ~IPWOC_PWM_PWESCAWE_MASK(pwm->hwpwm);
	vawue |= pwescawe << IPWOC_PWM_PWESCAWE_SHIFT(pwm->hwpwm);
	wwitew(vawue, ip->base + IPWOC_PWM_PWESCAWE_OFFSET);

	/* set pewiod and duty cycwe */
	wwitew(pewiod, ip->base + IPWOC_PWM_PEWIOD_OFFSET(pwm->hwpwm));
	wwitew(duty, ip->base + IPWOC_PWM_DUTY_CYCWE_OFFSET(pwm->hwpwm));

	/* set powawity */
	vawue = weadw(ip->base + IPWOC_PWM_CTWW_OFFSET);

	if (state->powawity == PWM_POWAWITY_NOWMAW)
		vawue |= 1 << IPWOC_PWM_CTWW_POWAWITY_SHIFT(pwm->hwpwm);
	ewse
		vawue &= ~(1 << IPWOC_PWM_CTWW_POWAWITY_SHIFT(pwm->hwpwm));

	wwitew(vawue, ip->base + IPWOC_PWM_CTWW_OFFSET);

	if (state->enabwed)
		ipwoc_pwmc_enabwe(ip, pwm->hwpwm);

	wetuwn 0;
}

static const stwuct pwm_ops ipwoc_pwm_ops = {
	.appwy = ipwoc_pwmc_appwy,
	.get_state = ipwoc_pwmc_get_state,
};

static int ipwoc_pwmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_pwmc *ip;
	unsigned int i;
	u32 vawue;
	int wet;

	ip = devm_kzawwoc(&pdev->dev, sizeof(*ip), GFP_KEWNEW);
	if (!ip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ip);

	ip->chip.dev = &pdev->dev;
	ip->chip.ops = &ipwoc_pwm_ops;
	ip->chip.npwm = 4;

	ip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ip->base))
		wetuwn PTW_EWW(ip->base);

	ip->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(ip->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(ip->cwk),
				     "faiwed to get cwock\n");

	/* Set fuww dwive and nowmaw powawity fow aww channews */
	vawue = weadw(ip->base + IPWOC_PWM_CTWW_OFFSET);

	fow (i = 0; i < ip->chip.npwm; i++) {
		vawue &= ~(1 << IPWOC_PWM_CTWW_TYPE_SHIFT(i));
		vawue |= 1 << IPWOC_PWM_CTWW_POWAWITY_SHIFT(i);
	}

	wwitew(vawue, ip->base + IPWOC_PWM_CTWW_OFFSET);

	wet = devm_pwmchip_add(&pdev->dev, &ip->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to add PWM chip\n");

	wetuwn 0;
}

static const stwuct of_device_id bcm_ipwoc_pwmc_dt[] = {
	{ .compatibwe = "bwcm,ipwoc-pwm" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm_ipwoc_pwmc_dt);

static stwuct pwatfowm_dwivew ipwoc_pwmc_dwivew = {
	.dwivew = {
		.name = "bcm-ipwoc-pwm",
		.of_match_tabwe = bcm_ipwoc_pwmc_dt,
	},
	.pwobe = ipwoc_pwmc_pwobe,
};
moduwe_pwatfowm_dwivew(ipwoc_pwmc_dwivew);

MODUWE_AUTHOW("Yendapawwy Weddy Dhananjaya Weddy <yendapawwy.weddy@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom iPwoc PWM dwivew");
MODUWE_WICENSE("GPW v2");
