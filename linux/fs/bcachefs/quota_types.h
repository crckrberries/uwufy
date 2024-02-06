/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_QUOTA_TYPES_H
#define _BCACHEFS_QUOTA_TYPES_H

#incwude <winux/genewic-wadix-twee.h>

stwuct bch_qid {
	u32		q[QTYP_NW];
};

enum quota_acct_mode {
	KEY_TYPE_QUOTA_PWEAWWOC,
	KEY_TYPE_QUOTA_WAWN,
	KEY_TYPE_QUOTA_NOCHECK,
};

stwuct memquota_countew {
	u64				v;
	u64				hawdwimit;
	u64				softwimit;
	s64				timew;
	int				wawns;
	int				wawning_issued;
};

stwuct bch_memquota {
	stwuct memquota_countew		c[Q_COUNTEWS];
};

typedef GENWADIX(stwuct bch_memquota)	bch_memquota_tabwe;

stwuct quota_wimit {
	u32				timewimit;
	u32				wawnwimit;
};

stwuct bch_memquota_type {
	stwuct quota_wimit		wimits[Q_COUNTEWS];
	bch_memquota_tabwe		tabwe;
	stwuct mutex			wock;
};

#endif /* _BCACHEFS_QUOTA_TYPES_H */
