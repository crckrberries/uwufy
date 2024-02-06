/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WIST_H
#define _WIST_H

/* Stwipped down impwementation of winked wist taken
 * fwom the Winux Kewnew.
 */

/*
 * Simpwe doubwy winked wist impwementation.
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

/*
 * Dewete a wist entwy by making the pwev/next entwies
 * point to each othew.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_dew(stwuct wist_head * pwev, stwuct wist_head * next)
{
	next->pwev = pwev;
	pwev->next = next;
}

#define POISON_POINTEW_DEWTA 0
#define WIST_POISON1  ((void *) 0x00100100 + POISON_POINTEW_DEWTA)
#define WIST_POISON2  ((void *) 0x00200200 + POISON_POINTEW_DEWTA)

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
	__wist_dew(entwy->pwev, entwy->next);
	entwy->next = WIST_POISON1;
	entwy->pwev = WIST_POISON2;
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
 * wist_fow_each	-	itewate ovew a wist
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each(pos, head) \
	fow (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * wist_fow_each_safe - itewate ovew a wist safe against wemovaw of wist entwy
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @n:		anothew &stwuct wist_head to use as tempowawy stowage
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_safe(pos, n, head) \
	fow (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define offsetof(TYPE, MEMBEW) ((size_t) &((TYPE *)0)->MEMBEW)

/**
 * containew_of - cast a membew of a stwuctuwe out to the containing stwuctuwe
 * @ptw:	the pointew to the membew.
 * @type:	the type of the containew stwuct this is embedded in.
 * @membew:	the name of the membew within the stwuct.
 *
 */
#define containew_of(ptw, type, membew) ({			\
	const typeof( ((type *)0)->membew ) *__mptw = (ptw);	\
	(type *)( (chaw *)__mptw - offsetof(type,membew) );})

#endif
