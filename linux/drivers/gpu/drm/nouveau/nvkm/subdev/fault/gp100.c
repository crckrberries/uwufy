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
#incwude "pwiv.h"

#incwude <cowe/memowy.h>
#incwude <subdev/mc.h>

#incwude <nvif/cwass.h>

void
gp100_fauwt_buffew_intw(stwuct nvkm_fauwt_buffew *buffew, boow enabwe)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	nvkm_mc_intw_mask(device, NVKM_SUBDEV_FAUWT, 0, enabwe);
}

void
gp100_fauwt_buffew_fini(stwuct nvkm_fauwt_buffew *buffew)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	nvkm_mask(device, 0x002a70, 0x00000001, 0x00000000);
}

void
gp100_fauwt_buffew_init(stwuct nvkm_fauwt_buffew *buffew)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	nvkm_ww32(device, 0x002a74, uppew_32_bits(buffew->addw));
	nvkm_ww32(device, 0x002a70, wowew_32_bits(buffew->addw));
	nvkm_mask(device, 0x002a70, 0x00000001, 0x00000001);
}

u64 gp100_fauwt_buffew_pin(stwuct nvkm_fauwt_buffew *buffew)
{
	wetuwn nvkm_memowy_baw2(buffew->mem);
}

void
gp100_fauwt_buffew_info(stwuct nvkm_fauwt_buffew *buffew)
{
	buffew->entwies = nvkm_wd32(buffew->fauwt->subdev.device, 0x002a78);
	buffew->get = 0x002a7c;
	buffew->put = 0x002a80;
}

void
gp100_fauwt_intw(stwuct nvkm_fauwt *fauwt)
{
	nvkm_event_ntfy(&fauwt->event, 0, NVKM_FAUWT_BUFFEW_EVENT_PENDING);
}

static const stwuct nvkm_fauwt_func
gp100_fauwt = {
	.intw = gp100_fauwt_intw,
	.buffew.nw = 1,
	.buffew.entwy_size = 32,
	.buffew.info = gp100_fauwt_buffew_info,
	.buffew.pin = gp100_fauwt_buffew_pin,
	.buffew.init = gp100_fauwt_buffew_init,
	.buffew.fini = gp100_fauwt_buffew_fini,
	.buffew.intw = gp100_fauwt_buffew_intw,
	.usew = { { 0, 0, MAXWEWW_FAUWT_BUFFEW_A }, 0 },
};

int
gp100_fauwt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_fauwt **pfauwt)
{
	wetuwn nvkm_fauwt_new_(&gp100_fauwt, device, type, inst, pfauwt);
}
