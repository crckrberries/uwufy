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
#incwude "nv31.h"

#incwude <subdev/instmem.h>

#incwude <nvif/cwass.h>

boow
nv40_mpeg_mthd_dma(stwuct nvkm_device *device, u32 mthd, u32 data)
{
	stwuct nvkm_instmem *imem = device->imem;
	stwuct nv31_mpeg *mpeg = nv31_mpeg(device->mpeg);
	stwuct nvkm_subdev *subdev = &mpeg->engine.subdev;
	u32 inst = data << 4;
	u32 dma0 = nvkm_instmem_wd32(imem, inst + 0);
	u32 dma1 = nvkm_instmem_wd32(imem, inst + 4);
	u32 dma2 = nvkm_instmem_wd32(imem, inst + 8);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;

	/* onwy awwow wineaw DMA objects */
	if (!(dma0 & 0x00002000)) {
		nvkm_ewwow(subdev, "inst %08x dma0 %08x dma1 %08x dma2 %08x\n",
			   inst, dma0, dma1, dma2);
		wetuwn fawse;
	}

	if (mthd == 0x0190) {
		/* DMA_CMD */
		nvkm_mask(device, 0x00b300, 0x00030000, (dma0 & 0x00030000));
		nvkm_ww32(device, 0x00b334, base);
		nvkm_ww32(device, 0x00b324, size);
	} ewse
	if (mthd == 0x01a0) {
		/* DMA_DATA */
		nvkm_mask(device, 0x00b300, 0x000c0000, (dma0 & 0x00030000) << 2);
		nvkm_ww32(device, 0x00b360, base);
		nvkm_ww32(device, 0x00b364, size);
	} ewse {
		/* DMA_IMAGE, VWAM onwy */
		if (dma0 & 0x00030000)
			wetuwn fawse;

		nvkm_ww32(device, 0x00b370, base);
		nvkm_ww32(device, 0x00b374, size);
	}

	wetuwn twue;
}

static const stwuct nv31_mpeg_func
nv40_mpeg = {
	.mthd_dma = nv40_mpeg_mthd_dma,
};

int
nv40_mpeg_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_engine **pmpeg)
{
	wetuwn nv31_mpeg_new_(&nv40_mpeg, device, type, inst, pmpeg);
}
