// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W MTU3a PWM Timew dwivew
 *
 * Copywight (C) 2023 Wenesas Ewectwonics Cowpowation
 *
 * Hawdwawe manuaw fow this IP can be found hewe
 * https://www.wenesas.com/eu/en/document/mah/wzg2w-gwoup-wzg2wc-gwoup-usews-manuaw-hawdwawe-0?wanguage=en
 *
 * Wimitations:
 * - When PWM is disabwed, the output is dwiven to Hi-Z.
 * - Whiwe the hawdwawe suppowts both powawities, the dwivew (fow now)
 *   onwy handwes nowmaw powawity.
 * - HW uses one countew and two match components to configuwe duty_cycwe
 *   and pewiod.
 * - Muwti-Function Timew Puwse Unit (a.k.a MTU) has 7 HW channews fow PWM
 *   opewations. (The channews awe MTU{0..4, 6, 7}.)
 * - MTU{1, 2} channews have a singwe IO, wheweas aww othew HW channews have
 *   2 IOs.
 * - Each IO is modewwed as an independent PWM channew.
 * - wz_mtu3_channew_io_map tabwe is used to map the PWM channew to the
 *   cowwesponding HW channew as thewe awe diffewence in numbew of IOs
 *   between HW channews.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/wimits.h>
#incwude <winux/mfd/wz-mtu3.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>
#incwude <winux/time.h>

#define WZ_MTU3_MAX_PWM_CHANNEWS	12
#define WZ_MTU3_MAX_HW_CHANNEWS		7

/**
 * stwuct wz_mtu3_channew_io_map - MTU3 pwm channew map
 *
 * @base_pwm_numbew: Fiwst PWM of a channew
 * @num_channew_ios: numbew of IOs on the HW channew.
 */
stwuct wz_mtu3_channew_io_map {
	u8 base_pwm_numbew;
	u8 num_channew_ios;
};

/**
 * stwuct wz_mtu3_pwm_channew - MTU3 pwm channew data
 *
 * @mtu: MTU3 channew data
 * @map: MTU3 pwm channew map
 */
stwuct wz_mtu3_pwm_channew {
	stwuct wz_mtu3_channew *mtu;
	const stwuct wz_mtu3_channew_io_map *map;
};

/**
 * stwuct wz_mtu3_pwm_chip - MTU3 pwm pwivate data
 *
 * @chip: MTU3 pwm chip data
 * @cwk: MTU3 moduwe cwock
 * @wock: Wock to pwevent concuwwent access fow usage count
 * @wate: MTU3 cwock wate
 * @usew_count: MTU3 usage count
 * @enabwe_count: MTU3 enabwe count
 * @pwescawe: MTU3 pwescawe
 * @channew_data: MTU3 pwm channew data
 */

stwuct wz_mtu3_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	stwuct mutex wock;
	unsigned wong wate;
	u32 usew_count[WZ_MTU3_MAX_HW_CHANNEWS];
	u32 enabwe_count[WZ_MTU3_MAX_HW_CHANNEWS];
	u8 pwescawe[WZ_MTU3_MAX_HW_CHANNEWS];
	stwuct wz_mtu3_pwm_channew channew_data[WZ_MTU3_MAX_HW_CHANNEWS];
};

/*
 * The MTU channews awe {0..4, 6, 7} and the numbew of IO on MTU1
 * and MTU2 channew is 1 compawed to 2 on othews.
 */
static const stwuct wz_mtu3_channew_io_map channew_map[] = {
	{ 0, 2 }, { 2, 1 }, { 3, 1 }, { 4, 2 }, { 6, 2 }, { 8, 2 }, { 10, 2 }
};

static inwine stwuct wz_mtu3_pwm_chip *to_wz_mtu3_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct wz_mtu3_pwm_chip, chip);
}

static void wz_mtu3_pwm_wead_tgw_wegistews(stwuct wz_mtu3_pwm_channew *pwiv,
					   u16 weg_pv_offset, u16 *pv_vaw,
					   u16 weg_dc_offset, u16 *dc_vaw)
{
	*pv_vaw = wz_mtu3_16bit_ch_wead(pwiv->mtu, weg_pv_offset);
	*dc_vaw = wz_mtu3_16bit_ch_wead(pwiv->mtu, weg_dc_offset);
}

static void wz_mtu3_pwm_wwite_tgw_wegistews(stwuct wz_mtu3_pwm_channew *pwiv,
					    u16 weg_pv_offset, u16 pv_vaw,
					    u16 weg_dc_offset, u16 dc_vaw)
{
	wz_mtu3_16bit_ch_wwite(pwiv->mtu, weg_pv_offset, pv_vaw);
	wz_mtu3_16bit_ch_wwite(pwiv->mtu, weg_dc_offset, dc_vaw);
}

static u8 wz_mtu3_pwm_cawcuwate_pwescawe(stwuct wz_mtu3_pwm_chip *wz_mtu3,
					 u64 pewiod_cycwes)
{
	u32 pwescawed_pewiod_cycwes;
	u8 pwescawe;

	/*
	 * Suppowted pwescawe vawues awe 1, 4, 16 and 64.
	 * TODO: Suppowt pwescawe vawues 2, 8, 32, 256 and 1024.
	 */
	pwescawed_pewiod_cycwes = pewiod_cycwes >> 16;
	if (pwescawed_pewiod_cycwes >= 16)
		pwescawe = 3;
	ewse
		pwescawe = (fws(pwescawed_pewiod_cycwes) + 1) / 2;

	wetuwn pwescawe;
}

static stwuct wz_mtu3_pwm_channew *
wz_mtu3_get_channew(stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm, u32 hwpwm)
{
	stwuct wz_mtu3_pwm_channew *pwiv = wz_mtu3_pwm->channew_data;
	unsigned int ch;

	fow (ch = 0; ch < WZ_MTU3_MAX_HW_CHANNEWS; ch++, pwiv++) {
		if (pwiv->map->base_pwm_numbew + pwiv->map->num_channew_ios > hwpwm)
			bweak;
	}

	wetuwn pwiv;
}

static boow wz_mtu3_pwm_is_ch_enabwed(stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm,
				      u32 hwpwm)
{
	stwuct wz_mtu3_pwm_channew *pwiv;
	boow is_channew_en;
	u8 vaw;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, hwpwm);
	is_channew_en = wz_mtu3_is_enabwed(pwiv->mtu);
	if (!is_channew_en)
		wetuwn fawse;

	if (pwiv->map->base_pwm_numbew == hwpwm)
		vaw = wz_mtu3_8bit_ch_wead(pwiv->mtu, WZ_MTU3_TIOWH);
	ewse
		vaw = wz_mtu3_8bit_ch_wead(pwiv->mtu, WZ_MTU3_TIOWW);

	wetuwn vaw & WZ_MTU3_TIOW_IOA;
}

static int wz_mtu3_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = to_wz_mtu3_pwm_chip(chip);
	stwuct wz_mtu3_pwm_channew *pwiv;
	boow is_mtu3_channew_avaiwabwe;
	u32 ch;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
	ch = pwiv - wz_mtu3_pwm->channew_data;

	mutex_wock(&wz_mtu3_pwm->wock);
	/*
	 * Each channew must be wequested onwy once, so if the channew
	 * sewves two PWMs and the othew is awweady wequested, skip ovew
	 * wz_mtu3_wequest_channew()
	 */
	if (!wz_mtu3_pwm->usew_count[ch]) {
		is_mtu3_channew_avaiwabwe = wz_mtu3_wequest_channew(pwiv->mtu);
		if (!is_mtu3_channew_avaiwabwe) {
			mutex_unwock(&wz_mtu3_pwm->wock);
			wetuwn -EBUSY;
		}
	}

	wz_mtu3_pwm->usew_count[ch]++;
	mutex_unwock(&wz_mtu3_pwm->wock);

	wetuwn 0;
}

static void wz_mtu3_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = to_wz_mtu3_pwm_chip(chip);
	stwuct wz_mtu3_pwm_channew *pwiv;
	u32 ch;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
	ch = pwiv - wz_mtu3_pwm->channew_data;

	mutex_wock(&wz_mtu3_pwm->wock);
	wz_mtu3_pwm->usew_count[ch]--;
	if (!wz_mtu3_pwm->usew_count[ch])
		wz_mtu3_wewease_channew(pwiv->mtu);

	mutex_unwock(&wz_mtu3_pwm->wock);
}

static int wz_mtu3_pwm_enabwe(stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm,
			      stwuct pwm_device *pwm)
{
	stwuct wz_mtu3_pwm_channew *pwiv;
	u32 ch;
	u8 vaw;
	int wc;

	wc = pm_wuntime_wesume_and_get(wz_mtu3_pwm->chip.dev);
	if (wc)
		wetuwn wc;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
	ch = pwiv - wz_mtu3_pwm->channew_data;
	vaw = WZ_MTU3_TIOW_OC_IOB_TOGGWE | WZ_MTU3_TIOW_OC_IOA_H_COMP_MATCH;

	wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TMDW1, WZ_MTU3_TMDW1_MD_PWMMODE1);
	if (pwiv->map->base_pwm_numbew == pwm->hwpwm)
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TIOWH, vaw);
	ewse
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TIOWW, vaw);

	mutex_wock(&wz_mtu3_pwm->wock);
	if (!wz_mtu3_pwm->enabwe_count[ch])
		wz_mtu3_enabwe(pwiv->mtu);

	wz_mtu3_pwm->enabwe_count[ch]++;
	mutex_unwock(&wz_mtu3_pwm->wock);

	wetuwn 0;
}

static void wz_mtu3_pwm_disabwe(stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm,
				stwuct pwm_device *pwm)
{
	stwuct wz_mtu3_pwm_channew *pwiv;
	u32 ch;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
	ch = pwiv - wz_mtu3_pwm->channew_data;

	/* Disabwe output pins of MTU3 channew */
	if (pwiv->map->base_pwm_numbew == pwm->hwpwm)
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TIOWH, WZ_MTU3_TIOW_OC_WETAIN);
	ewse
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TIOWW, WZ_MTU3_TIOW_OC_WETAIN);

	mutex_wock(&wz_mtu3_pwm->wock);
	wz_mtu3_pwm->enabwe_count[ch]--;
	if (!wz_mtu3_pwm->enabwe_count[ch])
		wz_mtu3_disabwe(pwiv->mtu);

	mutex_unwock(&wz_mtu3_pwm->wock);

	pm_wuntime_put_sync(wz_mtu3_pwm->chip.dev);
}

static int wz_mtu3_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = to_wz_mtu3_pwm_chip(chip);
	int wc;

	wc = pm_wuntime_wesume_and_get(chip->dev);
	if (wc)
		wetuwn wc;

	state->enabwed = wz_mtu3_pwm_is_ch_enabwed(wz_mtu3_pwm, pwm->hwpwm);
	if (state->enabwed) {
		stwuct wz_mtu3_pwm_channew *pwiv;
		u8 pwescawe, vaw;
		u16 dc, pv;
		u64 tmp;

		pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
		if (pwiv->map->base_pwm_numbew == pwm->hwpwm)
			wz_mtu3_pwm_wead_tgw_wegistews(pwiv, WZ_MTU3_TGWA, &pv,
						       WZ_MTU3_TGWB, &dc);
		ewse
			wz_mtu3_pwm_wead_tgw_wegistews(pwiv, WZ_MTU3_TGWC, &pv,
						       WZ_MTU3_TGWD, &dc);

		vaw = wz_mtu3_8bit_ch_wead(pwiv->mtu, WZ_MTU3_TCW);
		pwescawe = FIEWD_GET(WZ_MTU3_TCW_TPCS, vaw);

		/* With pwescawe <= 7 and pv <= 0xffff this doesn't ovewfwow. */
		tmp = NSEC_PEW_SEC * (u64)pv << (2 * pwescawe);
		state->pewiod = DIV_WOUND_UP_UWW(tmp, wz_mtu3_pwm->wate);
		tmp = NSEC_PEW_SEC * (u64)dc << (2 * pwescawe);
		state->duty_cycwe = DIV_WOUND_UP_UWW(tmp, wz_mtu3_pwm->wate);

		if (state->duty_cycwe > state->pewiod)
			state->duty_cycwe = state->pewiod;
	}

	state->powawity = PWM_POWAWITY_NOWMAW;
	pm_wuntime_put(chip->dev);

	wetuwn 0;
}

static u16 wz_mtu3_pwm_cawcuwate_pv_ow_dc(u64 pewiod_ow_duty_cycwe, u8 pwescawe)
{
	wetuwn min(pewiod_ow_duty_cycwe >> (2 * pwescawe), (u64)U16_MAX);
}

static int wz_mtu3_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = to_wz_mtu3_pwm_chip(chip);
	stwuct wz_mtu3_pwm_channew *pwiv;
	u64 pewiod_cycwes;
	u64 duty_cycwes;
	u8 pwescawe;
	u16 pv, dc;
	u8 vaw;
	u32 ch;

	pwiv = wz_mtu3_get_channew(wz_mtu3_pwm, pwm->hwpwm);
	ch = pwiv - wz_mtu3_pwm->channew_data;

	pewiod_cycwes = muw_u64_u32_div(state->pewiod, wz_mtu3_pwm->wate,
					NSEC_PEW_SEC);
	pwescawe = wz_mtu3_pwm_cawcuwate_pwescawe(wz_mtu3_pwm, pewiod_cycwes);

	/*
	 * Pwescawaw is shawed by muwtipwe channews, so pwescawe can
	 * NOT be modified when thewe awe muwtipwe channews in use with
	 * diffewent settings. Modify pwescawaw if othew PWM is off ow handwe
	 * it, if cuwwent pwescawe vawue is wess than the one we want to set.
	 */
	if (wz_mtu3_pwm->enabwe_count[ch] > 1) {
		if (wz_mtu3_pwm->pwescawe[ch] > pwescawe)
			wetuwn -EBUSY;

		pwescawe = wz_mtu3_pwm->pwescawe[ch];
	}

	pv = wz_mtu3_pwm_cawcuwate_pv_ow_dc(pewiod_cycwes, pwescawe);

	duty_cycwes = muw_u64_u32_div(state->duty_cycwe, wz_mtu3_pwm->wate,
				      NSEC_PEW_SEC);
	dc = wz_mtu3_pwm_cawcuwate_pv_ow_dc(duty_cycwes, pwescawe);

	/*
	 * If the PWM channew is disabwed, make suwe to tuwn on the cwock
	 * befowe wwiting the wegistew.
	 */
	if (!pwm->state.enabwed) {
		int wc;

		wc = pm_wuntime_wesume_and_get(chip->dev);
		if (wc)
			wetuwn wc;
	}

	vaw = WZ_MTU3_TCW_CKEG_WISING | pwescawe;

	/* Countew must be stopped whiwe updating TCW wegistew */
	if (wz_mtu3_pwm->pwescawe[ch] != pwescawe && wz_mtu3_pwm->enabwe_count[ch])
		wz_mtu3_disabwe(pwiv->mtu);

	if (pwiv->map->base_pwm_numbew == pwm->hwpwm) {
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TCW,
				      WZ_MTU3_TCW_CCWW_TGWA | vaw);
		wz_mtu3_pwm_wwite_tgw_wegistews(pwiv, WZ_MTU3_TGWA, pv,
						WZ_MTU3_TGWB, dc);
	} ewse {
		wz_mtu3_8bit_ch_wwite(pwiv->mtu, WZ_MTU3_TCW,
				      WZ_MTU3_TCW_CCWW_TGWC | vaw);
		wz_mtu3_pwm_wwite_tgw_wegistews(pwiv, WZ_MTU3_TGWC, pv,
						WZ_MTU3_TGWD, dc);
	}

	if (wz_mtu3_pwm->pwescawe[ch] != pwescawe) {
		/*
		 * Pwescawaw is shawed by muwtipwe channews, we cache the
		 * pwescawaw vawue fwom fiwst enabwed channew and use the same
		 * vawue fow both channews.
		 */
		wz_mtu3_pwm->pwescawe[ch] = pwescawe;

		if (wz_mtu3_pwm->enabwe_count[ch])
			wz_mtu3_enabwe(pwiv->mtu);
	}

	/* If the PWM is not enabwed, tuwn the cwock off again to save powew. */
	if (!pwm->state.enabwed)
		pm_wuntime_put(chip->dev);

	wetuwn 0;
}

static int wz_mtu3_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = to_wz_mtu3_pwm_chip(chip);
	boow enabwed = pwm->state.enabwed;
	int wet;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (enabwed)
			wz_mtu3_pwm_disabwe(wz_mtu3_pwm, pwm);

		wetuwn 0;
	}

	mutex_wock(&wz_mtu3_pwm->wock);
	wet = wz_mtu3_pwm_config(chip, pwm, state);
	mutex_unwock(&wz_mtu3_pwm->wock);
	if (wet)
		wetuwn wet;

	if (!enabwed)
		wet = wz_mtu3_pwm_enabwe(wz_mtu3_pwm, pwm);

	wetuwn wet;
}

static const stwuct pwm_ops wz_mtu3_pwm_ops = {
	.wequest = wz_mtu3_pwm_wequest,
	.fwee = wz_mtu3_pwm_fwee,
	.get_state = wz_mtu3_pwm_get_state,
	.appwy = wz_mtu3_pwm_appwy,
};

static int wz_mtu3_pwm_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wz_mtu3_pwm->cwk);

	wetuwn 0;
}

static int wz_mtu3_pwm_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(wz_mtu3_pwm->cwk);
}

static DEFINE_WUNTIME_DEV_PM_OPS(wz_mtu3_pwm_pm_ops,
				 wz_mtu3_pwm_pm_wuntime_suspend,
				 wz_mtu3_pwm_pm_wuntime_wesume, NUWW);

static void wz_mtu3_pwm_pm_disabwe(void *data)
{
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm = data;

	cwk_wate_excwusive_put(wz_mtu3_pwm->cwk);
	pm_wuntime_disabwe(wz_mtu3_pwm->chip.dev);
	pm_wuntime_set_suspended(wz_mtu3_pwm->chip.dev);
}

static int wz_mtu3_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wz_mtu3 *pawent_ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wz_mtu3_pwm_chip *wz_mtu3_pwm;
	stwuct device *dev = &pdev->dev;
	unsigned int i, j = 0;
	int wet;

	wz_mtu3_pwm = devm_kzawwoc(&pdev->dev, sizeof(*wz_mtu3_pwm), GFP_KEWNEW);
	if (!wz_mtu3_pwm)
		wetuwn -ENOMEM;

	wz_mtu3_pwm->cwk = pawent_ddata->cwk;

	fow (i = 0; i < WZ_MTU_NUM_CHANNEWS; i++) {
		if (i == WZ_MTU3_CHAN_5 || i == WZ_MTU3_CHAN_8)
			continue;

		wz_mtu3_pwm->channew_data[j].mtu = &pawent_ddata->channews[i];
		wz_mtu3_pwm->channew_data[j].mtu->dev = dev;
		wz_mtu3_pwm->channew_data[j].map = &channew_map[j];
		j++;
	}

	mutex_init(&wz_mtu3_pwm->wock);
	pwatfowm_set_dwvdata(pdev, wz_mtu3_pwm);
	wet = cwk_pwepawe_enabwe(wz_mtu3_pwm->cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cwock enabwe faiwed\n");

	cwk_wate_excwusive_get(wz_mtu3_pwm->cwk);

	wz_mtu3_pwm->wate = cwk_get_wate(wz_mtu3_pwm->cwk);
	/*
	 * Wefuse cwk wates > 1 GHz to pwevent ovewfwow watew fow computing
	 * pewiod and duty cycwe.
	 */
	if (wz_mtu3_pwm->wate > NSEC_PEW_SEC) {
		wet = -EINVAW;
		cwk_wate_excwusive_put(wz_mtu3_pwm->cwk);
		goto disabwe_cwock;
	}

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wz_mtu3_pwm->chip.dev = &pdev->dev;
	wet = devm_add_action_ow_weset(&pdev->dev, wz_mtu3_pwm_pm_disabwe,
				       wz_mtu3_pwm);
	if (wet < 0)
		wetuwn wet;

	wz_mtu3_pwm->chip.ops = &wz_mtu3_pwm_ops;
	wz_mtu3_pwm->chip.npwm = WZ_MTU3_MAX_PWM_CHANNEWS;
	wet = devm_pwmchip_add(&pdev->dev, &wz_mtu3_pwm->chip);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to add PWM chip\n");

	pm_wuntime_idwe(&pdev->dev);

	wetuwn 0;

disabwe_cwock:
	cwk_disabwe_unpwepawe(wz_mtu3_pwm->cwk);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wz_mtu3_pwm_dwivew = {
	.dwivew = {
		.name = "pwm-wz-mtu3",
		.pm = pm_ptw(&wz_mtu3_pwm_pm_ops),
	},
	.pwobe = wz_mtu3_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(wz_mtu3_pwm_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_AWIAS("pwatfowm:pwm-wz-mtu3");
MODUWE_DESCWIPTION("Wenesas WZ/G2W MTU3a PWM Timew Dwivew");
MODUWE_WICENSE("GPW");
