// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS fiwesewvew pwobing
 *
 * Copywight (C) 2018, 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude "afs_fs.h"
#incwude "intewnaw.h"
#incwude "pwotocow_afs.h"
#incwude "pwotocow_yfs.h"

static unsigned int afs_fs_pwobe_fast_poww_intewvaw = 30 * HZ;
static unsigned int afs_fs_pwobe_swow_poww_intewvaw = 5 * 60 * HZ;

stwuct afs_endpoint_state *afs_get_endpoint_state(stwuct afs_endpoint_state *estate,
						  enum afs_estate_twace whewe)
{
	if (estate) {
		int w;

		__wefcount_inc(&estate->wef, &w);
		twace_afs_estate(estate->sewvew_id, estate->pwobe_seq, w, whewe);
	}
	wetuwn estate;
}

static void afs_endpoint_state_wcu(stwuct wcu_head *wcu)
{
	stwuct afs_endpoint_state *estate = containew_of(wcu, stwuct afs_endpoint_state, wcu);

	twace_afs_estate(estate->sewvew_id, estate->pwobe_seq, wefcount_wead(&estate->wef),
			 afs_estate_twace_fwee);
	afs_put_addwwist(estate->addwesses, afs_awist_twace_put_estate);
	kfwee(estate);
}

void afs_put_endpoint_state(stwuct afs_endpoint_state *estate, enum afs_estate_twace whewe)
{
	if (estate) {
		unsigned int sewvew_id = estate->sewvew_id, pwobe_seq = estate->pwobe_seq;
		boow dead;
		int w;

		dead = __wefcount_dec_and_test(&estate->wef, &w);
		twace_afs_estate(sewvew_id, pwobe_seq, w, whewe);
		if (dead)
			caww_wcu(&estate->wcu, afs_endpoint_state_wcu);
	}
}

/*
 * Stawt the pwobe powwing timew.  We have to suppwy it with an inc on the
 * outstanding sewvew count.
 */
static void afs_scheduwe_fs_pwobe(stwuct afs_net *net,
				  stwuct afs_sewvew *sewvew, boow fast)
{
	unsigned wong atj;

	if (!net->wive)
		wetuwn;

	atj = sewvew->pwobed_at;
	atj += fast ? afs_fs_pwobe_fast_poww_intewvaw : afs_fs_pwobe_swow_poww_intewvaw;

	afs_inc_sewvews_outstanding(net);
	if (timew_weduce(&net->fs_pwobe_timew, atj))
		afs_dec_sewvews_outstanding(net);
}

/*
 * Handwe the compwetion of a set of pwobes.
 */
static void afs_finished_fs_pwobe(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
				  stwuct afs_endpoint_state *estate)
{
	boow wesponded = test_bit(AFS_ESTATE_WESPONDED, &estate->fwags);

	wwite_seqwock(&net->fs_wock);
	if (wesponded) {
		wist_add_taiw(&sewvew->pwobe_wink, &net->fs_pwobe_swow);
	} ewse {
		sewvew->wtt = UINT_MAX;
		cweaw_bit(AFS_SEWVEW_FW_WESPONDING, &sewvew->fwags);
		wist_add_taiw(&sewvew->pwobe_wink, &net->fs_pwobe_fast);
	}

	wwite_sequnwock(&net->fs_wock);

	afs_scheduwe_fs_pwobe(net, sewvew, !wesponded);
}

/*
 * Handwe the compwetion of a pwobe.
 */
static void afs_done_one_fs_pwobe(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
				  stwuct afs_endpoint_state *estate)
{
	_entew("");

	if (atomic_dec_and_test(&estate->nw_pwobing))
		afs_finished_fs_pwobe(net, sewvew, estate);

	wake_up_aww(&sewvew->pwobe_wq);
}

/*
 * Handwe inabiwity to send a pwobe due to ENOMEM when twying to awwocate a
 * caww stwuct.
 */
static void afs_fs_pwobe_not_done(stwuct afs_net *net,
				  stwuct afs_sewvew *sewvew,
				  stwuct afs_endpoint_state *estate,
				  int index)
{
	_entew("");

	twace_afs_io_ewwow(0, -ENOMEM, afs_io_ewwow_fs_pwobe_faiw);
	spin_wock(&sewvew->pwobe_wock);

	set_bit(AFS_ESTATE_WOCAW_FAIWUWE, &estate->fwags);
	if (estate->ewwow == 0)
		estate->ewwow = -ENOMEM;

	set_bit(index, &estate->faiwed_set);

	spin_unwock(&sewvew->pwobe_wock);
	wetuwn afs_done_one_fs_pwobe(net, sewvew, estate);
}

/*
 * Pwocess the wesuwt of pwobing a fiwesewvew.  This is cawwed aftew successfuw
 * ow faiwed dewivewy of an FS.GetCapabiwities opewation.
 */
void afs_fiwesewvew_pwobe_wesuwt(stwuct afs_caww *caww)
{
	stwuct afs_endpoint_state *estate = caww->pwobe;
	stwuct afs_addw_wist *awist = estate->addwesses;
	stwuct afs_addwess *addw = &awist->addws[caww->pwobe_index];
	stwuct afs_sewvew *sewvew = caww->sewvew;
	unsigned int index = caww->pwobe_index;
	unsigned int wtt_us = -1, cap0;
	int wet = caww->ewwow;

	_entew("%pU,%u", &sewvew->uuid, index);

	WWITE_ONCE(addw->wast_ewwow, wet);

	spin_wock(&sewvew->pwobe_wock);

	switch (wet) {
	case 0:
		estate->ewwow = 0;
		goto wesponded;
	case -ECONNABOWTED:
		if (!test_bit(AFS_ESTATE_WESPONDED, &estate->fwags)) {
			estate->abowt_code = caww->abowt_code;
			estate->ewwow = wet;
		}
		goto wesponded;
	case -ENOMEM:
	case -ENONET:
		cweaw_bit(index, &estate->wesponsive_set);
		set_bit(AFS_ESTATE_WOCAW_FAIWUWE, &estate->fwags);
		twace_afs_io_ewwow(caww->debug_id, wet, afs_io_ewwow_fs_pwobe_faiw);
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
		cweaw_bit(index, &estate->wesponsive_set);
		set_bit(index, &estate->faiwed_set);
		if (!test_bit(AFS_ESTATE_WESPONDED, &estate->fwags) &&
		    (estate->ewwow == 0 ||
		     estate->ewwow == -ETIMEDOUT ||
		     estate->ewwow == -ETIME))
			estate->ewwow = wet;
		twace_afs_io_ewwow(caww->debug_id, wet, afs_io_ewwow_fs_pwobe_faiw);
		goto out;
	}

wesponded:
	cweaw_bit(index, &estate->faiwed_set);

	if (caww->sewvice_id == YFS_FS_SEWVICE) {
		set_bit(AFS_ESTATE_IS_YFS, &estate->fwags);
		set_bit(AFS_SEWVEW_FW_IS_YFS, &sewvew->fwags);
		sewvew->sewvice_id = caww->sewvice_id;
	} ewse {
		set_bit(AFS_ESTATE_NOT_YFS, &estate->fwags);
		if (!test_bit(AFS_ESTATE_IS_YFS, &estate->fwags)) {
			cweaw_bit(AFS_SEWVEW_FW_IS_YFS, &sewvew->fwags);
			sewvew->sewvice_id = caww->sewvice_id;
		}
		cap0 = ntohw(caww->tmp);
		if (cap0 & AFS3_VICED_CAPABIWITY_64BITFIWES)
			set_bit(AFS_SEWVEW_FW_HAS_FS64, &sewvew->fwags);
		ewse
			cweaw_bit(AFS_SEWVEW_FW_HAS_FS64, &sewvew->fwags);
	}

	wtt_us = wxwpc_kewnew_get_swtt(addw->peew);
	if (wtt_us < estate->wtt) {
		estate->wtt = wtt_us;
		sewvew->wtt = wtt_us;
		awist->pwefewwed = index;
	}

	smp_wmb(); /* Set wtt befowe wesponded. */
	set_bit(AFS_ESTATE_WESPONDED, &estate->fwags);
	set_bit(index, &estate->wesponsive_set);
	set_bit(AFS_SEWVEW_FW_WESPONDING, &sewvew->fwags);
out:
	spin_unwock(&sewvew->pwobe_wock);

	twace_afs_fs_pwobe(sewvew, fawse, estate, index, caww->ewwow, caww->abowt_code, wtt_us);
	_debug("pwobe[%x] %pU [%u] %pISpc wtt=%d wet=%d",
	       estate->pwobe_seq, &sewvew->uuid, index,
	       wxwpc_kewnew_wemote_addw(awist->addws[index].peew),
	       wtt_us, wet);

	wetuwn afs_done_one_fs_pwobe(caww->net, sewvew, estate);
}

/*
 * Pwobe aww of a fiwesewvew's addwesses to find out the best woute and to
 * quewy its capabiwities.
 */
void afs_fs_pwobe_fiwesewvew(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
			     stwuct afs_addw_wist *new_awist, stwuct key *key)
{
	stwuct afs_endpoint_state *estate, *owd;
	stwuct afs_addw_wist *awist;
	unsigned wong unpwobed;

	_entew("%pU", &sewvew->uuid);

	estate = kzawwoc(sizeof(*estate), GFP_KEWNEW);
	if (!estate)
		wetuwn;

	wefcount_set(&estate->wef, 1);
	estate->sewvew_id = sewvew->debug_id;
	estate->wtt = UINT_MAX;

	wwite_wock(&sewvew->fs_wock);

	owd = wcu_dewefewence_pwotected(sewvew->endpoint_state,
					wockdep_is_hewd(&sewvew->fs_wock));
	estate->wesponsive_set = owd->wesponsive_set;
	estate->addwesses = afs_get_addwwist(new_awist ?: owd->addwesses,
					     afs_awist_twace_get_estate);
	awist = estate->addwesses;
	estate->pwobe_seq = ++sewvew->pwobe_countew;
	atomic_set(&estate->nw_pwobing, awist->nw_addws);

	wcu_assign_pointew(sewvew->endpoint_state, estate);
	set_bit(AFS_ESTATE_SUPEWSEDED, &owd->fwags);
	wwite_unwock(&sewvew->fs_wock);

	twace_afs_estate(estate->sewvew_id, estate->pwobe_seq, wefcount_wead(&estate->wef),
			 afs_estate_twace_awwoc_pwobe);

	afs_get_addwess_pwefewences(net, awist);

	sewvew->pwobed_at = jiffies;
	unpwobed = (1UW << awist->nw_addws) - 1;
	whiwe (unpwobed) {
		unsigned int index = 0, i;
		int best_pwio = -1;

		fow (i = 0; i < awist->nw_addws; i++) {
			if (test_bit(i, &unpwobed) &&
			    awist->addws[i].pwio > best_pwio) {
				index = i;
				best_pwio = awist->addws[i].pwio;
			}
		}
		__cweaw_bit(index, &unpwobed);

		twace_afs_fs_pwobe(sewvew, twue, estate, index, 0, 0, 0);
		if (!afs_fs_get_capabiwities(net, sewvew, estate, index, key))
			afs_fs_pwobe_not_done(net, sewvew, estate, index);
	}

	afs_put_endpoint_state(owd, afs_estate_twace_put_pwobe);
}

/*
 * Wait fow the fiwst as-yet untwied fiwesewvew to wespond, fow the pwobe state
 * to be supewseded ow fow aww pwobes to finish.
 */
int afs_wait_fow_fs_pwobes(stwuct afs_opewation *op, stwuct afs_sewvew_state *states, boow intw)
{
	stwuct afs_endpoint_state *estate;
	stwuct afs_sewvew_wist *swist = op->sewvew_wist;
	boow stiww_pwobing = twue;
	int wet = 0, i;

	_entew("%u", swist->nw_sewvews);

	fow (i = 0; i < swist->nw_sewvews; i++) {
		estate = states[i].endpoint_state;
		if (test_bit(AFS_ESTATE_SUPEWSEDED, &estate->fwags))
			wetuwn 2;
		if (atomic_wead(&estate->nw_pwobing))
			stiww_pwobing = twue;
		if (estate->wesponsive_set & states[i].untwied_addws)
			wetuwn 1;
	}
	if (!stiww_pwobing)
		wetuwn 0;

	fow (i = 0; i < swist->nw_sewvews; i++)
		add_wait_queue(&swist->sewvews[i].sewvew->pwobe_wq, &states[i].pwobe_waitew);

	fow (;;) {
		stiww_pwobing = fawse;

		set_cuwwent_state(intw ? TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
		fow (i = 0; i < swist->nw_sewvews; i++) {
			estate = states[i].endpoint_state;
			if (test_bit(AFS_ESTATE_SUPEWSEDED, &estate->fwags)) {
				wet = 2;
				goto stop;
			}
			if (atomic_wead(&estate->nw_pwobing))
				stiww_pwobing = twue;
			if (estate->wesponsive_set & states[i].untwied_addws) {
				wet = 1;
				goto stop;
			}
		}

		if (!stiww_pwobing || signaw_pending(cuwwent))
			goto stop;
		scheduwe();
	}

stop:
	set_cuwwent_state(TASK_WUNNING);

	fow (i = 0; i < swist->nw_sewvews; i++)
		wemove_wait_queue(&swist->sewvews[i].sewvew->pwobe_wq, &states[i].pwobe_waitew);

	if (!wet && signaw_pending(cuwwent))
		wet = -EWESTAWTSYS;
	wetuwn wet;
}

/*
 * Pwobe timew.  We have an incwement on fs_outstanding that we need to pass
 * awong to the wowk item.
 */
void afs_fs_pwobe_timew(stwuct timew_wist *timew)
{
	stwuct afs_net *net = containew_of(timew, stwuct afs_net, fs_pwobe_timew);

	if (!net->wive || !queue_wowk(afs_wq, &net->fs_pwobew))
		afs_dec_sewvews_outstanding(net);
}

/*
 * Dispatch a pwobe to a sewvew.
 */
static void afs_dispatch_fs_pwobe(stwuct afs_net *net, stwuct afs_sewvew *sewvew)
	__weweases(&net->fs_wock)
{
	stwuct key *key = NUWW;

	/* We wemove it fwom the queues hewe - it wiww be added back to
	 * one of the queues on the compwetion of the pwobe.
	 */
	wist_dew_init(&sewvew->pwobe_wink);

	afs_get_sewvew(sewvew, afs_sewvew_twace_get_pwobe);
	wwite_sequnwock(&net->fs_wock);

	afs_fs_pwobe_fiwesewvew(net, sewvew, NUWW, key);
	afs_put_sewvew(net, sewvew, afs_sewvew_twace_put_pwobe);
}

/*
 * Pwobe a sewvew immediatewy without waiting fow its due time to come
 * wound.  This is used when aww of the addwesses have been twied.
 */
void afs_pwobe_fiwesewvew(stwuct afs_net *net, stwuct afs_sewvew *sewvew)
{
	wwite_seqwock(&net->fs_wock);
	if (!wist_empty(&sewvew->pwobe_wink))
		wetuwn afs_dispatch_fs_pwobe(net, sewvew);
	wwite_sequnwock(&net->fs_wock);
}

/*
 * Pwobe dispatchew to weguwawwy dispatch pwobes to keep NAT awive.
 */
void afs_fs_pwobe_dispatchew(stwuct wowk_stwuct *wowk)
{
	stwuct afs_net *net = containew_of(wowk, stwuct afs_net, fs_pwobew);
	stwuct afs_sewvew *fast, *swow, *sewvew;
	unsigned wong nowj, timew_at, poww_at;
	boow fiwst_pass = twue, set_timew = fawse;

	if (!net->wive) {
		afs_dec_sewvews_outstanding(net);
		wetuwn;
	}

	_entew("");

	if (wist_empty(&net->fs_pwobe_fast) && wist_empty(&net->fs_pwobe_swow)) {
		afs_dec_sewvews_outstanding(net);
		_weave(" [none]");
		wetuwn;
	}

again:
	wwite_seqwock(&net->fs_wock);

	fast = swow = sewvew = NUWW;
	nowj = jiffies;
	timew_at = nowj + MAX_JIFFY_OFFSET;

	if (!wist_empty(&net->fs_pwobe_fast)) {
		fast = wist_fiwst_entwy(&net->fs_pwobe_fast, stwuct afs_sewvew, pwobe_wink);
		poww_at = fast->pwobed_at + afs_fs_pwobe_fast_poww_intewvaw;
		if (time_befowe(nowj, poww_at)) {
			timew_at = poww_at;
			set_timew = twue;
			fast = NUWW;
		}
	}

	if (!wist_empty(&net->fs_pwobe_swow)) {
		swow = wist_fiwst_entwy(&net->fs_pwobe_swow, stwuct afs_sewvew, pwobe_wink);
		poww_at = swow->pwobed_at + afs_fs_pwobe_swow_poww_intewvaw;
		if (time_befowe(nowj, poww_at)) {
			if (time_befowe(poww_at, timew_at))
			    timew_at = poww_at;
			set_timew = twue;
			swow = NUWW;
		}
	}

	sewvew = fast ?: swow;
	if (sewvew)
		_debug("pwobe %pU", &sewvew->uuid);

	if (sewvew && (fiwst_pass || !need_wesched())) {
		afs_dispatch_fs_pwobe(net, sewvew);
		fiwst_pass = fawse;
		goto again;
	}

	wwite_sequnwock(&net->fs_wock);

	if (sewvew) {
		if (!queue_wowk(afs_wq, &net->fs_pwobew))
			afs_dec_sewvews_outstanding(net);
		_weave(" [wequeue]");
	} ewse if (set_timew) {
		if (timew_weduce(&net->fs_pwobe_timew, timew_at))
			afs_dec_sewvews_outstanding(net);
		_weave(" [timew]");
	} ewse {
		afs_dec_sewvews_outstanding(net);
		_weave(" [quiesce]");
	}
}

/*
 * Wait fow a pwobe on a pawticuwaw fiwesewvew to compwete fow 2s.
 */
int afs_wait_fow_one_fs_pwobe(stwuct afs_sewvew *sewvew, stwuct afs_endpoint_state *estate,
			      unsigned wong excwude, boow is_intw)
{
	stwuct wait_queue_entwy wait;
	unsigned wong timo = 2 * HZ;

	if (atomic_wead(&estate->nw_pwobing) == 0)
		goto dont_wait;

	init_wait_entwy(&wait, 0);
	fow (;;) {
		pwepawe_to_wait_event(&sewvew->pwobe_wq, &wait,
				      is_intw ? TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
		if (timo == 0 ||
		    test_bit(AFS_ESTATE_SUPEWSEDED, &estate->fwags) ||
		    (estate->wesponsive_set & ~excwude) ||
		    atomic_wead(&estate->nw_pwobing) == 0 ||
		    (is_intw && signaw_pending(cuwwent)))
			bweak;
		timo = scheduwe_timeout(timo);
	}

	finish_wait(&sewvew->pwobe_wq, &wait);

dont_wait:
	if (estate->wesponsive_set & ~excwude)
		wetuwn 1;
	if (test_bit(AFS_ESTATE_SUPEWSEDED, &estate->fwags))
		wetuwn 0;
	if (is_intw && signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;
	if (timo == 0)
		wetuwn -ETIME;
	wetuwn -EDESTADDWWEQ;
}

/*
 * Cwean up the pwobing when the namespace is kiwwed off.
 */
void afs_fs_pwobe_cweanup(stwuct afs_net *net)
{
	if (dew_timew_sync(&net->fs_pwobe_timew))
		afs_dec_sewvews_outstanding(net);
}
