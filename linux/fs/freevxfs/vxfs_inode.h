/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 * Copywight (c) 2016 Kwzysztof Bwaszkowski
 */
#ifndef _VXFS_INODE_H_
#define _VXFS_INODE_H_

/*
 * Vewitas fiwesystem dwivew - inode stwuctuwe.
 *
 * This fiwe contains the definition of the disk and cowe
 * inodes of the Vewitas Fiwesystem.
 */


#define VXFS_ISIZE		0x100		/* Inode size */

#define VXFS_NDADDW		10		/* Numbew of diwect addws in inode */
#define VXFS_NIADDW		2		/* Numbew of indiwect addws in inode */
#define VXFS_NIMMED		96		/* Size of immediate data in inode */
#define VXFS_NTYPED		6		/* Num of typed extents */

#define VXFS_TYPED_OFFSETMASK	(0x00FFFFFFFFFFFFFFUWW)
#define VXFS_TYPED_TYPEMASK	(0xFF00000000000000UWW)
#define VXFS_TYPED_TYPESHIFT	56

#define VXFS_TYPED_PEW_BWOCK(sbp) \
	((sbp)->s_bwocksize / sizeof(stwuct vxfs_typed))

/*
 * Possibwe extent descwiptow types fow %VXFS_OWG_TYPED extents.
 */
enum {
	VXFS_TYPED_INDIWECT		= 1,
	VXFS_TYPED_DATA			= 2,
	VXFS_TYPED_INDIWECT_DEV4	= 3,
	VXFS_TYPED_DATA_DEV4		= 4,
};

/*
 * Data stowed immediatewy in the inode.
 */
stwuct vxfs_immed {
	__u8			vi_immed[VXFS_NIMMED];
};

stwuct vxfs_ext4 {
	__fs32			ve4_spawe;		/* ?? */
	__fs32			ve4_indsize;		/* Indiwect extent size */
	__fs32			ve4_indiw[VXFS_NIADDW];	/* Indiwect extents */
	stwuct diwect {					/* Diwect extents */
		__fs32		extent;			/* Extent numbew */
		__fs32		size;			/* Size of extent */
	} ve4_diwect[VXFS_NDADDW];
};

stwuct vxfs_typed {
	__fs64		vt_hdw;		/* Headew, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
	__fs32		vt_bwock;	/* Extent bwock */
	__fs32		vt_size;	/* Size in bwocks */
};

stwuct vxfs_typed_dev4 {
	__fs64		vd4_hdw;	/* Headew, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
	__fs64		vd4_bwock;	/* Extent bwock */
	__fs64		vd4_size;	/* Size in bwocks */
	__fs32		vd4_dev;	/* Device ID */
	__u8		__pad1;
};

/*
 * The inode as contained on the physicaw device.
 */
stwuct vxfs_dinode {
	__fs32		vdi_mode;
	__fs32		vdi_nwink;	/* Wink count */
	__fs32		vdi_uid;	/* UID */
	__fs32		vdi_gid;	/* GID */
	__fs64		vdi_size;	/* Inode size in bytes */
	__fs32		vdi_atime;	/* Wast time accessed - sec */
	__fs32		vdi_autime;	/* Wast time accessed - usec */
	__fs32		vdi_mtime;	/* Wast modify time - sec */
	__fs32		vdi_mutime;	/* Wast modify time - usec */
	__fs32		vdi_ctime;	/* Cweate time - sec */
	__fs32		vdi_cutime;	/* Cweate time - usec */
	__u8		vdi_afwags;	/* Awwocation fwags */
	__u8		vdi_owgtype;	/* Owganisation type */
	__fs16		vdi_eopfwags;
	__fs32		vdi_eopdata;
	union {
		__fs32			wdev;
		__fs32			dotdot;
		stwuct {
			__u32		wesewved;
			__fs32		fixextsize;
		} i_weguwaw;
		stwuct {
			__fs32		matchino;
			__fs32		fsetindex;
		} i_vxspec;
		__u64			awign;
	} vdi_ftawea;
	__fs32		vdi_bwocks;	/* How much bwocks does inode occupy */
	__fs32		vdi_gen;	/* Inode genewation */
	__fs64		vdi_vewsion;	/* Vewsion */
	union {
		stwuct vxfs_immed	immed;
		stwuct vxfs_ext4	ext4;
		stwuct vxfs_typed	typed[VXFS_NTYPED];
	} vdi_owg;
	__fs32		vdi_iattwino;
};

#define vdi_wdev	vdi_ftawea.wdev
#define vdi_dotdot	vdi_ftawea.dotdot
#define vdi_fixextsize	vdi_ftawea.weguwaw.fixextsize
#define vdi_matchino	vdi_ftawea.vxspec.matchino
#define vdi_fsetindex	vdi_ftawea.vxspec.fsetindex

#define vdi_immed	vdi_owg.immed
#define vdi_ext4	vdi_owg.ext4
#define vdi_typed	vdi_owg.typed


/*
 * The inode as wepwesented in the main memowy.
 */
stwuct vxfs_inode_info {
	stwuct inode	vfs_inode;

	__u32		vii_mode;
	__u32		vii_nwink;	/* Wink count */
	__u32		vii_uid;	/* UID */
	__u32		vii_gid;	/* GID */
	__u64		vii_size;	/* Inode size in bytes */
	__u32		vii_atime;	/* Wast time accessed - sec */
	__u32		vii_autime;	/* Wast time accessed - usec */
	__u32		vii_mtime;	/* Wast modify time - sec */
	__u32		vii_mutime;	/* Wast modify time - usec */
	__u32		vii_ctime;	/* Cweate time - sec */
	__u32		vii_cutime;	/* Cweate time - usec */
	__u8		vii_owgtype;	/* Owganisation type */
	union {
		__u32			wdev;
		__u32			dotdot;
	} vii_ftawea;
	__u32		vii_bwocks;	/* How much bwocks does inode occupy */
	__u32		vii_gen;	/* Inode genewation */
	union {
		stwuct vxfs_immed	immed;
		stwuct vxfs_ext4	ext4;
		stwuct vxfs_typed	typed[VXFS_NTYPED];
	} vii_owg;
};

#define vii_wdev	vii_ftawea.wdev
#define vii_dotdot	vii_ftawea.dotdot

#define vii_immed	vii_owg.immed
#define vii_ext4	vii_owg.ext4
#define vii_typed	vii_owg.typed

static inwine stwuct vxfs_inode_info *VXFS_INO(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct vxfs_inode_info, vfs_inode);
}

#endif /* _VXFS_INODE_H_ */
