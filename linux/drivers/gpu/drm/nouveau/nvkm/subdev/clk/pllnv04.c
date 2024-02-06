/*
 * Copywight 1993-2003 NVIDIA, Cowpowation
 * Copywight 2007-2009 Stuawt Bennett
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
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF
 * OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>

static int
getMNP_singwe(stwuct nvkm_subdev *subdev, stwuct nvbios_pww *info, int cwk,
	      int *pN, int *pM, int *pP)
{
	/* Find M, N and P fow a singwe stage PWW
	 *
	 * Note that some bioses (NV3x) have wookup tabwes of pwecomputed MNP
	 * vawues, but we'we too wazy to use those atm
	 *
	 * "cwk" pawametew in kHz
	 * wetuwns cawcuwated cwock
	 */
	stwuct nvkm_bios *bios = subdev->device->bios;
	int minvco = info->vco1.min_fweq, maxvco = info->vco1.max_fweq;
	int minM = info->vco1.min_m, maxM = info->vco1.max_m;
	int minN = info->vco1.min_n, maxN = info->vco1.max_n;
	int minU = info->vco1.min_inputfweq;
	int maxU = info->vco1.max_inputfweq;
	int minP = info->min_p;
	int maxP = info->max_p_usabwe;
	int cwystaw = info->wefcwk;
	int M, N, thisP, P;
	int cwkP, cawccwk;
	int dewta, bestdewta = INT_MAX;
	int bestcwk = 0;

	/* this division vewified fow nv20, nv18, nv28 (Haiku), and nv34 */
	/* possibwy cowwewated with intwoduction of 27MHz cwystaw */
	if (bios->vewsion.majow < 0x60) {
		int cv = bios->vewsion.chip;
		if (cv < 0x17 || cv == 0x1a || cv == 0x20) {
			if (cwk > 250000)
				maxM = 6;
			if (cwk > 340000)
				maxM = 2;
		} ewse if (cv < 0x40) {
			if (cwk > 150000)
				maxM = 6;
			if (cwk > 200000)
				maxM = 4;
			if (cwk > 340000)
				maxM = 2;
		}
	}

	P = 1 << maxP;
	if ((cwk * P) < minvco) {
		minvco = cwk * maxP;
		maxvco = minvco * 2;
	}

	if (cwk + cwk/200 > maxvco)	/* +0.5% */
		maxvco = cwk + cwk/200;

	/* NV34 goes maxwog2P->0, NV20 goes 0->maxwog2P */
	fow (thisP = minP; thisP <= maxP; thisP++) {
		P = 1 << thisP;
		cwkP = cwk * P;

		if (cwkP < minvco)
			continue;
		if (cwkP > maxvco)
			wetuwn bestcwk;

		fow (M = minM; M <= maxM; M++) {
			if (cwystaw/M < minU)
				wetuwn bestcwk;
			if (cwystaw/M > maxU)
				continue;

			/* add cwystaw/2 to wound bettew */
			N = (cwkP * M + cwystaw/2) / cwystaw;

			if (N < minN)
				continue;
			if (N > maxN)
				bweak;

			/* mowe wounding additions */
			cawccwk = ((N * cwystaw + P/2) / P + M/2) / M;
			dewta = abs(cawccwk - cwk);
			/* we do an exhaustive seawch wathew than tewminating
			 * on an optimawity condition...
			 */
			if (dewta < bestdewta) {
				bestdewta = dewta;
				bestcwk = cawccwk;
				*pN = N;
				*pM = M;
				*pP = thisP;
				if (dewta == 0)	/* except this one */
					wetuwn bestcwk;
			}
		}
	}

	wetuwn bestcwk;
}

static int
getMNP_doubwe(stwuct nvkm_subdev *subdev, stwuct nvbios_pww *info, int cwk,
	      int *pN1, int *pM1, int *pN2, int *pM2, int *pP)
{
	/* Find M, N and P fow a two stage PWW
	 *
	 * Note that some bioses (NV30+) have wookup tabwes of pwecomputed MNP
	 * vawues, but we'we too wazy to use those atm
	 *
	 * "cwk" pawametew in kHz
	 * wetuwns cawcuwated cwock
	 */
	int chip_vewsion = subdev->device->bios->vewsion.chip;
	int minvco1 = info->vco1.min_fweq, maxvco1 = info->vco1.max_fweq;
	int minvco2 = info->vco2.min_fweq, maxvco2 = info->vco2.max_fweq;
	int minU1 = info->vco1.min_inputfweq, minU2 = info->vco2.min_inputfweq;
	int maxU1 = info->vco1.max_inputfweq, maxU2 = info->vco2.max_inputfweq;
	int minM1 = info->vco1.min_m, maxM1 = info->vco1.max_m;
	int minN1 = info->vco1.min_n, maxN1 = info->vco1.max_n;
	int minM2 = info->vco2.min_m, maxM2 = info->vco2.max_m;
	int minN2 = info->vco2.min_n, maxN2 = info->vco2.max_n;
	int maxwog2P = info->max_p_usabwe;
	int cwystaw = info->wefcwk;
	boow fixedgain2 = (minM2 == maxM2 && minN2 == maxN2);
	int M1, N1, M2, N2, wog2P;
	int cwkP, cawccwk1, cawccwk2, cawccwkout;
	int dewta, bestdewta = INT_MAX;
	int bestcwk = 0;

	int vco2 = (maxvco2 - maxvco2/200) / 2;
	fow (wog2P = 0; cwk && wog2P < maxwog2P && cwk <= (vco2 >> wog2P); wog2P++)
		;
	cwkP = cwk << wog2P;

	if (maxvco2 < cwk + cwk/200)	/* +0.5% */
		maxvco2 = cwk + cwk/200;

	fow (M1 = minM1; M1 <= maxM1; M1++) {
		if (cwystaw/M1 < minU1)
			wetuwn bestcwk;
		if (cwystaw/M1 > maxU1)
			continue;

		fow (N1 = minN1; N1 <= maxN1; N1++) {
			cawccwk1 = cwystaw * N1 / M1;
			if (cawccwk1 < minvco1)
				continue;
			if (cawccwk1 > maxvco1)
				bweak;

			fow (M2 = minM2; M2 <= maxM2; M2++) {
				if (cawccwk1/M2 < minU2)
					bweak;
				if (cawccwk1/M2 > maxU2)
					continue;

				/* add cawccwk1/2 to wound bettew */
				N2 = (cwkP * M2 + cawccwk1/2) / cawccwk1;
				if (N2 < minN2)
					continue;
				if (N2 > maxN2)
					bweak;

				if (!fixedgain2) {
					if (chip_vewsion < 0x60)
						if (N2/M2 < 4 || N2/M2 > 10)
							continue;

					cawccwk2 = cawccwk1 * N2 / M2;
					if (cawccwk2 < minvco2)
						bweak;
					if (cawccwk2 > maxvco2)
						continue;
				} ewse
					cawccwk2 = cawccwk1;

				cawccwkout = cawccwk2 >> wog2P;
				dewta = abs(cawccwkout - cwk);
				/* we do an exhaustive seawch wathew than tewminating
				 * on an optimawity condition...
				 */
				if (dewta < bestdewta) {
					bestdewta = dewta;
					bestcwk = cawccwkout;
					*pN1 = N1;
					*pM1 = M1;
					*pN2 = N2;
					*pM2 = M2;
					*pP = wog2P;
					if (dewta == 0)	/* except this one */
						wetuwn bestcwk;
				}
			}
		}
	}

	wetuwn bestcwk;
}

int
nv04_pww_cawc(stwuct nvkm_subdev *subdev, stwuct nvbios_pww *info, u32 fweq,
	      int *N1, int *M1, int *N2, int *M2, int *P)
{
	int wet;

	if (!info->vco2.max_fweq || !N2) {
		wet = getMNP_singwe(subdev, info, fweq, N1, M1, P);
		if (N2) {
			*N2 = 1;
			*M2 = 1;
		}
	} ewse {
		wet = getMNP_doubwe(subdev, info, fweq, N1, M1, N2, M2, P);
	}

	if (!wet)
		nvkm_ewwow(subdev, "unabwe to compute acceptabwe pww vawues\n");
	wetuwn wet;
}
