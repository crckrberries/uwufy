// SPDX-Wicense-Identifiew: GPW-2.0
//
// wt1016.c  --  WT1016 AWSA SoC audio ampwifiew dwivew
//
// Copywight 2020 Weawtek Semiconductow Cowp.
// Authow: Odew Chiou <odew_chiou@weawtek.com>
//

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
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
#incwude "wt1016.h"

static const stwuct weg_sequence wt1016_patch[] = {
	{WT1016_VOW_CTWW_3,	0x8900},
	{WT1016_ANA_CTWW_1,	0xa002},
	{WT1016_ANA_CTWW_2,	0x0002},
	{WT1016_CWOCK_4,	0x6700},
	{WT1016_CWASSD_3,	0xdc55},
	{WT1016_CWASSD_4,	0x376a},
	{WT1016_CWASSD_5,	0x009f},
};

static const stwuct weg_defauwt wt1016_weg[] = {
	{0x00, 0x0000},
	{0x01, 0x5400},
	{0x02, 0x5506},
	{0x03, 0xf800},
	{0x04, 0x0000},
	{0x05, 0xbfbf},
	{0x06, 0x8900},
	{0x07, 0xa002},
	{0x08, 0x0000},
	{0x09, 0x0000},
	{0x0a, 0x0000},
	{0x0c, 0x0000},
	{0x0d, 0x0000},
	{0x0e, 0x10ec},
	{0x0f, 0x6595},
	{0x11, 0x0002},
	{0x1c, 0x0000},
	{0x1d, 0x0000},
	{0x1e, 0x0000},
	{0x1f, 0xf000},
	{0x20, 0x0000},
	{0x21, 0x6000},
	{0x22, 0x0000},
	{0x23, 0x6700},
	{0x24, 0x0000},
	{0x25, 0x0000},
	{0x26, 0x0000},
	{0x40, 0x0018},
	{0x60, 0x00a5},
	{0x80, 0x0010},
	{0x81, 0x0009},
	{0x82, 0x0000},
	{0x83, 0x0000},
	{0xa0, 0x0700},
	{0xc0, 0x0080},
	{0xc1, 0x02a0},
	{0xc2, 0x1400},
	{0xc3, 0x0a4a},
	{0xc4, 0x552a},
	{0xc5, 0x087e},
	{0xc6, 0x0020},
	{0xc7, 0xa833},
	{0xc8, 0x0433},
	{0xc9, 0x8040},
	{0xca, 0xdc55},
	{0xcb, 0x376a},
	{0xcc, 0x009f},
	{0xcf, 0x0020},
};

static boow wt1016_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT1016_ANA_FWAG:
	case WT1016_VEWSION2_ID:
	case WT1016_VEWSION1_ID:
	case WT1016_VENDEW_ID:
	case WT1016_DEVICE_ID:
	case WT1016_TEST_SIGNAW:
	case WT1016_SC_CTWW_1:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow wt1016_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT1016_WESET:
	case WT1016_PADS_CTWW_1:
	case WT1016_PADS_CTWW_2:
	case WT1016_I2C_CTWW:
	case WT1016_VOW_CTWW_1:
	case WT1016_VOW_CTWW_2:
	case WT1016_VOW_CTWW_3:
	case WT1016_ANA_CTWW_1:
	case WT1016_MUX_SEW:
	case WT1016_WX_I2S_CTWW:
	case WT1016_ANA_FWAG:
	case WT1016_VEWSION2_ID:
	case WT1016_VEWSION1_ID:
	case WT1016_VENDEW_ID:
	case WT1016_DEVICE_ID:
	case WT1016_ANA_CTWW_2:
	case WT1016_TEST_SIGNAW:
	case WT1016_TEST_CTWW_1:
	case WT1016_TEST_CTWW_2:
	case WT1016_TEST_CTWW_3:
	case WT1016_CWOCK_1:
	case WT1016_CWOCK_2:
	case WT1016_CWOCK_3:
	case WT1016_CWOCK_4:
	case WT1016_CWOCK_5:
	case WT1016_CWOCK_6:
	case WT1016_CWOCK_7:
	case WT1016_I2S_CTWW:
	case WT1016_DAC_CTWW_1:
	case WT1016_SC_CTWW_1:
	case WT1016_SC_CTWW_2:
	case WT1016_SC_CTWW_3:
	case WT1016_SC_CTWW_4:
	case WT1016_SIW_DET:
	case WT1016_SYS_CWK:
	case WT1016_BIAS_CUW:
	case WT1016_DAC_CTWW_2:
	case WT1016_WDO_CTWW:
	case WT1016_CWASSD_1:
	case WT1016_PWW1:
	case WT1016_PWW2:
	case WT1016_PWW3:
	case WT1016_CWASSD_2:
	case WT1016_CWASSD_OUT:
	case WT1016_CWASSD_3:
	case WT1016_CWASSD_4:
	case WT1016_CWASSD_5:
	case WT1016_PWW_CTWW:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static const DECWAWE_TWV_DB_SCAWE(dac_vow_twv, -9550, 50, 0);

static const stwuct snd_kcontwow_new wt1016_snd_contwows[] = {
	SOC_DOUBWE_TWV("DAC Pwayback Vowume", WT1016_VOW_CTWW_2,
		WT1016_W_VOW_SFT, WT1016_W_VOW_SFT, 191, 0, dac_vow_twv),
	SOC_DOUBWE("DAC Pwayback Switch", WT1016_VOW_CTWW_1,
		WT1016_DA_MUTE_W_SFT, WT1016_DA_MUTE_W_SFT, 1, 1),
};

static int wt1016_is_sys_cwk_fwom_pww(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);

	if (wt1016->syscwk_swc == WT1016_SCWK_S_PWW)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* Intewface data sewect */
static const chaw * const wt1016_data_sewect[] = {
	"W/W", "W/W", "W/W", "W/W"
};

static SOC_ENUM_SINGWE_DECW(wt1016_if_data_swap_enum,
	WT1016_I2S_CTWW, WT1016_I2S_DATA_SWAP_SFT, wt1016_data_sewect);

static const stwuct snd_kcontwow_new wt1016_if_data_swap_mux =
	SOC_DAPM_ENUM("Data Swap Mux", wt1016_if_data_swap_enum);

static const stwuct snd_soc_dapm_widget wt1016_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("Data Swap Mux", SND_SOC_NOPM, 0, 0,
			&wt1016_if_data_swap_mux),

	SND_SOC_DAPM_SUPPWY("DAC Fiwtew", WT1016_CWOCK_3,
		WT1016_PWW_DAC_FIWTEW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAMOD", WT1016_CWOCK_3, WT1016_PWW_DACMOD_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("FIFO", WT1016_CWOCK_3, WT1016_PWW_CWK_FIFO_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Puwe DC", WT1016_CWOCK_3,
		WT1016_PWW_CWK_PUWEDC_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK Siwence Det", WT1016_CWOCK_3,
		WT1016_PWW_SIW_DET_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WC 25M", WT1016_CWOCK_3, WT1016_PWW_WC_25M_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW1", WT1016_CWOCK_3, WT1016_PWW_PWW1_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ANA CTWW", WT1016_CWOCK_3, WT1016_PWW_ANA_CTWW_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK SYS", WT1016_CWOCK_3, WT1016_PWW_CWK_SYS_BIT,
		0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("WWCK Det", WT1016_CWOCK_4, WT1016_PWW_WWCK_DET_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BCWK Det", WT1016_CWOCK_4, WT1016_PWW_BCWK_DET_BIT,
		0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("CKGEN DAC", WT1016_DAC_CTWW_2,
		WT1016_CKGEN_DAC_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VCM SWOW", WT1016_CWASSD_1, WT1016_VCM_SWOW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Siwence Det", WT1016_SIW_DET,
		WT1016_SIW_DET_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW2", WT1016_PWW2, WT1016_PWW2_EN_BIT, 0, NUWW,
		0),

	SND_SOC_DAPM_SUPPWY_S("BG1 BG2", 1, WT1016_PWW_CTWW,
		WT1016_PWW_BG_1_2_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("MBIAS BG", 1, WT1016_PWW_CTWW,
		WT1016_PWW_MBIAS_BG_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("PWW", 1, WT1016_PWW_CTWW, WT1016_PWW_PWW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("BASIC", 1, WT1016_PWW_CTWW, WT1016_PWW_BASIC_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("CWASS D", 1, WT1016_PWW_CTWW,
		WT1016_PWW_CWSD_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("25M", 1, WT1016_PWW_CTWW, WT1016_PWW_25M_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW", 1, WT1016_PWW_CTWW, WT1016_PWW_DACW_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW", 1, WT1016_PWW_CTWW, WT1016_PWW_DACW_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("WDO2", 1, WT1016_PWW_CTWW, WT1016_PWW_WDO2_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("VWEF", 1, WT1016_PWW_CTWW, WT1016_PWW_VWEF_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("MBIAS", 1, WT1016_PWW_CTWW, WT1016_PWW_MBIAS_BIT,
		0, NUWW, 0),

	SND_SOC_DAPM_AIF_IN("AIFWX", "AIF Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("SPO"),
};

static const stwuct snd_soc_dapm_woute wt1016_dapm_woutes[] = {
	{ "Data Swap Mux", "W/W", "AIFWX" },
	{ "Data Swap Mux", "W/W", "AIFWX" },
	{ "Data Swap Mux", "W/W", "AIFWX" },
	{ "Data Swap Mux", "W/W", "AIFWX" },

	{ "DAC", NUWW, "DAC Fiwtew" },
	{ "DAC", NUWW, "DAMOD" },
	{ "DAC", NUWW, "FIFO" },
	{ "DAC", NUWW, "Puwe DC" },
	{ "DAC", NUWW, "Siwence Det" },
	{ "DAC", NUWW, "ANA CTWW" },
	{ "DAC", NUWW, "CWK SYS" },
	{ "DAC", NUWW, "WWCK Det" },
	{ "DAC", NUWW, "BCWK Det" },
	{ "DAC", NUWW, "CKGEN DAC" },
	{ "DAC", NUWW, "VCM SWOW" },

	{ "PWW", NUWW, "PWW1" },
	{ "PWW", NUWW, "PWW2" },
	{ "25M", NUWW, "WC 25M" },
	{ "Siwence Det", NUWW, "CWK Siwence Det" },

	{ "DAC", NUWW, "Data Swap Mux" },
	{ "DAC", NUWW, "BG1 BG2" },
	{ "DAC", NUWW, "MBIAS BG" },
	{ "DAC", NUWW, "PWW", wt1016_is_sys_cwk_fwom_pww},
	{ "DAC", NUWW, "BASIC" },
	{ "DAC", NUWW, "CWASS D" },
	{ "DAC", NUWW, "25M" },
	{ "DAC", NUWW, "DACW" },
	{ "DAC", NUWW, "DACW" },
	{ "DAC", NUWW, "WDO2" },
	{ "DAC", NUWW, "VWEF" },
	{ "DAC", NUWW, "MBIAS" },

	{ "SPO", NUWW, "DAC" },
};

static int wt1016_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);
	int pwe_div, bcwk_ms, fwame_size;
	unsigned int vaw_wen = 0;

	wt1016->wwck = pawams_wate(pawams);
	pwe_div = ww6231_get_cwk_info(wt1016->syscwk, wt1016->wwck);
	if (pwe_div < 0) {
		dev_eww(component->dev, "Unsuppowted cwock wate\n");
		wetuwn -EINVAW;
	}

	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0) {
		dev_eww(component->dev, "Unsuppowted fwame size: %d\n",
			fwame_size);
		wetuwn -EINVAW;
	}

	bcwk_ms = fwame_size > 32;
	wt1016->bcwk = wt1016->wwck * (32 << bcwk_ms);

	if (bcwk_ms && wt1016->mastew)
		snd_soc_component_update_bits(component, WT1016_I2S_CTWW,
			WT1016_I2S_BCWK_MS_MASK, WT1016_I2S_BCWK_MS_64);

	dev_dbg(component->dev, "wwck is %dHz and pwe_div is %d fow iis %d\n",
				wt1016->wwck, pwe_div, dai->id);

	switch (pawams_width(pawams)) {
	case 16:
		vaw_wen = WT1016_I2S_DW_16;
		bweak;
	case 20:
		vaw_wen = WT1016_I2S_DW_20;
		bweak;
	case 24:
		vaw_wen = WT1016_I2S_DW_24;
		bweak;
	case 32:
		vaw_wen = WT1016_I2S_DW_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT1016_I2S_CTWW,
		WT1016_I2S_DW_MASK, vaw_wen);
	snd_soc_component_update_bits(component, WT1016_CWOCK_2,
		WT1016_FS_PD_MASK | WT1016_OSW_PD_MASK,
		((pwe_div + 3) << WT1016_FS_PD_SFT) |
		(pwe_div << WT1016_OSW_PD_SFT));

	wetuwn 0;
}

static int wt1016_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		weg_vaw |= WT1016_I2S_MS_M;
		wt1016->mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		weg_vaw |= WT1016_I2S_MS_S;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg_vaw |= WT1016_I2S_BCWK_POW_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT1016_I2S_DF_WEFT;
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT1016_I2S_DF_PCM_A;
		bweak;

	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT1016_I2S_DF_PCM_B;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT1016_I2S_CTWW,
			WT1016_I2S_MS_MASK | WT1016_I2S_BCWK_POW_MASK |
			WT1016_I2S_DF_MASK, weg_vaw);

	wetuwn 0;
}

static int wt1016_set_component_syscwk(stwuct snd_soc_component *component,
		int cwk_id, int souwce, unsigned int fweq, int diw)
{
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	if (fweq == wt1016->syscwk && cwk_id == wt1016->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT1016_SCWK_S_MCWK:
		weg_vaw |= WT1016_CWK_SYS_SEW_MCWK;
		bweak;

	case WT1016_SCWK_S_PWW:
		weg_vaw |= WT1016_CWK_SYS_SEW_PWW;
		bweak;

	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}

	wt1016->syscwk = fweq;
	wt1016->syscwk_swc = cwk_id;

	dev_dbg(component->dev, "Syscwk is %dHz and cwock id is %d\n",
		fweq, cwk_id);

	snd_soc_component_update_bits(component, WT1016_CWOCK_1,
			WT1016_CWK_SYS_SEW_MASK, weg_vaw);

	wetuwn 0;
}

static int wt1016_set_component_pww(stwuct snd_soc_component *component,
		int pww_id, int souwce, unsigned int fweq_in,
		unsigned int fweq_out)
{
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt1016->pww_in = 0;
		wt1016->pww_out = 0;

		wetuwn 0;
	}

	if (souwce == wt1016->pww_swc && fweq_in == wt1016->pww_in &&
		fweq_out == wt1016->pww_out)
		wetuwn 0;

	switch (souwce) {
	case WT1016_PWW_S_MCWK:
		snd_soc_component_update_bits(component, WT1016_CWOCK_1,
			WT1016_PWW_SEW_MASK, WT1016_PWW_SEW_MCWK);
		bweak;

	case WT1016_PWW_S_BCWK:
		snd_soc_component_update_bits(component, WT1016_CWOCK_1,
			WT1016_PWW_SEW_MASK, WT1016_PWW_SEW_BCWK);
		bweak;

	defauwt:
		dev_eww(component->dev, "Unknown PWW Souwce %d\n", souwce);
		wetuwn -EINVAW;
	}

	wet = ww6231_pww_cawc(fweq_in, fweq_out * 4, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "mbypass=%d m=%d n=%d kbypass=%d k=%d\n",
		pww_code.m_bp, (pww_code.m_bp ? 0 : pww_code.m_code),
		pww_code.n_code, pww_code.k_bp,
		(pww_code.k_bp ? 0 : pww_code.k_code));

	snd_soc_component_wwite(component, WT1016_PWW1,
		((pww_code.m_bp ? 0 : pww_code.m_code) << WT1016_PWW_M_SFT) |
		(pww_code.m_bp << WT1016_PWW_M_BP_SFT) |
		pww_code.n_code);
	snd_soc_component_wwite(component, WT1016_PWW2,
		(pww_code.k_bp << WT1016_PWW_K_BP_SFT) |
		(pww_code.k_bp ? 0 : pww_code.k_code));

	wt1016->pww_in = fweq_in;
	wt1016->pww_out = fweq_out;
	wt1016->pww_swc = souwce;

	wetuwn 0;
}

static int wt1016_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt1016_pwiv *wt1016 =
		snd_soc_component_get_dwvdata(component);

	wt1016->component = component;

	wetuwn 0;
}

static void wt1016_wemove(stwuct snd_soc_component *component)
{
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);

	wegmap_wwite(wt1016->wegmap, WT1016_WESET, 0);
}

#define WT1016_STEWEO_WATES SNDWV_PCM_WATE_8000_48000
#define WT1016_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt1016_aif_dai_ops = {
	.hw_pawams = wt1016_hw_pawams,
	.set_fmt = wt1016_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew wt1016_dai[] = {
	{
		.name = "wt1016-aif",
		.id = 0,
		.pwayback = {
			.stweam_name = "AIF Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT1016_STEWEO_WATES,
			.fowmats = WT1016_FOWMATS,
		},
		.ops = &wt1016_aif_dai_ops,
	}
};

#ifdef CONFIG_PM
static int wt1016_suspend(stwuct snd_soc_component *component)
{
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt1016->wegmap, twue);
	wegcache_mawk_diwty(wt1016->wegmap);

	wetuwn 0;
}

static int wt1016_wesume(stwuct snd_soc_component *component)
{
	stwuct wt1016_pwiv *wt1016 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt1016->wegmap, fawse);
	wegcache_sync(wt1016->wegmap);

	wetuwn 0;
}
#ewse
#define wt1016_suspend NUWW
#define wt1016_wesume NUWW
#endif

static const stwuct snd_soc_component_dwivew soc_component_dev_wt1016 = {
	.pwobe = wt1016_pwobe,
	.wemove = wt1016_wemove,
	.suspend = wt1016_suspend,
	.wesume = wt1016_wesume,
	.contwows = wt1016_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt1016_snd_contwows),
	.dapm_widgets = wt1016_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt1016_dapm_widgets),
	.dapm_woutes = wt1016_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wt1016_dapm_woutes),
	.set_syscwk = wt1016_set_component_syscwk,
	.set_pww = wt1016_set_component_pww,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt1016_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = WT1016_PWW_CTWW,
	.vowatiwe_weg = wt1016_vowatiwe_wegistew,
	.weadabwe_weg = wt1016_weadabwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = wt1016_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt1016_weg),
};

static const stwuct i2c_device_id wt1016_i2c_id[] = {
	{ "wt1016", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt1016_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id wt1016_of_match[] = {
	{ .compatibwe = "weawtek,wt1016", },
	{},
};
MODUWE_DEVICE_TABWE(of, wt1016_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt1016_acpi_match[] = {
	{"10EC1016", 0,},
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt1016_acpi_match);
#endif

static int wt1016_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt1016_pwiv *wt1016;
	int wet;
	unsigned int vaw;

	wt1016 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt1016_pwiv),
				GFP_KEWNEW);
	if (wt1016 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt1016);

	wt1016->wegmap = devm_wegmap_init_i2c(i2c, &wt1016_wegmap);
	if (IS_EWW(wt1016->wegmap)) {
		wet = PTW_EWW(wt1016->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wegmap_wead(wt1016->wegmap, WT1016_DEVICE_ID, &vaw);
	if (vaw != WT1016_DEVICE_ID_VAW) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %x is not wt1016\n", vaw);
		wetuwn -ENODEV;
	}

	wegmap_wwite(wt1016->wegmap, WT1016_WESET, 0);

	wet = wegmap_wegistew_patch(wt1016->wegmap, wt1016_patch,
				    AWWAY_SIZE(wt1016_patch));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
		&soc_component_dev_wt1016,
		wt1016_dai, AWWAY_SIZE(wt1016_dai));
}

static void wt1016_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wt1016_pwiv *wt1016 = i2c_get_cwientdata(cwient);

	wegmap_wwite(wt1016->wegmap, WT1016_WESET, 0);
}

static stwuct i2c_dwivew wt1016_i2c_dwivew = {
	.dwivew = {
		.name = "wt1016",
		.of_match_tabwe = of_match_ptw(wt1016_of_match),
		.acpi_match_tabwe = ACPI_PTW(wt1016_acpi_match),
	},
	.pwobe = wt1016_i2c_pwobe,
	.shutdown = wt1016_i2c_shutdown,
	.id_tabwe = wt1016_i2c_id,
};
moduwe_i2c_dwivew(wt1016_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT1016 dwivew");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
