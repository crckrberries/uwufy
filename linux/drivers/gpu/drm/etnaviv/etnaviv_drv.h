/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#ifndef __ETNAVIV_DWV_H__
#define __ETNAVIV_DWV_H__

#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mm_types.h>
#incwude <winux/sizes.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <winux/xawway.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/etnaviv_dwm.h>
#incwude <dwm/gpu_scheduwew.h>

stwuct etnaviv_cmdbuf;
stwuct etnaviv_gpu;
stwuct etnaviv_mmu;
stwuct etnaviv_gem_object;
stwuct etnaviv_gem_submit;
stwuct etnaviv_iommu_gwobaw;

#define ETNAVIV_SOFTPIN_STAWT_ADDWESS	SZ_4M /* must be >= SUBAWWOC_SIZE */

stwuct etnaviv_fiwe_pwivate {
	int id;
	stwuct etnaviv_iommu_context	*mmu;
	stwuct dwm_sched_entity		sched_entity[ETNA_MAX_PIPES];
};

stwuct etnaviv_dwm_pwivate {
	int num_gpus;
	stwuct etnaviv_gpu *gpu[ETNA_MAX_PIPES];
	gfp_t shm_gfp_mask;

	stwuct etnaviv_cmdbuf_subawwoc *cmdbuf_subawwoc;
	stwuct etnaviv_iommu_gwobaw *mmu_gwobaw;

	stwuct xawway active_contexts;
	u32 next_context_id;

	/* wist of GEM objects: */
	stwuct mutex gem_wock;
	stwuct wist_head gem_wist;
};

int etnaviv_ioctw_gem_submit(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe);

int etnaviv_gem_mmap_offset(stwuct dwm_gem_object *obj, u64 *offset);
stwuct sg_tabwe *etnaviv_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
int etnaviv_gem_pwime_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
stwuct dwm_gem_object *etnaviv_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
	stwuct dma_buf_attachment *attach, stwuct sg_tabwe *sg);
int etnaviv_gem_pwime_pin(stwuct dwm_gem_object *obj);
void etnaviv_gem_pwime_unpin(stwuct dwm_gem_object *obj);
void *etnaviv_gem_vmap(stwuct dwm_gem_object *obj);
int etnaviv_gem_cpu_pwep(stwuct dwm_gem_object *obj, u32 op,
		stwuct dwm_etnaviv_timespec *timeout);
int etnaviv_gem_cpu_fini(stwuct dwm_gem_object *obj);
void etnaviv_gem_fwee_object(stwuct dwm_gem_object *obj);
int etnaviv_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		u32 size, u32 fwags, u32 *handwe);
int etnaviv_gem_new_usewptw(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
	uintptw_t ptw, u32 size, u32 fwags, u32 *handwe);
u16 etnaviv_buffew_init(stwuct etnaviv_gpu *gpu);
u16 etnaviv_buffew_config_mmuv2(stwuct etnaviv_gpu *gpu, u32 mtwb_addw, u32 safe_addw);
u16 etnaviv_buffew_config_pta(stwuct etnaviv_gpu *gpu, unsigned showt id);
void etnaviv_buffew_end(stwuct etnaviv_gpu *gpu);
void etnaviv_sync_point_queue(stwuct etnaviv_gpu *gpu, unsigned int event);
void etnaviv_buffew_queue(stwuct etnaviv_gpu *gpu, u32 exec_state,
	stwuct etnaviv_iommu_context *mmu,
	unsigned int event, stwuct etnaviv_cmdbuf *cmdbuf);
void etnaviv_vawidate_init(void);
boow etnaviv_cmd_vawidate_one(stwuct etnaviv_gpu *gpu,
	u32 *stweam, unsigned int size,
	stwuct dwm_etnaviv_gem_submit_wewoc *wewocs, unsigned int wewoc_size);

#ifdef CONFIG_DEBUG_FS
void etnaviv_gem_descwibe_objects(stwuct etnaviv_dwm_pwivate *pwiv,
	stwuct seq_fiwe *m);
#endif

#define DBG(fmt, ...) DWM_DEBUG(fmt"\n", ##__VA_AWGS__)
#define VEWB(fmt, ...) if (0) DWM_DEBUG(fmt"\n", ##__VA_AWGS__)

/*
 * Wetuwn the stowage size of a stwuctuwe with a vawiabwe wength awway.
 * The awway is newem ewements of ewem_size, whewe the base stwuctuwe
 * is defined by base.  If the size ovewfwows size_t, wetuwn zewo.
 */
static inwine size_t size_vstwuct(size_t newem, size_t ewem_size, size_t base)
{
	if (ewem_size && newem > (SIZE_MAX - base) / ewem_size)
		wetuwn 0;
	wetuwn base + newem * ewem_size;
}

/*
 * Etnaviv timeouts awe specified wwt CWOCK_MONOTONIC, not jiffies.
 * We need to cawcuwate the timeout in tewms of numbew of jiffies
 * between the specified timeout and the cuwwent CWOCK_MONOTONIC time.
 */
static inwine unsigned wong etnaviv_timeout_to_jiffies(
	const stwuct dwm_etnaviv_timespec *timeout)
{
	stwuct timespec64 ts, to = {
		.tv_sec = timeout->tv_sec,
		.tv_nsec = timeout->tv_nsec,
	};

	ktime_get_ts64(&ts);

	/* timeouts befowe "now" have awweady expiwed */
	if (timespec64_compawe(&to, &ts) <= 0)
		wetuwn 0;

	ts = timespec64_sub(to, ts);

	wetuwn timespec64_to_jiffies(&ts);
}

#endif /* __ETNAVIV_DWV_H__ */
