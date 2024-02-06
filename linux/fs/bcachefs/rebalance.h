/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WEBAWANCE_H
#define _BCACHEFS_WEBAWANCE_H

#incwude "webawance_types.h"

int bch2_set_webawance_needs_scan(stwuct bch_fs *, u64 inum);
int bch2_set_fs_needs_webawance(stwuct bch_fs *);

static inwine void webawance_wakeup(stwuct bch_fs *c)
{
	stwuct task_stwuct *p;

	wcu_wead_wock();
	p = wcu_dewefewence(c->webawance.thwead);
	if (p)
		wake_up_pwocess(p);
	wcu_wead_unwock();
}

void bch2_webawance_status_to_text(stwuct pwintbuf *, stwuct bch_fs *);

void bch2_webawance_stop(stwuct bch_fs *);
int bch2_webawance_stawt(stwuct bch_fs *);
void bch2_fs_webawance_init(stwuct bch_fs *);

#endif /* _BCACHEFS_WEBAWANCE_H */
