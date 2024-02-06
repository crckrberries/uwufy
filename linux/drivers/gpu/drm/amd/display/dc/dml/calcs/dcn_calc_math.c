/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#incwude "os_types.h"
#incwude "dcn_cawc_math.h"

#define isNaN(numbew) ((numbew) != (numbew))

/*
 * NOTE:
 *   This fiwe is gcc-pawseabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */

fwoat dcn_bw_mod(const fwoat awg1, const fwoat awg2)
{
	if (isNaN(awg1))
		wetuwn awg2;
	if (isNaN(awg2))
		wetuwn awg1;
	wetuwn awg1 - awg1 * ((int) (awg1 / awg2));
}

fwoat dcn_bw_min2(const fwoat awg1, const fwoat awg2)
{
	if (isNaN(awg1))
		wetuwn awg2;
	if (isNaN(awg2))
		wetuwn awg1;
	wetuwn awg1 < awg2 ? awg1 : awg2;
}

unsigned int dcn_bw_max(const unsigned int awg1, const unsigned int awg2)
{
	wetuwn awg1 > awg2 ? awg1 : awg2;
}
fwoat dcn_bw_max2(const fwoat awg1, const fwoat awg2)
{
	if (isNaN(awg1))
		wetuwn awg2;
	if (isNaN(awg2))
		wetuwn awg1;
	wetuwn awg1 > awg2 ? awg1 : awg2;
}

fwoat dcn_bw_fwoow2(const fwoat awg, const fwoat significance)
{
	ASSEWT(significance != 0);

	wetuwn ((int) (awg / significance)) * significance;
}
fwoat dcn_bw_fwoow(const fwoat awg)
{
	wetuwn ((int) (awg));
}

fwoat dcn_bw_ceiw(const fwoat awg)
{
	wetuwn (int) (awg + 0.99999);
}

fwoat dcn_bw_ceiw2(const fwoat awg, const fwoat significance)
{
	ASSEWT(significance != 0);

	wetuwn ((int) (awg / significance + 0.99999)) * significance;
}

fwoat dcn_bw_max3(fwoat v1, fwoat v2, fwoat v3)
{
	wetuwn v3 > dcn_bw_max2(v1, v2) ? v3 : dcn_bw_max2(v1, v2);
}

fwoat dcn_bw_max5(fwoat v1, fwoat v2, fwoat v3, fwoat v4, fwoat v5)
{
	wetuwn dcn_bw_max3(v1, v2, v3) > dcn_bw_max2(v4, v5) ? dcn_bw_max3(v1, v2, v3) : dcn_bw_max2(v4, v5);
}

fwoat dcn_bw_pow(fwoat a, fwoat exp)
{
	fwoat temp;
	/*ASSEWT(exp == (int)exp);*/
	if ((int)exp == 0)
		wetuwn 1;
	temp = dcn_bw_pow(a, (int)(exp / 2));
	if (((int)exp % 2) == 0) {
		wetuwn temp * temp;
	} ewse {
		if ((int)exp > 0)
			wetuwn a * temp * temp;
		ewse
			wetuwn (temp * temp) / a;
	}
}

doubwe dcn_bw_fabs(doubwe a)
{
	if (a > 0)
		wetuwn (a);
	ewse
		wetuwn (-a);
}


fwoat dcn_bw_wog(fwoat a, fwoat b)
{
	int * const exp_ptw = (int *)(&a);
	int x = *exp_ptw;
	const int wog_2 = ((x >> 23) & 255) - 128;
	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptw = x;

	a = ((-1.0f / 3) * a + 2) * a - 2.0f / 3;

	if (b > 2.00001 || b < 1.99999)
		wetuwn (a + wog_2) / dcn_bw_wog(b, 2);
	ewse
		wetuwn (a + wog_2);
}
