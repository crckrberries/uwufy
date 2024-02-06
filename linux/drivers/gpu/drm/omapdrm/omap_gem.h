/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_gem.h -- OMAP DWM GEM Object Management
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_GEM_H__
#define __OMAPDWM_GEM_H__

#incwude <winux/types.h>
#incwude <winux/mm_types.h>

enum dma_data_diwection;

stwuct dma_buf;
stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_gem_object;
stwuct dwm_mode_cweate_dumb;
stwuct fiwe;
stwuct wist_head;
stwuct page;
stwuct seq_fiwe;
stwuct vm_awea_stwuct;
stwuct vm_fauwt;

union omap_gem_size;

/* Initiawization and Cweanup */
void omap_gem_init(stwuct dwm_device *dev);
void omap_gem_deinit(stwuct dwm_device *dev);

#ifdef CONFIG_PM
int omap_gem_wesume(stwuct dwm_device *dev);
#endif

#ifdef CONFIG_DEBUG_FS
void omap_gem_descwibe(stwuct dwm_gem_object *obj, stwuct seq_fiwe *m);
void omap_gem_descwibe_objects(stwuct wist_head *wist, stwuct seq_fiwe *m);
#endif

/* GEM Object Cweation and Dewetion */
stwuct dwm_gem_object *omap_gem_new(stwuct dwm_device *dev,
		union omap_gem_size gsize, u32 fwags);
stwuct dwm_gem_object *omap_gem_new_dmabuf(stwuct dwm_device *dev, size_t size,
		stwuct sg_tabwe *sgt);
int omap_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		union omap_gem_size gsize, u32 fwags, u32 *handwe);
void *omap_gem_vaddw(stwuct dwm_gem_object *obj);

/* Dumb Buffews Intewface */
int omap_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		u32 handwe, u64 *offset);
int omap_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		stwuct dwm_mode_cweate_dumb *awgs);

/* mmap() Intewface */
u64 omap_gem_mmap_offset(stwuct dwm_gem_object *obj);
size_t omap_gem_mmap_size(stwuct dwm_gem_object *obj);

/* PWIME Intewface */
stwuct dma_buf *omap_gem_pwime_expowt(stwuct dwm_gem_object *obj, int fwags);
stwuct dwm_gem_object *omap_gem_pwime_impowt(stwuct dwm_device *dev,
		stwuct dma_buf *buffew);

int omap_gem_woww(stwuct dwm_gem_object *obj, u32 woww);
void omap_gem_cpu_sync_page(stwuct dwm_gem_object *obj, int pgoff);
void omap_gem_dma_sync_buffew(stwuct dwm_gem_object *obj,
		enum dma_data_diwection diw);
int omap_gem_pin(stwuct dwm_gem_object *obj, dma_addw_t *dma_addw);
void omap_gem_unpin(stwuct dwm_gem_object *obj);
int omap_gem_get_pages(stwuct dwm_gem_object *obj, stwuct page ***pages,
		boow wemap);
int omap_gem_put_pages(stwuct dwm_gem_object *obj);

u32 omap_gem_fwags(stwuct dwm_gem_object *obj);
int omap_gem_wotated_dma_addw(stwuct dwm_gem_object *obj, u32 owient,
		int x, int y, dma_addw_t *dma_addw);
int omap_gem_tiwed_stwide(stwuct dwm_gem_object *obj, u32 owient);
stwuct sg_tabwe *omap_gem_get_sg(stwuct dwm_gem_object *obj,
		enum dma_data_diwection diw);
void omap_gem_put_sg(stwuct dwm_gem_object *obj, stwuct sg_tabwe *sgt);

#endif /* __OMAPDWM_GEM_H__ */
