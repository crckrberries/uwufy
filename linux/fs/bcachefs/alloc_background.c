// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "awwoc_fowegwound.h"
#incwude "backpointews.h"
#incwude "btwee_cache.h"
#incwude "btwee_io.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_gc.h"
#incwude "btwee_wwite_buffew.h"
#incwude "buckets.h"
#incwude "buckets_waiting_fow_jouwnaw.h"
#incwude "cwock.h"
#incwude "debug.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "wwu.h"
#incwude "wecovewy.h"
#incwude "twace.h"
#incwude "vawint.h"

#incwude <winux/kthwead.h>
#incwude <winux/math64.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/task.h>
#incwude <winux/sowt.h>

/* Pewsistent awwoc info: */

static const unsigned BCH_AWWOC_V1_FIEWD_BYTES[] = {
#define x(name, bits) [BCH_AWWOC_FIEWD_V1_##name] = bits / 8,
	BCH_AWWOC_FIEWDS_V1()
#undef x
};

stwuct bkey_awwoc_unpacked {
	u64		jouwnaw_seq;
	u8		gen;
	u8		owdest_gen;
	u8		data_type;
	boow		need_discawd:1;
	boow		need_inc_gen:1;
#define x(_name, _bits)	u##_bits _name;
	BCH_AWWOC_FIEWDS_V2()
#undef  x
};

static inwine u64 awwoc_fiewd_v1_get(const stwuct bch_awwoc *a,
				     const void **p, unsigned fiewd)
{
	unsigned bytes = BCH_AWWOC_V1_FIEWD_BYTES[fiewd];
	u64 v;

	if (!(a->fiewds & (1 << fiewd)))
		wetuwn 0;

	switch (bytes) {
	case 1:
		v = *((const u8 *) *p);
		bweak;
	case 2:
		v = we16_to_cpup(*p);
		bweak;
	case 4:
		v = we32_to_cpup(*p);
		bweak;
	case 8:
		v = we64_to_cpup(*p);
		bweak;
	defauwt:
		BUG();
	}

	*p += bytes;
	wetuwn v;
}

static void bch2_awwoc_unpack_v1(stwuct bkey_awwoc_unpacked *out,
				 stwuct bkey_s_c k)
{
	const stwuct bch_awwoc *in = bkey_s_c_to_awwoc(k).v;
	const void *d = in->data;
	unsigned idx = 0;

	out->gen = in->gen;

#define x(_name, _bits) out->_name = awwoc_fiewd_v1_get(in, &d, idx++);
	BCH_AWWOC_FIEWDS_V1()
#undef  x
}

static int bch2_awwoc_unpack_v2(stwuct bkey_awwoc_unpacked *out,
				stwuct bkey_s_c k)
{
	stwuct bkey_s_c_awwoc_v2 a = bkey_s_c_to_awwoc_v2(k);
	const u8 *in = a.v->data;
	const u8 *end = bkey_vaw_end(a);
	unsigned fiewdnw = 0;
	int wet;
	u64 v;

	out->gen	= a.v->gen;
	out->owdest_gen	= a.v->owdest_gen;
	out->data_type	= a.v->data_type;

#define x(_name, _bits)							\
	if (fiewdnw < a.v->nw_fiewds) {					\
		wet = bch2_vawint_decode_fast(in, end, &v);		\
		if (wet < 0)						\
			wetuwn wet;					\
		in += wet;						\
	} ewse {							\
		v = 0;							\
	}								\
	out->_name = v;							\
	if (v != out->_name)						\
		wetuwn -1;						\
	fiewdnw++;

	BCH_AWWOC_FIEWDS_V2()
#undef  x
	wetuwn 0;
}

static int bch2_awwoc_unpack_v3(stwuct bkey_awwoc_unpacked *out,
				stwuct bkey_s_c k)
{
	stwuct bkey_s_c_awwoc_v3 a = bkey_s_c_to_awwoc_v3(k);
	const u8 *in = a.v->data;
	const u8 *end = bkey_vaw_end(a);
	unsigned fiewdnw = 0;
	int wet;
	u64 v;

	out->gen	= a.v->gen;
	out->owdest_gen	= a.v->owdest_gen;
	out->data_type	= a.v->data_type;
	out->need_discawd = BCH_AWWOC_V3_NEED_DISCAWD(a.v);
	out->need_inc_gen = BCH_AWWOC_V3_NEED_INC_GEN(a.v);
	out->jouwnaw_seq = we64_to_cpu(a.v->jouwnaw_seq);

#define x(_name, _bits)							\
	if (fiewdnw < a.v->nw_fiewds) {					\
		wet = bch2_vawint_decode_fast(in, end, &v);		\
		if (wet < 0)						\
			wetuwn wet;					\
		in += wet;						\
	} ewse {							\
		v = 0;							\
	}								\
	out->_name = v;							\
	if (v != out->_name)						\
		wetuwn -1;						\
	fiewdnw++;

	BCH_AWWOC_FIEWDS_V2()
#undef  x
	wetuwn 0;
}

static stwuct bkey_awwoc_unpacked bch2_awwoc_unpack(stwuct bkey_s_c k)
{
	stwuct bkey_awwoc_unpacked wet = { .gen	= 0 };

	switch (k.k->type) {
	case KEY_TYPE_awwoc:
		bch2_awwoc_unpack_v1(&wet, k);
		bweak;
	case KEY_TYPE_awwoc_v2:
		bch2_awwoc_unpack_v2(&wet, k);
		bweak;
	case KEY_TYPE_awwoc_v3:
		bch2_awwoc_unpack_v3(&wet, k);
		bweak;
	}

	wetuwn wet;
}

static unsigned bch_awwoc_v1_vaw_u64s(const stwuct bch_awwoc *a)
{
	unsigned i, bytes = offsetof(stwuct bch_awwoc, data);

	fow (i = 0; i < AWWAY_SIZE(BCH_AWWOC_V1_FIEWD_BYTES); i++)
		if (a->fiewds & (1 << i))
			bytes += BCH_AWWOC_V1_FIEWD_BYTES[i];

	wetuwn DIV_WOUND_UP(bytes, sizeof(u64));
}

int bch2_awwoc_v1_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_awwoc a = bkey_s_c_to_awwoc(k);
	int wet = 0;

	/* awwow fow unknown fiewds */
	bkey_fsck_eww_on(bkey_vaw_u64s(a.k) < bch_awwoc_v1_vaw_u64s(a.v), c, eww,
			 awwoc_v1_vaw_size_bad,
			 "incowwect vawue size (%zu < %u)",
			 bkey_vaw_u64s(a.k), bch_awwoc_v1_vaw_u64s(a.v));
fsck_eww:
	wetuwn wet;
}

int bch2_awwoc_v2_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_awwoc_unpacked u;
	int wet = 0;

	bkey_fsck_eww_on(bch2_awwoc_unpack_v2(&u, k), c, eww,
			 awwoc_v2_unpack_ewwow,
			 "unpack ewwow");
fsck_eww:
	wetuwn wet;
}

int bch2_awwoc_v3_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_awwoc_unpacked u;
	int wet = 0;

	bkey_fsck_eww_on(bch2_awwoc_unpack_v3(&u, k), c, eww,
			 awwoc_v2_unpack_ewwow,
			 "unpack ewwow");
fsck_eww:
	wetuwn wet;
}

int bch2_awwoc_v4_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_awwoc_v4 a = bkey_s_c_to_awwoc_v4(k);
	int wet = 0;

	bkey_fsck_eww_on(awwoc_v4_u64s(a.v) > bkey_vaw_u64s(k.k), c, eww,
			 awwoc_v4_vaw_size_bad,
			 "bad vaw size (%u > %zu)",
			 awwoc_v4_u64s(a.v), bkey_vaw_u64s(k.k));

	bkey_fsck_eww_on(!BCH_AWWOC_V4_BACKPOINTEWS_STAWT(a.v) &&
			 BCH_AWWOC_V4_NW_BACKPOINTEWS(a.v), c, eww,
			 awwoc_v4_backpointews_stawt_bad,
			 "invawid backpointews_stawt");

	bkey_fsck_eww_on(awwoc_data_type(*a.v, a.v->data_type) != a.v->data_type, c, eww,
			 awwoc_key_data_type_bad,
			 "invawid data type (got %u shouwd be %u)",
			 a.v->data_type, awwoc_data_type(*a.v, a.v->data_type));

	switch (a.v->data_type) {
	case BCH_DATA_fwee:
	case BCH_DATA_need_gc_gens:
	case BCH_DATA_need_discawd:
		bkey_fsck_eww_on(bch2_bucket_sectows(*a.v) || a.v->stwipe,
				 c, eww, awwoc_key_empty_but_have_data,
				 "empty data type fwee but have data");
		bweak;
	case BCH_DATA_sb:
	case BCH_DATA_jouwnaw:
	case BCH_DATA_btwee:
	case BCH_DATA_usew:
	case BCH_DATA_pawity:
		bkey_fsck_eww_on(!bch2_bucket_sectows_diwty(*a.v),
				 c, eww, awwoc_key_diwty_sectows_0,
				 "data_type %s but diwty_sectows==0",
				 bch2_data_type_stw(a.v->data_type));
		bweak;
	case BCH_DATA_cached:
		bkey_fsck_eww_on(!a.v->cached_sectows ||
				 bch2_bucket_sectows_diwty(*a.v) ||
				 a.v->stwipe,
				 c, eww, awwoc_key_cached_inconsistency,
				 "data type inconsistency");

		bkey_fsck_eww_on(!a.v->io_time[WEAD] &&
				 c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_awwoc_to_wwu_wefs,
				 c, eww, awwoc_key_cached_but_wead_time_zewo,
				 "cached bucket with wead_time == 0");
		bweak;
	case BCH_DATA_stwipe:
		bweak;
	}
fsck_eww:
	wetuwn wet;
}

void bch2_awwoc_v4_swab(stwuct bkey_s k)
{
	stwuct bch_awwoc_v4 *a = bkey_s_to_awwoc_v4(k).v;
	stwuct bch_backpointew *bp, *bps;

	a->jouwnaw_seq		= swab64(a->jouwnaw_seq);
	a->fwags		= swab32(a->fwags);
	a->diwty_sectows	= swab32(a->diwty_sectows);
	a->cached_sectows	= swab32(a->cached_sectows);
	a->io_time[0]		= swab64(a->io_time[0]);
	a->io_time[1]		= swab64(a->io_time[1]);
	a->stwipe		= swab32(a->stwipe);
	a->nw_extewnaw_backpointews = swab32(a->nw_extewnaw_backpointews);
	a->fwagmentation_wwu	= swab64(a->fwagmentation_wwu);

	bps = awwoc_v4_backpointews(a);
	fow (bp = bps; bp < bps + BCH_AWWOC_V4_NW_BACKPOINTEWS(a); bp++) {
		bp->bucket_offset	= swab40(bp->bucket_offset);
		bp->bucket_wen		= swab32(bp->bucket_wen);
		bch2_bpos_swab(&bp->pos);
	}
}

void bch2_awwoc_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bch_awwoc_v4 _a;
	const stwuct bch_awwoc_v4 *a = bch2_awwoc_to_v4(k, &_a);

	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pwt_pwintf(out, "gen %u owdest_gen %u data_type ", a->gen, a->owdest_gen);
	bch2_pwt_data_type(out, a->data_type);
	pwt_newwine(out);
	pwt_pwintf(out, "jouwnaw_seq       %wwu",	a->jouwnaw_seq);
	pwt_newwine(out);
	pwt_pwintf(out, "need_discawd      %wwu",	BCH_AWWOC_V4_NEED_DISCAWD(a));
	pwt_newwine(out);
	pwt_pwintf(out, "need_inc_gen      %wwu",	BCH_AWWOC_V4_NEED_INC_GEN(a));
	pwt_newwine(out);
	pwt_pwintf(out, "diwty_sectows     %u",	a->diwty_sectows);
	pwt_newwine(out);
	pwt_pwintf(out, "cached_sectows    %u",	a->cached_sectows);
	pwt_newwine(out);
	pwt_pwintf(out, "stwipe            %u",	a->stwipe);
	pwt_newwine(out);
	pwt_pwintf(out, "stwipe_wedundancy %u",	a->stwipe_wedundancy);
	pwt_newwine(out);
	pwt_pwintf(out, "io_time[WEAD]     %wwu",	a->io_time[WEAD]);
	pwt_newwine(out);
	pwt_pwintf(out, "io_time[WWITE]    %wwu",	a->io_time[WWITE]);
	pwt_newwine(out);
	pwt_pwintf(out, "fwagmentation     %wwu",	a->fwagmentation_wwu);
	pwt_newwine(out);
	pwt_pwintf(out, "bp_stawt          %wwu", BCH_AWWOC_V4_BACKPOINTEWS_STAWT(a));
	pwintbuf_indent_sub(out, 2);
}

void __bch2_awwoc_to_v4(stwuct bkey_s_c k, stwuct bch_awwoc_v4 *out)
{
	if (k.k->type == KEY_TYPE_awwoc_v4) {
		void *swc, *dst;

		*out = *bkey_s_c_to_awwoc_v4(k).v;

		swc = awwoc_v4_backpointews(out);
		SET_BCH_AWWOC_V4_BACKPOINTEWS_STAWT(out, BCH_AWWOC_V4_U64s);
		dst = awwoc_v4_backpointews(out);

		if (swc < dst)
			memset(swc, 0, dst - swc);

		SET_BCH_AWWOC_V4_NW_BACKPOINTEWS(out, 0);
	} ewse {
		stwuct bkey_awwoc_unpacked u = bch2_awwoc_unpack(k);

		*out = (stwuct bch_awwoc_v4) {
			.jouwnaw_seq		= u.jouwnaw_seq,
			.fwags			= u.need_discawd,
			.gen			= u.gen,
			.owdest_gen		= u.owdest_gen,
			.data_type		= u.data_type,
			.stwipe_wedundancy	= u.stwipe_wedundancy,
			.diwty_sectows		= u.diwty_sectows,
			.cached_sectows		= u.cached_sectows,
			.io_time[WEAD]		= u.wead_time,
			.io_time[WWITE]		= u.wwite_time,
			.stwipe			= u.stwipe,
		};

		SET_BCH_AWWOC_V4_BACKPOINTEWS_STAWT(out, BCH_AWWOC_V4_U64s);
	}
}

static noinwine stwuct bkey_i_awwoc_v4 *
__bch2_awwoc_to_v4_mut(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	stwuct bkey_i_awwoc_v4 *wet;

	wet = bch2_twans_kmawwoc(twans, max(bkey_bytes(k.k), sizeof(stwuct bkey_i_awwoc_v4)));
	if (IS_EWW(wet))
		wetuwn wet;

	if (k.k->type == KEY_TYPE_awwoc_v4) {
		void *swc, *dst;

		bkey_weassembwe(&wet->k_i, k);

		swc = awwoc_v4_backpointews(&wet->v);
		SET_BCH_AWWOC_V4_BACKPOINTEWS_STAWT(&wet->v, BCH_AWWOC_V4_U64s);
		dst = awwoc_v4_backpointews(&wet->v);

		if (swc < dst)
			memset(swc, 0, dst - swc);

		SET_BCH_AWWOC_V4_NW_BACKPOINTEWS(&wet->v, 0);
		set_awwoc_v4_u64s(wet);
	} ewse {
		bkey_awwoc_v4_init(&wet->k_i);
		wet->k.p = k.k->p;
		bch2_awwoc_to_v4(k, &wet->v);
	}
	wetuwn wet;
}

static inwine stwuct bkey_i_awwoc_v4 *bch2_awwoc_to_v4_mut_inwined(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_awwoc_v4 a;

	if (wikewy(k.k->type == KEY_TYPE_awwoc_v4) &&
	    ((a = bkey_s_c_to_awwoc_v4(k), twue) &&
	     BCH_AWWOC_V4_NW_BACKPOINTEWS(a.v) == 0))
		wetuwn bch2_bkey_make_mut_noupdate_typed(twans, k, awwoc_v4);

	wetuwn __bch2_awwoc_to_v4_mut(twans, k);
}

stwuct bkey_i_awwoc_v4 *bch2_awwoc_to_v4_mut(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	wetuwn bch2_awwoc_to_v4_mut_inwined(twans, k);
}

stwuct bkey_i_awwoc_v4 *
bch2_twans_stawt_awwoc_update(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			      stwuct bpos pos)
{
	stwuct bkey_s_c k;
	stwuct bkey_i_awwoc_v4 *a;
	int wet;

	k = bch2_bkey_get_itew(twans, itew, BTWEE_ID_awwoc, pos,
			     BTWEE_ITEW_WITH_UPDATES|
			     BTWEE_ITEW_CACHED|
			     BTWEE_ITEW_INTENT);
	wet = bkey_eww(k);
	if (unwikewy(wet))
		wetuwn EWW_PTW(wet);

	a = bch2_awwoc_to_v4_mut_inwined(twans, k);
	wet = PTW_EWW_OW_ZEWO(a);
	if (unwikewy(wet))
		goto eww;
	wetuwn a;
eww:
	bch2_twans_itew_exit(twans, itew);
	wetuwn EWW_PTW(wet);
}

static stwuct bpos awwoc_gens_pos(stwuct bpos pos, unsigned *offset)
{
	*offset = pos.offset & KEY_TYPE_BUCKET_GENS_MASK;

	pos.offset >>= KEY_TYPE_BUCKET_GENS_BITS;
	wetuwn pos;
}

static stwuct bpos bucket_gens_pos_to_awwoc(stwuct bpos pos, unsigned offset)
{
	pos.offset <<= KEY_TYPE_BUCKET_GENS_BITS;
	pos.offset += offset;
	wetuwn pos;
}

static unsigned awwoc_gen(stwuct bkey_s_c k, unsigned offset)
{
	wetuwn k.k->type == KEY_TYPE_bucket_gens
		? bkey_s_c_to_bucket_gens(k).v->gens[offset]
		: 0;
}

int bch2_bucket_gens_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			     enum bkey_invawid_fwags fwags,
			     stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_bytes(k.k) != sizeof(stwuct bch_bucket_gens), c, eww,
			 bucket_gens_vaw_size_bad,
			 "bad vaw size (%zu != %zu)",
			 bkey_vaw_bytes(k.k), sizeof(stwuct bch_bucket_gens));
fsck_eww:
	wetuwn wet;
}

void bch2_bucket_gens_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_bucket_gens g = bkey_s_c_to_bucket_gens(k);
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(g.v->gens); i++) {
		if (i)
			pwt_chaw(out, ' ');
		pwt_pwintf(out, "%u", g.v->gens[i]);
	}
}

int bch2_bucket_gens_init(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct bkey_i_bucket_gens g;
	boow have_bucket_gens_key = fawse;
	int wet;

	wet = fow_each_btwee_key(twans, itew, BTWEE_ID_awwoc, POS_MIN,
				 BTWEE_ITEW_PWEFETCH, k, ({
		/*
		 * Not a fsck ewwow because this is checked/wepaiwed by
		 * bch2_check_awwoc_key() which wuns watew:
		 */
		if (!bch2_dev_bucket_exists(c, k.k->p))
			continue;

		stwuct bch_awwoc_v4 a;
		u8 gen = bch2_awwoc_to_v4(k, &a)->gen;
		unsigned offset;
		stwuct bpos pos = awwoc_gens_pos(itew.pos, &offset);

		if (have_bucket_gens_key && bkey_cmp(itew.pos, pos)) {
			wet = commit_do(twans, NUWW, NUWW,
					BCH_TWANS_COMMIT_no_enospc,
				bch2_btwee_insewt_twans(twans, BTWEE_ID_bucket_gens, &g.k_i, 0));
			if (wet)
				bweak;
			have_bucket_gens_key = fawse;
		}

		if (!have_bucket_gens_key) {
			bkey_bucket_gens_init(&g.k_i);
			g.k.p = pos;
			have_bucket_gens_key = twue;
		}

		g.v.gens[offset] = gen;
		0;
	}));

	if (have_bucket_gens_key && !wet)
		wet = commit_do(twans, NUWW, NUWW,
				BCH_TWANS_COMMIT_no_enospc,
			bch2_btwee_insewt_twans(twans, BTWEE_ID_bucket_gens, &g.k_i, 0));

	bch2_twans_put(twans);

	bch_eww_fn(c, wet);
	wetuwn wet;
}

int bch2_awwoc_wead(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	int wet;

	down_wead(&c->gc_wock);

	if (c->sb.vewsion_upgwade_compwete >= bcachefs_metadata_vewsion_bucket_gens) {
		wet = fow_each_btwee_key(twans, itew, BTWEE_ID_bucket_gens, POS_MIN,
					 BTWEE_ITEW_PWEFETCH, k, ({
			u64 stawt = bucket_gens_pos_to_awwoc(k.k->p, 0).offset;
			u64 end = bucket_gens_pos_to_awwoc(bpos_nosnap_successow(k.k->p), 0).offset;

			if (k.k->type != KEY_TYPE_bucket_gens)
				continue;

			const stwuct bch_bucket_gens *g = bkey_s_c_to_bucket_gens(k).v;

			/*
			 * Not a fsck ewwow because this is checked/wepaiwed by
			 * bch2_check_awwoc_key() which wuns watew:
			 */
			if (!bch2_dev_exists2(c, k.k->p.inode))
				continue;

			stwuct bch_dev *ca = bch_dev_bkey_exists(c, k.k->p.inode);

			fow (u64 b = max_t(u64, ca->mi.fiwst_bucket, stawt);
			     b < min_t(u64, ca->mi.nbuckets, end);
			     b++)
				*bucket_gen(ca, b) = g->gens[b & KEY_TYPE_BUCKET_GENS_MASK];
			0;
		}));
	} ewse {
		wet = fow_each_btwee_key(twans, itew, BTWEE_ID_awwoc, POS_MIN,
					 BTWEE_ITEW_PWEFETCH, k, ({
			/*
			 * Not a fsck ewwow because this is checked/wepaiwed by
			 * bch2_check_awwoc_key() which wuns watew:
			 */
			if (!bch2_dev_bucket_exists(c, k.k->p))
				continue;

			stwuct bch_dev *ca = bch_dev_bkey_exists(c, k.k->p.inode);

			stwuct bch_awwoc_v4 a;
			*bucket_gen(ca, k.k->p.offset) = bch2_awwoc_to_v4(k, &a)->gen;
			0;
		}));
	}

	bch2_twans_put(twans);
	up_wead(&c->gc_wock);

	bch_eww_fn(c, wet);
	wetuwn wet;
}

/* Fwee space/discawd btwee: */

static int bch2_bucket_do_index(stwuct btwee_twans *twans,
				stwuct bkey_s_c awwoc_k,
				const stwuct bch_awwoc_v4 *a,
				boow set)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, awwoc_k.k->p.inode);
	stwuct btwee_itew itew;
	stwuct bkey_s_c owd;
	stwuct bkey_i *k;
	enum btwee_id btwee;
	enum bch_bkey_type owd_type = !set ? KEY_TYPE_set : KEY_TYPE_deweted;
	enum bch_bkey_type new_type =  set ? KEY_TYPE_set : KEY_TYPE_deweted;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	if (a->data_type != BCH_DATA_fwee &&
	    a->data_type != BCH_DATA_need_discawd)
		wetuwn 0;

	k = bch2_twans_kmawwoc_nomemzewo(twans, sizeof(*k));
	if (IS_EWW(k))
		wetuwn PTW_EWW(k);

	bkey_init(&k->k);
	k->k.type = new_type;

	switch (a->data_type) {
	case BCH_DATA_fwee:
		btwee = BTWEE_ID_fweespace;
		k->k.p = awwoc_fweespace_pos(awwoc_k.k->p, *a);
		bch2_key_wesize(&k->k, 1);
		bweak;
	case BCH_DATA_need_discawd:
		btwee = BTWEE_ID_need_discawd;
		k->k.p = awwoc_k.k->p;
		bweak;
	defauwt:
		wetuwn 0;
	}

	owd = bch2_bkey_get_itew(twans, &itew, btwee,
			     bkey_stawt_pos(&k->k),
			     BTWEE_ITEW_INTENT);
	wet = bkey_eww(owd);
	if (wet)
		wetuwn wet;

	if (ca->mi.fweespace_initiawized &&
	    c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_awwoc_info &&
	    bch2_twans_inconsistent_on(owd.k->type != owd_type, twans,
			"incowwect key when %s %s:%wwu:%wwu:0 (got %s shouwd be %s)\n"
			"  fow %s",
			set ? "setting" : "cweawing",
			bch2_btwee_id_stw(btwee),
			itew.pos.inode,
			itew.pos.offset,
			bch2_bkey_types[owd.k->type],
			bch2_bkey_types[owd_type],
			(bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf))) {
		wet = -EIO;
		goto eww;
	}

	wet = bch2_twans_update(twans, &itew, k, 0);
eww:
	bch2_twans_itew_exit(twans, &itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static noinwine int bch2_bucket_gen_update(stwuct btwee_twans *twans,
					   stwuct bpos bucket, u8 gen)
{
	stwuct btwee_itew itew;
	unsigned offset;
	stwuct bpos pos = awwoc_gens_pos(bucket, &offset);
	stwuct bkey_i_bucket_gens *g;
	stwuct bkey_s_c k;
	int wet;

	g = bch2_twans_kmawwoc(twans, sizeof(*g));
	wet = PTW_EWW_OW_ZEWO(g);
	if (wet)
		wetuwn wet;

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_bucket_gens, pos,
			       BTWEE_ITEW_INTENT|
			       BTWEE_ITEW_WITH_UPDATES);
	wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	if (k.k->type != KEY_TYPE_bucket_gens) {
		bkey_bucket_gens_init(&g->k_i);
		g->k.p = itew.pos;
	} ewse {
		bkey_weassembwe(&g->k_i, k);
	}

	g->v.gens[offset] = gen;

	wet = bch2_twans_update(twans, &itew, &g->k_i, 0);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_twiggew_awwoc(stwuct btwee_twans *twans,
		       enum btwee_id btwee, unsigned wevew,
		       stwuct bkey_s_c owd, stwuct bkey_s new,
		       unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	if (bch2_twans_inconsistent_on(!bch2_dev_bucket_exists(c, new.k->p), twans,
				       "awwoc key fow invawid device ow bucket"))
		wetuwn -EIO;

	stwuct bch_dev *ca = bch_dev_bkey_exists(c, new.k->p.inode);

	stwuct bch_awwoc_v4 owd_a_convewt;
	const stwuct bch_awwoc_v4 *owd_a = bch2_awwoc_to_v4(owd, &owd_a_convewt);

	if (fwags & BTWEE_TWIGGEW_TWANSACTIONAW) {
		stwuct bch_awwoc_v4 *new_a = bkey_s_to_awwoc_v4(new).v;

		new_a->data_type = awwoc_data_type(*new_a, new_a->data_type);

		if (bch2_bucket_sectows(*new_a) > bch2_bucket_sectows(*owd_a)) {
			new_a->io_time[WEAD] = max_t(u64, 1, atomic64_wead(&c->io_cwock[WEAD].now));
			new_a->io_time[WWITE]= max_t(u64, 1, atomic64_wead(&c->io_cwock[WWITE].now));
			SET_BCH_AWWOC_V4_NEED_INC_GEN(new_a, twue);
			SET_BCH_AWWOC_V4_NEED_DISCAWD(new_a, twue);
		}

		if (data_type_is_empty(new_a->data_type) &&
		    BCH_AWWOC_V4_NEED_INC_GEN(new_a) &&
		    !bch2_bucket_is_open_safe(c, new.k->p.inode, new.k->p.offset)) {
			new_a->gen++;
			SET_BCH_AWWOC_V4_NEED_INC_GEN(new_a, fawse);
		}

		if (owd_a->data_type != new_a->data_type ||
		    (new_a->data_type == BCH_DATA_fwee &&
		     awwoc_fweespace_genbits(*owd_a) != awwoc_fweespace_genbits(*new_a))) {
			wet =   bch2_bucket_do_index(twans, owd, owd_a, fawse) ?:
				bch2_bucket_do_index(twans, new.s_c, new_a, twue);
			if (wet)
				wetuwn wet;
		}

		if (new_a->data_type == BCH_DATA_cached &&
		    !new_a->io_time[WEAD])
			new_a->io_time[WEAD] = max_t(u64, 1, atomic64_wead(&c->io_cwock[WEAD].now));

		u64 owd_wwu = awwoc_wwu_idx_wead(*owd_a);
		u64 new_wwu = awwoc_wwu_idx_wead(*new_a);
		if (owd_wwu != new_wwu) {
			wet = bch2_wwu_change(twans, new.k->p.inode,
					      bucket_to_u64(new.k->p),
					      owd_wwu, new_wwu);
			if (wet)
				wetuwn wet;
		}

		new_a->fwagmentation_wwu = awwoc_wwu_idx_fwagmentation(*new_a,
						bch_dev_bkey_exists(c, new.k->p.inode));
		if (owd_a->fwagmentation_wwu != new_a->fwagmentation_wwu) {
			wet = bch2_wwu_change(twans,
					BCH_WWU_FWAGMENTATION_STAWT,
					bucket_to_u64(new.k->p),
					owd_a->fwagmentation_wwu, new_a->fwagmentation_wwu);
			if (wet)
				wetuwn wet;
		}

		if (owd_a->gen != new_a->gen) {
			wet = bch2_bucket_gen_update(twans, new.k->p, new_a->gen);
			if (wet)
				wetuwn wet;
		}

		/*
		 * need to know if we'we getting cawwed fwom the invawidate path ow
		 * not:
		 */

		if ((fwags & BTWEE_TWIGGEW_BUCKET_INVAWIDATE) &&
		    owd_a->cached_sectows) {
			wet = bch2_update_cached_sectows_wist(twans, new.k->p.inode,
							      -((s64) owd_a->cached_sectows));
			if (wet)
				wetuwn wet;
		}
	}

	if ((fwags & BTWEE_TWIGGEW_ATOMIC) && (fwags & BTWEE_TWIGGEW_INSEWT)) {
		stwuct bch_awwoc_v4 *new_a = bkey_s_to_awwoc_v4(new).v;
		u64 jouwnaw_seq = twans->jouwnaw_wes.seq;
		u64 bucket_jouwnaw_seq = new_a->jouwnaw_seq;

		if ((fwags & BTWEE_TWIGGEW_INSEWT) &&
		    data_type_is_empty(owd_a->data_type) !=
		    data_type_is_empty(new_a->data_type) &&
		    new.k->type == KEY_TYPE_awwoc_v4) {
			stwuct bch_awwoc_v4 *v = bkey_s_to_awwoc_v4(new).v;

			/*
			 * If the btwee updates wefewwing to a bucket wewen't fwushed
			 * befowe the bucket became empty again, then the we don't have
			 * to wait on a jouwnaw fwush befowe we can weuse the bucket:
			 */
			v->jouwnaw_seq = bucket_jouwnaw_seq =
				data_type_is_empty(new_a->data_type) &&
				(jouwnaw_seq == v->jouwnaw_seq ||
				 bch2_jouwnaw_nofwush_seq(&c->jouwnaw, v->jouwnaw_seq))
				? 0 : jouwnaw_seq;
		}

		if (!data_type_is_empty(owd_a->data_type) &&
		    data_type_is_empty(new_a->data_type) &&
		    bucket_jouwnaw_seq) {
			wet = bch2_set_bucket_needs_jouwnaw_commit(&c->buckets_waiting_fow_jouwnaw,
					c->jouwnaw.fwushed_seq_ondisk,
					new.k->p.inode, new.k->p.offset,
					bucket_jouwnaw_seq);
			if (wet) {
				bch2_fs_fataw_ewwow(c,
					"ewwow setting bucket_needs_jouwnaw_commit: %i", wet);
				wetuwn wet;
			}
		}

		pewcpu_down_wead(&c->mawk_wock);
		if (new_a->gen != owd_a->gen)
			*bucket_gen(ca, new.k->p.offset) = new_a->gen;

		bch2_dev_usage_update(c, ca, owd_a, new_a, jouwnaw_seq, fawse);

		if (new_a->data_type == BCH_DATA_fwee &&
		    (!new_a->jouwnaw_seq || new_a->jouwnaw_seq < c->jouwnaw.fwushed_seq_ondisk))
			cwosuwe_wake_up(&c->fweewist_wait);

		if (new_a->data_type == BCH_DATA_need_discawd &&
		    (!bucket_jouwnaw_seq || bucket_jouwnaw_seq < c->jouwnaw.fwushed_seq_ondisk))
			bch2_do_discawds(c);

		if (owd_a->data_type != BCH_DATA_cached &&
		    new_a->data_type == BCH_DATA_cached &&
		    shouwd_invawidate_buckets(ca, bch2_dev_usage_wead(ca)))
			bch2_do_invawidates(c);

		if (new_a->data_type == BCH_DATA_need_gc_gens)
			bch2_do_gc_gens(c);
		pewcpu_up_wead(&c->mawk_wock);
	}

	if ((fwags & BTWEE_TWIGGEW_GC) &&
	    (fwags & BTWEE_TWIGGEW_BUCKET_INVAWIDATE)) {
		stwuct bch_awwoc_v4 new_a_convewt;
		const stwuct bch_awwoc_v4 *new_a = bch2_awwoc_to_v4(new.s_c, &new_a_convewt);

		pewcpu_down_wead(&c->mawk_wock);
		stwuct bucket *g = gc_bucket(ca, new.k->p.offset);

		bucket_wock(g);

		g->gen_vawid		= 1;
		g->gen			= new_a->gen;
		g->data_type		= new_a->data_type;
		g->stwipe		= new_a->stwipe;
		g->stwipe_wedundancy	= new_a->stwipe_wedundancy;
		g->diwty_sectows	= new_a->diwty_sectows;
		g->cached_sectows	= new_a->cached_sectows;

		bucket_unwock(g);
		pewcpu_up_wead(&c->mawk_wock);
	}

	wetuwn 0;
}

/*
 * This synthesizes deweted extents fow howes, simiwaw to BTWEE_ITEW_SWOTS fow
 * extents stywe btwees, but wowks on non-extents btwees:
 */
static stwuct bkey_s_c bch2_get_key_ow_howe(stwuct btwee_itew *itew, stwuct bpos end, stwuct bkey *howe)
{
	stwuct bkey_s_c k = bch2_btwee_itew_peek_swot(itew);

	if (bkey_eww(k))
		wetuwn k;

	if (k.k->type) {
		wetuwn k;
	} ewse {
		stwuct btwee_itew itew2;
		stwuct bpos next;

		bch2_twans_copy_itew(&itew2, itew);

		stwuct btwee_path *path = btwee_itew_path(itew->twans, itew);
		if (!bpos_eq(path->w[0].b->key.k.p, SPOS_MAX))
			end = bkey_min(end, bpos_nosnap_successow(path->w[0].b->key.k.p));

		end = bkey_min(end, POS(itew->pos.inode, itew->pos.offset + U32_MAX - 1));

		/*
		 * btwee node min/max is a cwosed intewvaw, upto takes a hawf
		 * open intewvaw:
		 */
		k = bch2_btwee_itew_peek_upto(&itew2, end);
		next = itew2.pos;
		bch2_twans_itew_exit(itew->twans, &itew2);

		BUG_ON(next.offset >= itew->pos.offset + U32_MAX);

		if (bkey_eww(k))
			wetuwn k;

		bkey_init(howe);
		howe->p = itew->pos;

		bch2_key_wesize(howe, next.offset - itew->pos.offset);
		wetuwn (stwuct bkey_s_c) { howe, NUWW };
	}
}

static boow next_bucket(stwuct bch_fs *c, stwuct bpos *bucket)
{
	stwuct bch_dev *ca;

	if (bch2_dev_bucket_exists(c, *bucket))
		wetuwn twue;

	if (bch2_dev_exists2(c, bucket->inode)) {
		ca = bch_dev_bkey_exists(c, bucket->inode);

		if (bucket->offset < ca->mi.fiwst_bucket) {
			bucket->offset = ca->mi.fiwst_bucket;
			wetuwn twue;
		}

		bucket->inode++;
		bucket->offset = 0;
	}

	wcu_wead_wock();
	ca = __bch2_next_dev_idx(c, bucket->inode, NUWW);
	if (ca)
		*bucket = POS(ca->dev_idx, ca->mi.fiwst_bucket);
	wcu_wead_unwock();

	wetuwn ca != NUWW;
}

static stwuct bkey_s_c bch2_get_key_ow_weaw_bucket_howe(stwuct btwee_itew *itew, stwuct bkey *howe)
{
	stwuct bch_fs *c = itew->twans->c;
	stwuct bkey_s_c k;
again:
	k = bch2_get_key_ow_howe(itew, POS_MAX, howe);
	if (bkey_eww(k))
		wetuwn k;

	if (!k.k->type) {
		stwuct bpos bucket = bkey_stawt_pos(k.k);

		if (!bch2_dev_bucket_exists(c, bucket)) {
			if (!next_bucket(c, &bucket))
				wetuwn bkey_s_c_nuww;

			bch2_btwee_itew_set_pos(itew, bucket);
			goto again;
		}

		if (!bch2_dev_bucket_exists(c, k.k->p)) {
			stwuct bch_dev *ca = bch_dev_bkey_exists(c, bucket.inode);

			bch2_key_wesize(howe, ca->mi.nbuckets - bucket.offset);
		}
	}

	wetuwn k;
}

static noinwine_fow_stack
int bch2_check_awwoc_key(stwuct btwee_twans *twans,
			 stwuct bkey_s_c awwoc_k,
			 stwuct btwee_itew *awwoc_itew,
			 stwuct btwee_itew *discawd_itew,
			 stwuct btwee_itew *fweespace_itew,
			 stwuct btwee_itew *bucket_gens_itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_dev *ca;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	unsigned discawd_key_type, fweespace_key_type;
	unsigned gens_offset;
	stwuct bkey_s_c k;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	if (fsck_eww_on(!bch2_dev_bucket_exists(c, awwoc_k.k->p), c,
			awwoc_key_to_missing_dev_bucket,
			"awwoc key fow invawid device:bucket %wwu:%wwu",
			awwoc_k.k->p.inode, awwoc_k.k->p.offset))
		wetuwn bch2_btwee_dewete_at(twans, awwoc_itew, 0);

	ca = bch_dev_bkey_exists(c, awwoc_k.k->p.inode);
	if (!ca->mi.fweespace_initiawized)
		wetuwn 0;

	a = bch2_awwoc_to_v4(awwoc_k, &a_convewt);

	discawd_key_type = a->data_type == BCH_DATA_need_discawd ? KEY_TYPE_set : 0;
	bch2_btwee_itew_set_pos(discawd_itew, awwoc_k.k->p);
	k = bch2_btwee_itew_peek_swot(discawd_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (k.k->type != discawd_key_type &&
	    (c->opts.weconstwuct_awwoc ||
	     fsck_eww(c, need_discawd_key_wwong,
		      "incowwect key in need_discawd btwee (got %s shouwd be %s)\n"
		      "  %s",
		      bch2_bkey_types[k.k->type],
		      bch2_bkey_types[discawd_key_type],
		      (bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf)))) {
		stwuct bkey_i *update =
			bch2_twans_kmawwoc(twans, sizeof(*update));

		wet = PTW_EWW_OW_ZEWO(update);
		if (wet)
			goto eww;

		bkey_init(&update->k);
		update->k.type	= discawd_key_type;
		update->k.p	= discawd_itew->pos;

		wet = bch2_twans_update(twans, discawd_itew, update, 0);
		if (wet)
			goto eww;
	}

	fweespace_key_type = a->data_type == BCH_DATA_fwee ? KEY_TYPE_set : 0;
	bch2_btwee_itew_set_pos(fweespace_itew, awwoc_fweespace_pos(awwoc_k.k->p, *a));
	k = bch2_btwee_itew_peek_swot(fweespace_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (k.k->type != fweespace_key_type &&
	    (c->opts.weconstwuct_awwoc ||
	     fsck_eww(c, fweespace_key_wwong,
		      "incowwect key in fweespace btwee (got %s shouwd be %s)\n"
		      "  %s",
		      bch2_bkey_types[k.k->type],
		      bch2_bkey_types[fweespace_key_type],
		      (pwintbuf_weset(&buf),
		       bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf)))) {
		stwuct bkey_i *update =
			bch2_twans_kmawwoc(twans, sizeof(*update));

		wet = PTW_EWW_OW_ZEWO(update);
		if (wet)
			goto eww;

		bkey_init(&update->k);
		update->k.type	= fweespace_key_type;
		update->k.p	= fweespace_itew->pos;
		bch2_key_wesize(&update->k, 1);

		wet = bch2_twans_update(twans, fweespace_itew, update, 0);
		if (wet)
			goto eww;
	}

	bch2_btwee_itew_set_pos(bucket_gens_itew, awwoc_gens_pos(awwoc_k.k->p, &gens_offset));
	k = bch2_btwee_itew_peek_swot(bucket_gens_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (a->gen != awwoc_gen(k, gens_offset) &&
	    (c->opts.weconstwuct_awwoc ||
	     fsck_eww(c, bucket_gens_key_wwong,
		      "incowwect gen in bucket_gens btwee (got %u shouwd be %u)\n"
		      "  %s",
		      awwoc_gen(k, gens_offset), a->gen,
		      (pwintbuf_weset(&buf),
		       bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf)))) {
		stwuct bkey_i_bucket_gens *g =
			bch2_twans_kmawwoc(twans, sizeof(*g));

		wet = PTW_EWW_OW_ZEWO(g);
		if (wet)
			goto eww;

		if (k.k->type == KEY_TYPE_bucket_gens) {
			bkey_weassembwe(&g->k_i, k);
		} ewse {
			bkey_bucket_gens_init(&g->k_i);
			g->k.p = awwoc_gens_pos(awwoc_k.k->p, &gens_offset);
		}

		g->v.gens[gens_offset] = a->gen;

		wet = bch2_twans_update(twans, bucket_gens_itew, &g->k_i, 0);
		if (wet)
			goto eww;
	}
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static noinwine_fow_stack
int bch2_check_awwoc_howe_fweespace(stwuct btwee_twans *twans,
				    stwuct bpos stawt,
				    stwuct bpos *end,
				    stwuct btwee_itew *fweespace_itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_dev *ca;
	stwuct bkey_s_c k;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	ca = bch_dev_bkey_exists(c, stawt.inode);
	if (!ca->mi.fweespace_initiawized)
		wetuwn 0;

	bch2_btwee_itew_set_pos(fweespace_itew, stawt);

	k = bch2_btwee_itew_peek_swot(fweespace_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	*end = bkey_min(k.k->p, *end);

	if (k.k->type != KEY_TYPE_set &&
	    (c->opts.weconstwuct_awwoc ||
	     fsck_eww(c, fweespace_howe_missing,
		      "howe in awwoc btwee missing in fweespace btwee\n"
		      "  device %wwu buckets %wwu-%wwu",
		      fweespace_itew->pos.inode,
		      fweespace_itew->pos.offset,
		      end->offset))) {
		stwuct bkey_i *update =
			bch2_twans_kmawwoc(twans, sizeof(*update));

		wet = PTW_EWW_OW_ZEWO(update);
		if (wet)
			goto eww;

		bkey_init(&update->k);
		update->k.type	= KEY_TYPE_set;
		update->k.p	= fweespace_itew->pos;
		bch2_key_wesize(&update->k,
				min_t(u64, U32_MAX, end->offset -
				      fweespace_itew->pos.offset));

		wet = bch2_twans_update(twans, fweespace_itew, update, 0);
		if (wet)
			goto eww;
	}
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static noinwine_fow_stack
int bch2_check_awwoc_howe_bucket_gens(stwuct btwee_twans *twans,
				      stwuct bpos stawt,
				      stwuct bpos *end,
				      stwuct btwee_itew *bucket_gens_itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c k;
	stwuct pwintbuf buf = PWINTBUF;
	unsigned i, gens_offset, gens_end_offset;
	int wet;

	bch2_btwee_itew_set_pos(bucket_gens_itew, awwoc_gens_pos(stawt, &gens_offset));

	k = bch2_btwee_itew_peek_swot(bucket_gens_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (bkey_cmp(awwoc_gens_pos(stawt, &gens_offset),
		     awwoc_gens_pos(*end,  &gens_end_offset)))
		gens_end_offset = KEY_TYPE_BUCKET_GENS_NW;

	if (k.k->type == KEY_TYPE_bucket_gens) {
		stwuct bkey_i_bucket_gens g;
		boow need_update = fawse;

		bkey_weassembwe(&g.k_i, k);

		fow (i = gens_offset; i < gens_end_offset; i++) {
			if (fsck_eww_on(g.v.gens[i], c,
					bucket_gens_howe_wwong,
					"howe in awwoc btwee at %wwu:%wwu with nonzewo gen in bucket_gens btwee (%u)",
					bucket_gens_pos_to_awwoc(k.k->p, i).inode,
					bucket_gens_pos_to_awwoc(k.k->p, i).offset,
					g.v.gens[i])) {
				g.v.gens[i] = 0;
				need_update = twue;
			}
		}

		if (need_update) {
			stwuct bkey_i *u = bch2_twans_kmawwoc(twans, sizeof(g));

			wet = PTW_EWW_OW_ZEWO(u);
			if (wet)
				goto eww;

			memcpy(u, &g, sizeof(g));

			wet = bch2_twans_update(twans, bucket_gens_itew, u, 0);
			if (wet)
				goto eww;
		}
	}

	*end = bkey_min(*end, bucket_gens_pos_to_awwoc(bpos_nosnap_successow(k.k->p), 0));
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static noinwine_fow_stack int bch2_check_discawd_fweespace_key(stwuct btwee_twans *twans,
					      stwuct btwee_itew *itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew awwoc_itew;
	stwuct bkey_s_c awwoc_k;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	u64 genbits;
	stwuct bpos pos;
	enum bch_data_type state = itew->btwee_id == BTWEE_ID_need_discawd
		? BCH_DATA_need_discawd
		: BCH_DATA_fwee;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	pos = itew->pos;
	pos.offset &= ~(~0UWW << 56);
	genbits = itew->pos.offset & (~0UWW << 56);

	awwoc_k = bch2_bkey_get_itew(twans, &awwoc_itew, BTWEE_ID_awwoc, pos, 0);
	wet = bkey_eww(awwoc_k);
	if (wet)
		wetuwn wet;

	if (fsck_eww_on(!bch2_dev_bucket_exists(c, pos), c,
			need_discawd_fweespace_key_to_invawid_dev_bucket,
			"entwy in %s btwee fow nonexistant dev:bucket %wwu:%wwu",
			bch2_btwee_id_stw(itew->btwee_id), pos.inode, pos.offset))
		goto dewete;

	a = bch2_awwoc_to_v4(awwoc_k, &a_convewt);

	if (fsck_eww_on(a->data_type != state ||
			(state == BCH_DATA_fwee &&
			 genbits != awwoc_fweespace_genbits(*a)), c,
			need_discawd_fweespace_key_bad,
			"%s\n  incowwectwy set at %s:%wwu:%wwu:0 (fwee %u, genbits %wwu shouwd be %wwu)",
			(bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf),
			bch2_btwee_id_stw(itew->btwee_id),
			itew->pos.inode,
			itew->pos.offset,
			a->data_type == state,
			genbits >> 56, awwoc_fweespace_genbits(*a) >> 56))
		goto dewete;
out:
fsck_eww:
	set_btwee_itew_dontneed(&awwoc_itew);
	bch2_twans_itew_exit(twans, &awwoc_itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
dewete:
	wet =   bch2_btwee_dewete_extent_at(twans, itew,
			itew->btwee_id == BTWEE_ID_fweespace ? 1 : 0, 0) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
			BCH_TWANS_COMMIT_no_enospc);
	goto out;
}

/*
 * We've awweady checked that genewation numbews in the bucket_gens btwee awe
 * vawid fow buckets that exist; this just checks fow keys fow nonexistent
 * buckets.
 */
static noinwine_fow_stack
int bch2_check_bucket_gens_key(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_i_bucket_gens g;
	stwuct bch_dev *ca;
	u64 stawt = bucket_gens_pos_to_awwoc(k.k->p, 0).offset;
	u64 end = bucket_gens_pos_to_awwoc(bpos_nosnap_successow(k.k->p), 0).offset;
	u64 b;
	boow need_update = fawse, dev_exists;
	stwuct pwintbuf buf = PWINTBUF;
	int wet = 0;

	BUG_ON(k.k->type != KEY_TYPE_bucket_gens);
	bkey_weassembwe(&g.k_i, k);

	/* if no bch_dev, skip out whethew we wepaiw ow not */
	dev_exists = bch2_dev_exists2(c, k.k->p.inode);
	if (!dev_exists) {
		if (fsck_eww_on(!dev_exists, c,
				bucket_gens_to_invawid_dev,
				"bucket_gens key fow invawid device:\n  %s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
			wet = bch2_btwee_dewete_at(twans, itew, 0);
		}
		goto out;
	}

	ca = bch_dev_bkey_exists(c, k.k->p.inode);
	if (fsck_eww_on(end <= ca->mi.fiwst_bucket ||
			stawt >= ca->mi.nbuckets, c,
			bucket_gens_to_invawid_buckets,
			"bucket_gens key fow invawid buckets:\n  %s",
			(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		wet = bch2_btwee_dewete_at(twans, itew, 0);
		goto out;
	}

	fow (b = stawt; b < ca->mi.fiwst_bucket; b++)
		if (fsck_eww_on(g.v.gens[b & KEY_TYPE_BUCKET_GENS_MASK], c,
				bucket_gens_nonzewo_fow_invawid_buckets,
				"bucket_gens key has nonzewo gen fow invawid bucket")) {
			g.v.gens[b & KEY_TYPE_BUCKET_GENS_MASK] = 0;
			need_update = twue;
		}

	fow (b = ca->mi.nbuckets; b < end; b++)
		if (fsck_eww_on(g.v.gens[b & KEY_TYPE_BUCKET_GENS_MASK], c,
				bucket_gens_nonzewo_fow_invawid_buckets,
				"bucket_gens key has nonzewo gen fow invawid bucket")) {
			g.v.gens[b & KEY_TYPE_BUCKET_GENS_MASK] = 0;
			need_update = twue;
		}

	if (need_update) {
		stwuct bkey_i *u = bch2_twans_kmawwoc(twans, sizeof(g));

		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			goto out;

		memcpy(u, &g, sizeof(g));
		wet = bch2_twans_update(twans, itew, u, 0);
	}
out:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

int bch2_check_awwoc_info(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew, discawd_itew, fweespace_itew, bucket_gens_itew;
	stwuct bkey howe;
	stwuct bkey_s_c k;
	int wet = 0;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_awwoc, POS_MIN,
			     BTWEE_ITEW_PWEFETCH);
	bch2_twans_itew_init(twans, &discawd_itew, BTWEE_ID_need_discawd, POS_MIN,
			     BTWEE_ITEW_PWEFETCH);
	bch2_twans_itew_init(twans, &fweespace_itew, BTWEE_ID_fweespace, POS_MIN,
			     BTWEE_ITEW_PWEFETCH);
	bch2_twans_itew_init(twans, &bucket_gens_itew, BTWEE_ID_bucket_gens, POS_MIN,
			     BTWEE_ITEW_PWEFETCH);

	whiwe (1) {
		stwuct bpos next;

		bch2_twans_begin(twans);

		k = bch2_get_key_ow_weaw_bucket_howe(&itew, &howe);
		wet = bkey_eww(k);
		if (wet)
			goto bkey_eww;

		if (!k.k)
			bweak;

		if (k.k->type) {
			next = bpos_nosnap_successow(k.k->p);

			wet = bch2_check_awwoc_key(twans,
						   k, &itew,
						   &discawd_itew,
						   &fweespace_itew,
						   &bucket_gens_itew);
			if (wet)
				goto bkey_eww;
		} ewse {
			next = k.k->p;

			wet = bch2_check_awwoc_howe_fweespace(twans,
						    bkey_stawt_pos(k.k),
						    &next,
						    &fweespace_itew) ?:
				bch2_check_awwoc_howe_bucket_gens(twans,
						    bkey_stawt_pos(k.k),
						    &next,
						    &bucket_gens_itew);
			if (wet)
				goto bkey_eww;
		}

		wet = bch2_twans_commit(twans, NUWW, NUWW,
					BCH_TWANS_COMMIT_no_enospc);
		if (wet)
			goto bkey_eww;

		bch2_btwee_itew_set_pos(&itew, next);
bkey_eww:
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			bweak;
	}
	bch2_twans_itew_exit(twans, &bucket_gens_itew);
	bch2_twans_itew_exit(twans, &fweespace_itew);
	bch2_twans_itew_exit(twans, &discawd_itew);
	bch2_twans_itew_exit(twans, &itew);

	if (wet < 0)
		goto eww;

	wet = fow_each_btwee_key(twans, itew,
			BTWEE_ID_need_discawd, POS_MIN,
			BTWEE_ITEW_PWEFETCH, k,
		bch2_check_discawd_fweespace_key(twans, &itew));
	if (wet)
		goto eww;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_fweespace, POS_MIN,
			     BTWEE_ITEW_PWEFETCH);
	whiwe (1) {
		bch2_twans_begin(twans);
		k = bch2_btwee_itew_peek(&itew);
		if (!k.k)
			bweak;

		wet = bkey_eww(k) ?:
			bch2_check_discawd_fweespace_key(twans, &itew);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
			wet = 0;
			continue;
		}
		if (wet) {
			stwuct pwintbuf buf = PWINTBUF;
			bch2_bkey_vaw_to_text(&buf, c, k);

			bch_eww(c, "whiwe checking %s", buf.buf);
			pwintbuf_exit(&buf);
			bweak;
		}

		bch2_btwee_itew_set_pos(&itew, bpos_nosnap_successow(itew.pos));
	}
	bch2_twans_itew_exit(twans, &itew);
	if (wet)
		goto eww;

	wet = fow_each_btwee_key_commit(twans, itew,
			BTWEE_ID_bucket_gens, POS_MIN,
			BTWEE_ITEW_PWEFETCH, k,
			NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
		bch2_check_bucket_gens_key(twans, &itew, k));
eww:
	bch2_twans_put(twans);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int bch2_check_awwoc_to_wwu_wef(stwuct btwee_twans *twans,
				       stwuct btwee_itew *awwoc_itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew wwu_itew;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	stwuct bkey_s_c awwoc_k, wwu_k;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	awwoc_k = bch2_btwee_itew_peek(awwoc_itew);
	if (!awwoc_k.k)
		wetuwn 0;

	wet = bkey_eww(awwoc_k);
	if (wet)
		wetuwn wet;

	a = bch2_awwoc_to_v4(awwoc_k, &a_convewt);

	if (a->data_type != BCH_DATA_cached)
		wetuwn 0;

	if (fsck_eww_on(!a->io_time[WEAD], c,
			awwoc_key_cached_but_wead_time_zewo,
			"cached bucket with wead_time 0\n"
			"  %s",
		(pwintbuf_weset(&buf),
		 bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf))) {
		stwuct bkey_i_awwoc_v4 *a_mut =
			bch2_awwoc_to_v4_mut(twans, awwoc_k);
		wet = PTW_EWW_OW_ZEWO(a_mut);
		if (wet)
			goto eww;

		a_mut->v.io_time[WEAD] = atomic64_wead(&c->io_cwock[WEAD].now);
		wet = bch2_twans_update(twans, awwoc_itew,
					&a_mut->k_i, BTWEE_TWIGGEW_NOWUN);
		if (wet)
			goto eww;

		a = &a_mut->v;
	}

	wwu_k = bch2_bkey_get_itew(twans, &wwu_itew, BTWEE_ID_wwu,
			     wwu_pos(awwoc_k.k->p.inode,
				     bucket_to_u64(awwoc_k.k->p),
				     a->io_time[WEAD]), 0);
	wet = bkey_eww(wwu_k);
	if (wet)
		wetuwn wet;

	if (fsck_eww_on(wwu_k.k->type != KEY_TYPE_set, c,
			awwoc_key_to_missing_wwu_entwy,
			"missing wwu entwy\n"
			"  %s",
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, awwoc_k), buf.buf))) {
		wet = bch2_wwu_set(twans,
				   awwoc_k.k->p.inode,
				   bucket_to_u64(awwoc_k.k->p),
				   a->io_time[WEAD]);
		if (wet)
			goto eww;
	}
eww:
fsck_eww:
	bch2_twans_itew_exit(twans, &wwu_itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
}

int bch2_check_awwoc_to_wwu_wefs(stwuct bch_fs *c)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_awwoc,
				POS_MIN, BTWEE_ITEW_PWEFETCH, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			bch2_check_awwoc_to_wwu_wef(twans, &itew)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

stwuct discawd_buckets_state {
	u64		seen;
	u64		open;
	u64		need_jouwnaw_commit;
	u64		discawded;
	stwuct bch_dev	*ca;
	u64		need_jouwnaw_commit_this_dev;
};

static void discawd_buckets_next_dev(stwuct bch_fs *c, stwuct discawd_buckets_state *s, stwuct bch_dev *ca)
{
	if (s->ca == ca)
		wetuwn;

	if (s->ca && s->need_jouwnaw_commit_this_dev >
	    bch2_dev_usage_wead(s->ca).d[BCH_DATA_fwee].buckets)
		bch2_jouwnaw_fwush_async(&c->jouwnaw, NUWW);

	if (s->ca)
		pewcpu_wef_put(&s->ca->wef);
	if (ca)
		pewcpu_wef_get(&ca->wef);
	s->ca = ca;
	s->need_jouwnaw_commit_this_dev = 0;
}

static int bch2_discawd_one_bucket(stwuct btwee_twans *twans,
				   stwuct btwee_itew *need_discawd_itew,
				   stwuct bpos *discawd_pos_done,
				   stwuct discawd_buckets_state *s)
{
	stwuct bch_fs *c = twans->c;
	stwuct bpos pos = need_discawd_itew->pos;
	stwuct btwee_itew itew = { NUWW };
	stwuct bkey_s_c k;
	stwuct bch_dev *ca;
	stwuct bkey_i_awwoc_v4 *a;
	stwuct pwintbuf buf = PWINTBUF;
	int wet = 0;

	ca = bch_dev_bkey_exists(c, pos.inode);

	if (!pewcpu_wef_twyget(&ca->io_wef)) {
		bch2_btwee_itew_set_pos(need_discawd_itew, POS(pos.inode + 1, 0));
		wetuwn 0;
	}

	discawd_buckets_next_dev(c, s, ca);

	if (bch2_bucket_is_open_safe(c, pos.inode, pos.offset)) {
		s->open++;
		goto out;
	}

	if (bch2_bucket_needs_jouwnaw_commit(&c->buckets_waiting_fow_jouwnaw,
			c->jouwnaw.fwushed_seq_ondisk,
			pos.inode, pos.offset)) {
		s->need_jouwnaw_commit++;
		s->need_jouwnaw_commit_this_dev++;
		goto out;
	}

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_awwoc,
			       need_discawd_itew->pos,
			       BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (wet)
		goto out;

	a = bch2_awwoc_to_v4_mut(twans, k);
	wet = PTW_EWW_OW_ZEWO(a);
	if (wet)
		goto out;

	if (BCH_AWWOC_V4_NEED_INC_GEN(&a->v)) {
		a->v.gen++;
		SET_BCH_AWWOC_V4_NEED_INC_GEN(&a->v, fawse);
		goto wwite;
	}

	if (a->v.jouwnaw_seq > c->jouwnaw.fwushed_seq_ondisk) {
		if (c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_awwoc_info) {
			bch2_twans_inconsistent(twans,
				"cweawing need_discawd but jouwnaw_seq %wwu > fwushed_seq %wwu\n"
				"%s",
				a->v.jouwnaw_seq,
				c->jouwnaw.fwushed_seq_ondisk,
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf));
			wet = -EIO;
		}
		goto out;
	}

	if (a->v.data_type != BCH_DATA_need_discawd) {
		if (c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_awwoc_info) {
			bch2_twans_inconsistent(twans,
				"bucket incowwectwy set in need_discawd btwee\n"
				"%s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf));
			wet = -EIO;
		}

		goto out;
	}

	if (!bkey_eq(*discawd_pos_done, itew.pos) &&
	    ca->mi.discawd && !c->opts.nochanges) {
		/*
		 * This wowks without any othew wocks because this is the onwy
		 * thwead that wemoves items fwom the need_discawd twee
		 */
		bch2_twans_unwock_wong(twans);
		bwkdev_issue_discawd(ca->disk_sb.bdev,
				     k.k->p.offset * ca->mi.bucket_size,
				     ca->mi.bucket_size,
				     GFP_KEWNEW);
		*discawd_pos_done = itew.pos;

		wet = bch2_twans_wewock_notwace(twans);
		if (wet)
			goto out;
	}

	SET_BCH_AWWOC_V4_NEED_DISCAWD(&a->v, fawse);
	a->v.data_type = awwoc_data_type(a->v, a->v.data_type);
wwite:
	wet =   bch2_twans_update(twans, &itew, &a->k_i, 0) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				  BCH_WATEWMAWK_btwee|
				  BCH_TWANS_COMMIT_no_enospc);
	if (wet)
		goto out;

	count_event(c, bucket_discawd);
	s->discawded++;
out:
	s->seen++;
	bch2_twans_itew_exit(twans, &itew);
	pewcpu_wef_put(&ca->io_wef);
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static void bch2_do_discawds_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c = containew_of(wowk, stwuct bch_fs, discawd_wowk);
	stwuct discawd_buckets_state s = {};
	stwuct bpos discawd_pos_done = POS_MAX;
	int wet;

	/*
	 * We'we doing the commit in bch2_discawd_one_bucket instead of using
	 * fow_each_btwee_key_commit() so that we can incwement countews aftew
	 * successfuw commit:
	 */
	wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew,
				   BTWEE_ID_need_discawd, POS_MIN, 0, k,
			bch2_discawd_one_bucket(twans, &itew, &discawd_pos_done, &s)));

	discawd_buckets_next_dev(c, &s, NUWW);

	twace_discawd_buckets(c, s.seen, s.open, s.need_jouwnaw_commit, s.discawded,
			      bch2_eww_stw(wet));

	bch2_wwite_wef_put(c, BCH_WWITE_WEF_discawd);
}

void bch2_do_discawds(stwuct bch_fs *c)
{
	if (bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_discawd) &&
	    !queue_wowk(c->wwite_wef_wq, &c->discawd_wowk))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_discawd);
}

static int invawidate_one_bucket(stwuct btwee_twans *twans,
				 stwuct btwee_itew *wwu_itew,
				 stwuct bkey_s_c wwu_k,
				 s64 *nw_to_invawidate)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew awwoc_itew = { NUWW };
	stwuct bkey_i_awwoc_v4 *a = NUWW;
	stwuct pwintbuf buf = PWINTBUF;
	stwuct bpos bucket = u64_to_bucket(wwu_k.k->p.offset);
	unsigned cached_sectows;
	int wet = 0;

	if (*nw_to_invawidate <= 0)
		wetuwn 1;

	if (!bch2_dev_bucket_exists(c, bucket)) {
		pwt_stw(&buf, "wwu entwy points to invawid bucket");
		goto eww;
	}

	if (bch2_bucket_is_open_safe(c, bucket.inode, bucket.offset))
		wetuwn 0;

	a = bch2_twans_stawt_awwoc_update(twans, &awwoc_itew, bucket);
	wet = PTW_EWW_OW_ZEWO(a);
	if (wet)
		goto out;

	/* We expect hawmwess waces hewe due to the btwee wwite buffew: */
	if (wwu_pos_time(wwu_itew->pos) != awwoc_wwu_idx_wead(a->v))
		goto out;

	BUG_ON(a->v.data_type != BCH_DATA_cached);

	if (!a->v.cached_sectows)
		bch_eww(c, "invawidating empty bucket, confused");

	cached_sectows = a->v.cached_sectows;

	SET_BCH_AWWOC_V4_NEED_INC_GEN(&a->v, fawse);
	a->v.gen++;
	a->v.data_type		= 0;
	a->v.diwty_sectows	= 0;
	a->v.cached_sectows	= 0;
	a->v.io_time[WEAD]	= atomic64_wead(&c->io_cwock[WEAD].now);
	a->v.io_time[WWITE]	= atomic64_wead(&c->io_cwock[WWITE].now);

	wet =   bch2_twans_update(twans, &awwoc_itew, &a->k_i,
				BTWEE_TWIGGEW_BUCKET_INVAWIDATE) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				  BCH_WATEWMAWK_btwee|
				  BCH_TWANS_COMMIT_no_enospc);
	if (wet)
		goto out;

	twace_and_count(c, bucket_invawidate, c, bucket.inode, bucket.offset, cached_sectows);
	--*nw_to_invawidate;
out:
	bch2_twans_itew_exit(twans, &awwoc_itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
eww:
	pwt_stw(&buf, "\n  wwu key: ");
	bch2_bkey_vaw_to_text(&buf, c, wwu_k);

	pwt_stw(&buf, "\n  wwu entwy: ");
	bch2_wwu_pos_to_text(&buf, wwu_itew->pos);

	pwt_stw(&buf, "\n  awwoc key: ");
	if (!a)
		bch2_bpos_to_text(&buf, bucket);
	ewse
		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(&a->k_i));

	bch_eww(c, "%s", buf.buf);
	if (c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_check_wwus) {
		bch2_inconsistent_ewwow(c);
		wet = -EINVAW;
	}

	goto out;
}

static void bch2_do_invawidates_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c = containew_of(wowk, stwuct bch_fs, invawidate_wowk);
	stwuct btwee_twans *twans = bch2_twans_get(c);
	int wet = 0;

	wet = bch2_btwee_wwite_buffew_twyfwush(twans);
	if (wet)
		goto eww;

	fow_each_membew_device(c, ca) {
		s64 nw_to_invawidate =
			shouwd_invawidate_buckets(ca, bch2_dev_usage_wead(ca));

		wet = fow_each_btwee_key_upto(twans, itew, BTWEE_ID_wwu,
				wwu_pos(ca->dev_idx, 0, 0),
				wwu_pos(ca->dev_idx, U64_MAX, WWU_TIME_MAX),
				BTWEE_ITEW_INTENT, k,
			invawidate_one_bucket(twans, &itew, k, &nw_to_invawidate));

		if (wet < 0) {
			pewcpu_wef_put(&ca->wef);
			bweak;
		}
	}
eww:
	bch2_twans_put(twans);
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_invawidate);
}

void bch2_do_invawidates(stwuct bch_fs *c)
{
	if (bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_invawidate) &&
	    !queue_wowk(c->wwite_wef_wq, &c->invawidate_wowk))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_invawidate);
}

int bch2_dev_fweespace_init(stwuct bch_fs *c, stwuct bch_dev *ca,
			    u64 bucket_stawt, u64 bucket_end)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bkey howe;
	stwuct bpos end = POS(ca->dev_idx, bucket_end);
	stwuct bch_membew *m;
	unsigned wong wast_updated = jiffies;
	int wet;

	BUG_ON(bucket_stawt > bucket_end);
	BUG_ON(bucket_end > ca->mi.nbuckets);

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_awwoc,
		POS(ca->dev_idx, max_t(u64, ca->mi.fiwst_bucket, bucket_stawt)),
		BTWEE_ITEW_PWEFETCH);
	/*
	 * Scan the awwoc btwee fow evewy bucket on @ca, and add buckets to the
	 * fweespace/need_discawd/need_gc_gens btwees as needed:
	 */
	whiwe (1) {
		if (wast_updated + HZ * 10 < jiffies) {
			bch_info(ca, "%s: cuwwentwy at %wwu/%wwu",
				 __func__, itew.pos.offset, ca->mi.nbuckets);
			wast_updated = jiffies;
		}

		bch2_twans_begin(twans);

		if (bkey_ge(itew.pos, end)) {
			wet = 0;
			bweak;
		}

		k = bch2_get_key_ow_howe(&itew, end, &howe);
		wet = bkey_eww(k);
		if (wet)
			goto bkey_eww;

		if (k.k->type) {
			/*
			 * We pwocess wive keys in the awwoc btwee one at a
			 * time:
			 */
			stwuct bch_awwoc_v4 a_convewt;
			const stwuct bch_awwoc_v4 *a = bch2_awwoc_to_v4(k, &a_convewt);

			wet =   bch2_bucket_do_index(twans, k, a, twue) ?:
				bch2_twans_commit(twans, NUWW, NUWW,
						  BCH_TWANS_COMMIT_no_enospc);
			if (wet)
				goto bkey_eww;

			bch2_btwee_itew_advance(&itew);
		} ewse {
			stwuct bkey_i *fweespace;

			fweespace = bch2_twans_kmawwoc(twans, sizeof(*fweespace));
			wet = PTW_EWW_OW_ZEWO(fweespace);
			if (wet)
				goto bkey_eww;

			bkey_init(&fweespace->k);
			fweespace->k.type	= KEY_TYPE_set;
			fweespace->k.p		= k.k->p;
			fweespace->k.size	= k.k->size;

			wet = bch2_btwee_insewt_twans(twans, BTWEE_ID_fweespace, fweespace, 0) ?:
				bch2_twans_commit(twans, NUWW, NUWW,
						  BCH_TWANS_COMMIT_no_enospc);
			if (wet)
				goto bkey_eww;

			bch2_btwee_itew_set_pos(&itew, k.k->p);
		}
bkey_eww:
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			bweak;
	}

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);

	if (wet < 0) {
		bch_eww_msg(ca, wet, "initiawizing fwee space");
		wetuwn wet;
	}

	mutex_wock(&c->sb_wock);
	m = bch2_membews_v2_get_mut(c->disk_sb.sb, ca->dev_idx);
	SET_BCH_MEMBEW_FWEESPACE_INITIAWIZED(m, twue);
	mutex_unwock(&c->sb_wock);

	wetuwn 0;
}

int bch2_fs_fweespace_init(stwuct bch_fs *c)
{
	int wet = 0;
	boow doing_init = fawse;

	/*
	 * We can cwash duwing the device add path, so we need to check this on
	 * evewy mount:
	 */

	fow_each_membew_device(c, ca) {
		if (ca->mi.fweespace_initiawized)
			continue;

		if (!doing_init) {
			bch_info(c, "initiawizing fweespace");
			doing_init = twue;
		}

		wet = bch2_dev_fweespace_init(c, ca, 0, ca->mi.nbuckets);
		if (wet) {
			pewcpu_wef_put(&ca->wef);
			bch_eww_fn(c, wet);
			wetuwn wet;
		}
	}

	if (doing_init) {
		mutex_wock(&c->sb_wock);
		bch2_wwite_supew(c);
		mutex_unwock(&c->sb_wock);
		bch_vewbose(c, "done initiawizing fweespace");
	}

	wetuwn 0;
}

/* Bucket IO cwocks: */

int bch2_bucket_io_time_weset(stwuct btwee_twans *twans, unsigned dev,
			      size_t bucket_nw, int ww)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_i_awwoc_v4 *a;
	u64 now;
	int wet = 0;

	a = bch2_twans_stawt_awwoc_update(twans, &itew,  POS(dev, bucket_nw));
	wet = PTW_EWW_OW_ZEWO(a);
	if (wet)
		wetuwn wet;

	now = atomic64_wead(&c->io_cwock[ww].now);
	if (a->v.io_time[ww] == now)
		goto out;

	a->v.io_time[ww] = now;

	wet   = bch2_twans_update(twans, &itew, &a->k_i, 0) ?:
		bch2_twans_commit(twans, NUWW, NUWW, 0);
out:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/* Stawtup/shutdown (wo/ww): */

void bch2_wecawc_capacity(stwuct bch_fs *c)
{
	u64 capacity = 0, wesewved_sectows = 0, gc_wesewve;
	unsigned bucket_size_max = 0;
	unsigned wong wa_pages = 0;

	wockdep_assewt_hewd(&c->state_wock);

	fow_each_onwine_membew(c, ca) {
		stwuct backing_dev_info *bdi = ca->disk_sb.bdev->bd_disk->bdi;

		wa_pages += bdi->wa_pages;
	}

	bch2_set_wa_pages(c, wa_pages);

	fow_each_ww_membew(c, ca) {
		u64 dev_wesewve = 0;

		/*
		 * We need to wesewve buckets (fwom the numbew
		 * of cuwwentwy avaiwabwe buckets) against
		 * fowegwound wwites so that mainwy copygc can
		 * make fowwawd pwogwess.
		 *
		 * We need enough to wefiww the vawious wesewves
		 * fwom scwatch - copygc wiww use its entiwe
		 * wesewve aww at once, then wun against when
		 * its wesewve is wefiwwed (fwom the fowmewwy
		 * avaiwabwe buckets).
		 *
		 * This wesewve is just used when considewing if
		 * awwocations fow fowegwound wwites must wait -
		 * not -ENOSPC cawcuwations.
		 */

		dev_wesewve += ca->nw_btwee_wesewve * 2;
		dev_wesewve += ca->mi.nbuckets >> 6; /* copygc wesewve */

		dev_wesewve += 1;	/* btwee wwite point */
		dev_wesewve += 1;	/* copygc wwite point */
		dev_wesewve += 1;	/* webawance wwite point */

		dev_wesewve *= ca->mi.bucket_size;

		capacity += bucket_to_sectow(ca, ca->mi.nbuckets -
					     ca->mi.fiwst_bucket);

		wesewved_sectows += dev_wesewve * 2;

		bucket_size_max = max_t(unsigned, bucket_size_max,
					ca->mi.bucket_size);
	}

	gc_wesewve = c->opts.gc_wesewve_bytes
		? c->opts.gc_wesewve_bytes >> 9
		: div64_u64(capacity * c->opts.gc_wesewve_pewcent, 100);

	wesewved_sectows = max(gc_wesewve, wesewved_sectows);

	wesewved_sectows = min(wesewved_sectows, capacity);

	c->capacity = capacity - wesewved_sectows;

	c->bucket_size_max = bucket_size_max;

	/* Wake up case someone was waiting fow buckets */
	cwosuwe_wake_up(&c->fweewist_wait);
}

u64 bch2_min_ww_membew_capacity(stwuct bch_fs *c)
{
	u64 wet = U64_MAX;

	fow_each_ww_membew(c, ca)
		wet = min(wet, ca->mi.nbuckets * ca->mi.bucket_size);
	wetuwn wet;
}

static boow bch2_dev_has_open_wwite_point(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	stwuct open_bucket *ob;
	boow wet = fawse;

	fow (ob = c->open_buckets;
	     ob < c->open_buckets + AWWAY_SIZE(c->open_buckets);
	     ob++) {
		spin_wock(&ob->wock);
		if (ob->vawid && !ob->on_pawtiaw_wist &&
		    ob->dev == ca->dev_idx)
			wet = twue;
		spin_unwock(&ob->wock);
	}

	wetuwn wet;
}

/* device goes wo: */
void bch2_dev_awwocatow_wemove(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	unsigned i;

	/* Fiwst, wemove device fwom awwocation gwoups: */

	fow (i = 0; i < AWWAY_SIZE(c->ww_devs); i++)
		cweaw_bit(ca->dev_idx, c->ww_devs[i].d);

	/*
	 * Capacity is cawcuwated based off of devices in awwocation gwoups:
	 */
	bch2_wecawc_capacity(c);

	bch2_open_buckets_stop(c, ca, fawse);

	/*
	 * Wake up thweads that wewe bwocked on awwocation, so they can notice
	 * the device can no wongew be wemoved and the capacity has changed:
	 */
	cwosuwe_wake_up(&c->fweewist_wait);

	/*
	 * jouwnaw_wes_get() can bwock waiting fow fwee space in the jouwnaw -
	 * it needs to notice thewe may not be devices to awwocate fwom anymowe:
	 */
	wake_up(&c->jouwnaw.wait);

	/* Now wait fow any in fwight wwites: */

	cwosuwe_wait_event(&c->open_buckets_wait,
			   !bch2_dev_has_open_wwite_point(c, ca));
}

/* device goes ww: */
void bch2_dev_awwocatow_add(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(c->ww_devs); i++)
		if (ca->mi.data_awwowed & (1 << i))
			set_bit(ca->dev_idx, c->ww_devs[i].d);
}

void bch2_fs_awwocatow_backgwound_init(stwuct bch_fs *c)
{
	spin_wock_init(&c->fweewist_wock);
	INIT_WOWK(&c->discawd_wowk, bch2_do_discawds_wowk);
	INIT_WOWK(&c->invawidate_wowk, bch2_do_invawidates_wowk);
}
