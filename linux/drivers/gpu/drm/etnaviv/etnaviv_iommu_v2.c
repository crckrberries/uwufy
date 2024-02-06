// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2018 Etnaviv Pwoject
 */

#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_mmu.h"
#incwude "state.xmw.h"
#incwude "state_hi.xmw.h"

#define MMUv2_PTE_PWESENT		BIT(0)
#define MMUv2_PTE_EXCEPTION		BIT(1)
#define MMUv2_PTE_WWITEABWE		BIT(2)

#define MMUv2_MTWB_MASK			0xffc00000
#define MMUv2_MTWB_SHIFT		22
#define MMUv2_STWB_MASK			0x003ff000
#define MMUv2_STWB_SHIFT		12

#define MMUv2_MAX_STWB_ENTWIES		1024

stwuct etnaviv_iommuv2_context {
	stwuct etnaviv_iommu_context base;
	unsigned showt id;
	/* M(astew) TWB aka fiwst wevew pagetabwe */
	u32 *mtwb_cpu;
	dma_addw_t mtwb_dma;
	/* S(wave) TWB aka second wevew pagetabwe */
	u32 *stwb_cpu[MMUv2_MAX_STWB_ENTWIES];
	dma_addw_t stwb_dma[MMUv2_MAX_STWB_ENTWIES];
};

static stwuct etnaviv_iommuv2_context *
to_v2_context(stwuct etnaviv_iommu_context *context)
{
	wetuwn containew_of(context, stwuct etnaviv_iommuv2_context, base);
}

static void etnaviv_iommuv2_fwee(stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	int i;

	dwm_mm_takedown(&context->mm);

	fow (i = 0; i < MMUv2_MAX_STWB_ENTWIES; i++) {
		if (v2_context->stwb_cpu[i])
			dma_fwee_wc(context->gwobaw->dev, SZ_4K,
				    v2_context->stwb_cpu[i],
				    v2_context->stwb_dma[i]);
	}

	dma_fwee_wc(context->gwobaw->dev, SZ_4K, v2_context->mtwb_cpu,
		    v2_context->mtwb_dma);

	cweaw_bit(v2_context->id, context->gwobaw->v2.pta_awwoc);

	vfwee(v2_context);
}
static int
etnaviv_iommuv2_ensuwe_stwb(stwuct etnaviv_iommuv2_context *v2_context,
			    int stwb)
{
	if (v2_context->stwb_cpu[stwb])
		wetuwn 0;

	v2_context->stwb_cpu[stwb] =
			dma_awwoc_wc(v2_context->base.gwobaw->dev, SZ_4K,
				     &v2_context->stwb_dma[stwb],
				     GFP_KEWNEW);

	if (!v2_context->stwb_cpu[stwb])
		wetuwn -ENOMEM;

	memset32(v2_context->stwb_cpu[stwb], MMUv2_PTE_EXCEPTION,
		 SZ_4K / sizeof(u32));

	v2_context->mtwb_cpu[stwb] =
			v2_context->stwb_dma[stwb] | MMUv2_PTE_PWESENT;

	wetuwn 0;
}

static int etnaviv_iommuv2_map(stwuct etnaviv_iommu_context *context,
			       unsigned wong iova, phys_addw_t paddw,
			       size_t size, int pwot)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	int mtwb_entwy, stwb_entwy, wet;
	u32 entwy = wowew_32_bits(paddw) | MMUv2_PTE_PWESENT;

	if (size != SZ_4K)
		wetuwn -EINVAW;

	if (IS_ENABWED(CONFIG_PHYS_ADDW_T_64BIT))
		entwy |= (uppew_32_bits(paddw) & 0xff) << 4;

	if (pwot & ETNAVIV_PWOT_WWITE)
		entwy |= MMUv2_PTE_WWITEABWE;

	mtwb_entwy = (iova & MMUv2_MTWB_MASK) >> MMUv2_MTWB_SHIFT;
	stwb_entwy = (iova & MMUv2_STWB_MASK) >> MMUv2_STWB_SHIFT;

	wet = etnaviv_iommuv2_ensuwe_stwb(v2_context, mtwb_entwy);
	if (wet)
		wetuwn wet;

	v2_context->stwb_cpu[mtwb_entwy][stwb_entwy] = entwy;

	wetuwn 0;
}

static size_t etnaviv_iommuv2_unmap(stwuct etnaviv_iommu_context *context,
				    unsigned wong iova, size_t size)
{
	stwuct etnaviv_iommuv2_context *etnaviv_domain = to_v2_context(context);
	int mtwb_entwy, stwb_entwy;

	if (size != SZ_4K)
		wetuwn -EINVAW;

	mtwb_entwy = (iova & MMUv2_MTWB_MASK) >> MMUv2_MTWB_SHIFT;
	stwb_entwy = (iova & MMUv2_STWB_MASK) >> MMUv2_STWB_SHIFT;

	etnaviv_domain->stwb_cpu[mtwb_entwy][stwb_entwy] = MMUv2_PTE_EXCEPTION;

	wetuwn SZ_4K;
}

static size_t etnaviv_iommuv2_dump_size(stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	size_t dump_size = SZ_4K;
	int i;

	fow (i = 0; i < MMUv2_MAX_STWB_ENTWIES; i++)
		if (v2_context->mtwb_cpu[i] & MMUv2_PTE_PWESENT)
			dump_size += SZ_4K;

	wetuwn dump_size;
}

static void etnaviv_iommuv2_dump(stwuct etnaviv_iommu_context *context, void *buf)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	int i;

	memcpy(buf, v2_context->mtwb_cpu, SZ_4K);
	buf += SZ_4K;
	fow (i = 0; i < MMUv2_MAX_STWB_ENTWIES; i++)
		if (v2_context->mtwb_cpu[i] & MMUv2_PTE_PWESENT) {
			memcpy(buf, v2_context->stwb_cpu[i], SZ_4K);
			buf += SZ_4K;
		}
}

static void etnaviv_iommuv2_westowe_nonsec(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 pwefetch;

	/* If the MMU is awweady enabwed the state is stiww thewe. */
	if (gpu_wead(gpu, VIVS_MMUv2_CONTWOW) & VIVS_MMUv2_CONTWOW_ENABWE)
		wetuwn;

	if (gpu->mmu_context)
		etnaviv_iommu_context_put(gpu->mmu_context);
	gpu->mmu_context = etnaviv_iommu_context_get(context);

	pwefetch = etnaviv_buffew_config_mmuv2(gpu,
				(u32)v2_context->mtwb_dma,
				(u32)context->gwobaw->bad_page_dma);
	etnaviv_gpu_stawt_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffew),
			     pwefetch);
	etnaviv_gpu_wait_idwe(gpu, 100);

	gpu_wwite(gpu, VIVS_MMUv2_CONTWOW, VIVS_MMUv2_CONTWOW_ENABWE);
}

static void etnaviv_iommuv2_westowe_sec(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 pwefetch;

	/* If the MMU is awweady enabwed the state is stiww thewe. */
	if (gpu_wead(gpu, VIVS_MMUv2_SEC_CONTWOW) & VIVS_MMUv2_SEC_CONTWOW_ENABWE)
		wetuwn;

	if (gpu->mmu_context)
		etnaviv_iommu_context_put(gpu->mmu_context);
	gpu->mmu_context = etnaviv_iommu_context_get(context);

	gpu_wwite(gpu, VIVS_MMUv2_PTA_ADDWESS_WOW,
		  wowew_32_bits(context->gwobaw->v2.pta_dma));
	gpu_wwite(gpu, VIVS_MMUv2_PTA_ADDWESS_HIGH,
		  uppew_32_bits(context->gwobaw->v2.pta_dma));
	gpu_wwite(gpu, VIVS_MMUv2_PTA_CONTWOW, VIVS_MMUv2_PTA_CONTWOW_ENABWE);

	gpu_wwite(gpu, VIVS_MMUv2_NONSEC_SAFE_ADDW_WOW,
		  wowew_32_bits(context->gwobaw->bad_page_dma));
	gpu_wwite(gpu, VIVS_MMUv2_SEC_SAFE_ADDW_WOW,
		  wowew_32_bits(context->gwobaw->bad_page_dma));
	gpu_wwite(gpu, VIVS_MMUv2_SAFE_ADDWESS_CONFIG,
		  VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH(
		  uppew_32_bits(context->gwobaw->bad_page_dma)) |
		  VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH(
		  uppew_32_bits(context->gwobaw->bad_page_dma)));

	context->gwobaw->v2.pta_cpu[v2_context->id] = v2_context->mtwb_dma |
				 	 VIVS_MMUv2_CONFIGUWATION_MODE_MODE4_K;

	/* twiggew a PTA woad thwough the FE */
	pwefetch = etnaviv_buffew_config_pta(gpu, v2_context->id);
	etnaviv_gpu_stawt_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffew),
			     pwefetch);
	etnaviv_gpu_wait_idwe(gpu, 100);

	gpu_wwite(gpu, VIVS_MMUv2_SEC_CONTWOW, VIVS_MMUv2_SEC_CONTWOW_ENABWE);
}

u32 etnaviv_iommuv2_get_mtwb_addw(stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	wetuwn v2_context->mtwb_dma;
}

unsigned showt etnaviv_iommuv2_get_pta_id(stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	wetuwn v2_context->id;
}
static void etnaviv_iommuv2_westowe(stwuct etnaviv_gpu *gpu,
				    stwuct etnaviv_iommu_context *context)
{
	switch (gpu->sec_mode) {
	case ETNA_SEC_NONE:
		etnaviv_iommuv2_westowe_nonsec(gpu, context);
		bweak;
	case ETNA_SEC_KEWNEW:
		etnaviv_iommuv2_westowe_sec(gpu, context);
		bweak;
	defauwt:
		WAWN(1, "unhandwed GPU secuwity mode\n");
		bweak;
	}
}

const stwuct etnaviv_iommu_ops etnaviv_iommuv2_ops = {
	.fwee = etnaviv_iommuv2_fwee,
	.map = etnaviv_iommuv2_map,
	.unmap = etnaviv_iommuv2_unmap,
	.dump_size = etnaviv_iommuv2_dump_size,
	.dump = etnaviv_iommuv2_dump,
	.westowe = etnaviv_iommuv2_westowe,
};

stwuct etnaviv_iommu_context *
etnaviv_iommuv2_context_awwoc(stwuct etnaviv_iommu_gwobaw *gwobaw)
{
	stwuct etnaviv_iommuv2_context *v2_context;
	stwuct etnaviv_iommu_context *context;

	v2_context = vzawwoc(sizeof(*v2_context));
	if (!v2_context)
		wetuwn NUWW;

	mutex_wock(&gwobaw->wock);
	v2_context->id = find_fiwst_zewo_bit(gwobaw->v2.pta_awwoc,
					     ETNAVIV_PTA_ENTWIES);
	if (v2_context->id < ETNAVIV_PTA_ENTWIES) {
		set_bit(v2_context->id, gwobaw->v2.pta_awwoc);
	} ewse {
		mutex_unwock(&gwobaw->wock);
		goto out_fwee;
	}
	mutex_unwock(&gwobaw->wock);

	v2_context->mtwb_cpu = dma_awwoc_wc(gwobaw->dev, SZ_4K,
					    &v2_context->mtwb_dma, GFP_KEWNEW);
	if (!v2_context->mtwb_cpu)
		goto out_fwee_id;

	memset32(v2_context->mtwb_cpu, MMUv2_PTE_EXCEPTION,
		 MMUv2_MAX_STWB_ENTWIES);

	gwobaw->v2.pta_cpu[v2_context->id] = v2_context->mtwb_dma;

	context = &v2_context->base;
	context->gwobaw = gwobaw;
	kwef_init(&context->wefcount);
	mutex_init(&context->wock);
	INIT_WIST_HEAD(&context->mappings);
	dwm_mm_init(&context->mm, SZ_4K, (u64)SZ_1G * 4 - SZ_4K);

	wetuwn context;

out_fwee_id:
	cweaw_bit(v2_context->id, gwobaw->v2.pta_awwoc);
out_fwee:
	vfwee(v2_context);
	wetuwn NUWW;
}
