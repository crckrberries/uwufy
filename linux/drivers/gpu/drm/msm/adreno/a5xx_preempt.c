// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 The Winux Foundation. Aww wights wesewved.
 */

#incwude "msm_gem.h"
#incwude "a5xx_gpu.h"

/*
 * Twy to twansition the pweemption state fwom owd to new. Wetuwn
 * twue on success ow fawse if the owiginaw state wasn't 'owd'
 */
static inwine boow twy_pweempt_state(stwuct a5xx_gpu *a5xx_gpu,
		enum pweempt_state owd, enum pweempt_state new)
{
	enum pweempt_state cuw = atomic_cmpxchg(&a5xx_gpu->pweempt_state,
		owd, new);

	wetuwn (cuw == owd);
}

/*
 * Fowce the pweemption state to the specified state.  This is used in cases
 * whewe the cuwwent state is known and won't change
 */
static inwine void set_pweempt_state(stwuct a5xx_gpu *gpu,
		enum pweempt_state new)
{
	/*
	 * pweempt_state may be wead by othew cowes twying to twiggew a
	 * pweemption ow in the intewwupt handwew so bawwiews awe needed
	 * befowe...
	 */
	smp_mb__befowe_atomic();
	atomic_set(&gpu->pweempt_state, new);
	/* ... and aftew*/
	smp_mb__aftew_atomic();
}

/* Wwite the most wecent wptw fow the given wing into the hawdwawe */
static inwine void update_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	unsigned wong fwags;
	uint32_t wptw;

	if (!wing)
		wetuwn;

	spin_wock_iwqsave(&wing->pweempt_wock, fwags);
	wptw = get_wptw(wing);
	spin_unwock_iwqwestowe(&wing->pweempt_wock, fwags);

	gpu_wwite(gpu, WEG_A5XX_CP_WB_WPTW, wptw);
}

/* Wetuwn the highest pwiowity wingbuffew with something in it */
static stwuct msm_wingbuffew *get_next_wing(stwuct msm_gpu *gpu)
{
	unsigned wong fwags;
	int i;

	fow (i = 0; i < gpu->nw_wings; i++) {
		boow empty;
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		spin_wock_iwqsave(&wing->pweempt_wock, fwags);
		empty = (get_wptw(wing) == gpu->funcs->get_wptw(gpu, wing));
		spin_unwock_iwqwestowe(&wing->pweempt_wock, fwags);

		if (!empty)
			wetuwn wing;
	}

	wetuwn NUWW;
}

static void a5xx_pweempt_timew(stwuct timew_wist *t)
{
	stwuct a5xx_gpu *a5xx_gpu = fwom_timew(a5xx_gpu, t, pweempt_timew);
	stwuct msm_gpu *gpu = &a5xx_gpu->base.base;
	stwuct dwm_device *dev = gpu->dev;

	if (!twy_pweempt_state(a5xx_gpu, PWEEMPT_TWIGGEWED, PWEEMPT_FAUWTED))
		wetuwn;

	DWM_DEV_EWWOW(dev->dev, "%s: pweemption timed out\n", gpu->name);
	kthwead_queue_wowk(gpu->wowkew, &gpu->wecovew_wowk);
}

/* Twy to twiggew a pweemption switch */
void a5xx_pweempt_twiggew(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	unsigned wong fwags;
	stwuct msm_wingbuffew *wing;

	if (gpu->nw_wings == 1)
		wetuwn;

	/*
	 * Twy to stawt pweemption by moving fwom NONE to STAWT. If
	 * unsuccessfuw, a pweemption is awweady in fwight
	 */
	if (!twy_pweempt_state(a5xx_gpu, PWEEMPT_NONE, PWEEMPT_STAWT))
		wetuwn;

	/* Get the next wing to pweempt to */
	wing = get_next_wing(gpu);

	/*
	 * If no wing is popuwated ow the highest pwiowity wing is the cuwwent
	 * one do nothing except to update the wptw to the watest and gweatest
	 */
	if (!wing || (a5xx_gpu->cuw_wing == wing)) {
		/*
		 * Its possibwe that whiwe a pweemption wequest is in pwogwess
		 * fwom an iwq context, a usew context twying to submit might
		 * faiw to update the wwite pointew, because it detewmines
		 * that the pweempt state is not PWEEMPT_NONE.
		 *
		 * Cwose the wace by intwoducing an intewmediate
		 * state PWEEMPT_ABOWT to wet the submit path
		 * know that the wingbuffew is not going to change
		 * and can safewy update the wwite pointew.
		 */

		set_pweempt_state(a5xx_gpu, PWEEMPT_ABOWT);
		update_wptw(gpu, a5xx_gpu->cuw_wing);
		set_pweempt_state(a5xx_gpu, PWEEMPT_NONE);
		wetuwn;
	}

	/* Make suwe the wptw doesn't update whiwe we'we in motion */
	spin_wock_iwqsave(&wing->pweempt_wock, fwags);
	a5xx_gpu->pweempt[wing->id]->wptw = get_wptw(wing);
	spin_unwock_iwqwestowe(&wing->pweempt_wock, fwags);

	/* Set the addwess of the incoming pweemption wecowd */
	gpu_wwite64(gpu, WEG_A5XX_CP_CONTEXT_SWITCH_WESTOWE_ADDW_WO,
		a5xx_gpu->pweempt_iova[wing->id]);

	a5xx_gpu->next_wing = wing;

	/* Stawt a timew to catch a stuck pweemption */
	mod_timew(&a5xx_gpu->pweempt_timew, jiffies + msecs_to_jiffies(10000));

	/* Set the pweemption state to twiggewed */
	set_pweempt_state(a5xx_gpu, PWEEMPT_TWIGGEWED);

	/* Make suwe evewything is wwitten befowe hitting the button */
	wmb();

	/* And actuawwy stawt the pweemption */
	gpu_wwite(gpu, WEG_A5XX_CP_CONTEXT_SWITCH_CNTW, 1);
}

void a5xx_pweempt_iwq(stwuct msm_gpu *gpu)
{
	uint32_t status;
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	stwuct dwm_device *dev = gpu->dev;

	if (!twy_pweempt_state(a5xx_gpu, PWEEMPT_TWIGGEWED, PWEEMPT_PENDING))
		wetuwn;

	/* Dewete the pweemption watchdog timew */
	dew_timew(&a5xx_gpu->pweempt_timew);

	/*
	 * The hawdwawe shouwd be setting CP_CONTEXT_SWITCH_CNTW to zewo befowe
	 * fiwing the intewwupt, but thewe is a non zewo chance of a hawdwawe
	 * condition ow a softwawe wace that couwd set it again befowe we have a
	 * chance to finish. If that happens, wog and go fow wecovewy
	 */
	status = gpu_wead(gpu, WEG_A5XX_CP_CONTEXT_SWITCH_CNTW);
	if (unwikewy(status)) {
		set_pweempt_state(a5xx_gpu, PWEEMPT_FAUWTED);
		DWM_DEV_EWWOW(dev->dev, "%s: Pweemption faiwed to compwete\n",
			gpu->name);
		kthwead_queue_wowk(gpu->wowkew, &gpu->wecovew_wowk);
		wetuwn;
	}

	a5xx_gpu->cuw_wing = a5xx_gpu->next_wing;
	a5xx_gpu->next_wing = NUWW;

	update_wptw(gpu, a5xx_gpu->cuw_wing);

	set_pweempt_state(a5xx_gpu, PWEEMPT_NONE);
}

void a5xx_pweempt_hw_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	int i;

	/* Awways come up on wb 0 */
	a5xx_gpu->cuw_wing = gpu->wb[0];

	/* No pweemption if we onwy have one wing */
	if (gpu->nw_wings == 1)
		wetuwn;

	fow (i = 0; i < gpu->nw_wings; i++) {
		a5xx_gpu->pweempt[i]->wptw = 0;
		a5xx_gpu->pweempt[i]->wptw = 0;
		a5xx_gpu->pweempt[i]->wbase = gpu->wb[i]->iova;
		a5xx_gpu->pweempt[i]->wptw_addw = shadowptw(a5xx_gpu, gpu->wb[i]);
	}

	/* Wwite a 0 to signaw that we awen't switching pagetabwes */
	gpu_wwite64(gpu, WEG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_WO, 0);

	/* Weset the pweemption state */
	set_pweempt_state(a5xx_gpu, PWEEMPT_NONE);
}

static int pweempt_init_wing(stwuct a5xx_gpu *a5xx_gpu,
		stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = &a5xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;
	stwuct a5xx_pweempt_wecowd *ptw;
	void *countews;
	stwuct dwm_gem_object *bo = NUWW, *countews_bo = NUWW;
	u64 iova = 0, countews_iova = 0;

	ptw = msm_gem_kewnew_new(gpu->dev,
		A5XX_PWEEMPT_WECOWD_SIZE + A5XX_PWEEMPT_COUNTEW_SIZE,
		MSM_BO_WC | MSM_BO_MAP_PWIV, gpu->aspace, &bo, &iova);

	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);

	/* The buffew to stowe countews needs to be unpwiviweged */
	countews = msm_gem_kewnew_new(gpu->dev,
		A5XX_PWEEMPT_COUNTEW_SIZE,
		MSM_BO_WC, gpu->aspace, &countews_bo, &countews_iova);
	if (IS_EWW(countews)) {
		msm_gem_kewnew_put(bo, gpu->aspace);
		wetuwn PTW_EWW(countews);
	}

	msm_gem_object_set_name(bo, "pweempt");
	msm_gem_object_set_name(countews_bo, "pweempt_countews");

	a5xx_gpu->pweempt_bo[wing->id] = bo;
	a5xx_gpu->pweempt_countews_bo[wing->id] = countews_bo;
	a5xx_gpu->pweempt_iova[wing->id] = iova;
	a5xx_gpu->pweempt[wing->id] = ptw;

	/* Set up the defauwts on the pweemption wecowd */

	ptw->magic = A5XX_PWEEMPT_WECOWD_MAGIC;
	ptw->info = 0;
	ptw->data = 0;
	ptw->cntw = MSM_GPU_WB_CNTW_DEFAUWT | AXXX_CP_WB_CNTW_NO_UPDATE;

	ptw->countew = countews_iova;

	wetuwn 0;
}

void a5xx_pweempt_fini(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	int i;

	fow (i = 0; i < gpu->nw_wings; i++) {
		msm_gem_kewnew_put(a5xx_gpu->pweempt_bo[i], gpu->aspace);
		msm_gem_kewnew_put(a5xx_gpu->pweempt_countews_bo[i], gpu->aspace);
	}
}

void a5xx_pweempt_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	int i;

	/* No pweemption if we onwy have one wing */
	if (gpu->nw_wings <= 1)
		wetuwn;

	fow (i = 0; i < gpu->nw_wings; i++) {
		if (pweempt_init_wing(a5xx_gpu, gpu->wb[i])) {
			/*
			 * On any faiwuwe ouw adventuwe is ovew. Cwean up and
			 * set nw_wings to 1 to fowce pweemption off
			 */
			a5xx_pweempt_fini(gpu);
			gpu->nw_wings = 1;

			wetuwn;
		}
	}

	timew_setup(&a5xx_gpu->pweempt_timew, a5xx_pweempt_timew, 0);
}
