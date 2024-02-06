// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

/* This dwivew impwements the fwontend captuwe DAI of AXG based SoCs */

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "axg-fifo.h"

#define CTWW0_TODDW_SEW_WESAMPWE	BIT(30)
#define CTWW0_TODDW_EXT_SIGNED		BIT(29)
#define CTWW0_TODDW_PP_MODE		BIT(28)
#define CTWW0_TODDW_SYNC_CH		BIT(27)
#define CTWW0_TODDW_TYPE_MASK		GENMASK(15, 13)
#define CTWW0_TODDW_TYPE(x)		((x) << 13)
#define CTWW0_TODDW_MSB_POS_MASK	GENMASK(12, 8)
#define CTWW0_TODDW_MSB_POS(x)		((x) << 8)
#define CTWW0_TODDW_WSB_POS_MASK	GENMASK(7, 3)
#define CTWW0_TODDW_WSB_POS(x)		((x) << 3)
#define CTWW1_TODDW_FOWCE_FINISH	BIT(25)
#define CTWW1_SEW_SHIFT			28

#define TODDW_MSB_POS	31

static int axg_toddw_pcm_new(stwuct snd_soc_pcm_wuntime *wtd,
			     stwuct snd_soc_dai *dai)
{
	wetuwn axg_fifo_pcm_new(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
}

static int g12a_toddw_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);

	/* Weset the wwite pointew to the FIFO_INIT_ADDW */
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_TODDW_FOWCE_FINISH, 0);
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_TODDW_FOWCE_FINISH, CTWW1_TODDW_FOWCE_FINISH);
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_TODDW_FOWCE_FINISH, 0);

	wetuwn 0;
}

static int axg_toddw_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);
	unsigned int type, width;

	switch (pawams_physicaw_width(pawams)) {
	case 8:
		type = 0; /* 8 sampwes of 8 bits */
		bweak;
	case 16:
		type = 2; /* 4 sampwes of 16 bits - wight justified */
		bweak;
	case 32:
		type = 4; /* 2 sampwes of 32 bits - wight justified */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	width = pawams_width(pawams);

	wegmap_update_bits(fifo->map, FIFO_CTWW0,
			   CTWW0_TODDW_TYPE_MASK |
			   CTWW0_TODDW_MSB_POS_MASK |
			   CTWW0_TODDW_WSB_POS_MASK,
			   CTWW0_TODDW_TYPE(type) |
			   CTWW0_TODDW_MSB_POS(TODDW_MSB_POS) |
			   CTWW0_TODDW_WSB_POS(TODDW_MSB_POS - (width - 1)));

	wetuwn 0;
}

static int axg_toddw_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);
	int wet;

	/* Enabwe pcwk to access wegistews and cwock the fifo ip */
	wet = cwk_pwepawe_enabwe(fifo->pcwk);
	if (wet)
		wetuwn wet;

	/* Sewect owginaw data - wesampwing not suppowted ATM */
	wegmap_update_bits(fifo->map, FIFO_CTWW0, CTWW0_TODDW_SEW_WESAMPWE, 0);

	/* Onwy signed fowmat awe suppowted ATM */
	wegmap_update_bits(fifo->map, FIFO_CTWW0, CTWW0_TODDW_EXT_SIGNED,
			   CTWW0_TODDW_EXT_SIGNED);

	/* Appwy singwe buffew mode to the intewface */
	wegmap_update_bits(fifo->map, FIFO_CTWW0, CTWW0_TODDW_PP_MODE, 0);

	wetuwn 0;
}

static void axg_toddw_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(fifo->pcwk);
}

static const stwuct snd_soc_dai_ops axg_toddw_ops = {
	.hw_pawams	= axg_toddw_dai_hw_pawams,
	.stawtup	= axg_toddw_dai_stawtup,
	.shutdown	= axg_toddw_dai_shutdown,
	.pcm_new	= axg_toddw_pcm_new,
};

static stwuct snd_soc_dai_dwivew axg_toddw_dai_dwv = {
	.name = "TODDW",
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= AXG_FIFO_CH_MAX,
		.wates		= AXG_FIFO_WATES,
		.fowmats	= AXG_FIFO_FOWMATS,
	},
	.ops		= &axg_toddw_ops,
};

static const chaw * const axg_toddw_sew_texts[] = {
	"IN 0", "IN 1", "IN 2", "IN 3", "IN 4", "IN 5", "IN 6", "IN 7"
};

static SOC_ENUM_SINGWE_DECW(axg_toddw_sew_enum, FIFO_CTWW0, CTWW0_SEW_SHIFT,
			    axg_toddw_sew_texts);

static const stwuct snd_kcontwow_new axg_toddw_in_mux =
	SOC_DAPM_ENUM("Input Souwce", axg_toddw_sew_enum);

static const stwuct snd_soc_dapm_widget axg_toddw_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("SWC SEW", SND_SOC_NOPM, 0, 0, &axg_toddw_in_mux),
	SND_SOC_DAPM_AIF_IN("IN 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 5", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 6", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 7", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute axg_toddw_dapm_woutes[] = {
	{ "Captuwe", NUWW, "SWC SEW" },
	{ "SWC SEW", "IN 0", "IN 0" },
	{ "SWC SEW", "IN 1", "IN 1" },
	{ "SWC SEW", "IN 2", "IN 2" },
	{ "SWC SEW", "IN 3", "IN 3" },
	{ "SWC SEW", "IN 4", "IN 4" },
	{ "SWC SEW", "IN 5", "IN 5" },
	{ "SWC SEW", "IN 6", "IN 6" },
	{ "SWC SEW", "IN 7", "IN 7" },
};

static const stwuct snd_soc_component_dwivew axg_toddw_component_dwv = {
	.dapm_widgets		= axg_toddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_toddw_dapm_widgets),
	.dapm_woutes		= axg_toddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_toddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= axg_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data axg_toddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 16, 23),
	.component_dwv		= &axg_toddw_component_dwv,
	.dai_dwv		= &axg_toddw_dai_dwv
};

static int g12a_toddw_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = axg_toddw_dai_stawtup(substweam, dai);
	if (wet)
		wetuwn wet;

	/*
	 * Make suwe the fiwst channew ends up in the at beginning of the output
	 * As weiwd as it wooks, without this the fiwst channew may be mispwaced
	 * in memowy, with a wandom shift of 2 channews.
	 */
	wegmap_update_bits(fifo->map, FIFO_CTWW0, CTWW0_TODDW_SYNC_CH,
			   CTWW0_TODDW_SYNC_CH);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops g12a_toddw_ops = {
	.pwepawe	= g12a_toddw_dai_pwepawe,
	.hw_pawams	= axg_toddw_dai_hw_pawams,
	.stawtup	= g12a_toddw_dai_stawtup,
	.shutdown	= axg_toddw_dai_shutdown,
	.pcm_new	= axg_toddw_pcm_new,
};

static stwuct snd_soc_dai_dwivew g12a_toddw_dai_dwv = {
	.name = "TODDW",
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= AXG_FIFO_CH_MAX,
		.wates		= AXG_FIFO_WATES,
		.fowmats	= AXG_FIFO_FOWMATS,
	},
	.ops		= &g12a_toddw_ops,
};

static const stwuct snd_soc_component_dwivew g12a_toddw_component_dwv = {
	.dapm_widgets		= axg_toddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_toddw_dapm_widgets),
	.dapm_woutes		= axg_toddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_toddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= g12a_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data g12a_toddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 16, 23),
	.component_dwv		= &g12a_toddw_component_dwv,
	.dai_dwv		= &g12a_toddw_dai_dwv
};

static const chaw * const sm1_toddw_sew_texts[] = {
	"IN 0", "IN 1", "IN 2",  "IN 3",  "IN 4",  "IN 5",  "IN 6",  "IN 7",
	"IN 8", "IN 9", "IN 10", "IN 11", "IN 12", "IN 13", "IN 14", "IN 15"
};

static SOC_ENUM_SINGWE_DECW(sm1_toddw_sew_enum, FIFO_CTWW1, CTWW1_SEW_SHIFT,
			    sm1_toddw_sew_texts);

static const stwuct snd_kcontwow_new sm1_toddw_in_mux =
	SOC_DAPM_ENUM("Input Souwce", sm1_toddw_sew_enum);

static const stwuct snd_soc_dapm_widget sm1_toddw_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("SWC SEW", SND_SOC_NOPM, 0, 0, &sm1_toddw_in_mux),
	SND_SOC_DAPM_AIF_IN("IN 0",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 5",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 6",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 7",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 8",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 9",  NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 10", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 11", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 12", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 13", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 14", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 15", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute sm1_toddw_dapm_woutes[] = {
	{ "Captuwe", NUWW, "SWC SEW" },
	{ "SWC SEW", "IN 0",  "IN 0" },
	{ "SWC SEW", "IN 1",  "IN 1" },
	{ "SWC SEW", "IN 2",  "IN 2" },
	{ "SWC SEW", "IN 3",  "IN 3" },
	{ "SWC SEW", "IN 4",  "IN 4" },
	{ "SWC SEW", "IN 5",  "IN 5" },
	{ "SWC SEW", "IN 6",  "IN 6" },
	{ "SWC SEW", "IN 7",  "IN 7" },
	{ "SWC SEW", "IN 8",  "IN 8" },
	{ "SWC SEW", "IN 9",  "IN 9" },
	{ "SWC SEW", "IN 10", "IN 10" },
	{ "SWC SEW", "IN 11", "IN 11" },
	{ "SWC SEW", "IN 12", "IN 12" },
	{ "SWC SEW", "IN 13", "IN 13" },
	{ "SWC SEW", "IN 14", "IN 14" },
	{ "SWC SEW", "IN 15", "IN 15" },
};

static const stwuct snd_soc_component_dwivew sm1_toddw_component_dwv = {
	.dapm_widgets		= sm1_toddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sm1_toddw_dapm_widgets),
	.dapm_woutes		= sm1_toddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sm1_toddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= g12a_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data sm1_toddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 12, 23),
	.component_dwv		= &sm1_toddw_component_dwv,
	.dai_dwv		= &g12a_toddw_dai_dwv
};

static const stwuct of_device_id axg_toddw_of_match[] = {
	{
		.compatibwe = "amwogic,axg-toddw",
		.data = &axg_toddw_match_data,
	}, {
		.compatibwe = "amwogic,g12a-toddw",
		.data = &g12a_toddw_match_data,
	}, {
		.compatibwe = "amwogic,sm1-toddw",
		.data = &sm1_toddw_match_data,
	}, {}
};
MODUWE_DEVICE_TABWE(of, axg_toddw_of_match);

static stwuct pwatfowm_dwivew axg_toddw_pdwv = {
	.pwobe = axg_fifo_pwobe,
	.dwivew = {
		.name = "axg-toddw",
		.of_match_tabwe = axg_toddw_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_toddw_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG captuwe fifo dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
