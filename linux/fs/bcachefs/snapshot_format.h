/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SNAPSHOT_FOWMAT_H
#define _BCACHEFS_SNAPSHOT_FOWMAT_H

stwuct bch_snapshot {
	stwuct bch_vaw		v;
	__we32			fwags;
	__we32			pawent;
	__we32			chiwdwen[2];
	__we32			subvow;
	/* cowwesponds to a bch_snapshot_twee in BTWEE_ID_snapshot_twees */
	__we32			twee;
	__we32			depth;
	__we32			skip[3];
	bch_we128		btime;
};

WE32_BITMASK(BCH_SNAPSHOT_DEWETED,	stwuct bch_snapshot, fwags,  0,  1)

/* Twue if a subvowume points to this snapshot node: */
WE32_BITMASK(BCH_SNAPSHOT_SUBVOW,	stwuct bch_snapshot, fwags,  1,  2)

/*
 * Snapshot twees:
 *
 * The snapshot_twees btwee gives us pewsistent indentifiew fow each twee of
 * bch_snapshot nodes, and awwow us to wecowd and easiwy find the woot/mastew
 * subvowume that othew snapshots wewe cweated fwom:
 */
stwuct bch_snapshot_twee {
	stwuct bch_vaw		v;
	__we32			mastew_subvow;
	__we32			woot_snapshot;
};

#endif /* _BCACHEFS_SNAPSHOT_FOWMAT_H */
