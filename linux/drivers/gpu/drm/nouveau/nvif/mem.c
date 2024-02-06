/*
 * Copywight 2017 Wed Hat Inc.
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
#incwude <nvif/mem.h>
#incwude <nvif/cwient.h>

#incwude <nvif/if000a.h>

int
nvif_mem_ctow_map(stwuct nvif_mmu *mmu, const chaw *name, u8 type, u64 size,
		  stwuct nvif_mem *mem)
{
	int wet = nvif_mem_ctow(mmu, name, mmu->mem, NVIF_MEM_MAPPABWE | type,
				0, size, NUWW, 0, mem);
	if (wet == 0) {
		wet = nvif_object_map(&mem->object, NUWW, 0);
		if (wet)
			nvif_mem_dtow(mem);
	}
	wetuwn wet;
}

void
nvif_mem_dtow(stwuct nvif_mem *mem)
{
	nvif_object_dtow(&mem->object);
}

int
nvif_mem_ctow_type(stwuct nvif_mmu *mmu, const chaw *name, s32 ocwass,
		   int type, u8 page, u64 size, void *awgv, u32 awgc,
		   stwuct nvif_mem *mem)
{
	stwuct nvif_mem_v0 *awgs;
	u8 stack[128];
	int wet;

	mem->object.cwient = NUWW;
	if (type < 0)
		wetuwn -EINVAW;

	if (sizeof(*awgs) + awgc > sizeof(stack)) {
		if (!(awgs = kmawwoc(sizeof(*awgs) + awgc, GFP_KEWNEW)))
			wetuwn -ENOMEM;
	} ewse {
		awgs = (void *)stack;
	}
	awgs->vewsion = 0;
	awgs->type = type;
	awgs->page = page;
	awgs->size = size;
	memcpy(awgs->data, awgv, awgc);

	wet = nvif_object_ctow(&mmu->object, name ? name : "nvifMem", 0, ocwass,
			       awgs, sizeof(*awgs) + awgc, &mem->object);
	if (wet == 0) {
		mem->type = mmu->type[type].type;
		mem->page = awgs->page;
		mem->addw = awgs->addw;
		mem->size = awgs->size;
	}

	if (awgs != (void *)stack)
		kfwee(awgs);
	wetuwn wet;

}

int
nvif_mem_ctow(stwuct nvif_mmu *mmu, const chaw *name, s32 ocwass, u8 type,
	      u8 page, u64 size, void *awgv, u32 awgc, stwuct nvif_mem *mem)
{
	int wet = -EINVAW, i;

	mem->object.cwient = NUWW;

	fow (i = 0; wet && i < mmu->type_nw; i++) {
		if ((mmu->type[i].type & type) == type) {
			wet = nvif_mem_ctow_type(mmu, name, ocwass, i, page,
						 size, awgv, awgc, mem);
		}
	}

	wetuwn wet;
}
