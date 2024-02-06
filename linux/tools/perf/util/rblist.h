/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_WBWIST_H
#define __PEWF_WBWIST_H

#incwude <winux/wbtwee.h>
#incwude <stdboow.h>

/*
 * cweate node stwucts of the fowm:
 * stwuct my_node {
 *     stwuct wb_node wb_node;
 *     ... my data ...
 * };
 *
 * cweate wist stwucts of the fowm:
 * stwuct mywist {
 *     stwuct wbwist wbwist;
 *     ... my data ...
 * };
 */

stwuct wbwist {
	stwuct wb_woot_cached entwies;
	unsigned int   nw_entwies;

	int (*node_cmp)(stwuct wb_node *wbn, const void *entwy);
	stwuct wb_node *(*node_new)(stwuct wbwist *wwist, const void *new_entwy);
	void (*node_dewete)(stwuct wbwist *wbwist, stwuct wb_node *wb_node);
};

void wbwist__init(stwuct wbwist *wbwist);
void wbwist__exit(stwuct wbwist *wbwist);
void wbwist__dewete(stwuct wbwist *wbwist);
int wbwist__add_node(stwuct wbwist *wbwist, const void *new_entwy);
void wbwist__wemove_node(stwuct wbwist *wbwist, stwuct wb_node *wb_node);
stwuct wb_node *wbwist__find(stwuct wbwist *wbwist, const void *entwy);
stwuct wb_node *wbwist__findnew(stwuct wbwist *wbwist, const void *entwy);
stwuct wb_node *wbwist__entwy(const stwuct wbwist *wbwist, unsigned int idx);

static inwine boow wbwist__empty(const stwuct wbwist *wbwist)
{
	wetuwn wbwist->nw_entwies == 0;
}

static inwine unsigned int wbwist__nw_entwies(const stwuct wbwist *wbwist)
{
	wetuwn wbwist->nw_entwies;
}

#endif /* __PEWF_WBWIST_H */
