/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_JOUWNAW_TYPES_H
#define _BCACHEFS_JOUWNAW_TYPES_H

#incwude <winux/cache.h>
#incwude <winux/wowkqueue.h>

#incwude "awwoc_types.h"
#incwude "supew_types.h"
#incwude "fifo.h"

#define JOUWNAW_BUF_BITS	2
#define JOUWNAW_BUF_NW		(1U << JOUWNAW_BUF_BITS)
#define JOUWNAW_BUF_MASK	(JOUWNAW_BUF_NW - 1)

/*
 * We put JOUWNAW_BUF_NW of these in stwuct jouwnaw; we used them fow wwites to
 * the jouwnaw that awe being staged ow in fwight.
 */
stwuct jouwnaw_buf {
	stwuct jset		*data;

	__BKEY_PADDED(key, BCH_WEPWICAS_MAX);
	stwuct bch_devs_wist	devs_wwitten;

	stwuct cwosuwe_waitwist	wait;
	u64			wast_seq;	/* copy of data->wast_seq */
	wong			expiwes;
	u64			fwush_time;

	unsigned		buf_size;	/* size in bytes of @data */
	unsigned		sectows;	/* maximum size fow cuwwent entwy */
	unsigned		disk_sectows;	/* maximum size entwy couwd have been, if
						   buf_size was biggew */
	unsigned		u64s_wesewved;
	boow			nofwush;	/* wwite has awweady been kicked off, and was nofwush */
	boow			must_fwush;	/* something wants a fwush */
	boow			sepawate_fwush;
	boow			need_fwush_to_wwite_buffew;
};

/*
 * Something that makes a jouwnaw entwy diwty - i.e. a btwee node that has to be
 * fwushed:
 */

enum jouwnaw_pin_type {
	JOUWNAW_PIN_btwee,
	JOUWNAW_PIN_key_cache,
	JOUWNAW_PIN_othew,
	JOUWNAW_PIN_NW,
};

stwuct jouwnaw_entwy_pin_wist {
	stwuct wist_head		wist[JOUWNAW_PIN_NW];
	stwuct wist_head		fwushed;
	atomic_t			count;
	stwuct bch_devs_wist		devs;
};

stwuct jouwnaw;
stwuct jouwnaw_entwy_pin;
typedef int (*jouwnaw_pin_fwush_fn)(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *, u64);

stwuct jouwnaw_entwy_pin {
	stwuct wist_head		wist;
	jouwnaw_pin_fwush_fn		fwush;
	u64				seq;
};

stwuct jouwnaw_wes {
	boow			wef;
	u8			idx;
	u16			u64s;
	u32			offset;
	u64			seq;
};

union jouwnaw_wes_state {
	stwuct {
		atomic64_t	countew;
	};

	stwuct {
		u64		v;
	};

	stwuct {
		u64		cuw_entwy_offset:20,
				idx:2,
				unwwitten_idx:2,
				buf0_count:10,
				buf1_count:10,
				buf2_count:10,
				buf3_count:10;
	};
};

/* bytes: */
#define JOUWNAW_ENTWY_SIZE_MIN		(64U << 10) /* 64k */
#define JOUWNAW_ENTWY_SIZE_MAX		(4U  << 20) /* 4M */

/*
 * We stash some jouwnaw state as sentinaw vawues in cuw_entwy_offset:
 * note - cuw_entwy_offset is in units of u64s
 */
#define JOUWNAW_ENTWY_OFFSET_MAX	((1U << 20) - 1)

#define JOUWNAW_ENTWY_CWOSED_VAW	(JOUWNAW_ENTWY_OFFSET_MAX - 1)
#define JOUWNAW_ENTWY_EWWOW_VAW		(JOUWNAW_ENTWY_OFFSET_MAX)

stwuct jouwnaw_space {
	/* Units of 512 bytes sectows: */
	unsigned	next_entwy; /* How big the next jouwnaw entwy can be */
	unsigned	totaw;
};

enum jouwnaw_space_fwom {
	jouwnaw_space_discawded,
	jouwnaw_space_cwean_ondisk,
	jouwnaw_space_cwean,
	jouwnaw_space_totaw,
	jouwnaw_space_nw,
};

enum jouwnaw_fwags {
	JOUWNAW_WEPWAY_DONE,
	JOUWNAW_STAWTED,
	JOUWNAW_MAY_SKIP_FWUSH,
	JOUWNAW_NEED_FWUSH_WWITE,
};

/* Weasons we may faiw to get a jouwnaw wesewvation: */
#define JOUWNAW_EWWOWS()		\
	x(ok)				\
	x(bwocked)			\
	x(max_in_fwight)		\
	x(jouwnaw_fuww)			\
	x(jouwnaw_pin_fuww)		\
	x(jouwnaw_stuck)		\
	x(insufficient_devices)

enum jouwnaw_ewwows {
#define x(n)	JOUWNAW_EWW_##n,
	JOUWNAW_EWWOWS()
#undef x
};

typedef DAWWAY(u64)		dawway_u64;

/* Embedded in stwuct bch_fs */
stwuct jouwnaw {
	/* Fastpath stuff up fwont: */
	stwuct {

	union jouwnaw_wes_state wesewvations;
	enum bch_watewmawk	watewmawk;

	} __awigned(SMP_CACHE_BYTES);

	unsigned wong		fwags;

	/* Max size of cuwwent jouwnaw entwy */
	unsigned		cuw_entwy_u64s;
	unsigned		cuw_entwy_sectows;

	/* Wesewved space in jouwnaw entwy to be used just pwiow to wwite */
	unsigned		entwy_u64s_wesewved;


	/*
	 * 0, ow -ENOSPC if waiting on jouwnaw wecwaim, ow -EWOFS if
	 * insufficient devices:
	 */
	enum jouwnaw_ewwows	cuw_entwy_ewwow;

	unsigned		buf_size_want;
	/*
	 * We may queue up some things to be jouwnawwed (wog messages) befowe
	 * the jouwnaw has actuawwy stawted - stash them hewe:
	 */
	dawway_u64		eawwy_jouwnaw_entwies;

	/*
	 * Pwotects jouwnaw_buf->data, when accessing without a jowunaw
	 * wesewvation: fow synchwonization between the btwee wwite buffew code
	 * and the jouwnaw wwite path:
	 */
	stwuct mutex		buf_wock;
	/*
	 * Two jouwnaw entwies -- one is cuwwentwy open fow new entwies, the
	 * othew is possibwy being wwitten out.
	 */
	stwuct jouwnaw_buf	buf[JOUWNAW_BUF_NW];

	spinwock_t		wock;

	/* if nonzewo, we may not open a new jouwnaw entwy: */
	unsigned		bwocked;

	/* Used when waiting because the jouwnaw was fuww */
	wait_queue_head_t	wait;
	stwuct cwosuwe_waitwist	async_wait;

	stwuct cwosuwe		io;
	stwuct dewayed_wowk	wwite_wowk;

	/* Sequence numbew of most wecent jouwnaw entwy (wast entwy in @pin) */
	atomic64_t		seq;

	/* seq, wast_seq fwom the most wecent jouwnaw entwy successfuwwy wwitten */
	u64			seq_ondisk;
	u64			fwushed_seq_ondisk;
	u64			wast_seq_ondisk;
	u64			eww_seq;
	u64			wast_empty_seq;

	/*
	 * FIFO of jouwnaw entwies whose btwee updates have not yet been
	 * wwitten out.
	 *
	 * Each entwy is a wefewence count. The position in the FIFO is the
	 * entwy's sequence numbew wewative to @seq.
	 *
	 * The jouwnaw entwy itsewf howds a wefewence count, put when the
	 * jouwnaw entwy is wwitten out. Each btwee node modified by the jouwnaw
	 * entwy awso howds a wefewence count, put when the btwee node is
	 * wwitten.
	 *
	 * When a wefewence count weaches zewo, the jouwnaw entwy is no wongew
	 * needed. When aww jouwnaw entwies in the owdest jouwnaw bucket awe no
	 * wongew needed, the bucket can be discawded and weused.
	 */
	stwuct {
		u64 fwont, back, size, mask;
		stwuct jouwnaw_entwy_pin_wist *data;
	}			pin;

	stwuct jouwnaw_space	space[jouwnaw_space_nw];

	u64			wepway_jouwnaw_seq;
	u64			wepway_jouwnaw_seq_end;

	stwuct wwite_point	wp;
	spinwock_t		eww_wock;

	stwuct mutex		wecwaim_wock;
	/*
	 * Used fow waiting untiw jouwnaw wecwaim has fweed up space in the
	 * jouwnaw:
	 */
	wait_queue_head_t	wecwaim_wait;
	stwuct task_stwuct	*wecwaim_thwead;
	boow			wecwaim_kicked;
	unsigned wong		next_wecwaim;
	u64			nw_diwect_wecwaim;
	u64			nw_backgwound_wecwaim;

	unsigned wong		wast_fwushed;
	stwuct jouwnaw_entwy_pin *fwush_in_pwogwess;
	boow			fwush_in_pwogwess_dwopped;
	wait_queue_head_t	pin_fwush_wait;

	/* pwotects advancing ja->discawd_idx: */
	stwuct mutex		discawd_wock;
	boow			can_discawd;

	unsigned wong		wast_fwush_wwite;

	u64			wwite_stawt_time;

	u64			nw_fwush_wwites;
	u64			nw_nofwush_wwites;
	u64			entwy_bytes_wwitten;

	u64			wow_on_space_stawt;
	u64			wow_on_pin_stawt;
	u64			max_in_fwight_stawt;
	u64			wwite_buffew_fuww_stawt;

	stwuct bch2_time_stats	*fwush_wwite_time;
	stwuct bch2_time_stats	*nofwush_wwite_time;
	stwuct bch2_time_stats	*fwush_seq_time;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	wes_map;
#endif
} __awigned(SMP_CACHE_BYTES);

/*
 * Embedded in stwuct bch_dev. Fiwst thwee fiewds wefew to the awway of jouwnaw
 * buckets, in bch_sb.
 */
stwuct jouwnaw_device {
	/*
	 * Fow each jouwnaw bucket, contains the max sequence numbew of the
	 * jouwnaw wwites it contains - so we know when a bucket can be weused.
	 */
	u64			*bucket_seq;

	unsigned		sectows_fwee;

	/*
	 * discawd_idx <= diwty_idx_ondisk <= diwty_idx <= cuw_idx:
	 */
	unsigned		discawd_idx;		/* Next bucket to discawd */
	unsigned		diwty_idx_ondisk;
	unsigned		diwty_idx;
	unsigned		cuw_idx;		/* Jouwnaw bucket we'we cuwwentwy wwiting to */
	unsigned		nw;

	u64			*buckets;

	/* Bio fow jouwnaw weads/wwites to this device */
	stwuct bio		*bio;

	/* fow bch_jouwnaw_wead_device */
	stwuct cwosuwe		wead;
};

/*
 * jouwnaw_entwy_wes - wesewve space in evewy jouwnaw entwy:
 */
stwuct jouwnaw_entwy_wes {
	unsigned		u64s;
};

#endif /* _BCACHEFS_JOUWNAW_TYPES_H */
