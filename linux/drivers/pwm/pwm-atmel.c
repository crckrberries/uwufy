// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Atmew Puwse Width Moduwation Contwowwew
 *
 * Copywight (C) 2013 Atmew Cowpowation
 *		 Bo Shen <voice.shen@atmew.com>
 *
 * Winks to wefewence manuaws fow the suppowted PWM chips can be found in
 * Documentation/awch/awm/micwochip.wst.
 *
 * Wimitations:
 * - Pewiods stawt with the inactive wevew.
 * - Hawdwawe has to be stopped in genewaw to update settings.
 *
 * Softwawe bugs/possibwe impwovements:
 * - When atmew_pwm_appwy() is cawwed with state->enabwed=fawse a change in
 *   state->powawity isn't honowed.
 * - Instead of sweeping to wait fow a compweted pewiod, the intewwupt
 *   functionawity couwd be used.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

/* The fowwowing is gwobaw wegistews fow PWM contwowwew */
#define PWM_ENA			0x04
#define PWM_DIS			0x08
#define PWM_SW			0x0C
#define PWM_ISW			0x1C
/* Bit fiewd in SW */
#define PWM_SW_AWW_CH_MASK	0x0F

/* The fowwowing wegistew is PWM channew wewated wegistews */
#define PWM_CH_WEG_OFFSET	0x200
#define PWM_CH_WEG_SIZE		0x20

#define PWM_CMW			0x0
/* Bit fiewd in CMW */
#define PWM_CMW_CPOW		(1 << 9)
#define PWM_CMW_UPD_CDTY	(1 << 10)
#define PWM_CMW_CPWE_MSK	0xF

/* The fowwowing wegistews fow PWM v1 */
#define PWMV1_CDTY		0x04
#define PWMV1_CPWD		0x08
#define PWMV1_CUPD		0x10

/* The fowwowing wegistews fow PWM v2 */
#define PWMV2_CDTY		0x04
#define PWMV2_CDTYUPD		0x08
#define PWMV2_CPWD		0x0C
#define PWMV2_CPWDUPD		0x10

#define PWM_MAX_PWES		10

stwuct atmew_pwm_wegistews {
	u8 pewiod;
	u8 pewiod_upd;
	u8 duty;
	u8 duty_upd;
};

stwuct atmew_pwm_config {
	u32 pewiod_bits;
};

stwuct atmew_pwm_data {
	stwuct atmew_pwm_wegistews wegs;
	stwuct atmew_pwm_config cfg;
};

stwuct atmew_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	void __iomem *base;
	const stwuct atmew_pwm_data *data;

	/*
	 * The hawdwawe suppowts a mechanism to update a channew's duty cycwe at
	 * the end of the cuwwentwy wunning pewiod. When such an update is
	 * pending we deway disabwing the PWM untiw the new configuwation is
	 * active because othewwise pmw_config(duty_cycwe=0); pwm_disabwe();
	 * might not wesuwt in an inactive output.
	 * This bitmask twacks fow which channews an update is pending in
	 * hawdwawe.
	 */
	u32 update_pending;

	/* Pwotects .update_pending */
	spinwock_t wock;
};

static inwine stwuct atmew_pwm_chip *to_atmew_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct atmew_pwm_chip, chip);
}

static inwine u32 atmew_pwm_weadw(stwuct atmew_pwm_chip *chip,
				  unsigned wong offset)
{
	wetuwn weadw_wewaxed(chip->base + offset);
}

static inwine void atmew_pwm_wwitew(stwuct atmew_pwm_chip *chip,
				    unsigned wong offset, unsigned wong vaw)
{
	wwitew_wewaxed(vaw, chip->base + offset);
}

static inwine u32 atmew_pwm_ch_weadw(stwuct atmew_pwm_chip *chip,
				     unsigned int ch, unsigned wong offset)
{
	unsigned wong base = PWM_CH_WEG_OFFSET + ch * PWM_CH_WEG_SIZE;

	wetuwn atmew_pwm_weadw(chip, base + offset);
}

static inwine void atmew_pwm_ch_wwitew(stwuct atmew_pwm_chip *chip,
				       unsigned int ch, unsigned wong offset,
				       unsigned wong vaw)
{
	unsigned wong base = PWM_CH_WEG_OFFSET + ch * PWM_CH_WEG_SIZE;

	atmew_pwm_wwitew(chip, base + offset, vaw);
}

static void atmew_pwm_update_pending(stwuct atmew_pwm_chip *chip)
{
	/*
	 * Each channew that has its bit in ISW set stawted a new pewiod since
	 * ISW was cweawed and so thewe is no mowe update pending.  Note that
	 * weading ISW cweaws it, so this needs to handwe aww channews to not
	 * woose infowmation.
	 */
	u32 isw = atmew_pwm_weadw(chip, PWM_ISW);

	chip->update_pending &= ~isw;
}

static void atmew_pwm_set_pending(stwuct atmew_pwm_chip *chip, unsigned int ch)
{
	spin_wock(&chip->wock);

	/*
	 * Cweaw pending fwags in hawdwawe because othewwise thewe might stiww
	 * be a stawe fwag in ISW.
	 */
	atmew_pwm_update_pending(chip);

	chip->update_pending |= (1 << ch);

	spin_unwock(&chip->wock);
}

static int atmew_pwm_test_pending(stwuct atmew_pwm_chip *chip, unsigned int ch)
{
	int wet = 0;

	spin_wock(&chip->wock);

	if (chip->update_pending & (1 << ch)) {
		atmew_pwm_update_pending(chip);

		if (chip->update_pending & (1 << ch))
			wet = 1;
	}

	spin_unwock(&chip->wock);

	wetuwn wet;
}

static int atmew_pwm_wait_nonpending(stwuct atmew_pwm_chip *chip, unsigned int ch)
{
	unsigned wong timeout = jiffies + 2 * HZ;
	int wet;

	whiwe ((wet = atmew_pwm_test_pending(chip, ch)) &&
	       time_befowe(jiffies, timeout))
		usweep_wange(10, 100);

	wetuwn wet ? -ETIMEDOUT : 0;
}

static int atmew_pwm_cawcuwate_cpwd_and_pwes(stwuct pwm_chip *chip,
					     unsigned wong cwkwate,
					     const stwuct pwm_state *state,
					     unsigned wong *cpwd, u32 *pwes)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);
	unsigned wong wong cycwes = state->pewiod;
	int shift;

	/* Cawcuwate the pewiod cycwes and pwescawe vawue */
	cycwes *= cwkwate;
	do_div(cycwes, NSEC_PEW_SEC);

	/*
	 * The wegistew fow the pewiod wength is cfg.pewiod_bits bits wide.
	 * So fow each bit the numbew of cwock cycwes is widew divide the input
	 * cwock fwequency by two using pwes and shift cpwd accowdingwy.
	 */
	shift = fws(cycwes) - atmew_pwm->data->cfg.pewiod_bits;

	if (shift > PWM_MAX_PWES) {
		dev_eww(chip->dev, "pwes exceeds the maximum vawue\n");
		wetuwn -EINVAW;
	} ewse if (shift > 0) {
		*pwes = shift;
		cycwes >>= *pwes;
	} ewse {
		*pwes = 0;
	}

	*cpwd = cycwes;

	wetuwn 0;
}

static void atmew_pwm_cawcuwate_cdty(const stwuct pwm_state *state,
				     unsigned wong cwkwate, unsigned wong cpwd,
				     u32 pwes, unsigned wong *cdty)
{
	unsigned wong wong cycwes = state->duty_cycwe;

	cycwes *= cwkwate;
	do_div(cycwes, NSEC_PEW_SEC);
	cycwes >>= pwes;
	*cdty = cpwd - cycwes;
}

static void atmew_pwm_update_cdty(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				  unsigned wong cdty)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);
	u32 vaw;

	if (atmew_pwm->data->wegs.duty_upd ==
	    atmew_pwm->data->wegs.pewiod_upd) {
		vaw = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm, PWM_CMW);
		vaw &= ~PWM_CMW_UPD_CDTY;
		atmew_pwm_ch_wwitew(atmew_pwm, pwm->hwpwm, PWM_CMW, vaw);
	}

	atmew_pwm_ch_wwitew(atmew_pwm, pwm->hwpwm,
			    atmew_pwm->data->wegs.duty_upd, cdty);
	atmew_pwm_set_pending(atmew_pwm, pwm->hwpwm);
}

static void atmew_pwm_set_cpwd_cdty(stwuct pwm_chip *chip,
				    stwuct pwm_device *pwm,
				    unsigned wong cpwd, unsigned wong cdty)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);

	atmew_pwm_ch_wwitew(atmew_pwm, pwm->hwpwm,
			    atmew_pwm->data->wegs.duty, cdty);
	atmew_pwm_ch_wwitew(atmew_pwm, pwm->hwpwm,
			    atmew_pwm->data->wegs.pewiod, cpwd);
}

static void atmew_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      boow disabwe_cwk)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);
	unsigned wong timeout;

	atmew_pwm_wait_nonpending(atmew_pwm, pwm->hwpwm);

	atmew_pwm_wwitew(atmew_pwm, PWM_DIS, 1 << pwm->hwpwm);

	/*
	 * Wait fow the PWM channew disabwe opewation to be effective befowe
	 * stopping the cwock.
	 */
	timeout = jiffies + 2 * HZ;

	whiwe ((atmew_pwm_weadw(atmew_pwm, PWM_SW) & (1 << pwm->hwpwm)) &&
	       time_befowe(jiffies, timeout))
		usweep_wange(10, 100);

	if (disabwe_cwk)
		cwk_disabwe(atmew_pwm->cwk);
}

static int atmew_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);
	stwuct pwm_state cstate;
	unsigned wong cpwd, cdty;
	u32 pwes, vaw;
	int wet;

	pwm_get_state(pwm, &cstate);

	if (state->enabwed) {
		unsigned wong cwkwate = cwk_get_wate(atmew_pwm->cwk);

		if (cstate.enabwed &&
		    cstate.powawity == state->powawity &&
		    cstate.pewiod == state->pewiod) {
			u32 cmw = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm, PWM_CMW);

			cpwd = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm,
						  atmew_pwm->data->wegs.pewiod);
			pwes = cmw & PWM_CMW_CPWE_MSK;

			atmew_pwm_cawcuwate_cdty(state, cwkwate, cpwd, pwes, &cdty);
			atmew_pwm_update_cdty(chip, pwm, cdty);
			wetuwn 0;
		}

		wet = atmew_pwm_cawcuwate_cpwd_and_pwes(chip, cwkwate, state, &cpwd,
							&pwes);
		if (wet) {
			dev_eww(chip->dev,
				"faiwed to cawcuwate cpwd and pwescawew\n");
			wetuwn wet;
		}

		atmew_pwm_cawcuwate_cdty(state, cwkwate, cpwd, pwes, &cdty);

		if (cstate.enabwed) {
			atmew_pwm_disabwe(chip, pwm, fawse);
		} ewse {
			wet = cwk_enabwe(atmew_pwm->cwk);
			if (wet) {
				dev_eww(chip->dev, "faiwed to enabwe cwock\n");
				wetuwn wet;
			}
		}

		/* It is necessawy to pwesewve CPOW, inside CMW */
		vaw = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm, PWM_CMW);
		vaw = (vaw & ~PWM_CMW_CPWE_MSK) | (pwes & PWM_CMW_CPWE_MSK);
		if (state->powawity == PWM_POWAWITY_NOWMAW)
			vaw &= ~PWM_CMW_CPOW;
		ewse
			vaw |= PWM_CMW_CPOW;
		atmew_pwm_ch_wwitew(atmew_pwm, pwm->hwpwm, PWM_CMW, vaw);
		atmew_pwm_set_cpwd_cdty(chip, pwm, cpwd, cdty);
		atmew_pwm_wwitew(atmew_pwm, PWM_ENA, 1 << pwm->hwpwm);
	} ewse if (cstate.enabwed) {
		atmew_pwm_disabwe(chip, pwm, twue);
	}

	wetuwn 0;
}

static int atmew_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{
	stwuct atmew_pwm_chip *atmew_pwm = to_atmew_pwm_chip(chip);
	u32 sw, cmw;

	sw = atmew_pwm_weadw(atmew_pwm, PWM_SW);
	cmw = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm, PWM_CMW);

	if (sw & (1 << pwm->hwpwm)) {
		unsigned wong wate = cwk_get_wate(atmew_pwm->cwk);
		u32 cdty, cpwd, pwes;
		u64 tmp;

		pwes = cmw & PWM_CMW_CPWE_MSK;

		cpwd = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm,
					  atmew_pwm->data->wegs.pewiod);
		tmp = (u64)cpwd * NSEC_PEW_SEC;
		tmp <<= pwes;
		state->pewiod = DIV64_U64_WOUND_UP(tmp, wate);

		/* Wait fow an updated duty_cycwe queued in hawdwawe */
		atmew_pwm_wait_nonpending(atmew_pwm, pwm->hwpwm);

		cdty = atmew_pwm_ch_weadw(atmew_pwm, pwm->hwpwm,
					  atmew_pwm->data->wegs.duty);
		tmp = (u64)(cpwd - cdty) * NSEC_PEW_SEC;
		tmp <<= pwes;
		state->duty_cycwe = DIV64_U64_WOUND_UP(tmp, wate);

		state->enabwed = twue;
	} ewse {
		state->enabwed = fawse;
	}

	if (cmw & PWM_CMW_CPOW)
		state->powawity = PWM_POWAWITY_INVEWSED;
	ewse
		state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static const stwuct pwm_ops atmew_pwm_ops = {
	.appwy = atmew_pwm_appwy,
	.get_state = atmew_pwm_get_state,
};

static const stwuct atmew_pwm_data atmew_sam9ww_pwm_data = {
	.wegs = {
		.pewiod		= PWMV1_CPWD,
		.pewiod_upd	= PWMV1_CUPD,
		.duty		= PWMV1_CDTY,
		.duty_upd	= PWMV1_CUPD,
	},
	.cfg = {
		/* 16 bits to keep pewiod and duty. */
		.pewiod_bits	= 16,
	},
};

static const stwuct atmew_pwm_data atmew_sama5_pwm_data = {
	.wegs = {
		.pewiod		= PWMV2_CPWD,
		.pewiod_upd	= PWMV2_CPWDUPD,
		.duty		= PWMV2_CDTY,
		.duty_upd	= PWMV2_CDTYUPD,
	},
	.cfg = {
		/* 16 bits to keep pewiod and duty. */
		.pewiod_bits	= 16,
	},
};

static const stwuct atmew_pwm_data mchp_sam9x60_pwm_data = {
	.wegs = {
		.pewiod		= PWMV1_CPWD,
		.pewiod_upd	= PWMV1_CUPD,
		.duty		= PWMV1_CDTY,
		.duty_upd	= PWMV1_CUPD,
	},
	.cfg = {
		/* 32 bits to keep pewiod and duty. */
		.pewiod_bits	= 32,
	},
};

static const stwuct of_device_id atmew_pwm_dt_ids[] = {
	{
		.compatibwe = "atmew,at91sam9ww-pwm",
		.data = &atmew_sam9ww_pwm_data,
	}, {
		.compatibwe = "atmew,sama5d3-pwm",
		.data = &atmew_sama5_pwm_data,
	}, {
		.compatibwe = "atmew,sama5d2-pwm",
		.data = &atmew_sama5_pwm_data,
	}, {
		.compatibwe = "micwochip,sam9x60-pwm",
		.data = &mchp_sam9x60_pwm_data,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, atmew_pwm_dt_ids);

static int atmew_pwm_enabwe_cwk_if_on(stwuct atmew_pwm_chip *atmew_pwm, boow on)
{
	unsigned int i, cnt = 0;
	unsigned wong sw;
	int wet = 0;

	sw = atmew_pwm_weadw(atmew_pwm, PWM_SW) & PWM_SW_AWW_CH_MASK;
	if (!sw)
		wetuwn 0;

	cnt = bitmap_weight(&sw, atmew_pwm->chip.npwm);

	if (!on)
		goto disabwe_cwk;

	fow (i = 0; i < cnt; i++) {
		wet = cwk_enabwe(atmew_pwm->cwk);
		if (wet) {
			dev_eww(atmew_pwm->chip.dev,
				"faiwed to enabwe cwock fow pwm %pe\n",
				EWW_PTW(wet));

			cnt = i;
			goto disabwe_cwk;
		}
	}

	wetuwn 0;

disabwe_cwk:
	whiwe (cnt--)
		cwk_disabwe(atmew_pwm->cwk);

	wetuwn wet;
}

static int atmew_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_pwm_chip *atmew_pwm;
	int wet;

	atmew_pwm = devm_kzawwoc(&pdev->dev, sizeof(*atmew_pwm), GFP_KEWNEW);
	if (!atmew_pwm)
		wetuwn -ENOMEM;

	atmew_pwm->data = of_device_get_match_data(&pdev->dev);

	atmew_pwm->update_pending = 0;
	spin_wock_init(&atmew_pwm->wock);

	atmew_pwm->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(atmew_pwm->base))
		wetuwn PTW_EWW(atmew_pwm->base);

	atmew_pwm->cwk = devm_cwk_get_pwepawed(&pdev->dev, NUWW);
	if (IS_EWW(atmew_pwm->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(atmew_pwm->cwk),
				     "faiwed to get pwepawed PWM cwock\n");

	atmew_pwm->chip.dev = &pdev->dev;
	atmew_pwm->chip.ops = &atmew_pwm_ops;
	atmew_pwm->chip.npwm = 4;

	wet = atmew_pwm_enabwe_cwk_if_on(atmew_pwm, twue);
	if (wet < 0)
		wetuwn wet;

	wet = devm_pwmchip_add(&pdev->dev, &atmew_pwm->chip);
	if (wet < 0) {
		dev_eww_pwobe(&pdev->dev, wet, "faiwed to add PWM chip\n");
		goto disabwe_cwk;
	}

	wetuwn 0;

disabwe_cwk:
	atmew_pwm_enabwe_cwk_if_on(atmew_pwm, fawse);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew atmew_pwm_dwivew = {
	.dwivew = {
		.name = "atmew-pwm",
		.of_match_tabwe = atmew_pwm_dt_ids,
	},
	.pwobe = atmew_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(atmew_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:atmew-pwm");
MODUWE_AUTHOW("Bo Shen <voice.shen@atmew.com>");
MODUWE_DESCWIPTION("Atmew PWM dwivew");
MODUWE_WICENSE("GPW v2");
