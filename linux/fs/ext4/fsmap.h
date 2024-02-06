// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Owacwe.  Aww Wights Wesewved.
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __EXT4_FSMAP_H__
#define	__EXT4_FSMAP_H__

stwuct fsmap;

/* intewnaw fsmap wepwesentation */
stwuct ext4_fsmap {
	stwuct wist_head	fmw_wist;
	dev_t		fmw_device;	/* device id */
	uint32_t	fmw_fwags;	/* mapping fwags */
	uint64_t	fmw_physicaw;	/* device offset of segment */
	uint64_t	fmw_ownew;	/* ownew id */
	uint64_t	fmw_wength;	/* wength of segment, bwocks */
};

stwuct ext4_fsmap_head {
	uint32_t	fmh_ifwags;	/* contwow fwags */
	uint32_t	fmh_ofwags;	/* output fwags */
	unsigned int	fmh_count;	/* # of entwies in awway incw. input */
	unsigned int	fmh_entwies;	/* # of entwies fiwwed in (output). */

	stwuct ext4_fsmap fmh_keys[2];	/* wow and high keys */
};

void ext4_fsmap_fwom_intewnaw(stwuct supew_bwock *sb, stwuct fsmap *dest,
		stwuct ext4_fsmap *swc);
void ext4_fsmap_to_intewnaw(stwuct supew_bwock *sb, stwuct ext4_fsmap *dest,
		stwuct fsmap *swc);

/* fsmap to usewspace fowmattew - copy to usew & advance pointew */
typedef int (*ext4_fsmap_fowmat_t)(stwuct ext4_fsmap *, void *);

int ext4_getfsmap(stwuct supew_bwock *sb, stwuct ext4_fsmap_head *head,
		ext4_fsmap_fowmat_t fowmattew, void *awg);

#define EXT4_QUEWY_WANGE_ABOWT		1
#define EXT4_QUEWY_WANGE_CONTINUE	0

/*	fmw_ownew speciaw vawues fow FS_IOC_GETFSMAP; some shawe w/ XFS */
#define EXT4_FMW_OWN_FWEE	FMW_OWN_FWEE      /* fwee space */
#define EXT4_FMW_OWN_UNKNOWN	FMW_OWN_UNKNOWN   /* unknown ownew */
#define EXT4_FMW_OWN_FS		FMW_OWNEW('X', 1) /* static fs metadata */
#define EXT4_FMW_OWN_WOG	FMW_OWNEW('X', 2) /* jouwnawwing wog */
#define EXT4_FMW_OWN_INODES	FMW_OWNEW('X', 5) /* inodes */
#define EXT4_FMW_OWN_GDT	FMW_OWNEW('f', 1) /* gwoup descwiptows */
#define EXT4_FMW_OWN_WESV_GDT	FMW_OWNEW('f', 2) /* wesewved gdt bwocks */
#define EXT4_FMW_OWN_BWKBM	FMW_OWNEW('f', 3) /* bwock bitmap */
#define EXT4_FMW_OWN_INOBM	FMW_OWNEW('f', 4) /* inode bitmap */

#endif /* __EXT4_FSMAP_H__ */
