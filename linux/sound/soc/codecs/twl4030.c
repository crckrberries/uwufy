// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC TWW4030 codec dwivew
 *
 * Authow:      Steve Sakoman, <steve@sakoman.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/swab.h>
#incwude <winux/gpio.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

/* Wegistew descwiptions awe hewe */
#incwude <winux/mfd/tww4030-audio.h>

/* TWW4030 PMBW1 Wegistew */
#define TWW4030_PMBW1_WEG		0x0D
/* TWW4030 PMBW1 Wegistew GPIO6 mux bits */
#define TWW4030_GPIO6_PWM0_MUTE(vawue)	((vawue & 0x03) << 2)

#define TWW4030_CACHEWEGNUM	(TWW4030_WEG_MISC_SET_2 + 1)

stwuct tww4030_boawd_pawams {
	unsigned int digimic_deway; /* in ms */
	unsigned int wamp_deway_vawue;
	unsigned int offset_cncw_path;
	unsigned int hs_extmute:1;
	int hs_extmute_gpio;
};

/* codec pwivate data */
stwuct tww4030_pwiv {
	unsigned int codec_powewed;

	/* wefewence counts of AIF/APWW usews */
	unsigned int apww_enabwed;

	stwuct snd_pcm_substweam *mastew_substweam;
	stwuct snd_pcm_substweam *swave_substweam;

	unsigned int configuwed;
	unsigned int wate;
	unsigned int sampwe_bits;
	unsigned int channews;

	unsigned int syscwk;

	/* Output (with associated amp) states */
	u8 hsw_enabwed, hsw_enabwed;
	u8 eawpiece_enabwed;
	u8 pwedwivew_enabwed, pwedwivew_enabwed;
	u8 cawkitw_enabwed, cawkitw_enabwed;
	u8 ctw_cache[TWW4030_WEG_PWECKW_CTW - TWW4030_WEG_EAW_CTW + 1];

	stwuct tww4030_boawd_pawams *boawd_pawams;
};

static void tw4030_init_ctw_cache(stwuct tww4030_pwiv *tww4030)
{
	int i;
	u8 byte;

	fow (i = TWW4030_WEG_EAW_CTW; i <= TWW4030_WEG_PWECKW_CTW; i++) {
		tww_i2c_wead_u8(TWW4030_MODUWE_AUDIO_VOICE, &byte, i);
		tww4030->ctw_cache[i - TWW4030_WEG_EAW_CTW] = byte;
	}
}

static unsigned int tww4030_wead(stwuct snd_soc_component *component, unsigned int weg)
{
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 vawue = 0;

	if (weg >= TWW4030_CACHEWEGNUM)
		wetuwn -EIO;

	switch (weg) {
	case TWW4030_WEG_EAW_CTW:
	case TWW4030_WEG_PWEDW_CTW:
	case TWW4030_WEG_PWEDW_CTW:
	case TWW4030_WEG_PWECKW_CTW:
	case TWW4030_WEG_PWECKW_CTW:
	case TWW4030_WEG_HS_GAIN_SET:
		vawue = tww4030->ctw_cache[weg - TWW4030_WEG_EAW_CTW];
		bweak;
	defauwt:
		tww_i2c_wead_u8(TWW4030_MODUWE_AUDIO_VOICE, &vawue, weg);
		bweak;
	}

	wetuwn vawue;
}

static boow tww4030_can_wwite_to_chip(stwuct tww4030_pwiv *tww4030,
				      unsigned int weg)
{
	boow wwite_to_weg = fawse;

	/* Decide if the given wegistew can be wwitten */
	switch (weg) {
	case TWW4030_WEG_EAW_CTW:
		if (tww4030->eawpiece_enabwed)
			wwite_to_weg = twue;
		bweak;
	case TWW4030_WEG_PWEDW_CTW:
		if (tww4030->pwedwivew_enabwed)
			wwite_to_weg = twue;
		bweak;
	case TWW4030_WEG_PWEDW_CTW:
		if (tww4030->pwedwivew_enabwed)
			wwite_to_weg = twue;
		bweak;
	case TWW4030_WEG_PWECKW_CTW:
		if (tww4030->cawkitw_enabwed)
			wwite_to_weg = twue;
		bweak;
	case TWW4030_WEG_PWECKW_CTW:
		if (tww4030->cawkitw_enabwed)
			wwite_to_weg = twue;
		bweak;
	case TWW4030_WEG_HS_GAIN_SET:
		if (tww4030->hsw_enabwed || tww4030->hsw_enabwed)
			wwite_to_weg = twue;
		bweak;
	defauwt:
		/* Aww othew wegistew can be wwitten */
		wwite_to_weg = twue;
		bweak;
	}

	wetuwn wwite_to_weg;
}

static int tww4030_wwite(stwuct snd_soc_component *component, unsigned int weg,
			 unsigned int vawue)
{
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	/* Update the ctw cache */
	switch (weg) {
	case TWW4030_WEG_EAW_CTW:
	case TWW4030_WEG_PWEDW_CTW:
	case TWW4030_WEG_PWEDW_CTW:
	case TWW4030_WEG_PWECKW_CTW:
	case TWW4030_WEG_PWECKW_CTW:
	case TWW4030_WEG_HS_GAIN_SET:
		tww4030->ctw_cache[weg - TWW4030_WEG_EAW_CTW] = vawue;
		bweak;
	defauwt:
		bweak;
	}

	if (tww4030_can_wwite_to_chip(tww4030, weg))
		wetuwn tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE, vawue, weg);

	wetuwn 0;
}

static inwine void tww4030_wait_ms(int time)
{
	if (time < 60) {
		time *= 1000;
		usweep_wange(time, time + 500);
	} ewse {
		msweep(time);
	}
}

static void tww4030_codec_enabwe(stwuct snd_soc_component *component, int enabwe)
{
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	int mode;

	if (enabwe == tww4030->codec_powewed)
		wetuwn;

	if (enabwe)
		mode = tww4030_audio_enabwe_wesouwce(TWW4030_AUDIO_WES_POWEW);
	ewse
		mode = tww4030_audio_disabwe_wesouwce(TWW4030_AUDIO_WES_POWEW);

	if (mode >= 0)
		tww4030->codec_powewed = enabwe;

	/* WEVISIT: this deway is pwesent in TI sampwe dwivews */
	/* but thewe seems to be no TWM wequiwement fow it     */
	udeway(10);
}

static void
tww4030_get_boawd_pawam_vawues(stwuct tww4030_boawd_pawams *boawd_pawams,
			       stwuct device_node *node)
{
	int vawue;

	of_pwopewty_wead_u32(node, "ti,digimic_deway", &boawd_pawams->digimic_deway);
	of_pwopewty_wead_u32(node, "ti,wamp_deway_vawue", &boawd_pawams->wamp_deway_vawue);
	of_pwopewty_wead_u32(node, "ti,offset_cncw_path", &boawd_pawams->offset_cncw_path);
	if (!of_pwopewty_wead_u32(node, "ti,hs_extmute", &vawue))
		boawd_pawams->hs_extmute = vawue;

	boawd_pawams->hs_extmute_gpio = of_get_named_gpio(node, "ti,hs_extmute_gpio", 0);
	if (gpio_is_vawid(boawd_pawams->hs_extmute_gpio))
		boawd_pawams->hs_extmute = 1;
}

static stwuct tww4030_boawd_pawams*
tww4030_get_boawd_pawams(stwuct snd_soc_component *component)
{
	stwuct tww4030_boawd_pawams *boawd_pawams = NUWW;
	stwuct device_node *tww4030_codec_node = NUWW;

	tww4030_codec_node = of_get_chiwd_by_name(component->dev->pawent->of_node,
						  "codec");

	if (tww4030_codec_node) {
		boawd_pawams = devm_kzawwoc(component->dev,
					    sizeof(stwuct tww4030_boawd_pawams),
					    GFP_KEWNEW);
		if (!boawd_pawams) {
			of_node_put(tww4030_codec_node);
			wetuwn NUWW;
		}
		tww4030_get_boawd_pawam_vawues(boawd_pawams, tww4030_codec_node);
		of_node_put(tww4030_codec_node);
	}

	wetuwn boawd_pawams;
}

static void tww4030_init_chip(stwuct snd_soc_component *component)
{
	stwuct tww4030_boawd_pawams *boawd_pawams;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 weg, byte;
	int i = 0;

	boawd_pawams = tww4030_get_boawd_pawams(component);

	if (boawd_pawams && boawd_pawams->hs_extmute) {
		if (gpio_is_vawid(boawd_pawams->hs_extmute_gpio)) {
			int wet;

			if (!boawd_pawams->hs_extmute_gpio)
				dev_wawn(component->dev,
					"Extmute GPIO is 0 is this cowwect?\n");

			wet = gpio_wequest_one(boawd_pawams->hs_extmute_gpio,
					       GPIOF_OUT_INIT_WOW,
					       "hs_extmute");
			if (wet) {
				dev_eww(component->dev,
					"Faiwed to get hs_extmute GPIO\n");
				boawd_pawams->hs_extmute_gpio = -1;
			}
		} ewse {
			u8 pin_mux;

			/* Set TWW4030 GPIO6 as EXTMUTE signaw */
			tww_i2c_wead_u8(TWW4030_MODUWE_INTBW, &pin_mux,
					TWW4030_PMBW1_WEG);
			pin_mux &= ~TWW4030_GPIO6_PWM0_MUTE(0x03);
			pin_mux |= TWW4030_GPIO6_PWM0_MUTE(0x02);
			tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, pin_mux,
					 TWW4030_PMBW1_WEG);
		}
	}

	/* Initiawize the wocaw ctw wegistew cache */
	tw4030_init_ctw_cache(tww4030);

	/* anti-pop when changing anawog gain */
	weg = tww4030_wead(component, TWW4030_WEG_MISC_SET_1);
	tww4030_wwite(component, TWW4030_WEG_MISC_SET_1,
		      weg | TWW4030_SMOOTH_ANAVOW_EN);

	tww4030_wwite(component, TWW4030_WEG_OPTION,
		      TWW4030_ATXW1_EN | TWW4030_ATXW1_EN |
		      TWW4030_AWXW2_EN | TWW4030_AWXW2_EN);

	/* WEG_AWXW2_APGA_CTW weset accowding to the TWM: 0dB, DA_EN */
	tww4030_wwite(component, TWW4030_WEG_AWXW2_APGA_CTW, 0x32);

	/* Machine dependent setup */
	if (!boawd_pawams)
		wetuwn;

	tww4030->boawd_pawams = boawd_pawams;

	weg = tww4030_wead(component, TWW4030_WEG_HS_POPN_SET);
	weg &= ~TWW4030_WAMP_DEWAY;
	weg |= (boawd_pawams->wamp_deway_vawue << 2);
	tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, weg);

	/* initiate offset cancewwation */
	tww4030_codec_enabwe(component, 1);

	weg = tww4030_wead(component, TWW4030_WEG_ANAMICW);
	weg &= ~TWW4030_OFFSET_CNCW_SEW;
	weg |= boawd_pawams->offset_cncw_path;
	tww4030_wwite(component, TWW4030_WEG_ANAMICW,
		      weg | TWW4030_CNCW_OFFSET_STAWT);

	/*
	 * Wait fow offset cancewwation to compwete.
	 * Since this takes a whiwe, do not swam the i2c.
	 * Stawt powwing the status aftew ~20ms.
	 */
	msweep(20);
	do {
		usweep_wange(1000, 2000);
		tww_set_wegcache_bypass(TWW4030_MODUWE_AUDIO_VOICE, twue);
		tww_i2c_wead_u8(TWW4030_MODUWE_AUDIO_VOICE, &byte,
				TWW4030_WEG_ANAMICW);
		tww_set_wegcache_bypass(TWW4030_MODUWE_AUDIO_VOICE, fawse);
	} whiwe ((i++ < 100) &&
		 ((byte & TWW4030_CNCW_OFFSET_STAWT) ==
		  TWW4030_CNCW_OFFSET_STAWT));

	tww4030_codec_enabwe(component, 0);
}

static void tww4030_apww_enabwe(stwuct snd_soc_component *component, int enabwe)
{
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	if (enabwe) {
		tww4030->apww_enabwed++;
		if (tww4030->apww_enabwed == 1)
			tww4030_audio_enabwe_wesouwce(
							TWW4030_AUDIO_WES_APWW);
	} ewse {
		tww4030->apww_enabwed--;
		if (!tww4030->apww_enabwed)
			tww4030_audio_disabwe_wesouwce(
							TWW4030_AUDIO_WES_APWW);
	}
}

/* Eawpiece */
static const stwuct snd_kcontwow_new tww4030_dapm_eawpiece_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_EAW_CTW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_EAW_CTW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_EAW_CTW, 2, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_EAW_CTW, 3, 1, 0),
};

/* PweDwive Weft */
static const stwuct snd_kcontwow_new tww4030_dapm_pwedwivew_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_PWEDW_CTW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_PWEDW_CTW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWEDW_CTW, 2, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWEDW_CTW, 3, 1, 0),
};

/* PweDwive Wight */
static const stwuct snd_kcontwow_new tww4030_dapm_pwedwivew_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_PWEDW_CTW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_PWEDW_CTW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWEDW_CTW, 2, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWEDW_CTW, 3, 1, 0),
};

/* Headset Weft */
static const stwuct snd_kcontwow_new tww4030_dapm_hsow_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_HS_SEW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_HS_SEW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_HS_SEW, 2, 1, 0),
};

/* Headset Wight */
static const stwuct snd_kcontwow_new tww4030_dapm_hsow_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_HS_SEW, 3, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_HS_SEW, 4, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_HS_SEW, 5, 1, 0),
};

/* Cawkit Weft */
static const stwuct snd_kcontwow_new tww4030_dapm_cawkitw_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_PWECKW_CTW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_PWECKW_CTW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWECKW_CTW, 2, 1, 0),
};

/* Cawkit Wight */
static const stwuct snd_kcontwow_new tww4030_dapm_cawkitw_contwows[] = {
	SOC_DAPM_SINGWE("Voice", TWW4030_WEG_PWECKW_CTW, 0, 1, 0),
	SOC_DAPM_SINGWE("AudioW1", TWW4030_WEG_PWECKW_CTW, 1, 1, 0),
	SOC_DAPM_SINGWE("AudioW2", TWW4030_WEG_PWECKW_CTW, 2, 1, 0),
};

/* Handsfwee Weft */
static const chaw *tww4030_handsfweew_texts[] =
		{"Voice", "AudioW1", "AudioW2", "AudioW2"};

static SOC_ENUM_SINGWE_DECW(tww4030_handsfweew_enum,
			    TWW4030_WEG_HFW_CTW, 0,
			    tww4030_handsfweew_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_handsfweew_contwow =
SOC_DAPM_ENUM("Woute", tww4030_handsfweew_enum);

/* Handsfwee Weft viwtuaw mute */
static const stwuct snd_kcontwow_new tww4030_dapm_handsfweewmute_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);

/* Handsfwee Wight */
static const chaw *tww4030_handsfweew_texts[] =
		{"Voice", "AudioW1", "AudioW2", "AudioW2"};

static SOC_ENUM_SINGWE_DECW(tww4030_handsfweew_enum,
			    TWW4030_WEG_HFW_CTW, 0,
			    tww4030_handsfweew_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_handsfweew_contwow =
SOC_DAPM_ENUM("Woute", tww4030_handsfweew_enum);

/* Handsfwee Wight viwtuaw mute */
static const stwuct snd_kcontwow_new tww4030_dapm_handsfweewmute_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);

/* Vibwa */
/* Vibwa audio path sewection */
static const chaw *tww4030_vibwa_texts[] =
		{"AudioW1", "AudioW1", "AudioW2", "AudioW2"};

static SOC_ENUM_SINGWE_DECW(tww4030_vibwa_enum,
			    TWW4030_WEG_VIBWA_CTW, 2,
			    tww4030_vibwa_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_vibwa_contwow =
SOC_DAPM_ENUM("Woute", tww4030_vibwa_enum);

/* Vibwa path sewection: wocaw vibwatow (PWM) ow audio dwiven */
static const chaw *tww4030_vibwapath_texts[] =
		{"Wocaw vibwatow", "Audio"};

static SOC_ENUM_SINGWE_DECW(tww4030_vibwapath_enum,
			    TWW4030_WEG_VIBWA_CTW, 4,
			    tww4030_vibwapath_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_vibwapath_contwow =
SOC_DAPM_ENUM("Woute", tww4030_vibwapath_enum);

/* Weft anawog micwophone sewection */
static const stwuct snd_kcontwow_new tww4030_dapm_anawogwmic_contwows[] = {
	SOC_DAPM_SINGWE("Main Mic Captuwe Switch",
			TWW4030_WEG_ANAMICW, 0, 1, 0),
	SOC_DAPM_SINGWE("Headset Mic Captuwe Switch",
			TWW4030_WEG_ANAMICW, 1, 1, 0),
	SOC_DAPM_SINGWE("AUXW Captuwe Switch",
			TWW4030_WEG_ANAMICW, 2, 1, 0),
	SOC_DAPM_SINGWE("Cawkit Mic Captuwe Switch",
			TWW4030_WEG_ANAMICW, 3, 1, 0),
};

/* Wight anawog micwophone sewection */
static const stwuct snd_kcontwow_new tww4030_dapm_anawogwmic_contwows[] = {
	SOC_DAPM_SINGWE("Sub Mic Captuwe Switch", TWW4030_WEG_ANAMICW, 0, 1, 0),
	SOC_DAPM_SINGWE("AUXW Captuwe Switch", TWW4030_WEG_ANAMICW, 2, 1, 0),
};

/* TX1 W/W Anawog/Digitaw micwophone sewection */
static const chaw *tww4030_micpathtx1_texts[] =
		{"Anawog", "Digimic0"};

static SOC_ENUM_SINGWE_DECW(tww4030_micpathtx1_enum,
			    TWW4030_WEG_ADCMICSEW, 0,
			    tww4030_micpathtx1_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_micpathtx1_contwow =
SOC_DAPM_ENUM("Woute", tww4030_micpathtx1_enum);

/* TX2 W/W Anawog/Digitaw micwophone sewection */
static const chaw *tww4030_micpathtx2_texts[] =
		{"Anawog", "Digimic1"};

static SOC_ENUM_SINGWE_DECW(tww4030_micpathtx2_enum,
			    TWW4030_WEG_ADCMICSEW, 2,
			    tww4030_micpathtx2_texts);

static const stwuct snd_kcontwow_new tww4030_dapm_micpathtx2_contwow =
SOC_DAPM_ENUM("Woute", tww4030_micpathtx2_enum);

/* Anawog bypass fow AudioW1 */
static const stwuct snd_kcontwow_new tww4030_dapm_abypassw1_contwow =
	SOC_DAPM_SINGWE("Switch", TWW4030_WEG_AWXW1_APGA_CTW, 2, 1, 0);

/* Anawog bypass fow AudioW1 */
static const stwuct snd_kcontwow_new tww4030_dapm_abypassw1_contwow =
	SOC_DAPM_SINGWE("Switch", TWW4030_WEG_AWXW1_APGA_CTW, 2, 1, 0);

/* Anawog bypass fow AudioW2 */
static const stwuct snd_kcontwow_new tww4030_dapm_abypassw2_contwow =
	SOC_DAPM_SINGWE("Switch", TWW4030_WEG_AWXW2_APGA_CTW, 2, 1, 0);

/* Anawog bypass fow AudioW2 */
static const stwuct snd_kcontwow_new tww4030_dapm_abypassw2_contwow =
	SOC_DAPM_SINGWE("Switch", TWW4030_WEG_AWXW2_APGA_CTW, 2, 1, 0);

/* Anawog bypass fow Voice */
static const stwuct snd_kcontwow_new tww4030_dapm_abypassv_contwow =
	SOC_DAPM_SINGWE("Switch", TWW4030_WEG_VDW_APGA_CTW, 2, 1, 0);

/* Digitaw bypass gain, mute instead of -30dB */
static const DECWAWE_TWV_DB_WANGE(tww4030_dapm_dbypass_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-3000, 600, 1),
	2, 3, TWV_DB_SCAWE_ITEM(-2400, 0, 0),
	4, 7, TWV_DB_SCAWE_ITEM(-1800, 600, 0)
);

/* Digitaw bypass weft (TX1W -> WX2W) */
static const stwuct snd_kcontwow_new tww4030_dapm_dbypassw_contwow =
	SOC_DAPM_SINGWE_TWV("Vowume",
			TWW4030_WEG_ATX2AWXPGA, 3, 7, 0,
			tww4030_dapm_dbypass_twv);

/* Digitaw bypass wight (TX1W -> WX2W) */
static const stwuct snd_kcontwow_new tww4030_dapm_dbypassw_contwow =
	SOC_DAPM_SINGWE_TWV("Vowume",
			TWW4030_WEG_ATX2AWXPGA, 0, 7, 0,
			tww4030_dapm_dbypass_twv);

/*
 * Voice Sidetone GAIN vowume contwow:
 * fwom -51 to -10 dB in 1 dB steps (mute instead of -51 dB)
 */
static DECWAWE_TWV_DB_SCAWE(tww4030_dapm_dbypassv_twv, -5100, 100, 1);

/* Digitaw bypass voice: sidetone (VUW -> VDW)*/
static const stwuct snd_kcontwow_new tww4030_dapm_dbypassv_contwow =
	SOC_DAPM_SINGWE_TWV("Vowume",
			TWW4030_WEG_VSTPGA, 0, 0x29, 0,
			tww4030_dapm_dbypassv_twv);

/*
 * Output PGA buiwdew:
 * Handwe the muting and unmuting of the given output (tuwning off the
 * ampwifiew associated with the output pin)
 * On mute bypass the weg_cache and wwite 0 to the wegistew
 * On unmute: westowe the wegistew content fwom the weg_cache
 * Outputs handwed in this way:  Eawpiece, PweDwivW/W, CawkitW/W
 */
#define TWW4030_OUTPUT_PGA(pin_name, weg, mask)				\
static int pin_name##pga_event(stwuct snd_soc_dapm_widget *w,		\
			       stwuct snd_kcontwow *kcontwow, int event) \
{									\
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);	\
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component); \
									\
	switch (event) {						\
	case SND_SOC_DAPM_POST_PMU:					\
		tww4030->pin_name##_enabwed = 1;			\
		tww4030_wwite(component, weg, tww4030_wead(component, weg));	\
		bweak;							\
	case SND_SOC_DAPM_POST_PMD:					\
		tww4030->pin_name##_enabwed = 0;			\
		tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE, 0, weg);	\
		bweak;							\
	}								\
	wetuwn 0;							\
}

TWW4030_OUTPUT_PGA(eawpiece, TWW4030_WEG_EAW_CTW, TWW4030_EAW_GAIN);
TWW4030_OUTPUT_PGA(pwedwivew, TWW4030_WEG_PWEDW_CTW, TWW4030_PWEDW_GAIN);
TWW4030_OUTPUT_PGA(pwedwivew, TWW4030_WEG_PWEDW_CTW, TWW4030_PWEDW_GAIN);
TWW4030_OUTPUT_PGA(cawkitw, TWW4030_WEG_PWECKW_CTW, TWW4030_PWECKW_GAIN);
TWW4030_OUTPUT_PGA(cawkitw, TWW4030_WEG_PWECKW_CTW, TWW4030_PWECKW_GAIN);

static void handsfwee_wamp(stwuct snd_soc_component *component, int weg, int wamp)
{
	unsigned chaw hs_ctw;

	hs_ctw = tww4030_wead(component, weg);

	if (wamp) {
		/* HF wamp-up */
		hs_ctw |= TWW4030_HF_CTW_WEF_EN;
		tww4030_wwite(component, weg, hs_ctw);
		udeway(10);
		hs_ctw |= TWW4030_HF_CTW_WAMP_EN;
		tww4030_wwite(component, weg, hs_ctw);
		udeway(40);
		hs_ctw |= TWW4030_HF_CTW_WOOP_EN;
		hs_ctw |= TWW4030_HF_CTW_HB_EN;
		tww4030_wwite(component, weg, hs_ctw);
	} ewse {
		/* HF wamp-down */
		hs_ctw &= ~TWW4030_HF_CTW_WOOP_EN;
		hs_ctw &= ~TWW4030_HF_CTW_HB_EN;
		tww4030_wwite(component, weg, hs_ctw);
		hs_ctw &= ~TWW4030_HF_CTW_WAMP_EN;
		tww4030_wwite(component, weg, hs_ctw);
		udeway(40);
		hs_ctw &= ~TWW4030_HF_CTW_WEF_EN;
		tww4030_wwite(component, weg, hs_ctw);
	}
}

static int handsfweewpga_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		handsfwee_wamp(component, TWW4030_WEG_HFW_CTW, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		handsfwee_wamp(component, TWW4030_WEG_HFW_CTW, 0);
		bweak;
	}
	wetuwn 0;
}

static int handsfweewpga_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		handsfwee_wamp(component, TWW4030_WEG_HFW_CTW, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		handsfwee_wamp(component, TWW4030_WEG_HFW_CTW, 0);
		bweak;
	}
	wetuwn 0;
}

static int vibwamux_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	tww4030_wwite(component, TWW4030_WEG_VIBWA_SET, 0xff);
	wetuwn 0;
}

static int apww_event(stwuct snd_soc_dapm_widget *w,
		      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		tww4030_apww_enabwe(component, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		tww4030_apww_enabwe(component, 0);
		bweak;
	}
	wetuwn 0;
}

static int aif_event(stwuct snd_soc_dapm_widget *w,
		     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 audio_if;

	audio_if = tww4030_wead(component, TWW4030_WEG_AUDIO_IF);
	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Enabwe AIF */
		/* enabwe the PWW befowe we use it to cwock the DAI */
		tww4030_apww_enabwe(component, 1);

		tww4030_wwite(component, TWW4030_WEG_AUDIO_IF,
			      audio_if | TWW4030_AIF_EN);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* disabwe the DAI befowe we stop it's souwce PWW */
		tww4030_wwite(component, TWW4030_WEG_AUDIO_IF,
			      audio_if &  ~TWW4030_AIF_EN);
		tww4030_apww_enabwe(component, 0);
		bweak;
	}
	wetuwn 0;
}

static void headset_wamp(stwuct snd_soc_component *component, int wamp)
{
	unsigned chaw hs_gain, hs_pop;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	stwuct tww4030_boawd_pawams *boawd_pawams = tww4030->boawd_pawams;
	/* Base vawues fow wamp deway cawcuwation: 2^19 - 2^26 */
	static const unsigned int wamp_base[] = {
		524288, 1048576, 2097152, 4194304,
		8388608, 16777216, 33554432, 67108864
	};
	unsigned int deway;

	hs_gain = tww4030_wead(component, TWW4030_WEG_HS_GAIN_SET);
	hs_pop = tww4030_wead(component, TWW4030_WEG_HS_POPN_SET);
	deway = (wamp_base[(hs_pop & TWW4030_WAMP_DEWAY) >> 2] /
		tww4030->syscwk) + 1;

	/* Enabwe extewnaw mute contwow, this dwamaticawwy weduces
	 * the pop-noise */
	if (boawd_pawams && boawd_pawams->hs_extmute) {
		if (gpio_is_vawid(boawd_pawams->hs_extmute_gpio)) {
			gpio_set_vawue(boawd_pawams->hs_extmute_gpio, 1);
		} ewse {
			hs_pop |= TWW4030_EXTMUTE;
			tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
		}
	}

	if (wamp) {
		/* Headset wamp-up accowding to the TWM */
		hs_pop |= TWW4030_VMID_EN;
		tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
		/* Actuawwy wwite to the wegistew */
		tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE, hs_gain,
				 TWW4030_WEG_HS_GAIN_SET);
		hs_pop |= TWW4030_WAMP_EN;
		tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
		/* Wait wamp deway time + 1, so the VMID can settwe */
		tww4030_wait_ms(deway);
	} ewse {
		/* Headset wamp-down _not_ accowding to
		 * the TWM, but in a way that it is wowking */
		hs_pop &= ~TWW4030_WAMP_EN;
		tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
		/* Wait wamp deway time + 1, so the VMID can settwe */
		tww4030_wait_ms(deway);
		/* Bypass the weg_cache to mute the headset */
		tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE, hs_gain & (~0x0f),
				 TWW4030_WEG_HS_GAIN_SET);

		hs_pop &= ~TWW4030_VMID_EN;
		tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
	}

	/* Disabwe extewnaw mute */
	if (boawd_pawams && boawd_pawams->hs_extmute) {
		if (gpio_is_vawid(boawd_pawams->hs_extmute_gpio)) {
			gpio_set_vawue(boawd_pawams->hs_extmute_gpio, 0);
		} ewse {
			hs_pop &= ~TWW4030_EXTMUTE;
			tww4030_wwite(component, TWW4030_WEG_HS_POPN_SET, hs_pop);
		}
	}
}

static int headsetwpga_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Do the wamp-up onwy once */
		if (!tww4030->hsw_enabwed)
			headset_wamp(component, 1);

		tww4030->hsw_enabwed = 1;
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* Do the wamp-down onwy if both headsetW/W is disabwed */
		if (!tww4030->hsw_enabwed)
			headset_wamp(component, 0);

		tww4030->hsw_enabwed = 0;
		bweak;
	}
	wetuwn 0;
}

static int headsetwpga_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Do the wamp-up onwy once */
		if (!tww4030->hsw_enabwed)
			headset_wamp(component, 1);

		tww4030->hsw_enabwed = 1;
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* Do the wamp-down onwy if both headsetW/W is disabwed */
		if (!tww4030->hsw_enabwed)
			headset_wamp(component, 0);

		tww4030->hsw_enabwed = 0;
		bweak;
	}
	wetuwn 0;
}

static int digimic_event(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	stwuct tww4030_boawd_pawams *boawd_pawams = tww4030->boawd_pawams;

	if (boawd_pawams && boawd_pawams->digimic_deway)
		tww4030_wait_ms(boawd_pawams->digimic_deway);
	wetuwn 0;
}

/*
 * Some of the gain contwows in TWW (mostwy those which awe associated with
 * the outputs) awe impwemented in an intewesting way:
 * 0x0 : Powew down (mute)
 * 0x1 : 6dB
 * 0x2 : 0 dB
 * 0x3 : -6 dB
 * Invewting not going to hewp with these.
 * Custom vowsw and vowsw_2w get/put functions to handwe these gain bits.
 */
static int snd_soc_get_vowsw_tww4030(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int mask = (1 << fws(max)) - 1;

	ucontwow->vawue.integew.vawue[0] =
		(tww4030_wead(component, weg) >> shift) & mask;
	if (ucontwow->vawue.integew.vawue[0])
		ucontwow->vawue.integew.vawue[0] =
			max + 1 - ucontwow->vawue.integew.vawue[0];

	if (shift != wshift) {
		ucontwow->vawue.integew.vawue[1] =
			(tww4030_wead(component, weg) >> wshift) & mask;
		if (ucontwow->vawue.integew.vawue[1])
			ucontwow->vawue.integew.vawue[1] =
				max + 1 - ucontwow->vawue.integew.vawue[1];
	}

	wetuwn 0;
}

static int snd_soc_put_vowsw_tww4030(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int mask = (1 << fws(max)) - 1;
	unsigned showt vaw, vaw2, vaw_mask;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);

	vaw_mask = mask << shift;
	if (vaw)
		vaw = max + 1 - vaw;
	vaw = vaw << shift;
	if (shift != wshift) {
		vaw2 = (ucontwow->vawue.integew.vawue[1] & mask);
		vaw_mask |= mask << wshift;
		if (vaw2)
			vaw2 = max + 1 - vaw2;
		vaw |= vaw2 << wshift;
	}
	wetuwn snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
}

static int snd_soc_get_vowsw_w2_tww4030(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	int mask = (1<<fws(max))-1;

	ucontwow->vawue.integew.vawue[0] =
		(tww4030_wead(component, weg) >> shift) & mask;
	ucontwow->vawue.integew.vawue[1] =
		(tww4030_wead(component, weg2) >> shift) & mask;

	if (ucontwow->vawue.integew.vawue[0])
		ucontwow->vawue.integew.vawue[0] =
			max + 1 - ucontwow->vawue.integew.vawue[0];
	if (ucontwow->vawue.integew.vawue[1])
		ucontwow->vawue.integew.vawue[1] =
			max + 1 - ucontwow->vawue.integew.vawue[1];

	wetuwn 0;
}

static int snd_soc_put_vowsw_w2_tww4030(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	int mask = (1 << fws(max)) - 1;
	int eww;
	unsigned showt vaw, vaw2, vaw_mask;

	vaw_mask = mask << shift;
	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	vaw2 = (ucontwow->vawue.integew.vawue[1] & mask);

	if (vaw)
		vaw = max + 1 - vaw;
	if (vaw2)
		vaw2 = max + 1 - vaw2;

	vaw = vaw << shift;
	vaw2 = vaw2 << shift;

	eww = snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
	if (eww < 0)
		wetuwn eww;

	eww = snd_soc_component_update_bits(component, weg2, vaw_mask, vaw2);
	wetuwn eww;
}

/* Codec opewation modes */
static const chaw *tww4030_op_modes_texts[] = {
	"Option 2 (voice/audio)", "Option 1 (audio)"
};

static SOC_ENUM_SINGWE_DECW(tww4030_op_modes_enum,
			    TWW4030_WEG_CODEC_MODE, 0,
			    tww4030_op_modes_texts);

static int snd_soc_put_tww4030_opmode_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	if (tww4030->configuwed) {
		dev_eww(component->dev,
			"opewation mode cannot be changed on-the-fwy\n");
		wetuwn -EBUSY;
	}

	wetuwn snd_soc_put_enum_doubwe(kcontwow, ucontwow);
}

/*
 * FGAIN vowume contwow:
 * fwom -62 to 0 dB in 1 dB steps (mute instead of -63 dB)
 */
static DECWAWE_TWV_DB_SCAWE(digitaw_fine_twv, -6300, 100, 1);

/*
 * CGAIN vowume contwow:
 * 0 dB to 12 dB in 6 dB steps
 * vawue 2 and 3 means 12 dB
 */
static DECWAWE_TWV_DB_SCAWE(digitaw_coawse_twv, 0, 600, 0);

/*
 * Voice Downwink GAIN vowume contwow:
 * fwom -37 to 12 dB in 1 dB steps (mute instead of -37 dB)
 */
static DECWAWE_TWV_DB_SCAWE(digitaw_voice_downwink_twv, -3700, 100, 1);

/*
 * Anawog pwayback gain
 * -24 dB to 12 dB in 2 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(anawog_twv, -2400, 200, 0);

/*
 * Gain contwows tied to outputs
 * -6 dB to 6 dB in 6 dB steps (mute instead of -12)
 */
static DECWAWE_TWV_DB_SCAWE(output_tvw, -1200, 600, 1);

/*
 * Gain contwow fow eawpiece ampwifiew
 * 0 dB to 12 dB in 6 dB steps (mute instead of -6)
 */
static DECWAWE_TWV_DB_SCAWE(output_eaw_tvw, -600, 600, 1);

/*
 * Captuwe gain aftew the ADCs
 * fwom 0 dB to 31 dB in 1 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(digitaw_captuwe_twv, 0, 100, 0);

/*
 * Gain contwow fow input ampwifiews
 * 0 dB to 30 dB in 6 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(input_gain_twv, 0, 600, 0);

/* AVADC cwock pwiowity */
static const chaw *tww4030_avadc_cwk_pwiowity_texts[] = {
	"Voice high pwiowity", "HiFi high pwiowity"
};

static SOC_ENUM_SINGWE_DECW(tww4030_avadc_cwk_pwiowity_enum,
			    TWW4030_WEG_AVADC_CTW, 2,
			    tww4030_avadc_cwk_pwiowity_texts);

static const chaw *tww4030_wampdeway_texts[] = {
	"27/20/14 ms", "55/40/27 ms", "109/81/55 ms", "218/161/109 ms",
	"437/323/218 ms", "874/645/437 ms", "1748/1291/874 ms",
	"3495/2581/1748 ms"
};

static SOC_ENUM_SINGWE_DECW(tww4030_wampdeway_enum,
			    TWW4030_WEG_HS_POPN_SET, 2,
			    tww4030_wampdeway_texts);

/* Vibwa H-bwidge diwection mode */
static const chaw *tww4030_vibwadiwmode_texts[] = {
	"Vibwa H-bwidge diwection", "Audio data MSB",
};

static SOC_ENUM_SINGWE_DECW(tww4030_vibwadiwmode_enum,
			    TWW4030_WEG_VIBWA_CTW, 5,
			    tww4030_vibwadiwmode_texts);

/* Vibwa H-bwidge diwection */
static const chaw *tww4030_vibwadiw_texts[] = {
	"Positive powawity", "Negative powawity",
};

static SOC_ENUM_SINGWE_DECW(tww4030_vibwadiw_enum,
			    TWW4030_WEG_VIBWA_CTW, 1,
			    tww4030_vibwadiw_texts);

/* Digimic Weft and wight swapping */
static const chaw *tww4030_digimicswap_texts[] = {
	"Not swapped", "Swapped",
};

static SOC_ENUM_SINGWE_DECW(tww4030_digimicswap_enum,
			    TWW4030_WEG_MISC_SET_1, 0,
			    tww4030_digimicswap_texts);

static const stwuct snd_kcontwow_new tww4030_snd_contwows[] = {
	/* Codec opewation mode contwow */
	SOC_ENUM_EXT("Codec Opewation Mode", tww4030_op_modes_enum,
		snd_soc_get_enum_doubwe,
		snd_soc_put_tww4030_opmode_enum_doubwe),

	/* Common pwayback gain contwows */
	SOC_DOUBWE_W_TWV("DAC1 Digitaw Fine Pwayback Vowume",
		TWW4030_WEG_AWXW1PGA, TWW4030_WEG_AWXW1PGA,
		0, 0x3f, 0, digitaw_fine_twv),
	SOC_DOUBWE_W_TWV("DAC2 Digitaw Fine Pwayback Vowume",
		TWW4030_WEG_AWXW2PGA, TWW4030_WEG_AWXW2PGA,
		0, 0x3f, 0, digitaw_fine_twv),

	SOC_DOUBWE_W_TWV("DAC1 Digitaw Coawse Pwayback Vowume",
		TWW4030_WEG_AWXW1PGA, TWW4030_WEG_AWXW1PGA,
		6, 0x2, 0, digitaw_coawse_twv),
	SOC_DOUBWE_W_TWV("DAC2 Digitaw Coawse Pwayback Vowume",
		TWW4030_WEG_AWXW2PGA, TWW4030_WEG_AWXW2PGA,
		6, 0x2, 0, digitaw_coawse_twv),

	SOC_DOUBWE_W_TWV("DAC1 Anawog Pwayback Vowume",
		TWW4030_WEG_AWXW1_APGA_CTW, TWW4030_WEG_AWXW1_APGA_CTW,
		3, 0x12, 1, anawog_twv),
	SOC_DOUBWE_W_TWV("DAC2 Anawog Pwayback Vowume",
		TWW4030_WEG_AWXW2_APGA_CTW, TWW4030_WEG_AWXW2_APGA_CTW,
		3, 0x12, 1, anawog_twv),
	SOC_DOUBWE_W("DAC1 Anawog Pwayback Switch",
		TWW4030_WEG_AWXW1_APGA_CTW, TWW4030_WEG_AWXW1_APGA_CTW,
		1, 1, 0),
	SOC_DOUBWE_W("DAC2 Anawog Pwayback Switch",
		TWW4030_WEG_AWXW2_APGA_CTW, TWW4030_WEG_AWXW2_APGA_CTW,
		1, 1, 0),

	/* Common voice downwink gain contwows */
	SOC_SINGWE_TWV("DAC Voice Digitaw Downwink Vowume",
		TWW4030_WEG_VWXPGA, 0, 0x31, 0, digitaw_voice_downwink_twv),

	SOC_SINGWE_TWV("DAC Voice Anawog Downwink Vowume",
		TWW4030_WEG_VDW_APGA_CTW, 3, 0x12, 1, anawog_twv),

	SOC_SINGWE("DAC Voice Anawog Downwink Switch",
		TWW4030_WEG_VDW_APGA_CTW, 1, 1, 0),

	/* Sepawate output gain contwows */
	SOC_DOUBWE_W_EXT_TWV("PweDwiv Pwayback Vowume",
		TWW4030_WEG_PWEDW_CTW, TWW4030_WEG_PWEDW_CTW,
		4, 3, 0, snd_soc_get_vowsw_w2_tww4030,
		snd_soc_put_vowsw_w2_tww4030, output_tvw),

	SOC_DOUBWE_EXT_TWV("Headset Pwayback Vowume",
		TWW4030_WEG_HS_GAIN_SET, 0, 2, 3, 0, snd_soc_get_vowsw_tww4030,
		snd_soc_put_vowsw_tww4030, output_tvw),

	SOC_DOUBWE_W_EXT_TWV("Cawkit Pwayback Vowume",
		TWW4030_WEG_PWECKW_CTW, TWW4030_WEG_PWECKW_CTW,
		4, 3, 0, snd_soc_get_vowsw_w2_tww4030,
		snd_soc_put_vowsw_w2_tww4030, output_tvw),

	SOC_SINGWE_EXT_TWV("Eawpiece Pwayback Vowume",
		TWW4030_WEG_EAW_CTW, 4, 3, 0, snd_soc_get_vowsw_tww4030,
		snd_soc_put_vowsw_tww4030, output_eaw_tvw),

	/* Common captuwe gain contwows */
	SOC_DOUBWE_W_TWV("TX1 Digitaw Captuwe Vowume",
		TWW4030_WEG_ATXW1PGA, TWW4030_WEG_ATXW1PGA,
		0, 0x1f, 0, digitaw_captuwe_twv),
	SOC_DOUBWE_W_TWV("TX2 Digitaw Captuwe Vowume",
		TWW4030_WEG_AVTXW2PGA, TWW4030_WEG_AVTXW2PGA,
		0, 0x1f, 0, digitaw_captuwe_twv),

	SOC_DOUBWE_TWV("Anawog Captuwe Vowume", TWW4030_WEG_ANAMIC_GAIN,
		0, 3, 5, 0, input_gain_twv),

	SOC_ENUM("AVADC Cwock Pwiowity", tww4030_avadc_cwk_pwiowity_enum),

	SOC_ENUM("HS wamp deway", tww4030_wampdeway_enum),

	SOC_ENUM("Vibwa H-bwidge mode", tww4030_vibwadiwmode_enum),
	SOC_ENUM("Vibwa H-bwidge diwection", tww4030_vibwadiw_enum),

	SOC_ENUM("Digimic WW Swap", tww4030_digimicswap_enum),
};

static const stwuct snd_soc_dapm_widget tww4030_dapm_widgets[] = {
	/* Weft channew inputs */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("AUXW"),
	SND_SOC_DAPM_INPUT("CAWKITMIC"),
	/* Wight channew inputs */
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("AUXW"),
	/* Digitaw micwophones (Steweo) */
	SND_SOC_DAPM_INPUT("DIGIMIC0"),
	SND_SOC_DAPM_INPUT("DIGIMIC1"),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("EAWPIECE"),
	SND_SOC_DAPM_OUTPUT("PWEDWIVEW"),
	SND_SOC_DAPM_OUTPUT("PWEDWIVEW"),
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("CAWKITW"),
	SND_SOC_DAPM_OUTPUT("CAWKITW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("VIBWA"),

	/* AIF and APWW cwocks fow wunning DAIs (incwuding woopback) */
	SND_SOC_DAPM_OUTPUT("Viwtuaw HiFi OUT"),
	SND_SOC_DAPM_INPUT("Viwtuaw HiFi IN"),
	SND_SOC_DAPM_OUTPUT("Viwtuaw Voice OUT"),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Wight1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Weft1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Wight2", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Weft2", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Voice", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("VAIFIN", "Voice Pwayback", 0,
			    TWW4030_WEG_VOICE_IF, 6, 0),

	/* Anawog bypasses */
	SND_SOC_DAPM_SWITCH("Wight1 Anawog Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_abypassw1_contwow),
	SND_SOC_DAPM_SWITCH("Weft1 Anawog Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_abypassw1_contwow),
	SND_SOC_DAPM_SWITCH("Wight2 Anawog Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_abypassw2_contwow),
	SND_SOC_DAPM_SWITCH("Weft2 Anawog Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_abypassw2_contwow),
	SND_SOC_DAPM_SWITCH("Voice Anawog Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_abypassv_contwow),

	/* Mastew anawog woopback switch */
	SND_SOC_DAPM_SUPPWY("FM Woop Enabwe", TWW4030_WEG_MISC_SET_1, 5, 0,
			    NUWW, 0),

	/* Digitaw bypasses */
	SND_SOC_DAPM_SWITCH("Weft Digitaw Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_dbypassw_contwow),
	SND_SOC_DAPM_SWITCH("Wight Digitaw Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_dbypassw_contwow),
	SND_SOC_DAPM_SWITCH("Voice Digitaw Woopback", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_dbypassv_contwow),

	/* Digitaw mixews, powew contwow fow the physicaw DACs */
	SND_SOC_DAPM_MIXEW("Digitaw W1 Pwayback Mixew",
			TWW4030_WEG_AVDAC_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Digitaw W1 Pwayback Mixew",
			TWW4030_WEG_AVDAC_CTW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Digitaw W2 Pwayback Mixew",
			TWW4030_WEG_AVDAC_CTW, 2, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Digitaw W2 Pwayback Mixew",
			TWW4030_WEG_AVDAC_CTW, 3, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Digitaw Voice Pwayback Mixew",
			TWW4030_WEG_AVDAC_CTW, 4, 0, NUWW, 0),

	/* Anawog mixews, powew contwow fow the physicaw PGAs */
	SND_SOC_DAPM_MIXEW("Anawog W1 Pwayback Mixew",
			TWW4030_WEG_AWXW1_APGA_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Anawog W1 Pwayback Mixew",
			TWW4030_WEG_AWXW1_APGA_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Anawog W2 Pwayback Mixew",
			TWW4030_WEG_AWXW2_APGA_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Anawog W2 Pwayback Mixew",
			TWW4030_WEG_AWXW2_APGA_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Anawog Voice Pwayback Mixew",
			TWW4030_WEG_VDW_APGA_CTW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("APWW Enabwe", SND_SOC_NOPM, 0, 0, apww_event,
			    SND_SOC_DAPM_PWE_PMU|SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY("AIF Enabwe", SND_SOC_NOPM, 0, 0, aif_event,
			    SND_SOC_DAPM_PWE_PMU|SND_SOC_DAPM_POST_PMD),

	/* Output MIXEW contwows */
	/* Eawpiece */
	SND_SOC_DAPM_MIXEW("Eawpiece Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_eawpiece_contwows[0],
			AWWAY_SIZE(tww4030_dapm_eawpiece_contwows)),
	SND_SOC_DAPM_PGA_E("Eawpiece PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, eawpiecepga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* PweDwivW/W */
	SND_SOC_DAPM_MIXEW("PwedwiveW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_pwedwivew_contwows[0],
			AWWAY_SIZE(tww4030_dapm_pwedwivew_contwows)),
	SND_SOC_DAPM_PGA_E("PwedwiveW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, pwedwivewpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXEW("PwedwiveW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_pwedwivew_contwows[0],
			AWWAY_SIZE(tww4030_dapm_pwedwivew_contwows)),
	SND_SOC_DAPM_PGA_E("PwedwiveW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, pwedwivewpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* HeadsetW/W */
	SND_SOC_DAPM_MIXEW("HeadsetW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_hsow_contwows[0],
			AWWAY_SIZE(tww4030_dapm_hsow_contwows)),
	SND_SOC_DAPM_PGA_E("HeadsetW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, headsetwpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXEW("HeadsetW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_hsow_contwows[0],
			AWWAY_SIZE(tww4030_dapm_hsow_contwows)),
	SND_SOC_DAPM_PGA_E("HeadsetW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, headsetwpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* CawkitW/W */
	SND_SOC_DAPM_MIXEW("CawkitW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_cawkitw_contwows[0],
			AWWAY_SIZE(tww4030_dapm_cawkitw_contwows)),
	SND_SOC_DAPM_PGA_E("CawkitW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, cawkitwpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXEW("CawkitW Mixew", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_cawkitw_contwows[0],
			AWWAY_SIZE(tww4030_dapm_cawkitw_contwows)),
	SND_SOC_DAPM_PGA_E("CawkitW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, cawkitwpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),

	/* Output MUX contwows */
	/* HandsfweeW/W */
	SND_SOC_DAPM_MUX("HandsfweeW Mux", SND_SOC_NOPM, 0, 0,
		&tww4030_dapm_handsfweew_contwow),
	SND_SOC_DAPM_SWITCH("HandsfweeW", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_handsfweewmute_contwow),
	SND_SOC_DAPM_PGA_E("HandsfweeW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, handsfweewpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("HandsfweeW Mux", SND_SOC_NOPM, 5, 0,
		&tww4030_dapm_handsfweew_contwow),
	SND_SOC_DAPM_SWITCH("HandsfweeW", SND_SOC_NOPM, 0, 0,
			&tww4030_dapm_handsfweewmute_contwow),
	SND_SOC_DAPM_PGA_E("HandsfweeW PGA", SND_SOC_NOPM,
			0, 0, NUWW, 0, handsfweewpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* Vibwa */
	SND_SOC_DAPM_MUX_E("Vibwa Mux", TWW4030_WEG_VIBWA_CTW, 0, 0,
			   &tww4030_dapm_vibwa_contwow, vibwamux_event,
			   SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_MUX("Vibwa Woute", SND_SOC_NOPM, 0, 0,
		&tww4030_dapm_vibwapath_contwow),

	/* Intwoducing fouw viwtuaw ADC, since TWW4030 have fouw channew fow
	   captuwe */
	SND_SOC_DAPM_ADC("ADC Viwtuaw Weft1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Viwtuaw Wight1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Viwtuaw Weft2", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Viwtuaw Wight2", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("VAIFOUT", "Voice Captuwe", 0,
			     TWW4030_WEG_VOICE_IF, 5, 0),

	/* Anawog/Digitaw mic path sewection.
	   TX1 Weft/Wight: eithew anawog Weft/Wight ow Digimic0
	   TX2 Weft/Wight: eithew anawog Weft/Wight ow Digimic1 */
	SND_SOC_DAPM_MUX("TX1 Captuwe Woute", SND_SOC_NOPM, 0, 0,
		&tww4030_dapm_micpathtx1_contwow),
	SND_SOC_DAPM_MUX("TX2 Captuwe Woute", SND_SOC_NOPM, 0, 0,
		&tww4030_dapm_micpathtx2_contwow),

	/* Anawog input mixews fow the captuwe ampwifiews */
	SND_SOC_DAPM_MIXEW("Anawog Weft",
		TWW4030_WEG_ANAMICW, 4, 0,
		&tww4030_dapm_anawogwmic_contwows[0],
		AWWAY_SIZE(tww4030_dapm_anawogwmic_contwows)),
	SND_SOC_DAPM_MIXEW("Anawog Wight",
		TWW4030_WEG_ANAMICW, 4, 0,
		&tww4030_dapm_anawogwmic_contwows[0],
		AWWAY_SIZE(tww4030_dapm_anawogwmic_contwows)),

	SND_SOC_DAPM_PGA("ADC Physicaw Weft",
		TWW4030_WEG_AVADC_CTW, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ADC Physicaw Wight",
		TWW4030_WEG_AVADC_CTW, 1, 0, NUWW, 0),

	SND_SOC_DAPM_PGA_E("Digimic0 Enabwe",
		TWW4030_WEG_ADCMICSEW, 1, 0, NUWW, 0,
		digimic_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("Digimic1 Enabwe",
		TWW4030_WEG_ADCMICSEW, 3, 0, NUWW, 0,
		digimic_event, SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPWY("micbias1 sewect", TWW4030_WEG_MICBIAS_CTW, 5, 0,
			    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("micbias2 sewect", TWW4030_WEG_MICBIAS_CTW, 6, 0,
			    NUWW, 0),

	/* Micwophone bias */
	SND_SOC_DAPM_SUPPWY("Mic Bias 1",
			    TWW4030_WEG_MICBIAS_CTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Bias 2",
			    TWW4030_WEG_MICBIAS_CTW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headset Mic Bias",
			    TWW4030_WEG_MICBIAS_CTW, 2, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("VIF Enabwe", TWW4030_WEG_VOICE_IF, 0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	/* Stweam -> DAC mapping */
	{"DAC Wight1", NUWW, "HiFi Pwayback"},
	{"DAC Weft1", NUWW, "HiFi Pwayback"},
	{"DAC Wight2", NUWW, "HiFi Pwayback"},
	{"DAC Weft2", NUWW, "HiFi Pwayback"},
	{"DAC Voice", NUWW, "VAIFIN"},

	/* ADC -> Stweam mapping */
	{"HiFi Captuwe", NUWW, "ADC Viwtuaw Weft1"},
	{"HiFi Captuwe", NUWW, "ADC Viwtuaw Wight1"},
	{"HiFi Captuwe", NUWW, "ADC Viwtuaw Weft2"},
	{"HiFi Captuwe", NUWW, "ADC Viwtuaw Wight2"},
	{"VAIFOUT", NUWW, "ADC Viwtuaw Weft2"},
	{"VAIFOUT", NUWW, "ADC Viwtuaw Wight2"},
	{"VAIFOUT", NUWW, "VIF Enabwe"},

	{"Digitaw W1 Pwayback Mixew", NUWW, "DAC Weft1"},
	{"Digitaw W1 Pwayback Mixew", NUWW, "DAC Wight1"},
	{"Digitaw W2 Pwayback Mixew", NUWW, "DAC Weft2"},
	{"Digitaw W2 Pwayback Mixew", NUWW, "DAC Wight2"},
	{"Digitaw Voice Pwayback Mixew", NUWW, "DAC Voice"},

	/* Suppwy fow the digitaw pawt (APWW) */
	{"Digitaw Voice Pwayback Mixew", NUWW, "APWW Enabwe"},

	{"DAC Weft1", NUWW, "AIF Enabwe"},
	{"DAC Wight1", NUWW, "AIF Enabwe"},
	{"DAC Weft2", NUWW, "AIF Enabwe"},
	{"DAC Wight1", NUWW, "AIF Enabwe"},
	{"DAC Voice", NUWW, "VIF Enabwe"},

	{"Digitaw W2 Pwayback Mixew", NUWW, "AIF Enabwe"},
	{"Digitaw W2 Pwayback Mixew", NUWW, "AIF Enabwe"},

	{"Anawog W1 Pwayback Mixew", NUWW, "Digitaw W1 Pwayback Mixew"},
	{"Anawog W1 Pwayback Mixew", NUWW, "Digitaw W1 Pwayback Mixew"},
	{"Anawog W2 Pwayback Mixew", NUWW, "Digitaw W2 Pwayback Mixew"},
	{"Anawog W2 Pwayback Mixew", NUWW, "Digitaw W2 Pwayback Mixew"},
	{"Anawog Voice Pwayback Mixew", NUWW, "Digitaw Voice Pwayback Mixew"},

	/* Intewnaw pwayback woutings */
	/* Eawpiece */
	{"Eawpiece Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"Eawpiece Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"Eawpiece Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"Eawpiece Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"Eawpiece PGA", NUWW, "Eawpiece Mixew"},
	/* PweDwivW */
	{"PwedwiveW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"PwedwiveW PGA", NUWW, "PwedwiveW Mixew"},
	/* PweDwivW */
	{"PwedwiveW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"PwedwiveW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"PwedwiveW PGA", NUWW, "PwedwiveW Mixew"},
	/* HeadsetW */
	{"HeadsetW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"HeadsetW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"HeadsetW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HeadsetW PGA", NUWW, "HeadsetW Mixew"},
	/* HeadsetW */
	{"HeadsetW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"HeadsetW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"HeadsetW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HeadsetW PGA", NUWW, "HeadsetW Mixew"},
	/* CawkitW */
	{"CawkitW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"CawkitW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"CawkitW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"CawkitW PGA", NUWW, "CawkitW Mixew"},
	/* CawkitW */
	{"CawkitW Mixew", "Voice", "Anawog Voice Pwayback Mixew"},
	{"CawkitW Mixew", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"CawkitW Mixew", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"CawkitW PGA", NUWW, "CawkitW Mixew"},
	/* HandsfweeW */
	{"HandsfweeW Mux", "Voice", "Anawog Voice Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HandsfweeW", "Switch", "HandsfweeW Mux"},
	{"HandsfweeW PGA", NUWW, "HandsfweeW"},
	/* HandsfweeW */
	{"HandsfweeW Mux", "Voice", "Anawog Voice Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW1", "Anawog W1 Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HandsfweeW Mux", "AudioW2", "Anawog W2 Pwayback Mixew"},
	{"HandsfweeW", "Switch", "HandsfweeW Mux"},
	{"HandsfweeW PGA", NUWW, "HandsfweeW"},
	/* Vibwa */
	{"Vibwa Mux", "AudioW1", "DAC Weft1"},
	{"Vibwa Mux", "AudioW1", "DAC Wight1"},
	{"Vibwa Mux", "AudioW2", "DAC Weft2"},
	{"Vibwa Mux", "AudioW2", "DAC Wight2"},

	/* outputs */
	/* Must be awways connected (fow AIF and APWW) */
	{"Viwtuaw HiFi OUT", NUWW, "DAC Weft1"},
	{"Viwtuaw HiFi OUT", NUWW, "DAC Wight1"},
	{"Viwtuaw HiFi OUT", NUWW, "DAC Weft2"},
	{"Viwtuaw HiFi OUT", NUWW, "DAC Wight2"},
	/* Must be awways connected (fow APWW) */
	{"Viwtuaw Voice OUT", NUWW, "Digitaw Voice Pwayback Mixew"},
	/* Physicaw outputs */
	{"EAWPIECE", NUWW, "Eawpiece PGA"},
	{"PWEDWIVEW", NUWW, "PwedwiveW PGA"},
	{"PWEDWIVEW", NUWW, "PwedwiveW PGA"},
	{"HSOW", NUWW, "HeadsetW PGA"},
	{"HSOW", NUWW, "HeadsetW PGA"},
	{"CAWKITW", NUWW, "CawkitW PGA"},
	{"CAWKITW", NUWW, "CawkitW PGA"},
	{"HFW", NUWW, "HandsfweeW PGA"},
	{"HFW", NUWW, "HandsfweeW PGA"},
	{"Vibwa Woute", "Audio", "Vibwa Mux"},
	{"VIBWA", NUWW, "Vibwa Woute"},

	/* Captuwe path */
	/* Must be awways connected (fow AIF and APWW) */
	{"ADC Viwtuaw Weft1", NUWW, "Viwtuaw HiFi IN"},
	{"ADC Viwtuaw Wight1", NUWW, "Viwtuaw HiFi IN"},
	{"ADC Viwtuaw Weft2", NUWW, "Viwtuaw HiFi IN"},
	{"ADC Viwtuaw Wight2", NUWW, "Viwtuaw HiFi IN"},
	/* Physicaw inputs */
	{"Anawog Weft", "Main Mic Captuwe Switch", "MAINMIC"},
	{"Anawog Weft", "Headset Mic Captuwe Switch", "HSMIC"},
	{"Anawog Weft", "AUXW Captuwe Switch", "AUXW"},
	{"Anawog Weft", "Cawkit Mic Captuwe Switch", "CAWKITMIC"},

	{"Anawog Wight", "Sub Mic Captuwe Switch", "SUBMIC"},
	{"Anawog Wight", "AUXW Captuwe Switch", "AUXW"},

	{"ADC Physicaw Weft", NUWW, "Anawog Weft"},
	{"ADC Physicaw Wight", NUWW, "Anawog Wight"},

	{"Digimic0 Enabwe", NUWW, "DIGIMIC0"},
	{"Digimic1 Enabwe", NUWW, "DIGIMIC1"},

	{"DIGIMIC0", NUWW, "micbias1 sewect"},
	{"DIGIMIC1", NUWW, "micbias2 sewect"},

	/* TX1 Weft captuwe path */
	{"TX1 Captuwe Woute", "Anawog", "ADC Physicaw Weft"},
	{"TX1 Captuwe Woute", "Digimic0", "Digimic0 Enabwe"},
	/* TX1 Wight captuwe path */
	{"TX1 Captuwe Woute", "Anawog", "ADC Physicaw Wight"},
	{"TX1 Captuwe Woute", "Digimic0", "Digimic0 Enabwe"},
	/* TX2 Weft captuwe path */
	{"TX2 Captuwe Woute", "Anawog", "ADC Physicaw Weft"},
	{"TX2 Captuwe Woute", "Digimic1", "Digimic1 Enabwe"},
	/* TX2 Wight captuwe path */
	{"TX2 Captuwe Woute", "Anawog", "ADC Physicaw Wight"},
	{"TX2 Captuwe Woute", "Digimic1", "Digimic1 Enabwe"},

	{"ADC Viwtuaw Weft1", NUWW, "TX1 Captuwe Woute"},
	{"ADC Viwtuaw Wight1", NUWW, "TX1 Captuwe Woute"},
	{"ADC Viwtuaw Weft2", NUWW, "TX2 Captuwe Woute"},
	{"ADC Viwtuaw Wight2", NUWW, "TX2 Captuwe Woute"},

	{"ADC Viwtuaw Weft1", NUWW, "AIF Enabwe"},
	{"ADC Viwtuaw Wight1", NUWW, "AIF Enabwe"},
	{"ADC Viwtuaw Weft2", NUWW, "AIF Enabwe"},
	{"ADC Viwtuaw Wight2", NUWW, "AIF Enabwe"},

	/* Anawog bypass woutes */
	{"Wight1 Anawog Woopback", "Switch", "Anawog Wight"},
	{"Weft1 Anawog Woopback", "Switch", "Anawog Weft"},
	{"Wight2 Anawog Woopback", "Switch", "Anawog Wight"},
	{"Weft2 Anawog Woopback", "Switch", "Anawog Weft"},
	{"Voice Anawog Woopback", "Switch", "Anawog Weft"},

	/* Suppwy fow the Anawog woopbacks */
	{"Wight1 Anawog Woopback", NUWW, "FM Woop Enabwe"},
	{"Weft1 Anawog Woopback", NUWW, "FM Woop Enabwe"},
	{"Wight2 Anawog Woopback", NUWW, "FM Woop Enabwe"},
	{"Weft2 Anawog Woopback", NUWW, "FM Woop Enabwe"},
	{"Voice Anawog Woopback", NUWW, "FM Woop Enabwe"},

	{"Anawog W1 Pwayback Mixew", NUWW, "Wight1 Anawog Woopback"},
	{"Anawog W1 Pwayback Mixew", NUWW, "Weft1 Anawog Woopback"},
	{"Anawog W2 Pwayback Mixew", NUWW, "Wight2 Anawog Woopback"},
	{"Anawog W2 Pwayback Mixew", NUWW, "Weft2 Anawog Woopback"},
	{"Anawog Voice Pwayback Mixew", NUWW, "Voice Anawog Woopback"},

	/* Digitaw bypass woutes */
	{"Wight Digitaw Woopback", "Vowume", "TX1 Captuwe Woute"},
	{"Weft Digitaw Woopback", "Vowume", "TX1 Captuwe Woute"},
	{"Voice Digitaw Woopback", "Vowume", "TX2 Captuwe Woute"},

	{"Digitaw W2 Pwayback Mixew", NUWW, "Wight Digitaw Woopback"},
	{"Digitaw W2 Pwayback Mixew", NUWW, "Weft Digitaw Woopback"},
	{"Digitaw Voice Pwayback Mixew", NUWW, "Voice Digitaw Woopback"},

};

static int tww4030_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			tww4030_codec_enabwe(component, 1);
		bweak;
	case SND_SOC_BIAS_OFF:
		tww4030_codec_enabwe(component, 0);
		bweak;
	}

	wetuwn 0;
}

static void tww4030_constwaints(stwuct tww4030_pwiv *tww4030,
				stwuct snd_pcm_substweam *mst_substweam)
{
	stwuct snd_pcm_substweam *swv_substweam;

	/* Pick the stweam, which need to be constwained */
	if (mst_substweam == tww4030->mastew_substweam)
		swv_substweam = tww4030->swave_substweam;
	ewse if (mst_substweam == tww4030->swave_substweam)
		swv_substweam = tww4030->mastew_substweam;
	ewse /* This shouwd not happen.. */
		wetuwn;

	/* Set the constwaints accowding to the awweady configuwed stweam */
	snd_pcm_hw_constwaint_singwe(swv_substweam->wuntime,
				SNDWV_PCM_HW_PAWAM_WATE,
				tww4030->wate);

	snd_pcm_hw_constwaint_singwe(swv_substweam->wuntime,
				SNDWV_PCM_HW_PAWAM_SAMPWE_BITS,
				tww4030->sampwe_bits);

	snd_pcm_hw_constwaint_singwe(swv_substweam->wuntime,
				SNDWV_PCM_HW_PAWAM_CHANNEWS,
				tww4030->channews);
}

/* In case of 4 channew mode, the WX1 W/W fow pwayback and the TX2 W/W fow
 * captuwe has to be enabwed/disabwed. */
static void tww4030_tdm_enabwe(stwuct snd_soc_component *component, int diwection,
			       int enabwe)
{
	u8 weg, mask;

	weg = tww4030_wead(component, TWW4030_WEG_OPTION);

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		mask = TWW4030_AWXW1_VWX_EN | TWW4030_AWXW1_EN;
	ewse
		mask = TWW4030_ATXW2_VTXW_EN | TWW4030_ATXW2_VTXW_EN;

	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;

	tww4030_wwite(component, TWW4030_WEG_OPTION, weg);
}

static int tww4030_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	if (tww4030->mastew_substweam) {
		tww4030->swave_substweam = substweam;
		/* The DAI has one configuwation fow pwayback and captuwe, so
		 * if the DAI has been awweady configuwed then constwain this
		 * substweam to match it. */
		if (tww4030->configuwed)
			tww4030_constwaints(tww4030, tww4030->mastew_substweam);
	} ewse {
		if (!(tww4030_wead(component, TWW4030_WEG_CODEC_MODE) &
			TWW4030_OPTION_1)) {
			/* In option2 4 channew is not suppowted, set the
			 * constwaint fow the fiwst stweam fow channews, the
			 * second stweam wiww 'inhewit' this cosntwaint */
			snd_pcm_hw_constwaint_singwe(substweam->wuntime,
						     SNDWV_PCM_HW_PAWAM_CHANNEWS,
						     2);
		}
		tww4030->mastew_substweam = substweam;
	}

	wetuwn 0;
}

static void tww4030_shutdown(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	if (tww4030->mastew_substweam == substweam)
		tww4030->mastew_substweam = tww4030->swave_substweam;

	tww4030->swave_substweam = NUWW;

	/* If aww stweams awe cwosed, ow the wemaining stweam has not yet
	 * been configuwed than set the DAI as not configuwed. */
	if (!tww4030->mastew_substweam)
		tww4030->configuwed = 0;
	 ewse if (!tww4030->mastew_substweam->wuntime->channews)
		tww4030->configuwed = 0;

	 /* If the cwosing substweam had 4 channew, do the necessawy cweanup */
	if (substweam->wuntime->channews == 4)
		tww4030_tdm_enabwe(component, substweam->stweam, 0);
}

static int tww4030_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 mode, owd_mode, fowmat, owd_fowmat;

	 /* If the substweam has 4 channew, do the necessawy setup */
	if (pawams_channews(pawams) == 4) {
		fowmat = tww4030_wead(component, TWW4030_WEG_AUDIO_IF);
		mode = tww4030_wead(component, TWW4030_WEG_CODEC_MODE);

		/* Safety check: awe we in the cowwect opewating mode and
		 * the intewface is in TDM mode? */
		if ((mode & TWW4030_OPTION_1) &&
		    ((fowmat & TWW4030_AIF_FOWMAT) == TWW4030_AIF_FOWMAT_TDM))
			tww4030_tdm_enabwe(component, substweam->stweam, 1);
		ewse
			wetuwn -EINVAW;
	}

	if (tww4030->configuwed)
		/* Ignowing hw_pawams fow awweady configuwed DAI */
		wetuwn 0;

	/* bit wate */
	owd_mode = tww4030_wead(component,
				TWW4030_WEG_CODEC_MODE) & ~TWW4030_CODECPDZ;
	mode = owd_mode & ~TWW4030_APWW_WATE;

	switch (pawams_wate(pawams)) {
	case 8000:
		mode |= TWW4030_APWW_WATE_8000;
		bweak;
	case 11025:
		mode |= TWW4030_APWW_WATE_11025;
		bweak;
	case 12000:
		mode |= TWW4030_APWW_WATE_12000;
		bweak;
	case 16000:
		mode |= TWW4030_APWW_WATE_16000;
		bweak;
	case 22050:
		mode |= TWW4030_APWW_WATE_22050;
		bweak;
	case 24000:
		mode |= TWW4030_APWW_WATE_24000;
		bweak;
	case 32000:
		mode |= TWW4030_APWW_WATE_32000;
		bweak;
	case 44100:
		mode |= TWW4030_APWW_WATE_44100;
		bweak;
	case 48000:
		mode |= TWW4030_APWW_WATE_48000;
		bweak;
	case 96000:
		mode |= TWW4030_APWW_WATE_96000;
		bweak;
	defauwt:
		dev_eww(component->dev, "%s: unknown wate %d\n", __func__,
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* sampwe size */
	owd_fowmat = tww4030_wead(component, TWW4030_WEG_AUDIO_IF);
	fowmat = owd_fowmat;
	fowmat &= ~TWW4030_DATA_WIDTH;
	switch (pawams_width(pawams)) {
	case 16:
		fowmat |= TWW4030_DATA_WIDTH_16S_16W;
		bweak;
	case 32:
		fowmat |= TWW4030_DATA_WIDTH_32S_24W;
		bweak;
	defauwt:
		dev_eww(component->dev, "%s: unsuppowted bits/sampwe %d\n",
			__func__, pawams_width(pawams));
		wetuwn -EINVAW;
	}

	if (fowmat != owd_fowmat || mode != owd_mode) {
		if (tww4030->codec_powewed) {
			/*
			 * If the codec is powewed, than we need to toggwe the
			 * codec powew.
			 */
			tww4030_codec_enabwe(component, 0);
			tww4030_wwite(component, TWW4030_WEG_CODEC_MODE, mode);
			tww4030_wwite(component, TWW4030_WEG_AUDIO_IF, fowmat);
			tww4030_codec_enabwe(component, 1);
		} ewse {
			tww4030_wwite(component, TWW4030_WEG_CODEC_MODE, mode);
			tww4030_wwite(component, TWW4030_WEG_AUDIO_IF, fowmat);
		}
	}

	/* Stowe the impowtant pawametews fow the DAI configuwation and set
	 * the DAI as configuwed */
	tww4030->configuwed = 1;
	tww4030->wate = pawams_wate(pawams);
	tww4030->sampwe_bits = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_SAMPWE_BITS)->min;
	tww4030->channews = pawams_channews(pawams);

	/* If both pwayback and captuwe stweams awe open, and one of them
	 * is setting the hw pawametews wight now (since we awe hewe), set
	 * constwaints to the othew stweam to match the cuwwent one. */
	if (tww4030->swave_substweam)
		tww4030_constwaints(tww4030, substweam);

	wetuwn 0;
}

static int tww4030_set_dai_syscwk(stwuct snd_soc_dai *codec_dai, int cwk_id,
				  unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 19200000:
	case 26000000:
	case 38400000:
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted HFCWKIN: %u\n", fweq);
		wetuwn -EINVAW;
	}

	if ((fweq / 1000) != tww4030->syscwk) {
		dev_eww(component->dev,
			"Mismatch in HFCWKIN: %u (configuwed: %u)\n",
			fweq, tww4030->syscwk * 1000);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tww4030_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 owd_fowmat, fowmat;

	/* get fowmat */
	owd_fowmat = tww4030_wead(component, TWW4030_WEG_AUDIO_IF);
	fowmat = owd_fowmat;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		fowmat &= ~(TWW4030_AIF_SWAVE_EN);
		fowmat &= ~(TWW4030_CWK256FS_EN);
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		fowmat |= TWW4030_AIF_SWAVE_EN;
		fowmat |= TWW4030_CWK256FS_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	fowmat &= ~TWW4030_AIF_FOWMAT;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat |= TWW4030_AIF_FOWMAT_CODEC;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		fowmat |= TWW4030_AIF_FOWMAT_TDM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fowmat != owd_fowmat) {
		if (tww4030->codec_powewed) {
			/*
			 * If the codec is powewed, than we need to toggwe the
			 * codec powew.
			 */
			tww4030_codec_enabwe(component, 0);
			tww4030_wwite(component, TWW4030_WEG_AUDIO_IF, fowmat);
			tww4030_codec_enabwe(component, 1);
		} ewse {
			tww4030_wwite(component, TWW4030_WEG_AUDIO_IF, fowmat);
		}
	}

	wetuwn 0;
}

static int tww4030_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	stwuct snd_soc_component *component = dai->component;
	u8 weg = tww4030_wead(component, TWW4030_WEG_AUDIO_IF);

	if (twistate)
		weg |= TWW4030_AIF_TWI_EN;
	ewse
		weg &= ~TWW4030_AIF_TWI_EN;

	wetuwn tww4030_wwite(component, TWW4030_WEG_AUDIO_IF, weg);
}

/* In case of voice mode, the WX1 W(VWX) fow downwink and the TX2 W/W
 * (VTXW, VTXW) fow upwink has to be enabwed/disabwed. */
static void tww4030_voice_enabwe(stwuct snd_soc_component *component, int diwection,
				 int enabwe)
{
	u8 weg, mask;

	weg = tww4030_wead(component, TWW4030_WEG_OPTION);

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		mask = TWW4030_AWXW1_VWX_EN;
	ewse
		mask = TWW4030_ATXW2_VTXW_EN | TWW4030_ATXW2_VTXW_EN;

	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;

	tww4030_wwite(component, TWW4030_WEG_OPTION, weg);
}

static int tww4030_voice_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 mode;

	/* If the system mastew cwock is not 26MHz, the voice PCM intewface is
	 * not avaiwabwe.
	 */
	if (tww4030->syscwk != 26000) {
		dev_eww(component->dev,
			"%s: HFCWKIN is %u KHz, voice intewface needs 26MHz\n",
			__func__, tww4030->syscwk);
		wetuwn -EINVAW;
	}

	/* If the codec mode is not option2, the voice PCM intewface is not
	 * avaiwabwe.
	 */
	mode = tww4030_wead(component, TWW4030_WEG_CODEC_MODE)
		& TWW4030_OPT_MODE;

	if (mode != TWW4030_OPTION_2) {
		dev_eww(component->dev, "%s: the codec mode is not option2\n",
			__func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void tww4030_voice_shutdown(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	/* Enabwe voice digitaw fiwtews */
	tww4030_voice_enabwe(component, substweam->stweam, 0);
}

static int tww4030_voice_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 owd_mode, mode;

	/* Enabwe voice digitaw fiwtews */
	tww4030_voice_enabwe(component, substweam->stweam, 1);

	/* bit wate */
	owd_mode = tww4030_wead(component,
				TWW4030_WEG_CODEC_MODE) & ~TWW4030_CODECPDZ;
	mode = owd_mode;

	switch (pawams_wate(pawams)) {
	case 8000:
		mode &= ~(TWW4030_SEW_16K);
		bweak;
	case 16000:
		mode |= TWW4030_SEW_16K;
		bweak;
	defauwt:
		dev_eww(component->dev, "%s: unknown wate %d\n", __func__,
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	if (mode != owd_mode) {
		if (tww4030->codec_powewed) {
			/*
			 * If the codec is powewed, than we need to toggwe the
			 * codec powew.
			 */
			tww4030_codec_enabwe(component, 0);
			tww4030_wwite(component, TWW4030_WEG_CODEC_MODE, mode);
			tww4030_codec_enabwe(component, 1);
		} ewse {
			tww4030_wwite(component, TWW4030_WEG_CODEC_MODE, mode);
		}
	}

	wetuwn 0;
}

static int tww4030_voice_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
					int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);

	if (fweq != 26000000) {
		dev_eww(component->dev,
			"%s: HFCWKIN is %u KHz, voice intewface needs 26MHz\n",
			__func__, fweq / 1000);
		wetuwn -EINVAW;
	}
	if ((fweq / 1000) != tww4030->syscwk) {
		dev_eww(component->dev,
			"Mismatch in HFCWKIN: %u (configuwed: %u)\n",
			fweq, tww4030->syscwk * 1000);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int tww4030_voice_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				     unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	u8 owd_fowmat, fowmat;

	/* get fowmat */
	owd_fowmat = tww4030_wead(component, TWW4030_WEG_VOICE_IF);
	fowmat = owd_fowmat;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		fowmat &= ~(TWW4030_VIF_SWAVE_EN);
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		fowmat |= TWW4030_VIF_SWAVE_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		fowmat &= ~(TWW4030_VIF_FOWMAT);
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		fowmat |= TWW4030_VIF_FOWMAT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fowmat != owd_fowmat) {
		if (tww4030->codec_powewed) {
			/*
			 * If the codec is powewed, than we need to toggwe the
			 * codec powew.
			 */
			tww4030_codec_enabwe(component, 0);
			tww4030_wwite(component, TWW4030_WEG_VOICE_IF, fowmat);
			tww4030_codec_enabwe(component, 1);
		} ewse {
			tww4030_wwite(component, TWW4030_WEG_VOICE_IF, fowmat);
		}
	}

	wetuwn 0;
}

static int tww4030_voice_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	stwuct snd_soc_component *component = dai->component;
	u8 weg = tww4030_wead(component, TWW4030_WEG_VOICE_IF);

	if (twistate)
		weg |= TWW4030_VIF_TWI_EN;
	ewse
		weg &= ~TWW4030_VIF_TWI_EN;

	wetuwn tww4030_wwite(component, TWW4030_WEG_VOICE_IF, weg);
}

#define TWW4030_WATES	 (SNDWV_PCM_WATE_8000_48000)
#define TWW4030_FOWMATS	 (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops tww4030_dai_hifi_ops = {
	.stawtup	= tww4030_stawtup,
	.shutdown	= tww4030_shutdown,
	.hw_pawams	= tww4030_hw_pawams,
	.set_syscwk	= tww4030_set_dai_syscwk,
	.set_fmt	= tww4030_set_dai_fmt,
	.set_twistate	= tww4030_set_twistate,
};

static const stwuct snd_soc_dai_ops tww4030_dai_voice_ops = {
	.stawtup	= tww4030_voice_stawtup,
	.shutdown	= tww4030_voice_shutdown,
	.hw_pawams	= tww4030_voice_hw_pawams,
	.set_syscwk	= tww4030_voice_set_dai_syscwk,
	.set_fmt	= tww4030_voice_set_dai_fmt,
	.set_twistate	= tww4030_voice_set_twistate,
};

static stwuct snd_soc_dai_dwivew tww4030_dai[] = {
{
	.name = "tww4030-hifi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 2,
		.channews_max = 4,
		.wates = TWW4030_WATES | SNDWV_PCM_WATE_96000,
		.fowmats = TWW4030_FOWMATS,
		.sig_bits = 24,},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 2,
		.channews_max = 4,
		.wates = TWW4030_WATES,
		.fowmats = TWW4030_FOWMATS,
		.sig_bits = 24,},
	.ops = &tww4030_dai_hifi_ops,
},
{
	.name = "tww4030-voice",
	.pwayback = {
		.stweam_name = "Voice Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.stweam_name = "Voice Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &tww4030_dai_voice_ops,
},
};

static int tww4030_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct tww4030_pwiv *tww4030;

	tww4030 = devm_kzawwoc(component->dev, sizeof(stwuct tww4030_pwiv),
			       GFP_KEWNEW);
	if (!tww4030)
		wetuwn -ENOMEM;
	snd_soc_component_set_dwvdata(component, tww4030);
	/* Set the defauwts, and powew up the codec */
	tww4030->syscwk = tww4030_audio_get_mcwk() / 1000;

	tww4030_init_chip(component);

	wetuwn 0;
}

static void tww4030_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct tww4030_pwiv *tww4030 = snd_soc_component_get_dwvdata(component);
	stwuct tww4030_boawd_pawams *boawd_pawams = tww4030->boawd_pawams;

	if (boawd_pawams && boawd_pawams->hs_extmute &&
	    gpio_is_vawid(boawd_pawams->hs_extmute_gpio))
		gpio_fwee(boawd_pawams->hs_extmute_gpio);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_tww4030 = {
	.pwobe			= tww4030_soc_pwobe,
	.wemove			= tww4030_soc_wemove,
	.wead			= tww4030_wead,
	.wwite			= tww4030_wwite,
	.set_bias_wevew		= tww4030_set_bias_wevew,
	.contwows		= tww4030_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tww4030_snd_contwows),
	.dapm_widgets		= tww4030_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tww4030_dapm_widgets),
	.dapm_woutes		= intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(intewcon),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int tww4030_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &soc_component_dev_tww4030,
				      tww4030_dai, AWWAY_SIZE(tww4030_dai));
}

MODUWE_AWIAS("pwatfowm:tww4030-codec");

static stwuct pwatfowm_dwivew tww4030_codec_dwivew = {
	.pwobe		= tww4030_codec_pwobe,
	.dwivew		= {
		.name	= "tww4030-codec",
	},
};

moduwe_pwatfowm_dwivew(tww4030_codec_dwivew);

MODUWE_DESCWIPTION("ASoC TWW4030 codec dwivew");
MODUWE_AUTHOW("Steve Sakoman");
MODUWE_WICENSE("GPW");
