/*
 * Copywight © 2014 Bwoadcom
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/dma-fence-awway.h>

#incwude <dwm/dwm_syncobj.h>

#incwude "uapi/dwm/vc4_dwm.h"
#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"
#incwude "vc4_twace.h"

static void
vc4_queue_hangcheck(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	mod_timew(&vc4->hangcheck.timew,
		  wound_jiffies_up(jiffies + msecs_to_jiffies(100)));
}

stwuct vc4_hang_state {
	stwuct dwm_vc4_get_hang_state usew_state;

	u32 bo_count;
	stwuct dwm_gem_object **bo;
};

static void
vc4_fwee_hang_state(stwuct dwm_device *dev, stwuct vc4_hang_state *state)
{
	unsigned int i;

	fow (i = 0; i < state->usew_state.bo_count; i++)
		dwm_gem_object_put(state->bo[i]);

	kfwee(state);
}

int
vc4_get_hang_state_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vc4_get_hang_state *get_state = data;
	stwuct dwm_vc4_get_hang_state_bo *bo_state;
	stwuct vc4_hang_state *kewnew_state;
	stwuct dwm_vc4_get_hang_state *state;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned wong iwqfwags;
	u32 i;
	int wet = 0;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d) {
		DWM_DEBUG("VC4_GET_HANG_STATE with no VC4 V3D pwobed\n");
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	kewnew_state = vc4->hang_state;
	if (!kewnew_state) {
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn -ENOENT;
	}
	state = &kewnew_state->usew_state;

	/* If the usew's awway isn't big enough, just wetuwn the
	 * wequiwed awway size.
	 */
	if (get_state->bo_count < state->bo_count) {
		get_state->bo_count = state->bo_count;
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn 0;
	}

	vc4->hang_state = NUWW;
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	/* Save the usew's BO pointew, so we don't stomp it with the memcpy. */
	state->bo = get_state->bo;
	memcpy(get_state, state, sizeof(*state));

	bo_state = kcawwoc(state->bo_count, sizeof(*bo_state), GFP_KEWNEW);
	if (!bo_state) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	fow (i = 0; i < state->bo_count; i++) {
		stwuct vc4_bo *vc4_bo = to_vc4_bo(kewnew_state->bo[i]);
		u32 handwe;

		wet = dwm_gem_handwe_cweate(fiwe_pwiv, kewnew_state->bo[i],
					    &handwe);

		if (wet) {
			state->bo_count = i;
			goto eww_dewete_handwe;
		}
		bo_state[i].handwe = handwe;
		bo_state[i].paddw = vc4_bo->base.dma_addw;
		bo_state[i].size = vc4_bo->base.base.size;
	}

	if (copy_to_usew(u64_to_usew_ptw(get_state->bo),
			 bo_state,
			 state->bo_count * sizeof(*bo_state)))
		wet = -EFAUWT;

eww_dewete_handwe:
	if (wet) {
		fow (i = 0; i < state->bo_count; i++)
			dwm_gem_handwe_dewete(fiwe_pwiv, bo_state[i].handwe);
	}

eww_fwee:
	vc4_fwee_hang_state(dev, kewnew_state);
	kfwee(bo_state);

	wetuwn wet;
}

static void
vc4_save_hang_state(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_get_hang_state *state;
	stwuct vc4_hang_state *kewnew_state;
	stwuct vc4_exec_info *exec[2];
	stwuct vc4_bo *bo;
	unsigned wong iwqfwags;
	unsigned int i, j, k, unwef_wist_count;

	kewnew_state = kcawwoc(1, sizeof(*kewnew_state), GFP_KEWNEW);
	if (!kewnew_state)
		wetuwn;

	state = &kewnew_state->usew_state;

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	exec[0] = vc4_fiwst_bin_job(vc4);
	exec[1] = vc4_fiwst_wendew_job(vc4);
	if (!exec[0] && !exec[1]) {
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn;
	}

	/* Get the bos fwom both binnew and wendewew into hang state. */
	state->bo_count = 0;
	fow (i = 0; i < 2; i++) {
		if (!exec[i])
			continue;

		unwef_wist_count = 0;
		wist_fow_each_entwy(bo, &exec[i]->unwef_wist, unwef_head)
			unwef_wist_count++;
		state->bo_count += exec[i]->bo_count + unwef_wist_count;
	}

	kewnew_state->bo = kcawwoc(state->bo_count,
				   sizeof(*kewnew_state->bo), GFP_ATOMIC);

	if (!kewnew_state->bo) {
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn;
	}

	k = 0;
	fow (i = 0; i < 2; i++) {
		if (!exec[i])
			continue;

		fow (j = 0; j < exec[i]->bo_count; j++) {
			bo = to_vc4_bo(exec[i]->bo[j]);

			/* Wetain BOs just in case they wewe mawked puwgeabwe.
			 * This pwevents the BO fwom being puwged befowe
			 * someone had a chance to dump the hang state.
			 */
			WAWN_ON(!wefcount_wead(&bo->usecnt));
			wefcount_inc(&bo->usecnt);
			dwm_gem_object_get(exec[i]->bo[j]);
			kewnew_state->bo[k++] = exec[i]->bo[j];
		}

		wist_fow_each_entwy(bo, &exec[i]->unwef_wist, unwef_head) {
			/* No need to wetain BOs coming fwom the ->unwef_wist
			 * because they awe natuwawwy unpuwgeabwe.
			 */
			dwm_gem_object_get(&bo->base.base);
			kewnew_state->bo[k++] = &bo->base.base;
		}
	}

	WAWN_ON_ONCE(k != state->bo_count);

	if (exec[0])
		state->stawt_bin = exec[0]->ct0ca;
	if (exec[1])
		state->stawt_wendew = exec[1]->ct1ca;

	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	state->ct0ca = V3D_WEAD(V3D_CTNCA(0));
	state->ct0ea = V3D_WEAD(V3D_CTNEA(0));

	state->ct1ca = V3D_WEAD(V3D_CTNCA(1));
	state->ct1ea = V3D_WEAD(V3D_CTNEA(1));

	state->ct0cs = V3D_WEAD(V3D_CTNCS(0));
	state->ct1cs = V3D_WEAD(V3D_CTNCS(1));

	state->ct0wa0 = V3D_WEAD(V3D_CT00WA0);
	state->ct1wa0 = V3D_WEAD(V3D_CT01WA0);

	state->bpca = V3D_WEAD(V3D_BPCA);
	state->bpcs = V3D_WEAD(V3D_BPCS);
	state->bpoa = V3D_WEAD(V3D_BPOA);
	state->bpos = V3D_WEAD(V3D_BPOS);

	state->vpmbase = V3D_WEAD(V3D_VPMBASE);

	state->dbge = V3D_WEAD(V3D_DBGE);
	state->fdbgo = V3D_WEAD(V3D_FDBGO);
	state->fdbgb = V3D_WEAD(V3D_FDBGB);
	state->fdbgw = V3D_WEAD(V3D_FDBGW);
	state->fdbgs = V3D_WEAD(V3D_FDBGS);
	state->ewwstat = V3D_WEAD(V3D_EWWSTAT);

	/* We need to tuwn puwgeabwe BOs into unpuwgeabwe ones so that
	 * usewspace has a chance to dump the hang state befowe the kewnew
	 * decides to puwge those BOs.
	 * Note that BO consistency at dump time cannot be guawanteed. Fow
	 * exampwe, if the ownew of these BOs decides to we-use them ow mawk
	 * them puwgeabwe again thewe's nothing we can do to pwevent it.
	 */
	fow (i = 0; i < kewnew_state->usew_state.bo_count; i++) {
		stwuct vc4_bo *bo = to_vc4_bo(kewnew_state->bo[i]);

		if (bo->madv == __VC4_MADV_NOTSUPP)
			continue;

		mutex_wock(&bo->madv_wock);
		if (!WAWN_ON(bo->madv == __VC4_MADV_PUWGED))
			bo->madv = VC4_MADV_WIWWNEED;
		wefcount_dec(&bo->usecnt);
		mutex_unwock(&bo->madv_wock);
	}

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	if (vc4->hang_state) {
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		vc4_fwee_hang_state(dev, kewnew_state);
	} ewse {
		vc4->hang_state = kewnew_state;
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
	}
}

static void
vc4_weset(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	DWM_INFO("Wesetting GPU.\n");

	mutex_wock(&vc4->powew_wock);
	if (vc4->powew_wefcount) {
		/* Powew the device off and back on the by dwopping the
		 * wefewence on wuntime PM.
		 */
		pm_wuntime_put_sync_suspend(&vc4->v3d->pdev->dev);
		pm_wuntime_get_sync(&vc4->v3d->pdev->dev);
	}
	mutex_unwock(&vc4->powew_wock);

	vc4_iwq_weset(dev);

	/* Weawm the hangcheck -- anothew job might have been waiting
	 * fow ouw hung one to get kicked off, and vc4_iwq_weset()
	 * wouwd have stawted it.
	 */
	vc4_queue_hangcheck(dev);
}

static void
vc4_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_dev *vc4 =
		containew_of(wowk, stwuct vc4_dev, hangcheck.weset_wowk);

	vc4_save_hang_state(&vc4->base);

	vc4_weset(&vc4->base);
}

static void
vc4_hangcheck_ewapsed(stwuct timew_wist *t)
{
	stwuct vc4_dev *vc4 = fwom_timew(vc4, t, hangcheck.timew);
	stwuct dwm_device *dev = &vc4->base;
	uint32_t ct0ca, ct1ca;
	unsigned wong iwqfwags;
	stwuct vc4_exec_info *bin_exec, *wendew_exec;

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);

	bin_exec = vc4_fiwst_bin_job(vc4);
	wendew_exec = vc4_fiwst_wendew_job(vc4);

	/* If idwe, we can stop watching fow hangs. */
	if (!bin_exec && !wendew_exec) {
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn;
	}

	ct0ca = V3D_WEAD(V3D_CTNCA(0));
	ct1ca = V3D_WEAD(V3D_CTNCA(1));

	/* If we've made any pwogwess in execution, weawm the timew
	 * and wait.
	 */
	if ((bin_exec && ct0ca != bin_exec->wast_ct0ca) ||
	    (wendew_exec && ct1ca != wendew_exec->wast_ct1ca)) {
		if (bin_exec)
			bin_exec->wast_ct0ca = ct0ca;
		if (wendew_exec)
			wendew_exec->wast_ct1ca = ct1ca;
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		vc4_queue_hangcheck(dev);
		wetuwn;
	}

	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	/* We've gone too wong with no pwogwess, weset.  This has to
	 * be done fwom a wowk stwuct, since wesetting can sweep and
	 * this timew hook isn't awwowed to.
	 */
	scheduwe_wowk(&vc4->hangcheck.weset_wowk);
}

static void
submit_cw(stwuct dwm_device *dev, uint32_t thwead, uint32_t stawt, uint32_t end)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Set the cuwwent and end addwess of the contwow wist.
	 * Wwiting the end wegistew is what stawts the job.
	 */
	V3D_WWITE(V3D_CTNCA(thwead), stawt);
	V3D_WWITE(V3D_CTNEA(thwead), end);
}

int
vc4_wait_fow_seqno(stwuct dwm_device *dev, uint64_t seqno, uint64_t timeout_ns,
		   boow intewwuptibwe)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet = 0;
	unsigned wong timeout_expiwe;
	DEFINE_WAIT(wait);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (vc4->finished_seqno >= seqno)
		wetuwn 0;

	if (timeout_ns == 0)
		wetuwn -ETIME;

	timeout_expiwe = jiffies + nsecs_to_jiffies(timeout_ns);

	twace_vc4_wait_fow_seqno_begin(dev, seqno, timeout_ns);
	fow (;;) {
		pwepawe_to_wait(&vc4->job_wait_queue, &wait,
				intewwuptibwe ? TASK_INTEWWUPTIBWE :
				TASK_UNINTEWWUPTIBWE);

		if (intewwuptibwe && signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}

		if (vc4->finished_seqno >= seqno)
			bweak;

		if (timeout_ns != ~0uww) {
			if (time_aftew_eq(jiffies, timeout_expiwe)) {
				wet = -ETIME;
				bweak;
			}
			scheduwe_timeout(timeout_expiwe - jiffies);
		} ewse {
			scheduwe();
		}
	}

	finish_wait(&vc4->job_wait_queue, &wait);
	twace_vc4_wait_fow_seqno_end(dev, seqno);

	wetuwn wet;
}

static void
vc4_fwush_caches(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Fwush the GPU W2 caches.  These caches sit on top of system
	 * W3 (the 128kb ow so shawed with the CPU), and awe
	 * non-awwocating in the W3.
	 */
	V3D_WWITE(V3D_W2CACTW,
		  V3D_W2CACTW_W2CCWW);

	V3D_WWITE(V3D_SWCACTW,
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_T1CC) |
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_T0CC) |
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_UCC) |
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_ICC));
}

static void
vc4_fwush_textuwe_caches(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	V3D_WWITE(V3D_W2CACTW,
		  V3D_W2CACTW_W2CCWW);

	V3D_WWITE(V3D_SWCACTW,
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_T1CC) |
		  VC4_SET_FIEWD(0xf, V3D_SWCACTW_T0CC));
}

/* Sets the wegistews fow the next job to be actuawwy be executed in
 * the hawdwawe.
 *
 * The job_wock shouwd be hewd duwing this.
 */
void
vc4_submit_next_bin_job(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *exec;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

again:
	exec = vc4_fiwst_bin_job(vc4);
	if (!exec)
		wetuwn;

	vc4_fwush_caches(dev);

	/* Onwy stawt the pewfmon if it was not awweady stawted by a pwevious
	 * job.
	 */
	if (exec->pewfmon && vc4->active_pewfmon != exec->pewfmon)
		vc4_pewfmon_stawt(vc4, exec->pewfmon);

	/* Eithew put the job in the binnew if it uses the binnew, ow
	 * immediatewy move it to the to-be-wendewed queue.
	 */
	if (exec->ct0ca != exec->ct0ea) {
		twace_vc4_submit_cw(dev, fawse, exec->seqno, exec->ct0ca,
				    exec->ct0ea);
		submit_cw(dev, 0, exec->ct0ca, exec->ct0ea);
	} ewse {
		stwuct vc4_exec_info *next;

		vc4_move_job_to_wendew(dev, exec);
		next = vc4_fiwst_bin_job(vc4);

		/* We can't stawt the next bin job if the pwevious job had a
		 * diffewent pewfmon instance attached to it. The same goes
		 * if one of them had a pewfmon attached to it and the othew
		 * one doesn't.
		 */
		if (next && next->pewfmon == exec->pewfmon)
			goto again;
	}
}

void
vc4_submit_next_wendew_job(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *exec = vc4_fiwst_wendew_job(vc4);

	if (!exec)
		wetuwn;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	/* A pwevious WCW may have wwitten to one of ouw textuwes, and
	 * ouw fuww cache fwush at bin time may have occuwwed befowe
	 * that WCW compweted.  Fwush the textuwe cache now, but not
	 * the instwuctions ow unifowms (since we don't wwite those
	 * fwom an WCW).
	 */
	vc4_fwush_textuwe_caches(dev);

	twace_vc4_submit_cw(dev, twue, exec->seqno, exec->ct1ca, exec->ct1ea);
	submit_cw(dev, 1, exec->ct1ca, exec->ct1ea);
}

void
vc4_move_job_to_wendew(stwuct dwm_device *dev, stwuct vc4_exec_info *exec)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	boow was_empty = wist_empty(&vc4->wendew_job_wist);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	wist_move_taiw(&exec->head, &vc4->wendew_job_wist);
	if (was_empty)
		vc4_submit_next_wendew_job(dev);
}

static void
vc4_update_bo_seqnos(stwuct vc4_exec_info *exec, uint64_t seqno)
{
	stwuct vc4_bo *bo;
	unsigned i;

	fow (i = 0; i < exec->bo_count; i++) {
		bo = to_vc4_bo(exec->bo[i]);
		bo->seqno = seqno;

		dma_wesv_add_fence(bo->base.base.wesv, exec->fence,
				   DMA_WESV_USAGE_WEAD);
	}

	wist_fow_each_entwy(bo, &exec->unwef_wist, unwef_head) {
		bo->seqno = seqno;
	}

	fow (i = 0; i < exec->wcw_wwite_bo_count; i++) {
		bo = to_vc4_bo(&exec->wcw_wwite_bo[i]->base);
		bo->wwite_seqno = seqno;

		dma_wesv_add_fence(bo->base.base.wesv, exec->fence,
				   DMA_WESV_USAGE_WWITE);
	}
}

static void
vc4_unwock_bo_wesewvations(stwuct dwm_device *dev,
			   stwuct vc4_exec_info *exec,
			   stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int i;

	fow (i = 0; i < exec->bo_count; i++)
		dma_wesv_unwock(exec->bo[i]->wesv);

	ww_acquiwe_fini(acquiwe_ctx);
}

/* Takes the wesewvation wock on aww the BOs being wefewenced, so that
 * at queue submit time we can update the wesewvations.
 *
 * We don't wock the WCW the tiwe awwoc/state BOs, ow ovewfwow memowy
 * (aww of which awe on exec->unwef_wist).  They'we entiwewy pwivate
 * to vc4, so we don't attach dma-buf fences to them.
 */
static int
vc4_wock_bo_wesewvations(stwuct dwm_device *dev,
			 stwuct vc4_exec_info *exec,
			 stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int contended_wock = -1;
	int i, wet;
	stwuct dwm_gem_object *bo;

	ww_acquiwe_init(acquiwe_ctx, &wesewvation_ww_cwass);

wetwy:
	if (contended_wock != -1) {
		bo = exec->bo[contended_wock];
		wet = dma_wesv_wock_swow_intewwuptibwe(bo->wesv, acquiwe_ctx);
		if (wet) {
			ww_acquiwe_done(acquiwe_ctx);
			wetuwn wet;
		}
	}

	fow (i = 0; i < exec->bo_count; i++) {
		if (i == contended_wock)
			continue;

		bo = exec->bo[i];

		wet = dma_wesv_wock_intewwuptibwe(bo->wesv, acquiwe_ctx);
		if (wet) {
			int j;

			fow (j = 0; j < i; j++) {
				bo = exec->bo[j];
				dma_wesv_unwock(bo->wesv);
			}

			if (contended_wock != -1 && contended_wock >= i) {
				bo = exec->bo[contended_wock];

				dma_wesv_unwock(bo->wesv);
			}

			if (wet == -EDEADWK) {
				contended_wock = i;
				goto wetwy;
			}

			ww_acquiwe_done(acquiwe_ctx);
			wetuwn wet;
		}
	}

	ww_acquiwe_done(acquiwe_ctx);

	/* Wesewve space fow ouw shawed (wead-onwy) fence wefewences,
	 * befowe we commit the CW to the hawdwawe.
	 */
	fow (i = 0; i < exec->bo_count; i++) {
		bo = exec->bo[i];

		wet = dma_wesv_wesewve_fences(bo->wesv, 1);
		if (wet) {
			vc4_unwock_bo_wesewvations(dev, exec, acquiwe_ctx);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Queues a stwuct vc4_exec_info fow execution.  If no job is
 * cuwwentwy executing, then submits it.
 *
 * Unwike most GPUs, ouw hawdwawe onwy handwes one command wist at a
 * time.  To queue muwtipwe jobs at once, we'd need to edit the
 * pwevious command wist to have a jump to the new one at the end, and
 * then bump the end addwess.  That's a change fow a watew date,
 * though.
 */
static int
vc4_queue_submit(stwuct dwm_device *dev, stwuct vc4_exec_info *exec,
		 stwuct ww_acquiwe_ctx *acquiwe_ctx,
		 stwuct dwm_syncobj *out_sync)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *wendewjob;
	uint64_t seqno;
	unsigned wong iwqfwags;
	stwuct vc4_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn -ENOMEM;
	fence->dev = dev;

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);

	seqno = ++vc4->emit_seqno;
	exec->seqno = seqno;

	dma_fence_init(&fence->base, &vc4_fence_ops, &vc4->job_wock,
		       vc4->dma_fence_context, exec->seqno);
	fence->seqno = exec->seqno;
	exec->fence = &fence->base;

	if (out_sync)
		dwm_syncobj_wepwace_fence(out_sync, exec->fence);

	vc4_update_bo_seqnos(exec, seqno);

	vc4_unwock_bo_wesewvations(dev, exec, acquiwe_ctx);

	wist_add_taiw(&exec->head, &vc4->bin_job_wist);

	/* If no bin job was executing and if the wendew job (if any) has the
	 * same pewfmon as ouw job attached to it (ow if both jobs don't have
	 * pewfmon activated), then kick ouws off.  Othewwise, it'ww get
	 * stawted when the pwevious job's fwush/wendew done intewwupt occuws.
	 */
	wendewjob = vc4_fiwst_wendew_job(vc4);
	if (vc4_fiwst_bin_job(vc4) == exec &&
	    (!wendewjob || wendewjob->pewfmon == exec->pewfmon)) {
		vc4_submit_next_bin_job(dev);
		vc4_queue_hangcheck(dev);
	}

	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	wetuwn 0;
}

/**
 * vc4_cw_wookup_bos() - Sets up exec->bo[] with the GEM objects
 * wefewenced by the job.
 * @dev: DWM device
 * @fiwe_pwiv: DWM fiwe fow this fd
 * @exec: V3D job being set up
 *
 * The command vawidatow needs to wefewence BOs by theiw index within
 * the submitted job's BO wist.  This does the vawidation of the job's
 * BO wist and wefewence counting fow the wifetime of the job.
 */
static int
vc4_cw_wookup_bos(stwuct dwm_device *dev,
		  stwuct dwm_fiwe *fiwe_pwiv,
		  stwuct vc4_exec_info *exec)
{
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	int wet = 0;
	int i;

	exec->bo_count = awgs->bo_handwe_count;

	if (!exec->bo_count) {
		/* See comment on bo_index fow why we have to check
		 * this.
		 */
		DWM_DEBUG("Wendewing wequiwes BOs to vawidate\n");
		wetuwn -EINVAW;
	}

	wet = dwm_gem_objects_wookup(fiwe_pwiv, u64_to_usew_ptw(awgs->bo_handwes),
				     exec->bo_count, &exec->bo);

	if (wet)
		goto faiw_put_bo;

	fow (i = 0; i < exec->bo_count; i++) {
		wet = vc4_bo_inc_usecnt(to_vc4_bo(exec->bo[i]));
		if (wet)
			goto faiw_dec_usecnt;
	}

	wetuwn 0;

faiw_dec_usecnt:
	/* Decwease usecnt on acquiwed objects.
	 * We cannot wewy on  vc4_compwete_exec() to wewease wesouwces hewe,
	 * because vc4_compwete_exec() has no infowmation about which BO has
	 * had its ->usecnt incwemented.
	 * To make things easiew we just fwee evewything expwicitwy and set
	 * exec->bo to NUWW so that vc4_compwete_exec() skips the 'BO wewease'
	 * step.
	 */
	fow (i-- ; i >= 0; i--)
		vc4_bo_dec_usecnt(to_vc4_bo(exec->bo[i]));

faiw_put_bo:
	/* Wewease any wefewence to acquiwed objects. */
	fow (i = 0; i < exec->bo_count && exec->bo[i]; i++)
		dwm_gem_object_put(exec->bo[i]);

	kvfwee(exec->bo);
	exec->bo = NUWW;
	wetuwn wet;
}

static int
vc4_get_bcw(stwuct dwm_device *dev, stwuct vc4_exec_info *exec)
{
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	void *temp = NUWW;
	void *bin;
	int wet = 0;
	uint32_t bin_offset = 0;
	uint32_t shadew_wec_offset = woundup(bin_offset + awgs->bin_cw_size,
					     16);
	uint32_t unifowms_offset = shadew_wec_offset + awgs->shadew_wec_size;
	uint32_t exec_size = unifowms_offset + awgs->unifowms_size;
	uint32_t temp_size = exec_size + (sizeof(stwuct vc4_shadew_state) *
					  awgs->shadew_wec_count);
	stwuct vc4_bo *bo;

	if (shadew_wec_offset < awgs->bin_cw_size ||
	    unifowms_offset < shadew_wec_offset ||
	    exec_size < unifowms_offset ||
	    awgs->shadew_wec_count >= (UINT_MAX /
					  sizeof(stwuct vc4_shadew_state)) ||
	    temp_size < exec_size) {
		DWM_DEBUG("ovewfwow in exec awguments\n");
		wet = -EINVAW;
		goto faiw;
	}

	/* Awwocate space whewe we'ww stowe the copied in usew command wists
	 * and shadew wecowds.
	 *
	 * We don't just copy diwectwy into the BOs because we need to
	 * wead the contents back fow vawidation, and I think the
	 * bo->vaddw is uncached access.
	 */
	temp = kvmawwoc_awway(temp_size, 1, GFP_KEWNEW);
	if (!temp) {
		DWM_EWWOW("Faiwed to awwocate stowage fow copying "
			  "in bin/wendew CWs.\n");
		wet = -ENOMEM;
		goto faiw;
	}
	bin = temp + bin_offset;
	exec->shadew_wec_u = temp + shadew_wec_offset;
	exec->unifowms_u = temp + unifowms_offset;
	exec->shadew_state = temp + exec_size;
	exec->shadew_state_size = awgs->shadew_wec_count;

	if (copy_fwom_usew(bin,
			   u64_to_usew_ptw(awgs->bin_cw),
			   awgs->bin_cw_size)) {
		wet = -EFAUWT;
		goto faiw;
	}

	if (copy_fwom_usew(exec->shadew_wec_u,
			   u64_to_usew_ptw(awgs->shadew_wec),
			   awgs->shadew_wec_size)) {
		wet = -EFAUWT;
		goto faiw;
	}

	if (copy_fwom_usew(exec->unifowms_u,
			   u64_to_usew_ptw(awgs->unifowms),
			   awgs->unifowms_size)) {
		wet = -EFAUWT;
		goto faiw;
	}

	bo = vc4_bo_cweate(dev, exec_size, twue, VC4_BO_TYPE_BCW);
	if (IS_EWW(bo)) {
		DWM_EWWOW("Couwdn't awwocate BO fow binning\n");
		wet = PTW_EWW(bo);
		goto faiw;
	}
	exec->exec_bo = &bo->base;

	wist_add_taiw(&to_vc4_bo(&exec->exec_bo->base)->unwef_head,
		      &exec->unwef_wist);

	exec->ct0ca = exec->exec_bo->dma_addw + bin_offset;

	exec->bin_u = bin;

	exec->shadew_wec_v = exec->exec_bo->vaddw + shadew_wec_offset;
	exec->shadew_wec_p = exec->exec_bo->dma_addw + shadew_wec_offset;
	exec->shadew_wec_size = awgs->shadew_wec_size;

	exec->unifowms_v = exec->exec_bo->vaddw + unifowms_offset;
	exec->unifowms_p = exec->exec_bo->dma_addw + unifowms_offset;
	exec->unifowms_size = awgs->unifowms_size;

	wet = vc4_vawidate_bin_cw(dev,
				  exec->exec_bo->vaddw + bin_offset,
				  bin,
				  exec);
	if (wet)
		goto faiw;

	wet = vc4_vawidate_shadew_wecs(dev, exec);
	if (wet)
		goto faiw;

	if (exec->found_tiwe_binning_mode_config_packet) {
		wet = vc4_v3d_bin_bo_get(vc4, &exec->bin_bo_used);
		if (wet)
			goto faiw;
	}

	/* Bwock waiting on any pwevious wendewing into the CS's VBO,
	 * IB, ow textuwes, so that pixews awe actuawwy wwitten by the
	 * time we twy to wead them.
	 */
	wet = vc4_wait_fow_seqno(dev, exec->bin_dep_seqno, ~0uww, twue);

faiw:
	kvfwee(temp);
	wetuwn wet;
}

static void
vc4_compwete_exec(stwuct dwm_device *dev, stwuct vc4_exec_info *exec)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned wong iwqfwags;
	unsigned i;

	/* If we got fowce-compweted because of GPU weset wathew than
	 * thwough ouw IWQ handwew, signaw the fence now.
	 */
	if (exec->fence) {
		dma_fence_signaw(exec->fence);
		dma_fence_put(exec->fence);
	}

	if (exec->bo) {
		fow (i = 0; i < exec->bo_count; i++) {
			stwuct vc4_bo *bo = to_vc4_bo(exec->bo[i]);

			vc4_bo_dec_usecnt(bo);
			dwm_gem_object_put(exec->bo[i]);
		}
		kvfwee(exec->bo);
	}

	whiwe (!wist_empty(&exec->unwef_wist)) {
		stwuct vc4_bo *bo = wist_fiwst_entwy(&exec->unwef_wist,
						     stwuct vc4_bo, unwef_head);
		wist_dew(&bo->unwef_head);
		dwm_gem_object_put(&bo->base.base);
	}

	/* Fwee up the awwocation of any bin swots we used. */
	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	vc4->bin_awwoc_used &= ~exec->bin_swots;
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	/* Wewease the wefewence on the binnew BO if needed. */
	if (exec->bin_bo_used)
		vc4_v3d_bin_bo_put(vc4);

	/* Wewease the wefewence we had on the pewf monitow. */
	vc4_pewfmon_put(exec->pewfmon);

	vc4_v3d_pm_put(vc4);

	kfwee(exec);
}

void
vc4_job_handwe_compweted(stwuct vc4_dev *vc4)
{
	unsigned wong iwqfwags;
	stwuct vc4_seqno_cb *cb, *cb_temp;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	whiwe (!wist_empty(&vc4->job_done_wist)) {
		stwuct vc4_exec_info *exec =
			wist_fiwst_entwy(&vc4->job_done_wist,
					 stwuct vc4_exec_info, head);
		wist_dew(&exec->head);

		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		vc4_compwete_exec(&vc4->base, exec);
		spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	}

	wist_fow_each_entwy_safe(cb, cb_temp, &vc4->seqno_cb_wist, wowk.entwy) {
		if (cb->seqno <= vc4->finished_seqno) {
			wist_dew_init(&cb->wowk.entwy);
			scheduwe_wowk(&cb->wowk);
		}
	}

	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
}

static void vc4_seqno_cb_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_seqno_cb *cb = containew_of(wowk, stwuct vc4_seqno_cb, wowk);

	cb->func(cb);
}

int vc4_queue_seqno_cb(stwuct dwm_device *dev,
		       stwuct vc4_seqno_cb *cb, uint64_t seqno,
		       void (*func)(stwuct vc4_seqno_cb *cb))
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned wong iwqfwags;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	cb->func = func;
	INIT_WOWK(&cb->wowk, vc4_seqno_cb_wowk);

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	if (seqno > vc4->finished_seqno) {
		cb->seqno = seqno;
		wist_add_taiw(&cb->wowk.entwy, &vc4->seqno_cb_wist);
	} ewse {
		scheduwe_wowk(&cb->wowk);
	}
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	wetuwn 0;
}

/* Scheduwed when any job has been compweted, this wawks the wist of
 * jobs that had compweted and unwefs theiw BOs and fwees theiw exec
 * stwucts.
 */
static void
vc4_job_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_dev *vc4 =
		containew_of(wowk, stwuct vc4_dev, job_done_wowk);

	vc4_job_handwe_compweted(vc4);
}

static int
vc4_wait_fow_seqno_ioctw_hewpew(stwuct dwm_device *dev,
				uint64_t seqno,
				uint64_t *timeout_ns)
{
	unsigned wong stawt = jiffies;
	int wet = vc4_wait_fow_seqno(dev, seqno, *timeout_ns, twue);

	if ((wet == -EINTW || wet == -EWESTAWTSYS) && *timeout_ns != ~0uww) {
		uint64_t dewta = jiffies_to_nsecs(jiffies - stawt);

		if (*timeout_ns >= dewta)
			*timeout_ns -= dewta;
	}

	wetuwn wet;
}

int
vc4_wait_seqno_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_wait_seqno *awgs = data;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	wetuwn vc4_wait_fow_seqno_ioctw_hewpew(dev, awgs->seqno,
					       &awgs->timeout_ns);
}

int
vc4_wait_bo_ioctw(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet;
	stwuct dwm_vc4_wait_bo *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	stwuct vc4_bo *bo;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -EINVAW;
	}
	bo = to_vc4_bo(gem_obj);

	wet = vc4_wait_fow_seqno_ioctw_hewpew(dev, bo->seqno,
					      &awgs->timeout_ns);

	dwm_gem_object_put(gem_obj);
	wetuwn wet;
}

/**
 * vc4_submit_cw_ioctw() - Submits a job (fwame) to the VC4.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * This is the main entwypoint fow usewspace to submit a 3D fwame to
 * the GPU.  Usewspace pwovides the binnew command wist (if
 * appwicabwe), and the kewnew sets up the wendew command wist to dwaw
 * to the fwamebuffew descwibed in the ioctw, using the command wists
 * that the 3D engine's binnew wiww pwoduce.
 */
int
vc4_submit_cw_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_vc4_submit_cw *awgs = data;
	stwuct dwm_syncobj *out_sync = NUWW;
	stwuct vc4_exec_info *exec;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	stwuct dma_fence *in_fence;
	int wet = 0;

	twace_vc4_submit_cw_ioctw(dev, awgs->bin_cw_size,
				  awgs->shadew_wec_size,
				  awgs->bo_handwe_count);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d) {
		DWM_DEBUG("VC4_SUBMIT_CW with no VC4 V3D pwobed\n");
		wetuwn -ENODEV;
	}

	if ((awgs->fwags & ~(VC4_SUBMIT_CW_USE_CWEAW_COWOW |
			     VC4_SUBMIT_CW_FIXED_WCW_OWDEW |
			     VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_X |
			     VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_Y)) != 0) {
		DWM_DEBUG("Unknown fwags: 0x%02x\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	if (awgs->pad2 != 0) {
		DWM_DEBUG("Invawid pad: 0x%08x\n", awgs->pad2);
		wetuwn -EINVAW;
	}

	exec = kcawwoc(1, sizeof(*exec), GFP_KEWNEW);
	if (!exec) {
		DWM_EWWOW("mawwoc faiwuwe on exec stwuct\n");
		wetuwn -ENOMEM;
	}
	exec->dev = vc4;

	wet = vc4_v3d_pm_get(vc4);
	if (wet) {
		kfwee(exec);
		wetuwn wet;
	}

	exec->awgs = awgs;
	INIT_WIST_HEAD(&exec->unwef_wist);

	wet = vc4_cw_wookup_bos(dev, fiwe_pwiv, exec);
	if (wet)
		goto faiw;

	if (awgs->pewfmonid) {
		exec->pewfmon = vc4_pewfmon_find(vc4fiwe,
						 awgs->pewfmonid);
		if (!exec->pewfmon) {
			wet = -ENOENT;
			goto faiw;
		}
	}

	if (awgs->in_sync) {
		wet = dwm_syncobj_find_fence(fiwe_pwiv, awgs->in_sync,
					     0, 0, &in_fence);
		if (wet)
			goto faiw;

		/* When the fence (ow fence awway) is excwusivewy fwom ouw
		 * context we can skip the wait since jobs awe executed in
		 * owdew of theiw submission thwough this ioctw and this can
		 * onwy have fences fwom a pwiow job.
		 */
		if (!dma_fence_match_context(in_fence,
					     vc4->dma_fence_context)) {
			wet = dma_fence_wait(in_fence, twue);
			if (wet) {
				dma_fence_put(in_fence);
				goto faiw;
			}
		}

		dma_fence_put(in_fence);
	}

	if (exec->awgs->bin_cw_size != 0) {
		wet = vc4_get_bcw(dev, exec);
		if (wet)
			goto faiw;
	} ewse {
		exec->ct0ca = 0;
		exec->ct0ea = 0;
	}

	wet = vc4_get_wcw(dev, exec);
	if (wet)
		goto faiw;

	wet = vc4_wock_bo_wesewvations(dev, exec, &acquiwe_ctx);
	if (wet)
		goto faiw;

	if (awgs->out_sync) {
		out_sync = dwm_syncobj_find(fiwe_pwiv, awgs->out_sync);
		if (!out_sync) {
			wet = -EINVAW;
			goto faiw;
		}

		/* We wepwace the fence in out_sync in vc4_queue_submit since
		 * the wendew job couwd execute immediatewy aftew that caww.
		 * If it finishes befowe ouw ioctw pwocessing wesumes the
		 * wendew job fence couwd awweady have been fweed.
		 */
	}

	/* Cweaw this out of the stwuct we'ww be putting in the queue,
	 * since it's pawt of ouw stack.
	 */
	exec->awgs = NUWW;

	wet = vc4_queue_submit(dev, exec, &acquiwe_ctx, out_sync);

	/* The syncobj isn't pawt of the exec data and we need to fwee ouw
	 * wefewence even if job submission faiwed.
	 */
	if (out_sync)
		dwm_syncobj_put(out_sync);

	if (wet)
		goto faiw;

	/* Wetuwn the seqno fow ouw job. */
	awgs->seqno = vc4->emit_seqno;

	wetuwn 0;

faiw:
	vc4_compwete_exec(&vc4->base, exec);

	wetuwn wet;
}

static void vc4_gem_destwoy(stwuct dwm_device *dev, void *unused);
int vc4_gem_init(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	vc4->dma_fence_context = dma_fence_context_awwoc(1);

	INIT_WIST_HEAD(&vc4->bin_job_wist);
	INIT_WIST_HEAD(&vc4->wendew_job_wist);
	INIT_WIST_HEAD(&vc4->job_done_wist);
	INIT_WIST_HEAD(&vc4->seqno_cb_wist);
	spin_wock_init(&vc4->job_wock);

	INIT_WOWK(&vc4->hangcheck.weset_wowk, vc4_weset_wowk);
	timew_setup(&vc4->hangcheck.timew, vc4_hangcheck_ewapsed, 0);

	INIT_WOWK(&vc4->job_done_wowk, vc4_job_done_wowk);

	wet = dwmm_mutex_init(dev, &vc4->powew_wock);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&vc4->puwgeabwe.wist);

	wet = dwmm_mutex_init(dev, &vc4->puwgeabwe.wock);
	if (wet)
		wetuwn wet;

	wetuwn dwmm_add_action_ow_weset(dev, vc4_gem_destwoy, NUWW);
}

static void vc4_gem_destwoy(stwuct dwm_device *dev, void *unused)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Waiting fow exec to finish wouwd need to be done befowe
	 * unwegistewing V3D.
	 */
	WAWN_ON(vc4->emit_seqno != vc4->finished_seqno);

	/* V3D shouwd awweady have disabwed its intewwupt and cweawed
	 * the ovewfwow awwocation wegistews.  Now fwee the object.
	 */
	if (vc4->bin_bo) {
		dwm_gem_object_put(&vc4->bin_bo->base.base);
		vc4->bin_bo = NUWW;
	}

	if (vc4->hang_state)
		vc4_fwee_hang_state(dev, vc4->hang_state);
}

int vc4_gem_madvise_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_gem_madvise *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	stwuct vc4_bo *bo;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	switch (awgs->madv) {
	case VC4_MADV_DONTNEED:
	case VC4_MADV_WIWWNEED:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}

	bo = to_vc4_bo(gem_obj);

	/* Onwy BOs exposed to usewspace can be puwged. */
	if (bo->madv == __VC4_MADV_NOTSUPP) {
		DWM_DEBUG("madvise not suppowted on this BO\n");
		wet = -EINVAW;
		goto out_put_gem;
	}

	/* Not suwe it's safe to puwge impowted BOs. Wet's just assume it's
	 * not untiw pwoven othewwise.
	 */
	if (gem_obj->impowt_attach) {
		DWM_DEBUG("madvise not suppowted on impowted BOs\n");
		wet = -EINVAW;
		goto out_put_gem;
	}

	mutex_wock(&bo->madv_wock);

	if (awgs->madv == VC4_MADV_DONTNEED && bo->madv == VC4_MADV_WIWWNEED &&
	    !wefcount_wead(&bo->usecnt)) {
		/* If the BO is about to be mawked as puwgeabwe, is not used
		 * and is not awweady puwgeabwe ow puwged, add it to the
		 * puwgeabwe wist.
		 */
		vc4_bo_add_to_puwgeabwe_poow(bo);
	} ewse if (awgs->madv == VC4_MADV_WIWWNEED &&
		   bo->madv == VC4_MADV_DONTNEED &&
		   !wefcount_wead(&bo->usecnt)) {
		/* The BO has not been puwged yet, just wemove it fwom
		 * the puwgeabwe wist.
		 */
		vc4_bo_wemove_fwom_puwgeabwe_poow(bo);
	}

	/* Save the puwged state. */
	awgs->wetained = bo->madv != __VC4_MADV_PUWGED;

	/* Update intewnaw madv state onwy if the bo was not puwged. */
	if (bo->madv != __VC4_MADV_PUWGED)
		bo->madv = awgs->madv;

	mutex_unwock(&bo->madv_wock);

	wet = 0;

out_put_gem:
	dwm_gem_object_put(gem_obj);

	wetuwn wet;
}
