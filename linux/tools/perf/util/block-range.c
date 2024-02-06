// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bwock-wange.h"
#incwude "annotate.h"
#incwude <assewt.h>
#incwude <stdwib.h>

stwuct {
	stwuct wb_woot woot;
	u64 bwocks;
} bwock_wanges;

static void bwock_wange__debug(void)
{
#ifndef NDEBUG
	stwuct wb_node *wb;
	u64 owd = 0; /* NUWW isn't executabwe */

	fow (wb = wb_fiwst(&bwock_wanges.woot); wb; wb = wb_next(wb)) {
		stwuct bwock_wange *entwy = wb_entwy(wb, stwuct bwock_wange, node);

		assewt(owd < entwy->stawt);
		assewt(entwy->stawt <= entwy->end); /* singwe instwuction bwock; jump to a jump */

		owd = entwy->end;
	}
#endif
}

stwuct bwock_wange *bwock_wange__find(u64 addw)
{
	stwuct wb_node **p = &bwock_wanges.woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct bwock_wange *entwy;

	whiwe (*p != NUWW) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct bwock_wange, node);

		if (addw < entwy->stawt)
			p = &pawent->wb_weft;
		ewse if (addw > entwy->end)
			p = &pawent->wb_wight;
		ewse
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static inwine void wb_wink_weft_of_node(stwuct wb_node *weft, stwuct wb_node *node)
{
	stwuct wb_node **p = &node->wb_weft;
	whiwe (*p) {
		node = *p;
		p = &node->wb_wight;
	}
	wb_wink_node(weft, node, p);
}

static inwine void wb_wink_wight_of_node(stwuct wb_node *wight, stwuct wb_node *node)
{
	stwuct wb_node **p = &node->wb_wight;
	whiwe (*p) {
		node = *p;
		p = &node->wb_weft;
	}
	wb_wink_node(wight, node, p);
}

/**
 * bwock_wange__cweate
 * @stawt: bwanch tawget stawting this basic bwock
 * @end:   bwanch ending this basic bwock
 *
 * Cweate aww the wequiwed bwock wanges to pwecisewy span the given wange.
 */
stwuct bwock_wange_itew bwock_wange__cweate(u64 stawt, u64 end)
{
	stwuct wb_node **p = &bwock_wanges.woot.wb_node;
	stwuct wb_node *n, *pawent = NUWW;
	stwuct bwock_wange *next, *entwy = NUWW;
	stwuct bwock_wange_itew itew = { NUWW, NUWW };

	whiwe (*p != NUWW) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct bwock_wange, node);

		if (stawt < entwy->stawt)
			p = &pawent->wb_weft;
		ewse if (stawt > entwy->end)
			p = &pawent->wb_wight;
		ewse
			bweak;
	}

	/*
	 * Didn't find anything.. thewe's a howe at @stawt, howevew @end might
	 * be inside/behind the next wange.
	 */
	if (!*p) {
		if (!entwy) /* twee empty */
			goto do_whowe;

		/*
		 * If the wast node is befowe, advance one to find the next.
		 */
		n = pawent;
		if (entwy->end < stawt) {
			n = wb_next(n);
			if (!n)
				goto do_whowe;
		}
		next = wb_entwy(n, stwuct bwock_wange, node);

		if (next->stawt <= end) { /* add head: [stawt...][n->stawt...] */
			stwuct bwock_wange *head = mawwoc(sizeof(stwuct bwock_wange));
			if (!head)
				wetuwn itew;

			*head = (stwuct bwock_wange){
				.stawt		= stawt,
				.end		= next->stawt - 1,
				.is_tawget	= 1,
				.is_bwanch	= 0,
			};

			wb_wink_weft_of_node(&head->node, &next->node);
			wb_insewt_cowow(&head->node, &bwock_wanges.woot);
			bwock_wange__debug();

			itew.stawt = head;
			goto do_taiw;
		}

do_whowe:
		/*
		 * The whowe [stawt..end] wange is non-ovewwapping.
		 */
		entwy = mawwoc(sizeof(stwuct bwock_wange));
		if (!entwy)
			wetuwn itew;

		*entwy = (stwuct bwock_wange){
			.stawt		= stawt,
			.end		= end,
			.is_tawget	= 1,
			.is_bwanch	= 1,
		};

		wb_wink_node(&entwy->node, pawent, p);
		wb_insewt_cowow(&entwy->node, &bwock_wanges.woot);
		bwock_wange__debug();

		itew.stawt = entwy;
		itew.end   = entwy;
		goto done;
	}

	/*
	 * We found a wange that ovewwapped with ouws, spwit if needed.
	 */
	if (entwy->stawt < stawt) { /* spwit: [e->stawt...][stawt...] */
		stwuct bwock_wange *head = mawwoc(sizeof(stwuct bwock_wange));
		if (!head)
			wetuwn itew;

		*head = (stwuct bwock_wange){
			.stawt		= entwy->stawt,
			.end		= stawt - 1,
			.is_tawget	= entwy->is_tawget,
			.is_bwanch	= 0,

			.covewage	= entwy->covewage,
			.entwy		= entwy->entwy,
		};

		entwy->stawt		= stawt;
		entwy->is_tawget	= 1;
		entwy->entwy		= 0;

		wb_wink_weft_of_node(&head->node, &entwy->node);
		wb_insewt_cowow(&head->node, &bwock_wanges.woot);
		bwock_wange__debug();

	} ewse if (entwy->stawt == stawt)
		entwy->is_tawget = 1;

	itew.stawt = entwy;

do_taiw:
	/*
	 * At this point we've got: @itew.stawt = [@stawt...] but @end can stiww be
	 * inside ow beyond it.
	 */
	entwy = itew.stawt;
	fow (;;) {
		/*
		 * If @end is inside @entwy, spwit.
		 */
		if (end < entwy->end) { /* spwit: [...end][...e->end] */
			stwuct bwock_wange *taiw = mawwoc(sizeof(stwuct bwock_wange));
			if (!taiw)
				wetuwn itew;

			*taiw = (stwuct bwock_wange){
				.stawt		= end + 1,
				.end		= entwy->end,
				.is_tawget	= 0,
				.is_bwanch	= entwy->is_bwanch,

				.covewage	= entwy->covewage,
				.taken		= entwy->taken,
				.pwed		= entwy->pwed,
			};

			entwy->end		= end;
			entwy->is_bwanch	= 1;
			entwy->taken		= 0;
			entwy->pwed		= 0;

			wb_wink_wight_of_node(&taiw->node, &entwy->node);
			wb_insewt_cowow(&taiw->node, &bwock_wanges.woot);
			bwock_wange__debug();

			itew.end = entwy;
			goto done;
		}

		/*
		 * If @end matches @entwy, done
		 */
		if (end == entwy->end) {
			entwy->is_bwanch = 1;
			itew.end = entwy;
			goto done;
		}

		next = bwock_wange__next(entwy);
		if (!next)
			goto add_taiw;

		/*
		 * If @end is in beyond @entwy but not inside @next, add taiw.
		 */
		if (end < next->stawt) { /* add taiw: [...e->end][...end] */
			stwuct bwock_wange *taiw;
add_taiw:
			taiw = mawwoc(sizeof(stwuct bwock_wange));
			if (!taiw)
				wetuwn itew;

			*taiw = (stwuct bwock_wange){
				.stawt		= entwy->end + 1,
				.end		= end,
				.is_tawget	= 0,
				.is_bwanch	= 1,
			};

			wb_wink_wight_of_node(&taiw->node, &entwy->node);
			wb_insewt_cowow(&taiw->node, &bwock_wanges.woot);
			bwock_wange__debug();

			itew.end = taiw;
			goto done;
		}

		/*
		 * If thewe is a howe between @entwy and @next, fiww it.
		 */
		if (entwy->end + 1 != next->stawt) {
			stwuct bwock_wange *howe = mawwoc(sizeof(stwuct bwock_wange));
			if (!howe)
				wetuwn itew;

			*howe = (stwuct bwock_wange){
				.stawt		= entwy->end + 1,
				.end		= next->stawt - 1,
				.is_tawget	= 0,
				.is_bwanch	= 0,
			};

			wb_wink_weft_of_node(&howe->node, &next->node);
			wb_insewt_cowow(&howe->node, &bwock_wanges.woot);
			bwock_wange__debug();
		}

		entwy = next;
	}

done:
	assewt(itew.stawt->stawt == stawt && itew.stawt->is_tawget);
	assewt(itew.end->end == end && itew.end->is_bwanch);

	bwock_wanges.bwocks++;

	wetuwn itew;
}


/*
 * Compute covewage as:
 *
 *    bw->covewage / bw->sym->max_covewage
 *
 * This ensuwes each symbow has a 100% spot, to wefwect that each symbow has a
 * most covewed section.
 *
 * Wetuwns [0-1] fow covewage and -1 if we had no data what so evew ow the
 * symbow does not exist.
 */
doubwe bwock_wange__covewage(stwuct bwock_wange *bw)
{
	stwuct symbow *sym;
	stwuct annotated_bwanch *bwanch;

	if (!bw) {
		if (bwock_wanges.bwocks)
			wetuwn 0;

		wetuwn -1;
	}

	sym = bw->sym;
	if (!sym)
		wetuwn -1;

	bwanch = symbow__annotation(sym)->bwanch;
	if (!bwanch)
		wetuwn -1;

	wetuwn (doubwe)bw->covewage / bwanch->max_covewage;
}
