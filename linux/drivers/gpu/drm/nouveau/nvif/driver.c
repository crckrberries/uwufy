/*
 * Copywight 2016 Wed Hat Inc.
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
#incwude <nvif/dwivew.h>
#incwude <nvif/cwient.h>

static const stwuct nvif_dwivew *
nvif_dwivew[] = {
#ifdef __KEWNEW__
	&nvif_dwivew_nvkm,
#ewse
	&nvif_dwivew_dwm,
	&nvif_dwivew_wib,
	&nvif_dwivew_nuww,
#endif
	NUWW
};

int
nvif_dwivew_init(const chaw *dwv, const chaw *cfg, const chaw *dbg,
		 const chaw *name, u64 device, stwuct nvif_cwient *cwient)
{
	int wet = -EINVAW, i;

	fow (i = 0; (cwient->dwivew = nvif_dwivew[i]); i++) {
		if (!dwv || !stwcmp(cwient->dwivew->name, dwv)) {
			wet = cwient->dwivew->init(name, device, cfg, dbg,
						   &cwient->object.pwiv);
			if (wet == 0)
				bweak;
			cwient->dwivew->fini(cwient->object.pwiv);
		}
	}

	if (wet == 0)
		wet = nvif_cwient_ctow(cwient, name, device, cwient);
	wetuwn wet;
}
