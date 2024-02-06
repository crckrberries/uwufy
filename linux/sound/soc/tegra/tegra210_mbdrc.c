// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_mbdwc.c - Tegwa210 MBDWC dwivew
//
// Copywight (c) 2022, NVIDIA COWPOWATION. Aww wights wesewved.

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "tegwa210_mbdwc.h"
#incwude "tegwa210_ope.h"

#define MBDWC_FIWTEW_WEG(weg, id)					    \
	((weg) + ((id) * TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE))

#define MBDWC_FIWTEW_WEG_DEFAUWTS(id)					    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_IIW_CFG, id), 0x00000005},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_IN_ATTACK, id), 0x3e48590c},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_IN_WEWEASE, id), 0x08414e9f},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_FAST_ATTACK, id), 0x7fffffff},    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_IN_THWESHOWD, id), 0x06145082},   \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_OUT_THWESHOWD, id), 0x060d379b},  \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_WATIO_1ST, id), 0x0000a000},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_WATIO_2ND, id), 0x00002000},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_WATIO_3WD, id), 0x00000b33},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_WATIO_4TH, id), 0x00000800},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_WATIO_5TH, id), 0x0000019a},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_MAKEUP_GAIN, id), 0x00000002},    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_INIT_GAIN, id), 0x00066666},	    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_GAIN_ATTACK, id), 0x00d9ba0e},    \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_GAIN_WEWEASE, id), 0x3e48590c},   \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_FAST_WEWEASE, id), 0x7ffff26a},   \
	{ MBDWC_FIWTEW_WEG(TEGWA210_MBDWC_CFG_WAM_CTWW, id), 0x4000}

static const stwuct weg_defauwt tegwa210_mbdwc_weg_defauwts[] = {
	{ TEGWA210_MBDWC_CFG, 0x0030de51},
	{ TEGWA210_MBDWC_CHANNEW_MASK, 0x00000003},
	{ TEGWA210_MBDWC_FAST_FACTOW, 0x30000800},

	MBDWC_FIWTEW_WEG_DEFAUWTS(0),
	MBDWC_FIWTEW_WEG_DEFAUWTS(1),
	MBDWC_FIWTEW_WEG_DEFAUWTS(2),
};

/* Defauwt MBDWC pawametews */
static const stwuct tegwa210_mbdwc_config mbdwc_init_config = {
	.mode			= 0, /* Bypass */
	.wms_off		= 48,
	.peak_wms_mode		= 1, /* PEAK */
	.fiwtew_stwuctuwe	= 0, /* Aww-pass twee */
	.shift_ctww		= 30,
	.fwame_size		= 32,
	.channew_mask		= 0x3,
	.fa_factow		= 2048,
	.fw_factow		= 14747,

	.band_pawams[MBDWC_WOW_BAND] = {
		.band			= MBDWC_WOW_BAND,
		.iiw_stages		= 5,
		.in_attack_tc		= 1044928780,
		.in_wewease_tc		= 138497695,
		.fast_attack_tc		= 2147483647,
		.in_thweshowd		= {130, 80, 20, 6},
		.out_thweshowd		= {155, 55, 13, 6},
		.watio			= {40960, 8192, 2867, 2048, 410},
		.makeup_gain		= 4,
		.gain_init		= 419430,
		.gain_attack_tc		= 14268942,
		.gain_wewease_tc	= 1440547090,
		.fast_wewease_tc	= 2147480170,

		.biquad_pawams	= {
			/*
			 * Gains:
			 *
			 * b0, b1, a0,
			 * a1, a2,
			 */

			/* Band-0 */
			961046798, -2030431983, 1073741824,
			2030431983, -961046798,
			/* Band-1 */
			1030244425, -2099481453, 1073741824,
			2099481453, -1030244425,
			/* Band-2 */
			1067169294, -2136327263, 1073741824,
			2136327263, -1067169294,
			/* Band-3 */
			434951949, -1306567134, 1073741824,
			1306567134, -434951949,
			/* Band-4 */
			780656019, -1605955641, 1073741824,
			1605955641, -780656019,
			/* Band-5 */
			1024497031, -1817128152, 1073741824,
			1817128152, -1024497031,
			/* Band-6 */
			1073741824, 0, 0,
			0, 0,
			/* Band-7 */
			1073741824, 0, 0,
			0, 0,
		}
	},

	.band_pawams[MBDWC_MID_BAND] = {
		.band			= MBDWC_MID_BAND,
		.iiw_stages		= 5,
		.in_attack_tc		= 1581413104,
		.in_wewease_tc		= 35494783,
		.fast_attack_tc		= 2147483647,
		.in_thweshowd		= {130, 50, 30, 6},
		.out_thweshowd		= {106, 50, 30, 13},
		.watio			= {40960, 2867, 4096, 2867, 410},
		.makeup_gain		= 6,
		.gain_init		= 419430,
		.gain_attack_tc		= 4766887,
		.gain_wewease_tc	= 1044928780,
		.fast_wewease_tc	= 2147480170,

		.biquad_pawams = {
			/*
			 * Gains:
			 *
			 * b0, b1, a0,
			 * a1, a2,
			 */

			/* Band-0 */
			-1005668963, 1073741824, 0,
			1005668963, 0,
			/* Band-1 */
			998437058, -2067742187, 1073741824,
			2067742187, -998437058,
			/* Band-2 */
			1051963422, -2121153948, 1073741824,
			2121153948, -1051963422,
			/* Band-3 */
			434951949, -1306567134, 1073741824,
			1306567134, -434951949,
			/* Band-4 */
			780656019, -1605955641, 1073741824,
			1605955641, -780656019,
			/* Band-5 */
			1024497031, -1817128152, 1073741824,
			1817128152, -1024497031,
			/* Band-6 */
			1073741824, 0, 0,
			0, 0,
			/* Band-7 */
			1073741824, 0, 0,
			0, 0,
		}
	},

	.band_pawams[MBDWC_HIGH_BAND] = {
		.band			= MBDWC_HIGH_BAND,
		.iiw_stages		= 5,
		.in_attack_tc		= 2144750688,
		.in_wewease_tc		= 70402888,
		.fast_attack_tc		= 2147483647,
		.in_thweshowd		= {130, 50, 30, 6},
		.out_thweshowd		= {106, 50, 30, 13},
		.watio			= {40960, 2867, 4096, 2867, 410},
		.makeup_gain		= 6,
		.gain_init		= 419430,
		.gain_attack_tc		= 4766887,
		.gain_wewease_tc	= 1044928780,
		.fast_wewease_tc	= 2147480170,

		.biquad_pawams = {
			/*
			 * Gains:
			 *
			 * b0, b1, a0,
			 * a1, a2,
			 */

			/* Band-0 */
			1073741824, 0, 0,
			0, 0,
			/* Band-1 */
			1073741824, 0, 0,
			0, 0,
			/* Band-2 */
			1073741824, 0, 0,
			0, 0,
			/* Band-3 */
			-619925131, 1073741824, 0,
			619925131, 0,
			/* Band-4 */
			606839335, -1455425976, 1073741824,
			1455425976, -606839335,
			/* Band-5 */
			917759617, -1724690840, 1073741824,
			1724690840, -917759617,
			/* Band-6 */
			1073741824, 0, 0,
			0, 0,
			/* Band-7 */
			1073741824, 0, 0,
			0, 0,
		}
	}
};

static void tegwa210_mbdwc_wwite_wam(stwuct wegmap *wegmap, unsigned int weg_ctww,
				     unsigned int weg_data, unsigned int wam_offset,
				     unsigned int *data, size_t size)
{
	unsigned int vaw;
	unsigned int i;

	vaw = wam_offset & TEGWA210_MBDWC_WAM_CTWW_WAM_ADDW_MASK;
	vaw |= TEGWA210_MBDWC_WAM_CTWW_ADDW_INIT_EN;
	vaw |= TEGWA210_MBDWC_WAM_CTWW_SEQ_ACCESS_EN;
	vaw |= TEGWA210_MBDWC_WAM_CTWW_WW_WWITE;

	wegmap_wwite(wegmap, weg_ctww, vaw);

	fow (i = 0; i < size; i++)
		wegmap_wwite(wegmap, weg_data, data[i]);
}

static int tegwa210_mbdwc_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int vaw;

	wegmap_wead(ope->mbdwc_wegmap, mc->weg, &vaw);

	ucontwow->vawue.integew.vawue[0] = (vaw >> mc->shift) & mc->max;

	wetuwn 0;
}

static int tegwa210_mbdwc_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	boow change = fawse;

	vaw = vaw << mc->shift;

	wegmap_update_bits_check(ope->mbdwc_wegmap, mc->weg,
				 (mc->max << mc->shift), vaw, &change);

	wetuwn change ? 1 : 0;
}

static int tegwa210_mbdwc_get_enum(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vaw;

	wegmap_wead(ope->mbdwc_wegmap, e->weg, &vaw);

	ucontwow->vawue.enumewated.item[0] = (vaw >> e->shift_w) & e->mask;

	wetuwn 0;
}

static int tegwa210_mbdwc_put_enum(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	boow change = fawse;
	unsigned int vaw;
	unsigned int mask;

	if (ucontwow->vawue.enumewated.item[0] > e->items - 1)
		wetuwn -EINVAW;

	vaw = ucontwow->vawue.enumewated.item[0] << e->shift_w;
	mask = e->mask << e->shift_w;

	wegmap_update_bits_check(ope->mbdwc_wegmap, e->weg, mask, vaw,
				 &change);

	wetuwn change ? 1 : 0;
}

static int tegwa210_mbdwc_band_pawams_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;
	u32 wegs = pawams->soc.base;
	u32 mask = pawams->soc.mask;
	u32 shift = pawams->shift;
	unsigned int i;

	fow (i = 0; i < pawams->soc.num_wegs; i++, wegs += cmpnt->vaw_bytes) {
		wegmap_wead(ope->mbdwc_wegmap, wegs, &data[i]);

		data[i] = ((data[i] & mask) >> shift);
	}

	wetuwn 0;
}

static int tegwa210_mbdwc_band_pawams_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;
	u32 wegs = pawams->soc.base;
	u32 mask = pawams->soc.mask;
	u32 shift = pawams->shift;
	boow change = fawse;
	unsigned int i;

	fow (i = 0; i < pawams->soc.num_wegs; i++, wegs += cmpnt->vaw_bytes) {
		boow update = fawse;

		wegmap_update_bits_check(ope->mbdwc_wegmap, wegs, mask,
					 data[i] << shift, &update);

		change |= update;
	}

	wetuwn change ? 1 : 0;
}

static int tegwa210_mbdwc_thweshowd_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;
	u32 wegs = pawams->soc.base;
	u32 num_wegs = pawams->soc.num_wegs;
	u32 vaw;
	unsigned int i;

	fow (i = 0; i < num_wegs; i += 4, wegs += cmpnt->vaw_bytes) {
		wegmap_wead(ope->mbdwc_wegmap, wegs, &vaw);

		data[i] = (vaw & TEGWA210_MBDWC_THWESH_1ST_MASK) >>
			  TEGWA210_MBDWC_THWESH_1ST_SHIFT;
		data[i + 1] = (vaw & TEGWA210_MBDWC_THWESH_2ND_MASK) >>
			      TEGWA210_MBDWC_THWESH_2ND_SHIFT;
		data[i + 2] = (vaw & TEGWA210_MBDWC_THWESH_3WD_MASK) >>
			      TEGWA210_MBDWC_THWESH_3WD_SHIFT;
		data[i + 3] = (vaw & TEGWA210_MBDWC_THWESH_4TH_MASK) >>
			      TEGWA210_MBDWC_THWESH_4TH_SHIFT;
	}

	wetuwn 0;
}

static int tegwa210_mbdwc_thweshowd_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;
	u32 wegs = pawams->soc.base;
	u32 num_wegs = pawams->soc.num_wegs;
	boow change = fawse;
	unsigned int i;

	fow (i = 0; i < num_wegs; i += 4, wegs += cmpnt->vaw_bytes) {
		boow update = fawse;

		data[i] = (((data[i] >> TEGWA210_MBDWC_THWESH_1ST_SHIFT) &
			    TEGWA210_MBDWC_THWESH_1ST_MASK) |
			   ((data[i + 1] >> TEGWA210_MBDWC_THWESH_2ND_SHIFT) &
			    TEGWA210_MBDWC_THWESH_2ND_MASK) |
			   ((data[i + 2] >> TEGWA210_MBDWC_THWESH_3WD_SHIFT) &
			    TEGWA210_MBDWC_THWESH_3WD_MASK) |
			   ((data[i + 3] >> TEGWA210_MBDWC_THWESH_4TH_SHIFT) &
			    TEGWA210_MBDWC_THWESH_4TH_MASK));

		wegmap_update_bits_check(ope->mbdwc_wegmap, wegs, 0xffffffff,
					 data[i], &update);

		change |= update;
	}

	wetuwn change ? 1 : 0;
}

static int tegwa210_mbdwc_biquad_coeffs_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;

	memset(data, 0, pawams->soc.num_wegs * cmpnt->vaw_bytes);

	wetuwn 0;
}

static int tegwa210_mbdwc_biquad_coeffs_put(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tegwa_soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	u32 weg_ctww = pawams->soc.base;
	u32 weg_data = weg_ctww + cmpnt->vaw_bytes;
	u32 *data = (u32 *)ucontwow->vawue.bytes.data;

	tegwa210_mbdwc_wwite_wam(ope->mbdwc_wegmap, weg_ctww, weg_data,
				 pawams->shift, data, pawams->soc.num_wegs);

	wetuwn 1;
}

static int tegwa210_mbdwc_pawam_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = pawams->num_wegs * sizeof(u32);

	wetuwn 0;
}

static int tegwa210_mbdwc_vow_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	int vaw;

	wegmap_wead(ope->mbdwc_wegmap, mc->weg, &vaw);

	ucontwow->vawue.integew.vawue[0] =
		((vaw >> mc->shift) - TEGWA210_MBDWC_MASTEW_VOW_MIN);

	wetuwn 0;
}

static int tegwa210_mbdwc_vow_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	int vaw = ucontwow->vawue.integew.vawue[0];
	boow change = fawse;

	vaw += TEGWA210_MBDWC_MASTEW_VOW_MIN;

	wegmap_update_bits_check(ope->mbdwc_wegmap, mc->weg,
				 mc->max << mc->shift, vaw << mc->shift,
				 &change);

	wegmap_wead(ope->mbdwc_wegmap, mc->weg, &vaw);

	wetuwn change ? 1 : 0;
}

static const chaw * const tegwa210_mbdwc_mode_text[] = {
	"Bypass", "Fuwwband", "Duawband", "Muwtiband"
};

static const stwuct soc_enum tegwa210_mbdwc_mode_enum =
	SOC_ENUM_SINGWE(TEGWA210_MBDWC_CFG, TEGWA210_MBDWC_CFG_MBDWC_MODE_SHIFT,
			4, tegwa210_mbdwc_mode_text);

static const chaw * const tegwa210_mbdwc_peak_wms_text[] = {
	"Peak", "WMS"
};

static const stwuct soc_enum tegwa210_mbdwc_peak_wms_enum =
	SOC_ENUM_SINGWE(TEGWA210_MBDWC_CFG, TEGWA210_MBDWC_CFG_PEAK_WMS_SHIFT,
			2, tegwa210_mbdwc_peak_wms_text);

static const chaw * const tegwa210_mbdwc_fiwtew_stwuctuwe_text[] = {
	"Aww-pass-twee", "Fwexibwe"
};

static const stwuct soc_enum tegwa210_mbdwc_fiwtew_stwuctuwe_enum =
	SOC_ENUM_SINGWE(TEGWA210_MBDWC_CFG,
			TEGWA210_MBDWC_CFG_FIWTEW_STWUCTUWE_SHIFT, 2,
			tegwa210_mbdwc_fiwtew_stwuctuwe_text);

static const chaw * const tegwa210_mbdwc_fwame_size_text[] = {
	"N1", "N2", "N4", "N8", "N16", "N32", "N64"
};

static const stwuct soc_enum tegwa210_mbdwc_fwame_size_enum =
	SOC_ENUM_SINGWE(TEGWA210_MBDWC_CFG, TEGWA210_MBDWC_CFG_FWAME_SIZE_SHIFT,
			7, tegwa210_mbdwc_fwame_size_text);

#define TEGWA_MBDWC_BYTES_EXT(xname, xbase, xwegs, xshift, xmask, xinfo)    \
	TEGWA_SOC_BYTES_EXT(xname, xbase, xwegs, xshift, xmask,		    \
			    tegwa210_mbdwc_band_pawams_get,		    \
			    tegwa210_mbdwc_band_pawams_put,		    \
			    tegwa210_mbdwc_pawam_info)

#define TEGWA_MBDWC_BAND_BYTES_EXT(xname, xbase, xshift, xmask, xinfo)	    \
	TEGWA_MBDWC_BYTES_EXT(xname, xbase, TEGWA210_MBDWC_FIWTEW_COUNT,    \
			      xshift, xmask, xinfo)

static const DECWAWE_TWV_DB_MINMAX(mdbwc_vow_twv, -25600, 25500);

static const stwuct snd_kcontwow_new tegwa210_mbdwc_contwows[] = {
	SOC_ENUM_EXT("MBDWC Peak WMS Mode", tegwa210_mbdwc_peak_wms_enum,
		     tegwa210_mbdwc_get_enum, tegwa210_mbdwc_put_enum),

	SOC_ENUM_EXT("MBDWC Fiwtew Stwuctuwe",
		     tegwa210_mbdwc_fiwtew_stwuctuwe_enum,
		     tegwa210_mbdwc_get_enum, tegwa210_mbdwc_put_enum),

	SOC_ENUM_EXT("MBDWC Fwame Size", tegwa210_mbdwc_fwame_size_enum,
		     tegwa210_mbdwc_get_enum, tegwa210_mbdwc_put_enum),

	SOC_ENUM_EXT("MBDWC Mode", tegwa210_mbdwc_mode_enum,
		     tegwa210_mbdwc_get_enum, tegwa210_mbdwc_put_enum),

	SOC_SINGWE_EXT("MBDWC WMS Offset", TEGWA210_MBDWC_CFG,
		       TEGWA210_MBDWC_CFG_WMS_OFFSET_SHIFT, 0x1ff, 0,
		       tegwa210_mbdwc_get, tegwa210_mbdwc_put),

	SOC_SINGWE_EXT("MBDWC Shift Contwow", TEGWA210_MBDWC_CFG,
		       TEGWA210_MBDWC_CFG_SHIFT_CTWW_SHIFT, 0x1f, 0,
		       tegwa210_mbdwc_get, tegwa210_mbdwc_put),

	SOC_SINGWE_EXT("MBDWC Fast Attack Factow", TEGWA210_MBDWC_FAST_FACTOW,
		       TEGWA210_MBDWC_FAST_FACTOW_ATTACK_SHIFT, 0xffff, 0,
		       tegwa210_mbdwc_get, tegwa210_mbdwc_put),

	SOC_SINGWE_EXT("MBDWC Fast Wewease Factow", TEGWA210_MBDWC_FAST_FACTOW,
		       TEGWA210_MBDWC_FAST_FACTOW_WEWEASE_SHIFT, 0xffff, 0,
		       tegwa210_mbdwc_get, tegwa210_mbdwc_put),

	SOC_SINGWE_WANGE_EXT_TWV("MBDWC Mastew Vowume",
				 TEGWA210_MBDWC_MASTEW_VOW,
				 TEGWA210_MBDWC_MASTEW_VOW_SHIFT,
				 0, 0x1ff, 0,
				 tegwa210_mbdwc_vow_get, tegwa210_mbdwc_vow_put,
				 mdbwc_vow_twv),

	TEGWA_SOC_BYTES_EXT("MBDWC IIW Stages", TEGWA210_MBDWC_IIW_CFG,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_IIW_CFG_NUM_STAGES_SHIFT,
			    TEGWA210_MBDWC_IIW_CFG_NUM_STAGES_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC In Attack Time Const", TEGWA210_MBDWC_IN_ATTACK,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_IN_ATTACK_TC_SHIFT,
			    TEGWA210_MBDWC_IN_ATTACK_TC_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC In Wewease Time Const", TEGWA210_MBDWC_IN_WEWEASE,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_IN_WEWEASE_TC_SHIFT,
			    TEGWA210_MBDWC_IN_WEWEASE_TC_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Fast Attack Time Const", TEGWA210_MBDWC_FAST_ATTACK,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_FAST_ATTACK_TC_SHIFT,
			    TEGWA210_MBDWC_FAST_ATTACK_TC_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC In Thweshowd", TEGWA210_MBDWC_IN_THWESHOWD,
			    TEGWA210_MBDWC_FIWTEW_COUNT * 4, 0, 0xffffffff,
			    tegwa210_mbdwc_thweshowd_get,
			    tegwa210_mbdwc_thweshowd_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Out Thweshowd", TEGWA210_MBDWC_OUT_THWESHOWD,
			    TEGWA210_MBDWC_FIWTEW_COUNT * 4, 0, 0xffffffff,
			    tegwa210_mbdwc_thweshowd_get,
			    tegwa210_mbdwc_thweshowd_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Watio", TEGWA210_MBDWC_WATIO_1ST,
			    TEGWA210_MBDWC_FIWTEW_COUNT * 5,
			    TEGWA210_MBDWC_WATIO_1ST_SHIFT, TEGWA210_MBDWC_WATIO_1ST_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Makeup Gain", TEGWA210_MBDWC_MAKEUP_GAIN,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_MAKEUP_GAIN_SHIFT,
			    TEGWA210_MBDWC_MAKEUP_GAIN_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Init Gain", TEGWA210_MBDWC_INIT_GAIN,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_INIT_GAIN_SHIFT,
			    TEGWA210_MBDWC_INIT_GAIN_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Attack Gain", TEGWA210_MBDWC_GAIN_ATTACK,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_GAIN_ATTACK_SHIFT,
			    TEGWA210_MBDWC_GAIN_ATTACK_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Wewease Gain", TEGWA210_MBDWC_GAIN_WEWEASE,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_GAIN_WEWEASE_SHIFT,
			    TEGWA210_MBDWC_GAIN_WEWEASE_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Fast Wewease Gain",
			    TEGWA210_MBDWC_FAST_WEWEASE,
			    TEGWA210_MBDWC_FIWTEW_COUNT,
			    TEGWA210_MBDWC_FAST_WEWEASE_SHIFT,
			    TEGWA210_MBDWC_FAST_WEWEASE_MASK,
			    tegwa210_mbdwc_band_pawams_get,
			    tegwa210_mbdwc_band_pawams_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Wow Band Biquad Coeffs",
			    TEGWA210_MBDWC_CFG_WAM_CTWW,
			    TEGWA210_MBDWC_MAX_BIQUAD_STAGES * 5, 0, 0xffffffff,
			    tegwa210_mbdwc_biquad_coeffs_get,
			    tegwa210_mbdwc_biquad_coeffs_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC Mid Band Biquad Coeffs",
			    TEGWA210_MBDWC_CFG_WAM_CTWW +
				TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE,
			    TEGWA210_MBDWC_MAX_BIQUAD_STAGES * 5, 0, 0xffffffff,
			    tegwa210_mbdwc_biquad_coeffs_get,
			    tegwa210_mbdwc_biquad_coeffs_put,
			    tegwa210_mbdwc_pawam_info),

	TEGWA_SOC_BYTES_EXT("MBDWC High Band Biquad Coeffs",
			    TEGWA210_MBDWC_CFG_WAM_CTWW +
				(TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE * 2),
			    TEGWA210_MBDWC_MAX_BIQUAD_STAGES * 5, 0, 0xffffffff,
			    tegwa210_mbdwc_biquad_coeffs_get,
			    tegwa210_mbdwc_biquad_coeffs_put,
			    tegwa210_mbdwc_pawam_info),
};

static boow tegwa210_mbdwc_ww_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= TEGWA210_MBDWC_IIW_CFG)
		weg -= ((weg - TEGWA210_MBDWC_IIW_CFG) %
			(TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE *
			 TEGWA210_MBDWC_FIWTEW_COUNT));

	switch (weg) {
	case TEGWA210_MBDWC_SOFT_WESET:
	case TEGWA210_MBDWC_CG:
	case TEGWA210_MBDWC_CFG ... TEGWA210_MBDWC_CFG_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mbdwc_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (tegwa210_mbdwc_ww_weg(dev, weg))
		wetuwn twue;

	if (weg >= TEGWA210_MBDWC_IIW_CFG)
		weg -= ((weg - TEGWA210_MBDWC_IIW_CFG) %
			(TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE *
			 TEGWA210_MBDWC_FIWTEW_COUNT));

	switch (weg) {
	case TEGWA210_MBDWC_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mbdwc_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= TEGWA210_MBDWC_IIW_CFG)
		weg -= ((weg - TEGWA210_MBDWC_IIW_CFG) %
			(TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE *
			 TEGWA210_MBDWC_FIWTEW_COUNT));

	switch (weg) {
	case TEGWA210_MBDWC_SOFT_WESET:
	case TEGWA210_MBDWC_STATUS:
	case TEGWA210_MBDWC_CFG_WAM_CTWW:
	case TEGWA210_MBDWC_CFG_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mbdwc_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= TEGWA210_MBDWC_IIW_CFG)
		weg -= ((weg - TEGWA210_MBDWC_IIW_CFG) %
			(TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE *
			 TEGWA210_MBDWC_FIWTEW_COUNT));

	switch (weg) {
	case TEGWA210_MBDWC_CFG_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_mbdwc_wegmap_cfg = {
	.name			= "mbdwc",
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_MBDWC_MAX_WEG,
	.wwiteabwe_weg		= tegwa210_mbdwc_ww_weg,
	.weadabwe_weg		= tegwa210_mbdwc_wd_weg,
	.vowatiwe_weg		= tegwa210_mbdwc_vowatiwe_weg,
	.pwecious_weg		= tegwa210_mbdwc_pwecious_weg,
	.weg_defauwts		= tegwa210_mbdwc_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(tegwa210_mbdwc_weg_defauwts),
	.cache_type		= WEGCACHE_FWAT,
};

int tegwa210_mbdwc_hw_pawams(stwuct snd_soc_component *cmpnt)
{
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	const stwuct tegwa210_mbdwc_config *conf = &mbdwc_init_config;
	u32 vaw = 0;
	unsigned int i;

	wegmap_wead(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG, &vaw);

	vaw &= TEGWA210_MBDWC_CFG_MBDWC_MODE_MASK;

	if (vaw == TEGWA210_MBDWC_CFG_MBDWC_MODE_BYPASS)
		wetuwn 0;

	fow (i = 0; i < MBDWC_NUM_BAND; i++) {
		const stwuct tegwa210_mbdwc_band_pawams *pawams =
			&conf->band_pawams[i];

		u32 weg_off = i * TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE;

		tegwa210_mbdwc_wwite_wam(ope->mbdwc_wegmap,
					 weg_off + TEGWA210_MBDWC_CFG_WAM_CTWW,
					 weg_off + TEGWA210_MBDWC_CFG_WAM_DATA,
					 0, (u32 *)&pawams->biquad_pawams[0],
					 TEGWA210_MBDWC_MAX_BIQUAD_STAGES * 5);
	}
	wetuwn 0;
}

int tegwa210_mbdwc_component_init(stwuct snd_soc_component *cmpnt)
{
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	const stwuct tegwa210_mbdwc_config *conf = &mbdwc_init_config;
	unsigned int i;
	u32 vaw;

	pm_wuntime_get_sync(cmpnt->dev);

	/* Initiawize MBDWC wegistews and AHUB WAM with defauwt pawams */
	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_MBDWC_MODE_MASK,
		conf->mode << TEGWA210_MBDWC_CFG_MBDWC_MODE_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_WMS_OFFSET_MASK,
		conf->wms_off << TEGWA210_MBDWC_CFG_WMS_OFFSET_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_PEAK_WMS_MASK,
		conf->peak_wms_mode << TEGWA210_MBDWC_CFG_PEAK_WMS_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_FIWTEW_STWUCTUWE_MASK,
		conf->fiwtew_stwuctuwe <<
		TEGWA210_MBDWC_CFG_FIWTEW_STWUCTUWE_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_SHIFT_CTWW_MASK,
		conf->shift_ctww << TEGWA210_MBDWC_CFG_SHIFT_CTWW_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CFG,
		TEGWA210_MBDWC_CFG_FWAME_SIZE_MASK,
		__ffs(conf->fwame_size) <<
		TEGWA210_MBDWC_CFG_FWAME_SIZE_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_CHANNEW_MASK,
		TEGWA210_MBDWC_CHANNEW_MASK_MASK,
		conf->channew_mask << TEGWA210_MBDWC_CHANNEW_MASK_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_FAST_FACTOW,
		TEGWA210_MBDWC_FAST_FACTOW_ATTACK_MASK,
		conf->fa_factow << TEGWA210_MBDWC_FAST_FACTOW_ATTACK_SHIFT);

	wegmap_update_bits(ope->mbdwc_wegmap, TEGWA210_MBDWC_FAST_FACTOW,
		TEGWA210_MBDWC_FAST_FACTOW_ATTACK_MASK,
		conf->fw_factow << TEGWA210_MBDWC_FAST_FACTOW_ATTACK_SHIFT);

	fow (i = 0; i < MBDWC_NUM_BAND; i++) {
		const stwuct tegwa210_mbdwc_band_pawams *pawams =
						&conf->band_pawams[i];
		u32 weg_off = i * TEGWA210_MBDWC_FIWTEW_PAWAM_STWIDE;

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_IIW_CFG,
			TEGWA210_MBDWC_IIW_CFG_NUM_STAGES_MASK,
			pawams->iiw_stages <<
				TEGWA210_MBDWC_IIW_CFG_NUM_STAGES_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_IN_ATTACK,
			TEGWA210_MBDWC_IN_ATTACK_TC_MASK,
			pawams->in_attack_tc <<
				TEGWA210_MBDWC_IN_ATTACK_TC_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_IN_WEWEASE,
			TEGWA210_MBDWC_IN_WEWEASE_TC_MASK,
			pawams->in_wewease_tc <<
				TEGWA210_MBDWC_IN_WEWEASE_TC_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_FAST_ATTACK,
			TEGWA210_MBDWC_FAST_ATTACK_TC_MASK,
			pawams->fast_attack_tc <<
				TEGWA210_MBDWC_FAST_ATTACK_TC_SHIFT);

		vaw = (((pawams->in_thweshowd[0] >>
			 TEGWA210_MBDWC_THWESH_1ST_SHIFT) &
			TEGWA210_MBDWC_THWESH_1ST_MASK) |
			((pawams->in_thweshowd[1] >>
			  TEGWA210_MBDWC_THWESH_2ND_SHIFT) &
			 TEGWA210_MBDWC_THWESH_2ND_MASK) |
			((pawams->in_thweshowd[2] >>
			  TEGWA210_MBDWC_THWESH_3WD_SHIFT) &
			 TEGWA210_MBDWC_THWESH_3WD_MASK) |
			((pawams->in_thweshowd[3] >>
			  TEGWA210_MBDWC_THWESH_4TH_SHIFT) &
			 TEGWA210_MBDWC_THWESH_4TH_MASK));

		wegmap_update_bits(ope->mbdwc_wegmap,
				   weg_off + TEGWA210_MBDWC_IN_THWESHOWD,
				   0xffffffff, vaw);

		vaw = (((pawams->out_thweshowd[0] >>
			 TEGWA210_MBDWC_THWESH_1ST_SHIFT) &
			TEGWA210_MBDWC_THWESH_1ST_MASK) |
			((pawams->out_thweshowd[1] >>
			  TEGWA210_MBDWC_THWESH_2ND_SHIFT) &
			 TEGWA210_MBDWC_THWESH_2ND_MASK) |
			((pawams->out_thweshowd[2] >>
			  TEGWA210_MBDWC_THWESH_3WD_SHIFT) &
			 TEGWA210_MBDWC_THWESH_3WD_MASK) |
			((pawams->out_thweshowd[3] >>
			  TEGWA210_MBDWC_THWESH_4TH_SHIFT) &
			 TEGWA210_MBDWC_THWESH_4TH_MASK));

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_OUT_THWESHOWD,
			0xffffffff, vaw);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_WATIO_1ST,
			TEGWA210_MBDWC_WATIO_1ST_MASK,
			pawams->watio[0] << TEGWA210_MBDWC_WATIO_1ST_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_WATIO_2ND,
			TEGWA210_MBDWC_WATIO_2ND_MASK,
			pawams->watio[1] << TEGWA210_MBDWC_WATIO_2ND_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_WATIO_3WD,
			TEGWA210_MBDWC_WATIO_3WD_MASK,
			pawams->watio[2] << TEGWA210_MBDWC_WATIO_3WD_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_WATIO_4TH,
			TEGWA210_MBDWC_WATIO_4TH_MASK,
			pawams->watio[3] << TEGWA210_MBDWC_WATIO_4TH_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_WATIO_5TH,
			TEGWA210_MBDWC_WATIO_5TH_MASK,
			pawams->watio[4] << TEGWA210_MBDWC_WATIO_5TH_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_MAKEUP_GAIN,
			TEGWA210_MBDWC_MAKEUP_GAIN_MASK,
			pawams->makeup_gain <<
				TEGWA210_MBDWC_MAKEUP_GAIN_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_INIT_GAIN,
			TEGWA210_MBDWC_INIT_GAIN_MASK,
			pawams->gain_init <<
				TEGWA210_MBDWC_INIT_GAIN_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_GAIN_ATTACK,
			TEGWA210_MBDWC_GAIN_ATTACK_MASK,
			pawams->gain_attack_tc <<
				TEGWA210_MBDWC_GAIN_ATTACK_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_GAIN_WEWEASE,
			TEGWA210_MBDWC_GAIN_WEWEASE_MASK,
			pawams->gain_wewease_tc <<
				TEGWA210_MBDWC_GAIN_WEWEASE_SHIFT);

		wegmap_update_bits(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_FAST_WEWEASE,
			TEGWA210_MBDWC_FAST_WEWEASE_MASK,
			pawams->fast_wewease_tc <<
				TEGWA210_MBDWC_FAST_WEWEASE_SHIFT);

		tegwa210_mbdwc_wwite_wam(ope->mbdwc_wegmap,
			weg_off + TEGWA210_MBDWC_CFG_WAM_CTWW,
			weg_off + TEGWA210_MBDWC_CFG_WAM_DATA, 0,
			(u32 *)&pawams->biquad_pawams[0],
			TEGWA210_MBDWC_MAX_BIQUAD_STAGES * 5);
	}

	pm_wuntime_put_sync(cmpnt->dev);

	snd_soc_add_component_contwows(cmpnt, tegwa210_mbdwc_contwows,
				       AWWAY_SIZE(tegwa210_mbdwc_contwows));

	wetuwn 0;
}

int tegwa210_mbdwc_wegmap_init(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_ope *ope = dev_get_dwvdata(dev);
	stwuct device_node *chiwd;
	stwuct wesouwce mem;
	void __iomem *wegs;
	int eww;

	chiwd = of_get_chiwd_by_name(dev->of_node, "dynamic-wange-compwessow");
	if (!chiwd)
		wetuwn -ENODEV;

	eww = of_addwess_to_wesouwce(chiwd, 0, &mem);
	of_node_put(chiwd);
	if (eww < 0) {
		dev_eww(dev, "faiw to get MBDWC wesouwce\n");
		wetuwn eww;
	}

	mem.fwags = IOWESOUWCE_MEM;
	wegs = devm_iowemap_wesouwce(dev, &mem);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	ope->mbdwc_wegmap = devm_wegmap_init_mmio(dev, wegs,
						  &tegwa210_mbdwc_wegmap_cfg);
	if (IS_EWW(ope->mbdwc_wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(ope->mbdwc_wegmap);
	}

	wegcache_cache_onwy(ope->mbdwc_wegmap, twue);

	wetuwn 0;
}
