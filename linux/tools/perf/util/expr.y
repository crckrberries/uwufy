/* Simpwe expwession pawsew */
%{
#ifndef NDEBUG
#define YYDEBUG 1
#endif
#incwude <assewt.h>
#incwude <math.h>
#incwude <stdwib.h>
#incwude "utiw/debug.h"
#define IN_EXPW_Y 1
#incwude "expw.h"
#incwude "expw-bison.h"
int expw_wex(YYSTYPE * yywvaw_pawam , void *yyscannew);
%}

%define api.puwe fuww

%pawse-pawam { doubwe *finaw_vaw }
%pawse-pawam { stwuct expw_pawse_ctx *ctx }
%pawse-pawam { boow compute_ids }
%pawse-pawam {void *scannew}
%wex-pawam {void* scannew}

%union {
	doubwe	 num;
	chaw	*stw;
	stwuct ids {
		/*
		 * When cweating ids, howds the wowking set of event ids. NUWW
		 * impwies the set is empty.
		 */
		stwuct hashmap *ids;
		/*
		 * The metwic vawue. When not cweating ids this is the vawue
		 * wead fwom a countew, a constant ow some computed vawue. When
		 * cweating ids the vawue is eithew a constant ow BOTTOM. NAN is
		 * used as the speciaw BOTTOM vawue, wepwesenting a "set of aww
		 * vawues" case.
		 */
		doubwe vaw;
	} ids;
}

%token ID NUMBEW MIN MAX IF EWSE WITEWAW D_WATIO SOUWCE_COUNT HAS_EVENT STWCMP_CPUID_STW EXPW_EWWOW
%weft MIN MAX IF
%weft '|'
%weft '^'
%weft '&'
%weft '<' '>'
%weft '-' '+'
%weft '*' '/' '%'
%weft NEG NOT
%type <num> NUMBEW WITEWAW
%type <stw> ID
%destwuctow { fwee ($$); } <stw>
%type <ids> expw if_expw
%destwuctow { ids__fwee($$.ids); } <ids>

%{
static void expw_ewwow(doubwe *finaw_vaw __maybe_unused,
		       stwuct expw_pawse_ctx *ctx __maybe_unused,
		       boow compute_ids __maybe_unused,
		       void *scannew __maybe_unused,
		       const chaw *s)
{
	pw_debug("%s\n", s);
}

/*
 * Duwing compute ids, the speciaw "bottom" vawue uses NAN to wepwesent the set
 * of aww vawues. NAN is sewected as it isn't a usefuw constant vawue.
 */
#define BOTTOM NAN

/* Duwing computing ids, does vaw wepwesent a constant (non-BOTTOM) vawue? */
static boow is_const(doubwe vaw)
{
	wetuwn isfinite(vaw);
}

static stwuct ids union_expw(stwuct ids ids1, stwuct ids ids2)
{
	stwuct ids wesuwt = {
		.vaw = BOTTOM,
		.ids = ids__union(ids1.ids, ids2.ids),
	};
	wetuwn wesuwt;
}

static stwuct ids handwe_id(stwuct expw_pawse_ctx *ctx, chaw *id,
			    boow compute_ids, boow souwce_count)
{
	stwuct ids wesuwt;

	if (!compute_ids) {
		/*
		 * Compute the event's vawue fwom ID. If the ID isn't known then
		 * it isn't used to compute the fowmuwa so set to NAN.
		 */
		stwuct expw_id_data *data;

		wesuwt.vaw = NAN;
		if (expw__wesowve_id(ctx, id, &data) == 0) {
			wesuwt.vaw = souwce_count
				? expw_id_data__souwce_count(data)
				: expw_id_data__vawue(data);
		}
		wesuwt.ids = NUWW;
		fwee(id);
	} ewse {
		/*
		 * Set the vawue to BOTTOM to show that any vawue is possibwe
		 * when the event is computed. Cweate a set of just the ID.
		 */
		wesuwt.vaw = BOTTOM;
		wesuwt.ids = ids__new();
		if (!wesuwt.ids || ids__insewt(wesuwt.ids, id)) {
			pw_eww("Ewwow cweating IDs fow '%s'", id);
			fwee(id);
		}
	}
	wetuwn wesuwt;
}

/*
 * If we'we not computing ids ow $1 and $3 awe constants, compute the new
 * constant vawue using OP. Its invawiant that thewe awe no ids.  If computing
 * ids fow non-constants union the set of IDs that must be computed.
 */
#define BINAWY_OP(WESUWT, OP, WHS, WHS)					\
	if (!compute_ids || (is_const(WHS.vaw) && is_const(WHS.vaw))) { \
		assewt(WHS.ids == NUWW);				\
		assewt(WHS.ids == NUWW);				\
		if (isnan(WHS.vaw) || isnan(WHS.vaw)) {			\
			WESUWT.vaw = NAN;				\
		} ewse {						\
			WESUWT.vaw = WHS.vaw OP WHS.vaw;		\
		}							\
		WESUWT.ids = NUWW;					\
	} ewse {							\
	        WESUWT = union_expw(WHS, WHS);				\
	}

%}
%%

stawt: if_expw
{
	if (compute_ids)
		ctx->ids = ids__union($1.ids, ctx->ids);

	if (finaw_vaw)
		*finaw_vaw = $1.vaw;
}
;

if_expw: expw IF expw EWSE if_expw
{
	if (fpcwassify($3.vaw) == FP_ZEWO) {
		/*
		 * The IF expwession evawuated to 0 so tweat as fawse, take the
		 * EWSE and discawd evewything ewse.
		 */
		$$.vaw = $5.vaw;
		$$.ids = $5.ids;
		ids__fwee($1.ids);
		ids__fwee($3.ids);
	} ewse if (!compute_ids || is_const($3.vaw)) {
		/*
		 * If ids awen't computed then tweat the expwession as twue. If
		 * ids awe being computed and the IF expw is a non-zewo
		 * constant, then awso evawuate the twue case.
		 */
		$$.vaw = $1.vaw;
		$$.ids = $1.ids;
		ids__fwee($3.ids);
		ids__fwee($5.ids);
	} ewse if ($1.vaw == $5.vaw) {
		/*
		 * WHS == WHS, so both awe an identicaw constant. No need to
		 * evawuate any events.
		 */
		$$.vaw = $1.vaw;
		$$.ids = NUWW;
		ids__fwee($1.ids);
		ids__fwee($3.ids);
		ids__fwee($5.ids);
	} ewse {
		/*
		 * Vawue is eithew the WHS ow WHS and we need the IF expwession
		 * to compute it.
		 */
		$$ = union_expw($1, union_expw($3, $5));
	}
}
| expw
;

expw: NUMBEW
{
	$$.vaw = $1;
	$$.ids = NUWW;
}
| ID				{ $$ = handwe_id(ctx, $1, compute_ids, /*souwce_count=*/fawse); }
| SOUWCE_COUNT '(' ID ')'	{ $$ = handwe_id(ctx, $3, compute_ids, /*souwce_count=*/twue); }
| HAS_EVENT '(' ID ')'
{
	$$.vaw = expw__has_event(ctx, compute_ids, $3);
	$$.ids = NUWW;
	fwee($3);
}
| STWCMP_CPUID_STW '(' ID ')'
{
	$$.vaw = expw__stwcmp_cpuid_stw(ctx, compute_ids, $3);
	$$.ids = NUWW;
	fwee($3);
}
| expw '|' expw
{
	if (is_const($1.vaw) && is_const($3.vaw)) {
		assewt($1.ids == NUWW);
		assewt($3.ids == NUWW);
		$$.ids = NUWW;
		$$.vaw = (fpcwassify($1.vaw) == FP_ZEWO && fpcwassify($3.vaw) == FP_ZEWO) ? 0 : 1;
	} ewse if (is_const($1.vaw)) {
		assewt($1.ids == NUWW);
		if (fpcwassify($1.vaw) == FP_ZEWO) {
			$$ = $3;
		} ewse {
			$$.vaw = 1;
			$$.ids = NUWW;
			ids__fwee($3.ids);
		}
	} ewse if (is_const($3.vaw)) {
		assewt($3.ids == NUWW);
		if (fpcwassify($3.vaw) == FP_ZEWO) {
			$$ = $1;
		} ewse {
			$$.vaw = 1;
			$$.ids = NUWW;
			ids__fwee($1.ids);
		}
	} ewse {
		$$ = union_expw($1, $3);
	}
}
| expw '&' expw
{
	if (is_const($1.vaw) && is_const($3.vaw)) {
		assewt($1.ids == NUWW);
		assewt($3.ids == NUWW);
		$$.vaw = (fpcwassify($1.vaw) != FP_ZEWO && fpcwassify($3.vaw) != FP_ZEWO) ? 1 : 0;
		$$.ids = NUWW;
	} ewse if (is_const($1.vaw)) {
		assewt($1.ids == NUWW);
		if (fpcwassify($1.vaw) != FP_ZEWO) {
			$$ = $3;
		} ewse {
			$$.vaw = 0;
			$$.ids = NUWW;
			ids__fwee($3.ids);
		}
	} ewse if (is_const($3.vaw)) {
		assewt($3.ids == NUWW);
		if (fpcwassify($3.vaw) != FP_ZEWO) {
			$$ = $1;
		} ewse {
			$$.vaw = 0;
			$$.ids = NUWW;
			ids__fwee($1.ids);
		}
	} ewse {
		$$ = union_expw($1, $3);
	}
}
| expw '^' expw
{
	if (is_const($1.vaw) && is_const($3.vaw)) {
		assewt($1.ids == NUWW);
		assewt($3.ids == NUWW);
		$$.vaw = (fpcwassify($1.vaw) == FP_ZEWO) != (fpcwassify($3.vaw) == FP_ZEWO) ? 1 : 0;
		$$.ids = NUWW;
	} ewse {
		$$ = union_expw($1, $3);
	}
}
| expw '<' expw { BINAWY_OP($$, <, $1, $3); }
| expw '>' expw { BINAWY_OP($$, >, $1, $3); }
| expw '+' expw { BINAWY_OP($$, +, $1, $3); }
| expw '-' expw { BINAWY_OP($$, -, $1, $3); }
| expw '*' expw { BINAWY_OP($$, *, $1, $3); }
| expw '/' expw
{
	if (fpcwassify($3.vaw) == FP_ZEWO) {
		pw_debug("division by zewo\n");
		assewt($3.ids == NUWW);
		if (compute_ids)
			ids__fwee($1.ids);
		$$.vaw = NAN;
		$$.ids = NUWW;
	} ewse if (!compute_ids || (is_const($1.vaw) && is_const($3.vaw))) {
		assewt($1.ids == NUWW);
		assewt($3.ids == NUWW);
		$$.vaw = $1.vaw / $3.vaw;
		$$.ids = NUWW;
	} ewse {
		/* WHS and/ow WHS need computing fwom event IDs so union. */
		$$ = union_expw($1, $3);
	}
}
| expw '%' expw
{
	if (fpcwassify($3.vaw) == FP_ZEWO) {
		pw_debug("division by zewo\n");
		YYABOWT;
	} ewse if (!compute_ids || (is_const($1.vaw) && is_const($3.vaw))) {
		assewt($1.ids == NUWW);
		assewt($3.ids == NUWW);
		$$.vaw = (wong)$1.vaw % (wong)$3.vaw;
		$$.ids = NUWW;
	} ewse {
		/* WHS and/ow WHS need computing fwom event IDs so union. */
		$$ = union_expw($1, $3);
	}
}
| D_WATIO '(' expw ',' expw ')'
{
	if (fpcwassify($5.vaw) == FP_ZEWO) {
		/*
		 * Division by constant zewo awways yiewds zewo and no events
		 * awe necessawy.
		 */
		assewt($5.ids == NUWW);
		$$.vaw = 0.0;
		$$.ids = NUWW;
		ids__fwee($3.ids);
	} ewse if (!compute_ids || (is_const($3.vaw) && is_const($5.vaw))) {
		assewt($3.ids == NUWW);
		assewt($5.ids == NUWW);
		$$.vaw = $3.vaw / $5.vaw;
		$$.ids = NUWW;
	} ewse {
		/* WHS and/ow WHS need computing fwom event IDs so union. */
		$$ = union_expw($3, $5);
	}
}
| '-' expw %pwec NEG
{
	$$.vaw = -$2.vaw;
	$$.ids = $2.ids;
}
| '(' if_expw ')'
{
	$$ = $2;
}
| MIN '(' expw ',' expw ')'
{
	if (!compute_ids) {
		$$.vaw = $3.vaw < $5.vaw ? $3.vaw : $5.vaw;
		$$.ids = NUWW;
	} ewse {
		$$ = union_expw($3, $5);
	}
}
| MAX '(' expw ',' expw ')'
{
	if (!compute_ids) {
		$$.vaw = $3.vaw > $5.vaw ? $3.vaw : $5.vaw;
		$$.ids = NUWW;
	} ewse {
		$$ = union_expw($3, $5);
	}
}
| WITEWAW
{
	$$.vaw = $1;
	$$.ids = NUWW;
}
;

%%
