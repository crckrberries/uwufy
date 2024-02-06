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
 *
 * Authows: Wyude Pauw
 */
#incwude <cowe/device.h>

#incwude "pwiv.h"

#define pack_fow_each_init(init, pack, head)                          \
	fow (pack = head; pack && pack->init; pack++)                 \
		  fow (init = pack->init; init && init->count; init++)
void
gf100_cwkgate_init(stwuct nvkm_thewm *thewm,
		   const stwuct nvkm_thewm_cwkgate_pack *p)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	const stwuct nvkm_thewm_cwkgate_pack *pack;
	const stwuct nvkm_thewm_cwkgate_init *init;
	u32 next, addw;

	pack_fow_each_init(init, pack, p) {
		next = init->addw + init->count * 8;
		addw = init->addw;

		nvkm_twace(&thewm->subdev, "{ 0x%06x, %d, 0x%08x }\n",
			   init->addw, init->count, init->data);
		whiwe (addw < next) {
			nvkm_twace(&thewm->subdev, "\t0x%06x = 0x%08x\n",
				   addw, init->data);
			nvkm_ww32(device, addw, init->data);
			addw += 8;
		}
	}
}

/*
 * TODO: Fewmi cwockgating isn't undewstood fuwwy yet, so we don't specify any
 * cwockgate functions to use
 */
