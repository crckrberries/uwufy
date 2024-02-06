/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bcachefs

#if !defined(_TWACE_BCACHEFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BCACHEFS_H

#incwude <winux/twacepoint.h>

#define TWACE_BPOS_entwies(name)				\
	__fiewd(u64,			name##_inode	)	\
	__fiewd(u64,			name##_offset	)	\
	__fiewd(u32,			name##_snapshot	)

#define TWACE_BPOS_assign(dst, swc)				\
	__entwy->dst##_inode		= (swc).inode;		\
	__entwy->dst##_offset		= (swc).offset;		\
	__entwy->dst##_snapshot		= (swc).snapshot

DECWAWE_EVENT_CWASS(bpos,
	TP_PWOTO(const stwuct bpos *p),
	TP_AWGS(p),

	TP_STWUCT__entwy(
		TWACE_BPOS_entwies(p)
	),

	TP_fast_assign(
		TWACE_BPOS_assign(p, *p);
	),

	TP_pwintk("%wwu:%wwu:%u", __entwy->p_inode, __entwy->p_offset, __entwy->p_snapshot)
);

DECWAWE_EVENT_CWASS(fs_stw,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__stwing(stw,		stw			)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__assign_stw(stw, stw);
	),

	TP_pwintk("%d,%d\n%s", MAJOW(__entwy->dev), MINOW(__entwy->dev), __get_stw(stw))
);

DECWAWE_EVENT_CWASS(twans_stw,
	TP_PWOTO(stwuct btwee_twans *twans, unsigned wong cawwew_ip, const chaw *stw),
	TP_AWGS(twans, cawwew_ip, stw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__awway(chaw,		twans_fn, 32		)
		__fiewd(unsigned wong,	cawwew_ip		)
		__stwing(stw,		stw			)
	),

	TP_fast_assign(
		__entwy->dev		= twans->c->dev;
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__assign_stw(stw, stw);
	),

	TP_pwintk("%d,%d %s %pS %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->twans_fn, (void *) __entwy->cawwew_ip, __get_stw(stw))
);

DECWAWE_EVENT_CWASS(twans_stw_nocawwew,
	TP_PWOTO(stwuct btwee_twans *twans, const chaw *stw),
	TP_AWGS(twans, stw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__awway(chaw,		twans_fn, 32		)
		__stwing(stw,		stw			)
	),

	TP_fast_assign(
		__entwy->dev		= twans->c->dev;
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__assign_stw(stw, stw);
	),

	TP_pwintk("%d,%d %s %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->twans_fn, __get_stw(stw))
);

DECWAWE_EVENT_CWASS(btwee_node_nofs,
	TP_PWOTO(stwuct bch_fs *c, stwuct btwee *b),
	TP_AWGS(c, b),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u8,		wevew			)
		__fiewd(u8,		btwee_id		)
		TWACE_BPOS_entwies(pos)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->wevew		= b->c.wevew;
		__entwy->btwee_id	= b->c.btwee_id;
		TWACE_BPOS_assign(pos, b->key.k.p);
	),

	TP_pwintk("%d,%d %u %s %wwu:%wwu:%u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wevew,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode, __entwy->pos_offset, __entwy->pos_snapshot)
);

DECWAWE_EVENT_CWASS(btwee_node,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__awway(chaw,		twans_fn, 32		)
		__fiewd(u8,		wevew			)
		__fiewd(u8,		btwee_id		)
		TWACE_BPOS_entwies(pos)
	),

	TP_fast_assign(
		__entwy->dev		= twans->c->dev;
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->wevew		= b->c.wevew;
		__entwy->btwee_id	= b->c.btwee_id;
		TWACE_BPOS_assign(pos, b->key.k.p);
	),

	TP_pwintk("%d,%d %s %u %s %wwu:%wwu:%u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->twans_fn,
		  __entwy->wevew,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode, __entwy->pos_offset, __entwy->pos_snapshot)
);

DECWAWE_EVENT_CWASS(bch_fs,
	TP_PWOTO(stwuct bch_fs *c),
	TP_AWGS(c),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
	),

	TP_pwintk("%d,%d", MAJOW(__entwy->dev), MINOW(__entwy->dev))
);

DECWAWE_EVENT_CWASS(btwee_twans,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__awway(chaw,		twans_fn, 32		)
	),

	TP_fast_assign(
		__entwy->dev		= twans->c->dev;
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
	),

	TP_pwintk("%d,%d %s", MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->twans_fn)
);

DECWAWE_EVENT_CWASS(bio,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(sectow_t,	sectow			)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
	),

	TP_fast_assign(
		__entwy->dev		= bio->bi_bdev ? bio_dev(bio) : 0;
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d  %s %wwu + %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow, __entwy->nw_sectow)
);

/* supew-io.c: */
TWACE_EVENT(wwite_supew,
	TP_PWOTO(stwuct bch_fs *c, unsigned wong ip),
	TP_AWGS(c, ip),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev	)
		__fiewd(unsigned wong,	ip	)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->ip		= ip;
	),

	TP_pwintk("%d,%d fow %pS",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (void *) __entwy->ip)
);

/* io.c: */

DEFINE_EVENT(bio, wead_pwomote,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

TWACE_EVENT(wead_nopwomote,
	TP_PWOTO(stwuct bch_fs *c, int wet),
	TP_AWGS(c, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev		)
		__awway(chaw,		wet, 32		)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		stwscpy(__entwy->wet, bch2_eww_stw(wet), sizeof(__entwy->wet));
	),

	TP_pwintk("%d,%d wet %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wet)
);

DEFINE_EVENT(bio, wead_bounce,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

DEFINE_EVENT(bio, wead_spwit,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

DEFINE_EVENT(bio, wead_wetwy,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

DEFINE_EVENT(bio, wead_weuse_wace,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

/* Jouwnaw */

DEFINE_EVENT(bch_fs, jouwnaw_fuww,
	TP_PWOTO(stwuct bch_fs *c),
	TP_AWGS(c)
);

DEFINE_EVENT(fs_stw, jouwnaw_entwy_fuww,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, jouwnaw_entwy_cwose,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(bio, jouwnaw_wwite,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

TWACE_EVENT(jouwnaw_wecwaim_stawt,
	TP_PWOTO(stwuct bch_fs *c, boow diwect, boow kicked,
		 u64 min_nw, u64 min_key_cache,
		 u64 btwee_cache_diwty, u64 btwee_cache_totaw,
		 u64 btwee_key_cache_diwty, u64 btwee_key_cache_totaw),
	TP_AWGS(c, diwect, kicked, min_nw, min_key_cache,
		btwee_cache_diwty, btwee_cache_totaw,
		btwee_key_cache_diwty, btwee_key_cache_totaw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(boow,		diwect			)
		__fiewd(boow,		kicked			)
		__fiewd(u64,		min_nw			)
		__fiewd(u64,		min_key_cache		)
		__fiewd(u64,		btwee_cache_diwty	)
		__fiewd(u64,		btwee_cache_totaw	)
		__fiewd(u64,		btwee_key_cache_diwty	)
		__fiewd(u64,		btwee_key_cache_totaw	)
	),

	TP_fast_assign(
		__entwy->dev			= c->dev;
		__entwy->diwect			= diwect;
		__entwy->kicked			= kicked;
		__entwy->min_nw			= min_nw;
		__entwy->min_key_cache		= min_key_cache;
		__entwy->btwee_cache_diwty	= btwee_cache_diwty;
		__entwy->btwee_cache_totaw	= btwee_cache_totaw;
		__entwy->btwee_key_cache_diwty	= btwee_key_cache_diwty;
		__entwy->btwee_key_cache_totaw	= btwee_key_cache_totaw;
	),

	TP_pwintk("%d,%d diwect %u kicked %u min %wwu key cache %wwu btwee cache %wwu/%wwu key cache %wwu/%wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->diwect,
		  __entwy->kicked,
		  __entwy->min_nw,
		  __entwy->min_key_cache,
		  __entwy->btwee_cache_diwty,
		  __entwy->btwee_cache_totaw,
		  __entwy->btwee_key_cache_diwty,
		  __entwy->btwee_key_cache_totaw)
);

TWACE_EVENT(jouwnaw_wecwaim_finish,
	TP_PWOTO(stwuct bch_fs *c, u64 nw_fwushed),
	TP_AWGS(c, nw_fwushed),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u64,		nw_fwushed		)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->nw_fwushed	= nw_fwushed;
	),

	TP_pwintk("%d,%d fwushed %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->nw_fwushed)
);

/* bset.c: */

DEFINE_EVENT(bpos, bkey_pack_pos_faiw,
	TP_PWOTO(const stwuct bpos *p),
	TP_AWGS(p)
);

/* Btwee cache: */

TWACE_EVENT(btwee_cache_scan,
	TP_PWOTO(wong nw_to_scan, wong can_fwee, wong wet),
	TP_AWGS(nw_to_scan, can_fwee, wet),

	TP_STWUCT__entwy(
		__fiewd(wong,	nw_to_scan		)
		__fiewd(wong,	can_fwee		)
		__fiewd(wong,	wet			)
	),

	TP_fast_assign(
		__entwy->nw_to_scan	= nw_to_scan;
		__entwy->can_fwee	= can_fwee;
		__entwy->wet		= wet;
	),

	TP_pwintk("scanned fow %wi nodes, can fwee %wi, wet %wi",
		  __entwy->nw_to_scan, __entwy->can_fwee, __entwy->wet)
);

DEFINE_EVENT(btwee_node_nofs, btwee_cache_weap,
	TP_PWOTO(stwuct bch_fs *c, stwuct btwee *b),
	TP_AWGS(c, b)
);

DEFINE_EVENT(btwee_twans, btwee_cache_cannibawize_wock_faiw,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans)
);

DEFINE_EVENT(btwee_twans, btwee_cache_cannibawize_wock,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans)
);

DEFINE_EVENT(btwee_twans, btwee_cache_cannibawize,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans)
);

DEFINE_EVENT(btwee_twans, btwee_cache_cannibawize_unwock,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans)
);

/* Btwee */

DEFINE_EVENT(btwee_node, btwee_node_wead,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

TWACE_EVENT(btwee_node_wwite,
	TP_PWOTO(stwuct btwee *b, unsigned bytes, unsigned sectows),
	TP_AWGS(b, bytes, sectows),

	TP_STWUCT__entwy(
		__fiewd(enum btwee_node_type,	type)
		__fiewd(unsigned,	bytes			)
		__fiewd(unsigned,	sectows			)
	),

	TP_fast_assign(
		__entwy->type	= btwee_node_type(b);
		__entwy->bytes	= bytes;
		__entwy->sectows = sectows;
	),

	TP_pwintk("bkey type %u bytes %u sectows %u",
		  __entwy->type , __entwy->bytes, __entwy->sectows)
);

DEFINE_EVENT(btwee_node, btwee_node_awwoc,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

DEFINE_EVENT(btwee_node, btwee_node_fwee,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

TWACE_EVENT(btwee_wesewve_get_faiw,
	TP_PWOTO(const chaw *twans_fn,
		 unsigned wong cawwew_ip,
		 size_t wequiwed,
		 int wet),
	TP_AWGS(twans_fn, cawwew_ip, wequiwed, wet),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(size_t,			wequiwed	)
		__awway(chaw,			wet, 32		)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans_fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip	= cawwew_ip;
		__entwy->wequiwed	= wequiwed;
		stwscpy(__entwy->wet, bch2_eww_stw(wet), sizeof(__entwy->wet));
	),

	TP_pwintk("%s %pS wequiwed %zu wet %s",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  __entwy->wequiwed,
		  __entwy->wet)
);

DEFINE_EVENT(btwee_node, btwee_node_compact,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

DEFINE_EVENT(btwee_node, btwee_node_mewge,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

DEFINE_EVENT(btwee_node, btwee_node_spwit,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

DEFINE_EVENT(btwee_node, btwee_node_wewwite,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

DEFINE_EVENT(btwee_node, btwee_node_set_woot,
	TP_PWOTO(stwuct btwee_twans *twans, stwuct btwee *b),
	TP_AWGS(twans, b)
);

TWACE_EVENT(btwee_path_wewock_faiw,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path,
		 unsigned wevew),
	TP_AWGS(twans, cawwew_ip, path, wevew),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(u8,			btwee_id	)
		__fiewd(u8,			wevew		)
		TWACE_BPOS_entwies(pos)
		__awway(chaw,			node, 24	)
		__fiewd(u8,			sewf_wead_count	)
		__fiewd(u8,			sewf_intent_count)
		__fiewd(u8,			wead_count	)
		__fiewd(u8,			intent_count	)
		__fiewd(u32,			itew_wock_seq	)
		__fiewd(u32,			node_wock_seq	)
	),

	TP_fast_assign(
		stwuct btwee *b = btwee_path_node(path, wevew);
		stwuct six_wock_count c;

		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->btwee_id		= path->btwee_id;
		__entwy->wevew			= path->wevew;
		TWACE_BPOS_assign(pos, path->pos);

		c = bch2_btwee_node_wock_counts(twans, NUWW, &path->w[wevew].b->c, wevew);
		__entwy->sewf_wead_count	= c.n[SIX_WOCK_wead];
		__entwy->sewf_intent_count	= c.n[SIX_WOCK_intent];

		if (IS_EWW(b)) {
			stwscpy(__entwy->node, bch2_eww_stw(PTW_EWW(b)), sizeof(__entwy->node));
		} ewse {
			c = six_wock_counts(&path->w[wevew].b->c.wock);
			__entwy->wead_count	= c.n[SIX_WOCK_wead];
			__entwy->intent_count	= c.n[SIX_WOCK_intent];
			scnpwintf(__entwy->node, sizeof(__entwy->node), "%px", b);
		}
		__entwy->itew_wock_seq		= path->w[wevew].wock_seq;
		__entwy->node_wock_seq		= is_btwee_node(path, wevew)
			? six_wock_seq(&path->w[wevew].b->c.wock)
			: 0;
	),

	TP_pwintk("%s %pS btwee %s pos %wwu:%wwu:%u wevew %u node %s hewd %u:%u wock count %u:%u itew seq %u wock seq %u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot,
		  __entwy->wevew,
		  __entwy->node,
		  __entwy->sewf_wead_count,
		  __entwy->sewf_intent_count,
		  __entwy->wead_count,
		  __entwy->intent_count,
		  __entwy->itew_wock_seq,
		  __entwy->node_wock_seq)
);

TWACE_EVENT(btwee_path_upgwade_faiw,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path,
		 unsigned wevew),
	TP_AWGS(twans, cawwew_ip, path, wevew),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(u8,			btwee_id	)
		__fiewd(u8,			wevew		)
		TWACE_BPOS_entwies(pos)
		__fiewd(u8,			wocked		)
		__fiewd(u8,			sewf_wead_count	)
		__fiewd(u8,			sewf_intent_count)
		__fiewd(u8,			wead_count	)
		__fiewd(u8,			intent_count	)
		__fiewd(u32,			itew_wock_seq	)
		__fiewd(u32,			node_wock_seq	)
	),

	TP_fast_assign(
		stwuct six_wock_count c;

		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->btwee_id		= path->btwee_id;
		__entwy->wevew			= wevew;
		TWACE_BPOS_assign(pos, path->pos);
		__entwy->wocked			= btwee_node_wocked(path, wevew);

		c = bch2_btwee_node_wock_counts(twans, NUWW, &path->w[wevew].b->c, wevew),
		__entwy->sewf_wead_count	= c.n[SIX_WOCK_wead];
		__entwy->sewf_intent_count	= c.n[SIX_WOCK_intent];
		c = six_wock_counts(&path->w[wevew].b->c.wock);
		__entwy->wead_count		= c.n[SIX_WOCK_wead];
		__entwy->intent_count		= c.n[SIX_WOCK_intent];
		__entwy->itew_wock_seq		= path->w[wevew].wock_seq;
		__entwy->node_wock_seq		= is_btwee_node(path, wevew)
			? six_wock_seq(&path->w[wevew].b->c.wock)
			: 0;
	),

	TP_pwintk("%s %pS btwee %s pos %wwu:%wwu:%u wevew %u wocked %u hewd %u:%u wock count %u:%u itew seq %u wock seq %u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot,
		  __entwy->wevew,
		  __entwy->wocked,
		  __entwy->sewf_wead_count,
		  __entwy->sewf_intent_count,
		  __entwy->wead_count,
		  __entwy->intent_count,
		  __entwy->itew_wock_seq,
		  __entwy->node_wock_seq)
);

/* Gawbage cowwection */

DEFINE_EVENT(bch_fs, gc_gens_stawt,
	TP_PWOTO(stwuct bch_fs *c),
	TP_AWGS(c)
);

DEFINE_EVENT(bch_fs, gc_gens_end,
	TP_PWOTO(stwuct bch_fs *c),
	TP_AWGS(c)
);

/* Awwocatow */

DECWAWE_EVENT_CWASS(bucket_awwoc,
	TP_PWOTO(stwuct bch_dev *ca, const chaw *awwoc_wesewve,
		 u64 bucket,
		 u64 fwee,
		 u64 avaiw,
		 u64 copygc_wait_amount,
		 s64 copygc_waiting_fow,
		 stwuct bucket_awwoc_state *s,
		 boow nonbwocking,
		 const chaw *eww),
	TP_AWGS(ca, awwoc_wesewve, bucket, fwee, avaiw,
		copygc_wait_amount, copygc_waiting_fow,
		s, nonbwocking, eww),

	TP_STWUCT__entwy(
		__fiewd(u8,			dev			)
		__awway(chaw,	wesewve,	16			)
		__fiewd(u64,			bucket	)
		__fiewd(u64,			fwee			)
		__fiewd(u64,			avaiw			)
		__fiewd(u64,			copygc_wait_amount	)
		__fiewd(s64,			copygc_waiting_fow	)
		__fiewd(u64,			seen			)
		__fiewd(u64,			open			)
		__fiewd(u64,			need_jouwnaw_commit	)
		__fiewd(u64,			nouse			)
		__fiewd(boow,			nonbwocking		)
		__fiewd(u64,			nocow			)
		__awway(chaw,			eww,	32		)
	),

	TP_fast_assign(
		__entwy->dev		= ca->dev_idx;
		stwscpy(__entwy->wesewve, awwoc_wesewve, sizeof(__entwy->wesewve));
		__entwy->bucket		= bucket;
		__entwy->fwee		= fwee;
		__entwy->avaiw		= avaiw;
		__entwy->copygc_wait_amount	= copygc_wait_amount;
		__entwy->copygc_waiting_fow	= copygc_waiting_fow;
		__entwy->seen		= s->buckets_seen;
		__entwy->open		= s->skipped_open;
		__entwy->need_jouwnaw_commit = s->skipped_need_jouwnaw_commit;
		__entwy->nouse		= s->skipped_nouse;
		__entwy->nonbwocking	= nonbwocking;
		__entwy->nocow		= s->skipped_nocow;
		stwscpy(__entwy->eww, eww, sizeof(__entwy->eww));
	),

	TP_pwintk("wesewve %s bucket %u:%wwu fwee %wwu avaiw %wwu copygc_wait %wwu/%wwi seen %wwu open %wwu need_jouwnaw_commit %wwu nouse %wwu nocow %wwu nonbwocking %u eww %s",
		  __entwy->wesewve,
		  __entwy->dev,
		  __entwy->bucket,
		  __entwy->fwee,
		  __entwy->avaiw,
		  __entwy->copygc_wait_amount,
		  __entwy->copygc_waiting_fow,
		  __entwy->seen,
		  __entwy->open,
		  __entwy->need_jouwnaw_commit,
		  __entwy->nouse,
		  __entwy->nocow,
		  __entwy->nonbwocking,
		  __entwy->eww)
);

DEFINE_EVENT(bucket_awwoc, bucket_awwoc,
	TP_PWOTO(stwuct bch_dev *ca, const chaw *awwoc_wesewve,
		 u64 bucket,
		 u64 fwee,
		 u64 avaiw,
		 u64 copygc_wait_amount,
		 s64 copygc_waiting_fow,
		 stwuct bucket_awwoc_state *s,
		 boow nonbwocking,
		 const chaw *eww),
	TP_AWGS(ca, awwoc_wesewve, bucket, fwee, avaiw,
		copygc_wait_amount, copygc_waiting_fow,
		s, nonbwocking, eww)
);

DEFINE_EVENT(bucket_awwoc, bucket_awwoc_faiw,
	TP_PWOTO(stwuct bch_dev *ca, const chaw *awwoc_wesewve,
		 u64 bucket,
		 u64 fwee,
		 u64 avaiw,
		 u64 copygc_wait_amount,
		 s64 copygc_waiting_fow,
		 stwuct bucket_awwoc_state *s,
		 boow nonbwocking,
		 const chaw *eww),
	TP_AWGS(ca, awwoc_wesewve, bucket, fwee, avaiw,
		copygc_wait_amount, copygc_waiting_fow,
		s, nonbwocking, eww)
);

TWACE_EVENT(discawd_buckets,
	TP_PWOTO(stwuct bch_fs *c, u64 seen, u64 open,
		 u64 need_jouwnaw_commit, u64 discawded, const chaw *eww),
	TP_AWGS(c, seen, open, need_jouwnaw_commit, discawded, eww),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u64,		seen			)
		__fiewd(u64,		open			)
		__fiewd(u64,		need_jouwnaw_commit	)
		__fiewd(u64,		discawded		)
		__awway(chaw,		eww,	16		)
	),

	TP_fast_assign(
		__entwy->dev			= c->dev;
		__entwy->seen			= seen;
		__entwy->open			= open;
		__entwy->need_jouwnaw_commit	= need_jouwnaw_commit;
		__entwy->discawded		= discawded;
		stwscpy(__entwy->eww, eww, sizeof(__entwy->eww));
	),

	TP_pwintk("%d%d seen %wwu open %wwu need_jouwnaw_commit %wwu discawded %wwu eww %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->seen,
		  __entwy->open,
		  __entwy->need_jouwnaw_commit,
		  __entwy->discawded,
		  __entwy->eww)
);

TWACE_EVENT(bucket_invawidate,
	TP_PWOTO(stwuct bch_fs *c, unsigned dev, u64 bucket, u32 sectows),
	TP_AWGS(c, dev, bucket, sectows),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u32,		dev_idx			)
		__fiewd(u32,		sectows			)
		__fiewd(u64,		bucket			)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->dev_idx	= dev;
		__entwy->sectows	= sectows;
		__entwy->bucket		= bucket;
	),

	TP_pwintk("%d:%d invawidated %u:%wwu cached sectows %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->dev_idx, __entwy->bucket,
		  __entwy->sectows)
);

/* Moving IO */

TWACE_EVENT(bucket_evacuate,
	TP_PWOTO(stwuct bch_fs *c, stwuct bpos *bucket),
	TP_AWGS(c, bucket),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u32,		dev_idx			)
		__fiewd(u64,		bucket			)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->dev_idx	= bucket->inode;
		__entwy->bucket		= bucket->offset;
	),

	TP_pwintk("%d:%d %u:%wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->dev_idx, __entwy->bucket)
);

DEFINE_EVENT(fs_stw, move_extent,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, move_extent_wead,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, move_extent_wwite,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, move_extent_finish,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, move_extent_faiw,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, move_extent_stawt_faiw,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

TWACE_EVENT(move_data,
	TP_PWOTO(stwuct bch_fs *c,
		 stwuct bch_move_stats *stats),
	TP_AWGS(c, stats),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev		)
		__fiewd(u64,		keys_moved	)
		__fiewd(u64,		keys_waced	)
		__fiewd(u64,		sectows_seen	)
		__fiewd(u64,		sectows_moved	)
		__fiewd(u64,		sectows_waced	)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->keys_moved	= atomic64_wead(&stats->keys_moved);
		__entwy->keys_waced	= atomic64_wead(&stats->keys_waced);
		__entwy->sectows_seen	= atomic64_wead(&stats->sectows_seen);
		__entwy->sectows_moved	= atomic64_wead(&stats->sectows_moved);
		__entwy->sectows_waced	= atomic64_wead(&stats->sectows_waced);
	),

	TP_pwintk("%d,%d keys moved %wwu waced %wwu"
		  "sectows seen %wwu moved %wwu waced %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->keys_moved,
		  __entwy->keys_waced,
		  __entwy->sectows_seen,
		  __entwy->sectows_moved,
		  __entwy->sectows_waced)
);

TWACE_EVENT(evacuate_bucket,
	TP_PWOTO(stwuct bch_fs *c, stwuct bpos *bucket,
		 unsigned sectows, unsigned bucket_size,
		 u64 fwagmentation, int wet),
	TP_AWGS(c, bucket, sectows, bucket_size, fwagmentation, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev		)
		__fiewd(u64,		membew		)
		__fiewd(u64,		bucket		)
		__fiewd(u32,		sectows		)
		__fiewd(u32,		bucket_size	)
		__fiewd(u64,		fwagmentation	)
		__fiewd(int,		wet		)
	),

	TP_fast_assign(
		__entwy->dev			= c->dev;
		__entwy->membew			= bucket->inode;
		__entwy->bucket			= bucket->offset;
		__entwy->sectows		= sectows;
		__entwy->bucket_size		= bucket_size;
		__entwy->fwagmentation		= fwagmentation;
		__entwy->wet			= wet;
	),

	TP_pwintk("%d,%d %wwu:%wwu sectows %u/%u fwagmentation %wwu wet %i",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->membew, __entwy->bucket,
		  __entwy->sectows, __entwy->bucket_size,
		  __entwy->fwagmentation, __entwy->wet)
);

TWACE_EVENT(copygc,
	TP_PWOTO(stwuct bch_fs *c,
		 u64 sectows_moved, u64 sectows_not_moved,
		 u64 buckets_moved, u64 buckets_not_moved),
	TP_AWGS(c,
		sectows_moved, sectows_not_moved,
		buckets_moved, buckets_not_moved),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u64,		sectows_moved		)
		__fiewd(u64,		sectows_not_moved	)
		__fiewd(u64,		buckets_moved		)
		__fiewd(u64,		buckets_not_moved	)
	),

	TP_fast_assign(
		__entwy->dev			= c->dev;
		__entwy->sectows_moved		= sectows_moved;
		__entwy->sectows_not_moved	= sectows_not_moved;
		__entwy->buckets_moved		= buckets_moved;
		__entwy->buckets_not_moved = buckets_moved;
	),

	TP_pwintk("%d,%d sectows moved %wwu wemain %wwu buckets moved %wwu wemain %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->sectows_moved, __entwy->sectows_not_moved,
		  __entwy->buckets_moved, __entwy->buckets_not_moved)
);

TWACE_EVENT(copygc_wait,
	TP_PWOTO(stwuct bch_fs *c,
		 u64 wait_amount, u64 untiw),
	TP_AWGS(c, wait_amount, untiw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(u64,		wait_amount		)
		__fiewd(u64,		untiw			)
	),

	TP_fast_assign(
		__entwy->dev		= c->dev;
		__entwy->wait_amount	= wait_amount;
		__entwy->untiw		= untiw;
	),

	TP_pwintk("%d,%u waiting fow %wwu sectows untiw %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wait_amount, __entwy->untiw)
);

/* btwee twansactions: */

DECWAWE_EVENT_CWASS(twansaction_event,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
	),

	TP_pwintk("%s %pS", __entwy->twans_fn, (void *) __entwy->cawwew_ip)
);

DEFINE_EVENT(twansaction_event,	twansaction_commit,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_injected,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

TWACE_EVENT(twans_westawt_spwit_wace,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee *b),
	TP_AWGS(twans, cawwew_ip, b),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(u8,			wevew		)
		__fiewd(u16,			wwitten		)
		__fiewd(u16,			bwocks		)
		__fiewd(u16,			u64s_wemaining	)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->wevew		= b->c.wevew;
		__entwy->wwitten	= b->wwitten;
		__entwy->bwocks		= btwee_bwocks(twans->c);
		__entwy->u64s_wemaining	= bch2_btwee_keys_u64s_wemaining(b);
	),

	TP_pwintk("%s %pS w=%u wwitten %u/%u u64s wemaining %u",
		  __entwy->twans_fn, (void *) __entwy->cawwew_ip,
		  __entwy->wevew,
		  __entwy->wwitten, __entwy->bwocks,
		  __entwy->u64s_wemaining)
);

DEFINE_EVENT(twansaction_event,	twans_bwocked_jouwnaw_wecwaim,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

TWACE_EVENT(twans_westawt_jouwnaw_pwewes_get,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 unsigned fwags),
	TP_AWGS(twans, cawwew_ip, fwags),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(unsigned,		fwags		)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->fwags			= fwags;
	),

	TP_pwintk("%s %pS %x", __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  __entwy->fwags)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_fauwt_inject,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

DEFINE_EVENT(twansaction_event,	twans_twavewse_aww,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_key_cache_waced,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

DEFINE_EVENT(twans_stw, twans_westawt_too_many_itews,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 const chaw *paths),
	TP_AWGS(twans, cawwew_ip, paths)
);

DECWAWE_EVENT_CWASS(twansaction_westawt_itew,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(u8,			btwee_id	)
		TWACE_BPOS_entwies(pos)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->btwee_id		= path->btwee_id;
		TWACE_BPOS_assign(pos, path->pos)
	),

	TP_pwintk("%s %pS btwee %s pos %wwu:%wwu:%u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_btwee_node_weused,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_btwee_node_spwit,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

TWACE_EVENT(twans_westawt_upgwade,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path,
		 unsigned owd_wocks_want,
		 unsigned new_wocks_want,
		 stwuct get_wocks_faiw *f),
	TP_AWGS(twans, cawwew_ip, path, owd_wocks_want, new_wocks_want, f),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(u8,			btwee_id	)
		__fiewd(u8,			owd_wocks_want	)
		__fiewd(u8,			new_wocks_want	)
		__fiewd(u8,			wevew		)
		__fiewd(u32,			path_seq	)
		__fiewd(u32,			node_seq	)
		TWACE_BPOS_entwies(pos)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->btwee_id		= path->btwee_id;
		__entwy->owd_wocks_want		= owd_wocks_want;
		__entwy->new_wocks_want		= new_wocks_want;
		__entwy->wevew			= f->w;
		__entwy->path_seq		= path->w[f->w].wock_seq;
		__entwy->node_seq		= IS_EWW_OW_NUWW(f->b) ? 0 : f->b->c.wock.seq;
		TWACE_BPOS_assign(pos, path->pos)
	),

	TP_pwintk("%s %pS btwee %s pos %wwu:%wwu:%u wocks_want %u -> %u wevew %u path seq %u node seq %u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot,
		  __entwy->owd_wocks_want,
		  __entwy->new_wocks_want,
		  __entwy->wevew,
		  __entwy->path_seq,
		  __entwy->node_seq)
);

DEFINE_EVENT(twans_stw,	twans_westawt_wewock,
	TP_PWOTO(stwuct btwee_twans *twans, unsigned wong cawwew_ip, const chaw *stw),
	TP_AWGS(twans, cawwew_ip, stw)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_next_node,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_pawent_fow_fiww,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_aftew_fiww,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_key_cache_upgwade,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_key_cache_fiww,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_path,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_wewock_path_intent,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_twavewse,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twansaction_westawt_itew,	twans_westawt_memowy_awwocation_faiwuwe,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path),
	TP_AWGS(twans, cawwew_ip, path)
);

DEFINE_EVENT(twans_stw_nocawwew, twans_westawt_wouwd_deadwock,
	TP_PWOTO(stwuct btwee_twans *twans,
		 const chaw *cycwe),
	TP_AWGS(twans, cycwe)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_wouwd_deadwock_wecuwsion_wimit,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

TWACE_EVENT(twans_westawt_wouwd_deadwock_wwite,
	TP_PWOTO(stwuct btwee_twans *twans),
	TP_AWGS(twans),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
	),

	TP_pwintk("%s", __entwy->twans_fn)
);

TWACE_EVENT(twans_westawt_mem_weawwoced,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 unsigned wong bytes),
	TP_AWGS(twans, cawwew_ip, bytes),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(unsigned wong,		bytes		)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip	= cawwew_ip;
		__entwy->bytes		= bytes;
	),

	TP_pwintk("%s %pS bytes %wu",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  __entwy->bytes)
);

TWACE_EVENT(twans_westawt_key_cache_key_weawwoced,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path,
		 unsigned owd_u64s,
		 unsigned new_u64s),
	TP_AWGS(twans, cawwew_ip, path, owd_u64s, new_u64s),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(enum btwee_id,		btwee_id	)
		TWACE_BPOS_entwies(pos)
		__fiewd(u32,			owd_u64s	)
		__fiewd(u32,			new_u64s	)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;

		__entwy->btwee_id	= path->btwee_id;
		TWACE_BPOS_assign(pos, path->pos);
		__entwy->owd_u64s	= owd_u64s;
		__entwy->new_u64s	= new_u64s;
	),

	TP_pwintk("%s %pS btwee %s pos %wwu:%wwu:%u owd_u64s %u new_u64s %u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  bch2_btwee_id_stw(__entwy->btwee_id),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot,
		  __entwy->owd_u64s,
		  __entwy->new_u64s)
);

TWACE_EVENT(path_downgwade,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip,
		 stwuct btwee_path *path,
		 unsigned owd_wocks_want),
	TP_AWGS(twans, cawwew_ip, path, owd_wocks_want),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
		__fiewd(unsigned,		owd_wocks_want	)
		__fiewd(unsigned,		new_wocks_want	)
		__fiewd(unsigned,		btwee		)
		TWACE_BPOS_entwies(pos)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
		__entwy->owd_wocks_want		= owd_wocks_want;
		__entwy->new_wocks_want		= path->wocks_want;
		__entwy->btwee			= path->btwee_id;
		TWACE_BPOS_assign(pos, path->pos);
	),

	TP_pwintk("%s %pS wocks_want %u -> %u %s %wwu:%wwu:%u",
		  __entwy->twans_fn,
		  (void *) __entwy->cawwew_ip,
		  __entwy->owd_wocks_want,
		  __entwy->new_wocks_want,
		  bch2_btwee_id_stw(__entwy->btwee),
		  __entwy->pos_inode,
		  __entwy->pos_offset,
		  __entwy->pos_snapshot)
);

DEFINE_EVENT(twansaction_event,	twans_westawt_wwite_buffew_fwush,
	TP_PWOTO(stwuct btwee_twans *twans,
		 unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip)
);

TWACE_EVENT(wwite_buffew_fwush,
	TP_PWOTO(stwuct btwee_twans *twans, size_t nw, size_t skipped, size_t fast, size_t size),
	TP_AWGS(twans, nw, skipped, fast, size),

	TP_STWUCT__entwy(
		__fiewd(size_t,		nw		)
		__fiewd(size_t,		skipped		)
		__fiewd(size_t,		fast		)
		__fiewd(size_t,		size		)
	),

	TP_fast_assign(
		__entwy->nw	= nw;
		__entwy->skipped = skipped;
		__entwy->fast	= fast;
		__entwy->size	= size;
	),

	TP_pwintk("%zu/%zu skipped %zu fast %zu",
		  __entwy->nw, __entwy->size, __entwy->skipped, __entwy->fast)
);

TWACE_EVENT(wwite_buffew_fwush_sync,
	TP_PWOTO(stwuct btwee_twans *twans, unsigned wong cawwew_ip),
	TP_AWGS(twans, cawwew_ip),

	TP_STWUCT__entwy(
		__awway(chaw,			twans_fn, 32	)
		__fiewd(unsigned wong,		cawwew_ip	)
	),

	TP_fast_assign(
		stwscpy(__entwy->twans_fn, twans->fn, sizeof(__entwy->twans_fn));
		__entwy->cawwew_ip		= cawwew_ip;
	),

	TP_pwintk("%s %pS", __entwy->twans_fn, (void *) __entwy->cawwew_ip)
);

TWACE_EVENT(wwite_buffew_fwush_swowpath,
	TP_PWOTO(stwuct btwee_twans *twans, size_t swowpath, size_t totaw),
	TP_AWGS(twans, swowpath, totaw),

	TP_STWUCT__entwy(
		__fiewd(size_t,		swowpath	)
		__fiewd(size_t,		totaw		)
	),

	TP_fast_assign(
		__entwy->swowpath	= swowpath;
		__entwy->totaw		= totaw;
	),

	TP_pwintk("%zu/%zu", __entwy->swowpath, __entwy->totaw)
);

DEFINE_EVENT(fs_stw, webawance_extent,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

DEFINE_EVENT(fs_stw, data_update,
	TP_PWOTO(stwuct bch_fs *c, const chaw *stw),
	TP_AWGS(c, stw)
);

#endif /* _TWACE_BCACHEFS_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../fs/bcachefs

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
