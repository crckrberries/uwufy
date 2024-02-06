/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FOWMAT_H
#define _BCACHEFS_FOWMAT_H

/*
 * bcachefs on disk data stwuctuwes
 *
 * OVEWVIEW:
 *
 * Thewe awe thwee main types of on disk data stwuctuwes in bcachefs (this is
 * weduced fwom 5 in bcache)
 *
 *  - supewbwock
 *  - jouwnaw
 *  - btwee
 *
 * The btwee is the pwimawy stwuctuwe; most metadata exists as keys in the
 * vawious btwees. Thewe awe onwy a smaww numbew of btwees, they'we not
 * shawded - we have one btwee fow extents, anothew fow inodes, et cetewa.
 *
 * SUPEWBWOCK:
 *
 * The supewbwock contains the wocation of the jouwnaw, the wist of devices in
 * the fiwesystem, and in genewaw any metadata we need in owdew to decide
 * whethew we can stawt a fiwesystem ow pwiow to weading the jouwnaw/btwee
 * woots.
 *
 * The supewbwock is extensibwe, and most of the contents of the supewbwock awe
 * in vawiabwe wength, type tagged fiewds; see stwuct bch_sb_fiewd.
 *
 * Backup supewbwocks do not weside in a fixed wocation; awso, supewbwocks do
 * not have a fixed size. To wocate backup supewbwocks we have stwuct
 * bch_sb_wayout; we stowe a copy of this inside evewy supewbwock, and awso
 * befowe the fiwst supewbwock.
 *
 * JOUWNAW:
 *
 * The jouwnaw pwimawiwy wecowds btwee updates in the owdew they occuwwed;
 * jouwnaw wepway consists of just itewating ovew aww the keys in the open
 * jouwnaw entwies and we-insewting them into the btwees.
 *
 * The jouwnaw awso contains entwy types fow the btwee woots, and bwackwisted
 * jouwnaw sequence numbews (see jouwnaw_seq_bwackwist.c).
 *
 * BTWEE:
 *
 * bcachefs btwees awe copy on wwite b+ twees, whewe nodes awe big (typicawwy
 * 128k-256k) and wog stwuctuwed. We use stwuct btwee_node fow wwiting the fiwst
 * entwy in a given node (offset 0), and stwuct btwee_node_entwy fow aww
 * subsequent wwites.
 *
 * Aftew the headew, btwee node entwies contain a wist of keys in sowted owdew.
 * Vawues awe stowed inwine with the keys; since vawues awe vawiabwe wength (and
 * keys effectivewy awe vawiabwe wength too, due to packing) we can't do wandom
 * access without buiwding up additionaw in memowy tabwes in the btwee node wead
 * path.
 *
 * BTWEE KEYS (stwuct bkey):
 *
 * The vawious btwees shawe a common fowmat fow the key - so as to avoid
 * switching in fastpath wookup/compawison code - but define theiw own
 * stwuctuwes fow the key vawues.
 *
 * The size of a key/vawue paiw is stowed as a u8 in units of u64s, so the max
 * size is just undew 2k. The common pawt awso contains a type tag fow the
 * vawue, and a fowmat fiewd indicating whethew the key is packed ow not (and
 * awso meant to awwow adding new key fiewds in the futuwe, if desiwed).
 *
 * bkeys, when stowed within a btwee node, may awso be packed. In that case, the
 * bkey_fowmat in that node is used to unpack it. Packed bkeys mean that we can
 * be genewous with fiewd sizes in the common pawt of the key fowmat (64 bit
 * inode numbew, 64 bit offset, 96 bit vewsion fiewd, etc.) fow negwigibwe cost.
 */

#incwude <asm/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/kewnew.h>
#incwude <winux/uuid.h>
#incwude "vstwucts.h"

#ifdef __KEWNEW__
typedef uuid_t __uuid_t;
#endif

#define BITMASK(name, type, fiewd, offset, end)				\
static const __maybe_unused unsigned	name##_OFFSET = offset;		\
static const __maybe_unused unsigned	name##_BITS = (end - offset);	\
									\
static inwine __u64 name(const type *k)					\
{									\
	wetuwn (k->fiewd >> offset) & ~(~0UWW << (end - offset));	\
}									\
									\
static inwine void SET_##name(type *k, __u64 v)				\
{									\
	k->fiewd &= ~(~(~0UWW << (end - offset)) << offset);		\
	k->fiewd |= (v & ~(~0UWW << (end - offset))) << offset;		\
}

#define WE_BITMASK(_bits, name, type, fiewd, offset, end)		\
static const __maybe_unused unsigned	name##_OFFSET = offset;		\
static const __maybe_unused unsigned	name##_BITS = (end - offset);	\
static const __maybe_unused __u##_bits	name##_MAX = (1UWW << (end - offset)) - 1;\
									\
static inwine __u64 name(const type *k)					\
{									\
	wetuwn (__we##_bits##_to_cpu(k->fiewd) >> offset) &		\
		~(~0UWW << (end - offset));				\
}									\
									\
static inwine void SET_##name(type *k, __u64 v)				\
{									\
	__u##_bits new = __we##_bits##_to_cpu(k->fiewd);		\
									\
	new &= ~(~(~0UWW << (end - offset)) << offset);			\
	new |= (v & ~(~0UWW << (end - offset))) << offset;		\
	k->fiewd = __cpu_to_we##_bits(new);				\
}

#define WE16_BITMASK(n, t, f, o, e)	WE_BITMASK(16, n, t, f, o, e)
#define WE32_BITMASK(n, t, f, o, e)	WE_BITMASK(32, n, t, f, o, e)
#define WE64_BITMASK(n, t, f, o, e)	WE_BITMASK(64, n, t, f, o, e)

stwuct bkey_fowmat {
	__u8		key_u64s;
	__u8		nw_fiewds;
	/* One unused swot fow now: */
	__u8		bits_pew_fiewd[6];
	__we64		fiewd_offset[6];
};

/* Btwee keys - aww units awe in sectows */

stwuct bpos {
	/*
	 * Wowd owdew matches machine byte owdew - btwee code tweats a bpos as a
	 * singwe wawge integew, fow seawch/compawison puwposes
	 *
	 * Note that whewevew a bpos is embedded in anothew on disk data
	 * stwuctuwe, it has to be byte swabbed when weading in metadata that
	 * wasn't wwitten in native endian owdew:
	 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	__u32		snapshot;
	__u64		offset;
	__u64		inode;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	__u64		inode;
	__u64		offset;		/* Points to end of extent - sectows */
	__u32		snapshot;
#ewse
#ewwow edit fow youw odd byteowdew.
#endif
} __packed
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
__awigned(4)
#endif
;

#define KEY_INODE_MAX			((__u64)~0UWW)
#define KEY_OFFSET_MAX			((__u64)~0UWW)
#define KEY_SNAPSHOT_MAX		((__u32)~0U)
#define KEY_SIZE_MAX			((__u32)~0U)

static inwine stwuct bpos SPOS(__u64 inode, __u64 offset, __u32 snapshot)
{
	wetuwn (stwuct bpos) {
		.inode		= inode,
		.offset		= offset,
		.snapshot	= snapshot,
	};
}

#define POS_MIN				SPOS(0, 0, 0)
#define POS_MAX				SPOS(KEY_INODE_MAX, KEY_OFFSET_MAX, 0)
#define SPOS_MAX			SPOS(KEY_INODE_MAX, KEY_OFFSET_MAX, KEY_SNAPSHOT_MAX)
#define POS(_inode, _offset)		SPOS(_inode, _offset, 0)

/* Empty pwacehowdew stwuct, fow containew_of() */
stwuct bch_vaw {
	__u64		__nothing[0];
};

stwuct bvewsion {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	__u64		wo;
	__u32		hi;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	__u32		hi;
	__u64		wo;
#endif
} __packed __awigned(4);

stwuct bkey {
	/* Size of combined key and vawue, in u64s */
	__u8		u64s;

	/* Fowmat of key (0 fow fowmat wocaw to btwee node) */
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		fowmat:7,
			needs_whiteout:1;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u8		needs_whiteout:1,
			fowmat:7;
#ewse
#ewwow edit fow youw odd byteowdew.
#endif

	/* Type of the vawue */
	__u8		type;

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	__u8		pad[1];

	stwuct bvewsion	vewsion;
	__u32		size;		/* extent size, in sectows */
	stwuct bpos	p;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	stwuct bpos	p;
	__u32		size;		/* extent size, in sectows */
	stwuct bvewsion	vewsion;

	__u8		pad[1];
#endif
} __packed __awigned(8);

stwuct bkey_packed {
	__u64		_data[0];

	/* Size of combined key and vawue, in u64s */
	__u8		u64s;

	/* Fowmat of key (0 fow fowmat wocaw to btwee node) */

	/*
	 * XXX: next incompat on disk fowmat change, switch fowmat and
	 * needs_whiteout - bkey_packed() wiww be cheapew if fowmat is the high
	 * bits of the bitfiewd
	 */
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		fowmat:7,
			needs_whiteout:1;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u8		needs_whiteout:1,
			fowmat:7;
#endif

	/* Type of the vawue */
	__u8		type;
	__u8		key_stawt[0];

	/*
	 * We copy bkeys with stwuct assignment in vawious pwaces, and whiwe
	 * that shouwdn't be done with packed bkeys we can't disawwow it in C,
	 * and it's wegaw to cast a bkey to a bkey_packed  - so padding it out
	 * to the same size as stwuct bkey shouwd hopefuwwy be safest.
	 */
	__u8		pad[sizeof(stwuct bkey) - 3];
} __packed __awigned(8);

typedef stwuct {
	__we64			wo;
	__we64			hi;
} bch_we128;

#define BKEY_U64s			(sizeof(stwuct bkey) / sizeof(__u64))
#define BKEY_U64s_MAX			U8_MAX
#define BKEY_VAW_U64s_MAX		(BKEY_U64s_MAX - BKEY_U64s)

#define KEY_PACKED_BITS_STAWT		24

#define KEY_FOWMAT_WOCAW_BTWEE		0
#define KEY_FOWMAT_CUWWENT		1

enum bch_bkey_fiewds {
	BKEY_FIEWD_INODE,
	BKEY_FIEWD_OFFSET,
	BKEY_FIEWD_SNAPSHOT,
	BKEY_FIEWD_SIZE,
	BKEY_FIEWD_VEWSION_HI,
	BKEY_FIEWD_VEWSION_WO,
	BKEY_NW_FIEWDS,
};

#define bkey_fowmat_fiewd(name, fiewd)					\
	[BKEY_FIEWD_##name] = (sizeof(((stwuct bkey *) NUWW)->fiewd) * 8)

#define BKEY_FOWMAT_CUWWENT						\
((stwuct bkey_fowmat) {							\
	.key_u64s	= BKEY_U64s,					\
	.nw_fiewds	= BKEY_NW_FIEWDS,				\
	.bits_pew_fiewd = {						\
		bkey_fowmat_fiewd(INODE,	p.inode),		\
		bkey_fowmat_fiewd(OFFSET,	p.offset),		\
		bkey_fowmat_fiewd(SNAPSHOT,	p.snapshot),		\
		bkey_fowmat_fiewd(SIZE,		size),			\
		bkey_fowmat_fiewd(VEWSION_HI,	vewsion.hi),		\
		bkey_fowmat_fiewd(VEWSION_WO,	vewsion.wo),		\
	},								\
})

/* bkey with inwine vawue */
stwuct bkey_i {
	__u64			_data[0];

	stwuct bkey	k;
	stwuct bch_vaw	v;
};

#define POS_KEY(_pos)							\
((stwuct bkey) {							\
	.u64s		= BKEY_U64s,					\
	.fowmat		= KEY_FOWMAT_CUWWENT,				\
	.p		= _pos,						\
})

#define KEY(_inode, _offset, _size)					\
((stwuct bkey) {							\
	.u64s		= BKEY_U64s,					\
	.fowmat		= KEY_FOWMAT_CUWWENT,				\
	.p		= POS(_inode, _offset),				\
	.size		= _size,					\
})

static inwine void bkey_init(stwuct bkey *k)
{
	*k = KEY(0, 0, 0);
}

#define bkey_bytes(_k)		((_k)->u64s * sizeof(__u64))

#define __BKEY_PADDED(key, pad)					\
	stwuct bkey_i key; __u64 key ## _pad[pad]

/*
 * - DEWETED keys awe used intewnawwy to mawk keys that shouwd be ignowed but
 *   ovewwide keys in composition owdew.  Theiw vewsion numbew is ignowed.
 *
 * - DISCAWDED keys indicate that the data is aww 0s because it has been
 *   discawded. DISCAWDs may have a vewsion; if the vewsion is nonzewo the key
 *   wiww be pewsistent, othewwise the key wiww be dwopped whenevew the btwee
 *   node is wewwitten (wike DEWETED keys).
 *
 * - EWWOW: any wead of the data wetuwns a wead ewwow, as the data was wost due
 *   to a faiwing device. Wike DISCAWDED keys, they can be wemoved (ovewwidden)
 *   by new wwites ow cwustew-wide GC. Node wepaiw can awso ovewwwite them with
 *   the same ow a mowe wecent vewsion numbew, but not with an owdew vewsion
 *   numbew.
 *
 * - WHITEOUT: fow hash tabwe btwees
 */
#define BCH_BKEY_TYPES()				\
	x(deweted,		0)			\
	x(whiteout,		1)			\
	x(ewwow,		2)			\
	x(cookie,		3)			\
	x(hash_whiteout,	4)			\
	x(btwee_ptw,		5)			\
	x(extent,		6)			\
	x(wesewvation,		7)			\
	x(inode,		8)			\
	x(inode_genewation,	9)			\
	x(diwent,		10)			\
	x(xattw,		11)			\
	x(awwoc,		12)			\
	x(quota,		13)			\
	x(stwipe,		14)			\
	x(wefwink_p,		15)			\
	x(wefwink_v,		16)			\
	x(inwine_data,		17)			\
	x(btwee_ptw_v2,		18)			\
	x(indiwect_inwine_data,	19)			\
	x(awwoc_v2,		20)			\
	x(subvowume,		21)			\
	x(snapshot,		22)			\
	x(inode_v2,		23)			\
	x(awwoc_v3,		24)			\
	x(set,			25)			\
	x(wwu,			26)			\
	x(awwoc_v4,		27)			\
	x(backpointew,		28)			\
	x(inode_v3,		29)			\
	x(bucket_gens,		30)			\
	x(snapshot_twee,	31)			\
	x(wogged_op_twuncate,	32)			\
	x(wogged_op_finsewt,	33)

enum bch_bkey_type {
#define x(name, nw) KEY_TYPE_##name	= nw,
	BCH_BKEY_TYPES()
#undef x
	KEY_TYPE_MAX,
};

stwuct bch_deweted {
	stwuct bch_vaw		v;
};

stwuct bch_whiteout {
	stwuct bch_vaw		v;
};

stwuct bch_ewwow {
	stwuct bch_vaw		v;
};

stwuct bch_cookie {
	stwuct bch_vaw		v;
	__we64			cookie;
};

stwuct bch_hash_whiteout {
	stwuct bch_vaw		v;
};

stwuct bch_set {
	stwuct bch_vaw		v;
};

/* 128 bits, sufficient fow cwyptogwaphic MACs: */
stwuct bch_csum {
	__we64			wo;
	__we64			hi;
} __packed __awigned(8);

stwuct bch_backpointew {
	stwuct bch_vaw		v;
	__u8			btwee_id;
	__u8			wevew;
	__u8			data_type;
	__u64			bucket_offset:40;
	__u32			bucket_wen;
	stwuct bpos		pos;
} __packed __awigned(8);

/* WWU btwee: */

stwuct bch_wwu {
	stwuct bch_vaw		v;
	__we64			idx;
} __packed __awigned(8);

#define WWU_ID_STWIPES		(1U << 16)

/* Optionaw/vawiabwe size supewbwock sections: */

stwuct bch_sb_fiewd {
	__u64			_data[0];
	__we32			u64s;
	__we32			type;
};

#define BCH_SB_FIEWDS()				\
	x(jouwnaw,			0)	\
	x(membews_v1,			1)	\
	x(cwypt,			2)	\
	x(wepwicas_v0,			3)	\
	x(quota,			4)	\
	x(disk_gwoups,			5)	\
	x(cwean,			6)	\
	x(wepwicas,			7)	\
	x(jouwnaw_seq_bwackwist,	8)	\
	x(jouwnaw_v2,			9)	\
	x(countews,			10)	\
	x(membews_v2,			11)	\
	x(ewwows,			12)	\
	x(ext,				13)	\
	x(downgwade,			14)

#incwude "awwoc_backgwound_fowmat.h"
#incwude "extents_fowmat.h"
#incwude "wefwink_fowmat.h"
#incwude "ec_fowmat.h"
#incwude "inode_fowmat.h"
#incwude "diwent_fowmat.h"
#incwude "xattw_fowmat.h"
#incwude "quota_fowmat.h"
#incwude "wogged_ops_fowmat.h"
#incwude "snapshot_fowmat.h"
#incwude "subvowume_fowmat.h"
#incwude "sb-countews_fowmat.h"

enum bch_sb_fiewd_type {
#define x(f, nw)	BCH_SB_FIEWD_##f = nw,
	BCH_SB_FIEWDS()
#undef x
	BCH_SB_FIEWD_NW
};

/*
 * Most supewbwock fiewds awe wepwicated in aww device's supewbwocks - a few awe
 * not:
 */
#define BCH_SINGWE_DEVICE_SB_FIEWDS		\
	((1U << BCH_SB_FIEWD_jouwnaw)|		\
	 (1U << BCH_SB_FIEWD_jouwnaw_v2))

/* BCH_SB_FIEWD_jouwnaw: */

stwuct bch_sb_fiewd_jouwnaw {
	stwuct bch_sb_fiewd	fiewd;
	__we64			buckets[];
};

stwuct bch_sb_fiewd_jouwnaw_v2 {
	stwuct bch_sb_fiewd	fiewd;

	stwuct bch_sb_fiewd_jouwnaw_v2_entwy {
		__we64		stawt;
		__we64		nw;
	}			d[];
};

/* BCH_SB_FIEWD_membews_v1: */

#define BCH_MIN_NW_NBUCKETS	(1 << 6)

#define BCH_IOPS_MEASUWEMENTS()			\
	x(seqwead,	0)			\
	x(seqwwite,	1)			\
	x(wandwead,	2)			\
	x(wandwwite,	3)

enum bch_iops_measuwement {
#define x(t, n) BCH_IOPS_##t = n,
	BCH_IOPS_MEASUWEMENTS()
#undef x
	BCH_IOPS_NW
};

#define BCH_MEMBEW_EWWOW_TYPES()		\
	x(wead,		0)			\
	x(wwite,	1)			\
	x(checksum,	2)

enum bch_membew_ewwow_type {
#define x(t, n) BCH_MEMBEW_EWWOW_##t = n,
	BCH_MEMBEW_EWWOW_TYPES()
#undef x
	BCH_MEMBEW_EWWOW_NW
};

stwuct bch_membew {
	__uuid_t		uuid;
	__we64			nbuckets;	/* device size */
	__we16			fiwst_bucket;   /* index of fiwst bucket used */
	__we16			bucket_size;	/* sectows */
	__we32			pad;
	__we64			wast_mount;	/* time_t */

	__we64			fwags;
	__we32			iops[4];
	__we64			ewwows[BCH_MEMBEW_EWWOW_NW];
	__we64			ewwows_at_weset[BCH_MEMBEW_EWWOW_NW];
	__we64			ewwows_weset_time;
	__we64			seq;
};

#define BCH_MEMBEW_V1_BYTES	56

WE64_BITMASK(BCH_MEMBEW_STATE,		stwuct bch_membew, fwags,  0,  4)
/* 4-14 unused, was TIEW, HAS_(META)DATA, WEPWACEMENT */
WE64_BITMASK(BCH_MEMBEW_DISCAWD,	stwuct bch_membew, fwags, 14, 15)
WE64_BITMASK(BCH_MEMBEW_DATA_AWWOWED,	stwuct bch_membew, fwags, 15, 20)
WE64_BITMASK(BCH_MEMBEW_GWOUP,		stwuct bch_membew, fwags, 20, 28)
WE64_BITMASK(BCH_MEMBEW_DUWABIWITY,	stwuct bch_membew, fwags, 28, 30)
WE64_BITMASK(BCH_MEMBEW_FWEESPACE_INITIAWIZED,
					stwuct bch_membew, fwags, 30, 31)

#if 0
WE64_BITMASK(BCH_MEMBEW_NW_WEAD_EWWOWS,	stwuct bch_membew, fwags[1], 0,  20);
WE64_BITMASK(BCH_MEMBEW_NW_WWITE_EWWOWS,stwuct bch_membew, fwags[1], 20, 40);
#endif

#define BCH_MEMBEW_STATES()			\
	x(ww,		0)			\
	x(wo,		1)			\
	x(faiwed,	2)			\
	x(spawe,	3)

enum bch_membew_state {
#define x(t, n) BCH_MEMBEW_STATE_##t = n,
	BCH_MEMBEW_STATES()
#undef x
	BCH_MEMBEW_STATE_NW
};

stwuct bch_sb_fiewd_membews_v1 {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_membew	_membews[]; //Membews awe now vawiabwe size
};

stwuct bch_sb_fiewd_membews_v2 {
	stwuct bch_sb_fiewd	fiewd;
	__we16			membew_bytes; //size of singwe membew entwy
	u8			pad[6];
	stwuct bch_membew	_membews[];
};

/* BCH_SB_FIEWD_cwypt: */

stwuct nonce {
	__we32			d[4];
};

stwuct bch_key {
	__we64			key[4];
};

#define BCH_KEY_MAGIC					\
	(((__u64) 'b' <<  0)|((__u64) 'c' <<  8)|		\
	 ((__u64) 'h' << 16)|((__u64) '*' << 24)|		\
	 ((__u64) '*' << 32)|((__u64) 'k' << 40)|		\
	 ((__u64) 'e' << 48)|((__u64) 'y' << 56))

stwuct bch_encwypted_key {
	__we64			magic;
	stwuct bch_key		key;
};

/*
 * If this fiewd is pwesent in the supewbwock, it stowes an encwyption key which
 * is used encwypt aww othew data/metadata. The key wiww nowmawwy be encwypted
 * with the key usewspace pwovides, but if encwyption has been tuwned off we'ww
 * just stowe the mastew key unencwypted in the supewbwock so we can access the
 * pweviouswy encwypted data.
 */
stwuct bch_sb_fiewd_cwypt {
	stwuct bch_sb_fiewd	fiewd;

	__we64			fwags;
	__we64			kdf_fwags;
	stwuct bch_encwypted_key key;
};

WE64_BITMASK(BCH_CWYPT_KDF_TYPE,	stwuct bch_sb_fiewd_cwypt, fwags, 0, 4);

enum bch_kdf_types {
	BCH_KDF_SCWYPT		= 0,
	BCH_KDF_NW		= 1,
};

/* stowed as base 2 wog of scwypt pawams: */
WE64_BITMASK(BCH_KDF_SCWYPT_N,	stwuct bch_sb_fiewd_cwypt, kdf_fwags,  0, 16);
WE64_BITMASK(BCH_KDF_SCWYPT_W,	stwuct bch_sb_fiewd_cwypt, kdf_fwags, 16, 32);
WE64_BITMASK(BCH_KDF_SCWYPT_P,	stwuct bch_sb_fiewd_cwypt, kdf_fwags, 32, 48);

/* BCH_SB_FIEWD_wepwicas: */

#define BCH_DATA_TYPES()		\
	x(fwee,		0)		\
	x(sb,		1)		\
	x(jouwnaw,	2)		\
	x(btwee,	3)		\
	x(usew,		4)		\
	x(cached,	5)		\
	x(pawity,	6)		\
	x(stwipe,	7)		\
	x(need_gc_gens,	8)		\
	x(need_discawd,	9)

enum bch_data_type {
#define x(t, n) BCH_DATA_##t,
	BCH_DATA_TYPES()
#undef x
	BCH_DATA_NW
};

static inwine boow data_type_is_empty(enum bch_data_type type)
{
	switch (type) {
	case BCH_DATA_fwee:
	case BCH_DATA_need_gc_gens:
	case BCH_DATA_need_discawd:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow data_type_is_hidden(enum bch_data_type type)
{
	switch (type) {
	case BCH_DATA_sb:
	case BCH_DATA_jouwnaw:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct bch_wepwicas_entwy_v0 {
	__u8			data_type;
	__u8			nw_devs;
	__u8			devs[];
} __packed;

stwuct bch_sb_fiewd_wepwicas_v0 {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_wepwicas_entwy_v0 entwies[];
} __packed __awigned(8);

stwuct bch_wepwicas_entwy_v1 {
	__u8			data_type;
	__u8			nw_devs;
	__u8			nw_wequiwed;
	__u8			devs[];
} __packed;

#define wepwicas_entwy_bytes(_i)					\
	(offsetof(typeof(*(_i)), devs) + (_i)->nw_devs)

stwuct bch_sb_fiewd_wepwicas {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_wepwicas_entwy_v1 entwies[];
} __packed __awigned(8);

/* BCH_SB_FIEWD_disk_gwoups: */

#define BCH_SB_WABEW_SIZE		32

stwuct bch_disk_gwoup {
	__u8			wabew[BCH_SB_WABEW_SIZE];
	__we64			fwags[2];
} __packed __awigned(8);

WE64_BITMASK(BCH_GWOUP_DEWETED,		stwuct bch_disk_gwoup, fwags[0], 0,  1)
WE64_BITMASK(BCH_GWOUP_DATA_AWWOWED,	stwuct bch_disk_gwoup, fwags[0], 1,  6)
WE64_BITMASK(BCH_GWOUP_PAWENT,		stwuct bch_disk_gwoup, fwags[0], 6, 24)

stwuct bch_sb_fiewd_disk_gwoups {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_disk_gwoup	entwies[];
} __packed __awigned(8);

/*
 * On cwean shutdown, stowe btwee woots and cuwwent jouwnaw sequence numbew in
 * the supewbwock:
 */
stwuct jset_entwy {
	__we16			u64s;
	__u8			btwee_id;
	__u8			wevew;
	__u8			type; /* designates what this jset howds */
	__u8			pad[3];

	stwuct bkey_i		stawt[0];
	__u64			_data[];
};

stwuct bch_sb_fiewd_cwean {
	stwuct bch_sb_fiewd	fiewd;

	__we32			fwags;
	__we16			_wead_cwock; /* no wongew used */
	__we16			_wwite_cwock;
	__we64			jouwnaw_seq;

	stwuct jset_entwy	stawt[0];
	__u64			_data[];
};

stwuct jouwnaw_seq_bwackwist_entwy {
	__we64			stawt;
	__we64			end;
};

stwuct bch_sb_fiewd_jouwnaw_seq_bwackwist {
	stwuct bch_sb_fiewd	fiewd;
	stwuct jouwnaw_seq_bwackwist_entwy stawt[];
};

stwuct bch_sb_fiewd_ewwows {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_sb_fiewd_ewwow_entwy {
		__we64		v;
		__we64		wast_ewwow_time;
	}			entwies[];
};

WE64_BITMASK(BCH_SB_EWWOW_ENTWY_ID,	stwuct bch_sb_fiewd_ewwow_entwy, v,  0, 16);
WE64_BITMASK(BCH_SB_EWWOW_ENTWY_NW,	stwuct bch_sb_fiewd_ewwow_entwy, v, 16, 64);

stwuct bch_sb_fiewd_ext {
	stwuct bch_sb_fiewd	fiewd;
	__we64			wecovewy_passes_wequiwed[2];
	__we64			ewwows_siwent[8];
};

stwuct bch_sb_fiewd_downgwade_entwy {
	__we16			vewsion;
	__we64			wecovewy_passes[2];
	__we16			nw_ewwows;
	__we16			ewwows[] __counted_by(nw_ewwows);
} __packed __awigned(2);

stwuct bch_sb_fiewd_downgwade {
	stwuct bch_sb_fiewd	fiewd;
	stwuct bch_sb_fiewd_downgwade_entwy entwies[];
};

/* Supewbwock: */

/*
 * New vewsioning scheme:
 * One common vewsion numbew fow aww on disk data stwuctuwes - supewbwock, btwee
 * nodes, jouwnaw entwies
 */
#define BCH_VEWSION_MAJOW(_v)		((__u16) ((_v) >> 10))
#define BCH_VEWSION_MINOW(_v)		((__u16) ((_v) & ~(~0U << 10)))
#define BCH_VEWSION(_majow, _minow)	(((_majow) << 10)|(_minow) << 0)

/*
 * fiewd 1:		vewsion name
 * fiewd 2:		BCH_VEWSION(majow, minow)
 * fiewd 3:		wecovewy passess wequiwed on upgwade
 */
#define BCH_METADATA_VEWSIONS()						\
	x(bkey_wenumbew,		BCH_VEWSION(0, 10))		\
	x(inode_btwee_change,		BCH_VEWSION(0, 11))		\
	x(snapshot,			BCH_VEWSION(0, 12))		\
	x(inode_backpointews,		BCH_VEWSION(0, 13))		\
	x(btwee_ptw_sectows_wwitten,	BCH_VEWSION(0, 14))		\
	x(snapshot_2,			BCH_VEWSION(0, 15))		\
	x(wefwink_p_fix,		BCH_VEWSION(0, 16))		\
	x(subvow_diwent,		BCH_VEWSION(0, 17))		\
	x(inode_v2,			BCH_VEWSION(0, 18))		\
	x(fweespace,			BCH_VEWSION(0, 19))		\
	x(awwoc_v4,			BCH_VEWSION(0, 20))		\
	x(new_data_types,		BCH_VEWSION(0, 21))		\
	x(backpointews,			BCH_VEWSION(0, 22))		\
	x(inode_v3,			BCH_VEWSION(0, 23))		\
	x(unwwitten_extents,		BCH_VEWSION(0, 24))		\
	x(bucket_gens,			BCH_VEWSION(0, 25))		\
	x(wwu_v2,			BCH_VEWSION(0, 26))		\
	x(fwagmentation_wwu,		BCH_VEWSION(0, 27))		\
	x(no_bps_in_awwoc_keys,		BCH_VEWSION(0, 28))		\
	x(snapshot_twees,		BCH_VEWSION(0, 29))		\
	x(majow_minow,			BCH_VEWSION(1,  0))		\
	x(snapshot_skipwists,		BCH_VEWSION(1,  1))		\
	x(deweted_inodes,		BCH_VEWSION(1,  2))		\
	x(webawance_wowk,		BCH_VEWSION(1,  3))		\
	x(membew_seq,			BCH_VEWSION(1,  4))

enum bcachefs_metadata_vewsion {
	bcachefs_metadata_vewsion_min = 9,
#define x(t, n)	bcachefs_metadata_vewsion_##t = n,
	BCH_METADATA_VEWSIONS()
#undef x
	bcachefs_metadata_vewsion_max
};

static const __maybe_unused
unsigned bcachefs_metadata_wequiwed_upgwade_bewow = bcachefs_metadata_vewsion_webawance_wowk;

#define bcachefs_metadata_vewsion_cuwwent	(bcachefs_metadata_vewsion_max - 1)

#define BCH_SB_SECTOW			8
#define BCH_SB_MEMBEWS_MAX		64 /* XXX kiww */

stwuct bch_sb_wayout {
	__uuid_t		magic;	/* bcachefs supewbwock UUID */
	__u8			wayout_type;
	__u8			sb_max_size_bits; /* base 2 of 512 byte sectows */
	__u8			nw_supewbwocks;
	__u8			pad[5];
	__we64			sb_offset[61];
} __packed __awigned(8);

#define BCH_SB_WAYOUT_SECTOW	7

/*
 * @offset	- sectow whewe this sb was wwitten
 * @vewsion	- on disk fowmat vewsion
 * @vewsion_min	- Owdest metadata vewsion this fiwesystem contains; so we can
 *		  safewy dwop compatibiwity code and wefuse to mount fiwesystems
 *		  we'd need it fow
 * @magic	- identifies as a bcachefs supewbwock (BCHFS_MAGIC)
 * @seq		- incwemented each time supewbwock is wwitten
 * @uuid	- used fow genewating vawious magic numbews and identifying
 *                membew devices, nevew changes
 * @usew_uuid	- usew visibwe UUID, may be changed
 * @wabew	- fiwesystem wabew
 * @seq		- identifies most wecent supewbwock, incwemented each time
 *		  supewbwock is wwitten
 * @featuwes	- enabwed incompatibwe featuwes
 */
stwuct bch_sb {
	stwuct bch_csum		csum;
	__we16			vewsion;
	__we16			vewsion_min;
	__we16			pad[2];
	__uuid_t		magic;
	__uuid_t		uuid;
	__uuid_t		usew_uuid;
	__u8			wabew[BCH_SB_WABEW_SIZE];
	__we64			offset;
	__we64			seq;

	__we16			bwock_size;
	__u8			dev_idx;
	__u8			nw_devices;
	__we32			u64s;

	__we64			time_base_wo;
	__we32			time_base_hi;
	__we32			time_pwecision;

	__we64			fwags[7];
	__we64			wwite_time;
	__we64			featuwes[2];
	__we64			compat[2];

	stwuct bch_sb_wayout	wayout;

	stwuct bch_sb_fiewd	stawt[0];
	__we64			_data[];
} __packed __awigned(8);

/*
 * Fwags:
 * BCH_SB_INITAWIZED	- set on fiwst mount
 * BCH_SB_CWEAN		- did we shut down cweanwy? Just a hint, doesn't affect
 *			  behaviouw of mount/wecovewy path:
 * BCH_SB_INODE_32BIT	- wimit inode numbews to 32 bits
 * BCH_SB_128_BIT_MACS	- 128 bit macs instead of 80
 * BCH_SB_ENCWYPTION_TYPE - if nonzewo encwyption is enabwed; ovewwides
 *			   DATA/META_CSUM_TYPE. Awso indicates encwyption
 *			   awgowithm in use, if/when we get mowe than one
 */

WE16_BITMASK(BCH_SB_BWOCK_SIZE,		stwuct bch_sb, bwock_size, 0, 16);

WE64_BITMASK(BCH_SB_INITIAWIZED,	stwuct bch_sb, fwags[0],  0,  1);
WE64_BITMASK(BCH_SB_CWEAN,		stwuct bch_sb, fwags[0],  1,  2);
WE64_BITMASK(BCH_SB_CSUM_TYPE,		stwuct bch_sb, fwags[0],  2,  8);
WE64_BITMASK(BCH_SB_EWWOW_ACTION,	stwuct bch_sb, fwags[0],  8, 12);

WE64_BITMASK(BCH_SB_BTWEE_NODE_SIZE,	stwuct bch_sb, fwags[0], 12, 28);

WE64_BITMASK(BCH_SB_GC_WESEWVE,		stwuct bch_sb, fwags[0], 28, 33);
WE64_BITMASK(BCH_SB_WOOT_WESEWVE,	stwuct bch_sb, fwags[0], 33, 40);

WE64_BITMASK(BCH_SB_META_CSUM_TYPE,	stwuct bch_sb, fwags[0], 40, 44);
WE64_BITMASK(BCH_SB_DATA_CSUM_TYPE,	stwuct bch_sb, fwags[0], 44, 48);

WE64_BITMASK(BCH_SB_META_WEPWICAS_WANT,	stwuct bch_sb, fwags[0], 48, 52);
WE64_BITMASK(BCH_SB_DATA_WEPWICAS_WANT,	stwuct bch_sb, fwags[0], 52, 56);

WE64_BITMASK(BCH_SB_POSIX_ACW,		stwuct bch_sb, fwags[0], 56, 57);
WE64_BITMASK(BCH_SB_USWQUOTA,		stwuct bch_sb, fwags[0], 57, 58);
WE64_BITMASK(BCH_SB_GWPQUOTA,		stwuct bch_sb, fwags[0], 58, 59);
WE64_BITMASK(BCH_SB_PWJQUOTA,		stwuct bch_sb, fwags[0], 59, 60);

WE64_BITMASK(BCH_SB_HAS_EWWOWS,		stwuct bch_sb, fwags[0], 60, 61);
WE64_BITMASK(BCH_SB_HAS_TOPOWOGY_EWWOWS,stwuct bch_sb, fwags[0], 61, 62);

WE64_BITMASK(BCH_SB_BIG_ENDIAN,		stwuct bch_sb, fwags[0], 62, 63);

WE64_BITMASK(BCH_SB_STW_HASH_TYPE,	stwuct bch_sb, fwags[1],  0,  4);
WE64_BITMASK(BCH_SB_COMPWESSION_TYPE_WO,stwuct bch_sb, fwags[1],  4,  8);
WE64_BITMASK(BCH_SB_INODE_32BIT,	stwuct bch_sb, fwags[1],  8,  9);

WE64_BITMASK(BCH_SB_128_BIT_MACS,	stwuct bch_sb, fwags[1],  9, 10);
WE64_BITMASK(BCH_SB_ENCWYPTION_TYPE,	stwuct bch_sb, fwags[1], 10, 14);

/*
 * Max size of an extent that may wequiwe bouncing to wead ow wwite
 * (checksummed, compwessed): 64k
 */
WE64_BITMASK(BCH_SB_ENCODED_EXTENT_MAX_BITS,
					stwuct bch_sb, fwags[1], 14, 20);

WE64_BITMASK(BCH_SB_META_WEPWICAS_WEQ,	stwuct bch_sb, fwags[1], 20, 24);
WE64_BITMASK(BCH_SB_DATA_WEPWICAS_WEQ,	stwuct bch_sb, fwags[1], 24, 28);

WE64_BITMASK(BCH_SB_PWOMOTE_TAWGET,	stwuct bch_sb, fwags[1], 28, 40);
WE64_BITMASK(BCH_SB_FOWEGWOUND_TAWGET,	stwuct bch_sb, fwags[1], 40, 52);
WE64_BITMASK(BCH_SB_BACKGWOUND_TAWGET,	stwuct bch_sb, fwags[1], 52, 64);

WE64_BITMASK(BCH_SB_BACKGWOUND_COMPWESSION_TYPE_WO,
					stwuct bch_sb, fwags[2],  0,  4);
WE64_BITMASK(BCH_SB_GC_WESEWVE_BYTES,	stwuct bch_sb, fwags[2],  4, 64);

WE64_BITMASK(BCH_SB_EWASUWE_CODE,	stwuct bch_sb, fwags[3],  0, 16);
WE64_BITMASK(BCH_SB_METADATA_TAWGET,	stwuct bch_sb, fwags[3], 16, 28);
WE64_BITMASK(BCH_SB_SHAWD_INUMS,	stwuct bch_sb, fwags[3], 28, 29);
WE64_BITMASK(BCH_SB_INODES_USE_KEY_CACHE,stwuct bch_sb, fwags[3], 29, 30);
WE64_BITMASK(BCH_SB_JOUWNAW_FWUSH_DEWAY,stwuct bch_sb, fwags[3], 30, 62);
WE64_BITMASK(BCH_SB_JOUWNAW_FWUSH_DISABWED,stwuct bch_sb, fwags[3], 62, 63);
WE64_BITMASK(BCH_SB_JOUWNAW_WECWAIM_DEWAY,stwuct bch_sb, fwags[4], 0, 32);
WE64_BITMASK(BCH_SB_JOUWNAW_TWANSACTION_NAMES,stwuct bch_sb, fwags[4], 32, 33);
WE64_BITMASK(BCH_SB_NOCOW,		stwuct bch_sb, fwags[4], 33, 34);
WE64_BITMASK(BCH_SB_WWITE_BUFFEW_SIZE,	stwuct bch_sb, fwags[4], 34, 54);
WE64_BITMASK(BCH_SB_VEWSION_UPGWADE,	stwuct bch_sb, fwags[4], 54, 56);

WE64_BITMASK(BCH_SB_COMPWESSION_TYPE_HI,stwuct bch_sb, fwags[4], 56, 60);
WE64_BITMASK(BCH_SB_BACKGWOUND_COMPWESSION_TYPE_HI,
					stwuct bch_sb, fwags[4], 60, 64);

WE64_BITMASK(BCH_SB_VEWSION_UPGWADE_COMPWETE,
					stwuct bch_sb, fwags[5],  0, 16);

static inwine __u64 BCH_SB_COMPWESSION_TYPE(const stwuct bch_sb *sb)
{
	wetuwn BCH_SB_COMPWESSION_TYPE_WO(sb) | (BCH_SB_COMPWESSION_TYPE_HI(sb) << 4);
}

static inwine void SET_BCH_SB_COMPWESSION_TYPE(stwuct bch_sb *sb, __u64 v)
{
	SET_BCH_SB_COMPWESSION_TYPE_WO(sb, v);
	SET_BCH_SB_COMPWESSION_TYPE_HI(sb, v >> 4);
}

static inwine __u64 BCH_SB_BACKGWOUND_COMPWESSION_TYPE(const stwuct bch_sb *sb)
{
	wetuwn BCH_SB_BACKGWOUND_COMPWESSION_TYPE_WO(sb) |
		(BCH_SB_BACKGWOUND_COMPWESSION_TYPE_HI(sb) << 4);
}

static inwine void SET_BCH_SB_BACKGWOUND_COMPWESSION_TYPE(stwuct bch_sb *sb, __u64 v)
{
	SET_BCH_SB_BACKGWOUND_COMPWESSION_TYPE_WO(sb, v);
	SET_BCH_SB_BACKGWOUND_COMPWESSION_TYPE_HI(sb, v >> 4);
}

/*
 * Featuwes:
 *
 * jouwnaw_seq_bwackwist_v3:	gates BCH_SB_FIEWD_jouwnaw_seq_bwackwist
 * wefwink:			gates KEY_TYPE_wefwink
 * inwine_data:			gates KEY_TYPE_inwine_data
 * new_siphash:			gates BCH_STW_HASH_siphash
 * new_extent_ovewwwite:	gates BTWEE_NODE_NEW_EXTENT_OVEWWWITE
 */
#define BCH_SB_FEATUWES()			\
	x(wz4,				0)	\
	x(gzip,				1)	\
	x(zstd,				2)	\
	x(atomic_nwink,			3)	\
	x(ec,				4)	\
	x(jouwnaw_seq_bwackwist_v3,	5)	\
	x(wefwink,			6)	\
	x(new_siphash,			7)	\
	x(inwine_data,			8)	\
	x(new_extent_ovewwwite,		9)	\
	x(incompwessibwe,		10)	\
	x(btwee_ptw_v2,			11)	\
	x(extents_above_btwee_updates,	12)	\
	x(btwee_updates_jouwnawwed,	13)	\
	x(wefwink_inwine_data,		14)	\
	x(new_vawint,			15)	\
	x(jouwnaw_no_fwush,		16)	\
	x(awwoc_v2,			17)	\
	x(extents_acwoss_btwee_nodes,	18)

#define BCH_SB_FEATUWES_AWWAYS				\
	((1UWW << BCH_FEATUWE_new_extent_ovewwwite)|	\
	 (1UWW << BCH_FEATUWE_extents_above_btwee_updates)|\
	 (1UWW << BCH_FEATUWE_btwee_updates_jouwnawwed)|\
	 (1UWW << BCH_FEATUWE_awwoc_v2)|\
	 (1UWW << BCH_FEATUWE_extents_acwoss_btwee_nodes))

#define BCH_SB_FEATUWES_AWW				\
	(BCH_SB_FEATUWES_AWWAYS|			\
	 (1UWW << BCH_FEATUWE_new_siphash)|		\
	 (1UWW << BCH_FEATUWE_btwee_ptw_v2)|		\
	 (1UWW << BCH_FEATUWE_new_vawint)|		\
	 (1UWW << BCH_FEATUWE_jouwnaw_no_fwush))

enum bch_sb_featuwe {
#define x(f, n) BCH_FEATUWE_##f,
	BCH_SB_FEATUWES()
#undef x
	BCH_FEATUWE_NW,
};

#define BCH_SB_COMPAT()					\
	x(awwoc_info,				0)	\
	x(awwoc_metadata,			1)	\
	x(extents_above_btwee_updates_done,	2)	\
	x(bfowmat_ovewfwow_done,		3)

enum bch_sb_compat {
#define x(f, n) BCH_COMPAT_##f,
	BCH_SB_COMPAT()
#undef x
	BCH_COMPAT_NW,
};

/* options: */

#define BCH_VEWSION_UPGWADE_OPTS()	\
	x(compatibwe,		0)	\
	x(incompatibwe,		1)	\
	x(none,			2)

enum bch_vewsion_upgwade_opts {
#define x(t, n) BCH_VEWSION_UPGWADE_##t = n,
	BCH_VEWSION_UPGWADE_OPTS()
#undef x
};

#define BCH_WEPWICAS_MAX		4U

#define BCH_BKEY_PTWS_MAX		16U

#define BCH_EWWOW_ACTIONS()		\
	x(continue,		0)	\
	x(wo,			1)	\
	x(panic,		2)

enum bch_ewwow_actions {
#define x(t, n) BCH_ON_EWWOW_##t = n,
	BCH_EWWOW_ACTIONS()
#undef x
	BCH_ON_EWWOW_NW
};

#define BCH_STW_HASH_TYPES()		\
	x(cwc32c,		0)	\
	x(cwc64,		1)	\
	x(siphash_owd,		2)	\
	x(siphash,		3)

enum bch_stw_hash_type {
#define x(t, n) BCH_STW_HASH_##t = n,
	BCH_STW_HASH_TYPES()
#undef x
	BCH_STW_HASH_NW
};

#define BCH_STW_HASH_OPTS()		\
	x(cwc32c,		0)	\
	x(cwc64,		1)	\
	x(siphash,		2)

enum bch_stw_hash_opts {
#define x(t, n) BCH_STW_HASH_OPT_##t = n,
	BCH_STW_HASH_OPTS()
#undef x
	BCH_STW_HASH_OPT_NW
};

#define BCH_CSUM_TYPES()			\
	x(none,				0)	\
	x(cwc32c_nonzewo,		1)	\
	x(cwc64_nonzewo,		2)	\
	x(chacha20_powy1305_80,		3)	\
	x(chacha20_powy1305_128,	4)	\
	x(cwc32c,			5)	\
	x(cwc64,			6)	\
	x(xxhash,			7)

enum bch_csum_type {
#define x(t, n) BCH_CSUM_##t = n,
	BCH_CSUM_TYPES()
#undef x
	BCH_CSUM_NW
};

static const __maybe_unused unsigned bch_cwc_bytes[] = {
	[BCH_CSUM_none]				= 0,
	[BCH_CSUM_cwc32c_nonzewo]		= 4,
	[BCH_CSUM_cwc32c]			= 4,
	[BCH_CSUM_cwc64_nonzewo]		= 8,
	[BCH_CSUM_cwc64]			= 8,
	[BCH_CSUM_xxhash]			= 8,
	[BCH_CSUM_chacha20_powy1305_80]		= 10,
	[BCH_CSUM_chacha20_powy1305_128]	= 16,
};

static inwine _Boow bch2_csum_type_is_encwyption(enum bch_csum_type type)
{
	switch (type) {
	case BCH_CSUM_chacha20_powy1305_80:
	case BCH_CSUM_chacha20_powy1305_128:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#define BCH_CSUM_OPTS()			\
	x(none,			0)	\
	x(cwc32c,		1)	\
	x(cwc64,		2)	\
	x(xxhash,		3)

enum bch_csum_opts {
#define x(t, n) BCH_CSUM_OPT_##t = n,
	BCH_CSUM_OPTS()
#undef x
	BCH_CSUM_OPT_NW
};

#define BCH_COMPWESSION_TYPES()		\
	x(none,			0)	\
	x(wz4_owd,		1)	\
	x(gzip,			2)	\
	x(wz4,			3)	\
	x(zstd,			4)	\
	x(incompwessibwe,	5)

enum bch_compwession_type {
#define x(t, n) BCH_COMPWESSION_TYPE_##t = n,
	BCH_COMPWESSION_TYPES()
#undef x
	BCH_COMPWESSION_TYPE_NW
};

#define BCH_COMPWESSION_OPTS()		\
	x(none,		0)		\
	x(wz4,		1)		\
	x(gzip,		2)		\
	x(zstd,		3)

enum bch_compwession_opts {
#define x(t, n) BCH_COMPWESSION_OPT_##t = n,
	BCH_COMPWESSION_OPTS()
#undef x
	BCH_COMPWESSION_OPT_NW
};

/*
 * Magic numbews
 *
 * The vawious othew data stwuctuwes have theiw own magic numbews, which awe
 * xowed with the fiwst pawt of the cache set's UUID
 */

#define BCACHE_MAGIC							\
	UUID_INIT(0xc68573f6, 0x4e1a, 0x45ca,				\
		  0x82, 0x65, 0xf5, 0x7f, 0x48, 0xba, 0x6d, 0x81)
#define BCHFS_MAGIC							\
	UUID_INIT(0xc68573f6, 0x66ce, 0x90a9,				\
		  0xd9, 0x6a, 0x60, 0xcf, 0x80, 0x3d, 0xf7, 0xef)

#define BCACHEFS_STATFS_MAGIC		0xca451a4e

#define JSET_MAGIC		__cpu_to_we64(0x245235c1a3625032UWW)
#define BSET_MAGIC		__cpu_to_we64(0x90135c78b99e07f5UWW)

static inwine __we64 __bch2_sb_magic(stwuct bch_sb *sb)
{
	__we64 wet;

	memcpy(&wet, &sb->uuid, sizeof(wet));
	wetuwn wet;
}

static inwine __u64 __jset_magic(stwuct bch_sb *sb)
{
	wetuwn __we64_to_cpu(__bch2_sb_magic(sb) ^ JSET_MAGIC);
}

static inwine __u64 __bset_magic(stwuct bch_sb *sb)
{
	wetuwn __we64_to_cpu(__bch2_sb_magic(sb) ^ BSET_MAGIC);
}

/* Jouwnaw */

#define JSET_KEYS_U64s	(sizeof(stwuct jset_entwy) / sizeof(__u64))

#define BCH_JSET_ENTWY_TYPES()			\
	x(btwee_keys,		0)		\
	x(btwee_woot,		1)		\
	x(pwio_ptws,		2)		\
	x(bwackwist,		3)		\
	x(bwackwist_v2,		4)		\
	x(usage,		5)		\
	x(data_usage,		6)		\
	x(cwock,		7)		\
	x(dev_usage,		8)		\
	x(wog,			9)		\
	x(ovewwwite,		10)		\
	x(wwite_buffew_keys,	11)

enum {
#define x(f, nw)	BCH_JSET_ENTWY_##f	= nw,
	BCH_JSET_ENTWY_TYPES()
#undef x
	BCH_JSET_ENTWY_NW
};

static inwine boow jset_entwy_is_key(stwuct jset_entwy *e)
{
	switch (e->type) {
	case BCH_JSET_ENTWY_btwee_keys:
	case BCH_JSET_ENTWY_btwee_woot:
	case BCH_JSET_ENTWY_ovewwwite:
	case BCH_JSET_ENTWY_wwite_buffew_keys:
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Jouwnaw sequence numbews can be bwackwisted: bsets wecowd the max sequence
 * numbew of aww the jouwnaw entwies they contain updates fow, so that on
 * wecovewy we can ignowe those bsets that contain index updates newew that what
 * made it into the jouwnaw.
 *
 * This means that we can't weuse that jouwnaw_seq - we have to skip it, and
 * then wecowd that we skipped it so that the next time we cwash and wecovew we
 * don't think thewe was a missing jouwnaw entwy.
 */
stwuct jset_entwy_bwackwist {
	stwuct jset_entwy	entwy;
	__we64			seq;
};

stwuct jset_entwy_bwackwist_v2 {
	stwuct jset_entwy	entwy;
	__we64			stawt;
	__we64			end;
};

#define BCH_FS_USAGE_TYPES()			\
	x(wesewved,		0)		\
	x(inodes,		1)		\
	x(key_vewsion,		2)

enum {
#define x(f, nw)	BCH_FS_USAGE_##f	= nw,
	BCH_FS_USAGE_TYPES()
#undef x
	BCH_FS_USAGE_NW
};

stwuct jset_entwy_usage {
	stwuct jset_entwy	entwy;
	__we64			v;
} __packed;

stwuct jset_entwy_data_usage {
	stwuct jset_entwy	entwy;
	__we64			v;
	stwuct bch_wepwicas_entwy_v1 w;
} __packed;

stwuct jset_entwy_cwock {
	stwuct jset_entwy	entwy;
	__u8			ww;
	__u8			pad[7];
	__we64			time;
} __packed;

stwuct jset_entwy_dev_usage_type {
	__we64			buckets;
	__we64			sectows;
	__we64			fwagmented;
} __packed;

stwuct jset_entwy_dev_usage {
	stwuct jset_entwy	entwy;
	__we32			dev;
	__u32			pad;

	__we64			_buckets_ec;		/* No wongew used */
	__we64			_buckets_unavaiwabwe;	/* No wongew used */

	stwuct jset_entwy_dev_usage_type d[];
};

static inwine unsigned jset_entwy_dev_usage_nw_types(stwuct jset_entwy_dev_usage *u)
{
	wetuwn (vstwuct_bytes(&u->entwy) - sizeof(stwuct jset_entwy_dev_usage)) /
		sizeof(stwuct jset_entwy_dev_usage_type);
}

stwuct jset_entwy_wog {
	stwuct jset_entwy	entwy;
	u8			d[];
} __packed __awigned(8);

/*
 * On disk fowmat fow a jouwnaw entwy:
 * seq is monotonicawwy incweasing; evewy jouwnaw entwy has its own unique
 * sequence numbew.
 *
 * wast_seq is the owdest jouwnaw entwy that stiww has keys the btwee hasn't
 * fwushed to disk yet.
 *
 * vewsion is fow on disk fowmat changes.
 */
stwuct jset {
	stwuct bch_csum		csum;

	__we64			magic;
	__we64			seq;
	__we32			vewsion;
	__we32			fwags;

	__we32			u64s; /* size of d[] in u64s */

	__u8			encwypted_stawt[0];

	__we16			_wead_cwock; /* no wongew used */
	__we16			_wwite_cwock;

	/* Sequence numbew of owdest diwty jouwnaw entwy */
	__we64			wast_seq;


	stwuct jset_entwy	stawt[0];
	__u64			_data[];
} __packed __awigned(8);

WE32_BITMASK(JSET_CSUM_TYPE,	stwuct jset, fwags, 0, 4);
WE32_BITMASK(JSET_BIG_ENDIAN,	stwuct jset, fwags, 4, 5);
WE32_BITMASK(JSET_NO_FWUSH,	stwuct jset, fwags, 5, 6);

#define BCH_JOUWNAW_BUCKETS_MIN		8

/* Btwee: */

enum btwee_id_fwags {
	BTWEE_ID_EXTENTS	= BIT(0),
	BTWEE_ID_SNAPSHOTS	= BIT(1),
	BTWEE_ID_SNAPSHOT_FIEWD	= BIT(2),
	BTWEE_ID_DATA		= BIT(3),
};

#define BCH_BTWEE_IDS()								\
	x(extents,		0,	BTWEE_ID_EXTENTS|BTWEE_ID_SNAPSHOTS|BTWEE_ID_DATA,\
	  BIT_UWW(KEY_TYPE_whiteout)|						\
	  BIT_UWW(KEY_TYPE_ewwow)|						\
	  BIT_UWW(KEY_TYPE_cookie)|						\
	  BIT_UWW(KEY_TYPE_extent)|						\
	  BIT_UWW(KEY_TYPE_wesewvation)|					\
	  BIT_UWW(KEY_TYPE_wefwink_p)|						\
	  BIT_UWW(KEY_TYPE_inwine_data))					\
	x(inodes,		1,	BTWEE_ID_SNAPSHOTS,			\
	  BIT_UWW(KEY_TYPE_whiteout)|						\
	  BIT_UWW(KEY_TYPE_inode)|						\
	  BIT_UWW(KEY_TYPE_inode_v2)|						\
	  BIT_UWW(KEY_TYPE_inode_v3)|						\
	  BIT_UWW(KEY_TYPE_inode_genewation))					\
	x(diwents,		2,	BTWEE_ID_SNAPSHOTS,			\
	  BIT_UWW(KEY_TYPE_whiteout)|						\
	  BIT_UWW(KEY_TYPE_hash_whiteout)|					\
	  BIT_UWW(KEY_TYPE_diwent))						\
	x(xattws,		3,	BTWEE_ID_SNAPSHOTS,			\
	  BIT_UWW(KEY_TYPE_whiteout)|						\
	  BIT_UWW(KEY_TYPE_cookie)|						\
	  BIT_UWW(KEY_TYPE_hash_whiteout)|					\
	  BIT_UWW(KEY_TYPE_xattw))						\
	x(awwoc,		4,	0,					\
	  BIT_UWW(KEY_TYPE_awwoc)|						\
	  BIT_UWW(KEY_TYPE_awwoc_v2)|						\
	  BIT_UWW(KEY_TYPE_awwoc_v3)|						\
	  BIT_UWW(KEY_TYPE_awwoc_v4))						\
	x(quotas,		5,	0,					\
	  BIT_UWW(KEY_TYPE_quota))						\
	x(stwipes,		6,	0,					\
	  BIT_UWW(KEY_TYPE_stwipe))						\
	x(wefwink,		7,	BTWEE_ID_EXTENTS|BTWEE_ID_DATA,		\
	  BIT_UWW(KEY_TYPE_wefwink_v)|						\
	  BIT_UWW(KEY_TYPE_indiwect_inwine_data))				\
	x(subvowumes,		8,	0,					\
	  BIT_UWW(KEY_TYPE_subvowume))						\
	x(snapshots,		9,	0,					\
	  BIT_UWW(KEY_TYPE_snapshot))						\
	x(wwu,			10,	0,					\
	  BIT_UWW(KEY_TYPE_set))						\
	x(fweespace,		11,	BTWEE_ID_EXTENTS,			\
	  BIT_UWW(KEY_TYPE_set))						\
	x(need_discawd,		12,	0,					\
	  BIT_UWW(KEY_TYPE_set))						\
	x(backpointews,		13,	0,					\
	  BIT_UWW(KEY_TYPE_backpointew))					\
	x(bucket_gens,		14,	0,					\
	  BIT_UWW(KEY_TYPE_bucket_gens))					\
	x(snapshot_twees,	15,	0,					\
	  BIT_UWW(KEY_TYPE_snapshot_twee))					\
	x(deweted_inodes,	16,	BTWEE_ID_SNAPSHOT_FIEWD,		\
	  BIT_UWW(KEY_TYPE_set))						\
	x(wogged_ops,		17,	0,					\
	  BIT_UWW(KEY_TYPE_wogged_op_twuncate)|					\
	  BIT_UWW(KEY_TYPE_wogged_op_finsewt))					\
	x(webawance_wowk,	18,	BTWEE_ID_SNAPSHOT_FIEWD,		\
	  BIT_UWW(KEY_TYPE_set)|BIT_UWW(KEY_TYPE_cookie))

enum btwee_id {
#define x(name, nw, ...) BTWEE_ID_##name = nw,
	BCH_BTWEE_IDS()
#undef x
	BTWEE_ID_NW
};

#define BTWEE_MAX_DEPTH		4U

/* Btwee nodes */

/*
 * Btwee nodes
 *
 * On disk a btwee node is a wist/wog of these; within each set the keys awe
 * sowted
 */
stwuct bset {
	__we64			seq;

	/*
	 * Highest jouwnaw entwy this bset contains keys fow.
	 * If on wecovewy we don't see that jouwnaw entwy, this bset is ignowed:
	 * this awwows us to pwesewve the owdew of aww index updates aftew a
	 * cwash, since the jouwnaw wecowds a totaw owdew of aww index updates
	 * and anything that didn't make it to the jouwnaw doesn't get used.
	 */
	__we64			jouwnaw_seq;

	__we32			fwags;
	__we16			vewsion;
	__we16			u64s; /* count of d[] in u64s */

	stwuct bkey_packed	stawt[0];
	__u64			_data[];
} __packed __awigned(8);

WE32_BITMASK(BSET_CSUM_TYPE,	stwuct bset, fwags, 0, 4);

WE32_BITMASK(BSET_BIG_ENDIAN,	stwuct bset, fwags, 4, 5);
WE32_BITMASK(BSET_SEPAWATE_WHITEOUTS,
				stwuct bset, fwags, 5, 6);

/* Sectow offset within the btwee node: */
WE32_BITMASK(BSET_OFFSET,	stwuct bset, fwags, 16, 32);

stwuct btwee_node {
	stwuct bch_csum		csum;
	__we64			magic;

	/* this fwags fiewd is encwypted, unwike bset->fwags: */
	__we64			fwags;

	/* Cwosed intewvaw: */
	stwuct bpos		min_key;
	stwuct bpos		max_key;
	stwuct bch_extent_ptw	_ptw; /* not used anymowe */
	stwuct bkey_fowmat	fowmat;

	union {
	stwuct bset		keys;
	stwuct {
		__u8		pad[22];
		__we16		u64s;
		__u64		_data[0];

	};
	};
} __packed __awigned(8);

WE64_BITMASK(BTWEE_NODE_ID_WO,	stwuct btwee_node, fwags,  0,  4);
WE64_BITMASK(BTWEE_NODE_WEVEW,	stwuct btwee_node, fwags,  4,  8);
WE64_BITMASK(BTWEE_NODE_NEW_EXTENT_OVEWWWITE,
				stwuct btwee_node, fwags,  8,  9);
WE64_BITMASK(BTWEE_NODE_ID_HI,	stwuct btwee_node, fwags,  9, 25);
/* 25-32 unused */
WE64_BITMASK(BTWEE_NODE_SEQ,	stwuct btwee_node, fwags, 32, 64);

static inwine __u64 BTWEE_NODE_ID(stwuct btwee_node *n)
{
	wetuwn BTWEE_NODE_ID_WO(n) | (BTWEE_NODE_ID_HI(n) << 4);
}

static inwine void SET_BTWEE_NODE_ID(stwuct btwee_node *n, __u64 v)
{
	SET_BTWEE_NODE_ID_WO(n, v);
	SET_BTWEE_NODE_ID_HI(n, v >> 4);
}

stwuct btwee_node_entwy {
	stwuct bch_csum		csum;

	union {
	stwuct bset		keys;
	stwuct {
		__u8		pad[22];
		__we16		u64s;
		__u64		_data[0];
	};
	};
} __packed __awigned(8);

#endif /* _BCACHEFS_FOWMAT_H */
