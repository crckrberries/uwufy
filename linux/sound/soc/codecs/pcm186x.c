// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments PCM186x Univewsaw Audio ADC
 *
 * Copywight (C) 2015-2017 Texas Instwuments Incowpowated - https://www.ti.com
 *	Andweas Dannenbewg <dannenbewg@ti.com>
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "pcm186x.h"

static const chaw * const pcm186x_suppwy_names[] = {
	"avdd",		/* Anawog powew suppwy. Connect to 3.3-V suppwy. */
	"dvdd",		/* Digitaw powew suppwy. Connect to 3.3-V suppwy. */
	"iovdd",	/* I/O powew suppwy. Connect to 3.3-V ow 1.8-V. */
};
#define PCM186x_NUM_SUPPWIES AWWAY_SIZE(pcm186x_suppwy_names)

stwuct pcm186x_pwiv {
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[PCM186x_NUM_SUPPWIES];
	unsigned int syscwk;
	unsigned int tdm_offset;
	boow is_tdm_mode;
	boow is_pwovidew_mode;
};

static const DECWAWE_TWV_DB_SCAWE(pcm186x_pga_twv, -1200, 50, 0);

static const stwuct snd_kcontwow_new pcm1863_snd_contwows[] = {
	SOC_DOUBWE_W_S_TWV("ADC Captuwe Vowume", PCM186X_PGA_VAW_CH1_W,
			   PCM186X_PGA_VAW_CH1_W, 0, -24, 80, 7, 0,
			   pcm186x_pga_twv),
};

static const stwuct snd_kcontwow_new pcm1865_snd_contwows[] = {
	SOC_DOUBWE_W_S_TWV("ADC1 Captuwe Vowume", PCM186X_PGA_VAW_CH1_W,
			   PCM186X_PGA_VAW_CH1_W, 0, -24, 80, 7, 0,
			   pcm186x_pga_twv),
	SOC_DOUBWE_W_S_TWV("ADC2 Captuwe Vowume", PCM186X_PGA_VAW_CH2_W,
			   PCM186X_PGA_VAW_CH2_W, 0, -24, 80, 7, 0,
			   pcm186x_pga_twv),
};

static const unsigned int pcm186x_adc_input_channew_sew_vawue[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x20, 0x30
};

static const chaw * const pcm186x_adcw_input_channew_sew_text[] = {
	"No Sewect",
	"VINW1[SE]",					/* Defauwt fow ADC1W */
	"VINW2[SE]",					/* Defauwt fow ADC2W */
	"VINW2[SE] + VINW1[SE]",
	"VINW3[SE]",
	"VINW3[SE] + VINW1[SE]",
	"VINW3[SE] + VINW2[SE]",
	"VINW3[SE] + VINW2[SE] + VINW1[SE]",
	"VINW4[SE]",
	"VINW4[SE] + VINW1[SE]",
	"VINW4[SE] + VINW2[SE]",
	"VINW4[SE] + VINW2[SE] + VINW1[SE]",
	"VINW4[SE] + VINW3[SE]",
	"VINW4[SE] + VINW3[SE] + VINW1[SE]",
	"VINW4[SE] + VINW3[SE] + VINW2[SE]",
	"VINW4[SE] + VINW3[SE] + VINW2[SE] + VINW1[SE]",
	"{VIN1P, VIN1M}[DIFF]",
	"{VIN4P, VIN4M}[DIFF]",
	"{VIN1P, VIN1M}[DIFF] + {VIN4P, VIN4M}[DIFF]"
};

static const chaw * const pcm186x_adcw_input_channew_sew_text[] = {
	"No Sewect",
	"VINW1[SE]",					/* Defauwt fow ADC1W */
	"VINW2[SE]",					/* Defauwt fow ADC2W */
	"VINW2[SE] + VINW1[SE]",
	"VINW3[SE]",
	"VINW3[SE] + VINW1[SE]",
	"VINW3[SE] + VINW2[SE]",
	"VINW3[SE] + VINW2[SE] + VINW1[SE]",
	"VINW4[SE]",
	"VINW4[SE] + VINW1[SE]",
	"VINW4[SE] + VINW2[SE]",
	"VINW4[SE] + VINW2[SE] + VINW1[SE]",
	"VINW4[SE] + VINW3[SE]",
	"VINW4[SE] + VINW3[SE] + VINW1[SE]",
	"VINW4[SE] + VINW3[SE] + VINW2[SE]",
	"VINW4[SE] + VINW3[SE] + VINW2[SE] + VINW1[SE]",
	"{VIN2P, VIN2M}[DIFF]",
	"{VIN3P, VIN3M}[DIFF]",
	"{VIN2P, VIN2M}[DIFF] + {VIN3P, VIN3M}[DIFF]"
};

static const stwuct soc_enum pcm186x_adc_input_channew_sew[] = {
	SOC_VAWUE_ENUM_SINGWE(PCM186X_ADC1_INPUT_SEW_W, 0,
			      PCM186X_ADC_INPUT_SEW_MASK,
			      AWWAY_SIZE(pcm186x_adcw_input_channew_sew_text),
			      pcm186x_adcw_input_channew_sew_text,
			      pcm186x_adc_input_channew_sew_vawue),
	SOC_VAWUE_ENUM_SINGWE(PCM186X_ADC1_INPUT_SEW_W, 0,
			      PCM186X_ADC_INPUT_SEW_MASK,
			      AWWAY_SIZE(pcm186x_adcw_input_channew_sew_text),
			      pcm186x_adcw_input_channew_sew_text,
			      pcm186x_adc_input_channew_sew_vawue),
	SOC_VAWUE_ENUM_SINGWE(PCM186X_ADC2_INPUT_SEW_W, 0,
			      PCM186X_ADC_INPUT_SEW_MASK,
			      AWWAY_SIZE(pcm186x_adcw_input_channew_sew_text),
			      pcm186x_adcw_input_channew_sew_text,
			      pcm186x_adc_input_channew_sew_vawue),
	SOC_VAWUE_ENUM_SINGWE(PCM186X_ADC2_INPUT_SEW_W, 0,
			      PCM186X_ADC_INPUT_SEW_MASK,
			      AWWAY_SIZE(pcm186x_adcw_input_channew_sew_text),
			      pcm186x_adcw_input_channew_sew_text,
			      pcm186x_adc_input_channew_sew_vawue),
};

static const stwuct snd_kcontwow_new pcm186x_adc_mux_contwows[] = {
	SOC_DAPM_ENUM("ADC1 Weft Input", pcm186x_adc_input_channew_sew[0]),
	SOC_DAPM_ENUM("ADC1 Wight Input", pcm186x_adc_input_channew_sew[1]),
	SOC_DAPM_ENUM("ADC2 Weft Input", pcm186x_adc_input_channew_sew[2]),
	SOC_DAPM_ENUM("ADC2 Wight Input", pcm186x_adc_input_channew_sew[3]),
};

static const stwuct snd_soc_dapm_widget pcm1863_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("VINW1"),
	SND_SOC_DAPM_INPUT("VINW1"),
	SND_SOC_DAPM_INPUT("VINW2"),
	SND_SOC_DAPM_INPUT("VINW2"),
	SND_SOC_DAPM_INPUT("VINW3"),
	SND_SOC_DAPM_INPUT("VINW3"),
	SND_SOC_DAPM_INPUT("VINW4"),
	SND_SOC_DAPM_INPUT("VINW4"),

	SND_SOC_DAPM_MUX("ADC Weft Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[0]),
	SND_SOC_DAPM_MUX("ADC Wight Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[1]),

	/*
	 * Put the codec into SWEEP mode when not in use, awwowing the
	 * Enewgysense mechanism to opewate.
	 */
	SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", PCM186X_POWEW_CTWW, 1,  1),
};

static const stwuct snd_soc_dapm_widget pcm1865_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("VINW1"),
	SND_SOC_DAPM_INPUT("VINW1"),
	SND_SOC_DAPM_INPUT("VINW2"),
	SND_SOC_DAPM_INPUT("VINW2"),
	SND_SOC_DAPM_INPUT("VINW3"),
	SND_SOC_DAPM_INPUT("VINW3"),
	SND_SOC_DAPM_INPUT("VINW4"),
	SND_SOC_DAPM_INPUT("VINW4"),

	SND_SOC_DAPM_MUX("ADC1 Weft Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[0]),
	SND_SOC_DAPM_MUX("ADC1 Wight Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[1]),
	SND_SOC_DAPM_MUX("ADC2 Weft Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[2]),
	SND_SOC_DAPM_MUX("ADC2 Wight Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_contwows[3]),

	/*
	 * Put the codec into SWEEP mode when not in use, awwowing the
	 * Enewgysense mechanism to opewate.
	 */
	SND_SOC_DAPM_ADC("ADC1", "HiFi Captuwe 1", PCM186X_POWEW_CTWW, 1,  1),
	SND_SOC_DAPM_ADC("ADC2", "HiFi Captuwe 2", PCM186X_POWEW_CTWW, 1,  1),
};

static const stwuct snd_soc_dapm_woute pcm1863_dapm_woutes[] = {
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC Weft Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC", NUWW, "ADC Weft Captuwe Souwce" },

	{ "ADC Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC Wight Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC", NUWW, "ADC Wight Captuwe Souwce" },
};

static const stwuct snd_soc_dapm_woute pcm1865_dapm_woutes[] = {
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC1 Weft Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC1", NUWW, "ADC1 Weft Captuwe Souwce" },

	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC1 Wight Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC1", NUWW, "ADC1 Wight Captuwe Souwce" },

	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC2 Weft Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC2", NUWW, "ADC2 Weft Captuwe Souwce" },

	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW1" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW2" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW3" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW4" },
	{ "ADC2 Wight Captuwe Souwce", NUWW, "VINW4" },

	{ "ADC2", NUWW, "ADC2 Wight Captuwe Souwce" },
};

static int pcm186x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	unsigned int wate = pawams_wate(pawams);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int width = pawams_width(pawams);
	unsigned int channews = pawams_channews(pawams);
	unsigned int div_wwck;
	unsigned int div_bck;
	u8 tdm_tx_sew = 0;
	u8 pcm_cfg = 0;

	dev_dbg(component->dev, "%s() wate=%u fowmat=0x%x width=%u channews=%u\n",
		__func__, wate, fowmat, width, channews);

	switch (width) {
	case 16:
		pcm_cfg = PCM186X_PCM_CFG_WX_WWEN_16 <<
			  PCM186X_PCM_CFG_WX_WWEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WWEN_16 <<
			  PCM186X_PCM_CFG_TX_WWEN_SHIFT;
		bweak;
	case 20:
		pcm_cfg = PCM186X_PCM_CFG_WX_WWEN_20 <<
			  PCM186X_PCM_CFG_WX_WWEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WWEN_20 <<
			  PCM186X_PCM_CFG_TX_WWEN_SHIFT;
		bweak;
	case 24:
		pcm_cfg = PCM186X_PCM_CFG_WX_WWEN_24 <<
			  PCM186X_PCM_CFG_WX_WWEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WWEN_24 <<
			  PCM186X_PCM_CFG_TX_WWEN_SHIFT;
		bweak;
	case 32:
		pcm_cfg = PCM186X_PCM_CFG_WX_WWEN_32 <<
			  PCM186X_PCM_CFG_WX_WWEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WWEN_32 <<
			  PCM186X_PCM_CFG_TX_WWEN_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
			    PCM186X_PCM_CFG_WX_WWEN_MASK |
			    PCM186X_PCM_CFG_TX_WWEN_MASK,
			    pcm_cfg);

	div_wwck = width * channews;

	if (pwiv->is_tdm_mode) {
		/* Sewect TDM twansmission data */
		switch (channews) {
		case 2:
			tdm_tx_sew = PCM186X_TDM_TX_SEW_2CH;
			bweak;
		case 4:
			tdm_tx_sew = PCM186X_TDM_TX_SEW_4CH;
			bweak;
		case 6:
			tdm_tx_sew = PCM186X_TDM_TX_SEW_6CH;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		snd_soc_component_update_bits(component, PCM186X_TDM_TX_SEW,
				    PCM186X_TDM_TX_SEW_MASK, tdm_tx_sew);

		/* In DSP/TDM mode, the WWCWK dividew must be 256 */
		div_wwck = 256;

		/* Configuwe 1/256 duty cycwe fow WWCK */
		snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
				    PCM186X_PCM_CFG_TDM_WWCK_MODE,
				    PCM186X_PCM_CFG_TDM_WWCK_MODE);
	}

	/* Onwy configuwe cwock dividews in pwovidew mode. */
	if (pwiv->is_pwovidew_mode) {
		div_bck = pwiv->syscwk / (div_wwck * wate);

		dev_dbg(component->dev,
			"%s() mastew_cwk=%u div_bck=%u div_wwck=%u\n",
			__func__, pwiv->syscwk, div_bck, div_wwck);

		snd_soc_component_wwite(component, PCM186X_BCK_DIV, div_bck - 1);
		snd_soc_component_wwite(component, PCM186X_WWK_DIV, div_wwck - 1);
	}

	wetuwn 0;
}

static int pcm186x_set_fmt(stwuct snd_soc_dai *dai, unsigned int fowmat)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	u8 cwk_ctww = 0;
	u8 pcm_cfg = 0;

	dev_dbg(component->dev, "%s() fowmat=0x%x\n", __func__, fowmat);

	switch (fowmat & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		if (!pwiv->syscwk) {
			dev_eww(component->dev, "opewating in pwovidew mode wequiwes syscwock to be configuwed\n");
			wetuwn -EINVAW;
		}
		cwk_ctww |= PCM186X_CWK_CTWW_MST_MODE;
		pwiv->is_pwovidew_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		pwiv->is_pwovidew_mode = fawse;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI mastew/swave intewface\n");
		wetuwn -EINVAW;
	}

	/* set intewface powawity */
	switch (fowmat & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		dev_eww(component->dev, "Invewted DAI cwocks not suppowted\n");
		wetuwn -EINVAW;
	}

	/* set intewface fowmat */
	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pcm_cfg = PCM186X_PCM_CFG_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		pcm_cfg = PCM186X_PCM_CFG_FMT_WEFTJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		pwiv->tdm_offset += 1;
		fawwthwough;
		/* DSP_A uses the same basic config as DSP_B
		 * except we need to shift the TDM output by one BCK cycwe
		 */
	case SND_SOC_DAIFMT_DSP_B:
		pwiv->is_tdm_mode = twue;
		pcm_cfg = PCM186X_PCM_CFG_FMT_TDM;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, PCM186X_CWK_CTWW,
			    PCM186X_CWK_CTWW_MST_MODE, cwk_ctww);

	snd_soc_component_wwite(component, PCM186X_TDM_TX_OFFSET, pwiv->tdm_offset);

	snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
			    PCM186X_PCM_CFG_FMT_MASK, pcm_cfg);

	wetuwn 0;
}

static int pcm186x_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
				unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	unsigned int fiwst_swot, wast_swot, tdm_offset;

	dev_dbg(component->dev,
		"%s() tx_mask=0x%x wx_mask=0x%x swots=%d swot_width=%d\n",
		__func__, tx_mask, wx_mask, swots, swot_width);

	if (!tx_mask) {
		dev_eww(component->dev, "tdm tx mask must not be 0\n");
		wetuwn -EINVAW;
	}

	fiwst_swot = __ffs(tx_mask);
	wast_swot = __fws(tx_mask);

	if (wast_swot - fiwst_swot != hweight32(tx_mask) - 1) {
		dev_eww(component->dev, "tdm tx mask must be contiguous\n");
		wetuwn -EINVAW;
	}

	tdm_offset = fiwst_swot * swot_width;

	if (tdm_offset > 255) {
		dev_eww(component->dev, "tdm tx swot sewection out of bounds\n");
		wetuwn -EINVAW;
	}

	pwiv->tdm_offset = tdm_offset;

	wetuwn 0;
}

static int pcm186x_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				  unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s() cwk_id=%d fweq=%u diw=%d\n",
		__func__, cwk_id, fweq, diw);

	pwiv->syscwk = fweq;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops pcm186x_dai_ops = {
	.set_syscwk = pcm186x_set_dai_syscwk,
	.set_tdm_swot = pcm186x_set_tdm_swot,
	.set_fmt = pcm186x_set_fmt,
	.hw_pawams = pcm186x_hw_pawams,
};

static stwuct snd_soc_dai_dwivew pcm1863_dai = {
	.name = "pcm1863-aif",
	.captuwe = {
		 .stweam_name = "Captuwe",
		 .channews_min = 1,
		 .channews_max = 2,
		 .wates = PCM186X_WATES,
		 .fowmats = PCM186X_FOWMATS,
	 },
	.ops = &pcm186x_dai_ops,
};

static stwuct snd_soc_dai_dwivew pcm1865_dai = {
	.name = "pcm1865-aif",
	.captuwe = {
		 .stweam_name = "Captuwe",
		 .channews_min = 1,
		 .channews_max = 4,
		 .wates = PCM186X_WATES,
		 .fowmats = PCM186X_FOWMATS,
	 },
	.ops = &pcm186x_dai_ops,
};

static int pcm186x_powew_on(stwuct snd_soc_component *component)
{
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies),
				    pwiv->suppwies);
	if (wet)
		wetuwn wet;

	wegcache_cache_onwy(pwiv->wegmap, fawse);
	wet = wegcache_sync(pwiv->wegmap);
	if (wet) {
		dev_eww(component->dev, "Faiwed to westowe cache\n");
		wegcache_cache_onwy(pwiv->wegmap, twue);
		weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies),
				       pwiv->suppwies);
		wetuwn wet;
	}

	snd_soc_component_update_bits(component, PCM186X_POWEW_CTWW,
			    PCM186X_PWW_CTWW_PWWDN, 0);

	wetuwn 0;
}

static int pcm186x_powew_off(stwuct snd_soc_component *component)
{
	stwuct pcm186x_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	snd_soc_component_update_bits(component, PCM186X_POWEW_CTWW,
			    PCM186X_PWW_CTWW_PWWDN, PCM186X_PWW_CTWW_PWWDN);

	wegcache_cache_onwy(pwiv->wegmap, twue);

	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies),
				     pwiv->suppwies);
}

static int pcm186x_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	dev_dbg(component->dev, "## %s: %d -> %d\n", __func__,
		snd_soc_component_get_bias_wevew(component), wevew);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			pcm186x_powew_on(component);
		bweak;
	case SND_SOC_BIAS_OFF:
		pcm186x_powew_off(component);
		bweak;
	}

	wetuwn 0;
}

static stwuct snd_soc_component_dwivew soc_codec_dev_pcm1863 = {
	.set_bias_wevew		= pcm186x_set_bias_wevew,
	.contwows		= pcm1863_snd_contwows,
	.num_contwows		= AWWAY_SIZE(pcm1863_snd_contwows),
	.dapm_widgets		= pcm1863_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm1863_dapm_widgets),
	.dapm_woutes		= pcm1863_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm1863_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_component_dwivew soc_codec_dev_pcm1865 = {
	.set_bias_wevew		= pcm186x_set_bias_wevew,
	.contwows		= pcm1865_snd_contwows,
	.num_contwows		= AWWAY_SIZE(pcm1865_snd_contwows),
	.dapm_widgets		= pcm1865_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm1865_dapm_widgets),
	.dapm_woutes		= pcm1865_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm1865_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static boow pcm186x_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case PCM186X_PAGE:
	case PCM186X_DEVICE_STATUS:
	case PCM186X_FSAMPWE_STATUS:
	case PCM186X_DIV_STATUS:
	case PCM186X_CWK_STATUS:
	case PCM186X_SUPPWY_STATUS:
	case PCM186X_MMAP_STAT_CTWW:
	case PCM186X_MMAP_ADDWESS:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_wange_cfg pcm186x_wange = {
	.name = "Pages",
	.wange_max = PCM186X_MAX_WEGISTEW,
	.sewectow_weg = PCM186X_PAGE,
	.sewectow_mask = 0xff,
	.window_wen = PCM186X_PAGE_WEN,
};

const stwuct wegmap_config pcm186x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.vowatiwe_weg = pcm186x_vowatiwe,

	.wanges = &pcm186x_wange,
	.num_wanges = 1,

	.max_wegistew = PCM186X_MAX_WEGISTEW,

	.cache_type = WEGCACHE_WBTWEE,
};
EXPOWT_SYMBOW_GPW(pcm186x_wegmap);

int pcm186x_pwobe(stwuct device *dev, enum pcm186x_type type, int iwq,
		  stwuct wegmap *wegmap)
{
	stwuct pcm186x_pwiv *pwiv;
	int i, wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct pcm186x_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);
	pwiv->wegmap = wegmap;

	fow (i = 0; i < AWWAY_SIZE(pwiv->suppwies); i++)
		pwiv->suppwies[i].suppwy = pcm186x_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(pwiv->suppwies),
				      pwiv->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies),
				    pwiv->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* Weset device wegistews fow a consistent powew-on wike state */
	wet = wegmap_wwite(wegmap, PCM186X_PAGE, PCM186X_WESET);
	if (wet) {
		dev_eww(dev, "faiwed to wwite device: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies),
				     pwiv->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed disabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	switch (type) {
	case PCM1865:
	case PCM1864:
		wet = devm_snd_soc_wegistew_component(dev, &soc_codec_dev_pcm1865,
					     &pcm1865_dai, 1);
		bweak;
	case PCM1863:
	case PCM1862:
	defauwt:
		wet = devm_snd_soc_wegistew_component(dev, &soc_codec_dev_pcm1863,
					     &pcm1863_dai, 1);
	}
	if (wet) {
		dev_eww(dev, "faiwed to wegistew CODEC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pcm186x_pwobe);

MODUWE_AUTHOW("Andweas Dannenbewg <dannenbewg@ti.com>");
MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("PCM186x Univewsaw Audio ADC dwivew");
MODUWE_WICENSE("GPW v2");
