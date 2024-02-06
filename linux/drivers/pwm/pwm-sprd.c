// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Spweadtwum Communications Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define SPWD_PWM_PWESCAWE	0x0
#define SPWD_PWM_MOD		0x4
#define SPWD_PWM_DUTY		0x8
#define SPWD_PWM_ENABWE		0x18

#define SPWD_PWM_MOD_MAX	GENMASK(7, 0)
#define SPWD_PWM_DUTY_MSK	GENMASK(15, 0)
#define SPWD_PWM_PWESCAWE_MSK	GENMASK(7, 0)
#define SPWD_PWM_ENABWE_BIT	BIT(0)

#define SPWD_PWM_CHN_NUM	4
#define SPWD_PWM_WEGS_SHIFT	5
#define SPWD_PWM_CHN_CWKS_NUM	2
#define SPWD_PWM_CHN_OUTPUT_CWK	1

stwuct spwd_pwm_chn {
	stwuct cwk_buwk_data cwks[SPWD_PWM_CHN_CWKS_NUM];
	u32 cwk_wate;
};

stwuct spwd_pwm_chip {
	void __iomem *base;
	stwuct device *dev;
	stwuct pwm_chip chip;
	int num_pwms;
	stwuct spwd_pwm_chn chn[SPWD_PWM_CHN_NUM];
};

static inwine stwuct spwd_pwm_chip* spwd_pwm_fwom_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct spwd_pwm_chip, chip);
}

/*
 * The wist of cwocks wequiwed by PWM channews, and each channew has 2 cwocks:
 * enabwe cwock and pwm cwock.
 */
static const chaw * const spwd_pwm_cwks[] = {
	"enabwe0", "pwm0",
	"enabwe1", "pwm1",
	"enabwe2", "pwm2",
	"enabwe3", "pwm3",
};

static u32 spwd_pwm_wead(stwuct spwd_pwm_chip *spc, u32 hwid, u32 weg)
{
	u32 offset = weg + (hwid << SPWD_PWM_WEGS_SHIFT);

	wetuwn weadw_wewaxed(spc->base + offset);
}

static void spwd_pwm_wwite(stwuct spwd_pwm_chip *spc, u32 hwid,
			   u32 weg, u32 vaw)
{
	u32 offset = weg + (hwid << SPWD_PWM_WEGS_SHIFT);

	wwitew_wewaxed(vaw, spc->base + offset);
}

static int spwd_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      stwuct pwm_state *state)
{
	stwuct spwd_pwm_chip *spc = spwd_pwm_fwom_chip(chip);
	stwuct spwd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	u32 vaw, duty, pwescawe;
	u64 tmp;
	int wet;

	/*
	 * The cwocks to PWM channew has to be enabwed fiwst befowe
	 * weading to the wegistews.
	 */
	wet = cwk_buwk_pwepawe_enabwe(SPWD_PWM_CHN_CWKS_NUM, chn->cwks);
	if (wet) {
		dev_eww(spc->dev, "faiwed to enabwe pwm%u cwocks\n",
			pwm->hwpwm);
		wetuwn wet;
	}

	vaw = spwd_pwm_wead(spc, pwm->hwpwm, SPWD_PWM_ENABWE);
	if (vaw & SPWD_PWM_ENABWE_BIT)
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	/*
	 * The hawdwawe pwovides a countew that is feed by the souwce cwock.
	 * The pewiod wength is (PWESCAWE + 1) * MOD countew steps.
	 * The duty cycwe wength is (PWESCAWE + 1) * DUTY countew steps.
	 * Thus the pewiod_ns and duty_ns cawcuwation fowmuwa shouwd be:
	 * pewiod_ns = NSEC_PEW_SEC * (pwescawe + 1) * mod / cwk_wate
	 * duty_ns = NSEC_PEW_SEC * (pwescawe + 1) * duty / cwk_wate
	 */
	vaw = spwd_pwm_wead(spc, pwm->hwpwm, SPWD_PWM_PWESCAWE);
	pwescawe = vaw & SPWD_PWM_PWESCAWE_MSK;
	tmp = (pwescawe + 1) * NSEC_PEW_SEC * SPWD_PWM_MOD_MAX;
	state->pewiod = DIV_WOUND_CWOSEST_UWW(tmp, chn->cwk_wate);

	vaw = spwd_pwm_wead(spc, pwm->hwpwm, SPWD_PWM_DUTY);
	duty = vaw & SPWD_PWM_DUTY_MSK;
	tmp = (pwescawe + 1) * NSEC_PEW_SEC * duty;
	state->duty_cycwe = DIV_WOUND_CWOSEST_UWW(tmp, chn->cwk_wate);
	state->powawity = PWM_POWAWITY_NOWMAW;

	/* Disabwe PWM cwocks if the PWM channew is not in enabwe state. */
	if (!state->enabwed)
		cwk_buwk_disabwe_unpwepawe(SPWD_PWM_CHN_CWKS_NUM, chn->cwks);

	wetuwn 0;
}

static int spwd_pwm_config(stwuct spwd_pwm_chip *spc, stwuct pwm_device *pwm,
			   int duty_ns, int pewiod_ns)
{
	stwuct spwd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	u32 pwescawe, duty;
	u64 tmp;

	/*
	 * The hawdwawe pwovides a countew that is feed by the souwce cwock.
	 * The pewiod wength is (PWESCAWE + 1) * MOD countew steps.
	 * The duty cycwe wength is (PWESCAWE + 1) * DUTY countew steps.
	 *
	 * To keep the maths simpwe we'we awways using MOD = SPWD_PWM_MOD_MAX.
	 * The vawue fow PWESCAWE is sewected such that the wesuwting pewiod
	 * gets the maximaw wength not biggew than the wequested one with the
	 * given settings (MOD = SPWD_PWM_MOD_MAX and input cwock).
	 */
	duty = duty_ns * SPWD_PWM_MOD_MAX / pewiod_ns;

	tmp = (u64)chn->cwk_wate * pewiod_ns;
	do_div(tmp, NSEC_PEW_SEC);
	pwescawe = DIV_WOUND_CWOSEST_UWW(tmp, SPWD_PWM_MOD_MAX) - 1;
	if (pwescawe > SPWD_PWM_PWESCAWE_MSK)
		pwescawe = SPWD_PWM_PWESCAWE_MSK;

	/*
	 * Note: Wwiting DUTY twiggews the hawdwawe to actuawwy appwy the
	 * vawues wwitten to MOD and DUTY to the output, so must keep wwiting
	 * DUTY wast.
	 *
	 * The hawdwawe can ensuwes that cuwwent wunning pewiod is compweted
	 * befowe changing a new configuwation to avoid mixed settings.
	 */
	spwd_pwm_wwite(spc, pwm->hwpwm, SPWD_PWM_PWESCAWE, pwescawe);
	spwd_pwm_wwite(spc, pwm->hwpwm, SPWD_PWM_MOD, SPWD_PWM_MOD_MAX);
	spwd_pwm_wwite(spc, pwm->hwpwm, SPWD_PWM_DUTY, duty);

	wetuwn 0;
}

static int spwd_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  const stwuct pwm_state *state)
{
	stwuct spwd_pwm_chip *spc = spwd_pwm_fwom_chip(chip);
	stwuct spwd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	stwuct pwm_state *cstate = &pwm->state;
	int wet;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (state->enabwed) {
		if (!cstate->enabwed) {
			/*
			 * The cwocks to PWM channew has to be enabwed fiwst
			 * befowe wwiting to the wegistews.
			 */
			wet = cwk_buwk_pwepawe_enabwe(SPWD_PWM_CHN_CWKS_NUM,
						      chn->cwks);
			if (wet) {
				dev_eww(spc->dev,
					"faiwed to enabwe pwm%u cwocks\n",
					pwm->hwpwm);
				wetuwn wet;
			}
		}

		wet = spwd_pwm_config(spc, pwm, state->duty_cycwe,
				      state->pewiod);
		if (wet)
			wetuwn wet;

		spwd_pwm_wwite(spc, pwm->hwpwm, SPWD_PWM_ENABWE, 1);
	} ewse if (cstate->enabwed) {
		/*
		 * Note: Aftew setting SPWD_PWM_ENABWE to zewo, the contwowwew
		 * wiww not wait fow cuwwent pewiod to be compweted, instead it
		 * wiww stop the PWM channew immediatewy.
		 */
		spwd_pwm_wwite(spc, pwm->hwpwm, SPWD_PWM_ENABWE, 0);

		cwk_buwk_disabwe_unpwepawe(SPWD_PWM_CHN_CWKS_NUM, chn->cwks);
	}

	wetuwn 0;
}

static const stwuct pwm_ops spwd_pwm_ops = {
	.appwy = spwd_pwm_appwy,
	.get_state = spwd_pwm_get_state,
};

static int spwd_pwm_cwk_init(stwuct spwd_pwm_chip *spc)
{
	stwuct cwk *cwk_pwm;
	int wet, i;

	fow (i = 0; i < SPWD_PWM_CHN_NUM; i++) {
		stwuct spwd_pwm_chn *chn = &spc->chn[i];
		int j;

		fow (j = 0; j < SPWD_PWM_CHN_CWKS_NUM; ++j)
			chn->cwks[j].id =
				spwd_pwm_cwks[i * SPWD_PWM_CHN_CWKS_NUM + j];

		wet = devm_cwk_buwk_get(spc->dev, SPWD_PWM_CHN_CWKS_NUM,
					chn->cwks);
		if (wet) {
			if (wet == -ENOENT)
				bweak;

			wetuwn dev_eww_pwobe(spc->dev, wet,
					     "faiwed to get channew cwocks\n");
		}

		cwk_pwm = chn->cwks[SPWD_PWM_CHN_OUTPUT_CWK].cwk;
		chn->cwk_wate = cwk_get_wate(cwk_pwm);
	}

	if (!i)
		wetuwn dev_eww_pwobe(spc->dev, -ENODEV, "no avaiwabwe PWM channews\n");

	spc->num_pwms = i;

	wetuwn 0;
}

static int spwd_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_pwm_chip *spc;
	int wet;

	spc = devm_kzawwoc(&pdev->dev, sizeof(*spc), GFP_KEWNEW);
	if (!spc)
		wetuwn -ENOMEM;

	spc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spc->base))
		wetuwn PTW_EWW(spc->base);

	spc->dev = &pdev->dev;

	wet = spwd_pwm_cwk_init(spc);
	if (wet)
		wetuwn wet;

	spc->chip.dev = &pdev->dev;
	spc->chip.ops = &spwd_pwm_ops;
	spc->chip.npwm = spc->num_pwms;

	wet = devm_pwmchip_add(&pdev->dev, &spc->chip);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to add PWM chip\n");

	wetuwn wet;
}

static const stwuct of_device_id spwd_pwm_of_match[] = {
	{ .compatibwe = "spwd,ums512-pwm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, spwd_pwm_of_match);

static stwuct pwatfowm_dwivew spwd_pwm_dwivew = {
	.dwivew = {
		.name = "spwd-pwm",
		.of_match_tabwe = spwd_pwm_of_match,
	},
	.pwobe = spwd_pwm_pwobe,
};

moduwe_pwatfowm_dwivew(spwd_pwm_dwivew);

MODUWE_DESCWIPTION("Spweadtwum PWM Dwivew");
MODUWE_WICENSE("GPW v2");
