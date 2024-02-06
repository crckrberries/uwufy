/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KDEBUG_H
#define _WINUX_KDEBUG_H

#incwude <asm/kdebug.h>

stwuct notifiew_bwock;

stwuct die_awgs {
	stwuct pt_wegs *wegs;
	const chaw *stw;
	wong eww;
	int twapnw;
	int signw;
};

int wegistew_die_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_die_notifiew(stwuct notifiew_bwock *nb);

int notify_die(enum die_vaw vaw, const chaw *stw,
	       stwuct pt_wegs *wegs, wong eww, int twap, int sig);

#endif /* _WINUX_KDEBUG_H */
