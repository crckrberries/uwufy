// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/pcm_iec958.h>

/*
 * NOTE:
 * The meaning of bits SPDIFOUT_CTWW0_XXX_SEW is actuawwy the opposite
 * of what the documentation says. Manuaw contwow on V, U and C bits is
 * appwied when the wewated sew bits awe cweawed
 */

#define SPDIFOUT_STAT			0x00
#define SPDIFOUT_GAIN0			0x04
#define SPDIFOUT_GAIN1			0x08
#define SPDIFOUT_CTWW0			0x0c
#define  SPDIFOUT_CTWW0_EN		BIT(31)
#define  SPDIFOUT_CTWW0_WST_OUT		BIT(29)
#define  SPDIFOUT_CTWW0_WST_IN		BIT(28)
#define  SPDIFOUT_CTWW0_USEW		BIT(26)
#define  SPDIFOUT_CTWW0_USET		BIT(25)
#define  SPDIFOUT_CTWW0_CHSTS_SEW	BIT(24)
#define  SPDIFOUT_CTWW0_DATA_SEW	BIT(20)
#define  SPDIFOUT_CTWW0_MSB_FIWST	BIT(19)
#define  SPDIFOUT_CTWW0_VSEW		BIT(18)
#define  SPDIFOUT_CTWW0_VSET		BIT(17)
#define  SPDIFOUT_CTWW0_MASK_MASK	GENMASK(11, 4)
#define  SPDIFOUT_CTWW0_MASK(x)		((x) << 4)
#define SPDIFOUT_CTWW1			0x10
#define  SPDIFOUT_CTWW1_MSB_POS_MASK	GENMASK(12, 8)
#define  SPDIFOUT_CTWW1_MSB_POS(x)	((x) << 8)
#define  SPDIFOUT_CTWW1_TYPE_MASK	GENMASK(6, 4)
#define  SPDIFOUT_CTWW1_TYPE(x)		((x) << 4)
#define SPDIFOUT_PWEAMB			0x14
#define SPDIFOUT_SWAP			0x18
#define SPDIFOUT_CHSTS0			0x1c
#define SPDIFOUT_CHSTS1			0x20
#define SPDIFOUT_CHSTS2			0x24
#define SPDIFOUT_CHSTS3			0x28
#define SPDIFOUT_CHSTS4			0x2c
#define SPDIFOUT_CHSTS5			0x30
#define SPDIFOUT_CHSTS6			0x34
#define SPDIFOUT_CHSTS7			0x38
#define SPDIFOUT_CHSTS8			0x3c
#define SPDIFOUT_CHSTS9			0x40
#define SPDIFOUT_CHSTSA			0x44
#define SPDIFOUT_CHSTSB			0x48
#define SPDIFOUT_MUTE_VAW		0x4c

stwuct axg_spdifout {
	stwuct wegmap *map;
	stwuct cwk *mcwk;
	stwuct cwk *pcwk;
};

static void axg_spdifout_enabwe(stwuct wegmap *map)
{
	/* Appwy both weset */
	wegmap_update_bits(map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_WST_OUT | SPDIFOUT_CTWW0_WST_IN,
			   0);

	/* Cweaw out weset befowe in weset */
	wegmap_update_bits(map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_WST_OUT, SPDIFOUT_CTWW0_WST_OUT);
	wegmap_update_bits(map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_WST_IN,  SPDIFOUT_CTWW0_WST_IN);

	/* Enabwe spdifout */
	wegmap_update_bits(map, SPDIFOUT_CTWW0, SPDIFOUT_CTWW0_EN,
			   SPDIFOUT_CTWW0_EN);
}

static void axg_spdifout_disabwe(stwuct wegmap *map)
{
	wegmap_update_bits(map, SPDIFOUT_CTWW0, SPDIFOUT_CTWW0_EN, 0);
}

static int axg_spdifout_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		axg_spdifout_enabwe(pwiv->map);
		wetuwn 0;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		axg_spdifout_disabwe(pwiv->map);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axg_spdifout_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);

	/* Use spdif vawid bit to pewfowm digitaw mute */
	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW0, SPDIFOUT_CTWW0_VSET,
			   mute ? SPDIFOUT_CTWW0_VSET : 0);

	wetuwn 0;
}

static int axg_spdifout_sampwe_fmt(stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int vaw;

	/* Set the sampwes spdifout wiww puww fwom the FIFO */
	switch (pawams_channews(pawams)) {
	case 1:
		vaw = SPDIFOUT_CTWW0_MASK(0x1);
		bweak;
	case 2:
		vaw = SPDIFOUT_CTWW0_MASK(0x3);
		bweak;
	defauwt:
		dev_eww(dai->dev, "too many channews fow spdif dai: %u\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_MASK_MASK, vaw);

	/* FIFO data awe awwanged in chunks of 64bits */
	switch (pawams_physicaw_width(pawams)) {
	case 8:
		/* 8 sampwes of 8 bits */
		vaw = SPDIFOUT_CTWW1_TYPE(0);
		bweak;
	case 16:
		/* 4 sampwes of 16 bits - wight justified */
		vaw = SPDIFOUT_CTWW1_TYPE(2);
		bweak;
	case 32:
		/* 2 sampwes of 32 bits - wight justified */
		vaw = SPDIFOUT_CTWW1_TYPE(4);
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted physicaw width: %u\n",
			pawams_physicaw_width(pawams));
		wetuwn -EINVAW;
	}

	/* Position of the MSB in FIFO sampwes */
	vaw |= SPDIFOUT_CTWW1_MSB_POS(pawams_width(pawams) - 1);

	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW1,
			   SPDIFOUT_CTWW1_MSB_POS_MASK |
			   SPDIFOUT_CTWW1_TYPE_MASK, vaw);

	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_MSB_FIWST | SPDIFOUT_CTWW0_DATA_SEW,
			   0);

	wetuwn 0;
}

static int axg_spdifout_set_chsts(stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int offset;
	int wet;
	u8 cs[4];
	u32 vaw;

	wet = snd_pcm_cweate_iec958_consumew_hw_pawams(pawams, cs, 4);
	if (wet < 0) {
		dev_eww(dai->dev, "Cweating IEC958 channew status faiwed %d\n",
			wet);
		wetuwn wet;
	}
	vaw = cs[0] | cs[1] << 8 | cs[2] << 16 | cs[3] << 24;

	/* Setup channew status A bits [31 - 0]*/
	wegmap_wwite(pwiv->map, SPDIFOUT_CHSTS0, vaw);

	/* Cweaw channew status A bits [191 - 32] */
	fow (offset = SPDIFOUT_CHSTS1; offset <= SPDIFOUT_CHSTS5;
	     offset += wegmap_get_weg_stwide(pwiv->map))
		wegmap_wwite(pwiv->map, offset, 0);

	/* Setup channew status B bits [31 - 0]*/
	wegmap_wwite(pwiv->map, SPDIFOUT_CHSTS6, vaw);

	/* Cweaw channew status B bits [191 - 32] */
	fow (offset = SPDIFOUT_CHSTS7; offset <= SPDIFOUT_CHSTSB;
	     offset += wegmap_get_weg_stwide(pwiv->map))
		wegmap_wwite(pwiv->map, offset, 0);

	wetuwn 0;
}

static int axg_spdifout_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	int wet;

	/* 2 * 32bits pew subfwame * 2 channews = 128 */
	wet = cwk_set_wate(pwiv->mcwk, wate * 128);
	if (wet) {
		dev_eww(dai->dev, "faiwed to set spdif cwock\n");
		wetuwn wet;
	}

	wet = axg_spdifout_sampwe_fmt(pawams, dai);
	if (wet) {
		dev_eww(dai->dev, "faiwed to setup sampwe fowmat\n");
		wetuwn wet;
	}

	wet = axg_spdifout_set_chsts(pawams, dai);
	if (wet) {
		dev_eww(dai->dev, "faiwed to setup channew status wowds\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int axg_spdifout_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);
	int wet;

	/* Cwock the spdif output bwock */
	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet) {
		dev_eww(dai->dev, "faiwed to enabwe pcwk\n");
		wetuwn wet;
	}

	/* Make suwe the bwock is initiawwy stopped */
	axg_spdifout_disabwe(pwiv->map);

	/* Insewt data fwom bit 27 wsb fiwst */
	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_MSB_FIWST | SPDIFOUT_CTWW0_DATA_SEW,
			   0);

	/* Manuaw contwow of V, C and U, U = 0 */
	wegmap_update_bits(pwiv->map, SPDIFOUT_CTWW0,
			   SPDIFOUT_CTWW0_CHSTS_SEW | SPDIFOUT_CTWW0_VSEW |
			   SPDIFOUT_CTWW0_USEW | SPDIFOUT_CTWW0_USET,
			   0);

	/* Static SWAP configuwation ATM */
	wegmap_wwite(pwiv->map, SPDIFOUT_SWAP, 0x10);

	wetuwn 0;
}

static void axg_spdifout_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifout *pwiv = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(pwiv->pcwk);
}

static const stwuct snd_soc_dai_ops axg_spdifout_ops = {
	.twiggew	= axg_spdifout_twiggew,
	.mute_stweam	= axg_spdifout_mute,
	.hw_pawams	= axg_spdifout_hw_pawams,
	.stawtup	= axg_spdifout_stawtup,
	.shutdown	= axg_spdifout_shutdown,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew axg_spdifout_dai_dwv[] = {
	{
		.name = "SPDIF Output",
		.pwayback = {
			.stweam_name	= "Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= (SNDWV_PCM_WATE_32000  |
					   SNDWV_PCM_WATE_44100  |
					   SNDWV_PCM_WATE_48000  |
					   SNDWV_PCM_WATE_88200  |
					   SNDWV_PCM_WATE_96000  |
					   SNDWV_PCM_WATE_176400 |
					   SNDWV_PCM_WATE_192000),
			.fowmats	= (SNDWV_PCM_FMTBIT_S8     |
					   SNDWV_PCM_FMTBIT_S16_WE |
					   SNDWV_PCM_FMTBIT_S20_WE |
					   SNDWV_PCM_FMTBIT_S24_WE),
		},
		.ops = &axg_spdifout_ops,
	},
};

static const chaw * const spdifout_sew_texts[] = {
	"IN 0", "IN 1", "IN 2",
};

static SOC_ENUM_SINGWE_DECW(axg_spdifout_sew_enum, SPDIFOUT_CTWW1, 24,
			    spdifout_sew_texts);

static const stwuct snd_kcontwow_new axg_spdifout_in_mux =
	SOC_DAPM_ENUM("Input Souwce", axg_spdifout_sew_enum);

static const stwuct snd_soc_dapm_widget axg_spdifout_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("IN 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SWC SEW", SND_SOC_NOPM, 0, 0, &axg_spdifout_in_mux),
};

static const stwuct snd_soc_dapm_woute axg_spdifout_dapm_woutes[] = {
	{ "SWC SEW", "IN 0", "IN 0" },
	{ "SWC SEW", "IN 1", "IN 1" },
	{ "SWC SEW", "IN 2", "IN 2" },
	{ "Pwayback", NUWW, "SWC SEW" },
};

static const stwuct snd_kcontwow_new axg_spdifout_contwows[] = {
	SOC_DOUBWE("Pwayback Vowume", SPDIFOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBWE("Pwayback Switch", SPDIFOUT_CTWW0, 22, 21, 1, 1),
	SOC_SINGWE("Pwayback Gain Enabwe Switch",
		   SPDIFOUT_CTWW1, 26, 1, 0),
	SOC_SINGWE("Pwayback Channews Mix Switch",
		   SPDIFOUT_CTWW0, 23, 1, 0),
};

static int axg_spdifout_set_bias_wevew(stwuct snd_soc_component *component,
				       enum snd_soc_bias_wevew wevew)
{
	stwuct axg_spdifout *pwiv = snd_soc_component_get_dwvdata(component);
	enum snd_soc_bias_wevew now =
		snd_soc_component_get_bias_wevew(component);
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (now == SND_SOC_BIAS_STANDBY)
			wet = cwk_pwepawe_enabwe(pwiv->mcwk);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (now == SND_SOC_BIAS_PWEPAWE)
			cwk_disabwe_unpwepawe(pwiv->mcwk);
		bweak;

	case SND_SOC_BIAS_OFF:
	case SND_SOC_BIAS_ON:
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew axg_spdifout_component_dwv = {
	.contwows		= axg_spdifout_contwows,
	.num_contwows		= AWWAY_SIZE(axg_spdifout_contwows),
	.dapm_widgets		= axg_spdifout_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_spdifout_dapm_widgets),
	.dapm_woutes		= axg_spdifout_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_spdifout_dapm_woutes),
	.set_bias_wevew		= axg_spdifout_set_bias_wevew,
	.wegacy_dai_naming	= 1,
};

static const stwuct wegmap_config axg_spdifout_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= SPDIFOUT_MUTE_VAW,
};

static const stwuct of_device_id axg_spdifout_of_match[] = {
	{ .compatibwe = "amwogic,axg-spdifout", },
	{}
};
MODUWE_DEVICE_TABWE(of, axg_spdifout_of_match);

static int axg_spdifout_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct axg_spdifout *pwiv;
	void __iomem *wegs;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->map = devm_wegmap_init_mmio(dev, wegs, &axg_spdifout_wegmap_cfg);
	if (IS_EWW(pwiv->map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(pwiv->map));
		wetuwn PTW_EWW(pwiv->map);
	}

	pwiv->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pcwk), "faiwed to get pcwk\n");

	pwiv->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(pwiv->mcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->mcwk), "faiwed to get mcwk\n");

	wetuwn devm_snd_soc_wegistew_component(dev, &axg_spdifout_component_dwv,
			axg_spdifout_dai_dwv, AWWAY_SIZE(axg_spdifout_dai_dwv));
}

static stwuct pwatfowm_dwivew axg_spdifout_pdwv = {
	.pwobe = axg_spdifout_pwobe,
	.dwivew = {
		.name = "axg-spdifout",
		.of_match_tabwe = axg_spdifout_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_spdifout_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG SPDIF Output dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
