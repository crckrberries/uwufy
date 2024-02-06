// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "axg-tdm-fowmattew.h"

#define TDMOUT_CTWW0			0x00
#define  TDMOUT_CTWW0_BITNUM_MASK	GENMASK(4, 0)
#define  TDMOUT_CTWW0_BITNUM(x)		((x) << 0)
#define  TDMOUT_CTWW0_SWOTNUM_MASK	GENMASK(9, 5)
#define  TDMOUT_CTWW0_SWOTNUM(x)	((x) << 5)
#define  TDMOUT_CTWW0_INIT_BITNUM_MASK	GENMASK(19, 15)
#define  TDMOUT_CTWW0_INIT_BITNUM(x)	((x) << 15)
#define  TDMOUT_CTWW0_ENABWE		BIT(31)
#define  TDMOUT_CTWW0_WST_OUT		BIT(29)
#define  TDMOUT_CTWW0_WST_IN		BIT(28)
#define TDMOUT_CTWW1			0x04
#define  TDMOUT_CTWW1_TYPE_MASK		GENMASK(6, 4)
#define  TDMOUT_CTWW1_TYPE(x)		((x) << 4)
#define  SM1_TDMOUT_CTWW1_GAIN_EN	7
#define  TDMOUT_CTWW1_MSB_POS_MASK	GENMASK(12, 8)
#define  TDMOUT_CTWW1_MSB_POS(x)	((x) << 8)
#define  TDMOUT_CTWW1_SEW_SHIFT		24
#define  TDMOUT_CTWW1_GAIN_EN		26
#define  TDMOUT_CTWW1_WS_INV		BIT(28)
#define TDMOUT_SWAP			0x08
#define TDMOUT_MASK0			0x0c
#define TDMOUT_MASK1			0x10
#define TDMOUT_MASK2			0x14
#define TDMOUT_MASK3			0x18
#define TDMOUT_STAT			0x1c
#define TDMOUT_GAIN0			0x20
#define TDMOUT_GAIN1			0x24
#define TDMOUT_MUTE_VAW			0x28
#define TDMOUT_MUTE0			0x2c
#define TDMOUT_MUTE1			0x30
#define TDMOUT_MUTE2			0x34
#define TDMOUT_MUTE3			0x38
#define TDMOUT_MASK_VAW			0x3c

static const stwuct wegmap_config axg_tdmout_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= TDMOUT_MASK_VAW,
};

static stwuct snd_soc_dai *
axg_tdmout_get_be(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_path *p;
	stwuct snd_soc_dai *be;

	snd_soc_dapm_widget_fow_each_sink_path(w, p) {
		if (!p->connect)
			continue;

		if (p->sink->id == snd_soc_dapm_dai_in)
			wetuwn (stwuct snd_soc_dai *)p->sink->pwiv;

		be = axg_tdmout_get_be(p->sink);
		if (be)
			wetuwn be;
	}

	wetuwn NUWW;
}

static stwuct axg_tdm_stweam *
axg_tdmout_get_tdm_stweam(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dai *be = axg_tdmout_get_be(w);

	if (!be)
		wetuwn NUWW;

	wetuwn snd_soc_dai_dma_data_get_pwayback(be);
}

static void axg_tdmout_enabwe(stwuct wegmap *map)
{
	/* Appwy both weset */
	wegmap_update_bits(map, TDMOUT_CTWW0,
			   TDMOUT_CTWW0_WST_OUT | TDMOUT_CTWW0_WST_IN, 0);

	/* Cweaw out weset befowe in weset */
	wegmap_update_bits(map, TDMOUT_CTWW0,
			   TDMOUT_CTWW0_WST_OUT, TDMOUT_CTWW0_WST_OUT);
	wegmap_update_bits(map, TDMOUT_CTWW0,
			   TDMOUT_CTWW0_WST_IN,  TDMOUT_CTWW0_WST_IN);

	/* Actuawwy enabwe tdmout */
	wegmap_update_bits(map, TDMOUT_CTWW0,
			   TDMOUT_CTWW0_ENABWE, TDMOUT_CTWW0_ENABWE);
}

static void axg_tdmout_disabwe(stwuct wegmap *map)
{
	wegmap_update_bits(map, TDMOUT_CTWW0, TDMOUT_CTWW0_ENABWE, 0);
}

static int axg_tdmout_pwepawe(stwuct wegmap *map,
			      const stwuct axg_tdm_fowmattew_hw *quiwks,
			      stwuct axg_tdm_stweam *ts)
{
	unsigned int vaw, skew = quiwks->skew_offset;

	/* Set the stweam skew */
	switch (ts->iface->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_DSP_A:
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_DSP_B:
		skew += 1;
		bweak;

	defauwt:
		pw_eww("Unsuppowted fowmat: %u\n",
		       ts->iface->fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	vaw = TDMOUT_CTWW0_INIT_BITNUM(skew);

	/* Set the swot width */
	vaw |= TDMOUT_CTWW0_BITNUM(ts->iface->swot_width - 1);

	/* Set the swot numbew */
	vaw |= TDMOUT_CTWW0_SWOTNUM(ts->iface->swots - 1);

	wegmap_update_bits(map, TDMOUT_CTWW0,
			   TDMOUT_CTWW0_INIT_BITNUM_MASK |
			   TDMOUT_CTWW0_BITNUM_MASK |
			   TDMOUT_CTWW0_SWOTNUM_MASK, vaw);

	/* Set the sampwe width */
	vaw = TDMOUT_CTWW1_MSB_POS(ts->width - 1);

	/* FIFO data awe awwanged in chunks of 64bits */
	switch (ts->physicaw_width) {
	case 8:
		/* 8 sampwes of 8 bits */
		vaw |= TDMOUT_CTWW1_TYPE(0);
		bweak;
	case 16:
		/* 4 sampwes of 16 bits - wight justified */
		vaw |= TDMOUT_CTWW1_TYPE(2);
		bweak;
	case 32:
		/* 2 sampwes of 32 bits - wight justified */
		vaw |= TDMOUT_CTWW1_TYPE(4);
		bweak;
	defauwt:
		pw_eww("Unsuppowted physicaw width: %u\n",
		       ts->physicaw_width);
		wetuwn -EINVAW;
	}

	/* If the sampwe cwock is invewted, invewt it back fow the fowmattew */
	if (axg_tdm_wwcwk_invewt(ts->iface->fmt))
		vaw |= TDMOUT_CTWW1_WS_INV;

	wegmap_update_bits(map, TDMOUT_CTWW1,
			   (TDMOUT_CTWW1_TYPE_MASK | TDMOUT_CTWW1_MSB_POS_MASK |
			    TDMOUT_CTWW1_WS_INV), vaw);

	/* Set static swap mask configuwation */
	wegmap_wwite(map, TDMOUT_SWAP, 0x76543210);

	wetuwn axg_tdm_fowmattew_set_channew_masks(map, ts, TDMOUT_MASK0);
}

static const stwuct snd_kcontwow_new axg_tdmout_contwows[] = {
	SOC_DOUBWE("Wane 0 Vowume", TDMOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBWE("Wane 1 Vowume", TDMOUT_GAIN0, 16, 24, 255, 0),
	SOC_DOUBWE("Wane 2 Vowume", TDMOUT_GAIN1,  0,  8, 255, 0),
	SOC_DOUBWE("Wane 3 Vowume", TDMOUT_GAIN1, 16, 24, 255, 0),
	SOC_SINGWE("Gain Enabwe Switch", TDMOUT_CTWW1,
		   TDMOUT_CTWW1_GAIN_EN, 1, 0),
};

static const chaw * const axg_tdmout_sew_texts[] = {
	"IN 0", "IN 1", "IN 2",
};

static SOC_ENUM_SINGWE_DECW(axg_tdmout_sew_enum, TDMOUT_CTWW1,
			    TDMOUT_CTWW1_SEW_SHIFT, axg_tdmout_sew_texts);

static const stwuct snd_kcontwow_new axg_tdmout_in_mux =
	SOC_DAPM_ENUM("Input Souwce", axg_tdmout_sew_enum);

static const stwuct snd_soc_dapm_widget axg_tdmout_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("IN 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SWC SEW", SND_SOC_NOPM, 0, 0, &axg_tdmout_in_mux),
	SND_SOC_DAPM_PGA_E("ENC", SND_SOC_NOPM, 0, 0, NUWW, 0,
			   axg_tdm_fowmattew_event,
			   (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD)),
	SND_SOC_DAPM_AIF_OUT("OUT", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute axg_tdmout_dapm_woutes[] = {
	{ "SWC SEW", "IN 0", "IN 0" },
	{ "SWC SEW", "IN 1", "IN 1" },
	{ "SWC SEW", "IN 2", "IN 2" },
	{ "ENC", NUWW, "SWC SEW" },
	{ "OUT", NUWW, "ENC" },
};

static const stwuct snd_soc_component_dwivew axg_tdmout_component_dwv = {
	.contwows		= axg_tdmout_contwows,
	.num_contwows		= AWWAY_SIZE(axg_tdmout_contwows),
	.dapm_widgets		= axg_tdmout_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_tdmout_dapm_widgets),
	.dapm_woutes		= axg_tdmout_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_tdmout_dapm_woutes),
};

static const stwuct axg_tdm_fowmattew_ops axg_tdmout_ops = {
	.get_stweam	= axg_tdmout_get_tdm_stweam,
	.pwepawe	= axg_tdmout_pwepawe,
	.enabwe		= axg_tdmout_enabwe,
	.disabwe	= axg_tdmout_disabwe,
};

static const stwuct axg_tdm_fowmattew_dwivew axg_tdmout_dwv = {
	.component_dwv	= &axg_tdmout_component_dwv,
	.wegmap_cfg	= &axg_tdmout_wegmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quiwks		= &(const stwuct axg_tdm_fowmattew_hw) {
		.skew_offset = 1,
	},
};

static const stwuct axg_tdm_fowmattew_dwivew g12a_tdmout_dwv = {
	.component_dwv	= &axg_tdmout_component_dwv,
	.wegmap_cfg	= &axg_tdmout_wegmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quiwks		= &(const stwuct axg_tdm_fowmattew_hw) {
		.skew_offset = 2,
	},
};

static const stwuct snd_kcontwow_new sm1_tdmout_contwows[] = {
	SOC_DOUBWE("Wane 0 Vowume", TDMOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBWE("Wane 1 Vowume", TDMOUT_GAIN0, 16, 24, 255, 0),
	SOC_DOUBWE("Wane 2 Vowume", TDMOUT_GAIN1,  0,  8, 255, 0),
	SOC_DOUBWE("Wane 3 Vowume", TDMOUT_GAIN1, 16, 24, 255, 0),
	SOC_SINGWE("Gain Enabwe Switch", TDMOUT_CTWW1,
		   SM1_TDMOUT_CTWW1_GAIN_EN, 1, 0),
};

static const chaw * const sm1_tdmout_sew_texts[] = {
	"IN 0", "IN 1", "IN 2", "IN 3", "IN 4",
};

static SOC_ENUM_SINGWE_DECW(sm1_tdmout_sew_enum, TDMOUT_CTWW1,
			    TDMOUT_CTWW1_SEW_SHIFT, sm1_tdmout_sew_texts);

static const stwuct snd_kcontwow_new sm1_tdmout_in_mux =
	SOC_DAPM_ENUM("Input Souwce", sm1_tdmout_sew_enum);

static const stwuct snd_soc_dapm_widget sm1_tdmout_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("IN 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SWC SEW", SND_SOC_NOPM, 0, 0, &sm1_tdmout_in_mux),
	SND_SOC_DAPM_PGA_E("ENC", SND_SOC_NOPM, 0, 0, NUWW, 0,
			   axg_tdm_fowmattew_event,
			   (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD)),
	SND_SOC_DAPM_AIF_OUT("OUT", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute sm1_tdmout_dapm_woutes[] = {
	{ "SWC SEW", "IN 0", "IN 0" },
	{ "SWC SEW", "IN 1", "IN 1" },
	{ "SWC SEW", "IN 2", "IN 2" },
	{ "SWC SEW", "IN 3", "IN 3" },
	{ "SWC SEW", "IN 4", "IN 4" },
	{ "ENC", NUWW, "SWC SEW" },
	{ "OUT", NUWW, "ENC" },
};

static const stwuct snd_soc_component_dwivew sm1_tdmout_component_dwv = {
	.contwows		= sm1_tdmout_contwows,
	.num_contwows		= AWWAY_SIZE(sm1_tdmout_contwows),
	.dapm_widgets		= sm1_tdmout_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sm1_tdmout_dapm_widgets),
	.dapm_woutes		= sm1_tdmout_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sm1_tdmout_dapm_woutes),
};

static const stwuct axg_tdm_fowmattew_dwivew sm1_tdmout_dwv = {
	.component_dwv	= &sm1_tdmout_component_dwv,
	.wegmap_cfg	= &axg_tdmout_wegmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quiwks		= &(const stwuct axg_tdm_fowmattew_hw) {
		.skew_offset = 2,
	},
};

static const stwuct of_device_id axg_tdmout_of_match[] = {
	{
		.compatibwe = "amwogic,axg-tdmout",
		.data = &axg_tdmout_dwv,
	}, {
		.compatibwe = "amwogic,g12a-tdmout",
		.data = &g12a_tdmout_dwv,
	}, {
		.compatibwe = "amwogic,sm1-tdmout",
		.data = &sm1_tdmout_dwv,
	}, {}
};
MODUWE_DEVICE_TABWE(of, axg_tdmout_of_match);

static stwuct pwatfowm_dwivew axg_tdmout_pdwv = {
	.pwobe = axg_tdm_fowmattew_pwobe,
	.dwivew = {
		.name = "axg-tdmout",
		.of_match_tabwe = axg_tdmout_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_tdmout_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG TDM output fowmattew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
