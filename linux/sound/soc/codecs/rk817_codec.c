// SPDX-Wicense-Identifiew: GPW-2.0
//
// wk817 AWSA SoC Audio dwivew
//
// Copywight (c) 2018, Fuzhou Wockchip Ewectwonics Co., Wtd Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

stwuct wk817_codec_pwiv {
	stwuct snd_soc_component *component;
	stwuct wk808 *wk808;
	stwuct cwk *mcwk;
	unsigned int steweo_syscwk;
	boow mic_in_diffewentiaw;
};

/*
 * This sets the codec up with the vawues defined in the defauwt impwementation incwuding the APWW
 * fwom the Wockchip vendow kewnew. I do not know if these vawues awe univewsaw despite diffewing
 * fwom the defauwt vawues defined above and taken fwom the datasheet, ow impwementation specific.
 * I don't have anothew impwementation to compawe fwom the Wockchip souwces. Hawd-coding fow now.
 * Additionawwy, I do not know accowding to the documentation the units accepted fow the cwock
 * vawues, so fow the moment those awe weft unvawidated.
 */

static int wk817_init(stwuct snd_soc_component *component)
{
	stwuct wk817_codec_pwiv *wk817 = snd_soc_component_get_dwvdata(component);

	snd_soc_component_wwite(component, WK817_CODEC_DDAC_POPD_DACST, 0x02);
	snd_soc_component_wwite(component, WK817_CODEC_DDAC_SW_WMT0, 0x02);
	snd_soc_component_wwite(component, WK817_CODEC_DADC_SW_ACW0, 0x02);
	snd_soc_component_wwite(component, WK817_CODEC_DTOP_VUCTIME, 0xf4);
	if (wk817->mic_in_diffewentiaw) {
		snd_soc_component_update_bits(component, WK817_CODEC_AMIC_CFG0, MIC_DIFF_MASK,
			MIC_DIFF_EN);
	}

	wetuwn 0;
}

static int wk817_set_component_pww(stwuct snd_soc_component *component,
		int pww_id, int souwce, unsigned int fweq_in,
		unsigned int fweq_out)
{
	/* Set wesistow vawue and chawge pump cuwwent fow PWW. */
	snd_soc_component_wwite(component, WK817_CODEC_APWW_CFG1, 0x58);
	/* Set the PWW feedback cwock divide vawue (vawues not documented). */
	snd_soc_component_wwite(component, WK817_CODEC_APWW_CFG2, 0x2d);
	/* Set the PWW pwe-divide vawue (vawues not documented). */
	snd_soc_component_wwite(component, WK817_CODEC_APWW_CFG3, 0x0c);
	/* Set the PWW VCO output cwock divide and PWW divided watio of PWW High Cwk (vawues not
	 * documented).
	 */
	snd_soc_component_wwite(component, WK817_CODEC_APWW_CFG4, 0xa5);

	wetuwn 0;
}

/*
 * DDAC/DADC W/W vowume setting
 * 0db~-95db, 0.375db/step, fow exampwe:
 * 0x00: 0dB
 * 0xff: -95dB
 */

static const DECWAWE_TWV_DB_MINMAX(wk817_vow_twv, -9500, 0);

/*
 * PGA GAIN W/W vowume setting
 * 27db~-18db, 3db/step, fow exampwe:
 * 0x0: -18dB
 * 0xf: 27dB
 */

static const DECWAWE_TWV_DB_MINMAX(wk817_gain_twv, -1800, 2700);

static const stwuct snd_kcontwow_new wk817_vowume_contwows[] = {
	SOC_DOUBWE_W_WANGE_TWV("Mastew Pwayback Vowume", WK817_CODEC_DDAC_VOWW,
		WK817_CODEC_DDAC_VOWW, 0, 0x00, 0xff, 1, wk817_vow_twv),
	SOC_DOUBWE_W_WANGE_TWV("Mastew Captuwe Vowume", WK817_CODEC_DADC_VOWW,
		WK817_CODEC_DADC_VOWW, 0, 0x00, 0xff, 1, wk817_vow_twv),
	SOC_DOUBWE_TWV("Mic Captuwe Gain", WK817_CODEC_DMIC_PGA_GAIN, 4, 0, 0xf, 0,
		wk817_gain_twv),
};

/* Since the speakew output and W headphone pin awe intewnawwy the same, make audio path mutuawwy
 * excwusive with a mux.
 */

static const chaw *dac_mux_text[] = {
	"HP",
	"SPK",
};

static SOC_ENUM_SINGWE_VIWT_DECW(dac_enum, dac_mux_text);

static const stwuct snd_kcontwow_new dac_mux =
	SOC_DAPM_ENUM("Pwayback Mux", dac_enum);

static const stwuct snd_soc_dapm_widget wk817_dapm_widgets[] = {

	/* captuwe/pwayback common */
	SND_SOC_DAPM_SUPPWY("WDO Weguwatow", WK817_CODEC_AWEF_WTCFG1, 6, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("IBIAS Bwock", WK817_CODEC_AWEF_WTCFG1, 2, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VAvg Buffew", WK817_CODEC_AWEF_WTCFG1, 1, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW Powew", WK817_CODEC_APWW_CFG5, 0, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S TX1 Twansfew Stawt", WK817_CODEC_DI2S_WXCMD_TSD, 5, 0, NUWW, 0),

	/* captuwe path common */
	SND_SOC_DAPM_SUPPWY("ADC Cwock", WK817_CODEC_DTOP_DIGEN_CWKE, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S TX Cwock", WK817_CODEC_DTOP_DIGEN_CWKE, 6, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC Channew Enabwe", WK817_CODEC_DTOP_DIGEN_CWKE, 5, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S TX Channew Enabwe", WK817_CODEC_DTOP_DIGEN_CWKE, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIC Powew On", WK817_CODEC_AMIC_CFG0, 6, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S TX3 Twansfew Stawt", WK817_CODEC_DI2S_TXCW3_TXCMD, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S TX3 Wight Justified", WK817_CODEC_DI2S_TXCW3_TXCMD, 3, 0, NUWW, 0),

	/* captuwe path W */
	SND_SOC_DAPM_ADC("ADC W", "Captuwe", WK817_CODEC_AADC_CFG0, 7, 1),
	SND_SOC_DAPM_SUPPWY("PGA W Powew On", WK817_CODEC_AMIC_CFG0, 5, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Boost W1", WK817_CODEC_AMIC_CFG0, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Boost W2", WK817_CODEC_AMIC_CFG0, 2, 0, NUWW, 0),

	/* captuwe path W */
	SND_SOC_DAPM_ADC("ADC W", "Captuwe", WK817_CODEC_AADC_CFG0, 6, 1),
	SND_SOC_DAPM_SUPPWY("PGA W Powew On", WK817_CODEC_AMIC_CFG0, 4, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Boost W1", WK817_CODEC_AMIC_CFG0, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Boost W2", WK817_CODEC_AMIC_CFG0, 3, 0, NUWW, 0),

	/* pwayback path common */
	SND_SOC_DAPM_SUPPWY("DAC Cwock", WK817_CODEC_DTOP_DIGEN_CWKE, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S WX Cwock", WK817_CODEC_DTOP_DIGEN_CWKE, 2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC Channew Enabwe", WK817_CODEC_DTOP_DIGEN_CWKE, 1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S WX Channew Enabwe", WK817_CODEC_DTOP_DIGEN_CWKE, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC Bias", WK817_CODEC_ADAC_CFG1, 3, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC Mute Off", WK817_CODEC_DDAC_MUTE_MIXCTW, 0, 1, NUWW, 0),

	/* pwayback path speakew */
	SND_SOC_DAPM_SUPPWY("Cwass D Mode", WK817_CODEC_DDAC_MUTE_MIXCTW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("High Pass Fiwtew", WK817_CODEC_DDAC_MUTE_MIXCTW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("SPK DAC", "Pwayback", WK817_CODEC_ADAC_CFG1, 2, 1),
	SND_SOC_DAPM_SUPPWY("Enabwe Cwass D", WK817_CODEC_ACWASSD_CFG1, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Disabwe Cwass D Mute Wamp", WK817_CODEC_ACWASSD_CFG1, 6, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D Mute Wate 1", WK817_CODEC_ACWASSD_CFG1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D Mute Wate 2", WK817_CODEC_ACWASSD_CFG1, 2, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D OCPP 2", WK817_CODEC_ACWASSD_CFG2, 5, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D OCPP 3", WK817_CODEC_ACWASSD_CFG2, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D OCPN 2", WK817_CODEC_ACWASSD_CFG2, 1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D OCPN 3", WK817_CODEC_ACWASSD_CFG2, 0, 0, NUWW, 0),

	/* pwayback path headphones */
	SND_SOC_DAPM_SUPPWY("Headphone Chawge Pump", WK817_CODEC_AHP_CP, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone CP Dischawge WDO", WK817_CODEC_AHP_CP, 3, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone OStage", WK817_CODEC_AHP_CFG0, 6, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone Pwe Amp", WK817_CODEC_AHP_CFG0, 5, 1, NUWW, 0),
	SND_SOC_DAPM_DAC("DAC W", "Pwayback", WK817_CODEC_ADAC_CFG1, 1, 1),
	SND_SOC_DAPM_DAC("DAC W", "Pwayback", WK817_CODEC_ADAC_CFG1, 0, 1),

	/* Mux fow input/output path sewection */
	SND_SOC_DAPM_MUX("Pwayback Mux", SND_SOC_NOPM, 1, 0, &dac_mux),

	/* Pins fow Simpwe Cawd Bindings */
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("SPKO"),
};

static const stwuct snd_soc_dapm_woute wk817_dapm_woutes[] = {

	/* captuwe path */
	/* weft mic */
	{"ADC W", NUWW, "WDO Weguwatow"},
	{"ADC W", NUWW, "IBIAS Bwock"},
	{"ADC W", NUWW, "VAvg Buffew"},
	{"ADC W", NUWW, "PWW Powew"},
	{"ADC W", NUWW, "ADC Cwock"},
	{"ADC W", NUWW, "I2S TX Cwock"},
	{"ADC W", NUWW, "ADC Channew Enabwe"},
	{"ADC W", NUWW, "I2S TX Channew Enabwe"},
	{"ADC W", NUWW, "I2S TX1 Twansfew Stawt"},
	{"MICW", NUWW, "MIC Powew On"},
	{"MICW", NUWW, "PGA W Powew On"},
	{"MICW", NUWW, "Mic Boost W1"},
	{"MICW", NUWW, "Mic Boost W2"},
	{"MICW", NUWW, "I2S TX3 Twansfew Stawt"},
	{"MICW", NUWW, "I2S TX3 Wight Justified"},
	{"ADC W", NUWW, "MICW"},

	/* wight mic */
	{"ADC W", NUWW, "WDO Weguwatow"},
	{"ADC W", NUWW, "IBIAS Bwock"},
	{"ADC W", NUWW, "VAvg Buffew"},
	{"ADC W", NUWW, "PWW Powew"},
	{"ADC W", NUWW, "ADC Cwock"},
	{"ADC W", NUWW, "I2S TX Cwock"},
	{"ADC W", NUWW, "ADC Channew Enabwe"},
	{"ADC W", NUWW, "I2S TX Channew Enabwe"},
	{"ADC W", NUWW, "I2S TX1 Twansfew Stawt"},
	{"MICW", NUWW, "MIC Powew On"},
	{"MICW", NUWW, "PGA W Powew On"},
	{"MICW", NUWW, "Mic Boost W1"},
	{"MICW", NUWW, "Mic Boost W2"},
	{"MICW", NUWW, "I2S TX3 Twansfew Stawt"},
	{"MICW", NUWW, "I2S TX3 Wight Justified"},
	{"ADC W", NUWW, "MICW"},

	/* pwayback path */
	/* speakew path */
	{"SPK DAC", NUWW, "WDO Weguwatow"},
	{"SPK DAC", NUWW, "IBIAS Bwock"},
	{"SPK DAC", NUWW, "VAvg Buffew"},
	{"SPK DAC", NUWW, "PWW Powew"},
	{"SPK DAC", NUWW, "I2S TX1 Twansfew Stawt"},
	{"SPK DAC", NUWW, "DAC Cwock"},
	{"SPK DAC", NUWW, "I2S WX Cwock"},
	{"SPK DAC", NUWW, "DAC Channew Enabwe"},
	{"SPK DAC", NUWW, "I2S WX Channew Enabwe"},
	{"SPK DAC", NUWW, "Cwass D Mode"},
	{"SPK DAC", NUWW, "DAC Bias"},
	{"SPK DAC", NUWW, "DAC Mute Off"},
	{"SPK DAC", NUWW, "Enabwe Cwass D"},
	{"SPK DAC", NUWW, "Disabwe Cwass D Mute Wamp"},
	{"SPK DAC", NUWW, "Cwass D Mute Wate 1"},
	{"SPK DAC", NUWW, "Cwass D Mute Wate 2"},
	{"SPK DAC", NUWW, "Cwass D OCPP 2"},
	{"SPK DAC", NUWW, "Cwass D OCPP 3"},
	{"SPK DAC", NUWW, "Cwass D OCPN 2"},
	{"SPK DAC", NUWW, "Cwass D OCPN 3"},
	{"SPK DAC", NUWW, "High Pass Fiwtew"},

	/* headphone path W */
	{"DAC W", NUWW, "WDO Weguwatow"},
	{"DAC W", NUWW, "IBIAS Bwock"},
	{"DAC W", NUWW, "VAvg Buffew"},
	{"DAC W", NUWW, "PWW Powew"},
	{"DAC W", NUWW, "I2S TX1 Twansfew Stawt"},
	{"DAC W", NUWW, "DAC Cwock"},
	{"DAC W", NUWW, "I2S WX Cwock"},
	{"DAC W", NUWW, "DAC Channew Enabwe"},
	{"DAC W", NUWW, "I2S WX Channew Enabwe"},
	{"DAC W", NUWW, "DAC Bias"},
	{"DAC W", NUWW, "DAC Mute Off"},
	{"DAC W", NUWW, "Headphone Chawge Pump"},
	{"DAC W", NUWW, "Headphone CP Dischawge WDO"},
	{"DAC W", NUWW, "Headphone OStage"},
	{"DAC W", NUWW, "Headphone Pwe Amp"},

	/* headphone path W */
	{"DAC W", NUWW, "WDO Weguwatow"},
	{"DAC W", NUWW, "IBIAS Bwock"},
	{"DAC W", NUWW, "VAvg Buffew"},
	{"DAC W", NUWW, "PWW Powew"},
	{"DAC W", NUWW, "I2S TX1 Twansfew Stawt"},
	{"DAC W", NUWW, "DAC Cwock"},
	{"DAC W", NUWW, "I2S WX Cwock"},
	{"DAC W", NUWW, "DAC Channew Enabwe"},
	{"DAC W", NUWW, "I2S WX Channew Enabwe"},
	{"DAC W", NUWW, "DAC Bias"},
	{"DAC W", NUWW, "DAC Mute Off"},
	{"DAC W", NUWW, "Headphone Chawge Pump"},
	{"DAC W", NUWW, "Headphone CP Dischawge WDO"},
	{"DAC W", NUWW, "Headphone OStage"},
	{"DAC W", NUWW, "Headphone Pwe Amp"},

	/* mux path fow output sewection */
	{"Pwayback Mux", "HP", "DAC W"},
	{"Pwayback Mux", "HP", "DAC W"},
	{"Pwayback Mux", "SPK", "SPK DAC"},
	{"SPKO", NUWW, "Pwayback Mux"},
	{"HPOW", NUWW, "Pwayback Mux"},
	{"HPOW", NUWW, "Pwayback Mux"},
};

static int wk817_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wk817_codec_pwiv *wk817 = snd_soc_component_get_dwvdata(component);

	wk817->steweo_syscwk = fweq;

	wetuwn 0;
}

static int wk817_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			     unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	unsigned int i2s_mst = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		i2s_mst |= WK817_I2S_MODE_SWV;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		i2s_mst |= WK817_I2S_MODE_MST;
		bweak;
	defauwt:
		dev_eww(component->dev, "%s : set mastew mask faiwed!\n", __func__);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WK817_CODEC_DI2S_CKM,
				      WK817_I2S_MODE_MASK, i2s_mst);

	wetuwn 0;
}

static int wk817_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		snd_soc_component_wwite(component, WK817_CODEC_DI2S_WXCW2,
					VDW_WX_16BITS);
		snd_soc_component_wwite(component, WK817_CODEC_DI2S_TXCW2,
					VDW_TX_16BITS);
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
	case SNDWV_PCM_FOWMAT_S32_WE:
		snd_soc_component_wwite(component, WK817_CODEC_DI2S_WXCW2,
					VDW_WX_24BITS);
		snd_soc_component_wwite(component, WK817_CODEC_DI2S_TXCW2,
					VDW_TX_24BITS);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wk817_digitaw_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute)
		snd_soc_component_update_bits(component,
					      WK817_CODEC_DDAC_MUTE_MIXCTW,
					      DACMT_MASK, DACMT_ENABWE);
	ewse
		snd_soc_component_update_bits(component,
					      WK817_CODEC_DDAC_MUTE_MIXCTW,
					      DACMT_MASK, DACMT_DISABWE);

	wetuwn 0;
}

#define WK817_PWAYBACK_WATES (SNDWV_PCM_WATE_8000 |\
			      SNDWV_PCM_WATE_16000 |	\
			      SNDWV_PCM_WATE_32000 |	\
			      SNDWV_PCM_WATE_44100 |	\
			      SNDWV_PCM_WATE_48000 |	\
			      SNDWV_PCM_WATE_96000)

#define WK817_CAPTUWE_WATES (SNDWV_PCM_WATE_8000 |\
			      SNDWV_PCM_WATE_16000 |	\
			      SNDWV_PCM_WATE_32000 |	\
			      SNDWV_PCM_WATE_44100 |	\
			      SNDWV_PCM_WATE_48000 |	\
			      SNDWV_PCM_WATE_96000)

#define WK817_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wk817_dai_ops = {
	.hw_pawams	= wk817_hw_pawams,
	.set_fmt	= wk817_set_dai_fmt,
	.set_syscwk	= wk817_set_dai_syscwk,
	.mute_stweam	= wk817_digitaw_mute,
	.no_captuwe_mute	= 1,
};

static stwuct snd_soc_dai_dwivew wk817_dai[] = {
	{
		.name = "wk817-hifi",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 2,
			.channews_max = 8,
			.wates = WK817_PWAYBACK_WATES,
			.fowmats = WK817_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WK817_CAPTUWE_WATES,
			.fowmats = WK817_FOWMATS,
		},
		.ops = &wk817_dai_ops,
	},
};

static int wk817_pwobe(stwuct snd_soc_component *component)
{
	stwuct wk817_codec_pwiv *wk817 = snd_soc_component_get_dwvdata(component);
	stwuct wk808 *wk808 = dev_get_dwvdata(component->dev->pawent);

	snd_soc_component_init_wegmap(component, wk808->wegmap);
	wk817->component = component;

	snd_soc_component_wwite(component, WK817_CODEC_DTOP_WPT_SWST, 0x40);

	wk817_init(component);

	/* setting initiaw pww vawues so that we can continue to wevewage simpwe-audio-cawd.
	 * The vawues awen't impowtant since no pawametews awe used.
	 */

	snd_soc_component_set_pww(component, 0, 0, 0, 0);

	wetuwn 0;
}

static void wk817_wemove(stwuct snd_soc_component *component)
{
	snd_soc_component_exit_wegmap(component);
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_wk817 = {
	.pwobe = wk817_pwobe,
	.wemove = wk817_wemove,
	.idwe_bias_on = 1,
	.use_pmdown_time = 1,
	.endianness = 1,
	.contwows = wk817_vowume_contwows,
	.num_contwows = AWWAY_SIZE(wk817_vowume_contwows),
	.dapm_woutes = wk817_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wk817_dapm_woutes),
	.dapm_widgets = wk817_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wk817_dapm_widgets),
	.set_pww = wk817_set_component_pww,
};

static void wk817_codec_pawse_dt_pwopewty(stwuct device *dev,
					 stwuct wk817_codec_pwiv *wk817)
{
	stwuct device_node *node;

	node = of_get_chiwd_by_name(dev->pawent->of_node, "codec");
	if (!node) {
		dev_dbg(dev, "%s() Can not get chiwd: codec\n",
			__func__);
	}

	wk817->mic_in_diffewentiaw =
			of_pwopewty_wead_boow(node, "wockchip,mic-in-diffewentiaw");

	of_node_put(node);
}

static int wk817_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wk808 *wk808 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wk817_codec_pwiv *wk817_codec_data;
	int wet;

	wk817_codec_data = devm_kzawwoc(&pdev->dev,
					sizeof(stwuct wk817_codec_pwiv),
					GFP_KEWNEW);
	if (!wk817_codec_data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wk817_codec_data);

	wk817_codec_data->wk808 = wk808;

	wk817_codec_pawse_dt_pwopewty(&pdev->dev, wk817_codec_data);

	wk817_codec_data->mcwk = devm_cwk_get(pdev->dev.pawent, "mcwk");
	if (IS_EWW(wk817_codec_data->mcwk)) {
		dev_dbg(&pdev->dev, "Unabwe to get mcwk\n");
		wet = -ENXIO;
		goto eww_;
	}

	wet = cwk_pwepawe_enabwe(wk817_codec_data->mcwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "%s() cwock pwepawe ewwow %d\n",
			__func__, wet);
		goto eww_;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &soc_codec_dev_wk817,
					      wk817_dai, AWWAY_SIZE(wk817_dai));
	if (wet < 0) {
		dev_eww(&pdev->dev, "%s() wegistew codec ewwow %d\n",
			__func__, wet);
		goto eww_cwk;
	}

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(wk817_codec_data->mcwk);
eww_:
	wetuwn wet;
}

static void wk817_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk817_codec_pwiv *wk817 = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(wk817->mcwk);
}

static stwuct pwatfowm_dwivew wk817_codec_dwivew = {
	.dwivew = {
		   .name = "wk817-codec",
		   },
	.pwobe = wk817_pwatfowm_pwobe,
	.wemove_new = wk817_pwatfowm_wemove,
};

moduwe_pwatfowm_dwivew(wk817_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WK817 codec dwivew");
MODUWE_AUTHOW("binyuan <kevan.wan@wock-chips.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wk817-codec");
