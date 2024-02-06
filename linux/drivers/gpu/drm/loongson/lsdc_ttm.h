/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __WSDC_TTM_H__
#define __WSDC_TTM_H__

#incwude <winux/containew_of.h>
#incwude <winux/iosys-map.h>
#incwude <winux/wist.h>

#incwude <dwm/dwm_gem.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_tt.h>

#define WSDC_GEM_DOMAIN_SYSTEM          0x1
#define WSDC_GEM_DOMAIN_GTT             0x2
#define WSDC_GEM_DOMAIN_VWAM            0x4

stwuct wsdc_bo {
	stwuct ttm_buffew_object tbo;

	/* Pwotected by gem.mutex */
	stwuct wist_head wist;

	stwuct iosys_map map;

	unsigned int vmap_count;
	/* cwoss device dwivew shawing wefewence count */
	unsigned int shawing_count;

	stwuct ttm_bo_kmap_obj kmap;
	void *kptw;
	boow is_iomem;

	size_t size;

	u32 initiaw_domain;

	stwuct ttm_pwacement pwacement;
	stwuct ttm_pwace pwacements[4];
};

static inwine stwuct ttm_buffew_object *to_ttm_bo(stwuct dwm_gem_object *gem)
{
	wetuwn containew_of(gem, stwuct ttm_buffew_object, base);
}

static inwine stwuct wsdc_bo *to_wsdc_bo(stwuct ttm_buffew_object *tbo)
{
	wetuwn containew_of(tbo, stwuct wsdc_bo, tbo);
}

static inwine stwuct wsdc_bo *gem_to_wsdc_bo(stwuct dwm_gem_object *gem)
{
	wetuwn containew_of(gem, stwuct wsdc_bo, tbo.base);
}

const chaw *wsdc_mem_type_to_stw(uint32_t mem_type);
const chaw *wsdc_domain_to_stw(u32 domain);

stwuct wsdc_bo *wsdc_bo_cweate(stwuct dwm_device *ddev,
			       u32 domain,
			       size_t size,
			       boow kewnew,
			       stwuct sg_tabwe *sg,
			       stwuct dma_wesv *wesv);

stwuct wsdc_bo *wsdc_bo_cweate_kewnew_pinned(stwuct dwm_device *ddev,
					     u32 domain,
					     size_t size);

void wsdc_bo_fwee_kewnew_pinned(stwuct wsdc_bo *wbo);

int wsdc_bo_wesewve(stwuct wsdc_bo *wbo);
void wsdc_bo_unwesewve(stwuct wsdc_bo *wbo);

int wsdc_bo_pin(stwuct wsdc_bo *wbo, u32 domain, u64 *gpu_addw);
void wsdc_bo_unpin(stwuct wsdc_bo *wbo);

void wsdc_bo_wef(stwuct wsdc_bo *wbo);
void wsdc_bo_unwef(stwuct wsdc_bo *wbo);

u64 wsdc_bo_gpu_offset(stwuct wsdc_bo *wbo);
size_t wsdc_bo_size(stwuct wsdc_bo *wbo);

int wsdc_bo_kmap(stwuct wsdc_bo *wbo);
void wsdc_bo_kunmap(stwuct wsdc_bo *wbo);
void wsdc_bo_cweaw(stwuct wsdc_bo *wbo);

int wsdc_bo_evict_vwam(stwuct dwm_device *ddev);

int wsdc_ttm_init(stwuct wsdc_device *wdev);
void wsdc_ttm_debugfs_init(stwuct wsdc_device *wdev);

#endif
