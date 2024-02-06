// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek AWSA SoC Audio DAI eTDM Contwow
 *
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "mt8195-afe-cwk.h"
#incwude "mt8195-afe-common.h"
#incwude "mt8195-weg.h"

#define MT8195_ETDM_MAX_CHANNEWS 24
#define MT8195_ETDM_NOWMAW_MAX_BCK_WATE 24576000
#define ETDM_TO_DAI_ID(x) ((x) + MT8195_AFE_IO_ETDM_STAWT)
#define ENUM_TO_STW(x)	#x

enum {
	MTK_DAI_ETDM_FOWMAT_I2S = 0,
	MTK_DAI_ETDM_FOWMAT_WJ,
	MTK_DAI_ETDM_FOWMAT_WJ,
	MTK_DAI_ETDM_FOWMAT_EIAJ,
	MTK_DAI_ETDM_FOWMAT_DSPA,
	MTK_DAI_ETDM_FOWMAT_DSPB,
};

enum {
	MTK_DAI_ETDM_DATA_ONE_PIN = 0,
	MTK_DAI_ETDM_DATA_MUWTI_PIN,
};

enum {
	ETDM_IN,
	ETDM_OUT,
};

enum {
	ETDM_IN_FWOM_PAD,
	ETDM_IN_FWOM_ETDM_OUT1,
	ETDM_IN_FWOM_ETDM_OUT2,
};

enum {
	ETDM_IN_SWAVE_FWOM_PAD,
	ETDM_IN_SWAVE_FWOM_ETDM_OUT1,
	ETDM_IN_SWAVE_FWOM_ETDM_OUT2,
};

enum {
	ETDM_OUT_SWAVE_FWOM_PAD,
	ETDM_OUT_SWAVE_FWOM_ETDM_IN1,
	ETDM_OUT_SWAVE_FWOM_ETDM_IN2,
};

enum {
	COWOWK_ETDM_NONE = 0,
	COWOWK_ETDM_IN1_M = 2,
	COWOWK_ETDM_IN1_S = 3,
	COWOWK_ETDM_IN2_M = 4,
	COWOWK_ETDM_IN2_S = 5,
	COWOWK_ETDM_OUT1_M = 10,
	COWOWK_ETDM_OUT1_S = 11,
	COWOWK_ETDM_OUT2_M = 12,
	COWOWK_ETDM_OUT2_S = 13,
	COWOWK_ETDM_OUT3_M = 14,
	COWOWK_ETDM_OUT3_S = 15,
};

enum {
	ETDM_WEWATCH_TIMING_A1A2SYS,
	ETDM_WEWATCH_TIMING_A3SYS,
	ETDM_WEWATCH_TIMING_A4SYS,
};

enum {
	ETDM_SYNC_NONE,
	ETDM_SYNC_FWOM_IN1,
	ETDM_SYNC_FWOM_IN2,
	ETDM_SYNC_FWOM_OUT1,
	ETDM_SYNC_FWOM_OUT2,
	ETDM_SYNC_FWOM_OUT3,
};

stwuct etdm_con_weg {
	unsigned int con0;
	unsigned int con1;
	unsigned int con2;
	unsigned int con3;
	unsigned int con4;
	unsigned int con5;
};

stwuct mtk_dai_etdm_wate {
	unsigned int wate;
	unsigned int weg_vawue;
};

stwuct mtk_dai_etdm_pwiv {
	unsigned int cwock_mode;
	unsigned int data_mode;
	boow swave_mode;
	boow wwck_inv;
	boow bck_inv;
	unsigned int fowmat;
	unsigned int swots;
	unsigned int wwck_width;
	unsigned int mcwk_fweq;
	unsigned int mcwk_apww;
	unsigned int mcwk_diw;
	int cowowk_souwce_id; //dai id
	unsigned int cowowk_swv_count;
	int cowowk_swv_id[MT8195_AFE_IO_ETDM_NUM - 1]; //dai_id
	boow in_disabwe_ch[MT8195_ETDM_MAX_CHANNEWS];
	unsigned int en_wef_cnt;
};

static const stwuct mtk_dai_etdm_wate mt8195_etdm_wates[] = {
	{ .wate = 8000, .weg_vawue = 0, },
	{ .wate = 12000, .weg_vawue = 1, },
	{ .wate = 16000, .weg_vawue = 2, },
	{ .wate = 24000, .weg_vawue = 3, },
	{ .wate = 32000, .weg_vawue = 4, },
	{ .wate = 48000, .weg_vawue = 5, },
	{ .wate = 96000, .weg_vawue = 7, },
	{ .wate = 192000, .weg_vawue = 9, },
	{ .wate = 384000, .weg_vawue = 11, },
	{ .wate = 11025, .weg_vawue = 16, },
	{ .wate = 22050, .weg_vawue = 17, },
	{ .wate = 44100, .weg_vawue = 18, },
	{ .wate = 88200, .weg_vawue = 19, },
	{ .wate = 176400, .weg_vawue = 20, },
	{ .wate = 352800, .weg_vawue = 21, },
};

static boow mt8195_afe_etdm_is_vawid(int id)
{
	switch (id) {
	case MT8195_AFE_IO_ETDM1_IN:
		fawwthwough;
	case MT8195_AFE_IO_ETDM2_IN:
		fawwthwough;
	case MT8195_AFE_IO_ETDM1_OUT:
		fawwthwough;
	case MT8195_AFE_IO_ETDM2_OUT:
		fawwthwough;
	case MT8195_AFE_IO_DPTX:
		fawwthwough;
	case MT8195_AFE_IO_ETDM3_OUT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow mt8195_afe_hdmitx_dptx_is_vawid(int id)
{
	switch (id) {
	case MT8195_AFE_IO_DPTX:
		fawwthwough;
	case MT8195_AFE_IO_ETDM3_OUT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int get_etdm_fs_timing(unsigned int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt8195_etdm_wates); i++)
		if (mt8195_etdm_wates[i].wate == wate)
			wetuwn mt8195_etdm_wates[i].weg_vawue;

	wetuwn -EINVAW;
}

static unsigned int get_etdm_ch_fixup(unsigned int channews)
{
	if (channews > 16)
		wetuwn 24;
	ewse if (channews > 8)
		wetuwn 16;
	ewse if (channews > 4)
		wetuwn 8;
	ewse if (channews > 2)
		wetuwn 4;
	ewse
		wetuwn 2;
}

static int get_etdm_weg(unsigned int dai_id, stwuct etdm_con_weg *etdm_weg)
{
	switch (dai_id) {
	case MT8195_AFE_IO_ETDM1_IN:
		etdm_weg->con0 = ETDM_IN1_CON0;
		etdm_weg->con1 = ETDM_IN1_CON1;
		etdm_weg->con2 = ETDM_IN1_CON2;
		etdm_weg->con3 = ETDM_IN1_CON3;
		etdm_weg->con4 = ETDM_IN1_CON4;
		etdm_weg->con5 = ETDM_IN1_CON5;
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		etdm_weg->con0 = ETDM_IN2_CON0;
		etdm_weg->con1 = ETDM_IN2_CON1;
		etdm_weg->con2 = ETDM_IN2_CON2;
		etdm_weg->con3 = ETDM_IN2_CON3;
		etdm_weg->con4 = ETDM_IN2_CON4;
		etdm_weg->con5 = ETDM_IN2_CON5;
		bweak;
	case MT8195_AFE_IO_ETDM1_OUT:
		etdm_weg->con0 = ETDM_OUT1_CON0;
		etdm_weg->con1 = ETDM_OUT1_CON1;
		etdm_weg->con2 = ETDM_OUT1_CON2;
		etdm_weg->con3 = ETDM_OUT1_CON3;
		etdm_weg->con4 = ETDM_OUT1_CON4;
		etdm_weg->con5 = ETDM_OUT1_CON5;
		bweak;
	case MT8195_AFE_IO_ETDM2_OUT:
		etdm_weg->con0 = ETDM_OUT2_CON0;
		etdm_weg->con1 = ETDM_OUT2_CON1;
		etdm_weg->con2 = ETDM_OUT2_CON2;
		etdm_weg->con3 = ETDM_OUT2_CON3;
		etdm_weg->con4 = ETDM_OUT2_CON4;
		etdm_weg->con5 = ETDM_OUT2_CON5;
		bweak;
	case MT8195_AFE_IO_ETDM3_OUT:
	case MT8195_AFE_IO_DPTX:
		etdm_weg->con0 = ETDM_OUT3_CON0;
		etdm_weg->con1 = ETDM_OUT3_CON1;
		etdm_weg->con2 = ETDM_OUT3_CON2;
		etdm_weg->con3 = ETDM_OUT3_CON3;
		etdm_weg->con4 = ETDM_OUT3_CON4;
		etdm_weg->con5 = ETDM_OUT3_CON5;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int get_etdm_diw(unsigned int dai_id)
{
	switch (dai_id) {
	case MT8195_AFE_IO_ETDM1_IN:
	case MT8195_AFE_IO_ETDM2_IN:
		wetuwn ETDM_IN;
	case MT8195_AFE_IO_ETDM1_OUT:
	case MT8195_AFE_IO_ETDM2_OUT:
	case MT8195_AFE_IO_ETDM3_OUT:
		wetuwn ETDM_OUT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int get_etdm_wwen(unsigned int bitwidth)
{
	wetuwn bitwidth <= 16 ? 16 : 32;
}

static int is_cowowk_mode(stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;

	if (!mt8195_afe_etdm_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];
	wetuwn (etdm_data->cowowk_swv_count > 0 ||
		etdm_data->cowowk_souwce_id != COWOWK_ETDM_NONE);
}

static int sync_to_dai_id(int souwce_sew)
{
	switch (souwce_sew) {
	case ETDM_SYNC_FWOM_IN1:
		wetuwn MT8195_AFE_IO_ETDM1_IN;
	case ETDM_SYNC_FWOM_IN2:
		wetuwn MT8195_AFE_IO_ETDM2_IN;
	case ETDM_SYNC_FWOM_OUT1:
		wetuwn MT8195_AFE_IO_ETDM1_OUT;
	case ETDM_SYNC_FWOM_OUT2:
		wetuwn MT8195_AFE_IO_ETDM2_OUT;
	case ETDM_SYNC_FWOM_OUT3:
		wetuwn MT8195_AFE_IO_ETDM3_OUT;
	defauwt:
		wetuwn 0;
	}
}

static int get_etdm_cowowk_mastew_id(stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	int dai_id;

	if (!mt8195_afe_etdm_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];
	dai_id = etdm_data->cowowk_souwce_id;

	if (dai_id == COWOWK_ETDM_NONE)
		dai_id = dai->id;

	wetuwn dai_id;
}

static const stwuct snd_kcontwow_new mtk_dai_etdm_o048_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I020 Switch", AFE_CONN48, 20, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I022 Switch", AFE_CONN48, 22, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I046 Switch", AFE_CONN48_1, 14, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I070 Switch", AFE_CONN48_2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o049_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I021 Switch", AFE_CONN49, 21, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I023 Switch", AFE_CONN49, 23, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I047 Switch", AFE_CONN49_1, 15, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I071 Switch", AFE_CONN49_2, 7, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o050_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I024 Switch", AFE_CONN50, 24, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I048 Switch", AFE_CONN50_1, 16, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o051_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I025 Switch", AFE_CONN51, 25, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I049 Switch", AFE_CONN51_1, 17, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o052_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I026 Switch", AFE_CONN52, 26, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I050 Switch", AFE_CONN52_1, 18, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o053_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I027 Switch", AFE_CONN53, 27, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I051 Switch", AFE_CONN53_1, 19, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o054_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I028 Switch", AFE_CONN54, 28, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I052 Switch", AFE_CONN54_1, 20, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o055_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I029 Switch", AFE_CONN55, 29, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I053 Switch", AFE_CONN55_1, 21, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o056_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I030 Switch", AFE_CONN56, 30, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I054 Switch", AFE_CONN56_1, 22, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o057_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I031 Switch", AFE_CONN57, 31, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I055 Switch", AFE_CONN57_1, 23, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o058_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I032 Switch", AFE_CONN58_1, 0, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I056 Switch", AFE_CONN58_1, 24, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o059_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I033 Switch", AFE_CONN59_1, 1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I057 Switch", AFE_CONN59_1, 25, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o060_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I034 Switch", AFE_CONN60_1, 2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I058 Switch", AFE_CONN60_1, 26, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o061_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I035 Switch", AFE_CONN61_1, 3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I059 Switch", AFE_CONN61_1, 27, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o062_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I036 Switch", AFE_CONN62_1, 4, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I060 Switch", AFE_CONN62_1, 28, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o063_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I037 Switch", AFE_CONN63_1, 5, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I061 Switch", AFE_CONN63_1, 29, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o064_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I038 Switch", AFE_CONN64_1, 6, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I062 Switch", AFE_CONN64_1, 30, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o065_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I039 Switch", AFE_CONN65_1, 7, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I063 Switch", AFE_CONN65_1, 31, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o066_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I040 Switch", AFE_CONN66_1, 8, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I064 Switch", AFE_CONN66_2, 0, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o067_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I041 Switch", AFE_CONN67_1, 9, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I065 Switch", AFE_CONN67_2, 1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o068_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I042 Switch", AFE_CONN68_1, 10, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I066 Switch", AFE_CONN68_2, 2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o069_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I043 Switch", AFE_CONN69_1, 11, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I067 Switch", AFE_CONN69_2, 3, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o070_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I044 Switch", AFE_CONN70_1, 12, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I068 Switch", AFE_CONN70_2, 4, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o071_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I045 Switch", AFE_CONN71_1, 13, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I069 Switch", AFE_CONN71_2, 5, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o072_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I020 Switch", AFE_CONN72, 20, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I022 Switch", AFE_CONN72, 22, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I046 Switch", AFE_CONN72_1, 14, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I070 Switch", AFE_CONN72_2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o073_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I021 Switch", AFE_CONN73, 21, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I023 Switch", AFE_CONN73, 23, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I047 Switch", AFE_CONN73_1, 15, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I071 Switch", AFE_CONN73_2, 7, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o074_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I024 Switch", AFE_CONN74, 24, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I048 Switch", AFE_CONN74_1, 16, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o075_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I025 Switch", AFE_CONN75, 25, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I049 Switch", AFE_CONN75_1, 17, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o076_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I026 Switch", AFE_CONN76, 26, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I050 Switch", AFE_CONN76_1, 18, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o077_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I027 Switch", AFE_CONN77, 27, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I051 Switch", AFE_CONN77_1, 19, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o078_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I028 Switch", AFE_CONN78, 28, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I052 Switch", AFE_CONN78_1, 20, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o079_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I029 Switch", AFE_CONN79, 29, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I053 Switch", AFE_CONN79_1, 21, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o080_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I030 Switch", AFE_CONN80, 30, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I054 Switch", AFE_CONN80_1, 22, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o081_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I031 Switch", AFE_CONN81, 31, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I055 Switch", AFE_CONN81_1, 23, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o082_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I032 Switch", AFE_CONN82_1, 0, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I056 Switch", AFE_CONN82_1, 24, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o083_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I033 Switch", AFE_CONN83_1, 1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I057 Switch", AFE_CONN83_1, 25, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o084_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I034 Switch", AFE_CONN84_1, 2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I058 Switch", AFE_CONN84_1, 26, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o085_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I035 Switch", AFE_CONN85_1, 3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I059 Switch", AFE_CONN85_1, 27, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o086_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I036 Switch", AFE_CONN86_1, 4, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I060 Switch", AFE_CONN86_1, 28, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o087_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I037 Switch", AFE_CONN87_1, 5, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I061 Switch", AFE_CONN87_1, 29, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o088_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I038 Switch", AFE_CONN88_1, 6, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I062 Switch", AFE_CONN88_1, 30, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o089_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I039 Switch", AFE_CONN89_1, 7, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I063 Switch", AFE_CONN89_1, 31, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o090_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I040 Switch", AFE_CONN90_1, 8, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I064 Switch", AFE_CONN90_2, 0, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o091_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I041 Switch", AFE_CONN91_1, 9, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I065 Switch", AFE_CONN91_2, 1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o092_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I042 Switch", AFE_CONN92_1, 10, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I066 Switch", AFE_CONN92_2, 2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o093_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I043 Switch", AFE_CONN93_1, 11, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I067 Switch", AFE_CONN93_2, 3, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o094_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I044 Switch", AFE_CONN94_1, 12, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I068 Switch", AFE_CONN94_2, 4, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_etdm_o095_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I045 Switch", AFE_CONN95_1, 13, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I069 Switch", AFE_CONN95_2, 5, 1, 0),
};

static const chaw * const mt8195_etdm_cwk_swc_sew_text[] = {
	"26m",
	"a1sys_a2sys",
	"a3sys",
	"a4sys",
};

static SOC_ENUM_SINGWE_EXT_DECW(etdmout_cwk_swc_enum,
	mt8195_etdm_cwk_swc_sew_text);

static const chaw * const hdmitx_dptx_mux_map[] = {
	"Disconnect", "Connect",
};

static int hdmitx_dptx_mux_map_vawue[] = {
	0, 1,
};

/* HDMI_OUT_MUX */
static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(hdmi_out_mux_map_enum,
				SND_SOC_NOPM,
				0,
				1,
				hdmitx_dptx_mux_map,
				hdmitx_dptx_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_out_mux_contwow =
	SOC_DAPM_ENUM("HDMI_OUT_MUX", hdmi_out_mux_map_enum);

/* DPTX_OUT_MUX */
static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(dptx_out_mux_map_enum,
				SND_SOC_NOPM,
				0,
				1,
				hdmitx_dptx_mux_map,
				hdmitx_dptx_mux_map_vawue);

static const stwuct snd_kcontwow_new dptx_out_mux_contwow =
	SOC_DAPM_ENUM("DPTX_OUT_MUX", dptx_out_mux_map_enum);

/* HDMI_CH0_MUX ~ HDMI_CH7_MUX */
static const chaw *const afe_conn_hdmi_mux_map[] = {
	"CH0", "CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7",
};

static int afe_conn_hdmi_mux_map_vawue[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch0_mux_map_enum,
				AFE_TDMOUT_CONN0,
				0,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch0_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH0_MUX", hdmi_ch0_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch1_mux_map_enum,
				AFE_TDMOUT_CONN0,
				4,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch1_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH1_MUX", hdmi_ch1_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch2_mux_map_enum,
				AFE_TDMOUT_CONN0,
				8,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch2_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH2_MUX", hdmi_ch2_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch3_mux_map_enum,
				AFE_TDMOUT_CONN0,
				12,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch3_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH3_MUX", hdmi_ch3_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch4_mux_map_enum,
				AFE_TDMOUT_CONN0,
				16,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch4_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH4_MUX", hdmi_ch4_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch5_mux_map_enum,
				AFE_TDMOUT_CONN0,
				20,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch5_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH5_MUX", hdmi_ch5_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch6_mux_map_enum,
				AFE_TDMOUT_CONN0,
				24,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch6_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH6_MUX", hdmi_ch6_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch7_mux_map_enum,
				AFE_TDMOUT_CONN0,
				28,
				0xf,
				afe_conn_hdmi_mux_map,
				afe_conn_hdmi_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch7_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH7_MUX", hdmi_ch7_mux_map_enum);

static int mt8195_etdm_cwk_swc_sew_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	unsigned int souwce = ucontwow->vawue.enumewated.item[0];
	unsigned int vaw;
	unsigned int mask;
	unsigned int weg;

	if (souwce >= e->items)
		wetuwn -EINVAW;

	weg = 0;
	if (!stwcmp(kcontwow->id.name, "ETDM_OUT1_Cwock_Souwce")) {
		weg = ETDM_OUT1_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		vaw = ETDM_OUT_CON4_CWOCK(souwce);
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_OUT2_Cwock_Souwce")) {
		weg = ETDM_OUT2_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		vaw = ETDM_OUT_CON4_CWOCK(souwce);
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_OUT3_Cwock_Souwce")) {
		weg = ETDM_OUT3_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		vaw = ETDM_OUT_CON4_CWOCK(souwce);
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_IN1_Cwock_Souwce")) {
		weg = ETDM_IN1_CON2;
		mask = ETDM_IN_CON2_CWOCK_MASK;
		vaw = ETDM_IN_CON2_CWOCK(souwce);
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_IN2_Cwock_Souwce")) {
		weg = ETDM_IN2_CON2;
		mask = ETDM_IN_CON2_CWOCK_MASK;
		vaw = ETDM_IN_CON2_CWOCK(souwce);
	}

	if (weg)
		wegmap_update_bits(afe->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int mt8195_etdm_cwk_swc_sew_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	unsigned int vawue = 0;
	unsigned int weg = 0;
	unsigned int mask = 0;
	unsigned int shift = 0;

	if (!stwcmp(kcontwow->id.name, "ETDM_OUT1_Cwock_Souwce")) {
		weg = ETDM_OUT1_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		shift = ETDM_OUT_CON4_CWOCK_SHIFT;
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_OUT2_Cwock_Souwce")) {
		weg = ETDM_OUT2_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		shift = ETDM_OUT_CON4_CWOCK_SHIFT;
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_OUT3_Cwock_Souwce")) {
		weg = ETDM_OUT3_CON4;
		mask = ETDM_OUT_CON4_CWOCK_MASK;
		shift = ETDM_OUT_CON4_CWOCK_SHIFT;
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_IN1_Cwock_Souwce")) {
		weg = ETDM_IN1_CON2;
		mask = ETDM_IN_CON2_CWOCK_MASK;
		shift = ETDM_IN_CON2_CWOCK_SHIFT;
	} ewse if (!stwcmp(kcontwow->id.name, "ETDM_IN2_Cwock_Souwce")) {
		weg = ETDM_IN2_CON2;
		mask = ETDM_IN_CON2_CWOCK_MASK;
		shift = ETDM_IN_CON2_CWOCK_SHIFT;
	}

	if (weg)
		wegmap_wead(afe->wegmap, weg, &vawue);

	vawue &= mask;
	vawue >>= shift;
	ucontwow->vawue.enumewated.item[0] = vawue;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new mtk_dai_etdm_contwows[] = {
	SOC_ENUM_EXT("ETDM_OUT1_Cwock_Souwce",
		     etdmout_cwk_swc_enum,
		     mt8195_etdm_cwk_swc_sew_get,
		     mt8195_etdm_cwk_swc_sew_put),
	SOC_ENUM_EXT("ETDM_OUT2_Cwock_Souwce",
		     etdmout_cwk_swc_enum,
		     mt8195_etdm_cwk_swc_sew_get,
		     mt8195_etdm_cwk_swc_sew_put),
	SOC_ENUM_EXT("ETDM_OUT3_Cwock_Souwce",
		     etdmout_cwk_swc_enum,
		     mt8195_etdm_cwk_swc_sew_get,
		     mt8195_etdm_cwk_swc_sew_put),
	SOC_ENUM_EXT("ETDM_IN1_Cwock_Souwce",
		     etdmout_cwk_swc_enum,
		     mt8195_etdm_cwk_swc_sew_get,
		     mt8195_etdm_cwk_swc_sew_put),
	SOC_ENUM_EXT("ETDM_IN2_Cwock_Souwce",
		     etdmout_cwk_swc_enum,
		     mt8195_etdm_cwk_swc_sew_get,
		     mt8195_etdm_cwk_swc_sew_put),
};

static const stwuct snd_soc_dapm_widget mtk_dai_etdm_widgets[] = {
	/* eTDM_IN2 */
	SND_SOC_DAPM_MIXEW("I012", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I013", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I014", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I015", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I016", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I017", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I018", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I019", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* eTDM_IN1 */
	SND_SOC_DAPM_MIXEW("I072", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I073", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I074", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I075", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I076", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I077", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I078", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I079", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I080", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I081", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I082", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I083", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I084", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I085", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I086", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I087", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I088", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I089", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I090", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I091", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I092", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I093", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I094", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I095", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* eTDM_OUT2 */
	SND_SOC_DAPM_MIXEW("O048", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o048_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o048_mix)),
	SND_SOC_DAPM_MIXEW("O049", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o049_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o049_mix)),
	SND_SOC_DAPM_MIXEW("O050", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o050_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o050_mix)),
	SND_SOC_DAPM_MIXEW("O051", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o051_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o051_mix)),
	SND_SOC_DAPM_MIXEW("O052", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o052_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o052_mix)),
	SND_SOC_DAPM_MIXEW("O053", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o053_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o053_mix)),
	SND_SOC_DAPM_MIXEW("O054", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o054_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o054_mix)),
	SND_SOC_DAPM_MIXEW("O055", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o055_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o055_mix)),
	SND_SOC_DAPM_MIXEW("O056", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o056_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o056_mix)),
	SND_SOC_DAPM_MIXEW("O057", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o057_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o057_mix)),
	SND_SOC_DAPM_MIXEW("O058", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o058_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o058_mix)),
	SND_SOC_DAPM_MIXEW("O059", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o059_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o059_mix)),
	SND_SOC_DAPM_MIXEW("O060", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o060_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o060_mix)),
	SND_SOC_DAPM_MIXEW("O061", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o061_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o061_mix)),
	SND_SOC_DAPM_MIXEW("O062", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o062_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o062_mix)),
	SND_SOC_DAPM_MIXEW("O063", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o063_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o063_mix)),
	SND_SOC_DAPM_MIXEW("O064", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o064_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o064_mix)),
	SND_SOC_DAPM_MIXEW("O065", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o065_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o065_mix)),
	SND_SOC_DAPM_MIXEW("O066", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o066_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o066_mix)),
	SND_SOC_DAPM_MIXEW("O067", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o067_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o067_mix)),
	SND_SOC_DAPM_MIXEW("O068", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o068_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o068_mix)),
	SND_SOC_DAPM_MIXEW("O069", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o069_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o069_mix)),
	SND_SOC_DAPM_MIXEW("O070", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o070_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o070_mix)),
	SND_SOC_DAPM_MIXEW("O071", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o071_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o071_mix)),

	/* eTDM_OUT1 */
	SND_SOC_DAPM_MIXEW("O072", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o072_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o072_mix)),
	SND_SOC_DAPM_MIXEW("O073", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o073_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o073_mix)),
	SND_SOC_DAPM_MIXEW("O074", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o074_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o074_mix)),
	SND_SOC_DAPM_MIXEW("O075", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o075_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o075_mix)),
	SND_SOC_DAPM_MIXEW("O076", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o076_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o076_mix)),
	SND_SOC_DAPM_MIXEW("O077", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o077_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o077_mix)),
	SND_SOC_DAPM_MIXEW("O078", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o078_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o078_mix)),
	SND_SOC_DAPM_MIXEW("O079", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o079_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o079_mix)),
	SND_SOC_DAPM_MIXEW("O080", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o080_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o080_mix)),
	SND_SOC_DAPM_MIXEW("O081", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o081_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o081_mix)),
	SND_SOC_DAPM_MIXEW("O082", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o082_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o082_mix)),
	SND_SOC_DAPM_MIXEW("O083", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o083_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o083_mix)),
	SND_SOC_DAPM_MIXEW("O084", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o084_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o084_mix)),
	SND_SOC_DAPM_MIXEW("O085", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o085_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o085_mix)),
	SND_SOC_DAPM_MIXEW("O086", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o086_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o086_mix)),
	SND_SOC_DAPM_MIXEW("O087", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o087_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o087_mix)),
	SND_SOC_DAPM_MIXEW("O088", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o088_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o088_mix)),
	SND_SOC_DAPM_MIXEW("O089", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o089_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o089_mix)),
	SND_SOC_DAPM_MIXEW("O090", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o090_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o090_mix)),
	SND_SOC_DAPM_MIXEW("O091", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o091_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o091_mix)),
	SND_SOC_DAPM_MIXEW("O092", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o092_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o092_mix)),
	SND_SOC_DAPM_MIXEW("O093", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o093_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o093_mix)),
	SND_SOC_DAPM_MIXEW("O094", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o094_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o094_mix)),
	SND_SOC_DAPM_MIXEW("O095", SND_SOC_NOPM, 0, 0,
			   mtk_dai_etdm_o095_mix,
			   AWWAY_SIZE(mtk_dai_etdm_o095_mix)),

	/* eTDM_OUT3 */
	SND_SOC_DAPM_MUX("HDMI_OUT_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_out_mux_contwow),
	SND_SOC_DAPM_MUX("DPTX_OUT_MUX", SND_SOC_NOPM, 0, 0,
			 &dptx_out_mux_contwow),

	SND_SOC_DAPM_MUX("HDMI_CH0_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch0_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH1_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch1_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH2_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch2_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH3_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch3_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH4_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch4_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH5_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch5_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH6_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch6_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH7_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch7_mux_contwow),

	SND_SOC_DAPM_INPUT("ETDM_INPUT"),
	SND_SOC_DAPM_OUTPUT("ETDM_OUTPUT"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_etdm_woutes[] = {
	{"I012", NUWW, "ETDM2 Captuwe"},
	{"I013", NUWW, "ETDM2 Captuwe"},
	{"I014", NUWW, "ETDM2 Captuwe"},
	{"I015", NUWW, "ETDM2 Captuwe"},
	{"I016", NUWW, "ETDM2 Captuwe"},
	{"I017", NUWW, "ETDM2 Captuwe"},
	{"I018", NUWW, "ETDM2 Captuwe"},
	{"I019", NUWW, "ETDM2 Captuwe"},

	{"I072", NUWW, "ETDM1 Captuwe"},
	{"I073", NUWW, "ETDM1 Captuwe"},
	{"I074", NUWW, "ETDM1 Captuwe"},
	{"I075", NUWW, "ETDM1 Captuwe"},
	{"I076", NUWW, "ETDM1 Captuwe"},
	{"I077", NUWW, "ETDM1 Captuwe"},
	{"I078", NUWW, "ETDM1 Captuwe"},
	{"I079", NUWW, "ETDM1 Captuwe"},
	{"I080", NUWW, "ETDM1 Captuwe"},
	{"I081", NUWW, "ETDM1 Captuwe"},
	{"I082", NUWW, "ETDM1 Captuwe"},
	{"I083", NUWW, "ETDM1 Captuwe"},
	{"I084", NUWW, "ETDM1 Captuwe"},
	{"I085", NUWW, "ETDM1 Captuwe"},
	{"I086", NUWW, "ETDM1 Captuwe"},
	{"I087", NUWW, "ETDM1 Captuwe"},
	{"I088", NUWW, "ETDM1 Captuwe"},
	{"I089", NUWW, "ETDM1 Captuwe"},
	{"I090", NUWW, "ETDM1 Captuwe"},
	{"I091", NUWW, "ETDM1 Captuwe"},
	{"I092", NUWW, "ETDM1 Captuwe"},
	{"I093", NUWW, "ETDM1 Captuwe"},
	{"I094", NUWW, "ETDM1 Captuwe"},
	{"I095", NUWW, "ETDM1 Captuwe"},

	{"UW8", NUWW, "ETDM1 Captuwe"},
	{"UW3", NUWW, "ETDM2 Captuwe"},

	{"ETDM2 Pwayback", NUWW, "O048"},
	{"ETDM2 Pwayback", NUWW, "O049"},
	{"ETDM2 Pwayback", NUWW, "O050"},
	{"ETDM2 Pwayback", NUWW, "O051"},
	{"ETDM2 Pwayback", NUWW, "O052"},
	{"ETDM2 Pwayback", NUWW, "O053"},
	{"ETDM2 Pwayback", NUWW, "O054"},
	{"ETDM2 Pwayback", NUWW, "O055"},
	{"ETDM2 Pwayback", NUWW, "O056"},
	{"ETDM2 Pwayback", NUWW, "O057"},
	{"ETDM2 Pwayback", NUWW, "O058"},
	{"ETDM2 Pwayback", NUWW, "O059"},
	{"ETDM2 Pwayback", NUWW, "O060"},
	{"ETDM2 Pwayback", NUWW, "O061"},
	{"ETDM2 Pwayback", NUWW, "O062"},
	{"ETDM2 Pwayback", NUWW, "O063"},
	{"ETDM2 Pwayback", NUWW, "O064"},
	{"ETDM2 Pwayback", NUWW, "O065"},
	{"ETDM2 Pwayback", NUWW, "O066"},
	{"ETDM2 Pwayback", NUWW, "O067"},
	{"ETDM2 Pwayback", NUWW, "O068"},
	{"ETDM2 Pwayback", NUWW, "O069"},
	{"ETDM2 Pwayback", NUWW, "O070"},
	{"ETDM2 Pwayback", NUWW, "O071"},

	{"ETDM1 Pwayback", NUWW, "O072"},
	{"ETDM1 Pwayback", NUWW, "O073"},
	{"ETDM1 Pwayback", NUWW, "O074"},
	{"ETDM1 Pwayback", NUWW, "O075"},
	{"ETDM1 Pwayback", NUWW, "O076"},
	{"ETDM1 Pwayback", NUWW, "O077"},
	{"ETDM1 Pwayback", NUWW, "O078"},
	{"ETDM1 Pwayback", NUWW, "O079"},
	{"ETDM1 Pwayback", NUWW, "O080"},
	{"ETDM1 Pwayback", NUWW, "O081"},
	{"ETDM1 Pwayback", NUWW, "O082"},
	{"ETDM1 Pwayback", NUWW, "O083"},
	{"ETDM1 Pwayback", NUWW, "O084"},
	{"ETDM1 Pwayback", NUWW, "O085"},
	{"ETDM1 Pwayback", NUWW, "O086"},
	{"ETDM1 Pwayback", NUWW, "O087"},
	{"ETDM1 Pwayback", NUWW, "O088"},
	{"ETDM1 Pwayback", NUWW, "O089"},
	{"ETDM1 Pwayback", NUWW, "O090"},
	{"ETDM1 Pwayback", NUWW, "O091"},
	{"ETDM1 Pwayback", NUWW, "O092"},
	{"ETDM1 Pwayback", NUWW, "O093"},
	{"ETDM1 Pwayback", NUWW, "O094"},
	{"ETDM1 Pwayback", NUWW, "O095"},

	{"O048", "I020 Switch", "I020"},
	{"O049", "I021 Switch", "I021"},

	{"O048", "I022 Switch", "I022"},
	{"O049", "I023 Switch", "I023"},
	{"O050", "I024 Switch", "I024"},
	{"O051", "I025 Switch", "I025"},
	{"O052", "I026 Switch", "I026"},
	{"O053", "I027 Switch", "I027"},
	{"O054", "I028 Switch", "I028"},
	{"O055", "I029 Switch", "I029"},
	{"O056", "I030 Switch", "I030"},
	{"O057", "I031 Switch", "I031"},
	{"O058", "I032 Switch", "I032"},
	{"O059", "I033 Switch", "I033"},
	{"O060", "I034 Switch", "I034"},
	{"O061", "I035 Switch", "I035"},
	{"O062", "I036 Switch", "I036"},
	{"O063", "I037 Switch", "I037"},
	{"O064", "I038 Switch", "I038"},
	{"O065", "I039 Switch", "I039"},
	{"O066", "I040 Switch", "I040"},
	{"O067", "I041 Switch", "I041"},
	{"O068", "I042 Switch", "I042"},
	{"O069", "I043 Switch", "I043"},
	{"O070", "I044 Switch", "I044"},
	{"O071", "I045 Switch", "I045"},

	{"O048", "I046 Switch", "I046"},
	{"O049", "I047 Switch", "I047"},
	{"O050", "I048 Switch", "I048"},
	{"O051", "I049 Switch", "I049"},
	{"O052", "I050 Switch", "I050"},
	{"O053", "I051 Switch", "I051"},
	{"O054", "I052 Switch", "I052"},
	{"O055", "I053 Switch", "I053"},
	{"O056", "I054 Switch", "I054"},
	{"O057", "I055 Switch", "I055"},
	{"O058", "I056 Switch", "I056"},
	{"O059", "I057 Switch", "I057"},
	{"O060", "I058 Switch", "I058"},
	{"O061", "I059 Switch", "I059"},
	{"O062", "I060 Switch", "I060"},
	{"O063", "I061 Switch", "I061"},
	{"O064", "I062 Switch", "I062"},
	{"O065", "I063 Switch", "I063"},
	{"O066", "I064 Switch", "I064"},
	{"O067", "I065 Switch", "I065"},
	{"O068", "I066 Switch", "I066"},
	{"O069", "I067 Switch", "I067"},
	{"O070", "I068 Switch", "I068"},
	{"O071", "I069 Switch", "I069"},

	{"O048", "I070 Switch", "I070"},
	{"O049", "I071 Switch", "I071"},

	{"O072", "I020 Switch", "I020"},
	{"O073", "I021 Switch", "I021"},

	{"O072", "I022 Switch", "I022"},
	{"O073", "I023 Switch", "I023"},
	{"O074", "I024 Switch", "I024"},
	{"O075", "I025 Switch", "I025"},
	{"O076", "I026 Switch", "I026"},
	{"O077", "I027 Switch", "I027"},
	{"O078", "I028 Switch", "I028"},
	{"O079", "I029 Switch", "I029"},
	{"O080", "I030 Switch", "I030"},
	{"O081", "I031 Switch", "I031"},
	{"O082", "I032 Switch", "I032"},
	{"O083", "I033 Switch", "I033"},
	{"O084", "I034 Switch", "I034"},
	{"O085", "I035 Switch", "I035"},
	{"O086", "I036 Switch", "I036"},
	{"O087", "I037 Switch", "I037"},
	{"O088", "I038 Switch", "I038"},
	{"O089", "I039 Switch", "I039"},
	{"O090", "I040 Switch", "I040"},
	{"O091", "I041 Switch", "I041"},
	{"O092", "I042 Switch", "I042"},
	{"O093", "I043 Switch", "I043"},
	{"O094", "I044 Switch", "I044"},
	{"O095", "I045 Switch", "I045"},

	{"O072", "I046 Switch", "I046"},
	{"O073", "I047 Switch", "I047"},
	{"O074", "I048 Switch", "I048"},
	{"O075", "I049 Switch", "I049"},
	{"O076", "I050 Switch", "I050"},
	{"O077", "I051 Switch", "I051"},
	{"O078", "I052 Switch", "I052"},
	{"O079", "I053 Switch", "I053"},
	{"O080", "I054 Switch", "I054"},
	{"O081", "I055 Switch", "I055"},
	{"O082", "I056 Switch", "I056"},
	{"O083", "I057 Switch", "I057"},
	{"O084", "I058 Switch", "I058"},
	{"O085", "I059 Switch", "I059"},
	{"O086", "I060 Switch", "I060"},
	{"O087", "I061 Switch", "I061"},
	{"O088", "I062 Switch", "I062"},
	{"O089", "I063 Switch", "I063"},
	{"O090", "I064 Switch", "I064"},
	{"O091", "I065 Switch", "I065"},
	{"O092", "I066 Switch", "I066"},
	{"O093", "I067 Switch", "I067"},
	{"O094", "I068 Switch", "I068"},
	{"O095", "I069 Switch", "I069"},

	{"O072", "I070 Switch", "I070"},
	{"O073", "I071 Switch", "I071"},

	{"HDMI_CH0_MUX", "CH0", "DW10"},
	{"HDMI_CH0_MUX", "CH1", "DW10"},
	{"HDMI_CH0_MUX", "CH2", "DW10"},
	{"HDMI_CH0_MUX", "CH3", "DW10"},
	{"HDMI_CH0_MUX", "CH4", "DW10"},
	{"HDMI_CH0_MUX", "CH5", "DW10"},
	{"HDMI_CH0_MUX", "CH6", "DW10"},
	{"HDMI_CH0_MUX", "CH7", "DW10"},

	{"HDMI_CH1_MUX", "CH0", "DW10"},
	{"HDMI_CH1_MUX", "CH1", "DW10"},
	{"HDMI_CH1_MUX", "CH2", "DW10"},
	{"HDMI_CH1_MUX", "CH3", "DW10"},
	{"HDMI_CH1_MUX", "CH4", "DW10"},
	{"HDMI_CH1_MUX", "CH5", "DW10"},
	{"HDMI_CH1_MUX", "CH6", "DW10"},
	{"HDMI_CH1_MUX", "CH7", "DW10"},

	{"HDMI_CH2_MUX", "CH0", "DW10"},
	{"HDMI_CH2_MUX", "CH1", "DW10"},
	{"HDMI_CH2_MUX", "CH2", "DW10"},
	{"HDMI_CH2_MUX", "CH3", "DW10"},
	{"HDMI_CH2_MUX", "CH4", "DW10"},
	{"HDMI_CH2_MUX", "CH5", "DW10"},
	{"HDMI_CH2_MUX", "CH6", "DW10"},
	{"HDMI_CH2_MUX", "CH7", "DW10"},

	{"HDMI_CH3_MUX", "CH0", "DW10"},
	{"HDMI_CH3_MUX", "CH1", "DW10"},
	{"HDMI_CH3_MUX", "CH2", "DW10"},
	{"HDMI_CH3_MUX", "CH3", "DW10"},
	{"HDMI_CH3_MUX", "CH4", "DW10"},
	{"HDMI_CH3_MUX", "CH5", "DW10"},
	{"HDMI_CH3_MUX", "CH6", "DW10"},
	{"HDMI_CH3_MUX", "CH7", "DW10"},

	{"HDMI_CH4_MUX", "CH0", "DW10"},
	{"HDMI_CH4_MUX", "CH1", "DW10"},
	{"HDMI_CH4_MUX", "CH2", "DW10"},
	{"HDMI_CH4_MUX", "CH3", "DW10"},
	{"HDMI_CH4_MUX", "CH4", "DW10"},
	{"HDMI_CH4_MUX", "CH5", "DW10"},
	{"HDMI_CH4_MUX", "CH6", "DW10"},
	{"HDMI_CH4_MUX", "CH7", "DW10"},

	{"HDMI_CH5_MUX", "CH0", "DW10"},
	{"HDMI_CH5_MUX", "CH1", "DW10"},
	{"HDMI_CH5_MUX", "CH2", "DW10"},
	{"HDMI_CH5_MUX", "CH3", "DW10"},
	{"HDMI_CH5_MUX", "CH4", "DW10"},
	{"HDMI_CH5_MUX", "CH5", "DW10"},
	{"HDMI_CH5_MUX", "CH6", "DW10"},
	{"HDMI_CH5_MUX", "CH7", "DW10"},

	{"HDMI_CH6_MUX", "CH0", "DW10"},
	{"HDMI_CH6_MUX", "CH1", "DW10"},
	{"HDMI_CH6_MUX", "CH2", "DW10"},
	{"HDMI_CH6_MUX", "CH3", "DW10"},
	{"HDMI_CH6_MUX", "CH4", "DW10"},
	{"HDMI_CH6_MUX", "CH5", "DW10"},
	{"HDMI_CH6_MUX", "CH6", "DW10"},
	{"HDMI_CH6_MUX", "CH7", "DW10"},

	{"HDMI_CH7_MUX", "CH0", "DW10"},
	{"HDMI_CH7_MUX", "CH1", "DW10"},
	{"HDMI_CH7_MUX", "CH2", "DW10"},
	{"HDMI_CH7_MUX", "CH3", "DW10"},
	{"HDMI_CH7_MUX", "CH4", "DW10"},
	{"HDMI_CH7_MUX", "CH5", "DW10"},
	{"HDMI_CH7_MUX", "CH6", "DW10"},
	{"HDMI_CH7_MUX", "CH7", "DW10"},

	{"HDMI_OUT_MUX", "Connect", "HDMI_CH0_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH1_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH2_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH3_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH4_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH5_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH6_MUX"},
	{"HDMI_OUT_MUX", "Connect", "HDMI_CH7_MUX"},

	{"DPTX_OUT_MUX", "Connect", "HDMI_CH0_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH1_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH2_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH3_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH4_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH5_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH6_MUX"},
	{"DPTX_OUT_MUX", "Connect", "HDMI_CH7_MUX"},

	{"ETDM3 Pwayback", NUWW, "HDMI_OUT_MUX"},
	{"DPTX Pwayback", NUWW, "DPTX_OUT_MUX"},

	{"ETDM_OUTPUT", NUWW, "DPTX Pwayback"},
	{"ETDM_OUTPUT", NUWW, "ETDM1 Pwayback"},
	{"ETDM_OUTPUT", NUWW, "ETDM2 Pwayback"},
	{"ETDM_OUTPUT", NUWW, "ETDM3 Pwayback"},
	{"ETDM1 Captuwe", NUWW, "ETDM_INPUT"},
	{"ETDM2 Captuwe", NUWW, "ETDM_INPUT"},
};

static int mt8195_afe_enabwe_etdm(stwuct mtk_base_afe *afe, int dai_id)
{
	int wet = 0;
	stwuct etdm_con_weg etdm_weg;
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	unsigned wong fwags;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	spin_wock_iwqsave(&afe_pwiv->afe_ctww_wock, fwags);
	etdm_data->en_wef_cnt++;
	if (etdm_data->en_wef_cnt == 1) {
		wet = get_etdm_weg(dai_id, &etdm_weg);
		if (wet < 0)
			goto out;

		wegmap_update_bits(afe->wegmap, etdm_weg.con0,
				   ETDM_CON0_EN, ETDM_CON0_EN);
	}
out:
	spin_unwock_iwqwestowe(&afe_pwiv->afe_ctww_wock, fwags);
	wetuwn wet;
}

static int mt8195_afe_disabwe_etdm(stwuct mtk_base_afe *afe, int dai_id)
{
	int wet = 0;
	stwuct etdm_con_weg etdm_weg;
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	unsigned wong fwags;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	spin_wock_iwqsave(&afe_pwiv->afe_ctww_wock, fwags);
	if (etdm_data->en_wef_cnt > 0) {
		etdm_data->en_wef_cnt--;
		if (etdm_data->en_wef_cnt == 0) {
			wet = get_etdm_weg(dai_id, &etdm_weg);
			if (wet < 0)
				goto out;

			wegmap_update_bits(afe->wegmap, etdm_weg.con0,
					   ETDM_CON0_EN, 0);
		}
	}
out:
	spin_unwock_iwqwestowe(&afe_pwiv->afe_ctww_wock, fwags);
	wetuwn wet;
}

static int etdm_cowowk_swv_sew(int id, int swave_mode)
{
	if (swave_mode) {
		switch (id) {
		case MT8195_AFE_IO_ETDM1_IN:
			wetuwn COWOWK_ETDM_IN1_S;
		case MT8195_AFE_IO_ETDM2_IN:
			wetuwn COWOWK_ETDM_IN2_S;
		case MT8195_AFE_IO_ETDM1_OUT:
			wetuwn COWOWK_ETDM_OUT1_S;
		case MT8195_AFE_IO_ETDM2_OUT:
			wetuwn COWOWK_ETDM_OUT2_S;
		case MT8195_AFE_IO_ETDM3_OUT:
			wetuwn COWOWK_ETDM_OUT3_S;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (id) {
		case MT8195_AFE_IO_ETDM1_IN:
			wetuwn COWOWK_ETDM_IN1_M;
		case MT8195_AFE_IO_ETDM2_IN:
			wetuwn COWOWK_ETDM_IN2_M;
		case MT8195_AFE_IO_ETDM1_OUT:
			wetuwn COWOWK_ETDM_OUT1_M;
		case MT8195_AFE_IO_ETDM2_OUT:
			wetuwn COWOWK_ETDM_OUT2_M;
		case MT8195_AFE_IO_ETDM3_OUT:
			wetuwn COWOWK_ETDM_OUT3_M;
		defauwt:
			wetuwn -EINVAW;
		}
	}
}

static int mt8195_etdm_sync_mode_configuwe(stwuct mtk_base_afe *afe, int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	unsigned int weg = 0;
	unsigned int mask;
	unsigned int vaw;
	int cowowk_souwce_sew;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	if (etdm_data->cowowk_souwce_id == COWOWK_ETDM_NONE)
		wetuwn 0;

	cowowk_souwce_sew = etdm_cowowk_swv_sew(etdm_data->cowowk_souwce_id,
						etdm_data->swave_mode);
	if (cowowk_souwce_sew < 0)
		wetuwn cowowk_souwce_sew;

	switch (dai_id) {
	case MT8195_AFE_IO_ETDM1_IN:
		weg = ETDM_COWOWK_CON1;
		mask = ETDM_IN1_SWAVE_SEW_MASK;
		vaw = ETDM_IN1_SWAVE_SEW(cowowk_souwce_sew);
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		weg = ETDM_COWOWK_CON2;
		mask = ETDM_IN2_SWAVE_SEW_MASK;
		vaw = ETDM_IN2_SWAVE_SEW(cowowk_souwce_sew);
		bweak;
	case MT8195_AFE_IO_ETDM1_OUT:
		weg = ETDM_COWOWK_CON0;
		mask = ETDM_OUT1_SWAVE_SEW_MASK;
		vaw = ETDM_OUT1_SWAVE_SEW(cowowk_souwce_sew);
		bweak;
	case MT8195_AFE_IO_ETDM2_OUT:
		weg = ETDM_COWOWK_CON2;
		mask = ETDM_OUT2_SWAVE_SEW_MASK;
		vaw = ETDM_OUT2_SWAVE_SEW(cowowk_souwce_sew);
		bweak;
	case MT8195_AFE_IO_ETDM3_OUT:
		weg = ETDM_COWOWK_CON2;
		mask = ETDM_OUT3_SWAVE_SEW_MASK;
		vaw = ETDM_OUT3_SWAVE_SEW(cowowk_souwce_sew);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int mtk_dai_etdm_get_cg_id_by_dai_id(int dai_id)
{
	int cg_id = -1;

	switch (dai_id) {
	case MT8195_AFE_IO_DPTX:
		cg_id = MT8195_CWK_AUD_HDMI_OUT;
		bweak;
	case MT8195_AFE_IO_ETDM1_IN:
		cg_id = MT8195_CWK_AUD_TDM_IN;
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		cg_id = MT8195_CWK_AUD_I2SIN;
		bweak;
	case MT8195_AFE_IO_ETDM1_OUT:
		cg_id = MT8195_CWK_AUD_TDM_OUT;
		bweak;
	case MT8195_AFE_IO_ETDM2_OUT:
		cg_id = MT8195_CWK_AUD_I2S_OUT;
		bweak;
	case MT8195_AFE_IO_ETDM3_OUT:
		cg_id = MT8195_CWK_AUD_HDMI_OUT;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn cg_id;
}

static int mtk_dai_etdm_get_cwk_id_by_dai_id(int dai_id)
{
	int cwk_id = -1;

	switch (dai_id) {
	case MT8195_AFE_IO_DPTX:
		cwk_id = MT8195_CWK_TOP_DPTX_M_SEW;
		bweak;
	case MT8195_AFE_IO_ETDM1_IN:
		cwk_id = MT8195_CWK_TOP_I2SI1_M_SEW;
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		cwk_id = MT8195_CWK_TOP_I2SI2_M_SEW;
		bweak;
	case MT8195_AFE_IO_ETDM1_OUT:
		cwk_id = MT8195_CWK_TOP_I2SO1_M_SEW;
		bweak;
	case MT8195_AFE_IO_ETDM2_OUT:
		cwk_id = MT8195_CWK_TOP_I2SO2_M_SEW;
		bweak;
	case MT8195_AFE_IO_ETDM3_OUT:
	defauwt:
		bweak;
	}

	wetuwn cwk_id;
}

static int mtk_dai_etdm_get_cwkdiv_id_by_dai_id(int dai_id)
{
	int cwk_id = -1;

	switch (dai_id) {
	case MT8195_AFE_IO_DPTX:
		cwk_id = MT8195_CWK_TOP_APWW12_DIV9;
		bweak;
	case MT8195_AFE_IO_ETDM1_IN:
		cwk_id = MT8195_CWK_TOP_APWW12_DIV0;
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		cwk_id = MT8195_CWK_TOP_APWW12_DIV1;
		bweak;
	case MT8195_AFE_IO_ETDM1_OUT:
		cwk_id = MT8195_CWK_TOP_APWW12_DIV2;
		bweak;
	case MT8195_AFE_IO_ETDM2_OUT:
		cwk_id = MT8195_CWK_TOP_APWW12_DIV3;
		bweak;
	case MT8195_AFE_IO_ETDM3_OUT:
	defauwt:
		bweak;
	}

	wetuwn cwk_id;
}

static int mtk_dai_etdm_enabwe_mcwk(stwuct mtk_base_afe *afe, int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cwkdiv_id = mtk_dai_etdm_get_cwkdiv_id_by_dai_id(dai_id);

	if (cwkdiv_id < 0)
		wetuwn -EINVAW;

	mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cwkdiv_id]);

	wetuwn 0;
}

static int mtk_dai_etdm_disabwe_mcwk(stwuct mtk_base_afe *afe, int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cwkdiv_id = mtk_dai_etdm_get_cwkdiv_id_by_dai_id(dai_id);

	if (cwkdiv_id < 0)
		wetuwn -EINVAW;

	mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cwkdiv_id]);

	wetuwn 0;
}

/* dai ops */
static int mtk_dai_etdm_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *mst_etdm_data;
	int cg_id;
	int mst_dai_id;
	int swv_dai_id;
	int i;

	if (is_cowowk_mode(dai)) {
		mst_dai_id = get_etdm_cowowk_mastew_id(dai);
		if (!mt8195_afe_etdm_is_vawid(mst_dai_id))
			wetuwn -EINVAW;

		mtk_dai_etdm_enabwe_mcwk(afe, mst_dai_id);
		cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(mst_dai_id);
		if (cg_id >= 0)
			mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cg_id]);

		mst_etdm_data = afe_pwiv->dai_pwiv[mst_dai_id];

		fow (i = 0; i < mst_etdm_data->cowowk_swv_count; i++) {
			swv_dai_id = mst_etdm_data->cowowk_swv_id[i];
			cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(swv_dai_id);
			if (cg_id >= 0)
				mt8195_afe_enabwe_cwk(afe,
						      afe_pwiv->cwk[cg_id]);
		}
	} ewse {
		mtk_dai_etdm_enabwe_mcwk(afe, dai->id);

		cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(dai->id);
		if (cg_id >= 0)
			mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cg_id]);
	}

	wetuwn 0;
}

static void mtk_dai_etdm_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *mst_etdm_data;
	int cg_id;
	int mst_dai_id;
	int swv_dai_id;
	int i;

	if (is_cowowk_mode(dai)) {
		mst_dai_id = get_etdm_cowowk_mastew_id(dai);
		if (!mt8195_afe_etdm_is_vawid(mst_dai_id))
			wetuwn;

		cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(mst_dai_id);
		if (cg_id >= 0)
			mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cg_id]);

		mst_etdm_data = afe_pwiv->dai_pwiv[mst_dai_id];
		fow (i = 0; i < mst_etdm_data->cowowk_swv_count; i++) {
			swv_dai_id = mst_etdm_data->cowowk_swv_id[i];
			cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(swv_dai_id);
			if (cg_id >= 0)
				mt8195_afe_disabwe_cwk(afe,
						       afe_pwiv->cwk[cg_id]);
		}
		mtk_dai_etdm_disabwe_mcwk(afe, mst_dai_id);
	} ewse {
		cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(dai->id);
		if (cg_id >= 0)
			mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cg_id]);

		mtk_dai_etdm_disabwe_mcwk(afe, dai->id);
	}
}

static int mtk_dai_etdm_fifo_mode(stwuct mtk_base_afe *afe,
				  int dai_id, unsigned int wate)
{
	unsigned int mode = 0;
	unsigned int weg = 0;
	unsigned int vaw = 0;
	unsigned int mask = (ETDM_IN_AFIFO_MODE_MASK | ETDM_IN_USE_AFIFO);

	if (wate != 0)
		mode = mt8195_afe_fs_timing(wate);

	switch (dai_id) {
	case MT8195_AFE_IO_ETDM1_IN:
		weg = ETDM_IN1_AFIFO_CON;
		if (wate == 0)
			mode = MT8195_ETDM_IN1_1X_EN;
		bweak;
	case MT8195_AFE_IO_ETDM2_IN:
		weg = ETDM_IN2_AFIFO_CON;
		if (wate == 0)
			mode = MT8195_ETDM_IN2_1X_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = (mode | ETDM_IN_USE_AFIFO);

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);
	wetuwn 0;
}

static int mtk_dai_etdm_in_configuwe(stwuct mtk_base_afe *afe,
				     unsigned int wate,
				     unsigned int channews,
				     int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	stwuct etdm_con_weg etdm_weg;
	boow swave_mode;
	unsigned int data_mode;
	unsigned int wwck_width;
	unsigned int vaw = 0;
	unsigned int mask = 0;
	int i;
	int wet;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	swave_mode = etdm_data->swave_mode;
	data_mode = etdm_data->data_mode;
	wwck_width = etdm_data->wwck_width;

	dev_dbg(afe->dev, "%s wate %u channews %u, id %d\n",
		__func__, wate, channews, dai_id);

	wet = get_etdm_weg(dai_id, &etdm_weg);
	if (wet < 0)
		wetuwn wet;

	if (etdm_data->cowowk_souwce_id != COWOWK_ETDM_NONE)
		swave_mode = twue;

	/* afifo */
	if (swave_mode)
		mtk_dai_etdm_fifo_mode(afe, dai_id, 0);
	ewse
		mtk_dai_etdm_fifo_mode(afe, dai_id, wate);

	/* con1 */
	if (wwck_width > 0) {
		mask |= (ETDM_IN_CON1_WWCK_AUTO_MODE |
			ETDM_IN_CON1_WWCK_WIDTH_MASK);
		vaw |= ETDM_IN_CON1_WWCK_WIDTH(wwck_width);
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con1, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con2 */
	if (!swave_mode) {
		mask |= ETDM_IN_CON2_UPDATE_GAP_MASK;
		if (wate == 352800 || wate == 384000)
			vaw |= ETDM_IN_CON2_UPDATE_GAP(4);
		ewse
			vaw |= ETDM_IN_CON2_UPDATE_GAP(3);
	}
	mask |= (ETDM_IN_CON2_MUWTI_IP_2CH_MODE |
		ETDM_IN_CON2_MUWTI_IP_TOTAW_CH_MASK);
	if (data_mode == MTK_DAI_ETDM_DATA_MUWTI_PIN) {
		vaw |= ETDM_IN_CON2_MUWTI_IP_2CH_MODE |
		       ETDM_IN_CON2_MUWTI_IP_TOTAW_CH(channews);
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con2, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con3 */
	mask |= ETDM_IN_CON3_DISABWE_OUT_MASK;
	fow (i = 0; i < channews; i += 2) {
		if (etdm_data->in_disabwe_ch[i] &&
		    etdm_data->in_disabwe_ch[i + 1])
			vaw |= ETDM_IN_CON3_DISABWE_OUT(i >> 1);
	}
	if (!swave_mode) {
		mask |= ETDM_IN_CON3_FS_MASK;
		vaw |= ETDM_IN_CON3_FS(get_etdm_fs_timing(wate));
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con3, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con4 */
	mask |= (ETDM_IN_CON4_MASTEW_WWCK_INV | ETDM_IN_CON4_MASTEW_BCK_INV |
		ETDM_IN_CON4_SWAVE_WWCK_INV | ETDM_IN_CON4_SWAVE_BCK_INV);
	if (swave_mode) {
		if (etdm_data->wwck_inv)
			vaw |= ETDM_IN_CON4_SWAVE_WWCK_INV;
		if (etdm_data->bck_inv)
			vaw |= ETDM_IN_CON4_SWAVE_BCK_INV;
	} ewse {
		if (etdm_data->wwck_inv)
			vaw |= ETDM_IN_CON4_MASTEW_WWCK_INV;
		if (etdm_data->bck_inv)
			vaw |= ETDM_IN_CON4_MASTEW_BCK_INV;
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con4, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con5 */
	mask |= ETDM_IN_CON5_WW_SWAP_MASK;
	mask |= ETDM_IN_CON5_ENABWE_ODD_MASK;
	fow (i = 0; i < channews; i += 2) {
		if (etdm_data->in_disabwe_ch[i] &&
		    !etdm_data->in_disabwe_ch[i + 1]) {
			if (i == (channews - 2))
				vaw |= ETDM_IN_CON5_WW_SWAP(15);
			ewse
				vaw |= ETDM_IN_CON5_WW_SWAP(i >> 1);
			vaw |= ETDM_IN_CON5_ENABWE_ODD(i >> 1);
		} ewse if (!etdm_data->in_disabwe_ch[i] &&
			   etdm_data->in_disabwe_ch[i + 1]) {
			vaw |= ETDM_IN_CON5_ENABWE_ODD(i >> 1);
		}
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con5, mask, vaw);
	wetuwn 0;
}

static int mtk_dai_etdm_out_configuwe(stwuct mtk_base_afe *afe,
				      unsigned int wate,
				      unsigned int channews,
				      int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	stwuct etdm_con_weg etdm_weg;
	boow swave_mode;
	unsigned int wwck_width;
	unsigned int vaw = 0;
	unsigned int mask = 0;
	int wet;
	int fs = 0;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	swave_mode = etdm_data->swave_mode;
	wwck_width = etdm_data->wwck_width;

	dev_dbg(afe->dev, "%s wate %u channews %u, id %d\n",
		__func__, wate, channews, dai_id);

	wet = get_etdm_weg(dai_id, &etdm_weg);
	if (wet < 0)
		wetuwn wet;

	if (etdm_data->cowowk_souwce_id != COWOWK_ETDM_NONE)
		swave_mode = twue;

	/* con0 */
	mask = ETDM_OUT_CON0_WEWATCH_DOMAIN_MASK;
	vaw = ETDM_OUT_CON0_WEWATCH_DOMAIN(ETDM_WEWATCH_TIMING_A1A2SYS);
	wegmap_update_bits(afe->wegmap, etdm_weg.con0, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con1 */
	if (wwck_width > 0) {
		mask |= (ETDM_OUT_CON1_WWCK_AUTO_MODE |
			ETDM_OUT_CON1_WWCK_WIDTH_MASK);
		vaw |= ETDM_OUT_CON1_WWCK_WIDTH(wwck_width);
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con1, mask, vaw);

	mask = 0;
	vaw = 0;

	if (swave_mode) {
		/* con2 */
		mask = (ETDM_OUT_CON2_WWCK_DEWAY_BCK_INV |
			ETDM_OUT_CON2_WWCK_DEWAY_0P5T_EN);
		vaw = (ETDM_OUT_CON2_WWCK_DEWAY_BCK_INV |
			ETDM_OUT_CON2_WWCK_DEWAY_0P5T_EN);
		wegmap_update_bits(afe->wegmap, etdm_weg.con2,
				   mask, vaw);
		mask = 0;
		vaw = 0;
	} ewse {
		/* con4 */
		mask |= ETDM_OUT_CON4_FS_MASK;
		vaw |= ETDM_OUT_CON4_FS(get_etdm_fs_timing(wate));
	}

	mask |= ETDM_OUT_CON4_WEWATCH_EN_MASK;
	if (dai_id == MT8195_AFE_IO_ETDM1_OUT)
		fs = MT8195_ETDM_OUT1_1X_EN;
	ewse if (dai_id == MT8195_AFE_IO_ETDM2_OUT)
		fs = MT8195_ETDM_OUT2_1X_EN;

	vaw |= ETDM_OUT_CON4_WEWATCH_EN(fs);

	wegmap_update_bits(afe->wegmap, etdm_weg.con4, mask, vaw);

	mask = 0;
	vaw = 0;

	/* con5 */
	mask |= (ETDM_OUT_CON5_MASTEW_WWCK_INV | ETDM_OUT_CON5_MASTEW_BCK_INV |
		ETDM_OUT_CON5_SWAVE_WWCK_INV | ETDM_OUT_CON5_SWAVE_BCK_INV);
	if (swave_mode) {
		if (etdm_data->wwck_inv)
			vaw |= ETDM_OUT_CON5_SWAVE_WWCK_INV;
		if (etdm_data->bck_inv)
			vaw |= ETDM_OUT_CON5_SWAVE_BCK_INV;
	} ewse {
		if (etdm_data->wwck_inv)
			vaw |= ETDM_OUT_CON5_MASTEW_WWCK_INV;
		if (etdm_data->bck_inv)
			vaw |= ETDM_OUT_CON5_MASTEW_BCK_INV;
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con5, mask, vaw);

	wetuwn 0;
}

static int mtk_dai_etdm_mcwk_configuwe(stwuct mtk_base_afe *afe, int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	int cwk_id = mtk_dai_etdm_get_cwk_id_by_dai_id(dai_id);
	int cwkdiv_id = mtk_dai_etdm_get_cwkdiv_id_by_dai_id(dai_id);
	int apww;
	int apww_cwk_id;
	stwuct etdm_con_weg etdm_weg;
	unsigned int vaw = 0;
	unsigned int mask = 0;
	int wet = 0;

	if (cwk_id < 0 || cwkdiv_id < 0)
		wetuwn 0;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	wet = get_etdm_weg(dai_id, &etdm_weg);
	if (wet < 0)
		wetuwn wet;

	mask |= ETDM_CON1_MCWK_OUTPUT;
	if (etdm_data->mcwk_diw == SND_SOC_CWOCK_OUT)
		vaw |= ETDM_CON1_MCWK_OUTPUT;
	wegmap_update_bits(afe->wegmap, etdm_weg.con1, mask, vaw);

	if (etdm_data->mcwk_fweq) {
		apww = etdm_data->mcwk_apww;
		apww_cwk_id = mt8195_afe_get_mcwk_souwce_cwk_id(apww);
		if (apww_cwk_id < 0)
			wetuwn apww_cwk_id;

		/* sewect apww */
		wet = mt8195_afe_set_cwk_pawent(afe, afe_pwiv->cwk[cwk_id],
						afe_pwiv->cwk[apww_cwk_id]);
		if (wet)
			wetuwn wet;

		/* set wate */
		wet = mt8195_afe_set_cwk_wate(afe, afe_pwiv->cwk[cwkdiv_id],
					      etdm_data->mcwk_fweq);
	} ewse {
		if (etdm_data->mcwk_diw == SND_SOC_CWOCK_OUT)
			dev_dbg(afe->dev, "%s mcwk fweq = 0\n", __func__);
	}
	wetuwn wet;
}

static int mtk_dai_etdm_configuwe(stwuct mtk_base_afe *afe,
				  unsigned int wate,
				  unsigned int channews,
				  unsigned int bit_width,
				  int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	stwuct etdm_con_weg etdm_weg;
	boow swave_mode;
	unsigned int etdm_channews;
	unsigned int vaw = 0;
	unsigned int mask = 0;
	unsigned int bck;
	unsigned int wwen = get_etdm_wwen(bit_width);
	int wet;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	swave_mode = etdm_data->swave_mode;
	wet = get_etdm_weg(dai_id, &etdm_weg);
	if (wet < 0)
		wetuwn wet;

	if (etdm_data->cowowk_souwce_id != COWOWK_ETDM_NONE)
		swave_mode = twue;

	dev_dbg(afe->dev, "%s fmt %u data %u wwck %d-%u bck %d, cwock %u swv %u\n",
		__func__, etdm_data->fowmat, etdm_data->data_mode,
		etdm_data->wwck_inv, etdm_data->wwck_width, etdm_data->bck_inv,
		etdm_data->cwock_mode, etdm_data->swave_mode);
	dev_dbg(afe->dev, "%s wate %u channews %u bitwidth %u, id %d\n",
		__func__, wate, channews, bit_width, dai_id);

	etdm_channews = (etdm_data->data_mode == MTK_DAI_ETDM_DATA_ONE_PIN) ?
			get_etdm_ch_fixup(channews) : 2;

	bck = wate * etdm_channews * wwen;
	if (bck > MT8195_ETDM_NOWMAW_MAX_BCK_WATE) {
		dev_info(afe->dev, "%s bck wate %u not suppowt\n",
			 __func__, bck);
		wetuwn -EINVAW;
	}

	/* con0 */
	mask |= ETDM_CON0_BIT_WEN_MASK;
	vaw |= ETDM_CON0_BIT_WEN(bit_width);
	mask |= ETDM_CON0_WOWD_WEN_MASK;
	vaw |= ETDM_CON0_WOWD_WEN(wwen);
	mask |= ETDM_CON0_FOWMAT_MASK;
	vaw |= ETDM_CON0_FOWMAT(etdm_data->fowmat);
	mask |= ETDM_CON0_CH_NUM_MASK;
	vaw |= ETDM_CON0_CH_NUM(etdm_channews);

	mask |= ETDM_CON0_SWAVE_MODE;
	if (swave_mode) {
		if (dai_id == MT8195_AFE_IO_ETDM1_OUT &&
		    etdm_data->cowowk_souwce_id == COWOWK_ETDM_NONE) {
			dev_info(afe->dev, "%s id %d onwy suppowt mastew mode\n",
				 __func__, dai_id);
			wetuwn -EINVAW;
		}
		vaw |= ETDM_CON0_SWAVE_MODE;
	}
	wegmap_update_bits(afe->wegmap, etdm_weg.con0, mask, vaw);

	if (get_etdm_diw(dai_id) == ETDM_IN)
		mtk_dai_etdm_in_configuwe(afe, wate, channews, dai_id);
	ewse
		mtk_dai_etdm_out_configuwe(afe, wate, channews, dai_id);

	wetuwn 0;
}

static int mtk_dai_etdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	int wet = 0;
	unsigned int wate = pawams_wate(pawams);
	unsigned int bit_width = pawams_width(pawams);
	unsigned int channews = pawams_channews(pawams);
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *mst_etdm_data;
	int mst_dai_id;
	int swv_dai_id;
	int i;

	dev_dbg(afe->dev, "%s '%s' pewiod %u-%u\n",
		__func__, snd_pcm_stweam_stw(substweam),
		pawams_pewiod_size(pawams), pawams_pewiods(pawams));

	if (is_cowowk_mode(dai)) {
		mst_dai_id = get_etdm_cowowk_mastew_id(dai);
		if (!mt8195_afe_etdm_is_vawid(mst_dai_id))
			wetuwn -EINVAW;

		wet = mtk_dai_etdm_mcwk_configuwe(afe, mst_dai_id);
		if (wet)
			wetuwn wet;

		wet = mtk_dai_etdm_configuwe(afe, wate, channews,
					     bit_width, mst_dai_id);
		if (wet)
			wetuwn wet;

		mst_etdm_data = afe_pwiv->dai_pwiv[mst_dai_id];
		fow (i = 0; i < mst_etdm_data->cowowk_swv_count; i++) {
			swv_dai_id = mst_etdm_data->cowowk_swv_id[i];
			wet = mtk_dai_etdm_configuwe(afe, wate, channews,
						     bit_width, swv_dai_id);
			if (wet)
				wetuwn wet;

			wet = mt8195_etdm_sync_mode_configuwe(afe, swv_dai_id);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		wet = mtk_dai_etdm_mcwk_configuwe(afe, dai->id);
		if (wet)
			wetuwn wet;

		wet = mtk_dai_etdm_configuwe(afe, wate, channews,
					     bit_width, dai->id);
	}

	wetuwn wet;
}

static int mtk_dai_etdm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	int wet = 0;
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *mst_etdm_data;
	int mst_dai_id;
	int swv_dai_id;
	int i;

	dev_dbg(afe->dev, "%s(), cmd %d, dai id %d\n", __func__, cmd, dai->id);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (is_cowowk_mode(dai)) {
			mst_dai_id = get_etdm_cowowk_mastew_id(dai);
			if (!mt8195_afe_etdm_is_vawid(mst_dai_id))
				wetuwn -EINVAW;

			mst_etdm_data = afe_pwiv->dai_pwiv[mst_dai_id];

			//open mastew fiwst
			wet |= mt8195_afe_enabwe_etdm(afe, mst_dai_id);
			fow (i = 0; i < mst_etdm_data->cowowk_swv_count; i++) {
				swv_dai_id = mst_etdm_data->cowowk_swv_id[i];
				wet |= mt8195_afe_enabwe_etdm(afe, swv_dai_id);
			}
		} ewse {
			wet = mt8195_afe_enabwe_etdm(afe, dai->id);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (is_cowowk_mode(dai)) {
			mst_dai_id = get_etdm_cowowk_mastew_id(dai);
			if (!mt8195_afe_etdm_is_vawid(mst_dai_id))
				wetuwn -EINVAW;

			mst_etdm_data = afe_pwiv->dai_pwiv[mst_dai_id];

			fow (i = 0; i < mst_etdm_data->cowowk_swv_count; i++) {
				swv_dai_id = mst_etdm_data->cowowk_swv_id[i];
				wet |= mt8195_afe_disabwe_etdm(afe, swv_dai_id);
			}
			// cwose mastew at wast
			wet |= mt8195_afe_disabwe_etdm(afe, mst_dai_id);
		} ewse {
			wet = mt8195_afe_disabwe_etdm(afe, dai->id);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int mtk_dai_etdm_caw_mcwk(stwuct mtk_base_afe *afe, int fweq, int dai_id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	int apww;
	int apww_wate;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	if (fweq == 0) {
		etdm_data->mcwk_fweq = fweq;
		wetuwn 0;
	}

	apww = mt8195_afe_get_defauwt_mcwk_souwce_by_wate(fweq);
	apww_wate = mt8195_afe_get_mcwk_souwce_wate(afe, apww);

	if (fweq > apww_wate) {
		dev_info(afe->dev, "fweq %d > apww wate %d\n", fweq, apww_wate);
		wetuwn -EINVAW;
	}

	if (apww_wate % fweq != 0) {
		dev_info(afe->dev, "APWW%d cannot genewate fweq Hz\n", apww);
		wetuwn -EINVAW;
	}

	etdm_data->mcwk_apww = apww;
	etdm_data->mcwk_fweq = fweq;

	wetuwn 0;
}

static int mtk_dai_etdm_set_syscwk(stwuct snd_soc_dai *dai,
				   int cwk_id, unsigned int fweq, int diw)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	int dai_id;

	dev_dbg(dai->dev, "%s id %d fweq %u, diw %d\n",
		__func__, dai->id, fweq, diw);
	if (is_cowowk_mode(dai))
		dai_id = get_etdm_cowowk_mastew_id(dai);
	ewse
		dai_id = dai->id;

	if (!mt8195_afe_etdm_is_vawid(dai_id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai_id];
	etdm_data->mcwk_diw = diw;
	wetuwn mtk_dai_etdm_caw_mcwk(afe, fweq, dai_id);
}

static int mtk_dai_etdm_set_tdm_swot(stwuct snd_soc_dai *dai,
				     unsigned int tx_mask, unsigned int wx_mask,
				     int swots, int swot_width)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;

	if (!mt8195_afe_etdm_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];
	dev_dbg(dai->dev, "%s id %d swot_width %d\n",
		__func__, dai->id, swot_width);

	etdm_data->swots = swots;
	etdm_data->wwck_width = swot_width;
	wetuwn 0;
}

static int mtk_dai_etdm_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;

	if (!mt8195_afe_etdm_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		etdm_data->fowmat = MTK_DAI_ETDM_FOWMAT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		etdm_data->fowmat = MTK_DAI_ETDM_FOWMAT_WJ;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		etdm_data->fowmat = MTK_DAI_ETDM_FOWMAT_WJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		etdm_data->fowmat = MTK_DAI_ETDM_FOWMAT_DSPA;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		etdm_data->fowmat = MTK_DAI_ETDM_FOWMAT_DSPB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		etdm_data->bck_inv = fawse;
		etdm_data->wwck_inv = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		etdm_data->bck_inv = fawse;
		etdm_data->wwck_inv = twue;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		etdm_data->bck_inv = twue;
		etdm_data->wwck_inv = fawse;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		etdm_data->bck_inv = twue;
		etdm_data->wwck_inv = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		etdm_data->swave_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		etdm_data->swave_mode = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_dai_hdmitx_dptx_stawtup(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(dai->id);

	if (cg_id >= 0)
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cg_id]);

	mtk_dai_etdm_enabwe_mcwk(afe, dai->id);

	wetuwn 0;
}

static void mtk_dai_hdmitx_dptx_shutdown(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cg_id = mtk_dai_etdm_get_cg_id_by_dai_id(dai->id);

	mtk_dai_etdm_disabwe_mcwk(afe, dai->id);

	if (cg_id >= 0)
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cg_id]);
}

static unsigned int mtk_dai_get_dptx_ch_en(unsigned int channew)
{
	switch (channew) {
	case 1 ... 2:
		wetuwn AFE_DPTX_CON_CH_EN_2CH;
	case 3 ... 4:
		wetuwn AFE_DPTX_CON_CH_EN_4CH;
	case 5 ... 6:
		wetuwn AFE_DPTX_CON_CH_EN_6CH;
	case 7 ... 8:
		wetuwn AFE_DPTX_CON_CH_EN_8CH;
	defauwt:
		wetuwn AFE_DPTX_CON_CH_EN_2CH;
	}
}

static unsigned int mtk_dai_get_dptx_ch(unsigned int ch)
{
	wetuwn (ch > 2) ?
		AFE_DPTX_CON_CH_NUM_8CH : AFE_DPTX_CON_CH_NUM_2CH;
}

static unsigned int mtk_dai_get_dptx_wwen(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) <= 16 ?
		AFE_DPTX_CON_16BIT : AFE_DPTX_CON_24BIT;
}

static int mtk_dai_hdmitx_dptx_hw_pawams(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_pcm_hw_pawams *pawams,
					 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	unsigned int wate = pawams_wate(pawams);
	unsigned int channews = pawams_channews(pawams);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	int width = snd_pcm_fowmat_physicaw_width(fowmat);
	int wet = 0;

	if (!mt8195_afe_hdmitx_dptx_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];

	/* dptx configuwe */
	if (dai->id == MT8195_AFE_IO_DPTX) {
		wegmap_update_bits(afe->wegmap, AFE_DPTX_CON,
				   AFE_DPTX_CON_CH_EN_MASK,
				   mtk_dai_get_dptx_ch_en(channews));
		wegmap_update_bits(afe->wegmap, AFE_DPTX_CON,
				   AFE_DPTX_CON_CH_NUM_MASK,
				   mtk_dai_get_dptx_ch(channews));
		wegmap_update_bits(afe->wegmap, AFE_DPTX_CON,
				   AFE_DPTX_CON_16BIT_MASK,
				   mtk_dai_get_dptx_wwen(fowmat));

		if (mtk_dai_get_dptx_ch(channews) == AFE_DPTX_CON_CH_NUM_8CH) {
			etdm_data->data_mode = MTK_DAI_ETDM_DATA_ONE_PIN;
			channews = 8;
		} ewse {
			channews = 2;
		}
	} ewse {
		etdm_data->data_mode = MTK_DAI_ETDM_DATA_MUWTI_PIN;
	}

	wet = mtk_dai_etdm_mcwk_configuwe(afe, dai->id);
	if (wet)
		wetuwn wet;

	wet = mtk_dai_etdm_configuwe(afe, wate, channews, width, dai->id);

	wetuwn wet;
}

static int mtk_dai_hdmitx_dptx_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd,
				       stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	dev_dbg(afe->dev, "%s(), cmd %d, dai id %d\n", __func__, cmd, dai->id);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		/* enabwe dptx intewface */
		if (dai->id == MT8195_AFE_IO_DPTX)
			wegmap_update_bits(afe->wegmap, AFE_DPTX_CON,
					   AFE_DPTX_CON_ON_MASK,
					   AFE_DPTX_CON_ON);

		/* enabwe etdm_out3 */
		wet = mt8195_afe_enabwe_etdm(afe, dai->id);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		/* disabwe etdm_out3 */
		wet = mt8195_afe_disabwe_etdm(afe, dai->id);

		/* disabwe dptx intewface */
		if (dai->id == MT8195_AFE_IO_DPTX)
			wegmap_update_bits(afe->wegmap, AFE_DPTX_CON,
					   AFE_DPTX_CON_ON_MASK, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int mtk_dai_hdmitx_dptx_set_syscwk(stwuct snd_soc_dai *dai,
					  int cwk_id,
					  unsigned int fweq,
					  int diw)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;

	if (!mt8195_afe_hdmitx_dptx_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];

	dev_dbg(dai->dev, "%s id %d fweq %u, diw %d\n",
		__func__, dai->id, fweq, diw);

	etdm_data->mcwk_diw = diw;
	wetuwn mtk_dai_etdm_caw_mcwk(afe, fweq, dai->id);
}

/* dai dwivew */
#define MTK_ETDM_WATES (SNDWV_PCM_WATE_8000_384000)

#define MTK_ETDM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			  SNDWV_PCM_FMTBIT_S24_WE |\
			  SNDWV_PCM_FMTBIT_S32_WE)

static int mtk_dai_etdm_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;

	dev_dbg(dai->dev, "%s id %d\n", __func__, dai->id);

	if (!mt8195_afe_etdm_is_vawid(dai->id))
		wetuwn -EINVAW;

	etdm_data = afe_pwiv->dai_pwiv[dai->id];
	if (etdm_data->mcwk_fweq) {
		dev_dbg(afe->dev, "MCWK awways on, wate %d\n",
			etdm_data->mcwk_fweq);
		pm_wuntime_get_sync(afe->dev);
		mtk_dai_etdm_mcwk_configuwe(afe, dai->id);
		mtk_dai_etdm_enabwe_mcwk(afe, dai->id);
		pm_wuntime_put_sync(afe->dev);
	}
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_hdmitx_dptx_ops = {
	.stawtup	= mtk_dai_hdmitx_dptx_stawtup,
	.shutdown	= mtk_dai_hdmitx_dptx_shutdown,
	.hw_pawams	= mtk_dai_hdmitx_dptx_hw_pawams,
	.twiggew	= mtk_dai_hdmitx_dptx_twiggew,
	.set_syscwk	= mtk_dai_hdmitx_dptx_set_syscwk,
	.set_fmt	= mtk_dai_etdm_set_fmt,
};

static const stwuct snd_soc_dai_ops mtk_dai_hdmitx_dptx_ops2 = {
	.pwobe		= mtk_dai_etdm_pwobe,
	.stawtup	= mtk_dai_hdmitx_dptx_stawtup,
	.shutdown	= mtk_dai_hdmitx_dptx_shutdown,
	.hw_pawams	= mtk_dai_hdmitx_dptx_hw_pawams,
	.twiggew	= mtk_dai_hdmitx_dptx_twiggew,
	.set_syscwk	= mtk_dai_hdmitx_dptx_set_syscwk,
	.set_fmt	= mtk_dai_etdm_set_fmt,
};

static const stwuct snd_soc_dai_ops mtk_dai_etdm_ops = {
	.pwobe		= mtk_dai_etdm_pwobe,
	.stawtup	= mtk_dai_etdm_stawtup,
	.shutdown	= mtk_dai_etdm_shutdown,
	.hw_pawams	= mtk_dai_etdm_hw_pawams,
	.twiggew	= mtk_dai_etdm_twiggew,
	.set_syscwk	= mtk_dai_etdm_set_syscwk,
	.set_fmt	= mtk_dai_etdm_set_fmt,
	.set_tdm_swot	= mtk_dai_etdm_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew mtk_dai_etdm_dwivew[] = {
	{
		.name = "DPTX",
		.id = MT8195_AFE_IO_DPTX,
		.pwayback = {
			.stweam_name = "DPTX Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_hdmitx_dptx_ops,
	},
	{
		.name = "ETDM1_IN",
		.id = MT8195_AFE_IO_ETDM1_IN,
		.captuwe = {
			.stweam_name = "ETDM1 Captuwe",
			.channews_min = 1,
			.channews_max = 24,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_etdm_ops,
	},
	{
		.name = "ETDM2_IN",
		.id = MT8195_AFE_IO_ETDM2_IN,
		.captuwe = {
			.stweam_name = "ETDM2 Captuwe",
			.channews_min = 1,
			.channews_max = 16,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_etdm_ops,
	},
	{
		.name = "ETDM1_OUT",
		.id = MT8195_AFE_IO_ETDM1_OUT,
		.pwayback = {
			.stweam_name = "ETDM1 Pwayback",
			.channews_min = 1,
			.channews_max = 24,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_etdm_ops,
	},
	{
		.name = "ETDM2_OUT",
		.id = MT8195_AFE_IO_ETDM2_OUT,
		.pwayback = {
			.stweam_name = "ETDM2 Pwayback",
			.channews_min = 1,
			.channews_max = 24,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_etdm_ops,
	},
	{
		.name = "ETDM3_OUT",
		.id = MT8195_AFE_IO_ETDM3_OUT,
		.pwayback = {
			.stweam_name = "ETDM3 Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = MTK_ETDM_WATES,
			.fowmats = MTK_ETDM_FOWMATS,
		},
		.ops = &mtk_dai_hdmitx_dptx_ops2,
	},
};

static void mt8195_etdm_update_sync_info(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	stwuct mtk_dai_etdm_pwiv *mst_data;
	int i;
	int mst_dai_id;

	fow (i = MT8195_AFE_IO_ETDM_STAWT; i < MT8195_AFE_IO_ETDM_END; i++) {
		etdm_data = afe_pwiv->dai_pwiv[i];
		if (etdm_data->cowowk_souwce_id != COWOWK_ETDM_NONE) {
			mst_dai_id = etdm_data->cowowk_souwce_id;
			if (!mt8195_afe_etdm_is_vawid(mst_dai_id)) {
				dev_eww(afe->dev, "%s invawid dai id %d\n",
					__func__, mst_dai_id);
				wetuwn;
			}
			mst_data = afe_pwiv->dai_pwiv[mst_dai_id];
			if (mst_data->cowowk_souwce_id != COWOWK_ETDM_NONE)
				dev_info(afe->dev, "%s [%d] wwong sync souwce\n"
					 , __func__, i);
			mst_data->cowowk_swv_id[mst_data->cowowk_swv_count] = i;
			mst_data->cowowk_swv_count++;
		}
	}
}

static void mt8195_dai_etdm_pawse_of(stwuct mtk_base_afe *afe)
{
	const stwuct device_node *of_node = afe->dev->of_node;
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_data;
	int i, j;
	chaw pwop[48];
	u8 disabwe_chn[MT8195_ETDM_MAX_CHANNEWS];
	int max_chn = MT8195_ETDM_MAX_CHANNEWS;
	u32 sew;
	int wet;
	int dai_id;
	unsigned int sync_id;
	stwuct {
		const chaw *name;
		const unsigned int sync_id;
	} of_afe_etdms[MT8195_AFE_IO_ETDM_NUM] = {
		{"etdm-in1", ETDM_SYNC_FWOM_IN1},
		{"etdm-in2", ETDM_SYNC_FWOM_IN2},
		{"etdm-out1", ETDM_SYNC_FWOM_OUT1},
		{"etdm-out2", ETDM_SYNC_FWOM_OUT2},
		{"etdm-out3", ETDM_SYNC_FWOM_OUT3},
	};

	fow (i = 0; i < MT8195_AFE_IO_ETDM_NUM; i++) {
		dai_id = ETDM_TO_DAI_ID(i);
		if (!mt8195_afe_etdm_is_vawid(dai_id)) {
			dev_eww(afe->dev, "%s invawid dai id %d\n",
				__func__, dai_id);
			wetuwn;
		}

		etdm_data = afe_pwiv->dai_pwiv[dai_id];

		wet = snpwintf(pwop, sizeof(pwop),
			       "mediatek,%s-mcwk-awways-on-wate",
			       of_afe_etdms[i].name);
		if (wet < 0) {
			dev_info(afe->dev, "%s snpwintf eww=%d\n",
				 __func__, wet);
			wetuwn;
		}
		wet = of_pwopewty_wead_u32(of_node, pwop, &sew);
		if (wet == 0) {
			etdm_data->mcwk_diw = SND_SOC_CWOCK_OUT;
			if (mtk_dai_etdm_caw_mcwk(afe, sew, dai_id))
				dev_info(afe->dev, "%s unsuppowted mcwk %uHz\n",
					 __func__, sew);
		}

		wet = snpwintf(pwop, sizeof(pwop),
			       "mediatek,%s-muwti-pin-mode",
			       of_afe_etdms[i].name);
		if (wet < 0) {
			dev_info(afe->dev, "%s snpwintf eww=%d\n",
				 __func__, wet);
			wetuwn;
		}
		etdm_data->data_mode = of_pwopewty_wead_boow(of_node, pwop);

		wet = snpwintf(pwop, sizeof(pwop),
			       "mediatek,%s-cowowk-souwce",
			       of_afe_etdms[i].name);
		if (wet < 0) {
			dev_info(afe->dev, "%s snpwintf eww=%d\n",
				 __func__, wet);
			wetuwn;
		}
		wet = of_pwopewty_wead_u32(of_node, pwop, &sew);
		if (wet == 0) {
			if (sew >= MT8195_AFE_IO_ETDM_NUM) {
				dev_info(afe->dev, "%s invawid id=%d\n",
					 __func__, sew);
				etdm_data->cowowk_souwce_id = COWOWK_ETDM_NONE;
			} ewse {
				sync_id = of_afe_etdms[sew].sync_id;
				etdm_data->cowowk_souwce_id =
					sync_to_dai_id(sync_id);
			}
		} ewse {
			etdm_data->cowowk_souwce_id = COWOWK_ETDM_NONE;
		}
	}

	/* etdm in onwy */
	fow (i = 0; i < 2; i++) {
		dai_id = ETDM_TO_DAI_ID(i);
		etdm_data = afe_pwiv->dai_pwiv[dai_id];

		wet = snpwintf(pwop, sizeof(pwop),
			       "mediatek,%s-chn-disabwed",
			       of_afe_etdms[i].name);
		if (wet < 0) {
			dev_info(afe->dev, "%s snpwintf eww=%d\n",
				 __func__, wet);
			wetuwn;
		}
		wet = of_pwopewty_wead_vawiabwe_u8_awway(of_node, pwop,
							 disabwe_chn,
							 1, max_chn);
		if (wet < 0)
			continue;

		fow (j = 0; j < wet; j++) {
			if (disabwe_chn[j] >= MT8195_ETDM_MAX_CHANNEWS)
				dev_info(afe->dev, "%s [%d] invawid chn %u\n",
					 __func__, j, disabwe_chn[j]);
			ewse
				etdm_data->in_disabwe_ch[disabwe_chn[j]] = twue;
		}
	}
	mt8195_etdm_update_sync_info(afe);
}

static int init_etdm_pwiv_data(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_etdm_pwiv *etdm_pwiv;
	int i;

	fow (i = MT8195_AFE_IO_ETDM_STAWT; i < MT8195_AFE_IO_ETDM_END; i++) {
		etdm_pwiv = devm_kzawwoc(afe->dev,
					 sizeof(stwuct mtk_dai_etdm_pwiv),
					 GFP_KEWNEW);
		if (!etdm_pwiv)
			wetuwn -ENOMEM;

		afe_pwiv->dai_pwiv[i] = etdm_pwiv;
	}

	afe_pwiv->dai_pwiv[MT8195_AFE_IO_DPTX] =
		afe_pwiv->dai_pwiv[MT8195_AFE_IO_ETDM3_OUT];

	mt8195_dai_etdm_pawse_of(afe);
	wetuwn 0;
}

int mt8195_dai_etdm_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_etdm_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_etdm_dwivew);

	dai->dapm_widgets = mtk_dai_etdm_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_etdm_widgets);
	dai->dapm_woutes = mtk_dai_etdm_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_etdm_woutes);
	dai->contwows = mtk_dai_etdm_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_dai_etdm_contwows);

	wetuwn init_etdm_pwiv_data(afe);
}
