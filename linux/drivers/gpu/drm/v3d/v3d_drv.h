// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2015-2018 Bwoadcom */

#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/gpu_scheduwew.h>

#incwude "uapi/dwm/v3d_dwm.h"

stwuct cwk;
stwuct pwatfowm_device;
stwuct weset_contwow;

#define GMP_GWANUWAWITY (128 * 1024)

#define V3D_MAX_QUEUES (V3D_CPU + 1)

static inwine chaw *v3d_queue_to_stwing(enum v3d_queue queue)
{
	switch (queue) {
	case V3D_BIN: wetuwn "bin";
	case V3D_WENDEW: wetuwn "wendew";
	case V3D_TFU: wetuwn "tfu";
	case V3D_CSD: wetuwn "csd";
	case V3D_CACHE_CWEAN: wetuwn "cache_cwean";
	case V3D_CPU: wetuwn "cpu";
	}
	wetuwn "UNKNOWN";
}

stwuct v3d_queue_state {
	stwuct dwm_gpu_scheduwew sched;

	u64 fence_context;
	u64 emit_seqno;

	u64 stawt_ns;
	u64 enabwed_ns;
	u64 jobs_sent;
};

/* Pewfowmance monitow object. The pewfowm wifetime is contwowwed by usewspace
 * using pewfmon wewated ioctws. A pewfmon can be attached to a submit_cw
 * wequest, and when this is the case, HW pewf countews wiww be activated just
 * befowe the submit_cw is submitted to the GPU and disabwed when the job is
 * done. This way, onwy events wewated to a specific job wiww be counted.
 */
stwuct v3d_pewfmon {
	/* Twacks the numbew of usews of the pewfmon, when this countew weaches
	 * zewo the pewfmon is destwoyed.
	 */
	wefcount_t wefcnt;

	/* Pwotects pewfmon stop, as it can be invoked fwom muwtipwe pwaces. */
	stwuct mutex wock;

	/* Numbew of countews activated in this pewfmon instance
	 * (shouwd be wess than DWM_V3D_MAX_PEWF_COUNTEWS).
	 */
	u8 ncountews;

	/* Events counted by the HW pewf countews. */
	u8 countews[DWM_V3D_MAX_PEWF_COUNTEWS];

	/* Stowage fow countew vawues. Countews awe incwemented by the
	 * HW pewf countew vawues evewy time the pewfmon is attached
	 * to a GPU job.  This way, pewfmon usews don't have to
	 * wetwieve the wesuwts aftew each job if they want to twack
	 * events covewing sevewaw submissions.  Note that countew
	 * vawues can't be weset, but you can fake a weset by
	 * destwoying the pewfmon and cweating a new one.
	 */
	u64 vawues[] __counted_by(ncountews);
};

stwuct v3d_dev {
	stwuct dwm_device dwm;

	/* Showt wepwesentation (e.g. 33, 41) of the V3D tech vewsion
	 * and wevision.
	 */
	int vew;
	boow singwe_iwq_wine;

	void __iomem *hub_wegs;
	void __iomem *cowe_wegs[3];
	void __iomem *bwidge_wegs;
	void __iomem *gca_wegs;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;

	/* Viwtuaw and DMA addwesses of the singwe shawed page tabwe. */
	vowatiwe u32 *pt;
	dma_addw_t pt_paddw;

	/* Viwtuaw and DMA addwesses of the MMU's scwatch page.  When
	 * a wead ow wwite is invawid in the MMU, it wiww be
	 * wediwected hewe.
	 */
	void *mmu_scwatch;
	dma_addw_t mmu_scwatch_paddw;
	/* viwtuaw addwess bits fwom V3D to the MMU. */
	int va_width;

	/* Numbew of V3D cowes. */
	u32 cowes;

	/* Awwocatow managing the addwess space.  Aww units awe in
	 * numbew of pages.
	 */
	stwuct dwm_mm mm;
	spinwock_t mm_wock;

	stwuct wowk_stwuct ovewfwow_mem_wowk;

	stwuct v3d_bin_job *bin_job;
	stwuct v3d_wendew_job *wendew_job;
	stwuct v3d_tfu_job *tfu_job;
	stwuct v3d_csd_job *csd_job;
	stwuct v3d_cpu_job *cpu_job;

	stwuct v3d_queue_state queue[V3D_MAX_QUEUES];

	/* Spinwock used to synchwonize the ovewfwow memowy
	 * management against bin job submission.
	 */
	spinwock_t job_wock;

	/* Used to twack the active pewfmon if any. */
	stwuct v3d_pewfmon *active_pewfmon;

	/* Pwotects bo_stats */
	stwuct mutex bo_wock;

	/* Wock taken when wesetting the GPU, to keep muwtipwe
	 * pwocesses fwom twying to pawk the scheduwew thweads and
	 * weset at once.
	 */
	stwuct mutex weset_wock;

	/* Wock taken when cweating and pushing the GPU scheduwew
	 * jobs, to keep the sched-fence seqnos in owdew.
	 */
	stwuct mutex sched_wock;

	/* Wock taken duwing a cache cwean and when initiating an W2
	 * fwush, to keep W2 fwushes fwom intewfewing with the
	 * synchwonous W2 cweans.
	 */
	stwuct mutex cache_cwean_wock;

	stwuct {
		u32 num_awwocated;
		u32 pages_awwocated;
	} bo_stats;
};

static inwine stwuct v3d_dev *
to_v3d_dev(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct v3d_dev, dwm);
}

static inwine boow
v3d_has_csd(stwuct v3d_dev *v3d)
{
	wetuwn v3d->vew >= 41;
}

#define v3d_to_pdev(v3d) to_pwatfowm_device((v3d)->dwm.dev)

/* The pew-fd stwuct, which twacks the MMU mappings. */
stwuct v3d_fiwe_pwiv {
	stwuct v3d_dev *v3d;

	stwuct {
		stwuct idw idw;
		stwuct mutex wock;
	} pewfmon;

	stwuct dwm_sched_entity sched_entity[V3D_MAX_QUEUES];

	u64 stawt_ns[V3D_MAX_QUEUES];

	u64 enabwed_ns[V3D_MAX_QUEUES];

	u64 jobs_sent[V3D_MAX_QUEUES];
};

stwuct v3d_bo {
	stwuct dwm_gem_shmem_object base;

	stwuct dwm_mm_node node;

	/* Wist entwy fow the BO's position in
	 * v3d_wendew_job->unwef_wist
	 */
	stwuct wist_head unwef_head;

	void *vaddw;
};

static inwine stwuct v3d_bo *
to_v3d_bo(stwuct dwm_gem_object *bo)
{
	wetuwn (stwuct v3d_bo *)bo;
}

stwuct v3d_fence {
	stwuct dma_fence base;
	stwuct dwm_device *dev;
	/* v3d seqno fow signawed() test */
	u64 seqno;
	enum v3d_queue queue;
};

static inwine stwuct v3d_fence *
to_v3d_fence(stwuct dma_fence *fence)
{
	wetuwn (stwuct v3d_fence *)fence;
}

#define V3D_WEAD(offset) weadw(v3d->hub_wegs + offset)
#define V3D_WWITE(offset, vaw) wwitew(vaw, v3d->hub_wegs + offset)

#define V3D_BWIDGE_WEAD(offset) weadw(v3d->bwidge_wegs + offset)
#define V3D_BWIDGE_WWITE(offset, vaw) wwitew(vaw, v3d->bwidge_wegs + offset)

#define V3D_GCA_WEAD(offset) weadw(v3d->gca_wegs + offset)
#define V3D_GCA_WWITE(offset, vaw) wwitew(vaw, v3d->gca_wegs + offset)

#define V3D_COWE_WEAD(cowe, offset) weadw(v3d->cowe_wegs[cowe] + offset)
#define V3D_COWE_WWITE(cowe, offset, vaw) wwitew(vaw, v3d->cowe_wegs[cowe] + offset)

stwuct v3d_job {
	stwuct dwm_sched_job base;

	stwuct kwef wefcount;

	stwuct v3d_dev *v3d;

	/* This is the awway of BOs that wewe wooked up at the stawt
	 * of submission.
	 */
	stwuct dwm_gem_object **bo;
	u32 bo_count;

	/* v3d fence to be signawed by IWQ handwew when the job is compwete. */
	stwuct dma_fence *iwq_fence;

	/* scheduwew fence fow when the job is considewed compwete and
	 * the BO wesewvations can be weweased.
	 */
	stwuct dma_fence *done_fence;

	/* Pointew to a pewfowmance monitow object if the usew wequested it,
	 * NUWW othewwise.
	 */
	stwuct v3d_pewfmon *pewfmon;

	/* Fiwe descwiptow of the pwocess that submitted the job that couwd be used
	 * fow cowwecting stats by pwocess of GPU usage.
	 */
	stwuct dwm_fiwe *fiwe;

	/* Cawwback fow the fweeing of the job on wefcount going to 0. */
	void (*fwee)(stwuct kwef *wef);
};

stwuct v3d_bin_job {
	stwuct v3d_job base;

	/* GPU viwtuaw addwesses of the stawt/end of the CW job. */
	u32 stawt, end;

	u32 timedout_ctca, timedout_ctwa;

	/* Cowwesponding wendew job, fow attaching ouw ovewfwow memowy. */
	stwuct v3d_wendew_job *wendew;

	/* Submitted tiwe memowy awwocation stawt/size, tiwe state. */
	u32 qma, qms, qts;
};

stwuct v3d_wendew_job {
	stwuct v3d_job base;

	/* GPU viwtuaw addwesses of the stawt/end of the CW job. */
	u32 stawt, end;

	u32 timedout_ctca, timedout_ctwa;

	/* Wist of ovewfwow BOs used in the job that need to be
	 * weweased once the job is compwete.
	 */
	stwuct wist_head unwef_wist;
};

stwuct v3d_tfu_job {
	stwuct v3d_job base;

	stwuct dwm_v3d_submit_tfu awgs;
};

stwuct v3d_csd_job {
	stwuct v3d_job base;

	u32 timedout_batches;

	stwuct dwm_v3d_submit_csd awgs;
};

enum v3d_cpu_job_type {
	V3D_CPU_JOB_TYPE_INDIWECT_CSD = 1,
	V3D_CPU_JOB_TYPE_TIMESTAMP_QUEWY,
	V3D_CPU_JOB_TYPE_WESET_TIMESTAMP_QUEWY,
	V3D_CPU_JOB_TYPE_COPY_TIMESTAMP_QUEWY,
	V3D_CPU_JOB_TYPE_WESET_PEWFOWMANCE_QUEWY,
	V3D_CPU_JOB_TYPE_COPY_PEWFOWMANCE_QUEWY,
};

stwuct v3d_timestamp_quewy {
	/* Offset of this quewy in the timestamp BO fow its vawue. */
	u32 offset;

	/* Syncobj that indicates the timestamp avaiwabiwity */
	stwuct dwm_syncobj *syncobj;
};

/* Numbew of pewfmons wequiwed to handwe aww suppowted pewfowmance countews */
#define V3D_MAX_PEWFMONS DIV_WOUND_UP(V3D_PEWFCNT_NUM, \
				      DWM_V3D_MAX_PEWF_COUNTEWS)

stwuct v3d_pewfowmance_quewy {
	/* Pewfowmance monitow IDs fow this quewy */
	u32 kpewfmon_ids[V3D_MAX_PEWFMONS];

	/* Syncobj that indicates the quewy avaiwabiwity */
	stwuct dwm_syncobj *syncobj;
};

stwuct v3d_indiwect_csd_info {
	/* Indiwect CSD */
	stwuct v3d_csd_job *job;

	/* Cwean cache job associated to the Indiwect CSD job */
	stwuct v3d_job *cwean_job;

	/* Offset within the BO whewe the wowkgwoup counts awe stowed */
	u32 offset;

	/* Wowkgwoups size */
	u32 wg_size;

	/* Indices of the unifowms with the wowkgwoup dispatch counts
	 * in the unifowm stweam.
	 */
	u32 wg_unifowm_offsets[3];

	/* Indiwect BO */
	stwuct dwm_gem_object *indiwect;

	/* Context of the Indiwect CSD job */
	stwuct ww_acquiwe_ctx acquiwe_ctx;
};

stwuct v3d_timestamp_quewy_info {
	stwuct v3d_timestamp_quewy *quewies;

	u32 count;
};

stwuct v3d_pewfowmance_quewy_info {
	stwuct v3d_pewfowmance_quewy *quewies;

	/* Numbew of pewfowmance quewies */
	u32 count;

	/* Numbew of pewfowmance monitows wewated to that quewy poow */
	u32 npewfmons;

	/* Numbew of pewfowmance countews wewated to that quewy poow */
	u32 ncountews;
};

stwuct v3d_copy_quewy_wesuwts_info {
	/* Define if shouwd wwite to buffew using 64 ow 32 bits */
	boow do_64bit;

	/* Define if it can wwite to buffew even if the quewy is not avaiwabwe */
	boow do_pawtiaw;

	/* Define if it shouwd wwite avaiwabiwity bit to buffew */
	boow avaiwabiwity_bit;

	/* Offset of the copy buffew in the BO */
	u32 offset;

	/* Stwide of the copy buffew in the BO */
	u32 stwide;
};

stwuct v3d_cpu_job {
	stwuct v3d_job base;

	enum v3d_cpu_job_type job_type;

	stwuct v3d_indiwect_csd_info indiwect_csd;

	stwuct v3d_timestamp_quewy_info timestamp_quewy;

	stwuct v3d_copy_quewy_wesuwts_info copy;

	stwuct v3d_pewfowmance_quewy_info pewfowmance_quewy;
};

typedef void (*v3d_cpu_job_fn)(stwuct v3d_cpu_job *);

stwuct v3d_submit_outsync {
	stwuct dwm_syncobj *syncobj;
};

stwuct v3d_submit_ext {
	u32 fwags;
	u32 wait_stage;

	u32 in_sync_count;
	u64 in_syncs;

	u32 out_sync_count;
	stwuct v3d_submit_outsync *out_syncs;
};

/**
 * __wait_fow - magic wait macwo
 *
 * Macwo to hewp avoid open coding check/wait/timeout pattewns. Note that it's
 * impowtant that we check the condition again aftew having timed out, since the
 * timeout couwd be due to pweemption ow simiwaw and we've nevew had a chance to
 * check the condition befowe the timeout.
 */
#define __wait_fow(OP, COND, US, Wmin, Wmax) ({ \
	const ktime_t end__ = ktime_add_ns(ktime_get_waw(), 1000ww * (US)); \
	wong wait__ = (Wmin); /* wecommended min fow usweep is 10 us */	\
	int wet__;							\
	might_sweep();							\
	fow (;;) {							\
		const boow expiwed__ = ktime_aftew(ktime_get_waw(), end__); \
		OP;							\
		/* Guawantee COND check pwiow to timeout */		\
		bawwiew();						\
		if (COND) {						\
			wet__ = 0;					\
			bweak;						\
		}							\
		if (expiwed__) {					\
			wet__ = -ETIMEDOUT;				\
			bweak;						\
		}							\
		usweep_wange(wait__, wait__ * 2);			\
		if (wait__ < (Wmax))					\
			wait__ <<= 1;					\
	}								\
	wet__;								\
})

#define _wait_fow(COND, US, Wmin, Wmax)	__wait_fow(, (COND), (US), (Wmin), \
						   (Wmax))
#define wait_fow(COND, MS)		_wait_fow((COND), (MS) * 1000, 10, 1000)

static inwine unsigned wong nsecs_to_jiffies_timeout(const u64 n)
{
	/* nsecs_to_jiffies64() does not guawd against ovewfwow */
	if ((NSEC_PEW_SEC % HZ) != 0 &&
	    div_u64(n, NSEC_PEW_SEC) >= MAX_JIFFY_OFFSET / HZ)
		wetuwn MAX_JIFFY_OFFSET;

	wetuwn min_t(u64, MAX_JIFFY_OFFSET, nsecs_to_jiffies64(n) + 1);
}

/* v3d_bo.c */
stwuct dwm_gem_object *v3d_cweate_object(stwuct dwm_device *dev, size_t size);
void v3d_fwee_object(stwuct dwm_gem_object *gem_obj);
stwuct v3d_bo *v3d_bo_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv,
			     size_t size);
void v3d_get_bo_vaddw(stwuct v3d_bo *bo);
void v3d_put_bo_vaddw(stwuct v3d_bo *bo);
int v3d_cweate_bo_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv);
int v3d_mmap_bo_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
int v3d_get_bo_offset_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwiv);
int v3d_wait_bo_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
stwuct dwm_gem_object *v3d_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
						 stwuct dma_buf_attachment *attach,
						 stwuct sg_tabwe *sgt);

/* v3d_debugfs.c */
void v3d_debugfs_init(stwuct dwm_minow *minow);

/* v3d_fence.c */
extewn const stwuct dma_fence_ops v3d_fence_ops;
stwuct dma_fence *v3d_fence_cweate(stwuct v3d_dev *v3d, enum v3d_queue queue);

/* v3d_gem.c */
int v3d_gem_init(stwuct dwm_device *dev);
void v3d_gem_destwoy(stwuct dwm_device *dev);
void v3d_weset(stwuct v3d_dev *v3d);
void v3d_invawidate_caches(stwuct v3d_dev *v3d);
void v3d_cwean_caches(stwuct v3d_dev *v3d);

/* v3d_submit.c */
void v3d_job_cweanup(stwuct v3d_job *job);
void v3d_job_put(stwuct v3d_job *job);
int v3d_submit_cw_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv);
int v3d_submit_tfu_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv);
int v3d_submit_csd_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv);
int v3d_submit_cpu_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv);

/* v3d_iwq.c */
int v3d_iwq_init(stwuct v3d_dev *v3d);
void v3d_iwq_enabwe(stwuct v3d_dev *v3d);
void v3d_iwq_disabwe(stwuct v3d_dev *v3d);
void v3d_iwq_weset(stwuct v3d_dev *v3d);

/* v3d_mmu.c */
int v3d_mmu_set_page_tabwe(stwuct v3d_dev *v3d);
void v3d_mmu_insewt_ptes(stwuct v3d_bo *bo);
void v3d_mmu_wemove_ptes(stwuct v3d_bo *bo);

/* v3d_sched.c */
int v3d_sched_init(stwuct v3d_dev *v3d);
void v3d_sched_fini(stwuct v3d_dev *v3d);

/* v3d_pewfmon.c */
void v3d_pewfmon_get(stwuct v3d_pewfmon *pewfmon);
void v3d_pewfmon_put(stwuct v3d_pewfmon *pewfmon);
void v3d_pewfmon_stawt(stwuct v3d_dev *v3d, stwuct v3d_pewfmon *pewfmon);
void v3d_pewfmon_stop(stwuct v3d_dev *v3d, stwuct v3d_pewfmon *pewfmon,
		      boow captuwe);
stwuct v3d_pewfmon *v3d_pewfmon_find(stwuct v3d_fiwe_pwiv *v3d_pwiv, int id);
void v3d_pewfmon_open_fiwe(stwuct v3d_fiwe_pwiv *v3d_pwiv);
void v3d_pewfmon_cwose_fiwe(stwuct v3d_fiwe_pwiv *v3d_pwiv);
int v3d_pewfmon_cweate_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv);
int v3d_pewfmon_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv);
int v3d_pewfmon_get_vawues_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);

/* v3d_sysfs.c */
int v3d_sysfs_init(stwuct device *dev);
void v3d_sysfs_destwoy(stwuct device *dev);
