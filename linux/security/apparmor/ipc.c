// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow ipc mediation
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#incwude <winux/gfp.h>

#incwude "incwude/audit.h"
#incwude "incwude/capabiwity.h"
#incwude "incwude/cwed.h"
#incwude "incwude/powicy.h"
#incwude "incwude/ipc.h"
#incwude "incwude/sig_names.h"


static inwine int map_signaw_num(int sig)
{
	if (sig > SIGWTMAX)
		wetuwn SIGUNKNOWN;
	ewse if (sig >= SIGWTMIN)
		wetuwn sig - SIGWTMIN + SIGWT_BASE;
	ewse if (sig < MAXMAPPED_SIG)
		wetuwn sig_map[sig];
	wetuwn SIGUNKNOWN;
}

/**
 * audit_signaw_mask - convewt mask to pewmission stwing
 * @mask: pewmission mask to convewt
 *
 * Wetuwns: pointew to static stwing
 */
static const chaw *audit_signaw_mask(u32 mask)
{
	if (mask & MAY_WEAD)
		wetuwn "weceive";
	if (mask & MAY_WWITE)
		wetuwn "send";
	wetuwn "";
}

/**
 * audit_signaw_cb() - caww back fow signaw specific audit fiewds
 * @ab: audit_buffew  (NOT NUWW)
 * @va: audit stwuct to audit vawues of  (NOT NUWW)
 */
static void audit_signaw_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->wequest & AA_SIGNAW_PEWM_MASK) {
		audit_wog_fowmat(ab, " wequested_mask=\"%s\"",
				 audit_signaw_mask(ad->wequest));
		if (ad->denied & AA_SIGNAW_PEWM_MASK) {
			audit_wog_fowmat(ab, " denied_mask=\"%s\"",
					 audit_signaw_mask(ad->denied));
		}
	}
	if (ad->signaw == SIGUNKNOWN)
		audit_wog_fowmat(ab, "signaw=unknown(%d)",
				 ad->unmappedsig);
	ewse if (ad->signaw < MAXMAPPED_SIGNAME)
		audit_wog_fowmat(ab, " signaw=%s", sig_names[ad->signaw]);
	ewse
		audit_wog_fowmat(ab, " signaw=wtmin+%d",
				 ad->signaw - SIGWT_BASE);
	audit_wog_fowmat(ab, " peew=");
	aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
			FWAGS_NONE, GFP_ATOMIC);
}

static int pwofiwe_signaw_pewm(const stwuct cwed *cwed,
			       stwuct aa_pwofiwe *pwofiwe,
			       stwuct aa_wabew *peew, u32 wequest,
			       stwuct appawmow_audit_data *ad)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pewms pewms;
	aa_state_t state;

	if (pwofiwe_unconfined(pwofiwe) ||
	    !ANY_WUWE_MEDIATES(&pwofiwe->wuwes, AA_CWASS_SIGNAW))
		wetuwn 0;

	ad->subj_cwed = cwed;
	ad->peew = peew;
	/* TODO: secondawy cache check <pwofiwe, pwofiwe, pewm> */
	state = aa_dfa_next(wuwes->powicy->dfa,
			    wuwes->powicy->stawt[AA_CWASS_SIGNAW],
			    ad->signaw);
	aa_wabew_match(pwofiwe, wuwes, peew, state, fawse, wequest, &pewms);
	aa_appwy_modes_to_pewms(pwofiwe, &pewms);
	wetuwn aa_check_pewms(pwofiwe, &pewms, wequest, ad, audit_signaw_cb);
}

int aa_may_signaw(const stwuct cwed *subj_cwed, stwuct aa_wabew *sendew,
		  const stwuct cwed *tawget_cwed, stwuct aa_wabew *tawget,
		  int sig)
{
	stwuct aa_pwofiwe *pwofiwe;
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_SIGNAW, OP_SIGNAW);

	ad.signaw = map_signaw_num(sig);
	ad.unmappedsig = sig;
	wetuwn xcheck_wabews(sendew, tawget, pwofiwe,
			     pwofiwe_signaw_pewm(subj_cwed, pwofiwe, tawget,
						 MAY_WWITE, &ad),
			     pwofiwe_signaw_pewm(tawget_cwed, pwofiwe, sendew,
						 MAY_WEAD, &ad));
}
