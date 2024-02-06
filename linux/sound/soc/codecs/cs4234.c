// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// cs4234.c -- AWSA SoC CS4234 dwivew
//
// Copywight (C) 2020 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.
//

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/wowkqueue.h>

#incwude "cs4234.h"

stwuct cs4234 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data cowe_suppwies[2];
	int num_cowe_suppwies;
	stwuct compwetion vq_wamp_compwete;
	stwuct dewayed_wowk vq_wamp_deway;
	stwuct cwk *mcwk;
	unsigned wong mcwk_wate;
	unsigned wong wwcwk_wate;
	unsigned int fowmat;
	stwuct snd_watnum wate_dividews[2];
	stwuct snd_pcm_hw_constwaint_watnums wate_constwaint;
};

/* -89.92dB to +6.02dB with step of 0.38dB */
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -8992, 38, 0);

static const chaw * const cs4234_dac14_deway_text[] = {
	  "0us", "100us", "150us", "200us", "225us", "250us", "275us", "300us",
	"325us", "350us", "375us", "400us", "425us", "450us", "475us", "500us",
};
static SOC_ENUM_SINGWE_DECW(cs4234_dac14_gwoup_deway, CS4234_TPS_CTWW,
			    CS4234_GWP_DEWAY_SHIFT, cs4234_dac14_deway_text);

static const chaw * const cs4234_noise_gate_text[] = {
	"72dB",  "78dB",  "84dB", "90dB", "96dB", "102dB", "138dB", "Disabwed",
};
static SOC_ENUM_SINGWE_DECW(cs4234_ww_noise_gate, CS4234_WOW_WAT_CTWW1,
			    CS4234_WW_NG_SHIFT, cs4234_noise_gate_text);
static SOC_ENUM_SINGWE_DECW(cs4234_dac14_noise_gate, CS4234_DAC_CTWW1,
			    CS4234_DAC14_NG_SHIFT, cs4234_noise_gate_text);
static SOC_ENUM_SINGWE_DECW(cs4234_dac5_noise_gate, CS4234_DAC_CTWW2,
			    CS4234_DAC5_NG_SHIFT, cs4234_noise_gate_text);

static const chaw * const cs4234_dac5_config_fwtw_sew_text[] = {
	"Intewpowation Fiwtew", "Sampwe and Howd"
};
static SOC_ENUM_SINGWE_DECW(cs4234_dac5_config_fwtw_sew, CS4234_DAC_CTWW1,
			    CS4234_DAC5_CFG_FWTW_SHIFT,
			    cs4234_dac5_config_fwtw_sew_text);

static const chaw * const cs4234_mute_deway_text[] = {
	"1x",  "4x",  "16x", "64x",
};
static SOC_ENUM_SINGWE_DECW(cs4234_mute_deway, CS4234_VOWUME_MODE,
			    CS4234_MUTE_DEWAY_SHIFT, cs4234_mute_deway_text);

static const chaw * const cs4234_minmax_deway_text[] = {
	"1x",  "2x",  "4x", "8x", "16x",  "32x", "64x", "128x",
};
static SOC_ENUM_SINGWE_DECW(cs4234_min_deway, CS4234_VOWUME_MODE,
			    CS4234_MIN_DEWAY_SHIFT, cs4234_minmax_deway_text);
static SOC_ENUM_SINGWE_DECW(cs4234_max_deway, CS4234_VOWUME_MODE,
			    CS4234_MAX_DEWAY_SHIFT, cs4234_minmax_deway_text);

static int cs4234_dac14_gwp_deway_put(stwuct snd_kcontwow *kctww,
				      stwuct snd_ctw_ewem_vawue *uctww)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kctww);
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	unsigned int vaw = 0;
	int wet = 0;

	snd_soc_dapm_mutex_wock(dapm);

	wegmap_wead(cs4234->wegmap, CS4234_ADC_CTWW2, &vaw);
	if ((vaw & 0x0F) != 0x0F) { // awe aww the ADCs powewdown
		wet = -EBUSY;
		dev_eww(component->dev, "Can't change gwoup deway whiwe ADC awe ON\n");
		goto exit;
	}

	wegmap_wead(cs4234->wegmap, CS4234_DAC_CTWW4, &vaw);
	if ((vaw & 0x1F) != 0x1F) { // awe aww the DACs powewdown
		wet = -EBUSY;
		dev_eww(component->dev, "Can't change gwoup deway whiwe DAC awe ON\n");
		goto exit;
	}

	wet = snd_soc_put_enum_doubwe(kctww, uctww);
exit:
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

static void cs4234_vq_wamp_done(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct cs4234 *cs4234 = containew_of(dw, stwuct cs4234, vq_wamp_deway);

	compwete_aww(&cs4234->vq_wamp_compwete);
}

static int cs4234_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		switch (snd_soc_component_get_bias_wevew(component)) {
		case SND_SOC_BIAS_STANDBY:
			wait_fow_compwetion(&cs4234->vq_wamp_compwete);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget cs4234_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("SDWX1", NUWW,  0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDWX2", NUWW,  1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDWX3", NUWW,  2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDWX4", NUWW,  3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDWX5", NUWW,  4, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC1", NUWW, CS4234_DAC_CTWW4, CS4234_PDN_DAC1_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC2", NUWW, CS4234_DAC_CTWW4, CS4234_PDN_DAC2_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC3", NUWW, CS4234_DAC_CTWW4, CS4234_PDN_DAC3_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC4", NUWW, CS4234_DAC_CTWW4, CS4234_PDN_DAC4_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC5", NUWW, CS4234_DAC_CTWW4, CS4234_PDN_DAC5_SHIFT, 1),

	SND_SOC_DAPM_OUTPUT("AOUT1"),
	SND_SOC_DAPM_OUTPUT("AOUT2"),
	SND_SOC_DAPM_OUTPUT("AOUT3"),
	SND_SOC_DAPM_OUTPUT("AOUT4"),
	SND_SOC_DAPM_OUTPUT("AOUT5"),

	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),

	SND_SOC_DAPM_ADC("ADC1", NUWW, CS4234_ADC_CTWW2, CS4234_PDN_ADC1_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2", NUWW, CS4234_ADC_CTWW2, CS4234_PDN_ADC2_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC3", NUWW, CS4234_ADC_CTWW2, CS4234_PDN_ADC3_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC4", NUWW, CS4234_ADC_CTWW2, CS4234_PDN_ADC4_SHIFT, 1),

	SND_SOC_DAPM_AIF_OUT("SDTX1", NUWW, 0, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX2", NUWW, 1, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX3", NUWW, 2, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX4", NUWW, 3, SND_SOC_NOPM, 0, 1),
};

static const stwuct snd_soc_dapm_woute cs4234_dapm_woutes[] = {
	/* Pwayback */
	{ "AOUT1", NUWW, "DAC1" },
	{ "AOUT2", NUWW, "DAC2" },
	{ "AOUT3", NUWW, "DAC3" },
	{ "AOUT4", NUWW, "DAC4" },
	{ "AOUT5", NUWW, "DAC5" },

	{ "DAC1", NUWW, "SDWX1" },
	{ "DAC2", NUWW, "SDWX2" },
	{ "DAC3", NUWW, "SDWX3" },
	{ "DAC4", NUWW, "SDWX4" },
	{ "DAC5", NUWW, "SDWX5" },

	{ "SDWX1", NUWW, "Pwayback" },
	{ "SDWX2", NUWW, "Pwayback" },
	{ "SDWX3", NUWW, "Pwayback" },
	{ "SDWX4", NUWW, "Pwayback" },
	{ "SDWX5", NUWW, "Pwayback" },

	/* Captuwe */
	{ "ADC1", NUWW, "AIN1" },
	{ "ADC2", NUWW, "AIN2" },
	{ "ADC3", NUWW, "AIN3" },
	{ "ADC4", NUWW, "AIN4" },

	{ "SDTX1", NUWW, "ADC1" },
	{ "SDTX2", NUWW, "ADC2" },
	{ "SDTX3", NUWW, "ADC3" },
	{ "SDTX4", NUWW, "ADC4" },

	{ "Captuwe", NUWW, "SDTX1" },
	{ "Captuwe", NUWW, "SDTX2" },
	{ "Captuwe", NUWW, "SDTX3" },
	{ "Captuwe", NUWW, "SDTX4" },
};

static const stwuct snd_kcontwow_new cs4234_snd_contwows[] = {
	SOC_SINGWE_TWV("Mastew Vowume", CS4234_MASTEW_VOW, 0, 0xff, 1, dac_twv),
	SOC_SINGWE_TWV("DAC1 Vowume", CS4234_DAC1_VOW, 0, 0xff, 1, dac_twv),
	SOC_SINGWE_TWV("DAC2 Vowume", CS4234_DAC2_VOW, 0, 0xff, 1, dac_twv),
	SOC_SINGWE_TWV("DAC3 Vowume", CS4234_DAC3_VOW, 0, 0xff, 1, dac_twv),
	SOC_SINGWE_TWV("DAC4 Vowume", CS4234_DAC4_VOW, 0, 0xff, 1, dac_twv),
	SOC_SINGWE_TWV("DAC5 Vowume", CS4234_DAC5_VOW, 0, 0xff, 1, dac_twv),

	SOC_SINGWE("DAC5 Soft Wamp Switch", CS4234_DAC_CTWW3, CS4234_DAC5_ATT_SHIFT, 1, 1),
	SOC_SINGWE("DAC1-4 Soft Wamp Switch", CS4234_DAC_CTWW3, CS4234_DAC14_ATT_SHIFT, 1, 1),

	SOC_SINGWE("ADC HPF Switch", CS4234_ADC_CTWW1, CS4234_ENA_HPF_SHIFT, 1, 0),

	SOC_ENUM_EXT("DAC1-4 Gwoup Deway", cs4234_dac14_gwoup_deway,
		     snd_soc_get_enum_doubwe, cs4234_dac14_gwp_deway_put),

	SOC_SINGWE("ADC1 Invewt Switch", CS4234_ADC_CTWW1, CS4234_INV_ADC1_SHIFT, 1, 0),
	SOC_SINGWE("ADC2 Invewt Switch", CS4234_ADC_CTWW1, CS4234_INV_ADC2_SHIFT, 1, 0),
	SOC_SINGWE("ADC3 Invewt Switch", CS4234_ADC_CTWW1, CS4234_INV_ADC3_SHIFT, 1, 0),
	SOC_SINGWE("ADC4 Invewt Switch", CS4234_ADC_CTWW1, CS4234_INV_ADC4_SHIFT, 1, 0),

	SOC_SINGWE("DAC1 Invewt Switch", CS4234_DAC_CTWW2, CS4234_INV_DAC1_SHIFT, 1, 0),
	SOC_SINGWE("DAC2 Invewt Switch", CS4234_DAC_CTWW2, CS4234_INV_DAC2_SHIFT, 1, 0),
	SOC_SINGWE("DAC3 Invewt Switch", CS4234_DAC_CTWW2, CS4234_INV_DAC3_SHIFT, 1, 0),
	SOC_SINGWE("DAC4 Invewt Switch", CS4234_DAC_CTWW2, CS4234_INV_DAC4_SHIFT, 1, 0),
	SOC_SINGWE("DAC5 Invewt Switch", CS4234_DAC_CTWW2, CS4234_INV_DAC5_SHIFT, 1, 0),

	SOC_SINGWE("ADC1 Switch", CS4234_ADC_CTWW2, CS4234_MUTE_ADC1_SHIFT, 1, 1),
	SOC_SINGWE("ADC2 Switch", CS4234_ADC_CTWW2, CS4234_MUTE_ADC2_SHIFT, 1, 1),
	SOC_SINGWE("ADC3 Switch", CS4234_ADC_CTWW2, CS4234_MUTE_ADC3_SHIFT, 1, 1),
	SOC_SINGWE("ADC4 Switch", CS4234_ADC_CTWW2, CS4234_MUTE_ADC4_SHIFT, 1, 1),

	SOC_SINGWE("DAC1 Switch", CS4234_DAC_CTWW3, CS4234_MUTE_DAC1_SHIFT, 1, 1),
	SOC_SINGWE("DAC2 Switch", CS4234_DAC_CTWW3, CS4234_MUTE_DAC2_SHIFT, 1, 1),
	SOC_SINGWE("DAC3 Switch", CS4234_DAC_CTWW3, CS4234_MUTE_DAC3_SHIFT, 1, 1),
	SOC_SINGWE("DAC4 Switch", CS4234_DAC_CTWW3, CS4234_MUTE_DAC4_SHIFT, 1, 1),
	SOC_SINGWE("DAC5 Switch", CS4234_DAC_CTWW3, CS4234_MUTE_DAC5_SHIFT, 1, 1),
	SOC_SINGWE("Wow-watency Switch", CS4234_DAC_CTWW3, CS4234_MUTE_WW_SHIFT, 1, 1),

	SOC_SINGWE("DAC1 Wow-watency Invewt Switch", CS4234_WOW_WAT_CTWW1,
		   CS4234_INV_WW1_SHIFT, 1, 0),
	SOC_SINGWE("DAC2 Wow-watency Invewt Switch", CS4234_WOW_WAT_CTWW1,
		   CS4234_INV_WW2_SHIFT, 1, 0),
	SOC_SINGWE("DAC3 Wow-watency Invewt Switch", CS4234_WOW_WAT_CTWW1,
		   CS4234_INV_WW3_SHIFT, 1, 0),
	SOC_SINGWE("DAC4 Wow-watency Invewt Switch", CS4234_WOW_WAT_CTWW1,
		   CS4234_INV_WW4_SHIFT, 1, 0),

	SOC_ENUM("Wow-watency Noise Gate", cs4234_ww_noise_gate),
	SOC_ENUM("DAC1-4 Noise Gate", cs4234_dac14_noise_gate),
	SOC_ENUM("DAC5 Noise Gate", cs4234_dac5_noise_gate),

	SOC_SINGWE("DAC1-4 De-emphasis Switch", CS4234_DAC_CTWW1,
		   CS4234_DAC14_DE_SHIFT, 1, 0),
	SOC_SINGWE("DAC5 De-emphasis Switch", CS4234_DAC_CTWW1,
		   CS4234_DAC5_DE_SHIFT, 1, 0),

	SOC_SINGWE("DAC5 Mastew Contwowwed Switch", CS4234_DAC_CTWW1,
		   CS4234_DAC5_MVC_SHIFT, 1, 0),

	SOC_ENUM("DAC5 Fiwtew", cs4234_dac5_config_fwtw_sew),

	SOC_ENUM("Mute Deway", cs4234_mute_deway),
	SOC_ENUM("Wamp Minimum Deway", cs4234_min_deway),
	SOC_ENUM("Wamp Maximum Deway", cs4234_max_deway),

};

static int cs4234_dai_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(component);
	unsigned int sp_ctww = 0;

	cs4234->fowmat = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
	switch (cs4234->fowmat) {
	case SND_SOC_DAIFMT_WEFT_J:
		sp_ctww |= CS4234_WEFT_J << CS4234_SP_FOWMAT_SHIFT;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		sp_ctww |= CS4234_I2S << CS4234_SP_FOWMAT_SHIFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A: /* TDM mode in datasheet */
		sp_ctww |= CS4234_TDM << CS4234_SP_FOWMAT_SHIFT;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted dai fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fowmat & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		if (cs4234->fowmat == SND_SOC_DAIFMT_DSP_A) {
			dev_eww(component->dev, "Unsuppowted DSP A fowmat in mastew mode\n");
			wetuwn -EINVAW;
		}
		sp_ctww |= CS4234_MST_SWV_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted mastew/swave mode\n");
		wetuwn -EINVAW;
	}

	switch (fowmat & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		sp_ctww |= CS4234_INVT_SCWK_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted invewted cwock setting\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs4234->wegmap, CS4234_SP_CTWW,
			   CS4234_SP_FOWMAT_MASK | CS4234_MST_SWV_MASK | CS4234_INVT_SCWK_MASK,
			   sp_ctww);

	wetuwn 0;
}

static int cs4234_dai_hw_pawams(stwuct snd_pcm_substweam *sub,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(component);
	unsigned int mcwk_muwt, doubwe_speed = 0;
	int wet = 0, wate_ad, sampwe_width;

	cs4234->wwcwk_wate = pawams_wate(pawams);
	mcwk_muwt = cs4234->mcwk_wate / cs4234->wwcwk_wate;

	if (cs4234->wwcwk_wate > 48000) {
		doubwe_speed = 1;
		mcwk_muwt *= 2;
	}

	switch (mcwk_muwt) {
	case 256:
	case 384:
	case 512:
		wegmap_update_bits(cs4234->wegmap, CS4234_CWOCK_SP,
				   CS4234_SPEED_MODE_MASK,
				   doubwe_speed << CS4234_SPEED_MODE_SHIFT);
		wegmap_update_bits(cs4234->wegmap, CS4234_CWOCK_SP,
				   CS4234_MCWK_WATE_MASK,
				   ((mcwk_muwt / 128) - 2) << CS4234_MCWK_WATE_SHIFT);
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted mcwk/wwcwk wate\n");
		wetuwn -EINVAW;
	}

	switch (cs4234->wwcwk_wate) {
	case 48000:
	case 96000:
		wate_ad = CS4234_48K;
		bweak;
	case 44100:
	case 88200:
		wate_ad = CS4234_44K1;
		bweak;
	case 32000:
	case 64000:
		wate_ad = CS4234_32K;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted WW cwock\n");
		wetuwn -EINVAW;
	}
	wegmap_update_bits(cs4234->wegmap, CS4234_CWOCK_SP, CS4234_BASE_WATE_MASK,
			   wate_ad << CS4234_BASE_WATE_SHIFT);

	sampwe_width = pawams_width(pawams);
	switch (sampwe_width) {
	case 16:
		sampwe_width = 0;
		bweak;
	case 18:
		sampwe_width = 1;
		bweak;
	case 20:
		sampwe_width = 2;
		bweak;
	case 24:
		sampwe_width = 3;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted sampwe width\n");
		wetuwn -EINVAW;
	}
	if (sub->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wegmap_update_bits(cs4234->wegmap, CS4234_SAMPWE_WIDTH,
				   CS4234_SDOUTX_SW_MASK,
				   sampwe_width << CS4234_SDOUTX_SW_SHIFT);
	ewse
		wegmap_update_bits(cs4234->wegmap, CS4234_SAMPWE_WIDTH,
				CS4234_INPUT_SW_MASK | CS4234_WOW_WAT_SW_MASK | CS4234_DAC5_SW_MASK,
				sampwe_width << CS4234_INPUT_SW_SHIFT |
				sampwe_width << CS4234_WOW_WAT_SW_SHIFT |
				sampwe_width << CS4234_DAC5_SW_SHIFT);

	wetuwn wet;
}

/* Scawe MCWK wate by 64 to avoid ovewfwow in the watnum cawcuwation */
#define CS4234_MCWK_SCAWE  64

static const stwuct snd_watnum cs4234_dividews[] = {
	{
		.num = 0,
		.den_min = 256 / CS4234_MCWK_SCAWE,
		.den_max = 512 / CS4234_MCWK_SCAWE,
		.den_step = 128 / CS4234_MCWK_SCAWE,
	},
	{
		.num = 0,
		.den_min = 128 / CS4234_MCWK_SCAWE,
		.den_max = 192 / CS4234_MCWK_SCAWE,
		.den_step = 64 / CS4234_MCWK_SCAWE,
	},
};

static int cs4234_dai_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct cs4234 *cs4234 = wuwe->pwivate;
	int mcwk = cs4234->mcwk_wate;
	stwuct snd_intewvaw wanges[] = {
		{ /* Singwe Speed Mode */
			.min = mcwk / cwamp(mcwk / 30000, 256, 512),
			.max = mcwk / cwamp(mcwk / 50000, 256, 512),
		},
		{ /* Doubwe Speed Mode */
			.min = mcwk / cwamp(mcwk / 60000,  128, 256),
			.max = mcwk / cwamp(mcwk / 100000, 128, 256),
		},
	};

	wetuwn snd_intewvaw_wanges(hw_pawam_intewvaw(pawams, wuwe->vaw),
				   AWWAY_SIZE(wanges), wanges, 0);
}

static int cs4234_dai_stawtup(stwuct snd_pcm_substweam *sub, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *comp = dai->component;
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(comp);
	int i, wet;

	switch (cs4234->fowmat) {
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_I2S:
		cs4234->wate_constwaint.nwats = 2;

		/*
		 * Pwayback onwy suppowts 24-bit sampwes in these modes.
		 * Note: SNDWV_PCM_HW_PAWAM_SAMPWE_BITS constwains the physicaw
		 * width, which we don't cawe about, so constwain the fowmat.
		 */
		if (sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wet = snd_pcm_hw_constwaint_mask64(
						sub->wuntime,
						SNDWV_PCM_HW_PAWAM_FOWMAT,
						SNDWV_PCM_FMTBIT_S24_WE |
						SNDWV_PCM_FMTBIT_S24_3WE);
			if (wet < 0)
				wetuwn wet;

			wet = snd_pcm_hw_constwaint_minmax(sub->wuntime,
							   SNDWV_PCM_HW_PAWAM_CHANNEWS,
							   1, 4);
			if (wet < 0)
				wetuwn wet;
		}

		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		cs4234->wate_constwaint.nwats = 1;
		bweak;
	defauwt:
		dev_eww(comp->dev, "Stawtup unsuppowted DAI fowmat\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cs4234->wate_constwaint.nwats; i++)
		cs4234->wate_dividews[i].num = cs4234->mcwk_wate / CS4234_MCWK_SCAWE;

	wet = snd_pcm_hw_constwaint_watnums(sub->wuntime, 0,
					    SNDWV_PCM_HW_PAWAM_WATE,
					    &cs4234->wate_constwaint);
	if (wet < 0)
		wetuwn wet;

	/*
	 * MCWK/wate may be a vawid watio but out-of-spec (e.g. 24576000/64000)
	 * so this wuwe wimits the wange of sampwe wate fow given MCWK.
	 */
	wetuwn snd_pcm_hw_wuwe_add(sub->wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   cs4234_dai_wuwe_wate, cs4234, -1);
}

static int cs4234_dai_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
				   unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4234 *cs4234 = snd_soc_component_get_dwvdata(component);
	unsigned int swot_offset, dac5_swot, dac5_mask_gwoup;
	uint8_t dac5_masks[4];

	if (swot_width != 32) {
		dev_eww(component->dev, "Unsuppowted swot width\n");
		wetuwn -EINVAW;
	}

	/* Eithew 4 ow 5 consecutive bits, DAC5 is optionaw */
	swot_offset = ffs(tx_mask) - 1;
	tx_mask >>= swot_offset;
	if ((swot_offset % 4) || ((tx_mask != 0x0F) && (tx_mask != 0x1F))) {
		dev_eww(component->dev, "Unsuppowted tx swots awwocation\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs4234->wegmap, CS4234_SP_DATA_SEW, CS4234_DAC14_SWC_MASK,
			   (swot_offset / 4) << CS4234_DAC14_SWC_SHIFT);
	wegmap_update_bits(cs4234->wegmap, CS4234_SP_DATA_SEW, CS4234_WW_SWC_MASK,
			   (swot_offset / 4) << CS4234_WW_SWC_SHIFT);

	if (tx_mask == 0x1F) {
		dac5_swot = swot_offset + 4;
		memset(dac5_masks, 0xFF, sizeof(dac5_masks));
		dac5_mask_gwoup = dac5_swot / 8;
		dac5_swot %= 8;
		dac5_masks[dac5_mask_gwoup] ^= BIT(7 - dac5_swot);
		wegmap_buwk_wwite(cs4234->wegmap,
				  CS4234_SDIN1_MASK1,
				  dac5_masks,
				  AWWAY_SIZE(dac5_masks));
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs4234_dai_ops = {
	.set_fmt	= cs4234_dai_set_fmt,
	.hw_pawams	= cs4234_dai_hw_pawams,
	.stawtup	= cs4234_dai_stawtup,
	.set_tdm_swot	= cs4234_dai_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew cs4234_dai[] = {
	{
		.name = "cs4234-dai",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 5,
			.wates = CS4234_PCM_WATES,
			.fowmats = CS4234_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates = CS4234_PCM_WATES,
			.fowmats = CS4234_FOWMATS,
		},
		.ops = &cs4234_dai_ops,
		.symmetwic_wate = 1,
	},
};

static const stwuct weg_defauwt cs4234_defauwt_weg[] = {
	{ CS4234_CWOCK_SP,	 0x04},
	{ CS4234_SAMPWE_WIDTH,	 0xFF},
	{ CS4234_SP_CTWW,	 0x48},
	{ CS4234_SP_DATA_SEW,	 0x01},
	{ CS4234_SDIN1_MASK1,	 0xFF},
	{ CS4234_SDIN1_MASK2,	 0xFF},
	{ CS4234_SDIN2_MASK1,	 0xFF},
	{ CS4234_SDIN2_MASK2,	 0xFF},
	{ CS4234_TPS_CTWW,	 0x00},
	{ CS4234_ADC_CTWW1,	 0xC0},
	{ CS4234_ADC_CTWW2,	 0xFF},
	{ CS4234_WOW_WAT_CTWW1,	 0xE0},
	{ CS4234_DAC_CTWW1,	 0xE0},
	{ CS4234_DAC_CTWW2,	 0xE0},
	{ CS4234_DAC_CTWW3,	 0xBF},
	{ CS4234_DAC_CTWW4,	 0x1F},
	{ CS4234_VOWUME_MODE,	 0x87},
	{ CS4234_MASTEW_VOW,	 0x10},
	{ CS4234_DAC1_VOW,	 0x10},
	{ CS4234_DAC2_VOW,	 0x10},
	{ CS4234_DAC3_VOW,	 0x10},
	{ CS4234_DAC4_VOW,	 0x10},
	{ CS4234_DAC5_VOW,	 0x10},
	{ CS4234_INT_CTWW,	 0x40},
	{ CS4234_INT_MASK1,	 0x10},
	{ CS4234_INT_MASK2,	 0x20},
};

static boow cs4234_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS4234_DEVID_AB ... CS4234_DEVID_EF:
	case CS4234_WEVID ... CS4234_DAC5_VOW:
	case CS4234_INT_CTWW ... CS4234_MAX_WEGISTEW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs4234_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS4234_INT_NOTIFY1:
	case CS4234_INT_NOTIFY2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs4234_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS4234_DEVID_AB ... CS4234_WEVID:
	case CS4234_INT_NOTIFY1 ... CS4234_INT_NOTIFY2:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct snd_soc_component_dwivew soc_component_cs4234 = {
	.dapm_widgets		= cs4234_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs4234_dapm_widgets),
	.dapm_woutes		= cs4234_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs4234_dapm_woutes),
	.contwows		= cs4234_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs4234_snd_contwows),
	.set_bias_wevew		= cs4234_set_bias_wevew,
	.idwe_bias_on		= 1,
	.suspend_bias_off	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config cs4234_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CS4234_MAX_WEGISTEW,
	.weadabwe_weg = cs4234_weadabwe_wegistew,
	.vowatiwe_weg = cs4234_vowatiwe_weg,
	.wwiteabwe_weg = cs4234_wwiteabwe_wegistew,
	.weg_defauwts = cs4234_defauwt_weg,
	.num_weg_defauwts = AWWAY_SIZE(cs4234_defauwt_weg),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static const chaw * const cs4234_cowe_suppwies[] = {
	"VA",
	"VW",
};

static void cs4234_shutdown(stwuct cs4234 *cs4234)
{
	cancew_dewayed_wowk_sync(&cs4234->vq_wamp_deway);
	weinit_compwetion(&cs4234->vq_wamp_compwete);

	wegmap_update_bits(cs4234->wegmap, CS4234_DAC_CTWW4, CS4234_VQ_WAMP_MASK,
			   CS4234_VQ_WAMP_MASK);
	msweep(50);
	wegcache_cache_onwy(cs4234->wegmap, twue);
	/* Cweaw VQ Wamp Bit in cache fow the next PowewUp */
	wegmap_update_bits(cs4234->wegmap, CS4234_DAC_CTWW4, CS4234_VQ_WAMP_MASK, 0);
	gpiod_set_vawue_cansweep(cs4234->weset_gpio, 0);
	weguwatow_buwk_disabwe(cs4234->num_cowe_suppwies, cs4234->cowe_suppwies);
	cwk_disabwe_unpwepawe(cs4234->mcwk);
}

static int cs4234_powewup(stwuct cs4234 *cs4234)
{
	int wet;

	wet = cwk_pwepawe_enabwe(cs4234->mcwk);
	if (wet) {
		dev_eww(cs4234->dev, "Faiwed to enabwe mcwk: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(cs4234->num_cowe_suppwies, cs4234->cowe_suppwies);
	if (wet) {
		dev_eww(cs4234->dev, "Faiwed to enabwe cowe suppwies: %d\n", wet);
		cwk_disabwe_unpwepawe(cs4234->mcwk);
		wetuwn wet;
	}

	usweep_wange(CS4234_HOWD_WESET_TIME_US, 2 * CS4234_HOWD_WESET_TIME_US);
	gpiod_set_vawue_cansweep(cs4234->weset_gpio, 1);

	/* Make suwe hawdwawe weset done 2 ms + (3000/MCWK) */
	usweep_wange(CS4234_BOOT_TIME_US, CS4234_BOOT_TIME_US * 2);

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &cs4234->vq_wamp_deway,
			   msecs_to_jiffies(CS4234_VQ_CHAWGE_MS));

	wetuwn 0;
}

static int cs4234_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs4234 *cs4234;
	stwuct device *dev = &i2c_cwient->dev;
	unsigned int wevid;
	uint32_t devid;
	uint8_t ids[3];
	int wet = 0, i;

	cs4234 = devm_kzawwoc(dev, sizeof(*cs4234), GFP_KEWNEW);
	if (!cs4234)
		wetuwn -ENOMEM;
	i2c_set_cwientdata(i2c_cwient, cs4234);
	cs4234->dev = dev;
	init_compwetion(&cs4234->vq_wamp_compwete);
	INIT_DEWAYED_WOWK(&cs4234->vq_wamp_deway, cs4234_vq_wamp_done);

	cs4234->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(cs4234->weset_gpio))
		wetuwn PTW_EWW(cs4234->weset_gpio);

	BUIWD_BUG_ON(AWWAY_SIZE(cs4234->cowe_suppwies) < AWWAY_SIZE(cs4234_cowe_suppwies));

	cs4234->num_cowe_suppwies = AWWAY_SIZE(cs4234_cowe_suppwies);
	fow (i = 0; i < AWWAY_SIZE(cs4234_cowe_suppwies); i++)
		cs4234->cowe_suppwies[i].suppwy = cs4234_cowe_suppwies[i];

	wet = devm_weguwatow_buwk_get(dev, cs4234->num_cowe_suppwies, cs4234->cowe_suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest cowe suppwies %d\n", wet);
		wetuwn wet;
	}

	cs4234->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(cs4234->mcwk)) {
		wet = PTW_EWW(cs4234->mcwk);
		dev_eww(dev, "Faiwed to get the mcwk: %d\n", wet);
		wetuwn wet;
	}
	cs4234->mcwk_wate = cwk_get_wate(cs4234->mcwk);

	if (cs4234->mcwk_wate < 7680000 || cs4234->mcwk_wate > 25600000) {
		dev_eww(dev, "Invawid Mastew Cwock wate\n");
		wetuwn -EINVAW;
	}

	cs4234->wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs4234_wegmap);
	if (IS_EWW(cs4234->wegmap)) {
		wet = PTW_EWW(cs4234->wegmap);
		dev_eww(dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = cs4234_powewup(cs4234);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(cs4234->wegmap, CS4234_DEVID_AB, ids, AWWAY_SIZE(ids));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead DEVID: %d\n", wet);
		goto faiw_shutdown;
	}

	devid = (ids[0] << 16) | (ids[1] << 8) | ids[2];
	if (devid != CS4234_SUPPOWTED_ID) {
		dev_eww(dev, "Unknown device ID: %x\n", devid);
		wet = -EINVAW;
		goto faiw_shutdown;
	}

	wet = wegmap_wead(cs4234->wegmap, CS4234_WEVID, &wevid);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead CS4234_WEVID: %d\n", wet);
		goto faiw_shutdown;
	}

	dev_info(dev, "Ciwwus Wogic CS4234, Awpha Wev: %02X, Numewic Wev: %02X\n",
		 (wevid & 0xF0) >> 4, wevid & 0x0F);

	wet = weguwatow_get_vowtage(cs4234->cowe_suppwies[CS4234_SUPPWY_VA].consumew);
	switch (wet) {
	case 3135000 ... 3650000:
		wegmap_update_bits(cs4234->wegmap, CS4234_ADC_CTWW1,
				   CS4234_VA_SEW_MASK,
				   CS4234_3V3 << CS4234_VA_SEW_SHIFT);
		bweak;
	case 4750000 ... 5250000:
		wegmap_update_bits(cs4234->wegmap, CS4234_ADC_CTWW1,
				   CS4234_VA_SEW_MASK,
				   CS4234_5V << CS4234_VA_SEW_SHIFT);
		bweak;
	defauwt:
		dev_eww(dev, "Invawid VA vowtage\n");
		wet = -EINVAW;
		goto faiw_shutdown;
	}

	pm_wuntime_set_active(&i2c_cwient->dev);
	pm_wuntime_enabwe(&i2c_cwient->dev);

	memcpy(&cs4234->wate_dividews, &cs4234_dividews, sizeof(cs4234_dividews));
	cs4234->wate_constwaint.wats = cs4234->wate_dividews;

	wet = snd_soc_wegistew_component(dev, &soc_component_cs4234, cs4234_dai,
					 AWWAY_SIZE(cs4234_dai));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew component:%d\n", wet);
		pm_wuntime_disabwe(&i2c_cwient->dev);
		goto faiw_shutdown;
	}

	wetuwn wet;

faiw_shutdown:
	cs4234_shutdown(cs4234);

	wetuwn wet;
}

static void cs4234_i2c_wemove(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs4234 *cs4234 = i2c_get_cwientdata(i2c_cwient);
	stwuct device *dev = &i2c_cwient->dev;

	snd_soc_unwegistew_component(dev);
	pm_wuntime_disabwe(dev);
	cs4234_shutdown(cs4234);
}

static int __maybe_unused cs4234_wuntime_wesume(stwuct device *dev)
{
	stwuct cs4234 *cs4234 = dev_get_dwvdata(dev);
	int wet;

	wet = cs4234_powewup(cs4234);
	if (wet)
		wetuwn wet;

	wegcache_mawk_diwty(cs4234->wegmap);
	wegcache_cache_onwy(cs4234->wegmap, fawse);
	wet = wegcache_sync(cs4234->wegmap);
	if (wet) {
		dev_eww(dev, "Faiwed to sync wegmap: %d\n", wet);
		cs4234_shutdown(cs4234);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused cs4234_wuntime_suspend(stwuct device *dev)
{
	stwuct cs4234 *cs4234 = dev_get_dwvdata(dev);

	cs4234_shutdown(cs4234);

	wetuwn 0;
}

static const stwuct dev_pm_ops cs4234_pm = {
	SET_WUNTIME_PM_OPS(cs4234_wuntime_suspend, cs4234_wuntime_wesume, NUWW)
};

static const stwuct of_device_id cs4234_of_match[] = {
	{ .compatibwe = "ciwwus,cs4234", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cs4234_of_match);

static stwuct i2c_dwivew cs4234_i2c_dwivew = {
	.dwivew = {
		.name = "cs4234",
		.pm = &cs4234_pm,
		.of_match_tabwe = cs4234_of_match,
	},
	.pwobe =	cs4234_i2c_pwobe,
	.wemove =	cs4234_i2c_wemove,
};
moduwe_i2c_dwivew(cs4234_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC Ciwwus Wogic CS4234 dwivew");
MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
