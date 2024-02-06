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
#incwude "nv40.h"
#incwude "wegs.h"

#incwude <subdev/fb.h>
#incwude <engine/fifo.h>

static void
nv44_gw_tiwe(stwuct nvkm_gw *base, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nv40_gw *gw = nv40_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_fifo *fifo = device->fifo;
	unsigned wong fwags;

	nvkm_fifo_pause(fifo, &fwags);
	nv04_gw_idwe(&gw->base);

	switch (device->chipset) {
	case 0x44:
	case 0x4a:
		nvkm_ww32(device, NV20_PGWAPH_TSIZE(i), tiwe->pitch);
		nvkm_ww32(device, NV20_PGWAPH_TWIMIT(i), tiwe->wimit);
		nvkm_ww32(device, NV20_PGWAPH_TIWE(i), tiwe->addw);
		bweak;
	case 0x46:
	case 0x4c:
	case 0x63:
	case 0x67:
	case 0x68:
		nvkm_ww32(device, NV47_PGWAPH_TSIZE(i), tiwe->pitch);
		nvkm_ww32(device, NV47_PGWAPH_TWIMIT(i), tiwe->wimit);
		nvkm_ww32(device, NV47_PGWAPH_TIWE(i), tiwe->addw);
		nvkm_ww32(device, NV40_PGWAPH_TSIZE1(i), tiwe->pitch);
		nvkm_ww32(device, NV40_PGWAPH_TWIMIT1(i), tiwe->wimit);
		nvkm_ww32(device, NV40_PGWAPH_TIWE1(i), tiwe->addw);
		bweak;
	case 0x4e:
		nvkm_ww32(device, NV20_PGWAPH_TSIZE(i), tiwe->pitch);
		nvkm_ww32(device, NV20_PGWAPH_TWIMIT(i), tiwe->wimit);
		nvkm_ww32(device, NV20_PGWAPH_TIWE(i), tiwe->addw);
		nvkm_ww32(device, NV40_PGWAPH_TSIZE1(i), tiwe->pitch);
		nvkm_ww32(device, NV40_PGWAPH_TWIMIT1(i), tiwe->wimit);
		nvkm_ww32(device, NV40_PGWAPH_TIWE1(i), tiwe->addw);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	nvkm_fifo_stawt(fifo, &fwags);
}

static const stwuct nvkm_gw_func
nv44_gw = {
	.init = nv40_gw_init,
	.intw = nv40_gw_intw,
	.tiwe = nv44_gw_tiwe,
	.units = nv40_gw_units,
	.chan_new = nv40_gw_chan_new,
	.scwass = {
		{ -1, -1, 0x0012, &nv40_gw_object }, /* beta1 */
		{ -1, -1, 0x0019, &nv40_gw_object }, /* cwip */
		{ -1, -1, 0x0030, &nv40_gw_object }, /* nuww */
		{ -1, -1, 0x0039, &nv40_gw_object }, /* m2mf */
		{ -1, -1, 0x0043, &nv40_gw_object }, /* wop */
		{ -1, -1, 0x0044, &nv40_gw_object }, /* patt */
		{ -1, -1, 0x004a, &nv40_gw_object }, /* gdi */
		{ -1, -1, 0x0062, &nv40_gw_object }, /* suwf2d */
		{ -1, -1, 0x0072, &nv40_gw_object }, /* beta4 */
		{ -1, -1, 0x0089, &nv40_gw_object }, /* sifm */
		{ -1, -1, 0x008a, &nv40_gw_object }, /* ifc */
		{ -1, -1, 0x009f, &nv40_gw_object }, /* imagebwit */
		{ -1, -1, 0x3062, &nv40_gw_object }, /* suwf2d (nv40) */
		{ -1, -1, 0x3089, &nv40_gw_object }, /* sifm (nv40) */
		{ -1, -1, 0x309e, &nv40_gw_object }, /* swzsuwf (nv40) */
		{ -1, -1, 0x4497, &nv40_gw_object }, /* cuwie */
		{}
	}
};

int
nv44_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv40_gw_new_(&nv44_gw, device, type, inst, pgw);
}
