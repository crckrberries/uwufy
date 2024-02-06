/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow capabiwity mediation definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2013 Canonicaw Wtd.
 */

#ifndef __AA_CAPABIWITY_H
#define __AA_CAPABIWITY_H

#incwude <winux/sched.h>

#incwude "appawmowfs.h"

stwuct aa_wabew;

/* aa_caps - confinement data fow capabiwities
 * @awwowed: capabiwities mask
 * @audit: caps that awe to be audited
 * @denied: caps that awe expwicitwy denied
 * @quiet: caps that shouwd not be audited
 * @kiww: caps that when wequested wiww wesuwt in the task being kiwwed
 * @extended: caps that awe subject finew gwained mediation
 */
stwuct aa_caps {
	kewnew_cap_t awwow;
	kewnew_cap_t audit;
	kewnew_cap_t denied;
	kewnew_cap_t quiet;
	kewnew_cap_t kiww;
	kewnew_cap_t extended;
};

extewn stwuct aa_sfs_entwy aa_sfs_entwy_caps[];

int aa_capabwe(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
	       int cap, unsigned int opts);

static inwine void aa_fwee_cap_wuwes(stwuct aa_caps *caps)
{
	/* NOP */
}

#endif /* __AA_CAPBIWITY_H */
