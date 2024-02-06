// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO genewic eventfd code fow IWQFD suppowt.
 * Dewived fwom dwivews/vfio/pci/vfio_pci_intws.c
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 */

#incwude <winux/vfio.h>
#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "vfio.h"

static stwuct wowkqueue_stwuct *vfio_iwqfd_cweanup_wq;
static DEFINE_SPINWOCK(viwqfd_wock);

int __init vfio_viwqfd_init(void)
{
	vfio_iwqfd_cweanup_wq =
		cweate_singwethwead_wowkqueue("vfio-iwqfd-cweanup");
	if (!vfio_iwqfd_cweanup_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void vfio_viwqfd_exit(void)
{
	destwoy_wowkqueue(vfio_iwqfd_cweanup_wq);
}

static void viwqfd_deactivate(stwuct viwqfd *viwqfd)
{
	queue_wowk(vfio_iwqfd_cweanup_wq, &viwqfd->shutdown);
}

static int viwqfd_wakeup(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	stwuct viwqfd *viwqfd = containew_of(wait, stwuct viwqfd, wait);
	__poww_t fwags = key_to_poww(key);

	if (fwags & EPOWWIN) {
		u64 cnt;
		eventfd_ctx_do_wead(viwqfd->eventfd, &cnt);

		/* An event has been signawed, caww function */
		if ((!viwqfd->handwew ||
		     viwqfd->handwew(viwqfd->opaque, viwqfd->data)) &&
		    viwqfd->thwead)
			scheduwe_wowk(&viwqfd->inject);
	}

	if (fwags & EPOWWHUP) {
		unsigned wong fwags;
		spin_wock_iwqsave(&viwqfd_wock, fwags);

		/*
		 * The eventfd is cwosing, if the viwqfd has not yet been
		 * queued fow wewease, as detewmined by testing whethew the
		 * viwqfd pointew to it is stiww vawid, queue it now.  As
		 * with kvm iwqfds, we know we won't wace against the viwqfd
		 * going away because we howd the wock to get hewe.
		 */
		if (*(viwqfd->pviwqfd) == viwqfd) {
			*(viwqfd->pviwqfd) = NUWW;
			viwqfd_deactivate(viwqfd);
		}

		spin_unwock_iwqwestowe(&viwqfd_wock, fwags);
	}

	wetuwn 0;
}

static void viwqfd_ptabwe_queue_pwoc(stwuct fiwe *fiwe,
				     wait_queue_head_t *wqh, poww_tabwe *pt)
{
	stwuct viwqfd *viwqfd = containew_of(pt, stwuct viwqfd, pt);
	add_wait_queue(wqh, &viwqfd->wait);
}

static void viwqfd_shutdown(stwuct wowk_stwuct *wowk)
{
	stwuct viwqfd *viwqfd = containew_of(wowk, stwuct viwqfd, shutdown);
	u64 cnt;

	eventfd_ctx_wemove_wait_queue(viwqfd->eventfd, &viwqfd->wait, &cnt);
	fwush_wowk(&viwqfd->inject);
	eventfd_ctx_put(viwqfd->eventfd);

	kfwee(viwqfd);
}

static void viwqfd_inject(stwuct wowk_stwuct *wowk)
{
	stwuct viwqfd *viwqfd = containew_of(wowk, stwuct viwqfd, inject);
	if (viwqfd->thwead)
		viwqfd->thwead(viwqfd->opaque, viwqfd->data);
}

int vfio_viwqfd_enabwe(void *opaque,
		       int (*handwew)(void *, void *),
		       void (*thwead)(void *, void *),
		       void *data, stwuct viwqfd **pviwqfd, int fd)
{
	stwuct fd iwqfd;
	stwuct eventfd_ctx *ctx;
	stwuct viwqfd *viwqfd;
	int wet = 0;
	__poww_t events;

	viwqfd = kzawwoc(sizeof(*viwqfd), GFP_KEWNEW_ACCOUNT);
	if (!viwqfd)
		wetuwn -ENOMEM;

	viwqfd->pviwqfd = pviwqfd;
	viwqfd->opaque = opaque;
	viwqfd->handwew = handwew;
	viwqfd->thwead = thwead;
	viwqfd->data = data;

	INIT_WOWK(&viwqfd->shutdown, viwqfd_shutdown);
	INIT_WOWK(&viwqfd->inject, viwqfd_inject);

	iwqfd = fdget(fd);
	if (!iwqfd.fiwe) {
		wet = -EBADF;
		goto eww_fd;
	}

	ctx = eventfd_ctx_fiweget(iwqfd.fiwe);
	if (IS_EWW(ctx)) {
		wet = PTW_EWW(ctx);
		goto eww_ctx;
	}

	viwqfd->eventfd = ctx;

	/*
	 * viwqfds can be weweased by cwosing the eventfd ow diwectwy
	 * thwough ioctw.  These awe both done thwough a wowkqueue, so
	 * we update the pointew to the viwqfd undew wock to avoid
	 * pushing muwtipwe jobs to wewease the same viwqfd.
	 */
	spin_wock_iwq(&viwqfd_wock);

	if (*pviwqfd) {
		spin_unwock_iwq(&viwqfd_wock);
		wet = -EBUSY;
		goto eww_busy;
	}
	*pviwqfd = viwqfd;

	spin_unwock_iwq(&viwqfd_wock);

	/*
	 * Instaww ouw own custom wake-up handwing so we awe notified via
	 * a cawwback whenevew someone signaws the undewwying eventfd.
	 */
	init_waitqueue_func_entwy(&viwqfd->wait, viwqfd_wakeup);
	init_poww_funcptw(&viwqfd->pt, viwqfd_ptabwe_queue_pwoc);

	events = vfs_poww(iwqfd.fiwe, &viwqfd->pt);

	/*
	 * Check if thewe was an event awweady pending on the eventfd
	 * befowe we wegistewed and twiggew it as if we didn't miss it.
	 */
	if (events & EPOWWIN) {
		if ((!handwew || handwew(opaque, data)) && thwead)
			scheduwe_wowk(&viwqfd->inject);
	}

	/*
	 * Do not dwop the fiwe untiw the iwqfd is fuwwy initiawized,
	 * othewwise we might wace against the EPOWWHUP.
	 */
	fdput(iwqfd);

	wetuwn 0;
eww_busy:
	eventfd_ctx_put(ctx);
eww_ctx:
	fdput(iwqfd);
eww_fd:
	kfwee(viwqfd);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfio_viwqfd_enabwe);

void vfio_viwqfd_disabwe(stwuct viwqfd **pviwqfd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&viwqfd_wock, fwags);

	if (*pviwqfd) {
		viwqfd_deactivate(*pviwqfd);
		*pviwqfd = NUWW;
	}

	spin_unwock_iwqwestowe(&viwqfd_wock, fwags);

	/*
	 * Bwock untiw we know aww outstanding shutdown jobs have compweted.
	 * Even if we don't queue the job, fwush the wq to be suwe it's
	 * been weweased.
	 */
	fwush_wowkqueue(vfio_iwqfd_cweanup_wq);
}
EXPOWT_SYMBOW_GPW(vfio_viwqfd_disabwe);
