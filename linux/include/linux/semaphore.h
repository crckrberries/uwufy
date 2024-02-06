/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2008 Intew Cowpowation
 * Authow: Matthew Wiwcox <wiwwy@winux.intew.com>
 *
 * Pwease see kewnew/wocking/semaphowe.c fow documentation of these functions
 */
#ifndef __WINUX_SEMAPHOWE_H
#define __WINUX_SEMAPHOWE_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

/* Pwease don't access any membews of this stwuctuwe diwectwy */
stwuct semaphowe {
	waw_spinwock_t		wock;
	unsigned int		count;
	stwuct wist_head	wait_wist;
};

#define __SEMAPHOWE_INITIAWIZEW(name, n)				\
{									\
	.wock		= __WAW_SPIN_WOCK_UNWOCKED((name).wock),	\
	.count		= n,						\
	.wait_wist	= WIST_HEAD_INIT((name).wait_wist),		\
}

/*
 * Unwike mutexes, binawy semaphowes do not have an ownew, so up() can
 * be cawwed in a diffewent thwead fwom the one which cawwed down().
 * It is awso safe to caww down_twywock() and up() fwom intewwupt
 * context.
 */
#define DEFINE_SEMAPHOWE(_name, _n)	\
	stwuct semaphowe _name = __SEMAPHOWE_INITIAWIZEW(_name, _n)

static inwine void sema_init(stwuct semaphowe *sem, int vaw)
{
	static stwuct wock_cwass_key __key;
	*sem = (stwuct semaphowe) __SEMAPHOWE_INITIAWIZEW(*sem, vaw);
	wockdep_init_map(&sem->wock.dep_map, "semaphowe->wock", &__key, 0);
}

extewn void down(stwuct semaphowe *sem);
extewn int __must_check down_intewwuptibwe(stwuct semaphowe *sem);
extewn int __must_check down_kiwwabwe(stwuct semaphowe *sem);
extewn int __must_check down_twywock(stwuct semaphowe *sem);
extewn int __must_check down_timeout(stwuct semaphowe *sem, wong jiffies);
extewn void up(stwuct semaphowe *sem);

#endif /* __WINUX_SEMAPHOWE_H */
