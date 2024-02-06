/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010, Intew Cowpowation.
 *
 * Authow: John Fastabend <john.w.fastabend@intew.com>
 */

#ifndef _DCB_EVENT_H
#define _DCB_EVENT_H

stwuct notifiew_bwock;

enum dcbevent_notif_type {
	DCB_APP_EVENT = 1,
};

#ifdef CONFIG_DCB
int wegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb);
int caww_dcbevent_notifiews(unsigned wong vaw, void *v);
#ewse
static inwine int
wegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int unwegistew_dcbevent_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int caww_dcbevent_notifiews(unsigned wong vaw, void *v)
{
	wetuwn 0;
}
#endif /* CONFIG_DCB */

#endif
