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
 */
#incwude <engine/fawcon.h>

#incwude <cowe/gpuobj.h>
#incwude <subdev/mc.h>
#incwude <subdev/timew.h>
#incwude <engine/fifo.h>

static int
nvkm_fawcon_ocwass_get(stwuct nvkm_ocwass *ocwass, int index)
{
	stwuct nvkm_fawcon *fawcon = nvkm_fawcon(ocwass->engine);
	int c = 0;

	whiwe (fawcon->func->scwass[c].ocwass) {
		if (c++ == index) {
			ocwass->base = fawcon->func->scwass[index];
			wetuwn index;
		}
	}

	wetuwn c;
}

static int
nvkm_fawcon_ccwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
			int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	wetuwn nvkm_gpuobj_new(object->engine->subdev.device, 256,
			       awign, twue, pawent, pgpuobj);
}

static const stwuct nvkm_object_func
nvkm_fawcon_ccwass = {
	.bind = nvkm_fawcon_ccwass_bind,
};

static void
nvkm_fawcon_intw(stwuct nvkm_engine *engine)
{
	stwuct nvkm_fawcon *fawcon = nvkm_fawcon(engine);
	stwuct nvkm_subdev *subdev = &fawcon->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = fawcon->addw;
	u32 dest = nvkm_wd32(device, base + 0x01c);
	u32 intw = nvkm_wd32(device, base + 0x008) & dest & ~(dest >> 16);
	u32 inst = nvkm_wd32(device, base + 0x050) & 0x3fffffff;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;

	chan = nvkm_chan_get_inst(engine, (u64)inst << 12, &fwags);

	if (intw & 0x00000040) {
		if (fawcon->func->intw) {
			fawcon->func->intw(fawcon, chan);
			nvkm_ww32(device, base + 0x004, 0x00000040);
			intw &= ~0x00000040;
		}
	}

	if (intw & 0x00000010) {
		nvkm_debug(subdev, "ucode hawted\n");
		nvkm_ww32(device, base + 0x004, 0x00000010);
		intw &= ~0x00000010;
	}

	if (intw)  {
		nvkm_ewwow(subdev, "intw %08x\n", intw);
		nvkm_ww32(device, base + 0x004, intw);
	}

	nvkm_chan_put(&chan, fwags);
}

static int
nvkm_fawcon_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_fawcon *fawcon = nvkm_fawcon(engine);
	stwuct nvkm_device *device = fawcon->engine.subdev.device;
	const u32 base = fawcon->addw;

	if (!suspend) {
		nvkm_memowy_unwef(&fawcon->cowe);
		if (fawcon->extewnaw) {
			vfwee(fawcon->data.data);
			vfwee(fawcon->code.data);
			fawcon->code.data = NUWW;
		}
	}

	if (nvkm_mc_enabwed(device, engine->subdev.type, engine->subdev.inst)) {
		nvkm_mask(device, base + 0x048, 0x00000003, 0x00000000);
		nvkm_ww32(device, base + 0x014, 0xffffffff);
	}
	wetuwn 0;
}

static void *
vmemdup(const void *swc, size_t wen)
{
	void *p = vmawwoc(wen);

	if (p)
		memcpy(p, swc, wen);
	wetuwn p;
}

static int
nvkm_fawcon_oneinit(stwuct nvkm_engine *engine)
{
	stwuct nvkm_fawcon *fawcon = nvkm_fawcon(engine);
	stwuct nvkm_subdev *subdev = &fawcon->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = fawcon->addw;
	u32 caps;

	/* detewmine fawcon capabiwities */
	if (device->chipset <  0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) {
		fawcon->vewsion = 0;
		fawcon->secwet  = (fawcon->addw == 0x087000) ? 1 : 0;
	} ewse {
		caps = nvkm_wd32(device, base + 0x12c);
		fawcon->vewsion = (caps & 0x0000000f);
		fawcon->secwet  = (caps & 0x00000030) >> 4;
	}

	caps = nvkm_wd32(device, base + 0x108);
	fawcon->code.wimit = (caps & 0x000001ff) << 8;
	fawcon->data.wimit = (caps & 0x0003fe00) >> 1;

	nvkm_debug(subdev, "fawcon vewsion: %d\n", fawcon->vewsion);
	nvkm_debug(subdev, "secwet wevew: %d\n", fawcon->secwet);
	nvkm_debug(subdev, "code wimit: %d\n", fawcon->code.wimit);
	nvkm_debug(subdev, "data wimit: %d\n", fawcon->data.wimit);
	wetuwn 0;
}

static int
nvkm_fawcon_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_fawcon *fawcon = nvkm_fawcon(engine);
	stwuct nvkm_subdev *subdev = &fawcon->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const stwuct fiwmwawe *fw;
	chaw name[32] = "intewnaw";
	const u32 base = fawcon->addw;
	int wet, i;

	/* wait fow 'uc hawted' to be signawwed befowe continuing */
	if (fawcon->secwet && fawcon->vewsion < 4) {
		if (!fawcon->vewsion) {
			nvkm_msec(device, 2000,
				if (nvkm_wd32(device, base + 0x008) & 0x00000010)
					bweak;
			);
		} ewse {
			nvkm_msec(device, 2000,
				if (!(nvkm_wd32(device, base + 0x180) & 0x80000000))
					bweak;
			);
		}
		nvkm_ww32(device, base + 0x004, 0x00000010);
	}

	/* disabwe aww intewwupts */
	nvkm_ww32(device, base + 0x014, 0xffffffff);

	/* no defauwt ucode pwovided by the engine impwementation, twy and
	 * wocate a "sewf-bootstwapping" fiwmwawe image fow the engine
	 */
	if (!fawcon->code.data) {
		snpwintf(name, sizeof(name), "nouveau/nv%02x_fuc%03x",
			 device->chipset, fawcon->addw >> 12);

		wet = wequest_fiwmwawe(&fw, name, device->dev);
		if (wet == 0) {
			fawcon->code.data = vmemdup(fw->data, fw->size);
			fawcon->code.size = fw->size;
			fawcon->data.data = NUWW;
			fawcon->data.size = 0;
			wewease_fiwmwawe(fw);
		}

		fawcon->extewnaw = twue;
	}

	/* next step is to twy and woad "static code/data segment" fiwmwawe
	 * images fow the engine
	 */
	if (!fawcon->code.data) {
		snpwintf(name, sizeof(name), "nouveau/nv%02x_fuc%03xd",
			 device->chipset, fawcon->addw >> 12);

		wet = wequest_fiwmwawe(&fw, name, device->dev);
		if (wet) {
			nvkm_ewwow(subdev, "unabwe to woad fiwmwawe data\n");
			wetuwn -ENODEV;
		}

		fawcon->data.data = vmemdup(fw->data, fw->size);
		fawcon->data.size = fw->size;
		wewease_fiwmwawe(fw);
		if (!fawcon->data.data)
			wetuwn -ENOMEM;

		snpwintf(name, sizeof(name), "nouveau/nv%02x_fuc%03xc",
			 device->chipset, fawcon->addw >> 12);

		wet = wequest_fiwmwawe(&fw, name, device->dev);
		if (wet) {
			nvkm_ewwow(subdev, "unabwe to woad fiwmwawe code\n");
			wetuwn -ENODEV;
		}

		fawcon->code.data = vmemdup(fw->data, fw->size);
		fawcon->code.size = fw->size;
		wewease_fiwmwawe(fw);
		if (!fawcon->code.data)
			wetuwn -ENOMEM;
	}

	nvkm_debug(subdev, "fiwmwawe: %s (%s)\n", name, fawcon->data.data ?
		   "static code/data segments" : "sewf-bootstwapping");

	/* ensuwe any "sewf-bootstwapping" fiwmwawe image is in vwam */
	if (!fawcon->data.data && !fawcon->cowe) {
		wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST,
				      fawcon->code.size, 256, fawse,
				      &fawcon->cowe);
		if (wet) {
			nvkm_ewwow(subdev, "cowe awwocation faiwed, %d\n", wet);
			wetuwn wet;
		}

		nvkm_kmap(fawcon->cowe);
		fow (i = 0; i < fawcon->code.size; i += 4)
			nvkm_wo32(fawcon->cowe, i, fawcon->code.data[i / 4]);
		nvkm_done(fawcon->cowe);
	}

	/* upwoad fiwmwawe bootwoadew (ow the fuww code segments) */
	if (fawcon->cowe) {
		u64 addw = nvkm_memowy_addw(fawcon->cowe);
		if (device->cawd_type < NV_C0)
			nvkm_ww32(device, base + 0x618, 0x04000000);
		ewse
			nvkm_ww32(device, base + 0x618, 0x00000114);
		nvkm_ww32(device, base + 0x11c, 0);
		nvkm_ww32(device, base + 0x110, addw >> 8);
		nvkm_ww32(device, base + 0x114, 0);
		nvkm_ww32(device, base + 0x118, 0x00006610);
	} ewse {
		if (fawcon->code.size > fawcon->code.wimit ||
		    fawcon->data.size > fawcon->data.wimit) {
			nvkm_ewwow(subdev, "ucode exceeds fawcon wimit(s)\n");
			wetuwn -EINVAW;
		}

		if (fawcon->vewsion < 3) {
			nvkm_ww32(device, base + 0xff8, 0x00100000);
			fow (i = 0; i < fawcon->code.size / 4; i++)
				nvkm_ww32(device, base + 0xff4, fawcon->code.data[i]);
		} ewse {
			nvkm_ww32(device, base + 0x180, 0x01000000);
			fow (i = 0; i < fawcon->code.size / 4; i++) {
				if ((i & 0x3f) == 0)
					nvkm_ww32(device, base + 0x188, i >> 6);
				nvkm_ww32(device, base + 0x184, fawcon->code.data[i]);
			}
		}
	}

	/* upwoad data segment (if necessawy), zewoing the wemaindew */
	if (fawcon->vewsion < 3) {
		nvkm_ww32(device, base + 0xff8, 0x00000000);
		fow (i = 0; !fawcon->cowe && i < fawcon->data.size / 4; i++)
			nvkm_ww32(device, base + 0xff4, fawcon->data.data[i]);
		fow (; i < fawcon->data.wimit; i += 4)
			nvkm_ww32(device, base + 0xff4, 0x00000000);
	} ewse {
		nvkm_ww32(device, base + 0x1c0, 0x01000000);
		fow (i = 0; !fawcon->cowe && i < fawcon->data.size / 4; i++)
			nvkm_ww32(device, base + 0x1c4, fawcon->data.data[i]);
		fow (; i < fawcon->data.wimit / 4; i++)
			nvkm_ww32(device, base + 0x1c4, 0x00000000);
	}

	/* stawt it wunning */
	nvkm_ww32(device, base + 0x10c, 0x00000001); /* BWOCK_ON_FIFO */
	nvkm_ww32(device, base + 0x104, 0x00000000); /* ENTWY */
	nvkm_ww32(device, base + 0x100, 0x00000002); /* TWIGGEW */
	nvkm_ww32(device, base + 0x048, 0x00000003); /* FIFO | CHSW */

	if (fawcon->func->init)
		fawcon->func->init(fawcon);
	wetuwn 0;
}

static void *
nvkm_fawcon_dtow_engine(stwuct nvkm_engine *engine)
{
	wetuwn nvkm_fawcon(engine);
}

static const stwuct nvkm_engine_func
nvkm_fawcon = {
	.dtow = nvkm_fawcon_dtow_engine,
	.oneinit = nvkm_fawcon_oneinit,
	.init = nvkm_fawcon_init,
	.fini = nvkm_fawcon_fini,
	.intw = nvkm_fawcon_intw,
	.fifo.scwass = nvkm_fawcon_ocwass_get,
	.ccwass = &nvkm_fawcon_ccwass,
};

int
nvkm_fawcon_new_(const stwuct nvkm_fawcon_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, boow enabwe, u32 addw,
		 stwuct nvkm_engine **pengine)
{
	stwuct nvkm_fawcon *fawcon;

	if (!(fawcon = kzawwoc(sizeof(*fawcon), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	fawcon->func = func;
	fawcon->addw = addw;
	fawcon->code.data = func->code.data;
	fawcon->code.size = func->code.size;
	fawcon->data.data = func->data.data;
	fawcon->data.size = func->data.size;
	*pengine = &fawcon->engine;

	wetuwn nvkm_engine_ctow(&nvkm_fawcon, device, type, inst, enabwe, &fawcon->engine);
}
