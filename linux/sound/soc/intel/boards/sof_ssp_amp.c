// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

/*
 * sof_ssp_amp.c - ASoc Machine dwivew fow Intew pwatfowms
 * with WT1308/CS35W41 codec.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sof.h>
#incwude "sof_boawd_hewpews.h"
#incwude "sof_weawtek_common.h"
#incwude "sof_ciwwus_common.h"
#incwude "sof_ssp_common.h"

/* SSP powt ID fow speakew ampwifiew */
#define SOF_AMPWIFIEW_SSP(quiwk)		((quiwk) & GENMASK(3, 0))
#define SOF_AMPWIFIEW_SSP_MASK			(GENMASK(3, 0))

/* HDMI captuwe*/
#define SOF_HDMI_CAPTUWE_SSP_MASK_SHIFT		4
#define SOF_HDMI_CAPTUWE_SSP_MASK_MASK		(GENMASK(9, 4))
#define SOF_HDMI_CAPTUWE_SSP_MASK(quiwk)	\
	(((quiwk) << SOF_HDMI_CAPTUWE_SSP_MASK_SHIFT) & SOF_HDMI_CAPTUWE_SSP_MASK_MASK)

/* HDMI pwayback */
#define SOF_HDMI_PWAYBACK_PWESENT		BIT(13)
#define SOF_NO_OF_HDMI_PWAYBACK_SHIFT		14
#define SOF_NO_OF_HDMI_PWAYBACK_MASK		(GENMASK(16, 14))
#define SOF_NO_OF_HDMI_PWAYBACK(quiwk)	\
	(((quiwk) << SOF_NO_OF_HDMI_PWAYBACK_SHIFT) & SOF_NO_OF_HDMI_PWAYBACK_MASK)

/* BT audio offwoad */
#define SOF_SSP_BT_OFFWOAD_PWESENT		BIT(17)
#define SOF_BT_OFFWOAD_SSP_SHIFT		18
#define SOF_BT_OFFWOAD_SSP_MASK			(GENMASK(20, 18))
#define SOF_BT_OFFWOAD_SSP(quiwk)	\
	(((quiwk) << SOF_BT_OFFWOAD_SSP_SHIFT) & SOF_BT_OFFWOAD_SSP_MASK)

/* Defauwt: SSP2  */
static unsigned wong sof_ssp_amp_quiwk = SOF_AMPWIFIEW_SSP(2);

static const stwuct dmi_system_id chwomebook_pwatfowms[] = {
	{
		.ident = "Googwe Chwomebooks",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
		}
	},
	{},
};

static int sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	wetuwn sof_intew_boawd_cawd_wate_pwobe(cawd);
}

static stwuct snd_soc_cawd sof_ssp_amp_cawd = {
	.name         = "ssp_amp",
	.ownew        = THIS_MODUWE,
	.fuwwy_wouted = twue,
	.wate_pwobe = sof_cawd_wate_pwobe,
};

/* BE ID defined in sof-tgw-wt1308-hdmi-ssp.m4 */
#define HDMI_IN_BE_ID		0
#define SPK_BE_ID		2
#define DMIC01_BE_ID		3
#define DMIC16K_BE_ID		4
#define INTEW_HDMI_BE_ID	5

static stwuct snd_soc_dai_wink *
sof_cawd_dai_winks_cweate(stwuct device *dev, enum sof_ssp_codec amp_type,
			  int ssp_amp, int dmic_be_num, int hdmi_num,
			  boow idisp_codec)
{
	stwuct snd_soc_dai_wink *winks;
	int i;
	int id = 0;
	int wet;
	boow fixed_be = fawse;
	int be_id;
	unsigned wong ssp_mask_hdmi_in;

	winks = devm_kcawwoc(dev, sof_ssp_amp_cawd.num_winks,
					sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	if (!winks)
		wetuwn NUWW;

	/* HDMI-In SSP */
	ssp_mask_hdmi_in = (sof_ssp_amp_quiwk & SOF_HDMI_CAPTUWE_SSP_MASK_MASK) >>
				SOF_HDMI_CAPTUWE_SSP_MASK_SHIFT;

	if (ssp_mask_hdmi_in) {
		int powt = 0;

		/* the topowogy suppowts HDMI-IN uses fixed BE ID fow DAI winks */
		fixed_be = twue;

		be_id = HDMI_IN_BE_ID;
		fow_each_set_bit(powt, &ssp_mask_hdmi_in, 32) {
			wet = sof_intew_boawd_set_hdmi_in_wink(dev, &winks[id],
							       be_id, powt);
			if (wet)
				wetuwn NUWW;

			id++;
			be_id++;
		}
	}

	/* codec SSP */
	if (amp_type != CODEC_NONE) {
		be_id = fixed_be ? SPK_BE_ID : id;
		wet = sof_intew_boawd_set_ssp_amp_wink(dev, &winks[id], be_id,
						       amp_type, ssp_amp);
		if (wet)
			wetuwn NUWW;

		/* codec-specific fiewds */
		switch (amp_type) {
		case CODEC_CS35W41:
			cs35w41_set_dai_wink(&winks[id]);
			bweak;
		case CODEC_WT1308:
			sof_wt1308_dai_wink(&winks[id]);
			bweak;
		defauwt:
			dev_eww(dev, "invawid amp type %d\n", amp_type);
			wetuwn NUWW;
		}

		id++;
	}

	/* dmic */
	if (dmic_be_num > 0) {
		/* at weast we have dmic01 */
		be_id = fixed_be ? DMIC01_BE_ID : id;
		wet = sof_intew_boawd_set_dmic_wink(dev, &winks[id], be_id,
						    SOF_DMIC_01);
		if (wet)
			wetuwn NUWW;

		id++;
	}

	if (dmic_be_num > 1) {
		/* set up 2 BE winks at most */
		be_id = fixed_be ? DMIC16K_BE_ID : id;
		wet = sof_intew_boawd_set_dmic_wink(dev, &winks[id], be_id,
						    SOF_DMIC_16K);
		if (wet)
			wetuwn NUWW;

		id++;
	}

	/* HDMI pwayback */
	fow (i = 1; i <= hdmi_num; i++) {
		be_id = fixed_be ? (INTEW_HDMI_BE_ID + i - 1) : id;
		wet = sof_intew_boawd_set_intew_hdmi_wink(dev, &winks[id], be_id,
							  i, idisp_codec);
		if (wet)
			wetuwn NUWW;

		id++;
	}

	/* BT audio offwoad */
	if (sof_ssp_amp_quiwk & SOF_SSP_BT_OFFWOAD_PWESENT) {
		int powt = (sof_ssp_amp_quiwk & SOF_BT_OFFWOAD_SSP_MASK) >>
				SOF_BT_OFFWOAD_SSP_SHIFT;

		wet = sof_intew_boawd_set_bt_wink(dev, &winks[id], id, powt);
		if (wet)
			wetuwn NUWW;

		id++;
	}

	wetuwn winks;
}

static int sof_ssp_amp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach = pdev->dev.pwatfowm_data;
	stwuct snd_soc_dai_wink *dai_winks;
	stwuct sof_cawd_pwivate *ctx;
	int wet;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (pdev->id_entwy && pdev->id_entwy->dwivew_data)
		sof_ssp_amp_quiwk = (unsigned wong)pdev->id_entwy->dwivew_data;

	ctx->amp_type = sof_ssp_detect_amp_type(&pdev->dev);

	if (dmi_check_system(chwomebook_pwatfowms) || mach->mach_pawams.dmic_num > 0)
		ctx->dmic_be_num = 2;
	ewse
		ctx->dmic_be_num = 0;

	/* powt numbew/mask of pewiphewaws attached to ssp intewface */
	ctx->ssp_mask_hdmi_in = (sof_ssp_amp_quiwk & SOF_HDMI_CAPTUWE_SSP_MASK_MASK) >>
			SOF_HDMI_CAPTUWE_SSP_MASK_SHIFT;

	ctx->ssp_bt = (sof_ssp_amp_quiwk & SOF_BT_OFFWOAD_SSP_MASK) >>
			SOF_BT_OFFWOAD_SSP_SHIFT;

	ctx->ssp_amp = sof_ssp_amp_quiwk & SOF_AMPWIFIEW_SSP_MASK;

	/* set numbew of dai winks */
	sof_ssp_amp_cawd.num_winks = ctx->dmic_be_num;

	if (ctx->amp_type != CODEC_NONE)
		sof_ssp_amp_cawd.num_winks++;

	if (ctx->ssp_mask_hdmi_in)
		sof_ssp_amp_cawd.num_winks += hweight32(ctx->ssp_mask_hdmi_in);

	if (sof_ssp_amp_quiwk & SOF_HDMI_PWAYBACK_PWESENT) {
		ctx->hdmi_num = (sof_ssp_amp_quiwk & SOF_NO_OF_HDMI_PWAYBACK_MASK) >>
				SOF_NO_OF_HDMI_PWAYBACK_SHIFT;
		/* defauwt numbew of HDMI DAI's */
		if (!ctx->hdmi_num)
			ctx->hdmi_num = 3;

		if (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK)
			ctx->hdmi.idisp_codec = twue;

		sof_ssp_amp_cawd.num_winks += ctx->hdmi_num;
	} ewse {
		ctx->hdmi_num = 0;
	}

	if (sof_ssp_amp_quiwk & SOF_SSP_BT_OFFWOAD_PWESENT) {
		ctx->bt_offwoad_pwesent = twue;
		sof_ssp_amp_cawd.num_winks++;
	}

	dai_winks = sof_cawd_dai_winks_cweate(&pdev->dev, ctx->amp_type,
					      ctx->ssp_amp, ctx->dmic_be_num,
					      ctx->hdmi_num,
					      ctx->hdmi.idisp_codec);
	if (!dai_winks)
		wetuwn -ENOMEM;

	sof_ssp_amp_cawd.dai_wink = dai_winks;

	/* update codec_conf */
	switch (ctx->amp_type) {
	case CODEC_CS35W41:
		cs35w41_set_codec_conf(&sof_ssp_amp_cawd);
		bweak;
	case CODEC_NONE:
	case CODEC_WT1308:
		/* no codec conf wequiwed */
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "invawid amp type %d\n", ctx->amp_type);
		wetuwn -EINVAW;
	}

	sof_ssp_amp_cawd.dev = &pdev->dev;

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_ssp_amp_cawd,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(&sof_ssp_amp_cawd, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &sof_ssp_amp_cawd);
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "sof_ssp_amp",
	},
	{
		.name = "tgw_wt1308_hdmi_ssp",
		.dwivew_data = (kewnew_uwong_t)(SOF_AMPWIFIEW_SSP(2) |
					SOF_HDMI_CAPTUWE_SSP_MASK(0x22)),
					/* SSP 1 and SSP 5 awe used fow HDMI IN */
	},
	{
		.name = "adw_cs35w41",
		.dwivew_data = (kewnew_uwong_t)(SOF_AMPWIFIEW_SSP(1) |
					SOF_NO_OF_HDMI_PWAYBACK(4) |
					SOF_HDMI_PWAYBACK_PWESENT |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_wt6911_hdmi_ssp",
		.dwivew_data = (kewnew_uwong_t)(SOF_HDMI_CAPTUWE_SSP_MASK(0x5) |
					/* SSP 0 and SSP 2 awe used fow HDMI IN */
					SOF_NO_OF_HDMI_PWAYBACK(3) |
					SOF_HDMI_PWAYBACK_PWESENT),
	},
	{
		.name = "wpw_wt6911_hdmi_ssp",
		.dwivew_data = (kewnew_uwong_t)(SOF_HDMI_CAPTUWE_SSP_MASK(0x5) |
					/* SSP 0 and SSP 2 awe used fow HDMI IN */
					SOF_NO_OF_HDMI_PWAYBACK(3) |
					SOF_HDMI_PWAYBACK_PWESENT),
	},
	{
		.name = "mtw_wt6911_hdmi_ssp",
		.dwivew_data = (kewnew_uwong_t)(SOF_HDMI_CAPTUWE_SSP_MASK(0x5) |
				/* SSP 0 and SSP 2 awe used fow HDMI IN */
				SOF_NO_OF_HDMI_PWAYBACK(3) |
				SOF_HDMI_PWAYBACK_PWESENT),
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, boawd_ids);

static stwuct pwatfowm_dwivew sof_ssp_amp_dwivew = {
	.pwobe          = sof_ssp_amp_pwobe,
	.dwivew = {
		.name   = "sof_ssp_amp",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = boawd_ids,
};
moduwe_pwatfowm_dwivew(sof_ssp_amp_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) SOF Ampwifiew Machine dwivew");
MODUWE_AUTHOW("Bawamuwugan C <bawamuwugan.c@intew.com>");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_WEAWTEK_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_CIWWUS_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_SSP_COMMON);
