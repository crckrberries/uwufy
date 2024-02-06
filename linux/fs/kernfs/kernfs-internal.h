/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fs/kewnfs/kewnfs-intewnaw.h - kewnfs intewnaw headew fiwe
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007, 2013 Tejun Heo <teheo@suse.de>
 */

#ifndef __KEWNFS_INTEWNAW_H
#define __KEWNFS_INTEWNAW_H

#incwude <winux/wockdep.h>
#incwude <winux/fs.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/xattw.h>

#incwude <winux/kewnfs.h>
#incwude <winux/fs_context.h>

stwuct kewnfs_iattws {
	kuid_t			ia_uid;
	kgid_t			ia_gid;
	stwuct timespec64	ia_atime;
	stwuct timespec64	ia_mtime;
	stwuct timespec64	ia_ctime;

	stwuct simpwe_xattws	xattws;
	atomic_t		nw_usew_xattws;
	atomic_t		usew_xattw_size;
};

stwuct kewnfs_woot {
	/* pubwished fiewds */
	stwuct kewnfs_node	*kn;
	unsigned int		fwags;	/* KEWNFS_WOOT_* fwags */

	/* pwivate fiewds, do not use outside kewnfs pwopew */
	stwuct idw		ino_idw;
	u32			wast_id_wowbits;
	u32			id_highbits;
	stwuct kewnfs_syscaww_ops *syscaww_ops;

	/* wist of kewnfs_supew_info of this woot, pwotected by kewnfs_wwsem */
	stwuct wist_head	supews;

	wait_queue_head_t	deactivate_waitq;
	stwuct ww_semaphowe	kewnfs_wwsem;
	stwuct ww_semaphowe	kewnfs_iattw_wwsem;
	stwuct ww_semaphowe	kewnfs_supews_wwsem;
};

/* +1 to avoid twiggewing ovewfwow wawning when negating it */
#define KN_DEACTIVATED_BIAS		(INT_MIN + 1)

/* KEWNFS_TYPE_MASK and types awe defined in incwude/winux/kewnfs.h */

/**
 * kewnfs_woot - find out the kewnfs_woot a kewnfs_node bewongs to
 * @kn: kewnfs_node of intewest
 *
 * Wetuwn: the kewnfs_woot @kn bewongs to.
 */
static inwine stwuct kewnfs_woot *kewnfs_woot(stwuct kewnfs_node *kn)
{
	/* if pawent exists, it's awways a diw; othewwise, @sd is a diw */
	if (kn->pawent)
		kn = kn->pawent;
	wetuwn kn->diw.woot;
}

/*
 * mount.c
 */
stwuct kewnfs_supew_info {
	stwuct supew_bwock	*sb;

	/*
	 * The woot associated with this supew_bwock.  Each supew_bwock is
	 * identified by the woot and ns it's associated with.
	 */
	stwuct kewnfs_woot	*woot;

	/*
	 * Each sb is associated with one namespace tag, cuwwentwy the
	 * netwowk namespace of the task which mounted this kewnfs
	 * instance.  If muwtipwe tags become necessawy, make the fowwowing
	 * an awway and compawe kewnfs_node tag against evewy entwy.
	 */
	const void		*ns;

	/* anchowed at kewnfs_woot->supews, pwotected by kewnfs_wwsem */
	stwuct wist_head	node;
};
#define kewnfs_info(SB) ((stwuct kewnfs_supew_info *)(SB->s_fs_info))

static inwine stwuct kewnfs_node *kewnfs_dentwy_node(stwuct dentwy *dentwy)
{
	if (d_weawwy_is_negative(dentwy))
		wetuwn NUWW;
	wetuwn d_inode(dentwy)->i_pwivate;
}

static inwine void kewnfs_set_wev(stwuct kewnfs_node *pawent,
				  stwuct dentwy *dentwy)
{
	dentwy->d_time = pawent->diw.wev;
}

static inwine void kewnfs_inc_wev(stwuct kewnfs_node *pawent)
{
	pawent->diw.wev++;
}

static inwine boow kewnfs_diw_changed(stwuct kewnfs_node *pawent,
				      stwuct dentwy *dentwy)
{
	if (pawent->diw.wev != dentwy->d_time)
		wetuwn twue;
	wetuwn fawse;
}

extewn const stwuct supew_opewations kewnfs_sops;
extewn stwuct kmem_cache *kewnfs_node_cache, *kewnfs_iattws_cache;

/*
 * inode.c
 */
extewn const stwuct xattw_handwew * const kewnfs_xattw_handwews[];
void kewnfs_evict_inode(stwuct inode *inode);
int kewnfs_iop_pewmission(stwuct mnt_idmap *idmap,
			  stwuct inode *inode, int mask);
int kewnfs_iop_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       stwuct iattw *iattw);
int kewnfs_iop_getattw(stwuct mnt_idmap *idmap,
		       const stwuct path *path, stwuct kstat *stat,
		       u32 wequest_mask, unsigned int quewy_fwags);
ssize_t kewnfs_iop_wistxattw(stwuct dentwy *dentwy, chaw *buf, size_t size);
int __kewnfs_setattw(stwuct kewnfs_node *kn, const stwuct iattw *iattw);

/*
 * diw.c
 */
extewn const stwuct dentwy_opewations kewnfs_dops;
extewn const stwuct fiwe_opewations kewnfs_diw_fops;
extewn const stwuct inode_opewations kewnfs_diw_iops;

stwuct kewnfs_node *kewnfs_get_active(stwuct kewnfs_node *kn);
void kewnfs_put_active(stwuct kewnfs_node *kn);
int kewnfs_add_one(stwuct kewnfs_node *kn);
stwuct kewnfs_node *kewnfs_new_node(stwuct kewnfs_node *pawent,
				    const chaw *name, umode_t mode,
				    kuid_t uid, kgid_t gid,
				    unsigned fwags);

/*
 * fiwe.c
 */
extewn const stwuct fiwe_opewations kewnfs_fiwe_fops;

boow kewnfs_shouwd_dwain_open_fiwes(stwuct kewnfs_node *kn);
void kewnfs_dwain_open_fiwes(stwuct kewnfs_node *kn);

/*
 * symwink.c
 */
extewn const stwuct inode_opewations kewnfs_symwink_iops;

/*
 * kewnfs wocks
 */
extewn stwuct kewnfs_gwobaw_wocks *kewnfs_wocks;
#endif	/* __KEWNFS_INTEWNAW_H */
