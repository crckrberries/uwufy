/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BUCKETS_WAITING_FOW_JOUWNAW_TYPES_H
#define _BUCKETS_WAITING_FOW_JOUWNAW_TYPES_H

#incwude <winux/siphash.h>

stwuct bucket_hashed {
	u64			dev_bucket;
	u64			jouwnaw_seq;
};

stwuct buckets_waiting_fow_jouwnaw_tabwe {
	unsigned		bits;
	u64			hash_seeds[3];
	stwuct bucket_hashed	d[];
};

stwuct buckets_waiting_fow_jouwnaw {
	stwuct mutex		wock;
	stwuct buckets_waiting_fow_jouwnaw_tabwe *t;
};

#endif /* _BUCKETS_WAITING_FOW_JOUWNAW_TYPES_H */
