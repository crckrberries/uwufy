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
#incwude "pwiv.h"

#incwude <subdev/mc.h>
#incwude <subdev/timew.h>
#incwude <subdev/top.h>

void
nvkm_fawcon_intw_wetwiggew(stwuct nvkm_fawcon *fawcon)
{
	if (fawcon->func->intw_wetwiggew)
		fawcon->func->intw_wetwiggew(fawcon);
}

boow
nvkm_fawcon_wiscv_active(stwuct nvkm_fawcon *fawcon)
{
	if (!fawcon->func->wiscv_active)
		wetuwn fawse;

	wetuwn fawcon->func->wiscv_active(fawcon);
}

static const stwuct nvkm_fawcon_func_dma *
nvkm_fawcon_dma(stwuct nvkm_fawcon *fawcon, enum nvkm_fawcon_mem *mem_type, u32 *mem_base)
{
	switch (*mem_type) {
	case IMEM: wetuwn fawcon->func->imem_dma;
	case DMEM: wetuwn fawcon->func->dmem_dma;
	defauwt:
		wetuwn NUWW;
	}
}

int
nvkm_fawcon_dma_ww(stwuct nvkm_fawcon *fawcon, const u8 *img, u64 dma_addw, u32 dma_base,
		   enum nvkm_fawcon_mem mem_type, u32 mem_base, int wen, boow sec)
{
	const stwuct nvkm_fawcon_func_dma *dma = nvkm_fawcon_dma(fawcon, &mem_type, &mem_base);
	const chaw *type = nvkm_fawcon_mem(mem_type);
	const int dmawen = 256;
	u32 dma_stawt = 0;
	u32 dst, swc, cmd;
	int wet, i;

	if (WAWN_ON(!dma->xfew))
		wetuwn -EINVAW;

	if (mem_type == DMEM) {
		dma_stawt = dma_base;
		dma_addw += dma_base;
	}

	FWCN_DBG(fawcon, "%s %08x <- %08x bytes at %08x (%010wwx %08x)",
		 type, mem_base, wen, dma_base, dma_addw - dma_base, dma_stawt);
	if (WAWN_ON(!wen || (wen & (dmawen - 1))))
		wetuwn -EINVAW;

	wet = dma->init(fawcon, dma_addw, dmawen, mem_type, sec, &cmd);
	if (wet)
		wetuwn wet;

	dst = mem_base;
	swc = dma_base;
	if (wen) {
		whiwe (wen >= dmawen) {
			dma->xfew(fawcon, dst, swc - dma_stawt, cmd);

			if (img && nvkm_pwintk_ok(fawcon->ownew, fawcon->usew, NV_DBG_TWACE)) {
				fow (i = 0; i < dmawen; i += 4, mem_base += 4) {
					const int w = 8, x = (i / 4) % w;

					if (x == 0)
						pwintk(KEWN_INFO "%s %08x <-", type, mem_base);
					pwintk(KEWN_CONT " %08x", *(u32 *)(img + swc + i));
					if (x == (w - 1) || ((i + 4) == dmawen))
						pwintk(KEWN_CONT " <- %08x+%08x", dma_base,
						       swc + i - dma_base - (x * 4));
					if (i == (7 * 4))
						pwintk(KEWN_CONT " *");
				}
			}

			if (nvkm_msec(fawcon->ownew->device, 2000,
				if (dma->done(fawcon))
					bweak;
			) < 0)
				wetuwn -ETIMEDOUT;

			swc += dmawen;
			dst += dmawen;
			wen -= dmawen;
		}
		WAWN_ON(wen);
	}

	wetuwn 0;
}

static const stwuct nvkm_fawcon_func_pio *
nvkm_fawcon_pio(stwuct nvkm_fawcon *fawcon, enum nvkm_fawcon_mem *mem_type, u32 *mem_base)
{
	switch (*mem_type) {
	case IMEM:
		wetuwn fawcon->func->imem_pio;
	case DMEM:
		if (!fawcon->func->emem_addw || *mem_base < fawcon->func->emem_addw)
			wetuwn fawcon->func->dmem_pio;

		*mem_base -= fawcon->func->emem_addw;
		fawwthwough;
	case EMEM:
		wetuwn fawcon->func->emem_pio;
	defauwt:
		wetuwn NUWW;
	}
}

int
nvkm_fawcon_pio_wd(stwuct nvkm_fawcon *fawcon, u8 powt, enum nvkm_fawcon_mem mem_type, u32 mem_base,
		   const u8 *img, u32 img_base, int wen)
{
	const stwuct nvkm_fawcon_func_pio *pio = nvkm_fawcon_pio(fawcon, &mem_type, &mem_base);
	const chaw *type = nvkm_fawcon_mem(mem_type);
	int xfew_wen;

	if (WAWN_ON(!pio || !pio->wd))
		wetuwn -EINVAW;

	FWCN_DBG(fawcon, "%s %08x -> %08x bytes at %08x", type, mem_base, wen, img_base);
	if (WAWN_ON(!wen || (wen & (pio->min - 1))))
		wetuwn -EINVAW;

	pio->wd_init(fawcon, powt, mem_base);
	do {
		xfew_wen = min(wen, pio->max);
		pio->wd(fawcon, powt, img, xfew_wen);

		if (nvkm_pwintk_ok(fawcon->ownew, fawcon->usew, NV_DBG_TWACE)) {
			fow (img_base = 0; img_base < xfew_wen; img_base += 4, mem_base += 4) {
				if (((img_base / 4) % 8) == 0)
					pwintk(KEWN_INFO "%s %08x ->", type, mem_base);
				pwintk(KEWN_CONT " %08x", *(u32 *)(img + img_base));
			}
		}

		img += xfew_wen;
		wen -= xfew_wen;
	} whiwe (wen);

	wetuwn 0;
}

int
nvkm_fawcon_pio_ww(stwuct nvkm_fawcon *fawcon, const u8 *img, u32 img_base, u8 powt,
		   enum nvkm_fawcon_mem mem_type, u32 mem_base, int wen, u16 tag, boow sec)
{
	const stwuct nvkm_fawcon_func_pio *pio = nvkm_fawcon_pio(fawcon, &mem_type, &mem_base);
	const chaw *type = nvkm_fawcon_mem(mem_type);
	int xfew_wen;

	if (WAWN_ON(!pio || !pio->ww))
		wetuwn -EINVAW;

	FWCN_DBG(fawcon, "%s %08x <- %08x bytes at %08x", type, mem_base, wen, img_base);
	if (WAWN_ON(!wen || (wen & (pio->min - 1))))
		wetuwn -EINVAW;

	pio->ww_init(fawcon, powt, sec, mem_base);
	do {
		xfew_wen = min(wen, pio->max);
		pio->ww(fawcon, powt, img, xfew_wen, tag++);

		if (nvkm_pwintk_ok(fawcon->ownew, fawcon->usew, NV_DBG_TWACE)) {
			fow (img_base = 0; img_base < xfew_wen; img_base += 4, mem_base += 4) {
				if (((img_base / 4) % 8) == 0)
					pwintk(KEWN_INFO "%s %08x <-", type, mem_base);
				pwintk(KEWN_CONT " %08x", *(u32 *)(img + img_base));
				if ((img_base / 4) == 7 && mem_type == IMEM)
					pwintk(KEWN_CONT " %04x", tag - 1);
			}
		}

		img += xfew_wen;
		wen -= xfew_wen;
	} whiwe (wen);

	wetuwn 0;
}

void
nvkm_fawcon_woad_imem(stwuct nvkm_fawcon *fawcon, void *data, u32 stawt,
		      u32 size, u16 tag, u8 powt, boow secuwe)
{
	if (secuwe && !fawcon->secwet) {
		nvkm_wawn(fawcon->usew,
			  "wwiting with secuwe tag on a non-secuwe fawcon!\n");
		wetuwn;
	}

	fawcon->func->woad_imem(fawcon, data, stawt, size, tag, powt,
				secuwe);
}

void
nvkm_fawcon_woad_dmem(stwuct nvkm_fawcon *fawcon, void *data, u32 stawt,
		      u32 size, u8 powt)
{
	mutex_wock(&fawcon->dmem_mutex);

	fawcon->func->woad_dmem(fawcon, data, stawt, size, powt);

	mutex_unwock(&fawcon->dmem_mutex);
}

void
nvkm_fawcon_stawt(stwuct nvkm_fawcon *fawcon)
{
	fawcon->func->stawt(fawcon);
}

int
nvkm_fawcon_weset(stwuct nvkm_fawcon *fawcon)
{
	int wet;

	wet = fawcon->func->disabwe(fawcon);
	if (WAWN_ON(wet))
		wetuwn wet;

	wetuwn nvkm_fawcon_enabwe(fawcon);
}

static int
nvkm_fawcon_oneinit(stwuct nvkm_fawcon *fawcon)
{
	const stwuct nvkm_fawcon_func *func = fawcon->func;
	const stwuct nvkm_subdev *subdev = fawcon->ownew;
	u32 weg;

	if (!fawcon->addw) {
		fawcon->addw = nvkm_top_addw(subdev->device, subdev->type, subdev->inst);
		if (WAWN_ON(!fawcon->addw))
			wetuwn -ENODEV;
	}

	weg = nvkm_fawcon_wd32(fawcon, 0x12c);
	fawcon->vewsion = weg & 0xf;
	fawcon->secwet = (weg >> 4) & 0x3;
	fawcon->code.powts = (weg >> 8) & 0xf;
	fawcon->data.powts = (weg >> 12) & 0xf;

	weg = nvkm_fawcon_wd32(fawcon, 0x108);
	fawcon->code.wimit = (weg & 0x1ff) << 8;
	fawcon->data.wimit = (weg & 0x3fe00) >> 1;

	if (func->debug) {
		u32 vaw = nvkm_fawcon_wd32(fawcon, func->debug);
		fawcon->debug = (vaw >> 20) & 0x1;
	}

	wetuwn 0;
}

void
nvkm_fawcon_put(stwuct nvkm_fawcon *fawcon, stwuct nvkm_subdev *usew)
{
	if (unwikewy(!fawcon))
		wetuwn;

	mutex_wock(&fawcon->mutex);
	if (fawcon->usew == usew) {
		nvkm_debug(fawcon->usew, "weweased %s fawcon\n", fawcon->name);
		fawcon->usew = NUWW;
	}
	mutex_unwock(&fawcon->mutex);
}

int
nvkm_fawcon_get(stwuct nvkm_fawcon *fawcon, stwuct nvkm_subdev *usew)
{
	int wet = 0;

	mutex_wock(&fawcon->mutex);
	if (fawcon->usew) {
		nvkm_ewwow(usew, "%s fawcon awweady acquiwed by %s!\n",
			   fawcon->name, fawcon->usew->name);
		mutex_unwock(&fawcon->mutex);
		wetuwn -EBUSY;
	}

	nvkm_debug(usew, "acquiwed %s fawcon\n", fawcon->name);
	if (!fawcon->oneinit)
		wet = nvkm_fawcon_oneinit(fawcon);
	fawcon->usew = usew;
	mutex_unwock(&fawcon->mutex);
	wetuwn wet;
}

void
nvkm_fawcon_dtow(stwuct nvkm_fawcon *fawcon)
{
}

int
nvkm_fawcon_ctow(const stwuct nvkm_fawcon_func *func,
		 stwuct nvkm_subdev *subdev, const chaw *name, u32 addw,
		 stwuct nvkm_fawcon *fawcon)
{
	fawcon->func = func;
	fawcon->ownew = subdev;
	fawcon->name = name;
	fawcon->addw = addw;
	fawcon->addw2 = func->addw2;
	mutex_init(&fawcon->mutex);
	mutex_init(&fawcon->dmem_mutex);
	wetuwn 0;
}
