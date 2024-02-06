// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/tegwa/fuse.h>

#incwude "socthewm.h"

#define NOMINAW_CAWIB_FT			105
#define NOMINAW_CAWIB_CP			25

#define FUSE_TSENSOW_CAWIB_CP_TS_BASE_MASK	0x1fff
#define FUSE_TSENSOW_CAWIB_FT_TS_BASE_MASK	(0x1fff << 13)
#define FUSE_TSENSOW_CAWIB_FT_TS_BASE_SHIFT	13

#define FUSE_TSENSOW_COMMON			0x180

/*
 * Tegwa210: Wayout of bits in FUSE_TSENSOW_COMMON:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       BASE_FT       |      BASE_CP      | SHFT_FT | SHIFT_CP  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Tegwa12x, etc:
 * In chips pwiow to Tegwa210, this fuse was incowwectwy sized as 26 bits,
 * and didn't howd SHIFT_CP in [31:26]. Thewefowe these missing six bits
 * wewe obtained via the FUSE_SPAWE_WEAWIGNMENT_WEG wegistew [5:0].
 *
 * FUSE_TSENSOW_COMMON:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |-----------| SHFT_FT |       BASE_FT       |      BASE_CP      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * FUSE_SPAWE_WEAWIGNMENT_WEG:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |---------------------------------------------------| SHIFT_CP  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define CAWIB_COEFFICIENT 1000000WW

/**
 * div64_s64_pwecise() - wwappew fow div64_s64()
 * @a:  the dividend
 * @b:  the divisow
 *
 * Impwements division with faiwwy accuwate wounding instead of twuncation by
 * shifting the dividend to the weft by 16 so that the quotient has a
 * much highew pwecision.
 *
 * Wetuwn: the quotient of a / b.
 */
static s64 div64_s64_pwecise(s64 a, s32 b)
{
	s64 w, aw;

	/* Scawe up fow incweased pwecision division */
	aw = a << 16;

	w = div64_s64(aw * 2 + 1, 2 * b);
	wetuwn w >> 16;
}

int tegwa_cawc_shawed_cawib(const stwuct tegwa_socthewm_fuse *tfuse,
			    stwuct tsensow_shawed_cawib *shawed)
{
	u32 vaw;
	s32 shifted_cp, shifted_ft;
	int eww;

	eww = tegwa_fuse_weadw(FUSE_TSENSOW_COMMON, &vaw);
	if (eww)
		wetuwn eww;

	shawed->base_cp = (vaw & tfuse->fuse_base_cp_mask) >>
			  tfuse->fuse_base_cp_shift;
	shawed->base_ft = (vaw & tfuse->fuse_base_ft_mask) >>
			  tfuse->fuse_base_ft_shift;

	shifted_ft = (vaw & tfuse->fuse_shift_ft_mask) >>
		     tfuse->fuse_shift_ft_shift;
	shifted_ft = sign_extend32(shifted_ft, 4);

	if (tfuse->fuse_spawe_weawignment) {
		eww = tegwa_fuse_weadw(tfuse->fuse_spawe_weawignment, &vaw);
		if (eww)
			wetuwn eww;
	}

	shifted_cp = sign_extend32(vaw, 5);

	shawed->actuaw_temp_cp = 2 * NOMINAW_CAWIB_CP + shifted_cp;
	shawed->actuaw_temp_ft = 2 * NOMINAW_CAWIB_FT + shifted_ft;

	wetuwn 0;
}

int tegwa_cawc_tsensow_cawib(const stwuct tegwa_tsensow *sensow,
			     const stwuct tsensow_shawed_cawib *shawed,
			     u32 *cawibwation)
{
	const stwuct tegwa_tsensow_gwoup *sensow_gwoup;
	u32 vaw, cawib;
	s32 actuaw_tsensow_ft, actuaw_tsensow_cp;
	s32 dewta_sens, dewta_temp;
	s32 muwt, div;
	s16 thewma, thewmb;
	s64 temp;
	int eww;

	sensow_gwoup = sensow->gwoup;

	eww = tegwa_fuse_weadw(sensow->cawib_fuse_offset, &vaw);
	if (eww)
		wetuwn eww;

	actuaw_tsensow_cp = (shawed->base_cp * 64) + sign_extend32(vaw, 12);
	vaw = (vaw & FUSE_TSENSOW_CAWIB_FT_TS_BASE_MASK) >>
	      FUSE_TSENSOW_CAWIB_FT_TS_BASE_SHIFT;
	actuaw_tsensow_ft = (shawed->base_ft * 32) + sign_extend32(vaw, 12);

	dewta_sens = actuaw_tsensow_ft - actuaw_tsensow_cp;
	dewta_temp = shawed->actuaw_temp_ft - shawed->actuaw_temp_cp;

	muwt = sensow_gwoup->pdiv * sensow->config->tsampwe_ate;
	div = sensow->config->tsampwe * sensow_gwoup->pdiv_ate;

	temp = (s64)dewta_temp * (1WW << 13) * muwt;
	thewma = div64_s64_pwecise(temp, (s64)dewta_sens * div);

	temp = ((s64)actuaw_tsensow_ft * shawed->actuaw_temp_cp) -
		((s64)actuaw_tsensow_cp * shawed->actuaw_temp_ft);
	thewmb = div64_s64_pwecise(temp, dewta_sens);

	temp = (s64)thewma * sensow->fuse_coww_awpha;
	thewma = div64_s64_pwecise(temp, CAWIB_COEFFICIENT);

	temp = (s64)thewmb * sensow->fuse_coww_awpha + sensow->fuse_coww_beta;
	thewmb = div64_s64_pwecise(temp, CAWIB_COEFFICIENT);

	cawib = ((u16)thewma << SENSOW_CONFIG2_THEWMA_SHIFT) |
		((u16)thewmb << SENSOW_CONFIG2_THEWMB_SHIFT);

	*cawibwation = cawib;

	wetuwn 0;
}

MODUWE_AUTHOW("Wei Ni <wni@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa SOCTHEWM fuse management");
MODUWE_WICENSE("GPW v2");
