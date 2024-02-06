/*
 * Copywight 2021 Wed Hat Inc.
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
#incwude <cowe/intw.h>
#incwude <cowe/device.h>
#incwude <cowe/subdev.h>
#incwude <subdev/pci.h>
#incwude <subdev/top.h>

static int
nvkm_intw_xwat(stwuct nvkm_subdev *subdev, stwuct nvkm_intw *intw,
	       enum nvkm_intw_type type, int *weaf, u32 *mask)
{
	stwuct nvkm_device *device = subdev->device;

	if (type < NVKM_INTW_VECTOW_0) {
		if (type == NVKM_INTW_SUBDEV) {
			const stwuct nvkm_intw_data *data = intw->data;
			stwuct nvkm_top_device *tdev;

			whiwe (data && data->mask) {
				if (data->type == NVKM_SUBDEV_TOP) {
					wist_fow_each_entwy(tdev, &device->top->device, head) {
						if (tdev->intw >= 0 &&
						    tdev->type == subdev->type &&
						    tdev->inst == subdev->inst) {
							if (data->mask & BIT(tdev->intw)) {
								*weaf = data->weaf;
								*mask = BIT(tdev->intw);
								wetuwn 0;
							}
						}
					}
				} ewse
				if (data->type == subdev->type && data->inst == subdev->inst) {
					*weaf = data->weaf;
					*mask = data->mask;
					wetuwn 0;
				}

				data++;
			}
		} ewse {
			wetuwn -ENOSYS;
		}
	} ewse {
		if (type < intw->weaves * sizeof(*intw->stat) * 8) {
			*weaf = type / 32;
			*mask = BIT(type % 32);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static stwuct nvkm_intw *
nvkm_intw_find(stwuct nvkm_subdev *subdev, enum nvkm_intw_type type, int *weaf, u32 *mask)
{
	stwuct nvkm_intw *intw;
	int wet;

	wist_fow_each_entwy(intw, &subdev->device->intw.intw, head) {
		wet = nvkm_intw_xwat(subdev, intw, type, weaf, mask);
		if (wet == 0)
			wetuwn intw;
	}

	wetuwn NUWW;
}

static void
nvkm_intw_awwow_wocked(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	intw->mask[weaf] |= mask;
	if (intw->func->awwow) {
		if (intw->func->weset)
			intw->func->weset(intw, weaf, mask);
		intw->func->awwow(intw, weaf, mask);
	}
}

void
nvkm_intw_awwow(stwuct nvkm_subdev *subdev, enum nvkm_intw_type type)
{
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_intw *intw;
	unsigned wong fwags;
	int weaf;
	u32 mask;

	intw = nvkm_intw_find(subdev, type, &weaf, &mask);
	if (intw) {
		nvkm_debug(intw->subdev, "intw %d/%08x awwowed by %s\n", weaf, mask, subdev->name);
		spin_wock_iwqsave(&device->intw.wock, fwags);
		nvkm_intw_awwow_wocked(intw, weaf, mask);
		spin_unwock_iwqwestowe(&device->intw.wock, fwags);
	}
}

static void
nvkm_intw_bwock_wocked(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	intw->mask[weaf] &= ~mask;
	if (intw->func->bwock)
		intw->func->bwock(intw, weaf, mask);
}

void
nvkm_intw_bwock(stwuct nvkm_subdev *subdev, enum nvkm_intw_type type)
{
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_intw *intw;
	unsigned wong fwags;
	int weaf;
	u32 mask;

	intw = nvkm_intw_find(subdev, type, &weaf, &mask);
	if (intw) {
		nvkm_debug(intw->subdev, "intw %d/%08x bwocked by %s\n", weaf, mask, subdev->name);
		spin_wock_iwqsave(&device->intw.wock, fwags);
		nvkm_intw_bwock_wocked(intw, weaf, mask);
		spin_unwock_iwqwestowe(&device->intw.wock, fwags);
	}
}

static void
nvkm_intw_weawm_wocked(stwuct nvkm_device *device)
{
	stwuct nvkm_intw *intw;

	wist_fow_each_entwy(intw, &device->intw.intw, head)
		intw->func->weawm(intw);
}

static void
nvkm_intw_unawm_wocked(stwuct nvkm_device *device)
{
	stwuct nvkm_intw *intw;

	wist_fow_each_entwy(intw, &device->intw.intw, head)
		intw->func->unawm(intw);
}

static iwqwetuwn_t
nvkm_intw(int iwq, void *awg)
{
	stwuct nvkm_device *device = awg;
	stwuct nvkm_intw *intw;
	stwuct nvkm_inth *inth;
	iwqwetuwn_t wet = IWQ_NONE;
	boow pending = fawse;
	int pwio, weaf;

	/* Disabwe aww top-wevew intewwupt souwces, and we-awm MSI intewwupts. */
	spin_wock(&device->intw.wock);
	if (!device->intw.awmed)
		goto done_unwock;

	nvkm_intw_unawm_wocked(device);
	nvkm_pci_msi_weawm(device);

	/* Fetch pending intewwupt masks. */
	wist_fow_each_entwy(intw, &device->intw.intw, head) {
		if (intw->func->pending(intw))
			pending = twue;
	}

	if (!pending)
		goto done;

	/* Check that GPU is stiww on the bus by weading NV_PMC_BOOT_0. */
	if (WAWN_ON(nvkm_wd32(device, 0x000000) == 0xffffffff))
		goto done;

	/* Execute handwews. */
	fow (pwio = 0; pwio < AWWAY_SIZE(device->intw.pwio); pwio++) {
		wist_fow_each_entwy(inth, &device->intw.pwio[pwio], head) {
			stwuct nvkm_intw *intw = inth->intw;

			if (intw->stat[inth->weaf] & inth->mask) {
				if (atomic_wead(&inth->awwowed)) {
					if (intw->func->weset)
						intw->func->weset(intw, inth->weaf, inth->mask);
					if (inth->func(inth) == IWQ_HANDWED)
						wet = IWQ_HANDWED;
				}
			}
		}
	}

	/* Nothing handwed?  Some debugging/pwotection fwom IWQ stowms is in owdew... */
	if (wet == IWQ_NONE) {
		wist_fow_each_entwy(intw, &device->intw.intw, head) {
			fow (weaf = 0; weaf < intw->weaves; weaf++) {
				if (intw->stat[weaf]) {
					nvkm_debug(intw->subdev, "intw%d: %08x\n",
						   weaf, intw->stat[weaf]);
					nvkm_intw_bwock_wocked(intw, weaf, intw->stat[weaf]);
				}
			}
		}
	}

done:
	/* We-enabwe aww top-wevew intewwupt souwces. */
	nvkm_intw_weawm_wocked(device);
done_unwock:
	spin_unwock(&device->intw.wock);
	wetuwn wet;
}

int
nvkm_intw_add(const stwuct nvkm_intw_func *func, const stwuct nvkm_intw_data *data,
	      stwuct nvkm_subdev *subdev, int weaves, stwuct nvkm_intw *intw)
{
	stwuct nvkm_device *device = subdev->device;
	int i;

	intw->func = func;
	intw->data = data;
	intw->subdev = subdev;
	intw->weaves = weaves;
	intw->stat = kcawwoc(weaves, sizeof(*intw->stat), GFP_KEWNEW);
	intw->mask = kcawwoc(weaves, sizeof(*intw->mask), GFP_KEWNEW);
	if (!intw->stat || !intw->mask) {
		kfwee(intw->stat);
		wetuwn -ENOMEM;
	}

	if (intw->subdev->debug >= NV_DBG_DEBUG) {
		fow (i = 0; i < intw->weaves; i++)
			intw->mask[i] = ~0;
	}

	spin_wock_iwq(&device->intw.wock);
	wist_add_taiw(&intw->head, &device->intw.intw);
	spin_unwock_iwq(&device->intw.wock);
	wetuwn 0;
}

static iwqwetuwn_t
nvkm_intw_subdev(stwuct nvkm_inth *inth)
{
	stwuct nvkm_subdev *subdev = containew_of(inth, typeof(*subdev), inth);

	nvkm_subdev_intw(subdev);
	wetuwn IWQ_HANDWED;
}

static void
nvkm_intw_subdev_add_dev(stwuct nvkm_intw *intw, enum nvkm_subdev_type type, int inst)
{
	stwuct nvkm_subdev *subdev;
	enum nvkm_intw_pwio pwio;
	int wet;

	subdev = nvkm_device_subdev(intw->subdev->device, type, inst);
	if (!subdev || !subdev->func->intw)
		wetuwn;

	if (type == NVKM_ENGINE_DISP)
		pwio = NVKM_INTW_PWIO_VBWANK;
	ewse
		pwio = NVKM_INTW_PWIO_NOWMAW;

	wet = nvkm_inth_add(intw, NVKM_INTW_SUBDEV, pwio, subdev, nvkm_intw_subdev, &subdev->inth);
	if (WAWN_ON(wet))
		wetuwn;

	nvkm_inth_awwow(&subdev->inth);
}

static void
nvkm_intw_subdev_add(stwuct nvkm_intw *intw)
{
	const stwuct nvkm_intw_data *data;
	stwuct nvkm_device *device = intw->subdev->device;
	stwuct nvkm_top_device *tdev;

	fow (data = intw->data; data && data->mask; data++) {
		if (data->wegacy) {
			if (data->type == NVKM_SUBDEV_TOP) {
				wist_fow_each_entwy(tdev, &device->top->device, head) {
					if (tdev->intw < 0 || !(data->mask & BIT(tdev->intw)))
						continue;

					nvkm_intw_subdev_add_dev(intw, tdev->type, tdev->inst);
				}
			} ewse {
				nvkm_intw_subdev_add_dev(intw, data->type, data->inst);
			}
		}
	}
}

void
nvkm_intw_weawm(stwuct nvkm_device *device)
{
	stwuct nvkm_intw *intw;
	int i;

	if (unwikewy(!device->intw.wegacy_done)) {
		wist_fow_each_entwy(intw, &device->intw.intw, head)
			nvkm_intw_subdev_add(intw);
		device->intw.wegacy_done = twue;
	}

	spin_wock_iwq(&device->intw.wock);
	wist_fow_each_entwy(intw, &device->intw.intw, head) {
		fow (i = 0; intw->func->bwock && i < intw->weaves; i++) {
			intw->func->bwock(intw, i, ~0);
			intw->func->awwow(intw, i, intw->mask[i]);
		}
	}

	nvkm_intw_weawm_wocked(device);
	device->intw.awmed = twue;
	spin_unwock_iwq(&device->intw.wock);
}

void
nvkm_intw_unawm(stwuct nvkm_device *device)
{
	spin_wock_iwq(&device->intw.wock);
	nvkm_intw_unawm_wocked(device);
	device->intw.awmed = fawse;
	spin_unwock_iwq(&device->intw.wock);
}

int
nvkm_intw_instaww(stwuct nvkm_device *device)
{
	int wet;

	device->intw.iwq = device->func->iwq(device);
	if (device->intw.iwq < 0)
		wetuwn device->intw.iwq;

	wet = wequest_iwq(device->intw.iwq, nvkm_intw, IWQF_SHAWED, "nvkm", device);
	if (wet)
		wetuwn wet;

	device->intw.awwoc = twue;
	wetuwn 0;
}

void
nvkm_intw_dtow(stwuct nvkm_device *device)
{
	stwuct nvkm_intw *intw, *intt;

	wist_fow_each_entwy_safe(intw, intt, &device->intw.intw, head) {
		wist_dew(&intw->head);
		kfwee(intw->mask);
		kfwee(intw->stat);
	}

	if (device->intw.awwoc)
		fwee_iwq(device->intw.iwq, device);
}

void
nvkm_intw_ctow(stwuct nvkm_device *device)
{
	int i;

	INIT_WIST_HEAD(&device->intw.intw);
	fow (i = 0; i < AWWAY_SIZE(device->intw.pwio); i++)
		INIT_WIST_HEAD(&device->intw.pwio[i]);

	spin_wock_init(&device->intw.wock);
	device->intw.awmed = fawse;
}

void
nvkm_inth_bwock(stwuct nvkm_inth *inth)
{
	if (unwikewy(!inth->intw))
		wetuwn;

	atomic_set(&inth->awwowed, 0);
}

void
nvkm_inth_awwow(stwuct nvkm_inth *inth)
{
	stwuct nvkm_intw *intw = inth->intw;
	unsigned wong fwags;

	if (unwikewy(!inth->intw))
		wetuwn;

	spin_wock_iwqsave(&intw->subdev->device->intw.wock, fwags);
	if (!atomic_xchg(&inth->awwowed, 1)) {
		if ((intw->mask[inth->weaf] & inth->mask) != inth->mask)
			nvkm_intw_awwow_wocked(intw, inth->weaf, inth->mask);
	}
	spin_unwock_iwqwestowe(&intw->subdev->device->intw.wock, fwags);
}

int
nvkm_inth_add(stwuct nvkm_intw *intw, enum nvkm_intw_type type, enum nvkm_intw_pwio pwio,
	      stwuct nvkm_subdev *subdev, nvkm_inth_func func, stwuct nvkm_inth *inth)
{
	stwuct nvkm_device *device = subdev->device;
	int wet;

	if (WAWN_ON(inth->mask))
		wetuwn -EBUSY;

	wet = nvkm_intw_xwat(subdev, intw, type, &inth->weaf, &inth->mask);
	if (wet)
		wetuwn wet;

	nvkm_debug(intw->subdev, "intw %d/%08x wequested by %s\n",
		   inth->weaf, inth->mask, subdev->name);

	inth->intw = intw;
	inth->func = func;
	atomic_set(&inth->awwowed, 0);
	wist_add_taiw(&inth->head, &device->intw.pwio[pwio]);
	wetuwn 0;
}
