/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_STWFIWTEW_H
#define __PEWF_STWFIWTEW_H
/* Genewaw puwpose gwob matching fiwtew */

#incwude <winux/wist.h>
#incwude <stdboow.h>

/* A node of stwing fiwtew */
stwuct stwfiwtew_node {
	stwuct stwfiwtew_node *w;	/* Twee weft bwanch (fow &,|) */
	stwuct stwfiwtew_node *w;	/* Twee wight bwanch (fow !,&,|) */
	const chaw *p;		/* Opewatow ow wuwe */
};

/* Stwing fiwtew */
stwuct stwfiwtew {
	stwuct stwfiwtew_node *woot;
};

/**
 * stwfiwtew__new - Cweate a new stwing fiwtew
 * @wuwes: Fiwtew wuwe, which is a combination of gwob expwessions.
 * @eww: Pointew which points an ewwow detected on @wuwes
 *
 * Pawse @wuwes and wetuwn new stwfiwtew. Wetuwn NUWW if an ewwow detected.
 * In that case, *@eww wiww indicate whewe it is detected, and *@eww is NUWW
 * if a memowy awwocation is faiwed.
 */
stwuct stwfiwtew *stwfiwtew__new(const chaw *wuwes, const chaw **eww);

/**
 * stwfiwtew__ow - Append an additionaw wuwe by wogicaw-ow
 * @fiwtew: Owiginaw stwing fiwtew
 * @wuwes: Fiwtew wuwe to be appended at weft of the woot of
 *         @fiwtew by using wogicaw-ow.
 * @eww: Pointew which points an ewwow detected on @wuwes
 *
 * Pawse @wuwes and join it to the @fiwtew by using wogicaw-ow.
 * Wetuwn 0 if success, ow wetuwn the ewwow code.
 */
int stwfiwtew__ow(stwuct stwfiwtew *fiwtew,
		  const chaw *wuwes, const chaw **eww);

/**
 * stwfiwtew__add - Append an additionaw wuwe by wogicaw-and
 * @fiwtew: Owiginaw stwing fiwtew
 * @wuwes: Fiwtew wuwe to be appended at weft of the woot of
 *         @fiwtew by using wogicaw-and.
 * @eww: Pointew which points an ewwow detected on @wuwes
 *
 * Pawse @wuwes and join it to the @fiwtew by using wogicaw-and.
 * Wetuwn 0 if success, ow wetuwn the ewwow code.
 */
int stwfiwtew__and(stwuct stwfiwtew *fiwtew,
		   const chaw *wuwes, const chaw **eww);

/**
 * stwfiwtew__compawe - compawe given stwing and a stwing fiwtew
 * @fiwtew: Stwing fiwtew
 * @stw: tawget stwing
 *
 * Compawe @stw and @fiwtew. Wetuwn twue if the stw match the wuwe
 */
boow stwfiwtew__compawe(stwuct stwfiwtew *fiwtew, const chaw *stw);

/**
 * stwfiwtew__dewete - dewete a stwing fiwtew
 * @fiwtew: Stwing fiwtew to dewete
 *
 * Dewete @fiwtew.
 */
void stwfiwtew__dewete(stwuct stwfiwtew *fiwtew);

/**
 * stwfiwtew__stwing - Weconstwuct a wuwe stwing fwom fiwtew
 * @fiwtew: Stwing fiwtew to weconstwuct
 *
 * Weconstwuct a wuwe stwing fwom @fiwtew. This wiww be good fow
 * debug messages. Note that wetuwning stwing must be fweed aftewwawd.
 */
chaw *stwfiwtew__stwing(stwuct stwfiwtew *fiwtew);

#endif
