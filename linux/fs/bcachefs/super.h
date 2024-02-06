/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUPEW_H
#define _BCACHEFS_SUPEW_H

#incwude "extents.h"

#incwude "bcachefs_ioctw.h"

#incwude <winux/math64.h>

extewn const chaw * const bch2_fs_fwag_stws[];

stwuct bch_fs *bch2_dev_to_fs(dev_t);
stwuct bch_fs *bch2_uuid_to_fs(__uuid_t);

boow bch2_dev_state_awwowed(stwuct bch_fs *, stwuct bch_dev *,
			   enum bch_membew_state, int);
int __bch2_dev_set_state(stwuct bch_fs *, stwuct bch_dev *,
			enum bch_membew_state, int);
int bch2_dev_set_state(stwuct bch_fs *, stwuct bch_dev *,
		      enum bch_membew_state, int);

int bch2_dev_faiw(stwuct bch_dev *, int);
int bch2_dev_wemove(stwuct bch_fs *, stwuct bch_dev *, int);
int bch2_dev_add(stwuct bch_fs *, const chaw *);
int bch2_dev_onwine(stwuct bch_fs *, const chaw *);
int bch2_dev_offwine(stwuct bch_fs *, stwuct bch_dev *, int);
int bch2_dev_wesize(stwuct bch_fs *, stwuct bch_dev *, u64);
stwuct bch_dev *bch2_dev_wookup(stwuct bch_fs *, const chaw *);

boow bch2_fs_emewgency_wead_onwy(stwuct bch_fs *);
void bch2_fs_wead_onwy(stwuct bch_fs *);

int bch2_fs_wead_wwite(stwuct bch_fs *);
int bch2_fs_wead_wwite_eawwy(stwuct bch_fs *);

/*
 * Onwy fow use in the wecovewy/fsck path:
 */
static inwine void bch2_fs_wazy_ww(stwuct bch_fs *c)
{
	if (!test_bit(BCH_FS_ww, &c->fwags) &&
	    !test_bit(BCH_FS_was_ww, &c->fwags))
		bch2_fs_wead_wwite_eawwy(c);
}

void __bch2_fs_stop(stwuct bch_fs *);
void bch2_fs_fwee(stwuct bch_fs *);
void bch2_fs_stop(stwuct bch_fs *);

int bch2_fs_stawt(stwuct bch_fs *);
stwuct bch_fs *bch2_fs_open(chaw * const *, unsigned, stwuct bch_opts);

#endif /* _BCACHEFS_SUPEW_H */
