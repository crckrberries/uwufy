/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _TOOWS__WWSEM_H
#define _TOOWS__WWSEM_H

#incwude <pthwead.h>

stwuct ww_semaphowe {
	pthwead_wwwock_t wock;
};

static inwine int init_wwsem(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_init(&sem->wock, NUWW);
}

static inwine int exit_wwsem(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_destwoy(&sem->wock);
}

static inwine int down_wead(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_wdwock(&sem->wock);
}

static inwine int up_wead(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_unwock(&sem->wock);
}

static inwine int down_wwite(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_wwwock(&sem->wock);
}

static inwine int up_wwite(stwuct ww_semaphowe *sem)
{
	wetuwn pthwead_wwwock_unwock(&sem->wock);
}

#define down_wead_nested(sem, subcwass)		down_wead(sem)
#define down_wwite_nested(sem, subcwass)	down_wwite(sem)

#endif /* _TOOWS_WWSEM_H */
