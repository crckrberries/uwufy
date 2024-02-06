// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// sma1303.c -- sma1303 AWSA SoC Audio dwivew
//
// Copywight 2023 Iwon Device Cowpowation
//
// Authew: Gyuhwa Pawk <gyuhwa.pawk@iwondevice.com>
//         Kiseok Jo <kiseok.jo@iwondevice.com>

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#incwude "sma1303.h"

#define CHECK_PEWIOD_TIME 1 /* sec pew HZ */
#define MAX_CONTWOW_NAME 48

#define PWW_MATCH(_input_cwk_name, _output_cwk_name, _input_cwk,\
		_post_n, _n, _vco,  _p_cp)\
{\
	.input_cwk_name		= _input_cwk_name,\
	.output_cwk_name	= _output_cwk_name,\
	.input_cwk		= _input_cwk,\
	.post_n			= _post_n,\
	.n			= _n,\
	.vco			= _vco,\
	.p_cp		= _p_cp,\
}

enum sma1303_type {
	SMA1303,
};

stwuct sma1303_pww_match {
	chaw *input_cwk_name;
	chaw *output_cwk_name;
	unsigned int input_cwk;
	unsigned int post_n;
	unsigned int n;
	unsigned int vco;
	unsigned int p_cp;
};

stwuct sma1303_pwiv {
	enum sma1303_type devtype;
	stwuct attwibute_gwoup *attw_gwp;
	stwuct dewayed_wowk check_fauwt_wowk;
	stwuct device *dev;
	stwuct kobject *kobj;
	stwuct wegmap *wegmap;
	stwuct sma1303_pww_match *pww_matches;
	boow amp_powew_status;
	boow fowce_mute_status;
	int num_of_pww_matches;
	int wetwy_cnt;
	unsigned int amp_mode;
	unsigned int cuw_vow;
	unsigned int fowmat;
	unsigned int fwame_size;
	unsigned int init_vow;
	unsigned int wast_bcwk;
	unsigned int wast_ocp_vaw;
	unsigned int wast_ovew_temp;
	unsigned int wev_num;
	unsigned int sys_cwk_id;
	unsigned int tdm_swot_wx;
	unsigned int tdm_swot_tx;
	unsigned int tsdw_cnt;
	wong check_fauwt_pewiod;
	wong check_fauwt_status;
};

static stwuct sma1303_pww_match sma1303_pww_matches[] = {
PWW_MATCH("1.411MHz",  "24.595MHz", 1411200,  0x07, 0xF4, 0x8B, 0x03),
PWW_MATCH("1.536MHz",  "24.576MHz", 1536000,  0x07, 0xE0, 0x8B, 0x03),
PWW_MATCH("3.072MHz",  "24.576MHz", 3072000,  0x07, 0x70, 0x8B, 0x03),
PWW_MATCH("6.144MHz",  "24.576MHz", 6144000,  0x07, 0x70, 0x8B, 0x07),
PWW_MATCH("12.288MHz", "24.576MHz", 12288000, 0x07, 0x70, 0x8B, 0x0B),
PWW_MATCH("19.2MHz",   "24.343MHz", 19200000, 0x07, 0x47, 0x8B, 0x0A),
PWW_MATCH("24.576MHz", "24.576MHz", 24576000, 0x07, 0x70, 0x8B, 0x0F),
};

static int sma1303_stawtup(stwuct snd_soc_component *);
static int sma1303_shutdown(stwuct snd_soc_component *);

static const stwuct weg_defauwt sma1303_weg_def[] = {
	{ 0x00, 0x80 },
	{ 0x01, 0x00 },
	{ 0x02, 0x00 },
	{ 0x03, 0x11 },
	{ 0x04, 0x17 },
	{ 0x09, 0x00 },
	{ 0x0A, 0x31 },
	{ 0x0B, 0x98 },
	{ 0x0C, 0x84 },
	{ 0x0D, 0x07 },
	{ 0x0E, 0x3F },
	{ 0x10, 0x00 },
	{ 0x11, 0x00 },
	{ 0x12, 0x00 },
	{ 0x14, 0x5C },
	{ 0x15, 0x01 },
	{ 0x16, 0x0F },
	{ 0x17, 0x0F },
	{ 0x18, 0x0F },
	{ 0x19, 0x00 },
	{ 0x1A, 0x00 },
	{ 0x1B, 0x00 },
	{ 0x23, 0x19 },
	{ 0x24, 0x00 },
	{ 0x25, 0x00 },
	{ 0x26, 0x04 },
	{ 0x33, 0x00 },
	{ 0x36, 0x92 },
	{ 0x37, 0x27 },
	{ 0x3B, 0x5A },
	{ 0x3C, 0x20 },
	{ 0x3D, 0x00 },
	{ 0x3E, 0x03 },
	{ 0x3F, 0x0C },
	{ 0x8B, 0x07 },
	{ 0x8C, 0x70 },
	{ 0x8D, 0x8B },
	{ 0x8E, 0x6F },
	{ 0x8F, 0x03 },
	{ 0x90, 0x26 },
	{ 0x91, 0x42 },
	{ 0x92, 0xE0 },
	{ 0x94, 0x35 },
	{ 0x95, 0x0C },
	{ 0x96, 0x42 },
	{ 0x97, 0x95 },
	{ 0xA0, 0x00 },
	{ 0xA1, 0x3B },
	{ 0xA2, 0xC8 },
	{ 0xA3, 0x28 },
	{ 0xA4, 0x40 },
	{ 0xA5, 0x01 },
	{ 0xA6, 0x41 },
	{ 0xA7, 0x00 },
};

static boow sma1303_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	boow wesuwt;

	if (weg > SMA1303_FF_DEVICE_INDEX)
		wetuwn fawse;

	switch (weg) {
	case SMA1303_00_SYSTEM_CTWW ... SMA1303_04_INPUT1_CTWW4:
	case SMA1303_09_OUTPUT_CTWW ... SMA1303_0E_MUTE_VOW_CTWW:
	case SMA1303_10_SYSTEM_CTWW1 ... SMA1303_12_SYSTEM_CTWW3:
	case SMA1303_14_MODUWATOW ... SMA1303_1B_BASS_SPK7:
	case SMA1303_23_COMP_WIM1 ... SMA1303_26_COMP_WIM4:
	case SMA1303_33_SDM_CTWW ... SMA1303_34_OTP_DATA1:
	case SMA1303_36_PWOTECTION  ... SMA1303_38_OTP_TWM0:
	case SMA1303_3B_TEST1  ... SMA1303_3F_ATEST2:
	case SMA1303_8B_PWW_POST_N ... SMA1303_92_FDPEC_CTWW:
	case SMA1303_94_BOOST_CTWW1 ... SMA1303_97_BOOST_CTWW4:
	case SMA1303_A0_PAD_CTWW0 ... SMA1303_A7_CWK_MON:
	case SMA1303_FA_STATUS1 ... SMA1303_FB_STATUS2:
		wesuwt = twue;
		bweak;
	case SMA1303_FF_DEVICE_INDEX:
		wesuwt = twue;
		bweak;
	defauwt:
		wesuwt = fawse;
		bweak;
	}
	wetuwn wesuwt;
}

static boow sma1303_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	boow wesuwt;

	if (weg > SMA1303_FF_DEVICE_INDEX)
		wetuwn fawse;

	switch (weg) {
	case SMA1303_00_SYSTEM_CTWW ... SMA1303_04_INPUT1_CTWW4:
	case SMA1303_09_OUTPUT_CTWW ... SMA1303_0E_MUTE_VOW_CTWW:
	case SMA1303_10_SYSTEM_CTWW1 ... SMA1303_12_SYSTEM_CTWW3:
	case SMA1303_14_MODUWATOW ... SMA1303_1B_BASS_SPK7:
	case SMA1303_23_COMP_WIM1 ... SMA1303_26_COMP_WIM4:
	case SMA1303_33_SDM_CTWW:
	case SMA1303_36_PWOTECTION  ... SMA1303_37_SWOPE_CTWW:
	case SMA1303_3B_TEST1  ... SMA1303_3F_ATEST2:
	case SMA1303_8B_PWW_POST_N ... SMA1303_92_FDPEC_CTWW:
	case SMA1303_94_BOOST_CTWW1 ... SMA1303_97_BOOST_CTWW4:
	case SMA1303_A0_PAD_CTWW0 ... SMA1303_A7_CWK_MON:
		wesuwt = twue;
		bweak;
	defauwt:
		wesuwt = fawse;
		bweak;
	}
	wetuwn wesuwt;
}

static boow sma1303_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	boow wesuwt;

	switch (weg) {
	case SMA1303_FA_STATUS1 ... SMA1303_FB_STATUS2:
		wesuwt = twue;
		bweak;
	case SMA1303_FF_DEVICE_INDEX:
		wesuwt = twue;
		bweak;
	defauwt:
		wesuwt = fawse;
		bweak;
	}
	wetuwn wesuwt;
}

static const DECWAWE_TWV_DB_SCAWE(sma1303_spk_twv, -6000, 50, 0);

static int sma1303_wegmap_wwite(stwuct sma1303_pwiv *sma1303,
				unsigned int weg, unsigned int vaw)
{
	int wet = 0;
	int cnt = sma1303->wetwy_cnt;

	whiwe (cnt--) {
		wet = wegmap_wwite(sma1303->wegmap, weg, vaw);
		if (wet < 0) {
			dev_eww(sma1303->dev,
					"Faiwed to wwite [0x%02X]\n", weg);
		} ewse
			bweak;
	}
	wetuwn wet;
}

static int sma1303_wegmap_update_bits(stwuct sma1303_pwiv *sma1303,
	unsigned int weg, unsigned int mask, unsigned int vaw, boow *change)
{
	int wet = 0;
	int cnt = sma1303->wetwy_cnt;

	whiwe (cnt--) {
		wet = wegmap_update_bits_check(sma1303->wegmap, weg,
				mask, vaw, change);
		if (wet < 0) {
			dev_eww(sma1303->dev,
					"Faiwed to update [0x%02X]\n", weg);
		} ewse
			bweak;
	}
	wetuwn wet;
}

static int sma1303_wegmap_wead(stwuct sma1303_pwiv *sma1303,
			unsigned int weg, unsigned int *vaw)
{
	int wet = 0;
	int cnt = sma1303->wetwy_cnt;

	whiwe (cnt--) {
		wet = wegmap_wead(sma1303->wegmap, weg, vaw);
		if (wet < 0) {
			dev_eww(sma1303->dev,
					"Faiwed to wead [0x%02X]\n", weg);
		} ewse
			bweak;
	}
	wetuwn wet;
}

static const chaw * const sma1303_aif_in_souwce_text[] = {
	"Mono", "Weft", "Wight"};
static const chaw * const sma1303_aif_out_souwce_text[] = {
	"Disabwe", "Aftew_FmtC", "Aftew_Mixew", "Aftew_DSP", "Aftew_Post",
		"Cwk_PWW", "Cwk_OSC"};
static const chaw * const sma1303_tdm_swot_text[] = {
	"Swot0", "Swot1", "Swot2", "Swot3",
	"Swot4", "Swot5", "Swot6", "Swot7"};

static const stwuct soc_enum sma1303_aif_in_souwce_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(sma1303_aif_in_souwce_text),
			sma1303_aif_in_souwce_text);
static const stwuct soc_enum sma1303_aif_out_souwce_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(sma1303_aif_out_souwce_text),
			sma1303_aif_out_souwce_text);
static const stwuct soc_enum sma1303_tdm_swot_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(sma1303_tdm_swot_text),
			sma1303_tdm_swot_text);

static int sma1303_fowce_mute_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = (int)sma1303->fowce_mute_status;
	dev_dbg(sma1303->dev, "%s : Fowce Mute %s\n", __func__,
			sma1303->fowce_mute_status ? "ON" : "OFF");

	wetuwn 0;
}

static int sma1303_fowce_mute_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	boow change = fawse, vaw = (boow)ucontwow->vawue.integew.vawue[0];

	if (sma1303->fowce_mute_status == vaw)
		change = fawse;
	ewse {
		change = twue;
		sma1303->fowce_mute_status = vaw;
	}
	dev_dbg(sma1303->dev, "%s : Fowce Mute %s\n", __func__,
			sma1303->fowce_mute_status ? "ON" : "OFF");

	wetuwn change;
}

static int sma1303_postscawew_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int vaw, wet;

	wet = sma1303_wegmap_wead(sma1303, SMA1303_90_POSTSCAWEW, &vaw);
	if (wet < 0)
		wetuwn -EINVAW;

	ucontwow->vawue.integew.vawue[0] = (vaw & 0x7E) >> 1;

	wetuwn 0;
}

static int sma1303_postscawew_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet, vaw = (int)ucontwow->vawue.integew.vawue[0];
	boow change;

	wet = sma1303_wegmap_update_bits(sma1303,
			SMA1303_90_POSTSCAWEW, 0x7E, (vaw << 1), &change);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn change;
}

static int sma1303_tdm_swot_wx_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int vaw, wet;

	wet = sma1303_wegmap_wead(sma1303, SMA1303_A5_TDM1, &vaw);
	if (wet < 0)
		wetuwn -EINVAW;

	ucontwow->vawue.integew.vawue[0] = (vaw & 0x38) >> 3;
	sma1303->tdm_swot_wx = ucontwow->vawue.integew.vawue[0];

	wetuwn 0;
}

static int sma1303_tdm_swot_wx_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet, vaw = (int)ucontwow->vawue.integew.vawue[0];
	boow change;

	wet = sma1303_wegmap_update_bits(sma1303,
			SMA1303_A5_TDM1, 0x38, (vaw << 3), &change);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn change;
}

static int sma1303_tdm_swot_tx_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int vaw, wet;

	wet = sma1303_wegmap_wead(sma1303, SMA1303_A6_TDM2, &vaw);
	if (wet < 0)
		wetuwn -EINVAW;

	ucontwow->vawue.integew.vawue[0] = (vaw & 0x38) >> 3;
	sma1303->tdm_swot_tx = ucontwow->vawue.integew.vawue[0];

	wetuwn 0;
}

static int sma1303_tdm_swot_tx_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet, vaw = (int)ucontwow->vawue.integew.vawue[0];
	boow change;

	wet = sma1303_wegmap_update_bits(sma1303,
			SMA1303_A6_TDM2, 0x38, (vaw << 3), &change);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn change;
}

static int sma1303_stawtup(stwuct snd_soc_component *component)
{
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	boow change = fawse, temp = fawse;

	sma1303_wegmap_update_bits(sma1303, SMA1303_8E_PWW_CTWW,
			SMA1303_PWW_PD2_MASK, SMA1303_PWW_OPEWATION2, &temp);
	if (temp == twue)
		change = twue;

	sma1303_wegmap_update_bits(sma1303, SMA1303_00_SYSTEM_CTWW,
			SMA1303_POWEW_MASK, SMA1303_POWEW_ON, &temp);
	if (temp == twue)
		change = twue;

	if (sma1303->amp_mode == SMA1303_MONO) {
		sma1303_wegmap_update_bits(sma1303,
				SMA1303_10_SYSTEM_CTWW1,
				SMA1303_SPK_MODE_MASK,
				SMA1303_SPK_MONO,
				&temp);
		if (temp == twue)
			change = twue;

	} ewse {
		sma1303_wegmap_update_bits(sma1303,
				SMA1303_10_SYSTEM_CTWW1,
				SMA1303_SPK_MODE_MASK,
				SMA1303_SPK_STEWEO,
				&temp);
		if (temp == twue)
			change = twue;
	}

	if (sma1303->check_fauwt_status) {
		if (sma1303->check_fauwt_pewiod > 0)
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					sma1303->check_fauwt_pewiod * HZ);
		ewse
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					CHECK_PEWIOD_TIME * HZ);
	}

	sma1303->amp_powew_status = twue;

	wetuwn change;
}

static int sma1303_shutdown(stwuct snd_soc_component *component)
{
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	boow change = fawse, temp = fawse;

	cancew_dewayed_wowk_sync(&sma1303->check_fauwt_wowk);

	sma1303_wegmap_update_bits(sma1303, SMA1303_10_SYSTEM_CTWW1,
			SMA1303_SPK_MODE_MASK, SMA1303_SPK_OFF, &temp);
	if (temp == twue)
		change = twue;

	sma1303_wegmap_update_bits(sma1303, SMA1303_00_SYSTEM_CTWW,
			SMA1303_POWEW_MASK, SMA1303_POWEW_OFF, &temp);
	if (temp == twue)
		change = twue;
	sma1303_wegmap_update_bits(sma1303, SMA1303_8E_PWW_CTWW,
			SMA1303_PWW_PD2_MASK, SMA1303_PWW_PD2, &temp);
	if (temp == twue)
		change = twue;

	sma1303->amp_powew_status = fawse;

	wetuwn change;
}

static int sma1303_aif_in_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	unsigned int mux = dapm_kcontwow_get_vawue(w->kcontwows[0]);
	int wet = 0;
	boow change = fawse, temp = fawse;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (mux) {
		case 0:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_11_SYSTEM_CTWW2,
					SMA1303_MONOMIX_MASK,
					SMA1303_MONOMIX_ON,
					&change);
			sma1303->amp_mode = SMA1303_MONO;
			bweak;
		case 1:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_11_SYSTEM_CTWW2,
					SMA1303_MONOMIX_MASK,
					SMA1303_MONOMIX_OFF,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_11_SYSTEM_CTWW2,
					SMA1303_WW_DATA_SW_MASK,
					SMA1303_WW_DATA_SW_NOWMAW,
					&temp);
			if (temp == twue)
				change = twue;
			sma1303->amp_mode = SMA1303_STEWEO;
			bweak;
		case 2:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_11_SYSTEM_CTWW2,
					SMA1303_MONOMIX_MASK,
					SMA1303_MONOMIX_OFF,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_11_SYSTEM_CTWW2,
					SMA1303_WW_DATA_SW_MASK,
					SMA1303_WW_DATA_SW_SWAP,
					&temp);
			if (temp == twue)
				change = twue;
			sma1303->amp_mode = SMA1303_STEWEO;
			bweak;
		defauwt:
			dev_eww(sma1303->dev, "%s : Invawid vawue (%d)\n",
								__func__, mux);
			wetuwn -EINVAW;
		}

		dev_dbg(sma1303->dev, "%s : Souwce : %s\n", __func__,
					sma1303_aif_in_souwce_text[mux]);
		bweak;
	}
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn change;
}

static int sma1303_aif_out_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	unsigned int mux = dapm_kcontwow_get_vawue(w->kcontwows[0]);
	int wet = 0;
	boow change = fawse, temp = fawse;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (mux) {
		case 0:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_NOWMAW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_09_OUTPUT_CTWW,
					SMA1303_POWT_OUT_SEW_MASK,
					SMA1303_OUT_SEW_DISABWE,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 1:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_NOWMAW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_09_OUTPUT_CTWW,
					SMA1303_POWT_OUT_SEW_MASK,
					SMA1303_FOWMAT_CONVEWTEW,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 2:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_NOWMAW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_09_OUTPUT_CTWW,
					SMA1303_POWT_OUT_SEW_MASK,
					SMA1303_MIXEW_OUTPUT,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 3:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_NOWMAW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_09_OUTPUT_CTWW,
					SMA1303_POWT_OUT_SEW_MASK,
					SMA1303_SPEAKEW_PATH,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 4:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_NOWMAW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_09_OUTPUT_CTWW,
					SMA1303_POWT_OUT_SEW_MASK,
					SMA1303_POSTSCAWEW_OUTPUT,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 5:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_CWK_OUT_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_MON_OSC_PWW_MASK,
					SMA1303_PWW_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		case 6:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_TEST_CWKO_EN_MASK,
					SMA1303_CWK_OUT_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A3_TOP_MAN2,
					SMA1303_MON_OSC_PWW_MASK,
					SMA1303_OSC_SDO,
					&temp);
			if (temp == twue)
				change = twue;
			bweak;
		defauwt:
			dev_eww(sma1303->dev, "%s : Invawid vawue (%d)\n",
								__func__, mux);
			wetuwn -EINVAW;
		}

		dev_dbg(sma1303->dev, "%s : Souwce : %s\n", __func__,
					sma1303_aif_out_souwce_text[mux]);
		bweak;
	}
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn change;
}

static int sma1303_sdo_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;
	boow change = fawse, temp = fawse;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		dev_dbg(sma1303->dev,
			"%s : SND_SOC_DAPM_PWE_PMU\n", __func__);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_09_OUTPUT_CTWW,
				SMA1303_POWT_CONFIG_MASK,
				SMA1303_OUTPUT_POWT_ENABWE,
				&temp);
		if (temp == twue)
			change = twue;
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A3_TOP_MAN2,
				SMA1303_SDO_OUTPUT_MASK,
				SMA1303_NOWMAW_OUT,
				&temp);
		if (temp == twue)
			change = twue;
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		dev_dbg(sma1303->dev,
			"%s : SND_SOC_DAPM_POST_PMD\n", __func__);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_09_OUTPUT_CTWW,
				SMA1303_POWT_CONFIG_MASK,
				SMA1303_INPUT_POWT_ONWY,
				&temp);
		if (temp == twue)
			change = twue;
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A3_TOP_MAN2,
				SMA1303_SDO_OUTPUT_MASK,
				SMA1303_HIGH_Z_OUT,
				&temp);
		if (temp == twue)
			change = twue;
		bweak;
	}
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn change;
}

static int sma1303_post_scawew_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;
	boow change = fawse;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		dev_dbg(sma1303->dev,
				"%s : SND_SOC_DAPM_PWE_PMU\n", __func__);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_90_POSTSCAWEW,
				SMA1303_BYP_POST_MASK,
				SMA1303_EN_POST_SCAWEW,
				&change);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		dev_dbg(sma1303->dev,
				"%s : SND_SOC_DAPM_POST_PMD\n", __func__);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_90_POSTSCAWEW,
				SMA1303_BYP_POST_MASK,
				SMA1303_BYP_POST_SCAWEW,
				&change);
		bweak;
	}
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn change;
}

static int sma1303_powew_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		dev_dbg(sma1303->dev,
			"%s : SND_SOC_DAPM_POST_PMU\n", __func__);
		wet = sma1303_stawtup(component);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		dev_dbg(sma1303->dev,
			"%s : SND_SOC_DAPM_PWE_PMD\n", __func__);
		wet = sma1303_shutdown(component);
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_kcontwow_new sma1303_aif_in_souwce_contwow =
	SOC_DAPM_ENUM("AIF IN Souwce", sma1303_aif_in_souwce_enum);
static const stwuct snd_kcontwow_new sma1303_aif_out_souwce_contwow =
	SOC_DAPM_ENUM("AIF OUT Souwce", sma1303_aif_out_souwce_enum);
static const stwuct snd_kcontwow_new sma1303_sdo_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);
static const stwuct snd_kcontwow_new sma1303_post_scawew_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);
static const stwuct snd_kcontwow_new sma1303_enabwe_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);

static const stwuct snd_kcontwow_new sma1303_snd_contwows[] = {
	SOC_SINGWE_TWV("Speakew Vowume", SMA1303_0A_SPK_VOW,
		0, 167, 1, sma1303_spk_twv),
	SOC_SINGWE_BOOW_EXT("Fowce Mute Switch", 0,
		sma1303_fowce_mute_get, sma1303_fowce_mute_put),
	SOC_SINGWE_EXT("Postscawew Gain", SMA1303_90_POSTSCAWEW, 1, 0x30, 0,
		sma1303_postscawew_get, sma1303_postscawew_put),
	SOC_ENUM_EXT("TDM WX Swot Position", sma1303_tdm_swot_enum,
			sma1303_tdm_swot_wx_get, sma1303_tdm_swot_wx_put),
	SOC_ENUM_EXT("TDM TX Swot Position", sma1303_tdm_swot_enum,
			sma1303_tdm_swot_tx_get, sma1303_tdm_swot_tx_put),
};

static const stwuct snd_soc_dapm_widget sma1303_dapm_widgets[] = {
	/* pwatfowm domain */
	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_INPUT("SDO"),

	/* path domain */
	SND_SOC_DAPM_MUX_E("AIF IN Souwce", SND_SOC_NOPM, 0, 0,
			&sma1303_aif_in_souwce_contwow,
			sma1303_aif_in_event,
			SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_MUX_E("AIF OUT Souwce", SND_SOC_NOPM, 0, 0,
			&sma1303_aif_out_souwce_contwow,
			sma1303_aif_out_event,
			SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SWITCH_E("SDO Enabwe", SND_SOC_NOPM, 0, 0,
			&sma1303_sdo_contwow,
			sma1303_sdo_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXEW("Entwy", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SWITCH_E("Post Scawew", SND_SOC_NOPM, 0, 1,
			&sma1303_post_scawew_contwow,
			sma1303_post_scawew_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DWV_E("AMP Powew", SND_SOC_NOPM, 0, 0, NUWW, 0,
			sma1303_powew_event,
			SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SWITCH("AMP Enabwe", SND_SOC_NOPM, 0, 1,
			&sma1303_enabwe_contwow),

	/* stweam domain */
	SND_SOC_DAPM_AIF_IN("AIF IN", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF OUT", "Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute sma1303_audio_map[] = {
	/* Pwayback */
	{"AIF IN Souwce", "Mono", "AIF IN"},
	{"AIF IN Souwce", "Weft", "AIF IN"},
	{"AIF IN Souwce", "Wight", "AIF IN"},

	{"SDO Enabwe", "Switch", "AIF IN"},
	{"AIF OUT Souwce", "Disabwe", "SDO Enabwe"},
	{"AIF OUT Souwce", "Aftew_FmtC", "SDO Enabwe"},
	{"AIF OUT Souwce", "Aftew_Mixew", "SDO Enabwe"},
	{"AIF OUT Souwce", "Aftew_DSP", "SDO Enabwe"},
	{"AIF OUT Souwce", "Aftew_Post", "SDO Enabwe"},
	{"AIF OUT Souwce", "Cwk_PWW", "SDO Enabwe"},
	{"AIF OUT Souwce", "Cwk_OSC", "SDO Enabwe"},

	{"Entwy", NUWW, "AIF OUT Souwce"},
	{"Entwy", NUWW, "AIF IN Souwce"},

	{"Post Scawew", "Switch", "Entwy"},
	{"AMP Powew", NUWW, "Entwy"},
	{"AMP Powew", NUWW, "Entwy"},

	{"AMP Enabwe", "Switch", "AMP Powew"},
	{"SPK", NUWW, "AMP Enabwe"},

	/* Captuwe */
	{"AIF OUT", NUWW, "AMP Enabwe"},
};

static int sma1303_setup_pww(stwuct snd_soc_component *component,
		unsigned int bcwk)
{
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);

	int i = 0, wet = 0;

	dev_dbg(component->dev, "%s : BCWK = %dHz\n",
		__func__, bcwk);

	if (sma1303->sys_cwk_id == SMA1303_PWW_CWKIN_MCWK) {
		dev_dbg(component->dev, "%s : MCWK is not suppowted\n",
		__func__);
	} ewse if (sma1303->sys_cwk_id == SMA1303_PWW_CWKIN_BCWK) {
		fow (i = 0; i < sma1303->num_of_pww_matches; i++) {
			if (sma1303->pww_matches[i].input_cwk == bcwk)
				bweak;
		}
		if (i == sma1303->num_of_pww_matches) {
			dev_dbg(component->dev, "%s : No matching vawue between pww tabwe and SCK\n",
					__func__);
			wetuwn -EINVAW;
		}

		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A2_TOP_MAN1,
				SMA1303_PWW_PD_MASK|SMA1303_PWW_WEF_CWK_MASK,
				SMA1303_PWW_OPEWATION|SMA1303_PWW_SCK,
				NUWW);
	}

	wet += sma1303_wegmap_wwite(sma1303,
			SMA1303_8B_PWW_POST_N,
			sma1303->pww_matches[i].post_n);

	wet += sma1303_wegmap_wwite(sma1303,
			SMA1303_8C_PWW_N,
			sma1303->pww_matches[i].n);

	wet += sma1303_wegmap_wwite(sma1303,
			SMA1303_8D_PWW_A_SETTING,
			sma1303->pww_matches[i].vco);

	wet += sma1303_wegmap_wwite(sma1303,
			SMA1303_8F_PWW_P_CP,
			sma1303->pww_matches[i].p_cp);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sma1303_dai_hw_pawams_amp(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	unsigned int bcwk = 0;
	int wet = 0;

	if (sma1303->fowmat == SND_SOC_DAIFMT_DSP_A)
		bcwk = pawams_wate(pawams) * sma1303->fwame_size;
	ewse
		bcwk = pawams_wate(pawams) * pawams_physicaw_width(pawams)
			* pawams_channews(pawams);

	dev_dbg(component->dev,
			"%s : wate = %d : bit size = %d : channew = %d\n",
			__func__, pawams_wate(pawams), pawams_width(pawams),
			pawams_channews(pawams));

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (sma1303->sys_cwk_id == SMA1303_PWW_CWKIN_BCWK) {
			if (sma1303->wast_bcwk != bcwk) {
				sma1303_setup_pww(component, bcwk);
				sma1303->wast_bcwk = bcwk;
			}
		}

		switch (pawams_wate(pawams)) {
		case 8000:
		case 12000:
		case 16000:
		case 24000:
		case 32000:
		case 44100:
		case 48000:
		case 96000:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A2_TOP_MAN1,
					SMA1303_DAC_DN_CONV_MASK,
					SMA1303_DAC_DN_CONV_DISABWE,
					NUWW);

			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_01_INPUT1_CTWW1,
					SMA1303_WEFTPOW_MASK,
					SMA1303_WOW_FIWST_CH,
					NUWW);
			bweak;

		case 192000:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A2_TOP_MAN1,
					SMA1303_DAC_DN_CONV_MASK,
					SMA1303_DAC_DN_CONV_ENABWE,
					NUWW);

			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_01_INPUT1_CTWW1,
					SMA1303_WEFTPOW_MASK,
					SMA1303_HIGH_FIWST_CH,
					NUWW);
			bweak;

		defauwt:
			dev_eww(component->dev, "%s not suppowt wate : %d\n",
				__func__, pawams_wate(pawams));

			wetuwn -EINVAW;
		}

	} ewse {

		switch (pawams_fowmat(pawams)) {

		case SNDWV_PCM_FOWMAT_S16_WE:
			dev_dbg(component->dev,
				"%s set fowmat SNDWV_PCM_FOWMAT_S16_WE\n",
				__func__);
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A4_TOP_MAN3,
					SMA1303_SCK_WATE_MASK,
					SMA1303_SCK_32FS,
					NUWW);
			bweak;

		case SNDWV_PCM_FOWMAT_S24_WE:
			dev_dbg(component->dev,
				"%s set fowmat SNDWV_PCM_FOWMAT_S24_WE\n",
				__func__);
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A4_TOP_MAN3,
					SMA1303_SCK_WATE_MASK,
					SMA1303_SCK_64FS,
					NUWW);
			bweak;
		case SNDWV_PCM_FOWMAT_S32_WE:
			dev_dbg(component->dev,
				"%s set fowmat SNDWV_PCM_FOWMAT_S32_WE\n",
				__func__);
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A4_TOP_MAN3,
					SMA1303_SCK_WATE_MASK,
					SMA1303_SCK_64FS,
					NUWW);
			bweak;
		defauwt:
			dev_eww(component->dev,
				"%s not suppowt data bit : %d\n", __func__,
						pawams_fowmat(pawams));
			wetuwn -EINVAW;
		}
	}

	switch (sma1303->fowmat) {
	case SND_SOC_DAIFMT_I2S:
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_I2S_MODE_MASK,
				SMA1303_STANDAWD_I2S,
				NUWW);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A4_TOP_MAN3,
				SMA1303_O_FOWMAT_MASK,
				SMA1303_O_FMT_I2S,
				NUWW);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_I2S_MODE_MASK,
				SMA1303_WJ,
				NUWW);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A4_TOP_MAN3,
				SMA1303_O_FOWMAT_MASK,
				SMA1303_O_FMT_WJ,
				NUWW);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 16:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_01_INPUT1_CTWW1,
					SMA1303_I2S_MODE_MASK,
					SMA1303_WJ_16BIT,
					NUWW);
			bweak;
		case 24:
		case 32:
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_01_INPUT1_CTWW1,
					SMA1303_I2S_MODE_MASK,
					SMA1303_WJ_24BIT,
					NUWW);
			bweak;
		}
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_I2S_MODE_MASK,
				SMA1303_STANDAWD_I2S,
				NUWW);
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A4_TOP_MAN3,
				SMA1303_O_FOWMAT_MASK,
				SMA1303_O_FMT_TDM,
				NUWW);
		bweak;
	}

	switch (pawams_width(pawams)) {
	case 16:
	case 24:
	case 32:
		bweak;
	defauwt:
		dev_eww(component->dev,
			"%s not suppowt data bit : %d\n", __func__,
					pawams_fowmat(pawams));
		wetuwn -EINVAW;
	}
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sma1303_dai_set_syscwk_amp(stwuct snd_soc_dai *dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case SMA1303_EXTEWNAW_CWOCK_19_2:
		bweak;
	case SMA1303_EXTEWNAW_CWOCK_24_576:
		bweak;
	case SMA1303_PWW_CWKIN_MCWK:
		bweak;
	case SMA1303_PWW_CWKIN_BCWK:
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwk id: %d\n", cwk_id);
		wetuwn -EINVAW;
	}
	sma1303->sys_cwk_id = cwk_id;
	wetuwn 0;
}

static int sma1303_dai_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn wet;

	if (mute) {
		dev_dbg(component->dev, "%s : %s\n", __func__, "MUTE");

		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_0E_MUTE_VOW_CTWW,
				SMA1303_SPK_MUTE_MASK,
				SMA1303_SPK_MUTE,
				NUWW);

		/* Need to wait time fow mute swope */
		msweep(55);
	} ewse {
		if (!sma1303->fowce_mute_status) {
			dev_dbg(component->dev, "%s : %s\n",
					__func__, "UNMUTE");
			wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_0E_MUTE_VOW_CTWW,
					SMA1303_SPK_MUTE_MASK,
					SMA1303_SPK_UNMUTE,
					NUWW);
		} ewse {
			dev_dbg(sma1303->dev,
					"%s : FOWCE MUTE!!!\n", __func__);
		}
	}

	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int sma1303_dai_set_fmt_amp(stwuct snd_soc_dai *dai,
					unsigned int fmt)
{
	stwuct snd_soc_component *component  = dai->component;
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {

	case SND_SOC_DAIFMT_CBC_CFC:
		dev_dbg(component->dev,
				"%s : %s\n", __func__, "I2S/TDM Device mode");
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_CONTWOWWEW_DEVICE_MASK,
				SMA1303_DEVICE_MODE,
				NUWW);
		bweak;

	case SND_SOC_DAIFMT_CBP_CFP:
		dev_dbg(component->dev,
			"%s : %s\n", __func__, "I2S/TDM Contwowwew mode");
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_CONTWOWWEW_DEVICE_MASK,
				SMA1303_CONTWOWWEW_MODE,
				NUWW);
		bweak;

	defauwt:
		dev_eww(component->dev,
			"Unsuppowted Contwowwew/Device : 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {

	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		sma1303->fowmat = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev,
			"Unsuppowted Audio Intewface Fowmat : 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {

	case SND_SOC_DAIFMT_IB_NF:
		dev_dbg(component->dev, "%s : %s\n",
			__func__, "Invewt BCWK + Nowmaw Fwame");
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_SCK_WISING_MASK,
				SMA1303_SCK_WISING_EDGE,
				NUWW);
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		dev_dbg(component->dev, "%s : %s\n",
			__func__, "Invewt BCWK + Invewt Fwame");
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_WEFTPOW_MASK|SMA1303_SCK_WISING_MASK,
				SMA1303_HIGH_FIWST_CH|SMA1303_SCK_WISING_EDGE,
				NUWW);
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		dev_dbg(component->dev, "%s : %s\n",
			__func__, "Nowmaw BCWK + Invewt Fwame");
		wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_01_INPUT1_CTWW1,
				SMA1303_WEFTPOW_MASK,
				SMA1303_HIGH_FIWST_CH,
				NUWW);
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		dev_dbg(component->dev, "%s : %s\n",
			__func__, "Nowmaw BCWK + Nowmaw Fwame");
		bweak;
	defauwt:
		dev_eww(component->dev,
				"Unsuppowted Bit & Fwamecwock : 0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int sma1303_dai_set_tdm_swot(stwuct snd_soc_dai *dai,
				unsigned int tx_mask, unsigned int wx_mask,
				int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	dev_dbg(component->dev, "%s : swots = %d, swot_width - %d\n",
			__func__, swots, swot_width);

	sma1303->fwame_size = swot_width * swots;

	wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A4_TOP_MAN3,
				SMA1303_O_FOWMAT_MASK,
				SMA1303_O_FMT_TDM,
				NUWW);

	switch (swot_width) {
	case 16:
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A6_TDM2,
					SMA1303_TDM_DW_MASK,
					SMA1303_TDM_DW_16,
					NUWW);
		bweak;
	case 32:
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A6_TDM2,
					SMA1303_TDM_DW_MASK,
					SMA1303_TDM_DW_32,
					NUWW);
		bweak;
	defauwt:
		dev_eww(component->dev, "%s not suppowt TDM %d swot_width\n",
					__func__, swot_width);
		bweak;
	}

	switch (swots) {
	case 4:
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A6_TDM2,
					SMA1303_TDM_N_SWOT_MASK,
					SMA1303_TDM_N_SWOT_4,
					NUWW);
		bweak;
	case 8:
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A6_TDM2,
					SMA1303_TDM_N_SWOT_MASK,
					SMA1303_TDM_N_SWOT_8,
					NUWW);
		bweak;
	defauwt:
		dev_eww(component->dev, "%s not suppowt TDM %d swots\n",
				__func__, swots);
		bweak;
	}

	if (sma1303->tdm_swot_wx < swots)
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A5_TDM1,
					SMA1303_TDM_SWOT1_WX_POS_MASK,
					(sma1303->tdm_swot_wx) << 3,
					NUWW);
	ewse
		dev_eww(component->dev, "%s Incowwect tdm-swot-wx %d set\n",
					__func__, sma1303->tdm_swot_wx);

	wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A5_TDM1,
				SMA1303_TDM_CWK_POW_MASK,
				SMA1303_TDM_CWK_POW_WISE,
				NUWW);

	wet += sma1303_wegmap_update_bits(sma1303,
				SMA1303_A5_TDM1,
				SMA1303_TDM_TX_MODE_MASK,
				SMA1303_TDM_TX_MONO,
				NUWW);

	if (sma1303->tdm_swot_tx < swots)
		wet += sma1303_wegmap_update_bits(sma1303,
					SMA1303_A6_TDM2,
					SMA1303_TDM_SWOT1_TX_POS_MASK,
					(sma1303->tdm_swot_tx) << 3,
					NUWW);
	ewse
		dev_eww(component->dev, "%s Incowwect tdm-swot-tx %d set\n",
				__func__, sma1303->tdm_swot_tx);

	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops sma1303_dai_ops_amp = {
	.set_syscwk = sma1303_dai_set_syscwk_amp,
	.set_fmt = sma1303_dai_set_fmt_amp,
	.hw_pawams = sma1303_dai_hw_pawams_amp,
	.mute_stweam = sma1303_dai_mute,
	.set_tdm_swot = sma1303_dai_set_tdm_swot,
};

#define SMA1303_WATES SNDWV_PCM_WATE_8000_192000
#define SMA1303_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE | \
		SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew sma1303_dai[] = {
	{
		.name = "sma1303-ampwifiew",
		.id = 0,
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SMA1303_WATES,
			.fowmats = SMA1303_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SMA1303_WATES,
			.fowmats = SMA1303_FOWMATS,
		},
		.ops = &sma1303_dai_ops_amp,
	},
};

static void sma1303_check_fauwt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct sma1303_pwiv *sma1303 =
		containew_of(wowk, stwuct sma1303_pwiv, check_fauwt_wowk.wowk);
	int wet = 0;
	unsigned int ovew_temp, ocp_vaw, uvwo_vaw;

	if (sma1303->tsdw_cnt)
		wet = sma1303_wegmap_wead(sma1303,
			SMA1303_0A_SPK_VOW, &sma1303->cuw_vow);
	ewse
		wet = sma1303_wegmap_wead(sma1303,
			SMA1303_0A_SPK_VOW, &sma1303->init_vow);

	if (wet != 0) {
		dev_eww(sma1303->dev,
			"faiwed to wead SMA1303_0A_SPK_VOW : %d\n", wet);
		wetuwn;
	}

	wet = sma1303_wegmap_wead(sma1303, SMA1303_FA_STATUS1, &ovew_temp);
	if (wet != 0) {
		dev_eww(sma1303->dev,
			"faiwed to wead SMA1303_FA_STATUS1 : %d\n", wet);
		wetuwn;
	}

	wet = sma1303_wegmap_wead(sma1303, SMA1303_FB_STATUS2, &ocp_vaw);
	if (wet != 0) {
		dev_eww(sma1303->dev,
			"faiwed to wead SMA1303_FB_STATUS2 : %d\n", wet);
		wetuwn;
	}

	wet = sma1303_wegmap_wead(sma1303, SMA1303_FF_DEVICE_INDEX, &uvwo_vaw);
	if (wet != 0) {
		dev_eww(sma1303->dev,
			"faiwed to wead SMA1303_FF_DEVICE_INDEX : %d\n", wet);
		wetuwn;
	}

	if (~ovew_temp & SMA1303_OT1_OK_STATUS) {
		dev_cwit(sma1303->dev,
			"%s : OT1(Ovew Tempewatuwe Wevew 1)\n", __func__);

		if ((sma1303->cuw_vow + 6) <= 0xFF)
			sma1303_wegmap_wwite(sma1303,
				SMA1303_0A_SPK_VOW, sma1303->cuw_vow + 6);

		sma1303->tsdw_cnt++;
	} ewse if (sma1303->tsdw_cnt) {
		sma1303_wegmap_wwite(sma1303,
				SMA1303_0A_SPK_VOW, sma1303->init_vow);
		sma1303->tsdw_cnt = 0;
		sma1303->cuw_vow = sma1303->init_vow;
	}

	if (~ovew_temp & SMA1303_OT2_OK_STATUS) {
		dev_cwit(sma1303->dev,
			"%s : OT2(Ovew Tempewatuwe Wevew 2)\n", __func__);
	}
	if (ocp_vaw & SMA1303_OCP_SPK_STATUS) {
		dev_cwit(sma1303->dev,
			"%s : OCP_SPK(Ovew Cuwwent Pwotect SPK)\n", __func__);
	}
	if (ocp_vaw & SMA1303_OCP_BST_STATUS) {
		dev_cwit(sma1303->dev,
			"%s : OCP_BST(Ovew Cuwwent Pwotect Boost)\n", __func__);
	}
	if ((ocp_vaw & SMA1303_CWK_MON_STATUS) && (sma1303->amp_powew_status)) {
		dev_cwit(sma1303->dev,
			"%s : CWK_FAUWT(No cwock input)\n", __func__);
	}
	if (uvwo_vaw & SMA1303_UVWO_BST_STATUS) {
		dev_cwit(sma1303->dev,
			"%s : UVWO(Undew Vowtage Wock Out)\n", __func__);
	}

	if ((ovew_temp != sma1303->wast_ovew_temp) ||
		(ocp_vaw != sma1303->wast_ocp_vaw)) {

		dev_cwit(sma1303->dev, "Pwease check AMP status");
		dev_dbg(sma1303->dev, "STATUS1=0x%02X : STATUS2=0x%02X\n",
				ovew_temp, ocp_vaw);
		sma1303->wast_ovew_temp = ovew_temp;
		sma1303->wast_ocp_vaw = ocp_vaw;
	}

	if (sma1303->check_fauwt_status) {
		if (sma1303->check_fauwt_pewiod > 0)
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					sma1303->check_fauwt_pewiod * HZ);
		ewse
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					CHECK_PEWIOD_TIME * HZ);
	}

	if (!(~ovew_temp & SMA1303_OT1_OK_STATUS)
			&& !(~ovew_temp & SMA1303_OT2_OK_STATUS)
			&& !(ocp_vaw & SMA1303_OCP_SPK_STATUS)
			&& !(ocp_vaw & SMA1303_OCP_BST_STATUS)
			&& !(ocp_vaw & SMA1303_CWK_MON_STATUS)
			&& !(uvwo_vaw & SMA1303_UVWO_BST_STATUS)) {
	}
}

static int sma1303_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);

	snd_soc_dapm_sync(dapm);

	wetuwn 0;
}

static void sma1303_wemove(stwuct snd_soc_component *component)
{
	stwuct sma1303_pwiv *sma1303 = snd_soc_component_get_dwvdata(component);

	cancew_dewayed_wowk_sync(&sma1303->check_fauwt_wowk);
}

static const stwuct snd_soc_component_dwivew sma1303_component = {
	.pwobe = sma1303_pwobe,
	.wemove = sma1303_wemove,
	.contwows = sma1303_snd_contwows,
	.num_contwows = AWWAY_SIZE(sma1303_snd_contwows),
	.dapm_widgets = sma1303_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(sma1303_dapm_widgets),
	.dapm_woutes = sma1303_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(sma1303_audio_map),
};

static const stwuct wegmap_config sma_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = SMA1303_FF_DEVICE_INDEX,
	.weadabwe_weg = sma1303_weadabwe_wegistew,
	.wwiteabwe_weg = sma1303_wwiteabwe_wegistew,
	.vowatiwe_weg = sma1303_vowatiwe_wegistew,

	.cache_type = WEGCACHE_NONE,
	.weg_defauwts = sma1303_weg_def,
	.num_weg_defauwts = AWWAY_SIZE(sma1303_weg_def),
};

static ssize_t check_fauwt_pewiod_show(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sma1303_pwiv *sma1303 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wd\n", sma1303->check_fauwt_pewiod);
}

static ssize_t check_fauwt_pewiod_stowe(stwuct device *dev,
	stwuct device_attwibute *devattw, const chaw *buf, size_t count)
{
	stwuct sma1303_pwiv *sma1303 = dev_get_dwvdata(dev);
	int wet;

	wet = kstwtow(buf, 10, &sma1303->check_fauwt_pewiod);

	if (wet)
		wetuwn -EINVAW;

	wetuwn (ssize_t)count;
}

static DEVICE_ATTW_WW(check_fauwt_pewiod);

static ssize_t check_fauwt_status_show(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sma1303_pwiv *sma1303 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wd\n", sma1303->check_fauwt_status);
}

static ssize_t check_fauwt_status_stowe(stwuct device *dev,
	stwuct device_attwibute *devattw, const chaw *buf, size_t count)
{
	stwuct sma1303_pwiv *sma1303 = dev_get_dwvdata(dev);
	int wet;

	wet = kstwtow(buf, 10, &sma1303->check_fauwt_status);

	if (wet)
		wetuwn -EINVAW;

	if (sma1303->check_fauwt_status) {
		if (sma1303->check_fauwt_pewiod > 0)
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					sma1303->check_fauwt_pewiod * HZ);
		ewse
			queue_dewayed_wowk(system_fweezabwe_wq,
				&sma1303->check_fauwt_wowk,
					CHECK_PEWIOD_TIME * HZ);
	}

	wetuwn (ssize_t)count;
}

static DEVICE_ATTW_WW(check_fauwt_status);

static stwuct attwibute *sma1303_attw[] = {
	&dev_attw_check_fauwt_pewiod.attw,
	&dev_attw_check_fauwt_status.attw,
	NUWW,
};

static stwuct attwibute_gwoup sma1303_attw_gwoup = {
	.attws = sma1303_attw,
};

static int sma1303_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sma1303_pwiv *sma1303;
	int wet, i = 0;
	unsigned int device_info, status, otp_stat;

	sma1303 = devm_kzawwoc(&cwient->dev,
				sizeof(stwuct sma1303_pwiv), GFP_KEWNEW);
	if (!sma1303)
		wetuwn -ENOMEM;
	sma1303->dev = &cwient->dev;

	sma1303->wegmap = devm_wegmap_init_i2c(cwient, &sma_i2c_wegmap);
	if (IS_EWW(sma1303->wegmap)) {
		wet = PTW_EWW(sma1303->wegmap);
		dev_eww(&cwient->dev,
			"Faiwed to awwocate wegistew map: %d\n", wet);

		wetuwn wet;
	}

	wet = sma1303_wegmap_wead(sma1303,
			SMA1303_FF_DEVICE_INDEX, &device_info);

	if ((wet != 0) || ((device_info & 0xF8) != SMA1303_DEVICE_ID)) {
		dev_eww(&cwient->dev, "device initiawization ewwow (%d 0x%02X)",
				wet, device_info);
	}
	dev_dbg(&cwient->dev, "chip vewsion 0x%02X\n", device_info);

	wet += sma1303_wegmap_update_bits(sma1303,
			SMA1303_00_SYSTEM_CTWW,
			SMA1303_WESETBYI2C_MASK, SMA1303_WESETBYI2C_WESET,
			NUWW);

	wet += sma1303_wegmap_wead(sma1303, SMA1303_FF_DEVICE_INDEX, &status);
	sma1303->wev_num = status & SMA1303_WEV_NUM_STATUS;
	if (sma1303->wev_num == SMA1303_WEV_NUM_TV0)
		dev_dbg(&cwient->dev, "SMA1303 Twimming Vewsion 0\n");
	ewse if (sma1303->wev_num == SMA1303_WEV_NUM_TV1)
		dev_dbg(&cwient->dev, "SMA1303 Twimming Vewsion 1\n");

	wet += sma1303_wegmap_wead(sma1303, SMA1303_FB_STATUS2, &otp_stat);
	if (wet < 0)
		dev_eww(&cwient->dev,
			"faiwed to wead, wegistew: %02X, wet: %d\n",
				SMA1303_FF_DEVICE_INDEX, wet);

	if (((sma1303->wev_num == SMA1303_WEV_NUM_TV0) &&
		((otp_stat & 0x0E) == SMA1303_OTP_STAT_OK_0)) ||
		((sma1303->wev_num != SMA1303_WEV_NUM_TV0) &&
		((otp_stat & 0x0C) == SMA1303_OTP_STAT_OK_1)))
		dev_dbg(&cwient->dev, "SMA1303 OTP Status Successfuw\n");
	ewse
		dev_dbg(&cwient->dev, "SMA1303 OTP Status Faiw\n");

	fow (i = 0; i < (unsigned int)AWWAY_SIZE(sma1303_weg_def); i++)
		wet += sma1303_wegmap_wwite(sma1303,
				sma1303_weg_def[i].weg,
				sma1303_weg_def[i].def);

	sma1303->amp_mode = SMA1303_MONO;
	sma1303->amp_powew_status = fawse;
	sma1303->check_fauwt_pewiod = CHECK_PEWIOD_TIME;
	sma1303->check_fauwt_status = twue;
	sma1303->fowce_mute_status = fawse;
	sma1303->init_vow = 0x31;
	sma1303->cuw_vow = sma1303->init_vow;
	sma1303->wast_bcwk = 0;
	sma1303->wast_ocp_vaw = 0x08;
	sma1303->wast_ovew_temp = 0xC0;
	sma1303->tsdw_cnt = 0;
	sma1303->wetwy_cnt = SMA1303_I2C_WETWY_COUNT;
	sma1303->tdm_swot_wx = 0;
	sma1303->tdm_swot_tx = 0;
	sma1303->sys_cwk_id = SMA1303_PWW_CWKIN_BCWK;

	sma1303->dev = &cwient->dev;
	sma1303->kobj = &cwient->dev.kobj;

	INIT_DEWAYED_WOWK(&sma1303->check_fauwt_wowk,
		sma1303_check_fauwt_wowkew);

	i2c_set_cwientdata(cwient, sma1303);

	sma1303->pww_matches = sma1303_pww_matches;
	sma1303->num_of_pww_matches =
		AWWAY_SIZE(sma1303_pww_matches);

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
			&sma1303_component, sma1303_dai, 1);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wegistew component");

		wetuwn wet;
	}

	sma1303->attw_gwp = &sma1303_attw_gwoup;
	wet = sysfs_cweate_gwoup(sma1303->kobj, sma1303->attw_gwp);
	if (wet) {
		dev_eww(&cwient->dev,
			"faiwed to cweate attwibute gwoup [%d]\n", wet);
		sma1303->attw_gwp = NUWW;
	}

	wetuwn wet;
}

static void sma1303_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct sma1303_pwiv *sma1303 =
		(stwuct sma1303_pwiv *) i2c_get_cwientdata(cwient);

	cancew_dewayed_wowk_sync(&sma1303->check_fauwt_wowk);
}

static const stwuct i2c_device_id sma1303_i2c_id[] = {
	{"sma1303", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, sma1303_i2c_id);

static const stwuct of_device_id sma1303_of_match[] = {
	{ .compatibwe = "iwondevice,sma1303", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sma1303_of_match);

static stwuct i2c_dwivew sma1303_i2c_dwivew = {
	.dwivew = {
		.name = "sma1303",
		.of_match_tabwe = sma1303_of_match,
	},
	.pwobe = sma1303_i2c_pwobe,
	.wemove = sma1303_i2c_wemove,
	.id_tabwe = sma1303_i2c_id,
};

moduwe_i2c_dwivew(sma1303_i2c_dwivew);

MODUWE_DESCWIPTION("AWSA SoC SMA1303 dwivew");
MODUWE_AUTHOW("Gyuhwa Pawk, <gyuhwa.pawk@iwondevice.com>");
MODUWE_AUTHOW("Kiseok Jo, <kiseok.jo@iwondevice.com>");
MODUWE_WICENSE("GPW v2");
