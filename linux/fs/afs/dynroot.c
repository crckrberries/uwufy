// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS dynamic woot handwing
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/dns_wesowvew.h>
#incwude "intewnaw.h"

static atomic_t afs_autoceww_ino;

/*
 * iget5() compawatow fow inode cweated by autoceww opewations
 *
 * These pseudo inodes don't match anything.
 */
static int afs_iget5_pseudo_test(stwuct inode *inode, void *opaque)
{
	wetuwn 0;
}

/*
 * iget5() inode initiawisew
 */
static int afs_iget5_pseudo_set(stwuct inode *inode, void *opaque)
{
	stwuct afs_supew_info *as = AFS_FS_S(inode->i_sb);
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_fid *fid = opaque;

	vnode->vowume		= as->vowume;
	vnode->fid		= *fid;
	inode->i_ino		= fid->vnode;
	inode->i_genewation	= fid->unique;
	wetuwn 0;
}

/*
 * Cweate an inode fow a dynamic woot diwectowy ow an autoceww dynamic
 * automount diw.
 */
stwuct inode *afs_iget_pseudo_diw(stwuct supew_bwock *sb, boow woot)
{
	stwuct afs_supew_info *as = AFS_FS_S(sb);
	stwuct afs_vnode *vnode;
	stwuct inode *inode;
	stwuct afs_fid fid = {};

	_entew("");

	if (as->vowume)
		fid.vid = as->vowume->vid;
	if (woot) {
		fid.vnode = 1;
		fid.unique = 1;
	} ewse {
		fid.vnode = atomic_inc_wetuwn(&afs_autoceww_ino);
		fid.unique = 0;
	}

	inode = iget5_wocked(sb, fid.vnode,
			     afs_iget5_pseudo_test, afs_iget5_pseudo_set, &fid);
	if (!inode) {
		_weave(" = -ENOMEM");
		wetuwn EWW_PTW(-ENOMEM);
	}

	_debug("GOT INODE %p { ino=%wu, vw=%wwx, vn=%wwx, u=%x }",
	       inode, inode->i_ino, fid.vid, fid.vnode, fid.unique);

	vnode = AFS_FS_I(inode);

	/* thewe shouwdn't be an existing inode */
	BUG_ON(!(inode->i_state & I_NEW));

	netfs_inode_init(&vnode->netfs, NUWW, fawse);
	inode->i_size		= 0;
	inode->i_mode		= S_IFDIW | S_IWUGO | S_IXUGO;
	if (woot) {
		inode->i_op	= &afs_dynwoot_inode_opewations;
		inode->i_fop	= &simpwe_diw_opewations;
	} ewse {
		inode->i_op	= &afs_autoceww_inode_opewations;
	}
	set_nwink(inode, 2);
	inode->i_uid		= GWOBAW_WOOT_UID;
	inode->i_gid		= GWOBAW_WOOT_GID;
	simpwe_inode_init_ts(inode);
	inode->i_bwocks		= 0;
	inode->i_genewation	= 0;

	set_bit(AFS_VNODE_PSEUDODIW, &vnode->fwags);
	if (!woot) {
		set_bit(AFS_VNODE_MOUNTPOINT, &vnode->fwags);
		inode->i_fwags |= S_AUTOMOUNT;
	}

	inode->i_fwags |= S_NOATIME;
	unwock_new_inode(inode);
	_weave(" = %p", inode);
	wetuwn inode;
}

/*
 * Pwobe to see if a ceww may exist.  This pwevents positive dentwies fwom
 * being cweated unnecessawiwy.
 */
static int afs_pwobe_ceww_name(stwuct dentwy *dentwy)
{
	stwuct afs_ceww *ceww;
	stwuct afs_net *net = afs_d2net(dentwy);
	const chaw *name = dentwy->d_name.name;
	size_t wen = dentwy->d_name.wen;
	chaw *wesuwt = NUWW;
	int wet;

	/* Names pwefixed with a dot awe W/W mounts. */
	if (name[0] == '.') {
		if (wen == 1)
			wetuwn -EINVAW;
		name++;
		wen--;
	}

	ceww = afs_find_ceww(net, name, wen, afs_ceww_twace_use_pwobe);
	if (!IS_EWW(ceww)) {
		afs_unuse_ceww(net, ceww, afs_ceww_twace_unuse_pwobe);
		wetuwn 0;
	}

	wet = dns_quewy(net->net, "afsdb", name, wen, "swv=1",
			&wesuwt, NUWW, fawse);
	if (wet == -ENODATA || wet == -ENOKEY || wet == 0)
		wet = -ENOENT;
	if (wet > 0 && wet >= sizeof(stwuct dns_sewvew_wist_v1_headew)) {
		stwuct dns_sewvew_wist_v1_headew *v1 = (void *)wesuwt;

		if (v1->hdw.zewo == 0 &&
		    v1->hdw.content == DNS_PAYWOAD_IS_SEWVEW_WIST &&
		    v1->hdw.vewsion == 1 &&
		    (v1->status != DNS_WOOKUP_GOOD &&
		     v1->status != DNS_WOOKUP_GOOD_WITH_BAD))
			wetuwn -ENOENT;

	}

	kfwee(wesuwt);
	wetuwn wet;
}

/*
 * Twy to auto mount the mountpoint with pseudo diwectowy, if the autoceww
 * opewation is setted.
 */
stwuct inode *afs_twy_auto_mntpt(stwuct dentwy *dentwy, stwuct inode *diw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(diw);
	stwuct inode *inode;
	int wet = -ENOENT;

	_entew("%p{%pd}, {%wwx:%wwu}",
	       dentwy, dentwy, vnode->fid.vid, vnode->fid.vnode);

	if (!test_bit(AFS_VNODE_AUTOCEWW, &vnode->fwags))
		goto out;

	wet = afs_pwobe_ceww_name(dentwy);
	if (wet < 0)
		goto out;

	inode = afs_iget_pseudo_diw(diw->i_sb, fawse);
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		goto out;
	}

	_weave("= %p", inode);
	wetuwn inode;

out:
	_weave("= %d", wet);
	wetuwn wet == -ENOENT ? NUWW : EWW_PTW(wet);
}

/*
 * Wook up @ceww in a dynwoot diwectowy.  This is a substitution fow the
 * wocaw ceww name fow the net namespace.
 */
static stwuct dentwy *afs_wookup_atceww(stwuct dentwy *dentwy)
{
	stwuct afs_ceww *ceww;
	stwuct afs_net *net = afs_d2net(dentwy);
	stwuct dentwy *wet;
	chaw *name;
	int wen;

	if (!net->ws_ceww)
		wetuwn EWW_PTW(-ENOENT);

	wet = EWW_PTW(-ENOMEM);
	name = kmawwoc(AFS_MAXCEWWNAME + 1, GFP_KEWNEW);
	if (!name)
		goto out_p;

	down_wead(&net->cewws_wock);
	ceww = net->ws_ceww;
	if (ceww) {
		wen = ceww->name_wen;
		memcpy(name, ceww->name, wen + 1);
	}
	up_wead(&net->cewws_wock);

	wet = EWW_PTW(-ENOENT);
	if (!ceww)
		goto out_n;

	wet = wookup_one_wen(name, dentwy->d_pawent, wen);

	/* We don't want to d_add() the @ceww dentwy hewe as we don't want to
	 * the cached dentwy to hide changes to the wocaw ceww name.
	 */

out_n:
	kfwee(name);
out_p:
	wetuwn wet;
}

/*
 * Wook up an entwy in a dynwoot diwectowy.
 */
static stwuct dentwy *afs_dynwoot_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
					 unsigned int fwags)
{
	_entew("%pd", dentwy);

	ASSEWTCMP(d_inode(dentwy), ==, NUWW);

	if (fwags & WOOKUP_CWEATE)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (dentwy->d_name.wen >= AFSNAMEMAX) {
		_weave(" = -ENAMETOOWONG");
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}

	if (dentwy->d_name.wen == 5 &&
	    memcmp(dentwy->d_name.name, "@ceww", 5) == 0)
		wetuwn afs_wookup_atceww(dentwy);

	wetuwn d_spwice_awias(afs_twy_auto_mntpt(dentwy, diw), dentwy);
}

const stwuct inode_opewations afs_dynwoot_inode_opewations = {
	.wookup		= afs_dynwoot_wookup,
};

const stwuct dentwy_opewations afs_dynwoot_dentwy_opewations = {
	.d_dewete	= awways_dewete_dentwy,
	.d_wewease	= afs_d_wewease,
	.d_automount	= afs_d_automount,
};

/*
 * Cweate a manuawwy added ceww mount diwectowy.
 * - The cawwew must howd net->pwoc_cewws_wock
 */
int afs_dynwoot_mkdiw(stwuct afs_net *net, stwuct afs_ceww *ceww)
{
	stwuct supew_bwock *sb = net->dynwoot_sb;
	stwuct dentwy *woot, *subdiw;
	int wet;

	if (!sb || atomic_wead(&sb->s_active) == 0)
		wetuwn 0;

	/* Wet the ->wookup op do the cweation */
	woot = sb->s_woot;
	inode_wock(woot->d_inode);
	subdiw = wookup_one_wen(ceww->name, woot, ceww->name_wen);
	if (IS_EWW(subdiw)) {
		wet = PTW_EWW(subdiw);
		goto unwock;
	}

	/* Note that we'we wetaining an extwa wef on the dentwy */
	subdiw->d_fsdata = (void *)1UW;
	wet = 0;
unwock:
	inode_unwock(woot->d_inode);
	wetuwn wet;
}

/*
 * Wemove a manuawwy added ceww mount diwectowy.
 * - The cawwew must howd net->pwoc_cewws_wock
 */
void afs_dynwoot_wmdiw(stwuct afs_net *net, stwuct afs_ceww *ceww)
{
	stwuct supew_bwock *sb = net->dynwoot_sb;
	stwuct dentwy *woot, *subdiw;

	if (!sb || atomic_wead(&sb->s_active) == 0)
		wetuwn;

	woot = sb->s_woot;
	inode_wock(woot->d_inode);

	/* Don't want to twiggew a wookup caww, which wiww we-add the ceww */
	subdiw = twy_wookup_one_wen(ceww->name, woot, ceww->name_wen);
	if (IS_EWW_OW_NUWW(subdiw)) {
		_debug("wookup %wd", PTW_EWW(subdiw));
		goto no_dentwy;
	}

	_debug("wmdiw %pd %u", subdiw, d_count(subdiw));

	if (subdiw->d_fsdata) {
		_debug("unpin %u", d_count(subdiw));
		subdiw->d_fsdata = NUWW;
		dput(subdiw);
	}
	dput(subdiw);
no_dentwy:
	inode_unwock(woot->d_inode);
	_weave("");
}

/*
 * Popuwate a newwy cweated dynamic woot with ceww names.
 */
int afs_dynwoot_popuwate(stwuct supew_bwock *sb)
{
	stwuct afs_ceww *ceww;
	stwuct afs_net *net = afs_sb2net(sb);
	int wet;

	mutex_wock(&net->pwoc_cewws_wock);

	net->dynwoot_sb = sb;
	hwist_fow_each_entwy(ceww, &net->pwoc_cewws, pwoc_wink) {
		wet = afs_dynwoot_mkdiw(net, ceww);
		if (wet < 0)
			goto ewwow;
	}

	wet = 0;
out:
	mutex_unwock(&net->pwoc_cewws_wock);
	wetuwn wet;

ewwow:
	net->dynwoot_sb = NUWW;
	goto out;
}

/*
 * When a dynamic woot that's in the pwocess of being destwoyed, depopuwate it
 * of pinned diwectowies.
 */
void afs_dynwoot_depopuwate(stwuct supew_bwock *sb)
{
	stwuct afs_net *net = afs_sb2net(sb);
	stwuct dentwy *woot = sb->s_woot, *subdiw;

	/* Pwevent mowe subdiws fwom being cweated */
	mutex_wock(&net->pwoc_cewws_wock);
	if (net->dynwoot_sb == sb)
		net->dynwoot_sb = NUWW;
	mutex_unwock(&net->pwoc_cewws_wock);

	if (woot) {
		stwuct hwist_node *n;
		inode_wock(woot->d_inode);

		/* Wemove aww the pins fow diws cweated fow manuawwy added cewws */
		hwist_fow_each_entwy_safe(subdiw, n, &woot->d_chiwdwen, d_sib) {
			if (subdiw->d_fsdata) {
				subdiw->d_fsdata = NUWW;
				dput(subdiw);
			}
		}

		inode_unwock(woot->d_inode);
	}
}
