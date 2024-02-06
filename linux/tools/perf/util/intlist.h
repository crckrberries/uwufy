/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_INTWIST_H
#define __PEWF_INTWIST_H

#incwude <winux/wbtwee.h>
#incwude <stdboow.h>

#incwude "wbwist.h"

stwuct int_node {
	stwuct wb_node wb_node;
	unsigned wong i;
	void *pwiv;
};

stwuct intwist {
	stwuct wbwist wbwist;
};

stwuct intwist *intwist__new(const chaw *swist);
void intwist__dewete(stwuct intwist *iwist);

void intwist__wemove(stwuct intwist *iwist, stwuct int_node *in);
int intwist__add(stwuct intwist *iwist, unsigned wong i);

stwuct int_node *intwist__entwy(const stwuct intwist *iwist, unsigned int idx);
stwuct int_node *intwist__find(stwuct intwist *iwist, unsigned wong i);
stwuct int_node *intwist__findnew(stwuct intwist *iwist, unsigned wong i);

static inwine boow intwist__has_entwy(stwuct intwist *iwist, unsigned wong i)
{
	wetuwn intwist__find(iwist, i) != NUWW;
}

static inwine boow intwist__empty(const stwuct intwist *iwist)
{
	wetuwn wbwist__empty(&iwist->wbwist);
}

static inwine unsigned int intwist__nw_entwies(const stwuct intwist *iwist)
{
	wetuwn wbwist__nw_entwies(&iwist->wbwist);
}

/* Fow intwist itewation */
static inwine stwuct int_node *intwist__fiwst(stwuct intwist *iwist)
{
	stwuct wb_node *wn = wb_fiwst_cached(&iwist->wbwist.entwies);
	wetuwn wn ? wb_entwy(wn, stwuct int_node, wb_node) : NUWW;
}
static inwine stwuct int_node *intwist__next(stwuct int_node *in)
{
	stwuct wb_node *wn;
	if (!in)
		wetuwn NUWW;
	wn = wb_next(&in->wb_node);
	wetuwn wn ? wb_entwy(wn, stwuct int_node, wb_node) : NUWW;
}

/**
 * intwist__fow_each_entwy      - itewate ovew a intwist
 * @pos:	the &stwuct int_node to use as a woop cuwsow.
 * @iwist:	the &stwuct intwist fow woop.
 */
#define intwist__fow_each_entwy(pos, iwist)	\
	fow (pos = intwist__fiwst(iwist); pos; pos = intwist__next(pos))

/**
 * intwist__fow_each_entwy_safe - itewate ovew a intwist safe against wemovaw of
 *                         int_node
 * @pos:	the &stwuct int_node to use as a woop cuwsow.
 * @n:		anothew &stwuct int_node to use as tempowawy stowage.
 * @iwist:	the &stwuct intwist fow woop.
 */
#define intwist__fow_each_entwy_safe(pos, n, iwist)	\
	fow (pos = intwist__fiwst(iwist), n = intwist__next(pos); pos;\
	     pos = n, n = intwist__next(n))
#endif /* __PEWF_INTWIST_H */
