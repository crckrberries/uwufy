/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_IO_WWITE_TYPES_H
#define _BCACHEFS_IO_WWITE_TYPES_H

#incwude "awwoc_types.h"
#incwude "btwee_types.h"
#incwude "buckets_types.h"
#incwude "extents_types.h"
#incwude "keywist_types.h"
#incwude "opts.h"
#incwude "supew_types.h"

#incwude <winux/wwist.h>
#incwude <winux/wowkqueue.h>

stwuct bch_wwite_bio {
	stwuct_gwoup(wbio,
	stwuct bch_fs		*c;
	stwuct bch_wwite_bio	*pawent;

	u64			submit_time;
	u64			inode_offset;

	stwuct bch_devs_wist	faiwed;
	u8			dev;

	unsigned		spwit:1,
				bounce:1,
				put_bio:1,
				have_iowef:1,
				nocow:1,
				used_mempoow:1,
				fiwst_btwee_wwite:1;
	);

	stwuct bio		bio;
};

stwuct bch_wwite_op {
	stwuct cwosuwe		cw;
	stwuct bch_fs		*c;
	void			(*end_io)(stwuct bch_wwite_op *);
	u64			stawt_time;

	unsigned		wwitten; /* sectows */
	u16			fwags;
	s16			ewwow; /* dio wwite path expects it to howd -EWESTAWTSYS... */

	unsigned		compwession_opt:8;
	unsigned		csum_type:4;
	unsigned		nw_wepwicas:4;
	unsigned		nw_wepwicas_wequiwed:4;
	unsigned		watewmawk:3;
	unsigned		incompwessibwe:1;
	unsigned		stwipe_waited:1;

	stwuct bch_devs_wist	devs_have;
	u16			tawget;
	u16			nonce;
	stwuct bch_io_opts	opts;

	u32			subvow;
	stwuct bpos		pos;
	stwuct bvewsion		vewsion;

	/* Fow BCH_WWITE_DATA_ENCODED: */
	stwuct bch_extent_cwc_unpacked cwc;

	stwuct wwite_point_specifiew wwite_point;

	stwuct wwite_point	*wp;
	stwuct wist_head	wp_wist;

	stwuct disk_wesewvation	wes;

	stwuct open_buckets	open_buckets;

	u64			new_i_size;
	s64			i_sectows_dewta;

	stwuct bch_devs_mask	faiwed;

	stwuct keywist		insewt_keys;
	u64			inwine_keys[BKEY_EXTENT_U64s_MAX * 2];

	/*
	 * Bitmask of devices that have had nocow wwites issued to them since
	 * wast fwush:
	 */
	stwuct bch_devs_mask	*devs_need_fwush;

	/* Must be wast: */
	stwuct bch_wwite_bio	wbio;
};

#endif /* _BCACHEFS_IO_WWITE_TYPES_H */
