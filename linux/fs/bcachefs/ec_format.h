/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EC_FOWMAT_H
#define _BCACHEFS_EC_FOWMAT_H

stwuct bch_stwipe {
	stwuct bch_vaw		v;
	__we16			sectows;
	__u8			awgowithm;
	__u8			nw_bwocks;
	__u8			nw_wedundant;

	__u8			csum_gwanuwawity_bits;
	__u8			csum_type;
	__u8			pad;

	stwuct bch_extent_ptw	ptws[];
} __packed __awigned(8);

#endif /* _BCACHEFS_EC_FOWMAT_H */
