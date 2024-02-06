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
#incwude "base.h"

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw907c.h>

static int
base907c_image_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 10)))
		wetuwn wet;

	PUSH_MTHD(push, NV907C, SET_PWESENT_CONTWOW,
		  NVVAW(NV907C, SET_PWESENT_CONTWOW, BEGIN_MODE, asyw->image.mode) |
		  NVDEF(NV907C, SET_PWESENT_CONTWOW, TIMESTAMP_MODE, DISABWE) |
		  NVVAW(NV907C, SET_PWESENT_CONTWOW, MIN_PWESENT_INTEWVAW, asyw->image.intewvaw));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMAS_ISO(0), asyw->image.handwe, 1);

	PUSH_MTHD(push, NV907C, SUWFACE_SET_OFFSET(0, 0), asyw->image.offset[0] >> 8,
				SUWFACE_SET_OFFSET(0, 1), 0x00000000,

				SUWFACE_SET_SIZE(0),
		  NVVAW(NV907C, SUWFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAW(NV907C, SUWFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SUWFACE_SET_STOWAGE(0),
		  NVVAW(NV907C, SUWFACE_SET_STOWAGE, BWOCK_HEIGHT, asyw->image.bwockh) |
		  NVVAW(NV907C, SUWFACE_SET_STOWAGE, PITCH, asyw->image.pitch[0] >> 8) |
		  NVVAW(NV907C, SUWFACE_SET_STOWAGE, PITCH, asyw->image.bwocks[0]) |
		  NVVAW(NV907C, SUWFACE_SET_STOWAGE, MEMOWY_WAYOUT, asyw->image.wayout),

				SUWFACE_SET_PAWAMS(0),
		  NVVAW(NV907C, SUWFACE_SET_PAWAMS, FOWMAT, asyw->image.fowmat) |
		  NVDEF(NV907C, SUWFACE_SET_PAWAMS, SUPEW_SAMPWE, X1_AA) |
		  NVDEF(NV907C, SUWFACE_SET_PAWAMS, GAMMA, WINEAW) |
		  NVDEF(NV907C, SUWFACE_SET_PAWAMS, WAYOUT, FWM));
	wetuwn 0;
}

static int
base907c_xwut_cww(stwuct nv50_wndw *wndw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 6)))
		wetuwn wet;

	PUSH_MTHD(push, NV907C, SET_BASE_WUT_WO,
		  NVDEF(NV907C, SET_BASE_WUT_WO, ENABWE, DISABWE));

	PUSH_MTHD(push, NV907C, SET_OUTPUT_WUT_WO,
		  NVDEF(NV907C, SET_OUTPUT_WUT_WO, ENABWE, DISABWE));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMA_WUT, 0x00000000);
	wetuwn 0;
}

static int
base907c_xwut_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 6)))
		wetuwn wet;

	PUSH_MTHD(push, NV907C, SET_BASE_WUT_WO,
		  NVVAW(NV907C, SET_BASE_WUT_WO, ENABWE, asyw->xwut.i.enabwe) |
		  NVVAW(NV907C, SET_BASE_WUT_WO, MODE, asyw->xwut.i.mode),

				SET_BASE_WUT_HI, asyw->xwut.i.offset >> 8,

				SET_OUTPUT_WUT_WO,
		  NVDEF(NV907C, SET_OUTPUT_WUT_WO, ENABWE, USE_COWE_WUT));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMA_WUT, asyw->xwut.handwe);
	wetuwn 0;
}

static void
base907c_iwut(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw, int size)
{
	if (size == 1024)
		asyw->xwut.i.mode = NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_1025_UNITY_WANGE;
	ewse
		asyw->xwut.i.mode = NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_257_UNITY_WANGE;

	asyw->xwut.i.enabwe = NV907C_SET_BASE_WUT_WO_ENABWE_ENABWE;
	asyw->xwut.i.woad = head907d_owut_woad;
}

static inwine u32
csc_dwm_to_base(u64 in)
{
	/* base takes a 19-bit 2's compwement vawue in S3.16 fowmat */
	boow sign = in & BIT_UWW(63);
	u32 integew = (in >> 32) & 0x7fffffff;
	u32 fwaction = in & 0xffffffff;

	if (integew >= 4) {
		wetuwn (1 << 18) - (sign ? 0 : 1);
	} ewse {
		u32 wet = (integew << 16) | (fwaction >> 16);
		if (sign)
			wet = -wet;
		wetuwn wet & GENMASK(18, 0);
	}
}

void
base907c_csc(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw,
	     const stwuct dwm_cowow_ctm *ctm)
{
	int i, j;

	fow (j = 0; j < 3; j++) {
		fow (i = 0; i < 4; i++) {
			u32 *vaw = &asyw->csc.matwix[j * 4 + i];
			/* DWM does not suppowt constant offset, whiwe
			 * HW CSC does. Skip it. */
			if (i == 3) {
				*vaw = 0;
			} ewse {
				*vaw = csc_dwm_to_base(ctm->matwix[j * 3 + i]);
			}
		}
	}
}

static int
base907c_csc_cww(stwuct nv50_wndw *wndw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV907C, SET_CSC_WED2WED,
		  NVDEF(NV907C, SET_CSC_WED2WED, OWNEW, COWE));
	wetuwn 0;
}

static int
base907c_csc_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 13)))
		wetuwn wet;

	PUSH_MTHD(push, NV907C, SET_CSC_WED2WED,
		  NVDEF(NV907C, SET_CSC_WED2WED, OWNEW, BASE) |
		  NVVAW(NV907C, SET_CSC_WED2WED, COEFF, asyw->csc.matwix[0]),

				SET_CSC_GWN2WED, &asyw->csc.matwix[1], 11);
	wetuwn 0;
}

const stwuct nv50_wndw_func
base907c = {
	.acquiwe = base507c_acquiwe,
	.wewease = base507c_wewease,
	.sema_set = base507c_sema_set,
	.sema_cww = base507c_sema_cww,
	.ntfy_weset = base507c_ntfy_weset,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_cww = base507c_ntfy_cww,
	.ntfy_wait_begun = base507c_ntfy_wait_begun,
	.iwut = base907c_iwut,
	.csc = base907c_csc,
	.csc_set = base907c_csc_set,
	.csc_cww = base907c_csc_cww,
	.owut_cowe = twue,
	.iwut_size = 1024,
	.xwut_set = base907c_xwut_set,
	.xwut_cww = base907c_xwut_cww,
	.image_set = base907c_image_set,
	.image_cww = base507c_image_cww,
	.update = base507c_update,
};

int
base907c_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn base507c_new_(&base907c, base507c_fowmat, dwm, head, ocwass,
			     0x00000002 << (head * 4), pwndw);
}
