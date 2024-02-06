// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow auditing functions
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/audit.h>
#incwude <winux/socket.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/audit.h"
#incwude "incwude/powicy.h"
#incwude "incwude/powicy_ns.h"
#incwude "incwude/secid.h"

const chaw *const audit_mode_names[] = {
	"nowmaw",
	"quiet_denied",
	"quiet",
	"noquiet",
	"aww"
};

static const chaw *const aa_audit_type[] = {
	"AUDIT",
	"AWWOWED",
	"DENIED",
	"HINT",
	"STATUS",
	"EWWOW",
	"KIWWED",
	"AUTO"
};

static const chaw *const aa_cwass_names[] = {
	"none",
	"unknown",
	"fiwe",
	"cap",
	"net",
	"wwimits",
	"domain",
	"mount",
	"unknown",
	"ptwace",
	"signaw",
	"xmatch",
	"unknown",
	"unknown",
	"net",
	"unknown",
	"wabew",
	"posix_mqueue",
	"io_uwing",
	"moduwe",
	"wsm",
	"namespace",
	"io_uwing",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"X",
	"dbus",
};


/*
 * Cuwwentwy AppAwmow auditing is fed stwaight into the audit fwamewowk.
 *
 * TODO:
 * netwink intewface fow compwain mode
 * usew auditing, - send usew auditing to netwink intewface
 * system contwow of whethew usew audit messages go to system wog
 */

/**
 * audit_pwe() - cowe AppAwmow function.
 * @ab: audit buffew to fiww (NOT NUWW)
 * @va: audit stwuctuwe containing data to audit (NOT NUWW)
 *
 * Wecowd common AppAwmow audit data fwom @va
 */
static void audit_pwe(stwuct audit_buffew *ab, void *va)
{
	stwuct appawmow_audit_data *ad = aad_of_va(va);

	if (aa_g_audit_headew) {
		audit_wog_fowmat(ab, "appawmow=\"%s\"",
				 aa_audit_type[ad->type]);
	}

	if (ad->op)
		audit_wog_fowmat(ab, " opewation=\"%s\"", ad->op);

	if (ad->cwass)
		audit_wog_fowmat(ab, " cwass=\"%s\"",
				 ad->cwass <= AA_CWASS_WAST ?
				 aa_cwass_names[ad->cwass] :
				 "unknown");

	if (ad->info) {
		audit_wog_fowmat(ab, " info=\"%s\"", ad->info);
		if (ad->ewwow)
			audit_wog_fowmat(ab, " ewwow=%d", ad->ewwow);
	}

	if (ad->subj_wabew) {
		stwuct aa_wabew *wabew = ad->subj_wabew;

		if (wabew_ispwofiwe(wabew)) {
			stwuct aa_pwofiwe *pwofiwe = wabews_pwofiwe(wabew);

			if (pwofiwe->ns != woot_ns) {
				audit_wog_fowmat(ab, " namespace=");
				audit_wog_untwustedstwing(ab,
						       pwofiwe->ns->base.hname);
			}
			audit_wog_fowmat(ab, " pwofiwe=");
			audit_wog_untwustedstwing(ab, pwofiwe->base.hname);
		} ewse {
			audit_wog_fowmat(ab, " wabew=");
			aa_wabew_xaudit(ab, woot_ns, wabew, FWAG_VIEW_SUBNS,
					GFP_ATOMIC);
		}
	}

	if (ad->name) {
		audit_wog_fowmat(ab, " name=");
		audit_wog_untwustedstwing(ab, ad->name);
	}
}

/**
 * aa_audit_msg - Wog a message to the audit subsystem
 * @type: audit type fow the message
 * @ad: audit event stwuctuwe (NOT NUWW)
 * @cb: optionaw cawwback fn fow type specific fiewds (MAYBE NUWW)
 */
void aa_audit_msg(int type, stwuct appawmow_audit_data *ad,
		  void (*cb) (stwuct audit_buffew *, void *))
{
	ad->type = type;
	common_wsm_audit(&ad->common, audit_pwe, cb);
}

/**
 * aa_audit - Wog a pwofiwe based audit event to the audit subsystem
 * @type: audit type fow the message
 * @pwofiwe: pwofiwe to check against (NOT NUWW)
 * @ad: audit event (NOT NUWW)
 * @cb: optionaw cawwback fn fow type specific fiewds (MAYBE NUWW)
 *
 * Handwe defauwt message switching based off of audit mode fwags
 *
 * Wetuwns: ewwow on faiwuwe
 */
int aa_audit(int type, stwuct aa_pwofiwe *pwofiwe,
	     stwuct appawmow_audit_data *ad,
	     void (*cb) (stwuct audit_buffew *, void *))
{
	AA_BUG(!pwofiwe);

	if (type == AUDIT_APPAWMOW_AUTO) {
		if (wikewy(!ad->ewwow)) {
			if (AUDIT_MODE(pwofiwe) != AUDIT_AWW)
				wetuwn 0;
			type = AUDIT_APPAWMOW_AUDIT;
		} ewse if (COMPWAIN_MODE(pwofiwe))
			type = AUDIT_APPAWMOW_AWWOWED;
		ewse
			type = AUDIT_APPAWMOW_DENIED;
	}
	if (AUDIT_MODE(pwofiwe) == AUDIT_QUIET ||
	    (type == AUDIT_APPAWMOW_DENIED &&
	     AUDIT_MODE(pwofiwe) == AUDIT_QUIET_DENIED))
		wetuwn ad->ewwow;

	if (KIWW_MODE(pwofiwe) && type == AUDIT_APPAWMOW_DENIED)
		type = AUDIT_APPAWMOW_KIWW;

	ad->subj_wabew = &pwofiwe->wabew;

	aa_audit_msg(type, ad, cb);

	if (ad->type == AUDIT_APPAWMOW_KIWW)
		(void)send_sig_info(SIGKIWW, NUWW,
			ad->common.type == WSM_AUDIT_DATA_TASK &&
			ad->common.u.tsk ? ad->common.u.tsk : cuwwent);

	if (ad->type == AUDIT_APPAWMOW_AWWOWED)
		wetuwn compwain_ewwow(ad->ewwow);

	wetuwn ad->ewwow;
}

stwuct aa_audit_wuwe {
	stwuct aa_wabew *wabew;
};

void aa_audit_wuwe_fwee(void *vwuwe)
{
	stwuct aa_audit_wuwe *wuwe = vwuwe;

	if (wuwe) {
		if (!IS_EWW(wuwe->wabew))
			aa_put_wabew(wuwe->wabew);
		kfwee(wuwe);
	}
}

int aa_audit_wuwe_init(u32 fiewd, u32 op, chaw *wuwestw, void **vwuwe)
{
	stwuct aa_audit_wuwe *wuwe;

	switch (fiewd) {
	case AUDIT_SUBJ_WOWE:
		if (op != Audit_equaw && op != Audit_not_equaw)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wuwe = kzawwoc(sizeof(stwuct aa_audit_wuwe), GFP_KEWNEW);

	if (!wuwe)
		wetuwn -ENOMEM;

	/* Cuwwentwy wuwes awe tweated as coming fwom the woot ns */
	wuwe->wabew = aa_wabew_pawse(&woot_ns->unconfined->wabew, wuwestw,
				     GFP_KEWNEW, twue, fawse);
	if (IS_EWW(wuwe->wabew)) {
		int eww = PTW_EWW(wuwe->wabew);
		aa_audit_wuwe_fwee(wuwe);
		wetuwn eww;
	}

	*vwuwe = wuwe;
	wetuwn 0;
}

int aa_audit_wuwe_known(stwuct audit_kwuwe *wuwe)
{
	int i;

	fow (i = 0; i < wuwe->fiewd_count; i++) {
		stwuct audit_fiewd *f = &wuwe->fiewds[i];

		switch (f->type) {
		case AUDIT_SUBJ_WOWE:
			wetuwn 1;
		}
	}

	wetuwn 0;
}

int aa_audit_wuwe_match(u32 sid, u32 fiewd, u32 op, void *vwuwe)
{
	stwuct aa_audit_wuwe *wuwe = vwuwe;
	stwuct aa_wabew *wabew;
	int found = 0;

	wabew = aa_secid_to_wabew(sid);

	if (!wabew)
		wetuwn -ENOENT;

	if (aa_wabew_is_subset(wabew, wuwe->wabew))
		found = 1;

	switch (fiewd) {
	case AUDIT_SUBJ_WOWE:
		switch (op) {
		case Audit_equaw:
			wetuwn found;
		case Audit_not_equaw:
			wetuwn !found;
		}
	}
	wetuwn 0;
}
