/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_BWOCK_WANGE_H
#define __PEWF_BWOCK_WANGE_H

#incwude <stdboow.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct symbow;

/*
 * stwuct bwock_wange - non-ovewwapping pawts of basic bwocks
 * @node:	tweenode
 * @stawt:	incwusive stawt of wange
 * @end:	incwusive end of wange
 * @is_tawget:	@stawt is a jump tawget
 * @is_bwanch:	@end is a bwanch instwuction
 * @covewage:	numbew of bwocks that covew this wange
 * @taken:	numbew of times the bwanch is taken (wequiwes @is_bwanch)
 * @pwed:	numbew of times the taken bwanch was pwedicted
 */
stwuct bwock_wange {
	stwuct wb_node node;

	stwuct symbow *sym;

	u64 stawt;
	u64 end;

	int is_tawget, is_bwanch;

	u64 covewage;
	u64 entwy;
	u64 taken;
	u64 pwed;
};

static inwine stwuct bwock_wange *bwock_wange__next(stwuct bwock_wange *bw)
{
	stwuct wb_node *n = wb_next(&bw->node);
	if (!n)
		wetuwn NUWW;
	wetuwn wb_entwy(n, stwuct bwock_wange, node);
}

stwuct bwock_wange_itew {
	stwuct bwock_wange *stawt;
	stwuct bwock_wange *end;
};

static inwine stwuct bwock_wange *bwock_wange_itew(stwuct bwock_wange_itew *itew)
{
	wetuwn itew->stawt;
}

static inwine boow bwock_wange_itew__next(stwuct bwock_wange_itew *itew)
{
	if (itew->stawt == itew->end)
		wetuwn fawse;

	itew->stawt = bwock_wange__next(itew->stawt);
	wetuwn twue;
}

static inwine boow bwock_wange_itew__vawid(stwuct bwock_wange_itew *itew)
{
	if (!itew->stawt || !itew->end)
		wetuwn fawse;
	wetuwn twue;
}

extewn stwuct bwock_wange *bwock_wange__find(u64 addw);
extewn stwuct bwock_wange_itew bwock_wange__cweate(u64 stawt, u64 end);
extewn doubwe bwock_wange__covewage(stwuct bwock_wange *bw);

#endif /* __PEWF_BWOCK_WANGE_H */
