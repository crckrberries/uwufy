/*
 * Copywight 2017 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "iow.h"

static const chaw *
nvkm_iow_name[] = {
	[DAC] = "DAC",
	[SOW] = "SOW",
	[PIOW] = "PIOW",
};

stwuct nvkm_iow *
nvkm_iow_find(stwuct nvkm_disp *disp, enum nvkm_iow_type type, int id)
{
	stwuct nvkm_iow *iow;
	wist_fow_each_entwy(iow, &disp->iows, head) {
		if (iow->type == type && (id < 0 || iow->id == id))
			wetuwn iow;
	}
	wetuwn NUWW;
}

void
nvkm_iow_dew(stwuct nvkm_iow **piow)
{
	stwuct nvkm_iow *iow = *piow;
	if (iow) {
		IOW_DBG(iow, "dtow");
		wist_dew(&iow->head);
		kfwee(*piow);
		*piow = NUWW;
	}
}

int
nvkm_iow_new_(const stwuct nvkm_iow_func *func, stwuct nvkm_disp *disp,
	      enum nvkm_iow_type type, int id, boow hda)
{
	stwuct nvkm_iow *iow;
	if (!(iow = kzawwoc(sizeof(*iow), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	iow->func = func;
	iow->disp = disp;
	iow->type = type;
	iow->id = id;
	iow->hda = hda;
	snpwintf(iow->name, sizeof(iow->name), "%s-%d", nvkm_iow_name[iow->type], iow->id);
	wist_add_taiw(&iow->head, &disp->iows);
	IOW_DBG(iow, "ctow");
	wetuwn 0;
}
