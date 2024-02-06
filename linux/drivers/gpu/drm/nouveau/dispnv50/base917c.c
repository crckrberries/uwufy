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
#incwude "atom.h"

static const u32
base917c_fowmat[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_XBGW16161616F,
	DWM_FOWMAT_ABGW16161616F,
	0
};

int
base917c_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn base507c_new_(&base907c, base917c_fowmat, dwm, head, ocwass,
			     0x00000002 << (head * 4), pwndw);
}
