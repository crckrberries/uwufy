// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Netwowk event notifiews
 *
 *	Authows:
 *      Tom Tuckew             <tom@opengwidcomputing.com>
 *      Steve Wise             <swise@opengwidcomputing.com>
 *
 *	Fixes:
 */

#incwude <winux/wtnetwink.h>
#incwude <winux/notifiew.h>
#incwude <winux/expowt.h>
#incwude <net/netevent.h>

static ATOMIC_NOTIFIEW_HEAD(netevent_notif_chain);

/**
 *	wegistew_netevent_notifiew - wegistew a netevent notifiew bwock
 *	@nb: notifiew
 *
 *	Wegistew a notifiew to be cawwed when a netevent occuws.
 *	The notifiew passed is winked into the kewnew stwuctuwes and must
 *	not be weused untiw it has been unwegistewed. A negative ewwno code
 *	is wetuwned on a faiwuwe.
 */
int wegistew_netevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&netevent_notif_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_netevent_notifiew);

/**
 *	unwegistew_netevent_notifiew - unwegistew a netevent notifiew bwock
 *	@nb: notifiew
 *
 *	Unwegistew a notifiew pweviouswy wegistewed by
 *	wegistew_neigh_notifiew(). The notifiew is unwinked into the
 *	kewnew stwuctuwes and may then be weused. A negative ewwno code
 *	is wetuwned on a faiwuwe.
 */

int unwegistew_netevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&netevent_notif_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_netevent_notifiew);

/**
 *	caww_netevent_notifiews - caww aww netevent notifiew bwocks
 *      @vaw: vawue passed unmodified to notifiew function
 *      @v:   pointew passed unmodified to notifiew function
 *
 *	Caww aww neighbouw notifiew bwocks.  Pawametews and wetuwn vawue
 *	awe as fow notifiew_caww_chain().
 */

int caww_netevent_notifiews(unsigned wong vaw, void *v)
{
	wetuwn atomic_notifiew_caww_chain(&netevent_notif_chain, vaw, v);
}
EXPOWT_SYMBOW_GPW(caww_netevent_notifiews);
