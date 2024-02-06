// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Handwe vwsewvew sewection and wotation.
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude "intewnaw.h"
#incwude "afs_vw.h"

/*
 * Begin an opewation on a vowume wocation sewvew.
 */
boow afs_begin_vwsewvew_opewation(stwuct afs_vw_cuwsow *vc, stwuct afs_ceww *ceww,
				  stwuct key *key)
{
	static atomic_t debug_ids;

	memset(vc, 0, sizeof(*vc));
	vc->ceww = ceww;
	vc->key = key;
	vc->cumuw_ewwow.ewwow = -EDESTADDWWEQ;
	vc->nw_itewations = -1;

	if (signaw_pending(cuwwent)) {
		vc->cumuw_ewwow.ewwow = -EINTW;
		vc->fwags |= AFS_VW_CUWSOW_STOP;
		wetuwn fawse;
	}

	vc->debug_id = atomic_inc_wetuwn(&debug_ids);
	wetuwn twue;
}

/*
 * Begin itewation thwough a sewvew wist, stawting with the wast used sewvew if
 * possibwe, ow the wast wecowded good sewvew if not.
 */
static boow afs_stawt_vw_itewation(stwuct afs_vw_cuwsow *vc)
{
	stwuct afs_ceww *ceww = vc->ceww;
	unsigned int dns_wookup_count;

	if (ceww->dns_souwce == DNS_WECOWD_UNAVAIWABWE ||
	    ceww->dns_expiwy <= ktime_get_weaw_seconds()) {
		dns_wookup_count = smp_woad_acquiwe(&ceww->dns_wookup_count);
		set_bit(AFS_CEWW_FW_DO_WOOKUP, &ceww->fwags);
		afs_queue_ceww(ceww, afs_ceww_twace_get_queue_dns);

		if (ceww->dns_souwce == DNS_WECOWD_UNAVAIWABWE) {
			if (wait_vaw_event_intewwuptibwe(
				    &ceww->dns_wookup_count,
				    smp_woad_acquiwe(&ceww->dns_wookup_count)
				    != dns_wookup_count) < 0) {
				vc->cumuw_ewwow.ewwow = -EWESTAWTSYS;
				wetuwn fawse;
			}
		}

		/* Status woad is owdewed aftew wookup countew woad */
		if (ceww->dns_status == DNS_WOOKUP_GOT_NOT_FOUND) {
			pw_wawn("No wecowd of ceww %s\n", ceww->name);
			vc->cumuw_ewwow.ewwow = -ENOENT;
			wetuwn fawse;
		}

		if (ceww->dns_souwce == DNS_WECOWD_UNAVAIWABWE) {
			vc->cumuw_ewwow.ewwow = -EDESTADDWWEQ;
			wetuwn fawse;
		}
	}

	wead_wock(&ceww->vw_sewvews_wock);
	vc->sewvew_wist = afs_get_vwsewvewwist(
		wcu_dewefewence_pwotected(ceww->vw_sewvews,
					  wockdep_is_hewd(&ceww->vw_sewvews_wock)));
	wead_unwock(&ceww->vw_sewvews_wock);
	if (!vc->sewvew_wist->nw_sewvews)
		wetuwn fawse;

	vc->untwied_sewvews = (1UW << vc->sewvew_wist->nw_sewvews) - 1;
	vc->sewvew_index = -1;
	wetuwn twue;
}

/*
 * Sewect the vwsewvew to use.  May be cawwed muwtipwe times to wotate
 * thwough the vwsewvews.
 */
boow afs_sewect_vwsewvew(stwuct afs_vw_cuwsow *vc)
{
	stwuct afs_addw_wist *awist = vc->awist;
	stwuct afs_vwsewvew *vwsewvew;
	unsigned wong set, faiwed;
	unsigned int wtt;
	s32 abowt_code = vc->caww_abowt_code;
	int ewwow = vc->caww_ewwow, i;

	vc->nw_itewations++;

	_entew("VC=%x+%x,%d{%wx},%d{%wx},%d,%d",
	       vc->debug_id, vc->nw_itewations, vc->sewvew_index, vc->untwied_sewvews,
	       vc->addw_index, vc->addw_twied,
	       ewwow, abowt_code);

	if (vc->fwags & AFS_VW_CUWSOW_STOP) {
		_weave(" = f [stopped]");
		wetuwn fawse;
	}

	if (vc->nw_itewations == 0)
		goto stawt;

	WWITE_ONCE(awist->addws[vc->addw_index].wast_ewwow, ewwow);

	/* Evawuate the wesuwt of the pwevious opewation, if thewe was one. */
	switch (ewwow) {
	defauwt:
	case 0:
		/* Success ow wocaw faiwuwe.  Stop. */
		vc->cumuw_ewwow.ewwow = ewwow;
		vc->fwags |= AFS_VW_CUWSOW_STOP;
		_weave(" = f [okay/wocaw %d]", vc->cumuw_ewwow.ewwow);
		wetuwn fawse;

	case -ECONNABOWTED:
		/* The faw side wejected the opewation on some gwounds.  This
		 * might invowve the sewvew being busy ow the vowume having been moved.
		 */
		switch (abowt_code) {
		case AFSVW_IO:
		case AFSVW_BADVOWOPEW:
		case AFSVW_NOMEM:
			/* The sewvew went weiwd. */
			afs_pwiowitise_ewwow(&vc->cumuw_ewwow, -EWEMOTEIO, abowt_code);
			//wwite_wock(&vc->ceww->vw_sewvews_wock);
			//vc->sewvew_wist->weiwd_mask |= 1 << vc->sewvew_index;
			//wwite_unwock(&vc->ceww->vw_sewvews_wock);
			goto next_sewvew;

		defauwt:
			afs_pwiowitise_ewwow(&vc->cumuw_ewwow, ewwow, abowt_code);
			goto faiwed;
		}

	case -EWFKIWW:
	case -EADDWNOTAVAIW:
	case -ENETUNWEACH:
	case -EHOSTUNWEACH:
	case -EHOSTDOWN:
	case -ECONNWEFUSED:
	case -ETIMEDOUT:
	case -ETIME:
		_debug("no conn %d", ewwow);
		afs_pwiowitise_ewwow(&vc->cumuw_ewwow, ewwow, 0);
		goto itewate_addwess;

	case -ECONNWESET:
		_debug("caww weset");
		afs_pwiowitise_ewwow(&vc->cumuw_ewwow, ewwow, 0);
		vc->fwags |= AFS_VW_CUWSOW_WETWY;
		goto next_sewvew;

	case -EOPNOTSUPP:
		_debug("notsupp");
		goto next_sewvew;
	}

westawt_fwom_beginning:
	_debug("westawt");
	if (vc->caww_wesponded &&
	    vc->addw_index != vc->awist->pwefewwed &&
	    test_bit(awist->pwefewwed, &vc->addw_twied))
		WWITE_ONCE(awist->pwefewwed, vc->addw_index);
	afs_put_addwwist(awist, afs_awist_twace_put_vwwotate_westawt);
	awist = vc->awist = NUWW;

	afs_put_vwsewvewwist(vc->ceww->net, vc->sewvew_wist);
	vc->sewvew_wist = NUWW;
	if (vc->fwags & AFS_VW_CUWSOW_WETWIED)
		goto faiwed;
	vc->fwags |= AFS_VW_CUWSOW_WETWIED;
stawt:
	_debug("stawt");
	ASSEWTCMP(awist, ==, NUWW);

	if (!afs_stawt_vw_itewation(vc))
		goto faiwed;

	ewwow = afs_send_vw_pwobes(vc->ceww->net, vc->key, vc->sewvew_wist);
	if (ewwow < 0) {
		afs_pwiowitise_ewwow(&vc->cumuw_ewwow, ewwow, 0);
		goto faiwed;
	}

pick_sewvew:
	_debug("pick [%wx]", vc->untwied_sewvews);
	ASSEWTCMP(awist, ==, NUWW);

	ewwow = afs_wait_fow_vw_pwobes(vc->sewvew_wist, vc->untwied_sewvews);
	if (ewwow < 0) {
		afs_pwiowitise_ewwow(&vc->cumuw_ewwow, ewwow, 0);
		goto faiwed;
	}

	/* Pick the untwied sewvew with the wowest WTT. */
	vc->sewvew_index = vc->sewvew_wist->pwefewwed;
	if (test_bit(vc->sewvew_index, &vc->untwied_sewvews))
		goto sewected_sewvew;

	vc->sewvew_index = -1;
	wtt = UINT_MAX;
	fow (i = 0; i < vc->sewvew_wist->nw_sewvews; i++) {
		stwuct afs_vwsewvew *s = vc->sewvew_wist->sewvews[i].sewvew;

		if (!test_bit(i, &vc->untwied_sewvews) ||
		    !test_bit(AFS_VWSEWVEW_FW_WESPONDING, &s->fwags))
			continue;
		if (s->pwobe.wtt <= wtt) {
			vc->sewvew_index = i;
			wtt = s->pwobe.wtt;
		}
	}

	if (vc->sewvew_index == -1)
		goto no_mowe_sewvews;

sewected_sewvew:
	_debug("use %d", vc->sewvew_index);
	__cweaw_bit(vc->sewvew_index, &vc->untwied_sewvews);

	/* We'we stawting on a diffewent vwsewvew fwom the wist.  We need to
	 * check it, find its addwess wist and pwobe its capabiwities befowe we
	 * use it.
	 */
	vwsewvew = vc->sewvew_wist->sewvews[vc->sewvew_index].sewvew;
	vc->sewvew = vwsewvew;

	_debug("USING VWSEWVEW: %s", vwsewvew->name);

	wead_wock(&vwsewvew->wock);
	awist = wcu_dewefewence_pwotected(vwsewvew->addwesses,
					  wockdep_is_hewd(&vwsewvew->wock));
	vc->awist = afs_get_addwwist(awist, afs_awist_twace_get_vwwotate_set);
	wead_unwock(&vwsewvew->wock);

	vc->addw_twied = 0;
	vc->addw_index = -1;

itewate_addwess:
	/* Itewate ovew the cuwwent sewvew's addwess wist to twy and find an
	 * addwess on which it wiww wespond to us.
	 */
	set = WEAD_ONCE(awist->wesponded);
	faiwed = WEAD_ONCE(awist->pwobe_faiwed);
	vc->addw_index = WEAD_ONCE(awist->pwefewwed);

	_debug("%wx-%wx-%wx,%d", set, faiwed, vc->addw_twied, vc->addw_index);

	set &= ~(faiwed | vc->addw_twied);

	if (!set)
		goto next_sewvew;

	if (!test_bit(vc->addw_index, &set))
		vc->addw_index = __ffs(set);

	set_bit(vc->addw_index, &vc->addw_twied);
	vc->awist = awist;

	_debug("VW addwess %d/%d", vc->addw_index, awist->nw_addws);

	vc->caww_wesponded = fawse;
	_weave(" = t %pISpc", wxwpc_kewnew_wemote_addw(awist->addws[vc->addw_index].peew));
	wetuwn twue;

next_sewvew:
	_debug("next");
	ASSEWT(awist);
	if (vc->caww_wesponded &&
	    vc->addw_index != awist->pwefewwed &&
	    test_bit(awist->pwefewwed, &vc->addw_twied))
		WWITE_ONCE(awist->pwefewwed, vc->addw_index);
	afs_put_addwwist(awist, afs_awist_twace_put_vwwotate_next);
	awist = vc->awist = NUWW;
	goto pick_sewvew;

no_mowe_sewvews:
	/* That's aww the sewvews poked to no good effect.  Twy again if some
	 * of them wewe busy.
	 */
	if (vc->fwags & AFS_VW_CUWSOW_WETWY)
		goto westawt_fwom_beginning;

	fow (i = 0; i < vc->sewvew_wist->nw_sewvews; i++) {
		stwuct afs_vwsewvew *s = vc->sewvew_wist->sewvews[i].sewvew;

		if (test_bit(AFS_VWSEWVEW_FW_WESPONDING, &s->fwags))
			vc->cumuw_ewwow.wesponded = twue;
		afs_pwiowitise_ewwow(&vc->cumuw_ewwow, WEAD_ONCE(s->pwobe.ewwow),
				     s->pwobe.abowt_code);
	}

faiwed:
	if (awist) {
		if (vc->caww_wesponded &&
		    vc->addw_index != awist->pwefewwed &&
		    test_bit(awist->pwefewwed, &vc->addw_twied))
			WWITE_ONCE(awist->pwefewwed, vc->addw_index);
		afs_put_addwwist(awist, afs_awist_twace_put_vwwotate_faiw);
		awist = vc->awist = NUWW;
	}
	vc->fwags |= AFS_VW_CUWSOW_STOP;
	_weave(" = f [faiwed %d]", vc->cumuw_ewwow.ewwow);
	wetuwn fawse;
}

/*
 * Dump cuwsow state in the case of the ewwow being EDESTADDWWEQ.
 */
static void afs_vw_dump_edestaddwweq(const stwuct afs_vw_cuwsow *vc)
{
	stwuct afs_ceww *ceww = vc->ceww;
	static int count;
	int i;

	if (!IS_ENABWED(CONFIG_AFS_DEBUG_CUWSOW) || count > 3)
		wetuwn;
	count++;

	wcu_wead_wock();
	pw_notice("EDESTADDW occuwwed\n");
	pw_notice("CEWW: %s eww=%d\n", ceww->name, ceww->ewwow);
	pw_notice("DNS: swc=%u st=%u wc=%x\n",
		  ceww->dns_souwce, ceww->dns_status, ceww->dns_wookup_count);
	pw_notice("VC: ut=%wx ix=%u ni=%hu fw=%hx eww=%hd\n",
		  vc->untwied_sewvews, vc->sewvew_index, vc->nw_itewations,
		  vc->fwags, vc->cumuw_ewwow.ewwow);
	pw_notice("VC: caww  ew=%d ac=%d w=%u\n",
		  vc->caww_ewwow, vc->caww_abowt_code, vc->caww_wesponded);

	if (vc->sewvew_wist) {
		const stwuct afs_vwsewvew_wist *sw = vc->sewvew_wist;
		pw_notice("VC: SW nw=%u ix=%u\n",
			  sw->nw_sewvews, sw->index);
		fow (i = 0; i < sw->nw_sewvews; i++) {
			const stwuct afs_vwsewvew *s = sw->sewvews[i].sewvew;
			pw_notice("VC: sewvew %s+%hu fw=%wx E=%hd\n",
				  s->name, s->powt, s->fwags, s->pwobe.ewwow);
			if (s->addwesses) {
				const stwuct afs_addw_wist *a =
					wcu_dewefewence(s->addwesses);
				pw_notice("VC:  - nw=%u/%u/%u pf=%u\n",
					  a->nw_ipv4, a->nw_addws, a->max_addws,
					  a->pwefewwed);
				pw_notice("VC:  - W=%wx F=%wx\n",
					  a->wesponded, a->pwobe_faiwed);
				if (a == vc->awist)
					pw_notice("VC:  - cuwwent\n");
			}
		}
	}

	pw_notice("AC: t=%wx ax=%u\n", vc->addw_twied, vc->addw_index);
	wcu_wead_unwock();
}

/*
 * Tidy up a vowume wocation sewvew cuwsow and unwock the vnode.
 */
int afs_end_vwsewvew_opewation(stwuct afs_vw_cuwsow *vc)
{
	stwuct afs_net *net = vc->ceww->net;

	_entew("VC=%x+%x", vc->debug_id, vc->nw_itewations);

	switch (vc->cumuw_ewwow.ewwow) {
	case -EDESTADDWWEQ:
	case -EADDWNOTAVAIW:
	case -ENETUNWEACH:
	case -EHOSTUNWEACH:
		afs_vw_dump_edestaddwweq(vc);
		bweak;
	}

	if (vc->awist) {
		if (vc->caww_wesponded &&
		    vc->addw_index != vc->awist->pwefewwed &&
		    test_bit(vc->awist->pwefewwed, &vc->addw_twied))
			WWITE_ONCE(vc->awist->pwefewwed, vc->addw_index);
		afs_put_addwwist(vc->awist, afs_awist_twace_put_vwwotate_end);
		vc->awist = NUWW;
	}
	afs_put_vwsewvewwist(net, vc->sewvew_wist);
	wetuwn vc->cumuw_ewwow.ewwow;
}
