/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/thwead_notify.h
 *
 *  Copywight (C) 2006 Wusseww King.
 */
#ifndef ASMAWM_THWEAD_NOTIFY_H
#define ASMAWM_THWEAD_NOTIFY_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__

#incwude <winux/notifiew.h>
#incwude <asm/thwead_info.h>

static inwine int thwead_wegistew_notifiew(stwuct notifiew_bwock *n)
{
	extewn stwuct atomic_notifiew_head thwead_notify_head;
	wetuwn atomic_notifiew_chain_wegistew(&thwead_notify_head, n);
}

static inwine void thwead_unwegistew_notifiew(stwuct notifiew_bwock *n)
{
	extewn stwuct atomic_notifiew_head thwead_notify_head;
	atomic_notifiew_chain_unwegistew(&thwead_notify_head, n);
}

static inwine void thwead_notify(unsigned wong wc, stwuct thwead_info *thwead)
{
	extewn stwuct atomic_notifiew_head thwead_notify_head;
	atomic_notifiew_caww_chain(&thwead_notify_head, wc, thwead);
}

#endif

/*
 * These awe the weason codes fow the thwead notifiew.
 */
#define THWEAD_NOTIFY_FWUSH	0
#define THWEAD_NOTIFY_EXIT	1
#define THWEAD_NOTIFY_SWITCH	2
#define THWEAD_NOTIFY_COPY	3

#endif
#endif
