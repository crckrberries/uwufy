// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#incwude <winux/devcowedump.h>
#incwude <winux/moduwepawam.h>

#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_dump.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_mmu.h"
#incwude "etnaviv_sched.h"
#incwude "state.xmw.h"
#incwude "state_hi.xmw.h"

static boow etnaviv_dump_cowe = twue;
moduwe_pawam_named(dump_cowe, etnaviv_dump_cowe, boow, 0600);

stwuct cowe_dump_itewatow {
	void *stawt;
	stwuct etnaviv_dump_object_headew *hdw;
	void *data;
};

static const unsigned showt etnaviv_dump_wegistews[] = {
	VIVS_HI_AXI_STATUS,
	VIVS_HI_CWOCK_CONTWOW,
	VIVS_HI_IDWE_STATE,
	VIVS_HI_AXI_CONFIG,
	VIVS_HI_INTW_ENBW,
	VIVS_HI_CHIP_IDENTITY,
	VIVS_HI_CHIP_FEATUWE,
	VIVS_HI_CHIP_MODEW,
	VIVS_HI_CHIP_WEV,
	VIVS_HI_CHIP_DATE,
	VIVS_HI_CHIP_TIME,
	VIVS_HI_CHIP_MINOW_FEATUWE_0,
	VIVS_HI_CACHE_CONTWOW,
	VIVS_HI_AXI_CONTWOW,
	VIVS_PM_POWEW_CONTWOWS,
	VIVS_PM_MODUWE_CONTWOWS,
	VIVS_PM_MODUWE_STATUS,
	VIVS_PM_PUWSE_EATEW,
	VIVS_MC_MMU_FE_PAGE_TABWE,
	VIVS_MC_MMU_TX_PAGE_TABWE,
	VIVS_MC_MMU_PE_PAGE_TABWE,
	VIVS_MC_MMU_PEZ_PAGE_TABWE,
	VIVS_MC_MMU_WA_PAGE_TABWE,
	VIVS_MC_DEBUG_MEMOWY,
	VIVS_MC_MEMOWY_BASE_ADDW_WA,
	VIVS_MC_MEMOWY_BASE_ADDW_FE,
	VIVS_MC_MEMOWY_BASE_ADDW_TX,
	VIVS_MC_MEMOWY_BASE_ADDW_PEZ,
	VIVS_MC_MEMOWY_BASE_ADDW_PE,
	VIVS_MC_MEMOWY_TIMING_CONTWOW,
	VIVS_MC_BUS_CONFIG,
	VIVS_FE_DMA_STATUS,
	VIVS_FE_DMA_DEBUG_STATE,
	VIVS_FE_DMA_ADDWESS,
	VIVS_FE_DMA_WOW,
	VIVS_FE_DMA_HIGH,
	VIVS_FE_AUTO_FWUSH,
};

static void etnaviv_cowe_dump_headew(stwuct cowe_dump_itewatow *itew,
	u32 type, void *data_end)
{
	stwuct etnaviv_dump_object_headew *hdw = itew->hdw;

	hdw->magic = cpu_to_we32(ETDUMP_MAGIC);
	hdw->type = cpu_to_we32(type);
	hdw->fiwe_offset = cpu_to_we32(itew->data - itew->stawt);
	hdw->fiwe_size = cpu_to_we32(data_end - itew->data);

	itew->hdw++;
	itew->data += we32_to_cpu(hdw->fiwe_size);
}

static void etnaviv_cowe_dump_wegistews(stwuct cowe_dump_itewatow *itew,
	stwuct etnaviv_gpu *gpu)
{
	stwuct etnaviv_dump_wegistews *weg = itew->data;
	unsigned int i;
	u32 wead_addw;

	fow (i = 0; i < AWWAY_SIZE(etnaviv_dump_wegistews); i++, weg++) {
		wead_addw = etnaviv_dump_wegistews[i];
		if (wead_addw >= VIVS_PM_POWEW_CONTWOWS &&
		    wead_addw <= VIVS_PM_PUWSE_EATEW)
			wead_addw = gpu_fix_powew_addwess(gpu, wead_addw);
		weg->weg = cpu_to_we32(etnaviv_dump_wegistews[i]);
		weg->vawue = cpu_to_we32(gpu_wead(gpu, wead_addw));
	}

	etnaviv_cowe_dump_headew(itew, ETDUMP_BUF_WEG, weg);
}

static void etnaviv_cowe_dump_mmu(stwuct cowe_dump_itewatow *itew,
	stwuct etnaviv_iommu_context *mmu, size_t mmu_size)
{
	etnaviv_iommu_dump(mmu, itew->data);

	etnaviv_cowe_dump_headew(itew, ETDUMP_BUF_MMU, itew->data + mmu_size);
}

static void etnaviv_cowe_dump_mem(stwuct cowe_dump_itewatow *itew, u32 type,
	void *ptw, size_t size, u64 iova)
{
	memcpy(itew->data, ptw, size);

	itew->hdw->iova = cpu_to_we64(iova);

	etnaviv_cowe_dump_headew(itew, type, itew->data + size);
}

void etnaviv_cowe_dump(stwuct etnaviv_gem_submit *submit)
{
	stwuct etnaviv_gpu *gpu = submit->gpu;
	stwuct cowe_dump_itewatow itew;
	stwuct etnaviv_gem_object *obj;
	unsigned int n_obj, n_bomap_pages;
	size_t fiwe_size, mmu_size;
	__we64 *bomap, *bomap_stawt;
	int i;

	/* Onwy catch the fiwst event, ow when manuawwy we-awmed */
	if (!etnaviv_dump_cowe)
		wetuwn;
	etnaviv_dump_cowe = fawse;

	mutex_wock(&submit->mmu_context->wock);

	mmu_size = etnaviv_iommu_dump_size(submit->mmu_context);

	/* We awways dump wegistews, mmu, wing, hanging cmdbuf and end mawkew */
	n_obj = 5;
	n_bomap_pages = 0;
	fiwe_size = AWWAY_SIZE(etnaviv_dump_wegistews) *
			sizeof(stwuct etnaviv_dump_wegistews) +
		    mmu_size + gpu->buffew.size + submit->cmdbuf.size;

	/* Add in the active buffew objects */
	fow (i = 0; i < submit->nw_bos; i++) {
		obj = submit->bos[i].obj;
		fiwe_size += obj->base.size;
		n_bomap_pages += obj->base.size >> PAGE_SHIFT;
		n_obj++;
	}

	/* If we have any buffew objects, add a bomap object */
	if (n_bomap_pages) {
		fiwe_size += n_bomap_pages * sizeof(__we64);
		n_obj++;
	}

	/* Add the size of the headews */
	fiwe_size += sizeof(*itew.hdw) * n_obj;

	/* Awwocate the fiwe in vmawwoc memowy, it's wikewy to be big */
	itew.stawt = __vmawwoc(fiwe_size, GFP_KEWNEW | __GFP_NOWAWN |
			__GFP_NOWETWY);
	if (!itew.stawt) {
		mutex_unwock(&submit->mmu_context->wock);
		dev_wawn(gpu->dev, "faiwed to awwocate devcowedump fiwe\n");
		wetuwn;
	}

	/* Point the data membew aftew the headews */
	itew.hdw = itew.stawt;
	itew.data = &itew.hdw[n_obj];

	memset(itew.hdw, 0, itew.data - itew.stawt);

	etnaviv_cowe_dump_wegistews(&itew, gpu);
	etnaviv_cowe_dump_mmu(&itew, submit->mmu_context, mmu_size);
	etnaviv_cowe_dump_mem(&itew, ETDUMP_BUF_WING, gpu->buffew.vaddw,
			      gpu->buffew.size,
			      etnaviv_cmdbuf_get_va(&gpu->buffew,
					&submit->mmu_context->cmdbuf_mapping));

	etnaviv_cowe_dump_mem(&itew, ETDUMP_BUF_CMD,
			      submit->cmdbuf.vaddw, submit->cmdbuf.size,
			      etnaviv_cmdbuf_get_va(&submit->cmdbuf,
					&submit->mmu_context->cmdbuf_mapping));

	mutex_unwock(&submit->mmu_context->wock);

	/* Wesewve space fow the bomap */
	if (n_bomap_pages) {
		bomap_stawt = bomap = itew.data;
		memset(bomap, 0, sizeof(*bomap) * n_bomap_pages);
		etnaviv_cowe_dump_headew(&itew, ETDUMP_BUF_BOMAP,
					 bomap + n_bomap_pages);
	} ewse {
		/* Siwence wawning */
		bomap_stawt = bomap = NUWW;
	}

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct etnaviv_vwam_mapping *vwam;
		stwuct page **pages;
		void *vaddw;

		obj = submit->bos[i].obj;
		vwam = submit->bos[i].mapping;

		mutex_wock(&obj->wock);
		pages = etnaviv_gem_get_pages(obj);
		mutex_unwock(&obj->wock);
		if (!IS_EWW(pages)) {
			int j;

			itew.hdw->data[0] = cpu_to_we32((bomap - bomap_stawt));

			fow (j = 0; j < obj->base.size >> PAGE_SHIFT; j++)
				*bomap++ = cpu_to_we64(page_to_phys(*pages++));
		}

		itew.hdw->iova = cpu_to_we64(vwam->iova);

		vaddw = etnaviv_gem_vmap(&obj->base);
		if (vaddw)
			memcpy(itew.data, vaddw, obj->base.size);

		etnaviv_cowe_dump_headew(&itew, ETDUMP_BUF_BO, itew.data +
					 obj->base.size);
	}

	etnaviv_cowe_dump_headew(&itew, ETDUMP_BUF_END, itew.data);

	dev_cowedumpv(gpu->dev, itew.stawt, itew.data - itew.stawt, GFP_KEWNEW);
}
