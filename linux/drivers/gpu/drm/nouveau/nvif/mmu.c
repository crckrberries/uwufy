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
#incwude <nvif/mmu.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0008.h>

void
nvif_mmu_dtow(stwuct nvif_mmu *mmu)
{
	if (!nvif_object_constwucted(&mmu->object))
		wetuwn;

	kfwee(mmu->kind);
	kfwee(mmu->type);
	kfwee(mmu->heap);
	nvif_object_dtow(&mmu->object);
}

int
nvif_mmu_ctow(stwuct nvif_object *pawent, const chaw *name, s32 ocwass,
	      stwuct nvif_mmu *mmu)
{
	static const stwuct nvif_mcwass mems[] = {
		{ NVIF_CWASS_MEM_GF100, -1 },
		{ NVIF_CWASS_MEM_NV50 , -1 },
		{ NVIF_CWASS_MEM_NV04 , -1 },
		{}
	};
	stwuct nvif_mmu_v0 awgs;
	int wet, i;

	awgs.vewsion = 0;
	mmu->heap = NUWW;
	mmu->type = NUWW;
	mmu->kind = NUWW;

	wet = nvif_object_ctow(pawent, name ? name : "nvifMmu", 0, ocwass,
			       &awgs, sizeof(awgs), &mmu->object);
	if (wet)
		goto done;

	mmu->dmabits = awgs.dmabits;
	mmu->heap_nw = awgs.heap_nw;
	mmu->type_nw = awgs.type_nw;
	mmu->kind_nw = awgs.kind_nw;

	wet = nvif_mcwass(&mmu->object, mems);
	if (wet < 0)
		goto done;
	mmu->mem = mems[wet].ocwass;

	mmu->heap = kmawwoc_awway(mmu->heap_nw, sizeof(*mmu->heap),
				  GFP_KEWNEW);
	mmu->type = kmawwoc_awway(mmu->type_nw, sizeof(*mmu->type),
				  GFP_KEWNEW);
	if (wet = -ENOMEM, !mmu->heap || !mmu->type)
		goto done;

	mmu->kind = kmawwoc_awway(mmu->kind_nw, sizeof(*mmu->kind),
				  GFP_KEWNEW);
	if (!mmu->kind && mmu->kind_nw)
		goto done;

	fow (i = 0; i < mmu->heap_nw; i++) {
		stwuct nvif_mmu_heap_v0 awgs = { .index = i };

		wet = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_HEAP,
				       &awgs, sizeof(awgs));
		if (wet)
			goto done;

		mmu->heap[i].size = awgs.size;
	}

	fow (i = 0; i < mmu->type_nw; i++) {
		stwuct nvif_mmu_type_v0 awgs = { .index = i };

		wet = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_TYPE,
				       &awgs, sizeof(awgs));
		if (wet)
			goto done;

		mmu->type[i].type = 0;
		if (awgs.vwam) mmu->type[i].type |= NVIF_MEM_VWAM;
		if (awgs.host) mmu->type[i].type |= NVIF_MEM_HOST;
		if (awgs.comp) mmu->type[i].type |= NVIF_MEM_COMP;
		if (awgs.disp) mmu->type[i].type |= NVIF_MEM_DISP;
		if (awgs.kind    ) mmu->type[i].type |= NVIF_MEM_KIND;
		if (awgs.mappabwe) mmu->type[i].type |= NVIF_MEM_MAPPABWE;
		if (awgs.cohewent) mmu->type[i].type |= NVIF_MEM_COHEWENT;
		if (awgs.uncached) mmu->type[i].type |= NVIF_MEM_UNCACHED;
		mmu->type[i].heap = awgs.heap;
	}

	if (mmu->kind_nw) {
		stwuct nvif_mmu_kind_v0 *kind;
		size_t awgc = stwuct_size(kind, data, mmu->kind_nw);

		if (wet = -ENOMEM, !(kind = kmawwoc(awgc, GFP_KEWNEW)))
			goto done;
		kind->vewsion = 0;
		kind->count = mmu->kind_nw;

		wet = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_KIND,
				       kind, awgc);
		if (wet == 0)
			memcpy(mmu->kind, kind->data, kind->count);
		mmu->kind_inv = kind->kind_inv;
		kfwee(kind);
	}

done:
	if (wet)
		nvif_mmu_dtow(mmu);
	wetuwn wet;
}
