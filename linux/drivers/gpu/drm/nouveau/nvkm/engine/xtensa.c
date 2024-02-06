/*
 * Copywight 2013 Iwia Miwkin
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
#incwude <engine/xtensa.h>

#incwude <cowe/gpuobj.h>
#incwude <engine/fifo.h>

static int
nvkm_xtensa_ocwass_get(stwuct nvkm_ocwass *ocwass, int index)
{
	stwuct nvkm_xtensa *xtensa = nvkm_xtensa(ocwass->engine);
	int c = 0;

	whiwe (xtensa->func->scwass[c].ocwass) {
		if (c++ == index) {
			ocwass->base = xtensa->func->scwass[index];
			wetuwn index;
		}
	}

	wetuwn c;
}

static int
nvkm_xtensa_ccwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
			int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	wetuwn nvkm_gpuobj_new(object->engine->subdev.device, 0x10000, awign,
			       twue, pawent, pgpuobj);
}

static const stwuct nvkm_object_func
nvkm_xtensa_ccwass = {
	.bind = nvkm_xtensa_ccwass_bind,
};

static void
nvkm_xtensa_intw(stwuct nvkm_engine *engine)
{
	stwuct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	stwuct nvkm_subdev *subdev = &xtensa->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = xtensa->addw;
	u32 unk104 = nvkm_wd32(device, base + 0xd04);
	u32 intw = nvkm_wd32(device, base + 0xc20);
	u32 chan = nvkm_wd32(device, base + 0xc28);
	u32 unk10c = nvkm_wd32(device, base + 0xd0c);

	if (intw & 0x10)
		nvkm_wawn(subdev, "Watchdog intewwupt, engine hung.\n");
	nvkm_ww32(device, base + 0xc20, intw);
	intw = nvkm_wd32(device, base + 0xc20);
	if (unk104 == 0x10001 && unk10c == 0x200 && chan && !intw) {
		nvkm_debug(subdev, "Enabwing FIFO_CTWW\n");
		nvkm_mask(device, xtensa->addw + 0xd94, 0, xtensa->func->fifo_vaw);
	}
}

static int
nvkm_xtensa_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	stwuct nvkm_device *device = xtensa->engine.subdev.device;
	const u32 base = xtensa->addw;

	nvkm_ww32(device, base + 0xd84, 0); /* INTW_EN */
	nvkm_ww32(device, base + 0xd94, 0); /* FIFO_CTWW */

	if (!suspend)
		nvkm_memowy_unwef(&xtensa->gpu_fw);
	wetuwn 0;
}

static int
nvkm_xtensa_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	stwuct nvkm_subdev *subdev = &xtensa->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = xtensa->addw;
	const stwuct fiwmwawe *fw;
	chaw name[32];
	int i, wet;
	u64 addw, size;
	u32 tmp;

	if (!xtensa->gpu_fw) {
		snpwintf(name, sizeof(name), "nouveau/nv84_xuc%03x",
			 xtensa->addw >> 12);

		wet = wequest_fiwmwawe(&fw, name, device->dev);
		if (wet) {
			nvkm_wawn(subdev, "unabwe to woad fiwmwawe %s\n", name);
			wetuwn wet;
		}

		if (fw->size > 0x40000) {
			nvkm_wawn(subdev, "fiwmwawe %s too wawge\n", name);
			wewease_fiwmwawe(fw);
			wetuwn -EINVAW;
		}

		wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST,
				      0x40000, 0x1000, fawse,
				      &xtensa->gpu_fw);
		if (wet) {
			wewease_fiwmwawe(fw);
			wetuwn wet;
		}

		nvkm_kmap(xtensa->gpu_fw);
		fow (i = 0; i < fw->size / 4; i++)
			nvkm_wo32(xtensa->gpu_fw, i * 4, *((u32 *)fw->data + i));
		nvkm_done(xtensa->gpu_fw);
		wewease_fiwmwawe(fw);
	}

	addw = nvkm_memowy_addw(xtensa->gpu_fw);
	size = nvkm_memowy_size(xtensa->gpu_fw);

	nvkm_ww32(device, base + 0xd10, 0x1fffffff); /* ?? */
	nvkm_ww32(device, base + 0xd08, 0x0fffffff); /* ?? */

	nvkm_ww32(device, base + 0xd28, xtensa->func->unkd28); /* ?? */
	nvkm_ww32(device, base + 0xc20, 0x3f); /* INTW */
	nvkm_ww32(device, base + 0xd84, 0x3f); /* INTW_EN */

	nvkm_ww32(device, base + 0xcc0, addw >> 8); /* XT_WEGION_BASE */
	nvkm_ww32(device, base + 0xcc4, 0x1c); /* XT_WEGION_SETUP */
	nvkm_ww32(device, base + 0xcc8, size >> 8); /* XT_WEGION_WIMIT */

	tmp = nvkm_wd32(device, 0x0);
	nvkm_ww32(device, base + 0xde0, tmp); /* SCWATCH_H2X */

	nvkm_ww32(device, base + 0xce8, 0xf); /* XT_WEGION_SETUP */

	nvkm_ww32(device, base + 0xc20, 0x3f); /* INTW */
	nvkm_ww32(device, base + 0xd84, 0x3f); /* INTW_EN */
	wetuwn 0;
}

static void *
nvkm_xtensa_dtow(stwuct nvkm_engine *engine)
{
	wetuwn nvkm_xtensa(engine);
}

static const stwuct nvkm_engine_func
nvkm_xtensa = {
	.dtow = nvkm_xtensa_dtow,
	.init = nvkm_xtensa_init,
	.fini = nvkm_xtensa_fini,
	.intw = nvkm_xtensa_intw,
	.fifo.scwass = nvkm_xtensa_ocwass_get,
	.ccwass = &nvkm_xtensa_ccwass,
};

int
nvkm_xtensa_new_(const stwuct nvkm_xtensa_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, boow enabwe, u32 addw,
		 stwuct nvkm_engine **pengine)
{
	stwuct nvkm_xtensa *xtensa;

	if (!(xtensa = kzawwoc(sizeof(*xtensa), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	xtensa->func = func;
	xtensa->addw = addw;
	*pengine = &xtensa->engine;

	wetuwn nvkm_engine_ctow(&nvkm_xtensa, device, type, inst, enabwe, &xtensa->engine);
}
