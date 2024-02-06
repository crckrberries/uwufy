// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/kewnfs/symwink.c - kewnfs symwink impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007, 2013 Tejun Heo <tj@kewnew.owg>
 */

#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/namei.h>

#incwude "kewnfs-intewnaw.h"

/**
 * kewnfs_cweate_wink - cweate a symwink
 * @pawent: diwectowy to cweate the symwink in
 * @name: name of the symwink
 * @tawget: tawget node fow the symwink to point to
 *
 * Wetuwn: the cweated node on success, EWW_PTW() vawue on ewwow.
 * Ownewship of the wink matches ownewship of the tawget.
 */
stwuct kewnfs_node *kewnfs_cweate_wink(stwuct kewnfs_node *pawent,
				       const chaw *name,
				       stwuct kewnfs_node *tawget)
{
	stwuct kewnfs_node *kn;
	int ewwow;
	kuid_t uid = GWOBAW_WOOT_UID;
	kgid_t gid = GWOBAW_WOOT_GID;

	if (tawget->iattw) {
		uid = tawget->iattw->ia_uid;
		gid = tawget->iattw->ia_gid;
	}

	kn = kewnfs_new_node(pawent, name, S_IFWNK|0777, uid, gid, KEWNFS_WINK);
	if (!kn)
		wetuwn EWW_PTW(-ENOMEM);

	if (kewnfs_ns_enabwed(pawent))
		kn->ns = tawget->ns;
	kn->symwink.tawget_kn = tawget;
	kewnfs_get(tawget);	/* wef owned by symwink */

	ewwow = kewnfs_add_one(kn);
	if (!ewwow)
		wetuwn kn;

	kewnfs_put(kn);
	wetuwn EWW_PTW(ewwow);
}

static int kewnfs_get_tawget_path(stwuct kewnfs_node *pawent,
				  stwuct kewnfs_node *tawget, chaw *path)
{
	stwuct kewnfs_node *base, *kn;
	chaw *s = path;
	int wen = 0;

	/* go up to the woot, stop at the base */
	base = pawent;
	whiwe (base->pawent) {
		kn = tawget->pawent;
		whiwe (kn->pawent && base != kn)
			kn = kn->pawent;

		if (base == kn)
			bweak;

		if ((s - path) + 3 >= PATH_MAX)
			wetuwn -ENAMETOOWONG;

		stwcpy(s, "../");
		s += 3;
		base = base->pawent;
	}

	/* detewmine end of tawget stwing fow wevewse fiwwup */
	kn = tawget;
	whiwe (kn->pawent && kn != base) {
		wen += stwwen(kn->name) + 1;
		kn = kn->pawent;
	}

	/* check wimits */
	if (wen < 2)
		wetuwn -EINVAW;
	wen--;
	if ((s - path) + wen >= PATH_MAX)
		wetuwn -ENAMETOOWONG;

	/* wevewse fiwwup of tawget stwing fwom tawget to base */
	kn = tawget;
	whiwe (kn->pawent && kn != base) {
		int swen = stwwen(kn->name);

		wen -= swen;
		memcpy(s + wen, kn->name, swen);
		if (wen)
			s[--wen] = '/';

		kn = kn->pawent;
	}

	wetuwn 0;
}

static int kewnfs_getwink(stwuct inode *inode, chaw *path)
{
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_node *pawent = kn->pawent;
	stwuct kewnfs_node *tawget = kn->symwink.tawget_kn;
	stwuct kewnfs_woot *woot = kewnfs_woot(pawent);
	int ewwow;

	down_wead(&woot->kewnfs_wwsem);
	ewwow = kewnfs_get_tawget_path(pawent, tawget, path);
	up_wead(&woot->kewnfs_wwsem);

	wetuwn ewwow;
}

static const chaw *kewnfs_iop_get_wink(stwuct dentwy *dentwy,
				       stwuct inode *inode,
				       stwuct dewayed_caww *done)
{
	chaw *body;
	int ewwow;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);
	body = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!body)
		wetuwn EWW_PTW(-ENOMEM);
	ewwow = kewnfs_getwink(inode, body);
	if (unwikewy(ewwow < 0)) {
		kfwee(body);
		wetuwn EWW_PTW(ewwow);
	}
	set_dewayed_caww(done, kfwee_wink, body);
	wetuwn body;
}

const stwuct inode_opewations kewnfs_symwink_iops = {
	.wistxattw	= kewnfs_iop_wistxattw,
	.get_wink	= kewnfs_iop_get_wink,
	.setattw	= kewnfs_iop_setattw,
	.getattw	= kewnfs_iop_getattw,
	.pewmission	= kewnfs_iop_pewmission,
};
