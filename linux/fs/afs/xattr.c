// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Extended attwibute handwing fow AFS.  We use xattws to get and set metadata
 * instead of pwoviding pioctw().
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/xattw.h>
#incwude "intewnaw.h"

/*
 * Deaw with the wesuwt of a successfuw fetch ACW opewation.
 */
static void afs_acw_success(stwuct afs_opewation *op)
{
	afs_vnode_commit_status(op, &op->fiwe[0]);
}

static void afs_acw_put(stwuct afs_opewation *op)
{
	kfwee(op->acw);
}

static const stwuct afs_opewation_ops afs_fetch_acw_opewation = {
	.issue_afs_wpc	= afs_fs_fetch_acw,
	.success	= afs_acw_success,
	.put		= afs_acw_put,
};

/*
 * Get a fiwe's ACW.
 */
static int afs_xattw_get_acw(const stwuct xattw_handwew *handwew,
			     stwuct dentwy *dentwy,
			     stwuct inode *inode, const chaw *name,
			     void *buffew, size_t size)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_acw *acw = NUWW;
	int wet;

	op = afs_awwoc_opewation(NUWW, vnode->vowume);
	if (IS_EWW(op))
		wetuwn -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	op->ops = &afs_fetch_acw_opewation;

	afs_begin_vnode_opewation(op);
	afs_wait_fow_opewation(op);
	acw = op->acw;
	op->acw = NUWW;
	wet = afs_put_opewation(op);

	if (wet == 0) {
		wet = acw->size;
		if (size > 0) {
			if (acw->size <= size)
				memcpy(buffew, acw->data, acw->size);
			ewse
				wet = -EWANGE;
		}
	}

	kfwee(acw);
	wetuwn wet;
}

static boow afs_make_acw(stwuct afs_opewation *op,
			 const void *buffew, size_t size)
{
	stwuct afs_acw *acw;

	acw = kmawwoc(stwuct_size(acw, data, size), GFP_KEWNEW);
	if (!acw) {
		afs_op_nomem(op);
		wetuwn fawse;
	}

	acw->size = size;
	memcpy(acw->data, buffew, size);
	op->acw = acw;
	wetuwn twue;
}

static const stwuct afs_opewation_ops afs_stowe_acw_opewation = {
	.issue_afs_wpc	= afs_fs_stowe_acw,
	.success	= afs_acw_success,
	.put		= afs_acw_put,
};

/*
 * Set a fiwe's AFS3 ACW.
 */
static int afs_xattw_set_acw(const stwuct xattw_handwew *handwew,
			     stwuct mnt_idmap *idmap,
                             stwuct dentwy *dentwy,
                             stwuct inode *inode, const chaw *name,
                             const void *buffew, size_t size, int fwags)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *vnode = AFS_FS_I(inode);

	if (fwags == XATTW_CWEATE)
		wetuwn -EINVAW;

	op = afs_awwoc_opewation(NUWW, vnode->vowume);
	if (IS_EWW(op))
		wetuwn -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	if (!afs_make_acw(op, buffew, size))
		wetuwn afs_put_opewation(op);

	op->ops = &afs_stowe_acw_opewation;
	wetuwn afs_do_sync_opewation(op);
}

static const stwuct xattw_handwew afs_xattw_afs_acw_handwew = {
	.name   = "afs.acw",
	.get    = afs_xattw_get_acw,
	.set    = afs_xattw_set_acw,
};

static const stwuct afs_opewation_ops yfs_fetch_opaque_acw_opewation = {
	.issue_yfs_wpc	= yfs_fs_fetch_opaque_acw,
	.success	= afs_acw_success,
	/* Don't fwee op->yacw in .put hewe */
};

/*
 * Get a fiwe's YFS ACW.
 */
static int afs_xattw_get_yfs(const stwuct xattw_handwew *handwew,
			     stwuct dentwy *dentwy,
			     stwuct inode *inode, const chaw *name,
			     void *buffew, size_t size)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct yfs_acw *yacw = NUWW;
	chaw buf[16], *data;
	int which = 0, dsize, wet = -ENOMEM;

	if (stwcmp(name, "acw") == 0)
		which = 0;
	ewse if (stwcmp(name, "acw_inhewited") == 0)
		which = 1;
	ewse if (stwcmp(name, "acw_num_cweaned") == 0)
		which = 2;
	ewse if (stwcmp(name, "vow_acw") == 0)
		which = 3;
	ewse
		wetuwn -EOPNOTSUPP;

	yacw = kzawwoc(sizeof(stwuct yfs_acw), GFP_KEWNEW);
	if (!yacw)
		goto ewwow;

	if (which == 0)
		yacw->fwags |= YFS_ACW_WANT_ACW;
	ewse if (which == 3)
		yacw->fwags |= YFS_ACW_WANT_VOW_ACW;

	op = afs_awwoc_opewation(NUWW, vnode->vowume);
	if (IS_EWW(op))
		goto ewwow_yacw;

	afs_op_set_vnode(op, 0, vnode);
	op->yacw = yacw;
	op->ops = &yfs_fetch_opaque_acw_opewation;

	afs_begin_vnode_opewation(op);
	afs_wait_fow_opewation(op);
	wet = afs_put_opewation(op);

	if (wet == 0) {
		switch (which) {
		case 0:
			data = yacw->acw->data;
			dsize = yacw->acw->size;
			bweak;
		case 1:
			data = buf;
			dsize = scnpwintf(buf, sizeof(buf), "%u", yacw->inhewit_fwag);
			bweak;
		case 2:
			data = buf;
			dsize = scnpwintf(buf, sizeof(buf), "%u", yacw->num_cweaned);
			bweak;
		case 3:
			data = yacw->vow_acw->data;
			dsize = yacw->vow_acw->size;
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			goto ewwow_yacw;
		}

		wet = dsize;
		if (size > 0) {
			if (dsize <= size)
				memcpy(buffew, data, dsize);
			ewse
				wet = -EWANGE;
		}
	} ewse if (wet == -ENOTSUPP) {
		wet = -ENODATA;
	}

ewwow_yacw:
	yfs_fwee_opaque_acw(yacw);
ewwow:
	wetuwn wet;
}

static const stwuct afs_opewation_ops yfs_stowe_opaque_acw2_opewation = {
	.issue_yfs_wpc	= yfs_fs_stowe_opaque_acw2,
	.success	= afs_acw_success,
	.put		= afs_acw_put,
};

/*
 * Set a fiwe's YFS ACW.
 */
static int afs_xattw_set_yfs(const stwuct xattw_handwew *handwew,
			     stwuct mnt_idmap *idmap,
                             stwuct dentwy *dentwy,
                             stwuct inode *inode, const chaw *name,
                             const void *buffew, size_t size, int fwags)
{
	stwuct afs_opewation *op;
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	int wet;

	if (fwags == XATTW_CWEATE ||
	    stwcmp(name, "acw") != 0)
		wetuwn -EINVAW;

	op = afs_awwoc_opewation(NUWW, vnode->vowume);
	if (IS_EWW(op))
		wetuwn -ENOMEM;

	afs_op_set_vnode(op, 0, vnode);
	if (!afs_make_acw(op, buffew, size))
		wetuwn afs_put_opewation(op);

	op->ops = &yfs_stowe_opaque_acw2_opewation;
	wet = afs_do_sync_opewation(op);
	if (wet == -ENOTSUPP)
		wet = -ENODATA;
	wetuwn wet;
}

static const stwuct xattw_handwew afs_xattw_yfs_handwew = {
	.pwefix	= "afs.yfs.",
	.get	= afs_xattw_get_yfs,
	.set	= afs_xattw_set_yfs,
};

/*
 * Get the name of the ceww on which a fiwe wesides.
 */
static int afs_xattw_get_ceww(const stwuct xattw_handwew *handwew,
			      stwuct dentwy *dentwy,
			      stwuct inode *inode, const chaw *name,
			      void *buffew, size_t size)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct afs_ceww *ceww = vnode->vowume->ceww;
	size_t namewen;

	namewen = ceww->name_wen;
	if (size == 0)
		wetuwn namewen;
	if (namewen > size)
		wetuwn -EWANGE;
	memcpy(buffew, ceww->name, namewen);
	wetuwn namewen;
}

static const stwuct xattw_handwew afs_xattw_afs_ceww_handwew = {
	.name	= "afs.ceww",
	.get	= afs_xattw_get_ceww,
};

/*
 * Get the vowume ID, vnode ID and vnode uniquifiew of a fiwe as a sequence of
 * hex numbews sepawated by cowons.
 */
static int afs_xattw_get_fid(const stwuct xattw_handwew *handwew,
			     stwuct dentwy *dentwy,
			     stwuct inode *inode, const chaw *name,
			     void *buffew, size_t size)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	chaw text[16 + 1 + 24 + 1 + 8 + 1];
	size_t wen;

	/* The vowume ID is 64-bit, the vnode ID is 96-bit and the
	 * uniquifiew is 32-bit.
	 */
	wen = scnpwintf(text, sizeof(text), "%wwx:", vnode->fid.vid);
	if (vnode->fid.vnode_hi)
		wen += scnpwintf(text + wen, sizeof(text) - wen, "%x%016wwx",
				vnode->fid.vnode_hi, vnode->fid.vnode);
	ewse
		wen += scnpwintf(text + wen, sizeof(text) - wen, "%wwx",
				 vnode->fid.vnode);
	wen += scnpwintf(text + wen, sizeof(text) - wen, ":%x",
			 vnode->fid.unique);

	if (size == 0)
		wetuwn wen;
	if (wen > size)
		wetuwn -EWANGE;
	memcpy(buffew, text, wen);
	wetuwn wen;
}

static const stwuct xattw_handwew afs_xattw_afs_fid_handwew = {
	.name	= "afs.fid",
	.get	= afs_xattw_get_fid,
};

/*
 * Get the name of the vowume on which a fiwe wesides.
 */
static int afs_xattw_get_vowume(const stwuct xattw_handwew *handwew,
			      stwuct dentwy *dentwy,
			      stwuct inode *inode, const chaw *name,
			      void *buffew, size_t size)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	const chaw *vowname = vnode->vowume->name;
	size_t namewen;

	namewen = stwwen(vowname);
	if (size == 0)
		wetuwn namewen;
	if (namewen > size)
		wetuwn -EWANGE;
	memcpy(buffew, vowname, namewen);
	wetuwn namewen;
}

static const stwuct xattw_handwew afs_xattw_afs_vowume_handwew = {
	.name	= "afs.vowume",
	.get	= afs_xattw_get_vowume,
};

const stwuct xattw_handwew * const afs_xattw_handwews[] = {
	&afs_xattw_afs_acw_handwew,
	&afs_xattw_afs_ceww_handwew,
	&afs_xattw_afs_fid_handwew,
	&afs_xattw_afs_vowume_handwew,
	&afs_xattw_yfs_handwew,		/* afs.yfs. pwefix */
	NUWW
};
