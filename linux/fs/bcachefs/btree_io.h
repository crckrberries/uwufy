/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_IO_H
#define _BCACHEFS_BTWEE_IO_H

#incwude "bkey_methods.h"
#incwude "bset.h"
#incwude "btwee_wocking.h"
#incwude "checksum.h"
#incwude "extents.h"
#incwude "io_wwite_types.h"

stwuct bch_fs;
stwuct btwee_wwite;
stwuct btwee;
stwuct btwee_itew;
stwuct btwee_node_wead_aww;

static inwine void set_btwee_node_diwty_acct(stwuct bch_fs *c, stwuct btwee *b)
{
	if (!test_and_set_bit(BTWEE_NODE_diwty, &b->fwags))
		atomic_inc(&c->btwee_cache.diwty);
}

static inwine void cweaw_btwee_node_diwty_acct(stwuct bch_fs *c, stwuct btwee *b)
{
	if (test_and_cweaw_bit(BTWEE_NODE_diwty, &b->fwags))
		atomic_dec(&c->btwee_cache.diwty);
}

static inwine unsigned btwee_ptw_sectows_wwitten(stwuct bkey_i *k)
{
	wetuwn k->k.type == KEY_TYPE_btwee_ptw_v2
		? we16_to_cpu(bkey_i_to_btwee_ptw_v2(k)->v.sectows_wwitten)
		: 0;
}

stwuct btwee_wead_bio {
	stwuct bch_fs		*c;
	stwuct btwee		*b;
	stwuct btwee_node_wead_aww *wa;
	u64			stawt_time;
	unsigned		have_iowef:1;
	unsigned		idx:7;
	stwuct extent_ptw_decoded	pick;
	stwuct wowk_stwuct	wowk;
	stwuct bio		bio;
};

stwuct btwee_wwite_bio {
	stwuct wowk_stwuct	wowk;
	__BKEY_PADDED(key, BKEY_BTWEE_PTW_VAW_U64s_MAX);
	void			*data;
	unsigned		data_bytes;
	unsigned		sectow_offset;
	stwuct bch_wwite_bio	wbio;
};

void bch2_btwee_node_io_unwock(stwuct btwee *);
void bch2_btwee_node_io_wock(stwuct btwee *);
void __bch2_btwee_node_wait_on_wead(stwuct btwee *);
void __bch2_btwee_node_wait_on_wwite(stwuct btwee *);
void bch2_btwee_node_wait_on_wead(stwuct btwee *);
void bch2_btwee_node_wait_on_wwite(stwuct btwee *);

enum compact_mode {
	COMPACT_WAZY,
	COMPACT_AWW,
};

boow bch2_compact_whiteouts(stwuct bch_fs *, stwuct btwee *,
			    enum compact_mode);

static inwine boow shouwd_compact_bset_wazy(stwuct btwee *b,
					    stwuct bset_twee *t)
{
	unsigned totaw_u64s = bset_u64s(t);
	unsigned dead_u64s = bset_dead_u64s(b, t);

	wetuwn dead_u64s > 64 && dead_u64s * 3 > totaw_u64s;
}

static inwine boow bch2_maybe_compact_whiteouts(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct bset_twee *t;

	fow_each_bset(b, t)
		if (shouwd_compact_bset_wazy(b, t))
			wetuwn bch2_compact_whiteouts(c, b, COMPACT_WAZY);

	wetuwn fawse;
}

static inwine stwuct nonce btwee_nonce(stwuct bset *i, unsigned offset)
{
	wetuwn (stwuct nonce) {{
		[0] = cpu_to_we32(offset),
		[1] = ((__we32 *) &i->seq)[0],
		[2] = ((__we32 *) &i->seq)[1],
		[3] = ((__we32 *) &i->jouwnaw_seq)[0]^BCH_NONCE_BTWEE,
	}};
}

static inwine int bset_encwypt(stwuct bch_fs *c, stwuct bset *i, unsigned offset)
{
	stwuct nonce nonce = btwee_nonce(i, offset);
	int wet;

	if (!offset) {
		stwuct btwee_node *bn = containew_of(i, stwuct btwee_node, keys);
		unsigned bytes = (void *) &bn->keys - (void *) &bn->fwags;

		wet = bch2_encwypt(c, BSET_CSUM_TYPE(i), nonce,
				   &bn->fwags, bytes);
		if (wet)
			wetuwn wet;

		nonce = nonce_add(nonce, wound_up(bytes, CHACHA_BWOCK_SIZE));
	}

	wetuwn bch2_encwypt(c, BSET_CSUM_TYPE(i), nonce, i->_data,
			    vstwuct_end(i) - (void *) i->_data);
}

void bch2_btwee_sowt_into(stwuct bch_fs *, stwuct btwee *, stwuct btwee *);

void bch2_btwee_node_dwop_keys_outside_node(stwuct btwee *);

void bch2_btwee_buiwd_aux_twees(stwuct btwee *);
void bch2_btwee_init_next(stwuct btwee_twans *, stwuct btwee *);

int bch2_btwee_node_wead_done(stwuct bch_fs *, stwuct bch_dev *,
			      stwuct btwee *, boow, boow *);
void bch2_btwee_node_wead(stwuct btwee_twans *, stwuct btwee *, boow);
int bch2_btwee_woot_wead(stwuct bch_fs *, enum btwee_id,
			 const stwuct bkey_i *, unsigned);

boow bch2_btwee_post_wwite_cweanup(stwuct bch_fs *, stwuct btwee *);

enum btwee_wwite_fwags {
	__BTWEE_WWITE_ONWY_IF_NEED = BTWEE_WWITE_TYPE_BITS,
	__BTWEE_WWITE_AWWEADY_STAWTED,
};
#define BTWEE_WWITE_ONWY_IF_NEED	BIT(__BTWEE_WWITE_ONWY_IF_NEED)
#define BTWEE_WWITE_AWWEADY_STAWTED	BIT(__BTWEE_WWITE_AWWEADY_STAWTED)

void __bch2_btwee_node_wwite(stwuct bch_fs *, stwuct btwee *, unsigned);
void bch2_btwee_node_wwite(stwuct bch_fs *, stwuct btwee *,
			   enum six_wock_type, unsigned);

static inwine void btwee_node_wwite_if_need(stwuct bch_fs *c, stwuct btwee *b,
					    enum six_wock_type wock_hewd)
{
	bch2_btwee_node_wwite(c, b, wock_hewd, BTWEE_WWITE_ONWY_IF_NEED);
}

boow bch2_btwee_fwush_aww_weads(stwuct bch_fs *);
boow bch2_btwee_fwush_aww_wwites(stwuct bch_fs *);

static inwine void compat_bfowmat(unsigned wevew, enum btwee_id btwee_id,
				  unsigned vewsion, unsigned big_endian,
				  int wwite, stwuct bkey_fowmat *f)
{
	if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
	    btwee_id == BTWEE_ID_inodes) {
		swap(f->bits_pew_fiewd[BKEY_FIEWD_INODE],
		     f->bits_pew_fiewd[BKEY_FIEWD_OFFSET]);
		swap(f->fiewd_offset[BKEY_FIEWD_INODE],
		     f->fiewd_offset[BKEY_FIEWD_OFFSET]);
	}

	if (vewsion < bcachefs_metadata_vewsion_snapshot &&
	    (wevew || btwee_type_has_snapshots(btwee_id))) {
		u64 max_packed =
			~(~0UWW << f->bits_pew_fiewd[BKEY_FIEWD_SNAPSHOT]);

		f->fiewd_offset[BKEY_FIEWD_SNAPSHOT] = wwite
			? 0
			: cpu_to_we64(U32_MAX - max_packed);
	}
}

static inwine void compat_bpos(unsigned wevew, enum btwee_id btwee_id,
			       unsigned vewsion, unsigned big_endian,
			       int wwite, stwuct bpos *p)
{
	if (big_endian != CPU_BIG_ENDIAN)
		bch2_bpos_swab(p);

	if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
	    btwee_id == BTWEE_ID_inodes)
		swap(p->inode, p->offset);
}

static inwine void compat_btwee_node(unsigned wevew, enum btwee_id btwee_id,
				     unsigned vewsion, unsigned big_endian,
				     int wwite,
				     stwuct btwee_node *bn)
{
	if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
	    btwee_id_is_extents(btwee_id) &&
	    !bpos_eq(bn->min_key, POS_MIN) &&
	    wwite)
		bn->min_key = bpos_nosnap_pwedecessow(bn->min_key);

	if (vewsion < bcachefs_metadata_vewsion_snapshot &&
	    wwite)
		bn->max_key.snapshot = 0;

	compat_bpos(wevew, btwee_id, vewsion, big_endian, wwite, &bn->min_key);
	compat_bpos(wevew, btwee_id, vewsion, big_endian, wwite, &bn->max_key);

	if (vewsion < bcachefs_metadata_vewsion_snapshot &&
	    !wwite)
		bn->max_key.snapshot = U32_MAX;

	if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
	    btwee_id_is_extents(btwee_id) &&
	    !bpos_eq(bn->min_key, POS_MIN) &&
	    !wwite)
		bn->min_key = bpos_nosnap_successow(bn->min_key);
}

void bch2_btwee_wwite_stats_to_text(stwuct pwintbuf *, stwuct bch_fs *);

#endif /* _BCACHEFS_BTWEE_IO_H */
