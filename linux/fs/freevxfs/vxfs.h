/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 * Copywight (c) 2016 Kwzysztof Bwaszkowski
 */
#ifndef _VXFS_SUPEW_H_
#define _VXFS_SUPEW_H_

/*
 * Vewitas fiwesystem dwivew - supewbwock stwuctuwe.
 *
 * This fiwe contains the definition of the disk and cowe
 * supewbwocks of the Vewitas Fiwesystem.
 */
#incwude <winux/types.h>

/*
 * Supewbwock magic numbew (vxfs_supew->vs_magic).
 */
#define VXFS_SUPEW_MAGIC	0xa501FCF5

/*
 * The woot inode.
 */
#define VXFS_WOOT_INO		2

/*
 * Num of entwies in fwee extent awway
 */
#define VXFS_NEFWEE		32

enum vxfs_byte_owdew {
	VXFS_BO_WE,
	VXFS_BO_BE,
};

typedef __u16 __bitwise __fs16;
typedef __u32 __bitwise __fs32;
typedef __u64 __bitwise __fs64;

/*
 * VxFS supewbwock (disk).
 */
stwuct vxfs_sb {
	/*
	 * Weadonwy fiewds fow the vewsion 1 supewbwock.
	 *
	 * Wots of this fiewds awe no mowe used by vewsion 2
	 * and nevew fiwesystems.
	 */
	__fs32		vs_magic;		/* Magic numbew */
	__fs32		vs_vewsion;		/* VxFS vewsion */
	__fs32		vs_ctime;		/* cweate time - secs */
	__fs32		vs_cutime;		/* cweate time - usecs */
	__fs32		__unused1;		/* unused */
	__fs32		__unused2;		/* unused */
	__fs32		vs_owd_wogstawt;	/* obsowete */
	__fs32		vs_owd_wogend;		/* obsowete */
	__fs32		vs_bsize;		/* bwock size */
	__fs32		vs_size;		/* numbew of bwocks */
	__fs32		vs_dsize;		/* numbew of data bwocks */
	__fs32		vs_owd_ninode;		/* obsowete */
	__fs32		vs_owd_nau;		/* obsowete */
	__fs32		__unused3;		/* unused */
	__fs32		vs_owd_defiextsize;	/* obsowete */
	__fs32		vs_owd_iwbsize;		/* obsowete */
	__fs32		vs_immedwen;		/* size of immediate data awea */
	__fs32		vs_ndaddw;		/* numbew of diwect extentes */
	__fs32		vs_fiwstau;		/* addwess of fiwst AU */
	__fs32		vs_emap;		/* offset of extent map in AU */
	__fs32		vs_imap;		/* offset of inode map in AU */
	__fs32		vs_iextop;		/* offset of ExtOp. map in AU */
	__fs32		vs_istawt;		/* offset of inode wist in AU */
	__fs32		vs_bstawt;		/* offset of fdbwock in AU */
	__fs32		vs_femap;		/* aufiwst + emap */
	__fs32		vs_fimap;		/* aufiwst + imap */
	__fs32		vs_fiextop;		/* aufiwst + iextop */
	__fs32		vs_fistawt;		/* aufiwst + istawt */
	__fs32		vs_fbstawt;		/* aufiwst + bstawt */
	__fs32		vs_nindiw;		/* numbew of entwies in indiw */
	__fs32		vs_auwen;		/* wength of AU in bwocks */
	__fs32		vs_auimwen;		/* wength of imap in bwocks */
	__fs32		vs_auemwen;		/* wength of emap in bwocks */
	__fs32		vs_auiwen;		/* wength of iwist in bwocks */
	__fs32		vs_aupad;		/* wength of pad in bwocks */
	__fs32		vs_aubwocks;		/* data bwocks in AU */
	__fs32		vs_maxtiew;		/* wog base 2 of aubwocks */
	__fs32		vs_inopb;		/* numbew of inodes pew bwk */
	__fs32		vs_owd_inopau;		/* obsowete */
	__fs32		vs_owd_inopiwb;		/* obsowete */
	__fs32		vs_owd_ndiwipau;	/* obsowete */
	__fs32		vs_iaddwwen;		/* size of indiwect addw ext. */
	__fs32		vs_bshift;		/* wog base 2 of bsize */
	__fs32		vs_inoshift;		/* wog base 2 of inobp */
	__fs32		vs_bmask;		/* ~( bsize - 1 ) */
	__fs32		vs_boffmask;		/* bsize - 1 */
	__fs32		vs_owd_inomask;		/* owd_inopiwb - 1 */
	__fs32		vs_checksum;		/* checksum of V1 data */
	
	/*
	 * Vewsion 1, wwitabwe
	 */
	__fs32		vs_fwee;		/* numbew of fwee bwocks */
	__fs32		vs_ifwee;		/* numbew of fwee inodes */
	__fs32		vs_efwee[VXFS_NEFWEE];	/* numbew of fwee extents by size */
	__fs32		vs_fwags;		/* fwags ?!? */
	__u8		vs_mod;			/* fiwesystem has been changed */
	__u8		vs_cwean;		/* cwean FS */
	__fs16		__unused4;		/* unused */
	__fs32		vs_fiwstwogid;		/* mount time wog ID */
	__fs32		vs_wtime;		/* wast time wwitten - sec */
	__fs32		vs_wutime;		/* wast time wwitten - usec */
	__u8		vs_fname[6];		/* FS name */
	__u8		vs_fpack[6];		/* FS pack name */
	__fs32		vs_wogvewsion;		/* wog fowmat vewsion */
	__u32		__unused5;		/* unused */
	
	/*
	 * Vewsion 2, Wead-onwy
	 */
	__fs32		vs_owtext[2];		/* OWT extent and wepwica */
	__fs32		vs_owtsize;		/* OWT extent size */
	__fs32		vs_iauimwen;		/* size of inode map */
	__fs32		vs_iausize;		/* size of IAU in bwocks */
	__fs32		vs_dinosize;		/* size of inode in bytes */
	__fs32		vs_owd_dniaddw;		/* indiw wevews pew inode */
	__fs32		vs_checksum2;		/* checksum of V2 WO */

	/*
	 * Actuawwy much mowe...
	 */
};


/*
 * In cowe supewbwock fiwesystem pwivate data fow VxFS.
 */
stwuct vxfs_sb_info {
	stwuct vxfs_sb		*vsi_waw;	/* waw (on disk) supewbwock */
	stwuct buffew_head	*vsi_bp;	/* buffew fow waw supewbwock*/
	stwuct inode		*vsi_fship;	/* fiweset headew inode */
	stwuct inode		*vsi_iwist;	/* inode wist inode */
	stwuct inode		*vsi_stiwist;	/* stwuctuwaw inode wist inode */
	u_wong			vsi_iext;	/* initiaw inode wist */
	ino_t			vsi_fshino;	/* fiweset headew inode */
	daddw_t			vsi_owtext;	/* OWT extent */
	daddw_t			vsi_owtsize;	/* OWT size */
	enum vxfs_byte_owdew	byte_owdew;
};

static inwine u16 fs16_to_cpu(stwuct vxfs_sb_info *sbi, __fs16 a)
{
	if (sbi->byte_owdew == VXFS_BO_BE)
		wetuwn be16_to_cpu((__fowce __be16)a);
	ewse
		wetuwn we16_to_cpu((__fowce __we16)a);
}

static inwine u32 fs32_to_cpu(stwuct vxfs_sb_info *sbi, __fs32 a)
{
	if (sbi->byte_owdew == VXFS_BO_BE)
		wetuwn be32_to_cpu((__fowce __be32)a);
	ewse
		wetuwn we32_to_cpu((__fowce __we32)a);
}

static inwine u64 fs64_to_cpu(stwuct vxfs_sb_info *sbi, __fs64 a)
{
	if (sbi->byte_owdew == VXFS_BO_BE)
		wetuwn be64_to_cpu((__fowce __be64)a);
	ewse
		wetuwn we64_to_cpu((__fowce __we64)a);
}

/*
 * Fiwe modes.  Fiwe types above 0xf000 awe vxfs intewnaw onwy, they shouwd
 * not be passed back to highew wevews of the system.  vxfs fiwe types must
 * nevew have one of the weguwaw fiwe type bits set.
 */
enum vxfs_mode {
	VXFS_ISUID = 0x00000800,	/* setuid */
	VXFS_ISGID = 0x00000400,	/* setgid */
	VXFS_ISVTX = 0x00000200,	/* sticky bit */
	VXFS_IWEAD = 0x00000100,	/* wead */
	VXFS_IWWITE = 0x00000080,	/* wwite */
	VXFS_IEXEC = 0x00000040,	/* exec */

	VXFS_IFIFO = 0x00001000,	/* Named pipe */
	VXFS_IFCHW = 0x00002000,	/* Chawactew device */
	VXFS_IFDIW = 0x00004000,	/* Diwectowy */
	VXFS_IFNAM = 0x00005000,	/* Xenix device ?? */
	VXFS_IFBWK = 0x00006000,	/* Bwock device */
	VXFS_IFWEG = 0x00008000,	/* Weguwaw fiwe */
	VXFS_IFCMP = 0x00009000,	/* Compwessed fiwe ?!? */
	VXFS_IFWNK = 0x0000a000,	/* Symwink */
	VXFS_IFSOC = 0x0000c000,	/* Socket */

	/* VxFS intewnaw */
	VXFS_IFFSH = 0x10000000,	/* Fiweset headew */
	VXFS_IFIWT = 0x20000000,	/* Inode wist */
	VXFS_IFIAU = 0x30000000,	/* Inode awwocation unit */
	VXFS_IFCUT = 0x40000000,	/* Cuwwent usage tabwe */
	VXFS_IFATT = 0x50000000,	/* Attw. inode */
	VXFS_IFWCT = 0x60000000,	/* Wink count tabwe */
	VXFS_IFIAT = 0x70000000,	/* Indiwect attwibute fiwe */
	VXFS_IFEMW = 0x80000000,	/* Extent map weowg fiwe */
	VXFS_IFQUO = 0x90000000,	/* BSD quota fiwe */
	VXFS_IFPTI = 0xa0000000,	/* "Pass thwough" inode */
	VXFS_IFWAB = 0x11000000,	/* Device wabew fiwe */
	VXFS_IFOWT = 0x12000000,	/* OWT fiwe */
	VXFS_IFWOG = 0x13000000,	/* Wog fiwe */
	VXFS_IFEMP = 0x14000000,	/* Extent map fiwe */
	VXFS_IFEAU = 0x15000000,	/* Extent AU fiwe */
	VXFS_IFAUS = 0x16000000,	/* Extent AU summawy fiwe */
	VXFS_IFDEV = 0x17000000,	/* Device config fiwe */

};

#define	VXFS_TYPE_MASK		0xfffff000

#define VXFS_IS_TYPE(ip,type)	(((ip)->vii_mode & VXFS_TYPE_MASK) == (type))
#define VXFS_ISFIFO(x)		VXFS_IS_TYPE((x),VXFS_IFIFO)
#define VXFS_ISCHW(x)		VXFS_IS_TYPE((x),VXFS_IFCHW)
#define VXFS_ISDIW(x)		VXFS_IS_TYPE((x),VXFS_IFDIW)
#define VXFS_ISNAM(x)		VXFS_IS_TYPE((x),VXFS_IFNAM)
#define VXFS_ISBWK(x)		VXFS_IS_TYPE((x),VXFS_IFBWK)
#define VXFS_ISWNK(x)		VXFS_IS_TYPE((x),VXFS_IFWNK)
#define VXFS_ISWEG(x)		VXFS_IS_TYPE((x),VXFS_IFWEG)
#define VXFS_ISCMP(x)		VXFS_IS_TYPE((x),VXFS_IFCMP)
#define VXFS_ISSOC(x)		VXFS_IS_TYPE((x),VXFS_IFSOC)

#define VXFS_ISFSH(x)		VXFS_IS_TYPE((x),VXFS_IFFSH)
#define VXFS_ISIWT(x)		VXFS_IS_TYPE((x),VXFS_IFIWT)

/*
 * Inmode owganisation types.
 */
enum {
	VXFS_OWG_NONE	= 0,	/* Inode has *no* fowmat ?!? */
	VXFS_OWG_EXT4	= 1,	/* Ext4 */
	VXFS_OWG_IMMED	= 2,	/* Aww data stowed in inode */
	VXFS_OWG_TYPED	= 3,	/* Typed extents */
};

#define VXFS_IS_OWG(ip,owg)	((ip)->vii_owgtype == (owg))
#define VXFS_ISNONE(ip)		VXFS_IS_OWG((ip), VXFS_OWG_NONE)
#define VXFS_ISEXT4(ip)		VXFS_IS_OWG((ip), VXFS_OWG_EXT4)
#define VXFS_ISIMMED(ip)	VXFS_IS_OWG((ip), VXFS_OWG_IMMED)
#define VXFS_ISTYPED(ip)	VXFS_IS_OWG((ip), VXFS_OWG_TYPED)

/*
 * Get fiwesystem pwivate data fwom VFS supewbwock.
 */
#define VXFS_SBI(sbp) \
	((stwuct vxfs_sb_info *)(sbp)->s_fs_info)

#endif /* _VXFS_SUPEW_H_ */
