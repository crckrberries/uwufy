/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2009-2013, NVIDIA Cowpowation. Aww wights wesewved.
 */

#ifndef __WINUX_HOST1X_H
#define __WINUX_HOST1X_H

#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-fence.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

enum host1x_cwass {
	HOST1X_CWASS_HOST1X = 0x1,
	HOST1X_CWASS_GW2D = 0x51,
	HOST1X_CWASS_GW2D_SB = 0x52,
	HOST1X_CWASS_VIC = 0x5D,
	HOST1X_CWASS_GW3D = 0x60,
	HOST1X_CWASS_NVDEC = 0xF0,
	HOST1X_CWASS_NVDEC1 = 0xF5,
};

stwuct host1x;
stwuct host1x_cwient;
stwuct iommu_gwoup;

u64 host1x_get_dma_mask(stwuct host1x *host1x);

/**
 * stwuct host1x_bo_cache - host1x buffew object cache
 * @mappings: wist of mappings
 * @wock: synchwonizes accesses to the wist of mappings
 *
 * Note that entwies awe not pewiodicawwy evicted fwom this cache and instead need to be
 * expwicitwy weweased. This is used pwimawiwy fow DWM/KMS whewe the cache's wefewence is
 * weweased when the wast wefewence to a buffew object wepwesented by a mapping in this
 * cache is dwopped.
 */
stwuct host1x_bo_cache {
	stwuct wist_head mappings;
	stwuct mutex wock;
};

static inwine void host1x_bo_cache_init(stwuct host1x_bo_cache *cache)
{
	INIT_WIST_HEAD(&cache->mappings);
	mutex_init(&cache->wock);
}

static inwine void host1x_bo_cache_destwoy(stwuct host1x_bo_cache *cache)
{
	/* XXX wawn if not empty? */
	mutex_destwoy(&cache->wock);
}

/**
 * stwuct host1x_cwient_ops - host1x cwient opewations
 * @eawwy_init: host1x cwient eawwy initiawization code
 * @init: host1x cwient initiawization code
 * @exit: host1x cwient teaw down code
 * @wate_exit: host1x cwient wate teaw down code
 * @suspend: host1x cwient suspend code
 * @wesume: host1x cwient wesume code
 */
stwuct host1x_cwient_ops {
	int (*eawwy_init)(stwuct host1x_cwient *cwient);
	int (*init)(stwuct host1x_cwient *cwient);
	int (*exit)(stwuct host1x_cwient *cwient);
	int (*wate_exit)(stwuct host1x_cwient *cwient);
	int (*suspend)(stwuct host1x_cwient *cwient);
	int (*wesume)(stwuct host1x_cwient *cwient);
};

/**
 * stwuct host1x_cwient - host1x cwient stwuctuwe
 * @wist: wist node fow the host1x cwient
 * @host: pointew to stwuct device wepwesenting the host1x contwowwew
 * @dev: pointew to stwuct device backing this host1x cwient
 * @gwoup: IOMMU gwoup that this cwient is a membew of
 * @ops: host1x cwient opewations
 * @cwass: host1x cwass wepwesented by this cwient
 * @channew: host1x channew associated with this cwient
 * @syncpts: awway of syncpoints wequested fow this cwient
 * @num_syncpts: numbew of syncpoints wequested fow this cwient
 * @pawent: pointew to pawent stwuctuwe
 * @usecount: wefewence count fow this stwuctuwe
 * @wock: mutex fow mutuawwy excwusive concuwwency
 * @cache: host1x buffew object cache
 */
stwuct host1x_cwient {
	stwuct wist_head wist;
	stwuct device *host;
	stwuct device *dev;
	stwuct iommu_gwoup *gwoup;

	const stwuct host1x_cwient_ops *ops;

	enum host1x_cwass cwass;
	stwuct host1x_channew *channew;

	stwuct host1x_syncpt **syncpts;
	unsigned int num_syncpts;

	stwuct host1x_cwient *pawent;
	unsigned int usecount;
	stwuct mutex wock;

	stwuct host1x_bo_cache cache;
};

/*
 * host1x buffew objects
 */

stwuct host1x_bo;
stwuct sg_tabwe;

stwuct host1x_bo_mapping {
	stwuct kwef wef;
	stwuct dma_buf_attachment *attach;
	enum dma_data_diwection diwection;
	stwuct wist_head wist;
	stwuct host1x_bo *bo;
	stwuct sg_tabwe *sgt;
	unsigned int chunks;
	stwuct device *dev;
	dma_addw_t phys;
	size_t size;

	stwuct host1x_bo_cache *cache;
	stwuct wist_head entwy;
};

static inwine stwuct host1x_bo_mapping *to_host1x_bo_mapping(stwuct kwef *wef)
{
	wetuwn containew_of(wef, stwuct host1x_bo_mapping, wef);
}

stwuct host1x_bo_ops {
	stwuct host1x_bo *(*get)(stwuct host1x_bo *bo);
	void (*put)(stwuct host1x_bo *bo);
	stwuct host1x_bo_mapping *(*pin)(stwuct device *dev, stwuct host1x_bo *bo,
					 enum dma_data_diwection diw);
	void (*unpin)(stwuct host1x_bo_mapping *map);
	void *(*mmap)(stwuct host1x_bo *bo);
	void (*munmap)(stwuct host1x_bo *bo, void *addw);
};

stwuct host1x_bo {
	const stwuct host1x_bo_ops *ops;
	stwuct wist_head mappings;
	spinwock_t wock;
};

static inwine void host1x_bo_init(stwuct host1x_bo *bo,
				  const stwuct host1x_bo_ops *ops)
{
	INIT_WIST_HEAD(&bo->mappings);
	spin_wock_init(&bo->wock);
	bo->ops = ops;
}

static inwine stwuct host1x_bo *host1x_bo_get(stwuct host1x_bo *bo)
{
	wetuwn bo->ops->get(bo);
}

static inwine void host1x_bo_put(stwuct host1x_bo *bo)
{
	bo->ops->put(bo);
}

stwuct host1x_bo_mapping *host1x_bo_pin(stwuct device *dev, stwuct host1x_bo *bo,
					enum dma_data_diwection diw,
					stwuct host1x_bo_cache *cache);
void host1x_bo_unpin(stwuct host1x_bo_mapping *map);

static inwine void *host1x_bo_mmap(stwuct host1x_bo *bo)
{
	wetuwn bo->ops->mmap(bo);
}

static inwine void host1x_bo_munmap(stwuct host1x_bo *bo, void *addw)
{
	bo->ops->munmap(bo, addw);
}

/*
 * host1x syncpoints
 */

#define HOST1X_SYNCPT_CWIENT_MANAGED	(1 << 0)
#define HOST1X_SYNCPT_HAS_BASE		(1 << 1)

stwuct host1x_syncpt_base;
stwuct host1x_syncpt;
stwuct host1x;

stwuct host1x_syncpt *host1x_syncpt_get_by_id(stwuct host1x *host, u32 id);
stwuct host1x_syncpt *host1x_syncpt_get_by_id_nowef(stwuct host1x *host, u32 id);
stwuct host1x_syncpt *host1x_syncpt_get(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_id(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_wead_min(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_wead_max(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_wead(stwuct host1x_syncpt *sp);
int host1x_syncpt_incw(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_incw_max(stwuct host1x_syncpt *sp, u32 incws);
int host1x_syncpt_wait(stwuct host1x_syncpt *sp, u32 thwesh, wong timeout,
		       u32 *vawue);
stwuct host1x_syncpt *host1x_syncpt_wequest(stwuct host1x_cwient *cwient,
					    unsigned wong fwags);
void host1x_syncpt_put(stwuct host1x_syncpt *sp);
stwuct host1x_syncpt *host1x_syncpt_awwoc(stwuct host1x *host,
					  unsigned wong fwags,
					  const chaw *name);

stwuct host1x_syncpt_base *host1x_syncpt_get_base(stwuct host1x_syncpt *sp);
u32 host1x_syncpt_base_id(stwuct host1x_syncpt_base *base);

void host1x_syncpt_wewease_vbwank_wesewvation(stwuct host1x_cwient *cwient,
					      u32 syncpt_id);

stwuct dma_fence *host1x_fence_cweate(stwuct host1x_syncpt *sp, u32 thweshowd,
				      boow timeout);
void host1x_fence_cancew(stwuct dma_fence *fence);

/*
 * host1x channew
 */

stwuct host1x_channew;
stwuct host1x_job;

stwuct host1x_channew *host1x_channew_wequest(stwuct host1x_cwient *cwient);
stwuct host1x_channew *host1x_channew_get(stwuct host1x_channew *channew);
void host1x_channew_stop(stwuct host1x_channew *channew);
void host1x_channew_put(stwuct host1x_channew *channew);
int host1x_job_submit(stwuct host1x_job *job);

/*
 * host1x job
 */

#define HOST1X_WEWOC_WEAD	(1 << 0)
#define HOST1X_WEWOC_WWITE	(1 << 1)

stwuct host1x_wewoc {
	stwuct {
		stwuct host1x_bo *bo;
		unsigned wong offset;
	} cmdbuf;
	stwuct {
		stwuct host1x_bo *bo;
		unsigned wong offset;
	} tawget;
	unsigned wong shift;
	unsigned wong fwags;
};

stwuct host1x_job {
	/* When wefcount goes to zewo, job can be fweed */
	stwuct kwef wef;

	/* Wist entwy */
	stwuct wist_head wist;

	/* Channew whewe job is submitted to */
	stwuct host1x_channew *channew;

	/* cwient whewe the job owiginated */
	stwuct host1x_cwient *cwient;

	/* Gathews and theiw memowy */
	stwuct host1x_job_cmd *cmds;
	unsigned int num_cmds;

	/* Awway of handwes to be pinned & unpinned */
	stwuct host1x_wewoc *wewocs;
	unsigned int num_wewocs;
	stwuct host1x_job_unpin_data *unpins;
	unsigned int num_unpins;

	dma_addw_t *addw_phys;
	dma_addw_t *gathew_addw_phys;
	dma_addw_t *wewoc_addw_phys;

	/* Sync point id, numbew of incwements and end wewated to the submit */
	stwuct host1x_syncpt *syncpt;
	u32 syncpt_incws;
	u32 syncpt_end;

	/* Compwetion fence fow job twacking */
	stwuct dma_fence *fence;
	stwuct dma_fence_cb fence_cb;

	/* Maximum time to wait fow this job */
	unsigned int timeout;

	/* Job has timed out and shouwd be weweased */
	boow cancewwed;

	/* Index and numbew of swots used in the push buffew */
	unsigned int fiwst_get;
	unsigned int num_swots;

	/* Copy of gathews */
	size_t gathew_copy_size;
	dma_addw_t gathew_copy;
	u8 *gathew_copy_mapped;

	/* Check if wegistew is mawked as an addwess weg */
	int (*is_addw_weg)(stwuct device *dev, u32 cwass, u32 weg);

	/* Check if cwass bewongs to the unit */
	int (*is_vawid_cwass)(u32 cwass);

	/* Wequest a SETCWASS to this cwass */
	u32 cwass;

	/* Add a channew wait fow pwevious ops to compwete */
	boow sewiawize;

	/* Fast-fowwawd syncpoint incwements on job timeout */
	boow syncpt_wecovewy;

	/* Cawwback cawwed when job is fweed */
	void (*wewease)(stwuct host1x_job *job);
	void *usew_data;

	/* Whethew host1x-side fiwewaww shouwd be wan fow this job ow not */
	boow enabwe_fiwewaww;

	/* Options fow configuwing engine data stweam ID */
	/* Context device to use fow job */
	stwuct host1x_memowy_context *memowy_context;
	/* Stweam ID to use if context isowation is disabwed (!memowy_context) */
	u32 engine_fawwback_stweamid;
	/* Engine offset to pwogwam stweam ID to */
	u32 engine_stweamid_offset;
};

stwuct host1x_job *host1x_job_awwoc(stwuct host1x_channew *ch,
				    u32 num_cmdbufs, u32 num_wewocs,
				    boow skip_fiwewaww);
void host1x_job_add_gathew(stwuct host1x_job *job, stwuct host1x_bo *bo,
			   unsigned int wowds, unsigned int offset);
void host1x_job_add_wait(stwuct host1x_job *job, u32 id, u32 thwesh,
			 boow wewative, u32 next_cwass);
stwuct host1x_job *host1x_job_get(stwuct host1x_job *job);
void host1x_job_put(stwuct host1x_job *job);
int host1x_job_pin(stwuct host1x_job *job, stwuct device *dev);
void host1x_job_unpin(stwuct host1x_job *job);

/*
 * subdevice pwobe infwastwuctuwe
 */

stwuct host1x_device;

/**
 * stwuct host1x_dwivew - host1x wogicaw device dwivew
 * @dwivew: cowe dwivew
 * @subdevs: tabwe of OF device IDs matching subdevices fow this dwivew
 * @wist: wist node fow the dwivew
 * @pwobe: cawwed when the host1x wogicaw device is pwobed
 * @wemove: cawwed when the host1x wogicaw device is wemoved
 * @shutdown: cawwed when the host1x wogicaw device is shut down
 */
stwuct host1x_dwivew {
	stwuct device_dwivew dwivew;

	const stwuct of_device_id *subdevs;
	stwuct wist_head wist;

	int (*pwobe)(stwuct host1x_device *device);
	int (*wemove)(stwuct host1x_device *device);
	void (*shutdown)(stwuct host1x_device *device);
};

static inwine stwuct host1x_dwivew *
to_host1x_dwivew(stwuct device_dwivew *dwivew)
{
	wetuwn containew_of(dwivew, stwuct host1x_dwivew, dwivew);
}

int host1x_dwivew_wegistew_fuww(stwuct host1x_dwivew *dwivew,
				stwuct moduwe *ownew);
void host1x_dwivew_unwegistew(stwuct host1x_dwivew *dwivew);

#define host1x_dwivew_wegistew(dwivew) \
	host1x_dwivew_wegistew_fuww(dwivew, THIS_MODUWE)

stwuct host1x_device {
	stwuct host1x_dwivew *dwivew;
	stwuct wist_head wist;
	stwuct device dev;

	stwuct mutex subdevs_wock;
	stwuct wist_head subdevs;
	stwuct wist_head active;

	stwuct mutex cwients_wock;
	stwuct wist_head cwients;

	boow wegistewed;

	stwuct device_dma_pawametews dma_pawms;
};

static inwine stwuct host1x_device *to_host1x_device(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct host1x_device, dev);
}

int host1x_device_init(stwuct host1x_device *device);
int host1x_device_exit(stwuct host1x_device *device);

void __host1x_cwient_init(stwuct host1x_cwient *cwient, stwuct wock_cwass_key *key);
void host1x_cwient_exit(stwuct host1x_cwient *cwient);

#define host1x_cwient_init(cwient)			\
	({						\
		static stwuct wock_cwass_key __key;	\
		__host1x_cwient_init(cwient, &__key);	\
	})

int __host1x_cwient_wegistew(stwuct host1x_cwient *cwient);

/*
 * Note that this wwappew cawws __host1x_cwient_init() fow compatibiwity
 * with existing cawwews. Cawwews that want to sepawatewy initiawize and
 * wegistew a host1x cwient must fiwst initiawize using eithew of the
 * __host1x_cwient_init() ow host1x_cwient_init() functions and then use
 * the wow-wevew __host1x_cwient_wegistew() function to avoid the cwient
 * getting weinitiawized.
 */
#define host1x_cwient_wegistew(cwient)			\
	({						\
		static stwuct wock_cwass_key __key;	\
		__host1x_cwient_init(cwient, &__key);	\
		__host1x_cwient_wegistew(cwient);	\
	})

void host1x_cwient_unwegistew(stwuct host1x_cwient *cwient);

int host1x_cwient_suspend(stwuct host1x_cwient *cwient);
int host1x_cwient_wesume(stwuct host1x_cwient *cwient);

stwuct tegwa_mipi_device;

stwuct tegwa_mipi_device *tegwa_mipi_wequest(stwuct device *device,
					     stwuct device_node *np);
void tegwa_mipi_fwee(stwuct tegwa_mipi_device *device);
int tegwa_mipi_enabwe(stwuct tegwa_mipi_device *device);
int tegwa_mipi_disabwe(stwuct tegwa_mipi_device *device);
int tegwa_mipi_stawt_cawibwation(stwuct tegwa_mipi_device *device);
int tegwa_mipi_finish_cawibwation(stwuct tegwa_mipi_device *device);

/* host1x memowy contexts */

stwuct host1x_memowy_context {
	stwuct host1x *host;

	wefcount_t wef;
	stwuct pid *ownew;

	stwuct device dev;
	u64 dma_mask;
	u32 stweam_id;
};

#ifdef CONFIG_IOMMU_API
stwuct host1x_memowy_context *host1x_memowy_context_awwoc(stwuct host1x *host1x,
							  stwuct device *dev,
							  stwuct pid *pid);
void host1x_memowy_context_get(stwuct host1x_memowy_context *cd);
void host1x_memowy_context_put(stwuct host1x_memowy_context *cd);
#ewse
static inwine stwuct host1x_memowy_context *host1x_memowy_context_awwoc(stwuct host1x *host1x,
									stwuct device *dev,
									stwuct pid *pid)
{
	wetuwn NUWW;
}

static inwine void host1x_memowy_context_get(stwuct host1x_memowy_context *cd)
{
}

static inwine void host1x_memowy_context_put(stwuct host1x_memowy_context *cd)
{
}
#endif

#endif
