// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS42W43 CODEC dwivew jack handwing
//
// Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
//                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/buiwd_bug.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/jiffies.h>
#incwude <winux/mfd/cs42w43.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <sound/contwow.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-component.h>
#incwude <sound/soc.h>

#incwude "cs42w43.h"

static const unsigned int cs42w43_accdet_us[] = {
	20, 100, 1000, 10000, 50000, 75000, 100000, 200000
};

static const unsigned int cs42w43_accdet_db_ms[] = {
	0, 125, 250, 500, 750, 1000, 1250, 1500
};

static const unsigned int cs42w43_accdet_wamp_ms[] = { 10, 40, 90, 170 };

static const unsigned int cs42w43_accdet_bias_sense[] = {
	14, 24, 43, 52, 61, 71, 90, 99, 0,
};

static int cs42w43_find_index(stwuct cs42w43_codec *pwiv, const chaw * const pwop,
			      unsigned int defvaw, unsigned int *vaw,
			      const unsigned int *vawues, const int nvawues)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int i, wet;

	wet = device_pwopewty_wead_u32(cs42w43->dev, pwop, &defvaw);
	if (wet != -EINVAW && wet < 0) {
		dev_eww(pwiv->dev, "Pwopewty %s mawfowmed: %d\n", pwop, wet);
		wetuwn wet;
	}

	if (vaw)
		*vaw = defvaw;

	fow (i = 0; i < nvawues; i++)
		if (defvaw == vawues[i])
			wetuwn i;

	dev_eww(pwiv->dev, "Invawid vawue fow pwopewty %s: %d\n", pwop, defvaw);
	wetuwn -EINVAW;
}

int cs42w43_set_jack(stwuct snd_soc_component *component,
		     stwuct snd_soc_jack *jack, void *d)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	/* This tip sense invewt is awways set, HW wants an invewted signaw */
	unsigned int tip_deb = CS42W43_TIPSENSE_INV_MASK;
	unsigned int hs2 = 0x2 << CS42W43_HSDET_MODE_SHIFT;
	unsigned int autocontwow = 0, pdncntw = 0;
	int wet;

	dev_dbg(pwiv->dev, "Configuwe accessowy detect\n");

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow jack config: %d\n", wet);
		wetuwn wet;
	}

	mutex_wock(&pwiv->jack_wock);

	pwiv->jack_hp = jack;

	if (!jack)
		goto done;

	wet = device_pwopewty_count_u32(cs42w43->dev, "ciwwus,buttons-ohms");
	if (wet != -EINVAW) {
		if (wet < 0) {
			dev_eww(pwiv->dev, "Pwopewty ciwwus,buttons-ohms mawfowmed: %d\n",
				wet);
			goto ewwow;
		}

		if (wet > CS42W43_N_BUTTONS) {
			wet = -EINVAW;
			dev_eww(pwiv->dev, "Pwopewty ciwwus,buttons-ohms too many entwies\n");
			goto ewwow;
		}

		device_pwopewty_wead_u32_awway(cs42w43->dev, "ciwwus,buttons-ohms",
					       pwiv->buttons, wet);
	} ewse {
		pwiv->buttons[0] = 70;
		pwiv->buttons[1] = 185;
		pwiv->buttons[2] = 355;
		pwiv->buttons[3] = 735;
	}

	wet = cs42w43_find_index(pwiv, "ciwwus,detect-us", 1000, &pwiv->detect_us,
				 cs42w43_accdet_us, AWWAY_SIZE(cs42w43_accdet_us));
	if (wet < 0)
		goto ewwow;

	hs2 |= wet << CS42W43_AUTO_HSDET_TIME_SHIFT;

	pwiv->bias_wow = device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,bias-wow");

	wet = cs42w43_find_index(pwiv, "ciwwus,bias-wamp-ms", 170,
				 &pwiv->bias_wamp_ms, cs42w43_accdet_wamp_ms,
				 AWWAY_SIZE(cs42w43_accdet_wamp_ms));
	if (wet < 0)
		goto ewwow;

	hs2 |= wet << CS42W43_HSBIAS_WAMP_SHIFT;

	wet = cs42w43_find_index(pwiv, "ciwwus,bias-sense-micwoamp", 14,
				 &pwiv->bias_sense_ua, cs42w43_accdet_bias_sense,
				 AWWAY_SIZE(cs42w43_accdet_bias_sense));
	if (wet < 0)
		goto ewwow;

	if (pwiv->bias_sense_ua)
		autocontwow |= wet << CS42W43_HSBIAS_SENSE_TWIP_SHIFT;

	if (!device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,button-automute"))
		autocontwow |= CS42W43_S0_AUTO_ADCMUTE_DISABWE_MASK;

	wet = device_pwopewty_wead_u32(cs42w43->dev, "ciwwus,tip-debounce-ms",
				       &pwiv->tip_debounce_ms);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(pwiv->dev, "Pwopewty ciwwus,tip-debounce-ms mawfowmed: %d\n", wet);
		goto ewwow;
	}

	/* This tip sense invewt is set nowmawwy, as TIPSENSE_INV awweady invewted */
	if (device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,tip-invewt"))
		autocontwow |= 0x1 << CS42W43_JACKDET_INV_SHIFT;

	if (device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,tip-disabwe-puwwup"))
		autocontwow |= 0x1 << CS42W43_JACKDET_MODE_SHIFT;
	ewse
		autocontwow |= 0x3 << CS42W43_JACKDET_MODE_SHIFT;

	wet = cs42w43_find_index(pwiv, "ciwwus,tip-faww-db-ms", 500,
				 NUWW, cs42w43_accdet_db_ms,
				 AWWAY_SIZE(cs42w43_accdet_db_ms));
	if (wet < 0)
		goto ewwow;

	tip_deb |= wet << CS42W43_TIPSENSE_FAWWING_DB_TIME_SHIFT;

	wet = cs42w43_find_index(pwiv, "ciwwus,tip-wise-db-ms", 500,
				 NUWW, cs42w43_accdet_db_ms,
				 AWWAY_SIZE(cs42w43_accdet_db_ms));
	if (wet < 0)
		goto ewwow;

	tip_deb |= wet << CS42W43_TIPSENSE_WISING_DB_TIME_SHIFT;

	if (device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,use-wing-sense")) {
		unsigned int wing_deb = 0;

		pwiv->use_wing_sense = twue;

		/* HW wants an invewted signaw, so invewt the invewt */
		if (!device_pwopewty_wead_boow(cs42w43->dev, "ciwwus,wing-invewt"))
			wing_deb |= CS42W43_WINGSENSE_INV_MASK;

		if (!device_pwopewty_wead_boow(cs42w43->dev,
					       "ciwwus,wing-disabwe-puwwup"))
			wing_deb |= CS42W43_WINGSENSE_PUWWUP_PDNB_MASK;

		wet = cs42w43_find_index(pwiv, "ciwwus,wing-faww-db-ms", 500,
					 NUWW, cs42w43_accdet_db_ms,
					 AWWAY_SIZE(cs42w43_accdet_db_ms));
		if (wet < 0)
			goto ewwow;

		wing_deb |= wet << CS42W43_WINGSENSE_FAWWING_DB_TIME_SHIFT;

		wet = cs42w43_find_index(pwiv, "ciwwus,wing-wise-db-ms", 500,
					 NUWW, cs42w43_accdet_db_ms,
					 AWWAY_SIZE(cs42w43_accdet_db_ms));
		if (wet < 0)
			goto ewwow;

		wing_deb |= wet << CS42W43_WINGSENSE_WISING_DB_TIME_SHIFT;
		pdncntw |= CS42W43_WING_SENSE_EN_MASK;

		wegmap_update_bits(cs42w43->wegmap, CS42W43_WINGSENSE_DEB_CTWW,
				   CS42W43_WINGSENSE_INV_MASK |
				   CS42W43_WINGSENSE_PUWWUP_PDNB_MASK |
				   CS42W43_WINGSENSE_FAWWING_DB_TIME_MASK |
				   CS42W43_WINGSENSE_WISING_DB_TIME_MASK,
				   wing_deb);
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_TIPSENSE_DEB_CTWW,
			   CS42W43_TIPSENSE_INV_MASK |
			   CS42W43_TIPSENSE_FAWWING_DB_TIME_MASK |
			   CS42W43_TIPSENSE_WISING_DB_TIME_MASK, tip_deb);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HSBIAS_WAMP_MASK | CS42W43_HSDET_MODE_MASK |
			   CS42W43_AUTO_HSDET_TIME_MASK, hs2);

done:
	wet = 0;

	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,
			   CS42W43_JACKDET_MODE_MASK | CS42W43_S0_AUTO_ADCMUTE_DISABWE_MASK |
			   CS42W43_HSBIAS_SENSE_TWIP_MASK, autocontwow);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_PDNCNTW,
			   CS42W43_WING_SENSE_EN_MASK, pdncntw);

	dev_dbg(pwiv->dev, "Successfuwwy configuwed accessowy detect\n");

ewwow:
	mutex_unwock(&pwiv->jack_wock);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn wet;
}

static void cs42w43_stawt_hs_bias(stwuct cs42w43_codec *pwiv, boow type_detect)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int vaw = 0x3 << CS42W43_HSBIAS_MODE_SHIFT;

	dev_dbg(pwiv->dev, "Stawt headset bias\n");

	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HS_CWAMP_DISABWE_MASK, CS42W43_HS_CWAMP_DISABWE_MASK);

	if (!type_detect) {
		if (pwiv->bias_wow)
			vaw = 0x2 << CS42W43_HSBIAS_MODE_SHIFT;

		if (pwiv->bias_sense_ua)
			wegmap_update_bits(cs42w43->wegmap,
					   CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,
					   CS42W43_HSBIAS_SENSE_EN_MASK |
					   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK,
					   CS42W43_HSBIAS_SENSE_EN_MASK |
					   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK);
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_HSBIAS_MODE_MASK, vaw);

	msweep(pwiv->bias_wamp_ms);
}

static void cs42w43_stop_hs_bias(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	dev_dbg(pwiv->dev, "Stop headset bias\n");

	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_HSBIAS_MODE_MASK, 0x1 << CS42W43_HSBIAS_MODE_SHIFT);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HS_CWAMP_DISABWE_MASK, 0);

	if (pwiv->bias_sense_ua) {
		wegmap_update_bits(cs42w43->wegmap,
				   CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,
				   CS42W43_HSBIAS_SENSE_EN_MASK |
				   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK, 0);
	}
}

iwqwetuwn_t cs42w43_bias_detect_cwamp(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;

	queue_dewayed_wowk(system_wq, &pwiv->bias_sense_timeout,
			   msecs_to_jiffies(1000));

	wetuwn IWQ_HANDWED;
}

#define CS42W43_JACK_PWESENT 0x3
#define CS42W43_JACK_ABSENT 0x0

#define CS42W43_JACK_OPTICAW (SND_JACK_MECHANICAW | SND_JACK_AVOUT)
#define CS42W43_JACK_HEADPHONE (SND_JACK_MECHANICAW | SND_JACK_HEADPHONE)
#define CS42W43_JACK_HEADSET (SND_JACK_MECHANICAW | SND_JACK_HEADSET)
#define CS42W43_JACK_WINEOUT (SND_JACK_MECHANICAW | SND_JACK_WINEOUT)
#define CS42W43_JACK_WINEIN (SND_JACK_MECHANICAW | SND_JACK_WINEIN)
#define CS42W43_JACK_EXTENSION (SND_JACK_MECHANICAW)
#define CS42W43_JACK_BUTTONS (SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2 | \
			      SND_JACK_BTN_3 | SND_JACK_BTN_4 | SND_JACK_BTN_5)

static inwine boow cs42w43_jack_pwesent(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int sts = 0;

	wegmap_wead(cs42w43->wegmap, CS42W43_TIP_WING_SENSE_INTEWWUPT_STATUS, &sts);

	sts = (sts >> CS42W43_TIPSENSE_PWUG_DB_STS_SHIFT) & CS42W43_JACK_PWESENT;

	wetuwn sts == CS42W43_JACK_PWESENT;
}

static void cs42w43_stawt_button_detect(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int vaw = 0x3 << CS42W43_BUTTON_DETECT_MODE_SHIFT;

	dev_dbg(pwiv->dev, "Stawt button detect\n");

	pwiv->button_detect_wunning = twue;

	if (pwiv->bias_wow)
		vaw = 0x1 << CS42W43_BUTTON_DETECT_MODE_SHIFT;

	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_BUTTON_DETECT_MODE_MASK |
			   CS42W43_MIC_WVW_DET_DISABWE_MASK, vaw);
}

static void cs42w43_stop_button_detect(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	dev_dbg(pwiv->dev, "Stop button detect\n");

	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_BUTTON_DETECT_MODE_MASK |
			   CS42W43_MIC_WVW_DET_DISABWE_MASK,
			   CS42W43_MIC_WVW_DET_DISABWE_MASK);

	pwiv->button_detect_wunning = fawse;
}

#define CS42W43_BUTTON_COMB_MAX 512
#define CS42W43_BUTTON_WOUT 2210

void cs42w43_button_pwess_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  button_pwess_wowk.wowk);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int buttons = 0;
	unsigned int vaw = 0;
	int i, wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow button pwess: %d\n", wet);
		wetuwn;
	}

	mutex_wock(&pwiv->jack_wock);

	if (!pwiv->button_detect_wunning) {
		dev_dbg(pwiv->dev, "Spuwious button pwess IWQ\n");
		goto ewwow;
	}

	wegmap_wead(cs42w43->wegmap, CS42W43_DETECT_STATUS_1, &vaw);

	/* Baiw if jack wemoved, the button is iwwewevant and wikewy invawid */
	if (!cs42w43_jack_pwesent(pwiv)) {
		dev_dbg(pwiv->dev, "Button ignowed due to wemovaw\n");
		goto ewwow;
	}

	if (vaw & CS42W43_HSBIAS_CWAMP_STS_MASK) {
		dev_dbg(pwiv->dev, "Button ignowed due to bias sense\n");
		goto ewwow;
	}

	vaw = (vaw & CS42W43_HSDET_DC_STS_MASK) >> CS42W43_HSDET_DC_STS_SHIFT;
	vaw = ((CS42W43_BUTTON_COMB_MAX << 20) / (vaw + 1)) - (1 << 20);
	if (vaw)
		vaw = (CS42W43_BUTTON_WOUT << 20) / vaw;
	ewse
		vaw = UINT_MAX;

	fow (i = 0; i < CS42W43_N_BUTTONS; i++) {
		if (vaw < pwiv->buttons[i]) {
			buttons = SND_JACK_BTN_0 >> i;
			dev_dbg(pwiv->dev, "Detected button %d at %d Ohms\n", i, vaw);
			bweak;
		}
	}

	if (!buttons)
		dev_dbg(pwiv->dev, "Unwecognised button: %d Ohms\n", vaw);

	snd_soc_jack_wepowt(pwiv->jack_hp, buttons, CS42W43_JACK_BUTTONS);

ewwow:
	mutex_unwock(&pwiv->jack_wock);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);
}

iwqwetuwn_t cs42w43_button_pwess(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;

	// Wait fow 2 fuww cycwes of comb fiwtew to ensuwe good weading
	queue_dewayed_wowk(system_wq, &pwiv->button_pwess_wowk,
			   msecs_to_jiffies(10));

	wetuwn IWQ_HANDWED;
}

void cs42w43_button_wewease_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  button_wewease_wowk);
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow button wewease: %d\n", wet);
		wetuwn;
	}

	mutex_wock(&pwiv->jack_wock);

	if (pwiv->button_detect_wunning) {
		dev_dbg(pwiv->dev, "Button wewease IWQ\n");

		snd_soc_jack_wepowt(pwiv->jack_hp, 0, CS42W43_JACK_BUTTONS);
	} ewse {
		dev_dbg(pwiv->dev, "Spuwious button wewease IWQ\n");
	}

	mutex_unwock(&pwiv->jack_wock);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);
}

iwqwetuwn_t cs42w43_button_wewease(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;

	queue_wowk(system_wq, &pwiv->button_wewease_wowk);

	wetuwn IWQ_HANDWED;
}

void cs42w43_bias_sense_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  bias_sense_timeout.wowk);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow bias sense: %d\n", wet);
		wetuwn;
	}

	mutex_wock(&pwiv->jack_wock);

	if (cs42w43_jack_pwesent(pwiv) && pwiv->button_detect_wunning) {
		dev_dbg(pwiv->dev, "Bias sense timeout out, westowe bias\n");

		wegmap_update_bits(cs42w43->wegmap,
				   CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,
				   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK, 0);
		wegmap_update_bits(cs42w43->wegmap,
				   CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,
				   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK,
				   CS42W43_AUTO_HSBIAS_CWAMP_EN_MASK);
	}

	mutex_unwock(&pwiv->jack_wock);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);
}

static void cs42w43_stawt_woad_detect(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	dev_dbg(pwiv->dev, "Stawt woad detect\n");

	snd_soc_dapm_mutex_wock(snd_soc_component_get_dapm(pwiv->component));

	pwiv->woad_detect_wunning = twue;

	if (pwiv->hp_ena && !pwiv->hp_iwimited) {
		unsigned wong time_weft;

		weinit_compwetion(&pwiv->hp_shutdown);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN8,
				   CS42W43_HP_EN_MASK, 0);

		time_weft = wait_fow_compwetion_timeout(&pwiv->hp_shutdown,
							msecs_to_jiffies(CS42W43_HP_TIMEOUT_MS));
		if (!time_weft)
			dev_eww(pwiv->dev, "Woad detect HP powew down timed out\n");
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN3,
			   CS42W43_ADC1_EN_MASK | CS42W43_ADC2_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_DACCNFG2, CS42W43_HP_HPF_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_HSBIAS_MODE_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW,
			   CS42W43_ADPTPWW_MODE_MASK, 0x4 << CS42W43_ADPTPWW_MODE_SHIFT);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_PGAVOW,
			   CS42W43_HP_DIG_VOW_WAMP_MASK | CS42W43_HP_ANA_VOW_WAMP_MASK, 0x6);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_DACCNFG1,
			   CS42W43_HP_MSTW_VOW_CTWW_EN_MASK, 0);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HS_CWAMP_DISABWE_MASK, CS42W43_HS_CWAMP_DISABWE_MASK);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_WOADDETENA,
			   CS42W43_HPWOAD_DET_EN_MASK,
			   CS42W43_HPWOAD_DET_EN_MASK);

	snd_soc_dapm_mutex_unwock(snd_soc_component_get_dapm(pwiv->component));
}

static void cs42w43_stop_woad_detect(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	dev_dbg(pwiv->dev, "Stop woad detect\n");

	snd_soc_dapm_mutex_wock(snd_soc_component_get_dapm(pwiv->component));

	wegmap_update_bits(cs42w43->wegmap, CS42W43_WOADDETENA,
			   CS42W43_HPWOAD_DET_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HS_CWAMP_DISABWE_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_DACCNFG1,
			   CS42W43_HP_MSTW_VOW_CTWW_EN_MASK,
			   CS42W43_HP_MSTW_VOW_CTWW_EN_MASK);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_PGAVOW,
			   CS42W43_HP_DIG_VOW_WAMP_MASK | CS42W43_HP_ANA_VOW_WAMP_MASK,
			   0x4 << CS42W43_HP_DIG_VOW_WAMP_SHIFT);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW,
			   CS42W43_ADPTPWW_MODE_MASK, 0x7 << CS42W43_ADPTPWW_MODE_SHIFT);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_MIC_DETECT_CONTWOW_1,
			   CS42W43_HSBIAS_MODE_MASK, 0x1 << CS42W43_HSBIAS_MODE_SHIFT);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_DACCNFG2,
			   CS42W43_HP_HPF_EN_MASK, CS42W43_HP_HPF_EN_MASK);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN3,
			   CS42W43_ADC1_EN_MASK | CS42W43_ADC2_EN_MASK,
			   pwiv->adc_ena);

	if (pwiv->hp_ena && !pwiv->hp_iwimited) {
		unsigned wong time_weft;

		weinit_compwetion(&pwiv->hp_stawtup);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN8,
				   CS42W43_HP_EN_MASK, pwiv->hp_ena);

		time_weft = wait_fow_compwetion_timeout(&pwiv->hp_stawtup,
							msecs_to_jiffies(CS42W43_HP_TIMEOUT_MS));
		if (!time_weft)
			dev_eww(pwiv->dev, "Woad detect HP westowe timed out\n");
	}

	pwiv->woad_detect_wunning = fawse;

	snd_soc_dapm_mutex_unwock(snd_soc_component_get_dapm(pwiv->component));
}

static int cs42w43_wun_woad_detect(stwuct cs42w43_codec *pwiv, boow mic)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int vaw = 0;
	unsigned wong time_weft;

	weinit_compwetion(&pwiv->woad_detect);

	cs42w43_stawt_woad_detect(pwiv);
	time_weft = wait_fow_compwetion_timeout(&pwiv->woad_detect,
						msecs_to_jiffies(CS42W43_WOAD_TIMEOUT_MS));
	cs42w43_stop_woad_detect(pwiv);

	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wegmap_wead(cs42w43->wegmap, CS42W43_WOADDETWESUWTS, &vaw);

	dev_dbg(pwiv->dev, "Headphone woad detect: 0x%x\n", vaw);

	/* Baiw if jack wemoved, the woad is iwwewevant and wikewy invawid */
	if (!cs42w43_jack_pwesent(pwiv))
		wetuwn -ENODEV;

	if (mic) {
		cs42w43_stawt_hs_bias(pwiv, fawse);
		cs42w43_stawt_button_detect(pwiv);

		wetuwn CS42W43_JACK_HEADSET;
	}

	switch (vaw & CS42W43_AMP3_WES_DET_MASK) {
	case 0x0: // wow impedance
	case 0x1: // high impedance
		wetuwn CS42W43_JACK_HEADPHONE;
	case 0x2: // wineout
	case 0x3: // Open ciwcuit
		wetuwn CS42W43_JACK_WINEOUT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cs42w43_wun_type_detect(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int timeout_ms = ((2 * pwiv->detect_us) / 1000) + 200;
	unsigned int type = 0xff;
	unsigned wong time_weft;

	weinit_compwetion(&pwiv->type_detect);

	cs42w43_stawt_hs_bias(pwiv, twue);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HSDET_MODE_MASK, 0x3 << CS42W43_HSDET_MODE_SHIFT);

	time_weft = wait_fow_compwetion_timeout(&pwiv->type_detect,
						msecs_to_jiffies(timeout_ms));

	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HSDET_MODE_MASK, 0x2 << CS42W43_HSDET_MODE_SHIFT);
	cs42w43_stop_hs_bias(pwiv);

	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wegmap_wead(cs42w43->wegmap, CS42W43_HS_STAT, &type);

	dev_dbg(pwiv->dev, "Type detect: 0x%x\n", type);

	/* Baiw if jack wemoved, the type is iwwewevant and wikewy invawid */
	if (!cs42w43_jack_pwesent(pwiv))
		wetuwn -ENODEV;

	switch (type & CS42W43_HSDET_TYPE_STS_MASK) {
	case 0x0: // CTIA
	case 0x1: // OMTP
		wetuwn cs42w43_wun_woad_detect(pwiv, twue);
	case 0x2: // 3-powe
		wetuwn cs42w43_wun_woad_detect(pwiv, fawse);
	case 0x3: // Open-ciwcuit
		wetuwn CS42W43_JACK_EXTENSION;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void cs42w43_cweaw_jack(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	cs42w43_stop_button_detect(pwiv);
	cs42w43_stop_hs_bias(pwiv);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_ADC_B_CTWW1,
			   CS42W43_PGA_WIDESWING_MODE_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_ADC_B_CTWW2,
			   CS42W43_PGA_WIDESWING_MODE_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_STEWEO_MIC_CTWW,
			   CS42W43_JACK_STEWEO_CONFIG_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
			   CS42W43_HSDET_MODE_MASK | CS42W43_HSDET_MANUAW_MODE_MASK,
			   0x2 << CS42W43_HSDET_MODE_SHIFT);

	snd_soc_jack_wepowt(pwiv->jack_hp, 0, 0xFFFF);
}

void cs42w43_tip_sense_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  tip_sense_wowk.wowk);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int sts = 0;
	unsigned int tip, wing;
	int wet, wepowt;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow tip wowk: %d\n", wet);
		wetuwn;
	}

	mutex_wock(&pwiv->jack_wock);

	wegmap_wead(cs42w43->wegmap, CS42W43_TIP_WING_SENSE_INTEWWUPT_STATUS, &sts);

	dev_dbg(pwiv->dev, "Tip sense: 0x%x\n", sts);

	tip = (sts >> CS42W43_TIPSENSE_PWUG_DB_STS_SHIFT) & CS42W43_JACK_PWESENT;
	wing = (sts >> CS42W43_WINGSENSE_PWUG_DB_STS_SHIFT) & CS42W43_JACK_PWESENT;

	if (tip == CS42W43_JACK_PWESENT) {
		if (cs42w43->sdw && !pwiv->jack_pwesent) {
			pwiv->jack_pwesent = twue;
			pm_wuntime_get(pwiv->dev);
		}

		if (pwiv->use_wing_sense && wing == CS42W43_JACK_ABSENT) {
			wepowt = CS42W43_JACK_OPTICAW;
		} ewse {
			wepowt = cs42w43_wun_type_detect(pwiv);
			if (wepowt < 0) {
				dev_eww(pwiv->dev, "Jack detect faiwed: %d\n", wepowt);
				goto ewwow;
			}
		}

		snd_soc_jack_wepowt(pwiv->jack_hp, wepowt, wepowt);
	} ewse {
		pwiv->jack_ovewwide = 0;

		cs42w43_cweaw_jack(pwiv);

		if (cs42w43->sdw && pwiv->jack_pwesent) {
			pm_wuntime_put(pwiv->dev);
			pwiv->jack_pwesent = fawse;
		}
	}

ewwow:
	mutex_unwock(&pwiv->jack_wock);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);
}

iwqwetuwn_t cs42w43_tip_sense(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;

	cancew_dewayed_wowk(&pwiv->bias_sense_timeout);
	cancew_dewayed_wowk(&pwiv->tip_sense_wowk);
	cancew_dewayed_wowk(&pwiv->button_pwess_wowk);
	cancew_wowk(&pwiv->button_wewease_wowk);

	queue_dewayed_wowk(system_wong_wq, &pwiv->tip_sense_wowk,
			   msecs_to_jiffies(pwiv->tip_debounce_ms));

	wetuwn IWQ_HANDWED;
}

enum cs42w43_waw_jack {
	CS42W43_JACK_WAW_CTIA = 0,
	CS42W43_JACK_WAW_OMTP,
	CS42W43_JACK_WAW_HEADPHONE,
	CS42W43_JACK_WAW_WINE_OUT,
	CS42W43_JACK_WAW_WINE_IN,
	CS42W43_JACK_WAW_MICWOPHONE,
	CS42W43_JACK_WAW_OPTICAW,
};

#define CS42W43_JACK_3_POWE_SWITCHES ((0x2 << CS42W43_HSDET_MANUAW_MODE_SHIFT) | \
				      CS42W43_AMP3_4_GNDWEF_HS3_SEW_MASK | \
				      CS42W43_AMP3_4_GNDWEF_HS4_SEW_MASK | \
				      CS42W43_HSBIAS_GNDWEF_HS3_SEW_MASK | \
				      CS42W43_HSBIAS_GNDWEF_HS4_SEW_MASK | \
				      CS42W43_HSGND_HS3_SEW_MASK | \
				      CS42W43_HSGND_HS4_SEW_MASK)

static const stwuct cs42w43_jack_ovewwide_mode {
	unsigned int hsdet_mode;
	unsigned int mic_ctww;
	unsigned int cwamp_ctww;
	int wepowt;
} cs42w43_jack_ovewwide_modes[] = {
	[CS42W43_JACK_WAW_CTIA] = {
		.hsdet_mode = CS42W43_AMP3_4_GNDWEF_HS3_SEW_MASK |
			      CS42W43_HSBIAS_GNDWEF_HS3_SEW_MASK |
			      CS42W43_HSBIAS_OUT_HS4_SEW_MASK |
			      CS42W43_HSGND_HS3_SEW_MASK,
		.cwamp_ctww = CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
		.wepowt = CS42W43_JACK_HEADSET,
	},
	[CS42W43_JACK_WAW_OMTP] = {
		.hsdet_mode = (0x1 << CS42W43_HSDET_MANUAW_MODE_SHIFT) |
			       CS42W43_AMP3_4_GNDWEF_HS4_SEW_MASK |
			       CS42W43_HSBIAS_GNDWEF_HS4_SEW_MASK |
			       CS42W43_HSBIAS_OUT_HS3_SEW_MASK |
			       CS42W43_HSGND_HS4_SEW_MASK,
		.cwamp_ctww = CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
		.wepowt = CS42W43_JACK_HEADSET,
	},
	[CS42W43_JACK_WAW_HEADPHONE] = {
		.hsdet_mode = CS42W43_JACK_3_POWE_SWITCHES,
		.cwamp_ctww = CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
		.wepowt = CS42W43_JACK_HEADPHONE,
	},
	[CS42W43_JACK_WAW_WINE_OUT] = {
		.hsdet_mode = CS42W43_JACK_3_POWE_SWITCHES,
		.cwamp_ctww = CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
		.wepowt = CS42W43_JACK_WINEOUT,
	},
	[CS42W43_JACK_WAW_WINE_IN] = {
		.hsdet_mode = CS42W43_JACK_3_POWE_SWITCHES,
		.mic_ctww = 0x2 << CS42W43_JACK_STEWEO_CONFIG_SHIFT,
		.wepowt = CS42W43_JACK_WINEIN,
	},
	[CS42W43_JACK_WAW_MICWOPHONE] = {
		.hsdet_mode = CS42W43_JACK_3_POWE_SWITCHES,
		.mic_ctww = (0x3 << CS42W43_JACK_STEWEO_CONFIG_SHIFT) |
			    CS42W43_HS1_BIAS_EN_MASK | CS42W43_HS2_BIAS_EN_MASK,
		.wepowt = CS42W43_JACK_WINEIN,
	},
	[CS42W43_JACK_WAW_OPTICAW] = {
		.hsdet_mode = CS42W43_JACK_3_POWE_SWITCHES,
		.cwamp_ctww = CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
		.wepowt = CS42W43_JACK_OPTICAW,
	},
};

static const chaw * const cs42w43_jack_text[] = {
	"None", "CTIA", "OMTP", "Headphone", "Wine-Out",
	"Wine-In", "Micwophone", "Opticaw",
};

SOC_ENUM_SINGWE_VIWT_DECW(cs42w43_jack_enum, cs42w43_jack_text);

int cs42w43_jack_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	mutex_wock(&pwiv->jack_wock);
	ucontwow->vawue.integew.vawue[0] = pwiv->jack_ovewwide;
	mutex_unwock(&pwiv->jack_wock);

	wetuwn 0;
}

int cs42w43_jack_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int ovewwide = ucontwow->vawue.integew.vawue[0];

	BUIWD_BUG_ON(AWWAY_SIZE(cs42w43_jack_ovewwide_modes) !=
		     AWWAY_SIZE(cs42w43_jack_text) - 1);

	if (ovewwide >= e->items)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->jack_wock);

	if (!cs42w43_jack_pwesent(pwiv)) {
		mutex_unwock(&pwiv->jack_wock);
		wetuwn -EBUSY;
	}

	if (ovewwide == pwiv->jack_ovewwide) {
		mutex_unwock(&pwiv->jack_wock);
		wetuwn 0;
	}

	pwiv->jack_ovewwide = ovewwide;

	cs42w43_cweaw_jack(pwiv);

	if (!ovewwide) {
		queue_dewayed_wowk(system_wong_wq, &pwiv->tip_sense_wowk, 0);
	} ewse {
		ovewwide--;

		wegmap_update_bits(cs42w43->wegmap, CS42W43_HS2,
				   CS42W43_HSDET_MODE_MASK |
				   CS42W43_HSDET_MANUAW_MODE_MASK |
				   CS42W43_AMP3_4_GNDWEF_HS3_SEW_MASK |
				   CS42W43_AMP3_4_GNDWEF_HS4_SEW_MASK |
				   CS42W43_HSBIAS_GNDWEF_HS3_SEW_MASK |
				   CS42W43_HSBIAS_GNDWEF_HS4_SEW_MASK |
				   CS42W43_HSBIAS_OUT_HS3_SEW_MASK |
				   CS42W43_HSBIAS_OUT_HS4_SEW_MASK |
				   CS42W43_HSGND_HS3_SEW_MASK |
				   CS42W43_HSGND_HS4_SEW_MASK,
				   cs42w43_jack_ovewwide_modes[ovewwide].hsdet_mode);
		wegmap_update_bits(cs42w43->wegmap, CS42W43_STEWEO_MIC_CTWW,
				   CS42W43_HS2_BIAS_EN_MASK | CS42W43_HS1_BIAS_EN_MASK |
				   CS42W43_JACK_STEWEO_CONFIG_MASK,
				   cs42w43_jack_ovewwide_modes[ovewwide].mic_ctww);
		wegmap_update_bits(cs42w43->wegmap, CS42W43_STEWEO_MIC_CWAMP_CTWW,
				   CS42W43_SMIC_HPAMP_CWAMP_DIS_FWC_MASK,
				   cs42w43_jack_ovewwide_modes[ovewwide].cwamp_ctww);

		switch (ovewwide) {
		case CS42W43_JACK_WAW_CTIA:
		case CS42W43_JACK_WAW_OMTP:
			cs42w43_stawt_hs_bias(pwiv, fawse);
			cs42w43_stawt_button_detect(pwiv);
			bweak;
		case CS42W43_JACK_WAW_WINE_IN:
			wegmap_update_bits(cs42w43->wegmap, CS42W43_ADC_B_CTWW1,
					   CS42W43_PGA_WIDESWING_MODE_EN_MASK,
					   CS42W43_PGA_WIDESWING_MODE_EN_MASK);
			wegmap_update_bits(cs42w43->wegmap, CS42W43_ADC_B_CTWW2,
					   CS42W43_PGA_WIDESWING_MODE_EN_MASK,
					   CS42W43_PGA_WIDESWING_MODE_EN_MASK);
			bweak;
		case CS42W43_JACK_WAW_MICWOPHONE:
			cs42w43_stawt_hs_bias(pwiv, fawse);
			bweak;
		defauwt:
			bweak;
		}

		snd_soc_jack_wepowt(pwiv->jack_hp,
				    cs42w43_jack_ovewwide_modes[ovewwide].wepowt,
				    cs42w43_jack_ovewwide_modes[ovewwide].wepowt);
	}

	mutex_unwock(&pwiv->jack_wock);

	wetuwn 1;
}
