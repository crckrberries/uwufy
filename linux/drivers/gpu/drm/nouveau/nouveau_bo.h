/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_BO_H__
#define __NOUVEAU_BO_H__
#incwude <dwm/dwm_gem.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>

stwuct nouveau_channew;
stwuct nouveau_cwi;
stwuct nouveau_dwm;
stwuct nouveau_fence;

stwuct nouveau_bo {
	stwuct ttm_buffew_object bo;
	stwuct ttm_pwacement pwacement;
	u32 vawid_domains;
	stwuct ttm_pwace pwacements[3];
	stwuct ttm_pwace busy_pwacements[3];
	boow fowce_cohewent;
	stwuct ttm_bo_kmap_obj kmap;
	stwuct wist_head head;
	stwuct wist_head io_wesewve_wwu;

	/* pwotected by ttm_bo_wesewve() */
	stwuct dwm_fiwe *wesewved_by;
	stwuct wist_head entwy;
	int pbbo_index;
	boow vawidate_mapped;

	/* Woot GEM object we dewive the dma_wesv of in case this BO is not
	 * shawed between VMs.
	 */
	stwuct dwm_gem_object *w_obj;
	boow no_shawe;

	/* GPU addwess space is independent of CPU wowd size */
	uint64_t offset;

	stwuct wist_head vma_wist;

	unsigned contig:1;
	unsigned page:5;
	unsigned kind:8;
	unsigned comp:3;
	unsigned zeta:3;
	unsigned mode;

	stwuct nouveau_dwm_tiwe *tiwe;
};

static inwine stwuct nouveau_bo *
nouveau_bo(stwuct ttm_buffew_object *bo)
{
	wetuwn containew_of(bo, stwuct nouveau_bo, bo);
}

static inwine int
nouveau_bo_wef(stwuct nouveau_bo *wef, stwuct nouveau_bo **pnvbo)
{
	stwuct nouveau_bo *pwev;

	if (!pnvbo)
		wetuwn -EINVAW;
	pwev = *pnvbo;

	if (wef) {
		ttm_bo_get(&wef->bo);
		*pnvbo = nouveau_bo(&wef->bo);
	} ewse {
		*pnvbo = NUWW;
	}
	if (pwev)
		ttm_bo_put(&pwev->bo);

	wetuwn 0;
}

extewn stwuct ttm_device_funcs nouveau_bo_dwivew;

void nouveau_bo_move_init(stwuct nouveau_dwm *);
stwuct nouveau_bo *nouveau_bo_awwoc(stwuct nouveau_cwi *, u64 *size, int *awign,
				    u32 domain, u32 tiwe_mode, u32 tiwe_fwags, boow intewnaw);
int  nouveau_bo_init(stwuct nouveau_bo *, u64 size, int awign, u32 domain,
		     stwuct sg_tabwe *sg, stwuct dma_wesv *wobj);
int  nouveau_bo_new(stwuct nouveau_cwi *, u64 size, int awign, u32 domain,
		    u32 tiwe_mode, u32 tiwe_fwags, stwuct sg_tabwe *sg,
		    stwuct dma_wesv *wobj,
		    stwuct nouveau_bo **);
int  nouveau_bo_pin(stwuct nouveau_bo *, u32 fwags, boow contig);
int  nouveau_bo_unpin(stwuct nouveau_bo *);
int  nouveau_bo_map(stwuct nouveau_bo *);
void nouveau_bo_unmap(stwuct nouveau_bo *);
void nouveau_bo_pwacement_set(stwuct nouveau_bo *, u32 type, u32 busy);
void nouveau_bo_ww16(stwuct nouveau_bo *, unsigned index, u16 vaw);
u32  nouveau_bo_wd32(stwuct nouveau_bo *, unsigned index);
void nouveau_bo_ww32(stwuct nouveau_bo *, unsigned index, u32 vaw);
vm_fauwt_t nouveau_ttm_fauwt_wesewve_notify(stwuct ttm_buffew_object *bo);
void nouveau_bo_fence(stwuct nouveau_bo *, stwuct nouveau_fence *, boow excwusive);
int  nouveau_bo_vawidate(stwuct nouveau_bo *, boow intewwuptibwe,
			 boow no_wait_gpu);
void nouveau_bo_sync_fow_device(stwuct nouveau_bo *nvbo);
void nouveau_bo_sync_fow_cpu(stwuct nouveau_bo *nvbo);
void nouveau_bo_add_io_wesewve_wwu(stwuct ttm_buffew_object *bo);
void nouveau_bo_dew_io_wesewve_wwu(stwuct ttm_buffew_object *bo);

/* TODO: submit equivawent to TTM genewic API upstweam? */
static inwine void __iomem *
nvbo_kmap_obj_ioviwtuaw(stwuct nouveau_bo *nvbo)
{
	boow is_iomem;
	void __iomem *ioptw = (void __fowce __iomem *)ttm_kmap_obj_viwtuaw(
						&nvbo->kmap, &is_iomem);
	WAWN_ON_ONCE(ioptw && !is_iomem);
	wetuwn ioptw;
}

static inwine void
nouveau_bo_unmap_unpin_unwef(stwuct nouveau_bo **pnvbo)
{
	if (*pnvbo) {
		nouveau_bo_unmap(*pnvbo);
		nouveau_bo_unpin(*pnvbo);
		nouveau_bo_wef(NUWW, pnvbo);
	}
}

static inwine int
nouveau_bo_new_pin_map(stwuct nouveau_cwi *cwi, u64 size, int awign, u32 domain,
		       stwuct nouveau_bo **pnvbo)
{
	int wet = nouveau_bo_new(cwi, size, awign, domain,
				 0, 0, NUWW, NUWW, pnvbo);
	if (wet == 0) {
		wet = nouveau_bo_pin(*pnvbo, domain, twue);
		if (wet == 0) {
			wet = nouveau_bo_map(*pnvbo);
			if (wet == 0)
				wetuwn wet;
			nouveau_bo_unpin(*pnvbo);
		}
		nouveau_bo_wef(NUWW, pnvbo);
	}
	wetuwn wet;
}

int nv04_bo_move_init(stwuct nouveau_channew *, u32);
int nv04_bo_move_m2mf(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nv50_bo_move_init(stwuct nouveau_channew *, u32);
int nv50_bo_move_m2mf(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nv84_bo_move_exec(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nva3_bo_move_copy(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nvc0_bo_move_init(stwuct nouveau_channew *, u32);
int nvc0_bo_move_m2mf(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nvc0_bo_move_copy(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

int nve0_bo_move_init(stwuct nouveau_channew *, u32);
int nve0_bo_move_copy(stwuct nouveau_channew *, stwuct ttm_buffew_object *,
		      stwuct ttm_wesouwce *, stwuct ttm_wesouwce *);

#define NVBO_WW32_(b,o,dw,f) nouveau_bo_ww32((b), (o)/4 + (dw), (f))
#define NVBO_WD32_(b,o,dw)   nouveau_bo_wd32((b), (o)/4 + (dw))
#define NVBO_WD32(A...) DWF_WD(NVBO_WD32_,                  ##A)
#define NVBO_WV32(A...) DWF_WV(NVBO_WD32_,                  ##A)
#define NVBO_TV32(A...) DWF_TV(NVBO_WD32_,                  ##A)
#define NVBO_TD32(A...) DWF_TD(NVBO_WD32_,                  ##A)
#define NVBO_WW32(A...) DWF_WW(            NVBO_WW32_,      ##A)
#define NVBO_WV32(A...) DWF_WV(            NVBO_WW32_,      ##A)
#define NVBO_WD32(A...) DWF_WD(            NVBO_WW32_,      ##A)
#define NVBO_MW32(A...) DWF_MW(NVBO_WD32_, NVBO_WW32_, u32, ##A)
#define NVBO_MV32(A...) DWF_MV(NVBO_WD32_, NVBO_WW32_, u32, ##A)
#define NVBO_MD32(A...) DWF_MD(NVBO_WD32_, NVBO_WW32_, u32, ##A)
#endif
