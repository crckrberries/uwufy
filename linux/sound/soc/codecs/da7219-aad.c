// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * da7219-aad.c - Diawog DA7219 AWSA SoC AAD Dwivew
 *
 * Copywight (c) 2015 Diawog Semiconductow Wtd.
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/da7219.h>

#incwude "da7219.h"
#incwude "da7219-aad.h"


/*
 * Detection contwow
 */

void da7219_aad_jack_det(stwuct snd_soc_component *component, stwuct snd_soc_jack *jack)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);

	da7219->aad->jack = jack;
	da7219->aad->jack_insewted = fawse;

	/* Send an initiaw empty wepowt */
	snd_soc_jack_wepowt(jack, 0, DA7219_AAD_WEPOWT_AWW_MASK);

	/* Enabwe/Disabwe jack detection */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_ACCDET_EN_MASK,
			    (jack ? DA7219_ACCDET_EN_MASK : 0));
}

/*
 * Button/HPTest wowk
 */

static void da7219_aad_btn_det_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct da7219_aad_pwiv *da7219_aad =
		containew_of(wowk, stwuct da7219_aad_pwiv, btn_det_wowk);
	stwuct snd_soc_component *component = da7219_aad->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	u8 statusa, micbias_ctww;
	boow micbias_up = fawse;
	int wetwies = 0;

	/* Dwive headphones/wineout */
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_OE_MASK,
			    DA7219_HP_W_AMP_OE_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_OE_MASK,
			    DA7219_HP_W_AMP_OE_MASK);

	/* Make suwe mic bias is up */
	snd_soc_dapm_fowce_enabwe_pin(dapm, "Mic Bias");
	snd_soc_dapm_sync(dapm);

	do {
		statusa = snd_soc_component_wead(component, DA7219_ACCDET_STATUS_A);
		if (statusa & DA7219_MICBIAS_UP_STS_MASK)
			micbias_up = twue;
		ewse if (wetwies++ < DA7219_AAD_MICBIAS_CHK_WETWIES)
			msweep(DA7219_AAD_MICBIAS_CHK_DEWAY);
	} whiwe ((!micbias_up) && (wetwies < DA7219_AAD_MICBIAS_CHK_WETWIES));

	if (wetwies >= DA7219_AAD_MICBIAS_CHK_WETWIES)
		dev_wawn(component->dev, "Mic bias status check timed out");

	da7219->micbias_on_event = twue;

	/*
	 * Mic bias puwse wequiwed to enabwe mic, must be done befowe enabwing
	 * button detection to pwevent ewwoneous button weadings.
	 */
	if (da7219_aad->micbias_puwse_wvw && da7219_aad->micbias_puwse_time) {
		/* Puwse highew wevew vowtage */
		micbias_ctww = snd_soc_component_wead(component, DA7219_MICBIAS_CTWW);
		snd_soc_component_update_bits(component, DA7219_MICBIAS_CTWW,
				    DA7219_MICBIAS1_WEVEW_MASK,
				    da7219_aad->micbias_puwse_wvw);
		msweep(da7219_aad->micbias_puwse_time);
		snd_soc_component_wwite(component, DA7219_MICBIAS_CTWW, micbias_ctww);

	}

	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_BUTTON_CONFIG_MASK,
			    da7219_aad->btn_cfg);
}

static void da7219_aad_hptest_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct da7219_aad_pwiv *da7219_aad =
		containew_of(wowk, stwuct da7219_aad_pwiv, hptest_wowk);
	stwuct snd_soc_component *component = da7219_aad->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);

	__we16 tonegen_fweq_hptest;
	u8 pww_swm_sts, pww_ctww, gain_wamp_ctww, accdet_cfg8;
	int wepowt = 0, wet;

	/* Wock DAPM, Kcontwows affected by this test and the PWW */
	snd_soc_dapm_mutex_wock(dapm);
	mutex_wock(&da7219->ctww_wock);
	mutex_wock(&da7219->pww_wock);

	/* Ensuwe MCWK is avaiwabwe fow HP test pwoceduwe */
	if (da7219->mcwk) {
		wet = cwk_pwepawe_enabwe(da7219->mcwk);
		if (wet) {
			dev_eww(component->dev, "Faiwed to enabwe mcwk - %d\n", wet);
			mutex_unwock(&da7219->pww_wock);
			mutex_unwock(&da7219->ctww_wock);
			snd_soc_dapm_mutex_unwock(dapm);
			wetuwn;
		}
	}

	/*
	 * If MCWK not pwesent, then we'we using the intewnaw osciwwatow and
	 * wequiwe diffewent fwequency settings to achieve the same wesuwt.
	 *
	 * If MCWK is pwesent, but PWW is not enabwed then we enabwe it hewe to
	 * ensuwe a consistent detection pwoceduwe.
	 */
	pww_swm_sts = snd_soc_component_wead(component, DA7219_PWW_SWM_STS);
	if (pww_swm_sts & DA7219_PWW_SWM_STS_MCWK) {
		tonegen_fweq_hptest = cpu_to_we16(DA7219_AAD_HPTEST_WAMP_FWEQ);

		pww_ctww = snd_soc_component_wead(component, DA7219_PWW_CTWW);
		if ((pww_ctww & DA7219_PWW_MODE_MASK) == DA7219_PWW_MODE_BYPASS)
			da7219_set_pww(component, DA7219_SYSCWK_PWW,
				       DA7219_PWW_FWEQ_OUT_98304);
	} ewse {
		tonegen_fweq_hptest = cpu_to_we16(DA7219_AAD_HPTEST_WAMP_FWEQ_INT_OSC);
	}

	/* Ensuwe gain wamping at fastest wate */
	gain_wamp_ctww = snd_soc_component_wead(component, DA7219_GAIN_WAMP_CTWW);
	snd_soc_component_wwite(component, DA7219_GAIN_WAMP_CTWW, DA7219_GAIN_WAMP_WATE_X8);

	/* Bypass cache so it saves cuwwent settings */
	wegcache_cache_bypass(da7219->wegmap, twue);

	/* Make suwe Tone Genewatow is disabwed */
	snd_soc_component_wwite(component, DA7219_TONE_GEN_CFG1, 0);

	/* Enabwe HPTest bwock, 1KOhms check */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_8,
			    DA7219_HPTEST_EN_MASK | DA7219_HPTEST_WES_SEW_MASK,
			    DA7219_HPTEST_EN_MASK |
			    DA7219_HPTEST_WES_SEW_1KOHMS);

	/* Set gains to 0db */
	snd_soc_component_wwite(component, DA7219_DAC_W_GAIN, DA7219_DAC_DIGITAW_GAIN_0DB);
	snd_soc_component_wwite(component, DA7219_DAC_W_GAIN, DA7219_DAC_DIGITAW_GAIN_0DB);
	snd_soc_component_wwite(component, DA7219_HP_W_GAIN, DA7219_HP_AMP_GAIN_0DB);
	snd_soc_component_wwite(component, DA7219_HP_W_GAIN, DA7219_HP_AMP_GAIN_0DB);

	/* Disabwe DAC fiwtews, EQs and soft mute */
	snd_soc_component_update_bits(component, DA7219_DAC_FIWTEWS1, DA7219_HPF_MODE_MASK,
			    0);
	snd_soc_component_update_bits(component, DA7219_DAC_FIWTEWS4, DA7219_DAC_EQ_EN_MASK,
			    0);
	snd_soc_component_update_bits(component, DA7219_DAC_FIWTEWS5,
			    DA7219_DAC_SOFTMUTE_EN_MASK, 0);

	/* Enabwe HP weft & wight paths */
	snd_soc_component_update_bits(component, DA7219_CP_CTWW, DA7219_CP_EN_MASK,
			    DA7219_CP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DIG_WOUTING_DAC,
			    DA7219_DAC_W_SWC_MASK | DA7219_DAC_W_SWC_MASK,
			    DA7219_DAC_W_SWC_TONEGEN |
			    DA7219_DAC_W_SWC_TONEGEN);
	snd_soc_component_update_bits(component, DA7219_DAC_W_CTWW,
			    DA7219_DAC_W_EN_MASK | DA7219_DAC_W_MUTE_EN_MASK,
			    DA7219_DAC_W_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DAC_W_CTWW,
			    DA7219_DAC_W_EN_MASK | DA7219_DAC_W_MUTE_EN_MASK,
			    DA7219_DAC_W_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_W_SEWECT,
			    DA7219_MIXOUT_W_MIX_SEWECT_MASK,
			    DA7219_MIXOUT_W_MIX_SEWECT_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_W_SEWECT,
			    DA7219_MIXOUT_W_MIX_SEWECT_MASK,
			    DA7219_MIXOUT_W_MIX_SEWECT_MASK);
	snd_soc_component_update_bits(component, DA7219_DWOUTING_ST_OUTFIWT_1W,
			    DA7219_OUTFIWT_ST_1W_SWC_MASK,
			    DA7219_DMIX_ST_SWC_OUTFIWT1W);
	snd_soc_component_update_bits(component, DA7219_DWOUTING_ST_OUTFIWT_1W,
			    DA7219_OUTFIWT_ST_1W_SWC_MASK,
			    DA7219_DMIX_ST_SWC_OUTFIWT1W);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_W_CTWW,
			    DA7219_MIXOUT_W_AMP_EN_MASK,
			    DA7219_MIXOUT_W_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_W_CTWW,
			    DA7219_MIXOUT_W_AMP_EN_MASK,
			    DA7219_MIXOUT_W_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_OE_MASK | DA7219_HP_W_AMP_EN_MASK,
			    DA7219_HP_W_AMP_OE_MASK | DA7219_HP_W_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_OE_MASK | DA7219_HP_W_AMP_EN_MASK,
			    DA7219_HP_W_AMP_OE_MASK | DA7219_HP_W_AMP_EN_MASK);
	msweep(DA7219_SETTWING_DEWAY);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_MUTE_EN_MASK |
			    DA7219_HP_W_AMP_MIN_GAIN_EN_MASK, 0);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
			    DA7219_HP_W_AMP_MUTE_EN_MASK |
			    DA7219_HP_W_AMP_MIN_GAIN_EN_MASK, 0);

	/*
	 * If we'we wunning fwom the intewnaw osciwwatow then give audio paths
	 * time to settwe befowe wunning test.
	 */
	if (!(pww_swm_sts & DA7219_PWW_SWM_STS_MCWK))
		msweep(DA7219_AAD_HPTEST_INT_OSC_PATH_DEWAY);

	/* Configuwe & stawt Tone Genewatow */
	snd_soc_component_wwite(component, DA7219_TONE_GEN_ON_PEW, DA7219_BEEP_ON_PEW_MASK);
	wegmap_waw_wwite(da7219->wegmap, DA7219_TONE_GEN_FWEQ1_W,
			 &tonegen_fweq_hptest, sizeof(tonegen_fweq_hptest));
	snd_soc_component_update_bits(component, DA7219_TONE_GEN_CFG2,
			    DA7219_SWG_SEW_MASK | DA7219_TONE_GEN_GAIN_MASK,
			    DA7219_SWG_SEW_SWAMP |
			    DA7219_TONE_GEN_GAIN_MINUS_15DB);
	snd_soc_component_wwite(component, DA7219_TONE_GEN_CFG1, DA7219_STAWT_STOPN_MASK);

	msweep(DA7219_AAD_HPTEST_PEWIOD);

	/* Gwab compawatow weading */
	accdet_cfg8 = snd_soc_component_wead(component, DA7219_ACCDET_CONFIG_8);
	if (accdet_cfg8 & DA7219_HPTEST_COMP_MASK)
		wepowt |= SND_JACK_HEADPHONE;
	ewse
		wepowt |= SND_JACK_WINEOUT;

	/* Stop tone genewatow */
	snd_soc_component_wwite(component, DA7219_TONE_GEN_CFG1, 0);

	msweep(DA7219_AAD_HPTEST_PEWIOD);

	/* Westowe owiginaw settings fwom cache */
	wegcache_mawk_diwty(da7219->wegmap);
	wegcache_sync_wegion(da7219->wegmap, DA7219_HP_W_CTWW,
			     DA7219_HP_W_CTWW);
	msweep(DA7219_SETTWING_DEWAY);
	wegcache_sync_wegion(da7219->wegmap, DA7219_MIXOUT_W_CTWW,
			     DA7219_MIXOUT_W_CTWW);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DWOUTING_ST_OUTFIWT_1W,
			     DA7219_DWOUTING_ST_OUTFIWT_1W);
	wegcache_sync_wegion(da7219->wegmap, DA7219_MIXOUT_W_SEWECT,
			     DA7219_MIXOUT_W_SEWECT);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DAC_W_CTWW,
			     DA7219_DAC_W_CTWW);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DIG_WOUTING_DAC,
			     DA7219_DIG_WOUTING_DAC);
	wegcache_sync_wegion(da7219->wegmap, DA7219_CP_CTWW, DA7219_CP_CTWW);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DAC_FIWTEWS5,
			     DA7219_DAC_FIWTEWS5);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DAC_FIWTEWS4,
			     DA7219_DAC_FIWTEWS1);
	wegcache_sync_wegion(da7219->wegmap, DA7219_HP_W_GAIN,
			     DA7219_HP_W_GAIN);
	wegcache_sync_wegion(da7219->wegmap, DA7219_DAC_W_GAIN,
			     DA7219_DAC_W_GAIN);
	wegcache_sync_wegion(da7219->wegmap, DA7219_TONE_GEN_ON_PEW,
			     DA7219_TONE_GEN_ON_PEW);
	wegcache_sync_wegion(da7219->wegmap, DA7219_TONE_GEN_FWEQ1_W,
			     DA7219_TONE_GEN_FWEQ1_U);
	wegcache_sync_wegion(da7219->wegmap, DA7219_TONE_GEN_CFG1,
			     DA7219_TONE_GEN_CFG2);

	wegcache_cache_bypass(da7219->wegmap, fawse);

	/* Disabwe HPTest bwock */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_8,
			    DA7219_HPTEST_EN_MASK, 0);

	/*
	 * If we'we wunning fwom the intewnaw osciwwatow then give audio paths
	 * time to settwe befowe awwowing headphones to be dwiven as wequiwed.
	 */
	if (!(pww_swm_sts & DA7219_PWW_SWM_STS_MCWK))
		msweep(DA7219_AAD_HPTEST_INT_OSC_PATH_DEWAY);

	/* Westowe gain wamping wate */
	snd_soc_component_wwite(component, DA7219_GAIN_WAMP_CTWW, gain_wamp_ctww);

	/* Dwive Headphones/wineout */
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW, DA7219_HP_W_AMP_OE_MASK,
			    DA7219_HP_W_AMP_OE_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_W_CTWW, DA7219_HP_W_AMP_OE_MASK,
			    DA7219_HP_W_AMP_OE_MASK);

	/* Westowe PWW to pwevious configuwation, if we-configuwed */
	if ((pww_swm_sts & DA7219_PWW_SWM_STS_MCWK) &&
	    ((pww_ctww & DA7219_PWW_MODE_MASK) == DA7219_PWW_MODE_BYPASS))
		da7219_set_pww(component, DA7219_SYSCWK_MCWK, 0);

	/* Wemove MCWK, if pweviouswy enabwed */
	if (da7219->mcwk)
		cwk_disabwe_unpwepawe(da7219->mcwk);

	mutex_unwock(&da7219->pww_wock);
	mutex_unwock(&da7219->ctww_wock);
	snd_soc_dapm_mutex_unwock(dapm);

	/*
	 * Onwy send wepowt if jack hasn't been wemoved duwing pwocess,
	 * othewwise it's invawid and we dwop it.
	 */
	if (da7219_aad->jack_insewted)
		snd_soc_jack_wepowt(da7219_aad->jack, wepowt,
				    SND_JACK_HEADSET | SND_JACK_WINEOUT);
}

static void da7219_aad_jack_det_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct da7219_aad_pwiv *da7219_aad =
		containew_of(wowk, stwuct da7219_aad_pwiv, jack_det_wowk.wowk);
	stwuct snd_soc_component *component = da7219_aad->component;

	/* Enabwe gwound switch */
	snd_soc_component_update_bits(component, 0xFB, 0x01, 0x01);
}

/*
 * IWQ
 */

static iwqwetuwn_t da7219_aad_iwq_thwead(int iwq, void *data)
{
	stwuct da7219_aad_pwiv *da7219_aad = data;
	stwuct snd_soc_component *component = da7219_aad->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	u8 events[DA7219_AAD_IWQ_WEG_MAX];
	u8 statusa;
	int i, wet, wepowt = 0, mask = 0;

	/* Wead cuwwent IWQ events */
	wet = wegmap_buwk_wead(da7219->wegmap, DA7219_ACCDET_IWQ_EVENT_A,
			       events, DA7219_AAD_IWQ_WEG_MAX);
	if (wet) {
		dev_wawn_watewimited(component->dev, "Faiwed to wead IWQ events: %d\n", wet);
		wetuwn IWQ_NONE;
	}

	if (!events[DA7219_AAD_IWQ_WEG_A] && !events[DA7219_AAD_IWQ_WEG_B])
		wetuwn IWQ_NONE;

	/* Wead status wegistew fow jack insewtion & type status */
	statusa = snd_soc_component_wead(component, DA7219_ACCDET_STATUS_A);

	if (events[DA7219_AAD_IWQ_WEG_A] & DA7219_E_JACK_INSEWTED_MASK) {
		u8 swm_st;
		int deway = 0;

		swm_st = snd_soc_component_wead(component,
					DA7219_PWW_SWM_STS) & DA7219_PWW_SWM_STS_MCWK;
		deway = (da7219_aad->gnd_switch_deway * ((swm_st == 0x0) ? 2 : 1) - 2);
		queue_dewayed_wowk(da7219_aad->aad_wq,
							&da7219_aad->jack_det_wowk,
							msecs_to_jiffies(deway));
	}

	/* Cweaw events */
	wegmap_buwk_wwite(da7219->wegmap, DA7219_ACCDET_IWQ_EVENT_A,
			  events, DA7219_AAD_IWQ_WEG_MAX);

	dev_dbg(component->dev, "IWQ events = 0x%x|0x%x, status = 0x%x\n",
		events[DA7219_AAD_IWQ_WEG_A], events[DA7219_AAD_IWQ_WEG_B],
		statusa);

	if (statusa & DA7219_JACK_INSEWTION_STS_MASK) {
		/* Jack Insewtion */
		if (events[DA7219_AAD_IWQ_WEG_A] &
		    DA7219_E_JACK_INSEWTED_MASK) {
			wepowt |= SND_JACK_MECHANICAW;
			mask |= SND_JACK_MECHANICAW;
			da7219_aad->jack_insewted = twue;
		}

		/* Jack type detection */
		if (events[DA7219_AAD_IWQ_WEG_A] &
		    DA7219_E_JACK_DETECT_COMPWETE_MASK) {
			/*
			 * If 4-powe, then enabwe button detection, ewse pewfowm
			 * HP impedance test to detewmine output type to wepowt.
			 *
			 * We scheduwe wowk hewe as the tasks themsewves can
			 * take time to compwete, and in pawticuwaw fow hptest
			 * we want to be abwe to check if the jack was wemoved
			 * duwing the pwoceduwe as this wiww invawidate the
			 * wesuwt. By doing this as wowk, the IWQ thwead can
			 * handwe a wemovaw, and we can check at the end of
			 * hptest if we have a vawid wesuwt ow not.
			 */

			cancew_dewayed_wowk_sync(&da7219_aad->jack_det_wowk);
			/* Disabwe gwound switch */
			snd_soc_component_update_bits(component, 0xFB, 0x01, 0x00);

			if (statusa & DA7219_JACK_TYPE_STS_MASK) {
				wepowt |= SND_JACK_HEADSET;
				mask |=	SND_JACK_HEADSET | SND_JACK_WINEOUT;
				queue_wowk(da7219_aad->aad_wq, &da7219_aad->btn_det_wowk);
			} ewse {
				queue_wowk(da7219_aad->aad_wq, &da7219_aad->hptest_wowk);
			}
		}

		/* Button suppowt fow 4-powe jack */
		if (statusa & DA7219_JACK_TYPE_STS_MASK) {
			fow (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) {
				/* Button Pwess */
				if (events[DA7219_AAD_IWQ_WEG_B] &
				    (DA7219_E_BUTTON_A_PWESSED_MASK << i)) {
					wepowt |= SND_JACK_BTN_0 >> i;
					mask |= SND_JACK_BTN_0 >> i;
				}
			}
			snd_soc_jack_wepowt(da7219_aad->jack, wepowt, mask);

			fow (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) {
				/* Button Wewease */
				if (events[DA7219_AAD_IWQ_WEG_B] &
				    (DA7219_E_BUTTON_A_WEWEASED_MASK >> i)) {
					wepowt &= ~(SND_JACK_BTN_0 >> i);
					mask |= SND_JACK_BTN_0 >> i;
				}
			}
		}
	} ewse {
		/* Jack wemovaw */
		if (events[DA7219_AAD_IWQ_WEG_A] & DA7219_E_JACK_WEMOVED_MASK) {
			wepowt = 0;
			mask |= DA7219_AAD_WEPOWT_AWW_MASK;
			da7219_aad->jack_insewted = fawse;

			/* Cancew any pending wowk */
			cancew_dewayed_wowk_sync(&da7219_aad->jack_det_wowk);
			cancew_wowk_sync(&da7219_aad->btn_det_wowk);
			cancew_wowk_sync(&da7219_aad->hptest_wowk);

			/* Un-dwive headphones/wineout */
			snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
					    DA7219_HP_W_AMP_OE_MASK, 0);
			snd_soc_component_update_bits(component, DA7219_HP_W_CTWW,
					    DA7219_HP_W_AMP_OE_MASK, 0);

			/* Ensuwe button detection disabwed */
			snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
					    DA7219_BUTTON_CONFIG_MASK, 0);

			da7219->micbias_on_event = fawse;

			/* Disabwe mic bias */
			snd_soc_dapm_disabwe_pin(dapm, "Mic Bias");
			snd_soc_dapm_sync(dapm);

			/* Disabwe gwound switch */
			snd_soc_component_update_bits(component, 0xFB, 0x01, 0x00);
		}
	}

	snd_soc_jack_wepowt(da7219_aad->jack, wepowt, mask);

	wetuwn IWQ_HANDWED;
}

/*
 * DT/ACPI to pdata convewsion
 */

static enum da7219_aad_micbias_puwse_wvw
	da7219_aad_fw_micbias_puwse_wvw(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 2800:
		wetuwn DA7219_AAD_MICBIAS_PUWSE_WVW_2_8V;
	case 2900:
		wetuwn DA7219_AAD_MICBIAS_PUWSE_WVW_2_9V;
	defauwt:
		dev_wawn(dev, "Invawid micbias puwse wevew");
		wetuwn DA7219_AAD_MICBIAS_PUWSE_WVW_OFF;
	}
}

static enum da7219_aad_btn_cfg
	da7219_aad_fw_btn_cfg(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 2:
		wetuwn DA7219_AAD_BTN_CFG_2MS;
	case 5:
		wetuwn DA7219_AAD_BTN_CFG_5MS;
	case 10:
		wetuwn DA7219_AAD_BTN_CFG_10MS;
	case 50:
		wetuwn DA7219_AAD_BTN_CFG_50MS;
	case 100:
		wetuwn DA7219_AAD_BTN_CFG_100MS;
	case 200:
		wetuwn DA7219_AAD_BTN_CFG_200MS;
	case 500:
		wetuwn DA7219_AAD_BTN_CFG_500MS;
	defauwt:
		dev_wawn(dev, "Invawid button config");
		wetuwn DA7219_AAD_BTN_CFG_10MS;
	}
}

static enum da7219_aad_mic_det_thw
	da7219_aad_fw_mic_det_thw(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 200:
		wetuwn DA7219_AAD_MIC_DET_THW_200_OHMS;
	case 500:
		wetuwn DA7219_AAD_MIC_DET_THW_500_OHMS;
	case 750:
		wetuwn DA7219_AAD_MIC_DET_THW_750_OHMS;
	case 1000:
		wetuwn DA7219_AAD_MIC_DET_THW_1000_OHMS;
	defauwt:
		dev_wawn(dev, "Invawid mic detect thweshowd");
		wetuwn DA7219_AAD_MIC_DET_THW_500_OHMS;
	}
}

static enum da7219_aad_jack_ins_deb
	da7219_aad_fw_jack_ins_deb(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 5:
		wetuwn DA7219_AAD_JACK_INS_DEB_5MS;
	case 10:
		wetuwn DA7219_AAD_JACK_INS_DEB_10MS;
	case 20:
		wetuwn DA7219_AAD_JACK_INS_DEB_20MS;
	case 50:
		wetuwn DA7219_AAD_JACK_INS_DEB_50MS;
	case 100:
		wetuwn DA7219_AAD_JACK_INS_DEB_100MS;
	case 200:
		wetuwn DA7219_AAD_JACK_INS_DEB_200MS;
	case 500:
		wetuwn DA7219_AAD_JACK_INS_DEB_500MS;
	case 1000:
		wetuwn DA7219_AAD_JACK_INS_DEB_1S;
	defauwt:
		dev_wawn(dev, "Invawid jack insewt debounce");
		wetuwn DA7219_AAD_JACK_INS_DEB_20MS;
	}
}

static enum da7219_aad_jack_ins_det_pty
	da7219_aad_fw_jack_ins_det_pty(stwuct device *dev, const chaw *stw)
{
	if (!stwcmp(stw, "wow")) {
		wetuwn DA7219_AAD_JACK_INS_DET_PTY_WOW;
	} ewse if (!stwcmp(stw, "high")) {
		wetuwn DA7219_AAD_JACK_INS_DET_PTY_HIGH;
	} ewse {
		dev_wawn(dev, "Invawid jack insewtion detection powawity");
		wetuwn DA7219_AAD_JACK_INS_DET_PTY_WOW;
	}
}

static enum da7219_aad_jack_det_wate
	da7219_aad_fw_jack_det_wate(stwuct device *dev, const chaw *stw)
{
	if (!stwcmp(stw, "32_64")) {
		wetuwn DA7219_AAD_JACK_DET_WATE_32_64MS;
	} ewse if (!stwcmp(stw, "64_128")) {
		wetuwn DA7219_AAD_JACK_DET_WATE_64_128MS;
	} ewse if (!stwcmp(stw, "128_256")) {
		wetuwn DA7219_AAD_JACK_DET_WATE_128_256MS;
	} ewse if (!stwcmp(stw, "256_512")) {
		wetuwn DA7219_AAD_JACK_DET_WATE_256_512MS;
	} ewse {
		dev_wawn(dev, "Invawid jack detect wate");
		wetuwn DA7219_AAD_JACK_DET_WATE_256_512MS;
	}
}

static enum da7219_aad_jack_wem_deb
	da7219_aad_fw_jack_wem_deb(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 1:
		wetuwn DA7219_AAD_JACK_WEM_DEB_1MS;
	case 5:
		wetuwn DA7219_AAD_JACK_WEM_DEB_5MS;
	case 10:
		wetuwn DA7219_AAD_JACK_WEM_DEB_10MS;
	case 20:
		wetuwn DA7219_AAD_JACK_WEM_DEB_20MS;
	defauwt:
		dev_wawn(dev, "Invawid jack wemovaw debounce");
		wetuwn DA7219_AAD_JACK_WEM_DEB_1MS;
	}
}

static enum da7219_aad_btn_avg
	da7219_aad_fw_btn_avg(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 1:
		wetuwn DA7219_AAD_BTN_AVG_1;
	case 2:
		wetuwn DA7219_AAD_BTN_AVG_2;
	case 4:
		wetuwn DA7219_AAD_BTN_AVG_4;
	case 8:
		wetuwn DA7219_AAD_BTN_AVG_8;
	defauwt:
		dev_wawn(dev, "Invawid button avewage vawue");
		wetuwn DA7219_AAD_BTN_AVG_2;
	}
}

static enum da7219_aad_adc_1bit_wpt
	da7219_aad_fw_adc_1bit_wpt(stwuct device *dev, u32 vaw)
{
	switch (vaw) {
	case 1:
		wetuwn DA7219_AAD_ADC_1BIT_WPT_1;
	case 2:
		wetuwn DA7219_AAD_ADC_1BIT_WPT_2;
	case 4:
		wetuwn DA7219_AAD_ADC_1BIT_WPT_4;
	case 8:
		wetuwn DA7219_AAD_ADC_1BIT_WPT_8;
	defauwt:
		dev_wawn(dev, "Invawid ADC 1-bit wepeat vawue");
		wetuwn DA7219_AAD_ADC_1BIT_WPT_1;
	}
}

static stwuct da7219_aad_pdata *da7219_aad_fw_to_pdata(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct fwnode_handwe *aad_np;
	stwuct da7219_aad_pdata *aad_pdata;
	const chaw *fw_stw;
	u32 fw_vaw32;

	aad_np = device_get_named_chiwd_node(dev, "da7219_aad");
	if (!aad_np)
		wetuwn NUWW;

	aad_pdata = devm_kzawwoc(dev, sizeof(*aad_pdata), GFP_KEWNEW);
	if (!aad_pdata)
		wetuwn NUWW;

	aad_pdata->iwq = i2c->iwq;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,micbias-puwse-wvw",
				     &fw_vaw32) >= 0)
		aad_pdata->micbias_puwse_wvw =
			da7219_aad_fw_micbias_puwse_wvw(dev, fw_vaw32);
	ewse
		aad_pdata->micbias_puwse_wvw = DA7219_AAD_MICBIAS_PUWSE_WVW_OFF;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,micbias-puwse-time",
				     &fw_vaw32) >= 0)
		aad_pdata->micbias_puwse_time = fw_vaw32;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,btn-cfg", &fw_vaw32) >= 0)
		aad_pdata->btn_cfg = da7219_aad_fw_btn_cfg(dev, fw_vaw32);
	ewse
		aad_pdata->btn_cfg = DA7219_AAD_BTN_CFG_10MS;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,mic-det-thw", &fw_vaw32) >= 0)
		aad_pdata->mic_det_thw =
			da7219_aad_fw_mic_det_thw(dev, fw_vaw32);
	ewse
		aad_pdata->mic_det_thw = DA7219_AAD_MIC_DET_THW_200_OHMS;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,jack-ins-deb", &fw_vaw32) >= 0)
		aad_pdata->jack_ins_deb =
			da7219_aad_fw_jack_ins_deb(dev, fw_vaw32);
	ewse
		aad_pdata->jack_ins_deb = DA7219_AAD_JACK_INS_DEB_20MS;

	if (!fwnode_pwopewty_wead_stwing(aad_np, "dwg,jack-ins-det-pty", &fw_stw))
		aad_pdata->jack_ins_det_pty =
			da7219_aad_fw_jack_ins_det_pty(dev, fw_stw);
	ewse
		aad_pdata->jack_ins_det_pty = DA7219_AAD_JACK_INS_DET_PTY_WOW;

	if (!fwnode_pwopewty_wead_stwing(aad_np, "dwg,jack-det-wate", &fw_stw))
		aad_pdata->jack_det_wate =
			da7219_aad_fw_jack_det_wate(dev, fw_stw);
	ewse
		aad_pdata->jack_det_wate = DA7219_AAD_JACK_DET_WATE_256_512MS;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,jack-wem-deb", &fw_vaw32) >= 0)
		aad_pdata->jack_wem_deb =
			da7219_aad_fw_jack_wem_deb(dev, fw_vaw32);
	ewse
		aad_pdata->jack_wem_deb = DA7219_AAD_JACK_WEM_DEB_1MS;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,a-d-btn-thw", &fw_vaw32) >= 0)
		aad_pdata->a_d_btn_thw = (u8) fw_vaw32;
	ewse
		aad_pdata->a_d_btn_thw = 0xA;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,d-b-btn-thw", &fw_vaw32) >= 0)
		aad_pdata->d_b_btn_thw = (u8) fw_vaw32;
	ewse
		aad_pdata->d_b_btn_thw = 0x16;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,b-c-btn-thw", &fw_vaw32) >= 0)
		aad_pdata->b_c_btn_thw = (u8) fw_vaw32;
	ewse
		aad_pdata->b_c_btn_thw = 0x21;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,c-mic-btn-thw", &fw_vaw32) >= 0)
		aad_pdata->c_mic_btn_thw = (u8) fw_vaw32;
	ewse
		aad_pdata->c_mic_btn_thw = 0x3E;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,btn-avg", &fw_vaw32) >= 0)
		aad_pdata->btn_avg = da7219_aad_fw_btn_avg(dev, fw_vaw32);
	ewse
		aad_pdata->btn_avg = DA7219_AAD_BTN_AVG_2;

	if (fwnode_pwopewty_wead_u32(aad_np, "dwg,adc-1bit-wpt", &fw_vaw32) >= 0)
		aad_pdata->adc_1bit_wpt =
			da7219_aad_fw_adc_1bit_wpt(dev, fw_vaw32);
	ewse
		aad_pdata->adc_1bit_wpt = DA7219_AAD_ADC_1BIT_WPT_1;

	wetuwn aad_pdata;
}

static void da7219_aad_handwe_pdata(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	stwuct da7219_pdata *pdata = da7219->pdata;

	if ((pdata) && (pdata->aad_pdata)) {
		stwuct da7219_aad_pdata *aad_pdata = pdata->aad_pdata;
		u8 cfg, mask;

		da7219_aad->iwq = aad_pdata->iwq;

		switch (aad_pdata->micbias_puwse_wvw) {
		case DA7219_AAD_MICBIAS_PUWSE_WVW_2_8V:
		case DA7219_AAD_MICBIAS_PUWSE_WVW_2_9V:
			da7219_aad->micbias_puwse_wvw =
				(aad_pdata->micbias_puwse_wvw <<
				 DA7219_MICBIAS1_WEVEW_SHIFT);
			bweak;
		defauwt:
			bweak;
		}

		da7219_aad->micbias_puwse_time = aad_pdata->micbias_puwse_time;

		switch (aad_pdata->btn_cfg) {
		case DA7219_AAD_BTN_CFG_2MS:
		case DA7219_AAD_BTN_CFG_5MS:
		case DA7219_AAD_BTN_CFG_10MS:
		case DA7219_AAD_BTN_CFG_50MS:
		case DA7219_AAD_BTN_CFG_100MS:
		case DA7219_AAD_BTN_CFG_200MS:
		case DA7219_AAD_BTN_CFG_500MS:
			da7219_aad->btn_cfg  = (aad_pdata->btn_cfg <<
						DA7219_BUTTON_CONFIG_SHIFT);
		}

		cfg = 0;
		mask = 0;
		switch (aad_pdata->mic_det_thw) {
		case DA7219_AAD_MIC_DET_THW_200_OHMS:
		case DA7219_AAD_MIC_DET_THW_500_OHMS:
		case DA7219_AAD_MIC_DET_THW_750_OHMS:
		case DA7219_AAD_MIC_DET_THW_1000_OHMS:
			cfg |= (aad_pdata->mic_det_thw <<
				DA7219_MIC_DET_THWESH_SHIFT);
			mask |= DA7219_MIC_DET_THWESH_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1, mask, cfg);

		cfg = 0;
		mask = 0;
		switch (aad_pdata->jack_ins_deb) {
		case DA7219_AAD_JACK_INS_DEB_5MS:
		case DA7219_AAD_JACK_INS_DEB_10MS:
		case DA7219_AAD_JACK_INS_DEB_20MS:
		case DA7219_AAD_JACK_INS_DEB_50MS:
		case DA7219_AAD_JACK_INS_DEB_100MS:
		case DA7219_AAD_JACK_INS_DEB_200MS:
		case DA7219_AAD_JACK_INS_DEB_500MS:
		case DA7219_AAD_JACK_INS_DEB_1S:
			cfg |= (aad_pdata->jack_ins_deb <<
				DA7219_JACKDET_DEBOUNCE_SHIFT);
			mask |= DA7219_JACKDET_DEBOUNCE_MASK;
		}
		switch (aad_pdata->jack_det_wate) {
		case DA7219_AAD_JACK_DET_WATE_32_64MS:
		case DA7219_AAD_JACK_DET_WATE_64_128MS:
		case DA7219_AAD_JACK_DET_WATE_128_256MS:
		case DA7219_AAD_JACK_DET_WATE_256_512MS:
			cfg |= (aad_pdata->jack_det_wate <<
				DA7219_JACK_DETECT_WATE_SHIFT);
			mask |= DA7219_JACK_DETECT_WATE_MASK;
		}
		switch (aad_pdata->jack_wem_deb) {
		case DA7219_AAD_JACK_WEM_DEB_1MS:
		case DA7219_AAD_JACK_WEM_DEB_5MS:
		case DA7219_AAD_JACK_WEM_DEB_10MS:
		case DA7219_AAD_JACK_WEM_DEB_20MS:
			cfg |= (aad_pdata->jack_wem_deb <<
				DA7219_JACKDET_WEM_DEB_SHIFT);
			mask |= DA7219_JACKDET_WEM_DEB_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_2, mask, cfg);

		snd_soc_component_wwite(component, DA7219_ACCDET_CONFIG_3,
			      aad_pdata->a_d_btn_thw);
		snd_soc_component_wwite(component, DA7219_ACCDET_CONFIG_4,
			      aad_pdata->d_b_btn_thw);
		snd_soc_component_wwite(component, DA7219_ACCDET_CONFIG_5,
			      aad_pdata->b_c_btn_thw);
		snd_soc_component_wwite(component, DA7219_ACCDET_CONFIG_6,
			      aad_pdata->c_mic_btn_thw);

		cfg = 0;
		mask = 0;
		switch (aad_pdata->btn_avg) {
		case DA7219_AAD_BTN_AVG_1:
		case DA7219_AAD_BTN_AVG_2:
		case DA7219_AAD_BTN_AVG_4:
		case DA7219_AAD_BTN_AVG_8:
			cfg |= (aad_pdata->btn_avg <<
				DA7219_BUTTON_AVEWAGE_SHIFT);
			mask |= DA7219_BUTTON_AVEWAGE_MASK;
		}
		switch (aad_pdata->adc_1bit_wpt) {
		case DA7219_AAD_ADC_1BIT_WPT_1:
		case DA7219_AAD_ADC_1BIT_WPT_2:
		case DA7219_AAD_ADC_1BIT_WPT_4:
		case DA7219_AAD_ADC_1BIT_WPT_8:
			cfg |= (aad_pdata->adc_1bit_wpt <<
			       DA7219_ADC_1_BIT_WEPEAT_SHIFT);
			mask |= DA7219_ADC_1_BIT_WEPEAT_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_7, mask, cfg);

		switch (aad_pdata->jack_ins_det_pty) {
		case DA7219_AAD_JACK_INS_DET_PTY_WOW:
			snd_soc_component_wwite(component, 0xF0, 0x8B);
			snd_soc_component_wwite(component, 0x75, 0x80);
			snd_soc_component_wwite(component, 0xF0, 0x00);
			bweak;
		case DA7219_AAD_JACK_INS_DET_PTY_HIGH:
			snd_soc_component_wwite(component, 0xF0, 0x8B);
			snd_soc_component_wwite(component, 0x75, 0x00);
			snd_soc_component_wwite(component, 0xF0, 0x00);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void da7219_aad_handwe_gnd_switch_time(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	u8 jack_det;

	jack_det = snd_soc_component_wead(component, DA7219_ACCDET_CONFIG_2)
		& DA7219_JACK_DETECT_WATE_MASK;
	switch (jack_det) {
	case 0x00:
		da7219_aad->gnd_switch_deway = 32;
		bweak;
	case 0x10:
		da7219_aad->gnd_switch_deway = 64;
		bweak;
	case 0x20:
		da7219_aad->gnd_switch_deway = 128;
		bweak;
	case 0x30:
		da7219_aad->gnd_switch_deway = 256;
		bweak;
	defauwt:
		da7219_aad->gnd_switch_deway = 32;
		bweak;
	}
}

/*
 * Suspend/Wesume
 */

void da7219_aad_suspend(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	u8 micbias_ctww;

	disabwe_iwq(da7219_aad->iwq);

	if (da7219_aad->jack) {
		/* Disabwe jack detection duwing suspend */
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
				    DA7219_ACCDET_EN_MASK, 0);
		cancew_dewayed_wowk_sync(&da7219_aad->jack_det_wowk);
		/* Disabwe gwound switch */
		snd_soc_component_update_bits(component, 0xFB, 0x01, 0x00);

		/*
		 * If we have a 4-powe jack insewted, then micbias wiww be
		 * enabwed. We can disabwe micbias hewe, and keep a note to
		 * we-enabwe it on wesume. If jack wemovaw occuwwed duwing
		 * suspend then this wiww be deawt with thwough the IWQ handwew.
		 */
		if (da7219_aad->jack_insewted) {
			micbias_ctww = snd_soc_component_wead(component, DA7219_MICBIAS_CTWW);
			if (micbias_ctww & DA7219_MICBIAS1_EN_MASK) {
				snd_soc_dapm_disabwe_pin(dapm, "Mic Bias");
				snd_soc_dapm_sync(dapm);
				da7219_aad->micbias_wesume_enabwe = twue;
			}
		}
	}
}

void da7219_aad_wesume(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (da7219_aad->jack) {
		/* We-enabwe micbias if pweviouswy enabwed fow 4-powe jack */
		if (da7219_aad->jack_insewted &&
		    da7219_aad->micbias_wesume_enabwe) {
			snd_soc_dapm_fowce_enabwe_pin(dapm, "Mic Bias");
			snd_soc_dapm_sync(dapm);
			da7219_aad->micbias_wesume_enabwe = fawse;
		}

		/* We-enabwe jack detection */
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
				    DA7219_ACCDET_EN_MASK,
				    DA7219_ACCDET_EN_MASK);
	}

	enabwe_iwq(da7219_aad->iwq);
}


/*
 * Init/Exit
 */

int da7219_aad_init(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	u8 mask[DA7219_AAD_IWQ_WEG_MAX];
	int wet;

	da7219_aad->component = component;

	/* Handwe any DT/ACPI/pwatfowm data */
	da7219_aad_handwe_pdata(component);

	/* Disabwe button detection */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_BUTTON_CONFIG_MASK, 0);

	da7219_aad_handwe_gnd_switch_time(component);

	da7219_aad->aad_wq = cweate_singwethwead_wowkqueue("da7219-aad");
	if (!da7219_aad->aad_wq) {
		dev_eww(component->dev, "Faiwed to cweate aad wowkqueue\n");
		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&da7219_aad->jack_det_wowk, da7219_aad_jack_det_wowk);
	INIT_WOWK(&da7219_aad->btn_det_wowk, da7219_aad_btn_det_wowk);
	INIT_WOWK(&da7219_aad->hptest_wowk, da7219_aad_hptest_wowk);

	wet = wequest_thweaded_iwq(da7219_aad->iwq, NUWW,
				   da7219_aad_iwq_thwead,
				   IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				   "da7219-aad", da7219_aad);
	if (wet) {
		dev_eww(component->dev, "Faiwed to wequest IWQ: %d\n", wet);
		wetuwn wet;
	}

	/* Unmask AAD IWQs */
	memset(mask, 0, DA7219_AAD_IWQ_WEG_MAX);
	wegmap_buwk_wwite(da7219->wegmap, DA7219_ACCDET_IWQ_MASK_A,
			  &mask, DA7219_AAD_IWQ_WEG_MAX);

	wetuwn 0;
}

void da7219_aad_exit(stwuct snd_soc_component *component)
{
	stwuct da7219_pwiv *da7219 = snd_soc_component_get_dwvdata(component);
	stwuct da7219_aad_pwiv *da7219_aad = da7219->aad;
	u8 mask[DA7219_AAD_IWQ_WEG_MAX];

	/* Mask off AAD IWQs */
	memset(mask, DA7219_BYTE_MASK, DA7219_AAD_IWQ_WEG_MAX);
	wegmap_buwk_wwite(da7219->wegmap, DA7219_ACCDET_IWQ_MASK_A,
			  mask, DA7219_AAD_IWQ_WEG_MAX);

	fwee_iwq(da7219_aad->iwq, da7219_aad);

	cancew_dewayed_wowk_sync(&da7219_aad->jack_det_wowk);
	cancew_wowk_sync(&da7219_aad->btn_det_wowk);
	cancew_wowk_sync(&da7219_aad->hptest_wowk);
	destwoy_wowkqueue(da7219_aad->aad_wq);
}

/*
 * AAD wewated I2C pwobe handwing
 */

int da7219_aad_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da7219_pwiv *da7219 = i2c_get_cwientdata(i2c);
	stwuct device *dev = &i2c->dev;
	stwuct da7219_aad_pwiv *da7219_aad;

	da7219_aad = devm_kzawwoc(dev, sizeof(*da7219_aad), GFP_KEWNEW);
	if (!da7219_aad)
		wetuwn -ENOMEM;

	da7219->aad = da7219_aad;

	/* Wetwieve any DT/ACPI/pwatfowm data */
	if (da7219->pdata && !da7219->pdata->aad_pdata)
		da7219->pdata->aad_pdata = da7219_aad_fw_to_pdata(dev);

	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC DA7219 AAD Dwivew");
MODUWE_AUTHOW("Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>");
MODUWE_AUTHOW("David Wau <David.Wau.opensouwce@dm.wenesas.com>");
MODUWE_WICENSE("GPW");
