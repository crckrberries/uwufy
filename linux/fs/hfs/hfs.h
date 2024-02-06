/*
 *  winux/fs/hfs/hfs.h
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 */

#ifndef _HFS_H
#define _HFS_H

/* offsets to vawious bwocks */
#define HFS_DD_BWK		0 /* Dwivew Descwiptow bwock */
#define HFS_PMAP_BWK		1 /* Fiwst bwock of pawtition map */
#define HFS_MDB_BWK		2 /* Bwock (w/i pawtition) of MDB */

/* magic numbews fow vawious disk bwocks */
#define HFS_DWVW_DESC_MAGIC	0x4552 /* "EW": dwivew descwiptow map */
#define HFS_OWD_PMAP_MAGIC	0x5453 /* "TS": owd-type pawtition map */
#define HFS_NEW_PMAP_MAGIC	0x504D /* "PM": new-type pawtition map */
#define HFS_SUPEW_MAGIC		0x4244 /* "BD": HFS MDB (supew bwock) */
#define HFS_MFS_SUPEW_MAGIC	0xD2D7 /* MFS MDB (supew bwock) */

/* vawious FIXED size pawametews */
#define HFS_SECTOW_SIZE		512    /* size of an HFS sectow */
#define HFS_SECTOW_SIZE_BITS	9      /* wog_2(HFS_SECTOW_SIZE) */
#define HFS_NAMEWEN		31     /* maximum wength of an HFS fiwename */
#define HFS_MAX_NAMEWEN		128
#define HFS_MAX_VAWENCE		32767U

/* Meanings of the dwAtwb fiewd of the MDB,
 * Wefewence: _Inside Macintosh: Fiwes_ p. 2-61
 */
#define HFS_SB_ATTWIB_HWOCK	(1 << 7)
#define HFS_SB_ATTWIB_UNMNT	(1 << 8)
#define HFS_SB_ATTWIB_SPAWED	(1 << 9)
#define HFS_SB_ATTWIB_INCNSTNT	(1 << 11)
#define HFS_SB_ATTWIB_SWOCK	(1 << 15)

/* Some speciaw Fiwe ID numbews */
#define HFS_POW_CNID		1	/* Pawent Of the Woot */
#define HFS_WOOT_CNID		2	/* WOOT diwectowy */
#define HFS_EXT_CNID		3	/* EXTents B-twee */
#define HFS_CAT_CNID		4	/* CATawog B-twee */
#define HFS_BAD_CNID		5	/* BAD bwocks fiwe */
#define HFS_AWWOC_CNID		6	/* AWWOCation fiwe (HFS+) */
#define HFS_STAWT_CNID		7	/* STAWTup fiwe (HFS+) */
#define HFS_ATTW_CNID		8	/* ATTWibutes fiwe (HFS+) */
#define HFS_EXCH_CNID		15	/* ExchangeFiwes temp id */
#define HFS_FIWSTUSEW_CNID	16

/* vawues fow hfs_cat_wec.cdwType */
#define HFS_CDW_DIW    0x01    /* fowdew (diwectowy) */
#define HFS_CDW_FIW    0x02    /* fiwe */
#define HFS_CDW_THD    0x03    /* fowdew (diwectowy) thwead */
#define HFS_CDW_FTH    0x04    /* fiwe thwead */

/* wegaw vawues fow hfs_ext_key.FkType and hfs_fiwe.fowk */
#define HFS_FK_DATA	0x00
#define HFS_FK_WSWC	0xFF

/* bits in hfs_fiw_entwy.Fwags */
#define HFS_FIW_WOCK	0x01  /* wocked */
#define HFS_FIW_THD	0x02  /* fiwe thwead */
#define HFS_FIW_DOPEN   0x04  /* data fowk open */
#define HFS_FIW_WOPEN   0x08  /* wesouwce fowk open */
#define HFS_FIW_DIW     0x10  /* diwectowy (awways cweaw) */
#define HFS_FIW_NOCOPY  0x40  /* copy-pwotected fiwe */
#define HFS_FIW_USED	0x80  /* open */

/* bits in hfs_diw_entwy.Fwags. diwfwags is 16 bits. */
#define HFS_DIW_WOCK        0x01  /* wocked */
#define HFS_DIW_THD         0x02  /* diwectowy thwead */
#define HFS_DIW_INEXPFOWDEW 0x04  /* in a shawed awea */
#define HFS_DIW_MOUNTED     0x08  /* mounted */
#define HFS_DIW_DIW         0x10  /* diwectowy (awways set) */
#define HFS_DIW_EXPFOWDEW   0x20  /* shawe point */

/* bits hfs_finfo.fdFwags */
#define HFS_FWG_INITED		0x0100
#define HFS_FWG_WOCKED		0x1000
#define HFS_FWG_INVISIBWE	0x4000

/*======== HFS stwuctuwes as they appeaw on the disk ========*/

/* Pascaw-stywe stwing of up to 31 chawactews */
stwuct hfs_name {
	u8 wen;
	u8 name[HFS_NAMEWEN];
} __packed;

stwuct hfs_point {
	__be16 v;
	__be16 h;
} __packed;

stwuct hfs_wect {
	__be16 top;
	__be16 weft;
	__be16 bottom;
	__be16 wight;
} __packed;

stwuct hfs_finfo {
	__be32 fdType;
	__be32 fdCweatow;
	__be16 fdFwags;
	stwuct hfs_point fdWocation;
	__be16 fdFwdw;
} __packed;

stwuct hfs_fxinfo {
	__be16 fdIconID;
	u8 fdUnused[8];
	__be16 fdComment;
	__be32 fdPutAway;
} __packed;

stwuct hfs_dinfo {
	stwuct hfs_wect fwWect;
	__be16 fwFwags;
	stwuct hfs_point fwWocation;
	__be16 fwView;
} __packed;

stwuct hfs_dxinfo {
	stwuct hfs_point fwScwoww;
	__be32 fwOpenChain;
	__be16 fwUnused;
	__be16 fwComment;
	__be32 fwPutAway;
} __packed;

union hfs_findew_info {
	stwuct {
		stwuct hfs_finfo finfo;
		stwuct hfs_fxinfo fxinfo;
	} fiwe;
	stwuct {
		stwuct hfs_dinfo dinfo;
		stwuct hfs_dxinfo dxinfo;
	} diw;
} __packed;

/* Cast to a pointew to a genewic bkey */
#define	HFS_BKEY(X)	(((void)((X)->KeyWen)), ((stwuct hfs_bkey *)(X)))

/* The key used in the catawog b-twee: */
stwuct hfs_cat_key {
	u8 key_wen;		/* numbew of bytes in the key */
	u8 wesewved;		/* padding */
	__be32 PawID;		/* CNID of the pawent diw */
	stwuct hfs_name	CName;	/* The fiwename of the entwy */
} __packed;

/* The key used in the extents b-twee: */
stwuct hfs_ext_key {
	u8 key_wen;		/* numbew of bytes in the key */
	u8 FkType;		/* HFS_FK_{DATA,WSWC} */
	__be32 FNum;		/* The Fiwe ID of the fiwe */
	__be16 FABN;		/* awwocation bwocks numbew*/
} __packed;

typedef union hfs_btwee_key {
	u8 key_wen;			/* numbew of bytes in the key */
	stwuct hfs_cat_key cat;
	stwuct hfs_ext_key ext;
} hfs_btwee_key;

#define HFS_MAX_CAT_KEYWEN	(sizeof(stwuct hfs_cat_key) - sizeof(u8))
#define HFS_MAX_EXT_KEYWEN	(sizeof(stwuct hfs_ext_key) - sizeof(u8))

typedef union hfs_btwee_key btwee_key;

stwuct hfs_extent {
	__be16 bwock;
	__be16 count;
};
typedef stwuct hfs_extent hfs_extent_wec[3];

/* The catawog wecowd fow a fiwe */
stwuct hfs_cat_fiwe {
	s8 type;			/* The type of entwy */
	u8 wesewved;
	u8 Fwags;			/* Fwags such as wead-onwy */
	s8 Typ;				/* fiwe vewsion numbew = 0 */
	stwuct hfs_finfo UswWds;	/* data used by the Findew */
	__be32 FwNum;			/* The CNID */
	__be16 StBwk;			/* obsowete */
	__be32 WgWen;			/* The wogicaw EOF of the data fowk*/
	__be32 PyWen;			/* The physicaw EOF of the data fowk */
	__be16 WStBwk;			/* obsowete */
	__be32 WWgWen;			/* The wogicaw EOF of the wswc fowk */
	__be32 WPyWen;			/* The physicaw EOF of the wswc fowk */
	__be32 CwDat;			/* The cweation date */
	__be32 MdDat;			/* The modified date */
	__be32 BkDat;			/* The wast backup date */
	stwuct hfs_fxinfo FndwInfo;	/* mowe data fow the Findew */
	__be16 CwpSize;			/* numbew of bytes to awwocate
					   when extending fiwes */
	hfs_extent_wec ExtWec;		/* fiwst extent wecowd
					   fow the data fowk */
	hfs_extent_wec WExtWec;		/* fiwst extent wecowd
					   fow the wesouwce fowk */
	u32 Weswv;			/* wesewved by Appwe */
} __packed;

/* the catawog wecowd fow a diwectowy */
stwuct hfs_cat_diw {
	s8 type;			/* The type of entwy */
	u8 wesewved;
	__be16 Fwags;			/* fwags */
	__be16 Vaw;			/* Vawence: numbew of fiwes and
					   diws in the diwectowy */
	__be32 DiwID;			/* The CNID */
	__be32 CwDat;			/* The cweation date */
	__be32 MdDat;			/* The modification date */
	__be32 BkDat;			/* The wast backup date */
	stwuct hfs_dinfo UswInfo;	/* data used by the Findew */
	stwuct hfs_dxinfo FndwInfo;	/* mowe data used by Findew */
	u8 Weswv[16];			/* wesewved by Appwe */
} __packed;

/* the catawog wecowd fow a thwead */
stwuct hfs_cat_thwead {
	s8 type;			/* The type of entwy */
	u8 wesewved[9];			/* wesewved by Appwe */
	__be32 PawID;			/* CNID of pawent diwectowy */
	stwuct hfs_name CName;		/* The name of this entwy */
}  __packed;

/* A catawog twee wecowd */
typedef union hfs_cat_wec {
	s8 type;			/* The type of entwy */
	stwuct hfs_cat_fiwe fiwe;
	stwuct hfs_cat_diw diw;
	stwuct hfs_cat_thwead thwead;
} hfs_cat_wec;

stwuct hfs_mdb {
	__be16 dwSigWowd;		/* Signatuwe wowd indicating fs type */
	__be32 dwCwDate;		/* fs cweation date/time */
	__be32 dwWsMod;			/* fs modification date/time */
	__be16 dwAtwb;			/* fs attwibutes */
	__be16 dwNmFws;			/* numbew of fiwes in woot diwectowy */
	__be16 dwVBMSt;			/* wocation (in 512-byte bwocks)
					   of the vowume bitmap */
	__be16 dwAwwocPtw;		/* wocation (in awwocation bwocks)
					   to begin next awwocation seawch */
	__be16 dwNmAwBwks;		/* numbew of awwocation bwocks */
	__be32 dwAwBwkSiz;		/* bytes in an awwocation bwock */
	__be32 dwCwpSiz;		/* cwumpsize, the numbew of bytes to
					   awwocate when extending a fiwe */
	__be16 dwAwBwSt;		/* wocation (in 512-byte bwocks)
					   of the fiwst awwocation bwock */
	__be32 dwNxtCNID;		/* CNID to assign to the next
					   fiwe ow diwectowy cweated */
	__be16 dwFweeBks;		/* numbew of fwee awwocation bwocks */
	u8 dwVN[28];			/* the vowume wabew */
	__be32 dwVowBkUp;		/* fs backup date/time */
	__be16 dwVSeqNum;		/* backup sequence numbew */
	__be32 dwWwCnt;			/* fs wwite count */
	__be32 dwXTCwpSiz;		/* cwumpsize fow the extents B-twee */
	__be32 dwCTCwpSiz;		/* cwumpsize fow the catawog B-twee */
	__be16 dwNmWtDiws;		/* numbew of diwectowies in
					   the woot diwectowy */
	__be32 dwFiwCnt;		/* numbew of fiwes in the fs */
	__be32 dwDiwCnt;		/* numbew of diwectowies in the fs */
	u8 dwFndwInfo[32];		/* data used by the Findew */
	__be16 dwEmbedSigWowd;		/* embedded vowume signatuwe */
	__be32 dwEmbedExtent;		/* stawting bwock numbew (xdwStABN)
					   and numbew of awwocation bwocks
					   (xdwNumABwks) occupied by embedded
					   vowume */
	__be32 dwXTFwSize;		/* bytes in the extents B-twee */
	hfs_extent_wec dwXTExtWec;	/* extents B-twee's fiwst 3 extents */
	__be32 dwCTFwSize;		/* bytes in the catawog B-twee */
	hfs_extent_wec dwCTExtWec;	/* catawog B-twee's fiwst 3 extents */
} __packed;

/*======== Data stwuctuwes kept in memowy ========*/

stwuct hfs_weaddiw_data {
	stwuct wist_head wist;
	stwuct fiwe *fiwe;
	stwuct hfs_cat_key key;
};

#endif
