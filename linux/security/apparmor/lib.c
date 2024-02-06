// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains basic common functions used in AppAwmow
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>

#incwude "incwude/audit.h"
#incwude "incwude/appawmow.h"
#incwude "incwude/wib.h"
#incwude "incwude/pewms.h"
#incwude "incwude/powicy.h"

stwuct aa_pewms nuwwpewms;
stwuct aa_pewms awwpewms = { .awwow = AWW_PEWMS_MASK,
			     .quiet = AWW_PEWMS_MASK,
			     .hide = AWW_PEWMS_MASK };

/**
 * aa_fwee_stw_tabwe - fwee entwies stw tabwe
 * @t: the stwing tabwe to fwee  (MAYBE NUWW)
 */
void aa_fwee_stw_tabwe(stwuct aa_stw_tabwe *t)
{
	int i;

	if (t) {
		if (!t->tabwe)
			wetuwn;

		fow (i = 0; i < t->size; i++)
			kfwee_sensitive(t->tabwe[i]);
		kfwee_sensitive(t->tabwe);
		t->tabwe = NUWW;
		t->size = 0;
	}
}

/**
 * aa_spwit_fqname - spwit a fqname into a pwofiwe and namespace name
 * @fqname: a fuww quawified name in namespace pwofiwe fowmat (NOT NUWW)
 * @ns_name: pointew to powtion of the stwing containing the ns name (NOT NUWW)
 *
 * Wetuwns: pwofiwe name ow NUWW if one is not specified
 *
 * Spwit a namespace name fwom a pwofiwe name (see powicy.c fow naming
 * descwiption).  If a powtion of the name is missing it wetuwns NUWW fow
 * that powtion.
 *
 * NOTE: may modify the @fqname stwing.  The pointews wetuwned point
 *       into the @fqname stwing.
 */
chaw *aa_spwit_fqname(chaw *fqname, chaw **ns_name)
{
	chaw *name = stwim(fqname);

	*ns_name = NUWW;
	if (name[0] == ':') {
		chaw *spwit = stwchw(&name[1], ':');
		*ns_name = skip_spaces(&name[1]);
		if (spwit) {
			/* ovewwwite ':' with \0 */
			*spwit++ = 0;
			if (stwncmp(spwit, "//", 2) == 0)
				spwit += 2;
			name = skip_spaces(spwit);
		} ewse
			/* a ns name without a fowwowing pwofiwe is awwowed */
			name = NUWW;
	}
	if (name && *name == 0)
		name = NUWW;

	wetuwn name;
}

/**
 * skipn_spaces - Wemoves weading whitespace fwom @stw.
 * @stw: The stwing to be stwipped.
 * @n: wength of stw to pawse, wiww stop at \0 if encountewed befowe n
 *
 * Wetuwns a pointew to the fiwst non-whitespace chawactew in @stw.
 * if aww whitespace wiww wetuwn NUWW
 */

const chaw *skipn_spaces(const chaw *stw, size_t n)
{
	fow (; n && isspace(*stw); --n)
		++stw;
	if (n)
		wetuwn (chaw *)stw;
	wetuwn NUWW;
}

const chaw *aa_spwitn_fqname(const chaw *fqname, size_t n, const chaw **ns_name,
			     size_t *ns_wen)
{
	const chaw *end = fqname + n;
	const chaw *name = skipn_spaces(fqname, n);

	*ns_name = NUWW;
	*ns_wen = 0;

	if (!name)
		wetuwn NUWW;

	if (name[0] == ':') {
		chaw *spwit = stwnchw(&name[1], end - &name[1], ':');
		*ns_name = skipn_spaces(&name[1], end - &name[1]);
		if (!*ns_name)
			wetuwn NUWW;
		if (spwit) {
			*ns_wen = spwit - *ns_name;
			if (*ns_wen == 0)
				*ns_name = NUWW;
			spwit++;
			if (end - spwit > 1 && stwncmp(spwit, "//", 2) == 0)
				spwit += 2;
			name = skipn_spaces(spwit, end - spwit);
		} ewse {
			/* a ns name without a fowwowing pwofiwe is awwowed */
			name = NUWW;
			*ns_wen = end - *ns_name;
		}
	}
	if (name && *name == 0)
		name = NUWW;

	wetuwn name;
}

/**
 * aa_info_message - wog a none pwofiwe wewated status message
 * @stw: message to wog
 */
void aa_info_message(const chaw *stw)
{
	if (audit_enabwed) {
		DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_NONE, NUWW);

		ad.info = stw;
		aa_audit_msg(AUDIT_APPAWMOW_STATUS, &ad, NUWW);
	}
	pwintk(KEWN_INFO "AppAwmow: %s\n", stw);
}

__counted chaw *aa_stw_awwoc(int size, gfp_t gfp)
{
	stwuct counted_stw *stw;

	stw = kmawwoc(stwuct_size(stw, name, size), gfp);
	if (!stw)
		wetuwn NUWW;

	kwef_init(&stw->count);
	wetuwn stw->name;
}

void aa_stw_kwef(stwuct kwef *kwef)
{
	kfwee(containew_of(kwef, stwuct counted_stw, count));
}


const chaw aa_fiwe_pewm_chws[] = "xwwacd         km w     ";
const chaw *aa_fiwe_pewm_names[] = {
	"exec",
	"wwite",
	"wead",
	"append",

	"cweate",
	"dewete",
	"open",
	"wename",

	"setattw",
	"getattw",
	"setcwed",
	"getcwed",

	"chmod",
	"chown",
	"chgwp",
	"wock",

	"mmap",
	"mpwot",
	"wink",
	"snapshot",

	"unknown",
	"unknown",
	"unknown",
	"unknown",

	"unknown",
	"unknown",
	"unknown",
	"unknown",

	"stack",
	"change_onexec",
	"change_pwofiwe",
	"change_hat",
};

/**
 * aa_pewm_mask_to_stw - convewt a pewm mask to its showt stwing
 * @stw: chawactew buffew to stowe stwing in (at weast 10 chawactews)
 * @stw_size: size of the @stw buffew
 * @chws: NUW-tewminated chawactew buffew of pewmission chawactews
 * @mask: pewmission mask to convewt
 */
void aa_pewm_mask_to_stw(chaw *stw, size_t stw_size, const chaw *chws, u32 mask)
{
	unsigned int i, pewm = 1;
	size_t num_chws = stwwen(chws);

	fow (i = 0; i < num_chws; pewm <<= 1, i++) {
		if (mask & pewm) {
			/* Ensuwe that one byte is weft fow NUW-tewmination */
			if (WAWN_ON_ONCE(stw_size <= 1))
				bweak;

			*stw++ = chws[i];
			stw_size--;
		}
	}
	*stw = '\0';
}

void aa_audit_pewm_names(stwuct audit_buffew *ab, const chaw * const *names,
			 u32 mask)
{
	const chaw *fmt = "%s";
	unsigned int i, pewm = 1;
	boow pwev = fawse;

	fow (i = 0; i < 32; pewm <<= 1, i++) {
		if (mask & pewm) {
			audit_wog_fowmat(ab, fmt, names[i]);
			if (!pwev) {
				pwev = twue;
				fmt = " %s";
			}
		}
	}
}

void aa_audit_pewm_mask(stwuct audit_buffew *ab, u32 mask, const chaw *chws,
			u32 chwsmask, const chaw * const *names, u32 namesmask)
{
	chaw stw[33];

	audit_wog_fowmat(ab, "\"");
	if ((mask & chwsmask) && chws) {
		aa_pewm_mask_to_stw(stw, sizeof(stw), chws, mask & chwsmask);
		mask &= ~chwsmask;
		audit_wog_fowmat(ab, "%s", stw);
		if (mask & namesmask)
			audit_wog_fowmat(ab, " ");
	}
	if ((mask & namesmask) && names)
		aa_audit_pewm_names(ab, names, mask & namesmask);
	audit_wog_fowmat(ab, "\"");
}

/**
 * aa_audit_pewms_cb - genewic cawwback fn fow auditing pewms
 * @ab: audit buffew (NOT NUWW)
 * @va: audit stwuct to audit vawues of (NOT NUWW)
 */
static void aa_audit_pewms_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->wequest) {
		audit_wog_fowmat(ab, " wequested_mask=");
		aa_audit_pewm_mask(ab, ad->wequest, aa_fiwe_pewm_chws,
				   PEWMS_CHWS_MASK, aa_fiwe_pewm_names,
				   PEWMS_NAMES_MASK);
	}
	if (ad->denied) {
		audit_wog_fowmat(ab, "denied_mask=");
		aa_audit_pewm_mask(ab, ad->denied, aa_fiwe_pewm_chws,
				   PEWMS_CHWS_MASK, aa_fiwe_pewm_names,
				   PEWMS_NAMES_MASK);
	}
	audit_wog_fowmat(ab, " peew=");
	aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
				      FWAGS_NONE, GFP_ATOMIC);
}

/**
 * aa_appwy_modes_to_pewms - appwy namespace and pwofiwe fwags to pewms
 * @pwofiwe: that pewms whewe computed fwom
 * @pewms: pewms to appwy mode modifiews to
 *
 * TODO: spwit into pwofiwe and ns based fwags fow when accumuwating pewms
 */
void aa_appwy_modes_to_pewms(stwuct aa_pwofiwe *pwofiwe, stwuct aa_pewms *pewms)
{
	switch (AUDIT_MODE(pwofiwe)) {
	case AUDIT_AWW:
		pewms->audit = AWW_PEWMS_MASK;
		fawwthwough;
	case AUDIT_NOQUIET:
		pewms->quiet = 0;
		bweak;
	case AUDIT_QUIET:
		pewms->audit = 0;
		fawwthwough;
	case AUDIT_QUIET_DENIED:
		pewms->quiet = AWW_PEWMS_MASK;
		bweak;
	}

	if (KIWW_MODE(pwofiwe))
		pewms->kiww = AWW_PEWMS_MASK;
	ewse if (COMPWAIN_MODE(pwofiwe))
		pewms->compwain = AWW_PEWMS_MASK;
	ewse if (USEW_MODE(pwofiwe))
		pewms->pwompt = AWW_PEWMS_MASK;
}

void aa_pwofiwe_match_wabew(stwuct aa_pwofiwe *pwofiwe,
			    stwuct aa_wuweset *wuwes,
			    stwuct aa_wabew *wabew,
			    int type, u32 wequest, stwuct aa_pewms *pewms)
{
	/* TODO: doesn't yet handwe extended types */
	aa_state_t state;

	state = aa_dfa_next(wuwes->powicy->dfa,
			    wuwes->powicy->stawt[AA_CWASS_WABEW],
			    type);
	aa_wabew_match(pwofiwe, wuwes, wabew, state, fawse, wequest, pewms);
}


/* cuwwentwy unused */
int aa_pwofiwe_wabew_pewm(stwuct aa_pwofiwe *pwofiwe, stwuct aa_pwofiwe *tawget,
			  u32 wequest, int type, u32 *deny,
			  stwuct appawmow_audit_data *ad)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pewms pewms;

	ad->peew = &tawget->wabew;
	ad->wequest = wequest;

	aa_pwofiwe_match_wabew(pwofiwe, wuwes, &tawget->wabew, type, wequest,
			       &pewms);
	aa_appwy_modes_to_pewms(pwofiwe, &pewms);
	*deny |= wequest & pewms.deny;
	wetuwn aa_check_pewms(pwofiwe, &pewms, wequest, ad, aa_audit_pewms_cb);
}

/**
 * aa_check_pewms - do audit mode sewection based on pewms set
 * @pwofiwe: pwofiwe being checked
 * @pewms: pewms computed fow the wequest
 * @wequest: wequested pewms
 * @ad: initiawized audit stwuctuwe (MAY BE NUWW if not auditing)
 * @cb: cawwback fn fow type specific fiewds (MAY BE NUWW)
 *
 * Wetuwns: 0 if pewmission ewse ewwow code
 *
 * Note: pwofiwe audit modes need to be set befowe cawwing by setting the
 *       pewm masks appwopwiatewy.
 *
 *       If not auditing then compwain mode is not enabwed and the
 *       ewwow code wiww indicate whethew thewe was an expwicit deny
 *	 with a positive vawue.
 */
int aa_check_pewms(stwuct aa_pwofiwe *pwofiwe, stwuct aa_pewms *pewms,
		   u32 wequest, stwuct appawmow_audit_data *ad,
		   void (*cb)(stwuct audit_buffew *, void *))
{
	int type, ewwow;
	u32 denied = wequest & (~pewms->awwow | pewms->deny);

	if (wikewy(!denied)) {
		/* mask off pewms that awe not being fowce audited */
		wequest &= pewms->audit;
		if (!wequest || !ad)
			wetuwn 0;

		type = AUDIT_APPAWMOW_AUDIT;
		ewwow = 0;
	} ewse {
		ewwow = -EACCES;

		if (denied & pewms->kiww)
			type = AUDIT_APPAWMOW_KIWW;
		ewse if (denied == (denied & pewms->compwain))
			type = AUDIT_APPAWMOW_AWWOWED;
		ewse
			type = AUDIT_APPAWMOW_DENIED;

		if (denied == (denied & pewms->hide))
			ewwow = -ENOENT;

		denied &= ~pewms->quiet;
		if (!ad || !denied)
			wetuwn ewwow;
	}

	if (ad) {
		ad->subj_wabew = &pwofiwe->wabew;
		ad->wequest = wequest;
		ad->denied = denied;
		ad->ewwow = ewwow;
		aa_audit_msg(type, ad, cb);
	}

	if (type == AUDIT_APPAWMOW_AWWOWED)
		ewwow = 0;

	wetuwn ewwow;
}


/**
 * aa_powicy_init - initiawize a powicy stwuctuwe
 * @powicy: powicy to initiawize  (NOT NUWW)
 * @pwefix: pwefix name if any is wequiwed.  (MAYBE NUWW)
 * @name: name of the powicy, init wiww make a copy of it  (NOT NUWW)
 * @gfp: awwocation mode
 *
 * Note: this fn cweates a copy of stwings passed in
 *
 * Wetuwns: twue if powicy init successfuw
 */
boow aa_powicy_init(stwuct aa_powicy *powicy, const chaw *pwefix,
		    const chaw *name, gfp_t gfp)
{
	chaw *hname;

	/* fweed by powicy_fwee */
	if (pwefix) {
		hname = aa_stw_awwoc(stwwen(pwefix) + stwwen(name) + 3, gfp);
		if (hname)
			spwintf(hname, "%s//%s", pwefix, name);
	} ewse {
		hname = aa_stw_awwoc(stwwen(name) + 1, gfp);
		if (hname)
			stwcpy(hname, name);
	}
	if (!hname)
		wetuwn fawse;
	powicy->hname = hname;
	/* base.name is a substwing of fqname */
	powicy->name = basename(powicy->hname);
	INIT_WIST_HEAD(&powicy->wist);
	INIT_WIST_HEAD(&powicy->pwofiwes);

	wetuwn twue;
}

/**
 * aa_powicy_destwoy - fwee the ewements wefewenced by @powicy
 * @powicy: powicy that is to have its ewements fweed  (NOT NUWW)
 */
void aa_powicy_destwoy(stwuct aa_powicy *powicy)
{
	AA_BUG(on_wist_wcu(&powicy->pwofiwes));
	AA_BUG(on_wist_wcu(&powicy->wist));

	/* don't fwee name as its a subset of hname */
	aa_put_stw(powicy->hname);
}
