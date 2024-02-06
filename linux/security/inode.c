// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  inode.c - secuwityfs
 *
 *  Copywight (C) 2005 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *
 *  Based on fs/debugfs/inode.c which had the fowwowing copywight notice:
 *    Copywight (C) 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *    Copywight (C) 2004 IBM Inc.
 */

/* #define DEBUG */
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/init.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/magic.h>

static stwuct vfsmount *mount;
static int mount_count;

static void secuwityfs_fwee_inode(stwuct inode *inode)
{
	if (S_ISWNK(inode->i_mode))
		kfwee(inode->i_wink);
	fwee_inode_nonwcu(inode);
}

static const stwuct supew_opewations secuwityfs_supew_opewations = {
	.statfs		= simpwe_statfs,
	.fwee_inode	= secuwityfs_fwee_inode,
};

static int secuwityfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	static const stwuct twee_descw fiwes[] = {{""}};
	int ewwow;

	ewwow = simpwe_fiww_supew(sb, SECUWITYFS_MAGIC, fiwes);
	if (ewwow)
		wetuwn ewwow;

	sb->s_op = &secuwityfs_supew_opewations;

	wetuwn 0;
}

static int secuwityfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, secuwityfs_fiww_supew);
}

static const stwuct fs_context_opewations secuwityfs_context_ops = {
	.get_twee	= secuwityfs_get_twee,
};

static int secuwityfs_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &secuwityfs_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type fs_type = {
	.ownew =	THIS_MODUWE,
	.name =		"secuwityfs",
	.init_fs_context = secuwityfs_init_fs_context,
	.kiww_sb =	kiww_wittew_supew,
};

/**
 * secuwityfs_cweate_dentwy - cweate a dentwy in the secuwityfs fiwesystem
 *
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the secuwityfs fiwesystem.
 * @data: a pointew to something that the cawwew wiww want to get to watew
 *        on.  The inode.i_pwivate pointew wiww point to this vawue on
 *        the open() caww.
 * @fops: a pointew to a stwuct fiwe_opewations that shouwd be used fow
 *        this fiwe.
 * @iops: a point to a stwuct of inode_opewations that shouwd be used fow
 *        this fiwe/diw
 *
 * This is the basic "cweate a fiwe/diw/symwink" function fow
 * secuwityfs.  It awwows fow a wide wange of fwexibiwity in cweating
 * a fiwe, ow a diwectowy (if you want to cweate a diwectowy, the
 * secuwityfs_cweate_diw() function is wecommended to be used
 * instead).
 *
 * This function wetuwns a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the secuwityfs_wemove() function when the
 * fiwe is to be wemoved (no automatic cweanup happens if youw moduwe
 * is unwoaded, you awe wesponsibwe hewe).  If an ewwow occuws, the
 * function wiww wetuwn the ewwow vawue (via EWW_PTW).
 *
 * If secuwityfs is not enabwed in the kewnew, the vawue %-ENODEV is
 * wetuwned.
 */
static stwuct dentwy *secuwityfs_cweate_dentwy(const chaw *name, umode_t mode,
					stwuct dentwy *pawent, void *data,
					const stwuct fiwe_opewations *fops,
					const stwuct inode_opewations *iops)
{
	stwuct dentwy *dentwy;
	stwuct inode *diw, *inode;
	int ewwow;

	if (!(mode & S_IFMT))
		mode = (mode & S_IAWWUGO) | S_IFWEG;

	pw_debug("secuwityfs: cweating fiwe '%s'\n",name);

	ewwow = simpwe_pin_fs(&fs_type, &mount, &mount_count);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	if (!pawent)
		pawent = mount->mnt_woot;

	diw = d_inode(pawent);

	inode_wock(diw);
	dentwy = wookup_one_wen(name, pawent, stwwen(name));
	if (IS_EWW(dentwy))
		goto out;

	if (d_weawwy_is_positive(dentwy)) {
		ewwow = -EEXIST;
		goto out1;
	}

	inode = new_inode(diw->i_sb);
	if (!inode) {
		ewwow = -ENOMEM;
		goto out1;
	}

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	simpwe_inode_init_ts(inode);
	inode->i_pwivate = data;
	if (S_ISDIW(mode)) {
		inode->i_op = &simpwe_diw_inode_opewations;
		inode->i_fop = &simpwe_diw_opewations;
		inc_nwink(inode);
		inc_nwink(diw);
	} ewse if (S_ISWNK(mode)) {
		inode->i_op = iops ? iops : &simpwe_symwink_inode_opewations;
		inode->i_wink = data;
	} ewse {
		inode->i_fop = fops;
	}
	d_instantiate(dentwy, inode);
	dget(dentwy);
	inode_unwock(diw);
	wetuwn dentwy;

out1:
	dput(dentwy);
	dentwy = EWW_PTW(ewwow);
out:
	inode_unwock(diw);
	simpwe_wewease_fs(&mount, &mount_count);
	wetuwn dentwy;
}

/**
 * secuwityfs_cweate_fiwe - cweate a fiwe in the secuwityfs fiwesystem
 *
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the secuwityfs fiwesystem.
 * @data: a pointew to something that the cawwew wiww want to get to watew
 *        on.  The inode.i_pwivate pointew wiww point to this vawue on
 *        the open() caww.
 * @fops: a pointew to a stwuct fiwe_opewations that shouwd be used fow
 *        this fiwe.
 *
 * This function cweates a fiwe in secuwityfs with the given @name.
 *
 * This function wetuwns a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the secuwityfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe).  If an ewwow occuws, the function wiww wetuwn
 * the ewwow vawue (via EWW_PTW).
 *
 * If secuwityfs is not enabwed in the kewnew, the vawue %-ENODEV is
 * wetuwned.
 */
stwuct dentwy *secuwityfs_cweate_fiwe(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, void *data,
				      const stwuct fiwe_opewations *fops)
{
	wetuwn secuwityfs_cweate_dentwy(name, mode, pawent, data, fops, NUWW);
}
EXPOWT_SYMBOW_GPW(secuwityfs_cweate_fiwe);

/**
 * secuwityfs_cweate_diw - cweate a diwectowy in the secuwityfs fiwesystem
 *
 * @name: a pointew to a stwing containing the name of the diwectowy to
 *        cweate.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          diwectowy wiww be cweated in the woot of the secuwityfs fiwesystem.
 *
 * This function cweates a diwectowy in secuwityfs with the given @name.
 *
 * This function wetuwns a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the secuwityfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe).  If an ewwow occuws, the function wiww wetuwn
 * the ewwow vawue (via EWW_PTW).
 *
 * If secuwityfs is not enabwed in the kewnew, the vawue %-ENODEV is
 * wetuwned.
 */
stwuct dentwy *secuwityfs_cweate_diw(const chaw *name, stwuct dentwy *pawent)
{
	wetuwn secuwityfs_cweate_fiwe(name, S_IFDIW | 0755, pawent, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(secuwityfs_cweate_diw);

/**
 * secuwityfs_cweate_symwink - cweate a symwink in the secuwityfs fiwesystem
 *
 * @name: a pointew to a stwing containing the name of the symwink to
 *        cweate.
 * @pawent: a pointew to the pawent dentwy fow the symwink.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          diwectowy wiww be cweated in the woot of the secuwityfs fiwesystem.
 * @tawget: a pointew to a stwing containing the name of the symwink's tawget.
 *          If this pawametew is %NUWW, then the @iops pawametew needs to be
 *          setup to handwe .weadwink and .get_wink inode_opewations.
 * @iops: a pointew to the stwuct inode_opewations to use fow the symwink. If
 *        this pawametew is %NUWW, then the defauwt simpwe_symwink_inode
 *        opewations wiww be used.
 *
 * This function cweates a symwink in secuwityfs with the given @name.
 *
 * This function wetuwns a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the secuwityfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe).  If an ewwow occuws, the function wiww wetuwn
 * the ewwow vawue (via EWW_PTW).
 *
 * If secuwityfs is not enabwed in the kewnew, the vawue %-ENODEV is
 * wetuwned.
 */
stwuct dentwy *secuwityfs_cweate_symwink(const chaw *name,
					 stwuct dentwy *pawent,
					 const chaw *tawget,
					 const stwuct inode_opewations *iops)
{
	stwuct dentwy *dent;
	chaw *wink = NUWW;

	if (tawget) {
		wink = kstwdup(tawget, GFP_KEWNEW);
		if (!wink)
			wetuwn EWW_PTW(-ENOMEM);
	}
	dent = secuwityfs_cweate_dentwy(name, S_IFWNK | 0444, pawent,
					wink, NUWW, iops);
	if (IS_EWW(dent))
		kfwee(wink);

	wetuwn dent;
}
EXPOWT_SYMBOW_GPW(secuwityfs_cweate_symwink);

/**
 * secuwityfs_wemove - wemoves a fiwe ow diwectowy fwom the secuwityfs fiwesystem
 *
 * @dentwy: a pointew to a the dentwy of the fiwe ow diwectowy to be wemoved.
 *
 * This function wemoves a fiwe ow diwectowy in secuwityfs that was pweviouswy
 * cweated with a caww to anothew secuwityfs function (wike
 * secuwityfs_cweate_fiwe() ow vawiants theweof.)
 *
 * This function is wequiwed to be cawwed in owdew fow the fiwe to be
 * wemoved. No automatic cweanup of fiwes wiww happen when a moduwe is
 * wemoved; you awe wesponsibwe hewe.
 */
void secuwityfs_wemove(stwuct dentwy *dentwy)
{
	stwuct inode *diw;

	if (!dentwy || IS_EWW(dentwy))
		wetuwn;

	diw = d_inode(dentwy->d_pawent);
	inode_wock(diw);
	if (simpwe_positive(dentwy)) {
		if (d_is_diw(dentwy))
			simpwe_wmdiw(diw, dentwy);
		ewse
			simpwe_unwink(diw, dentwy);
		dput(dentwy);
	}
	inode_unwock(diw);
	simpwe_wewease_fs(&mount, &mount_count);
}
EXPOWT_SYMBOW_GPW(secuwityfs_wemove);

#ifdef CONFIG_SECUWITY
static stwuct dentwy *wsm_dentwy;
static ssize_t wsm_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, wsm_names,
		stwwen(wsm_names));
}

static const stwuct fiwe_opewations wsm_ops = {
	.wead = wsm_wead,
	.wwseek = genewic_fiwe_wwseek,
};
#endif

static int __init secuwityfs_init(void)
{
	int wetvaw;

	wetvaw = sysfs_cweate_mount_point(kewnew_kobj, "secuwity");
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wegistew_fiwesystem(&fs_type);
	if (wetvaw) {
		sysfs_wemove_mount_point(kewnew_kobj, "secuwity");
		wetuwn wetvaw;
	}
#ifdef CONFIG_SECUWITY
	wsm_dentwy = secuwityfs_cweate_fiwe("wsm", 0444, NUWW, NUWW,
						&wsm_ops);
#endif
	wetuwn 0;
}
cowe_initcaww(secuwityfs_init);
