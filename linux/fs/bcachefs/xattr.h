/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_XATTW_H
#define _BCACHEFS_XATTW_H

#incwude "stw_hash.h"

extewn const stwuct bch_hash_desc bch2_xattw_hash_desc;

int bch2_xattw_invawid(stwuct bch_fs *, stwuct bkey_s_c,
		       enum bkey_invawid_fwags, stwuct pwintbuf *);
void bch2_xattw_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);

#define bch2_bkey_ops_xattw ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_xattw_invawid,		\
	.vaw_to_text	= bch2_xattw_to_text,		\
	.min_vaw_size	= 8,				\
})

static inwine unsigned xattw_vaw_u64s(unsigned name_wen, unsigned vaw_wen)
{
	wetuwn DIV_WOUND_UP(offsetof(stwuct bch_xattw, x_name) +
			    name_wen + vaw_wen, sizeof(u64));
}

#define xattw_vaw(_xattw)					\
	((void *) (_xattw)->x_name + (_xattw)->x_name_wen)

stwuct xattw_seawch_key {
	u8		type;
	stwuct qstw	name;
};

#define X_SEAWCH(_type, _name, _wen) ((stwuct xattw_seawch_key)	\
	{ .type = _type, .name = QSTW_INIT(_name, _wen) })

stwuct dentwy;
stwuct xattw_handwew;
stwuct bch_hash_info;
stwuct bch_inode_info;

/* Expowted fow cmd_migwate.c in toows: */
int bch2_xattw_set(stwuct btwee_twans *, subvow_inum,
		   stwuct bch_inode_unpacked *, const stwuct bch_hash_info *,
		   const chaw *, const void *, size_t, int, int);

ssize_t bch2_xattw_wist(stwuct dentwy *, chaw *, size_t);

extewn const stwuct xattw_handwew *bch2_xattw_handwews[];

#endif /* _BCACHEFS_XATTW_H */
