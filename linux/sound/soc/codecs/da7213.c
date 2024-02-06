// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DA7213 AWSA SoC Codec Dwivew
 *
 * Copywight (c) 2013 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 * Based on DA9055 AWSA SoC codec dwivew.
 */

#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude <sound/da7213.h>
#incwude "da7213.h"


/* Gain and Vowume */
static const DECWAWE_TWV_DB_WANGE(aux_vow_twv,
	/* -54dB */
	0x0, 0x11, TWV_DB_SCAWE_ITEM(-5400, 0, 0),
	/* -52.5dB to 15dB */
	0x12, 0x3f, TWV_DB_SCAWE_ITEM(-5250, 150, 0)
);

static const DECWAWE_TWV_DB_WANGE(digitaw_gain_twv,
	0x0, 0x07, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* -78dB to 12dB */
	0x08, 0x7f, TWV_DB_SCAWE_ITEM(-7800, 75, 0)
);

static const DECWAWE_TWV_DB_WANGE(awc_anawog_gain_twv,
	0x0, 0x0, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* 0dB to 36dB */
	0x01, 0x07, TWV_DB_SCAWE_ITEM(0, 600, 0)
);

static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(mixin_gain_twv, -450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(eq_gain_twv, -1050, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(hp_vow_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wineout_vow_twv, -4800, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_thweshowd_twv, -9450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_gain_twv, 0, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(da7213_tonegen_gain_twv, -4500, 300, 0);

/* ADC and DAC voice mode (8kHz) high pass cutoff vawue */
static const chaw * const da7213_voice_hpf_cownew_txt[] = {
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_voice_hpf_cownew,
			    DA7213_DAC_FIWTEWS1,
			    DA7213_VOICE_HPF_COWNEW_SHIFT,
			    da7213_voice_hpf_cownew_txt);

static SOC_ENUM_SINGWE_DECW(da7213_adc_voice_hpf_cownew,
			    DA7213_ADC_FIWTEWS1,
			    DA7213_VOICE_HPF_COWNEW_SHIFT,
			    da7213_voice_hpf_cownew_txt);

/* ADC and DAC high pass fiwtew cutoff vawue */
static const chaw * const da7213_audio_hpf_cownew_txt[] = {
	"Fs/24000", "Fs/12000", "Fs/6000", "Fs/3000"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_audio_hpf_cownew,
			    DA7213_DAC_FIWTEWS1
			    , DA7213_AUDIO_HPF_COWNEW_SHIFT,
			    da7213_audio_hpf_cownew_txt);

static SOC_ENUM_SINGWE_DECW(da7213_adc_audio_hpf_cownew,
			    DA7213_ADC_FIWTEWS1,
			    DA7213_AUDIO_HPF_COWNEW_SHIFT,
			    da7213_audio_hpf_cownew_txt);

static const chaw * const da7213_tonegen_dtmf_key_txt[] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D",
	"*", "#"
};

static const stwuct soc_enum da7213_tonegen_dtmf_key =
	SOC_ENUM_SINGWE(DA7213_TONE_GEN_CFG1, DA7213_DTMF_WEG_SHIFT,
			DA7213_DTMF_WEG_MAX, da7213_tonegen_dtmf_key_txt);

static const chaw * const da7213_tonegen_swg_sew_txt[] = {
	"Sum", "SWG1", "SWG2", "Sum"
};

static const stwuct soc_enum da7213_tonegen_swg_sew =
	SOC_ENUM_SINGWE(DA7213_TONE_GEN_CFG2, DA7213_SWG_SEW_SHIFT,
			DA7213_SWG_SEW_MAX, da7213_tonegen_swg_sew_txt);

/* Gain wamping wate vawue */
static const chaw * const da7213_gain_wamp_wate_txt[] = {
	"nominaw wate * 8", "nominaw wate * 16", "nominaw wate / 16",
	"nominaw wate / 32"
};

static SOC_ENUM_SINGWE_DECW(da7213_gain_wamp_wate,
			    DA7213_GAIN_WAMP_CTWW,
			    DA7213_GAIN_WAMP_WATE_SHIFT,
			    da7213_gain_wamp_wate_txt);

/* DAC noise gate setup time vawue */
static const chaw * const da7213_dac_ng_setup_time_txt[] = {
	"256 sampwes", "512 sampwes", "1024 sampwes", "2048 sampwes"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_ng_setup_time,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_SETUP_TIME_SHIFT,
			    da7213_dac_ng_setup_time_txt);

/* DAC noise gate wampup wate vawue */
static const chaw * const da7213_dac_ng_wampup_txt[] = {
	"0.02 ms/dB", "0.16 ms/dB"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_ng_wampup_wate,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_WAMPUP_WATE_SHIFT,
			    da7213_dac_ng_wampup_txt);

/* DAC noise gate wampdown wate vawue */
static const chaw * const da7213_dac_ng_wampdown_txt[] = {
	"0.64 ms/dB", "20.48 ms/dB"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_ng_wampdown_wate,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_WAMPDN_WATE_SHIFT,
			    da7213_dac_ng_wampdown_txt);

/* DAC soft mute wate vawue */
static const chaw * const da7213_dac_soft_mute_wate_txt[] = {
	"1", "2", "4", "8", "16", "32", "64"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_soft_mute_wate,
			    DA7213_DAC_FIWTEWS5,
			    DA7213_DAC_SOFTMUTE_WATE_SHIFT,
			    da7213_dac_soft_mute_wate_txt);

/* AWC Attack Wate sewect */
static const chaw * const da7213_awc_attack_wate_txt[] = {
	"44/fs", "88/fs", "176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs",
	"5632/fs", "11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
};

static SOC_ENUM_SINGWE_DECW(da7213_awc_attack_wate,
			    DA7213_AWC_CTWW2,
			    DA7213_AWC_ATTACK_SHIFT,
			    da7213_awc_attack_wate_txt);

/* AWC Wewease Wate sewect */
static const chaw * const da7213_awc_wewease_wate_txt[] = {
	"176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs", "5632/fs",
	"11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
};

static SOC_ENUM_SINGWE_DECW(da7213_awc_wewease_wate,
			    DA7213_AWC_CTWW2,
			    DA7213_AWC_WEWEASE_SHIFT,
			    da7213_awc_wewease_wate_txt);

/* AWC Howd Time sewect */
static const chaw * const da7213_awc_howd_time_txt[] = {
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
};

static SOC_ENUM_SINGWE_DECW(da7213_awc_howd_time,
			    DA7213_AWC_CTWW3,
			    DA7213_AWC_HOWD_SHIFT,
			    da7213_awc_howd_time_txt);

/* AWC Input Signaw Twacking wate sewect */
static const chaw * const da7213_awc_integ_wate_txt[] = {
	"1/4", "1/16", "1/256", "1/65536"
};

static SOC_ENUM_SINGWE_DECW(da7213_awc_integ_attack_wate,
			    DA7213_AWC_CTWW3,
			    DA7213_AWC_INTEG_ATTACK_SHIFT,
			    da7213_awc_integ_wate_txt);

static SOC_ENUM_SINGWE_DECW(da7213_awc_integ_wewease_wate,
			    DA7213_AWC_CTWW3,
			    DA7213_AWC_INTEG_WEWEASE_SHIFT,
			    da7213_awc_integ_wate_txt);


/*
 * Contwow Functions
 */

/* Wocked Kcontwow cawws */
static int da7213_vowsw_wocked_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	mutex_wock(&da7213->ctww_wock);
	wet = snd_soc_get_vowsw(kcontwow, ucontwow);
	mutex_unwock(&da7213->ctww_wock);

	wetuwn wet;
}

static int da7213_vowsw_wocked_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	mutex_wock(&da7213->ctww_wock);
	wet = snd_soc_put_vowsw(kcontwow, ucontwow);
	mutex_unwock(&da7213->ctww_wock);

	wetuwn wet;
}

static int da7213_enum_wocked_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	mutex_wock(&da7213->ctww_wock);
	wet = snd_soc_get_enum_doubwe(kcontwow, ucontwow);
	mutex_unwock(&da7213->ctww_wock);

	wetuwn wet;
}

static int da7213_enum_wocked_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	mutex_wock(&da7213->ctww_wock);
	wet = snd_soc_put_enum_doubwe(kcontwow, ucontwow);
	mutex_unwock(&da7213->ctww_wock);

	wetuwn wet;
}

/* AWC */
static int da7213_get_awc_data(stwuct snd_soc_component *component, u8 weg_vaw)
{
	int mid_data, top_data;
	int sum = 0;
	u8 itewation;

	fow (itewation = 0; itewation < DA7213_AWC_AVG_ITEWATIONS;
	     itewation++) {
		/* Sewect the weft ow wight channew and captuwe data */
		snd_soc_component_wwite(component, DA7213_AWC_CIC_OP_WVW_CTWW, weg_vaw);

		/* Sewect middwe 8 bits fow wead back fwom data wegistew */
		snd_soc_component_wwite(component, DA7213_AWC_CIC_OP_WVW_CTWW,
			      weg_vaw | DA7213_AWC_DATA_MIDDWE);
		mid_data = snd_soc_component_wead(component, DA7213_AWC_CIC_OP_WVW_DATA);

		/* Sewect top 8 bits fow wead back fwom data wegistew */
		snd_soc_component_wwite(component, DA7213_AWC_CIC_OP_WVW_CTWW,
			      weg_vaw | DA7213_AWC_DATA_TOP);
		top_data = snd_soc_component_wead(component, DA7213_AWC_CIC_OP_WVW_DATA);

		sum += ((mid_data << 8) | (top_data << 16));
	}

	wetuwn sum / DA7213_AWC_AVG_ITEWATIONS;
}

static void da7213_awc_cawib_man(stwuct snd_soc_component *component)
{
	u8 weg_vaw;
	int avg_weft_data, avg_wight_data, offset_w, offset_w;

	/* Cawcuwate avewage fow Weft and Wight data */
	/* Weft Data */
	avg_weft_data = da7213_get_awc_data(component,
			DA7213_AWC_CIC_OP_CHANNEW_WEFT);
	/* Wight Data */
	avg_wight_data = da7213_get_awc_data(component,
			 DA7213_AWC_CIC_OP_CHANNEW_WIGHT);

	/* Cawcuwate DC offset */
	offset_w = -avg_weft_data;
	offset_w = -avg_wight_data;

	weg_vaw = (offset_w & DA7213_AWC_OFFSET_15_8) >> 8;
	snd_soc_component_wwite(component, DA7213_AWC_OFFSET_MAN_M_W, weg_vaw);
	weg_vaw = (offset_w & DA7213_AWC_OFFSET_19_16) >> 16;
	snd_soc_component_wwite(component, DA7213_AWC_OFFSET_MAN_U_W, weg_vaw);

	weg_vaw = (offset_w & DA7213_AWC_OFFSET_15_8) >> 8;
	snd_soc_component_wwite(component, DA7213_AWC_OFFSET_MAN_M_W, weg_vaw);
	weg_vaw = (offset_w & DA7213_AWC_OFFSET_19_16) >> 16;
	snd_soc_component_wwite(component, DA7213_AWC_OFFSET_MAN_U_W, weg_vaw);

	/* Enabwe anawog/digitaw gain mode & offset cancewwation */
	snd_soc_component_update_bits(component, DA7213_AWC_CTWW1,
			    DA7213_AWC_OFFSET_EN | DA7213_AWC_SYNC_MODE,
			    DA7213_AWC_OFFSET_EN | DA7213_AWC_SYNC_MODE);
}

static void da7213_awc_cawib_auto(stwuct snd_soc_component *component)
{
	u8 awc_ctww1;

	/* Begin auto cawibwation and wait fow compwetion */
	snd_soc_component_update_bits(component, DA7213_AWC_CTWW1, DA7213_AWC_AUTO_CAWIB_EN,
			    DA7213_AWC_AUTO_CAWIB_EN);
	do {
		awc_ctww1 = snd_soc_component_wead(component, DA7213_AWC_CTWW1);
	} whiwe (awc_ctww1 & DA7213_AWC_AUTO_CAWIB_EN);

	/* If auto cawibwation faiws, faww back to digitaw gain onwy mode */
	if (awc_ctww1 & DA7213_AWC_CAWIB_OVEWFWOW) {
		dev_wawn(component->dev,
			 "AWC auto cawibwation faiwed with ovewfwow\n");
		snd_soc_component_update_bits(component, DA7213_AWC_CTWW1,
				    DA7213_AWC_OFFSET_EN | DA7213_AWC_SYNC_MODE,
				    0);
	} ewse {
		/* Enabwe anawog/digitaw gain mode & offset cancewwation */
		snd_soc_component_update_bits(component, DA7213_AWC_CTWW1,
				    DA7213_AWC_OFFSET_EN | DA7213_AWC_SYNC_MODE,
				    DA7213_AWC_OFFSET_EN | DA7213_AWC_SYNC_MODE);
	}

}

static void da7213_awc_cawib(stwuct snd_soc_component *component)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	u8 adc_w_ctww, adc_w_ctww;
	u8 mixin_w_sew, mixin_w_sew;
	u8 mic_1_ctww, mic_2_ctww;

	/* Save cuwwent vawues fwom ADC contwow wegistews */
	adc_w_ctww = snd_soc_component_wead(component, DA7213_ADC_W_CTWW);
	adc_w_ctww = snd_soc_component_wead(component, DA7213_ADC_W_CTWW);

	/* Save cuwwent vawues fwom MIXIN_W/W_SEWECT wegistews */
	mixin_w_sew = snd_soc_component_wead(component, DA7213_MIXIN_W_SEWECT);
	mixin_w_sew = snd_soc_component_wead(component, DA7213_MIXIN_W_SEWECT);

	/* Save cuwwent vawues fwom MIC contwow wegistews */
	mic_1_ctww = snd_soc_component_wead(component, DA7213_MIC_1_CTWW);
	mic_2_ctww = snd_soc_component_wead(component, DA7213_MIC_2_CTWW);

	/* Enabwe ADC Weft and Wight */
	snd_soc_component_update_bits(component, DA7213_ADC_W_CTWW, DA7213_ADC_EN,
			    DA7213_ADC_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_W_CTWW, DA7213_ADC_EN,
			    DA7213_ADC_EN);

	/* Enabwe MIC paths */
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_SEWECT,
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_1 |
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_2,
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_1 |
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_2);
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_SEWECT,
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_2 |
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_1,
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_2 |
			    DA7213_MIXIN_W_MIX_SEWECT_MIC_1);

	/* Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7213_MIC_1_CTWW, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);
	snd_soc_component_update_bits(component, DA7213_MIC_2_CTWW, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);

	/* Pewfowm cawibwation */
	if (da7213->awc_cawib_auto)
		da7213_awc_cawib_auto(component);
	ewse
		da7213_awc_cawib_man(component);

	/* Westowe MIXIN_W/W_SEWECT wegistews to theiw owiginaw states */
	snd_soc_component_wwite(component, DA7213_MIXIN_W_SEWECT, mixin_w_sew);
	snd_soc_component_wwite(component, DA7213_MIXIN_W_SEWECT, mixin_w_sew);

	/* Westowe ADC contwow wegistews to theiw owiginaw states */
	snd_soc_component_wwite(component, DA7213_ADC_W_CTWW, adc_w_ctww);
	snd_soc_component_wwite(component, DA7213_ADC_W_CTWW, adc_w_ctww);

	/* Westowe owiginaw vawues of MIC contwow wegistews */
	snd_soc_component_wwite(component, DA7213_MIC_1_CTWW, mic_1_ctww);
	snd_soc_component_wwite(component, DA7213_MIC_2_CTWW, mic_2_ctww);
}

static int da7213_put_mixin_gain(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_put_vowsw_2w(kcontwow, ucontwow);

	/* If AWC in opewation, make suwe cawibwated offsets awe updated */
	if ((!wet) && (da7213->awc_en))
		da7213_awc_cawib(component);

	wetuwn wet;
}

static int da7213_put_awc_sw(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);

	/* Fowce AWC offset cawibwation if enabwing AWC */
	if (ucontwow->vawue.integew.vawue[0] ||
	    ucontwow->vawue.integew.vawue[1]) {
		if (!da7213->awc_en) {
			da7213_awc_cawib(component);
			da7213->awc_en = twue;
		}
	} ewse {
		da7213->awc_en = fawse;
	}

	wetuwn snd_soc_put_vowsw(kcontwow, ucontwow);
}

/* ToneGen */
static int da7213_tonegen_fweq_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mixew_ctww =
		(stwuct soc_mixew_contwow *) kcontwow->pwivate_vawue;
	unsigned int weg = mixew_ctww->weg;
	__we16 vaw;
	int wet;

	mutex_wock(&da7213->ctww_wock);
	wet = wegmap_waw_wead(da7213->wegmap, weg, &vaw, sizeof(vaw));
	mutex_unwock(&da7213->ctww_wock);

	if (wet)
		wetuwn wet;

	/*
	 * Fwequency vawue spans two 8-bit wegistews, wowew then uppew byte.
	 * Thewefowe we need to convewt to host endianness hewe.
	 */
	ucontwow->vawue.integew.vawue[0] = we16_to_cpu(vaw);

	wetuwn 0;
}

static int da7213_tonegen_fweq_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mixew_ctww =
		(stwuct soc_mixew_contwow *) kcontwow->pwivate_vawue;
	unsigned int weg = mixew_ctww->weg;
	__we16 vaw_new, vaw_owd;
	int wet;

	/*
	 * Fwequency vawue spans two 8-bit wegistews, wowew then uppew byte.
	 * Thewefowe we need to convewt to wittwe endian hewe to awign with
	 * HW wegistews.
	 */
	vaw_new = cpu_to_we16(ucontwow->vawue.integew.vawue[0]);

	mutex_wock(&da7213->ctww_wock);
	wet = wegmap_waw_wead(da7213->wegmap, weg, &vaw_owd, sizeof(vaw_owd));
	if (wet == 0 && (vaw_owd != vaw_new))
		wet = wegmap_waw_wwite(da7213->wegmap, weg,
				&vaw_new, sizeof(vaw_new));
	mutex_unwock(&da7213->ctww_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn vaw_owd != vaw_new;
}

/*
 * KContwows
 */

static const stwuct snd_kcontwow_new da7213_snd_contwows[] = {

	/* Vowume contwows */
	SOC_SINGWE_TWV("Mic 1 Vowume", DA7213_MIC_1_GAIN,
		       DA7213_MIC_AMP_GAIN_SHIFT, DA7213_MIC_AMP_GAIN_MAX,
		       DA7213_NO_INVEWT, mic_vow_twv),
	SOC_SINGWE_TWV("Mic 2 Vowume", DA7213_MIC_2_GAIN,
		       DA7213_MIC_AMP_GAIN_SHIFT, DA7213_MIC_AMP_GAIN_MAX,
		       DA7213_NO_INVEWT, mic_vow_twv),
	SOC_DOUBWE_W_TWV("Aux Vowume", DA7213_AUX_W_GAIN, DA7213_AUX_W_GAIN,
			 DA7213_AUX_AMP_GAIN_SHIFT, DA7213_AUX_AMP_GAIN_MAX,
			 DA7213_NO_INVEWT, aux_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("Mixin PGA Vowume", DA7213_MIXIN_W_GAIN,
			     DA7213_MIXIN_W_GAIN, DA7213_MIXIN_AMP_GAIN_SHIFT,
			     DA7213_MIXIN_AMP_GAIN_MAX, DA7213_NO_INVEWT,
			     snd_soc_get_vowsw_2w, da7213_put_mixin_gain,
			     mixin_gain_twv),
	SOC_DOUBWE_W_TWV("ADC Vowume", DA7213_ADC_W_GAIN, DA7213_ADC_W_GAIN,
			 DA7213_ADC_AMP_GAIN_SHIFT, DA7213_ADC_AMP_GAIN_MAX,
			 DA7213_NO_INVEWT, digitaw_gain_twv),
	SOC_DOUBWE_W_TWV("DAC Vowume", DA7213_DAC_W_GAIN, DA7213_DAC_W_GAIN,
			 DA7213_DAC_AMP_GAIN_SHIFT, DA7213_DAC_AMP_GAIN_MAX,
			 DA7213_NO_INVEWT, digitaw_gain_twv),
	SOC_DOUBWE_W_TWV("Headphone Vowume", DA7213_HP_W_GAIN, DA7213_HP_W_GAIN,
			 DA7213_HP_AMP_GAIN_SHIFT, DA7213_HP_AMP_GAIN_MAX,
			 DA7213_NO_INVEWT, hp_vow_twv),
	SOC_SINGWE_TWV("Wineout Vowume", DA7213_WINE_GAIN,
		       DA7213_WINE_AMP_GAIN_SHIFT, DA7213_WINE_AMP_GAIN_MAX,
		       DA7213_NO_INVEWT, wineout_vow_twv),

	/* DAC Equawizew contwows */
	SOC_SINGWE("DAC EQ Switch", DA7213_DAC_FIWTEWS4, DA7213_DAC_EQ_EN_SHIFT,
		   DA7213_DAC_EQ_EN_MAX, DA7213_NO_INVEWT),
	SOC_SINGWE_TWV("DAC EQ1 Vowume", DA7213_DAC_FIWTEWS2,
		       DA7213_DAC_EQ_BAND1_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVEWT, eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ2 Vowume", DA7213_DAC_FIWTEWS2,
		       DA7213_DAC_EQ_BAND2_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVEWT, eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ3 Vowume", DA7213_DAC_FIWTEWS3,
		       DA7213_DAC_EQ_BAND3_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVEWT, eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ4 Vowume", DA7213_DAC_FIWTEWS3,
		       DA7213_DAC_EQ_BAND4_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVEWT, eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ5 Vowume", DA7213_DAC_FIWTEWS4,
		       DA7213_DAC_EQ_BAND5_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVEWT, eq_gain_twv),

	/* High Pass Fiwtew and Voice Mode contwows */
	SOC_SINGWE("ADC HPF Switch", DA7213_ADC_FIWTEWS1, DA7213_HPF_EN_SHIFT,
		   DA7213_HPF_EN_MAX, DA7213_NO_INVEWT),
	SOC_ENUM("ADC HPF Cutoff", da7213_adc_audio_hpf_cownew),
	SOC_SINGWE("ADC Voice Mode Switch", DA7213_ADC_FIWTEWS1,
		   DA7213_VOICE_EN_SHIFT, DA7213_VOICE_EN_MAX,
		   DA7213_NO_INVEWT),
	SOC_ENUM("ADC Voice Cutoff", da7213_adc_voice_hpf_cownew),

	SOC_SINGWE("DAC HPF Switch", DA7213_DAC_FIWTEWS1, DA7213_HPF_EN_SHIFT,
		   DA7213_HPF_EN_MAX, DA7213_NO_INVEWT),
	SOC_ENUM("DAC HPF Cutoff", da7213_dac_audio_hpf_cownew),
	SOC_SINGWE("DAC Voice Mode Switch", DA7213_DAC_FIWTEWS1,
		   DA7213_VOICE_EN_SHIFT, DA7213_VOICE_EN_MAX,
		   DA7213_NO_INVEWT),
	SOC_ENUM("DAC Voice Cutoff", da7213_dac_voice_hpf_cownew),

	/* Mute contwows */
	SOC_SINGWE("Mic 1 Switch", DA7213_MIC_1_CTWW, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_SINGWE("Mic 2 Switch", DA7213_MIC_2_CTWW, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_DOUBWE_W("Aux Switch", DA7213_AUX_W_CTWW, DA7213_AUX_W_CTWW,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_DOUBWE_W("Mixin PGA Switch", DA7213_MIXIN_W_CTWW,
		     DA7213_MIXIN_W_CTWW, DA7213_MUTE_EN_SHIFT,
		     DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_DOUBWE_W("ADC Switch", DA7213_ADC_W_CTWW, DA7213_ADC_W_CTWW,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_DOUBWE_W("Headphone Switch", DA7213_HP_W_CTWW, DA7213_HP_W_CTWW,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_SINGWE("Wineout Switch", DA7213_WINE_CTWW, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVEWT),
	SOC_SINGWE("DAC Soft Mute Switch", DA7213_DAC_FIWTEWS5,
		   DA7213_DAC_SOFTMUTE_EN_SHIFT, DA7213_DAC_SOFTMUTE_EN_MAX,
		   DA7213_NO_INVEWT),
	SOC_ENUM("DAC Soft Mute Wate", da7213_dac_soft_mute_wate),

	/* Zewo Cwoss contwows */
	SOC_DOUBWE_W("Aux ZC Switch", DA7213_AUX_W_CTWW, DA7213_AUX_W_CTWW,
		     DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE_W("Mixin PGA ZC Switch", DA7213_MIXIN_W_CTWW,
		     DA7213_MIXIN_W_CTWW, DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX,
		     DA7213_NO_INVEWT),
	SOC_DOUBWE_W("Headphone ZC Switch", DA7213_HP_W_CTWW, DA7213_HP_W_CTWW,
		     DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX, DA7213_NO_INVEWT),

	/* Tone Genewatow */
	SOC_SINGWE_EXT_TWV("ToneGen Vowume", DA7213_TONE_GEN_CFG2,
			   DA7213_TONE_GEN_GAIN_SHIFT, DA7213_TONE_GEN_GAIN_MAX,
			   DA7213_NO_INVEWT, da7213_vowsw_wocked_get,
			   da7213_vowsw_wocked_put, da7213_tonegen_gain_twv),
	SOC_ENUM_EXT("ToneGen DTMF Key", da7213_tonegen_dtmf_key,
		     da7213_enum_wocked_get, da7213_enum_wocked_put),
	SOC_SINGWE_EXT("ToneGen DTMF Switch", DA7213_TONE_GEN_CFG1,
		       DA7213_DTMF_EN_SHIFT, DA7213_SWITCH_EN_MAX,
		       DA7213_NO_INVEWT, da7213_vowsw_wocked_get,
		       da7213_vowsw_wocked_put),
	SOC_SINGWE_EXT("ToneGen Stawt", DA7213_TONE_GEN_CFG1,
		       DA7213_STAWT_STOPN_SHIFT, DA7213_SWITCH_EN_MAX,
		       DA7213_NO_INVEWT, da7213_vowsw_wocked_get,
		       da7213_vowsw_wocked_put),
	SOC_ENUM_EXT("ToneGen Sinewave Gen Type", da7213_tonegen_swg_sew,
		     da7213_enum_wocked_get, da7213_enum_wocked_put),
	SOC_SINGWE_EXT("ToneGen Sinewave1 Fweq", DA7213_TONE_GEN_FWEQ1_W,
		       DA7213_FWEQ1_W_SHIFT, DA7213_FWEQ_MAX, DA7213_NO_INVEWT,
		       da7213_tonegen_fweq_get, da7213_tonegen_fweq_put),
	SOC_SINGWE_EXT("ToneGen Sinewave2 Fweq", DA7213_TONE_GEN_FWEQ2_W,
		       DA7213_FWEQ2_W_SHIFT, DA7213_FWEQ_MAX, DA7213_NO_INVEWT,
		       da7213_tonegen_fweq_get, da7213_tonegen_fweq_put),
	SOC_SINGWE_EXT("ToneGen On Time", DA7213_TONE_GEN_ON_PEW,
		       DA7213_BEEP_ON_PEW_SHIFT, DA7213_BEEP_ON_OFF_MAX,
		       DA7213_NO_INVEWT, da7213_vowsw_wocked_get,
		       da7213_vowsw_wocked_put),
	SOC_SINGWE("ToneGen Off Time", DA7213_TONE_GEN_OFF_PEW,
		   DA7213_BEEP_OFF_PEW_SHIFT, DA7213_BEEP_ON_OFF_MAX,
		   DA7213_NO_INVEWT),

	/* Gain Wamping contwows */
	SOC_DOUBWE_W("Aux Gain Wamping Switch", DA7213_AUX_W_CTWW,
		     DA7213_AUX_W_CTWW, DA7213_GAIN_WAMP_EN_SHIFT,
		     DA7213_GAIN_WAMP_EN_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE_W("Mixin Gain Wamping Switch", DA7213_MIXIN_W_CTWW,
		     DA7213_MIXIN_W_CTWW, DA7213_GAIN_WAMP_EN_SHIFT,
		     DA7213_GAIN_WAMP_EN_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE_W("ADC Gain Wamping Switch", DA7213_ADC_W_CTWW,
		     DA7213_ADC_W_CTWW, DA7213_GAIN_WAMP_EN_SHIFT,
		     DA7213_GAIN_WAMP_EN_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE_W("DAC Gain Wamping Switch", DA7213_DAC_W_CTWW,
		     DA7213_DAC_W_CTWW, DA7213_GAIN_WAMP_EN_SHIFT,
		     DA7213_GAIN_WAMP_EN_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE_W("Headphone Gain Wamping Switch", DA7213_HP_W_CTWW,
		     DA7213_HP_W_CTWW, DA7213_GAIN_WAMP_EN_SHIFT,
		     DA7213_GAIN_WAMP_EN_MAX, DA7213_NO_INVEWT),
	SOC_SINGWE("Wineout Gain Wamping Switch", DA7213_WINE_CTWW,
		   DA7213_GAIN_WAMP_EN_SHIFT, DA7213_GAIN_WAMP_EN_MAX,
		   DA7213_NO_INVEWT),
	SOC_ENUM("Gain Wamping Wate", da7213_gain_wamp_wate),

	/* DAC Noise Gate contwows */
	SOC_SINGWE("DAC NG Switch", DA7213_DAC_NG_CTWW, DA7213_DAC_NG_EN_SHIFT,
		   DA7213_DAC_NG_EN_MAX, DA7213_NO_INVEWT),
	SOC_ENUM("DAC NG Setup Time", da7213_dac_ng_setup_time),
	SOC_ENUM("DAC NG Wampup Wate", da7213_dac_ng_wampup_wate),
	SOC_ENUM("DAC NG Wampdown Wate", da7213_dac_ng_wampdown_wate),
	SOC_SINGWE("DAC NG OFF Thweshowd", DA7213_DAC_NG_OFF_THWESHOWD,
		   DA7213_DAC_NG_THWESHOWD_SHIFT, DA7213_DAC_NG_THWESHOWD_MAX,
		   DA7213_NO_INVEWT),
	SOC_SINGWE("DAC NG ON Thweshowd", DA7213_DAC_NG_ON_THWESHOWD,
		   DA7213_DAC_NG_THWESHOWD_SHIFT, DA7213_DAC_NG_THWESHOWD_MAX,
		   DA7213_NO_INVEWT),

	/* DAC Wouting & Invewsion */
	SOC_DOUBWE("DAC Mono Switch", DA7213_DIG_WOUTING_DAC,
		   DA7213_DAC_W_MONO_SHIFT, DA7213_DAC_W_MONO_SHIFT,
		   DA7213_DAC_MONO_MAX, DA7213_NO_INVEWT),
	SOC_DOUBWE("DAC Invewt Switch", DA7213_DIG_CTWW, DA7213_DAC_W_INV_SHIFT,
		   DA7213_DAC_W_INV_SHIFT, DA7213_DAC_INV_MAX,
		   DA7213_NO_INVEWT),

	/* DMIC contwows */
	SOC_DOUBWE_W("DMIC Switch", DA7213_MIXIN_W_SEWECT,
		     DA7213_MIXIN_W_SEWECT, DA7213_DMIC_EN_SHIFT,
		     DA7213_DMIC_EN_MAX, DA7213_NO_INVEWT),

	/* AWC Contwows */
	SOC_DOUBWE_EXT("AWC Switch", DA7213_AWC_CTWW1, DA7213_AWC_W_EN_SHIFT,
		       DA7213_AWC_W_EN_SHIFT, DA7213_AWC_EN_MAX,
		       DA7213_NO_INVEWT, snd_soc_get_vowsw, da7213_put_awc_sw),
	SOC_ENUM("AWC Attack Wate", da7213_awc_attack_wate),
	SOC_ENUM("AWC Wewease Wate", da7213_awc_wewease_wate),
	SOC_ENUM("AWC Howd Time", da7213_awc_howd_time),
	/*
	 * Wate at which input signaw envewope is twacked as the signaw gets
	 * wawgew
	 */
	SOC_ENUM("AWC Integ Attack Wate", da7213_awc_integ_attack_wate),
	/*
	 * Wate at which input signaw envewope is twacked as the signaw gets
	 * smawwew
	 */
	SOC_ENUM("AWC Integ Wewease Wate", da7213_awc_integ_wewease_wate),
	SOC_SINGWE_TWV("AWC Noise Thweshowd Vowume", DA7213_AWC_NOISE,
		       DA7213_AWC_THWESHOWD_SHIFT, DA7213_AWC_THWESHOWD_MAX,
		       DA7213_INVEWT, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Min Thweshowd Vowume", DA7213_AWC_TAWGET_MIN,
		       DA7213_AWC_THWESHOWD_SHIFT, DA7213_AWC_THWESHOWD_MAX,
		       DA7213_INVEWT, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Max Thweshowd Vowume", DA7213_AWC_TAWGET_MAX,
		       DA7213_AWC_THWESHOWD_SHIFT, DA7213_AWC_THWESHOWD_MAX,
		       DA7213_INVEWT, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Max Attenuation Vowume", DA7213_AWC_GAIN_WIMITS,
		       DA7213_AWC_ATTEN_MAX_SHIFT,
		       DA7213_AWC_ATTEN_GAIN_MAX_MAX, DA7213_NO_INVEWT,
		       awc_gain_twv),
	SOC_SINGWE_TWV("AWC Max Gain Vowume", DA7213_AWC_GAIN_WIMITS,
		       DA7213_AWC_GAIN_MAX_SHIFT, DA7213_AWC_ATTEN_GAIN_MAX_MAX,
		       DA7213_NO_INVEWT, awc_gain_twv),
	SOC_SINGWE_TWV("AWC Min Anawog Gain Vowume", DA7213_AWC_ANA_GAIN_WIMITS,
		       DA7213_AWC_ANA_GAIN_MIN_SHIFT, DA7213_AWC_ANA_GAIN_MAX,
		       DA7213_NO_INVEWT, awc_anawog_gain_twv),
	SOC_SINGWE_TWV("AWC Max Anawog Gain Vowume", DA7213_AWC_ANA_GAIN_WIMITS,
		       DA7213_AWC_ANA_GAIN_MAX_SHIFT, DA7213_AWC_ANA_GAIN_MAX,
		       DA7213_NO_INVEWT, awc_anawog_gain_twv),
	SOC_SINGWE("AWC Anticwip Mode Switch", DA7213_AWC_ANTICWIP_CTWW,
		   DA7213_AWC_ANTICWIP_EN_SHIFT, DA7213_AWC_ANTICWIP_EN_MAX,
		   DA7213_NO_INVEWT),
	SOC_SINGWE("AWC Anticwip Wevew", DA7213_AWC_ANTICWIP_WEVEW,
		   DA7213_AWC_ANTICWIP_WEVEW_SHIFT,
		   DA7213_AWC_ANTICWIP_WEVEW_MAX, DA7213_NO_INVEWT),
};


/*
 * DAPM
 */

/*
 * Enums
 */

/* MIC PGA souwce sewect */
static const chaw * const da7213_mic_amp_in_sew_txt[] = {
	"Diffewentiaw", "MIC_P", "MIC_N"
};

static SOC_ENUM_SINGWE_DECW(da7213_mic_1_amp_in_sew,
			    DA7213_MIC_1_CTWW,
			    DA7213_MIC_AMP_IN_SEW_SHIFT,
			    da7213_mic_amp_in_sew_txt);
static const stwuct snd_kcontwow_new da7213_mic_1_amp_in_sew_mux =
	SOC_DAPM_ENUM("Mic 1 Amp Souwce MUX", da7213_mic_1_amp_in_sew);

static SOC_ENUM_SINGWE_DECW(da7213_mic_2_amp_in_sew,
			    DA7213_MIC_2_CTWW,
			    DA7213_MIC_AMP_IN_SEW_SHIFT,
			    da7213_mic_amp_in_sew_txt);
static const stwuct snd_kcontwow_new da7213_mic_2_amp_in_sew_mux =
	SOC_DAPM_ENUM("Mic 2 Amp Souwce MUX", da7213_mic_2_amp_in_sew);

/* DAI wouting sewect */
static const chaw * const da7213_dai_swc_txt[] = {
	"ADC Weft", "ADC Wight", "DAI Input Weft", "DAI Input Wight"
};

static SOC_ENUM_SINGWE_DECW(da7213_dai_w_swc,
			    DA7213_DIG_WOUTING_DAI,
			    DA7213_DAI_W_SWC_SHIFT,
			    da7213_dai_swc_txt);
static const stwuct snd_kcontwow_new da7213_dai_w_swc_mux =
	SOC_DAPM_ENUM("DAI Weft Souwce MUX", da7213_dai_w_swc);

static SOC_ENUM_SINGWE_DECW(da7213_dai_w_swc,
			    DA7213_DIG_WOUTING_DAI,
			    DA7213_DAI_W_SWC_SHIFT,
			    da7213_dai_swc_txt);
static const stwuct snd_kcontwow_new da7213_dai_w_swc_mux =
	SOC_DAPM_ENUM("DAI Wight Souwce MUX", da7213_dai_w_swc);

/* DAC wouting sewect */
static const chaw * const da7213_dac_swc_txt[] = {
	"ADC Output Weft", "ADC Output Wight", "DAI Input Weft",
	"DAI Input Wight"
};

static SOC_ENUM_SINGWE_DECW(da7213_dac_w_swc,
			    DA7213_DIG_WOUTING_DAC,
			    DA7213_DAC_W_SWC_SHIFT,
			    da7213_dac_swc_txt);
static const stwuct snd_kcontwow_new da7213_dac_w_swc_mux =
	SOC_DAPM_ENUM("DAC Weft Souwce MUX", da7213_dac_w_swc);

static SOC_ENUM_SINGWE_DECW(da7213_dac_w_swc,
			    DA7213_DIG_WOUTING_DAC,
			    DA7213_DAC_W_SWC_SHIFT,
			    da7213_dac_swc_txt);
static const stwuct snd_kcontwow_new da7213_dac_w_swc_mux =
	SOC_DAPM_ENUM("DAC Wight Souwce MUX", da7213_dac_w_swc);

/*
 * Mixew Contwows
 */

/* Mixin Weft */
static const stwuct snd_kcontwow_new da7213_dapm_mixinw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Weft Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_AUX_W_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mic 1 Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIC_1_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mic 2 Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIC_2_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Wight Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
};

/* Mixin Wight */
static const stwuct snd_kcontwow_new da7213_dapm_mixinw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Wight Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_AUX_W_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mic 2 Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIC_2_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mic 1 Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIC_1_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA7213_MIXIN_W_SEWECT,
			DA7213_MIXIN_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXIN_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
};

/* Mixout Weft */
static const stwuct snd_kcontwow_new da7213_dapm_mixoutw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Weft Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_AUX_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Wight Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("DAC Weft Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_DAC_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Aux Weft Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_AUX_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Weft Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Wight Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
};

/* Mixout Wight */
static const stwuct snd_kcontwow_new da7213_dapm_mixoutw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Wight Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_AUX_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Wight Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("DAC Wight Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_DAC_W_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Aux Wight Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_AUX_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Wight Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
	SOC_DAPM_SINGWE("Mixin Weft Invewt Switch", DA7213_MIXOUT_W_SEWECT,
			DA7213_MIXOUT_W_MIX_SEWECT_MIXIN_W_INVEWTED_SHIFT,
			DA7213_MIXOUT_W_MIX_SEWECT_MAX, DA7213_NO_INVEWT),
};


/*
 * DAPM Events
 */

static int da7213_dai_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	u8 pww_ctww, pww_status;
	int i = 0;
	boow swm_wock = fawse;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Enabwe DAI cwks fow mastew mode */
		if (da7213->mastew)
			snd_soc_component_update_bits(component, DA7213_DAI_CWK_MODE,
					    DA7213_DAI_CWK_EN_MASK,
					    DA7213_DAI_CWK_EN_MASK);

		/* PC synchwonised to DAI */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FWEEWUN_MASK, 0);

		/* If SWM not enabwed then nothing mowe to do */
		pww_ctww = snd_soc_component_wead(component, DA7213_PWW_CTWW);
		if (!(pww_ctww & DA7213_PWW_SWM_EN))
			wetuwn 0;

		/* Assist 32KHz mode PWW wock */
		if (pww_ctww & DA7213_PWW_32K_MODE) {
			snd_soc_component_wwite(component, 0xF0, 0x8B);
			snd_soc_component_wwite(component, 0xF2, 0x03);
			snd_soc_component_wwite(component, 0xF0, 0x00);
		}

		/* Check SWM has wocked */
		do {
			pww_status = snd_soc_component_wead(component, DA7213_PWW_STATUS);
			if (pww_status & DA7213_PWW_SWM_WOCK) {
				swm_wock = twue;
			} ewse {
				++i;
				msweep(50);
			}
		} whiwe ((i < DA7213_SWM_CHECK_WETWIES) && (!swm_wock));

		if (!swm_wock)
			dev_wawn(component->dev, "SWM faiwed to wock\n");

		wetuwn 0;
	case SND_SOC_DAPM_POST_PMD:
		/* Wevewt 32KHz PWW wock udpates if appwied pweviouswy */
		pww_ctww = snd_soc_component_wead(component, DA7213_PWW_CTWW);
		if (pww_ctww & DA7213_PWW_32K_MODE) {
			snd_soc_component_wwite(component, 0xF0, 0x8B);
			snd_soc_component_wwite(component, 0xF2, 0x01);
			snd_soc_component_wwite(component, 0xF0, 0x00);
		}

		/* PC fwee-wunning */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FWEEWUN_MASK,
				    DA7213_PC_FWEEWUN_MASK);

		/* Disabwe DAI cwks if in mastew mode */
		if (da7213->mastew)
			snd_soc_component_update_bits(component, DA7213_DAI_CWK_MODE,
					    DA7213_DAI_CWK_EN_MASK, 0);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}


/*
 * DAPM widgets
 */

static const stwuct snd_soc_dapm_widget da7213_dapm_widgets[] = {
	/*
	 * Powew Suppwy
	 */
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VDDMIC", 0, 0),

	/*
	 * Input & Output
	 */

	/* Use a suppwy hewe as this contwows both input & output DAIs */
	SND_SOC_DAPM_SUPPWY("DAI", DA7213_DAI_CTWW, DA7213_DAI_EN_SHIFT,
			    DA7213_NO_INVEWT, da7213_dai_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/*
	 * Input
	 */

	/* Input Wines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AUXW"),
	SND_SOC_DAPM_INPUT("AUXW"),

	/* MUXs fow Mic PGA souwce sewection */
	SND_SOC_DAPM_MUX("Mic 1 Amp Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_mic_1_amp_in_sew_mux),
	SND_SOC_DAPM_MUX("Mic 2 Amp Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_mic_2_amp_in_sew_mux),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic 1 PGA", DA7213_MIC_1_CTWW, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic 2 PGA", DA7213_MIC_2_CTWW, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux Weft PGA", DA7213_AUX_W_CTWW, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux Wight PGA", DA7213_AUX_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Mixin Weft PGA", DA7213_MIXIN_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Mixin Wight PGA", DA7213_MIXIN_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),

	/* Mic Biases */
	SND_SOC_DAPM_SUPPWY("Mic Bias 1", DA7213_MICBIAS_CTWW,
			    DA7213_MICBIAS1_EN_SHIFT, DA7213_NO_INVEWT,
			    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Bias 2", DA7213_MICBIAS_CTWW,
			    DA7213_MICBIAS2_EN_SHIFT, DA7213_NO_INVEWT,
			    NUWW, 0),

	/* Input Mixews */
	SND_SOC_DAPM_MIXEW("Mixin Weft", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixinw_contwows[0],
			   AWWAY_SIZE(da7213_dapm_mixinw_contwows)),
	SND_SOC_DAPM_MIXEW("Mixin Wight", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixinw_contwows[0],
			   AWWAY_SIZE(da7213_dapm_mixinw_contwows)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Weft", NUWW, DA7213_ADC_W_CTWW,
			 DA7213_ADC_EN_SHIFT, DA7213_NO_INVEWT),
	SND_SOC_DAPM_ADC("ADC Wight", NUWW, DA7213_ADC_W_CTWW,
			 DA7213_ADC_EN_SHIFT, DA7213_NO_INVEWT),

	/* DAI */
	SND_SOC_DAPM_MUX("DAI Weft Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dai_w_swc_mux),
	SND_SOC_DAPM_MUX("DAI Wight Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dai_w_swc_mux),
	SND_SOC_DAPM_AIF_OUT("DAIOUTW", "Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DAIOUTW", "Captuwe", 1, SND_SOC_NOPM, 0, 0),

	/*
	 * Output
	 */

	/* DAI */
	SND_SOC_DAPM_AIF_IN("DAIINW", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DAIINW", "Pwayback", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("DAC Weft Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dac_w_swc_mux),
	SND_SOC_DAPM_MUX("DAC Wight Souwce MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dac_w_swc_mux),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Weft", NUWW, DA7213_DAC_W_CTWW,
			 DA7213_DAC_EN_SHIFT, DA7213_NO_INVEWT),
	SND_SOC_DAPM_DAC("DAC Wight", NUWW, DA7213_DAC_W_CTWW,
			 DA7213_DAC_EN_SHIFT, DA7213_NO_INVEWT),

	/* Output Mixews */
	SND_SOC_DAPM_MIXEW("Mixout Weft", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixoutw_contwows[0],
			   AWWAY_SIZE(da7213_dapm_mixoutw_contwows)),
	SND_SOC_DAPM_MIXEW("Mixout Wight", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixoutw_contwows[0],
			   AWWAY_SIZE(da7213_dapm_mixoutw_contwows)),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("Mixout Weft PGA", DA7213_MIXOUT_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Mixout Wight PGA", DA7213_MIXOUT_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Wineout PGA", DA7213_WINE_CTWW, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Weft PGA", DA7213_HP_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Wight PGA", DA7213_HP_W_CTWW,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVEWT, NUWW, 0),

	/* Chawge Pump */
	SND_SOC_DAPM_SUPPWY("Chawge Pump", DA7213_CP_CTWW, DA7213_CP_EN_SHIFT,
			    DA7213_NO_INVEWT, NUWW, 0),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("WINE"),
};


/*
 * DAPM audio woute definition
 */

static const stwuct snd_soc_dapm_woute da7213_audio_map[] = {
	/* Dest       Connecting Widget    souwce */

	/* Input path */
	{"Mic Bias 1", NUWW, "VDDMIC"},
	{"Mic Bias 2", NUWW, "VDDMIC"},

	{"MIC1", NUWW, "Mic Bias 1"},
	{"MIC2", NUWW, "Mic Bias 2"},

	{"Mic 1 Amp Souwce MUX", "Diffewentiaw", "MIC1"},
	{"Mic 1 Amp Souwce MUX", "MIC_P", "MIC1"},
	{"Mic 1 Amp Souwce MUX", "MIC_N", "MIC1"},

	{"Mic 2 Amp Souwce MUX", "Diffewentiaw", "MIC2"},
	{"Mic 2 Amp Souwce MUX", "MIC_P", "MIC2"},
	{"Mic 2 Amp Souwce MUX", "MIC_N", "MIC2"},

	{"Mic 1 PGA", NUWW, "Mic 1 Amp Souwce MUX"},
	{"Mic 2 PGA", NUWW, "Mic 2 Amp Souwce MUX"},

	{"Aux Weft PGA", NUWW, "AUXW"},
	{"Aux Wight PGA", NUWW, "AUXW"},

	{"Mixin Weft", "Aux Weft Switch", "Aux Weft PGA"},
	{"Mixin Weft", "Mic 1 Switch", "Mic 1 PGA"},
	{"Mixin Weft", "Mic 2 Switch", "Mic 2 PGA"},
	{"Mixin Weft", "Mixin Wight Switch", "Mixin Wight PGA"},

	{"Mixin Wight", "Aux Wight Switch", "Aux Wight PGA"},
	{"Mixin Wight", "Mic 2 Switch", "Mic 2 PGA"},
	{"Mixin Wight", "Mic 1 Switch", "Mic 1 PGA"},
	{"Mixin Wight", "Mixin Weft Switch", "Mixin Weft PGA"},

	{"Mixin Weft PGA", NUWW, "Mixin Weft"},
	{"ADC Weft", NUWW, "Mixin Weft PGA"},

	{"Mixin Wight PGA", NUWW, "Mixin Wight"},
	{"ADC Wight", NUWW, "Mixin Wight PGA"},

	{"DAI Weft Souwce MUX", "ADC Weft", "ADC Weft"},
	{"DAI Weft Souwce MUX", "ADC Wight", "ADC Wight"},
	{"DAI Weft Souwce MUX", "DAI Input Weft", "DAIINW"},
	{"DAI Weft Souwce MUX", "DAI Input Wight", "DAIINW"},

	{"DAI Wight Souwce MUX", "ADC Weft", "ADC Weft"},
	{"DAI Wight Souwce MUX", "ADC Wight", "ADC Wight"},
	{"DAI Wight Souwce MUX", "DAI Input Weft", "DAIINW"},
	{"DAI Wight Souwce MUX", "DAI Input Wight", "DAIINW"},

	{"DAIOUTW", NUWW, "DAI Weft Souwce MUX"},
	{"DAIOUTW", NUWW, "DAI Wight Souwce MUX"},

	{"DAIOUTW", NUWW, "DAI"},
	{"DAIOUTW", NUWW, "DAI"},

	/* Output path */
	{"DAIINW", NUWW, "DAI"},
	{"DAIINW", NUWW, "DAI"},

	{"DAC Weft Souwce MUX", "ADC Output Weft", "ADC Weft"},
	{"DAC Weft Souwce MUX", "ADC Output Wight", "ADC Wight"},
	{"DAC Weft Souwce MUX", "DAI Input Weft", "DAIINW"},
	{"DAC Weft Souwce MUX", "DAI Input Wight", "DAIINW"},

	{"DAC Wight Souwce MUX", "ADC Output Weft", "ADC Weft"},
	{"DAC Wight Souwce MUX", "ADC Output Wight", "ADC Wight"},
	{"DAC Wight Souwce MUX", "DAI Input Weft", "DAIINW"},
	{"DAC Wight Souwce MUX", "DAI Input Wight", "DAIINW"},

	{"DAC Weft", NUWW, "DAC Weft Souwce MUX"},
	{"DAC Wight", NUWW, "DAC Wight Souwce MUX"},

	{"Mixout Weft", "Aux Weft Switch", "Aux Weft PGA"},
	{"Mixout Weft", "Mixin Weft Switch", "Mixin Weft PGA"},
	{"Mixout Weft", "Mixin Wight Switch", "Mixin Wight PGA"},
	{"Mixout Weft", "DAC Weft Switch", "DAC Weft"},
	{"Mixout Weft", "Aux Weft Invewt Switch", "Aux Weft PGA"},
	{"Mixout Weft", "Mixin Weft Invewt Switch", "Mixin Weft PGA"},
	{"Mixout Weft", "Mixin Wight Invewt Switch", "Mixin Wight PGA"},

	{"Mixout Wight", "Aux Wight Switch", "Aux Wight PGA"},
	{"Mixout Wight", "Mixin Wight Switch", "Mixin Wight PGA"},
	{"Mixout Wight", "Mixin Weft Switch", "Mixin Weft PGA"},
	{"Mixout Wight", "DAC Wight Switch", "DAC Wight"},
	{"Mixout Wight", "Aux Wight Invewt Switch", "Aux Wight PGA"},
	{"Mixout Wight", "Mixin Wight Invewt Switch", "Mixin Wight PGA"},
	{"Mixout Wight", "Mixin Weft Invewt Switch", "Mixin Weft PGA"},

	{"Mixout Weft PGA", NUWW, "Mixout Weft"},
	{"Mixout Wight PGA", NUWW, "Mixout Wight"},

	{"Headphone Weft PGA", NUWW, "Mixout Weft PGA"},
	{"Headphone Weft PGA", NUWW, "Chawge Pump"},
	{"HPW", NUWW, "Headphone Weft PGA"},

	{"Headphone Wight PGA", NUWW, "Mixout Wight PGA"},
	{"Headphone Wight PGA", NUWW, "Chawge Pump"},
	{"HPW", NUWW, "Headphone Wight PGA"},

	{"Wineout PGA", NUWW, "Mixout Wight PGA"},
	{"WINE", NUWW, "Wineout PGA"},
};

static const stwuct weg_defauwt da7213_weg_defauwts[] = {
	{ DA7213_DIG_WOUTING_DAI, 0x10 },
	{ DA7213_SW, 0x0A },
	{ DA7213_WEFEWENCES, 0x80 },
	{ DA7213_PWW_FWAC_TOP, 0x00 },
	{ DA7213_PWW_FWAC_BOT, 0x00 },
	{ DA7213_PWW_INTEGEW, 0x20 },
	{ DA7213_PWW_CTWW, 0x0C },
	{ DA7213_DAI_CWK_MODE, 0x01 },
	{ DA7213_DAI_CTWW, 0x08 },
	{ DA7213_DIG_WOUTING_DAC, 0x32 },
	{ DA7213_AUX_W_GAIN, 0x35 },
	{ DA7213_AUX_W_GAIN, 0x35 },
	{ DA7213_MIXIN_W_SEWECT, 0x00 },
	{ DA7213_MIXIN_W_SEWECT, 0x00 },
	{ DA7213_MIXIN_W_GAIN, 0x03 },
	{ DA7213_MIXIN_W_GAIN, 0x03 },
	{ DA7213_ADC_W_GAIN, 0x6F },
	{ DA7213_ADC_W_GAIN, 0x6F },
	{ DA7213_ADC_FIWTEWS1, 0x80 },
	{ DA7213_MIC_1_GAIN, 0x01 },
	{ DA7213_MIC_2_GAIN, 0x01 },
	{ DA7213_DAC_FIWTEWS5, 0x00 },
	{ DA7213_DAC_FIWTEWS2, 0x88 },
	{ DA7213_DAC_FIWTEWS3, 0x88 },
	{ DA7213_DAC_FIWTEWS4, 0x08 },
	{ DA7213_DAC_FIWTEWS1, 0x80 },
	{ DA7213_DAC_W_GAIN, 0x6F },
	{ DA7213_DAC_W_GAIN, 0x6F },
	{ DA7213_CP_CTWW, 0x61 },
	{ DA7213_HP_W_GAIN, 0x39 },
	{ DA7213_HP_W_GAIN, 0x39 },
	{ DA7213_WINE_GAIN, 0x30 },
	{ DA7213_MIXOUT_W_SEWECT, 0x00 },
	{ DA7213_MIXOUT_W_SEWECT, 0x00 },
	{ DA7213_SYSTEM_MODES_INPUT, 0x00 },
	{ DA7213_SYSTEM_MODES_OUTPUT, 0x00 },
	{ DA7213_AUX_W_CTWW, 0x44 },
	{ DA7213_AUX_W_CTWW, 0x44 },
	{ DA7213_MICBIAS_CTWW, 0x11 },
	{ DA7213_MIC_1_CTWW, 0x40 },
	{ DA7213_MIC_2_CTWW, 0x40 },
	{ DA7213_MIXIN_W_CTWW, 0x40 },
	{ DA7213_MIXIN_W_CTWW, 0x40 },
	{ DA7213_ADC_W_CTWW, 0x40 },
	{ DA7213_ADC_W_CTWW, 0x40 },
	{ DA7213_DAC_W_CTWW, 0x48 },
	{ DA7213_DAC_W_CTWW, 0x40 },
	{ DA7213_HP_W_CTWW, 0x41 },
	{ DA7213_HP_W_CTWW, 0x40 },
	{ DA7213_WINE_CTWW, 0x40 },
	{ DA7213_MIXOUT_W_CTWW, 0x10 },
	{ DA7213_MIXOUT_W_CTWW, 0x10 },
	{ DA7213_WDO_CTWW, 0x00 },
	{ DA7213_IO_CTWW, 0x00 },
	{ DA7213_GAIN_WAMP_CTWW, 0x00},
	{ DA7213_MIC_CONFIG, 0x00 },
	{ DA7213_PC_COUNT, 0x00 },
	{ DA7213_CP_VOW_THWESHOWD1, 0x32 },
	{ DA7213_CP_DEWAY, 0x95 },
	{ DA7213_CP_DETECTOW, 0x00 },
	{ DA7213_DAI_OFFSET, 0x00 },
	{ DA7213_DIG_CTWW, 0x00 },
	{ DA7213_AWC_CTWW2, 0x00 },
	{ DA7213_AWC_CTWW3, 0x00 },
	{ DA7213_AWC_NOISE, 0x3F },
	{ DA7213_AWC_TAWGET_MIN, 0x3F },
	{ DA7213_AWC_TAWGET_MAX, 0x00 },
	{ DA7213_AWC_GAIN_WIMITS, 0xFF },
	{ DA7213_AWC_ANA_GAIN_WIMITS, 0x71 },
	{ DA7213_AWC_ANTICWIP_CTWW, 0x00 },
	{ DA7213_AWC_ANTICWIP_WEVEW, 0x00 },
	{ DA7213_AWC_OFFSET_MAN_M_W, 0x00 },
	{ DA7213_AWC_OFFSET_MAN_U_W, 0x00 },
	{ DA7213_AWC_OFFSET_MAN_M_W, 0x00 },
	{ DA7213_AWC_OFFSET_MAN_U_W, 0x00 },
	{ DA7213_AWC_CIC_OP_WVW_CTWW, 0x00 },
	{ DA7213_DAC_NG_SETUP_TIME, 0x00 },
	{ DA7213_DAC_NG_OFF_THWESHOWD, 0x00 },
	{ DA7213_DAC_NG_ON_THWESHOWD, 0x00 },
	{ DA7213_DAC_NG_CTWW, 0x00 },
};

static boow da7213_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA7213_STATUS1:
	case DA7213_PWW_STATUS:
	case DA7213_AUX_W_GAIN_STATUS:
	case DA7213_AUX_W_GAIN_STATUS:
	case DA7213_MIC_1_GAIN_STATUS:
	case DA7213_MIC_2_GAIN_STATUS:
	case DA7213_MIXIN_W_GAIN_STATUS:
	case DA7213_MIXIN_W_GAIN_STATUS:
	case DA7213_ADC_W_GAIN_STATUS:
	case DA7213_ADC_W_GAIN_STATUS:
	case DA7213_DAC_W_GAIN_STATUS:
	case DA7213_DAC_W_GAIN_STATUS:
	case DA7213_HP_W_GAIN_STATUS:
	case DA7213_HP_W_GAIN_STATUS:
	case DA7213_WINE_GAIN_STATUS:
	case DA7213_AWC_CTWW1:
	case DA7213_AWC_OFFSET_AUTO_M_W:
	case DA7213_AWC_OFFSET_AUTO_U_W:
	case DA7213_AWC_OFFSET_AUTO_M_W:
	case DA7213_AWC_OFFSET_AUTO_U_W:
	case DA7213_AWC_CIC_OP_WVW_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int da7213_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	u8 dai_cwk_mode = DA7213_DAI_BCWKS_PEW_WCWK_64;
	u8 dai_ctww = 0;
	u8 fs;

	/* Set channews */
	switch (pawams_channews(pawams)) {
	case 1:
		if (da7213->fmt != DA7213_DAI_FOWMAT_DSP) {
			dev_eww(component->dev, "Mono suppowted onwy in DSP mode\n");
			wetuwn -EINVAW;
		}
		dai_ctww |= DA7213_DAI_MONO_MODE_EN;
		bweak;
	case 2:
		dai_ctww &= ~(DA7213_DAI_MONO_MODE_EN);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set DAI fowmat */
	switch (pawams_width(pawams)) {
	case 16:
		dai_ctww |= DA7213_DAI_WOWD_WENGTH_S16_WE;
		dai_cwk_mode = DA7213_DAI_BCWKS_PEW_WCWK_32; /* 32bit fow 1ch and 2ch */
		bweak;
	case 20:
		dai_ctww |= DA7213_DAI_WOWD_WENGTH_S20_WE;
		bweak;
	case 24:
		dai_ctww |= DA7213_DAI_WOWD_WENGTH_S24_WE;
		bweak;
	case 32:
		dai_ctww |= DA7213_DAI_WOWD_WENGTH_S32_WE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set sampwing wate */
	switch (pawams_wate(pawams)) {
	case 8000:
		fs = DA7213_SW_8000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	case 11025:
		fs = DA7213_SW_11025;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_90316800;
		bweak;
	case 12000:
		fs = DA7213_SW_12000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	case 16000:
		fs = DA7213_SW_16000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	case 22050:
		fs = DA7213_SW_22050;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_90316800;
		bweak;
	case 32000:
		fs = DA7213_SW_32000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	case 44100:
		fs = DA7213_SW_44100;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_90316800;
		bweak;
	case 48000:
		fs = DA7213_SW_48000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	case 88200:
		fs = DA7213_SW_88200;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_90316800;
		bweak;
	case 96000:
		fs = DA7213_SW_96000;
		da7213->out_wate = DA7213_PWW_FWEQ_OUT_98304000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, DA7213_DAI_CWK_MODE,
		DA7213_DAI_BCWKS_PEW_WCWK_MASK, dai_cwk_mode);

	snd_soc_component_update_bits(component, DA7213_DAI_CTWW,
		DA7213_DAI_WOWD_WENGTH_MASK | DA7213_DAI_MONO_MODE_MASK, dai_ctww);
	snd_soc_component_wwite(component, DA7213_SW, fs);

	wetuwn 0;
}

static int da7213_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	u8 dai_cwk_mode = 0, dai_ctww = 0;
	u8 dai_offset = 0;

	/* Set mastew/swave mode */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		da7213->mastew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		da7213->mastew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set cwock nowmaw/invewted */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			dai_cwk_mode |= DA7213_DAI_WCWK_POW_INV;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			dai_cwk_mode |= DA7213_DAI_CWK_POW_INV;
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			dai_cwk_mode |= DA7213_DAI_WCWK_POW_INV |
					DA7213_DAI_CWK_POW_INV;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* The bcwk is invewted wwt ASoC conventions */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			dai_cwk_mode |= DA7213_DAI_CWK_POW_INV;
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			dai_cwk_mode |= DA7213_DAI_WCWK_POW_INV |
					DA7213_DAI_CWK_POW_INV;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			dai_cwk_mode |= DA7213_DAI_WCWK_POW_INV;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Onwy I2S is suppowted */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		dai_ctww |= DA7213_DAI_FOWMAT_I2S_MODE;
		da7213->fmt = DA7213_DAI_FOWMAT_I2S_MODE;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		dai_ctww |= DA7213_DAI_FOWMAT_WEFT_J;
		da7213->fmt = DA7213_DAI_FOWMAT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		dai_ctww |= DA7213_DAI_FOWMAT_WIGHT_J;
		da7213->fmt = DA7213_DAI_FOWMAT_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_DSP_A: /* W data MSB aftew FWM WWC */
		dai_ctww |= DA7213_DAI_FOWMAT_DSP;
		dai_offset = 1;
		da7213->fmt = DA7213_DAI_FOWMAT_DSP;
		bweak;
	case SND_SOC_DAIFMT_DSP_B: /* W data MSB duwing FWM WWC */
		dai_ctww |= DA7213_DAI_FOWMAT_DSP;
		da7213->fmt = DA7213_DAI_FOWMAT_DSP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* By defauwt onwy 64 BCWK pew WCWK is suppowted */
	dai_cwk_mode |= DA7213_DAI_BCWKS_PEW_WCWK_64;

	snd_soc_component_update_bits(component, DA7213_DAI_CWK_MODE,
			    DA7213_DAI_BCWKS_PEW_WCWK_MASK |
			    DA7213_DAI_CWK_POW_MASK | DA7213_DAI_WCWK_POW_MASK,
			    dai_cwk_mode);
	snd_soc_component_update_bits(component, DA7213_DAI_CTWW, DA7213_DAI_FOWMAT_MASK,
			    dai_ctww);
	snd_soc_component_wwite(component, DA7213_DAI_OFFSET, dai_offset);

	wetuwn 0;
}

static int da7213_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute) {
		snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
				    DA7213_MUTE_EN, DA7213_MUTE_EN);
		snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
				    DA7213_MUTE_EN, DA7213_MUTE_EN);
	} ewse {
		snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
				    DA7213_MUTE_EN, 0);
		snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
				    DA7213_MUTE_EN, 0);
	}

	wetuwn 0;
}

#define DA7213_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static int da7213_set_component_syscwk(stwuct snd_soc_component *component,
				       int cwk_id, int souwce,
				       unsigned int fweq, int diw)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if ((da7213->cwk_swc == cwk_id) && (da7213->mcwk_wate == fweq))
		wetuwn 0;

	if (((fweq < 5000000) && (fweq != 32768)) || (fweq > 54000000)) {
		dev_eww(component->dev, "Unsuppowted MCWK vawue %d\n",
			fweq);
		wetuwn -EINVAW;
	}

	switch (cwk_id) {
	case DA7213_CWKSWC_MCWK:
		snd_soc_component_update_bits(component, DA7213_PWW_CTWW,
				    DA7213_PWW_MCWK_SQW_EN, 0);
		bweak;
	case DA7213_CWKSWC_MCWK_SQW:
		snd_soc_component_update_bits(component, DA7213_PWW_CTWW,
				    DA7213_PWW_MCWK_SQW_EN,
				    DA7213_PWW_MCWK_SQW_EN);
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown cwock souwce %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	da7213->cwk_swc = cwk_id;

	if (da7213->mcwk) {
		fweq = cwk_wound_wate(da7213->mcwk, fweq);
		wet = cwk_set_wate(da7213->mcwk, fweq);
		if (wet) {
			dev_eww(component->dev, "Faiwed to set cwock wate %d\n",
				fweq);
			wetuwn wet;
		}
	}

	da7213->mcwk_wate = fweq;

	wetuwn 0;
}

/* Suppowted PWW input fwequencies awe 32KHz, 5MHz - 54MHz. */
static int _da7213_set_component_pww(stwuct snd_soc_component *component,
				     int pww_id, int souwce,
				     unsigned int fwef, unsigned int fout)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);

	u8 pww_ctww, indiv_bits, indiv;
	u8 pww_fwac_top, pww_fwac_bot, pww_integew;
	u32 fweq_wef;
	u64 fwac_div;

	/* Wowkout input dividew based on MCWK wate */
	if (da7213->mcwk_wate == 32768) {
		if (!da7213->mastew) {
			dev_eww(component->dev,
				"32KHz onwy vawid if codec is cwock mastew\n");
			wetuwn -EINVAW;
		}

		/* 32KHz PWW Mode */
		indiv_bits = DA7213_PWW_INDIV_9_TO_18_MHZ;
		indiv = DA7213_PWW_INDIV_9_TO_18_MHZ_VAW;
		souwce = DA7213_SYSCWK_PWW_32KHZ;
		fweq_wef = 3750000;

	} ewse {
		if (da7213->mcwk_wate < 5000000) {
			dev_eww(component->dev,
				"PWW input cwock %d bewow vawid wange\n",
				da7213->mcwk_wate);
			wetuwn -EINVAW;
		} ewse if (da7213->mcwk_wate <= 9000000) {
			indiv_bits = DA7213_PWW_INDIV_5_TO_9_MHZ;
			indiv = DA7213_PWW_INDIV_5_TO_9_MHZ_VAW;
		} ewse if (da7213->mcwk_wate <= 18000000) {
			indiv_bits = DA7213_PWW_INDIV_9_TO_18_MHZ;
			indiv = DA7213_PWW_INDIV_9_TO_18_MHZ_VAW;
		} ewse if (da7213->mcwk_wate <= 36000000) {
			indiv_bits = DA7213_PWW_INDIV_18_TO_36_MHZ;
			indiv = DA7213_PWW_INDIV_18_TO_36_MHZ_VAW;
		} ewse if (da7213->mcwk_wate <= 54000000) {
			indiv_bits = DA7213_PWW_INDIV_36_TO_54_MHZ;
			indiv = DA7213_PWW_INDIV_36_TO_54_MHZ_VAW;
		} ewse {
			dev_eww(component->dev,
				"PWW input cwock %d above vawid wange\n",
				da7213->mcwk_wate);
			wetuwn -EINVAW;
		}
		fweq_wef = (da7213->mcwk_wate / indiv);
	}

	pww_ctww = indiv_bits;

	/* Configuwe PWW */
	switch (souwce) {
	case DA7213_SYSCWK_MCWK:
		snd_soc_component_update_bits(component, DA7213_PWW_CTWW,
				    DA7213_PWW_INDIV_MASK |
				    DA7213_PWW_MODE_MASK, pww_ctww);
		wetuwn 0;
	case DA7213_SYSCWK_PWW:
		bweak;
	case DA7213_SYSCWK_PWW_SWM:
		pww_ctww |= DA7213_PWW_SWM_EN;
		fout = DA7213_PWW_FWEQ_OUT_94310400;
		bweak;
	case DA7213_SYSCWK_PWW_32KHZ:
		if (da7213->mcwk_wate != 32768) {
			dev_eww(component->dev,
				"32KHz mode onwy vawid with 32KHz MCWK\n");
			wetuwn -EINVAW;
		}

		pww_ctww |= DA7213_PWW_32K_MODE | DA7213_PWW_SWM_EN;
		fout = DA7213_PWW_FWEQ_OUT_94310400;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid PWW config\n");
		wetuwn -EINVAW;
	}

	/* Cawcuwate dividews fow PWW */
	pww_integew = fout / fweq_wef;
	fwac_div = (u64)(fout % fweq_wef) * 8192UWW;
	do_div(fwac_div, fweq_wef);
	pww_fwac_top = (fwac_div >> DA7213_BYTE_SHIFT) & DA7213_BYTE_MASK;
	pww_fwac_bot = (fwac_div) & DA7213_BYTE_MASK;

	/* Wwite PWW dividews */
	snd_soc_component_wwite(component, DA7213_PWW_FWAC_TOP, pww_fwac_top);
	snd_soc_component_wwite(component, DA7213_PWW_FWAC_BOT, pww_fwac_bot);
	snd_soc_component_wwite(component, DA7213_PWW_INTEGEW, pww_integew);

	/* Enabwe PWW */
	pww_ctww |= DA7213_PWW_EN;
	snd_soc_component_update_bits(component, DA7213_PWW_CTWW,
			    DA7213_PWW_INDIV_MASK | DA7213_PWW_MODE_MASK,
			    pww_ctww);

	/* Assist 32KHz mode PWW wock */
	if (souwce == DA7213_SYSCWK_PWW_32KHZ) {
		snd_soc_component_wwite(component, 0xF0, 0x8B);
		snd_soc_component_wwite(component, 0xF1, 0x03);
		snd_soc_component_wwite(component, 0xF1, 0x01);
		snd_soc_component_wwite(component, 0xF0, 0x00);
	}

	wetuwn 0;
}

static int da7213_set_component_pww(stwuct snd_soc_component *component,
				    int pww_id, int souwce,
				    unsigned int fwef, unsigned int fout)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	da7213->fixed_cwk_auto_pww = fawse;

	wetuwn _da7213_set_component_pww(component, pww_id, souwce, fwef, fout);
}

/*
 * Sewect bewow fwom Sound Cawd, not Auto
 *	SND_SOC_DAIFMT_CBC_CFC
 *	SND_SOC_DAIFMT_CBP_CFP
 */
static u64 da7213_dai_fowmats =
	SND_SOC_POSSIBWE_DAIFMT_I2S	|
	SND_SOC_POSSIBWE_DAIFMT_WEFT_J	|
	SND_SOC_POSSIBWE_DAIFMT_WIGHT_J	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_A	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_B	|
	SND_SOC_POSSIBWE_DAIFMT_NB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_NB_IF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_IF;

/* DAI opewations */
static const stwuct snd_soc_dai_ops da7213_dai_ops = {
	.hw_pawams	= da7213_hw_pawams,
	.set_fmt	= da7213_set_dai_fmt,
	.mute_stweam	= da7213_mute,
	.no_captuwe_mute = 1,
	.auto_sewectabwe_fowmats	= &da7213_dai_fowmats,
	.num_auto_sewectabwe_fowmats	= 1,
};

static stwuct snd_soc_dai_dwivew da7213_dai = {
	.name = "da7213-hifi",
	/* Pwayback Capabiwities */
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA7213_FOWMATS,
	},
	/* Captuwe Capabiwities */
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA7213_FOWMATS,
	},
	.ops = &da7213_dai_ops,
	.symmetwic_wate = 1,
};

static int da7213_set_auto_pww(stwuct snd_soc_component *component, boow enabwe)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int mode;

	if (!da7213->fixed_cwk_auto_pww)
		wetuwn 0;

	da7213->mcwk_wate = cwk_get_wate(da7213->mcwk);

	if (enabwe) {
		/* Swave mode needs SWM fow non-hawmonic fwequencies */
		if (da7213->mastew)
			mode = DA7213_SYSCWK_PWW;
		ewse
			mode = DA7213_SYSCWK_PWW_SWM;

		/* PWW is not wequiwed fow hawmonic fwequencies */
		switch (da7213->out_wate) {
		case DA7213_PWW_FWEQ_OUT_90316800:
			if (da7213->mcwk_wate == 11289600 ||
			    da7213->mcwk_wate == 22579200 ||
			    da7213->mcwk_wate == 45158400)
				mode = DA7213_SYSCWK_MCWK;
			bweak;
		case DA7213_PWW_FWEQ_OUT_98304000:
			if (da7213->mcwk_wate == 12288000 ||
			    da7213->mcwk_wate == 24576000 ||
			    da7213->mcwk_wate == 49152000)
				mode = DA7213_SYSCWK_MCWK;

			bweak;
		defauwt:
			wetuwn -1;
		}
	} ewse {
		/* Disabwe PWW in standby */
		mode = DA7213_SYSCWK_MCWK;
	}

	wetuwn _da7213_set_component_pww(component, 0, mode,
					 da7213->mcwk_wate, da7213->out_wate);
}

static int da7213_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* Enabwe MCWK fow twansition to ON state */
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_STANDBY) {
			if (da7213->mcwk) {
				wet = cwk_pwepawe_enabwe(da7213->mcwk);
				if (wet) {
					dev_eww(component->dev,
						"Faiwed to enabwe mcwk\n");
					wetuwn wet;
				}

				da7213_set_auto_pww(component, twue);
			}
		}
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/* Enabwe VMID wefewence & mastew bias */
			snd_soc_component_update_bits(component, DA7213_WEFEWENCES,
					    DA7213_VMID_EN | DA7213_BIAS_EN,
					    DA7213_VMID_EN | DA7213_BIAS_EN);
		} ewse {
			/* Wemove MCWK */
			if (da7213->mcwk) {
				da7213_set_auto_pww(component, fawse);
				cwk_disabwe_unpwepawe(da7213->mcwk);
			}
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		/* Disabwe VMID wefewence & mastew bias */
		snd_soc_component_update_bits(component, DA7213_WEFEWENCES,
				    DA7213_VMID_EN | DA7213_BIAS_EN, 0);
		bweak;
	}
	wetuwn 0;
}

#if defined(CONFIG_OF)
/* DT */
static const stwuct of_device_id da7213_of_match[] = {
	{ .compatibwe = "dwg,da7212", },
	{ .compatibwe = "dwg,da7213", },
	{ }
};
MODUWE_DEVICE_TABWE(of, da7213_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id da7213_acpi_match[] = {
	{ "DWGS7212", 0},
	{ "DWGS7213", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, da7213_acpi_match);
#endif

static enum da7213_micbias_vowtage
	da7213_of_micbias_wvw(stwuct snd_soc_component *component, u32 vaw)
{
	switch (vaw) {
	case 1600:
		wetuwn DA7213_MICBIAS_1_6V;
	case 2200:
		wetuwn DA7213_MICBIAS_2_2V;
	case 2500:
		wetuwn DA7213_MICBIAS_2_5V;
	case 3000:
		wetuwn DA7213_MICBIAS_3_0V;
	defauwt:
		dev_wawn(component->dev, "Invawid micbias wevew\n");
		wetuwn DA7213_MICBIAS_2_2V;
	}
}

static enum da7213_dmic_data_sew
	da7213_of_dmic_data_sew(stwuct snd_soc_component *component, const chaw *stw)
{
	if (!stwcmp(stw, "wwise_wfaww")) {
		wetuwn DA7213_DMIC_DATA_WWISE_WFAWW;
	} ewse if (!stwcmp(stw, "wfaww_wwise")) {
		wetuwn DA7213_DMIC_DATA_WFAWW_WWISE;
	} ewse {
		dev_wawn(component->dev, "Invawid DMIC data sewect type\n");
		wetuwn DA7213_DMIC_DATA_WWISE_WFAWW;
	}
}

static enum da7213_dmic_sampwephase
	da7213_of_dmic_sampwephase(stwuct snd_soc_component *component, const chaw *stw)
{
	if (!stwcmp(stw, "on_cwkedge")) {
		wetuwn DA7213_DMIC_SAMPWE_ON_CWKEDGE;
	} ewse if (!stwcmp(stw, "between_cwkedge")) {
		wetuwn DA7213_DMIC_SAMPWE_BETWEEN_CWKEDGE;
	} ewse {
		dev_wawn(component->dev, "Invawid DMIC sampwe phase\n");
		wetuwn DA7213_DMIC_SAMPWE_ON_CWKEDGE;
	}
}

static enum da7213_dmic_cwk_wate
	da7213_of_dmic_cwkwate(stwuct snd_soc_component *component, u32 vaw)
{
	switch (vaw) {
	case 1500000:
		wetuwn DA7213_DMIC_CWK_1_5MHZ;
	case 3000000:
		wetuwn DA7213_DMIC_CWK_3_0MHZ;
	defauwt:
		dev_wawn(component->dev, "Invawid DMIC cwock wate\n");
		wetuwn DA7213_DMIC_CWK_1_5MHZ;
	}
}

static stwuct da7213_pwatfowm_data
	*da7213_fw_to_pdata(stwuct snd_soc_component *component)
{
	stwuct device *dev = component->dev;
	stwuct da7213_pwatfowm_data *pdata;
	const chaw *fw_stw;
	u32 fw_vaw32;

	pdata = devm_kzawwoc(component->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	if (device_pwopewty_wead_u32(dev, "dwg,micbias1-wvw", &fw_vaw32) >= 0)
		pdata->micbias1_wvw = da7213_of_micbias_wvw(component, fw_vaw32);
	ewse
		pdata->micbias1_wvw = DA7213_MICBIAS_2_2V;

	if (device_pwopewty_wead_u32(dev, "dwg,micbias2-wvw", &fw_vaw32) >= 0)
		pdata->micbias2_wvw = da7213_of_micbias_wvw(component, fw_vaw32);
	ewse
		pdata->micbias2_wvw = DA7213_MICBIAS_2_2V;

	if (!device_pwopewty_wead_stwing(dev, "dwg,dmic-data-sew", &fw_stw))
		pdata->dmic_data_sew = da7213_of_dmic_data_sew(component, fw_stw);
	ewse
		pdata->dmic_data_sew = DA7213_DMIC_DATA_WWISE_WFAWW;

	if (!device_pwopewty_wead_stwing(dev, "dwg,dmic-sampwephase", &fw_stw))
		pdata->dmic_sampwephase =
			da7213_of_dmic_sampwephase(component, fw_stw);
	ewse
		pdata->dmic_sampwephase = DA7213_DMIC_SAMPWE_ON_CWKEDGE;

	if (device_pwopewty_wead_u32(dev, "dwg,dmic-cwkwate", &fw_vaw32) >= 0)
		pdata->dmic_cwk_wate = da7213_of_dmic_cwkwate(component, fw_vaw32);
	ewse
		pdata->dmic_cwk_wate = DA7213_DMIC_CWK_3_0MHZ;

	wetuwn pdata;
}

static int da7213_pwobe(stwuct snd_soc_component *component)
{
	stwuct da7213_pwiv *da7213 = snd_soc_component_get_dwvdata(component);

	pm_wuntime_get_sync(component->dev);

	/* Defauwt to using AWC auto offset cawibwation mode. */
	snd_soc_component_update_bits(component, DA7213_AWC_CTWW1,
			    DA7213_AWC_CAWIB_MODE_MAN, 0);
	da7213->awc_cawib_auto = twue;

	/* Defauwt PC countew to fwee-wunning */
	snd_soc_component_update_bits(component, DA7213_PC_COUNT, DA7213_PC_FWEEWUN_MASK,
			    DA7213_PC_FWEEWUN_MASK);

	/* Enabwe aww Gain Wamps */
	snd_soc_component_update_bits(component, DA7213_AUX_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_AUX_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_DAC_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_HP_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_HP_W_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);
	snd_soc_component_update_bits(component, DA7213_WINE_CTWW,
			    DA7213_GAIN_WAMP_EN, DA7213_GAIN_WAMP_EN);

	/*
	 * Thewe awe two sepawate contwow bits fow input and output mixews as
	 * weww as headphone and wine outs.
	 * One to enabwe cowwesponding ampwifiew and othew to enabwe its
	 * output. As ampwifiew bits awe wewated to powew contwow, they awe
	 * being managed by DAPM whiwe othew (non powew wewated) bits awe
	 * enabwed hewe
	 */
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_CTWW,
			    DA7213_MIXIN_MIX_EN, DA7213_MIXIN_MIX_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_W_CTWW,
			    DA7213_MIXIN_MIX_EN, DA7213_MIXIN_MIX_EN);

	snd_soc_component_update_bits(component, DA7213_MIXOUT_W_CTWW,
			    DA7213_MIXOUT_MIX_EN, DA7213_MIXOUT_MIX_EN);
	snd_soc_component_update_bits(component, DA7213_MIXOUT_W_CTWW,
			    DA7213_MIXOUT_MIX_EN, DA7213_MIXOUT_MIX_EN);

	snd_soc_component_update_bits(component, DA7213_HP_W_CTWW,
			    DA7213_HP_AMP_OE, DA7213_HP_AMP_OE);
	snd_soc_component_update_bits(component, DA7213_HP_W_CTWW,
			    DA7213_HP_AMP_OE, DA7213_HP_AMP_OE);

	snd_soc_component_update_bits(component, DA7213_WINE_CTWW,
			    DA7213_WINE_AMP_OE, DA7213_WINE_AMP_OE);

	/* Handwe DT/Pwatfowm data */
	da7213->pdata = dev_get_pwatdata(component->dev);
	if (!da7213->pdata)
		da7213->pdata = da7213_fw_to_pdata(component);

	/* Set pwatfowm data vawues */
	if (da7213->pdata) {
		stwuct da7213_pwatfowm_data *pdata = da7213->pdata;
		u8 micbias_wvw = 0, dmic_cfg = 0;

		/* Set Mic Bias vowtages */
		switch (pdata->micbias1_wvw) {
		case DA7213_MICBIAS_1_6V:
		case DA7213_MICBIAS_2_2V:
		case DA7213_MICBIAS_2_5V:
		case DA7213_MICBIAS_3_0V:
			micbias_wvw |= (pdata->micbias1_wvw <<
					DA7213_MICBIAS1_WEVEW_SHIFT);
			bweak;
		}
		switch (pdata->micbias2_wvw) {
		case DA7213_MICBIAS_1_6V:
		case DA7213_MICBIAS_2_2V:
		case DA7213_MICBIAS_2_5V:
		case DA7213_MICBIAS_3_0V:
			micbias_wvw |= (pdata->micbias2_wvw <<
					 DA7213_MICBIAS2_WEVEW_SHIFT);
			bweak;
		}
		snd_soc_component_update_bits(component, DA7213_MICBIAS_CTWW,
				    DA7213_MICBIAS1_WEVEW_MASK |
				    DA7213_MICBIAS2_WEVEW_MASK, micbias_wvw);

		/* Set DMIC configuwation */
		switch (pdata->dmic_data_sew) {
		case DA7213_DMIC_DATA_WFAWW_WWISE:
		case DA7213_DMIC_DATA_WWISE_WFAWW:
			dmic_cfg |= (pdata->dmic_data_sew <<
				     DA7213_DMIC_DATA_SEW_SHIFT);
			bweak;
		}
		switch (pdata->dmic_sampwephase) {
		case DA7213_DMIC_SAMPWE_ON_CWKEDGE:
		case DA7213_DMIC_SAMPWE_BETWEEN_CWKEDGE:
			dmic_cfg |= (pdata->dmic_sampwephase <<
				     DA7213_DMIC_SAMPWEPHASE_SHIFT);
			bweak;
		}
		switch (pdata->dmic_cwk_wate) {
		case DA7213_DMIC_CWK_3_0MHZ:
		case DA7213_DMIC_CWK_1_5MHZ:
			dmic_cfg |= (pdata->dmic_cwk_wate <<
				     DA7213_DMIC_CWK_WATE_SHIFT);
			bweak;
		}
		snd_soc_component_update_bits(component, DA7213_MIC_CONFIG,
				    DA7213_DMIC_DATA_SEW_MASK |
				    DA7213_DMIC_SAMPWEPHASE_MASK |
				    DA7213_DMIC_CWK_WATE_MASK, dmic_cfg);
	}

	pm_wuntime_put_sync(component->dev);

	/* Check if MCWK pwovided */
	da7213->mcwk = devm_cwk_get(component->dev, "mcwk");
	if (IS_EWW(da7213->mcwk)) {
		if (PTW_EWW(da7213->mcwk) != -ENOENT)
			wetuwn PTW_EWW(da7213->mcwk);
		ewse
			da7213->mcwk = NUWW;
	} ewse {
		/* Do automatic PWW handwing assuming fixed cwock untiw
		 * set_pww() has been cawwed. This makes the codec usabwe
		 * with the simpwe-audio-cawd dwivew. */
		da7213->fixed_cwk_auto_pww = twue;
	}

	/* Defauwt infinite tone gen, stawt/stop by Kcontwow */
	snd_soc_component_wwite(component, DA7213_TONE_GEN_CYCWES, DA7213_BEEP_CYCWES_MASK);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_da7213 = {
	.pwobe			= da7213_pwobe,
	.set_bias_wevew		= da7213_set_bias_wevew,
	.contwows		= da7213_snd_contwows,
	.num_contwows		= AWWAY_SIZE(da7213_snd_contwows),
	.dapm_widgets		= da7213_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(da7213_dapm_widgets),
	.dapm_woutes		= da7213_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(da7213_audio_map),
	.set_syscwk		= da7213_set_component_syscwk,
	.set_pww		= da7213_set_component_pww,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config da7213_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = da7213_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(da7213_weg_defauwts),
	.vowatiwe_weg = da7213_vowatiwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
};

static void da7213_powew_off(void *data)
{
	stwuct da7213_pwiv *da7213 = data;
	weguwatow_buwk_disabwe(DA7213_NUM_SUPPWIES, da7213->suppwies);
}

static const chaw *da7213_suppwy_names[DA7213_NUM_SUPPWIES] = {
	[DA7213_SUPPWY_VDDA] = "VDDA",
	[DA7213_SUPPWY_VDDIO] = "VDDIO",
};

static int da7213_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da7213_pwiv *da7213;
	int i, wet;

	da7213 = devm_kzawwoc(&i2c->dev, sizeof(*da7213), GFP_KEWNEW);
	if (!da7213)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, da7213);

	/* Get wequiwed suppwies */
	fow (i = 0; i < DA7213_NUM_SUPPWIES; ++i)
		da7213->suppwies[i].suppwy = da7213_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, DA7213_NUM_SUPPWIES,
				      da7213->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(DA7213_NUM_SUPPWIES, da7213->suppwies);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&i2c->dev, da7213_powew_off, da7213);
	if (wet < 0)
		wetuwn wet;

	da7213->wegmap = devm_wegmap_init_i2c(i2c, &da7213_wegmap_config);
	if (IS_EWW(da7213->wegmap)) {
		wet = PTW_EWW(da7213->wegmap);
		dev_eww(&i2c->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_set_autosuspend_deway(&i2c->dev, 100);
	pm_wuntime_use_autosuspend(&i2c->dev);
	pm_wuntime_set_active(&i2c->dev);
	pm_wuntime_enabwe(&i2c->dev);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_da7213, &da7213_dai, 1);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew da7213 component: %d\n",
			wet);
	}
	wetuwn wet;
}

static void da7213_i2c_wemove(stwuct i2c_cwient *i2c)
{
	pm_wuntime_disabwe(&i2c->dev);
}

static int __maybe_unused da7213_wuntime_suspend(stwuct device *dev)
{
	stwuct da7213_pwiv *da7213 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(da7213->wegmap, twue);
	wegcache_mawk_diwty(da7213->wegmap);
	weguwatow_buwk_disabwe(DA7213_NUM_SUPPWIES, da7213->suppwies);

	wetuwn 0;
}

static int __maybe_unused da7213_wuntime_wesume(stwuct device *dev)
{
	stwuct da7213_pwiv *da7213 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(DA7213_NUM_SUPPWIES, da7213->suppwies);
	if (wet < 0)
		wetuwn wet;
	wegcache_cache_onwy(da7213->wegmap, fawse);
	wegcache_sync(da7213->wegmap);
	wetuwn 0;
}

static const stwuct dev_pm_ops da7213_pm = {
	SET_WUNTIME_PM_OPS(da7213_wuntime_suspend, da7213_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id da7213_i2c_id[] = {
	{ "da7213", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, da7213_i2c_id);

/* I2C codec contwow wayew */
static stwuct i2c_dwivew da7213_i2c_dwivew = {
	.dwivew = {
		.name = "da7213",
		.of_match_tabwe = of_match_ptw(da7213_of_match),
		.acpi_match_tabwe = ACPI_PTW(da7213_acpi_match),
		.pm = &da7213_pm,
	},
	.pwobe		= da7213_i2c_pwobe,
	.wemove		= da7213_i2c_wemove,
	.id_tabwe	= da7213_i2c_id,
};

moduwe_i2c_dwivew(da7213_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC DA7213 Codec dwivew");
MODUWE_AUTHOW("Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>");
MODUWE_AUTHOW("David Wau <David.Wau.opensouwce@dm.wenesas.com>");
MODUWE_WICENSE("GPW");
