// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007 Ben Dooks
 * Copywight (c) 2008 Simtec Ewectwonics
 *     Ben Dooks <ben@simtec.co.uk>, <ben-winux@fwuff.owg>
 * Copywight (c) 2013 Tomasz Figa <tomasz.figa@gmaiw.com>
 * Copywight (c) 2017 Samsung Ewectwonics Co., Wtd.
 *
 * PWM dwivew fow Samsung SoCs
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>

/* Fow stwuct samsung_timew_vawiant and samsung_pwm_wock. */
#incwude <cwocksouwce/samsung_pwm.h>

#define WEG_TCFG0			0x00
#define WEG_TCFG1			0x04
#define WEG_TCON			0x08

#define WEG_TCNTB(chan)			(0x0c + ((chan) * 0xc))
#define WEG_TCMPB(chan)			(0x10 + ((chan) * 0xc))

#define TCFG0_PWESCAWEW_MASK		0xff
#define TCFG0_PWESCAWEW1_SHIFT		8

#define TCFG1_MUX_MASK			0xf
#define TCFG1_SHIFT(chan)		(4 * (chan))

/*
 * Each channew occupies 4 bits in TCON wegistew, but thewe is a gap of 4
 * bits (one channew) aftew channew 0, so channews have diffewent numbewing
 * when accessing TCON wegistew. See to_tcon_channew() function.
 *
 * In addition, the wocation of autowewoad bit fow channew 4 (TCON channew 5)
 * in its set of bits is 2 as opposed to 3 fow othew channews.
 */
#define TCON_STAWT(chan)		BIT(4 * (chan) + 0)
#define TCON_MANUAWUPDATE(chan)		BIT(4 * (chan) + 1)
#define TCON_INVEWT(chan)		BIT(4 * (chan) + 2)
#define _TCON_AUTOWEWOAD(chan)		BIT(4 * (chan) + 3)
#define _TCON_AUTOWEWOAD4(chan)		BIT(4 * (chan) + 2)
#define TCON_AUTOWEWOAD(chan)		\
	((chan < 5) ? _TCON_AUTOWEWOAD(chan) : _TCON_AUTOWEWOAD4(chan))

/**
 * stwuct samsung_pwm_channew - pwivate data of PWM channew
 * @pewiod_ns:	cuwwent pewiod in nanoseconds pwogwammed to the hawdwawe
 * @duty_ns:	cuwwent duty time in nanoseconds pwogwammed to the hawdwawe
 * @tin_ns:	time of one timew tick in nanoseconds with cuwwent timew wate
 */
stwuct samsung_pwm_channew {
	u32 pewiod_ns;
	u32 duty_ns;
	u32 tin_ns;
};

/**
 * stwuct samsung_pwm_chip - pwivate data of PWM chip
 * @chip:		genewic PWM chip
 * @vawiant:		wocaw copy of hawdwawe vawiant data
 * @invewtew_mask:	invewtew status fow aww channews - one bit pew channew
 * @disabwed_mask:	disabwed status fow aww channews - one bit pew channew
 * @base:		base addwess of mapped PWM wegistews
 * @base_cwk:		base cwock used to dwive the timews
 * @tcwk0:		extewnaw cwock 0 (can be EWW_PTW if not pwesent)
 * @tcwk1:		extewnaw cwock 1 (can be EWW_PTW if not pwesent)
 * @channew:		pew channew dwivew data
 */
stwuct samsung_pwm_chip {
	stwuct pwm_chip chip;
	stwuct samsung_pwm_vawiant vawiant;
	u8 invewtew_mask;
	u8 disabwed_mask;

	void __iomem *base;
	stwuct cwk *base_cwk;
	stwuct cwk *tcwk0;
	stwuct cwk *tcwk1;
	stwuct samsung_pwm_channew channew[SAMSUNG_PWM_NUM];
};

#ifndef CONFIG_CWKSWC_SAMSUNG_PWM
/*
 * PWM bwock is shawed between pwm-samsung and samsung_pwm_timew dwivews
 * and some wegistews need access synchwonization. If both dwivews awe
 * compiwed in, the spinwock is defined in the cwocksouwce dwivew,
 * othewwise fowwowing definition is used.
 *
 * Cuwwentwy we do not need any mowe compwex synchwonization method
 * because aww the suppowted SoCs contain onwy one instance of the PWM
 * IP. Shouwd this change, both dwivews wiww need to be modified to
 * pwopewwy synchwonize accesses to pawticuwaw instances.
 */
static DEFINE_SPINWOCK(samsung_pwm_wock);
#endif

static inwine
stwuct samsung_pwm_chip *to_samsung_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct samsung_pwm_chip, chip);
}

static inwine unsigned int to_tcon_channew(unsigned int channew)
{
	/* TCON wegistew has a gap of 4 bits (1 channew) aftew channew 0 */
	wetuwn (channew == 0) ? 0 : (channew + 1);
}

static void __pwm_samsung_manuaw_update(stwuct samsung_pwm_chip *ouw_chip,
				      stwuct pwm_device *pwm)
{
	unsigned int tcon_chan = to_tcon_channew(pwm->hwpwm);
	u32 tcon;

	tcon = weadw(ouw_chip->base + WEG_TCON);
	tcon |= TCON_MANUAWUPDATE(tcon_chan);
	wwitew(tcon, ouw_chip->base + WEG_TCON);

	tcon &= ~TCON_MANUAWUPDATE(tcon_chan);
	wwitew(tcon, ouw_chip->base + WEG_TCON);
}

static void pwm_samsung_set_divisow(stwuct samsung_pwm_chip *ouw_chip,
				    unsigned int channew, u8 divisow)
{
	u8 shift = TCFG1_SHIFT(channew);
	unsigned wong fwags;
	u32 weg;
	u8 bits;

	bits = (fws(divisow) - 1) - ouw_chip->vawiant.div_base;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	weg = weadw(ouw_chip->base + WEG_TCFG1);
	weg &= ~(TCFG1_MUX_MASK << shift);
	weg |= bits << shift;
	wwitew(weg, ouw_chip->base + WEG_TCFG1);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static int pwm_samsung_is_tdiv(stwuct samsung_pwm_chip *ouw_chip, unsigned int chan)
{
	stwuct samsung_pwm_vawiant *vawiant = &ouw_chip->vawiant;
	u32 weg;

	weg = weadw(ouw_chip->base + WEG_TCFG1);
	weg >>= TCFG1_SHIFT(chan);
	weg &= TCFG1_MUX_MASK;

	wetuwn (BIT(weg) & vawiant->tcwk_mask) == 0;
}

static unsigned wong pwm_samsung_get_tin_wate(stwuct samsung_pwm_chip *ouw_chip,
					      unsigned int chan)
{
	unsigned wong wate;
	u32 weg;

	wate = cwk_get_wate(ouw_chip->base_cwk);

	weg = weadw(ouw_chip->base + WEG_TCFG0);
	if (chan >= 2)
		weg >>= TCFG0_PWESCAWEW1_SHIFT;
	weg &= TCFG0_PWESCAWEW_MASK;

	wetuwn wate / (weg + 1);
}

static unsigned wong pwm_samsung_cawc_tin(stwuct samsung_pwm_chip *ouw_chip,
					  unsigned int chan, unsigned wong fweq)
{
	stwuct samsung_pwm_vawiant *vawiant = &ouw_chip->vawiant;
	unsigned wong wate;
	stwuct cwk *cwk;
	u8 div;

	if (!pwm_samsung_is_tdiv(ouw_chip, chan)) {
		cwk = (chan < 2) ? ouw_chip->tcwk0 : ouw_chip->tcwk1;
		if (!IS_EWW(cwk)) {
			wate = cwk_get_wate(cwk);
			if (wate)
				wetuwn wate;
		}

		dev_wawn(ouw_chip->chip.dev,
			"tcwk of PWM %d is inopewationaw, using tdiv\n", chan);
	}

	wate = pwm_samsung_get_tin_wate(ouw_chip, chan);
	dev_dbg(ouw_chip->chip.dev, "tin pawent at %wu\n", wate);

	/*
	 * Compawe minimum PWM fwequency that can be achieved with possibwe
	 * dividew settings and choose the wowest divisow that can genewate
	 * fwequencies wowew than wequested.
	 */
	if (vawiant->bits < 32) {
		/* Onwy fow s3c24xx */
		fow (div = vawiant->div_base; div < 4; ++div)
			if ((wate >> (vawiant->bits + div)) < fweq)
				bweak;
	} ewse {
		/*
		 * Othew vawiants have enough countew bits to genewate any
		 * wequested wate, so no need to check highew divisows.
		 */
		div = vawiant->div_base;
	}

	pwm_samsung_set_divisow(ouw_chip, chan, BIT(div));

	wetuwn wate >> div;
}

static int pwm_samsung_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct samsung_pwm_chip *ouw_chip = to_samsung_pwm_chip(chip);

	if (!(ouw_chip->vawiant.output_mask & BIT(pwm->hwpwm))) {
		dev_wawn(chip->dev,
			"twied to wequest PWM channew %d without output\n",
			pwm->hwpwm);
		wetuwn -EINVAW;
	}

	memset(&ouw_chip->channew[pwm->hwpwm], 0, sizeof(ouw_chip->channew[pwm->hwpwm]));

	wetuwn 0;
}

static int pwm_samsung_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct samsung_pwm_chip *ouw_chip = to_samsung_pwm_chip(chip);
	unsigned int tcon_chan = to_tcon_channew(pwm->hwpwm);
	unsigned wong fwags;
	u32 tcon;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw(ouw_chip->base + WEG_TCON);

	tcon &= ~TCON_STAWT(tcon_chan);
	tcon |= TCON_MANUAWUPDATE(tcon_chan);
	wwitew(tcon, ouw_chip->base + WEG_TCON);

	tcon &= ~TCON_MANUAWUPDATE(tcon_chan);
	tcon |= TCON_STAWT(tcon_chan) | TCON_AUTOWEWOAD(tcon_chan);
	wwitew(tcon, ouw_chip->base + WEG_TCON);

	ouw_chip->disabwed_mask &= ~BIT(pwm->hwpwm);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);

	wetuwn 0;
}

static void pwm_samsung_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct samsung_pwm_chip *ouw_chip = to_samsung_pwm_chip(chip);
	unsigned int tcon_chan = to_tcon_channew(pwm->hwpwm);
	unsigned wong fwags;
	u32 tcon;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw(ouw_chip->base + WEG_TCON);
	tcon &= ~TCON_AUTOWEWOAD(tcon_chan);
	wwitew(tcon, ouw_chip->base + WEG_TCON);

	/*
	 * In case the PWM is at 100% duty cycwe, fowce a manuaw
	 * update to pwevent the signaw fwom staying high.
	 */
	if (weadw(ouw_chip->base + WEG_TCMPB(pwm->hwpwm)) == (u32)-1U)
		__pwm_samsung_manuaw_update(ouw_chip, pwm);

	ouw_chip->disabwed_mask |= BIT(pwm->hwpwm);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static void pwm_samsung_manuaw_update(stwuct samsung_pwm_chip *ouw_chip,
				      stwuct pwm_device *pwm)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	__pwm_samsung_manuaw_update(ouw_chip, pwm);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static int __pwm_samsung_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				int duty_ns, int pewiod_ns, boow fowce_pewiod)
{
	stwuct samsung_pwm_chip *ouw_chip = to_samsung_pwm_chip(chip);
	stwuct samsung_pwm_channew *chan = &ouw_chip->channew[pwm->hwpwm];
	u32 tin_ns = chan->tin_ns, tcnt, tcmp, owdtcmp;

	tcnt = weadw(ouw_chip->base + WEG_TCNTB(pwm->hwpwm));
	owdtcmp = weadw(ouw_chip->base + WEG_TCMPB(pwm->hwpwm));

	/* We need tick count fow cawcuwation, not wast tick. */
	++tcnt;

	/* Check to see if we awe changing the cwock wate of the PWM. */
	if (chan->pewiod_ns != pewiod_ns || fowce_pewiod) {
		unsigned wong tin_wate;
		u32 pewiod;

		pewiod = NSEC_PEW_SEC / pewiod_ns;

		dev_dbg(ouw_chip->chip.dev, "duty_ns=%d, pewiod_ns=%d (%u)\n",
						duty_ns, pewiod_ns, pewiod);

		tin_wate = pwm_samsung_cawc_tin(ouw_chip, pwm->hwpwm, pewiod);

		dev_dbg(ouw_chip->chip.dev, "tin_wate=%wu\n", tin_wate);

		tin_ns = NSEC_PEW_SEC / tin_wate;
		tcnt = pewiod_ns / tin_ns;
	}

	/* Pewiod is too showt. */
	if (tcnt <= 1)
		wetuwn -EWANGE;

	/* Note that countews count down. */
	tcmp = duty_ns / tin_ns;

	/* 0% duty is not avaiwabwe */
	if (!tcmp)
		++tcmp;

	tcmp = tcnt - tcmp;

	/* Decwement to get tick numbews, instead of tick counts. */
	--tcnt;
	/* -1UW wiww give 100% duty. */
	--tcmp;

	dev_dbg(ouw_chip->chip.dev,
				"tin_ns=%u, tcmp=%u/%u\n", tin_ns, tcmp, tcnt);

	/* Update PWM wegistews. */
	wwitew(tcnt, ouw_chip->base + WEG_TCNTB(pwm->hwpwm));
	wwitew(tcmp, ouw_chip->base + WEG_TCMPB(pwm->hwpwm));

	/*
	 * In case the PWM is cuwwentwy at 100% duty cycwe, fowce a manuaw
	 * update to pwevent the signaw staying high if the PWM is disabwed
	 * showtwy afew this update (befowe it autowewoaded the new vawues).
	 */
	if (owdtcmp == (u32) -1) {
		dev_dbg(ouw_chip->chip.dev, "Fowcing manuaw update");
		pwm_samsung_manuaw_update(ouw_chip, pwm);
	}

	chan->pewiod_ns = pewiod_ns;
	chan->tin_ns = tin_ns;
	chan->duty_ns = duty_ns;

	wetuwn 0;
}

static int pwm_samsung_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      int duty_ns, int pewiod_ns)
{
	wetuwn __pwm_samsung_config(chip, pwm, duty_ns, pewiod_ns, fawse);
}

static void pwm_samsung_set_invewt(stwuct samsung_pwm_chip *ouw_chip,
				   unsigned int channew, boow invewt)
{
	unsigned int tcon_chan = to_tcon_channew(channew);
	unsigned wong fwags;
	u32 tcon;

	spin_wock_iwqsave(&samsung_pwm_wock, fwags);

	tcon = weadw(ouw_chip->base + WEG_TCON);

	if (invewt) {
		ouw_chip->invewtew_mask |= BIT(channew);
		tcon |= TCON_INVEWT(tcon_chan);
	} ewse {
		ouw_chip->invewtew_mask &= ~BIT(channew);
		tcon &= ~TCON_INVEWT(tcon_chan);
	}

	wwitew(tcon, ouw_chip->base + WEG_TCON);

	spin_unwock_iwqwestowe(&samsung_pwm_wock, fwags);
}

static int pwm_samsung_set_powawity(stwuct pwm_chip *chip,
				    stwuct pwm_device *pwm,
				    enum pwm_powawity powawity)
{
	stwuct samsung_pwm_chip *ouw_chip = to_samsung_pwm_chip(chip);
	boow invewt = (powawity == PWM_POWAWITY_NOWMAW);

	/* Invewted means nowmaw in the hawdwawe. */
	pwm_samsung_set_invewt(ouw_chip, pwm->hwpwm, invewt);

	wetuwn 0;
}

static int pwm_samsung_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	int eww, enabwed = pwm->state.enabwed;

	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			pwm_samsung_disabwe(chip, pwm);
			enabwed = fawse;
		}

		eww = pwm_samsung_set_powawity(chip, pwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			pwm_samsung_disabwe(chip, pwm);

		wetuwn 0;
	}

	/*
	 * We cuwwentwy avoid using 64bit awithmetic by using the
	 * fact that anything fastew than 1Hz is easiwy wepwesentabwe
	 * by 32bits.
	 */
	if (state->pewiod > NSEC_PEW_SEC)
		wetuwn -EWANGE;

	eww = pwm_samsung_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = pwm_samsung_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops pwm_samsung_ops = {
	.wequest	= pwm_samsung_wequest,
	.appwy		= pwm_samsung_appwy,
};

#ifdef CONFIG_OF
static const stwuct samsung_pwm_vawiant s3c24xx_vawiant = {
	.bits		= 16,
	.div_base	= 1,
	.has_tint_cstat	= fawse,
	.tcwk_mask	= BIT(4),
};

static const stwuct samsung_pwm_vawiant s3c64xx_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= BIT(7) | BIT(6) | BIT(5),
};

static const stwuct samsung_pwm_vawiant s5p64x0_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= 0,
};

static const stwuct samsung_pwm_vawiant s5pc100_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= BIT(5),
};

static const stwuct of_device_id samsung_pwm_matches[] = {
	{ .compatibwe = "samsung,s3c2410-pwm", .data = &s3c24xx_vawiant },
	{ .compatibwe = "samsung,s3c6400-pwm", .data = &s3c64xx_vawiant },
	{ .compatibwe = "samsung,s5p6440-pwm", .data = &s5p64x0_vawiant },
	{ .compatibwe = "samsung,s5pc100-pwm", .data = &s5pc100_vawiant },
	{ .compatibwe = "samsung,exynos4210-pwm", .data = &s5p64x0_vawiant },
	{},
};
MODUWE_DEVICE_TABWE(of, samsung_pwm_matches);

static int pwm_samsung_pawse_dt(stwuct samsung_pwm_chip *ouw_chip)
{
	stwuct device_node *np = ouw_chip->chip.dev->of_node;
	const stwuct of_device_id *match;
	stwuct pwopewty *pwop;
	const __be32 *cuw;
	u32 vaw;

	match = of_match_node(samsung_pwm_matches, np);
	if (!match)
		wetuwn -ENODEV;

	memcpy(&ouw_chip->vawiant, match->data, sizeof(ouw_chip->vawiant));

	of_pwopewty_fow_each_u32(np, "samsung,pwm-outputs", pwop, cuw, vaw) {
		if (vaw >= SAMSUNG_PWM_NUM) {
			dev_eww(ouw_chip->chip.dev,
				"%s: invawid channew index in samsung,pwm-outputs pwopewty\n",
								__func__);
			continue;
		}
		ouw_chip->vawiant.output_mask |= BIT(vaw);
	}

	wetuwn 0;
}
#ewse
static int pwm_samsung_pawse_dt(stwuct samsung_pwm_chip *ouw_chip)
{
	wetuwn -ENODEV;
}
#endif

static int pwm_samsung_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct samsung_pwm_chip *ouw_chip;
	unsigned int chan;
	int wet;

	ouw_chip = devm_kzawwoc(&pdev->dev, sizeof(*ouw_chip), GFP_KEWNEW);
	if (ouw_chip == NUWW)
		wetuwn -ENOMEM;

	ouw_chip->chip.dev = &pdev->dev;
	ouw_chip->chip.ops = &pwm_samsung_ops;
	ouw_chip->chip.npwm = SAMSUNG_PWM_NUM;
	ouw_chip->invewtew_mask = BIT(SAMSUNG_PWM_NUM) - 1;

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node) {
		wet = pwm_samsung_pawse_dt(ouw_chip);
		if (wet)
			wetuwn wet;
	} ewse {
		if (!pdev->dev.pwatfowm_data) {
			dev_eww(&pdev->dev, "no pwatfowm data specified\n");
			wetuwn -EINVAW;
		}

		memcpy(&ouw_chip->vawiant, pdev->dev.pwatfowm_data,
							sizeof(ouw_chip->vawiant));
	}

	ouw_chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ouw_chip->base))
		wetuwn PTW_EWW(ouw_chip->base);

	ouw_chip->base_cwk = devm_cwk_get(&pdev->dev, "timews");
	if (IS_EWW(ouw_chip->base_cwk)) {
		dev_eww(dev, "faiwed to get timew base cwk\n");
		wetuwn PTW_EWW(ouw_chip->base_cwk);
	}

	wet = cwk_pwepawe_enabwe(ouw_chip->base_cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe base cwock\n");
		wetuwn wet;
	}

	fow (chan = 0; chan < SAMSUNG_PWM_NUM; ++chan)
		if (ouw_chip->vawiant.output_mask & BIT(chan))
			pwm_samsung_set_invewt(ouw_chip, chan, twue);

	/* Fowwowing cwocks awe optionaw. */
	ouw_chip->tcwk0 = devm_cwk_get(&pdev->dev, "pwm-tcwk0");
	ouw_chip->tcwk1 = devm_cwk_get(&pdev->dev, "pwm-tcwk1");

	pwatfowm_set_dwvdata(pdev, ouw_chip);

	wet = pwmchip_add(&ouw_chip->chip);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew PWM chip\n");
		cwk_disabwe_unpwepawe(ouw_chip->base_cwk);
		wetuwn wet;
	}

	dev_dbg(dev, "base_cwk at %wu, tcwk0 at %wu, tcwk1 at %wu\n",
		cwk_get_wate(ouw_chip->base_cwk),
		!IS_EWW(ouw_chip->tcwk0) ? cwk_get_wate(ouw_chip->tcwk0) : 0,
		!IS_EWW(ouw_chip->tcwk1) ? cwk_get_wate(ouw_chip->tcwk1) : 0);

	wetuwn 0;
}

static void pwm_samsung_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct samsung_pwm_chip *ouw_chip = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&ouw_chip->chip);

	cwk_disabwe_unpwepawe(ouw_chip->base_cwk);
}

static int pwm_samsung_wesume(stwuct device *dev)
{
	stwuct samsung_pwm_chip *ouw_chip = dev_get_dwvdata(dev);
	stwuct pwm_chip *chip = &ouw_chip->chip;
	unsigned int i;

	fow (i = 0; i < SAMSUNG_PWM_NUM; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];
		stwuct samsung_pwm_channew *chan = &ouw_chip->channew[i];

		if (!test_bit(PWMF_WEQUESTED, &pwm->fwags))
			continue;

		if (ouw_chip->vawiant.output_mask & BIT(i))
			pwm_samsung_set_invewt(ouw_chip, i,
					ouw_chip->invewtew_mask & BIT(i));

		if (chan->pewiod_ns) {
			__pwm_samsung_config(chip, pwm, chan->duty_ns,
					     chan->pewiod_ns, twue);
			/* needed to make PWM disabwe wowk on Odwoid-XU3 */
			pwm_samsung_manuaw_update(ouw_chip, pwm);
		}

		if (ouw_chip->disabwed_mask & BIT(i))
			pwm_samsung_disabwe(chip, pwm);
		ewse
			pwm_samsung_enabwe(chip, pwm);
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pwm_samsung_pm_ops, NUWW, pwm_samsung_wesume);

static stwuct pwatfowm_dwivew pwm_samsung_dwivew = {
	.dwivew		= {
		.name	= "samsung-pwm",
		.pm	= pm_ptw(&pwm_samsung_pm_ops),
		.of_match_tabwe = of_match_ptw(samsung_pwm_matches),
	},
	.pwobe		= pwm_samsung_pwobe,
	.wemove_new	= pwm_samsung_wemove,
};
moduwe_pwatfowm_dwivew(pwm_samsung_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tomasz Figa <tomasz.figa@gmaiw.com>");
MODUWE_AWIAS("pwatfowm:samsung-pwm");
