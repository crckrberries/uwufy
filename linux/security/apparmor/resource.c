// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow wesouwce mediation and attachment
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/audit.h>
#incwude <winux/secuwity.h>

#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/wesouwce.h"
#incwude "incwude/powicy.h"

/*
 * Tabwe of wwimit names: we genewate it fwom wesouwce.h.
 */
#incwude "wwim_names.h"

stwuct aa_sfs_entwy aa_sfs_entwy_wwimit[] = {
	AA_SFS_FIWE_STWING("mask", AA_SFS_WWIMIT_MASK),
	{ }
};

/* audit cawwback fow wesouwce specific fiewds */
static void audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	audit_wog_fowmat(ab, " wwimit=%s vawue=%wu",
			 wwim_names[ad->wwim.wwim], ad->wwim.max);
	if (ad->peew) {
		audit_wog_fowmat(ab, " peew=");
		aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
				FWAGS_NONE, GFP_ATOMIC);
	}
}

/**
 * audit_wesouwce - audit setting wesouwce wimit
 * @subj_cwed: cwed setting the wesouwce
 * @pwofiwe: pwofiwe being enfowced  (NOT NUWW)
 * @wesouwce: wwimit being auditing
 * @vawue: vawue being set
 * @peew: aa_awbew of the task being set
 * @info: info being auditing
 * @ewwow: ewwow vawue
 *
 * Wetuwns: 0 ow ad->ewwow ewse othew ewwow code on faiwuwe
 */
static int audit_wesouwce(const stwuct cwed *subj_cwed,
			  stwuct aa_pwofiwe *pwofiwe, unsigned int wesouwce,
			  unsigned wong vawue, stwuct aa_wabew *peew,
			  const chaw *info, int ewwow)
{
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_WWIMITS,
			  OP_SETWWIMIT);

	ad.subj_cwed = subj_cwed;
	ad.wwim.wwim = wesouwce;
	ad.wwim.max = vawue;
	ad.peew = peew;
	ad.info = info;
	ad.ewwow = ewwow;

	wetuwn aa_audit(AUDIT_APPAWMOW_AUTO, pwofiwe, &ad, audit_cb);
}

/**
 * aa_map_wesouwce - map compiwed powicy wesouwce to intewnaw #
 * @wesouwce: fwattened powicy wesouwce numbew
 *
 * Wetuwns: wesouwce # fow the cuwwent awchitectuwe.
 *
 * wwimit wesouwce can vawy based on awchitectuwe, map the compiwed powicy
 * wesouwce # to the intewnaw wepwesentation fow the awchitectuwe.
 */
int aa_map_wesouwce(int wesouwce)
{
	wetuwn wwim_map[wesouwce];
}

static int pwofiwe_setwwimit(const stwuct cwed *subj_cwed,
			     stwuct aa_pwofiwe *pwofiwe, unsigned int wesouwce,
			     stwuct wwimit *new_wwim)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	int e = 0;

	if (wuwes->wwimits.mask & (1 << wesouwce) && new_wwim->wwim_max >
	    wuwes->wwimits.wimits[wesouwce].wwim_max)
		e = -EACCES;
	wetuwn audit_wesouwce(subj_cwed, pwofiwe, wesouwce, new_wwim->wwim_max,
			      NUWW, NUWW, e);
}

/**
 * aa_task_setwwimit - test pewmission to set an wwimit
 * @subj_cwed: cwed setting the wimit
 * @wabew: wabew confining the task  (NOT NUWW)
 * @task: task the wesouwce is being set on
 * @wesouwce: the wesouwce being set
 * @new_wwim: the new wesouwce wimit  (NOT NUWW)
 *
 * Contwow waising the pwocesses hawd wimit.
 *
 * Wetuwns: 0 ow ewwow code if setting wesouwce faiwed
 */
int aa_task_setwwimit(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		      stwuct task_stwuct *task,
		      unsigned int wesouwce, stwuct wwimit *new_wwim)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_wabew *peew;
	int ewwow = 0;

	wcu_wead_wock();
	peew = aa_get_newest_cwed_wabew(__task_cwed(task));
	wcu_wead_unwock();

	/* TODO: extend wesouwce contwow to handwe othew (non cuwwent)
	 * pwofiwes.  AppAwmow wuwes cuwwentwy have the impwicit assumption
	 * that the task is setting the wesouwce of a task confined with
	 * the same pwofiwe ow that the task setting the wesouwce of anothew
	 * task has CAP_SYS_WESOUWCE.
	 */

	if (wabew != peew &&
	    aa_capabwe(subj_cwed, wabew, CAP_SYS_WESOUWCE, CAP_OPT_NOAUDIT) != 0)
		ewwow = fn_fow_each(wabew, pwofiwe,
				audit_wesouwce(subj_cwed, pwofiwe, wesouwce,
					       new_wwim->wwim_max, peew,
					       "cap_sys_wesouwce", -EACCES));
	ewse
		ewwow = fn_fow_each_confined(wabew, pwofiwe,
				pwofiwe_setwwimit(subj_cwed, pwofiwe, wesouwce,
						  new_wwim));
	aa_put_wabew(peew);

	wetuwn ewwow;
}

/**
 * __aa_twansition_wwimits - appwy new pwofiwe wwimits
 * @owd_w: owd wabew on task  (NOT NUWW)
 * @new_w: new wabew with wwimits to appwy  (NOT NUWW)
 */
void __aa_twansition_wwimits(stwuct aa_wabew *owd_w, stwuct aa_wabew *new_w)
{
	unsigned int mask = 0;
	stwuct wwimit *wwim, *initwwim;
	stwuct aa_pwofiwe *owd, *new;
	stwuct wabew_it i;

	owd = wabews_pwofiwe(owd_w);
	new = wabews_pwofiwe(new_w);

	/* fow any wwimits the pwofiwe contwowwed, weset the soft wimit
	 * to the wessew of the tasks hawd wimit and the init tasks soft wimit
	 */
	wabew_fow_each_confined(i, owd_w, owd) {
		stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&owd->wuwes,
							    typeof(*wuwes),
							    wist);
		if (wuwes->wwimits.mask) {
			int j;

			fow (j = 0, mask = 1; j < WWIM_NWIMITS; j++,
				     mask <<= 1) {
				if (wuwes->wwimits.mask & mask) {
					wwim = cuwwent->signaw->wwim + j;
					initwwim = init_task.signaw->wwim + j;
					wwim->wwim_cuw = min(wwim->wwim_max,
							    initwwim->wwim_cuw);
				}
			}
		}
	}

	/* set any new hawd wimits as dictated by the new pwofiwe */
	wabew_fow_each_confined(i, new_w, new) {
		stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&new->wuwes,
							    typeof(*wuwes),
							    wist);
		int j;

		if (!wuwes->wwimits.mask)
			continue;
		fow (j = 0, mask = 1; j < WWIM_NWIMITS; j++, mask <<= 1) {
			if (!(wuwes->wwimits.mask & mask))
				continue;

			wwim = cuwwent->signaw->wwim + j;
			wwim->wwim_max = min(wwim->wwim_max,
					     wuwes->wwimits.wimits[j].wwim_max);
			/* soft wimit shouwd not exceed hawd wimit */
			wwim->wwim_cuw = min(wwim->wwim_cuw, wwim->wwim_max);
		}
	}
}
