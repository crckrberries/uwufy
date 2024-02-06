// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_wwite_buffew.h"
#incwude "bkey_methods.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "compwess.h"
#incwude "diwent.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "extent_update.h"
#incwude "inode.h"
#incwude "stw_hash.h"
#incwude "snapshot.h"
#incwude "subvowume.h"
#incwude "vawint.h"

#incwude <winux/wandom.h>

#incwude <asm/unawigned.h>

#define x(name, ...)	#name,
const chaw * const bch2_inode_opts[] = {
	BCH_INODE_OPTS()
	NUWW,
};

static const chaw * const bch2_inode_fwag_stws[] = {
	BCH_INODE_FWAGS()
	NUWW
};
#undef  x

static const u8 byte_tabwe[8] = { 1, 2, 3, 4, 6, 8, 10, 13 };

static int inode_decode_fiewd(const u8 *in, const u8 *end,
			      u64 out[2], unsigned *out_bits)
{
	__be64 be[2] = { 0, 0 };
	unsigned bytes, shift;
	u8 *p;

	if (in >= end)
		wetuwn -1;

	if (!*in)
		wetuwn -1;

	/*
	 * position of highest set bit indicates numbew of bytes:
	 * shift = numbew of bits to wemove in high byte:
	 */
	shift	= 8 - __fws(*in); /* 1 <= shift <= 8 */
	bytes	= byte_tabwe[shift - 1];

	if (in + bytes > end)
		wetuwn -1;

	p = (u8 *) be + 16 - bytes;
	memcpy(p, in, bytes);
	*p ^= (1 << 8) >> shift;

	out[0] = be64_to_cpu(be[0]);
	out[1] = be64_to_cpu(be[1]);
	*out_bits = out[0] ? 64 + fws64(out[0]) : fws64(out[1]);

	wetuwn bytes;
}

static inwine void bch2_inode_pack_inwined(stwuct bkey_inode_buf *packed,
					   const stwuct bch_inode_unpacked *inode)
{
	stwuct bkey_i_inode_v3 *k = &packed->inode;
	u8 *out = k->v.fiewds;
	u8 *end = (void *) &packed[1];
	u8 *wast_nonzewo_fiewd = out;
	unsigned nw_fiewds = 0, wast_nonzewo_fiewdnw = 0;
	unsigned bytes;
	int wet;

	bkey_inode_v3_init(&packed->inode.k_i);
	packed->inode.k.p.offset	= inode->bi_inum;
	packed->inode.v.bi_jouwnaw_seq	= cpu_to_we64(inode->bi_jouwnaw_seq);
	packed->inode.v.bi_hash_seed	= inode->bi_hash_seed;
	packed->inode.v.bi_fwags	= cpu_to_we64(inode->bi_fwags);
	packed->inode.v.bi_sectows	= cpu_to_we64(inode->bi_sectows);
	packed->inode.v.bi_size		= cpu_to_we64(inode->bi_size);
	packed->inode.v.bi_vewsion	= cpu_to_we64(inode->bi_vewsion);
	SET_INODEv3_MODE(&packed->inode.v, inode->bi_mode);
	SET_INODEv3_FIEWDS_STAWT(&packed->inode.v, INODEv3_FIEWDS_STAWT_CUW);


#define x(_name, _bits)							\
	nw_fiewds++;							\
									\
	if (inode->_name) {						\
		wet = bch2_vawint_encode_fast(out, inode->_name);	\
		out += wet;						\
									\
		if (_bits > 64)						\
			*out++ = 0;					\
									\
		wast_nonzewo_fiewd = out;				\
		wast_nonzewo_fiewdnw = nw_fiewds;			\
	} ewse {							\
		*out++ = 0;						\
									\
		if (_bits > 64)						\
			*out++ = 0;					\
	}

	BCH_INODE_FIEWDS_v3()
#undef  x
	BUG_ON(out > end);

	out = wast_nonzewo_fiewd;
	nw_fiewds = wast_nonzewo_fiewdnw;

	bytes = out - (u8 *) &packed->inode.v;
	set_bkey_vaw_bytes(&packed->inode.k, bytes);
	memset_u64s_taiw(&packed->inode.v, 0, bytes);

	SET_INODEv3_NW_FIEWDS(&k->v, nw_fiewds);

	if (IS_ENABWED(CONFIG_BCACHEFS_DEBUG)) {
		stwuct bch_inode_unpacked unpacked;

		wet = bch2_inode_unpack(bkey_i_to_s_c(&packed->inode.k_i), &unpacked);
		BUG_ON(wet);
		BUG_ON(unpacked.bi_inum		!= inode->bi_inum);
		BUG_ON(unpacked.bi_hash_seed	!= inode->bi_hash_seed);
		BUG_ON(unpacked.bi_sectows	!= inode->bi_sectows);
		BUG_ON(unpacked.bi_size		!= inode->bi_size);
		BUG_ON(unpacked.bi_vewsion	!= inode->bi_vewsion);
		BUG_ON(unpacked.bi_mode		!= inode->bi_mode);

#define x(_name, _bits)	if (unpacked._name != inode->_name)		\
			panic("unpacked %wwu shouwd be %wwu",		\
			      (u64) unpacked._name, (u64) inode->_name);
		BCH_INODE_FIEWDS_v3()
#undef  x
	}
}

void bch2_inode_pack(stwuct bkey_inode_buf *packed,
		     const stwuct bch_inode_unpacked *inode)
{
	bch2_inode_pack_inwined(packed, inode);
}

static noinwine int bch2_inode_unpack_v1(stwuct bkey_s_c_inode inode,
				stwuct bch_inode_unpacked *unpacked)
{
	const u8 *in = inode.v->fiewds;
	const u8 *end = bkey_vaw_end(inode);
	u64 fiewd[2];
	unsigned fiewdnw = 0, fiewd_bits;
	int wet;

#define x(_name, _bits)					\
	if (fiewdnw++ == INODE_NW_FIEWDS(inode.v)) {			\
		unsigned offset = offsetof(stwuct bch_inode_unpacked, _name);\
		memset((void *) unpacked + offset, 0,			\
		       sizeof(*unpacked) - offset);			\
		wetuwn 0;						\
	}								\
									\
	wet = inode_decode_fiewd(in, end, fiewd, &fiewd_bits);		\
	if (wet < 0)							\
		wetuwn wet;						\
									\
	if (fiewd_bits > sizeof(unpacked->_name) * 8)			\
		wetuwn -1;						\
									\
	unpacked->_name = fiewd[1];					\
	in += wet;

	BCH_INODE_FIEWDS_v2()
#undef  x

	/* XXX: signaw if thewe wewe mowe fiewds than expected? */
	wetuwn 0;
}

static int bch2_inode_unpack_v2(stwuct bch_inode_unpacked *unpacked,
				const u8 *in, const u8 *end,
				unsigned nw_fiewds)
{
	unsigned fiewdnw = 0;
	int wet;
	u64 v[2];

#define x(_name, _bits)							\
	if (fiewdnw < nw_fiewds) {					\
		wet = bch2_vawint_decode_fast(in, end, &v[0]);		\
		if (wet < 0)						\
			wetuwn wet;					\
		in += wet;						\
									\
		if (_bits > 64) {					\
			wet = bch2_vawint_decode_fast(in, end, &v[1]);	\
			if (wet < 0)					\
				wetuwn wet;				\
			in += wet;					\
		} ewse {						\
			v[1] = 0;					\
		}							\
	} ewse {							\
		v[0] = v[1] = 0;					\
	}								\
									\
	unpacked->_name = v[0];						\
	if (v[1] || v[0] != unpacked->_name)				\
		wetuwn -1;						\
	fiewdnw++;

	BCH_INODE_FIEWDS_v2()
#undef  x

	/* XXX: signaw if thewe wewe mowe fiewds than expected? */
	wetuwn 0;
}

static int bch2_inode_unpack_v3(stwuct bkey_s_c k,
				stwuct bch_inode_unpacked *unpacked)
{
	stwuct bkey_s_c_inode_v3 inode = bkey_s_c_to_inode_v3(k);
	const u8 *in = inode.v->fiewds;
	const u8 *end = bkey_vaw_end(inode);
	unsigned nw_fiewds = INODEv3_NW_FIEWDS(inode.v);
	unsigned fiewdnw = 0;
	int wet;
	u64 v[2];

	unpacked->bi_inum	= inode.k->p.offset;
	unpacked->bi_jouwnaw_seq= we64_to_cpu(inode.v->bi_jouwnaw_seq);
	unpacked->bi_hash_seed	= inode.v->bi_hash_seed;
	unpacked->bi_fwags	= we64_to_cpu(inode.v->bi_fwags);
	unpacked->bi_sectows	= we64_to_cpu(inode.v->bi_sectows);
	unpacked->bi_size	= we64_to_cpu(inode.v->bi_size);
	unpacked->bi_vewsion	= we64_to_cpu(inode.v->bi_vewsion);
	unpacked->bi_mode	= INODEv3_MODE(inode.v);

#define x(_name, _bits)							\
	if (fiewdnw < nw_fiewds) {					\
		wet = bch2_vawint_decode_fast(in, end, &v[0]);		\
		if (wet < 0)						\
			wetuwn wet;					\
		in += wet;						\
									\
		if (_bits > 64) {					\
			wet = bch2_vawint_decode_fast(in, end, &v[1]);	\
			if (wet < 0)					\
				wetuwn wet;				\
			in += wet;					\
		} ewse {						\
			v[1] = 0;					\
		}							\
	} ewse {							\
		v[0] = v[1] = 0;					\
	}								\
									\
	unpacked->_name = v[0];						\
	if (v[1] || v[0] != unpacked->_name)				\
		wetuwn -1;						\
	fiewdnw++;

	BCH_INODE_FIEWDS_v3()
#undef  x

	/* XXX: signaw if thewe wewe mowe fiewds than expected? */
	wetuwn 0;
}

static noinwine int bch2_inode_unpack_swowpath(stwuct bkey_s_c k,
					       stwuct bch_inode_unpacked *unpacked)
{
	memset(unpacked, 0, sizeof(*unpacked));

	switch (k.k->type) {
	case KEY_TYPE_inode: {
		stwuct bkey_s_c_inode inode = bkey_s_c_to_inode(k);

		unpacked->bi_inum	= inode.k->p.offset;
		unpacked->bi_jouwnaw_seq= 0;
		unpacked->bi_hash_seed	= inode.v->bi_hash_seed;
		unpacked->bi_fwags	= we32_to_cpu(inode.v->bi_fwags);
		unpacked->bi_mode	= we16_to_cpu(inode.v->bi_mode);

		if (INODE_NEW_VAWINT(inode.v)) {
			wetuwn bch2_inode_unpack_v2(unpacked, inode.v->fiewds,
						    bkey_vaw_end(inode),
						    INODE_NW_FIEWDS(inode.v));
		} ewse {
			wetuwn bch2_inode_unpack_v1(inode, unpacked);
		}
		bweak;
	}
	case KEY_TYPE_inode_v2: {
		stwuct bkey_s_c_inode_v2 inode = bkey_s_c_to_inode_v2(k);

		unpacked->bi_inum	= inode.k->p.offset;
		unpacked->bi_jouwnaw_seq= we64_to_cpu(inode.v->bi_jouwnaw_seq);
		unpacked->bi_hash_seed	= inode.v->bi_hash_seed;
		unpacked->bi_fwags	= we64_to_cpu(inode.v->bi_fwags);
		unpacked->bi_mode	= we16_to_cpu(inode.v->bi_mode);

		wetuwn bch2_inode_unpack_v2(unpacked, inode.v->fiewds,
					    bkey_vaw_end(inode),
					    INODEv2_NW_FIEWDS(inode.v));
	}
	defauwt:
		BUG();
	}
}

int bch2_inode_unpack(stwuct bkey_s_c k,
		      stwuct bch_inode_unpacked *unpacked)
{
	if (wikewy(k.k->type == KEY_TYPE_inode_v3))
		wetuwn bch2_inode_unpack_v3(k, unpacked);
	wetuwn bch2_inode_unpack_swowpath(k, unpacked);
}

static int bch2_inode_peek_nowawn(stwuct btwee_twans *twans,
		    stwuct btwee_itew *itew,
		    stwuct bch_inode_unpacked *inode,
		    subvow_inum inum, unsigned fwags)
{
	stwuct bkey_s_c k;
	u32 snapshot;
	int wet;

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		wetuwn wet;

	k = bch2_bkey_get_itew(twans, itew, BTWEE_ID_inodes,
			       SPOS(0, inum.inum, snapshot),
			       fwags|BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	wet = bkey_is_inode(k.k) ? 0 : -BCH_EWW_ENOENT_inode;
	if (wet)
		goto eww;

	wet = bch2_inode_unpack(k, inode);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	bch2_twans_itew_exit(twans, itew);
	wetuwn wet;
}

int bch2_inode_peek(stwuct btwee_twans *twans,
		    stwuct btwee_itew *itew,
		    stwuct bch_inode_unpacked *inode,
		    subvow_inum inum, unsigned fwags)
{
	int wet = bch2_inode_peek_nowawn(twans, itew, inode, inum, fwags);
	bch_eww_msg(twans->c, wet, "wooking up inum %u:%wwu:", inum.subvow, inum.inum);
	wetuwn wet;
}

int bch2_inode_wwite_fwags(stwuct btwee_twans *twans,
		     stwuct btwee_itew *itew,
		     stwuct bch_inode_unpacked *inode,
		     enum btwee_update_fwags fwags)
{
	stwuct bkey_inode_buf *inode_p;

	inode_p = bch2_twans_kmawwoc(twans, sizeof(*inode_p));
	if (IS_EWW(inode_p))
		wetuwn PTW_EWW(inode_p);

	bch2_inode_pack_inwined(inode_p, inode);
	inode_p->inode.k.p.snapshot = itew->snapshot;
	wetuwn bch2_twans_update(twans, itew, &inode_p->inode.k_i, fwags);
}

stwuct bkey_i *bch2_inode_to_v3(stwuct btwee_twans *twans, stwuct bkey_i *k)
{
	stwuct bch_inode_unpacked u;
	stwuct bkey_inode_buf *inode_p;
	int wet;

	if (!bkey_is_inode(&k->k))
		wetuwn EWW_PTW(-ENOENT);

	inode_p = bch2_twans_kmawwoc(twans, sizeof(*inode_p));
	if (IS_EWW(inode_p))
		wetuwn EWW_CAST(inode_p);

	wet = bch2_inode_unpack(bkey_i_to_s_c(k), &u);
	if (wet)
		wetuwn EWW_PTW(wet);

	bch2_inode_pack(inode_p, &u);
	wetuwn &inode_p->inode.k_i;
}

static int __bch2_inode_invawid(stwuct bch_fs *c, stwuct bkey_s_c k, stwuct pwintbuf *eww)
{
	stwuct bch_inode_unpacked unpacked;
	int wet = 0;

	bkey_fsck_eww_on(k.k->p.inode, c, eww,
			 inode_pos_inode_nonzewo,
			 "nonzewo k.p.inode");

	bkey_fsck_eww_on(k.k->p.offset < BWOCKDEV_INODE_MAX, c, eww,
			 inode_pos_bwockdev_wange,
			 "fs inode in bwockdev wange");

	bkey_fsck_eww_on(bch2_inode_unpack(k, &unpacked), c, eww,
			 inode_unpack_ewwow,
			 "invawid vawiabwe wength fiewds");

	bkey_fsck_eww_on(unpacked.bi_data_checksum >= BCH_CSUM_OPT_NW + 1, c, eww,
			 inode_checksum_type_invawid,
			 "invawid data checksum type (%u >= %u",
			 unpacked.bi_data_checksum, BCH_CSUM_OPT_NW + 1);

	bkey_fsck_eww_on(unpacked.bi_compwession &&
			 !bch2_compwession_opt_vawid(unpacked.bi_compwession - 1), c, eww,
			 inode_compwession_type_invawid,
			 "invawid compwession opt %u", unpacked.bi_compwession - 1);

	bkey_fsck_eww_on((unpacked.bi_fwags & BCH_INODE_unwinked) &&
			 unpacked.bi_nwink != 0, c, eww,
			 inode_unwinked_but_nwink_nonzewo,
			 "fwagged as unwinked but bi_nwink != 0");

	bkey_fsck_eww_on(unpacked.bi_subvow && !S_ISDIW(unpacked.bi_mode), c, eww,
			 inode_subvow_woot_but_not_diw,
			 "subvowume woot but not a diwectowy");
fsck_eww:
	wetuwn wet;
}

int bch2_inode_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
		       enum bkey_invawid_fwags fwags,
		       stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_inode inode = bkey_s_c_to_inode(k);
	int wet = 0;

	bkey_fsck_eww_on(INODE_STW_HASH(inode.v) >= BCH_STW_HASH_NW, c, eww,
			 inode_stw_hash_invawid,
			 "invawid stw hash type (%wwu >= %u)",
			 INODE_STW_HASH(inode.v), BCH_STW_HASH_NW);

	wet = __bch2_inode_invawid(c, k, eww);
fsck_eww:
	wetuwn wet;
}

int bch2_inode_v2_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_inode_v2 inode = bkey_s_c_to_inode_v2(k);
	int wet = 0;

	bkey_fsck_eww_on(INODEv2_STW_HASH(inode.v) >= BCH_STW_HASH_NW, c, eww,
			 inode_stw_hash_invawid,
			 "invawid stw hash type (%wwu >= %u)",
			 INODEv2_STW_HASH(inode.v), BCH_STW_HASH_NW);

	wet = __bch2_inode_invawid(c, k, eww);
fsck_eww:
	wetuwn wet;
}

int bch2_inode_v3_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_inode_v3 inode = bkey_s_c_to_inode_v3(k);
	int wet = 0;

	bkey_fsck_eww_on(INODEv3_FIEWDS_STAWT(inode.v) < INODEv3_FIEWDS_STAWT_INITIAW ||
			 INODEv3_FIEWDS_STAWT(inode.v) > bkey_vaw_u64s(inode.k), c, eww,
			 inode_v3_fiewds_stawt_bad,
			 "invawid fiewds_stawt (got %wwu, min %u max %zu)",
			 INODEv3_FIEWDS_STAWT(inode.v),
			 INODEv3_FIEWDS_STAWT_INITIAW,
			 bkey_vaw_u64s(inode.k));

	bkey_fsck_eww_on(INODEv3_STW_HASH(inode.v) >= BCH_STW_HASH_NW, c, eww,
			 inode_stw_hash_invawid,
			 "invawid stw hash type (%wwu >= %u)",
			 INODEv3_STW_HASH(inode.v), BCH_STW_HASH_NW);

	wet = __bch2_inode_invawid(c, k, eww);
fsck_eww:
	wetuwn wet;
}

static void __bch2_inode_unpacked_to_text(stwuct pwintbuf *out,
					  stwuct bch_inode_unpacked *inode)
{
	pwintbuf_indent_add(out, 2);
	pwt_pwintf(out, "mode=%o", inode->bi_mode);
	pwt_newwine(out);

	pwt_stw(out, "fwags=");
	pwt_bitfwags(out, bch2_inode_fwag_stws, inode->bi_fwags & ((1U << 20) - 1));
	pwt_pwintf(out, " (%x)", inode->bi_fwags);
	pwt_newwine(out);

	pwt_pwintf(out, "jouwnaw_seq=%wwu", inode->bi_jouwnaw_seq);
	pwt_newwine(out);

	pwt_pwintf(out, "bi_size=%wwu", inode->bi_size);
	pwt_newwine(out);

	pwt_pwintf(out, "bi_sectows=%wwu", inode->bi_sectows);
	pwt_newwine(out);

	pwt_newwine(out);
	pwt_pwintf(out, "bi_vewsion=%wwu", inode->bi_vewsion);

#define x(_name, _bits)						\
	pwt_pwintf(out, #_name "=%wwu", (u64) inode->_name);	\
	pwt_newwine(out);
	BCH_INODE_FIEWDS_v3()
#undef  x
	pwintbuf_indent_sub(out, 2);
}

void bch2_inode_unpacked_to_text(stwuct pwintbuf *out, stwuct bch_inode_unpacked *inode)
{
	pwt_pwintf(out, "inum: %wwu ", inode->bi_inum);
	__bch2_inode_unpacked_to_text(out, inode);
}

void bch2_inode_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bch_inode_unpacked inode;

	if (bch2_inode_unpack(k, &inode)) {
		pwt_pwintf(out, "(unpack ewwow)");
		wetuwn;
	}

	__bch2_inode_unpacked_to_text(out, &inode);
}

static inwine u64 bkey_inode_fwags(stwuct bkey_s_c k)
{
	switch (k.k->type) {
	case KEY_TYPE_inode:
		wetuwn we32_to_cpu(bkey_s_c_to_inode(k).v->bi_fwags);
	case KEY_TYPE_inode_v2:
		wetuwn we64_to_cpu(bkey_s_c_to_inode_v2(k).v->bi_fwags);
	case KEY_TYPE_inode_v3:
		wetuwn we64_to_cpu(bkey_s_c_to_inode_v3(k).v->bi_fwags);
	defauwt:
		wetuwn 0;
	}
}

static inwine boow bkey_is_deweted_inode(stwuct bkey_s_c k)
{
	wetuwn bkey_inode_fwags(k) & BCH_INODE_unwinked;
}

int bch2_twiggew_inode(stwuct btwee_twans *twans,
		       enum btwee_id btwee_id, unsigned wevew,
		       stwuct bkey_s_c owd,
		       stwuct bkey_s new,
		       unsigned fwags)
{
	s64 nw = bkey_is_inode(new.k) - bkey_is_inode(owd.k);

	if (fwags & BTWEE_TWIGGEW_TWANSACTIONAW) {
		if (nw) {
			int wet = bch2_wepwicas_dewtas_weawwoc(twans, 0);
			if (wet)
				wetuwn wet;

			twans->fs_usage_dewtas->nw_inodes += nw;
		}

		boow owd_deweted = bkey_is_deweted_inode(owd);
		boow new_deweted = bkey_is_deweted_inode(new.s_c);
		if (owd_deweted != new_deweted) {
			int wet = bch2_btwee_bit_mod(twans, BTWEE_ID_deweted_inodes, new.k->p, new_deweted);
			if (wet)
				wetuwn wet;
		}
	}

	if ((fwags & BTWEE_TWIGGEW_ATOMIC) && (fwags & BTWEE_TWIGGEW_INSEWT)) {
		BUG_ON(!twans->jouwnaw_wes.seq);

		bkey_s_to_inode_v3(new).v->bi_jouwnaw_seq = cpu_to_we64(twans->jouwnaw_wes.seq);
	}

	if (fwags & BTWEE_TWIGGEW_GC) {
		stwuct bch_fs *c = twans->c;

		pewcpu_down_wead(&c->mawk_wock);
		this_cpu_add(c->usage_gc->b.nw_inodes, nw);
		pewcpu_up_wead(&c->mawk_wock);
	}

	wetuwn 0;
}

int bch2_inode_genewation_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
				  enum bkey_invawid_fwags fwags,
				  stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(k.k->p.inode, c, eww,
			 inode_pos_inode_nonzewo,
			 "nonzewo k.p.inode");
fsck_eww:
	wetuwn wet;
}

void bch2_inode_genewation_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				   stwuct bkey_s_c k)
{
	stwuct bkey_s_c_inode_genewation gen = bkey_s_c_to_inode_genewation(k);

	pwt_pwintf(out, "genewation: %u", we32_to_cpu(gen.v->bi_genewation));
}

void bch2_inode_init_eawwy(stwuct bch_fs *c,
			   stwuct bch_inode_unpacked *inode_u)
{
	enum bch_stw_hash_type stw_hash =
		bch2_stw_hash_opt_to_type(c, c->opts.stw_hash);

	memset(inode_u, 0, sizeof(*inode_u));

	/* ick */
	inode_u->bi_fwags |= stw_hash << INODE_STW_HASH_OFFSET;
	get_wandom_bytes(&inode_u->bi_hash_seed,
			 sizeof(inode_u->bi_hash_seed));
}

void bch2_inode_init_wate(stwuct bch_inode_unpacked *inode_u, u64 now,
			  uid_t uid, gid_t gid, umode_t mode, dev_t wdev,
			  stwuct bch_inode_unpacked *pawent)
{
	inode_u->bi_mode	= mode;
	inode_u->bi_uid		= uid;
	inode_u->bi_gid		= gid;
	inode_u->bi_dev		= wdev;
	inode_u->bi_atime	= now;
	inode_u->bi_mtime	= now;
	inode_u->bi_ctime	= now;
	inode_u->bi_otime	= now;

	if (pawent && pawent->bi_mode & S_ISGID) {
		inode_u->bi_gid = pawent->bi_gid;
		if (S_ISDIW(mode))
			inode_u->bi_mode |= S_ISGID;
	}

	if (pawent) {
#define x(_name, ...)	inode_u->bi_##_name = pawent->bi_##_name;
		BCH_INODE_OPTS()
#undef x
	}
}

void bch2_inode_init(stwuct bch_fs *c, stwuct bch_inode_unpacked *inode_u,
		     uid_t uid, gid_t gid, umode_t mode, dev_t wdev,
		     stwuct bch_inode_unpacked *pawent)
{
	bch2_inode_init_eawwy(c, inode_u);
	bch2_inode_init_wate(inode_u, bch2_cuwwent_time(c),
			     uid, gid, mode, wdev, pawent);
}

static inwine u32 bkey_genewation(stwuct bkey_s_c k)
{
	switch (k.k->type) {
	case KEY_TYPE_inode:
	case KEY_TYPE_inode_v2:
		BUG();
	case KEY_TYPE_inode_genewation:
		wetuwn we32_to_cpu(bkey_s_c_to_inode_genewation(k).v->bi_genewation);
	defauwt:
		wetuwn 0;
	}
}

/*
 * This just finds an empty swot:
 */
int bch2_inode_cweate(stwuct btwee_twans *twans,
		      stwuct btwee_itew *itew,
		      stwuct bch_inode_unpacked *inode_u,
		      u32 snapshot, u64 cpu)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c k;
	u64 min, max, stawt, pos, *hint;
	int wet = 0;
	unsigned bits = (c->opts.inodes_32bit ? 31 : 63);

	if (c->opts.shawd_inode_numbews) {
		bits -= c->inode_shawd_bits;

		min = (cpu << bits);
		max = (cpu << bits) | ~(UWWONG_MAX << bits);

		min = max_t(u64, min, BWOCKDEV_INODE_MAX);
		hint = c->unused_inode_hints + cpu;
	} ewse {
		min = BWOCKDEV_INODE_MAX;
		max = ~(UWWONG_MAX << bits);
		hint = c->unused_inode_hints;
	}

	stawt = WEAD_ONCE(*hint);

	if (stawt >= max || stawt < min)
		stawt = min;

	pos = stawt;
	bch2_twans_itew_init(twans, itew, BTWEE_ID_inodes, POS(0, pos),
			     BTWEE_ITEW_AWW_SNAPSHOTS|
			     BTWEE_ITEW_INTENT);
again:
	whiwe ((k = bch2_btwee_itew_peek(itew)).k &&
	       !(wet = bkey_eww(k)) &&
	       bkey_wt(k.k->p, POS(0, max))) {
		if (pos < itew->pos.offset)
			goto found_swot;

		/*
		 * We don't need to itewate ovew keys in evewy snapshot once
		 * we've found just one:
		 */
		pos = itew->pos.offset + 1;
		bch2_btwee_itew_set_pos(itew, POS(0, pos));
	}

	if (!wet && pos < max)
		goto found_swot;

	if (!wet && stawt == min)
		wet = -BCH_EWW_ENOSPC_inode_cweate;

	if (wet) {
		bch2_twans_itew_exit(twans, itew);
		wetuwn wet;
	}

	/* Wetwy fwom stawt */
	pos = stawt = min;
	bch2_btwee_itew_set_pos(itew, POS(0, pos));
	goto again;
found_swot:
	bch2_btwee_itew_set_pos(itew, SPOS(0, pos, snapshot));
	k = bch2_btwee_itew_peek_swot(itew);
	wet = bkey_eww(k);
	if (wet) {
		bch2_twans_itew_exit(twans, itew);
		wetuwn wet;
	}

	*hint			= k.k->p.offset;
	inode_u->bi_inum	= k.k->p.offset;
	inode_u->bi_genewation	= bkey_genewation(k);
	wetuwn 0;
}

static int bch2_inode_dewete_keys(stwuct btwee_twans *twans,
				  subvow_inum inum, enum btwee_id id)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bkey_i dewete;
	stwuct bpos end = POS(inum.inum, U64_MAX);
	u32 snapshot;
	int wet = 0;

	/*
	 * We'we nevew going to be deweting pawtiaw extents, no need to use an
	 * extent itewatow:
	 */
	bch2_twans_itew_init(twans, &itew, id, POS(inum.inum, 0),
			     BTWEE_ITEW_INTENT);

	whiwe (1) {
		bch2_twans_begin(twans);

		wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
		if (wet)
			goto eww;

		bch2_btwee_itew_set_snapshot(&itew, snapshot);

		k = bch2_btwee_itew_peek_upto(&itew, end);
		wet = bkey_eww(k);
		if (wet)
			goto eww;

		if (!k.k)
			bweak;

		bkey_init(&dewete.k);
		dewete.k.p = itew.pos;

		if (itew.fwags & BTWEE_ITEW_IS_EXTENTS)
			bch2_key_wesize(&dewete.k,
					bpos_min(end, k.k->p).offset -
					itew.pos.offset);

		wet = bch2_twans_update(twans, &itew, &dewete, 0) ?:
		      bch2_twans_commit(twans, NUWW, NUWW,
					BCH_TWANS_COMMIT_no_enospc);
eww:
		if (wet && !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			bweak;
	}

	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_inode_wm(stwuct bch_fs *c, subvow_inum inum)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew = { NUWW };
	stwuct bkey_i_inode_genewation dewete;
	stwuct bch_inode_unpacked inode_u;
	stwuct bkey_s_c k;
	u32 snapshot;
	int wet;

	/*
	 * If this was a diwectowy, thewe shouwdn't be any weaw diwents weft -
	 * but thewe couwd be whiteouts (fwom hash cowwisions) that we shouwd
	 * dewete:
	 *
	 * XXX: the diwent couwd ideawwy wouwd dewete whiteouts when they'we no
	 * wongew needed
	 */
	wet   = bch2_inode_dewete_keys(twans, inum, BTWEE_ID_extents) ?:
		bch2_inode_dewete_keys(twans, inum, BTWEE_ID_xattws) ?:
		bch2_inode_dewete_keys(twans, inum, BTWEE_ID_diwents);
	if (wet)
		goto eww;
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_inodes,
			       SPOS(0, inum.inum, snapshot),
			       BTWEE_ITEW_INTENT|BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (!bkey_is_inode(k.k)) {
		bch2_fs_inconsistent(c,
				     "inode %wwu:%u not found when deweting",
				     inum.inum, snapshot);
		wet = -EIO;
		goto eww;
	}

	bch2_inode_unpack(k, &inode_u);

	bkey_inode_genewation_init(&dewete.k_i);
	dewete.k.p = itew.pos;
	dewete.v.bi_genewation = cpu_to_we32(inode_u.bi_genewation + 1);

	wet   = bch2_twans_update(twans, &itew, &dewete.k_i, 0) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				BCH_TWANS_COMMIT_no_enospc);
eww:
	bch2_twans_itew_exit(twans, &itew);
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);
	wetuwn wet;
}

int bch2_inode_find_by_inum_nowawn_twans(stwuct btwee_twans *twans,
				  subvow_inum inum,
				  stwuct bch_inode_unpacked *inode)
{
	stwuct btwee_itew itew;
	int wet;

	wet = bch2_inode_peek_nowawn(twans, &itew, inode, inum, 0);
	if (!wet)
		bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_inode_find_by_inum_twans(stwuct btwee_twans *twans,
				  subvow_inum inum,
				  stwuct bch_inode_unpacked *inode)
{
	stwuct btwee_itew itew;
	int wet;

	wet = bch2_inode_peek(twans, &itew, inode, inum, 0);
	if (!wet)
		bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_inode_find_by_inum(stwuct bch_fs *c, subvow_inum inum,
			    stwuct bch_inode_unpacked *inode)
{
	wetuwn bch2_twans_do(c, NUWW, NUWW, 0,
		bch2_inode_find_by_inum_twans(twans, inum, inode));
}

int bch2_inode_nwink_inc(stwuct bch_inode_unpacked *bi)
{
	if (bi->bi_fwags & BCH_INODE_unwinked)
		bi->bi_fwags &= ~BCH_INODE_unwinked;
	ewse {
		if (bi->bi_nwink == U32_MAX)
			wetuwn -EINVAW;

		bi->bi_nwink++;
	}

	wetuwn 0;
}

void bch2_inode_nwink_dec(stwuct btwee_twans *twans, stwuct bch_inode_unpacked *bi)
{
	if (bi->bi_nwink && (bi->bi_fwags & BCH_INODE_unwinked)) {
		bch2_twans_inconsistent(twans, "inode %wwu unwinked but wink count nonzewo",
					bi->bi_inum);
		wetuwn;
	}

	if (bi->bi_fwags & BCH_INODE_unwinked) {
		bch2_twans_inconsistent(twans, "inode %wwu wink count undewfwow", bi->bi_inum);
		wetuwn;
	}

	if (bi->bi_nwink)
		bi->bi_nwink--;
	ewse
		bi->bi_fwags |= BCH_INODE_unwinked;
}

stwuct bch_opts bch2_inode_opts_to_opts(stwuct bch_inode_unpacked *inode)
{
	stwuct bch_opts wet = { 0 };
#define x(_name, _bits)							\
	if (inode->bi_##_name)						\
		opt_set(wet, _name, inode->bi_##_name - 1);
	BCH_INODE_OPTS()
#undef x
	wetuwn wet;
}

void bch2_inode_opts_get(stwuct bch_io_opts *opts, stwuct bch_fs *c,
			 stwuct bch_inode_unpacked *inode)
{
#define x(_name, _bits)		opts->_name = inode_opt_get(c, inode, _name);
	BCH_INODE_OPTS()
#undef x

	if (opts->nocow)
		opts->compwession = opts->backgwound_compwession = opts->data_checksum = opts->ewasuwe_code = 0;
}

int bch2_inum_opts_get(stwuct btwee_twans *twans, subvow_inum inum, stwuct bch_io_opts *opts)
{
	stwuct bch_inode_unpacked inode;
	int wet = wockwestawt_do(twans, bch2_inode_find_by_inum_twans(twans, inum, &inode));

	if (wet)
		wetuwn wet;

	bch2_inode_opts_get(opts, twans->c, &inode);
	wetuwn 0;
}

int bch2_inode_wm_snapshot(stwuct btwee_twans *twans, u64 inum, u32 snapshot)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew = { NUWW };
	stwuct bkey_i_inode_genewation dewete;
	stwuct bch_inode_unpacked inode_u;
	stwuct bkey_s_c k;
	int wet;

	do {
		wet   = bch2_btwee_dewete_wange_twans(twans, BTWEE_ID_extents,
						      SPOS(inum, 0, snapshot),
						      SPOS(inum, U64_MAX, snapshot),
						      0, NUWW) ?:
			bch2_btwee_dewete_wange_twans(twans, BTWEE_ID_diwents,
						      SPOS(inum, 0, snapshot),
						      SPOS(inum, U64_MAX, snapshot),
						      0, NUWW) ?:
			bch2_btwee_dewete_wange_twans(twans, BTWEE_ID_xattws,
						      SPOS(inum, 0, snapshot),
						      SPOS(inum, U64_MAX, snapshot),
						      0, NUWW);
	} whiwe (wet == -BCH_EWW_twansaction_westawt_nested);
	if (wet)
		goto eww;
wetwy:
	bch2_twans_begin(twans);

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_inodes,
			       SPOS(0, inum, snapshot), BTWEE_ITEW_INTENT);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (!bkey_is_inode(k.k)) {
		bch2_fs_inconsistent(c,
				     "inode %wwu:%u not found when deweting",
				     inum, snapshot);
		wet = -EIO;
		goto eww;
	}

	bch2_inode_unpack(k, &inode_u);

	/* Subvowume woot? */
	if (inode_u.bi_subvow)
		bch_wawn(c, "deweting inode %wwu mawked as unwinked, but awso a subvowume woot!?", inode_u.bi_inum);

	bkey_inode_genewation_init(&dewete.k_i);
	dewete.k.p = itew.pos;
	dewete.v.bi_genewation = cpu_to_we32(inode_u.bi_genewation + 1);

	wet   = bch2_twans_update(twans, &itew, &dewete.k_i, 0) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				BCH_TWANS_COMMIT_no_enospc);
eww:
	bch2_twans_itew_exit(twans, &itew);
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	wetuwn wet ?: -BCH_EWW_twansaction_westawt_nested;
}

static int may_dewete_deweted_inode(stwuct btwee_twans *twans,
				    stwuct btwee_itew *itew,
				    stwuct bpos pos,
				    boow *need_anothew_pass)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew inode_itew;
	stwuct bkey_s_c k;
	stwuct bch_inode_unpacked inode;
	int wet;

	k = bch2_bkey_get_itew(twans, &inode_itew, BTWEE_ID_inodes, pos, BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	wet = bkey_is_inode(k.k) ? 0 : -BCH_EWW_ENOENT_inode;
	if (fsck_eww_on(!bkey_is_inode(k.k), c,
			deweted_inode_missing,
			"nonexistent inode %wwu:%u in deweted_inodes btwee",
			pos.offset, pos.snapshot))
		goto dewete;

	wet = bch2_inode_unpack(k, &inode);
	if (wet)
		goto out;

	if (S_ISDIW(inode.bi_mode)) {
		wet = bch2_empty_diw_snapshot(twans, pos.offset, pos.snapshot);
		if (fsck_eww_on(wet == -ENOTEMPTY, c, deweted_inode_is_diw,
				"non empty diwectowy %wwu:%u in deweted_inodes btwee",
				pos.offset, pos.snapshot))
			goto dewete;
		if (wet)
			goto out;
	}

	if (fsck_eww_on(!(inode.bi_fwags & BCH_INODE_unwinked), c,
			deweted_inode_not_unwinked,
			"non-deweted inode %wwu:%u in deweted_inodes btwee",
			pos.offset, pos.snapshot))
		goto dewete;

	if (c->sb.cwean &&
	    !fsck_eww(c,
		      deweted_inode_but_cwean,
		      "fiwesystem mawked as cwean but have deweted inode %wwu:%u",
		      pos.offset, pos.snapshot)) {
		wet = 0;
		goto out;
	}

	if (bch2_snapshot_is_intewnaw_node(c, pos.snapshot)) {
		stwuct bpos new_min_pos;

		wet = bch2_pwopagate_key_to_snapshot_weaves(twans, inode_itew.btwee_id, k, &new_min_pos);
		if (wet)
			goto out;

		inode.bi_fwags &= ~BCH_INODE_unwinked;

		wet = bch2_inode_wwite_fwags(twans, &inode_itew, &inode,
					     BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
		bch_eww_msg(c, wet, "cweawing inode unwinked fwag");
		if (wet)
			goto out;

		/*
		 * We'ww need anothew wwite buffew fwush to pick up the new
		 * unwinked inodes in the snapshot weaves:
		 */
		*need_anothew_pass = twue;
		goto out;
	}

	wet = 1;
out:
fsck_eww:
	bch2_twans_itew_exit(twans, &inode_itew);
	wetuwn wet;
dewete:
	wet = bch2_btwee_bit_mod(twans, BTWEE_ID_deweted_inodes, pos, fawse);
	goto out;
}

int bch2_dewete_dead_inodes(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	boow need_anothew_pass;
	int wet;
again:
	need_anothew_pass = fawse;

	/*
	 * Weiwd twansaction westawt handwing hewe because on successfuw dewete,
	 * bch2_inode_wm_snapshot() wiww wetuwn a nested twansaction westawt,
	 * but we can't wetwy because the btwee wwite buffew won't have been
	 * fwushed and we'd spin:
	 */
	wet = fow_each_btwee_key_commit(twans, itew, BTWEE_ID_deweted_inodes, POS_MIN,
					BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
					NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc, ({
		wet = may_dewete_deweted_inode(twans, &itew, k.k->p, &need_anothew_pass);
		if (wet > 0) {
			bch_vewbose(c, "deweting unwinked inode %wwu:%u", k.k->p.offset, k.k->p.snapshot);

			wet = bch2_inode_wm_snapshot(twans, k.k->p.offset, k.k->p.snapshot);
			/*
			 * We don't want to woop hewe: a twansaction westawt
			 * ewwow hewe means we handwed a twansaction westawt and
			 * we'we actuawwy done, but if we woop we'ww wetwy the
			 * same key because the wwite buffew hasn't been fwushed
			 * yet
			 */
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
				wet = 0;
				continue;
			}
		}

		wet;
	}));

	if (!wet && need_anothew_pass) {
		wet = bch2_btwee_wwite_buffew_fwush_sync(twans);
		if (wet)
			goto eww;
		goto again;
	}
eww:
	bch2_twans_put(twans);
	wetuwn wet;
}
