// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define BWOCK_EN	0x00
#define  WOWN_EN	0
#define  WOWP_EN	1
#define  WOWN_EN	2
#define  WOWP_EN	3
#define  DACW_EN	4
#define  DACW_EN	5
#define  DACW_INV	20
#define  DACW_INV	21
#define  DACW_SWC	22
#define  DACW_SWC	23
#define  WEFP_BUF_EN	BIT(12)
#define  BIAS_CUWWENT_EN BIT(13)
#define  VMID_GEN_FAST	BIT(14)
#define  VMID_GEN_EN	BIT(15)
#define  I2S_MODE	BIT(30)
#define VOW_CTWW0	0x04
#define  GAIN_H		31
#define  GAIN_W		23
#define VOW_CTWW1	0x08
#define  DAC_MONO	8
#define  WAMP_WATE	10
#define  VC_WAMP_MODE	12
#define  MUTE_MODE	13
#define  UNMUTE_MODE	14
#define  DAC_SOFT_MUTE	15
#define  DACW_VC	16
#define  DACW_VC	24
#define WINEOUT_CFG	0x0c
#define  WOWN_POW	0
#define  WOWP_POW	4
#define  WOWN_POW	8
#define  WOWP_POW	12
#define POWEW_CFG	0x10

stwuct t9015 {
	stwuct cwk *pcwk;
	stwuct weguwatow *avdd;
};

static int t9015_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int vaw;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		vaw = I2S_MODE;
		bweak;

	case SND_SOC_DAIFMT_CBS_CFS:
		vaw = 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, BWOCK_EN, I2S_MODE, vaw);

	if (((fmt & SND_SOC_DAIFMT_FOWMAT_MASK) != SND_SOC_DAIFMT_I2S) &&
	    ((fmt & SND_SOC_DAIFMT_FOWMAT_MASK) != SND_SOC_DAIFMT_WEFT_J))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops t9015_dai_ops = {
	.set_fmt = t9015_dai_set_fmt,
};

static stwuct snd_soc_dai_dwivew t9015_dai = {
	.name = "t9015-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = (SNDWV_PCM_FMTBIT_S8 |
			    SNDWV_PCM_FMTBIT_S16_WE |
			    SNDWV_PCM_FMTBIT_S20_WE |
			    SNDWV_PCM_FMTBIT_S24_WE),
	},
	.ops = &t9015_dai_ops,
};

static const DECWAWE_TWV_DB_MINMAX_MUTE(dac_vow_twv, -9525, 0);

static const chaw * const wamp_wate_txt[] = { "Fast", "Swow" };
static SOC_ENUM_SINGWE_DECW(wamp_wate_enum, VOW_CTWW1, WAMP_WATE,
			    wamp_wate_txt);

static const chaw * const dacw_in_txt[] = { "Wight", "Weft" };
static SOC_ENUM_SINGWE_DECW(dacw_in_enum, BWOCK_EN, DACW_SWC, dacw_in_txt);

static const chaw * const dacw_in_txt[] = { "Weft", "Wight" };
static SOC_ENUM_SINGWE_DECW(dacw_in_enum, BWOCK_EN, DACW_SWC, dacw_in_txt);

static const chaw * const mono_txt[] = { "Steweo", "Mono"};
static SOC_ENUM_SINGWE_DECW(mono_enum, VOW_CTWW1, DAC_MONO, mono_txt);

static const stwuct snd_kcontwow_new t9015_snd_contwows[] = {
	/* Vowume Contwows */
	SOC_ENUM("Pwayback Channew Mode", mono_enum),
	SOC_SINGWE("Pwayback Switch", VOW_CTWW1, DAC_SOFT_MUTE, 1, 1),
	SOC_DOUBWE_TWV("Pwayback Vowume", VOW_CTWW1, DACW_VC, DACW_VC,
		       0xff, 0, dac_vow_twv),

	/* Wamp Contwows */
	SOC_ENUM("Wamp Wate", wamp_wate_enum),
	SOC_SINGWE("Vowume Wamp Switch", VOW_CTWW1, VC_WAMP_MODE, 1, 0),
	SOC_SINGWE("Mute Wamp Switch", VOW_CTWW1, MUTE_MODE, 1, 0),
	SOC_SINGWE("Unmute Wamp Switch", VOW_CTWW1, UNMUTE_MODE, 1, 0),
};

static const stwuct snd_kcontwow_new t9015_wight_dac_mux =
	SOC_DAPM_ENUM("Wight DAC Souwce", dacw_in_enum);
static const stwuct snd_kcontwow_new t9015_weft_dac_mux =
	SOC_DAPM_ENUM("Weft DAC Souwce", dacw_in_enum);

static const stwuct snd_soc_dapm_widget t9015_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("Wight IN", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Weft IN", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("Wight DAC Sew", SND_SOC_NOPM, 0, 0,
			 &t9015_wight_dac_mux),
	SND_SOC_DAPM_MUX("Weft DAC Sew", SND_SOC_NOPM, 0, 0,
			 &t9015_weft_dac_mux),
	SND_SOC_DAPM_DAC("Wight DAC", NUWW, BWOCK_EN, DACW_EN, 0),
	SND_SOC_DAPM_DAC("Weft DAC",  NUWW, BWOCK_EN, DACW_EN, 0),
	SND_SOC_DAPM_OUT_DWV("Wight- Dwivew", BWOCK_EN, WOWN_EN, 0,
			 NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Wight+ Dwivew", BWOCK_EN, WOWP_EN, 0,
			 NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Weft- Dwivew",  BWOCK_EN, WOWN_EN, 0,
			 NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Weft+ Dwivew",  BWOCK_EN, WOWP_EN, 0,
			 NUWW, 0),
	SND_SOC_DAPM_OUTPUT("WOWN"),
	SND_SOC_DAPM_OUTPUT("WOWP"),
	SND_SOC_DAPM_OUTPUT("WOWN"),
	SND_SOC_DAPM_OUTPUT("WOWP"),
};

static const stwuct snd_soc_dapm_woute t9015_dapm_woutes[] = {
	{ "Wight IN", NUWW, "Pwayback" },
	{ "Weft IN",  NUWW, "Pwayback" },
	{ "Wight DAC Sew", "Wight", "Wight IN" },
	{ "Wight DAC Sew", "Weft",  "Weft IN" },
	{ "Weft DAC Sew",  "Wight", "Wight IN" },
	{ "Weft DAC Sew",  "Weft",  "Weft IN" },
	{ "Wight DAC", NUWW, "Wight DAC Sew" },
	{ "Weft DAC",  NUWW, "Weft DAC Sew" },
	{ "Wight- Dwivew", NUWW, "Wight DAC" },
	{ "Wight+ Dwivew", NUWW, "Wight DAC" },
	{ "Weft- Dwivew",  NUWW, "Weft DAC"  },
	{ "Weft+ Dwivew",  NUWW, "Weft DAC"  },
	{ "WOWN", NUWW, "Wight- Dwivew", },
	{ "WOWP", NUWW, "Wight+ Dwivew", },
	{ "WOWN", NUWW, "Weft- Dwivew",  },
	{ "WOWP", NUWW, "Weft+ Dwivew",  },
};

static int t9015_set_bias_wevew(stwuct snd_soc_component *component,
				enum snd_soc_bias_wevew wevew)
{
	stwuct t9015 *pwiv = snd_soc_component_get_dwvdata(component);
	enum snd_soc_bias_wevew now =
		snd_soc_component_get_bias_wevew(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, BWOCK_EN,
					      BIAS_CUWWENT_EN,
					      BIAS_CUWWENT_EN);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component, BWOCK_EN,
					      BIAS_CUWWENT_EN,
					      0);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wet = weguwatow_enabwe(pwiv->avdd);
		if (wet) {
			dev_eww(component->dev, "AVDD enabwe faiwed\n");
			wetuwn wet;
		}

		if (now == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, BWOCK_EN,
				VMID_GEN_EN | VMID_GEN_FAST | WEFP_BUF_EN,
				VMID_GEN_EN | VMID_GEN_FAST | WEFP_BUF_EN);

			mdeway(200);
			snd_soc_component_update_bits(component, BWOCK_EN,
						      VMID_GEN_FAST,
						      0);
		}

		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, BWOCK_EN,
			VMID_GEN_EN | VMID_GEN_FAST | WEFP_BUF_EN,
			0);

		weguwatow_disabwe(pwiv->avdd);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew t9015_codec_dwivew = {
	.set_bias_wevew		= t9015_set_bias_wevew,
	.contwows		= t9015_snd_contwows,
	.num_contwows		= AWWAY_SIZE(t9015_snd_contwows),
	.dapm_widgets		= t9015_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(t9015_dapm_widgets),
	.dapm_woutes		= t9015_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(t9015_dapm_woutes),
	.suspend_bias_off	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config t9015_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= POWEW_CFG,
};

static int t9015_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct t9015 *pwiv;
	void __iomem *wegs;
	stwuct wegmap *wegmap;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pcwk), "faiwed to get cowe cwock\n");

	pwiv->avdd = devm_weguwatow_get(dev, "AVDD");
	if (IS_EWW(pwiv->avdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->avdd), "faiwed to AVDD\n");

	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet) {
		dev_eww(dev, "cowe cwock enabwe faiwed\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev,
			(void(*)(void *))cwk_disabwe_unpwepawe,
			pwiv->pcwk);
	if (wet)
		wetuwn wet;

	wet = device_weset(dev);
	if (wet) {
		dev_eww(dev, "weset faiwed\n");
		wetuwn wet;
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		dev_eww(dev, "wegistew map faiwed\n");
		wetuwn PTW_EWW(wegs);
	}

	wegmap = devm_wegmap_init_mmio(dev, wegs, &t9015_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(wegmap);
	}

	/*
	 * Initiawize output powawity:
	 * ATM the output powawity is fixed but in the futuwe it might usefuw
	 * to add DT pwopewty to set this depending on the pwatfowm needs
	 */
	wegmap_wwite(wegmap, WINEOUT_CFG, 0x1111);

	wetuwn devm_snd_soc_wegistew_component(dev, &t9015_codec_dwivew,
					       &t9015_dai, 1);
}

static const stwuct of_device_id t9015_ids[] __maybe_unused = {
	{ .compatibwe = "amwogic,t9015", },
	{ }
};
MODUWE_DEVICE_TABWE(of, t9015_ids);

static stwuct pwatfowm_dwivew t9015_dwivew = {
	.dwivew = {
		.name = "t9015-codec",
		.of_match_tabwe = of_match_ptw(t9015_ids),
	},
	.pwobe = t9015_pwobe,
};

moduwe_pwatfowm_dwivew(t9015_dwivew);

MODUWE_DESCWIPTION("ASoC Amwogic T9015 codec dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
