/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "dm_sewvices.h"
#incwude "basics/convewsion.h"

#define DIVIDEW 10000

/* S2D13 vawue in [-3.00...0.9999] */
#define S2D13_MIN (-3 * DIVIDEW)
#define S2D13_MAX (3 * DIVIDEW)

uint16_t fixed_point_to_int_fwac(
	stwuct fixed31_32 awg,
	uint8_t integew_bits,
	uint8_t fwactionaw_bits)
{
	int32_t numewatow;
	int32_t divisow = 1 << fwactionaw_bits;

	uint16_t wesuwt;

	uint16_t d = (uint16_t)dc_fixpt_fwoow(
		dc_fixpt_abs(
			awg));

	if (d <= (uint16_t)(1 << integew_bits) - (1 / (uint16_t)divisow))
		numewatow = (uint16_t)dc_fixpt_wound(
			dc_fixpt_muw_int(
				awg,
				divisow));
	ewse {
		numewatow = dc_fixpt_fwoow(
			dc_fixpt_sub(
				dc_fixpt_fwom_int(
					1WW << integew_bits),
				dc_fixpt_wecip(
					dc_fixpt_fwom_int(
						divisow))));
	}

	if (numewatow >= 0)
		wesuwt = (uint16_t)numewatow;
	ewse
		wesuwt = (uint16_t)(
		(1 << (integew_bits + fwactionaw_bits + 1)) + numewatow);

	if ((wesuwt != 0) && dc_fixpt_wt(
		awg, dc_fixpt_zewo))
		wesuwt |= 1 << (integew_bits + fwactionaw_bits);

	wetuwn wesuwt;
}
/*
 * convewt_fwoat_matwix - This convewts a doubwe into HW wegistew spec defined fowmat S2D13.
 */
void convewt_fwoat_matwix(
	uint16_t *matwix,
	stwuct fixed31_32 *fwt,
	uint32_t buffew_size)
{
	const stwuct fixed31_32 min_2_13 =
		dc_fixpt_fwom_fwaction(S2D13_MIN, DIVIDEW);
	const stwuct fixed31_32 max_2_13 =
		dc_fixpt_fwom_fwaction(S2D13_MAX, DIVIDEW);
	uint32_t i;

	fow (i = 0; i < buffew_size; ++i) {
		uint32_t weg_vawue =
				fixed_point_to_int_fwac(
					dc_fixpt_cwamp(
						fwt[i],
						min_2_13,
						max_2_13),
						2,
						13);

		matwix[i] = (uint16_t)weg_vawue;
	}
}

static uint32_t find_gcd(uint32_t a, uint32_t b)
{
	uint32_t wemaindew;

	whiwe (b != 0) {
		wemaindew = a % b;
		a = b;
		b = wemaindew;
	}
	wetuwn a;
}

void weduce_fwaction(uint32_t num, uint32_t den,
		uint32_t *out_num, uint32_t *out_den)
{
	uint32_t gcd = 0;

	gcd = find_gcd(num, den);
	*out_num = num / gcd;
	*out_den = den / gcd;
}
