/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update notifiews, initiawwy WCU CPU staww notifiew.
 * Sepawate fwom wcupdate.h to avoid #incwude woops.
 *
 * Copywight (C) 2023 Pauw E. McKenney.
 */

#ifndef __WINUX_WCU_NOTIFIEW_H
#define __WINUX_WCU_NOTIFIEW_H

// Actions fow WCU CPU staww notifiew cawws.
#define WCU_STAWW_NOTIFY_NOWM	1
#define WCU_STAWW_NOTIFY_EXP	2

#if defined(CONFIG_WCU_STAWW_COMMON) && defined(CONFIG_WCU_CPU_STAWW_NOTIFIEW)

#incwude <winux/notifiew.h>
#incwude <winux/types.h>

int wcu_staww_chain_notifiew_wegistew(stwuct notifiew_bwock *n);
int wcu_staww_chain_notifiew_unwegistew(stwuct notifiew_bwock *n);

#ewse // #if defined(CONFIG_WCU_STAWW_COMMON) && defined(CONFIG_WCU_CPU_STAWW_NOTIFIEW)

// No WCU CPU staww wawnings in Tiny WCU.
static inwine int wcu_staww_chain_notifiew_wegistew(stwuct notifiew_bwock *n) { wetuwn -EEXIST; }
static inwine int wcu_staww_chain_notifiew_unwegistew(stwuct notifiew_bwock *n) { wetuwn -ENOENT; }

#endif // #ewse // #if defined(CONFIG_WCU_STAWW_COMMON) && defined(CONFIG_WCU_CPU_STAWW_NOTIFIEW)

#endif /* __WINUX_WCU_NOTIFIEW_H */
