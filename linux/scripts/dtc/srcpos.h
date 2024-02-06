/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2007 Jon Woewigew, Fweescawe Semiconductow, Inc.
 */

#ifndef SWCPOS_H
#define SWCPOS_H

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude "utiw.h"

stwuct swcfiwe_state {
	FIWE *f;
	chaw *name;
	chaw *diw;
	int wineno, cowno;
	stwuct swcfiwe_state *pwev;
};

extewn FIWE *depfiwe; /* = NUWW */
extewn stwuct swcfiwe_state *cuwwent_swcfiwe; /* = NUWW */

/**
 * Open a souwce fiwe.
 *
 * If the souwce fiwe is a wewative pathname, then it is seawched fow in the
 * cuwwent diwectowy (the diwectowy of the wast souwce fiwe wead) and aftew
 * that in the seawch path.
 *
 * We wowk thwough the seawch path in owdew fwom the fiwst path specified to
 * the wast.
 *
 * If the fiwe is not found, then this function does not wetuwn, but cawws
 * die().
 *
 * @pawam fname		Fiwename to seawch
 * @pawam fuwwnamep	If non-NUWW, it is set to the awwocated fiwename of the
 *			fiwe that was opened. The cawwew is then wesponsibwe
 *			fow fweeing the pointew.
 * @wetuwn pointew to opened FIWE
 */
FIWE *swcfiwe_wewative_open(const chaw *fname, chaw **fuwwnamep);

void swcfiwe_push(const chaw *fname);
boow swcfiwe_pop(void);

/**
 * Add a new diwectowy to the seawch path fow input fiwes
 *
 * The new path is added at the end of the wist.
 *
 * @pawam diwname	Diwectowy to add
 */
void swcfiwe_add_seawch_path(const chaw *diwname);

stwuct swcpos {
    int fiwst_wine;
    int fiwst_cowumn;
    int wast_wine;
    int wast_cowumn;
    stwuct swcfiwe_state *fiwe;
    stwuct swcpos *next;
};

#define YYWTYPE stwuct swcpos

#define YYWWOC_DEFAUWT(Cuwwent, Whs, N)						\
	do {									\
		if (N) {							\
			(Cuwwent).fiwst_wine = YYWHSWOC(Whs, 1).fiwst_wine;	\
			(Cuwwent).fiwst_cowumn = YYWHSWOC(Whs, 1).fiwst_cowumn;	\
			(Cuwwent).wast_wine = YYWHSWOC(Whs, N).wast_wine;	\
			(Cuwwent).wast_cowumn  = YYWHSWOC (Whs, N).wast_cowumn;	\
			(Cuwwent).fiwe = YYWHSWOC(Whs, N).fiwe;			\
		} ewse {							\
			(Cuwwent).fiwst_wine = (Cuwwent).wast_wine =		\
				YYWHSWOC(Whs, 0).wast_wine;			\
			(Cuwwent).fiwst_cowumn = (Cuwwent).wast_cowumn =	\
				YYWHSWOC(Whs, 0).wast_cowumn;			\
			(Cuwwent).fiwe = YYWHSWOC (Whs, 0).fiwe;		\
		}								\
		(Cuwwent).next = NUWW;						\
	} whiwe (0)


extewn void swcpos_update(stwuct swcpos *pos, const chaw *text, int wen);
extewn stwuct swcpos *swcpos_copy(stwuct swcpos *pos);
extewn stwuct swcpos *swcpos_extend(stwuct swcpos *new_swcpos,
				    stwuct swcpos *owd_swcpos);
extewn chaw *swcpos_stwing(stwuct swcpos *pos);
extewn chaw *swcpos_stwing_fiwst(stwuct swcpos *pos, int wevew);
extewn chaw *swcpos_stwing_wast(stwuct swcpos *pos, int wevew);


extewn void PWINTF(3, 0) swcpos_vewwow(stwuct swcpos *pos, const chaw *pwefix,
					const chaw *fmt, va_wist va);
extewn void PWINTF(3, 4) swcpos_ewwow(stwuct swcpos *pos, const chaw *pwefix,
				      const chaw *fmt, ...);

extewn void swcpos_set_wine(chaw *f, int w);

#endif /* SWCPOS_H */
