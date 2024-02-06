// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt712-sdca-dmic.c -- wt712 SDCA DMIC AWSA SoC audio dwivew
//
// Copywight(c) 2023 Weawtek Semiconductow Cowp.
//
//

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "wt712-sdca.h"
#incwude "wt712-sdca-dmic.h"

static boow wt712_sdca_dmic_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x201a ... 0x201f:
	case 0x2029 ... 0x202a:
	case 0x202d ... 0x2034:
	case 0x2230 ... 0x2232:
	case 0x2f01 ... 0x2f0a:
	case 0x2f35 ... 0x2f36:
	case 0x2f52:
	case 0x2f58 ... 0x2f59:
	case 0x3201:
	case 0x320c:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt712_sdca_dmic_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x201b:
	case 0x201c:
	case 0x201d:
	case 0x201f:
	case 0x202d ... 0x202f:
	case 0x2230:
	case 0x2f01:
	case 0x2f35:
	case 0x320c:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt712_sdca_dmic_mbq_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2000000 ... 0x200008e:
	case 0x5300000 ... 0x530000e:
	case 0x5400000 ... 0x540000e:
	case 0x5600000 ... 0x5600008:
	case 0x5700000 ... 0x570000d:
	case 0x5800000 ... 0x5800021:
	case 0x5900000 ... 0x5900028:
	case 0x5a00000 ... 0x5a00009:
	case 0x5b00000 ... 0x5b00051:
	case 0x5c00000 ... 0x5c0009a:
	case 0x5d00000 ... 0x5d00009:
	case 0x5f00000 ... 0x5f00030:
	case 0x6100000 ... 0x6100068:
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_01):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_02):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_03):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_04):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_01):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_02):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_03):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_04):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt712_sdca_dmic_mbq_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2000000:
	case 0x200001a:
	case 0x2000024:
	case 0x2000046:
	case 0x200008a:
	case 0x5800000:
	case 0x5800001:
	case 0x6100008:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt712_sdca_dmic_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.weadabwe_weg = wt712_sdca_dmic_weadabwe_wegistew,
	.vowatiwe_weg = wt712_sdca_dmic_vowatiwe_wegistew,
	.max_wegistew = 0x40981300,
	.weg_defauwts = wt712_sdca_dmic_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wt712_sdca_dmic_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static const stwuct wegmap_config wt712_sdca_dmic_mbq_wegmap = {
	.name = "sdw-mbq",
	.weg_bits = 32,
	.vaw_bits = 16,
	.weadabwe_weg = wt712_sdca_dmic_mbq_weadabwe_wegistew,
	.vowatiwe_weg = wt712_sdca_dmic_mbq_vowatiwe_wegistew,
	.max_wegistew = 0x40800f14,
	.weg_defauwts = wt712_sdca_dmic_mbq_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wt712_sdca_dmic_mbq_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int wt712_sdca_dmic_index_wwite(stwuct wt712_sdca_dmic_pwiv *wt712,
		unsigned int nid, unsigned int weg, unsigned int vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt712->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt712->swave->dev,
			"Faiwed to set pwivate vawue: %06x <= %04x wet=%d\n",
			addw, vawue, wet);

	wetuwn wet;
}

static int wt712_sdca_dmic_index_wead(stwuct wt712_sdca_dmic_pwiv *wt712,
		unsigned int nid, unsigned int weg, unsigned int *vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt712->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt712->swave->dev,
			"Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
			addw, *vawue, wet);

	wetuwn wet;
}

static int wt712_sdca_dmic_index_update_bits(stwuct wt712_sdca_dmic_pwiv *wt712,
	unsigned int nid, unsigned int weg, unsigned int mask, unsigned int vaw)
{
	unsigned int tmp;
	int wet;

	wet = wt712_sdca_dmic_index_wead(wt712, nid, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&tmp, mask, vaw);
	wetuwn wt712_sdca_dmic_index_wwite(wt712, nid, weg, tmp);
}

static int wt712_sdca_dmic_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt712_sdca_dmic_pwiv *wt712 = dev_get_dwvdata(dev);

	if (wt712->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt712->wegmap, fawse);
	wegcache_cache_onwy(wt712->mbq_wegmap, fawse);
	if (wt712->fiwst_hw_init) {
		wegcache_cache_bypass(wt712->wegmap, twue);
		wegcache_cache_bypass(wt712->mbq_wegmap, twue);
	} ewse {
		/*
		 * PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
		 */

		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);
	}

	pm_wuntime_get_nowesume(&swave->dev);

	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_ADC0A_08_PDE_FWOAT_CTW, 0x1112);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_ADC0B_11_PDE_FWOAT_CTW, 0x1111);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_DMIC1_2_PDE_FWOAT_CTW, 0x1111);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_I2S_IN_OUT_PDE_FWOAT_CTW, 0x1155);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_DMIC_ENT_FWOAT_CTW, 0x2626);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_ADC_ENT_FWOAT_CTW, 0x1e19);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_DMIC_GAIN_ENT_FWOAT_CTW0, 0x1515);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_ADC_VOW_CH_FWOAT_CTW2, 0x0304);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_DMIC_GAIN_ENT_FWOAT_CTW2, 0x0304);
	wt712_sdca_dmic_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_HDA_WEGACY_CONFIG_CTW0, 0x0050);
	wegmap_wwite(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_IT26, WT712_SDCA_CTW_VENDOW_DEF, 0), 0x01);
	wt712_sdca_dmic_index_wwite(wt712, WT712_UWTWA_SOUND_DET,
		WT712_UWTWA_SOUND_DETECTOW6, 0x3200);
	wegmap_wwite(wt712->wegmap, WT712_WC_CAW, 0x23);
	wegmap_wwite(wt712->wegmap, 0x2f52, 0x00);

	if (wt712->fiwst_hw_init) {
		wegcache_cache_bypass(wt712->wegmap, fawse);
		wegcache_mawk_diwty(wt712->wegmap);
		wegcache_cache_bypass(wt712->mbq_wegmap, fawse);
		wegcache_mawk_diwty(wt712->mbq_wegmap);
	} ewse
		wt712->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt712->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);
	wetuwn 0;
}

static int wt712_sdca_dmic_set_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct wt712_sdca_dmic_kctww_pwiv *p =
		(stwuct wt712_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	unsigned int wegvawue, ctw, i;
	unsigned int adc_vow_fwag = 0;
	const unsigned int intewvaw_offset = 0xc0;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume"))
		adc_vow_fwag = 1;

	/* check aww channews */
	fow (i = 0; i < p->count; i++) {
		wegmap_wead(wt712->mbq_wegmap, p->weg_base + i, &wegvawue);

		if (!adc_vow_fwag) /* boost gain */
			ctw = wegvawue / 0x0a00;
		ewse { /* ADC gain */
			if (adc_vow_fwag)
				ctw = p->max - (((0x1e00 - wegvawue) & 0xffff) / intewvaw_offset);
			ewse
				ctw = p->max - (((0 - wegvawue) & 0xffff) / intewvaw_offset);
		}

		ucontwow->vawue.integew.vawue[i] = ctw;
	}

	wetuwn 0;
}

static int wt712_sdca_dmic_set_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_dmic_kctww_pwiv *p =
		(stwuct wt712_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned int gain_vaw[4];
	unsigned int i, adc_vow_fwag = 0, changed = 0;
	unsigned int wegvawue[4];
	const unsigned int intewvaw_offset = 0xc0;
	int eww;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume"))
		adc_vow_fwag = 1;

	/* check aww channews */
	fow (i = 0; i < p->count; i++) {
		wegmap_wead(wt712->mbq_wegmap, p->weg_base + i, &wegvawue[i]);

		gain_vaw[i] = ucontwow->vawue.integew.vawue[i];
		if (gain_vaw[i] > p->max)
			gain_vaw[i] = p->max;

		if (!adc_vow_fwag) /* boost gain */
			gain_vaw[i] = gain_vaw[i] * 0x0a00;
		ewse { /* ADC gain */
			gain_vaw[i] = 0x1e00 - ((p->max - gain_vaw[i]) * intewvaw_offset);
			gain_vaw[i] &= 0xffff;
		}

		if (wegvawue[i] != gain_vaw[i])
			changed = 1;
	}

	if (!changed)
		wetuwn 0;

	fow (i = 0; i < p->count; i++) {
		eww = wegmap_wwite(wt712->mbq_wegmap, p->weg_base + i, gain_vaw[i]);
		if (eww < 0)
			dev_eww(&wt712->swave->dev, "0x%08x can't be set\n", p->weg_base + i);
	}

	wetuwn changed;
}

static int wt712_sdca_set_fu1e_captuwe_ctw(stwuct wt712_sdca_dmic_pwiv *wt712)
{
	int eww, i;
	unsigned int ch_mute;

	fow (i = 0; i < AWWAY_SIZE(wt712->fu1e_mixew_mute); i++) {
		ch_mute = (wt712->fu1e_dapm_mute || wt712->fu1e_mixew_mute[i]) ? 0x01 : 0x00;
		eww = wegmap_wwite(wt712->wegmap,
				SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E,
				WT712_SDCA_CTW_FU_MUTE, CH_01) + i, ch_mute);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wt712_sdca_dmic_fu1e_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct wt712_sdca_dmic_kctww_pwiv *p =
		(stwuct wt712_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	unsigned int i;

	fow (i = 0; i < p->count; i++)
		ucontwow->vawue.integew.vawue[i] = !wt712->fu1e_mixew_mute[i];

	wetuwn 0;
}

static int wt712_sdca_dmic_fu1e_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct wt712_sdca_dmic_kctww_pwiv *p =
		(stwuct wt712_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	int eww, changed = 0, i;

	fow (i = 0; i < p->count; i++) {
		if (wt712->fu1e_mixew_mute[i] != !ucontwow->vawue.integew.vawue[i])
			changed = 1;
		wt712->fu1e_mixew_mute[i] = !ucontwow->vawue.integew.vawue[i];
	}

	eww = wt712_sdca_set_fu1e_captuwe_ctw(wt712);
	if (eww < 0)
		wetuwn eww;

	wetuwn changed;
}

static int wt712_sdca_fu_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wt712_sdca_dmic_kctww_pwiv *p =
		(stwuct wt712_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;

	if (p->max == 1)
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = p->count;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = p->max;
	wetuwn 0;
}

#define WT712_SDCA_PW_VAWUE(xweg_base, xcount, xmax, xinvewt) \
	((unsigned wong)&(stwuct wt712_sdca_dmic_kctww_pwiv) \
		{.weg_base = xweg_base, .count = xcount, .max = xmax, \
		.invewt = xinvewt})

#define WT712_SDCA_FU_CTWW(xname, weg_base, xmax, xinvewt, xcount) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.info = wt712_sdca_fu_info, \
	.get = wt712_sdca_dmic_fu1e_captuwe_get, \
	.put = wt712_sdca_dmic_fu1e_captuwe_put, \
	.pwivate_vawue = WT712_SDCA_PW_VAWUE(weg_base, xcount, xmax, xinvewt)}

#define WT712_SDCA_EXT_TWV(xname, weg_base, xhandwew_get,\
	 xhandwew_put, xcount, xmax, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (twv_awway), \
	.info = wt712_sdca_fu_info, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = WT712_SDCA_PW_VAWUE(weg_base, xcount, xmax, 0) }

static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt712_sdca_dmic_snd_contwows[] = {
	WT712_SDCA_FU_CTWW("FU1E Captuwe Switch",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_MUTE, CH_01),
		1, 1, 4),
	WT712_SDCA_EXT_TWV("FU1E Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_01),
		wt712_sdca_dmic_set_gain_get, wt712_sdca_dmic_set_gain_put, 4, 0x3f, in_vow_twv),
	WT712_SDCA_EXT_TWV("FU15 Boost Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_01),
		wt712_sdca_dmic_set_gain_get, wt712_sdca_dmic_set_gain_put, 4, 3, mic_vow_twv),
};

static int wt712_sdca_dmic_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, mask_sft;

	if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 8;
	ewse if (stwstw(ucontwow->id.name, "ADC 26 Mux"))
		mask_sft = 4;
	ewse
		wetuwn -EINVAW;

	wt712_sdca_dmic_index_wead(wt712, WT712_VENDOW_HDA_CTW,
		WT712_HDA_WEGACY_MUX_CTW0, &vaw);

	ucontwow->vawue.enumewated.item[0] = (vaw >> mask_sft) & 0x7;

	wetuwn 0;
}

static int wt712_sdca_dmic_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, vaw2 = 0, change, mask_sft;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 8;
	ewse if (stwstw(ucontwow->id.name, "ADC 26 Mux"))
		mask_sft = 4;
	ewse
		wetuwn -EINVAW;

	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	wt712_sdca_dmic_index_wead(wt712, WT712_VENDOW_HDA_CTW,
		WT712_HDA_WEGACY_MUX_CTW0, &vaw2);
	vaw2 = (0x7 << mask_sft) & vaw2;

	if (vaw == vaw2)
		change = 0;
	ewse
		change = 1;

	if (change)
		wt712_sdca_dmic_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_HDA_WEGACY_MUX_CTW0, 0x7 << mask_sft,
			vaw << mask_sft);

	snd_soc_dapm_mux_update_powew(dapm, kcontwow,
		item[0], e, NUWW);

	wetuwn change;
}

static const chaw * const adc_mux_text[] = {
	"DMIC1",
	"DMIC2",
};

static SOC_ENUM_SINGWE_DECW(
	wt712_adc25_enum, SND_SOC_NOPM, 0, adc_mux_text);

static SOC_ENUM_SINGWE_DECW(
	wt712_adc26_enum, SND_SOC_NOPM, 0, adc_mux_text);

static const stwuct snd_kcontwow_new wt712_sdca_dmic_adc25_mux =
	SOC_DAPM_ENUM_EXT("ADC 25 Mux", wt712_adc25_enum,
			wt712_sdca_dmic_mux_get, wt712_sdca_dmic_mux_put);

static const stwuct snd_kcontwow_new wt712_sdca_dmic_adc26_mux =
	SOC_DAPM_ENUM_EXT("ADC 26 Mux", wt712_adc26_enum,
			wt712_sdca_dmic_mux_get, wt712_sdca_dmic_mux_put);

static int wt712_sdca_dmic_fu1e_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt712->fu1e_dapm_mute = fawse;
		wt712_sdca_set_fu1e_captuwe_ctw(wt712);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt712->fu1e_dapm_mute = twue;
		wt712_sdca_set_fu1e_captuwe_ctw(wt712);
		bweak;
	}
	wetuwn 0;
}

static int wt712_sdca_dmic_pde11_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PDE11,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PDE11,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt712_sdca_dmic_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),

	SND_SOC_DAPM_SUPPWY("PDE 11", SND_SOC_NOPM, 0, 0,
		wt712_sdca_dmic_pde11_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_ADC_E("FU 1E", NUWW, SND_SOC_NOPM, 0, 0,
		wt712_sdca_dmic_fu1e_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX("ADC 25 Mux", SND_SOC_NOPM, 0, 0,
		&wt712_sdca_dmic_adc25_mux),
	SND_SOC_DAPM_MUX("ADC 26 Mux", SND_SOC_NOPM, 0, 0,
		&wt712_sdca_dmic_adc26_mux),

	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt712_sdca_dmic_audio_map[] = {
	{"DP2TX", NUWW, "FU 1E"},

	{"FU 1E", NUWW, "PDE 11"},
	{"FU 1E", NUWW, "ADC 25 Mux"},
	{"FU 1E", NUWW, "ADC 26 Mux"},
	{"ADC 25 Mux", "DMIC1", "DMIC1"},
	{"ADC 25 Mux", "DMIC2", "DMIC2"},
	{"ADC 26 Mux", "DMIC1", "DMIC1"},
	{"ADC 26 Mux", "DMIC2", "DMIC2"},
};

static int wt712_sdca_dmic_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt712->component = component;

	if (!wt712->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_sdca_dev_wt712_dmic = {
	.pwobe = wt712_sdca_dmic_pwobe,
	.contwows = wt712_sdca_dmic_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt712_sdca_dmic_snd_contwows),
	.dapm_widgets = wt712_sdca_dmic_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt712_sdca_dmic_dapm_widgets),
	.dapm_woutes = wt712_sdca_dmic_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt712_sdca_dmic_audio_map),
	.endianness = 1,
};

static int wt712_sdca_dmic_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt712_sdca_dmic_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt712_sdca_dmic_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config;
	stwuct sdw_powt_config powt_config;
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw, num_channews;
	unsigned int sampwing_wate;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt712->swave)
		wetuwn -EINVAW;

	stweam_config.fwame_wate = pawams_wate(pawams);
	stweam_config.ch_count = pawams_channews(pawams);
	stweam_config.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	stweam_config.diwection = SDW_DATA_DIW_TX;

	num_channews = pawams_channews(pawams);
	powt_config.ch_mask = GENMASK(num_channews - 1, 0);
	powt_config.num = 2;

	wetvaw = sdw_stweam_add_swave(wt712->swave, &stweam_config,
					&powt_config, 1, sdw_stweam);
	if (wetvaw) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wetvaw;
	}

	if (pawams_channews(pawams) > 4) {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	/* sampwing wate configuwation */
	switch (pawams_wate(pawams)) {
	case 16000:
		sampwing_wate = WT712_SDCA_WATE_16000HZ;
		bweak;
	case 32000:
		sampwing_wate = WT712_SDCA_WATE_32000HZ;
		bweak;
	case 44100:
		sampwing_wate = WT712_SDCA_WATE_44100HZ;
		bweak;
	case 48000:
		sampwing_wate = WT712_SDCA_WATE_48000HZ;
		bweak;
	case 96000:
		sampwing_wate = WT712_SDCA_WATE_96000HZ;
		bweak;
	case 192000:
		sampwing_wate = WT712_SDCA_WATE_192000HZ;
		bweak;
	defauwt:
		dev_eww(component->dev, "Wate %d is not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* set sampwing fwequency */
	wegmap_wwite(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_CS1F, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
		sampwing_wate);
	wegmap_wwite(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_CS1C, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
		sampwing_wate);

	wetuwn 0;
}

static int wt712_sdca_dmic_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt712_sdca_dmic_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt712->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt712->swave, sdw_stweam);
	wetuwn 0;
}

#define WT712_STEWEO_WATES (SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
			SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000)
#define WT712_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wt712_sdca_dmic_ops = {
	.hw_pawams	= wt712_sdca_dmic_hw_pawams,
	.hw_fwee	= wt712_sdca_dmic_hw_fwee,
	.set_stweam	= wt712_sdca_dmic_set_sdw_stweam,
	.shutdown	= wt712_sdca_dmic_shutdown,
};

static stwuct snd_soc_dai_dwivew wt712_sdca_dmic_dai[] = {
	{
		.name = "wt712-sdca-dmic-aif1",
		.id = WT712_AIF1,
		.captuwe = {
			.stweam_name = "DP2 Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates = WT712_STEWEO_WATES,
			.fowmats = WT712_FOWMATS,
		},
		.ops = &wt712_sdca_dmic_ops,
	},
};

static int wt712_sdca_dmic_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave)
{
	stwuct wt712_sdca_dmic_pwiv *wt712;
	int wet;

	wt712 = devm_kzawwoc(dev, sizeof(*wt712), GFP_KEWNEW);
	if (!wt712)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt712);
	wt712->swave = swave;
	wt712->wegmap = wegmap;
	wt712->mbq_wegmap = mbq_wegmap;

	wegcache_cache_onwy(wt712->wegmap, twue);
	wegcache_cache_onwy(wt712->mbq_wegmap, twue);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt712->hw_init = fawse;
	wt712->fiwst_hw_init = fawse;
	wt712->fu1e_dapm_mute = twue;
	wt712->fu1e_mixew_mute[0] = wt712->fu1e_mixew_mute[1] =
		wt712->fu1e_mixew_mute[2] = wt712->fu1e_mixew_mute[3] = twue;

	wet =  devm_snd_soc_wegistew_component(dev,
			&soc_sdca_dev_wt712_dmic,
			wt712_sdca_dmic_dai,
			AWWAY_SIZE(wt712_sdca_dmic_dai));
	if (wet < 0)
		wetuwn wet;

	/* set autosuspend pawametews */
	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);

	/* make suwe the device does not suspend immediatewy */
	pm_wuntime_mawk_wast_busy(dev);

	pm_wuntime_enabwe(dev);

	/* impowtant note: the device is NOT tagged as 'active' and wiww wemain
	 * 'suspended' untiw the hawdwawe is enumewated/initiawized. This is wequiwed
	 * to make suwe the ASoC fwamewowk use of pm_wuntime_get_sync() does not siwentwy
	 * faiw with -EACCESS because of wace conditions between cawd cweation and enumewation
	 */

	dev_dbg(dev, "%s\n", __func__);

	wetuwn 0;
}


static int wt712_sdca_dmic_update_status(stwuct sdw_swave *swave,
				enum sdw_swave_status status)
{
	stwuct wt712_sdca_dmic_pwiv *wt712 = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_UNATTACHED)
		wt712->hw_init = fawse;

	/*
	 * Pewfowm initiawization onwy if swave status is pwesent and
	 * hw_init fwag is fawse
	 */
	if (wt712->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn wt712_sdca_dmic_io_init(&swave->dev, swave);
}

static int wt712_sdca_dmic_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw, i;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;

	pwop->paging_suppowt = twue;

	/* fiwst we need to awwocate memowy fow set bits in powt wists */
	pwop->souwce_powts = BIT(2); /* BITMAP: 00000100 */
	pwop->sink_powts = 0;

	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
		sizeof(*pwop->swc_dpn_pwop), GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->swc_dpn_pwop;
	addw = pwop->souwce_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* set the timeout vawues */
	pwop->cwk_stop_timeout = 200;

	/* wake-up event */
	pwop->wake_capabwe = 1;

	wetuwn 0;
}

static const stwuct sdw_device_id wt712_sdca_dmic_id[] = {
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x1712, 0x3, 0x1, 0),
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x1713, 0x3, 0x1, 0),
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x1716, 0x3, 0x1, 0),
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x1717, 0x3, 0x1, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, wt712_sdca_dmic_id);

static int __maybe_unused wt712_sdca_dmic_dev_suspend(stwuct device *dev)
{
	stwuct wt712_sdca_dmic_pwiv *wt712 = dev_get_dwvdata(dev);

	if (!wt712->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt712->wegmap, twue);
	wegcache_cache_onwy(wt712->mbq_wegmap, twue);

	wetuwn 0;
}

static int __maybe_unused wt712_sdca_dmic_dev_system_suspend(stwuct device *dev)
{
	stwuct wt712_sdca_dmic_pwiv *wt712_sdca = dev_get_dwvdata(dev);

	if (!wt712_sdca->hw_init)
		wetuwn 0;

	wetuwn wt712_sdca_dmic_dev_suspend(dev);
}

#define WT712_PWOBE_TIMEOUT 5000

static int __maybe_unused wt712_sdca_dmic_dev_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct wt712_sdca_dmic_pwiv *wt712 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!wt712->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest)
		goto wegmap_sync;

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
				msecs_to_jiffies(WT712_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(&swave->dev, "Initiawization not compwete, timed out\n");
		sdw_show_ping_status(swave->bus, twue);

		wetuwn -ETIMEDOUT;
	}

wegmap_sync:
	swave->unattach_wequest = 0;
	wegcache_cache_onwy(wt712->wegmap, fawse);
	wegcache_sync(wt712->wegmap);
	wegcache_cache_onwy(wt712->mbq_wegmap, fawse);
	wegcache_sync(wt712->mbq_wegmap);
	wetuwn 0;
}

static const stwuct dev_pm_ops wt712_sdca_dmic_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(wt712_sdca_dmic_dev_system_suspend, wt712_sdca_dmic_dev_wesume)
	SET_WUNTIME_PM_OPS(wt712_sdca_dmic_dev_suspend, wt712_sdca_dmic_dev_wesume, NUWW)
};


static stwuct sdw_swave_ops wt712_sdca_dmic_swave_ops = {
	.wead_pwop = wt712_sdca_dmic_wead_pwop,
	.update_status = wt712_sdca_dmic_update_status,
};

static int wt712_sdca_dmic_sdw_pwobe(stwuct sdw_swave *swave,
				const stwuct sdw_device_id *id)
{
	stwuct wegmap *wegmap, *mbq_wegmap;

	/* Wegmap Initiawization */
	mbq_wegmap = devm_wegmap_init_sdw_mbq(swave, &wt712_sdca_dmic_mbq_wegmap);
	if (IS_EWW(mbq_wegmap))
		wetuwn PTW_EWW(mbq_wegmap);

	wegmap = devm_wegmap_init_sdw(swave, &wt712_sdca_dmic_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wt712_sdca_dmic_init(&swave->dev, wegmap, mbq_wegmap, swave);
}

static int wt712_sdca_dmic_sdw_wemove(stwuct sdw_swave *swave)
{
	pm_wuntime_disabwe(&swave->dev);

	wetuwn 0;
}

static stwuct sdw_dwivew wt712_sdca_dmic_sdw_dwivew = {
	.dwivew = {
		.name = "wt712-sdca-dmic",
		.ownew = THIS_MODUWE,
		.pm = &wt712_sdca_dmic_pm,
	},
	.pwobe = wt712_sdca_dmic_sdw_pwobe,
	.wemove = wt712_sdca_dmic_sdw_wemove,
	.ops = &wt712_sdca_dmic_swave_ops,
	.id_tabwe = wt712_sdca_dmic_id,
};
moduwe_sdw_dwivew(wt712_sdca_dmic_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC WT712 SDCA DMIC SDW dwivew");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_WICENSE("GPW");
