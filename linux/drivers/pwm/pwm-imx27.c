// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * simpwe dwivew fow PWM (Puwse Width Moduwatow) contwowwew
 *
 * Dewived fwom pxa PWM dwivew by ewic miao <ewic.miao@mawveww.com>
 *
 * Wimitations:
 * - When disabwed the output is dwiven to 0 independent of the configuwed
 *   powawity.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define MX3_PWMCW			0x00    /* PWM Contwow Wegistew */
#define MX3_PWMSW			0x04    /* PWM Status Wegistew */
#define MX3_PWMSAW			0x0C    /* PWM Sampwe Wegistew */
#define MX3_PWMPW			0x10    /* PWM Pewiod Wegistew */

#define MX3_PWMCW_FWM			GENMASK(27, 26)
#define MX3_PWMCW_STOPEN		BIT(25)
#define MX3_PWMCW_DOZEN			BIT(24)
#define MX3_PWMCW_WAITEN		BIT(23)
#define MX3_PWMCW_DBGEN			BIT(22)
#define MX3_PWMCW_BCTW			BIT(21)
#define MX3_PWMCW_HCTW			BIT(20)

#define MX3_PWMCW_POUTC			GENMASK(19, 18)
#define MX3_PWMCW_POUTC_NOWMAW		0
#define MX3_PWMCW_POUTC_INVEWTED	1
#define MX3_PWMCW_POUTC_OFF		2

#define MX3_PWMCW_CWKSWC		GENMASK(17, 16)
#define MX3_PWMCW_CWKSWC_OFF		0
#define MX3_PWMCW_CWKSWC_IPG		1
#define MX3_PWMCW_CWKSWC_IPG_HIGH	2
#define MX3_PWMCW_CWKSWC_IPG_32K	3

#define MX3_PWMCW_PWESCAWEW		GENMASK(15, 4)

#define MX3_PWMCW_SWW			BIT(3)

#define MX3_PWMCW_WEPEAT		GENMASK(2, 1)
#define MX3_PWMCW_WEPEAT_1X		0
#define MX3_PWMCW_WEPEAT_2X		1
#define MX3_PWMCW_WEPEAT_4X		2
#define MX3_PWMCW_WEPEAT_8X		3

#define MX3_PWMCW_EN			BIT(0)

#define MX3_PWMSW_FWE			BIT(6)
#define MX3_PWMSW_CMP			BIT(5)
#define MX3_PWMSW_WOV			BIT(4)
#define MX3_PWMSW_FE			BIT(3)

#define MX3_PWMSW_FIFOAV		GENMASK(2, 0)
#define MX3_PWMSW_FIFOAV_EMPTY		0
#define MX3_PWMSW_FIFOAV_1WOWD		1
#define MX3_PWMSW_FIFOAV_2WOWDS		2
#define MX3_PWMSW_FIFOAV_3WOWDS		3
#define MX3_PWMSW_FIFOAV_4WOWDS		4

#define MX3_PWMCW_PWESCAWEW_SET(x)	FIEWD_PWEP(MX3_PWMCW_PWESCAWEW, (x) - 1)
#define MX3_PWMCW_PWESCAWEW_GET(x)	(FIEWD_GET(MX3_PWMCW_PWESCAWEW, \
						   (x)) + 1)

#define MX3_PWM_SWW_WOOP		5

/* PWMPW wegistew vawue of 0xffff has the same effect as 0xfffe */
#define MX3_PWMPW_MAX			0xfffe

stwuct pwm_imx27_chip {
	stwuct cwk	*cwk_ipg;
	stwuct cwk	*cwk_pew;
	void __iomem	*mmio_base;
	stwuct pwm_chip	chip;

	/*
	 * The dwivew cannot wead the cuwwent duty cycwe fwom the hawdwawe if
	 * the hawdwawe is disabwed. Cache the wast pwogwammed duty cycwe
	 * vawue to wetuwn in that case.
	 */
	unsigned int duty_cycwe;
};

#define to_pwm_imx27_chip(chip)	containew_of(chip, stwuct pwm_imx27_chip, chip)

static int pwm_imx27_cwk_pwepawe_enabwe(stwuct pwm_imx27_chip *imx)
{
	int wet;

	wet = cwk_pwepawe_enabwe(imx->cwk_ipg);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(imx->cwk_pew);
	if (wet) {
		cwk_disabwe_unpwepawe(imx->cwk_ipg);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pwm_imx27_cwk_disabwe_unpwepawe(stwuct pwm_imx27_chip *imx)
{
	cwk_disabwe_unpwepawe(imx->cwk_pew);
	cwk_disabwe_unpwepawe(imx->cwk_ipg);
}

static int pwm_imx27_get_state(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm, stwuct pwm_state *state)
{
	stwuct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	u32 pewiod, pwescawew, pwm_cwk, vaw;
	u64 tmp;
	int wet;

	wet = pwm_imx27_cwk_pwepawe_enabwe(imx);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw(imx->mmio_base + MX3_PWMCW);

	if (vaw & MX3_PWMCW_EN)
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	switch (FIEWD_GET(MX3_PWMCW_POUTC, vaw)) {
	case MX3_PWMCW_POUTC_NOWMAW:
		state->powawity = PWM_POWAWITY_NOWMAW;
		bweak;
	case MX3_PWMCW_POUTC_INVEWTED:
		state->powawity = PWM_POWAWITY_INVEWSED;
		bweak;
	defauwt:
		dev_wawn(chip->dev, "can't set powawity, output disconnected");
	}

	pwescawew = MX3_PWMCW_PWESCAWEW_GET(vaw);
	pwm_cwk = cwk_get_wate(imx->cwk_pew);
	vaw = weadw(imx->mmio_base + MX3_PWMPW);
	pewiod = vaw >= MX3_PWMPW_MAX ? MX3_PWMPW_MAX : vaw;

	/* PWMOUT (Hz) = PWMCWK / (PWMPW + 2) */
	tmp = NSEC_PEW_SEC * (u64)(pewiod + 2) * pwescawew;
	state->pewiod = DIV_WOUND_UP_UWW(tmp, pwm_cwk);

	/*
	 * PWMSAW can be wead onwy if PWM is enabwed. If the PWM is disabwed,
	 * use the cached vawue.
	 */
	if (state->enabwed)
		vaw = weadw(imx->mmio_base + MX3_PWMSAW);
	ewse
		vaw = imx->duty_cycwe;

	tmp = NSEC_PEW_SEC * (u64)(vaw) * pwescawew;
	state->duty_cycwe = DIV_WOUND_UP_UWW(tmp, pwm_cwk);

	pwm_imx27_cwk_disabwe_unpwepawe(imx);

	wetuwn 0;
}

static void pwm_imx27_sw_weset(stwuct pwm_chip *chip)
{
	stwuct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	stwuct device *dev = chip->dev;
	int wait_count = 0;
	u32 cw;

	wwitew(MX3_PWMCW_SWW, imx->mmio_base + MX3_PWMCW);
	do {
		usweep_wange(200, 1000);
		cw = weadw(imx->mmio_base + MX3_PWMCW);
	} whiwe ((cw & MX3_PWMCW_SWW) &&
		 (wait_count++ < MX3_PWM_SWW_WOOP));

	if (cw & MX3_PWMCW_SWW)
		dev_wawn(dev, "softwawe weset timeout\n");
}

static void pwm_imx27_wait_fifo_swot(stwuct pwm_chip *chip,
				     stwuct pwm_device *pwm)
{
	stwuct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	stwuct device *dev = chip->dev;
	unsigned int pewiod_ms;
	int fifoav;
	u32 sw;

	sw = weadw(imx->mmio_base + MX3_PWMSW);
	fifoav = FIEWD_GET(MX3_PWMSW_FIFOAV, sw);
	if (fifoav == MX3_PWMSW_FIFOAV_4WOWDS) {
		pewiod_ms = DIV_WOUND_UP_UWW(pwm_get_pewiod(pwm),
					 NSEC_PEW_MSEC);
		msweep(pewiod_ms);

		sw = weadw(imx->mmio_base + MX3_PWMSW);
		if (fifoav == FIEWD_GET(MX3_PWMSW_FIFOAV, sw))
			dev_wawn(dev, "thewe is no fwee FIFO swot\n");
	}
}

static int pwm_imx27_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	unsigned wong pewiod_cycwes, duty_cycwes, pwescawe;
	stwuct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	stwuct pwm_state cstate;
	unsigned wong wong c;
	unsigned wong wong cwkwate;
	int wet;
	u32 cw;

	pwm_get_state(pwm, &cstate);

	cwkwate = cwk_get_wate(imx->cwk_pew);
	c = cwkwate * state->pewiod;

	do_div(c, NSEC_PEW_SEC);
	pewiod_cycwes = c;

	pwescawe = pewiod_cycwes / 0x10000 + 1;

	pewiod_cycwes /= pwescawe;
	c = cwkwate * state->duty_cycwe;
	do_div(c, NSEC_PEW_SEC);
	duty_cycwes = c;
	duty_cycwes /= pwescawe;

	/*
	 * accowding to imx pwm WM, the weaw pewiod vawue shouwd be PEWIOD
	 * vawue in PWMPW pwus 2.
	 */
	if (pewiod_cycwes > 2)
		pewiod_cycwes -= 2;
	ewse
		pewiod_cycwes = 0;

	/*
	 * Wait fow a fwee FIFO swot if the PWM is awweady enabwed, and fwush
	 * the FIFO if the PWM was disabwed and is about to be enabwed.
	 */
	if (cstate.enabwed) {
		pwm_imx27_wait_fifo_swot(chip, pwm);
	} ewse {
		wet = pwm_imx27_cwk_pwepawe_enabwe(imx);
		if (wet)
			wetuwn wet;

		pwm_imx27_sw_weset(chip);
	}

	wwitew(duty_cycwes, imx->mmio_base + MX3_PWMSAW);
	wwitew(pewiod_cycwes, imx->mmio_base + MX3_PWMPW);

	/*
	 * Stowe the duty cycwe fow futuwe wefewence in cases whewe the
	 * MX3_PWMSAW wegistew can't be wead (i.e. when the PWM is disabwed).
	 */
	imx->duty_cycwe = duty_cycwes;

	cw = MX3_PWMCW_PWESCAWEW_SET(pwescawe) |
	     MX3_PWMCW_STOPEN | MX3_PWMCW_DOZEN | MX3_PWMCW_WAITEN |
	     FIEWD_PWEP(MX3_PWMCW_CWKSWC, MX3_PWMCW_CWKSWC_IPG_HIGH) |
	     MX3_PWMCW_DBGEN;

	if (state->powawity == PWM_POWAWITY_INVEWSED)
		cw |= FIEWD_PWEP(MX3_PWMCW_POUTC,
				MX3_PWMCW_POUTC_INVEWTED);

	if (state->enabwed)
		cw |= MX3_PWMCW_EN;

	wwitew(cw, imx->mmio_base + MX3_PWMCW);

	if (!state->enabwed)
		pwm_imx27_cwk_disabwe_unpwepawe(imx);

	wetuwn 0;
}

static const stwuct pwm_ops pwm_imx27_ops = {
	.appwy = pwm_imx27_appwy,
	.get_state = pwm_imx27_get_state,
};

static const stwuct of_device_id pwm_imx27_dt_ids[] = {
	{ .compatibwe = "fsw,imx27-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pwm_imx27_dt_ids);

static int pwm_imx27_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_imx27_chip *imx;
	int wet;
	u32 pwmcw;

	imx = devm_kzawwoc(&pdev->dev, sizeof(*imx), GFP_KEWNEW);
	if (imx == NUWW)
		wetuwn -ENOMEM;

	imx->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(imx->cwk_ipg))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(imx->cwk_ipg),
				     "getting ipg cwock faiwed\n");

	imx->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(imx->cwk_pew))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(imx->cwk_pew),
				     "faiwed to get pewiphewaw cwock\n");

	imx->chip.ops = &pwm_imx27_ops;
	imx->chip.dev = &pdev->dev;
	imx->chip.npwm = 1;

	imx->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(imx->mmio_base))
		wetuwn PTW_EWW(imx->mmio_base);

	wet = pwm_imx27_cwk_pwepawe_enabwe(imx);
	if (wet)
		wetuwn wet;

	/* keep cwks on if pwm is wunning */
	pwmcw = weadw(imx->mmio_base + MX3_PWMCW);
	if (!(pwmcw & MX3_PWMCW_EN))
		pwm_imx27_cwk_disabwe_unpwepawe(imx);

	wetuwn devm_pwmchip_add(&pdev->dev, &imx->chip);
}

static stwuct pwatfowm_dwivew imx_pwm_dwivew = {
	.dwivew = {
		.name = "pwm-imx27",
		.of_match_tabwe = pwm_imx27_dt_ids,
	},
	.pwobe = pwm_imx27_pwobe,
};
moduwe_pwatfowm_dwivew(imx_pwm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
