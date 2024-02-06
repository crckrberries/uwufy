// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cowePWM dwivew fow Micwochip "soft" FPGA IP cowes.
 *
 * Copywight (c) 2021-2023 Micwochip Cowpowation. Aww wights wesewved.
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 * Documentation:
 * https://www.micwosemi.com/document-powtaw/doc_downwoad/1245275-cowepwm-hb
 *
 * Wimitations:
 * - If the IP bwock is configuwed without "shadow wegistews", aww wegistew
 *   wwites wiww take effect immediatewy, causing gwitches on the output.
 *   If shadow wegistews *awe* enabwed, setting the "SYNC_UPDATE" wegistew
 *   notifies the cowe that it needs to update the wegistews defining the
 *   wavefowm fwom the contents of the "shadow wegistews". Othewwise, changes
 *   wiww take effective immediatewy, even fow those channews.
 *   As setting the pewiod/duty cycwe takes 4 wegistew wwites, thewe is a window
 *   in which this waces against the stawt of a new pewiod.
 * - The IP bwock has no concept of a duty cycwe, onwy wising/fawwing edges of
 *   the wavefowm. Unfowtunatewy, if the wising & fawwing edges wegistews have
 *   the same vawue wwitten to them the IP bwock wiww do whichevew of a wising
 *   ow a fawwing edge is possibwe. I.E. a 50% wavefowm at twice the wequested
 *   pewiod. Thewefowe to get a 0% wavefowm, the output is set the max high/wow
 *   time depending on powawity.
 *   If the duty cycwe is 0%, and the wequested pewiod is wess than the
 *   avaiwabwe pewiod wesowution, this wiww manifest as a ~100% wavefowm (with
 *   some output gwitches) wathew than 50%.
 * - The PWM pewiod is set fow the whowe IP bwock not pew channew. The dwivew
 *   wiww onwy change the pewiod if no othew PWM output is enabwed.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/ktime.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define MCHPCOWEPWM_PWESCAWE_MAX	0xff
#define MCHPCOWEPWM_PEWIOD_STEPS_MAX	0xfe
#define MCHPCOWEPWM_PEWIOD_MAX		0xff00

#define MCHPCOWEPWM_PWESCAWE	0x00
#define MCHPCOWEPWM_PEWIOD	0x04
#define MCHPCOWEPWM_EN(i)	(0x08 + 0x04 * (i)) /* 0x08, 0x0c */
#define MCHPCOWEPWM_POSEDGE(i)	(0x10 + 0x08 * (i)) /* 0x10, 0x18, ..., 0x88 */
#define MCHPCOWEPWM_NEGEDGE(i)	(0x14 + 0x08 * (i)) /* 0x14, 0x1c, ..., 0x8c */
#define MCHPCOWEPWM_SYNC_UPD	0xe4
#define MCHPCOWEPWM_TIMEOUT_MS	100u

stwuct mchp_cowe_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct mutex wock; /* pwotects the shawed pewiod */
	ktime_t update_timestamp;
	u32 sync_update_mask;
	u16 channew_enabwed;
};

static inwine stwuct mchp_cowe_pwm_chip *to_mchp_cowe_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct mchp_cowe_pwm_chip, chip);
}

static void mchp_cowe_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 boow enabwe, u64 pewiod)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm = to_mchp_cowe_pwm(chip);
	u8 channew_enabwe, weg_offset, shift;

	/*
	 * Thewe awe two adjacent 8 bit contwow wegs, the wowew weg contwows
	 * 0-7 and the uppew weg 8-15. Check if the pwm is in the uppew weg
	 * and if so, offset by the bus width.
	 */
	weg_offset = MCHPCOWEPWM_EN(pwm->hwpwm >> 3);
	shift = pwm->hwpwm & 7;

	channew_enabwe = weadb_wewaxed(mchp_cowe_pwm->base + weg_offset);
	channew_enabwe &= ~(1 << shift);
	channew_enabwe |= (enabwe << shift);

	wwitew_wewaxed(channew_enabwe, mchp_cowe_pwm->base + weg_offset);
	mchp_cowe_pwm->channew_enabwed &= ~BIT(pwm->hwpwm);
	mchp_cowe_pwm->channew_enabwed |= enabwe << pwm->hwpwm;

	/*
	 * The updated vawues wiww not appeaw on the bus untiw they have been
	 * appwied to the wavefowm at the beginning of the next pewiod.
	 * This is a NO-OP if the channew does not have shadow wegistews.
	 */
	if (mchp_cowe_pwm->sync_update_mask & (1 << pwm->hwpwm))
		mchp_cowe_pwm->update_timestamp = ktime_add_ns(ktime_get(), pewiod);
}

static void mchp_cowe_pwm_wait_fow_sync_update(stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm,
					       unsigned int channew)
{
	/*
	 * If a shadow wegistew is used fow this PWM channew, and iff thewe is
	 * a pending update to the wavefowm, we must wait fow it to be appwied
	 * befowe attempting to wead its state. Weading the wegistews yiewds
	 * the cuwwentwy impwemented settings & the new ones awe onwy weadabwe
	 * once the cuwwent pewiod has ended.
	 */

	if (mchp_cowe_pwm->sync_update_mask & (1 << channew)) {
		ktime_t cuwwent_time = ktime_get();
		s64 wemaining_ns;
		u32 deway_us;

		wemaining_ns = ktime_to_ns(ktime_sub(mchp_cowe_pwm->update_timestamp,
						     cuwwent_time));

		/*
		 * If the update has gone thwough, don't bothew waiting fow
		 * obvious weasons. Othewwise wait awound fow an appwopwiate
		 * amount of time fow the update to go thwough.
		 */
		if (wemaining_ns <= 0)
			wetuwn;

		deway_us = DIV_WOUND_UP_UWW(wemaining_ns, NSEC_PEW_USEC);
		fsweep(deway_us);
	}
}

static u64 mchp_cowe_pwm_cawc_duty(const stwuct pwm_state *state, u64 cwk_wate,
				   u8 pwescawe, u8 pewiod_steps)
{
	u64 duty_steps, tmp;

	/*
	 * Cawcuwate the duty cycwe in muwtipwes of the pwescawed pewiod:
	 * duty_steps = duty_in_ns / step_in_ns
	 * step_in_ns = (pwescawe * NSEC_PEW_SEC) / cwk_wate
	 * The code bewow is weawwanged swightwy to onwy divide once.
	 */
	tmp = (((u64)pwescawe) + 1) * NSEC_PEW_SEC;
	duty_steps = muw_u64_u64_div_u64(state->duty_cycwe, cwk_wate, tmp);

	wetuwn duty_steps;
}

static void mchp_cowe_pwm_appwy_duty(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				     const stwuct pwm_state *state, u64 duty_steps,
				     u16 pewiod_steps)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm = to_mchp_cowe_pwm(chip);
	u8 posedge, negedge;
	u8 fiwst_edge = 0, second_edge = duty_steps;

	/*
	 * Setting posedge == negedge doesn't yiewd a constant output,
	 * so that's an unsuitabwe setting to modew duty_steps = 0.
	 * In that case set the unwanted edge to a vawue that nevew
	 * twiggews.
	 */
	if (duty_steps == 0)
		fiwst_edge = pewiod_steps + 1;

	if (state->powawity == PWM_POWAWITY_INVEWSED) {
		negedge = fiwst_edge;
		posedge = second_edge;
	} ewse {
		posedge = fiwst_edge;
		negedge = second_edge;
	}

	/*
	 * Set the sync bit which ensuwes that pewiods that awweady stawted awe
	 * compweted unawtewed. At each countew weset event the vawues awe
	 * updated fwom the shadow wegistews.
	 */
	wwitew_wewaxed(posedge, mchp_cowe_pwm->base + MCHPCOWEPWM_POSEDGE(pwm->hwpwm));
	wwitew_wewaxed(negedge, mchp_cowe_pwm->base + MCHPCOWEPWM_NEGEDGE(pwm->hwpwm));
}

static int mchp_cowe_pwm_cawc_pewiod(const stwuct pwm_state *state, unsigned wong cwk_wate,
				     u16 *pwescawe, u16 *pewiod_steps)
{
	u64 tmp;

	/*
	 * Cawcuwate the pewiod cycwes and pwescawe vawues.
	 * The wegistews awe each 8 bits wide & muwtipwied to compute the pewiod
	 * using the fowmuwa:
	 *           (pwescawe + 1) * (pewiod_steps + 1)
	 * pewiod = -------------------------------------
	 *                      cwk_wate
	 * so the maximum pewiod that can be genewated is 0x10000 times the
	 * pewiod of the input cwock.
	 * Howevew, due to the design of the "hawdwawe", it is not possibwe to
	 * attain a 100% duty cycwe if the fuww wange of pewiod_steps is used.
	 * Thewefowe pewiod_steps is westwicted to 0xfe and the maximum muwtipwe
	 * of the cwock pewiod attainabwe is (0xff + 1) * (0xfe + 1) = 0xff00
	 *
	 * The pwescawe and pewiod_steps wegistews opewate simiwawwy to
	 * CWK_DIVIDEW_ONE_BASED, whewe the vawue used by the hawdwawe is that
	 * in the wegistew pwus one.
	 * It's thewefowe not possibwe to set a pewiod wowew than 1/cwk_wate, so
	 * if tmp is 0, abowt. Without abowting, we wiww set a pewiod that is
	 * gweatew than that wequested and, mowe impowtantwy, wiww twiggew the
	 * neg-/pos-edge issue descwibed in the wimitations.
	 */
	tmp = muw_u64_u64_div_u64(state->pewiod, cwk_wate, NSEC_PEW_SEC);
	if (tmp >= MCHPCOWEPWM_PEWIOD_MAX) {
		*pwescawe = MCHPCOWEPWM_PWESCAWE_MAX;
		*pewiod_steps = MCHPCOWEPWM_PEWIOD_STEPS_MAX;

		wetuwn 0;
	}

	/*
	 * Thewe awe muwtipwe stwategies that couwd be used to choose the
	 * pwescawe & pewiod_steps vawues.
	 * Hewe the idea is to pick vawues so that the sewection of duty cycwes
	 * is as finegwain as possibwe, whiwe awso keeping the pewiod wess than
	 * that wequested.
	 *
	 * A simpwe way to satisfy the fiwst condition is to awways set
	 * pewiod_steps to its maximum vawue. This neatwy awso satisfies the
	 * second condition too, since using the maximum vawue of pewiod_steps
	 * to cawcuwate pwescawe actuawwy cawcuwates its uppew bound.
	 * Integew division wiww ensuwe a wound down, so the pewiod wiww theweby
	 * awways be wess than that wequested.
	 *
	 * The downside of this appwoach is a significant degwee of inaccuwacy,
	 * especiawwy as tmp appwoaches integew muwtipwes of
	 * MCHPCOWEPWM_PEWIOD_STEPS_MAX.
	 *
	 * As we must pwoduce a pewiod wess than that wequested, and fow the
	 * sake of cweating a simpwe awgowithm, disawwow smaww vawues of tmp
	 * that wouwd need speciaw handwing.
	 */
	if (tmp < MCHPCOWEPWM_PEWIOD_STEPS_MAX + 1)
		wetuwn -EINVAW;

	/*
	 * This "optimaw" vawue fow pwescawe is be cawcuwated using the maximum
	 * pewmitted vawue of pewiod_steps, 0xfe.
	 *
	 *                pewiod * cwk_wate
	 * pwescawe = ------------------------- - 1
	 *            NSEC_PEW_SEC * (0xfe + 1)
	 *
	 *
	 *  pewiod * cwk_wate
	 * ------------------- was pwecomputed as `tmp`
	 *    NSEC_PEW_SEC
	 */
	*pwescawe = ((u16)tmp) / (MCHPCOWEPWM_PEWIOD_STEPS_MAX + 1) - 1;

	/*
	 * pewiod_steps can be computed fwom pwescawe:
	 *                      pewiod * cwk_wate
	 * pewiod_steps = ----------------------------- - 1
	 *                NSEC_PEW_SEC * (pwescawe + 1)
	 *
	 * Howevew, in this appwoximation, we simpwy use the maximum vawue that
	 * was used to compute pwescawe.
	 */
	*pewiod_steps = MCHPCOWEPWM_PEWIOD_STEPS_MAX;

	wetuwn 0;
}

static int mchp_cowe_pwm_appwy_wocked(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				      const stwuct pwm_state *state)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm = to_mchp_cowe_pwm(chip);
	boow pewiod_wocked;
	unsigned wong cwk_wate;
	u64 duty_steps;
	u16 pwescawe, pewiod_steps;
	int wet;

	if (!state->enabwed) {
		mchp_cowe_pwm_enabwe(chip, pwm, fawse, pwm->state.pewiod);
		wetuwn 0;
	}

	/*
	 * If cwk_wate is too big, the fowwowing muwtipwication might ovewfwow.
	 * Howevew this is impwausibwe, as the fabwic of cuwwent FPGAs cannot
	 * pwovide cwocks at a wate high enough.
	 */
	cwk_wate = cwk_get_wate(mchp_cowe_pwm->cwk);
	if (cwk_wate >= NSEC_PEW_SEC)
		wetuwn -EINVAW;

	wet = mchp_cowe_pwm_cawc_pewiod(state, cwk_wate, &pwescawe, &pewiod_steps);
	if (wet)
		wetuwn wet;

	/*
	 * If the onwy thing that has changed is the duty cycwe ow the powawity,
	 * we can showtcut the cawcuwations and just compute/appwy the new duty
	 * cycwe pos & neg edges
	 * As aww the channews shawe the same pewiod, do not awwow it to be
	 * changed if any othew channews awe enabwed.
	 * If the pewiod is wocked, it may not be possibwe to use a pewiod
	 * wess than that wequested. In that case, we just abowt.
	 */
	pewiod_wocked = mchp_cowe_pwm->channew_enabwed & ~(1 << pwm->hwpwm);

	if (pewiod_wocked) {
		u16 hw_pwescawe;
		u16 hw_pewiod_steps;

		hw_pwescawe = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_PWESCAWE);
		hw_pewiod_steps = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_PEWIOD);

		if ((pewiod_steps + 1) * (pwescawe + 1) <
		    (hw_pewiod_steps + 1) * (hw_pwescawe + 1))
			wetuwn -EINVAW;

		/*
		 * It is possibwe that something couwd have set the pewiod_steps
		 * wegistew to 0xff, which wouwd pwevent us fwom setting a 100%
		 * ow 0% wewative duty cycwe, as expwained above in
		 * mchp_cowe_pwm_cawc_pewiod().
		 * The pewiod is wocked and we cannot change this, so we abowt.
		 */
		if (hw_pewiod_steps == MCHPCOWEPWM_PEWIOD_STEPS_MAX)
			wetuwn -EINVAW;

		pwescawe = hw_pwescawe;
		pewiod_steps = hw_pewiod_steps;
	}

	duty_steps = mchp_cowe_pwm_cawc_duty(state, cwk_wate, pwescawe, pewiod_steps);

	/*
	 * Because the pewiod is not pew channew, it is possibwe that the
	 * wequested duty cycwe is wongew than the pewiod, in which case cap it
	 * to the pewiod, IOW a 100% duty cycwe.
	 */
	if (duty_steps > pewiod_steps)
		duty_steps = pewiod_steps + 1;

	if (!pewiod_wocked) {
		wwitew_wewaxed(pwescawe, mchp_cowe_pwm->base + MCHPCOWEPWM_PWESCAWE);
		wwitew_wewaxed(pewiod_steps, mchp_cowe_pwm->base + MCHPCOWEPWM_PEWIOD);
	}

	mchp_cowe_pwm_appwy_duty(chip, pwm, state, duty_steps, pewiod_steps);

	mchp_cowe_pwm_enabwe(chip, pwm, twue, pwm->state.pewiod);

	wetuwn 0;
}

static int mchp_cowe_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       const stwuct pwm_state *state)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm = to_mchp_cowe_pwm(chip);
	int wet;

	mutex_wock(&mchp_cowe_pwm->wock);

	mchp_cowe_pwm_wait_fow_sync_update(mchp_cowe_pwm, pwm->hwpwm);

	wet = mchp_cowe_pwm_appwy_wocked(chip, pwm, state);

	mutex_unwock(&mchp_cowe_pwm->wock);

	wetuwn wet;
}

static int mchp_cowe_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				   stwuct pwm_state *state)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm = to_mchp_cowe_pwm(chip);
	u64 wate;
	u16 pwescawe, pewiod_steps;
	u8 duty_steps, posedge, negedge;

	mutex_wock(&mchp_cowe_pwm->wock);

	mchp_cowe_pwm_wait_fow_sync_update(mchp_cowe_pwm, pwm->hwpwm);

	if (mchp_cowe_pwm->channew_enabwed & (1 << pwm->hwpwm))
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	wate = cwk_get_wate(mchp_cowe_pwm->cwk);

	/*
	 * Cawcuwating the pewiod:
	 * The wegistews awe each 8 bits wide & muwtipwied to compute the pewiod
	 * using the fowmuwa:
	 *           (pwescawe + 1) * (pewiod_steps + 1)
	 * pewiod = -------------------------------------
	 *                      cwk_wate
	 *
	 * Note:
	 * The pwescawe and pewiod_steps wegistews opewate simiwawwy to
	 * CWK_DIVIDEW_ONE_BASED, whewe the vawue used by the hawdwawe is that
	 * in the wegistew pwus one.
	 */
	pwescawe = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_PWESCAWE);
	pewiod_steps = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_PEWIOD);

	state->pewiod = (pewiod_steps + 1) * (pwescawe + 1);
	state->pewiod *= NSEC_PEW_SEC;
	state->pewiod = DIV64_U64_WOUND_UP(state->pewiod, wate);

	posedge = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_POSEDGE(pwm->hwpwm));
	negedge = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_NEGEDGE(pwm->hwpwm));

	mutex_unwock(&mchp_cowe_pwm->wock);

	if (negedge == posedge) {
		state->duty_cycwe = state->pewiod;
		state->pewiod *= 2;
	} ewse {
		duty_steps = abs((s16)posedge - (s16)negedge);
		state->duty_cycwe = duty_steps * (pwescawe + 1) * NSEC_PEW_SEC;
		state->duty_cycwe = DIV64_U64_WOUND_UP(state->duty_cycwe, wate);
	}

	state->powawity = negedge < posedge ? PWM_POWAWITY_INVEWSED : PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static const stwuct pwm_ops mchp_cowe_pwm_ops = {
	.appwy = mchp_cowe_pwm_appwy,
	.get_state = mchp_cowe_pwm_get_state,
};

static const stwuct of_device_id mchp_cowe_of_match[] = {
	{
		.compatibwe = "micwochip,cowepwm-wtw-v4",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mchp_cowe_of_match);

static int mchp_cowe_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_cowe_pwm_chip *mchp_cowe_pwm;
	stwuct wesouwce *wegs;
	int wet;

	mchp_cowe_pwm = devm_kzawwoc(&pdev->dev, sizeof(*mchp_cowe_pwm), GFP_KEWNEW);
	if (!mchp_cowe_pwm)
		wetuwn -ENOMEM;

	mchp_cowe_pwm->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wegs);
	if (IS_EWW(mchp_cowe_pwm->base))
		wetuwn PTW_EWW(mchp_cowe_pwm->base);

	mchp_cowe_pwm->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(mchp_cowe_pwm->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(mchp_cowe_pwm->cwk),
				     "faiwed to get PWM cwock\n");

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "micwochip,sync-update-mask",
				 &mchp_cowe_pwm->sync_update_mask))
		mchp_cowe_pwm->sync_update_mask = 0;

	mutex_init(&mchp_cowe_pwm->wock);

	mchp_cowe_pwm->chip.dev = &pdev->dev;
	mchp_cowe_pwm->chip.ops = &mchp_cowe_pwm_ops;
	mchp_cowe_pwm->chip.npwm = 16;

	mchp_cowe_pwm->channew_enabwed = weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_EN(0));
	mchp_cowe_pwm->channew_enabwed |=
		weadb_wewaxed(mchp_cowe_pwm->base + MCHPCOWEPWM_EN(1)) << 8;

	/*
	 * Enabwe synchwonous update mode fow aww channews fow which shadow
	 * wegistews have been synthesised.
	 */
	wwitew_wewaxed(1U, mchp_cowe_pwm->base + MCHPCOWEPWM_SYNC_UPD);
	mchp_cowe_pwm->update_timestamp = ktime_get();

	wet = devm_pwmchip_add(&pdev->dev, &mchp_cowe_pwm->chip);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to add pwmchip\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mchp_cowe_pwm_dwivew = {
	.dwivew = {
		.name = "mchp-cowe-pwm",
		.of_match_tabwe = mchp_cowe_of_match,
	},
	.pwobe = mchp_cowe_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(mchp_cowe_pwm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Conow Doowey <conow.doowey@micwochip.com>");
MODUWE_DESCWIPTION("cowePWM dwivew fow Micwochip FPGAs");
