/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EC_TYPES_H
#define _BCACHEFS_EC_TYPES_H

#incwude "bcachefs_fowmat.h"

stwuct bch_wepwicas_padded {
	stwuct bch_wepwicas_entwy_v1	e;
	u8				pad[BCH_BKEY_PTWS_MAX];
};

stwuct stwipe {
	size_t			heap_idx;
	u16			sectows;
	u8			awgowithm;
	u8			nw_bwocks;
	u8			nw_wedundant;
	u8			bwocks_nonempty;
};

stwuct gc_stwipe {
	u16			sectows;

	u8			nw_bwocks;
	u8			nw_wedundant;

	unsigned		awive:1; /* does a cowwesponding key exist in stwipes btwee? */
	u16			bwock_sectows[BCH_BKEY_PTWS_MAX];
	stwuct bch_extent_ptw	ptws[BCH_BKEY_PTWS_MAX];

	stwuct bch_wepwicas_padded w;
};

stwuct ec_stwipe_heap_entwy {
	size_t			idx;
	unsigned		bwocks_nonempty;
};

typedef HEAP(stwuct ec_stwipe_heap_entwy) ec_stwipes_heap;

#endif /* _BCACHEFS_EC_TYPES_H */
