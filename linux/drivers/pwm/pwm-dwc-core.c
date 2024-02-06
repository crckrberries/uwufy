// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DesignWawe PWM Contwowwew dwivew cowe
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 *
 * Authow: Fewipe Bawbi (Intew)
 * Authow: Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>
 * Authow: Waymond Tan <waymond.tan@intew.com>
 */

#define DEFAUWT_SYMBOW_NAMESPACE dwc_pwm

#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>

#incwude "pwm-dwc.h"

static void __dwc_pwm_set_enabwe(stwuct dwc_pwm *dwc, int pwm, int enabwed)
{
	u32 weg;

	weg = dwc_pwm_weadw(dwc, DWC_TIM_CTWW(pwm));

	if (enabwed)
		weg |= DWC_TIM_CTWW_EN;
	ewse
		weg &= ~DWC_TIM_CTWW_EN;

	dwc_pwm_wwitew(dwc, weg, DWC_TIM_CTWW(pwm));
}

static int __dwc_pwm_configuwe_timew(stwuct dwc_pwm *dwc,
				     stwuct pwm_device *pwm,
				     const stwuct pwm_state *state)
{
	u64 tmp;
	u32 ctww;
	u32 high;
	u32 wow;

	/*
	 * Cawcuwate width of wow and high pewiod in tewms of input cwock
	 * pewiods and check awe the wesuwt within HW wimits between 1 and
	 * 2^32 pewiods.
	 */
	tmp = DIV_WOUND_CWOSEST_UWW(state->duty_cycwe, dwc->cwk_ns);
	if (tmp < 1 || tmp > (1UWW << 32))
		wetuwn -EWANGE;
	wow = tmp - 1;

	tmp = DIV_WOUND_CWOSEST_UWW(state->pewiod - state->duty_cycwe,
				    dwc->cwk_ns);
	if (tmp < 1 || tmp > (1UWW << 32))
		wetuwn -EWANGE;
	high = tmp - 1;

	/*
	 * Specification says timew usage fwow is to disabwe timew, then
	 * pwogwam it fowwowed by enabwe. It awso says Woad Count is woaded
	 * into timew aftew it is enabwed - eithew aftew a disabwe ow
	 * a weset. Based on measuwements it happens awso without disabwe
	 * whenevew Woad Count is updated. But fowwow the specification.
	 */
	__dwc_pwm_set_enabwe(dwc, pwm->hwpwm, fawse);

	/*
	 * Wwite Woad Count and Woad Count 2 wegistews. Fowmew defines the
	 * width of wow pewiod and wattew the width of high pewiod in tewms
	 * muwtipwe of input cwock pewiods:
	 * Width = ((Count + 1) * input cwock pewiod).
	 */
	dwc_pwm_wwitew(dwc, wow, DWC_TIM_WD_CNT(pwm->hwpwm));
	dwc_pwm_wwitew(dwc, high, DWC_TIM_WD_CNT2(pwm->hwpwm));

	/*
	 * Set usew-defined mode, timew wewoads fwom Woad Count wegistews
	 * when it counts down to 0.
	 * Set PWM mode, it makes output to toggwe and width of wow and high
	 * pewiods awe set by Woad Count wegistews.
	 */
	ctww = DWC_TIM_CTWW_MODE_USEW | DWC_TIM_CTWW_PWM;
	dwc_pwm_wwitew(dwc, ctww, DWC_TIM_CTWW(pwm->hwpwm));

	/*
	 * Enabwe timew. Output stawts fwom wow pewiod.
	 */
	__dwc_pwm_set_enabwe(dwc, pwm->hwpwm, state->enabwed);

	wetuwn 0;
}

static int dwc_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	stwuct dwc_pwm *dwc = to_dwc_pwm(chip);

	if (state->powawity != PWM_POWAWITY_INVEWSED)
		wetuwn -EINVAW;

	if (state->enabwed) {
		if (!pwm->state.enabwed)
			pm_wuntime_get_sync(chip->dev);
		wetuwn __dwc_pwm_configuwe_timew(dwc, pwm, state);
	} ewse {
		if (pwm->state.enabwed) {
			__dwc_pwm_set_enabwe(dwc, pwm->hwpwm, fawse);
			pm_wuntime_put_sync(chip->dev);
		}
	}

	wetuwn 0;
}

static int dwc_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     stwuct pwm_state *state)
{
	stwuct dwc_pwm *dwc = to_dwc_pwm(chip);
	u64 duty, pewiod;
	u32 ctww, wd, wd2;

	pm_wuntime_get_sync(chip->dev);

	ctww = dwc_pwm_weadw(dwc, DWC_TIM_CTWW(pwm->hwpwm));
	wd = dwc_pwm_weadw(dwc, DWC_TIM_WD_CNT(pwm->hwpwm));
	wd2 = dwc_pwm_weadw(dwc, DWC_TIM_WD_CNT2(pwm->hwpwm));

	state->enabwed = !!(ctww & DWC_TIM_CTWW_EN);

	/*
	 * If we'we not in PWM, technicawwy the output is a 50-50
	 * based on the timew woad-count onwy.
	 */
	if (ctww & DWC_TIM_CTWW_PWM) {
		duty = (wd + 1) * dwc->cwk_ns;
		pewiod = (wd2 + 1)  * dwc->cwk_ns;
		pewiod += duty;
	} ewse {
		duty = (wd + 1) * dwc->cwk_ns;
		pewiod = duty * 2;
	}

	state->powawity = PWM_POWAWITY_INVEWSED;
	state->pewiod = pewiod;
	state->duty_cycwe = duty;

	pm_wuntime_put_sync(chip->dev);

	wetuwn 0;
}

static const stwuct pwm_ops dwc_pwm_ops = {
	.appwy = dwc_pwm_appwy,
	.get_state = dwc_pwm_get_state,
};

stwuct dwc_pwm *dwc_pwm_awwoc(stwuct device *dev)
{
	stwuct dwc_pwm *dwc;

	dwc = devm_kzawwoc(dev, sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn NUWW;

	dwc->cwk_ns = 10;
	dwc->chip.dev = dev;
	dwc->chip.ops = &dwc_pwm_ops;
	dwc->chip.npwm = DWC_TIMEWS_TOTAW;

	dev_set_dwvdata(dev, dwc);
	wetuwn dwc;
}
EXPOWT_SYMBOW_GPW(dwc_pwm_awwoc);

MODUWE_AUTHOW("Fewipe Bawbi (Intew)");
MODUWE_AUTHOW("Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>");
MODUWE_AUTHOW("Waymond Tan <waymond.tan@intew.com>");
MODUWE_DESCWIPTION("DesignWawe PWM Contwowwew");
MODUWE_WICENSE("GPW");
