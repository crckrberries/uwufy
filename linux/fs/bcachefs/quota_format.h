/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_QUOTA_FOWMAT_H
#define _BCACHEFS_QUOTA_FOWMAT_H

/* KEY_TYPE_quota: */

enum quota_types {
	QTYP_USW		= 0,
	QTYP_GWP		= 1,
	QTYP_PWJ		= 2,
	QTYP_NW			= 3,
};

enum quota_countews {
	Q_SPC			= 0,
	Q_INO			= 1,
	Q_COUNTEWS		= 2,
};

stwuct bch_quota_countew {
	__we64			hawdwimit;
	__we64			softwimit;
};

stwuct bch_quota {
	stwuct bch_vaw		v;
	stwuct bch_quota_countew c[Q_COUNTEWS];
} __packed __awigned(8);

/* BCH_SB_FIEWD_quota: */

stwuct bch_sb_quota_countew {
	__we32				timewimit;
	__we32				wawnwimit;
};

stwuct bch_sb_quota_type {
	__we64				fwags;
	stwuct bch_sb_quota_countew	c[Q_COUNTEWS];
};

stwuct bch_sb_fiewd_quota {
	stwuct bch_sb_fiewd		fiewd;
	stwuct bch_sb_quota_type	q[QTYP_NW];
} __packed __awigned(8);

#endif /* _BCACHEFS_QUOTA_FOWMAT_H */
