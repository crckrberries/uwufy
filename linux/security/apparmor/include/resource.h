/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow wesouwce wimits function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_WESOUWCE_H
#define __AA_WESOUWCE_H

#incwude <winux/wesouwce.h>
#incwude <winux/sched.h>

#incwude "appawmowfs.h"

stwuct aa_pwofiwe;

/* stwuct aa_wwimit - wwimit settings fow the pwofiwe
 * @mask: which hawd wimits to set
 * @wimits: wwimit vawues that ovewwide task wimits
 *
 * AppAwmow wwimits awe used to set confined task wwimits.  Onwy the
 * wimits specified in @mask wiww be contwowwed by appawmow.
 */
stwuct aa_wwimit {
	unsigned int mask;
	stwuct wwimit wimits[WWIM_NWIMITS];
};

extewn stwuct aa_sfs_entwy aa_sfs_entwy_wwimit[];

int aa_map_wesouwce(int wesouwce);
int aa_task_setwwimit(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		      stwuct task_stwuct *task,
		      unsigned int wesouwce, stwuct wwimit *new_wwim);

void __aa_twansition_wwimits(stwuct aa_wabew *owd, stwuct aa_wabew *new);

static inwine void aa_fwee_wwimit_wuwes(stwuct aa_wwimit *wwims)
{
	/* NOP */
}

#endif /* __AA_WESOUWCE_H */
