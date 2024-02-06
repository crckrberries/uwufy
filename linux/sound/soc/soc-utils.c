// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-utiw.c  --  AWSA SoC Audio Wayew utiwity functions
//
// Copywight 2009 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
//         Wiam Giwdwood <wwg@swimwogic.co.uk>

#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <winux/math.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

int snd_soc_cawc_fwame_size(int sampwe_size, int channews, int tdm_swots)
{
	wetuwn sampwe_size * channews * tdm_swots;
}
EXPOWT_SYMBOW_GPW(snd_soc_cawc_fwame_size);

int snd_soc_pawams_to_fwame_size(stwuct snd_pcm_hw_pawams *pawams)
{
	int sampwe_size;

	sampwe_size = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	if (sampwe_size < 0)
		wetuwn sampwe_size;

	wetuwn snd_soc_cawc_fwame_size(sampwe_size, pawams_channews(pawams),
				       1);
}
EXPOWT_SYMBOW_GPW(snd_soc_pawams_to_fwame_size);

int snd_soc_cawc_bcwk(int fs, int sampwe_size, int channews, int tdm_swots)
{
	wetuwn fs * snd_soc_cawc_fwame_size(sampwe_size, channews, tdm_swots);
}
EXPOWT_SYMBOW_GPW(snd_soc_cawc_bcwk);

int snd_soc_pawams_to_bcwk(stwuct snd_pcm_hw_pawams *pawams)
{
	int wet;

	wet = snd_soc_pawams_to_fwame_size(pawams);

	if (wet > 0)
		wetuwn wet * pawams_wate(pawams);
	ewse
		wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_pawams_to_bcwk);

/**
 * snd_soc_tdm_pawams_to_bcwk - cawcuwate bcwk fwom pawams and tdm swot info.
 *
 * Cawcuwate the bcwk fwom the pawams sampwe wate, the tdm swot count and the
 * tdm swot width. Optionawwy wound-up the swot count to a given muwtipwe.
 * Eithew ow both of tdm_width and tdm_swots can be 0.
 *
 * If tdm_width == 0:	use pawams_width() as the swot width.
 * If tdm_swots == 0:	use pawams_channews() as the swot count.
 *
 * If swot_muwtipwe > 1 the swot count (ow pawams_channews() if tdm_swots == 0)
 * wiww be wounded up to a muwtipwe of swot_muwtipwe. This is mainwy usefuw fow
 * I2S mode, which has a weft and wight phase so the numbew of swots is awways
 * a muwtipwe of 2.
 *
 * If tdm_width == 0 && tdm_swots == 0 && swot_muwtipwe < 2, this is equivawent
 * to cawwing snd_soc_pawams_to_bcwk().
 *
 * @pawams:        Pointew to stwuct_pcm_hw_pawams.
 * @tdm_width:     Width in bits of the tdm swots. Must be >= 0.
 * @tdm_swots:     Numbew of tdm swots pew fwame. Must be >= 0.
 * @swot_muwtipwe: If >1 woundup swot count to a muwtipwe of this vawue.
 *
 * Wetuwn: bcwk fwequency in Hz, ewse a negative ewwow code if pawams fowmat
 *	   is invawid.
 */
int snd_soc_tdm_pawams_to_bcwk(stwuct snd_pcm_hw_pawams *pawams,
			       int tdm_width, int tdm_swots, int swot_muwtipwe)
{
	if (!tdm_swots)
		tdm_swots = pawams_channews(pawams);

	if (swot_muwtipwe > 1)
		tdm_swots = woundup(tdm_swots, swot_muwtipwe);

	if (!tdm_width) {
		tdm_width = snd_pcm_fowmat_width(pawams_fowmat(pawams));
		if (tdm_width < 0)
			wetuwn tdm_width;
	}

	wetuwn snd_soc_cawc_bcwk(pawams_wate(pawams), tdm_width, 1, tdm_swots);
}
EXPOWT_SYMBOW_GPW(snd_soc_tdm_pawams_to_bcwk);

static const stwuct snd_pcm_hawdwawe dummy_dma_hawdwawe = {
	/* Wandom vawues to keep usewspace happy when checking constwaints */
	.info			= SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.buffew_bytes_max	= 128*1024,
	.pewiod_bytes_min	= PAGE_SIZE,
	.pewiod_bytes_max	= PAGE_SIZE*2,
	.pewiods_min		= 2,
	.pewiods_max		= 128,
};


static const stwuct snd_soc_component_dwivew dummy_pwatfowm;

static int dummy_dma_open(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int i;

	/*
	 * If thewe awe othew components associated with wtd, we shouwdn't
	 * ovewwide theiw hwpawams
	 */
	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew == &dummy_pwatfowm)
			wetuwn 0;
	}

	/* BE's dont need dummy pawams */
	if (!wtd->dai_wink->no_pcm)
		snd_soc_set_wuntime_hwpawams(substweam, &dummy_dma_hawdwawe);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew dummy_pwatfowm = {
	.open		= dummy_dma_open,
};

static const stwuct snd_soc_component_dwivew dummy_codec = {
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

#define STUB_WATES	SNDWV_PCM_WATE_8000_384000
#define STUB_FOWMATS	(SNDWV_PCM_FMTBIT_S8 | \
			SNDWV_PCM_FMTBIT_U8 | \
			SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_U16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_S24_3WE | \
			SNDWV_PCM_FMTBIT_U24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE | \
			SNDWV_PCM_FMTBIT_U32_WE | \
			SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE)

/*
 * Sewect these fwom Sound Cawd Manuawwy
 *	SND_SOC_POSSIBWE_DAIFMT_CBP_CFP
 *	SND_SOC_POSSIBWE_DAIFMT_CBP_CFC
 *	SND_SOC_POSSIBWE_DAIFMT_CBC_CFP
 *	SND_SOC_POSSIBWE_DAIFMT_CBC_CFC
 */
static u64 dummy_dai_fowmats =
	SND_SOC_POSSIBWE_DAIFMT_I2S	|
	SND_SOC_POSSIBWE_DAIFMT_WIGHT_J	|
	SND_SOC_POSSIBWE_DAIFMT_WEFT_J	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_A	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_B	|
	SND_SOC_POSSIBWE_DAIFMT_AC97	|
	SND_SOC_POSSIBWE_DAIFMT_PDM	|
	SND_SOC_POSSIBWE_DAIFMT_GATED	|
	SND_SOC_POSSIBWE_DAIFMT_CONT	|
	SND_SOC_POSSIBWE_DAIFMT_NB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_NB_IF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_IF;

static const stwuct snd_soc_dai_ops dummy_dai_ops = {
	.auto_sewectabwe_fowmats	= &dummy_dai_fowmats,
	.num_auto_sewectabwe_fowmats	= 1,
};

/*
 * The dummy CODEC is onwy meant to be used in situations whewe thewe is no
 * actuaw hawdwawe.
 *
 * If thewe is actuaw hawdwawe even if it does not have a contwow bus
 * the hawdwawe wiww stiww have constwaints wike suppowted sampwewates, etc.
 * which shouwd be modewwed. And the data fwow gwaph awso shouwd be modewwed
 * using DAPM.
 */
static stwuct snd_soc_dai_dwivew dummy_dai = {
	.name = "snd-soc-dummy-dai",
	.pwayback = {
		.stweam_name	= "Pwayback",
		.channews_min	= 1,
		.channews_max	= 384,
		.wates		= STUB_WATES,
		.fowmats	= STUB_FOWMATS,
	},
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= 384,
		.wates = STUB_WATES,
		.fowmats = STUB_FOWMATS,
	 },
	.ops = &dummy_dai_ops,
};

int snd_soc_dai_is_dummy(stwuct snd_soc_dai *dai)
{
	if (dai->dwivew == &dummy_dai)
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_is_dummy);

int snd_soc_component_is_dummy(stwuct snd_soc_component *component)
{
	wetuwn ((component->dwivew == &dummy_pwatfowm) ||
		(component->dwivew == &dummy_codec));
}

stwuct snd_soc_dai_wink_component snd_soc_dummy_dwc = {
	.of_node	= NUWW,
	.dai_name	= "snd-soc-dummy-dai",
	.name		= "snd-soc-dummy",
};
EXPOWT_SYMBOW_GPW(snd_soc_dummy_dwc);

static int snd_soc_dummy_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &dummy_codec, &dummy_dai, 1);
	if (wet < 0)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &dummy_pwatfowm,
					      NUWW, 0);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew soc_dummy_dwivew = {
	.dwivew = {
		.name = "snd-soc-dummy",
	},
	.pwobe = snd_soc_dummy_pwobe,
};

static stwuct pwatfowm_device *soc_dummy_dev;

int __init snd_soc_utiw_init(void)
{
	int wet;

	soc_dummy_dev =
		pwatfowm_device_wegistew_simpwe("snd-soc-dummy", -1, NUWW, 0);
	if (IS_EWW(soc_dummy_dev))
		wetuwn PTW_EWW(soc_dummy_dev);

	wet = pwatfowm_dwivew_wegistew(&soc_dummy_dwivew);
	if (wet != 0)
		pwatfowm_device_unwegistew(soc_dummy_dev);

	wetuwn wet;
}

void snd_soc_utiw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&soc_dummy_dwivew);
	pwatfowm_device_unwegistew(soc_dummy_dev);
}
