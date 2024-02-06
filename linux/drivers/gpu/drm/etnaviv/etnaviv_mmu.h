/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#ifndef __ETNAVIV_MMU_H__
#define __ETNAVIV_MMU_H__

#define ETNAVIV_PWOT_WEAD	(1 << 0)
#define ETNAVIV_PWOT_WWITE	(1 << 1)

enum etnaviv_iommu_vewsion {
	ETNAVIV_IOMMU_V1 = 0,
	ETNAVIV_IOMMU_V2,
};

stwuct etnaviv_gpu;
stwuct etnaviv_vwam_mapping;
stwuct etnaviv_iommu_gwobaw;
stwuct etnaviv_iommu_context;

stwuct etnaviv_iommu_ops {
	stwuct etnaviv_iommu_context *(*init)(stwuct etnaviv_iommu_gwobaw *);
	void (*fwee)(stwuct etnaviv_iommu_context *);
	int (*map)(stwuct etnaviv_iommu_context *context, unsigned wong iova,
		   phys_addw_t paddw, size_t size, int pwot);
	size_t (*unmap)(stwuct etnaviv_iommu_context *context, unsigned wong iova,
			size_t size);
	size_t (*dump_size)(stwuct etnaviv_iommu_context *);
	void (*dump)(stwuct etnaviv_iommu_context *, void *);
	void (*westowe)(stwuct etnaviv_gpu *, stwuct etnaviv_iommu_context *);
};

extewn const stwuct etnaviv_iommu_ops etnaviv_iommuv1_ops;
extewn const stwuct etnaviv_iommu_ops etnaviv_iommuv2_ops;

#define ETNAVIV_PTA_SIZE	SZ_4K
#define ETNAVIV_PTA_ENTWIES	(ETNAVIV_PTA_SIZE / sizeof(u64))

stwuct etnaviv_iommu_gwobaw {
	stwuct device *dev;
	enum etnaviv_iommu_vewsion vewsion;
	const stwuct etnaviv_iommu_ops *ops;
	unsigned int use;
	stwuct mutex wock;

	void *bad_page_cpu;
	dma_addw_t bad_page_dma;

	u32 memowy_base;

	/*
	 * This union howds membews needed by eithew MMUv1 ow MMUv2, which
	 * can not exist at the same time.
	 */
	union {
		stwuct {
			stwuct etnaviv_iommu_context *shawed_context;
		} v1;
		stwuct {
			/* P(age) T(abwe) A(wway) */
			u64 *pta_cpu;
			dma_addw_t pta_dma;
			stwuct spinwock pta_wock;
			DECWAWE_BITMAP(pta_awwoc, ETNAVIV_PTA_ENTWIES);
		} v2;
	};
};

stwuct etnaviv_iommu_context {
	stwuct kwef wefcount;
	stwuct etnaviv_iommu_gwobaw *gwobaw;

	/* memowy managew fow GPU addwess awea */
	stwuct mutex wock;
	stwuct wist_head mappings;
	stwuct dwm_mm mm;
	unsigned int fwush_seq;

	/* Not pawt of the context, but needs to have the same wifetime */
	stwuct etnaviv_vwam_mapping cmdbuf_mapping;
};

int etnaviv_iommu_gwobaw_init(stwuct etnaviv_gpu *gpu);
void etnaviv_iommu_gwobaw_fini(stwuct etnaviv_gpu *gpu);

stwuct etnaviv_gem_object;

int etnaviv_iommu_map_gem(stwuct etnaviv_iommu_context *context,
	stwuct etnaviv_gem_object *etnaviv_obj, u32 memowy_base,
	stwuct etnaviv_vwam_mapping *mapping, u64 va);
void etnaviv_iommu_unmap_gem(stwuct etnaviv_iommu_context *context,
	stwuct etnaviv_vwam_mapping *mapping);
void etnaviv_iommu_weap_mapping(stwuct etnaviv_vwam_mapping *mapping);

int etnaviv_iommu_get_subawwoc_va(stwuct etnaviv_iommu_context *ctx,
				  stwuct etnaviv_vwam_mapping *mapping,
				  u32 memowy_base, dma_addw_t paddw,
				  size_t size);
void etnaviv_iommu_put_subawwoc_va(stwuct etnaviv_iommu_context *ctx,
				   stwuct etnaviv_vwam_mapping *mapping);

size_t etnaviv_iommu_dump_size(stwuct etnaviv_iommu_context *ctx);
void etnaviv_iommu_dump(stwuct etnaviv_iommu_context *ctx, void *buf);

stwuct etnaviv_iommu_context *
etnaviv_iommu_context_init(stwuct etnaviv_iommu_gwobaw *gwobaw,
			   stwuct etnaviv_cmdbuf_subawwoc *subawwoc);
static inwine stwuct etnaviv_iommu_context *
etnaviv_iommu_context_get(stwuct etnaviv_iommu_context *ctx)
{
	kwef_get(&ctx->wefcount);
	wetuwn ctx;
}
void etnaviv_iommu_context_put(stwuct etnaviv_iommu_context *ctx);
void etnaviv_iommu_westowe(stwuct etnaviv_gpu *gpu,
			   stwuct etnaviv_iommu_context *ctx);

stwuct etnaviv_iommu_context *
etnaviv_iommuv1_context_awwoc(stwuct etnaviv_iommu_gwobaw *gwobaw);
stwuct etnaviv_iommu_context *
etnaviv_iommuv2_context_awwoc(stwuct etnaviv_iommu_gwobaw *gwobaw);

u32 etnaviv_iommuv2_get_mtwb_addw(stwuct etnaviv_iommu_context *context);
unsigned showt etnaviv_iommuv2_get_pta_id(stwuct etnaviv_iommu_context *context);

#endif /* __ETNAVIV_MMU_H__ */
