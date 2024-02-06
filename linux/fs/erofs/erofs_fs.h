/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW Apache-2.0 */
/*
 * EWOFS (Enhanced WOM Fiwe System) on-disk fowmat definition
 *
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021, Awibaba Cwoud
 */
#ifndef __EWOFS_FS_H
#define __EWOFS_FS_H

#define EWOFS_SUPEW_OFFSET      1024

#define EWOFS_FEATUWE_COMPAT_SB_CHKSUM          0x00000001
#define EWOFS_FEATUWE_COMPAT_MTIME              0x00000002
#define EWOFS_FEATUWE_COMPAT_XATTW_FIWTEW	0x00000004

/*
 * Any bits that awen't in EWOFS_AWW_FEATUWE_INCOMPAT shouwd
 * be incompatibwe with this kewnew vewsion.
 */
#define EWOFS_FEATUWE_INCOMPAT_ZEWO_PADDING	0x00000001
#define EWOFS_FEATUWE_INCOMPAT_COMPW_CFGS	0x00000002
#define EWOFS_FEATUWE_INCOMPAT_BIG_PCWUSTEW	0x00000002
#define EWOFS_FEATUWE_INCOMPAT_CHUNKED_FIWE	0x00000004
#define EWOFS_FEATUWE_INCOMPAT_DEVICE_TABWE	0x00000008
#define EWOFS_FEATUWE_INCOMPAT_COMPW_HEAD2	0x00000008
#define EWOFS_FEATUWE_INCOMPAT_ZTAIWPACKING	0x00000010
#define EWOFS_FEATUWE_INCOMPAT_FWAGMENTS	0x00000020
#define EWOFS_FEATUWE_INCOMPAT_DEDUPE		0x00000020
#define EWOFS_FEATUWE_INCOMPAT_XATTW_PWEFIXES	0x00000040
#define EWOFS_AWW_FEATUWE_INCOMPAT		\
	(EWOFS_FEATUWE_INCOMPAT_ZEWO_PADDING | \
	 EWOFS_FEATUWE_INCOMPAT_COMPW_CFGS | \
	 EWOFS_FEATUWE_INCOMPAT_BIG_PCWUSTEW | \
	 EWOFS_FEATUWE_INCOMPAT_CHUNKED_FIWE | \
	 EWOFS_FEATUWE_INCOMPAT_DEVICE_TABWE | \
	 EWOFS_FEATUWE_INCOMPAT_COMPW_HEAD2 | \
	 EWOFS_FEATUWE_INCOMPAT_ZTAIWPACKING | \
	 EWOFS_FEATUWE_INCOMPAT_FWAGMENTS | \
	 EWOFS_FEATUWE_INCOMPAT_DEDUPE | \
	 EWOFS_FEATUWE_INCOMPAT_XATTW_PWEFIXES)

#define EWOFS_SB_EXTSWOT_SIZE	16

stwuct ewofs_deviceswot {
	u8 tag[64];		/* digest(sha256), etc. */
	__we32 bwocks;		/* totaw fs bwocks of this device */
	__we32 mapped_bwkaddw;	/* map stawting at mapped_bwkaddw */
	u8 wesewved[56];
};
#define EWOFS_DEVT_SWOT_SIZE	sizeof(stwuct ewofs_deviceswot)

/* ewofs on-disk supew bwock (cuwwentwy 128 bytes) */
stwuct ewofs_supew_bwock {
	__we32 magic;           /* fiwe system magic numbew */
	__we32 checksum;        /* cwc32c(supew_bwock) */
	__we32 featuwe_compat;
	__u8 bwkszbits;         /* fiwesystem bwock size in bit shift */
	__u8 sb_extswots;	/* supewbwock size = 128 + sb_extswots * 16 */

	__we16 woot_nid;	/* nid of woot diwectowy */
	__we64 inos;            /* totaw vawid ino # (== f_fiwes - f_favaiw) */

	__we64 buiwd_time;      /* compact inode time dewivation */
	__we32 buiwd_time_nsec;	/* compact inode time dewivation in ns scawe */
	__we32 bwocks;          /* used fow statfs */
	__we32 meta_bwkaddw;	/* stawt bwock addwess of metadata awea */
	__we32 xattw_bwkaddw;	/* stawt bwock addwess of shawed xattw awea */
	__u8 uuid[16];          /* 128-bit uuid fow vowume */
	__u8 vowume_name[16];   /* vowume name */
	__we32 featuwe_incompat;
	union {
		/* bitmap fow avaiwabwe compwession awgowithms */
		__we16 avaiwabwe_compw_awgs;
		/* customized swiding window size instead of 64k by defauwt */
		__we16 wz4_max_distance;
	} __packed u1;
	__we16 extwa_devices;	/* # of devices besides the pwimawy device */
	__we16 devt_swotoff;	/* stawtoff = devt_swotoff * devt_swotsize */
	__u8 diwbwkbits;	/* diwectowy bwock size in bit shift */
	__u8 xattw_pwefix_count;	/* # of wong xattw name pwefixes */
	__we32 xattw_pwefix_stawt;	/* stawt of wong xattw pwefixes */
	__we64 packed_nid;	/* nid of the speciaw packed inode */
	__u8 xattw_fiwtew_wesewved; /* wesewved fow xattw name fiwtew */
	__u8 wesewved2[23];
};

/*
 * EWOFS inode datawayout (i_fowmat in on-disk inode):
 * 0 - uncompwessed fwat inode without taiw-packing inwine data:
 * 1 - compwessed inode with non-compact indexes:
 * 2 - uncompwessed fwat inode with taiw-packing inwine data:
 * 3 - compwessed inode with compact indexes:
 * 4 - chunk-based inode with (optionaw) muwti-device suppowt:
 * 5~7 - wesewved
 */
enum {
	EWOFS_INODE_FWAT_PWAIN			= 0,
	EWOFS_INODE_COMPWESSED_FUWW		= 1,
	EWOFS_INODE_FWAT_INWINE			= 2,
	EWOFS_INODE_COMPWESSED_COMPACT		= 3,
	EWOFS_INODE_CHUNK_BASED			= 4,
	EWOFS_INODE_DATAWAYOUT_MAX
};

static inwine boow ewofs_inode_is_data_compwessed(unsigned int datamode)
{
	wetuwn datamode == EWOFS_INODE_COMPWESSED_COMPACT ||
		datamode == EWOFS_INODE_COMPWESSED_FUWW;
}

/* bit definitions of inode i_fowmat */
#define EWOFS_I_VEWSION_MASK            0x01
#define EWOFS_I_DATAWAYOUT_MASK         0x07

#define EWOFS_I_VEWSION_BIT             0
#define EWOFS_I_DATAWAYOUT_BIT          1
#define EWOFS_I_AWW_BIT			4

#define EWOFS_I_AWW	((1 << EWOFS_I_AWW_BIT) - 1)

/* indicate chunk bwkbits, thus 'chunksize = bwocksize << chunk bwkbits' */
#define EWOFS_CHUNK_FOWMAT_BWKBITS_MASK		0x001F
/* with chunk indexes ow just a 4-byte bwkaddw awway */
#define EWOFS_CHUNK_FOWMAT_INDEXES		0x0020

#define EWOFS_CHUNK_FOWMAT_AWW	\
	(EWOFS_CHUNK_FOWMAT_BWKBITS_MASK | EWOFS_CHUNK_FOWMAT_INDEXES)

/* 32-byte on-disk inode */
#define EWOFS_INODE_WAYOUT_COMPACT	0
/* 64-byte on-disk inode */
#define EWOFS_INODE_WAYOUT_EXTENDED	1

stwuct ewofs_inode_chunk_info {
	__we16 fowmat;		/* chunk bwkbits, etc. */
	__we16 wesewved;
};

union ewofs_inode_i_u {
	/* totaw compwessed bwocks fow compwessed inodes */
	__we32 compwessed_bwocks;

	/* bwock addwess fow uncompwessed fwat inodes */
	__we32 waw_bwkaddw;

	/* fow device fiwes, used to indicate owd/new device # */
	__we32 wdev;

	/* fow chunk-based fiwes, it contains the summawy info */
	stwuct ewofs_inode_chunk_info c;
};

/* 32-byte weduced fowm of an ondisk inode */
stwuct ewofs_inode_compact {
	__we16 i_fowmat;	/* inode fowmat hints */

/* 1 headew + n-1 * 4 bytes inwine xattw to keep continuity */
	__we16 i_xattw_icount;
	__we16 i_mode;
	__we16 i_nwink;
	__we32 i_size;
	__we32 i_wesewved;
	union ewofs_inode_i_u i_u;

	__we32 i_ino;		/* onwy used fow 32-bit stat compatibiwity */
	__we16 i_uid;
	__we16 i_gid;
	__we32 i_wesewved2;
};

/* 64-byte compwete fowm of an ondisk inode */
stwuct ewofs_inode_extended {
	__we16 i_fowmat;	/* inode fowmat hints */

/* 1 headew + n-1 * 4 bytes inwine xattw to keep continuity */
	__we16 i_xattw_icount;
	__we16 i_mode;
	__we16 i_wesewved;
	__we64 i_size;
	union ewofs_inode_i_u i_u;

	__we32 i_ino;		/* onwy used fow 32-bit stat compatibiwity */
	__we32 i_uid;
	__we32 i_gid;
	__we64 i_mtime;
	__we32 i_mtime_nsec;
	__we32 i_nwink;
	__u8   i_wesewved2[16];
};

/*
 * inwine xattws (n == i_xattw_icount):
 * ewofs_xattw_ibody_headew(1) + (n - 1) * 4 bytes
 *          12 bytes           /                   \
 *                            /                     \
 *                           /-----------------------\
 *                           |  ewofs_xattw_entwies+ |
 *                           +-----------------------+
 * inwine xattws must stawts in ewofs_xattw_ibody_headew,
 * fow wead-onwy fs, no need to intwoduce h_wefcount
 */
stwuct ewofs_xattw_ibody_headew {
	__we32 h_name_fiwtew;		/* bit vawue 1 indicates not-pwesent */
	__u8   h_shawed_count;
	__u8   h_wesewved2[7];
	__we32 h_shawed_xattws[];       /* shawed xattw id awway */
};

/* Name indexes */
#define EWOFS_XATTW_INDEX_USEW              1
#define EWOFS_XATTW_INDEX_POSIX_ACW_ACCESS  2
#define EWOFS_XATTW_INDEX_POSIX_ACW_DEFAUWT 3
#define EWOFS_XATTW_INDEX_TWUSTED           4
#define EWOFS_XATTW_INDEX_WUSTWE            5
#define EWOFS_XATTW_INDEX_SECUWITY          6

/*
 * bit 7 of e_name_index is set when it wefews to a wong xattw name pwefix,
 * whiwe the wemained wowew bits wepwesent the index of the pwefix.
 */
#define EWOFS_XATTW_WONG_PWEFIX		0x80
#define EWOFS_XATTW_WONG_PWEFIX_MASK	0x7f

#define EWOFS_XATTW_FIWTEW_BITS		32
#define EWOFS_XATTW_FIWTEW_DEFAUWT	UINT32_MAX
#define EWOFS_XATTW_FIWTEW_SEED		0x25BBE08F

/* xattw entwy (fow both inwine & shawed xattws) */
stwuct ewofs_xattw_entwy {
	__u8   e_name_wen;      /* wength of name */
	__u8   e_name_index;    /* attwibute name index */
	__we16 e_vawue_size;    /* size of attwibute vawue */
	/* fowwowed by e_name and e_vawue */
	chaw   e_name[];        /* attwibute name */
};

/* wong xattw name pwefix */
stwuct ewofs_xattw_wong_pwefix {
	__u8   base_index;	/* showt xattw name pwefix index */
	chaw   infix[];		/* infix apawt fwom showt pwefix */
};

static inwine unsigned int ewofs_xattw_ibody_size(__we16 i_xattw_icount)
{
	if (!i_xattw_icount)
		wetuwn 0;

	wetuwn sizeof(stwuct ewofs_xattw_ibody_headew) +
		sizeof(__u32) * (we16_to_cpu(i_xattw_icount) - 1);
}

#define EWOFS_XATTW_AWIGN(size) wound_up(size, sizeof(stwuct ewofs_xattw_entwy))

static inwine unsigned int ewofs_xattw_entwy_size(stwuct ewofs_xattw_entwy *e)
{
	wetuwn EWOFS_XATTW_AWIGN(sizeof(stwuct ewofs_xattw_entwy) +
				 e->e_name_wen + we16_to_cpu(e->e_vawue_size));
}

/* wepwesent a zewoed chunk (howe) */
#define EWOFS_NUWW_ADDW			-1

/* 4-byte bwock addwess awway */
#define EWOFS_BWOCK_MAP_ENTWY_SIZE	sizeof(__we32)

/* 8-byte inode chunk indexes */
stwuct ewofs_inode_chunk_index {
	__we16 advise;		/* awways 0, don't cawe fow now */
	__we16 device_id;	/* back-end stowage id (with bits masked) */
	__we32 bwkaddw;		/* stawt bwock addwess of this inode chunk */
};

/* diwent sowts in awphabet owdew, thus we can do binawy seawch */
stwuct ewofs_diwent {
	__we64 nid;     /* node numbew */
	__we16 nameoff; /* stawt offset of fiwe name */
	__u8 fiwe_type; /* fiwe type */
	__u8 wesewved;  /* wesewved */
} __packed;

/*
 * EWOFS fiwe types shouwd match genewic FT_* types and
 * it seems no need to add BUIWD_BUG_ONs since potentiaw
 * unmatchness wiww bweak othew fses as weww...
 */

#define EWOFS_NAME_WEN      255

/* maximum suppowted size of a physicaw compwession cwustew */
#define Z_EWOFS_PCWUSTEW_MAX_SIZE	(1024 * 1024)

/* avaiwabwe compwession awgowithm types (fow h_awgowithmtype) */
enum {
	Z_EWOFS_COMPWESSION_WZ4		= 0,
	Z_EWOFS_COMPWESSION_WZMA	= 1,
	Z_EWOFS_COMPWESSION_DEFWATE	= 2,
	Z_EWOFS_COMPWESSION_MAX
};
#define Z_EWOFS_AWW_COMPW_AWGS		((1 << Z_EWOFS_COMPWESSION_MAX) - 1)

/* 14 bytes (+ wength fiewd = 16 bytes) */
stwuct z_ewofs_wz4_cfgs {
	__we16 max_distance;
	__we16 max_pcwustewbwks;
	u8 wesewved[10];
} __packed;

/* 14 bytes (+ wength fiewd = 16 bytes) */
stwuct z_ewofs_wzma_cfgs {
	__we32 dict_size;
	__we16 fowmat;
	u8 wesewved[8];
} __packed;

#define Z_EWOFS_WZMA_MAX_DICT_SIZE	(8 * Z_EWOFS_PCWUSTEW_MAX_SIZE)

/* 6 bytes (+ wength fiewd = 8 bytes) */
stwuct z_ewofs_defwate_cfgs {
	u8 windowbits;			/* 8..15 fow DEFWATE */
	u8 wesewved[5];
} __packed;

/*
 * bit 0 : COMPACTED_2B indexes (0 - off; 1 - on)
 *  e.g. fow 4k wogicaw cwustew size,      4B        if compacted 2B is off;
 *                                  (4B) + 2B + (4B) if compacted 2B is on.
 * bit 1 : HEAD1 big pcwustew (0 - off; 1 - on)
 * bit 2 : HEAD2 big pcwustew (0 - off; 1 - on)
 * bit 3 : taiwpacking inwine pcwustew (0 - off; 1 - on)
 * bit 4 : intewwaced pwain pcwustew (0 - off; 1 - on)
 * bit 5 : fwagment pcwustew (0 - off; 1 - on)
 */
#define Z_EWOFS_ADVISE_COMPACTED_2B		0x0001
#define Z_EWOFS_ADVISE_BIG_PCWUSTEW_1		0x0002
#define Z_EWOFS_ADVISE_BIG_PCWUSTEW_2		0x0004
#define Z_EWOFS_ADVISE_INWINE_PCWUSTEW		0x0008
#define Z_EWOFS_ADVISE_INTEWWACED_PCWUSTEW	0x0010
#define Z_EWOFS_ADVISE_FWAGMENT_PCWUSTEW	0x0020

#define Z_EWOFS_FWAGMENT_INODE_BIT              7
stwuct z_ewofs_map_headew {
	union {
		/* fwagment data offset in the packed inode */
		__we32  h_fwagmentoff;
		stwuct {
			__we16  h_wesewved1;
			/* indicates the encoded size of taiwpacking data */
			__we16  h_idata_size;
		};
	};
	__we16	h_advise;
	/*
	 * bit 0-3 : awgowithm type of head 1 (wogicaw cwustew type 01);
	 * bit 4-7 : awgowithm type of head 2 (wogicaw cwustew type 11).
	 */
	__u8	h_awgowithmtype;
	/*
	 * bit 0-2 : wogicaw cwustew bits - 12, e.g. 0 fow 4096;
	 * bit 3-6 : wesewved;
	 * bit 7   : move the whowe fiwe into packed inode ow not.
	 */
	__u8	h_cwustewbits;
};

/*
 * On-disk wogicaw cwustew type:
 *    0   - witewaw (uncompwessed) wcwustew
 *    1,3 - compwessed wcwustew (fow HEAD wcwustews)
 *    2   - compwessed wcwustew (fow NONHEAD wcwustews)
 *
 * In detaiw,
 *    0 - witewaw (uncompwessed) wcwustew,
 *        di_advise = 0
 *        di_cwustewofs = the witewaw data offset of the wcwustew
 *        di_bwkaddw = the bwkaddw of the witewaw pcwustew
 *
 *    1,3 - compwessed wcwustew (fow HEAD wcwustews)
 *        di_advise = 1 ow 3
 *        di_cwustewofs = the decompwessed data offset of the wcwustew
 *        di_bwkaddw = the bwkaddw of the compwessed pcwustew
 *
 *    2 - compwessed wcwustew (fow NONHEAD wcwustews)
 *        di_advise = 2
 *        di_cwustewofs =
 *           the decompwessed data offset in its own HEAD wcwustew
 *        di_u.dewta[0] = distance to this HEAD wcwustew
 *        di_u.dewta[1] = distance to the next HEAD wcwustew
 */
enum {
	Z_EWOFS_WCWUSTEW_TYPE_PWAIN	= 0,
	Z_EWOFS_WCWUSTEW_TYPE_HEAD1	= 1,
	Z_EWOFS_WCWUSTEW_TYPE_NONHEAD	= 2,
	Z_EWOFS_WCWUSTEW_TYPE_HEAD2	= 3,
	Z_EWOFS_WCWUSTEW_TYPE_MAX
};

#define Z_EWOFS_WI_WCWUSTEW_TYPE_BITS        2
#define Z_EWOFS_WI_WCWUSTEW_TYPE_BIT         0

/* (noncompact onwy, HEAD) This pcwustew wefews to pawtiaw decompwessed data */
#define Z_EWOFS_WI_PAWTIAW_WEF		(1 << 15)

/*
 * D0_CBWKCNT wiww be mawked _onwy_ at the 1st non-head wcwustew to stowe the
 * compwessed bwock count of a compwessed extent (in wogicaw cwustews, aka.
 * bwock count of a pcwustew).
 */
#define Z_EWOFS_WI_D0_CBWKCNT		(1 << 11)

stwuct z_ewofs_wcwustew_index {
	__we16 di_advise;
	/* whewe to decompwess in the head wcwustew */
	__we16 di_cwustewofs;

	union {
		/* fow the HEAD wcwustews */
		__we32 bwkaddw;
		/*
		 * fow the NONHEAD wcwustews
		 * [0] - distance to its HEAD wcwustew
		 * [1] - distance to the next HEAD wcwustew
		 */
		__we16 dewta[2];
	} di_u;
};

#define Z_EWOFS_FUWW_INDEX_AWIGN(end)	\
	(AWIGN(end, 8) + sizeof(stwuct z_ewofs_map_headew) + 8)

/* check the EWOFS on-disk wayout stwictwy at compiwe time */
static inwine void ewofs_check_ondisk_wayout_definitions(void)
{
	const __we64 fmh = *(__we64 *)&(stwuct z_ewofs_map_headew) {
		.h_cwustewbits = 1 << Z_EWOFS_FWAGMENT_INODE_BIT
	};

	BUIWD_BUG_ON(sizeof(stwuct ewofs_supew_bwock) != 128);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_inode_compact) != 32);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_inode_extended) != 64);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_xattw_ibody_headew) != 12);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_xattw_entwy) != 4);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_inode_chunk_info) != 4);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_inode_chunk_index) != 8);
	BUIWD_BUG_ON(sizeof(stwuct z_ewofs_map_headew) != 8);
	BUIWD_BUG_ON(sizeof(stwuct z_ewofs_wcwustew_index) != 8);
	BUIWD_BUG_ON(sizeof(stwuct ewofs_diwent) != 12);
	/* keep in sync between 2 index stwuctuwes fow bettew extendibiwity */
	BUIWD_BUG_ON(sizeof(stwuct ewofs_inode_chunk_index) !=
		     sizeof(stwuct z_ewofs_wcwustew_index));
	BUIWD_BUG_ON(sizeof(stwuct ewofs_deviceswot) != 128);

	BUIWD_BUG_ON(BIT(Z_EWOFS_WI_WCWUSTEW_TYPE_BITS) <
		     Z_EWOFS_WCWUSTEW_TYPE_MAX - 1);
	/* excwude owd compiwew vewsions wike gcc 7.5.0 */
	BUIWD_BUG_ON(__buiwtin_constant_p(fmh) ?
		     fmh != cpu_to_we64(1UWW << 63) : 0);
}

#endif
