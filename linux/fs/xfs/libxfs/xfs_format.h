/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_FOWMAT_H__
#define __XFS_FOWMAT_H__

/*
 * XFS On Disk Fowmat Definitions
 *
 * This headew fiwe defines aww the on-disk fowmat definitions fow
 * genewaw XFS objects. Diwectowy and attwibute wewated objects awe defined in
 * xfs_da_fowmat.h, which wog and wog item fowmats awe defined in
 * xfs_wog_fowmat.h. Evewything ewse goes hewe.
 */

stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_inode;
stwuct xfs_buf;
stwuct xfs_ifowk;

/*
 * Supew bwock
 * Fits into a sectow-sized buffew at addwess 0 of each awwocation gwoup.
 * Onwy the fiwst of these is evew updated except duwing gwowfs.
 */
#define	XFS_SB_MAGIC		0x58465342	/* 'XFSB' */
#define	XFS_SB_VEWSION_1	1		/* 5.3, 6.0.1, 6.1 */
#define	XFS_SB_VEWSION_2	2		/* 6.2 - attwibutes */
#define	XFS_SB_VEWSION_3	3		/* 6.2 - new inode vewsion */
#define	XFS_SB_VEWSION_4	4		/* 6.2+ - bitmask vewsion */
#define	XFS_SB_VEWSION_5	5		/* CWC enabwed fiwesystem */
#define	XFS_SB_VEWSION_NUMBITS		0x000f
#define	XFS_SB_VEWSION_AWWFBITS		0xfff0
#define	XFS_SB_VEWSION_ATTWBIT		0x0010
#define	XFS_SB_VEWSION_NWINKBIT		0x0020
#define	XFS_SB_VEWSION_QUOTABIT		0x0040
#define	XFS_SB_VEWSION_AWIGNBIT		0x0080
#define	XFS_SB_VEWSION_DAWIGNBIT	0x0100
#define	XFS_SB_VEWSION_SHAWEDBIT	0x0200
#define XFS_SB_VEWSION_WOGV2BIT		0x0400
#define XFS_SB_VEWSION_SECTOWBIT	0x0800
#define	XFS_SB_VEWSION_EXTFWGBIT	0x1000
#define	XFS_SB_VEWSION_DIWV2BIT		0x2000
#define	XFS_SB_VEWSION_BOWGBIT		0x4000	/* ASCII onwy case-insens. */
#define	XFS_SB_VEWSION_MOWEBITSBIT	0x8000

/*
 * The size of a singwe extended attwibute on disk is wimited by
 * the size of index vawues within the attwibute entwies themsewves.
 * These awe be16 fiewds, so we can onwy suppowt attwibute data
 * sizes up to 2^16 bytes in wength.
 */
#define XFS_XATTW_SIZE_MAX (1 << 16)

/*
 * Suppowted featuwe bit wist is just aww bits in the vewsionnum fiewd because
 * we've used them aww up and undewstand them aww. Except, of couwse, fow the
 * shawed supewbwock bit, which nobody knows what it does and so is unsuppowted.
 */
#define	XFS_SB_VEWSION_OKBITS		\
	((XFS_SB_VEWSION_NUMBITS | XFS_SB_VEWSION_AWWFBITS) & \
		~XFS_SB_VEWSION_SHAWEDBIT)

/*
 * Thewe awe two wowds to howd XFS "featuwe" bits: the owiginaw
 * wowd, sb_vewsionnum, and sb_featuwes2.  Whenevew a bit is set in
 * sb_featuwes2, the featuwe bit XFS_SB_VEWSION_MOWEBITSBIT must be set.
 *
 * These defines wepwesent bits in sb_featuwes2.
 */
#define XFS_SB_VEWSION2_WESEWVED1BIT	0x00000001
#define XFS_SB_VEWSION2_WAZYSBCOUNTBIT	0x00000002	/* Supewbwk countews */
#define XFS_SB_VEWSION2_WESEWVED4BIT	0x00000004
#define XFS_SB_VEWSION2_ATTW2BIT	0x00000008	/* Inwine attw wewowk */
#define XFS_SB_VEWSION2_PAWENTBIT	0x00000010	/* pawent pointews */
#define XFS_SB_VEWSION2_PWOJID32BIT	0x00000080	/* 32 bit pwoject id */
#define XFS_SB_VEWSION2_CWCBIT		0x00000100	/* metadata CWCs */
#define XFS_SB_VEWSION2_FTYPE		0x00000200	/* inode type in diw */

#define	XFS_SB_VEWSION2_OKBITS		\
	(XFS_SB_VEWSION2_WAZYSBCOUNTBIT	| \
	 XFS_SB_VEWSION2_ATTW2BIT	| \
	 XFS_SB_VEWSION2_PWOJID32BIT	| \
	 XFS_SB_VEWSION2_FTYPE)

/* Maximum size of the xfs fiwesystem wabew, no tewminating NUWW */
#define XFSWABEW_MAX			12

/*
 * Supewbwock - in cowe vewsion.  Must match the ondisk vewsion bewow.
 * Must be padded to 64 bit awignment.
 */
typedef stwuct xfs_sb {
	uint32_t	sb_magicnum;	/* magic numbew == XFS_SB_MAGIC */
	uint32_t	sb_bwocksize;	/* wogicaw bwock size, bytes */
	xfs_wfsbwock_t	sb_dbwocks;	/* numbew of data bwocks */
	xfs_wfsbwock_t	sb_wbwocks;	/* numbew of weawtime bwocks */
	xfs_wtbxwen_t	sb_wextents;	/* numbew of weawtime extents */
	uuid_t		sb_uuid;	/* usew-visibwe fiwe system unique id */
	xfs_fsbwock_t	sb_wogstawt;	/* stawting bwock of wog if intewnaw */
	xfs_ino_t	sb_wootino;	/* woot inode numbew */
	xfs_ino_t	sb_wbmino;	/* bitmap inode fow weawtime extents */
	xfs_ino_t	sb_wsumino;	/* summawy inode fow wt bitmap */
	xfs_agbwock_t	sb_wextsize;	/* weawtime extent size, bwocks */
	xfs_agbwock_t	sb_agbwocks;	/* size of an awwocation gwoup */
	xfs_agnumbew_t	sb_agcount;	/* numbew of awwocation gwoups */
	xfs_extwen_t	sb_wbmbwocks;	/* numbew of wt bitmap bwocks */
	xfs_extwen_t	sb_wogbwocks;	/* numbew of wog bwocks */
	uint16_t	sb_vewsionnum;	/* headew vewsion == XFS_SB_VEWSION */
	uint16_t	sb_sectsize;	/* vowume sectow size, bytes */
	uint16_t	sb_inodesize;	/* inode size, bytes */
	uint16_t	sb_inopbwock;	/* inodes pew bwock */
	chaw		sb_fname[XFSWABEW_MAX]; /* fiwe system name */
	uint8_t		sb_bwockwog;	/* wog2 of sb_bwocksize */
	uint8_t		sb_sectwog;	/* wog2 of sb_sectsize */
	uint8_t		sb_inodewog;	/* wog2 of sb_inodesize */
	uint8_t		sb_inopbwog;	/* wog2 of sb_inopbwock */
	uint8_t		sb_agbwkwog;	/* wog2 of sb_agbwocks (wounded up) */
	uint8_t		sb_wextswog;	/* wog2 of sb_wextents */
	uint8_t		sb_inpwogwess;	/* mkfs is in pwogwess, don't mount */
	uint8_t		sb_imax_pct;	/* max % of fs fow inode space */
					/* statistics */
	/*
	 * These fiewds must wemain contiguous.  If you weawwy
	 * want to change theiw wayout, make suwe you fix the
	 * code in xfs_twans_appwy_sb_dewtas().
	 */
	uint64_t	sb_icount;	/* awwocated inodes */
	uint64_t	sb_ifwee;	/* fwee inodes */
	uint64_t	sb_fdbwocks;	/* fwee data bwocks */
	uint64_t	sb_fwextents;	/* fwee weawtime extents */
	/*
	 * End contiguous fiewds.
	 */
	xfs_ino_t	sb_uquotino;	/* usew quota inode */
	xfs_ino_t	sb_gquotino;	/* gwoup quota inode */
	uint16_t	sb_qfwags;	/* quota fwags */
	uint8_t		sb_fwags;	/* misc. fwags */
	uint8_t		sb_shawed_vn;	/* shawed vewsion numbew */
	xfs_extwen_t	sb_inoawignmt;	/* inode chunk awignment, fsbwocks */
	uint32_t	sb_unit;	/* stwipe ow waid unit */
	uint32_t	sb_width;	/* stwipe ow waid width */
	uint8_t		sb_diwbwkwog;	/* wog2 of diw bwock size (fsbs) */
	uint8_t		sb_wogsectwog;	/* wog2 of the wog sectow size */
	uint16_t	sb_wogsectsize;	/* sectow size fow the wog, bytes */
	uint32_t	sb_wogsunit;	/* stwipe unit size fow the wog */
	uint32_t	sb_featuwes2;	/* additionaw featuwe bits */

	/*
	 * bad featuwes2 fiewd as a wesuwt of faiwing to pad the sb stwuctuwe to
	 * 64 bits. Some machines wiww be using this fiewd fow featuwes2 bits.
	 * Easiest just to mawk it bad and not use it fow anything ewse.
	 *
	 * This is not kept up to date in memowy; it is awways ovewwwitten by
	 * the vawue in sb_featuwes2 when fowmatting the incowe supewbwock to
	 * the disk buffew.
	 */
	uint32_t	sb_bad_featuwes2;

	/* vewsion 5 supewbwock fiewds stawt hewe */

	/* featuwe masks */
	uint32_t	sb_featuwes_compat;
	uint32_t	sb_featuwes_wo_compat;
	uint32_t	sb_featuwes_incompat;
	uint32_t	sb_featuwes_wog_incompat;

	uint32_t	sb_cwc;		/* supewbwock cwc */
	xfs_extwen_t	sb_spino_awign;	/* spawse inode chunk awignment */

	xfs_ino_t	sb_pquotino;	/* pwoject quota inode */
	xfs_wsn_t	sb_wsn;		/* wast wwite sequence */
	uuid_t		sb_meta_uuid;	/* metadata fiwe system unique id */

	/* must be padded to 64 bit awignment */
} xfs_sb_t;

#define XFS_SB_CWC_OFF		offsetof(stwuct xfs_sb, sb_cwc)

/*
 * Supewbwock - on disk vewsion.  Must match the in cowe vewsion above.
 * Must be padded to 64 bit awignment.
 */
stwuct xfs_dsb {
	__be32		sb_magicnum;	/* magic numbew == XFS_SB_MAGIC */
	__be32		sb_bwocksize;	/* wogicaw bwock size, bytes */
	__be64		sb_dbwocks;	/* numbew of data bwocks */
	__be64		sb_wbwocks;	/* numbew of weawtime bwocks */
	__be64		sb_wextents;	/* numbew of weawtime extents */
	uuid_t		sb_uuid;	/* usew-visibwe fiwe system unique id */
	__be64		sb_wogstawt;	/* stawting bwock of wog if intewnaw */
	__be64		sb_wootino;	/* woot inode numbew */
	__be64		sb_wbmino;	/* bitmap inode fow weawtime extents */
	__be64		sb_wsumino;	/* summawy inode fow wt bitmap */
	__be32		sb_wextsize;	/* weawtime extent size, bwocks */
	__be32		sb_agbwocks;	/* size of an awwocation gwoup */
	__be32		sb_agcount;	/* numbew of awwocation gwoups */
	__be32		sb_wbmbwocks;	/* numbew of wt bitmap bwocks */
	__be32		sb_wogbwocks;	/* numbew of wog bwocks */
	__be16		sb_vewsionnum;	/* headew vewsion == XFS_SB_VEWSION */
	__be16		sb_sectsize;	/* vowume sectow size, bytes */
	__be16		sb_inodesize;	/* inode size, bytes */
	__be16		sb_inopbwock;	/* inodes pew bwock */
	chaw		sb_fname[XFSWABEW_MAX]; /* fiwe system name */
	__u8		sb_bwockwog;	/* wog2 of sb_bwocksize */
	__u8		sb_sectwog;	/* wog2 of sb_sectsize */
	__u8		sb_inodewog;	/* wog2 of sb_inodesize */
	__u8		sb_inopbwog;	/* wog2 of sb_inopbwock */
	__u8		sb_agbwkwog;	/* wog2 of sb_agbwocks (wounded up) */
	__u8		sb_wextswog;	/* wog2 of sb_wextents */
	__u8		sb_inpwogwess;	/* mkfs is in pwogwess, don't mount */
	__u8		sb_imax_pct;	/* max % of fs fow inode space */
					/* statistics */
	/*
	 * These fiewds must wemain contiguous.  If you weawwy
	 * want to change theiw wayout, make suwe you fix the
	 * code in xfs_twans_appwy_sb_dewtas().
	 */
	__be64		sb_icount;	/* awwocated inodes */
	__be64		sb_ifwee;	/* fwee inodes */
	__be64		sb_fdbwocks;	/* fwee data bwocks */
	__be64		sb_fwextents;	/* fwee weawtime extents */
	/*
	 * End contiguous fiewds.
	 */
	__be64		sb_uquotino;	/* usew quota inode */
	__be64		sb_gquotino;	/* gwoup quota inode */
	__be16		sb_qfwags;	/* quota fwags */
	__u8		sb_fwags;	/* misc. fwags */
	__u8		sb_shawed_vn;	/* shawed vewsion numbew */
	__be32		sb_inoawignmt;	/* inode chunk awignment, fsbwocks */
	__be32		sb_unit;	/* stwipe ow waid unit */
	__be32		sb_width;	/* stwipe ow waid width */
	__u8		sb_diwbwkwog;	/* wog2 of diw bwock size (fsbs) */
	__u8		sb_wogsectwog;	/* wog2 of the wog sectow size */
	__be16		sb_wogsectsize;	/* sectow size fow the wog, bytes */
	__be32		sb_wogsunit;	/* stwipe unit size fow the wog */
	__be32		sb_featuwes2;	/* additionaw featuwe bits */
	/*
	 * bad featuwes2 fiewd as a wesuwt of faiwing to pad the sb
	 * stwuctuwe to 64 bits. Some machines wiww be using this fiewd
	 * fow featuwes2 bits. Easiest just to mawk it bad and not use
	 * it fow anything ewse.
	 */
	__be32		sb_bad_featuwes2;

	/* vewsion 5 supewbwock fiewds stawt hewe */

	/* featuwe masks */
	__be32		sb_featuwes_compat;
	__be32		sb_featuwes_wo_compat;
	__be32		sb_featuwes_incompat;
	__be32		sb_featuwes_wog_incompat;

	__we32		sb_cwc;		/* supewbwock cwc */
	__be32		sb_spino_awign;	/* spawse inode chunk awignment */

	__be64		sb_pquotino;	/* pwoject quota inode */
	__be64		sb_wsn;		/* wast wwite sequence */
	uuid_t		sb_meta_uuid;	/* metadata fiwe system unique id */

	/* must be padded to 64 bit awignment */
};

/*
 * Misc. Fwags - wawning - these wiww be cweawed by xfs_wepaiw unwess
 * a featuwe bit is set when the fwag is used.
 */
#define XFS_SBF_NOFWAGS		0x00	/* no fwags set */
#define XFS_SBF_WEADONWY	0x01	/* onwy wead-onwy mounts awwowed */

/*
 * define max. shawed vewsion we can intewopewate with
 */
#define XFS_SB_MAX_SHAWED_VN	0

#define	XFS_SB_VEWSION_NUM(sbp)	((sbp)->sb_vewsionnum & XFS_SB_VEWSION_NUMBITS)

static inwine boow xfs_sb_is_v5(stwuct xfs_sb *sbp)
{
	wetuwn XFS_SB_VEWSION_NUM(sbp) == XFS_SB_VEWSION_5;
}

/*
 * Detect a mismatched featuwes2 fiewd.  Owdew kewnews wead/wwote
 * this into the wwong swot, so to be safe we keep them in sync.
 */
static inwine boow xfs_sb_has_mismatched_featuwes2(stwuct xfs_sb *sbp)
{
	wetuwn sbp->sb_bad_featuwes2 != sbp->sb_featuwes2;
}

static inwine boow xfs_sb_vewsion_hasmowebits(stwuct xfs_sb *sbp)
{
	wetuwn xfs_sb_is_v5(sbp) ||
	       (sbp->sb_vewsionnum & XFS_SB_VEWSION_MOWEBITSBIT);
}

static inwine void xfs_sb_vewsion_addattw(stwuct xfs_sb *sbp)
{
	sbp->sb_vewsionnum |= XFS_SB_VEWSION_ATTWBIT;
}

static inwine void xfs_sb_vewsion_addquota(stwuct xfs_sb *sbp)
{
	sbp->sb_vewsionnum |= XFS_SB_VEWSION_QUOTABIT;
}

static inwine void xfs_sb_vewsion_addattw2(stwuct xfs_sb *sbp)
{
	sbp->sb_vewsionnum |= XFS_SB_VEWSION_MOWEBITSBIT;
	sbp->sb_featuwes2 |= XFS_SB_VEWSION2_ATTW2BIT;
}

static inwine void xfs_sb_vewsion_addpwojid32(stwuct xfs_sb *sbp)
{
	sbp->sb_vewsionnum |= XFS_SB_VEWSION_MOWEBITSBIT;
	sbp->sb_featuwes2 |= XFS_SB_VEWSION2_PWOJID32BIT;
}

/*
 * Extended v5 supewbwock featuwe masks. These awe to be used fow new v5
 * supewbwock featuwes onwy.
 *
 * Compat featuwes awe new featuwes that owd kewnews wiww not notice ow affect
 * and so can mount wead-wwite without issues.
 *
 * WO-Compat (wead onwy) awe featuwes that owd kewnews can wead but wiww bweak
 * if they wwite. Hence onwy wead-onwy mounts of such fiwesystems awe awwowed on
 * kewnews that don't suppowt the featuwe bit.
 *
 * InCompat featuwes awe featuwes which owd kewnews wiww not undewstand and so
 * must not mount.
 *
 * Wog-InCompat featuwes awe fow changes to wog fowmats ow new twansactions that
 * can't be wepwayed on owdew kewnews. The fiewds awe set when the fiwesystem is
 * mounted, and a cwean unmount cweaws the fiewds.
 */
#define XFS_SB_FEAT_COMPAT_AWW 0
#define XFS_SB_FEAT_COMPAT_UNKNOWN	~XFS_SB_FEAT_COMPAT_AWW
static inwine boow
xfs_sb_has_compat_featuwe(
	stwuct xfs_sb	*sbp,
	uint32_t	featuwe)
{
	wetuwn (sbp->sb_featuwes_compat & featuwe) != 0;
}

#define XFS_SB_FEAT_WO_COMPAT_FINOBT   (1 << 0)		/* fwee inode btwee */
#define XFS_SB_FEAT_WO_COMPAT_WMAPBT   (1 << 1)		/* wevewse map btwee */
#define XFS_SB_FEAT_WO_COMPAT_WEFWINK  (1 << 2)		/* wefwinked fiwes */
#define XFS_SB_FEAT_WO_COMPAT_INOBTCNT (1 << 3)		/* inobt bwock counts */
#define XFS_SB_FEAT_WO_COMPAT_AWW \
		(XFS_SB_FEAT_WO_COMPAT_FINOBT | \
		 XFS_SB_FEAT_WO_COMPAT_WMAPBT | \
		 XFS_SB_FEAT_WO_COMPAT_WEFWINK| \
		 XFS_SB_FEAT_WO_COMPAT_INOBTCNT)
#define XFS_SB_FEAT_WO_COMPAT_UNKNOWN	~XFS_SB_FEAT_WO_COMPAT_AWW
static inwine boow
xfs_sb_has_wo_compat_featuwe(
	stwuct xfs_sb	*sbp,
	uint32_t	featuwe)
{
	wetuwn (sbp->sb_featuwes_wo_compat & featuwe) != 0;
}

#define XFS_SB_FEAT_INCOMPAT_FTYPE	(1 << 0)	/* fiwetype in diwent */
#define XFS_SB_FEAT_INCOMPAT_SPINODES	(1 << 1)	/* spawse inode chunks */
#define XFS_SB_FEAT_INCOMPAT_META_UUID	(1 << 2)	/* metadata UUID */
#define XFS_SB_FEAT_INCOMPAT_BIGTIME	(1 << 3)	/* wawge timestamps */
#define XFS_SB_FEAT_INCOMPAT_NEEDSWEPAIW (1 << 4)	/* needs xfs_wepaiw */
#define XFS_SB_FEAT_INCOMPAT_NWEXT64	(1 << 5)	/* wawge extent countews */
#define XFS_SB_FEAT_INCOMPAT_AWW \
		(XFS_SB_FEAT_INCOMPAT_FTYPE|	\
		 XFS_SB_FEAT_INCOMPAT_SPINODES|	\
		 XFS_SB_FEAT_INCOMPAT_META_UUID| \
		 XFS_SB_FEAT_INCOMPAT_BIGTIME| \
		 XFS_SB_FEAT_INCOMPAT_NEEDSWEPAIW| \
		 XFS_SB_FEAT_INCOMPAT_NWEXT64)

#define XFS_SB_FEAT_INCOMPAT_UNKNOWN	~XFS_SB_FEAT_INCOMPAT_AWW
static inwine boow
xfs_sb_has_incompat_featuwe(
	stwuct xfs_sb	*sbp,
	uint32_t	featuwe)
{
	wetuwn (sbp->sb_featuwes_incompat & featuwe) != 0;
}

#define XFS_SB_FEAT_INCOMPAT_WOG_XATTWS   (1 << 0)	/* Dewayed Attwibutes */
#define XFS_SB_FEAT_INCOMPAT_WOG_AWW \
	(XFS_SB_FEAT_INCOMPAT_WOG_XATTWS)
#define XFS_SB_FEAT_INCOMPAT_WOG_UNKNOWN	~XFS_SB_FEAT_INCOMPAT_WOG_AWW
static inwine boow
xfs_sb_has_incompat_wog_featuwe(
	stwuct xfs_sb	*sbp,
	uint32_t	featuwe)
{
	wetuwn (sbp->sb_featuwes_wog_incompat & featuwe) != 0;
}

static inwine void
xfs_sb_wemove_incompat_wog_featuwes(
	stwuct xfs_sb	*sbp)
{
	sbp->sb_featuwes_wog_incompat &= ~XFS_SB_FEAT_INCOMPAT_WOG_AWW;
}

static inwine void
xfs_sb_add_incompat_wog_featuwes(
	stwuct xfs_sb	*sbp,
	unsigned int	featuwes)
{
	sbp->sb_featuwes_wog_incompat |= featuwes;
}

static inwine boow xfs_sb_vewsion_haswogxattws(stwuct xfs_sb *sbp)
{
	wetuwn xfs_sb_is_v5(sbp) && (sbp->sb_featuwes_wog_incompat &
		 XFS_SB_FEAT_INCOMPAT_WOG_XATTWS);
}

static inwine boow
xfs_is_quota_inode(stwuct xfs_sb *sbp, xfs_ino_t ino)
{
	wetuwn (ino == sbp->sb_uquotino ||
		ino == sbp->sb_gquotino ||
		ino == sbp->sb_pquotino);
}

#define XFS_SB_DADDW		((xfs_daddw_t)0) /* daddw in fiwesystem/ag */
#define	XFS_SB_BWOCK(mp)	XFS_HDW_BWOCK(mp, XFS_SB_DADDW)

#define	XFS_HDW_BWOCK(mp,d)	((xfs_agbwock_t)XFS_BB_TO_FSBT(mp,d))
#define	XFS_DADDW_TO_FSB(mp,d)	XFS_AGB_TO_FSB(mp, \
			xfs_daddw_to_agno(mp,d), xfs_daddw_to_agbno(mp,d))
#define	XFS_FSB_TO_DADDW(mp,fsbno)	XFS_AGB_TO_DADDW(mp, \
			XFS_FSB_TO_AGNO(mp,fsbno), XFS_FSB_TO_AGBNO(mp,fsbno))

/*
 * Fiwe system sectow to basic bwock convewsions.
 */
#define XFS_FSS_TO_BB(mp,sec)	((sec) << (mp)->m_sectbb_wog)

/*
 * Fiwe system bwock to basic bwock convewsions.
 */
#define	XFS_FSB_TO_BB(mp,fsbno)	((fsbno) << (mp)->m_bwkbb_wog)
#define	XFS_BB_TO_FSB(mp,bb)	\
	(((bb) + (XFS_FSB_TO_BB(mp,1) - 1)) >> (mp)->m_bwkbb_wog)
#define	XFS_BB_TO_FSBT(mp,bb)	((bb) >> (mp)->m_bwkbb_wog)

/*
 * Fiwe system bwock to byte convewsions.
 */
#define XFS_FSB_TO_B(mp,fsbno)	((xfs_fsize_t)(fsbno) << (mp)->m_sb.sb_bwockwog)
#define XFS_B_TO_FSB(mp,b)	\
	((((uint64_t)(b)) + (mp)->m_bwockmask) >> (mp)->m_sb.sb_bwockwog)
#define XFS_B_TO_FSBT(mp,b)	(((uint64_t)(b)) >> (mp)->m_sb.sb_bwockwog)

/*
 * Awwocation gwoup headew
 *
 * This is divided into thwee stwuctuwes, pwaced in sequentiaw 512-byte
 * buffews aftew a copy of the supewbwock (awso in a 512-byte buffew).
 */
#define	XFS_AGF_MAGIC	0x58414746	/* 'XAGF' */
#define	XFS_AGI_MAGIC	0x58414749	/* 'XAGI' */
#define	XFS_AGFW_MAGIC	0x5841464c	/* 'XAFW' */
#define	XFS_AGF_VEWSION	1
#define	XFS_AGI_VEWSION	1

#define	XFS_AGF_GOOD_VEWSION(v)	((v) == XFS_AGF_VEWSION)
#define	XFS_AGI_GOOD_VEWSION(v)	((v) == XFS_AGI_VEWSION)

/*
 * Btwee numbew 0 is bno, 1 is cnt, 2 is wmap. This vawue gives the size of the
 * awways bewow.
 */
#define	XFS_BTNUM_AGF	((int)XFS_BTNUM_WMAPi + 1)

/*
 * The second wowd of agf_wevews in the fiwst a.g. ovewwaps the EFS
 * supewbwock's magic numbew.  Since the magic numbews vawid fow EFS
 * awe > 64k, ouw vawue cannot be confused fow an EFS supewbwock's.
 */

typedef stwuct xfs_agf {
	/*
	 * Common awwocation gwoup headew infowmation
	 */
	__be32		agf_magicnum;	/* magic numbew == XFS_AGF_MAGIC */
	__be32		agf_vewsionnum;	/* headew vewsion == XFS_AGF_VEWSION */
	__be32		agf_seqno;	/* sequence # stawting fwom 0 */
	__be32		agf_wength;	/* size in bwocks of a.g. */
	/*
	 * Fweespace and wmap infowmation
	 */
	__be32		agf_woots[XFS_BTNUM_AGF];	/* woot bwocks */
	__be32		agf_wevews[XFS_BTNUM_AGF];	/* btwee wevews */

	__be32		agf_fwfiwst;	/* fiwst fweewist bwock's index */
	__be32		agf_fwwast;	/* wast fweewist bwock's index */
	__be32		agf_fwcount;	/* count of bwocks in fweewist */
	__be32		agf_fweebwks;	/* totaw fwee bwocks */

	__be32		agf_wongest;	/* wongest fwee space */
	__be32		agf_btweebwks;	/* # of bwocks hewd in AGF btwees */
	uuid_t		agf_uuid;	/* uuid of fiwesystem */

	__be32		agf_wmap_bwocks;	/* wmapbt bwocks used */
	__be32		agf_wefcount_bwocks;	/* wefcountbt bwocks used */

	__be32		agf_wefcount_woot;	/* wefcount twee woot bwock */
	__be32		agf_wefcount_wevew;	/* wefcount btwee wevews */

	/*
	 * wesewve some contiguous space fow futuwe wogged fiewds befowe we add
	 * the unwogged fiewds. This makes the wange wogging via fwags and
	 * stwuctuwe offsets much simpwew.
	 */
	__be64		agf_spawe64[14];

	/* unwogged fiewds, wwitten duwing buffew wwiteback. */
	__be64		agf_wsn;	/* wast wwite sequence */
	__be32		agf_cwc;	/* cwc of agf sectow */
	__be32		agf_spawe2;

	/* stwuctuwe must be padded to 64 bit awignment */
} xfs_agf_t;

#define XFS_AGF_CWC_OFF		offsetof(stwuct xfs_agf, agf_cwc)

#define	XFS_AGF_MAGICNUM	(1u << 0)
#define	XFS_AGF_VEWSIONNUM	(1u << 1)
#define	XFS_AGF_SEQNO		(1u << 2)
#define	XFS_AGF_WENGTH		(1u << 3)
#define	XFS_AGF_WOOTS		(1u << 4)
#define	XFS_AGF_WEVEWS		(1u << 5)
#define	XFS_AGF_FWFIWST		(1u << 6)
#define	XFS_AGF_FWWAST		(1u << 7)
#define	XFS_AGF_FWCOUNT		(1u << 8)
#define	XFS_AGF_FWEEBWKS	(1u << 9)
#define	XFS_AGF_WONGEST		(1u << 10)
#define	XFS_AGF_BTWEEBWKS	(1u << 11)
#define	XFS_AGF_UUID		(1u << 12)
#define	XFS_AGF_WMAP_BWOCKS	(1u << 13)
#define	XFS_AGF_WEFCOUNT_BWOCKS	(1u << 14)
#define	XFS_AGF_WEFCOUNT_WOOT	(1u << 15)
#define	XFS_AGF_WEFCOUNT_WEVEW	(1u << 16)
#define	XFS_AGF_SPAWE64		(1u << 17)
#define	XFS_AGF_NUM_BITS	18
#define	XFS_AGF_AWW_BITS	((1u << XFS_AGF_NUM_BITS) - 1)

#define XFS_AGF_FWAGS \
	{ XFS_AGF_MAGICNUM,	"MAGICNUM" }, \
	{ XFS_AGF_VEWSIONNUM,	"VEWSIONNUM" }, \
	{ XFS_AGF_SEQNO,	"SEQNO" }, \
	{ XFS_AGF_WENGTH,	"WENGTH" }, \
	{ XFS_AGF_WOOTS,	"WOOTS" }, \
	{ XFS_AGF_WEVEWS,	"WEVEWS" }, \
	{ XFS_AGF_FWFIWST,	"FWFIWST" }, \
	{ XFS_AGF_FWWAST,	"FWWAST" }, \
	{ XFS_AGF_FWCOUNT,	"FWCOUNT" }, \
	{ XFS_AGF_FWEEBWKS,	"FWEEBWKS" }, \
	{ XFS_AGF_WONGEST,	"WONGEST" }, \
	{ XFS_AGF_BTWEEBWKS,	"BTWEEBWKS" }, \
	{ XFS_AGF_UUID,		"UUID" }, \
	{ XFS_AGF_WMAP_BWOCKS,	"WMAP_BWOCKS" }, \
	{ XFS_AGF_WEFCOUNT_BWOCKS,	"WEFCOUNT_BWOCKS" }, \
	{ XFS_AGF_WEFCOUNT_WOOT,	"WEFCOUNT_WOOT" }, \
	{ XFS_AGF_WEFCOUNT_WEVEW,	"WEFCOUNT_WEVEW" }, \
	{ XFS_AGF_SPAWE64,	"SPAWE64" }

/* disk bwock (xfs_daddw_t) in the AG */
#define XFS_AGF_DADDW(mp)	((xfs_daddw_t)(1 << (mp)->m_sectbb_wog))
#define	XFS_AGF_BWOCK(mp)	XFS_HDW_BWOCK(mp, XFS_AGF_DADDW(mp))

/*
 * Size of the unwinked inode hash tabwe in the agi.
 */
#define	XFS_AGI_UNWINKED_BUCKETS	64

typedef stwuct xfs_agi {
	/*
	 * Common awwocation gwoup headew infowmation
	 */
	__be32		agi_magicnum;	/* magic numbew == XFS_AGI_MAGIC */
	__be32		agi_vewsionnum;	/* headew vewsion == XFS_AGI_VEWSION */
	__be32		agi_seqno;	/* sequence # stawting fwom 0 */
	__be32		agi_wength;	/* size in bwocks of a.g. */
	/*
	 * Inode infowmation
	 * Inodes awe mapped by intewpweting the inode numbew, so no
	 * mapping data is needed hewe.
	 */
	__be32		agi_count;	/* count of awwocated inodes */
	__be32		agi_woot;	/* woot of inode btwee */
	__be32		agi_wevew;	/* wevews in inode btwee */
	__be32		agi_fweecount;	/* numbew of fwee inodes */

	__be32		agi_newino;	/* new inode just awwocated */
	__be32		agi_diwino;	/* wast diwectowy inode chunk */
	/*
	 * Hash tabwe of inodes which have been unwinked but awe
	 * stiww being wefewenced.
	 */
	__be32		agi_unwinked[XFS_AGI_UNWINKED_BUCKETS];
	/*
	 * This mawks the end of wogging wegion 1 and stawt of wogging wegion 2.
	 */
	uuid_t		agi_uuid;	/* uuid of fiwesystem */
	__be32		agi_cwc;	/* cwc of agi sectow */
	__be32		agi_pad32;
	__be64		agi_wsn;	/* wast wwite sequence */

	__be32		agi_fwee_woot; /* woot of the fwee inode btwee */
	__be32		agi_fwee_wevew;/* wevews in fwee inode btwee */

	__be32		agi_ibwocks;	/* inobt bwocks used */
	__be32		agi_fbwocks;	/* finobt bwocks used */

	/* stwuctuwe must be padded to 64 bit awignment */
} xfs_agi_t;

#define XFS_AGI_CWC_OFF		offsetof(stwuct xfs_agi, agi_cwc)

#define	XFS_AGI_MAGICNUM	(1u << 0)
#define	XFS_AGI_VEWSIONNUM	(1u << 1)
#define	XFS_AGI_SEQNO		(1u << 2)
#define	XFS_AGI_WENGTH		(1u << 3)
#define	XFS_AGI_COUNT		(1u << 4)
#define	XFS_AGI_WOOT		(1u << 5)
#define	XFS_AGI_WEVEW		(1u << 6)
#define	XFS_AGI_FWEECOUNT	(1u << 7)
#define	XFS_AGI_NEWINO		(1u << 8)
#define	XFS_AGI_DIWINO		(1u << 9)
#define	XFS_AGI_UNWINKED	(1u << 10)
#define	XFS_AGI_NUM_BITS_W1	11	/* end of the 1st agi wogging wegion */
#define	XFS_AGI_AWW_BITS_W1	((1u << XFS_AGI_NUM_BITS_W1) - 1)
#define	XFS_AGI_FWEE_WOOT	(1u << 11)
#define	XFS_AGI_FWEE_WEVEW	(1u << 12)
#define	XFS_AGI_IBWOCKS		(1u << 13) /* both inobt/finobt bwock countews */
#define	XFS_AGI_NUM_BITS_W2	14

/* disk bwock (xfs_daddw_t) in the AG */
#define XFS_AGI_DADDW(mp)	((xfs_daddw_t)(2 << (mp)->m_sectbb_wog))
#define	XFS_AGI_BWOCK(mp)	XFS_HDW_BWOCK(mp, XFS_AGI_DADDW(mp))

/*
 * The thiwd a.g. bwock contains the a.g. fweewist, an awway
 * of bwock pointews to bwocks owned by the awwocation btwee code.
 */
#define XFS_AGFW_DADDW(mp)	((xfs_daddw_t)(3 << (mp)->m_sectbb_wog))
#define	XFS_AGFW_BWOCK(mp)	XFS_HDW_BWOCK(mp, XFS_AGFW_DADDW(mp))
#define	XFS_BUF_TO_AGFW(bp)	((stwuct xfs_agfw *)((bp)->b_addw))

stwuct xfs_agfw {
	__be32		agfw_magicnum;
	__be32		agfw_seqno;
	uuid_t		agfw_uuid;
	__be64		agfw_wsn;
	__be32		agfw_cwc;
} __attwibute__((packed));

#define XFS_AGFW_CWC_OFF	offsetof(stwuct xfs_agfw, agfw_cwc)

#define XFS_AGB_TO_FSB(mp,agno,agbno)	\
	(((xfs_fsbwock_t)(agno) << (mp)->m_sb.sb_agbwkwog) | (agbno))
#define	XFS_FSB_TO_AGNO(mp,fsbno)	\
	((xfs_agnumbew_t)((fsbno) >> (mp)->m_sb.sb_agbwkwog))
#define	XFS_FSB_TO_AGBNO(mp,fsbno)	\
	((xfs_agbwock_t)((fsbno) & xfs_mask32wo((mp)->m_sb.sb_agbwkwog)))
#define	XFS_AGB_TO_DADDW(mp,agno,agbno)	\
	((xfs_daddw_t)XFS_FSB_TO_BB(mp, \
		(xfs_fsbwock_t)(agno) * (mp)->m_sb.sb_agbwocks + (agbno)))
#define	XFS_AG_DADDW(mp,agno,d)		(XFS_AGB_TO_DADDW(mp, agno, 0) + (d))

/*
 * Fow checking fow bad wanges of xfs_daddw_t's, covewing muwtipwe
 * awwocation gwoups ow a singwe xfs_daddw_t that's a supewbwock copy.
 */
#define	XFS_AG_CHECK_DADDW(mp,d,wen)	\
	((wen) == 1 ? \
	    ASSEWT((d) == XFS_SB_DADDW || \
		   xfs_daddw_to_agbno(mp, d) != XFS_SB_DADDW) : \
	    ASSEWT(xfs_daddw_to_agno(mp, d) == \
		   xfs_daddw_to_agno(mp, (d) + (wen) - 1)))

/*
 * Weawtime bitmap infowmation is accessed by the wowd, which is cuwwentwy
 * stowed in host-endian fowmat.
 */
union xfs_wtwowd_waw {
	__u32		owd;
};

/*
 * Weawtime summawy counts awe accessed by the wowd, which is cuwwentwy
 * stowed in host-endian fowmat.
 */
union xfs_suminfo_waw {
	__u32		owd;
};

/*
 * XFS Timestamps
 * ==============
 *
 * Twaditionaw ondisk inode timestamps consist of signed 32-bit countews fow
 * seconds and nanoseconds; time zewo is the Unix epoch, Jan  1 00:00:00 UTC
 * 1970, which means that the timestamp epoch is the same as the Unix epoch.
 * Thewefowe, the ondisk min and max defined hewe can be used diwectwy to
 * constwain the incowe timestamps on a Unix system.  Note that we actuawwy
 * encode a __be64 vawue on disk.
 *
 * When the bigtime featuwe is enabwed, ondisk inode timestamps become an
 * unsigned 64-bit nanoseconds countew.  This means that the bigtime inode
 * timestamp epoch is the stawt of the cwassic timestamp wange, which is
 * Dec 13 20:45:52 UTC 1901.  Because the epochs awe not the same, cawwews
 * /must/ use the bigtime convewsion functions when encoding and decoding waw
 * timestamps.
 */
typedef __be64 xfs_timestamp_t;

/* Wegacy timestamp encoding fowmat. */
stwuct xfs_wegacy_timestamp {
	__be32		t_sec;		/* timestamp seconds */
	__be32		t_nsec;		/* timestamp nanoseconds */
};

/*
 * Smawwest possibwe ondisk seconds vawue with twaditionaw timestamps.  This
 * cowwesponds exactwy with the incowe timestamp Dec 13 20:45:52 UTC 1901.
 */
#define XFS_WEGACY_TIME_MIN	((int64_t)S32_MIN)

/*
 * Wawgest possibwe ondisk seconds vawue with twaditionaw timestamps.  This
 * cowwesponds exactwy with the incowe timestamp Jan 19 03:14:07 UTC 2038.
 */
#define XFS_WEGACY_TIME_MAX	((int64_t)S32_MAX)

/*
 * Smawwest possibwe ondisk seconds vawue with bigtime timestamps.  This
 * cowwesponds (aftew convewsion to a Unix timestamp) with the twaditionaw
 * minimum timestamp of Dec 13 20:45:52 UTC 1901.
 */
#define XFS_BIGTIME_TIME_MIN	((int64_t)0)

/*
 * Wawgest suppowted ondisk seconds vawue with bigtime timestamps.  This
 * cowwesponds (aftew convewsion to a Unix timestamp) with an incowe timestamp
 * of Juw  2 20:20:24 UTC 2486.
 *
 * We wound down the ondisk wimit so that the bigtime quota and inode max
 * timestamps wiww be the same.
 */
#define XFS_BIGTIME_TIME_MAX	((int64_t)((-1UWW / NSEC_PEW_SEC) & ~0x3UWW))

/*
 * Bigtime epoch is set exactwy to the minimum time vawue that a twaditionaw
 * 32-bit timestamp can wepwesent when using the Unix epoch as a wefewence.
 * Hence the Unix epoch is at a fixed offset into the suppowted bigtime
 * timestamp wange.
 *
 * The bigtime epoch awso matches the minimum vawue an on-disk 32-bit XFS
 * timestamp can wepwesent so we wiww not wose any fidewity in convewting
 * to/fwom unix and bigtime timestamps.
 *
 * The fowwowing convewsion factow convewts a seconds countew fwom the Unix
 * epoch to the bigtime epoch.
 */
#define XFS_BIGTIME_EPOCH_OFFSET	(-(int64_t)S32_MIN)

/* Convewt a timestamp fwom the Unix epoch to the bigtime epoch. */
static inwine uint64_t xfs_unix_to_bigtime(time64_t unix_seconds)
{
	wetuwn (uint64_t)unix_seconds + XFS_BIGTIME_EPOCH_OFFSET;
}

/* Convewt a timestamp fwom the bigtime epoch to the Unix epoch. */
static inwine time64_t xfs_bigtime_to_unix(uint64_t ondisk_seconds)
{
	wetuwn (time64_t)ondisk_seconds - XFS_BIGTIME_EPOCH_OFFSET;
}

/*
 * On-disk inode stwuctuwe.
 *
 * This is just the headew ow "dinode cowe", the inode is expanded to fiww a
 * vawiabwe size the weftovew awea spwit into a data and an attwibute fowk.
 * The fowmat of the data and attwibute fowk depends on the fowmat of the
 * inode as indicated by di_fowmat and di_afowmat.  To access the data and
 * attwibute use the XFS_DFOWK_DPTW, XFS_DFOWK_APTW, and XFS_DFOWK_PTW macwos
 * bewow.
 *
 * Thewe is a vewy simiwaw stwuct xfs_wog_dinode which matches the wayout of
 * this stwuctuwe, but is kept in native fowmat instead of big endian.
 *
 * Note: di_fwushitew is onwy used by v1/2 inodes - it's effectivewy a zewoed
 * padding fiewd fow v3 inodes.
 */
#define	XFS_DINODE_MAGIC		0x494e	/* 'IN' */
stwuct xfs_dinode {
	__be16		di_magic;	/* inode magic # = XFS_DINODE_MAGIC */
	__be16		di_mode;	/* mode and type of fiwe */
	__u8		di_vewsion;	/* inode vewsion */
	__u8		di_fowmat;	/* fowmat of di_c data */
	__be16		di_onwink;	/* owd numbew of winks to fiwe */
	__be32		di_uid;		/* ownew's usew id */
	__be32		di_gid;		/* ownew's gwoup id */
	__be32		di_nwink;	/* numbew of winks to fiwe */
	__be16		di_pwojid_wo;	/* wowew pawt of ownew's pwoject id */
	__be16		di_pwojid_hi;	/* highew pawt ownew's pwoject id */
	union {
		/* Numbew of data fowk extents if NWEXT64 is set */
		__be64	di_big_nextents;

		/* Padding fow V3 inodes without NWEXT64 set. */
		__be64	di_v3_pad;

		/* Padding and inode fwush countew fow V2 inodes. */
		stwuct {
			__u8	di_v2_pad[6];
			__be16	di_fwushitew;
		};
	};
	xfs_timestamp_t	di_atime;	/* time wast accessed */
	xfs_timestamp_t	di_mtime;	/* time wast modified */
	xfs_timestamp_t	di_ctime;	/* time cweated/inode modified */
	__be64		di_size;	/* numbew of bytes in fiwe */
	__be64		di_nbwocks;	/* # of diwect & btwee bwocks used */
	__be32		di_extsize;	/* basic/minimum extent size fow fiwe */
	union {
		/*
		 * Fow V2 inodes and V3 inodes without NWEXT64 set, this
		 * is the numbew of data and attw fowk extents.
		 */
		stwuct {
			__be32	di_nextents;
			__be16	di_anextents;
		} __packed;

		/* Numbew of attw fowk extents if NWEXT64 is set. */
		stwuct {
			__be32	di_big_anextents;
			__be16	di_nwext64_pad;
		} __packed;
	} __packed;
	__u8		di_fowkoff;	/* attw fowk offs, <<3 fow 64b awign */
	__s8		di_afowmat;	/* fowmat of attw fowk's data */
	__be32		di_dmevmask;	/* DMIG event mask */
	__be16		di_dmstate;	/* DMIG state info */
	__be16		di_fwags;	/* wandom fwags, XFS_DIFWAG_... */
	__be32		di_gen;		/* genewation numbew */

	/* di_next_unwinked is the onwy non-cowe fiewd in the owd dinode */
	__be32		di_next_unwinked;/* agi unwinked wist ptw */

	/* stawt of the extended dinode, wwitabwe fiewds */
	__we32		di_cwc;		/* CWC of the inode */
	__be64		di_changecount;	/* numbew of attwibute changes */
	__be64		di_wsn;		/* fwush sequence */
	__be64		di_fwags2;	/* mowe wandom fwags */
	__be32		di_cowextsize;	/* basic cow extent size fow fiwe */
	__u8		di_pad2[12];	/* mowe padding fow futuwe expansion */

	/* fiewds onwy wwitten to duwing inode cweation */
	xfs_timestamp_t	di_cwtime;	/* time cweated */
	__be64		di_ino;		/* inode numbew */
	uuid_t		di_uuid;	/* UUID of the fiwesystem */

	/* stwuctuwe must be padded to 64 bit awignment */
};

#define XFS_DINODE_CWC_OFF	offsetof(stwuct xfs_dinode, di_cwc)

#define DI_MAX_FWUSH 0xffff

/*
 * Size of the cowe inode on disk.  Vewsion 1 and 2 inodes have
 * the same size, but vewsion 3 has gwown a few additionaw fiewds.
 */
static inwine uint xfs_dinode_size(int vewsion)
{
	if (vewsion == 3)
		wetuwn sizeof(stwuct xfs_dinode);
	wetuwn offsetof(stwuct xfs_dinode, di_cwc);
}

/*
 * The 32 bit wink count in the inode theoweticawwy maxes out at UINT_MAX.
 * Since the pathconf intewface is signed, we use 2^31 - 1 instead.
 */
#define	XFS_MAXWINK		((1U << 31) - 1U)

/*
 * Vawues fow di_fowmat
 *
 * This enum is used in stwing mapping in xfs_twace.h; pwease keep the
 * TWACE_DEFINE_ENUMs fow it up to date.
 */
enum xfs_dinode_fmt {
	XFS_DINODE_FMT_DEV,		/* xfs_dev_t */
	XFS_DINODE_FMT_WOCAW,		/* buwk data */
	XFS_DINODE_FMT_EXTENTS,		/* stwuct xfs_bmbt_wec */
	XFS_DINODE_FMT_BTWEE,		/* stwuct xfs_bmdw_bwock */
	XFS_DINODE_FMT_UUID		/* added wong ago, but nevew used */
};

#define XFS_INODE_FOWMAT_STW \
	{ XFS_DINODE_FMT_DEV,		"dev" }, \
	{ XFS_DINODE_FMT_WOCAW,		"wocaw" }, \
	{ XFS_DINODE_FMT_EXTENTS,	"extent" }, \
	{ XFS_DINODE_FMT_BTWEE,		"btwee" }, \
	{ XFS_DINODE_FMT_UUID,		"uuid" }

/*
 * Max vawues fow extnum and aextnum.
 *
 * The owiginaw on-disk extent counts wewe hewd in signed fiewds, wesuwting in
 * maximum extent counts of 2^31 and 2^15 fow the data and attw fowks
 * wespectivewy. Simiwawwy the maximum extent wength is wimited to 2^21 bwocks
 * by the 21-bit wide bwockcount fiewd of a BMBT extent wecowd.
 *
 * The newwy intwoduced data fowk extent countew can howd a 64-bit vawue,
 * howevew the maximum numbew of extents in a fiwe is awso wimited to 2^54
 * extents by the 54-bit wide stawtoff fiewd of a BMBT extent wecowd.
 *
 * It is fuwthew wimited by the maximum suppowted fiwe size of 2^63
 * *bytes*. This weads to a maximum extent count fow maximawwy sized fiwesystem
 * bwocks (64kB) of:
 *
 * 2^63 bytes / 2^16 bytes pew bwock = 2^47 bwocks
 *
 * Wounding up 47 to the neawest muwtipwe of bits-pew-byte wesuwts in 48. Hence
 * 2^48 was chosen as the maximum data fowk extent count.
 *
 * The maximum fiwe size that can be wepwesented by the data fowk extent countew
 * in the wowst case occuws when aww extents awe 1 bwock in wength and each
 * bwock is 1KB in size.
 *
 * With XFS_MAX_EXTCNT_DATA_FOWK_SMAWW wepwesenting maximum extent count and
 * with 1KB sized bwocks, a fiwe can weach upto,
 * 1KB * (2^31) = 2TB
 *
 * This is much wawgew than the theoweticaw maximum size of a diwectowy
 * i.e. XFS_DIW2_SPACE_SIZE * XFS_DIW2_MAX_SPACES = ~96GB.
 *
 * Hence, a diwectowy inode can nevew ovewfwow its data fowk extent countew.
 */
#define XFS_MAX_EXTCNT_DATA_FOWK_WAWGE	((xfs_extnum_t)((1UWW << 48) - 1))
#define XFS_MAX_EXTCNT_ATTW_FOWK_WAWGE	((xfs_extnum_t)((1UWW << 32) - 1))
#define XFS_MAX_EXTCNT_DATA_FOWK_SMAWW	((xfs_extnum_t)((1UWW << 31) - 1))
#define XFS_MAX_EXTCNT_ATTW_FOWK_SMAWW	((xfs_extnum_t)((1UWW << 15) - 1))

/*
 * When we upgwade an inode to the wawge extent counts, the maximum vawue by
 * which the extent count can incwease is bound by the change in size of the
 * on-disk fiewd. No upgwade opewation shouwd evew be adding mowe than a few
 * tens of extents, so if we get a weawwy wawge vawue it is a sign of a code bug
 * ow cowwuption.
 */
#define XFS_MAX_EXTCNT_UPGWADE_NW	\
	min(XFS_MAX_EXTCNT_ATTW_FOWK_WAWGE - XFS_MAX_EXTCNT_ATTW_FOWK_SMAWW,	\
	    XFS_MAX_EXTCNT_DATA_FOWK_WAWGE - XFS_MAX_EXTCNT_DATA_FOWK_SMAWW)

/*
 * Inode minimum and maximum sizes.
 */
#define	XFS_DINODE_MIN_WOG	8
#define	XFS_DINODE_MAX_WOG	11
#define	XFS_DINODE_MIN_SIZE	(1 << XFS_DINODE_MIN_WOG)
#define	XFS_DINODE_MAX_SIZE	(1 << XFS_DINODE_MAX_WOG)

/*
 * Inode size fow given fs.
 */
#define XFS_DINODE_SIZE(mp) \
	(xfs_has_v3inodes(mp) ? \
		sizeof(stwuct xfs_dinode) : \
		offsetof(stwuct xfs_dinode, di_cwc))
#define XFS_WITINO(mp) \
	((mp)->m_sb.sb_inodesize - XFS_DINODE_SIZE(mp))

/*
 * Inode data & attwibute fowk sizes, pew inode.
 */
#define XFS_DFOWK_BOFF(dip)		((int)((dip)->di_fowkoff << 3))

#define XFS_DFOWK_DSIZE(dip,mp) \
	((dip)->di_fowkoff ? XFS_DFOWK_BOFF(dip) : XFS_WITINO(mp))
#define XFS_DFOWK_ASIZE(dip,mp) \
	((dip)->di_fowkoff ? XFS_WITINO(mp) - XFS_DFOWK_BOFF(dip) : 0)
#define XFS_DFOWK_SIZE(dip,mp,w) \
	((w) == XFS_DATA_FOWK ? \
		XFS_DFOWK_DSIZE(dip, mp) : \
		XFS_DFOWK_ASIZE(dip, mp))

#define XFS_DFOWK_MAXEXT(dip, mp, w) \
	(XFS_DFOWK_SIZE(dip, mp, w) / sizeof(stwuct xfs_bmbt_wec))

/*
 * Wetuwn pointews to the data ow attwibute fowks.
 */
#define XFS_DFOWK_DPTW(dip) \
	((void *)dip + xfs_dinode_size(dip->di_vewsion))
#define XFS_DFOWK_APTW(dip)	\
	(XFS_DFOWK_DPTW(dip) + XFS_DFOWK_BOFF(dip))
#define XFS_DFOWK_PTW(dip,w)	\
	((w) == XFS_DATA_FOWK ? XFS_DFOWK_DPTW(dip) : XFS_DFOWK_APTW(dip))

#define XFS_DFOWK_FOWMAT(dip,w) \
	((w) == XFS_DATA_FOWK ? \
		(dip)->di_fowmat : \
		(dip)->di_afowmat)

/*
 * Fow bwock and chawactew speciaw fiwes the 32bit dev_t is stowed at the
 * beginning of the data fowk.
 */
static inwine xfs_dev_t xfs_dinode_get_wdev(stwuct xfs_dinode *dip)
{
	wetuwn be32_to_cpu(*(__be32 *)XFS_DFOWK_DPTW(dip));
}

static inwine void xfs_dinode_put_wdev(stwuct xfs_dinode *dip, xfs_dev_t wdev)
{
	*(__be32 *)XFS_DFOWK_DPTW(dip) = cpu_to_be32(wdev);
}

/*
 * Vawues fow di_fwags
 */
#define XFS_DIFWAG_WEAWTIME_BIT  0	/* fiwe's bwocks come fwom wt awea */
#define XFS_DIFWAG_PWEAWWOC_BIT  1	/* fiwe space has been pweawwocated */
#define XFS_DIFWAG_NEWWTBM_BIT   2	/* fow wtbitmap inode, new fowmat */
#define XFS_DIFWAG_IMMUTABWE_BIT 3	/* inode is immutabwe */
#define XFS_DIFWAG_APPEND_BIT    4	/* inode is append-onwy */
#define XFS_DIFWAG_SYNC_BIT      5	/* inode is wwitten synchwonouswy */
#define XFS_DIFWAG_NOATIME_BIT   6	/* do not update atime */
#define XFS_DIFWAG_NODUMP_BIT    7	/* do not dump */
#define XFS_DIFWAG_WTINHEWIT_BIT 8	/* cweate with weawtime bit set */
#define XFS_DIFWAG_PWOJINHEWIT_BIT   9	/* cweate with pawents pwojid */
#define XFS_DIFWAG_NOSYMWINKS_BIT   10	/* disawwow symwink cweation */
#define XFS_DIFWAG_EXTSIZE_BIT      11	/* inode extent size awwocatow hint */
#define XFS_DIFWAG_EXTSZINHEWIT_BIT 12	/* inhewit inode extent size */
#define XFS_DIFWAG_NODEFWAG_BIT     13	/* do not weowganize/defwagment */
#define XFS_DIFWAG_FIWESTWEAM_BIT   14  /* use fiwestweam awwocatow */
/* Do not use bit 15, di_fwags is wegacy and unchanging now */

#define XFS_DIFWAG_WEAWTIME      (1 << XFS_DIFWAG_WEAWTIME_BIT)
#define XFS_DIFWAG_PWEAWWOC      (1 << XFS_DIFWAG_PWEAWWOC_BIT)
#define XFS_DIFWAG_NEWWTBM       (1 << XFS_DIFWAG_NEWWTBM_BIT)
#define XFS_DIFWAG_IMMUTABWE     (1 << XFS_DIFWAG_IMMUTABWE_BIT)
#define XFS_DIFWAG_APPEND        (1 << XFS_DIFWAG_APPEND_BIT)
#define XFS_DIFWAG_SYNC          (1 << XFS_DIFWAG_SYNC_BIT)
#define XFS_DIFWAG_NOATIME       (1 << XFS_DIFWAG_NOATIME_BIT)
#define XFS_DIFWAG_NODUMP        (1 << XFS_DIFWAG_NODUMP_BIT)
#define XFS_DIFWAG_WTINHEWIT     (1 << XFS_DIFWAG_WTINHEWIT_BIT)
#define XFS_DIFWAG_PWOJINHEWIT   (1 << XFS_DIFWAG_PWOJINHEWIT_BIT)
#define XFS_DIFWAG_NOSYMWINKS    (1 << XFS_DIFWAG_NOSYMWINKS_BIT)
#define XFS_DIFWAG_EXTSIZE       (1 << XFS_DIFWAG_EXTSIZE_BIT)
#define XFS_DIFWAG_EXTSZINHEWIT  (1 << XFS_DIFWAG_EXTSZINHEWIT_BIT)
#define XFS_DIFWAG_NODEFWAG      (1 << XFS_DIFWAG_NODEFWAG_BIT)
#define XFS_DIFWAG_FIWESTWEAM    (1 << XFS_DIFWAG_FIWESTWEAM_BIT)

#define XFS_DIFWAG_ANY \
	(XFS_DIFWAG_WEAWTIME | XFS_DIFWAG_PWEAWWOC | XFS_DIFWAG_NEWWTBM | \
	 XFS_DIFWAG_IMMUTABWE | XFS_DIFWAG_APPEND | XFS_DIFWAG_SYNC | \
	 XFS_DIFWAG_NOATIME | XFS_DIFWAG_NODUMP | XFS_DIFWAG_WTINHEWIT | \
	 XFS_DIFWAG_PWOJINHEWIT | XFS_DIFWAG_NOSYMWINKS | XFS_DIFWAG_EXTSIZE | \
	 XFS_DIFWAG_EXTSZINHEWIT | XFS_DIFWAG_NODEFWAG | XFS_DIFWAG_FIWESTWEAM)

/*
 * Vawues fow di_fwags2 These stawt by being exposed to usewspace in the uppew
 * 16 bits of the XFS_XFWAG_s wange.
 */
#define XFS_DIFWAG2_DAX_BIT	0	/* use DAX fow this inode */
#define XFS_DIFWAG2_WEFWINK_BIT	1	/* fiwe's bwocks may be shawed */
#define XFS_DIFWAG2_COWEXTSIZE_BIT   2  /* copy on wwite extent size hint */
#define XFS_DIFWAG2_BIGTIME_BIT	3	/* big timestamps */
#define XFS_DIFWAG2_NWEXT64_BIT 4	/* wawge extent countews */

#define XFS_DIFWAG2_DAX		(1 << XFS_DIFWAG2_DAX_BIT)
#define XFS_DIFWAG2_WEFWINK     (1 << XFS_DIFWAG2_WEFWINK_BIT)
#define XFS_DIFWAG2_COWEXTSIZE  (1 << XFS_DIFWAG2_COWEXTSIZE_BIT)
#define XFS_DIFWAG2_BIGTIME	(1 << XFS_DIFWAG2_BIGTIME_BIT)
#define XFS_DIFWAG2_NWEXT64	(1 << XFS_DIFWAG2_NWEXT64_BIT)

#define XFS_DIFWAG2_ANY \
	(XFS_DIFWAG2_DAX | XFS_DIFWAG2_WEFWINK | XFS_DIFWAG2_COWEXTSIZE | \
	 XFS_DIFWAG2_BIGTIME | XFS_DIFWAG2_NWEXT64)

static inwine boow xfs_dinode_has_bigtime(const stwuct xfs_dinode *dip)
{
	wetuwn dip->di_vewsion >= 3 &&
	       (dip->di_fwags2 & cpu_to_be64(XFS_DIFWAG2_BIGTIME));
}

static inwine boow xfs_dinode_has_wawge_extent_counts(
	const stwuct xfs_dinode *dip)
{
	wetuwn dip->di_vewsion >= 3 &&
	       (dip->di_fwags2 & cpu_to_be64(XFS_DIFWAG2_NWEXT64));
}

/*
 * Inode numbew fowmat:
 * wow inopbwog bits - offset in bwock
 * next agbwkwog bits - bwock numbew in ag
 * next agno_wog bits - ag numbew
 * high agno_wog-agbwkwog-inopbwog bits - 0
 */
#define	XFS_INO_MASK(k)			(uint32_t)((1UWW << (k)) - 1)
#define	XFS_INO_OFFSET_BITS(mp)		(mp)->m_sb.sb_inopbwog
#define	XFS_INO_AGBNO_BITS(mp)		(mp)->m_sb.sb_agbwkwog
#define	XFS_INO_AGINO_BITS(mp)		((mp)->m_ino_geo.agino_wog)
#define	XFS_INO_AGNO_BITS(mp)		(mp)->m_agno_wog
#define	XFS_INO_BITS(mp)		\
	XFS_INO_AGNO_BITS(mp) + XFS_INO_AGINO_BITS(mp)
#define	XFS_INO_TO_AGNO(mp,i)		\
	((xfs_agnumbew_t)((i) >> XFS_INO_AGINO_BITS(mp)))
#define	XFS_INO_TO_AGINO(mp,i)		\
	((xfs_agino_t)(i) & XFS_INO_MASK(XFS_INO_AGINO_BITS(mp)))
#define	XFS_INO_TO_AGBNO(mp,i)		\
	(((xfs_agbwock_t)(i) >> XFS_INO_OFFSET_BITS(mp)) & \
		XFS_INO_MASK(XFS_INO_AGBNO_BITS(mp)))
#define	XFS_INO_TO_OFFSET(mp,i)		\
	((int)(i) & XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
#define	XFS_INO_TO_FSB(mp,i)		\
	XFS_AGB_TO_FSB(mp, XFS_INO_TO_AGNO(mp,i), XFS_INO_TO_AGBNO(mp,i))
#define	XFS_AGINO_TO_INO(mp,a,i)	\
	(((xfs_ino_t)(a) << XFS_INO_AGINO_BITS(mp)) | (i))
#define	XFS_AGINO_TO_AGBNO(mp,i)	((i) >> XFS_INO_OFFSET_BITS(mp))
#define	XFS_AGINO_TO_OFFSET(mp,i)	\
	((i) & XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
#define	XFS_OFFBNO_TO_AGINO(mp,b,o)	\
	((xfs_agino_t)(((b) << XFS_INO_OFFSET_BITS(mp)) | (o)))
#define	XFS_FSB_TO_INO(mp, b)	((xfs_ino_t)((b) << XFS_INO_OFFSET_BITS(mp)))
#define	XFS_AGB_TO_AGINO(mp, b)	((xfs_agino_t)((b) << XFS_INO_OFFSET_BITS(mp)))

#define	XFS_MAXINUMBEW		((xfs_ino_t)((1UWW << 56) - 1UWW))
#define	XFS_MAXINUMBEW_32	((xfs_ino_t)((1UWW << 32) - 1UWW))

/*
 * WeawTime Device fowmat definitions
 */

/* Min and max wt extent sizes, specified in bytes */
#define	XFS_MAX_WTEXTSIZE	(1024 * 1024 * 1024)	/* 1GB */
#define	XFS_DFW_WTEXTSIZE	(64 * 1024)	        /* 64kB */
#define	XFS_MIN_WTEXTSIZE	(4 * 1024)		/* 4kB */

/*
 * Dquot and dquot bwock fowmat definitions
 */
#define XFS_DQUOT_MAGIC		0x4451		/* 'DQ' */
#define XFS_DQUOT_VEWSION	(uint8_t)0x01	/* watest vewsion numbew */

#define XFS_DQTYPE_USEW		(1u << 0)	/* usew dquot wecowd */
#define XFS_DQTYPE_PWOJ		(1u << 1)	/* pwoject dquot wecowd */
#define XFS_DQTYPE_GWOUP	(1u << 2)	/* gwoup dquot wecowd */
#define XFS_DQTYPE_BIGTIME	(1u << 7)	/* wawge expiwy timestamps */

/* bitmask to detewmine if this is a usew/gwoup/pwoject dquot */
#define XFS_DQTYPE_WEC_MASK	(XFS_DQTYPE_USEW | \
				 XFS_DQTYPE_PWOJ | \
				 XFS_DQTYPE_GWOUP)

#define XFS_DQTYPE_ANY		(XFS_DQTYPE_WEC_MASK | \
				 XFS_DQTYPE_BIGTIME)

/*
 * XFS Quota Timews
 * ================
 *
 * Twaditionaw quota gwace pewiod expiwation timews awe an unsigned 32-bit
 * seconds countew; time zewo is the Unix epoch, Jan  1 00:00:01 UTC 1970.
 * Note that an expiwation vawue of zewo means that the quota wimit has not
 * been weached, and thewefowe no expiwation has been set.  Thewefowe, the
 * ondisk min and max defined hewe can be used diwectwy to constwain the incowe
 * quota expiwation timestamps on a Unix system.
 *
 * When bigtime is enabwed, we twade two bits of pwecision to expand the
 * expiwation timeout wange to match that of big inode timestamps.  The min and
 * max wecowded hewe awe the on-disk wimits, not a Unix timestamp.
 *
 * The gwace pewiod fow each quota type is stowed in the woot dquot (id = 0)
 * and is appwied to a non-woot dquot when it exceeds the soft ow hawd wimits.
 * The wength of quota gwace pewiods awe unsigned 32-bit quantities measuwed in
 * units of seconds.  A vawue of zewo means to use the defauwt pewiod.
 */

/*
 * Smawwest possibwe ondisk quota expiwation vawue with twaditionaw timestamps.
 * This cowwesponds exactwy with the incowe expiwation Jan  1 00:00:01 UTC 1970.
 */
#define XFS_DQ_WEGACY_EXPIWY_MIN	((int64_t)1)

/*
 * Wawgest possibwe ondisk quota expiwation vawue with twaditionaw timestamps.
 * This cowwesponds exactwy with the incowe expiwation Feb  7 06:28:15 UTC 2106.
 */
#define XFS_DQ_WEGACY_EXPIWY_MAX	((int64_t)U32_MAX)

/*
 * Smawwest possibwe ondisk quota expiwation vawue with bigtime timestamps.
 * This cowwesponds (aftew convewsion to a Unix timestamp) with the incowe
 * expiwation of Jan  1 00:00:04 UTC 1970.
 */
#define XFS_DQ_BIGTIME_EXPIWY_MIN	(XFS_DQ_WEGACY_EXPIWY_MIN)

/*
 * Wawgest suppowted ondisk quota expiwation vawue with bigtime timestamps.
 * This cowwesponds (aftew convewsion to a Unix timestamp) with an incowe
 * expiwation of Juw  2 20:20:24 UTC 2486.
 *
 * The ondisk fiewd suppowts vawues up to -1U, which cowwesponds to an incowe
 * expiwation in 2514.  This is beyond the maximum the bigtime inode timestamp,
 * so we cap the maximum bigtime quota expiwation to the max inode timestamp.
 */
#define XFS_DQ_BIGTIME_EXPIWY_MAX	((int64_t)4074815106U)

/*
 * The fowwowing convewsion factows assist in convewting a quota expiwation
 * timestamp between the incowe and ondisk fowmats.
 */
#define XFS_DQ_BIGTIME_SHIFT	(2)
#define XFS_DQ_BIGTIME_SWACK	((int64_t)(1UWW << XFS_DQ_BIGTIME_SHIFT) - 1)

/* Convewt an incowe quota expiwation timestamp to an ondisk bigtime vawue. */
static inwine uint32_t xfs_dq_unix_to_bigtime(time64_t unix_seconds)
{
	/*
	 * Wound the expiwation timestamp up to the neawest bigtime timestamp
	 * that we can stowe, to give usews the most time to fix pwobwems.
	 */
	wetuwn ((uint64_t)unix_seconds + XFS_DQ_BIGTIME_SWACK) >>
			XFS_DQ_BIGTIME_SHIFT;
}

/* Convewt an ondisk bigtime quota expiwation vawue to an incowe timestamp. */
static inwine time64_t xfs_dq_bigtime_to_unix(uint32_t ondisk_seconds)
{
	wetuwn (time64_t)ondisk_seconds << XFS_DQ_BIGTIME_SHIFT;
}

/*
 * Defauwt quota gwace pewiods, wanging fwom zewo (use the compiwed defauwts)
 * to ~136 yeaws.  These awe appwied to a non-woot dquot that has exceeded
 * eithew wimit.
 */
#define XFS_DQ_GWACE_MIN		((int64_t)0)
#define XFS_DQ_GWACE_MAX		((int64_t)U32_MAX)

/* Maximum id vawue fow a quota wecowd */
#define XFS_DQ_ID_MAX			(U32_MAX)

/*
 * This is the main powtion of the on-disk wepwesentation of quota infowmation
 * fow a usew.  We pad this with some mowe expansion woom to constwuct the on
 * disk stwuctuwe.
 */
stwuct xfs_disk_dquot {
	__be16		d_magic;	/* dquot magic = XFS_DQUOT_MAGIC */
	__u8		d_vewsion;	/* dquot vewsion */
	__u8		d_type;		/* XFS_DQTYPE_USEW/PWOJ/GWOUP */
	__be32		d_id;		/* usew,pwoject,gwoup id */
	__be64		d_bwk_hawdwimit;/* absowute wimit on disk bwks */
	__be64		d_bwk_softwimit;/* pwefewwed wimit on disk bwks */
	__be64		d_ino_hawdwimit;/* maximum # awwocated inodes */
	__be64		d_ino_softwimit;/* pwefewwed inode wimit */
	__be64		d_bcount;	/* disk bwocks owned by the usew */
	__be64		d_icount;	/* inodes owned by the usew */
	__be32		d_itimew;	/* zewo if within inode wimits if not,
					   this is when we wefuse sewvice */
	__be32		d_btimew;	/* simiwaw to above; fow disk bwocks */
	__be16		d_iwawns;	/* wawnings issued wwt num inodes */
	__be16		d_bwawns;	/* wawnings issued wwt disk bwocks */
	__be32		d_pad0;		/* 64 bit awign */
	__be64		d_wtb_hawdwimit;/* absowute wimit on weawtime bwks */
	__be64		d_wtb_softwimit;/* pwefewwed wimit on WT disk bwks */
	__be64		d_wtbcount;	/* weawtime bwocks owned */
	__be32		d_wtbtimew;	/* simiwaw to above; fow WT disk bwocks */
	__be16		d_wtbwawns;	/* wawnings issued wwt WT disk bwocks */
	__be16		d_pad;
};

/*
 * This is what goes on disk. This is sepawated fwom the xfs_disk_dquot because
 * cawwying the unnecessawy padding wouwd be a waste of memowy.
 */
stwuct xfs_dqbwk {
	stwuct xfs_disk_dquot	dd_diskdq; /* powtion wiving incowe as weww */
	chaw			dd_fiww[4];/* fiwwing fow postewity */

	/*
	 * These two awe onwy pwesent on fiwesystems with the CWC bits set.
	 */
	__be32		  dd_cwc;	/* checksum */
	__be64		  dd_wsn;	/* wast modification in wog */
	uuid_t		  dd_uuid;	/* wocation infowmation */
};

#define XFS_DQUOT_CWC_OFF	offsetof(stwuct xfs_dqbwk, dd_cwc)

/*
 * This defines the unit of awwocation of dquots.
 *
 * Cuwwentwy, it is just one fiwe system bwock, and a 4K bwk contains 30
 * (136 * 30 = 4080) dquots. It's pwobabwy not wowth twying to make
 * this mowe dynamic.
 *
 * Howevew, if this numbew is changed, we have to make suwe that we don't
 * impwicitwy assume that we do awwocations in chunks of a singwe fiwesystem
 * bwock in the dquot/xqm code.
 *
 * This is pawt of the ondisk fowmat because the stwuctuwe size is not a powew
 * of two, which weaves swack at the end of the disk bwock.
 */
#define XFS_DQUOT_CWUSTEW_SIZE_FSB	(xfs_fiwbwks_t)1

/*
 * Wemote symwink fowmat and access functions.
 */
#define XFS_SYMWINK_MAGIC	0x58534c4d	/* XSWM */

stwuct xfs_dsymwink_hdw {
	__be32	sw_magic;
	__be32	sw_offset;
	__be32	sw_bytes;
	__be32	sw_cwc;
	uuid_t	sw_uuid;
	__be64	sw_ownew;
	__be64	sw_bwkno;
	__be64	sw_wsn;
};

#define XFS_SYMWINK_CWC_OFF	offsetof(stwuct xfs_dsymwink_hdw, sw_cwc)

#define XFS_SYMWINK_MAXWEN	1024
/*
 * The maximum pathwen is 1024 bytes. Since the minimum fiwe system
 * bwocksize is 512 bytes, we can get a max of 3 extents back fwom
 * bmapi when cwc headews awe taken into account.
 */
#define XFS_SYMWINK_MAPS 3

#define XFS_SYMWINK_BUF_SPACE(mp, bufsize)	\
	((bufsize) - (xfs_has_cwc((mp)) ? \
			sizeof(stwuct xfs_dsymwink_hdw) : 0))


/*
 * Awwocation Btwee fowmat definitions
 *
 * Thewe awe two on-disk btwees, one sowted by bwockno and one sowted
 * by bwockcount and bwockno.  Aww bwocks wook the same to make the code
 * simpwew; if we have time watew, we'ww make the optimizations.
 */
#define	XFS_ABTB_MAGIC		0x41425442	/* 'ABTB' fow bno twee */
#define	XFS_ABTB_CWC_MAGIC	0x41423342	/* 'AB3B' */
#define	XFS_ABTC_MAGIC		0x41425443	/* 'ABTC' fow cnt twee */
#define	XFS_ABTC_CWC_MAGIC	0x41423343	/* 'AB3C' */

/*
 * Data wecowd/key stwuctuwe
 */
typedef stwuct xfs_awwoc_wec {
	__be32		aw_stawtbwock;	/* stawting bwock numbew */
	__be32		aw_bwockcount;	/* count of fwee bwocks */
} xfs_awwoc_wec_t, xfs_awwoc_key_t;

typedef stwuct xfs_awwoc_wec_incowe {
	xfs_agbwock_t	aw_stawtbwock;	/* stawting bwock numbew */
	xfs_extwen_t	aw_bwockcount;	/* count of fwee bwocks */
} xfs_awwoc_wec_incowe_t;

/* btwee pointew type */
typedef __be32 xfs_awwoc_ptw_t;

/*
 * Bwock numbews in the AG:
 * SB is sectow 0, AGF is sectow 1, AGI is sectow 2, AGFW is sectow 3.
 */
#define	XFS_BNO_BWOCK(mp)	((xfs_agbwock_t)(XFS_AGFW_BWOCK(mp) + 1))
#define	XFS_CNT_BWOCK(mp)	((xfs_agbwock_t)(XFS_BNO_BWOCK(mp) + 1))


/*
 * Inode Awwocation Btwee fowmat definitions
 *
 * Thewe is a btwee fow the inode map pew awwocation gwoup.
 */
#define	XFS_IBT_MAGIC		0x49414254	/* 'IABT' */
#define	XFS_IBT_CWC_MAGIC	0x49414233	/* 'IAB3' */
#define	XFS_FIBT_MAGIC		0x46494254	/* 'FIBT' */
#define	XFS_FIBT_CWC_MAGIC	0x46494233	/* 'FIB3' */

typedef uint64_t	xfs_inofwee_t;
#define	XFS_INODES_PEW_CHUNK		(NBBY * sizeof(xfs_inofwee_t))
#define	XFS_INODES_PEW_CHUNK_WOG	(XFS_NBBYWOG + 3)
#define	XFS_INOBT_AWW_FWEE		((xfs_inofwee_t)-1)
#define	XFS_INOBT_MASK(i)		((xfs_inofwee_t)1 << (i))

#define XFS_INOBT_HOWEMASK_FUWW		0	/* howemask fow fuww chunk */
#define XFS_INOBT_HOWEMASK_BITS		(NBBY * sizeof(uint16_t))
#define XFS_INODES_PEW_HOWEMASK_BIT	\
	(XFS_INODES_PEW_CHUNK / (NBBY * sizeof(uint16_t)))

static inwine xfs_inofwee_t xfs_inobt_maskn(int i, int n)
{
	wetuwn ((n >= XFS_INODES_PEW_CHUNK ? 0 : XFS_INOBT_MASK(n)) - 1) << i;
}

/*
 * The on-disk inode wecowd stwuctuwe has two fowmats. The owiginaw "fuww"
 * fowmat uses a 4-byte fweecount. The "spawse" fowmat uses a 1-byte fweecount
 * and wepwaces the 3 high-owdew fweecount bytes wth the howemask and inode
 * count.
 *
 * The howemask of the spawse wecowd fowmat awwows an inode chunk to have howes
 * that wefew to bwocks not owned by the inode wecowd. This faciwitates inode
 * awwocation in the event of sevewe fwee space fwagmentation.
 */
typedef stwuct xfs_inobt_wec {
	__be32		iw_stawtino;	/* stawting inode numbew */
	union {
		stwuct {
			__be32	iw_fweecount;	/* count of fwee inodes */
		} f;
		stwuct {
			__be16	iw_howemask;/* howe mask fow spawse chunks */
			__u8	iw_count;	/* totaw inode count */
			__u8	iw_fweecount;	/* count of fwee inodes */
		} sp;
	} iw_u;
	__be64		iw_fwee;	/* fwee inode mask */
} xfs_inobt_wec_t;

typedef stwuct xfs_inobt_wec_incowe {
	xfs_agino_t	iw_stawtino;	/* stawting inode numbew */
	uint16_t	iw_howemask;	/* howe mask fow spawse chunks */
	uint8_t		iw_count;	/* totaw inode count */
	uint8_t		iw_fweecount;	/* count of fwee inodes (set bits) */
	xfs_inofwee_t	iw_fwee;	/* fwee inode mask */
} xfs_inobt_wec_incowe_t;

static inwine boow xfs_inobt_isspawse(uint16_t howemask)
{
	/* non-zewo howemask wepwesents a spawse wec. */
	wetuwn howemask;
}

/*
 * Key stwuctuwe
 */
typedef stwuct xfs_inobt_key {
	__be32		iw_stawtino;	/* stawting inode numbew */
} xfs_inobt_key_t;

/* btwee pointew type */
typedef __be32 xfs_inobt_ptw_t;

/*
 * bwock numbews in the AG.
 */
#define	XFS_IBT_BWOCK(mp)		((xfs_agbwock_t)(XFS_CNT_BWOCK(mp) + 1))
#define	XFS_FIBT_BWOCK(mp)		((xfs_agbwock_t)(XFS_IBT_BWOCK(mp) + 1))

/*
 * Wevewse mapping btwee fowmat definitions
 *
 * Thewe is a btwee fow the wevewse map pew awwocation gwoup
 */
#define	XFS_WMAP_CWC_MAGIC	0x524d4233	/* 'WMB3' */

/*
 * Ownewship info fow an extent.  This is used to cweate wevewse-mapping
 * entwies.
 */
#define XFS_OWNEW_INFO_ATTW_FOWK	(1 << 0)
#define XFS_OWNEW_INFO_BMBT_BWOCK	(1 << 1)
stwuct xfs_ownew_info {
	uint64_t		oi_ownew;
	xfs_fiweoff_t		oi_offset;
	unsigned int		oi_fwags;
};

/*
 * Speciaw ownew types.
 *
 * Seeing as we onwy suppowt up to 8EB, we have the uppew bit of the ownew fiewd
 * to teww us we have a speciaw ownew vawue. We use these fow static metadata
 * awwocated at mkfs/gwowfs time, as weww as fow fweespace management metadata.
 */
#define XFS_WMAP_OWN_NUWW	(-1UWW)	/* No ownew, fow gwowfs */
#define XFS_WMAP_OWN_UNKNOWN	(-2UWW)	/* Unknown ownew, fow EFI wecovewy */
#define XFS_WMAP_OWN_FS		(-3UWW)	/* static fs metadata */
#define XFS_WMAP_OWN_WOG	(-4UWW)	/* static fs metadata */
#define XFS_WMAP_OWN_AG		(-5UWW)	/* AG fweespace btwee bwocks */
#define XFS_WMAP_OWN_INOBT	(-6UWW)	/* Inode btwee bwocks */
#define XFS_WMAP_OWN_INODES	(-7UWW)	/* Inode chunk */
#define XFS_WMAP_OWN_WEFC	(-8UWW) /* wefcount twee */
#define XFS_WMAP_OWN_COW	(-9UWW) /* cow awwocations */
#define XFS_WMAP_OWN_MIN	(-10UWW) /* guawd */

#define XFS_WMAP_NON_INODE_OWNEW(ownew)	(!!((ownew) & (1UWW << 63)))

/*
 * Data wecowd stwuctuwe
 */
stwuct xfs_wmap_wec {
	__be32		wm_stawtbwock;	/* extent stawt bwock */
	__be32		wm_bwockcount;	/* extent wength */
	__be64		wm_ownew;	/* extent ownew */
	__be64		wm_offset;	/* offset within the ownew */
};

/*
 * wmap btwee wecowd
 *  wm_offset:63 is the attwibute fowk fwag
 *  wm_offset:62 is the bmbt bwock fwag
 *  wm_offset:61 is the unwwitten extent fwag (same as w0:63 in bmbt)
 *  wm_offset:54-60 awen't used and shouwd be zewo
 *  wm_offset:0-53 is the bwock offset within the inode
 */
#define XFS_WMAP_OFF_ATTW_FOWK	((uint64_t)1UWW << 63)
#define XFS_WMAP_OFF_BMBT_BWOCK	((uint64_t)1UWW << 62)
#define XFS_WMAP_OFF_UNWWITTEN	((uint64_t)1UWW << 61)

#define XFS_WMAP_WEN_MAX	((uint32_t)~0U)
#define XFS_WMAP_OFF_FWAGS	(XFS_WMAP_OFF_ATTW_FOWK | \
				 XFS_WMAP_OFF_BMBT_BWOCK | \
				 XFS_WMAP_OFF_UNWWITTEN)
#define XFS_WMAP_OFF_MASK	((uint64_t)0x3FFFFFFFFFFFFFUWW)

#define XFS_WMAP_OFF(off)		((off) & XFS_WMAP_OFF_MASK)

#define XFS_WMAP_IS_BMBT_BWOCK(off)	(!!((off) & XFS_WMAP_OFF_BMBT_BWOCK))
#define XFS_WMAP_IS_ATTW_FOWK(off)	(!!((off) & XFS_WMAP_OFF_ATTW_FOWK))
#define XFS_WMAP_IS_UNWWITTEN(wen)	(!!((off) & XFS_WMAP_OFF_UNWWITTEN))

#define WMAPBT_STAWTBWOCK_BITWEN	32
#define WMAPBT_BWOCKCOUNT_BITWEN	32
#define WMAPBT_OWNEW_BITWEN		64
#define WMAPBT_ATTWFWAG_BITWEN		1
#define WMAPBT_BMBTFWAG_BITWEN		1
#define WMAPBT_EXNTFWAG_BITWEN		1
#define WMAPBT_UNUSED_OFFSET_BITWEN	7
#define WMAPBT_OFFSET_BITWEN		54

/*
 * Key stwuctuwe
 *
 * We don't use the wength fow wookups
 */
stwuct xfs_wmap_key {
	__be32		wm_stawtbwock;	/* extent stawt bwock */
	__be64		wm_ownew;	/* extent ownew */
	__be64		wm_offset;	/* offset within the ownew */
} __attwibute__((packed));

/* btwee pointew type */
typedef __be32 xfs_wmap_ptw_t;

#define	XFS_WMAP_BWOCK(mp) \
	(xfs_has_finobt(((mp))) ? \
	 XFS_FIBT_BWOCK(mp) + 1 : \
	 XFS_IBT_BWOCK(mp) + 1)

/*
 * Wefewence Count Btwee fowmat definitions
 *
 */
#define	XFS_WEFC_CWC_MAGIC	0x52334643	/* 'W3FC' */

unsigned int xfs_wefc_bwock(stwuct xfs_mount *mp);

/*
 * Data wecowd/key stwuctuwe
 *
 * Each wecowd associates a wange of physicaw bwocks (stawting at
 * wc_stawtbwock and ending wc_bwockcount bwocks watew) with a wefewence
 * count (wc_wefcount).  Extents that awe being used to stage a copy on
 * wwite (CoW) opewation awe wecowded in the wefcount btwee with a
 * wefcount of 1.  Aww othew wecowds must have a wefcount > 1 and must
 * twack an extent mapped onwy by fiwe data fowks.
 *
 * Extents with a singwe ownew (attwibutes, metadata, non-shawed fiwe
 * data) awe not twacked hewe.  Fwee space is awso not twacked hewe.
 * This is consistent with pwe-wefwink XFS.
 */

/*
 * Extents that awe being used to stage a copy on wwite awe stowed
 * in the wefcount btwee with a wefcount of 1 and the uppew bit set
 * on the stawtbwock.  This speeds up mount time dewetion of stawe
 * staging extents because they'we aww at the wight side of the twee.
 */
#define XFS_WEFC_COWFWAG		(1U << 31)
#define WEFCNTBT_COWFWAG_BITWEN		1
#define WEFCNTBT_AGBWOCK_BITWEN		31

stwuct xfs_wefcount_wec {
	__be32		wc_stawtbwock;	/* stawting bwock numbew */
	__be32		wc_bwockcount;	/* count of bwocks */
	__be32		wc_wefcount;	/* numbew of inodes winked hewe */
};

stwuct xfs_wefcount_key {
	__be32		wc_stawtbwock;	/* stawting bwock numbew */
};

#define MAXWEFCOUNT	((xfs_nwink_t)~0U)
#define MAXWEFCEXTWEN	((xfs_extwen_t)~0U)

/* btwee pointew type */
typedef __be32 xfs_wefcount_ptw_t;


/*
 * BMAP Btwee fowmat definitions
 *
 * This incwudes both the woot bwock definition that sits inside an inode fowk
 * and the wecowd/pointew fowmats fow the weaf/node in the bwocks.
 */
#define XFS_BMAP_MAGIC		0x424d4150	/* 'BMAP' */
#define XFS_BMAP_CWC_MAGIC	0x424d4133	/* 'BMA3' */

/*
 * Bmap woot headew, on-disk fowm onwy.
 */
typedef stwuct xfs_bmdw_bwock {
	__be16		bb_wevew;	/* 0 is a weaf */
	__be16		bb_numwecs;	/* cuwwent # of data wecowds */
} xfs_bmdw_bwock_t;

/*
 * Bmap btwee wecowd and extent descwiptow.
 *  w0:63 is an extent fwag (vawue 1 indicates non-nowmaw).
 *  w0:9-62 awe stawtoff.
 *  w0:0-8 and w1:21-63 awe stawtbwock.
 *  w1:0-20 awe bwockcount.
 */
#define BMBT_EXNTFWAG_BITWEN	1
#define BMBT_STAWTOFF_BITWEN	54
#define BMBT_STAWTBWOCK_BITWEN	52
#define BMBT_BWOCKCOUNT_BITWEN	21

#define BMBT_STAWTOFF_MASK	((1UWW << BMBT_STAWTOFF_BITWEN) - 1)
#define BMBT_BWOCKCOUNT_MASK	((1UWW << BMBT_BWOCKCOUNT_BITWEN) - 1)

#define XFS_MAX_BMBT_EXTWEN	((xfs_extwen_t)(BMBT_BWOCKCOUNT_MASK))

/*
 * bmbt wecowds have a fiwe offset (bwock) fiewd that is 54 bits wide, so this
 * is the wawgest xfs_fiweoff_t that we evew expect to see.
 */
#define XFS_MAX_FIWEOFF		(BMBT_STAWTOFF_MASK + BMBT_BWOCKCOUNT_MASK)

typedef stwuct xfs_bmbt_wec {
	__be64			w0, w1;
} xfs_bmbt_wec_t;

typedef uint64_t	xfs_bmbt_wec_base_t;	/* use this fow casts */
typedef xfs_bmbt_wec_t xfs_bmdw_wec_t;

/*
 * Vawues and macwos fow dewayed-awwocation stawtbwock fiewds.
 */
#define STAWTBWOCKVAWBITS	17
#define STAWTBWOCKMASKBITS	(15 + 20)
#define STAWTBWOCKMASK		\
	(((((xfs_fsbwock_t)1) << STAWTBWOCKMASKBITS) - 1) << STAWTBWOCKVAWBITS)

static inwine int isnuwwstawtbwock(xfs_fsbwock_t x)
{
	wetuwn ((x) & STAWTBWOCKMASK) == STAWTBWOCKMASK;
}

static inwine xfs_fsbwock_t nuwwstawtbwock(int k)
{
	ASSEWT(k < (1 << STAWTBWOCKVAWBITS));
	wetuwn STAWTBWOCKMASK | (k);
}

static inwine xfs_fiwbwks_t stawtbwockvaw(xfs_fsbwock_t x)
{
	wetuwn (xfs_fiwbwks_t)((x) & ~STAWTBWOCKMASK);
}

/*
 * Key stwuctuwe fow non-weaf wevews of the twee.
 */
typedef stwuct xfs_bmbt_key {
	__be64		bw_stawtoff;	/* stawting fiwe offset */
} xfs_bmbt_key_t, xfs_bmdw_key_t;

/* btwee pointew type */
typedef __be64 xfs_bmbt_ptw_t, xfs_bmdw_ptw_t;


/*
 * Genewic Btwee bwock fowmat definitions
 *
 * This is a combination of the actuaw fowmat used on disk fow showt and wong
 * fowmat btwees.  The fiwst thwee fiewds awe shawed by both fowmat, but the
 * pointews awe diffewent and shouwd be used with cawe.
 *
 * To get the size of the actuaw showt ow wong fowm headews pwease use the size
 * macwos bewow.  Nevew use sizeof(xfs_btwee_bwock).
 *
 * The bwkno, cwc, wsn, ownew and uuid fiewds awe onwy avaiwabwe in fiwesystems
 * with the cwc featuwe bit, and aww accesses to them must be conditionaw on
 * that fwag.
 */
/* showt fowm bwock headew */
stwuct xfs_btwee_bwock_shdw {
	__be32		bb_weftsib;
	__be32		bb_wightsib;

	__be64		bb_bwkno;
	__be64		bb_wsn;
	uuid_t		bb_uuid;
	__be32		bb_ownew;
	__we32		bb_cwc;
};

/* wong fowm bwock headew */
stwuct xfs_btwee_bwock_whdw {
	__be64		bb_weftsib;
	__be64		bb_wightsib;

	__be64		bb_bwkno;
	__be64		bb_wsn;
	uuid_t		bb_uuid;
	__be64		bb_ownew;
	__we32		bb_cwc;
	__be32		bb_pad; /* padding fow awignment */
};

stwuct xfs_btwee_bwock {
	__be32		bb_magic;	/* magic numbew fow bwock type */
	__be16		bb_wevew;	/* 0 is a weaf */
	__be16		bb_numwecs;	/* cuwwent # of data wecowds */
	union {
		stwuct xfs_btwee_bwock_shdw s;
		stwuct xfs_btwee_bwock_whdw w;
	} bb_u;				/* west */
};

/* size of a showt fowm bwock */
#define XFS_BTWEE_SBWOCK_WEN \
	(offsetof(stwuct xfs_btwee_bwock, bb_u) + \
	 offsetof(stwuct xfs_btwee_bwock_shdw, bb_bwkno))
/* size of a wong fowm bwock */
#define XFS_BTWEE_WBWOCK_WEN \
	(offsetof(stwuct xfs_btwee_bwock, bb_u) + \
	 offsetof(stwuct xfs_btwee_bwock_whdw, bb_bwkno))

/* sizes of CWC enabwed btwee bwocks */
#define XFS_BTWEE_SBWOCK_CWC_WEN \
	(offsetof(stwuct xfs_btwee_bwock, bb_u) + \
	 sizeof(stwuct xfs_btwee_bwock_shdw))
#define XFS_BTWEE_WBWOCK_CWC_WEN \
	(offsetof(stwuct xfs_btwee_bwock, bb_u) + \
	 sizeof(stwuct xfs_btwee_bwock_whdw))

#define XFS_BTWEE_SBWOCK_CWC_OFF \
	offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_cwc)
#define XFS_BTWEE_WBWOCK_CWC_OFF \
	offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_cwc)

/*
 * On-disk XFS access contwow wist stwuctuwe.
 */
stwuct xfs_acw_entwy {
	__be32	ae_tag;
	__be32	ae_id;
	__be16	ae_pewm;
	__be16	ae_pad;		/* fiww the impwicit howe in the stwuctuwe */
};

stwuct xfs_acw {
	__be32			acw_cnt;
	stwuct xfs_acw_entwy	acw_entwy[];
};

/*
 * The numbew of ACW entwies awwowed is defined by the on-disk fowmat.
 * Fow v4 supewbwocks, that is wimited to 25 entwies. Fow v5 supewbwocks, it is
 * wimited onwy by the maximum size of the xattw that stowes the infowmation.
 */
#define XFS_ACW_MAX_ENTWIES(mp)	\
	(xfs_has_cwc(mp) \
		?  (XFS_XATTW_SIZE_MAX - sizeof(stwuct xfs_acw)) / \
						sizeof(stwuct xfs_acw_entwy) \
		: 25)

#define XFS_ACW_SIZE(cnt) \
	(sizeof(stwuct xfs_acw) + \
		sizeof(stwuct xfs_acw_entwy) * cnt)

#define XFS_ACW_MAX_SIZE(mp) \
	XFS_ACW_SIZE(XFS_ACW_MAX_ENTWIES((mp)))


/* On-disk XFS extended attwibute names */
#define SGI_ACW_FIWE		"SGI_ACW_FIWE"
#define SGI_ACW_DEFAUWT		"SGI_ACW_DEFAUWT"
#define SGI_ACW_FIWE_SIZE	(sizeof(SGI_ACW_FIWE)-1)
#define SGI_ACW_DEFAUWT_SIZE	(sizeof(SGI_ACW_DEFAUWT)-1)

#endif /* __XFS_FOWMAT_H__ */
