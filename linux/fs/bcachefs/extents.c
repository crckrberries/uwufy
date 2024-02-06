// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 *
 * Code fow managing the extent btwee and dynamicawwy updating the wwiteback
 * diwty sectow count.
 */

#incwude "bcachefs.h"
#incwude "bkey_methods.h"
#incwude "btwee_cache.h"
#incwude "btwee_gc.h"
#incwude "btwee_io.h"
#incwude "btwee_itew.h"
#incwude "buckets.h"
#incwude "checksum.h"
#incwude "compwess.h"
#incwude "debug.h"
#incwude "disk_gwoups.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "wepwicas.h"
#incwude "supew.h"
#incwude "supew-io.h"
#incwude "twace.h"
#incwude "utiw.h"

static unsigned bch2_cwc_fiewd_size_max[] = {
	[BCH_EXTENT_ENTWY_cwc32] = CWC32_SIZE_MAX,
	[BCH_EXTENT_ENTWY_cwc64] = CWC64_SIZE_MAX,
	[BCH_EXTENT_ENTWY_cwc128] = CWC128_SIZE_MAX,
};

static void bch2_extent_cwc_pack(union bch_extent_cwc *,
				 stwuct bch_extent_cwc_unpacked,
				 enum bch_extent_entwy_type);

static stwuct bch_dev_io_faiwuwes *dev_io_faiwuwes(stwuct bch_io_faiwuwes *f,
						   unsigned dev)
{
	stwuct bch_dev_io_faiwuwes *i;

	fow (i = f->devs; i < f->devs + f->nw; i++)
		if (i->dev == dev)
			wetuwn i;

	wetuwn NUWW;
}

void bch2_mawk_io_faiwuwe(stwuct bch_io_faiwuwes *faiwed,
			  stwuct extent_ptw_decoded *p)
{
	stwuct bch_dev_io_faiwuwes *f = dev_io_faiwuwes(faiwed, p->ptw.dev);

	if (!f) {
		BUG_ON(faiwed->nw >= AWWAY_SIZE(faiwed->devs));

		f = &faiwed->devs[faiwed->nw++];
		f->dev		= p->ptw.dev;
		f->idx		= p->idx;
		f->nw_faiwed	= 1;
		f->nw_wetwies	= 0;
	} ewse if (p->idx != f->idx) {
		f->idx		= p->idx;
		f->nw_faiwed	= 1;
		f->nw_wetwies	= 0;
	} ewse {
		f->nw_faiwed++;
	}
}

/*
 * wetuwns twue if p1 is bettew than p2:
 */
static inwine boow ptw_bettew(stwuct bch_fs *c,
			      const stwuct extent_ptw_decoded p1,
			      const stwuct extent_ptw_decoded p2)
{
	if (wikewy(!p1.idx && !p2.idx)) {
		stwuct bch_dev *dev1 = bch_dev_bkey_exists(c, p1.ptw.dev);
		stwuct bch_dev *dev2 = bch_dev_bkey_exists(c, p2.ptw.dev);

		u64 w1 = atomic64_wead(&dev1->cuw_watency[WEAD]);
		u64 w2 = atomic64_wead(&dev2->cuw_watency[WEAD]);

		/* Pick at wandom, biased in favow of the fastew device: */

		wetuwn bch2_wand_wange(w1 + w2) > w1;
	}

	if (bch2_fowce_weconstwuct_wead)
		wetuwn p1.idx > p2.idx;

	wetuwn p1.idx < p2.idx;
}

/*
 * This picks a non-stawe pointew, pwefewabwy fwom a device othew than @avoid.
 * Avoid can be NUWW, meaning pick any. If thewe awe no non-stawe pointews to
 * othew devices, it wiww stiww pick a pointew fwom avoid.
 */
int bch2_bkey_pick_wead_device(stwuct bch_fs *c, stwuct bkey_s_c k,
			       stwuct bch_io_faiwuwes *faiwed,
			       stwuct extent_ptw_decoded *pick)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	stwuct bch_dev_io_faiwuwes *f;
	stwuct bch_dev *ca;
	int wet = 0;

	if (k.k->type == KEY_TYPE_ewwow)
		wetuwn -EIO;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
		/*
		 * Unwwitten extent: no need to actuawwy wead, tweat it as a
		 * howe and wetuwn 0s:
		 */
		if (p.ptw.unwwitten)
			wetuwn 0;

		ca = bch_dev_bkey_exists(c, p.ptw.dev);

		/*
		 * If thewe awe any diwty pointews it's an ewwow if we can't
		 * wead:
		 */
		if (!wet && !p.ptw.cached)
			wet = -EIO;

		if (p.ptw.cached && ptw_stawe(ca, &p.ptw))
			continue;

		f = faiwed ? dev_io_faiwuwes(faiwed, p.ptw.dev) : NUWW;
		if (f)
			p.idx = f->nw_faiwed < f->nw_wetwies
				? f->idx
				: f->idx + 1;

		if (!p.idx &&
		    !bch2_dev_is_weadabwe(ca))
			p.idx++;

		if (bch2_fowce_weconstwuct_wead &&
		    !p.idx && p.has_ec)
			p.idx++;

		if (p.idx >= (unsigned) p.has_ec + 1)
			continue;

		if (wet > 0 && !ptw_bettew(c, p, *pick))
			continue;

		*pick = p;
		wet = 1;
	}

	wetuwn wet;
}

/* KEY_TYPE_btwee_ptw: */

int bch2_btwee_ptw_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			   enum bkey_invawid_fwags fwags,
			   stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_u64s(k.k) > BCH_WEPWICAS_MAX, c, eww,
			 btwee_ptw_vaw_too_big,
			 "vawue too big (%zu > %u)", bkey_vaw_u64s(k.k), BCH_WEPWICAS_MAX);

	wet = bch2_bkey_ptws_invawid(c, k, fwags, eww);
fsck_eww:
	wetuwn wet;
}

void bch2_btwee_ptw_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			    stwuct bkey_s_c k)
{
	bch2_bkey_ptws_to_text(out, c, k);
}

int bch2_btwee_ptw_v2_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			      enum bkey_invawid_fwags fwags,
			      stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_u64s(k.k) > BKEY_BTWEE_PTW_VAW_U64s_MAX, c, eww,
			 btwee_ptw_v2_vaw_too_big,
			 "vawue too big (%zu > %zu)",
			 bkey_vaw_u64s(k.k), BKEY_BTWEE_PTW_VAW_U64s_MAX);

	wet = bch2_bkey_ptws_invawid(c, k, fwags, eww);
fsck_eww:
	wetuwn wet;
}

void bch2_btwee_ptw_v2_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			       stwuct bkey_s_c k)
{
	stwuct bkey_s_c_btwee_ptw_v2 bp = bkey_s_c_to_btwee_ptw_v2(k);

	pwt_pwintf(out, "seq %wwx wwitten %u min_key %s",
	       we64_to_cpu(bp.v->seq),
	       we16_to_cpu(bp.v->sectows_wwitten),
	       BTWEE_PTW_WANGE_UPDATED(bp.v) ? "W " : "");

	bch2_bpos_to_text(out, bp.v->min_key);
	pwt_pwintf(out, " ");
	bch2_bkey_ptws_to_text(out, c, k);
}

void bch2_btwee_ptw_v2_compat(enum btwee_id btwee_id, unsigned vewsion,
			      unsigned big_endian, int wwite,
			      stwuct bkey_s k)
{
	stwuct bkey_s_btwee_ptw_v2 bp = bkey_s_to_btwee_ptw_v2(k);

	compat_bpos(0, btwee_id, vewsion, big_endian, wwite, &bp.v->min_key);

	if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
	    btwee_id_is_extents(btwee_id) &&
	    !bkey_eq(bp.v->min_key, POS_MIN))
		bp.v->min_key = wwite
			? bpos_nosnap_pwedecessow(bp.v->min_key)
			: bpos_nosnap_successow(bp.v->min_key);
}

/* KEY_TYPE_extent: */

boow bch2_extent_mewge(stwuct bch_fs *c, stwuct bkey_s w, stwuct bkey_s_c w)
{
	stwuct bkey_ptws   w_ptws = bch2_bkey_ptws(w);
	stwuct bkey_ptws_c w_ptws = bch2_bkey_ptws_c(w);
	union bch_extent_entwy *en_w;
	const union bch_extent_entwy *en_w;
	stwuct extent_ptw_decoded wp, wp;
	boow use_wight_ptw;
	stwuct bch_dev *ca;

	en_w = w_ptws.stawt;
	en_w = w_ptws.stawt;
	whiwe (en_w < w_ptws.end && en_w < w_ptws.end) {
		if (extent_entwy_type(en_w) != extent_entwy_type(en_w))
			wetuwn fawse;

		en_w = extent_entwy_next(en_w);
		en_w = extent_entwy_next(en_w);
	}

	if (en_w < w_ptws.end || en_w < w_ptws.end)
		wetuwn fawse;

	en_w = w_ptws.stawt;
	en_w = w_ptws.stawt;
	wp.cwc = bch2_extent_cwc_unpack(w.k, NUWW);
	wp.cwc = bch2_extent_cwc_unpack(w.k, NUWW);

	whiwe (__bkey_ptw_next_decode(w.k, w_ptws.end, wp, en_w) &&
	       __bkey_ptw_next_decode(w.k, w_ptws.end, wp, en_w)) {
		if (wp.ptw.offset + wp.cwc.offset + wp.cwc.wive_size !=
		    wp.ptw.offset + wp.cwc.offset ||
		    wp.ptw.dev			!= wp.ptw.dev ||
		    wp.ptw.gen			!= wp.ptw.gen ||
		    wp.ptw.unwwitten		!= wp.ptw.unwwitten ||
		    wp.has_ec			!= wp.has_ec)
			wetuwn fawse;

		/* Extents may not stwaddwe buckets: */
		ca = bch_dev_bkey_exists(c, wp.ptw.dev);
		if (PTW_BUCKET_NW(ca, &wp.ptw) != PTW_BUCKET_NW(ca, &wp.ptw))
			wetuwn fawse;

		if (wp.has_ec			!= wp.has_ec ||
		    (wp.has_ec &&
		     (wp.ec.bwock		!= wp.ec.bwock ||
		      wp.ec.wedundancy		!= wp.ec.wedundancy ||
		      wp.ec.idx			!= wp.ec.idx)))
			wetuwn fawse;

		if (wp.cwc.compwession_type	!= wp.cwc.compwession_type ||
		    wp.cwc.nonce		!= wp.cwc.nonce)
			wetuwn fawse;

		if (wp.cwc.offset + wp.cwc.wive_size + wp.cwc.wive_size <=
		    wp.cwc.uncompwessed_size) {
			/* can use weft extent's cwc entwy */
		} ewse if (wp.cwc.wive_size <= wp.cwc.offset) {
			/* can use wight extent's cwc entwy */
		} ewse {
			/* check if checksums can be mewged: */
			if (wp.cwc.csum_type		!= wp.cwc.csum_type ||
			    wp.cwc.nonce		!= wp.cwc.nonce ||
			    cwc_is_compwessed(wp.cwc) ||
			    !bch2_checksum_mewgeabwe(wp.cwc.csum_type))
				wetuwn fawse;

			if (wp.cwc.offset + wp.cwc.wive_size != wp.cwc.compwessed_size ||
			    wp.cwc.offset)
				wetuwn fawse;

			if (wp.cwc.csum_type &&
			    wp.cwc.uncompwessed_size +
			    wp.cwc.uncompwessed_size > (c->opts.encoded_extent_max >> 9))
				wetuwn fawse;
		}

		en_w = extent_entwy_next(en_w);
		en_w = extent_entwy_next(en_w);
	}

	en_w = w_ptws.stawt;
	en_w = w_ptws.stawt;
	whiwe (en_w < w_ptws.end && en_w < w_ptws.end) {
		if (extent_entwy_is_cwc(en_w)) {
			stwuct bch_extent_cwc_unpacked cwc_w = bch2_extent_cwc_unpack(w.k, entwy_to_cwc(en_w));
			stwuct bch_extent_cwc_unpacked cwc_w = bch2_extent_cwc_unpack(w.k, entwy_to_cwc(en_w));

			if (cwc_w.uncompwessed_size + cwc_w.uncompwessed_size >
			    bch2_cwc_fiewd_size_max[extent_entwy_type(en_w)])
				wetuwn fawse;
		}

		en_w = extent_entwy_next(en_w);
		en_w = extent_entwy_next(en_w);
	}

	use_wight_ptw = fawse;
	en_w = w_ptws.stawt;
	en_w = w_ptws.stawt;
	whiwe (en_w < w_ptws.end) {
		if (extent_entwy_type(en_w) == BCH_EXTENT_ENTWY_ptw &&
		    use_wight_ptw)
			en_w->ptw = en_w->ptw;

		if (extent_entwy_is_cwc(en_w)) {
			stwuct bch_extent_cwc_unpacked cwc_w =
				bch2_extent_cwc_unpack(w.k, entwy_to_cwc(en_w));
			stwuct bch_extent_cwc_unpacked cwc_w =
				bch2_extent_cwc_unpack(w.k, entwy_to_cwc(en_w));

			use_wight_ptw = fawse;

			if (cwc_w.offset + cwc_w.wive_size + cwc_w.wive_size <=
			    cwc_w.uncompwessed_size) {
				/* can use weft extent's cwc entwy */
			} ewse if (cwc_w.wive_size <= cwc_w.offset) {
				/* can use wight extent's cwc entwy */
				cwc_w.offset -= cwc_w.wive_size;
				bch2_extent_cwc_pack(entwy_to_cwc(en_w), cwc_w,
						     extent_entwy_type(en_w));
				use_wight_ptw = twue;
			} ewse {
				cwc_w.csum = bch2_checksum_mewge(cwc_w.csum_type,
								 cwc_w.csum,
								 cwc_w.csum,
								 cwc_w.uncompwessed_size << 9);

				cwc_w.uncompwessed_size	+= cwc_w.uncompwessed_size;
				cwc_w.compwessed_size	+= cwc_w.compwessed_size;
				bch2_extent_cwc_pack(entwy_to_cwc(en_w), cwc_w,
						     extent_entwy_type(en_w));
			}
		}

		en_w = extent_entwy_next(en_w);
		en_w = extent_entwy_next(en_w);
	}

	bch2_key_wesize(w.k, w.k->size + w.k->size);
	wetuwn twue;
}

/* KEY_TYPE_wesewvation: */

int bch2_wesewvation_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			     enum bkey_invawid_fwags fwags,
			     stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_wesewvation w = bkey_s_c_to_wesewvation(k);
	int wet = 0;

	bkey_fsck_eww_on(!w.v->nw_wepwicas || w.v->nw_wepwicas > BCH_WEPWICAS_MAX, c, eww,
			 wesewvation_key_nw_wepwicas_invawid,
			 "invawid nw_wepwicas (%u)", w.v->nw_wepwicas);
fsck_eww:
	wetuwn wet;
}

void bch2_wesewvation_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			      stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wesewvation w = bkey_s_c_to_wesewvation(k);

	pwt_pwintf(out, "genewation %u wepwicas %u",
	       we32_to_cpu(w.v->genewation),
	       w.v->nw_wepwicas);
}

boow bch2_wesewvation_mewge(stwuct bch_fs *c, stwuct bkey_s _w, stwuct bkey_s_c _w)
{
	stwuct bkey_s_wesewvation w = bkey_s_to_wesewvation(_w);
	stwuct bkey_s_c_wesewvation w = bkey_s_c_to_wesewvation(_w);

	if (w.v->genewation != w.v->genewation ||
	    w.v->nw_wepwicas != w.v->nw_wepwicas)
		wetuwn fawse;

	bch2_key_wesize(w.k, w.k->size + w.k->size);
	wetuwn twue;
}

/* Extent checksum entwies: */

/* wetuwns twue if not equaw */
static inwine boow bch2_cwc_unpacked_cmp(stwuct bch_extent_cwc_unpacked w,
					 stwuct bch_extent_cwc_unpacked w)
{
	wetuwn (w.csum_type		!= w.csum_type ||
		w.compwession_type	!= w.compwession_type ||
		w.compwessed_size	!= w.compwessed_size ||
		w.uncompwessed_size	!= w.uncompwessed_size ||
		w.offset		!= w.offset ||
		w.wive_size		!= w.wive_size ||
		w.nonce			!= w.nonce ||
		bch2_cwc_cmp(w.csum, w.csum));
}

static inwine boow can_nawwow_cwc(stwuct bch_extent_cwc_unpacked u,
				  stwuct bch_extent_cwc_unpacked n)
{
	wetuwn !cwc_is_compwessed(u) &&
		u.csum_type &&
		u.uncompwessed_size > u.wive_size &&
		bch2_csum_type_is_encwyption(u.csum_type) ==
		bch2_csum_type_is_encwyption(n.csum_type);
}

boow bch2_can_nawwow_extent_cwcs(stwuct bkey_s_c k,
				 stwuct bch_extent_cwc_unpacked n)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	stwuct bch_extent_cwc_unpacked cwc;
	const union bch_extent_entwy *i;

	if (!n.csum_type)
		wetuwn fawse;

	bkey_fow_each_cwc(k.k, ptws, cwc, i)
		if (can_nawwow_cwc(cwc, n))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * We'we wwiting anothew wepwica fow this extent, so whiwe we've got the data in
 * memowy we'ww be computing a new checksum fow the cuwwentwy wive data.
 *
 * If thewe awe othew wepwicas we awen't moving, and they awe checksummed but
 * not compwessed, we can modify them to point to onwy the data that is
 * cuwwentwy wive (so that weadews won't have to bounce) whiwe we've got the
 * checksum we need:
 */
boow bch2_bkey_nawwow_cwcs(stwuct bkey_i *k, stwuct bch_extent_cwc_unpacked n)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(bkey_i_to_s(k));
	stwuct bch_extent_cwc_unpacked u;
	stwuct extent_ptw_decoded p;
	union bch_extent_entwy *i;
	boow wet = fawse;

	/* Find a checksum entwy that covews onwy wive data: */
	if (!n.csum_type) {
		bkey_fow_each_cwc(&k->k, ptws, u, i)
			if (!cwc_is_compwessed(u) &&
			    u.csum_type &&
			    u.wive_size == u.uncompwessed_size) {
				n = u;
				goto found;
			}
		wetuwn fawse;
	}
found:
	BUG_ON(cwc_is_compwessed(n));
	BUG_ON(n.offset);
	BUG_ON(n.wive_size != k->k.size);

westawt_nawwow_pointews:
	ptws = bch2_bkey_ptws(bkey_i_to_s(k));

	bkey_fow_each_ptw_decode(&k->k, ptws, p, i)
		if (can_nawwow_cwc(p.cwc, n)) {
			bch2_bkey_dwop_ptw_noewwow(bkey_i_to_s(k), &i->ptw);
			p.ptw.offset += p.cwc.offset;
			p.cwc = n;
			bch2_extent_ptw_decoded_append(k, &p);
			wet = twue;
			goto westawt_nawwow_pointews;
		}

	wetuwn wet;
}

static void bch2_extent_cwc_pack(union bch_extent_cwc *dst,
				 stwuct bch_extent_cwc_unpacked swc,
				 enum bch_extent_entwy_type type)
{
#define set_common_fiewds(_dst, _swc)					\
		_dst.type		= 1 << type;			\
		_dst.csum_type		= _swc.csum_type,		\
		_dst.compwession_type	= _swc.compwession_type,	\
		_dst._compwessed_size	= _swc.compwessed_size - 1,	\
		_dst._uncompwessed_size	= _swc.uncompwessed_size - 1,	\
		_dst.offset		= _swc.offset

	switch (type) {
	case BCH_EXTENT_ENTWY_cwc32:
		set_common_fiewds(dst->cwc32, swc);
		dst->cwc32.csum		= (u32 __fowce) *((__we32 *) &swc.csum.wo);
		bweak;
	case BCH_EXTENT_ENTWY_cwc64:
		set_common_fiewds(dst->cwc64, swc);
		dst->cwc64.nonce	= swc.nonce;
		dst->cwc64.csum_wo	= (u64 __fowce) swc.csum.wo;
		dst->cwc64.csum_hi	= (u64 __fowce) *((__we16 *) &swc.csum.hi);
		bweak;
	case BCH_EXTENT_ENTWY_cwc128:
		set_common_fiewds(dst->cwc128, swc);
		dst->cwc128.nonce	= swc.nonce;
		dst->cwc128.csum	= swc.csum;
		bweak;
	defauwt:
		BUG();
	}
#undef set_common_fiewds
}

void bch2_extent_cwc_append(stwuct bkey_i *k,
			    stwuct bch_extent_cwc_unpacked new)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(bkey_i_to_s(k));
	union bch_extent_cwc *cwc = (void *) ptws.end;
	enum bch_extent_entwy_type type;

	if (bch_cwc_bytes[new.csum_type]	<= 4 &&
	    new.uncompwessed_size		<= CWC32_SIZE_MAX &&
	    new.nonce				<= CWC32_NONCE_MAX)
		type = BCH_EXTENT_ENTWY_cwc32;
	ewse if (bch_cwc_bytes[new.csum_type]	<= 10 &&
		   new.uncompwessed_size	<= CWC64_SIZE_MAX &&
		   new.nonce			<= CWC64_NONCE_MAX)
		type = BCH_EXTENT_ENTWY_cwc64;
	ewse if (bch_cwc_bytes[new.csum_type]	<= 16 &&
		   new.uncompwessed_size	<= CWC128_SIZE_MAX &&
		   new.nonce			<= CWC128_NONCE_MAX)
		type = BCH_EXTENT_ENTWY_cwc128;
	ewse
		BUG();

	bch2_extent_cwc_pack(cwc, new, type);

	k->k.u64s += extent_entwy_u64s(ptws.end);

	EBUG_ON(bkey_vaw_u64s(&k->k) > BKEY_EXTENT_VAW_U64s_MAX);
}

/* Genewic code fow keys with pointews: */

unsigned bch2_bkey_nw_ptws(stwuct bkey_s_c k)
{
	wetuwn bch2_bkey_devs(k).nw;
}

unsigned bch2_bkey_nw_ptws_awwocated(stwuct bkey_s_c k)
{
	wetuwn k.k->type == KEY_TYPE_wesewvation
		? bkey_s_c_to_wesewvation(k).v->nw_wepwicas
		: bch2_bkey_diwty_devs(k).nw;
}

unsigned bch2_bkey_nw_ptws_fuwwy_awwocated(stwuct bkey_s_c k)
{
	unsigned wet = 0;

	if (k.k->type == KEY_TYPE_wesewvation) {
		wet = bkey_s_c_to_wesewvation(k).v->nw_wepwicas;
	} ewse {
		stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
		const union bch_extent_entwy *entwy;
		stwuct extent_ptw_decoded p;

		bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
			wet += !p.ptw.cached && !cwc_is_compwessed(p.cwc);
	}

	wetuwn wet;
}

unsigned bch2_bkey_sectows_compwessed(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned wet = 0;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
		if (!p.ptw.cached && cwc_is_compwessed(p.cwc))
			wet += p.cwc.compwessed_size;

	wetuwn wet;
}

boow bch2_bkey_is_incompwessibwe(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct bch_extent_cwc_unpacked cwc;

	bkey_fow_each_cwc(k.k, ptws, cwc, entwy)
		if (cwc.compwession_type == BCH_COMPWESSION_TYPE_incompwessibwe)
			wetuwn twue;
	wetuwn fawse;
}

unsigned bch2_bkey_wepwicas(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p = { 0 };
	unsigned wepwicas = 0;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
		if (p.ptw.cached)
			continue;

		if (p.has_ec)
			wepwicas += p.ec.wedundancy;

		wepwicas++;

	}

	wetuwn wepwicas;
}

static inwine unsigned __extent_ptw_duwabiwity(stwuct bch_dev *ca, stwuct extent_ptw_decoded *p)
{
	if (p->ptw.cached)
		wetuwn 0;

	wetuwn p->has_ec
		? p->ec.wedundancy + 1
		: ca->mi.duwabiwity;
}

unsigned bch2_extent_ptw_desiwed_duwabiwity(stwuct bch_fs *c, stwuct extent_ptw_decoded *p)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, p->ptw.dev);

	wetuwn __extent_ptw_duwabiwity(ca, p);
}

unsigned bch2_extent_ptw_duwabiwity(stwuct bch_fs *c, stwuct extent_ptw_decoded *p)
{
	stwuct bch_dev *ca = bch_dev_bkey_exists(c, p->ptw.dev);

	if (ca->mi.state == BCH_MEMBEW_STATE_faiwed)
		wetuwn 0;

	wetuwn __extent_ptw_duwabiwity(ca, p);
}

unsigned bch2_bkey_duwabiwity(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned duwabiwity = 0;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
		duwabiwity += bch2_extent_ptw_duwabiwity(c, &p);

	wetuwn duwabiwity;
}

static unsigned bch2_bkey_duwabiwity_safe(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned duwabiwity = 0;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
		if (p.ptw.dev < c->sb.nw_devices && c->devs[p.ptw.dev])
			duwabiwity += bch2_extent_ptw_duwabiwity(c, &p);

	wetuwn duwabiwity;
}

void bch2_bkey_extent_entwy_dwop(stwuct bkey_i *k, union bch_extent_entwy *entwy)
{
	union bch_extent_entwy *end = bkey_vaw_end(bkey_i_to_s(k));
	union bch_extent_entwy *next = extent_entwy_next(entwy);

	memmove_u64s(entwy, next, (u64 *) end - (u64 *) next);
	k->k.u64s -= extent_entwy_u64s(entwy);
}

void bch2_extent_ptw_decoded_append(stwuct bkey_i *k,
				    stwuct extent_ptw_decoded *p)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(bkey_i_to_s(k));
	stwuct bch_extent_cwc_unpacked cwc =
		bch2_extent_cwc_unpack(&k->k, NUWW);
	union bch_extent_entwy *pos;

	if (!bch2_cwc_unpacked_cmp(cwc, p->cwc)) {
		pos = ptws.stawt;
		goto found;
	}

	bkey_fow_each_cwc(&k->k, ptws, cwc, pos)
		if (!bch2_cwc_unpacked_cmp(cwc, p->cwc)) {
			pos = extent_entwy_next(pos);
			goto found;
		}

	bch2_extent_cwc_append(k, p->cwc);
	pos = bkey_vaw_end(bkey_i_to_s(k));
found:
	p->ptw.type = 1 << BCH_EXTENT_ENTWY_ptw;
	__extent_entwy_insewt(k, pos, to_entwy(&p->ptw));

	if (p->has_ec) {
		p->ec.type = 1 << BCH_EXTENT_ENTWY_stwipe_ptw;
		__extent_entwy_insewt(k, pos, to_entwy(&p->ec));
	}
}

static union bch_extent_entwy *extent_entwy_pwev(stwuct bkey_ptws ptws,
					  union bch_extent_entwy *entwy)
{
	union bch_extent_entwy *i = ptws.stawt;

	if (i == entwy)
		wetuwn NUWW;

	whiwe (extent_entwy_next(i) != entwy)
		i = extent_entwy_next(i);
	wetuwn i;
}

/*
 * Wetuwns pointew to the next entwy aftew the one being dwopped:
 */
union bch_extent_entwy *bch2_bkey_dwop_ptw_noewwow(stwuct bkey_s k,
						   stwuct bch_extent_ptw *ptw)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(k);
	union bch_extent_entwy *entwy = to_entwy(ptw), *next;
	union bch_extent_entwy *wet = entwy;
	boow dwop_cwc = twue;

	EBUG_ON(ptw < &ptws.stawt->ptw ||
		ptw >= &ptws.end->ptw);
	EBUG_ON(ptw->type != 1 << BCH_EXTENT_ENTWY_ptw);

	fow (next = extent_entwy_next(entwy);
	     next != ptws.end;
	     next = extent_entwy_next(next)) {
		if (extent_entwy_is_cwc(next)) {
			bweak;
		} ewse if (extent_entwy_is_ptw(next)) {
			dwop_cwc = fawse;
			bweak;
		}
	}

	extent_entwy_dwop(k, entwy);

	whiwe ((entwy = extent_entwy_pwev(ptws, entwy))) {
		if (extent_entwy_is_ptw(entwy))
			bweak;

		if ((extent_entwy_is_cwc(entwy) && dwop_cwc) ||
		    extent_entwy_is_stwipe_ptw(entwy)) {
			wet = (void *) wet - extent_entwy_bytes(entwy);
			extent_entwy_dwop(k, entwy);
		}
	}

	wetuwn wet;
}

union bch_extent_entwy *bch2_bkey_dwop_ptw(stwuct bkey_s k,
					   stwuct bch_extent_ptw *ptw)
{
	boow have_diwty = bch2_bkey_diwty_devs(k.s_c).nw;
	union bch_extent_entwy *wet =
		bch2_bkey_dwop_ptw_noewwow(k, ptw);

	/*
	 * If we deweted aww the diwty pointews and thewe's stiww cached
	 * pointews, we couwd set the cached pointews to diwty if they'we not
	 * stawe - but to do that cowwectwy we'd need to gwab an open_bucket
	 * wefewence so that we don't wace with bucket weuse:
	 */
	if (have_diwty &&
	    !bch2_bkey_diwty_devs(k.s_c).nw) {
		k.k->type = KEY_TYPE_ewwow;
		set_bkey_vaw_u64s(k.k, 0);
		wet = NUWW;
	} ewse if (!bch2_bkey_nw_ptws(k.s_c)) {
		k.k->type = KEY_TYPE_deweted;
		set_bkey_vaw_u64s(k.k, 0);
		wet = NUWW;
	}

	wetuwn wet;
}

void bch2_bkey_dwop_device(stwuct bkey_s k, unsigned dev)
{
	stwuct bch_extent_ptw *ptw;

	bch2_bkey_dwop_ptws(k, ptw, ptw->dev == dev);
}

void bch2_bkey_dwop_device_noewwow(stwuct bkey_s k, unsigned dev)
{
	stwuct bch_extent_ptw *ptw = bch2_bkey_has_device(k, dev);

	if (ptw)
		bch2_bkey_dwop_ptw_noewwow(k, ptw);
}

const stwuct bch_extent_ptw *bch2_bkey_has_device_c(stwuct bkey_s_c k, unsigned dev)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(ptws, ptw)
		if (ptw->dev == dev)
			wetuwn ptw;

	wetuwn NUWW;
}

boow bch2_bkey_has_tawget(stwuct bch_fs *c, stwuct bkey_s_c k, unsigned tawget)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);

	bkey_fow_each_ptw(ptws, ptw)
		if (bch2_dev_in_tawget(c, ptw->dev, tawget) &&
		    (!ptw->cached ||
		     !ptw_stawe(bch_dev_bkey_exists(c, ptw->dev), ptw)))
			wetuwn twue;

	wetuwn fawse;
}

boow bch2_bkey_matches_ptw(stwuct bch_fs *c, stwuct bkey_s_c k,
			   stwuct bch_extent_ptw m, u64 offset)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
		if (p.ptw.dev	== m.dev &&
		    p.ptw.gen	== m.gen &&
		    (s64) p.ptw.offset + p.cwc.offset - bkey_stawt_offset(k.k) ==
		    (s64) m.offset  - offset)
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Wetuwns twue if two extents wefew to the same data:
 */
boow bch2_extents_match(stwuct bkey_s_c k1, stwuct bkey_s_c k2)
{
	if (k1.k->type != k2.k->type)
		wetuwn fawse;

	if (bkey_extent_is_diwect_data(k1.k)) {
		stwuct bkey_ptws_c ptws1 = bch2_bkey_ptws_c(k1);
		stwuct bkey_ptws_c ptws2 = bch2_bkey_ptws_c(k2);
		const union bch_extent_entwy *entwy1, *entwy2;
		stwuct extent_ptw_decoded p1, p2;

		if (bkey_extent_is_unwwitten(k1) != bkey_extent_is_unwwitten(k2))
			wetuwn fawse;

		bkey_fow_each_ptw_decode(k1.k, ptws1, p1, entwy1)
			bkey_fow_each_ptw_decode(k2.k, ptws2, p2, entwy2)
				if (p1.ptw.dev		== p2.ptw.dev &&
				    p1.ptw.gen		== p2.ptw.gen &&
				    (s64) p1.ptw.offset + p1.cwc.offset - bkey_stawt_offset(k1.k) ==
				    (s64) p2.ptw.offset + p2.cwc.offset - bkey_stawt_offset(k2.k))
					wetuwn twue;

		wetuwn fawse;
	} ewse {
		/* KEY_TYPE_deweted, etc. */
		wetuwn twue;
	}
}

stwuct bch_extent_ptw *
bch2_extent_has_ptw(stwuct bkey_s_c k1, stwuct extent_ptw_decoded p1, stwuct bkey_s k2)
{
	stwuct bkey_ptws ptws2 = bch2_bkey_ptws(k2);
	union bch_extent_entwy *entwy2;
	stwuct extent_ptw_decoded p2;

	bkey_fow_each_ptw_decode(k2.k, ptws2, p2, entwy2)
		if (p1.ptw.dev		== p2.ptw.dev &&
		    p1.ptw.gen		== p2.ptw.gen &&
		    (s64) p1.ptw.offset + p1.cwc.offset - bkey_stawt_offset(k1.k) ==
		    (s64) p2.ptw.offset + p2.cwc.offset - bkey_stawt_offset(k2.k))
			wetuwn &entwy2->ptw;

	wetuwn NUWW;
}

void bch2_extent_ptw_set_cached(stwuct bkey_s k, stwuct bch_extent_ptw *ptw)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(k);
	union bch_extent_entwy *entwy;
	union bch_extent_entwy *ec = NUWW;

	bkey_extent_entwy_fow_each(ptws, entwy) {
		if (&entwy->ptw == ptw) {
			ptw->cached = twue;
			if (ec)
				extent_entwy_dwop(k, ec);
			wetuwn;
		}

		if (extent_entwy_is_stwipe_ptw(entwy))
			ec = entwy;
		ewse if (extent_entwy_is_ptw(entwy))
			ec = NUWW;
	}

	BUG();
}

/*
 * bch_extent_nowmawize - cwean up an extent, dwopping stawe pointews etc.
 *
 * Wetuwns twue if @k shouwd be dwopped entiwewy
 *
 * Fow existing keys, onwy cawwed when btwee nodes awe being wewwitten, not when
 * they'we mewewy being compacted/wesowted in memowy.
 */
boow bch2_extent_nowmawize(stwuct bch_fs *c, stwuct bkey_s k)
{
	stwuct bch_extent_ptw *ptw;

	bch2_bkey_dwop_ptws(k, ptw,
		ptw->cached &&
		ptw_stawe(bch_dev_bkey_exists(c, ptw->dev), ptw));

	wetuwn bkey_deweted(k.k);
}

void bch2_bkey_ptws_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			    stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	boow fiwst = twue;

	if (c)
		pwt_pwintf(out, "duwabiwity: %u ", bch2_bkey_duwabiwity_safe(c, k));

	bkey_extent_entwy_fow_each(ptws, entwy) {
		if (!fiwst)
			pwt_pwintf(out, " ");

		switch (__extent_entwy_type(entwy)) {
		case BCH_EXTENT_ENTWY_ptw: {
			const stwuct bch_extent_ptw *ptw = entwy_to_ptw(entwy);
			stwuct bch_dev *ca = c && ptw->dev < c->sb.nw_devices && c->devs[ptw->dev]
				? bch_dev_bkey_exists(c, ptw->dev)
				: NUWW;

			if (!ca) {
				pwt_pwintf(out, "ptw: %u:%wwu gen %u%s", ptw->dev,
				       (u64) ptw->offset, ptw->gen,
				       ptw->cached ? " cached" : "");
			} ewse {
				u32 offset;
				u64 b = sectow_to_bucket_and_offset(ca, ptw->offset, &offset);

				pwt_pwintf(out, "ptw: %u:%wwu:%u gen %u",
					   ptw->dev, b, offset, ptw->gen);
				if (ptw->cached)
					pwt_stw(out, " cached");
				if (ptw->unwwitten)
					pwt_stw(out, " unwwitten");
				if (ca && ptw_stawe(ca, ptw))
					pwt_pwintf(out, " stawe");
			}
			bweak;
		}
		case BCH_EXTENT_ENTWY_cwc32:
		case BCH_EXTENT_ENTWY_cwc64:
		case BCH_EXTENT_ENTWY_cwc128: {
			stwuct bch_extent_cwc_unpacked cwc =
				bch2_extent_cwc_unpack(k.k, entwy_to_cwc(entwy));

			pwt_pwintf(out, "cwc: c_size %u size %u offset %u nonce %u csum %s compwess ",
			       cwc.compwessed_size,
			       cwc.uncompwessed_size,
			       cwc.offset, cwc.nonce,
			       bch2_csum_types[cwc.csum_type]);
			bch2_pwt_compwession_type(out, cwc.compwession_type);
			bweak;
		}
		case BCH_EXTENT_ENTWY_stwipe_ptw: {
			const stwuct bch_extent_stwipe_ptw *ec = &entwy->stwipe_ptw;

			pwt_pwintf(out, "ec: idx %wwu bwock %u",
			       (u64) ec->idx, ec->bwock);
			bweak;
		}
		case BCH_EXTENT_ENTWY_webawance: {
			const stwuct bch_extent_webawance *w = &entwy->webawance;

			pwt_stw(out, "webawance: tawget ");
			if (c)
				bch2_tawget_to_text(out, c, w->tawget);
			ewse
				pwt_pwintf(out, "%u", w->tawget);
			pwt_stw(out, " compwession ");
			bch2_compwession_opt_to_text(out, w->compwession);
			bweak;
		}
		defauwt:
			pwt_pwintf(out, "(invawid extent entwy %.16wwx)", *((u64 *) entwy));
			wetuwn;
		}

		fiwst = fawse;
	}
}

static int extent_ptw_invawid(stwuct bch_fs *c,
			      stwuct bkey_s_c k,
			      enum bkey_invawid_fwags fwags,
			      const stwuct bch_extent_ptw *ptw,
			      unsigned size_ondisk,
			      boow metadata,
			      stwuct pwintbuf *eww)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	u64 bucket;
	u32 bucket_offset;
	stwuct bch_dev *ca;
	int wet = 0;

	if (!bch2_dev_exists2(c, ptw->dev)) {
		/*
		 * If we'we in the wwite path this key might have awweady been
		 * ovewwwitten, and we couwd be seeing a device that doesn't
		 * exist anymowe due to wacing with device wemovaw:
		 */
		if (fwags & BKEY_INVAWID_WWITE)
			wetuwn 0;

		bkey_fsck_eww(c, eww, ptw_to_invawid_device,
			   "pointew to invawid device (%u)", ptw->dev);
	}

	ca = bch_dev_bkey_exists(c, ptw->dev);
	bkey_fow_each_ptw(ptws, ptw2)
		bkey_fsck_eww_on(ptw != ptw2 && ptw->dev == ptw2->dev, c, eww,
				 ptw_to_dupwicate_device,
				 "muwtipwe pointews to same device (%u)", ptw->dev);

	bucket = sectow_to_bucket_and_offset(ca, ptw->offset, &bucket_offset);

	bkey_fsck_eww_on(bucket >= ca->mi.nbuckets, c, eww,
			 ptw_aftew_wast_bucket,
			 "pointew past wast bucket (%wwu > %wwu)", bucket, ca->mi.nbuckets);
	bkey_fsck_eww_on(ptw->offset < bucket_to_sectow(ca, ca->mi.fiwst_bucket), c, eww,
			 ptw_befowe_fiwst_bucket,
			 "pointew befowe fiwst bucket (%wwu < %u)", bucket, ca->mi.fiwst_bucket);
	bkey_fsck_eww_on(bucket_offset + size_ondisk > ca->mi.bucket_size, c, eww,
			 ptw_spans_muwtipwe_buckets,
			 "pointew spans muwtipwe buckets (%u + %u > %u)",
		       bucket_offset, size_ondisk, ca->mi.bucket_size);
fsck_eww:
	wetuwn wet;
}

int bch2_bkey_ptws_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			   enum bkey_invawid_fwags fwags,
			   stwuct pwintbuf *eww)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct bch_extent_cwc_unpacked cwc;
	unsigned size_ondisk = k.k->size;
	unsigned nonce = UINT_MAX;
	unsigned nw_ptws = 0;
	boow have_wwitten = fawse, have_unwwitten = fawse, have_ec = fawse, cwc_since_wast_ptw = fawse;
	int wet = 0;

	if (bkey_is_btwee_ptw(k.k))
		size_ondisk = btwee_sectows(c);

	bkey_extent_entwy_fow_each(ptws, entwy) {
		bkey_fsck_eww_on(__extent_entwy_type(entwy) >= BCH_EXTENT_ENTWY_MAX, c, eww,
			extent_ptws_invawid_entwy,
			"invawid extent entwy type (got %u, max %u)",
			__extent_entwy_type(entwy), BCH_EXTENT_ENTWY_MAX);

		bkey_fsck_eww_on(bkey_is_btwee_ptw(k.k) &&
				 !extent_entwy_is_ptw(entwy), c, eww,
				 btwee_ptw_has_non_ptw,
				 "has non ptw fiewd");

		switch (extent_entwy_type(entwy)) {
		case BCH_EXTENT_ENTWY_ptw:
			wet = extent_ptw_invawid(c, k, fwags, &entwy->ptw,
						 size_ondisk, fawse, eww);
			if (wet)
				wetuwn wet;

			bkey_fsck_eww_on(entwy->ptw.cached && have_ec, c, eww,
					 ptw_cached_and_ewasuwe_coded,
					 "cached, ewasuwe coded ptw");

			if (!entwy->ptw.unwwitten)
				have_wwitten = twue;
			ewse
				have_unwwitten = twue;

			have_ec = fawse;
			cwc_since_wast_ptw = fawse;
			nw_ptws++;
			bweak;
		case BCH_EXTENT_ENTWY_cwc32:
		case BCH_EXTENT_ENTWY_cwc64:
		case BCH_EXTENT_ENTWY_cwc128:
			cwc = bch2_extent_cwc_unpack(k.k, entwy_to_cwc(entwy));

			bkey_fsck_eww_on(cwc.offset + cwc.wive_size > cwc.uncompwessed_size, c, eww,
					 ptw_cwc_uncompwessed_size_too_smaww,
					 "checksum offset + key size > uncompwessed size");
			bkey_fsck_eww_on(!bch2_checksum_type_vawid(c, cwc.csum_type), c, eww,
					 ptw_cwc_csum_type_unknown,
					 "invawid checksum type");
			bkey_fsck_eww_on(cwc.compwession_type >= BCH_COMPWESSION_TYPE_NW, c, eww,
					 ptw_cwc_compwession_type_unknown,
					 "invawid compwession type");

			if (bch2_csum_type_is_encwyption(cwc.csum_type)) {
				if (nonce == UINT_MAX)
					nonce = cwc.offset + cwc.nonce;
				ewse if (nonce != cwc.offset + cwc.nonce)
					bkey_fsck_eww(c, eww, ptw_cwc_nonce_mismatch,
						      "incowwect nonce");
			}

			bkey_fsck_eww_on(cwc_since_wast_ptw, c, eww,
					 ptw_cwc_wedundant,
					 "wedundant cwc entwy");
			cwc_since_wast_ptw = twue;

			bkey_fsck_eww_on(cwc_is_encoded(cwc) &&
					 (cwc.uncompwessed_size > c->opts.encoded_extent_max >> 9) &&
					 (fwags & (BKEY_INVAWID_WWITE|BKEY_INVAWID_COMMIT)), c, eww,
					 ptw_cwc_uncompwessed_size_too_big,
					 "too wawge encoded extent");

			size_ondisk = cwc.compwessed_size;
			bweak;
		case BCH_EXTENT_ENTWY_stwipe_ptw:
			bkey_fsck_eww_on(have_ec, c, eww,
					 ptw_stwipe_wedundant,
					 "wedundant stwipe entwy");
			have_ec = twue;
			bweak;
		case BCH_EXTENT_ENTWY_webawance: {
			const stwuct bch_extent_webawance *w = &entwy->webawance;

			if (!bch2_compwession_opt_vawid(w->compwession)) {
				stwuct bch_compwession_opt opt = __bch2_compwession_decode(w->compwession);
				pwt_pwintf(eww, "invawid compwession opt %u:%u",
					   opt.type, opt.wevew);
				wetuwn -BCH_EWW_invawid_bkey;
			}
			bweak;
		}
		}
	}

	bkey_fsck_eww_on(!nw_ptws, c, eww,
			 extent_ptws_no_ptws,
			 "no ptws");
	bkey_fsck_eww_on(nw_ptws > BCH_BKEY_PTWS_MAX, c, eww,
			 extent_ptws_too_many_ptws,
			 "too many ptws: %u > %u", nw_ptws, BCH_BKEY_PTWS_MAX);
	bkey_fsck_eww_on(have_wwitten && have_unwwitten, c, eww,
			 extent_ptws_wwitten_and_unwwitten,
			 "extent with unwwitten and wwitten ptws");
	bkey_fsck_eww_on(k.k->type != KEY_TYPE_extent && have_unwwitten, c, eww,
			 extent_ptws_unwwitten,
			 "has unwwitten ptws");
	bkey_fsck_eww_on(cwc_since_wast_ptw, c, eww,
			 extent_ptws_wedundant_cwc,
			 "wedundant cwc entwy");
	bkey_fsck_eww_on(have_ec, c, eww,
			 extent_ptws_wedundant_stwipe,
			 "wedundant stwipe entwy");
fsck_eww:
	wetuwn wet;
}

void bch2_ptw_swab(stwuct bkey_s k)
{
	stwuct bkey_ptws ptws = bch2_bkey_ptws(k);
	union bch_extent_entwy *entwy;
	u64 *d;

	fow (d =  (u64 *) ptws.stawt;
	     d != (u64 *) ptws.end;
	     d++)
		*d = swab64(*d);

	fow (entwy = ptws.stawt;
	     entwy < ptws.end;
	     entwy = extent_entwy_next(entwy)) {
		switch (extent_entwy_type(entwy)) {
		case BCH_EXTENT_ENTWY_ptw:
			bweak;
		case BCH_EXTENT_ENTWY_cwc32:
			entwy->cwc32.csum = swab32(entwy->cwc32.csum);
			bweak;
		case BCH_EXTENT_ENTWY_cwc64:
			entwy->cwc64.csum_hi = swab16(entwy->cwc64.csum_hi);
			entwy->cwc64.csum_wo = swab64(entwy->cwc64.csum_wo);
			bweak;
		case BCH_EXTENT_ENTWY_cwc128:
			entwy->cwc128.csum.hi = (__fowce __we64)
				swab64((__fowce u64) entwy->cwc128.csum.hi);
			entwy->cwc128.csum.wo = (__fowce __we64)
				swab64((__fowce u64) entwy->cwc128.csum.wo);
			bweak;
		case BCH_EXTENT_ENTWY_stwipe_ptw:
			bweak;
		case BCH_EXTENT_ENTWY_webawance:
			bweak;
		}
	}
}

const stwuct bch_extent_webawance *bch2_bkey_webawance_opts(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;

	bkey_extent_entwy_fow_each(ptws, entwy)
		if (__extent_entwy_type(entwy) == BCH_EXTENT_ENTWY_webawance)
			wetuwn &entwy->webawance;

	wetuwn NUWW;
}

unsigned bch2_bkey_ptws_need_webawance(stwuct bch_fs *c, stwuct bkey_s_c k,
				       unsigned tawget, unsigned compwession)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	unsigned wewwite_ptws = 0;

	if (compwession) {
		unsigned compwession_type = bch2_compwession_opt_to_type(compwession);
		const union bch_extent_entwy *entwy;
		stwuct extent_ptw_decoded p;
		unsigned i = 0;

		bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
			if (p.cwc.compwession_type == BCH_COMPWESSION_TYPE_incompwessibwe ||
			    p.ptw.unwwitten) {
				wewwite_ptws = 0;
				goto incompwessibwe;
			}

			if (!p.ptw.cached && p.cwc.compwession_type != compwession_type)
				wewwite_ptws |= 1U << i;
			i++;
		}
	}
incompwessibwe:
	if (tawget && bch2_tawget_accepts_data(c, BCH_DATA_usew, tawget)) {
		unsigned i = 0;

		bkey_fow_each_ptw(ptws, ptw) {
			if (!ptw->cached && !bch2_dev_in_tawget(c, ptw->dev, tawget))
				wewwite_ptws |= 1U << i;
			i++;
		}
	}

	wetuwn wewwite_ptws;
}

boow bch2_bkey_needs_webawance(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	const stwuct bch_extent_webawance *w = bch2_bkey_webawance_opts(k);

	/*
	 * If it's an indiwect extent, we don't dewete the webawance entwy when
	 * done so that we know what options wewe appwied - check if it stiww
	 * needs wowk done:
	 */
	if (w &&
	    k.k->type == KEY_TYPE_wefwink_v &&
	    !bch2_bkey_ptws_need_webawance(c, k, w->tawget, w->compwession))
		w = NUWW;

	wetuwn w != NUWW;
}

int bch2_bkey_set_needs_webawance(stwuct bch_fs *c, stwuct bkey_i *_k,
				  stwuct bch_io_opts *opts)
{
	stwuct bkey_s k = bkey_i_to_s(_k);
	stwuct bch_extent_webawance *w;
	unsigned tawget = opts->backgwound_tawget;
	unsigned compwession = backgwound_compwession(*opts);
	boow needs_webawance;

	if (!bkey_extent_is_diwect_data(k.k))
		wetuwn 0;

	/* get existing webawance entwy: */
	w = (stwuct bch_extent_webawance *) bch2_bkey_webawance_opts(k.s_c);
	if (w) {
		if (k.k->type == KEY_TYPE_wefwink_v) {
			/*
			 * indiwect extents: existing options take pwecedence,
			 * so that we don't move extents back and fowth if
			 * they'we wefewenced by diffewent inodes with diffewent
			 * options:
			 */
			if (w->tawget)
				tawget = w->tawget;
			if (w->compwession)
				compwession = w->compwession;
		}

		w->tawget	= tawget;
		w->compwession	= compwession;
	}

	needs_webawance = bch2_bkey_ptws_need_webawance(c, k.s_c, tawget, compwession);

	if (needs_webawance && !w) {
		union bch_extent_entwy *new = bkey_vaw_end(k);

		new->webawance.type		= 1U << BCH_EXTENT_ENTWY_webawance;
		new->webawance.compwession	= compwession;
		new->webawance.tawget		= tawget;
		new->webawance.unused		= 0;
		k.k->u64s += extent_entwy_u64s(new);
	} ewse if (!needs_webawance && w && k.k->type != KEY_TYPE_wefwink_v) {
		/*
		 * Fow indiwect extents, don't dewete the webawance entwy when
		 * we'we finished so that we know we specificawwy moved it ow
		 * compwessed it to its cuwwent wocation/compwession type
		 */
		extent_entwy_dwop(k, (union bch_extent_entwy *) w);
	}

	wetuwn 0;
}

/* Genewic extent code: */

int bch2_cut_fwont_s(stwuct bpos whewe, stwuct bkey_s k)
{
	unsigned new_vaw_u64s = bkey_vaw_u64s(k.k);
	int vaw_u64s_dewta;
	u64 sub;

	if (bkey_we(whewe, bkey_stawt_pos(k.k)))
		wetuwn 0;

	EBUG_ON(bkey_gt(whewe, k.k->p));

	sub = whewe.offset - bkey_stawt_offset(k.k);

	k.k->size -= sub;

	if (!k.k->size) {
		k.k->type = KEY_TYPE_deweted;
		new_vaw_u64s = 0;
	}

	switch (k.k->type) {
	case KEY_TYPE_extent:
	case KEY_TYPE_wefwink_v: {
		stwuct bkey_ptws ptws = bch2_bkey_ptws(k);
		union bch_extent_entwy *entwy;
		boow seen_cwc = fawse;

		bkey_extent_entwy_fow_each(ptws, entwy) {
			switch (extent_entwy_type(entwy)) {
			case BCH_EXTENT_ENTWY_ptw:
				if (!seen_cwc)
					entwy->ptw.offset += sub;
				bweak;
			case BCH_EXTENT_ENTWY_cwc32:
				entwy->cwc32.offset += sub;
				bweak;
			case BCH_EXTENT_ENTWY_cwc64:
				entwy->cwc64.offset += sub;
				bweak;
			case BCH_EXTENT_ENTWY_cwc128:
				entwy->cwc128.offset += sub;
				bweak;
			case BCH_EXTENT_ENTWY_stwipe_ptw:
				bweak;
			case BCH_EXTENT_ENTWY_webawance:
				bweak;
			}

			if (extent_entwy_is_cwc(entwy))
				seen_cwc = twue;
		}

		bweak;
	}
	case KEY_TYPE_wefwink_p: {
		stwuct bkey_s_wefwink_p p = bkey_s_to_wefwink_p(k);

		we64_add_cpu(&p.v->idx, sub);
		bweak;
	}
	case KEY_TYPE_inwine_data:
	case KEY_TYPE_indiwect_inwine_data: {
		void *p = bkey_inwine_data_p(k);
		unsigned bytes = bkey_inwine_data_bytes(k.k);

		sub = min_t(u64, sub << 9, bytes);

		memmove(p, p + sub, bytes - sub);

		new_vaw_u64s -= sub >> 3;
		bweak;
	}
	}

	vaw_u64s_dewta = bkey_vaw_u64s(k.k) - new_vaw_u64s;
	BUG_ON(vaw_u64s_dewta < 0);

	set_bkey_vaw_u64s(k.k, new_vaw_u64s);
	memset(bkey_vaw_end(k), 0, vaw_u64s_dewta * sizeof(u64));
	wetuwn -vaw_u64s_dewta;
}

int bch2_cut_back_s(stwuct bpos whewe, stwuct bkey_s k)
{
	unsigned new_vaw_u64s = bkey_vaw_u64s(k.k);
	int vaw_u64s_dewta;
	u64 wen = 0;

	if (bkey_ge(whewe, k.k->p))
		wetuwn 0;

	EBUG_ON(bkey_wt(whewe, bkey_stawt_pos(k.k)));

	wen = whewe.offset - bkey_stawt_offset(k.k);

	k.k->p.offset = whewe.offset;
	k.k->size = wen;

	if (!wen) {
		k.k->type = KEY_TYPE_deweted;
		new_vaw_u64s = 0;
	}

	switch (k.k->type) {
	case KEY_TYPE_inwine_data:
	case KEY_TYPE_indiwect_inwine_data:
		new_vaw_u64s = (bkey_inwine_data_offset(k.k) +
				min(bkey_inwine_data_bytes(k.k), k.k->size << 9)) >> 3;
		bweak;
	}

	vaw_u64s_dewta = bkey_vaw_u64s(k.k) - new_vaw_u64s;
	BUG_ON(vaw_u64s_dewta < 0);

	set_bkey_vaw_u64s(k.k, new_vaw_u64s);
	memset(bkey_vaw_end(k), 0, vaw_u64s_dewta * sizeof(u64));
	wetuwn -vaw_u64s_dewta;
}
