// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt715-sdca.c -- wt715 AWSA SoC audio dwivew
//
// Copywight(c) 2020 Weawtek Semiconductow Cowp.
//
//
//

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>

#incwude "wt715-sdca.h"

static int wt715_sdca_index_wwite(stwuct wt715_sdca_pwiv *wt715,
		unsigned int nid, unsigned int weg, unsigned int vawue)
{
	stwuct wegmap *wegmap = wt715->mbq_wegmap;
	unsigned int addw;
	int wet;

	addw = (nid << 20) | weg;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt715->swave->dev,
			"Faiwed to set pwivate vawue: %08x <= %04x %d\n",
			addw, vawue, wet);

	wetuwn wet;
}

static int wt715_sdca_index_wead(stwuct wt715_sdca_pwiv *wt715,
		unsigned int nid, unsigned int weg, unsigned int *vawue)
{
	stwuct wegmap *wegmap = wt715->mbq_wegmap;
	unsigned int addw;
	int wet;

	addw = (nid << 20) | weg;

	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt715->swave->dev,
				"Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
				addw, *vawue, wet);

	wetuwn wet;
}

static int wt715_sdca_index_update_bits(stwuct wt715_sdca_pwiv *wt715,
	unsigned int nid, unsigned int weg, unsigned int mask, unsigned int vaw)
{
	unsigned int tmp;
	int wet;

	wet = wt715_sdca_index_wead(wt715, nid, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&tmp, mask, vaw);

	wetuwn wt715_sdca_index_wwite(wt715, nid, weg, tmp);
}

static inwine unsigned int wt715_sdca_vow_gain(unsigned int u_ctww_vaw,
		unsigned int vow_max, unsigned int vow_gain_sft)
{
	unsigned int vaw;

	if (u_ctww_vaw > vow_max)
		u_ctww_vaw = vow_max;
	vaw = u_ctww_vaw;
	u_ctww_vaw =
		((abs(u_ctww_vaw - vow_gain_sft) * WT715_SDCA_DB_STEP) << 8) / 1000;
	if (vaw <= vow_gain_sft) {
		u_ctww_vaw = ~u_ctww_vaw;
		u_ctww_vaw += 1;
	}
	u_ctww_vaw &= 0xffff;

	wetuwn u_ctww_vaw;
}

static inwine unsigned int wt715_sdca_boost_gain(unsigned int u_ctww_vaw,
		unsigned int b_max, unsigned int b_gain_sft)
{
	if (u_ctww_vaw > b_max)
		u_ctww_vaw = b_max;

	wetuwn (u_ctww_vaw * 10) << b_gain_sft;
}

static inwine unsigned int wt715_sdca_get_gain(unsigned int weg_vaw,
		unsigned int gain_sft)
{
	unsigned int neg_fwag = 0;

	if (weg_vaw & BIT(15)) {
		weg_vaw = ~(weg_vaw - 1) & 0xffff;
		neg_fwag = 1;
	}
	weg_vaw *= 1000;
	weg_vaw >>= 8;
	if (neg_fwag)
		weg_vaw = gain_sft - weg_vaw / WT715_SDCA_DB_STEP;
	ewse
		weg_vaw = gain_sft + weg_vaw / WT715_SDCA_DB_STEP;

	wetuwn weg_vaw;
}

/* SDCA Vowume/Boost contwow */
static int wt715_sdca_set_amp_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	unsigned int gain_vaw, i, k_changed = 0;
	int wet;

	fow (i = 0; i < 2; i++) {
		if (ucontwow->vawue.integew.vawue[i] != wt715->kctw_2ch_owig[i]) {
			k_changed = 1;
			bweak;
		}
	}

	fow (i = 0; i < 2; i++) {
		wt715->kctw_2ch_owig[i] = ucontwow->vawue.integew.vawue[i];
		gain_vaw =
			wt715_sdca_vow_gain(ucontwow->vawue.integew.vawue[i], mc->max,
				mc->shift);
		wet = wegmap_wwite(wt715->mbq_wegmap, mc->weg + i, gain_vaw);
		if (wet != 0) {
			dev_eww(component->dev, "Faiwed to wwite 0x%x=0x%x\n",
				mc->weg + i, gain_vaw);
			wetuwn wet;
		}
	}

	wetuwn k_changed;
}

static int wt715_sdca_set_amp_gain_4ch_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int weg_base = p->weg_base, k_changed = 0;
	const unsigned int gain_sft = 0x2f;
	unsigned int gain_vaw, i;
	int wet;

	fow (i = 0; i < 4; i++) {
		if (ucontwow->vawue.integew.vawue[i] != wt715->kctw_4ch_owig[i]) {
			k_changed = 1;
			bweak;
		}
	}

	fow (i = 0; i < 4; i++) {
		wt715->kctw_4ch_owig[i] = ucontwow->vawue.integew.vawue[i];
		gain_vaw =
			wt715_sdca_vow_gain(ucontwow->vawue.integew.vawue[i], p->max,
				gain_sft);
		wet = wegmap_wwite(wt715->mbq_wegmap, weg_base + i,
				gain_vaw);
		if (wet != 0) {
			dev_eww(component->dev, "Faiwed to wwite 0x%x=0x%x\n",
				weg_base + i, gain_vaw);
			wetuwn wet;
		}
	}

	wetuwn k_changed;
}

static int wt715_sdca_set_amp_gain_8ch_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int weg_base = p->weg_base, i, k_changed = 0;
	const unsigned int gain_sft = 8;
	unsigned int gain_vaw, weg;
	int wet;

	fow (i = 0; i < 8; i++) {
		if (ucontwow->vawue.integew.vawue[i] != wt715->kctw_8ch_owig[i]) {
			k_changed = 1;
			bweak;
		}
	}

	fow (i = 0; i < 8; i++) {
		wt715->kctw_8ch_owig[i] = ucontwow->vawue.integew.vawue[i];
		gain_vaw =
			wt715_sdca_boost_gain(ucontwow->vawue.integew.vawue[i], p->max,
				gain_sft);
		weg = i < 7 ? weg_base + i : (weg_base - 1) | BIT(15);
		wet = wegmap_wwite(wt715->mbq_wegmap, weg, gain_vaw);
		if (wet != 0) {
			dev_eww(component->dev, "Faiwed to wwite 0x%x=0x%x\n",
				weg, gain_vaw);
			wetuwn wet;
		}
	}

	wetuwn k_changed;
}

static int wt715_sdca_set_amp_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw, i;
	int wet;

	fow (i = 0; i < 2; i++) {
		wet = wegmap_wead(wt715->mbq_wegmap, mc->weg + i, &vaw);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to wead 0x%x, wet=%d\n",
				mc->weg + i, wet);
			wetuwn wet;
		}
		ucontwow->vawue.integew.vawue[i] = wt715_sdca_get_gain(vaw, mc->shift);
	}

	wetuwn 0;
}

static int wt715_sdca_set_amp_gain_4ch_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int weg_base = p->weg_base, i;
	const unsigned int gain_sft = 0x2f;
	unsigned int vaw;
	int wet;

	fow (i = 0; i < 4; i++) {
		wet = wegmap_wead(wt715->mbq_wegmap, weg_base + i, &vaw);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to wead 0x%x, wet=%d\n",
				weg_base + i, wet);
			wetuwn wet;
		}
		ucontwow->vawue.integew.vawue[i] = wt715_sdca_get_gain(vaw, gain_sft);
	}

	wetuwn 0;
}

static int wt715_sdca_set_amp_gain_8ch_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int weg_base = p->weg_base;
	const unsigned int gain_sft = 8;
	unsigned int vaw_w, vaw_w;
	unsigned int i, weg;
	int wet;

	fow (i = 0; i < 8; i += 2) {
		wet = wegmap_wead(wt715->mbq_wegmap, weg_base + i, &vaw_w);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to wead 0x%x, wet=%d\n",
					weg_base + i, wet);
			wetuwn wet;
		}
		ucontwow->vawue.integew.vawue[i] = (vaw_w >> gain_sft) / 10;

		weg = (i == 6) ? (weg_base - 1) | BIT(15) : weg_base + 1 + i;
		wet = wegmap_wead(wt715->mbq_wegmap, weg, &vaw_w);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to wead 0x%x, wet=%d\n",
					weg, wet);
			wetuwn wet;
		}
		ucontwow->vawue.integew.vawue[i + 1] = (vaw_w >> gain_sft) / 10;
	}

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -17625, 375, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static int wt715_sdca_get_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int weg_base = p->weg_base;
	unsigned int invewt = p->invewt, i;
	int vaw;

	fow (i = 0; i < p->count; i += 2) {
		vaw = snd_soc_component_wead(component, weg_base + i);
		if (vaw < 0)
			wetuwn -EINVAW;
		ucontwow->vawue.integew.vawue[i] = invewt ? p->max - vaw : vaw;

		vaw = snd_soc_component_wead(component, weg_base + 1 + i);
		if (vaw < 0)
			wetuwn -EINVAW;
		ucontwow->vawue.integew.vawue[i + 1] =
			invewt ? p->max - vaw : vaw;
	}

	wetuwn 0;
}

static int wt715_sdca_put_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;
	unsigned int vaw[4] = {0}, vaw_mask, i, k_changed = 0;
	unsigned int weg = p->weg_base;
	unsigned int shift = p->shift;
	unsigned int max = p->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = p->invewt;
	int eww;

	fow (i = 0; i < 4; i++) {
		if (ucontwow->vawue.integew.vawue[i] != wt715->kctw_switch_owig[i]) {
			k_changed = 1;
			bweak;
		}
	}

	fow (i = 0; i < 2; i++) {
		wt715->kctw_switch_owig[i * 2] = ucontwow->vawue.integew.vawue[i * 2];
		vaw[i * 2] = ucontwow->vawue.integew.vawue[i * 2] & mask;
		if (invewt)
			vaw[i * 2] = max - vaw[i * 2];
		vaw_mask = mask << shift;
		vaw[i * 2] <<= shift;

		wt715->kctw_switch_owig[i * 2 + 1] =
			ucontwow->vawue.integew.vawue[i * 2 + 1];
		vaw[i * 2 + 1] =
			ucontwow->vawue.integew.vawue[i * 2 + 1] & mask;
		if (invewt)
			vaw[i * 2 + 1] = max - vaw[i * 2 + 1];

		vaw[i * 2 + 1] <<=  shift;

		eww = snd_soc_component_update_bits(component, weg + i * 2, vaw_mask,
				vaw[i * 2]);
		if (eww < 0)
			wetuwn eww;

		eww = snd_soc_component_update_bits(component, weg + 1 + i * 2,
			vaw_mask, vaw[i * 2 + 1]);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn k_changed;
}

static int wt715_sdca_fu_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wt715_sdca_kcontwow_pwivate *p =
		(stwuct wt715_sdca_kcontwow_pwivate *)kcontwow->pwivate_vawue;

	if (p->max == 1)
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = p->count;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = p->max;
	wetuwn 0;
}

#define WT715_SDCA_PW_VAWUE(xweg_base, xcount, xmax, xshift, xinvewt) \
	((unsigned wong)&(stwuct wt715_sdca_kcontwow_pwivate) \
		{.weg_base = xweg_base, .count = xcount, .max = xmax, \
		.shift = xshift, .invewt = xinvewt})

#define WT715_SDCA_FU_CTWW(xname, weg_base, xshift, xmax, xinvewt, xcount) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.info = wt715_sdca_fu_info, \
	.get = wt715_sdca_get_vowsw, \
	.put = wt715_sdca_put_vowsw, \
	.pwivate_vawue = WT715_SDCA_PW_VAWUE(weg_base, xcount, xmax, \
					xshift, xinvewt)}

#define SOC_DOUBWE_W_EXT(xname, weg_weft, weg_wight, xshift, xmax, xinvewt,\
	 xhandwew_get, xhandwew_put) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.info = snd_soc_info_vowsw, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = SOC_DOUBWE_W_VAWUE(weg_weft, weg_wight, xshift, \
					    xmax, xinvewt) }

#define WT715_SDCA_EXT_TWV(xname, weg_base, xhandwew_get,\
	 xhandwew_put, twv_awway, xcount, xmax) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (twv_awway), \
	.info = wt715_sdca_fu_info, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = WT715_SDCA_PW_VAWUE(weg_base, xcount, xmax, 0, 0) }

#define WT715_SDCA_BOOST_EXT_TWV(xname, weg_base, xhandwew_get,\
	 xhandwew_put, twv_awway, xcount, xmax) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (twv_awway), \
	.info = wt715_sdca_fu_info, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = WT715_SDCA_PW_VAWUE(weg_base, xcount, xmax, 0, 0) }

static const stwuct snd_kcontwow_new wt715_sdca_snd_contwows[] = {
	/* Captuwe switch */
	SOC_DOUBWE_W("FU0A Captuwe Switch",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC7_27_VOW,
			WT715_SDCA_FU_MUTE_CTWW, CH_01),
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC7_27_VOW,
			WT715_SDCA_FU_MUTE_CTWW, CH_02),
			0, 1, 1),
	WT715_SDCA_FU_CTWW("FU02 Captuwe Switch",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC8_9_VOW,
			WT715_SDCA_FU_MUTE_CTWW, CH_01),
			0, 1, 1, 4),
	WT715_SDCA_FU_CTWW("FU06 Captuwe Switch",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC10_11_VOW,
			WT715_SDCA_FU_MUTE_CTWW, CH_01),
			0, 1, 1, 4),
	/* Vowume Contwow */
	SOC_DOUBWE_W_EXT_TWV("FU0A Captuwe Vowume",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC7_27_VOW,
			WT715_SDCA_FU_VOW_CTWW, CH_01),
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC7_27_VOW,
			WT715_SDCA_FU_VOW_CTWW, CH_02),
			0x2f, 0x7f, 0,
		wt715_sdca_set_amp_gain_get, wt715_sdca_set_amp_gain_put,
		in_vow_twv),
	WT715_SDCA_EXT_TWV("FU02 Captuwe Vowume",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC8_9_VOW,
			WT715_SDCA_FU_VOW_CTWW, CH_01),
		wt715_sdca_set_amp_gain_4ch_get,
		wt715_sdca_set_amp_gain_4ch_put,
		in_vow_twv, 4, 0x7f),
	WT715_SDCA_EXT_TWV("FU06 Captuwe Vowume",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_ADC10_11_VOW,
			WT715_SDCA_FU_VOW_CTWW, CH_01),
		wt715_sdca_set_amp_gain_4ch_get,
		wt715_sdca_set_amp_gain_4ch_put,
		in_vow_twv, 4, 0x7f),
	/* MIC Boost Contwow */
	WT715_SDCA_BOOST_EXT_TWV("FU0E Boost",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_DMIC_GAIN_EN,
			WT715_SDCA_FU_DMIC_GAIN_CTWW, CH_01),
			wt715_sdca_set_amp_gain_8ch_get,
			wt715_sdca_set_amp_gain_8ch_put,
			mic_vow_twv, 8, 3),
	WT715_SDCA_BOOST_EXT_TWV("FU0C Boost",
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_FU_AMIC_GAIN_EN,
			WT715_SDCA_FU_DMIC_GAIN_CTWW, CH_01),
			wt715_sdca_set_amp_gain_8ch_get,
			wt715_sdca_set_amp_gain_8ch_put,
			mic_vow_twv, 8, 3),
};

static int wt715_sdca_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw, mask_sft;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		mask_sft = 8;
	ewse if (stwstw(ucontwow->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	ewse if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	ewse
		wetuwn -EINVAW;

	wt715_sdca_index_wead(wt715, WT715_VENDOW_HDA_CTW,
		WT715_HDA_WEGACY_MUX_CTW1, &vaw);
	vaw = (vaw >> mask_sft) & 0xf;

	/*
	 * The fiwst two indices of ADC Mux 24/25 awe wouted to the same
	 * hawdwawe souwce. ie, ADC Mux 24 0/1 wiww both connect to MIC2.
	 * To have a unique set of inputs, we skip the index1 of the muxes.
	 */
	if ((stwstw(ucontwow->id.name, "ADC 24 Mux") ||
		stwstw(ucontwow->id.name, "ADC 25 Mux")) && vaw > 0)
		vaw -= 1;
	ucontwow->vawue.enumewated.item[0] = vaw;

	wetuwn 0;
}

static int wt715_sdca_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
				snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, vaw2 = 0, change, mask_sft;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		mask_sft = 8;
	ewse if (stwstw(ucontwow->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	ewse if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	ewse
		wetuwn -EINVAW;

	/* Vewb ID = 0x701h, nid = e->weg */
	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	wt715_sdca_index_wead(wt715, WT715_VENDOW_HDA_CTW,
		WT715_HDA_WEGACY_MUX_CTW1, &vaw2);
	vaw2 = (vaw2 >> mask_sft) & 0xf;

	change = vaw != vaw2;

	if (change)
		wt715_sdca_index_update_bits(wt715, WT715_VENDOW_HDA_CTW,
			WT715_HDA_WEGACY_MUX_CTW1, 0xf << mask_sft, vaw << mask_sft);

	snd_soc_dapm_mux_update_powew(dapm, kcontwow, item[0], e, NUWW);

	wetuwn change;
}

static const chaw * const adc_22_23_mux_text[] = {
	"MIC1",
	"MIC2",
	"WINE1",
	"WINE2",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
};

/*
 * Due to mux design fow nid 24 (MUX_IN3)/25 (MUX_IN4), connection index 0 and
 * 1 wiww be connected to the same dmic souwce, thewefowe we skip index 1 to
 * avoid misundewstanding on usage of dapm wouting.
 */
static int wt715_adc_24_25_vawues[] = {
	0,
	2,
	3,
	4,
	5,
};

static const chaw * const adc_24_mux_text[] = {
	"MIC2",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
};

static const chaw * const adc_25_mux_text[] = {
	"MIC1",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
};

static SOC_ENUM_SINGWE_DECW(wt715_adc22_enum, SND_SOC_NOPM, 0,
	adc_22_23_mux_text);

static SOC_ENUM_SINGWE_DECW(wt715_adc23_enum, SND_SOC_NOPM, 0,
	adc_22_23_mux_text);

static SOC_VAWUE_ENUM_SINGWE_DECW(wt715_adc24_enum,
	SND_SOC_NOPM, 0, 0xf,
	adc_24_mux_text, wt715_adc_24_25_vawues);
static SOC_VAWUE_ENUM_SINGWE_DECW(wt715_adc25_enum,
	SND_SOC_NOPM, 0, 0xf,
	adc_25_mux_text, wt715_adc_24_25_vawues);

static const stwuct snd_kcontwow_new wt715_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", wt715_adc22_enum,
			wt715_sdca_mux_get, wt715_sdca_mux_put);

static const stwuct snd_kcontwow_new wt715_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", wt715_adc23_enum,
			wt715_sdca_mux_get, wt715_sdca_mux_put);

static const stwuct snd_kcontwow_new wt715_adc24_mux =
	SOC_DAPM_ENUM_EXT("ADC 24 Mux", wt715_adc24_enum,
			wt715_sdca_mux_get, wt715_sdca_mux_put);

static const stwuct snd_kcontwow_new wt715_adc25_mux =
	SOC_DAPM_ENUM_EXT("ADC 25 Mux", wt715_adc25_enum,
			wt715_sdca_mux_get, wt715_sdca_mux_put);

static int wt715_sdca_pde23_24_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt715->wegmap,
			SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_CWEQ_POW_EN,
				WT715_SDCA_WEQ_POW_CTWW,
				CH_00), 0x00);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt715->wegmap,
			SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_CWEQ_POW_EN,
				WT715_SDCA_WEQ_POW_CTWW,
				CH_00), 0x03);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt715_sdca_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("DMIC3"),
	SND_SOC_DAPM_INPUT("DMIC4"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("WINE2"),

	SND_SOC_DAPM_SUPPWY("PDE23_24", SND_SOC_NOPM, 0, 0,
		wt715_sdca_pde23_24_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_ADC("ADC 07", NUWW, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 08", NUWW, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 09", NUWW, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 27", NUWW, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&wt715_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&wt715_adc23_mux),
	SND_SOC_DAPM_MUX("ADC 24 Mux", SND_SOC_NOPM, 0, 0,
		&wt715_adc24_mux),
	SND_SOC_DAPM_MUX("ADC 25 Mux", SND_SOC_NOPM, 0, 0,
		&wt715_adc25_mux),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP6TX", "DP6 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt715_sdca_audio_map[] = {
	{"DP6TX", NUWW, "ADC 09"},
	{"DP6TX", NUWW, "ADC 08"},
	{"DP4TX", NUWW, "ADC 07"},
	{"DP4TX", NUWW, "ADC 27"},
	{"DP4TX", NUWW, "ADC 09"},
	{"DP4TX", NUWW, "ADC 08"},

	{"WINE1", NUWW, "PDE23_24"},
	{"WINE2", NUWW, "PDE23_24"},
	{"MIC1", NUWW, "PDE23_24"},
	{"MIC2", NUWW, "PDE23_24"},
	{"DMIC1", NUWW, "PDE23_24"},
	{"DMIC2", NUWW, "PDE23_24"},
	{"DMIC3", NUWW, "PDE23_24"},
	{"DMIC4", NUWW, "PDE23_24"},

	{"ADC 09", NUWW, "ADC 22 Mux"},
	{"ADC 08", NUWW, "ADC 23 Mux"},
	{"ADC 07", NUWW, "ADC 24 Mux"},
	{"ADC 27", NUWW, "ADC 25 Mux"},
	{"ADC 22 Mux", "MIC1", "MIC1"},
	{"ADC 22 Mux", "MIC2", "MIC2"},
	{"ADC 22 Mux", "WINE1", "WINE1"},
	{"ADC 22 Mux", "WINE2", "WINE2"},
	{"ADC 22 Mux", "DMIC1", "DMIC1"},
	{"ADC 22 Mux", "DMIC2", "DMIC2"},
	{"ADC 22 Mux", "DMIC3", "DMIC3"},
	{"ADC 22 Mux", "DMIC4", "DMIC4"},
	{"ADC 23 Mux", "MIC1", "MIC1"},
	{"ADC 23 Mux", "MIC2", "MIC2"},
	{"ADC 23 Mux", "WINE1", "WINE1"},
	{"ADC 23 Mux", "WINE2", "WINE2"},
	{"ADC 23 Mux", "DMIC1", "DMIC1"},
	{"ADC 23 Mux", "DMIC2", "DMIC2"},
	{"ADC 23 Mux", "DMIC3", "DMIC3"},
	{"ADC 23 Mux", "DMIC4", "DMIC4"},
	{"ADC 24 Mux", "MIC2", "MIC2"},
	{"ADC 24 Mux", "DMIC1", "DMIC1"},
	{"ADC 24 Mux", "DMIC2", "DMIC2"},
	{"ADC 24 Mux", "DMIC3", "DMIC3"},
	{"ADC 24 Mux", "DMIC4", "DMIC4"},
	{"ADC 25 Mux", "MIC1", "MIC1"},
	{"ADC 25 Mux", "DMIC1", "DMIC1"},
	{"ADC 25 Mux", "DMIC2", "DMIC2"},
	{"ADC 25 Mux", "DMIC3", "DMIC3"},
	{"ADC 25 Mux", "DMIC4", "DMIC4"},
};

static int wt715_sdca_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	int wet;

	if (!wt715->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_wt715_sdca = {
	.pwobe = wt715_sdca_pwobe,
	.contwows = wt715_sdca_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt715_sdca_snd_contwows),
	.dapm_widgets = wt715_sdca_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt715_sdca_dapm_widgets),
	.dapm_woutes = wt715_sdca_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt715_sdca_audio_map),
	.endianness = 1,
};

static int wt715_sdca_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt715_sdca_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)

{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt715_sdca_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw;
	unsigned int vaw;

	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt715->swave)
		wetuwn -EINVAW;

	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	switch (dai->id) {
	case WT715_AIF1:
		powt_config.num = 6;
		wt715_sdca_index_wwite(wt715, WT715_VENDOW_WEG, WT715_SDW_INPUT_SEW,
			0xa500);
		bweak;
	case WT715_AIF2:
		powt_config.num = 4;
		wt715_sdca_index_wwite(wt715, WT715_VENDOW_WEG, WT715_SDW_INPUT_SEW,
			0xaf00);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI id %d\n", dai->id);
		wetuwn -EINVAW;
	}

	wetvaw = sdw_stweam_add_swave(wt715->swave, &stweam_config,
					&powt_config, 1, sdw_stweam);
	if (wetvaw) {
		dev_eww(component->dev, "Unabwe to configuwe powt, wetvaw:%d\n",
			wetvaw);
		wetuwn wetvaw;
	}

	switch (pawams_wate(pawams)) {
	case 8000:
		vaw = 0x1;
		bweak;
	case 11025:
		vaw = 0x2;
		bweak;
	case 12000:
		vaw = 0x3;
		bweak;
	case 16000:
		vaw = 0x4;
		bweak;
	case 22050:
		vaw = 0x5;
		bweak;
	case 24000:
		vaw = 0x6;
		bweak;
	case 32000:
		vaw = 0x7;
		bweak;
	case 44100:
		vaw = 0x8;
		bweak;
	case 48000:
		vaw = 0x9;
		bweak;
	case 88200:
		vaw = 0xa;
		bweak;
	case 96000:
		vaw = 0xb;
		bweak;
	case 176400:
		vaw = 0xc;
		bweak;
	case 192000:
		vaw = 0xd;
		bweak;
	case 384000:
		vaw = 0xe;
		bweak;
	case 768000:
		vaw = 0xf;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted sampwe wate %d\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	wegmap_wwite(wt715->wegmap,
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_CS_FWEQ_IND_EN,
			WT715_SDCA_FWEQ_IND_CTWW, CH_00), vaw);

	wetuwn 0;
}

static int wt715_sdca_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt715_sdca_pwiv *wt715 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt715->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt715->swave, sdw_stweam);
	wetuwn 0;
}

#define WT715_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define WT715_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt715_sdca_ops = {
	.hw_pawams	= wt715_sdca_pcm_hw_pawams,
	.hw_fwee	= wt715_sdca_pcm_hw_fwee,
	.set_stweam	= wt715_sdca_set_sdw_stweam,
	.shutdown	= wt715_sdca_shutdown,
};

static stwuct snd_soc_dai_dwivew wt715_sdca_dai[] = {
	{
		.name = "wt715-aif1",
		.id = WT715_AIF1,
		.captuwe = {
			.stweam_name = "DP6 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT715_STEWEO_WATES,
			.fowmats = WT715_FOWMATS,
		},
		.ops = &wt715_sdca_ops,
	},
	{
		.name = "wt715-aif2",
		.id = WT715_AIF2,
		.captuwe = {
			.stweam_name = "DP4 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT715_STEWEO_WATES,
			.fowmats = WT715_FOWMATS,
		},
		.ops = &wt715_sdca_ops,
	},
};

/* Bus cwock fwequency */
#define WT715_CWK_FWEQ_9600000HZ 9600000
#define WT715_CWK_FWEQ_12000000HZ 12000000
#define WT715_CWK_FWEQ_6000000HZ 6000000
#define WT715_CWK_FWEQ_4800000HZ 4800000
#define WT715_CWK_FWEQ_2400000HZ 2400000
#define WT715_CWK_FWEQ_12288000HZ 12288000

int wt715_sdca_init(stwuct device *dev, stwuct wegmap *mbq_wegmap,
	stwuct wegmap *wegmap, stwuct sdw_swave *swave)
{
	stwuct wt715_sdca_pwiv *wt715;
	int wet;

	wt715 = devm_kzawwoc(dev, sizeof(*wt715), GFP_KEWNEW);
	if (!wt715)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt715);
	wt715->swave = swave;
	wt715->wegmap = wegmap;
	wt715->mbq_wegmap = mbq_wegmap;
	wt715->hw_sdw_vew = swave->id.sdw_vewsion;

	wegcache_cache_onwy(wt715->wegmap, twue);
	wegcache_cache_onwy(wt715->mbq_wegmap, twue);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt715->hw_init = fawse;
	wt715->fiwst_hw_init = fawse;

	wet = devm_snd_soc_wegistew_component(dev,
			&soc_codec_dev_wt715_sdca,
			wt715_sdca_dai,
			AWWAY_SIZE(wt715_sdca_dai));
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

	wetuwn wet;
}

int wt715_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt715_sdca_pwiv *wt715 = dev_get_dwvdata(dev);
	unsigned int hw_vew;

	if (wt715->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt715->wegmap, fawse);
	wegcache_cache_onwy(wt715->mbq_wegmap, fawse);

	/*
	 * PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
	 */
	if (!wt715->fiwst_hw_init) {
		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);

		wt715->fiwst_hw_init = twue;
	}

	pm_wuntime_get_nowesume(&swave->dev);

	wt715_sdca_index_wead(wt715, WT715_VENDOW_WEG,
		WT715_PWODUCT_NUM, &hw_vew);
	hw_vew = hw_vew & 0x000f;

	/* set cwock sewectow = extewnaw */
	wegmap_wwite(wt715->wegmap,
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_CX_CWK_SEW_EN,
			WT715_SDCA_CX_CWK_SEW_CTWW, CH_00), 0x1);
	/* set GPIO_4/5/6 to be 3wd/4th DMIC usage */
	if (hw_vew == 0x0)
		wt715_sdca_index_update_bits(wt715, WT715_VENDOW_WEG,
			WT715_AD_FUNC_EN, 0x54, 0x54);
	ewse if (hw_vew == 0x1) {
		wt715_sdca_index_update_bits(wt715, WT715_VENDOW_WEG,
			WT715_AD_FUNC_EN, 0x55, 0x55);
		wt715_sdca_index_update_bits(wt715, WT715_VENDOW_WEG,
			WT715_WEV_1, 0x40, 0x40);
	}
	/* DFWW Cawibwation twiggew */
	wt715_sdca_index_update_bits(wt715, WT715_VENDOW_WEG,
			WT715_DFWW_VAD, 0x1, 0x1);
	/* twiggew mode = VAD enabwe */
	wegmap_wwite(wt715->wegmap,
		SDW_SDCA_CTW(FUN_MIC_AWWAY, WT715_SDCA_SMPU_TWIG_ST_EN,
			WT715_SDCA_SMPU_TWIG_EN_CTWW, CH_00), 0x2);
	/* SMPU-1 intewwupt enabwe mask */
	wegmap_update_bits(wt715->wegmap, WT715_INT_MASK, 0x1, 0x1);

	/* Mawk Swave initiawization compwete */
	wt715->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC wt715 dwivew SDW SDCA");
MODUWE_AUTHOW("Jack Yu <jack.yu@weawtek.com>");
MODUWE_WICENSE("GPW v2");
