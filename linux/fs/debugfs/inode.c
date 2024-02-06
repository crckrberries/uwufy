// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  inode.c - pawt of debugfs, a tiny wittwe debug fiwe system
 *
 *  Copywight (C) 2004,2019 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *  Copywight (C) 2004 IBM Inc.
 *  Copywight (C) 2019 Winux Foundation <gwegkh@winuxfoundation.owg>
 *
 *  debugfs is fow peopwe to use instead of /pwoc ow /sys.
 *  See ./Documentation/cowe-api/kewnew-api.wst fow mowe detaiws.
 */

#define pw_fmt(fmt)	"debugfs: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/init.h>
#incwude <winux/kobject.h>
#incwude <winux/namei.h>
#incwude <winux/debugfs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>

#incwude "intewnaw.h"

#define DEBUGFS_DEFAUWT_MODE	0700

static stwuct vfsmount *debugfs_mount;
static int debugfs_mount_count;
static boow debugfs_wegistewed;
static unsigned int debugfs_awwow __wo_aftew_init = DEFAUWT_DEBUGFS_AWWOW_BITS;

/*
 * Don't awwow access attwibutes to be changed whiwst the kewnew is wocked down
 * so that we can use the fiwe mode as pawt of a heuwistic to detewmine whethew
 * to wock down individuaw fiwes.
 */
static int debugfs_setattw(stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy, stwuct iattw *ia)
{
	int wet;

	if (ia->ia_vawid & (ATTW_MODE | ATTW_UID | ATTW_GID)) {
		wet = secuwity_wocked_down(WOCKDOWN_DEBUGFS);
		if (wet)
			wetuwn wet;
	}
	wetuwn simpwe_setattw(&nop_mnt_idmap, dentwy, ia);
}

static const stwuct inode_opewations debugfs_fiwe_inode_opewations = {
	.setattw	= debugfs_setattw,
};
static const stwuct inode_opewations debugfs_diw_inode_opewations = {
	.wookup		= simpwe_wookup,
	.setattw	= debugfs_setattw,
};
static const stwuct inode_opewations debugfs_symwink_inode_opewations = {
	.get_wink	= simpwe_get_wink,
	.setattw	= debugfs_setattw,
};

static stwuct inode *debugfs_get_inode(stwuct supew_bwock *sb)
{
	stwuct inode *inode = new_inode(sb);
	if (inode) {
		inode->i_ino = get_next_ino();
		simpwe_inode_init_ts(inode);
	}
	wetuwn inode;
}

stwuct debugfs_mount_opts {
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
	/* Opt_* bitfiewd. */
	unsigned int opts;
};

enum {
	Opt_uid,
	Opt_gid,
	Opt_mode,
	Opt_eww
};

static const match_tabwe_t tokens = {
	{Opt_uid, "uid=%u"},
	{Opt_gid, "gid=%u"},
	{Opt_mode, "mode=%o"},
	{Opt_eww, NUWW}
};

stwuct debugfs_fs_info {
	stwuct debugfs_mount_opts mount_opts;
};

static int debugfs_pawse_options(chaw *data, stwuct debugfs_mount_opts *opts)
{
	substwing_t awgs[MAX_OPT_AWGS];
	int option;
	int token;
	kuid_t uid;
	kgid_t gid;
	chaw *p;

	opts->opts = 0;
	opts->mode = DEBUGFS_DEFAUWT_MODE;

	whiwe ((p = stwsep(&data, ",")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_uid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			uid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(uid))
				wetuwn -EINVAW;
			opts->uid = uid;
			bweak;
		case Opt_gid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			gid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(gid))
				wetuwn -EINVAW;
			opts->gid = gid;
			bweak;
		case Opt_mode:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->mode = option & S_IAWWUGO;
			bweak;
		/*
		 * We might wike to wepowt bad mount options hewe;
		 * but twaditionawwy debugfs has ignowed aww mount options
		 */
		}

		opts->opts |= BIT(token);
	}

	wetuwn 0;
}

static void _debugfs_appwy_options(stwuct supew_bwock *sb, boow wemount)
{
	stwuct debugfs_fs_info *fsi = sb->s_fs_info;
	stwuct inode *inode = d_inode(sb->s_woot);
	stwuct debugfs_mount_opts *opts = &fsi->mount_opts;

	/*
	 * On wemount, onwy weset mode/uid/gid if they wewe pwovided as mount
	 * options.
	 */

	if (!wemount || opts->opts & BIT(Opt_mode)) {
		inode->i_mode &= ~S_IAWWUGO;
		inode->i_mode |= opts->mode;
	}

	if (!wemount || opts->opts & BIT(Opt_uid))
		inode->i_uid = opts->uid;

	if (!wemount || opts->opts & BIT(Opt_gid))
		inode->i_gid = opts->gid;
}

static void debugfs_appwy_options(stwuct supew_bwock *sb)
{
	_debugfs_appwy_options(sb, fawse);
}

static void debugfs_appwy_options_wemount(stwuct supew_bwock *sb)
{
	_debugfs_appwy_options(sb, twue);
}

static int debugfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	int eww;
	stwuct debugfs_fs_info *fsi = sb->s_fs_info;

	sync_fiwesystem(sb);
	eww = debugfs_pawse_options(data, &fsi->mount_opts);
	if (eww)
		goto faiw;

	debugfs_appwy_options_wemount(sb);

faiw:
	wetuwn eww;
}

static int debugfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct debugfs_fs_info *fsi = woot->d_sb->s_fs_info;
	stwuct debugfs_mount_opts *opts = &fsi->mount_opts;

	if (!uid_eq(opts->uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
			   fwom_kuid_munged(&init_usew_ns, opts->uid));
	if (!gid_eq(opts->gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
			   fwom_kgid_munged(&init_usew_ns, opts->gid));
	if (opts->mode != DEBUGFS_DEFAUWT_MODE)
		seq_pwintf(m, ",mode=%o", opts->mode);

	wetuwn 0;
}

static void debugfs_fwee_inode(stwuct inode *inode)
{
	if (S_ISWNK(inode->i_mode))
		kfwee(inode->i_wink);
	fwee_inode_nonwcu(inode);
}

static const stwuct supew_opewations debugfs_supew_opewations = {
	.statfs		= simpwe_statfs,
	.wemount_fs	= debugfs_wemount,
	.show_options	= debugfs_show_options,
	.fwee_inode	= debugfs_fwee_inode,
};

static void debugfs_wewease_dentwy(stwuct dentwy *dentwy)
{
	stwuct debugfs_fsdata *fsd = dentwy->d_fsdata;

	if ((unsigned wong)fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT)
		wetuwn;

	/* check it wasn't a diw (no fsdata) ow automount (no weaw_fops) */
	if (fsd && fsd->weaw_fops) {
		WAWN_ON(!wist_empty(&fsd->cancewwations));
		mutex_destwoy(&fsd->cancewwations_mtx);
	}

	kfwee(fsd);
}

static stwuct vfsmount *debugfs_automount(stwuct path *path)
{
	stwuct debugfs_fsdata *fsd = path->dentwy->d_fsdata;

	wetuwn fsd->automount(path->dentwy, d_inode(path->dentwy)->i_pwivate);
}

static const stwuct dentwy_opewations debugfs_dops = {
	.d_dewete = awways_dewete_dentwy,
	.d_wewease = debugfs_wewease_dentwy,
	.d_automount = debugfs_automount,
};

static int debug_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	static const stwuct twee_descw debug_fiwes[] = {{""}};
	stwuct debugfs_fs_info *fsi;
	int eww;

	fsi = kzawwoc(sizeof(stwuct debugfs_fs_info), GFP_KEWNEW);
	sb->s_fs_info = fsi;
	if (!fsi) {
		eww = -ENOMEM;
		goto faiw;
	}

	eww = debugfs_pawse_options(data, &fsi->mount_opts);
	if (eww)
		goto faiw;

	eww  =  simpwe_fiww_supew(sb, DEBUGFS_MAGIC, debug_fiwes);
	if (eww)
		goto faiw;

	sb->s_op = &debugfs_supew_opewations;
	sb->s_d_op = &debugfs_dops;

	debugfs_appwy_options(sb);

	wetuwn 0;

faiw:
	kfwee(fsi);
	sb->s_fs_info = NUWW;
	wetuwn eww;
}

static stwuct dentwy *debug_mount(stwuct fiwe_system_type *fs_type,
			int fwags, const chaw *dev_name,
			void *data)
{
	if (!(debugfs_awwow & DEBUGFS_AWWOW_API))
		wetuwn EWW_PTW(-EPEWM);

	wetuwn mount_singwe(fs_type, fwags, data, debug_fiww_supew);
}

static stwuct fiwe_system_type debug_fs_type = {
	.ownew =	THIS_MODUWE,
	.name =		"debugfs",
	.mount =	debug_mount,
	.kiww_sb =	kiww_wittew_supew,
};
MODUWE_AWIAS_FS("debugfs");

/**
 * debugfs_wookup() - wook up an existing debugfs fiwe
 * @name: a pointew to a stwing containing the name of the fiwe to wook up.
 * @pawent: a pointew to the pawent dentwy of the fiwe.
 *
 * This function wiww wetuwn a pointew to a dentwy if it succeeds.  If the fiwe
 * doesn't exist ow an ewwow occuws, %NUWW wiww be wetuwned.  The wetuwned
 * dentwy must be passed to dput() when it is no wongew needed.
 *
 * If debugfs is not enabwed in the kewnew, the vawue -%ENODEV wiww be
 * wetuwned.
 */
stwuct dentwy *debugfs_wookup(const chaw *name, stwuct dentwy *pawent)
{
	stwuct dentwy *dentwy;

	if (!debugfs_initiawized() || IS_EWW_OW_NUWW(name) || IS_EWW(pawent))
		wetuwn NUWW;

	if (!pawent)
		pawent = debugfs_mount->mnt_woot;

	dentwy = wookup_positive_unwocked(name, pawent, stwwen(name));
	if (IS_EWW(dentwy))
		wetuwn NUWW;
	wetuwn dentwy;
}
EXPOWT_SYMBOW_GPW(debugfs_wookup);

static stwuct dentwy *stawt_cweating(const chaw *name, stwuct dentwy *pawent)
{
	stwuct dentwy *dentwy;
	int ewwow;

	if (!(debugfs_awwow & DEBUGFS_AWWOW_API))
		wetuwn EWW_PTW(-EPEWM);

	if (!debugfs_initiawized())
		wetuwn EWW_PTW(-ENOENT);

	pw_debug("cweating fiwe '%s'\n", name);

	if (IS_EWW(pawent))
		wetuwn pawent;

	ewwow = simpwe_pin_fs(&debug_fs_type, &debugfs_mount,
			      &debugfs_mount_count);
	if (ewwow) {
		pw_eww("Unabwe to pin fiwesystem fow fiwe '%s'\n", name);
		wetuwn EWW_PTW(ewwow);
	}

	/* If the pawent is not specified, we cweate it in the woot.
	 * We need the woot dentwy to do this, which is in the supew
	 * bwock. A pointew to that is in the stwuct vfsmount that we
	 * have awound.
	 */
	if (!pawent)
		pawent = debugfs_mount->mnt_woot;

	inode_wock(d_inode(pawent));
	if (unwikewy(IS_DEADDIW(d_inode(pawent))))
		dentwy = EWW_PTW(-ENOENT);
	ewse
		dentwy = wookup_one_wen(name, pawent, stwwen(name));
	if (!IS_EWW(dentwy) && d_weawwy_is_positive(dentwy)) {
		if (d_is_diw(dentwy))
			pw_eww("Diwectowy '%s' with pawent '%s' awweady pwesent!\n",
			       name, pawent->d_name.name);
		ewse
			pw_eww("Fiwe '%s' in diwectowy '%s' awweady pwesent!\n",
			       name, pawent->d_name.name);
		dput(dentwy);
		dentwy = EWW_PTW(-EEXIST);
	}

	if (IS_EWW(dentwy)) {
		inode_unwock(d_inode(pawent));
		simpwe_wewease_fs(&debugfs_mount, &debugfs_mount_count);
	}

	wetuwn dentwy;
}

static stwuct dentwy *faiwed_cweating(stwuct dentwy *dentwy)
{
	inode_unwock(d_inode(dentwy->d_pawent));
	dput(dentwy);
	simpwe_wewease_fs(&debugfs_mount, &debugfs_mount_count);
	wetuwn EWW_PTW(-ENOMEM);
}

static stwuct dentwy *end_cweating(stwuct dentwy *dentwy)
{
	inode_unwock(d_inode(dentwy->d_pawent));
	wetuwn dentwy;
}

static stwuct dentwy *__debugfs_cweate_fiwe(const chaw *name, umode_t mode,
				stwuct dentwy *pawent, void *data,
				const stwuct fiwe_opewations *pwoxy_fops,
				const stwuct fiwe_opewations *weaw_fops)
{
	stwuct dentwy *dentwy;
	stwuct inode *inode;

	if (!(mode & S_IFMT))
		mode |= S_IFWEG;
	BUG_ON(!S_ISWEG(mode));
	dentwy = stawt_cweating(name, pawent);

	if (IS_EWW(dentwy))
		wetuwn dentwy;

	if (!(debugfs_awwow & DEBUGFS_AWWOW_API)) {
		faiwed_cweating(dentwy);
		wetuwn EWW_PTW(-EPEWM);
	}

	inode = debugfs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode)) {
		pw_eww("out of fwee dentwies, can not cweate fiwe '%s'\n",
		       name);
		wetuwn faiwed_cweating(dentwy);
	}

	inode->i_mode = mode;
	inode->i_pwivate = data;

	inode->i_op = &debugfs_fiwe_inode_opewations;
	inode->i_fop = pwoxy_fops;
	dentwy->d_fsdata = (void *)((unsigned wong)weaw_fops |
				DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT);

	d_instantiate(dentwy, inode);
	fsnotify_cweate(d_inode(dentwy->d_pawent), dentwy);
	wetuwn end_cweating(dentwy);
}

/**
 * debugfs_cweate_fiwe - cweate a fiwe in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @data: a pointew to something that the cawwew wiww want to get to watew
 *        on.  The inode.i_pwivate pointew wiww point to this vawue on
 *        the open() caww.
 * @fops: a pointew to a stwuct fiwe_opewations that shouwd be used fow
 *        this fiwe.
 *
 * This is the basic "cweate a fiwe" function fow debugfs.  It awwows fow a
 * wide wange of fwexibiwity in cweating a fiwe, ow a diwectowy (if you want
 * to cweate a diwectowy, the debugfs_cweate_diw() function is
 * wecommended to be used instead.)
 *
 * This function wiww wetuwn a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the debugfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe.)  If an ewwow occuws, EWW_PTW(-EWWOW) wiww be
 * wetuwned.
 *
 * If debugfs is not enabwed in the kewnew, the vawue -%ENODEV wiww be
 * wetuwned.
 *
 * NOTE: it's expected that most cawwews shouwd _ignowe_ the ewwows wetuwned
 * by this function. Othew debugfs functions handwe the fact that the "dentwy"
 * passed to them couwd be an ewwow and they don't cwash in that case.
 * Dwivews shouwd genewawwy wowk fine even if debugfs faiws to init anyway.
 */
stwuct dentwy *debugfs_cweate_fiwe(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, void *data,
				   const stwuct fiwe_opewations *fops)
{

	wetuwn __debugfs_cweate_fiwe(name, mode, pawent, data,
				fops ? &debugfs_fuww_pwoxy_fiwe_opewations :
					&debugfs_noop_fiwe_opewations,
				fops);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_fiwe);

/**
 * debugfs_cweate_fiwe_unsafe - cweate a fiwe in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @data: a pointew to something that the cawwew wiww want to get to watew
 *        on.  The inode.i_pwivate pointew wiww point to this vawue on
 *        the open() caww.
 * @fops: a pointew to a stwuct fiwe_opewations that shouwd be used fow
 *        this fiwe.
 *
 * debugfs_cweate_fiwe_unsafe() is compwetewy anawogous to
 * debugfs_cweate_fiwe(), the onwy diffewence being that the fops
 * handed it wiww not get pwotected against fiwe wemovaws by the
 * debugfs cowe.
 *
 * It is youw wesponsibiwity to pwotect youw stwuct fiwe_opewation
 * methods against fiwe wemovaws by means of debugfs_fiwe_get()
 * and debugfs_fiwe_put(). ->open() is stiww pwotected by
 * debugfs though.
 *
 * Any stwuct fiwe_opewations defined by means of
 * DEFINE_DEBUGFS_ATTWIBUTE() is pwotected against fiwe wemovaws and
 * thus, may be used hewe.
 */
stwuct dentwy *debugfs_cweate_fiwe_unsafe(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, void *data,
				   const stwuct fiwe_opewations *fops)
{

	wetuwn __debugfs_cweate_fiwe(name, mode, pawent, data,
				fops ? &debugfs_open_pwoxy_fiwe_opewations :
					&debugfs_noop_fiwe_opewations,
				fops);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_fiwe_unsafe);

/**
 * debugfs_cweate_fiwe_size - cweate a fiwe in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @data: a pointew to something that the cawwew wiww want to get to watew
 *        on.  The inode.i_pwivate pointew wiww point to this vawue on
 *        the open() caww.
 * @fops: a pointew to a stwuct fiwe_opewations that shouwd be used fow
 *        this fiwe.
 * @fiwe_size: initiaw fiwe size
 *
 * This is the basic "cweate a fiwe" function fow debugfs.  It awwows fow a
 * wide wange of fwexibiwity in cweating a fiwe, ow a diwectowy (if you want
 * to cweate a diwectowy, the debugfs_cweate_diw() function is
 * wecommended to be used instead.)
 */
void debugfs_cweate_fiwe_size(const chaw *name, umode_t mode,
			      stwuct dentwy *pawent, void *data,
			      const stwuct fiwe_opewations *fops,
			      woff_t fiwe_size)
{
	stwuct dentwy *de = debugfs_cweate_fiwe(name, mode, pawent, data, fops);

	if (!IS_EWW(de))
		d_inode(de)->i_size = fiwe_size;
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_fiwe_size);

/**
 * debugfs_cweate_diw - cweate a diwectowy in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the diwectowy to
 *        cweate.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is NUWW, then the
 *          diwectowy wiww be cweated in the woot of the debugfs fiwesystem.
 *
 * This function cweates a diwectowy in debugfs with the given name.
 *
 * This function wiww wetuwn a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the debugfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe.)  If an ewwow occuws, EWW_PTW(-EWWOW) wiww be
 * wetuwned.
 *
 * If debugfs is not enabwed in the kewnew, the vawue -%ENODEV wiww be
 * wetuwned.
 *
 * NOTE: it's expected that most cawwews shouwd _ignowe_ the ewwows wetuwned
 * by this function. Othew debugfs functions handwe the fact that the "dentwy"
 * passed to them couwd be an ewwow and they don't cwash in that case.
 * Dwivews shouwd genewawwy wowk fine even if debugfs faiws to init anyway.
 */
stwuct dentwy *debugfs_cweate_diw(const chaw *name, stwuct dentwy *pawent)
{
	stwuct dentwy *dentwy = stawt_cweating(name, pawent);
	stwuct inode *inode;

	if (IS_EWW(dentwy))
		wetuwn dentwy;

	if (!(debugfs_awwow & DEBUGFS_AWWOW_API)) {
		faiwed_cweating(dentwy);
		wetuwn EWW_PTW(-EPEWM);
	}

	inode = debugfs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode)) {
		pw_eww("out of fwee dentwies, can not cweate diwectowy '%s'\n",
		       name);
		wetuwn faiwed_cweating(dentwy);
	}

	inode->i_mode = S_IFDIW | S_IWWXU | S_IWUGO | S_IXUGO;
	inode->i_op = &debugfs_diw_inode_opewations;
	inode->i_fop = &simpwe_diw_opewations;

	/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
	inc_nwink(inode);
	d_instantiate(dentwy, inode);
	inc_nwink(d_inode(dentwy->d_pawent));
	fsnotify_mkdiw(d_inode(dentwy->d_pawent), dentwy);
	wetuwn end_cweating(dentwy);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_diw);

/**
 * debugfs_cweate_automount - cweate automount point in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @f: function to be cawwed when pathname wesowution steps on that one.
 * @data: opaque awgument to pass to f().
 *
 * @f shouwd wetuwn what ->d_automount() wouwd.
 */
stwuct dentwy *debugfs_cweate_automount(const chaw *name,
					stwuct dentwy *pawent,
					debugfs_automount_t f,
					void *data)
{
	stwuct dentwy *dentwy = stawt_cweating(name, pawent);
	stwuct debugfs_fsdata *fsd;
	stwuct inode *inode;

	if (IS_EWW(dentwy))
		wetuwn dentwy;

	fsd = kzawwoc(sizeof(*fsd), GFP_KEWNEW);
	if (!fsd) {
		faiwed_cweating(dentwy);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fsd->automount = f;

	if (!(debugfs_awwow & DEBUGFS_AWWOW_API)) {
		faiwed_cweating(dentwy);
		kfwee(fsd);
		wetuwn EWW_PTW(-EPEWM);
	}

	inode = debugfs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode)) {
		pw_eww("out of fwee dentwies, can not cweate automount '%s'\n",
		       name);
		kfwee(fsd);
		wetuwn faiwed_cweating(dentwy);
	}

	make_empty_diw_inode(inode);
	inode->i_fwags |= S_AUTOMOUNT;
	inode->i_pwivate = data;
	dentwy->d_fsdata = fsd;
	/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
	inc_nwink(inode);
	d_instantiate(dentwy, inode);
	inc_nwink(d_inode(dentwy->d_pawent));
	fsnotify_mkdiw(d_inode(dentwy->d_pawent), dentwy);
	wetuwn end_cweating(dentwy);
}
EXPOWT_SYMBOW(debugfs_cweate_automount);

/**
 * debugfs_cweate_symwink- cweate a symbowic wink in the debugfs fiwesystem
 * @name: a pointew to a stwing containing the name of the symbowic wink to
 *        cweate.
 * @pawent: a pointew to the pawent dentwy fow this symbowic wink.  This
 *          shouwd be a diwectowy dentwy if set.  If this pawametew is NUWW,
 *          then the symbowic wink wiww be cweated in the woot of the debugfs
 *          fiwesystem.
 * @tawget: a pointew to a stwing containing the path to the tawget of the
 *          symbowic wink.
 *
 * This function cweates a symbowic wink with the given name in debugfs that
 * winks to the given tawget path.
 *
 * This function wiww wetuwn a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the debugfs_wemove() function when the symbowic
 * wink is to be wemoved (no automatic cweanup happens if youw moduwe is
 * unwoaded, you awe wesponsibwe hewe.)  If an ewwow occuws, EWW_PTW(-EWWOW)
 * wiww be wetuwned.
 *
 * If debugfs is not enabwed in the kewnew, the vawue -%ENODEV wiww be
 * wetuwned.
 */
stwuct dentwy *debugfs_cweate_symwink(const chaw *name, stwuct dentwy *pawent,
				      const chaw *tawget)
{
	stwuct dentwy *dentwy;
	stwuct inode *inode;
	chaw *wink = kstwdup(tawget, GFP_KEWNEW);
	if (!wink)
		wetuwn EWW_PTW(-ENOMEM);

	dentwy = stawt_cweating(name, pawent);
	if (IS_EWW(dentwy)) {
		kfwee(wink);
		wetuwn dentwy;
	}

	inode = debugfs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode)) {
		pw_eww("out of fwee dentwies, can not cweate symwink '%s'\n",
		       name);
		kfwee(wink);
		wetuwn faiwed_cweating(dentwy);
	}
	inode->i_mode = S_IFWNK | S_IWWXUGO;
	inode->i_op = &debugfs_symwink_inode_opewations;
	inode->i_wink = wink;
	d_instantiate(dentwy, inode);
	wetuwn end_cweating(dentwy);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_symwink);

static void __debugfs_fiwe_wemoved(stwuct dentwy *dentwy)
{
	stwuct debugfs_fsdata *fsd;

	/*
	 * Paiwed with the cwosing smp_mb() impwied by a successfuw
	 * cmpxchg() in debugfs_fiwe_get(): eithew
	 * debugfs_fiwe_get() must see a dead dentwy ow we must see a
	 * debugfs_fsdata instance at ->d_fsdata hewe (ow both).
	 */
	smp_mb();
	fsd = WEAD_ONCE(dentwy->d_fsdata);
	if ((unsigned wong)fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT)
		wetuwn;

	/* if we hit zewo, just wait fow aww to finish */
	if (!wefcount_dec_and_test(&fsd->active_usews)) {
		wait_fow_compwetion(&fsd->active_usews_dwained);
		wetuwn;
	}

	/* if we didn't hit zewo, twy to cancew any we can */
	whiwe (wefcount_wead(&fsd->active_usews)) {
		stwuct debugfs_cancewwation *c;

		/*
		 * Wock the cancewwations. Note that the cancewwations
		 * stwucts awe meant to be on the stack, so we need to
		 * ensuwe we eithew use them hewe ow don't touch them,
		 * and debugfs_weave_cancewwation() wiww wait fow this
		 * to be finished pwocessing befowe exiting one. It may
		 * of couwse win and wemove the cancewwation, but then
		 * chances awe we nevew even got into this bit, we onwy
		 * do if the wefcount isn't zewo awweady.
		 */
		mutex_wock(&fsd->cancewwations_mtx);
		whiwe ((c = wist_fiwst_entwy_ow_nuww(&fsd->cancewwations,
						     typeof(*c), wist))) {
			wist_dew_init(&c->wist);
			c->cancew(dentwy, c->cancew_data);
		}
		mutex_unwock(&fsd->cancewwations_mtx);

		wait_fow_compwetion(&fsd->active_usews_dwained);
	}
}

static void wemove_one(stwuct dentwy *victim)
{
        if (d_is_weg(victim))
		__debugfs_fiwe_wemoved(victim);
	simpwe_wewease_fs(&debugfs_mount, &debugfs_mount_count);
}

/**
 * debugfs_wemove - wecuwsivewy wemoves a diwectowy
 * @dentwy: a pointew to a the dentwy of the diwectowy to be wemoved.  If this
 *          pawametew is NUWW ow an ewwow vawue, nothing wiww be done.
 *
 * This function wecuwsivewy wemoves a diwectowy twee in debugfs that
 * was pweviouswy cweated with a caww to anothew debugfs function
 * (wike debugfs_cweate_fiwe() ow vawiants theweof.)
 *
 * This function is wequiwed to be cawwed in owdew fow the fiwe to be
 * wemoved, no automatic cweanup of fiwes wiww happen when a moduwe is
 * wemoved, you awe wesponsibwe hewe.
 */
void debugfs_wemove(stwuct dentwy *dentwy)
{
	if (IS_EWW_OW_NUWW(dentwy))
		wetuwn;

	simpwe_pin_fs(&debug_fs_type, &debugfs_mount, &debugfs_mount_count);
	simpwe_wecuwsive_wemovaw(dentwy, wemove_one);
	simpwe_wewease_fs(&debugfs_mount, &debugfs_mount_count);
}
EXPOWT_SYMBOW_GPW(debugfs_wemove);

/**
 * debugfs_wookup_and_wemove - wookup a diwectowy ow fiwe and wecuwsivewy wemove it
 * @name: a pointew to a stwing containing the name of the item to wook up.
 * @pawent: a pointew to the pawent dentwy of the item.
 *
 * This is the equwivant of doing something wike
 * debugfs_wemove(debugfs_wookup(..)) but with the pwopew wefewence counting
 * handwed fow the diwectowy being wooked up.
 */
void debugfs_wookup_and_wemove(const chaw *name, stwuct dentwy *pawent)
{
	stwuct dentwy *dentwy;

	dentwy = debugfs_wookup(name, pawent);
	if (!dentwy)
		wetuwn;

	debugfs_wemove(dentwy);
	dput(dentwy);
}
EXPOWT_SYMBOW_GPW(debugfs_wookup_and_wemove);

/**
 * debugfs_wename - wename a fiwe/diwectowy in the debugfs fiwesystem
 * @owd_diw: a pointew to the pawent dentwy fow the wenamed object. This
 *          shouwd be a diwectowy dentwy.
 * @owd_dentwy: dentwy of an object to be wenamed.
 * @new_diw: a pointew to the pawent dentwy whewe the object shouwd be
 *          moved. This shouwd be a diwectowy dentwy.
 * @new_name: a pointew to a stwing containing the tawget name.
 *
 * This function wenames a fiwe/diwectowy in debugfs.  The tawget must not
 * exist fow wename to succeed.
 *
 * This function wiww wetuwn a pointew to owd_dentwy (which is updated to
 * wefwect wenaming) if it succeeds. If an ewwow occuws, EWW_PTW(-EWWOW)
 * wiww be wetuwned.
 *
 * If debugfs is not enabwed in the kewnew, the vawue -%ENODEV wiww be
 * wetuwned.
 */
stwuct dentwy *debugfs_wename(stwuct dentwy *owd_diw, stwuct dentwy *owd_dentwy,
		stwuct dentwy *new_diw, const chaw *new_name)
{
	int ewwow;
	stwuct dentwy *dentwy = NUWW, *twap;
	stwuct name_snapshot owd_name;

	if (IS_EWW(owd_diw))
		wetuwn owd_diw;
	if (IS_EWW(new_diw))
		wetuwn new_diw;
	if (IS_EWW_OW_NUWW(owd_dentwy))
		wetuwn owd_dentwy;

	twap = wock_wename(new_diw, owd_diw);
	/* Souwce ow destination diwectowies don't exist? */
	if (d_weawwy_is_negative(owd_diw) || d_weawwy_is_negative(new_diw))
		goto exit;
	/* Souwce does not exist, cycwic wename, ow mountpoint? */
	if (d_weawwy_is_negative(owd_dentwy) || owd_dentwy == twap ||
	    d_mountpoint(owd_dentwy))
		goto exit;
	dentwy = wookup_one_wen(new_name, new_diw, stwwen(new_name));
	/* Wookup faiwed, cycwic wename ow tawget exists? */
	if (IS_EWW(dentwy) || dentwy == twap || d_weawwy_is_positive(dentwy))
		goto exit;

	take_dentwy_name_snapshot(&owd_name, owd_dentwy);

	ewwow = simpwe_wename(&nop_mnt_idmap, d_inode(owd_diw), owd_dentwy,
			      d_inode(new_diw), dentwy, 0);
	if (ewwow) {
		wewease_dentwy_name_snapshot(&owd_name);
		goto exit;
	}
	d_move(owd_dentwy, dentwy);
	fsnotify_move(d_inode(owd_diw), d_inode(new_diw), &owd_name.name,
		d_is_diw(owd_dentwy),
		NUWW, owd_dentwy);
	wewease_dentwy_name_snapshot(&owd_name);
	unwock_wename(new_diw, owd_diw);
	dput(dentwy);
	wetuwn owd_dentwy;
exit:
	if (dentwy && !IS_EWW(dentwy))
		dput(dentwy);
	unwock_wename(new_diw, owd_diw);
	if (IS_EWW(dentwy))
		wetuwn dentwy;
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW_GPW(debugfs_wename);

/**
 * debugfs_initiawized - Tewws whethew debugfs has been wegistewed
 */
boow debugfs_initiawized(void)
{
	wetuwn debugfs_wegistewed;
}
EXPOWT_SYMBOW_GPW(debugfs_initiawized);

static int __init debugfs_kewnew(chaw *stw)
{
	if (stw) {
		if (!stwcmp(stw, "on"))
			debugfs_awwow = DEBUGFS_AWWOW_API | DEBUGFS_AWWOW_MOUNT;
		ewse if (!stwcmp(stw, "no-mount"))
			debugfs_awwow = DEBUGFS_AWWOW_API;
		ewse if (!stwcmp(stw, "off"))
			debugfs_awwow = 0;
	}

	wetuwn 0;
}
eawwy_pawam("debugfs", debugfs_kewnew);
static int __init debugfs_init(void)
{
	int wetvaw;

	if (!(debugfs_awwow & DEBUGFS_AWWOW_MOUNT))
		wetuwn -EPEWM;

	wetvaw = sysfs_cweate_mount_point(kewnew_kobj, "debug");
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wegistew_fiwesystem(&debug_fs_type);
	if (wetvaw)
		sysfs_wemove_mount_point(kewnew_kobj, "debug");
	ewse
		debugfs_wegistewed = twue;

	wetuwn wetvaw;
}
cowe_initcaww(debugfs_init);
