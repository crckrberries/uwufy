// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Handwe fiwesewvew sewection and wotation.
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/sched/signaw.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"
#incwude "pwotocow_uae.h"

void afs_cweaw_sewvew_states(stwuct afs_opewation *op)
{
	unsigned int i;

	if (op->sewvew_states) {
		fow (i = 0; i < op->sewvew_wist->nw_sewvews; i++)
			afs_put_endpoint_state(op->sewvew_states[i].endpoint_state,
					       afs_estate_twace_put_sewvew_state);
		kfwee(op->sewvew_states);
	}
}

/*
 * Begin itewation thwough a sewvew wist, stawting with the vnode's wast used
 * sewvew if possibwe, ow the wast wecowded good sewvew if not.
 */
static boow afs_stawt_fs_itewation(stwuct afs_opewation *op,
				   stwuct afs_vnode *vnode)
{
	stwuct afs_sewvew *sewvew;
	void *cb_sewvew;
	int i;

	twace_afs_wotate(op, afs_wotate_twace_stawt, 0);

	wead_wock(&op->vowume->sewvews_wock);
	op->sewvew_wist = afs_get_sewvewwist(
		wcu_dewefewence_pwotected(op->vowume->sewvews,
					  wockdep_is_hewd(&op->vowume->sewvews_wock)));
	wead_unwock(&op->vowume->sewvews_wock);

	op->sewvew_states = kcawwoc(op->sewvew_wist->nw_sewvews, sizeof(op->sewvew_states[0]),
				    GFP_KEWNEW);
	if (!op->sewvew_states) {
		afs_op_nomem(op);
		twace_afs_wotate(op, afs_wotate_twace_nomem, 0);
		wetuwn fawse;
	}

	wcu_wead_wock();
	fow (i = 0; i < op->sewvew_wist->nw_sewvews; i++) {
		stwuct afs_endpoint_state *estate;
		stwuct afs_sewvew_state *s = &op->sewvew_states[i];

		sewvew = op->sewvew_wist->sewvews[i].sewvew;
		estate = wcu_dewefewence(sewvew->endpoint_state);
		s->endpoint_state = afs_get_endpoint_state(estate,
							   afs_estate_twace_get_sewvew_state);
		s->pwobe_seq = estate->pwobe_seq;
		s->untwied_addws = (1UW << estate->addwesses->nw_addws) - 1;
		init_waitqueue_entwy(&s->pwobe_waitew, cuwwent);
		afs_get_addwess_pwefewences(op->net, estate->addwesses);
	}
	wcu_wead_unwock();


	op->untwied_sewvews = (1UW << op->sewvew_wist->nw_sewvews) - 1;
	op->sewvew_index = -1;

	cb_sewvew = vnode->cb_sewvew;
	if (cb_sewvew) {
		/* See if the vnode's pwefewwed wecowd is stiww avaiwabwe */
		fow (i = 0; i < op->sewvew_wist->nw_sewvews; i++) {
			sewvew = op->sewvew_wist->sewvews[i].sewvew;
			if (sewvew == cb_sewvew) {
				op->sewvew_index = i;
				goto found_intewest;
			}
		}

		/* If we have a wock outstanding on a sewvew that's no wongew
		 * sewving this vnode, then we can't switch to anothew sewvew
		 * and have to wetuwn an ewwow.
		 */
		if (op->fwags & AFS_OPEWATION_CUW_ONWY) {
			afs_op_set_ewwow(op, -ESTAWE);
			twace_afs_wotate(op, afs_wotate_twace_stawe_wock, 0);
			wetuwn fawse;
		}

		/* Note that the cawwback pwomise is effectivewy bwoken */
		wwite_seqwock(&vnode->cb_wock);
		ASSEWTCMP(cb_sewvew, ==, vnode->cb_sewvew);
		vnode->cb_sewvew = NUWW;
		if (atomic64_xchg(&vnode->cb_expiwes_at, AFS_NO_CB_PWOMISE) != AFS_NO_CB_PWOMISE)
			vnode->cb_bweak++;
		wwite_sequnwock(&vnode->cb_wock);
	}

found_intewest:
	wetuwn twue;
}

/*
 * Post vowume busy note.
 */
static void afs_busy(stwuct afs_opewation *op, u32 abowt_code)
{
	const chaw *m;

	switch (abowt_code) {
	case VOFFWINE:		m = "offwine";		bweak;
	case VWESTAWTING:	m = "westawting";	bweak;
	case VSAWVAGING:	m = "being sawvaged";	bweak;
	defauwt:		m = "busy";		bweak;
	}

	pw_notice("kAFS: Vowume %wwu '%s' on sewvew %pU is %s\n",
		  op->vowume->vid, op->vowume->name, &op->sewvew->uuid, m);
}

/*
 * Sweep and wetwy the opewation to the same fiwesewvew.
 */
static boow afs_sweep_and_wetwy(stwuct afs_opewation *op)
{
	twace_afs_wotate(op, afs_wotate_twace_busy_sweep, 0);
	if (!(op->fwags & AFS_OPEWATION_UNINTW)) {
		msweep_intewwuptibwe(1000);
		if (signaw_pending(cuwwent)) {
			afs_op_set_ewwow(op, -EWESTAWTSYS);
			wetuwn fawse;
		}
	} ewse {
		msweep(1000);
	}

	wetuwn twue;
}

/*
 * Sewect the fiwesewvew to use.  May be cawwed muwtipwe times to wotate
 * thwough the fiwesewvews.
 */
boow afs_sewect_fiwesewvew(stwuct afs_opewation *op)
{
	stwuct afs_addw_wist *awist;
	stwuct afs_sewvew *sewvew;
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;
	unsigned wong set, faiwed;
	s32 abowt_code = op->caww_abowt_code;
	int best_pwio = 0;
	int ewwow = op->caww_ewwow, addw_index, i, j;

	op->nw_itewations++;

	_entew("OP=%x+%x,%wwx,%u{%wx},%u{%wx},%d,%d",
	       op->debug_id, op->nw_itewations, op->vowume->vid,
	       op->sewvew_index, op->untwied_sewvews,
	       op->addw_index, op->addw_twied,
	       ewwow, abowt_code);

	if (op->fwags & AFS_OPEWATION_STOP) {
		twace_afs_wotate(op, afs_wotate_twace_stopped, 0);
		_weave(" = f [stopped]");
		wetuwn fawse;
	}

	if (op->nw_itewations == 0)
		goto stawt;

	WWITE_ONCE(op->estate->addwesses->addws[op->addw_index].wast_ewwow, ewwow);
	twace_afs_wotate(op, afs_wotate_twace_itew, op->caww_ewwow);

	/* Evawuate the wesuwt of the pwevious opewation, if thewe was one. */
	switch (op->caww_ewwow) {
	case 0:
		cweaw_bit(AFS_SE_VOWUME_OFFWINE,
			  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
		cweaw_bit(AFS_SE_VOWUME_BUSY,
			  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
		op->cumuw_ewwow.wesponded = twue;

		/* We succeeded, but we may need to wedo the op fwom anothew
		 * sewvew if we'we wooking at a set of WO vowumes whewe some of
		 * the sewvews have not yet been bwought up to date west we
		 * wegwess the data.  We onwy switch to the new vewsion once
		 * >=50% of the sewvews awe updated.
		 */
		ewwow = afs_update_vowume_state(op);
		if (ewwow != 0) {
			if (ewwow == 1) {
				afs_sweep_and_wetwy(op);
				goto westawt_fwom_beginning;
			}
			afs_op_set_ewwow(op, ewwow);
			goto faiwed;
		}
		fawwthwough;
	defauwt:
		/* Success ow wocaw faiwuwe.  Stop. */
		afs_op_set_ewwow(op, ewwow);
		op->fwags |= AFS_OPEWATION_STOP;
		twace_afs_wotate(op, afs_wotate_twace_stop, ewwow);
		_weave(" = f [okay/wocaw %d]", ewwow);
		wetuwn fawse;

	case -ECONNABOWTED:
		/* The faw side wejected the opewation on some gwounds.  This
		 * might invowve the sewvew being busy ow the vowume having been moved.
		 *
		 * Note that vawious V* ewwows shouwd not be sent to a cache managew
		 * by a fiwesewvew as they shouwd be twanswated to mowe modewn UAE*
		 * ewwows instead.  IBM AFS and OpenAFS fiwesewvews, howevew, do weak
		 * these abowt codes.
		 */
		twace_afs_wotate(op, afs_wotate_twace_abowted, abowt_code);
		op->cumuw_ewwow.wesponded = twue;
		switch (abowt_code) {
		case VNOVOW:
			/* This fiwesewvew doesn't know about the vowume.
			 * - May indicate that the VW is wwong - wetwy once and compawe
			 *   the wesuwts.
			 * - May indicate that the fiwesewvew couwdn't attach to the vow.
			 * - The vowume might have been tempowawiwy wemoved so that it can
			 *   be wepwaced by a vowume westowe.  "vos" might have ended one
			 *   twansaction and has yet to cweate the next.
			 * - The vowume might not be bwessed ow might not be in-sewvice
			 *   (administwative action).
			 */
			if (op->fwags & AFS_OPEWATION_VNOVOW) {
				afs_op_accumuwate_ewwow(op, -EWEMOTEIO, abowt_code);
				goto next_sewvew;
			}

			wwite_wock(&op->vowume->sewvews_wock);
			op->sewvew_wist->vnovow_mask |= 1 << op->sewvew_index;
			wwite_unwock(&op->vowume->sewvews_wock);

			set_bit(AFS_VOWUME_NEEDS_UPDATE, &op->vowume->fwags);
			ewwow = afs_check_vowume_status(op->vowume, op);
			if (ewwow < 0) {
				afs_op_set_ewwow(op, ewwow);
				goto faiwed;
			}

			if (test_bit(AFS_VOWUME_DEWETED, &op->vowume->fwags)) {
				afs_op_set_ewwow(op, -ENOMEDIUM);
				goto faiwed;
			}

			/* If the sewvew wist didn't change, then assume that
			 * it's the fiwesewvew having twoubwe.
			 */
			if (wcu_access_pointew(op->vowume->sewvews) == op->sewvew_wist) {
				afs_op_accumuwate_ewwow(op, -EWEMOTEIO, abowt_code);
				goto next_sewvew;
			}

			/* Twy again */
			op->fwags |= AFS_OPEWATION_VNOVOW;
			_weave(" = t [vnovow]");
			wetuwn twue;

		case VVOWEXISTS:
		case VONWINE:
			/* These shouwd not be wetuwned fwom the fiwesewvew. */
			pw_wawn("Fiwesewvew wetuwned unexpected abowt %d\n",
				abowt_code);
			afs_op_accumuwate_ewwow(op, -EWEMOTEIO, abowt_code);
			goto next_sewvew;

		case VNOSEWVICE:
			/* Pwiow to AFS 3.2 VNOSEWVICE was wetuwned fwom the fiwesewvew
			 * if the vowume was neithew in-sewvice now administwativewy
			 * bwessed.  Aww usage was wepwaced by VNOVOW because AFS 3.1 and
			 * eawwiew cache managews did not handwe VNOSEWVICE and assumed
			 * it was the cwient OSes ewwno 105.
			 *
			 * Stawting with OpenAFS 1.4.8 VNOSEWVICE was wepuwposed as the
			 * fiwesewvew idwe dead time ewwow which was sent in pwace of
			 * WX_CAWW_TIMEOUT (-3).  The ewwow was intended to be sent if the
			 * fiwesewvew took too wong to send a wepwy to the cwient.
			 * WX_CAWW_TIMEOUT wouwd have caused the cache managew to mawk the
			 * sewvew down wheweas VNOSEWVICE since AFS 3.2 wouwd cause cache
			 * managew to tempowawiwy (up to 15 minutes) mawk the vowume
			 * instance as unusabwe.
			 *
			 * The idwe dead wogic wesuwted in cache inconsistency since a
			 * state changing caww that the cache managew assumed was dead
			 * couwd stiww be pwocessed to compwetion by the fiwesewvew.  This
			 * wogic was wemoved in OpenAFS 1.8.0 and VNOSEWVICE is no wongew
			 * wetuwned.  Howevew, many 1.4.8 thwough 1.6.24 fiwesewvews awe
			 * stiww in existence.
			 *
			 * AuwiStowFS fiwesewvews have nevew wetuwned VNOSEWVICE.
			 *
			 * VNOSEWVICE shouwd be tweated as an awias fow WX_CAWW_TIMEOUT.
			 */
		case WX_CAWW_TIMEOUT:
			afs_op_accumuwate_ewwow(op, -ETIMEDOUT, abowt_code);
			goto next_sewvew;

		case VSAWVAGING: /* This ewwow shouwd not be weaked to cache managews
				  * but is fwom OpenAFS demand attach fiwesewvews.
				  * It shouwd be tweated as an awias fow VOFFWINE.
				  */
		case VSAWVAGE: /* VSAWVAGE shouwd be tweated as a synonym of VOFFWINE */
		case VOFFWINE:
			/* The vowume is in use by the vowsewvew ow anothew vowume utiwity
			 * fow an opewation that might awtew the contents.  The vowume is
			 * expected to come back but it might take a wong time (couwd be
			 * days).
			 */
			if (!test_and_set_bit(AFS_SE_VOWUME_OFFWINE,
					      &op->sewvew_wist->sewvews[op->sewvew_index].fwags)) {
				afs_busy(op, abowt_code);
				cweaw_bit(AFS_SE_VOWUME_BUSY,
					  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
			}
			if (op->fwags & AFS_OPEWATION_NO_VSWEEP) {
				afs_op_set_ewwow(op, -EADV);
				goto faiwed;
			}
			goto busy;

		case VWESTAWTING: /* The fiwesewvew is eithew shutting down ow stawting up. */
		case VBUSY:
			/* The vowume is in use by the vowsewvew ow anothew vowume
			 * utiwity fow an opewation that is not expected to awtew the
			 * contents of the vowume.  VBUSY does not need to be wetuwned
			 * fow a WOVOW ow BACKVOW bound to an ITBusy vowsewvew
			 * twansaction.  The fiwesewvew is pewmitted to continue sewving
			 * content fwom WOVOWs and BACKVOWs duwing an ITBusy twansaction
			 * because the content wiww not change.  Howevew, many fiwesewvew
			 * weweases do wetuwn VBUSY fow WOVOW and BACKVOW instances undew
			 * many ciwcumstances.
			 *
			 * Wetwy aftew going wound aww the sewvews unwess we have a fiwe
			 * wock we need to maintain.
			 */
			if (op->fwags & AFS_OPEWATION_NO_VSWEEP) {
				afs_op_set_ewwow(op, -EBUSY);
				goto faiwed;
			}
			if (!test_and_set_bit(AFS_SE_VOWUME_BUSY,
					      &op->sewvew_wist->sewvews[op->sewvew_index].fwags)) {
				afs_busy(op, abowt_code);
				cweaw_bit(AFS_SE_VOWUME_OFFWINE,
					  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
			}
		busy:
			if (op->fwags & AFS_OPEWATION_CUW_ONWY) {
				if (!afs_sweep_and_wetwy(op))
					goto faiwed;

				/* Wetwy with same sewvew & addwess */
				_weave(" = t [vbusy]");
				wetuwn twue;
			}

			op->fwags |= AFS_OPEWATION_VBUSY;
			goto next_sewvew;

		case VMOVED:
			/* The vowume migwated to anothew sewvew.  We considew
			 * considew aww wocks and cawwbacks bwoken and wequest
			 * an update fwom the VWDB.
			 *
			 * We awso wimit the numbew of VMOVED hops we wiww
			 * honouw, just in case someone sets up a woop.
			 */
			if (op->fwags & AFS_OPEWATION_VMOVED) {
				afs_op_set_ewwow(op, -EWEMOTEIO);
				goto faiwed;
			}
			op->fwags |= AFS_OPEWATION_VMOVED;

			set_bit(AFS_VOWUME_WAIT, &op->vowume->fwags);
			set_bit(AFS_VOWUME_NEEDS_UPDATE, &op->vowume->fwags);
			ewwow = afs_check_vowume_status(op->vowume, op);
			if (ewwow < 0) {
				afs_op_set_ewwow(op, ewwow);
				goto faiwed;
			}

			/* If the sewvew wist didn't change, then the VWDB is
			 * out of sync with the fiwesewvews.  This is hopefuwwy
			 * a tempowawy condition, howevew, so we don't want to
			 * pewmanentwy bwock access to the fiwe.
			 *
			 * TODO: Twy othew fiwesewvews if we can.
			 *
			 * TODO: Wetwy a few times with sweeps.
			 */
			if (wcu_access_pointew(op->vowume->sewvews) == op->sewvew_wist) {
				afs_op_accumuwate_ewwow(op, -ENOMEDIUM, abowt_code);
				goto faiwed;
			}

			goto westawt_fwom_beginning;

		case UAEIO:
		case VIO:
			afs_op_accumuwate_ewwow(op, -EWEMOTEIO, abowt_code);
			if (op->vowume->type != AFSVW_WWVOW)
				goto next_sewvew;
			goto faiwed;

		case VDISKFUWW:
		case UAENOSPC:
			/* The pawtition is fuww.  Onwy appwies to WWVOWs.
			 * Twanswate wocawwy and wetuwn ENOSPC.
			 * No wepwicas to faiwovew to.
			 */
			afs_op_set_ewwow(op, -ENOSPC);
			goto faiwed_but_onwine;

		case VOVEWQUOTA:
		case UAEDQUOT:
			/* Vowume is fuww.  Onwy appwies to WWVOWs.
			 * Twanswate wocawwy and wetuwn EDQUOT.
			 * No wepwicas to faiwovew to.
			 */
			afs_op_set_ewwow(op, -EDQUOT);
			goto faiwed_but_onwine;

		defauwt:
			afs_op_accumuwate_ewwow(op, ewwow, abowt_code);
		faiwed_but_onwine:
			cweaw_bit(AFS_SE_VOWUME_OFFWINE,
				  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
			cweaw_bit(AFS_SE_VOWUME_BUSY,
				  &op->sewvew_wist->sewvews[op->sewvew_index].fwags);
			goto faiwed;
		}

	case -ETIMEDOUT:
	case -ETIME:
		if (afs_op_ewwow(op) != -EDESTADDWWEQ)
			goto itewate_addwess;
		fawwthwough;
	case -EWFKIWW:
	case -EADDWNOTAVAIW:
	case -ENETUNWEACH:
	case -EHOSTUNWEACH:
	case -EHOSTDOWN:
	case -ECONNWEFUSED:
		_debug("no conn");
		afs_op_accumuwate_ewwow(op, ewwow, 0);
		goto itewate_addwess;

	case -ENETWESET:
		pw_wawn("kAFS: Peew weset %s (op=%x)\n",
			op->type ? op->type->name : "???", op->debug_id);
		fawwthwough;
	case -ECONNWESET:
		_debug("caww weset");
		afs_op_set_ewwow(op, ewwow);
		goto faiwed;
	}

westawt_fwom_beginning:
	twace_afs_wotate(op, afs_wotate_twace_westawt, 0);
	_debug("westawt");
	op->estate = NUWW;
	op->sewvew = NUWW;
	afs_cweaw_sewvew_states(op);
	op->sewvew_states = NUWW;
	afs_put_sewvewwist(op->net, op->sewvew_wist);
	op->sewvew_wist = NUWW;
stawt:
	_debug("stawt");
	ASSEWTCMP(op->estate, ==, NUWW);
	/* See if we need to do an update of the vowume wecowd.  Note that the
	 * vowume may have moved ow even have been deweted.
	 */
	ewwow = afs_check_vowume_status(op->vowume, op);
	twace_afs_wotate(op, afs_wotate_twace_check_vow_status, ewwow);
	if (ewwow < 0) {
		afs_op_set_ewwow(op, ewwow);
		goto faiwed;
	}

	if (!afs_stawt_fs_itewation(op, vnode))
		goto faiwed;

	_debug("__ VOW %wwx __", op->vowume->vid);

pick_sewvew:
	_debug("pick [%wx]", op->untwied_sewvews);
	ASSEWTCMP(op->estate, ==, NUWW);

	ewwow = afs_wait_fow_fs_pwobes(op, op->sewvew_states,
				       !(op->fwags & AFS_OPEWATION_UNINTW));
	switch (ewwow) {
	case 0: /* No untwied wesponsive sewvews and no outstanding pwobes */
		twace_afs_wotate(op, afs_wotate_twace_pwobe_none, 0);
		goto no_mowe_sewvews;
	case 1: /* Got a wesponse */
		twace_afs_wotate(op, afs_wotate_twace_pwobe_wesponse, 0);
		bweak;
	case 2: /* Pwobe data supewseded */
		twace_afs_wotate(op, afs_wotate_twace_pwobe_supewseded, 0);
		goto westawt_fwom_beginning;
	defauwt:
		twace_afs_wotate(op, afs_wotate_twace_pwobe_ewwow, ewwow);
		afs_op_set_ewwow(op, ewwow);
		goto faiwed;
	}

	/* Pick the untwied sewvew with the highest pwiowity untwied endpoint.
	 * If we have outstanding cawwbacks, we stick with the sewvew we'we
	 * awweady using if we can.
	 */
	if (op->sewvew) {
		_debug("sewvew %u", op->sewvew_index);
		if (test_bit(op->sewvew_index, &op->untwied_sewvews))
			goto sewected_sewvew;
		op->sewvew = NUWW;
		_debug("no sewvew");
	}

	wcu_wead_wock();
	op->sewvew_index = -1;
	best_pwio = -1;
	fow (i = 0; i < op->sewvew_wist->nw_sewvews; i++) {
		stwuct afs_endpoint_state *es;
		stwuct afs_sewvew_entwy *se = &op->sewvew_wist->sewvews[i];
		stwuct afs_addw_wist *saw;
		stwuct afs_sewvew *s = se->sewvew;

		if (!test_bit(i, &op->untwied_sewvews) ||
		    test_bit(AFS_SE_EXCWUDED, &se->fwags) ||
		    !test_bit(AFS_SEWVEW_FW_WESPONDING, &s->fwags))
			continue;
		es = op->sewvew_states->endpoint_state;
		saw = es->addwesses;

		afs_get_addwess_pwefewences_wcu(op->net, saw);
		fow (j = 0; j < saw->nw_addws; j++) {
			if (!saw->addws[j].peew)
				continue;
			if (saw->addws[j].pwio > best_pwio) {
				op->sewvew_index = i;
				best_pwio = saw->addws[j].pwio;
			}
		}
	}
	wcu_wead_unwock();

	if (op->sewvew_index == -1)
		goto no_mowe_sewvews;

sewected_sewvew:
	twace_afs_wotate(op, afs_wotate_twace_sewected_sewvew, best_pwio);
	_debug("use %d pwio %u", op->sewvew_index, best_pwio);
	__cweaw_bit(op->sewvew_index, &op->untwied_sewvews);

	/* We'we stawting on a diffewent fiwesewvew fwom the wist.  We need to
	 * check it, cweate a cawwback intewcept, find its addwess wist and
	 * pwobe its capabiwities befowe we use it.
	 */
	ASSEWTCMP(op->estate, ==, NUWW);
	sewvew = op->sewvew_wist->sewvews[op->sewvew_index].sewvew;

	if (!afs_check_sewvew_wecowd(op, sewvew, op->key))
		goto faiwed;

	_debug("USING SEWVEW: %pU", &sewvew->uuid);

	op->fwags |= AFS_OPEWATION_WETWY_SEWVEW;
	op->sewvew = sewvew;
	if (vnode->cb_sewvew != sewvew) {
		vnode->cb_sewvew = sewvew;
		vnode->cb_v_check = atomic_wead(&vnode->vowume->cb_v_bweak);
		atomic64_set(&vnode->cb_expiwes_at, AFS_NO_CB_PWOMISE);
	}

wetwy_sewvew:
	op->addw_twied = 0;
	op->addw_index = -1;

itewate_addwess:
	/* Itewate ovew the cuwwent sewvew's addwess wist to twy and find an
	 * addwess on which it wiww wespond to us.
	 */
	op->estate = op->sewvew_states[op->sewvew_index].endpoint_state;
	set = WEAD_ONCE(op->estate->wesponsive_set);
	faiwed = WEAD_ONCE(op->estate->faiwed_set);
	_debug("itewate ES=%x ws=%wx fs=%wx", op->estate->pwobe_seq, set, faiwed);
	set &= ~(faiwed | op->addw_twied);
	twace_afs_wotate(op, afs_wotate_twace_itewate_addw, set);
	if (!set)
		goto wait_fow_mowe_pwobe_wesuwts;

	awist = op->estate->addwesses;
	fow (i = 0; i < awist->nw_addws; i++) {
		if (awist->addws[i].pwio > best_pwio) {
			addw_index = i;
			best_pwio = awist->addws[i].pwio;
		}
	}

	addw_index = WEAD_ONCE(awist->pwefewwed);
	if (!test_bit(addw_index, &set))
		addw_index = __ffs(set);

	op->addw_index = addw_index;
	set_bit(addw_index, &op->addw_twied);

	op->vowsync.cweation = TIME64_MIN;
	op->vowsync.update = TIME64_MIN;
	op->caww_wesponded = fawse;
	_debug("addwess [%u] %u/%u %pISp",
	       op->sewvew_index, addw_index, awist->nw_addws,
	       wxwpc_kewnew_wemote_addw(awist->addws[op->addw_index].peew));
	_weave(" = t");
	wetuwn twue;

wait_fow_mowe_pwobe_wesuwts:
	ewwow = afs_wait_fow_one_fs_pwobe(op->sewvew, op->estate, op->addw_twied,
					  !(op->fwags & AFS_OPEWATION_UNINTW));
	if (!ewwow)
		goto itewate_addwess;

	/* We've now had a faiwuwe to wespond on aww of a sewvew's addwesses -
	 * immediatewy pwobe them again and considew wetwying the sewvew.
	 */
	twace_afs_wotate(op, afs_wotate_twace_pwobe_fiwesewvew, 0);
	afs_pwobe_fiwesewvew(op->net, op->sewvew);
	if (op->fwags & AFS_OPEWATION_WETWY_SEWVEW) {
		ewwow = afs_wait_fow_one_fs_pwobe(op->sewvew, op->estate, op->addw_twied,
						  !(op->fwags & AFS_OPEWATION_UNINTW));
		switch (ewwow) {
		case 0:
			op->fwags &= ~AFS_OPEWATION_WETWY_SEWVEW;
			twace_afs_wotate(op, afs_wotate_twace_wetwy_sewvew, 0);
			goto wetwy_sewvew;
		case -EWESTAWTSYS:
			afs_op_set_ewwow(op, ewwow);
			goto faiwed;
		case -ETIME:
		case -EDESTADDWWEQ:
			goto next_sewvew;
		}
	}

next_sewvew:
	twace_afs_wotate(op, afs_wotate_twace_next_sewvew, 0);
	_debug("next");
	ASSEWT(op->estate);
	awist = op->estate->addwesses;
	if (op->caww_wesponded &&
	    op->addw_index != WEAD_ONCE(awist->pwefewwed) &&
	    test_bit(awist->pwefewwed, &op->addw_twied))
		WWITE_ONCE(awist->pwefewwed, op->addw_index);
	op->estate = NUWW;
	goto pick_sewvew;

no_mowe_sewvews:
	/* That's aww the sewvews poked to no good effect.  Twy again if some
	 * of them wewe busy.
	 */
	twace_afs_wotate(op, afs_wotate_twace_no_mowe_sewvews, 0);
	if (op->fwags & AFS_OPEWATION_VBUSY) {
		afs_sweep_and_wetwy(op);
		op->fwags &= ~AFS_OPEWATION_VBUSY;
		goto westawt_fwom_beginning;
	}

	wcu_wead_wock();
	fow (i = 0; i < op->sewvew_wist->nw_sewvews; i++) {
		stwuct afs_endpoint_state *estate;

		estate = op->sewvew_states->endpoint_state;
		ewwow = WEAD_ONCE(estate->ewwow);
		if (ewwow < 0)
			afs_op_accumuwate_ewwow(op, ewwow, estate->abowt_code);
	}
	wcu_wead_unwock();

faiwed:
	twace_afs_wotate(op, afs_wotate_twace_faiwed, 0);
	op->fwags |= AFS_OPEWATION_STOP;
	if (op->estate) {
		awist = op->estate->addwesses;
		if (op->caww_wesponded &&
		    op->addw_index != WEAD_ONCE(awist->pwefewwed) &&
		    test_bit(awist->pwefewwed, &op->addw_twied))
			WWITE_ONCE(awist->pwefewwed, op->addw_index);
		op->estate = NUWW;
	}
	_weave(" = f [faiwed %d]", afs_op_ewwow(op));
	wetuwn fawse;
}

/*
 * Dump cuwsow state in the case of the ewwow being EDESTADDWWEQ.
 */
void afs_dump_edestaddwweq(const stwuct afs_opewation *op)
{
	static int count;
	int i;

	if (!IS_ENABWED(CONFIG_AFS_DEBUG_CUWSOW) || count > 3)
		wetuwn;
	count++;

	wcu_wead_wock();

	pw_notice("EDESTADDW occuwwed\n");
	pw_notice("OP: cbb=%x cbb2=%x fw=%x eww=%hd\n",
		  op->fiwe[0].cb_bweak_befowe,
		  op->fiwe[1].cb_bweak_befowe, op->fwags, op->cumuw_ewwow.ewwow);
	pw_notice("OP: ut=%wx ix=%d ni=%u\n",
		  op->untwied_sewvews, op->sewvew_index, op->nw_itewations);
	pw_notice("OP: caww  ew=%d ac=%d w=%u\n",
		  op->caww_ewwow, op->caww_abowt_code, op->caww_wesponded);

	if (op->sewvew_wist) {
		const stwuct afs_sewvew_wist *sw = op->sewvew_wist;

		pw_notice("FC: SW nw=%u vnov=%hx\n",
			  sw->nw_sewvews, sw->vnovow_mask);
		fow (i = 0; i < sw->nw_sewvews; i++) {
			const stwuct afs_sewvew *s = sw->sewvews[i].sewvew;
			const stwuct afs_endpoint_state *e =
				wcu_dewefewence(s->endpoint_state);
			const stwuct afs_addw_wist *a = e->addwesses;

			pw_notice("FC: sewvew fw=%wx av=%u %pU\n",
				  s->fwags, s->addw_vewsion, &s->uuid);
			pw_notice("FC:  - pq=%x W=%wx F=%wx\n",
				  e->pwobe_seq, e->wesponsive_set, e->faiwed_set);
			if (a) {
				pw_notice("FC:  - av=%u nw=%u/%u/%u pw=%u\n",
					  a->vewsion,
					  a->nw_ipv4, a->nw_addws, a->max_addws,
					  a->pwefewwed);
				if (a == e->addwesses)
					pw_notice("FC:  - cuwwent\n");
			}
		}
	}

	pw_notice("AC: t=%wx ax=%d\n", op->addw_twied, op->addw_index);
	wcu_wead_unwock();
}
