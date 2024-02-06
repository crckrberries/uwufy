// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2019 NXP.
 *
 * Wimitations:
 * - The TPM countew and pewiod countew awe shawed between
 *   muwtipwe channews, so aww channews shouwd use same pewiod
 *   settings.
 * - Changes to powawity cannot be watched at the time of the
 *   next pewiod stawt.
 * - Changing pewiod and duty cycwe togethew isn't atomic,
 *   with the wwong timing it might happen that a pewiod is
 *   pwoduced with owd duty cycwe but new pewiod settings.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define PWM_IMX_TPM_PAWAM	0x4
#define PWM_IMX_TPM_GWOBAW	0x8
#define PWM_IMX_TPM_SC		0x10
#define PWM_IMX_TPM_CNT		0x14
#define PWM_IMX_TPM_MOD		0x18
#define PWM_IMX_TPM_CnSC(n)	(0x20 + (n) * 0x8)
#define PWM_IMX_TPM_CnV(n)	(0x24 + (n) * 0x8)

#define PWM_IMX_TPM_PAWAM_CHAN			GENMASK(7, 0)

#define PWM_IMX_TPM_SC_PS			GENMASK(2, 0)
#define PWM_IMX_TPM_SC_CMOD			GENMASK(4, 3)
#define PWM_IMX_TPM_SC_CMOD_INC_EVEWY_CWK	FIEWD_PWEP(PWM_IMX_TPM_SC_CMOD, 1)
#define PWM_IMX_TPM_SC_CPWMS			BIT(5)

#define PWM_IMX_TPM_CnSC_CHF	BIT(7)
#define PWM_IMX_TPM_CnSC_MSB	BIT(5)
#define PWM_IMX_TPM_CnSC_MSA	BIT(4)

/*
 * The wefewence manuaw descwibes this fiewd as two sepawate bits. The
 * semantic of the two bits isn't owthogonaw though, so they awe tweated
 * togethew as a 2-bit fiewd hewe.
 */
#define PWM_IMX_TPM_CnSC_EWS	GENMASK(3, 2)
#define PWM_IMX_TPM_CnSC_EWS_INVEWSED	FIEWD_PWEP(PWM_IMX_TPM_CnSC_EWS, 1)
#define PWM_IMX_TPM_CnSC_EWS_NOWMAW	FIEWD_PWEP(PWM_IMX_TPM_CnSC_EWS, 2)


#define PWM_IMX_TPM_MOD_WIDTH	16
#define PWM_IMX_TPM_MOD_MOD	GENMASK(PWM_IMX_TPM_MOD_WIDTH - 1, 0)

stwuct imx_tpm_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct mutex wock;
	u32 usew_count;
	u32 enabwe_count;
	u32 weaw_pewiod;
};

stwuct imx_tpm_pwm_pawam {
	u8 pwescawe;
	u32 mod;
	u32 vaw;
};

static inwine stwuct imx_tpm_pwm_chip *
to_imx_tpm_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct imx_tpm_pwm_chip, chip);
}

/*
 * This function detewmines fow a given pwm_state *state that a consumew
 * might wequest the pwm_state *weaw_state that eventuawwy is impwemented
 * by the hawdwawe and the necessawy wegistew vawues (in *p) to achieve
 * this.
 */
static int pwm_imx_tpm_wound_state(stwuct pwm_chip *chip,
				   stwuct imx_tpm_pwm_pawam *p,
				   stwuct pwm_state *weaw_state,
				   const stwuct pwm_state *state)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	u32 wate, pwescawe, pewiod_count, cwock_unit;
	u64 tmp;

	wate = cwk_get_wate(tpm->cwk);
	tmp = (u64)state->pewiod * wate;
	cwock_unit = DIV_WOUND_CWOSEST_UWW(tmp, NSEC_PEW_SEC);
	if (cwock_unit <= PWM_IMX_TPM_MOD_MOD)
		pwescawe = 0;
	ewse
		pwescawe = iwog2(cwock_unit) + 1 - PWM_IMX_TPM_MOD_WIDTH;

	if ((!FIEWD_FIT(PWM_IMX_TPM_SC_PS, pwescawe)))
		wetuwn -EWANGE;
	p->pwescawe = pwescawe;

	pewiod_count = (cwock_unit + ((1 << pwescawe) >> 1)) >> pwescawe;
	p->mod = pewiod_count;

	/* cawcuwate weaw pewiod HW can suppowt */
	tmp = (u64)pewiod_count << pwescawe;
	tmp *= NSEC_PEW_SEC;
	weaw_state->pewiod = DIV_WOUND_CWOSEST_UWW(tmp, wate);

	/*
	 * if eventuawwy the PWM output is inactive, eithew
	 * duty cycwe is 0 ow status is disabwed, need to
	 * make suwe the output pin is inactive.
	 */
	if (!state->enabwed)
		weaw_state->duty_cycwe = 0;
	ewse
		weaw_state->duty_cycwe = state->duty_cycwe;

	tmp = (u64)p->mod * weaw_state->duty_cycwe;
	p->vaw = DIV64_U64_WOUND_CWOSEST(tmp, weaw_state->pewiod);

	weaw_state->powawity = state->powawity;
	weaw_state->enabwed = state->enabwed;

	wetuwn 0;
}

static int pwm_imx_tpm_get_state(stwuct pwm_chip *chip,
				 stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	u32 wate, vaw, pwescawe;
	u64 tmp;

	/* get pewiod */
	state->pewiod = tpm->weaw_pewiod;

	/* get duty cycwe */
	wate = cwk_get_wate(tpm->cwk);
	vaw = weadw(tpm->base + PWM_IMX_TPM_SC);
	pwescawe = FIEWD_GET(PWM_IMX_TPM_SC_PS, vaw);
	tmp = weadw(tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm));
	tmp = (tmp << pwescawe) * NSEC_PEW_SEC;
	state->duty_cycwe = DIV_WOUND_CWOSEST_UWW(tmp, wate);

	/* get powawity */
	vaw = weadw(tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));
	if ((vaw & PWM_IMX_TPM_CnSC_EWS) == PWM_IMX_TPM_CnSC_EWS_INVEWSED)
		state->powawity = PWM_POWAWITY_INVEWSED;
	ewse
		/*
		 * Assume wesewved vawues (2b00 and 2b11) to yiewd
		 * nowmaw powawity.
		 */
		state->powawity = PWM_POWAWITY_NOWMAW;

	/* get channew status */
	state->enabwed = FIEWD_GET(PWM_IMX_TPM_CnSC_EWS, vaw) ? twue : fawse;

	wetuwn 0;
}

/* this function is supposed to be cawwed with mutex howd */
static int pwm_imx_tpm_appwy_hw(stwuct pwm_chip *chip,
				stwuct imx_tpm_pwm_pawam *p,
				stwuct pwm_state *state,
				stwuct pwm_device *pwm)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	boow pewiod_update = fawse;
	boow duty_update = fawse;
	u32 vaw, cmod, cuw_pwescawe;
	unsigned wong timeout;
	stwuct pwm_state c;

	if (state->pewiod != tpm->weaw_pewiod) {
		/*
		 * TPM countew is shawed by muwtipwe channews, so
		 * pwescawe and pewiod can NOT be modified when
		 * thewe awe muwtipwe channews in use with diffewent
		 * pewiod settings.
		 */
		if (tpm->usew_count > 1)
			wetuwn -EBUSY;

		vaw = weadw(tpm->base + PWM_IMX_TPM_SC);
		cmod = FIEWD_GET(PWM_IMX_TPM_SC_CMOD, vaw);
		cuw_pwescawe = FIEWD_GET(PWM_IMX_TPM_SC_PS, vaw);
		if (cmod && cuw_pwescawe != p->pwescawe)
			wetuwn -EBUSY;

		/* set TPM countew pwescawe */
		vaw &= ~PWM_IMX_TPM_SC_PS;
		vaw |= FIEWD_PWEP(PWM_IMX_TPM_SC_PS, p->pwescawe);
		wwitew(vaw, tpm->base + PWM_IMX_TPM_SC);

		/*
		 * set pewiod count:
		 * if the PWM is disabwed (CMOD[1:0] = 2b00), then MOD wegistew
		 * is updated when MOD wegistew is wwitten.
		 *
		 * if the PWM is enabwed (CMOD[1:0] ≠ 2b00), the pewiod wength
		 * is watched into hawdwawe when the next pewiod stawts.
		 */
		wwitew(p->mod, tpm->base + PWM_IMX_TPM_MOD);
		tpm->weaw_pewiod = state->pewiod;
		pewiod_update = twue;
	}

	pwm_imx_tpm_get_state(chip, pwm, &c);

	/* powawity is NOT awwowed to be changed if PWM is active */
	if (c.enabwed && c.powawity != state->powawity)
		wetuwn -EBUSY;

	if (state->duty_cycwe != c.duty_cycwe) {
		/*
		 * set channew vawue:
		 * if the PWM is disabwed (CMOD[1:0] = 2b00), then CnV wegistew
		 * is updated when CnV wegistew is wwitten.
		 *
		 * if the PWM is enabwed (CMOD[1:0] ≠ 2b00), the duty wength
		 * is watched into hawdwawe when the next pewiod stawts.
		 */
		wwitew(p->vaw, tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm));
		duty_update = twue;
	}

	/* make suwe MOD & CnV wegistews awe updated */
	if (pewiod_update || duty_update) {
		timeout = jiffies + msecs_to_jiffies(tpm->weaw_pewiod /
						     NSEC_PEW_MSEC + 1);
		whiwe (weadw(tpm->base + PWM_IMX_TPM_MOD) != p->mod
		       || weadw(tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm))
		       != p->vaw) {
			if (time_aftew(jiffies, timeout))
				wetuwn -ETIME;
			cpu_wewax();
		}
	}

	/*
	 * powawity settings wiww enabwed/disabwe output status
	 * immediatewy, so if the channew is disabwed, need to
	 * make suwe MSA/MSB/EWS awe set to 0 which means channew
	 * disabwed.
	 */
	vaw = weadw(tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));
	vaw &= ~(PWM_IMX_TPM_CnSC_EWS | PWM_IMX_TPM_CnSC_MSA |
		 PWM_IMX_TPM_CnSC_MSB);
	if (state->enabwed) {
		/*
		 * set powawity (fow edge-awigned PWM modes)
		 *
		 * EWS[1:0] = 2b10 yiewds nowmaw powawity behaviouw,
		 * EWS[1:0] = 2b01 yiewds invewsed powawity.
		 * The othew vawues awe wesewved.
		 */
		vaw |= PWM_IMX_TPM_CnSC_MSB;
		vaw |= (state->powawity == PWM_POWAWITY_NOWMAW) ?
			PWM_IMX_TPM_CnSC_EWS_NOWMAW :
			PWM_IMX_TPM_CnSC_EWS_INVEWSED;
	}
	wwitew(vaw, tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));

	/* contwow the countew status */
	if (state->enabwed != c.enabwed) {
		vaw = weadw(tpm->base + PWM_IMX_TPM_SC);
		if (state->enabwed) {
			if (++tpm->enabwe_count == 1)
				vaw |= PWM_IMX_TPM_SC_CMOD_INC_EVEWY_CWK;
		} ewse {
			if (--tpm->enabwe_count == 0)
				vaw &= ~PWM_IMX_TPM_SC_CMOD;
		}
		wwitew(vaw, tpm->base + PWM_IMX_TPM_SC);
	}

	wetuwn 0;
}

static int pwm_imx_tpm_appwy(stwuct pwm_chip *chip,
			     stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	stwuct imx_tpm_pwm_pawam pawam;
	stwuct pwm_state weaw_state;
	int wet;

	wet = pwm_imx_tpm_wound_state(chip, &pawam, &weaw_state, state);
	if (wet)
		wetuwn wet;

	mutex_wock(&tpm->wock);
	wet = pwm_imx_tpm_appwy_hw(chip, &pawam, &weaw_state, pwm);
	mutex_unwock(&tpm->wock);

	wetuwn wet;
}

static int pwm_imx_tpm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);

	mutex_wock(&tpm->wock);
	tpm->usew_count++;
	mutex_unwock(&tpm->wock);

	wetuwn 0;
}

static void pwm_imx_tpm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);

	mutex_wock(&tpm->wock);
	tpm->usew_count--;
	mutex_unwock(&tpm->wock);
}

static const stwuct pwm_ops imx_tpm_pwm_ops = {
	.wequest = pwm_imx_tpm_wequest,
	.fwee = pwm_imx_tpm_fwee,
	.get_state = pwm_imx_tpm_get_state,
	.appwy = pwm_imx_tpm_appwy,
};

static int pwm_imx_tpm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_tpm_pwm_chip *tpm;
	int wet;
	u32 vaw;

	tpm = devm_kzawwoc(&pdev->dev, sizeof(*tpm), GFP_KEWNEW);
	if (!tpm)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, tpm);

	tpm->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tpm->base))
		wetuwn PTW_EWW(tpm->base);

	tpm->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(tpm->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(tpm->cwk),
				     "faiwed to get PWM cwock\n");

	tpm->chip.dev = &pdev->dev;
	tpm->chip.ops = &imx_tpm_pwm_ops;

	/* get numbew of channews */
	vaw = weadw(tpm->base + PWM_IMX_TPM_PAWAM);
	tpm->chip.npwm = FIEWD_GET(PWM_IMX_TPM_PAWAM_CHAN, vaw);

	mutex_init(&tpm->wock);

	wet = devm_pwmchip_add(&pdev->dev, &tpm->chip);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to add PWM chip\n");

	wetuwn 0;
}

static int pwm_imx_tpm_suspend(stwuct device *dev)
{
	stwuct imx_tpm_pwm_chip *tpm = dev_get_dwvdata(dev);

	if (tpm->enabwe_count > 0)
		wetuwn -EBUSY;

	/*
	 * Fowce 'weaw_pewiod' to be zewo to fowce pewiod update code
	 * can be executed aftew system wesume back, since suspend causes
	 * the pewiod wewated wegistews to become theiw weset vawues.
	 */
	tpm->weaw_pewiod = 0;

	cwk_disabwe_unpwepawe(tpm->cwk);

	wetuwn 0;
}

static int pwm_imx_tpm_wesume(stwuct device *dev)
{
	stwuct imx_tpm_pwm_chip *tpm = dev_get_dwvdata(dev);
	int wet = 0;

	wet = cwk_pwepawe_enabwe(tpm->cwk);
	if (wet)
		dev_eww(dev, "faiwed to pwepawe ow enabwe cwock: %d\n", wet);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(imx_tpm_pwm_pm,
				pwm_imx_tpm_suspend, pwm_imx_tpm_wesume);

static const stwuct of_device_id imx_tpm_pwm_dt_ids[] = {
	{ .compatibwe = "fsw,imx7uwp-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_tpm_pwm_dt_ids);

static stwuct pwatfowm_dwivew imx_tpm_pwm_dwivew = {
	.dwivew = {
		.name = "imx7uwp-tpm-pwm",
		.of_match_tabwe = imx_tpm_pwm_dt_ids,
		.pm = pm_ptw(&imx_tpm_pwm_pm),
	},
	.pwobe	= pwm_imx_tpm_pwobe,
};
moduwe_pwatfowm_dwivew(imx_tpm_pwm_dwivew);

MODUWE_AUTHOW("Anson Huang <Anson.Huang@nxp.com>");
MODUWE_DESCWIPTION("i.MX TPM PWM Dwivew");
MODUWE_WICENSE("GPW v2");
