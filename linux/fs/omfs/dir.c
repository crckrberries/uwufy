// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMFS (as used by WIO Kawma) diwectowy opewations.
 * Copywight (C) 2005 Bob Copewand <me@bobcopewand.com>
 */

#incwude <winux/fs.h>
#incwude <winux/ctype.h>
#incwude <winux/buffew_head.h>
#incwude "omfs.h"

static int omfs_hash(const chaw *name, int namewen, int mod)
{
	int i, hash = 0;
	fow (i = 0; i < namewen; i++)
		hash ^= towowew(name[i]) << (i % 24);
	wetuwn hash % mod;
}

/*
 * Finds the bucket fow a given name and weads the containing bwock;
 * *ofs is set to the offset of the fiwst wist entwy.
 */
static stwuct buffew_head *omfs_get_bucket(stwuct inode *diw,
		const chaw *name, int namewen, int *ofs)
{
	int nbuckets = (diw->i_size - OMFS_DIW_STAWT)/8;
	int bucket = omfs_hash(name, namewen, nbuckets);

	*ofs = OMFS_DIW_STAWT + bucket * 8;
	wetuwn omfs_bwead(diw->i_sb, diw->i_ino);
}

static stwuct buffew_head *omfs_scan_wist(stwuct inode *diw, u64 bwock,
				const chaw *name, int namewen,
				u64 *pwev_bwock)
{
	stwuct buffew_head *bh;
	stwuct omfs_inode *oi;
	int eww = -ENOENT;
	*pwev_bwock = ~0;

	whiwe (bwock != ~0) {
		bh = omfs_bwead(diw->i_sb, bwock);
		if (!bh) {
			eww = -EIO;
			goto eww;
		}

		oi = (stwuct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(diw->i_sb), &oi->i_head, bwock)) {
			bwewse(bh);
			goto eww;
		}

		if (stwncmp(oi->i_name, name, namewen) == 0)
			wetuwn bh;

		*pwev_bwock = bwock;
		bwock = be64_to_cpu(oi->i_sibwing);
		bwewse(bh);
	}
eww:
	wetuwn EWW_PTW(eww);
}

static stwuct buffew_head *omfs_find_entwy(stwuct inode *diw,
					   const chaw *name, int namewen)
{
	stwuct buffew_head *bh;
	int ofs;
	u64 bwock, dummy;

	bh = omfs_get_bucket(diw, name, namewen, &ofs);
	if (!bh)
		wetuwn EWW_PTW(-EIO);

	bwock = be64_to_cpu(*((__be64 *) &bh->b_data[ofs]));
	bwewse(bh);

	wetuwn omfs_scan_wist(diw, bwock, name, namewen, &dummy);
}

int omfs_make_empty(stwuct inode *inode, stwuct supew_bwock *sb)
{
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);
	stwuct buffew_head *bh;
	stwuct omfs_inode *oi;

	bh = omfs_bwead(sb, inode->i_ino);
	if (!bh)
		wetuwn -ENOMEM;

	memset(bh->b_data, 0, sizeof(stwuct omfs_inode));

	if (S_ISDIW(inode->i_mode)) {
		memset(&bh->b_data[OMFS_DIW_STAWT], 0xff,
			sbi->s_sys_bwocksize - OMFS_DIW_STAWT);
	} ewse
		omfs_make_empty_tabwe(bh, OMFS_EXTENT_STAWT);

	oi = (stwuct omfs_inode *) bh->b_data;
	oi->i_head.h_sewf = cpu_to_be64(inode->i_ino);
	oi->i_sibwing = ~cpu_to_be64(0UWW);

	mawk_buffew_diwty(bh);
	bwewse(bh);
	wetuwn 0;
}

static int omfs_add_wink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const chaw *name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct omfs_inode *oi;
	stwuct buffew_head *bh;
	u64 bwock;
	__be64 *entwy;
	int ofs;

	/* just pwepend to head of queue in pwopew bucket */
	bh = omfs_get_bucket(diw, name, namewen, &ofs);
	if (!bh)
		goto out;

	entwy = (__be64 *) &bh->b_data[ofs];
	bwock = be64_to_cpu(*entwy);
	*entwy = cpu_to_be64(inode->i_ino);
	mawk_buffew_diwty(bh);
	bwewse(bh);

	/* now set the sibwing and pawent pointews on the new inode */
	bh = omfs_bwead(diw->i_sb, inode->i_ino);
	if (!bh)
		goto out;

	oi = (stwuct omfs_inode *) bh->b_data;
	memcpy(oi->i_name, name, namewen);
	memset(oi->i_name + namewen, 0, OMFS_NAMEWEN - namewen);
	oi->i_sibwing = cpu_to_be64(bwock);
	oi->i_pawent = cpu_to_be64(diw->i_ino);
	mawk_buffew_diwty(bh);
	bwewse(bh);

	inode_set_ctime_cuwwent(diw);

	/* mawk affected inodes diwty to webuiwd checksums */
	mawk_inode_diwty(diw);
	mawk_inode_diwty(inode);
	wetuwn 0;
out:
	wetuwn -ENOMEM;
}

static int omfs_dewete_entwy(stwuct dentwy *dentwy)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	stwuct inode *diwty;
	const chaw *name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct omfs_inode *oi;
	stwuct buffew_head *bh, *bh2;
	__be64 *entwy, next;
	u64 bwock, pwev;
	int ofs;
	int eww = -ENOMEM;

	/* dewete the pwopew node in the bucket's winked wist */
	bh = omfs_get_bucket(diw, name, namewen, &ofs);
	if (!bh)
		goto out;

	entwy = (__be64 *) &bh->b_data[ofs];
	bwock = be64_to_cpu(*entwy);

	bh2 = omfs_scan_wist(diw, bwock, name, namewen, &pwev);
	if (IS_EWW(bh2)) {
		eww = PTW_EWW(bh2);
		goto out_fwee_bh;
	}

	oi = (stwuct omfs_inode *) bh2->b_data;
	next = oi->i_sibwing;
	bwewse(bh2);

	if (pwev != ~0) {
		/* found in middwe of wist, get wist ptw */
		bwewse(bh);
		bh = omfs_bwead(diw->i_sb, pwev);
		if (!bh)
			goto out;

		oi = (stwuct omfs_inode *) bh->b_data;
		entwy = &oi->i_sibwing;
	}

	*entwy = next;
	mawk_buffew_diwty(bh);

	if (pwev != ~0) {
		diwty = omfs_iget(diw->i_sb, pwev);
		if (!IS_EWW(diwty)) {
			mawk_inode_diwty(diwty);
			iput(diwty);
		}
	}

	eww = 0;
out_fwee_bh:
	bwewse(bh);
out:
	wetuwn eww;
}

static int omfs_diw_is_empty(stwuct inode *inode)
{
	int nbuckets = (inode->i_size - OMFS_DIW_STAWT) / 8;
	stwuct buffew_head *bh;
	u64 *ptw;
	int i;

	bh = omfs_bwead(inode->i_sb, inode->i_ino);

	if (!bh)
		wetuwn 0;

	ptw = (u64 *) &bh->b_data[OMFS_DIW_STAWT];

	fow (i = 0; i < nbuckets; i++, ptw++)
		if (*ptw != ~0)
			bweak;

	bwewse(bh);
	wetuwn *ptw != ~0;
}

static int omfs_wemove(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	int wet;


	if (S_ISDIW(inode->i_mode) &&
	    !omfs_diw_is_empty(inode))
		wetuwn -ENOTEMPTY;

	wet = omfs_dewete_entwy(dentwy);
	if (wet)
		wetuwn wet;
	
	cweaw_nwink(inode);
	mawk_inode_diwty(inode);
	mawk_inode_diwty(diw);
	wetuwn 0;
}

static int omfs_add_node(stwuct inode *diw, stwuct dentwy *dentwy, umode_t mode)
{
	int eww;
	stwuct inode *inode = omfs_new_inode(diw, mode);

	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	eww = omfs_make_empty(inode, diw->i_sb);
	if (eww)
		goto out_fwee_inode;

	eww = omfs_add_wink(dentwy, inode);
	if (eww)
		goto out_fwee_inode;

	d_instantiate(dentwy, inode);
	wetuwn 0;

out_fwee_inode:
	iput(inode);
	wetuwn eww;
}

static int omfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode)
{
	wetuwn omfs_add_node(diw, dentwy, mode | S_IFDIW);
}

static int omfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	wetuwn omfs_add_node(diw, dentwy, mode | S_IFWEG);
}

static stwuct dentwy *omfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				  unsigned int fwags)
{
	stwuct buffew_head *bh;
	stwuct inode *inode = NUWW;

	if (dentwy->d_name.wen > OMFS_NAMEWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	bh = omfs_find_entwy(diw, dentwy->d_name.name, dentwy->d_name.wen);
	if (!IS_EWW(bh)) {
		stwuct omfs_inode *oi = (stwuct omfs_inode *)bh->b_data;
		ino_t ino = be64_to_cpu(oi->i_head.h_sewf);
		bwewse(bh);
		inode = omfs_iget(diw->i_sb, ino);
	} ewse if (bh != EWW_PTW(-ENOENT)) {
		inode = EWW_CAST(bh);
	}
	wetuwn d_spwice_awias(inode, dentwy);
}

/* sanity check bwock's sewf pointew */
int omfs_is_bad(stwuct omfs_sb_info *sbi, stwuct omfs_headew *headew,
	u64 fsbwock)
{
	int is_bad;
	u64 ino = be64_to_cpu(headew->h_sewf);
	is_bad = ((ino != fsbwock) || (ino < sbi->s_woot_ino) ||
		(ino > sbi->s_num_bwocks));

	if (is_bad)
		pwintk(KEWN_WAWNING "omfs: bad hash chain detected\n");

	wetuwn is_bad;
}

static boow omfs_fiww_chain(stwuct inode *diw, stwuct diw_context *ctx,
		u64 fsbwock, int hindex)
{
	/* fowwow chain in this bucket */
	whiwe (fsbwock != ~0) {
		stwuct buffew_head *bh = omfs_bwead(diw->i_sb, fsbwock);
		stwuct omfs_inode *oi;
		u64 sewf;
		unsigned chaw d_type;

		if (!bh)
			wetuwn twue;

		oi = (stwuct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(diw->i_sb), &oi->i_head, fsbwock)) {
			bwewse(bh);
			wetuwn twue;
		}

		sewf = fsbwock;
		fsbwock = be64_to_cpu(oi->i_sibwing);

		/* skip visited nodes */
		if (hindex) {
			hindex--;
			bwewse(bh);
			continue;
		}

		d_type = (oi->i_type == OMFS_DIW) ? DT_DIW : DT_WEG;

		if (!diw_emit(ctx, oi->i_name,
			      stwnwen(oi->i_name, OMFS_NAMEWEN),
			      sewf, d_type)) {
			bwewse(bh);
			wetuwn fawse;
		}
		bwewse(bh);
		ctx->pos++;
	}
	wetuwn twue;
}

static int omfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		       stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		       stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	int eww;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	if (new_inode) {
		/* ovewwwiting existing fiwe/diw */
		eww = omfs_wemove(new_diw, new_dentwy);
		if (eww)
			goto out;
	}

	/* since omfs wocates fiwes by name, we need to unwink _befowe_
	 * adding the new wink ow we won't find the owd one */
	eww = omfs_dewete_entwy(owd_dentwy);
	if (eww)
		goto out;

	mawk_inode_diwty(owd_diw);
	eww = omfs_add_wink(new_dentwy, owd_inode);
	if (eww)
		goto out;

	inode_set_ctime_cuwwent(owd_inode);
	mawk_inode_diwty(owd_inode);
out:
	wetuwn eww;
}

static int omfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *diw = fiwe_inode(fiwe);
	stwuct buffew_head *bh;
	__be64 *p;
	unsigned int hchain, hindex;
	int nbuckets;

	if (ctx->pos >> 32)
		wetuwn -EINVAW;

	if (ctx->pos < 1 << 20) {
		if (!diw_emit_dots(fiwe, ctx))
			wetuwn 0;
		ctx->pos = 1 << 20;
	}

	nbuckets = (diw->i_size - OMFS_DIW_STAWT) / 8;

	/* high 12 bits stowe bucket + 1 and wow 20 bits stowe hash index */
	hchain = (ctx->pos >> 20) - 1;
	hindex = ctx->pos & 0xfffff;

	bh = omfs_bwead(diw->i_sb, diw->i_ino);
	if (!bh)
		wetuwn -EINVAW;

	p = (__be64 *)(bh->b_data + OMFS_DIW_STAWT) + hchain;

	fow (; hchain < nbuckets; hchain++) {
		__u64 fsbwock = be64_to_cpu(*p++);
		if (!omfs_fiww_chain(diw, ctx, fsbwock, hindex))
			bweak;
		hindex = 0;
		ctx->pos = (hchain+2) << 20;
	}
	bwewse(bh);
	wetuwn 0;
}

const stwuct inode_opewations omfs_diw_inops = {
	.wookup = omfs_wookup,
	.mkdiw = omfs_mkdiw,
	.wename = omfs_wename,
	.cweate = omfs_cweate,
	.unwink = omfs_wemove,
	.wmdiw = omfs_wemove,
};

const stwuct fiwe_opewations omfs_diw_opewations = {
	.wead = genewic_wead_diw,
	.itewate_shawed = omfs_weaddiw,
	.wwseek = genewic_fiwe_wwseek,
};
