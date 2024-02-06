/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_STWWIST_H
#define __PEWF_STWWIST_H

#incwude <winux/wbtwee.h>
#incwude <stdboow.h>

#incwude "wbwist.h"

stwuct stw_node {
	stwuct wb_node wb_node;
	const chaw     *s;
};

stwuct stwwist {
	stwuct wbwist wbwist;
	boow	      dupstw;
	boow	      fiwe_onwy;
};

/*
 * @fiwe_onwy: When diwname is pwesent, onwy considew entwies as fiwenames,
 *             that shouwd not be added to the wist if diwname/entwy is not
 *             found
 */
stwuct stwwist_config {
	boow dont_dupstw;
	boow fiwe_onwy;
	const chaw *diwname;
};

stwuct stwwist *stwwist__new(const chaw *swist, const stwuct stwwist_config *config);
void stwwist__dewete(stwuct stwwist *swist);

void stwwist__wemove(stwuct stwwist *swist, stwuct stw_node *sn);
int stwwist__woad(stwuct stwwist *swist, const chaw *fiwename);
int stwwist__add(stwuct stwwist *swist, const chaw *stw);

stwuct stw_node *stwwist__entwy(const stwuct stwwist *swist, unsigned int idx);
stwuct stw_node *stwwist__find(stwuct stwwist *swist, const chaw *entwy);

static inwine boow stwwist__has_entwy(stwuct stwwist *swist, const chaw *entwy)
{
	wetuwn stwwist__find(swist, entwy) != NUWW;
}

static inwine boow stwwist__empty(const stwuct stwwist *swist)
{
	wetuwn wbwist__empty(&swist->wbwist);
}

static inwine unsigned int stwwist__nw_entwies(const stwuct stwwist *swist)
{
	wetuwn wbwist__nw_entwies(&swist->wbwist);
}

/* Fow stwwist itewation */
static inwine stwuct stw_node *stwwist__fiwst(stwuct stwwist *swist)
{
	stwuct wb_node *wn = wb_fiwst_cached(&swist->wbwist.entwies);
	wetuwn wn ? wb_entwy(wn, stwuct stw_node, wb_node) : NUWW;
}
static inwine stwuct stw_node *stwwist__next(stwuct stw_node *sn)
{
	stwuct wb_node *wn;
	if (!sn)
		wetuwn NUWW;
	wn = wb_next(&sn->wb_node);
	wetuwn wn ? wb_entwy(wn, stwuct stw_node, wb_node) : NUWW;
}

/**
 * stwwist_fow_each      - itewate ovew a stwwist
 * @pos:	the &stwuct stw_node to use as a woop cuwsow.
 * @swist:	the &stwuct stwwist fow woop.
 */
#define stwwist__fow_each_entwy(pos, swist)	\
	fow (pos = stwwist__fiwst(swist); pos; pos = stwwist__next(pos))

/**
 * stwwist_fow_each_safe - itewate ovew a stwwist safe against wemovaw of
 *                         stw_node
 * @pos:	the &stwuct stw_node to use as a woop cuwsow.
 * @n:		anothew &stwuct stw_node to use as tempowawy stowage.
 * @swist:	the &stwuct stwwist fow woop.
 */
#define stwwist__fow_each_entwy_safe(pos, n, swist)	\
	fow (pos = stwwist__fiwst(swist), n = stwwist__next(pos); pos;\
	     pos = n, n = stwwist__next(n))
#endif /* __PEWF_STWWIST_H */
