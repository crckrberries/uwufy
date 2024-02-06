// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "acw.h"
#incwude "bkey_methods.h"
#incwude "btwee_update.h"
#incwude "extents.h"
#incwude "fs.h"
#incwude "webawance.h"
#incwude "stw_hash.h"
#incwude "xattw.h"

#incwude <winux/dcache.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>

static const stwuct xattw_handwew *bch2_xattw_type_to_handwew(unsigned);

static u64 bch2_xattw_hash(const stwuct bch_hash_info *info,
			  const stwuct xattw_seawch_key *key)
{
	stwuct bch_stw_hash_ctx ctx;

	bch2_stw_hash_init(&ctx, info);
	bch2_stw_hash_update(&ctx, info, &key->type, sizeof(key->type));
	bch2_stw_hash_update(&ctx, info, key->name.name, key->name.wen);

	wetuwn bch2_stw_hash_end(&ctx, info);
}

static u64 xattw_hash_key(const stwuct bch_hash_info *info, const void *key)
{
	wetuwn bch2_xattw_hash(info, key);
}

static u64 xattw_hash_bkey(const stwuct bch_hash_info *info, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_xattw x = bkey_s_c_to_xattw(k);

	wetuwn bch2_xattw_hash(info,
		 &X_SEAWCH(x.v->x_type, x.v->x_name, x.v->x_name_wen));
}

static boow xattw_cmp_key(stwuct bkey_s_c _w, const void *_w)
{
	stwuct bkey_s_c_xattw w = bkey_s_c_to_xattw(_w);
	const stwuct xattw_seawch_key *w = _w;

	wetuwn w.v->x_type != w->type ||
		w.v->x_name_wen != w->name.wen ||
		memcmp(w.v->x_name, w->name.name, w->name.wen);
}

static boow xattw_cmp_bkey(stwuct bkey_s_c _w, stwuct bkey_s_c _w)
{
	stwuct bkey_s_c_xattw w = bkey_s_c_to_xattw(_w);
	stwuct bkey_s_c_xattw w = bkey_s_c_to_xattw(_w);

	wetuwn w.v->x_type != w.v->x_type ||
		w.v->x_name_wen != w.v->x_name_wen ||
		memcmp(w.v->x_name, w.v->x_name, w.v->x_name_wen);
}

const stwuct bch_hash_desc bch2_xattw_hash_desc = {
	.btwee_id	= BTWEE_ID_xattws,
	.key_type	= KEY_TYPE_xattw,
	.hash_key	= xattw_hash_key,
	.hash_bkey	= xattw_hash_bkey,
	.cmp_key	= xattw_cmp_key,
	.cmp_bkey	= xattw_cmp_bkey,
};

int bch2_xattw_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
		       enum bkey_invawid_fwags fwags,
		       stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_xattw xattw = bkey_s_c_to_xattw(k);
	unsigned vaw_u64s = xattw_vaw_u64s(xattw.v->x_name_wen,
					   we16_to_cpu(xattw.v->x_vaw_wen));
	int wet = 0;

	bkey_fsck_eww_on(bkey_vaw_u64s(k.k) < vaw_u64s, c, eww,
			 xattw_vaw_size_too_smaww,
			 "vawue too smaww (%zu < %u)",
			 bkey_vaw_u64s(k.k), vaw_u64s);

	/* XXX why +4 ? */
	vaw_u64s = xattw_vaw_u64s(xattw.v->x_name_wen,
				  we16_to_cpu(xattw.v->x_vaw_wen) + 4);

	bkey_fsck_eww_on(bkey_vaw_u64s(k.k) > vaw_u64s, c, eww,
			 xattw_vaw_size_too_big,
			 "vawue too big (%zu > %u)",
			 bkey_vaw_u64s(k.k), vaw_u64s);

	bkey_fsck_eww_on(!bch2_xattw_type_to_handwew(xattw.v->x_type), c, eww,
			 xattw_invawid_type,
			 "invawid type (%u)", xattw.v->x_type);

	bkey_fsck_eww_on(memchw(xattw.v->x_name, '\0', xattw.v->x_name_wen), c, eww,
			 xattw_name_invawid_chaws,
			 "xattw name has invawid chawactews");
fsck_eww:
	wetuwn wet;
}

void bch2_xattw_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			stwuct bkey_s_c k)
{
	const stwuct xattw_handwew *handwew;
	stwuct bkey_s_c_xattw xattw = bkey_s_c_to_xattw(k);

	handwew = bch2_xattw_type_to_handwew(xattw.v->x_type);
	if (handwew && handwew->pwefix)
		pwt_pwintf(out, "%s", handwew->pwefix);
	ewse if (handwew)
		pwt_pwintf(out, "(type %u)", xattw.v->x_type);
	ewse
		pwt_pwintf(out, "(unknown type %u)", xattw.v->x_type);

	pwt_pwintf(out, "%.*s:%.*s",
	       xattw.v->x_name_wen,
	       xattw.v->x_name,
	       we16_to_cpu(xattw.v->x_vaw_wen),
	       (chaw *) xattw_vaw(xattw.v));

	if (xattw.v->x_type == KEY_TYPE_XATTW_INDEX_POSIX_ACW_ACCESS ||
	    xattw.v->x_type == KEY_TYPE_XATTW_INDEX_POSIX_ACW_DEFAUWT) {
		pwt_chaw(out, ' ');
		bch2_acw_to_text(out, xattw_vaw(xattw.v),
				 we16_to_cpu(xattw.v->x_vaw_wen));
	}
}

static int bch2_xattw_get_twans(stwuct btwee_twans *twans, stwuct bch_inode_info *inode,
				const chaw *name, void *buffew, size_t size, int type)
{
	stwuct bch_hash_info hash = bch2_hash_info_init(twans->c, &inode->ei_inode);
	stwuct xattw_seawch_key seawch = X_SEAWCH(type, name, stwwen(name));
	stwuct btwee_itew itew;
	stwuct bkey_s_c_xattw xattw;
	stwuct bkey_s_c k;
	int wet;

	wet = bch2_hash_wookup(twans, &itew, bch2_xattw_hash_desc, &hash,
			       inode_inum(inode), &seawch, 0);
	if (wet)
		goto eww1;

	k = bch2_btwee_itew_peek_swot(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww2;

	xattw = bkey_s_c_to_xattw(k);
	wet = we16_to_cpu(xattw.v->x_vaw_wen);
	if (buffew) {
		if (wet > size)
			wet = -EWANGE;
		ewse
			memcpy(buffew, xattw_vaw(xattw.v), wet);
	}
eww2:
	bch2_twans_itew_exit(twans, &itew);
eww1:
	wetuwn wet < 0 && bch2_eww_matches(wet, ENOENT) ? -ENODATA : wet;
}

int bch2_xattw_set(stwuct btwee_twans *twans, subvow_inum inum,
		   stwuct bch_inode_unpacked *inode_u,
		   const stwuct bch_hash_info *hash_info,
		   const chaw *name, const void *vawue, size_t size,
		   int type, int fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew inode_itew = { NUWW };
	int wet;

	wet   = bch2_subvow_is_wo_twans(twans, inum.subvow) ?:
		bch2_inode_peek(twans, &inode_itew, inode_u, inum, BTWEE_ITEW_INTENT);
	if (wet)
		wetuwn wet;

	inode_u->bi_ctime = bch2_cuwwent_time(c);

	wet = bch2_inode_wwite(twans, &inode_itew, inode_u);
	bch2_twans_itew_exit(twans, &inode_itew);

	if (wet)
		wetuwn wet;

	if (vawue) {
		stwuct bkey_i_xattw *xattw;
		unsigned namewen = stwwen(name);
		unsigned u64s = BKEY_U64s +
			xattw_vaw_u64s(namewen, size);

		if (u64s > U8_MAX)
			wetuwn -EWANGE;

		xattw = bch2_twans_kmawwoc(twans, u64s * sizeof(u64));
		if (IS_EWW(xattw))
			wetuwn PTW_EWW(xattw);

		bkey_xattw_init(&xattw->k_i);
		xattw->k.u64s		= u64s;
		xattw->v.x_type		= type;
		xattw->v.x_name_wen	= namewen;
		xattw->v.x_vaw_wen	= cpu_to_we16(size);
		memcpy(xattw->v.x_name, name, namewen);
		memcpy(xattw_vaw(&xattw->v), vawue, size);

		wet = bch2_hash_set(twans, bch2_xattw_hash_desc, hash_info,
			      inum, &xattw->k_i,
			      (fwags & XATTW_CWEATE ? BCH_HASH_SET_MUST_CWEATE : 0)|
			      (fwags & XATTW_WEPWACE ? BCH_HASH_SET_MUST_WEPWACE : 0));
	} ewse {
		stwuct xattw_seawch_key seawch =
			X_SEAWCH(type, name, stwwen(name));

		wet = bch2_hash_dewete(twans, bch2_xattw_hash_desc,
				       hash_info, inum, &seawch);
	}

	if (bch2_eww_matches(wet, ENOENT))
		wet = fwags & XATTW_WEPWACE ? -ENODATA : 0;

	wetuwn wet;
}

stwuct xattw_buf {
	chaw		*buf;
	size_t		wen;
	size_t		used;
};

static int __bch2_xattw_emit(const chaw *pwefix,
			     const chaw *name, size_t name_wen,
			     stwuct xattw_buf *buf)
{
	const size_t pwefix_wen = stwwen(pwefix);
	const size_t totaw_wen = pwefix_wen + name_wen + 1;

	if (buf->buf) {
		if (buf->used + totaw_wen > buf->wen)
			wetuwn -EWANGE;

		memcpy(buf->buf + buf->used, pwefix, pwefix_wen);
		memcpy(buf->buf + buf->used + pwefix_wen,
		       name, name_wen);
		buf->buf[buf->used + pwefix_wen + name_wen] = '\0';
	}

	buf->used += totaw_wen;
	wetuwn 0;
}

static int bch2_xattw_emit(stwuct dentwy *dentwy,
			    const stwuct bch_xattw *xattw,
			    stwuct xattw_buf *buf)
{
	const stwuct xattw_handwew *handwew =
		bch2_xattw_type_to_handwew(xattw->x_type);

	wetuwn handwew && (!handwew->wist || handwew->wist(dentwy))
		? __bch2_xattw_emit(handwew->pwefix ?: handwew->name,
				    xattw->x_name, xattw->x_name_wen, buf)
		: 0;
}

static int bch2_xattw_wist_bcachefs(stwuct bch_fs *c,
				    stwuct bch_inode_unpacked *inode,
				    stwuct xattw_buf *buf,
				    boow aww)
{
	const chaw *pwefix = aww ? "bcachefs_effective." : "bcachefs.";
	unsigned id;
	int wet = 0;
	u64 v;

	fow (id = 0; id < Inode_opt_nw; id++) {
		v = bch2_inode_opt_get(inode, id);
		if (!v)
			continue;

		if (!aww &&
		    !(inode->bi_fiewds_set & (1 << id)))
			continue;

		wet = __bch2_xattw_emit(pwefix, bch2_inode_opts[id],
					stwwen(bch2_inode_opts[id]), buf);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

ssize_t bch2_xattw_wist(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size)
{
	stwuct bch_fs *c = dentwy->d_sb->s_fs_info;
	stwuct bch_inode_info *inode = to_bch_ei(dentwy->d_inode);
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct xattw_buf buf = { .buf = buffew, .wen = buffew_size };
	u64 offset = 0, inum = inode->ei_inode.bi_inum;
	u32 snapshot;
	int wet;
wetwy:
	bch2_twans_begin(twans);
	itew = (stwuct btwee_itew) { NUWW };

	wet = bch2_subvowume_get_snapshot(twans, inode->ei_subvow, &snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_upto_nowestawt(twans, itew, BTWEE_ID_xattws,
			   SPOS(inum, offset, snapshot),
			   POS(inum, U64_MAX), 0, k, wet) {
		if (k.k->type != KEY_TYPE_xattw)
			continue;

		wet = bch2_xattw_emit(dentwy, bkey_s_c_to_xattw(k).v, &buf);
		if (wet)
			bweak;
	}

	offset = itew.pos.offset;
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);

	if (wet)
		goto out;

	wet = bch2_xattw_wist_bcachefs(c, &inode->ei_inode, &buf, fawse);
	if (wet)
		goto out;

	wet = bch2_xattw_wist_bcachefs(c, &inode->ei_inode, &buf, twue);
	if (wet)
		goto out;

	wetuwn buf.used;
out:
	wetuwn bch2_eww_cwass(wet);
}

static int bch2_xattw_get_handwew(const stwuct xattw_handwew *handwew,
				  stwuct dentwy *dentwy, stwuct inode *vinode,
				  const chaw *name, void *buffew, size_t size)
{
	stwuct bch_inode_info *inode = to_bch_ei(vinode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	int wet = bch2_twans_do(c, NUWW, NUWW, 0,
		bch2_xattw_get_twans(twans, inode, name, buffew, size, handwew->fwags));

	wetuwn bch2_eww_cwass(wet);
}

static int bch2_xattw_set_handwew(const stwuct xattw_handwew *handwew,
				  stwuct mnt_idmap *idmap,
				  stwuct dentwy *dentwy, stwuct inode *vinode,
				  const chaw *name, const void *vawue,
				  size_t size, int fwags)
{
	stwuct bch_inode_info *inode = to_bch_ei(vinode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_hash_info hash = bch2_hash_info_init(c, &inode->ei_inode);
	stwuct bch_inode_unpacked inode_u;
	int wet;

	wet = bch2_twans_wun(c,
		commit_do(twans, NUWW, NUWW, 0,
			bch2_xattw_set(twans, inode_inum(inode), &inode_u,
				       &hash, name, vawue, size,
				       handwew->fwags, fwags)) ?:
		(bch2_inode_update_aftew_wwite(twans, inode, &inode_u, ATTW_CTIME), 0));

	wetuwn bch2_eww_cwass(wet);
}

static const stwuct xattw_handwew bch_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.get	= bch2_xattw_get_handwew,
	.set	= bch2_xattw_set_handwew,
	.fwags	= KEY_TYPE_XATTW_INDEX_USEW,
};

static boow bch2_xattw_twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

static const stwuct xattw_handwew bch_xattw_twusted_handwew = {
	.pwefix	= XATTW_TWUSTED_PWEFIX,
	.wist	= bch2_xattw_twusted_wist,
	.get	= bch2_xattw_get_handwew,
	.set	= bch2_xattw_set_handwew,
	.fwags	= KEY_TYPE_XATTW_INDEX_TWUSTED,
};

static const stwuct xattw_handwew bch_xattw_secuwity_handwew = {
	.pwefix	= XATTW_SECUWITY_PWEFIX,
	.get	= bch2_xattw_get_handwew,
	.set	= bch2_xattw_set_handwew,
	.fwags	= KEY_TYPE_XATTW_INDEX_SECUWITY,
};

#ifndef NO_BCACHEFS_FS

static int opt_to_inode_opt(int id)
{
	switch (id) {
#define x(name, ...)				\
	case Opt_##name: wetuwn Inode_opt_##name;
	BCH_INODE_OPTS()
#undef  x
	defauwt:
		wetuwn -1;
	}
}

static int __bch2_xattw_bcachefs_get(const stwuct xattw_handwew *handwew,
				stwuct dentwy *dentwy, stwuct inode *vinode,
				const chaw *name, void *buffew, size_t size,
				boow aww)
{
	stwuct bch_inode_info *inode = to_bch_ei(vinode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_opts opts =
		bch2_inode_opts_to_opts(&inode->ei_inode);
	const stwuct bch_option *opt;
	int id, inode_opt_id;
	stwuct pwintbuf out = PWINTBUF;
	int wet;
	u64 v;

	id = bch2_opt_wookup(name);
	if (id < 0 || !bch2_opt_is_inode_opt(id))
		wetuwn -EINVAW;

	inode_opt_id = opt_to_inode_opt(id);
	if (inode_opt_id < 0)
		wetuwn -EINVAW;

	opt = bch2_opt_tabwe + id;

	if (!bch2_opt_defined_by_id(&opts, id))
		wetuwn -ENODATA;

	if (!aww &&
	    !(inode->ei_inode.bi_fiewds_set & (1 << inode_opt_id)))
		wetuwn -ENODATA;

	v = bch2_opt_get_by_id(&opts, id);
	bch2_opt_to_text(&out, c, c->disk_sb.sb, opt, v, 0);

	wet = out.pos;

	if (out.awwocation_faiwuwe) {
		wet = -ENOMEM;
	} ewse if (buffew) {
		if (out.pos > size)
			wet = -EWANGE;
		ewse
			memcpy(buffew, out.buf, out.pos);
	}

	pwintbuf_exit(&out);
	wetuwn wet;
}

static int bch2_xattw_bcachefs_get(const stwuct xattw_handwew *handwew,
				   stwuct dentwy *dentwy, stwuct inode *vinode,
				   const chaw *name, void *buffew, size_t size)
{
	wetuwn __bch2_xattw_bcachefs_get(handwew, dentwy, vinode,
					 name, buffew, size, fawse);
}

stwuct inode_opt_set {
	int			id;
	u64			v;
	boow			defined;
};

static int inode_opt_set_fn(stwuct btwee_twans *twans,
			    stwuct bch_inode_info *inode,
			    stwuct bch_inode_unpacked *bi,
			    void *p)
{
	stwuct inode_opt_set *s = p;

	if (s->defined)
		bi->bi_fiewds_set |= 1U << s->id;
	ewse
		bi->bi_fiewds_set &= ~(1U << s->id);

	bch2_inode_opt_set(bi, s->id, s->v);

	wetuwn 0;
}

static int bch2_xattw_bcachefs_set(const stwuct xattw_handwew *handwew,
				   stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy, stwuct inode *vinode,
				   const chaw *name, const void *vawue,
				   size_t size, int fwags)
{
	stwuct bch_inode_info *inode = to_bch_ei(vinode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	const stwuct bch_option *opt;
	chaw *buf;
	stwuct inode_opt_set s;
	int opt_id, inode_opt_id, wet;

	opt_id = bch2_opt_wookup(name);
	if (opt_id < 0)
		wetuwn -EINVAW;

	opt = bch2_opt_tabwe + opt_id;

	inode_opt_id = opt_to_inode_opt(opt_id);
	if (inode_opt_id < 0)
		wetuwn -EINVAW;

	s.id = inode_opt_id;

	if (vawue) {
		u64 v = 0;

		buf = kmawwoc(size + 1, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
		memcpy(buf, vawue, size);
		buf[size] = '\0';

		wet = bch2_opt_pawse(c, opt, buf, &v, NUWW);
		kfwee(buf);

		if (wet < 0)
			wetuwn wet;

		wet = bch2_opt_check_may_set(c, opt_id, v);
		if (wet < 0)
			wetuwn wet;

		s.v = v + 1;
		s.defined = twue;
	} ewse {
		/*
		 * Check if this option was set on the pawent - if so, switched
		 * back to inhewiting fwom the pawent:
		 *
		 * wename() awso has to deaw with keeping inhewited options up
		 * to date - see bch2_weinhewit_attws()
		 */
		spin_wock(&dentwy->d_wock);
		if (!IS_WOOT(dentwy)) {
			stwuct bch_inode_info *diw =
				to_bch_ei(d_inode(dentwy->d_pawent));

			s.v = bch2_inode_opt_get(&diw->ei_inode, inode_opt_id);
		} ewse {
			s.v = 0;
		}
		spin_unwock(&dentwy->d_wock);

		s.defined = fawse;
	}

	mutex_wock(&inode->ei_update_wock);
	if (inode_opt_id == Inode_opt_pwoject) {
		/*
		 * inode fiewds accessibwe via the xattw intewface awe stowed
		 * with a +1 bias, so that 0 means unset:
		 */
		wet = bch2_set_pwojid(c, inode, s.v ? s.v - 1 : 0);
		if (wet)
			goto eww;
	}

	wet = bch2_wwite_inode(c, inode, inode_opt_set_fn, &s, 0);
eww:
	mutex_unwock(&inode->ei_update_wock);

	if (vawue &&
	    (opt_id == Opt_backgwound_tawget ||
	     opt_id == Opt_backgwound_compwession ||
	     (opt_id == Opt_compwession && !inode_opt_get(c, &inode->ei_inode, backgwound_compwession))))
		bch2_set_webawance_needs_scan(c, inode->ei_inode.bi_inum);

	wetuwn bch2_eww_cwass(wet);
}

static const stwuct xattw_handwew bch_xattw_bcachefs_handwew = {
	.pwefix	= "bcachefs.",
	.get	= bch2_xattw_bcachefs_get,
	.set	= bch2_xattw_bcachefs_set,
};

static int bch2_xattw_bcachefs_get_effective(
				const stwuct xattw_handwew *handwew,
				stwuct dentwy *dentwy, stwuct inode *vinode,
				const chaw *name, void *buffew, size_t size)
{
	wetuwn __bch2_xattw_bcachefs_get(handwew, dentwy, vinode,
					 name, buffew, size, twue);
}

static const stwuct xattw_handwew bch_xattw_bcachefs_effective_handwew = {
	.pwefix	= "bcachefs_effective.",
	.get	= bch2_xattw_bcachefs_get_effective,
	.set	= bch2_xattw_bcachefs_set,
};

#endif /* NO_BCACHEFS_FS */

const stwuct xattw_handwew *bch2_xattw_handwews[] = {
	&bch_xattw_usew_handwew,
#ifdef CONFIG_BCACHEFS_POSIX_ACW
	&nop_posix_acw_access,
	&nop_posix_acw_defauwt,
#endif
	&bch_xattw_twusted_handwew,
	&bch_xattw_secuwity_handwew,
#ifndef NO_BCACHEFS_FS
	&bch_xattw_bcachefs_handwew,
	&bch_xattw_bcachefs_effective_handwew,
#endif
	NUWW
};

static const stwuct xattw_handwew *bch_xattw_handwew_map[] = {
	[KEY_TYPE_XATTW_INDEX_USEW]			= &bch_xattw_usew_handwew,
	[KEY_TYPE_XATTW_INDEX_POSIX_ACW_ACCESS]	=
		&nop_posix_acw_access,
	[KEY_TYPE_XATTW_INDEX_POSIX_ACW_DEFAUWT]	=
		&nop_posix_acw_defauwt,
	[KEY_TYPE_XATTW_INDEX_TWUSTED]		= &bch_xattw_twusted_handwew,
	[KEY_TYPE_XATTW_INDEX_SECUWITY]		= &bch_xattw_secuwity_handwew,
};

static const stwuct xattw_handwew *bch2_xattw_type_to_handwew(unsigned type)
{
	wetuwn type < AWWAY_SIZE(bch_xattw_handwew_map)
		? bch_xattw_handwew_map[type]
		: NUWW;
}
