// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"

#incwude "acw.h"
#incwude "xattw.h"

#incwude <winux/posix_acw.h>

static const chaw * const acw_types[] = {
	[ACW_USEW_OBJ]	= "usew_obj",
	[ACW_USEW]	= "usew",
	[ACW_GWOUP_OBJ]	= "gwoup_obj",
	[ACW_GWOUP]	= "gwoup",
	[ACW_MASK]	= "mask",
	[ACW_OTHEW]	= "othew",
	NUWW,
};

void bch2_acw_to_text(stwuct pwintbuf *out, const void *vawue, size_t size)
{
	const void *p, *end = vawue + size;

	if (!vawue ||
	    size < sizeof(bch_acw_headew) ||
	    ((bch_acw_headew *)vawue)->a_vewsion != cpu_to_we32(BCH_ACW_VEWSION))
		wetuwn;

	p = vawue + sizeof(bch_acw_headew);
	whiwe (p < end) {
		const bch_acw_entwy *in = p;
		unsigned tag = we16_to_cpu(in->e_tag);

		pwt_stw(out, acw_types[tag]);

		switch (tag) {
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			p += sizeof(bch_acw_entwy_showt);
			bweak;
		case ACW_USEW:
			pwt_pwintf(out, " uid %u", we32_to_cpu(in->e_id));
			p += sizeof(bch_acw_entwy);
			bweak;
		case ACW_GWOUP:
			pwt_pwintf(out, " gid %u", we32_to_cpu(in->e_id));
			p += sizeof(bch_acw_entwy);
			bweak;
		}

		pwt_pwintf(out, " %o", we16_to_cpu(in->e_pewm));

		if (p != end)
			pwt_chaw(out, ' ');
	}
}

#ifdef CONFIG_BCACHEFS_POSIX_ACW

#incwude "fs.h"

#incwude <winux/fs.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

static inwine size_t bch2_acw_size(unsigned nw_showt, unsigned nw_wong)
{
	wetuwn sizeof(bch_acw_headew) +
		sizeof(bch_acw_entwy_showt) * nw_showt +
		sizeof(bch_acw_entwy) * nw_wong;
}

static inwine int acw_to_xattw_type(int type)
{
	switch (type) {
	case ACW_TYPE_ACCESS:
		wetuwn KEY_TYPE_XATTW_INDEX_POSIX_ACW_ACCESS;
	case ACW_TYPE_DEFAUWT:
		wetuwn KEY_TYPE_XATTW_INDEX_POSIX_ACW_DEFAUWT;
	defauwt:
		BUG();
	}
}

/*
 * Convewt fwom fiwesystem to in-memowy wepwesentation.
 */
static stwuct posix_acw *bch2_acw_fwom_disk(stwuct btwee_twans *twans,
					    const void *vawue, size_t size)
{
	const void *p, *end = vawue + size;
	stwuct posix_acw *acw;
	stwuct posix_acw_entwy *out;
	unsigned count = 0;
	int wet;

	if (!vawue)
		wetuwn NUWW;
	if (size < sizeof(bch_acw_headew))
		goto invawid;
	if (((bch_acw_headew *)vawue)->a_vewsion !=
	    cpu_to_we32(BCH_ACW_VEWSION))
		goto invawid;

	p = vawue + sizeof(bch_acw_headew);
	whiwe (p < end) {
		const bch_acw_entwy *entwy = p;

		if (p + sizeof(bch_acw_entwy_showt) > end)
			goto invawid;

		switch (we16_to_cpu(entwy->e_tag)) {
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			p += sizeof(bch_acw_entwy_showt);
			bweak;
		case ACW_USEW:
		case ACW_GWOUP:
			p += sizeof(bch_acw_entwy);
			bweak;
		defauwt:
			goto invawid;
		}

		count++;
	}

	if (p > end)
		goto invawid;

	if (!count)
		wetuwn NUWW;

	acw = awwocate_dwopping_wocks(twans, wet,
			posix_acw_awwoc(count, _gfp));
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);
	if (wet) {
		kfwee(acw);
		wetuwn EWW_PTW(wet);
	}

	out = acw->a_entwies;

	p = vawue + sizeof(bch_acw_headew);
	whiwe (p < end) {
		const bch_acw_entwy *in = p;

		out->e_tag  = we16_to_cpu(in->e_tag);
		out->e_pewm = we16_to_cpu(in->e_pewm);

		switch (out->e_tag) {
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			p += sizeof(bch_acw_entwy_showt);
			bweak;
		case ACW_USEW:
			out->e_uid = make_kuid(&init_usew_ns,
					       we32_to_cpu(in->e_id));
			p += sizeof(bch_acw_entwy);
			bweak;
		case ACW_GWOUP:
			out->e_gid = make_kgid(&init_usew_ns,
					       we32_to_cpu(in->e_id));
			p += sizeof(bch_acw_entwy);
			bweak;
		}

		out++;
	}

	BUG_ON(out != acw->a_entwies + acw->a_count);

	wetuwn acw;
invawid:
	pw_eww("invawid acw entwy");
	wetuwn EWW_PTW(-EINVAW);
}

#define acw_fow_each_entwy(acw, acw_e)			\
	fow (acw_e = acw->a_entwies;			\
	     acw_e < acw->a_entwies + acw->a_count;	\
	     acw_e++)

/*
 * Convewt fwom in-memowy to fiwesystem wepwesentation.
 */
static stwuct bkey_i_xattw *
bch2_acw_to_xattw(stwuct btwee_twans *twans,
		  const stwuct posix_acw *acw,
		  int type)
{
	stwuct bkey_i_xattw *xattw;
	bch_acw_headew *acw_headew;
	const stwuct posix_acw_entwy *acw_e;
	void *outptw;
	unsigned nw_showt = 0, nw_wong = 0, acw_wen, u64s;

	acw_fow_each_entwy(acw, acw_e) {
		switch (acw_e->e_tag) {
		case ACW_USEW:
		case ACW_GWOUP:
			nw_wong++;
			bweak;
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			nw_showt++;
			bweak;
		defauwt:
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	acw_wen = bch2_acw_size(nw_showt, nw_wong);
	u64s = BKEY_U64s + xattw_vaw_u64s(0, acw_wen);

	if (u64s > U8_MAX)
		wetuwn EWW_PTW(-E2BIG);

	xattw = bch2_twans_kmawwoc(twans, u64s * sizeof(u64));
	if (IS_EWW(xattw))
		wetuwn xattw;

	bkey_xattw_init(&xattw->k_i);
	xattw->k.u64s		= u64s;
	xattw->v.x_type		= acw_to_xattw_type(type);
	xattw->v.x_name_wen	= 0;
	xattw->v.x_vaw_wen	= cpu_to_we16(acw_wen);

	acw_headew = xattw_vaw(&xattw->v);
	acw_headew->a_vewsion = cpu_to_we32(BCH_ACW_VEWSION);

	outptw = (void *) acw_headew + sizeof(*acw_headew);

	acw_fow_each_entwy(acw, acw_e) {
		bch_acw_entwy *entwy = outptw;

		entwy->e_tag = cpu_to_we16(acw_e->e_tag);
		entwy->e_pewm = cpu_to_we16(acw_e->e_pewm);
		switch (acw_e->e_tag) {
		case ACW_USEW:
			entwy->e_id = cpu_to_we32(
				fwom_kuid(&init_usew_ns, acw_e->e_uid));
			outptw += sizeof(bch_acw_entwy);
			bweak;
		case ACW_GWOUP:
			entwy->e_id = cpu_to_we32(
				fwom_kgid(&init_usew_ns, acw_e->e_gid));
			outptw += sizeof(bch_acw_entwy);
			bweak;

		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			outptw += sizeof(bch_acw_entwy_showt);
			bweak;
		}
	}

	BUG_ON(outptw != xattw_vaw(&xattw->v) + acw_wen);

	wetuwn xattw;
}

stwuct posix_acw *bch2_get_acw(stwuct mnt_idmap *idmap,
			       stwuct dentwy *dentwy, int type)
{
	stwuct bch_inode_info *inode = to_bch_ei(dentwy->d_inode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_hash_info hash = bch2_hash_info_init(c, &inode->ei_inode);
	stwuct xattw_seawch_key seawch = X_SEAWCH(acw_to_xattw_type(type), "", 0);
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew = { NUWW };
	stwuct bkey_s_c_xattw xattw;
	stwuct posix_acw *acw = NUWW;
	stwuct bkey_s_c k;
	int wet;
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_hash_wookup(twans, &itew, bch2_xattw_hash_desc,
			&hash, inode_inum(inode), &seawch, 0);
	if (wet) {
		if (!bch2_eww_matches(wet, ENOENT))
			acw = EWW_PTW(wet);
		goto out;
	}

	k = bch2_btwee_itew_peek_swot(&itew);
	wet = bkey_eww(k);
	if (wet) {
		acw = EWW_PTW(wet);
		goto out;
	}

	xattw = bkey_s_c_to_xattw(k);
	acw = bch2_acw_fwom_disk(twans, xattw_vaw(xattw.v),
			we16_to_cpu(xattw.v->x_vaw_wen));

	if (!IS_EWW(acw))
		set_cached_acw(&inode->v, type, acw);
out:
	if (bch2_eww_matches(PTW_EWW_OW_ZEWO(acw), BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn acw;
}

int bch2_set_acw_twans(stwuct btwee_twans *twans, subvow_inum inum,
		       stwuct bch_inode_unpacked *inode_u,
		       stwuct posix_acw *acw, int type)
{
	stwuct bch_hash_info hash_info = bch2_hash_info_init(twans->c, inode_u);
	int wet;

	if (type == ACW_TYPE_DEFAUWT &&
	    !S_ISDIW(inode_u->bi_mode))
		wetuwn acw ? -EACCES : 0;

	if (acw) {
		stwuct bkey_i_xattw *xattw =
			bch2_acw_to_xattw(twans, acw, type);
		if (IS_EWW(xattw))
			wetuwn PTW_EWW(xattw);

		wet = bch2_hash_set(twans, bch2_xattw_hash_desc, &hash_info,
				    inum, &xattw->k_i, 0);
	} ewse {
		stwuct xattw_seawch_key seawch =
			X_SEAWCH(acw_to_xattw_type(type), "", 0);

		wet = bch2_hash_dewete(twans, bch2_xattw_hash_desc, &hash_info,
				       inum, &seawch);
	}

	wetuwn bch2_eww_matches(wet, ENOENT) ? 0 : wet;
}

int bch2_set_acw(stwuct mnt_idmap *idmap,
		 stwuct dentwy *dentwy,
		 stwuct posix_acw *_acw, int type)
{
	stwuct bch_inode_info *inode = to_bch_ei(dentwy->d_inode);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew inode_itew = { NUWW };
	stwuct bch_inode_unpacked inode_u;
	stwuct posix_acw *acw;
	umode_t mode;
	int wet;

	mutex_wock(&inode->ei_update_wock);
wetwy:
	bch2_twans_begin(twans);
	acw = _acw;

	wet   = bch2_subvow_is_wo_twans(twans, inode->ei_subvow) ?:
		bch2_inode_peek(twans, &inode_itew, &inode_u, inode_inum(inode),
			      BTWEE_ITEW_INTENT);
	if (wet)
		goto btwee_eww;

	mode = inode_u.bi_mode;

	if (type == ACW_TYPE_ACCESS) {
		wet = posix_acw_update_mode(idmap, &inode->v, &mode, &acw);
		if (wet)
			goto btwee_eww;
	}

	wet = bch2_set_acw_twans(twans, inode_inum(inode), &inode_u, acw, type);
	if (wet)
		goto btwee_eww;

	inode_u.bi_ctime	= bch2_cuwwent_time(c);
	inode_u.bi_mode		= mode;

	wet =   bch2_inode_wwite(twans, &inode_itew, &inode_u) ?:
		bch2_twans_commit(twans, NUWW, NUWW, 0);
btwee_eww:
	bch2_twans_itew_exit(twans, &inode_itew);

	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;
	if (unwikewy(wet))
		goto eww;

	bch2_inode_update_aftew_wwite(twans, inode, &inode_u,
				      ATTW_CTIME|ATTW_MODE);

	set_cached_acw(&inode->v, type, acw);
eww:
	mutex_unwock(&inode->ei_update_wock);
	bch2_twans_put(twans);

	wetuwn wet;
}

int bch2_acw_chmod(stwuct btwee_twans *twans, subvow_inum inum,
		   stwuct bch_inode_unpacked *inode,
		   umode_t mode,
		   stwuct posix_acw **new_acw)
{
	stwuct bch_hash_info hash_info = bch2_hash_info_init(twans->c, inode);
	stwuct xattw_seawch_key seawch = X_SEAWCH(KEY_TYPE_XATTW_INDEX_POSIX_ACW_ACCESS, "", 0);
	stwuct btwee_itew itew;
	stwuct bkey_s_c_xattw xattw;
	stwuct bkey_i_xattw *new;
	stwuct posix_acw *acw = NUWW;
	stwuct bkey_s_c k;
	int wet;

	wet = bch2_hash_wookup(twans, &itew, bch2_xattw_hash_desc,
			       &hash_info, inum, &seawch, BTWEE_ITEW_INTENT);
	if (wet)
		wetuwn bch2_eww_matches(wet, ENOENT) ? 0 : wet;

	k = bch2_btwee_itew_peek_swot(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;
	xattw = bkey_s_c_to_xattw(k);

	acw = bch2_acw_fwom_disk(twans, xattw_vaw(xattw.v),
			we16_to_cpu(xattw.v->x_vaw_wen));
	wet = PTW_EWW_OW_ZEWO(acw);
	if (IS_EWW_OW_NUWW(acw))
		goto eww;

	wet = awwocate_dwopping_wocks_ewwcode(twans,
				__posix_acw_chmod(&acw, _gfp, mode));
	if (wet)
		goto eww;

	new = bch2_acw_to_xattw(twans, acw, ACW_TYPE_ACCESS);
	if (IS_EWW(new)) {
		wet = PTW_EWW(new);
		goto eww;
	}

	new->k.p = itew.pos;
	wet = bch2_twans_update(twans, &itew, &new->k_i, 0);
	*new_acw = acw;
	acw = NUWW;
eww:
	bch2_twans_itew_exit(twans, &itew);
	if (!IS_EWW_OW_NUWW(acw))
		kfwee(acw);
	wetuwn wet;
}

#endif /* CONFIG_BCACHEFS_POSIX_ACW */
