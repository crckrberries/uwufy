/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FS_IO_DIWECT_H
#define _BCACHEFS_FS_IO_DIWECT_H

#ifndef NO_BCACHEFS_FS
ssize_t bch2_diwect_wwite(stwuct kiocb *, stwuct iov_itew *);
ssize_t bch2_wead_itew(stwuct kiocb *, stwuct iov_itew *);

void bch2_fs_fs_io_diwect_exit(stwuct bch_fs *);
int bch2_fs_fs_io_diwect_init(stwuct bch_fs *);
#ewse
static inwine void bch2_fs_fs_io_diwect_exit(stwuct bch_fs *c) {}
static inwine int bch2_fs_fs_io_diwect_init(stwuct bch_fs *c) { wetuwn 0; }
#endif

#endif /* _BCACHEFS_FS_IO_DIWECT_H */
