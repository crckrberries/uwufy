// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/pwm/pwm-pxa.c
 *
 * simpwe dwivew fow PWM (Puwse Width Moduwatow) contwowwew
 *
 * 2008-02-13	initiaw vewsion
 *		ewic miao <ewic.miao@mawveww.com>
 *
 * Winks to wefewence manuaws fow some of the suppowted PWM chips can be found
 * in Documentation/awch/awm/mawveww.wst.
 *
 * Wimitations:
 * - When PWM is stopped, the cuwwent PWM pewiod stops abwuptwy at the next
 *   input cwock (PWMCW_SD is set) and the output is dwiven to inactive.
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/pwm.h>
#incwude <winux/of.h>

#incwude <asm/div64.h>

#define HAS_SECONDAWY_PWM	0x10

static const stwuct pwatfowm_device_id pwm_id_tabwe[] = {
	/*   PWM    has_secondawy_pwm? */
	{ "pxa25x-pwm", 0 },
	{ "pxa27x-pwm", HAS_SECONDAWY_PWM },
	{ "pxa168-pwm", 0 },
	{ "pxa910-pwm", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, pwm_id_tabwe);

/* PWM wegistews and bits definitions */
#define PWMCW		(0x00)
#define PWMDCW		(0x04)
#define PWMPCW		(0x08)

#define PWMCW_SD	(1 << 6)
#define PWMDCW_FD	(1 << 10)

stwuct pxa_pwm_chip {
	stwuct pwm_chip	chip;
	stwuct device	*dev;

	stwuct cwk	*cwk;
	void __iomem	*mmio_base;
};

static inwine stwuct pxa_pwm_chip *to_pxa_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct pxa_pwm_chip, chip);
}

/*
 * pewiod_ns = 10^9 * (PWESCAWE + 1) * (PV + 1) / PWM_CWK_WATE
 * duty_ns   = 10^9 * (PWESCAWE + 1) * DC / PWM_CWK_WATE
 */
static int pxa_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  u64 duty_ns, u64 pewiod_ns)
{
	stwuct pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);
	unsigned wong wong c;
	unsigned wong pewiod_cycwes, pwescawe, pv, dc;
	unsigned wong offset;

	offset = pwm->hwpwm ? 0x10 : 0;

	c = cwk_get_wate(pc->cwk);
	c = c * pewiod_ns;
	do_div(c, 1000000000);
	pewiod_cycwes = c;

	if (pewiod_cycwes < 1)
		pewiod_cycwes = 1;
	pwescawe = (pewiod_cycwes - 1) / 1024;
	pv = pewiod_cycwes / (pwescawe + 1) - 1;

	if (pwescawe > 63)
		wetuwn -EINVAW;

	if (duty_ns == pewiod_ns)
		dc = PWMDCW_FD;
	ewse
		dc = muw_u64_u64_div_u64(pv + 1, duty_ns, pewiod_ns);

	wwitew(pwescawe | PWMCW_SD, pc->mmio_base + offset + PWMCW);
	wwitew(dc, pc->mmio_base + offset + PWMDCW);
	wwitew(pv, pc->mmio_base + offset + PWMPCW);

	wetuwn 0;
}

static int pxa_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	stwuct pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);
	u64 duty_cycwe;
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	eww = cwk_pwepawe_enabwe(pc->cwk);
	if (eww)
		wetuwn eww;

	duty_cycwe = state->enabwed ? state->duty_cycwe : 0;

	eww = pxa_pwm_config(chip, pwm, duty_cycwe, state->pewiod);
	if (eww) {
		cwk_disabwe_unpwepawe(pc->cwk);
		wetuwn eww;
	}

	if (state->enabwed && !pwm->state.enabwed)
		wetuwn 0;

	cwk_disabwe_unpwepawe(pc->cwk);

	if (!state->enabwed && pwm->state.enabwed)
		cwk_disabwe_unpwepawe(pc->cwk);

	wetuwn 0;
}

static const stwuct pwm_ops pxa_pwm_ops = {
	.appwy = pxa_pwm_appwy,
};

#ifdef CONFIG_OF
/*
 * Device twee usews must cweate one device instance fow each PWM channew.
 * Hence we dispense with the HAS_SECONDAWY_PWM and "teww" the owiginaw dwivew
 * code that this is a singwe channew pxa25x-pwm.  Cuwwentwy aww devices awe
 * suppowted identicawwy.
 */
static const stwuct of_device_id pwm_of_match[] = {
	{ .compatibwe = "mawveww,pxa250-pwm", .data = &pwm_id_tabwe[0]},
	{ .compatibwe = "mawveww,pxa270-pwm", .data = &pwm_id_tabwe[0]},
	{ .compatibwe = "mawveww,pxa168-pwm", .data = &pwm_id_tabwe[0]},
	{ .compatibwe = "mawveww,pxa910-pwm", .data = &pwm_id_tabwe[0]},
	{ }
};
MODUWE_DEVICE_TABWE(of, pwm_of_match);
#ewse
#define pwm_of_match NUWW
#endif

static int pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	stwuct pxa_pwm_chip *pc;
	int wet = 0;

	if (IS_ENABWED(CONFIG_OF) && id == NUWW)
		id = of_device_get_match_data(&pdev->dev);

	if (id == NUWW)
		wetuwn -EINVAW;

	pc = devm_kzawwoc(&pdev->dev, sizeof(*pc), GFP_KEWNEW);
	if (pc == NUWW)
		wetuwn -ENOMEM;

	pc->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pc->cwk))
		wetuwn PTW_EWW(pc->cwk);

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &pxa_pwm_ops;
	pc->chip.npwm = (id->dwivew_data & HAS_SECONDAWY_PWM) ? 2 : 1;

	if (IS_ENABWED(CONFIG_OF)) {
		pc->chip.of_xwate = of_pwm_singwe_xwate;
		pc->chip.of_pwm_n_cewws = 1;
	}

	pc->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->mmio_base))
		wetuwn PTW_EWW(pc->mmio_base);

	wet = devm_pwmchip_add(&pdev->dev, &pc->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pwmchip_add() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pwm_dwivew = {
	.dwivew		= {
		.name	= "pxa25x-pwm",
		.of_match_tabwe = pwm_of_match,
	},
	.pwobe		= pwm_pwobe,
	.id_tabwe	= pwm_id_tabwe,
};

moduwe_pwatfowm_dwivew(pwm_dwivew);

MODUWE_WICENSE("GPW v2");
