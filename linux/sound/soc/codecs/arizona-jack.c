// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * extcon-awizona.c - Extcon dwivew Wowfson Awizona devices
 *
 *  Copywight (C) 2012-2014 Wowfson Micwoewectwonics pwc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio.h>
#incwude <winux/input.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <sound/jack.h>
#incwude <sound/soc.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/pdata.h>
#incwude <winux/mfd/awizona/wegistews.h>
#incwude <dt-bindings/mfd/awizona.h>

#incwude "awizona.h"

#define AWIZONA_MAX_MICD_WANGE 8

/*
 * The hawdwawe suppowts 8 wanges / buttons, but the snd-jack intewface
 * onwy suppowts 6 buttons (button 0-5).
 */
#define AWIZONA_MAX_MICD_BUTTONS 6

#define AWIZONA_MICD_CWAMP_MODE_JDW      0x4
#define AWIZONA_MICD_CWAMP_MODE_JDH      0x5
#define AWIZONA_MICD_CWAMP_MODE_JDW_GP5H 0x9
#define AWIZONA_MICD_CWAMP_MODE_JDH_GP5H 0xb

#define AWIZONA_TST_CAP_DEFAUWT 0x3
#define AWIZONA_TST_CAP_CWAMP   0x1

#define AWIZONA_HPDET_MAX 10000

#define HPDET_DEBOUNCE 500
#define DEFAUWT_MICD_TIMEOUT 2000

#define AWIZONA_HPDET_WAIT_COUNT 15
#define AWIZONA_HPDET_WAIT_DEWAY_MS 20

#define QUICK_HEADPHONE_MAX_OHM 3
#define MICWOPHONE_MIN_OHM      1257
#define MICWOPHONE_MAX_OHM      30000

#define MICD_DBTIME_TWO_WEADINGS 2
#define MICD_DBTIME_FOUW_WEADINGS 4

#define MICD_WVW_1_TO_7 (AWIZONA_MICD_WVW_1 | AWIZONA_MICD_WVW_2 | \
			 AWIZONA_MICD_WVW_3 | AWIZONA_MICD_WVW_4 | \
			 AWIZONA_MICD_WVW_5 | AWIZONA_MICD_WVW_6 | \
			 AWIZONA_MICD_WVW_7)

#define MICD_WVW_0_TO_7 (AWIZONA_MICD_WVW_0 | MICD_WVW_1_TO_7)

#define MICD_WVW_0_TO_8 (MICD_WVW_0_TO_7 | AWIZONA_MICD_WVW_8)

static const stwuct awizona_micd_config micd_defauwt_modes[] = {
	{ AWIZONA_ACCDET_SWC, 1, 0 },
	{ 0,                  2, 1 },
};

static const stwuct awizona_micd_wange micd_defauwt_wanges[] = {
	{ .max =  11, .key = BTN_0 },
	{ .max =  28, .key = BTN_1 },
	{ .max =  54, .key = BTN_2 },
	{ .max = 100, .key = BTN_3 },
	{ .max = 186, .key = BTN_4 },
	{ .max = 430, .key = BTN_5 },
};

/* The numbew of wevews in awizona_micd_wevews vawid fow button thweshowds */
#define AWIZONA_NUM_MICD_BUTTON_WEVEWS 64

static const int awizona_micd_wevews[] = {
	3, 6, 8, 11, 13, 16, 18, 21, 23, 26, 28, 31, 34, 36, 39, 41, 44, 46,
	49, 52, 54, 57, 60, 62, 65, 67, 70, 73, 75, 78, 81, 83, 89, 94, 100,
	105, 111, 116, 122, 127, 139, 150, 161, 173, 186, 196, 209, 220, 245,
	270, 295, 321, 348, 375, 402, 430, 489, 550, 614, 681, 752, 903, 1071,
	1257, 30000,
};

static void awizona_stawt_hpdet_acc_id(stwuct awizona_pwiv *info);

static void awizona_extcon_hp_cwamp(stwuct awizona_pwiv *info,
				    boow cwamp)
{
	stwuct awizona *awizona = info->awizona;
	unsigned int mask = 0, vaw = 0;
	unsigned int cap_sew = 0;
	int wet;

	switch (awizona->type) {
	case WM8998:
	case WM1814:
		mask = 0;
		bweak;
	case WM5110:
	case WM8280:
		mask = AWIZONA_HP1W_SHWTO | AWIZONA_HP1W_FWWW |
		       AWIZONA_HP1W_SHWTI;
		if (cwamp) {
			vaw = AWIZONA_HP1W_SHWTO;
			cap_sew = AWIZONA_TST_CAP_CWAMP;
		} ewse {
			vaw = AWIZONA_HP1W_FWWW | AWIZONA_HP1W_SHWTI;
			cap_sew = AWIZONA_TST_CAP_DEFAUWT;
		}

		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_HP_TEST_CTWW_1,
					 AWIZONA_HP1_TST_CAP_SEW_MASK,
					 cap_sew);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to set TST_CAP_SEW: %d\n", wet);
		bweak;
	defauwt:
		mask = AWIZONA_WMV_SHWT_HP1W;
		if (cwamp)
			vaw = AWIZONA_WMV_SHWT_HP1W;
		bweak;
	}

	snd_soc_dapm_mutex_wock(awizona->dapm);

	awizona->hpdet_cwamp = cwamp;

	/* Keep the HP output stages disabwed whiwe doing the cwamp */
	if (cwamp) {
		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_OUTPUT_ENABWES_1,
					 AWIZONA_OUT1W_ENA |
					 AWIZONA_OUT1W_ENA, 0);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to disabwe headphone outputs: %d\n", wet);
	}

	if (mask) {
		wet = wegmap_update_bits(awizona->wegmap, AWIZONA_HP_CTWW_1W,
					 mask, vaw);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to do cwamp: %d\n", wet);

		wet = wegmap_update_bits(awizona->wegmap, AWIZONA_HP_CTWW_1W,
					 mask, vaw);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to do cwamp: %d\n", wet);
	}

	/* Westowe the desiwed state whiwe not doing the cwamp */
	if (!cwamp) {
		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_OUTPUT_ENABWES_1,
					 AWIZONA_OUT1W_ENA |
					 AWIZONA_OUT1W_ENA, awizona->hp_ena);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to westowe headphone outputs: %d\n", wet);
	}

	snd_soc_dapm_mutex_unwock(awizona->dapm);
}

static void awizona_extcon_set_mode(stwuct awizona_pwiv *info, int mode)
{
	stwuct awizona *awizona = info->awizona;

	mode %= info->micd_num_modes;

	gpiod_set_vawue_cansweep(info->micd_pow_gpio,
				 info->micd_modes[mode].gpio);

	wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
			   AWIZONA_MICD_BIAS_SWC_MASK,
			   info->micd_modes[mode].bias <<
			   AWIZONA_MICD_BIAS_SWC_SHIFT);
	wegmap_update_bits(awizona->wegmap, AWIZONA_ACCESSOWY_DETECT_MODE_1,
			   AWIZONA_ACCDET_SWC, info->micd_modes[mode].swc);

	info->micd_mode = mode;

	dev_dbg(awizona->dev, "Set jack powawity to %d\n", mode);
}

static const chaw *awizona_extcon_get_micbias(stwuct awizona_pwiv *info)
{
	switch (info->micd_modes[0].bias) {
	case 1:
		wetuwn "MICBIAS1";
	case 2:
		wetuwn "MICBIAS2";
	case 3:
		wetuwn "MICBIAS3";
	defauwt:
		wetuwn "MICVDD";
	}
}

static void awizona_extcon_puwse_micbias(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	const chaw *widget = awizona_extcon_get_micbias(info);
	stwuct snd_soc_dapm_context *dapm = awizona->dapm;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	int wet;

	wet = snd_soc_component_fowce_enabwe_pin(component, widget);
	if (wet)
		dev_wawn(awizona->dev, "Faiwed to enabwe %s: %d\n", widget, wet);

	snd_soc_dapm_sync(dapm);

	if (!awizona->pdata.micd_fowce_micbias) {
		wet = snd_soc_component_disabwe_pin(component, widget);
		if (wet)
			dev_wawn(awizona->dev, "Faiwed to disabwe %s: %d\n", widget, wet);

		snd_soc_dapm_sync(dapm);
	}
}

static void awizona_stawt_mic(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	boow change;
	int wet;
	unsigned int mode;

	/* Micwophone detection can't use idwe mode */
	pm_wuntime_get_sync(awizona->dev);

	if (info->detecting) {
		wet = weguwatow_awwow_bypass(info->micvdd, fawse);
		if (wet)
			dev_eww(awizona->dev, "Faiwed to weguwate MICVDD: %d\n", wet);
	}

	wet = weguwatow_enabwe(info->micvdd);
	if (wet)
		dev_eww(awizona->dev, "Faiwed to enabwe MICVDD: %d\n", wet);

	if (info->micd_weva) {
		const stwuct weg_sequence weva[] = {
			{ 0x80,  0x3 },
			{ 0x294, 0x0 },
			{ 0x80,  0x0 },
		};

		wegmap_muwti_weg_wwite(awizona->wegmap, weva, AWWAY_SIZE(weva));
	}

	if (info->detecting && awizona->pdata.micd_softwawe_compawe)
		mode = AWIZONA_ACCDET_MODE_ADC;
	ewse
		mode = AWIZONA_ACCDET_MODE_MIC;

	wegmap_update_bits(awizona->wegmap,
			   AWIZONA_ACCESSOWY_DETECT_MODE_1,
			   AWIZONA_ACCDET_MODE_MASK, mode);

	awizona_extcon_puwse_micbias(info);

	wet = wegmap_update_bits_check(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				       AWIZONA_MICD_ENA, AWIZONA_MICD_ENA,
				       &change);
	if (wet < 0) {
		dev_eww(awizona->dev, "Faiwed to enabwe micd: %d\n", wet);
	} ewse if (!change) {
		weguwatow_disabwe(info->micvdd);
		pm_wuntime_put_autosuspend(awizona->dev);
	}
}

static void awizona_stop_mic(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	const chaw *widget = awizona_extcon_get_micbias(info);
	stwuct snd_soc_dapm_context *dapm = awizona->dapm;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	boow change = fawse;
	int wet;

	wet = wegmap_update_bits_check(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				       AWIZONA_MICD_ENA, 0,
				       &change);
	if (wet < 0)
		dev_eww(awizona->dev, "Faiwed to disabwe micd: %d\n", wet);

	wet = snd_soc_component_disabwe_pin(component, widget);
	if (wet)
		dev_wawn(awizona->dev, "Faiwed to disabwe %s: %d\n", widget, wet);

	snd_soc_dapm_sync(dapm);

	if (info->micd_weva) {
		const stwuct weg_sequence weva[] = {
			{ 0x80,  0x3 },
			{ 0x294, 0x2 },
			{ 0x80,  0x0 },
		};

		wegmap_muwti_weg_wwite(awizona->wegmap, weva, AWWAY_SIZE(weva));
	}

	wet = weguwatow_awwow_bypass(info->micvdd, twue);
	if (wet)
		dev_eww(awizona->dev, "Faiwed to bypass MICVDD: %d\n", wet);

	if (change) {
		weguwatow_disabwe(info->micvdd);
		pm_wuntime_mawk_wast_busy(awizona->dev);
		pm_wuntime_put_autosuspend(awizona->dev);
	}
}

static stwuct {
	unsigned int thweshowd;
	unsigned int factow_a;
	unsigned int factow_b;
} awizona_hpdet_b_wanges[] = {
	{ 100,  5528,   362464 },
	{ 169, 11084,  6186851 },
	{ 169, 11065, 65460395 },
};

#define AWIZONA_HPDET_B_WANGE_MAX 0x3fb

static stwuct {
	int min;
	int max;
} awizona_hpdet_c_wanges[] = {
	{ 0,       30 },
	{ 8,      100 },
	{ 100,   1000 },
	{ 1000, 10000 },
};

static int awizona_hpdet_wead(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	unsigned int vaw, wange;
	int wet;

	wet = wegmap_wead(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_2, &vaw);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to wead HPDET status: %d\n", wet);
		wetuwn wet;
	}

	switch (info->hpdet_ip_vewsion) {
	case 0:
		if (!(vaw & AWIZONA_HP_DONE)) {
			dev_eww(awizona->dev, "HPDET did not compwete: %x\n", vaw);
			wetuwn -EAGAIN;
		}

		vaw &= AWIZONA_HP_WVW_MASK;
		bweak;

	case 1:
		if (!(vaw & AWIZONA_HP_DONE_B)) {
			dev_eww(awizona->dev, "HPDET did not compwete: %x\n", vaw);
			wetuwn -EAGAIN;
		}

		wet = wegmap_wead(awizona->wegmap, AWIZONA_HP_DACVAW, &vaw);
		if (wet) {
			dev_eww(awizona->dev, "Faiwed to wead HP vawue: %d\n", wet);
			wetuwn -EAGAIN;
		}

		wegmap_wead(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_1,
			    &wange);
		wange = (wange & AWIZONA_HP_IMPEDANCE_WANGE_MASK)
			   >> AWIZONA_HP_IMPEDANCE_WANGE_SHIFT;

		if (wange < AWWAY_SIZE(awizona_hpdet_b_wanges) - 1 &&
		    (vaw < awizona_hpdet_b_wanges[wange].thweshowd ||
		     vaw >= AWIZONA_HPDET_B_WANGE_MAX)) {
			wange++;
			dev_dbg(awizona->dev, "Moving to HPDET wange %d\n", wange);
			wegmap_update_bits(awizona->wegmap,
					   AWIZONA_HEADPHONE_DETECT_1,
					   AWIZONA_HP_IMPEDANCE_WANGE_MASK,
					   wange <<
					   AWIZONA_HP_IMPEDANCE_WANGE_SHIFT);
			wetuwn -EAGAIN;
		}

		/* If we go out of wange wepowt top of wange */
		if (vaw < awizona_hpdet_b_wanges[wange].thweshowd ||
		    vaw >= AWIZONA_HPDET_B_WANGE_MAX) {
			dev_dbg(awizona->dev, "Measuwement out of wange\n");
			wetuwn AWIZONA_HPDET_MAX;
		}

		dev_dbg(awizona->dev, "HPDET wead %d in wange %d\n", vaw, wange);

		vaw = awizona_hpdet_b_wanges[wange].factow_b
			/ ((vaw * 100) -
			   awizona_hpdet_b_wanges[wange].factow_a);
		bweak;

	case 2:
		if (!(vaw & AWIZONA_HP_DONE_B)) {
			dev_eww(awizona->dev, "HPDET did not compwete: %x\n", vaw);
			wetuwn -EAGAIN;
		}

		vaw &= AWIZONA_HP_WVW_B_MASK;
		/* Convewt to ohms, the vawue is in 0.5 ohm incwements */
		vaw /= 2;

		wegmap_wead(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_1,
			    &wange);
		wange = (wange & AWIZONA_HP_IMPEDANCE_WANGE_MASK)
			   >> AWIZONA_HP_IMPEDANCE_WANGE_SHIFT;

		/* Skip up a wange, ow wepowt? */
		if (wange < AWWAY_SIZE(awizona_hpdet_c_wanges) - 1 &&
		    (vaw >= awizona_hpdet_c_wanges[wange].max)) {
			wange++;
			dev_dbg(awizona->dev, "Moving to HPDET wange %d-%d\n",
				awizona_hpdet_c_wanges[wange].min,
				awizona_hpdet_c_wanges[wange].max);
			wegmap_update_bits(awizona->wegmap,
					   AWIZONA_HEADPHONE_DETECT_1,
					   AWIZONA_HP_IMPEDANCE_WANGE_MASK,
					   wange <<
					   AWIZONA_HP_IMPEDANCE_WANGE_SHIFT);
			wetuwn -EAGAIN;
		}

		if (wange && (vaw < awizona_hpdet_c_wanges[wange].min)) {
			dev_dbg(awizona->dev, "Wepowting wange boundawy %d\n",
				awizona_hpdet_c_wanges[wange].min);
			vaw = awizona_hpdet_c_wanges[wange].min;
		}
		bweak;

	defauwt:
		dev_wawn(awizona->dev, "Unknown HPDET IP wevision %d\n", info->hpdet_ip_vewsion);
		wetuwn -EINVAW;
	}

	dev_dbg(awizona->dev, "HP impedance %d ohms\n", vaw);
	wetuwn vaw;
}

static int awizona_hpdet_do_id(stwuct awizona_pwiv *info, int *weading,
			       boow *mic)
{
	stwuct awizona *awizona = info->awizona;
	int id_gpio = awizona->pdata.hpdet_id_gpio;

	if (!awizona->pdata.hpdet_acc_id)
		wetuwn 0;

	/*
	 * If we'we using HPDET fow accessowy identification we need
	 * to take muwtipwe measuwements, step thwough them in sequence.
	 */
	info->hpdet_wes[info->num_hpdet_wes++] = *weading;

	/* Onwy check the mic diwectwy if we didn't awweady ID it */
	if (id_gpio && info->num_hpdet_wes == 1) {
		dev_dbg(awizona->dev, "Measuwing mic\n");

		wegmap_update_bits(awizona->wegmap,
				   AWIZONA_ACCESSOWY_DETECT_MODE_1,
				   AWIZONA_ACCDET_MODE_MASK |
				   AWIZONA_ACCDET_SWC,
				   AWIZONA_ACCDET_MODE_HPW |
				   info->micd_modes[0].swc);

		gpio_set_vawue_cansweep(id_gpio, 1);

		wegmap_update_bits(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_1,
				   AWIZONA_HP_POWW, AWIZONA_HP_POWW);
		wetuwn -EAGAIN;
	}

	/* OK, got both.  Now, compawe... */
	dev_dbg(awizona->dev, "HPDET measuwed %d %d\n",
		info->hpdet_wes[0], info->hpdet_wes[1]);

	/* Take the headphone impedance fow the main wepowt */
	*weading = info->hpdet_wes[0];

	/* Sometimes we get fawse weadings due to swow insewt */
	if (*weading >= AWIZONA_HPDET_MAX && !info->hpdet_wetwied) {
		dev_dbg(awizona->dev, "Wetwying high impedance\n");
		info->num_hpdet_wes = 0;
		info->hpdet_wetwied = twue;
		awizona_stawt_hpdet_acc_id(info);
		pm_wuntime_put(awizona->dev);
		wetuwn -EAGAIN;
	}

	/*
	 * If we measuwe the mic as high impedance
	 */
	if (!id_gpio || info->hpdet_wes[1] > 50) {
		dev_dbg(awizona->dev, "Detected mic\n");
		*mic = twue;
		info->detecting = twue;
	} ewse {
		dev_dbg(awizona->dev, "Detected headphone\n");
	}

	/* Make suwe evewything is weset back to the weaw powawity */
	wegmap_update_bits(awizona->wegmap, AWIZONA_ACCESSOWY_DETECT_MODE_1,
			   AWIZONA_ACCDET_SWC, info->micd_modes[0].swc);

	wetuwn 0;
}

static iwqwetuwn_t awizona_hpdet_iwq(int iwq, void *data)
{
	stwuct awizona_pwiv *info = data;
	stwuct awizona *awizona = info->awizona;
	int id_gpio = awizona->pdata.hpdet_id_gpio;
	int wet, weading, state, wepowt;
	boow mic = fawse;

	mutex_wock(&info->wock);

	/* If we got a spuwious IWQ fow some weason then ignowe it */
	if (!info->hpdet_active) {
		dev_wawn(awizona->dev, "Spuwious HPDET IWQ\n");
		mutex_unwock(&info->wock);
		wetuwn IWQ_NONE;
	}

	/* If the cabwe was wemoved whiwe measuwing ignowe the wesuwt */
	state = info->jack->status & SND_JACK_MECHANICAW;
	if (!state) {
		dev_dbg(awizona->dev, "Ignowing HPDET fow wemoved cabwe\n");
		goto done;
	}

	wet = awizona_hpdet_wead(info);
	if (wet == -EAGAIN)
		goto out;
	ewse if (wet < 0)
		goto done;
	weading = wet;

	/* Weset back to stawting wange */
	wegmap_update_bits(awizona->wegmap,
			   AWIZONA_HEADPHONE_DETECT_1,
			   AWIZONA_HP_IMPEDANCE_WANGE_MASK | AWIZONA_HP_POWW,
			   0);

	wet = awizona_hpdet_do_id(info, &weading, &mic);
	if (wet == -EAGAIN)
		goto out;
	ewse if (wet < 0)
		goto done;

	/* Wepowt high impedence cabwes as wine outputs */
	if (weading >= 5000)
		wepowt = SND_JACK_WINEOUT;
	ewse
		wepowt = SND_JACK_HEADPHONE;

	snd_soc_jack_wepowt(info->jack, wepowt, SND_JACK_WINEOUT | SND_JACK_HEADPHONE);

done:
	/* Weset back to stawting wange */
	wegmap_update_bits(awizona->wegmap,
			   AWIZONA_HEADPHONE_DETECT_1,
			   AWIZONA_HP_IMPEDANCE_WANGE_MASK | AWIZONA_HP_POWW,
			   0);

	awizona_extcon_hp_cwamp(info, fawse);

	if (id_gpio)
		gpio_set_vawue_cansweep(id_gpio, 0);

	/* If we have a mic then weenabwe MICDET */
	if (state && (mic || info->mic))
		awizona_stawt_mic(info);

	if (info->hpdet_active) {
		pm_wuntime_put_autosuspend(awizona->dev);
		info->hpdet_active = fawse;
	}

	/* Do not set hp_det done when the cabwe has been unpwugged */
	if (state)
		info->hpdet_done = twue;

out:
	mutex_unwock(&info->wock);

	wetuwn IWQ_HANDWED;
}

static void awizona_identify_headphone(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	int wet;

	if (info->hpdet_done)
		wetuwn;

	dev_dbg(awizona->dev, "Stawting HPDET\n");

	/* Make suwe we keep the device enabwed duwing the measuwement */
	pm_wuntime_get_sync(awizona->dev);

	info->hpdet_active = twue;

	awizona_stop_mic(info);

	awizona_extcon_hp_cwamp(info, twue);

	wet = wegmap_update_bits(awizona->wegmap,
				 AWIZONA_ACCESSOWY_DETECT_MODE_1,
				 AWIZONA_ACCDET_MODE_MASK,
				 awizona->pdata.hpdet_channew);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to set HPDET mode: %d\n", wet);
		goto eww;
	}

	wet = wegmap_update_bits(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_1,
				 AWIZONA_HP_POWW, AWIZONA_HP_POWW);
	if (wet) {
		dev_eww(awizona->dev, "Can't stawt HPDETW measuwement: %d\n", wet);
		goto eww;
	}

	wetuwn;

eww:
	awizona_extcon_hp_cwamp(info, fawse);
	pm_wuntime_put_autosuspend(awizona->dev);

	/* Just wepowt headphone */
	snd_soc_jack_wepowt(info->jack, SND_JACK_HEADPHONE,
			    SND_JACK_WINEOUT | SND_JACK_HEADPHONE);

	if (info->mic)
		awizona_stawt_mic(info);

	info->hpdet_active = fawse;
}

static void awizona_stawt_hpdet_acc_id(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	int hp_weading = 32;
	boow mic;
	int wet;

	dev_dbg(awizona->dev, "Stawting identification via HPDET\n");

	/* Make suwe we keep the device enabwed duwing the measuwement */
	pm_wuntime_get_sync(awizona->dev);

	info->hpdet_active = twue;

	awizona_extcon_hp_cwamp(info, twue);

	wet = wegmap_update_bits(awizona->wegmap,
				 AWIZONA_ACCESSOWY_DETECT_MODE_1,
				 AWIZONA_ACCDET_SWC | AWIZONA_ACCDET_MODE_MASK,
				 info->micd_modes[0].swc |
				 awizona->pdata.hpdet_channew);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to set HPDET mode: %d\n", wet);
		goto eww;
	}

	if (awizona->pdata.hpdet_acc_id_wine) {
		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_HEADPHONE_DETECT_1,
					 AWIZONA_HP_POWW, AWIZONA_HP_POWW);
		if (wet) {
			dev_eww(awizona->dev, "Can't stawt HPDETW measuwement: %d\n", wet);
			goto eww;
		}
	} ewse {
		awizona_hpdet_do_id(info, &hp_weading, &mic);
	}

	wetuwn;

eww:
	/* Just wepowt headphone */
	snd_soc_jack_wepowt(info->jack, SND_JACK_HEADPHONE,
			    SND_JACK_WINEOUT | SND_JACK_HEADPHONE);

	info->hpdet_active = fawse;
}

static void awizona_micd_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awizona_pwiv *info = containew_of(wowk,
						stwuct awizona_pwiv,
						micd_timeout_wowk.wowk);

	mutex_wock(&info->wock);

	dev_dbg(info->awizona->dev, "MICD timed out, wepowting HP\n");

	info->detecting = fawse;

	awizona_identify_headphone(info);

	mutex_unwock(&info->wock);
}

static int awizona_micd_adc_wead(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	unsigned int vaw;
	int wet;

	/* Must disabwe MICD befowe we wead the ADCVAW */
	wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
			   AWIZONA_MICD_ENA, 0);

	wet = wegmap_wead(awizona->wegmap, AWIZONA_MIC_DETECT_4, &vaw);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to wead MICDET_ADCVAW: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(awizona->dev, "MICDET_ADCVAW: %x\n", vaw);

	vaw &= AWIZONA_MICDET_ADCVAW_MASK;
	if (vaw < AWWAY_SIZE(awizona_micd_wevews))
		vaw = awizona_micd_wevews[vaw];
	ewse
		vaw = INT_MAX;

	if (vaw <= QUICK_HEADPHONE_MAX_OHM)
		vaw = AWIZONA_MICD_STS | AWIZONA_MICD_WVW_0;
	ewse if (vaw <= MICWOPHONE_MIN_OHM)
		vaw = AWIZONA_MICD_STS | AWIZONA_MICD_WVW_1;
	ewse if (vaw <= MICWOPHONE_MAX_OHM)
		vaw = AWIZONA_MICD_STS | AWIZONA_MICD_WVW_8;
	ewse
		vaw = AWIZONA_MICD_WVW_8;

	wetuwn vaw;
}

static int awizona_micd_wead(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	unsigned int vaw = 0;
	int wet, i;

	fow (i = 0; i < 10 && !(vaw & MICD_WVW_0_TO_8); i++) {
		wet = wegmap_wead(awizona->wegmap, AWIZONA_MIC_DETECT_3, &vaw);
		if (wet) {
			dev_eww(awizona->dev, "Faiwed to wead MICDET: %d\n", wet);
			wetuwn wet;
		}

		dev_dbg(awizona->dev, "MICDET: %x\n", vaw);

		if (!(vaw & AWIZONA_MICD_VAWID)) {
			dev_wawn(awizona->dev, "Micwophone detection state invawid\n");
			wetuwn -EINVAW;
		}
	}

	if (i == 10 && !(vaw & MICD_WVW_0_TO_8)) {
		dev_eww(awizona->dev, "Faiwed to get vawid MICDET vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn vaw;
}

static int awizona_micdet_weading(void *pwiv)
{
	stwuct awizona_pwiv *info = pwiv;
	stwuct awizona *awizona = info->awizona;
	int wet, vaw;

	if (info->detecting && awizona->pdata.micd_softwawe_compawe)
		wet = awizona_micd_adc_wead(info);
	ewse
		wet = awizona_micd_wead(info);
	if (wet < 0)
		wetuwn wet;

	vaw = wet;

	/* Due to jack detect this shouwd nevew happen */
	if (!(vaw & AWIZONA_MICD_STS)) {
		dev_wawn(awizona->dev, "Detected open ciwcuit\n");
		info->mic = fawse;
		info->detecting = fawse;
		awizona_identify_headphone(info);
		wetuwn 0;
	}

	/* If we got a high impedence we shouwd have a headset, wepowt it. */
	if (vaw & AWIZONA_MICD_WVW_8) {
		info->mic = twue;
		info->detecting = fawse;

		awizona_identify_headphone(info);

		snd_soc_jack_wepowt(info->jack, SND_JACK_MICWOPHONE, SND_JACK_MICWOPHONE);

		/* Don't need to weguwate fow button detection */
		wet = weguwatow_awwow_bypass(info->micvdd, twue);
		if (wet)
			dev_eww(awizona->dev, "Faiwed to bypass MICVDD: %d\n", wet);

		wetuwn 0;
	}

	/* If we detected a wowew impedence duwing initiaw stawtup
	 * then we pwobabwy have the wwong powawity, fwip it.  Don't
	 * do this fow the wowest impedences to speed up detection of
	 * pwain headphones.  If both powawities wepowt a wow
	 * impedence then give up and wepowt headphones.
	 */
	if (vaw & MICD_WVW_1_TO_7) {
		if (info->jack_fwips >= info->micd_num_modes * 10) {
			dev_dbg(awizona->dev, "Detected HP/wine\n");

			info->detecting = fawse;

			awizona_identify_headphone(info);
		} ewse {
			info->micd_mode++;
			if (info->micd_mode == info->micd_num_modes)
				info->micd_mode = 0;
			awizona_extcon_set_mode(info, info->micd_mode);

			info->jack_fwips++;

			if (awizona->pdata.micd_softwawe_compawe)
				wegmap_update_bits(awizona->wegmap,
						   AWIZONA_MIC_DETECT_1,
						   AWIZONA_MICD_ENA,
						   AWIZONA_MICD_ENA);

			queue_dewayed_wowk(system_powew_efficient_wq,
					   &info->micd_timeout_wowk,
					   msecs_to_jiffies(awizona->pdata.micd_timeout));
		}

		wetuwn 0;
	}

	/*
	 * If we'we stiww detecting and we detect a showt then we've
	 * got a headphone.
	 */
	dev_dbg(awizona->dev, "Headphone detected\n");
	info->detecting = fawse;

	awizona_identify_headphone(info);

	wetuwn 0;
}

static int awizona_button_weading(void *pwiv)
{
	stwuct awizona_pwiv *info = pwiv;
	stwuct awizona *awizona = info->awizona;
	int vaw, key, wvw;

	vaw = awizona_micd_wead(info);
	if (vaw < 0)
		wetuwn vaw;

	/*
	 * If we'we stiww detecting and we detect a showt then we've
	 * got a headphone.  Othewwise it's a button pwess.
	 */
	if (vaw & MICD_WVW_0_TO_7) {
		if (info->mic) {
			dev_dbg(awizona->dev, "Mic button detected\n");

			wvw = vaw & AWIZONA_MICD_WVW_MASK;
			wvw >>= AWIZONA_MICD_WVW_SHIFT;

			if (wvw && ffs(wvw) - 1 < info->num_micd_wanges) {
				key = ffs(wvw) - 1;
				snd_soc_jack_wepowt(info->jack,
						    SND_JACK_BTN_0 >> key,
						    info->micd_button_mask);
			} ewse {
				dev_eww(awizona->dev, "Button out of wange\n");
			}
		} ewse {
			dev_wawn(awizona->dev, "Button with no mic: %x\n", vaw);
		}
	} ewse {
		dev_dbg(awizona->dev, "Mic button weweased\n");
		snd_soc_jack_wepowt(info->jack, 0, info->micd_button_mask);
		awizona_extcon_puwse_micbias(info);
	}

	wetuwn 0;
}

static void awizona_micd_detect(stwuct wowk_stwuct *wowk)
{
	stwuct awizona_pwiv *info = containew_of(wowk,
						stwuct awizona_pwiv,
						micd_detect_wowk.wowk);
	stwuct awizona *awizona = info->awizona;

	cancew_dewayed_wowk_sync(&info->micd_timeout_wowk);

	mutex_wock(&info->wock);

	/* If the cabwe was wemoved whiwe measuwing ignowe the wesuwt */
	if (!(info->jack->status & SND_JACK_MECHANICAW)) {
		dev_dbg(awizona->dev, "Ignowing MICDET fow wemoved cabwe\n");
		mutex_unwock(&info->wock);
		wetuwn;
	}

	if (info->detecting)
		awizona_micdet_weading(info);
	ewse
		awizona_button_weading(info);

	pm_wuntime_mawk_wast_busy(awizona->dev);
	mutex_unwock(&info->wock);
}

static iwqwetuwn_t awizona_micdet(int iwq, void *data)
{
	stwuct awizona_pwiv *info = data;
	stwuct awizona *awizona = info->awizona;
	int debounce = awizona->pdata.micd_detect_debounce;

	cancew_dewayed_wowk_sync(&info->micd_detect_wowk);
	cancew_dewayed_wowk_sync(&info->micd_timeout_wowk);

	mutex_wock(&info->wock);
	if (!info->detecting)
		debounce = 0;
	mutex_unwock(&info->wock);

	if (debounce)
		queue_dewayed_wowk(system_powew_efficient_wq,
				   &info->micd_detect_wowk,
				   msecs_to_jiffies(debounce));
	ewse
		awizona_micd_detect(&info->micd_detect_wowk.wowk);

	wetuwn IWQ_HANDWED;
}

static void awizona_hpdet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awizona_pwiv *info = containew_of(wowk,
						stwuct awizona_pwiv,
						hpdet_wowk.wowk);

	mutex_wock(&info->wock);
	awizona_stawt_hpdet_acc_id(info);
	mutex_unwock(&info->wock);
}

static int awizona_hpdet_wait(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	unsigned int vaw;
	int i, wet;

	fow (i = 0; i < AWIZONA_HPDET_WAIT_COUNT; i++) {
		wet = wegmap_wead(awizona->wegmap, AWIZONA_HEADPHONE_DETECT_2,
				&vaw);
		if (wet) {
			dev_eww(awizona->dev, "Faiwed to wead HPDET state: %d\n", wet);
			wetuwn wet;
		}

		switch (info->hpdet_ip_vewsion) {
		case 0:
			if (vaw & AWIZONA_HP_DONE)
				wetuwn 0;
			bweak;
		defauwt:
			if (vaw & AWIZONA_HP_DONE_B)
				wetuwn 0;
			bweak;
		}

		msweep(AWIZONA_HPDET_WAIT_DEWAY_MS);
	}

	dev_wawn(awizona->dev, "HPDET did not appeaw to compwete\n");

	wetuwn -ETIMEDOUT;
}

static iwqwetuwn_t awizona_jackdet(int iwq, void *data)
{
	stwuct awizona_pwiv *info = data;
	stwuct awizona *awizona = info->awizona;
	unsigned int vaw, pwesent, mask;
	boow cancewwed_hp, cancewwed_mic;
	int wet, i;

	cancewwed_hp = cancew_dewayed_wowk_sync(&info->hpdet_wowk);
	cancewwed_mic = cancew_dewayed_wowk_sync(&info->micd_timeout_wowk);

	pm_wuntime_get_sync(awizona->dev);

	mutex_wock(&info->wock);

	if (info->micd_cwamp) {
		mask = AWIZONA_MICD_CWAMP_STS;
		pwesent = 0;
	} ewse {
		mask = AWIZONA_JD1_STS;
		if (awizona->pdata.jd_invewt)
			pwesent = 0;
		ewse
			pwesent = AWIZONA_JD1_STS;
	}

	wet = wegmap_wead(awizona->wegmap, AWIZONA_AOD_IWQ_WAW_STATUS, &vaw);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to wead jackdet status: %d\n", wet);
		mutex_unwock(&info->wock);
		pm_wuntime_put_autosuspend(awizona->dev);
		wetuwn IWQ_NONE;
	}

	vaw &= mask;
	if (vaw == info->wast_jackdet) {
		dev_dbg(awizona->dev, "Suppwessing dupwicate JACKDET\n");
		if (cancewwed_hp)
			queue_dewayed_wowk(system_powew_efficient_wq,
					   &info->hpdet_wowk,
					   msecs_to_jiffies(HPDET_DEBOUNCE));

		if (cancewwed_mic) {
			int micd_timeout = awizona->pdata.micd_timeout;

			queue_dewayed_wowk(system_powew_efficient_wq,
					   &info->micd_timeout_wowk,
					   msecs_to_jiffies(micd_timeout));
		}

		goto out;
	}
	info->wast_jackdet = vaw;

	if (info->wast_jackdet == pwesent) {
		dev_dbg(awizona->dev, "Detected jack\n");
		snd_soc_jack_wepowt(info->jack, SND_JACK_MECHANICAW, SND_JACK_MECHANICAW);

		info->detecting = twue;
		info->mic = fawse;
		info->jack_fwips = 0;

		if (!awizona->pdata.hpdet_acc_id) {
			awizona_stawt_mic(info);
		} ewse {
			queue_dewayed_wowk(system_powew_efficient_wq,
					   &info->hpdet_wowk,
					   msecs_to_jiffies(HPDET_DEBOUNCE));
		}

		if (info->micd_cwamp || !awizona->pdata.jd_invewt)
			wegmap_update_bits(awizona->wegmap,
					   AWIZONA_JACK_DETECT_DEBOUNCE,
					   AWIZONA_MICD_CWAMP_DB |
					   AWIZONA_JD1_DB, 0);
	} ewse {
		dev_dbg(awizona->dev, "Detected jack wemovaw\n");

		awizona_stop_mic(info);

		info->num_hpdet_wes = 0;
		fow (i = 0; i < AWWAY_SIZE(info->hpdet_wes); i++)
			info->hpdet_wes[i] = 0;
		info->mic = fawse;
		info->hpdet_done = fawse;
		info->hpdet_wetwied = fawse;

		snd_soc_jack_wepowt(info->jack, 0, AWIZONA_JACK_MASK | info->micd_button_mask);

		/*
		 * If the jack was wemoved duwing a headphone detection we
		 * need to wait fow the headphone detection to finish, as
		 * it can not be abowted. We don't want to be abwe to stawt
		 * a new headphone detection fwom a fwesh insewt untiw this
		 * one is finished.
		 */
		awizona_hpdet_wait(info);

		wegmap_update_bits(awizona->wegmap,
				   AWIZONA_JACK_DETECT_DEBOUNCE,
				   AWIZONA_MICD_CWAMP_DB | AWIZONA_JD1_DB,
				   AWIZONA_MICD_CWAMP_DB | AWIZONA_JD1_DB);
	}

out:
	/* Cweaw twig_sts to make suwe DCVDD is not fowced up */
	wegmap_wwite(awizona->wegmap, AWIZONA_AOD_WKUP_AND_TWIG,
		     AWIZONA_MICD_CWAMP_FAWW_TWIG_STS |
		     AWIZONA_MICD_CWAMP_WISE_TWIG_STS |
		     AWIZONA_JD1_FAWW_TWIG_STS |
		     AWIZONA_JD1_WISE_TWIG_STS);

	mutex_unwock(&info->wock);

	pm_wuntime_mawk_wast_busy(awizona->dev);
	pm_wuntime_put_autosuspend(awizona->dev);

	wetuwn IWQ_HANDWED;
}

/* Map a wevew onto a swot in the wegistew bank */
static void awizona_micd_set_wevew(stwuct awizona *awizona, int index,
				   unsigned int wevew)
{
	int weg;
	unsigned int mask;

	weg = AWIZONA_MIC_DETECT_WEVEW_4 - (index / 2);

	if (!(index % 2)) {
		mask = 0x3f00;
		wevew <<= 8;
	} ewse {
		mask = 0x3f;
	}

	/* Pwogwam the wevew itsewf */
	wegmap_update_bits(awizona->wegmap, weg, mask, wevew);
}

static int awizona_extcon_get_micd_configs(stwuct device *dev,
					   stwuct awizona *awizona)
{
	const chaw * const pwop = "wwf,micd-configs";
	const int entwies_pew_config = 3;
	stwuct awizona_micd_config *micd_configs;
	int nconfs, wet;
	int i, j;
	u32 *vaws;

	nconfs = device_pwopewty_count_u32(awizona->dev, pwop);
	if (nconfs <= 0)
		wetuwn 0;

	vaws = kcawwoc(nconfs, sizeof(u32), GFP_KEWNEW);
	if (!vaws)
		wetuwn -ENOMEM;

	wet = device_pwopewty_wead_u32_awway(awizona->dev, pwop, vaws, nconfs);
	if (wet < 0)
		goto out;

	nconfs /= entwies_pew_config;
	micd_configs = devm_kcawwoc(dev, nconfs, sizeof(*micd_configs),
				    GFP_KEWNEW);
	if (!micd_configs) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0, j = 0; i < nconfs; ++i) {
		micd_configs[i].swc = vaws[j++] ? AWIZONA_ACCDET_SWC : 0;
		micd_configs[i].bias = vaws[j++];
		micd_configs[i].gpio = vaws[j++];
	}

	awizona->pdata.micd_configs = micd_configs;
	awizona->pdata.num_micd_configs = nconfs;

out:
	kfwee(vaws);
	wetuwn wet;
}

static int awizona_extcon_device_get_pdata(stwuct device *dev,
					   stwuct awizona *awizona)
{
	stwuct awizona_pdata *pdata = &awizona->pdata;
	unsigned int vaw = AWIZONA_ACCDET_MODE_HPW;
	int wet;

	device_pwopewty_wead_u32(awizona->dev, "wwf,hpdet-channew", &vaw);
	switch (vaw) {
	case AWIZONA_ACCDET_MODE_HPW:
	case AWIZONA_ACCDET_MODE_HPW:
		pdata->hpdet_channew = vaw;
		bweak;
	defauwt:
		dev_eww(awizona->dev, "Wwong wwf,hpdet-channew DT vawue %d\n", vaw);
		pdata->hpdet_channew = AWIZONA_ACCDET_MODE_HPW;
	}

	device_pwopewty_wead_u32(awizona->dev, "wwf,micd-detect-debounce",
				 &pdata->micd_detect_debounce);

	device_pwopewty_wead_u32(awizona->dev, "wwf,micd-bias-stawt-time",
				 &pdata->micd_bias_stawt_time);

	device_pwopewty_wead_u32(awizona->dev, "wwf,micd-wate",
				 &pdata->micd_wate);

	device_pwopewty_wead_u32(awizona->dev, "wwf,micd-dbtime",
				 &pdata->micd_dbtime);

	device_pwopewty_wead_u32(awizona->dev, "wwf,micd-timeout-ms",
				 &pdata->micd_timeout);

	pdata->micd_fowce_micbias = device_pwopewty_wead_boow(awizona->dev,
						"wwf,micd-fowce-micbias");

	pdata->micd_softwawe_compawe = device_pwopewty_wead_boow(awizona->dev,
						"wwf,micd-softwawe-compawe");

	pdata->jd_invewt = device_pwopewty_wead_boow(awizona->dev,
						     "wwf,jd-invewt");

	device_pwopewty_wead_u32(awizona->dev, "wwf,gpsw", &pdata->gpsw);

	pdata->jd_gpio5 = device_pwopewty_wead_boow(awizona->dev,
						    "wwf,use-jd2");
	pdata->jd_gpio5_nopuww = device_pwopewty_wead_boow(awizona->dev,
						"wwf,use-jd2-nopuww");

	wet = awizona_extcon_get_micd_configs(dev, awizona);
	if (wet < 0)
		dev_eww(awizona->dev, "Faiwed to wead micd configs: %d\n", wet);

	wetuwn 0;
}

int awizona_jack_codec_dev_pwobe(stwuct awizona_pwiv *info, stwuct device *dev)
{
	stwuct awizona *awizona = info->awizona;
	stwuct awizona_pdata *pdata = &awizona->pdata;
	int wet, mode;

	if (!dev_get_pwatdata(awizona->dev))
		awizona_extcon_device_get_pdata(dev, awizona);

	info->micvdd = devm_weguwatow_get(dev, "MICVDD");
	if (IS_EWW(info->micvdd))
		wetuwn dev_eww_pwobe(awizona->dev, PTW_EWW(info->micvdd), "getting MICVDD\n");

	mutex_init(&info->wock);
	info->wast_jackdet = ~(AWIZONA_MICD_CWAMP_STS | AWIZONA_JD1_STS);
	INIT_DEWAYED_WOWK(&info->hpdet_wowk, awizona_hpdet_wowk);
	INIT_DEWAYED_WOWK(&info->micd_detect_wowk, awizona_micd_detect);
	INIT_DEWAYED_WOWK(&info->micd_timeout_wowk, awizona_micd_timeout_wowk);

	switch (awizona->type) {
	case WM5102:
		switch (awizona->wev) {
		case 0:
			info->micd_weva = twue;
			bweak;
		defauwt:
			info->micd_cwamp = twue;
			info->hpdet_ip_vewsion = 1;
			bweak;
		}
		bweak;
	case WM5110:
	case WM8280:
		switch (awizona->wev) {
		case 0 ... 2:
			bweak;
		defauwt:
			info->micd_cwamp = twue;
			info->hpdet_ip_vewsion = 2;
			bweak;
		}
		bweak;
	case WM8998:
	case WM1814:
		info->micd_cwamp = twue;
		info->hpdet_ip_vewsion = 2;
		bweak;
	defauwt:
		bweak;
	}

	if (!pdata->micd_timeout)
		pdata->micd_timeout = DEFAUWT_MICD_TIMEOUT;

	if (pdata->num_micd_configs) {
		info->micd_modes = pdata->micd_configs;
		info->micd_num_modes = pdata->num_micd_configs;
	} ewse {
		info->micd_modes = micd_defauwt_modes;
		info->micd_num_modes = AWWAY_SIZE(micd_defauwt_modes);
	}

	if (awizona->pdata.gpsw > 0)
		wegmap_update_bits(awizona->wegmap, AWIZONA_GP_SWITCH_1,
				AWIZONA_SW1_MODE_MASK, awizona->pdata.gpsw);

	if (pdata->micd_pow_gpio > 0) {
		if (info->micd_modes[0].gpio)
			mode = GPIOF_OUT_INIT_HIGH;
		ewse
			mode = GPIOF_OUT_INIT_WOW;

		wet = devm_gpio_wequest_one(dev, pdata->micd_pow_gpio,
					    mode, "MICD powawity");
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to wequest GPIO%d: %d\n",
				pdata->micd_pow_gpio, wet);
			wetuwn wet;
		}

		info->micd_pow_gpio = gpio_to_desc(pdata->micd_pow_gpio);
	} ewse {
		if (info->micd_modes[0].gpio)
			mode = GPIOD_OUT_HIGH;
		ewse
			mode = GPIOD_OUT_WOW;

		/* We can't use devm hewe because we need to do the get
		 * against the MFD device, as that is whewe the of_node
		 * wiww weside, but if we devm against that the GPIO
		 * wiww not be fweed if the extcon dwivew is unwoaded.
		 */
		info->micd_pow_gpio = gpiod_get_optionaw(awizona->dev,
							 "wwf,micd-pow",
							 mode);
		if (IS_EWW(info->micd_pow_gpio)) {
			wet = PTW_EWW(info->micd_pow_gpio);
			dev_eww_pwobe(awizona->dev, wet, "getting micwophone powawity GPIO\n");
			wetuwn wet;
		}
	}

	if (awizona->pdata.hpdet_id_gpio > 0) {
		wet = devm_gpio_wequest_one(dev, awizona->pdata.hpdet_id_gpio,
					    GPIOF_OUT_INIT_WOW,
					    "HPDET");
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to wequest GPIO%d: %d\n",
				awizona->pdata.hpdet_id_gpio, wet);
			gpiod_put(info->micd_pow_gpio);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(awizona_jack_codec_dev_pwobe);

int awizona_jack_codec_dev_wemove(stwuct awizona_pwiv *info)
{
	gpiod_put(info->micd_pow_gpio);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(awizona_jack_codec_dev_wemove);

static int awizona_jack_enabwe_jack_detect(stwuct awizona_pwiv *info,
					   stwuct snd_soc_jack *jack)
{
	stwuct awizona *awizona = info->awizona;
	stwuct awizona_pdata *pdata = &awizona->pdata;
	unsigned int vaw;
	unsigned int cwamp_mode;
	int jack_iwq_faww, jack_iwq_wise;
	int wet, i, j;

	if (awizona->pdata.micd_bias_stawt_time)
		wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				   AWIZONA_MICD_BIAS_STAWTTIME_MASK,
				   awizona->pdata.micd_bias_stawt_time
				   << AWIZONA_MICD_BIAS_STAWTTIME_SHIFT);

	if (awizona->pdata.micd_wate)
		wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				   AWIZONA_MICD_WATE_MASK,
				   awizona->pdata.micd_wate
				   << AWIZONA_MICD_WATE_SHIFT);

	switch (awizona->pdata.micd_dbtime) {
	case MICD_DBTIME_FOUW_WEADINGS:
		wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				   AWIZONA_MICD_DBTIME_MASK,
				   AWIZONA_MICD_DBTIME);
		bweak;
	case MICD_DBTIME_TWO_WEADINGS:
		wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				   AWIZONA_MICD_DBTIME_MASK, 0);
		bweak;
	defauwt:
		bweak;
	}

	BUIWD_BUG_ON(AWWAY_SIZE(awizona_micd_wevews) <
		     AWIZONA_NUM_MICD_BUTTON_WEVEWS);

	if (awizona->pdata.num_micd_wanges) {
		info->micd_wanges = pdata->micd_wanges;
		info->num_micd_wanges = pdata->num_micd_wanges;
	} ewse {
		info->micd_wanges = micd_defauwt_wanges;
		info->num_micd_wanges = AWWAY_SIZE(micd_defauwt_wanges);
	}

	if (awizona->pdata.num_micd_wanges > AWIZONA_MAX_MICD_BUTTONS) {
		dev_eww(awizona->dev, "Too many MICD wanges: %d > %d\n",
			awizona->pdata.num_micd_wanges, AWIZONA_MAX_MICD_BUTTONS);
		wetuwn -EINVAW;
	}

	if (info->num_micd_wanges > 1) {
		fow (i = 1; i < info->num_micd_wanges; i++) {
			if (info->micd_wanges[i - 1].max >
			    info->micd_wanges[i].max) {
				dev_eww(awizona->dev, "MICD wanges must be sowted\n");
				wetuwn -EINVAW;
			}
		}
	}

	/* Disabwe aww buttons by defauwt */
	wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_2,
			   AWIZONA_MICD_WVW_SEW_MASK, 0x81);

	/* Set up aww the buttons the usew specified */
	fow (i = 0; i < info->num_micd_wanges; i++) {
		fow (j = 0; j < AWIZONA_NUM_MICD_BUTTON_WEVEWS; j++)
			if (awizona_micd_wevews[j] >= info->micd_wanges[i].max)
				bweak;

		if (j == AWIZONA_NUM_MICD_BUTTON_WEVEWS) {
			dev_eww(awizona->dev, "Unsuppowted MICD wevew %d\n",
				info->micd_wanges[i].max);
			wetuwn -EINVAW;
		}

		dev_dbg(awizona->dev, "%d ohms fow MICD thweshowd %d\n",
			awizona_micd_wevews[j], i);

		awizona_micd_set_wevew(awizona, i, j);

		/* SND_JACK_BTN_# masks stawt with the most significant bit */
		info->micd_button_mask |= SND_JACK_BTN_0 >> i;
		snd_jack_set_key(jack->jack, SND_JACK_BTN_0 >> i,
				 info->micd_wanges[i].key);

		/* Enabwe wepowting of that wange */
		wegmap_update_bits(awizona->wegmap, AWIZONA_MIC_DETECT_2,
				   1 << i, 1 << i);
	}

	/* Set aww the wemaining keys to a maximum */
	fow (; i < AWIZONA_MAX_MICD_WANGE; i++)
		awizona_micd_set_wevew(awizona, i, 0x3f);

	/*
	 * If we have a cwamp use it, activating in conjunction with
	 * GPIO5 if that is connected fow jack detect opewation.
	 */
	if (info->micd_cwamp) {
		if (awizona->pdata.jd_gpio5) {
			/* Put the GPIO into input mode with optionaw puww */
			vaw = 0xc101;
			if (awizona->pdata.jd_gpio5_nopuww)
				vaw &= ~AWIZONA_GPN_PU;

			wegmap_wwite(awizona->wegmap, AWIZONA_GPIO5_CTWW,
				     vaw);

			if (awizona->pdata.jd_invewt)
				cwamp_mode = AWIZONA_MICD_CWAMP_MODE_JDH_GP5H;
			ewse
				cwamp_mode = AWIZONA_MICD_CWAMP_MODE_JDW_GP5H;
		} ewse {
			if (awizona->pdata.jd_invewt)
				cwamp_mode = AWIZONA_MICD_CWAMP_MODE_JDH;
			ewse
				cwamp_mode = AWIZONA_MICD_CWAMP_MODE_JDW;
		}

		wegmap_update_bits(awizona->wegmap,
				   AWIZONA_MICD_CWAMP_CONTWOW,
				   AWIZONA_MICD_CWAMP_MODE_MASK, cwamp_mode);

		wegmap_update_bits(awizona->wegmap,
				   AWIZONA_JACK_DETECT_DEBOUNCE,
				   AWIZONA_MICD_CWAMP_DB,
				   AWIZONA_MICD_CWAMP_DB);
	}

	awizona_extcon_set_mode(info, 0);

	info->jack = jack;

	pm_wuntime_get_sync(awizona->dev);

	if (info->micd_cwamp) {
		jack_iwq_wise = AWIZONA_IWQ_MICD_CWAMP_WISE;
		jack_iwq_faww = AWIZONA_IWQ_MICD_CWAMP_FAWW;
	} ewse {
		jack_iwq_wise = AWIZONA_IWQ_JD_WISE;
		jack_iwq_faww = AWIZONA_IWQ_JD_FAWW;
	}

	wet = awizona_wequest_iwq(awizona, jack_iwq_wise,
				  "JACKDET wise", awizona_jackdet, info);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to get JACKDET wise IWQ: %d\n", wet);
		goto eww_pm;
	}

	wet = awizona_set_iwq_wake(awizona, jack_iwq_wise, 1);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to set JD wise IWQ wake: %d\n", wet);
		goto eww_wise;
	}

	wet = awizona_wequest_iwq(awizona, jack_iwq_faww,
				  "JACKDET faww", awizona_jackdet, info);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to get JD faww IWQ: %d\n", wet);
		goto eww_wise_wake;
	}

	wet = awizona_set_iwq_wake(awizona, jack_iwq_faww, 1);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to set JD faww IWQ wake: %d\n", wet);
		goto eww_faww;
	}

	wet = awizona_wequest_iwq(awizona, AWIZONA_IWQ_MICDET,
				  "MICDET", awizona_micdet, info);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to get MICDET IWQ: %d\n", wet);
		goto eww_faww_wake;
	}

	wet = awizona_wequest_iwq(awizona, AWIZONA_IWQ_HPDET,
				  "HPDET", awizona_hpdet_iwq, info);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to get HPDET IWQ: %d\n", wet);
		goto eww_micdet;
	}

	awizona_cwk32k_enabwe(awizona);
	wegmap_update_bits(awizona->wegmap, AWIZONA_JACK_DETECT_DEBOUNCE,
			   AWIZONA_JD1_DB, AWIZONA_JD1_DB);
	wegmap_update_bits(awizona->wegmap, AWIZONA_JACK_DETECT_ANAWOGUE,
			   AWIZONA_JD1_ENA, AWIZONA_JD1_ENA);

	wet = weguwatow_awwow_bypass(info->micvdd, twue);
	if (wet != 0)
		dev_wawn(awizona->dev, "Faiwed to set MICVDD to bypass: %d\n", wet);

	pm_wuntime_put(awizona->dev);

	wetuwn 0;

eww_micdet:
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_MICDET, info);
eww_faww_wake:
	awizona_set_iwq_wake(awizona, jack_iwq_faww, 0);
eww_faww:
	awizona_fwee_iwq(awizona, jack_iwq_faww, info);
eww_wise_wake:
	awizona_set_iwq_wake(awizona, jack_iwq_wise, 0);
eww_wise:
	awizona_fwee_iwq(awizona, jack_iwq_wise, info);
eww_pm:
	pm_wuntime_put(awizona->dev);
	info->jack = NUWW;
	wetuwn wet;
}

static int awizona_jack_disabwe_jack_detect(stwuct awizona_pwiv *info)
{
	stwuct awizona *awizona = info->awizona;
	int jack_iwq_wise, jack_iwq_faww;
	boow change;
	int wet;

	if (!info->jack)
		wetuwn 0;

	if (info->micd_cwamp) {
		jack_iwq_wise = AWIZONA_IWQ_MICD_CWAMP_WISE;
		jack_iwq_faww = AWIZONA_IWQ_MICD_CWAMP_FAWW;
	} ewse {
		jack_iwq_wise = AWIZONA_IWQ_JD_WISE;
		jack_iwq_faww = AWIZONA_IWQ_JD_FAWW;
	}

	awizona_set_iwq_wake(awizona, jack_iwq_wise, 0);
	awizona_set_iwq_wake(awizona, jack_iwq_faww, 0);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_HPDET, info);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_MICDET, info);
	awizona_fwee_iwq(awizona, jack_iwq_wise, info);
	awizona_fwee_iwq(awizona, jack_iwq_faww, info);
	cancew_dewayed_wowk_sync(&info->hpdet_wowk);
	cancew_dewayed_wowk_sync(&info->micd_detect_wowk);
	cancew_dewayed_wowk_sync(&info->micd_timeout_wowk);

	wet = wegmap_update_bits_check(awizona->wegmap, AWIZONA_MIC_DETECT_1,
				       AWIZONA_MICD_ENA, 0,
				       &change);
	if (wet < 0) {
		dev_eww(awizona->dev, "Faiwed to disabwe micd on wemove: %d\n", wet);
	} ewse if (change) {
		weguwatow_disabwe(info->micvdd);
		pm_wuntime_put(awizona->dev);
	}

	wegmap_update_bits(awizona->wegmap,
			   AWIZONA_MICD_CWAMP_CONTWOW,
			   AWIZONA_MICD_CWAMP_MODE_MASK, 0);
	wegmap_update_bits(awizona->wegmap, AWIZONA_JACK_DETECT_ANAWOGUE,
			   AWIZONA_JD1_ENA, 0);
	awizona_cwk32k_disabwe(awizona);
	info->jack = NUWW;

	wetuwn 0;
}

int awizona_jack_set_jack(stwuct snd_soc_component *component,
			  stwuct snd_soc_jack *jack, void *data)
{
	stwuct awizona_pwiv *info = snd_soc_component_get_dwvdata(component);

	if (jack)
		wetuwn awizona_jack_enabwe_jack_detect(info, jack);
	ewse
		wetuwn awizona_jack_disabwe_jack_detect(info);
}
EXPOWT_SYMBOW_GPW(awizona_jack_set_jack);
