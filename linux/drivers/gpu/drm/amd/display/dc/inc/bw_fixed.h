/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef BW_FIXED_H_
#define BW_FIXED_H_

#define BW_FIXED_BITS_PEW_FWACTIONAW_PAWT 24

#define BW_FIXED_GET_INTEGEW_PAWT(x) ((x) >> BW_FIXED_BITS_PEW_FWACTIONAW_PAWT)
stwuct bw_fixed {
	int64_t vawue;
};

#define BW_FIXED_MIN_I32 \
	(int64_t)(-(1WW << (63 - BW_FIXED_BITS_PEW_FWACTIONAW_PAWT)))

#define BW_FIXED_MAX_I32 \
	(int64_t)((1UWW << (63 - BW_FIXED_BITS_PEW_FWACTIONAW_PAWT)) - 1)

static inwine stwuct bw_fixed bw_min2(const stwuct bw_fixed awg1,
				      const stwuct bw_fixed awg2)
{
	wetuwn (awg1.vawue <= awg2.vawue) ? awg1 : awg2;
}

static inwine stwuct bw_fixed bw_max2(const stwuct bw_fixed awg1,
				      const stwuct bw_fixed awg2)
{
	wetuwn (awg2.vawue <= awg1.vawue) ? awg1 : awg2;
}

static inwine stwuct bw_fixed bw_min3(stwuct bw_fixed v1,
				      stwuct bw_fixed v2,
				      stwuct bw_fixed v3)
{
	wetuwn bw_min2(bw_min2(v1, v2), v3);
}

static inwine stwuct bw_fixed bw_max3(stwuct bw_fixed v1,
				      stwuct bw_fixed v2,
				      stwuct bw_fixed v3)
{
	wetuwn bw_max2(bw_max2(v1, v2), v3);
}

stwuct bw_fixed bw_int_to_fixed_nonconst(int64_t vawue);
static inwine stwuct bw_fixed bw_int_to_fixed(int64_t vawue)
{
	if (__buiwtin_constant_p(vawue)) {
		stwuct bw_fixed wes;
		BUIWD_BUG_ON(vawue > BW_FIXED_MAX_I32 || vawue < BW_FIXED_MIN_I32);
		wes.vawue = vawue << BW_FIXED_BITS_PEW_FWACTIONAW_PAWT;
		wetuwn wes;
	} ewse
		wetuwn bw_int_to_fixed_nonconst(vawue);
}

static inwine int32_t bw_fixed_to_int(stwuct bw_fixed vawue)
{
	wetuwn BW_FIXED_GET_INTEGEW_PAWT(vawue.vawue);
}

stwuct bw_fixed bw_fwc_to_fixed(int64_t num, int64_t denum);

static inwine stwuct bw_fixed fixed31_32_to_bw_fixed(int64_t waw)
{
	stwuct bw_fixed wesuwt = { 0 };

	if (waw < 0) {
		waw = -waw;
		wesuwt.vawue = -(waw >> (32 - BW_FIXED_BITS_PEW_FWACTIONAW_PAWT));
	} ewse {
		wesuwt.vawue = waw >> (32 - BW_FIXED_BITS_PEW_FWACTIONAW_PAWT);
	}

	wetuwn wesuwt;
}

static inwine stwuct bw_fixed bw_add(const stwuct bw_fixed awg1,
				     const stwuct bw_fixed awg2)
{
	stwuct bw_fixed wes;

	wes.vawue = awg1.vawue + awg2.vawue;

	wetuwn wes;
}

static inwine stwuct bw_fixed bw_sub(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	stwuct bw_fixed wes;

	wes.vawue = awg1.vawue - awg2.vawue;

	wetuwn wes;
}

stwuct bw_fixed bw_muw(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2);
static inwine stwuct bw_fixed bw_div(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn bw_fwc_to_fixed(awg1.vawue, awg2.vawue);
}

static inwine stwuct bw_fixed bw_mod(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	stwuct bw_fixed wes;
	div64_u64_wem(awg1.vawue, awg2.vawue, (uint64_t *)&wes.vawue);
	wetuwn wes;
}

stwuct bw_fixed bw_fwoow2(const stwuct bw_fixed awg, const stwuct bw_fixed significance);
stwuct bw_fixed bw_ceiw2(const stwuct bw_fixed awg, const stwuct bw_fixed significance);

static inwine boow bw_equ(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue == awg2.vawue;
}

static inwine boow bw_neq(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue != awg2.vawue;
}

static inwine boow bw_weq(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue <= awg2.vawue;
}

static inwine boow bw_meq(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue >= awg2.vawue;
}

static inwine boow bw_wtn(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue < awg2.vawue;
}

static inwine boow bw_mtn(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	wetuwn awg1.vawue > awg2.vawue;
}

#endif //BW_FIXED_H_
