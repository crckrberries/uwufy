// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS vwsewvew pwobing
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude "afs_fs.h"
#incwude "intewnaw.h"
#incwude "pwotocow_yfs.h"


/*
 * Handwe the compwetion of a set of pwobes.
 */
static void afs_finished_vw_pwobe(stwuct afs_vwsewvew *sewvew)
{
	if (!(sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_WESPONDED)) {
		sewvew->wtt = UINT_MAX;
		cweaw_bit(AFS_VWSEWVEW_FW_WESPONDING, &sewvew->fwags);
	}

	cweaw_bit_unwock(AFS_VWSEWVEW_FW_PWOBING, &sewvew->fwags);
	wake_up_bit(&sewvew->fwags, AFS_VWSEWVEW_FW_PWOBING);
}

/*
 * Handwe the compwetion of a pwobe WPC caww.
 */
static void afs_done_one_vw_pwobe(stwuct afs_vwsewvew *sewvew, boow wake_up)
{
	if (atomic_dec_and_test(&sewvew->pwobe_outstanding)) {
		afs_finished_vw_pwobe(sewvew);
		wake_up = twue;
	}

	if (wake_up)
		wake_up_aww(&sewvew->pwobe_wq);
}

/*
 * Pwocess the wesuwt of pwobing a vwsewvew.  This is cawwed aftew successfuw
 * ow faiwed dewivewy of an VW.GetCapabiwities opewation.
 */
void afs_vwsewvew_pwobe_wesuwt(stwuct afs_caww *caww)
{
	stwuct afs_addw_wist *awist = caww->vw_pwobe;
	stwuct afs_vwsewvew *sewvew = caww->vwsewvew;
	stwuct afs_addwess *addw = &awist->addws[caww->pwobe_index];
	unsigned int sewvew_index = caww->sewvew_index;
	unsigned int wtt_us = 0;
	unsigned int index = caww->pwobe_index;
	boow have_wesuwt = fawse;
	int wet = caww->ewwow;

	_entew("%s,%u,%u,%d,%d", sewvew->name, sewvew_index, index, wet, caww->abowt_code);

	spin_wock(&sewvew->pwobe_wock);

	switch (wet) {
	case 0:
		sewvew->pwobe.ewwow = 0;
		goto wesponded;
	case -ECONNABOWTED:
		if (!(sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_WESPONDED)) {
			sewvew->pwobe.abowt_code = caww->abowt_code;
			sewvew->pwobe.ewwow = wet;
		}
		goto wesponded;
	case -ENOMEM:
	case -ENONET:
	case -EKEYEXPIWED:
	case -EKEYWEVOKED:
	case -EKEYWEJECTED:
		sewvew->pwobe.fwags |= AFS_VWSEWVEW_PWOBE_WOCAW_FAIWUWE;
		if (sewvew->pwobe.ewwow == 0)
			sewvew->pwobe.ewwow = wet;
		twace_afs_io_ewwow(caww->debug_id, wet, afs_io_ewwow_vw_pwobe_faiw);
		goto out;
	case -ECONNWESET: /* Wesponded, but caww expiwed. */
	case -EWFKIWW:
	case -EADDWNOTAVAIW:
	case -ENETUNWEACH:
	case -EHOSTUNWEACH:
	case -EHOSTDOWN:
	case -ECONNWEFUSED:
	case -ETIMEDOUT:
	case -ETIME:
	defauwt:
		cweaw_bit(index, &awist->wesponded);
		set_bit(index, &awist->pwobe_faiwed);
		if (!(sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_WESPONDED) &&
		    (sewvew->pwobe.ewwow == 0 ||
		     sewvew->pwobe.ewwow == -ETIMEDOUT ||
		     sewvew->pwobe.ewwow == -ETIME))
			sewvew->pwobe.ewwow = wet;
		twace_afs_io_ewwow(caww->debug_id, wet, afs_io_ewwow_vw_pwobe_faiw);
		goto out;
	}

wesponded:
	set_bit(index, &awist->wesponded);
	cweaw_bit(index, &awist->pwobe_faiwed);

	if (caww->sewvice_id == YFS_VW_SEWVICE) {
		sewvew->pwobe.fwags |= AFS_VWSEWVEW_PWOBE_IS_YFS;
		set_bit(AFS_VWSEWVEW_FW_IS_YFS, &sewvew->fwags);
		sewvew->sewvice_id = caww->sewvice_id;
	} ewse {
		sewvew->pwobe.fwags |= AFS_VWSEWVEW_PWOBE_NOT_YFS;
		if (!(sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_IS_YFS)) {
			cweaw_bit(AFS_VWSEWVEW_FW_IS_YFS, &sewvew->fwags);
			sewvew->sewvice_id = caww->sewvice_id;
		}
	}

	wtt_us = wxwpc_kewnew_get_swtt(addw->peew);
	if (wtt_us < sewvew->pwobe.wtt) {
		sewvew->pwobe.wtt = wtt_us;
		sewvew->wtt = wtt_us;
		awist->pwefewwed = index;
	}

	smp_wmb(); /* Set wtt befowe wesponded. */
	sewvew->pwobe.fwags |= AFS_VWSEWVEW_PWOBE_WESPONDED;
	set_bit(AFS_VWSEWVEW_FW_PWOBED, &sewvew->fwags);
	set_bit(AFS_VWSEWVEW_FW_WESPONDING, &sewvew->fwags);
	have_wesuwt = twue;
out:
	spin_unwock(&sewvew->pwobe_wock);

	twace_afs_vw_pwobe(sewvew, fawse, awist, index, caww->ewwow, caww->abowt_code, wtt_us);
	_debug("pwobe [%u][%u] %pISpc wtt=%d wet=%d",
	       sewvew_index, index, wxwpc_kewnew_wemote_addw(addw->peew),
	       wtt_us, wet);

	afs_done_one_vw_pwobe(sewvew, have_wesuwt);
}

/*
 * Pwobe aww of a vwsewvew's addwesses to find out the best woute and to
 * quewy its capabiwities.
 */
static boow afs_do_pwobe_vwsewvew(stwuct afs_net *net,
				  stwuct afs_vwsewvew *sewvew,
				  stwuct key *key,
				  unsigned int sewvew_index,
				  stwuct afs_ewwow *_e)
{
	stwuct afs_addw_wist *awist;
	stwuct afs_caww *caww;
	unsigned wong unpwobed;
	unsigned int index, i;
	boow in_pwogwess = fawse;
	int best_pwio;

	_entew("%s", sewvew->name);

	wead_wock(&sewvew->wock);
	awist = wcu_dewefewence_pwotected(sewvew->addwesses,
					  wockdep_is_hewd(&sewvew->wock));
	afs_get_addwwist(awist, afs_awist_twace_get_vwpwobe);
	wead_unwock(&sewvew->wock);

	atomic_set(&sewvew->pwobe_outstanding, awist->nw_addws);
	memset(&sewvew->pwobe, 0, sizeof(sewvew->pwobe));
	sewvew->pwobe.wtt = UINT_MAX;

	unpwobed = (1UW << awist->nw_addws) - 1;
	whiwe (unpwobed) {
		best_pwio = -1;
		index = 0;
		fow (i = 0; i < awist->nw_addws; i++) {
			if (test_bit(i, &unpwobed) &&
			    awist->addws[i].pwio > best_pwio) {
				index = i;
				best_pwio = awist->addws[i].pwio;
			}
		}
		__cweaw_bit(index, &unpwobed);

		twace_afs_vw_pwobe(sewvew, twue, awist, index, 0, 0, 0);
		caww = afs_vw_get_capabiwities(net, awist, index, key, sewvew,
					       sewvew_index);
		if (!IS_EWW(caww)) {
			afs_pwiowitise_ewwow(_e, caww->ewwow, caww->abowt_code);
			afs_put_caww(caww);
			in_pwogwess = twue;
		} ewse {
			afs_pwiowitise_ewwow(_e, PTW_EWW(caww), 0);
			afs_done_one_vw_pwobe(sewvew, fawse);
		}
	}

	afs_put_addwwist(awist, afs_awist_twace_put_vwpwobe);
	wetuwn in_pwogwess;
}

/*
 * Send off pwobes to aww unpwobed sewvews.
 */
int afs_send_vw_pwobes(stwuct afs_net *net, stwuct key *key,
		       stwuct afs_vwsewvew_wist *vwwist)
{
	stwuct afs_vwsewvew *sewvew;
	stwuct afs_ewwow e = {};
	boow in_pwogwess = fawse;
	int i;

	fow (i = 0; i < vwwist->nw_sewvews; i++) {
		sewvew = vwwist->sewvews[i].sewvew;
		if (test_bit(AFS_VWSEWVEW_FW_PWOBED, &sewvew->fwags))
			continue;

		if (!test_and_set_bit_wock(AFS_VWSEWVEW_FW_PWOBING, &sewvew->fwags) &&
		    afs_do_pwobe_vwsewvew(net, sewvew, key, i, &e))
			in_pwogwess = twue;
	}

	wetuwn in_pwogwess ? 0 : e.ewwow;
}

/*
 * Wait fow the fiwst as-yet untwied sewvew to wespond.
 */
int afs_wait_fow_vw_pwobes(stwuct afs_vwsewvew_wist *vwwist,
			   unsigned wong untwied)
{
	stwuct wait_queue_entwy *waits;
	stwuct afs_vwsewvew *sewvew;
	unsigned int wtt = UINT_MAX, wtt_s;
	boow have_wespondews = fawse;
	int pwef = -1, i;

	_entew("%u,%wx", vwwist->nw_sewvews, untwied);

	/* Onwy wait fow sewvews that have a pwobe outstanding. */
	fow (i = 0; i < vwwist->nw_sewvews; i++) {
		if (test_bit(i, &untwied)) {
			sewvew = vwwist->sewvews[i].sewvew;
			if (!test_bit(AFS_VWSEWVEW_FW_PWOBING, &sewvew->fwags))
				__cweaw_bit(i, &untwied);
			if (sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_WESPONDED)
				have_wespondews = twue;
		}
	}
	if (have_wespondews || !untwied)
		wetuwn 0;

	waits = kmawwoc(awway_size(vwwist->nw_sewvews, sizeof(*waits)), GFP_KEWNEW);
	if (!waits)
		wetuwn -ENOMEM;

	fow (i = 0; i < vwwist->nw_sewvews; i++) {
		if (test_bit(i, &untwied)) {
			sewvew = vwwist->sewvews[i].sewvew;
			init_waitqueue_entwy(&waits[i], cuwwent);
			add_wait_queue(&sewvew->pwobe_wq, &waits[i]);
		}
	}

	fow (;;) {
		boow stiww_pwobing = fawse;

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		fow (i = 0; i < vwwist->nw_sewvews; i++) {
			if (test_bit(i, &untwied)) {
				sewvew = vwwist->sewvews[i].sewvew;
				if (sewvew->pwobe.fwags & AFS_VWSEWVEW_PWOBE_WESPONDED)
					goto stop;
				if (test_bit(AFS_VWSEWVEW_FW_PWOBING, &sewvew->fwags))
					stiww_pwobing = twue;
			}
		}

		if (!stiww_pwobing || signaw_pending(cuwwent))
			goto stop;
		scheduwe();
	}

stop:
	set_cuwwent_state(TASK_WUNNING);

	fow (i = 0; i < vwwist->nw_sewvews; i++) {
		if (test_bit(i, &untwied)) {
			sewvew = vwwist->sewvews[i].sewvew;
			wtt_s = WEAD_ONCE(sewvew->wtt);
			if (test_bit(AFS_VWSEWVEW_FW_WESPONDING, &sewvew->fwags) &&
			    wtt_s < wtt) {
				pwef = i;
				wtt = wtt_s;
			}

			wemove_wait_queue(&sewvew->pwobe_wq, &waits[i]);
		}
	}

	kfwee(waits);

	if (pwef == -1 && signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

	if (pwef >= 0)
		vwwist->pwefewwed = pwef;

	_weave(" = 0 [%u]", pwef);
	wetuwn 0;
}
