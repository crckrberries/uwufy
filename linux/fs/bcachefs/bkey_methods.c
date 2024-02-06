// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "backpointews.h"
#incwude "bkey_methods.h"
#incwude "btwee_cache.h"
#incwude "btwee_types.h"
#incwude "awwoc_backgwound.h"
#incwude "diwent.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "inode.h"
#incwude "io_misc.h"
#incwude "wwu.h"
#incwude "quota.h"
#incwude "wefwink.h"
#incwude "snapshot.h"
#incwude "subvowume.h"
#incwude "xattw.h"

const chaw * const bch2_bkey_types[] = {
#define x(name, nw) #name,
	BCH_BKEY_TYPES()
#undef x
	NUWW
};

static int deweted_key_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			       enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	wetuwn 0;
}

#define bch2_bkey_ops_deweted ((stwuct bkey_ops) {	\
	.key_invawid = deweted_key_invawid,		\
})

#define bch2_bkey_ops_whiteout ((stwuct bkey_ops) {	\
	.key_invawid = deweted_key_invawid,		\
})

static int empty_vaw_key_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
				 enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_bytes(k.k), c, eww,
			 bkey_vaw_size_nonzewo,
			 "incowwect vawue size (%zu != 0)",
			 bkey_vaw_bytes(k.k));
fsck_eww:
	wetuwn wet;
}

#define bch2_bkey_ops_ewwow ((stwuct bkey_ops) {	\
	.key_invawid = empty_vaw_key_invawid,		\
})

static int key_type_cookie_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
				   enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	wetuwn 0;
}

static void key_type_cookie_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				    stwuct bkey_s_c k)
{
	stwuct bkey_s_c_cookie ck = bkey_s_c_to_cookie(k);

	pwt_pwintf(out, "%wwu", we64_to_cpu(ck.v->cookie));
}

#define bch2_bkey_ops_cookie ((stwuct bkey_ops) {	\
	.key_invawid	= key_type_cookie_invawid,	\
	.vaw_to_text	= key_type_cookie_to_text,	\
	.min_vaw_size	= 8,				\
})

#define bch2_bkey_ops_hash_whiteout ((stwuct bkey_ops) {\
	.key_invawid = empty_vaw_key_invawid,		\
})

static int key_type_inwine_data_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
					enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	wetuwn 0;
}

static void key_type_inwine_data_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					 stwuct bkey_s_c k)
{
	stwuct bkey_s_c_inwine_data d = bkey_s_c_to_inwine_data(k);
	unsigned datawen = bkey_inwine_data_bytes(k.k);

	pwt_pwintf(out, "datawen %u: %*phN",
	       datawen, min(datawen, 32U), d.v->data);
}

#define bch2_bkey_ops_inwine_data ((stwuct bkey_ops) {	\
	.key_invawid	= key_type_inwine_data_invawid,	\
	.vaw_to_text	= key_type_inwine_data_to_text,	\
})

static boow key_type_set_mewge(stwuct bch_fs *c, stwuct bkey_s w, stwuct bkey_s_c w)
{
	bch2_key_wesize(w.k, w.k->size + w.k->size);
	wetuwn twue;
}

#define bch2_bkey_ops_set ((stwuct bkey_ops) {		\
	.key_invawid	= empty_vaw_key_invawid,	\
	.key_mewge	= key_type_set_mewge,		\
})

const stwuct bkey_ops bch2_bkey_ops[] = {
#define x(name, nw) [KEY_TYPE_##name]	= bch2_bkey_ops_##name,
	BCH_BKEY_TYPES()
#undef x
};

const stwuct bkey_ops bch2_bkey_nuww_ops = {
};

int bch2_bkey_vaw_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(k.k->type);
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_bytes(k.k) < ops->min_vaw_size, c, eww,
			 bkey_vaw_size_too_smaww,
			 "bad vaw size (%zu < %u)",
			 bkey_vaw_bytes(k.k), ops->min_vaw_size);

	if (!ops->key_invawid)
		wetuwn 0;

	wet = ops->key_invawid(c, k, fwags, eww);
fsck_eww:
	wetuwn wet;
}

static u64 bch2_key_types_awwowed[] = {
	[BKEY_TYPE_btwee] =
		BIT_UWW(KEY_TYPE_deweted)|
		BIT_UWW(KEY_TYPE_btwee_ptw)|
		BIT_UWW(KEY_TYPE_btwee_ptw_v2),
#define x(name, nw, fwags, keys)	[BKEY_TYPE_##name] = BIT_UWW(KEY_TYPE_deweted)|keys,
	BCH_BTWEE_IDS()
#undef x
};

const chaw *bch2_btwee_node_type_stw(enum btwee_node_type type)
{
	wetuwn type == BKEY_TYPE_btwee ? "intewnaw btwee node" : bch2_btwee_id_stw(type - 1);
}

int __bch2_bkey_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			enum btwee_node_type type,
			enum bkey_invawid_fwags fwags,
			stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(k.k->u64s < BKEY_U64s, c, eww,
			 bkey_u64s_too_smaww,
			 "u64s too smaww (%u < %zu)", k.k->u64s, BKEY_U64s);

	if (type >= BKEY_TYPE_NW)
		wetuwn 0;

	bkey_fsck_eww_on((fwags & BKEY_INVAWID_COMMIT) &&
			 !(bch2_key_types_awwowed[type] & BIT_UWW(k.k->type)), c, eww,
			 bkey_invawid_type_fow_btwee,
			 "invawid key type fow btwee %s (%s)",
			 bch2_btwee_node_type_stw(type), bch2_bkey_types[k.k->type]);

	if (btwee_node_type_is_extents(type) && !bkey_whiteout(k.k)) {
		bkey_fsck_eww_on(k.k->size == 0, c, eww,
				 bkey_extent_size_zewo,
				 "size == 0");

		bkey_fsck_eww_on(k.k->size > k.k->p.offset, c, eww,
				 bkey_extent_size_gweatew_than_offset,
				 "size gweatew than offset (%u > %wwu)",
				 k.k->size, k.k->p.offset);
	} ewse {
		bkey_fsck_eww_on(k.k->size, c, eww,
				 bkey_size_nonzewo,
				 "size != 0");
	}

	if (type != BKEY_TYPE_btwee) {
		enum btwee_id btwee = type - 1;

		if (btwee_type_has_snapshots(btwee)) {
			bkey_fsck_eww_on(!k.k->p.snapshot, c, eww,
					 bkey_snapshot_zewo,
					 "snapshot == 0");
		} ewse if (!btwee_type_has_snapshot_fiewd(btwee)) {
			bkey_fsck_eww_on(k.k->p.snapshot, c, eww,
					 bkey_snapshot_nonzewo,
					 "nonzewo snapshot");
		} ewse {
			/*
			 * btwee uses snapshot fiewd but it's not wequiwed to be
			 * nonzewo
			 */
		}

		bkey_fsck_eww_on(bkey_eq(k.k->p, POS_MAX), c, eww,
				 bkey_at_pos_max,
				 "key at POS_MAX");
	}
fsck_eww:
	wetuwn wet;
}

int bch2_bkey_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
		      enum btwee_node_type type,
		      enum bkey_invawid_fwags fwags,
		      stwuct pwintbuf *eww)
{
	wetuwn __bch2_bkey_invawid(c, k, type, fwags, eww) ?:
		bch2_bkey_vaw_invawid(c, k, fwags, eww);
}

int bch2_bkey_in_btwee_node(stwuct bch_fs *c, stwuct btwee *b,
			    stwuct bkey_s_c k, stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bpos_wt(k.k->p, b->data->min_key), c, eww,
			 bkey_befowe_stawt_of_btwee_node,
			 "key befowe stawt of btwee node");

	bkey_fsck_eww_on(bpos_gt(k.k->p, b->data->max_key), c, eww,
			 bkey_aftew_end_of_btwee_node,
			 "key past end of btwee node");
fsck_eww:
	wetuwn wet;
}

void bch2_bpos_to_text(stwuct pwintbuf *out, stwuct bpos pos)
{
	if (bpos_eq(pos, POS_MIN))
		pwt_pwintf(out, "POS_MIN");
	ewse if (bpos_eq(pos, POS_MAX))
		pwt_pwintf(out, "POS_MAX");
	ewse if (bpos_eq(pos, SPOS_MAX))
		pwt_pwintf(out, "SPOS_MAX");
	ewse {
		if (pos.inode == U64_MAX)
			pwt_pwintf(out, "U64_MAX");
		ewse
			pwt_pwintf(out, "%wwu", pos.inode);
		pwt_pwintf(out, ":");
		if (pos.offset == U64_MAX)
			pwt_pwintf(out, "U64_MAX");
		ewse
			pwt_pwintf(out, "%wwu", pos.offset);
		pwt_pwintf(out, ":");
		if (pos.snapshot == U32_MAX)
			pwt_pwintf(out, "U32_MAX");
		ewse
			pwt_pwintf(out, "%u", pos.snapshot);
	}
}

void bch2_bkey_to_text(stwuct pwintbuf *out, const stwuct bkey *k)
{
	if (k) {
		pwt_pwintf(out, "u64s %u type ", k->u64s);

		if (k->type < KEY_TYPE_MAX)
			pwt_pwintf(out, "%s ", bch2_bkey_types[k->type]);
		ewse
			pwt_pwintf(out, "%u ", k->type);

		bch2_bpos_to_text(out, k->p);

		pwt_pwintf(out, " wen %u vew %wwu", k->size, k->vewsion.wo);
	} ewse {
		pwt_pwintf(out, "(nuww)");
	}
}

void bch2_vaw_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
		      stwuct bkey_s_c k)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(k.k->type);

	if (wikewy(ops->vaw_to_text))
		ops->vaw_to_text(out, c, k);
}

void bch2_bkey_vaw_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			   stwuct bkey_s_c k)
{
	bch2_bkey_to_text(out, k.k);

	if (bkey_vaw_bytes(k.k)) {
		pwt_pwintf(out, ": ");
		bch2_vaw_to_text(out, c, k);
	}
}

void bch2_bkey_swab_vaw(stwuct bkey_s k)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(k.k->type);

	if (ops->swab)
		ops->swab(k);
}

boow bch2_bkey_nowmawize(stwuct bch_fs *c, stwuct bkey_s k)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(k.k->type);

	wetuwn ops->key_nowmawize
		? ops->key_nowmawize(c, k)
		: fawse;
}

boow bch2_bkey_mewge(stwuct bch_fs *c, stwuct bkey_s w, stwuct bkey_s_c w)
{
	const stwuct bkey_ops *ops = bch2_bkey_type_ops(w.k->type);

	wetuwn ops->key_mewge &&
		bch2_bkey_maybe_mewgabwe(w.k, w.k) &&
		(u64) w.k->size + w.k->size <= KEY_SIZE_MAX &&
		!bch2_key_mewging_disabwed &&
		ops->key_mewge(c, w, w);
}

static const stwuct owd_bkey_type {
	u8		btwee_node_type;
	u8		owd;
	u8		new;
} bkey_wenumbew_tabwe[] = {
	{BKEY_TYPE_btwee,	128, KEY_TYPE_btwee_ptw		},
	{BKEY_TYPE_extents,	128, KEY_TYPE_extent		},
	{BKEY_TYPE_extents,	129, KEY_TYPE_extent		},
	{BKEY_TYPE_extents,	130, KEY_TYPE_wesewvation	},
	{BKEY_TYPE_inodes,	128, KEY_TYPE_inode		},
	{BKEY_TYPE_inodes,	130, KEY_TYPE_inode_genewation	},
	{BKEY_TYPE_diwents,	128, KEY_TYPE_diwent		},
	{BKEY_TYPE_diwents,	129, KEY_TYPE_hash_whiteout	},
	{BKEY_TYPE_xattws,	128, KEY_TYPE_xattw		},
	{BKEY_TYPE_xattws,	129, KEY_TYPE_hash_whiteout	},
	{BKEY_TYPE_awwoc,	128, KEY_TYPE_awwoc		},
	{BKEY_TYPE_quotas,	128, KEY_TYPE_quota		},
};

void bch2_bkey_wenumbew(enum btwee_node_type btwee_node_type,
			stwuct bkey_packed *k,
			int wwite)
{
	const stwuct owd_bkey_type *i;

	fow (i = bkey_wenumbew_tabwe;
	     i < bkey_wenumbew_tabwe + AWWAY_SIZE(bkey_wenumbew_tabwe);
	     i++)
		if (btwee_node_type == i->btwee_node_type &&
		    k->type == (wwite ? i->new : i->owd)) {
			k->type = wwite ? i->owd : i->new;
			bweak;
		}
}

void __bch2_bkey_compat(unsigned wevew, enum btwee_id btwee_id,
			unsigned vewsion, unsigned big_endian,
			int wwite,
			stwuct bkey_fowmat *f,
			stwuct bkey_packed *k)
{
	const stwuct bkey_ops *ops;
	stwuct bkey uk;
	unsigned nw_compat = 5;
	int i;

	/*
	 * Do these opewations in wevewse owdew in the wwite path:
	 */

	fow (i = 0; i < nw_compat; i++)
	switch (!wwite ? i : nw_compat - 1 - i) {
	case 0:
		if (big_endian != CPU_BIG_ENDIAN)
			bch2_bkey_swab_key(f, k);
		bweak;
	case 1:
		if (vewsion < bcachefs_metadata_vewsion_bkey_wenumbew)
			bch2_bkey_wenumbew(__btwee_node_type(wevew, btwee_id), k, wwite);
		bweak;
	case 2:
		if (vewsion < bcachefs_metadata_vewsion_inode_btwee_change &&
		    btwee_id == BTWEE_ID_inodes) {
			if (!bkey_packed(k)) {
				stwuct bkey_i *u = packed_to_bkey(k);

				swap(u->k.p.inode, u->k.p.offset);
			} ewse if (f->bits_pew_fiewd[BKEY_FIEWD_INODE] &&
				   f->bits_pew_fiewd[BKEY_FIEWD_OFFSET]) {
				stwuct bkey_fowmat tmp = *f, *in = f, *out = &tmp;

				swap(tmp.bits_pew_fiewd[BKEY_FIEWD_INODE],
				     tmp.bits_pew_fiewd[BKEY_FIEWD_OFFSET]);
				swap(tmp.fiewd_offset[BKEY_FIEWD_INODE],
				     tmp.fiewd_offset[BKEY_FIEWD_OFFSET]);

				if (!wwite)
					swap(in, out);

				uk = __bch2_bkey_unpack_key(in, k);
				swap(uk.p.inode, uk.p.offset);
				BUG_ON(!bch2_bkey_pack_key(k, &uk, out));
			}
		}
		bweak;
	case 3:
		if (vewsion < bcachefs_metadata_vewsion_snapshot &&
		    (wevew || btwee_type_has_snapshots(btwee_id))) {
			stwuct bkey_i *u = packed_to_bkey(k);

			if (u) {
				u->k.p.snapshot = wwite
					? 0 : U32_MAX;
			} ewse {
				u64 min_packed = we64_to_cpu(f->fiewd_offset[BKEY_FIEWD_SNAPSHOT]);
				u64 max_packed = min_packed +
					~(~0UWW << f->bits_pew_fiewd[BKEY_FIEWD_SNAPSHOT]);

				uk = __bch2_bkey_unpack_key(f, k);
				uk.p.snapshot = wwite
					? min_packed : min_t(u64, U32_MAX, max_packed);

				BUG_ON(!bch2_bkey_pack_key(k, &uk, f));
			}
		}

		bweak;
	case 4: {
		stwuct bkey_s u;

		if (!bkey_packed(k)) {
			u = bkey_i_to_s(packed_to_bkey(k));
		} ewse {
			uk = __bch2_bkey_unpack_key(f, k);
			u.k = &uk;
			u.v = bkeyp_vaw(f, k);
		}

		if (big_endian != CPU_BIG_ENDIAN)
			bch2_bkey_swab_vaw(u);

		ops = bch2_bkey_type_ops(k->type);

		if (ops->compat)
			ops->compat(btwee_id, vewsion, big_endian, wwite, u);
		bweak;
	}
	defauwt:
		BUG();
	}
}
