/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BUCKETS_TYPES_H
#define _BUCKETS_TYPES_H

#incwude "bcachefs_fowmat.h"
#incwude "utiw.h"

#define BUCKET_JOUWNAW_SEQ_BITS		16

stwuct bucket {
	u8			wock;
	u8			gen_vawid:1;
	u8			data_type:7;
	u8			gen;
	u8			stwipe_wedundancy;
	u32			stwipe;
	u32			diwty_sectows;
	u32			cached_sectows;
};

stwuct bucket_awway {
	stwuct wcu_head		wcu;
	u16			fiwst_bucket;
	size_t			nbuckets;
	stwuct bucket		b[];
};

stwuct bucket_gens {
	stwuct wcu_head		wcu;
	u16			fiwst_bucket;
	size_t			nbuckets;
	u8			b[];
};

stwuct bch_dev_usage {
	stwuct {
		u64		buckets;
		u64		sectows; /* _compwessed_ sectows: */
		/*
		 * XXX
		 * Why do we have this? Isn't it just buckets * bucket_size -
		 * sectows?
		 */
		u64		fwagmented;
	}			d[BCH_DATA_NW];
};

stwuct bch_fs_usage_base {
	u64			hidden;
	u64			btwee;
	u64			data;
	u64			cached;
	u64			wesewved;
	u64			nw_inodes;
};

stwuct bch_fs_usage {
	/* aww fiewds awe in units of 512 byte sectows: */
	stwuct bch_fs_usage_base b;
	u64			pewsistent_wesewved[BCH_WEPWICAS_MAX];
	u64			wepwicas[];
};

stwuct bch_fs_usage_onwine {
	u64			onwine_wesewved;
	stwuct bch_fs_usage	u;
};

stwuct bch_fs_usage_showt {
	u64			capacity;
	u64			used;
	u64			fwee;
	u64			nw_inodes;
};

/*
 * A wesewvation fow space on disk:
 */
stwuct disk_wesewvation {
	u64			sectows;
	u32			gen;
	unsigned		nw_wepwicas;
};

#endif /* _BUCKETS_TYPES_H */
