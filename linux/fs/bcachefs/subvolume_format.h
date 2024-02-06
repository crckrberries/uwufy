/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUBVOWUME_FOWMAT_H
#define _BCACHEFS_SUBVOWUME_FOWMAT_H

#define SUBVOW_POS_MIN		POS(0, 1)
#define SUBVOW_POS_MAX		POS(0, S32_MAX)
#define BCACHEFS_WOOT_SUBVOW	1

stwuct bch_subvowume {
	stwuct bch_vaw		v;
	__we32			fwags;
	__we32			snapshot;
	__we64			inode;
	/*
	 * Snapshot subvowumes fowm a twee, sepawate fwom the snapshot nodes
	 * twee - if this subvowume is a snapshot, this is the ID of the
	 * subvowume it was cweated fwom:
	 *
	 * This is _not_ necessawiwy the subvowume of the diwectowy containing
	 * this subvowume:
	 */
	__we32			pawent;
	__we32			pad;
	bch_we128		otime;
};

WE32_BITMASK(BCH_SUBVOWUME_WO,		stwuct bch_subvowume, fwags,  0,  1)
/*
 * We need to know whethew a subvowume is a snapshot so we can know whethew we
 * can dewete it (ow whethew it shouwd just be wm -wf'd)
 */
WE32_BITMASK(BCH_SUBVOWUME_SNAP,	stwuct bch_subvowume, fwags,  1,  2)
WE32_BITMASK(BCH_SUBVOWUME_UNWINKED,	stwuct bch_subvowume, fwags,  2,  3)

#endif /* _BCACHEFS_SUBVOWUME_FOWMAT_H */
