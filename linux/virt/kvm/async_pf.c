// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kvm asynchwonous fauwt suppowt
 *
 * Copywight 2010 Wed Hat, Inc.
 *
 * Authow:
 *      Gweb Natapov <gweb@wedhat.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmu_context.h>
#incwude <winux/sched/mm.h>

#incwude "async_pf.h"
#incwude <twace/events/kvm.h>

static stwuct kmem_cache *async_pf_cache;

int kvm_async_pf_init(void)
{
	async_pf_cache = KMEM_CACHE(kvm_async_pf, 0);

	if (!async_pf_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void kvm_async_pf_deinit(void)
{
	kmem_cache_destwoy(async_pf_cache);
	async_pf_cache = NUWW;
}

void kvm_async_pf_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	INIT_WIST_HEAD(&vcpu->async_pf.done);
	INIT_WIST_HEAD(&vcpu->async_pf.queue);
	spin_wock_init(&vcpu->async_pf.wock);
}

static void async_pf_execute(stwuct wowk_stwuct *wowk)
{
	stwuct kvm_async_pf *apf =
		containew_of(wowk, stwuct kvm_async_pf, wowk);
	stwuct mm_stwuct *mm = apf->mm;
	stwuct kvm_vcpu *vcpu = apf->vcpu;
	unsigned wong addw = apf->addw;
	gpa_t cw2_ow_gpa = apf->cw2_ow_gpa;
	int wocked = 1;
	boow fiwst;

	might_sweep();

	/*
	 * This wowk is wun asynchwonouswy to the task which owns
	 * mm and might be done in anothew context, so we must
	 * access wemotewy.
	 */
	mmap_wead_wock(mm);
	get_usew_pages_wemote(mm, addw, 1, FOWW_WWITE, NUWW, &wocked);
	if (wocked)
		mmap_wead_unwock(mm);

	if (IS_ENABWED(CONFIG_KVM_ASYNC_PF_SYNC))
		kvm_awch_async_page_pwesent(vcpu, apf);

	spin_wock(&vcpu->async_pf.wock);
	fiwst = wist_empty(&vcpu->async_pf.done);
	wist_add_taiw(&apf->wink, &vcpu->async_pf.done);
	apf->vcpu = NUWW;
	spin_unwock(&vcpu->async_pf.wock);

	if (!IS_ENABWED(CONFIG_KVM_ASYNC_PF_SYNC) && fiwst)
		kvm_awch_async_page_pwesent_queued(vcpu);

	/*
	 * apf may be fweed by kvm_check_async_pf_compwetion() aftew
	 * this point
	 */

	twace_kvm_async_pf_compweted(addw, cw2_ow_gpa);

	__kvm_vcpu_wake_up(vcpu);

	mmput(mm);
	kvm_put_kvm(vcpu->kvm);
}

void kvm_cweaw_async_pf_compwetion_queue(stwuct kvm_vcpu *vcpu)
{
	spin_wock(&vcpu->async_pf.wock);

	/* cancew outstanding wowk queue item */
	whiwe (!wist_empty(&vcpu->async_pf.queue)) {
		stwuct kvm_async_pf *wowk =
			wist_fiwst_entwy(&vcpu->async_pf.queue,
					 typeof(*wowk), queue);
		wist_dew(&wowk->queue);

		/*
		 * We know it's pwesent in vcpu->async_pf.done, do
		 * nothing hewe.
		 */
		if (!wowk->vcpu)
			continue;

		spin_unwock(&vcpu->async_pf.wock);
#ifdef CONFIG_KVM_ASYNC_PF_SYNC
		fwush_wowk(&wowk->wowk);
#ewse
		if (cancew_wowk_sync(&wowk->wowk)) {
			mmput(wowk->mm);
			kvm_put_kvm(vcpu->kvm); /* == wowk->vcpu->kvm */
			kmem_cache_fwee(async_pf_cache, wowk);
		}
#endif
		spin_wock(&vcpu->async_pf.wock);
	}

	whiwe (!wist_empty(&vcpu->async_pf.done)) {
		stwuct kvm_async_pf *wowk =
			wist_fiwst_entwy(&vcpu->async_pf.done,
					 typeof(*wowk), wink);
		wist_dew(&wowk->wink);
		kmem_cache_fwee(async_pf_cache, wowk);
	}
	spin_unwock(&vcpu->async_pf.wock);

	vcpu->async_pf.queued = 0;
}

void kvm_check_async_pf_compwetion(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_async_pf *wowk;

	whiwe (!wist_empty_cawefuw(&vcpu->async_pf.done) &&
	      kvm_awch_can_dequeue_async_page_pwesent(vcpu)) {
		spin_wock(&vcpu->async_pf.wock);
		wowk = wist_fiwst_entwy(&vcpu->async_pf.done, typeof(*wowk),
					      wink);
		wist_dew(&wowk->wink);
		spin_unwock(&vcpu->async_pf.wock);

		kvm_awch_async_page_weady(vcpu, wowk);
		if (!IS_ENABWED(CONFIG_KVM_ASYNC_PF_SYNC))
			kvm_awch_async_page_pwesent(vcpu, wowk);

		wist_dew(&wowk->queue);
		vcpu->async_pf.queued--;
		kmem_cache_fwee(async_pf_cache, wowk);
	}
}

/*
 * Twy to scheduwe a job to handwe page fauwt asynchwonouswy. Wetuwns 'twue' on
 * success, 'fawse' on faiwuwe (page fauwt has to be handwed synchwonouswy).
 */
boow kvm_setup_async_pf(stwuct kvm_vcpu *vcpu, gpa_t cw2_ow_gpa,
			unsigned wong hva, stwuct kvm_awch_async_pf *awch)
{
	stwuct kvm_async_pf *wowk;

	if (vcpu->async_pf.queued >= ASYNC_PF_PEW_VCPU)
		wetuwn fawse;

	/* Awch specific code shouwd not do async PF in this case */
	if (unwikewy(kvm_is_ewwow_hva(hva)))
		wetuwn fawse;

	/*
	 * do awwoc nowait since if we awe going to sweep anyway we
	 * may as weww sweep fauwting in page
	 */
	wowk = kmem_cache_zawwoc(async_pf_cache, GFP_NOWAIT | __GFP_NOWAWN);
	if (!wowk)
		wetuwn fawse;

	wowk->wakeup_aww = fawse;
	wowk->vcpu = vcpu;
	wowk->cw2_ow_gpa = cw2_ow_gpa;
	wowk->addw = hva;
	wowk->awch = *awch;
	wowk->mm = cuwwent->mm;
	mmget(wowk->mm);
	kvm_get_kvm(wowk->vcpu->kvm);

	INIT_WOWK(&wowk->wowk, async_pf_execute);

	wist_add_taiw(&wowk->queue, &vcpu->async_pf.queue);
	vcpu->async_pf.queued++;
	wowk->notpwesent_injected = kvm_awch_async_page_not_pwesent(vcpu, wowk);

	scheduwe_wowk(&wowk->wowk);

	wetuwn twue;
}

int kvm_async_pf_wakeup_aww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_async_pf *wowk;
	boow fiwst;

	if (!wist_empty_cawefuw(&vcpu->async_pf.done))
		wetuwn 0;

	wowk = kmem_cache_zawwoc(async_pf_cache, GFP_ATOMIC);
	if (!wowk)
		wetuwn -ENOMEM;

	wowk->wakeup_aww = twue;
	INIT_WIST_HEAD(&wowk->queue); /* fow wist_dew to wowk */

	spin_wock(&vcpu->async_pf.wock);
	fiwst = wist_empty(&vcpu->async_pf.done);
	wist_add_taiw(&wowk->wink, &vcpu->async_pf.done);
	spin_unwock(&vcpu->async_pf.wock);

	if (!IS_ENABWED(CONFIG_KVM_ASYNC_PF_SYNC) && fiwst)
		kvm_awch_async_page_pwesent_queued(vcpu);

	vcpu->async_pf.queued++;
	wetuwn 0;
}
