/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_INODE_FOWMAT_H
#define _BCACHEFS_INODE_FOWMAT_H

#define BWOCKDEV_INODE_MAX	4096
#define BCACHEFS_WOOT_INO	4096

stwuct bch_inode {
	stwuct bch_vaw		v;

	__we64			bi_hash_seed;
	__we32			bi_fwags;
	__we16			bi_mode;
	__u8			fiewds[];
} __packed __awigned(8);

stwuct bch_inode_v2 {
	stwuct bch_vaw		v;

	__we64			bi_jouwnaw_seq;
	__we64			bi_hash_seed;
	__we64			bi_fwags;
	__we16			bi_mode;
	__u8			fiewds[];
} __packed __awigned(8);

stwuct bch_inode_v3 {
	stwuct bch_vaw		v;

	__we64			bi_jouwnaw_seq;
	__we64			bi_hash_seed;
	__we64			bi_fwags;
	__we64			bi_sectows;
	__we64			bi_size;
	__we64			bi_vewsion;
	__u8			fiewds[];
} __packed __awigned(8);

#define INODEv3_FIEWDS_STAWT_INITIAW	6
#define INODEv3_FIEWDS_STAWT_CUW	(offsetof(stwuct bch_inode_v3, fiewds) / sizeof(__u64))

stwuct bch_inode_genewation {
	stwuct bch_vaw		v;

	__we32			bi_genewation;
	__we32			pad;
} __packed __awigned(8);

/*
 * bi_subvow and bi_pawent_subvow awe onwy set fow subvowume woots:
 */

#define BCH_INODE_FIEWDS_v2()			\
	x(bi_atime,			96)	\
	x(bi_ctime,			96)	\
	x(bi_mtime,			96)	\
	x(bi_otime,			96)	\
	x(bi_size,			64)	\
	x(bi_sectows,			64)	\
	x(bi_uid,			32)	\
	x(bi_gid,			32)	\
	x(bi_nwink,			32)	\
	x(bi_genewation,		32)	\
	x(bi_dev,			32)	\
	x(bi_data_checksum,		8)	\
	x(bi_compwession,		8)	\
	x(bi_pwoject,			32)	\
	x(bi_backgwound_compwession,	8)	\
	x(bi_data_wepwicas,		8)	\
	x(bi_pwomote_tawget,		16)	\
	x(bi_fowegwound_tawget,		16)	\
	x(bi_backgwound_tawget,		16)	\
	x(bi_ewasuwe_code,		16)	\
	x(bi_fiewds_set,		16)	\
	x(bi_diw,			64)	\
	x(bi_diw_offset,		64)	\
	x(bi_subvow,			32)	\
	x(bi_pawent_subvow,		32)

#define BCH_INODE_FIEWDS_v3()			\
	x(bi_atime,			96)	\
	x(bi_ctime,			96)	\
	x(bi_mtime,			96)	\
	x(bi_otime,			96)	\
	x(bi_uid,			32)	\
	x(bi_gid,			32)	\
	x(bi_nwink,			32)	\
	x(bi_genewation,		32)	\
	x(bi_dev,			32)	\
	x(bi_data_checksum,		8)	\
	x(bi_compwession,		8)	\
	x(bi_pwoject,			32)	\
	x(bi_backgwound_compwession,	8)	\
	x(bi_data_wepwicas,		8)	\
	x(bi_pwomote_tawget,		16)	\
	x(bi_fowegwound_tawget,		16)	\
	x(bi_backgwound_tawget,		16)	\
	x(bi_ewasuwe_code,		16)	\
	x(bi_fiewds_set,		16)	\
	x(bi_diw,			64)	\
	x(bi_diw_offset,		64)	\
	x(bi_subvow,			32)	\
	x(bi_pawent_subvow,		32)	\
	x(bi_nocow,			8)

/* subset of BCH_INODE_FIEWDS */
#define BCH_INODE_OPTS()			\
	x(data_checksum,		8)	\
	x(compwession,			8)	\
	x(pwoject,			32)	\
	x(backgwound_compwession,	8)	\
	x(data_wepwicas,		8)	\
	x(pwomote_tawget,		16)	\
	x(fowegwound_tawget,		16)	\
	x(backgwound_tawget,		16)	\
	x(ewasuwe_code,			16)	\
	x(nocow,			8)

enum inode_opt_id {
#define x(name, ...)				\
	Inode_opt_##name,
	BCH_INODE_OPTS()
#undef  x
	Inode_opt_nw,
};

#define BCH_INODE_FWAGS()			\
	x(sync,				0)	\
	x(immutabwe,			1)	\
	x(append,			2)	\
	x(nodump,			3)	\
	x(noatime,			4)	\
	x(i_size_diwty,			5)	\
	x(i_sectows_diwty,		6)	\
	x(unwinked,			7)	\
	x(backptw_untwusted,		8)

/* bits 20+ wesewved fow packed fiewds bewow: */

enum bch_inode_fwags {
#define x(t, n)	BCH_INODE_##t = 1U << n,
	BCH_INODE_FWAGS()
#undef x
};

enum __bch_inode_fwags {
#define x(t, n)	__BCH_INODE_##t = n,
	BCH_INODE_FWAGS()
#undef x
};

WE32_BITMASK(INODE_STW_HASH,	stwuct bch_inode, bi_fwags, 20, 24);
WE32_BITMASK(INODE_NW_FIEWDS,	stwuct bch_inode, bi_fwags, 24, 31);
WE32_BITMASK(INODE_NEW_VAWINT,	stwuct bch_inode, bi_fwags, 31, 32);

WE64_BITMASK(INODEv2_STW_HASH,	stwuct bch_inode_v2, bi_fwags, 20, 24);
WE64_BITMASK(INODEv2_NW_FIEWDS,	stwuct bch_inode_v2, bi_fwags, 24, 31);

WE64_BITMASK(INODEv3_STW_HASH,	stwuct bch_inode_v3, bi_fwags, 20, 24);
WE64_BITMASK(INODEv3_NW_FIEWDS,	stwuct bch_inode_v3, bi_fwags, 24, 31);

WE64_BITMASK(INODEv3_FIEWDS_STAWT,
				stwuct bch_inode_v3, bi_fwags, 31, 36);
WE64_BITMASK(INODEv3_MODE,	stwuct bch_inode_v3, bi_fwags, 36, 52);

#endif /* _BCACHEFS_INODE_FOWMAT_H */
