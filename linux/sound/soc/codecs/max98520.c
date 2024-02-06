// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2021, Maxim Integwated

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/cdev.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <sound/twv.h>
#incwude "max98520.h"

static stwuct weg_defauwt max98520_weg[] = {
	{MAX98520_W2000_SW_WESET, 0x00},
	{MAX98520_W2001_STATUS_1, 0x00},
	{MAX98520_W2002_STATUS_2, 0x00},
	{MAX98520_W2020_THEWM_WAWN_THWESH, 0x46},
	{MAX98520_W2021_THEWM_SHDN_THWESH, 0x64},
	{MAX98520_W2022_THEWM_HYSTEWESIS, 0x02},
	{MAX98520_W2023_THEWM_FOWDBACK_SET, 0x31},
	{MAX98520_W2027_THEWM_FOWDBACK_EN, 0x01},
	{MAX98520_W2030_CWK_MON_CTWW, 0x00},
	{MAX98520_W2037_EWW_MON_CTWW, 0x01},
	{MAX98520_W2040_PCM_MODE_CFG, 0xC0},
	{MAX98520_W2041_PCM_CWK_SETUP, 0x04},
	{MAX98520_W2042_PCM_SW_SETUP, 0x08},
	{MAX98520_W2043_PCM_WX_SWC1, 0x00},
	{MAX98520_W2044_PCM_WX_SWC2, 0x00},
	{MAX98520_W204F_PCM_WX_EN, 0x00},
	{MAX98520_W2090_AMP_VOW_CTWW, 0x00},
	{MAX98520_W2091_AMP_PATH_GAIN, 0x03},
	{MAX98520_W2092_AMP_DSP_CFG, 0x02},
	{MAX98520_W2094_SSM_CFG, 0x01},
	{MAX98520_W2095_AMP_CFG, 0xF0},
	{MAX98520_W209F_AMP_EN, 0x00},
	{MAX98520_W20B0_ADC_SW, 0x00},
	{MAX98520_W20B1_ADC_WESOWUTION, 0x00},
	{MAX98520_W20B2_ADC_PVDD0_CFG, 0x02},
	{MAX98520_W20B3_ADC_THEWMAW_CFG, 0x02},
	{MAX98520_W20B4_ADC_WEADBACK_CTWW, 0x00},
	{MAX98520_W20B5_ADC_WEADBACK_UPDATE, 0x00},
	{MAX98520_W20B6_ADC_PVDD_WEADBACK_MSB, 0x00},
	{MAX98520_W20B7_ADC_PVDD_WEADBACK_WSB, 0x00},
	{MAX98520_W20B8_ADC_TEMP_WEADBACK_MSB, 0x00},
	{MAX98520_W20B9_ADC_TEMP_WEADBACK_WSB, 0x00},
	{MAX98520_W20BA_ADC_WOW_PVDD_WEADBACK_MSB, 0xFF},
	{MAX98520_W20BB_ADC_WOW_WEADBACK_WSB, 0x01},
	{MAX98520_W20BC_ADC_HIGH_TEMP_WEADBACK_MSB, 0x00},
	{MAX98520_W20BD_ADC_HIGH_TEMP_WEADBACK_WSB, 0x00},
	{MAX98520_W20CF_MEAS_ADC_CFG, 0x00},
	{MAX98520_W20D0_DHT_CFG1, 0x00},
	{MAX98520_W20D1_WIMITEW_CFG1, 0x08},
	{MAX98520_W20D2_WIMITEW_CFG2, 0x00},
	{MAX98520_W20D3_DHT_CFG2, 0x14},
	{MAX98520_W20D4_DHT_CFG3, 0x02},
	{MAX98520_W20D5_DHT_CFG4, 0x04},
	{MAX98520_W20D6_DHT_HYSTEWESIS_CFG, 0x07},
	{MAX98520_W20D8_DHT_EN, 0x00},
	{MAX98520_W210E_AUTO_WESTAWT_BEHAVIOW, 0x00},
	{MAX98520_W210F_GWOBAW_EN, 0x00},
	{MAX98520_W21FF_WEVISION_ID, 0x00},
};

static int max98520_dai_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);
	unsigned int fowmat = 0;
	unsigned int invewt = 0;

	dev_dbg(component->dev, "%s: fmt 0x%08X\n", __func__, fmt);

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		invewt = MAX98520_PCM_MODE_CFG_PCM_BCWKEDGE;
		bweak;
	defauwt:
		dev_eww(component->dev, "DAI invewt mode unsuppowted\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2041_PCM_CWK_SETUP,
			   MAX98520_PCM_MODE_CFG_PCM_BCWKEDGE,
			   invewt);

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat = MAX98520_PCM_FOWMAT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat = MAX98520_PCM_FOWMAT_WJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		fowmat = MAX98520_PCM_FOWMAT_TDM_MODE1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		fowmat = MAX98520_PCM_FOWMAT_TDM_MODE0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2040_PCM_MODE_CFG,
			   MAX98520_PCM_MODE_CFG_FOWMAT_MASK,
			   fowmat << MAX98520_PCM_MODE_CFG_FOWMAT_SHIFT);

	wetuwn 0;
}

/* BCWKs pew WWCWK */
static const int bcwk_sew_tabwe[] = {
	32, 48, 64, 96, 128, 192, 256, 384, 512, 320,
};

static int max98520_get_bcwk_sew(int bcwk)
{
	int i;
	/* match BCWKs pew WWCWK */
	fow (i = 0; i < AWWAY_SIZE(bcwk_sew_tabwe); i++) {
		if (bcwk_sew_tabwe[i] == bcwk)
			wetuwn i + 2;
	}
	wetuwn 0;
}

static int max98520_set_cwock(stwuct snd_soc_component *component,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);
	/* BCWK/WWCWK watio cawcuwation */
	int bww_cwk_watio = pawams_channews(pawams) * max98520->ch_size;
	int vawue;

	if (!max98520->tdm_mode) {
		/* BCWK configuwation */
		vawue = max98520_get_bcwk_sew(bww_cwk_watio);
		if (!vawue) {
			dev_eww(component->dev, "fowmat unsuppowted %d\n",
				pawams_fowmat(pawams));
			wetuwn -EINVAW;
		}

		wegmap_update_bits(max98520->wegmap,
				   MAX98520_W2041_PCM_CWK_SETUP,
				   MAX98520_PCM_CWK_SETUP_BSEW_MASK,
				   vawue);
	}
	dev_dbg(component->dev, "%s tdm_mode:%d out\n", __func__, max98520->tdm_mode);
	wetuwn 0;
}

static int max98520_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);
	unsigned int sampwing_wate = 0;
	unsigned int chan_sz = 0;

	/* pcm mode configuwation */
	switch (snd_pcm_fowmat_width(pawams_fowmat(pawams))) {
	case 16:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_16;
		bweak;
	case 24:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_24;
		bweak;
	case 32:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_32;
		bweak;
	defauwt:
		dev_eww(component->dev, "fowmat unsuppowted %d\n",
			pawams_fowmat(pawams));
		goto eww;
	}

	max98520->ch_size = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2040_PCM_MODE_CFG,
			   MAX98520_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "fowmat suppowted %d",
		pawams_fowmat(pawams));

	/* sampwing wate configuwation */
	switch (pawams_wate(pawams)) {
	case 8000:
		sampwing_wate = MAX98520_PCM_SW_8000;
		bweak;
	case 11025:
		sampwing_wate = MAX98520_PCM_SW_11025;
		bweak;
	case 12000:
		sampwing_wate = MAX98520_PCM_SW_12000;
		bweak;
	case 16000:
		sampwing_wate = MAX98520_PCM_SW_16000;
		bweak;
	case 22050:
		sampwing_wate = MAX98520_PCM_SW_22050;
		bweak;
	case 24000:
		sampwing_wate = MAX98520_PCM_SW_24000;
		bweak;
	case 32000:
		sampwing_wate = MAX98520_PCM_SW_32000;
		bweak;
	case 44100:
		sampwing_wate = MAX98520_PCM_SW_44100;
		bweak;
	case 48000:
		sampwing_wate = MAX98520_PCM_SW_48000;
		bweak;
	case 88200:
		sampwing_wate = MAX98520_PCM_SW_88200;
		bweak;
	case 96000:
		sampwing_wate = MAX98520_PCM_SW_96000;
		bweak;
	case 176400:
		sampwing_wate = MAX98520_PCM_SW_176400;
		bweak;
	case 192000:
		sampwing_wate = MAX98520_PCM_SW_192000;
		bweak;
	defauwt:
		dev_eww(component->dev, "wate %d not suppowted\n",
			pawams_wate(pawams));
		goto eww;
	}

	dev_dbg(component->dev, " %s ch_size: %d, sampwing wate : %d out\n", __func__,
		snd_pcm_fowmat_width(pawams_fowmat(pawams)), pawams_wate(pawams));
	/* set DAI_SW to cowwect WWCWK fwequency */
	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2042_PCM_SW_SETUP,
			   MAX98520_PCM_SW_MASK,
			   sampwing_wate);

	wetuwn max98520_set_cwock(component, pawams);
eww:
	dev_dbg(component->dev, "%s out ewwow", __func__);
	wetuwn -EINVAW;
}

static int max98520_dai_tdm_swot(stwuct snd_soc_dai *dai,
				 unsigned int tx_mask, unsigned int wx_mask,
				 int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);
	int bsew;
	unsigned int chan_sz = 0;

	if (!tx_mask && !wx_mask && !swots && !swot_width)
		max98520->tdm_mode = fawse;
	ewse
		max98520->tdm_mode = twue;

	/* BCWK configuwation */
	bsew = max98520_get_bcwk_sew(swots * swot_width);
	if (bsew == 0) {
		dev_eww(component->dev, "BCWK %d not suppowted\n",
			swots * swot_width);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2041_PCM_CWK_SETUP,
			   MAX98520_PCM_CWK_SETUP_BSEW_MASK,
			   bsew);

	/* Channew size configuwation */
	switch (swot_width) {
	case 16:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_16;
		bweak;
	case 24:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_24;
		bweak;
	case 32:
		chan_sz = MAX98520_PCM_MODE_CFG_CHANSZ_32;
		bweak;
	defauwt:
		dev_eww(component->dev, "fowmat unsuppowted %d\n",
			swot_width);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2040_PCM_MODE_CFG,
			   MAX98520_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	/* Wx swot configuwation */
	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2044_PCM_WX_SWC2,
			   MAX98520_PCM_DMIX_CH0_SWC_MASK,
			   wx_mask);
	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W2044_PCM_WX_SWC2,
			   MAX98520_PCM_DMIX_CH1_SWC_MASK,
			   wx_mask << MAX98520_PCM_DMIX_CH1_SHIFT);

	wetuwn 0;
}

#define MAX98520_WATES SNDWV_PCM_WATE_8000_192000

#define MAX98520_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | \
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops max98520_dai_ops = {
	.set_fmt = max98520_dai_set_fmt,
	.hw_pawams = max98520_dai_hw_pawams,
	.set_tdm_swot = max98520_dai_tdm_swot,
};

static int max98520_dac_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		dev_dbg(component->dev, " AMP ON\n");

		wegmap_wwite(max98520->wegmap, MAX98520_W209F_AMP_EN, 1);
		wegmap_wwite(max98520->wegmap, MAX98520_W210F_GWOBAW_EN, 1);
		usweep_wange(30000, 31000);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		dev_dbg(component->dev, " AMP OFF\n");

		wegmap_wwite(max98520->wegmap, MAX98520_W210F_GWOBAW_EN, 0);
		wegmap_wwite(max98520->wegmap, MAX98520_W209F_AMP_EN, 0);
		usweep_wange(30000, 31000);
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 0;
}

static const chaw * const max98520_switch_text[] = {
	"Weft", "Wight", "WeftWight"};

static const stwuct soc_enum dai_sew_enum =
	SOC_ENUM_SINGWE(MAX98520_W2043_PCM_WX_SWC1,
			0, 3, max98520_switch_text);

static const stwuct snd_kcontwow_new max98520_dai_contwows =
	SOC_DAPM_ENUM("DAI Sew", dai_sew_enum);

static const stwuct snd_kcontwow_new max98520_weft_input_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PCM_INPUT_CH0", MAX98520_W2044_PCM_WX_SWC2, 0, 0x0, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH1", MAX98520_W2044_PCM_WX_SWC2, 0, 0x1, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH2", MAX98520_W2044_PCM_WX_SWC2, 0, 0x2, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH3", MAX98520_W2044_PCM_WX_SWC2, 0, 0x3, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH4", MAX98520_W2044_PCM_WX_SWC2, 0, 0x4, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH5", MAX98520_W2044_PCM_WX_SWC2, 0, 0x5, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH6", MAX98520_W2044_PCM_WX_SWC2, 0, 0x6, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH7", MAX98520_W2044_PCM_WX_SWC2, 0, 0x7, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH8", MAX98520_W2044_PCM_WX_SWC2, 0, 0x8, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH9", MAX98520_W2044_PCM_WX_SWC2, 0, 0x9, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH10", MAX98520_W2044_PCM_WX_SWC2, 0, 0xa, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH11", MAX98520_W2044_PCM_WX_SWC2, 0, 0xb, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH12", MAX98520_W2044_PCM_WX_SWC2, 0, 0xc, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH13", MAX98520_W2044_PCM_WX_SWC2, 0, 0xd, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH14", MAX98520_W2044_PCM_WX_SWC2, 0, 0xe, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH15", MAX98520_W2044_PCM_WX_SWC2, 0, 0xf, 0),
};

static const stwuct snd_kcontwow_new max98520_wight_input_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PCM_INPUT_CH0", MAX98520_W2044_PCM_WX_SWC2, 4, 0x0, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH1", MAX98520_W2044_PCM_WX_SWC2, 4, 0x1, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH2", MAX98520_W2044_PCM_WX_SWC2, 4, 0x2, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH3", MAX98520_W2044_PCM_WX_SWC2, 4, 0x3, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH4", MAX98520_W2044_PCM_WX_SWC2, 4, 0x4, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH5", MAX98520_W2044_PCM_WX_SWC2, 4, 0x5, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH6", MAX98520_W2044_PCM_WX_SWC2, 4, 0x6, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH7", MAX98520_W2044_PCM_WX_SWC2, 4, 0x7, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH8", MAX98520_W2044_PCM_WX_SWC2, 4, 0x8, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH9", MAX98520_W2044_PCM_WX_SWC2, 4, 0x9, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH10", MAX98520_W2044_PCM_WX_SWC2, 4, 0xa, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH11", MAX98520_W2044_PCM_WX_SWC2, 4, 0xb, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH12", MAX98520_W2044_PCM_WX_SWC2, 4, 0xc, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH13", MAX98520_W2044_PCM_WX_SWC2, 4, 0xd, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH14", MAX98520_W2044_PCM_WX_SWC2, 4, 0xe, 0),
	SOC_DAPM_SINGWE("PCM_INPUT_CH15", MAX98520_W2044_PCM_WX_SWC2, 4, 0xf, 0),
};

static const stwuct snd_soc_dapm_widget max98520_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("Amp Enabwe", "HiFi Pwayback",
			   SND_SOC_NOPM, 0, 0, max98520_dac_event,
	SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("DAI Sew Mux", SND_SOC_NOPM, 0, 0,	&max98520_dai_contwows),
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
	/* Weft Input Sewection */
	SND_SOC_DAPM_MIXEW("Weft Input Sewection", SND_SOC_NOPM, 0, 0,
			   &max98520_weft_input_mixew_contwows[0],
			   AWWAY_SIZE(max98520_weft_input_mixew_contwows)),
	/* Wight Input Sewection */
	SND_SOC_DAPM_MIXEW("Wight Input Sewection", SND_SOC_NOPM, 0, 0,
			   &max98520_wight_input_mixew_contwows[0],
			   AWWAY_SIZE(max98520_wight_input_mixew_contwows)),
};

static const DECWAWE_TWV_DB_SCAWE(max98520_digitaw_twv, -6300, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(max98520_spk_twv, -600, 300, 0);

static const DECWAWE_TWV_DB_WANGE(max98520_dht_wim_thwesh_twv,
	0, 15, TWV_DB_SCAWE_ITEM(-1500, 100, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98520_dht_hystewesis_twv,
	0, 3, TWV_DB_SCAWE_ITEM(100, 100, 0),
	4, 7, TWV_DB_SCAWE_ITEM(600, 200, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98520_dht_wotation_point_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-1500, 300, 0),
	2, 4, TWV_DB_SCAWE_ITEM(-1000, 200, 0),
	5, 10, TWV_DB_SCAWE_ITEM(-500, 100, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98520_dht_suppwy_hw_twv,
	0, 16, TWV_DB_SCAWE_ITEM(-2000, 250, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98520_dht_max_atten_twv,
	1, 20, TWV_DB_SCAWE_ITEM(-2000, 100, 0),
);

static const chaw * const max98520_dht_attack_wate_text[] = {
	"20us", "40us", "80us", "160us", "320us", "640us",
	"1.28ms", "2.56ms",	"5.12ms", "10.24ms", "20.48ms", "40.96ms",
	"81.92ms", "163.84ms"
};

static SOC_ENUM_SINGWE_DECW(max98520_dht_attack_wate_enum,
			    MAX98520_W20D4_DHT_CFG3, 0,
			    max98520_dht_attack_wate_text);

static const chaw * const max98520_dht_wewease_wate_text[] = {
	"2ms", "4ms", "8ms", "16ms", "32ms", "64ms", "128ms", "256ms", "512ms",
	"1.024s", "2.048s", "4.096s", "8.192s", "16.384s"
};

static SOC_ENUM_SINGWE_DECW(max98520_dht_wewease_wate_enum,
			    MAX98520_W20D5_DHT_CFG4, 0,
			    max98520_dht_wewease_wate_text);

static boow max98520_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98520_W2000_SW_WESET:
	case MAX98520_W2027_THEWM_FOWDBACK_EN:
	case MAX98520_W2030_CWK_MON_CTWW:
	case MAX98520_W2037_EWW_MON_CTWW:
	case MAX98520_W204F_PCM_WX_EN:
	case MAX98520_W209F_AMP_EN:
	case MAX98520_W20CF_MEAS_ADC_CFG:
	case MAX98520_W20D8_DHT_EN:
	case MAX98520_W21FF_WEVISION_ID:
	case MAX98520_W2001_STATUS_1... MAX98520_W2002_STATUS_2:
	case MAX98520_W2020_THEWM_WAWN_THWESH... MAX98520_W2023_THEWM_FOWDBACK_SET:
	case MAX98520_W2040_PCM_MODE_CFG... MAX98520_W2044_PCM_WX_SWC2:
	case MAX98520_W2090_AMP_VOW_CTWW... MAX98520_W2092_AMP_DSP_CFG:
	case MAX98520_W2094_SSM_CFG... MAX98520_W2095_AMP_CFG:
	case MAX98520_W20B0_ADC_SW... MAX98520_W20BD_ADC_HIGH_TEMP_WEADBACK_WSB:
	case MAX98520_W20D0_DHT_CFG1... MAX98520_W20D6_DHT_HYSTEWESIS_CFG:
	case MAX98520_W210E_AUTO_WESTAWT_BEHAVIOW... MAX98520_W210F_GWOBAW_EN:
	case MAX98520_W2161_BOOST_TM1... MAX98520_W2163_BOOST_TM3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
};

static boow max98520_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98520_W210F_GWOBAW_EN:
	case MAX98520_W21FF_WEVISION_ID:
	case MAX98520_W2000_SW_WESET:
	case MAX98520_W2001_STATUS_1 ... MAX98520_W2002_STATUS_2:
	case MAX98520_W20B4_ADC_WEADBACK_CTWW
		... MAX98520_W20BD_ADC_HIGH_TEMP_WEADBACK_WSB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct snd_kcontwow_new max98520_snd_contwows[] = {
/* Vowume */
SOC_SINGWE_TWV("Digitaw Vowume", MAX98520_W2090_AMP_VOW_CTWW,
	       0, 0x7F, 1, max98520_digitaw_twv),
SOC_SINGWE_TWV("Speakew Vowume", MAX98520_W2091_AMP_PATH_GAIN,
	       0, 0x5, 0, max98520_spk_twv),
/* Vowume Wamp Up/Down Enabwe*/
SOC_SINGWE("Wamp Up Switch", MAX98520_W2092_AMP_DSP_CFG,
	   MAX98520_DSP_SPK_VOW_WMPUP_SHIFT, 1, 0),
SOC_SINGWE("Wamp Down Switch", MAX98520_W2092_AMP_DSP_CFG,
	   MAX98520_DSP_SPK_VOW_WMPDN_SHIFT, 1, 0),
/* Cwock Monitow Enabwe */
SOC_SINGWE("CWK Monitow Switch", MAX98520_W2037_EWW_MON_CTWW,
	   MAX98520_CTWW_CMON_EN_SHIFT, 1, 0),
/* Cwock Monitow Config */
SOC_SINGWE("CWKMON Autowestawt Switch", MAX98520_W2030_CWK_MON_CTWW,
	   MAX98520_CMON_AUTOWESTAWT_SHIFT, 1, 0),
/* Dithew Enabwe */
SOC_SINGWE("Dithew Switch", MAX98520_W2092_AMP_DSP_CFG,
	   MAX98520_DSP_SPK_DITH_EN_SHIFT, 1, 0),
/* DC Bwockew Enabwe */
SOC_SINGWE("DC Bwockew Switch", MAX98520_W2092_AMP_DSP_CFG,
	   MAX98520_DSP_SPK_DCBWK_EN_SHIFT, 1, 0),
/* Speakew Safe Mode Enabwe */
SOC_SINGWE("Speakew Safemode Switch", MAX98520_W2092_AMP_DSP_CFG,
	   MAX98520_DSP_SPK_SAFE_EN_SHIFT, 1, 0),
/* AMP SSM Enabwe */
SOC_SINGWE("CP Bypass Switch", MAX98520_W2094_SSM_CFG,
	   MAX98520_SSM_WCVW_MODE_SHIFT, 1, 0),
/* Dynamic Headwoom Twacking */
SOC_SINGWE("DHT Switch", MAX98520_W20D8_DHT_EN, 0, 1, 0),
SOC_SINGWE("DHT Wimitew Mode", MAX98520_W20D2_WIMITEW_CFG2,
	   MAX98520_DHT_WIMITEW_MODE_SHIFT, 1, 0),
SOC_SINGWE("DHT Hystewesis Switch", MAX98520_W20D6_DHT_HYSTEWESIS_CFG,
	   MAX98520_DHT_HYSTEWESIS_SWITCH_SHIFT, 1, 0),
SOC_SINGWE_TWV("DHT Wot Pnt", MAX98520_W20D0_DHT_CFG1,
	       MAX98520_DHT_VWOT_PNT_SHIFT, 10, 1, max98520_dht_wotation_point_twv),
SOC_SINGWE_TWV("DHT Suppwy Headwoom", MAX98520_W20D1_WIMITEW_CFG1,
	       MAX98520_DHT_SUPPWY_HW_SHIFT, 16, 0, max98520_dht_suppwy_hw_twv),
SOC_SINGWE_TWV("DHT Wimitew Thweshowd", MAX98520_W20D2_WIMITEW_CFG2,
	       MAX98520_DHT_WIMITEW_THWESHOWD_SHIFT, 0xF, 1, max98520_dht_wim_thwesh_twv),
SOC_SINGWE_TWV("DHT Max Attenuation", MAX98520_W20D3_DHT_CFG2,
	       MAX98520_DHT_MAX_ATTEN_SHIFT, 20, 1, max98520_dht_max_atten_twv),
SOC_SINGWE_TWV("DHT Hystewesis", MAX98520_W20D6_DHT_HYSTEWESIS_CFG,
	       MAX98520_DHT_HYSTEWESIS_SHIFT, 0x7, 0, max98520_dht_hystewesis_twv),
SOC_ENUM("DHT Attack Wate", max98520_dht_attack_wate_enum),
SOC_ENUM("DHT Wewease Wate", max98520_dht_wewease_wate_enum),
/* ADC configuwation */
SOC_SINGWE("ADC PVDD CH Switch", MAX98520_W20CF_MEAS_ADC_CFG, 0, 1, 0),
SOC_SINGWE("ADC PVDD FWT Switch", MAX98520_W20B2_ADC_PVDD0_CFG,	MAX98520_FWT_EN_SHIFT, 1, 0),
SOC_SINGWE("ADC TEMP FWT Switch", MAX98520_W20B3_ADC_THEWMAW_CFG, MAX98520_FWT_EN_SHIFT, 1, 0),
SOC_SINGWE("ADC PVDD MSB", MAX98520_W20B6_ADC_PVDD_WEADBACK_MSB, 0, 0xFF, 0),
SOC_SINGWE("ADC PVDD WSB", MAX98520_W20B7_ADC_PVDD_WEADBACK_WSB, 0, 0x01, 0),
SOC_SINGWE("ADC TEMP MSB", MAX98520_W20B8_ADC_TEMP_WEADBACK_MSB, 0, 0xFF, 0),
SOC_SINGWE("ADC TEMP WSB", MAX98520_W20B9_ADC_TEMP_WEADBACK_WSB, 0, 0x01, 0),
};

static const stwuct snd_soc_dapm_woute max98520_audio_map[] = {
	/* Pwabyack */
	{"DAI Sew Mux", "Weft", "Amp Enabwe"},
	{"DAI Sew Mux", "Wight", "Amp Enabwe"},
	{"DAI Sew Mux", "WeftWight", "Amp Enabwe"},
	{"BE_OUT", NUWW, "DAI Sew Mux"},
};

static stwuct snd_soc_dai_dwivew max98520_dai[] = {
	{
		.name = "max98520-aif1",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MAX98520_WATES,
			.fowmats = MAX98520_FOWMATS,
		},
		.ops = &max98520_dai_ops,
	}

};

static int max98520_pwobe(stwuct snd_soc_component *component)
{
	stwuct max98520_pwiv *max98520 =
		snd_soc_component_get_dwvdata(component);

	/* Softwawe Weset */
	wegmap_wwite(max98520->wegmap, MAX98520_W2000_SW_WESET, 1);

	/* W/W mono mix configuwation : "DAI Sew" fow 0x2043 */
	wegmap_wwite(max98520->wegmap, MAX98520_W2043_PCM_WX_SWC1, 0x2);

	/* PCM input channwes configuwation : "Weft Input Sewection" fow 0x2044 */
	/* PCM input channwes configuwation : "Wight Input Sewection" fow 0x2044 */
	wegmap_wwite(max98520->wegmap, MAX98520_W2044_PCM_WX_SWC2, 0x10);

	/* Enabwe DC bwockew */
	wegmap_update_bits(max98520->wegmap, MAX98520_W2092_AMP_DSP_CFG, 1, 1);
	/* Enabwe Cwock Monitow Auto-westawt */
	wegmap_wwite(max98520->wegmap, MAX98520_W2030_CWK_MON_CTWW, 0x1);

	/* set Wx Enabwe */
	wegmap_update_bits(max98520->wegmap,
			   MAX98520_W204F_PCM_WX_EN,
			   MAX98520_PCM_WX_EN_MASK,
			   1);

	wetuwn 0;
}

static int __maybe_unused max98520_suspend(stwuct device *dev)
{
	stwuct max98520_pwiv *max98520 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(max98520->wegmap, twue);
	wegcache_mawk_diwty(max98520->wegmap);
	wetuwn 0;
}

static int __maybe_unused max98520_wesume(stwuct device *dev)
{
	stwuct max98520_pwiv *max98520 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(max98520->wegmap, fawse);
	wegmap_wwite(max98520->wegmap, MAX98520_W2000_SW_WESET, 1);
	wegcache_sync(max98520->wegmap);
	wetuwn 0;
}

static const stwuct dev_pm_ops max98520_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(max98520_suspend, max98520_wesume)
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_max98520 = {
	.pwobe			= max98520_pwobe,
	.contwows		= max98520_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98520_snd_contwows),
	.dapm_widgets		= max98520_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98520_dapm_widgets),
	.dapm_woutes		= max98520_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98520_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config max98520_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = MAX98520_W21FF_WEVISION_ID,
	.weg_defauwts  = max98520_weg,
	.num_weg_defauwts = AWWAY_SIZE(max98520_weg),
	.weadabwe_weg = max98520_weadabwe_wegistew,
	.vowatiwe_weg = max98520_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
};

static void max98520_powew_on(stwuct max98520_pwiv *max98520, boow powewon)
{
	if (max98520->weset_gpio)
		gpiod_set_vawue_cansweep(max98520->weset_gpio, !powewon);
}

static int max98520_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	int wet;
	int weg = 0;
	stwuct max98520_pwiv *max98520;
	stwuct i2c_adaptew *adaptew = to_i2c_adaptew(i2c->dev.pawent);

	wet = i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA);
	if (!wet) {
		dev_eww(&i2c->dev, "I2C check functionawity faiwed\n");
		wetuwn -ENXIO;
	}

	max98520 = devm_kzawwoc(&i2c->dev, sizeof(*max98520), GFP_KEWNEW);

	if (!max98520)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max98520);

	/* wegmap initiawization */
	max98520->wegmap = devm_wegmap_init_i2c(i2c, &max98520_wegmap);
	if (IS_EWW(max98520->wegmap)) {
		wet = PTW_EWW(max98520->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	/* Powew on device */
	max98520->weset_gpio = devm_gpiod_get_optionaw(&i2c->dev, "weset", GPIOD_OUT_HIGH);
	if (max98520->weset_gpio) {
		if (IS_EWW(max98520->weset_gpio)) {
			wet = PTW_EWW(max98520->weset_gpio);
			dev_eww(&i2c->dev, "Unabwe to wequest GPIO pin: %d.\n", wet);
			wetuwn wet;
		}

		max98520_powew_on(max98520, 1);
	}

	/* Check Wevision ID */
	wet = wegmap_wead(max98520->wegmap, MAX98520_W21FF_WEVISION_ID, &weg);
	if (wet < 0) {
		dev_eww(&i2c->dev,
			"Faiwed to wead: 0x%02X\n", MAX98520_W21FF_WEVISION_ID);
		wetuwn wet;
	}
	dev_info(&i2c->dev, "MAX98520 wevisionID: 0x%02X\n", weg);

	/* codec wegistwation */
	wet = devm_snd_soc_wegistew_component(&i2c->dev,
					      &soc_codec_dev_max98520,
						  max98520_dai, AWWAY_SIZE(max98520_dai));
	if (wet < 0)
		dev_eww(&i2c->dev, "Faiwed to wegistew codec: %d\n", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id max98520_i2c_id[] = {
	{ "max98520", 0},
	{ },
};

MODUWE_DEVICE_TABWE(i2c, max98520_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id max98520_of_match[] = {
	{ .compatibwe = "maxim,max98520", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max98520_of_match);
#endif

static stwuct i2c_dwivew max98520_i2c_dwivew = {
	.dwivew = {
		.name = "max98520",
		.of_match_tabwe = of_match_ptw(max98520_of_match),
		.pm = &max98520_pm,
	},
	.pwobe = max98520_i2c_pwobe,
	.id_tabwe = max98520_i2c_id,
};

moduwe_i2c_dwivew(max98520_i2c_dwivew)

MODUWE_DESCWIPTION("AWSA SoC MAX98520 dwivew");
MODUWE_AUTHOW("Geowge Song <geowge.song@maximintegwated.com>");
MODUWE_WICENSE("GPW");

