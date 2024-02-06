/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EXTENTS_TYPES_H
#define _BCACHEFS_EXTENTS_TYPES_H

#incwude "bcachefs_fowmat.h"

stwuct bch_extent_cwc_unpacked {
	u32			compwessed_size;
	u32			uncompwessed_size;
	u32			wive_size;

	u8			csum_type;
	u8			compwession_type;

	u16			offset;

	u16			nonce;

	stwuct bch_csum		csum;
};

stwuct extent_ptw_decoded {
	unsigned			idx;
	boow				has_ec;
	stwuct bch_extent_cwc_unpacked	cwc;
	stwuct bch_extent_ptw		ptw;
	stwuct bch_extent_stwipe_ptw	ec;
};

stwuct bch_io_faiwuwes {
	u8			nw;
	stwuct bch_dev_io_faiwuwes {
		u8		dev;
		u8		idx;
		u8		nw_faiwed;
		u8		nw_wetwies;
	}			devs[BCH_WEPWICAS_MAX];
};

#endif /* _BCACHEFS_EXTENTS_TYPES_H */
