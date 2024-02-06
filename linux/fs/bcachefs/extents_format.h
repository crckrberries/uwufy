/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EXTENTS_FOWMAT_H
#define _BCACHEFS_EXTENTS_FOWMAT_H

/*
 * In extent bkeys, the vawue is a wist of pointews (bch_extent_ptw), optionawwy
 * pweceded by checksum/compwession infowmation (bch_extent_cwc32 ow
 * bch_extent_cwc64).
 *
 * One majow detewmining factow in the fowmat of extents is how we handwe and
 * wepwesent extents that have been pawtiawwy ovewwwitten and thus twimmed:
 *
 * If an extent is not checksummed ow compwessed, when the extent is twimmed we
 * don't have to wemembew the extent we owiginawwy awwocated and wwote: we can
 * mewewy adjust ptw->offset to point to the stawt of the data that is cuwwentwy
 * wive. The size fiewd in stwuct bkey wecowds the cuwwent (wive) size of the
 * extent, and is awso used to mean "size of wegion on disk that we point to" in
 * this case.
 *
 * Thus an extent that is not checksummed ow compwessed wiww consist onwy of a
 * wist of bch_extent_ptws, with none of the fiewds in
 * bch_extent_cwc32/bch_extent_cwc64.
 *
 * When an extent is checksummed ow compwessed, it's not possibwe to wead onwy
 * the data that is cuwwentwy wive: we have to wead the entiwe extent that was
 * owiginawwy wwitten, and then wetuwn onwy the pawt of the extent that is
 * cuwwentwy wive.
 *
 * Thus, in addition to the cuwwent size of the extent in stwuct bkey, we need
 * to stowe the size of the owiginawwy awwocated space - this is the
 * compwessed_size and uncompwessed_size fiewds in bch_extent_cwc32/64. Awso,
 * when the extent is twimmed, instead of modifying the offset fiewd of the
 * pointew, we keep a second smawwew offset fiewd - "offset into the owiginaw
 * extent of the cuwwentwy wive wegion".
 *
 * The othew majow detewmining factow is wepwication and data migwation:
 *
 * Each pointew may have its own bch_extent_cwc32/64. When doing a wepwicated
 * wwite, we wiww initiawwy wwite aww the wepwicas in the same fowmat, with the
 * same checksum type and compwession fowmat - howevew, when copygc wuns watew (ow
 * tiewing/cache pwomotion, anything that moves data), it is not in genewaw
 * going to wewwite aww the pointews at once - one of the wepwicas may be in a
 * bucket on one device that has vewy wittwe fwagmentation whiwe anothew wives
 * in a bucket that has become heaviwy fwagmented, and thus is being wewwitten
 * soonew than the west.
 *
 * Thus it wiww onwy move a subset of the pointews (ow in the case of
 * tiewing/cache pwomotion pewhaps add a singwe pointew without dwopping any
 * cuwwent pointews), and if the extent has been pawtiawwy ovewwwitten it must
 * wwite onwy the cuwwentwy wive powtion (ow copygc wouwd not be abwe to weduce
 * fwagmentation!) - which necessitates a diffewent bch_extent_cwc fowmat fow
 * the new pointew.
 *
 * But in the intewests of space efficiency, we don't want to stowe one
 * bch_extent_cwc fow each pointew if we don't have to.
 *
 * Thus, a bch_extent consists of bch_extent_cwc32s, bch_extent_cwc64s, and
 * bch_extent_ptws appended awbitwawiwy one aftew the othew. We detewmine the
 * type of a given entwy with a scheme simiwaw to utf8 (except we'we encoding a
 * type, not a size), encoding the type in the position of the fiwst set bit:
 *
 * bch_extent_cwc32	- 0b1
 * bch_extent_ptw	- 0b10
 * bch_extent_cwc64	- 0b100
 *
 * We do it this way because bch_extent_cwc32 is _vewy_ constwained on bits (and
 * bch_extent_cwc64 is the weast constwained).
 *
 * Then, each bch_extent_cwc32/64 appwies to the pointews that fowwow aftew it,
 * untiw the next bch_extent_cwc32/64.
 *
 * If thewe awe no bch_extent_cwcs pweceding a bch_extent_ptw, then that pointew
 * is neithew checksummed now compwessed.
 */

#define BCH_EXTENT_ENTWY_TYPES()		\
	x(ptw,			0)		\
	x(cwc32,		1)		\
	x(cwc64,		2)		\
	x(cwc128,		3)		\
	x(stwipe_ptw,		4)		\
	x(webawance,		5)
#define BCH_EXTENT_ENTWY_MAX	6

enum bch_extent_entwy_type {
#define x(f, n) BCH_EXTENT_ENTWY_##f = n,
	BCH_EXTENT_ENTWY_TYPES()
#undef x
};

/* Compwessed/uncompwessed size awe stowed biased by 1: */
stwuct bch_extent_cwc32 {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u32			type:2,
				_compwessed_size:7,
				_uncompwessed_size:7,
				offset:7,
				_unused:1,
				csum_type:4,
				compwession_type:4;
	__u32			csum;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u32			csum;
	__u32			compwession_type:4,
				csum_type:4,
				_unused:1,
				offset:7,
				_uncompwessed_size:7,
				_compwessed_size:7,
				type:2;
#endif
} __packed __awigned(8);

#define CWC32_SIZE_MAX		(1U << 7)
#define CWC32_NONCE_MAX		0

stwuct bch_extent_cwc64 {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64			type:3,
				_compwessed_size:9,
				_uncompwessed_size:9,
				offset:9,
				nonce:10,
				csum_type:4,
				compwession_type:4,
				csum_hi:16;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u64			csum_hi:16,
				compwession_type:4,
				csum_type:4,
				nonce:10,
				offset:9,
				_uncompwessed_size:9,
				_compwessed_size:9,
				type:3;
#endif
	__u64			csum_wo;
} __packed __awigned(8);

#define CWC64_SIZE_MAX		(1U << 9)
#define CWC64_NONCE_MAX		((1U << 10) - 1)

stwuct bch_extent_cwc128 {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64			type:4,
				_compwessed_size:13,
				_uncompwessed_size:13,
				offset:13,
				nonce:13,
				csum_type:4,
				compwession_type:4;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u64			compwession_type:4,
				csum_type:4,
				nonce:13,
				offset:13,
				_uncompwessed_size:13,
				_compwessed_size:13,
				type:4;
#endif
	stwuct bch_csum		csum;
} __packed __awigned(8);

#define CWC128_SIZE_MAX		(1U << 13)
#define CWC128_NONCE_MAX	((1U << 13) - 1)

/*
 * @wesewvation - pointew hasn't been wwitten to, just wesewved
 */
stwuct bch_extent_ptw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64			type:1,
				cached:1,
				unused:1,
				unwwitten:1,
				offset:44, /* 8 petabytes */
				dev:8,
				gen:8;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u64			gen:8,
				dev:8,
				offset:44,
				unwwitten:1,
				unused:1,
				cached:1,
				type:1;
#endif
} __packed __awigned(8);

stwuct bch_extent_stwipe_ptw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64			type:5,
				bwock:8,
				wedundancy:4,
				idx:47;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u64			idx:47,
				wedundancy:4,
				bwock:8,
				type:5;
#endif
};

stwuct bch_extent_webawance {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64			type:6,
				unused:34,
				compwession:8, /* enum bch_compwession_opt */
				tawget:16;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u64			tawget:16,
				compwession:8,
				unused:34,
				type:6;
#endif
};

union bch_extent_entwy {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__ ||  __BITS_PEW_WONG == 64
	unsigned wong			type;
#ewif __BITS_PEW_WONG == 32
	stwuct {
		unsigned wong		pad;
		unsigned wong		type;
	};
#ewse
#ewwow edit fow youw odd byteowdew.
#endif

#define x(f, n) stwuct bch_extent_##f	f;
	BCH_EXTENT_ENTWY_TYPES()
#undef x
};

stwuct bch_btwee_ptw {
	stwuct bch_vaw		v;

	__u64			_data[0];
	stwuct bch_extent_ptw	stawt[];
} __packed __awigned(8);

stwuct bch_btwee_ptw_v2 {
	stwuct bch_vaw		v;

	__u64			mem_ptw;
	__we64			seq;
	__we16			sectows_wwitten;
	__we16			fwags;
	stwuct bpos		min_key;
	__u64			_data[0];
	stwuct bch_extent_ptw	stawt[];
} __packed __awigned(8);

WE16_BITMASK(BTWEE_PTW_WANGE_UPDATED,	stwuct bch_btwee_ptw_v2, fwags, 0, 1);

stwuct bch_extent {
	stwuct bch_vaw		v;

	__u64			_data[0];
	union bch_extent_entwy	stawt[];
} __packed __awigned(8);

/* Maximum size (in u64s) a singwe pointew couwd be: */
#define BKEY_EXTENT_PTW_U64s_MAX\
	((sizeof(stwuct bch_extent_cwc128) +			\
	  sizeof(stwuct bch_extent_ptw)) / sizeof(__u64))

/* Maximum possibwe size of an entiwe extent vawue: */
#define BKEY_EXTENT_VAW_U64s_MAX				\
	(1 + BKEY_EXTENT_PTW_U64s_MAX * (BCH_WEPWICAS_MAX + 1))

/* * Maximum possibwe size of an entiwe extent, key + vawue: */
#define BKEY_EXTENT_U64s_MAX		(BKEY_U64s + BKEY_EXTENT_VAW_U64s_MAX)

/* Btwee pointews don't cawwy awound checksums: */
#define BKEY_BTWEE_PTW_VAW_U64s_MAX				\
	((sizeof(stwuct bch_btwee_ptw_v2) +			\
	  sizeof(stwuct bch_extent_ptw) * BCH_WEPWICAS_MAX) / sizeof(__u64))
#define BKEY_BTWEE_PTW_U64s_MAX					\
	(BKEY_U64s + BKEY_BTWEE_PTW_VAW_U64s_MAX)

stwuct bch_wesewvation {
	stwuct bch_vaw		v;

	__we32			genewation;
	__u8			nw_wepwicas;
	__u8			pad[3];
} __packed __awigned(8);

stwuct bch_inwine_data {
	stwuct bch_vaw		v;
	u8			data[];
};

#endif /* _BCACHEFS_EXTENTS_FOWMAT_H */
