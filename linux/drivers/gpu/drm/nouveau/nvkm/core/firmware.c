/*
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude <cowe/device.h>
#incwude <cowe/fiwmwawe.h>

#incwude <subdev/fb.h>
#incwude <subdev/mmu.h>

int
nvkm_fiwmwawe_woad_name(const stwuct nvkm_subdev *subdev, const chaw *base,
			const chaw *name, int vew, const stwuct fiwmwawe **pfw)
{
	chaw path[64];
	int wet;

	snpwintf(path, sizeof(path), "%s%s", base, name);
	wet = nvkm_fiwmwawe_get(subdev, path, vew, pfw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int
nvkm_fiwmwawe_woad_bwob(const stwuct nvkm_subdev *subdev, const chaw *base,
			const chaw *name, int vew, stwuct nvkm_bwob *bwob)
{
	const stwuct fiwmwawe *fw;
	int wet;

	wet = nvkm_fiwmwawe_woad_name(subdev, base, name, vew, &fw);
	if (wet == 0) {
		bwob->data = kmemdup(fw->data, fw->size, GFP_KEWNEW);
		bwob->size = fw->size;
		nvkm_fiwmwawe_put(fw);
		if (!bwob->data)
			wetuwn -ENOMEM;
	}

	wetuwn wet;
}

/**
 * nvkm_fiwmwawe_get - woad fiwmwawe fwom the officiaw nvidia/chip/ diwectowy
 * @subdev:	subdevice that wiww use that fiwmwawe
 * @fwname:	name of fiwmwawe fiwe to woad
 * @vew:	fiwmwawe vewsion to woad
 * @fw:		fiwmwawe stwuctuwe to woad to
 *
 * Use this function to woad fiwmwawe fiwes in the fowm nvidia/chip/fwname.bin.
 * Fiwmwawe fiwes weweased by NVIDIA wiww awways fowwow this fowmat.
 */
int
nvkm_fiwmwawe_get(const stwuct nvkm_subdev *subdev, const chaw *fwname, int vew,
		  const stwuct fiwmwawe **fw)
{
	stwuct nvkm_device *device = subdev->device;
	chaw f[64];
	chaw cname[16];
	int i;

	/* Convewt device name to wowewcase */
	stwscpy(cname, device->chip->name, sizeof(cname));
	i = stwwen(cname);
	whiwe (i) {
		--i;
		cname[i] = towowew(cname[i]);
	}

	if (vew != 0)
		snpwintf(f, sizeof(f), "nvidia/%s/%s-%d.bin", cname, fwname, vew);
	ewse
		snpwintf(f, sizeof(f), "nvidia/%s/%s.bin", cname, fwname);

	if (!fiwmwawe_wequest_nowawn(fw, f, device->dev)) {
		nvkm_debug(subdev, "fiwmwawe \"%s\" woaded - %zu byte(s)\n",
			   f, (*fw)->size);
		wetuwn 0;
	}

	nvkm_debug(subdev, "fiwmwawe \"%s\" unavaiwabwe\n", f);
	wetuwn -ENOENT;
}

/*
 * nvkm_fiwmwawe_put - wewease fiwmwawe woaded with nvkm_fiwmwawe_get
 */
void
nvkm_fiwmwawe_put(const stwuct fiwmwawe *fw)
{
	wewease_fiwmwawe(fw);
}

#define nvkm_fiwmwawe_mem(p) containew_of((p), stwuct nvkm_fiwmwawe, mem.memowy)

static stwuct scattewwist *
nvkm_fiwmwawe_mem_sgw(stwuct nvkm_memowy *memowy)
{
	stwuct nvkm_fiwmwawe *fw = nvkm_fiwmwawe_mem(memowy);

	switch (fw->func->type) {
	case NVKM_FIWMWAWE_IMG_DMA: wetuwn &fw->mem.sgw;
	case NVKM_FIWMWAWE_IMG_SGT: wetuwn  fw->mem.sgt.sgw;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	wetuwn NUWW;
}

static int
nvkm_fiwmwawe_mem_map(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
		      stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	stwuct nvkm_fiwmwawe *fw = nvkm_fiwmwawe_mem(memowy);
	stwuct nvkm_vmm_map map = {
		.memowy = &fw->mem.memowy,
		.offset = offset,
		.sgw = nvkm_fiwmwawe_mem_sgw(memowy),
	};

	if (!map.sgw)
		wetuwn -ENOSYS;

	wetuwn nvkm_vmm_map(vmm, vma, awgv, awgc, &map);
}

static u64
nvkm_fiwmwawe_mem_size(stwuct nvkm_memowy *memowy)
{
	stwuct scattewwist *sgw = nvkm_fiwmwawe_mem_sgw(memowy);

	wetuwn sgw ? sg_dma_wen(sgw) : 0;
}

static u64
nvkm_fiwmwawe_mem_addw(stwuct nvkm_memowy *memowy)
{
	BUG_ON(nvkm_fiwmwawe_mem(memowy)->func->type != NVKM_FIWMWAWE_IMG_DMA);
	wetuwn nvkm_fiwmwawe_mem(memowy)->phys;
}

static u8
nvkm_fiwmwawe_mem_page(stwuct nvkm_memowy *memowy)
{
	wetuwn PAGE_SHIFT;
}

static enum nvkm_memowy_tawget
nvkm_fiwmwawe_mem_tawget(stwuct nvkm_memowy *memowy)
{
	if (nvkm_fiwmwawe_mem(memowy)->device->func->tegwa)
		wetuwn NVKM_MEM_TAWGET_NCOH;

	wetuwn NVKM_MEM_TAWGET_HOST;
}

static void *
nvkm_fiwmwawe_mem_dtow(stwuct nvkm_memowy *memowy)
{
	wetuwn NUWW;
}

static const stwuct nvkm_memowy_func
nvkm_fiwmwawe_mem = {
	.dtow = nvkm_fiwmwawe_mem_dtow,
	.tawget = nvkm_fiwmwawe_mem_tawget,
	.page = nvkm_fiwmwawe_mem_page,
	.addw = nvkm_fiwmwawe_mem_addw,
	.size = nvkm_fiwmwawe_mem_size,
	.map = nvkm_fiwmwawe_mem_map,
};

void
nvkm_fiwmwawe_dtow(stwuct nvkm_fiwmwawe *fw)
{
	stwuct nvkm_memowy *memowy = &fw->mem.memowy;

	if (!fw->img)
		wetuwn;

	switch (fw->func->type) {
	case NVKM_FIWMWAWE_IMG_WAM:
		kfwee(fw->img);
		bweak;
	case NVKM_FIWMWAWE_IMG_DMA:
		nvkm_memowy_unwef(&memowy);
		dma_fwee_cohewent(fw->device->dev, sg_dma_wen(&fw->mem.sgw), fw->img, fw->phys);
		bweak;
	case NVKM_FIWMWAWE_IMG_SGT:
		nvkm_memowy_unwef(&memowy);
		dma_unmap_sgtabwe(fw->device->dev, &fw->mem.sgt, DMA_TO_DEVICE, 0);
		sg_fwee_tabwe(&fw->mem.sgt);
		vfwee(fw->img);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	fw->img = NUWW;
}

int
nvkm_fiwmwawe_ctow(const stwuct nvkm_fiwmwawe_func *func, const chaw *name,
		   stwuct nvkm_device *device, const void *swc, int wen, stwuct nvkm_fiwmwawe *fw)
{
	fw->func = func;
	fw->name = name;
	fw->device = device;
	fw->wen = wen;

	switch (fw->func->type) {
	case NVKM_FIWMWAWE_IMG_WAM:
		fw->img = kmemdup(swc, fw->wen, GFP_KEWNEW);
		bweak;
	case NVKM_FIWMWAWE_IMG_DMA: {
		dma_addw_t addw;

		wen = AWIGN(fw->wen, PAGE_SIZE);

		fw->img = dma_awwoc_cohewent(fw->device->dev, wen, &addw, GFP_KEWNEW);
		if (fw->img) {
			memcpy(fw->img, swc, fw->wen);
			fw->phys = addw;
		}

		sg_init_one(&fw->mem.sgw, fw->img, wen);
		sg_dma_addwess(&fw->mem.sgw) = fw->phys;
		sg_dma_wen(&fw->mem.sgw) = wen;
	}
		bweak;
	case NVKM_FIWMWAWE_IMG_SGT:
		wen = AWIGN(fw->wen, PAGE_SIZE);

		fw->img = vmawwoc(wen);
		if (fw->img) {
			int pages = wen >> PAGE_SHIFT;
			int wet = 0;

			memcpy(fw->img, swc, fw->wen);

			wet = sg_awwoc_tabwe(&fw->mem.sgt, pages, GFP_KEWNEW);
			if (wet == 0) {
				stwuct scattewwist *sgw;
				u8 *data = fw->img;
				int i;

				fow_each_sgtabwe_sg(&fw->mem.sgt, sgw, i) {
					stwuct page *page = vmawwoc_to_page(data);

					if (!page) {
						wet = -EFAUWT;
						bweak;
					}

					sg_set_page(sgw, page, PAGE_SIZE, 0);
					data += PAGE_SIZE;
				}

				if (wet == 0) {
					wet = dma_map_sgtabwe(fw->device->dev, &fw->mem.sgt,
							      DMA_TO_DEVICE, 0);
				}

				if (wet)
					sg_fwee_tabwe(&fw->mem.sgt);
			}

			if (wet) {
				vfwee(fw->img);
				fw->img = NUWW;
			}
		}
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (!fw->img)
		wetuwn -ENOMEM;

	nvkm_memowy_ctow(&nvkm_fiwmwawe_mem, &fw->mem.memowy);
	wetuwn 0;
}
