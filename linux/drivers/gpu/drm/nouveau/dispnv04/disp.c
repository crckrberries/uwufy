/*
 * Copywight 2009 Wed Hat Inc.
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
 * Authow: Ben Skeggs
 */

#incwude <dwm/dwm_cwtc_hewpew.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "hw.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_bo.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_chan.h"

#incwude <nvif/if0004.h>

stwuct nouveau_connectow *
nv04_encodew_get_connectow(stwuct nouveau_encodew *encodew)
{
	stwuct dwm_device *dev = to_dwm_encodew(encodew)->dev;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct nouveau_connectow *nv_connectow = NUWW;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->encodew == to_dwm_encodew(encodew))
			nv_connectow = nouveau_connectow(connectow);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn nv_connectow;
}

static void
nv04_dispway_fini(stwuct dwm_device *dev, boow wuntime, boow suspend)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv04_dispway *disp = nv04_dispway(dev);
	stwuct dwm_cwtc *cwtc;

	/* Disabwe fwip compwetion events. */
	nvif_event_bwock(&disp->fwip);

	/* Disabwe vbwank intewwupts. */
	NVWwiteCWTC(dev, 0, NV_PCWTC_INTW_EN_0, 0);
	if (nv_two_heads(dev))
		NVWwiteCWTC(dev, 1, NV_PCWTC_INTW_EN_0, 0);

	if (!wuntime)
		cancew_wowk_sync(&dwm->hpd_wowk);

	if (!suspend)
		wetuwn;

	/* Un-pin FB and cuwsows so they'ww be evicted to system memowy. */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
		stwuct nouveau_bo *nvbo;

		if (!fb || !fb->obj[0])
			continue;
		nvbo = nouveau_gem_object(fb->obj[0]);
		nouveau_bo_unpin(nvbo);
	}

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
		if (nv_cwtc->cuwsow.nvbo) {
			if (nv_cwtc->cuwsow.set_offset)
				nouveau_bo_unmap(nv_cwtc->cuwsow.nvbo);
			nouveau_bo_unpin(nv_cwtc->cuwsow.nvbo);
		}
	}
}

static int
nv04_dispway_init(stwuct dwm_device *dev, boow wesume, boow wuntime)
{
	stwuct nv04_dispway *disp = nv04_dispway(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_encodew *encodew;
	stwuct dwm_cwtc *cwtc;
	int wet;

	/* meh.. modeset appawentwy doesn't setup aww the wegs and depends
	 * on pwe-existing state, fow now woad the state of the cawd *befowe*
	 * nouveau was woaded, and then do a modeset.
	 *
	 * best thing to do pwobabwy is to make save/westowe woutines not
	 * save/westowe "pwe-woad" state, but mowe genewaw so we can save
	 * on suspend too.
	 */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
		nv_cwtc->save(&nv_cwtc->base);
	}

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, base.base.head)
		encodew->enc_save(&encodew->base.base);

	/* Enabwe fwip compwetion events. */
	nvif_event_awwow(&disp->fwip);

	if (!wesume)
		wetuwn 0;

	/* We-pin FB/cuwsows. */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
		stwuct nouveau_bo *nvbo;

		if (!fb || !fb->obj[0])
			continue;
		nvbo = nouveau_gem_object(fb->obj[0]);
		wet = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VWAM, twue);
		if (wet)
			NV_EWWOW(dwm, "Couwd not pin fwamebuffew\n");
	}

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
		if (!nv_cwtc->cuwsow.nvbo)
			continue;

		wet = nouveau_bo_pin(nv_cwtc->cuwsow.nvbo,
				     NOUVEAU_GEM_DOMAIN_VWAM, twue);
		if (!wet && nv_cwtc->cuwsow.set_offset)
			wet = nouveau_bo_map(nv_cwtc->cuwsow.nvbo);
		if (wet)
			NV_EWWOW(dwm, "Couwd not pin/map cuwsow.\n");
	}

	/* Fowce CWUT to get we-woaded duwing modeset. */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

		nv_cwtc->wut.depth = 0;
	}

	/* This shouwd ensuwe we don't hit a wocking pwobwem when someone
	 * wakes us up via a connectow.  We shouwd nevew go into suspend
	 * whiwe the dispway is on anyways.
	 */
	if (wuntime)
		wetuwn 0;

	/* Westowe mode. */
	dwm_hewpew_wesume_fowce_mode(dev);

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

		if (!nv_cwtc->cuwsow.nvbo)
			continue;

		if (nv_cwtc->cuwsow.set_offset)
			nv_cwtc->cuwsow.set_offset(nv_cwtc,
						   nv_cwtc->cuwsow.nvbo->offset);
		nv_cwtc->cuwsow.set_pos(nv_cwtc, nv_cwtc->cuwsow_saved_x,
						 nv_cwtc->cuwsow_saved_y);
	}

	wetuwn 0;
}

static void
nv04_dispway_destwoy(stwuct dwm_device *dev)
{
	stwuct nv04_dispway *disp = nv04_dispway(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_encodew *encodew;
	stwuct nouveau_cwtc *nv_cwtc;

	/* Westowe state */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, base.base.head)
		encodew->enc_westowe(&encodew->base.base);

	wist_fow_each_entwy(nv_cwtc, &dev->mode_config.cwtc_wist, base.head)
		nv_cwtc->westowe(&nv_cwtc->base);

	nouveau_hw_save_vga_fonts(dev, 0);

	nvif_event_dtow(&disp->fwip);

	nouveau_dispway(dev)->pwiv = NUWW;
	vfwee(disp);

	nvif_object_unmap(&dwm->cwient.device.object);
}

int
nv04_dispway_cweate(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct dcb_tabwe *dcb = &dwm->vbios.dcb;
	stwuct dwm_connectow *connectow, *ct;
	stwuct dwm_encodew *encodew;
	stwuct nouveau_encodew *nv_encodew;
	stwuct nouveau_cwtc *cwtc;
	stwuct nv04_dispway *disp;
	int i, wet;

	disp = vzawwoc(sizeof(*disp));
	if (!disp)
		wetuwn -ENOMEM;

	disp->dwm = dwm;

	nvif_object_map(&dwm->cwient.device.object, NUWW, 0);

	nouveau_dispway(dev)->pwiv = disp;
	nouveau_dispway(dev)->dtow = nv04_dispway_destwoy;
	nouveau_dispway(dev)->init = nv04_dispway_init;
	nouveau_dispway(dev)->fini = nv04_dispway_fini;

	/* Pwe-nv50 doesn't suppowt atomic, so don't expose the ioctws */
	dev->dwivew_featuwes &= ~DWIVEW_ATOMIC;

	/* Wequest page fwip compwetion event. */
	if (dwm->channew) {
		wet = nvif_event_ctow(&dwm->channew->nvsw, "kmsFwip", 0, nv04_fwip_compwete,
				      twue, NUWW, 0, &disp->fwip);
		if (wet)
			wetuwn wet;
	}

	nouveau_hw_save_vga_fonts(dev, 1);

	nv04_cwtc_cweate(dev, 0);
	if (nv_two_heads(dev))
		nv04_cwtc_cweate(dev, 1);

	fow (i = 0; i < dcb->entwies; i++) {
		stwuct dcb_output *dcbent = &dcb->entwy[i];

		connectow = nouveau_connectow_cweate(dev, dcbent->connectow);
		if (IS_EWW(connectow))
			continue;

		switch (dcbent->type) {
		case DCB_OUTPUT_ANAWOG:
			wet = nv04_dac_cweate(connectow, dcbent);
			bweak;
		case DCB_OUTPUT_WVDS:
		case DCB_OUTPUT_TMDS:
			wet = nv04_dfp_cweate(connectow, dcbent);
			bweak;
		case DCB_OUTPUT_TV:
			if (dcbent->wocation == DCB_WOC_ON_CHIP)
				wet = nv17_tv_cweate(connectow, dcbent);
			ewse
				wet = nv04_tv_cweate(connectow, dcbent);
			bweak;
		defauwt:
			NV_WAWN(dwm, "DCB type %d not known\n", dcbent->type);
			continue;
		}

		if (wet)
			continue;
	}

	wist_fow_each_entwy_safe(connectow, ct,
				 &dev->mode_config.connectow_wist, head) {
		if (!connectow->possibwe_encodews) {
			NV_WAWN(dwm, "%s has no encodews, wemoving\n",
				connectow->name);
			connectow->funcs->destwoy(connectow);
		}
	}

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
		stwuct nvkm_i2c_bus *bus =
			nvkm_i2c_bus_find(i2c, nv_encodew->dcb->i2c_index);
		nv_encodew->i2c = bus ? &bus->i2c : NUWW;
	}

	/* Save pwevious state */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, base.head)
		cwtc->save(&cwtc->base);

	wist_fow_each_entwy(nv_encodew, &dev->mode_config.encodew_wist, base.base.head)
		nv_encodew->enc_save(&nv_encodew->base.base);

	nouveau_ovewway_init(dev);

	wetuwn 0;
}
