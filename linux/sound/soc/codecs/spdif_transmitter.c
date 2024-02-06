// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC SPDIF DIT dwivew
 *
 *  This dwivew is used by contwowwews which can opewate in DIT (SPDI/F) whewe
 *  no codec is needed.  This fiwe pwovides stub codec that can be used
 *  in these configuwations. TI DaVinci Audio contwowwew uses this dwivew.
 *
 * Authow:      Steve Chen,  <schen@mvista.com>
 * Copywight:   (C) 2009 MontaVista Softwawe, Inc., <souwce@mvista.com>
 * Copywight:   (C) 2009  Texas Instwuments, India
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <winux/of.h>

#define DWV_NAME "spdif-dit"

#define STUB_WATES	SNDWV_PCM_WATE_8000_192000
#define STUB_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE  | \
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dapm_widget dit_widgets[] = {
	SND_SOC_DAPM_OUTPUT("spdif-out"),
};

static const stwuct snd_soc_dapm_woute dit_woutes[] = {
	{ "spdif-out", NUWW, "Pwayback" },
};

static stwuct snd_soc_component_dwivew soc_codec_spdif_dit = {
	.dapm_widgets		= dit_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(dit_widgets),
	.dapm_woutes		= dit_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(dit_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew dit_stub_dai = {
	.name		= "dit-hifi",
	.pwayback 	= {
		.stweam_name	= "Pwayback",
		.channews_min	= 1,
		.channews_max	= 384,
		.wates		= STUB_WATES,
		.fowmats	= STUB_FOWMATS,
	},
};

static int spdif_dit_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_codec_spdif_dit,
			&dit_stub_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id spdif_dit_dt_ids[] = {
	{ .compatibwe = "winux,spdif-dit", },
	{ }
};
MODUWE_DEVICE_TABWE(of, spdif_dit_dt_ids);
#endif

static stwuct pwatfowm_dwivew spdif_dit_dwivew = {
	.pwobe		= spdif_dit_pwobe,
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = of_match_ptw(spdif_dit_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(spdif_dit_dwivew);

MODUWE_AUTHOW("Steve Chen <schen@mvista.com>");
MODUWE_DESCWIPTION("SPDIF dummy codec dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
