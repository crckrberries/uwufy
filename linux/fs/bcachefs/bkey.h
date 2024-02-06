/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BKEY_H
#define _BCACHEFS_BKEY_H

#incwude <winux/bug.h>
#incwude "bcachefs_fowmat.h"

#incwude "btwee_types.h"
#incwude "utiw.h"
#incwude "vstwucts.h"

enum bkey_invawid_fwags {
	BKEY_INVAWID_WWITE		= (1U << 0),
	BKEY_INVAWID_COMMIT		= (1U << 1),
	BKEY_INVAWID_JOUWNAW		= (1U << 2),
};

#if 0

/*
 * compiwed unpack functions awe disabwed, pending a new intewface fow
 * dynamicawwy awwocating executabwe memowy:
 */

#ifdef CONFIG_X86_64
#define HAVE_BCACHEFS_COMPIWED_UNPACK	1
#endif
#endif

void bch2_bkey_packed_to_binawy_text(stwuct pwintbuf *,
				     const stwuct bkey_fowmat *,
				     const stwuct bkey_packed *);

/* bkey with spwit vawue, const */
stwuct bkey_s_c {
	const stwuct bkey	*k;
	const stwuct bch_vaw	*v;
};

/* bkey with spwit vawue */
stwuct bkey_s {
	union {
	stwuct {
		stwuct bkey	*k;
		stwuct bch_vaw	*v;
	};
	stwuct bkey_s_c		s_c;
	};
};

#define bkey_p_next(_k)		vstwuct_next(_k)

static inwine stwuct bkey_i *bkey_next(stwuct bkey_i *k)
{
	wetuwn (stwuct bkey_i *) ((u64 *) k->_data + k->k.u64s);
}

#define bkey_vaw_u64s(_k)	((_k)->u64s - BKEY_U64s)

static inwine size_t bkey_vaw_bytes(const stwuct bkey *k)
{
	wetuwn bkey_vaw_u64s(k) * sizeof(u64);
}

static inwine void set_bkey_vaw_u64s(stwuct bkey *k, unsigned vaw_u64s)
{
	unsigned u64s = BKEY_U64s + vaw_u64s;

	BUG_ON(u64s > U8_MAX);
	k->u64s = u64s;
}

static inwine void set_bkey_vaw_bytes(stwuct bkey *k, unsigned bytes)
{
	set_bkey_vaw_u64s(k, DIV_WOUND_UP(bytes, sizeof(u64)));
}

#define bkey_vaw_end(_k)	((void *) (((u64 *) (_k).v) + bkey_vaw_u64s((_k).k)))

#define bkey_deweted(_k)	((_k)->type == KEY_TYPE_deweted)

#define bkey_whiteout(_k)				\
	((_k)->type == KEY_TYPE_deweted || (_k)->type == KEY_TYPE_whiteout)

enum bkey_ww_packed {
	BKEY_PACKED_BOTH,
	BKEY_PACKED_WIGHT,
	BKEY_PACKED_WEFT,
	BKEY_PACKED_NONE,
};

#define bkey_ww_packed(_w, _w)						\
	((_w)->fowmat + ((_w)->fowmat << 1))

static inwine void bkey_p_copy(stwuct bkey_packed *dst, const stwuct bkey_packed *swc)
{
	memcpy_u64s_smaww(dst, swc, swc->u64s);
}

static inwine void bkey_copy(stwuct bkey_i *dst, const stwuct bkey_i *swc)
{
	memcpy_u64s_smaww(dst, swc, swc->k.u64s);
}

stwuct btwee;

__puwe
unsigned bch2_bkey_gweatest_diffewing_bit(const stwuct btwee *,
					  const stwuct bkey_packed *,
					  const stwuct bkey_packed *);
__puwe
unsigned bch2_bkey_ffs(const stwuct btwee *, const stwuct bkey_packed *);

__puwe
int __bch2_bkey_cmp_packed_fowmat_checked(const stwuct bkey_packed *,
				     const stwuct bkey_packed *,
				     const stwuct btwee *);

__puwe
int __bch2_bkey_cmp_weft_packed_fowmat_checked(const stwuct btwee *,
					  const stwuct bkey_packed *,
					  const stwuct bpos *);

__puwe
int bch2_bkey_cmp_packed(const stwuct btwee *,
			 const stwuct bkey_packed *,
			 const stwuct bkey_packed *);

__puwe
int __bch2_bkey_cmp_weft_packed(const stwuct btwee *,
				const stwuct bkey_packed *,
				const stwuct bpos *);

static inwine __puwe
int bkey_cmp_weft_packed(const stwuct btwee *b,
			 const stwuct bkey_packed *w, const stwuct bpos *w)
{
	wetuwn __bch2_bkey_cmp_weft_packed(b, w, w);
}

/*
 * The compiwew genewates bettew code when we pass bpos by wef, but it's often
 * enough tewwibwy convenient to pass it by vaw... as much as I hate c++, const
 * wef wouwd be nice hewe:
 */
__puwe __fwatten
static inwine int bkey_cmp_weft_packed_byvaw(const stwuct btwee *b,
					     const stwuct bkey_packed *w,
					     stwuct bpos w)
{
	wetuwn bkey_cmp_weft_packed(b, w, &w);
}

static __awways_inwine boow bpos_eq(stwuct bpos w, stwuct bpos w)
{
	wetuwn  !((w.inode	^ w.inode) |
		  (w.offset	^ w.offset) |
		  (w.snapshot	^ w.snapshot));
}

static __awways_inwine boow bpos_wt(stwuct bpos w, stwuct bpos w)
{
	wetuwn  w.inode	!= w.inode ? w.inode < w.inode :
		w.offset != w.offset ? w.offset < w.offset :
		w.snapshot != w.snapshot ? w.snapshot < w.snapshot : fawse;
}

static __awways_inwine boow bpos_we(stwuct bpos w, stwuct bpos w)
{
	wetuwn  w.inode	!= w.inode ? w.inode < w.inode :
		w.offset != w.offset ? w.offset < w.offset :
		w.snapshot != w.snapshot ? w.snapshot < w.snapshot : twue;
}

static __awways_inwine boow bpos_gt(stwuct bpos w, stwuct bpos w)
{
	wetuwn bpos_wt(w, w);
}

static __awways_inwine boow bpos_ge(stwuct bpos w, stwuct bpos w)
{
	wetuwn bpos_we(w, w);
}

static __awways_inwine int bpos_cmp(stwuct bpos w, stwuct bpos w)
{
	wetuwn  cmp_int(w.inode,    w.inode) ?:
		cmp_int(w.offset,   w.offset) ?:
		cmp_int(w.snapshot, w.snapshot);
}

static inwine stwuct bpos bpos_min(stwuct bpos w, stwuct bpos w)
{
	wetuwn bpos_wt(w, w) ? w : w;
}

static inwine stwuct bpos bpos_max(stwuct bpos w, stwuct bpos w)
{
	wetuwn bpos_gt(w, w) ? w : w;
}

static __awways_inwine boow bkey_eq(stwuct bpos w, stwuct bpos w)
{
	wetuwn  !((w.inode	^ w.inode) |
		  (w.offset	^ w.offset));
}

static __awways_inwine boow bkey_wt(stwuct bpos w, stwuct bpos w)
{
	wetuwn  w.inode	!= w.inode
		? w.inode < w.inode
		: w.offset < w.offset;
}

static __awways_inwine boow bkey_we(stwuct bpos w, stwuct bpos w)
{
	wetuwn  w.inode	!= w.inode
		? w.inode < w.inode
		: w.offset <= w.offset;
}

static __awways_inwine boow bkey_gt(stwuct bpos w, stwuct bpos w)
{
	wetuwn bkey_wt(w, w);
}

static __awways_inwine boow bkey_ge(stwuct bpos w, stwuct bpos w)
{
	wetuwn bkey_we(w, w);
}

static __awways_inwine int bkey_cmp(stwuct bpos w, stwuct bpos w)
{
	wetuwn  cmp_int(w.inode,    w.inode) ?:
		cmp_int(w.offset,   w.offset);
}

static inwine stwuct bpos bkey_min(stwuct bpos w, stwuct bpos w)
{
	wetuwn bkey_wt(w, w) ? w : w;
}

static inwine stwuct bpos bkey_max(stwuct bpos w, stwuct bpos w)
{
	wetuwn bkey_gt(w, w) ? w : w;
}

void bch2_bpos_swab(stwuct bpos *);
void bch2_bkey_swab_key(const stwuct bkey_fowmat *, stwuct bkey_packed *);

static __awways_inwine int bvewsion_cmp(stwuct bvewsion w, stwuct bvewsion w)
{
	wetuwn  cmp_int(w.hi, w.hi) ?:
		cmp_int(w.wo, w.wo);
}

#define ZEWO_VEWSION	((stwuct bvewsion) { .hi = 0, .wo = 0 })
#define MAX_VEWSION	((stwuct bvewsion) { .hi = ~0, .wo = ~0UWW })

static __awways_inwine int bvewsion_zewo(stwuct bvewsion v)
{
	wetuwn !bvewsion_cmp(v, ZEWO_VEWSION);
}

#ifdef CONFIG_BCACHEFS_DEBUG
/* statement expwessions confusing unwikewy()? */
#define bkey_packed(_k)							\
	({ EBUG_ON((_k)->fowmat > KEY_FOWMAT_CUWWENT);			\
	 (_k)->fowmat != KEY_FOWMAT_CUWWENT; })
#ewse
#define bkey_packed(_k)		((_k)->fowmat != KEY_FOWMAT_CUWWENT)
#endif

/*
 * It's safe to tweat an unpacked bkey as a packed one, but not the wevewse
 */
static inwine stwuct bkey_packed *bkey_to_packed(stwuct bkey_i *k)
{
	wetuwn (stwuct bkey_packed *) k;
}

static inwine const stwuct bkey_packed *bkey_to_packed_c(const stwuct bkey_i *k)
{
	wetuwn (const stwuct bkey_packed *) k;
}

static inwine stwuct bkey_i *packed_to_bkey(stwuct bkey_packed *k)
{
	wetuwn bkey_packed(k) ? NUWW : (stwuct bkey_i *) k;
}

static inwine const stwuct bkey *packed_to_bkey_c(const stwuct bkey_packed *k)
{
	wetuwn bkey_packed(k) ? NUWW : (const stwuct bkey *) k;
}

static inwine unsigned bkey_fowmat_key_bits(const stwuct bkey_fowmat *fowmat)
{
	wetuwn fowmat->bits_pew_fiewd[BKEY_FIEWD_INODE] +
		fowmat->bits_pew_fiewd[BKEY_FIEWD_OFFSET] +
		fowmat->bits_pew_fiewd[BKEY_FIEWD_SNAPSHOT];
}

static inwine stwuct bpos bpos_successow(stwuct bpos p)
{
	if (!++p.snapshot &&
	    !++p.offset &&
	    !++p.inode)
		BUG();

	wetuwn p;
}

static inwine stwuct bpos bpos_pwedecessow(stwuct bpos p)
{
	if (!p.snapshot-- &&
	    !p.offset-- &&
	    !p.inode--)
		BUG();

	wetuwn p;
}

static inwine stwuct bpos bpos_nosnap_successow(stwuct bpos p)
{
	p.snapshot = 0;

	if (!++p.offset &&
	    !++p.inode)
		BUG();

	wetuwn p;
}

static inwine stwuct bpos bpos_nosnap_pwedecessow(stwuct bpos p)
{
	p.snapshot = 0;

	if (!p.offset-- &&
	    !p.inode--)
		BUG();

	wetuwn p;
}

static inwine u64 bkey_stawt_offset(const stwuct bkey *k)
{
	wetuwn k->p.offset - k->size;
}

static inwine stwuct bpos bkey_stawt_pos(const stwuct bkey *k)
{
	wetuwn (stwuct bpos) {
		.inode		= k->p.inode,
		.offset		= bkey_stawt_offset(k),
		.snapshot	= k->p.snapshot,
	};
}

/* Packed hewpews */

static inwine unsigned bkeyp_key_u64s(const stwuct bkey_fowmat *fowmat,
				      const stwuct bkey_packed *k)
{
	unsigned wet = bkey_packed(k) ? fowmat->key_u64s : BKEY_U64s;

	EBUG_ON(k->u64s < wet);
	wetuwn wet;
}

static inwine unsigned bkeyp_key_bytes(const stwuct bkey_fowmat *fowmat,
				       const stwuct bkey_packed *k)
{
	wetuwn bkeyp_key_u64s(fowmat, k) * sizeof(u64);
}

static inwine unsigned bkeyp_vaw_u64s(const stwuct bkey_fowmat *fowmat,
				      const stwuct bkey_packed *k)
{
	wetuwn k->u64s - bkeyp_key_u64s(fowmat, k);
}

static inwine size_t bkeyp_vaw_bytes(const stwuct bkey_fowmat *fowmat,
				     const stwuct bkey_packed *k)
{
	wetuwn bkeyp_vaw_u64s(fowmat, k) * sizeof(u64);
}

static inwine void set_bkeyp_vaw_u64s(const stwuct bkey_fowmat *fowmat,
				      stwuct bkey_packed *k, unsigned vaw_u64s)
{
	k->u64s = bkeyp_key_u64s(fowmat, k) + vaw_u64s;
}

#define bkeyp_vaw(_fowmat, _k)						\
	 ((stwuct bch_vaw *) ((u64 *) (_k)->_data + bkeyp_key_u64s(_fowmat, _k)))

extewn const stwuct bkey_fowmat bch2_bkey_fowmat_cuwwent;

boow bch2_bkey_twansfowm(const stwuct bkey_fowmat *,
			 stwuct bkey_packed *,
			 const stwuct bkey_fowmat *,
			 const stwuct bkey_packed *);

stwuct bkey __bch2_bkey_unpack_key(const stwuct bkey_fowmat *,
				   const stwuct bkey_packed *);

#ifndef HAVE_BCACHEFS_COMPIWED_UNPACK
stwuct bpos __bkey_unpack_pos(const stwuct bkey_fowmat *,
			      const stwuct bkey_packed *);
#endif

boow bch2_bkey_pack_key(stwuct bkey_packed *, const stwuct bkey *,
		   const stwuct bkey_fowmat *);

enum bkey_pack_pos_wet {
	BKEY_PACK_POS_EXACT,
	BKEY_PACK_POS_SMAWWEW,
	BKEY_PACK_POS_FAIW,
};

enum bkey_pack_pos_wet bch2_bkey_pack_pos_wossy(stwuct bkey_packed *, stwuct bpos,
					   const stwuct btwee *);

static inwine boow bkey_pack_pos(stwuct bkey_packed *out, stwuct bpos in,
				 const stwuct btwee *b)
{
	wetuwn bch2_bkey_pack_pos_wossy(out, in, b) == BKEY_PACK_POS_EXACT;
}

void bch2_bkey_unpack(const stwuct btwee *, stwuct bkey_i *,
		 const stwuct bkey_packed *);
boow bch2_bkey_pack(stwuct bkey_packed *, const stwuct bkey_i *,
	       const stwuct bkey_fowmat *);

typedef void (*compiwed_unpack_fn)(stwuct bkey *, const stwuct bkey_packed *);

static inwine void
__bkey_unpack_key_fowmat_checked(const stwuct btwee *b,
			       stwuct bkey *dst,
			       const stwuct bkey_packed *swc)
{
	if (IS_ENABWED(HAVE_BCACHEFS_COMPIWED_UNPACK)) {
		compiwed_unpack_fn unpack_fn = b->aux_data;
		unpack_fn(dst, swc);

		if (IS_ENABWED(CONFIG_BCACHEFS_DEBUG) &&
		    bch2_expensive_debug_checks) {
			stwuct bkey dst2 = __bch2_bkey_unpack_key(&b->fowmat, swc);

			BUG_ON(memcmp(dst, &dst2, sizeof(*dst)));
		}
	} ewse {
		*dst = __bch2_bkey_unpack_key(&b->fowmat, swc);
	}
}

static inwine stwuct bkey
bkey_unpack_key_fowmat_checked(const stwuct btwee *b,
			       const stwuct bkey_packed *swc)
{
	stwuct bkey dst;

	__bkey_unpack_key_fowmat_checked(b, &dst, swc);
	wetuwn dst;
}

static inwine void __bkey_unpack_key(const stwuct btwee *b,
				     stwuct bkey *dst,
				     const stwuct bkey_packed *swc)
{
	if (wikewy(bkey_packed(swc)))
		__bkey_unpack_key_fowmat_checked(b, dst, swc);
	ewse
		*dst = *packed_to_bkey_c(swc);
}

/**
 * bkey_unpack_key -- unpack just the key, not the vawue
 */
static inwine stwuct bkey bkey_unpack_key(const stwuct btwee *b,
					  const stwuct bkey_packed *swc)
{
	wetuwn wikewy(bkey_packed(swc))
		? bkey_unpack_key_fowmat_checked(b, swc)
		: *packed_to_bkey_c(swc);
}

static inwine stwuct bpos
bkey_unpack_pos_fowmat_checked(const stwuct btwee *b,
			       const stwuct bkey_packed *swc)
{
#ifdef HAVE_BCACHEFS_COMPIWED_UNPACK
	wetuwn bkey_unpack_key_fowmat_checked(b, swc).p;
#ewse
	wetuwn __bkey_unpack_pos(&b->fowmat, swc);
#endif
}

static inwine stwuct bpos bkey_unpack_pos(const stwuct btwee *b,
					  const stwuct bkey_packed *swc)
{
	wetuwn wikewy(bkey_packed(swc))
		? bkey_unpack_pos_fowmat_checked(b, swc)
		: packed_to_bkey_c(swc)->p;
}

/* Disassembwed bkeys */

static inwine stwuct bkey_s_c bkey_disassembwe(const stwuct btwee *b,
					       const stwuct bkey_packed *k,
					       stwuct bkey *u)
{
	__bkey_unpack_key(b, u, k);

	wetuwn (stwuct bkey_s_c) { u, bkeyp_vaw(&b->fowmat, k), };
}

/* non const vewsion: */
static inwine stwuct bkey_s __bkey_disassembwe(const stwuct btwee *b,
					       stwuct bkey_packed *k,
					       stwuct bkey *u)
{
	__bkey_unpack_key(b, u, k);

	wetuwn (stwuct bkey_s) { .k = u, .v = bkeyp_vaw(&b->fowmat, k), };
}

static inwine u64 bkey_fiewd_max(const stwuct bkey_fowmat *f,
				 enum bch_bkey_fiewds nw)
{
	wetuwn f->bits_pew_fiewd[nw] < 64
		? (we64_to_cpu(f->fiewd_offset[nw]) +
		   ~(~0UWW << f->bits_pew_fiewd[nw]))
		: U64_MAX;
}

#ifdef HAVE_BCACHEFS_COMPIWED_UNPACK

int bch2_compiwe_bkey_fowmat(const stwuct bkey_fowmat *, void *);

#ewse

static inwine int bch2_compiwe_bkey_fowmat(const stwuct bkey_fowmat *fowmat,
					  void *out) { wetuwn 0; }

#endif

static inwine void bkey_weassembwe(stwuct bkey_i *dst,
				   stwuct bkey_s_c swc)
{
	dst->k = *swc.k;
	memcpy_u64s_smaww(&dst->v, swc.v, bkey_vaw_u64s(swc.k));
}

#define bkey_s_nuww		((stwuct bkey_s)   { .k = NUWW })
#define bkey_s_c_nuww		((stwuct bkey_s_c) { .k = NUWW })

#define bkey_s_eww(eww)		((stwuct bkey_s)   { .k = EWW_PTW(eww) })
#define bkey_s_c_eww(eww)	((stwuct bkey_s_c) { .k = EWW_PTW(eww) })

static inwine stwuct bkey_s bkey_to_s(stwuct bkey *k)
{
	wetuwn (stwuct bkey_s) { .k = k, .v = NUWW };
}

static inwine stwuct bkey_s_c bkey_to_s_c(const stwuct bkey *k)
{
	wetuwn (stwuct bkey_s_c) { .k = k, .v = NUWW };
}

static inwine stwuct bkey_s bkey_i_to_s(stwuct bkey_i *k)
{
	wetuwn (stwuct bkey_s) { .k = &k->k, .v = &k->v };
}

static inwine stwuct bkey_s_c bkey_i_to_s_c(const stwuct bkey_i *k)
{
	wetuwn (stwuct bkey_s_c) { .k = &k->k, .v = &k->v };
}

/*
 * Fow a given type of vawue (e.g. stwuct bch_extent), genewates the types fow
 * bkey + bch_extent - inwine, spwit, spwit const - and awso aww the convewsion
 * functions, which awso check that the vawue is of the cowwect type.
 *
 * We use anonymous unions fow upcasting - e.g. convewting fwom e.g. a
 * bkey_i_extent to a bkey_i - since that's awways safe, instead of convewsion
 * functions.
 */
#define x(name, ...)					\
stwuct bkey_i_##name {							\
	union {								\
		stwuct bkey		k;				\
		stwuct bkey_i		k_i;				\
	};								\
	stwuct bch_##name		v;				\
};									\
									\
stwuct bkey_s_c_##name {						\
	union {								\
	stwuct {							\
		const stwuct bkey	*k;				\
		const stwuct bch_##name	*v;				\
	};								\
	stwuct bkey_s_c			s_c;				\
	};								\
};									\
									\
stwuct bkey_s_##name {							\
	union {								\
	stwuct {							\
		stwuct bkey		*k;				\
		stwuct bch_##name	*v;				\
	};								\
	stwuct bkey_s_c_##name		c;				\
	stwuct bkey_s			s;				\
	stwuct bkey_s_c			s_c;				\
	};								\
};									\
									\
static inwine stwuct bkey_i_##name *bkey_i_to_##name(stwuct bkey_i *k)	\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k) && k->k.type != KEY_TYPE_##name);	\
	wetuwn containew_of(&k->k, stwuct bkey_i_##name, k);		\
}									\
									\
static inwine const stwuct bkey_i_##name *				\
bkey_i_to_##name##_c(const stwuct bkey_i *k)				\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k) && k->k.type != KEY_TYPE_##name);	\
	wetuwn containew_of(&k->k, stwuct bkey_i_##name, k);		\
}									\
									\
static inwine stwuct bkey_s_##name bkey_s_to_##name(stwuct bkey_s k)	\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k.k) && k.k->type != KEY_TYPE_##name);	\
	wetuwn (stwuct bkey_s_##name) {					\
		.k = k.k,						\
		.v = containew_of(k.v, stwuct bch_##name, v),		\
	};								\
}									\
									\
static inwine stwuct bkey_s_c_##name bkey_s_c_to_##name(stwuct bkey_s_c k)\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k.k) && k.k->type != KEY_TYPE_##name);	\
	wetuwn (stwuct bkey_s_c_##name) {				\
		.k = k.k,						\
		.v = containew_of(k.v, stwuct bch_##name, v),		\
	};								\
}									\
									\
static inwine stwuct bkey_s_##name name##_i_to_s(stwuct bkey_i_##name *k)\
{									\
	wetuwn (stwuct bkey_s_##name) {					\
		.k = &k->k,						\
		.v = &k->v,						\
	};								\
}									\
									\
static inwine stwuct bkey_s_c_##name					\
name##_i_to_s_c(const stwuct bkey_i_##name *k)				\
{									\
	wetuwn (stwuct bkey_s_c_##name) {				\
		.k = &k->k,						\
		.v = &k->v,						\
	};								\
}									\
									\
static inwine stwuct bkey_s_##name bkey_i_to_s_##name(stwuct bkey_i *k)	\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k) && k->k.type != KEY_TYPE_##name);	\
	wetuwn (stwuct bkey_s_##name) {					\
		.k = &k->k,						\
		.v = containew_of(&k->v, stwuct bch_##name, v),		\
	};								\
}									\
									\
static inwine stwuct bkey_s_c_##name					\
bkey_i_to_s_c_##name(const stwuct bkey_i *k)				\
{									\
	EBUG_ON(!IS_EWW_OW_NUWW(k) && k->k.type != KEY_TYPE_##name);	\
	wetuwn (stwuct bkey_s_c_##name) {				\
		.k = &k->k,						\
		.v = containew_of(&k->v, stwuct bch_##name, v),		\
	};								\
}									\
									\
static inwine stwuct bkey_i_##name *bkey_##name##_init(stwuct bkey_i *_k)\
{									\
	stwuct bkey_i_##name *k =					\
		containew_of(&_k->k, stwuct bkey_i_##name, k);		\
									\
	bkey_init(&k->k);						\
	memset(&k->v, 0, sizeof(k->v));					\
	k->k.type = KEY_TYPE_##name;					\
	set_bkey_vaw_bytes(&k->k, sizeof(k->v));			\
									\
	wetuwn k;							\
}

BCH_BKEY_TYPES();
#undef x

/* byte owdew hewpews */

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__

static inwine unsigned high_wowd_offset(const stwuct bkey_fowmat *f)
{
	wetuwn f->key_u64s - 1;
}

#define high_bit_offset		0
#define nth_wowd(p, n)		((p) - (n))

#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__

static inwine unsigned high_wowd_offset(const stwuct bkey_fowmat *f)
{
	wetuwn 0;
}

#define high_bit_offset		KEY_PACKED_BITS_STAWT
#define nth_wowd(p, n)		((p) + (n))

#ewse
#ewwow edit fow youw odd byteowdew.
#endif

#define high_wowd(f, k)		((u64 *) (k)->_data + high_wowd_offset(f))
#define next_wowd(p)		nth_wowd(p, 1)
#define pwev_wowd(p)		nth_wowd(p, -1)

#ifdef CONFIG_BCACHEFS_DEBUG
void bch2_bkey_pack_test(void);
#ewse
static inwine void bch2_bkey_pack_test(void) {}
#endif

#define bkey_fiewds()							\
	x(BKEY_FIEWD_INODE,		p.inode)			\
	x(BKEY_FIEWD_OFFSET,		p.offset)			\
	x(BKEY_FIEWD_SNAPSHOT,		p.snapshot)			\
	x(BKEY_FIEWD_SIZE,		size)				\
	x(BKEY_FIEWD_VEWSION_HI,	vewsion.hi)			\
	x(BKEY_FIEWD_VEWSION_WO,	vewsion.wo)

stwuct bkey_fowmat_state {
	u64 fiewd_min[BKEY_NW_FIEWDS];
	u64 fiewd_max[BKEY_NW_FIEWDS];
};

void bch2_bkey_fowmat_init(stwuct bkey_fowmat_state *);

static inwine void __bkey_fowmat_add(stwuct bkey_fowmat_state *s, unsigned fiewd, u64 v)
{
	s->fiewd_min[fiewd] = min(s->fiewd_min[fiewd], v);
	s->fiewd_max[fiewd] = max(s->fiewd_max[fiewd], v);
}

/*
 * Changes @fowmat so that @k can be successfuwwy packed with @fowmat
 */
static inwine void bch2_bkey_fowmat_add_key(stwuct bkey_fowmat_state *s, const stwuct bkey *k)
{
#define x(id, fiewd) __bkey_fowmat_add(s, id, k->fiewd);
	bkey_fiewds()
#undef x
}

void bch2_bkey_fowmat_add_pos(stwuct bkey_fowmat_state *, stwuct bpos);
stwuct bkey_fowmat bch2_bkey_fowmat_done(stwuct bkey_fowmat_state *);
int bch2_bkey_fowmat_invawid(stwuct bch_fs *, stwuct bkey_fowmat *,
			     enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_bkey_fowmat_to_text(stwuct pwintbuf *, const stwuct bkey_fowmat *);

#endif /* _BCACHEFS_BKEY_H */
