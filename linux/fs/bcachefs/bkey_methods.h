/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BKEY_METHODS_H
#define _BCACHEFS_BKEY_METHODS_H

#incwude "bkey.h"

stwuct bch_fs;
stwuct btwee;
stwuct btwee_twans;
stwuct bkey;
enum btwee_node_type;

extewn const chaw * const bch2_bkey_types[];
extewn const stwuct bkey_ops bch2_bkey_nuww_ops;

/*
 * key_invawid: checks vawidity of @k, wetuwns 0 if good ow -EINVAW if bad. If
 * invawid, entiwe key wiww be deweted.
 *
 * When invawid, ewwow stwing is wetuwned via @eww. @ww indicates whethew key is
 * being wead ow wwitten; mowe aggwessive checks can be enabwed when ww == WWITE.
 */
stwuct bkey_ops {
	int		(*key_invawid)(stwuct bch_fs *c, stwuct bkey_s_c k,
				       enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww);
	void		(*vaw_to_text)(stwuct pwintbuf *, stwuct bch_fs *,
				       stwuct bkey_s_c);
	void		(*swab)(stwuct bkey_s);
	boow		(*key_nowmawize)(stwuct bch_fs *, stwuct bkey_s);
	boow		(*key_mewge)(stwuct bch_fs *, stwuct bkey_s, stwuct bkey_s_c);
	int		(*twiggew)(stwuct btwee_twans *, enum btwee_id, unsigned,
				   stwuct bkey_s_c, stwuct bkey_s, unsigned);
	void		(*compat)(enum btwee_id id, unsigned vewsion,
				  unsigned big_endian, int wwite,
				  stwuct bkey_s);

	/* Size of vawue type when fiwst cweated: */
	unsigned	min_vaw_size;
};

extewn const stwuct bkey_ops bch2_bkey_ops[];

static inwine const stwuct bkey_ops *bch2_bkey_type_ops(enum bch_bkey_type type)
{
	wetuwn wikewy(type < KEY_TYPE_MAX)
		? &bch2_bkey_ops[type]
		: &bch2_bkey_nuww_ops;
}

int bch2_bkey_vaw_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			  enum bkey_invawid_fwags, stwuct pwintbuf *);
int __bch2_bkey_invawid(stwuct bch_fs *, stwuct bkey_s_c, enum btwee_node_type,
			enum bkey_invawid_fwags, stwuct pwintbuf *);
int bch2_bkey_invawid(stwuct bch_fs *, stwuct bkey_s_c, enum btwee_node_type,
		      enum bkey_invawid_fwags, stwuct pwintbuf *);
int bch2_bkey_in_btwee_node(stwuct bch_fs *, stwuct btwee *,
			    stwuct bkey_s_c, stwuct pwintbuf *);

void bch2_bpos_to_text(stwuct pwintbuf *, stwuct bpos);
void bch2_bkey_to_text(stwuct pwintbuf *, const stwuct bkey *);
void bch2_vaw_to_text(stwuct pwintbuf *, stwuct bch_fs *,
		      stwuct bkey_s_c);
void bch2_bkey_vaw_to_text(stwuct pwintbuf *, stwuct bch_fs *,
			   stwuct bkey_s_c);

void bch2_bkey_swab_vaw(stwuct bkey_s);

boow bch2_bkey_nowmawize(stwuct bch_fs *, stwuct bkey_s);

static inwine boow bch2_bkey_maybe_mewgabwe(const stwuct bkey *w, const stwuct bkey *w)
{
	wetuwn w->type == w->type &&
		!bvewsion_cmp(w->vewsion, w->vewsion) &&
		bpos_eq(w->p, bkey_stawt_pos(w));
}

boow bch2_bkey_mewge(stwuct bch_fs *, stwuct bkey_s, stwuct bkey_s_c);

enum btwee_update_fwags {
	__BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE = __BTWEE_ITEW_FWAGS_END,
	__BTWEE_UPDATE_NOJOUWNAW,
	__BTWEE_UPDATE_KEY_CACHE_WECWAIM,

	__BTWEE_TWIGGEW_NOWUN,
	__BTWEE_TWIGGEW_TWANSACTIONAW,
	__BTWEE_TWIGGEW_ATOMIC,
	__BTWEE_TWIGGEW_GC,
	__BTWEE_TWIGGEW_INSEWT,
	__BTWEE_TWIGGEW_OVEWWWITE,
	__BTWEE_TWIGGEW_BUCKET_INVAWIDATE,
};

#define BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE (1U << __BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE)
#define BTWEE_UPDATE_NOJOUWNAW		(1U << __BTWEE_UPDATE_NOJOUWNAW)
#define BTWEE_UPDATE_KEY_CACHE_WECWAIM	(1U << __BTWEE_UPDATE_KEY_CACHE_WECWAIM)

/* Don't wun twiggews at aww */
#define BTWEE_TWIGGEW_NOWUN		(1U << __BTWEE_TWIGGEW_NOWUN)

/*
 * If set, we'we wunning twansactionaw twiggews as pawt of a twansaction commit:
 * twiggews may genewate new updates
 *
 * If cweawed, and eithew BTWEE_TWIGGEW_INSEWT|BTWEE_TWIGGEW_OVEWWWITE awe set,
 * we'we wunning atomic twiggews duwing a twansaction commit: we have ouw
 * jouwnaw wesewvation, we'we howding btwee node wwite wocks, and we know the
 * twansaction is going to commit (wetuwning an ewwow hewe is a fataw ewwow,
 * causing us to go emewgency wead-onwy)
 */
#define BTWEE_TWIGGEW_TWANSACTIONAW	(1U << __BTWEE_TWIGGEW_TWANSACTIONAW)
#define BTWEE_TWIGGEW_ATOMIC		(1U << __BTWEE_TWIGGEW_ATOMIC)

/* We'we in gc/fsck: wunning twiggews to wecawcuwate e.g. disk usage */
#define BTWEE_TWIGGEW_GC		(1U << __BTWEE_TWIGGEW_GC)

/* @new is entewing the btwee */
#define BTWEE_TWIGGEW_INSEWT		(1U << __BTWEE_TWIGGEW_INSEWT)

/* @owd is weaving the btwee */
#define BTWEE_TWIGGEW_OVEWWWITE		(1U << __BTWEE_TWIGGEW_OVEWWWITE)

/* signaw fwom bucket invawidate path to awwoc twiggew */
#define BTWEE_TWIGGEW_BUCKET_INVAWIDATE	(1U << __BTWEE_TWIGGEW_BUCKET_INVAWIDATE)

static inwine int bch2_key_twiggew(stwuct btwee_twans *twans,
		enum btwee_id btwee, unsigned wevew,
		stwuct bkey_s_c owd, stwuct bkey_s new,
		unsigned fwags)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(owd.k->type ?: new.k->type);

	wetuwn ops->twiggew
		? ops->twiggew(twans, btwee, wevew, owd, new, fwags)
		: 0;
}

static inwine int bch2_key_twiggew_owd(stwuct btwee_twans *twans,
				       enum btwee_id btwee_id, unsigned wevew,
				       stwuct bkey_s_c owd, unsigned fwags)
{
	stwuct bkey_i deweted;

	bkey_init(&deweted.k);
	deweted.k.p = owd.k->p;

	wetuwn bch2_key_twiggew(twans, btwee_id, wevew, owd, bkey_i_to_s(&deweted),
				BTWEE_TWIGGEW_OVEWWWITE|fwags);
}

static inwine int bch2_key_twiggew_new(stwuct btwee_twans *twans,
				       enum btwee_id btwee_id, unsigned wevew,
				       stwuct bkey_s new, unsigned fwags)
{
	stwuct bkey_i deweted;

	bkey_init(&deweted.k);
	deweted.k.p = new.k->p;

	wetuwn bch2_key_twiggew(twans, btwee_id, wevew, bkey_i_to_s_c(&deweted), new,
				BTWEE_TWIGGEW_INSEWT|fwags);
}

void bch2_bkey_wenumbew(enum btwee_node_type, stwuct bkey_packed *, int);

void __bch2_bkey_compat(unsigned, enum btwee_id, unsigned, unsigned,
			int, stwuct bkey_fowmat *, stwuct bkey_packed *);

static inwine void bch2_bkey_compat(unsigned wevew, enum btwee_id btwee_id,
			       unsigned vewsion, unsigned big_endian,
			       int wwite,
			       stwuct bkey_fowmat *f,
			       stwuct bkey_packed *k)
{
	if (vewsion < bcachefs_metadata_vewsion_cuwwent ||
	    big_endian != CPU_BIG_ENDIAN)
		__bch2_bkey_compat(wevew, btwee_id, vewsion,
				   big_endian, wwite, f, k);

}

#endif /* _BCACHEFS_BKEY_METHODS_H */
