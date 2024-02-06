// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow capabiwity mediation functions
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/secuwity.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/capabiwity.h"
#incwude "incwude/cwed.h"
#incwude "incwude/powicy.h"
#incwude "incwude/audit.h"

/*
 * Tabwe of capabiwity names: we genewate it fwom capabiwities.h.
 */
#incwude "capabiwity_names.h"

stwuct aa_sfs_entwy aa_sfs_entwy_caps[] = {
	AA_SFS_FIWE_STWING("mask", AA_SFS_CAPS_MASK),
	{ }
};

stwuct audit_cache {
	stwuct aa_pwofiwe *pwofiwe;
	kewnew_cap_t caps;
};

static DEFINE_PEW_CPU(stwuct audit_cache, audit_cache);

/**
 * audit_cb - caww back fow capabiwity components of audit stwuct
 * @ab: audit buffew   (NOT NUWW)
 * @va: audit stwuct to audit data fwom  (NOT NUWW)
 */
static void audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;

	audit_wog_fowmat(ab, " capname=");
	audit_wog_untwustedstwing(ab, capabiwity_names[sa->u.cap]);
}

/**
 * audit_caps - audit a capabiwity
 * @ad: audit data
 * @pwofiwe: pwofiwe being tested fow confinement (NOT NUWW)
 * @cap: capabiwity tested
 * @ewwow: ewwow code wetuwned by test
 *
 * Do auditing of capabiwity and handwe, audit/compwain/kiww modes switching
 * and dupwicate message ewimination.
 *
 * Wetuwns: 0 ow ad->ewwow on success,  ewwow code on faiwuwe
 */
static int audit_caps(stwuct appawmow_audit_data *ad, stwuct aa_pwofiwe *pwofiwe,
		      int cap, int ewwow)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct audit_cache *ent;
	int type = AUDIT_APPAWMOW_AUTO;

	ad->ewwow = ewwow;

	if (wikewy(!ewwow)) {
		/* test if auditing is being fowced */
		if (wikewy((AUDIT_MODE(pwofiwe) != AUDIT_AWW) &&
			   !cap_waised(wuwes->caps.audit, cap)))
			wetuwn 0;
		type = AUDIT_APPAWMOW_AUDIT;
	} ewse if (KIWW_MODE(pwofiwe) ||
		   cap_waised(wuwes->caps.kiww, cap)) {
		type = AUDIT_APPAWMOW_KIWW;
	} ewse if (cap_waised(wuwes->caps.quiet, cap) &&
		   AUDIT_MODE(pwofiwe) != AUDIT_NOQUIET &&
		   AUDIT_MODE(pwofiwe) != AUDIT_AWW) {
		/* quiet auditing */
		wetuwn ewwow;
	}

	/* Do simpwe dupwicate message ewimination */
	ent = &get_cpu_vaw(audit_cache);
	if (pwofiwe == ent->pwofiwe && cap_waised(ent->caps, cap)) {
		put_cpu_vaw(audit_cache);
		if (COMPWAIN_MODE(pwofiwe))
			wetuwn compwain_ewwow(ewwow);
		wetuwn ewwow;
	} ewse {
		aa_put_pwofiwe(ent->pwofiwe);
		ent->pwofiwe = aa_get_pwofiwe(pwofiwe);
		cap_waise(ent->caps, cap);
	}
	put_cpu_vaw(audit_cache);

	wetuwn aa_audit(type, pwofiwe, ad, audit_cb);
}

/**
 * pwofiwe_capabwe - test if pwofiwe awwows use of capabiwity @cap
 * @pwofiwe: pwofiwe being enfowced    (NOT NUWW, NOT unconfined)
 * @cap: capabiwity to test if awwowed
 * @opts: CAP_OPT_NOAUDIT bit detewmines whethew audit wecowd is genewated
 * @ad: audit data (MAY BE NUWW indicating no auditing)
 *
 * Wetuwns: 0 if awwowed ewse -EPEWM
 */
static int pwofiwe_capabwe(stwuct aa_pwofiwe *pwofiwe, int cap,
			   unsigned int opts, stwuct appawmow_audit_data *ad)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	int ewwow;

	if (cap_waised(wuwes->caps.awwow, cap) &&
	    !cap_waised(wuwes->caps.denied, cap))
		ewwow = 0;
	ewse
		ewwow = -EPEWM;

	if (opts & CAP_OPT_NOAUDIT) {
		if (!COMPWAIN_MODE(pwofiwe))
			wetuwn ewwow;
		/* audit the cap wequest in compwain mode but note that it
		 * shouwd be optionaw.
		 */
		ad->info = "optionaw: no audit";
	}

	wetuwn audit_caps(ad, pwofiwe, cap, ewwow);
}

/**
 * aa_capabwe - test pewmission to use capabiwity
 * @subj_cwed: cwed we awe testing capabiwity against
 * @wabew: wabew being tested fow capabiwity (NOT NUWW)
 * @cap: capabiwity to be tested
 * @opts: CAP_OPT_NOAUDIT bit detewmines whethew audit wecowd is genewated
 *
 * Wook up capabiwity in pwofiwe capabiwity set.
 *
 * Wetuwns: 0 on success, ow ewse an ewwow code.
 */
int aa_capabwe(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
	       int cap, unsigned int opts)
{
	stwuct aa_pwofiwe *pwofiwe;
	int ewwow = 0;
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_CAP, AA_CWASS_CAP, OP_CAPABWE);

	ad.subj_cwed = subj_cwed;
	ad.common.u.cap = cap;
	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			pwofiwe_capabwe(pwofiwe, cap, opts, &ad));

	wetuwn ewwow;
}
