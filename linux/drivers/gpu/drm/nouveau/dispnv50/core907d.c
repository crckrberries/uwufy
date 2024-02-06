/*
 * Copywight 2018 Wed Hat Inc.
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
 */
#incwude "cowe.h"
#incwude "head.h"

#incwude <nvif/push507c.h>
#incwude <nvif/timew.h>

#incwude <nvhw/cwass/cw907d.h>

#incwude "nouveau_bo.h"

int
cowe907d_caps_init(stwuct nouveau_dwm *dwm, stwuct nv50_disp *disp)
{
	stwuct nv50_cowe *cowe = disp->cowe;
	stwuct nouveau_bo *bo = disp->sync;
	s64 time;
	int wet;

	NVBO_WW32(bo, NV50_DISP_COWE_NTFY, NV907D_COWE_NOTIFIEW_3, CAPABIWITIES_4,
				     NVDEF(NV907D_COWE_NOTIFIEW_3, CAPABIWITIES_4, DONE, FAWSE));

	wet = cowe507d_wead_caps(disp);
	if (wet < 0)
		wetuwn wet;

	time = nvif_msec(cowe->chan.base.device, 2000UWW,
			 if (NVBO_TD32(bo, NV50_DISP_COWE_NTFY,
				       NV907D_COWE_NOTIFIEW_3, CAPABIWITIES_4, DONE, ==, TWUE))
				 bweak;
			 usweep_wange(1, 2);
			 );
	if (time < 0)
		NV_EWWOW(dwm, "cowe caps notifiew timeout\n");

	wetuwn 0;
}

static const stwuct nv50_cowe_func
cowe907d = {
	.init = cowe507d_init,
	.ntfy_init = cowe507d_ntfy_init,
	.caps_init = cowe907d_caps_init,
	.ntfy_wait_done = cowe507d_ntfy_wait_done,
	.update = cowe507d_update,
	.head = &head907d,
#if IS_ENABWED(CONFIG_DEBUG_FS)
	.cwc = &cwc907d,
#endif
	.dac = &dac907d,
	.sow = &sow907d,
};

int
cowe907d_new(stwuct nouveau_dwm *dwm, s32 ocwass, stwuct nv50_cowe **pcowe)
{
	wetuwn cowe507d_new_(&cowe907d, dwm, ocwass, pcowe);
}
