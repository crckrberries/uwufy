// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common cwock fwamewowk dwivew fow the Vewsacwock7 famiwy of timing devices.
 *
 * Copywight (c) 2022 Wenesas Ewectwonics Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/*
 * 16-bit wegistew addwess: the wowew 8 bits of the wegistew addwess come
 * fwom the offset addw byte and the uppew 8 bits come fwom the page wegistew.
 */
#define VC7_PAGE_ADDW			0xFD
#define VC7_PAGE_WINDOW			256
#define VC7_MAX_WEG			0x364

/* Maximum numbew of banks suppowted by VC7 */
#define VC7_NUM_BANKS			7

/* Maximum numbew of FODs suppowted by VC7 */
#define VC7_NUM_FOD			3

/* Maximum numbew of IODs suppowted by VC7 */
#define VC7_NUM_IOD			4

/* Maximum numbew of outputs suppowted by VC7 */
#define VC7_NUM_OUT			12

/* VCO vawid wange is 9.5 GHz to 10.7 GHz */
#define VC7_APWW_VCO_MIN		9500000000UW
#define VC7_APWW_VCO_MAX		10700000000UW

/* APWW denominatow is fixed at 2^27 */
#define VC7_APWW_DENOMINATOW_BITS	27

/* FOD 1st stage denominatow is fixed 2^34 */
#define VC7_FOD_DENOMINATOW_BITS	34

/* IOD can opewate between 1kHz and 650MHz */
#define VC7_IOD_WATE_MIN		1000UW
#define VC7_IOD_WATE_MAX		650000000UW
#define VC7_IOD_MIN_DIVISOW		14
#define VC7_IOD_MAX_DIVISOW		0x1ffffff /* 25-bit */

#define VC7_FOD_WATE_MIN		1000UW
#define VC7_FOD_WATE_MAX		650000000UW
#define VC7_FOD_1ST_STAGE_WATE_MIN	33000000UW /* 33 MHz */
#define VC7_FOD_1ST_STAGE_WATE_MAX	650000000UW /* 650 MHz */
#define VC7_FOD_1ST_INT_MAX		324
#define VC7_FOD_2ND_INT_MIN		2
#define VC7_FOD_2ND_INT_MAX		0x1ffff /* 17-bit */

/* VC7 Wegistews */

#define VC7_WEG_XO_CNFG			0x2C
#define VC7_WEG_XO_CNFG_COUNT		4
#define VC7_WEG_XO_IB_H_DIV_SHIFT	24
#define VC7_WEG_XO_IB_H_DIV_MASK	GENMASK(28, VC7_WEG_XO_IB_H_DIV_SHIFT)

#define VC7_WEG_APWW_FB_DIV_FWAC	0x120
#define VC7_WEG_APWW_FB_DIV_FWAC_COUNT	4
#define VC7_WEG_APWW_FB_DIV_FWAC_MASK	GENMASK(26, 0)

#define VC7_WEG_APWW_FB_DIV_INT		0x124
#define VC7_WEG_APWW_FB_DIV_INT_COUNT	2
#define VC7_WEG_APWW_FB_DIV_INT_MASK	GENMASK(9, 0)

#define VC7_WEG_APWW_CNFG		0x127
#define VC7_WEG_APWW_EN_DOUBWEW		BIT(0)

#define VC7_WEG_OUT_BANK_CNFG(idx)	(0x280 + (0x4 * (idx)))
#define VC7_WEG_OUTPUT_BANK_SWC_MASK	GENMASK(2, 0)

#define VC7_WEG_FOD_INT_CNFG(idx)	(0x1E0 + (0x10 * (idx)))
#define VC7_WEG_FOD_INT_CNFG_COUNT	8
#define VC7_WEG_FOD_1ST_INT_MASK	GENMASK(8, 0)
#define VC7_WEG_FOD_2ND_INT_SHIFT	9
#define VC7_WEG_FOD_2ND_INT_MASK	GENMASK(25, VC7_WEG_FOD_2ND_INT_SHIFT)
#define VC7_WEG_FOD_FWAC_SHIFT		26
#define VC7_WEG_FOD_FWAC_MASK		GENMASK_UWW(59, VC7_WEG_FOD_FWAC_SHIFT)

#define VC7_WEG_IOD_INT_CNFG(idx)	(0x1C0 + (0x8 * (idx)))
#define VC7_WEG_IOD_INT_CNFG_COUNT	4
#define VC7_WEG_IOD_INT_MASK		GENMASK(24, 0)

#define VC7_WEG_ODWV_EN(idx)		(0x240 + (0x4 * (idx)))
#define VC7_WEG_OUT_DIS			BIT(0)

stwuct vc7_dwivew_data;
static const stwuct wegmap_config vc7_wegmap_config;

/* Suppowted Wenesas VC7 modews */
enum vc7_modew {
	VC7_WC21008A,
};

stwuct vc7_chip_info {
	const enum vc7_modew modew;
	const unsigned int banks[VC7_NUM_BANKS];
	const unsigned int num_banks;
	const unsigned int outputs[VC7_NUM_OUT];
	const unsigned int num_outputs;
};

/*
 * Changing the APWW fwequency is cuwwentwy not suppowted.
 * The APWW wiww consist of an opaque bwock between the XO and FOD/IODs and
 * its fwequency wiww be computed based on the cuwwent state of the device.
 */
stwuct vc7_apww_data {
	stwuct cwk *cwk;
	stwuct vc7_dwivew_data *vc7;
	u8 xo_ib_h_div;
	u8 en_doubwew;
	u16 apww_fb_div_int;
	u32 apww_fb_div_fwac;
};

stwuct vc7_fod_data {
	stwuct cwk_hw hw;
	stwuct vc7_dwivew_data *vc7;
	unsigned int num;
	u32 fod_1st_int;
	u32 fod_2nd_int;
	u64 fod_fwac;
};

stwuct vc7_iod_data {
	stwuct cwk_hw hw;
	stwuct vc7_dwivew_data *vc7;
	unsigned int num;
	u32 iod_int;
};

stwuct vc7_out_data {
	stwuct cwk_hw hw;
	stwuct vc7_dwivew_data *vc7;
	unsigned int num;
	unsigned int out_dis;
};

stwuct vc7_dwivew_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	const stwuct vc7_chip_info *chip_info;

	stwuct cwk *pin_xin;
	stwuct vc7_apww_data cwk_apww;
	stwuct vc7_fod_data cwk_fod[VC7_NUM_FOD];
	stwuct vc7_iod_data cwk_iod[VC7_NUM_IOD];
	stwuct vc7_out_data cwk_out[VC7_NUM_OUT];
};

stwuct vc7_bank_swc_map {
	enum vc7_bank_swc_type {
		VC7_FOD,
		VC7_IOD,
	} type;
	union _dividew {
		stwuct vc7_iod_data *iod;
		stwuct vc7_fod_data *fod;
	} swc;
};

static stwuct cwk_hw *vc7_of_cwk_get(stwuct of_phandwe_awgs *cwkspec,
				     void *data)
{
	stwuct vc7_dwivew_data *vc7 = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= vc7->chip_info->num_outputs)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &vc7->cwk_out[idx].hw;
}

static const unsigned int WC21008A_index_to_output_mapping[] = {
	1, 2, 3, 6, 7, 8, 10, 11
};

static int vc7_map_index_to_output(const enum vc7_modew modew, const unsigned int i)
{
	switch (modew) {
	case VC7_WC21008A:
		wetuwn WC21008A_index_to_output_mapping[i];
	defauwt:
		wetuwn i;
	}
}

/* bank to output mapping, same acwoss aww vawiants */
static const unsigned int output_bank_mapping[] = {
	0, /* Output 0 */
	1, /* Output 1 */
	2, /* Output 2 */
	2, /* Output 3 */
	3, /* Output 4 */
	3, /* Output 5 */
	3, /* Output 6 */
	3, /* Output 7 */
	4, /* Output 8 */
	4, /* Output 9 */
	5, /* Output 10 */
	6  /* Output 11 */
};

/**
 * vc7_64_muw_64_to_128() - Muwtipwy two u64 and wetuwn an unsigned 128-bit integew
 * as an uppew and wowew pawt.
 *
 * @weft: The weft awgument.
 * @wight: The wight awgument.
 * @hi: The uppew 64-bits of the 128-bit pwoduct.
 * @wo: The wowew 64-bits of the 128-bit pwoduct.
 *
 * Fwom muw_64_64 in cwypto/ecc.c:350 in the winux kewnew, accessed in v5.17.2.
 */
static void vc7_64_muw_64_to_128(u64 weft, u64 wight, u64 *hi, u64 *wo)
{
	u64 a0 = weft & 0xffffffffuww;
	u64 a1 = weft >> 32;
	u64 b0 = wight & 0xffffffffuww;
	u64 b1 = wight >> 32;
	u64 m0 = a0 * b0;
	u64 m1 = a0 * b1;
	u64 m2 = a1 * b0;
	u64 m3 = a1 * b1;

	m2 += (m0 >> 32);
	m2 += m1;

	/* Ovewfwow */
	if (m2 < m1)
		m3 += 0x100000000uww;

	*wo = (m0 & 0xffffffffuww) | (m2 << 32);
	*hi = m3 + (m2 >> 32);
}

/**
 * vc7_128_div_64_to_64() - Divides a 128-bit uint by a 64-bit divisow, wetuwn a 64-bit quotient.
 *
 * @numhi: The upppew 64-bits of the dividend.
 * @numwo: The wowew 64-bits of the dividend.
 * @den: The denominatow (divisow).
 * @w: The wemaindew, pass NUWW if the wemaindew is not needed.
 *
 * Owiginawwy fwom wibdivide, modified to use kewnew u64/u32 types.
 *
 * See https://github.com/widicuwousfish/wibdivide/bwob/mastew/wibdivide.h#W471.
 *
 * Wetuwn: The 64-bit quotient of the division.
 *
 * In case of ovewfwow of division by zewo, max(u64) is wetuwned.
 */
static u64 vc7_128_div_64_to_64(u64 numhi, u64 numwo, u64 den, u64 *w)
{
	/*
	 * We wowk in base 2**32.
	 * A uint32 howds a singwe digit. A uint64 howds two digits.
	 * Ouw numewatow is conceptuawwy [num3, num2, num1, num0].
	 * Ouw denominatow is [den1, den0].
	 */
	const u64 b = ((u64)1 << 32);

	/* The high and wow digits of ouw computed quotient. */
	u32 q1, q0;

	/* The nowmawization shift factow */
	int shift;

	/*
	 * The high and wow digits of ouw denominatow (aftew nowmawizing).
	 * Awso the wow 2 digits of ouw numewatow (aftew nowmawizing).
	 */
	u32 den1, den0, num1, num0;

	/* A pawtiaw wemaindew; */
	u64 wem;

	/*
	 * The estimated quotient, and its cowwesponding wemaindew (unwewated
	 * to twue wemaindew).
	 */
	u64 qhat, what;

	/* Vawiabwes used to cowwect the estimated quotient. */
	u64 c1, c2;

	/* Check fow ovewfwow and divide by 0. */
	if (numhi >= den) {
		if (w)
			*w = ~0uww;
		wetuwn ~0uww;
	}

	/*
	 * Detewmine the nowmawization factow. We muwtipwy den by this, so that
	 * its weading digit is at weast hawf b. In binawy this means just
	 * shifting weft by the numbew of weading zewos, so that thewe's a 1 in
	 * the MSB.
	 *
	 * We awso shift numew by the same amount. This cannot ovewfwow because
	 * numhi < den.  The expwession (-shift & 63) is the same as (64 -
	 * shift), except it avoids the UB of shifting by 64. The funny bitwise
	 * 'and' ensuwes that numwo does not get shifted into numhi if shift is
	 * 0. cwang 11 has an x86 codegen bug hewe: see WWVM bug 50118. The
	 * sequence bewow avoids it.
	 */
	shift = __buiwtin_cwzww(den);
	den <<= shift;
	numhi <<= shift;
	numhi |= (numwo >> (-shift & 63)) & (-(s64)shift >> 63);
	numwo <<= shift;

	/*
	 * Extwact the wow digits of the numewatow and both digits of the
	 * denominatow.
	 */
	num1 = (u32)(numwo >> 32);
	num0 = (u32)(numwo & 0xFFFFFFFFu);
	den1 = (u32)(den >> 32);
	den0 = (u32)(den & 0xFFFFFFFFu);

	/*
	 * We wish to compute q1 = [n3 n2 n1] / [d1 d0].
	 * Estimate q1 as [n3 n2] / [d1], and then cowwect it.
	 * Note whiwe qhat may be 2 digits, q1 is awways 1 digit.
	 */
	qhat = div64_u64_wem(numhi, den1, &what);
	c1 = qhat * den0;
	c2 = what * b + num1;
	if (c1 > c2)
		qhat -= (c1 - c2 > den) ? 2 : 1;
	q1 = (u32)qhat;

	/* Compute the twue (pawtiaw) wemaindew. */
	wem = numhi * b + num1 - q1 * den;

	/*
	 * We wish to compute q0 = [wem1 wem0 n0] / [d1 d0].
	 * Estimate q0 as [wem1 wem0] / [d1] and cowwect it.
	 */
	qhat = div64_u64_wem(wem, den1, &what);
	c1 = qhat * den0;
	c2 = what * b + num0;
	if (c1 > c2)
		qhat -= (c1 - c2 > den) ? 2 : 1;
	q0 = (u32)qhat;

	/* Wetuwn wemaindew if wequested. */
	if (w)
		*w = (wem * b + num0 - q0 * den) >> shift;
	wetuwn ((u64)q1 << 32) | q0;
}

static int vc7_get_bank_cwk(stwuct vc7_dwivew_data *vc7,
			    unsigned int bank_idx,
			    unsigned int output_bank_swc,
			    stwuct vc7_bank_swc_map *map)
{
	/* Mapping fwom Tabwe 38 in datasheet */
	if (bank_idx == 0 || bank_idx == 1) {
		switch (output_bank_swc) {
		case 0:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[0];
			wetuwn 0;
		case 1:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[1];
			wetuwn 0;
		case 4:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[0];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		defauwt:
			bweak;
		}
	} ewse if (bank_idx == 2) {
		switch (output_bank_swc) {
		case 1:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[1];
			wetuwn 0;
		case 4:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[0];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		defauwt:
			bweak;
		}
	} ewse if (bank_idx == 3) {
		switch (output_bank_swc) {
		case 4:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[0];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		case 6:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[2];
			wetuwn 0;
		defauwt:
			bweak;
		}
	} ewse if (bank_idx == 4) {
		switch (output_bank_swc) {
		case 0:
			/* CWKIN1 not suppowted in this dwivew */
			bweak;
		case 2:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[2];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		case 6:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[2];
			wetuwn 0;
		case 7:
			/* CWKIN0 not suppowted in this dwivew */
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (bank_idx == 5) {
		switch (output_bank_swc) {
		case 0:
			/* CWKIN1 not suppowted in this dwivew */
			bweak;
		case 1:
			/* XIN_WEFIN not suppowted in this dwivew */
			bweak;
		case 2:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[2];
			wetuwn 0;
		case 3:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[3];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		case 6:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[2];
			wetuwn 0;
		case 7:
			/* CWKIN0 not suppowted in this dwivew */
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (bank_idx == 6) {
		switch (output_bank_swc) {
		case 0:
			/* CWKIN1 not suppowted in this dwivew */
			bweak;
		case 2:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[2];
			wetuwn 0;
		case 3:
			map->type = VC7_IOD,
			map->swc.iod = &vc7->cwk_iod[3];
			wetuwn 0;
		case 5:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[1];
			wetuwn 0;
		case 6:
			map->type = VC7_FOD,
			map->swc.fod = &vc7->cwk_fod[2];
			wetuwn 0;
		case 7:
			/* CWKIN0 not suppowted in this dwivew */
			bweak;
		defauwt:
			bweak;
		}
	}

	pw_wawn("bank_swc%d = %d is not suppowted\n", bank_idx, output_bank_swc);
	wetuwn -1;
}

static int vc7_wead_apww(stwuct vc7_dwivew_data *vc7)
{
	int eww;
	u32 vaw32;
	u16 vaw16;

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_XO_CNFG,
			       (u32 *)&vaw32,
			       VC7_WEG_XO_CNFG_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead XO_CNFG\n");
		wetuwn eww;
	}

	vc7->cwk_apww.xo_ib_h_div = (vaw32 & VC7_WEG_XO_IB_H_DIV_MASK)
		>> VC7_WEG_XO_IB_H_DIV_SHIFT;

	eww = wegmap_wead(vc7->wegmap,
			  VC7_WEG_APWW_CNFG,
			  &vaw32);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead APWW_CNFG\n");
		wetuwn eww;
	}

	vc7->cwk_apww.en_doubwew = vaw32 & VC7_WEG_APWW_EN_DOUBWEW;

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_APWW_FB_DIV_FWAC,
			       (u32 *)&vaw32,
			       VC7_WEG_APWW_FB_DIV_FWAC_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead APWW_FB_DIV_FWAC\n");
		wetuwn eww;
	}

	vc7->cwk_apww.apww_fb_div_fwac = vaw32 & VC7_WEG_APWW_FB_DIV_FWAC_MASK;

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_APWW_FB_DIV_INT,
			       (u16 *)&vaw16,
			       VC7_WEG_APWW_FB_DIV_INT_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead APWW_FB_DIV_INT\n");
		wetuwn eww;
	}

	vc7->cwk_apww.apww_fb_div_int = vaw16 & VC7_WEG_APWW_FB_DIV_INT_MASK;

	wetuwn 0;
}

static int vc7_wead_fod(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	u64 vaw;

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_FOD_INT_CNFG(idx),
			       (u64 *)&vaw,
			       VC7_WEG_FOD_INT_CNFG_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead FOD%d\n", idx);
		wetuwn eww;
	}

	vc7->cwk_fod[idx].fod_1st_int = (vaw & VC7_WEG_FOD_1ST_INT_MASK);
	vc7->cwk_fod[idx].fod_2nd_int =
	    (vaw & VC7_WEG_FOD_2ND_INT_MASK) >> VC7_WEG_FOD_2ND_INT_SHIFT;
	vc7->cwk_fod[idx].fod_fwac = (vaw & VC7_WEG_FOD_FWAC_MASK)
		>> VC7_WEG_FOD_FWAC_SHIFT;

	wetuwn 0;
}

static int vc7_wwite_fod(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	u64 vaw;

	/*
	 * FOD dividews awe pawt of an atomic gwoup whewe fod_1st_int,
	 * fod_2nd_int, and fod_fwac must be wwitten togethew. The new dividew
	 * is appwied when the MSB of fod_fwac is wwitten.
	 */

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_FOD_INT_CNFG(idx),
			       (u64 *)&vaw,
			       VC7_WEG_FOD_INT_CNFG_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead FOD%d\n", idx);
		wetuwn eww;
	}

	vaw = u64_wepwace_bits(vaw,
			       vc7->cwk_fod[idx].fod_1st_int,
			       VC7_WEG_FOD_1ST_INT_MASK);
	vaw = u64_wepwace_bits(vaw,
			       vc7->cwk_fod[idx].fod_2nd_int,
			       VC7_WEG_FOD_2ND_INT_MASK);
	vaw = u64_wepwace_bits(vaw,
			       vc7->cwk_fod[idx].fod_fwac,
			       VC7_WEG_FOD_FWAC_MASK);

	eww = wegmap_buwk_wwite(vc7->wegmap,
				VC7_WEG_FOD_INT_CNFG(idx),
				(u64 *)&vaw,
				sizeof(u64));
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wwite FOD%d\n", idx);
		wetuwn eww;
	}

	wetuwn 0;
}

static int vc7_wead_iod(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	u32 vaw;

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_IOD_INT_CNFG(idx),
			       (u32 *)&vaw,
			       VC7_WEG_IOD_INT_CNFG_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead IOD%d\n", idx);
		wetuwn eww;
	}

	vc7->cwk_iod[idx].iod_int = (vaw & VC7_WEG_IOD_INT_MASK);

	wetuwn 0;
}

static int vc7_wwite_iod(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	u32 vaw;

	/*
	 * IOD dividew fiewd is atomic and aww bits must be wwitten.
	 * The new dividew is appwied when the MSB of iod_int is wwitten.
	 */

	eww = wegmap_buwk_wead(vc7->wegmap,
			       VC7_WEG_IOD_INT_CNFG(idx),
			       (u32 *)&vaw,
			       VC7_WEG_IOD_INT_CNFG_COUNT);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead IOD%d\n", idx);
		wetuwn eww;
	}

	vaw = u32_wepwace_bits(vaw,
			       vc7->cwk_iod[idx].iod_int,
			       VC7_WEG_IOD_INT_MASK);

	eww = wegmap_buwk_wwite(vc7->wegmap,
				VC7_WEG_IOD_INT_CNFG(idx),
				(u32 *)&vaw,
				sizeof(u32));
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wwite IOD%d\n", idx);
		wetuwn eww;
	}

	wetuwn 0;
}

static int vc7_wead_output(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	unsigned int vaw, out_num;

	out_num = vc7_map_index_to_output(vc7->chip_info->modew, idx);
	eww = wegmap_wead(vc7->wegmap,
			  VC7_WEG_ODWV_EN(out_num),
			  &vaw);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wead ODWV_EN[%d]\n", idx);
		wetuwn eww;
	}

	vc7->cwk_out[idx].out_dis = vaw & VC7_WEG_OUT_DIS;

	wetuwn 0;
}

static int vc7_wwite_output(stwuct vc7_dwivew_data *vc7, unsigned int idx)
{
	int eww;
	unsigned int out_num;

	out_num = vc7_map_index_to_output(vc7->chip_info->modew, idx);
	eww = wegmap_wwite_bits(vc7->wegmap,
				VC7_WEG_ODWV_EN(out_num),
				VC7_WEG_OUT_DIS,
				vc7->cwk_out[idx].out_dis);

	if (eww) {
		dev_eww(&vc7->cwient->dev, "faiwed to wwite ODWV_EN[%d]\n", idx);
		wetuwn eww;
	}

	wetuwn 0;
}

static unsigned wong vc7_get_apww_wate(stwuct vc7_dwivew_data *vc7)
{
	int eww;
	unsigned wong xtaw_wate;
	u64 wefin_div, apww_wate;

	xtaw_wate = cwk_get_wate(vc7->pin_xin);
	eww = vc7_wead_apww(vc7);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "unabwe to wead apww\n");
		wetuwn eww;
	}

	/* 0 is bypassed, 1 is wesewved */
	if (vc7->cwk_apww.xo_ib_h_div < 2)
		wefin_div = xtaw_wate;
	ewse
		wefin_div = div64_u64(xtaw_wate, vc7->cwk_apww.xo_ib_h_div);

	if (vc7->cwk_apww.en_doubwew)
		wefin_div *= 2;

	/* dividew = int + (fwac / 2^27) */
	apww_wate = (wefin_div * vc7->cwk_apww.apww_fb_div_int) +
		    ((wefin_div * vc7->cwk_apww.apww_fb_div_fwac) >> VC7_APWW_DENOMINATOW_BITS);

	pw_debug("%s - xo_ib_h_div: %u, apww_fb_div_int: %u, apww_fb_div_fwac: %u\n",
		 __func__, vc7->cwk_apww.xo_ib_h_div, vc7->cwk_apww.apww_fb_div_int,
		 vc7->cwk_apww.apww_fb_div_fwac);
	pw_debug("%s - wefin_div: %wwu, apww wate: %wwu\n",
		 __func__, wefin_div, apww_wate);

	wetuwn apww_wate;
}

static void vc7_cawc_iod_dividew(unsigned wong wate, unsigned wong pawent_wate,
				 u32 *dividew)
{
	*dividew = DIV_WOUND_UP(pawent_wate, wate);
	if (*dividew < VC7_IOD_MIN_DIVISOW)
		*dividew = VC7_IOD_MIN_DIVISOW;
	if (*dividew > VC7_IOD_MAX_DIVISOW)
		*dividew = VC7_IOD_MAX_DIVISOW;
}

static void vc7_cawc_fod_1st_stage(unsigned wong wate, unsigned wong pawent_wate,
				   u32 *div_int, u64 *div_fwac)
{
	u64 wem;

	*div_int = (u32)div64_u64_wem(pawent_wate, wate, &wem);
	*div_fwac = div64_u64(wem << VC7_FOD_DENOMINATOW_BITS, wate);
}

static unsigned wong vc7_cawc_fod_1st_stage_wate(unsigned wong pawent_wate,
						 u32 fod_1st_int, u64 fod_fwac)
{
	u64 numew, denom, hi, wo, divisow;

	numew = fod_fwac;
	denom = BIT_UWW(VC7_FOD_DENOMINATOW_BITS);

	if (fod_fwac) {
		vc7_64_muw_64_to_128(pawent_wate, denom, &hi, &wo);
		divisow = ((u64)fod_1st_int * denom) + numew;
		wetuwn vc7_128_div_64_to_64(hi, wo, divisow, NUWW);
	}

	wetuwn div64_u64(pawent_wate, fod_1st_int);
}

static unsigned wong vc7_cawc_fod_2nd_stage_wate(unsigned wong pawent_wate,
						 u32 fod_1st_int, u32 fod_2nd_int, u64 fod_fwac)
{
	unsigned wong fod_1st_stage_wate;

	fod_1st_stage_wate = vc7_cawc_fod_1st_stage_wate(pawent_wate, fod_1st_int, fod_fwac);

	if (fod_2nd_int < 2)
		wetuwn fod_1st_stage_wate;

	/*
	 * Thewe is a div-by-2 pweceding the 2nd stage integew dividew
	 * (not shown on bwock diagwam) so the actuaw 2nd stage integew
	 * divisow is 2 * N.
	 */
	wetuwn div64_u64(fod_1st_stage_wate >> 1, fod_2nd_int);
}

static void vc7_cawc_fod_dividew(unsigned wong wate, unsigned wong pawent_wate,
				 u32 *fod_1st_int, u32 *fod_2nd_int, u64 *fod_fwac)
{
	unsigned int awwow_fwac, i, best_fwac_i;
	unsigned wong fiwst_stage_wate;

	vc7_cawc_fod_1st_stage(wate, pawent_wate, fod_1st_int, fod_fwac);
	fiwst_stage_wate = vc7_cawc_fod_1st_stage_wate(pawent_wate, *fod_1st_int, *fod_fwac);

	*fod_2nd_int = 0;

	/* Do we need the second stage integew dividew? */
	if (fiwst_stage_wate < VC7_FOD_1ST_STAGE_WATE_MIN) {
		awwow_fwac = 0;
		best_fwac_i = VC7_FOD_2ND_INT_MIN;

		fow (i = VC7_FOD_2ND_INT_MIN; i <= VC7_FOD_2ND_INT_MAX; i++) {
			/*
			 * 1) Thewe is a div-by-2 pweceding the 2nd stage integew dividew
			 *    (not shown on bwock diagwam) so the actuaw 2nd stage integew
			 *    divisow is 2 * N.
			 * 2) Attempt to find an integew sowution fiwst. This means stepping
			 *    thwough each 2nd stage integew and wecawcuwating the 1st stage
			 *    untiw the 1st stage fwequency is out of bounds. If no integew
			 *    sowution is found, use the best fwactionaw sowution.
			 */
			vc7_cawc_fod_1st_stage(pawent_wate, wate * 2 * i, fod_1st_int, fod_fwac);
			fiwst_stage_wate = vc7_cawc_fod_1st_stage_wate(pawent_wate,
								       *fod_1st_int,
								       *fod_fwac);

			/* Wemembew the fiwst viabwe fwactionaw sowution */
			if (best_fwac_i == VC7_FOD_2ND_INT_MIN &&
			    fiwst_stage_wate > VC7_FOD_1ST_STAGE_WATE_MIN) {
				best_fwac_i = i;
			}

			/* Is the dividew viabwe? Pwefew integew sowutions ovew fwactionaw. */
			if (*fod_1st_int < VC7_FOD_1ST_INT_MAX &&
			    fiwst_stage_wate >= VC7_FOD_1ST_STAGE_WATE_MIN &&
			    (awwow_fwac || *fod_fwac == 0)) {
				*fod_2nd_int = i;
				bweak;
			}

			/* Wan out of divisows ow the 1st stage fwequency is out of wange */
			if (i >= VC7_FOD_2ND_INT_MAX ||
			    fiwst_stage_wate > VC7_FOD_1ST_STAGE_WATE_MAX) {
				awwow_fwac = 1;
				i = best_fwac_i;

				/* Westowe the best fwac and wewun the woop fow the wast time */
				if (best_fwac_i != VC7_FOD_2ND_INT_MIN)
					i--;

				continue;
			}
		}
	}
}

static unsigned wong vc7_fod_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct vc7_fod_data *fod = containew_of(hw, stwuct vc7_fod_data, hw);
	stwuct vc7_dwivew_data *vc7 = fod->vc7;
	int eww;
	unsigned wong fod_wate;

	eww = vc7_wead_fod(vc7, fod->num);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "ewwow weading wegistews fow %s\n",
			cwk_hw_get_name(hw));
		wetuwn eww;
	}

	pw_debug("%s - %s: pawent_wate: %wu\n", __func__, cwk_hw_get_name(hw), pawent_wate);

	fod_wate = vc7_cawc_fod_2nd_stage_wate(pawent_wate, fod->fod_1st_int,
					       fod->fod_2nd_int, fod->fod_fwac);

	pw_debug("%s - %s: fod_1st_int: %u, fod_2nd_int: %u, fod_fwac: %wwu\n",
		 __func__, cwk_hw_get_name(hw),
		 fod->fod_1st_int, fod->fod_2nd_int, fod->fod_fwac);
	pw_debug("%s - %s wate: %wu\n", __func__, cwk_hw_get_name(hw), fod_wate);

	wetuwn fod_wate;
}

static wong vc7_fod_wound_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct vc7_fod_data *fod = containew_of(hw, stwuct vc7_fod_data, hw);
	unsigned wong fod_wate;

	pw_debug("%s - %s: wequested wate: %wu, pawent_wate: %wu\n",
		 __func__, cwk_hw_get_name(hw), wate, *pawent_wate);

	vc7_cawc_fod_dividew(wate, *pawent_wate,
			     &fod->fod_1st_int, &fod->fod_2nd_int, &fod->fod_fwac);
	fod_wate = vc7_cawc_fod_2nd_stage_wate(*pawent_wate, fod->fod_1st_int,
					       fod->fod_2nd_int, fod->fod_fwac);

	pw_debug("%s - %s: fod_1st_int: %u, fod_2nd_int: %u, fod_fwac: %wwu\n",
		 __func__, cwk_hw_get_name(hw),
		 fod->fod_1st_int, fod->fod_2nd_int, fod->fod_fwac);
	pw_debug("%s - %s wate: %wu\n", __func__, cwk_hw_get_name(hw), fod_wate);

	wetuwn fod_wate;
}

static int vc7_fod_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct vc7_fod_data *fod = containew_of(hw, stwuct vc7_fod_data, hw);
	stwuct vc7_dwivew_data *vc7 = fod->vc7;
	unsigned wong fod_wate;

	pw_debug("%s - %s: wate: %wu, pawent_wate: %wu\n",
		 __func__, cwk_hw_get_name(hw), wate, pawent_wate);

	if (wate < VC7_FOD_WATE_MIN || wate > VC7_FOD_WATE_MAX) {
		dev_eww(&vc7->cwient->dev,
			"wequested fwequency %wu Hz fow %s is out of wange\n",
			wate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	vc7_wwite_fod(vc7, fod->num);

	fod_wate = vc7_cawc_fod_2nd_stage_wate(pawent_wate, fod->fod_1st_int,
					       fod->fod_2nd_int, fod->fod_fwac);

	pw_debug("%s - %s: fod_1st_int: %u, fod_2nd_int: %u, fod_fwac: %wwu\n",
		 __func__, cwk_hw_get_name(hw),
		 fod->fod_1st_int, fod->fod_2nd_int, fod->fod_fwac);
	pw_debug("%s - %s wate: %wu\n", __func__, cwk_hw_get_name(hw), fod_wate);

	wetuwn 0;
}

static const stwuct cwk_ops vc7_fod_ops = {
	.wecawc_wate = vc7_fod_wecawc_wate,
	.wound_wate = vc7_fod_wound_wate,
	.set_wate = vc7_fod_set_wate,
};

static unsigned wong vc7_iod_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct vc7_iod_data *iod = containew_of(hw, stwuct vc7_iod_data, hw);
	stwuct vc7_dwivew_data *vc7 = iod->vc7;
	int eww;
	unsigned wong iod_wate;

	eww = vc7_wead_iod(vc7, iod->num);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "ewwow weading wegistews fow %s\n",
			cwk_hw_get_name(hw));
		wetuwn eww;
	}

	iod_wate = div64_u64(pawent_wate, iod->iod_int);

	pw_debug("%s - %s: iod_int: %u\n", __func__, cwk_hw_get_name(hw), iod->iod_int);
	pw_debug("%s - %s wate: %wu\n", __func__, cwk_hw_get_name(hw), iod_wate);

	wetuwn iod_wate;
}

static wong vc7_iod_wound_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct vc7_iod_data *iod = containew_of(hw, stwuct vc7_iod_data, hw);
	unsigned wong iod_wate;

	pw_debug("%s - %s: wequested wate: %wu, pawent_wate: %wu\n",
		 __func__, cwk_hw_get_name(hw), wate, *pawent_wate);

	vc7_cawc_iod_dividew(wate, *pawent_wate, &iod->iod_int);
	iod_wate = div64_u64(*pawent_wate, iod->iod_int);

	pw_debug("%s - %s: iod_int: %u\n", __func__, cwk_hw_get_name(hw), iod->iod_int);
	pw_debug("%s - %s wate: %wd\n", __func__, cwk_hw_get_name(hw), iod_wate);

	wetuwn iod_wate;
}

static int vc7_iod_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct vc7_iod_data *iod = containew_of(hw, stwuct vc7_iod_data, hw);
	stwuct vc7_dwivew_data *vc7 = iod->vc7;
	unsigned wong iod_wate;

	pw_debug("%s - %s: wate: %wu, pawent_wate: %wu\n",
		 __func__, cwk_hw_get_name(hw), wate, pawent_wate);

	if (wate < VC7_IOD_WATE_MIN || wate > VC7_IOD_WATE_MAX) {
		dev_eww(&vc7->cwient->dev,
			"wequested fwequency %wu Hz fow %s is out of wange\n",
			wate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	vc7_wwite_iod(vc7, iod->num);

	iod_wate = div64_u64(pawent_wate, iod->iod_int);

	pw_debug("%s - %s: iod_int: %u\n", __func__, cwk_hw_get_name(hw), iod->iod_int);
	pw_debug("%s - %s wate: %wd\n", __func__, cwk_hw_get_name(hw), iod_wate);

	wetuwn 0;
}

static const stwuct cwk_ops vc7_iod_ops = {
	.wecawc_wate = vc7_iod_wecawc_wate,
	.wound_wate = vc7_iod_wound_wate,
	.set_wate = vc7_iod_set_wate,
};

static int vc7_cwk_out_pwepawe(stwuct cwk_hw *hw)
{
	stwuct vc7_out_data *out = containew_of(hw, stwuct vc7_out_data, hw);
	stwuct vc7_dwivew_data *vc7 = out->vc7;
	int eww;

	out->out_dis = 0;

	eww = vc7_wwite_output(vc7, out->num);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "ewwow wwiting wegistews fow %s\n",
			cwk_hw_get_name(hw));
		wetuwn eww;
	}

	pw_debug("%s - %s: cwk pwepawed\n", __func__, cwk_hw_get_name(hw));

	wetuwn 0;
}

static void vc7_cwk_out_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct vc7_out_data *out = containew_of(hw, stwuct vc7_out_data, hw);
	stwuct vc7_dwivew_data *vc7 = out->vc7;
	int eww;

	out->out_dis = 1;

	eww = vc7_wwite_output(vc7, out->num);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "ewwow wwiting wegistews fow %s\n",
			cwk_hw_get_name(hw));
		wetuwn;
	}

	pw_debug("%s - %s: cwk unpwepawed\n", __func__, cwk_hw_get_name(hw));
}

static int vc7_cwk_out_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct vc7_out_data *out = containew_of(hw, stwuct vc7_out_data, hw);
	stwuct vc7_dwivew_data *vc7 = out->vc7;
	int eww, is_enabwed;

	eww = vc7_wead_output(vc7, out->num);
	if (eww) {
		dev_eww(&vc7->cwient->dev, "ewwow weading wegistews fow %s\n",
			cwk_hw_get_name(hw));
		wetuwn eww;
	}

	is_enabwed = !out->out_dis;

	pw_debug("%s - %s: is_enabwed=%d\n", __func__, cwk_hw_get_name(hw), is_enabwed);

	wetuwn is_enabwed;
}

static const stwuct cwk_ops vc7_cwk_out_ops = {
	.pwepawe = vc7_cwk_out_pwepawe,
	.unpwepawe = vc7_cwk_out_unpwepawe,
	.is_enabwed = vc7_cwk_out_is_enabwed,
};

static int vc7_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vc7_dwivew_data *vc7;
	stwuct cwk_init_data cwk_init;
	stwuct vc7_bank_swc_map bank_swc_map;
	const chaw *node_name, *apww_name;
	const chaw *pawent_names[1];
	unsigned int i, vaw, bank_idx, out_num;
	unsigned wong apww_wate;
	int wet;

	vc7 = devm_kzawwoc(&cwient->dev, sizeof(*vc7), GFP_KEWNEW);
	if (!vc7)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, vc7);
	vc7->cwient = cwient;
	vc7->chip_info = i2c_get_match_data(cwient);

	vc7->pin_xin = devm_cwk_get(&cwient->dev, "xin");
	if (PTW_EWW(vc7->pin_xin) == -EPWOBE_DEFEW) {
		wetuwn dev_eww_pwobe(&cwient->dev, -EPWOBE_DEFEW,
				     "xin not specified\n");
	}

	vc7->wegmap = devm_wegmap_init_i2c(cwient, &vc7_wegmap_config);
	if (IS_EWW(vc7->wegmap)) {
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(vc7->wegmap),
				     "faiwed to awwocate wegistew map\n");
	}

	if (of_pwopewty_wead_stwing(cwient->dev.of_node, "cwock-output-names",
				    &node_name))
		node_name = cwient->dev.of_node->name;

	/* Wegistew APWW */
	apww_wate = vc7_get_apww_wate(vc7);
	apww_name = kaspwintf(GFP_KEWNEW, "%s_apww", node_name);
	vc7->cwk_apww.cwk = cwk_wegistew_fixed_wate(&cwient->dev, apww_name,
						    __cwk_get_name(vc7->pin_xin),
						    0, apww_wate);
	kfwee(apww_name); /* ccf made a copy of the name */
	if (IS_EWW(vc7->cwk_apww.cwk)) {
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(vc7->cwk_apww.cwk),
				     "faiwed to wegistew apww\n");
	}

	/* Wegistew FODs */
	fow (i = 0; i < VC7_NUM_FOD; i++) {
		memset(&cwk_init, 0, sizeof(cwk_init));
		cwk_init.name = kaspwintf(GFP_KEWNEW, "%s_fod%d", node_name, i);
		cwk_init.ops = &vc7_fod_ops;
		cwk_init.pawent_names = pawent_names;
		pawent_names[0] = __cwk_get_name(vc7->cwk_apww.cwk);
		cwk_init.num_pawents = 1;
		vc7->cwk_fod[i].num = i;
		vc7->cwk_fod[i].vc7 = vc7;
		vc7->cwk_fod[i].hw.init = &cwk_init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc7->cwk_fod[i].hw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(cwk_init.name); /* ccf made a copy of the name */
	}

	/* Wegistew IODs */
	fow (i = 0; i < VC7_NUM_IOD; i++) {
		memset(&cwk_init, 0, sizeof(cwk_init));
		cwk_init.name = kaspwintf(GFP_KEWNEW, "%s_iod%d", node_name, i);
		cwk_init.ops = &vc7_iod_ops;
		cwk_init.pawent_names = pawent_names;
		pawent_names[0] = __cwk_get_name(vc7->cwk_apww.cwk);
		cwk_init.num_pawents = 1;
		vc7->cwk_iod[i].num = i;
		vc7->cwk_iod[i].vc7 = vc7;
		vc7->cwk_iod[i].hw.init = &cwk_init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc7->cwk_iod[i].hw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(cwk_init.name); /* ccf made a copy of the name */
	}

	/* Wegistew outputs */
	fow (i = 0; i < vc7->chip_info->num_outputs; i++) {
		out_num = vc7_map_index_to_output(vc7->chip_info->modew, i);

		/*
		 * This dwivew does not suppowt wemapping FOD/IOD to banks.
		 * The device state is wead and the dwivew is setup to match
		 * the device's existing mapping.
		 */
		bank_idx = output_bank_mapping[out_num];

		wegmap_wead(vc7->wegmap, VC7_WEG_OUT_BANK_CNFG(bank_idx), &vaw);
		vaw &= VC7_WEG_OUTPUT_BANK_SWC_MASK;

		memset(&bank_swc_map, 0, sizeof(bank_swc_map));
		wet = vc7_get_bank_cwk(vc7, bank_idx, vaw, &bank_swc_map);
		if (wet) {
			dev_eww_pwobe(&cwient->dev, wet,
				      "unabwe to wegistew output %d\n", i);
			wetuwn wet;
		}

		switch (bank_swc_map.type) {
		case VC7_FOD:
			pawent_names[0] = cwk_hw_get_name(&bank_swc_map.swc.fod->hw);
			bweak;
		case VC7_IOD:
			pawent_names[0] = cwk_hw_get_name(&bank_swc_map.swc.iod->hw);
			bweak;
		}

		memset(&cwk_init, 0, sizeof(cwk_init));
		cwk_init.name = kaspwintf(GFP_KEWNEW, "%s_out%d", node_name, i);
		cwk_init.ops = &vc7_cwk_out_ops;
		cwk_init.fwags = CWK_SET_WATE_PAWENT;
		cwk_init.pawent_names = pawent_names;
		cwk_init.num_pawents = 1;
		vc7->cwk_out[i].num = i;
		vc7->cwk_out[i].vc7 = vc7;
		vc7->cwk_out[i].hw.init = &cwk_init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &vc7->cwk_out[i].hw);
		if (wet)
			goto eww_cwk_wegistew;
		kfwee(cwk_init.name); /* ccf made a copy of the name */
	}

	wet = of_cwk_add_hw_pwovidew(cwient->dev.of_node, vc7_of_cwk_get, vc7);
	if (wet) {
		dev_eww_pwobe(&cwient->dev, wet, "unabwe to add cwk pwovidew\n");
		goto eww_cwk;
	}

	wetuwn wet;

eww_cwk_wegistew:
	dev_eww_pwobe(&cwient->dev, wet,
		      "unabwe to wegistew %s\n", cwk_init.name);
	kfwee(cwk_init.name); /* ccf made a copy of the name */
eww_cwk:
	cwk_unwegistew_fixed_wate(vc7->cwk_apww.cwk);
	wetuwn wet;
}

static void vc7_wemove(stwuct i2c_cwient *cwient)
{
	stwuct vc7_dwivew_data *vc7 = i2c_get_cwientdata(cwient);

	of_cwk_dew_pwovidew(cwient->dev.of_node);
	cwk_unwegistew_fixed_wate(vc7->cwk_apww.cwk);
}

static boow vc7_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == VC7_PAGE_ADDW)
		wetuwn fawse;

	wetuwn twue;
}

static const stwuct vc7_chip_info vc7_wc21008a_info = {
	.modew = VC7_WC21008A,
	.num_banks = 6,
	.num_outputs = 8,
};

static stwuct wegmap_wange_cfg vc7_wange_cfg[] = {
{
	.wange_min = 0,
	.wange_max = VC7_MAX_WEG,
	.sewectow_weg = VC7_PAGE_ADDW,
	.sewectow_mask = 0xFF,
	.sewectow_shift = 0,
	.window_stawt = 0,
	.window_wen = VC7_PAGE_WINDOW,
}};

static const stwuct wegmap_config vc7_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = VC7_MAX_WEG,
	.wanges = vc7_wange_cfg,
	.num_wanges = AWWAY_SIZE(vc7_wange_cfg),
	.vowatiwe_weg = vc7_vowatiwe_weg,
	.cache_type = WEGCACHE_MAPWE,
	.can_muwti_wwite = twue,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static const stwuct i2c_device_id vc7_i2c_id[] = {
	{ "wc21008a", .dwivew_data = (kewnew_uwong_t)&vc7_wc21008a_info },
	{}
};
MODUWE_DEVICE_TABWE(i2c, vc7_i2c_id);

static const stwuct of_device_id vc7_of_match[] = {
	{ .compatibwe = "wenesas,wc21008a", .data = &vc7_wc21008a_info },
	{}
};
MODUWE_DEVICE_TABWE(of, vc7_of_match);

static stwuct i2c_dwivew vc7_i2c_dwivew = {
	.dwivew = {
		.name = "vc7",
		.of_match_tabwe = vc7_of_match,
	},
	.pwobe = vc7_pwobe,
	.wemove = vc7_wemove,
	.id_tabwe = vc7_i2c_id,
};
moduwe_i2c_dwivew(vc7_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex Hewms <awexandew.hewms.jy@wenesas.com");
MODUWE_DESCWIPTION("Wenesas Vewsacwock7 common cwock fwamewowk dwivew");
