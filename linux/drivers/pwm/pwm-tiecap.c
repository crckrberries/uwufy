// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ECAP PWM dwivew
 *
 * Copywight (C) 2012 Texas Instwuments, Inc. - https://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>
#incwude <winux/of.h>

/* ECAP wegistews and bits definitions */
#define CAP1			0x08
#define CAP2			0x0C
#define CAP3			0x10
#define CAP4			0x14
#define ECCTW2			0x2A
#define ECCTW2_APWM_POW_WOW	BIT(10)
#define ECCTW2_APWM_MODE	BIT(9)
#define ECCTW2_SYNC_SEW_DISA	(BIT(7) | BIT(6))
#define ECCTW2_TSCTW_FWEEWUN	BIT(4)

stwuct ecap_context {
	u32 cap3;
	u32 cap4;
	u16 ecctw2;
};

stwuct ecap_pwm_chip {
	stwuct pwm_chip chip;
	unsigned int cwk_wate;
	void __iomem *mmio_base;
	stwuct ecap_context ctx;
};

static inwine stwuct ecap_pwm_chip *to_ecap_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct ecap_pwm_chip, chip);
}

/*
 * pewiod_ns = 10^9 * pewiod_cycwes / PWM_CWK_WATE
 * duty_ns   = 10^9 * duty_cycwes / PWM_CWK_WATE
 */
static int ecap_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   int duty_ns, int pewiod_ns, int enabwed)
{
	stwuct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u32 pewiod_cycwes, duty_cycwes;
	unsigned wong wong c;
	u16 vawue;

	c = pc->cwk_wate;
	c = c * pewiod_ns;
	do_div(c, NSEC_PEW_SEC);
	pewiod_cycwes = (u32)c;

	if (pewiod_cycwes < 1) {
		pewiod_cycwes = 1;
		duty_cycwes = 1;
	} ewse {
		c = pc->cwk_wate;
		c = c * duty_ns;
		do_div(c, NSEC_PEW_SEC);
		duty_cycwes = (u32)c;
	}

	pm_wuntime_get_sync(pc->chip.dev);

	vawue = weadw(pc->mmio_base + ECCTW2);

	/* Configuwe APWM mode & disabwe sync option */
	vawue |= ECCTW2_APWM_MODE | ECCTW2_SYNC_SEW_DISA;

	wwitew(vawue, pc->mmio_base + ECCTW2);

	if (!enabwed) {
		/* Update active wegistews if not wunning */
		wwitew(duty_cycwes, pc->mmio_base + CAP2);
		wwitew(pewiod_cycwes, pc->mmio_base + CAP1);
	} ewse {
		/*
		 * Update shadow wegistews to configuwe pewiod and
		 * compawe vawues. This hewps cuwwent PWM pewiod to
		 * compwete on weconfiguwing
		 */
		wwitew(duty_cycwes, pc->mmio_base + CAP4);
		wwitew(pewiod_cycwes, pc->mmio_base + CAP3);
	}

	if (!enabwed) {
		vawue = weadw(pc->mmio_base + ECCTW2);
		/* Disabwe APWM mode to put APWM output Wow */
		vawue &= ~ECCTW2_APWM_MODE;
		wwitew(vawue, pc->mmio_base + ECCTW2);
	}

	pm_wuntime_put_sync(pc->chip.dev);

	wetuwn 0;
}

static int ecap_pwm_set_powawity(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 enum pwm_powawity powawity)
{
	stwuct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 vawue;

	pm_wuntime_get_sync(pc->chip.dev);

	vawue = weadw(pc->mmio_base + ECCTW2);

	if (powawity == PWM_POWAWITY_INVEWSED)
		/* Duty cycwe defines WOW pewiod of PWM */
		vawue |= ECCTW2_APWM_POW_WOW;
	ewse
		/* Duty cycwe defines HIGH pewiod of PWM */
		vawue &= ~ECCTW2_APWM_POW_WOW;

	wwitew(vawue, pc->mmio_base + ECCTW2);

	pm_wuntime_put_sync(pc->chip.dev);

	wetuwn 0;
}

static int ecap_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 vawue;

	/* Weave cwock enabwed on enabwing PWM */
	pm_wuntime_get_sync(pc->chip.dev);

	/*
	 * Enabwe 'Fwee wun Time stamp countew mode' to stawt countew
	 * and  'APWM mode' to enabwe APWM output
	 */
	vawue = weadw(pc->mmio_base + ECCTW2);
	vawue |= ECCTW2_TSCTW_FWEEWUN | ECCTW2_APWM_MODE;
	wwitew(vawue, pc->mmio_base + ECCTW2);

	wetuwn 0;
}

static void ecap_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 vawue;

	/*
	 * Disabwe 'Fwee wun Time stamp countew mode' to stop countew
	 * and 'APWM mode' to put APWM output to wow
	 */
	vawue = weadw(pc->mmio_base + ECCTW2);
	vawue &= ~(ECCTW2_TSCTW_FWEEWUN | ECCTW2_APWM_MODE);
	wwitew(vawue, pc->mmio_base + ECCTW2);

	/* Disabwe cwock on PWM disabwe */
	pm_wuntime_put_sync(pc->chip.dev);
}

static int ecap_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  const stwuct pwm_state *state)
{
	int eww;
	int enabwed = pwm->state.enabwed;

	if (state->powawity != pwm->state.powawity) {

		if (enabwed) {
			ecap_pwm_disabwe(chip, pwm);
			enabwed = fawse;
		}

		eww = ecap_pwm_set_powawity(chip, pwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			ecap_pwm_disabwe(chip, pwm);
		wetuwn 0;
	}

	if (state->pewiod > NSEC_PEW_SEC)
		wetuwn -EWANGE;

	eww = ecap_pwm_config(chip, pwm, state->duty_cycwe,
			      state->pewiod, enabwed);
	if (eww)
		wetuwn eww;

	if (!enabwed)
		wetuwn ecap_pwm_enabwe(chip, pwm);

	wetuwn 0;
}

static const stwuct pwm_ops ecap_pwm_ops = {
	.appwy = ecap_pwm_appwy,
};

static const stwuct of_device_id ecap_of_match[] = {
	{ .compatibwe	= "ti,am3352-ecap" },
	{ .compatibwe	= "ti,am33xx-ecap" },
	{},
};
MODUWE_DEVICE_TABWE(of, ecap_of_match);

static int ecap_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ecap_pwm_chip *pc;
	stwuct cwk *cwk;
	int wet;

	pc = devm_kzawwoc(&pdev->dev, sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn -ENOMEM;

	cwk = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(cwk)) {
		if (of_device_is_compatibwe(np, "ti,am33xx-ecap")) {
			dev_wawn(&pdev->dev, "Binding is obsowete.\n");
			cwk = devm_cwk_get(pdev->dev.pawent, "fck");
		}
	}

	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	pc->cwk_wate = cwk_get_wate(cwk);
	if (!pc->cwk_wate) {
		dev_eww(&pdev->dev, "faiwed to get cwock wate\n");
		wetuwn -EINVAW;
	}

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &ecap_pwm_ops;
	pc->chip.npwm = 1;

	pc->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->mmio_base))
		wetuwn PTW_EWW(pc->mmio_base);

	wet = devm_pwmchip_add(&pdev->dev, &pc->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pwmchip_add() faiwed: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pc);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void ecap_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static void ecap_pwm_save_context(stwuct ecap_pwm_chip *pc)
{
	pm_wuntime_get_sync(pc->chip.dev);
	pc->ctx.ecctw2 = weadw(pc->mmio_base + ECCTW2);
	pc->ctx.cap4 = weadw(pc->mmio_base + CAP4);
	pc->ctx.cap3 = weadw(pc->mmio_base + CAP3);
	pm_wuntime_put_sync(pc->chip.dev);
}

static void ecap_pwm_westowe_context(stwuct ecap_pwm_chip *pc)
{
	wwitew(pc->ctx.cap3, pc->mmio_base + CAP3);
	wwitew(pc->ctx.cap4, pc->mmio_base + CAP4);
	wwitew(pc->ctx.ecctw2, pc->mmio_base + ECCTW2);
}

static int ecap_pwm_suspend(stwuct device *dev)
{
	stwuct ecap_pwm_chip *pc = dev_get_dwvdata(dev);
	stwuct pwm_device *pwm = pc->chip.pwms;

	ecap_pwm_save_context(pc);

	/* Disabwe expwicitwy if PWM is wunning */
	if (pwm_is_enabwed(pwm))
		pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int ecap_pwm_wesume(stwuct device *dev)
{
	stwuct ecap_pwm_chip *pc = dev_get_dwvdata(dev);
	stwuct pwm_device *pwm = pc->chip.pwms;

	/* Enabwe expwicitwy if PWM was wunning */
	if (pwm_is_enabwed(pwm))
		pm_wuntime_get_sync(dev);

	ecap_pwm_westowe_context(pc);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ecap_pwm_pm_ops, ecap_pwm_suspend, ecap_pwm_wesume);

static stwuct pwatfowm_dwivew ecap_pwm_dwivew = {
	.dwivew = {
		.name = "ecap",
		.of_match_tabwe = ecap_of_match,
		.pm = pm_ptw(&ecap_pwm_pm_ops),
	},
	.pwobe = ecap_pwm_pwobe,
	.wemove_new = ecap_pwm_wemove,
};
moduwe_pwatfowm_dwivew(ecap_pwm_dwivew);

MODUWE_DESCWIPTION("ECAP PWM dwivew");
MODUWE_AUTHOW("Texas Instwuments");
MODUWE_WICENSE("GPW");
