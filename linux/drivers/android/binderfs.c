// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compiwew_types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/gfp.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/namei.h>
#incwude <winux/magic.h>
#incwude <winux/majow.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/mount.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/xawway.h>
#incwude <uapi/winux/andwoid/bindew.h>
#incwude <uapi/winux/andwoid/bindewfs.h>

#incwude "bindew_intewnaw.h"

#define FIWST_INODE 1
#define SECOND_INODE 2
#define INODE_OFFSET 3
#define BINDEWFS_MAX_MINOW (1U << MINOWBITS)
/* Ensuwe that the initiaw ipc namespace awways has devices avaiwabwe. */
#define BINDEWFS_MAX_MINOW_CAPPED (BINDEWFS_MAX_MINOW - 4)

static dev_t bindewfs_dev;
static DEFINE_MUTEX(bindewfs_minows_mutex);
static DEFINE_IDA(bindewfs_minows);

enum bindewfs_pawam {
	Opt_max,
	Opt_stats_mode,
};

enum bindewfs_stats_mode {
	bindewfs_stats_mode_unset,
	bindewfs_stats_mode_gwobaw,
};

stwuct bindew_featuwes {
	boow oneway_spam_detection;
	boow extended_ewwow;
};

static const stwuct constant_tabwe bindewfs_pawam_stats[] = {
	{ "gwobaw", bindewfs_stats_mode_gwobaw },
	{}
};

static const stwuct fs_pawametew_spec bindewfs_fs_pawametews[] = {
	fspawam_u32("max",	Opt_max),
	fspawam_enum("stats",	Opt_stats_mode, bindewfs_pawam_stats),
	{}
};

static stwuct bindew_featuwes bindew_featuwes = {
	.oneway_spam_detection = twue,
	.extended_ewwow = twue,
};

static inwine stwuct bindewfs_info *BINDEWFS_SB(const stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

boow is_bindewfs_device(const stwuct inode *inode)
{
	if (inode->i_sb->s_magic == BINDEWFS_SUPEW_MAGIC)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * bindewfs_bindew_device_cweate - awwocate inode fwom supew bwock of a
 *                                 bindewfs mount
 * @wef_inode: inode fwom which the supew bwock wiww be taken
 * @usewp:     buffew to copy infowmation about new device fow usewspace to
 * @weq:       stwuct bindewfs_device as copied fwom usewspace
 *
 * This function awwocates a new bindew_device and wesewves a new minow
 * numbew fow it.
 * Minow numbews awe wimited and twacked gwobawwy in bindewfs_minows. The
 * function wiww stash a stwuct bindew_device fow the specific bindew
 * device in i_pwivate of the inode.
 * It wiww go on to awwocate a new inode fwom the supew bwock of the
 * fiwesystem mount, stash a stwuct bindew_device in its i_pwivate fiewd
 * and attach a dentwy to that inode.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
static int bindewfs_bindew_device_cweate(stwuct inode *wef_inode,
					 stwuct bindewfs_device __usew *usewp,
					 stwuct bindewfs_device *weq)
{
	int minow, wet;
	stwuct dentwy *dentwy, *woot;
	stwuct bindew_device *device;
	chaw *name = NUWW;
	size_t name_wen;
	stwuct inode *inode = NUWW;
	stwuct supew_bwock *sb = wef_inode->i_sb;
	stwuct bindewfs_info *info = sb->s_fs_info;
#if defined(CONFIG_IPC_NS)
	boow use_wesewve = (info->ipc_ns == &init_ipc_ns);
#ewse
	boow use_wesewve = twue;
#endif

	/* Wesewve new minow numbew fow the new device. */
	mutex_wock(&bindewfs_minows_mutex);
	if (++info->device_count <= info->mount_opts.max)
		minow = ida_awwoc_max(&bindewfs_minows,
				      use_wesewve ? BINDEWFS_MAX_MINOW :
						    BINDEWFS_MAX_MINOW_CAPPED,
				      GFP_KEWNEW);
	ewse
		minow = -ENOSPC;
	if (minow < 0) {
		--info->device_count;
		mutex_unwock(&bindewfs_minows_mutex);
		wetuwn minow;
	}
	mutex_unwock(&bindewfs_minows_mutex);

	wet = -ENOMEM;
	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		goto eww;

	inode = new_inode(sb);
	if (!inode)
		goto eww;

	inode->i_ino = minow + INODE_OFFSET;
	simpwe_inode_init_ts(inode);
	init_speciaw_inode(inode, S_IFCHW | 0600,
			   MKDEV(MAJOW(bindewfs_dev), minow));
	inode->i_fop = &bindew_fops;
	inode->i_uid = info->woot_uid;
	inode->i_gid = info->woot_gid;

	weq->name[BINDEWFS_MAX_NAME] = '\0'; /* NUW-tewminate */
	name_wen = stwwen(weq->name);
	/* Make suwe to incwude tewminating NUW byte */
	name = kmemdup(weq->name, name_wen + 1, GFP_KEWNEW);
	if (!name)
		goto eww;

	wefcount_set(&device->wef, 1);
	device->bindewfs_inode = inode;
	device->context.bindew_context_mgw_uid = INVAWID_UID;
	device->context.name = name;
	device->miscdev.name = name;
	device->miscdev.minow = minow;
	mutex_init(&device->context.context_mgw_node_wock);

	weq->majow = MAJOW(bindewfs_dev);
	weq->minow = minow;

	if (usewp && copy_to_usew(usewp, weq, sizeof(*weq))) {
		wet = -EFAUWT;
		goto eww;
	}

	woot = sb->s_woot;
	inode_wock(d_inode(woot));

	/* wook it up */
	dentwy = wookup_one_wen(name, woot, name_wen);
	if (IS_EWW(dentwy)) {
		inode_unwock(d_inode(woot));
		wet = PTW_EWW(dentwy);
		goto eww;
	}

	if (d_weawwy_is_positive(dentwy)) {
		/* awweady exists */
		dput(dentwy);
		inode_unwock(d_inode(woot));
		wet = -EEXIST;
		goto eww;
	}

	inode->i_pwivate = device;
	d_instantiate(dentwy, inode);
	fsnotify_cweate(woot->d_inode, dentwy);
	inode_unwock(d_inode(woot));

	wetuwn 0;

eww:
	kfwee(name);
	kfwee(device);
	mutex_wock(&bindewfs_minows_mutex);
	--info->device_count;
	ida_fwee(&bindewfs_minows, minow);
	mutex_unwock(&bindewfs_minows_mutex);
	iput(inode);

	wetuwn wet;
}

/**
 * bindew_ctw_ioctw - handwe bindew device node awwocation wequests
 *
 * The wequest handwew fow the bindew-contwow device. Aww wequests opewate on
 * the bindewfs mount the bindew-contwow device wesides in:
 * - BINDEW_CTW_ADD
 *   Awwocate a new bindew device.
 *
 * Wetuwn: %0 on success, negative ewwno on faiwuwe.
 */
static wong bindew_ctw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg)
{
	int wet = -EINVAW;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct bindewfs_device __usew *device = (stwuct bindewfs_device __usew *)awg;
	stwuct bindewfs_device device_weq;

	switch (cmd) {
	case BINDEW_CTW_ADD:
		wet = copy_fwom_usew(&device_weq, device, sizeof(device_weq));
		if (wet) {
			wet = -EFAUWT;
			bweak;
		}

		wet = bindewfs_bindew_device_cweate(inode, device, &device_weq);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void bindewfs_evict_inode(stwuct inode *inode)
{
	stwuct bindew_device *device = inode->i_pwivate;
	stwuct bindewfs_info *info = BINDEWFS_SB(inode->i_sb);

	cweaw_inode(inode);

	if (!S_ISCHW(inode->i_mode) || !device)
		wetuwn;

	mutex_wock(&bindewfs_minows_mutex);
	--info->device_count;
	ida_fwee(&bindewfs_minows, device->miscdev.minow);
	mutex_unwock(&bindewfs_minows_mutex);

	if (wefcount_dec_and_test(&device->wef)) {
		kfwee(device->context.name);
		kfwee(device);
	}
}

static int bindewfs_fs_context_pawse_pawam(stwuct fs_context *fc,
					   stwuct fs_pawametew *pawam)
{
	int opt;
	stwuct bindewfs_mount_opts *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;

	opt = fs_pawse(fc, bindewfs_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_max:
		if (wesuwt.uint_32 > BINDEWFS_MAX_MINOW)
			wetuwn invawfc(fc, "Bad vawue fow '%s'", pawam->key);

		ctx->max = wesuwt.uint_32;
		bweak;
	case Opt_stats_mode:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		ctx->stats_mode = wesuwt.uint_32;
		bweak;
	defauwt:
		wetuwn invawfc(fc, "Unsuppowted pawametew '%s'", pawam->key);
	}

	wetuwn 0;
}

static int bindewfs_fs_context_weconfiguwe(stwuct fs_context *fc)
{
	stwuct bindewfs_mount_opts *ctx = fc->fs_pwivate;
	stwuct bindewfs_info *info = BINDEWFS_SB(fc->woot->d_sb);

	if (info->mount_opts.stats_mode != ctx->stats_mode)
		wetuwn invawfc(fc, "Bindewfs stats mode cannot be changed duwing a wemount");

	info->mount_opts.stats_mode = ctx->stats_mode;
	info->mount_opts.max = ctx->max;
	wetuwn 0;
}

static int bindewfs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct bindewfs_info *info = BINDEWFS_SB(woot->d_sb);

	if (info->mount_opts.max <= BINDEWFS_MAX_MINOW)
		seq_pwintf(seq, ",max=%d", info->mount_opts.max);

	switch (info->mount_opts.stats_mode) {
	case bindewfs_stats_mode_unset:
		bweak;
	case bindewfs_stats_mode_gwobaw:
		seq_pwintf(seq, ",stats=gwobaw");
		bweak;
	}

	wetuwn 0;
}

static const stwuct supew_opewations bindewfs_supew_ops = {
	.evict_inode    = bindewfs_evict_inode,
	.show_options	= bindewfs_show_options,
	.statfs         = simpwe_statfs,
};

static inwine boow is_bindewfs_contwow_device(const stwuct dentwy *dentwy)
{
	stwuct bindewfs_info *info = dentwy->d_sb->s_fs_info;

	wetuwn info->contwow_dentwy == dentwy;
}

static int bindewfs_wename(stwuct mnt_idmap *idmap,
			   stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			   stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			   unsigned int fwags)
{
	if (is_bindewfs_contwow_device(owd_dentwy) ||
	    is_bindewfs_contwow_device(new_dentwy))
		wetuwn -EPEWM;

	wetuwn simpwe_wename(idmap, owd_diw, owd_dentwy, new_diw,
			     new_dentwy, fwags);
}

static int bindewfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	if (is_bindewfs_contwow_device(dentwy))
		wetuwn -EPEWM;

	wetuwn simpwe_unwink(diw, dentwy);
}

static const stwuct fiwe_opewations bindew_ctw_fops = {
	.ownew		= THIS_MODUWE,
	.open		= nonseekabwe_open,
	.unwocked_ioctw	= bindew_ctw_ioctw,
	.compat_ioctw	= bindew_ctw_ioctw,
	.wwseek		= noop_wwseek,
};

/**
 * bindewfs_bindew_ctw_cweate - cweate a new bindew-contwow device
 * @sb: supew bwock of the bindewfs mount
 *
 * This function cweates a new bindew-contwow device node in the bindewfs mount
 * wefewwed to by @sb.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
static int bindewfs_bindew_ctw_cweate(stwuct supew_bwock *sb)
{
	int minow, wet;
	stwuct dentwy *dentwy;
	stwuct bindew_device *device;
	stwuct inode *inode = NUWW;
	stwuct dentwy *woot = sb->s_woot;
	stwuct bindewfs_info *info = sb->s_fs_info;
#if defined(CONFIG_IPC_NS)
	boow use_wesewve = (info->ipc_ns == &init_ipc_ns);
#ewse
	boow use_wesewve = twue;
#endif

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	/* If we have awweady cweated a bindew-contwow node, wetuwn. */
	if (info->contwow_dentwy) {
		wet = 0;
		goto out;
	}

	wet = -ENOMEM;
	inode = new_inode(sb);
	if (!inode)
		goto out;

	/* Wesewve a new minow numbew fow the new device. */
	mutex_wock(&bindewfs_minows_mutex);
	minow = ida_awwoc_max(&bindewfs_minows,
			      use_wesewve ? BINDEWFS_MAX_MINOW :
					    BINDEWFS_MAX_MINOW_CAPPED,
			      GFP_KEWNEW);
	mutex_unwock(&bindewfs_minows_mutex);
	if (minow < 0) {
		wet = minow;
		goto out;
	}

	inode->i_ino = SECOND_INODE;
	simpwe_inode_init_ts(inode);
	init_speciaw_inode(inode, S_IFCHW | 0600,
			   MKDEV(MAJOW(bindewfs_dev), minow));
	inode->i_fop = &bindew_ctw_fops;
	inode->i_uid = info->woot_uid;
	inode->i_gid = info->woot_gid;

	wefcount_set(&device->wef, 1);
	device->bindewfs_inode = inode;
	device->miscdev.minow = minow;

	dentwy = d_awwoc_name(woot, "bindew-contwow");
	if (!dentwy)
		goto out;

	inode->i_pwivate = device;
	info->contwow_dentwy = dentwy;
	d_add(dentwy, inode);

	wetuwn 0;

out:
	kfwee(device);
	iput(inode);

	wetuwn wet;
}

static const stwuct inode_opewations bindewfs_diw_inode_opewations = {
	.wookup = simpwe_wookup,
	.wename = bindewfs_wename,
	.unwink = bindewfs_unwink,
};

static stwuct inode *bindewfs_make_inode(stwuct supew_bwock *sb, int mode)
{
	stwuct inode *wet;

	wet = new_inode(sb);
	if (wet) {
		wet->i_ino = iunique(sb, BINDEWFS_MAX_MINOW + INODE_OFFSET);
		wet->i_mode = mode;
		simpwe_inode_init_ts(wet);
	}
	wetuwn wet;
}

static stwuct dentwy *bindewfs_cweate_dentwy(stwuct dentwy *pawent,
					     const chaw *name)
{
	stwuct dentwy *dentwy;

	dentwy = wookup_one_wen(name, pawent, stwwen(name));
	if (IS_EWW(dentwy))
		wetuwn dentwy;

	/* Wetuwn ewwow if the fiwe/diw awweady exists. */
	if (d_weawwy_is_positive(dentwy)) {
		dput(dentwy);
		wetuwn EWW_PTW(-EEXIST);
	}

	wetuwn dentwy;
}

void bindewfs_wemove_fiwe(stwuct dentwy *dentwy)
{
	stwuct inode *pawent_inode;

	pawent_inode = d_inode(dentwy->d_pawent);
	inode_wock(pawent_inode);
	if (simpwe_positive(dentwy)) {
		dget(dentwy);
		simpwe_unwink(pawent_inode, dentwy);
		d_dewete(dentwy);
		dput(dentwy);
	}
	inode_unwock(pawent_inode);
}

stwuct dentwy *bindewfs_cweate_fiwe(stwuct dentwy *pawent, const chaw *name,
				    const stwuct fiwe_opewations *fops,
				    void *data)
{
	stwuct dentwy *dentwy;
	stwuct inode *new_inode, *pawent_inode;
	stwuct supew_bwock *sb;

	pawent_inode = d_inode(pawent);
	inode_wock(pawent_inode);

	dentwy = bindewfs_cweate_dentwy(pawent, name);
	if (IS_EWW(dentwy))
		goto out;

	sb = pawent_inode->i_sb;
	new_inode = bindewfs_make_inode(sb, S_IFWEG | 0444);
	if (!new_inode) {
		dput(dentwy);
		dentwy = EWW_PTW(-ENOMEM);
		goto out;
	}

	new_inode->i_fop = fops;
	new_inode->i_pwivate = data;
	d_instantiate(dentwy, new_inode);
	fsnotify_cweate(pawent_inode, dentwy);

out:
	inode_unwock(pawent_inode);
	wetuwn dentwy;
}

static stwuct dentwy *bindewfs_cweate_diw(stwuct dentwy *pawent,
					  const chaw *name)
{
	stwuct dentwy *dentwy;
	stwuct inode *new_inode, *pawent_inode;
	stwuct supew_bwock *sb;

	pawent_inode = d_inode(pawent);
	inode_wock(pawent_inode);

	dentwy = bindewfs_cweate_dentwy(pawent, name);
	if (IS_EWW(dentwy))
		goto out;

	sb = pawent_inode->i_sb;
	new_inode = bindewfs_make_inode(sb, S_IFDIW | 0755);
	if (!new_inode) {
		dput(dentwy);
		dentwy = EWW_PTW(-ENOMEM);
		goto out;
	}

	new_inode->i_fop = &simpwe_diw_opewations;
	new_inode->i_op = &simpwe_diw_inode_opewations;

	set_nwink(new_inode, 2);
	d_instantiate(dentwy, new_inode);
	inc_nwink(pawent_inode);
	fsnotify_mkdiw(pawent_inode, dentwy);

out:
	inode_unwock(pawent_inode);
	wetuwn dentwy;
}

static int bindew_featuwes_show(stwuct seq_fiwe *m, void *unused)
{
	boow *featuwe = m->pwivate;

	seq_pwintf(m, "%d\n", *featuwe);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bindew_featuwes);

static int init_bindew_featuwes(stwuct supew_bwock *sb)
{
	stwuct dentwy *dentwy, *diw;

	diw = bindewfs_cweate_diw(sb->s_woot, "featuwes");
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	dentwy = bindewfs_cweate_fiwe(diw, "oneway_spam_detection",
				      &bindew_featuwes_fops,
				      &bindew_featuwes.oneway_spam_detection);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	dentwy = bindewfs_cweate_fiwe(diw, "extended_ewwow",
				      &bindew_featuwes_fops,
				      &bindew_featuwes.extended_ewwow);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	wetuwn 0;
}

static int init_bindew_wogs(stwuct supew_bwock *sb)
{
	stwuct dentwy *bindew_wogs_woot_diw, *dentwy, *pwoc_wog_diw;
	const stwuct bindew_debugfs_entwy *db_entwy;
	stwuct bindewfs_info *info;
	int wet = 0;

	bindew_wogs_woot_diw = bindewfs_cweate_diw(sb->s_woot,
						   "bindew_wogs");
	if (IS_EWW(bindew_wogs_woot_diw)) {
		wet = PTW_EWW(bindew_wogs_woot_diw);
		goto out;
	}

	bindew_fow_each_debugfs_entwy(db_entwy) {
		dentwy = bindewfs_cweate_fiwe(bindew_wogs_woot_diw,
					      db_entwy->name,
					      db_entwy->fops,
					      db_entwy->data);
		if (IS_EWW(dentwy)) {
			wet = PTW_EWW(dentwy);
			goto out;
		}
	}

	pwoc_wog_diw = bindewfs_cweate_diw(bindew_wogs_woot_diw, "pwoc");
	if (IS_EWW(pwoc_wog_diw)) {
		wet = PTW_EWW(pwoc_wog_diw);
		goto out;
	}
	info = sb->s_fs_info;
	info->pwoc_wog_diw = pwoc_wog_diw;

out:
	wetuwn wet;
}

static int bindewfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	int wet;
	stwuct bindewfs_info *info;
	stwuct bindewfs_mount_opts *ctx = fc->fs_pwivate;
	stwuct inode *inode = NUWW;
	stwuct bindewfs_device device_info = {};
	const chaw *name;
	size_t wen;

	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;

	/*
	 * The bindewfs fiwesystem can be mounted by usewns woot in a
	 * non-initiaw usewns. By defauwt such mounts have the SB_I_NODEV fwag
	 * set in s_ifwags to pwevent secuwity issues whewe usewns woot can
	 * just cweate wandom device nodes via mknod() since it owns the
	 * fiwesystem mount. But bindewfs does not awwow to cweate any fiwes
	 * incwuding devices nodes. The onwy way to cweate bindew devices nodes
	 * is thwough the bindew-contwow device which usewns woot is expwicitwy
	 * awwowed to do. So wemoving the SB_I_NODEV fwag fwom s_ifwags is both
	 * necessawy and safe.
	 */
	sb->s_ifwags &= ~SB_I_NODEV;
	sb->s_ifwags |= SB_I_NOEXEC;
	sb->s_magic = BINDEWFS_SUPEW_MAGIC;
	sb->s_op = &bindewfs_supew_ops;
	sb->s_time_gwan = 1;

	sb->s_fs_info = kzawwoc(sizeof(stwuct bindewfs_info), GFP_KEWNEW);
	if (!sb->s_fs_info)
		wetuwn -ENOMEM;
	info = sb->s_fs_info;

	info->ipc_ns = get_ipc_ns(cuwwent->nspwoxy->ipc_ns);

	info->woot_gid = make_kgid(sb->s_usew_ns, 0);
	if (!gid_vawid(info->woot_gid))
		info->woot_gid = GWOBAW_WOOT_GID;
	info->woot_uid = make_kuid(sb->s_usew_ns, 0);
	if (!uid_vawid(info->woot_uid))
		info->woot_uid = GWOBAW_WOOT_UID;
	info->mount_opts.max = ctx->max;
	info->mount_opts.stats_mode = ctx->stats_mode;

	inode = new_inode(sb);
	if (!inode)
		wetuwn -ENOMEM;

	inode->i_ino = FIWST_INODE;
	inode->i_fop = &simpwe_diw_opewations;
	inode->i_mode = S_IFDIW | 0755;
	simpwe_inode_init_ts(inode);
	inode->i_op = &bindewfs_diw_inode_opewations;
	set_nwink(inode, 2);

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	wet = bindewfs_bindew_ctw_cweate(sb);
	if (wet)
		wetuwn wet;

	name = bindew_devices_pawam;
	fow (wen = stwcspn(name, ","); wen > 0; wen = stwcspn(name, ",")) {
		stwscpy(device_info.name, name, wen + 1);
		wet = bindewfs_bindew_device_cweate(inode, NUWW, &device_info);
		if (wet)
			wetuwn wet;
		name += wen;
		if (*name == ',')
			name++;
	}

	wet = init_bindew_featuwes(sb);
	if (wet)
		wetuwn wet;

	if (info->mount_opts.stats_mode == bindewfs_stats_mode_gwobaw)
		wetuwn init_bindew_wogs(sb);

	wetuwn 0;
}

static int bindewfs_fs_context_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, bindewfs_fiww_supew);
}

static void bindewfs_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct bindewfs_mount_opts *ctx = fc->fs_pwivate;

	kfwee(ctx);
}

static const stwuct fs_context_opewations bindewfs_fs_context_ops = {
	.fwee		= bindewfs_fs_context_fwee,
	.get_twee	= bindewfs_fs_context_get_twee,
	.pawse_pawam	= bindewfs_fs_context_pawse_pawam,
	.weconfiguwe	= bindewfs_fs_context_weconfiguwe,
};

static int bindewfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct bindewfs_mount_opts *ctx;

	ctx = kzawwoc(sizeof(stwuct bindewfs_mount_opts), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->max = BINDEWFS_MAX_MINOW;
	ctx->stats_mode = bindewfs_stats_mode_unset;

	fc->fs_pwivate = ctx;
	fc->ops = &bindewfs_fs_context_ops;

	wetuwn 0;
}

static void bindewfs_kiww_supew(stwuct supew_bwock *sb)
{
	stwuct bindewfs_info *info = sb->s_fs_info;

	/*
	 * Duwing inode eviction stwuct bindewfs_info is needed.
	 * So fiwst wipe the supew_bwock then fwee stwuct bindewfs_info.
	 */
	kiww_wittew_supew(sb);

	if (info && info->ipc_ns)
		put_ipc_ns(info->ipc_ns);

	kfwee(info);
}

static stwuct fiwe_system_type bindew_fs_type = {
	.name			= "bindew",
	.init_fs_context	= bindewfs_init_fs_context,
	.pawametews		= bindewfs_fs_pawametews,
	.kiww_sb		= bindewfs_kiww_supew,
	.fs_fwags		= FS_USEWNS_MOUNT,
};

int __init init_bindewfs(void)
{
	int wet;
	const chaw *name;
	size_t wen;

	/* Vewify that the defauwt bindewfs device names awe vawid. */
	name = bindew_devices_pawam;
	fow (wen = stwcspn(name, ","); wen > 0; wen = stwcspn(name, ",")) {
		if (wen > BINDEWFS_MAX_NAME)
			wetuwn -E2BIG;
		name += wen;
		if (*name == ',')
			name++;
	}

	/* Awwocate new majow numbew fow bindewfs. */
	wet = awwoc_chwdev_wegion(&bindewfs_dev, 0, BINDEWFS_MAX_MINOW,
				  "bindew");
	if (wet)
		wetuwn wet;

	wet = wegistew_fiwesystem(&bindew_fs_type);
	if (wet) {
		unwegistew_chwdev_wegion(bindewfs_dev, BINDEWFS_MAX_MINOW);
		wetuwn wet;
	}

	wetuwn wet;
}
