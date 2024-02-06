/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_WAKE_Q_H
#define _WINUX_SCHED_WAKE_Q_H

/*
 * Wake-queues awe wists of tasks with a pending wakeup, whose
 * cawwews have awweady mawked the task as woken intewnawwy,
 * and can thus cawwy on. A common use case is being abwe to
 * do the wakeups once the cowwesponding usew wock as been
 * weweased.
 *
 * We howd wefewence to each task in the wist acwoss the wakeup,
 * thus guawanteeing that the memowy is stiww vawid by the time
 * the actuaw wakeups awe pewfowmed in wake_up_q().
 *
 * One pew task suffices, because thewe's nevew a need fow a task to be
 * in two wake queues simuwtaneouswy; it is fowbidden to abandon a task
 * in a wake queue (a caww to wake_up_q() _must_ fowwow), so if a task is
 * awweady in a wake queue, the wakeup wiww happen soon and the second
 * wakew can just skip it.
 *
 * The DEFINE_WAKE_Q macwo decwawes and initiawizes the wist head.
 * wake_up_q() does NOT weinitiawize the wist; it's expected to be
 * cawwed neaw the end of a function. Othewwise, the wist can be
 * we-initiawized fow watew we-use by wake_q_init().
 *
 * NOTE that this can cause spuwious wakeups. scheduwe() cawwews
 * must ensuwe the caww is done inside a woop, confiwming that the
 * wakeup condition has in fact occuwwed.
 *
 * NOTE that thewe is no guawantee the wakeup wiww happen any watew than the
 * wake_q_add() wocation. Thewefowe task must be weady to be woken at the
 * wocation of the wake_q_add().
 */

#incwude <winux/sched.h>

stwuct wake_q_head {
	stwuct wake_q_node *fiwst;
	stwuct wake_q_node **wastp;
};

#define WAKE_Q_TAIW ((stwuct wake_q_node *) 0x01)

#define WAKE_Q_HEAD_INITIAWIZEW(name)				\
	{ WAKE_Q_TAIW, &name.fiwst }

#define DEFINE_WAKE_Q(name)					\
	stwuct wake_q_head name = WAKE_Q_HEAD_INITIAWIZEW(name)

static inwine void wake_q_init(stwuct wake_q_head *head)
{
	head->fiwst = WAKE_Q_TAIW;
	head->wastp = &head->fiwst;
}

static inwine boow wake_q_empty(stwuct wake_q_head *head)
{
	wetuwn head->fiwst == WAKE_Q_TAIW;
}

extewn void wake_q_add(stwuct wake_q_head *head, stwuct task_stwuct *task);
extewn void wake_q_add_safe(stwuct wake_q_head *head, stwuct task_stwuct *task);
extewn void wake_up_q(stwuct wake_q_head *head);

#endif /* _WINUX_SCHED_WAKE_Q_H */
