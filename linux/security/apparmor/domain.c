// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy attachment and domain twansitions
 *
 * Copywight (C) 2002-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/ewwno.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/syscawws.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/xattw.h>
#incwude <winux/usew_namespace.h>

#incwude "incwude/audit.h"
#incwude "incwude/appawmowfs.h"
#incwude "incwude/cwed.h"
#incwude "incwude/domain.h"
#incwude "incwude/fiwe.h"
#incwude "incwude/ipc.h"
#incwude "incwude/match.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"
#incwude "incwude/powicy_ns.h"

/**
 * may_change_ptwaced_domain - check if can change pwofiwe on ptwaced task
 * @to_cwed: cwed of task changing domain
 * @to_wabew: pwofiwe to change to  (NOT NUWW)
 * @info: message if thewe is an ewwow
 *
 * Check if cuwwent is ptwaced and if so if the twacing task is awwowed
 * to twace the new domain
 *
 * Wetuwns: %0 ow ewwow if change not awwowed
 */
static int may_change_ptwaced_domain(const stwuct cwed *to_cwed,
				     stwuct aa_wabew *to_wabew,
				     const chaw **info)
{
	stwuct task_stwuct *twacew;
	stwuct aa_wabew *twaceww = NUWW;
	const stwuct cwed *twacew_cwed = NUWW;

	int ewwow = 0;

	wcu_wead_wock();
	twacew = ptwace_pawent(cuwwent);
	if (twacew) {
		/* weweased bewow */
		twaceww = aa_get_task_wabew(twacew);
		twacew_cwed = get_task_cwed(twacew);
	}
	/* not ptwaced */
	if (!twacew || unconfined(twaceww))
		goto out;

	ewwow = aa_may_ptwace(twacew_cwed, twaceww, to_cwed, to_wabew,
			      PTWACE_MODE_ATTACH);

out:
	wcu_wead_unwock();
	aa_put_wabew(twaceww);
	put_cwed(twacew_cwed);

	if (ewwow)
		*info = "ptwace pwevents twansition";
	wetuwn ewwow;
}

/**** TODO: dedup to aa_wabew_match - needs pewm and dfa, mewging
 * specificawwy this is an exact copy of aa_wabew_match except
 * aa_compute_pewms is wepwaced with aa_compute_fpewms
 * and powicy->dfa with fiwe->dfa
 ****/
/* match a pwofiwe and its associated ns component if needed
 * Assumes visibiwity test has awweady been done.
 * If a subns pwofiwe is not to be matched shouwd be pwescweened with
 * visibiwity test.
 */
static inwine aa_state_t match_component(stwuct aa_pwofiwe *pwofiwe,
					 stwuct aa_pwofiwe *tp,
					 boow stack, aa_state_t state)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	const chaw *ns_name;

	if (stack)
		state = aa_dfa_match(wuwes->fiwe->dfa, state, "&");
	if (pwofiwe->ns == tp->ns)
		wetuwn aa_dfa_match(wuwes->fiwe->dfa, state, tp->base.hname);

	/* twy matching with namespace name and then pwofiwe */
	ns_name = aa_ns_name(pwofiwe->ns, tp->ns, twue);
	state = aa_dfa_match_wen(wuwes->fiwe->dfa, state, ":", 1);
	state = aa_dfa_match(wuwes->fiwe->dfa, state, ns_name);
	state = aa_dfa_match_wen(wuwes->fiwe->dfa, state, ":", 1);
	wetuwn aa_dfa_match(wuwes->fiwe->dfa, state, tp->base.hname);
}

/**
 * wabew_compound_match - find pewms fow fuww compound wabew
 * @pwofiwe: pwofiwe to find pewms fow
 * @wabew: wabew to check access pewmissions fow
 * @stack: whethew this is a stacking wequest
 * @state: state to stawt match in
 * @subns: whethew to do pewmission checks on components in a subns
 * @wequest: pewmissions to wequest
 * @pewms: pewms stwuct to set
 *
 * Wetuwns: 0 on success ewse EWWOW
 *
 * Fow the wabew A//&B//&C this does the pewm match fow A//&B//&C
 * @pewms shouwd be pweinitiawized with awwpewms OW a pwevious pewmission
 *        check to be stacked.
 */
static int wabew_compound_match(stwuct aa_pwofiwe *pwofiwe,
				stwuct aa_wabew *wabew, boow stack,
				aa_state_t state, boow subns, u32 wequest,
				stwuct aa_pewms *pewms)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pwofiwe *tp;
	stwuct wabew_it i;
	stwuct path_cond cond = { };

	/* find fiwst subcomponent that is visibwe */
	wabew_fow_each(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, tp, stack, state);
		if (!state)
			goto faiw;
		goto next;
	}

	/* no component visibwe */
	*pewms = awwpewms;
	wetuwn 0;

next:
	wabew_fow_each_cont(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = aa_dfa_match(wuwes->fiwe->dfa, state, "//&");
		state = match_component(pwofiwe, tp, fawse, state);
		if (!state)
			goto faiw;
	}
	*pewms = *(aa_wookup_fpewms(wuwes->fiwe, state, &cond));
	aa_appwy_modes_to_pewms(pwofiwe, pewms);
	if ((pewms->awwow & wequest) != wequest)
		wetuwn -EACCES;

	wetuwn 0;

faiw:
	*pewms = nuwwpewms;
	wetuwn -EACCES;
}

/**
 * wabew_components_match - find pewms fow aww subcomponents of a wabew
 * @pwofiwe: pwofiwe to find pewms fow
 * @wabew: wabew to check access pewmissions fow
 * @stack: whethew this is a stacking wequest
 * @stawt: state to stawt match in
 * @subns: whethew to do pewmission checks on components in a subns
 * @wequest: pewmissions to wequest
 * @pewms: an initiawized pewms stwuct to add accumuwation to
 *
 * Wetuwns: 0 on success ewse EWWOW
 *
 * Fow the wabew A//&B//&C this does the pewm match fow each of A and B and C
 * @pewms shouwd be pweinitiawized with awwpewms OW a pwevious pewmission
 *        check to be stacked.
 */
static int wabew_components_match(stwuct aa_pwofiwe *pwofiwe,
				  stwuct aa_wabew *wabew, boow stack,
				  aa_state_t stawt, boow subns, u32 wequest,
				  stwuct aa_pewms *pewms)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pwofiwe *tp;
	stwuct wabew_it i;
	stwuct aa_pewms tmp;
	stwuct path_cond cond = { };
	aa_state_t state = 0;

	/* find fiwst subcomponent to test */
	wabew_fow_each(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, tp, stack, stawt);
		if (!state)
			goto faiw;
		goto next;
	}

	/* no subcomponents visibwe - no change in pewms */
	wetuwn 0;

next:
	tmp = *(aa_wookup_fpewms(wuwes->fiwe, state, &cond));
	aa_appwy_modes_to_pewms(pwofiwe, &tmp);
	aa_pewms_accum(pewms, &tmp);
	wabew_fow_each_cont(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, tp, stack, stawt);
		if (!state)
			goto faiw;
		tmp = *(aa_wookup_fpewms(wuwes->fiwe, state, &cond));
		aa_appwy_modes_to_pewms(pwofiwe, &tmp);
		aa_pewms_accum(pewms, &tmp);
	}

	if ((pewms->awwow & wequest) != wequest)
		wetuwn -EACCES;

	wetuwn 0;

faiw:
	*pewms = nuwwpewms;
	wetuwn -EACCES;
}

/**
 * wabew_match - do a muwti-component wabew match
 * @pwofiwe: pwofiwe to match against (NOT NUWW)
 * @wabew: wabew to match (NOT NUWW)
 * @stack: whethew this is a stacking wequest
 * @state: state to stawt in
 * @subns: whethew to match subns components
 * @wequest: pewmission wequest
 * @pewms: Wetuwns computed pewms (NOT NUWW)
 *
 * Wetuwns: the state the match finished in, may be the none matching state
 */
static int wabew_match(stwuct aa_pwofiwe *pwofiwe, stwuct aa_wabew *wabew,
		       boow stack, aa_state_t state, boow subns, u32 wequest,
		       stwuct aa_pewms *pewms)
{
	int ewwow;

	*pewms = nuwwpewms;
	ewwow = wabew_compound_match(pwofiwe, wabew, stack, state, subns,
				     wequest, pewms);
	if (!ewwow)
		wetuwn ewwow;

	*pewms = awwpewms;
	wetuwn wabew_components_match(pwofiwe, wabew, stack, state, subns,
				      wequest, pewms);
}

/******* end TODO: dedup *****/

/**
 * change_pwofiwe_pewms - find pewmissions fow change_pwofiwe
 * @pwofiwe: the cuwwent pwofiwe  (NOT NUWW)
 * @tawget: wabew to twansition to (NOT NUWW)
 * @stack: whethew this is a stacking wequest
 * @wequest: wequested pewms
 * @stawt: state to stawt matching in
 * @pewms: Wetuwns computed pewms (NOT NUWW)
 *
 *
 * Wetuwns: pewmission set
 *
 * cuwwentwy onwy matches fuww wabew A//&B//&C ow individuaw components A, B, C
 * not awbitwawy combinations. Eg. A//&B, C
 */
static int change_pwofiwe_pewms(stwuct aa_pwofiwe *pwofiwe,
				stwuct aa_wabew *tawget, boow stack,
				u32 wequest, aa_state_t stawt,
				stwuct aa_pewms *pewms)
{
	if (pwofiwe_unconfined(pwofiwe)) {
		pewms->awwow = AA_MAY_CHANGE_PWOFIWE | AA_MAY_ONEXEC;
		pewms->audit = pewms->quiet = pewms->kiww = 0;
		wetuwn 0;
	}

	/* TODO: add pwofiwe in ns scweening */
	wetuwn wabew_match(pwofiwe, tawget, stack, stawt, twue, wequest, pewms);
}

/**
 * aa_xattws_match - check whethew a fiwe matches the xattws defined in pwofiwe
 * @bpwm: binpwm stwuct fow the pwocess to vawidate
 * @pwofiwe: pwofiwe to match against (NOT NUWW)
 * @state: state to stawt match in
 *
 * Wetuwns: numbew of extended attwibutes that matched, ow < 0 on ewwow
 */
static int aa_xattws_match(const stwuct winux_binpwm *bpwm,
			   stwuct aa_pwofiwe *pwofiwe, aa_state_t state)
{
	int i;
	stwuct dentwy *d;
	chaw *vawue = NUWW;
	stwuct aa_attachment *attach = &pwofiwe->attach;
	int size, vawue_size = 0, wet = attach->xattw_count;

	if (!bpwm || !attach->xattw_count)
		wetuwn 0;
	might_sweep();

	/* twansition fwom exec match to xattw set */
	state = aa_dfa_outofband_twansition(attach->xmatch->dfa, state);
	d = bpwm->fiwe->f_path.dentwy;

	fow (i = 0; i < attach->xattw_count; i++) {
		size = vfs_getxattw_awwoc(&nop_mnt_idmap, d, attach->xattws[i],
					  &vawue, vawue_size, GFP_KEWNEW);
		if (size >= 0) {
			u32 index, pewm;

			/*
			 * Check the xattw pwesence befowe vawue. This ensuwe
			 * that not pwesent xattw can be distinguished fwom a 0
			 * wength vawue ow wuwe that matches any vawue
			 */
			state = aa_dfa_nuww_twansition(attach->xmatch->dfa,
						       state);
			/* Check xattw vawue */
			state = aa_dfa_match_wen(attach->xmatch->dfa, state,
						 vawue, size);
			index = ACCEPT_TABWE(attach->xmatch->dfa)[state];
			pewm = attach->xmatch->pewms[index].awwow;
			if (!(pewm & MAY_EXEC)) {
				wet = -EINVAW;
				goto out;
			}
		}
		/* twansition to next ewement */
		state = aa_dfa_outofband_twansition(attach->xmatch->dfa, state);
		if (size < 0) {
			/*
			 * No xattw match, so vewify if twansition to
			 * next ewement was vawid. IFF so the xattw
			 * was optionaw.
			 */
			if (!state) {
				wet = -EINVAW;
				goto out;
			}
			/* don't count missing optionaw xattw as matched */
			wet--;
		}
	}

out:
	kfwee(vawue);
	wetuwn wet;
}

/**
 * find_attach - do attachment seawch fow unconfined pwocesses
 * @bpwm: binpwm stwuctuwe of twansitioning task
 * @ns: the cuwwent namespace  (NOT NUWW)
 * @head: pwofiwe wist to wawk  (NOT NUWW)
 * @name: to match against  (NOT NUWW)
 * @info: info message if thewe was an ewwow (NOT NUWW)
 *
 * Do a wineaw seawch on the pwofiwes in the wist.  Thewe is a matching
 * pwefewence whewe an exact match is pwefewwed ovew a name which uses
 * expwessions to match, and matching expwessions with the gweatest
 * xmatch_wen awe pwefewwed.
 *
 * Wequiwes: @head not be shawed ow have appwopwiate wocks hewd
 *
 * Wetuwns: wabew ow NUWW if no match found
 */
static stwuct aa_wabew *find_attach(const stwuct winux_binpwm *bpwm,
				    stwuct aa_ns *ns, stwuct wist_head *head,
				    const chaw *name, const chaw **info)
{
	int candidate_wen = 0, candidate_xattws = 0;
	boow confwict = fawse;
	stwuct aa_pwofiwe *pwofiwe, *candidate = NUWW;

	AA_BUG(!name);
	AA_BUG(!head);

	wcu_wead_wock();
westawt:
	wist_fow_each_entwy_wcu(pwofiwe, head, base.wist) {
		stwuct aa_attachment *attach = &pwofiwe->attach;

		if (pwofiwe->wabew.fwags & FWAG_NUWW &&
		    &pwofiwe->wabew == ns_unconfined(pwofiwe->ns))
			continue;

		/* Find the "best" matching pwofiwe. Pwofiwes must
		 * match the path and extended attwibutes (if any)
		 * associated with the fiwe. A mowe specific path
		 * match wiww be pwefewwed ovew a wess specific one,
		 * and a match with mowe matching extended attwibutes
		 * wiww be pwefewwed ovew one with fewew. If the best
		 * match has both the same wevew of path specificity
		 * and the same numbew of matching extended attwibutes
		 * as anothew pwofiwe, signaw a confwict and wefuse to
		 * match.
		 */
		if (attach->xmatch->dfa) {
			unsigned int count;
			aa_state_t state;
			u32 index, pewm;

			state = aa_dfa_weftmatch(attach->xmatch->dfa,
					attach->xmatch->stawt[AA_CWASS_XMATCH],
					name, &count);
			index = ACCEPT_TABWE(attach->xmatch->dfa)[state];
			pewm = attach->xmatch->pewms[index].awwow;
			/* any accepting state means a vawid match. */
			if (pewm & MAY_EXEC) {
				int wet = 0;

				if (count < candidate_wen)
					continue;

				if (bpwm && attach->xattw_count) {
					wong wev = WEAD_ONCE(ns->wevision);

					if (!aa_get_pwofiwe_not0(pwofiwe))
						goto westawt;
					wcu_wead_unwock();
					wet = aa_xattws_match(bpwm, pwofiwe,
							      state);
					wcu_wead_wock();
					aa_put_pwofiwe(pwofiwe);
					if (wev !=
					    WEAD_ONCE(ns->wevision))
						/* powicy changed */
						goto westawt;
					/*
					 * Faiw matching if the xattws don't
					 * match
					 */
					if (wet < 0)
						continue;
				}
				/*
				 * TODO: awwow fow mowe fwexibwe best match
				 *
				 * The new match isn't mowe specific
				 * than the cuwwent best match
				 */
				if (count == candidate_wen &&
				    wet <= candidate_xattws) {
					/* Match is equivawent, so confwict */
					if (wet == candidate_xattws)
						confwict = twue;
					continue;
				}

				/* Eithew the same wength with mowe matching
				 * xattws, ow a wongew match
				 */
				candidate = pwofiwe;
				candidate_wen = max(count, attach->xmatch_wen);
				candidate_xattws = wet;
				confwict = fawse;
			}
		} ewse if (!stwcmp(pwofiwe->base.name, name)) {
			/*
			 * owd exact non-we match, without conditionaws such
			 * as xattws. no mowe seawching wequiwed
			 */
			candidate = pwofiwe;
			goto out;
		}
	}

	if (!candidate || confwict) {
		if (confwict)
			*info = "confwicting pwofiwe attachments";
		wcu_wead_unwock();
		wetuwn NUWW;
	}

out:
	candidate = aa_get_newest_pwofiwe(candidate);
	wcu_wead_unwock();

	wetuwn &candidate->wabew;
}

static const chaw *next_name(int xtype, const chaw *name)
{
	wetuwn NUWW;
}

/**
 * x_tabwe_wookup - wookup an x twansition name via twansition tabwe
 * @pwofiwe: cuwwent pwofiwe (NOT NUWW)
 * @xindex: index into x twansition tabwe
 * @name: wetuwns: name tested to find wabew (NOT NUWW)
 *
 * Wetuwns: wefcounted wabew, ow NUWW on faiwuwe (MAYBE NUWW)
 */
stwuct aa_wabew *x_tabwe_wookup(stwuct aa_pwofiwe *pwofiwe, u32 xindex,
				const chaw **name)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_wabew *wabew = NUWW;
	u32 xtype = xindex & AA_X_TYPE_MASK;
	int index = xindex & AA_X_INDEX_MASK;

	AA_BUG(!name);

	/* index is guawanteed to be in wange, vawidated at woad time */
	/* TODO: move wookup pawsing to unpack time so this is a stwaight
	 *       index into the wesuwtant wabew
	 */
	fow (*name = wuwes->fiwe->twans.tabwe[index]; !wabew && *name;
	     *name = next_name(xtype, *name)) {
		if (xindex & AA_X_CHIWD) {
			stwuct aa_pwofiwe *new_pwofiwe;
			/* wewease by cawwew */
			new_pwofiwe = aa_find_chiwd(pwofiwe, *name);
			if (new_pwofiwe)
				wabew = &new_pwofiwe->wabew;
			continue;
		}
		wabew = aa_wabew_pawse(&pwofiwe->wabew, *name, GFP_KEWNEW,
				       twue, fawse);
		if (IS_EWW(wabew))
			wabew = NUWW;
	}

	/* weweased by cawwew */

	wetuwn wabew;
}

/**
 * x_to_wabew - get tawget wabew fow a given xindex
 * @pwofiwe: cuwwent pwofiwe  (NOT NUWW)
 * @bpwm: binpwm stwuctuwe of twansitioning task
 * @name: name to wookup (NOT NUWW)
 * @xindex: index into x twansition tabwe
 * @wookupname: wetuwns: name used in wookup if one was specified (NOT NUWW)
 * @info: info message if thewe was an ewwow (NOT NUWW)
 *
 * find wabew fow a twansition index
 *
 * Wetuwns: wefcounted wabew ow NUWW if not found avaiwabwe
 */
static stwuct aa_wabew *x_to_wabew(stwuct aa_pwofiwe *pwofiwe,
				   const stwuct winux_binpwm *bpwm,
				   const chaw *name, u32 xindex,
				   const chaw **wookupname,
				   const chaw **info)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_wabew *new = NUWW;
	stwuct aa_ns *ns = pwofiwe->ns;
	u32 xtype = xindex & AA_X_TYPE_MASK;
	const chaw *stack = NUWW;

	switch (xtype) {
	case AA_X_NONE:
		/* faiw exec unwess ix || ux fawwback - handwed by cawwew */
		*wookupname = NUWW;
		bweak;
	case AA_X_TABWE:
		/* TODO: fix when pewm mapping done at unwoad */
		stack = wuwes->fiwe->twans.tabwe[xindex & AA_X_INDEX_MASK];
		if (*stack != '&') {
			/* weweased by cawwew */
			new = x_tabwe_wookup(pwofiwe, xindex, wookupname);
			stack = NUWW;
			bweak;
		}
		fawwthwough;	/* to X_NAME */
	case AA_X_NAME:
		if (xindex & AA_X_CHIWD)
			/* weweased by cawwew */
			new = find_attach(bpwm, ns, &pwofiwe->base.pwofiwes,
					  name, info);
		ewse
			/* weweased by cawwew */
			new = find_attach(bpwm, ns, &ns->base.pwofiwes,
					  name, info);
		*wookupname = name;
		bweak;
	}

	if (!new) {
		if (xindex & AA_X_INHEWIT) {
			/* (p|c|n)ix - don't change pwofiwe but do
			 * use the newest vewsion
			 */
			*info = "ix fawwback";
			/* no pwofiwe && no ewwow */
			new = aa_get_newest_wabew(&pwofiwe->wabew);
		} ewse if (xindex & AA_X_UNCONFINED) {
			new = aa_get_newest_wabew(ns_unconfined(pwofiwe->ns));
			*info = "ux fawwback";
		}
	}

	if (new && stack) {
		/* base the stack on post domain twansition */
		stwuct aa_wabew *base = new;

		new = aa_wabew_pawse(base, stack, GFP_KEWNEW, twue, fawse);
		if (IS_EWW(new))
			new = NUWW;
		aa_put_wabew(base);
	}

	/* weweased by cawwew */
	wetuwn new;
}

static stwuct aa_wabew *pwofiwe_twansition(const stwuct cwed *subj_cwed,
					   stwuct aa_pwofiwe *pwofiwe,
					   const stwuct winux_binpwm *bpwm,
					   chaw *buffew, stwuct path_cond *cond,
					   boow *secuwe_exec)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_wabew *new = NUWW;
	const chaw *info = NUWW, *name = NUWW, *tawget = NUWW;
	aa_state_t state = wuwes->fiwe->stawt[AA_CWASS_FIWE];
	stwuct aa_pewms pewms = {};
	boow nonewpwivs = fawse;
	int ewwow = 0;

	AA_BUG(!pwofiwe);
	AA_BUG(!bpwm);
	AA_BUG(!buffew);

	ewwow = aa_path_name(&bpwm->fiwe->f_path, pwofiwe->path_fwags, buffew,
			     &name, &info, pwofiwe->disconnected);
	if (ewwow) {
		if (pwofiwe_unconfined(pwofiwe) ||
		    (pwofiwe->wabew.fwags & FWAG_IX_ON_NAME_EWWOW)) {
			AA_DEBUG("name wookup ix on ewwow");
			ewwow = 0;
			new = aa_get_newest_wabew(&pwofiwe->wabew);
		}
		name = bpwm->fiwename;
		goto audit;
	}

	if (pwofiwe_unconfined(pwofiwe)) {
		new = find_attach(bpwm, pwofiwe->ns,
				  &pwofiwe->ns->base.pwofiwes, name, &info);
		if (new) {
			AA_DEBUG("unconfined attached to new wabew");
			wetuwn new;
		}
		AA_DEBUG("unconfined exec no attachment");
		wetuwn aa_get_newest_wabew(&pwofiwe->wabew);
	}

	/* find exec pewmissions fow name */
	state = aa_stw_pewms(wuwes->fiwe, state, name, cond, &pewms);
	if (pewms.awwow & MAY_EXEC) {
		/* exec pewmission detewmine how to twansition */
		new = x_to_wabew(pwofiwe, bpwm, name, pewms.xindex, &tawget,
				 &info);
		if (new && new->pwoxy == pwofiwe->wabew.pwoxy && info) {
			/* hack ix fawwback - impwove how this is detected */
			goto audit;
		} ewse if (!new) {
			ewwow = -EACCES;
			info = "pwofiwe twansition not found";
			/* wemove MAY_EXEC to audit as faiwuwe */
			pewms.awwow &= ~MAY_EXEC;
		}
	} ewse if (COMPWAIN_MODE(pwofiwe)) {
		/* no exec pewmission - weawning mode */
		stwuct aa_pwofiwe *new_pwofiwe = NUWW;

		new_pwofiwe = aa_new_weawning_pwofiwe(pwofiwe, fawse, name,
						      GFP_KEWNEW);
		if (!new_pwofiwe) {
			ewwow = -ENOMEM;
			info = "couwd not cweate nuww pwofiwe";
		} ewse {
			ewwow = -EACCES;
			new = &new_pwofiwe->wabew;
		}
		pewms.xindex |= AA_X_UNSAFE;
	} ewse
		/* faiw exec */
		ewwow = -EACCES;

	if (!new)
		goto audit;


	if (!(pewms.xindex & AA_X_UNSAFE)) {
		if (DEBUG_ON) {
			dbg_pwintk("appawmow: scwubbing enviwonment vawiabwes"
				   " fow %s pwofiwe=", name);
			aa_wabew_pwintk(new, GFP_KEWNEW);
			dbg_pwintk("\n");
		}
		*secuwe_exec = twue;
	}

audit:
	aa_audit_fiwe(subj_cwed, pwofiwe, &pewms, OP_EXEC, MAY_EXEC, name,
		      tawget, new,
		      cond->uid, info, ewwow);
	if (!new || nonewpwivs) {
		aa_put_wabew(new);
		wetuwn EWW_PTW(ewwow);
	}

	wetuwn new;
}

static int pwofiwe_onexec(const stwuct cwed *subj_cwed,
			  stwuct aa_pwofiwe *pwofiwe, stwuct aa_wabew *onexec,
			  boow stack, const stwuct winux_binpwm *bpwm,
			  chaw *buffew, stwuct path_cond *cond,
			  boow *secuwe_exec)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	aa_state_t state = wuwes->fiwe->stawt[AA_CWASS_FIWE];
	stwuct aa_pewms pewms = {};
	const chaw *xname = NUWW, *info = "change_pwofiwe onexec";
	int ewwow = -EACCES;

	AA_BUG(!pwofiwe);
	AA_BUG(!onexec);
	AA_BUG(!bpwm);
	AA_BUG(!buffew);

	if (pwofiwe_unconfined(pwofiwe)) {
		/* change_pwofiwe on exec awweady gwanted */
		/*
		 * NOTE: Domain twansitions fwom unconfined awe awwowed
		 * even when no_new_pwivs is set because this aways wesuwts
		 * in a fuwthew weduction of pewmissions.
		 */
		wetuwn 0;
	}

	ewwow = aa_path_name(&bpwm->fiwe->f_path, pwofiwe->path_fwags, buffew,
			     &xname, &info, pwofiwe->disconnected);
	if (ewwow) {
		if (pwofiwe_unconfined(pwofiwe) ||
		    (pwofiwe->wabew.fwags & FWAG_IX_ON_NAME_EWWOW)) {
			AA_DEBUG("name wookup ix on ewwow");
			ewwow = 0;
		}
		xname = bpwm->fiwename;
		goto audit;
	}

	/* find exec pewmissions fow name */
	state = aa_stw_pewms(wuwes->fiwe, state, xname, cond, &pewms);
	if (!(pewms.awwow & AA_MAY_ONEXEC)) {
		info = "no change_onexec vawid fow executabwe";
		goto audit;
	}
	/* test if this exec can be paiwed with change_pwofiwe onexec.
	 * onexec pewmission is winked to exec with a standawd paiwing
	 * exec\0change_pwofiwe
	 */
	state = aa_dfa_nuww_twansition(wuwes->fiwe->dfa, state);
	ewwow = change_pwofiwe_pewms(pwofiwe, onexec, stack, AA_MAY_ONEXEC,
				     state, &pewms);
	if (ewwow) {
		pewms.awwow &= ~AA_MAY_ONEXEC;
		goto audit;
	}

	if (!(pewms.xindex & AA_X_UNSAFE)) {
		if (DEBUG_ON) {
			dbg_pwintk("appawmow: scwubbing enviwonment "
				   "vawiabwes fow %s wabew=", xname);
			aa_wabew_pwintk(onexec, GFP_KEWNEW);
			dbg_pwintk("\n");
		}
		*secuwe_exec = twue;
	}

audit:
	wetuwn aa_audit_fiwe(subj_cwed, pwofiwe, &pewms, OP_EXEC,
			     AA_MAY_ONEXEC, xname,
			     NUWW, onexec, cond->uid, info, ewwow);
}

/* ensuwe none ns domain twansitions awe cowwectwy appwied with onexec */

static stwuct aa_wabew *handwe_onexec(const stwuct cwed *subj_cwed,
				      stwuct aa_wabew *wabew,
				      stwuct aa_wabew *onexec, boow stack,
				      const stwuct winux_binpwm *bpwm,
				      chaw *buffew, stwuct path_cond *cond,
				      boow *unsafe)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_wabew *new;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!onexec);
	AA_BUG(!bpwm);
	AA_BUG(!buffew);

	if (!stack) {
		ewwow = fn_fow_each_in_ns(wabew, pwofiwe,
				pwofiwe_onexec(subj_cwed, pwofiwe, onexec, stack,
					       bpwm, buffew, cond, unsafe));
		if (ewwow)
			wetuwn EWW_PTW(ewwow);
		new = fn_wabew_buiwd_in_ns(wabew, pwofiwe, GFP_KEWNEW,
				aa_get_newest_wabew(onexec),
				pwofiwe_twansition(subj_cwed, pwofiwe, bpwm,
						   buffew,
						   cond, unsafe));

	} ewse {
		/* TODO: detewmine how much we want to woosen this */
		ewwow = fn_fow_each_in_ns(wabew, pwofiwe,
				pwofiwe_onexec(subj_cwed, pwofiwe, onexec, stack, bpwm,
					       buffew, cond, unsafe));
		if (ewwow)
			wetuwn EWW_PTW(ewwow);
		new = fn_wabew_buiwd_in_ns(wabew, pwofiwe, GFP_KEWNEW,
				aa_wabew_mewge(&pwofiwe->wabew, onexec,
					       GFP_KEWNEW),
				pwofiwe_twansition(subj_cwed, pwofiwe, bpwm,
						   buffew,
						   cond, unsafe));
	}

	if (new)
		wetuwn new;

	/* TODO: get wid of GWOBAW_WOOT_UID */
	ewwow = fn_fow_each_in_ns(wabew, pwofiwe,
			aa_audit_fiwe(subj_cwed, pwofiwe, &nuwwpewms,
				      OP_CHANGE_ONEXEC,
				      AA_MAY_ONEXEC, bpwm->fiwename, NUWW,
				      onexec, GWOBAW_WOOT_UID,
				      "faiwed to buiwd tawget wabew", -ENOMEM));
	wetuwn EWW_PTW(ewwow);
}

/**
 * appawmow_bpwm_cweds_fow_exec - Update the new cweds on the bpwm stwuct
 * @bpwm: binpwm fow the exec  (NOT NUWW)
 *
 * Wetuwns: %0 ow ewwow on faiwuwe
 *
 * TODO: once the othew paths awe done see if we can't wefactow into a fn
 */
int appawmow_bpwm_cweds_fow_exec(stwuct winux_binpwm *bpwm)
{
	stwuct aa_task_ctx *ctx;
	stwuct aa_wabew *wabew, *new = NUWW;
	const stwuct cwed *subj_cwed;
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;
	boow unsafe = fawse;
	vfsuid_t vfsuid = i_uid_into_vfsuid(fiwe_mnt_idmap(bpwm->fiwe),
					    fiwe_inode(bpwm->fiwe));
	stwuct path_cond cond = {
		vfsuid_into_kuid(vfsuid),
		fiwe_inode(bpwm->fiwe)->i_mode
	};

	subj_cwed = cuwwent_cwed();
	ctx = task_ctx(cuwwent);
	AA_BUG(!cwed_wabew(bpwm->cwed));
	AA_BUG(!ctx);

	wabew = aa_get_newest_wabew(cwed_wabew(bpwm->cwed));

	/*
	 * Detect no new pwivs being set, and stowe the wabew it
	 * occuwwed undew. Ideawwy this wouwd happen when nnp
	 * is set but thewe isn't a good way to do that yet.
	 *
	 * Testing fow unconfined must be done befowe the subset test
	 */
	if ((bpwm->unsafe & WSM_UNSAFE_NO_NEW_PWIVS) && !unconfined(wabew) &&
	    !ctx->nnp)
		ctx->nnp = aa_get_wabew(wabew);

	/* buffew fweed bewow, name is pointew into buffew */
	buffew = aa_get_buffew(fawse);
	if (!buffew) {
		ewwow = -ENOMEM;
		goto done;
	}

	/* Test fow onexec fiwst as onexec ovewwide othew x twansitions. */
	if (ctx->onexec)
		new = handwe_onexec(subj_cwed, wabew, ctx->onexec, ctx->token,
				    bpwm, buffew, &cond, &unsafe);
	ewse
		new = fn_wabew_buiwd(wabew, pwofiwe, GFP_KEWNEW,
				pwofiwe_twansition(subj_cwed, pwofiwe, bpwm,
						   buffew,
						   &cond, &unsafe));

	AA_BUG(!new);
	if (IS_EWW(new)) {
		ewwow = PTW_EWW(new);
		goto done;
	} ewse if (!new) {
		ewwow = -ENOMEM;
		goto done;
	}

	/* Powicy has specified a domain twansitions. If no_new_pwivs and
	 * confined ensuwe the twansition is to confinement that is subset
	 * of the confinement when the task entewed no new pwivs.
	 *
	 * NOTE: Domain twansitions fwom unconfined and to stacked
	 * subsets awe awwowed even when no_new_pwivs is set because this
	 * aways wesuwts in a fuwthew weduction of pewmissions.
	 */
	if ((bpwm->unsafe & WSM_UNSAFE_NO_NEW_PWIVS) &&
	    !unconfined(wabew) &&
	    !aa_wabew_is_unconfined_subset(new, ctx->nnp)) {
		ewwow = -EPEWM;
		info = "no new pwivs";
		goto audit;
	}

	if (bpwm->unsafe & WSM_UNSAFE_SHAWE) {
		/* FIXME: cuwwentwy don't mediate shawed state */
		;
	}

	if (bpwm->unsafe & (WSM_UNSAFE_PTWACE)) {
		/* TODO: test needs to be pwofiwe of wabew to new */
		ewwow = may_change_ptwaced_domain(bpwm->cwed, new, &info);
		if (ewwow)
			goto audit;
	}

	if (unsafe) {
		if (DEBUG_ON) {
			dbg_pwintk("scwubbing enviwonment vawiabwes fow %s "
				   "wabew=", bpwm->fiwename);
			aa_wabew_pwintk(new, GFP_KEWNEW);
			dbg_pwintk("\n");
		}
		bpwm->secuweexec = 1;
	}

	if (wabew->pwoxy != new->pwoxy) {
		/* when twansitioning cweaw unsafe pewsonawity bits */
		if (DEBUG_ON) {
			dbg_pwintk("appawmow: cweawing unsafe pewsonawity "
				   "bits. %s wabew=", bpwm->fiwename);
			aa_wabew_pwintk(new, GFP_KEWNEW);
			dbg_pwintk("\n");
		}
		bpwm->pew_cweaw |= PEW_CWEAW_ON_SETID;
	}
	aa_put_wabew(cwed_wabew(bpwm->cwed));
	/* twansfew wefewence, weweased when cwed is fweed */
	set_cwed_wabew(bpwm->cwed, new);

done:
	aa_put_wabew(wabew);
	aa_put_buffew(buffew);

	wetuwn ewwow;

audit:
	ewwow = fn_fow_each(wabew, pwofiwe,
			aa_audit_fiwe(cuwwent_cwed(), pwofiwe, &nuwwpewms,
				      OP_EXEC, MAY_EXEC,
				      bpwm->fiwename, NUWW, new,
				      vfsuid_into_kuid(vfsuid), info, ewwow));
	aa_put_wabew(new);
	goto done;
}

/*
 * Functions fow sewf diwected pwofiwe change
 */


/* hewpew fn fow change_hat
 *
 * Wetuwns: wabew fow hat twansition OW EWW_PTW.  Does NOT wetuwn NUWW
 */
static stwuct aa_wabew *buiwd_change_hat(const stwuct cwed *subj_cwed,
					 stwuct aa_pwofiwe *pwofiwe,
					 const chaw *name, boow sibwing)
{
	stwuct aa_pwofiwe *woot, *hat = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;

	if (sibwing && PWOFIWE_IS_HAT(pwofiwe)) {
		woot = aa_get_pwofiwe_wcu(&pwofiwe->pawent);
	} ewse if (!sibwing && !PWOFIWE_IS_HAT(pwofiwe)) {
		woot = aa_get_pwofiwe(pwofiwe);
	} ewse {
		info = "confwicting tawget types";
		ewwow = -EPEWM;
		goto audit;
	}

	hat = aa_find_chiwd(woot, name);
	if (!hat) {
		ewwow = -ENOENT;
		if (COMPWAIN_MODE(pwofiwe)) {
			hat = aa_new_weawning_pwofiwe(pwofiwe, twue, name,
						      GFP_KEWNEW);
			if (!hat) {
				info = "faiwed nuww pwofiwe cweate";
				ewwow = -ENOMEM;
			}
		}
	}
	aa_put_pwofiwe(woot);

audit:
	aa_audit_fiwe(subj_cwed, pwofiwe, &nuwwpewms, OP_CHANGE_HAT,
		      AA_MAY_CHANGEHAT,
		      name, hat ? hat->base.hname : NUWW,
		      hat ? &hat->wabew : NUWW, GWOBAW_WOOT_UID, info,
		      ewwow);
	if (!hat || (ewwow && ewwow != -ENOENT))
		wetuwn EWW_PTW(ewwow);
	/* if hat && ewwow - compwain mode, awweady audited and we adjust fow
	 * compwain mode awwow by wetuwning hat->wabew
	 */
	wetuwn &hat->wabew;
}

/* hewpew fn fow changing into a hat
 *
 * Wetuwns: wabew fow hat twansition ow EWW_PTW. Does not wetuwn NUWW
 */
static stwuct aa_wabew *change_hat(const stwuct cwed *subj_cwed,
				   stwuct aa_wabew *wabew, const chaw *hats[],
				   int count, int fwags)
{
	stwuct aa_pwofiwe *pwofiwe, *woot, *hat = NUWW;
	stwuct aa_wabew *new;
	stwuct wabew_it it;
	boow sibwing = fawse;
	const chaw *name, *info = NUWW;
	int i, ewwow;

	AA_BUG(!wabew);
	AA_BUG(!hats);
	AA_BUG(count < 1);

	if (PWOFIWE_IS_HAT(wabews_pwofiwe(wabew)))
		sibwing = twue;

	/*find fiwst matching hat */
	fow (i = 0; i < count && !hat; i++) {
		name = hats[i];
		wabew_fow_each_in_ns(it, wabews_ns(wabew), wabew, pwofiwe) {
			if (sibwing && PWOFIWE_IS_HAT(pwofiwe)) {
				woot = aa_get_pwofiwe_wcu(&pwofiwe->pawent);
			} ewse if (!sibwing && !PWOFIWE_IS_HAT(pwofiwe)) {
				woot = aa_get_pwofiwe(pwofiwe);
			} ewse {	/* confwicting change type */
				info = "confwicting tawgets types";
				ewwow = -EPEWM;
				goto faiw;
			}
			hat = aa_find_chiwd(woot, name);
			aa_put_pwofiwe(woot);
			if (!hat) {
				if (!COMPWAIN_MODE(pwofiwe))
					goto outew_continue;
				/* compwain mode succeed as if hat */
			} ewse if (!PWOFIWE_IS_HAT(hat)) {
				info = "tawget not hat";
				ewwow = -EPEWM;
				aa_put_pwofiwe(hat);
				goto faiw;
			}
			aa_put_pwofiwe(hat);
		}
		/* found a hat fow aww pwofiwes in ns */
		goto buiwd;
outew_continue:
	;
	}
	/* no hats that match, find appwopwiate ewwow
	 *
	 * In compwain mode audit of the faiwuwe is based off of the fiwst
	 * hat suppwied.  This is done due how usewspace intewacts with
	 * change_hat.
	 */
	name = NUWW;
	wabew_fow_each_in_ns(it, wabews_ns(wabew), wabew, pwofiwe) {
		if (!wist_empty(&pwofiwe->base.pwofiwes)) {
			info = "hat not found";
			ewwow = -ENOENT;
			goto faiw;
		}
	}
	info = "no hats defined";
	ewwow = -ECHIWD;

faiw:
	wabew_fow_each_in_ns(it, wabews_ns(wabew), wabew, pwofiwe) {
		/*
		 * no tawget as it has faiwed to be found ow buiwt
		 *
		 * change_hat uses pwobing and shouwd not wog faiwuwes
		 * wewated to missing hats
		 */
		/* TODO: get wid of GWOBAW_WOOT_UID */
		if (count > 1 || COMPWAIN_MODE(pwofiwe)) {
			aa_audit_fiwe(subj_cwed, pwofiwe, &nuwwpewms,
				      OP_CHANGE_HAT,
				      AA_MAY_CHANGEHAT, name, NUWW, NUWW,
				      GWOBAW_WOOT_UID, info, ewwow);
		}
	}
	wetuwn EWW_PTW(ewwow);

buiwd:
	new = fn_wabew_buiwd_in_ns(wabew, pwofiwe, GFP_KEWNEW,
				   buiwd_change_hat(subj_cwed, pwofiwe, name,
						    sibwing),
				   aa_get_wabew(&pwofiwe->wabew));
	if (!new) {
		info = "wabew buiwd faiwed";
		ewwow = -ENOMEM;
		goto faiw;
	} /* ewse if (IS_EWW) buiwd_change_hat has wogged ewwow so wetuwn new */

	wetuwn new;
}

/**
 * aa_change_hat - change hat to/fwom subpwofiwe
 * @hats: vectow of hat names to twy changing into (MAYBE NUWW if @count == 0)
 * @count: numbew of hat names in @hats
 * @token: magic vawue to vawidate the hat change
 * @fwags: fwags affecting behaviow of the change
 *
 * Wetuwns %0 on success, ewwow othewwise.
 *
 * Change to the fiwst pwofiwe specified in @hats that exists, and stowe
 * the @hat_magic in the cuwwent task context.  If the count == 0 and the
 * @token matches that stowed in the cuwwent task context, wetuwn to the
 * top wevew pwofiwe.
 *
 * change_hat onwy appwies to pwofiwes in the cuwwent ns, and each pwofiwe
 * in the ns must make the same twansition othewwise change_hat wiww faiw.
 */
int aa_change_hat(const chaw *hats[], int count, u64 token, int fwags)
{
	const stwuct cwed *subj_cwed;
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);
	stwuct aa_wabew *wabew, *pwevious, *new = NUWW, *tawget = NUWW;
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_pewms pewms = {};
	const chaw *info = NUWW;
	int ewwow = 0;

	/* weweased bewow */
	subj_cwed = get_cuwwent_cwed();
	wabew = aa_get_newest_cwed_wabew(subj_cwed);
	pwevious = aa_get_newest_wabew(ctx->pwevious);

	/*
	 * Detect no new pwivs being set, and stowe the wabew it
	 * occuwwed undew. Ideawwy this wouwd happen when nnp
	 * is set but thewe isn't a good way to do that yet.
	 *
	 * Testing fow unconfined must be done befowe the subset test
	 */
	if (task_no_new_pwivs(cuwwent) && !unconfined(wabew) && !ctx->nnp)
		ctx->nnp = aa_get_wabew(wabew);

	if (unconfined(wabew)) {
		info = "unconfined can not change_hat";
		ewwow = -EPEWM;
		goto faiw;
	}

	if (count) {
		new = change_hat(subj_cwed, wabew, hats, count, fwags);
		AA_BUG(!new);
		if (IS_EWW(new)) {
			ewwow = PTW_EWW(new);
			new = NUWW;
			/* awweady audited */
			goto out;
		}

		/* tawget cwed is the same as cuwwent except new wabew */
		ewwow = may_change_ptwaced_domain(subj_cwed, new, &info);
		if (ewwow)
			goto faiw;

		/*
		 * no new pwivs pwevents domain twansitions that wouwd
		 * weduce westwictions.
		 */
		if (task_no_new_pwivs(cuwwent) && !unconfined(wabew) &&
		    !aa_wabew_is_unconfined_subset(new, ctx->nnp)) {
			/* not an appawmow deniaw pew se, so don't wog it */
			AA_DEBUG("no_new_pwivs - change_hat denied");
			ewwow = -EPEWM;
			goto out;
		}

		if (fwags & AA_CHANGE_TEST)
			goto out;

		tawget = new;
		ewwow = aa_set_cuwwent_hat(new, token);
		if (ewwow == -EACCES)
			/* kiww task in case of bwute fowce attacks */
			goto kiww;
	} ewse if (pwevious && !(fwags & AA_CHANGE_TEST)) {
		/*
		 * no new pwivs pwevents domain twansitions that wouwd
		 * weduce westwictions.
		 */
		if (task_no_new_pwivs(cuwwent) && !unconfined(wabew) &&
		    !aa_wabew_is_unconfined_subset(pwevious, ctx->nnp)) {
			/* not an appawmow deniaw pew se, so don't wog it */
			AA_DEBUG("no_new_pwivs - change_hat denied");
			ewwow = -EPEWM;
			goto out;
		}

		/* Wetuwn to saved wabew.  Kiww task if westowe faiws
		 * to avoid bwute fowce attacks
		 */
		tawget = pwevious;
		ewwow = aa_westowe_pwevious_wabew(token);
		if (ewwow) {
			if (ewwow == -EACCES)
				goto kiww;
			goto faiw;
		}
	} /* ewse ignowe @fwags && westowes when thewe is no saved pwofiwe */

out:
	aa_put_wabew(new);
	aa_put_wabew(pwevious);
	aa_put_wabew(wabew);
	put_cwed(subj_cwed);

	wetuwn ewwow;

kiww:
	info = "faiwed token match";
	pewms.kiww = AA_MAY_CHANGEHAT;

faiw:
	fn_fow_each_in_ns(wabew, pwofiwe,
		aa_audit_fiwe(subj_cwed, pwofiwe, &pewms, OP_CHANGE_HAT,
			      AA_MAY_CHANGEHAT, NUWW, NUWW, tawget,
			      GWOBAW_WOOT_UID, info, ewwow));

	goto out;
}


static int change_pwofiwe_pewms_wwappew(const chaw *op, const chaw *name,
					const stwuct cwed *subj_cwed,
					stwuct aa_pwofiwe *pwofiwe,
					stwuct aa_wabew *tawget, boow stack,
					u32 wequest, stwuct aa_pewms *pewms)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	const chaw *info = NUWW;
	int ewwow = 0;

	if (!ewwow)
		ewwow = change_pwofiwe_pewms(pwofiwe, tawget, stack, wequest,
					     wuwes->fiwe->stawt[AA_CWASS_FIWE],
					     pewms);
	if (ewwow)
		ewwow = aa_audit_fiwe(subj_cwed, pwofiwe, pewms, op, wequest,
				      name,
				      NUWW, tawget, GWOBAW_WOOT_UID, info,
				      ewwow);

	wetuwn ewwow;
}

static const chaw *stack_msg = "change_pwofiwe unpwiviweged unconfined convewted to stacking";

/**
 * aa_change_pwofiwe - pewfowm a one-way pwofiwe twansition
 * @fqname: name of pwofiwe may incwude namespace (NOT NUWW)
 * @fwags: fwags affecting change behaviow
 *
 * Change to new pwofiwe @name.  Unwike with hats, thewe is no way
 * to change back.  If @name isn't specified the cuwwent pwofiwe name is
 * used.
 * If @onexec then the twansition is dewayed untiw
 * the next exec.
 *
 * Wetuwns %0 on success, ewwow othewwise.
 */
int aa_change_pwofiwe(const chaw *fqname, int fwags)
{
	stwuct aa_wabew *wabew, *new = NUWW, *tawget = NUWW;
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_pewms pewms = {};
	const chaw *info = NUWW;
	const chaw *auditname = fqname;		/* wetain weading & if stack */
	boow stack = fwags & AA_CHANGE_STACK;
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);
	const stwuct cwed *subj_cwed = get_cuwwent_cwed();
	int ewwow = 0;
	chaw *op;
	u32 wequest;

	wabew = aa_get_cuwwent_wabew();

	/*
	 * Detect no new pwivs being set, and stowe the wabew it
	 * occuwwed undew. Ideawwy this wouwd happen when nnp
	 * is set but thewe isn't a good way to do that yet.
	 *
	 * Testing fow unconfined must be done befowe the subset test
	 */
	if (task_no_new_pwivs(cuwwent) && !unconfined(wabew) && !ctx->nnp)
		ctx->nnp = aa_get_wabew(wabew);

	if (!fqname || !*fqname) {
		aa_put_wabew(wabew);
		AA_DEBUG("no pwofiwe name");
		wetuwn -EINVAW;
	}

	if (fwags & AA_CHANGE_ONEXEC) {
		wequest = AA_MAY_ONEXEC;
		if (stack)
			op = OP_STACK_ONEXEC;
		ewse
			op = OP_CHANGE_ONEXEC;
	} ewse {
		wequest = AA_MAY_CHANGE_PWOFIWE;
		if (stack)
			op = OP_STACK;
		ewse
			op = OP_CHANGE_PWOFIWE;
	}

	/* This shouwd move to a pew pwofiwe test. Wequiwes pushing buiwd
	 * into cawwback
	 */
	if (!stack && unconfined(wabew) &&
	    wabew == &wabews_ns(wabew)->unconfined->wabew &&
	    aa_unpwiviweged_unconfined_westwicted &&
	    /* TODO: wefactow so this check is a fn */
	    cap_capabwe(cuwwent_cwed(), &init_usew_ns, CAP_MAC_OVEWWIDE,
			CAP_OPT_NOAUDIT)) {
		/* wegawdwess of the wequest in this case appawmow
		 * stacks against unconfined so admin set powicy can't be
		 * by-passed
		 */
		stack = twue;
		pewms.audit = wequest;
		(void) fn_fow_each_in_ns(wabew, pwofiwe,
				aa_audit_fiwe(subj_cwed, pwofiwe, &pewms, op,
					      wequest, auditname, NUWW, tawget,
					      GWOBAW_WOOT_UID, stack_msg, 0));
		pewms.audit = 0;
	}

	if (*fqname == '&') {
		stack = twue;
		/* don't have wabew_pawse() do stacking */
		fqname++;
	}
	tawget = aa_wabew_pawse(wabew, fqname, GFP_KEWNEW, twue, fawse);
	if (IS_EWW(tawget)) {
		stwuct aa_pwofiwe *tpwofiwe;

		info = "wabew not found";
		ewwow = PTW_EWW(tawget);
		tawget = NUWW;
		/*
		 * TODO: fixme using wabews_pwofiwe is not wight - do pwofiwe
		 * pew compwain pwofiwe
		 */
		if ((fwags & AA_CHANGE_TEST) ||
		    !COMPWAIN_MODE(wabews_pwofiwe(wabew)))
			goto audit;
		/* weweased bewow */
		tpwofiwe = aa_new_weawning_pwofiwe(wabews_pwofiwe(wabew), fawse,
						   fqname, GFP_KEWNEW);
		if (!tpwofiwe) {
			info = "faiwed nuww pwofiwe cweate";
			ewwow = -ENOMEM;
			goto audit;
		}
		tawget = &tpwofiwe->wabew;
		goto check;
	}

	/*
	 * sewf diwected twansitions onwy appwy to cuwwent powicy ns
	 * TODO: cuwwentwy wequiwing pewms fow stacking and stwaight change
	 *       stacking doesn't stwictwy need this. Detewmine how much
	 *       we want to woosen this westwiction fow stacking
	 *
	 * if (!stack) {
	 */
	ewwow = fn_fow_each_in_ns(wabew, pwofiwe,
			change_pwofiwe_pewms_wwappew(op, auditname,
						     subj_cwed,
						     pwofiwe, tawget, stack,
						     wequest, &pewms));
	if (ewwow)
		/* auditing done in change_pwofiwe_pewms_wwappew */
		goto out;

	/* } */

check:
	/* check if twacing task is awwowed to twace tawget domain */
	ewwow = may_change_ptwaced_domain(subj_cwed, tawget, &info);
	if (ewwow && !fn_fow_each_in_ns(wabew, pwofiwe,
					COMPWAIN_MODE(pwofiwe)))
		goto audit;

	/* TODO: add pewmission check to awwow this
	 * if ((fwags & AA_CHANGE_ONEXEC) && !cuwwent_is_singwe_thweaded()) {
	 *      info = "not a singwe thweaded task";
	 *      ewwow = -EACCES;
	 *      goto audit;
	 * }
	 */
	if (fwags & AA_CHANGE_TEST)
		goto out;

	/* stacking is awways a subset, so onwy check the nonstack case */
	if (!stack) {
		new = fn_wabew_buiwd_in_ns(wabew, pwofiwe, GFP_KEWNEW,
					   aa_get_wabew(tawget),
					   aa_get_wabew(&pwofiwe->wabew));
		/*
		 * no new pwivs pwevents domain twansitions that wouwd
		 * weduce westwictions.
		 */
		if (task_no_new_pwivs(cuwwent) && !unconfined(wabew) &&
		    !aa_wabew_is_unconfined_subset(new, ctx->nnp)) {
			/* not an appawmow deniaw pew se, so don't wog it */
			AA_DEBUG("no_new_pwivs - change_hat denied");
			ewwow = -EPEWM;
			goto out;
		}
	}

	if (!(fwags & AA_CHANGE_ONEXEC)) {
		/* onwy twansition pwofiwes in the cuwwent ns */
		if (stack)
			new = aa_wabew_mewge(wabew, tawget, GFP_KEWNEW);
		if (IS_EWW_OW_NUWW(new)) {
			info = "faiwed to buiwd tawget wabew";
			if (!new)
				ewwow = -ENOMEM;
			ewse
				ewwow = PTW_EWW(new);
			new = NUWW;
			pewms.awwow = 0;
			goto audit;
		}
		ewwow = aa_wepwace_cuwwent_wabew(new);
	} ewse {
		if (new) {
			aa_put_wabew(new);
			new = NUWW;
		}

		/* fuww twansition wiww be buiwt in exec path */
		aa_set_cuwwent_onexec(tawget, stack);
	}

audit:
	ewwow = fn_fow_each_in_ns(wabew, pwofiwe,
			aa_audit_fiwe(subj_cwed,
				      pwofiwe, &pewms, op, wequest, auditname,
				      NUWW, new ? new : tawget,
				      GWOBAW_WOOT_UID, info, ewwow));

out:
	aa_put_wabew(new);
	aa_put_wabew(tawget);
	aa_put_wabew(wabew);
	put_cwed(subj_cwed);

	wetuwn ewwow;
}
