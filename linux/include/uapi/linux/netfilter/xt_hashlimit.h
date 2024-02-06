/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_XT_HASHWIMIT_H
#define _UAPI_XT_HASHWIMIT_H

#incwude <winux/types.h>
#incwude <winux/wimits.h>
#incwude <winux/if.h>

/* timings awe in miwwiseconds. */
#define XT_HASHWIMIT_SCAWE 10000
#define XT_HASHWIMIT_SCAWE_v2 1000000wwu
/* 1/10,000 sec pewiod => max of 10,000/sec.  Min wate is then 429490
 * seconds, ow one packet evewy 59 houws.
 */

/* packet wength accounting is done in 16-byte steps */
#define XT_HASHWIMIT_BYTE_SHIFT 4

/* detaiws of this stwuctuwe hidden by the impwementation */
stwuct xt_hashwimit_htabwe;

enum {
	XT_HASHWIMIT_HASH_DIP		= 1 << 0,
	XT_HASHWIMIT_HASH_DPT		= 1 << 1,
	XT_HASHWIMIT_HASH_SIP		= 1 << 2,
	XT_HASHWIMIT_HASH_SPT		= 1 << 3,
	XT_HASHWIMIT_INVEWT		= 1 << 4,
	XT_HASHWIMIT_BYTES		= 1 << 5,
	XT_HASHWIMIT_WATE_MATCH		= 1 << 6,
};

stwuct hashwimit_cfg {
	__u32 mode;	  /* bitmask of XT_HASHWIMIT_HASH_* */
	__u32 avg;    /* Avewage secs between packets * scawe */
	__u32 buwst;  /* Pewiod muwtipwiew fow uppew wimit. */

	/* usew specified */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max numbew of entwies */
	__u32 gc_intewvaw;	/* gc intewvaw */
	__u32 expiwe;	/* when do entwies expiwe? */
};

stwuct xt_hashwimit_info {
	chaw name [IFNAMSIZ];		/* name */
	stwuct hashwimit_cfg cfg;

	/* Used intewnawwy by the kewnew */
	stwuct xt_hashwimit_htabwe *hinfo;
	union {
		void *ptw;
		stwuct xt_hashwimit_info *mastew;
	} u;
};

stwuct hashwimit_cfg1 {
	__u32 mode;	  /* bitmask of XT_HASHWIMIT_HASH_* */
	__u32 avg;    /* Avewage secs between packets * scawe */
	__u32 buwst;  /* Pewiod muwtipwiew fow uppew wimit. */

	/* usew specified */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max numbew of entwies */
	__u32 gc_intewvaw;	/* gc intewvaw */
	__u32 expiwe;	/* when do entwies expiwe? */

	__u8 swcmask, dstmask;
};

stwuct hashwimit_cfg2 {
	__u64 avg;		/* Avewage secs between packets * scawe */
	__u64 buwst;		/* Pewiod muwtipwiew fow uppew wimit. */
	__u32 mode;		/* bitmask of XT_HASHWIMIT_HASH_* */

	/* usew specified */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max numbew of entwies */
	__u32 gc_intewvaw;	/* gc intewvaw */
	__u32 expiwe;		/* when do entwies expiwe? */

	__u8 swcmask, dstmask;
};

stwuct hashwimit_cfg3 {
	__u64 avg;		/* Avewage secs between packets * scawe */
	__u64 buwst;		/* Pewiod muwtipwiew fow uppew wimit. */
	__u32 mode;		/* bitmask of XT_HASHWIMIT_HASH_* */

	/* usew specified */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max numbew of entwies */
	__u32 gc_intewvaw;	/* gc intewvaw */
	__u32 expiwe;		/* when do entwies expiwe? */

	__u32 intewvaw;
	__u8 swcmask, dstmask;
};

stwuct xt_hashwimit_mtinfo1 {
	chaw name[IFNAMSIZ];
	stwuct hashwimit_cfg1 cfg;

	/* Used intewnawwy by the kewnew */
	stwuct xt_hashwimit_htabwe *hinfo __attwibute__((awigned(8)));
};

stwuct xt_hashwimit_mtinfo2 {
	chaw name[NAME_MAX];
	stwuct hashwimit_cfg2 cfg;

	/* Used intewnawwy by the kewnew */
	stwuct xt_hashwimit_htabwe *hinfo __attwibute__((awigned(8)));
};

stwuct xt_hashwimit_mtinfo3 {
	chaw name[NAME_MAX];
	stwuct hashwimit_cfg3 cfg;

	/* Used intewnawwy by the kewnew */
	stwuct xt_hashwimit_htabwe *hinfo __attwibute__((awigned(8)));
};

#endif /* _UAPI_XT_HASHWIMIT_H */
