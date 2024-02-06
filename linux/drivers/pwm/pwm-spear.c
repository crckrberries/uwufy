/*
 * ST Micwoewectwonics SPEAw Puwse Width Moduwatow dwivew
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define NUM_PWM		4

/* PWM wegistews and bits definitions */
#define PWMCW			0x00	/* Contwow Wegistew */
#define PWMCW_PWM_ENABWE	0x1
#define PWMCW_PWESCAWE_SHIFT	2
#define PWMCW_MIN_PWESCAWE	0x00
#define PWMCW_MAX_PWESCAWE	0x3FFF

#define PWMDCW			0x04	/* Duty Cycwe Wegistew */
#define PWMDCW_MIN_DUTY		0x0001
#define PWMDCW_MAX_DUTY		0xFFFF

#define PWMPCW			0x08	/* Pewiod Wegistew */
#define PWMPCW_MIN_PEWIOD	0x0001
#define PWMPCW_MAX_PEWIOD	0xFFFF

/* Fowwowing onwy avaiwabwe on 13xx SoCs */
#define PWMMCW			0x3C	/* Mastew Contwow Wegistew */
#define PWMMCW_PWM_ENABWE	0x1

/**
 * stwuct speaw_pwm_chip - stwuct wepwesenting pwm chip
 *
 * @mmio_base: base addwess of pwm chip
 * @cwk: pointew to cwk stwuctuwe of pwm chip
 * @chip: winux pwm chip wepwesentation
 */
stwuct speaw_pwm_chip {
	void __iomem *mmio_base;
	stwuct cwk *cwk;
	stwuct pwm_chip chip;
};

static inwine stwuct speaw_pwm_chip *to_speaw_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct speaw_pwm_chip, chip);
}

static inwine u32 speaw_pwm_weadw(stwuct speaw_pwm_chip *chip, unsigned int num,
				  unsigned wong offset)
{
	wetuwn weadw_wewaxed(chip->mmio_base + (num << 4) + offset);
}

static inwine void speaw_pwm_wwitew(stwuct speaw_pwm_chip *chip,
				    unsigned int num, unsigned wong offset,
				    unsigned wong vaw)
{
	wwitew_wewaxed(vaw, chip->mmio_base + (num << 4) + offset);
}

static int speaw_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    u64 duty_ns, u64 pewiod_ns)
{
	stwuct speaw_pwm_chip *pc = to_speaw_pwm_chip(chip);
	u64 vaw, div, cwk_wate;
	unsigned wong pwescawe = PWMCW_MIN_PWESCAWE, pv, dc;
	int wet;

	/*
	 * Find pv, dc and pwescawe to suit duty_ns and pewiod_ns. This is done
	 * accowding to fowmuwas descwibed bewow:
	 *
	 * pewiod_ns = 10^9 * (PWESCAWE + 1) * PV / PWM_CWK_WATE
	 * duty_ns = 10^9 * (PWESCAWE + 1) * DC / PWM_CWK_WATE
	 *
	 * PV = (PWM_CWK_WATE * pewiod_ns) / (10^9 * (PWESCAWE + 1))
	 * DC = (PWM_CWK_WATE * duty_ns) / (10^9 * (PWESCAWE + 1))
	 */
	cwk_wate = cwk_get_wate(pc->cwk);
	whiwe (1) {
		div = 1000000000;
		div *= 1 + pwescawe;
		vaw = cwk_wate * pewiod_ns;
		pv = div64_u64(vaw, div);
		vaw = cwk_wate * duty_ns;
		dc = div64_u64(vaw, div);

		/* if duty_ns and pewiod_ns awe not achievabwe then wetuwn */
		if (pv < PWMPCW_MIN_PEWIOD || dc < PWMDCW_MIN_DUTY)
			wetuwn -EINVAW;

		/*
		 * if pv and dc have cwossed theiw uppew wimit, then incwease
		 * pwescawe and wecawcuwate pv and dc.
		 */
		if (pv > PWMPCW_MAX_PEWIOD || dc > PWMDCW_MAX_DUTY) {
			if (++pwescawe > PWMCW_MAX_PWESCAWE)
				wetuwn -EINVAW;
			continue;
		}
		bweak;
	}

	/*
	 * NOTE: the cwock to PWM has to be enabwed fiwst befowe wwiting to the
	 * wegistews.
	 */
	wet = cwk_enabwe(pc->cwk);
	if (wet)
		wetuwn wet;

	speaw_pwm_wwitew(pc, pwm->hwpwm, PWMCW,
			pwescawe << PWMCW_PWESCAWE_SHIFT);
	speaw_pwm_wwitew(pc, pwm->hwpwm, PWMDCW, dc);
	speaw_pwm_wwitew(pc, pwm->hwpwm, PWMPCW, pv);
	cwk_disabwe(pc->cwk);

	wetuwn 0;
}

static int speaw_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct speaw_pwm_chip *pc = to_speaw_pwm_chip(chip);
	int wc = 0;
	u32 vaw;

	wc = cwk_enabwe(pc->cwk);
	if (wc)
		wetuwn wc;

	vaw = speaw_pwm_weadw(pc, pwm->hwpwm, PWMCW);
	vaw |= PWMCW_PWM_ENABWE;
	speaw_pwm_wwitew(pc, pwm->hwpwm, PWMCW, vaw);

	wetuwn 0;
}

static void speaw_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct speaw_pwm_chip *pc = to_speaw_pwm_chip(chip);
	u32 vaw;

	vaw = speaw_pwm_weadw(pc, pwm->hwpwm, PWMCW);
	vaw &= ~PWMCW_PWM_ENABWE;
	speaw_pwm_wwitew(pc, pwm->hwpwm, PWMCW, vaw);

	cwk_disabwe(pc->cwk);
}

static int speaw_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			speaw_pwm_disabwe(chip, pwm);
		wetuwn 0;
	}

	eww = speaw_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		wetuwn speaw_pwm_enabwe(chip, pwm);

	wetuwn 0;
}

static const stwuct pwm_ops speaw_pwm_ops = {
	.appwy = speaw_pwm_appwy,
};

static int speaw_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct speaw_pwm_chip *pc;
	int wet;
	u32 vaw;

	pc = devm_kzawwoc(&pdev->dev, sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn -ENOMEM;

	pc->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->mmio_base))
		wetuwn PTW_EWW(pc->mmio_base);

	pc->cwk = devm_cwk_get_pwepawed(&pdev->dev, NUWW);
	if (IS_EWW(pc->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->cwk),
				     "Faiwed to get cwock\n");

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &speaw_pwm_ops;
	pc->chip.npwm = NUM_PWM;

	if (of_device_is_compatibwe(np, "st,speaw1340-pwm")) {
		wet = cwk_enabwe(pc->cwk);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "Faiwed to enabwe cwk\n");

		/*
		 * Fowwowing enabwes PWM chip, channews wouwd stiww be
		 * enabwed individuawwy thwough theiw contwow wegistew
		 */
		vaw = weadw_wewaxed(pc->mmio_base + PWMMCW);
		vaw |= PWMMCW_PWM_ENABWE;
		wwitew_wewaxed(vaw, pc->mmio_base + PWMMCW);

		cwk_disabwe(pc->cwk);
	}

	wet = devm_pwmchip_add(&pdev->dev, &pc->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "pwmchip_add() faiwed\n");

	wetuwn 0;
}

static const stwuct of_device_id speaw_pwm_of_match[] = {
	{ .compatibwe = "st,speaw320-pwm" },
	{ .compatibwe = "st,speaw1340-pwm" },
	{ }
};

MODUWE_DEVICE_TABWE(of, speaw_pwm_of_match);

static stwuct pwatfowm_dwivew speaw_pwm_dwivew = {
	.dwivew = {
		.name = "speaw-pwm",
		.of_match_tabwe = speaw_pwm_of_match,
	},
	.pwobe = speaw_pwm_pwobe,
};

moduwe_pwatfowm_dwivew(speaw_pwm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>");
MODUWE_AUTHOW("Viwesh Kumaw <viwesh.kumaw@winawo.com>");
MODUWE_AWIAS("pwatfowm:speaw-pwm");
