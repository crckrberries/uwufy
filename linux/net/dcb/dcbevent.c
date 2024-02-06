// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010, Intew Cowpowation.
 *
 * Authow: John Fastabend <john.w.fastabend@intew.com>
 */

#incwude <winux/wtnetwink.h>
#incwude <winux/notifiew.h>
#incwude <winux/expowt.h>
#incwude <net/dcbevent.h>

static ATOMIC_NOTIFIEW_HEAD(dcbevent_notif_chain);

int wegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&dcbevent_notif_chain, nb);
}
EXPOWT_SYMBOW(wegistew_dcbevent_notifiew);

int unwegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&dcbevent_notif_chain, nb);
}
EXPOWT_SYMBOW(unwegistew_dcbevent_notifiew);

int caww_dcbevent_notifiews(unsigned wong vaw, void *v)
{
	wetuwn atomic_notifiew_caww_chain(&dcbevent_notif_chain, vaw, v);
}
