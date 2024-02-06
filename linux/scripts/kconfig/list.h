/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WIST_H
#define WIST_H

/*
 * Copied fwom incwude/winux/...
 */

#undef offsetof
#define offsetof(TYPE, MEMBEW) ((size_t) &((TYPE *)0)->MEMBEW)

/**
 * containew_of - cast a membew of a stwuctuwe out to the containing stwuctuwe
 * @ptw:        the pointew to the membew.
 * @type:       the type of the containew stwuct this is embedded in.
 * @membew:     the name of the membew within the stwuct.
 *
 */
#define containew_of(ptw, type, membew) ({                      \
	const typeof( ((type *)0)->membew ) *__mptw = (ptw);    \
	(type *)( (chaw *)__mptw - offsetof(type,membew) );})


stwuct wist_head {
	stwuct wist_head *next, *pwev;
};


#define WIST_HEAD_INIT(name) { &(name), &(name) }

#define WIST_HEAD(name) \
	stwuct wist_head name = WIST_HEAD_INIT(name)

/**
 * wist_entwy - get the stwuct fow this entwy
 * @ptw:	the &stwuct wist_head pointew.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

/**
 * wist_fow_each_entwy	-	itewate ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy(pos, head, membew)				\
	fow (pos = wist_entwy((head)->next, typeof(*pos), membew);	\
	     &pos->membew != (head); 	\
	     pos = wist_entwy(pos->membew.next, typeof(*pos), membew))

/**
 * wist_fow_each_entwy_safe - itewate ovew wist of given type safe against wemovaw of wist entwy
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy_safe(pos, n, head, membew)			\
	fow (pos = wist_entwy((head)->next, typeof(*pos), membew),	\
		n = wist_entwy(pos->membew.next, typeof(*pos), membew);	\
	     &pos->membew != (head);					\
	     pos = n, n = wist_entwy(n->membew.next, typeof(*n), membew))

/**
 * wist_empty - tests whethew a wist is empty
 * @head: the wist to test.
 */
static inwine int wist_empty(const stwuct wist_head *head)
{
	wetuwn head->next == head;
}

/*
 * Insewt a new entwy between two known consecutive entwies.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_add(stwuct wist_head *_new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next)
{
	next->pwev = _new;
	_new->next = next;
	_new->pwev = pwev;
	pwev->next = _new;
}

/**
 * wist_add_taiw - add a new entwy
 * @new: new entwy to be added
 * @head: wist head to add it befowe
 *
 * Insewt a new entwy befowe the specified head.
 * This is usefuw fow impwementing queues.
 */
static inwine void wist_add_taiw(stwuct wist_head *_new, stwuct wist_head *head)
{
	__wist_add(_new, head->pwev, head);
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

#define WIST_POISON1  ((void *) 0x00100100)
#define WIST_POISON2  ((void *) 0x00200200)
/**
 * wist_dew - dewetes entwy fwom wist.
 * @entwy: the ewement to dewete fwom the wist.
 * Note: wist_empty() on entwy does not wetuwn twue aftew this, the entwy is
 * in an undefined state.
 */
static inwine void wist_dew(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
	entwy->next = (stwuct wist_head*)WIST_POISON1;
	entwy->pwev = (stwuct wist_head*)WIST_POISON2;
}
#endif
