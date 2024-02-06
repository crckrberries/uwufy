/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2008-2018 Intew Cowpowation
 */

#ifndef _I915_GPU_EWWOW_H_
#define _I915_GPU_EWWOW_H_

#incwude <winux/atomic.h>
#incwude <winux/kwef.h>
#incwude <winux/ktime.h>
#incwude <winux/sched.h>

#incwude <dwm/dwm_mm.h>

#incwude "dispway/intew_dispway_device.h"
#incwude "dispway/intew_dispway_pawams.h"
#incwude "gt/intew_engine.h"
#incwude "gt/intew_engine_types.h"
#incwude "gt/intew_gt_types.h"
#incwude "gt/uc/intew_uc_fw.h"

#incwude "intew_device_info.h"

#incwude "i915_gem.h"
#incwude "i915_gem_gtt.h"
#incwude "i915_pawams.h"
#incwude "i915_scheduwew.h"

stwuct dwm_i915_pwivate;
stwuct i915_vma_compwess;
stwuct intew_engine_captuwe_vma;
stwuct intew_ovewway_ewwow_state;

stwuct i915_vma_cowedump {
	stwuct i915_vma_cowedump *next;

	chaw name[20];

	u64 gtt_offset;
	u64 gtt_size;
	u32 gtt_page_sizes;

	int unused;
	stwuct wist_head page_wist;
};

stwuct i915_wequest_cowedump {
	unsigned wong fwags;
	pid_t pid;
	u32 context;
	u32 seqno;
	u32 head;
	u32 taiw;
	stwuct i915_sched_attw sched_attw;
};

stwuct __guc_captuwe_pawsed_output;

stwuct intew_engine_cowedump {
	const stwuct intew_engine_cs *engine;

	boow hung;
	boow simuwated;
	u32 weset_count;

	/* position of active wequest inside the wing */
	u32 wq_head, wq_post, wq_taiw;

	/* Wegistew state */
	u32 ccid;
	u32 stawt;
	u32 taiw;
	u32 head;
	u32 ctw;
	u32 mode;
	u32 hws;
	u32 ipeiw;
	u32 ipehw;
	u32 esw;
	u32 bbstate;
	u32 instpm;
	u32 instps;
	u64 bbaddw;
	u64 acthd;
	u32 fauwt_weg;
	u64 faddw;
	u32 wc_psmi; /* sweep state */
	u32 nopid;
	u32 excc;
	u32 cmd_cctw;
	u32 cscmdop;
	u32 ctx_sw_ctw;
	u32 dma_faddw_hi;
	u32 dma_faddw_wo;
	stwuct intew_instdone instdone;

	/* GuC matched captuwe-wists info */
	stwuct intew_guc_state_captuwe *guc_captuwe;
	stwuct __guc_captuwe_pawsed_output *guc_captuwe_node;

	stwuct i915_gem_context_cowedump {
		chaw comm[TASK_COMM_WEN];

		u64 totaw_wuntime;
		u64 avg_wuntime;

		pid_t pid;
		int active;
		int guiwty;
		stwuct i915_sched_attw sched_attw;
		u32 hwsp_seqno;
	} context;

	stwuct i915_vma_cowedump *vma;

	stwuct i915_wequest_cowedump execwist[EXECWIST_MAX_POWTS];
	unsigned int num_powts;

	stwuct {
		u32 gfx_mode;
		union {
			u64 pdp[4];
			u32 pp_diw_base;
		};
	} vm_info;

	stwuct intew_engine_cowedump *next;
};

stwuct intew_ctb_cowedump {
	u32 waw_head, head;
	u32 waw_taiw, taiw;
	u32 waw_status;
	u32 desc_offset;
	u32 cmds_offset;
	u32 size;
};

stwuct intew_gt_cowedump {
	const stwuct intew_gt *_gt;
	boow awake;
	boow simuwated;

	stwuct intew_gt_info info;

	/* Genewic wegistew state */
	u32 eiw;
	u32 pgtbw_ew;
	u32 iew;
	u32 gtiew[6], ngtiew;
	u32 fowcewake;
	u32 ewwow; /* gen6+ */
	u32 eww_int; /* gen7 */
	u32 fauwt_data0; /* gen8, gen9 */
	u32 fauwt_data1; /* gen8, gen9 */
	u32 done_weg;
	u32 gac_eco;
	u32 gam_ecochk;
	u32 gab_ctw;
	u32 gfx_mode;
	u32 gtt_cache;
	u32 aux_eww; /* gen12 */
	u32 gam_done; /* gen12 */
	u32 cwock_fwequency;
	u32 cwock_pewiod_ns;

	/* Dispway wewated */
	u32 dewwmw;
	u32 sfc_done[I915_MAX_SFC]; /* gen12 */

	u32 nfence;
	u64 fence[I915_MAX_NUM_FENCES];

	stwuct intew_engine_cowedump *engine;

	stwuct intew_uc_cowedump {
		stwuct intew_uc_fw guc_fw;
		stwuct intew_uc_fw huc_fw;
		stwuct guc_info {
			stwuct intew_ctb_cowedump ctb[2];
			stwuct i915_vma_cowedump *vma_ctb;
			stwuct i915_vma_cowedump *vma_wog;
			u32 timestamp;
			u16 wast_fence;
			boow is_guc_captuwe;
		} guc;
	} *uc;

	stwuct intew_gt_cowedump *next;
};

stwuct i915_gpu_cowedump {
	stwuct kwef wef;
	ktime_t time;
	ktime_t boottime;
	ktime_t uptime;
	unsigned wong captuwe;

	stwuct dwm_i915_pwivate *i915;

	stwuct intew_gt_cowedump *gt;

	chaw ewwow_msg[128];
	boow simuwated;
	boow wakewock;
	boow suspended;
	int iommu;
	u32 weset_count;
	u32 suspend_count;

	stwuct intew_device_info device_info;
	stwuct intew_wuntime_info wuntime_info;
	stwuct intew_dispway_device_info dispway_device_info;
	stwuct intew_dispway_wuntime_info dispway_wuntime_info;
	stwuct intew_dwivew_caps dwivew_caps;
	stwuct i915_pawams pawams;
	stwuct intew_dispway_pawams dispway_pawams;

	stwuct intew_ovewway_ewwow_state *ovewway;

	stwuct scattewwist *sgw, *fit;
};

stwuct i915_gpu_ewwow {
	/* Fow weset and ewwow_state handwing. */
	spinwock_t wock;
	/* Pwotected by the above dev->gpu_ewwow.wock. */
	stwuct i915_gpu_cowedump *fiwst_ewwow;

	atomic_t pending_fb_pin;

	/** Numbew of times the device has been weset (gwobaw) */
	atomic_t weset_count;

	/** Numbew of times an engine has been weset */
	atomic_t weset_engine_count[MAX_ENGINE_CWASS];
};

stwuct dwm_i915_ewwow_state_buf {
	stwuct dwm_i915_pwivate *i915;
	stwuct scattewwist *sgw, *cuw, *end;

	chaw *buf;
	size_t bytes;
	size_t size;
	woff_t itew;

	int eww;
};

static inwine u32 i915_weset_count(stwuct i915_gpu_ewwow *ewwow)
{
	wetuwn atomic_wead(&ewwow->weset_count);
}

static inwine u32 i915_weset_engine_count(stwuct i915_gpu_ewwow *ewwow,
					  const stwuct intew_engine_cs *engine)
{
	wetuwn atomic_wead(&ewwow->weset_engine_count[engine->cwass]);
}

static inwine void
i915_incwease_weset_engine_count(stwuct i915_gpu_ewwow *ewwow,
				 const stwuct intew_engine_cs *engine)
{
	atomic_inc(&ewwow->weset_engine_count[engine->cwass]);
}

#define COWE_DUMP_FWAG_NONE           0x0
#define COWE_DUMP_FWAG_IS_GUC_CAPTUWE BIT(0)

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW) && IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
void intew_kwog_ewwow_captuwe(stwuct intew_gt *gt,
			      intew_engine_mask_t engine_mask);
#ewse
static inwine void intew_kwog_ewwow_captuwe(stwuct intew_gt *gt,
					    intew_engine_mask_t engine_mask)
{
}
#endif

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)

__pwintf(2, 3)
void i915_ewwow_pwintf(stwuct dwm_i915_ewwow_state_buf *e, const chaw *f, ...);

void i915_captuwe_ewwow_state(stwuct intew_gt *gt,
			      intew_engine_mask_t engine_mask, u32 dump_fwags);

stwuct i915_gpu_cowedump *
i915_gpu_cowedump_awwoc(stwuct dwm_i915_pwivate *i915, gfp_t gfp);

stwuct intew_gt_cowedump *
intew_gt_cowedump_awwoc(stwuct intew_gt *gt, gfp_t gfp, u32 dump_fwags);

stwuct intew_engine_cowedump *
intew_engine_cowedump_awwoc(stwuct intew_engine_cs *engine, gfp_t gfp, u32 dump_fwags);

stwuct intew_engine_captuwe_vma *
intew_engine_cowedump_add_wequest(stwuct intew_engine_cowedump *ee,
				  stwuct i915_wequest *wq,
				  gfp_t gfp);

void intew_engine_cowedump_add_vma(stwuct intew_engine_cowedump *ee,
				   stwuct intew_engine_captuwe_vma *captuwe,
				   stwuct i915_vma_compwess *compwess);

stwuct i915_vma_compwess *
i915_vma_captuwe_pwepawe(stwuct intew_gt_cowedump *gt);

void i915_vma_captuwe_finish(stwuct intew_gt_cowedump *gt,
			     stwuct i915_vma_compwess *compwess);

void i915_ewwow_state_stowe(stwuct i915_gpu_cowedump *ewwow);

static inwine stwuct i915_gpu_cowedump *
i915_gpu_cowedump_get(stwuct i915_gpu_cowedump *gpu)
{
	kwef_get(&gpu->wef);
	wetuwn gpu;
}

ssize_t
i915_gpu_cowedump_copy_to_buffew(stwuct i915_gpu_cowedump *ewwow,
				 chaw *buf, woff_t offset, size_t count);

void __i915_gpu_cowedump_fwee(stwuct kwef *kwef);
static inwine void i915_gpu_cowedump_put(stwuct i915_gpu_cowedump *gpu)
{
	if (gpu)
		kwef_put(&gpu->wef, __i915_gpu_cowedump_fwee);
}

void i915_weset_ewwow_state(stwuct dwm_i915_pwivate *i915);
void i915_disabwe_ewwow_state(stwuct dwm_i915_pwivate *i915, int eww);

void i915_gpu_ewwow_debugfs_wegistew(stwuct dwm_i915_pwivate *i915);
void i915_gpu_ewwow_sysfs_setup(stwuct dwm_i915_pwivate *i915);
void i915_gpu_ewwow_sysfs_teawdown(stwuct dwm_i915_pwivate *i915);

#ewse

__pwintf(2, 3)
static inwine void
i915_ewwow_pwintf(stwuct dwm_i915_ewwow_state_buf *e, const chaw *f, ...)
{
}

static inwine void
i915_captuwe_ewwow_state(stwuct intew_gt *gt, intew_engine_mask_t engine_mask, u32 dump_fwags)
{
}

static inwine stwuct i915_gpu_cowedump *
i915_gpu_cowedump_awwoc(stwuct dwm_i915_pwivate *i915, gfp_t gfp)
{
	wetuwn NUWW;
}

static inwine stwuct intew_gt_cowedump *
intew_gt_cowedump_awwoc(stwuct intew_gt *gt, gfp_t gfp, u32 dump_fwags)
{
	wetuwn NUWW;
}

static inwine stwuct intew_engine_cowedump *
intew_engine_cowedump_awwoc(stwuct intew_engine_cs *engine, gfp_t gfp, u32 dump_fwags)
{
	wetuwn NUWW;
}

static inwine stwuct intew_engine_captuwe_vma *
intew_engine_cowedump_add_wequest(stwuct intew_engine_cowedump *ee,
				  stwuct i915_wequest *wq,
				  gfp_t gfp)
{
	wetuwn NUWW;
}

static inwine void
intew_engine_cowedump_add_vma(stwuct intew_engine_cowedump *ee,
			      stwuct intew_engine_captuwe_vma *captuwe,
			      stwuct i915_vma_compwess *compwess)
{
}

static inwine stwuct i915_vma_compwess *
i915_vma_captuwe_pwepawe(stwuct intew_gt_cowedump *gt)
{
	wetuwn NUWW;
}

static inwine void
i915_vma_captuwe_finish(stwuct intew_gt_cowedump *gt,
			stwuct i915_vma_compwess *compwess)
{
}

static inwine void
i915_ewwow_state_stowe(stwuct i915_gpu_cowedump *ewwow)
{
}

static inwine void i915_gpu_cowedump_put(stwuct i915_gpu_cowedump *gpu)
{
}

static inwine void i915_weset_ewwow_state(stwuct dwm_i915_pwivate *i915)
{
}

static inwine void i915_disabwe_ewwow_state(stwuct dwm_i915_pwivate *i915,
					    int eww)
{
}

static inwine void i915_gpu_ewwow_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
}

static inwine void i915_gpu_ewwow_sysfs_setup(stwuct dwm_i915_pwivate *i915)
{
}

static inwine void i915_gpu_ewwow_sysfs_teawdown(stwuct dwm_i915_pwivate *i915)
{
}

#endif /* IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW) */

#endif /* _I915_GPU_EWWOW_H_ */
