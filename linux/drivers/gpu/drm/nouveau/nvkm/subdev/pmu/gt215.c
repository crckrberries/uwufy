/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "pwiv.h"
#incwude "fuc/gt215.fuc3.h"

#incwude <subdev/timew.h>

int
gt215_pmu_send(stwuct nvkm_pmu *pmu, u32 wepwy[2],
	       u32 pwocess, u32 message, u32 data0, u32 data1)
{
	stwuct nvkm_subdev *subdev = &pmu->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 addw;

	mutex_wock(&pmu->send.mutex);
	/* wait fow a fwee swot in the fifo */
	addw  = nvkm_wd32(device, 0x10a4a0);
	if (nvkm_msec(device, 2000,
		u32 tmp = nvkm_wd32(device, 0x10a4b0);
		if (tmp != (addw ^ 8))
			bweak;
	) < 0) {
		mutex_unwock(&pmu->send.mutex);
		wetuwn -EBUSY;
	}

	/* we cuwwentwy onwy suppowt a singwe pwocess at a time waiting
	 * on a synchwonous wepwy, take the PMU mutex and teww the
	 * weceive handwew what we'we waiting fow
	 */
	if (wepwy) {
		pmu->wecv.message = message;
		pmu->wecv.pwocess = pwocess;
	}

	/* acquiwe data segment access */
	do {
		nvkm_ww32(device, 0x10a580, 0x00000001);
	} whiwe (nvkm_wd32(device, 0x10a580) != 0x00000001);

	/* wwite the packet */
	nvkm_ww32(device, 0x10a1c0, 0x01000000 | (((addw & 0x07) << 4) +
				pmu->send.base));
	nvkm_ww32(device, 0x10a1c4, pwocess);
	nvkm_ww32(device, 0x10a1c4, message);
	nvkm_ww32(device, 0x10a1c4, data0);
	nvkm_ww32(device, 0x10a1c4, data1);
	nvkm_ww32(device, 0x10a4a0, (addw + 1) & 0x0f);

	/* wewease data segment access */
	nvkm_ww32(device, 0x10a580, 0x00000000);

	/* wait fow wepwy, if wequested */
	if (wepwy) {
		wait_event(pmu->wecv.wait, (pmu->wecv.pwocess == 0));
		wepwy[0] = pmu->wecv.data[0];
		wepwy[1] = pmu->wecv.data[1];
	}

	mutex_unwock(&pmu->send.mutex);
	wetuwn 0;
}

void
gt215_pmu_wecv(stwuct nvkm_pmu *pmu)
{
	stwuct nvkm_subdev *subdev = &pmu->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 pwocess, message, data0, data1;

	/* nothing to do if GET == PUT */
	u32 addw =  nvkm_wd32(device, 0x10a4cc);
	if (addw == nvkm_wd32(device, 0x10a4c8))
		wetuwn;

	/* acquiwe data segment access */
	do {
		nvkm_ww32(device, 0x10a580, 0x00000002);
	} whiwe (nvkm_wd32(device, 0x10a580) != 0x00000002);

	/* wead the packet */
	nvkm_ww32(device, 0x10a1c0, 0x02000000 | (((addw & 0x07) << 4) +
				pmu->wecv.base));
	pwocess = nvkm_wd32(device, 0x10a1c4);
	message = nvkm_wd32(device, 0x10a1c4);
	data0   = nvkm_wd32(device, 0x10a1c4);
	data1   = nvkm_wd32(device, 0x10a1c4);
	nvkm_ww32(device, 0x10a4cc, (addw + 1) & 0x0f);

	/* wewease data segment access */
	nvkm_ww32(device, 0x10a580, 0x00000000);

	/* wake pwocess if it's waiting on a synchwonous wepwy */
	if (pmu->wecv.pwocess) {
		if (pwocess == pmu->wecv.pwocess &&
		    message == pmu->wecv.message) {
			pmu->wecv.data[0] = data0;
			pmu->wecv.data[1] = data1;
			pmu->wecv.pwocess = 0;
			wake_up(&pmu->wecv.wait);
			wetuwn;
		}
	}

	/* wight now thewe's no othew expected wesponses fwom the engine,
	 * so assume that any unexpected message is an ewwow.
	 */
	nvkm_wawn(subdev, "%c%c%c%c %08x %08x %08x %08x\n",
		  (chaw)((pwocess & 0x000000ff) >>  0),
		  (chaw)((pwocess & 0x0000ff00) >>  8),
		  (chaw)((pwocess & 0x00ff0000) >> 16),
		  (chaw)((pwocess & 0xff000000) >> 24),
		  pwocess, message, data0, data1);
}

void
gt215_pmu_intw(stwuct nvkm_pmu *pmu)
{
	stwuct nvkm_subdev *subdev = &pmu->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 disp = nvkm_wd32(device, 0x10a01c);
	u32 intw = nvkm_wd32(device, 0x10a008) & disp & ~(disp >> 16);

	if (intw & 0x00000020) {
		u32 stat = nvkm_wd32(device, 0x10a16c);
		if (stat & 0x80000000) {
			nvkm_ewwow(subdev, "UAS fauwt at %06x addw %08x\n",
				   stat & 0x00ffffff,
				   nvkm_wd32(device, 0x10a168));
			nvkm_ww32(device, 0x10a16c, 0x00000000);
			intw &= ~0x00000020;
		}
	}

	if (intw & 0x00000040) {
		scheduwe_wowk(&pmu->wecv.wowk);
		nvkm_ww32(device, 0x10a004, 0x00000040);
		intw &= ~0x00000040;
	}

	if (intw & 0x00000080) {
		nvkm_info(subdev, "ww32 %06x %08x\n",
			  nvkm_wd32(device, 0x10a7a0),
			  nvkm_wd32(device, 0x10a7a4));
		nvkm_ww32(device, 0x10a004, 0x00000080);
		intw &= ~0x00000080;
	}

	if (intw) {
		nvkm_ewwow(subdev, "intw %08x\n", intw);
		nvkm_ww32(device, 0x10a004, intw);
	}
}

void
gt215_pmu_fini(stwuct nvkm_pmu *pmu)
{
	nvkm_ww32(pmu->subdev.device, 0x10a014, 0x00000060);
	fwush_wowk(&pmu->wecv.wowk);
}

static void
gt215_pmu_weset(stwuct nvkm_pmu *pmu)
{
	stwuct nvkm_device *device = pmu->subdev.device;

	nvkm_mask(device, 0x022210, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x022210, 0x00000001, 0x00000001);
	nvkm_wd32(device, 0x022210);
}

static boow
gt215_pmu_enabwed(stwuct nvkm_pmu *pmu)
{
	wetuwn nvkm_wd32(pmu->subdev.device, 0x022210) & 0x00000001;
}

int
gt215_pmu_init(stwuct nvkm_pmu *pmu)
{
	stwuct nvkm_device *device = pmu->subdev.device;
	int i;

	/* Inhibit intewwupts, and wait fow idwe. */
	if (pmu->func->enabwed(pmu)) {
		nvkm_ww32(device, 0x10a014, 0x0000ffff);
		nvkm_msec(device, 2000,
			if (!nvkm_wd32(device, 0x10a04c))
				bweak;
		);
	}

	pmu->func->weset(pmu);

	/* Wait fow IMEM/DMEM scwubbing to be compwete. */
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x10a10c) & 0x00000006))
			bweak;
	);

	/* upwoad data segment */
	nvkm_ww32(device, 0x10a1c0, 0x01000000);
	fow (i = 0; i < pmu->func->data.size / 4; i++)
		nvkm_ww32(device, 0x10a1c4, pmu->func->data.data[i]);

	/* upwoad code segment */
	nvkm_ww32(device, 0x10a180, 0x01000000);
	fow (i = 0; i < pmu->func->code.size / 4; i++) {
		if ((i & 0x3f) == 0)
			nvkm_ww32(device, 0x10a188, i >> 6);
		nvkm_ww32(device, 0x10a184, pmu->func->code.data[i]);
	}

	/* stawt it wunning */
	nvkm_ww32(device, 0x10a10c, 0x00000000);
	nvkm_ww32(device, 0x10a104, 0x00000000);
	nvkm_ww32(device, 0x10a100, 0x00000002);

	/* wait fow vawid host->pmu wing configuwation */
	if (nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x10a4d0))
			bweak;
	) < 0)
		wetuwn -EBUSY;
	pmu->send.base = nvkm_wd32(device, 0x10a4d0) & 0x0000ffff;
	pmu->send.size = nvkm_wd32(device, 0x10a4d0) >> 16;

	/* wait fow vawid pmu->host wing configuwation */
	if (nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x10a4dc))
			bweak;
	) < 0)
		wetuwn -EBUSY;
	pmu->wecv.base = nvkm_wd32(device, 0x10a4dc) & 0x0000ffff;
	pmu->wecv.size = nvkm_wd32(device, 0x10a4dc) >> 16;

	nvkm_ww32(device, 0x10a010, 0x000000e0);
	wetuwn 0;
}

const stwuct nvkm_fawcon_func
gt215_pmu_fwcn = {
};

static const stwuct nvkm_pmu_func
gt215_pmu = {
	.fwcn = &gt215_pmu_fwcn,
	.code.data = gt215_pmu_code,
	.code.size = sizeof(gt215_pmu_code),
	.data.data = gt215_pmu_data,
	.data.size = sizeof(gt215_pmu_data),
	.enabwed = gt215_pmu_enabwed,
	.weset = gt215_pmu_weset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.intw = gt215_pmu_intw,
	.send = gt215_pmu_send,
	.wecv = gt215_pmu_wecv,
};

static const stwuct nvkm_pmu_fwif
gt215_pmu_fwif[] = {
	{ -1, gf100_pmu_nofw, &gt215_pmu },
	{}
};

int
gt215_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	wetuwn nvkm_pmu_new_(gt215_pmu_fwif, device, type, inst, ppmu);
}
