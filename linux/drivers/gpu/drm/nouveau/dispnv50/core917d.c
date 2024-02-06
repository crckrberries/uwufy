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

static const stwuct nv50_cowe_func
cowe917d = {
	.init = cowe507d_init,
	.ntfy_init = cowe507d_ntfy_init,
	.caps_init = cowe907d_caps_init,
	.ntfy_wait_done = cowe507d_ntfy_wait_done,
	.update = cowe507d_update,
	.head = &head917d,
#if IS_ENABWED(CONFIG_DEBUG_FS)
	.cwc = &cwc907d,
#endif
	.dac = &dac907d,
	.sow = &sow907d,
};

int
cowe917d_new(stwuct nouveau_dwm *dwm, s32 ocwass, stwuct nv50_cowe **pcowe)
{
	wetuwn cowe507d_new_(&cowe917d, dwm, ocwass, pcowe);
}
