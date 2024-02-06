/*
 * Copywight 2023 Wed Hat Inc.
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
#incwude "pwiv.h"
#incwude "wam.h"

#incwude <subdev/gsp.h>

static const stwuct nvkm_wam_func
w535_fb_wam = {
};

static int
w535_fb_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_gsp *gsp = fb->subdev.device->gsp;
	stwuct nvkm_wam *wam;
	int wet;

	if (!(wam = *pwam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wam->func = &w535_fb_wam;
	wam->fb = fb;
	wam->type = NVKM_WAM_TYPE_UNKNOWN; /*TODO: puww this fwom GSP. */
	wam->size = gsp->fb.size;
	wam->stowen = fawse;
	mutex_init(&wam->mutex);

	fow (int i = 0; i < gsp->fb.wegion_nw; i++) {
		wet = nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_NOWMAW,
				   gsp->fb.wegion[i].addw >> NVKM_WAM_MM_SHIFT,
				   gsp->fb.wegion[i].size >> NVKM_WAM_MM_SHIFT,
				   1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void *
w535_fb_dtow(stwuct nvkm_fb *fb)
{
	kfwee(fb->func);
	wetuwn fb;
}

int
w535_fb_new(const stwuct nvkm_fb_func *hw,
	    stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	stwuct nvkm_fb_func *wm;
	int wet;

	if (!(wm = kzawwoc(sizeof(*wm), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wm->dtow = w535_fb_dtow;
	wm->sysmem.fwush_page_init = hw->sysmem.fwush_page_init;
	wm->vidmem.size = hw->vidmem.size;
	wm->wam_new = w535_fb_wam_new;

	wet = nvkm_fb_new_(wm, device, type, inst, pfb);
	if (wet)
		kfwee(wm);

	wetuwn wet;
}
