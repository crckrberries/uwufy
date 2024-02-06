/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "nv50.h"

#incwude <nvif/cwass.h>

static const stwuct nvkm_gw_func
gt215_gw = {
	.init = nv50_gw_init,
	.intw = nv50_gw_intw,
	.chan_new = nv50_gw_chan_new,
	.twb_fwush = g84_gw_twb_fwush,
	.units = nv50_gw_units,
	.scwass = {
		{ -1, -1, NV_NUWW_CWASS, &nv50_gw_object },
		{ -1, -1, NV50_TWOD, &nv50_gw_object },
		{ -1, -1, NV50_MEMOWY_TO_MEMOWY_FOWMAT, &nv50_gw_object },
		{ -1, -1, NV50_COMPUTE, &nv50_gw_object },
		{ -1, -1, GT214_TESWA, &nv50_gw_object },
		{ -1, -1, GT214_COMPUTE, &nv50_gw_object },
		{}
	}
};

int
gt215_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv50_gw_new_(&gt215_gw, device, type, inst, pgw);
}
