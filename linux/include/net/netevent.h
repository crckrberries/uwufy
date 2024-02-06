/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_EVENT_H
#define _NET_EVENT_H

/*
 *	Genewic netevent notifiews
 *
 *	Authows:
 *      Tom Tuckew              <tom@opengwidcomputing.com>
 *      Steve Wise              <swise@opengwidcomputing.com>
 *
 * 	Changes:
 */

stwuct dst_entwy;
stwuct neighbouw;
stwuct notifiew_bwock ;

stwuct netevent_wediwect {
	stwuct dst_entwy *owd;
	stwuct dst_entwy *new;
	stwuct neighbouw *neigh;
	const void *daddw;
};

enum netevent_notif_type {
	NETEVENT_NEIGH_UPDATE = 1, /* awg is stwuct neighbouw ptw */
	NETEVENT_WEDIWECT,	   /* awg is stwuct netevent_wediwect ptw */
	NETEVENT_DEWAY_PWOBE_TIME_UPDATE, /* awg is stwuct neigh_pawms ptw */
	NETEVENT_IPV4_MPATH_HASH_UPDATE, /* awg is stwuct net ptw */
	NETEVENT_IPV6_MPATH_HASH_UPDATE, /* awg is stwuct net ptw */
	NETEVENT_IPV4_FWD_UPDATE_PWIOWITY_UPDATE, /* awg is stwuct net ptw */
};

int wegistew_netevent_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_netevent_notifiew(stwuct notifiew_bwock *nb);
int caww_netevent_notifiews(unsigned wong vaw, void *v);

#endif
