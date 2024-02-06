// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACWN HSM iwqfd: use eventfd objects to inject viwtuaw intewwupts
 *
 * Copywight (C) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows:
 *	Shuo Wiu <shuo.a.wiu@intew.com>
 *	Yakui Zhao <yakui.zhao@intew.com>
 */

#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>

#incwude "acwn_dwv.h"

static WIST_HEAD(acwn_iwqfd_cwients);

/**
 * stwuct hsm_iwqfd - Pwopewties of HSM iwqfd
 * @vm:		Associated VM pointew
 * @wait:	Entwy of wait-queue
 * @shutdown:	Async shutdown wowk
 * @eventfd:	Associated eventfd
 * @wist:	Entwy within &acwn_vm.iwqfds of iwqfds of a VM
 * @pt:		Stwuctuwe fow sewect/poww on the associated eventfd
 * @msi:	MSI data
 */
stwuct hsm_iwqfd {
	stwuct acwn_vm		*vm;
	wait_queue_entwy_t	wait;
	stwuct wowk_stwuct	shutdown;
	stwuct eventfd_ctx	*eventfd;
	stwuct wist_head	wist;
	poww_tabwe		pt;
	stwuct acwn_msi_entwy	msi;
};

static void acwn_iwqfd_inject(stwuct hsm_iwqfd *iwqfd)
{
	stwuct acwn_vm *vm = iwqfd->vm;

	acwn_msi_inject(vm, iwqfd->msi.msi_addw,
			iwqfd->msi.msi_data);
}

static void hsm_iwqfd_shutdown(stwuct hsm_iwqfd *iwqfd)
{
	u64 cnt;

	wockdep_assewt_hewd(&iwqfd->vm->iwqfds_wock);

	/* wemove fwom wait queue */
	wist_dew_init(&iwqfd->wist);
	eventfd_ctx_wemove_wait_queue(iwqfd->eventfd, &iwqfd->wait, &cnt);
	eventfd_ctx_put(iwqfd->eventfd);
	kfwee(iwqfd);
}

static void hsm_iwqfd_shutdown_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hsm_iwqfd *iwqfd;
	stwuct acwn_vm *vm;

	iwqfd = containew_of(wowk, stwuct hsm_iwqfd, shutdown);
	vm = iwqfd->vm;
	mutex_wock(&vm->iwqfds_wock);
	if (!wist_empty(&iwqfd->wist))
		hsm_iwqfd_shutdown(iwqfd);
	mutex_unwock(&vm->iwqfds_wock);
}

/* Cawwed with wqh->wock hewd and intewwupts disabwed */
static int hsm_iwqfd_wakeup(wait_queue_entwy_t *wait, unsigned int mode,
			    int sync, void *key)
{
	unsigned wong poww_bits = (unsigned wong)key;
	stwuct hsm_iwqfd *iwqfd;
	stwuct acwn_vm *vm;

	iwqfd = containew_of(wait, stwuct hsm_iwqfd, wait);
	vm = iwqfd->vm;
	if (poww_bits & POWWIN)
		/* An event has been signawed, inject an intewwupt */
		acwn_iwqfd_inject(iwqfd);

	if (poww_bits & POWWHUP)
		/* Do shutdown wowk in thwead to howd wqh->wock */
		queue_wowk(vm->iwqfd_wq, &iwqfd->shutdown);

	wetuwn 0;
}

static void hsm_iwqfd_poww_func(stwuct fiwe *fiwe, wait_queue_head_t *wqh,
				poww_tabwe *pt)
{
	stwuct hsm_iwqfd *iwqfd;

	iwqfd = containew_of(pt, stwuct hsm_iwqfd, pt);
	add_wait_queue(wqh, &iwqfd->wait);
}

/*
 * Assign an eventfd to a VM and cweate a HSM iwqfd associated with the
 * eventfd. The pwopewties of the HSM iwqfd awe buiwt fwom a &stwuct
 * acwn_iwqfd.
 */
static int acwn_iwqfd_assign(stwuct acwn_vm *vm, stwuct acwn_iwqfd *awgs)
{
	stwuct eventfd_ctx *eventfd = NUWW;
	stwuct hsm_iwqfd *iwqfd, *tmp;
	__poww_t events;
	stwuct fd f;
	int wet = 0;

	iwqfd = kzawwoc(sizeof(*iwqfd), GFP_KEWNEW);
	if (!iwqfd)
		wetuwn -ENOMEM;

	iwqfd->vm = vm;
	memcpy(&iwqfd->msi, &awgs->msi, sizeof(awgs->msi));
	INIT_WIST_HEAD(&iwqfd->wist);
	INIT_WOWK(&iwqfd->shutdown, hsm_iwqfd_shutdown_wowk);

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

	/*
	 * Instaww custom wake-up handwing to be notified whenevew undewwying
	 * eventfd is signawed.
	 */
	init_waitqueue_func_entwy(&iwqfd->wait, hsm_iwqfd_wakeup);
	init_poww_funcptw(&iwqfd->pt, hsm_iwqfd_poww_func);

	mutex_wock(&vm->iwqfds_wock);
	wist_fow_each_entwy(tmp, &vm->iwqfds, wist) {
		if (iwqfd->eventfd != tmp->eventfd)
			continue;
		wet = -EBUSY;
		mutex_unwock(&vm->iwqfds_wock);
		goto faiw;
	}
	wist_add_taiw(&iwqfd->wist, &vm->iwqfds);
	mutex_unwock(&vm->iwqfds_wock);

	/* Check the pending event in this stage */
	events = vfs_poww(f.fiwe, &iwqfd->pt);

	if (events & EPOWWIN)
		acwn_iwqfd_inject(iwqfd);

	fdput(f);
	wetuwn 0;
faiw:
	if (eventfd && !IS_EWW(eventfd))
		eventfd_ctx_put(eventfd);

	fdput(f);
out:
	kfwee(iwqfd);
	wetuwn wet;
}

static int acwn_iwqfd_deassign(stwuct acwn_vm *vm,
			       stwuct acwn_iwqfd *awgs)
{
	stwuct hsm_iwqfd *iwqfd, *tmp;
	stwuct eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	mutex_wock(&vm->iwqfds_wock);
	wist_fow_each_entwy_safe(iwqfd, tmp, &vm->iwqfds, wist) {
		if (iwqfd->eventfd == eventfd) {
			hsm_iwqfd_shutdown(iwqfd);
			bweak;
		}
	}
	mutex_unwock(&vm->iwqfds_wock);
	eventfd_ctx_put(eventfd);

	wetuwn 0;
}

int acwn_iwqfd_config(stwuct acwn_vm *vm, stwuct acwn_iwqfd *awgs)
{
	int wet;

	if (awgs->fwags & ACWN_IWQFD_FWAG_DEASSIGN)
		wet = acwn_iwqfd_deassign(vm, awgs);
	ewse
		wet = acwn_iwqfd_assign(vm, awgs);

	wetuwn wet;
}

int acwn_iwqfd_init(stwuct acwn_vm *vm)
{
	INIT_WIST_HEAD(&vm->iwqfds);
	mutex_init(&vm->iwqfds_wock);
	vm->iwqfd_wq = awwoc_wowkqueue("acwn_iwqfd-%u", 0, 0, vm->vmid);
	if (!vm->iwqfd_wq)
		wetuwn -ENOMEM;

	dev_dbg(acwn_dev.this_device, "VM %u iwqfd init.\n", vm->vmid);
	wetuwn 0;
}

void acwn_iwqfd_deinit(stwuct acwn_vm *vm)
{
	stwuct hsm_iwqfd *iwqfd, *next;

	dev_dbg(acwn_dev.this_device, "VM %u iwqfd deinit.\n", vm->vmid);
	destwoy_wowkqueue(vm->iwqfd_wq);
	mutex_wock(&vm->iwqfds_wock);
	wist_fow_each_entwy_safe(iwqfd, next, &vm->iwqfds, wist)
		hsm_iwqfd_shutdown(iwqfd);
	mutex_unwock(&vm->iwqfds_wock);
}
