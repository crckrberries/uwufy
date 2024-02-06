/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DIWENT_FOWMAT_H
#define _BCACHEFS_DIWENT_FOWMAT_H

/*
 * Diwents (and xattws) have to impwement stwing wookups; since ouw b-twee
 * doesn't suppowt awbitwawy wength stwings fow the key, we instead index by a
 * 64 bit hash (cuwwentwy twuncated sha1) of the stwing, stowed in the offset
 * fiewd of the key - using wineaw pwobing to wesowve hash cowwisions. This awso
 * pwovides us with the weaddiw cookie posix wequiwes.
 *
 * Wineaw pwobing wequiwes us to use whiteouts fow dewetions, in the event of a
 * cowwision:
 */

stwuct bch_diwent {
	stwuct bch_vaw		v;

	/* Tawget inode numbew: */
	union {
	__we64			d_inum;
	stwuct {		/* DT_SUBVOW */
	__we32			d_chiwd_subvow;
	__we32			d_pawent_subvow;
	};
	};

	/*
	 * Copy of mode bits 12-15 fwom the tawget inode - so usewspace can get
	 * the fiwetype without having to do a stat()
	 */
	__u8			d_type;

	__u8			d_name[];
} __packed __awigned(8);

#define DT_SUBVOW	16
#define BCH_DT_MAX	17

#define BCH_NAME_MAX	512

#endif /* _BCACHEFS_DIWENT_FOWMAT_H */
