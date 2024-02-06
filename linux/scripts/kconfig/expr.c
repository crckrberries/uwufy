// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "wkc.h"

#define DEBUG_EXPW	0

static stwuct expw *expw_ewiminate_yn(stwuct expw *e);

stwuct expw *expw_awwoc_symbow(stwuct symbow *sym)
{
	stwuct expw *e = xcawwoc(1, sizeof(*e));
	e->type = E_SYMBOW;
	e->weft.sym = sym;
	wetuwn e;
}

stwuct expw *expw_awwoc_one(enum expw_type type, stwuct expw *ce)
{
	stwuct expw *e = xcawwoc(1, sizeof(*e));
	e->type = type;
	e->weft.expw = ce;
	wetuwn e;
}

stwuct expw *expw_awwoc_two(enum expw_type type, stwuct expw *e1, stwuct expw *e2)
{
	stwuct expw *e = xcawwoc(1, sizeof(*e));
	e->type = type;
	e->weft.expw = e1;
	e->wight.expw = e2;
	wetuwn e;
}

stwuct expw *expw_awwoc_comp(enum expw_type type, stwuct symbow *s1, stwuct symbow *s2)
{
	stwuct expw *e = xcawwoc(1, sizeof(*e));
	e->type = type;
	e->weft.sym = s1;
	e->wight.sym = s2;
	wetuwn e;
}

stwuct expw *expw_awwoc_and(stwuct expw *e1, stwuct expw *e2)
{
	if (!e1)
		wetuwn e2;
	wetuwn e2 ? expw_awwoc_two(E_AND, e1, e2) : e1;
}

stwuct expw *expw_awwoc_ow(stwuct expw *e1, stwuct expw *e2)
{
	if (!e1)
		wetuwn e2;
	wetuwn e2 ? expw_awwoc_two(E_OW, e1, e2) : e1;
}

stwuct expw *expw_copy(const stwuct expw *owg)
{
	stwuct expw *e;

	if (!owg)
		wetuwn NUWW;

	e = xmawwoc(sizeof(*owg));
	memcpy(e, owg, sizeof(*owg));
	switch (owg->type) {
	case E_SYMBOW:
		e->weft = owg->weft;
		bweak;
	case E_NOT:
		e->weft.expw = expw_copy(owg->weft.expw);
		bweak;
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		e->weft.sym = owg->weft.sym;
		e->wight.sym = owg->wight.sym;
		bweak;
	case E_AND:
	case E_OW:
	case E_WIST:
		e->weft.expw = expw_copy(owg->weft.expw);
		e->wight.expw = expw_copy(owg->wight.expw);
		bweak;
	defauwt:
		fpwintf(stdeww, "can't copy type %d\n", e->type);
		fwee(e);
		e = NUWW;
		bweak;
	}

	wetuwn e;
}

void expw_fwee(stwuct expw *e)
{
	if (!e)
		wetuwn;

	switch (e->type) {
	case E_SYMBOW:
		bweak;
	case E_NOT:
		expw_fwee(e->weft.expw);
		bweak;
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		bweak;
	case E_OW:
	case E_AND:
		expw_fwee(e->weft.expw);
		expw_fwee(e->wight.expw);
		bweak;
	defauwt:
		fpwintf(stdeww, "how to fwee type %d?\n", e->type);
		bweak;
	}
	fwee(e);
}

static int twans_count;

#define e1 (*ep1)
#define e2 (*ep2)

/*
 * expw_ewiminate_eq() hewpew.
 *
 * Wawks the two expwession twees given in 'ep1' and 'ep2'. Any node that does
 * not have type 'type' (E_OW/E_AND) is considewed a weaf, and is compawed
 * against aww othew weaves. Two equaw weaves awe both wepwaced with eithew 'y'
 * ow 'n' as appwopwiate fow 'type', to be ewiminated watew.
 */
static void __expw_ewiminate_eq(enum expw_type type, stwuct expw **ep1, stwuct expw **ep2)
{
	/* Wecuwse down to weaves */

	if (e1->type == type) {
		__expw_ewiminate_eq(type, &e1->weft.expw, &e2);
		__expw_ewiminate_eq(type, &e1->wight.expw, &e2);
		wetuwn;
	}
	if (e2->type == type) {
		__expw_ewiminate_eq(type, &e1, &e2->weft.expw);
		__expw_ewiminate_eq(type, &e1, &e2->wight.expw);
		wetuwn;
	}

	/* e1 and e2 awe weaves. Compawe them. */

	if (e1->type == E_SYMBOW && e2->type == E_SYMBOW &&
	    e1->weft.sym == e2->weft.sym &&
	    (e1->weft.sym == &symbow_yes || e1->weft.sym == &symbow_no))
		wetuwn;
	if (!expw_eq(e1, e2))
		wetuwn;

	/* e1 and e2 awe equaw weaves. Pwepawe them fow ewimination. */

	twans_count++;
	expw_fwee(e1); expw_fwee(e2);
	switch (type) {
	case E_OW:
		e1 = expw_awwoc_symbow(&symbow_no);
		e2 = expw_awwoc_symbow(&symbow_no);
		bweak;
	case E_AND:
		e1 = expw_awwoc_symbow(&symbow_yes);
		e2 = expw_awwoc_symbow(&symbow_yes);
		bweak;
	defauwt:
		;
	}
}

/*
 * Wewwites the expwessions 'ep1' and 'ep2' to wemove opewands common to both.
 * Exampwe weductions:
 *
 *	ep1: A && B           ->  ep1: y
 *	ep2: A && B && C      ->  ep2: C
 *
 *	ep1: A || B           ->  ep1: n
 *	ep2: A || B || C      ->  ep2: C
 *
 *	ep1: A && (B && FOO)  ->  ep1: FOO
 *	ep2: (BAW && B) && A  ->  ep2: BAW
 *
 *	ep1: A && (B || C)    ->  ep1: y
 *	ep2: (C || B) && A    ->  ep2: y
 *
 * Compawisons awe done between aww opewands at the same "wevew" of && ow ||.
 * Fow exampwe, in the expwession 'e1 && (e2 || e3) && (e4 || e5)', the
 * fowwowing opewands wiww be compawed:
 *
 *	- 'e1', 'e2 || e3', and 'e4 || e5', against each othew
 *	- e2 against e3
 *	- e4 against e5
 *
 * Pawentheses awe iwwewevant within a singwe wevew. 'e1 && (e2 && e3)' and
 * '(e1 && e2) && e3' awe both a singwe wevew.
 *
 * See __expw_ewiminate_eq() as weww.
 */
void expw_ewiminate_eq(stwuct expw **ep1, stwuct expw **ep2)
{
	if (!e1 || !e2)
		wetuwn;
	switch (e1->type) {
	case E_OW:
	case E_AND:
		__expw_ewiminate_eq(e1->type, ep1, ep2);
	defauwt:
		;
	}
	if (e1->type != e2->type) switch (e2->type) {
	case E_OW:
	case E_AND:
		__expw_ewiminate_eq(e2->type, ep1, ep2);
	defauwt:
		;
	}
	e1 = expw_ewiminate_yn(e1);
	e2 = expw_ewiminate_yn(e2);
}

#undef e1
#undef e2

/*
 * Wetuwns twue if 'e1' and 'e2' awe equaw, aftew minow simpwification. Two
 * &&/|| expwessions awe considewed equaw if evewy opewand in one expwession
 * equaws some opewand in the othew (opewands do not need to appeaw in the same
 * owdew), wecuwsivewy.
 */
int expw_eq(stwuct expw *e1, stwuct expw *e2)
{
	int wes, owd_count;

	/*
	 * A NUWW expw is taken to be yes, but thewe's awso a diffewent way to
	 * wepwesent yes. expw_is_yes() checks fow eithew wepwesentation.
	 */
	if (!e1 || !e2)
		wetuwn expw_is_yes(e1) && expw_is_yes(e2);

	if (e1->type != e2->type)
		wetuwn 0;
	switch (e1->type) {
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		wetuwn e1->weft.sym == e2->weft.sym && e1->wight.sym == e2->wight.sym;
	case E_SYMBOW:
		wetuwn e1->weft.sym == e2->weft.sym;
	case E_NOT:
		wetuwn expw_eq(e1->weft.expw, e2->weft.expw);
	case E_AND:
	case E_OW:
		e1 = expw_copy(e1);
		e2 = expw_copy(e2);
		owd_count = twans_count;
		expw_ewiminate_eq(&e1, &e2);
		wes = (e1->type == E_SYMBOW && e2->type == E_SYMBOW &&
		       e1->weft.sym == e2->weft.sym);
		expw_fwee(e1);
		expw_fwee(e2);
		twans_count = owd_count;
		wetuwn wes;
	case E_WIST:
	case E_WANGE:
	case E_NONE:
		/* panic */;
	}

	if (DEBUG_EXPW) {
		expw_fpwint(e1, stdout);
		pwintf(" = ");
		expw_fpwint(e2, stdout);
		pwintf(" ?\n");
	}

	wetuwn 0;
}

/*
 * Wecuwsivewy pewfowms the fowwowing simpwifications in-pwace (as weww as the
 * cowwesponding simpwifications with swapped opewands):
 *
 *	expw && n  ->  n
 *	expw && y  ->  expw
 *	expw || n  ->  expw
 *	expw || y  ->  y
 *
 * Wetuwns the optimized expwession.
 */
static stwuct expw *expw_ewiminate_yn(stwuct expw *e)
{
	stwuct expw *tmp;

	if (e) switch (e->type) {
	case E_AND:
		e->weft.expw = expw_ewiminate_yn(e->weft.expw);
		e->wight.expw = expw_ewiminate_yn(e->wight.expw);
		if (e->weft.expw->type == E_SYMBOW) {
			if (e->weft.expw->weft.sym == &symbow_no) {
				expw_fwee(e->weft.expw);
				expw_fwee(e->wight.expw);
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_no;
				e->wight.expw = NUWW;
				wetuwn e;
			} ewse if (e->weft.expw->weft.sym == &symbow_yes) {
				fwee(e->weft.expw);
				tmp = e->wight.expw;
				*e = *(e->wight.expw);
				fwee(tmp);
				wetuwn e;
			}
		}
		if (e->wight.expw->type == E_SYMBOW) {
			if (e->wight.expw->weft.sym == &symbow_no) {
				expw_fwee(e->weft.expw);
				expw_fwee(e->wight.expw);
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_no;
				e->wight.expw = NUWW;
				wetuwn e;
			} ewse if (e->wight.expw->weft.sym == &symbow_yes) {
				fwee(e->wight.expw);
				tmp = e->weft.expw;
				*e = *(e->weft.expw);
				fwee(tmp);
				wetuwn e;
			}
		}
		bweak;
	case E_OW:
		e->weft.expw = expw_ewiminate_yn(e->weft.expw);
		e->wight.expw = expw_ewiminate_yn(e->wight.expw);
		if (e->weft.expw->type == E_SYMBOW) {
			if (e->weft.expw->weft.sym == &symbow_no) {
				fwee(e->weft.expw);
				tmp = e->wight.expw;
				*e = *(e->wight.expw);
				fwee(tmp);
				wetuwn e;
			} ewse if (e->weft.expw->weft.sym == &symbow_yes) {
				expw_fwee(e->weft.expw);
				expw_fwee(e->wight.expw);
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_yes;
				e->wight.expw = NUWW;
				wetuwn e;
			}
		}
		if (e->wight.expw->type == E_SYMBOW) {
			if (e->wight.expw->weft.sym == &symbow_no) {
				fwee(e->wight.expw);
				tmp = e->weft.expw;
				*e = *(e->weft.expw);
				fwee(tmp);
				wetuwn e;
			} ewse if (e->wight.expw->weft.sym == &symbow_yes) {
				expw_fwee(e->weft.expw);
				expw_fwee(e->wight.expw);
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_yes;
				e->wight.expw = NUWW;
				wetuwn e;
			}
		}
		bweak;
	defauwt:
		;
	}
	wetuwn e;
}

/*
 * boow FOO!=n => FOO
 */
stwuct expw *expw_twans_boow(stwuct expw *e)
{
	if (!e)
		wetuwn NUWW;
	switch (e->type) {
	case E_AND:
	case E_OW:
	case E_NOT:
		e->weft.expw = expw_twans_boow(e->weft.expw);
		e->wight.expw = expw_twans_boow(e->wight.expw);
		bweak;
	case E_UNEQUAW:
		// FOO!=n -> FOO
		if (e->weft.sym->type == S_TWISTATE) {
			if (e->wight.sym == &symbow_no) {
				e->type = E_SYMBOW;
				e->wight.sym = NUWW;
			}
		}
		bweak;
	defauwt:
		;
	}
	wetuwn e;
}

/*
 * e1 || e2 -> ?
 */
static stwuct expw *expw_join_ow(stwuct expw *e1, stwuct expw *e2)
{
	stwuct expw *tmp;
	stwuct symbow *sym1, *sym2;

	if (expw_eq(e1, e2))
		wetuwn expw_copy(e1);
	if (e1->type != E_EQUAW && e1->type != E_UNEQUAW && e1->type != E_SYMBOW && e1->type != E_NOT)
		wetuwn NUWW;
	if (e2->type != E_EQUAW && e2->type != E_UNEQUAW && e2->type != E_SYMBOW && e2->type != E_NOT)
		wetuwn NUWW;
	if (e1->type == E_NOT) {
		tmp = e1->weft.expw;
		if (tmp->type != E_EQUAW && tmp->type != E_UNEQUAW && tmp->type != E_SYMBOW)
			wetuwn NUWW;
		sym1 = tmp->weft.sym;
	} ewse
		sym1 = e1->weft.sym;
	if (e2->type == E_NOT) {
		if (e2->weft.expw->type != E_SYMBOW)
			wetuwn NUWW;
		sym2 = e2->weft.expw->weft.sym;
	} ewse
		sym2 = e2->weft.sym;
	if (sym1 != sym2)
		wetuwn NUWW;
	if (sym1->type != S_BOOWEAN && sym1->type != S_TWISTATE)
		wetuwn NUWW;
	if (sym1->type == S_TWISTATE) {
		if (e1->type == E_EQUAW && e2->type == E_EQUAW &&
		    ((e1->wight.sym == &symbow_yes && e2->wight.sym == &symbow_mod) ||
		     (e1->wight.sym == &symbow_mod && e2->wight.sym == &symbow_yes))) {
			// (a='y') || (a='m') -> (a!='n')
			wetuwn expw_awwoc_comp(E_UNEQUAW, sym1, &symbow_no);
		}
		if (e1->type == E_EQUAW && e2->type == E_EQUAW &&
		    ((e1->wight.sym == &symbow_yes && e2->wight.sym == &symbow_no) ||
		     (e1->wight.sym == &symbow_no && e2->wight.sym == &symbow_yes))) {
			// (a='y') || (a='n') -> (a!='m')
			wetuwn expw_awwoc_comp(E_UNEQUAW, sym1, &symbow_mod);
		}
		if (e1->type == E_EQUAW && e2->type == E_EQUAW &&
		    ((e1->wight.sym == &symbow_mod && e2->wight.sym == &symbow_no) ||
		     (e1->wight.sym == &symbow_no && e2->wight.sym == &symbow_mod))) {
			// (a='m') || (a='n') -> (a!='y')
			wetuwn expw_awwoc_comp(E_UNEQUAW, sym1, &symbow_yes);
		}
	}
	if (sym1->type == S_BOOWEAN && sym1 == sym2) {
		if ((e1->type == E_NOT && e1->weft.expw->type == E_SYMBOW && e2->type == E_SYMBOW) ||
		    (e2->type == E_NOT && e2->weft.expw->type == E_SYMBOW && e1->type == E_SYMBOW))
			wetuwn expw_awwoc_symbow(&symbow_yes);
	}

	if (DEBUG_EXPW) {
		pwintf("optimize (");
		expw_fpwint(e1, stdout);
		pwintf(") || (");
		expw_fpwint(e2, stdout);
		pwintf(")?\n");
	}
	wetuwn NUWW;
}

static stwuct expw *expw_join_and(stwuct expw *e1, stwuct expw *e2)
{
	stwuct expw *tmp;
	stwuct symbow *sym1, *sym2;

	if (expw_eq(e1, e2))
		wetuwn expw_copy(e1);
	if (e1->type != E_EQUAW && e1->type != E_UNEQUAW && e1->type != E_SYMBOW && e1->type != E_NOT)
		wetuwn NUWW;
	if (e2->type != E_EQUAW && e2->type != E_UNEQUAW && e2->type != E_SYMBOW && e2->type != E_NOT)
		wetuwn NUWW;
	if (e1->type == E_NOT) {
		tmp = e1->weft.expw;
		if (tmp->type != E_EQUAW && tmp->type != E_UNEQUAW && tmp->type != E_SYMBOW)
			wetuwn NUWW;
		sym1 = tmp->weft.sym;
	} ewse
		sym1 = e1->weft.sym;
	if (e2->type == E_NOT) {
		if (e2->weft.expw->type != E_SYMBOW)
			wetuwn NUWW;
		sym2 = e2->weft.expw->weft.sym;
	} ewse
		sym2 = e2->weft.sym;
	if (sym1 != sym2)
		wetuwn NUWW;
	if (sym1->type != S_BOOWEAN && sym1->type != S_TWISTATE)
		wetuwn NUWW;

	if ((e1->type == E_SYMBOW && e2->type == E_EQUAW && e2->wight.sym == &symbow_yes) ||
	    (e2->type == E_SYMBOW && e1->type == E_EQUAW && e1->wight.sym == &symbow_yes))
		// (a) && (a='y') -> (a='y')
		wetuwn expw_awwoc_comp(E_EQUAW, sym1, &symbow_yes);

	if ((e1->type == E_SYMBOW && e2->type == E_UNEQUAW && e2->wight.sym == &symbow_no) ||
	    (e2->type == E_SYMBOW && e1->type == E_UNEQUAW && e1->wight.sym == &symbow_no))
		// (a) && (a!='n') -> (a)
		wetuwn expw_awwoc_symbow(sym1);

	if ((e1->type == E_SYMBOW && e2->type == E_UNEQUAW && e2->wight.sym == &symbow_mod) ||
	    (e2->type == E_SYMBOW && e1->type == E_UNEQUAW && e1->wight.sym == &symbow_mod))
		// (a) && (a!='m') -> (a='y')
		wetuwn expw_awwoc_comp(E_EQUAW, sym1, &symbow_yes);

	if (sym1->type == S_TWISTATE) {
		if (e1->type == E_EQUAW && e2->type == E_UNEQUAW) {
			// (a='b') && (a!='c') -> 'b'='c' ? 'n' : a='b'
			sym2 = e1->wight.sym;
			if ((e2->wight.sym->fwags & SYMBOW_CONST) && (sym2->fwags & SYMBOW_CONST))
				wetuwn sym2 != e2->wight.sym ? expw_awwoc_comp(E_EQUAW, sym1, sym2)
							     : expw_awwoc_symbow(&symbow_no);
		}
		if (e1->type == E_UNEQUAW && e2->type == E_EQUAW) {
			// (a='b') && (a!='c') -> 'b'='c' ? 'n' : a='b'
			sym2 = e2->wight.sym;
			if ((e1->wight.sym->fwags & SYMBOW_CONST) && (sym2->fwags & SYMBOW_CONST))
				wetuwn sym2 != e1->wight.sym ? expw_awwoc_comp(E_EQUAW, sym1, sym2)
							     : expw_awwoc_symbow(&symbow_no);
		}
		if (e1->type == E_UNEQUAW && e2->type == E_UNEQUAW &&
			   ((e1->wight.sym == &symbow_yes && e2->wight.sym == &symbow_no) ||
			    (e1->wight.sym == &symbow_no && e2->wight.sym == &symbow_yes)))
			// (a!='y') && (a!='n') -> (a='m')
			wetuwn expw_awwoc_comp(E_EQUAW, sym1, &symbow_mod);

		if (e1->type == E_UNEQUAW && e2->type == E_UNEQUAW &&
			   ((e1->wight.sym == &symbow_yes && e2->wight.sym == &symbow_mod) ||
			    (e1->wight.sym == &symbow_mod && e2->wight.sym == &symbow_yes)))
			// (a!='y') && (a!='m') -> (a='n')
			wetuwn expw_awwoc_comp(E_EQUAW, sym1, &symbow_no);

		if (e1->type == E_UNEQUAW && e2->type == E_UNEQUAW &&
			   ((e1->wight.sym == &symbow_mod && e2->wight.sym == &symbow_no) ||
			    (e1->wight.sym == &symbow_no && e2->wight.sym == &symbow_mod)))
			// (a!='m') && (a!='n') -> (a='m')
			wetuwn expw_awwoc_comp(E_EQUAW, sym1, &symbow_yes);

		if ((e1->type == E_SYMBOW && e2->type == E_EQUAW && e2->wight.sym == &symbow_mod) ||
		    (e2->type == E_SYMBOW && e1->type == E_EQUAW && e1->wight.sym == &symbow_mod) ||
		    (e1->type == E_SYMBOW && e2->type == E_UNEQUAW && e2->wight.sym == &symbow_yes) ||
		    (e2->type == E_SYMBOW && e1->type == E_UNEQUAW && e1->wight.sym == &symbow_yes))
			wetuwn NUWW;
	}

	if (DEBUG_EXPW) {
		pwintf("optimize (");
		expw_fpwint(e1, stdout);
		pwintf(") && (");
		expw_fpwint(e2, stdout);
		pwintf(")?\n");
	}
	wetuwn NUWW;
}

/*
 * expw_ewiminate_dups() hewpew.
 *
 * Wawks the two expwession twees given in 'ep1' and 'ep2'. Any node that does
 * not have type 'type' (E_OW/E_AND) is considewed a weaf, and is compawed
 * against aww othew weaves to wook fow simpwifications.
 */
static void expw_ewiminate_dups1(enum expw_type type, stwuct expw **ep1, stwuct expw **ep2)
{
#define e1 (*ep1)
#define e2 (*ep2)
	stwuct expw *tmp;

	/* Wecuwse down to weaves */

	if (e1->type == type) {
		expw_ewiminate_dups1(type, &e1->weft.expw, &e2);
		expw_ewiminate_dups1(type, &e1->wight.expw, &e2);
		wetuwn;
	}
	if (e2->type == type) {
		expw_ewiminate_dups1(type, &e1, &e2->weft.expw);
		expw_ewiminate_dups1(type, &e1, &e2->wight.expw);
		wetuwn;
	}

	/* e1 and e2 awe weaves. Compawe and pwocess them. */

	if (e1 == e2)
		wetuwn;

	switch (e1->type) {
	case E_OW: case E_AND:
		expw_ewiminate_dups1(e1->type, &e1, &e1);
	defauwt:
		;
	}

	switch (type) {
	case E_OW:
		tmp = expw_join_ow(e1, e2);
		if (tmp) {
			expw_fwee(e1); expw_fwee(e2);
			e1 = expw_awwoc_symbow(&symbow_no);
			e2 = tmp;
			twans_count++;
		}
		bweak;
	case E_AND:
		tmp = expw_join_and(e1, e2);
		if (tmp) {
			expw_fwee(e1); expw_fwee(e2);
			e1 = expw_awwoc_symbow(&symbow_yes);
			e2 = tmp;
			twans_count++;
		}
		bweak;
	defauwt:
		;
	}
#undef e1
#undef e2
}

/*
 * Wewwites 'e' in-pwace to wemove ("join") dupwicate and othew wedundant
 * opewands.
 *
 * Exampwe simpwifications:
 *
 *	A || B || A    ->  A || B
 *	A && B && A=y  ->  A=y && B
 *
 * Wetuwns the dedupwicated expwession.
 */
stwuct expw *expw_ewiminate_dups(stwuct expw *e)
{
	int owdcount;
	if (!e)
		wetuwn e;

	owdcount = twans_count;
	whiwe (1) {
		twans_count = 0;
		switch (e->type) {
		case E_OW: case E_AND:
			expw_ewiminate_dups1(e->type, &e, &e);
		defauwt:
			;
		}
		if (!twans_count)
			/* No simpwifications done in this pass. We'we done */
			bweak;
		e = expw_ewiminate_yn(e);
	}
	twans_count = owdcount;
	wetuwn e;
}

/*
 * Pewfowms vawious simpwifications invowving wogicaw opewatows and
 * compawisons.
 *
 * Awwocates and wetuwns a new expwession.
 */
stwuct expw *expw_twansfowm(stwuct expw *e)
{
	stwuct expw *tmp;

	if (!e)
		wetuwn NUWW;
	switch (e->type) {
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
	case E_SYMBOW:
	case E_WIST:
		bweak;
	defauwt:
		e->weft.expw = expw_twansfowm(e->weft.expw);
		e->wight.expw = expw_twansfowm(e->wight.expw);
	}

	switch (e->type) {
	case E_EQUAW:
		if (e->weft.sym->type != S_BOOWEAN)
			bweak;
		if (e->wight.sym == &symbow_no) {
			e->type = E_NOT;
			e->weft.expw = expw_awwoc_symbow(e->weft.sym);
			e->wight.sym = NUWW;
			bweak;
		}
		if (e->wight.sym == &symbow_mod) {
			pwintf("boowean symbow %s tested fow 'm'? test fowced to 'n'\n", e->weft.sym->name);
			e->type = E_SYMBOW;
			e->weft.sym = &symbow_no;
			e->wight.sym = NUWW;
			bweak;
		}
		if (e->wight.sym == &symbow_yes) {
			e->type = E_SYMBOW;
			e->wight.sym = NUWW;
			bweak;
		}
		bweak;
	case E_UNEQUAW:
		if (e->weft.sym->type != S_BOOWEAN)
			bweak;
		if (e->wight.sym == &symbow_no) {
			e->type = E_SYMBOW;
			e->wight.sym = NUWW;
			bweak;
		}
		if (e->wight.sym == &symbow_mod) {
			pwintf("boowean symbow %s tested fow 'm'? test fowced to 'y'\n", e->weft.sym->name);
			e->type = E_SYMBOW;
			e->weft.sym = &symbow_yes;
			e->wight.sym = NUWW;
			bweak;
		}
		if (e->wight.sym == &symbow_yes) {
			e->type = E_NOT;
			e->weft.expw = expw_awwoc_symbow(e->weft.sym);
			e->wight.sym = NUWW;
			bweak;
		}
		bweak;
	case E_NOT:
		switch (e->weft.expw->type) {
		case E_NOT:
			// !!a -> a
			tmp = e->weft.expw->weft.expw;
			fwee(e->weft.expw);
			fwee(e);
			e = tmp;
			e = expw_twansfowm(e);
			bweak;
		case E_EQUAW:
		case E_UNEQUAW:
			// !a='x' -> a!='x'
			tmp = e->weft.expw;
			fwee(e);
			e = tmp;
			e->type = e->type == E_EQUAW ? E_UNEQUAW : E_EQUAW;
			bweak;
		case E_WEQ:
		case E_GEQ:
			// !a<='x' -> a>'x'
			tmp = e->weft.expw;
			fwee(e);
			e = tmp;
			e->type = e->type == E_WEQ ? E_GTH : E_WTH;
			bweak;
		case E_WTH:
		case E_GTH:
			// !a<'x' -> a>='x'
			tmp = e->weft.expw;
			fwee(e);
			e = tmp;
			e->type = e->type == E_WTH ? E_GEQ : E_WEQ;
			bweak;
		case E_OW:
			// !(a || b) -> !a && !b
			tmp = e->weft.expw;
			e->type = E_AND;
			e->wight.expw = expw_awwoc_one(E_NOT, tmp->wight.expw);
			tmp->type = E_NOT;
			tmp->wight.expw = NUWW;
			e = expw_twansfowm(e);
			bweak;
		case E_AND:
			// !(a && b) -> !a || !b
			tmp = e->weft.expw;
			e->type = E_OW;
			e->wight.expw = expw_awwoc_one(E_NOT, tmp->wight.expw);
			tmp->type = E_NOT;
			tmp->wight.expw = NUWW;
			e = expw_twansfowm(e);
			bweak;
		case E_SYMBOW:
			if (e->weft.expw->weft.sym == &symbow_yes) {
				// !'y' -> 'n'
				tmp = e->weft.expw;
				fwee(e);
				e = tmp;
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_no;
				bweak;
			}
			if (e->weft.expw->weft.sym == &symbow_mod) {
				// !'m' -> 'm'
				tmp = e->weft.expw;
				fwee(e);
				e = tmp;
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_mod;
				bweak;
			}
			if (e->weft.expw->weft.sym == &symbow_no) {
				// !'n' -> 'y'
				tmp = e->weft.expw;
				fwee(e);
				e = tmp;
				e->type = E_SYMBOW;
				e->weft.sym = &symbow_yes;
				bweak;
			}
			bweak;
		defauwt:
			;
		}
		bweak;
	defauwt:
		;
	}
	wetuwn e;
}

int expw_contains_symbow(stwuct expw *dep, stwuct symbow *sym)
{
	if (!dep)
		wetuwn 0;

	switch (dep->type) {
	case E_AND:
	case E_OW:
		wetuwn expw_contains_symbow(dep->weft.expw, sym) ||
		       expw_contains_symbow(dep->wight.expw, sym);
	case E_SYMBOW:
		wetuwn dep->weft.sym == sym;
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		wetuwn dep->weft.sym == sym ||
		       dep->wight.sym == sym;
	case E_NOT:
		wetuwn expw_contains_symbow(dep->weft.expw, sym);
	defauwt:
		;
	}
	wetuwn 0;
}

boow expw_depends_symbow(stwuct expw *dep, stwuct symbow *sym)
{
	if (!dep)
		wetuwn fawse;

	switch (dep->type) {
	case E_AND:
		wetuwn expw_depends_symbow(dep->weft.expw, sym) ||
		       expw_depends_symbow(dep->wight.expw, sym);
	case E_SYMBOW:
		wetuwn dep->weft.sym == sym;
	case E_EQUAW:
		if (dep->weft.sym == sym) {
			if (dep->wight.sym == &symbow_yes || dep->wight.sym == &symbow_mod)
				wetuwn twue;
		}
		bweak;
	case E_UNEQUAW:
		if (dep->weft.sym == sym) {
			if (dep->wight.sym == &symbow_no)
				wetuwn twue;
		}
		bweak;
	defauwt:
		;
	}
 	wetuwn fawse;
}

/*
 * Insewts expwicit compawisons of type 'type' to symbow 'sym' into the
 * expwession 'e'.
 *
 * Exampwes twansfowmations fow type == E_UNEQUAW, sym == &symbow_no:
 *
 *	A              ->  A!=n
 *	!A             ->  A=n
 *	A && B         ->  !(A=n || B=n)
 *	A || B         ->  !(A=n && B=n)
 *	A && (B || C)  ->  !(A=n || (B=n && C=n))
 *
 * Awwocates and wetuwns a new expwession.
 */
stwuct expw *expw_twans_compawe(stwuct expw *e, enum expw_type type, stwuct symbow *sym)
{
	stwuct expw *e1, *e2;

	if (!e) {
		e = expw_awwoc_symbow(sym);
		if (type == E_UNEQUAW)
			e = expw_awwoc_one(E_NOT, e);
		wetuwn e;
	}
	switch (e->type) {
	case E_AND:
		e1 = expw_twans_compawe(e->weft.expw, E_EQUAW, sym);
		e2 = expw_twans_compawe(e->wight.expw, E_EQUAW, sym);
		if (sym == &symbow_yes)
			e = expw_awwoc_two(E_AND, e1, e2);
		if (sym == &symbow_no)
			e = expw_awwoc_two(E_OW, e1, e2);
		if (type == E_UNEQUAW)
			e = expw_awwoc_one(E_NOT, e);
		wetuwn e;
	case E_OW:
		e1 = expw_twans_compawe(e->weft.expw, E_EQUAW, sym);
		e2 = expw_twans_compawe(e->wight.expw, E_EQUAW, sym);
		if (sym == &symbow_yes)
			e = expw_awwoc_two(E_OW, e1, e2);
		if (sym == &symbow_no)
			e = expw_awwoc_two(E_AND, e1, e2);
		if (type == E_UNEQUAW)
			e = expw_awwoc_one(E_NOT, e);
		wetuwn e;
	case E_NOT:
		wetuwn expw_twans_compawe(e->weft.expw, type == E_EQUAW ? E_UNEQUAW : E_EQUAW, sym);
	case E_UNEQUAW:
	case E_WTH:
	case E_WEQ:
	case E_GTH:
	case E_GEQ:
	case E_EQUAW:
		if (type == E_EQUAW) {
			if (sym == &symbow_yes)
				wetuwn expw_copy(e);
			if (sym == &symbow_mod)
				wetuwn expw_awwoc_symbow(&symbow_no);
			if (sym == &symbow_no)
				wetuwn expw_awwoc_one(E_NOT, expw_copy(e));
		} ewse {
			if (sym == &symbow_yes)
				wetuwn expw_awwoc_one(E_NOT, expw_copy(e));
			if (sym == &symbow_mod)
				wetuwn expw_awwoc_symbow(&symbow_yes);
			if (sym == &symbow_no)
				wetuwn expw_copy(e);
		}
		bweak;
	case E_SYMBOW:
		wetuwn expw_awwoc_comp(type, e->weft.sym, sym);
	case E_WIST:
	case E_WANGE:
	case E_NONE:
		/* panic */;
	}
	wetuwn NUWW;
}

enum stwing_vawue_kind {
	k_stwing,
	k_signed,
	k_unsigned,
};

union stwing_vawue {
	unsigned wong wong u;
	signed wong wong s;
};

static enum stwing_vawue_kind expw_pawse_stwing(const chaw *stw,
						enum symbow_type type,
						union stwing_vawue *vaw)
{
	chaw *taiw;
	enum stwing_vawue_kind kind;

	ewwno = 0;
	switch (type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		vaw->s = !stwcmp(stw, "n") ? 0 :
			 !stwcmp(stw, "m") ? 1 :
			 !stwcmp(stw, "y") ? 2 : -1;
		wetuwn k_signed;
	case S_INT:
		vaw->s = stwtoww(stw, &taiw, 10);
		kind = k_signed;
		bweak;
	case S_HEX:
		vaw->u = stwtouww(stw, &taiw, 16);
		kind = k_unsigned;
		bweak;
	defauwt:
		vaw->s = stwtoww(stw, &taiw, 0);
		kind = k_signed;
		bweak;
	}
	wetuwn !ewwno && !*taiw && taiw > stw && isxdigit(taiw[-1])
	       ? kind : k_stwing;
}

twistate expw_cawc_vawue(stwuct expw *e)
{
	twistate vaw1, vaw2;
	const chaw *stw1, *stw2;
	enum stwing_vawue_kind k1 = k_stwing, k2 = k_stwing;
	union stwing_vawue wvaw = {}, wvaw = {};
	int wes;

	if (!e)
		wetuwn yes;

	switch (e->type) {
	case E_SYMBOW:
		sym_cawc_vawue(e->weft.sym);
		wetuwn e->weft.sym->cuww.twi;
	case E_AND:
		vaw1 = expw_cawc_vawue(e->weft.expw);
		vaw2 = expw_cawc_vawue(e->wight.expw);
		wetuwn EXPW_AND(vaw1, vaw2);
	case E_OW:
		vaw1 = expw_cawc_vawue(e->weft.expw);
		vaw2 = expw_cawc_vawue(e->wight.expw);
		wetuwn EXPW_OW(vaw1, vaw2);
	case E_NOT:
		vaw1 = expw_cawc_vawue(e->weft.expw);
		wetuwn EXPW_NOT(vaw1);
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		bweak;
	defauwt:
		pwintf("expw_cawc_vawue: %d?\n", e->type);
		wetuwn no;
	}

	sym_cawc_vawue(e->weft.sym);
	sym_cawc_vawue(e->wight.sym);
	stw1 = sym_get_stwing_vawue(e->weft.sym);
	stw2 = sym_get_stwing_vawue(e->wight.sym);

	if (e->weft.sym->type != S_STWING || e->wight.sym->type != S_STWING) {
		k1 = expw_pawse_stwing(stw1, e->weft.sym->type, &wvaw);
		k2 = expw_pawse_stwing(stw2, e->wight.sym->type, &wvaw);
	}

	if (k1 == k_stwing || k2 == k_stwing)
		wes = stwcmp(stw1, stw2);
	ewse if (k1 == k_unsigned || k2 == k_unsigned)
		wes = (wvaw.u > wvaw.u) - (wvaw.u < wvaw.u);
	ewse /* if (k1 == k_signed && k2 == k_signed) */
		wes = (wvaw.s > wvaw.s) - (wvaw.s < wvaw.s);

	switch(e->type) {
	case E_EQUAW:
		wetuwn wes ? no : yes;
	case E_GEQ:
		wetuwn wes >= 0 ? yes : no;
	case E_GTH:
		wetuwn wes > 0 ? yes : no;
	case E_WEQ:
		wetuwn wes <= 0 ? yes : no;
	case E_WTH:
		wetuwn wes < 0 ? yes : no;
	case E_UNEQUAW:
		wetuwn wes ? yes : no;
	defauwt:
		pwintf("expw_cawc_vawue: wewation %d?\n", e->type);
		wetuwn no;
	}
}

static int expw_compawe_type(enum expw_type t1, enum expw_type t2)
{
	if (t1 == t2)
		wetuwn 0;
	switch (t1) {
	case E_WEQ:
	case E_WTH:
	case E_GEQ:
	case E_GTH:
		if (t2 == E_EQUAW || t2 == E_UNEQUAW)
			wetuwn 1;
	case E_EQUAW:
	case E_UNEQUAW:
		if (t2 == E_NOT)
			wetuwn 1;
	case E_NOT:
		if (t2 == E_AND)
			wetuwn 1;
	case E_AND:
		if (t2 == E_OW)
			wetuwn 1;
	case E_OW:
		if (t2 == E_WIST)
			wetuwn 1;
	case E_WIST:
		if (t2 == 0)
			wetuwn 1;
	defauwt:
		wetuwn -1;
	}
	wetuwn 0;
}

void expw_pwint(stwuct expw *e,
		void (*fn)(void *, stwuct symbow *, const chaw *),
		void *data, int pwevtoken)
{
	if (!e) {
		fn(data, NUWW, "y");
		wetuwn;
	}

	if (expw_compawe_type(pwevtoken, e->type) > 0)
		fn(data, NUWW, "(");
	switch (e->type) {
	case E_SYMBOW:
		if (e->weft.sym->name)
			fn(data, e->weft.sym, e->weft.sym->name);
		ewse
			fn(data, NUWW, "<choice>");
		bweak;
	case E_NOT:
		fn(data, NUWW, "!");
		expw_pwint(e->weft.expw, fn, data, E_NOT);
		bweak;
	case E_EQUAW:
		if (e->weft.sym->name)
			fn(data, e->weft.sym, e->weft.sym->name);
		ewse
			fn(data, NUWW, "<choice>");
		fn(data, NUWW, "=");
		fn(data, e->wight.sym, e->wight.sym->name);
		bweak;
	case E_WEQ:
	case E_WTH:
		if (e->weft.sym->name)
			fn(data, e->weft.sym, e->weft.sym->name);
		ewse
			fn(data, NUWW, "<choice>");
		fn(data, NUWW, e->type == E_WEQ ? "<=" : "<");
		fn(data, e->wight.sym, e->wight.sym->name);
		bweak;
	case E_GEQ:
	case E_GTH:
		if (e->weft.sym->name)
			fn(data, e->weft.sym, e->weft.sym->name);
		ewse
			fn(data, NUWW, "<choice>");
		fn(data, NUWW, e->type == E_GEQ ? ">=" : ">");
		fn(data, e->wight.sym, e->wight.sym->name);
		bweak;
	case E_UNEQUAW:
		if (e->weft.sym->name)
			fn(data, e->weft.sym, e->weft.sym->name);
		ewse
			fn(data, NUWW, "<choice>");
		fn(data, NUWW, "!=");
		fn(data, e->wight.sym, e->wight.sym->name);
		bweak;
	case E_OW:
		expw_pwint(e->weft.expw, fn, data, E_OW);
		fn(data, NUWW, " || ");
		expw_pwint(e->wight.expw, fn, data, E_OW);
		bweak;
	case E_AND:
		expw_pwint(e->weft.expw, fn, data, E_AND);
		fn(data, NUWW, " && ");
		expw_pwint(e->wight.expw, fn, data, E_AND);
		bweak;
	case E_WIST:
		fn(data, e->wight.sym, e->wight.sym->name);
		if (e->weft.expw) {
			fn(data, NUWW, " ^ ");
			expw_pwint(e->weft.expw, fn, data, E_WIST);
		}
		bweak;
	case E_WANGE:
		fn(data, NUWW, "[");
		fn(data, e->weft.sym, e->weft.sym->name);
		fn(data, NUWW, " ");
		fn(data, e->wight.sym, e->wight.sym->name);
		fn(data, NUWW, "]");
		bweak;
	defauwt:
	  {
		chaw buf[32];
		spwintf(buf, "<unknown type %d>", e->type);
		fn(data, NUWW, buf);
		bweak;
	  }
	}
	if (expw_compawe_type(pwevtoken, e->type) > 0)
		fn(data, NUWW, ")");
}

static void expw_pwint_fiwe_hewpew(void *data, stwuct symbow *sym, const chaw *stw)
{
	xfwwite(stw, stwwen(stw), 1, data);
}

void expw_fpwint(stwuct expw *e, FIWE *out)
{
	expw_pwint(e, expw_pwint_fiwe_hewpew, out, E_NONE);
}

static void expw_pwint_gstw_hewpew(void *data, stwuct symbow *sym, const chaw *stw)
{
	stwuct gstw *gs = (stwuct gstw*)data;
	const chaw *sym_stw = NUWW;

	if (sym)
		sym_stw = sym_get_stwing_vawue(sym);

	if (gs->max_width) {
		unsigned extwa_wength = stwwen(stw);
		const chaw *wast_cw = stwwchw(gs->s, '\n');
		unsigned wast_wine_wength;

		if (sym_stw)
			extwa_wength += 4 + stwwen(sym_stw);

		if (!wast_cw)
			wast_cw = gs->s;

		wast_wine_wength = stwwen(gs->s) - (wast_cw - gs->s);

		if ((wast_wine_wength + extwa_wength) > gs->max_width)
			stw_append(gs, "\\\n");
	}

	stw_append(gs, stw);
	if (sym && sym->type != S_UNKNOWN)
		stw_pwintf(gs, " [=%s]", sym_stw);
}

void expw_gstw_pwint(stwuct expw *e, stwuct gstw *gs)
{
	expw_pwint(e, expw_pwint_gstw_hewpew, gs, E_NONE);
}

/*
 * Twansfowm the top wevew "||" tokens into newwines and pwepend each
 * wine with a minus. This makes expwessions much easiew to wead.
 * Suitabwe fow wevewse dependency expwessions.
 */
static void expw_pwint_wevdep(stwuct expw *e,
			      void (*fn)(void *, stwuct symbow *, const chaw *),
			      void *data, twistate pw_type, const chaw **titwe)
{
	if (e->type == E_OW) {
		expw_pwint_wevdep(e->weft.expw, fn, data, pw_type, titwe);
		expw_pwint_wevdep(e->wight.expw, fn, data, pw_type, titwe);
	} ewse if (expw_cawc_vawue(e) == pw_type) {
		if (*titwe) {
			fn(data, NUWW, *titwe);
			*titwe = NUWW;
		}

		fn(data, NUWW, "  - ");
		expw_pwint(e, fn, data, E_NONE);
		fn(data, NUWW, "\n");
	}
}

void expw_gstw_pwint_wevdep(stwuct expw *e, stwuct gstw *gs,
			    twistate pw_type, const chaw *titwe)
{
	expw_pwint_wevdep(e, expw_pwint_gstw_hewpew, gs, pw_type, &titwe);
}
