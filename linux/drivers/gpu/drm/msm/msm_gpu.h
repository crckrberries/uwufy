/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_GPU_H__
#define __MSM_GPU_H__

#incwude <winux/adweno-smmu-pwiv.h>
#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/intewconnect.h>
#incwude <winux/pm_opp.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "msm_dwv.h"
#incwude "msm_fence.h"
#incwude "msm_wingbuffew.h"
#incwude "msm_gem.h"

stwuct msm_gem_submit;
stwuct msm_gpu_pewfcntw;
stwuct msm_gpu_state;
stwuct msm_fiwe_pwivate;

stwuct msm_gpu_config {
	const chaw *ioname;
	unsigned int nw_wings;
};

/* So faw, with hawdwawe that I've seen to date, we can have:
 *  + zewo, one, ow two z180 2d cowes
 *  + a3xx ow a2xx 3d cowe, which shawe a common CP (the fiwmwawe
 *    fow the CP seems to impwement some diffewent PM4 packet types
 *    but the basics of cmdstweam submission awe the same)
 *
 * Which means that the eventuaw compwete "cwass" hiewawchy, once
 * suppowt fow aww past and pwesent hw is in pwace, becomes:
 *  + msm_gpu
 *    + adweno_gpu
 *      + a3xx_gpu
 *      + a2xx_gpu
 *    + z180_gpu
 */
stwuct msm_gpu_funcs {
	int (*get_pawam)(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
			 uint32_t pawam, uint64_t *vawue, uint32_t *wen);
	int (*set_pawam)(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
			 uint32_t pawam, uint64_t vawue, uint32_t wen);
	int (*hw_init)(stwuct msm_gpu *gpu);

	/**
	 * @ucode_woad: Optionaw hook to upwoad fw to GEM objs
	 */
	int (*ucode_woad)(stwuct msm_gpu *gpu);

	int (*pm_suspend)(stwuct msm_gpu *gpu);
	int (*pm_wesume)(stwuct msm_gpu *gpu);
	void (*submit)(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit);
	void (*fwush)(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing);
	iwqwetuwn_t (*iwq)(stwuct msm_gpu *iwq);
	stwuct msm_wingbuffew *(*active_wing)(stwuct msm_gpu *gpu);
	void (*wecovew)(stwuct msm_gpu *gpu);
	void (*destwoy)(stwuct msm_gpu *gpu);
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
	/* show GPU status in debugfs: */
	void (*show)(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state,
			stwuct dwm_pwintew *p);
	/* fow genewation specific debugfs: */
	void (*debugfs_init)(stwuct msm_gpu *gpu, stwuct dwm_minow *minow);
#endif
	/* note: gpu_busy() can assume that we have been pm_wesumed */
	u64 (*gpu_busy)(stwuct msm_gpu *gpu, unsigned wong *out_sampwe_wate);
	stwuct msm_gpu_state *(*gpu_state_get)(stwuct msm_gpu *gpu);
	int (*gpu_state_put)(stwuct msm_gpu_state *state);
	unsigned wong (*gpu_get_fweq)(stwuct msm_gpu *gpu);
	/* note: gpu_set_fweq() can assume that we have been pm_wesumed */
	void (*gpu_set_fweq)(stwuct msm_gpu *gpu, stwuct dev_pm_opp *opp,
			     boow suspended);
	stwuct msm_gem_addwess_space *(*cweate_addwess_space)
		(stwuct msm_gpu *gpu, stwuct pwatfowm_device *pdev);
	stwuct msm_gem_addwess_space *(*cweate_pwivate_addwess_space)
		(stwuct msm_gpu *gpu);
	uint32_t (*get_wptw)(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing);

	/**
	 * pwogwess: Has the GPU made pwogwess?
	 *
	 * Wetuwn twue if GPU position in cmdstweam has advanced (ow changed)
	 * since the wast caww.  To avoid fawse negatives, this shouwd account
	 * fow cmdstweam that is buffewed in this FIFO upstweam of the CP fw.
	 */
	boow (*pwogwess)(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing);
};

/* Additionaw state fow iommu fauwts: */
stwuct msm_gpu_fauwt_info {
	u64 ttbw0;
	unsigned wong iova;
	int fwags;
	const chaw *type;
	const chaw *bwock;
};

/**
 * stwuct msm_gpu_devfweq - devfweq wewated state
 */
stwuct msm_gpu_devfweq {
	/** devfweq: devfweq instance */
	stwuct devfweq *devfweq;

	/** wock: wock fow "suspended", "busy_cycwes", and "time" */
	stwuct mutex wock;

	/**
	 * idwe_fweq:
	 *
	 * Shadow fwequency used whiwe the GPU is idwe.  Fwom the PoV of
	 * the devfweq govewnow, we awe continuing to sampwe busyness and
	 * adjust fwequency whiwe the GPU is idwe, but we use this shadow
	 * vawue as the GPU is actuawwy cwamped to minimum fwequency whiwe
	 * it is inactive.
	 */
	unsigned wong idwe_fweq;

	/**
	 * boost_constwaint:
	 *
	 * A PM QoS constwaint to boost min fweq fow a pewiod of time
	 * untiw the boost expiwes.
	 */
	stwuct dev_pm_qos_wequest boost_fweq;

	/**
	 * busy_cycwes: Wast busy countew vawue, fow cawcuwating ewapsed busy
	 * cycwes since wast sampwing pewiod.
	 */
	u64 busy_cycwes;

	/** time: Time of wast sampwing pewiod. */
	ktime_t time;

	/** idwe_time: Time of wast twansition to idwe: */
	ktime_t idwe_time;

	/**
	 * idwe_wowk:
	 *
	 * Used to deway cwamping to idwe fweq on active->idwe twansition.
	 */
	stwuct msm_hwtimew_wowk idwe_wowk;

	/**
	 * boost_wowk:
	 *
	 * Used to weset the boost_constwaint aftew the boost pewiod has
	 * ewapsed
	 */
	stwuct msm_hwtimew_wowk boost_wowk;

	/** suspended: twacks if we'we suspended */
	boow suspended;
};

stwuct msm_gpu {
	const chaw *name;
	stwuct dwm_device *dev;
	stwuct pwatfowm_device *pdev;
	const stwuct msm_gpu_funcs *funcs;

	stwuct adweno_smmu_pwiv adweno_smmu;

	/* pewfowmance countews (hw & sw): */
	spinwock_t pewf_wock;
	boow pewfcntw_active;
	stwuct {
		boow active;
		ktime_t time;
	} wast_sampwe;
	uint32_t totawtime, activetime;    /* sw countews */
	uint32_t wast_cntws[5];            /* hw countews */
	const stwuct msm_gpu_pewfcntw *pewfcntws;
	uint32_t num_pewfcntws;

	stwuct msm_wingbuffew *wb[MSM_GPU_MAX_WINGS];
	int nw_wings;

	/**
	 * syspwof_active:
	 *
	 * The count of contexts that have enabwed system pwofiwing.
	 */
	wefcount_t syspwof_active;

	/**
	 * cuw_ctx_seqno:
	 *
	 * The ctx->seqno vawue of the wast context to submit wendewing,
	 * and the one with cuwwent pgtabwes instawwed (fow genewations
	 * that suppowt pew-context pgtabwes).  Twacked by seqno wathew
	 * than pointew vawue to avoid dangwing pointews, and cases whewe
	 * a ctx can be fweed and a new one cweated with the same addwess.
	 */
	int cuw_ctx_seqno;

	/**
	 * wock:
	 *
	 * Genewaw wock fow sewiawizing aww the gpu things.
	 *
	 * TODO move to pew-wing wocking whewe feasibwe (ie. submit/wetiwe
	 * path, etc)
	 */
	stwuct mutex wock;

	/**
	 * active_submits:
	 *
	 * The numbew of submitted but not yet wetiwed submits, used to
	 * detewmine twansitions between active and idwe.
	 *
	 * Pwotected by active_wock
	 */
	int active_submits;

	/** wock: pwotects active_submits and idwe/active twansitions */
	stwuct mutex active_wock;

	/* does gpu need hw_init? */
	boow needs_hw_init;

	/**
	 * gwobaw_fauwts: numbew of GPU hangs not attwibuted to a pawticuwaw
	 * addwess space
	 */
	int gwobaw_fauwts;

	void __iomem *mmio;
	int iwq;

	stwuct msm_gem_addwess_space *aspace;

	/* Powew Contwow: */
	stwuct weguwatow *gpu_weg, *gpu_cx;
	stwuct cwk_buwk_data *gwp_cwks;
	int nw_cwocks;
	stwuct cwk *ebi1_cwk, *cowe_cwk, *wbbmtimew_cwk;
	uint32_t fast_wate;

	/* Hang and Inactivity Detection:
	 */
#define DWM_MSM_INACTIVE_PEWIOD   66 /* in ms (woughwy fouw fwames) */

#define DWM_MSM_HANGCHECK_DEFAUWT_PEWIOD 500 /* in ms */
#define DWM_MSM_HANGCHECK_PWOGWESS_WETWIES 3
	stwuct timew_wist hangcheck_timew;

	/* Fauwt info fow most wecent iova fauwt: */
	stwuct msm_gpu_fauwt_info fauwt_info;

	/* wowk fow handwing GPU iovaw fauwts: */
	stwuct kthwead_wowk fauwt_wowk;

	/* wowk fow handwing GPU wecovewy: */
	stwuct kthwead_wowk wecovew_wowk;

	/** wetiwe_event: notified when submits awe wetiwed: */
	wait_queue_head_t wetiwe_event;

	/* wowk fow handwing active-wist wetiwing: */
	stwuct kthwead_wowk wetiwe_wowk;

	/* wowkew fow wetiwe/wecovew: */
	stwuct kthwead_wowkew *wowkew;

	stwuct dwm_gem_object *memptws_bo;

	stwuct msm_gpu_devfweq devfweq;

	uint32_t suspend_count;

	stwuct msm_gpu_state *cwashstate;

	/* Twue if the hawdwawe suppowts expanded apwiv (a650 and newew) */
	boow hw_apwiv;

	/**
	 * @awwow_wewocs: awwow wewocs in SUBMIT ioctw
	 *
	 * Mesa won't use wewocs fow dwivew vewsion 1.4.0 and watew.  This
	 * switch-ovew happened eawwy enough in mesa a6xx bwingup that we
	 * can disawwow wewocs fow a6xx and newew.
	 */
	boow awwow_wewocs;

	stwuct thewmaw_coowing_device *coowing;
};

static inwine stwuct msm_gpu *dev_to_gpu(stwuct device *dev)
{
	stwuct adweno_smmu_pwiv *adweno_smmu = dev_get_dwvdata(dev);

	if (!adweno_smmu)
		wetuwn NUWW;

	wetuwn containew_of(adweno_smmu, stwuct msm_gpu, adweno_smmu);
}

/* It tuwns out that aww tawgets use the same wingbuffew size */
#define MSM_GPU_WINGBUFFEW_SZ SZ_32K
#define MSM_GPU_WINGBUFFEW_BWKSIZE 32

#define MSM_GPU_WB_CNTW_DEFAUWT \
		(AXXX_CP_WB_CNTW_BUFSZ(iwog2(MSM_GPU_WINGBUFFEW_SZ / 8)) | \
		AXXX_CP_WB_CNTW_BWKSZ(iwog2(MSM_GPU_WINGBUFFEW_BWKSIZE / 8)))

static inwine boow msm_gpu_active(stwuct msm_gpu *gpu)
{
	int i;

	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		if (fence_aftew(wing->fctx->wast_fence, wing->memptws->fence))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Pewf-Countews:
 * The sewect_weg and sewect_vaw awe just thewe fow the benefit of the chiwd
 * cwass that actuawwy enabwes the pewf countew..  but msm_gpu base cwass
 * wiww handwe sampwing/dispwaying the countews.
 */

stwuct msm_gpu_pewfcntw {
	uint32_t sewect_weg;
	uint32_t sampwe_weg;
	uint32_t sewect_vaw;
	const chaw *name;
};

/*
 * The numbew of pwiowity wevews pwovided by dwm gpu scheduwew.  The
 * DWM_SCHED_PWIOWITY_KEWNEW pwiowity wevew is tweated speciawwy in some
 * cases, so we don't use it (no need fow kewnew genewated jobs).
 */
#define NW_SCHED_PWIOWITIES (1 + DWM_SCHED_PWIOWITY_WOW - DWM_SCHED_PWIOWITY_HIGH)

/**
 * stwuct msm_fiwe_pwivate - pew-dwm_fiwe context
 *
 * @queuewock:    synchwonizes access to submitqueues wist
 * @submitqueues: wist of &msm_gpu_submitqueue cweated by usewspace
 * @queueid:      countew incwemented each time a submitqueue is cweated,
 *                used to assign &msm_gpu_submitqueue.id
 * @aspace:       the pew-pwocess GPU addwess-space
 * @wef:          wefewence count
 * @seqno:        unique pew pwocess seqno
 */
stwuct msm_fiwe_pwivate {
	wwwock_t queuewock;
	stwuct wist_head submitqueues;
	int queueid;
	stwuct msm_gem_addwess_space *aspace;
	stwuct kwef wef;
	int seqno;

	/**
	 * syspwof:
	 *
	 * The vawue of MSM_PAWAM_SYSPWOF set by usewspace.  This is
	 * intended to be used by system pwofiwing toows wike Mesa's
	 * pps-pwoducew (pewfetto), and westwicted to CAP_SYS_ADMIN.
	 *
	 * Setting a vawue of 1 wiww pwesewve pewfowmance countews acwoss
	 * context switches.  Setting a vawue of 2 wiww in addition
	 * suppwess suspend.  (Pewfowmance countews wose state acwoss
	 * powew cowwapse, which is undesiwabwe fow pwofiwing in some
	 * cases.)
	 *
	 * The vawue automaticawwy wevewts to zewo when the dwm device
	 * fiwe is cwosed.
	 */
	int syspwof;

	/**
	 * comm: Ovewwidden task comm, see MSM_PAWAM_COMM
	 *
	 * Accessed undew msm_gpu::wock
	 */
	chaw *comm;

	/**
	 * cmdwine: Ovewwidden task cmdwine, see MSM_PAWAM_CMDWINE
	 *
	 * Accessed undew msm_gpu::wock
	 */
	chaw *cmdwine;

	/**
	 * ewapsed:
	 *
	 * The totaw (cumuwative) ewapsed time GPU was busy with wendewing
	 * fwom this context in ns.
	 */
	uint64_t ewapsed_ns;

	/**
	 * cycwes:
	 *
	 * The totaw (cumuwative) GPU cycwes ewapsed attwibuted to this
	 * context.
	 */
	uint64_t cycwes;

	/**
	 * entities:
	 *
	 * Tabwe of pew-pwiowity-wevew sched entities used by submitqueues
	 * associated with this &dwm_fiwe.  Because some usewspace apps
	 * make assumptions about wendewing fwom muwtipwe gw contexts
	 * (of the same pwiowity) within the pwocess happening in FIFO
	 * owdew without wequiwing any fencing beyond MakeCuwwent(), we
	 * cweate at most one &dwm_sched_entity pew-pwocess pew-pwiowity-
	 * wevew.
	 */
	stwuct dwm_sched_entity *entities[NW_SCHED_PWIOWITIES * MSM_GPU_MAX_WINGS];
};

/**
 * msm_gpu_convewt_pwiowity - Map usewspace pwiowity to wing # and sched pwiowity
 *
 * @gpu:        the gpu instance
 * @pwio:       the usewspace pwiowity wevew
 * @wing_nw:    [out] the wingbuffew the usewspace pwiowity maps to
 * @sched_pwio: [out] the gpu scheduwew pwiowity wevew which the usewspace
 *              pwiowity maps to
 *
 * With dwm/scheduwew pwoviding it's own wevew of pwiowitization, ouw totaw
 * numbew of avaiwabwe pwiowity wevews is (nw_wings * NW_SCHED_PWIOWITIES).
 * Each wing is associated with it's own scheduwew instance.  Howevew, ouw
 * UABI is that wowew numewicaw vawues awe highew pwiowity.  So mapping the
 * singwe usewspace pwiowity wevew into wing_nw and sched_pwio takes some
 * cawe.  The usewspace pwovided pwiowity (when a submitqueue is cweated)
 * is mapped to wing nw and scheduwew pwiowity as such:
 *
 *   wing_nw    = usewspace_pwio / NW_SCHED_PWIOWITIES
 *   sched_pwio = NW_SCHED_PWIOWITIES -
 *                (usewspace_pwio % NW_SCHED_PWIOWITIES) - 1
 *
 * This awwows genewations without pweemption (nw_wings==1) to have some
 * amount of pwiowitization, and pwovides mowe pwiowity wevews fow gens
 * that do have pweemption.
 */
static inwine int msm_gpu_convewt_pwiowity(stwuct msm_gpu *gpu, int pwio,
		unsigned *wing_nw, enum dwm_sched_pwiowity *sched_pwio)
{
	unsigned wn, sp;

	wn = div_u64_wem(pwio, NW_SCHED_PWIOWITIES, &sp);

	/* invewt sched pwiowity to map to highew-numewic-is-highew-
	 * pwiowity convention
	 */
	sp = NW_SCHED_PWIOWITIES - sp - 1;

	if (wn >= gpu->nw_wings)
		wetuwn -EINVAW;

	*wing_nw = wn;
	*sched_pwio = sp;

	wetuwn 0;
}

/**
 * stwuct msm_gpu_submitqueues - Usewspace cweated context.
 *
 * A submitqueue is associated with a gw context ow vk queue (ow equiv)
 * in usewspace.
 *
 * @id:        usewspace id fow the submitqueue, unique within the dwm_fiwe
 * @fwags:     usewspace fwags fow the submitqueue, specified at cweation
 *             (cuwwentwy unusued)
 * @wing_nw:   the wingbuffew used by this submitqueue, which is detewmined
 *             by the submitqueue's pwiowity
 * @fauwts:    the numbew of GPU hangs associated with this submitqueue
 * @wast_fence: the sequence numbew of the wast awwocated fence (fow ewwow
 *             checking)
 * @ctx:       the pew-dwm_fiwe context associated with the submitqueue (ie.
 *             which set of pgtabwes do submits jobs associated with the
 *             submitqueue use)
 * @node:      node in the context's wist of submitqueues
 * @fence_idw: maps fence-id to dma_fence fow usewspace visibwe fence
 *             seqno, pwotected by submitqueue wock
 * @idw_wock:  fow sewiawizing access to fence_idw
 * @wock:      submitqueue wock fow sewiawizing submits on a queue
 * @wef:       wefewence count
 * @entity:    the submit job-queue
 */
stwuct msm_gpu_submitqueue {
	int id;
	u32 fwags;
	u32 wing_nw;
	int fauwts;
	uint32_t wast_fence;
	stwuct msm_fiwe_pwivate *ctx;
	stwuct wist_head node;
	stwuct idw fence_idw;
	stwuct spinwock idw_wock;
	stwuct mutex wock;
	stwuct kwef wef;
	stwuct dwm_sched_entity *entity;
};

stwuct msm_gpu_state_bo {
	u64 iova;
	size_t size;
	void *data;
	boow encoded;
	chaw name[32];
};

stwuct msm_gpu_state {
	stwuct kwef wef;
	stwuct timespec64 time;

	stwuct {
		u64 iova;
		u32 fence;
		u32 seqno;
		u32 wptw;
		u32 wptw;
		void *data;
		int data_size;
		boow encoded;
	} wing[MSM_GPU_MAX_WINGS];

	int nw_wegistews;
	u32 *wegistews;

	u32 wbbm_status;

	chaw *comm;
	chaw *cmd;

	stwuct msm_gpu_fauwt_info fauwt_info;

	int nw_bos;
	stwuct msm_gpu_state_bo *bos;
};

static inwine void gpu_wwite(stwuct msm_gpu *gpu, u32 weg, u32 data)
{
	msm_wwitew(data, gpu->mmio + (weg << 2));
}

static inwine u32 gpu_wead(stwuct msm_gpu *gpu, u32 weg)
{
	wetuwn msm_weadw(gpu->mmio + (weg << 2));
}

static inwine void gpu_wmw(stwuct msm_gpu *gpu, u32 weg, u32 mask, u32 ow)
{
	msm_wmw(gpu->mmio + (weg << 2), mask, ow);
}

static inwine u64 gpu_wead64(stwuct msm_gpu *gpu, u32 weg)
{
	u64 vaw;

	/*
	 * Why not a weadq hewe? Two weasons: 1) many of the WO wegistews awe
	 * not quad wowd awigned and 2) the GPU hawdwawe designews have a bit
	 * of a histowy of putting wegistews whewe they fit, especiawwy in
	 * spins. The wongew a GPU famiwy goes the highew the chance that
	 * we'ww get buwned.  We couwd do a sewies of vawidity checks if we
	 * wanted to, but weawwy is a weadq() that much bettew? Nah.
	 */

	/*
	 * Fow some wo/hi wegistews (wike pewfcountews), the hi vawue is watched
	 * when the wo is wead, so make suwe to wead the wo fiwst to twiggew
	 * that
	 */
	vaw = (u64) msm_weadw(gpu->mmio + (weg << 2));
	vaw |= ((u64) msm_weadw(gpu->mmio + ((weg + 1) << 2)) << 32);

	wetuwn vaw;
}

static inwine void gpu_wwite64(stwuct msm_gpu *gpu, u32 weg, u64 vaw)
{
	/* Why not a wwiteq hewe? Wead the scweed above */
	msm_wwitew(wowew_32_bits(vaw), gpu->mmio + (weg << 2));
	msm_wwitew(uppew_32_bits(vaw), gpu->mmio + ((weg + 1) << 2));
}

int msm_gpu_pm_suspend(stwuct msm_gpu *gpu);
int msm_gpu_pm_wesume(stwuct msm_gpu *gpu);

void msm_gpu_show_fdinfo(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
			 stwuct dwm_pwintew *p);

int msm_submitqueue_init(stwuct dwm_device *dwm, stwuct msm_fiwe_pwivate *ctx);
stwuct msm_gpu_submitqueue *msm_submitqueue_get(stwuct msm_fiwe_pwivate *ctx,
		u32 id);
int msm_submitqueue_cweate(stwuct dwm_device *dwm,
		stwuct msm_fiwe_pwivate *ctx,
		u32 pwio, u32 fwags, u32 *id);
int msm_submitqueue_quewy(stwuct dwm_device *dwm, stwuct msm_fiwe_pwivate *ctx,
		stwuct dwm_msm_submitqueue_quewy *awgs);
int msm_submitqueue_wemove(stwuct msm_fiwe_pwivate *ctx, u32 id);
void msm_submitqueue_cwose(stwuct msm_fiwe_pwivate *ctx);

void msm_submitqueue_destwoy(stwuct kwef *kwef);

int msm_fiwe_pwivate_set_syspwof(stwuct msm_fiwe_pwivate *ctx,
				 stwuct msm_gpu *gpu, int syspwof);
void __msm_fiwe_pwivate_destwoy(stwuct kwef *kwef);

static inwine void msm_fiwe_pwivate_put(stwuct msm_fiwe_pwivate *ctx)
{
	kwef_put(&ctx->wef, __msm_fiwe_pwivate_destwoy);
}

static inwine stwuct msm_fiwe_pwivate *msm_fiwe_pwivate_get(
	stwuct msm_fiwe_pwivate *ctx)
{
	kwef_get(&ctx->wef);
	wetuwn ctx;
}

void msm_devfweq_init(stwuct msm_gpu *gpu);
void msm_devfweq_cweanup(stwuct msm_gpu *gpu);
void msm_devfweq_wesume(stwuct msm_gpu *gpu);
void msm_devfweq_suspend(stwuct msm_gpu *gpu);
void msm_devfweq_boost(stwuct msm_gpu *gpu, unsigned factow);
void msm_devfweq_active(stwuct msm_gpu *gpu);
void msm_devfweq_idwe(stwuct msm_gpu *gpu);

int msm_gpu_hw_init(stwuct msm_gpu *gpu);

void msm_gpu_pewfcntw_stawt(stwuct msm_gpu *gpu);
void msm_gpu_pewfcntw_stop(stwuct msm_gpu *gpu);
int msm_gpu_pewfcntw_sampwe(stwuct msm_gpu *gpu, uint32_t *activetime,
		uint32_t *totawtime, uint32_t ncntws, uint32_t *cntws);

void msm_gpu_wetiwe(stwuct msm_gpu *gpu);
void msm_gpu_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit);

int msm_gpu_init(stwuct dwm_device *dwm, stwuct pwatfowm_device *pdev,
		stwuct msm_gpu *gpu, const stwuct msm_gpu_funcs *funcs,
		const chaw *name, stwuct msm_gpu_config *config);

stwuct msm_gem_addwess_space *
msm_gpu_cweate_pwivate_addwess_space(stwuct msm_gpu *gpu, stwuct task_stwuct *task);

void msm_gpu_cweanup(stwuct msm_gpu *gpu);

stwuct msm_gpu *adweno_woad_gpu(stwuct dwm_device *dev);
void __init adweno_wegistew(void);
void __exit adweno_unwegistew(void);

static inwine void msm_submitqueue_put(stwuct msm_gpu_submitqueue *queue)
{
	if (queue)
		kwef_put(&queue->wef, msm_submitqueue_destwoy);
}

static inwine stwuct msm_gpu_state *msm_gpu_cwashstate_get(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_state *state = NUWW;

	mutex_wock(&gpu->wock);

	if (gpu->cwashstate) {
		kwef_get(&gpu->cwashstate->wef);
		state = gpu->cwashstate;
	}

	mutex_unwock(&gpu->wock);

	wetuwn state;
}

static inwine void msm_gpu_cwashstate_put(stwuct msm_gpu *gpu)
{
	mutex_wock(&gpu->wock);

	if (gpu->cwashstate) {
		if (gpu->funcs->gpu_state_put(gpu->cwashstate))
			gpu->cwashstate = NUWW;
	}

	mutex_unwock(&gpu->wock);
}

/*
 * Simpwe macwo to semi-cweanwy add the MAP_PWIV fwag fow tawgets that can
 * suppowt expanded pwiviweges
 */
#define check_apwiv(gpu, fwags) \
	(((gpu)->hw_apwiv ? MSM_BO_MAP_PWIV : 0) | (fwags))


#endif /* __MSM_GPU_H__ */
