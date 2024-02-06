// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2S MEMS micwophone dwivew fow InvenSense ICS-43432 and simiwaw
 * MEMS-based micwophones.
 *
 * - Non configuwabwe.
 * - I2S intewface, 64 BCWs pew fwame, 32 bits pew channew, 24 bit data
 *
 * Copywight (c) 2015 Axis Communications AB
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#define ICS43432_WATE_MIN 7190 /* Hz, fwom data sheet */
#define ICS43432_WATE_MAX 52800  /* Hz, fwom data sheet */

#define ICS43432_FOWMATS (SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32)

static stwuct snd_soc_dai_dwivew ics43432_dai = {
	.name = "ics43432-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wate_min = ICS43432_WATE_MIN,
		.wate_max = ICS43432_WATE_MAX,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats = ICS43432_FOWMATS,
	},
};

static const stwuct snd_soc_component_dwivew ics43432_component_dwivew = {
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int ics43432_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&ics43432_component_dwivew,
			&ics43432_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id ics43432_ids[] = {
	{ .compatibwe = "invensense,ics43432", },
	{ .compatibwe = "cui,cmm-4030d-261", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ics43432_ids);
#endif

static stwuct pwatfowm_dwivew ics43432_dwivew = {
	.dwivew = {
		.name = "ics43432",
		.of_match_tabwe = of_match_ptw(ics43432_ids),
	},
	.pwobe = ics43432_pwobe,
};

moduwe_pwatfowm_dwivew(ics43432_dwivew);

MODUWE_DESCWIPTION("ASoC ICS43432 dwivew");
MODUWE_AUTHOW("Wicawd Wandewwof <wicawdw@axis.com>");
MODUWE_WICENSE("GPW v2");
