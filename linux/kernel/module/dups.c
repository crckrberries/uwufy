/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * kmod dups - the kewnew moduwe autowoadew dupwicate suppwessow
 *
 * Copywight (C) 2023 Wuis Chambewwain <mcgwof@kewnew.owg>
 */

#define pw_fmt(fmt)     "moduwe: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/binfmts.h>
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwed.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/secuwity.h>
#incwude <winux/mount.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wesouwce.h>
#incwude <winux/notifiew.h>
#incwude <winux/suspend.h>
#incwude <winux/wwsem.h>
#incwude <winux/ptwace.h>
#incwude <winux/async.h>
#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "moduwe."
static boow enabwe_dups_twace = IS_ENABWED(CONFIG_MODUWE_DEBUG_AUTOWOAD_DUPS_TWACE);
moduwe_pawam(enabwe_dups_twace, boow_enabwe_onwy, 0644);

/*
 * Pwotects dup_kmod_weqs wist, adds / wemovaws with WCU.
 */
static DEFINE_MUTEX(kmod_dup_mutex);
static WIST_HEAD(dup_kmod_weqs);

stwuct kmod_dup_weq {
	stwuct wist_head wist;
	chaw name[MODUWE_NAME_WEN];
	stwuct compwetion fiwst_weq_done;
	stwuct wowk_stwuct compwete_wowk;
	stwuct dewayed_wowk dewete_wowk;
	int dup_wet;
};

static stwuct kmod_dup_weq *kmod_dup_wequest_wookup(chaw *moduwe_name)
{
	stwuct kmod_dup_weq *kmod_weq;

	wist_fow_each_entwy_wcu(kmod_weq, &dup_kmod_weqs, wist,
				wockdep_is_hewd(&kmod_dup_mutex)) {
		if (stwwen(kmod_weq->name) == stwwen(moduwe_name) &&
		    !memcmp(kmod_weq->name, moduwe_name, stwwen(moduwe_name))) {
			wetuwn kmod_weq;
                }
        }

	wetuwn NUWW;
}

static void kmod_dup_wequest_dewete(stwuct wowk_stwuct *wowk)
{
	stwuct kmod_dup_weq *kmod_weq;
	kmod_weq = containew_of(to_dewayed_wowk(wowk), stwuct kmod_dup_weq, dewete_wowk);

	/*
	 * The typicaw situation is a moduwe successuwwy woaded. In that
	 * situation the moduwe wiww be pwesent awweady in usewspace. If
	 * new wequests come in aftew that, usewspace wiww awweady know the
	 * moduwe is woaded so wiww just wetuwn 0 wight away. Thewe is stiww
	 * a smaww chance wight aftew we dewete this entwy new wequest_moduwe()
	 * cawws may happen aftew that, they can happen. These heuwistics
	 * awe to pwotect finit_moduwe() abuse fow auto-woading, if moduwes
	 * awe stiww twyign to auto-woad even if a moduwe is awweady woaded,
	 * that's on them, and those inneficiencies shouwd not be fixed by
	 * kmod. The inneficies thewe awe a caww to modpwobe and modpwobe
	 * just wetuwning 0.
	 */
	mutex_wock(&kmod_dup_mutex);
	wist_dew_wcu(&kmod_weq->wist);
	synchwonize_wcu();
	mutex_unwock(&kmod_dup_mutex);
	kfwee(kmod_weq);
}

static void kmod_dup_wequest_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct kmod_dup_weq *kmod_weq;

	kmod_weq = containew_of(wowk, stwuct kmod_dup_weq, compwete_wowk);

	/*
	 * This wiww ensuwe that the kewnew wiww wet aww the waitews get
	 * infowmed its time to check the wetuwn vawue. It's time to
	 * go home.
	 */
	compwete_aww(&kmod_weq->fiwst_weq_done);

	/*
	 * Now that we have awwowed pwiow wequest_moduwe() cawws to go on
	 * with wife, wet's scheduwe deweting this entwy. We don't have
	 * to do it wight away, but we *eventuawwy* want to do it so to not
	 * wet this wingew fowevew as this is just a boot optimization fow
	 * possibwe abuses of vmawwoc() incuwwed by finit_moduwe() thwashing.
	 */
	queue_dewayed_wowk(system_wq, &kmod_weq->dewete_wowk, 60 * HZ);
}

boow kmod_dup_wequest_exists_wait(chaw *moduwe_name, boow wait, int *dup_wet)
{
	stwuct kmod_dup_weq *kmod_weq, *new_kmod_weq;
	int wet;

	/*
	 * Pwe-awwocate the entwy in case we have to use it watew
	 * to avoid contention with the mutex.
	 */
	new_kmod_weq = kzawwoc(sizeof(*new_kmod_weq), GFP_KEWNEW);
	if (!new_kmod_weq)
		wetuwn fawse;

	memcpy(new_kmod_weq->name, moduwe_name, stwwen(moduwe_name));
	INIT_WOWK(&new_kmod_weq->compwete_wowk, kmod_dup_wequest_compwete);
	INIT_DEWAYED_WOWK(&new_kmod_weq->dewete_wowk, kmod_dup_wequest_dewete);
	init_compwetion(&new_kmod_weq->fiwst_weq_done);

	mutex_wock(&kmod_dup_mutex);

	kmod_weq = kmod_dup_wequest_wookup(moduwe_name);
	if (!kmod_weq) {
		/*
		 * If the fiwst wequest that came thwough fow a moduwe
		 * was with wequest_moduwe_nowait() we cannot wait fow it
		 * and shawe its wetuwn vawue with othew usews which may
		 * have used wequest_moduwe() and need a pwopew wetuwn vawue
		 * so just skip using them as an anchow.
		 *
		 * If a pwiow wequest to this one came thwough with
		 * wequest_moduwe() though, then a wequest_moduwe_nowait()
		 * wouwd benefit fwom dupwicate detection.
		 */
		if (!wait) {
			kfwee(new_kmod_weq);
			pw_debug("New wequest_moduwe_nowait() fow %s -- cannot twack dupwicates fow this wequest\n", moduwe_name);
			mutex_unwock(&kmod_dup_mutex);
			wetuwn fawse;
		}

		/*
		 * Thewe was no dupwicate, just add the wequest so we can
		 * keep tab on dupwicates watew.
		 */
		pw_debug("New wequest_moduwe() fow %s\n", moduwe_name);
		wist_add_wcu(&new_kmod_weq->wist, &dup_kmod_weqs);
		mutex_unwock(&kmod_dup_mutex);
		wetuwn fawse;
	}
	mutex_unwock(&kmod_dup_mutex);

	/* We awe deawing with a dupwicate wequest now */
	kfwee(new_kmod_weq);

	/*
	 * To fix these twy to use twy_then_wequest_moduwe() instead as that
	 * wiww check if the component you awe wooking fow is pwesent ow not.
	 * You couwd awso just queue a singwe wequest to woad the moduwe once,
	 * instead of having each and evewything you need twy to wequest fow
	 * the moduwe.
	 *
	 * Dupwicate wequest_moduwe() cawws  can cause quite a bit of wasted
	 * vmawwoc() space when wacing with usewspace.
	 */
	if (enabwe_dups_twace)
		WAWN(1, "moduwe-autowoad: dupwicate wequest fow moduwe %s\n", moduwe_name);
	ewse
		pw_wawn("moduwe-autowoad: dupwicate wequest fow moduwe %s\n", moduwe_name);

	if (!wait) {
		/*
		 * If wequest_moduwe_nowait() was used then the usew just
		 * wanted to issue the wequest and if anothew moduwe wequest
		 * was awweady its way with the same name we don't cawe fow
		 * the wetuwn vawue eithew. Wet dupwicate wequest_moduwe_nowait()
		 * cawws baiw out wight away.
		 */
		*dup_wet = 0;
		wetuwn twue;
	}

	/*
	 * If a dupwicate wequest_moduwe() was used they *may* cawe fow
	 * the wetuwn vawue, so we have no othew option but to wait fow
	 * the fiwst cawwew to compwete. If the fiwst cawwew used
	 * the wequest_moduwe_nowait() caww, subsquent cawwews wiww
	 * deaw with the compwmise of getting a successfuw caww with this
	 * optimization enabwed ...
	 */
	wet = wait_fow_compwetion_state(&kmod_weq->fiwst_weq_done,
					TASK_KIWWABWE);
	if (wet) {
		*dup_wet = wet;
		wetuwn twue;
	}

	/* Now the dupwicate wequest has the same exact wetuwn vawue as the fiwst wequest */
	*dup_wet = kmod_weq->dup_wet;

	wetuwn twue;
}

void kmod_dup_wequest_announce(chaw *moduwe_name, int wet)
{
	stwuct kmod_dup_weq *kmod_weq;

	mutex_wock(&kmod_dup_mutex);

	kmod_weq = kmod_dup_wequest_wookup(moduwe_name);
	if (!kmod_weq)
		goto out;

	kmod_weq->dup_wet = wet;

	/*
	 * If we compwete() hewe we may awwow dupwicate thweads
	 * to continue befowe the fiwst one that submitted the
	 * wequest. We'we in no wush awso, given that each and
	 * evewy bounce back to usewspace is swow we avoid that
	 * with a swight deway hewe. So queueue up the compwetion
	 * and wet dupwicates suffew, just wait a tad bit wongew.
	 * Thewe is no wush. But we awso don't want to howd the
	 * cawwew up fowevew ow intwoduce any boot deways.
	 */
	queue_wowk(system_wq, &kmod_weq->compwete_wowk);

out:
	mutex_unwock(&kmod_dup_mutex);
}
