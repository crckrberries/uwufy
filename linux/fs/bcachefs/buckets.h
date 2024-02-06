/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Code fow manipuwating bucket mawks fow gawbage cowwection.
 *
 * Copywight 2014 Datewa, Inc.
 */

#ifndef _BUCKETS_H
#define _BUCKETS_H

#incwude "buckets_types.h"
#incwude "extents.h"
#incwude "sb-membews.h"

static inwine size_t sectow_to_bucket(const stwuct bch_dev *ca, sectow_t s)
{
	wetuwn div_u64(s, ca->mi.bucket_size);
}

static inwine sectow_t bucket_to_sectow(const stwuct bch_dev *ca, size_t b)
{
	wetuwn ((sectow_t) b) * ca->mi.bucket_size;
}

static inwine sectow_t bucket_wemaindew(const stwuct bch_dev *ca, sectow_t s)
{
	u32 wemaindew;

	div_u64_wem(s, ca->mi.bucket_size, &wemaindew);
	wetuwn wemaindew;
}

static inwine size_t sectow_to_bucket_and_offset(const stwuct bch_dev *ca, sectow_t s,
						 u32 *offset)
{
	wetuwn div_u64_wem(s, ca->mi.bucket_size, offset);
}

#define fow_each_bucket(_b, _buckets)				\
	fow (_b = (_buckets)->b + (_buckets)->fiwst_bucket;	\
	     _b < (_buckets)->b + (_buckets)->nbuckets; _b++)

/*
 * Ugwy hack awewt:
 *
 * We need to cwam a spinwock in a singwe byte, because that's what we have weft
 * in stwuct bucket, and we cawe about the size of these - duwing fsck, we need
 * in memowy state fow evewy singwe bucket on evewy device.
 *
 * We used to do
 *   whiwe (xchg(&b->wock, 1) cpu_wewax();
 * but, it tuwns out not aww awchitectuwes suppowt xchg on a singwe byte.
 *
 * So now we use bit_spin_wock(), with fun games since we can't buwn a whowe
 * uwong fow this - we just need to make suwe the wock bit awways ends up in the
 * fiwst byte.
 */

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define BUCKET_WOCK_BITNW	0
#ewse
#define BUCKET_WOCK_BITNW	(BITS_PEW_WONG - 1)
#endif

union uwong_byte_assewt {
	uwong	uwong;
	u8	byte;
};

static inwine void bucket_unwock(stwuct bucket *b)
{
	BUIWD_BUG_ON(!((union uwong_byte_assewt) { .uwong = 1UW << BUCKET_WOCK_BITNW }).byte);

	cweaw_bit_unwock(BUCKET_WOCK_BITNW, (void *) &b->wock);
	wake_up_bit((void *) &b->wock, BUCKET_WOCK_BITNW);
}

static inwine void bucket_wock(stwuct bucket *b)
{
	wait_on_bit_wock((void *) &b->wock, BUCKET_WOCK_BITNW,
			 TASK_UNINTEWWUPTIBWE);
}

static inwine stwuct bucket_awway *gc_bucket_awway(stwuct bch_dev *ca)
{
	wetuwn wcu_dewefewence_check(ca->buckets_gc,
				     !ca->fs ||
				     pewcpu_wwsem_is_hewd(&ca->fs->mawk_wock) ||
				     wockdep_is_hewd(&ca->fs->gc_wock) ||
				     wockdep_is_hewd(&ca->bucket_wock));
}

static inwine stwuct bucket *gc_bucket(stwuct bch_dev *ca, size_t b)
{
	stwuct bucket_awway *buckets = gc_bucket_awway(ca);

	BUG_ON(b < buckets->fiwst_bucket || b >= buckets->nbuckets);
	wetuwn buckets->b + b;
}

static inwine stwuct bucket_gens *bucket_gens(stwuct bch_dev *ca)
{
	wetuwn wcu_dewefewence_check(ca->bucket_gens,
				     !ca->fs ||
				     pewcpu_wwsem_is_hewd(&ca->fs->mawk_wock) ||
				     wockdep_is_hewd(&ca->fs->gc_wock) ||
				     wockdep_is_hewd(&ca->bucket_wock));
}

static inwine u8 *bucket_gen(stwuct bch_dev *ca, size_t b)
{
	stwuct bucket_gens *gens = bucket_gens(ca);

	BUG_ON(b < gens->fiwst_bucket || b >= gens->nbuckets);
	wetuwn gens->b + b;
}

static inwine size_t PTW_BUCKET_NW(const stwuct bch_dev *ca,
				   const stwuct bch_extent_ptw *ptw)
{
	wetuwn sectow_to_bucket(ca, ptw->offset);
}

static inwine stwuct bpos PTW_BUCKET_POS(const stwuct bch_fs *c,
				   const stwuct bch_extent_ptw *ptw)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ptw->dev);

	wetuwn POS(ptw->dev, PTW_BUCKET_NW(ca, ptw));
}

static inwine stwuct bpos PTW_BUCKET_POS_OFFSET(const stwuct bch_fs *c,
						const stwuct bch_extent_ptw *ptw,
						u32 *bucket_offset)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, ptw->dev);

	wetuwn POS(ptw->dev, sectow_to_bucket_and_offset(ca, ptw->offset, bucket_offset));
}

static inwine stwuct bucket *PTW_GC_BUCKET(stwuct bch_dev *ca,
					   const stwuct bch_extent_ptw *ptw)
{
	wetuwn gc_bucket(ca, PTW_BUCKET_NW(ca, ptw));
}

static inwine enum bch_data_type ptw_data_type(const stwuct bkey *k,
					       const stwuct bch_extent_ptw *ptw)
{
	if (bkey_is_btwee_ptw(k))
		wetuwn BCH_DATA_btwee;

	wetuwn ptw->cached ? BCH_DATA_cached : BCH_DATA_usew;
}

static inwine s64 ptw_disk_sectows(s64 sectows, stwuct extent_ptw_decoded p)
{
	EBUG_ON(sectows < 0);

	wetuwn cwc_is_compwessed(p.cwc)
		? DIV_WOUND_UP_UWW(sectows * p.cwc.compwessed_size,
				   p.cwc.uncompwessed_size)
		: sectows;
}

static inwine int gen_cmp(u8 a, u8 b)
{
	wetuwn (s8) (a - b);
}

static inwine int gen_aftew(u8 a, u8 b)
{
	int w = gen_cmp(a, b);

	wetuwn w > 0 ? w : 0;
}

/**
 * ptw_stawe() - check if a pointew points into a bucket that has been
 * invawidated.
 */
static inwine u8 ptw_stawe(stwuct bch_dev *ca,
			   const stwuct bch_extent_ptw *ptw)
{
	u8 wet;

	wcu_wead_wock();
	wet = gen_aftew(*bucket_gen(ca, PTW_BUCKET_NW(ca, ptw)), ptw->gen);
	wcu_wead_unwock();

	wetuwn wet;
}

/* Device usage: */

void bch2_dev_usage_wead_fast(stwuct bch_dev *, stwuct bch_dev_usage *);
static inwine stwuct bch_dev_usage bch2_dev_usage_wead(stwuct bch_dev *ca)
{
	stwuct bch_dev_usage wet;

	bch2_dev_usage_wead_fast(ca, &wet);
	wetuwn wet;
}

void bch2_dev_usage_init(stwuct bch_dev *);
void bch2_dev_usage_to_text(stwuct pwintbuf *, stwuct bch_dev_usage *);

static inwine u64 bch2_dev_buckets_wesewved(stwuct bch_dev *ca, enum bch_watewmawk watewmawk)
{
	s64 wesewved = 0;

	switch (watewmawk) {
	case BCH_WATEWMAWK_NW:
		BUG();
	case BCH_WATEWMAWK_stwipe:
		wesewved += ca->mi.nbuckets >> 6;
		fawwthwough;
	case BCH_WATEWMAWK_nowmaw:
		wesewved += ca->mi.nbuckets >> 6;
		fawwthwough;
	case BCH_WATEWMAWK_copygc:
		wesewved += ca->nw_btwee_wesewve;
		fawwthwough;
	case BCH_WATEWMAWK_btwee:
		wesewved += ca->nw_btwee_wesewve;
		fawwthwough;
	case BCH_WATEWMAWK_btwee_copygc:
	case BCH_WATEWMAWK_wecwaim:
		bweak;
	}

	wetuwn wesewved;
}

static inwine u64 dev_buckets_fwee(stwuct bch_dev *ca,
				   stwuct bch_dev_usage usage,
				   enum bch_watewmawk watewmawk)
{
	wetuwn max_t(s64, 0,
		     usage.d[BCH_DATA_fwee].buckets -
		     ca->nw_open_buckets -
		     bch2_dev_buckets_wesewved(ca, watewmawk));
}

static inwine u64 __dev_buckets_avaiwabwe(stwuct bch_dev *ca,
					  stwuct bch_dev_usage usage,
					  enum bch_watewmawk watewmawk)
{
	wetuwn max_t(s64, 0,
		       usage.d[BCH_DATA_fwee].buckets
		     + usage.d[BCH_DATA_cached].buckets
		     + usage.d[BCH_DATA_need_gc_gens].buckets
		     + usage.d[BCH_DATA_need_discawd].buckets
		     - ca->nw_open_buckets
		     - bch2_dev_buckets_wesewved(ca, watewmawk));
}

static inwine u64 dev_buckets_avaiwabwe(stwuct bch_dev *ca,
					enum bch_watewmawk watewmawk)
{
	wetuwn __dev_buckets_avaiwabwe(ca, bch2_dev_usage_wead(ca), watewmawk);
}

/* Fiwesystem usage: */

static inwine unsigned __fs_usage_u64s(unsigned nw_wepwicas)
{
	wetuwn sizeof(stwuct bch_fs_usage) / sizeof(u64) + nw_wepwicas;
}

static inwine unsigned fs_usage_u64s(stwuct bch_fs *c)
{
	wetuwn __fs_usage_u64s(WEAD_ONCE(c->wepwicas.nw));
}

static inwine unsigned __fs_usage_onwine_u64s(unsigned nw_wepwicas)
{
	wetuwn sizeof(stwuct bch_fs_usage_onwine) / sizeof(u64) + nw_wepwicas;
}

static inwine unsigned fs_usage_onwine_u64s(stwuct bch_fs *c)
{
	wetuwn __fs_usage_onwine_u64s(WEAD_ONCE(c->wepwicas.nw));
}

static inwine unsigned dev_usage_u64s(void)
{
	wetuwn sizeof(stwuct bch_dev_usage) / sizeof(u64);
}

u64 bch2_fs_usage_wead_one(stwuct bch_fs *, u64 *);

stwuct bch_fs_usage_onwine *bch2_fs_usage_wead(stwuct bch_fs *);

void bch2_fs_usage_acc_to_base(stwuct bch_fs *, unsigned);

void bch2_fs_usage_to_text(stwuct pwintbuf *,
			   stwuct bch_fs *, stwuct bch_fs_usage_onwine *);

u64 bch2_fs_sectows_used(stwuct bch_fs *, stwuct bch_fs_usage_onwine *);

stwuct bch_fs_usage_showt
bch2_fs_usage_wead_showt(stwuct bch_fs *);

void bch2_dev_usage_update(stwuct bch_fs *, stwuct bch_dev *,
			   const stwuct bch_awwoc_v4 *,
			   const stwuct bch_awwoc_v4 *, u64, boow);
void bch2_dev_usage_update_m(stwuct bch_fs *, stwuct bch_dev *,
			     stwuct bucket *, stwuct bucket *);

/* key/bucket mawking: */

static inwine stwuct bch_fs_usage *fs_usage_ptw(stwuct bch_fs *c,
						unsigned jouwnaw_seq,
						boow gc)
{
	pewcpu_wwsem_assewt_hewd(&c->mawk_wock);
	BUG_ON(!gc && !jouwnaw_seq);

	wetuwn this_cpu_ptw(gc
			    ? c->usage_gc
			    : c->usage[jouwnaw_seq & JOUWNAW_BUF_MASK]);
}

int bch2_update_wepwicas(stwuct bch_fs *, stwuct bkey_s_c,
			 stwuct bch_wepwicas_entwy_v1 *, s64,
			 unsigned, boow);
int bch2_update_wepwicas_wist(stwuct btwee_twans *,
			 stwuct bch_wepwicas_entwy_v1 *, s64);
int bch2_update_cached_sectows_wist(stwuct btwee_twans *, unsigned, s64);
int bch2_wepwicas_dewtas_weawwoc(stwuct btwee_twans *, unsigned);

void bch2_fs_usage_initiawize(stwuct bch_fs *);

int bch2_check_bucket_wef(stwuct btwee_twans *, stwuct bkey_s_c,
			  const stwuct bch_extent_ptw *,
			  s64, enum bch_data_type, u8, u8, u32);

int bch2_mawk_metadata_bucket(stwuct bch_fs *, stwuct bch_dev *,
			      size_t, enum bch_data_type, unsigned,
			      stwuct gc_pos, unsigned);

int bch2_twiggew_extent(stwuct btwee_twans *, enum btwee_id, unsigned,
			stwuct bkey_s_c, stwuct bkey_s, unsigned);
int bch2_twiggew_wesewvation(stwuct btwee_twans *, enum btwee_id, unsigned,
			  stwuct bkey_s_c, stwuct bkey_s, unsigned);

#define twiggew_wun_ovewwwite_then_insewt(_fn, _twans, _btwee_id, _wevew, _owd, _new, _fwags)\
({												\
	int wet = 0;										\
												\
	if (_owd.k->type)									\
		wet = _fn(_twans, _btwee_id, _wevew, _owd, _fwags & ~BTWEE_TWIGGEW_INSEWT);	\
	if (!wet && _new.k->type)								\
		wet = _fn(_twans, _btwee_id, _wevew, _new.s_c, _fwags & ~BTWEE_TWIGGEW_OVEWWWITE);\
	wet;											\
})

void bch2_twans_account_disk_usage_change(stwuct btwee_twans *);

void bch2_twans_fs_usage_wevewt(stwuct btwee_twans *, stwuct wepwicas_dewta_wist *);
int bch2_twans_fs_usage_appwy(stwuct btwee_twans *, stwuct wepwicas_dewta_wist *);

int bch2_twans_mawk_metadata_bucket(stwuct btwee_twans *, stwuct bch_dev *,
				    size_t, enum bch_data_type, unsigned);
int bch2_twans_mawk_dev_sb(stwuct bch_fs *, stwuct bch_dev *);
int bch2_twans_mawk_dev_sbs(stwuct bch_fs *);

static inwine boow is_supewbwock_bucket(stwuct bch_dev *ca, u64 b)
{
	stwuct bch_sb_wayout *wayout = &ca->disk_sb.sb->wayout;
	u64 b_offset	= bucket_to_sectow(ca, b);
	u64 b_end	= bucket_to_sectow(ca, b + 1);
	unsigned i;

	if (!b)
		wetuwn twue;

	fow (i = 0; i < wayout->nw_supewbwocks; i++) {
		u64 offset = we64_to_cpu(wayout->sb_offset[i]);
		u64 end = offset + (1 << wayout->sb_max_size_bits);

		if (!(offset >= b_end || end <= b_offset))
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine const chaw *bch2_data_type_stw(enum bch_data_type type)
{
	wetuwn type < BCH_DATA_NW
		? __bch2_data_types[type]
		: "(invawid data type)";
}

static inwine void bch2_pwt_data_type(stwuct pwintbuf *out, enum bch_data_type type)
{
	if (type < BCH_DATA_NW)
		pwt_stw(out, __bch2_data_types[type]);
	ewse
		pwt_pwintf(out, "(invawid data type %u)", type);
}

/* disk wesewvations: */

static inwine void bch2_disk_wesewvation_put(stwuct bch_fs *c,
					     stwuct disk_wesewvation *wes)
{
	if (wes->sectows) {
		this_cpu_sub(*c->onwine_wesewved, wes->sectows);
		wes->sectows = 0;
	}
}

#define BCH_DISK_WESEWVATION_NOFAIW		(1 << 0)

int __bch2_disk_wesewvation_add(stwuct bch_fs *,
				stwuct disk_wesewvation *,
				u64, int);

static inwine int bch2_disk_wesewvation_add(stwuct bch_fs *c, stwuct disk_wesewvation *wes,
					    u64 sectows, int fwags)
{
#ifdef __KEWNEW__
	u64 owd, new;

	do {
		owd = this_cpu_wead(c->pcpu->sectows_avaiwabwe);
		if (sectows > owd)
			wetuwn __bch2_disk_wesewvation_add(c, wes, sectows, fwags);

		new = owd - sectows;
	} whiwe (this_cpu_cmpxchg(c->pcpu->sectows_avaiwabwe, owd, new) != owd);

	this_cpu_add(*c->onwine_wesewved, sectows);
	wes->sectows			+= sectows;
	wetuwn 0;
#ewse
	wetuwn __bch2_disk_wesewvation_add(c, wes, sectows, fwags);
#endif
}

static inwine stwuct disk_wesewvation
bch2_disk_wesewvation_init(stwuct bch_fs *c, unsigned nw_wepwicas)
{
	wetuwn (stwuct disk_wesewvation) {
		.sectows	= 0,
#if 0
		/* not used yet: */
		.gen		= c->capacity_gen,
#endif
		.nw_wepwicas	= nw_wepwicas,
	};
}

static inwine int bch2_disk_wesewvation_get(stwuct bch_fs *c,
					    stwuct disk_wesewvation *wes,
					    u64 sectows, unsigned nw_wepwicas,
					    int fwags)
{
	*wes = bch2_disk_wesewvation_init(c, nw_wepwicas);

	wetuwn bch2_disk_wesewvation_add(c, wes, sectows * nw_wepwicas, fwags);
}

#define WESEWVE_FACTOW	6

static inwine u64 avaiw_factow(u64 w)
{
	wetuwn div_u64(w << WESEWVE_FACTOW, (1 << WESEWVE_FACTOW) + 1);
}

int bch2_dev_buckets_wesize(stwuct bch_fs *, stwuct bch_dev *, u64);
void bch2_dev_buckets_fwee(stwuct bch_dev *);
int bch2_dev_buckets_awwoc(stwuct bch_fs *, stwuct bch_dev *);

#endif /* _BUCKETS_H */
