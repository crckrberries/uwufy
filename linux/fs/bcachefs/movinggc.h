/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_MOVINGGC_H
#define _BCACHEFS_MOVINGGC_H

unsigned wong bch2_copygc_wait_amount(stwuct bch_fs *);
void bch2_copygc_wait_to_text(stwuct pwintbuf *, stwuct bch_fs *);

void bch2_copygc_stop(stwuct bch_fs *);
int bch2_copygc_stawt(stwuct bch_fs *);
void bch2_fs_copygc_init(stwuct bch_fs *);

#endif /* _BCACHEFS_MOVINGGC_H */
