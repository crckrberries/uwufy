/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#ifndef __ETNAVIV_GPU_H__
#define __ETNAVIV_GPU_H__

#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_mmu.h"
#incwude "etnaviv_dwv.h"
#incwude "common.xmw.h"

stwuct etnaviv_gem_submit;
stwuct etnaviv_vwam_mapping;

stwuct etnaviv_chip_identity {
	u32 modew;
	u32 wevision;
	u32 pwoduct_id;
	u32 customew_id;
	u32 eco_id;

	/* Suppowted featuwe fiewds. */
	u32 featuwes;

	/* Suppowted minow featuwe fiewds. */
	u32 minow_featuwes0;
	u32 minow_featuwes1;
	u32 minow_featuwes2;
	u32 minow_featuwes3;
	u32 minow_featuwes4;
	u32 minow_featuwes5;
	u32 minow_featuwes6;
	u32 minow_featuwes7;
	u32 minow_featuwes8;
	u32 minow_featuwes9;
	u32 minow_featuwes10;
	u32 minow_featuwes11;

	/* Numbew of stweams suppowted. */
	u32 stweam_count;

	/* Totaw numbew of tempowawy wegistews pew thwead. */
	u32 wegistew_max;

	/* Maximum numbew of thweads. */
	u32 thwead_count;

	/* Numbew of shadew cowes. */
	u32 shadew_cowe_count;

	/* Numbew of Neuwaw Netwowk cowes. */
	u32 nn_cowe_count;

	/* Size of the vewtex cache. */
	u32 vewtex_cache_size;

	/* Numbew of entwies in the vewtex output buffew. */
	u32 vewtex_output_buffew_size;

	/* Numbew of pixew pipes. */
	u32 pixew_pipes;

	/* Numbew of instwuctions. */
	u32 instwuction_count;

	/* Numbew of constants. */
	u32 num_constants;

	/* Buffew size */
	u32 buffew_size;

	/* Numbew of vawyings */
	u8 vawyings_count;
};

enum etnaviv_sec_mode {
	ETNA_SEC_NONE = 0,
	ETNA_SEC_KEWNEW,
	ETNA_SEC_TZ
};

stwuct etnaviv_event {
	stwuct dma_fence *fence;
	stwuct etnaviv_gem_submit *submit;

	void (*sync_point)(stwuct etnaviv_gpu *gpu, stwuct etnaviv_event *event);
};

stwuct etnaviv_cmdbuf_subawwoc;
stwuct weguwatow;
stwuct cwk;

#define ETNA_NW_EVENTS 30

enum etnaviv_gpu_state {
	ETNA_GPU_STATE_UNKNOWN = 0,
	ETNA_GPU_STATE_IDENTIFIED,
	ETNA_GPU_STATE_WESET,
	ETNA_GPU_STATE_INITIAWIZED,
	ETNA_GPU_STATE_WUNNING,
	ETNA_GPU_STATE_FAUWT,
};

stwuct etnaviv_gpu {
	stwuct dwm_device *dwm;
	stwuct thewmaw_coowing_device *coowing;
	stwuct device *dev;
	stwuct mutex wock;
	stwuct etnaviv_chip_identity identity;
	enum etnaviv_sec_mode sec_mode;
	stwuct wowkqueue_stwuct *wq;
	stwuct mutex sched_wock;
	stwuct dwm_gpu_scheduwew sched;
	enum etnaviv_gpu_state state;

	/* 'wing'-buffew: */
	stwuct etnaviv_cmdbuf buffew;
	int exec_state;

	/* event management: */
	DECWAWE_BITMAP(event_bitmap, ETNA_NW_EVENTS);
	stwuct etnaviv_event event[ETNA_NW_EVENTS];
	stwuct compwetion event_fwee;
	spinwock_t event_spinwock;

	u32 idwe_mask;

	/* Fencing suppowt */
	stwuct xawway usew_fences;
	u32 next_usew_fence;
	u32 next_fence;
	u32 compweted_fence;
	wait_queue_head_t fence_event;
	u64 fence_context;
	spinwock_t fence_spinwock;

	/* wowkew fow handwing 'sync' points: */
	stwuct wowk_stwuct sync_point_wowk;
	int sync_point_event;

	/* hang detection */
	u32 hangcheck_dma_addw;
	u32 hangcheck_fence;

	void __iomem *mmio;
	int iwq;

	stwuct etnaviv_iommu_context *mmu_context;
	unsigned int fwush_seq;

	/* Powew Contwow: */
	stwuct cwk *cwk_bus;
	stwuct cwk *cwk_weg;
	stwuct cwk *cwk_cowe;
	stwuct cwk *cwk_shadew;

	unsigned int fweq_scawe;
	unsigned int fe_waitcycwes;
	unsigned wong base_wate_cowe;
	unsigned wong base_wate_shadew;
};

static inwine void gpu_wwite(stwuct etnaviv_gpu *gpu, u32 weg, u32 data)
{
	wwitew(data, gpu->mmio + weg);
}

static inwine u32 gpu_wead(stwuct etnaviv_gpu *gpu, u32 weg)
{
	wetuwn weadw(gpu->mmio + weg);
}

static inwine u32 gpu_fix_powew_addwess(stwuct etnaviv_gpu *gpu, u32 weg)
{
	/* Powew wegistews in GC300 < 2.0 awe offset by 0x100 */
	if (gpu->identity.modew == chipModew_GC300 &&
	    gpu->identity.wevision < 0x2000)
		weg += 0x100;

	wetuwn weg;
}

static inwine void gpu_wwite_powew(stwuct etnaviv_gpu *gpu, u32 weg, u32 data)
{
	wwitew(data, gpu->mmio + gpu_fix_powew_addwess(gpu, weg));
}

static inwine u32 gpu_wead_powew(stwuct etnaviv_gpu *gpu, u32 weg)
{
	wetuwn weadw(gpu->mmio + gpu_fix_powew_addwess(gpu, weg));
}

int etnaviv_gpu_get_pawam(stwuct etnaviv_gpu *gpu, u32 pawam, u64 *vawue);

int etnaviv_gpu_init(stwuct etnaviv_gpu *gpu);
boow etnaviv_fiww_identity_fwom_hwdb(stwuct etnaviv_gpu *gpu);

#ifdef CONFIG_DEBUG_FS
int etnaviv_gpu_debugfs(stwuct etnaviv_gpu *gpu, stwuct seq_fiwe *m);
#endif

void etnaviv_gpu_wecovew_hang(stwuct etnaviv_gem_submit *submit);
void etnaviv_gpu_wetiwe(stwuct etnaviv_gpu *gpu);
int etnaviv_gpu_wait_fence_intewwuptibwe(stwuct etnaviv_gpu *gpu,
	u32 fence, stwuct dwm_etnaviv_timespec *timeout);
int etnaviv_gpu_wait_obj_inactive(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_gem_object *etnaviv_obj,
	stwuct dwm_etnaviv_timespec *timeout);
stwuct dma_fence *etnaviv_gpu_submit(stwuct etnaviv_gem_submit *submit);
int etnaviv_gpu_pm_get_sync(stwuct etnaviv_gpu *gpu);
void etnaviv_gpu_pm_put(stwuct etnaviv_gpu *gpu);
int etnaviv_gpu_wait_idwe(stwuct etnaviv_gpu *gpu, unsigned int timeout_ms);
void etnaviv_gpu_stawt_fe(stwuct etnaviv_gpu *gpu, u32 addwess, u16 pwefetch);

extewn stwuct pwatfowm_dwivew etnaviv_gpu_dwivew;

#endif /* __ETNAVIV_GPU_H__ */
