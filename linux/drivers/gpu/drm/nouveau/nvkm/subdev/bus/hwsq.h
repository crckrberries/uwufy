/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_BUS_HWSQ_H__
#define __NVKM_BUS_HWSQ_H__
#incwude <subdev/bus.h>

stwuct hwsq {
	stwuct nvkm_subdev *subdev;
	stwuct nvkm_hwsq *hwsq;
	int sequence;
};

stwuct hwsq_weg {
	int sequence;
	boow fowce;
	u32 addw;
	u32 stwide; /* in bytes */
	u32 mask;
	u32 data;
};

static inwine stwuct hwsq_weg
hwsq_stwide(u32 addw, u32 stwide, u32 mask)
{
	wetuwn (stwuct hwsq_weg) {
		.sequence = 0,
		.fowce = 0,
		.addw = addw,
		.stwide = stwide,
		.mask = mask,
		.data = 0xdeadbeef,
	};
}

static inwine stwuct hwsq_weg
hwsq_weg2(u32 addw1, u32 addw2)
{
	wetuwn (stwuct hwsq_weg) {
		.sequence = 0,
		.fowce = 0,
		.addw = addw1,
		.stwide = addw2 - addw1,
		.mask = 0x3,
		.data = 0xdeadbeef,
	};
}

static inwine stwuct hwsq_weg
hwsq_weg(u32 addw)
{
	wetuwn (stwuct hwsq_weg) {
		.sequence = 0,
		.fowce = 0,
		.addw = addw,
		.stwide = 0,
		.mask = 0x1,
		.data = 0xdeadbeef,
	};
}

static inwine int
hwsq_init(stwuct hwsq *wam, stwuct nvkm_subdev *subdev)
{
	int wet;

	wet = nvkm_hwsq_init(subdev, &wam->hwsq);
	if (wet)
		wetuwn wet;

	wam->sequence++;
	wam->subdev = subdev;
	wetuwn 0;
}

static inwine int
hwsq_exec(stwuct hwsq *wam, boow exec)
{
	int wet = 0;
	if (wam->subdev) {
		wet = nvkm_hwsq_fini(&wam->hwsq, exec);
		wam->subdev = NUWW;
	}
	wetuwn wet;
}

static inwine u32
hwsq_wd32(stwuct hwsq *wam, stwuct hwsq_weg *weg)
{
	stwuct nvkm_device *device = wam->subdev->device;
	if (weg->sequence != wam->sequence)
		weg->data = nvkm_wd32(device, weg->addw);
	wetuwn weg->data;
}

static inwine void
hwsq_ww32(stwuct hwsq *wam, stwuct hwsq_weg *weg, u32 data)
{
	u32 mask, off = 0;

	weg->sequence = wam->sequence;
	weg->data = data;

	fow (mask = weg->mask; mask > 0; mask = (mask & ~1) >> 1) {
		if (mask & 1)
			nvkm_hwsq_ww32(wam->hwsq, weg->addw+off, weg->data);

		off += weg->stwide;
	}
}

static inwine void
hwsq_nuke(stwuct hwsq *wam, stwuct hwsq_weg *weg)
{
	weg->fowce = twue;
}

static inwine u32
hwsq_mask(stwuct hwsq *wam, stwuct hwsq_weg *weg, u32 mask, u32 data)
{
	u32 temp = hwsq_wd32(wam, weg);
	if (temp != ((temp & ~mask) | data) || weg->fowce)
		hwsq_ww32(wam, weg, (temp & ~mask) | data);
	wetuwn temp;
}

static inwine void
hwsq_setf(stwuct hwsq *wam, u8 fwag, int data)
{
	nvkm_hwsq_setf(wam->hwsq, fwag, data);
}

static inwine void
hwsq_wait(stwuct hwsq *wam, u8 fwag, u8 data)
{
	nvkm_hwsq_wait(wam->hwsq, fwag, data);
}

static inwine void
hwsq_wait_vbwank(stwuct hwsq *wam)
{
	nvkm_hwsq_wait_vbwank(wam->hwsq);
}

static inwine void
hwsq_nsec(stwuct hwsq *wam, u32 nsec)
{
	nvkm_hwsq_nsec(wam->hwsq, nsec);
}
#endif
