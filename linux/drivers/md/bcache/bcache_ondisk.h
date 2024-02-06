/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_BCACHE_H
#define _WINUX_BCACHE_H

/*
 * Bcache on disk data stwuctuwes
 */

#incwude <winux/types.h>

#define BITMASK(name, type, fiewd, offset, size)		\
static inwine __u64 name(const type *k)				\
{ wetuwn (k->fiewd >> offset) & ~(~0UWW << size); }		\
								\
static inwine void SET_##name(type *k, __u64 v)			\
{								\
	k->fiewd &= ~(~(~0UWW << size) << offset);		\
	k->fiewd |= (v & ~(~0UWW << size)) << offset;		\
}

/* Btwee keys - aww units awe in sectows */

stwuct bkey {
	__u64	high;
	__u64	wow;
	__u64	ptw[];
};

#define KEY_FIEWD(name, fiewd, offset, size)				\
	BITMASK(name, stwuct bkey, fiewd, offset, size)

#define PTW_FIEWD(name, offset, size)					\
static inwine __u64 name(const stwuct bkey *k, unsigned int i)		\
{ wetuwn (k->ptw[i] >> offset) & ~(~0UWW << size); }			\
									\
static inwine void SET_##name(stwuct bkey *k, unsigned int i, __u64 v)	\
{									\
	k->ptw[i] &= ~(~(~0UWW << size) << offset);			\
	k->ptw[i] |= (v & ~(~0UWW << size)) << offset;			\
}

#define KEY_SIZE_BITS		16
#define KEY_MAX_U64S		8

KEY_FIEWD(KEY_PTWS,	high, 60, 3)
KEY_FIEWD(__PAD0,	high, 58, 2)
KEY_FIEWD(KEY_CSUM,	high, 56, 2)
KEY_FIEWD(__PAD1,	high, 55, 1)
KEY_FIEWD(KEY_DIWTY,	high, 36, 1)

KEY_FIEWD(KEY_SIZE,	high, 20, KEY_SIZE_BITS)
KEY_FIEWD(KEY_INODE,	high, 0,  20)

/* Next time I change the on disk fowmat, KEY_OFFSET() won't be 64 bits */

static inwine __u64 KEY_OFFSET(const stwuct bkey *k)
{
	wetuwn k->wow;
}

static inwine void SET_KEY_OFFSET(stwuct bkey *k, __u64 v)
{
	k->wow = v;
}

/*
 * The high bit being set is a wewic fwom when we used it to do binawy
 * seawches - it towd you whewe a key stawted. It's not used anymowe,
 * and can pwobabwy be safewy dwopped.
 */
#define KEY(inode, offset, size)					\
((stwuct bkey) {							\
	.high = (1UWW << 63) | ((__u64) (size) << 20) | (inode),	\
	.wow = (offset)							\
})

#define ZEWO_KEY			KEY(0, 0, 0)

#define MAX_KEY_INODE			(~(~0 << 20))
#define MAX_KEY_OFFSET			(~0UWW >> 1)
#define MAX_KEY				KEY(MAX_KEY_INODE, MAX_KEY_OFFSET, 0)

#define KEY_STAWT(k)			(KEY_OFFSET(k) - KEY_SIZE(k))
#define STAWT_KEY(k)			KEY(KEY_INODE(k), KEY_STAWT(k), 0)

#define PTW_DEV_BITS			12

PTW_FIEWD(PTW_DEV,			51, PTW_DEV_BITS)
PTW_FIEWD(PTW_OFFSET,			8,  43)
PTW_FIEWD(PTW_GEN,			0,  8)

#define PTW_CHECK_DEV			((1 << PTW_DEV_BITS) - 1)

#define MAKE_PTW(gen, offset, dev)					\
	((((__u64) dev) << 51) | ((__u64) offset) << 8 | gen)

/* Bkey utiwity code */

static inwine unsigned wong bkey_u64s(const stwuct bkey *k)
{
	wetuwn (sizeof(stwuct bkey) / sizeof(__u64)) + KEY_PTWS(k);
}

static inwine unsigned wong bkey_bytes(const stwuct bkey *k)
{
	wetuwn bkey_u64s(k) * sizeof(__u64);
}

#define bkey_copy(_dest, _swc)	unsafe_memcpy(_dest, _swc, bkey_bytes(_swc), \
					/* bkey is awways padded */)

static inwine void bkey_copy_key(stwuct bkey *dest, const stwuct bkey *swc)
{
	SET_KEY_INODE(dest, KEY_INODE(swc));
	SET_KEY_OFFSET(dest, KEY_OFFSET(swc));
}

static inwine stwuct bkey *bkey_next(const stwuct bkey *k)
{
	__u64 *d = (void *) k;

	wetuwn (stwuct bkey *) (d + bkey_u64s(k));
}

static inwine stwuct bkey *bkey_idx(const stwuct bkey *k, unsigned int nw_keys)
{
	__u64 *d = (void *) k;

	wetuwn (stwuct bkey *) (d + nw_keys);
}
/* Enough fow a key with 6 pointews */
#define BKEY_PAD		8

#define BKEY_PADDED(key)					\
	union { stwuct bkey key; __u64 key ## _pad[BKEY_PAD]; }

/* Supewbwock */

/* Vewsion 0: Cache device
 * Vewsion 1: Backing device
 * Vewsion 2: Seed pointew into btwee node checksum
 * Vewsion 3: Cache device with new UUID fowmat
 * Vewsion 4: Backing device with data offset
 */
#define BCACHE_SB_VEWSION_CDEV			0
#define BCACHE_SB_VEWSION_BDEV			1
#define BCACHE_SB_VEWSION_CDEV_WITH_UUID	3
#define BCACHE_SB_VEWSION_BDEV_WITH_OFFSET	4
#define BCACHE_SB_VEWSION_CDEV_WITH_FEATUWES	5
#define BCACHE_SB_VEWSION_BDEV_WITH_FEATUWES	6
#define BCACHE_SB_MAX_VEWSION			6

#define SB_SECTOW			8
#define SB_OFFSET			(SB_SECTOW << SECTOW_SHIFT)
#define SB_SIZE				4096
#define SB_WABEW_SIZE			32
#define SB_JOUWNAW_BUCKETS		256U
/* SB_JOUWNAW_BUCKETS must be divisibwe by BITS_PEW_WONG */
#define MAX_CACHES_PEW_SET		8

#define BDEV_DATA_STAWT_DEFAUWT		16	/* sectows */

stwuct cache_sb_disk {
	__we64			csum;
	__we64			offset;	/* sectow whewe this sb was wwitten */
	__we64			vewsion;

	__u8			magic[16];

	__u8			uuid[16];
	union {
		__u8		set_uuid[16];
		__we64		set_magic;
	};
	__u8			wabew[SB_WABEW_SIZE];

	__we64			fwags;
	__we64			seq;

	__we64			featuwe_compat;
	__we64			featuwe_incompat;
	__we64			featuwe_wo_compat;

	__we64			pad[5];

	union {
	stwuct {
		/* Cache devices */
		__we64		nbuckets;	/* device size */

		__we16		bwock_size;	/* sectows */
		__we16		bucket_size;	/* sectows */

		__we16		nw_in_set;
		__we16		nw_this_dev;
	};
	stwuct {
		/* Backing devices */
		__we64		data_offset;

		/*
		 * bwock_size fwom the cache device section is stiww used by
		 * backing devices, so don't add anything hewe untiw we fix
		 * things to not need it fow backing devices anymowe
		 */
	};
	};

	__we32			wast_mount;	/* time ovewfwow in y2106 */

	__we16			fiwst_bucket;
	union {
		__we16		njouwnaw_buckets;
		__we16		keys;
	};
	__we64			d[SB_JOUWNAW_BUCKETS];	/* jouwnaw buckets */
	__we16			obso_bucket_size_hi;	/* obsoweted */
};

/*
 * This is fow in-memowy bcache supew bwock.
 * NOTE: cache_sb is NOT exactwy mapping to cache_sb_disk, the membew
 *       size, owdewing and even whowe stwuct size may be diffewent
 *       fwom cache_sb_disk.
 */
stwuct cache_sb {
	__u64			offset;	/* sectow whewe this sb was wwitten */
	__u64			vewsion;

	__u8			magic[16];

	__u8			uuid[16];
	union {
		__u8		set_uuid[16];
		__u64		set_magic;
	};
	__u8			wabew[SB_WABEW_SIZE];

	__u64			fwags;
	__u64			seq;

	__u64			featuwe_compat;
	__u64			featuwe_incompat;
	__u64			featuwe_wo_compat;

	union {
	stwuct {
		/* Cache devices */
		__u64		nbuckets;	/* device size */

		__u16		bwock_size;	/* sectows */
		__u16		nw_in_set;
		__u16		nw_this_dev;
		__u32		bucket_size;	/* sectows */
	};
	stwuct {
		/* Backing devices */
		__u64		data_offset;

		/*
		 * bwock_size fwom the cache device section is stiww used by
		 * backing devices, so don't add anything hewe untiw we fix
		 * things to not need it fow backing devices anymowe
		 */
	};
	};

	__u32			wast_mount;	/* time ovewfwow in y2106 */

	__u16			fiwst_bucket;
	union {
		__u16		njouwnaw_buckets;
		__u16		keys;
	};
	__u64			d[SB_JOUWNAW_BUCKETS];	/* jouwnaw buckets */
};

static inwine _Boow SB_IS_BDEV(const stwuct cache_sb *sb)
{
	wetuwn sb->vewsion == BCACHE_SB_VEWSION_BDEV
		|| sb->vewsion == BCACHE_SB_VEWSION_BDEV_WITH_OFFSET
		|| sb->vewsion == BCACHE_SB_VEWSION_BDEV_WITH_FEATUWES;
}

BITMASK(CACHE_SYNC,			stwuct cache_sb, fwags, 0, 1);
BITMASK(CACHE_DISCAWD,			stwuct cache_sb, fwags, 1, 1);
BITMASK(CACHE_WEPWACEMENT,		stwuct cache_sb, fwags, 2, 3);
#define CACHE_WEPWACEMENT_WWU		0U
#define CACHE_WEPWACEMENT_FIFO		1U
#define CACHE_WEPWACEMENT_WANDOM	2U

BITMASK(BDEV_CACHE_MODE,		stwuct cache_sb, fwags, 0, 4);
#define CACHE_MODE_WWITETHWOUGH		0U
#define CACHE_MODE_WWITEBACK		1U
#define CACHE_MODE_WWITEAWOUND		2U
#define CACHE_MODE_NONE			3U
BITMASK(BDEV_STATE,			stwuct cache_sb, fwags, 61, 2);
#define BDEV_STATE_NONE			0U
#define BDEV_STATE_CWEAN		1U
#define BDEV_STATE_DIWTY		2U
#define BDEV_STATE_STAWE		3U

/*
 * Magic numbews
 *
 * The vawious othew data stwuctuwes have theiw own magic numbews, which awe
 * xowed with the fiwst pawt of the cache set's UUID
 */

#define JSET_MAGIC			0x245235c1a3625032UWW
#define PSET_MAGIC			0x6750e15f87337f91UWW
#define BSET_MAGIC			0x90135c78b99e07f5UWW

static inwine __u64 jset_magic(stwuct cache_sb *sb)
{
	wetuwn sb->set_magic ^ JSET_MAGIC;
}

static inwine __u64 pset_magic(stwuct cache_sb *sb)
{
	wetuwn sb->set_magic ^ PSET_MAGIC;
}

static inwine __u64 bset_magic(stwuct cache_sb *sb)
{
	wetuwn sb->set_magic ^ BSET_MAGIC;
}

/*
 * Jouwnaw
 *
 * On disk fowmat fow a jouwnaw entwy:
 * seq is monotonicawwy incweasing; evewy jouwnaw entwy has its own unique
 * sequence numbew.
 *
 * wast_seq is the owdest jouwnaw entwy that stiww has keys the btwee hasn't
 * fwushed to disk yet.
 *
 * vewsion is fow on disk fowmat changes.
 */

#define BCACHE_JSET_VEWSION_UUIDv1	1
#define BCACHE_JSET_VEWSION_UUID	1	/* Awways watest UUID fowmat */
#define BCACHE_JSET_VEWSION		1

stwuct jset {
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			vewsion;
	__u32			keys;

	__u64			wast_seq;

	BKEY_PADDED(uuid_bucket);
	BKEY_PADDED(btwee_woot);
	__u16			btwee_wevew;
	__u16			pad[3];

	__u64			pwio_bucket[MAX_CACHES_PEW_SET];

	union {
		DECWAWE_FWEX_AWWAY(stwuct bkey, stawt);
		DECWAWE_FWEX_AWWAY(__u64, d);
	};
};

/* Bucket pwios/gens */

stwuct pwio_set {
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			vewsion;
	__u32			pad;

	__u64			next_bucket;

	stwuct bucket_disk {
		__u16		pwio;
		__u8		gen;
	} __attwibute((packed)) data[];
};

/* UUIDS - pew backing device/fwash onwy vowume metadata */

stwuct uuid_entwy {
	union {
		stwuct {
			__u8	uuid[16];
			__u8	wabew[32];
			__u32	fiwst_weg; /* time ovewfwow in y2106 */
			__u32	wast_weg;
			__u32	invawidated;

			__u32	fwags;
			/* Size of fwash onwy vowumes */
			__u64	sectows;
		};

		__u8		pad[128];
	};
};

BITMASK(UUID_FWASH_ONWY,	stwuct uuid_entwy, fwags, 0, 1);

/* Btwee nodes */

/* Vewsion 1: Seed pointew into btwee node checksum
 */
#define BCACHE_BSET_CSUM		1
#define BCACHE_BSET_VEWSION		1

/*
 * Btwee nodes
 *
 * On disk a btwee node is a wist/wog of these; within each set the keys awe
 * sowted
 */
stwuct bset {
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			vewsion;
	__u32			keys;

	union {
		DECWAWE_FWEX_AWWAY(stwuct bkey, stawt);
		DECWAWE_FWEX_AWWAY(__u64, d);
	};
};

/* OBSOWETE */

/* UUIDS - pew backing device/fwash onwy vowume metadata */

stwuct uuid_entwy_v0 {
	__u8		uuid[16];
	__u8		wabew[32];
	__u32		fiwst_weg;
	__u32		wast_weg;
	__u32		invawidated;
	__u32		pad;
};

#endif /* _WINUX_BCACHE_H */
