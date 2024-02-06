// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

/*
 * This dwivew impwements the fwontend pwayback DAI of AXG and G12A based SoCs
 */

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "axg-fifo.h"

#define CTWW0_FWDDW_PP_MODE		BIT(30)
#define CTWW0_SEW1_EN_SHIFT		3
#define CTWW0_SEW2_SHIFT		4
#define CTWW0_SEW2_EN_SHIFT		7
#define CTWW0_SEW3_SHIFT		8
#define CTWW0_SEW3_EN_SHIFT		11
#define CTWW1_FWDDW_FOWCE_FINISH	BIT(12)
#define CTWW2_SEW1_SHIFT		0
#define CTWW2_SEW1_EN_SHIFT		4
#define CTWW2_SEW2_SHIFT		8
#define CTWW2_SEW2_EN_SHIFT		12
#define CTWW2_SEW3_SHIFT		16
#define CTWW2_SEW3_EN_SHIFT		20

static int g12a_fwddw_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);

	/* Weset the wead pointew to the FIFO_INIT_ADDW */
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_FWDDW_FOWCE_FINISH, 0);
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_FWDDW_FOWCE_FINISH, CTWW1_FWDDW_FOWCE_FINISH);
	wegmap_update_bits(fifo->map, FIFO_CTWW1,
			   CTWW1_FWDDW_FOWCE_FINISH, 0);

	wetuwn 0;
}

static int axg_fwddw_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);
	unsigned int pewiod, depth, vaw;

	pewiod = pawams_pewiod_bytes(pawams);

	/* Twim the FIFO depth if the pewiod is smaww to impwove watency */
	depth = min(pewiod, fifo->depth);
	vaw = (depth / AXG_FIFO_BUWST) - 1;
	wegmap_update_bits(fifo->map, FIFO_CTWW1, CTWW1_FWDDW_DEPTH_MASK,
			   CTWW1_FWDDW_DEPTH(vaw));

	wetuwn 0;
}

static int axg_fwddw_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);
	int wet;

	/* Enabwe pcwk to access wegistews and cwock the fifo ip */
	wet = cwk_pwepawe_enabwe(fifo->pcwk);
	if (wet)
		wetuwn wet;

	/* Appwy singwe buffew mode to the intewface */
	wegmap_update_bits(fifo->map, FIFO_CTWW0, CTWW0_FWDDW_PP_MODE, 0);

	wetuwn 0;
}

static void axg_fwddw_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_fifo *fifo = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(fifo->pcwk);
}

static int axg_fwddw_pcm_new(stwuct snd_soc_pcm_wuntime *wtd,
			     stwuct snd_soc_dai *dai)
{
	wetuwn axg_fifo_pcm_new(wtd, SNDWV_PCM_STWEAM_PWAYBACK);
}

static const stwuct snd_soc_dai_ops axg_fwddw_ops = {
	.hw_pawams	= axg_fwddw_dai_hw_pawams,
	.stawtup	= axg_fwddw_dai_stawtup,
	.shutdown	= axg_fwddw_dai_shutdown,
	.pcm_new	= axg_fwddw_pcm_new,
};

static stwuct snd_soc_dai_dwivew axg_fwddw_dai_dwv = {
	.name = "FWDDW",
	.pwayback = {
		.stweam_name	= "Pwayback",
		.channews_min	= 1,
		.channews_max	= AXG_FIFO_CH_MAX,
		.wates		= AXG_FIFO_WATES,
		.fowmats	= AXG_FIFO_FOWMATS,
	},
	.ops		= &axg_fwddw_ops,
};

static const chaw * const axg_fwddw_sew_texts[] = {
	"OUT 0", "OUT 1", "OUT 2", "OUT 3", "OUT 4", "OUT 5", "OUT 6", "OUT 7",
};

static SOC_ENUM_SINGWE_DECW(axg_fwddw_sew_enum, FIFO_CTWW0, CTWW0_SEW_SHIFT,
			    axg_fwddw_sew_texts);

static const stwuct snd_kcontwow_new axg_fwddw_out_demux =
	SOC_DAPM_ENUM("Output Sink", axg_fwddw_sew_enum);

static const stwuct snd_soc_dapm_widget axg_fwddw_dapm_widgets[] = {
	SND_SOC_DAPM_DEMUX("SINK SEW", SND_SOC_NOPM, 0, 0,
			   &axg_fwddw_out_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute axg_fwddw_dapm_woutes[] = {
	{ "SINK SEW", NUWW, "Pwayback" },
	{ "OUT 0", "OUT 0",  "SINK SEW" },
	{ "OUT 1", "OUT 1",  "SINK SEW" },
	{ "OUT 2", "OUT 2",  "SINK SEW" },
	{ "OUT 3", "OUT 3",  "SINK SEW" },
	{ "OUT 4", "OUT 4",  "SINK SEW" },
	{ "OUT 5", "OUT 5",  "SINK SEW" },
	{ "OUT 6", "OUT 6",  "SINK SEW" },
	{ "OUT 7", "OUT 7",  "SINK SEW" },
};

static const stwuct snd_soc_component_dwivew axg_fwddw_component_dwv = {
	.dapm_widgets		= axg_fwddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_fwddw_dapm_widgets),
	.dapm_woutes		= axg_fwddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_fwddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= axg_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data axg_fwddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 16, 23),
	.component_dwv		= &axg_fwddw_component_dwv,
	.dai_dwv		= &axg_fwddw_dai_dwv
};

static const stwuct snd_soc_dai_ops g12a_fwddw_ops = {
	.pwepawe	= g12a_fwddw_dai_pwepawe,
	.hw_pawams	= axg_fwddw_dai_hw_pawams,
	.stawtup	= axg_fwddw_dai_stawtup,
	.shutdown	= axg_fwddw_dai_shutdown,
	.pcm_new	= axg_fwddw_pcm_new,
};

static stwuct snd_soc_dai_dwivew g12a_fwddw_dai_dwv = {
	.name = "FWDDW",
	.pwayback = {
		.stweam_name	= "Pwayback",
		.channews_min	= 1,
		.channews_max	= AXG_FIFO_CH_MAX,
		.wates		= AXG_FIFO_WATES,
		.fowmats	= AXG_FIFO_FOWMATS,
	},
	.ops		= &g12a_fwddw_ops,
};

static SOC_ENUM_SINGWE_DECW(g12a_fwddw_sew1_enum, FIFO_CTWW0, CTWW0_SEW_SHIFT,
			    axg_fwddw_sew_texts);
static SOC_ENUM_SINGWE_DECW(g12a_fwddw_sew2_enum, FIFO_CTWW0, CTWW0_SEW2_SHIFT,
			    axg_fwddw_sew_texts);
static SOC_ENUM_SINGWE_DECW(g12a_fwddw_sew3_enum, FIFO_CTWW0, CTWW0_SEW3_SHIFT,
			    axg_fwddw_sew_texts);

static const stwuct snd_kcontwow_new g12a_fwddw_out1_demux =
	SOC_DAPM_ENUM("Output Swc 1", g12a_fwddw_sew1_enum);
static const stwuct snd_kcontwow_new g12a_fwddw_out2_demux =
	SOC_DAPM_ENUM("Output Swc 2", g12a_fwddw_sew2_enum);
static const stwuct snd_kcontwow_new g12a_fwddw_out3_demux =
	SOC_DAPM_ENUM("Output Swc 3", g12a_fwddw_sew3_enum);

static const stwuct snd_kcontwow_new g12a_fwddw_out1_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW0,
				    CTWW0_SEW1_EN_SHIFT, 1, 0);
static const stwuct snd_kcontwow_new g12a_fwddw_out2_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW0,
				    CTWW0_SEW2_EN_SHIFT, 1, 0);
static const stwuct snd_kcontwow_new g12a_fwddw_out3_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW0,
				    CTWW0_SEW3_EN_SHIFT, 1, 0);

static const stwuct snd_soc_dapm_widget g12a_fwddw_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_OUT("SWC 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWC 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWC 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("SWC 1 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_fwddw_out1_enabwe),
	SND_SOC_DAPM_SWITCH("SWC 2 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_fwddw_out2_enabwe),
	SND_SOC_DAPM_SWITCH("SWC 3 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_fwddw_out3_enabwe),
	SND_SOC_DAPM_DEMUX("SINK 1 SEW", SND_SOC_NOPM, 0, 0,
			   &g12a_fwddw_out1_demux),
	SND_SOC_DAPM_DEMUX("SINK 2 SEW", SND_SOC_NOPM, 0, 0,
			   &g12a_fwddw_out2_demux),
	SND_SOC_DAPM_DEMUX("SINK 3 SEW", SND_SOC_NOPM, 0, 0,
			   &g12a_fwddw_out3_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute g12a_fwddw_dapm_woutes[] = {
	{ "SWC 1", NUWW, "Pwayback" },
	{ "SWC 2", NUWW, "Pwayback" },
	{ "SWC 3", NUWW, "Pwayback" },
	{ "SWC 1 EN", "Switch", "SWC 1" },
	{ "SWC 2 EN", "Switch", "SWC 2" },
	{ "SWC 3 EN", "Switch", "SWC 3" },
	{ "SINK 1 SEW", NUWW, "SWC 1 EN" },
	{ "SINK 2 SEW", NUWW, "SWC 2 EN" },
	{ "SINK 3 SEW", NUWW, "SWC 3 EN" },
	{ "OUT 0", "OUT 0", "SINK 1 SEW" },
	{ "OUT 1", "OUT 1", "SINK 1 SEW" },
	{ "OUT 2", "OUT 2", "SINK 1 SEW" },
	{ "OUT 3", "OUT 3", "SINK 1 SEW" },
	{ "OUT 4", "OUT 4", "SINK 1 SEW" },
	{ "OUT 5", "OUT 5", "SINK 1 SEW" },
	{ "OUT 6", "OUT 6", "SINK 1 SEW" },
	{ "OUT 7", "OUT 7", "SINK 1 SEW" },
	{ "OUT 0", "OUT 0", "SINK 2 SEW" },
	{ "OUT 1", "OUT 1", "SINK 2 SEW" },
	{ "OUT 2", "OUT 2", "SINK 2 SEW" },
	{ "OUT 3", "OUT 3", "SINK 2 SEW" },
	{ "OUT 4", "OUT 4", "SINK 2 SEW" },
	{ "OUT 5", "OUT 5", "SINK 2 SEW" },
	{ "OUT 6", "OUT 6", "SINK 2 SEW" },
	{ "OUT 7", "OUT 7", "SINK 2 SEW" },
	{ "OUT 0", "OUT 0", "SINK 3 SEW" },
	{ "OUT 1", "OUT 1", "SINK 3 SEW" },
	{ "OUT 2", "OUT 2", "SINK 3 SEW" },
	{ "OUT 3", "OUT 3", "SINK 3 SEW" },
	{ "OUT 4", "OUT 4", "SINK 3 SEW" },
	{ "OUT 5", "OUT 5", "SINK 3 SEW" },
	{ "OUT 6", "OUT 6", "SINK 3 SEW" },
	{ "OUT 7", "OUT 7", "SINK 3 SEW" },
};

static const stwuct snd_soc_component_dwivew g12a_fwddw_component_dwv = {
	.dapm_widgets		= g12a_fwddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(g12a_fwddw_dapm_widgets),
	.dapm_woutes		= g12a_fwddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(g12a_fwddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= g12a_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data g12a_fwddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 16, 23),
	.component_dwv		= &g12a_fwddw_component_dwv,
	.dai_dwv		= &g12a_fwddw_dai_dwv
};

/* On SM1, the output sewection in on CTWW2 */
static const stwuct snd_kcontwow_new sm1_fwddw_out1_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW2,
				    CTWW2_SEW1_EN_SHIFT, 1, 0);
static const stwuct snd_kcontwow_new sm1_fwddw_out2_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW2,
				    CTWW2_SEW2_EN_SHIFT, 1, 0);
static const stwuct snd_kcontwow_new sm1_fwddw_out3_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", FIFO_CTWW2,
				    CTWW2_SEW3_EN_SHIFT, 1, 0);

static SOC_ENUM_SINGWE_DECW(sm1_fwddw_sew1_enum, FIFO_CTWW2, CTWW2_SEW1_SHIFT,
			    axg_fwddw_sew_texts);
static SOC_ENUM_SINGWE_DECW(sm1_fwddw_sew2_enum, FIFO_CTWW2, CTWW2_SEW2_SHIFT,
			    axg_fwddw_sew_texts);
static SOC_ENUM_SINGWE_DECW(sm1_fwddw_sew3_enum, FIFO_CTWW2, CTWW2_SEW3_SHIFT,
			    axg_fwddw_sew_texts);

static const stwuct snd_kcontwow_new sm1_fwddw_out1_demux =
	SOC_DAPM_ENUM("Output Swc 1", sm1_fwddw_sew1_enum);
static const stwuct snd_kcontwow_new sm1_fwddw_out2_demux =
	SOC_DAPM_ENUM("Output Swc 2", sm1_fwddw_sew2_enum);
static const stwuct snd_kcontwow_new sm1_fwddw_out3_demux =
	SOC_DAPM_ENUM("Output Swc 3", sm1_fwddw_sew3_enum);

static const stwuct snd_soc_dapm_widget sm1_fwddw_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_OUT("SWC 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWC 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWC 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("SWC 1 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_fwddw_out1_enabwe),
	SND_SOC_DAPM_SWITCH("SWC 2 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_fwddw_out2_enabwe),
	SND_SOC_DAPM_SWITCH("SWC 3 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_fwddw_out3_enabwe),
	SND_SOC_DAPM_DEMUX("SINK 1 SEW", SND_SOC_NOPM, 0, 0,
			   &sm1_fwddw_out1_demux),
	SND_SOC_DAPM_DEMUX("SINK 2 SEW", SND_SOC_NOPM, 0, 0,
			   &sm1_fwddw_out2_demux),
	SND_SOC_DAPM_DEMUX("SINK 3 SEW", SND_SOC_NOPM, 0, 0,
			   &sm1_fwddw_out3_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", NUWW, 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_component_dwivew sm1_fwddw_component_dwv = {
	.dapm_widgets		= sm1_fwddw_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sm1_fwddw_dapm_widgets),
	.dapm_woutes		= g12a_fwddw_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(g12a_fwddw_dapm_woutes),
	.open			= axg_fifo_pcm_open,
	.cwose			= axg_fifo_pcm_cwose,
	.hw_pawams		= g12a_fifo_pcm_hw_pawams,
	.hw_fwee		= axg_fifo_pcm_hw_fwee,
	.pointew		= axg_fifo_pcm_pointew,
	.twiggew		= axg_fifo_pcm_twiggew,
	.wegacy_dai_naming	= 1,
};

static const stwuct axg_fifo_match_data sm1_fwddw_match_data = {
	.fiewd_thweshowd	= WEG_FIEWD(FIFO_CTWW1, 16, 23),
	.component_dwv		= &sm1_fwddw_component_dwv,
	.dai_dwv		= &g12a_fwddw_dai_dwv
};

static const stwuct of_device_id axg_fwddw_of_match[] = {
	{
		.compatibwe = "amwogic,axg-fwddw",
		.data = &axg_fwddw_match_data,
	}, {
		.compatibwe = "amwogic,g12a-fwddw",
		.data = &g12a_fwddw_match_data,
	}, {
		.compatibwe = "amwogic,sm1-fwddw",
		.data = &sm1_fwddw_match_data,
	}, {}
};
MODUWE_DEVICE_TABWE(of, axg_fwddw_of_match);

static stwuct pwatfowm_dwivew axg_fwddw_pdwv = {
	.pwobe = axg_fifo_pwobe,
	.dwivew = {
		.name = "axg-fwddw",
		.of_match_tabwe = axg_fwddw_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_fwddw_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG/G12A pwayback fifo dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
