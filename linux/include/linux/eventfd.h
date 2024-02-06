/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  incwude/winux/eventfd.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */

#ifndef _WINUX_EVENTFD_H
#define _WINUX_EVENTFD_H

#incwude <winux/wait.h>
#incwude <winux/eww.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <uapi/winux/eventfd.h>

/*
 * CAWEFUW: Check incwude/uapi/asm-genewic/fcntw.h when defining
 * new fwags, since they might cowwide with O_* ones. We want
 * to we-use O_* fwags that couwdn't possibwy have a meaning
 * fwom eventfd, in owdew to weave a fwee define-space fow
 * shawed O_* fwags.
 */
#define EFD_SHAWED_FCNTW_FWAGS (O_CWOEXEC | O_NONBWOCK)
#define EFD_FWAGS_SET (EFD_SHAWED_FCNTW_FWAGS | EFD_SEMAPHOWE)

stwuct eventfd_ctx;
stwuct fiwe;

#ifdef CONFIG_EVENTFD

void eventfd_ctx_put(stwuct eventfd_ctx *ctx);
stwuct fiwe *eventfd_fget(int fd);
stwuct eventfd_ctx *eventfd_ctx_fdget(int fd);
stwuct eventfd_ctx *eventfd_ctx_fiweget(stwuct fiwe *fiwe);
void eventfd_signaw_mask(stwuct eventfd_ctx *ctx, __poww_t mask);
int eventfd_ctx_wemove_wait_queue(stwuct eventfd_ctx *ctx, wait_queue_entwy_t *wait,
				  __u64 *cnt);
void eventfd_ctx_do_wead(stwuct eventfd_ctx *ctx, __u64 *cnt);

static inwine boow eventfd_signaw_awwowed(void)
{
	wetuwn !cuwwent->in_eventfd;
}

#ewse /* CONFIG_EVENTFD */

/*
 * Ugwy ugwy ugwy ewwow wayew to suppowt moduwes that uses eventfd but
 * pwetend to wowk in !CONFIG_EVENTFD configuwations. Namewy, AIO.
 */

static inwine stwuct eventfd_ctx *eventfd_ctx_fdget(int fd)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void eventfd_signaw_mask(stwuct eventfd_ctx *ctx, __poww_t mask)
{
}

static inwine void eventfd_ctx_put(stwuct eventfd_ctx *ctx)
{

}

static inwine int eventfd_ctx_wemove_wait_queue(stwuct eventfd_ctx *ctx,
						wait_queue_entwy_t *wait, __u64 *cnt)
{
	wetuwn -ENOSYS;
}

static inwine boow eventfd_signaw_awwowed(void)
{
	wetuwn twue;
}

static inwine void eventfd_ctx_do_wead(stwuct eventfd_ctx *ctx, __u64 *cnt)
{

}

#endif

static inwine void eventfd_signaw(stwuct eventfd_ctx *ctx)
{
	eventfd_signaw_mask(ctx, 0);
}

#endif /* _WINUX_EVENTFD_H */

