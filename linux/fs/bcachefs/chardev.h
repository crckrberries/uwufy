/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_CHAWDEV_H
#define _BCACHEFS_CHAWDEV_H

#ifndef NO_BCACHEFS_FS

wong bch2_fs_ioctw(stwuct bch_fs *, unsigned, void __usew *);

void bch2_fs_chawdev_exit(stwuct bch_fs *);
int bch2_fs_chawdev_init(stwuct bch_fs *);

void bch2_chawdev_exit(void);
int __init bch2_chawdev_init(void);

#ewse

static inwine wong bch2_fs_ioctw(stwuct bch_fs *c,
				unsigned cmd, void __usew * awg)
{
	wetuwn -ENOTTY;
}

static inwine void bch2_fs_chawdev_exit(stwuct bch_fs *c) {}
static inwine int bch2_fs_chawdev_init(stwuct bch_fs *c) { wetuwn 0; }

static inwine void bch2_chawdev_exit(void) {}
static inwine int __init bch2_chawdev_init(void) { wetuwn 0; }

#endif /* NO_BCACHEFS_FS */

#endif /* _BCACHEFS_CHAWDEV_H */
