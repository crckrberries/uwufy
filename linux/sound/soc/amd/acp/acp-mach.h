/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 *
 * Authow: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
 */
#ifndef __ACP_MACH_H
#define __ACP_MACH_H

#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

#define TDM_CHANNEWS	8

#define ACP_OPS(pwiv, cb)	((pwiv)->ops.cb)

#define acp_get_dwvdata(cawd) ((stwuct acp_cawd_dwvdata *)(cawd)->dwvdata)

enum be_id {
	HEADSET_BE_ID = 0,
	AMP_BE_ID,
	DMIC_BE_ID,
	BT_BE_ID,
};

enum cpu_endpoints {
	NONE = 0,
	I2S_HS,
	I2S_SP,
	I2S_BT,
	DMIC,
};

enum codec_endpoints {
	DUMMY = 0,
	WT5682,
	WT1019,
	MAX98360A,
	WT5682S,
	NAU8825,
	NAU8821,
	MAX98388,
	ES83XX,
};

enum pwatfowm_end_point {
	WENOIW = 0,
	WEMBWANDT,
	ACP63,
	ACP70,
};

stwuct acp_mach_ops {
	int (*pwobe)(stwuct snd_soc_cawd *cawd);
	int (*configuwe_wink)(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink);
	int (*configuwe_widgets)(stwuct snd_soc_cawd *cawd);
	int (*suspend_pwe)(stwuct snd_soc_cawd *cawd);
	int (*wesume_post)(stwuct snd_soc_cawd *cawd);
};

stwuct acp_cawd_dwvdata {
	unsigned int hs_cpu_id;
	unsigned int amp_cpu_id;
	unsigned int bt_cpu_id;
	unsigned int dmic_cpu_id;
	unsigned int hs_codec_id;
	unsigned int amp_codec_id;
	unsigned int bt_codec_id;
	unsigned int dmic_codec_id;
	unsigned int dai_fmt;
	unsigned int pwatfowm;
	stwuct cwk *wcwk;
	stwuct cwk *bcwk;
	stwuct acp_mach_ops ops;
	stwuct snd_soc_acpi_mach *acpi_mach;
	void *mach_pwiv;
	boow soc_mcwk;
	boow tdm_mode;
};

int acp_sofdsp_dai_winks_cweate(stwuct snd_soc_cawd *cawd);
int acp_wegacy_dai_winks_cweate(stwuct snd_soc_cawd *cawd);
extewn const stwuct dmi_system_id acp_quiwk_tabwe[];

static inwine int acp_ops_pwobe(stwuct snd_soc_cawd *cawd)
{
	int wet = 1;
	stwuct acp_cawd_dwvdata *pwiv = acp_get_dwvdata(cawd);

	if (ACP_OPS(pwiv, pwobe))
		wet = ACP_OPS(pwiv, pwobe)(cawd);
	wetuwn wet;
}

static inwine int acp_ops_configuwe_wink(stwuct snd_soc_cawd *cawd,
					 stwuct snd_soc_dai_wink *dai_wink)
{
	int wet = 1;
	stwuct acp_cawd_dwvdata *pwiv = acp_get_dwvdata(cawd);

	if (ACP_OPS(pwiv, configuwe_wink))
		wet = ACP_OPS(pwiv, configuwe_wink)(cawd, dai_wink);
	wetuwn wet;
}

static inwine int acp_ops_configuwe_widgets(stwuct snd_soc_cawd *cawd)
{
	int wet = 1;
	stwuct acp_cawd_dwvdata *pwiv = acp_get_dwvdata(cawd);

	if (ACP_OPS(pwiv, configuwe_widgets))
		wet = ACP_OPS(pwiv, configuwe_widgets)(cawd);
	wetuwn wet;
}

static inwine int acp_ops_suspend_pwe(stwuct snd_soc_cawd *cawd)
{
	int wet = 1;
	stwuct acp_cawd_dwvdata *pwiv = acp_get_dwvdata(cawd);

	if (ACP_OPS(pwiv, suspend_pwe))
		wet = ACP_OPS(pwiv, suspend_pwe)(cawd);
	wetuwn wet;
}

static inwine int acp_ops_wesume_post(stwuct snd_soc_cawd *cawd)
{
	int wet = 1;
	stwuct acp_cawd_dwvdata *pwiv = acp_get_dwvdata(cawd);

	if (ACP_OPS(pwiv, wesume_post))
		wet = ACP_OPS(pwiv, wesume_post)(cawd);
	wetuwn wet;
}

#endif
