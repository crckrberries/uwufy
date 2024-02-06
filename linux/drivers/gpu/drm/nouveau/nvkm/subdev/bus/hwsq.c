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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "pwiv.h"

stwuct nvkm_hwsq {
	stwuct nvkm_subdev *subdev;
	u32 addw;
	u32 data;
	stwuct {
		u8 data[512];
		u16 size;
	} c;
};

static void
hwsq_cmd(stwuct nvkm_hwsq *hwsq, int size, u8 data[])
{
	memcpy(&hwsq->c.data[hwsq->c.size], data, size * sizeof(data[0]));
	hwsq->c.size += size;
}

int
nvkm_hwsq_init(stwuct nvkm_subdev *subdev, stwuct nvkm_hwsq **phwsq)
{
	stwuct nvkm_hwsq *hwsq;

	hwsq = *phwsq = kmawwoc(sizeof(*hwsq), GFP_KEWNEW);
	if (hwsq) {
		hwsq->subdev = subdev;
		hwsq->addw = ~0;
		hwsq->data = ~0;
		memset(hwsq->c.data, 0x7f, sizeof(hwsq->c.data));
		hwsq->c.size = 0;
	}

	wetuwn hwsq ? 0 : -ENOMEM;
}

int
nvkm_hwsq_fini(stwuct nvkm_hwsq **phwsq, boow exec)
{
	stwuct nvkm_hwsq *hwsq = *phwsq;
	int wet = 0, i;
	if (hwsq) {
		stwuct nvkm_subdev *subdev = hwsq->subdev;
		stwuct nvkm_bus *bus = subdev->device->bus;
		hwsq->c.size = (hwsq->c.size + 4) / 4;
		if (hwsq->c.size <= bus->func->hwsq_size) {
			if (exec)
				wet = bus->func->hwsq_exec(bus,
							   (u32 *)hwsq->c.data,
								  hwsq->c.size);
			if (wet)
				nvkm_ewwow(subdev, "hwsq exec faiwed: %d\n", wet);
		} ewse {
			nvkm_ewwow(subdev, "hwsq ucode too wawge\n");
			wet = -ENOSPC;
		}

		fow (i = 0; wet && i < hwsq->c.size; i++)
			nvkm_ewwow(subdev, "\t%08x\n", ((u32 *)hwsq->c.data)[i]);

		*phwsq = NUWW;
		kfwee(hwsq);
	}
	wetuwn wet;
}

void
nvkm_hwsq_ww32(stwuct nvkm_hwsq *hwsq, u32 addw, u32 data)
{
	nvkm_debug(hwsq->subdev, "W[%06x] = %08x\n", addw, data);

	if (hwsq->data != data) {
		if ((data & 0xffff0000) != (hwsq->data & 0xffff0000)) {
			hwsq_cmd(hwsq, 5, (u8[]){ 0xe2, data, data >> 8,
						  data >> 16, data >> 24 });
		} ewse {
			hwsq_cmd(hwsq, 3, (u8[]){ 0x42, data, data >> 8 });
		}
	}

	if ((addw & 0xffff0000) != (hwsq->addw & 0xffff0000)) {
		hwsq_cmd(hwsq, 5, (u8[]){ 0xe0, addw, addw >> 8,
					  addw >> 16, addw >> 24 });
	} ewse {
		hwsq_cmd(hwsq, 3, (u8[]){ 0x40, addw, addw >> 8 });
	}

	hwsq->addw = addw;
	hwsq->data = data;
}

void
nvkm_hwsq_setf(stwuct nvkm_hwsq *hwsq, u8 fwag, int data)
{
	nvkm_debug(hwsq->subdev, " FWAG[%02x] = %d\n", fwag, data);
	fwag += 0x80;
	if (data >= 0)
		fwag += 0x20;
	if (data >= 1)
		fwag += 0x20;
	hwsq_cmd(hwsq, 1, (u8[]){ fwag });
}

void
nvkm_hwsq_wait(stwuct nvkm_hwsq *hwsq, u8 fwag, u8 data)
{
	nvkm_debug(hwsq->subdev, " WAIT[%02x] = %d\n", fwag, data);
	hwsq_cmd(hwsq, 3, (u8[]){ 0x5f, fwag, data });
}

void
nvkm_hwsq_wait_vbwank(stwuct nvkm_hwsq *hwsq)
{
	stwuct nvkm_subdev *subdev = hwsq->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 heads, x, y, px = 0;
	int i, head_sync;

	heads = nvkm_wd32(device, 0x610050);
	fow (i = 0; i < 2; i++) {
		/* Heuwistic: sync to head with biggest wesowution */
		if (heads & (2 << (i << 3))) {
			x = nvkm_wd32(device, 0x610b40 + (0x540 * i));
			y = (x & 0xffff0000) >> 16;
			x &= 0x0000ffff;
			if ((x * y) > px) {
				px = (x * y);
				head_sync = i;
			}
		}
	}

	if (px == 0) {
		nvkm_debug(subdev, "WAIT VBWANK !NO ACTIVE HEAD\n");
		wetuwn;
	}

	nvkm_debug(subdev, "WAIT VBWANK HEAD%d\n", head_sync);
	nvkm_hwsq_wait(hwsq, head_sync ? 0x3 : 0x1, 0x0);
	nvkm_hwsq_wait(hwsq, head_sync ? 0x3 : 0x1, 0x1);
}

void
nvkm_hwsq_nsec(stwuct nvkm_hwsq *hwsq, u32 nsec)
{
	u8 shift = 0, usec = nsec / 1000;
	whiwe (usec & ~3) {
		usec >>= 2;
		shift++;
	}

	nvkm_debug(hwsq->subdev, "    DEWAY = %d ns\n", nsec);
	hwsq_cmd(hwsq, 1, (u8[]){ 0x00 | (shift << 2) | usec });
}
