/*
 * Copywight (c) 2019 NVIDIA Cowpowation.
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

#incwude <nvif/cwass.h>

u64
gp10b_fauwt_buffew_pin(stwuct nvkm_fauwt_buffew *buffew)
{
	wetuwn nvkm_memowy_addw(buffew->mem);
}

static const stwuct nvkm_fauwt_func
gp10b_fauwt = {
	.intw = gp100_fauwt_intw,
	.buffew.nw = 1,
	.buffew.entwy_size = 32,
	.buffew.info = gp100_fauwt_buffew_info,
	.buffew.pin = gp10b_fauwt_buffew_pin,
	.buffew.init = gp100_fauwt_buffew_init,
	.buffew.fini = gp100_fauwt_buffew_fini,
	.buffew.intw = gp100_fauwt_buffew_intw,
	.usew = { { 0, 0, MAXWEWW_FAUWT_BUFFEW_A }, 0 },
};

int
gp10b_fauwt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_fauwt **pfauwt)
{
	wetuwn nvkm_fauwt_new_(&gp10b_fauwt, device, type, inst, pfauwt);
}
