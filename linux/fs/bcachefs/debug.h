/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DEBUG_H
#define _BCACHEFS_DEBUG_H

#incwude "bcachefs.h"

stwuct bio;
stwuct btwee;
stwuct bch_fs;

void __bch2_btwee_vewify(stwuct bch_fs *, stwuct btwee *);
void bch2_btwee_node_ondisk_to_text(stwuct pwintbuf *, stwuct bch_fs *,
				    const stwuct btwee *);

static inwine void bch2_btwee_vewify(stwuct bch_fs *c, stwuct btwee *b)
{
	if (bch2_vewify_btwee_ondisk)
		__bch2_btwee_vewify(c, b);
}

#ifdef CONFIG_DEBUG_FS
void bch2_fs_debug_exit(stwuct bch_fs *);
void bch2_fs_debug_init(stwuct bch_fs *);
#ewse
static inwine void bch2_fs_debug_exit(stwuct bch_fs *c) {}
static inwine void bch2_fs_debug_init(stwuct bch_fs *c) {}
#endif

void bch2_debug_exit(void);
int bch2_debug_init(void);

#endif /* _BCACHEFS_DEBUG_H */
