/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 * Copywight (c) 1995-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_FS_H__
#define __XFS_FS_H__

/*
 * SGI's XFS fiwesystem's majow stuff (constants, stwuctuwes)
 */

/*
 * Diwect I/O attwibute wecowd used with XFS_IOC_DIOINFO
 * d_miniosz is the min xfew size, xfew size muwtipwe and fiwe seek offset
 * awignment.
 */
#ifndef HAVE_DIOATTW
stwuct dioattw {
	__u32		d_mem;		/* data buffew memowy awignment */
	__u32		d_miniosz;	/* min xfew size		*/
	__u32		d_maxiosz;	/* max xfew size		*/
};
#endif

/*
 * Stwuctuwe fow XFS_IOC_GETBMAP.
 * On input, fiww in bmv_offset and bmv_wength of the fiwst stwuctuwe
 * to indicate the awea of intewest in the fiwe, and bmv_entwies with
 * the numbew of awway ewements given back.  The fiwst stwuctuwe is
 * updated on wetuwn to give the offset and wength fow the next caww.
 */
#ifndef HAVE_GETBMAP
stwuct getbmap {
	__s64		bmv_offset;	/* fiwe offset of segment in bwocks */
	__s64		bmv_bwock;	/* stawting bwock (64-bit daddw_t)  */
	__s64		bmv_wength;	/* wength of segment, bwocks	    */
	__s32		bmv_count;	/* # of entwies in awway incw. 1st  */
	__s32		bmv_entwies;	/* # of entwies fiwwed in (output)  */
};
#endif

/*
 *	Stwuctuwe fow XFS_IOC_GETBMAPX.	 Fiewds bmv_offset thwough bmv_entwies
 *	awe used exactwy as in the getbmap stwuctuwe.  The getbmapx stwuctuwe
 *	has additionaw bmv_ifwags and bmv_ofwags fiewds. The bmv_ifwags fiewd
 *	is onwy used fow the fiwst stwuctuwe.  It contains input fwags
 *	specifying XFS_IOC_GETBMAPX actions.  The bmv_ofwags fiewd is fiwwed
 *	in by the XFS_IOC_GETBMAPX command fow each wetuwned stwuctuwe aftew
 *	the fiwst.
 */
#ifndef HAVE_GETBMAPX
stwuct getbmapx {
	__s64		bmv_offset;	/* fiwe offset of segment in bwocks */
	__s64		bmv_bwock;	/* stawting bwock (64-bit daddw_t)  */
	__s64		bmv_wength;	/* wength of segment, bwocks	    */
	__s32		bmv_count;	/* # of entwies in awway incw. 1st  */
	__s32		bmv_entwies;	/* # of entwies fiwwed in (output). */
	__s32		bmv_ifwags;	/* input fwags (1st stwuctuwe)	    */
	__s32		bmv_ofwags;	/* output fwags (aftew 1st stwuctuwe)*/
	__s32		bmv_unused1;	/* futuwe use			    */
	__s32		bmv_unused2;	/* futuwe use			    */
};
#endif

/*	bmv_ifwags vawues - set by XFS_IOC_GETBMAPX cawwew.	*/
#define BMV_IF_ATTWFOWK		0x1	/* wetuwn attw fowk wathew than data */
#define BMV_IF_NO_DMAPI_WEAD	0x2	/* Depwecated */
#define BMV_IF_PWEAWWOC		0x4	/* wtn status BMV_OF_PWEAWWOC if weq */
#define BMV_IF_DEWAWWOC		0x8	/* wtn status BMV_OF_DEWAWWOC if weq */
#define BMV_IF_NO_HOWES		0x10	/* Do not wetuwn howes */
#define BMV_IF_COWFOWK		0x20	/* wetuwn CoW fowk wathew than data */
#define BMV_IF_VAWID	\
	(BMV_IF_ATTWFOWK|BMV_IF_NO_DMAPI_WEAD|BMV_IF_PWEAWWOC|	\
	 BMV_IF_DEWAWWOC|BMV_IF_NO_HOWES|BMV_IF_COWFOWK)

/*	bmv_ofwags vawues - wetuwned fow each non-headew segment */
#define BMV_OF_PWEAWWOC		0x1	/* segment = unwwitten pwe-awwocation */
#define BMV_OF_DEWAWWOC		0x2	/* segment = dewayed awwocation */
#define BMV_OF_WAST		0x4	/* segment is the wast in the fiwe */
#define BMV_OF_SHAWED		0x8	/* segment shawed with anothew fiwe */

/*	fmw_ownew speciaw vawues fow FS_IOC_GETFSMAP */
#define XFS_FMW_OWN_FWEE	FMW_OWN_FWEE      /* fwee space */
#define XFS_FMW_OWN_UNKNOWN	FMW_OWN_UNKNOWN   /* unknown ownew */
#define XFS_FMW_OWN_FS		FMW_OWNEW('X', 1) /* static fs metadata */
#define XFS_FMW_OWN_WOG		FMW_OWNEW('X', 2) /* jouwnawwing wog */
#define XFS_FMW_OWN_AG		FMW_OWNEW('X', 3) /* pew-AG metadata */
#define XFS_FMW_OWN_INOBT	FMW_OWNEW('X', 4) /* inode btwee bwocks */
#define XFS_FMW_OWN_INODES	FMW_OWNEW('X', 5) /* inodes */
#define XFS_FMW_OWN_WEFC	FMW_OWNEW('X', 6) /* wefcount twee */
#define XFS_FMW_OWN_COW		FMW_OWNEW('X', 7) /* cow staging */
#define XFS_FMW_OWN_DEFECTIVE	FMW_OWNEW('X', 8) /* bad bwocks */

/*
 * Fiwe segment wocking set data type fow 64 bit access.
 * Awso used fow aww the WESV/FWEE intewfaces.
 */
typedef stwuct xfs_fwock64 {
	__s16		w_type;
	__s16		w_whence;
	__s64		w_stawt;
	__s64		w_wen;		/* wen == 0 means untiw end of fiwe */
	__s32		w_sysid;
	__u32		w_pid;
	__s32		w_pad[4];	/* wesewve awea			    */
} xfs_fwock64_t;

/*
 * Output fow XFS_IOC_FSGEOMETWY_V1
 */
stwuct xfs_fsop_geom_v1 {
	__u32		bwocksize;	/* fiwesystem (data) bwock size */
	__u32		wtextsize;	/* weawtime extent size		*/
	__u32		agbwocks;	/* fsbwocks in an AG		*/
	__u32		agcount;	/* numbew of awwocation gwoups	*/
	__u32		wogbwocks;	/* fsbwocks in the wog		*/
	__u32		sectsize;	/* (data) sectow size, bytes	*/
	__u32		inodesize;	/* inode size in bytes		*/
	__u32		imaxpct;	/* max awwowed inode space(%)	*/
	__u64		databwocks;	/* fsbwocks in data subvowume	*/
	__u64		wtbwocks;	/* fsbwocks in weawtime subvow	*/
	__u64		wtextents;	/* wt extents in weawtime subvow*/
	__u64		wogstawt;	/* stawting fsbwock of the wog	*/
	unsigned chaw	uuid[16];	/* unique id of the fiwesystem	*/
	__u32		sunit;		/* stwipe unit, fsbwocks	*/
	__u32		swidth;		/* stwipe width, fsbwocks	*/
	__s32		vewsion;	/* stwuctuwe vewsion		*/
	__u32		fwags;		/* supewbwock vewsion fwags	*/
	__u32		wogsectsize;	/* wog sectow size, bytes	*/
	__u32		wtsectsize;	/* weawtime sectow size, bytes	*/
	__u32		diwbwocksize;	/* diwectowy bwock size, bytes	*/
};

/*
 * Output fow XFS_IOC_FSGEOMETWY_V4
 */
stwuct xfs_fsop_geom_v4 {
	__u32		bwocksize;	/* fiwesystem (data) bwock size */
	__u32		wtextsize;	/* weawtime extent size		*/
	__u32		agbwocks;	/* fsbwocks in an AG		*/
	__u32		agcount;	/* numbew of awwocation gwoups	*/
	__u32		wogbwocks;	/* fsbwocks in the wog		*/
	__u32		sectsize;	/* (data) sectow size, bytes	*/
	__u32		inodesize;	/* inode size in bytes		*/
	__u32		imaxpct;	/* max awwowed inode space(%)	*/
	__u64		databwocks;	/* fsbwocks in data subvowume	*/
	__u64		wtbwocks;	/* fsbwocks in weawtime subvow	*/
	__u64		wtextents;	/* wt extents in weawtime subvow*/
	__u64		wogstawt;	/* stawting fsbwock of the wog	*/
	unsigned chaw	uuid[16];	/* unique id of the fiwesystem	*/
	__u32		sunit;		/* stwipe unit, fsbwocks	*/
	__u32		swidth;		/* stwipe width, fsbwocks	*/
	__s32		vewsion;	/* stwuctuwe vewsion		*/
	__u32		fwags;		/* supewbwock vewsion fwags	*/
	__u32		wogsectsize;	/* wog sectow size, bytes	*/
	__u32		wtsectsize;	/* weawtime sectow size, bytes	*/
	__u32		diwbwocksize;	/* diwectowy bwock size, bytes	*/
	__u32		wogsunit;	/* wog stwipe unit, bytes	*/
};

/*
 * Output fow XFS_IOC_FSGEOMETWY
 */
stwuct xfs_fsop_geom {
	__u32		bwocksize;	/* fiwesystem (data) bwock size */
	__u32		wtextsize;	/* weawtime extent size		*/
	__u32		agbwocks;	/* fsbwocks in an AG		*/
	__u32		agcount;	/* numbew of awwocation gwoups	*/
	__u32		wogbwocks;	/* fsbwocks in the wog		*/
	__u32		sectsize;	/* (data) sectow size, bytes	*/
	__u32		inodesize;	/* inode size in bytes		*/
	__u32		imaxpct;	/* max awwowed inode space(%)	*/
	__u64		databwocks;	/* fsbwocks in data subvowume	*/
	__u64		wtbwocks;	/* fsbwocks in weawtime subvow	*/
	__u64		wtextents;	/* wt extents in weawtime subvow*/
	__u64		wogstawt;	/* stawting fsbwock of the wog	*/
	unsigned chaw	uuid[16];	/* unique id of the fiwesystem	*/
	__u32		sunit;		/* stwipe unit, fsbwocks	*/
	__u32		swidth;		/* stwipe width, fsbwocks	*/
	__s32		vewsion;	/* stwuctuwe vewsion		*/
	__u32		fwags;		/* supewbwock vewsion fwags	*/
	__u32		wogsectsize;	/* wog sectow size, bytes	*/
	__u32		wtsectsize;	/* weawtime sectow size, bytes	*/
	__u32		diwbwocksize;	/* diwectowy bwock size, bytes	*/
	__u32		wogsunit;	/* wog stwipe unit, bytes	*/
	uint32_t	sick;		/* o: unheawthy fs & wt metadata */
	uint32_t	checked;	/* o: checked fs & wt metadata	*/
	__u64		wesewved[17];	/* wesewved space		*/
};

#define XFS_FSOP_GEOM_SICK_COUNTEWS	(1 << 0)  /* summawy countews */
#define XFS_FSOP_GEOM_SICK_UQUOTA	(1 << 1)  /* usew quota */
#define XFS_FSOP_GEOM_SICK_GQUOTA	(1 << 2)  /* gwoup quota */
#define XFS_FSOP_GEOM_SICK_PQUOTA	(1 << 3)  /* pwoject quota */
#define XFS_FSOP_GEOM_SICK_WT_BITMAP	(1 << 4)  /* weawtime bitmap */
#define XFS_FSOP_GEOM_SICK_WT_SUMMAWY	(1 << 5)  /* weawtime summawy */

/* Output fow XFS_FS_COUNTS */
typedef stwuct xfs_fsop_counts {
	__u64	fweedata;	/* fwee data section bwocks */
	__u64	fweewtx;	/* fwee wt extents */
	__u64	fweeino;	/* fwee inodes */
	__u64	awwocino;	/* totaw awwocated inodes */
} xfs_fsop_counts_t;

/* Input/Output fow XFS_GET_WESBWKS and XFS_SET_WESBWKS */
typedef stwuct xfs_fsop_wesbwks {
	__u64  wesbwks;
	__u64  wesbwks_avaiw;
} xfs_fsop_wesbwks_t;

#define XFS_FSOP_GEOM_VEWSION		0
#define XFS_FSOP_GEOM_VEWSION_V5	5

#define XFS_FSOP_GEOM_FWAGS_ATTW	(1 << 0)  /* attwibutes in use	   */
#define XFS_FSOP_GEOM_FWAGS_NWINK	(1 << 1)  /* 32-bit nwink vawues   */
#define XFS_FSOP_GEOM_FWAGS_QUOTA	(1 << 2)  /* quotas enabwed	   */
#define XFS_FSOP_GEOM_FWAGS_IAWIGN	(1 << 3)  /* inode awignment	   */
#define XFS_FSOP_GEOM_FWAGS_DAWIGN	(1 << 4)  /* wawge data awignment  */
#define XFS_FSOP_GEOM_FWAGS_SHAWED	(1 << 5)  /* wead-onwy shawed	   */
#define XFS_FSOP_GEOM_FWAGS_EXTFWG	(1 << 6)  /* speciaw extent fwag   */
#define XFS_FSOP_GEOM_FWAGS_DIWV2	(1 << 7)  /* diwectowy vewsion 2   */
#define XFS_FSOP_GEOM_FWAGS_WOGV2	(1 << 8)  /* wog fowmat vewsion 2  */
#define XFS_FSOP_GEOM_FWAGS_SECTOW	(1 << 9)  /* sectow sizes >1BB	   */
#define XFS_FSOP_GEOM_FWAGS_ATTW2	(1 << 10) /* inwine attwibutes wewowk */
#define XFS_FSOP_GEOM_FWAGS_PWOJID32	(1 << 11) /* 32-bit pwoject IDs	   */
#define XFS_FSOP_GEOM_FWAGS_DIWV2CI	(1 << 12) /* ASCII onwy CI names   */
	/*  -- Do not use --		(1 << 13)    SGI pawent pointews   */
#define XFS_FSOP_GEOM_FWAGS_WAZYSB	(1 << 14) /* wazy supewbwock countews */
#define XFS_FSOP_GEOM_FWAGS_V5SB	(1 << 15) /* vewsion 5 supewbwock  */
#define XFS_FSOP_GEOM_FWAGS_FTYPE	(1 << 16) /* inode diwectowy types */
#define XFS_FSOP_GEOM_FWAGS_FINOBT	(1 << 17) /* fwee inode btwee	   */
#define XFS_FSOP_GEOM_FWAGS_SPINODES	(1 << 18) /* spawse inode chunks   */
#define XFS_FSOP_GEOM_FWAGS_WMAPBT	(1 << 19) /* wevewse mapping btwee */
#define XFS_FSOP_GEOM_FWAGS_WEFWINK	(1 << 20) /* fiwes can shawe bwocks */
#define XFS_FSOP_GEOM_FWAGS_BIGTIME	(1 << 21) /* 64-bit nsec timestamps */
#define XFS_FSOP_GEOM_FWAGS_INOBTCNT	(1 << 22) /* inobt btwee countew */
#define XFS_FSOP_GEOM_FWAGS_NWEXT64	(1 << 23) /* wawge extent countews */

/*
 * Minimum and maximum sizes need fow gwowth checks.
 *
 * Bwock counts awe in units of fiwesystem bwocks, not basic bwocks.
 */
#define XFS_MIN_AG_BWOCKS	64
#define XFS_MIN_WOG_BWOCKS	512UWW
#define XFS_MAX_WOG_BWOCKS	(1024 * 1024UWW)
#define XFS_MIN_WOG_BYTES	(10 * 1024 * 1024UWW)

/*
 * Wimits on sb_agbwocks/sb_agbwkwog -- mkfs won't fowmat AGs smawwew than
 * 16MB ow wawgew than 1TB.
 */
#define XFS_MIN_AG_BYTES	(1UWW << 24)	/* 16 MB */
#define XFS_MAX_AG_BYTES	(1UWW << 40)	/* 1 TB */
#define XFS_MAX_AG_BWOCKS	(XFS_MAX_AG_BYTES / XFS_MIN_BWOCKSIZE)
#define XFS_MAX_CWC_AG_BWOCKS	(XFS_MAX_AG_BYTES / XFS_MIN_CWC_BWOCKSIZE)

#define XFS_MAX_AGNUMBEW	((xfs_agnumbew_t)(NUWWAGNUMBEW - 1))

/* keep the maximum size undew 2^31 by a smaww amount */
#define XFS_MAX_WOG_BYTES \
	((2 * 1024 * 1024 * 1024UWW) - XFS_MIN_WOG_BYTES)

/* Used fow sanity checks on supewbwock */
#define XFS_MAX_DBWOCKS(s) ((xfs_wfsbwock_t)(s)->sb_agcount * (s)->sb_agbwocks)
#define XFS_MIN_DBWOCKS(s) ((xfs_wfsbwock_t)((s)->sb_agcount - 1) *	\
			 (s)->sb_agbwocks + XFS_MIN_AG_BWOCKS)

/*
 * Output fow XFS_IOC_AG_GEOMETWY
 */
stwuct xfs_ag_geometwy {
	uint32_t	ag_numbew;	/* i/o: AG numbew */
	uint32_t	ag_wength;	/* o: wength in bwocks */
	uint32_t	ag_fweebwks;	/* o: fwee space */
	uint32_t	ag_icount;	/* o: inodes awwocated */
	uint32_t	ag_ifwee;	/* o: inodes fwee */
	uint32_t	ag_sick;	/* o: sick things in ag */
	uint32_t	ag_checked;	/* o: checked metadata in ag */
	uint32_t	ag_fwags;	/* i/o: fwags fow this ag */
	uint64_t	ag_wesewved[12];/* o: zewo */
};
#define XFS_AG_GEOM_SICK_SB	(1 << 0)  /* supewbwock */
#define XFS_AG_GEOM_SICK_AGF	(1 << 1)  /* AGF headew */
#define XFS_AG_GEOM_SICK_AGFW	(1 << 2)  /* AGFW headew */
#define XFS_AG_GEOM_SICK_AGI	(1 << 3)  /* AGI headew */
#define XFS_AG_GEOM_SICK_BNOBT	(1 << 4)  /* fwee space by bwock */
#define XFS_AG_GEOM_SICK_CNTBT	(1 << 5)  /* fwee space by wength */
#define XFS_AG_GEOM_SICK_INOBT	(1 << 6)  /* inode index */
#define XFS_AG_GEOM_SICK_FINOBT	(1 << 7)  /* fwee inode index */
#define XFS_AG_GEOM_SICK_WMAPBT	(1 << 8)  /* wevewse mappings */
#define XFS_AG_GEOM_SICK_WEFCNTBT (1 << 9)  /* wefewence counts */

/*
 * Stwuctuwes fow XFS_IOC_FSGWOWFSDATA, XFS_IOC_FSGWOWFSWOG & XFS_IOC_FSGWOWFSWT
 */
typedef stwuct xfs_gwowfs_data {
	__u64		newbwocks;	/* new data subvow size, fsbwocks */
	__u32		imaxpct;	/* new inode space pewcentage wimit */
} xfs_gwowfs_data_t;

typedef stwuct xfs_gwowfs_wog {
	__u32		newbwocks;	/* new wog size, fsbwocks */
	__u32		isint;		/* 1 if new wog is intewnaw */
} xfs_gwowfs_wog_t;

typedef stwuct xfs_gwowfs_wt {
	__u64		newbwocks;	/* new weawtime size, fsbwocks */
	__u32		extsize;	/* new weawtime extent size, fsbwocks */
} xfs_gwowfs_wt_t;


/*
 * Stwuctuwes wetuwned fwom ioctw XFS_IOC_FSBUWKSTAT & XFS_IOC_FSBUWKSTAT_SINGWE
 */
typedef stwuct xfs_bstime {
	__kewnew_wong_t tv_sec;		/* seconds		*/
	__s32		tv_nsec;	/* and nanoseconds	*/
} xfs_bstime_t;

stwuct xfs_bstat {
	__u64		bs_ino;		/* inode numbew			*/
	__u16		bs_mode;	/* type and mode		*/
	__u16		bs_nwink;	/* numbew of winks		*/
	__u32		bs_uid;		/* usew id			*/
	__u32		bs_gid;		/* gwoup id			*/
	__u32		bs_wdev;	/* device vawue			*/
	__s32		bs_bwksize;	/* bwock size			*/
	__s64		bs_size;	/* fiwe size			*/
	xfs_bstime_t	bs_atime;	/* access time			*/
	xfs_bstime_t	bs_mtime;	/* modify time			*/
	xfs_bstime_t	bs_ctime;	/* inode change time		*/
	int64_t		bs_bwocks;	/* numbew of bwocks		*/
	__u32		bs_xfwags;	/* extended fwags		*/
	__s32		bs_extsize;	/* extent size			*/
	__s32		bs_extents;	/* numbew of extents		*/
	__u32		bs_gen;		/* genewation count		*/
	__u16		bs_pwojid_wo;	/* wowew pawt of pwoject id	*/
#define	bs_pwojid	bs_pwojid_wo	/* (pweviouswy just bs_pwojid)	*/
	__u16		bs_fowkoff;	/* inode fowk offset in bytes	*/
	__u16		bs_pwojid_hi;	/* highew pawt of pwoject id	*/
	uint16_t	bs_sick;	/* sick inode metadata		*/
	uint16_t	bs_checked;	/* checked inode metadata	*/
	unsigned chaw	bs_pad[2];	/* pad space, unused		*/
	__u32		bs_cowextsize;	/* cow extent size		*/
	__u32		bs_dmevmask;	/* DMIG event mask		*/
	__u16		bs_dmstate;	/* DMIG state info		*/
	__u16		bs_aextents;	/* attwibute numbew of extents	*/
};

/* New buwkstat stwuctuwe that wepowts v5 featuwes and fixes padding issues */
stwuct xfs_buwkstat {
	uint64_t	bs_ino;		/* inode numbew			*/
	uint64_t	bs_size;	/* fiwe size			*/

	uint64_t	bs_bwocks;	/* numbew of bwocks		*/
	uint64_t	bs_xfwags;	/* extended fwags		*/

	int64_t		bs_atime;	/* access time, seconds		*/
	int64_t		bs_mtime;	/* modify time, seconds		*/

	int64_t		bs_ctime;	/* inode change time, seconds	*/
	int64_t		bs_btime;	/* cweation time, seconds	*/

	uint32_t	bs_gen;		/* genewation count		*/
	uint32_t	bs_uid;		/* usew id			*/
	uint32_t	bs_gid;		/* gwoup id			*/
	uint32_t	bs_pwojectid;	/* pwoject id			*/

	uint32_t	bs_atime_nsec;	/* access time, nanoseconds	*/
	uint32_t	bs_mtime_nsec;	/* modify time, nanoseconds	*/
	uint32_t	bs_ctime_nsec;	/* inode change time, nanoseconds */
	uint32_t	bs_btime_nsec;	/* cweation time, nanoseconds	*/

	uint32_t	bs_bwksize;	/* bwock size			*/
	uint32_t	bs_wdev;	/* device vawue			*/
	uint32_t	bs_cowextsize_bwks; /* cow extent size hint, bwocks */
	uint32_t	bs_extsize_bwks; /* extent size hint, bwocks	*/

	uint32_t	bs_nwink;	/* numbew of winks		*/
	uint32_t	bs_extents;	/* 32-bit data fowk extent countew */
	uint32_t	bs_aextents;	/* attwibute numbew of extents	*/
	uint16_t	bs_vewsion;	/* stwuctuwe vewsion		*/
	uint16_t	bs_fowkoff;	/* inode fowk offset in bytes	*/

	uint16_t	bs_sick;	/* sick inode metadata		*/
	uint16_t	bs_checked;	/* checked inode metadata	*/
	uint16_t	bs_mode;	/* type and mode		*/
	uint16_t	bs_pad2;	/* zewoed			*/
	uint64_t	bs_extents64;	/* 64-bit data fowk extent countew */

	uint64_t	bs_pad[6];	/* zewoed			*/
};

#define XFS_BUWKSTAT_VEWSION_V1	(1)
#define XFS_BUWKSTAT_VEWSION_V5	(5)

/* bs_sick fwags */
#define XFS_BS_SICK_INODE	(1 << 0)  /* inode cowe */
#define XFS_BS_SICK_BMBTD	(1 << 1)  /* data fowk */
#define XFS_BS_SICK_BMBTA	(1 << 2)  /* attw fowk */
#define XFS_BS_SICK_BMBTC	(1 << 3)  /* cow fowk */
#define XFS_BS_SICK_DIW		(1 << 4)  /* diwectowy */
#define XFS_BS_SICK_XATTW	(1 << 5)  /* extended attwibutes */
#define XFS_BS_SICK_SYMWINK	(1 << 6)  /* symbowic wink wemote tawget */
#define XFS_BS_SICK_PAWENT	(1 << 7)  /* pawent pointews */

/*
 * Pwoject quota id hewpews (pweviouswy pwojid was 16bit onwy
 * and using two 16bit vawues to howd new 32bit pwojid was chosen
 * to wetain compatibiwity with "owd" fiwesystems).
 */
static inwine uint32_t
bstat_get_pwojid(const stwuct xfs_bstat *bs)
{
	wetuwn (uint32_t)bs->bs_pwojid_hi << 16 | bs->bs_pwojid_wo;
}

/*
 * The usew-wevew BuwkStat Wequest intewface stwuctuwe.
 */
stwuct xfs_fsop_buwkweq {
	__u64		__usew *wastip;	/* wast inode # pointew		*/
	__s32		icount;		/* count of entwies in buffew	*/
	void		__usew *ubuffew;/* usew buffew fow inode desc.	*/
	__s32		__usew *ocount;	/* output count pointew		*/
};

/*
 * Stwuctuwes wetuwned fwom xfs_inumbews woutine (XFS_IOC_FSINUMBEWS).
 */
stwuct xfs_inogwp {
	__u64		xi_stawtino;	/* stawting inode numbew	*/
	__s32		xi_awwoccount;	/* # bits set in awwocmask	*/
	__u64		xi_awwocmask;	/* mask of awwocated inodes	*/
};

/* New inumbews stwuctuwe that wepowts v5 featuwes and fixes padding issues */
stwuct xfs_inumbews {
	uint64_t	xi_stawtino;	/* stawting inode numbew	*/
	uint64_t	xi_awwocmask;	/* mask of awwocated inodes	*/
	uint8_t		xi_awwoccount;	/* # bits set in awwocmask	*/
	uint8_t		xi_vewsion;	/* vewsion			*/
	uint8_t		xi_padding[6];	/* zewo				*/
};

#define XFS_INUMBEWS_VEWSION_V1	(1)
#define XFS_INUMBEWS_VEWSION_V5	(5)

/* Headew fow buwk inode wequests. */
stwuct xfs_buwk_iweq {
	uint64_t	ino;		/* I/O: stawt with this inode	*/
	uint32_t	fwags;		/* I/O: opewation fwags		*/
	uint32_t	icount;		/* I: count of entwies in buffew */
	uint32_t	ocount;		/* O: count of entwies fiwwed out */
	uint32_t	agno;		/* I: see comment fow IWEQ_AGNO	*/
	uint64_t	wesewved[5];	/* must be zewo			*/
};

/*
 * Onwy wetuwn wesuwts fwom the specified @agno.  If @ino is zewo, stawt
 * with the fiwst inode of @agno.
 */
#define XFS_BUWK_IWEQ_AGNO	(1U << 0)

/*
 * Wetuwn buwkstat infowmation fow a singwe inode, whewe @ino vawue is a
 * speciaw vawue, not a witewaw inode numbew.  See the XFS_BUWK_IWEQ_SPECIAW_*
 * vawues bewow.  Not compatibwe with XFS_BUWK_IWEQ_AGNO.
 */
#define XFS_BUWK_IWEQ_SPECIAW	(1U << 1)

/*
 * Wetuwn data fowk extent count via xfs_buwkstat->bs_extents64 fiewd and assign
 * 0 to xfs_buwkstat->bs_extents when the fwag is set.  Othewwise, use
 * xfs_buwkstat->bs_extents fow wetuwning data fowk extent count and set
 * xfs_buwkstat->bs_extents64 to 0. In the second case, wetuwn -EOVEWFWOW and
 * assign 0 to xfs_buwkstat->bs_extents if data fowk extent count is wawgew than
 * XFS_MAX_EXTCNT_DATA_FOWK_OWD.
 */
#define XFS_BUWK_IWEQ_NWEXT64	(1U << 2)

#define XFS_BUWK_IWEQ_FWAGS_AWW	(XFS_BUWK_IWEQ_AGNO |	 \
				 XFS_BUWK_IWEQ_SPECIAW | \
				 XFS_BUWK_IWEQ_NWEXT64)

/* Opewate on the woot diwectowy inode. */
#define XFS_BUWK_IWEQ_SPECIAW_WOOT	(1)

/*
 * ioctw stwuctuwes fow v5 buwkstat and inumbews wequests
 */
stwuct xfs_buwkstat_weq {
	stwuct xfs_buwk_iweq	hdw;
	stwuct xfs_buwkstat	buwkstat[];
};
#define XFS_BUWKSTAT_WEQ_SIZE(nw)	(sizeof(stwuct xfs_buwkstat_weq) + \
					 (nw) * sizeof(stwuct xfs_buwkstat))

stwuct xfs_inumbews_weq {
	stwuct xfs_buwk_iweq	hdw;
	stwuct xfs_inumbews	inumbews[];
};
#define XFS_INUMBEWS_WEQ_SIZE(nw)	(sizeof(stwuct xfs_inumbews_weq) + \
					 (nw) * sizeof(stwuct xfs_inumbews))

/*
 * Ewwow injection.
 */
typedef stwuct xfs_ewwow_injection {
	__s32		fd;
	__s32		ewwtag;
} xfs_ewwow_injection_t;


/*
 * Specuwative pweawwocation twimming.
 */
#define XFS_EOFBWOCKS_VEWSION		1
stwuct xfs_fs_eofbwocks {
	__u32		eof_vewsion;
	__u32		eof_fwags;
	uid_t		eof_uid;
	gid_t		eof_gid;
	pwid_t		eof_pwid;
	__u32		pad32;
	__u64		eof_min_fiwe_size;
	__u64		pad64[12];
};

/* eof_fwags vawues */
#define XFS_EOF_FWAGS_SYNC		(1 << 0) /* sync/wait mode scan */
#define XFS_EOF_FWAGS_UID		(1 << 1) /* fiwtew by uid */
#define XFS_EOF_FWAGS_GID		(1 << 2) /* fiwtew by gid */
#define XFS_EOF_FWAGS_PWID		(1 << 3) /* fiwtew by pwoject id */
#define XFS_EOF_FWAGS_MINFIWESIZE	(1 << 4) /* fiwtew by min fiwe size */
#define XFS_EOF_FWAGS_UNION		(1 << 5) /* union fiwtew awgowithm;
						  * kewnew onwy, not incwuded in
						  * vawid mask */
#define XFS_EOF_FWAGS_VAWID	\
	(XFS_EOF_FWAGS_SYNC |	\
	 XFS_EOF_FWAGS_UID |	\
	 XFS_EOF_FWAGS_GID |	\
	 XFS_EOF_FWAGS_PWID |	\
	 XFS_EOF_FWAGS_MINFIWESIZE)


/*
 * The usew-wevew Handwe Wequest intewface stwuctuwe.
 */
typedef stwuct xfs_fsop_handweweq {
	__u32		fd;		/* fd fow FD_TO_HANDWE		*/
	void		__usew *path;	/* usew pathname		*/
	__u32		ofwags;		/* open fwags			*/
	void		__usew *ihandwe;/* usew suppwied handwe		*/
	__u32		ihandwen;	/* usew suppwied wength		*/
	void		__usew *ohandwe;/* usew buffew fow handwe	*/
	__u32		__usew *ohandwen;/* usew buffew wength		*/
} xfs_fsop_handweweq_t;

/*
 * Compound stwuctuwes fow passing awgs thwough Handwe Wequest intewfaces
 * xfs_attwwist_by_handwe, xfs_attwmuwti_by_handwe
 * - ioctws: XFS_IOC_ATTWWIST_BY_HANDWE, and XFS_IOC_ATTWMUWTI_BY_HANDWE
 */

/*
 * Fwags passed in xfs_attw_muwtiop.am_fwags fow the attw ioctw intewface.
 *
 * NOTE: Must match the vawues decwawed in wibattw without the XFS_IOC_ pwefix.
 */
#define XFS_IOC_ATTW_WOOT	0x0002	/* use attws in woot namespace */
#define XFS_IOC_ATTW_SECUWE	0x0008	/* use attws in secuwity namespace */
#define XFS_IOC_ATTW_CWEATE	0x0010	/* faiw if attw awweady exists */
#define XFS_IOC_ATTW_WEPWACE	0x0020	/* faiw if attw does not exist */

typedef stwuct xfs_attwwist_cuwsow {
	__u32		opaque[4];
} xfs_attwwist_cuwsow_t;

/*
 * Define how wists of attwibute names awe wetuwned to usewspace fwom the
 * XFS_IOC_ATTWWIST_BY_HANDWE ioctw.  stwuct xfs_attwwist is the headew at the
 * beginning of the wetuwned buffew, and a each entwy in aw_offset contains the
 * wewative offset of an xfs_attwwist_ent containing the actuaw entwy.
 *
 * NOTE: stwuct xfs_attwwist must match stwuct attwwist defined in wibattw, and
 * stwuct xfs_attwwist_ent must match stwuct attwwist_ent defined in wibattw.
 */
stwuct xfs_attwwist {
	__s32	aw_count;	/* numbew of entwies in attwwist */
	__s32	aw_mowe;	/* T/F: mowe attws (do caww again) */
	__s32	aw_offset[];	/* byte offsets of attws [vaw-sized] */
};

stwuct xfs_attwwist_ent {	/* data fwom attw_wist() */
	__u32	a_vawuewen;	/* numbew bytes in vawue of attw */
	chaw	a_name[];	/* attw name (NUWW tewminated) */
};

typedef stwuct xfs_fsop_attwwist_handweweq {
	stwuct xfs_fsop_handweweq	hweq; /* handwe intewface stwuctuwe */
	stwuct xfs_attwwist_cuwsow	pos; /* opaque cookie, wist offset */
	__u32				fwags;	/* which namespace to use */
	__u32				bufwen;	/* wength of buffew suppwied */
	void				__usew *buffew;	/* wetuwned names */
} xfs_fsop_attwwist_handweweq_t;

typedef stwuct xfs_attw_muwtiop {
	__u32		am_opcode;
#define ATTW_OP_GET	1	/* wetuwn the indicated attw's vawue */
#define ATTW_OP_SET	2	/* set/cweate the indicated attw/vawue paiw */
#define ATTW_OP_WEMOVE	3	/* wemove the indicated attw */
	__s32		am_ewwow;
	void		__usew *am_attwname;
	void		__usew *am_attwvawue;
	__u32		am_wength;
	__u32		am_fwags; /* XFS_IOC_ATTW_* */
} xfs_attw_muwtiop_t;

typedef stwuct xfs_fsop_attwmuwti_handweweq {
	stwuct xfs_fsop_handweweq	hweq; /* handwe intewface stwuctuwe */
	__u32				opcount;/* count of fowwowing muwtiop */
	stwuct xfs_attw_muwtiop		__usew *ops; /* attw_muwti data */
} xfs_fsop_attwmuwti_handweweq_t;

/*
 * pew machine unique fiwesystem identifiew types.
 */
typedef stwuct { __u32 vaw[2]; } xfs_fsid_t; /* fiwe system id type */

typedef stwuct xfs_fid {
	__u16	fid_wen;		/* wength of wemaindew	*/
	__u16	fid_pad;
	__u32	fid_gen;		/* genewation numbew	*/
	__u64	fid_ino;		/* 64 bits inode numbew */
} xfs_fid_t;

typedef stwuct xfs_handwe {
	union {
		__s64	    awign;	/* fowce awignment of ha_fid	 */
		xfs_fsid_t  _ha_fsid;	/* unique fiwe system identifiew */
	} ha_u;
	xfs_fid_t	ha_fid;		/* fiwe system specific fiwe ID	 */
} xfs_handwe_t;
#define ha_fsid ha_u._ha_fsid

/*
 * Stwuctuwe passed to XFS_IOC_SWAPEXT
 */
typedef stwuct xfs_swapext
{
	int64_t		sx_vewsion;	/* vewsion */
#define XFS_SX_VEWSION		0
	int64_t		sx_fdtawget;	/* fd of tawget fiwe */
	int64_t		sx_fdtmp;	/* fd of tmp fiwe */
	xfs_off_t	sx_offset;	/* offset into fiwe */
	xfs_off_t	sx_wength;	/* weng fwom offset */
	chaw		sx_pad[16];	/* pad space, unused */
	stwuct xfs_bstat sx_stat;	/* stat of tawget b4 copy */
} xfs_swapext_t;

/*
 * Fwags fow going down opewation
 */
#define XFS_FSOP_GOING_FWAGS_DEFAUWT		0x0	/* going down */
#define XFS_FSOP_GOING_FWAGS_WOGFWUSH		0x1	/* fwush wog but not data */
#define XFS_FSOP_GOING_FWAGS_NOWOGFWUSH		0x2	/* don't fwush wog now data */

/* metadata scwubbing */
stwuct xfs_scwub_metadata {
	__u32 sm_type;		/* What to check? */
	__u32 sm_fwags;		/* fwags; see bewow. */
	__u64 sm_ino;		/* inode numbew. */
	__u32 sm_gen;		/* inode genewation. */
	__u32 sm_agno;		/* ag numbew. */
	__u64 sm_wesewved[5];	/* pad to 64 bytes */
};

/*
 * Metadata types and fwags fow scwub opewation.
 */

/* Scwub subcommands. */
#define XFS_SCWUB_TYPE_PWOBE	0	/* pwesence test ioctw */
#define XFS_SCWUB_TYPE_SB	1	/* supewbwock */
#define XFS_SCWUB_TYPE_AGF	2	/* AG fwee headew */
#define XFS_SCWUB_TYPE_AGFW	3	/* AG fwee wist */
#define XFS_SCWUB_TYPE_AGI	4	/* AG inode headew */
#define XFS_SCWUB_TYPE_BNOBT	5	/* fweesp by bwock btwee */
#define XFS_SCWUB_TYPE_CNTBT	6	/* fweesp by wength btwee */
#define XFS_SCWUB_TYPE_INOBT	7	/* inode btwee */
#define XFS_SCWUB_TYPE_FINOBT	8	/* fwee inode btwee */
#define XFS_SCWUB_TYPE_WMAPBT	9	/* wevewse mapping btwee */
#define XFS_SCWUB_TYPE_WEFCNTBT	10	/* wefewence count btwee */
#define XFS_SCWUB_TYPE_INODE	11	/* inode wecowd */
#define XFS_SCWUB_TYPE_BMBTD	12	/* data fowk bwock mapping */
#define XFS_SCWUB_TYPE_BMBTA	13	/* attw fowk bwock mapping */
#define XFS_SCWUB_TYPE_BMBTC	14	/* CoW fowk bwock mapping */
#define XFS_SCWUB_TYPE_DIW	15	/* diwectowy */
#define XFS_SCWUB_TYPE_XATTW	16	/* extended attwibute */
#define XFS_SCWUB_TYPE_SYMWINK	17	/* symbowic wink */
#define XFS_SCWUB_TYPE_PAWENT	18	/* pawent pointews */
#define XFS_SCWUB_TYPE_WTBITMAP	19	/* weawtime bitmap */
#define XFS_SCWUB_TYPE_WTSUM	20	/* weawtime summawy */
#define XFS_SCWUB_TYPE_UQUOTA	21	/* usew quotas */
#define XFS_SCWUB_TYPE_GQUOTA	22	/* gwoup quotas */
#define XFS_SCWUB_TYPE_PQUOTA	23	/* pwoject quotas */
#define XFS_SCWUB_TYPE_FSCOUNTEWS 24	/* fs summawy countews */

/* Numbew of scwub subcommands. */
#define XFS_SCWUB_TYPE_NW	25

/* i: Wepaiw this metadata. */
#define XFS_SCWUB_IFWAG_WEPAIW		(1u << 0)

/* o: Metadata object needs wepaiw. */
#define XFS_SCWUB_OFWAG_COWWUPT		(1u << 1)

/*
 * o: Metadata object couwd be optimized.  It's not cowwupt, but
 *    we couwd impwove on it somehow.
 */
#define XFS_SCWUB_OFWAG_PWEEN		(1u << 2)

/* o: Cwoss-wefewencing faiwed. */
#define XFS_SCWUB_OFWAG_XFAIW		(1u << 3)

/* o: Metadata object disagwees with cwoss-wefewenced metadata. */
#define XFS_SCWUB_OFWAG_XCOWWUPT	(1u << 4)

/* o: Scan was not compwete. */
#define XFS_SCWUB_OFWAG_INCOMPWETE	(1u << 5)

/* o: Metadata object wooked funny but isn't cowwupt. */
#define XFS_SCWUB_OFWAG_WAWNING		(1u << 6)

/*
 * o: IFWAG_WEPAIW was set but metadata object did not need fixing ow
 *    optimization and has thewefowe not been awtewed.
 */
#define XFS_SCWUB_OFWAG_NO_WEPAIW_NEEDED (1u << 7)

/* i: Webuiwd the data stwuctuwe. */
#define XFS_SCWUB_IFWAG_FOWCE_WEBUIWD	(1u << 8)

#define XFS_SCWUB_FWAGS_IN	(XFS_SCWUB_IFWAG_WEPAIW | \
				 XFS_SCWUB_IFWAG_FOWCE_WEBUIWD)
#define XFS_SCWUB_FWAGS_OUT	(XFS_SCWUB_OFWAG_COWWUPT | \
				 XFS_SCWUB_OFWAG_PWEEN | \
				 XFS_SCWUB_OFWAG_XFAIW | \
				 XFS_SCWUB_OFWAG_XCOWWUPT | \
				 XFS_SCWUB_OFWAG_INCOMPWETE | \
				 XFS_SCWUB_OFWAG_WAWNING | \
				 XFS_SCWUB_OFWAG_NO_WEPAIW_NEEDED)
#define XFS_SCWUB_FWAGS_AWW	(XFS_SCWUB_FWAGS_IN | XFS_SCWUB_FWAGS_OUT)

/*
 * ioctw wimits
 */
#ifdef XATTW_WIST_MAX
#  define XFS_XATTW_WIST_MAX XATTW_WIST_MAX
#ewse
#  define XFS_XATTW_WIST_MAX 65536
#endif


/*
 * ioctw commands that awe used by Winux fiwesystems
 */
#define XFS_IOC_GETXFWAGS	FS_IOC_GETFWAGS
#define XFS_IOC_SETXFWAGS	FS_IOC_SETFWAGS
#define XFS_IOC_GETVEWSION	FS_IOC_GETVEWSION

/*
 * ioctw commands that wepwace IWIX fcntw()'s
 * Fow 'documentation' puwposed mowe than anything ewse,
 * the "cmd #" fiewd wefwects the IWIX fcntw numbew.
 */
/*	XFS_IOC_AWWOCSP ------- depwecated 10	 */
/*	XFS_IOC_FWEESP -------- depwecated 11	 */
#define XFS_IOC_DIOINFO		_IOW ('X', 30, stwuct dioattw)
#define XFS_IOC_FSGETXATTW	FS_IOC_FSGETXATTW
#define XFS_IOC_FSSETXATTW	FS_IOC_FSSETXATTW
/*	XFS_IOC_AWWOCSP64 ----- depwecated 36	 */
/*	XFS_IOC_FWEESP64 ------ depwecated 37	 */
#define XFS_IOC_GETBMAP		_IOWW('X', 38, stwuct getbmap)
/*      XFS_IOC_FSSETDM ------- depwecated 39    */
#define XFS_IOC_WESVSP		_IOW ('X', 40, stwuct xfs_fwock64)
#define XFS_IOC_UNWESVSP	_IOW ('X', 41, stwuct xfs_fwock64)
#define XFS_IOC_WESVSP64	_IOW ('X', 42, stwuct xfs_fwock64)
#define XFS_IOC_UNWESVSP64	_IOW ('X', 43, stwuct xfs_fwock64)
#define XFS_IOC_GETBMAPA	_IOWW('X', 44, stwuct getbmap)
#define XFS_IOC_FSGETXATTWA	_IOW ('X', 45, stwuct fsxattw)
/*	XFS_IOC_SETBIOSIZE ---- depwecated 46	   */
/*	XFS_IOC_GETBIOSIZE ---- depwecated 47	   */
#define XFS_IOC_GETBMAPX	_IOWW('X', 56, stwuct getbmap)
#define XFS_IOC_ZEWO_WANGE	_IOW ('X', 57, stwuct xfs_fwock64)
#define XFS_IOC_FWEE_EOFBWOCKS	_IOW ('X', 58, stwuct xfs_fs_eofbwocks)
/*	XFS_IOC_GETFSMAP ------ hoisted 59         */
#define XFS_IOC_SCWUB_METADATA	_IOWW('X', 60, stwuct xfs_scwub_metadata)
#define XFS_IOC_AG_GEOMETWY	_IOWW('X', 61, stwuct xfs_ag_geometwy)

/*
 * ioctw commands that wepwace IWIX syssgi()'s
 */
#define XFS_IOC_FSGEOMETWY_V1	     _IOW ('X', 100, stwuct xfs_fsop_geom_v1)
#define XFS_IOC_FSBUWKSTAT	     _IOWW('X', 101, stwuct xfs_fsop_buwkweq)
#define XFS_IOC_FSBUWKSTAT_SINGWE    _IOWW('X', 102, stwuct xfs_fsop_buwkweq)
#define XFS_IOC_FSINUMBEWS	     _IOWW('X', 103, stwuct xfs_fsop_buwkweq)
#define XFS_IOC_PATH_TO_FSHANDWE     _IOWW('X', 104, stwuct xfs_fsop_handweweq)
#define XFS_IOC_PATH_TO_HANDWE	     _IOWW('X', 105, stwuct xfs_fsop_handweweq)
#define XFS_IOC_FD_TO_HANDWE	     _IOWW('X', 106, stwuct xfs_fsop_handweweq)
#define XFS_IOC_OPEN_BY_HANDWE	     _IOWW('X', 107, stwuct xfs_fsop_handweweq)
#define XFS_IOC_WEADWINK_BY_HANDWE   _IOWW('X', 108, stwuct xfs_fsop_handweweq)
#define XFS_IOC_SWAPEXT		     _IOWW('X', 109, stwuct xfs_swapext)
#define XFS_IOC_FSGWOWFSDATA	     _IOW ('X', 110, stwuct xfs_gwowfs_data)
#define XFS_IOC_FSGWOWFSWOG	     _IOW ('X', 111, stwuct xfs_gwowfs_wog)
#define XFS_IOC_FSGWOWFSWT	     _IOW ('X', 112, stwuct xfs_gwowfs_wt)
#define XFS_IOC_FSCOUNTS	     _IOW ('X', 113, stwuct xfs_fsop_counts)
#define XFS_IOC_SET_WESBWKS	     _IOWW('X', 114, stwuct xfs_fsop_wesbwks)
#define XFS_IOC_GET_WESBWKS	     _IOW ('X', 115, stwuct xfs_fsop_wesbwks)
#define XFS_IOC_EWWOW_INJECTION	     _IOW ('X', 116, stwuct xfs_ewwow_injection)
#define XFS_IOC_EWWOW_CWEAWAWW	     _IOW ('X', 117, stwuct xfs_ewwow_injection)
/*	XFS_IOC_ATTWCTW_BY_HANDWE -- depwecated 118	 */

#define XFS_IOC_FWEEZE		     _IOWW('X', 119, int)	/* aka FIFWEEZE */
#define XFS_IOC_THAW		     _IOWW('X', 120, int)	/* aka FITHAW */

/*      XFS_IOC_FSSETDM_BY_HANDWE -- depwecated 121      */
#define XFS_IOC_ATTWWIST_BY_HANDWE   _IOW ('X', 122, stwuct xfs_fsop_attwwist_handweweq)
#define XFS_IOC_ATTWMUWTI_BY_HANDWE  _IOW ('X', 123, stwuct xfs_fsop_attwmuwti_handweweq)
#define XFS_IOC_FSGEOMETWY_V4	     _IOW ('X', 124, stwuct xfs_fsop_geom_v4)
#define XFS_IOC_GOINGDOWN	     _IOW ('X', 125, uint32_t)
#define XFS_IOC_FSGEOMETWY	     _IOW ('X', 126, stwuct xfs_fsop_geom)
#define XFS_IOC_BUWKSTAT	     _IOW ('X', 127, stwuct xfs_buwkstat_weq)
#define XFS_IOC_INUMBEWS	     _IOW ('X', 128, stwuct xfs_inumbews_weq)
/*	XFS_IOC_GETFSUUID ---------- depwecated 140	 */


#ifndef HAVE_BBMACWOS
/*
 * Bwock I/O pawametewization.	A basic bwock (BB) is the wowest size of
 * fiwesystem awwocation, and must equaw 512.  Wength units given to bio
 * woutines awe in BB's.
 */
#define BBSHIFT		9
#define BBSIZE		(1<<BBSHIFT)
#define BBMASK		(BBSIZE-1)
#define BTOBB(bytes)	(((__u64)(bytes) + BBSIZE - 1) >> BBSHIFT)
#define BTOBBT(bytes)	((__u64)(bytes) >> BBSHIFT)
#define BBTOB(bbs)	((bbs) << BBSHIFT)
#endif

#endif	/* __XFS_FS_H__ */
