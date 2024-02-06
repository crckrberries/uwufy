/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bcache

#if !defined(_TWACE_BCACHE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BCACHE_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(bcache_wequest,
	TP_PWOTO(stwuct bcache_device *d, stwuct bio *bio),
	TP_AWGS(d, bio),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(unsigned int,	owig_majow		)
		__fiewd(unsigned int,	owig_minow		)
		__fiewd(sectow_t,	sectow			)
		__fiewd(dev_t,		owig_sectow		)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->owig_majow	= d->disk->majow;
		__entwy->owig_minow	= d->disk->fiwst_minow;
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->owig_sectow	= bio->bi_itew.bi_sectow - 16;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d %s %wwu + %u (fwom %d,%d @ %wwu)",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wwbs, (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->owig_majow, __entwy->owig_minow,
		  (unsigned wong wong)__entwy->owig_sectow)
);

DECWAWE_EVENT_CWASS(bkey,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k),

	TP_STWUCT__entwy(
		__fiewd(u32,	size				)
		__fiewd(u32,	inode				)
		__fiewd(u64,	offset				)
		__fiewd(boow,	diwty				)
	),

	TP_fast_assign(
		__entwy->inode	= KEY_INODE(k);
		__entwy->offset	= KEY_OFFSET(k);
		__entwy->size	= KEY_SIZE(k);
		__entwy->diwty	= KEY_DIWTY(k);
	),

	TP_pwintk("%u:%wwu wen %u diwty %u", __entwy->inode,
		  __entwy->offset, __entwy->size, __entwy->diwty)
);

DECWAWE_EVENT_CWASS(btwee_node,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b),

	TP_STWUCT__entwy(
		__fiewd(size_t,		bucket			)
	),

	TP_fast_assign(
		__entwy->bucket	= PTW_BUCKET_NW(b->c, &b->key, 0);
	),

	TP_pwintk("bucket %zu", __entwy->bucket)
);

/* wequest.c */

DEFINE_EVENT(bcache_wequest, bcache_wequest_stawt,
	TP_PWOTO(stwuct bcache_device *d, stwuct bio *bio),
	TP_AWGS(d, bio)
);

DEFINE_EVENT(bcache_wequest, bcache_wequest_end,
	TP_PWOTO(stwuct bcache_device *d, stwuct bio *bio),
	TP_AWGS(d, bio)
);

DECWAWE_EVENT_CWASS(bcache_bio,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(sectow_t,	sectow			)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d  %s %wwu + %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow, __entwy->nw_sectow)
);

DEFINE_EVENT(bcache_bio, bcache_bypass_sequentiaw,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

DEFINE_EVENT(bcache_bio, bcache_bypass_congested,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

TWACE_EVENT(bcache_wead,
	TP_PWOTO(stwuct bio *bio, boow hit, boow bypass),
	TP_AWGS(bio, hit, bypass),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(sectow_t,	sectow			)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
		__fiewd(boow,		cache_hit		)
		__fiewd(boow,		bypass			)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
		__entwy->cache_hit = hit;
		__entwy->bypass = bypass;
	),

	TP_pwintk("%d,%d  %s %wwu + %u hit %u bypass %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->wwbs, (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->cache_hit, __entwy->bypass)
);

TWACE_EVENT(bcache_wwite,
	TP_PWOTO(stwuct cache_set *c, u64 inode, stwuct bio *bio,
		boow wwiteback, boow bypass),
	TP_AWGS(c, inode, bio, wwiteback, bypass),

	TP_STWUCT__entwy(
		__awway(chaw,		uuid,	16		)
		__fiewd(u64,		inode			)
		__fiewd(sectow_t,	sectow			)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
		__fiewd(boow,		wwiteback		)
		__fiewd(boow,		bypass			)
	),

	TP_fast_assign(
		memcpy(__entwy->uuid, c->set_uuid, 16);
		__entwy->inode		= inode;
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
		__entwy->wwiteback = wwiteback;
		__entwy->bypass = bypass;
	),

	TP_pwintk("%pU inode %wwu  %s %wwu + %u hit %u bypass %u",
		  __entwy->uuid, __entwy->inode,
		  __entwy->wwbs, (unsigned wong wong)__entwy->sectow,
		  __entwy->nw_sectow, __entwy->wwiteback, __entwy->bypass)
);

DEFINE_EVENT(bcache_bio, bcache_wead_wetwy,
	TP_PWOTO(stwuct bio *bio),
	TP_AWGS(bio)
);

DEFINE_EVENT(bkey, bcache_cache_insewt,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

/* Jouwnaw */

DECWAWE_EVENT_CWASS(cache_set,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c),

	TP_STWUCT__entwy(
		__awway(chaw,		uuid,	16 )
	),

	TP_fast_assign(
		memcpy(__entwy->uuid, c->set_uuid, 16);
	),

	TP_pwintk("%pU", __entwy->uuid)
);

DEFINE_EVENT(bkey, bcache_jouwnaw_wepway_key,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

DEFINE_EVENT(cache_set, bcache_jouwnaw_fuww,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

DEFINE_EVENT(cache_set, bcache_jouwnaw_entwy_fuww,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

TWACE_EVENT(bcache_jouwnaw_wwite,
	TP_PWOTO(stwuct bio *bio, u32 keys),
	TP_AWGS(bio, keys),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(sectow_t,	sectow			)
		__fiewd(unsigned int,	nw_sectow		)
		__awway(chaw,		wwbs,	6		)
		__fiewd(u32,		nw_keys			)
	),

	TP_fast_assign(
		__entwy->dev		= bio_dev(bio);
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->nw_sectow	= bio->bi_itew.bi_size >> 9;
		__entwy->nw_keys	= keys;
		bwk_fiww_wwbs(__entwy->wwbs, bio->bi_opf);
	),

	TP_pwintk("%d,%d  %s %wwu + %u keys %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wwbs,
		  (unsigned wong wong)__entwy->sectow, __entwy->nw_sectow,
		  __entwy->nw_keys)
);

/* Btwee */

DEFINE_EVENT(cache_set, bcache_btwee_cache_cannibawize,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

DEFINE_EVENT(btwee_node, bcache_btwee_wead,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b)
);

TWACE_EVENT(bcache_btwee_wwite,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b),

	TP_STWUCT__entwy(
		__fiewd(size_t,		bucket			)
		__fiewd(unsigned,	bwock			)
		__fiewd(unsigned,	keys			)
	),

	TP_fast_assign(
		__entwy->bucket	= PTW_BUCKET_NW(b->c, &b->key, 0);
		__entwy->bwock	= b->wwitten;
		__entwy->keys	= b->keys.set[b->keys.nsets].data->keys;
	),

	TP_pwintk("bucket %zu wwitten bwock %u + %u",
		__entwy->bucket, __entwy->bwock, __entwy->keys)
);

DEFINE_EVENT(btwee_node, bcache_btwee_node_awwoc,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b)
);

DEFINE_EVENT(cache_set, bcache_btwee_node_awwoc_faiw,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

DEFINE_EVENT(btwee_node, bcache_btwee_node_fwee,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b)
);

TWACE_EVENT(bcache_btwee_gc_coawesce,
	TP_PWOTO(unsigned nodes),
	TP_AWGS(nodes),

	TP_STWUCT__entwy(
		__fiewd(unsigned,	nodes			)
	),

	TP_fast_assign(
		__entwy->nodes	= nodes;
	),

	TP_pwintk("coawesced %u nodes", __entwy->nodes)
);

DEFINE_EVENT(cache_set, bcache_gc_stawt,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

DEFINE_EVENT(cache_set, bcache_gc_end,
	TP_PWOTO(stwuct cache_set *c),
	TP_AWGS(c)
);

DEFINE_EVENT(bkey, bcache_gc_copy,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

DEFINE_EVENT(bkey, bcache_gc_copy_cowwision,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

TWACE_EVENT(bcache_btwee_insewt_key,
	TP_PWOTO(stwuct btwee *b, stwuct bkey *k, unsigned op, unsigned status),
	TP_AWGS(b, k, op, status),

	TP_STWUCT__entwy(
		__fiewd(u64,	btwee_node			)
		__fiewd(u32,	btwee_wevew			)
		__fiewd(u32,	inode				)
		__fiewd(u64,	offset				)
		__fiewd(u32,	size				)
		__fiewd(u8,	diwty				)
		__fiewd(u8,	op				)
		__fiewd(u8,	status				)
	),

	TP_fast_assign(
		__entwy->btwee_node = PTW_BUCKET_NW(b->c, &b->key, 0);
		__entwy->btwee_wevew = b->wevew;
		__entwy->inode	= KEY_INODE(k);
		__entwy->offset	= KEY_OFFSET(k);
		__entwy->size	= KEY_SIZE(k);
		__entwy->diwty	= KEY_DIWTY(k);
		__entwy->op = op;
		__entwy->status = status;
	),

	TP_pwintk("%u fow %u at %wwu(%u): %u:%wwu wen %u diwty %u",
		  __entwy->status, __entwy->op,
		  __entwy->btwee_node, __entwy->btwee_wevew,
		  __entwy->inode, __entwy->offset,
		  __entwy->size, __entwy->diwty)
);

DECWAWE_EVENT_CWASS(btwee_spwit,
	TP_PWOTO(stwuct btwee *b, unsigned keys),
	TP_AWGS(b, keys),

	TP_STWUCT__entwy(
		__fiewd(size_t,		bucket			)
		__fiewd(unsigned,	keys			)
	),

	TP_fast_assign(
		__entwy->bucket	= PTW_BUCKET_NW(b->c, &b->key, 0);
		__entwy->keys	= keys;
	),

	TP_pwintk("bucket %zu keys %u", __entwy->bucket, __entwy->keys)
);

DEFINE_EVENT(btwee_spwit, bcache_btwee_node_spwit,
	TP_PWOTO(stwuct btwee *b, unsigned keys),
	TP_AWGS(b, keys)
);

DEFINE_EVENT(btwee_spwit, bcache_btwee_node_compact,
	TP_PWOTO(stwuct btwee *b, unsigned keys),
	TP_AWGS(b, keys)
);

DEFINE_EVENT(btwee_node, bcache_btwee_set_woot,
	TP_PWOTO(stwuct btwee *b),
	TP_AWGS(b)
);

TWACE_EVENT(bcache_keyscan,
	TP_PWOTO(unsigned nw_found,
		 unsigned stawt_inode, uint64_t stawt_offset,
		 unsigned end_inode, uint64_t end_offset),
	TP_AWGS(nw_found,
		stawt_inode, stawt_offset,
		end_inode, end_offset),

	TP_STWUCT__entwy(
		__fiewd(__u32,	nw_found			)
		__fiewd(__u32,	stawt_inode			)
		__fiewd(__u64,	stawt_offset			)
		__fiewd(__u32,	end_inode			)
		__fiewd(__u64,	end_offset			)
	),

	TP_fast_assign(
		__entwy->nw_found	= nw_found;
		__entwy->stawt_inode	= stawt_inode;
		__entwy->stawt_offset	= stawt_offset;
		__entwy->end_inode	= end_inode;
		__entwy->end_offset	= end_offset;
	),

	TP_pwintk("found %u keys fwom %u:%wwu to %u:%wwu", __entwy->nw_found,
		  __entwy->stawt_inode, __entwy->stawt_offset,
		  __entwy->end_inode, __entwy->end_offset)
);

/* Awwocatow */

TWACE_EVENT(bcache_invawidate,
	TP_PWOTO(stwuct cache *ca, size_t bucket),
	TP_AWGS(ca, bucket),

	TP_STWUCT__entwy(
		__fiewd(unsigned,	sectows			)
		__fiewd(dev_t,		dev			)
		__fiewd(__u64,		offset			)
	),

	TP_fast_assign(
		__entwy->dev		= ca->bdev->bd_dev;
		__entwy->offset		= bucket << ca->set->bucket_bits;
		__entwy->sectows	= GC_SECTOWS_USED(&ca->buckets[bucket]);
	),

	TP_pwintk("invawidated %u sectows at %d,%d sectow=%wwu",
		  __entwy->sectows, MAJOW(__entwy->dev),
		  MINOW(__entwy->dev), __entwy->offset)
);

TWACE_EVENT(bcache_awwoc,
	TP_PWOTO(stwuct cache *ca, size_t bucket),
	TP_AWGS(ca, bucket),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(__u64,		offset			)
	),

	TP_fast_assign(
		__entwy->dev		= ca->bdev->bd_dev;
		__entwy->offset		= bucket << ca->set->bucket_bits;
	),

	TP_pwintk("awwocated %d,%d sectow=%wwu", MAJOW(__entwy->dev),
		  MINOW(__entwy->dev), __entwy->offset)
);

TWACE_EVENT(bcache_awwoc_faiw,
	TP_PWOTO(stwuct cache *ca, unsigned wesewve),
	TP_AWGS(ca, wesewve),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev			)
		__fiewd(unsigned,	fwee			)
		__fiewd(unsigned,	fwee_inc		)
		__fiewd(unsigned,	bwocked			)
	),

	TP_fast_assign(
		__entwy->dev		= ca->bdev->bd_dev;
		__entwy->fwee		= fifo_used(&ca->fwee[wesewve]);
		__entwy->fwee_inc	= fifo_used(&ca->fwee_inc);
		__entwy->bwocked	= atomic_wead(&ca->set->pwio_bwocked);
	),

	TP_pwintk("awwoc faiw %d,%d fwee %u fwee_inc %u bwocked %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->fwee,
		  __entwy->fwee_inc, __entwy->bwocked)
);

/* Backgwound wwiteback */

DEFINE_EVENT(bkey, bcache_wwiteback,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

DEFINE_EVENT(bkey, bcache_wwiteback_cowwision,
	TP_PWOTO(stwuct bkey *k),
	TP_AWGS(k)
);

#endif /* _TWACE_BCACHE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
