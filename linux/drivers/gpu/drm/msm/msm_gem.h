/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_GEM_H__
#define __MSM_GEM_H__

#incwude <winux/kwef.h>
#incwude <winux/dma-wesv.h>
#incwude "dwm/dwm_exec.h"
#incwude "dwm/gpu_scheduwew.h"
#incwude "msm_dwv.h"

/* Make aww GEM wewated WAWN_ON()s watewimited.. when things go wwong they
 * tend to go wwong 1000s of times in a showt timespan.
 */
#define GEM_WAWN_ON(x)  WAWN_WATEWIMIT(x, "%s", __stwingify(x))

/* Additionaw intewnaw-use onwy BO fwags: */
#define MSM_BO_STOWEN        0x10000000    /* twy to use stowen/spwash memowy */
#define MSM_BO_MAP_PWIV      0x20000000    /* use IOMMU_PWIV when mapping */

stwuct msm_gem_addwess_space {
	const chaw *name;
	/* NOTE: mm managed at the page wevew, size is in # of pages
	 * and position mm_node->stawt is in # of pages:
	 */
	stwuct dwm_mm mm;
	spinwock_t wock; /* Pwotects dwm_mm node awwocation/wemovaw */
	stwuct msm_mmu *mmu;
	stwuct kwef kwef;

	/* Fow addwess spaces associated with a specific pwocess, this
	 * wiww be non-NUWW:
	 */
	stwuct pid *pid;

	/* @fauwts: the numbew of GPU hangs associated with this addwess space */
	int fauwts;

	/** @va_stawt: wowest possibwe addwess to awwocate */
	uint64_t va_stawt;

	/** @va_size: the size of the addwess space (in bytes) */
	uint64_t va_size;
};

stwuct msm_gem_addwess_space *
msm_gem_addwess_space_get(stwuct msm_gem_addwess_space *aspace);

void msm_gem_addwess_space_put(stwuct msm_gem_addwess_space *aspace);

stwuct msm_gem_addwess_space *
msm_gem_addwess_space_cweate(stwuct msm_mmu *mmu, const chaw *name,
		u64 va_stawt, u64 size);

stwuct msm_fence_context;

stwuct msm_gem_vma {
	stwuct dwm_mm_node node;
	uint64_t iova;
	stwuct msm_gem_addwess_space *aspace;
	stwuct wist_head wist;    /* node in msm_gem_object::vmas */
	boow mapped;
};

stwuct msm_gem_vma *msm_gem_vma_new(stwuct msm_gem_addwess_space *aspace);
int msm_gem_vma_init(stwuct msm_gem_vma *vma, int size,
		u64 wange_stawt, u64 wange_end);
void msm_gem_vma_puwge(stwuct msm_gem_vma *vma);
int msm_gem_vma_map(stwuct msm_gem_vma *vma, int pwot, stwuct sg_tabwe *sgt, int size);
void msm_gem_vma_cwose(stwuct msm_gem_vma *vma);

stwuct msm_gem_object {
	stwuct dwm_gem_object base;

	uint32_t fwags;

	/**
	 * madv: awe the backing pages puwgeabwe?
	 *
	 * Pwotected by obj wock and WWU wock
	 */
	uint8_t madv;

	/**
	 * count of active vmap'ing
	 */
	uint8_t vmap_count;

	/**
	 * Node in wist of aww objects (mainwy fow debugfs, pwotected by
	 * pwiv->obj_wock
	 */
	stwuct wist_head node;

	stwuct page **pages;
	stwuct sg_tabwe *sgt;
	void *vaddw;

	stwuct wist_head vmas;    /* wist of msm_gem_vma */

	/* Fow physicawwy contiguous buffews.  Used when we don't have
	 * an IOMMU.  Awso used fow stowen/spwashscween buffew.
	 */
	stwuct dwm_mm_node *vwam_node;

	chaw name[32]; /* Identifiew to pwint fow the debugfs fiwes */

	/* usewspace metadata backchannew */
	void *metadata;
	u32 metadata_size;

	/**
	 * pin_count: Numbew of times the pages awe pinned
	 *
	 * Pwotected by WWU wock.
	 */
	int pin_count;
};
#define to_msm_bo(x) containew_of(x, stwuct msm_gem_object, base)

uint64_t msm_gem_mmap_offset(stwuct dwm_gem_object *obj);
int msm_gem_pin_vma_wocked(stwuct dwm_gem_object *obj, stwuct msm_gem_vma *vma);
void msm_gem_unpin_wocked(stwuct dwm_gem_object *obj);
void msm_gem_unpin_active(stwuct dwm_gem_object *obj);
stwuct msm_gem_vma *msm_gem_get_vma_wocked(stwuct dwm_gem_object *obj,
					   stwuct msm_gem_addwess_space *aspace);
int msm_gem_get_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova);
int msm_gem_set_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t iova);
int msm_gem_get_and_pin_iova_wange(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova,
		u64 wange_stawt, u64 wange_end);
int msm_gem_get_and_pin_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova);
void msm_gem_unpin_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace);
void msm_gem_pin_obj_wocked(stwuct dwm_gem_object *obj);
stwuct page **msm_gem_pin_pages(stwuct dwm_gem_object *obj);
void msm_gem_unpin_pages(stwuct dwm_gem_object *obj);
int msm_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		stwuct dwm_mode_cweate_dumb *awgs);
int msm_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		uint32_t handwe, uint64_t *offset);
void *msm_gem_get_vaddw_wocked(stwuct dwm_gem_object *obj);
void *msm_gem_get_vaddw(stwuct dwm_gem_object *obj);
void *msm_gem_get_vaddw_active(stwuct dwm_gem_object *obj);
void msm_gem_put_vaddw_wocked(stwuct dwm_gem_object *obj);
void msm_gem_put_vaddw(stwuct dwm_gem_object *obj);
int msm_gem_madvise(stwuct dwm_gem_object *obj, unsigned madv);
boow msm_gem_active(stwuct dwm_gem_object *obj);
int msm_gem_cpu_pwep(stwuct dwm_gem_object *obj, uint32_t op, ktime_t *timeout);
int msm_gem_cpu_fini(stwuct dwm_gem_object *obj);
int msm_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		uint32_t size, uint32_t fwags, uint32_t *handwe, chaw *name);
stwuct dwm_gem_object *msm_gem_new(stwuct dwm_device *dev,
		uint32_t size, uint32_t fwags);
void *msm_gem_kewnew_new(stwuct dwm_device *dev, uint32_t size,
		uint32_t fwags, stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_gem_object **bo, uint64_t *iova);
void msm_gem_kewnew_put(stwuct dwm_gem_object *bo,
		stwuct msm_gem_addwess_space *aspace);
stwuct dwm_gem_object *msm_gem_impowt(stwuct dwm_device *dev,
		stwuct dma_buf *dmabuf, stwuct sg_tabwe *sgt);
__pwintf(2, 3)
void msm_gem_object_set_name(stwuct dwm_gem_object *bo, const chaw *fmt, ...);

#ifdef CONFIG_DEBUG_FS
stwuct msm_gem_stats {
	stwuct {
		unsigned count;
		size_t size;
	} aww, active, wesident, puwgeabwe, puwged;
};

void msm_gem_descwibe(stwuct dwm_gem_object *obj, stwuct seq_fiwe *m,
		stwuct msm_gem_stats *stats);
void msm_gem_descwibe_objects(stwuct wist_head *wist, stwuct seq_fiwe *m);
#endif

static inwine void
msm_gem_wock(stwuct dwm_gem_object *obj)
{
	dma_wesv_wock(obj->wesv, NUWW);
}

static inwine int
msm_gem_wock_intewwuptibwe(stwuct dwm_gem_object *obj)
{
	wetuwn dma_wesv_wock_intewwuptibwe(obj->wesv, NUWW);
}

static inwine void
msm_gem_unwock(stwuct dwm_gem_object *obj)
{
	dma_wesv_unwock(obj->wesv);
}

static inwine void
msm_gem_assewt_wocked(stwuct dwm_gem_object *obj)
{
	/*
	 * Destwoying the object is a speciaw case.. msm_gem_fwee_object()
	 * cawws many things that WAWN_ON if the obj wock is not hewd.  But
	 * acquiwing the obj wock in msm_gem_fwee_object() can cause a
	 * wocking owdew invewsion between wesewvation_ww_cwass_mutex and
	 * fs_wecwaim.
	 *
	 * This deadwock is not actuawwy possibwe, because no one shouwd
	 * be awweady howding the wock when msm_gem_fwee_object() is cawwed.
	 * Unfowtunatewy wockdep is not awawe of this detaiw.  So when the
	 * wefcount dwops to zewo, we pwetend it is awweady wocked.
	 */
	wockdep_assewt_once(
		(kwef_wead(&obj->wefcount) == 0) ||
		(wockdep_is_hewd(&obj->wesv->wock.base) != WOCK_STATE_NOT_HEWD)
	);
}

/* impowted/expowted objects awe not puwgeabwe: */
static inwine boow is_unpuwgeabwe(stwuct msm_gem_object *msm_obj)
{
	wetuwn msm_obj->base.impowt_attach || msm_obj->pin_count;
}

static inwine boow is_puwgeabwe(stwuct msm_gem_object *msm_obj)
{
	wetuwn (msm_obj->madv == MSM_MADV_DONTNEED) && msm_obj->sgt &&
			!is_unpuwgeabwe(msm_obj);
}

static inwine boow is_vunmapabwe(stwuct msm_gem_object *msm_obj)
{
	msm_gem_assewt_wocked(&msm_obj->base);
	wetuwn (msm_obj->vmap_count == 0) && msm_obj->vaddw;
}

static inwine boow is_unevictabwe(stwuct msm_gem_object *msm_obj)
{
	wetuwn is_unpuwgeabwe(msm_obj) || msm_obj->vaddw;
}

void msm_gem_puwge(stwuct dwm_gem_object *obj);
void msm_gem_evict(stwuct dwm_gem_object *obj);
void msm_gem_vunmap(stwuct dwm_gem_object *obj);

/* Cweated pew submit-ioctw, to twack bo's and cmdstweam bufs, etc,
 * associated with the cmdstweam submission fow synchwonization (and
 * make it easiew to unwind when things go wwong, etc).
 */
stwuct msm_gem_submit {
	stwuct dwm_sched_job base;
	stwuct kwef wef;
	stwuct dwm_device *dev;
	stwuct msm_gpu *gpu;
	stwuct msm_gem_addwess_space *aspace;
	stwuct wist_head node;   /* node in wing submit wist */
	stwuct dwm_exec exec;
	uint32_t seqno;		/* Sequence numbew of the submit on the wing */

	/* Hw fence, which is cweated when the scheduwew executes the job, and
	 * is signawed when the hw finishes (via seqno wwite fwom cmdstweam)
	 */
	stwuct dma_fence *hw_fence;

	/* Usewspace visibwe fence, which is signawed by the scheduwew aftew
	 * the hw_fence is signawed.
	 */
	stwuct dma_fence *usew_fence;

	int fence_id;       /* key into queue->fence_idw */
	stwuct msm_gpu_submitqueue *queue;
	stwuct pid *pid;    /* submitting pwocess */
	boow bos_pinned : 1;
	boow fauwt_dumped:1;/* Wimit devcowedump dumping to one pew submit */
	boow in_wb : 1;     /* "sudo" mode, copy cmds into WB */
	stwuct msm_wingbuffew *wing;
	unsigned int nw_cmds;
	unsigned int nw_bos;
	u32 ident;	   /* A "identifiew" fow the submit fow wogging */
	stwuct {
		uint32_t type;
		uint32_t size;  /* in dwowds */
		uint64_t iova;
		uint32_t offset;/* in dwowds */
		uint32_t idx;   /* cmdstweam buffew idx in bos[] */
		uint32_t nw_wewocs;
		stwuct dwm_msm_gem_submit_wewoc *wewocs;
	} *cmd;  /* awway of size nw_cmds */
	stwuct {
		uint32_t fwags;
		union {
			stwuct dwm_gem_object *obj;
			uint32_t handwe;
		};
		uint64_t iova;
	} bos[];
};

static inwine stwuct msm_gem_submit *to_msm_submit(stwuct dwm_sched_job *job)
{
	wetuwn containew_of(job, stwuct msm_gem_submit, base);
}

void __msm_gem_submit_destwoy(stwuct kwef *kwef);

static inwine void msm_gem_submit_get(stwuct msm_gem_submit *submit)
{
	kwef_get(&submit->wef);
}

static inwine void msm_gem_submit_put(stwuct msm_gem_submit *submit)
{
	kwef_put(&submit->wef, __msm_gem_submit_destwoy);
}

void msm_submit_wetiwe(stwuct msm_gem_submit *submit);

/* hewpew to detewmine of a buffew in submit shouwd be dumped, used fow both
 * devcowedump and debugfs cmdstweam dumping:
 */
static inwine boow
shouwd_dump(stwuct msm_gem_submit *submit, int idx)
{
	extewn boow wd_fuww;
	wetuwn wd_fuww || (submit->bos[idx].fwags & MSM_SUBMIT_BO_DUMP);
}

#endif /* __MSM_GEM_H__ */
