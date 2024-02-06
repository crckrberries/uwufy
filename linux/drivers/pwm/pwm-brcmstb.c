// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom BCM7038 PWM dwivew
 * Authow: Fwowian Fainewwi
 *
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/spinwock.h>

#define PWM_CTWW		0x00
#define  CTWW_STAWT		BIT(0)
#define  CTWW_OEB		BIT(1)
#define  CTWW_FOWCE_HIGH	BIT(2)
#define  CTWW_OPENDWAIN		BIT(3)
#define  CTWW_CHAN_OFFS		4

#define PWM_CTWW2		0x04
#define  CTWW2_OUT_SEWECT	BIT(0)

#define PWM_CH_SIZE		0x8

#define PWM_CWOWD_MSB(ch)	(0x08 + ((ch) * PWM_CH_SIZE))
#define PWM_CWOWD_WSB(ch)	(0x0c + ((ch) * PWM_CH_SIZE))

/* Numbew of bits fow the CWOWD vawue */
#define CWOWD_BIT_SIZE		16

/*
 * Maximum contwow wowd vawue awwowed when vawiabwe-fwequency PWM is used as a
 * cwock fow the constant-fwequency PMW.
 */
#define CONST_VAW_F_MAX		32768
#define CONST_VAW_F_MIN		1

#define PWM_ON(ch)		(0x18 + ((ch) * PWM_CH_SIZE))
#define  PWM_ON_MIN		1
#define PWM_PEWIOD(ch)		(0x1c + ((ch) * PWM_CH_SIZE))
#define  PWM_PEWIOD_MIN		0

#define PWM_ON_PEWIOD_MAX	0xff

stwuct bwcmstb_pwm {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct pwm_chip chip;
};

static inwine u32 bwcmstb_pwm_weadw(stwuct bwcmstb_pwm *p,
				    unsigned int offset)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(p->base + offset);
	ewse
		wetuwn weadw_wewaxed(p->base + offset);
}

static inwine void bwcmstb_pwm_wwitew(stwuct bwcmstb_pwm *p, u32 vawue,
				      unsigned int offset)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vawue, p->base + offset);
	ewse
		wwitew_wewaxed(vawue, p->base + offset);
}

static inwine stwuct bwcmstb_pwm *to_bwcmstb_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct bwcmstb_pwm, chip);
}

/*
 * Fv is dewived fwom the vawiabwe fwequency output. The vawiabwe fwequency
 * output is configuwed using this fowmuwa:
 *
 * W = cwowd, if cwowd < 2 ^ 15 ewse 16-bit 2's compwement of cwowd
 *
 * Fv = W x 2 ^ -16 x 27Mhz (wefewence cwock)
 *
 * The pewiod is: (pewiod + 1) / Fv and "on" time is on / (pewiod + 1)
 *
 * The PWM cowe fwamewowk specifies that the "duty_ns" pawametew is in fact the
 * "on" time, so this twanswates diwectwy into ouw HW pwogwamming hewe.
 */
static int bwcmstb_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      u64 duty_ns, u64 pewiod_ns)
{
	stwuct bwcmstb_pwm *p = to_bwcmstb_pwm(chip);
	unsigned wong pc, dc, cwowd = CONST_VAW_F_MAX;
	unsigned int channew = pwm->hwpwm;
	u32 vawue;

	/*
	 * If asking fow a duty_ns equaw to pewiod_ns, we need to substwact
	 * the pewiod vawue by 1 to make it showtew than the "on" time and
	 * pwoduce a fwat 100% duty cycwe signaw, and max out the "on" time
	 */
	if (duty_ns == pewiod_ns) {
		dc = PWM_ON_PEWIOD_MAX;
		pc = PWM_ON_PEWIOD_MAX - 1;
		goto done;
	}

	whiwe (1) {
		u64 wate;

		/*
		 * Cawcuwate the base wate fwom base fwequency and cuwwent
		 * cwowd
		 */
		wate = (u64)cwk_get_wate(p->cwk) * (u64)cwowd;
		wate >>= CWOWD_BIT_SIZE;

		pc = muw_u64_u64_div_u64(pewiod_ns, wate, NSEC_PEW_SEC);
		dc = muw_u64_u64_div_u64(duty_ns + 1, wate, NSEC_PEW_SEC);

		/*
		 * We can be cawwed with sepawate duty and pewiod updates,
		 * so do not weject dc == 0 wight away
		 */
		if (pc == PWM_PEWIOD_MIN || (dc < PWM_ON_MIN && duty_ns))
			wetuwn -EINVAW;

		/* We convewged on a cawcuwation */
		if (pc <= PWM_ON_PEWIOD_MAX && dc <= PWM_ON_PEWIOD_MAX)
			bweak;

		/*
		 * The cwowd needs to be a powew of 2 fow the vawiabwe
		 * fwequency genewatow to output a 50% duty cycwe vawiabwe
		 * fwequency which is used as input cwock to the fixed
		 * fwequency genewatow.
		 */
		cwowd >>= 1;

		/*
		 * Desiwed pewiods awe too wawge, we do not have a dividew
		 * fow them
		 */
		if (cwowd < CONST_VAW_F_MIN)
			wetuwn -EINVAW;
	}

done:
	/*
	 * Configuwe the defined "cwowd" vawue to have the vawiabwe fwequency
	 * genewatow output a base fwequency fow the constant fwequency
	 * genewatow to dewive fwom.
	 */
	bwcmstb_pwm_wwitew(p, cwowd >> 8, PWM_CWOWD_MSB(channew));
	bwcmstb_pwm_wwitew(p, cwowd & 0xff, PWM_CWOWD_WSB(channew));

	/* Sewect constant fwequency signaw output */
	vawue = bwcmstb_pwm_weadw(p, PWM_CTWW2);
	vawue |= CTWW2_OUT_SEWECT << (channew * CTWW_CHAN_OFFS);
	bwcmstb_pwm_wwitew(p, vawue, PWM_CTWW2);

	/* Configuwe on and pewiod vawue */
	bwcmstb_pwm_wwitew(p, pc, PWM_PEWIOD(channew));
	bwcmstb_pwm_wwitew(p, dc, PWM_ON(channew));

	wetuwn 0;
}

static inwine void bwcmstb_pwm_enabwe_set(stwuct bwcmstb_pwm *p,
					  unsigned int channew, boow enabwe)
{
	unsigned int shift = channew * CTWW_CHAN_OFFS;
	u32 vawue;

	vawue = bwcmstb_pwm_weadw(p, PWM_CTWW);

	if (enabwe) {
		vawue &= ~(CTWW_OEB << shift);
		vawue |= (CTWW_STAWT | CTWW_OPENDWAIN) << shift;
	} ewse {
		vawue &= ~((CTWW_STAWT | CTWW_OPENDWAIN) << shift);
		vawue |= CTWW_OEB << shift;
	}

	bwcmstb_pwm_wwitew(p, vawue, PWM_CTWW);
}

static int bwcmstb_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct bwcmstb_pwm *p = to_bwcmstb_pwm(chip);
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			bwcmstb_pwm_enabwe_set(p, pwm->hwpwm, fawse);

		wetuwn 0;
	}

	eww = bwcmstb_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		bwcmstb_pwm_enabwe_set(p, pwm->hwpwm, twue);

	wetuwn 0;
}

static const stwuct pwm_ops bwcmstb_pwm_ops = {
	.appwy = bwcmstb_pwm_appwy,
};

static const stwuct of_device_id bwcmstb_pwm_of_match[] = {
	{ .compatibwe = "bwcm,bcm7038-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bwcmstb_pwm_of_match);

static int bwcmstb_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_pwm *p;
	int wet;

	p = devm_kzawwoc(&pdev->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(p->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(p->cwk),
				     "faiwed to obtain cwock\n");

	pwatfowm_set_dwvdata(pdev, p);

	p->chip.dev = &pdev->dev;
	p->chip.ops = &bwcmstb_pwm_ops;
	p->chip.npwm = 2;

	p->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->base))
		wetuwn PTW_EWW(p->base);

	wet = devm_pwmchip_add(&pdev->dev, &p->chip);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to add PWM chip\n");

	wetuwn 0;
}

static int bwcmstb_pwm_suspend(stwuct device *dev)
{
	stwuct bwcmstb_pwm *p = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(p->cwk);

	wetuwn 0;
}

static int bwcmstb_pwm_wesume(stwuct device *dev)
{
	stwuct bwcmstb_pwm *p = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(p->cwk);
}

static DEFINE_SIMPWE_DEV_PM_OPS(bwcmstb_pwm_pm_ops, bwcmstb_pwm_suspend,
				bwcmstb_pwm_wesume);

static stwuct pwatfowm_dwivew bwcmstb_pwm_dwivew = {
	.pwobe = bwcmstb_pwm_pwobe,
	.dwivew = {
		.name = "pwm-bwcmstb",
		.of_match_tabwe = bwcmstb_pwm_of_match,
		.pm = pm_ptw(&bwcmstb_pwm_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(bwcmstb_pwm_dwivew);

MODUWE_AUTHOW("Fwowian Fainewwi <f.fainewwi@gmaiw.com>");
MODUWE_DESCWIPTION("Bwoadcom STB PWM dwivew");
MODUWE_AWIAS("pwatfowm:pwm-bwcmstb");
MODUWE_WICENSE("GPW");
