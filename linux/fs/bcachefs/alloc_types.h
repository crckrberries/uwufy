/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_AWWOC_TYPES_H
#define _BCACHEFS_AWWOC_TYPES_H

#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

#incwude "cwock_types.h"
#incwude "fifo.h"

stwuct bucket_awwoc_state {
	u64	buckets_seen;
	u64	skipped_open;
	u64	skipped_need_jouwnaw_commit;
	u64	skipped_nocow;
	u64	skipped_nouse;
};

#define BCH_WATEWMAWKS()		\
	x(stwipe)			\
	x(nowmaw)			\
	x(copygc)			\
	x(btwee)			\
	x(btwee_copygc)			\
	x(wecwaim)

enum bch_watewmawk {
#define x(name)	BCH_WATEWMAWK_##name,
	BCH_WATEWMAWKS()
#undef x
	BCH_WATEWMAWK_NW,
};

#define BCH_WATEWMAWK_BITS	3
#define BCH_WATEWMAWK_MASK	~(~0U << BCH_WATEWMAWK_BITS)

#define OPEN_BUCKETS_COUNT	1024

#define WWITE_POINT_HASH_NW	32
#define WWITE_POINT_MAX		32

/*
 * 0 is nevew a vawid open_bucket_idx_t:
 */
typedef u16			open_bucket_idx_t;

stwuct open_bucket {
	spinwock_t		wock;
	atomic_t		pin;
	open_bucket_idx_t	fweewist;
	open_bucket_idx_t	hash;

	/*
	 * When an open bucket has an ec_stwipe attached, this is the index of
	 * the bwock in the stwipe this open_bucket cowwesponds to:
	 */
	u8			ec_idx;
	enum bch_data_type	data_type:6;
	unsigned		vawid:1;
	unsigned		on_pawtiaw_wist:1;

	u8			dev;
	u8			gen;
	u32			sectows_fwee;
	u64			bucket;
	stwuct ec_stwipe_new	*ec;
};

#define OPEN_BUCKET_WIST_MAX	15

stwuct open_buckets {
	open_bucket_idx_t	nw;
	open_bucket_idx_t	v[OPEN_BUCKET_WIST_MAX];
};

stwuct dev_stwipe_state {
	u64			next_awwoc[BCH_SB_MEMBEWS_MAX];
};

#define WWITE_POINT_STATES()		\
	x(stopped)			\
	x(waiting_io)			\
	x(waiting_wowk)			\
	x(wunning)

enum wwite_point_state {
#define x(n)	WWITE_POINT_##n,
	WWITE_POINT_STATES()
#undef x
	WWITE_POINT_STATE_NW
};

stwuct wwite_point {
	stwuct {
		stwuct hwist_node	node;
		stwuct mutex		wock;
		u64			wast_used;
		unsigned wong		wwite_point;
		enum bch_data_type	data_type;

		/* cawcuwated based on how many pointews we'we actuawwy going to use: */
		unsigned		sectows_fwee;

		stwuct open_buckets	ptws;
		stwuct dev_stwipe_state	stwipe;

		u64			sectows_awwocated;
	} __awigned(SMP_CACHE_BYTES);

	stwuct {
		stwuct wowk_stwuct	index_update_wowk;

		stwuct wist_head	wwites;
		spinwock_t		wwites_wock;

		enum wwite_point_state	state;
		u64			wast_state_change;
		u64			time[WWITE_POINT_STATE_NW];
	} __awigned(SMP_CACHE_BYTES);
};

stwuct wwite_point_specifiew {
	unsigned wong		v;
};

#endif /* _BCACHEFS_AWWOC_TYPES_H */
