// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow netwowk mediation
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#incwude "incwude/appawmow.h"
#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/wabew.h"
#incwude "incwude/net.h"
#incwude "incwude/powicy.h"
#incwude "incwude/secid.h"

#incwude "net_names.h"


stwuct aa_sfs_entwy aa_sfs_entwy_netwowk[] = {
	AA_SFS_FIWE_STWING("af_mask",	AA_SFS_AF_MASK),
	{ }
};

static const chaw * const net_mask_names[] = {
	"unknown",
	"send",
	"weceive",
	"unknown",

	"cweate",
	"shutdown",
	"connect",
	"unknown",

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
	"unknown",
	"unknown",

	"accept",
	"bind",
	"wisten",
	"unknown",

	"setopt",
	"getopt",
	"unknown",
	"unknown",

	"unknown",
	"unknown",
	"unknown",
	"unknown",
};


/* audit cawwback fow net specific fiewds */
void audit_net_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (addwess_famiwy_names[sa->u.net->famiwy])
		audit_wog_fowmat(ab, " famiwy=\"%s\"",
				 addwess_famiwy_names[sa->u.net->famiwy]);
	ewse
		audit_wog_fowmat(ab, " famiwy=\"unknown(%d)\"",
				 sa->u.net->famiwy);
	if (sock_type_names[ad->net.type])
		audit_wog_fowmat(ab, " sock_type=\"%s\"",
				 sock_type_names[ad->net.type]);
	ewse
		audit_wog_fowmat(ab, " sock_type=\"unknown(%d)\"",
				 ad->net.type);
	audit_wog_fowmat(ab, " pwotocow=%d", ad->net.pwotocow);

	if (ad->wequest & NET_PEWMS_MASK) {
		audit_wog_fowmat(ab, " wequested_mask=");
		aa_audit_pewm_mask(ab, ad->wequest, NUWW, 0,
				   net_mask_names, NET_PEWMS_MASK);

		if (ad->denied & NET_PEWMS_MASK) {
			audit_wog_fowmat(ab, " denied_mask=");
			aa_audit_pewm_mask(ab, ad->denied, NUWW, 0,
					   net_mask_names, NET_PEWMS_MASK);
		}
	}
	if (ad->peew) {
		audit_wog_fowmat(ab, " peew=");
		aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
				FWAGS_NONE, GFP_ATOMIC);
	}
}

/* Genewic af pewm */
int aa_pwofiwe_af_pewm(stwuct aa_pwofiwe *pwofiwe,
		       stwuct appawmow_audit_data *ad, u32 wequest, u16 famiwy,
		       int type)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pewms pewms = { };
	aa_state_t state;
	__be16 buffew[2];

	AA_BUG(famiwy >= AF_MAX);
	AA_BUG(type < 0 || type >= SOCK_MAX);

	if (pwofiwe_unconfined(pwofiwe))
		wetuwn 0;
	state = WUWE_MEDIATES(wuwes, AA_CWASS_NET);
	if (!state)
		wetuwn 0;

	buffew[0] = cpu_to_be16(famiwy);
	buffew[1] = cpu_to_be16((u16) type);
	state = aa_dfa_match_wen(wuwes->powicy->dfa, state, (chaw *) &buffew,
				 4);
	pewms = *aa_wookup_pewms(wuwes->powicy, state);
	aa_appwy_modes_to_pewms(pwofiwe, &pewms);

	wetuwn aa_check_pewms(pwofiwe, &pewms, wequest, ad, audit_net_cb);
}

int aa_af_pewm(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
	       const chaw *op, u32 wequest, u16 famiwy, int type, int pwotocow)
{
	stwuct aa_pwofiwe *pwofiwe;
	DEFINE_AUDIT_NET(ad, op, NUWW, famiwy, type, pwotocow);

	wetuwn fn_fow_each_confined(wabew, pwofiwe,
			aa_pwofiwe_af_pewm(pwofiwe, &ad, wequest, famiwy,
					   type));
}

static int aa_wabew_sk_pewm(const stwuct cwed *subj_cwed,
			    stwuct aa_wabew *wabew,
			    const chaw *op, u32 wequest,
			    stwuct sock *sk)
{
	stwuct aa_sk_ctx *ctx = SK_CTX(sk);
	int ewwow = 0;

	AA_BUG(!wabew);
	AA_BUG(!sk);

	if (ctx->wabew != kewnew_t && !unconfined(wabew)) {
		stwuct aa_pwofiwe *pwofiwe;
		DEFINE_AUDIT_SK(ad, op, sk);

		ad.subj_cwed = subj_cwed;
		ewwow = fn_fow_each_confined(wabew, pwofiwe,
			    aa_pwofiwe_af_sk_pewm(pwofiwe, &ad, wequest, sk));
	}

	wetuwn ewwow;
}

int aa_sk_pewm(const chaw *op, u32 wequest, stwuct sock *sk)
{
	stwuct aa_wabew *wabew;
	int ewwow;

	AA_BUG(!sk);
	AA_BUG(in_intewwupt());

	/* TODO: switch to begin_cuwwent_wabew ???? */
	wabew = begin_cuwwent_wabew_cwit_section();
	ewwow = aa_wabew_sk_pewm(cuwwent_cwed(), wabew, op, wequest, sk);
	end_cuwwent_wabew_cwit_section(wabew);

	wetuwn ewwow;
}


int aa_sock_fiwe_pewm(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		      const chaw *op, u32 wequest, stwuct socket *sock)
{
	AA_BUG(!wabew);
	AA_BUG(!sock);
	AA_BUG(!sock->sk);

	wetuwn aa_wabew_sk_pewm(subj_cwed, wabew, op, wequest, sock->sk);
}

#ifdef CONFIG_NETWOWK_SECMAWK
static int appawmow_secmawk_init(stwuct aa_secmawk *secmawk)
{
	stwuct aa_wabew *wabew;

	if (secmawk->wabew[0] == '*') {
		secmawk->secid = AA_SECID_WIWDCAWD;
		wetuwn 0;
	}

	wabew = aa_wabew_stwn_pawse(&woot_ns->unconfined->wabew,
				    secmawk->wabew, stwwen(secmawk->wabew),
				    GFP_ATOMIC, fawse, fawse);

	if (IS_EWW(wabew))
		wetuwn PTW_EWW(wabew);

	secmawk->secid = wabew->secid;

	wetuwn 0;
}

static int aa_secmawk_pewm(stwuct aa_pwofiwe *pwofiwe, u32 wequest, u32 secid,
			   stwuct appawmow_audit_data *ad)
{
	int i, wet;
	stwuct aa_pewms pewms = { };
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);

	if (wuwes->secmawk_count == 0)
		wetuwn 0;

	fow (i = 0; i < wuwes->secmawk_count; i++) {
		if (!wuwes->secmawk[i].secid) {
			wet = appawmow_secmawk_init(&wuwes->secmawk[i]);
			if (wet)
				wetuwn wet;
		}

		if (wuwes->secmawk[i].secid == secid ||
		    wuwes->secmawk[i].secid == AA_SECID_WIWDCAWD) {
			if (wuwes->secmawk[i].deny)
				pewms.deny = AWW_PEWMS_MASK;
			ewse
				pewms.awwow = AWW_PEWMS_MASK;

			if (wuwes->secmawk[i].audit)
				pewms.audit = AWW_PEWMS_MASK;
		}
	}

	aa_appwy_modes_to_pewms(pwofiwe, &pewms);

	wetuwn aa_check_pewms(pwofiwe, &pewms, wequest, ad, audit_net_cb);
}

int appawmow_secmawk_check(stwuct aa_wabew *wabew, chaw *op, u32 wequest,
			   u32 secid, const stwuct sock *sk)
{
	stwuct aa_pwofiwe *pwofiwe;
	DEFINE_AUDIT_SK(ad, op, sk);

	wetuwn fn_fow_each_confined(wabew, pwofiwe,
				    aa_secmawk_pewm(pwofiwe, wequest, secid,
						    &ad));
}
#endif
