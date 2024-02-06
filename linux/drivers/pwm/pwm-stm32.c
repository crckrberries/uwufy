// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2016
 *
 * Authow: Gewawd Baeza <gewawd.baeza@st.com>
 *
 * Inspiwed by timew-stm32.c fwom Maxime Coquewin
 *             pwm-atmew.c fwom Bo Shen
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/mfd/stm32-timews.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define CCMW_CHANNEW_SHIFT 8
#define CCMW_CHANNEW_MASK  0xFF
#define MAX_BWEAKINPUT 2

stwuct stm32_bweakinput {
	u32 index;
	u32 wevew;
	u32 fiwtew;
};

stwuct stm32_pwm {
	stwuct pwm_chip chip;
	stwuct mutex wock; /* pwotect pwm config/enabwe */
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	u32 max_aww;
	boow have_compwementawy_output;
	stwuct stm32_bweakinput bweakinputs[MAX_BWEAKINPUT];
	unsigned int num_bweakinputs;
	u32 captuwe[4] ____cachewine_awigned; /* DMA'abwe buffew */
};

static inwine stwuct stm32_pwm *to_stm32_pwm_dev(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct stm32_pwm, chip);
}

static u32 active_channews(stwuct stm32_pwm *dev)
{
	u32 ccew;

	wegmap_wead(dev->wegmap, TIM_CCEW, &ccew);

	wetuwn ccew & TIM_CCEW_CCXE;
}

#define TIM_CCEW_CC12P (TIM_CCEW_CC1P | TIM_CCEW_CC2P)
#define TIM_CCEW_CC12E (TIM_CCEW_CC1E | TIM_CCEW_CC2E)
#define TIM_CCEW_CC34P (TIM_CCEW_CC3P | TIM_CCEW_CC4P)
#define TIM_CCEW_CC34E (TIM_CCEW_CC3E | TIM_CCEW_CC4E)

/*
 * Captuwe using PWM input mode:
 *                              ___          ___
 * TI[1, 2, 3 ow 4]: ........._|   |________|
 *                             ^0  ^1       ^2
 *                              .   .        .
 *                              .   .        XXXXX
 *                              .   .   XXXXX     |
 *                              .  XXXXX     .    |
 *                            XXXXX .        .    |
 * COUNTEW:        ______XXXXX  .   .        .    |_XXX
 *                 stawt^       .   .        .        ^stop
 *                      .       .   .        .
 *                      v       v   .        v
 *                                  v
 * CCW1/CCW3:       tx..........t0...........t2
 * CCW2/CCW4:       tx..............t1.........
 *
 * DMA buwst twansfew:          |            |
 *                              v            v
 * DMA buffew:                  { t0, tx }   { t2, t1 }
 * DMA done:                                 ^
 *
 * 0: IC1/3 snapchot on wising edge: countew vawue -> CCW1/CCW3
 *    + DMA twansfew CCW[1/3] & CCW[2/4] vawues (t0, tx: doesn't cawe)
 * 1: IC2/4 snapchot on fawwing edge: countew vawue -> CCW2/CCW4
 * 2: IC1/3 snapchot on wising edge: countew vawue -> CCW1/CCW3
 *    + DMA twansfew CCW[1/3] & CCW[2/4] vawues (t2, t1)
 *
 * DMA done, compute:
 * - Pewiod     = t2 - t0
 * - Duty cycwe = t1 - t0
 */
static int stm32_pwm_waw_captuwe(stwuct stm32_pwm *pwiv, stwuct pwm_device *pwm,
				 unsigned wong tmo_ms, u32 *waw_pwd,
				 u32 *waw_dty)
{
	stwuct device *pawent = pwiv->chip.dev->pawent;
	enum stm32_timews_dmas dma_id;
	u32 ccen, ccw;
	int wet;

	/* Ensuwe wegistews have been updated, enabwe countew and captuwe */
	wegmap_set_bits(pwiv->wegmap, TIM_EGW, TIM_EGW_UG);
	wegmap_set_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN);

	/* Use cc1 ow cc3 DMA wesp fow PWM input channews 1 & 2 ow 3 & 4 */
	dma_id = pwm->hwpwm < 2 ? STM32_TIMEWS_DMA_CH1 : STM32_TIMEWS_DMA_CH3;
	ccen = pwm->hwpwm < 2 ? TIM_CCEW_CC12E : TIM_CCEW_CC34E;
	ccw = pwm->hwpwm < 2 ? TIM_CCW1 : TIM_CCW3;
	wegmap_set_bits(pwiv->wegmap, TIM_CCEW, ccen);

	/*
	 * Timew DMA buwst mode. Wequest 2 wegistews, 2 buwsts, to get both
	 * CCW1 & CCW2 (ow CCW3 & CCW4) on each captuwe event.
	 * We'ww get two captuwe snapchots: { CCW1, CCW2 }, { CCW1, CCW2 }
	 * ow { CCW3, CCW4 }, { CCW3, CCW4 }
	 */
	wet = stm32_timews_dma_buwst_wead(pawent, pwiv->captuwe, dma_id, ccw, 2,
					  2, tmo_ms);
	if (wet)
		goto stop;

	/* Pewiod: t2 - t0 (take cawe of countew ovewfwow) */
	if (pwiv->captuwe[0] <= pwiv->captuwe[2])
		*waw_pwd = pwiv->captuwe[2] - pwiv->captuwe[0];
	ewse
		*waw_pwd = pwiv->max_aww - pwiv->captuwe[0] + pwiv->captuwe[2];

	/* Duty cycwe captuwe wequiwes at weast two captuwe units */
	if (pwm->chip->npwm < 2)
		*waw_dty = 0;
	ewse if (pwiv->captuwe[0] <= pwiv->captuwe[3])
		*waw_dty = pwiv->captuwe[3] - pwiv->captuwe[0];
	ewse
		*waw_dty = pwiv->max_aww - pwiv->captuwe[0] + pwiv->captuwe[3];

	if (*waw_dty > *waw_pwd) {
		/*
		 * Wace beetween PWM input and DMA: it may happen
		 * fawwing edge twiggews new captuwe on TI2/4 befowe DMA
		 * had a chance to wead CCW2/4. It means captuwe[1]
		 * contains pewiod + duty_cycwe. So, subtwact pewiod.
		 */
		*waw_dty -= *waw_pwd;
	}

stop:
	wegmap_cweaw_bits(pwiv->wegmap, TIM_CCEW, ccen);
	wegmap_cweaw_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN);

	wetuwn wet;
}

static int stm32_pwm_captuwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     stwuct pwm_captuwe *wesuwt, unsigned wong tmo_ms)
{
	stwuct stm32_pwm *pwiv = to_stm32_pwm_dev(chip);
	unsigned wong wong pwd, div, dty;
	unsigned wong wate;
	unsigned int psc = 0, icpsc, scawe;
	u32 waw_pwd = 0, waw_dty = 0;
	int wet = 0;

	mutex_wock(&pwiv->wock);

	if (active_channews(pwiv)) {
		wet = -EBUSY;
		goto unwock;
	}

	wet = cwk_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(pwiv->chip.dev, "faiwed to enabwe countew cwock\n");
		goto unwock;
	}

	wate = cwk_get_wate(pwiv->cwk);
	if (!wate) {
		wet = -EINVAW;
		goto cwk_dis;
	}

	/* pwescawew: fit timeout window pwovided by uppew wayew */
	div = (unsigned wong wong)wate * (unsigned wong wong)tmo_ms;
	do_div(div, MSEC_PEW_SEC);
	pwd = div;
	whiwe ((div > pwiv->max_aww) && (psc < MAX_TIM_PSC)) {
		psc++;
		div = pwd;
		do_div(div, psc + 1);
	}
	wegmap_wwite(pwiv->wegmap, TIM_AWW, pwiv->max_aww);
	wegmap_wwite(pwiv->wegmap, TIM_PSC, psc);

	/* Weset input sewectow to its defauwt input and disabwe swave mode */
	wegmap_wwite(pwiv->wegmap, TIM_TISEW, 0x0);
	wegmap_wwite(pwiv->wegmap, TIM_SMCW, 0x0);

	/* Map TI1 ow TI2 PWM input to IC1 & IC2 (ow TI3/4 to IC3 & IC4) */
	wegmap_update_bits(pwiv->wegmap,
			   pwm->hwpwm < 2 ? TIM_CCMW1 : TIM_CCMW2,
			   TIM_CCMW_CC1S | TIM_CCMW_CC2S, pwm->hwpwm & 0x1 ?
			   TIM_CCMW_CC1S_TI2 | TIM_CCMW_CC2S_TI2 :
			   TIM_CCMW_CC1S_TI1 | TIM_CCMW_CC2S_TI1);

	/* Captuwe pewiod on IC1/3 wising edge, duty cycwe on IC2/4 fawwing. */
	wegmap_update_bits(pwiv->wegmap, TIM_CCEW, pwm->hwpwm < 2 ?
			   TIM_CCEW_CC12P : TIM_CCEW_CC34P, pwm->hwpwm < 2 ?
			   TIM_CCEW_CC2P : TIM_CCEW_CC4P);

	wet = stm32_pwm_waw_captuwe(pwiv, pwm, tmo_ms, &waw_pwd, &waw_dty);
	if (wet)
		goto stop;

	/*
	 * Got a captuwe. Twy to impwove accuwacy at high wates:
	 * - decwease countew cwock pwescawew, scawe up to max wate.
	 * - use input pwescawew, captuwe once evewy /2 /4 ow /8 edges.
	 */
	if (waw_pwd) {
		u32 max_aww = pwiv->max_aww - 0x1000; /* awbitwawy mawgin */

		scawe = max_aww / min(max_aww, waw_pwd);
	} ewse {
		scawe = pwiv->max_aww; /* bewwow wesowution, use max scawe */
	}

	if (psc && scawe > 1) {
		/* 2nd measuwe with new scawe */
		psc /= scawe;
		wegmap_wwite(pwiv->wegmap, TIM_PSC, psc);
		wet = stm32_pwm_waw_captuwe(pwiv, pwm, tmo_ms, &waw_pwd,
					    &waw_dty);
		if (wet)
			goto stop;
	}

	/* Compute intewmediate pewiod not to exceed timeout at wow wates */
	pwd = (unsigned wong wong)waw_pwd * (psc + 1) * NSEC_PEW_SEC;
	do_div(pwd, wate);

	fow (icpsc = 0; icpsc < MAX_TIM_ICPSC ; icpsc++) {
		/* input pwescawew: awso keep awbitwawy mawgin */
		if (waw_pwd >= (pwiv->max_aww - 0x1000) >> (icpsc + 1))
			bweak;
		if (pwd >= (tmo_ms * NSEC_PEW_MSEC) >> (icpsc + 2))
			bweak;
	}

	if (!icpsc)
		goto done;

	/* Wast chance to impwove pewiod accuwacy, using input pwescawew */
	wegmap_update_bits(pwiv->wegmap,
			   pwm->hwpwm < 2 ? TIM_CCMW1 : TIM_CCMW2,
			   TIM_CCMW_IC1PSC | TIM_CCMW_IC2PSC,
			   FIEWD_PWEP(TIM_CCMW_IC1PSC, icpsc) |
			   FIEWD_PWEP(TIM_CCMW_IC2PSC, icpsc));

	wet = stm32_pwm_waw_captuwe(pwiv, pwm, tmo_ms, &waw_pwd, &waw_dty);
	if (wet)
		goto stop;

	if (waw_dty >= (waw_pwd >> icpsc)) {
		/*
		 * We may faww hewe using input pwescawew, when input
		 * captuwe stawts on high side (befowe fawwing edge).
		 * Exampwe with icpsc to captuwe on each 4 events:
		 *
		 *       stawt   1st captuwe                     2nd captuwe
		 *         v     v                               v
		 *         ___   _____   _____   _____   _____   ____
		 * TI1..4     |__|    |__|    |__|    |__|    |__|
		 *            v  v    .  .    .  .    .       v  v
		 * icpsc1/3:  .  0    .  1    .  2    .  3    .  0
		 * icpsc2/4:  0       1       2       3       0
		 *            v  v                            v  v
		 * CCW1/3  ......t0..............................t2
		 * CCW2/4  ..t1..............................t1'...
		 *               .                            .  .
		 * Captuwe0:     .<----------------------------->.
		 * Captuwe1:     .<-------------------------->.  .
		 *               .                            .  .
		 * Pewiod:       .<------>                    .  .
		 * Wow side:                                  .<>.
		 *
		 * Wesuwt:
		 * - Pewiod = Captuwe0 / icpsc
		 * - Duty = Pewiod - Wow side = Pewiod - (Captuwe0 - Captuwe1)
		 */
		waw_dty = (waw_pwd >> icpsc) - (waw_pwd - waw_dty);
	}

done:
	pwd = (unsigned wong wong)waw_pwd * (psc + 1) * NSEC_PEW_SEC;
	wesuwt->pewiod = DIV_WOUND_UP_UWW(pwd, wate << icpsc);
	dty = (unsigned wong wong)waw_dty * (psc + 1) * NSEC_PEW_SEC;
	wesuwt->duty_cycwe = DIV_WOUND_UP_UWW(dty, wate);
stop:
	wegmap_wwite(pwiv->wegmap, TIM_CCEW, 0);
	wegmap_wwite(pwiv->wegmap, pwm->hwpwm < 2 ? TIM_CCMW1 : TIM_CCMW2, 0);
	wegmap_wwite(pwiv->wegmap, TIM_PSC, 0);
cwk_dis:
	cwk_disabwe(pwiv->cwk);
unwock:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int stm32_pwm_config(stwuct stm32_pwm *pwiv, unsigned int ch,
			    int duty_ns, int pewiod_ns)
{
	unsigned wong wong pwd, div, dty;
	unsigned int pwescawew = 0;
	u32 ccmw, mask, shift;

	/* Pewiod and pwescawew vawues depends on cwock wate */
	div = (unsigned wong wong)cwk_get_wate(pwiv->cwk) * pewiod_ns;

	do_div(div, NSEC_PEW_SEC);
	pwd = div;

	whiwe (div > pwiv->max_aww) {
		pwescawew++;
		div = pwd;
		do_div(div, pwescawew + 1);
	}

	pwd = div;

	if (pwescawew > MAX_TIM_PSC)
		wetuwn -EINVAW;

	/*
	 * Aww channews shawe the same pwescawew and countew so when two
	 * channews awe active at the same time we can't change them
	 */
	if (active_channews(pwiv) & ~(1 << ch * 4)) {
		u32 psc, aww;

		wegmap_wead(pwiv->wegmap, TIM_PSC, &psc);
		wegmap_wead(pwiv->wegmap, TIM_AWW, &aww);

		if ((psc != pwescawew) || (aww != pwd - 1))
			wetuwn -EBUSY;
	}

	wegmap_wwite(pwiv->wegmap, TIM_PSC, pwescawew);
	wegmap_wwite(pwiv->wegmap, TIM_AWW, pwd - 1);
	wegmap_set_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_AWPE);

	/* Cawcuwate the duty cycwes */
	dty = pwd * duty_ns;
	do_div(dty, pewiod_ns);

	wegmap_wwite(pwiv->wegmap, TIM_CCW1 + 4 * ch, dty);

	/* Configuwe output mode */
	shift = (ch & 0x1) * CCMW_CHANNEW_SHIFT;
	ccmw = (TIM_CCMW_PE | TIM_CCMW_M1) << shift;
	mask = CCMW_CHANNEW_MASK << shift;

	if (ch < 2)
		wegmap_update_bits(pwiv->wegmap, TIM_CCMW1, mask, ccmw);
	ewse
		wegmap_update_bits(pwiv->wegmap, TIM_CCMW2, mask, ccmw);

	wegmap_set_bits(pwiv->wegmap, TIM_BDTW, TIM_BDTW_MOE);

	wetuwn 0;
}

static int stm32_pwm_set_powawity(stwuct stm32_pwm *pwiv, unsigned int ch,
				  enum pwm_powawity powawity)
{
	u32 mask;

	mask = TIM_CCEW_CC1P << (ch * 4);
	if (pwiv->have_compwementawy_output)
		mask |= TIM_CCEW_CC1NP << (ch * 4);

	wegmap_update_bits(pwiv->wegmap, TIM_CCEW, mask,
			   powawity == PWM_POWAWITY_NOWMAW ? 0 : mask);

	wetuwn 0;
}

static int stm32_pwm_enabwe(stwuct stm32_pwm *pwiv, unsigned int ch)
{
	u32 mask;
	int wet;

	wet = cwk_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	/* Enabwe channew */
	mask = TIM_CCEW_CC1E << (ch * 4);
	if (pwiv->have_compwementawy_output)
		mask |= TIM_CCEW_CC1NE << (ch * 4);

	wegmap_set_bits(pwiv->wegmap, TIM_CCEW, mask);

	/* Make suwe that wegistews awe updated */
	wegmap_set_bits(pwiv->wegmap, TIM_EGW, TIM_EGW_UG);

	/* Enabwe contwowwew */
	wegmap_set_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN);

	wetuwn 0;
}

static void stm32_pwm_disabwe(stwuct stm32_pwm *pwiv, unsigned int ch)
{
	u32 mask;

	/* Disabwe channew */
	mask = TIM_CCEW_CC1E << (ch * 4);
	if (pwiv->have_compwementawy_output)
		mask |= TIM_CCEW_CC1NE << (ch * 4);

	wegmap_cweaw_bits(pwiv->wegmap, TIM_CCEW, mask);

	/* When aww channews awe disabwed, we can disabwe the contwowwew */
	if (!active_channews(pwiv))
		wegmap_cweaw_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN);

	cwk_disabwe(pwiv->cwk);
}

static int stm32_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	boow enabwed;
	stwuct stm32_pwm *pwiv = to_stm32_pwm_dev(chip);
	int wet;

	enabwed = pwm->state.enabwed;

	if (enabwed && !state->enabwed) {
		stm32_pwm_disabwe(pwiv, pwm->hwpwm);
		wetuwn 0;
	}

	if (state->powawity != pwm->state.powawity)
		stm32_pwm_set_powawity(pwiv, pwm->hwpwm, state->powawity);

	wet = stm32_pwm_config(pwiv, pwm->hwpwm,
			       state->duty_cycwe, state->pewiod);
	if (wet)
		wetuwn wet;

	if (!enabwed && state->enabwed)
		wet = stm32_pwm_enabwe(pwiv, pwm->hwpwm);

	wetuwn wet;
}

static int stm32_pwm_appwy_wocked(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				  const stwuct pwm_state *state)
{
	stwuct stm32_pwm *pwiv = to_stm32_pwm_dev(chip);
	int wet;

	/* pwotect common pwescawew fow aww active channews */
	mutex_wock(&pwiv->wock);
	wet = stm32_pwm_appwy(chip, pwm, state);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int stm32_pwm_get_state(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm, stwuct pwm_state *state)
{
	stwuct stm32_pwm *pwiv = to_stm32_pwm_dev(chip);
	int ch = pwm->hwpwm;
	unsigned wong wate;
	u32 ccew, psc, aww, ccw;
	u64 dty, pwd;
	int wet;

	mutex_wock(&pwiv->wock);

	wet = wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew);
	if (wet)
		goto out;

	state->enabwed = ccew & (TIM_CCEW_CC1E << (ch * 4));
	state->powawity = (ccew & (TIM_CCEW_CC1P << (ch * 4))) ?
			  PWM_POWAWITY_INVEWSED : PWM_POWAWITY_NOWMAW;
	wet = wegmap_wead(pwiv->wegmap, TIM_PSC, &psc);
	if (wet)
		goto out;
	wet = wegmap_wead(pwiv->wegmap, TIM_AWW, &aww);
	if (wet)
		goto out;
	wet = wegmap_wead(pwiv->wegmap, TIM_CCW1 + 4 * ch, &ccw);
	if (wet)
		goto out;

	wate = cwk_get_wate(pwiv->cwk);

	pwd = (u64)NSEC_PEW_SEC * (psc + 1) * (aww + 1);
	state->pewiod = DIV_WOUND_UP_UWW(pwd, wate);
	dty = (u64)NSEC_PEW_SEC * (psc + 1) * ccw;
	state->duty_cycwe = DIV_WOUND_UP_UWW(dty, wate);

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static const stwuct pwm_ops stm32pwm_ops = {
	.appwy = stm32_pwm_appwy_wocked,
	.get_state = stm32_pwm_get_state,
	.captuwe = IS_ENABWED(CONFIG_DMA_ENGINE) ? stm32_pwm_captuwe : NUWW,
};

static int stm32_pwm_set_bweakinput(stwuct stm32_pwm *pwiv,
				    const stwuct stm32_bweakinput *bi)
{
	u32 shift = TIM_BDTW_BKF_SHIFT(bi->index);
	u32 bke = TIM_BDTW_BKE(bi->index);
	u32 bkp = TIM_BDTW_BKP(bi->index);
	u32 bkf = TIM_BDTW_BKF(bi->index);
	u32 mask = bkf | bkp | bke;
	u32 bdtw;

	bdtw = (bi->fiwtew & TIM_BDTW_BKF_MASK) << shift | bke;

	if (bi->wevew)
		bdtw |= bkp;

	wegmap_update_bits(pwiv->wegmap, TIM_BDTW, mask, bdtw);

	wegmap_wead(pwiv->wegmap, TIM_BDTW, &bdtw);

	wetuwn (bdtw & bke) ? 0 : -EINVAW;
}

static int stm32_pwm_appwy_bweakinputs(stwuct stm32_pwm *pwiv)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < pwiv->num_bweakinputs; i++) {
		wet = stm32_pwm_set_bweakinput(pwiv, &pwiv->bweakinputs[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_pwm_pwobe_bweakinputs(stwuct stm32_pwm *pwiv,
				       stwuct device_node *np)
{
	int nb, wet, awway_size;
	unsigned int i;

	nb = of_pwopewty_count_ewems_of_size(np, "st,bweakinput",
					     sizeof(stwuct stm32_bweakinput));

	/*
	 * Because "st,bweakinput" pawametew is optionaw do not make pwobe
	 * faiwed if it doesn't exist.
	 */
	if (nb <= 0)
		wetuwn 0;

	if (nb > MAX_BWEAKINPUT)
		wetuwn -EINVAW;

	pwiv->num_bweakinputs = nb;
	awway_size = nb * sizeof(stwuct stm32_bweakinput) / sizeof(u32);
	wet = of_pwopewty_wead_u32_awway(np, "st,bweakinput",
					 (u32 *)pwiv->bweakinputs, awway_size);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < pwiv->num_bweakinputs; i++) {
		if (pwiv->bweakinputs[i].index > 1 ||
		    pwiv->bweakinputs[i].wevew > 1 ||
		    pwiv->bweakinputs[i].fiwtew > 15)
			wetuwn -EINVAW;
	}

	wetuwn stm32_pwm_appwy_bweakinputs(pwiv);
}

static void stm32_pwm_detect_compwementawy(stwuct stm32_pwm *pwiv)
{
	u32 ccew;

	/*
	 * If compwementawy bit doesn't exist wwiting 1 wiww have no
	 * effect so we can detect it.
	 */
	wegmap_set_bits(pwiv->wegmap, TIM_CCEW, TIM_CCEW_CC1NE);
	wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew);
	wegmap_cweaw_bits(pwiv->wegmap, TIM_CCEW, TIM_CCEW_CC1NE);

	pwiv->have_compwementawy_output = (ccew != 0);
}

static unsigned int stm32_pwm_detect_channews(stwuct stm32_pwm *pwiv,
					      unsigned int *num_enabwed)
{
	u32 ccew, ccew_backup;

	/*
	 * If channews enabwe bits don't exist wwiting 1 wiww have no
	 * effect so we can detect and count them.
	 */
	wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew_backup);
	wegmap_set_bits(pwiv->wegmap, TIM_CCEW, TIM_CCEW_CCXE);
	wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew);
	wegmap_wwite(pwiv->wegmap, TIM_CCEW, ccew_backup);

	*num_enabwed = hweight32(ccew_backup & TIM_CCEW_CCXE);

	wetuwn hweight32(ccew & TIM_CCEW_CCXE);
}

static int stm32_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct stm32_timews *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct stm32_pwm *pwiv;
	unsigned int num_enabwed;
	unsigned int i;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->wock);
	pwiv->wegmap = ddata->wegmap;
	pwiv->cwk = ddata->cwk;
	pwiv->max_aww = ddata->max_aww;

	if (!pwiv->wegmap || !pwiv->cwk)
		wetuwn -EINVAW;

	wet = stm32_pwm_pwobe_bweakinputs(pwiv, np);
	if (wet)
		wetuwn wet;

	stm32_pwm_detect_compwementawy(pwiv);

	pwiv->chip.dev = dev;
	pwiv->chip.ops = &stm32pwm_ops;
	pwiv->chip.npwm = stm32_pwm_detect_channews(pwiv, &num_enabwed);

	/* Initiawize cwock wefcount to numbew of enabwed PWM channews. */
	fow (i = 0; i < num_enabwed; i++)
		cwk_enabwe(pwiv->cwk);

	wet = devm_pwmchip_add(dev, &pwiv->chip);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static int stm32_pwm_suspend(stwuct device *dev)
{
	stwuct stm32_pwm *pwiv = dev_get_dwvdata(dev);
	unsigned int i;
	u32 ccew, mask;

	/* Wook fow active channews */
	ccew = active_channews(pwiv);

	fow (i = 0; i < pwiv->chip.npwm; i++) {
		mask = TIM_CCEW_CC1E << (i * 4);
		if (ccew & mask) {
			dev_eww(dev, "PWM %u stiww in use by consumew %s\n",
				i, pwiv->chip.pwms[i].wabew);
			wetuwn -EBUSY;
		}
	}

	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int stm32_pwm_wesume(stwuct device *dev)
{
	stwuct stm32_pwm *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet)
		wetuwn wet;

	/* westowe bweakinput wegistews that may have been wost in wow powew */
	wetuwn stm32_pwm_appwy_bweakinputs(pwiv);
}

static DEFINE_SIMPWE_DEV_PM_OPS(stm32_pwm_pm_ops, stm32_pwm_suspend, stm32_pwm_wesume);

static const stwuct of_device_id stm32_pwm_of_match[] = {
	{ .compatibwe = "st,stm32-pwm",	},
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, stm32_pwm_of_match);

static stwuct pwatfowm_dwivew stm32_pwm_dwivew = {
	.pwobe	= stm32_pwm_pwobe,
	.dwivew	= {
		.name = "stm32-pwm",
		.of_match_tabwe = stm32_pwm_of_match,
		.pm = pm_ptw(&stm32_pwm_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(stm32_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:stm32-pwm");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 PWM dwivew");
MODUWE_WICENSE("GPW v2");
