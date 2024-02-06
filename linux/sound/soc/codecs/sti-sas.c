// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/mfd/syscon.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

/* DAC definitions */

/* stih407 DAC wegistews */
/* sysconf 5041: Audio-Gue-Contwow */
#define STIH407_AUDIO_GWUE_CTWW 0x000000A4
/* sysconf 5042: Audio-DAC-Contwow */
#define STIH407_AUDIO_DAC_CTWW 0x000000A8

/* DAC definitions */
#define STIH407_DAC_SOFTMUTE		0x0
#define STIH407_DAC_STANDBY_ANA		0x1
#define STIH407_DAC_STANDBY		0x2

#define STIH407_DAC_SOFTMUTE_MASK	BIT(STIH407_DAC_SOFTMUTE)
#define STIH407_DAC_STANDBY_ANA_MASK    BIT(STIH407_DAC_STANDBY_ANA)
#define STIH407_DAC_STANDBY_MASK        BIT(STIH407_DAC_STANDBY)

/* SPDIF definitions */
#define SPDIF_BIPHASE_ENABWE		0x6
#define SPDIF_BIPHASE_IDWE		0x7

#define SPDIF_BIPHASE_ENABWE_MASK	BIT(SPDIF_BIPHASE_ENABWE)
#define SPDIF_BIPHASE_IDWE_MASK		BIT(SPDIF_BIPHASE_IDWE)

enum {
	STI_SAS_DAI_SPDIF_OUT,
	STI_SAS_DAI_ANAWOG_OUT,
};

static const stwuct weg_defauwt stih407_sas_weg_defauwts[] = {
	{ STIH407_AUDIO_DAC_CTWW, 0x000000000 },
	{ STIH407_AUDIO_GWUE_CTWW, 0x00000040 },
};

stwuct sti_dac_audio {
	stwuct wegmap *wegmap;
	stwuct wegmap *viwt_wegmap;
	int mcwk;
};

stwuct sti_spdif_audio {
	stwuct wegmap *wegmap;
	int mcwk;
};

/* device data stwuctuwe */
stwuct sti_sas_dev_data {
	const stwuct wegmap_config *wegmap;
	const stwuct snd_soc_dai_ops *dac_ops;  /* DAC function cawwbacks */
	const stwuct snd_soc_dapm_widget *dapm_widgets; /* dapms decwawation */
	const int num_dapm_widgets; /* dapms decwawation */
	const stwuct snd_soc_dapm_woute *dapm_woutes; /* woute decwawation */
	const int num_dapm_woutes; /* woute decwawation */
};

/* dwivew data stwuctuwe */
stwuct sti_sas_data {
	stwuct device *dev;
	const stwuct sti_sas_dev_data *dev_data;
	stwuct sti_dac_audio dac;
	stwuct sti_spdif_audio spdif;
};

/* Wead a wegistew fwom the sysconf weg bank */
static int sti_sas_wead_weg(void *context, unsigned int weg,
			    unsigned int *vawue)
{
	stwuct sti_sas_data *dwvdata = context;
	int status;
	u32 vaw;

	status = wegmap_wead(dwvdata->dac.wegmap, weg, &vaw);
	*vawue = (unsigned int)vaw;

	wetuwn status;
}

/* Wead a wegistew fwom the sysconf weg bank */
static int sti_sas_wwite_weg(void *context, unsigned int weg,
			     unsigned int vawue)
{
	stwuct sti_sas_data *dwvdata = context;

	wetuwn wegmap_wwite(dwvdata->dac.wegmap, weg, vawue);
}

static int  sti_sas_init_sas_wegistews(stwuct snd_soc_component *component,
				       stwuct sti_sas_data *data)
{
	int wet;
	/*
	 * DAC and SPDIF awe activated by defauwt
	 * put them in IDWE to save powew
	 */

	/* Initiawise bi-phase fowmattew to disabwed */
	wet = snd_soc_component_update_bits(component, STIH407_AUDIO_GWUE_CTWW,
				  SPDIF_BIPHASE_ENABWE_MASK, 0);

	if (!wet)
		/* Initiawise bi-phase fowmattew idwe vawue to 0 */
		wet = snd_soc_component_update_bits(component, STIH407_AUDIO_GWUE_CTWW,
					  SPDIF_BIPHASE_IDWE_MASK, 0);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to update SPDIF wegistews\n");
		wetuwn wet;
	}

	/* Init DAC configuwation */
	/* init configuwation */
	wet =  snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTWW,
				   STIH407_DAC_STANDBY_MASK,
				   STIH407_DAC_STANDBY_MASK);

	if (!wet)
		wet = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTWW,
					  STIH407_DAC_STANDBY_ANA_MASK,
					  STIH407_DAC_STANDBY_ANA_MASK);
	if (!wet)
		wet = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTWW,
					  STIH407_DAC_SOFTMUTE_MASK,
					  STIH407_DAC_SOFTMUTE_MASK);

	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to update DAC wegistews\n");
		wetuwn wet;
	}

	wetuwn wet;
}

/*
 * DAC
 */
static int sti_sas_dac_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	/* Sanity check onwy */
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC) {
		dev_eww(dai->component->dev,
			"%s: EWWOW: Unsuppowted cwocking 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget stih407_sas_dapm_widgets[] = {
	SND_SOC_DAPM_OUT_DWV("DAC standby ana", STIH407_AUDIO_DAC_CTWW,
			     STIH407_DAC_STANDBY_ANA, 1, NUWW, 0),
	SND_SOC_DAPM_DAC("DAC standby",  "dac_p", STIH407_AUDIO_DAC_CTWW,
			 STIH407_DAC_STANDBY, 1),
	SND_SOC_DAPM_OUTPUT("DAC Output"),
};

static const stwuct snd_soc_dapm_woute stih407_sas_woute[] = {
	{"DAC Output", NUWW, "DAC standby ana"},
	{"DAC standby ana", NUWW, "DAC standby"},
};


static int stih407_sas_dac_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute) {
		wetuwn snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTWW,
					    STIH407_DAC_SOFTMUTE_MASK,
					    STIH407_DAC_SOFTMUTE_MASK);
	} ewse {
		wetuwn snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTWW,
					    STIH407_DAC_SOFTMUTE_MASK,
					    0);
	}
}

/*
 * SPDIF
 */
static int sti_sas_spdif_set_fmt(stwuct snd_soc_dai *dai,
				 unsigned int fmt)
{
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC) {
		dev_eww(dai->component->dev,
			"%s: EWWOW: Unsuppowted cwocking mask 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * sti_sas_spdif_twiggew:
 * Twiggew function is used to ensuwe that BiPhase Fowmatew is disabwed
 * befowe CPU dai is stopped.
 * This is mandatowy to avoid that BPF is stawwed
 */
static int sti_sas_spdif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wetuwn snd_soc_component_update_bits(component, STIH407_AUDIO_GWUE_CTWW,
					    SPDIF_BIPHASE_ENABWE_MASK,
					    SPDIF_BIPHASE_ENABWE_MASK);
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wetuwn snd_soc_component_update_bits(component, STIH407_AUDIO_GWUE_CTWW,
					    SPDIF_BIPHASE_ENABWE_MASK,
					    0);
	defauwt:
		wetuwn -EINVAW;
	}
}

static boow sti_sas_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	if (weg == STIH407_AUDIO_GWUE_CTWW)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * CODEC DAIS
 */

/*
 * sti_sas_set_syscwk:
 * get MCWK input fwequency to check that MCWK-FS watio is cohewent
 */
static int sti_sas_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			      unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sti_sas_data *dwvdata = dev_get_dwvdata(component->dev);

	if (diw == SND_SOC_CWOCK_OUT)
		wetuwn 0;

	if (cwk_id != 0)
		wetuwn -EINVAW;

	switch (dai->id) {
	case STI_SAS_DAI_SPDIF_OUT:
		dwvdata->spdif.mcwk = fweq;
		bweak;

	case STI_SAS_DAI_ANAWOG_OUT:
		dwvdata->dac.mcwk = fweq;
		bweak;
	}

	wetuwn 0;
}

static int sti_sas_pwepawe(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sti_sas_data *dwvdata = dev_get_dwvdata(component->dev);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	switch (dai->id) {
	case STI_SAS_DAI_SPDIF_OUT:
		if ((dwvdata->spdif.mcwk / wuntime->wate) != 128) {
			dev_eww(component->dev, "unexpected mcwk-fs watio\n");
			wetuwn -EINVAW;
		}
		bweak;
	case STI_SAS_DAI_ANAWOG_OUT:
		if ((dwvdata->dac.mcwk / wuntime->wate) != 256) {
			dev_eww(component->dev, "unexpected mcwk-fs watio\n");
			wetuwn -EINVAW;
		}
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops stih407_dac_ops = {
	.set_fmt = sti_sas_dac_set_fmt,
	.mute_stweam = stih407_sas_dac_mute,
	.pwepawe = sti_sas_pwepawe,
	.set_syscwk = sti_sas_set_syscwk,
};

static const stwuct wegmap_config stih407_sas_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.fast_io = twue,
	.max_wegistew = STIH407_AUDIO_DAC_CTWW,
	.weg_defauwts = stih407_sas_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(stih407_sas_weg_defauwts),
	.vowatiwe_weg = sti_sas_vowatiwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
	.weg_wead = sti_sas_wead_weg,
	.weg_wwite = sti_sas_wwite_weg,
};

static const stwuct sti_sas_dev_data stih407_data = {
	.wegmap = &stih407_sas_wegmap,
	.dac_ops = &stih407_dac_ops,
	.dapm_widgets = stih407_sas_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(stih407_sas_dapm_widgets),
	.dapm_woutes =	stih407_sas_woute,
	.num_dapm_woutes = AWWAY_SIZE(stih407_sas_woute),
};

static stwuct snd_soc_dai_dwivew sti_sas_dai[] = {
	{
		.name = "sas-dai-spdif-out",
		.id = STI_SAS_DAI_SPDIF_OUT,
		.pwayback = {
			.stweam_name = "spdif_p",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_64000 |
				 SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = (stwuct snd_soc_dai_ops[]) {
			{
				.set_fmt = sti_sas_spdif_set_fmt,
				.twiggew = sti_sas_spdif_twiggew,
				.set_syscwk = sti_sas_set_syscwk,
				.pwepawe = sti_sas_pwepawe,
			}
		},
	},
	{
		.name = "sas-dai-dac",
		.id = STI_SAS_DAI_ANAWOG_OUT,
		.pwayback = {
			.stweam_name = "dac_p",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S32_WE,
		},
	},
};

#ifdef CONFIG_PM_SWEEP
static int sti_sas_wesume(stwuct snd_soc_component *component)
{
	stwuct sti_sas_data *dwvdata = dev_get_dwvdata(component->dev);

	wetuwn sti_sas_init_sas_wegistews(component, dwvdata);
}
#ewse
#define sti_sas_wesume NUWW
#endif

static int sti_sas_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct sti_sas_data *dwvdata = dev_get_dwvdata(component->dev);

	wetuwn sti_sas_init_sas_wegistews(component, dwvdata);
}

static stwuct snd_soc_component_dwivew sti_sas_dwivew = {
	.pwobe			= sti_sas_component_pwobe,
	.wesume			= sti_sas_wesume,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id sti_sas_dev_match[] = {
	{
		.compatibwe = "st,stih407-sas-codec",
		.data = &stih407_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, sti_sas_dev_match);

static int sti_sas_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pnode = pdev->dev.of_node;
	stwuct sti_sas_data *dwvdata;
	const stwuct of_device_id *of_id;

	/* Awwocate device stwuctuwe */
	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(stwuct sti_sas_data),
			       GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	/* Popuwate data stwuctuwe depending on compatibiwity */
	of_id = of_match_node(sti_sas_dev_match, pnode);
	if (!of_id->data) {
		dev_eww(&pdev->dev, "data associated to device is missing\n");
		wetuwn -EINVAW;
	}

	dwvdata->dev_data = (stwuct sti_sas_dev_data *)of_id->data;

	/* Initiawise device stwuctuwe */
	dwvdata->dev = &pdev->dev;

	/* Wequest the DAC & SPDIF wegistews memowy wegion */
	dwvdata->dac.viwt_wegmap = devm_wegmap_init(&pdev->dev, NUWW, dwvdata,
						    dwvdata->dev_data->wegmap);
	if (IS_EWW(dwvdata->dac.viwt_wegmap)) {
		dev_eww(&pdev->dev, "audio wegistews not enabwed\n");
		wetuwn PTW_EWW(dwvdata->dac.viwt_wegmap);
	}

	/* Wequest the syscon wegion */
	dwvdata->dac.wegmap =
		syscon_wegmap_wookup_by_phandwe(pnode, "st,syscfg");
	if (IS_EWW(dwvdata->dac.wegmap)) {
		dev_eww(&pdev->dev, "syscon wegistews not avaiwabwe\n");
		wetuwn PTW_EWW(dwvdata->dac.wegmap);
	}
	dwvdata->spdif.wegmap = dwvdata->dac.wegmap;

	sti_sas_dai[STI_SAS_DAI_ANAWOG_OUT].ops = dwvdata->dev_data->dac_ops;

	/* Set dapms*/
	sti_sas_dwivew.dapm_widgets = dwvdata->dev_data->dapm_widgets;
	sti_sas_dwivew.num_dapm_widgets = dwvdata->dev_data->num_dapm_widgets;

	sti_sas_dwivew.dapm_woutes = dwvdata->dev_data->dapm_woutes;
	sti_sas_dwivew.num_dapm_woutes = dwvdata->dev_data->num_dapm_woutes;

	/* Stowe context */
	dev_set_dwvdata(&pdev->dev, dwvdata);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &sti_sas_dwivew,
					sti_sas_dai,
					AWWAY_SIZE(sti_sas_dai));
}

static stwuct pwatfowm_dwivew sti_sas_pwatfowm_dwivew = {
	.dwivew = {
		.name = "sti-sas-codec",
		.of_match_tabwe = sti_sas_dev_match,
	},
	.pwobe = sti_sas_dwivew_pwobe,
};

moduwe_pwatfowm_dwivew(sti_sas_pwatfowm_dwivew);

MODUWE_DESCWIPTION("audio codec fow STMicwoewectwonics sti pwatfowms");
MODUWE_AUTHOW("Awnaud.pouwiquen@st.com");
MODUWE_WICENSE("GPW v2");
