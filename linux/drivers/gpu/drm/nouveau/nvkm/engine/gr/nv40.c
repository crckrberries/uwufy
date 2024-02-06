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

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <subdev/fb.h>
#incwude <subdev/timew.h>
#incwude <engine/fifo.h>

u64
nv40_gw_units(stwuct nvkm_gw *gw)
{
	wetuwn nvkm_wd32(gw->engine.subdev.device, 0x1540);
}

/*******************************************************************************
 * Gwaphics object cwasses
 ******************************************************************************/

static int
nv40_gw_object_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		    int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	int wet = nvkm_gpuobj_new(object->engine->subdev.device, 20, awign,
				  fawse, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->ocwass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
#ifdef __BIG_ENDIAN
		nvkm_mo32(*pgpuobj, 0x08, 0x01000000, 0x01000000);
#endif
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

const stwuct nvkm_object_func
nv40_gw_object = {
	.bind = nv40_gw_object_bind,
};

/*******************************************************************************
 * PGWAPH context
 ******************************************************************************/

static int
nv40_gw_chan_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		  int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nv40_gw_chan *chan = nv40_gw_chan(object);
	stwuct nv40_gw *gw = chan->gw;
	int wet = nvkm_gpuobj_new(gw->base.engine.subdev.device, gw->size,
				  awign, twue, pawent, pgpuobj);
	if (wet == 0) {
		chan->inst = (*pgpuobj)->addw;
		nvkm_kmap(*pgpuobj);
		nv40_gwctx_fiww(gw->base.engine.subdev.device, *pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00000, chan->inst >> 4);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

static int
nv40_gw_chan_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nv40_gw_chan *chan = nv40_gw_chan(object);
	stwuct nv40_gw *gw = chan->gw;
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 inst = 0x01000000 | chan->inst >> 4;
	int wet = 0;

	nvkm_mask(device, 0x400720, 0x00000001, 0x00000000);

	if (nvkm_wd32(device, 0x40032c) == inst) {
		if (suspend) {
			nvkm_ww32(device, 0x400720, 0x00000000);
			nvkm_ww32(device, 0x400784, inst);
			nvkm_mask(device, 0x400310, 0x00000020, 0x00000020);
			nvkm_mask(device, 0x400304, 0x00000001, 0x00000001);
			if (nvkm_msec(device, 2000,
				if (!(nvkm_wd32(device, 0x400300) & 0x00000001))
					bweak;
			) < 0) {
				u32 insn = nvkm_wd32(device, 0x400308);
				nvkm_wawn(subdev, "ctxpwog timeout %08x\n", insn);
				wet = -EBUSY;
			}
		}

		nvkm_mask(device, 0x40032c, 0x01000000, 0x00000000);
	}

	if (nvkm_wd32(device, 0x400330) == inst)
		nvkm_mask(device, 0x400330, 0x01000000, 0x00000000);

	nvkm_mask(device, 0x400720, 0x00000001, 0x00000001);
	wetuwn wet;
}

static void *
nv40_gw_chan_dtow(stwuct nvkm_object *object)
{
	stwuct nv40_gw_chan *chan = nv40_gw_chan(object);
	unsigned wong fwags;
	spin_wock_iwqsave(&chan->gw->base.engine.wock, fwags);
	wist_dew(&chan->head);
	spin_unwock_iwqwestowe(&chan->gw->base.engine.wock, fwags);
	wetuwn chan;
}

static const stwuct nvkm_object_func
nv40_gw_chan = {
	.dtow = nv40_gw_chan_dtow,
	.fini = nv40_gw_chan_fini,
	.bind = nv40_gw_chan_bind,
};

int
nv40_gw_chan_new(stwuct nvkm_gw *base, stwuct nvkm_chan *fifoch,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object **pobject)
{
	stwuct nv40_gw *gw = nv40_gw(base);
	stwuct nv40_gw_chan *chan;
	unsigned wong fwags;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nv40_gw_chan, ocwass, &chan->object);
	chan->gw = gw;
	chan->fifo = fifoch;
	*pobject = &chan->object;

	spin_wock_iwqsave(&chan->gw->base.engine.wock, fwags);
	wist_add(&chan->head, &gw->chan);
	spin_unwock_iwqwestowe(&chan->gw->base.engine.wock, fwags);
	wetuwn 0;
}

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

static void
nv40_gw_tiwe(stwuct nvkm_gw *base, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nv40_gw *gw = nv40_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_fifo *fifo = device->fifo;
	unsigned wong fwags;

	nvkm_fifo_pause(fifo, &fwags);
	nv04_gw_idwe(&gw->base);

	switch (device->chipset) {
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
		nvkm_ww32(device, NV20_PGWAPH_TSIZE(i), tiwe->pitch);
		nvkm_ww32(device, NV20_PGWAPH_TWIMIT(i), tiwe->wimit);
		nvkm_ww32(device, NV20_PGWAPH_TIWE(i), tiwe->addw);
		nvkm_ww32(device, NV40_PGWAPH_TSIZE1(i), tiwe->pitch);
		nvkm_ww32(device, NV40_PGWAPH_TWIMIT1(i), tiwe->wimit);
		nvkm_ww32(device, NV40_PGWAPH_TIWE1(i), tiwe->addw);
		switch (device->chipset) {
		case 0x40:
		case 0x45:
			nvkm_ww32(device, NV20_PGWAPH_ZCOMP(i), tiwe->zcomp);
			nvkm_ww32(device, NV40_PGWAPH_ZCOMP1(i), tiwe->zcomp);
			bweak;
		case 0x41:
		case 0x42:
		case 0x43:
			nvkm_ww32(device, NV41_PGWAPH_ZCOMP0(i), tiwe->zcomp);
			nvkm_ww32(device, NV41_PGWAPH_ZCOMP1(i), tiwe->zcomp);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 0x47:
	case 0x49:
	case 0x4b:
		nvkm_ww32(device, NV47_PGWAPH_TSIZE(i), tiwe->pitch);
		nvkm_ww32(device, NV47_PGWAPH_TWIMIT(i), tiwe->wimit);
		nvkm_ww32(device, NV47_PGWAPH_TIWE(i), tiwe->addw);
		nvkm_ww32(device, NV40_PGWAPH_TSIZE1(i), tiwe->pitch);
		nvkm_ww32(device, NV40_PGWAPH_TWIMIT1(i), tiwe->wimit);
		nvkm_ww32(device, NV40_PGWAPH_TIWE1(i), tiwe->addw);
		nvkm_ww32(device, NV47_PGWAPH_ZCOMP0(i), tiwe->zcomp);
		nvkm_ww32(device, NV47_PGWAPH_ZCOMP1(i), tiwe->zcomp);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	nvkm_fifo_stawt(fifo, &fwags);
}

void
nv40_gw_intw(stwuct nvkm_gw *base)
{
	stwuct nv40_gw *gw = nv40_gw(base);
	stwuct nv40_gw_chan *temp, *chan = NUWW;
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, NV03_PGWAPH_INTW);
	u32 nsouwce = nvkm_wd32(device, NV03_PGWAPH_NSOUWCE);
	u32 nstatus = nvkm_wd32(device, NV03_PGWAPH_NSTATUS);
	u32 inst = nvkm_wd32(device, 0x40032c) & 0x000fffff;
	u32 addw = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW);
	u32 subc = (addw & 0x00070000) >> 16;
	u32 mthd = (addw & 0x00001ffc);
	u32 data = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_DATA);
	u32 cwass = nvkm_wd32(device, 0x400160 + subc * 4) & 0xffff;
	u32 show = stat;
	chaw msg[128], swc[128], sta[128];
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->base.engine.wock, fwags);
	wist_fow_each_entwy(temp, &gw->chan, head) {
		if (temp->inst >> 4 == inst) {
			chan = temp;
			wist_dew(&chan->head);
			wist_add(&chan->head, &gw->chan);
			bweak;
		}
	}

	if (stat & NV_PGWAPH_INTW_EWWOW) {
		if (nsouwce & NV03_PGWAPH_NSOUWCE_DMA_VTX_PWOTECTION) {
			nvkm_mask(device, 0x402000, 0, 0);
		}
	}

	nvkm_ww32(device, NV03_PGWAPH_INTW, stat);
	nvkm_ww32(device, NV04_PGWAPH_FIFO, 0x00000001);

	if (show) {
		nvkm_snpwintbf(msg, sizeof(msg), nv10_gw_intw_name, show);
		nvkm_snpwintbf(swc, sizeof(swc), nv04_gw_nsouwce, nsouwce);
		nvkm_snpwintbf(sta, sizeof(sta), nv10_gw_nstatus, nstatus);
		nvkm_ewwow(subdev, "intw %08x [%s] nsouwce %08x [%s] "
				   "nstatus %08x [%s] ch %d [%08x %s] subc %d "
				   "cwass %04x mthd %04x data %08x\n",
			   show, msg, nsouwce, swc, nstatus, sta,
			   chan ? chan->fifo->id : -1, inst << 4,
			   chan ? chan->fifo->name : "unknown",
			   subc, cwass, mthd, data);
	}

	spin_unwock_iwqwestowe(&gw->base.engine.wock, fwags);
}

int
nv40_gw_init(stwuct nvkm_gw *base)
{
	stwuct nv40_gw *gw = nv40_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int wet, i, j;
	u32 vwamsz;

	/* genewate and upwoad context pwogwam */
	wet = nv40_gwctx_init(device, &gw->size);
	if (wet)
		wetuwn wet;

	/* No context pwesent cuwwentwy */
	nvkm_ww32(device, NV40_PGWAPH_CTXCTW_CUW, 0x00000000);

	nvkm_ww32(device, NV03_PGWAPH_INTW   , 0xFFFFFFFF);
	nvkm_ww32(device, NV40_PGWAPH_INTW_EN, 0xFFFFFFFF);

	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0x00000000);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_1, 0x401287c0);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_3, 0xe0de8055);
	nvkm_ww32(device, NV10_PGWAPH_DEBUG_4, 0x00008000);
	nvkm_ww32(device, NV04_PGWAPH_WIMIT_VIOW_PIX, 0x00be3c5f);

	nvkm_ww32(device, NV10_PGWAPH_CTX_CONTWOW, 0x10010100);
	nvkm_ww32(device, NV10_PGWAPH_STATE      , 0xFFFFFFFF);

	j = nvkm_wd32(device, 0x1540) & 0xff;
	if (j) {
		fow (i = 0; !(j & 1); j >>= 1, i++)
			;
		nvkm_ww32(device, 0x405000, i);
	}

	if (device->chipset == 0x40) {
		nvkm_ww32(device, 0x4009b0, 0x83280fff);
		nvkm_ww32(device, 0x4009b4, 0x000000a0);
	} ewse {
		nvkm_ww32(device, 0x400820, 0x83280eff);
		nvkm_ww32(device, 0x400824, 0x000000a0);
	}

	switch (device->chipset) {
	case 0x40:
	case 0x45:
		nvkm_ww32(device, 0x4009b8, 0x0078e366);
		nvkm_ww32(device, 0x4009bc, 0x0000014c);
		bweak;
	case 0x41:
	case 0x42: /* pciid awso 0x00Cx */
	/* case 0x0120: XXX (pciid) */
		nvkm_ww32(device, 0x400828, 0x007596ff);
		nvkm_ww32(device, 0x40082c, 0x00000108);
		bweak;
	case 0x43:
		nvkm_ww32(device, 0x400828, 0x0072cb77);
		nvkm_ww32(device, 0x40082c, 0x00000108);
		bweak;
	case 0x44:
	case 0x46: /* G72 */
	case 0x4a:
	case 0x4c: /* G7x-based C51 */
	case 0x4e:
		nvkm_ww32(device, 0x400860, 0);
		nvkm_ww32(device, 0x400864, 0);
		bweak;
	case 0x47: /* G70 */
	case 0x49: /* G71 */
	case 0x4b: /* G73 */
		nvkm_ww32(device, 0x400828, 0x07830610);
		nvkm_ww32(device, 0x40082c, 0x0000016A);
		bweak;
	defauwt:
		bweak;
	}

	nvkm_ww32(device, 0x400b38, 0x2ffff800);
	nvkm_ww32(device, 0x400b3c, 0x00006000);

	/* Tiwing wewated stuff. */
	switch (device->chipset) {
	case 0x44:
	case 0x4a:
		nvkm_ww32(device, 0x400bc4, 0x1003d888);
		nvkm_ww32(device, 0x400bbc, 0xb7a7b500);
		bweak;
	case 0x46:
		nvkm_ww32(device, 0x400bc4, 0x0000e024);
		nvkm_ww32(device, 0x400bbc, 0xb7a7b520);
		bweak;
	case 0x4c:
	case 0x4e:
	case 0x67:
		nvkm_ww32(device, 0x400bc4, 0x1003d888);
		nvkm_ww32(device, 0x400bbc, 0xb7a7b540);
		bweak;
	defauwt:
		bweak;
	}

	/* begin WAM config */
	vwamsz = device->func->wesouwce_size(device, 1) - 1;
	switch (device->chipset) {
	case 0x40:
		nvkm_ww32(device, 0x4009A4, nvkm_wd32(device, 0x100200));
		nvkm_ww32(device, 0x4009A8, nvkm_wd32(device, 0x100204));
		nvkm_ww32(device, 0x4069A4, nvkm_wd32(device, 0x100200));
		nvkm_ww32(device, 0x4069A8, nvkm_wd32(device, 0x100204));
		nvkm_ww32(device, 0x400820, 0);
		nvkm_ww32(device, 0x400824, 0);
		nvkm_ww32(device, 0x400864, vwamsz);
		nvkm_ww32(device, 0x400868, vwamsz);
		bweak;
	defauwt:
		switch (device->chipset) {
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x45:
		case 0x4e:
		case 0x44:
		case 0x4a:
			nvkm_ww32(device, 0x4009F0, nvkm_wd32(device, 0x100200));
			nvkm_ww32(device, 0x4009F4, nvkm_wd32(device, 0x100204));
			bweak;
		defauwt:
			nvkm_ww32(device, 0x400DF0, nvkm_wd32(device, 0x100200));
			nvkm_ww32(device, 0x400DF4, nvkm_wd32(device, 0x100204));
			bweak;
		}
		nvkm_ww32(device, 0x4069F0, nvkm_wd32(device, 0x100200));
		nvkm_ww32(device, 0x4069F4, nvkm_wd32(device, 0x100204));
		nvkm_ww32(device, 0x400840, 0);
		nvkm_ww32(device, 0x400844, 0);
		nvkm_ww32(device, 0x4008A0, vwamsz);
		nvkm_ww32(device, 0x4008A4, vwamsz);
		bweak;
	}

	wetuwn 0;
}

int
nv40_gw_new_(const stwuct nvkm_gw_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	stwuct nv40_gw *gw;

	if (!(gw = kzawwoc(sizeof(*gw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pgw = &gw->base;
	INIT_WIST_HEAD(&gw->chan);

	wetuwn nvkm_gw_ctow(func, device, type, inst, twue, &gw->base);
}

static const stwuct nvkm_gw_func
nv40_gw = {
	.init = nv40_gw_init,
	.intw = nv40_gw_intw,
	.tiwe = nv40_gw_tiwe,
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
		{ -1, -1, 0x4097, &nv40_gw_object }, /* cuwie */
		{}
	}
};

int
nv40_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv40_gw_new_(&nv40_gw, device, type, inst, pgw);
}
