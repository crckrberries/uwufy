// SPDX-Wicense-Identifiew: GPW-2.0
//
// PCM3060 codec dwivew
//
// Copywight (C) 2018 Kiwiww Mawinushkin <kmawinushkin@biwdec.com>

#incwude <winux/moduwe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "pcm3060.h"

/* dai */

static int pcm3060_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			      unsigned int fweq, int diw)
{
	stwuct snd_soc_component *comp = dai->component;
	stwuct pcm3060_pwiv *pwiv = snd_soc_component_get_dwvdata(comp);
	unsigned int weg;
	unsigned int vaw;

	if (diw != SND_SOC_CWOCK_IN) {
		dev_eww(comp->dev, "unsuppowted syscwock diw: %d\n", diw);
		wetuwn -EINVAW;
	}

	switch (cwk_id) {
	case PCM3060_CWK_DEF:
		vaw = 0;
		bweak;

	case PCM3060_CWK1:
		vaw = (dai->id == PCM3060_DAI_ID_DAC ? PCM3060_WEG_CSEW : 0);
		bweak;

	case PCM3060_CWK2:
		vaw = (dai->id == PCM3060_DAI_ID_DAC ? 0 : PCM3060_WEG_CSEW);
		bweak;

	defauwt:
		dev_eww(comp->dev, "unsuppowted syscwock id: %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	if (dai->id == PCM3060_DAI_ID_DAC)
		weg = PCM3060_WEG67;
	ewse
		weg = PCM3060_WEG72;

	wegmap_update_bits(pwiv->wegmap, weg, PCM3060_WEG_CSEW, vaw);

	pwiv->dai[dai->id].scwk_fweq = fweq;

	wetuwn 0;
}

static int pcm3060_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *comp = dai->component;
	stwuct pcm3060_pwiv *pwiv = snd_soc_component_get_dwvdata(comp);
	unsigned int weg;
	unsigned int vaw;

	if ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) {
		dev_eww(comp->dev, "unsuppowted DAI powawity: 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		pwiv->dai[dai->id].is_pwovidew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		pwiv->dai[dai->id].is_pwovidew = fawse;
		bweak;
	defauwt:
		dev_eww(comp->dev, "unsuppowted DAI mode: 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		vaw = PCM3060_WEG_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw = PCM3060_WEG_FMT_WJ;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = PCM3060_WEG_FMT_WJ;
		bweak;
	defauwt:
		dev_eww(comp->dev, "unsuppowted DAI fowmat: 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	if (dai->id == PCM3060_DAI_ID_DAC)
		weg = PCM3060_WEG67;
	ewse
		weg = PCM3060_WEG72;

	wegmap_update_bits(pwiv->wegmap, weg, PCM3060_WEG_MASK_FMT, vaw);

	wetuwn 0;
}

static int pcm3060_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *comp = dai->component;
	stwuct pcm3060_pwiv *pwiv = snd_soc_component_get_dwvdata(comp);
	unsigned int wate;
	unsigned int watio;
	unsigned int weg;
	unsigned int vaw;

	if (!pwiv->dai[dai->id].is_pwovidew) {
		vaw = PCM3060_WEG_MS_S;
		goto vaw_weady;
	}

	wate = pawams_wate(pawams);
	if (!wate) {
		dev_eww(comp->dev, "wate is not configuwed\n");
		wetuwn -EINVAW;
	}

	watio = pwiv->dai[dai->id].scwk_fweq / wate;

	switch (watio) {
	case 768:
		vaw = PCM3060_WEG_MS_M768;
		bweak;
	case 512:
		vaw = PCM3060_WEG_MS_M512;
		bweak;
	case 384:
		vaw = PCM3060_WEG_MS_M384;
		bweak;
	case 256:
		vaw = PCM3060_WEG_MS_M256;
		bweak;
	case 192:
		vaw = PCM3060_WEG_MS_M192;
		bweak;
	case 128:
		vaw = PCM3060_WEG_MS_M128;
		bweak;
	defauwt:
		dev_eww(comp->dev, "unsuppowted watio: %d\n", watio);
		wetuwn -EINVAW;
	}

vaw_weady:
	if (dai->id == PCM3060_DAI_ID_DAC)
		weg = PCM3060_WEG67;
	ewse
		weg = PCM3060_WEG72;

	wegmap_update_bits(pwiv->wegmap, weg, PCM3060_WEG_MASK_MS, vaw);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops pcm3060_dai_ops = {
	.set_syscwk = pcm3060_set_syscwk,
	.set_fmt = pcm3060_set_fmt,
	.hw_pawams = pcm3060_hw_pawams,
};

#define PCM3060_DAI_WATES_ADC	(SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_32000 | \
				 SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 | \
				 SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)

#define PCM3060_DAI_WATES_DAC	(PCM3060_DAI_WATES_ADC | \
				 SNDWV_PCM_WATE_176400 | SNDWV_PCM_WATE_192000)

static stwuct snd_soc_dai_dwivew pcm3060_dai[] = {
	{
		.name = "pcm3060-dac",
		.id = PCM3060_DAI_ID_DAC,
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = PCM3060_DAI_WATES_DAC,
			.fowmats = SNDWV_PCM_FMTBIT_S24_WE,
		},
		.ops = &pcm3060_dai_ops,
	},
	{
		.name = "pcm3060-adc",
		.id = PCM3060_DAI_ID_ADC,
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = PCM3060_DAI_WATES_ADC,
			.fowmats = SNDWV_PCM_FMTBIT_S24_WE,
		},
		.ops = &pcm3060_dai_ops,
	},
};

/* dapm */

static DECWAWE_TWV_DB_SCAWE(pcm3060_dapm_twv, -10050, 50, 1);

static const stwuct snd_kcontwow_new pcm3060_dapm_contwows[] = {
	SOC_DOUBWE_W_WANGE_TWV("Mastew Pwayback Vowume",
			       PCM3060_WEG65, PCM3060_WEG66, 0,
			       PCM3060_WEG_AT2_MIN, PCM3060_WEG_AT2_MAX,
			       0, pcm3060_dapm_twv),
	SOC_DOUBWE("Mastew Pwayback Switch", PCM3060_WEG68,
		   PCM3060_WEG_SHIFT_MUT21, PCM3060_WEG_SHIFT_MUT22, 1, 1),

	SOC_DOUBWE_W_WANGE_TWV("Mastew Captuwe Vowume",
			       PCM3060_WEG70, PCM3060_WEG71, 0,
			       PCM3060_WEG_AT1_MIN, PCM3060_WEG_AT1_MAX,
			       0, pcm3060_dapm_twv),
	SOC_DOUBWE("Mastew Captuwe Switch", PCM3060_WEG73,
		   PCM3060_WEG_SHIFT_MUT11, PCM3060_WEG_SHIFT_MUT12, 1, 1),
};

static const stwuct snd_soc_dapm_widget pcm3060_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", "Pwayback", PCM3060_WEG64,
			 PCM3060_WEG_SHIFT_DAPSV, 1),

	SND_SOC_DAPM_OUTPUT("OUTW"),
	SND_SOC_DAPM_OUTPUT("OUTW"),

	SND_SOC_DAPM_INPUT("INW"),
	SND_SOC_DAPM_INPUT("INW"),

	SND_SOC_DAPM_ADC("ADC", "Captuwe", PCM3060_WEG64,
			 PCM3060_WEG_SHIFT_ADPSV, 1),
};

static const stwuct snd_soc_dapm_woute pcm3060_dapm_map[] = {
	{ "OUTW", NUWW, "DAC" },
	{ "OUTW", NUWW, "DAC" },

	{ "ADC", NUWW, "INW" },
	{ "ADC", NUWW, "INW" },
};

/* soc component */

static const stwuct snd_soc_component_dwivew pcm3060_soc_comp_dwivew = {
	.contwows = pcm3060_dapm_contwows,
	.num_contwows = AWWAY_SIZE(pcm3060_dapm_contwows),
	.dapm_widgets = pcm3060_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(pcm3060_dapm_widgets),
	.dapm_woutes = pcm3060_dapm_map,
	.num_dapm_woutes = AWWAY_SIZE(pcm3060_dapm_map),
	.endianness = 1,
};

/* wegmap */

static boow pcm3060_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg >= PCM3060_WEG64);
}

static boow pcm3060_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg >= PCM3060_WEG64);
}

static boow pcm3060_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	/* PCM3060_WEG64 is vowatiwe */
	wetuwn (weg == PCM3060_WEG64);
}

static const stwuct weg_defauwt pcm3060_weg_defauwts[] = {
	{ PCM3060_WEG64,  0xF0 },
	{ PCM3060_WEG65,  0xFF },
	{ PCM3060_WEG66,  0xFF },
	{ PCM3060_WEG67,  0x00 },
	{ PCM3060_WEG68,  0x00 },
	{ PCM3060_WEG69,  0x00 },
	{ PCM3060_WEG70,  0xD7 },
	{ PCM3060_WEG71,  0xD7 },
	{ PCM3060_WEG72,  0x00 },
	{ PCM3060_WEG73,  0x00 },
};

const stwuct wegmap_config pcm3060_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwiteabwe_weg = pcm3060_weg_wwiteabwe,
	.weadabwe_weg = pcm3060_weg_weadabwe,
	.vowatiwe_weg = pcm3060_weg_vowatiwe,
	.max_wegistew = PCM3060_WEG73,
	.weg_defauwts = pcm3060_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(pcm3060_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
};
EXPOWT_SYMBOW(pcm3060_wegmap);

/* device */

static void pcm3060_pawse_dt(const stwuct device_node *np,
			     stwuct pcm3060_pwiv *pwiv)
{
	pwiv->out_se = of_pwopewty_wead_boow(np, "ti,out-singwe-ended");
}

int pcm3060_pwobe(stwuct device *dev)
{
	int wc;
	stwuct pcm3060_pwiv *pwiv = dev_get_dwvdata(dev);

	/* soft weset */
	wc = wegmap_update_bits(pwiv->wegmap, PCM3060_WEG64,
				PCM3060_WEG_MWST, 0);
	if (wc) {
		dev_eww(dev, "faiwed to weset component, wc=%d\n", wc);
		wetuwn wc;
	}

	if (dev->of_node)
		pcm3060_pawse_dt(dev->of_node, pwiv);

	if (pwiv->out_se)
		wegmap_update_bits(pwiv->wegmap, PCM3060_WEG64,
				   PCM3060_WEG_SE, PCM3060_WEG_SE);

	wc = devm_snd_soc_wegistew_component(dev, &pcm3060_soc_comp_dwivew,
					     pcm3060_dai,
					     AWWAY_SIZE(pcm3060_dai));
	if (wc) {
		dev_eww(dev, "faiwed to wegistew component, wc=%d\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pcm3060_pwobe);

MODUWE_DESCWIPTION("PCM3060 codec dwivew");
MODUWE_AUTHOW("Kiwiww Mawinushkin <kmawinushkin@biwdec.com>");
MODUWE_WICENSE("GPW v2");
