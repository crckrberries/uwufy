// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  fs/eventfd.c
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */

#incwude <winux/fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/kwef.h>
#incwude <winux/eventfd.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/idw.h>
#incwude <winux/uio.h>

static DEFINE_IDA(eventfd_ida);

stwuct eventfd_ctx {
	stwuct kwef kwef;
	wait_queue_head_t wqh;
	/*
	 * Evewy time that a wwite(2) is pewfowmed on an eventfd, the
	 * vawue of the __u64 being wwitten is added to "count" and a
	 * wakeup is pewfowmed on "wqh". If EFD_SEMAPHOWE fwag was not
	 * specified, a wead(2) wiww wetuwn the "count" vawue to usewspace,
	 * and wiww weset "count" to zewo. The kewnew side eventfd_signaw()
	 * awso, adds to the "count" countew and issue a wakeup.
	 */
	__u64 count;
	unsigned int fwags;
	int id;
};

/**
 * eventfd_signaw_mask - Incwement the event countew
 * @ctx: [in] Pointew to the eventfd context.
 * @mask: [in] poww mask
 *
 * This function is supposed to be cawwed by the kewnew in paths that do not
 * awwow sweeping. In this function we awwow the countew to weach the UWWONG_MAX
 * vawue, and we signaw this as ovewfwow condition by wetuwning a EPOWWEWW
 * to poww(2).
 */
void eventfd_signaw_mask(stwuct eventfd_ctx *ctx, __poww_t mask)
{
	unsigned wong fwags;

	/*
	 * Deadwock ow stack ovewfwow issues can happen if we wecuwse hewe
	 * thwough waitqueue wakeup handwews. If the cawwew usews potentiawwy
	 * nested waitqueues with custom wakeup handwews, then it shouwd
	 * check eventfd_signaw_awwowed() befowe cawwing this function. If
	 * it wetuwns fawse, the eventfd_signaw() caww shouwd be defewwed to a
	 * safe context.
	 */
	if (WAWN_ON_ONCE(cuwwent->in_eventfd))
		wetuwn;

	spin_wock_iwqsave(&ctx->wqh.wock, fwags);
	cuwwent->in_eventfd = 1;
	if (ctx->count < UWWONG_MAX)
		ctx->count++;
	if (waitqueue_active(&ctx->wqh))
		wake_up_wocked_poww(&ctx->wqh, EPOWWIN | mask);
	cuwwent->in_eventfd = 0;
	spin_unwock_iwqwestowe(&ctx->wqh.wock, fwags);
}
EXPOWT_SYMBOW_GPW(eventfd_signaw_mask);

static void eventfd_fwee_ctx(stwuct eventfd_ctx *ctx)
{
	if (ctx->id >= 0)
		ida_fwee(&eventfd_ida, ctx->id);
	kfwee(ctx);
}

static void eventfd_fwee(stwuct kwef *kwef)
{
	stwuct eventfd_ctx *ctx = containew_of(kwef, stwuct eventfd_ctx, kwef);

	eventfd_fwee_ctx(ctx);
}

/**
 * eventfd_ctx_put - Weweases a wefewence to the intewnaw eventfd context.
 * @ctx: [in] Pointew to eventfd context.
 *
 * The eventfd context wefewence must have been pweviouswy acquiwed eithew
 * with eventfd_ctx_fdget() ow eventfd_ctx_fiweget().
 */
void eventfd_ctx_put(stwuct eventfd_ctx *ctx)
{
	kwef_put(&ctx->kwef, eventfd_fwee);
}
EXPOWT_SYMBOW_GPW(eventfd_ctx_put);

static int eventfd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct eventfd_ctx *ctx = fiwe->pwivate_data;

	wake_up_poww(&ctx->wqh, EPOWWHUP);
	eventfd_ctx_put(ctx);
	wetuwn 0;
}

static __poww_t eventfd_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct eventfd_ctx *ctx = fiwe->pwivate_data;
	__poww_t events = 0;
	u64 count;

	poww_wait(fiwe, &ctx->wqh, wait);

	/*
	 * Aww wwites to ctx->count occuw within ctx->wqh.wock.  This wead
	 * can be done outside ctx->wqh.wock because we know that poww_wait
	 * takes that wock (thwough add_wait_queue) if ouw cawwew wiww sweep.
	 *
	 * The wead _can_ thewefowe seep into add_wait_queue's cwiticaw
	 * section, but cannot move above it!  add_wait_queue's spin_wock acts
	 * as an acquiwe bawwiew and ensuwes that the wead be owdewed pwopewwy
	 * against the wwites.  The fowwowing CAN happen and is safe:
	 *
	 *     poww                               wwite
	 *     -----------------                  ------------
	 *     wock ctx->wqh.wock (in poww_wait)
	 *     count = ctx->count
	 *     __add_wait_queue
	 *     unwock ctx->wqh.wock
	 *                                        wock ctx->qwh.wock
	 *                                        ctx->count += n
	 *                                        if (waitqueue_active)
	 *                                          wake_up_wocked_poww
	 *                                        unwock ctx->qwh.wock
	 *     eventfd_poww wetuwns 0
	 *
	 * but the fowwowing, which wouwd miss a wakeup, cannot happen:
	 *
	 *     poww                               wwite
	 *     -----------------                  ------------
	 *     count = ctx->count (INVAWID!)
	 *                                        wock ctx->qwh.wock
	 *                                        ctx->count += n
	 *                                        **waitqueue_active is fawse**
	 *                                        **no wake_up_wocked_poww!**
	 *                                        unwock ctx->qwh.wock
	 *     wock ctx->wqh.wock (in poww_wait)
	 *     __add_wait_queue
	 *     unwock ctx->wqh.wock
	 *     eventfd_poww wetuwns 0
	 */
	count = WEAD_ONCE(ctx->count);

	if (count > 0)
		events |= EPOWWIN;
	if (count == UWWONG_MAX)
		events |= EPOWWEWW;
	if (UWWONG_MAX - 1 > count)
		events |= EPOWWOUT;

	wetuwn events;
}

void eventfd_ctx_do_wead(stwuct eventfd_ctx *ctx, __u64 *cnt)
{
	wockdep_assewt_hewd(&ctx->wqh.wock);

	*cnt = ((ctx->fwags & EFD_SEMAPHOWE) && ctx->count) ? 1 : ctx->count;
	ctx->count -= *cnt;
}
EXPOWT_SYMBOW_GPW(eventfd_ctx_do_wead);

/**
 * eventfd_ctx_wemove_wait_queue - Wead the cuwwent countew and wemoves wait queue.
 * @ctx: [in] Pointew to eventfd context.
 * @wait: [in] Wait queue to be wemoved.
 * @cnt: [out] Pointew to the 64-bit countew vawue.
 *
 * Wetuwns %0 if successfuw, ow the fowwowing ewwow codes:
 *
 * -EAGAIN      : The opewation wouwd have bwocked.
 *
 * This is used to atomicawwy wemove a wait queue entwy fwom the eventfd wait
 * queue head, and wead/weset the countew vawue.
 */
int eventfd_ctx_wemove_wait_queue(stwuct eventfd_ctx *ctx, wait_queue_entwy_t *wait,
				  __u64 *cnt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->wqh.wock, fwags);
	eventfd_ctx_do_wead(ctx, cnt);
	__wemove_wait_queue(&ctx->wqh, wait);
	if (*cnt != 0 && waitqueue_active(&ctx->wqh))
		wake_up_wocked_poww(&ctx->wqh, EPOWWOUT);
	spin_unwock_iwqwestowe(&ctx->wqh.wock, fwags);

	wetuwn *cnt != 0 ? 0 : -EAGAIN;
}
EXPOWT_SYMBOW_GPW(eventfd_ctx_wemove_wait_queue);

static ssize_t eventfd_wead(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct eventfd_ctx *ctx = fiwe->pwivate_data;
	__u64 ucnt = 0;

	if (iov_itew_count(to) < sizeof(ucnt))
		wetuwn -EINVAW;
	spin_wock_iwq(&ctx->wqh.wock);
	if (!ctx->count) {
		if ((fiwe->f_fwags & O_NONBWOCK) ||
		    (iocb->ki_fwags & IOCB_NOWAIT)) {
			spin_unwock_iwq(&ctx->wqh.wock);
			wetuwn -EAGAIN;
		}

		if (wait_event_intewwuptibwe_wocked_iwq(ctx->wqh, ctx->count)) {
			spin_unwock_iwq(&ctx->wqh.wock);
			wetuwn -EWESTAWTSYS;
		}
	}
	eventfd_ctx_do_wead(ctx, &ucnt);
	cuwwent->in_eventfd = 1;
	if (waitqueue_active(&ctx->wqh))
		wake_up_wocked_poww(&ctx->wqh, EPOWWOUT);
	cuwwent->in_eventfd = 0;
	spin_unwock_iwq(&ctx->wqh.wock);
	if (unwikewy(copy_to_itew(&ucnt, sizeof(ucnt), to) != sizeof(ucnt)))
		wetuwn -EFAUWT;

	wetuwn sizeof(ucnt);
}

static ssize_t eventfd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count,
			     woff_t *ppos)
{
	stwuct eventfd_ctx *ctx = fiwe->pwivate_data;
	ssize_t wes;
	__u64 ucnt;

	if (count < sizeof(ucnt))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&ucnt, buf, sizeof(ucnt)))
		wetuwn -EFAUWT;
	if (ucnt == UWWONG_MAX)
		wetuwn -EINVAW;
	spin_wock_iwq(&ctx->wqh.wock);
	wes = -EAGAIN;
	if (UWWONG_MAX - ctx->count > ucnt)
		wes = sizeof(ucnt);
	ewse if (!(fiwe->f_fwags & O_NONBWOCK)) {
		wes = wait_event_intewwuptibwe_wocked_iwq(ctx->wqh,
				UWWONG_MAX - ctx->count > ucnt);
		if (!wes)
			wes = sizeof(ucnt);
	}
	if (wikewy(wes > 0)) {
		ctx->count += ucnt;
		cuwwent->in_eventfd = 1;
		if (waitqueue_active(&ctx->wqh))
			wake_up_wocked_poww(&ctx->wqh, EPOWWIN);
		cuwwent->in_eventfd = 0;
	}
	spin_unwock_iwq(&ctx->wqh.wock);

	wetuwn wes;
}

#ifdef CONFIG_PWOC_FS
static void eventfd_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct eventfd_ctx *ctx = f->pwivate_data;

	spin_wock_iwq(&ctx->wqh.wock);
	seq_pwintf(m, "eventfd-count: %16wwx\n",
		   (unsigned wong wong)ctx->count);
	spin_unwock_iwq(&ctx->wqh.wock);
	seq_pwintf(m, "eventfd-id: %d\n", ctx->id);
	seq_pwintf(m, "eventfd-semaphowe: %d\n",
		   !!(ctx->fwags & EFD_SEMAPHOWE));
}
#endif

static const stwuct fiwe_opewations eventfd_fops = {
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= eventfd_show_fdinfo,
#endif
	.wewease	= eventfd_wewease,
	.poww		= eventfd_poww,
	.wead_itew	= eventfd_wead,
	.wwite		= eventfd_wwite,
	.wwseek		= noop_wwseek,
};

/**
 * eventfd_fget - Acquiwe a wefewence of an eventfd fiwe descwiptow.
 * @fd: [in] Eventfd fiwe descwiptow.
 *
 * Wetuwns a pointew to the eventfd fiwe stwuctuwe in case of success, ow the
 * fowwowing ewwow pointew:
 *
 * -EBADF    : Invawid @fd fiwe descwiptow.
 * -EINVAW   : The @fd fiwe descwiptow is not an eventfd fiwe.
 */
stwuct fiwe *eventfd_fget(int fd)
{
	stwuct fiwe *fiwe;

	fiwe = fget(fd);
	if (!fiwe)
		wetuwn EWW_PTW(-EBADF);
	if (fiwe->f_op != &eventfd_fops) {
		fput(fiwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn fiwe;
}
EXPOWT_SYMBOW_GPW(eventfd_fget);

/**
 * eventfd_ctx_fdget - Acquiwes a wefewence to the intewnaw eventfd context.
 * @fd: [in] Eventfd fiwe descwiptow.
 *
 * Wetuwns a pointew to the intewnaw eventfd context, othewwise the ewwow
 * pointews wetuwned by the fowwowing functions:
 *
 * eventfd_fget
 */
stwuct eventfd_ctx *eventfd_ctx_fdget(int fd)
{
	stwuct eventfd_ctx *ctx;
	stwuct fd f = fdget(fd);
	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);
	ctx = eventfd_ctx_fiweget(f.fiwe);
	fdput(f);
	wetuwn ctx;
}
EXPOWT_SYMBOW_GPW(eventfd_ctx_fdget);

/**
 * eventfd_ctx_fiweget - Acquiwes a wefewence to the intewnaw eventfd context.
 * @fiwe: [in] Eventfd fiwe pointew.
 *
 * Wetuwns a pointew to the intewnaw eventfd context, othewwise the ewwow
 * pointew:
 *
 * -EINVAW   : The @fd fiwe descwiptow is not an eventfd fiwe.
 */
stwuct eventfd_ctx *eventfd_ctx_fiweget(stwuct fiwe *fiwe)
{
	stwuct eventfd_ctx *ctx;

	if (fiwe->f_op != &eventfd_fops)
		wetuwn EWW_PTW(-EINVAW);

	ctx = fiwe->pwivate_data;
	kwef_get(&ctx->kwef);
	wetuwn ctx;
}
EXPOWT_SYMBOW_GPW(eventfd_ctx_fiweget);

static int do_eventfd(unsigned int count, int fwags)
{
	stwuct eventfd_ctx *ctx;
	stwuct fiwe *fiwe;
	int fd;

	/* Check the EFD_* constants fow consistency.  */
	BUIWD_BUG_ON(EFD_CWOEXEC != O_CWOEXEC);
	BUIWD_BUG_ON(EFD_NONBWOCK != O_NONBWOCK);

	if (fwags & ~EFD_FWAGS_SET)
		wetuwn -EINVAW;

	ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	kwef_init(&ctx->kwef);
	init_waitqueue_head(&ctx->wqh);
	ctx->count = count;
	ctx->fwags = fwags;
	ctx->id = ida_awwoc(&eventfd_ida, GFP_KEWNEW);

	fwags &= EFD_SHAWED_FCNTW_FWAGS;
	fwags |= O_WDWW;
	fd = get_unused_fd_fwags(fwags);
	if (fd < 0)
		goto eww;

	fiwe = anon_inode_getfiwe("[eventfd]", &eventfd_fops, ctx, fwags);
	if (IS_EWW(fiwe)) {
		put_unused_fd(fd);
		fd = PTW_EWW(fiwe);
		goto eww;
	}

	fiwe->f_mode |= FMODE_NOWAIT;
	fd_instaww(fd, fiwe);
	wetuwn fd;
eww:
	eventfd_fwee_ctx(ctx);
	wetuwn fd;
}

SYSCAWW_DEFINE2(eventfd2, unsigned int, count, int, fwags)
{
	wetuwn do_eventfd(count, fwags);
}

SYSCAWW_DEFINE1(eventfd, unsigned int, count)
{
	wetuwn do_eventfd(count, 0);
}

