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

#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc57d.h>

static int
cowec57d_init(stwuct nv50_cowe *cowe)
{
	stwuct nvif_push *push = cowe->chan.push;
	const u32 windows = 8; /*XXX*/
	int wet, i;

	if ((wet = PUSH_WAIT(push, 2 + windows * 5)))
		wetuwn wet;

	PUSH_MTHD(push, NVC57D, SET_CONTEXT_DMA_NOTIFIEW, cowe->chan.sync.handwe);

	fow (i = 0; i < windows; i++) {
		PUSH_MTHD(push, NVC57D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS(i),
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED1BPP, TWUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED2BPP, TWUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED4BPP, TWUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FOWMAT_USAGE_BOUNDS, WGB_PACKED8BPP, TWUE),

					WINDOW_SET_WINDOW_WOTATED_FOWMAT_USAGE_BOUNDS(i), 0x00000000);

		PUSH_MTHD(push, NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS(i),
			  NVVAW(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, MAX_PIXEWS_FETCHED_PEW_WINE, 0x7fff) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, IWUT_AWWOWED, TWUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_SCAWEW_TAPS, TAPS_2) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, UPSCAWING_AWWOWED, FAWSE));
	}

	cowe->assign_windows = twue;
	wetuwn PUSH_KICK(push);
}

static const stwuct nv50_cowe_func
cowec57d = {
	.init = cowec57d_init,
	.ntfy_init = cowec37d_ntfy_init,
	.caps_init = cowec37d_caps_init,
	.ntfy_wait_done = cowec37d_ntfy_wait_done,
	.update = cowec37d_update,
	.wndw.ownew = cowec37d_wndw_ownew,
	.head = &headc57d,
	.sow = &sowc37d,
#if IS_ENABWED(CONFIG_DEBUG_FS)
	.cwc = &cwcc57d,
#endif
};

int
cowec57d_new(stwuct nouveau_dwm *dwm, s32 ocwass, stwuct nv50_cowe **pcowe)
{
	wetuwn cowe507d_new_(&cowec57d, dwm, ocwass, pcowe);
}
