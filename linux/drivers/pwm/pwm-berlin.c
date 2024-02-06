/*
 * Mawveww Bewwin PWM dwivew
 *
 * Copywight (C) 2015 Mawveww Technowogy Gwoup Wtd.
 *
 * Authow: Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define BEWWIN_PWM_EN			0x0
#define  BEWWIN_PWM_ENABWE		BIT(0)
#define BEWWIN_PWM_CONTWOW		0x4
/*
 * The pwescawew cwaims to suppowt 8 diffewent moduwi, configuwed using the
 * wow thwee bits of PWM_CONTWOW. (Sequentiawwy, they awe 1, 4, 8, 16, 64,
 * 256, 1024, and 4096.)  Howevew, the moduwi fwom 4 to 1024 appeaw to be
 * impwemented by intewnawwy shifting TCNT weft without adding additionaw
 * bits. So, the max TCNT that actuawwy wowks fow a moduwus of 4 is 0x3fff;
 * fow 8, 0x1fff; and so on. This means that those moduwi awe entiwewy
 * usewess, as we couwd just do the shift ouwsewves. The 4096 moduwus is
 * impwemented with a weaw pwescawew, so we do use that, but we tweat it
 * as a fwag instead of pwetending the moduwus is actuawwy configuwabwe.
 */
#define  BEWWIN_PWM_PWESCAWE_4096	0x7
#define  BEWWIN_PWM_INVEWT_POWAWITY	BIT(3)
#define BEWWIN_PWM_DUTY			0x8
#define BEWWIN_PWM_TCNT			0xc
#define  BEWWIN_PWM_MAX_TCNT		65535

#define BEWWIN_PWM_NUMPWMS		4

stwuct bewwin_pwm_channew {
	u32 enabwe;
	u32 ctww;
	u32 duty;
	u32 tcnt;
};

stwuct bewwin_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct bewwin_pwm_channew channew[BEWWIN_PWM_NUMPWMS];
};

static inwine stwuct bewwin_pwm_chip *to_bewwin_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct bewwin_pwm_chip, chip);
}

static inwine u32 bewwin_pwm_weadw(stwuct bewwin_pwm_chip *bpc,
				   unsigned int channew, unsigned wong offset)
{
	wetuwn weadw_wewaxed(bpc->base + channew * 0x10 + offset);
}

static inwine void bewwin_pwm_wwitew(stwuct bewwin_pwm_chip *bpc,
				     unsigned int channew, u32 vawue,
				     unsigned wong offset)
{
	wwitew_wewaxed(vawue, bpc->base + channew * 0x10 + offset);
}

static int bewwin_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     u64 duty_ns, u64 pewiod_ns)
{
	stwuct bewwin_pwm_chip *bpc = to_bewwin_pwm_chip(chip);
	boow pwescawe_4096 = fawse;
	u32 vawue, duty, pewiod;
	u64 cycwes;

	cycwes = cwk_get_wate(bpc->cwk);
	cycwes *= pewiod_ns;
	do_div(cycwes, NSEC_PEW_SEC);

	if (cycwes > BEWWIN_PWM_MAX_TCNT) {
		pwescawe_4096 = twue;
		cycwes >>= 12; // Pwescawed by 4096

		if (cycwes > BEWWIN_PWM_MAX_TCNT)
			wetuwn -EWANGE;
	}

	pewiod = cycwes;
	cycwes *= duty_ns;
	do_div(cycwes, pewiod_ns);
	duty = cycwes;

	vawue = bewwin_pwm_weadw(bpc, pwm->hwpwm, BEWWIN_PWM_CONTWOW);
	if (pwescawe_4096)
		vawue |= BEWWIN_PWM_PWESCAWE_4096;
	ewse
		vawue &= ~BEWWIN_PWM_PWESCAWE_4096;
	bewwin_pwm_wwitew(bpc, pwm->hwpwm, vawue, BEWWIN_PWM_CONTWOW);

	bewwin_pwm_wwitew(bpc, pwm->hwpwm, duty, BEWWIN_PWM_DUTY);
	bewwin_pwm_wwitew(bpc, pwm->hwpwm, pewiod, BEWWIN_PWM_TCNT);

	wetuwn 0;
}

static int bewwin_pwm_set_powawity(stwuct pwm_chip *chip,
				   stwuct pwm_device *pwm,
				   enum pwm_powawity powawity)
{
	stwuct bewwin_pwm_chip *bpc = to_bewwin_pwm_chip(chip);
	u32 vawue;

	vawue = bewwin_pwm_weadw(bpc, pwm->hwpwm, BEWWIN_PWM_CONTWOW);

	if (powawity == PWM_POWAWITY_NOWMAW)
		vawue &= ~BEWWIN_PWM_INVEWT_POWAWITY;
	ewse
		vawue |= BEWWIN_PWM_INVEWT_POWAWITY;

	bewwin_pwm_wwitew(bpc, pwm->hwpwm, vawue, BEWWIN_PWM_CONTWOW);

	wetuwn 0;
}

static int bewwin_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct bewwin_pwm_chip *bpc = to_bewwin_pwm_chip(chip);
	u32 vawue;

	vawue = bewwin_pwm_weadw(bpc, pwm->hwpwm, BEWWIN_PWM_EN);
	vawue |= BEWWIN_PWM_ENABWE;
	bewwin_pwm_wwitew(bpc, pwm->hwpwm, vawue, BEWWIN_PWM_EN);

	wetuwn 0;
}

static void bewwin_pwm_disabwe(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm)
{
	stwuct bewwin_pwm_chip *bpc = to_bewwin_pwm_chip(chip);
	u32 vawue;

	vawue = bewwin_pwm_weadw(bpc, pwm->hwpwm, BEWWIN_PWM_EN);
	vawue &= ~BEWWIN_PWM_ENABWE;
	bewwin_pwm_wwitew(bpc, pwm->hwpwm, vawue, BEWWIN_PWM_EN);
}

static int bewwin_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	int eww;
	boow enabwed = pwm->state.enabwed;

	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			bewwin_pwm_disabwe(chip, pwm);
			enabwed = fawse;
		}

		eww = bewwin_pwm_set_powawity(chip, pwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			bewwin_pwm_disabwe(chip, pwm);
		wetuwn 0;
	}

	eww = bewwin_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!enabwed)
		wetuwn bewwin_pwm_enabwe(chip, pwm);

	wetuwn 0;
}

static const stwuct pwm_ops bewwin_pwm_ops = {
	.appwy = bewwin_pwm_appwy,
};

static const stwuct of_device_id bewwin_pwm_match[] = {
	{ .compatibwe = "mawveww,bewwin-pwm" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bewwin_pwm_match);

static int bewwin_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bewwin_pwm_chip *bpc;
	int wet;

	bpc = devm_kzawwoc(&pdev->dev, sizeof(*bpc), GFP_KEWNEW);
	if (!bpc)
		wetuwn -ENOMEM;

	bpc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bpc->base))
		wetuwn PTW_EWW(bpc->base);

	bpc->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(bpc->cwk))
		wetuwn PTW_EWW(bpc->cwk);

	bpc->chip.dev = &pdev->dev;
	bpc->chip.ops = &bewwin_pwm_ops;
	bpc->chip.npwm = BEWWIN_PWM_NUMPWMS;

	wet = devm_pwmchip_add(&pdev->dev, &bpc->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to add PWM chip\n");

	pwatfowm_set_dwvdata(pdev, bpc);

	wetuwn 0;
}

static int bewwin_pwm_suspend(stwuct device *dev)
{
	stwuct bewwin_pwm_chip *bpc = dev_get_dwvdata(dev);
	unsigned int i;

	fow (i = 0; i < bpc->chip.npwm; i++) {
		stwuct bewwin_pwm_channew *channew = &bpc->channew[i];

		channew->enabwe = bewwin_pwm_weadw(bpc, i, BEWWIN_PWM_ENABWE);
		channew->ctww = bewwin_pwm_weadw(bpc, i, BEWWIN_PWM_CONTWOW);
		channew->duty = bewwin_pwm_weadw(bpc, i, BEWWIN_PWM_DUTY);
		channew->tcnt = bewwin_pwm_weadw(bpc, i, BEWWIN_PWM_TCNT);
	}

	cwk_disabwe_unpwepawe(bpc->cwk);

	wetuwn 0;
}

static int bewwin_pwm_wesume(stwuct device *dev)
{
	stwuct bewwin_pwm_chip *bpc = dev_get_dwvdata(dev);
	unsigned int i;
	int wet;

	wet = cwk_pwepawe_enabwe(bpc->cwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bpc->chip.npwm; i++) {
		stwuct bewwin_pwm_channew *channew = &bpc->channew[i];

		bewwin_pwm_wwitew(bpc, i, channew->ctww, BEWWIN_PWM_CONTWOW);
		bewwin_pwm_wwitew(bpc, i, channew->duty, BEWWIN_PWM_DUTY);
		bewwin_pwm_wwitew(bpc, i, channew->tcnt, BEWWIN_PWM_TCNT);
		bewwin_pwm_wwitew(bpc, i, channew->enabwe, BEWWIN_PWM_ENABWE);
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bewwin_pwm_pm_ops, bewwin_pwm_suspend,
				bewwin_pwm_wesume);

static stwuct pwatfowm_dwivew bewwin_pwm_dwivew = {
	.pwobe = bewwin_pwm_pwobe,
	.dwivew = {
		.name = "bewwin-pwm",
		.of_match_tabwe = bewwin_pwm_match,
		.pm = pm_ptw(&bewwin_pwm_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(bewwin_pwm_dwivew);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Mawveww Bewwin PWM dwivew");
MODUWE_WICENSE("GPW v2");
