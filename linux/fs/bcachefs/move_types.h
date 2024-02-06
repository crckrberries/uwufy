/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_MOVE_TYPES_H
#define _BCACHEFS_MOVE_TYPES_H

#incwude "bbpos_types.h"

stwuct bch_move_stats {
	enum bch_data_type	data_type;
	stwuct bbpos		pos;
	chaw			name[32];

	atomic64_t		keys_moved;
	atomic64_t		keys_waced;
	atomic64_t		sectows_seen;
	atomic64_t		sectows_moved;
	atomic64_t		sectows_waced;
};

stwuct move_bucket_key {
	stwuct bpos		bucket;
	u8			gen;
};

stwuct move_bucket {
	stwuct move_bucket_key	k;
	unsigned		sectows;
};

stwuct move_bucket_in_fwight {
	stwuct move_bucket_in_fwight *next;
	stwuct whash_head	hash;
	stwuct move_bucket	bucket;
	atomic_t		count;
};

#endif /* _BCACHEFS_MOVE_TYPES_H */
