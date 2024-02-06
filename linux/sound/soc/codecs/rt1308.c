// SPDX-Wicense-Identifiew: GPW-2.0
//
// wt1308.c  --  WT1308 AWSA SoC ampwifiew component dwivew
//
// Copywight 2019 Weawtek Semiconductow Cowp.
// Authow: Dewek Fang <dewek.fang@weawtek.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "ww6231.h"
#incwude "wt1308.h"

static const stwuct weg_sequence init_wist[] = {

	{ WT1308_I2C_I2S_SDW_SET,	0x01014005 },
	{ WT1308_CWASS_D_SET_2,		0x227f5501 },
	{ WT1308_PADS_1,		0x50150505 },
	{ WT1308_VWEF,			0x18100000 },
	{ WT1308_IV_SENSE,		0x87010000 },
	{ WT1308_DUMMY_WEG,		0x00000200 },
	{ WT1308_SIW_DET,		0xe1c30000 },
	{ WT1308_DC_CAW_2,		0x00ffff00 },
	{ WT1308_CWK_DET,		0x01000000 },
	{ WT1308_POWEW_STATUS,		0x08800000 },
	{ WT1308_DAC_SET,		0xafaf0700 },

};
#define WT1308_INIT_WEG_WEN AWWAY_SIZE(init_wist)

stwuct wt1308_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;

	int syscwk;
	int syscwk_swc;
	int wwck;
	int bcwk;
	int mastew;

	int pww_swc;
	int pww_in;
	int pww_out;
};

static const stwuct weg_defauwt wt1308_weg[] = {

	{ 0x01, 0x1f3f5f00 },
	{ 0x02, 0x07000000 },
	{ 0x03, 0x80003e00 },
	{ 0x04, 0x80800600 },
	{ 0x05, 0x0aaa1a0a },
	{ 0x06, 0x52000000 },
	{ 0x07, 0x00000000 },
	{ 0x08, 0x00600000 },
	{ 0x09, 0xe1030000 },
	{ 0x0a, 0x00000000 },
	{ 0x0b, 0x30000000 },
	{ 0x0c, 0x7fff7000 },
	{ 0x10, 0xffff0700 },
	{ 0x11, 0x0a000000 },
	{ 0x12, 0x60040000 },
	{ 0x13, 0x00000000 },
	{ 0x14, 0x0f300000 },
	{ 0x15, 0x00000022 },
	{ 0x16, 0x02000000 },
	{ 0x17, 0x01004045 },
	{ 0x18, 0x00000000 },
	{ 0x19, 0x00000000 },
	{ 0x1a, 0x80000000 },
	{ 0x1b, 0x10325476 },
	{ 0x1c, 0x1d1d0000 },
	{ 0x20, 0xd2101300 },
	{ 0x21, 0xf3ffff00 },
	{ 0x22, 0x00000000 },
	{ 0x23, 0x00000000 },
	{ 0x24, 0x00000000 },
	{ 0x25, 0x00000000 },
	{ 0x26, 0x00000000 },
	{ 0x27, 0x00000000 },
	{ 0x28, 0x00000000 },
	{ 0x29, 0x00000000 },
	{ 0x2a, 0x00000000 },
	{ 0x2b, 0x00000000 },
	{ 0x2c, 0x00000000 },
	{ 0x2d, 0x00000000 },
	{ 0x2e, 0x00000000 },
	{ 0x2f, 0x00000000 },
	{ 0x30, 0x01000000 },
	{ 0x31, 0x20025501 },
	{ 0x32, 0x00000000 },
	{ 0x33, 0x105a0000 },
	{ 0x34, 0x10100000 },
	{ 0x35, 0x2aaa52aa },
	{ 0x36, 0x00c00000 },
	{ 0x37, 0x20046100 },
	{ 0x50, 0x10022f00 },
	{ 0x51, 0x003c0000 },
	{ 0x54, 0x04000000 },
	{ 0x55, 0x01000000 },
	{ 0x56, 0x02000000 },
	{ 0x57, 0x02000000 },
	{ 0x58, 0x02000000 },
	{ 0x59, 0x02000000 },
	{ 0x5b, 0x02000000 },
	{ 0x5c, 0x00000000 },
	{ 0x5d, 0x00000000 },
	{ 0x5e, 0x00000000 },
	{ 0x5f, 0x00000000 },
	{ 0x60, 0x02000000 },
	{ 0x61, 0x00000000 },
	{ 0x62, 0x00000000 },
	{ 0x63, 0x00000000 },
	{ 0x64, 0x00000000 },
	{ 0x65, 0x02000000 },
	{ 0x66, 0x00000000 },
	{ 0x67, 0x00000000 },
	{ 0x68, 0x00000000 },
	{ 0x69, 0x00000000 },
	{ 0x6a, 0x02000000 },
	{ 0x6c, 0x00000000 },
	{ 0x6d, 0x00000000 },
	{ 0x6e, 0x00000000 },
	{ 0x70, 0x10EC1308 },
	{ 0x71, 0x00000000 },
	{ 0x72, 0x00000000 },
	{ 0x73, 0x00000000 },
	{ 0x74, 0x00000000 },
	{ 0x75, 0x00000000 },
	{ 0x76, 0x00000000 },
	{ 0x77, 0x00000000 },
	{ 0x78, 0x00000000 },
	{ 0x79, 0x00000000 },
	{ 0x7a, 0x00000000 },
	{ 0x7b, 0x00000000 },
	{ 0x7c, 0x00000000 },
	{ 0x7d, 0x00000000 },
	{ 0x7e, 0x00000000 },
	{ 0x7f, 0x00020f00 },
	{ 0x80, 0x00000000 },
	{ 0x81, 0x00000000 },
	{ 0x82, 0x00000000 },
	{ 0x83, 0x00000000 },
	{ 0x84, 0x00000000 },
	{ 0x85, 0x00000000 },
	{ 0x86, 0x00000000 },
	{ 0x87, 0x00000000 },
	{ 0x88, 0x00000000 },
	{ 0x89, 0x00000000 },
	{ 0x8a, 0x00000000 },
	{ 0x8b, 0x00000000 },
	{ 0x8c, 0x00000000 },
	{ 0x8d, 0x00000000 },
	{ 0x8e, 0x00000000 },
	{ 0x90, 0x50250905 },
	{ 0x91, 0x15050000 },
	{ 0xa0, 0x00000000 },
	{ 0xa1, 0x00000000 },
	{ 0xa2, 0x00000000 },
	{ 0xa3, 0x00000000 },
	{ 0xa4, 0x00000000 },
	{ 0xb0, 0x00000000 },
	{ 0xb1, 0x00000000 },
	{ 0xb2, 0x00000000 },
	{ 0xb3, 0x00000000 },
	{ 0xb4, 0x00000000 },
	{ 0xb5, 0x00000000 },
	{ 0xb6, 0x00000000 },
	{ 0xb7, 0x00000000 },
	{ 0xb8, 0x00000000 },
	{ 0xb9, 0x00000000 },
	{ 0xba, 0x00000000 },
	{ 0xbb, 0x00000000 },
	{ 0xc0, 0x01000000 },
	{ 0xc1, 0x00000000 },
	{ 0xf0, 0x00000000 },
};

static int wt1308_weg_init(stwuct snd_soc_component *component)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);

	wetuwn wegmap_muwti_weg_wwite(wt1308->wegmap, init_wist,
				WT1308_INIT_WEG_WEN);
}

static boow wt1308_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT1308_WESET:
	case WT1308_WESET_N:
	case WT1308_CWK_2:
	case WT1308_SIW_DET:
	case WT1308_CWK_DET:
	case WT1308_DC_DET:
	case WT1308_DAC_SET:
	case WT1308_DAC_BUF:
	case WT1308_SDW_WEG_WDATA:
	case WT1308_DC_CAW_1:
	case WT1308_PVDD_OFFSET_CTW:
	case WT1308_CAW_OFFSET_DAC_PBTW:
	case WT1308_CAW_OFFSET_DAC_W:
	case WT1308_CAW_OFFSET_DAC_W:
	case WT1308_CAW_OFFSET_PWM_W:
	case WT1308_CAW_OFFSET_PWM_W:
	case WT1308_CAW_PWM_VOS_ADC_W:
	case WT1308_CAW_PWM_VOS_ADC_W:
	case WT1308_MBIAS:
	case WT1308_POWEW_STATUS:
	case WT1308_POWEW_INT:
	case WT1308_SINE_TONE_GEN_2:
	case WT1308_BQ_SET:
	case WT1308_BQ_PAWA_UPDATE:
	case WT1308_VEN_DEV_ID:
	case WT1308_VEWSION_ID:
	case WT1308_EFUSE_1:
	case WT1308_EFUSE_WEAD_PVDD_W:
	case WT1308_EFUSE_WEAD_PVDD_W:
	case WT1308_EFUSE_WEAD_PVDD_PTBW:
	case WT1308_EFUSE_WEAD_DEV:
	case WT1308_EFUSE_WEAD_W0:
	case WT1308_EFUSE_WEAD_ADC_W:
	case WT1308_EFUSE_WEAD_ADC_W:
	case WT1308_EFUSE_WEAD_ADC_PBTW:
	case WT1308_EFUSE_WESEWVE:
	case WT1308_EFUSE_DATA_0_MSB:
	case WT1308_EFUSE_DATA_0_WSB:
	case WT1308_EFUSE_DATA_1_MSB:
	case WT1308_EFUSE_DATA_1_WSB:
	case WT1308_EFUSE_DATA_2_MSB:
	case WT1308_EFUSE_DATA_2_WSB:
	case WT1308_EFUSE_DATA_3_MSB:
	case WT1308_EFUSE_DATA_3_WSB:
	case WT1308_EFUSE_STATUS_1:
	case WT1308_EFUSE_STATUS_2:
	case WT1308_DUMMY_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt1308_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT1308_WESET:
	case WT1308_WESET_N:
	case WT1308_CWK_GATING ... WT1308_DC_DET_THWES:
	case WT1308_DAC_SET ... WT1308_AD_FIWTEW_SET:
	case WT1308_DC_CAW_1 ... WT1308_POWEW_INT:
	case WT1308_SINE_TONE_GEN_1:
	case WT1308_SINE_TONE_GEN_2:
	case WT1308_BQ_SET:
	case WT1308_BQ_PAWA_UPDATE:
	case WT1308_BQ_PWE_VOW_W ... WT1308_BQ_POST_VOW_W:
	case WT1308_BQ1_W_H0 ... WT1308_BQ2_W_A2:
	case WT1308_VEN_DEV_ID:
	case WT1308_VEWSION_ID:
	case WT1308_SPK_BOUND:
	case WT1308_BQ1_EQ_W_1 ... WT1308_BQ2_EQ_W_3:
	case WT1308_EFUSE_1 ... WT1308_EFUSE_WESEWVE:
	case WT1308_PADS_1:
	case WT1308_PADS_2:
	case WT1308_TEST_MODE:
	case WT1308_TEST_1:
	case WT1308_TEST_2:
	case WT1308_TEST_3:
	case WT1308_TEST_4:
	case WT1308_EFUSE_DATA_0_MSB ... WT1308_EFUSE_STATUS_2:
	case WT1308_TCON_1:
	case WT1308_TCON_2:
	case WT1308_DUMMY_WEG:
	case WT1308_MAX_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wt1308_cwassd_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		msweep(30);
		snd_soc_component_update_bits(component, WT1308_POWEW_STATUS,
			WT1308_POW_PDB_WEG_BIT | WT1308_POW_PDB_MN_BIT,
			WT1308_POW_PDB_WEG_BIT | WT1308_POW_PDB_MN_BIT);
		msweep(40);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT1308_POWEW_STATUS,
			WT1308_POW_PDB_WEG_BIT | WT1308_POW_PDB_MN_BIT, 0);
		usweep_wange(150000, 200000);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const chaw * const wt1308_wx_data_ch_sewect[] = {
	"WW",
	"WW",
	"WW",
	"WW",
};

static SOC_ENUM_SINGWE_DECW(wt1308_wx_data_ch_enum, WT1308_DATA_PATH, 24,
	wt1308_wx_data_ch_sewect);

static const stwuct snd_kcontwow_new wt1308_snd_contwows[] = {

	/* I2S Data Channew Sewection */
	SOC_ENUM("WX Channew Sewect", wt1308_wx_data_ch_enum),
};

static const stwuct snd_kcontwow_new wt1308_sto_dac_w =
	SOC_DAPM_SINGWE("Switch", WT1308_DAC_SET,
		WT1308_DVOW_MUTE_W_EN_SFT, 1, 1);

static const stwuct snd_kcontwow_new wt1308_sto_dac_w =
	SOC_DAPM_SINGWE("Switch", WT1308_DAC_SET,
		WT1308_DVOW_MUTE_W_EN_SFT, 1, 1);

static const stwuct snd_soc_dapm_widget wt1308_dapm_widgets[] = {
	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),

	/* Suppwy Widgets */
	SND_SOC_DAPM_SUPPWY("MBIAS20U", WT1308_POWEW,
		WT1308_POW_MBIAS20U_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AWDO", WT1308_POWEW,
		WT1308_POW_AWDO_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DBG", WT1308_POWEW,
		WT1308_POW_DBG_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DACW", WT1308_POWEW,
		WT1308_POW_DACW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK25M", WT1308_POWEW,
		WT1308_POW_CWK25M_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC_W", WT1308_POWEW,
		WT1308_POW_ADC_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC_W", WT1308_POWEW,
		WT1308_POW_ADC_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DWDO", WT1308_POWEW,
		WT1308_POW_DWDO_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VWEF", WT1308_POWEW,
		WT1308_POW_VWEF_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIXEW_W", WT1308_POWEW,
		WT1308_POW_MIXEW_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIXEW_W", WT1308_POWEW,
		WT1308_POW_MIXEW_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MBIAS4U", WT1308_POWEW,
		WT1308_POW_MBIAS4U_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2_WDO", WT1308_POWEW,
		WT1308_POW_PWW2_WDO_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2B", WT1308_POWEW,
		WT1308_POW_PWW2B_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2F", WT1308_POWEW,
		WT1308_POW_PWW2F_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2F2", WT1308_POWEW,
		WT1308_POW_PWW2F2_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2B2", WT1308_POWEW,
		WT1308_POW_PWW2B2_EN_BIT, 0, NUWW, 0),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SUPPWY("DAC Powew", WT1308_POWEW,
		WT1308_POW_DAC1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("DAC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("DAC W", SND_SOC_NOPM, 0, 0, &wt1308_sto_dac_w),
	SND_SOC_DAPM_SWITCH("DAC W", SND_SOC_NOPM, 0, 0, &wt1308_sto_dac_w),

	/* Output Wines */
	SND_SOC_DAPM_PGA_E("CWASS D", SND_SOC_NOPM, 0, 0, NUWW, 0,
		wt1308_cwassd_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
};

static const stwuct snd_soc_dapm_woute wt1308_dapm_woutes[] = {

	{ "DAC", NUWW, "AIF1WX" },

	{ "DAC", NUWW, "MBIAS20U" },
	{ "DAC", NUWW, "AWDO" },
	{ "DAC", NUWW, "DBG" },
	{ "DAC", NUWW, "DACW" },
	{ "DAC", NUWW, "CWK25M" },
	{ "DAC", NUWW, "ADC_W" },
	{ "DAC", NUWW, "ADC_W" },
	{ "DAC", NUWW, "DWDO" },
	{ "DAC", NUWW, "VWEF" },
	{ "DAC", NUWW, "MIXEW_W" },
	{ "DAC", NUWW, "MIXEW_W" },
	{ "DAC", NUWW, "MBIAS4U" },
	{ "DAC", NUWW, "PWW2_WDO" },
	{ "DAC", NUWW, "PWW2B" },
	{ "DAC", NUWW, "PWW2F" },
	{ "DAC", NUWW, "PWW2F2" },
	{ "DAC", NUWW, "PWW2B2" },

	{ "DAC W", "Switch", "DAC" },
	{ "DAC W", "Switch", "DAC" },
	{ "DAC W", NUWW, "DAC Powew" },
	{ "DAC W", NUWW, "DAC Powew" },

	{ "CWASS D", NUWW, "DAC W" },
	{ "CWASS D", NUWW, "DAC W" },
	{ "SPOW", NUWW, "CWASS D" },
	{ "SPOW", NUWW, "CWASS D" },
};

static int wt1308_get_cwk_info(int scwk, int wate)
{
	int i;
	static const int pd[] = {1, 2, 3, 4, 6, 8, 12, 16};

	if (scwk <= 0 || wate <= 0)
		wetuwn -EINVAW;

	wate = wate << 8;
	fow (i = 0; i < AWWAY_SIZE(pd); i++)
		if (scwk == wate * pd[i])
			wetuwn i;

	wetuwn -EINVAW;
}

static int wt1308_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0, vaw_cwk, mask_cwk;
	int pwe_div, bcwk_ms, fwame_size;

	wt1308->wwck = pawams_wate(pawams);
	pwe_div = wt1308_get_cwk_info(wt1308->syscwk, wt1308->wwck);
	if (pwe_div < 0) {
		dev_eww(component->dev,
			"Unsuppowted cwock setting %d\n", wt1308->wwck);
		wetuwn -EINVAW;
	}

	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0) {
		dev_eww(component->dev, "Unsuppowted fwame size: %d\n",
			fwame_size);
		wetuwn -EINVAW;
	}

	bcwk_ms = fwame_size > 32;
	wt1308->bcwk = wt1308->wwck * (32 << bcwk_ms);

	dev_dbg(component->dev, "bcwk_ms is %d and pwe_div is %d fow iis %d\n",
				bcwk_ms, pwe_div, dai->id);

	dev_dbg(component->dev, "wwck is %dHz and pwe_div is %d fow iis %d\n",
				wt1308->wwck, pwe_div, dai->id);

	switch (pawams_width(pawams)) {
	case 16:
		vaw_wen |= WT1308_I2S_DW_SEW_16B;
		bweak;
	case 20:
		vaw_wen |= WT1308_I2S_DW_SEW_20B;
		bweak;
	case 24:
		vaw_wen |= WT1308_I2S_DW_SEW_24B;
		bweak;
	case 8:
		vaw_wen |= WT1308_I2S_DW_SEW_8B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case WT1308_AIF1:
		mask_cwk = WT1308_DIV_FS_SYS_MASK;
		vaw_cwk = pwe_div << WT1308_DIV_FS_SYS_SFT;
		snd_soc_component_update_bits(component,
			WT1308_I2S_SET_2, WT1308_I2S_DW_SEW_MASK,
			vaw_wen);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT1308_CWK_1,
		mask_cwk, vaw_cwk);

	wetuwn 0;
}

static int wt1308_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0, weg1_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		wt1308->mastew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT1308_I2S_DF_SEW_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT1308_I2S_DF_SEW_PCM_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT1308_I2S_DF_SEW_PCM_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg1_vaw |= WT1308_I2S_BCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case WT1308_AIF1:
		snd_soc_component_update_bits(component,
			WT1308_I2S_SET_1, WT1308_I2S_DF_SEW_MASK,
			weg_vaw);
		snd_soc_component_update_bits(component,
			WT1308_I2S_SET_2, WT1308_I2S_BCWK_MASK,
			weg1_vaw);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wt1308_set_component_syscwk(stwuct snd_soc_component *component,
		int cwk_id, int souwce, unsigned int fweq, int diw)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	if (fweq == wt1308->syscwk && cwk_id == wt1308->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT1308_FS_SYS_S_MCWK:
		weg_vaw |= WT1308_SEW_FS_SYS_SWC_MCWK;
		snd_soc_component_update_bits(component,
			WT1308_CWK_DET, WT1308_MCWK_DET_EN_MASK,
			WT1308_MCWK_DET_EN);
		bweak;
	case WT1308_FS_SYS_S_BCWK:
		weg_vaw |= WT1308_SEW_FS_SYS_SWC_BCWK;
		bweak;
	case WT1308_FS_SYS_S_PWW:
		weg_vaw |= WT1308_SEW_FS_SYS_SWC_PWW;
		bweak;
	case WT1308_FS_SYS_S_WCCWK:
		weg_vaw |= WT1308_SEW_FS_SYS_SWC_WCCWK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, WT1308_CWK_1,
		WT1308_SEW_FS_SYS_MASK, weg_vaw);
	wt1308->syscwk = fweq;
	wt1308->syscwk_swc = cwk_id;

	dev_dbg(component->dev, "Syscwk is %dHz and cwock id is %d\n",
		fweq, cwk_id);

	wetuwn 0;
}

static int wt1308_set_component_pww(stwuct snd_soc_component *component,
		int pww_id, int souwce, unsigned int fweq_in,
		unsigned int fweq_out)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;

	if (souwce == wt1308->pww_swc && fweq_in == wt1308->pww_in &&
	    fweq_out == wt1308->pww_out)
		wetuwn 0;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt1308->pww_in = 0;
		wt1308->pww_out = 0;
		snd_soc_component_update_bits(component,
			WT1308_CWK_1, WT1308_SEW_FS_SYS_MASK,
			WT1308_SEW_FS_SYS_SWC_MCWK);
		wetuwn 0;
	}

	switch (souwce) {
	case WT1308_PWW_S_MCWK:
		snd_soc_component_update_bits(component,
			WT1308_CWK_2, WT1308_SEW_PWW_SWC_MASK,
			WT1308_SEW_PWW_SWC_MCWK);
		snd_soc_component_update_bits(component,
			WT1308_CWK_DET, WT1308_MCWK_DET_EN_MASK,
			WT1308_MCWK_DET_EN);
		bweak;
	case WT1308_PWW_S_BCWK:
		snd_soc_component_update_bits(component,
			WT1308_CWK_2, WT1308_SEW_PWW_SWC_MASK,
			WT1308_SEW_PWW_SWC_BCWK);
		bweak;
	case WT1308_PWW_S_WCCWK:
		snd_soc_component_update_bits(component,
			WT1308_CWK_2, WT1308_SEW_PWW_SWC_MASK,
			WT1308_SEW_PWW_SWC_WCCWK);
		fweq_in = 25000000;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown PWW Souwce %d\n", souwce);
		wetuwn -EINVAW;
	}

	wet = ww6231_pww_cawc(fweq_in, fweq_out, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pww_code.m_bp, (pww_code.m_bp ? 0 : pww_code.m_code),
		pww_code.n_code, pww_code.k_code);

	snd_soc_component_wwite(component, WT1308_PWW_1,
		(pww_code.k_code << WT1308_PWW1_K_SFT) |
		(pww_code.m_bp << WT1308_PWW1_M_BYPASS_SFT) |
		((pww_code.m_bp ? 0 : pww_code.m_code) << WT1308_PWW1_M_SFT) |
		(pww_code.n_code << WT1308_PWW1_N_SFT));

	wt1308->pww_in = fweq_in;
	wt1308->pww_out = fweq_out;
	wt1308->pww_swc = souwce;

	wetuwn 0;
}

static int wt1308_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);

	wt1308->component = component;

	wetuwn wt1308_weg_init(component);
}

static void wt1308_wemove(stwuct snd_soc_component *component)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);

	wegmap_wwite(wt1308->wegmap, WT1308_WESET, 0);
}

#ifdef CONFIG_PM
static int wt1308_suspend(stwuct snd_soc_component *component)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt1308->wegmap, twue);
	wegcache_mawk_diwty(wt1308->wegmap);

	wetuwn 0;
}

static int wt1308_wesume(stwuct snd_soc_component *component)
{
	stwuct wt1308_pwiv *wt1308 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt1308->wegmap, fawse);
	wegcache_sync(wt1308->wegmap);

	wetuwn 0;
}
#ewse
#define wt1308_suspend NUWW
#define wt1308_wesume NUWW
#endif

#define WT1308_STEWEO_WATES SNDWV_PCM_WATE_48000
#define WT1308_FOWMATS (SNDWV_PCM_FMTBIT_S8 | \
			SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wt1308_aif_dai_ops = {
	.hw_pawams = wt1308_hw_pawams,
	.set_fmt = wt1308_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew wt1308_dai[] = {
	{
		.name = "wt1308-aif",
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT1308_STEWEO_WATES,
			.fowmats = WT1308_FOWMATS,
		},
		.ops = &wt1308_aif_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt1308 = {
	.pwobe = wt1308_pwobe,
	.wemove = wt1308_wemove,
	.suspend = wt1308_suspend,
	.wesume = wt1308_wesume,
	.contwows = wt1308_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt1308_snd_contwows),
	.dapm_widgets = wt1308_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt1308_dapm_widgets),
	.dapm_woutes = wt1308_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wt1308_dapm_woutes),
	.set_syscwk = wt1308_set_component_syscwk,
	.set_pww = wt1308_set_component_pww,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt1308_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.max_wegistew = WT1308_MAX_WEG,
	.vowatiwe_weg = wt1308_vowatiwe_wegistew,
	.weadabwe_weg = wt1308_weadabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt1308_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt1308_weg),
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

#ifdef CONFIG_OF
static const stwuct of_device_id wt1308_of_match[] = {
	{ .compatibwe = "weawtek,wt1308", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wt1308_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt1308_acpi_match[] = {
	{ "10EC1308", 0, },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wt1308_acpi_match);
#endif

static const stwuct i2c_device_id wt1308_i2c_id[] = {
	{ "wt1308", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt1308_i2c_id);

static void wt1308_efuse(stwuct wt1308_pwiv *wt1308)
{
	wegmap_wwite(wt1308->wegmap, WT1308_WESET, 0);

	wegmap_wwite(wt1308->wegmap, WT1308_POWEW_STATUS, 0x01800000);
	msweep(100);
	wegmap_wwite(wt1308->wegmap, WT1308_EFUSE_1, 0x44fe0f00);
	msweep(20);
	wegmap_wwite(wt1308->wegmap, WT1308_PVDD_OFFSET_CTW, 0x10000000);
}

static int wt1308_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt1308_pwiv *wt1308;
	int wet;
	unsigned int vaw;

	wt1308 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt1308_pwiv),
				GFP_KEWNEW);
	if (wt1308 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt1308);

	wt1308->wegmap = devm_wegmap_init_i2c(i2c, &wt1308_wegmap);
	if (IS_EWW(wt1308->wegmap)) {
		wet = PTW_EWW(wt1308->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wegmap_wead(wt1308->wegmap, WT1308_VEN_DEV_ID, &vaw);
	/* ignowe wast byte diffewence */
	if ((vaw & 0xFFFFFF00) != WT1308_DEVICE_ID_NUM) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %x is not wt1308\n", vaw);
		wetuwn -ENODEV;
	}

	wt1308_efuse(wt1308);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wt1308,
			wt1308_dai, AWWAY_SIZE(wt1308_dai));
}

static void wt1308_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wt1308_pwiv *wt1308 = i2c_get_cwientdata(cwient);

	wegmap_wwite(wt1308->wegmap, WT1308_WESET, 0);
}

static stwuct i2c_dwivew wt1308_i2c_dwivew = {
	.dwivew = {
		.name = "wt1308",
		.of_match_tabwe = of_match_ptw(wt1308_of_match),
		.acpi_match_tabwe = ACPI_PTW(wt1308_acpi_match),
	},
	.pwobe = wt1308_i2c_pwobe,
	.shutdown = wt1308_i2c_shutdown,
	.id_tabwe = wt1308_i2c_id,
};
moduwe_i2c_dwivew(wt1308_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT1308 ampwifiew dwivew");
MODUWE_AUTHOW("Dewek Fang <dewek.fang@weawtek.com>");
MODUWE_WICENSE("GPW v2");
