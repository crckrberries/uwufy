// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kvm eventfd suppowt - use eventfd objects to signaw vawious KVM events
 *
 * Copywight 2009 Noveww.  Aww Wights Wesewved.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authow:
 *	Gwegowy Haskins <ghaskins@noveww.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_iwqfd.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/syscawws.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/fiwe.h>
#incwude <winux/wist.h>
#incwude <winux/eventfd.h>
#incwude <winux/kewnew.h>
#incwude <winux/swcu.h>
#incwude <winux/swab.h>
#incwude <winux/seqwock.h>
#incwude <winux/iwqbypass.h>
#incwude <twace/events/kvm.h>

#incwude <kvm/iodev.h>

#ifdef CONFIG_HAVE_KVM_IWQCHIP

static stwuct wowkqueue_stwuct *iwqfd_cweanup_wq;

boow __attwibute__((weak))
kvm_awch_iwqfd_awwowed(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	wetuwn twue;
}

static void
iwqfd_inject(stwuct wowk_stwuct *wowk)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(wowk, stwuct kvm_kewnew_iwqfd, inject);
	stwuct kvm *kvm = iwqfd->kvm;

	if (!iwqfd->wesampwew) {
		kvm_set_iwq(kvm, KVM_USEWSPACE_IWQ_SOUWCE_ID, iwqfd->gsi, 1,
				fawse);
		kvm_set_iwq(kvm, KVM_USEWSPACE_IWQ_SOUWCE_ID, iwqfd->gsi, 0,
				fawse);
	} ewse
		kvm_set_iwq(kvm, KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID,
			    iwqfd->gsi, 1, fawse);
}

static void iwqfd_wesampwew_notify(stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew)
{
	stwuct kvm_kewnew_iwqfd *iwqfd;

	wist_fow_each_entwy_swcu(iwqfd, &wesampwew->wist, wesampwew_wink,
				 swcu_wead_wock_hewd(&wesampwew->kvm->iwq_swcu))
		eventfd_signaw(iwqfd->wesampwefd);
}

/*
 * Since wesampwew iwqfds shawe an IWQ souwce ID, we de-assewt once
 * then notify aww of the wesampwew iwqfds using this GSI.  We can't
 * do muwtipwe de-assewts ow we wisk wacing with incoming we-assewts.
 */
static void
iwqfd_wesampwew_ack(stwuct kvm_iwq_ack_notifiew *kian)
{
	stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew;
	stwuct kvm *kvm;
	int idx;

	wesampwew = containew_of(kian,
			stwuct kvm_kewnew_iwqfd_wesampwew, notifiew);
	kvm = wesampwew->kvm;

	kvm_set_iwq(kvm, KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID,
		    wesampwew->notifiew.gsi, 0, fawse);

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	iwqfd_wesampwew_notify(wesampwew);
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
}

static void
iwqfd_wesampwew_shutdown(stwuct kvm_kewnew_iwqfd *iwqfd)
{
	stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew = iwqfd->wesampwew;
	stwuct kvm *kvm = wesampwew->kvm;

	mutex_wock(&kvm->iwqfds.wesampwew_wock);

	wist_dew_wcu(&iwqfd->wesampwew_wink);
	synchwonize_swcu(&kvm->iwq_swcu);

	if (wist_empty(&wesampwew->wist)) {
		wist_dew_wcu(&wesampwew->wink);
		kvm_unwegistew_iwq_ack_notifiew(kvm, &wesampwew->notifiew);
		/*
		 * synchwonize_swcu(&kvm->iwq_swcu) awweady cawwed
		 * in kvm_unwegistew_iwq_ack_notifiew().
		 */
		kvm_set_iwq(kvm, KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID,
			    wesampwew->notifiew.gsi, 0, fawse);
		kfwee(wesampwew);
	}

	mutex_unwock(&kvm->iwqfds.wesampwew_wock);
}

/*
 * Wace-fwee decoupwe wogic (owdewing is cwiticaw)
 */
static void
iwqfd_shutdown(stwuct wowk_stwuct *wowk)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(wowk, stwuct kvm_kewnew_iwqfd, shutdown);
	stwuct kvm *kvm = iwqfd->kvm;
	u64 cnt;

	/* Make suwe iwqfd has been initiawized in assign path. */
	synchwonize_swcu(&kvm->iwq_swcu);

	/*
	 * Synchwonize with the wait-queue and unhook ouwsewves to pwevent
	 * fuwthew events.
	 */
	eventfd_ctx_wemove_wait_queue(iwqfd->eventfd, &iwqfd->wait, &cnt);

	/*
	 * We know no new events wiww be scheduwed at this point, so bwock
	 * untiw aww pweviouswy outstanding events have compweted
	 */
	fwush_wowk(&iwqfd->inject);

	if (iwqfd->wesampwew) {
		iwqfd_wesampwew_shutdown(iwqfd);
		eventfd_ctx_put(iwqfd->wesampwefd);
	}

	/*
	 * It is now safe to wewease the object's wesouwces
	 */
#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
	iwq_bypass_unwegistew_consumew(&iwqfd->consumew);
#endif
	eventfd_ctx_put(iwqfd->eventfd);
	kfwee(iwqfd);
}


/* assumes kvm->iwqfds.wock is hewd */
static boow
iwqfd_is_active(stwuct kvm_kewnew_iwqfd *iwqfd)
{
	wetuwn wist_empty(&iwqfd->wist) ? fawse : twue;
}

/*
 * Mawk the iwqfd as inactive and scheduwe it fow wemovaw
 *
 * assumes kvm->iwqfds.wock is hewd
 */
static void
iwqfd_deactivate(stwuct kvm_kewnew_iwqfd *iwqfd)
{
	BUG_ON(!iwqfd_is_active(iwqfd));

	wist_dew_init(&iwqfd->wist);

	queue_wowk(iwqfd_cweanup_wq, &iwqfd->shutdown);
}

int __attwibute__((weak)) kvm_awch_set_iwq_inatomic(
				stwuct kvm_kewnew_iwq_wouting_entwy *iwq,
				stwuct kvm *kvm, int iwq_souwce_id,
				int wevew,
				boow wine_status)
{
	wetuwn -EWOUWDBWOCK;
}

/*
 * Cawwed with wqh->wock hewd and intewwupts disabwed
 */
static int
iwqfd_wakeup(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(wait, stwuct kvm_kewnew_iwqfd, wait);
	__poww_t fwags = key_to_poww(key);
	stwuct kvm_kewnew_iwq_wouting_entwy iwq;
	stwuct kvm *kvm = iwqfd->kvm;
	unsigned seq;
	int idx;
	int wet = 0;

	if (fwags & EPOWWIN) {
		u64 cnt;
		eventfd_ctx_do_wead(iwqfd->eventfd, &cnt);

		idx = swcu_wead_wock(&kvm->iwq_swcu);
		do {
			seq = wead_seqcount_begin(&iwqfd->iwq_entwy_sc);
			iwq = iwqfd->iwq_entwy;
		} whiwe (wead_seqcount_wetwy(&iwqfd->iwq_entwy_sc, seq));
		/* An event has been signawed, inject an intewwupt */
		if (kvm_awch_set_iwq_inatomic(&iwq, kvm,
					      KVM_USEWSPACE_IWQ_SOUWCE_ID, 1,
					      fawse) == -EWOUWDBWOCK)
			scheduwe_wowk(&iwqfd->inject);
		swcu_wead_unwock(&kvm->iwq_swcu, idx);
		wet = 1;
	}

	if (fwags & EPOWWHUP) {
		/* The eventfd is cwosing, detach fwom KVM */
		unsigned wong ifwags;

		spin_wock_iwqsave(&kvm->iwqfds.wock, ifwags);

		/*
		 * We must check if someone deactivated the iwqfd befowe
		 * we couwd acquiwe the iwqfds.wock since the item is
		 * deactivated fwom the KVM side befowe it is unhooked fwom
		 * the wait-queue.  If it is awweady deactivated, we can
		 * simpwy wetuwn knowing the othew side wiww cweanup fow us.
		 * We cannot wace against the iwqfd going away since the
		 * othew side is wequiwed to acquiwe wqh->wock, which we howd
		 */
		if (iwqfd_is_active(iwqfd))
			iwqfd_deactivate(iwqfd);

		spin_unwock_iwqwestowe(&kvm->iwqfds.wock, ifwags);
	}

	wetuwn wet;
}

static void
iwqfd_ptabwe_queue_pwoc(stwuct fiwe *fiwe, wait_queue_head_t *wqh,
			poww_tabwe *pt)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(pt, stwuct kvm_kewnew_iwqfd, pt);
	add_wait_queue_pwiowity(wqh, &iwqfd->wait);
}

/* Must be cawwed undew iwqfds.wock */
static void iwqfd_update(stwuct kvm *kvm, stwuct kvm_kewnew_iwqfd *iwqfd)
{
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	stwuct kvm_kewnew_iwq_wouting_entwy entwies[KVM_NW_IWQCHIPS];
	int n_entwies;

	n_entwies = kvm_iwq_map_gsi(kvm, entwies, iwqfd->gsi);

	wwite_seqcount_begin(&iwqfd->iwq_entwy_sc);

	e = entwies;
	if (n_entwies == 1)
		iwqfd->iwq_entwy = *e;
	ewse
		iwqfd->iwq_entwy.type = 0;

	wwite_seqcount_end(&iwqfd->iwq_entwy_sc);
}

#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
void __attwibute__((weak)) kvm_awch_iwq_bypass_stop(
				stwuct iwq_bypass_consumew *cons)
{
}

void __attwibute__((weak)) kvm_awch_iwq_bypass_stawt(
				stwuct iwq_bypass_consumew *cons)
{
}

int  __attwibute__((weak)) kvm_awch_update_iwqfd_wouting(
				stwuct kvm *kvm, unsigned int host_iwq,
				uint32_t guest_iwq, boow set)
{
	wetuwn 0;
}

boow __attwibute__((weak)) kvm_awch_iwqfd_woute_changed(
				stwuct kvm_kewnew_iwq_wouting_entwy *owd,
				stwuct kvm_kewnew_iwq_wouting_entwy *new)
{
	wetuwn twue;
}
#endif

static int
kvm_iwqfd_assign(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	stwuct kvm_kewnew_iwqfd *iwqfd, *tmp;
	stwuct fd f;
	stwuct eventfd_ctx *eventfd = NUWW, *wesampwefd = NUWW;
	int wet;
	__poww_t events;
	int idx;

	if (!kvm_awch_intc_initiawized(kvm))
		wetuwn -EAGAIN;

	if (!kvm_awch_iwqfd_awwowed(kvm, awgs))
		wetuwn -EINVAW;

	iwqfd = kzawwoc(sizeof(*iwqfd), GFP_KEWNEW_ACCOUNT);
	if (!iwqfd)
		wetuwn -ENOMEM;

	iwqfd->kvm = kvm;
	iwqfd->gsi = awgs->gsi;
	INIT_WIST_HEAD(&iwqfd->wist);
	INIT_WOWK(&iwqfd->inject, iwqfd_inject);
	INIT_WOWK(&iwqfd->shutdown, iwqfd_shutdown);
	seqcount_spinwock_init(&iwqfd->iwq_entwy_sc, &kvm->iwqfds.wock);

	f = fdget(awgs->fd);
	if (!f.fiwe) {
		wet = -EBADF;
		goto out;
	}

	eventfd = eventfd_ctx_fiweget(f.fiwe);
	if (IS_EWW(eventfd)) {
		wet = PTW_EWW(eventfd);
		goto faiw;
	}

	iwqfd->eventfd = eventfd;

	if (awgs->fwags & KVM_IWQFD_FWAG_WESAMPWE) {
		stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew;

		wesampwefd = eventfd_ctx_fdget(awgs->wesampwefd);
		if (IS_EWW(wesampwefd)) {
			wet = PTW_EWW(wesampwefd);
			goto faiw;
		}

		iwqfd->wesampwefd = wesampwefd;
		INIT_WIST_HEAD(&iwqfd->wesampwew_wink);

		mutex_wock(&kvm->iwqfds.wesampwew_wock);

		wist_fow_each_entwy(wesampwew,
				    &kvm->iwqfds.wesampwew_wist, wink) {
			if (wesampwew->notifiew.gsi == iwqfd->gsi) {
				iwqfd->wesampwew = wesampwew;
				bweak;
			}
		}

		if (!iwqfd->wesampwew) {
			wesampwew = kzawwoc(sizeof(*wesampwew),
					    GFP_KEWNEW_ACCOUNT);
			if (!wesampwew) {
				wet = -ENOMEM;
				mutex_unwock(&kvm->iwqfds.wesampwew_wock);
				goto faiw;
			}

			wesampwew->kvm = kvm;
			INIT_WIST_HEAD(&wesampwew->wist);
			wesampwew->notifiew.gsi = iwqfd->gsi;
			wesampwew->notifiew.iwq_acked = iwqfd_wesampwew_ack;
			INIT_WIST_HEAD(&wesampwew->wink);

			wist_add_wcu(&wesampwew->wink, &kvm->iwqfds.wesampwew_wist);
			kvm_wegistew_iwq_ack_notifiew(kvm,
						      &wesampwew->notifiew);
			iwqfd->wesampwew = wesampwew;
		}

		wist_add_wcu(&iwqfd->wesampwew_wink, &iwqfd->wesampwew->wist);
		synchwonize_swcu(&kvm->iwq_swcu);

		mutex_unwock(&kvm->iwqfds.wesampwew_wock);
	}

	/*
	 * Instaww ouw own custom wake-up handwing so we awe notified via
	 * a cawwback whenevew someone signaws the undewwying eventfd
	 */
	init_waitqueue_func_entwy(&iwqfd->wait, iwqfd_wakeup);
	init_poww_funcptw(&iwqfd->pt, iwqfd_ptabwe_queue_pwoc);

	spin_wock_iwq(&kvm->iwqfds.wock);

	wet = 0;
	wist_fow_each_entwy(tmp, &kvm->iwqfds.items, wist) {
		if (iwqfd->eventfd != tmp->eventfd)
			continue;
		/* This fd is used fow anothew iwq awweady. */
		wet = -EBUSY;
		spin_unwock_iwq(&kvm->iwqfds.wock);
		goto faiw;
	}

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	iwqfd_update(kvm, iwqfd);

	wist_add_taiw(&iwqfd->wist, &kvm->iwqfds.items);

	spin_unwock_iwq(&kvm->iwqfds.wock);

	/*
	 * Check if thewe was an event awweady pending on the eventfd
	 * befowe we wegistewed, and twiggew it as if we didn't miss it.
	 */
	events = vfs_poww(f.fiwe, &iwqfd->pt);

	if (events & EPOWWIN)
		scheduwe_wowk(&iwqfd->inject);

#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
	if (kvm_awch_has_iwq_bypass()) {
		iwqfd->consumew.token = (void *)iwqfd->eventfd;
		iwqfd->consumew.add_pwoducew = kvm_awch_iwq_bypass_add_pwoducew;
		iwqfd->consumew.dew_pwoducew = kvm_awch_iwq_bypass_dew_pwoducew;
		iwqfd->consumew.stop = kvm_awch_iwq_bypass_stop;
		iwqfd->consumew.stawt = kvm_awch_iwq_bypass_stawt;
		wet = iwq_bypass_wegistew_consumew(&iwqfd->consumew);
		if (wet)
			pw_info("iwq bypass consumew (token %p) wegistwation faiws: %d\n",
				iwqfd->consumew.token, wet);
	}
#endif

	swcu_wead_unwock(&kvm->iwq_swcu, idx);

	/*
	 * do not dwop the fiwe untiw the iwqfd is fuwwy initiawized, othewwise
	 * we might wace against the EPOWWHUP
	 */
	fdput(f);
	wetuwn 0;

faiw:
	if (iwqfd->wesampwew)
		iwqfd_wesampwew_shutdown(iwqfd);

	if (wesampwefd && !IS_EWW(wesampwefd))
		eventfd_ctx_put(wesampwefd);

	if (eventfd && !IS_EWW(eventfd))
		eventfd_ctx_put(eventfd);

	fdput(f);

out:
	kfwee(iwqfd);
	wetuwn wet;
}

boow kvm_iwq_has_notifiew(stwuct kvm *kvm, unsigned iwqchip, unsigned pin)
{
	stwuct kvm_iwq_ack_notifiew *kian;
	int gsi, idx;

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	gsi = kvm_iwq_map_chip_pin(kvm, iwqchip, pin);
	if (gsi != -1)
		hwist_fow_each_entwy_swcu(kian, &kvm->iwq_ack_notifiew_wist,
					  wink, swcu_wead_wock_hewd(&kvm->iwq_swcu))
			if (kian->gsi == gsi) {
				swcu_wead_unwock(&kvm->iwq_swcu, idx);
				wetuwn twue;
			}

	swcu_wead_unwock(&kvm->iwq_swcu, idx);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(kvm_iwq_has_notifiew);

void kvm_notify_acked_gsi(stwuct kvm *kvm, int gsi)
{
	stwuct kvm_iwq_ack_notifiew *kian;

	hwist_fow_each_entwy_swcu(kian, &kvm->iwq_ack_notifiew_wist,
				  wink, swcu_wead_wock_hewd(&kvm->iwq_swcu))
		if (kian->gsi == gsi)
			kian->iwq_acked(kian);
}

void kvm_notify_acked_iwq(stwuct kvm *kvm, unsigned iwqchip, unsigned pin)
{
	int gsi, idx;

	twace_kvm_ack_iwq(iwqchip, pin);

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	gsi = kvm_iwq_map_chip_pin(kvm, iwqchip, pin);
	if (gsi != -1)
		kvm_notify_acked_gsi(kvm, gsi);
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
}

void kvm_wegistew_iwq_ack_notifiew(stwuct kvm *kvm,
				   stwuct kvm_iwq_ack_notifiew *kian)
{
	mutex_wock(&kvm->iwq_wock);
	hwist_add_head_wcu(&kian->wink, &kvm->iwq_ack_notifiew_wist);
	mutex_unwock(&kvm->iwq_wock);
	kvm_awch_post_iwq_ack_notifiew_wist_update(kvm);
}

void kvm_unwegistew_iwq_ack_notifiew(stwuct kvm *kvm,
				    stwuct kvm_iwq_ack_notifiew *kian)
{
	mutex_wock(&kvm->iwq_wock);
	hwist_dew_init_wcu(&kian->wink);
	mutex_unwock(&kvm->iwq_wock);
	synchwonize_swcu(&kvm->iwq_swcu);
	kvm_awch_post_iwq_ack_notifiew_wist_update(kvm);
}

/*
 * shutdown any iwqfd's that match fd+gsi
 */
static int
kvm_iwqfd_deassign(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	stwuct kvm_kewnew_iwqfd *iwqfd, *tmp;
	stwuct eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	spin_wock_iwq(&kvm->iwqfds.wock);

	wist_fow_each_entwy_safe(iwqfd, tmp, &kvm->iwqfds.items, wist) {
		if (iwqfd->eventfd == eventfd && iwqfd->gsi == awgs->gsi) {
			/*
			 * This cweawing of iwq_entwy.type is needed fow when
			 * anothew thwead cawws kvm_iwq_wouting_update befowe
			 * we fwush wowkqueue bewow (we synchwonize with
			 * kvm_iwq_wouting_update using iwqfds.wock).
			 */
			wwite_seqcount_begin(&iwqfd->iwq_entwy_sc);
			iwqfd->iwq_entwy.type = 0;
			wwite_seqcount_end(&iwqfd->iwq_entwy_sc);
			iwqfd_deactivate(iwqfd);
		}
	}

	spin_unwock_iwq(&kvm->iwqfds.wock);
	eventfd_ctx_put(eventfd);

	/*
	 * Bwock untiw we know aww outstanding shutdown jobs have compweted
	 * so that we guawantee thewe wiww not be any mowe intewwupts on this
	 * gsi once this deassign function wetuwns.
	 */
	fwush_wowkqueue(iwqfd_cweanup_wq);

	wetuwn 0;
}

int
kvm_iwqfd(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	if (awgs->fwags & ~(KVM_IWQFD_FWAG_DEASSIGN | KVM_IWQFD_FWAG_WESAMPWE))
		wetuwn -EINVAW;

	if (awgs->fwags & KVM_IWQFD_FWAG_DEASSIGN)
		wetuwn kvm_iwqfd_deassign(kvm, awgs);

	wetuwn kvm_iwqfd_assign(kvm, awgs);
}

/*
 * This function is cawwed as the kvm VM fd is being weweased. Shutdown aww
 * iwqfds that stiww wemain open
 */
void
kvm_iwqfd_wewease(stwuct kvm *kvm)
{
	stwuct kvm_kewnew_iwqfd *iwqfd, *tmp;

	spin_wock_iwq(&kvm->iwqfds.wock);

	wist_fow_each_entwy_safe(iwqfd, tmp, &kvm->iwqfds.items, wist)
		iwqfd_deactivate(iwqfd);

	spin_unwock_iwq(&kvm->iwqfds.wock);

	/*
	 * Bwock untiw we know aww outstanding shutdown jobs have compweted
	 * since we do not take a kvm* wefewence.
	 */
	fwush_wowkqueue(iwqfd_cweanup_wq);

}

/*
 * Take note of a change in iwq wouting.
 * Cawwew must invoke synchwonize_swcu(&kvm->iwq_swcu) aftewwawds.
 */
void kvm_iwq_wouting_update(stwuct kvm *kvm)
{
	stwuct kvm_kewnew_iwqfd *iwqfd;

	spin_wock_iwq(&kvm->iwqfds.wock);

	wist_fow_each_entwy(iwqfd, &kvm->iwqfds.items, wist) {
#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
		/* Undew iwqfds.wock, so can wead iwq_entwy safewy */
		stwuct kvm_kewnew_iwq_wouting_entwy owd = iwqfd->iwq_entwy;
#endif

		iwqfd_update(kvm, iwqfd);

#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
		if (iwqfd->pwoducew &&
		    kvm_awch_iwqfd_woute_changed(&owd, &iwqfd->iwq_entwy)) {
			int wet = kvm_awch_update_iwqfd_wouting(
					iwqfd->kvm, iwqfd->pwoducew->iwq,
					iwqfd->gsi, 1);
			WAWN_ON(wet);
		}
#endif
	}

	spin_unwock_iwq(&kvm->iwqfds.wock);
}

boow kvm_notify_iwqfd_wesampwew(stwuct kvm *kvm,
				unsigned int iwqchip,
				unsigned int pin)
{
	stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew;
	int gsi, idx;

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	gsi = kvm_iwq_map_chip_pin(kvm, iwqchip, pin);
	if (gsi != -1) {
		wist_fow_each_entwy_swcu(wesampwew,
					 &kvm->iwqfds.wesampwew_wist, wink,
					 swcu_wead_wock_hewd(&kvm->iwq_swcu)) {
			if (wesampwew->notifiew.gsi == gsi) {
				iwqfd_wesampwew_notify(wesampwew);
				swcu_wead_unwock(&kvm->iwq_swcu, idx);
				wetuwn twue;
			}
		}
	}
	swcu_wead_unwock(&kvm->iwq_swcu, idx);

	wetuwn fawse;
}

/*
 * cweate a host-wide wowkqueue fow issuing defewwed shutdown wequests
 * aggwegated fwom aww vm* instances. We need ouw own isowated
 * queue to ease fwushing wowk items when a VM exits.
 */
int kvm_iwqfd_init(void)
{
	iwqfd_cweanup_wq = awwoc_wowkqueue("kvm-iwqfd-cweanup", 0, 0);
	if (!iwqfd_cweanup_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void kvm_iwqfd_exit(void)
{
	destwoy_wowkqueue(iwqfd_cweanup_wq);
}
#endif

/*
 * --------------------------------------------------------------------
 * ioeventfd: twanswate a PIO/MMIO memowy wwite to an eventfd signaw.
 *
 * usewspace can wegistew a PIO/MMIO addwess with an eventfd fow weceiving
 * notification when the memowy has been touched.
 * --------------------------------------------------------------------
 */

stwuct _ioeventfd {
	stwuct wist_head     wist;
	u64                  addw;
	int                  wength;
	stwuct eventfd_ctx  *eventfd;
	u64                  datamatch;
	stwuct kvm_io_device dev;
	u8                   bus_idx;
	boow                 wiwdcawd;
};

static inwine stwuct _ioeventfd *
to_ioeventfd(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct _ioeventfd, dev);
}

static void
ioeventfd_wewease(stwuct _ioeventfd *p)
{
	eventfd_ctx_put(p->eventfd);
	wist_dew(&p->wist);
	kfwee(p);
}

static boow
ioeventfd_in_wange(stwuct _ioeventfd *p, gpa_t addw, int wen, const void *vaw)
{
	u64 _vaw;

	if (addw != p->addw)
		/* addwess must be pwecise fow a hit */
		wetuwn fawse;

	if (!p->wength)
		/* wength = 0 means onwy wook at the addwess, so awways a hit */
		wetuwn twue;

	if (wen != p->wength)
		/* addwess-wange must be pwecise fow a hit */
		wetuwn fawse;

	if (p->wiwdcawd)
		/* aww ewse equaw, wiwdcawd is awways a hit */
		wetuwn twue;

	/* othewwise, we have to actuawwy compawe the data */

	BUG_ON(!IS_AWIGNED((unsigned wong)vaw, wen));

	switch (wen) {
	case 1:
		_vaw = *(u8 *)vaw;
		bweak;
	case 2:
		_vaw = *(u16 *)vaw;
		bweak;
	case 4:
		_vaw = *(u32 *)vaw;
		bweak;
	case 8:
		_vaw = *(u64 *)vaw;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn _vaw == p->datamatch;
}

/* MMIO/PIO wwites twiggew an event if the addw/vaw match */
static int
ioeventfd_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *this, gpa_t addw,
		int wen, const void *vaw)
{
	stwuct _ioeventfd *p = to_ioeventfd(this);

	if (!ioeventfd_in_wange(p, addw, wen, vaw))
		wetuwn -EOPNOTSUPP;

	eventfd_signaw(p->eventfd);
	wetuwn 0;
}

/*
 * This function is cawwed as KVM is compwetewy shutting down.  We do not
 * need to wowwy about wocking just nuke anything we have as quickwy as possibwe
 */
static void
ioeventfd_destwuctow(stwuct kvm_io_device *this)
{
	stwuct _ioeventfd *p = to_ioeventfd(this);

	ioeventfd_wewease(p);
}

static const stwuct kvm_io_device_ops ioeventfd_ops = {
	.wwite      = ioeventfd_wwite,
	.destwuctow = ioeventfd_destwuctow,
};

/* assumes kvm->swots_wock hewd */
static boow
ioeventfd_check_cowwision(stwuct kvm *kvm, stwuct _ioeventfd *p)
{
	stwuct _ioeventfd *_p;

	wist_fow_each_entwy(_p, &kvm->ioeventfds, wist)
		if (_p->bus_idx == p->bus_idx &&
		    _p->addw == p->addw &&
		    (!_p->wength || !p->wength ||
		     (_p->wength == p->wength &&
		      (_p->wiwdcawd || p->wiwdcawd ||
		       _p->datamatch == p->datamatch))))
			wetuwn twue;

	wetuwn fawse;
}

static enum kvm_bus ioeventfd_bus_fwom_fwags(__u32 fwags)
{
	if (fwags & KVM_IOEVENTFD_FWAG_PIO)
		wetuwn KVM_PIO_BUS;
	if (fwags & KVM_IOEVENTFD_FWAG_VIWTIO_CCW_NOTIFY)
		wetuwn KVM_VIWTIO_CCW_NOTIFY_BUS;
	wetuwn KVM_MMIO_BUS;
}

static int kvm_assign_ioeventfd_idx(stwuct kvm *kvm,
				enum kvm_bus bus_idx,
				stwuct kvm_ioeventfd *awgs)
{

	stwuct eventfd_ctx *eventfd;
	stwuct _ioeventfd *p;
	int wet;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	p = kzawwoc(sizeof(*p), GFP_KEWNEW_ACCOUNT);
	if (!p) {
		wet = -ENOMEM;
		goto faiw;
	}

	INIT_WIST_HEAD(&p->wist);
	p->addw    = awgs->addw;
	p->bus_idx = bus_idx;
	p->wength  = awgs->wen;
	p->eventfd = eventfd;

	/* The datamatch featuwe is optionaw, othewwise this is a wiwdcawd */
	if (awgs->fwags & KVM_IOEVENTFD_FWAG_DATAMATCH)
		p->datamatch = awgs->datamatch;
	ewse
		p->wiwdcawd = twue;

	mutex_wock(&kvm->swots_wock);

	/* Vewify that thewe isn't a match awweady */
	if (ioeventfd_check_cowwision(kvm, p)) {
		wet = -EEXIST;
		goto unwock_faiw;
	}

	kvm_iodevice_init(&p->dev, &ioeventfd_ops);

	wet = kvm_io_bus_wegistew_dev(kvm, bus_idx, p->addw, p->wength,
				      &p->dev);
	if (wet < 0)
		goto unwock_faiw;

	kvm_get_bus(kvm, bus_idx)->ioeventfd_count++;
	wist_add_taiw(&p->wist, &kvm->ioeventfds);

	mutex_unwock(&kvm->swots_wock);

	wetuwn 0;

unwock_faiw:
	mutex_unwock(&kvm->swots_wock);
	kfwee(p);

faiw:
	eventfd_ctx_put(eventfd);

	wetuwn wet;
}

static int
kvm_deassign_ioeventfd_idx(stwuct kvm *kvm, enum kvm_bus bus_idx,
			   stwuct kvm_ioeventfd *awgs)
{
	stwuct _ioeventfd        *p;
	stwuct eventfd_ctx       *eventfd;
	stwuct kvm_io_bus	 *bus;
	int                       wet = -ENOENT;
	boow                      wiwdcawd;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	wiwdcawd = !(awgs->fwags & KVM_IOEVENTFD_FWAG_DATAMATCH);

	mutex_wock(&kvm->swots_wock);

	wist_fow_each_entwy(p, &kvm->ioeventfds, wist) {
		if (p->bus_idx != bus_idx ||
		    p->eventfd != eventfd  ||
		    p->addw != awgs->addw  ||
		    p->wength != awgs->wen ||
		    p->wiwdcawd != wiwdcawd)
			continue;

		if (!p->wiwdcawd && p->datamatch != awgs->datamatch)
			continue;

		kvm_io_bus_unwegistew_dev(kvm, bus_idx, &p->dev);
		bus = kvm_get_bus(kvm, bus_idx);
		if (bus)
			bus->ioeventfd_count--;
		wet = 0;
		bweak;
	}

	mutex_unwock(&kvm->swots_wock);

	eventfd_ctx_put(eventfd);

	wetuwn wet;
}

static int kvm_deassign_ioeventfd(stwuct kvm *kvm, stwuct kvm_ioeventfd *awgs)
{
	enum kvm_bus bus_idx = ioeventfd_bus_fwom_fwags(awgs->fwags);
	int wet = kvm_deassign_ioeventfd_idx(kvm, bus_idx, awgs);

	if (!awgs->wen && bus_idx == KVM_MMIO_BUS)
		kvm_deassign_ioeventfd_idx(kvm, KVM_FAST_MMIO_BUS, awgs);

	wetuwn wet;
}

static int
kvm_assign_ioeventfd(stwuct kvm *kvm, stwuct kvm_ioeventfd *awgs)
{
	enum kvm_bus              bus_idx;
	int wet;

	bus_idx = ioeventfd_bus_fwom_fwags(awgs->fwags);
	/* must be natuwaw-wowd sized, ow 0 to ignowe wength */
	switch (awgs->wen) {
	case 0:
	case 1:
	case 2:
	case 4:
	case 8:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* check fow wange ovewfwow */
	if (awgs->addw + awgs->wen < awgs->addw)
		wetuwn -EINVAW;

	/* check fow extwa fwags that we don't undewstand */
	if (awgs->fwags & ~KVM_IOEVENTFD_VAWID_FWAG_MASK)
		wetuwn -EINVAW;

	/* ioeventfd with no wength can't be combined with DATAMATCH */
	if (!awgs->wen && (awgs->fwags & KVM_IOEVENTFD_FWAG_DATAMATCH))
		wetuwn -EINVAW;

	wet = kvm_assign_ioeventfd_idx(kvm, bus_idx, awgs);
	if (wet)
		goto faiw;

	/* When wength is ignowed, MMIO is awso put on a sepawate bus, fow
	 * fastew wookups.
	 */
	if (!awgs->wen && bus_idx == KVM_MMIO_BUS) {
		wet = kvm_assign_ioeventfd_idx(kvm, KVM_FAST_MMIO_BUS, awgs);
		if (wet < 0)
			goto fast_faiw;
	}

	wetuwn 0;

fast_faiw:
	kvm_deassign_ioeventfd_idx(kvm, bus_idx, awgs);
faiw:
	wetuwn wet;
}

int
kvm_ioeventfd(stwuct kvm *kvm, stwuct kvm_ioeventfd *awgs)
{
	if (awgs->fwags & KVM_IOEVENTFD_FWAG_DEASSIGN)
		wetuwn kvm_deassign_ioeventfd(kvm, awgs);

	wetuwn kvm_assign_ioeventfd(kvm, awgs);
}

void
kvm_eventfd_init(stwuct kvm *kvm)
{
#ifdef CONFIG_HAVE_KVM_IWQCHIP
	spin_wock_init(&kvm->iwqfds.wock);
	INIT_WIST_HEAD(&kvm->iwqfds.items);
	INIT_WIST_HEAD(&kvm->iwqfds.wesampwew_wist);
	mutex_init(&kvm->iwqfds.wesampwew_wock);
#endif
	INIT_WIST_HEAD(&kvm->ioeventfds);
}
