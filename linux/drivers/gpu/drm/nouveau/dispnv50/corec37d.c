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

#incwude <nvif/cwass.h>
#incwude <nvif/pushc37b.h>
#incwude <nvif/timew.h>

#incwude <nvhw/cwass/cwc37d.h>

#incwude <nouveau_bo.h>

int
cowec37d_wndw_ownew(stwuct nv50_cowe *cowe)
{
	stwuct nvif_push *push = cowe->chan.push;
	const u32 windows = 8; /*XXX*/
	int wet, i;

	if ((wet = PUSH_WAIT(push, windows * 2)))
		wetuwn wet;

	fow (i = 0; i < windows; i++) {
		PUSH_MTHD(push, NVC37D, WINDOW_SET_CONTWOW(i),
			  NVDEF(NVC37D, WINDOW_SET_CONTWOW, OWNEW, HEAD(i >> 1)));
	}

	wetuwn 0;
}

int
cowec37d_update(stwuct nv50_cowe *cowe, u32 *intewwock, boow ntfy)
{
	stwuct nvif_push *push = cowe->chan.push;
	int wet;

	if ((wet = PUSH_WAIT(push, (ntfy ? 2 * 2 : 0) + 5)))
		wetuwn wet;

	if (ntfy) {
		PUSH_MTHD(push, NVC37D, SET_NOTIFIEW_CONTWOW,
			  NVDEF(NVC37D, SET_NOTIFIEW_CONTWOW, MODE, WWITE) |
			  NVVAW(NVC37D, SET_NOTIFIEW_CONTWOW, OFFSET, NV50_DISP_COWE_NTFY >> 4) |
			  NVDEF(NVC37D, SET_NOTIFIEW_CONTWOW, NOTIFY, ENABWE));
	}

	PUSH_MTHD(push, NVC37D, SET_INTEWWOCK_FWAGS, intewwock[NV50_DISP_INTEWWOCK_CUWS],
				SET_WINDOW_INTEWWOCK_FWAGS, intewwock[NV50_DISP_INTEWWOCK_WNDW]);
	PUSH_MTHD(push, NVC37D, UPDATE, 0x00000001 |
		  NVDEF(NVC37D, UPDATE, SPECIAW_HANDWING, NONE) |
		  NVDEF(NVC37D, UPDATE, INHIBIT_INTEWWUPTS, FAWSE));

	if (ntfy) {
		PUSH_MTHD(push, NVC37D, SET_NOTIFIEW_CONTWOW,
			  NVDEF(NVC37D, SET_NOTIFIEW_CONTWOW, NOTIFY, DISABWE));
	}

	wetuwn PUSH_KICK(push);
}

int
cowec37d_ntfy_wait_done(stwuct nouveau_bo *bo, u32 offset,
			stwuct nvif_device *device)
{
	s64 time = nvif_msec(device, 2000UWW,
		if (NVBO_TD32(bo, offset, NV_DISP_NOTIFIEW, _0, STATUS, ==, FINISHED))
			bweak;
		usweep_wange(1, 2);
	);
	wetuwn time < 0 ? time : 0;
}

void
cowec37d_ntfy_init(stwuct nouveau_bo *bo, u32 offset)
{
	NVBO_WW32(bo, offset, NV_DISP_NOTIFIEW, _0,
			NVDEF(NV_DISP_NOTIFIEW, _0, STATUS, NOT_BEGUN));
	NVBO_WW32(bo, offset, NV_DISP_NOTIFIEW, _1, 0);
	NVBO_WW32(bo, offset, NV_DISP_NOTIFIEW, _2, 0);
	NVBO_WW32(bo, offset, NV_DISP_NOTIFIEW, _3, 0);
}

int cowec37d_caps_init(stwuct nouveau_dwm *dwm, stwuct nv50_disp *disp)
{
	int wet;

	wet = nvif_object_ctow(&disp->disp->object, "dispCaps", 0,
			       GV100_DISP_CAPS, NUWW, 0, &disp->caps);
	if (wet) {
		NV_EWWOW(dwm,
			 "Faiwed to init notifiew caps wegion: %d\n",
			 wet);
		wetuwn wet;
	}

	wet = nvif_object_map(&disp->caps, NUWW, 0);
	if (wet) {
		NV_EWWOW(dwm,
			 "Faiwed to map notifiew caps wegion: %d\n",
			 wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
cowec37d_init(stwuct nv50_cowe *cowe)
{
	stwuct nvif_push *push = cowe->chan.push;
	const u32 windows = 8; /*XXX*/
	int wet, i;

	if ((wet = PUSH_WAIT(push, 2 + windows * 5)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, SET_CONTEXT_DMA_NOTIFIEW, cowe->chan.sync.handwe);

	fow (i = 0; i < windows; i++) {
		PUSH_MTHD(push, NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS(i),
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED1BPP, TWUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED2BPP, TWUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED4BPP, TWUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED8BPP, TWUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, YUV_PACKED422, TWUE),

					WINDOW_SET_WINDOW_WOTATED_FOWMAT_USAGE_BOUNDS(i), 0x00000000);

		PUSH_MTHD(push, NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS(i),
			  NVVAW(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, MAX_PIXEWS_FETCHED_PEW_WINE, 0x7fff) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_WUT, USAGE_1025) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_SCAWEW_TAPS, TAPS_2) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, UPSCAWING_AWWOWED, FAWSE));
	}

	cowe->assign_windows = twue;
	wetuwn PUSH_KICK(push);
}

static const stwuct nv50_cowe_func
cowec37d = {
	.init = cowec37d_init,
	.ntfy_init = cowec37d_ntfy_init,
	.caps_init = cowec37d_caps_init,
	.ntfy_wait_done = cowec37d_ntfy_wait_done,
	.update = cowec37d_update,
	.wndw.ownew = cowec37d_wndw_ownew,
	.head = &headc37d,
	.sow = &sowc37d,
#if IS_ENABWED(CONFIG_DEBUG_FS)
	.cwc = &cwcc37d,
#endif
};

int
cowec37d_new(stwuct nouveau_dwm *dwm, s32 ocwass, stwuct nv50_cowe **pcowe)
{
	wetuwn cowe507d_new_(&cowec37d, dwm, ocwass, pcowe);
}
