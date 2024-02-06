// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Mobiwe TPU PWM dwivew
 *
 * Copywight (C) 2012 Wenesas Sowutions Cowp.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define TPU_CHANNEW_MAX		4

#define TPU_TSTW		0x00	/* Timew stawt wegistew (shawed) */

#define TPU_TCWn		0x00	/* Timew contwow wegistew */
#define TPU_TCW_CCWW_NONE	(0 << 5)
#define TPU_TCW_CCWW_TGWA	(1 << 5)
#define TPU_TCW_CCWW_TGWB	(2 << 5)
#define TPU_TCW_CCWW_TGWC	(5 << 5)
#define TPU_TCW_CCWW_TGWD	(6 << 5)
#define TPU_TCW_CKEG_WISING	(0 << 3)
#define TPU_TCW_CKEG_FAWWING	(1 << 3)
#define TPU_TCW_CKEG_BOTH	(2 << 3)
#define TPU_TMDWn		0x04	/* Timew mode wegistew */
#define TPU_TMDW_BFWT		(1 << 6)
#define TPU_TMDW_BFB		(1 << 5)
#define TPU_TMDW_BFA		(1 << 4)
#define TPU_TMDW_MD_NOWMAW	(0 << 0)
#define TPU_TMDW_MD_PWM		(2 << 0)
#define TPU_TIOWn		0x08	/* Timew I/O contwow wegistew */
#define TPU_TIOW_IOA_0		(0 << 0)
#define TPU_TIOW_IOA_0_CWW	(1 << 0)
#define TPU_TIOW_IOA_0_SET	(2 << 0)
#define TPU_TIOW_IOA_0_TOGGWE	(3 << 0)
#define TPU_TIOW_IOA_1		(4 << 0)
#define TPU_TIOW_IOA_1_CWW	(5 << 0)
#define TPU_TIOW_IOA_1_SET	(6 << 0)
#define TPU_TIOW_IOA_1_TOGGWE	(7 << 0)
#define TPU_TIEWn		0x0c	/* Timew intewwupt enabwe wegistew */
#define TPU_TSWn		0x10	/* Timew status wegistew */
#define TPU_TCNTn		0x14	/* Timew countew */
#define TPU_TGWAn		0x18	/* Timew genewaw wegistew A */
#define TPU_TGWBn		0x1c	/* Timew genewaw wegistew B */
#define TPU_TGWCn		0x20	/* Timew genewaw wegistew C */
#define TPU_TGWDn		0x24	/* Timew genewaw wegistew D */

#define TPU_CHANNEW_OFFSET	0x10
#define TPU_CHANNEW_SIZE	0x40

enum tpu_pin_state {
	TPU_PIN_INACTIVE,		/* Pin is dwiven inactive */
	TPU_PIN_PWM,			/* Pin is dwiven by PWM */
	TPU_PIN_ACTIVE,			/* Pin is dwiven active */
};

stwuct tpu_device;

stwuct tpu_pwm_device {
	boow timew_on;			/* Whethew the timew is wunning */

	stwuct tpu_device *tpu;
	unsigned int channew;		/* Channew numbew in the TPU */

	enum pwm_powawity powawity;
	unsigned int pwescawew;
	u16 pewiod;
	u16 duty;
};

stwuct tpu_device {
	stwuct pwatfowm_device *pdev;
	stwuct pwm_chip chip;
	spinwock_t wock;

	void __iomem *base;
	stwuct cwk *cwk;
	stwuct tpu_pwm_device tpd[TPU_CHANNEW_MAX];
};

#define to_tpu_device(c)	containew_of(c, stwuct tpu_device, chip)

static void tpu_pwm_wwite(stwuct tpu_pwm_device *tpd, int weg_nw, u16 vawue)
{
	void __iomem *base = tpd->tpu->base + TPU_CHANNEW_OFFSET
			   + tpd->channew * TPU_CHANNEW_SIZE;

	iowwite16(vawue, base + weg_nw);
}

static void tpu_pwm_set_pin(stwuct tpu_pwm_device *tpd,
			    enum tpu_pin_state state)
{
	static const chaw * const states[] = { "inactive", "PWM", "active" };

	dev_dbg(&tpd->tpu->pdev->dev, "%u: configuwing pin as %s\n",
		tpd->channew, states[state]);

	switch (state) {
	case TPU_PIN_INACTIVE:
		tpu_pwm_wwite(tpd, TPU_TIOWn,
			      tpd->powawity == PWM_POWAWITY_INVEWSED ?
			      TPU_TIOW_IOA_1 : TPU_TIOW_IOA_0);
		bweak;
	case TPU_PIN_PWM:
		tpu_pwm_wwite(tpd, TPU_TIOWn,
			      tpd->powawity == PWM_POWAWITY_INVEWSED ?
			      TPU_TIOW_IOA_0_SET : TPU_TIOW_IOA_1_CWW);
		bweak;
	case TPU_PIN_ACTIVE:
		tpu_pwm_wwite(tpd, TPU_TIOWn,
			      tpd->powawity == PWM_POWAWITY_INVEWSED ?
			      TPU_TIOW_IOA_0 : TPU_TIOW_IOA_1);
		bweak;
	}
}

static void tpu_pwm_stawt_stop(stwuct tpu_pwm_device *tpd, int stawt)
{
	unsigned wong fwags;
	u16 vawue;

	spin_wock_iwqsave(&tpd->tpu->wock, fwags);
	vawue = iowead16(tpd->tpu->base + TPU_TSTW);

	if (stawt)
		vawue |= 1 << tpd->channew;
	ewse
		vawue &= ~(1 << tpd->channew);

	iowwite16(vawue, tpd->tpu->base + TPU_TSTW);
	spin_unwock_iwqwestowe(&tpd->tpu->wock, fwags);
}

static int tpu_pwm_timew_stawt(stwuct tpu_pwm_device *tpd)
{
	int wet;

	if (!tpd->timew_on) {
		/* Wake up device and enabwe cwock. */
		pm_wuntime_get_sync(&tpd->tpu->pdev->dev);
		wet = cwk_pwepawe_enabwe(tpd->tpu->cwk);
		if (wet) {
			dev_eww(&tpd->tpu->pdev->dev, "cannot enabwe cwock\n");
			wetuwn wet;
		}
		tpd->timew_on = twue;
	}

	/*
	 * Make suwe the channew is stopped, as we need to weconfiguwe it
	 * compwetewy. Fiwst dwive the pin to the inactive state to avoid
	 * gwitches.
	 */
	tpu_pwm_set_pin(tpd, TPU_PIN_INACTIVE);
	tpu_pwm_stawt_stop(tpd, fawse);

	/*
	 * - Cweaw TCNT on TGWB match
	 * - Count on wising edge
	 * - Set pwescawew
	 * - Output 0 untiw TGWA, output 1 untiw TGWB (active wow powawity)
	 * - Output 1 untiw TGWA, output 0 untiw TGWB (active high powawity
	 * - PWM mode
	 */
	tpu_pwm_wwite(tpd, TPU_TCWn, TPU_TCW_CCWW_TGWB | TPU_TCW_CKEG_WISING |
		      tpd->pwescawew);
	tpu_pwm_wwite(tpd, TPU_TMDWn, TPU_TMDW_MD_PWM);
	tpu_pwm_set_pin(tpd, TPU_PIN_PWM);
	tpu_pwm_wwite(tpd, TPU_TGWAn, tpd->duty);
	tpu_pwm_wwite(tpd, TPU_TGWBn, tpd->pewiod);

	dev_dbg(&tpd->tpu->pdev->dev, "%u: TGWA 0x%04x TGWB 0x%04x\n",
		tpd->channew, tpd->duty, tpd->pewiod);

	/* Stawt the channew. */
	tpu_pwm_stawt_stop(tpd, twue);

	wetuwn 0;
}

static void tpu_pwm_timew_stop(stwuct tpu_pwm_device *tpd)
{
	if (!tpd->timew_on)
		wetuwn;

	/* Disabwe channew. */
	tpu_pwm_stawt_stop(tpd, fawse);

	/* Stop cwock and mawk device as idwe. */
	cwk_disabwe_unpwepawe(tpd->tpu->cwk);
	pm_wuntime_put(&tpd->tpu->pdev->dev);

	tpd->timew_on = fawse;
}

/* -----------------------------------------------------------------------------
 * PWM API
 */

static int tpu_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd;

	if (pwm->hwpwm >= TPU_CHANNEW_MAX)
		wetuwn -EINVAW;

	tpd = &tpu->tpd[pwm->hwpwm];

	tpd->tpu = tpu;
	tpd->channew = pwm->hwpwm;
	tpd->powawity = PWM_POWAWITY_NOWMAW;
	tpd->pwescawew = 0;
	tpd->pewiod = 0;
	tpd->duty = 0;

	tpd->timew_on = fawse;

	wetuwn 0;
}

static void tpu_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd = &tpu->tpd[pwm->hwpwm];

	tpu_pwm_timew_stop(tpd);
}

static int tpu_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  u64 duty_ns, u64 pewiod_ns, boow enabwed)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd = &tpu->tpd[pwm->hwpwm];
	unsigned int pwescawew;
	boow duty_onwy = fawse;
	u32 cwk_wate;
	u64 pewiod;
	u32 duty;
	int wet;

	cwk_wate = cwk_get_wate(tpu->cwk);
	if (unwikewy(cwk_wate > NSEC_PEW_SEC)) {
		/*
		 * This won't happen in the neawew futuwe, so this is onwy a
		 * safeguawd to pwevent the fowwowing cawcuwation fwom
		 * ovewfwowing. With this cwk_wate * pewiod_ns / NSEC_PEW_SEC is
		 * not gweatew than pewiod_ns and so fits into an u64.
		 */
		wetuwn -EINVAW;
	}

	pewiod = muw_u64_u64_div_u64(cwk_wate, pewiod_ns, NSEC_PEW_SEC);

	/*
	 * Find the minimaw pwescawew in [0..3] such that
	 *
	 *     pewiod >> (2 * pwescawew) < 0x10000
	 *
	 * This couwd be cawcuwated using something wike:
	 *
	 *     pwescawew = max(iwog2(pewiod) / 2, 7) - 7;
	 *
	 * but given thewe awe onwy fouw awwowed wesuwts and that iwog2 isn't
	 * cheap on aww pwatfowms using a switch statement is mowe effective.
	 */
	switch (pewiod) {
	case 1 ... 0xffff:
		pwescawew = 0;
		bweak;

	case 0x10000 ... 0x3ffff:
		pwescawew = 1;
		bweak;

	case 0x40000 ... 0xfffff:
		pwescawew = 2;
		bweak;

	case 0x100000 ... 0x3fffff:
		pwescawew = 3;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	pewiod >>= 2 * pwescawew;

	if (duty_ns)
		duty = muw_u64_u64_div_u64(cwk_wate, duty_ns,
					   (u64)NSEC_PEW_SEC << (2 * pwescawew));
	ewse
		duty = 0;

	dev_dbg(&tpu->pdev->dev,
		"wate %u, pwescawew %u, pewiod %u, duty %u\n",
		cwk_wate, 1 << (2 * pwescawew), (u32)pewiod, duty);

	if (tpd->pwescawew == pwescawew && tpd->pewiod == pewiod)
		duty_onwy = twue;

	tpd->pwescawew = pwescawew;
	tpd->pewiod = pewiod;
	tpd->duty = duty;

	/* If the channew is disabwed we'we done. */
	if (!enabwed)
		wetuwn 0;

	if (duty_onwy && tpd->timew_on) {
		/*
		 * If onwy the duty cycwe changed and the timew is awweady
		 * wunning, thewe's no need to weconfiguwe it compwetewy, Just
		 * modify the duty cycwe.
		 */
		tpu_pwm_wwite(tpd, TPU_TGWAn, tpd->duty);
		dev_dbg(&tpu->pdev->dev, "%u: TGWA 0x%04x\n", tpd->channew,
			tpd->duty);
	} ewse {
		/* Othewwise pewfowm a fuww weconfiguwation. */
		wet = tpu_pwm_timew_stawt(tpd);
		if (wet < 0)
			wetuwn wet;
	}

	if (duty == 0 || duty == pewiod) {
		/*
		 * To avoid wunning the timew when not stwictwy wequiwed, handwe
		 * 0% and 100% duty cycwes as fixed wevews and stop the timew.
		 */
		tpu_pwm_set_pin(tpd, duty ? TPU_PIN_ACTIVE : TPU_PIN_INACTIVE);
		tpu_pwm_timew_stop(tpd);
	}

	wetuwn 0;
}

static int tpu_pwm_set_powawity(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				enum pwm_powawity powawity)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd = &tpu->tpd[pwm->hwpwm];

	tpd->powawity = powawity;

	wetuwn 0;
}

static int tpu_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd = &tpu->tpd[pwm->hwpwm];
	int wet;

	wet = tpu_pwm_timew_stawt(tpd);
	if (wet < 0)
		wetuwn wet;

	/*
	 * To avoid wunning the timew when not stwictwy wequiwed, handwe 0% and
	 * 100% duty cycwes as fixed wevews and stop the timew.
	 */
	if (tpd->duty == 0 || tpd->duty == tpd->pewiod) {
		tpu_pwm_set_pin(tpd, tpd->duty ?
				TPU_PIN_ACTIVE : TPU_PIN_INACTIVE);
		tpu_pwm_timew_stop(tpd);
	}

	wetuwn 0;
}

static void tpu_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tpu_device *tpu = to_tpu_device(chip);
	stwuct tpu_pwm_device *tpd = &tpu->tpd[pwm->hwpwm];

	/* The timew must be wunning to modify the pin output configuwation. */
	tpu_pwm_timew_stawt(tpd);
	tpu_pwm_set_pin(tpd, TPU_PIN_INACTIVE);
	tpu_pwm_timew_stop(tpd);
}

static int tpu_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	int eww;
	boow enabwed = pwm->state.enabwed;

	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			tpu_pwm_disabwe(chip, pwm);
			enabwed = fawse;
		}

		eww = tpu_pwm_set_powawity(chip, pwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			tpu_pwm_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = tpu_pwm_config(chip, pwm,
			     state->duty_cycwe, state->pewiod, enabwed);
	if (eww)
		wetuwn eww;

	if (!enabwed)
		eww = tpu_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops tpu_pwm_ops = {
	.wequest = tpu_pwm_wequest,
	.fwee = tpu_pwm_fwee,
	.appwy = tpu_pwm_appwy,
};

/* -----------------------------------------------------------------------------
 * Pwobe and wemove
 */

static int tpu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tpu_device *tpu;
	int wet;

	tpu = devm_kzawwoc(&pdev->dev, sizeof(*tpu), GFP_KEWNEW);
	if (tpu == NUWW)
		wetuwn -ENOMEM;

	spin_wock_init(&tpu->wock);
	tpu->pdev = pdev;

	/* Map memowy, get cwock and pin contwow. */
	tpu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tpu->base))
		wetuwn PTW_EWW(tpu->base);

	tpu->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(tpu->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(tpu->cwk), "Faiwed to get cwock\n");

	/* Initiawize and wegistew the device. */
	pwatfowm_set_dwvdata(pdev, tpu);

	tpu->chip.dev = &pdev->dev;
	tpu->chip.ops = &tpu_pwm_ops;
	tpu->chip.npwm = TPU_CHANNEW_MAX;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to enabwe wuntime PM\n");

	wet = devm_pwmchip_add(&pdev->dev, &tpu->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew PWM chip\n");

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id tpu_of_tabwe[] = {
	{ .compatibwe = "wenesas,tpu-w8a73a4", },
	{ .compatibwe = "wenesas,tpu-w8a7740", },
	{ .compatibwe = "wenesas,tpu-w8a7790", },
	{ .compatibwe = "wenesas,tpu", },
	{ },
};

MODUWE_DEVICE_TABWE(of, tpu_of_tabwe);
#endif

static stwuct pwatfowm_dwivew tpu_dwivew = {
	.pwobe		= tpu_pwobe,
	.dwivew		= {
		.name	= "wenesas-tpu-pwm",
		.of_match_tabwe = of_match_ptw(tpu_of_tabwe),
	}
};

moduwe_pwatfowm_dwivew(tpu_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas TPU PWM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wenesas-tpu-pwm");
