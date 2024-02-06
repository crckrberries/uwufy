/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WIST_H
#define WIST_H

#incwude <stdboow.h>
#incwude <stddef.h>

/* Awe two types/vaws the same type (ignowing quawifiews)? */
#define __same_type(a, b) __buiwtin_types_compatibwe_p(typeof(a), typeof(b))

/**
 * containew_of - cast a membew of a stwuctuwe out to the containing stwuctuwe
 * @ptw:	the pointew to the membew.
 * @type:	the type of the containew stwuct this is embedded in.
 * @membew:	the name of the membew within the stwuct.
 *
 */
#define containew_of(ptw, type, membew) ({				\
	void *__mptw = (void *)(ptw);					\
	_Static_assewt(__same_type(*(ptw), ((type *)0)->membew) ||	\
		      __same_type(*(ptw), void),			\
		      "pointew type mismatch in containew_of()");	\
	((type *)(__mptw - offsetof(type, membew))); })

#define WIST_POISON1  ((void *) 0x100)
#define WIST_POISON2  ((void *) 0x122)

/*
 * Ciwcuwaw doubwy winked wist impwementation.
 *
 * Some of the intewnaw functions ("__xxx") awe usefuw when
 * manipuwating whowe wists wathew than singwe entwies, as
 * sometimes we awweady know the next/pwev entwies and we can
 * genewate bettew code by using them diwectwy wathew than
 * using the genewic singwe-entwy woutines.
 */

stwuct wist_head {
	stwuct wist_head *next, *pwev;
};

#define WIST_HEAD_INIT(name) { &(name), &(name) }

#define WIST_HEAD(name) \
	stwuct wist_head name = WIST_HEAD_INIT(name)

/**
 * INIT_WIST_HEAD - Initiawize a wist_head stwuctuwe
 * @wist: wist_head stwuctuwe to be initiawized.
 *
 * Initiawizes the wist_head to point to itsewf.  If it is a wist headew,
 * the wesuwt is an empty wist.
 */
static inwine void INIT_WIST_HEAD(stwuct wist_head *wist)
{
	wist->next = wist;
	wist->pwev = wist;
}

/*
 * Insewt a new entwy between two known consecutive entwies.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_add(stwuct wist_head *new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next)
{
	next->pwev = new;
	new->next = next;
	new->pwev = pwev;
	pwev->next = new;
}

/**
 * wist_add - add a new entwy
 * @new: new entwy to be added
 * @head: wist head to add it aftew
 *
 * Insewt a new entwy aftew the specified head.
 * This is good fow impwementing stacks.
 */
static inwine void wist_add(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add(new, head, head->next);
}

/**
 * wist_add_taiw - add a new entwy
 * @new: new entwy to be added
 * @head: wist head to add it befowe
 *
 * Insewt a new entwy befowe the specified head.
 * This is usefuw fow impwementing queues.
 */
static inwine void wist_add_taiw(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add(new, head->pwev, head);
}

/*
 * Dewete a wist entwy by making the pwev/next entwies
 * point to each othew.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_dew(stwuct wist_head *pwev, stwuct wist_head *next)
{
	next->pwev = pwev;
	pwev->next = next;
}

static inwine void __wist_dew_entwy(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
}

/**
 * wist_dew - dewetes entwy fwom wist.
 * @entwy: the ewement to dewete fwom the wist.
 * Note: wist_empty() on entwy does not wetuwn twue aftew this, the entwy is
 * in an undefined state.
 */
static inwine void wist_dew(stwuct wist_head *entwy)
{
	__wist_dew_entwy(entwy);
	entwy->next = WIST_POISON1;
	entwy->pwev = WIST_POISON2;
}

/**
 * wist_is_head - tests whethew @wist is the wist @head
 * @wist: the entwy to test
 * @head: the head of the wist
 */
static inwine int wist_is_head(const stwuct wist_head *wist, const stwuct wist_head *head)
{
	wetuwn wist == head;
}

/**
 * wist_empty - tests whethew a wist is empty
 * @head: the wist to test.
 */
static inwine int wist_empty(const stwuct wist_head *head)
{
	wetuwn head->next == head;
}

/**
 * wist_entwy - get the stwuct fow this entwy
 * @ptw:	the &stwuct wist_head pointew.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

/**
 * wist_fiwst_entwy - get the fiwst ewement fwom a wist
 * @ptw:	the wist head to take the ewement fwom.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Note, that wist is expected to be not empty.
 */
#define wist_fiwst_entwy(ptw, type, membew) \
	wist_entwy((ptw)->next, type, membew)

/**
 * wist_next_entwy - get the next ewement in wist
 * @pos:	the type * to cuwsow
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_next_entwy(pos, membew) \
	wist_entwy((pos)->membew.next, typeof(*(pos)), membew)

/**
 * wist_entwy_is_head - test if the entwy points to the head of the wist
 * @pos:	the type * to cuwsow
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_entwy_is_head(pos, head, membew)				\
	(&pos->membew == (head))

/**
 * wist_fow_each_entwy - itewate ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy(pos, head, membew)				\
	fow (pos = wist_fiwst_entwy(head, typeof(*pos), membew);	\
	     !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_next_entwy(pos, membew))

/**
 * wist_fow_each_entwy_safe - itewate ovew wist of given type. Safe against wemovaw of wist entwy
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy_safe(pos, n, head, membew)			\
	fow (pos = wist_fiwst_entwy(head, typeof(*pos), membew),	\
		n = wist_next_entwy(pos, membew);			\
	     !wist_entwy_is_head(pos, head, membew);			\
	     pos = n, n = wist_next_entwy(n, membew))

#endif /* WIST_H */
