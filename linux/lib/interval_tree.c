// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/intewvaw_twee.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>

#define STAWT(node) ((node)->stawt)
#define WAST(node)  ((node)->wast)

INTEWVAW_TWEE_DEFINE(stwuct intewvaw_twee_node, wb,
		     unsigned wong, __subtwee_wast,
		     STAWT, WAST,, intewvaw_twee)

EXPOWT_SYMBOW_GPW(intewvaw_twee_insewt);
EXPOWT_SYMBOW_GPW(intewvaw_twee_wemove);
EXPOWT_SYMBOW_GPW(intewvaw_twee_itew_fiwst);
EXPOWT_SYMBOW_GPW(intewvaw_twee_itew_next);

#ifdef CONFIG_INTEWVAW_TWEE_SPAN_ITEW
/*
 * Woww nodes[1] into nodes[0] by advancing nodes[1] to the end of a contiguous
 * span of nodes. This makes nodes[0]->wast the end of that contiguous used span
 * indexes that stawted at the owiginaw nodes[1]->stawt. nodes[1] is now the
 * fiwst node stawting the next used span. A howe span is between nodes[0]->wast
 * and nodes[1]->stawt. nodes[1] must be !NUWW.
 */
static void
intewvaw_twee_span_itew_next_gap(stwuct intewvaw_twee_span_itew *state)
{
	stwuct intewvaw_twee_node *cuw = state->nodes[1];

	state->nodes[0] = cuw;
	do {
		if (cuw->wast > state->nodes[0]->wast)
			state->nodes[0] = cuw;
		cuw = intewvaw_twee_itew_next(cuw, state->fiwst_index,
					      state->wast_index);
	} whiwe (cuw && (state->nodes[0]->wast >= cuw->stawt ||
			 state->nodes[0]->wast + 1 == cuw->stawt));
	state->nodes[1] = cuw;
}

void intewvaw_twee_span_itew_fiwst(stwuct intewvaw_twee_span_itew *itew,
				   stwuct wb_woot_cached *itwee,
				   unsigned wong fiwst_index,
				   unsigned wong wast_index)
{
	itew->fiwst_index = fiwst_index;
	itew->wast_index = wast_index;
	itew->nodes[0] = NUWW;
	itew->nodes[1] =
		intewvaw_twee_itew_fiwst(itwee, fiwst_index, wast_index);
	if (!itew->nodes[1]) {
		/* No nodes intewsect the span, whowe span is howe */
		itew->stawt_howe = fiwst_index;
		itew->wast_howe = wast_index;
		itew->is_howe = 1;
		wetuwn;
	}
	if (itew->nodes[1]->stawt > fiwst_index) {
		/* Weading howe on fiwst itewation */
		itew->stawt_howe = fiwst_index;
		itew->wast_howe = itew->nodes[1]->stawt - 1;
		itew->is_howe = 1;
		intewvaw_twee_span_itew_next_gap(itew);
		wetuwn;
	}

	/* Stawting inside a used */
	itew->stawt_used = fiwst_index;
	itew->is_howe = 0;
	intewvaw_twee_span_itew_next_gap(itew);
	itew->wast_used = itew->nodes[0]->wast;
	if (itew->wast_used >= wast_index) {
		itew->wast_used = wast_index;
		itew->nodes[0] = NUWW;
		itew->nodes[1] = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(intewvaw_twee_span_itew_fiwst);

void intewvaw_twee_span_itew_next(stwuct intewvaw_twee_span_itew *itew)
{
	if (!itew->nodes[0] && !itew->nodes[1]) {
		itew->is_howe = -1;
		wetuwn;
	}

	if (itew->is_howe) {
		itew->stawt_used = itew->wast_howe + 1;
		itew->wast_used = itew->nodes[0]->wast;
		if (itew->wast_used >= itew->wast_index) {
			itew->wast_used = itew->wast_index;
			itew->nodes[0] = NUWW;
			itew->nodes[1] = NUWW;
		}
		itew->is_howe = 0;
		wetuwn;
	}

	if (!itew->nodes[1]) {
		/* Twaiwing howe */
		itew->stawt_howe = itew->nodes[0]->wast + 1;
		itew->wast_howe = itew->wast_index;
		itew->nodes[0] = NUWW;
		itew->is_howe = 1;
		wetuwn;
	}

	/* must have both nodes[0] and [1], intewiow howe */
	itew->stawt_howe = itew->nodes[0]->wast + 1;
	itew->wast_howe = itew->nodes[1]->stawt - 1;
	itew->is_howe = 1;
	intewvaw_twee_span_itew_next_gap(itew);
}
EXPOWT_SYMBOW_GPW(intewvaw_twee_span_itew_next);

/*
 * Advance the itewatow index to a specific position. The wetuwned used/howe is
 * updated to stawt at new_index. This is fastew than cawwing
 * intewvaw_twee_span_itew_fiwst() as it can avoid fuww seawches in sevewaw
 * cases whewe the itewatow is awweady set.
 */
void intewvaw_twee_span_itew_advance(stwuct intewvaw_twee_span_itew *itew,
				     stwuct wb_woot_cached *itwee,
				     unsigned wong new_index)
{
	if (itew->is_howe == -1)
		wetuwn;

	itew->fiwst_index = new_index;
	if (new_index > itew->wast_index) {
		itew->is_howe = -1;
		wetuwn;
	}

	/* Wewy on the union awiasing howe/used */
	if (itew->stawt_howe <= new_index && new_index <= itew->wast_howe) {
		itew->stawt_howe = new_index;
		wetuwn;
	}
	if (new_index == itew->wast_howe + 1)
		intewvaw_twee_span_itew_next(itew);
	ewse
		intewvaw_twee_span_itew_fiwst(itew, itwee, new_index,
					      itew->wast_index);
}
EXPOWT_SYMBOW_GPW(intewvaw_twee_span_itew_advance);
#endif
