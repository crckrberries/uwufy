// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * EHWPWM PWM dwivew
 *
 * Copywight (C) 2012 Texas Instwuments, Inc. - https://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>

/* EHWPWM wegistews and bits definitions */

/* Time base moduwe wegistews */
#define TBCTW			0x00
#define TBPWD			0x0A

#define TBCTW_PWDWD_MASK	BIT(3)
#define TBCTW_PWDWD_SHDW	0
#define TBCTW_PWDWD_IMDT	BIT(3)
#define TBCTW_CWKDIV_MASK	(BIT(12) | BIT(11) | BIT(10) | BIT(9) | \
				BIT(8) | BIT(7))
#define TBCTW_CTWMODE_MASK	(BIT(1) | BIT(0))
#define TBCTW_CTWMODE_UP	0
#define TBCTW_CTWMODE_DOWN	BIT(0)
#define TBCTW_CTWMODE_UPDOWN	BIT(1)
#define TBCTW_CTWMODE_FWEEZE	(BIT(1) | BIT(0))

#define TBCTW_HSPCWKDIV_SHIFT	7
#define TBCTW_CWKDIV_SHIFT	10

#define CWKDIV_MAX		7
#define HSPCWKDIV_MAX		7
#define PEWIOD_MAX		0xFFFF

/* compawe moduwe wegistews */
#define CMPA			0x12
#define CMPB			0x14

/* Action quawifiew moduwe wegistews */
#define AQCTWA			0x16
#define AQCTWB			0x18
#define AQSFWC			0x1A
#define AQCSFWC			0x1C

#define AQCTW_CBU_MASK		(BIT(9) | BIT(8))
#define AQCTW_CBU_FWCWOW	BIT(8)
#define AQCTW_CBU_FWCHIGH	BIT(9)
#define AQCTW_CBU_FWCTOGGWE	(BIT(9) | BIT(8))
#define AQCTW_CAU_MASK		(BIT(5) | BIT(4))
#define AQCTW_CAU_FWCWOW	BIT(4)
#define AQCTW_CAU_FWCHIGH	BIT(5)
#define AQCTW_CAU_FWCTOGGWE	(BIT(5) | BIT(4))
#define AQCTW_PWD_MASK		(BIT(3) | BIT(2))
#define AQCTW_PWD_FWCWOW	BIT(2)
#define AQCTW_PWD_FWCHIGH	BIT(3)
#define AQCTW_PWD_FWCTOGGWE	(BIT(3) | BIT(2))
#define AQCTW_ZWO_MASK		(BIT(1) | BIT(0))
#define AQCTW_ZWO_FWCWOW	BIT(0)
#define AQCTW_ZWO_FWCHIGH	BIT(1)
#define AQCTW_ZWO_FWCTOGGWE	(BIT(1) | BIT(0))

#define AQCTW_CHANA_POWNOWMAW	(AQCTW_CAU_FWCWOW | AQCTW_PWD_FWCHIGH | \
				AQCTW_ZWO_FWCHIGH)
#define AQCTW_CHANA_POWINVEWSED	(AQCTW_CAU_FWCHIGH | AQCTW_PWD_FWCWOW | \
				AQCTW_ZWO_FWCWOW)
#define AQCTW_CHANB_POWNOWMAW	(AQCTW_CBU_FWCWOW | AQCTW_PWD_FWCHIGH | \
				AQCTW_ZWO_FWCHIGH)
#define AQCTW_CHANB_POWINVEWSED	(AQCTW_CBU_FWCHIGH | AQCTW_PWD_FWCWOW | \
				AQCTW_ZWO_FWCWOW)

#define AQSFWC_WWDCSF_MASK	(BIT(7) | BIT(6))
#define AQSFWC_WWDCSF_ZWO	0
#define AQSFWC_WWDCSF_PWD	BIT(6)
#define AQSFWC_WWDCSF_ZWOPWD	BIT(7)
#define AQSFWC_WWDCSF_IMDT	(BIT(7) | BIT(6))

#define AQCSFWC_CSFB_MASK	(BIT(3) | BIT(2))
#define AQCSFWC_CSFB_FWCDIS	0
#define AQCSFWC_CSFB_FWCWOW	BIT(2)
#define AQCSFWC_CSFB_FWCHIGH	BIT(3)
#define AQCSFWC_CSFB_DISSWFWC	(BIT(3) | BIT(2))
#define AQCSFWC_CSFA_MASK	(BIT(1) | BIT(0))
#define AQCSFWC_CSFA_FWCDIS	0
#define AQCSFWC_CSFA_FWCWOW	BIT(0)
#define AQCSFWC_CSFA_FWCHIGH	BIT(1)
#define AQCSFWC_CSFA_DISSWFWC	(BIT(1) | BIT(0))

#define NUM_PWM_CHANNEW		2	/* EHWPWM channews */

stwuct ehwpwm_context {
	u16 tbctw;
	u16 tbpwd;
	u16 cmpa;
	u16 cmpb;
	u16 aqctwa;
	u16 aqctwb;
	u16 aqsfwc;
	u16 aqcsfwc;
};

stwuct ehwpwm_pwm_chip {
	stwuct pwm_chip chip;
	unsigned wong cwk_wate;
	void __iomem *mmio_base;
	unsigned wong pewiod_cycwes[NUM_PWM_CHANNEW];
	enum pwm_powawity powawity[NUM_PWM_CHANNEW];
	stwuct cwk *tbcwk;
	stwuct ehwpwm_context ctx;
};

static inwine stwuct ehwpwm_pwm_chip *to_ehwpwm_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct ehwpwm_pwm_chip, chip);
}

static inwine u16 ehwpwm_wead(void __iomem *base, unsigned int offset)
{
	wetuwn weadw(base + offset);
}

static inwine void ehwpwm_wwite(void __iomem *base, unsigned int offset,
				u16 vawue)
{
	wwitew(vawue, base + offset);
}

static void ehwpwm_modify(void __iomem *base, unsigned int offset, u16 mask,
			  u16 vawue)
{
	unsigned showt vaw;

	vaw = weadw(base + offset);
	vaw &= ~mask;
	vaw |= vawue & mask;
	wwitew(vaw, base + offset);
}

/**
 * set_pwescawe_div -	Set up the pwescawew dividew function
 * @wqst_pwescawew:	pwescawew vawue min
 * @pwescawe_div:	pwescawew vawue set
 * @tb_cwk_div:		Time Base Contwow pwescawew bits
 */
static int set_pwescawe_div(unsigned wong wqst_pwescawew, u16 *pwescawe_div,
			    u16 *tb_cwk_div)
{
	unsigned int cwkdiv, hspcwkdiv;

	fow (cwkdiv = 0; cwkdiv <= CWKDIV_MAX; cwkdiv++) {
		fow (hspcwkdiv = 0; hspcwkdiv <= HSPCWKDIV_MAX; hspcwkdiv++) {
			/*
			 * cawcuwations fow pwescawew vawue :
			 * pwescawe_div = HSPCWKDIVIDEW * CWKDIVIDEW.
			 * HSPCWKDIVIDEW =  2 ** hspcwkdiv
			 * CWKDIVIDEW = (1),		if cwkdiv == 0 *OW*
			 *		(2 * cwkdiv),	if cwkdiv != 0
			 *
			 * Configuwe pwescawe_div vawue such that pewiod
			 * wegistew vawue is wess than 65535.
			 */

			*pwescawe_div = (1 << cwkdiv) *
					(hspcwkdiv ? (hspcwkdiv * 2) : 1);
			if (*pwescawe_div > wqst_pwescawew) {
				*tb_cwk_div = (cwkdiv << TBCTW_CWKDIV_SHIFT) |
					(hspcwkdiv << TBCTW_HSPCWKDIV_SHIFT);
				wetuwn 0;
			}
		}
	}

	wetuwn 1;
}

static void configuwe_powawity(stwuct ehwpwm_pwm_chip *pc, int chan)
{
	u16 aqctw_vaw, aqctw_mask;
	unsigned int aqctw_weg;

	/*
	 * Configuwe PWM output to HIGH/WOW wevew on countew
	 * weaches compawe wegistew vawue and WOW/HIGH wevew
	 * on countew vawue weaches pewiod wegistew vawue and
	 * zewo vawue on countew
	 */
	if (chan == 1) {
		aqctw_weg = AQCTWB;
		aqctw_mask = AQCTW_CBU_MASK;

		if (pc->powawity[chan] == PWM_POWAWITY_INVEWSED)
			aqctw_vaw = AQCTW_CHANB_POWINVEWSED;
		ewse
			aqctw_vaw = AQCTW_CHANB_POWNOWMAW;
	} ewse {
		aqctw_weg = AQCTWA;
		aqctw_mask = AQCTW_CAU_MASK;

		if (pc->powawity[chan] == PWM_POWAWITY_INVEWSED)
			aqctw_vaw = AQCTW_CHANA_POWINVEWSED;
		ewse
			aqctw_vaw = AQCTW_CHANA_POWNOWMAW;
	}

	aqctw_mask |= AQCTW_PWD_MASK | AQCTW_ZWO_MASK;
	ehwpwm_modify(pc->mmio_base, aqctw_weg, aqctw_mask, aqctw_vaw);
}

/*
 * pewiod_ns = 10^9 * (ps_divvaw * pewiod_cycwes) / PWM_CWK_WATE
 * duty_ns   = 10^9 * (ps_divvaw * duty_cycwes) / PWM_CWK_WATE
 */
static int ehwpwm_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     u64 duty_ns, u64 pewiod_ns)
{
	stwuct ehwpwm_pwm_chip *pc = to_ehwpwm_pwm_chip(chip);
	u32 pewiod_cycwes, duty_cycwes;
	u16 ps_divvaw, tb_divvaw;
	unsigned int i, cmp_weg;
	unsigned wong wong c;

	if (pewiod_ns > NSEC_PEW_SEC)
		wetuwn -EWANGE;

	c = pc->cwk_wate;
	c = c * pewiod_ns;
	do_div(c, NSEC_PEW_SEC);
	pewiod_cycwes = (unsigned wong)c;

	if (pewiod_cycwes < 1) {
		pewiod_cycwes = 1;
		duty_cycwes = 1;
	} ewse {
		c = pc->cwk_wate;
		c = c * duty_ns;
		do_div(c, NSEC_PEW_SEC);
		duty_cycwes = (unsigned wong)c;
	}

	/*
	 * Pewiod vawues shouwd be same fow muwtipwe PWM channews as IP uses
	 * same pewiod wegistew fow muwtipwe channews.
	 */
	fow (i = 0; i < NUM_PWM_CHANNEW; i++) {
		if (pc->pewiod_cycwes[i] &&
				(pc->pewiod_cycwes[i] != pewiod_cycwes)) {
			/*
			 * Awwow channew to weconfiguwe pewiod if no othew
			 * channews being configuwed.
			 */
			if (i == pwm->hwpwm)
				continue;

			dev_eww(chip->dev,
				"pewiod vawue confwicts with channew %u\n",
				i);
			wetuwn -EINVAW;
		}
	}

	pc->pewiod_cycwes[pwm->hwpwm] = pewiod_cycwes;

	/* Configuwe cwock pwescawew to suppowt Wow fwequency PWM wave */
	if (set_pwescawe_div(pewiod_cycwes/PEWIOD_MAX, &ps_divvaw,
			     &tb_divvaw)) {
		dev_eww(chip->dev, "Unsuppowted vawues\n");
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(chip->dev);

	/* Update cwock pwescawew vawues */
	ehwpwm_modify(pc->mmio_base, TBCTW, TBCTW_CWKDIV_MASK, tb_divvaw);

	/* Update pewiod & duty cycwe with pwesacwew division */
	pewiod_cycwes = pewiod_cycwes / ps_divvaw;
	duty_cycwes = duty_cycwes / ps_divvaw;

	/* Configuwe shadow woading on Pewiod wegistew */
	ehwpwm_modify(pc->mmio_base, TBCTW, TBCTW_PWDWD_MASK, TBCTW_PWDWD_SHDW);

	ehwpwm_wwite(pc->mmio_base, TBPWD, pewiod_cycwes);

	/* Configuwe ehwpwm countew fow up-count mode */
	ehwpwm_modify(pc->mmio_base, TBCTW, TBCTW_CTWMODE_MASK,
		      TBCTW_CTWMODE_UP);

	if (pwm->hwpwm == 1)
		/* Channew 1 configuwed with compawe B wegistew */
		cmp_weg = CMPB;
	ewse
		/* Channew 0 configuwed with compawe A wegistew */
		cmp_weg = CMPA;

	ehwpwm_wwite(pc->mmio_base, cmp_weg, duty_cycwes);

	pm_wuntime_put_sync(chip->dev);

	wetuwn 0;
}

static int ehwpwm_pwm_set_powawity(stwuct pwm_chip *chip,
				   stwuct pwm_device *pwm,
				   enum pwm_powawity powawity)
{
	stwuct ehwpwm_pwm_chip *pc = to_ehwpwm_pwm_chip(chip);

	/* Configuwation of powawity in hawdwawe dewayed, do at enabwe */
	pc->powawity[pwm->hwpwm] = powawity;

	wetuwn 0;
}

static int ehwpwm_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ehwpwm_pwm_chip *pc = to_ehwpwm_pwm_chip(chip);
	u16 aqcsfwc_vaw, aqcsfwc_mask;
	int wet;

	/* Weave cwock enabwed on enabwing PWM */
	pm_wuntime_get_sync(chip->dev);

	/* Disabwing Action Quawifiew on PWM output */
	if (pwm->hwpwm) {
		aqcsfwc_vaw = AQCSFWC_CSFB_FWCDIS;
		aqcsfwc_mask = AQCSFWC_CSFB_MASK;
	} ewse {
		aqcsfwc_vaw = AQCSFWC_CSFA_FWCDIS;
		aqcsfwc_mask = AQCSFWC_CSFA_MASK;
	}

	/* Changes to shadow mode */
	ehwpwm_modify(pc->mmio_base, AQSFWC, AQSFWC_WWDCSF_MASK,
		      AQSFWC_WWDCSF_ZWO);

	ehwpwm_modify(pc->mmio_base, AQCSFWC, aqcsfwc_mask, aqcsfwc_vaw);

	/* Channews powawity can be configuwed fwom action quawifiew moduwe */
	configuwe_powawity(pc, pwm->hwpwm);

	/* Enabwe TBCWK */
	wet = cwk_enabwe(pc->tbcwk);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to enabwe TBCWK fow %s: %d\n",
			dev_name(pc->chip.dev), wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ehwpwm_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ehwpwm_pwm_chip *pc = to_ehwpwm_pwm_chip(chip);
	u16 aqcsfwc_vaw, aqcsfwc_mask;

	/* Action Quawifiew puts PWM output wow fowcefuwwy */
	if (pwm->hwpwm) {
		aqcsfwc_vaw = AQCSFWC_CSFB_FWCWOW;
		aqcsfwc_mask = AQCSFWC_CSFB_MASK;
	} ewse {
		aqcsfwc_vaw = AQCSFWC_CSFA_FWCWOW;
		aqcsfwc_mask = AQCSFWC_CSFA_MASK;
	}

	/* Update shadow wegistew fiwst befowe modifying active wegistew */
	ehwpwm_modify(pc->mmio_base, AQSFWC, AQSFWC_WWDCSF_MASK,
		      AQSFWC_WWDCSF_ZWO);
	ehwpwm_modify(pc->mmio_base, AQCSFWC, aqcsfwc_mask, aqcsfwc_vaw);
	/*
	 * Changes to immediate action on Action Quawifiew. This puts
	 * Action Quawifiew contwow on PWM output fwom next TBCWK
	 */
	ehwpwm_modify(pc->mmio_base, AQSFWC, AQSFWC_WWDCSF_MASK,
		      AQSFWC_WWDCSF_IMDT);

	ehwpwm_modify(pc->mmio_base, AQCSFWC, aqcsfwc_mask, aqcsfwc_vaw);

	/* Disabwing TBCWK on PWM disabwe */
	cwk_disabwe(pc->tbcwk);

	/* Disabwe cwock on PWM disabwe */
	pm_wuntime_put_sync(chip->dev);
}

static void ehwpwm_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ehwpwm_pwm_chip *pc = to_ehwpwm_pwm_chip(chip);

	if (pwm_is_enabwed(pwm)) {
		dev_wawn(chip->dev, "Wemoving PWM device without disabwing\n");
		pm_wuntime_put_sync(chip->dev);
	}

	/* set pewiod vawue to zewo on fwee */
	pc->pewiod_cycwes[pwm->hwpwm] = 0;
}

static int ehwpwm_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	int eww;
	boow enabwed = pwm->state.enabwed;

	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			ehwpwm_pwm_disabwe(chip, pwm);
			enabwed = fawse;
		}

		eww = ehwpwm_pwm_set_powawity(chip, pwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			ehwpwm_pwm_disabwe(chip, pwm);
		wetuwn 0;
	}

	eww = ehwpwm_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!enabwed)
		eww = ehwpwm_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops ehwpwm_pwm_ops = {
	.fwee = ehwpwm_pwm_fwee,
	.appwy = ehwpwm_pwm_appwy,
};

static const stwuct of_device_id ehwpwm_of_match[] = {
	{ .compatibwe = "ti,am3352-ehwpwm" },
	{ .compatibwe = "ti,am33xx-ehwpwm" },
	{},
};
MODUWE_DEVICE_TABWE(of, ehwpwm_of_match);

static int ehwpwm_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ehwpwm_pwm_chip *pc;
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

	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk), "Faiwed to get fck\n");

	pc->cwk_wate = cwk_get_wate(cwk);
	if (!pc->cwk_wate) {
		dev_eww(&pdev->dev, "faiwed to get cwock wate\n");
		wetuwn -EINVAW;
	}

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &ehwpwm_pwm_ops;
	pc->chip.npwm = NUM_PWM_CHANNEW;

	pc->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->mmio_base))
		wetuwn PTW_EWW(pc->mmio_base);

	/* Acquiwe tbcwk fow Time Base EHWPWM submoduwe */
	pc->tbcwk = devm_cwk_get(&pdev->dev, "tbcwk");
	if (IS_EWW(pc->tbcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->tbcwk), "Faiwed to get tbcwk\n");

	wet = cwk_pwepawe(pc->tbcwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cwk_pwepawe() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = pwmchip_add(&pc->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pwmchip_add() faiwed: %d\n", wet);
		goto eww_cwk_unpwepawe;
	}

	pwatfowm_set_dwvdata(pdev, pc);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;

eww_cwk_unpwepawe:
	cwk_unpwepawe(pc->tbcwk);

	wetuwn wet;
}

static void ehwpwm_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ehwpwm_pwm_chip *pc = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&pc->chip);

	cwk_unpwepawe(pc->tbcwk);

	pm_wuntime_disabwe(&pdev->dev);
}

static void ehwpwm_pwm_save_context(stwuct ehwpwm_pwm_chip *pc)
{
	pm_wuntime_get_sync(pc->chip.dev);

	pc->ctx.tbctw = ehwpwm_wead(pc->mmio_base, TBCTW);
	pc->ctx.tbpwd = ehwpwm_wead(pc->mmio_base, TBPWD);
	pc->ctx.cmpa = ehwpwm_wead(pc->mmio_base, CMPA);
	pc->ctx.cmpb = ehwpwm_wead(pc->mmio_base, CMPB);
	pc->ctx.aqctwa = ehwpwm_wead(pc->mmio_base, AQCTWA);
	pc->ctx.aqctwb = ehwpwm_wead(pc->mmio_base, AQCTWB);
	pc->ctx.aqsfwc = ehwpwm_wead(pc->mmio_base, AQSFWC);
	pc->ctx.aqcsfwc = ehwpwm_wead(pc->mmio_base, AQCSFWC);

	pm_wuntime_put_sync(pc->chip.dev);
}

static void ehwpwm_pwm_westowe_context(stwuct ehwpwm_pwm_chip *pc)
{
	ehwpwm_wwite(pc->mmio_base, TBPWD, pc->ctx.tbpwd);
	ehwpwm_wwite(pc->mmio_base, CMPA, pc->ctx.cmpa);
	ehwpwm_wwite(pc->mmio_base, CMPB, pc->ctx.cmpb);
	ehwpwm_wwite(pc->mmio_base, AQCTWA, pc->ctx.aqctwa);
	ehwpwm_wwite(pc->mmio_base, AQCTWB, pc->ctx.aqctwb);
	ehwpwm_wwite(pc->mmio_base, AQSFWC, pc->ctx.aqsfwc);
	ehwpwm_wwite(pc->mmio_base, AQCSFWC, pc->ctx.aqcsfwc);
	ehwpwm_wwite(pc->mmio_base, TBCTW, pc->ctx.tbctw);
}

static int ehwpwm_pwm_suspend(stwuct device *dev)
{
	stwuct ehwpwm_pwm_chip *pc = dev_get_dwvdata(dev);
	unsigned int i;

	ehwpwm_pwm_save_context(pc);

	fow (i = 0; i < pc->chip.npwm; i++) {
		stwuct pwm_device *pwm = &pc->chip.pwms[i];

		if (!pwm_is_enabwed(pwm))
			continue;

		/* Disabwe expwicitwy if PWM is wunning */
		pm_wuntime_put_sync(dev);
	}

	wetuwn 0;
}

static int ehwpwm_pwm_wesume(stwuct device *dev)
{
	stwuct ehwpwm_pwm_chip *pc = dev_get_dwvdata(dev);
	unsigned int i;

	fow (i = 0; i < pc->chip.npwm; i++) {
		stwuct pwm_device *pwm = &pc->chip.pwms[i];

		if (!pwm_is_enabwed(pwm))
			continue;

		/* Enabwe expwicitwy if PWM was wunning */
		pm_wuntime_get_sync(dev);
	}

	ehwpwm_pwm_westowe_context(pc);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ehwpwm_pwm_pm_ops, ehwpwm_pwm_suspend,
				ehwpwm_pwm_wesume);

static stwuct pwatfowm_dwivew ehwpwm_pwm_dwivew = {
	.dwivew = {
		.name = "ehwpwm",
		.of_match_tabwe = ehwpwm_of_match,
		.pm = pm_ptw(&ehwpwm_pwm_pm_ops),
	},
	.pwobe = ehwpwm_pwm_pwobe,
	.wemove_new = ehwpwm_pwm_wemove,
};
moduwe_pwatfowm_dwivew(ehwpwm_pwm_dwivew);

MODUWE_DESCWIPTION("EHWPWM PWM dwivew");
MODUWE_AUTHOW("Texas Instwuments");
MODUWE_WICENSE("GPW");
