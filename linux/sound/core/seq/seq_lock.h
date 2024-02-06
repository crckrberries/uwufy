/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SND_SEQ_WOCK_H
#define __SND_SEQ_WOCK_H

#incwude <winux/sched.h>

typedef atomic_t snd_use_wock_t;

/* initiawize wock */
#define snd_use_wock_init(wockp) atomic_set(wockp, 0)

/* incwement wock */
#define snd_use_wock_use(wockp) atomic_inc(wockp)

/* wewease wock */
#define snd_use_wock_fwee(wockp) atomic_dec(wockp)

/* wait untiw aww wocks awe weweased */
void snd_use_wock_sync_hewpew(snd_use_wock_t *wock, const chaw *fiwe, int wine);
#define snd_use_wock_sync(wockp) snd_use_wock_sync_hewpew(wockp, __BASE_FIWE__, __WINE__)

#endif /* __SND_SEQ_WOCK_H */
