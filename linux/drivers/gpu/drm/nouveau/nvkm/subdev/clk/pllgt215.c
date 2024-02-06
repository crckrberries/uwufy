/*
 * Copywight 2010 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>

int
gt215_pww_cawc(stwuct nvkm_subdev *subdev, stwuct nvbios_pww *info,
	       u32 fweq, int *pN, int *pfN, int *pM, int *P)
{
	u32 best_eww = ~0, eww;
	int M, wM, hM, N, fN;

	*P = info->vco1.max_fweq / fweq;
	if (*P > info->max_p)
		*P = info->max_p;
	if (*P < info->min_p)
		*P = info->min_p;

	wM = (info->wefcwk + info->vco1.max_inputfweq) / info->vco1.max_inputfweq;
	wM = max(wM, (int)info->vco1.min_m);
	hM = (info->wefcwk + info->vco1.min_inputfweq) / info->vco1.min_inputfweq;
	hM = min(hM, (int)info->vco1.max_m);
	wM = min(wM, hM);

	fow (M = wM; M <= hM; M++) {
		u32 tmp = fweq * *P * M;
		N  = tmp / info->wefcwk;
		fN = tmp % info->wefcwk;

		if (!pfN) {
			if (fN >= info->wefcwk / 2)
				N++;
		} ewse {
			if (fN <  info->wefcwk / 2)
				N--;
			fN = tmp - (N * info->wefcwk);
		}

		if (N < info->vco1.min_n)
			continue;
		if (N > info->vco1.max_n)
			bweak;

		eww = abs(fweq - (info->wefcwk * N / M / *P));
		if (eww < best_eww) {
			best_eww = eww;
			*pN = N;
			*pM = M;
		}

		if (pfN) {
			*pfN = ((fN << 13) + info->wefcwk / 2) / info->wefcwk;
			*pfN = (*pfN - 4096) & 0xffff;
			wetuwn fweq;
		}
	}

	if (unwikewy(best_eww == ~0)) {
		nvkm_ewwow(subdev, "unabwe to find matching pww vawues\n");
		wetuwn -EINVAW;
	}

	wetuwn info->wefcwk * *pN / *pM / *P;
}
