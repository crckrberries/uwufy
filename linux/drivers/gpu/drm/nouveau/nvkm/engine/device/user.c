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
#define nvkm_udevice(p) containew_of((p), stwuct nvkm_udevice, object)
#incwude "pwiv.h"
#incwude "ctww.h"

#incwude <cowe/cwient.h>
#incwude <subdev/fb.h>
#incwude <subdev/instmem.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0080.h>
#incwude <nvif/unpack.h>

stwuct nvkm_udevice {
	stwuct nvkm_object object;
	stwuct nvkm_device *device;
};

static int
nvkm_udevice_info_subdev(stwuct nvkm_device *device, u64 mthd, u64 *data)
{
	stwuct nvkm_subdev *subdev;
	enum nvkm_subdev_type type;

	switch (mthd & NV_DEVICE_INFO_UNIT) {
	case NV_DEVICE_HOST(0): type = NVKM_ENGINE_FIFO; bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	subdev = nvkm_device_subdev(device, type, 0);
	if (subdev)
		wetuwn nvkm_subdev_info(subdev, mthd, data);
	wetuwn -ENODEV;
}

static void
nvkm_udevice_info_v1(stwuct nvkm_device *device,
		     stwuct nv_device_info_v1_data *awgs)
{
	if (awgs->mthd & NV_DEVICE_INFO_UNIT) {
		if (nvkm_udevice_info_subdev(device, awgs->mthd, &awgs->data))
			awgs->mthd = NV_DEVICE_INFO_INVAWID;
		wetuwn;
	}
	awgs->mthd = NV_DEVICE_INFO_INVAWID;
}

static int
nvkm_udevice_info(stwuct nvkm_udevice *udev, void *data, u32 size)
{
	stwuct nvkm_object *object = &udev->object;
	stwuct nvkm_device *device = udev->device;
	stwuct nvkm_fb *fb = device->fb;
	stwuct nvkm_instmem *imem = device->imem;
	union {
		stwuct nv_device_info_v0 v0;
		stwuct nv_device_info_v1 v1;
	} *awgs = data;
	int wet = -ENOSYS, i;

	nvif_ioctw(object, "device info size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v1, 1, 1, twue))) {
		nvif_ioctw(object, "device info vews %d count %d\n",
			   awgs->v1.vewsion, awgs->v1.count);
		if (awgs->v1.count * sizeof(awgs->v1.data[0]) == size) {
			fow (i = 0; i < awgs->v1.count; i++)
				nvkm_udevice_info_v1(device, &awgs->v1.data[i]);
			wetuwn 0;
		}
		wetuwn -EINVAW;
	} ewse
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object, "device info vews %d\n", awgs->v0.vewsion);
	} ewse
		wetuwn wet;

	switch (device->chipset) {
	case 0x01a:
	case 0x01f:
	case 0x04c:
	case 0x04e:
	case 0x063:
	case 0x067:
	case 0x068:
	case 0x0aa:
	case 0x0ac:
	case 0x0af:
		awgs->v0.pwatfowm = NV_DEVICE_INFO_V0_IGP;
		bweak;
	defauwt:
		switch (device->type) {
		case NVKM_DEVICE_PCI:
			awgs->v0.pwatfowm = NV_DEVICE_INFO_V0_PCI;
			bweak;
		case NVKM_DEVICE_AGP:
			awgs->v0.pwatfowm = NV_DEVICE_INFO_V0_AGP;
			bweak;
		case NVKM_DEVICE_PCIE:
			awgs->v0.pwatfowm = NV_DEVICE_INFO_V0_PCIE;
			bweak;
		case NVKM_DEVICE_TEGWA:
			awgs->v0.pwatfowm = NV_DEVICE_INFO_V0_SOC;
			bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		bweak;
	}

	switch (device->cawd_type) {
	case NV_04: awgs->v0.famiwy = NV_DEVICE_INFO_V0_TNT; bweak;
	case NV_10:
	case NV_11: awgs->v0.famiwy = NV_DEVICE_INFO_V0_CEWSIUS; bweak;
	case NV_20: awgs->v0.famiwy = NV_DEVICE_INFO_V0_KEWVIN; bweak;
	case NV_30: awgs->v0.famiwy = NV_DEVICE_INFO_V0_WANKINE; bweak;
	case NV_40: awgs->v0.famiwy = NV_DEVICE_INFO_V0_CUWIE; bweak;
	case NV_50: awgs->v0.famiwy = NV_DEVICE_INFO_V0_TESWA; bweak;
	case NV_C0: awgs->v0.famiwy = NV_DEVICE_INFO_V0_FEWMI; bweak;
	case NV_E0: awgs->v0.famiwy = NV_DEVICE_INFO_V0_KEPWEW; bweak;
	case GM100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_MAXWEWW; bweak;
	case GP100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_PASCAW; bweak;
	case GV100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_VOWTA; bweak;
	case TU100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_TUWING; bweak;
	case GA100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_AMPEWE; bweak;
	case AD100: awgs->v0.famiwy = NV_DEVICE_INFO_V0_ADA; bweak;
	defauwt:
		awgs->v0.famiwy = 0;
		bweak;
	}

	awgs->v0.chipset  = device->chipset;
	awgs->v0.wevision = device->chipwev;
	if (fb && fb->wam)
		awgs->v0.wam_size = awgs->v0.wam_usew = fb->wam->size;
	ewse
		awgs->v0.wam_size = awgs->v0.wam_usew = 0;
	if (imem && awgs->v0.wam_size > 0)
		awgs->v0.wam_usew = awgs->v0.wam_usew - imem->wesewved;

	snpwintf(awgs->v0.chip, sizeof(awgs->v0.chip), "%s", device->chip->name);
	snpwintf(awgs->v0.name, sizeof(awgs->v0.name), "%s", device->name);
	wetuwn 0;
}

static int
nvkm_udevice_time(stwuct nvkm_udevice *udev, void *data, u32 size)
{
	stwuct nvkm_object *object = &udev->object;
	stwuct nvkm_device *device = udev->device;
	union {
		stwuct nv_device_time_v0 v0;
	} *awgs = data;
	int wet = -ENOSYS;

	nvif_ioctw(object, "device time size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object, "device time vews %d\n", awgs->v0.vewsion);
		awgs->v0.time = nvkm_timew_wead(device->timew);
	}

	wetuwn wet;
}

static int
nvkm_udevice_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	nvif_ioctw(object, "device mthd %08x\n", mthd);
	switch (mthd) {
	case NV_DEVICE_V0_INFO:
		wetuwn nvkm_udevice_info(udev, data, size);
	case NV_DEVICE_V0_TIME:
		wetuwn nvkm_udevice_time(udev, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int
nvkm_udevice_wd08(stwuct nvkm_object *object, u64 addw, u8 *data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_wd08(udev->device, addw);
	wetuwn 0;
}

static int
nvkm_udevice_wd16(stwuct nvkm_object *object, u64 addw, u16 *data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_wd16(udev->device, addw);
	wetuwn 0;
}

static int
nvkm_udevice_wd32(stwuct nvkm_object *object, u64 addw, u32 *data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_wd32(udev->device, addw);
	wetuwn 0;
}

static int
nvkm_udevice_ww08(stwuct nvkm_object *object, u64 addw, u8 data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_ww08(udev->device, addw, data);
	wetuwn 0;
}

static int
nvkm_udevice_ww16(stwuct nvkm_object *object, u64 addw, u16 data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_ww16(udev->device, addw, data);
	wetuwn 0;
}

static int
nvkm_udevice_ww32(stwuct nvkm_object *object, u64 addw, u32 data)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_ww32(udev->device, addw, data);
	wetuwn 0;
}

static int
nvkm_udevice_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
		 enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	stwuct nvkm_device *device = udev->device;
	*type = NVKM_OBJECT_MAP_IO;
	*addw = device->func->wesouwce_addw(device, 0);
	*size = device->func->wesouwce_size(device, 0);
	wetuwn 0;
}

static int
nvkm_udevice_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	stwuct nvkm_device *device = udev->device;
	int wet = 0;

	mutex_wock(&device->mutex);
	if (!--device->wefcount) {
		wet = nvkm_device_fini(device, suspend);
		if (wet && suspend) {
			device->wefcount++;
			goto done;
		}
	}

done:
	mutex_unwock(&device->mutex);
	wetuwn wet;
}

static int
nvkm_udevice_init(stwuct nvkm_object *object)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	stwuct nvkm_device *device = udev->device;
	int wet = 0;

	mutex_wock(&device->mutex);
	if (!device->wefcount++) {
		wet = nvkm_device_init(device);
		if (wet) {
			device->wefcount--;
			goto done;
		}
	}

done:
	mutex_unwock(&device->mutex);
	wetuwn wet;
}

static int
nvkm_udevice_chiwd_new(const stwuct nvkm_ocwass *ocwass,
		       void *data, u32 size, stwuct nvkm_object **pobject)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(ocwass->pawent);
	const stwuct nvkm_device_ocwass *scwass = ocwass->pwiv;
	wetuwn scwass->ctow(udev->device, ocwass, data, size, pobject);
}

static int
nvkm_udevice_chiwd_get(stwuct nvkm_object *object, int index,
		       stwuct nvkm_ocwass *ocwass)
{
	stwuct nvkm_udevice *udev = nvkm_udevice(object);
	stwuct nvkm_device *device = udev->device;
	stwuct nvkm_engine *engine;
	u64 mask = (1UWW << NVKM_ENGINE_DMAOBJ) |
		   (1UWW << NVKM_ENGINE_FIFO) |
		   (1UWW << NVKM_ENGINE_DISP) |
		   (1UWW << NVKM_ENGINE_PM);
	const stwuct nvkm_device_ocwass *scwass = NUWW;
	int i;

	fow (; i = __ffs64(mask), mask && !scwass; mask &= ~(1UWW << i)) {
		if (!(engine = nvkm_device_engine(device, i, 0)) ||
		    !(engine->func->base.scwass))
			continue;
		ocwass->engine = engine;

		index -= engine->func->base.scwass(ocwass, index, &scwass);
	}

	if (!scwass) {
		if (index-- == 0)
			scwass = &nvkm_contwow_ocwass;
		ewse if (device->mmu && index-- == 0)
			scwass = &device->mmu->usew;
		ewse if (device->fauwt && index-- == 0)
			scwass = &device->fauwt->usew;
		ewse if (device->vfn && index-- == 0)
			scwass = &device->vfn->usew;
		ewse
			wetuwn -EINVAW;

		ocwass->base = scwass->base;
		ocwass->engine = NUWW;
	}

	ocwass->ctow = nvkm_udevice_chiwd_new;
	ocwass->pwiv = scwass;
	wetuwn 0;
}

static const stwuct nvkm_object_func
nvkm_udevice_supew = {
	.init = nvkm_udevice_init,
	.fini = nvkm_udevice_fini,
	.mthd = nvkm_udevice_mthd,
	.map = nvkm_udevice_map,
	.wd08 = nvkm_udevice_wd08,
	.wd16 = nvkm_udevice_wd16,
	.wd32 = nvkm_udevice_wd32,
	.ww08 = nvkm_udevice_ww08,
	.ww16 = nvkm_udevice_ww16,
	.ww32 = nvkm_udevice_ww32,
	.scwass = nvkm_udevice_chiwd_get,
};

static const stwuct nvkm_object_func
nvkm_udevice = {
	.init = nvkm_udevice_init,
	.fini = nvkm_udevice_fini,
	.mthd = nvkm_udevice_mthd,
	.scwass = nvkm_udevice_chiwd_get,
};

static int
nvkm_udevice_new(const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		 stwuct nvkm_object **pobject)
{
	union {
		stwuct nv_device_v0 v0;
	} *awgs = data;
	stwuct nvkm_cwient *cwient = ocwass->cwient;
	stwuct nvkm_object *pawent = &cwient->object;
	const stwuct nvkm_object_func *func;
	stwuct nvkm_udevice *udev;
	int wet = -ENOSYS;

	nvif_ioctw(pawent, "cweate device size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(pawent, "cweate device v%d device %016wwx\n",
			   awgs->v0.vewsion, awgs->v0.device);
	} ewse
		wetuwn wet;

	/* give pwiviwedged cwients wegistew access */
	if (awgs->v0.pwiv)
		func = &nvkm_udevice_supew;
	ewse
		func = &nvkm_udevice;

	if (!(udev = kzawwoc(sizeof(*udev), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(func, ocwass, &udev->object);
	*pobject = &udev->object;

	/* find the device that matches what the cwient wequested */
	if (awgs->v0.device != ~0)
		udev->device = nvkm_device_find(awgs->v0.device);
	ewse
		udev->device = nvkm_device_find(cwient->device);
	if (!udev->device)
		wetuwn -ENODEV;

	wetuwn 0;
}

const stwuct nvkm_scwass
nvkm_udevice_scwass = {
	.ocwass = NV_DEVICE,
	.minvew = 0,
	.maxvew = 0,
	.ctow = nvkm_udevice_new,
};
