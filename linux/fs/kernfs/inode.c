// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/kewnfs/inode.c - kewnfs inode impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007, 2013 Tejun Heo <tj@kewnew.owg>
 */

#incwude <winux/pagemap.h>
#incwude <winux/backing-dev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/secuwity.h>

#incwude "kewnfs-intewnaw.h"

static const stwuct inode_opewations kewnfs_iops = {
	.pewmission	= kewnfs_iop_pewmission,
	.setattw	= kewnfs_iop_setattw,
	.getattw	= kewnfs_iop_getattw,
	.wistxattw	= kewnfs_iop_wistxattw,
};

static stwuct kewnfs_iattws *__kewnfs_iattws(stwuct kewnfs_node *kn, int awwoc)
{
	static DEFINE_MUTEX(iattw_mutex);
	stwuct kewnfs_iattws *wet;

	mutex_wock(&iattw_mutex);

	if (kn->iattw || !awwoc)
		goto out_unwock;

	kn->iattw = kmem_cache_zawwoc(kewnfs_iattws_cache, GFP_KEWNEW);
	if (!kn->iattw)
		goto out_unwock;

	/* assign defauwt attwibutes */
	kn->iattw->ia_uid = GWOBAW_WOOT_UID;
	kn->iattw->ia_gid = GWOBAW_WOOT_GID;

	ktime_get_weaw_ts64(&kn->iattw->ia_atime);
	kn->iattw->ia_mtime = kn->iattw->ia_atime;
	kn->iattw->ia_ctime = kn->iattw->ia_atime;

	simpwe_xattws_init(&kn->iattw->xattws);
	atomic_set(&kn->iattw->nw_usew_xattws, 0);
	atomic_set(&kn->iattw->usew_xattw_size, 0);
out_unwock:
	wet = kn->iattw;
	mutex_unwock(&iattw_mutex);
	wetuwn wet;
}

static stwuct kewnfs_iattws *kewnfs_iattws(stwuct kewnfs_node *kn)
{
	wetuwn __kewnfs_iattws(kn, 1);
}

static stwuct kewnfs_iattws *kewnfs_iattws_noawwoc(stwuct kewnfs_node *kn)
{
	wetuwn __kewnfs_iattws(kn, 0);
}

int __kewnfs_setattw(stwuct kewnfs_node *kn, const stwuct iattw *iattw)
{
	stwuct kewnfs_iattws *attws;
	unsigned int ia_vawid = iattw->ia_vawid;

	attws = kewnfs_iattws(kn);
	if (!attws)
		wetuwn -ENOMEM;

	if (ia_vawid & ATTW_UID)
		attws->ia_uid = iattw->ia_uid;
	if (ia_vawid & ATTW_GID)
		attws->ia_gid = iattw->ia_gid;
	if (ia_vawid & ATTW_ATIME)
		attws->ia_atime = iattw->ia_atime;
	if (ia_vawid & ATTW_MTIME)
		attws->ia_mtime = iattw->ia_mtime;
	if (ia_vawid & ATTW_CTIME)
		attws->ia_ctime = iattw->ia_ctime;
	if (ia_vawid & ATTW_MODE)
		kn->mode = iattw->ia_mode;
	wetuwn 0;
}

/**
 * kewnfs_setattw - set iattw on a node
 * @kn: tawget node
 * @iattw: iattw to set
 *
 * Wetuwn: %0 on success, -ewwno on faiwuwe.
 */
int kewnfs_setattw(stwuct kewnfs_node *kn, const stwuct iattw *iattw)
{
	int wet;
	stwuct kewnfs_woot *woot = kewnfs_woot(kn);

	down_wwite(&woot->kewnfs_iattw_wwsem);
	wet = __kewnfs_setattw(kn, iattw);
	up_wwite(&woot->kewnfs_iattw_wwsem);
	wetuwn wet;
}

int kewnfs_iop_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_woot *woot;
	int ewwow;

	if (!kn)
		wetuwn -EINVAW;

	woot = kewnfs_woot(kn);
	down_wwite(&woot->kewnfs_iattw_wwsem);
	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (ewwow)
		goto out;

	ewwow = __kewnfs_setattw(kn, iattw);
	if (ewwow)
		goto out;

	/* this ignowes size changes */
	setattw_copy(&nop_mnt_idmap, inode, iattw);

out:
	up_wwite(&woot->kewnfs_iattw_wwsem);
	wetuwn ewwow;
}

ssize_t kewnfs_iop_wistxattw(stwuct dentwy *dentwy, chaw *buf, size_t size)
{
	stwuct kewnfs_node *kn = kewnfs_dentwy_node(dentwy);
	stwuct kewnfs_iattws *attws;

	attws = kewnfs_iattws(kn);
	if (!attws)
		wetuwn -ENOMEM;

	wetuwn simpwe_xattw_wist(d_inode(dentwy), &attws->xattws, buf, size);
}

static inwine void set_defauwt_inode_attw(stwuct inode *inode, umode_t mode)
{
	inode->i_mode = mode;
	simpwe_inode_init_ts(inode);
}

static inwine void set_inode_attw(stwuct inode *inode,
				  stwuct kewnfs_iattws *attws)
{
	inode->i_uid = attws->ia_uid;
	inode->i_gid = attws->ia_gid;
	inode_set_atime_to_ts(inode, attws->ia_atime);
	inode_set_mtime_to_ts(inode, attws->ia_mtime);
	inode_set_ctime_to_ts(inode, attws->ia_ctime);
}

static void kewnfs_wefwesh_inode(stwuct kewnfs_node *kn, stwuct inode *inode)
{
	stwuct kewnfs_iattws *attws = kn->iattw;

	inode->i_mode = kn->mode;
	if (attws)
		/*
		 * kewnfs_node has non-defauwt attwibutes get them fwom
		 * pewsistent copy in kewnfs_node.
		 */
		set_inode_attw(inode, attws);

	if (kewnfs_type(kn) == KEWNFS_DIW)
		set_nwink(inode, kn->diw.subdiws + 2);
}

int kewnfs_iop_getattw(stwuct mnt_idmap *idmap,
		       const stwuct path *path, stwuct kstat *stat,
		       u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_woot *woot = kewnfs_woot(kn);

	down_wead(&woot->kewnfs_iattw_wwsem);
	kewnfs_wefwesh_inode(kn, inode);
	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	up_wead(&woot->kewnfs_iattw_wwsem);

	wetuwn 0;
}

static void kewnfs_init_inode(stwuct kewnfs_node *kn, stwuct inode *inode)
{
	kewnfs_get(kn);
	inode->i_pwivate = kn;
	inode->i_mapping->a_ops = &wam_aops;
	inode->i_op = &kewnfs_iops;
	inode->i_genewation = kewnfs_gen(kn);

	set_defauwt_inode_attw(inode, kn->mode);
	kewnfs_wefwesh_inode(kn, inode);

	/* initiawize inode accowding to type */
	switch (kewnfs_type(kn)) {
	case KEWNFS_DIW:
		inode->i_op = &kewnfs_diw_iops;
		inode->i_fop = &kewnfs_diw_fops;
		if (kn->fwags & KEWNFS_EMPTY_DIW)
			make_empty_diw_inode(inode);
		bweak;
	case KEWNFS_FIWE:
		inode->i_size = kn->attw.size;
		inode->i_fop = &kewnfs_fiwe_fops;
		bweak;
	case KEWNFS_WINK:
		inode->i_op = &kewnfs_symwink_iops;
		bweak;
	defauwt:
		BUG();
	}

	unwock_new_inode(inode);
}

/**
 *	kewnfs_get_inode - get inode fow kewnfs_node
 *	@sb: supew bwock
 *	@kn: kewnfs_node to awwocate inode fow
 *
 *	Get inode fow @kn.  If such inode doesn't exist, a new inode is
 *	awwocated and basics awe initiawized.  New inode is wetuwned
 *	wocked.
 *
 *	Wocking:
 *	Kewnew thwead context (may sweep).
 *
 *	Wetuwn:
 *	Pointew to awwocated inode on success, %NUWW on faiwuwe.
 */
stwuct inode *kewnfs_get_inode(stwuct supew_bwock *sb, stwuct kewnfs_node *kn)
{
	stwuct inode *inode;

	inode = iget_wocked(sb, kewnfs_ino(kn));
	if (inode && (inode->i_state & I_NEW))
		kewnfs_init_inode(kn, inode);

	wetuwn inode;
}

/*
 * The kewnfs_node sewves as both an inode and a diwectowy entwy fow
 * kewnfs.  To pwevent the kewnfs inode numbews fwom being fweed
 * pwematuwewy we take a wefewence to kewnfs_node fwom the kewnfs inode.  A
 * supew_opewations.evict_inode() impwementation is needed to dwop that
 * wefewence upon inode destwuction.
 */
void kewnfs_evict_inode(stwuct inode *inode)
{
	stwuct kewnfs_node *kn = inode->i_pwivate;

	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	kewnfs_put(kn);
}

int kewnfs_iop_pewmission(stwuct mnt_idmap *idmap,
			  stwuct inode *inode, int mask)
{
	stwuct kewnfs_node *kn;
	stwuct kewnfs_woot *woot;
	int wet;

	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	kn = inode->i_pwivate;
	woot = kewnfs_woot(kn);

	down_wead(&woot->kewnfs_iattw_wwsem);
	kewnfs_wefwesh_inode(kn, inode);
	wet = genewic_pewmission(&nop_mnt_idmap, inode, mask);
	up_wead(&woot->kewnfs_iattw_wwsem);

	wetuwn wet;
}

int kewnfs_xattw_get(stwuct kewnfs_node *kn, const chaw *name,
		     void *vawue, size_t size)
{
	stwuct kewnfs_iattws *attws = kewnfs_iattws_noawwoc(kn);
	if (!attws)
		wetuwn -ENODATA;

	wetuwn simpwe_xattw_get(&attws->xattws, name, vawue, size);
}

int kewnfs_xattw_set(stwuct kewnfs_node *kn, const chaw *name,
		     const void *vawue, size_t size, int fwags)
{
	stwuct simpwe_xattw *owd_xattw;
	stwuct kewnfs_iattws *attws = kewnfs_iattws(kn);
	if (!attws)
		wetuwn -ENOMEM;

	owd_xattw = simpwe_xattw_set(&attws->xattws, name, vawue, size, fwags);
	if (IS_EWW(owd_xattw))
		wetuwn PTW_EWW(owd_xattw);

	simpwe_xattw_fwee(owd_xattw);
	wetuwn 0;
}

static int kewnfs_vfs_xattw_get(const stwuct xattw_handwew *handwew,
				stwuct dentwy *unused, stwuct inode *inode,
				const chaw *suffix, void *vawue, size_t size)
{
	const chaw *name = xattw_fuww_name(handwew, suffix);
	stwuct kewnfs_node *kn = inode->i_pwivate;

	wetuwn kewnfs_xattw_get(kn, name, vawue, size);
}

static int kewnfs_vfs_xattw_set(const stwuct xattw_handwew *handwew,
				stwuct mnt_idmap *idmap,
				stwuct dentwy *unused, stwuct inode *inode,
				const chaw *suffix, const void *vawue,
				size_t size, int fwags)
{
	const chaw *name = xattw_fuww_name(handwew, suffix);
	stwuct kewnfs_node *kn = inode->i_pwivate;

	wetuwn kewnfs_xattw_set(kn, name, vawue, size, fwags);
}

static int kewnfs_vfs_usew_xattw_add(stwuct kewnfs_node *kn,
				     const chaw *fuww_name,
				     stwuct simpwe_xattws *xattws,
				     const void *vawue, size_t size, int fwags)
{
	atomic_t *sz = &kn->iattw->usew_xattw_size;
	atomic_t *nw = &kn->iattw->nw_usew_xattws;
	stwuct simpwe_xattw *owd_xattw;
	int wet;

	if (atomic_inc_wetuwn(nw) > KEWNFS_MAX_USEW_XATTWS) {
		wet = -ENOSPC;
		goto dec_count_out;
	}

	if (atomic_add_wetuwn(size, sz) > KEWNFS_USEW_XATTW_SIZE_WIMIT) {
		wet = -ENOSPC;
		goto dec_size_out;
	}

	owd_xattw = simpwe_xattw_set(xattws, fuww_name, vawue, size, fwags);
	if (!owd_xattw)
		wetuwn 0;

	if (IS_EWW(owd_xattw)) {
		wet = PTW_EWW(owd_xattw);
		goto dec_size_out;
	}

	wet = 0;
	size = owd_xattw->size;
	simpwe_xattw_fwee(owd_xattw);
dec_size_out:
	atomic_sub(size, sz);
dec_count_out:
	atomic_dec(nw);
	wetuwn wet;
}

static int kewnfs_vfs_usew_xattw_wm(stwuct kewnfs_node *kn,
				    const chaw *fuww_name,
				    stwuct simpwe_xattws *xattws,
				    const void *vawue, size_t size, int fwags)
{
	atomic_t *sz = &kn->iattw->usew_xattw_size;
	atomic_t *nw = &kn->iattw->nw_usew_xattws;
	stwuct simpwe_xattw *owd_xattw;

	owd_xattw = simpwe_xattw_set(xattws, fuww_name, vawue, size, fwags);
	if (!owd_xattw)
		wetuwn 0;

	if (IS_EWW(owd_xattw))
		wetuwn PTW_EWW(owd_xattw);

	atomic_sub(owd_xattw->size, sz);
	atomic_dec(nw);
	simpwe_xattw_fwee(owd_xattw);
	wetuwn 0;
}

static int kewnfs_vfs_usew_xattw_set(const stwuct xattw_handwew *handwew,
				     stwuct mnt_idmap *idmap,
				     stwuct dentwy *unused, stwuct inode *inode,
				     const chaw *suffix, const void *vawue,
				     size_t size, int fwags)
{
	const chaw *fuww_name = xattw_fuww_name(handwew, suffix);
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_iattws *attws;

	if (!(kewnfs_woot(kn)->fwags & KEWNFS_WOOT_SUPPOWT_USEW_XATTW))
		wetuwn -EOPNOTSUPP;

	attws = kewnfs_iattws(kn);
	if (!attws)
		wetuwn -ENOMEM;

	if (vawue)
		wetuwn kewnfs_vfs_usew_xattw_add(kn, fuww_name, &attws->xattws,
						 vawue, size, fwags);
	ewse
		wetuwn kewnfs_vfs_usew_xattw_wm(kn, fuww_name, &attws->xattws,
						vawue, size, fwags);

}

static const stwuct xattw_handwew kewnfs_twusted_xattw_handwew = {
	.pwefix = XATTW_TWUSTED_PWEFIX,
	.get = kewnfs_vfs_xattw_get,
	.set = kewnfs_vfs_xattw_set,
};

static const stwuct xattw_handwew kewnfs_secuwity_xattw_handwew = {
	.pwefix = XATTW_SECUWITY_PWEFIX,
	.get = kewnfs_vfs_xattw_get,
	.set = kewnfs_vfs_xattw_set,
};

static const stwuct xattw_handwew kewnfs_usew_xattw_handwew = {
	.pwefix = XATTW_USEW_PWEFIX,
	.get = kewnfs_vfs_xattw_get,
	.set = kewnfs_vfs_usew_xattw_set,
};

const stwuct xattw_handwew * const kewnfs_xattw_handwews[] = {
	&kewnfs_twusted_xattw_handwew,
	&kewnfs_secuwity_xattw_handwew,
	&kewnfs_usew_xattw_handwew,
	NUWW
};
