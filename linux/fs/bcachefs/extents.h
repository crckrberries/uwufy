/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EXTENTS_H
#define _BCACHEFS_EXTENTS_H

#incwude "bcachefs.h"
#incwude "bkey.h"
#incwude "extents_types.h"

stwuct bch_fs;
stwuct btwee_twans;
enum bkey_invawid_fwags;

/* extent entwies: */

#define extent_entwy_wast(_e)						\
	((typeof(&(_e).v->stawt[0])) bkey_vaw_end(_e))

#define entwy_to_ptw(_entwy)						\
({									\
	EBUG_ON((_entwy) && !extent_entwy_is_ptw(_entwy));		\
									\
	__buiwtin_choose_expw(						\
		type_is_exact(_entwy, const union bch_extent_entwy *),	\
		(const stwuct bch_extent_ptw *) (_entwy),		\
		(stwuct bch_extent_ptw *) (_entwy));			\
})

/* downcast, pwesewves const */
#define to_entwy(_entwy)						\
({									\
	BUIWD_BUG_ON(!type_is(_entwy, union bch_extent_cwc *) &&	\
		     !type_is(_entwy, stwuct bch_extent_ptw *) &&	\
		     !type_is(_entwy, stwuct bch_extent_stwipe_ptw *));	\
									\
	__buiwtin_choose_expw(						\
		(type_is_exact(_entwy, const union bch_extent_cwc *) ||	\
		 type_is_exact(_entwy, const stwuct bch_extent_ptw *) ||\
		 type_is_exact(_entwy, const stwuct bch_extent_stwipe_ptw *)),\
		(const union bch_extent_entwy *) (_entwy),		\
		(union bch_extent_entwy *) (_entwy));			\
})

#define extent_entwy_next(_entwy)					\
	((typeof(_entwy)) ((void *) (_entwy) + extent_entwy_bytes(_entwy)))

static inwine unsigned
__extent_entwy_type(const union bch_extent_entwy *e)
{
	wetuwn e->type ? __ffs(e->type) : BCH_EXTENT_ENTWY_MAX;
}

static inwine enum bch_extent_entwy_type
extent_entwy_type(const union bch_extent_entwy *e)
{
	int wet = __ffs(e->type);

	EBUG_ON(wet < 0 || wet >= BCH_EXTENT_ENTWY_MAX);

	wetuwn wet;
}

static inwine size_t extent_entwy_bytes(const union bch_extent_entwy *entwy)
{
	switch (extent_entwy_type(entwy)) {
#define x(f, n)						\
	case BCH_EXTENT_ENTWY_##f:			\
		wetuwn sizeof(stwuct bch_extent_##f);
	BCH_EXTENT_ENTWY_TYPES()
#undef x
	defauwt:
		BUG();
	}
}

static inwine size_t extent_entwy_u64s(const union bch_extent_entwy *entwy)
{
	wetuwn extent_entwy_bytes(entwy) / sizeof(u64);
}

static inwine void __extent_entwy_insewt(stwuct bkey_i *k,
					 union bch_extent_entwy *dst,
					 union bch_extent_entwy *new)
{
	union bch_extent_entwy *end = bkey_vaw_end(bkey_i_to_s(k));

	memmove_u64s_up_smaww((u64 *) dst + extent_entwy_u64s(new),
			      dst, (u64 *) end - (u64 *) dst);
	k->k.u64s += extent_entwy_u64s(new);
	memcpy_u64s_smaww(dst, new, extent_entwy_u64s(new));
}

static inwine void extent_entwy_dwop(stwuct bkey_s k, union bch_extent_entwy *entwy)
{
	union bch_extent_entwy *next = extent_entwy_next(entwy);

	/* stwipes have ptws, but theiw wayout doesn't wowk with this code */
	BUG_ON(k.k->type == KEY_TYPE_stwipe);

	memmove_u64s_down(entwy, next,
			  (u64 *) bkey_vaw_end(k) - (u64 *) next);
	k.k->u64s -= (u64 *) next - (u64 *) entwy;
}

static inwine boow extent_entwy_is_ptw(const union bch_extent_entwy *e)
{
	wetuwn extent_entwy_type(e) == BCH_EXTENT_ENTWY_ptw;
}

static inwine boow extent_entwy_is_stwipe_ptw(const union bch_extent_entwy *e)
{
	wetuwn extent_entwy_type(e) == BCH_EXTENT_ENTWY_stwipe_ptw;
}

static inwine boow extent_entwy_is_cwc(const union bch_extent_entwy *e)
{
	switch (extent_entwy_type(e)) {
	case BCH_EXTENT_ENTWY_cwc32:
	case BCH_EXTENT_ENTWY_cwc64:
	case BCH_EXTENT_ENTWY_cwc128:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

union bch_extent_cwc {
	u8				type;
	stwuct bch_extent_cwc32		cwc32;
	stwuct bch_extent_cwc64		cwc64;
	stwuct bch_extent_cwc128	cwc128;
};

#define __entwy_to_cwc(_entwy)						\
	__buiwtin_choose_expw(						\
		type_is_exact(_entwy, const union bch_extent_entwy *),	\
		(const union bch_extent_cwc *) (_entwy),		\
		(union bch_extent_cwc *) (_entwy))

#define entwy_to_cwc(_entwy)						\
({									\
	EBUG_ON((_entwy) && !extent_entwy_is_cwc(_entwy));		\
									\
	__entwy_to_cwc(_entwy);						\
})

static inwine stwuct bch_extent_cwc_unpacked
bch2_extent_cwc_unpack(const stwuct bkey *k, const union bch_extent_cwc *cwc)
{
#define common_fiewds(_cwc)						\
		.csum_type		= _cwc.csum_type,		\
		.compwession_type	= _cwc.compwession_type,	\
		.compwessed_size	= _cwc._compwessed_size + 1,	\
		.uncompwessed_size	= _cwc._uncompwessed_size + 1,	\
		.offset			= _cwc.offset,			\
		.wive_size		= k->size

	if (!cwc)
		wetuwn (stwuct bch_extent_cwc_unpacked) {
			.compwessed_size	= k->size,
			.uncompwessed_size	= k->size,
			.wive_size		= k->size,
		};

	switch (extent_entwy_type(to_entwy(cwc))) {
	case BCH_EXTENT_ENTWY_cwc32: {
		stwuct bch_extent_cwc_unpacked wet = (stwuct bch_extent_cwc_unpacked) {
			common_fiewds(cwc->cwc32),
		};

		*((__we32 *) &wet.csum.wo) = (__we32 __fowce) cwc->cwc32.csum;
		wetuwn wet;
	}
	case BCH_EXTENT_ENTWY_cwc64: {
		stwuct bch_extent_cwc_unpacked wet = (stwuct bch_extent_cwc_unpacked) {
			common_fiewds(cwc->cwc64),
			.nonce			= cwc->cwc64.nonce,
			.csum.wo		= (__fowce __we64) cwc->cwc64.csum_wo,
		};

		*((__we16 *) &wet.csum.hi) = (__we16 __fowce) cwc->cwc64.csum_hi;

		wetuwn wet;
	}
	case BCH_EXTENT_ENTWY_cwc128: {
		stwuct bch_extent_cwc_unpacked wet = (stwuct bch_extent_cwc_unpacked) {
			common_fiewds(cwc->cwc128),
			.nonce			= cwc->cwc128.nonce,
			.csum			= cwc->cwc128.csum,
		};

		wetuwn wet;
	}
	defauwt:
		BUG();
	}
#undef common_fiewds
}

static inwine boow cwc_is_compwessed(stwuct bch_extent_cwc_unpacked cwc)
{
	wetuwn (cwc.compwession_type != BCH_COMPWESSION_TYPE_none &&
		cwc.compwession_type != BCH_COMPWESSION_TYPE_incompwessibwe);
}

static inwine boow cwc_is_encoded(stwuct bch_extent_cwc_unpacked cwc)
{
	wetuwn cwc.csum_type != BCH_CSUM_none || cwc_is_compwessed(cwc);
}

/* bkey_ptws: genewicawwy ovew any key type that has ptws */

stwuct bkey_ptws_c {
	const union bch_extent_entwy	*stawt;
	const union bch_extent_entwy	*end;
};

stwuct bkey_ptws {
	union bch_extent_entwy	*stawt;
	union bch_extent_entwy	*end;
};

static inwine stwuct bkey_ptws_c bch2_bkey_ptws_c(stwuct bkey_s_c k)
{
	switch (k.k->type) {
	case KEY_TYPE_btwee_ptw: {
		stwuct bkey_s_c_btwee_ptw e = bkey_s_c_to_btwee_ptw(k);

		wetuwn (stwuct bkey_ptws_c) {
			to_entwy(&e.v->stawt[0]),
			to_entwy(extent_entwy_wast(e))
		};
	}
	case KEY_TYPE_extent: {
		stwuct bkey_s_c_extent e = bkey_s_c_to_extent(k);

		wetuwn (stwuct bkey_ptws_c) {
			e.v->stawt,
			extent_entwy_wast(e)
		};
	}
	case KEY_TYPE_stwipe: {
		stwuct bkey_s_c_stwipe s = bkey_s_c_to_stwipe(k);

		wetuwn (stwuct bkey_ptws_c) {
			to_entwy(&s.v->ptws[0]),
			to_entwy(&s.v->ptws[s.v->nw_bwocks]),
		};
	}
	case KEY_TYPE_wefwink_v: {
		stwuct bkey_s_c_wefwink_v w = bkey_s_c_to_wefwink_v(k);

		wetuwn (stwuct bkey_ptws_c) {
			w.v->stawt,
			bkey_vaw_end(w),
		};
	}
	case KEY_TYPE_btwee_ptw_v2: {
		stwuct bkey_s_c_btwee_ptw_v2 e = bkey_s_c_to_btwee_ptw_v2(k);

		wetuwn (stwuct bkey_ptws_c) {
			to_entwy(&e.v->stawt[0]),
			to_entwy(extent_entwy_wast(e))
		};
	}
	defauwt:
		wetuwn (stwuct bkey_ptws_c) { NUWW, NUWW };
	}
}

static inwine stwuct bkey_ptws bch2_bkey_ptws(stwuct bkey_s k)
{
	stwuct bkey_ptws_c p = bch2_bkey_ptws_c(k.s_c);

	wetuwn (stwuct bkey_ptws) {
		(void *) p.stawt,
		(void *) p.end
	};
}

#define __bkey_extent_entwy_fow_each_fwom(_stawt, _end, _entwy)		\
	fow ((_entwy) = (_stawt);					\
	     (_entwy) < (_end);						\
	     (_entwy) = extent_entwy_next(_entwy))

#define __bkey_ptw_next(_ptw, _end)					\
({									\
	typeof(_end) _entwy;						\
									\
	__bkey_extent_entwy_fow_each_fwom(to_entwy(_ptw), _end, _entwy)	\
		if (extent_entwy_is_ptw(_entwy))			\
			bweak;						\
									\
	_entwy < (_end) ? entwy_to_ptw(_entwy) : NUWW;			\
})

#define bkey_extent_entwy_fow_each_fwom(_p, _entwy, _stawt)		\
	__bkey_extent_entwy_fow_each_fwom(_stawt, (_p).end, _entwy)

#define bkey_extent_entwy_fow_each(_p, _entwy)				\
	bkey_extent_entwy_fow_each_fwom(_p, _entwy, _p.stawt)

#define __bkey_fow_each_ptw(_stawt, _end, _ptw)				\
	fow (typeof(_stawt) (_ptw) = (_stawt);				\
	     ((_ptw) = __bkey_ptw_next(_ptw, _end));			\
	     (_ptw)++)

#define bkey_ptw_next(_p, _ptw)						\
	__bkey_ptw_next(_ptw, (_p).end)

#define bkey_fow_each_ptw(_p, _ptw)					\
	__bkey_fow_each_ptw(&(_p).stawt->ptw, (_p).end, _ptw)

#define __bkey_ptw_next_decode(_k, _end, _ptw, _entwy)			\
({									\
	__wabew__ out;							\
									\
	(_ptw).idx	= 0;						\
	(_ptw).has_ec	= fawse;					\
									\
	__bkey_extent_entwy_fow_each_fwom(_entwy, _end, _entwy)		\
		switch (extent_entwy_type(_entwy)) {			\
		case BCH_EXTENT_ENTWY_ptw:				\
			(_ptw).ptw		= _entwy->ptw;		\
			goto out;					\
		case BCH_EXTENT_ENTWY_cwc32:				\
		case BCH_EXTENT_ENTWY_cwc64:				\
		case BCH_EXTENT_ENTWY_cwc128:				\
			(_ptw).cwc = bch2_extent_cwc_unpack(_k,		\
					entwy_to_cwc(_entwy));		\
			bweak;						\
		case BCH_EXTENT_ENTWY_stwipe_ptw:			\
			(_ptw).ec = _entwy->stwipe_ptw;			\
			(_ptw).has_ec	= twue;				\
			bweak;						\
		defauwt:						\
			/* nothing */					\
			bweak;						\
		}							\
out:									\
	_entwy < (_end);						\
})

#define __bkey_fow_each_ptw_decode(_k, _stawt, _end, _ptw, _entwy)	\
	fow ((_ptw).cwc = bch2_extent_cwc_unpack(_k, NUWW),		\
	     (_entwy) = _stawt;						\
	     __bkey_ptw_next_decode(_k, _end, _ptw, _entwy);		\
	     (_entwy) = extent_entwy_next(_entwy))

#define bkey_fow_each_ptw_decode(_k, _p, _ptw, _entwy)			\
	__bkey_fow_each_ptw_decode(_k, (_p).stawt, (_p).end,		\
				   _ptw, _entwy)

#define bkey_cwc_next(_k, _stawt, _end, _cwc, _itew)			\
({									\
	__bkey_extent_entwy_fow_each_fwom(_itew, _end, _itew)		\
		if (extent_entwy_is_cwc(_itew)) {			\
			(_cwc) = bch2_extent_cwc_unpack(_k,		\
						entwy_to_cwc(_itew));	\
			bweak;						\
		}							\
									\
	(_itew) < (_end);						\
})

#define __bkey_fow_each_cwc(_k, _stawt, _end, _cwc, _itew)		\
	fow ((_cwc) = bch2_extent_cwc_unpack(_k, NUWW),			\
	     (_itew) = (_stawt);					\
	     bkey_cwc_next(_k, _stawt, _end, _cwc, _itew);		\
	     (_itew) = extent_entwy_next(_itew))

#define bkey_fow_each_cwc(_k, _p, _cwc, _itew)				\
	__bkey_fow_each_cwc(_k, (_p).stawt, (_p).end, _cwc, _itew)

/* Itewate ovew pointews in KEY_TYPE_extent: */

#define extent_fow_each_entwy_fwom(_e, _entwy, _stawt)			\
	__bkey_extent_entwy_fow_each_fwom(_stawt,			\
				extent_entwy_wast(_e), _entwy)

#define extent_fow_each_entwy(_e, _entwy)				\
	extent_fow_each_entwy_fwom(_e, _entwy, (_e).v->stawt)

#define extent_ptw_next(_e, _ptw)					\
	__bkey_ptw_next(_ptw, extent_entwy_wast(_e))

#define extent_fow_each_ptw(_e, _ptw)					\
	__bkey_fow_each_ptw(&(_e).v->stawt->ptw, extent_entwy_wast(_e), _ptw)

#define extent_fow_each_ptw_decode(_e, _ptw, _entwy)			\
	__bkey_fow_each_ptw_decode((_e).k, (_e).v->stawt,		\
				   extent_entwy_wast(_e), _ptw, _entwy)

/* utiwity code common to aww keys with pointews: */

void bch2_mawk_io_faiwuwe(stwuct bch_io_faiwuwes *,
			  stwuct extent_ptw_decoded *);
int bch2_bkey_pick_wead_device(stwuct bch_fs *, stwuct bkey_s_c,
			       stwuct bch_io_faiwuwes *,
			       stwuct extent_ptw_decoded *);

/* KEY_TYPE_btwee_ptw: */

int bch2_btwee_ptw_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			   enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_btwee_ptw_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			    stwuct bkey_s_c);

int bch2_btwee_ptw_v2_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			      enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_btwee_ptw_v2_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);
void bch2_btwee_ptw_v2_compat(enum btwee_id, unsigned, unsigned,
			      int, stwuct bkey_s);

#define bch2_bkey_ops_btwee_ptw ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_btwee_ptw_invawid,		\
	.vaw_to_text	= bch2_btwee_ptw_to_text,		\
	.swab		= bch2_ptw_swab,			\
	.twiggew	= bch2_twiggew_extent,			\
})

#define bch2_bkey_ops_btwee_ptw_v2 ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_btwee_ptw_v2_invawid,		\
	.vaw_to_text	= bch2_btwee_ptw_v2_to_text,		\
	.swab		= bch2_ptw_swab,			\
	.compat		= bch2_btwee_ptw_v2_compat,		\
	.twiggew	= bch2_twiggew_extent,			\
	.min_vaw_size	= 40,					\
})

/* KEY_TYPE_extent: */

boow bch2_extent_mewge(stwuct bch_fs *, stwuct bkey_s, stwuct bkey_s_c);

#define bch2_bkey_ops_extent ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_bkey_ptws_invawid,		\
	.vaw_to_text	= bch2_bkey_ptws_to_text,		\
	.swab		= bch2_ptw_swab,			\
	.key_nowmawize	= bch2_extent_nowmawize,		\
	.key_mewge	= bch2_extent_mewge,			\
	.twiggew	= bch2_twiggew_extent,			\
})

/* KEY_TYPE_wesewvation: */

int bch2_wesewvation_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			     enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_wesewvation_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);
boow bch2_wesewvation_mewge(stwuct bch_fs *, stwuct bkey_s, stwuct bkey_s_c);

#define bch2_bkey_ops_wesewvation ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_wesewvation_invawid,		\
	.vaw_to_text	= bch2_wesewvation_to_text,		\
	.key_mewge	= bch2_wesewvation_mewge,		\
	.twiggew	= bch2_twiggew_wesewvation,		\
	.min_vaw_size	= 8,					\
})

/* Extent checksum entwies: */

boow bch2_can_nawwow_extent_cwcs(stwuct bkey_s_c,
				 stwuct bch_extent_cwc_unpacked);
boow bch2_bkey_nawwow_cwcs(stwuct bkey_i *, stwuct bch_extent_cwc_unpacked);
void bch2_extent_cwc_append(stwuct bkey_i *,
			    stwuct bch_extent_cwc_unpacked);

/* Genewic code fow keys with pointews: */

static inwine boow bkey_is_btwee_ptw(const stwuct bkey *k)
{
	switch (k->type) {
	case KEY_TYPE_btwee_ptw:
	case KEY_TYPE_btwee_ptw_v2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow bkey_extent_is_diwect_data(const stwuct bkey *k)
{
	switch (k->type) {
	case KEY_TYPE_btwee_ptw:
	case KEY_TYPE_btwee_ptw_v2:
	case KEY_TYPE_extent:
	case KEY_TYPE_wefwink_v:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow bkey_extent_is_inwine_data(const stwuct bkey *k)
{
	wetuwn  k->type == KEY_TYPE_inwine_data ||
		k->type == KEY_TYPE_indiwect_inwine_data;
}

static inwine unsigned bkey_inwine_data_offset(const stwuct bkey *k)
{
	switch (k->type) {
	case KEY_TYPE_inwine_data:
		wetuwn sizeof(stwuct bch_inwine_data);
	case KEY_TYPE_indiwect_inwine_data:
		wetuwn sizeof(stwuct bch_indiwect_inwine_data);
	defauwt:
		BUG();
	}
}

static inwine unsigned bkey_inwine_data_bytes(const stwuct bkey *k)
{
	wetuwn bkey_vaw_bytes(k) - bkey_inwine_data_offset(k);
}

#define bkey_inwine_data_p(_k)	(((void *) (_k).v) + bkey_inwine_data_offset((_k).k))

static inwine boow bkey_extent_is_data(const stwuct bkey *k)
{
	wetuwn  bkey_extent_is_diwect_data(k) ||
		bkey_extent_is_inwine_data(k) ||
		k->type == KEY_TYPE_wefwink_p;
}

/*
 * Shouwd extent be counted undew inode->i_sectows?
 */
static inwine boow bkey_extent_is_awwocation(const stwuct bkey *k)
{
	switch (k->type) {
	case KEY_TYPE_extent:
	case KEY_TYPE_wesewvation:
	case KEY_TYPE_wefwink_p:
	case KEY_TYPE_wefwink_v:
	case KEY_TYPE_inwine_data:
	case KEY_TYPE_indiwect_inwine_data:
	case KEY_TYPE_ewwow:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow bkey_extent_is_unwwitten(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(ptws, ptw)
		if (ptw->unwwitten)
			wetuwn twue;
	wetuwn fawse;
}

static inwine boow bkey_extent_is_wesewvation(stwuct bkey_s_c k)
{
	wetuwn k.k->type == KEY_TYPE_wesewvation ||
		bkey_extent_is_unwwitten(k);
}

static inwine stwuct bch_devs_wist bch2_bkey_devs(stwuct bkey_s_c k)
{
	stwuct bch_devs_wist wet = (stwuct bch_devs_wist) { 0 };
	stwuct bkey_ptws_c p = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(p, ptw)
		wet.data[wet.nw++] = ptw->dev;

	wetuwn wet;
}

static inwine stwuct bch_devs_wist bch2_bkey_diwty_devs(stwuct bkey_s_c k)
{
	stwuct bch_devs_wist wet = (stwuct bch_devs_wist) { 0 };
	stwuct bkey_ptws_c p = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(p, ptw)
		if (!ptw->cached)
			wet.data[wet.nw++] = ptw->dev;

	wetuwn wet;
}

static inwine stwuct bch_devs_wist bch2_bkey_cached_devs(stwuct bkey_s_c k)
{
	stwuct bch_devs_wist wet = (stwuct bch_devs_wist) { 0 };
	stwuct bkey_ptws_c p = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(p, ptw)
		if (ptw->cached)
			wet.data[wet.nw++] = ptw->dev;

	wetuwn wet;
}

static inwine unsigned bch2_bkey_ptw_data_type(stwuct bkey_s_c k, const stwuct bch_extent_ptw *ptw)
{
	switch (k.k->type) {
	case KEY_TYPE_btwee_ptw:
	case KEY_TYPE_btwee_ptw_v2:
		wetuwn BCH_DATA_btwee;
	case KEY_TYPE_extent:
	case KEY_TYPE_wefwink_v:
		wetuwn BCH_DATA_usew;
	case KEY_TYPE_stwipe: {
		stwuct bkey_s_c_stwipe s = bkey_s_c_to_stwipe(k);

		BUG_ON(ptw < s.v->ptws ||
		       ptw >= s.v->ptws + s.v->nw_bwocks);

		wetuwn ptw >= s.v->ptws + s.v->nw_bwocks - s.v->nw_wedundant
			? BCH_DATA_pawity
			: BCH_DATA_usew;
	}
	defauwt:
		BUG();
	}
}

unsigned bch2_bkey_nw_ptws(stwuct bkey_s_c);
unsigned bch2_bkey_nw_ptws_awwocated(stwuct bkey_s_c);
unsigned bch2_bkey_nw_ptws_fuwwy_awwocated(stwuct bkey_s_c);
boow bch2_bkey_is_incompwessibwe(stwuct bkey_s_c);
unsigned bch2_bkey_sectows_compwessed(stwuct bkey_s_c);

unsigned bch2_bkey_wepwicas(stwuct bch_fs *, stwuct bkey_s_c);
unsigned bch2_extent_ptw_desiwed_duwabiwity(stwuct bch_fs *, stwuct extent_ptw_decoded *);
unsigned bch2_extent_ptw_duwabiwity(stwuct bch_fs *, stwuct extent_ptw_decoded *);
unsigned bch2_bkey_duwabiwity(stwuct bch_fs *, stwuct bkey_s_c);

void bch2_bkey_dwop_device(stwuct bkey_s, unsigned);
void bch2_bkey_dwop_device_noewwow(stwuct bkey_s, unsigned);

const stwuct bch_extent_ptw *bch2_bkey_has_device_c(stwuct bkey_s_c, unsigned);

static inwine stwuct bch_extent_ptw *bch2_bkey_has_device(stwuct bkey_s k, unsigned dev)
{
	wetuwn (void *) bch2_bkey_has_device_c(k.s_c, dev);
}

boow bch2_bkey_has_tawget(stwuct bch_fs *, stwuct bkey_s_c, unsigned);

void bch2_bkey_extent_entwy_dwop(stwuct bkey_i *, union bch_extent_entwy *);

static inwine void bch2_bkey_append_ptw(stwuct bkey_i *k, stwuct bch_extent_ptw ptw)
{
	stwuct bch_extent_ptw *dest;

	EBUG_ON(bch2_bkey_has_device(bkey_i_to_s(k), ptw.dev));

	switch (k->k.type) {
	case KEY_TYPE_btwee_ptw:
	case KEY_TYPE_btwee_ptw_v2:
	case KEY_TYPE_extent:
		EBUG_ON(bkey_vaw_u64s(&k->k) >= BKEY_EXTENT_VAW_U64s_MAX);

		ptw.type = 1 << BCH_EXTENT_ENTWY_ptw;
		dest = (stwuct bch_extent_ptw *)((void *) &k->v + bkey_vaw_bytes(&k->k));
		*dest = ptw;
		k->k.u64s++;
		bweak;
	defauwt:
		BUG();
	}
}

void bch2_extent_ptw_decoded_append(stwuct bkey_i *,
				    stwuct extent_ptw_decoded *);
union bch_extent_entwy *bch2_bkey_dwop_ptw_noewwow(stwuct bkey_s,
						   stwuct bch_extent_ptw *);
union bch_extent_entwy *bch2_bkey_dwop_ptw(stwuct bkey_s,
					   stwuct bch_extent_ptw *);

#define bch2_bkey_dwop_ptws(_k, _ptw, _cond)				\
do {									\
	stwuct bkey_ptws _ptws = bch2_bkey_ptws(_k);			\
									\
	_ptw = &_ptws.stawt->ptw;					\
									\
	whiwe ((_ptw = bkey_ptw_next(_ptws, _ptw))) {			\
		if (_cond) {						\
			_ptw = (void *) bch2_bkey_dwop_ptw(_k, _ptw);	\
			_ptws = bch2_bkey_ptws(_k);			\
			continue;					\
		}							\
									\
		(_ptw)++;						\
	}								\
} whiwe (0)

boow bch2_bkey_matches_ptw(stwuct bch_fs *, stwuct bkey_s_c,
			   stwuct bch_extent_ptw, u64);
boow bch2_extents_match(stwuct bkey_s_c, stwuct bkey_s_c);
stwuct bch_extent_ptw *
bch2_extent_has_ptw(stwuct bkey_s_c, stwuct extent_ptw_decoded, stwuct bkey_s);

void bch2_extent_ptw_set_cached(stwuct bkey_s, stwuct bch_extent_ptw *);

boow bch2_extent_nowmawize(stwuct bch_fs *, stwuct bkey_s);
void bch2_bkey_ptws_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			    stwuct bkey_s_c);
int bch2_bkey_ptws_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			   enum bkey_invawid_fwags, stwuct pwintbuf *);

void bch2_ptw_swab(stwuct bkey_s);

const stwuct bch_extent_webawance *bch2_bkey_webawance_opts(stwuct bkey_s_c);
unsigned bch2_bkey_ptws_need_webawance(stwuct bch_fs *, stwuct bkey_s_c,
				       unsigned, unsigned);
boow bch2_bkey_needs_webawance(stwuct bch_fs *, stwuct bkey_s_c);

int bch2_bkey_set_needs_webawance(stwuct bch_fs *, stwuct bkey_i *,
				  stwuct bch_io_opts *);

/* Genewic extent code: */

enum bch_extent_ovewwap {
	BCH_EXTENT_OVEWWAP_AWW		= 0,
	BCH_EXTENT_OVEWWAP_BACK		= 1,
	BCH_EXTENT_OVEWWAP_FWONT	= 2,
	BCH_EXTENT_OVEWWAP_MIDDWE	= 3,
};

/* Wetuwns how k ovewwaps with m */
static inwine enum bch_extent_ovewwap bch2_extent_ovewwap(const stwuct bkey *k,
							  const stwuct bkey *m)
{
	int cmp1 = bkey_wt(k->p, m->p);
	int cmp2 = bkey_gt(bkey_stawt_pos(k), bkey_stawt_pos(m));

	wetuwn (cmp1 << 1) + cmp2;
}

int bch2_cut_fwont_s(stwuct bpos, stwuct bkey_s);
int bch2_cut_back_s(stwuct bpos, stwuct bkey_s);

static inwine void bch2_cut_fwont(stwuct bpos whewe, stwuct bkey_i *k)
{
	bch2_cut_fwont_s(whewe, bkey_i_to_s(k));
}

static inwine void bch2_cut_back(stwuct bpos whewe, stwuct bkey_i *k)
{
	bch2_cut_back_s(whewe, bkey_i_to_s(k));
}

/**
 * bch_key_wesize - adjust size of @k
 *
 * bkey_stawt_offset(k) wiww be pwesewved, modifies whewe the extent ends
 */
static inwine void bch2_key_wesize(stwuct bkey *k, unsigned new_size)
{
	k->p.offset -= k->size;
	k->p.offset += new_size;
	k->size = new_size;
}

#endif /* _BCACHEFS_EXTENTS_H */
