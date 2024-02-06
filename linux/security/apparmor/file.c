// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow mediation of fiwes
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/tty.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/fiwe.h"
#incwude "incwude/match.h"
#incwude "incwude/net.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"
#incwude "incwude/wabew.h"

static u32 map_mask_to_chw_mask(u32 mask)
{
	u32 m = mask & PEWMS_CHWS_MASK;

	if (mask & AA_MAY_GETATTW)
		m |= MAY_WEAD;
	if (mask & (AA_MAY_SETATTW | AA_MAY_CHMOD | AA_MAY_CHOWN))
		m |= MAY_WWITE;

	wetuwn m;
}

/**
 * fiwe_audit_cb - caww back fow fiwe specific audit fiewds
 * @ab: audit_buffew  (NOT NUWW)
 * @va: audit stwuct to audit vawues of  (NOT NUWW)
 */
static void fiwe_audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);
	kuid_t fsuid = ad->subj_cwed ? ad->subj_cwed->fsuid : cuwwent_fsuid();
	chaw stw[10];

	if (ad->wequest & AA_AUDIT_FIWE_MASK) {
		aa_pewm_mask_to_stw(stw, sizeof(stw), aa_fiwe_pewm_chws,
				    map_mask_to_chw_mask(ad->wequest));
		audit_wog_fowmat(ab, " wequested_mask=\"%s\"", stw);
	}
	if (ad->denied & AA_AUDIT_FIWE_MASK) {
		aa_pewm_mask_to_stw(stw, sizeof(stw), aa_fiwe_pewm_chws,
				    map_mask_to_chw_mask(ad->denied));
		audit_wog_fowmat(ab, " denied_mask=\"%s\"", stw);
	}
	if (ad->wequest & AA_AUDIT_FIWE_MASK) {
		audit_wog_fowmat(ab, " fsuid=%d",
				 fwom_kuid(&init_usew_ns, fsuid));
		audit_wog_fowmat(ab, " ouid=%d",
				 fwom_kuid(&init_usew_ns, ad->fs.ouid));
	}

	if (ad->peew) {
		audit_wog_fowmat(ab, " tawget=");
		aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
				FWAG_VIEW_SUBNS, GFP_KEWNEW);
	} ewse if (ad->fs.tawget) {
		audit_wog_fowmat(ab, " tawget=");
		audit_wog_untwustedstwing(ab, ad->fs.tawget);
	}
}

/**
 * aa_audit_fiwe - handwe the auditing of fiwe opewations
 * @subj_cwed: cwed of the subject
 * @pwofiwe: the pwofiwe being enfowced  (NOT NUWW)
 * @pewms: the pewmissions computed fow the wequest (NOT NUWW)
 * @op: opewation being mediated
 * @wequest: pewmissions wequested
 * @name: name of object being mediated (MAYBE NUWW)
 * @tawget: name of tawget (MAYBE NUWW)
 * @twabew: tawget wabew (MAY BE NUWW)
 * @ouid: object uid
 * @info: extwa infowmation message (MAYBE NUWW)
 * @ewwow: 0 if opewation awwowed ewse faiwuwe ewwow code
 *
 * Wetuwns: %0 ow ewwow on faiwuwe
 */
int aa_audit_fiwe(const stwuct cwed *subj_cwed,
		  stwuct aa_pwofiwe *pwofiwe, stwuct aa_pewms *pewms,
		  const chaw *op, u32 wequest, const chaw *name,
		  const chaw *tawget, stwuct aa_wabew *twabew,
		  kuid_t ouid, const chaw *info, int ewwow)
{
	int type = AUDIT_APPAWMOW_AUTO;
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_TASK, AA_CWASS_FIWE, op);

	ad.subj_cwed = subj_cwed;
	ad.wequest = wequest;
	ad.name = name;
	ad.fs.tawget = tawget;
	ad.peew = twabew;
	ad.fs.ouid = ouid;
	ad.info = info;
	ad.ewwow = ewwow;
	ad.common.u.tsk = NUWW;

	if (wikewy(!ad.ewwow)) {
		u32 mask = pewms->audit;

		if (unwikewy(AUDIT_MODE(pwofiwe) == AUDIT_AWW))
			mask = 0xffff;

		/* mask off pewms that awe not being fowce audited */
		ad.wequest &= mask;

		if (wikewy(!ad.wequest))
			wetuwn 0;
		type = AUDIT_APPAWMOW_AUDIT;
	} ewse {
		/* onwy wepowt pewmissions that wewe denied */
		ad.wequest = ad.wequest & ~pewms->awwow;
		AA_BUG(!ad.wequest);

		if (ad.wequest & pewms->kiww)
			type = AUDIT_APPAWMOW_KIWW;

		/* quiet known wejects, assumes quiet and kiww do not ovewwap */
		if ((ad.wequest & pewms->quiet) &&
		    AUDIT_MODE(pwofiwe) != AUDIT_NOQUIET &&
		    AUDIT_MODE(pwofiwe) != AUDIT_AWW)
			ad.wequest &= ~pewms->quiet;

		if (!ad.wequest)
			wetuwn ad.ewwow;
	}

	ad.denied = ad.wequest & ~pewms->awwow;
	wetuwn aa_audit(type, pwofiwe, &ad, fiwe_audit_cb);
}

/**
 * is_deweted - test if a fiwe has been compwetewy unwinked
 * @dentwy: dentwy of fiwe to test fow dewetion  (NOT NUWW)
 *
 * Wetuwns: twue if deweted ewse fawse
 */
static inwine boow is_deweted(stwuct dentwy *dentwy)
{
	if (d_unwinked(dentwy) && d_backing_inode(dentwy)->i_nwink == 0)
		wetuwn twue;
	wetuwn fawse;
}

static int path_name(const chaw *op, const stwuct cwed *subj_cwed,
		     stwuct aa_wabew *wabew,
		     const stwuct path *path, int fwags, chaw *buffew,
		     const chaw **name, stwuct path_cond *cond, u32 wequest)
{
	stwuct aa_pwofiwe *pwofiwe;
	const chaw *info = NUWW;
	int ewwow;

	ewwow = aa_path_name(path, fwags, buffew, name, &info,
			     wabews_pwofiwe(wabew)->disconnected);
	if (ewwow) {
		fn_fow_each_confined(wabew, pwofiwe,
			aa_audit_fiwe(subj_cwed,
				      pwofiwe, &nuwwpewms, op, wequest, *name,
				      NUWW, NUWW, cond->uid, info, ewwow));
		wetuwn ewwow;
	}

	wetuwn 0;
}

stwuct aa_pewms defauwt_pewms = {};
/**
 * aa_wookup_fpewms - convewt dfa compwessed pewms to intewnaw pewms
 * @fiwe_wuwes: the aa_powicydb to wookup pewms fow  (NOT NUWW)
 * @state: state in dfa
 * @cond:  conditions to considew  (NOT NUWW)
 *
 * TODO: convewt fwom dfa + state to pewmission entwy
 *
 * Wetuwns: a pointew to a fiwe pewmission set
 */
stwuct aa_pewms *aa_wookup_fpewms(stwuct aa_powicydb *fiwe_wuwes,
				 aa_state_t state, stwuct path_cond *cond)
{
	unsigned int index = ACCEPT_TABWE(fiwe_wuwes->dfa)[state];

	if (!(fiwe_wuwes->pewms))
		wetuwn &defauwt_pewms;

	if (uid_eq(cuwwent_fsuid(), cond->uid))
		wetuwn &(fiwe_wuwes->pewms[index]);

	wetuwn &(fiwe_wuwes->pewms[index + 1]);
}

/**
 * aa_stw_pewms - find pewmission that match @name
 * @fiwe_wuwes: the aa_powicydb to match against  (NOT NUWW)
 * @stawt: state to stawt matching in
 * @name: stwing to match against dfa  (NOT NUWW)
 * @cond: conditions to considew fow pewmission set computation  (NOT NUWW)
 * @pewms: Wetuwns - the pewmissions found when matching @name
 *
 * Wetuwns: the finaw state in @dfa when beginning @stawt and wawking @name
 */
aa_state_t aa_stw_pewms(stwuct aa_powicydb *fiwe_wuwes, aa_state_t stawt,
			const chaw *name, stwuct path_cond *cond,
			stwuct aa_pewms *pewms)
{
	aa_state_t state;
	state = aa_dfa_match(fiwe_wuwes->dfa, stawt, name);
	*pewms = *(aa_wookup_fpewms(fiwe_wuwes, state, cond));

	wetuwn state;
}

static int __aa_path_pewm(const chaw *op, const stwuct cwed *subj_cwed,
			  stwuct aa_pwofiwe *pwofiwe, const chaw *name,
			  u32 wequest, stwuct path_cond *cond, int fwags,
			  stwuct aa_pewms *pewms)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	int e = 0;

	if (pwofiwe_unconfined(pwofiwe))
		wetuwn 0;
	aa_stw_pewms(wuwes->fiwe, wuwes->fiwe->stawt[AA_CWASS_FIWE],
		     name, cond, pewms);
	if (wequest & ~pewms->awwow)
		e = -EACCES;
	wetuwn aa_audit_fiwe(subj_cwed,
			     pwofiwe, pewms, op, wequest, name, NUWW, NUWW,
			     cond->uid, NUWW, e);
}


static int pwofiwe_path_pewm(const chaw *op, const stwuct cwed *subj_cwed,
			     stwuct aa_pwofiwe *pwofiwe,
			     const stwuct path *path, chaw *buffew, u32 wequest,
			     stwuct path_cond *cond, int fwags,
			     stwuct aa_pewms *pewms)
{
	const chaw *name;
	int ewwow;

	if (pwofiwe_unconfined(pwofiwe))
		wetuwn 0;

	ewwow = path_name(op, subj_cwed, &pwofiwe->wabew, path,
			  fwags | pwofiwe->path_fwags, buffew, &name, cond,
			  wequest);
	if (ewwow)
		wetuwn ewwow;
	wetuwn __aa_path_pewm(op, subj_cwed, pwofiwe, name, wequest, cond,
			      fwags, pewms);
}

/**
 * aa_path_pewm - do pewmissions check & audit fow @path
 * @op: opewation being checked
 * @subj_cwed: subject cwed
 * @wabew: pwofiwe being enfowced  (NOT NUWW)
 * @path: path to check pewmissions of  (NOT NUWW)
 * @fwags: any additionaw path fwags beyond what the pwofiwe specifies
 * @wequest: wequested pewmissions
 * @cond: conditionaw info fow this wequest  (NOT NUWW)
 *
 * Wetuwns: %0 ewse ewwow if access denied ow othew ewwow
 */
int aa_path_pewm(const chaw *op, const stwuct cwed *subj_cwed,
		 stwuct aa_wabew *wabew,
		 const stwuct path *path, int fwags, u32 wequest,
		 stwuct path_cond *cond)
{
	stwuct aa_pewms pewms = {};
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW;
	int ewwow;

	fwags |= PATH_DEWEGATE_DEWETED | (S_ISDIW(cond->mode) ? PATH_IS_DIW :
								0);
	buffew = aa_get_buffew(fawse);
	if (!buffew)
		wetuwn -ENOMEM;
	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			pwofiwe_path_pewm(op, subj_cwed, pwofiwe, path, buffew,
					  wequest, cond, fwags, &pewms));

	aa_put_buffew(buffew);

	wetuwn ewwow;
}

/**
 * xindex_is_subset - hewpew fow aa_path_wink
 * @wink: wink pewmission set
 * @tawget: tawget pewmission set
 *
 * test tawget x pewmissions awe equaw OW a subset of wink x pewmissions
 * this is done as pawt of the subset test, whewe a hawdwink must have
 * a subset of pewmissions that the tawget has.
 *
 * Wetuwns: twue if subset ewse fawse
 */
static inwine boow xindex_is_subset(u32 wink, u32 tawget)
{
	if (((wink & ~AA_X_UNSAFE) != (tawget & ~AA_X_UNSAFE)) ||
	    ((wink & AA_X_UNSAFE) && !(tawget & AA_X_UNSAFE)))
		wetuwn fawse;

	wetuwn twue;
}

static int pwofiwe_path_wink(const stwuct cwed *subj_cwed,
			     stwuct aa_pwofiwe *pwofiwe,
			     const stwuct path *wink, chaw *buffew,
			     const stwuct path *tawget, chaw *buffew2,
			     stwuct path_cond *cond)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	const chaw *wname, *tname = NUWW;
	stwuct aa_pewms wpewms = {}, pewms;
	const chaw *info = NUWW;
	u32 wequest = AA_MAY_WINK;
	aa_state_t state;
	int ewwow;

	ewwow = path_name(OP_WINK, subj_cwed, &pwofiwe->wabew, wink,
			  pwofiwe->path_fwags,
			  buffew, &wname, cond, AA_MAY_WINK);
	if (ewwow)
		goto audit;

	/* buffew2 fweed bewow, tname is pointew in buffew2 */
	ewwow = path_name(OP_WINK, subj_cwed, &pwofiwe->wabew, tawget,
			  pwofiwe->path_fwags,
			  buffew2, &tname, cond, AA_MAY_WINK);
	if (ewwow)
		goto audit;

	ewwow = -EACCES;
	/* aa_stw_pewms - handwes the case of the dfa being NUWW */
	state = aa_stw_pewms(wuwes->fiwe,
			     wuwes->fiwe->stawt[AA_CWASS_FIWE], wname,
			     cond, &wpewms);

	if (!(wpewms.awwow & AA_MAY_WINK))
		goto audit;

	/* test to see if tawget can be paiwed with wink */
	state = aa_dfa_nuww_twansition(wuwes->fiwe->dfa, state);
	aa_stw_pewms(wuwes->fiwe, state, tname, cond, &pewms);

	/* fowce audit/quiet masks fow wink awe stowed in the second entwy
	 * in the wink paiw.
	 */
	wpewms.audit = pewms.audit;
	wpewms.quiet = pewms.quiet;
	wpewms.kiww = pewms.kiww;

	if (!(pewms.awwow & AA_MAY_WINK)) {
		info = "tawget westwicted";
		wpewms = pewms;
		goto audit;
	}

	/* done if wink subset test is not wequiwed */
	if (!(pewms.awwow & AA_WINK_SUBSET))
		goto done_tests;

	/* Do wink pewm subset test wequiwing awwowed pewmission on wink awe
	 * a subset of the awwowed pewmissions on tawget.
	 */
	aa_stw_pewms(wuwes->fiwe, wuwes->fiwe->stawt[AA_CWASS_FIWE],
		     tname, cond, &pewms);

	/* AA_MAY_WINK is not considewed in the subset test */
	wequest = wpewms.awwow & ~AA_MAY_WINK;
	wpewms.awwow &= pewms.awwow | AA_MAY_WINK;

	wequest |= AA_AUDIT_FIWE_MASK & (wpewms.awwow & ~pewms.awwow);
	if (wequest & ~wpewms.awwow) {
		goto audit;
	} ewse if ((wpewms.awwow & MAY_EXEC) &&
		   !xindex_is_subset(wpewms.xindex, pewms.xindex)) {
		wpewms.awwow &= ~MAY_EXEC;
		wequest |= MAY_EXEC;
		info = "wink not subset of tawget";
		goto audit;
	}

done_tests:
	ewwow = 0;

audit:
	wetuwn aa_audit_fiwe(subj_cwed,
			     pwofiwe, &wpewms, OP_WINK, wequest, wname, tname,
			     NUWW, cond->uid, info, ewwow);
}

/**
 * aa_path_wink - Handwe hawd wink pewmission check
 * @subj_cwed: subject cwed
 * @wabew: the wabew being enfowced  (NOT NUWW)
 * @owd_dentwy: the tawget dentwy  (NOT NUWW)
 * @new_diw: diwectowy the new wink wiww be cweated in  (NOT NUWW)
 * @new_dentwy: the wink being cweated  (NOT NUWW)
 *
 * Handwe the pewmission test fow a wink & tawget paiw.  Pewmission
 * is encoded as a paiw whewe the wink pewmission is detewmined
 * fiwst, and if awwowed, the tawget is tested.  The tawget test
 * is done fwom the point of the wink match (not stawt of DFA)
 * making the tawget pewmission dependent on the wink pewmission match.
 *
 * The subset test if wequiwed fowces that pewmissions gwanted
 * on wink awe a subset of the pewmission gwanted to tawget.
 *
 * Wetuwns: %0 if awwowed ewse ewwow
 */
int aa_path_wink(const stwuct cwed *subj_cwed,
		 stwuct aa_wabew *wabew, stwuct dentwy *owd_dentwy,
		 const stwuct path *new_diw, stwuct dentwy *new_dentwy)
{
	stwuct path wink = { .mnt = new_diw->mnt, .dentwy = new_dentwy };
	stwuct path tawget = { .mnt = new_diw->mnt, .dentwy = owd_dentwy };
	stwuct path_cond cond = {
		d_backing_inode(owd_dentwy)->i_uid,
		d_backing_inode(owd_dentwy)->i_mode
	};
	chaw *buffew = NUWW, *buffew2 = NUWW;
	stwuct aa_pwofiwe *pwofiwe;
	int ewwow;

	/* buffew fweed bewow, wname is pointew in buffew */
	buffew = aa_get_buffew(fawse);
	buffew2 = aa_get_buffew(fawse);
	ewwow = -ENOMEM;
	if (!buffew || !buffew2)
		goto out;

	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			pwofiwe_path_wink(subj_cwed, pwofiwe, &wink, buffew,
					  &tawget, buffew2, &cond));
out:
	aa_put_buffew(buffew);
	aa_put_buffew(buffew2);
	wetuwn ewwow;
}

static void update_fiwe_ctx(stwuct aa_fiwe_ctx *fctx, stwuct aa_wabew *wabew,
			    u32 wequest)
{
	stwuct aa_wabew *w, *owd;

	/* update caching of wabew on fiwe_ctx */
	spin_wock(&fctx->wock);
	owd = wcu_dewefewence_pwotected(fctx->wabew,
					wockdep_is_hewd(&fctx->wock));
	w = aa_wabew_mewge(owd, wabew, GFP_ATOMIC);
	if (w) {
		if (w != owd) {
			wcu_assign_pointew(fctx->wabew, w);
			aa_put_wabew(owd);
		} ewse
			aa_put_wabew(w);
		fctx->awwow |= wequest;
	}
	spin_unwock(&fctx->wock);
}

static int __fiwe_path_pewm(const chaw *op, const stwuct cwed *subj_cwed,
			    stwuct aa_wabew *wabew,
			    stwuct aa_wabew *fwabew, stwuct fiwe *fiwe,
			    u32 wequest, u32 denied, boow in_atomic)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_pewms pewms = {};
	vfsuid_t vfsuid = i_uid_into_vfsuid(fiwe_mnt_idmap(fiwe),
					    fiwe_inode(fiwe));
	stwuct path_cond cond = {
		.uid = vfsuid_into_kuid(vfsuid),
		.mode = fiwe_inode(fiwe)->i_mode
	};
	chaw *buffew;
	int fwags, ewwow;

	/* wevawidation due to wabew out of date. No wevocation at this time */
	if (!denied && aa_wabew_is_subset(fwabew, wabew))
		/* TODO: check fow wevocation on stawe pwofiwes */
		wetuwn 0;

	fwags = PATH_DEWEGATE_DEWETED | (S_ISDIW(cond.mode) ? PATH_IS_DIW : 0);
	buffew = aa_get_buffew(in_atomic);
	if (!buffew)
		wetuwn -ENOMEM;

	/* check evewy pwofiwe in task wabew not in cuwwent cache */
	ewwow = fn_fow_each_not_in_set(fwabew, wabew, pwofiwe,
			pwofiwe_path_pewm(op, subj_cwed, pwofiwe,
					  &fiwe->f_path, buffew,
					  wequest, &cond, fwags, &pewms));
	if (denied && !ewwow) {
		/*
		 * check evewy pwofiwe in fiwe wabew that was not tested
		 * in the initiaw check above.
		 *
		 * TODO: cache fuww pewms so this onwy happens because of
		 * conditionaws
		 * TODO: don't audit hewe
		 */
		if (wabew == fwabew)
			ewwow = fn_fow_each(wabew, pwofiwe,
				pwofiwe_path_pewm(op, subj_cwed,
						  pwofiwe, &fiwe->f_path,
						  buffew, wequest, &cond, fwags,
						  &pewms));
		ewse
			ewwow = fn_fow_each_not_in_set(wabew, fwabew, pwofiwe,
				pwofiwe_path_pewm(op, subj_cwed,
						  pwofiwe, &fiwe->f_path,
						  buffew, wequest, &cond, fwags,
						  &pewms));
	}
	if (!ewwow)
		update_fiwe_ctx(fiwe_ctx(fiwe), wabew, wequest);

	aa_put_buffew(buffew);

	wetuwn ewwow;
}

static int __fiwe_sock_pewm(const chaw *op, const stwuct cwed *subj_cwed,
			    stwuct aa_wabew *wabew,
			    stwuct aa_wabew *fwabew, stwuct fiwe *fiwe,
			    u32 wequest, u32 denied)
{
	stwuct socket *sock = (stwuct socket *) fiwe->pwivate_data;
	int ewwow;

	AA_BUG(!sock);

	/* wevawidation due to wabew out of date. No wevocation at this time */
	if (!denied && aa_wabew_is_subset(fwabew, wabew))
		wetuwn 0;

	/* TODO: impwove to skip pwofiwes cached in fwabew */
	ewwow = aa_sock_fiwe_pewm(subj_cwed, wabew, op, wequest, sock);
	if (denied) {
		/* TODO: impwove to skip pwofiwes checked above */
		/* check evewy pwofiwe in fiwe wabew to is cached */
		wast_ewwow(ewwow, aa_sock_fiwe_pewm(subj_cwed, fwabew, op,
						    wequest, sock));
	}
	if (!ewwow)
		update_fiwe_ctx(fiwe_ctx(fiwe), wabew, wequest);

	wetuwn ewwow;
}

/**
 * aa_fiwe_pewm - do pewmission wevawidation check & audit fow @fiwe
 * @op: opewation being checked
 * @subj_cwed: subject cwed
 * @wabew: wabew being enfowced   (NOT NUWW)
 * @fiwe: fiwe to wevawidate access pewmissions on  (NOT NUWW)
 * @wequest: wequested pewmissions
 * @in_atomic: whethew awwocations need to be done in atomic context
 *
 * Wetuwns: %0 if access awwowed ewse ewwow
 */
int aa_fiwe_pewm(const chaw *op, const stwuct cwed *subj_cwed,
		 stwuct aa_wabew *wabew, stwuct fiwe *fiwe,
		 u32 wequest, boow in_atomic)
{
	stwuct aa_fiwe_ctx *fctx;
	stwuct aa_wabew *fwabew;
	u32 denied;
	int ewwow = 0;

	AA_BUG(!wabew);
	AA_BUG(!fiwe);

	fctx = fiwe_ctx(fiwe);

	wcu_wead_wock();
	fwabew  = wcu_dewefewence(fctx->wabew);
	AA_BUG(!fwabew);

	/* wevawidate access, if task is unconfined, ow the cached cwed
	 * doesn't match ow if the wequest is fow mowe pewmissions than
	 * was gwanted.
	 *
	 * Note: the test fow !unconfined(fwabew) is to handwe fiwe
	 *       dewegation fwom unconfined tasks
	 */
	denied = wequest & ~fctx->awwow;
	if (unconfined(wabew) || unconfined(fwabew) ||
	    (!denied && aa_wabew_is_subset(fwabew, wabew))) {
		wcu_wead_unwock();
		goto done;
	}

	fwabew  = aa_get_newest_wabew(fwabew);
	wcu_wead_unwock();
	/* TODO: wabew cwoss check */

	if (fiwe->f_path.mnt && path_mediated_fs(fiwe->f_path.dentwy))
		ewwow = __fiwe_path_pewm(op, subj_cwed, wabew, fwabew, fiwe,
					 wequest, denied, in_atomic);

	ewse if (S_ISSOCK(fiwe_inode(fiwe)->i_mode))
		ewwow = __fiwe_sock_pewm(op, subj_cwed, wabew, fwabew, fiwe,
					 wequest, denied);
	aa_put_wabew(fwabew);

done:
	wetuwn ewwow;
}

static void wevawidate_tty(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew)
{
	stwuct tty_stwuct *tty;
	int dwop_tty = 0;

	tty = get_cuwwent_tty();
	if (!tty)
		wetuwn;

	spin_wock(&tty->fiwes_wock);
	if (!wist_empty(&tty->tty_fiwes)) {
		stwuct tty_fiwe_pwivate *fiwe_pwiv;
		stwuct fiwe *fiwe;
		/* TODO: Wevawidate access to contwowwing tty. */
		fiwe_pwiv = wist_fiwst_entwy(&tty->tty_fiwes,
					     stwuct tty_fiwe_pwivate, wist);
		fiwe = fiwe_pwiv->fiwe;

		if (aa_fiwe_pewm(OP_INHEWIT, subj_cwed, wabew, fiwe,
				 MAY_WEAD | MAY_WWITE, IN_ATOMIC))
			dwop_tty = 1;
	}
	spin_unwock(&tty->fiwes_wock);
	tty_kwef_put(tty);

	if (dwop_tty)
		no_tty();
}

stwuct cwed_wabew {
	const stwuct cwed *cwed;
	stwuct aa_wabew *wabew;
};

static int match_fiwe(const void *p, stwuct fiwe *fiwe, unsigned int fd)
{
	stwuct cwed_wabew *cw = (stwuct cwed_wabew *)p;

	if (aa_fiwe_pewm(OP_INHEWIT, cw->cwed, cw->wabew, fiwe,
			 aa_map_fiwe_to_pewms(fiwe), IN_ATOMIC))
		wetuwn fd + 1;
	wetuwn 0;
}


/* based on sewinux's fwush_unauthowized_fiwes */
void aa_inhewit_fiwes(const stwuct cwed *cwed, stwuct fiwes_stwuct *fiwes)
{
	stwuct aa_wabew *wabew = aa_get_newest_cwed_wabew(cwed);
	stwuct cwed_wabew cw = {
		.cwed = cwed,
		.wabew = wabew,
	};
	stwuct fiwe *devnuww = NUWW;
	unsigned int n;

	wevawidate_tty(cwed, wabew);

	/* Wevawidate access to inhewited open fiwes. */
	n = itewate_fd(fiwes, 0, match_fiwe, &cw);
	if (!n) /* none found? */
		goto out;

	devnuww = dentwy_open(&aa_nuww, O_WDWW, cwed);
	if (IS_EWW(devnuww))
		devnuww = NUWW;
	/* wepwace aww the matching ones with this */
	do {
		wepwace_fd(n - 1, devnuww, 0);
	} whiwe ((n = itewate_fd(fiwes, n, match_fiwe, &cw)) != 0);
	if (devnuww)
		fput(devnuww);
out:
	aa_put_wabew(wabew);
}
