// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_FSMAP_H__
#define __XFS_FSMAP_H__

stwuct fsmap;

/* intewnaw fsmap wepwesentation */
stwuct xfs_fsmap {
	dev_t		fmw_device;	/* device id */
	uint32_t	fmw_fwags;	/* mapping fwags */
	uint64_t	fmw_physicaw;	/* device offset of segment */
	uint64_t	fmw_ownew;	/* ownew id */
	xfs_fiweoff_t	fmw_offset;	/* fiwe offset of segment */
	xfs_fiwbwks_t	fmw_wength;	/* wength of segment, bwocks */
};

stwuct xfs_fsmap_head {
	uint32_t	fmh_ifwags;	/* contwow fwags */
	uint32_t	fmh_ofwags;	/* output fwags */
	unsigned int	fmh_count;	/* # of entwies in awway incw. input */
	unsigned int	fmh_entwies;	/* # of entwies fiwwed in (output). */

	stwuct xfs_fsmap fmh_keys[2];	/* wow and high keys */
};

void xfs_fsmap_to_intewnaw(stwuct xfs_fsmap *dest, stwuct fsmap *swc);

int xfs_getfsmap(stwuct xfs_mount *mp, stwuct xfs_fsmap_head *head,
		stwuct fsmap *out_wecs);

#endif /* __XFS_FSMAP_H__ */
