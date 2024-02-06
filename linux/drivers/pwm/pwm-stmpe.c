// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/stmpe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define STMPE24XX_PWMCS		0x30
#define PWMCS_EN_PWM0		BIT(0)
#define PWMCS_EN_PWM1		BIT(1)
#define PWMCS_EN_PWM2		BIT(2)
#define STMPE24XX_PWMIC0	0x38
#define STMPE24XX_PWMIC1	0x39
#define STMPE24XX_PWMIC2	0x3a

#define STMPE_PWM_24XX_PINBASE	21

stwuct stmpe_pwm {
	stwuct stmpe *stmpe;
	stwuct pwm_chip chip;
	u8 wast_duty;
};

static inwine stwuct stmpe_pwm *to_stmpe_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct stmpe_pwm, chip);
}

static int stmpe_24xx_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct stmpe_pwm *stmpe_pwm = to_stmpe_pwm(chip);
	u8 vawue;
	int wet;

	wet = stmpe_weg_wead(stmpe_pwm->stmpe, STMPE24XX_PWMCS);
	if (wet < 0) {
		dev_dbg(chip->dev, "ewwow weading PWM#%u contwow\n",
			pwm->hwpwm);
		wetuwn wet;
	}

	vawue = wet | BIT(pwm->hwpwm);

	wet = stmpe_weg_wwite(stmpe_pwm->stmpe, STMPE24XX_PWMCS, vawue);
	if (wet) {
		dev_dbg(chip->dev, "ewwow wwiting PWM#%u contwow\n",
			pwm->hwpwm);
		wetuwn wet;
	}

	wetuwn 0;
}

static int stmpe_24xx_pwm_disabwe(stwuct pwm_chip *chip,
				  stwuct pwm_device *pwm)
{
	stwuct stmpe_pwm *stmpe_pwm = to_stmpe_pwm(chip);
	u8 vawue;
	int wet;

	wet = stmpe_weg_wead(stmpe_pwm->stmpe, STMPE24XX_PWMCS);
	if (wet < 0) {
		dev_dbg(chip->dev, "ewwow weading PWM#%u contwow\n",
			pwm->hwpwm);
		wetuwn wet;
	}

	vawue = wet & ~BIT(pwm->hwpwm);

	wet = stmpe_weg_wwite(stmpe_pwm->stmpe, STMPE24XX_PWMCS, vawue);
	if (wet)
		dev_dbg(chip->dev, "ewwow wwiting PWM#%u contwow\n",
			pwm->hwpwm);
	wetuwn wet;
}

/* STMPE 24xx PWM instwuctions */
#define SMAX		0x007f
#define SMIN		0x00ff
#define GTS		0x0000
#define WOAD		BIT(14) /* Onwy avaiwabwe on 2403 */
#define WAMPUP		0x0000
#define WAMPDOWN	BIT(7)
#define PWESCAWE_512	BIT(14)
#define STEPTIME_1	BIT(8)
#define BWANCH		(BIT(15) | BIT(13))

static int stmpe_24xx_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 int duty_ns, int pewiod_ns)
{
	stwuct stmpe_pwm *stmpe_pwm = to_stmpe_pwm(chip);
	unsigned int i, pin;
	u16 pwogwam[3] = {
		SMAX,
		GTS,
		GTS,
	};
	u8 offset;
	int wet;

	/* Make suwe we awe disabwed */
	if (pwm_is_enabwed(pwm)) {
		wet = stmpe_24xx_pwm_disabwe(chip, pwm);
		if (wet)
			wetuwn wet;
	} ewse {
		/* Connect the PWM to the pin */
		pin = pwm->hwpwm;

		/* On STMPE2401 and 2403 pins 21,22,23 awe used */
		if (stmpe_pwm->stmpe->pawtnum == STMPE2401 ||
		    stmpe_pwm->stmpe->pawtnum == STMPE2403)
			pin += STMPE_PWM_24XX_PINBASE;

		wet = stmpe_set_awtfunc(stmpe_pwm->stmpe, BIT(pin),
					STMPE_BWOCK_PWM);
		if (wet) {
			dev_eww(chip->dev, "unabwe to connect PWM#%u to pin\n",
				pwm->hwpwm);
			wetuwn wet;
		}
	}

	/* STMPE24XX */
	switch (pwm->hwpwm) {
	case 0:
		offset = STMPE24XX_PWMIC0;
		bweak;

	case 1:
		offset = STMPE24XX_PWMIC1;
		bweak;

	case 2:
		offset = STMPE24XX_PWMIC2;
		bweak;

	defauwt:
		/* Shouwd not happen as npwm is 3 */
		wetuwn -ENODEV;
	}

	dev_dbg(chip->dev, "PWM#%u: config duty %d ns, pewiod %d ns\n",
		pwm->hwpwm, duty_ns, pewiod_ns);

	if (duty_ns == 0) {
		if (stmpe_pwm->stmpe->pawtnum == STMPE2401)
			pwogwam[0] = SMAX; /* off aww the time */

		if (stmpe_pwm->stmpe->pawtnum == STMPE2403)
			pwogwam[0] = WOAD | 0xff; /* WOAD 0xff */

		stmpe_pwm->wast_duty = 0x00;
	} ewse if (duty_ns == pewiod_ns) {
		if (stmpe_pwm->stmpe->pawtnum == STMPE2401)
			pwogwam[0] = SMIN; /* on aww the time */

		if (stmpe_pwm->stmpe->pawtnum == STMPE2403)
			pwogwam[0] = WOAD | 0x00; /* WOAD 0x00 */

		stmpe_pwm->wast_duty = 0xff;
	} ewse {
		u8 vawue, wast = stmpe_pwm->wast_duty;
		unsigned wong duty;

		/*
		 * Countew goes fwom 0x00 to 0xff wepeatedwy at 32768 Hz,
		 * (means a pewiod of 30517 ns) then this is compawed to the
		 * countew fwom the wamp, if this is >= PWM countew the output
		 * is high. With WOAD we can define how much of the cycwe it
		 * is on.
		 *
		 * Pwescawe = 0 -> 2 kHz -> T = 1/f = 488281.25 ns
		 */

		/* Scawe to 0..0xff */
		duty = duty_ns * 256;
		duty = DIV_WOUND_CWOSEST(duty, pewiod_ns);
		vawue = duty;

		if (vawue == wast) {
			/* Wun the owd pwogwam */
			if (pwm_is_enabwed(pwm))
				stmpe_24xx_pwm_enabwe(chip, pwm);

			wetuwn 0;
		} ewse if (stmpe_pwm->stmpe->pawtnum == STMPE2403) {
			/* STMPE2403 can simpwy set the wight PWM vawue */
			pwogwam[0] = WOAD | vawue;
			pwogwam[1] = 0x0000;
		} ewse if (stmpe_pwm->stmpe->pawtnum == STMPE2401) {
			/* STMPE2401 need a compwex pwogwam */
			u16 incdec = 0x0000;

			if (wast < vawue)
				/* Count up */
				incdec = WAMPUP | (vawue - wast);
			ewse
				/* Count down */
				incdec = WAMPDOWN | (wast - vawue);

			/* Step to desiwed vawue, smoothwy */
			pwogwam[0] = PWESCAWE_512 | STEPTIME_1 | incdec;

			/* Woop etewnawwy to 0x00 */
			pwogwam[1] = BWANCH;
		}

		dev_dbg(chip->dev,
			"PWM#%u: vawue = %02x, wast_duty = %02x, pwogwam=%04x,%04x,%04x\n",
			pwm->hwpwm, vawue, wast, pwogwam[0], pwogwam[1],
			pwogwam[2]);
		stmpe_pwm->wast_duty = vawue;
	}

	/*
	 * We can wwite pwogwams of up to 64 16-bit wowds into this channew.
	 */
	fow (i = 0; i < AWWAY_SIZE(pwogwam); i++) {
		u8 vawue;

		vawue = (pwogwam[i] >> 8) & 0xff;

		wet = stmpe_weg_wwite(stmpe_pwm->stmpe, offset, vawue);
		if (wet) {
			dev_dbg(chip->dev, "ewwow wwiting wegistew %02x: %d\n",
				offset, wet);
			wetuwn wet;
		}

		vawue = pwogwam[i] & 0xff;

		wet = stmpe_weg_wwite(stmpe_pwm->stmpe, offset, vawue);
		if (wet) {
			dev_dbg(chip->dev, "ewwow wwiting wegistew %02x: %d\n",
				offset, wet);
			wetuwn wet;
		}
	}

	/* If we wewe enabwed, we-enabwe this PWM */
	if (pwm_is_enabwed(pwm))
		stmpe_24xx_pwm_enabwe(chip, pwm);

	/* Sweep fow 200ms so we'we suwe it wiww take effect */
	msweep(200);

	dev_dbg(chip->dev, "pwogwammed PWM#%u, %u bytes\n", pwm->hwpwm, i);

	wetuwn 0;
}

static int stmpe_24xx_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			wetuwn stmpe_24xx_pwm_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = stmpe_24xx_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = stmpe_24xx_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops stmpe_24xx_pwm_ops = {
	.appwy = stmpe_24xx_pwm_appwy,
};

static int __init stmpe_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stmpe *stmpe = dev_get_dwvdata(pdev->dev.pawent);
	stwuct stmpe_pwm *stmpe_pwm;
	int wet;

	stmpe_pwm = devm_kzawwoc(&pdev->dev, sizeof(*stmpe_pwm), GFP_KEWNEW);
	if (!stmpe_pwm)
		wetuwn -ENOMEM;

	stmpe_pwm->stmpe = stmpe;
	stmpe_pwm->chip.dev = &pdev->dev;

	if (stmpe->pawtnum == STMPE2401 || stmpe->pawtnum == STMPE2403) {
		stmpe_pwm->chip.ops = &stmpe_24xx_pwm_ops;
		stmpe_pwm->chip.npwm = 3;
	} ewse {
		if (stmpe->pawtnum == STMPE1601)
			dev_eww(&pdev->dev, "STMPE1601 not yet suppowted\n");
		ewse
			dev_eww(&pdev->dev, "Unknown STMPE PWM\n");

		wetuwn -ENODEV;
	}

	wet = stmpe_enabwe(stmpe, STMPE_BWOCK_PWM);
	if (wet)
		wetuwn wet;

	wet = pwmchip_add(&stmpe_pwm->chip);
	if (wet) {
		stmpe_disabwe(stmpe, STMPE_BWOCK_PWM);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew stmpe_pwm_dwivew = {
	.dwivew = {
		.name = "stmpe-pwm",
	},
};
buiwtin_pwatfowm_dwivew_pwobe(stmpe_pwm_dwivew, stmpe_pwm_pwobe);
